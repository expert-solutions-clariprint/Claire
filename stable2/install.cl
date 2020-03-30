//*********************************************************************
//* CLAIRE                                            Sylvain Benilan *
//* install.cl                                                        *
//* Copyright (C) 2000 - 2003 xl. All Rights Reserved                 *
//*********************************************************************


/*********************************************************************/
/** Contents                                                         */
/**    0. setup                                                      */
/**    1. various check                                              */
/**    2. install                                                    */
/**    3. terminate installation                                     */
/*********************************************************************/


/*********************************************************************/
/**    0. setup                                                      */
/*********************************************************************/

(if (compiler.env = "ntv")
  (have_prefix? := false,
  claire_prefix := getenv("CLAIRE_PREFIX"),
  if (claire_prefix = "")
    claire_prefix := "C:\\dev"))

//<sb> this is an installation script for the CLAIRE XL release on unix and windows
// this script create a claire-vXX directory in your <claire_prefix> directory
// 'make install' executes this script
(if not(isenv?("CLAIRE_INSTALL"))
	(printf("==== Installing CLAIRE v~A - ~A ====\n", release(), compiler.env),
	//<sb> the variable have_prefix? is set to true when configure
	// is run with --prefix=<claire_prefix>
	// on a PC you can change claire_prefix in the init.cl file
	if not(have_prefix?) princ("Default "),
	printf("~Anstallation prefix is ~A, the script will:\n~I~I",
		(if have_prefix? "I" else "i"),
		claire_prefix,
		(if not(isdir?(claire_prefix / "claire" / "lib")) printf("  - create ~A\n", claire_prefix / "claire"  / "lib")),
		(let p := (claire_prefix / "claire"  / ("claire-v" /+ release()))
		in printf("  - ~A ~A\n", (if isdir?(p) "overwrite" else "create"), p)))))


/*********************************************************************/
/**    1. various check                                              */
/*********************************************************************/

INSTALL_DIR :: (claire_prefix / "claire")


(if not(isdir?(claire_prefix))
	(printf("Install directory ~A doesn't exists - install aborted\n", claire_prefix),
	exit(1)))

//<sb> the default install checks that /usr/local/bin exists
(if (not(have_prefix?) & not(isdir?(claire_prefix / "bin")))
	(if not(compiler.env = "ntv")
		(printf("Directory ~A doesn't exists - install aborted\n", claire_prefix / "bin"),
		exit(1))))

//<sb> check that a claire binary exists
(if (compiler.env = "ntv")
	(if not(isfile?(compiler.env / "cclaire.exe"))
		(printf("File cclaire.exe doesn't exists - install aborted\n"),
		exit(1)))
else
	(if not(isfile?(compiler.env / "cclaire"))
		(printf("File cclaire doesn't exists, please run make before - install aborted\n"),
		exit(1))))


/*********************************************************************/
/**    2. install                                                    */
/*********************************************************************/

//<sb> the installation directory is organized as follow:
//
//  <claire_prefix>
//      + claire                           // we create a claire folder at root
//         + lib                           // where the publication of a user module <m> takes place with 'claire -publish'
//             [ + <m.name>
//                 + <m.version>
//                   + init.cl
//                   + source
//                   + <v<claire_release>-<arch-C++>>
//                      + release
//                      + debug
//             ] ...
//         + claire-v<claire_release>      // support for multiple claire version
//               + lib
//                   - Kernel.o
//                   - Core.o
//                   - ...
//               + include
//                   - claire.h
//                   - marie.h
//                   - Kernel.h
//                   - ...
//               + bin
//                   - claire[.exe]        // the claire binary


(try
	(printf("Install dir: ~A\n", INSTALL_DIR),
		
	// we install claire in a subdirectory that depends
	// on the underlying arch & C compiler
	if not(isdir?(INSTALL_DIR))
		mkdir(INSTALL_DIR),
	
	// where to find claire binary
	if not(isdir?(INSTALL_DIR / "bin"))
		mkdir(INSTALL_DIR / "bin"),
	
	// where to find claire headers
	if not(isdir?(INSTALL_DIR / "include"))
		mkdir(INSTALL_DIR / "include"),

	// where to find claire libs
	if not(isdir?(INSTALL_DIR / "lib"))
		mkdir(INSTALL_DIR / "lib"),

	// where to find claire doc
	if not(isdir?(INSTALL_DIR / "doc"))
		mkdir(INSTALL_DIR / "doc"),
		
	// copy headers
	printf("Installing CLAIRE headers...\n"),

	for h in entries("include", "*.h")
		(fcopy("include" / h, INSTALL_DIR / "include" / h),
		chmod(INSTALL_DIR / "include" / h, 33188)),
	
	// copy libs
	printf("Installing CLAIRE libraries...\n"),
	
	for lib in entries(compiler.env, "*.o")
		(fcopy(compiler.env / lib, INSTALL_DIR / "lib" / lib),
		chmod(INSTALL_DIR / "lib" / lib, 33188)),
	for lib in entries(compiler.env, "*.lib")
		(fcopy(compiler.env / lib, INSTALL_DIR / "lib" / lib),
		chmod(INSTALL_DIR / "lib" / lib, 33188)),
	for lib in entries(compiler.env, "*.x")
		(fcopy(compiler.env / lib, INSTALL_DIR / "lib" / lib),
		chmod(INSTALL_DIR / "lib" / lib, 33188)),

	
	if isdir?("doc")
  	(// copy doc
  	printf("Installing CLAIRE documentation...\n"),
  	for f in entries("doc")
  		(fcopy("doc" / f, INSTALL_DIR / "doc" / f),
  		chmod(INSTALL_DIR / "doc" / f, 33188))),
	
	// copy claire binary
	printf("Installing CLAIRE binary...\n"),
	
	if (compiler.env = "ntv")
		fcopy(compiler.env / "cclaire.exe", INSTALL_DIR / "bin" / "claire.exe")
	else if isfile?(compiler.env / "cclaire.exe")
		fcopy(compiler.env / "cclaire.exe", INSTALL_DIR / "bin" / "claire.exe") // cygwin has .exe extension
	else if isfile?(compiler.env / "cclaire")
		fcopy(compiler.env / "cclaire", INSTALL_DIR / "bin" / "claire"),

	for dll in entries(compiler.env, "*.dll")
		fcopy(compiler.env / dll, INSTALL_DIR / "bin" / dll),

	for dll in entries(compiler.env, "*.so")
		fcopy(compiler.env / dll, INSTALL_DIR / "bin" / dll),

	// by default if no prefix have been specified we install a link /usr/local/bin/claire
	// to our claire binary (check anyway what does the link and warn user)
	if not(have_prefix?)
		(if (not(compiler.env = "ntv"))
			(if not(isfile?(claire_prefix / "bin" / "claire"))
				(printf("---- note: install a default link ~A -> ~A\n", claire_prefix / "bin" / "claire", INSTALL_DIR / "bin" / "claire"),
				symlink(INSTALL_DIR / "bin" / "claire", claire_prefix / "bin" / "claire"))
			else if (realpath(claire_prefix / "bin" / "claire") = INSTALL_DIR / "bin" / "claire")
				printf("---- note: ~A already linked to ~A\n",
							claire_prefix / "bin" / "claire",
							INSTALL_DIR / "bin" / "claire")
			else printf("---- warning: ~A is linked to ~A\n",
							claire_prefix / "bin" / "claire",
							realpath(claire_prefix / "bin" / "claire")))))
catch any
	(printf("~S\n",exception!()),
	exit(1))) // exit with an error

/*********************************************************************/
/**    3. terminate installation                                     */
/*********************************************************************/

(if not(isenv?("CLAIRE_LIBS"))
	printf("---- note: please create a CLAIRE_LIBS environment variable such you can export your own modules. CLAIRE_LIBS should contain a list of path (seprated by a ~S) that tell claire compiler where to search for exported modules.\n", *ps*),
if (compiler.env = "ntv")
	// pc note
	(if not(for i in explode(getenv("PATH"),*ps*) (if (i = INSTALL_DIR / "bin") break(true)))
		printf("---- note: please add ~A to your PATH\n", INSTALL_DIR / "bin"))
else
	// unix note
	(if not(have_prefix?)
		(if not(for i in explode(getenv("PATH"),*ps*) (if (i = claire_prefix / "bin") break(true)))
			printf("---- note: please add ~A to your PATH\n", claire_prefix / "bin"))
	else (if not(for i in explode(getenv("PATH"),*ps*) (if (i = INSTALL_DIR / "bin") break(true)))
			printf("---- note: please add ~A to your PATH\n", INSTALL_DIR / "bin"))),
printf("==== Installed ====\n"))


(exit(0)) // OK :)
