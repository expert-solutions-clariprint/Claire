ttt :: timer!()

(printf("===================================\n"))
(printf("====           STEP 1           ===\n"))
(printf("===================================\n"))

(compiler.inline? := false,
compiler.naming := 1,
PRODUCER.Generate/extension := ".cpp",
verbose() := 2,
compiler.safety := 5,
compiler.optimize? := false,
compiler.headers_dir := "include",
compiler.source := "csrc1")

(if not(isdir?("csrc1")) mkdir("csrc1"))
(if not(isdir?("csrc")) mkdir("csrc"))

Core/RELEASE :: version()


(compile(Core))
(compile(Serialize))
(compile(Language),
compiler.inline? := true)
(compile(Reader))
(compile(Optimize))
(compile(Generate))

(PRODUCER.Generate/extension := ".cpp",
Generate/generate_s_file("claire",list(Core,Serialize,Language,Reader,Optimize,Generate),claire))

(printf("Compiled in ~I\n", uptime(ttt)))
