
_240_to_nbsp <: filter()

_240_to_nbsp!(self:port) : _240_to_nbsp ->
	filter!(_240_to_nbsp(), self)

[write_port(self:_240_to_nbsp, buf:char*, len:integer) : integer ->
	for i in (1 .. len)
		let c := buf[i]
		in (if (c = '\240') fwrite("&nbsp;", self.target)
			else putc(c, self.target)),
	len]

column_sort(l1:list, l2:list) : boolean ->
	(l1[3] < l2[3])

[show_method_def_html(self:list[Defmethod]) : void ->
	if self
		( ?><b>In file <?== CODE_LOCS[self[1].arg][1] ?></b>
			<table style='font-family: Courier; font-size: 9pt'><?
		for d in self
			( ?><tr><td align='right'><?== CODE_LOCS[d.arg][2]
					?>:&nbsp;<a href="txmt://open?line=<?= CODE_LOCS[d.arg][2]
				?>&column=<?= CODE_LOCS[d.arg][3]
				?>&url=<?=
					url_encode("file://" /+ CODE_LOCS[d.arg][1])
			?>"><font color=red><b><?== d.arg.selector ?></b></font></a><td><b>(</b><?
				let first? := true
				in (for v in (d.arg.args but system)
					(if first? first? := false
					else ( ?>, &nbsp;<? )
					?><font color=green><b><?== v.mClaire/pname.name ?></b></font>:<?== v.range))
			?><b>)<?
				if d.inline? ( ?>&nbsp;=&gt;&nbsp;<? )
				else ( ?>&nbsp;-&gt;&nbsp;<? )
			?></b><?== d.iClaire/set_arg)
		?></table><? )]

show_file_lines_html(locs:list[list], n:integer) : void ->
	(try
		let lines := list<integer>(),
			src := locs[1][1],
			f := fopen(src, "r"),
			i := 0
		in (for loc in locs
				let l := loc[2]
				in (for i in (l - n .. l + n)
						(if (i > 0 & not(i % lines))
							lines add i)),
			lines := sort(< @ integer, lines),
			?><b>In file <?== src ?></b><br><?
			while not(eof?(f))
				(i :+ 1,
				let loc := sort(column_sort @ list, list{loc in locs | loc[2] = i}),
					ic := 0
				in (if loc
						( ?>&nbsp;&nbsp;<?= i ?>:&nbsp;<?
						for l in loc
							let c := l[3],
								len := l[4]
							in ( ?><?== fread(f, c - ic - 1),
								ic := c + len - 1,
								?><a href="txmt://open?line=<?= i
									?>&column=<?= c
									?>&url=<?=
										url_encode("file://" /+ src)
										?>"><font color=red><?== fread(f, len),
											?></font></a><? )
						?><?== freadline(f, "\n")
						?><br><? )
					else if (i > last(lines) + n)
						break()
					else let line := freadline(f,"\n"),
							n0 := get(lines, i + 1)
						in (if (i % lines)
								( ?>&nbsp;&nbsp;<?= i ?>:&nbsp;<?== line ?><br><?
								if eof?(f) ?><font color=blue>&lt;EOF&gt;</font><br><? )
							else if (n0 > 0 & n0 <= last(lines))
								( ?>&nbsp;&nbsp;...<br><? )
							)))
			?><br><?
			flush(cout()),
			fclose(f))
		catch any
			( ?><br><?
				let c := color(2)
				in (print(exception!()), color(c))
			?><br><? ))



rmdup(l:list[Call]) : list[Call] ->
	let res := list<Call>()
	in (for x in l
			(if (not(x % res) &
					not(exists(c in res|CODE_LOCS[c] = CODE_LOCS[x])))
				res add x),
		res)

defmethods(w:string) : list[Defmethod] ->
	let res := list<Defmethod>()
	in (for x in Defmethod
			(if (not(x.arg % res) &
					x.arg.selector.name.name = w &
					not(exists(c in res|CODE_LOCS[c.arg] = CODE_LOCS[x.arg])))
						res add x),
		res)

[fill_CLAIRE_LIBS(self:string, n:integer, paths:set[string]) : void ->
	if (n > 0)
		(for e in entries(self)
			(if (isfile?(self / e / "init.cl"))
				paths add self,
			if isdir?(self / e)
				fill_CLAIRE_LIBS(self / e, n - 1, paths)))]

[fill_CLAIRE_LIBS() : void ->
	let paths := set<string>()
	in (if isenv?("WCL_GOTODEF_ROOT")
			fill_CLAIRE_LIBS(realpath(getenv("WCL_GOTODEF_ROOT")), 2, paths)
		else if isenv?("TM_PROJECT_DIRECTORY")
			fill_CLAIRE_LIBS(realpath(getenv("TM_PROJECT_DIRECTORY")), 2, paths)
		else fill_CLAIRE_LIBS(realpath("."), 2, paths),
		print_in_string(),
		princ("CLAIRE_LIBS="),
		let first? := true
		in for d in paths
			(if first? first? := false else princ(":"),
			princ(d)),
		setenv(end_of_string()))]

[load_scope_code() : void ->
	if match_wildcard?(pwd(), "/*/xl/meta")
		(setcwd(".."), //<sb> claire source (/*/xl/meta)
		for m in {Core,Serialize,Language,Reader}
			(begin(m.part_of),
			m.mClaire/status := 0,
			load(m),
			end(m.part_of)))
	else if match_wildcard?(pwd(), "/*/xl/compile")
		(setcwd(".."), //<sb> claire source (/*/xl/compile)
		for m in set(get_value("Optimize"), get_value("Generate"))
			(begin(m.part_of),
			m.mClaire/status := 0,
			load(m),
			end(m.part_of)))
	else if (not(isfile?("init.cl")) &
			not(isfile?("../init.cl")) &
			isfile?(getenv("TM_FILEPATH")))
		(for e in entries(".", "*.cl")
			load(e), //<sb> not a module load("*.[w]cl")
		for e in entries(".", "*.wcl")
			load(e))
	else
		(if not(isfile?("init.cl"))
			setcwd(".."), //<sb> look for module init.cl
		if not(isfile?("init.cl"))
			setcwd(".."),
		if isfile?("init.cl")
			(Reader/set_eval_module(false),
			load("init.cl")))]

gotodef(w:string) : void ->
	(if (verbose() <= 0)
		ctrace() := null!(),
	?><title>Gotodef <?== w ?></title><?
	?><h3>Searching for <?== w ?> in <?= pwd() ?></h3><?
	fill_CLAIRE_LIBS(),
	let p := close_target!(_240_to_nbsp!(buffer!(cout(), 4096))),
		old := use_as_output(p)
	in (Reader/set_eval_module(false),
		load_scope_code(),
		let defs := defmethods(w)
		in (if defs
			 ( ?><hr><h4>Definitions</h4>
					<p style='font-family: Courier; font-size: 9pt'><?
				for file in {CODE_LOCS[c.arg][1] | c in list{c in defs|CODE_LOCS[c.arg]}}
					show_method_def_html(list{c in defs | CODE_LOCS[c.arg][1] = file})),
			let olocs := rmdup(list{c in Call|
								c.selector.name.name = w &
								CODE_LOCS[c] &
								not(c % defs) &
								not(exists(x in defs|CODE_LOCS[c] = CODE_LOCS[x.arg]))})
			in (if olocs
					(?></p><hr><h4>References</h4>
						<p style='font-family: Courier; font-size: 9pt'><?
				 	for file in {CODE_LOCS[c][1] | c in olocs}
						show_file_lines_html(
							list{l in list{CODE_LOCS[c] | c in olocs} | l[1] = file}, 1)))),
		use_as_output(old),
		fclose(p)))


[option_respond(self:{"-gotodef"}, l:list[string]) : void ->
	let w := getenv("TM_CURRENT_WORD")
	in (if l
			(if isdir?(l[1])
				(setenv("WCL_GOTODEF_ROOT=" /+ l[1]),
				l << 1),
			if l (w := l[1], l << 1)),
		try gotodef(w)
		catch any
			(color(2),
			print_exception(),
			color(1)),
		exit(0))]

[option_usage(self:{"-gotodef"}) : tuple(string, string, string) ->
	tuple("Goto definition", "-gotodef [<dir:path>] [<s:property>]",
			"Output definitions of <s> from directory <dir> (or . if undefined) and exit." /+
			" Are accounted calls to the property <s> and definition of found restrictions." /+
			" If <s> isn't specified then $TM_CURRENT_WORD is used instead (" /+
			"TextMate.app make this variable available).")]



