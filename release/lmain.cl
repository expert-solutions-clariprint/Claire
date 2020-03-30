//*********************************************************************
//* CLAIRE                                            Sylvain Benilan *
//* install.cl                                                        *
//* Copyright (C) 2000 - 2003 xl. All Rights Reserved                 *
//*********************************************************************

//<sb> here is defined the lmain file used by a local loader (option -ll)
// a local loader contains all dependencies of a module and can be used
// to interpret a module


[main(lp:list[string]) : void ->
	if exists(h in {"-h", "-help"}|h % lp)
		(printf("usage: ~A [-h | -help] [-D] [-n]\n\n",params()[1]),
		printf("   -D: start the debbuger\n"),
		printf("   -n: do not load init.cl file\n"),
		exit(0)),
	if ("-D" % lp) debug(),
	if (not("-n" % lp) & isfile?("init.cl"))
		(load("init"),
		when m := get_value(last(explode(pwd(), *fs*)))
		in (//[0] ==== Local loader for module ~A version ~A === // last(explode(pwd(), *fs*)), get(version, m),
			begin(m))
		else //[0] --- warning: the init.cl file doesn't define a module ~A === // last(explode(pwd(), *fs*))
		)]
		