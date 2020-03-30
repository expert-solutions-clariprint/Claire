//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| reader.cl                                                   |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+

// ---------------------------------------------------------------------
// Contents:
//   Part 1: the reader object
//   Part 2: lexical analysis
//   Part 3: reading structures	
//   Part 4: Variable Handling
// ---------------------------------------------------------------------


// **********************************************************************
// *   Part 1: The reader object                                        *
// **********************************************************************

// global definitions
delimiter <: global_variable()

arrow:any :: keyword(name = symbol!("->"))
(put(name(arrow), arrow))

triangle:any :: (keyword(name = symbol!("<:")))
// *arrow*:boolean :: false


// here we define the basic keywords
reserved_keyword <: keyword()

else :: reserved_keyword()
for :: reserved_keyword()
claire/ffor :: reserved_keyword() //<sb> v3.3.33 ffor
case :: reserved_keyword()
while :: reserved_keyword()
until :: reserved_keyword()
let :: reserved_keyword()
when :: reserved_keyword()
try :: reserved_keyword()
if :: reserved_keyword()
Zif :: reserved_keyword()
branch :: reserved_keyword()

keyword?(x:any) : boolean -> (x % reserved_keyword)

forall :: keyword()
//none :: keyword()
None :: keyword()
:= :: keyword()
: :: keyword()
catch :: keyword()
in :: keyword()
claire/by :: keyword() //<sb> v3.3.33 ffor
as :: keyword()
:: :: keyword()
printf :: keyword()
assert :: keyword()
return :: keyword()
break :: keyword()
trace :: keyword()
exists :: keyword()
some :: keyword()
=> :: keyword()
? :: keyword()
rule :: keyword()
quote :: keyword()
claire/inspect :: property()
claire/known! :: property()



// the meta_class of the reader --------------------------------------
// The key values are placed in indexed so that they can be changed (eof ...).
// The slot *internal* is used to give addresses to lexical variables.
// The function next reads a character and places it in the slot first.
//
meta_reader <: thing(source:string,
                     s_index:integer = 0,
                     fromp:port = stdin,
                     nb_line:integer,
                     external:string = "toplevel",
                     index:integer,
                     last_form:any,              // v3.3: replaces LastExpRead
                     maxstack:integer,
                     toplevel:boolean = true,
                     eof:integer, space:integer, tab:integer, bracket:any,
                     paren:any, comma:any, curly:any,
                     last_arrow:boolean = false,     // v3.3                     
                     s_properties:set[property] = Id(reader.s_properties),
                     cascade?:boolean = true, //<sb> add_module iterates parts
                     wcl?:boolean = false) //<sb> wcl


//<sb> cache of symbol and the location of their definitions
IDENTS:list := list<list>()


//<sb> used by #! scripts to check weither the current line is the first
get_lines(r:meta_reader) : integer ->
	(case r.fromp
		(line_counter (1 + read_lines(r.fromp)),
		any 0))

// closing brace as a CLAIRE entity
next(r:meta_reader) : integer ->
	(let c := externC("((CL_INT) r->fromp->getNext())",integer)
	in (r.nb_line := get_lines(r), c))
firstc(r:meta_reader) : integer -> externC("r->fromp->firstc",integer)

stop?(n:integer) : any -> (n = #/, | n = #/) | n = #/] | n = #/}) 

AND:any :: &
OR:any :: mClaire/new!(delimiter, symbol!("|", claire))

// sugar in file
;Declarations:set[property] :: Id(Declarations)

// this is used to keep comments when translating CLAIRE to another language
;LastExpRead:any := unknown                     // used to attach comments to exps

//matchWcl? :: property(open = 3) //<sb> wcl
//readWcl :: property(open = 3) //<sb> wcl

// read the next unit (definition, block or expression)
//
nextunit(r:meta_reader) : any
 -> let n := skipc(r) in
      (if (n = eof(r)) (next(r), EOF)    //<FXJ+NM> was: eof
       else if wcl_start?(r, n) read_top_wcl(r) //<sb> wcl
       else if (n = #/[) let z := nexte(cnext(r)) in nextdefinition(r,z,nexte(r),true)
       else if (n = #/() (if toplevel(r) nexts(r, none)
                          else readblock(r, nexte(cnext(r)), #/)))
       else if (n = #/`) Quote(arg = nextunit(cnext(r)))
       else if (n = #/;)
          (while (firstc(r) != eof(r) & firstc(r) != integer!('\n')) next(r),
           if (firstc(r) = eof(r)) EOF    //<FXJ+NM> was: eof
           else (next(r), nextunit(r)))
       else let x := (if toplevel(r) nexts(r, none) else nextexp(r,true)) in
           (if (toplevel(r) & (case x (Assign (var(x) % Vardef))))
               Defobj(ident = mClaire/pname(var(x)), arg = global_variable,
                      args = list(Call(=, list(range, 
                                               extract_type(range(var(x))))),
                                  Call(=, list(value, arg(x)))))
            else if (x % string) x
            else if (case x (Call (x.selector % r.s_properties &               // v3.3
                                   forall(y in x.args | not(y % Vardef)))))
              let z := (x as Call), a := z.args[1] in
                 (if (z.selector = begin & a % unbound_symbol) z.args[1] := string!(extract_symbol(a)),
                  if (z.selector = end & a % module)  z.args[1] := claire,
                  x)
            else if not(toplevel(r) | x % Assert) nextdefinition(r,x,nexte(r),false)
            else x))


// read the next statement & stops at the keyword e or at a delimiter
// the keyword has been read but not the delimiter, so we know which case
// by testing stop?(first(r))
// Note: it actually reads a fragment
//
nexts(r:meta_reader, e:keyword) : any
 -> let n := skipc(r) in
      (if (n = eof(r)) (next(r), EOF)   //<FXJ+NM> was: eof
       else if (n = #/[) let z := nexte(cnext(r)) in nextdefinition(r,z,nexte(r),true)
       else if (e = None) nexte(r)
       else let x := nexte(r) in
              (if keyword?(x) nextstruct(r, x, e)
               else if (e = none & (case x (Call (x.selector % r.s_properties)))) x
               else if (toplevel(r) & firstc(r) = integer!('\n'))
               		loopexp(r, x, e, false)
               else if wcl_start?(r, skipc(r)) (unget(r.fromp, '>'), x) //<sb> wcl
               else loopexp(r, x, e, false)))


[leaf_wcl_intruction?(self:any) : boolean ->
 	case self
      (Instruction case self
            (Construct leaf_wcl_intruction?(last(self.args)),
             Definition false,
			 Call_wcl false,
			 Princ_wcl true,
             Call_method leaf_wcl_intruction?(last(self.args)),
             Call_slot leaf_wcl_intruction?(self.arg),
             Call_table leaf_wcl_intruction?(self.arg),
             Call_array leaf_wcl_intruction?(self.arg),
             Update leaf_wcl_intruction?(self.value),
             Call leaf_wcl_intruction?(self.args),
             If (if self.iClaire/other leaf_wcl_intruction?(self.iClaire/other)
                 else leaf_wcl_intruction?(get(arg, self))),
             Do (if self.args
             		(leaf_wcl_intruction?(last(self.args)) |
             			(length(self.args) > 1 &
             				last(self.args) = none &
             					self.args[length(self.args) - 1] % (Princ_wcl U Call_wcl)))
             	else false),
             Iteration leaf_wcl_intruction?(self.arg),
             Ffor leaf_wcl_intruction?(self.arg),
             Let leaf_wcl_intruction?(self.arg),
             Case leaf_wcl_intruction?(self.args),
             While leaf_wcl_intruction?(self.arg),
             Handle leaf_wcl_intruction?(self.other),
             any false),
       any false)]
	
[head_wcl_intruction?(self:any) : boolean ->
 	case self
      (Instruction case self
            (Princ_wcl true,
             Do (if self.args head_wcl_intruction?(self.args[1])
             	else false),
             any false),
       any false)]
	

// loops until the right expression is built (ends with e ',', '}' or ')')
//
loopexp(r:meta_reader, x:any, e:keyword, loop:boolean) : any
 -> (if (toplevel(r) & e = none & findeol(r)) x
    else if (x = ?) Call(inspect_toplevel, list(nexte(r)))
    else if (skipc(r) = #/:)
       let y := nexte(cnext(r)) in
         (if (y = =) loopexp(r, combine(x, :=, nexte(r)), e, true)
          else if (y = :) nextinst(r, x)    // AHA (v3.0.05)
          else if operation?(y) extended_operator(y,x,loopexp(r, nexte(r), e, false)) // v3.3.32
          else if (x % Call)
             let w := nexte(r) in
               (if (w = =>) r.last_arrow := true                  // v3.3.00
                else if not(w = arrow | w = :=) 
                  Serror(149, "Wrong keyword (~S) after ~S",list(w,y)),
                nextmethod(r,x,y,(w = :=),false,(w = =>)))
          else Serror(150, "Illegal use of :~S after ~S", list(y, x)))
    else if wcl_start?(r, firstc(r)) (unget(r.fromp, '>'), x)
    else let y := nexte(r) in
           (if (y = e | (y = => & e = arrow))
               (if (y != e) r.last_arrow := true,                   // v3.3
                if stop?(firstc(r))
                   Serror(151, "~S not allowed after ~S\n",
                          list(char!(firstc(r)), e))
                else x)
            else if (y = triangle | y = arrow | y = : | y = :: | y = =>)
                nextdefinition(r,x,y,false)
            else if (y % delimiter & stop?(firstc(r))) x
            else if operation?(y)
               (if loop loopexp(r, combine(x, y, nexte(r)), e, true)
                else loopexp(r, combine!(x, y, nexte(r)), e, true))
            else (//[3] test leaf x=~S, y=~S // x, y,
            	if (y = ?) x
            	else if leaf_wcl_intruction?(x) Do!(x, y)
            	else if head_wcl_intruction?(y) Do!(x, y)
            	else Serror(152, "Separation missing between ~S \nand ~S [~S?]",
                        list(x, y, e)))))


// this is the special form for x :op y - new in v3.3.32
extended_operator(p:property,x:any,y:any) : any
  -> (case x (Call let r := (if (x.selector = nth) x.args[2] else x.args[1]),
                       v := Variable(mClaire/pname = gensym()),
                       %b := bind!(reader, v),
                       x2 := (if (x.selector = nth) Call(nth,list(x.args[1],v))
                              else Call(x.selector,list(v))),
                       res :=
							 (if (r % Call)
								Let(var = v, value = r, arg = combine(x2, :=, combine(x2,p,y)))
							  else combine(x, :=, combine(x, p, y)))
					in (unbind!(reader, %b),
						res),
              any combine(x, :=, combine(x, p, y))))



// reading the next compact expression - comments are ignored but they can
// be attached to the last read expression
//
nexte(r:meta_reader) : any
 -> let x := nextexp(r,false) in (if (x % Instruction) r.last_form := x, x)     // v3.3


[add_ident(s:string) : void ->
	let (f,l,o) := Core/get_location(reader.fromp)
	in let loc := list<any>(s,f,l)
	in (if (s = "." | s = "[") loc add (o - 1 - length(s))
		else loc add (o - 2 - length(s)),
		loc add length(s),
		IDENTS add loc)]

//<sb> fill the cache of symbol location
Kernel/read_ident(r:meta_reader) : any ->
	let x := Kernel/read_ident(r.fromp)
	in (if (x = while) add_ident("while")
		else case x
			({catch} add_ident("catch"),
			(symbol U unbound_symbol U property U class)
				(add_ident(Language/extract_symbol(x).name),
				if (Language/CAN_INIT_LOCATION? & x % unbound_symbol)
					Language/init_location(x))), //<sb> force unbound symbols to be localized
		x)

// reading the next compact expression/ same
//
nextexp(r:meta_reader,str:boolean) : any
 -> (let n:integer := skipc(r) in
      (if (n = #/)) paren(r)
       else if (n = #/}) curly(r)
       else if (n = #/]) bracket(r)
       else if (n = #/|) (next(r), OR)
       else if (n = #/,) comma(r)
       else if (n = eof(r)) Serror(153, "Eof inside an expression", nil)
       else if (n = #/;)
          (while (firstc(r) != eof(r) & firstc(r) != integer!('\n')) next(r),
           if (firstc(r) = eof(r)) EOF   //<FXJ+NM> was: eof
           else (next(r), nexte(r)))
       else if (n = #/#) read_escape(r)
       else if (n = #/`) Quote(arg = nexte(cnext(r)))
       else if wcl_start?(r, n) read_wcl(r)   //<sb> wcl
       else let y:any := unknown,
                x := (if (n = #/") Kernel/read_string(cnext(r).fromp)  ;"
                      else if (n = #/() readblock(r,nexte(cnext(r)), #/))
                      else if (n >= #/0 & n <= #/9) Kernel/read_number(r.fromp)
                      else if (n = #/{) readset(r, nexte(cnext(r)))
                      else (y := Kernel/read_ident(r),
                            if (y % string) y else nexti(r, y))) in
              (if (y % string)
                  (if extended_comment?(r,y as string)
				      extended_comment!(r,y as string)
				   else if str y
				   else if wcl_start?(r, skipc(r))
				   		(unget(r.fromp, ">"),
				   		?)
                   else nexte(r))         ; read a comment
               else (while (firstc(r) = #/[ | firstc(r) = #/. | firstc(r) = #/<)
	              (if (firstc(r) = #/<)
                        let y := nexte(cnext(r)) in
                          (if (x % class & firstc(r) = integer!('>'))
                            (cnext(r),
                             x := extract_class_call(x,list(Call(=,list(of,y)))),
                             x := nexti(r,x))
                           else Serror(154, "~S<~S not allowed",list(x,y)))
                       else if (firstc(r) = #/[)
                        (add_ident("["),
						let l := nextseq(cnext(r), #/]) in
                         x := (if (x % class & x != type & l)
                                  extract_class_call(x,l)
                               else (Call!(nth, x cons l))))
                       else (add_ident("."),
							let y := Kernel/read_ident(cnext(r).fromp),
                                p := make_a_property(y) in
                         (x := Call+(selector = p, args = list(x)),
                          if (p.reified = true) x := Call!( read, list(x))
						  else x))),
                     x))))

// reads a compact expression that starts with an ident
//
nexti(r:meta_reader, val:any) : any
 -> (if (firstc(r) = #/()
      (if (val % {exists, forall, some})
          let v :=  extract_variable(nexte(cnext(r))), %a2 := nexte(r),
		      %a3:any := any in
            (if (%a2 = in) (%a3 := nexte(r),
			    if (nexte(r) != OR)
                              Serror(155, "Missing | in exists / forall",nil))
             else if (%a2 = comma(r)) cnext(r)
             else Serror(156, "Wrong use of exists(~S ~S ...",list(v, %a2)),
             Exists( var = v, set_arg  = %a3,
                     arg = (let %bind := bind!(r,v), x := nexts!(r,#/)) in
                              (unbind!(r,%bind), x)),
                     other = (if (val = forall) true else if (val = exists) false else unknown)))
        else if (val = rule) (cnext(r), val)
        else readcall(r, val, unknown))
    else if (val = list & firstc(r) = #/{)
       let s := readset(r, nexte(cnext(r))) in
         case s
          (Image (put(isa,s,Collect), s),
           Select (put(isa,s,Lselect), s),
           any Serror(157, "~S cannot follow list{", list(s)))
    else if ((case val (Call (val.selector = nth & val.args[1] = list),
                        any false)) & firstc(r) = #/{)
       let s := readset(r, nexte(cnext(r))),
           x := extract_of_type(val as Call) in
         case s
          (Image (put(isa,s,Collect), put(of,s,x), s),
           Select (put(isa,s,Lselect), put(of,s,x), s),
           any Serror(157, "~S cannot follow list{", list(s)))
    else if ((case val (Call (val.selector = nth & val.args[1] = set),
                        any false)) & firstc(r) = #/{)
       let s := readset(r, nexte(cnext(r))),
           x := extract_of_type(val as Call) in
         case s
          (Image (put(of,s,x), s),
           Select (put(of,s,x), s),
           any Serror(157, "~S cannot follow list{", list(s)))
    else if (firstc(r) = #/:) nextvariable(r, val)
    else if (firstc(r) = #/@)
       let %a1 := Kernel/read_ident(cnext(r)) in
         (if not(%a1 % class)
             Serror(158, "Wrong type in call ~S@~S", list(val, %a1)),
          if (firstc(r) = #/() readcall(r, val, %a1)
          else Serror(159, "Missing ( after ~S@~S", list(val, %a1)))
    else val) 

// we have read the escape character #
//
read_escape(r:meta_reader) : any
 -> (if (firstc(cnext(r)) = #//)
       let val := firstc(cnext(r))
       in (next(r),
          Call(selector = integer!, args = list(char!(val))))
    else if (firstc(r) = #/')
       make_function(string!(extract_symbol(Kernel/read_ident(cnext(r)))))
    else if ((firstc(r) = #/i) & (firstc(cnext(r)) = #/f))
       (next(r), Zif)
    else if (get_lines(r) = 1 & firstc(r) = #/!) //<sb> allow claire file to be executed under unix
    	(while (firstc(cnext(r)) != integer!('\n') & firstc(r) != r.eof) none, // skip line
    	"")
    else Serror(160, "Wrong use of special char #",nil))
        

nextvariable(r:meta_reader, val:any) : any
 -> (if (val = <) (skipc(r), triangle)
     else Vardef(mClaire/pname = extract_symbol(val),
                 range = nexte(cnext(r))) )

// reads an expression, then the exact keyword e
//
nexts!(r:meta_reader, e:keyword) : any
 -> (let x := nexts(r, e) in
      (if not(stop?(firstc(r))) x
       else Serror(161, "Missing keyword ~S after ~S", list(e, x))))

// reads an expression, then the exact keyword e
//
nexte!(r:meta_reader, e:keyword) : any
 -> (let x := nexte(r) in
      (if (nexte(r) = e) x
       else Serror(161, "Missing keyword ~S after ~S", list(e, x))))

// ... exact separator
nexts!(r:meta_reader, e:integer) : any
 -> (let x := nexts(r, none) in
      (if (firstc(r) = e) (cnext(r), x)
       else Serror(162, "Missing separator ~S after ~S", list(char!(e), x))))

// ... keyword e or separator n. DOES NOT SKIP the last character
//
nexts!(r:meta_reader, e:keyword, n:integer) : any
 -> (let x := nexts(r, e) in
      (if (firstc(r) = n | not(stop?(firstc(r)))) x
       else Serror(163, "Wrong separator ~S after ~S", list(char!(firstc(r)), x))))

// checks if s is an extended comment
//
extended_comment?(r:meta_reader,s:string) : boolean
  -> (let n := get(s,']') in
        (if (s[1] = EOS | s[1] != '[' | n = 0) false // v0.01
         else forall(i in (2 .. n) | s[n] != '[')))

// produce the equivalent extended comment
//
extended_comment!(r:meta_reader,s:string) : any
  -> (let i := get(s,']'),
          k := substring(s,"//",true),
          m := length(s),
          col := color(0),			//<sb> ensure color mode is 0
          cx := firstc(r) in         // CL_INT code for the last char
       (print_in_string(),
	    while useless_c(integer!(s[m])) m :- 1,
		if (s[m] = ',') (cx := #/, , m :- 1),
		if (k = 0) k := m + 1,
        if (i = 3 & s[i - 1] = '?')
           printf("assert(~I)", for j in ((i + 2) .. m) princ(s[j]))
        else printf("trace(~I,\"~I\\n\"~I))",
               for j in (2 .. (i - 1)) princ(s[j]),
               for j in ((i + 2) .. (k - 1)) princ(s[j]),
               (if (k + 3 <= m) (princ(","),
	        for j in ((k + 3) .. m) princ(s[j])))),
		let isWcl? := r.wcl?, s2 := (r.wcl? := false, read(end_of_string())) in //<sb> wcl
		   (r.wcl? := isWcl?,
           flush(reader.fromp,cx),          // push back the int
           color(col),
           s2)))


