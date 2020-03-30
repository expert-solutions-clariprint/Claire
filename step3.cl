
(printf("=======================================\n"))
(printf("====             STEP 3             ===\n"))
(printf("=======================================\n"))
(printf("=== how to generate release files : ===\n"))
(printf("===      - csrc/cclaire-s.cpp       ===\n"))
(printf("===      - csrc/ccmain.cpp.in       ===\n"))
(printf("===      - include/ccmain.h         ===\n"))
(printf("=======================================\n"))


(compiler.inline? := true,
compiler.naming := 1,
verbose() := 2,
compiler.safety := 5,
compiler.optimize? := true,
compiler.headers_dir := "include",
compiler.source := "csrc")

[compile_ccmain_in() : void
 -> Compile/need_modules(OPT) := set(),
    let %interface:string := compiler.headers_dir / "ccmain.h" in
      (OPT.Compile/legal_modules := set!(module),
       OPT.Compile/properties := set<property>(),
       OPT.Compile/objects := list<any>(),
       OPT.Compile/functions := list<any>(),
       OPT.Compile/cinterface := fopen(%interface,"w"),
       OPT.Compile/cfile := "ccmain",
       Generate/generate_file("main.cl.in", source(compiler) / "ccmain"),
       use_as_output(OPT.Compile/cinterface),
       Generate/breakline(),
       for x in Compile/need_modules(OPT),
          (if (made_of(x) & not(x % claire_modules))
              printf("#include <~I.h>\n",Generate/ident(name(x)))),
       // generate the function definitions
       for l in OPT.Compile/functions     // prints the API methods
        let %f := l[1], %vars := l[2], s := l[3] in
          printf("\nextern ~I ~I(~I);",
                Generate/interface!(PRODUCER,s), c_princ(%f),
                Generate/typed_args_list(%vars)),
       printf("\n"), //<sb> solve warning on some C++ compiler
       fclose(OPT.Compile/cinterface))]

(load("main.cl.in"),
PRODUCER.Generate/extension := ".cpp.in",
compile_ccmain_in())


(PRODUCER.Generate/extension := ".cpp",
Generate/generate_s_file("cclaire",list(Core,Serialize,Language,Reader,Optimize,Generate),claire))