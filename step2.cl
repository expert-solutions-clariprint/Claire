
(load("version"))

ttt :: timer!()
(color(1))
(printf("=======================================\n"))
(printf("====              STEP 2            ===\n"))
(printf("=======================================\n"))
(printf("=== env : ~A\n", compiler.env))
(printf("=== external : ~A\n", compiler.external))
(printf("=== new version : v3.~I\n", print(VERSION)))

(PRODUCER.Generate/extension := ".cpp",
compiler.libraries_dir := list<string>("release", "debug", "release"),
compiler.inline? := true,
compiler.version := VERSION,
compiler.naming := 1,
verbose() := 2,
compiler.safety := 5,
compiler.optimize? := true,
compiler.headers_dir := "include",
compiler.source := "csrc")

//(Compile/FCALLSTINKS := true)

Core/RELEASE :: VERSION
(system.version := VERSION)


(compile(Core))
(compiler.inline? := false,
compile(Serialize),
compiler.inline? := true)
(compile(Language))
(compile(Reader))
(compiler.headers := list<string>())
(compiler.naming := 2) //<sb> generate encrytped C++ for the compiler
(compile(Optimize))
(compile(Generate))
(compiler.naming := 1)

(PRODUCER.Generate/extension := ".cpp",
Generate/generate_s_file("claire",list(Core,Serialize,Language,Reader,Optimize,Generate),claire))

(printf("Compiled in ~I\n", uptime(ttt)))
