

// **********************************************************************
// *   Part 1: hash table                                               *
// **********************************************************************

hash_table <: ephemeral_object(hash_max:integer,
								content:list[any])

hash_table!(n:integer) : hash_table ->
	hash_table(hash_max = n,
				content = make_list(n, any, 0))

map_node <: ephemeral_object
map_node <: ephemeral_object(nkey:any, nval:any, next:map_node)

[reset(self:hash_table) : void ->
	self.hash_max := 0,
	self.content := nil]

[hash_value_oid(self:hash_table, value:any) : integer ->
	externC("unsigned char *val = (unsigned char*)&value"),
	let h := 0
	in (externC("h += val[0]; h += (h << 10); h ^= (h >> 6)"),
		externC("h += val[1]; h += (h << 10); h ^= (h >> 6)"),
		externC("h += val[2]; h += (h << 10); h ^= (h >> 6)"),
		externC("h += val[3]; h += (h << 10); h ^= (h >> 6)"),
		externC("h += (h << 3); h ^= (h >> 11); h += (h << 15)"),
		externC("h &= self->hash_max"),
		h max 1)]

[hash_value_string(self:hash_table, value:string) : integer ->
	let len := length(value),
		h := 0
	in (for i in (0 .. len - 1)
			(externC("unsigned char c = value[i]"),
			externC("c = c >= 'A' && 'Z' >= c ? c + ('a' - 'A') : c"),
			externC("h += c"),
			externC("h += (h << 10); h ^= (h >> 6)")),
		externC("h += (h << 3); h ^= (h >> 11); h += (h << 15)"),
		externC("h &= self->hash_max"),
		h max 1)]

[nth=(self:hash_table, key:any, val:any) : void ->
	let str? := (case key (string true)),
		h := (if str? hash_value_string(self, key)
				else hash_value_oid(self, key)),
		g := self.content,
		x := g[h]
	in (if (x = 0)
			(if known?(val) g[h] := map_node(nkey = key, nval = val))
		else let ok? := false
			in (while known?(x)
					let n := x as map_node
					in (if ((str? & (case n.nkey (string key insensitive= n.nkey))) |
								(not(str?) & n.nkey = key))
							(n.nval := val,
							ok? := true,
							break()),
						externC("x = n->next ? _oid_(n->next) : CNULL")),
				if not(ok?)
					g[h] := map_node(nkey = key, nval = val, next = g[h])))]


[nth(self:hash_table, key:any) : any ->
	let str? := (case key (string true)),
		h := (if str? hash_value_string(self, key)
				else hash_value_oid(self, key)),
		g := self.content,
		x := g[h],
		res := unknown
	in (if (x != 0)
			while known?(x)
				let n := x as map_node
				in (if ((str? & (case n.nkey (string key insensitive= n.nkey))) |
								(not(str?) & n.nkey = key))
						(res := n.nval,
						break()),
					externC("x = n->next ? _oid_(n->next) : CNULL")),
		res)]


// **********************************************************************
// *   Part 1: model                                                    *
// **********************************************************************


MODULE_NAME:string := "Other"
NAME_TO_ITEM_TABLE :: hash_table!(8191)
ITEM_LOCATION :: hash_table!(8191)
SHORT_PRESENTATION:string := ""
DOC_TITLE:string := ""

*expl_doc*:boolean := false
*code_doc*:boolean := false
*doc_links*:boolean := false
*one_file*:boolean := false
*per_cat_file*:boolean := false
*directory*:string := "docs"
*only_doc_links*:boolean := false

DEPOPTIONS:boolean := false

doc_context <: ephemeral_object

doc_item <: object(
				src_location:any,
				documentation:string = "",
				xl?:boolean = false,
				name:string)

	doc_link <: doc_item(oid:string, src:string)

	doc_copyright <: doc_item()
	doc_preamble <: doc_item()
	doc_author <: doc_item()

	doc_category <: doc_item
	doc_entity <: doc_item
	
	doc_section <: doc_item(
					exploit?:boolean = false,
					categories:list[doc_category])

	doc_category <: doc_item(
					section:doc_section,
					exploit?:boolean = false,
					items:list[doc_entity],
					entity_names:list[string],
					aliases:list[string],
					aname:string)

	doc_option <: doc_item(
					usage:string,
					from_module:module,
					opts:list[string],
					vars:list[string],
					ranges:list[string])

	doc_entity <: doc_item(
					source:any,
					ident:symbol,
					category:doc_category)

	(inverse(section) := categories)
	(inverse(category) := items)

		doc_method <: doc_entity(
						vars:list[string],
						mrange:any,
						inline?:boolean,
						var_ranges:list[any])

		doc_class <: doc_entity(superclass:any)

		doc_global <: doc_entity(
						constant?:boolean = false,
						grange:any,
						value:any)

		doc_interface <: doc_entity(arg:any, args:list)

		doc_table <: doc_entity(
						trange:any,
						tbody:any)


[add_ref_to_item(self:doc_item, nm:string) : void ->
  if (find(nm, " ") = 0)
    doc_link(name = nm,
              oid = Core/Oid(self)),
  NAME_TO_ITEM_TABLE[nm] := self]

[string2item(ctx:doc_context, s:string) : any ->
  when x := NAME_TO_ITEM_TABLE[s]
  in x
  else
    (if not(ctx.in_code?) unknown
    else
      (when x := NAME_TO_ITEM_TABLE["code/" /+ s]
      in x
      else unknown))]
      

[save_doc_links(ctx:doc_context) : void ->
  let f := fopen(ctx.directory / ctx.source.name.name /+ ".links", "w")
  in (for l in list{x in doc_link|unknown?(src,x)}
        printf(f, "~A ~A\n", l.name, l.oid),
      fclose(f))]

[load_doc_links() : void ->
  if isdir?(getenv("CLAIRE_DOCLINKS"))
    for x in entries(getenv("CLAIRE_DOCLINKS"), "*.links")
      let f := fopen(getenv("CLAIRE_DOCLINKS") / x, "r")
      in (while not(eof?(f))
            let l := freadline(f)
            in (if (length(l) > 0)
                  let (n, o) := explode_wildcard(l, "* *")
                  in NAME_TO_ITEM_TABLE[n] := doc_link(name = n, oid = o, src = replace(x,".links",".html"))),
          fclose(f))]


[compare_items(e1:doc_entity, e2:doc_entity) : boolean ->
	if (e1 % doc_method & e2 % doc_method)
		(if (e1.name = e2.name)
			length(e1.vars) < length(e2.vars)
		else lower(e1.name) < lower(e2.name))
	else lower(e1.name) < lower(e2.name)]


[ordered_categories() : list[doc_category] ->
	let l := list<doc_category>()
	in (for sec in list{c in doc_section|not(*expl_doc*) | c.exploit?}
			  for cat in list{c in sec.categories|not(*expl_doc*) | c.exploit? | sec.exploit?}
				  l add cat,
		if not(*expl_doc*)
		  for cat in doc_category
			  (if unknown?(section, cat)
				  l add cat),
		l)]

[print_module(self:doc_entity) : void ->
	/*when idt := get(ident, self)
	in (if (get(module!, idt) != claire & get(mClaire/definition, idt) != module!())
		    ( ?><?== get(module!, idt) ?>/<? ))*/ none]

[make_alias(cat:doc_category, salias:string) : void ->
	cat.aliases add salias,
	add_ref_to_item(cat, salias)]

[make_category(scat:string) : doc_category ->
	when c := NAME_TO_ITEM_TABLE[scat]
	in (case c
			(doc_category c,
			any let c := doc_category(name = scat)
				in (add_ref_to_item(c,scat),
					c)))
	else let c := doc_category(name = scat)
		in (add_ref_to_item(c,scat),
			c)]

[make_section(cat:doc_category, ssec:string) : doc_category ->
	let sec := make_section(ssec)
	in (cat.section := sec,
		cat)]

[make_section(ssec:string) : doc_section ->
	when c := NAME_TO_ITEM_TABLE[ssec]
	in (case c
			(doc_section c,
			any let s := doc_section(name = ssec)
				in (NAME_TO_ITEM_TABLE[ssec] := s,
					s)))
	else let s := doc_section(name = ssec)
		in (NAME_TO_ITEM_TABLE[ssec] := s,
			s)]

[make_doc_item(x:any, sdoc:string, cat:string, xl:boolean) : void -> none]

[make_doc_item(x:Defmethod, sdoc:string, cat:string, xl:boolean) : void ->
  if not(*expl_doc*)
  	let idnt := x.arg.selector.name,
  		item := doc_method(source = x.arg.selector,
  							name = idnt.name,
  							xl? = xl,
  							ident = idnt,
  							src_location = ITEM_LOCATION[x],
  							documentation = sdoc)
  	in (add_ref_to_item(item,item.name),
  		if (length(cat) > 0)
  			item.category := make_category(cat)
  		else item.category := make_category(MODULE_NAME),
  		if (length(sdoc) = 0)
  			(item.category.entity_names add item.name,
  			item.category.aliases add item.name),
  		item.mrange := x.iClaire/set_arg,
  		item.inline? := x.inline?,
  		for v in list{v in x.arg.args | v != system}
  			(item.vars add v.mClaire/pname.name,
  			item.var_ranges add v.range),
  		item)]

[make_doc_item(x:Defarray, sdoc:string, cat:string, xl:boolean) : void ->
  if not(*expl_doc*)
  	let idnt := iClaire/extract_symbol(x.arg.args[1]),
  		item := doc_table(source = x,
  							name = idnt.name,
  							xl? = xl,
  							ident = idnt,
  							src_location = ITEM_LOCATION[x],
  							documentation = sdoc)
  	in (add_ref_to_item(item,item.name),
  		if (length(cat) > 0)
  			item.category := make_category(cat)
  		else item.category := make_category(MODULE_NAME),
  		if (length(sdoc) = 0)
  			(item.category.entity_names add item.name,
  			item.category.aliases add item.name),
  		item.trange := x.iClaire/set_arg,
  		item.tbody := x.body,
  		item)]


[make_doc_item(x:Defclass, sdoc:string, cat:string, xl:boolean) : void ->
  if not(*expl_doc*)
  	let idnt := x.iClaire/ident,
  		item := doc_class(source = get(idnt),
  							name = idnt.name,
  							xl? = xl,
  							ident = idnt,
  							src_location = ITEM_LOCATION[x],
  							documentation = sdoc)
  	in (add_ref_to_item(item,item.name),
  		if (length(cat) > 0)
  			item.category := make_category(cat)
  		else item.category := make_category(MODULE_NAME),
  		if (length(sdoc) = 0)
  			(item.category.entity_names add item.name,
  			item.category.aliases add item.name),
  		item.superclass := x.arg,
  		item)]


[make_doc_item(x:Defobj, sdoc:string, cat:string, xl:boolean) : void ->
  if not(*expl_doc*)
  	let idnt := x.iClaire/ident,
  		val := get(idnt)
  	in (if (known?(val) & owner(val) <= property & (val.open = 1 | val.open = 3))
  			let item := doc_interface(source = val,
  									xl? = xl,
  									name = idnt.name,
  									ident = idnt,
  									src_location = ITEM_LOCATION[x],
  									documentation = sdoc)
  			in (add_ref_to_item(item,item.name),
  				if (length(cat) > 0)
  					item.category := make_category(cat)
  				else item.category := make_category(MODULE_NAME),
  				if (length(sdoc) = 0)
  					(item.category.entity_names add item.name,
  					item.category.aliases add item.name),
  				item.arg := x.arg,
  				item.args := x.args,
  				item)
  		else if (x.arg = global_variable)
  			let item := doc_global(source = x,
  									xl? = xl,
  									name = idnt.name,
  									ident = idnt,
  									src_location = ITEM_LOCATION[x],
  									documentation = sdoc)
  			in (add_ref_to_item(item,item.name),
  				if (length(cat) > 0)
  					item.category := make_category(cat)
  				else item.category := make_category(MODULE_NAME),
  				if (length(sdoc) = 0)
  					(item.category.entity_names add item.name,
  					item.category.aliases add item.name),
  				item.value := x.args[2].args[2],
  				item.grange := x.args[1].args[2],
  				item.constant? := item.grange = {},
  				item))]

// **********************************************************************
// *   Part 1: loading files                                            *
// **********************************************************************

load_items(self:string) : list[any] ->
	(Reader/reader_push(),
	put(Kernel/index, reader, 0),
	put(Reader/maxstack, reader, 0),
	reader.external := self,
	let f := Reader/fopen_source(self),
		base_name := last(explode(self,*fs*)),
		res := list<any>(),
		 start := mClaire/base!(),
         top := mClaire/index!(),
		*item* := unknown,
		br? := false,
		insert_href := "",
		ineval? := false
	in (mClaire/set_base(top),
		reader.Reader/fromp := f,
		reader.Reader/toplevel := false,
		*item* := Reader/readblock(f),
		while not(*item* = EOF)
			(f.Core/firstc := integer!(' '),
			mClaire/set_index(top + (reader.Reader/maxstack + 1)),
			res add *item*,
			Reader/skipc(reader),
			let loc := Core/get_location(f)
			in (*item* := Reader/readblock(f),
				case *item*
					(string
						(*item* := rtrim(*item*),
						let href := (print_in_string(),
									printf("\\a\\href='claire://source-edit?file=~A&line=~A&editor=~A' [~A:~S]\\/a ",
											url_encode(loc[1]),
											loc[2],
											url_encode(getenv("WCL_EDITOR")),
											//location_url(loc),
											base_name,
											loc[2]),
									end_of_string())
						in (if (find(*item*, "@code") > 0)
								let cde := freadline(f, "// @code\n")
								in (loc := Core/get_location(f),
									unget(f, cde),
									res add "\\br \\i \\b - The following code is part of the source - \\/b \\/i",
									if *doc_links*
										res add ("\\br \\b [dump]\\/b " /+ href),
									res add "\\code",
									let exl := explode(cde, "\n")
									in (while (exl & space?(exl[1]))
											exl << 1,
										while (exl & space?(exl[length(exl)]))
											shrink(exl, length(exl) - 1),
										for x in exl
											(if not(match_wildcard?(x, "//*"))
												res add x)),
									res add "\\/code",
									if *doc_links*
										(res add (print_in_string(),
												printf("\\b [/dump]\\/b \\a\\href='claire://source-edit?file=~A&line=~A&editor=~A' [~A:~S]\\/a ",
													url_encode(loc[1]),
													loc[2],
													url_encode(getenv("WCL_EDITOR")),
													//location_url(loc),
													base_name, loc[2]),
												end_of_string())),
									res add "@cat",
									*item* := "")
							else if (find(*item*, "@cat") > 0 &
								trim(explode_wildcard(*item*,"*@cat*")[2]) != "")
								(br? := false,
								insert_href := "\\b [cat]\\/b " /+ href)
							else if (find(*item*, "@cat") > 0)
								(br? := false,
								if *doc_links*
									res add ("\\br \\b [/cat]\\/b " /+ href))
							else if (find(*item*, "@doc") > 0)
								(br? := false,
								insert_href := "\\b [doc]\\/b " /+ href)
							else if (length(insert_href) > 0 & length(*item*) > 0)
								(if *doc_links*
									res add insert_href,
								br? := false,
								insert_href := "")
							else if br?
								(br? := false,
								if *doc_links*
									res add href),
							if match_wildcard?(*item*,"*\\br")
								br? := true
							else if (match_wildcard?(*item*,"*\\/code *") |
										match_wildcard?(*item*,"*\\/code"))
								(br? := false,
								*item* := trim(*item*),
								insert_href := "\\br \\b [/code]\\/b " /+ href)
							else if (match_wildcard?(*item*,"*\\code *") |
										match_wildcard?(*item*,"*\\code"))
								(br? := false,
								if *doc_links*
									res add ("\\br \\b [code]\\/b " /+ href)))),
					any (insert_href := "",
						ineval? := false,
						ITEM_LOCATION[*item*] := loc)))),
		Reader/reader_pop(),
		mClaire/set_base(start),
        mClaire/set_index(top),
        fclose(f),
		res))



bad_eval <: exception(src:exception)
[self_print(self:bad_eval) : void -> print(self.src)]

[load_file_items(self:string) : void ->
	let items := load_items(self),
		len := length(items),
		i := 1,
		cursec := ""
	in (while (i < len)
			let x := items[i]
			in (case x
				(string
					(if match_wildcard?(x,"*@@title *")
						let ex := explode_wildcard(x,"*@@title *")
						in (DOC_TITLE := trim(ex[2]),
						    MODULE_NAME := DOC_TITLE)
					else if match_wildcard?(x,"*@@sec *")
						let ex := explode_wildcard(x,"*@@sec *")
						in (cursec := trim(ex[2]),
							make_section(cursec).exploit? := find(ex[1], "@exploitation") > 0)
					else if match_wildcard?(x,"*@@cat *")
						let ex := explode_wildcard(x,"*@@cat *"),
							al := explode(ex[2], "@@"),
							ocat := make_category(trim(al[1]))
						in (ocat.xl? := find(ex[1], "@xl") > 0,
						  ocat.exploit? := find(ex[1], "@exploitation") > 0,
							if (length(al) > 1)
							 for a in explode(al[2], " ")
							 	(if (length(trim(a)) > 0)
									make_alias(ocat, trim(a))),
							make_section(ocat, cursec))
					else if (find(x,"@cat") > 0)
						let n := find(x,"@cat"),
							nxl := (let n := find(x,"@xl") in (if (n > 0) n + 4 else -1)),
							nexpl := (let n := find(x,"@exploitation") in (if (n > 0) n + 14 else -1)),
							cat := trim(substring(x, max(n + 4, max(nxl, nexpl)), length(x))),
							ocat := make_category(cat),
							doc := "",
							edit := ITEM_LOCATION[x]
						in (i :+ 1,
							ocat.src_location := edit,
							while (i < len & items[i] % string & not(find(items[i], "@cat") > 0))
								let xx := items[i],
									si := find(xx, "@section"),
									sa := find(xx, "@alias"),
									sn := find(xx, "@name")
								in (if (find(xx, "@eval") > 0)
										let cde := "("
										in (i :+ 1,
											while (i < len & items[i] % string & not(find(items[i], "@eval") > 0))
												(cde :/+ items[i] /+ "\n",
												i :+ 1),
											let b := blob!(),
												old := use_as_output(b)
											in (try
													eval(read(cde /+ ")"))
												catch any
													bad_eval(src = exception!()),
												use_as_output(old),
												doc :/+ string!(b),
												fclose(b)))
									else if (si > 0)
										let sec := trim(substring(xx, si + 9, length(xx)))
										in make_section(ocat, sec)
									else if (sn > 0)
										let nm := trim(substring(xx, sn + 6, length(xx)))
										in ocat.aname := nm
									else if (sa > 0)
										for a in explode(substring(xx, sa + 7, length(xx)), " ")
											(if (length(a) > 0)
												make_alias(ocat, trim(a)))
									else
										(if (length(doc) > 0)
											doc :/+ "\n",
										doc :/+ xx),
									i :+ 1),
							//if unknown?(section, ocat)
							//	make_section(ocat, MODULE_NAME),
							ocat.xl? := (nxl > 0),
							ocat.exploit? := (nexpl > 0),
							if (ocat.documentation != "" & length(doc) > 0)
								ocat.documentation :/+ " \\br ",
							ocat.documentation :/+ doc)
					else if (find(x,"@copyright") > 0)
						let n := find(x,"@copyright"),
							cr := trim(substring(x, n + 11, length(x)))
						in doc_copyright(documentation = cr)
					else if (find(x,"@depoptions") > 0)
						DEPOPTIONS := true
					else if (find(x,"@author") > 0)
						let n := find(x,"@author"),
							cr := trim(substring(x, n + 8, length(x)))
						in doc_author(documentation = cr)
					else if (find(x,"@preamble") > 0)
						let doc := ""
						in (i :+ 1,
							while (i < len & items[i] % string & not(find(items[i], "@preamble") > 0))
								(if (length(doc) > 0) doc :/+ "\n",
								doc :/+ items[i],
								i :+ 1),
							if not(doc_preamble.instances)
								doc_preamble(),
							doc_preamble.instances[1].documentation :/+ doc)
					else if (find(x,"@presentation") > 0)
						let doc := ""
						in (i :+ 1,
							while (i < len & items[i] % string & not(find(items[i], "@presentation") > 0))
								(if (length(doc) > 0) doc :/+ "\n",
								doc :/+ items[i],
								i :+ 1),
							SHORT_PRESENTATION :/+ doc)
					else if (find(x,"@doc") > 0)
						let n := find(x,"@doc"),
							nxl := find(x,"@xl"),
							cat := trim(substring(x, max(n + 5, nxl + 4), length(x))),
							doc := ""
						in (i :+ 1,
							while (i < len & items[i] % string)
								(if (length(doc) > 0) doc :/+ "\n",
								doc :/+ items[i],
								i :+ 1),
							make_doc_item(items[i], doc, cat, nxl > 0))),
				any (if *code_doc*
						  make_doc_item(x, "", "Undocumented", false))),
				i :+ 1))]



// **********************************************************************
// *   Part 1: generator options                                        *
// **********************************************************************

[option_respond(opt:{"-export-doc-links"}, l:list[string]) : void ->
  *only_doc_links* := true]

[option_respond(opt:{"-doclink"}, l:list[string]) : void ->
	*doc_links* := true]

[option_respond(opt:{"-onefile"}, l:list[string]) : void ->
	*one_file* := true]

[option_respond(opt:{"-categories"}, l:list[string]) : void ->
	*per_cat_file* := true]


[option_respond(opt:{"-apidoc", "-codedoc", "-exploitationdoc"}, l:list[string]) : void ->
	let smod := last(explode(pwd(),*fs*))
	in (if isfile?("init.cl") load("init")
		else if not(l) invalid_option_argument()
		else (smod := l[1], l << 1),
		when m := get_value(smod)
		in (*code_doc* := (opt = "-codedoc"),
		    *expl_doc* := (opt = "-exploitationdoc"),
  		  load_doc_links(),
  			load_module_doc(m),
  			if (*code_doc* |
  					doc_section.instances | doc_category.instances |
  					exists(c in doc_entity.descendents|c.instances))
  				(if ((not(*one_file*) & not(*per_cat_file*)) |
  						(*one_file* & *per_cat_file*))
  					(*one_file* := true,
  					generate_module_doc(m),
  					*one_file* := false,
  					generate_module_doc(m))
  				else generate_module_doc(m)))
  		else error("~A is not a valid module"))]

[option_usage(self:{"-doclink", "-onefile", "-categories", "-apidoc", "-codedoc"}) : tuple(string, string, string) ->
	tuple("Generate documentation",
			"[-doclink] [-onefile | -categories] {-apidoc | -codedoc} <m:module>",
			"Generate the documentation of the module <m> from source files. " /+
			"When -apidoc is used, the documentation will reference definitions " /+
			"that have a @doc tag in their comment whereas -codedoc considers all " /+
			"definitions.\n" /+
			"The generated documentation will contain a single HTML file when -onefile is given " /+
			"or a per category file when -categories is specified, otherwise both are generated.\n" /+
			"Last, when -doclink is specified then with each definition is associated a link to " /+
			"the source file that contain the definition.")]


// **********************************************************************
// *   Part 1: loading items from module(s) file(s)                     *
// **********************************************************************

[load_module_doc(self:module) : void ->
	let m := module!(),
		mods := list<module>()
	in (module!() := self,
		MODULE_NAME := self.name.name,
		if (self = claire)
			(module!() := Kernel,
			Kernel.source := "meta",
			load_file_items(Kernel.source / "kernel"),
			module!() := self,
			mods := list<module>(Core, Serialize, Language, Reader),
			mods add get_value("Optimize") as module,
			mods add get_value("Generate") as module,
			for m in mods
				(module!() := m,
				for f in m.made_of
					load_file_items(m.source / f),
				module!() := self))
		else
			(mods := list<module>(self),
			for f in self.made_of
				(try
					load_file_items(self.source / f)
				catch any
					(case exception!()
						(bad_eval close(exception!()))))),
		module!() := m,
		let l := (if DEPOPTIONS option_usage.restrictions
		          else list<method>{r in option_usage.restrictions|r.module! = self}),
			idx := 0,
			first? := true,
			b := blob!(),
			old := use_as_output(b)
		in (for m in mods
				for r in list{r in l| not(r.module!.name.name % {"Reader", "Language", "Optimize", "Generate"}) & 
				                            not(r.domain[1][1] %
				                              {"-v", "-qonerror", "-errassegv", "-noel", "-trace", "-sample" })}
					(idx :+ 1,
					set_length(b, 0),
					let (title, syntax, help) := apply(r, list(r.domain[1][1])),
						opt := doc_option(name = title, from_module = m),
						c := color(2),
						l := Core/print_back_option_usage(syntax)
					in (color(c),
						opt.usage := string!(b),
						opt.opts := l[1],
						opt.vars := l[2],
						opt.ranges := l[3],
						opt.documentation := help,
						for o in opt.opts
							add_ref_to_item(opt,o))),
			use_as_output(old)))]


// **********************************************************************
// *   Part 1: doc generation                                           *
// **********************************************************************

ONE_FILE :: 0
PER_CATEGORY_FILE :: 2

doc_context <: ephemeral_object(
					generation_mode:integer = PER_CATEGORY_FILE,
					add_source_links?:boolean,
					source:module,
					index:string,
					directory:string,
					color:string = "",
					bold?:boolean = false,
					in_code?:boolean = false,
					in_a?:boolean = false)

[generate_module_doc(self:module) : void ->
	let ctx := doc_context(source = self,
							directory = *directory*,
							add_source_links? = *doc_links*)
	in (if *one_file*
			(ctx.index := self.name.name /+ ".html",
			ctx.generation_mode := ONE_FILE)
		else ctx.index := self.name.name /+ ".index.html",
		if not(isdir?(ctx.directory))
			mkdir(ctx.directory),
		if (length(SHORT_PRESENTATION) > 0)
			let f := fopen(ctx.directory / ctx.source.name.name /+ ".presentation", "w")
			in (fwrite(SHORT_PRESENTATION, f),
				fclose(f)),	
		let f := fopen(ctx.directory / ctx.index, "w"),
			old := use_as_output(f)
		in (html_file_header(ctx),
			if doc_author.instances
				( ?><ul>
				<?
				for c in doc_author
					( ?><li><b>Author :</b> <?== c.documentation ?></li>
						<? )
				?></ul>
				<? ),
			if doc_copyright.instances
				( ?><h1><span class=pretitle>&nbsp;</span>&nbsp;Copyright</h1>
				<?
				?><ul>
				<?
				for c in doc_copyright
					( ?><li><?== c.documentation ?></li>
						<? )
				?></ul>
				<? ),
			if doc_preamble.instances
				( ?><h1><span class=pretitle>&nbsp;</span>&nbsp;Preamble</h1>
				<?
				print_doc(ctx, doc_preamble.instances[1].documentation, nil, nil)),
			generate_index(ctx),
			generate_doc(ctx),
			html_file_footer(),
			fclose(f),
			use_as_output(old)))]



// **********************************************************************
// *   Part 1: index generation                                         *
// **********************************************************************


[generate_index(self:doc_context) : void ->
	generate_category_index(self),
	generate_option_index(self),
	if not(*expl_doc*)
  	(generate_entity_index(self, doc_global, "global", "Global Variable"),
  	generate_entity_index(self, doc_table, "table", "Table"),
  	generate_entity_index(self, doc_interface, "interface", "Interface"),
  	generate_entity_index(self, doc_class, "class", "Class"),
  	generate_entity_index(self, doc_method, "method", "Method"))]

[generate_index(ctx:doc_context, e:doc_entity) : void ->
	generate_index(ctx, e, false)]
[generate_index(ctx:doc_context, e:doc_entity, catindex?:boolean) : void ->
	?><font font-face='Courier' class='item_index'><?
	if (ctx.add_source_links? & known?(src_location, e))
		( ?>[<?
			if (length(e.documentation) > 0)
			Core/edit_link(e.src_location[1], e.src_location[2], "edit")
		else Core/edit_link(e.src_location[1], e.src_location[2], "<font color='red'>edit</font>")
		?>]<?
	/*	 ?>[<a href='<? item_location_url(e) ?>'><?
			if (length(e.documentation) > 0) ( ?>edit<? )
			else ( ?><font color='red'>edit</font><? )
		?></a>] <?*/ 
			if (length(e.documentation) > 0) ( ?>   <? ))
	print_module(e),
	if (length(e.documentation) = 0 & catindex?)
		( ?><?== e.name)
	else item_href(ctx, e),
	item_prototype(e, ctx),
	if e.xl? princ(" <font color='red'>[XL]</font>")
	?></font><? ]

[generate_category_index(self:doc_context) : void ->
	if list{c in doc_category|not(*expl_doc*) | c.exploit? | (if known?(section, c) c.section.exploit?)}
		( ?><h1><span class=pretitle>&nbsp;</span>&nbsp;<a name='__category_index__'>Category index</a></h1>
		<ol><?
		for sec in list{sec in doc_section.instances|sec.exploit? | 
		                      exists(c in sec.categories|not(*expl_doc*) | c.exploit?)}
			( ?>
			<li class='section'><a name='<?oid sec ?>'><?== sec.name
				?></a>
				<ol><?
				for cat in list{c in sec.categories|not(*expl_doc*) | sec.exploit? | c.exploit?}
					( ?><li>
						<? item_href(self, cat) ?><?
						if cat.xl? princ(" <font color='red'>[XL]</font>")
					?></li>
					<? )
				?></ol>
			</li>
			<? ),
		for cat in list{c in doc_category|unknown?(section, c)}
			( ?><li><? item_href(self, cat) ?><?
				if cat.xl? princ(" <font color='red'>[XL]</font>")
			?></li>
			<? )
		?></ol>
		<? )]

[generate_option_index(self:doc_context) : void ->
	if doc_option.instances
		( ?><h1><span class=pretitle>&nbsp;</span>&nbsp;<a name='__option_index__'>Command line option index</a></h1>
		<?
		?><ol>
		<?
		for opt in doc_option.instances
			( ?><li><? item_href(self, opt) ?> : <? princ(opt.usage)
			?></li>
			<? )
		?></ol>
		<? )]

[generate_entity_index(self:doc_context, c:class, cn:string, si:string) : void ->
	if c.instances
		( ?><h1><span class=pretitle>&nbsp;</span>&nbsp;<a name='__<?= cn ?>_index__'><?= si ?> index</a></h1>
		<ul><?
		for e in sort(compare_items @ doc_entity, c.instances)
			( ?><li><? generate_index(self, e, false) ?></li>
			<? )
		?></ul>
		<? )]



// **********************************************************************
// *   Part 1: doc generation                                           *
// **********************************************************************

[generate_doc(self:doc_context) : void ->
  if *only_doc_links*
    save_doc_links(self)
	else if (self.generation_mode = ONE_FILE)
		(save_doc_links(self),
		generate_doc(self, "categories", doc_category),
		generate_doc(self, "command line options", doc_option),
		if not(*expl_doc*)
  		(generate_doc(self, "global variables", doc_global),
  		generate_doc(self, "tables", doc_table),
  		generate_doc(self, "interfaces", doc_interface),
  		generate_doc(self, "classes", doc_class),
  		generate_doc(self, "methods", doc_method)))
	else
		(for cat in list{c in doc_category|not(*expl_doc*) | c.exploit?}
			let fn := (print_in_string(),
						item_file(self, cat),
						end_of_string()),
				f := fopen(self.directory / fn, "w"),
				old := use_as_output(f)
			in (html_file_header(self, cat),
				generate_doc(cat, self),
				for e in cat.items
					generate_doc(e, self),
				html_file_footer(),
				fclose(f),
				use_as_output(old)),
		let f := fopen(self.directory / self.source.name.name /+ ".option.html", "w"),
			old := use_as_output(f)
		in (html_file_header(self, "options"),
			for e in doc_option
				generate_doc(e, self),
			html_file_footer(),
			fclose(f),
			use_as_output(old)))]

[generate_doc(self:doc_context, str:string, c:class) : void ->
	if exists(x in c.instances | x.documentation != "")
		( ?><h1 style='page-break-before: always; page-break-after: avoid'><span class=pretitle>&nbsp;</span>&nbsp;<?==
			    if (length(DOC_TITLE) > 0) DOC_TITLE
			    else self.source
			  ?> <?= str ?></h1>
		<? ),
	if (c = doc_category)
		for cat in ordered_categories()
			generate_doc(cat, self)
	else if (c = doc_option)
		for opt in doc_option
			generate_doc(opt, self)
	else
		for e in sort(compare_items @ doc_entity, c.instances)
			generate_doc(e, self)]


[generate_doc(self:doc_category, ctx:doc_context) : void ->
	if (ctx.generation_mode = ONE_FILE)
		(if known?(aname,self) ( ?><a name='<?== self.aname ?>'><? )
		   ?><a name='<?oid self ?>'><hr size=0 style='page-break-before: always' /></a>
		<a name='<?= replace(self.name," ","_") ?>'><hr size=0 /></a><?
		  if known?(aname,self) ( ?></a><? )
		?>
		<? ) //<sb> don't rm this \n or it would break the link
	?><table width='100%' class='item_header'>
		<tr>
			<td width='33%' align='left' valign='bottom'><i><?
					if known?(section, self)
						let l := self.section.categories,
							c := get(l, self)
						in (if (c > 1) item_href(ctx, l[c - 1])
							else let li := doc_section.instances,
									cs := get(li, self.section)
								in (if (cs > 1)
										let sec := li[cs - 1]
										in ( ?><?== sec.name,
											if sec.categories
												( ?><br/><? item_href(ctx, last(sec.categories))))))
				?></i></td>
			<td width='33%' align='center' valign='top'><i><?
					category_index_href(ctx),
					if known?(section, self)
						( ?><br/><? section_index_href(ctx, self.section))
				?><br/><b><?== self.name ?></b>
				</i></td>
			<td width='33%' align='right' valign='bottom'><i><?
					if known?(section, self)
						let l := self.section.categories,
							len := length(l),
							c := get(l, self)
						in (if (c < len) item_href(ctx, l[c + 1])
							else let li := doc_section.instances,
									cs := get(li, self.section)
								in (if (cs < length(li))
										let sec := li[cs + 1]
										in ( ?><?== sec.name,
											if sec.categories
												( ?><br/><? item_href(ctx, sec.categories[1])))))
				?></i></td>
		</tr>
	</table>
	<?
	if (known?(section, self) & get(self.section.categories, self) = 1)
		( ?><h1><span class=pretitle>&nbsp;</span>&nbsp;<?== self.section.name ?></h1>
		<? )
	?><h2><span class=pretitle>&nbsp;</span>&nbsp;<?
		if (ctx.generation_mode != ONE_FILE)
			( ?><a name='<?oid self ?>'><?== self.name ?></a>
			<? )
		else ( ?><?== self.name ),
		if self.xl? princ(" <font color='red'>[XL]</font>")
	?></h2>
	<?
	?><ul><?
		for e in {e in sort(compare_items @ doc_entity, self.items) | e % doc_class}
			( ?><li><? generate_index(ctx, e, true) ?></li><? )
	?></ul><?	
	?><ul><?
		for e in {e in sort(compare_items @ doc_entity, self.items) | not(e % doc_class)}
			( ?><li><? generate_index(ctx, e, true) ?></li><? )
	?></ul><?	
	print_doc(ctx, self.documentation, self.entity_names, self.aliases)]

[generate_doc(self:doc_option, ctx:doc_context) : void ->
	?><a name='<?oid self ?>'><hr size=0 style='page-break-after: avoid' /></a>
	<table width='100%' class='item_header' >
		<tr>
			<td width='33%' align='left'><i><? option_index_href(ctx) ?></i></td>
			<td width='33%' align='center'><?== self.name ?></td>
			<td width='33%' align='right'><i><?==
			    if (length(DOC_TITLE) > 0) DOC_TITLE
			    else self.from_module
			    ?> command line option</i></td>
		</tr>
	</table><?
	if ctx.add_source_links?
		(when x := some(dm in Defmethod|
								let c := dm.arg
								in (c.selector = option_usage &
									c.args &
									self.opts[1] % c.args[1].range))
		in Core/edit_link(CODE_LOCS[x.arg])),
	?><h3 class='opt_usage'><? princ(self.usage) ?></h3><?
	if self.vars
		( ?><h4>Where</h4><?
		?><ul><?
			for i in (1 .. length(self.vars))
				( ?><li><font color='green'><b><?== self.vars[i]
					?></b></font> belongs to <?== self.ranges[i]
				?></li><? )
		?></ul><? ),
	print_doc(ctx, replace(self.documentation,"\n","\\br "), self.vars, self.opts)]

[start_entity_doc(self:doc_entity, ctx:doc_context) : void ->
	item_header(self, ctx),
	?><h3><?== (print_module(self), self.name),
						item_prototype(self, ctx) ?></h3><? ]

[generate_doc(self:doc_entity, ctx:doc_context) : void ->
	if (length(self.documentation) > 0)
		(start_entity_doc(self, ctx),
		print_doc(ctx, self.documentation, nil, list(self.name)))]

[generate_doc(self:doc_method, ctx:doc_context) : void ->
	if (length(self.documentation) > 0)
		(start_entity_doc(self, ctx),
		print_doc(ctx, self.documentation, self.vars, list(self.name)))]


DOC_CLASS_ROOTS:list[class] := list<class>(any, ephemeral_object, thing)

[generate_doc(self:doc_class, ctx:doc_context) : void ->
	if (length(self.documentation) > 0)
		(item_header(self, ctx)
	  ?><table><tr><td class=class_proto><?
	  ?><h3><? entity_print(self, ctx, self.source) ?></h3><?
		let c := self.source,
		    a := c
		in (while not(a % DOC_CLASS_ROOTS)
		      let aslots := list<slot>{s in c.slots | s.domain[1] = a}
		      in (if (a != c)
                ( ?><tr><td class='class_proto_super item_index'><?
		            when e := string2item(ctx, a.name.name)
        		    in item_href(ctx, e)
        		    else entity_print(self, ctx, a))
        		  ?><td class_proto_slot><?
        		  if (a = c) ( ?><br/><? ),
		          if not(aslots) ( ?><span class=item_index>&nbsp;&nbsp;-</span><? )
		          else
        		    ( for s in aslots
                    ( ?><span class=item_index>&nbsp;&nbsp;<b><?
                        entity_print(self, ctx, s.selector)
                    ?></b> : <?
                        let rg := s.range
                        in (case rg
                              (subtype
                                (when e := string2item(ctx, (case rg.mClaire/t1 (class rg.mClaire/t1.name.name, any "???")))
            		                in ( ?><?== rg.arg ?>[<? item_href(ctx, e) ?>]<? )
            		                else entity_print(self, ctx, rg)),
                              class
                                (when e := string2item(ctx, rg.name.name)
            		                in item_href(ctx, e)
            		                else entity_print(self, ctx, rg)),
            		              any entity_print(self, ctx, rg)))
        		        ?></span><br/><? )),
      			  a := a.superclass)),
	  ?></table><?
		let c := self.source
		in (if (c inherit? thing)
					let first? := true
					in (for x in c.instances
							(if first?
								( ?><h3>Instances</h3><?
								first? := false)
							else princ(", "),
							?><?== x))),
		print_doc(ctx, self.documentation, nil, list(self.name)))]


// **********************************************************************
// *   Part 1: generation of item headers                               *
// **********************************************************************

[start_item_header(self:doc_entity, ctx:doc_context, n%:integer) : void ->
	?><a name='<?oid self ?>'><hr size=0 style='page-break-after: avoid' /></a>
	<a name='<?= self.name ?>'><hr size=0 /></a>
	<table width='100%' class='item_header'>
		<tr>
			<td width='<?= n% ?>%' align='left'><i><? category_index_href(ctx) ?></i></td>
			<td width='<?= n% ?>%' align='center'><i><?
				if known?(category, self)
					item_href(ctx, self.category) ?></i></td><? ]

[end_item_header(self:doc_entity, ctx:doc_context, n%:integer, kind:string) : void ->
	?><td width='<?= n% ?>%' align='right'><i><?
		if self.xl? princ("<font color='red'>[XL]</font> ")
	?><?== self.ident.mClaire/definition ?> <?= kind ?></i></td>
	</tr></table><? ]


[item_header(self:doc_global, ctx:doc_context) : void ->
	start_item_header(self, ctx, 20),
	?><td width='20%' align='center'></td>
	<td width='20%' align='center'></td><?
	end_item_header(self, ctx, 20, (if (self.grange = {}) "constant"
											else "global variable"))]

[item_header(self:doc_table, ctx:doc_context) : void ->
	start_item_header(self, ctx, 20),
	?><td width='20%' align='center'></td>
	<td width='20%' align='center'></td><?
	end_item_header(self, ctx, 20, "table")]

[item_header(self:doc_method, ctx:doc_context) : void ->
	start_item_header(self, ctx, 20),
	?><td width='20%' align='center'><i><?
		if self.inline? princ("inline")
		else if (self.source.mClaire/dispatcher > 0) princ("fast dispatch")
		else princ("normal dispatch")
	 ?></i></td>
	<td width='20%' align='center'><i><?
		if (self.source % operation) princ("operation")
	 ?></i></td><?
	end_item_header(self, ctx, 20, "method")]

[item_header(self:doc_class, ctx:doc_context) : void ->
	start_item_header(self, ctx, 20),
	?><td width='20%' align='center'><i><?
		let c := self.superclass
		in (if (c.open = 0) princ("abstract")
			else if (c.open = 1) princ("final")
			else if (c.open = 4) princ("ephemeral")
			else princ("open"))
	 ?></i></td>
	<td width='20%'></td><?
	end_item_header(self, ctx, 20, "class")]

[item_header(self:doc_interface, ctx:doc_context) : void ->
	start_item_header(self, ctx, 20),
			?><td width='20%' align='center'><i><?
				if (self.source.mClaire/dispatcher > 0)
					princ("fast dispatch")
				else princ("normal dispatch")
			 ?></i></td>
			<td  width='20%'></td><?
	end_item_header(self, ctx, 20, "interface")]


// **********************************************************************
// *   Part 1: HTML tools                                               *
// **********************************************************************

[file_inline_css_style() : void ->
?><style>
body {
        font-size: 14px;
        font-family: arial, Helvetica;
}

h1 { font-size: 25px; }
h2 { font-size: 20px; }

a[href] {
	border-bottom: 1px dotted grey;
	text-decoration: none
}

.doc_paragraph
{
        font-size: 14px;
        font-family: arial, helvetica;
}

.item_header { font-size: 10px; page-break-before: avoid; page-break-inside: avoid; page-break-after: avoid }

.item_index {
		white-space: pre;
        font-size: 11px;
        font-family: monaco, courier, mono-space;
}

.table_code {
		margin: 10px auto;
}

.doc_code {
    white-space: pre;
		padding-top: .1em;
		padding-bottom: .5em;
		background-color: #EEE;
		border: #AAA solid 1px;
        font-size: 11px;
        font-family: monaco, courier, mono-space;
}

.opt_usage {
		margin-left: 1em;
		margin-right: 1em;
		padding: .2em;
		background-color: #EEE;
		border: #AAA solid 1px;
        font-family: monaco, courier, mono-space;
	
}

.class_proto {
	vertical-align: top;
	text-align: right;
}

.class_proto_super {
	vertical-align: top;
	text-align: right;
}

.class_proto_slot {
	vertical-align: top;
	text-align: left;
}

</style><? ]


[html_file_header(self:doc_context) : void ->
	?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
	<head>
		<title>
			<?== (if (length(DOC_TITLE) > 0) DOC_TITLE
			      else self.source) ?> documentation
		</title>
		<? file_inline_css_style() ?>
		<link rel="stylesheet" type="text/css" href="doc.css" media="all">
	</head>
	<body>
	<h1><span class=pretitle>&nbsp;</span>&nbsp;<?== (if (length(DOC_TITLE) > 0) DOC_TITLE else self.source)
	  ?> <?
  		if (self.source = claire)
  			printf("v~A ", release())
  		else if known?(version, self.source)
  			printf("~A ", self.source.version)
  	?><?
  	  (if *code_doc* princ("documentation")
  	  else if *expl_doc* princ("exploitation documentation")
  	  else princ("user manual"))
	?></h1><?
	?><p><i>Last updated : <?== strftime("%a, %d %b %Y", now()) ?></i></p><? ]

[html_file_header(self:doc_context, kind:string) : void ->
	?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
	<head>
		<link rel="stylesheet" type="text/css" href="doc.css" media="all">
		<title>
			<?== self.source ?> <?== kind ?>
		</title>
		<? file_inline_css_style() ?>
	</head>
	<h1><span class=pretitle>&nbsp;</span>&nbsp;<?== self.source ?> <?== kind ?>
	<body><? ]

[html_file_header(self:doc_context, x:doc_item) : void ->
	?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
	<head>
		<link rel="stylesheet" type="text/css" href="doc.css" media="all">
		<title>
			<?== self.source ?> : <?== x.name ?>
		</title>
		<? file_inline_css_style() ?>
	</head>
	<body><? ]

[html_file_footer() : void ->
	?></body>
	</html><? ]

[category_index_href(self:doc_context) : void ->
	if (self.generation_mode = ONE_FILE)
		( ?><a href='#__category_index__'>categories</a><? )
	else
		( ?><a href='<?= self.index ?>#__category_index__'>categories</a><? )]

[option_index_href(self:doc_context) : void ->
	if (self.generation_mode = ONE_FILE)
		( ?><a href='#__option_index__'>option index</a><? )
	else
		( ?><a href='<?= self.index ?>#__option_index__'>option index</a><? )]

[section_index_href(self:doc_context, sec:doc_section) : void ->
	if (self.generation_mode = ONE_FILE)
		( ?><a href='#<?oid sec ?>'><?== sec.name ?></a><? )
	else
		( ?><a href='<?= self.index ?>#<?oid sec ?>'><?== sec.name ?></a><? )]

[item_href(self:doc_context, x:doc_link) : void ->
	?><a href='<? printf("~A#~A", x.src, x.oid)
	  ?>'><font color='#<?= self.color ?>'><?== x.name
	    ?></font></a><? ]


[item_href(self:doc_context, x:doc_item) : void ->
	?><a href='<?
		if (self.generation_mode != ONE_FILE & x % doc_category)
			(item_file(self, x) ?>#<?oid x )
		else (item_file(self, x) ?>#<?
				(if (x % doc_entity & known?(category, x) & length(x.documentation) = 0)
					( ?><?oid x.category)
				else ( ?><?oid x))) ?>'><?
	if (length(self.color) > 0)
		( ?><font color='#<?= self.color ?>'><? )
	?><?== x.name,
		if (length(self.color) > 0)
			( ?></font><? )
 	?></a><? ]

[item_href(self:doc_context, x:doc_link, w:string) : void ->
	?><a href='<? printf("~A#~A", x.src, x.oid)
	  ?>'><font color='#<?= self.color ?>'><?== w
	    ?></font></a><? ]

[item_href(self:doc_context, x:doc_item, w:string) : void ->
	?><a href='<?
		if (self.generation_mode != ONE_FILE & x % doc_category)
			(item_file(self, x) ?>#<?oid x )
		else (item_file(self, x) ?>#<?
				(if (x % doc_entity & known?(category, x) & length(x.documentation) = 0)
					( ?><?oid x.category)
				else ( ?><?oid x)))
	?>'><font color='#<?= self.color ?>'><?== w
	?></font></a><? ]

[item_href(self:doc_context, x:doc_section, w:string) : void ->
	if (length(self.color) > 0)
		( ?><font color='#<?= self.color ?>'><?== w ?></font><? )
	else ?><?== w ?><? ]

[item_file(self:doc_context, x:doc_category) : void ->
	if (self.generation_mode != ONE_FILE)
		printf("~I.html", c_princ(x.name)) ?><? ]

[item_file(self:doc_context, x:doc_option) : void ->
	if (self.generation_mode != ONE_FILE)
		printf("~A.option.html", self.source.name.name) ?><? ]

[item_file(self:doc_context, x:doc_entity) : void ->
	item_file(self, x.category)]


RESTORE_MODULE:module := claire

[set_item_module(x:doc_entity) : void ->
	RESTORE_MODULE := module!(),
	if known?(mClaire/definition, x.ident)
		module!() := x.ident.mClaire/definition
	else module!() := x.ident.module!]

[restore_module() : void -> module!() := RESTORE_MODULE]

[entity_print(x:doc_entity, ctx:doc_context, e:any) : void ->
	set_item_module(x),
	?><?== e,
	restore_module()]

[item_prototype(x:doc_global, ctx:doc_context) : void ->
	set_item_module(x),
	?><font color='blue'><?
		if x.constant? princ(" :: ")
		else princ(" : ")
	?></font><?
	if not(x.constant?)
		( ?><?== x.grange
			?><font color='blue'> := </font><? )
	?><?== x.value ?><? ,
	restore_module()]

[item_prototype(x:doc_table, ctx:doc_context) : void ->
	set_item_module(x),
	?>[<?
		let l := x.source.arg.args,
			len := length(l)
		in (for i in (2 .. len)
				(if (i > 2) princ(", "),
				let v := l[i]
				in ( ?><?== v.mClaire/pname.name
					?><font color=blue>:</font><?== v.range)))
	?>] <font color=blue>:</font> <?== x.trange
	?> <font color=blue>:=</font> <?== x.tbody ?>
	<? ,
	restore_module()]


[item_prototype(x:doc_interface, ctx:doc_context) : void ->
	set_item_module(x),
	?><font color='blue'> :: </font><?== x.arg ?>(<?
	let first? := true
	in for y in x.args
		(if first? first? := false
		else princ(", ") ?><?== y)
	?>)<?
	restore_module()]

[item_prototype(x:doc_class, ctx:doc_context) : void ->
	set_item_module(x),
	?><font color='blue'> &lt;: </font><? ,
	when e := string2item(ctx, x.superclass.name.name)
	in item_href(ctx, e)
	else ( ?><?== x.superclass),
	restore_module()]

[item_prototype(x:doc_method, ctx:doc_context) : void ->
	set_item_module(x),
	?>(<?
		let first? := true
		in (for i in (1 .. length(x.vars))
				(if first? first? := false
				else ( ?>, <? )
				?><font color='green'><?==
					x.vars[i]
				?></font><font color='blue'>:</font><?== x.var_ranges[i]))
	?>)<font color='blue'> <?
		if x.inline? princ("=")
		else princ("-")
	?>&gt; </font><?== x.mrange ?><? ,
	restore_module()]


// **********************************************************************
// *   Part 1: markdown like parser                                     *
// **********************************************************************

[princ_doc_word(self:doc_context, w:string, vnames:list[string]) : void ->
	let b? := (self.bold? | (w % vnames))
	in (if b? princ("<b>"),
		if (length(self.color) > 0) printf("<font color='#~A'>", self.color)
		else printf("<font color='black'>")
		?><?== w,
		princ("</font>"),
		if b? princ("</b>"))]


IGNORE_WORDS :: {"and", "or", "the", "=", "!=", "<", ">", "+", "-", "/", "*", "<=", ">="}

[print_doc_word(self:doc_context, w:string, vnames:list[string], exclude:list[string]) : void ->
	if (w % vnames) ( ?><b><?== w ?></b><? )
	else if (length(w) = 0 | space?(w)) princ(w)
	else if self.in_a? ( ?><?== w )
	else if (w % IGNORE_WORDS | lower(w) % exclude)
		(if (length(self.color) = 0)
			( ?><?== w )
		else princ_doc_word(self, w, vnames))
	else (when x := string2item(self, w)
		in item_href(self, x, w)
		else ( ?><?== w))]

TAG_STOP :: {' ', '\\', '\t', '\n', '\r'}
DOC_STOP :: {"\\", ' ', '\t', '\n', '\r', "%%",
			'(', ')', '{', '}', '[',']',
			"\"", "'", '>',
			"?>",
			',', '.', ':', ';', '/', '=', '+', '*', '#'}

isnext?(self:port, s:string) : boolean ->
	let tmp := fread(self, length(s))
	in (if (tmp = s) true
		else
			(unget(self, tmp),
			false))

checknext?(self:port, s:string) : boolean ->
	let tmp := fread(self, length(s))
	in (unget(self, tmp),
		tmp = s)


[print_doc(self:doc_context, doc:string, vnames:list[string], exclude:list[string]) : void ->
	?><p align='justify' class='doc_paragraph'><?
		let b := blob!(doc)
		in (while not(eof?(b))
				let (w, dum) := freadline(b, DOC_STOP)
				in (print_doc_word(self, w, vnames, exclude),
						self.bold? := false,
						self.color := "",
					if (dum = "%%") princ(getc(b))
					else if (dum = "\\")
						let (tag, sdum) := freadline(b, TAG_STOP)
						in case tag
							({"br"} princ("</p><p align='justify' class='doc_paragraph'>"),
							{"xl"} princ("<font color='red'>[XL]</font> "),
							{"bs"} princ("\\"),
							{"def"} ( ?></p>
									<table align='center' width='80%'>
									<tr><td><p align='justify' class='doc_paragraph'>
										<b>Definition : </b><i><? ),
							{"/def"} ( ?></i></p></td></tr></table>
									<p align='justify' class='doc_paragraph'><? ),
							{"h3"} ( ?></p>
							  <h3><span class=pretitle>&nbsp;</span>&nbsp;<? ),
							{"/h3"} ( ?></h3>
							  <p align='justify' class='doc_paragraph'><? ),
							{"center"} ( ?></p>
							  <center><? ),
							{"/center"} ( ?></center>
							  <p align='justify' class='doc_paragraph'><? ),
							{"ul"} ( ?></p>
							  <ul><? ),
							{"/ul"} ( ?></ul>
							  <p align='justify' class='doc_paragraph'><? ),
							{"include"}
							  (try
							    let f := fopen(freadline(b), "r")
							    in (freadwrite(f, cout()),
							        fclose(f))
							  catch any none),
							{"filedump"}
							  (try
							    let f := fopen(freadline(b), "r")
							    in ( ?></p><table class='table_code' align=center border=0 width='85%'>
										  <tr><td class='doc_code'><?
										    while not(eof?(f))
										      let (a,b) := freadline(f, DOC_STOP)
										      in (print_doc_word(self, a, vnames, exclude)
										          ?><?== (case b (char string!(b) , any b)))
										    ?></td></tr></table>
							        <p align='justify' class='doc_paragraph'><?
							        fclose(f))
							  catch any none),
							{"code"}
								(self.in_code? := true,
								princ("</p><table class='table_code' align=center border=0 width='85%'>
										<tr><td class='doc_code'>")),
							{"/code"}
								(self.in_code? := false,
								self.color := "",
								self.bold? := false,
								princ("</td></tr></table>
							  <p align='justify' class='doc_paragraph'>")),
							any (printf("<~A", tag),
								if (tag = "a") self.in_a? := true
								else if (tag = "/a") self.in_a? := false,
								if (sdum = '\\')
									while not(eof?(b))
										let (attr, sep) := freadline(b, {' ', '\\', '\t', '\n', '\r'})
										in (printf(" ~A", attr),
											if (sep != '\\') break()),
								princ(">")))
					else if (dum = '<') princ("&lt;")
					else if (dum = '>') princ("&gt;")
					else if (dum = ' ' & isnext?(b, ":")) princ("&nbsp;:")
					else princ(dum)))
	?></p><? ]
