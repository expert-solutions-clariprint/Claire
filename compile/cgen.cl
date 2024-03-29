//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| cgen.cl,                                                    |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+

// -------------------------------------------------------------------
// Contents
//      Part 1: definition of the C++ code producer
//      Part 2: utilities for file generation
//      Part 3: interface declarations
//      Part 4: use of language dependent patterns (macros)
//      Part 5: System compiling methods
// -------------------------------------------------------------------

// renaming philosophy:
// keyword => become allcaps and if not good enough, add _CL_
// class => add Claire

// *******************************************************************
// *       Part 1: definition of the C++ code producer               *
// *******************************************************************

// definition of the class
c_producer <: producer(bad_names:list[symbol],        // avoid generating !
                       good_names:list[symbol])       // replacements (same order)


// definition of the instance
C++PRODUCER :: c_producer(
  open_comparators = list(<, >, >=, <=),
  open_operators = list(+,-,*,/,>>),
  extension = ".cpp",
  comment = "C++",
  bad_names = list(
    symbol!("do"), symbol!("if"), symbol!("and"), symbol!("or"),symbol!("not"),
    symbol!("printf"), symbol!("void"), Optimize/Pattern.name,
    symbol!("exception"), symbol!("return"), symbol!("new"),
    symbol!("class"), symbol!("private"), symbol!("operator"),
    symbol!("default"), symbol!("Handle"), symbol!("import"), symbol!("freeable_object"),
    symbol!("catch"), symbol!("stdout"), symbol!("stdin"), symbol!("stderr"),
    symbol!("break"), symbol!("char"), symbol!("interface"), symbol!("EOF"),
    symbol!("relation"), symbol!("System"), symbol!("object"),
    symbol!("port"),symbol!("socket"),
    symbol!("delete"), symbol!("boolean"), symbol!("function"),
    symbol!("type"), symbol!("system_thing"), symbol!("environment"),
    symbol!("abstract"), symbol!("final"), symbol!("system_object"),
    symbol!("NEW_ALLOC"), symbol!("BAG_UPDATE"), symbol!("SLOT_UPDATE"),
    symbol!("RETURN_ARG"), symbol!("SAFE_RESULT"),symbol!("SAFE_GC"),
    symbol!("collection"),symbol!("SIG_DFL"),symbol!("SIG_IGN"),
	symbol!("SIGHUP"),symbol!("SIGINT"),symbol!("SIGQUIT"),symbol!("SIGILL"),
	symbol!("SIGTRAP"),symbol!("SIGABRT"),symbol!("SIGIOT"),symbol!("SIGEMT"),
	symbol!("SIGFPE"),symbol!("SIGKILL"),symbol!("SIGBUS"),symbol!("SIGSEGV"),
	symbol!("SIGSYS"),symbol!("SIGPIPE"),symbol!("SIGALRM"),symbol!("SIGTERM"),
	symbol!("SIGURG"),symbol!("SIGSTOP"),symbol!("SIGTSTP"),symbol!("SIGCONT"),
	symbol!("SIGCHLD"),symbol!("SIGTTIN"),symbol!("SIGTTOU"),symbol!("SIGIO"),
	symbol!("SIGXCPU"),symbol!("SIGXFSZ"),symbol!("SIGVTALRM"),symbol!("SIGPROF"),
	symbol!("SIGWINCH"),symbol!("SIGINFO"),symbol!("SIGUSR1"),symbol!("SIGUSR2"),
	symbol!("ITIMER_REAL"),symbol!("ITIMER_VIRTUAL"),symbol!("ITIMER_PROF"),
	symbol!("F_SETOWN"),symbol!("F_SETFL"),symbol!("F_GETFL"),symbol!("FASYNC"),
	symbol!("WRUNNING"),symbol!("WEXITED"),symbol!("WSIGNALED"),symbol!("WSTOPPED"),
	symbol!("register"),symbol!("error"),symbol!("pipe"),symbol!("sizeof"),symbol!("do")),
 good_names = list(
    symbol!("DO"),symbol!("IF"),symbol!("ClaireAnd"),symbol!("ClaireOr"),symbol!("NOT"),
    symbol!("PRINTF"), symbol!("ClaireVoid"), symbol!("ClairePattern"),
    symbol!("ClaireException"), symbol!("RETURN"), symbol!("NEW"),
    symbol!("ClaireClass"), symbol!("PRIVATE"), symbol!("ClaireOperator"),
    symbol!("DEFAULT"), symbol!("ClaireHandle"), symbol!("ClaireImport"), symbol!("FreeableObject"),
    symbol!("CATCH"), symbol!("cl_stdout"), symbol!("cl_stdin"),  symbol!("cl_stderr"),
    symbol!("BREAK"), symbol!("ClaireChar"), symbol!("ClaireInterface"), symbol!("_eof"),
    symbol!("ClaireRelation"),symbol!("Core"),symbol!("ClaireObject"),
    symbol!("PortObject"),symbol!("cl_socket"),
    symbol!("_delete"), symbol!("ClaireBoolean"), symbol!("ClaireFunction"),
    symbol!("ClaireType"), symbol!("SystemThing"), symbol!("ClaireEnvironment"),
    symbol!("ABSTRACT"), symbol!("FINAL"),symbol!("SystemObject"),
    symbol!("_NEW_ALLOC"), symbol!("_BAG_UPDATE"), symbol!("_SLOT_UPDATE"),
    symbol!("_RETURN_ARG"), symbol!("_SAFE_RESULT"),symbol!("_SAFE_GC"),
    symbol!("ClaireCollection"),symbol!("CL_SIG_DFL"),symbol!("CL_SIG_IGN"),
	symbol!("CL_SIGHUP"),symbol!("CL_SIGINT"),symbol!("CL_SIGQUIT"),symbol!("CL_SIGILL"),
	symbol!("CL_SIGTRAP"),symbol!("CL_SIGABRT"),symbol!("CL_SIGIOT"),symbol!("CL_SIGEMT"),
	symbol!("CL_SIGFPE"),symbol!("CL_SIGKILL"),symbol!("CL_SIGBUS"),symbol!("CL_SIGSEGV"),
	symbol!("CL_SIGSYS"),symbol!("CL_SIGPIPE"),symbol!("CL_SIGALRM"),symbol!("CL_SIGTERM"),
	symbol!("CL_SIGURG"),symbol!("CL_SIGSTOP"),symbol!("CL_SIGTSTP"),symbol!("CL_SIGCONT"),
	symbol!("CL_SIGCHLD"),symbol!("CL_SIGTTIN"),symbol!("CL_SIGTTOU"),symbol!("CL_SIGIO"),
	symbol!("CL_SIGXCPU"),symbol!("CL_SIGXFSZ"),symbol!("CL_SIGVTALRM"),symbol!("CL_SIGPROF"),
	symbol!("CL_SIGWINCH"),symbol!("CL_SIGINFO"),symbol!("CL_SIGUSR1"),symbol!("CL_SIGUSR2"),
	symbol!("CL_ITIMER_REAL"),symbol!("CL_ITIMER_VIRTUAL"),symbol!("CL_ITIMER_PROF"),
	symbol!("CL_F_SETOWN"),symbol!("CL_F_SETFL"),symbol!("CL_F_GETFL"),symbol!("CL_FASYNC"),
	symbol!("CL_WRUNNING"),symbol!("CL_WEXITED"),symbol!("CL_WSIGNALED"),symbol!("CL_WSTOPPED"),
	symbol!("REGISTER"),symbol!("ClaireError"),symbol!("cl_pipe"),symbol!("cl_sizeof"),symbol!("cldo")),
 // a list of interface
 interfaces = list(string, "char *",
 					char*, "char*",
 					char, "ClaireChar *",
 					Core/FILE*, "FILE*",
                   float, "double ",
                   array, "OID *",
                   function, "OID (*)()"))


// use this producer
(PRODUCER := C++PRODUCER)

// makes an ident (string) from a variable's name
c_string(c:c_producer, self:Variable) : string
 -> (if (compiler.naming = 2) ("v" /+ string!(integer!(self.pname)))
     else (Core/print_in_string(), ident(c,self.pname), Core/end_of_string()))

c_string(c:c_producer, self:symbol) : string
 -> (Core/print_in_string(), ident(c,self), Core/end_of_string())

// to remove
string!(c:c_producer, self:Variable) : string
 -> (if (compiler.naming = 2) ("v" /+ string!(integer!(self.pname)))
     else (Core/print_in_string(), ident(c,self.pname), Core/end_of_string()))

string!(c:c_producer, self:symbol) : string
 -> (Core/print_in_string(), ident(c,self), Core/end_of_string())

// print a symbol for a variable
[ident(c:c_producer,v:Variable) : void
 ->  if (compiler.naming = 2) princ("v" /+ string!(integer!(v.pname)))
     else let s := v.pname, n := get(c.bad_names, s) in
       (if (n = 0)
       		(if (length(s.name) = 2 & s.name[1] = '_') //<sb> some compiler don't like 2 chars names starting by an underscore
       			princ("us"),
       		c_princ(string!(s)))
        else c_princ@symbol(c.good_names[n])) ]


// print a symbol for the structure definition
[ident(c:c_producer,s:symbol) : void
 -> let n := get(c.bad_names, s) in
       (if (n = 0) //c_princ(string!(s))
       		(if (length(s.name) = 2 & s.name[1] = '_') //<sb> some compiler don't like 2 chars names starting by an underscore
       			princ("us"),
       		c_princ(string!(s)))
        else c_princ@symbol(c.good_names[n])) ]


// v3.3.14 - from 2.5 !!!
// a class name is printed with the module identifier
class_princ(c:c_producer,self:class) : void
 -> (if (module!(self.name) != claire)
        (ident(c,(module!(self.name).name)), princ("_")),
     ident(c,self.name))



// code production for basic expression
[produce(c:c_producer,x:any) : void
 -> case x
      (function printf("_function_(~I,~I)", c_princ(x), print(string!(x))),
       char printf("_char_(((unsigned char)~S))", x),
       environment princ("ClEnv"),
       string printf("((char*)~S)", x),
       global_variable  globalVar(c,x),
       boolean  (if x princ("CTRUE") else princ("CFALSE")),
       symbol printf("symbol::make(~S,~I,~I)",string!(x),ident(module!(x).name),
                      ident(defined(x).name)),     // v3.2.38 thanks to FXJ
       class (if (x = import) princ("Kernel._cl_import")    // v3.3.22  
              else printf("~I._~I",ident(c,defined(x.name).name),
                             c_princ(string!(x.name)))),
       reserved_keyword printf("~I._cl_~I",ident(c,defined(x.name).name),
                               c_princ(string!(x.name))),
       thing  (if (x % module) printf("~I.it",ident(c,x.name))
               else printf("~I.~I",ident(c,defined(x.name).name),ident(x.name))),
       any princ("CNULL")) ]


// v3.3 : new ! a global variable contains the native value
[globalVar(c:c_producer,x:global_variable) : void
  ->  (if (x.range = {} & x.value % integer) printf("(OID)(~S)", x.value) //<sb> new OID
       else printf("~I.~I~I", ident(c,defined(x.name).name),
                              ident(x.name),
                              (if not(nativeVar?(x)) princ("->value")))) ]


// we make this a separate method because Java is more difficult
[stat_exp(c:c_producer,self:any,loop:any) : void
  -> if (self % to_C) stat_exp(c, (self as to_C).arg, loop)
     else if (self % to_CL) stat_exp(c, (self as to_CL).arg, loop)
     else if designated?(self)  princ(";")
     else printf("~I;~I", expression(self, loop), breakline()) ]

// *******************************************************************
// *       Part 2: utilities for file generation                     *
// *******************************************************************

// generate a namespace definition (the class)
// this creates the begining of the definition (to be filled)
[namespace!(c:c_producer,m:module) : void
 -> printf("\n\n// namespace class for ~S \n",m),
    printf("class CL_EXPORT ~IClass: public NameSpace {\npublic:\n",ident(c,m.name)) ]

// ... ends the previous definition and introduces the associated identifier
[module!(c:c_producer,m:module) : void
  -> printf("\n\n// module definition \n"),
     printf(" void metaLoad();};\n\n"),
     printf("extern CL_EXPORT ~IClass ~I;\n",ident(c,m.name),ident(c,m.name)),
/*     let m2 := m.part_of in
       while (not(m2.made_of) & m2 != claire)
         (printf("extern CL_EXPORT NameSpace ~I;\n",ident(c,m2.name)),
          m2 := m2.part_of) ]*/

    let m1 := m, m2 := m1.part_of in
       while (not(m2.made_of) & m2 != claire & m2.parts[1] = m1)
         (printf("extern CL_EXPORT NameSpace ~I;\n",ident(PRODUCER,m2.name)),
          m2 := m2.part_of, m1 := m2) ]


[declare(c:c_producer,p:property) : void
 -> breakline(),
    printf("~I = ~A::make(~S,~I~I~I);~I",expression(p, nil),
           (if (p % operation) "operation" else "property"),
           string!(p.name),
           (if (p.open != 1 | p.mClaire/dispatcher > 0 )               // 1 is the default value for open
               (expression(p.open, {}),princ(","))),
           expression(module!(p.name),nil),
           (if (p % operation) printf(",~A",p.precedence)
            else if (p.mClaire/dispatcher > 0)
               printf(",~I,~A",
                      expression(p.domain,nil),
                      p.mClaire/dispatcher)),
			(if p.reified printf(" ~I->reified = CTRUE;", expression(p, nil)))) ] //<sb> compile the reify status of a property

// ..
[start_module_interface(c:c_producer, self:module) : void
 -> let %interface:string := (compiler.headers_dir /+ ((*fs* /+ c_string(c,self.name)) /+ ".h")) in
       (OPT.cinterface := fopen(%interface, "w"),         // v3.0.4 -> change directory
        use_as_output(OPT.cinterface),
        printf("// interface definition for module ~S\n",self),
        printf("#ifndef CLAIREH_~I\n#define CLAIREH_~I\n", ident(self), ident(self)),
        for x in compiler.headers
           (if match_wildcard?(x,"*.*") printf("#include ~I\n", (if (left(x,1) = "<") princ(x) else print(x))) //<sb> allow .h extension in additional headers
           else printf("#include \"~A.h\"\n", x)),
       use_as_output(stdout)) ]

// v3.2.44
[end_module_interface(c:c_producer, self:module) : void -> printf("\n#endif\n")]
    

// ends the module definition and adds a } to each opened class file
[generate_end_file(j:c_producer,m:module) : void
  -> close_block(),       // end of module definition
     putc("\n"[1],OPT.outfile), //<sb> ensure new line at end of file - prevent C++ compiler warning
     fclose(OPT.outfile),
     // print right bracket in the end of each class definition
     for c in {c in OPT.objects | c % class}
       let p := fopen(compiler.source /+ *fs* /+ c_string(j,c.name) /+ j.extension,"a") in
          (use_as_output(p),
           close_block(),
           putc("\n"[1],p), //<sb> ensure new line at end of file - prevent C++ compiler warning
           fclose(p)) ]


// v3.2.44 : make this part dependent on the producer
[generate_classes(j:c_producer, s:string, m:module) : void
 -> //printf("\n\n~AClass ~A;\n\n",s,s),
 	printf("\n\nCL_EXPORT ~IClass ~I;\n\n",ident(j,m.name),ident(j,m.name)),
    let m1 := m, m2 := m1.part_of in
       while (not(m2.made_of) & m2 != claire & m2.parts[1] = m1)
         (printf("CL_EXPORT NameSpace ~I;\n",ident(PRODUCER,m2.name)),
          m2 := m2.part_of, m1 := m2) ]

// MOVE
[generate_start_file(c:c_producer,m:module) : void
  -> //[2] ++++ Creating the file ~A.cpp // c_string(c,m.name),
     start_file(string!(m.name),m),
     OPT.level := 0,
     printf("/* class file for module ~S */",m),
     breakline(),
     breakline(),
     printf("public class ~I extends NameSpace",ident(c,m.name)),
     new_block() ]


[generate_meta_load(c:c_producer,m:module) : void
  -> printf("void ~IClass::metaLoad() ",ident(c,m.name)),
     new_block(),
     breakline(),
     printf("~IClEnv->module_I = it;\n",breakline()) ] //<sb> rm GC_BIND - protect optimized vars

// start the produced C file
// Put the reference to the claire C header, and some useful comments
[start_file(s:string,m:module) : any
 ->  use_as_output(OPT.outfile),
     let empty? := fsize(Core/get_disk_file(OPT.outfile).Core/file_path) = 0.0
     in (printf("/***** CLAIRE Compilation of file ~A.cl \n         [version ~A / safety ~S] *****/\n\n",
              s, release(),compiler.safety),
       if empty?
         (printf("#include <claire.h>\n"),
         printf("#include <Kernel.h>\n"),
         for x in Reader/add_modules(list(m))
           (for w in { s in x.uses | s % string}
              printf("#include <~A.h>\n", w),
            if (x = m)
             (printf("\n#if defined(CLPC) && !defined(CLPCNODLL)\n"),
             printf("  #undef CL_EXPORT\n"),
             printf("  #define CL_EXPORT __declspec(dllexport)\n"),
             printf("#endif\n")),
           if x.made_of printf("#include <~I.h>\n", ident(x.name)),
           if (x = m)
             (printf("\n#if defined(CLPC) && !defined(CLPCNODLL)\n"),
             printf("  #undef CL_EXPORT\n"),
             printf("  #define CL_EXPORT __declspec(dllimport)\n"),
             printf("#endif\n"))),
         if OPT.cfile printf("#include <~A.h>\n", OPT.cfile),
         printf("\n#if defined(CLPC) && !defined(CLPCNODLL)\n"),
         printf("  #undef CL_EXPORT\n"),
         if OPT.cfile printf("  #define CL_EXPORT\n")
         else printf("  #define CL_EXPORT __declspec(dllexport)\n"),
         printf("#endif\n")),
       use_as_output(stdout))]

// define a new typed variable named v
// v3.0.72  fill with a default value !
[define_variable(c:c_producer,t:class,v:string) : void
  -> printf("~I~A ~I;", interface!(t), v,
              (if (t = integer | t = any) princ("= 0")
               else if (t = float) princ("=0.0"))) ]


[generate_profile(c:c_producer,m:any) : void
 -> if (m % method) get_dependents(m),
    printf("   PRcount *PR_x = PRstart(PRget_property(~I));~I",
             expression( (case m (method m.selector, any fastcall)), nil),
             breakline())  ]

// this part depends on the target language   -  v3.2.44
[generate_interface(c:c_producer,self:module) : void
 -> for x in list{x in OPT.objects | x % class}     // avoid problems with forward !
       printf("\nclass CL_EXPORT ~I;", class_princ(c,x)),  // v3.3.14
    // generate the list of the class structures
    for x in list{x in OPT.objects | x % class }     // prints the class definitions
       printf("\n\nclass CL_EXPORT ~I: public ~I~Ipublic:~I~I~I;", class_princ(c,x),    // v3.3.14
               class_princ(c,x.superclass),                                   // v3.3.14
               (new_block(), breakline()),
               (for y:slot in {s in get_indexed(x) |       // v3.2 take care of overriding
                               forall(s2 in x.superclass.slots | s2.selector != s.selector)}
                 (breakline(),
                  princ("   "),
                  interface!(PRODUCER,psort(y.range)),
                  ident(y.selector.name),
                  princ(";"))),
               methods_interface(PRODUCER,x),
               close_block()),
     for l in OPT.functions     // prints the API methods
       let %f := l[1], %vars := l[2], s := l[3] in
         printf("\nextern CL_EXPORT ~I ~I(~I);", interface!(PRODUCER,s), c_princ(%f),
                typed_args_list(%vars)) ]


// new in v3.3
// produce a native global variable for sorts integer, float and object
// the form is  module.name = value
[global_var_def!(c:c_producer,self:module, x:Let) : void
  -> let %gvar := get(x.value.args[1] as symbol) as global_variable,
         s := getRange(%gvar),
         %update := (x.arg as Do).args[2],  // should be an Update but may be a call ? .. v3.3.04
         %upval := (case %update (Update %update.value,    // Update is easy
                                  (Call U Call_method) %update.args[5],    // v3.3.04/0.08- a bug found by E. Gaudin & FXJ
                                  any error("Design bug: make ~S a public global var !",%gvar))), // hopefully, will never be used
         b:boolean := c_func(%upval),
         varg := build_Variable("V_C", any) in
       (if not(nativeVar?(%gvar)) statement(x,nil,nil)                   // storeable GV use old code pattern ...
        else (if not(b)
              printf("~IOID ~I;~I~I",new_block(),
                               ident(c,varg),
                               breakline(),
                               statement(%upval,c_string(PRODUCER,varg),nil)),
               printf("~I.~I = ~I;~I",
                           ident(c,self.name),
                           ident(c,%gvar.name),
                           (if b to_c(c,%upval,s,nil)
                            else to_c(c,varg, s,nil)),
                           (if not(b) close_block(), breakline())))) ]
       




// a new method (v3.0.55) that returns an abstraction of the gc protection usage:
//    false: does not use to_protect
//    true:  use protection but not on variables within a loop
//    <int>: use protection, but only once on a variable within a loop (i is the index)*
//    100000:  use protection fully
[gc_usage(self:any,loop:boolean) : any
 -> ///[3] \n\n\ngc_usage(~S,~S) // self, loop,
 	case self
      (Instruction case self
            (Construct gc_usage*(self.args,loop),
             Definition true,
             Call_method gc_usage*(self.args,loop),
             Call_slot gc_usage(self.arg,loop),
             Call_table gc_usage(self.arg,loop),
             Call_array gc_usage(self.arg,loop),
             to_C  gc_usage(self.arg,loop),
             to_CL  gc_usage(self.arg,loop),   // v3.2.42
             to_protect gc_or(gc_usage(self.arg,loop),true),
             Update gc_usage(self.value,loop),
             Call gc_usage*(self.args,loop),
             If gc_or(gc_usage(self.test,loop),
                      gc_or(gc_usage(get(arg, self), loop),
                            gc_usage(get(other, self), loop))),
             Do gc_usage*(self.args,loop),
             Iteration gc_or(gc_usage(self.set_arg,loop), gc_usage(self.arg,true)),
             Ffor true, /*gc_or(gc_or(gc_usage(self.set_arg,loop), gc_usage(self.arg,true)),
             			gc_usage(self.forkedby,loop)),*/
             Let let x := get(value,self) in
                      gc_or((if (loop & x % to_protect) true else false),
                            gc_or(gc_usage(x,loop),
                                  gc_usage(self.arg, loop))),
             Assign let x := get(arg,self) in
                      gc_or((if (loop & inner2outer?(x)) true   // v3.3.26 !
                             else false),
                            gc_usage(x,loop)),
             Gassign  gc_usage(self.arg,loop),
             And gc_usage*(self.args,loop),
             Or gc_usage*(self.args,loop),
             Cast gc_usage(self.arg, loop),
             Super gc_usage*(self.args,loop),
             Case gc_usage*(self.args,loop),
             While gc_or(gc_usage(self.arg, true), gc_usage(self.test, loop)),
             Return gc_usage(self.arg, loop),
             Handle gc_or(gc_or(gc_usage(self.arg, loop), gc_usage(self.other, loop)),
                                gc_usage(self.test, loop)),
             any false),
       any false) ]


// combining abstract values
[gc_or(x:any,y:any) : any
  -> if (x = false) y
     else if (x = true) (if (y = false) x else y)
     else if (y % integer) (if (x = y) y else 100000)
     else x]

// apply gc_usage to a list
[gc_usage*(l:list,loop:boolean) : any
  -> let x:any := false in
         (for y in l x := gc_or(x,gc_usage(y,loop)), x) ]



// produce the end statement for the function. self tells if the result
// is needed.
// we also add the debugging unbind if needed.
[protect_result(c:c_producer,s:class,use_gc:boolean,x:any) : string
 -> if (compiler.safety > 5)
       (OPT.protection := false, use_gc := false, OPT.loop_gc := false),
    let s1 := (if (s != void)
                 (if not(OPT.alloc_stack)
					 (if use_gc "GC_UNBIND; POP_SIGNAL; return "
					 else "POP_SIGNAL; return ")
					else
						//<sb> avoid signal handling if stack is used for the result
						// the signal handler could modify the stack
						(if use_gc "GC_UNBIND; return " 
					 	else "return "))
               else if use_gc "GC_UNBIND; POP_SIGNAL;"
               else "POP_SIGNAL;")
     in (OPT.protection := use_gc,
		if (OPT.profile? & (x % method | x = unknown)) "PRend(PR_x);" /+ s1
         else s1)]

// how to declare a function in the interface file and its header in the
// output file
[generate_function_start(c:c_producer,self:lambda,s:class,m:any, %nom:string) : void
 ->  let %dom := (if self.vars self.vars[1].range else any),
         %f := make_function(%nom),
         lv := (if (length(self.vars) = 1 & %dom % {void, environment})  nil       // v3.0.05 was : & not(s = float)
                else self.vars) in
       (update_function_entry(c,%f,lv,s),  // OPT.functions :add list(%f, lv, s),        // register the function in the API list
        use_as_output(OPT.outfile),
        case m (method (if (m.range = float | float % m.domain)                ; <FXJ>: PATCH !
                           generate_float_function(c,m,string!(%f))
                        else if (m.range % tuple)
                           generate_tuple_function(c,m,string!(%f)))),
        generate_regular_function(c,self,%f,s,m,lv)) ]


// regular case
[generate_regular_function(c:c_producer,self:lambda,%f:function,s:class,m:any,lv:list) : void
  -> if (compiler.naming != 2)
       printf("\n// The c++ function for: ~I\n",
               (case m
                 (method printf("~S(~I) [~I]", m.selector,
                                Language/ppvariable(self.vars),
                               (if (compiler.naming = 1) bitvectorSum(status!(m)))),
                  any princ(string!(%f))))),
     printf("CL_EXPORT ~I ~I(~I) ~I~I", interface!(c,s), c_princ(%f), typed_args_list(lv), new_block(),breakline()) ]


// new: make a special signature function (float -> OID) for methods that use
// float in their signature
[generate_float_function(c:c_producer,m:method,%nom:string) : void
 -> let ld := (if (length(m.domain) = 1 & domain!(m) = void) nil else m.domain),
        n := length(ld),
        lv := list{Variable(pname = gensym(),
                            range = (if (x = float) any else x)) | x in ld},
        %nom_ := %nom /+ "_",
        %f := make_function(%nom_),
        %lambda := lambda!(lv,nil),
        s := (if (m.range = float) any else psort(m.range)) in
       (generate_regular_function(c,%lambda, %f, s, m,lv),
        OPT.functions :add list(%f, lv, s),
        if (s != void) printf("return "),
        if (m.range = float) printf("_float_("),
        printf("~I(~I)",c_princ(functional!(m)),
                (for i in (1 .. n)
                  (if (i != 1) princ(","),
                   if (m.domain[i] = float) printf("float_v(~I)",expression(lv[i],nil))
                   else expression(lv[i],nil)))),
        if (m.range = float) printf(")"),
        princ(";\n"),
        princ("}\n\n")) ]

[at(c:c_producer) : void -> princ("->")]

// v3.2.52 : generate a nice function that can be used by the interpreter for tuple-valued
// methods. Note that this could be used instead of adding an ->coyIfNeeded
[generate_tuple_function(c:c_producer,m:method,%nom:string) : void
 -> let ld := (if (length(m.domain) = 1 & domain!(m) = void) nil else m.domain),
        n := length(ld),
        lv := list{Variable(pname = gensym(), range = x) | x in ld},
        %nom_ := %nom /+ "_",
        %f := make_function(%nom_),
        %lambda := lambda!(lv,nil),
        s := tuple in
       (generate_regular_function(c,%lambda, %f, s, m,lv),
        OPT.functions :add list(%f, lv, s),
        if (s != void) printf("return "),
        printf("~I(~I)",c_princ(functional!(m)),
                (for i in (1 .. n)
                  (if (i != 1) princ(","),
                   expression(lv[i],nil)))),
        printf("->copyIfNeeded();\n"),
        princ("}\n\n")) ]


// management of OPT.functions: list of entries ->  function info =
// list(%function, lv, s, m, lambda, outfile)     [mode f2c]
// list(%function, lv, s)                         [mode f2f]
[create_function_entry(c:c_producer, lb:lambda, %f:string, m:any) : any  -> nil ]
[update_function_entry(c:c_producer, %f:function, lv:list, s:class) : any
  ->  OPT.functions :add list(%f, lv, s), false ]

    
// *******************************************************************
// *       Part 3: interface declarations                            *
// *******************************************************************

// use the interface list
[c_interface(self:class) : string
 -> let n := get(PRODUCER.interfaces, self) in
       (if (n = 0) "OID *" else PRODUCER.interfaces[n + 1] as string ) ]

[c_interface(self:class,s:string) : void
 -> let n := get(PRODUCER.interfaces, self) in
       (if (n = 0) PRODUCER.interfaces := (PRODUCER.interfaces add self) add s
        else PRODUCER.interfaces[n + 1] := s) ]

// useful and nice
[c_interface(self:method) : void
 -> c_princ(Optimize/function_name(self.selector, self.domain,self.functional)) ]


// How to declare a sort in C. The boolean tells if we are in an external
// mode , in which case we produce the C sort. Otherwise, we use OIDs.
// we shall add later: float and boolean
[interface!(c:c_producer, self:class) : void
 ->  if (self = void) princ("void ")
     else if (self = integer) princ("CL_INT ")
     else if (self % {char,boolean,function}) printf("~I *", ident(c,self.name))
     else if (self inherit? import | self = string | self = array)
        princ(c_interface(self))
     else if (self inherit? object) printf("~I *", class_princ(c,self))  // v3.3.14
     else if (self inherit? bag) printf("~I *", ident(c,self.name))
     else if (self = float) printf("double ")
     else princ("OID ") ]

// general translation method: oself is an expression that must be translated
// to a CLAIRE id. oself is functional !
[to_cl(c:c_producer,x:any,s:class,loop:any) : void
 -> if (s = void) printf("_void_(~I)", expression(x, loop))
    else if (s inherit? object)
       (if (x = true) printf("Kernel.ctrue")
        else if (x = false) printf("Kernel.cfalse")
        else printf("_oid_(~I)", expression(x, loop)))
    else if (s = integer)
        (if (compiler.safety > 1) printf("((OID)~I)",expression(x, loop)) //<sb> cast negative values to avoid c++ compiler warining
         else printf("_integer_(~I)", expression(x, loop)))
    else if (s = char) printf("_oid_(~I)", expression(x, loop))
    else if (s = string) printf("_string_(~I)",expression(x,loop))
    else if (s = array) printf("_array_(~I)",expression(x,loop))
    else if (s = float) printf("_float_(~I)",expression(x,loop))
    else if (s inherit? import)
        printf("ClAlloc->import(~I,(OID *) ~I)", expression(s, {}),
                                         expression(x, loop))
    else if (s = any) expression(x, loop)
    else error("[internal] to_cl for a ~S is not implemented", s) ]

// reverse function
//
[to_c(c:c_producer,x:any,s:class,loop:any) : void
  -> if (s = integer)
		(if not(x % integer) printf("((CL_INT)~I)", expression(x, loop))
		else expression(x, loop))
     else if (x = unknown)
     	(if (s = float) printf("0.0") //<sb> v3.3.35 fix C++ warning
     	else printf("NULL"))
     else if (x % global_variable & x.range = {} & x.value = nil)
        printf("Kernel.nil")
     else if (s inherit? import & x % to_protect & get(arg,x) % to_CL)
     	//<sb> v3.3.35 prevent an allocation EXPORT(GC_OID(ClAlloc->import(...)))
     	// which is identity
     	expression(x.arg.arg, loop)
     else printf("~I~I)", to_c(c,s), expression(x, loop)) ]

// produces the first half of the previous statement
[to_c(c:c_producer,s:class) : void
 -> if (s inherit? object) printf("OBJECT(~I,", class_princ(s))   // v3.3.14
    else if (s = float) princ("float_v(")
    else if (s = char) printf("char_v(")
    else if (s = string) printf("string_v(")
    else if (s = array) printf("array_v(")
    else if (s inherit? import) printf("EXPORT((~I),", interface!(s))
    else error("[internal] to_c for a ~S is not implemented", s) ]

[public_static(c:c_producer) : void -> nil]

// v3.1.12
[bool_exp!(c:c_producer,self:any,loop:any)  : void
  -> case self
       (to_CL printf("(~I ? Kernel.ctrue : Kernel.cfalse)", bool_exp(self,true,loop)),
        any printf("(~I ? CTRUE : CFALSE)", bool_exp(self,true,loop))) ]


// *******************************************************************
// *       Part 4: use of language dependent patterns (macros)       *
// *******************************************************************

[inherit_exp(c:c_producer,a1:any,a2:any,loop:any) : void
 -> printf("INHERIT(~I,~I)", expression(a1, loop), expression(a2, loop)) ]

[bitvector_exp(c:c_producer,a1:any,a2:any,loop:any) : void
 -> printf("BCONTAIN(~I,~I)", expression(a1, loop), expression(a2, loop)) ]

// when we print an equality, we do not need to_CL !
[equal_exp(c:c_producer, a1:any,pos?:boolean,a2:any,id?:any) : void
 -> if (a1 % Compile/to_CL & a2 % Compile/to_CL &
         osort(a1.set_arg) = osort(a2.set_arg) &
         (Compile/identifiable?(a1.arg) |              // NEW:make sure id? := true or string
          Compile/identifiable?(a2.arg) |
          a1.set_arg = string | a1.set_arg = float))   // or float => will generate nice form
       equal_exp(c,a1.arg, pos?, a2.arg, true)
     else if (a1 % to_protect & a1.arg % to_CL & not(c_gc?(a1.arg.arg)) & 
              a2 % to_protect & a2.arg % to_CL & not(c_gc?(a2.arg.arg))) 
          equal_exp(c,a1.arg,pos?,a2.arg,id?)   // v3.3.32: gc-protect because of to_cl -> remove them
     else if (c_sort(a1) = string & c_sort(a2) = string &
              not(case a2 (to_C (a2.arg = unknown))))
        printf("(equal_string(~I,~I) ~I CTRUE)",
               expression(a1, nil), expression(a2, nil), sign_equal(pos?))
     else if (a1 % Compile/to_CL & a1.set_arg != integer & a2 = unknown)
       printf("(~I ~I ~I)", expression(a1.arg, nil), sign_equal(pos?),
       				(if (a1.set_arg = float) princ("0.0") //<sb> v3.3.35 fix C++ warning
       				else princ("NULL")))
     else if (char_exp?(c,a1) | char_exp?(c,a2))
        printf("(~I ~I ~I)", char_exp(c,a1, nil), sign_equal(pos?),
               char_exp(c,a2, nil))
     else if (id? | Compile/identifiable?(a1) | Compile/identifiable?(a2) |
              c_sort(a1) = float)
        (// if sort(a1) != sort(a2) y'a bug
         if (stupid_t(a1) glb stupid_t(a2) = {})
            (warn(), trace(2,"`BLUE ~S = ~S will fail ! [263]\n",a1,a2)),
         printf("(~I ~I ~I)", bexpression(a1, nil), sign_equal(pos?),
                bexpression(a2, nil)))
     else printf("(equal(~I,~I) ~I CTRUE)",
                 expression(a1, nil),
                 expression(a2, nil), sign_equal(pos?)) ]

// new: special code for char
[char_exp?(c:c_producer,x:any) : boolean
  -> case x (char true,
             Call_method let m := x.arg in
                           (m = *nth_1_string* |
                            (m = *nth_string* & compiler.safety >= 2)),
             any false) ]

[char_exp(c:c_producer,x:any,loop:any) : void
  -> case x (char printf("((unsigned char)~S)", x), //<sb>
  			;char printf("'~I~A'",
            ;       (if (x % {'"', ''', '?', '\'}) princ("\\")), x),
             Call_method
                let m := x.arg in
                   (if  (m = *nth_1_string* | m = *nth_string*)
                      let a1 := x.args[1], a2 := x.args[2] in
                         printf("~I[~I - 1]", expression(a1, loop),
                                              expression(a2, loop))
                    else printf("((unsigned char) ~I->ascii)",expression(x,loop))),
             any printf("((unsigned char) ~I->ascii)",expression(x,loop))) ]

             
// reads the member x from an expression oself of owner s
[c_member(c:c_producer,self:any,s:class,x:property,loop:any) : void
 ->  if (stupid_t(self) inherit? s)
        (/* if *in_store*
          printf("STOREREF(~I)->~I", expression(self, loop), ident(x.name))
        else */
          printf("~I->~I", expression(self, loop), ident(x.name)))
     else printf("CLREAD(~I,~I,~I)", class_princ(s),
                 (if *in_store*
                    printf("STOREREF(~I)", expression(self, loop))
                  else expression(self, loop)), ident(x.name)) ]

[addFast(c:c_producer) : void -> printf("->addFast") ]

// produces a cast for C++
cast!(c:c_producer,self:C_cast,loop:any) : void
 -> printf("((~I *) ~I)", class_princ(self.set_arg),    // v3.3.14
                          expression(self.arg, loop))

// u is either an expression, a variable or a string, which is indicated by the
// value of kind
// we use a place reserved in the stack (note the optimization if OPT.loop_index = 0)
// v3.2.32: trap the integer case ...
//<sb> loop_index is now even smatter 
[gc_protection_exp(c:c_producer,v:Variable,exp?:boolean,u:any,loop:any) : void
  -> if (osort(v.range) inherit? import |		//<sb> avoid external value to be pushed
			osort(v.range) = float | osort(v.range) = integer)     // in v3.0 double are NOT protected !
        printf("(~I=~I)",ident(c,v),             // v3.0.72
               (if exp? expression(u,loop) else c_princ(u as string)))
     else (c.stat :+ 1,          // v3.3.32
     	printf("GC__~A(~I~I, ~A)",
       (if (osort(v.range) = any) "OID"
        else if (osort(v.range) = string) "STRING"
        else "ANY"),        // any is for object
       ident(c,v),
       (if (u != v)         // used for an assinment
         (princ(" = "),
          (if exp? expression(u,loop) else c_princ(u as string)))),
       (OPT.loop_index :+ 1, OPT.loop_index))) ]   // v3.0.55 //<sb> even smatter reserving

// generic for bags
[bag_expression(cx:c_producer,c:class,l:bag,t:type,loop:any) : void
  -> if (length(l) = 0)
        printf("~S::empty(~I)",c,
               (if (t != void)
                    (//[5] t = ~S => ~S // t, c_code(t,object),
                     expression(c_code(t,object),loop))))
     else (printf("~S::alloc~I(~I~A,~I)", c,
                  (if (c = tuple & OPT.alloc_stack) princ("Stack")),                 // v3.2.26 // temporarly removed
                  (if (t != void) printf("~I,",expression(c_code(t,object),loop))),
                  length(l),
                  args_list(l, loop, length(l) > 2)))]



// *******************************************************************
// *       Part 5: System compiling methods                          *
// *******************************************************************


// compiles a list of modules into a system file, which is the small definition
// of the module and the associated load function
// v3.2.54 add the m argument
[generate_s_file(self:string,l:list,m:any) : void
 -> let p := fopen((compiler.source / self) /+ "-s" /+ PRODUCER.extension, "w"),
        l_used:list := Reader/add_modules(l),
        l_necessary:list := parents(l) in
       (//<sb> add trace for system file
       //[0] ==== Generate system file ~A // (compiler.source / self) /+ "-s" /+ PRODUCER.extension,
       OPT.cinterface := p,
        OPT.properties := set<property>(),
        OPT.objects := list<any>(),
        OPT.functions := list<any>(),
        OPT.need_to_close := set<any>(),
        OPT.legal_modules := set!(l_necessary),
        use_as_output(p),
        printf("// --- System configuration file for ~S ---\n\n", self),
        printf("#include <claire.h>\n"),
        printf("#include <Kernel.h>\n"),
        for x in l_used
          (if x.made_of printf("#include <~I.h>\n", ident(x.name))),
        create_load_modules(self, p, l_necessary,m),
        if (main @ list & domain!(main @ list) = list)
         let s := "main_list" in // if (compiler.naming = 0) "claire_main_list" else "main_list") in
          (printf("\nextern void ~A(list *l);\n",s),
           printf("void call_main() {~A(ClEnv->params);}\n",s))
        else princ("\nvoid call_main() {default_main();}\n"),     // v3.2.50 use default_main ...
        putc("\n"[1],p), //<sb> ensure new line at end of file - prevent C++ compiler warning
        breakline(),
        breakline(),
        printf("class InitLoadModule {\n"),
        printf("public:\n"),
    	  printf("  static InitLoadModule single;\n"),
    	  printf("  InitLoadModule() {\n"),
    	  printf("    set_load_module(loadModules);\n"),
    	  printf("    set_call_main(call_main);\n"),
    	  printf("  }\n"),
    	  printf("};\n\n"),
    	  printf("InitLoadModule InitLoadModule::single = InitLoadModule();\n"),
        fclose(p))]

// called by the run_system function. The goal of this method is
// to create the modules, and fill the corresponding indexed of the
// "system" object.
[create_load_modules(self:string,p:port,l_necessary:list,m:any) : void
 -> breakline(),
    for x in l_necessary //<sb> was {m in l_necessary | m.status = 5}
    			// a set may desorder the given list!
    	(if (x.status = 5)
       		printf("void load_~I() {~I.metaLoad();}\n",ident(x.name), ident(x.name))),
    printf("\n\nvoid loadModules() \n"),
    new_block(),
    printf("//module definitions ~I", breakline()),
    for x in l_necessary //<sb> was (l_necessary \ {claire,mClaire,Kernel})
    				// a set may desorder the given list!
       (if not(x % {claire,mClaire,Kernel})
       		printf("~I.initModule(~S,~I,~I,~I~S,~I);~I", ident(x.name), string!(x.name),
              expression(x.part_of,nil),
              expression(c_code(x.uses,list),nil),
              breakline(),
              source(x),
              expression(c_code(x.made_of,list),nil),
              breakline())),
    printf("//module load ~I", breakline()),
    for x in l_necessary //<sb> was {m in l_necessary | m.made_of & m.status != 5}
    				// a set may desorder the given list!
       (if (length(x.made_of) > 0 & x.status != 5)
       		printf("~I.metaLoad();~I",ident(x.name),breakline())),
    for x in l_necessary //<sb> was {m in l_necessary |m.status = 5}
    				// a set may desorder the given list!
      (when v := get(version, x) in printf("~I.it->version = ~S;~I",ident(x.name),v, breakline()), //<sb> add module version
      when v := get(comment, x) in printf("~I.it->comment = ~S;~I",ident(x.name),v, breakline()), //<sb> add module version
       if (x.status = 5)
		  ( printf("~I.it->evaluate = ~I~I",ident(x.name),
				   expression(make_function("load_" /+ string!(x.name)), false),
				   breakline()),
			printf("~I.it->status = 2;~I",ident(x.name), breakline()))),
    printf("ClEnv->module_I = ~I; ~I",
            expression( (if (m % module) m else claire), nil),
            breakline()),
    if (compiler.safety > 5) printf("ClAlloc->statusGC = 2;\n"),  // v3.1.12
    if OPT.profile?
       for p in Kernel/graph(Reader/PRdependent)
         case p (property for p2 in Reader/PRdependent[p]
                     (if (not(p2 % OPT.to_remove) &
                           mClaire/definition(p.name) = mClaire/definition(p2.name))   // v3.2.58
                     printf("PRdepends_property(~I,~I);\n",expression(p,nil),
                                 expression(p2,nil)))),
    close_block()]


[create_dynload_module(x:module) : void
 -> breakline(),
    printf("\n\nextern \"C\" CL_EXPORT void dynLoad~I() \n", c_princ(x.name)),
    new_block(),
 		printf("~I.initModule(~S,~I,~I,~I~S,~I);~I", ident(x.name), string!(x.name),
        expression(x.part_of,nil),
        expression(c_code(x.uses,list),nil),
        breakline(),
        source(x),
        expression(c_code(x.made_of,list),nil),
        breakline()),
    if (length(x.made_of) > 0 & x.status != 5)
       printf("~I.metaLoad();~I", ident(x.name), breakline()),
    when v := get(version, x)
    in printf("~I.it->version = ~S;~I",ident(x.name),v, breakline()), //<sb> add module version
    when v := get(comment, x)
    in printf("~I.it->comment = ~S;~I",ident(x.name),v, breakline()), //<sb> add module version
    close_block()]


// new: add the code to define interface methods
// WARNING: the interface methods are uniform but C++ does not support
// dynamic dispatch on them - they are really meant to be interface
// methods
methods_interface(c:c_producer,x:class) : void
  -> (for p in Language/InterfaceList[x]
       let m := (p @ x) in
         (//[5] method interface ~S at ~S -> ~S // p,x,m,
          if (m % method & known?(formula,m))
            let s := class!(m.range), %vars := cdr(m.formula.vars) in
               printf("~ICL_EXPORT ~I ~I(~I);  ",
                      breakline(),
                      interface!(c,s),
                      c_princ(p.name),
                      typed_args_list(%vars))))

methods_bodies(c:c_producer,x:class) : void
  -> (for p in Language/InterfaceList[x]
       let m := (p @ x) in
         (//[5] write method body ~S at ~S -> ~S // p,x,m,
          if (m % method & known?(formula,m))
            let s := class!(m.range), %vars := cdr(m.formula.vars) in
              (printf("~I// interface method ~I", breakline(), breakline()),
               printf("~ICL_EXPORT ~I ~I::~I(~I)~I  ",
                      breakline(),
                      interface!(c,s),
                      class_princ(x),  // v3.3.14
                      c_princ(p.name),
                      typed_args_list(%vars),
                      breakline()),
               printf("\t{ ~I~I;}\n~I",
                      (if (s != void) printf("return (~I) ",interface!(c,s))),
                      (if (p.mClaire/dispatcher > 0)
                          printf("~I->fcall((CL_INT) this~I)",
                                 expression(p,nil),
                                 (for v in %vars
                                     (princ(",(CL_INT) "), expression(v,nil))))
                       else printf("~I(this~I)",
                                c_princ(Compile/functional!(m)),
                                (for v in %vars
                                     (princ(","), expression(v,nil))))),
                       breakline()))))



