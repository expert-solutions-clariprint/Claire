//*********************************************************************
//* CLAIRE                                            Sylvain Benilan *
//* wcl.cl                                                            *
//* Copyright (C) 2000 - 2003 xl. All Rights Reserved                 *
//*********************************************************************

// ********************************************************************
// *   Part 1: echo & self_html (<?= and <?==)                        *
// ********************************************************************

print_oid(x:any) : void -> princ(Core/Oid(x))


[claire/echo(self:any) : void -> self_print(self)]
[claire/echo(self:string) : void -> princ(self)]
[claire/echo(self:integer) : void -> princ(self)]
[claire/echo(self:float) : void -> print(self)]
[claire/echo(self:char) : void -> princ(self)]
[claire/echo(p:property, self:object) : void ->
	if known?(p, self) echo(get(p, self))
	else none]

[claire/self_html(src:string) : void ->
	let len := length(src)
	in externC("{
		char *max = src + len;
		char buf[256];
		char *travel = buf;
		while(src < max) {
			int c = (unsigned char)(*src);
			switch(c) {
				case '\\\"':
					{*travel++ = '&';
					*travel++ = 'q';
					*travel++ = 'u';
					*travel++ = 'o';
					*travel++ = 't';
					*travel++ = ';';
					break;}
				case '\\'':
					{*travel++ = '&';
					*travel++ = 'a';
					*travel++ = 'p';
					*travel++ = 'o';
					*travel++ = 's';
					*travel++ = ';';
					break;}
				case '<':
					{*travel++ = '&';
					*travel++ = 'l';
					*travel++ = 't';
					*travel++ = ';';
					break;}
				case '>':
					{*travel++ = '&';
					*travel++ = 'g';
					*travel++ = 't';
					*travel++ = ';';
					break;}
				case '&':
					{*travel++ = '&';
					*travel++ = 'a';
					*travel++ = 'm';
					*travel++ = 'p';
					*travel++ = ';';
					break;}
				default: *travel++ = c;
			}
			if (travel - buf > 240) {
				Core.write_port->fcall((CL_INT)ClEnv->cout, (CL_INT)buf, (CL_INT)(travel - buf));
				travel = buf;
			}
			src++;
		}
		if (travel - buf > 0)
			Core.write_port->fcall((CL_INT)ClEnv->cout, (CL_INT)buf, (CL_INT)(travel - buf));}")]


[claire/nl2br(self:string) : string ->
	replace(replace(self, "\n","<br>"), "\r","")]


self_html_converter <: device(src:blob)
write_port(self:self_html_converter, buf:char*, len:integer) : integer ->
	(externC("{char out[256]; char *travel = out;
		int i = 0;
		for(;i < len;i++) {
			switch (buf[i]) {
				case '\\\"':
					{*travel++ = '&';
					*travel++ = 'q';
					*travel++ = 'u';
					*travel++ = 'o';
					*travel++ = 't';
					*travel++ = ';';
					break;}
				case '\\'':
					{*travel++ = '&';
					*travel++ = 'a';
					*travel++ = 'p';
					*travel++ = 'o';
					*travel++ = 's';
					*travel++ = ';';
					break;}
				case '<':
					{*travel++ = '&';
					*travel++ = 'l';
					*travel++ = 't';
					*travel++ = ';';
					break;}
				case '>':
					{*travel++ = '&';
					*travel++ = 'g';
					*travel++ = 't';
					*travel++ = ';';
					break;}
				case '&':
					{*travel++ = '&';
					*travel++ = 'a';
					*travel++ = 'm';
					*travel++ = 'p';
					*travel++ = ';';
					break;}
				default : *travel++ = buf[i];
			}
			if (travel - out > 200) {
				Core.write_port->fcall((CL_INT)self->src, (CL_INT)out, (CL_INT)(travel - out));
				travel = out;
			}
		}
		if (travel - out > 0)
			Core.write_port->fcall((CL_INT)self->src, (CL_INT)out, (CL_INT)(travel - out));
		}"),
	len)

SELF_HTML_CONVERTER :: self_html_converter(src = blob!())

[claire/self_html(self:any) : void ->
	try
		let conv := SELF_HTML_CONVERTER,
			old := use_as_output(conv)
		in (set_length(conv.src, 0),
			print(self),
			use_as_output(old),
			//<sb> note: cout() may be changed in the wcl env
			// when this self_html call produce the first print
			// out which implies a cout() redirection: so read
			// our buffer by chunk and print the chunk in the
			// current output
			freadwrite(conv.src, cout(), 1),
			freadwrite(conv.src, cout()))
	catch any
		(//[-100] self_html(~S) failed // owner(self)
		)]

[claire/self_html(p:property, self:object) : void ->
	if (@(p, owner(self)) & known?(p, self))
		self_html(get(p, self))
	else none]


// *********************************************************************
// *   Part 2: Reader callback                                         *
// *********************************************************************


[wcl_start?(r:meta_reader, p:integer) : boolean ->	
	case p
		({#/?}
			let c := getc(r.fromp)
			in (if (c = '>') true
				else (unget(r.fromp, c), false)))]


[nextswcl(r:meta_reader) : any ->
	let wcl := nexts(r, none)
	in (if (wcl = paren(r) | wcl = curly(r) | wcl = OR | wcl = bracket(r) | wcl = comma(r))
			none
		else if (wcl = if) readif(r, #/))
		else if (wcl = Zif)
			let %i := (readif(r, #/)) as If)
			in (if eval(test(%i)) arg(%i) else other(%i))
		else if (wcl = else) Serror(173, "Expression starting with else", nil)
		else if keyword?(wcl) nextstruct(r, wcl, none)
		else wcl)]

[Call_wcl!(self:property, l:list, loc:tuple) : Call_wcl ->
	let c := Call_wcl(self,l)
	in (let (f,ln,o) := loc
		in let s := (case self ({self_html} "==", {echo} "=", any self.name.name))
		in (c))]

[build_call_wcl(r:meta_reader, prop:property) : any ->
	let loc := Core/get_location(r.fromp),
		wcl := nextswcl(r)
	in (if (wcl = EOF) EOF
		else (wcl := (case wcl
					(Call+
						(if ((prop = self_html | prop = echo) & length(wcl.args) = 1)
							Call_wcl!(prop, list(selector(wcl), wcl.args[1]), loc)
						else Call_wcl!(prop, list(wcl), loc)),
					any Call_wcl!(prop, list(wcl), loc))),
				if wcl_start?(r, skipc(r))
					let swcl := read_wcl(r)
					in (if (swcl = EOF) wcl
						else Do!(wcl, swcl))
				else wcl))]

[build_top_call_wcl(r:meta_reader, prop:property) : any ->
	let loc := Core/get_location(r.fromp),
		wcl := nexte(r)
	in (if (wcl = EOF) EOF
		else (wcl := (case wcl
				(Call+
					(if ((prop = self_html | prop = echo) & length(wcl.args) = 1)
						Call_wcl!(prop, list(selector(wcl), wcl.args[1]), loc)
					else Call_wcl!(prop, list(wcl), loc)),
				any Call_wcl!(prop, list(wcl), loc))),
			wcl))]


//<sb> called by nextunit at the toplevel of a source file
// single wcl fragments are read
[read_top_wcl(r:meta_reader) : any ->
	let p := r.fromp,
		loc := Core/get_location(r.fromp),
		d := freadline(p, "<?"),
		c := Princ_wcl(selector = princ, args = list(d))
	in (p.Core/firstc := integer!(' '),
		let (inl, sep) := freadline(p, WCL_STOP)
		in (if (sep = "?")
				let ch := getc(p)
				in (if (ch = '>')
						let swcl := read_top_wcl(r)
						in (if (swcl = EOF) c
							else Do!(c, swcl))
					else (unget(p, '?'),
							unget(p, ch),
							c))
			else
				(if (length(sep) > 0)
					unget(p, sep), //<sb> unget the read seperator
				if (length(inl) = 0) c
				else
					when prop := (case inl
								({"="} echo,
								{"=="} self_html,
								{"oid"} print_oid,
								any get_value(inl)))
					in Do!(c, build_top_call_wcl(r, prop))
					else error("The property ~A is not known in ...<?~A", inl, inl))))]

[read_wcl(r:meta_reader) : any ->
	let p := r.fromp,
		loc := Core/get_location(r.fromp),
		d := freadline(p, "<?"),
		c := Princ_wcl(selector = princ, args = list(d)),
		pend := ""
	in (p.Core/firstc := integer!(' '),
		let (inl, sep) := freadline(p, WCL_STOP)
		in (if (sep = "?")
				let ch := getc(p)
				in (if (ch = '>') Do!(c, read_wcl(r))
					else (unget(p, '?'),
							unget(p, ch),
							c))
			else
				(if (length(sep) > 0)
					unget(p, sep), //<sb> unget the read seperator
				if (length(inl) = 0)
					(if (sep % {",", ")", "]", "}", "|"}) c
					else Do!(c, 
						let wcl := nextswcl(r)
						in (if wcl_start?(r, skipc(r))
								Do!(wcl, read_wcl(r))
							else wcl)))
				else
					(when prop := (case inl
								({"="} echo,
								{"=="} self_html,
								{"oid"} print_oid,
								any get_value(inl)))
					in Do!(c, build_call_wcl(r, prop))
					else error("The property ~A is not known in ...<?~A", inl, inl)))))]


// *********************************************************************
// *   Part 3: wcl file                                                *
// *********************************************************************

//<sb> activate web claire reader
(#if compiler.loading? reader.Reader/wcl? := true)


claire/fopen_source(self:string) : port ->
	(if (not(isfile?(self)) &
			not(match_wildcard?(self, "*.cl")) &
			not(match_wildcard?(self, "*.wcl")))
		self :/+ ".cl",
	let f:port := fopen(self, "r")
	in (if match_wildcard?(self, "*.wcl")
			let l := freadline(f)
			in (if match_wildcard?(l, "#!*")
					(unget(f, "\n?>"),
					unget(f, l))
				else (unget(f, "\n"),
						unget(f, l),
						unget(f, "?>"))),
		f := close_target!(line_counter!(f)),
		f))

claire/load_wcl :: property(open = 3)

//<sb> reads a WCL file and return a list of claire definition
// self should look like "filepath@PATH_INFO@path_info"
[load_wcl!(self:string) : list[Defclaire] ->
	Reader/reader_push(),
	write(Reader/index, reader, 1), //<sb> index 0 is reserved for load_wcl domain
	write(Reader/maxstack, reader, 1),
	let t := explode(self, "@PATH_INFO@"),
		fname := last(explode(t[1], *fs*)) as string,
		pinfo := (if (length(t) > 1) t[2] / fname else fname),
		f := fopen_source(t[1]),
		loc := Core/get_location(f),
		start := mClaire/base!(),
		top := mClaire/index!(),
		*item* := unknown,
		defs := list<Defclaire>(),
		bo := Do(list<any>()),
		lbody := bo.args
	in (mClaire/set_base(top),
		reader.Reader/fromp := f,
		reader.Reader/toplevel := false,
		*item* := readblock(f),
		while not(*item* = EOF)
			(mClaire/set_base(top),
			mClaire/index_jump(top + (reader.Reader/maxstack + 1)),
			case *item*
				(string none,
				Defclaire defs add *item*,
				any lbody add *item*),
			reader.Reader/index := 1,
		    reader.Reader/maxstack := 1,
		    mClaire/set_index(top),
		    mClaire/set_base(top),
			*item* := readblock(f)),
		defs add Defmethod(arg =
					Call(selector = load_wcl,
							args = list(Vardef(mClaire/pname = gensym(),
											range = set(pinfo)))),
						Language/set_arg = void, 
						body = bo, 
						inline? = false),
		Reader/reader_pop(),
		mClaire/set_base(start),
		mClaire/set_index(top),
		fclose(f),
		defs)]

//<sb> add a list of WCL file defined by wcl_path wildcard
// to the module's made_of. Any further request with the
// given pathinfo/file will call the compiled method
[claire/add_wcl(self:module, wcl_path:string, wild:string, pathinfo:string) : void ->
	setenv("WCL_RAISE_ERRORS=1"),
	cast!(self.made_of, string),
	for x in list{e in entries(wcl_path, wild)|length(e) > 0 & e[1] != '.'} //<sb> v3.3.33 filter hiden files
		(if isfile?(wcl_path / x)
			self.made_of :add wcl_path / x /+ "@PATH_INFO@" /+ pathinfo),
	for x in list{x in entries(wcl_path)|isdir?(wcl_path / x)}
		add_wcl(self, wcl_path / x, wild, pathinfo / x)]


[claire/add_wcl(self:module, wcl_path:string, wild:subtype[string], pathinfo:string) : void ->
	for w in wild add_wcl(self, wcl_path, w, pathinfo)]



