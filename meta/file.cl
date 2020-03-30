//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| file.cl                                                     |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+


// ---------------------------------------------------------------------
// Contents:
//   Part 1: Utilities
//   Part 2: Loading
//   Part 3: Reading
//   Part 4: Top-level
//   Part 5: The show & kill compiled_methods
// ---------------------------------------------------------------------

// **********************************************************************
// *   Part 1: Utilities                                                *
// **********************************************************************


// useful gadgets
//
[self_eval(self:delimiter) : any
 -> next(reader),                       // v3.1.04 better safe than sorry
    Serror(117, "Loose delimiter ~S in program", list(self))] //<sb>

(put(mClaire/evaluate, delimiter, (self_eval @ delimiter).functional))

//<sb> add the register symbol
claire/register :: property()

// a small useful function
// PORTABILITY WARNING: the following assumes newline is ^J (ASCII 10 dec)
// PORTABILITY WARNING: what about ^M (ASCII 13 dec)
//
// a small useful function
[useless_c(r:integer) : boolean
 -> //if (r = 10 | r = 13) write(nb_line, reader, reader.nb_line + 1),
    (r = externC("'\\n'", integer) | r = externC("'\\r'", integer) | r = externC("' '", integer) | r = reader.tab) ]

// take care of PC format (10 + 13)
skipc(self:meta_reader) : any
 -> (while useless_c(firstc(self))
           let b := (firstc(self) = integer!('\n')) in
             (next(self), if (b & firstc(self) = integer!('\r')) next(self)),
     firstc(self))

// look for a meaningful termination char such as ) or ]
skipc!(r:meta_reader) : any
 -> (let c := skipc(r) in
       (if (c = integer!(';'))
           (while (r.firstc != r.eof & r.firstc != integer!('\n')) next(r),
            if (r.firstc = r.eof) EOF
            else ( /*write(nb_line, r, r.nb_line + 1),*/ skipc!(r)))
        else if (c = integer!('/'))
           let x := Kernel/read_ident(r) in
              (if (x % string) skipc!(r) else integer!('/'))
        else c))

cnext(self:meta_reader) : meta_reader -> (next(self), self)
findeol(self:meta_reader) : boolean
 -> ((while useless_c(firstc(self))
        (if (firstc(self) = integer!('\n')) break(true), next(self))) |
     firstc(self) = self.eof)

// safety checking
//
checkno(r:meta_reader,n:integer,y:any) : any
 -> (if (r.firstc != n) r
     else Serror(118, "Read wrong char ~S after ~S", list(char!(n), y)))

// reads a keyword inside a control structure
//
verify(t:any,x:any,y:any) : any
 -> (if (x % t) x
     else Serror(119, "Read ~S instead of a ~S in a ~S", list(x, t, y)))

syntax_error <: exception(code:integer, cause:string, args:list)
self_print(self:syntax_error) : void ->
	printf("Syntax error [~S]\n~I", self.code, format(self.cause, self.args))

// prints a syntax error
//
Serror(c:integer, s:string, la:list) : {}
  -> (/*if known?(last_form, reader)
  		format("`RED ---- Syntax Error[in: ~S]:\n", list(reader.last_form))
  	  else color_princ("`RED ---- Syntax Error:\n"), //<sb>
      flush(reader.fromp), //<sb> would cause an error !
      */
      syntax_error(cause = s, args = la, code = c))
      //general_error(cause = "Syntax error [" /+ string!(c) /+ "] " /+ s, args = la))


// the reader-------------------------------------------------------------
//
reader :: meta_reader(space = 202,
                      eof = 255,
                      tab = externC("'\\t'", integer), index = 1,
                      bracket = mClaire/new!(delimiter, symbol!("]")),
                      paren = mClaire/new!(delimiter, symbol!(")")),
                      comma = mClaire/new!(delimiter, symbol!(",")),
                      curly = mClaire/new!(delimiter, symbol!("}")))


READER_STACK:list[meta_reader] := list<meta_reader>()

reader_push() : void -> (READER_STACK add copy(reader))
reader_pop() : void ->
	let y := last(READER_STACK) as meta_reader,
		r := reader
	in (shrink(READER_STACK, length(READER_STACK) - 1),
		externC("memcpy(r, y, sizeof(meta_reader))"))
reader_reset() : void -> (while READER_STACK reader_pop())

// variable handling -------------------------------------------------
// reads a variable
//
extract_variable(self:any) : Variable
 -> (if (case self (Variable get(self.mClaire/pname) != self))
        (put(range, self as Variable, extract_type(self.range)),
         self as Variable)
     else let v := Variable(mClaire/pname = extract_symbol(self)) in
            (reader.last_form := v, v))

// create a variable and add it to the lexical environment
bind!(self:meta_reader,%v:Variable) : list
 -> (put(index, %v, self.index),
     let value := get(%v.mClaire/pname) in
       (put(index, self, self.index + 1),
        if (self.index > self.maxstack) put(maxstack, self, self.index),
		Language/*variable_index* := self.maxstack,
        put(%v.mClaire/pname, %v),
        list(%v, value)))

// remove a variable from the lexical environment
//
unbind!(self:meta_reader,%first:list) : any
 -> (let var := %first[1] in
       (put(index, self, self.index - 1),
        put(var.mClaire/pname, %first[2])))

// this function is called by the main and restores the reader in a good shape. Also
// closes the input port to free the associated file ! <yc>
[Core/restore_state(self:meta_reader) : void
 ->  if (self.fromp != stdin) fclose(self.fromp),
     put(fromp, self, stdin),
     put(index, self, 1),
     flush(stdin,externC("' '", integer)),                            // v3.3.10  
     Core/restore_state()]


// *********************************************************************
// *   Part 2: Loading                                                 *
// *********************************************************************


// sload is the interactive version.
//
load_file(self:string,b:boolean) : any
 -> (reader_push(),
 	 write(index, reader, 0),
     write(maxstack, reader, 0),
     reader.external := self,
     trace(3, "---- [load CLAIRE file: ~A]\n", self),
     let f := fopen_source(self),
		 start := mClaire/base!(),
         top := mClaire/index!(),
		 *item* := unknown in
       (mClaire/set_base(top),
       	reader.fromp := f,
        reader.toplevel := false,
		if not(PROCESS_EVAL_INSTRUCTIONS?)
        	try *item* := readblock(f)
			catch any *item* := unknown
		else *item* := readblock(f),
        while not(*item* = EOF)     //<FXJ+NM>  was: eof
          (if b printf("~A:~S\n",reader.Reader/nb_line,*item*),
		  mClaire/index_jump(top + (reader.maxstack + 1)),
          //[4] load_file -> ~S // *item*,
		  case *item* 
             (string (if NeedComment      // v3.1.16 -> improve comment //<sb> put comment/module/file:line in DOC_INDEX table
                       (if known?(Language/LastComment)
                           Language/LastComment :/+ ("\n" /+ *item*)  
                        else if (length(*item*) > 0)
							Language/LastComment := *item*)),
              any (Language/LastComment := unknown,
					if (PROCESS_EVAL_INSTRUCTIONS? |
						(case *item*
								(Defobj unknown?(get(*item*.iClaire/ident)),
								Call *item*.selector % {use_module,load},
								Defclass unknown?(get(*item*.iClaire/ident)),
								any (f.Core/firstc := integer!(' '), false))))
					(if not(PROCESS_EVAL_INSTRUCTIONS?)
        				try *item* := eval(*item*)
						catch any *item* := unknown
					else *item* := eval(*item*)),
				 Language/LastComment := unknown)),
           if b printf("=> ~S \n\n", *item*),
           if not(PROCESS_EVAL_INSTRUCTIONS?)
				try *item* := readblock(f)
				catch any (f.Core/firstc := integer!(' '),
							*item* := unknown)
			else *item* := readblock(f)),
        reader_pop(),
        mClaire/set_base(start),
        mClaire/set_index(top),
        fclose(f)),
     true)


// the simple load
//
load(self:string) : any -> load_file(self, false)

sload(self:string) : any -> load_file(self, true)

// loading a module into the system.
// The correct package is open and each file is loaded.
[load_file(self:module,b:boolean) : void
 ->  if (self.mClaire/status = 2)
        (funcall(self.mClaire/evaluate, any, any, any),
         self.mClaire/status := 3)
     else if (self.mClaire/status = 0 & known?(source,self))
        (trace(3, "---- Loading the module ~S.\n", self),
         begin(self),
         let s := (self.source /+ *fs*) in
           for x in list{x in self.made_of|match_wildcard?(x,"*.cl") | not(match_wildcard?(x,"*.*"))} //<sb> exclude .cpp .h ... that can be made_of in xl version
           	load_file((s /+ replace(x,".cl","")) /+ ".cl", b), //<sb> allow extension in made_of
		 for x in list{x in self.made_of|match_wildcard?(x,"*@PATH_INFO@*")}
			(trace(3, "---- [load WCL file: ~A]\n", explode(x, "@PATH_INFO@")[1]),
			reader_push(),
			reader.toplevel := false,
			let defs := load_wcl!(x),
				start := mClaire/base!(),
				top := mClaire/index!()
			in (mClaire/set_base(top),
				for y in defs
					(mClaire/index_jump(top + (reader.maxstack + 1)),
					if PROCESS_EVAL_INSTRUCTIONS?
						eval(y)),
				reader_pop(),
				mClaire/set_base(start),
				mClaire/set_index(top))),
		self.mClaire/status := 1),
	end(self)]


//<sb> prevent load @ module to load module's code
PROCESS_LOAD_MODULE?:boolean := true
set_load_module(b:boolean) : void -> (PROCESS_LOAD_MODULE? := b)

//<sb> prevent eval(*item*) in load module
PROCESS_EVAL_INSTRUCTIONS?:boolean := true
set_eval_module(b:boolean) : void -> (PROCESS_EVAL_INSTRUCTIONS? := b)

// the simple load
//
load(self:module) : any
 -> (if PROCESS_LOAD_MODULE?
 		(for x in add_modules(list(self)) load_file(x, false)))
sload(self:module) : any
 -> (if PROCESS_LOAD_MODULE?
 		(for x in add_modules(list(self)) load_file(x, true)))

// This is a very important method which adds the right order the
// modules that must be loaded to load oself. the list l represents the
// list of modules that we know will be in the result. result represent
// the current list of ordered modules
//
add_modules(self:module,l:set,result:list) : list
 -> (if (self % result) result
     else if not(self % l) result // was : else if (self % l)result add self
     else (if (known?(part_of, self) & self.part_of != claire)
     			result := add_modules(self.part_of, l, result),
           for x in self.uses
             case x (module result := add_modules(x, l, result)),
           if not(self % result) result : add self,
           for x in self.parts
           		result := add_modules(x, l, result),
           result))

//<sb> we adopt a different strategy for add_module :
// first we fill a list of needed modules 

add_parts(self:module, result:set) : void ->
	(result :add self,
	for m in self.parts add_parts(m,result))

//<sb> add part_of until claire
add_subparts(self:module, result:set) : void  ->
	(if known?(part_of, self)
		let m := self.part_of
		in (result :add self,
			if (m != claire) add_subparts(m, result)))

add_uses(self:module, result:set) : void  ->
	(if not(self % result) result :add self,
	for m in self.uses
		(if not(m % result)
			(add_uses(m,result),
			if not(m.made_of) add_parts(m,result))))

add_modules(self:module, result:set) : void ->
	(add_uses(self,result),
	add_parts(self,result), //<sb> in the xl version we add parts for queried modules only
	add_subparts(self,result),
	result :add self)

// this methods takes a list of modules that must be loaded and returns
// a list of modules that are necessary for the definition
//
add_modules(self:list) : list
 -> (let base := set<module>(), l := list<module>() in
       (for m in self add_modules(m, base),
       for x in base l := add_modules(x, base, l), l))

// load a file of expressions (quite useful)
eload(self:string) : any
 -> (reader_push(),
 	 reader.index := 0,
     reader.maxstack := 0,
     reader.nb_line := 1,
     reader.external := self,
     trace(3, "---- [eload CLAIRE file: ~A]\n", self),
     let p1:port := fopen_source(self),
         start := mClaire/base!(),
         top := mClaire/index!(),
         *item* := unknown in
       (mClaire/set_base(top),
        reader.toplevel := false,
        reader.fromp := p1,
        *item* := read(p1),
       // while not(*item* = eof)
        while not(*item* = EOF)   //<FXJ+NM>  was: eof
          (mClaire/index_jump(top + (reader.maxstack + 1)),
           if PROCESS_EVAL_INSTRUCTIONS?
				*item* := eval(*item*),
           *item* := read(p1)),
		reader_pop(),
        mClaire/set_base(start),
        mClaire/set_index(top),
        fclose(p1)),
   true)


// *********************************************************************
// *   Part 3: Read & Top-level                                        *
// *********************************************************************

// The standard read function.
// This method reads from a CLAIRE port (self).
// We first check if self is the current reading port.
// the last character read (and not used) is in last(reader)
[readblock(p:port) : any
 -> IDENTS := list<list>(),
 	if (reader.fromp = p) nextunit(reader)
     else let // v := reader.firstc,
              p2 := reader.fromp in
            (put(fromp, reader, p),
             let val := nextunit(reader) in
               (put(fromp, reader, p2),
                if (val = paren(reader) | val = curly(reader) | val = comma(reader) | val = bracket(reader))
                   Serror(117, "Loose ~S in file", list(val)),
                val)) ]

// read reads a closed expression
[read(p:port) : any
 -> let p2 := reader.fromp in
    //    v := reader.firstc in
       (if (p != p2) (put(fromp, reader, p)), // , put(firstc, reader, 32)),
        let val := (if (skipc(reader) = reader.eof) EOF     //<FXJ+NM>  was: eof
//        let val := (if (skipc(reader) = reader.eof) eof
         else nexte(reader)) in
          (if (p != p2) put(fromp, reader, p2),
           if  (val = paren(reader) | val = curly(reader) | val = comma(reader) | val = bracket(reader))
               Serror(117, "Loose ~S in file", list(val)),
           val)) ]


// read into a string
[read(self:string) : any
 ->  let x := unknown in
      (reader_push(),
      reader.toplevel := true,
       let p := port!(self)
       in (reader.fromp := p,
	       try x := nextunit(reader)
    	   catch any (
				reader_pop(),
                fclose(p),   
				close@exception(system.exception!)),
           fclose(p)),
       reader_pop(),
       x)]

q :: keyword()
//call_debug :: property()


// calls the debugger
/*debug_if_possible() : any
 -> (if (system.Kernel/debug! >= 0)
        funcall((call_debug.restrictions[1] as method).functional, any,
              system, any)
     else print_exception())*/

// a method for calling the printer without issuing a message (that would
// modify the stack and make debugging impossible).
// here we assume that self_print is always defined and is always a compiled
// function
print_exception() : any
 -> (let p := use_as_output(stdout),
         %err := system.exception!,
         %prop := ((self_print @ owner(%err)) as method) in
       (try (if not(reader.toplevel)
				let loc := Core/get_location(reader.fromp)
				in (if isfile?(loc[1])
						(if (color() = 2)
							//<sb> if color is set to 2 (i.e. HTML output mode)
							// we use a href formatter that can be configured for
							// instance to open the file at the current location
							// with a text editor
							let href := getenv("WCL_HREF_FORMATER"),
								p := buffer!(cout(), 4096),
								old := use_as_output(p)
							in (color(0), //<sb> we have to set the no-color mode to avoid convertions
								if (length(href) = 0)
									href := "txmt://open?url=$URLFILE&line=$LINE",
								href := replace(href,"$FILE", loc[1]),
								href := replace(href,"$URLFILE", url_encode("file://" /+ loc[1])),
								href := replace(href,"$LINE", string!(loc[2])),
								?>In&nbsp;<a href='<?= href ?>'><?== loc[1] ?>:<?= loc[2] ?></a><br><?
								use_as_output(old),
								fclose(p),
								color(2))
						else printf("`REDIn ~A:~S\n", loc[1], loc[2]))),
       		set_color(31,0),
 			if known?(functional, %prop)
            	funcall(%prop.functional, object, %err, any)
         	else funcall(%prop, %err),
         	princ("\n"))
        catch any
        	(//<sb> some exceptions are fatal regarding printing :
			set_color(30,0),
			if (case exception!() (system_error exception!().index % {1,2,3,24,33,34}))
				close(exception!()),
			set_color(31,0),
 			printf("\n[121] unprintable error <~S>.\n", owner(%err))),
 	  set_color(30,0),
      use_as_output(p)))

// *********************************************************************
// *     Part 4: the show & kill methods                               *
// *********************************************************************

pretty_show :: property(open = 3)

//----------------- printing an object -------------------------
// %show is an open restriction which allow to show the value of a
// binary relation
//
// this method is the basic method called for show(..)
//
show(self:any) : any
 -> (case self
      (object for rel in owner(self).slots
               printf("~S: ~S\n", rel.selector, get(rel, self)),
       any printf("~S is a ~S\n", self, owner(self))),
     true)
/*
//<sb> moved to Core/function.cl

// This is the good version of kill, the nasty one is dangerous ....
// these restrictions of kill explain the dependencies among objects
//
claire/kill(self:object) : any
 -> (case self (thing put(self.name, unknown)),
     write(instances, self.isa, self.isa.instances delete self),
     {})

claire/kill(self:class) : any
 -> (while self.instances kill(self.instances[1]),
     for x in self.descendents (if (x.superclass = self) kill(x)),
     kill@object(self))
*/


WCL_STOP :: {"(", ")", "[", "]", "{", "}", "|", ",",
			" ", "\r", "\n", "\t",
			"?", ":",
			"/*", ";", "//",
			"\"", "'",
			"#"}


// our two very special inline methods
(inlineok?(min @ integer, "lambda[(x:integer,y:integer),(if (x <= y) x else y)]"))
(inlineok?(min @ float, "lambda[(x:float,y:float),(if (x <= y) x else y)]"))

(inlineok?(max @ integer, "lambda[(x:integer,y:integer),(if (y <= x) x else y)]"))
(inlineok?(max @ float, "lambda[(x:float,y:float),(if (y <= x) x else y)]"))


min(x:any,y:any) : type[x U y] => (if (x <= y) x else y)
max(x:any,y:any) : type[x U y] => (if (x <= y) y else x)



// check if the value is known?
known?(a:table,x:any) : boolean => (get(a,x) != unknown)
unknown?(a:table,x:any) : boolean => (get(a,x) = unknown)

/*
//<sb> moved to Core/function.cl

float!(self:string) : float
 -> let x := read(self) in
      (case x (float x,
      			integer float!(x),  // v3.3.22
               any error("[??] ~A is not a float",self)))*/

// v3.00.46 a new macro
>=(self:any,x:any) : boolean => (x <= self)



// this is a useful macro for hashing
[mClaire/hashgrow(l:list,hi:property) : list
 =>  let l1 := l,
         l2 := make_list(nth_get(l1, 0) * 2, unknown) in
       (for x in l1 (if known?(x) hi(l2, x)), l2)]

//<sb> we store external dependencies (module, path)
claire/used_modules:list[tuple(module,string)] := list<tuple(module,string)>()

//<sb> query the module m = "module/version" that will be used
// by another module later ...
// place some use_module commands in your init.cl file
// use_module searches for a init.cl that match module/version in
// both publish folder and CLAIRE_LIBS
[claire/use_module(m:string) : void ->
	if (length(m) = 0) error("use_module called with an empty string !"),
	if not(isenv?("CLAIRE_LIBS")) //[3] ---- warning: environment variable CLAIRE_LIBS undefined,
	let f := realpath(getenv("_")),
		hom := (if isenv?("CLAIRE_PUBLISH_HOME") getenv("CLAIRE_PUBLISH_HOME")
				else realpath(substring(f, 1, rfind(f,*fs*) - 1) / ".." / ".." / "..")),
		p := (let pu := explode(m, "/") in (if (length(pu) > 1) pu else
				let pc := explode(m, "\\") in pc)), //look for a version (support PC & unix)
		up := (if (length(p) > 1) p[1] / p[2] else p[1]),
		libs := explode(getenv("CLAIRE_LIBS"),*ps*) add (hom / "lib"),
		oldp := pwd()
	in (if unknown?(get_value(p[1]))
			when mp := some(mp in libs|isfile?(mp / up / "init.cl"))
			in (//[3] ==== Use module ~A at ~A [v~A] ==== // m, mp, release(),
				setcwd(mp / up),
				try
					(module!() := claire,
					load("init"),
					let m := get_value(p[1])
					in (if not(m % module)
							(error("The init file ~A doesn't define the module ~A [~S]!", mp / up / "init.cl", p[1], m)),
						load(m), // force the load of the module in case that is isn't done in the init
						used_modules :add tuple(m as module, mp / up as string)))
				catch any (setcwd(oldp), close(exception!())),
				setcwd(oldp))
			else (if exists(mp in libs|isdir?(mp / p[1]))
					(if (length(p) = 1)
						//[3] ---- warning: undefined version of module ~A, expect one of: // m
					else //[3] ---- warning: unresolved module ~A, missing version ~A in: // p[1], p[2],
					let first? := true, ump := "", haveinit? := false
					in (for mp in list{mp in list{(mp / p[1])| mp in libs}|isdir?(mp)}
							(if isfile?(mp / "init.cl") haveinit? := true
							else
								let es := list{e in entries(mp)|isdir?(mp / e) & isfile?(mp / e / "init.cl")}
								in (if es
										(//[3]      [~A] ~A // mp, es,
										if first? (first? := false, ump := (sort(> @ string,es)[1] as string))))),
						if (haveinit? | length(ump) > 0)
							(//[3]      ===> try with ~A // p[1] / ump,
							if (length(ump) = 0) use_module(p[1])
							else use_module(p[1] / ump))))
				else (//[0] ---- warning: the module ~A cannot be found in any of: // m,
					for mp in libs //[0]      ~A // mp
				)),
		//<sb> last we put the compiler in a default shape
		if known?(get_value("Compile"))
			(read("erase(inline?, compiler)"),
			read("erase(safety, compiler)"),
			read("erase(overflow?, compiler)"),
			read("erase(naming, compiler)"),
			read("(compiler.source := \"csrc\")"),
			read("(Compile/FCALLSTINKS := false)")))]



[option_usage(opt:{"-f", "-ef"}) : tuple(string, string, string) ->
	tuple("Load file",
			"{-f | -ef} +[<file:path>]",
			"Load the CLAIRE file(s) <file>. The given path may contain an extension " /+
			"assuming .cl by default. When the <-f> option is used, the file is " /+
			"assumed to contain CLAIRE definitions (variables, class, methods) whereas " /+
			" <-ef> attempts to read a file made of CLAIRE expression.")]
	

[option_respond(opt:{"-f", "-ef"}, l:list) : void ->
	if not(l) invalid_option_argument(),
	if (not(isfile?(l[1])) & not(isfile?(l[1] /+ ".cl")))
		error("~A cannot be opened", l[1]),
	while (l & (isfile?(l[1]) | isfile?(l[1] /+ ".cl")))
		let path := l[1]
		in (l << 1,
			case opt
				({"-f"} load(path),
				{"-ef"} eload(path)))]

[option_usage(opt:{"-princ", "-print", "-eval"}) : tuple(string, string, string) ->
	tuple("Eval expression",
			"{-princ | -print | -eval} <exp:any>",
			"Eval the CLAIRE expression <exp>. If <-princ> or <-print> is used instead " /+
			"of <-eval>, the result of the evaluation is princed/printed on the " /+
			"standard output. Often, the hosting shell support quotes allowing " /+
			"<exp> to contain space and/or special chars.")]

[option_respond(opt:{"-eval", "-princ", "-print"}, l:list) : void ->
	if not(l) invalid_option_argument(),
	let fragment := l[1]
	in (l << 1,
		reader_push(),
		let start := mClaire/base!(),
			top := mClaire/index!(),
			*item* := unknown
		in (mClaire/set_base(top),
			reader.maxstack := 0,
			reader.index := 0, 
			reader.fromp := blob!(fragment),
			*item* := nextunit(reader),
	        if not(*item* = EOF)
				(mClaire/index_jump(top + (reader.maxstack + 1)),
				*item* := eval(*item*)),
			reader_pop(),
			mClaire/set_base(start),
			mClaire/set_index(top),
			case opt
				({"-princ"} princ(*item*),
				{"-print"} print(*item*))))]



[option_usage(opt:{"-x", "-xe", "-x?-?", "-xe?-?"}) : tuple(string, string, string) ->
	tuple("Load script",
			"{-x | -xe | -x<S:(0 .. 9)>-<W:(0 .. 9)> | -xe<S:(0 .. 9)>-<W:(0 .. 9)>} <file:path> [<args>]",
			"Load the CLAIRE file <file> with implicit options -nologo and -q. " /+
			"If the option starts with -xe the file is assumed to contain CLAIRE expressions. " /+
			"When <S> and <W> are specified they are used to initialize CLAIRE memory (see -s option). " /+
			"Unix users may use this option for for a shell script header (e.g #!/usr/local/bin/claire -x). " /+
			"If the shell command contains any arguments (<args>) one should handle them in the script through " /+
			"the system variable 'system.params'.\n")]

[option_respond(opt:{"-x", "-xe", "-x?-?", "-xe?-?"}, l:list) : void ->
	if not(l) invalid_option_argument(),
	let path := l[1]
	in (l << 1,
		try
			(case left(opt, 3)
				({"-xe"} eload(path),
				any load(path)),
			shrink(l, 0)) //<sb> the script have its own option handling
		catch any
			(print_exception(),
			exit(1)),
		exit(0))]



NO_DEBUG_METHOD:list[method] := list<method>()

(inlineok?(eof? @ port, "lambda[(p:port),eof_port?(p)]"))

(#if compiler.loading?
	(if isfile?(getenv("_") /- "init.cl")
		try load(getenv("_") /- "init.cl")
		catch any none))

