
// *********************************************************************
// * CLAIRE                                            Sylvain Benilan *
// * toplevel.cl                                                       *
// * Copyright (C) 2005 xl. All Rights Reserved                        *
// *********************************************************************

//<sb> this file contains the console interface code including
// command loops for the interpreter, the inspector and the debugger
// and the management of execution contexts.
// Most of the code used to be in clConcole.cpp (<ycs>) and as been
// upgraded in claire in the xl version.

// ******************************************************************
// *    Part 3: standart console input                              *
// ******************************************************************

//<sb> stdin_line_reader is a basic terminal interface for the
// Reader, it should work on various subsystems.
// The clConsole.cpp file may define a custom line reader port
// based on editline BSD library that add history and completion
// features.

stdin_line_reader <: device(line:blob)

close_port(self:stdin_line_reader) : void ->
	fclose(self.line)

eof_port?(self:stdin_line_reader) : boolean -> false

//<sb> note: do not use set_length@blob to reset the line
// since it could be invoked while the line has been freed
// (e.g. at exit)
flush_port(self:stdin_line_reader) : void ->
	(self.line.Core/read_index := 0,
	self.line.Core/write_index := 0)

unget_port(self:stdin_line_reader, buf:char*, len:integer) : void ->
	unget_port(self.line, buf, len)

read_port(self:stdin_line_reader, buf:char*, len:integer) : integer ->
	(if eof?(self.line)
		(set_length(self.line, 0),
		fwrite(freadline(Core/Clib_stdin), self.line),
		fwrite("\n\n", self.line)),
	buf[1] := getc(self.line),
	if (len = 1) 1
	else 1 + read_port(self, buf + 1, len - 1))


// ******************************************************************
// *    Part 3: execution context                                   *
// ******************************************************************

//<sb> an execution_context object is an image of the system state
// at the time at which save_context has been called that can be
// restored by a call to restore_context. 
// note: the system backup is allocated in claire memory, this is
// important regarding the GC: it ensures for instance that the
// the backup of cout is marked by the GC...


execution_context <: ephemeral_object(
	module_stack:list,			//<sb> stack of begin(module)
	saved_system:environment,   //<sb> the environment
	saved_reader:meta_reader,	//<sb> the state of the reader
	debug_context?:boolean)
	

[save_context(debug?:boolean) : execution_context ->
	let exe := execution_context(debug_context? = debug?)
	in (exe.saved_system := externC("ClAlloc->makeAny(debug_ask == CTRUE ? 38 : 27)", environment),
		externC("memcpy(exe->saved_system, ClEnv, sizeof(CL_INT) * (debug_ask == CTRUE ? 38 : 27))"),
		exe.saved_reader := copy(reader),
		if debug?
			exe.module_stack := copy(externC("ClEnv->moduleStack", list)),
		mClaire/set_base(mClaire/index!()), //<sb> keep the current state of the stack
		exe)]

[restore_context(self:execution_context) : void ->
	externC("memcpy(ClEnv, self->saved_system, sizeof(CL_INT) * (self->debug_context_ask == CTRUE ? 38 : 27))"),
	if self.debug_context?
		externC("ClEnv->moduleStack = self->module_stack"),
	let r := reader
	in externC("memcpy(r, self->saved_reader, sizeof(meta_reader))")]


// ******************************************************************
// *    Part 3: tool                                                *
// ******************************************************************

PROMPT:string := ""	

[get_prompt() : string -> PROMPT]

//<sb> a special exception is used to abort a debug session
abort_debug <: exception()

self_print(self:abort_debug) : void ->
	printf("== debug session aborted == ")

//<sb> memory failure are not recoverable during debug :
// it would force the system to run in an unsafe environment
// (even the print of an exception could have an undefined issue).
// instead the exception is raised again by debug handlers such it
// can be cached by an outer handler (e.g. toplevel) from which
// stacks (execution & GC) are (hopefully enough) shorter.
// for that service we use a special pre-allocated exception which
// prevent an allocation to occur at the time of the congestion.
debug_fatal_error <: abort_debug(src:exception)
*debug_fatal_error* :: mClaire/new!(debug_fatal_error)

self_print(self:debug_fatal_error) : void ->
	printf("== fatal error during debug session ==\n~S",
				self.src)


// ******************************************************************
// *    Part 3: inspector loop                                      *
// ******************************************************************


INSPECT_STACK:list[any] := list<any>()

inspect_system(self:list[any]) : void ->
	(INSPECT_STACK := self)

IN_INSPECT_LOOP?:boolean := false

[inspect_toplevel(self:any) : void ->
	signal(SIGINT, SIG_IGN),
	INSPECT_STACK := list<any>(),
	let old_ctx := save_context(false)
	in (inspect(self),
		while true
			(IN_INSPECT_LOOP? := true,
			try
				let x := read_command("inspect> ")
				in (IN_INSPECT_LOOP? := false,
					if (x = q) break(),
					inspect_loop(x, INSPECT_STACK))
			catch any
				(signal(SIGINT, SIG_IGN),
				print_exception())),
		IN_INSPECT_LOOP? := false,
		restore_context(old_ctx))]


// ******************************************************************
// *    Part 3: toplevel loop                                       *
// ******************************************************************

NB_EVAL:integer := 0

//<sb> read a fragment on stdin
// ^C may be used to abort the command
[read_command(prompt:string) : any ->
	PROMPT := prompt,
	IDENTS := list<any>(),
	use_as_output(stdout),
	flush(stdout),
	reader.fromp := stdin,
	if not(Core/unix?()) Core/Clib_stdin.Core/eof_reached? := false,
	if (Core/get_device(stdin) % stdin_line_reader)
		(princ(prompt),
		flush(stdout)),
	reset_buffer(reader.fromp),
	reader.toplevel := true,
	flush(Core/get_device(reader.fromp)),
	reader.index := 0,
    reader.maxstack := 0,
	reader.fromp.Core/firstc := integer!(' '),
	signal(SIGINT, SIG_DFL),
	let c := color()
	in (if (c != 0) c := color(1),
		set_color(30, 0),
		flush(stdout),
		let x := Reader/nextunit(reader)
		in (signal(SIGINT, SIG_IGN),
			color(c),
			x))]

//<sb> evaluate and print the result of something that
// has been read. ^C may be used to abort the evaluation
// in debug mode ^C breaks the program
[eval_command(x:any, nb_eval:integer, check_break?:boolean) : void ->
	printf("`BLUEeval[~S]> `BLACK", nb_eval),
	flush(cout()),
	if (Language/DEBUG?)
		signal(SIGINT, Core/on_break_program)
	else signal(SIGINT, SIG_DFL),
	mClaire/index_jump(mClaire/index!() + (reader.maxstack + 1)),
	print(eval(x)),
	signal(SIGINT, SIG_IGN),
	princ("\n"),
	flush(cout())]

//<sb> here is a special version that raise
// an exception that is caught by the
// toplevel handler, it is used in the special
// case of an unrecoverable error (abort debug
// or memory exception)
TOP_CHANDLE:integer := 0
[close_toplevel_exception(self:exception) : void ->
	let n := TOP_CHANDLE
	in (externC("ClEnv->exception_I = self;
			  avoid_signal_caching = 0;
			  longjmp(ClEnv->handlers[n],3);"))]


command_line_error <: exception(src:any)
self_print(self:command_line_error) : void ->
	printf("An error has occurred during the handling of the command line:\n~S", self.src)

[Core/toplevel() : void ->
	signal(SIGINT, SIG_IGN),
	//<sb> the reader input should be connected
	// to a buffer for unget operations performed by
	// the wcl reader (i.e. expresion like ?>...<? )
	if (stdin = Core/Clib_stdin)
    stdin := buffer!(stdin_line_reader(line = blob!()), 1),
	NB_EVAL := 0,
	TOP_CHANDLE := externC("(ClEnv->cHandle+1)", integer),
	if Language/DEBUG?
		(color(1),
		printf("``RED ========== Debugger installed ==========\n")),
	if (Language/DEBUG? & Core/top_frame != Core/current_frame)
		(let clex := mClaire/new!(command_line_error)
		in (clex.src := get(exception!, system),
			put(exception!, system, clex)),
		try debug_loop()
		catch any
			printf("`REDThere is a bug in the debug loop :\n~I", print_exception()),
		exception!() := mClaire/new!(abort_debug),
		printf("~S\n", exception!())),
	let exe_ctx := save_context(false)
	in (while true
			(restore_context(exe_ctx),
			if Language/DEBUG?
				Core/reset_frame_stack(),
			try
				let eval? := true,
					x := read_command(
							(print_in_string(),
							printf("[~S]~S> ", getpid(), module!()),
							end_of_string()))
				in (case x
						({q} break(), //<sb> the normal exit
						unbound_symbol
							(if (x.name.name % {"s", "st", "ste", "step"})
								(if (Core/STEP = -1)
									(Core/STEP := 0,
									printf("``RED========== Stepper removed ==========\n"))
								else
									(Core/STEP := -1,
									printf("``RED========== Stepper installed ==========\n")),
								eval? := false))),
					if eval?
						(NB_EVAL :+ 1,
						eval_command(x, NB_EVAL, true)),
					exe_ctx.saved_system.verbose := verbose(),
					exe_ctx.saved_system.module! := module!())
			catch any
				(signal(SIGINT, SIG_IGN),
				if (owner(exception!()) = system_error &
							(exception!() as system_error).mClaire/index <= 3)
					print_exception()
				else if (exception!() % abort_debug)
					printf("~S\n", exception!())
				else if (Language/DEBUG? & Core/top_frame != Core/current_frame)
					(try
						debug_loop()
					catch any
						printf("`REDThere is a bug in the debug loop :\n~I",
									print_exception()),
					exception!() := mClaire/new!(abort_debug),
					printf("~S\n", exception!()))
				else
					(exe_ctx.saved_system.exception! := exception!(),
					print_exception()))),
		restore_context(exe_ctx))]


// ******************************************************************
// *    Part 3: debug command                                       *
// ******************************************************************

NB_DEBUG_EVAL:integer := 0

//<sb> debug_loop is called when a program issue an unhandled
// exception, it allows stack inspection (call stack, variables)
[debug_loop() : void ->
	signal(SIGINT, SIG_IGN),
	Core/STEP := 0,
	let oldout := use_as_output(stdout),
		old_ctx := save_context(true),
		frame := Core/current_frame,
		bindings := bind_frame(frame)
 	in (Language/DEBUG? := false,
		printf("``RED========= Unhandled exception =========\n"),
		print_exception(),
		if (oldout != cout())
			printf("`REDNote: output was ~S\n", oldout),
		show_frame_info(frame),
		NB_DEBUG_EVAL := 0,
		while true
			(try
				let x := read_command(
							(print_in_string(),
							printf("[debug]~S>> ", frame.Core/num),
							end_of_string()))
				in (case x
						({q} break(), //<sb> quit debug
						unbound_symbol
							(if (x.name.name % {"w", "wh", "whe", "wher", "where", "bt"})
								where(frame)
							else if (x.name.name % {"f", "fr", "fra", "fram", "frame"})
								show_frame_info(frame)
							else if (x.name.name % {"u", "up"})
								(if (frame.Core/num = 1)
									printf("`REDCannot go up the top frame\n")
								else
									(unbind_frame(bindings),
									frame := frame.Core/prev,
									bindings := bind_frame(frame),
									show_frame_info(frame)))
							else if (x.name.name % {"d", "do","dow","down"})
								(if unknown?(Core/next, frame)
									printf("`REDCannot go down the innermost frame\n")
								else
									(unbind_frame(bindings),
									frame := frame.Core/next,
									bindings := bind_frame(frame),
									show_frame_info(frame)))
							else if (x.name.name % {"e", "ed","edi","edit"})
								(print_in_string(),
								printf("claire://source-edit?file=~A&line=~A&editor=",
												url_encode(frame.Core/source),
												frame.Core/line),
								Core/open_link(end_of_string()))
							else
								(NB_DEBUG_EVAL :+ 1,
								eval_command(x, NB_DEBUG_EVAL, false))),
						any (NB_DEBUG_EVAL :+ 1,
							eval_command(x, NB_DEBUG_EVAL, false))))
				catch any
					(if (owner(exception!()) = system_error &
							(exception!() as system_error).mClaire/index <= 3)
						(*debug_fatal_error*.src := exception!(),
						close_toplevel_exception(*debug_fatal_error*)),
					signal(SIGINT, SIG_IGN),
					print_exception())),
		unbind_frame(bindings),
		Language/DEBUG? := true,
		restore_context(old_ctx))]

[Core/on_break_program() : void ->
	signal(SIGINT, SIG_IGN),
	Core/STEP := 0,
	let oldout := use_as_output(stdout),
		old_ctx := save_context(true),
		frame := Core/current_frame,
		bindings := bind_frame(frame)
 	in (Language/DEBUG? := false,
		printf("``RED=============== Stepper ===============\n"),
		if (oldout != cout())
			printf("`REDNote: output was ~S\n", oldout),
		show_frame_info(frame),
		while true
			(try
				let x := read_command(
							(print_in_string(),
							printf("[step]~S>> ", frame.Core/num),
							end_of_string()))
				in (case x
						({q} abort_debug(),
						unbound_symbol
							(if (x.name.name % {"w", "wh", "whe", "wher", "where", "bt"})
								where(frame)
							else if (x.name.name % {"f", "fr", "fra", "fram", "frame"})
								show_frame_info(frame)
							else if (x.name.name % {"u", "up"})
								(if (frame.Core/num = 1)
									printf("`REDCannot go up the top frame\n")
								else
									(unbind_frame(bindings),
									frame := frame.Core/prev,
									bindings := bind_frame(frame),
									show_frame_info(frame)))
							else if (x.name.name % {"d", "do","dow","down"})
								(if unknown?(Core/next, frame)
									printf("`REDCannot go down the innermost frame\n")
								else
									(unbind_frame(bindings),
									frame := frame.Core/next,
									bindings := bind_frame(frame),
									show_frame_info(frame)))
							else if (x.name.name % {"e", "ed","edi","edit"})
								(print_in_string(),
								printf("claire://source-edit?file=~A&line=~A&editor=",
												url_encode(frame.Core/source),
												frame.Core/line),
								Core/open_link(end_of_string()))
							else if (x.name.name % {"s", "st", "ste", "step"})
								(Core/STEP := -1,
								break())
							else if (x.name.name % {"n", "ne", "nex", "next"})
								(Core/STEP := Core/current_frame.Core/num,
								break())
							else if (x.name.name % {"o", "ou", "out"})
								(Core/STEP := Core/current_frame.Core/num - 1,
								break())
							else if (x.name.name % {"c", "co", "con", "cont", "conti", "contin", "continu","continue"})
								(Core/STEP := 0,
								break())
							else
								(NB_DEBUG_EVAL :+ 1,
								eval_command(x, NB_DEBUG_EVAL, false))),
						any (NB_DEBUG_EVAL :+ 1,
							eval_command(x, NB_DEBUG_EVAL, false))))
				catch any
					(Language/DEBUG? := true,
					if (exception!() % abort_debug)
						(unbind_frame(bindings),
						close(exception!())),
					if (owner(exception!()) = system_error &
							(exception!() as system_error).mClaire/index <= 3)
						(*debug_fatal_error*.src := exception!(),
						close_toplevel_exception(*debug_fatal_error*)),
					signal(SIGINT, SIG_IGN),
					print_exception())),
		unbind_frame(bindings),
		Language/DEBUG? := true,
		restore_context(old_ctx),
		signal(SIGINT, Core/on_break_program))]

// ******************************************************************
// *    Part 4: debug frame display                                 *
// ******************************************************************


[show_frame(self:Core/dbg_frame, frame:Core/dbg_frame) : void ->
	printf("``BLUE[~S]~I>> ~I(~I)\n",
			(when s := get(Core/frame_source, self)
			in (case s
					(method s.module!,
					tuple s[1],
					any module!()))
			else module!()),
			(color_princ("``BLUE"), print(self.Core/num)),
			(color_princ("``BLUE"),
			print((when s := get(Core/frame_source, self)
				in (case s
						(method s.selector,
						tuple s[2],
						any s))
				else "???"))),
			let i := 1,
				l := self.Core/vars,
				len := 2 * self.Core/dimension, // 2* because vars contains var,val pairs
				f? := true
			in while (i < len)
				let vn := l[i], vval := l[i + 1]
				in (i :+ 2,
					printf("~I~I~S`BLACK",
							(if f? f? := false else printf("`BLUE, ")),
							(color_princ("`BLUE"),princ(vn),princ(" = ")),
							vval)))]

[show_source_lines(self:Core/dbg_frame, n:integer) : void ->
	try
		let src := self.Core/source,
			l := self.Core/line,
			c := self.Core/column,
			len := self.Core/length,
			f := fopen(src, "r"),
			i := 0
		in (color_princ("`BLUE--- file `BLACK"),
			princ(src),
			color_princ(" `BLUE---`BLACK\n"),
			while not(eof?(f))
				(i :+ 1,
				if (i = l)
					(color_princ("`BLUE"),
					printf("~S", i),
					color_princ("`BLACK: "),
					freadwrite(f, cout(), c - 1),
					let tmp := fread(f, len),
						lentmp := length(tmp),
						sp := 1
					in (while (sp < lentmp)
							(if (tmp[sp] != ' ') break(),
							princ(" "),
							sp :+ 1),
						color_princ("``RED"),
						i :+ occurrence(tmp,"\n"),
						princ(tmp, sp, lentmp)),
						color_princ("`BLACK"),
						princ(freadline(f, "\n")),
						princ("\n"))
				else if (i > l + n)
						break()
				else let line := freadline(f,"\n")
					in (if (i >= l - n)
							(color_princ("`BLUE"),
							printf("~S", i),
							color_princ("`BLACK: "),
							printf("~A\n", line)))),
			fclose(f))
		catch any
			printf("`REDNo source file available\n")]

[show_frame_info(self:Core/dbg_frame) : void -> show_frame_info(self, self)]
[show_frame_info(self:Core/dbg_frame, frame:Core/dbg_frame) : void ->
	show_frame(self, frame),
	show_source_lines(self, 2)]

[where(frame:Core/dbg_frame) : void ->
	let fr := Core/current_frame
	in (while (fr.Core/num > 0)
			(show_frame(fr, frame),
			fr := fr.Core/prev))]

// ******************************************************************
// *    Part 5: frame variable binding                              *
// ******************************************************************

//<sb> DebugVariable is a container for local variable that :
//  - is bound to the symbol of the variable (bind_frame)
//  - hold the value of the variable to which it evaluates (self_eval)
DebugVariable <: ephemeral_object(value:any)

[self_eval(self:DebugVariable) : any -> self.value]

(put(mClaire/evaluate, DebugVariable, function!(self_eval_DebugVariable1)))


// add frame variables to the lexical environment
[bind_frame(self:Core/dbg_frame) : list ->
	let vs := self.Core/vars,
		len := length(vs),
		i := 1,
		bindings := list<any>()
	in (while (i < len)
			let sym := symbol!(vs[i], module!()),
				oval := get(sym)
			in (if (vs[i + 1] != Core/undefined_debug)
					(bindings add sym,
					bindings add oval,
					put(sym, DebugVariable(value = vs[i + 1]))),
				i :+ 2),
		bindings)]

// remove frame variable from the lexical environment
[unbind_frame(bindings:list) : void ->
	let len := length(bindings),
		i := 1
	in while (i < len)
		(put(bindings[i], bindings[i + 1]),
		i :+ 2)]
