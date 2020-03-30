// +----------------------------------------------------------------------+
// | init.cl                                                              |
// +----------------------------------------------------------------------+

// note the environment must be set-up through the -env declaration
// this file works for most UNIX and NT setups, you may need to edit it
// though

(compiler.inline? := true,       // do not change
OPT.Optimize/recompute := false,
compiler.naming := 1,
verbose() := 2,                  // not significant
compiler.safety := 5,            // do not change
compiler.headers_dir := "include",
compiler.source := "csrc",
if (compiler.env = "ntv")
  (PRODUCER.Generate/extension := ".cpp",
  // compiler options: optimized, debug, default
  compiler.options := list("-c /Ox", "-c /Ox", "-c /Ox"))
else
  (PRODUCER.Generate/extension := ".cpp",
  // compiler options: optimized, debug, default
  compiler.options := list("", "", ""),
  compiler.libraries_dir := list("release", "debug", "release")))

//<sb> handle installation prefix
(if (not(have_prefix?))
     (if (compiler.env = "ntv")
       claire_prefix := "C:\\dev" //<sb> change it manualy
     else claire_prefix := "/usr/local")) //<sb> use --prefix=<claire_prefix> with configure

(if (lower(sys_name()) % {"darwin"} & sys_compiler() = "g++")
  (ld_options := " -DCL64 -rdynamic",
  cxx_options := " -DCL64 -fPIC -DPIC",
  so_options := " -DCL64 -dynamiclib -undefined dynamic_lookup"))


(if (lower(sys_name()) % {"linux"} & sys_compiler() = "g++")
  (ld_options := " -rdynamic",
  cxx_options := " -fPIC -DPIC",
  so_options := " -fPIC -DPIC -rdynamic -shared"))

(if (lower(sys_name()) % {"sun", "sunos", "solaris"} & sys_compiler() = "g++")
  (ld_options := " -rdynamic",
  cxx_options := " -fPIC -DPIC",
  so_options := " -fPIC -DPIC -shared"))

(if (lower(sys_name()) % {"sun", "sunos", "solaris"} & sys_compiler() = "CC")
  (ld_options := " -Bdynamic",
  cxx_options := " -KPIC",
  so_options := " -KPIC -G"))

(if (lower(sys_name()) = "aix" & sys_compiler() = "g++")
  (ld_options := " -Wl,-bmaxdata:0x80000000 -Wl,-brtl -Wl,-bdynamic -Wl,-bexpfull",
  cxx_options := "",
  so_options := " -shared -Wl,-G")
else if (sys_name() = "aix")
  (ld_options := " -bmaxdata:0x80000000 -brtl -bdynamic -bexpfull",
  cxx_options := "",
  so_options := " -G -bM:SRE -bnoentry"))

(if (lower(sys_name()) = "os/390")
  (ld_options := " -W'l,xplink,compat=ZOSV1R9'",
  cxx_options := " -W'c,xplink,exportall,langlvl(extended),target(zOSV1R9)'",
  so_options := " -W'l,xplink,dll,compat=ZOSV1R9'"))

(if (lower(sys_name()) = "hp-ux")
  (ld_options := " -Wl,-E -Wl,+n",
  cxx_options := " +Z",
  so_options := " -Wl,-b"))

(if (lower(sys_name()) % {"linux"} & sys_compiler() = "g++")
  cxx_options :/+ " -Wno-write-strings")


// --------------------------------------------------------------------------
// when changing to a platform that requires a new makefile generator,
// one cannot use the existing old file to compile the new one. The following
// method may be used to cross-compile the new (revised) file once it is
// loaded
// THIS METHOD IS RESERVED FOR EXPERT USE ...
[ccmain() : void
  -> compiler.active? := true,
     begin(claire),
     Generate/*cf* := "ccmain",
     compiler.headers_dir := home() / "include",
     claire_lib := home() / "bin" / "debug" / compiler.env,
     compile("ccmain"),
     cmakefile("ccmain","cclaire")]
