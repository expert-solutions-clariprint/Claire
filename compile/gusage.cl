
// *********************************************************************
// * CLAIRE                                            Sylvain Benilan *
// * gusage.cl                                                         *
// * Copyright (C) 2005 xl. All Rights Reserved                        *
// *********************************************************************


// *******************************************************************
// * Contents                                                        *
// *    Part 1: definition of system variables                       *
// *    Part 2: definition of the main function                      *
// *    Part 3: single file compiling                                *
// *    Part 4: Generating makefiles                                 *
// *    Part 6: Creating new module (xl)                             *
// *    Part 7: Export/publish module (xl)                           *
// *    Part 8: Recompiling module (xl)                              *
// *    Part 9: Listing exported/published module (xl)               *
// *******************************************************************


claire/so_options:string  :: ""
claire/cxx_options:string :: ""
claire/ld_options:string  :: ""


// *******************************************************************
// *       Part 1: definition of the system variables                *
// *******************************************************************


// dumb utility
[external!(m:module) : string
 -> if known?(external,m) m.external else string!(m.name)]

[string2module(s:string) : module
  -> let m := get_value(s) in
       case m (module m,
               any error("~A is not a module",s))]

// *******************************************************************
// *       Part 2: definition of the main function
// *******************************************************************

rCode:boolean := true
%cm:string := ""
%cf:string := ""
%cxf:string := ""
dblevel:integer := 1
%out:string := ""
%cj:string := ""
%sudo:boolean := false
%ov:boolean := false
%cls:boolean := false
%call:boolean := false
%export:any := false
%both:boolean := false
%publish:boolean := false
%sm:string := ""
%em:string := ""
cppopts:string := ""
linkopts:string := ""
clevel:integer := 1
%init?:boolean := true
vlevel:integer := 2
slevel:integer := 0
clcc?:boolean := true


//<sb> get the path to the claire home dir
home_path() : string ->
  let f := realpath(getenv("_")),
    l := rfind(f,*fs*)
  in substring(f, 1, l - 5) // rm bin/claire
 
// *******************************************************************
// *       Part 3: single file compiling                             *
// *******************************************************************

// compile a single command file: can only generate functions
// since there is no associated module
// we assume that the file only contains function definitions
//
[function_compile(self:string, fullname:string) : void
 -> need_modules(OPT) := set(),
    let %interface:string := compiler.headers_dir / self /+ ".h" in
      (OPT.legal_modules := set!(module),
       OPT.properties := set<property>(),
       OPT.objects := list<any>(),
       OPT.functions := list<any>(),
       OPT.cinterface := fopen(%interface,"w"),
       OPT.cfile := self,
       if isfile?(source(compiler) / self /+ PRODUCER.extension)
          unlink(source(compiler) / self /+ PRODUCER.extension),
       Generate/generate_file(fullname, source(compiler) / self),
       use_as_output(OPT.cinterface),
       Generate/breakline(),
       for x in need_modules(OPT),
          (if (made_of(x) & not(x % claire_modules))
              printf("#include <~I.h>\n",Generate/ident(name(x)))),
       // generate the function definitions
       for l in OPT.functions     // prints the API methods
        let %f := l[1], %vars := l[2], s := l[3] in
          printf("\nextern ~I ~I(~I);",
                Generate/interface!(PRODUCER,s), c_princ(%f),
                Generate/typed_args_list(%vars)),
       printf("\n"), //<sb> solve warning on some C++ compiler
       fclose(OPT.cinterface))]


// *******************************************************************
// *       Part 4: Generating makefiles                              *
// *******************************************************************

//<sb> made lib paths compatible with xl architecture
// now support libs in <claire_prefix>/lib and in paths
// found in environment variable CLAIRE3_HOME (separated by ':')

[libpath() : string ->
  if (isfile?(compiler.env / "sclaire") | isfile?(compiler.env / "sclaire.exe")) compiler.env //<sb> needed for the compilation of cclaire from a release dir
  else home_path() / "lib"] // path to installed micro claire libs

//<sb> support for libs present in exported and published modules and local module
[libpath!(m:module) : void ->
  let ext := (if (compiler.env = "ntv") ".lib"
              else if (lower(sys_name()) = "os/390") ".x"
              else ".o")
  in when x := some(x in used_modules|x[1] = m)
  in (let mp := x[2] / ("v" /+ release() /+ "-" /+ env(compiler)),
      mpl := x[2] / env(compiler)
    in (if isdir?(mpl) // local module, for instances CLAIRE_LIBS may contains '..' 
              // -> assume to be a module under development
                 // -> lib path 'mpl' 
        (if isfile?(mpl / external!(m) /+ ".dll")
          fcopy(mpl / external!(m) /+ ".dll", env(compiler) / external!(m) /+ ".dll"),
        if isfile?(mpl / external!(m) /+ ext)
          princ(mpl / external!(m) /+ ext)
        else error("Local module ~S have no library file [~A]", m, mpl))
      else // external module (published or exported)
          // -> li path 'mp'
        (if isfile?(mp / external!(m) /+ ".dll")
          fcopy(mp / external!(m) /+ ".dll", env(compiler) / external!(m) /+ ".dll"),
        if isfile?(mp / external!(m) /+ ext)
          princ(mp / external!(m) /+ ext)
        else error("External module ~S have no library file [~A]", m, mp))))
  else (if isfile?(libpath() / external!(m) /+ ext) // micro claire libs (Kernel, mClaire, iClaire...)
          princ(libpath() / external!(m) /+ ext)
        else if (lower(sys_name()) = "os/390")
          princ(compiler.env / external!(m) /+ ".o")
        else princ(compiler.env / external!(m) /+ ext))] // module's lib

//<sb> support for headers present in exported and published modules and local module
[headers!() : void ->
  let %env := compiler.env,
    %I := "-I",
    ext := (if (compiler.env = "ntv") ".obj" else ".o")
  in (if (length(compiler.headers_dir) > 0 & entries(compiler.headers_dir,"*.h*"))
      printf("~A~A ", %I, compiler.headers_dir),
    if (isdir?("include") & compiler.headers_dir != "include" & entries("include","*.h*"))
      printf("~Ainclude ", %I),
    if (not(isfile?(compiler.env / "sclaire") | isfile?(compiler.env / "sclaire.exe")) & isdir?(home_path() / "include"))
      printf("~A~A ", %I, home_path() / "include"), // micor claire headers (Kernel, iClaire, mClaire...)
    for i in used_modules
      let mp := i[2] / ("v" /+ release() /+ "-" /+ env(compiler)),
        mpl := i[2], m := i[1]
      in (if isdir?(mpl / env(compiler)) // local module include dirs
          (if (isdir?(mpl / "include") & entries(mpl / "include"))
            printf("~A~A ", %I, mpl / "include")) //<sb> add user includes if any
        else // external module include dirs
          (if isfile?(mp / external!(m) /+ ext)
            printf("~A~A ", %I, mp))))]


// prints the list of lib files that are needed for m
[lib!(m:any,l:list) : void             // + Tibor
  -> let s_end := (if (env(compiler) = "ntv") ".lib"
                  else if (lower(sys_name()) = "os/390") ".x"
                  else ".o"),
      first := true,
         s_sep := " " in
      (for m2 in {x in l|made_of(x)}
        (if not(lower(sys_name()) = "os/390" & m2 = Core)
          printf("~I~I",
                       (if first first := false
                       else princ(s_sep),
                       libpath!(m2)),
                       for s in {s1 in uses(m2)|s1 % string}
                         printf("~A~A~A",s_sep,s,s_end))),
     for m2 in compiler.libraries
           (if first first := false
            else princ(s_sep),
            if (m2 = "Kernel")
              printf("~A~A~A~A~A", s_sep, libpath(), *fs*,
                          (if (s_end = ".x") "boot" else m2),
                          s_end)
            else if (m2 % {"Console", "noConsole", "wclConsole"})
              printf("~A~A~A~A~A", s_sep, libpath(), *fs*, m2,
                            (if (s_end = ".x") ".o" else s_end))
            else printf("~A~A", s_sep, m2)))]

[importlib!(m:any,l:list) : void             // + Tibor
  -> let s_end := (if (env(compiler) = "ntv") ".lib"
                  else if (lower(sys_name()) = "os/390") ".x"
                  else ".o"),
      first := true,
         s_sep := " " in
      (for m2 in {x in l|made_of(x) & m != x}
        (if not(lower(sys_name()) = "os/390" & m2 = Core)
          printf("~I~I",
                       (if first first := false
                       else princ(s_sep),
                       libpath!(m2)),
                       for s in {s1 in uses(m2)|s1 % string}
                         printf("~A~A~A",s_sep,s,s_end))),
     for m2 in list{l in compiler.libraries|not(l % {"Console", "noConsole", "wclConsole"})}
           (if first first := false
            else princ(s_sep),
            if (m2 = "Kernel")
              printf("~A~A~A~A~A", s_sep, libpath(), *fs*,
                          (if (s_end = ".x") "boot" else m2),
                          s_end)
            else if (m2 = "Core" & s_end = ".x") none
            else printf("~A~A", s_sep, m2)))]

// prints the necesssary files for the two compilation modes
// if link? is true we need a comma-separated list
// if m is a module, we compile fi*.cpp + m.cpp -> m.lib
// if m=f is a file, we compile f-s.cpp (system), f.cpp (functions) -> exe
[files!(m:any,link?:boolean,%out:string) : void
 ->  let %bef := (if link? "" else "$T" /+ *fs*),
      %cbef := (if link? "" else "$U" /+ *fs*),
     %end := (if (env(compiler) = "ntv") "obj" else "o"),
         %sep := (if link? "," else " ") in
        printf("~A~A.~A~I",%bef,                              // added by Tibor
          (if (link? | m % string) (%out /+ "-s") else external!(m)),
                %end,
          (case m
            (module
               (if not(link?)
                    for ff:string in made_of(m) //<sb> support for cpp in made_of
                      (if match_wildcard?(ff, "*@PATH_INFO@*")
              let t := explode(ff, "@PATH_INFO@"),
                fname := replace(t[1], *fs*, "-")
              in (if (left(fname,2) = "./") fname := substring(fname,3,length(fname)),
                if (left(fname,1) = ".") fname := substring(fname,2,length(fname)),
                printf("~A~A~A.~A ",%sep,%bef, fname, %end))
            else if (match_wildcard?(ff,"*.cl") | not(match_wildcard?(ff,"*.*")))
                           printf("~A~A~A.~A ",%sep,%bef, replace(ff,".cl",""), %end)
                      else if not(match_wildcard?(ff,"*.h*"))
                        printf("~A~A~A.~A ",%sep,%cbef, replace(replace(ff, ".cpp", ""),".cc",""), %end))),
             string printf("~A~A~A.~A",%sep, %bef, m, %end))))]
     

[job_option() : string ->
  let res := ""
  in (for i in (1 .. length(params()) - 1)
      (if (params()[i] = "-make")
        (res := (params()[i + 1] as string) /+ " ",
        i :+ 1)),
      res)]

// module linker - dispatch according to hardware and OS
[cmakefile(m:any, out:string) : void
  -> let l :=  Reader/add_modules(claire_modules),
         f := (case m (module string!(name(m)), any out)), // name of the .mk file
         %os := env(compiler) in
       (if not("-relink" % params())
          (if (out != "" & clcc?) Generate/generate_s_file(out,l,m), // v3.2.54 !!!!
          //<sb> rm these line see -noConsole option
          //else if (length(claire_modules) = 3) compiler.libraries :add "noConsole"
          //else compiler.libraries :add "Console",
          if (not("noConsole" % compiler.libraries) &
            not("wclConsole" % compiler.libraries)) compiler.libraries :add "Console",
          if (%os = "ntv") create_makefile_nt(m,out,l)    // Visual
          else create_makefile_unix(m, out, l)))]

    
    
;----------------------- NT makefile (MS Visual C++ or Warcom) ----------------------

[create_makefile_nt(m:any,out:string,l:list) : void
 -> (print_in_string(),
     printf("CL /nologo /DCLPC ~I~A", headers!(), claire_options),
     case m
      (module
         (printf(" /Tp~A~A~A~A", compiler.source, *fs*,external!(m), PRODUCER.extension),
         printf(" /Fo~A~A~A.obj", compiler.env, *fs*, external!(m))),
      any
         (printf(" /Tp~A~A~A~A", compiler.source, *fs*, m, PRODUCER.extension),
         printf(" /Fo~A~A~A.obj", compiler.source, *fs*, m))),
     let cmd := end_of_string()
     in (printf("~A\n", cmd),
        if (shell(cmd) != 0)
          (printf("Compilation error - abort\n"),
          exit(1))),
     case m
      (module
        (print_in_string(),
        printf("LIB /NOLOGO /DEF ~A~A~A.obj /OUT:~A~A~A.lib",
                  compiler.env, *fs*, external!(m),
                  compiler.env, *fs*, external!(m)),
        let cmd := end_of_string()
        in (printf("~A\n", cmd),
            if (shell(cmd) != 0)
              printf("Failed to generate import library\n")),
        print_in_string(),
        printf("LINK /SUBSYSTEM:CONSOLE /NOLOGO /STACK:1600000 ~Iuser32.lib gdi32.lib shell32.lib comdlg32.lib ws2_32.lib",
                  (if compiler.debug? princ("/DEBUG /MAP "))),
        printf(" ~I ~A~A~A.obj /DLL /OUT:~A~A~A.dll",
                  importlib!(m,l),
                  compiler.env, *fs*, external!(m),
                  compiler.env, *fs*,
                  external!(m)),
        let cmd := end_of_string()
        in (printf("~A\n", cmd),
            if (shell(cmd) != 0)
              (printf("DLL Link error\n"),
              exit(1))))),
     if (out != "")
       (print_in_string(),
       printf("CL /nologo /DCLPC ~I~A", headers!(), claire_options),
       printf(" /Tp~A~A~A-s~A", compiler.source, *fs*, out, PRODUCER.extension),
       printf(" /Fo~A~A~A-s.obj", compiler.source, *fs*, out),
       let cmd := end_of_string()
       in (printf("~A\n", cmd),
          if (shell(cmd) != 0)
            (printf("Compilation error - abort\n"),
            exit(1))),
        print_in_string(),
        printf("LINK /SUBSYSTEM:CONSOLE /NOLOGO ~I/STACK:1600000 user32.lib gdi32.lib shell32.lib comdlg32.lib ws2_32.lib",
                  (if compiler.debug? princ("/DEBUG /MAP "))),
        printf(" /IMPLIB:~A~Adummy.exe /OUT:~A~A~A.exe ~I ~I",
                          compiler.env, *fs*,
                          compiler.env, *fs*, out,
                          printf("~A~A~A-s.obj",compiler.source,*fs*,out),
                          lib!(m,l)),
        if (m % string)
          printf(" ~A~A~A.obj", compiler.source, *fs*, m),
        let cmd := end_of_string()
        in (printf("~A\n", cmd),
            if (shell(cmd) != 0)
              (printf("Link error - abort\n"),
              exit(1)))))]


; ------------------------  Unix (Linux, Solaris, OS X, ...) -----------------------
  
// creates the unix makefile for a module or a string (cf. nt makefile)
// this was copied from v2.4.28
// with the help of Francois Laburthe !
[create_makefile_unix(m:any,out:string,l:list) : void ->
  print_in_string(),
   printf("@CXX@ @CL_X86_64_CXX@ @CXXOPTIMFLAGS@ ~I~A~A", headers!(), claire_options, cxx_options),
   case m
    (module
       (printf(" -o ~A~A~A.o", compiler.env, *fs*, external!(m)),
       printf(" -c ~A~A~A~A", compiler.source, *fs*,external!(m), PRODUCER.extension)),
    any
       (printf(" -o ~A~A~A.o", compiler.source, *fs*, m),
       printf(" -c ~A~A~A~A", compiler.source, *fs*, m, PRODUCER.extension))),
   let cmd := end_of_string()
   in (printf("~A\n", cmd),
       let rc := shell(cmd)
       in (if ((lower(sys_name()) = "os/390" & not(rc % {0,4})) |
              (lower(sys_name()) != "os/390" & not(rc % {0})))
            (printf("Compilation error - abort\n"),
            exit(1)))),
   case m
    (module
      (print_in_string(),
      printf("@CXX@ @LDFLAGS@~A", so_options),
      printf(" -o ~A~A~A.so  ~A~A~A.o ~I",
                compiler.env, *fs*, external!(m),
                compiler.env, *fs*, external!(m),
                (if (lower(sys_name()) = "os/390")
                  importlib!(m,l))),
      let cmd := end_of_string()
      in (printf("~A\n", cmd),
         let rc := shell(cmd)
         in (if ((lower(sys_name()) = "os/390" & not(rc % {0,4})) |
                (lower(sys_name()) != "os/390" & not(rc % {0})))
              (printf("Failed to generate shared object\n"),
              exit(1)))),
      if (lower(sys_name()) = "os/390")
        shell("mv *.x " /+ compiler.env))),
   if (out != "")
     (print_in_string(),
     printf("@CXX@ @CL_X86_64_CXX@ @CXXOPTIMFLAGS@ ~I~A~A", headers!(), claire_options, cxx_options),
     printf(" -o ~A~A~A-s.o", compiler.source, *fs*, out),
     printf(" -c ~A~A~A-s~A", compiler.source, *fs*, out, PRODUCER.extension),
     let cmd := end_of_string()
     in (printf("~A\n", cmd),
         let rc := shell(cmd)
         in (if ((lower(sys_name()) = "os/390" & not(rc % {0,4})) |
                (lower(sys_name()) != "os/390" & not(rc % {0})))
              (printf("Compilation error - abort\n"),
              exit(1)))),
      print_in_string(),
      printf("@CXX@ @LDFLAGS@"),
      printf(" ~A -o ~A~A~A ~I ~I @LIBS@ @ETR_SOCKET_LIBS@",
                        ld_options,
                        compiler.env, *fs*, out,
                        printf("~A~A~A-s.o",compiler.source,*fs*,out),
                        lib!(m,l)),
      if (m % string)
        printf(" ~A~A~A.o", compiler.source, *fs*, m),
      let cmd := end_of_string()
      in (printf("~A\n", cmd),
          let rc := shell(cmd)
          in (if ((lower(sys_name()) = "os/390" & not(rc % {0,4})) |
                  (lower(sys_name()) != "os/390" & not(rc % {0})))
                (printf("Link error - abort\n"),
                exit(1)))))]




// *******************************************************************
// *    Part 6: Creating new module (xl)                             *
// *******************************************************************

//<sb> we have a method that creates necessary directories for
// a module compilation. It is useful when working with CVS
// that, for instance, won't create all dirs with a checkout 
[ensure_module_directories_exist() : void ->
  if not(isdir?("include"))
    (//[0] ---- creating directory .~Ainclude // *fs*,
    mkdir("include")),
  if not(isdir?("include"))
    (//[0] ---- creating directory ~A // "include",
    mkdir("include")),
  if not(isdir?("csrc"))
    (//[0] ---- creating directory ~A // "csrc",
    mkdir("csrc")),
  if not(isdir?(compiler.env))
    (//[0] ---- creating directory ~A // compiler.env,
    mkdir(compiler.env))]

//<sb> creates a new module
// i.e. a init.cl and module directories
[new_module(l:list[string]) : void ->
  let p := explode(l[1], *fs*)
  in (if (length(p) > 2) error("option -nm <[partof/[version/]]module> [m f.cl f.cpp ...]"),
    try
      (if isdir?(last(p)) error("The Directory ~A already exists", last(p)),
      if isfile?(last(p) / "init.cl") error("~A already exists", last(p) / "init.cl"),
      //[0] ==== Creating new module ~A ==== // last(p),
      mkdir(last(p)),
      mkdir(last(p) / "include"),
      mkdir(last(p) / "source"),
      mkdir(last(p) / "csrc"),
      mkdir(last(p) / compiler.env),
      let init := fopen(last(p) / "init.cl", "w")
      in (use_as_output(init),
        printf("\n// init file for module ~A", last(p)),
        printf("\n// created ~A by claire v~A\n\n", strftime("%c",now()), release()),
        if (length(p) = 2) l[1] := p[1] //printf("(use_module(\"~A\"))\n",p[1]),
        else if (length(p) = 3) l[1] := (p[1] / p[2])
        else l :<< 1,
        let done := list<string>() //<sb> using a set may desorder the list...
        in for j in list{i in l|not(match_wildcard?(i,"*.*")) | match_wildcard?(i,"*/*")}
            (if not(j % done)
              (done :add j,
              use_module(j),
              use_as_output(init),
              printf("(use_module(\"~A\"))\n", j))),
        printf("\n\n~A :: module(\n", last(p)),
        if (length(p) = 2) printf("\tpart_of = ~A,\n", p[1]),
        printf("\tuses = list("),
        let first? := true
        in (if (length(p) = 2) (princ(p[1]), first? := false),
          for j in list{i in l|not(match_wildcard?(i,"*.*")) | match_wildcard?(i,"*/*")}
            (if first? first? := false else princ(", "),
            princ(explode(j,*fs*)[1])),
          if first? princ("Core")),
        printf("),\n"),
        printf("\tmade_of = list("),
        let first? := true
        in (for j in list{i in l|match_wildcard?(i,"*.*") & not(match_wildcard?(i,"*/*"))}
            (if first? first? := false else princ(", "),
            if match_wildcard?(j,"*.h*")
              fclose(fopen(last(p) / "include" / j, "w"))
            else fclose(fopen(last(p) / "source" / j, "w")),
            printf("\"~A\"",j))),
        printf("),\n"),
        printf("\tsource = \"source\",\n"),
        printf("\tversion = \"v1.0.0\") // put your version here\n\n\n"),
        if (length(p) = 2) printf("(begin(~A))\n",p[1]),
        printf("(load(~A))\n", last(p)),
        if (length(p) = 2) printf("(end(~A))\n",p[1]),
        
        printf("\n\n// Here you can customize the C++ compiler.\n// You can uncomment and set any of the following option :\n\n"),
        printf("// ==== external libraries needed at link time ====\n"),
        printf(";(compiler.libraries :add \"-lsome_lib\")\n\n"),
        printf("// ==== C++ compiler options ====\n"),
        printf(";(compiler.options[1] :/+ \"-a_cpp_option\") // Optimize mode (-O)\n"),
        printf(";(compiler.options[2] :/+ \"-a_cpp_option\") // Debug mode (-D)\n"),
        printf(";(compiler.options[3] :/+ \"-a_cpp_option\") // Release mode\n\n"),
        
        printf("\n// Here you can customize the CLAIRE compiler.\n// You can uncomment and set any of the following option :\n\n"),
        printf("// ==== compiler safety ====\n// 0 -> super safe\n// 1 -> safe\n// 2 -> trust explicit types & super\n// 3 -> no overflow checking\n// 4 -> assumes no selector or range error\n// 5 -> assume no type errors of any kind\n"),
        printf(";(compiler.safety := 1)\n\n"),
        printf("// ==== compiler naming convention ====\n// 0 -> long & explicit names\n// 1 -> shorter names\n// 2 -> protected names\n"),
        printf(";(compiler.naming := 0)\n\n"),
        printf("// ==== compiler inline flag ====\n// set it to true if you want to include inline definitions in the generated library\n"),
        printf(";(compiler.inline? := false)\n\n"),
        printf("// ==== compiler overflow flag ====\n// set it to true to produce safe code with respect to owerflow\n"),
        printf(";(compiler.overflow? := false)\n\n"),
        printf("// ==== fast dispatch flag ====\n"),
        printf(";(FCALLSTINKS := false)\n\n"),
        
        printf("\n// Here you can customize the CLAIRE code generator.\n"),
        printf("// Some symbol may be reserved in the target language,\n"),
        printf("// for such symbol you have to define a translation :\n\n"),
        printf(";(Generate/C++PRODUCER.Generate/bad_names :add some_symbol)\n"), 
        printf(";(Generate/C++PRODUCER.Generate/good_names :add symbol!(\"some_symbol_translated\"))\n\n"),

        fclose(init)))
    catch any (use_as_output(stdout),
          printf("~S\n",exception!()), exit(1)),
    exit(0))]

// *******************************************************************
// *    Part 7: Export/publish module (xl)                           *
// *******************************************************************



//<sb> how to copy a module to an exported form (recursive)
[rcopy(fr:string, to:string) : void ->
  let m := explode(to,*fs*),
    tmp := (if (compiler.env = "ntv") left(to,2)
        else if (length(to) > 0 & to[1] = '/') "/"
        else ".")
  in (for i in m
      (if (length(i) > 0 & not(compiler.env = "ntv" & i = left(to,2)))
        (tmp :/ i,
        if not(isdir?(tmp)) mkdir(tmp)))),
  for i in entries(fr)
    (if isfile?(fr / i)
      (fcopy(fr / i, to / i),
      chmod(to / i, 33188))
    else if not(fr % {"CVS", ".svn"})
      rcopy(fr / i, to / i))]

//<sb> how to export/publish a module
// %ov tell wether we can overwrite an existing export
[export_module(exp?:boolean) : void ->
  try (
    if not(isfile?("init.cl"))
      error("The current directory doesn't not contain an init.cl file"),
    let ms := last(explode(pwd(),*fs*)),
        ext := (if (compiler.env = "ntv") ".obj" else ".o")
    in (if not(isfile?(compiler.env / ms /+ ext))
        error("Attempt to ~A the module ~A that does not have any lib yet, compile the module ~A first",
                  (if exp? "export" else "publish"), ms, ms)),
    let hom := realpath(home_path() / ".." / "..")
    in (if (not(exp?) & %sudo)
        (//[0] ---- note: attempt to publish ~A at ~A // last(explode(pwd(),*fs*)), hom,
        //[0] ==== Require permission for publication ====,
        print_in_string(),
        printf("sudo ~A ~I -publish\n",
              params()[1],
              (if %ov princ(" -ov"))),
        if (shell(end_of_string()) != 0)
          exit(1),
        exit(0)),
      load("init"),
      let m := last(explode(pwd(),*fs*)),
        mod := get_value(m),
        fm := (m / (when v := get(version, mod) in v else
              (//[0] ---- note: ~S.version undefined, default is [v0.0.0] // mod,
              "v0.0.0"))),
        libs := explode(getenv("CLAIRE_LIBS"),*ps*),
        p := (if not(exp?) hom / "lib"
          else case %export
            (integer
              (if (%export < 1 | %export > length(libs))
                error("-export ~A, ~A is a invalid index for CLAIRE_LIBS [~A]", %export, %export, libs),    
              libs[%export]),
            string
              (if not(%export % libs)
                //[0] ---- warning: ~A not found in CLAIRE_LIBS environment variable // %export,
              %export),
            any
              (if not(libs)
                error("export path ommited, can't guess it since environment variable CLAIRE_LIBS is undefined"),
              libs[1]))),
        mod_home := p / fm / ("v" /+ release() /+ "-" /+ env(compiler))
      in (//[0] ==== ~A ~A ==== // (if exp? "Export" else "Publish"), fm, 
        if (not(%ov) & isdir?(p / fm)) error("Sorry, directory ~S already exists (try with -ov to overwrite)", p / fm),
        if not(isdir?(p / fm)) //[0]      creating ~A // p / fm, 
        if not(isdir?(p / m)) mkdir(p / m),
        if not(isdir?(p / fm)) mkdir(p / fm),
        //[3]      copying files in ~A // p / fm,
        //[3]      init.cl, include, source and lib,
        fcopy("init.cl", p / fm / "init.cl"),
        chmod(p / fm / "init.cl", 33188),
        rcopy(env(compiler), mod_home),
        for i in entries("include", "*.h*")
          (fcopy("include" / i, mod_home / i),
          chmod(mod_home / i, 33188)),
        rcopy("include", mod_home),
        rcopy(mod.source, p / fm / mod.source),
        if isdir?("docs")
          rcopy("docs", p / fm / "docs"),
        //[3] == Call exported callback,
        try apply(get_value(mod, "exported"), list(exp?, %ov, p / fm,home_path()))
        catch any none, 
        //[0] Time : ~A // strftime("%c", now()),
        //[0] ==== ~A ~A ==== // fm, (if exp? "exported" else "published")
        )))
    catch any (printf("~S\n",exception!()), exit(1)),
    exit(0)]

// *******************************************************************
// *    Part 8: Recompiling module (xl)                              *
// *******************************************************************

//<sb> with -cls & -call some compiler options are relayed to the sub-process
[relayed_params() : string ->
  let res := " -qonerror", len := length(params())
  in (for i in (1 .. len)
      (if (params()[i] = "-s" & i + 2 <= len)
        (res :/+ " -s " /+ params()[i + 1] /+ " " /+ params()[i + 2])
      else if (params()[i] = "-cpp" & i + 1 <= len)
        (res :/+ " -cpp \'" /+ params()[i + 1] /+ "\'")
      else if (params()[i] = "-make" & i + 1 <= len)
        (res :/+ " -make \'" /+ params()[i + 1] /+ "\'")
      else if (params()[i] = "-link" & i + 1 <= len)
        (res :/+ " -link \'" /+ params()[i + 1] /+ "\'")
      else if (params()[i] = "-os" & i + 1 <= len)
        (res :/+ " -os " /+ params()[i + 1])
      else if (params()[i] % {"-relink", "-auto","-p","-safe","-zerobuffer","-noel","-color"})
        (res :/+ " " /+ params()[i])  
      ),
    if (verbose() != 0)
      res :/+ (" -v " /+ string!(verbose())), //<sb> transmit verbose
    " " /+ res)]



[compile_module_libs() : void ->
  let m := last(explode(pwd(),*fs*)),
    -D? := false,
    -O? := false,
    opts := ""
  in (for i in (1 .. length(params()))
      let p := params()[i]
      in case p
        ({"-D"} -D? := true,
        {"-O"} -O? := true,
        {"-chdir"} i :+ 1,
        {"-call", "-cls", "-both", "-ov", "-publish", "-export"} none,
        any opts :/+ " " /+ p),
    if (%both | -D?)
      (//[0] ==== Compile ~A's debug library ==== // m,
      if (shell(opts /+ " -D -cl") != 0) exit(1)),
    if (%both | not(-D?) | -O?)
      (if (compiler.optimize?)
        (//[0] \n\n==== Compile ~A's release library (optimized) ==== // m,
        if (shell(opts /+ " -O -cl") != 0) exit(1))
      else (//[0] \n\n==== Compile ~A's release library ==== // m,
        if (shell(opts /+ " -cl") != 0) exit(1))))]

[compile_all_module_libs() : void ->
  if (length(getenv("CLAIRE_LIBS")) = 0) setenv("CLAIRE_LIBS=..")
  else setenv("CLAIRE_LIBS=.."  /+ *ps* /+ getenv("CLAIRE_LIBS")),
  let mls := list{i in entries(".")|isdir?(i) & isfile?(i / "init.cl")},
    mods := list<module>(),
    opts := ""
  in (if not(mls)
      (//[0] ---- warning: there is no module folder in ~A // pwd(),
      exit(1)),
    //[0] ==== Compile all modules from ~A ==== // pwd(),
    let i := 1
    in (while (i <= length(params()))
        let p := params()[i]
        in (if (p = "-call") none
          else if (p = "-chdir") i :+ 1
          else opts :/+ " " /+ p,
          i :+ 1)),
    Reader/set_load_module(false), //<sb> prevent the module to be meta-loaded
    for i in mls
      let m := get_value(i)
      in (if (unknown?(m) | not(m % module))
          (//[3] ==== note: load module ~A ==== // i,
          read("begin(claire)"),
          setcwd(i),
          load("init.cl"),
          setcwd(".."),
          when mm := get_value(i)
          in (mods :add mm as module,
            mods := Reader/add_modules(mods)))), //<sb> recompile modules in the right order!
    if (length(%em) > 0)
      let mm := get_value(%em)
      in (case mm
          (module
            let on_mods := list<module>(mm)
            in mods := Reader/add_modules(on_mods),
          any error("Unknown module specified in option -call -em ~A", %em))),
    if (length(%sm) > 0)
      let mm := get_value(%sm)
      in (case mm
          (module
            let nmods := copy(mods)
            in (for m in mods
                let dep := Reader/add_modules(list<module>(m))
                in (if not(mm % dep)
                    (for mdep in dep
                      nmods :delete mdep)),
              mods := nmods),
          any error("Unknown module specified in option -call -sm ~A", %sm))),
    //[0] ==== Recompile ~A ==== // list{m in mods|isdir?(external!(m))},
    for mm in list{m in mods | external!(m) % mls}
      (//[0] \n\n\n\n =============================================,
      //[0] == Module ~S // mm,
      //[0] =============================================,
      //[3] ---- note: enter directory ~A // external!(mm),
      setcwd(external!(mm)), //<sb> enter module dir and compile it
      if (shell(opts /+ " -qonerror -cls") != 0)
        exit(1),
      //[3] ---- note: leave directory ~A // external!(mm),
      setcwd("..")),
    //[0] ==== ~A recompiled ==== // list{m in mods|isdir?(external!(m))},
    exit(0))]

  
// *******************************************************************
// *    Part 9: Listing exported/published module (xl)               *
// *******************************************************************


[module_list(l:list[string]) : void ->
    let f := realpath(getenv("_")),
    hom := (realpath(substring(f, 1, rfind(f,*fs*) - 1) / ".." / ".." / "..") / "lib"),
    mp := list{e in entries(hom)|isdir?(hom / e)},
    libs := explode(getenv("CLAIRE_LIBS"),*ps*),
    ml := list{tuple(i, list{m in entries(i)|isdir?(i / m)})|i in libs},
    sub := ((if l l[1] else ("v" /+ release())) /+ "-" /+ (l :<< 1, if l l[1] else compiler.env))
  in (//[0] ==== Query available modules for ~A ==== // sub,
    if mp
      (//[0] ==== Published modules [~A] ==== // hom,
      for m in mp
        (printf("   ~A: ", m),
        let first? := true,
          lver := list{v in entries(hom / m)|isdir?(hom / m / v) & isfile?(hom / m / v / "init.cl") &
                            isdir?(hom / m / v / sub)}
        in (if not(lver) printf("unavailable for ~A", sub)
          else for v in lver
            (if first? first? := false else princ(", "),
            printf("~A", v))),
        princ("\n"))),
    for l in ml
      (if l[2] //[0] ==== Exported modules [~A] ==== // l[1],
      for m in l[2]
        (printf("   ~A: ", m),
        let first? := true,
          lver := list{v in entries(l[1] / m)|isdir?(l[1] / m / v) & isfile?(l[1] / m / v / "init.cl") &
                            isdir?(l[1] / m / v / sub)}
        in (if not(lver) printf("unavailable for ~A", sub)
          else for v in lver
            (if first? first? := false else princ(", "),
            printf("~A",v))),
        princ("\n"))),
    exit(0))]

[module_info(l:list[string]) : void ->
  if not(l) invalid_option_argument(),
  let m := l[1]
  in (l :<< 1,
    if not(l)
      let f := realpath(getenv("_")),
        hom := (realpath(substring(f, 1, rfind(f,*fs*) - 1) / ".." / ".." / "..") / "lib"),
        libs := explode(getenv("CLAIRE_LIBS"),*ps*),
        found := false
      in (if isdir?(hom / m)
          for v in list{e in entries(hom / m)|isdir?(hom / m / e)}
            (found := true,
            if (shell(params()[1] /+ relayed_params() /+ " -mi " /+ m /+ " " /+ v) != 0) exit(1)),
        for lb in libs
          (if isdir?(lb / m)
            for v in list{e in entries(lb / m)|isdir?(lb / m / e)}
              (found := true,
              if (shell(params()[1] /+ relayed_params() /+ " -mi " /+ m /+ " " /+ v) != 0) exit(1))),
        if not(found)
          (printf("There is no module module ~A.\n", m),
          exit(1)))
    else
      let f := realpath(getenv("_")),
        hom := (realpath(substring(f, 1, rfind(f,*fs*) - 1) /
              ".." / ".." / "..") / "lib"),
        libs := explode(getenv("CLAIRE_LIBS"),*ps*),
        v := l[1], pub? := isdir?(hom / m / v),
        sub := ("v" /+ release() /+ "-" /+ compiler.env),
        mp := ""
      in (if pub? mp := hom / m / v
        else for p in libs
            (if isdir?(p / m / v) (mp := p / m / v, break())),
        if not(isdir?(mp))
          (printf("The module ~A with version ~A doesn't exists.\n", m, v),
          exit(1)),
        printf("==== module ~A version ~A ====\n", m, v),
        printf("- ~A at ~A\n", (if pub? "Published" else "Exported"), mp),
        verbose() := -1,
        Reader/set_load_module(false), //<sb> prevent the module to be loaded
        load(mp / "init.cl"),
        verbose() := 0,
        when mod := get_value(m)
        in (printf("- Uses ~A\n", mod.uses),
          for am in (Reader/add_modules(list<module>(mod)) delete mod)
            (if known?(version, am)
              printf("- Depends on ~S ~A\n", am, am.version)
            else printf("- Depends on ~S\n", am)))
        else (printf("~A doesn't defines the module ~A, please fix this init file.\n", mp / "init.cl", v),
            exit(1))),
    exit(0))]


[list_fcall() : void ->
  load("init"),
  %cm := get_value(last(explode(pwd(),*fs*))),
  printf("==== list of uniform property for ~S ====\n", %cm),
  for p in list{p in property|((unknown?(mClaire/definition,p.name) & get(module!,p.name) = %cm) | p.name.mClaire/definition = %cm) &
          length(p.restrictions) > 1 & Core/uniform(p)}
    printf("``BLACK~S ~I`BLACK\n~I",
      p, (if (p.mClaire/dispatcher > 0) princ("`REDinterface")),
      (for r in p.restrictions printf("  ~S\n", r))),
  exit(0)]





option_usage(opt:{"-env"}) : tuple(string, string, string) ->
  tuple("Compiler environment",
      "-env <env:string>",
      "Sets the compiler environment to <env>. This is an expert option " /+
      "used for cross-compilation.")

[option_respond(opt:{"-env"}, l:list) : void ->
  if not(l) invalid_option_argument(),
  compiler.env := l[1],
  l << 1]


option_usage(opt:{"-m", "-l"}) : tuple(string, string, string) ->
  tuple("Link with module",
      "-m <m:module>[/<version:string>] | -l <library:path>",
      "claire <-m> <m> loads the module <m> in the system and add it to the list of linked modules. " /+
      "You may specify a <version> to focus on particular version of the module.\n" /+
      "You may additionnaly link with a particular library using the <-l> option.")


[option_respond(opt:{"-m", "-l"}, l:list) : void ->
  if not(l) invalid_option_argument(),
  let mod := l[1] as string
  in (l << 1,
    case opt
      ({"-m"}
        (use_module(mod),
        let m := string2module(explode(mod,*fs*)[1])
        in (load(m),
          claire_modules :add m)),
      {"-l"}
        compiler.libraries :add mod))]


option_usage(opt:{"-od"}) : tuple(string, string, string) ->
  tuple("Output directory",
      "-od <directory:path>",
      "Sets the output directory for generated C++ files.")

[option_respond(opt:{"-od"}, l:list) : void ->
  if not(l) invalid_option_argument(),
  compiler.source := l[1],
  l << 1]


option_usage(opt:{"-safe", "-os"}) : tuple(string, string, string) ->
  tuple("Safety",
      "-safe | -os <safety:(0 .. 6)>",
      "Controls compiler safety. <-safe> put the compiler in the safest mode " /+
      "and <-os> set the safety to a particular level :\n" /+
      "0 : Super-safe, the type of each value returned by a method is checked against its " /+
        "range, and the size of the GC protection stack is minimized. All assertions are checked.\n" /+
      "1 : Safe (default).\n" /+
      "2 : We trust explicit types & super. The type information contained in local variable " /+
        "definition (inside a let) and in a super (f@c(...)) has priority over type inference " /+
        "and run-time checks are removed.\n" /+
      "3 : No overflow checking (integer & arrays), in addition to level 2.\n" /+
      "4 : We assume that there will be no selector errors or range errors at run-time. " /+
        "This allows the compiler to perform further static binding.\n" /+
      "5 : We assume that there will be no type errors of any kind at run-time.\n" /+
      "6 : Unsafe (level 5 + no GC protection). Assumes that garbage collection will " /+
        "never be used at run-time.")


[option_respond(opt:{"-safe"}, l:list) : void ->
  safety(compiler) := (if (dblevel = 0) 0 else 1),
  claire_lib := compiler.libraries_dir[2],
  claire_options := compiler.options[2]]

[option_respond(opt:{"-os"}, l:list) : void ->
  if not(l) invalid_option_argument(),
  slevel := integer!(l[1]),
  l << 1]


option_usage(opt:{"-o"}) : tuple(string, string, string) ->
  tuple("Output name",
      "-o <name:string>",
      "Sets the output executable file name.")

[option_respond(opt:{"-o"}, l:list) : void ->
  if not(l) invalid_option_argument(),
  %out := l[1],
  l << 1]


option_usage(opt:{"-D", "-O"}) : tuple(string, string, string) ->
  tuple("Optimization",
      "-D | -O",
      "Adjust the optimization level. <-D> generates a code instrumented for " /+
      "the CLAIRE debugger without any optimization (implicitely implies -debug). " /+
      "<-O> enable CLAIRE compiler optimization.")

[option_respond(opt:{"-D"}, l:list) : void ->
  Language/DEBUG? := true,
  dblevel := 0]

[option_respond(opt:{"-O"}, l:list) : void ->
  compiler.optimize? := true, dblevel := 2]


option_usage(opt:{"-p"}) : tuple(string, string, string) ->
  tuple("Profiler",
      "-p",
      "Enables profiling. The generated code is instrumented for profiling.")

[option_respond(opt:{"-p"}, l:list) : void ->
  OPT.profile? := true, dblevel :max 1]
  

option_usage(opt:{"-cpp", "-link", "-make"}) : tuple(string, string, string) ->
  tuple("C++ compiler",
      "-cpp <cxxoption:string> | -link <linkeroption:string> | -make <makeroption:string>",
      "Customize the generated makefile by adding some options " /+
      "to the C++ compiler and linker command lines and additionaly some maker option.")

[option_respond(opt:{"-cpp"}, l:list) : void ->
  if not(l) invalid_option_argument(),
  cppopts :/+ " " /+ l[1],
  l << 1]

[option_respond(opt:{"-make"}, l:list) : void ->
  if not(l) invalid_option_argument(),
  l << 1]

[option_respond(opt:{"-link"}, l:list) : void ->
  if not(l) invalid_option_argument(),
  linkopts :/+ " " /+ l[1],
  l << 1]


option_usage(opt:{"-cm", "-cc", "-cl"}) : tuple(string, string, string) ->
  tuple("Compile module",
      "{-cc | -cl | -cm} [<m:module>]",
      "Compile the module <m>. If <m> is unspecified the last module defined in the init.cl " /+
      "from the current directory is taken.\n" /+
      "The <-cc> option is the lightest compiling strategy for a module: claire <-cc> will " /+
      "produce a C++ file for each claire file in <m>.made_of. It does not produce a makefile " /+
      "or system file, and assumes that the user want to keep a complete control over the generation " /+
      "of the executable.\n" /+
      "A more friendly option is <-cl>, which adds a linking step so that all generated C++ files are " /+
      "compiled and linked into a library <m>.lib (the name of the library can be redefined with -o or " /+
      "by using the external slot of the module).\n" /+
      "The easier way to use the compiler is the <-cm> option which produces an executable from a module. " /+
      "It is similar to <-cl>, but in addition it produces a system file for the module that is being " /+
      "compiled and a makefile which is executed by claire, producing an executable that includes the interpreter.")

[option_respond(opt:{"-cm", "-cc", "-cl"}, l:list) : void ->
  if not(isfile?("init.cl"))
    error("Option ~A used outside a module directory", opt),
  ensure_module_directories_exist(),
  //TODO: if <m>
  //if l let m := get_value(l[1]) in
    //case m (module 
  %cm := last(explode(pwd(),*fs*)),
  case opt
    ({"-cc"} clevel := 0,
    {"-cm"} clevel := 2)]


option_usage(opt:{"-both", "-cls", "-call", "-sm", "-em"}) : tuple(string, string, string) ->
  tuple("Compile module library",
      "[-both] {-cls | -call [-sm <m:module>] [-em <m:module>]}",
      "<-cls> compiles a release module library for the current module. " /+
      "When <-both> is specified a debug version is also generated.\n" /+
      "<-call> attempts to do so for a set of module located in subdirectories. " /+
      "If <-sm> (resp. <-em>) is specified (and match a module located in a sub directory) " /+
      " then any modules before (resp. after) this one are not recompiled.")

[option_respond(opt:{"-both"}, l:list) : void -> %both := true]
[option_respond(opt:{"-cls"}, l:list) : void -> %cls := true]
[option_respond(opt:{"-call"}, l:list) : void -> %call := true]


option_usage(opt:{"-sudo", "-ov", "-publish", "-export"}) : tuple(string, string, string) ->
  tuple("Module publication",
      "[-sudo] [-ov] {-publish | -export [<i:integer> | <directory:path>]}",
      "Perform a module publication. A published module can be used " /+
      "by other modules or linked with a program (see option <-m>). " /+
      "The publication consist of a copy of the module (i.e. headers, library, init file and sources).\n" /+
      "With the <-publish> option, the copy is placed in the CLAIRE home folder. " /+
      "It is intended for general purpose modules that may be used by any program. " /+
      "According to the permission of the current user, the publication may fail. One, " /+
      "that have sudoer privileges may specify <-sudo> option such the copy is acheived " /+
      "from a sudoed process.\n" /+
      "The <-export> option is an alternative that allow local publication. The user " /+
      "may define a CLAIRE_LIBS environment variable that tell CLAIRE where to find " /+
      "exported modules. CLAIRE_LIBS should contain a list of path separated by a " /+
      "'" /+ *ps* /+ "' (path separator). The path where the module is exported " /+
      "is determined as follow :\n" /+
      "- The <i>th path of CLAIRE_LIBS list\n" /+
      "- The given <directory>\n" /+
      "- By default, the first path of CLAIRE_LIBS list\n" /+
      "Last, one have to specify <-ov> to force the overwrite of an existing publication.")

[option_respond(opt:{"-sudo"}, l:list) : void -> %sudo := true]
[option_respond(opt:{"-ov"}, l:list) : void -> %ov := true]
[option_respond(opt:{"-publish"}, l:list) : void -> %publish := true]
[option_respond(opt:{"-sm"}, l:list) : void ->
  if not(l) invalid_option_argument(),
  %sm := l[1],
  l << 1]
[option_respond(opt:{"-em"}, l:list) : void ->
  if not(l) invalid_option_argument(),
  %em := l[1],
  l << 1]

[option_respond(opt:{"-export"}, l:list) : void ->
  %publish := true,
  %export := true,
  if l
    let opt := l[1]
    in (if (integer!(opt) > 0)
        (l << 1,
        %export := integer!(opt))
      else if isdir?(opt)
        (l << 1,
        %export := opt))]


option_usage(opt:{"-nm"}) : tuple(string, string, string) ->
  tuple("New module",
      "-nm [<partof:module>/]<name:string> +[<m:module> | <f:filename>{.cpp | .cl | .h}]",
      "Create a new module with name <name>. If <partof> is specified the new module " /+
      "is created as a part of <partof>. You may specify a list of used module <m> and a " /+
      "list of source file <f> for this module.\n" /+
      "A new directory is created with the name of the module, it contains an init.cl " /+
      "that defines the CLAIRE instance, when specified subdirectories containing emtpy source files " /+
      "are also created.\n" /+
      "The option <-nm> is always the last command line option, following arguments have to " /+
      "be a module (<m>) or a source file (<f>).")

[option_respond(opt:{"-nm"}, l:list) : void -> new_module(l)]
  

option_usage(opt:{"-ml", "-mi"}) : tuple(string, string, string) ->
  tuple("Module info",
      "-ml | {-mi <m:module>[/<version:string>]}",
      "Provide a list of available module or with <-mi> informations " /+
      "relative to a partivular module.\n" /+
      "These options are always the last command line option, following arguments are " /+
      "ignored.")

[option_respond(opt:{"-ml"}, l:list[string]) : void -> module_list(l)]
[option_respond(opt:{"-mi"}, l:list[string]) : void -> module_info(l)]


option_usage(opt:{"-cx"}) : tuple(string, string, string) ->
  tuple("Configuration file",
      "-cx <test:path>",
      "When claire <-cx> <test> is invoked, the compiler takes a claire configuration file <test>, " /+
      "produces an equivalent C++ file and another C++ file called the system file. The first " /+
      "file is named <test>.cpp and the second file is named <test>-s.cpp. They are both placed " /+
      "in the directory source(compiler). The output name may be is changed with the <-o> option. " /+
      "The generated files are compiled and linked directly by claire. This is done by producing a " /+
      "makefile <test>.mk that links the generated binaries with the necessary claire modules. The " /+
      "option <-cx> is used to generate multi-module executable and is aimed at serious claire developers. " /+
      "A configuration file is a file that contains only methods without any type-checking ambiguity.")

[option_respond(opt:{"-cx"}, l:list) : void ->
  if not(l) invalid_option_argument(),
    %cf := l[1],
    l << 1,
    clevel := 2]


option_usage(opt:{"-n"}) : tuple(string, string, string) ->
  tuple("No init",
      "-n",
      "Prevent to load an init.cl file that is loaded by default.")

[option_respond(opt:{"-n"}, l:list) : void -> %init? := false]


option_usage(opt:{"-fcall"}) : tuple(string, string, string) ->
  tuple("Fast dispatch",
      "-fcall",
      "Prints a list of uniform properties candidate for fast dispatch and exits.")

[option_respond(opt:{"-fcall"}, l:list) : void -> list_fcall()]
  

option_usage(opt:{"-noConsole", "wclConsole"}) : tuple(string, string, string) ->
  tuple("Console",
      "-noConsole | -wclConsole",
      "Do not build an interpreter. <-wclConsole> is used to generate a web " /+
      "agent that works behind an HTTP server (e.g. behind mod_wcl & Apache).")

[option_respond(opt:{"-noConsole", "-wclConsole"}, l:list) : void ->
  claire_modules :delete Language, //<sb> noConsole mode
  claire_modules :delete Reader,
  case opt
    ({"-noConsole"} compiler.libraries :add "noConsole",
    {"-wclConsole"} compiler.libraries :add "wclConsole")]
 
 
[option_parsed() : void ->
  if %cls compile_module_libs()
  else if %call compile_all_module_libs()
  else if (length(%cf) > 0 | length(%cxf) > 0 | length(%cm) > 0)
    (if (%out = "")
      (if (%cm != "") %out := %cm
      else if (%cf != "") %out := replace(%cf,".cl","")),
    if %init?
      (if not(clcc?) Reader/set_load_module(false),
      load("init")),
    if (length(cppopts) > 0)
      (compiler.options[1] :/+ " " /+ cppopts /+ " ",
      compiler.options[2] :/+ " " /+ cppopts /+ " ",
      compiler.options[3] :/+ " " /+ cppopts /+ " "),
    if (length(linkopts) > 0)
      compiler.libraries :add " " /+ linkopts,
    claire_options :=  compiler.options[(if (dblevel = 0) 2 else if (dblevel = 2) 1 else 3)],
    claire_lib := compiler.libraries_dir[(if (dblevel = 0) 2 else if (dblevel = 2) 1 else 3)],
    if (slevel > 0) compiler.safety := slevel,        // v3.3.26
    if (%cm != "")
      let m := string2module(%cm) in
      (compiler.active? := true,
      if (m.uses = list(claire_modules[2]))
        (//claire_modules := shrink(claire_modules,2), //<sb> rm -> noConsole option
        trace(0,"=== Light Module ~S uses ~A ===\n", m, m.uses)),
      claire_modules :add m,
      load(get_value("Compile")),
      if (%out != "") external(m) := %out,
      if clcc?
        load(m),
      if (dblevel < 1) (compiler.safety :min 4, compiler.debug? :add m),
      if clcc?
        compile(m),
      if (clevel = 1)
        (if (%out != "") m.external := %out, cmakefile(m,""))
      else if (clevel = 2) cmakefile(m,%out),                       // v3.2.12: level = 0 => do nothing ....
      exit(0))
    else if (%cj != "")
       apply(get_value("jcmakefile") as property, list(string2module(%cj), %out, (clevel = 0)))
    else if (%cf != "")
       (compiler.active? := true,
      load(get_value("Compile")),
      load(%cf),
      if (not(match_wildcard?(%cf,"*.cl")) & isfile?(%cf /+ ".cl")) %cf :/+ ".cl",
      function_compile(replace(%cf,".cl",""), %cf),
      cmakefile(replace(%cf,".cl",""),%out),
      exit(0))
    else if (%cxf != "")
       (compiler.active? := true,
      load(get_value("Compile")),
      load(%cxf),
      if (not(match_wildcard?(%cxf,"*.cl")) & isfile?(%cxf /+ ".cl")) %cxf :/+ ".cl",
      function_compile(replace(%cxf,".cl",""), %cxf),
      exit(0))),
  if %publish
    export_module(%export != false),
  if %cls exit(0)]


[option_respond(opt:{"-skipcl"}, l:list[string]) : void ->
  clcc? := false]

[option_usage(self:{"-skipcl"}) : tuple(string, string, string) ->
  tuple("Compile from C++ source",
      "-skipcl",
      "Compile only C++ sources but not claire sources")]

