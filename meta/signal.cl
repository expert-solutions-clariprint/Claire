//*********************************************************************
//* CLAIRE                                            Sylvain Benilan *
//* signal.cl                                                         *
//* Copyright (C) 2000 - 2005 xl. All Rights Reserved                 *
//*********************************************************************

// This file contains signal handling methods and some tools to
// manipulate the process signal mask.

// *********************************************************************
// *  Table of contents                                                *
// *   Part 1: signal handler definition                               *
// *   Part 2: signal API                                              *
// *   Part 3: signal mask                                             *
// *   Part 4: itimer                                                  *
// *   Part 5: waitpid                                                 *
// *********************************************************************

//<sb> @cat @xl Signal Handling
// @section Platform
// Starting with XL CLAIRE we can install an Interrupt Service Routine written in CLAIRE
// for a particular signal.
// Signals, in XL CLAIRE, are not true asynchronous event since they are
// always caught by the Kernel as a first step and redistributed to the meta
// code from an appropriate execution point (necessary to preserve 
// memory integrity) : the meta handling is always performed in the program execution
// flow (i.e. not in the stack of the signal handler) so that the code of the handler
// may be arbitrary complex.\br
// The signal interface is very similar to C interface, we use
// signal(sig:signal_handler, p:property) to install a signal handler :
// \code
// user_interrupt() : void -> error("User interrupt")
//
// (signal(SIGUSR1, user_interrupt))
// (raise(SIGUSR1)) // would throw the error above
// \/code
// Notice that in XL CLAIRE after the delivery of a signal the signal is always
// re-installed. To uninstall a handler one should use the special property SIG_DFL
// which correspond to a default handling :
// \code
// (signal(SIGUSR1, SIG_DFL))
// \/code
// We could also ignore a signal using the special property SIG_IGN :
// \code
// (signal(SIGUSR1, SIG_IGN))
// \/code
// Last, XL CLAIRE comes with another special property SIG_EXT that is set by default to
// a signal already installed at the time of CLAIRE initialization (as may be done by a
// library linked with CLAIRE).\br
// However, SIGINT is handled in a particular way (SIGINT is on most UNIX
// raised with the keyboard when the user types ^C - Control + C).
// The SIGINT handler, when set to SIG_DFL (default), throws a user interrupt error such to
// abort the current computation and come back to the interpreter. If, additionally, the
// debugger is active, SIGINT would behave as a breakpoint.
// @cat

// *********************************************************************
// *   Part 1: signal handler definition                               *
// *********************************************************************


//<sb> @doc @xl Signal Handling
// In claire signals are named objects. signal handling is system dependent and a
// signal_handler instance may not correspond to a supported signal in which case
// its value signo will be set to -1.
claire/signal_handler <: thing(private/signo:integer = -1, private/handler:property)


claire/SIGHUP :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGHUP\n"),
	SIGHUP.signo := externC("SIGHUP", integer),
	externC("\n#endif\n")))

claire/SIGQUIT :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGQUIT\n"),
	SIGQUIT.signo := externC("SIGQUIT", integer),
	externC("\n#endif\n")))

claire/SIGILL :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGILL\n"),
	SIGILL.signo := externC("SIGILL", integer),
	externC("\n#endif\n")))

claire/SIGTRAP :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGTRAP\n"),
	SIGTRAP.signo := externC("SIGTRAP", integer),
	externC("\n#endif\n")))

claire/SIGABRT :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGABRT\n"),
	SIGABRT.signo := externC("SIGABRT", integer),
	externC("\n#endif\n")))

claire/SIGEMT :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGEMT\n"),
	SIGEMT.signo := externC("SIGEMT", integer),
	externC("\n#endif\n")))

claire/SIGFPE :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGFPE\n"),
	SIGFPE.signo := externC("SIGFPE", integer),
	externC("\n#endif\n")))

claire/SIGKILL :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGKILL\n"),
	SIGKILL.signo := externC("SIGKILL", integer),
	externC("\n#endif\n")))


claire/SIGBUS :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGBUS\n"),
	SIGBUS.signo := externC("SIGBUS", integer),
	externC("\n#endif\n")))

claire/SIGSEGV :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGSEGV\n"),
	SIGSEGV.signo := externC("SIGSEGV", integer),
	externC("\n#endif\n")))

claire/SIGSYS :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGSYS\n"),
	SIGSYS.signo := externC("SIGSYS", integer),
	externC("\n#endif\n")))

claire/SIGPIPE :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGPIPE\n"),
	SIGPIPE.signo := externC("SIGPIPE", integer),
	externC("\n#endif\n")))

claire/SIGALRM :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGALRM\n"),
	SIGALRM.signo := externC("SIGALRM", integer),
	externC("\n#endif\n")))

claire/SIGTERM :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGTERM\n"),
	SIGTERM.signo := externC("SIGTERM", integer),
	externC("\n#endif\n")))

claire/SIGURG :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGURG\n"),
	SIGURG.signo := externC("SIGURG", integer),
	externC("\n#endif\n")))

claire/SIGSTOP :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGSTOP\n"),
	SIGSTOP.signo := externC("SIGSTOP", integer),
	externC("\n#endif\n")))

claire/SIGTSTP :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGTSTP\n"),
	SIGTSTP.signo := externC("SIGTSTP", integer),
	externC("\n#endif\n")))

claire/SIGCONT :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGCONT\n"),
	SIGCONT.signo := externC("SIGCONT", integer),
	externC("\n#endif\n")))

claire/SIGCHLD :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGCHLD\n"),
	SIGCHLD.signo := externC("SIGCHLD", integer),
	externC("\n#endif\n")))

claire/SIGTTIN :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGTTIN\n"),
	SIGTTIN.signo := externC("SIGTTIN", integer),
	externC("\n#endif\n")))

claire/SIGTTOU :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGTTOU\n"),
	SIGTTOU.signo := externC("SIGTTOU", integer),
	externC("\n#endif\n")))

claire/SIGIO :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGIO\n"),
	SIGIO.signo := externC("SIGIO", integer),
	externC("\n#endif\n")))

claire/SIGXCPU :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGXCPU\n"),
	SIGXCPU.signo := externC("SIGXCPU", integer),
	externC("\n#endif\n")))

claire/SIGXFSZ :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGXFSZ\n"),
	SIGXFSZ.signo := externC("SIGXFSZ", integer),
	externC("\n#endif\n")))

claire/SIGVTALRM :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGVTALRM\n"),
	SIGVTALRM.signo := externC("SIGVTALRM", integer),
	externC("\n#endif\n")))

claire/SIGPROF :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGPROF\n"),
	SIGPROF.signo := externC("SIGPROF", integer),
	externC("\n#endif\n")))

claire/SIGWINCH :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGWINCH\n"),
	SIGWINCH.signo := externC("SIGWINCH", integer),
	externC("\n#endif\n")))

claire/SIGINFO :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGINFO\n"),
	SIGINFO.signo := externC("SIGINFO", integer),
	externC("\n#endif\n")))

claire/SIGUSR1 :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGUSR1\n"),
	SIGUSR1.signo := externC("SIGUSR1", integer),
	externC("\n#endif\n")))

claire/SIGUSR2 :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGUSR2\n"),
	SIGUSR2.signo := externC("SIGUSR2", integer),
	externC("\n#endif\n")))

claire/SIGINT :: signal_handler()
(#if compiler.loading?
	(externC("\n#ifdef SIGINT\n"),
	SIGINT.signo := externC("SIGINT", integer),
	externC("\n#endif\n")))

claire/SIG_DFL :: property()
claire/SIG_IGN :: property()
claire/SIG_EXT :: property() // something different from SIG_DFL or SIG_IGN (i.e. external)

private/SIG_MAP[sig:integer] : signal_handler := SIGHUP


//<sb> setup signal handlers
(externC("\n#ifndef CLPC\n"),
for sig in signal_handler
	(if (sig.signo != -1)
		(SIG_MAP[sig.signo] := sig,
		let sh:signal_handler := sig
		in (externC("void (*h)(CL_INT) = (void (*)(CL_INT))::signal(sh->signo, SIG_DFL)"),
			sh.handler := (if (externC("(h == (void (*)(CL_INT))SIG_DFL)",integer) = 1)
								SIG_DFL
							else if (externC("(h == (void (*)(CL_INT))SIG_IGN)",integer) = 1)
								(externC("::signal(sh->signo, SIG_IGN)"),
								SIG_IGN)
							else (externC("::signal(sh->signo, (void (*)(int))h)"),
								trace(1, "---- Warning : signal ~S:~S is in use\n", sh, sh.signo),
								SIG_EXT))))),
externC("\n#else\n"),
for sig in signal_handler
	(if (sig.signo != -1)
		(sig.handler := SIG_DFL,
		SIG_MAP[sig.signo] := sig)),
externC("\n#endif\n"))


// *********************************************************************
// *   Part 2: signal API                                              *
// *********************************************************************

//<sb> @doc @xl Signal Handling
// Install a signal handler for the given signal_handler. A restriction p
// should exists with the domain void.
// signal returns the old property associated with the signal handler.
// One may use special values for the handler p:
// \ul
// \li SIG_IGN : ignore the signal
// \li SIG_EXT : this value is used by signal initializer if a signal is found
// to be already installed (e.g. by an external library).
// \li SIG_DFL : restore the default handler (system dependent). SIGINT is handled
// \/ul
// in a special way when assigned to SIG_DFL: the USER INTERRUPT.
// In CLAIRE signals are synchronously distributed to the meta code such to
// keep CLAIRE memory in a good shape. That is, there is a delay between the
// kernel routine that catches the signal and the execution of the meta handler.
[claire/signal(sig:signal_handler, p:property) : property ->
	if unix?()
		(if (sig.signo = -1) error("signal ~S not available on this machine",sig),
		if (p = SIG_DFL & sig != SIGINT) //<sb> default behavior for SIGINT
			(if (externC("(signal(sig->signo, SIG_DFL)==SIG_ERR)",integer) = 1)
				(if (sig = SIGKILL | sig = SIGSTOP)
					error("an attempt is made to ignore or supply a handler (~S) for ~S",p,sig)
				else error("signal ~S is not a valid signal number",sig)))
		else if (p = SIG_IGN)
			(if (externC("(signal(sig->signo, SIG_IGN)==SIG_ERR)", integer) = 1)
				(if (sig = SIGKILL | sig = SIGSTOP)
					error("an attempt is made to ignore or supply a handler (~S) for ~S",p,sig)
				else error("signal ~S is not a valid signal number",sig)))
		else if (externC("(signal(sig->signo, kernel_sighandler_integer)==SIG_ERR)",integer) = 1)
			(if (sig = SIGKILL | sig = SIGSTOP)
				error("an attempt is made to ignore or supply a handler (~S) for ~S",p,sig)
			else error("signal ~S is not a valid signal number",sig))),
		let old := sig.handler
		in (sig.handler := p,
			  old)]

//<sb> this is the meta signal handler
// we dispatch it according to the current mapping sig/handler in claire.
// note that we catch any exception that can occur during the handler
// a false value is returned in such situation, this tell kernel handler
// to re-close the exception after having restore a correct sigprocmask
// IN CLAIRE A SIGNAL HANDLER REMAINS INSTALLED AFTER ITS DELIVERY
[private/meta_sighandler(sigv:integer) : boolean ->
		(try let sig := SIG_MAP[sigv], p := sig.handler
			in (if (sigv = -1)
					system_error(mClaire/index = 57) //<sb> signal stack overflow
				else if (p != SIG_DFL & p != SIG_IGN & p != SIG_EXT)
					(when h := some(m in p.restrictions| let dom := m.domain
										in (length(dom) = 1 & dom[1] = void | sig % dom[1]))
					in (if (h.domain[1] = integer) apply(p,list(sig))
						else apply(p,list(void)))
					else error("No available restriction of ~S to deliver signal ~S", p, sig)) 
				else if (sig = SIGINT & p != SIG_IGN)
					//<sb> default behavior for SIGINT: user interrupt
					system_error(mClaire/index = 34),
				true)
		catch any
			false)]

SHOULD_BREAK?:boolean := false


//<sb> @doc @xl Signal Handling
// raise the given signal to the calling process
[claire/raise(sig:signal_handler) : void ->
	if (externC("(raise(sig->signo) == -1)",integer) = 1)
		externC("Cerrorno(87,_integer_(sig->signo),0)")]

//<sb> @doc @xl Signal Handling
// send the signal sig to the process with pid p.
[claire/kill(p:integer, sig:signal_handler) : void ->
	externC("\n#if defined(CLPC) || !defined(HAVE_KILL)
		Cerror(75,_string_(\"kill\"),0);
	#else
		if(kill(p,sig->signo) == -1)
			Cerrorno(86,_integer_(p),_integer_(sig->signo));
	#endif
	")]



// *********************************************************************
// *   Part 3: signal mask                                             *
// *********************************************************************


//<sb> @doc @xl Signal Handling
// sigprocmask returns the set of signal that are part of the process signal mask,
// that is the set of signal that the subsystem blocks from delivery.
[claire/sigprocmask() : set[signal_handler] ->
	let l := set<signal_handler>()
	in (externC("\n#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)\n"),
		externC("Cerror(75,_string_(\"sigprocmask\"),0)"),
		externC("\n#else\n"),
		externC("sigset_t ss"),
		externC("sigemptyset(&ss)"),
		externC("sigprocmask(SIG_SETMASK,0,&ss)"),
		for sig in {sig in signal_handler|sig.signo != -1}
			let sh:signal_handler := sig
			in (if (externC("sigismember(&ss,sh->signo)",integer) != 0)
					l :add sig),
		externC("\n#endif\n"),
		l)]

//<sb> @doc @xl Signal Handling
// sigsetmask sets the set of signal for the process signal mask,
// that is the set of signal that the subsystem blocks from delivery.
[claire/sigsetmask(self:subtype[signal_handler]) : set[signal_handler] ->
	let l := set<signal_handler>()
	in (externC("\n#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)\n"),
		externC("Cerror(75,_string_(\"sigprocmask\"),0)"),
		externC("\n#else\n"),
		externC("sigset_t ss,so"),
		externC("sigemptyset(&ss);sigemptyset(&so)"),
		for sig in self
			let sh:signal_handler := sig
			in externC("sigaddset(&ss,sh->signo)"),
		externC("sigprocmask(SIG_SETMASK,&ss,&so)"),
		for sig in {sig in signal_handler|sig.signo != -1}
			let sh:signal_handler := sig
			in (if (externC("sigismember(&so,sh->signo)",integer) != 0)
					l :add sig),
		externC("\n#endif\n"),
		l)]

//<sb> @doc @xl Signal Handling
// sigpending returns the set of signals that are currently blocked from delivery,
// i.e. the process has been signaled but the delivery is blocked until the signal
// is unblocked (sigunblock).
[claire/sigpending() : set[signal_handler] ->
	let l := set<signal_handler>()
	in (externC("\n#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)\n"),
		externC("Cerror(75,_string_(\"sigpending\"),0)"),
		externC("\n#else\n"),
		externC("sigset_t ss"),
		externC("if(sigpending(&ss) == -1) Cerrorno(74,_string_(\"sigpending @ void\"),0)"),
		for sig in {sig in signal_handler|sig.signo != -1}
			let sh:signal_handler := sig
			in (if (externC("sigismember(&ss,sh->signo)",integer) != 0)
					l :add sig),
		externC("\n#endif\n"),
		l)]

//<sb> @doc @xl Signal Handling
// sigblock adds a set of signal to the process signal mask.
[claire/sigblock(self:subtype[signal_handler]) : set[signal_handler] ->
	let l := set<signal_handler>()
	in (externC("\n#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)\n"),
		externC("Cerror(75,_string_(\"sigprocmask\"),0)"),
		externC("\n#else\n"),
		externC("sigset_t ss,so"),
		externC("sigemptyset(&ss);sigemptyset(&so)"),
		for sig in self
			let sh:signal_handler := sig
			in externC("sigaddset(&ss,sh->signo)"),
		externC("sigprocmask(SIG_BLOCK,&ss,&so)"),
		for sig in {sig in signal_handler|sig.signo != -1}
			let sh:signal_handler := sig
			in (if (externC("sigismember(&so,sh->signo)",integer) != 0)
					l :add sig),
		externC("\n#endif\n"),
		l)]

//<sb> @doc @xl Signal Handling
// sigunblock removes a set of signal to the process signal mask.
[claire/sigunblock(self:subtype[signal_handler]) : set[signal_handler] ->
	let l := set<signal_handler>()
	in (externC("\n#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)\n"),
		externC("Cerror(75,_string_(\"sigprocmask\"),0)"),
		externC("\n#else\n"),
		externC("sigset_t ss,so"),
		externC("sigemptyset(&ss);sigemptyset(&so)"),
		for sig in self
			let sh:signal_handler := sig
			in externC("sigaddset(&ss,sh->signo)"),
		externC("sigprocmask(SIG_UNBLOCK,&ss,&so)"),
		for sig in {sig in signal_handler|sig.signo != -1}
			let sh:signal_handler := sig
			in (if (externC("sigismember(&so,sh->signo)",integer) != 0)
					l :add sig),
		externC("\n#endif\n"),
		l)]

//<sb> @doc @xl Signal Handling
// sigsuspend temporarily changes the process signal mask to the set sigs, and then
// wait for a signal to arrive; on return the previous set of masked signals is restored.
// The signal mask set is usually empty to indicate that all signals are to be unblocked
// for the duration of the call.
[claire/sigsuspend(self:subtype[signal_handler]) : void ->
	externC("\n#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)\n"),
	externC("Cerror(75,_string_(\"sigsuspend\"),0)"),
	externC("\n#else\n"),
	externC("sigset_t ss"),
	externC("sigemptyset(&ss)"),
	for sig in self
		let sh:signal_handler := sig
		in externC("sigaddset(&ss,sh->signo)"),
	externC("sigsuspend(&ss)"),
	externC("\n#endif\n")]

//<sb> install the SIGINT (system_error 34) handler
(#if compiler.loading?
	externC("\n#ifndef CLPC
	    ::signal(SIGINT, kernel_sighandler_integer);
	      #ifdef HAVE_SIGINTERRUPT
	        siginterrupt(SIGINT, 1);
	      #endif
	    #endif\n"))

// *********************************************************************
// *   Part 4: itimer                                                  *
// *********************************************************************

//<sb> @doc @xl Signal Handling
// UNIX timer interface can handle 3 kind of timers:
// \ul
// \li The ITIMER_REAL timer decrements in real time.
// A SIGALRM signal is delivered when this timer expires.
// \li The ITIMER_VIRTUAL timer decrements in process virtual time.
// It runs only when the process is executing. A SIGVTALRM signal is
// delivered when it expires.
// \li The ITIMER_PROF timer decrements both in process virtual time and
// when the system is running on behalf of the process. It is designed
// to be used by interpreters in statistically profiling the execution
// of interpreted programs. Each time the ITIMER_PROF timer expires, the
// SIGPROF signal is delivered. Because this signal may interrupt in-progress
// system calls, programs using this timer must be prepared to restart
// interrupted system calls.
// \/ul
private/itimer <: thing(private/timerno:integer)


claire/ITIMER_REAL :: itimer()
(#if compiler.loading?
	(externC("\n#ifdef ITIMER_REAL\n"),
	ITIMER_REAL.timerno := externC("ITIMER_REAL", integer),
	externC("\n#endif\n")))

claire/ITIMER_VIRTUAL :: itimer()
(#if compiler.loading?
	(externC("\n#ifdef ITIMER_VIRTUAL\n"),
	ITIMER_VIRTUAL.timerno := externC("ITIMER_VIRTUAL", integer),
	externC("\n#endif\n")))

claire/ITIMER_PROF :: itimer()
(#if compiler.loading?
	(externC("\n#ifdef ITIMER_PROF\n"),
	ITIMER_PROF.timerno := externC("ITIMER_PROF", integer),
	externC("\n#endif\n")))


//<sb> @doc @xl Signal Handling
// setitimer sets a timer to the specified interval / value (in milliseconds). If value is non-zero,
// it indicates the time to the next timer expiration (at reload). If interval is non-zero, it
// specifies a value to be used in reloading value when the timer expires. Setting interval/value
// to 0/0 disables a timer. Setting interval to 0 causes a timer to be disabled after its next
// expiration (assuming value is non-zero). For instance we could implement a timeout as follow :
// \code
// timeout() : void -> error("Time out !")
//
// (signal(SIGALRM, timeout))
//
// (setitimer(ITIMER_REAL, 0, 10000))
// \/code
// which would raise a time out exception after 10 seconds of (real time) processing.
[claire/setitimer(it:itimer, interval:integer, value:integer) : tuple(integer, integer) ->
	let ointerval:integer := 0,
		ovalue:integer := 0
	in (externC("\n#if defined(CLPC) || !defined(HAVE_SETITIMER)\n"),
		externC("Cerror(75,_string_(\"setitimer\"),0)"),
		externC("\n#else\n"),
		externC("struct itimerval sit,osit"),
		externC("sit.it_interval.tv_sec = interval / 1000"),
		externC("sit.it_interval.tv_usec = interval % 1000"),
		externC("sit.it_value.tv_sec = value / 1000"),
		externC("sit.it_value.tv_usec = value % 1000"),
		externC("if(setitimer(it->timerno, &sit, &osit) == -1) {"),
			externC("Cerrorno(88, it->timerno, 0); }"),
		ointerval := externC("osit.it_interval.tv_sec * 1000 + osit.it_interval.tv_usec", integer),
		ovalue := externC("osit.it_value.tv_sec * 1000 + osit.it_value.tv_usec", integer),
		externC("\n#endif\n"),
		tuple(ointerval,ovalue))]

//<sb> @doc @xl Signal Handling
// getitimer returns the current values for timer it (i.e. the interval and the value).
[claire/getitimer(it:itimer) : tuple(integer, integer) ->
	let interval:integer := 0,
		value:integer := 0
	in (externC("\n#if defined(CLPC) || !defined(HAVE_GETITIMER)\n"),
		externC("Cerror(75,_string_(\"getitimer\"),0)"),
		externC("\n#else\n"),
		externC("struct itimerval sit"),
		externC("if(getitimer(it->timerno, &sit) == -1) {"),
			externC("Cerrorno(89, it->timerno, 0); }"),
		interval := externC("sit.it_interval.tv_sec * 1000 + sit.it_interval.tv_usec", integer),
		value := externC("sit.it_value.tv_sec * 1000 + sit.it_value.tv_usec", integer),
		externC("\n#endif\n"),
		tuple(interval,value))]

// *********************************************************************
// *   Part 5: waitpid                                                 *
// *********************************************************************

//<sb> @doc @xl Process handling
// A process status is returned by waitpid and tell how a child process
// has exited:
// \ul
// \li WRUNNING : the child still runs
// \li WEXITED : the child exited normally with a call to exit
// \li WSIGNALED : the child was terminated by a signal, this may be an
// abnormal termination that caused the creation a core dump file.
// \li WSTOPPED : the child was stopped
// \/ul
claire/process_status <: thing()

claire/WRUNNING :: process_status()
claire/WEXITED :: process_status()
claire/WSIGNALED :: process_status()
claire/WSTOPPED :: process_status()


//<sb> @doc @xl Process handling
// waitpid is a the UNIX interface to get status of child process.
// The parameter p specifies the set of child processes to wait for:
// \ul
// \li p = -1 : the call waits for any child process.
// \li p = 0 : the call waits for any child process in the process group of the caller.
// \li p > 0 : the call waits for the process with process id p.
// \li else : the call waits for any process whose process group id equals the absolute value of p.
// \/ul
// block?, when true, tell that the call should block until a waited child terminates.
[claire/waitpid(p:integer, block?:boolean) : tuple(process_status, integer, any) ->
	let (status:integer, pid:integer, no:integer) := (Kernel/waitpid_status(p, block?) as tuple(integer, integer, integer))
	in let pstatus := (case status
				({0} WRUNNING, {3} WSIGNALED,
				{2} WSTOPPED, any WEXITED))
		in (if (pstatus = WEXITED) tuple(pstatus, pid, (if (no = -1) unknown else no))
			else
				when sig := some(sig in signal_handler|sig.signo = no)
				in tuple(pstatus, pid, sig)
				else tuple(pstatus, pid, (if (no = -1) unknown else no)))]

//<sb> @doc @xl Process handling
// waitpid(p) is equivalent to waitpid(p, true)
[claire/waitpid(p:integer) : tuple(process_status, integer, any) ->
	waitpid(p, true)]

