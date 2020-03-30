//*********************************************************************
//* CLAIRE                                            Sylvain Benilan *
//* complete.cl                                                       *
//* Copyright (C) 2000 - 2003 xl. All Rights Reserved                 *
//*********************************************************************


//<sb> this file contains some completion facility for the command
// line interpreter, it defines generic completion method for both
// claire and shell interpreters.
// The completion style is inspired from zle (zsh command line editor)
// in the way that hitting TAB repeatedly update the command line with
// possible matches.

//<sb> Claire completion is made on any named entity (classes and things)

//<sb> An interpreter should define the following callback that,
// for instances, are convenient for readline library (note that
// in the readline case we doesn't use readline internal completion
// facilities and we access readline buffer directly)

insert_text(t:string) : void -> function!(interpreter_insert_text)
delete_text(s:integer,e:integer) : void -> function!(interpreter_delete_text)
reset_state() : void -> function!(interpreter_reset_state)
get_cursor_position() : integer -> function!(self_print)
get_text() : string -> function!(interpreter_get_text, NEW_ALLOC)
display_list(l:list) : void -> function!(interpreter_display_list)

// *********************************************************************
// * Table of content:                                                 *
// * 1. claire completion                                              *
// * 2. shell completion                                               *
// *********************************************************************


// *********************************************************************
// * 1. claire completion                                              *
// *********************************************************************


private/MATCHES:list[string] := list<string>()
private/LAST_EXPLODED:list[char U string] := list<(char U string)>()
private/LAST_MODULE:module := claire
private/LAST_LINE:string := ""
private/LAST_POSITION:integer := -1
private/MATCH_INDEX:integer := 0
private/COMPLETE_START_POSITION:integer := -1

[completion_reset() : void ->
	COMPLETE_START_POSITION := -1,
	LAST_LINE := "",
	MATCH_INDEX := 0,
	LAST_POSITION := -1,
	LAST_MODULE := claire,
	shrink(MATCHES, 0)]


[private/explode_separators(s:string) : void ->
	shrink(LAST_EXPLODED, 0),
	let p1 := 1, len := length(s), l := LAST_EXPLODED
	in (for p2 in (1 .. len)
			(if (s[p2] % {'[',']','(',')','{','}',';',' ','@', '/','.',':','<','>','|',',','\"','\''})
				(if (p2 > p1 & p1 <= len) l :add substring(s, p1, p2 - 1),
				l :add s[p2],
				p1 := p2 + 1)),
		if (p1 <= len) l :add substring(s, p1, len))]

[private/same_tree?(a:module) : boolean ->
	if (a = LAST_MODULE) true
	else if (a = claire) false
	else same_tree?(a.part_of)]

[private/complete_named_object(o:string, l:list[string]) : void ->
	let p := length(o)
	in (for s in list{s in (thing U class)|known?(mClaire/definition, s.name) &
								o = substring(s.name.name, 1,p)}
			when x := get_value(LAST_MODULE, s.name.name)
			in l :add s.name.name
			else (if same_tree?(s.name.module!) l :add s.name.module!.name.name /+ "/" /+ s.name.name))]

[private/complete_slot(o:string, l:list[string]) : void ->
	let p := length(o)
	in (for s in list{s in slot|known?(mClaire/definition, s.selector.name) &
								o = substring(s.selector.name.name, 1,p)}
			when x := get_value(LAST_MODULE, s.selector.name.name)
			in l :add s.selector.name.name
			else (if same_tree?(s.selector.name.module!) l :add s.selector.name.module!.name.name /+ "/" /+ s.selector.name.name))]

[private/complete_class(o:string, l:list[string]) : void ->
	let p := length(o)
	in (for s in list{s in class|known?(mClaire/definition, s.name) &
								o = substring(s.name.name, 1,p)}
			when x := get_value(LAST_MODULE, s.name.name)
			in l :add s.name.name
			else (if same_tree?(s.name.module!) l :add s.name.module!.name.name /+ "/" /+ s.name.name))]


[private/nodup(l:list[string]) : void ->
	shrink(MATCHES, 0),
	for i in l
		(if not(i % MATCHES) MATCHES :add i),
	MATCHES := sort(< @ string, MATCHES)]


[fill_claire_matches(buf:string, end:integer) : void ->
	let tmp := substring(buf, 1, end),
		l := (explode_separators(tmp), LAST_EXPLODED),
		len := length(l),
		res := list<string>()
	in (LAST_MODULE := module!(),
		if (l[len] % string) COMPLETE_START_POSITION := end - length(l[len]) + 1
		else COMPLETE_START_POSITION := -1,
		if (len >= 3 & l[len - 1] = '/'  & l[len - 2] % string & l[len] % string)
			(when x := get_value(l[len - 2])
			in (if (x % module)
					(LAST_MODULE := x as module,
					nth-(l, len - 2),
					nth-(l, len - 2),
					len := length(l))))
		else if (len >= 4 & l[len] = '(' & l[len - 1] % string & l[len - 2] = '/' & l[len - 3] % string)
			when x := get_value(l[len - 3])
			in (if (x % module)
					(LAST_MODULE := x as module)),
		if (len > 0 & l[len] % string)
			(if ((len > 2 & l[len - 2] = '<' & l[len - 1] = '(') |
				(len > 1 & (l[len - 1] = '<' | l[len - 1] = '[')) |
				(len > 2 & l[len - 2] % string & l[len - 1] = ':') |
				(len > 2 & l[len - 1] = ' ' & l[len - 2] = "U") |
				(len > 3 & l[len - 1] = ' ' & l[len - 2] = ':' & l[len - 3] = ' '))
				complete_class(l[len], res)
			else if (len > 1 & l[len - 1] = '.') complete_slot(l[len], res)
			else complete_named_object(l[len], res)),
		nodup(res))]


[match_prefix() : string ->
	let ll := list<string>{(last(explode(i,"/")) as string)|i in MATCHES},
		res := copy(ll[1]) //<sb> we shall not modify a matched element: copy it
	in (for i in ll
			let lres := length(res), li := length(i)
			in (if (lres = 0) break(),
				if (li < lres) (shrink(res, li), lres := li),
				for j in (1 .. lres)
					(if (res[j] != i[j])
						(shrink(res, j - 1),
						break()))), res)]

[method_description(m:method) : string ->
	let res := m.selector.name.name, first? := true
	in (res :/+ "(",
		for a in m.domain
			(if first? first? := false
			else res :/+ ", ",
			res :/+ (print_in_string(), print(a), end_of_string())),
		res :/+ ") `BLUE-> `BLACK",
		res :/+ (print_in_string(), print(m.range), end_of_string()),
		res)]

[class_description(self:class) : string ->
	print_in_string(),
	printf("~S <: ~S\n", self, self.superclass),
	for s in (self.slots but (isa @ object) but (name @ thing))
		printf("~S:~S = ~S\n", s.selector, s.range, s.default),
	end_of_string()]

[claire_complete() : void ->
	let oldtrace := ctrace()
	in (ctrace() := null!(), //prevent a gc trace to occur while completing
		let pos := get_cursor_position(), line := get_text()
		in (if (MATCHES & pos = LAST_POSITION & line = LAST_LINE & COMPLETE_START_POSITION != -1)
				(delete_text(COMPLETE_START_POSITION, pos),
				MATCH_INDEX :+ 1,
				if (MATCH_INDEX = length(MATCHES)) ding(),
				if (MATCH_INDEX > length(MATCHES)) MATCH_INDEX := 1,
				insert_text(MATCHES[MATCH_INDEX]),
				LAST_POSITION := get_cursor_position(),
				LAST_LINE := get_text())
			else
				(fill_claire_matches(line, pos - 1),
				if MATCHES
					(MATCH_INDEX := 0,
					LAST_POSITION := pos,
					LAST_LINE := get_text(),
					if (length(MATCHES) = 1)
						(claire_complete(),
						COMPLETE_START_POSITION := -1)
					else
						let mp := match_prefix()
						in (if (length(mp) > pos - COMPLETE_START_POSITION)
								(shrink(MATCHES,0),
								MATCHES :add mp,
								claire_complete(),
								COMPLETE_START_POSITION := -1)
							else
								(ding(),
								display_list(MATCHES),
								MATCHES :add substring(line,COMPLETE_START_POSITION,pos - 1))))
				else let l := LAST_EXPLODED, len := length(l)
					in (if (len > 1 & l[len] = '.' & l[len - 1] % string)
							(when p := get_value(LAST_MODULE, l[len - 1])
							in (if (p % class)
									display_list(list<string>(class_description(p)))
								else display_list(list<string>(class_description(owner(p)))),
								ding()))
						else if (len > 1 & l[len] = '(' & l[len - 1] % string)
							when p := get_value(LAST_MODULE, l[len - 1])
							in (if (p % property)
									let lm := p.restrictions
									in (if lm
											(princ("\n"),
											for i in list<string>{method_description(m)|m in lm}												
												printf("  ~I\n", color_princ(i)),
											//display_list(list<string>{method_description(m)|m in lm}),
											ding())))
							else insert_text("\t")
						else insert_text("\t")))), ctrace() := oldtrace)]


// *********************************************************************
// * 2. shell completion                                               *
// *********************************************************************

BINS:list[string] := list<string>()
BINS_INIT?:boolean := false

[bin_init() : void ->
	if not(BINS_INIT?)
		(BINS_INIT? := true,
		for p in explode(getenv("PATH"), *ps*)
                	(if isdir?(p)
				for f in {i in entries(p)|not(isdir?(p / i))}
					BINS :add f))]

[fill_binaries(buf:string) : void ->
	let p := rfind(buf, *fs*),
		p0 := rfind(buf, " ") + 1
	in (COMPLETE_START_POSITION := -1,
		if (p0 > 1 & p0 > p) COMPLETE_START_POSITION := p0
		else if (p = 0 & p0 = 1) COMPLETE_START_POSITION := 1,
		if (COMPLETE_START_POSITION > 0)
			buf := substring(buf,COMPLETE_START_POSITION,length(buf)),
		bin_init(),
		for f in {i in BINS|find(i,buf) = 1}
			MATCHES :add (replace(f," ", "\\ ") /+ " "))]

[fill_files(buf:string) : void ->
	let p := rfind(buf, *fs*),
		p0 := rfind(buf, " ") + 1,
		tmp := (if (p0 > 1 & p < p0) substring(buf,p0,length(buf))
				else if (p0 > 1 & p >= p0) substring(buf, p0, p)
				else ""),
		df := (if (p > 0 & p >= p0 & p + 1 <= length(buf)) substring(buf, p + 1, length(buf))
				else "")
	in (if (p > 0)
			(shrink(MATCHES, 0),
			COMPLETE_START_POSITION := min(p + 1, 1 + length(buf)),
			try for f in entries(tmp)
				(if (length(df) = 0 | find(f, df) = 1)
					let match:string := f 
					in (if isdir?(tmp / f) match :/+ "/",
						MATCHES :add match as string))
			catch any none))]

[shell_complete() : void ->
	let oldtrace := ctrace()
	in (ctrace() := null!(), //prevent a gc trace to occur while completing
		let pos := get_cursor_position(), line := get_text()
		in (if (MATCHES & pos = LAST_POSITION & line = LAST_LINE & COMPLETE_START_POSITION != -1)
				(delete_text(COMPLETE_START_POSITION, pos),
				MATCH_INDEX :+ 1,
				if (MATCH_INDEX = length(MATCHES)) ding(),
				if (MATCH_INDEX > length(MATCHES)) MATCH_INDEX := 1,
				insert_text(MATCHES[MATCH_INDEX]),
				LAST_POSITION := get_cursor_position(),
				LAST_LINE := get_text())
			else
				(shrink(MATCHES, 0),
				let tmp := substring(line,1,pos - 1)
				in (fill_binaries(tmp),
					if (COMPLETE_START_POSITION = -1 | length(MATCHES) = 0)
						fill_files(tmp)),
				nodup(copy(MATCHES)),
				if MATCHES
					(MATCH_INDEX := 0,
					LAST_POSITION := pos,
					LAST_LINE := get_text(),
					if (length(MATCHES) = 1)
						(shell_complete(),
						COMPLETE_START_POSITION := -1)
					else
						let mp := match_prefix()
						in (if (length(mp) > pos - COMPLETE_START_POSITION)
								(shrink(MATCHES,0),
								MATCHES :add mp,
								shell_complete(),
								COMPLETE_START_POSITION := -1)
							else
								(ding(),
								display_list(MATCHES),
								MATCHES :add substring(line,COMPLETE_START_POSITION,pos - 1)
								))))), ctrace() := oldtrace)]

