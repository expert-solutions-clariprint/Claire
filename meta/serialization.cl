//*********************************************************************
//* CLAIRE                                            Sylvain Benilan *
//* serialization.cl                                                  *
//* Copyright (C) 2000 - 2003 xl. All Rights Reserved                 *
//*********************************************************************

// This file contains general purpose (un)serialization methods
// for storage or IPC.
// It is intended to to be fast and simple, the serialization format
// is non-human readable (i.e. binary), its API is provided on port.
// Last the serialization method is intended to be endian sensitiveness
// such serialized data is portable.

// *********************************************************************
// *  Table of contents                                                *
// *   Part 1: global                                                  *
// *   Part 2: serialize                                               *
// *   Part 3: unserialize                                             *
// *   Part 4: api                                                     *
// *********************************************************************


// *********************************************************************
// *   Part 1: global                                                  *
// *********************************************************************


claire/serialize_context <: ephemeral_object(
					private/toplevel?:boolean = true,
					claire/toplevel_only?:boolean = true,
					private/currentOid:integer = 0,
					private/alreadySerialized:list[any],
					private/toSerialize?:list[any])

[close(self:serialize_context) : serialize_context -> self]

nth(self:serialize_context, x:any) : integer =>
	let l := self.alreadySerialized, i := 1
	in (if (for y in l (if (y = x) break(true), i :+ 1))
			i else 0)

[private/preSerialize(self:any, ctx:serialize_context) : void
 -> if (self % bag)	(for i in self preSerialize(i,ctx))
 	else if (self % global_variable) ctx.toSerialize? :add get(value, self)
 	else if (known?(self) & self % object) ctx.toSerialize? :add self]

claire/unserialize_context <: ephemeral_object(
					private/unserialized:table[range = any])

[close(self:unserialize_context) : unserialize_context ->
	self.unserialized := make_table(integer,any,unknown),
	self]


[private/puti(aint:integer,p:port) : void ->
	externC("unsigned CL_INT self = (unsigned int)aint"),
	externC("int v = 0; for(;v < sizeof(CL_INT);v++) {"),
	externC("int offset = v << 3"),
	externC("unsigned char c = (unsigned char)((self & (0xFF << offset)) >> offset)"),
	externC("p->put((char)c);}")]
[private/putc(i:integer,p:port) : void -> externC("unsigned char c = i;p->put((char)c)")]


// *********************************************************************
// *   Part 2: serialize                                               *
// *********************************************************************

[private/newOid(self:any, tag:integer,p:port, ctx:serialize_context) : integer ->
	ctx.currentOid :+ 1,
	putc(tag, p),
	ibserialize(ctx.currentOid, p, ctx),
	ctx.alreadySerialized :add self,
	ctx.currentOid]

[private/shouldSerialize?(self:any, tag:integer, p:port, ctx:serialize_context) : boolean ->
	let z := ctx[self]
	in (if (z > 0)
			(putc(34,p),
			ibserialize(z, p, ctx),
			//[5] ~S pop oid ~S --> // self, z,
			false)
		else
			(newOid(self, tag, p, ctx),
			//[5] ~S push oid ~S <-- // self, ctx.currentOid,
			true))]

TEST_SET :: {table, restriction, collection, exception, symbol,
			boolean, integer, char, float, string, type, array,
			module, class, bag}

[private/ibserialize_prop(self:object, prop:property, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@slot(~S) <-- // @(prop,owner(self)),
	ibserialize(prop.name, p, ctx),
	when val := get(prop, self)
	in (if prop.multivalued?
			let x:bag := list{i in val|not(ctx.toplevel_only?) | ctx.toplevel? |
										(let z := owner(i) in z % TEST_SET) |
										i % ctx.toSerialize?}
			in (if (val % set) x := set!(x),
				x := cast!(x, of(val)),
				ibserialize(x,p, ctx))
		else ibserialize(val,p, ctx))
	else putc(10,p)]

[private/ibserialize(self:object, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@object(~S) // self,
	let z := ctx[self]
	in (if (z > 0)
			(putc(34,p),
			//[5] ~S pop oid ~S --> // self, z,
			ibserialize(z, p, ctx))
		else if (not(ctx.toplevel_only?) | ctx.toplevel? | self % ctx.toSerialize?)
			let top? := ctx.toplevel?, own := owner(self)
			in (ctx.toplevel? := false,
				newOid(self, 13, p, ctx),
				//ctx.toSerialize?[self] := false,
				//[5] ~S push oid ~S <-- // self, ctx.currentOid,
				ibserialize(own,p, ctx),
				for prop in {s in {s.selector|s in (own.slots but (isa @ object))} |
								not(get(s,self) % (function U unbound_symbol U environment))}
					ibserialize_prop(self, prop, p, ctx),
				putc(14,p),
				ctx.toplevel? := top?)
		else putc(10,p))]

[private/ibserialize(self:thing, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@thing(~S) // self,
	if shouldSerialize?(self,15,p, ctx)
		ibserialize(self.name,p, ctx)]

;	let z := ctx[self]
;	in (if (z > 0)
;			(putc(34, p),
;			//[5] ~S pop oid ~S --> // self, z,
;			ibserialize(z, p, ctx))
;		else if (not(ctx.toplevel_only?) | ctx.toplevel? | self % ctx.toSerialize?)
;			let top? := ctx.toplevel?, own := owner(self)
;			in (ctx.toplevel? := false,
;				newOid(self, 15, p, ctx),
;				//ctx.toSerialize?[self] := false,
;				//[5] ~S push oid ~S <-- // self, ctx.currentOid,
;				ibserialize!(self.name,p, ctx),
;				ibserialize(own,p, ctx),
;				for prop in {s in {s.selector|s in (own.slots but (isa @ object) but (name @ thing))} |
;								not(get(s,self) % (function U unbound_symbol U environment))}
;					ibserialize_prop(self, prop, p, ctx),
;				putc(16,p),
;				ctx.toplevel? := top?)
;		else putc(10,p))]

[private/ibserialize(self:module, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@module(~S) // self,
	if shouldSerialize?(self,8,p, ctx)
		(ibserialize(self.name.name,p, ctx))]
/*
[private/ibserialize!(self:symbol, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize!@symbol(~S) // self,
	if shouldSerialize?(self, 38, p, ctx)
		(ibserialize(self.module!, p, ctx),
		ibserialize(self.name, p, ctx))]
*/
[private/ibserialize(self:symbol, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@symbol(~S) // self,
	if shouldSerialize?(self, 12, p, ctx)
		(ibserialize(self.module!, p, ctx),
		ibserialize(self.name, p, ctx))]

[private/ibserialize(self:class, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@class(~S) // self,
	if shouldSerialize?(self,2,p, ctx)
		ibserialize(self.name,p, ctx)]

[private/ibserialize(self:table, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@table(~S) // self,
	ctx.toSerialize? :add self,
	for x in list{x in self.mClaire/graph|known?(x)}
		ctx.toSerialize? :add x,
	ibserialize@object(self, p, ctx)]

[private/ibserialize(self:system_thing, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@system_thing(~S) // self,
	if shouldSerialize?(self,37,p, ctx)
		ibserialize(self.name,p, ctx)]

[private/ibserialize(self:bag, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@bag(~S) // self,
	newOid(self, 18, p, ctx),
	//[5] ~S push bag oid ~S <-- // self, ctx.currentOid,
	for i in self
		(if known?(i) ibserialize(i, p, ctx)
		else putc(10,p)),
	case self
		(list (if (of(self) = {}) putc(19,p)
				else (putc(22,p), ibserialize(of(self),p, ctx))),
		set (if (of(self) = {}) putc(20,p)
				else (putc(23,p), ibserialize(of(self),p, ctx))),
		tuple putc(21,p))]


[private/ibserialize(self:array, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@array(~S) // self,
	if shouldSerialize?(self,25,p, ctx)
		(for i in (1 .. length(self)) 
			when x := self[i] in ibserialize(x,p, ctx)
			else putc(10,p),
		if (of(self) = {}) putc(26,p)
		else (putc(27,p), ibserialize(of(self),p, ctx)))]

[private/ibserialize(self:restriction, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@restriction(~S) // self,
	ctx.toSerialize? :add self,
	ibserialize@object(self,p, ctx)]

[private/ibserialize(self:collection, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@collection(~S) // self,
	ctx.toSerialize? :add self,
	ibserialize@object(self,p, ctx)]

[private/ibserialize(self:exception, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@exception(~S) // self,
	ctx.toSerialize? :add self,
	ibserialize@object(self,p, ctx)]


[private/ibserialize(self:global_variable, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@global_variable(~S) // self,
	if shouldSerialize?(self,24,p, ctx)
		(ibserialize(self.name,p, ctx),
		ibserialize(range(self),p, ctx),
		ibserialize(value(self),p, ctx))]

[private/ibserialize(self:boolean, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@boolean(~S) // self,
	if self putc(4,p) else putc(5,p)]


[private/ibserialize(self:integer, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@integer(~S) // self,
	if (self < 256 & self > -256)
		(if (self > 0) (putc(28,p),externC("unsigned char c = self;p->put((char)c)"))
				  else (putc(29,p),externC("char c = -self;p->put((char)c)")))
	else (putc(30,p), puti(self,p))]

[private/ibserialize(self:string, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize(~S) // self,
	putc(6,p),
	ibserialize(length(self), p, ctx),
	princ(self)]
			
[private/ibserialize(self:char, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize(~S) // self,
	putc(7,p),
	putc(self,p)]

[private/ibserialize(self:float, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize(~S) // self,
	putc(9,p),
	externC("static char buf[256]"),
	externC("sprintf(buf,\"%.20f\",self)"), //<sb> fix precision pb: was %g
	ibserialize@string(externC("buf", string), p, ctx)]
			
[private/ibserialize(self:any, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@any(~S) // self,
	putc(10,p)] //<sb> i.e. put unknown


[private/ibserialize(self:system_object, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@system_object(~S) // self,
	error("serialization of system_object (~S) unsupported", self)]

[private/ibserialize(self:blob, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@blob(~S) // self,
	if shouldSerialize?(self, 39, p, ctx)
		let idx := get_index(self)
		in (set_index(self, 0),
		    ibserialize(length(self), p, ctx),
		    freadwrite(self, p),
		    set_index(self, idx))]

[private/ibserialize(self:clob, p:port, ctx:serialize_context) : void ->
	//[5] ibserialize@clob(~S) // self,
	if shouldSerialize?(self, 40, p, ctx)
		let idx := get_index(self)
		in (set_index(self, 0),
		    ibserialize(length(self), p, ctx),
		    freadwrite(self, p),
		    set_index(self, idx))]

//(interface(ibserialize))

// *********************************************************************
// *   Part 3: unserialize                                             *
// *********************************************************************


private/multiValuedBreak <: thing()
private/breakList :: multiValuedBreak()
private/breakTypedList :: multiValuedBreak()
private/breakSet :: multiValuedBreak()
private/breakTypedSet :: multiValuedBreak()
private/breakArray :: multiValuedBreak()
private/breakTypedArray :: multiValuedBreak()
private/breakTuple :: multiValuedBreak()
private/breakObject :: multiValuedBreak()


private/TMP:port := port!()

[private/bunint(p:port) : integer ->
	let i := 0
	in (externC("int v = 0; for(;v < sizeof(CL_INT);v++) {"),
		externC("unsigned char c = p->get()"),
		externC("i |= (CL_INT)((CL_INT)c << (v << 3));}"), i)]

[private/bunid(p:port, ctx:unserialize_context) : integer ->
	let oid := (let x := ibunserialize(p,ctx)
					in (if not(x % integer) error("bunid read ~S instead of an integer", x),
						x as integer))
	in (//[5] bunid ~S // oid,
		when x := ctx.unserialized[oid] in error("bunid, oid ~S is already known!?", oid),
		oid)]
	
[private/bunoid(p:port, ctx:unserialize_context) : any ->
	let oid := (let x := ibunserialize(p,ctx)
				in (if not(x % integer) error("bunoid read ~S instead of an integer", x),
					x as integer))
	in (//[5] bunoid ~S // oid,
		when x := ctx.unserialized[oid] in x 
		else error("bunoid ~S is an invalid oid!?", oid))]

[private/bunmodule(p:port, ctx:unserialize_context) : module ->
	let oid := bunid(p,ctx),
		n:string := (let x := ibunserialize(p,ctx)
					in (if not(x % string) error("bunmodule read ~S instead of a string", x),
						x as string)),
		mod := get_value(n)
	in (//[5] bunmodule ~S // mod,
		if not(mod % module) error("bunmodule expected a module instead of ~S", mod),
		ctx.unserialized[oid] := mod,
		mod as module)]

[private/bunstring(p:port, ctx:unserialize_context) : string ->
	let tmp := TMP,
		len:integer := (let x := ibunserialize(p,ctx)
						in (if not(x % integer) error("bunstring expected an integer instead of ~S", x),
							x))
	in (mClaire/set_length(tmp,0),
		externC("while(len--) {"),
		if eof?(p) error("bunstring encountered premature eof"),
		externC("char c = p->get(); tmp->put(c);}"),
		let s := string!(tmp)
		in (//[5] bunstring ~S // s,
			s))]


[private/bunsymbol(p:port, ctx:unserialize_context) : symbol ->
	let oid := bunid(p,ctx), mod := ibunserialize(p,ctx)
	in (if not(mod % module) error("bunsymbol expected a module instead of ~S", mod),
		let m:module := (mod as module), res:symbol := claire.name,
				n:string := (let x := ibunserialize(p,ctx)
							in (if not(x % string) error("bunsymbol read ~S instead of a string", x),
								x as string))
		in (when sy := get_symbol(m,n)
			in res := (sy as symbol)
			else error("bunsymbol error, ~S/~A is an undefined symbol",mod,n),
			ctx.unserialized[oid] := res,
			//[5] bunsymbol ~S // res,
			res))]
/*
[private/bunsymbol!(p:port, ctx:unserialize_context) : symbol ->
	let oid := bunid(p,ctx), mod := ibunserialize(p,ctx)
	in (if not(mod % module) error("bunsymbol! expected a module instead of ~S", mod),
		let m:module := (mod as module), res:symbol := claire.name,
				n:string := (let x := ibunserialize(p,ctx)
							in (if not(x % string) error("bunsymbol! read ~S instead of a string", x),
								x as string))
		in (when sy := get_symbol(m,n)
			in res := (sy as symbol)
			else res := symbol!(n, m),
			ctx.unserialized[oid] := res,
			//[5] bunsymbol! ~S // res,
			res))]
*/
[private/bunbagarray(p:port, ctx:unserialize_context) : (bag U array) ->
	let l := list<any>(), oid := bunid(p,ctx),
		res := (while not(eof?(p))
					let x := ibunserialize(p,ctx)
					in (case x
						({breakTypedList} break(cast!(l, ibunserialize(p,ctx))),
						{breakList} break(cast!(l, {})),
						{breakTypedSet} break(cast!(set!(l), ibunserialize(p,ctx))), 
						{breakSet} break(cast!(set!(l), {})), 
						{breakTypedArray} break(array!(cast!(l, ibunserialize(p,ctx)))),
						{breakArray} break(array!(cast!(l, {}))),
						{breakTuple} break(tuple!(l)),
						any l :add x))) 
			in (ctx.unserialized[oid] := res,
				//[5] bunbagarray ~S // res,
				res as (bag U array))]

[private/bunobject(p:port, ctx:unserialize_context) : object ->
	let s := unknown, val := unknown, oid := bunid(p,ctx), c := ibunserialize(p,ctx), i := 0,
		obj := (if not(c % class) error("bunobject expected a class instead of ~S",c),
				mClaire/new!(c as class))
	in (ctx.unserialized[oid] := obj, // ensure correct refenrencing
		//[5] ==== bunobject of class ~S // c,
		while not(eof?(p))
			(s := ibunserialize(p,ctx), // pop slot's selector
			if (s = breakObject) break(),
			//[5] bunslot ~S @ <~S> // s, owner(obj),
			if not(s % symbol) error("bunobject expected a valid symbol instead of ~S (class ~S)",s,c),
			s := get(s as symbol),
			if not(s % property) error("bunobject expected a property instead of ~S (class ~S)",s,c),
			val := ibunserialize(p,ctx),
			//[5] bunslotval ~S @ <~S> <--- ~S // s, owner(obj), val,
			let sl := @(s as property, c as class)
			in (if (sl.default != val & not(val % range(sl)))
					error("bunobject type error, can't put ~S in ~S @ ~S of range ~S",val,s,c,sl.range)),
			if (not(val % port) | val % blob) put(s as property, obj, val)),
		if (s != breakObject) error("bunobject encountered premature eof"),
		//[5] ==== bunobject call complete! on <~S> // owner(obj),
		if (c.open != ephemeral() & not(obj % c.instances))
			mClaire/add!(instances, c, obj),
		mClaire/complete!(obj))]

[private/bunthing(p:port, ctx:unserialize_context) : object ->
	let oid := bunid(p,ctx),
		nm := ibunserialize(p,ctx)
	in (if not(nm % symbol) error("bunthing expected a symbol instead of ~S", nm),
		let x := get(nm as symbol)
		in (if not(x % thing) error("bunthing expected a thing ~S instead of ~S", nm, x),
			ctx.unserialized[oid] := x,
			x as object))]


/*	let s := unknown, val := unknown, oid := bunid(p,ctx),
		nm := ibunserialize(p,ctx), c := ibunserialize(p,ctx),
		unamed? := (nm = get_symbol("unamed")),
		obj := (if not(c % class) error("bunthing expected a class instead of ~S",c),
				if not(nm % symbol) error("bunthing expected a symbol instead of ~S",nm),
				when x := (if unamed? unknown else get(nm as symbol)) in
					(//[5] ==== bunthing existing ~S // x,
					ctx.unserialized[oid] := x, // ensure correct referencing
					if not(owner(x) = (c as class)) error("bunthing try to update ~S:~S with an object of class ~S!",x,owner(x),c),
					x) else (//[5] ==== bunthing new!@~S with name ~S // c, nm,
							let x := (if unamed? mClaire/new!(c as class)
										else mClaire/new!(c as class, nm))
							in (ctx.unserialized[oid] := x, // ensure correct refenrencing
								x)))
	in (while not(eof?(p))
			(s := ibunserialize(p,ctx), // pop slot's selector
			if (s = breakObject) break(),
			//[5] bunslot ~S @ <~S> // s, owner(obj),
			if not(s % symbol) error("bunthing expected a valid symbol instead of ~S (class ~S)",s,c),
			s := get(s as symbol),
			if not(s % property) error("bunthing expected a property instead of ~S (class ~S)",s,c),
			val := ibunserialize(p,ctx),
			//val := ibunserialize(p,ctx),
			let sl := @(s as property, c as class)
			in (if (sl.default != val & not(val % range(sl)))
					error("bunthing type error, can't put ~S in ~S @ ~S of range ~S)",val,s,c,sl.range)),
			if not(val % port) put(s as property, obj, val)),
		if (s != breakObject) error("bunthing encountered premature eof"),
		//[5] ==== bunthing call complete! on <~S> // owner(obj),
		if (c.open != ephemeral() & not(obj % c.instances) & not(unamed? & c = table))
			mClaire/add!(instances, c, obj),
		if (c != table) mClaire/complete!(obj)
		else obj) as object]
*/
[private/bunvar(p:port, ctx:unserialize_context) : global_variable ->
	let oid := bunid(p,ctx), nm := ibunserialize(p,ctx), r := unknown, val := unknown,
		res := (if not(nm % symbol) error("bunvar expected a symbol instead of ~S",nm),
				when x := get(nm as symbol) in
					(ctx.unserialized[oid] := x, // ensure correct refenrencing
					//[5] bunvar existing ~S // x,
					r := ibunserialize(p,ctx),
					if not(r = range(x)) error("bunvar try to update ~S's range (~S) with ~S", x, range(x), r),
					x) else (//[5] bunvar ~S // nm,
							r := ibunserialize(p,ctx),
							if not(r % type) error("bunvar range type error, ~S is not a type", r),
							let x := mClaire/new!(global_variable, nm)
							in (put(range, x, r),
								ctx.unserialized[oid] := x, // ensure correct referencing
								x)))
	in (val := ibunserialize(p,ctx),
		put(value, res as global_variable, val),
		if not(res % global_variable.instances)
			mClaire/add!(instances, global_variable, res),
		mClaire/complete!(res) as global_variable)]
		 
	
[private/bunclass(p:port, ctx:unserialize_context) : class ->
	let oid := bunid(p,ctx), symb := ibunserialize(p,ctx),
		res := (if not(symb % symbol) error("~S is not a symbol!", symb),
			get@symbol(symb))
	in (//[5] bunclass ~S // res,
		if not(res % class) error("~S does not beong to class",res),
		ctx.unserialized[oid] := res, res as class)]

[private/bunsysthing(p:port, ctx:unserialize_context) : system_thing ->
	let oid := bunid(p,ctx), symb := ibunserialize(p,ctx),
		res := (if not(symb % symbol) error("~S is not a symbol!", symb),
			get@symbol(symb))
	in (//[5] bunsysthying ~S // res,
		if not(res % system_thing) error("~S does not belong to system_thing",res),
		ctx.unserialized[oid] := res, res as system_thing)]

[private/buntype(p:port, ctx:unserialize_context) : Type ->
	let oid := bunid(p,ctx), res := ibunserialize(p,ctx)
	in (//[5] buntype ~S // res,
		if not(res % Type) error("~S is not a Type!", res),
			ctx.unserialized[oid] := res, res as Type)]

[private/bunblob(p:port, ctx:unserialize_context) : blob ->
	let oid := bunid(p,ctx),
	    sz := ibunserialize(p,ctx)
	in (//[5] bunblob ~S // sz,
		if not(sz % integer) error("~S is not a blob size, integer expected!", sz),
		let b := blob!()
		in (freadwrite(p, b, sz),
		    ctx.unserialized[oid] := b,
		    b))]

[private/bunclob(p:port, ctx:unserialize_context) : clob ->
	let oid := bunid(p,ctx),
	    sz := ibunserialize(p,ctx)
	in (//[5] bunclob ~S // sz,
		if not(sz % integer) error("~S is not a blob size, integer expected!", sz),
		let b := clob!()
		in (freadwrite(p, b, sz),
		    ctx.unserialized[oid] := b,
		    b))]

[private/ibunserialize(p:port, ctx:unserialize_context) : any ->
	let tag := externC("p->get()",integer),
		bun := (case tag
				({2} bunclass(p,ctx),
				{4} true,
				{5} false,
				{6} bunstring(p,ctx),
				{7} externC("char_I_integer(p->get())", char),
				{8} bunmodule(p,ctx),
				{9} let x := ibunserialize(p, ctx)
					in (if not(x % string) error("~S does not belong to string", x),
						float!(x)),
				{10} unknown,
				{11} buntype(p,ctx),
				{12} bunsymbol(p,ctx),
				{13} bunobject(p,ctx),
				{14} breakObject,
				{15} bunthing(p,ctx),
				{16} breakObject,
				{18, 25} bunbagarray(p,ctx),
				{19} breakList,
				{20} breakSet,
				{21} breakTuple,
				{22} breakTypedList,
				{23} breakTypedSet,
				{24} bunvar(p,ctx),
				{26} breakArray,
				{27} breakTypedArray,
				{28} let i := 0 in (externC("unsigned char c = p->get();i = (CL_INT)c"), i),
				{29} let i := 0 in (externC("unsigned char c = p->get();i = (CL_INT)c"), -(i)),
				{30} bunint(p),
				{34} bunoid(p,ctx),
				{37} bunsysthing(p,ctx),
				{39} bunblob(p,ctx),
				{40} bunclob(p,ctx),
//				{38} bunsymbol!(p,ctx),
				any error("ibunserialize found an invalid tag (~S)",tag)))
		in (//[5] bun ~S // bun,
			bun)]
	

// *********************************************************************
// *   Part 4: api                                                     *
// *********************************************************************

// @cat @xl Serialization
// @section I/O, Modules and system interface
// XL CLAIRE distribution comes with the module Serialize that provide
// generic mechanism (using CLAIRE reflection) for writing/reading CLAIRE
// data structures to/from a communication port.
// The ability to convert a data structure to a binary stream can be used for
// Inter Process Communication (IPC) to exchange objects over a network or to
// store on the hard disk a set of object that belong to a user session.
// For instance :
// \code
// b :: blob!()
// (serialize(b, 12), serialize(b, list(12)))
// (assert(unserialize(b) = 12)
// (assert(unserialize(b) = list(12))
// \/code
// The example above illustrates the simple case when the serialized data represent
// a primitive object (an integer and a list with an integer),
// sometimes we need to serialize a tree of objects having relations one to each other in
// a single step and we would like the serialize process to be recursive :
// \code
// A <: ephemeral_object()
// B <: ephemeral_object(a:A)
// 
// b :: blob!()
// (serialize(b, false, B(a = A())))
// (assert(known?(a, unserialize(b))))
// \/code
// We use a serialize restriction that take a top? flag that tell whether the
// serialization should be simple (when top? is true) or recursive (when top?
// is false). By default serialize in non-recursive :
// \code
// serialize(b, x) <=> serialize(b, false, x)
// \/code
// When used recursively, serialize will traverse the object relation such to
// serialize related objects. As such it would serialize the whole database but
// it doesn't because named objects (class, property...) are not serialized.
// When a named object is serialized we only save its symbol. It comes the
// important rule that the process that unserialize a data stream should have
// in its database all named objects referenced by the data stream (e.g. classes
// have to be defined in both serializer and unserializer process). The recursion
// rules are as follow :
// \ul
// \li primitive are simple case and always serialized
// \li tables are always serialized and a recursion is always performed for objects
// that are referenced by the table.
// \li bags and arrays are always serialized and the recursion is always done for bag's elements.
// \li for named objects only the name is serialized
// \li for any other objects the recursion is made for each slots. So does related
// objects when top? is false.
// \/ul
// Notice that an inverse relation that should exists between a unserialized object
// and the object database is built during unserialization. Also notice that
// when an object is unserialized the close constructor is called so that if you
// serialize an exception, the unserialize process will throw the error (which can
// be used as an event). Here is a sample method that applies a property with a list
// of argument (like apply) but does it in a child process. The result is transmitted
// between the child and the parent through a pipe using serialization facility :
// \code
// [fork_apply(p:property, l:list) : any ->
// 	let s := socketpair() // create a pipe
// 	in (if forker?()
// 			// parent process :
// 			(fclose(s[2]),
// 			let x := (try unserialize(s[1]) // read the result on the pipe
// 						catch any exception!()), // and catch the error if any
// 				st := waitpid(forked()) // wait for child termination
// 			in (if (st[1] != WEXITED & st[3] != 0)
// 					error("fork_apply(~S, ~S) failed with ~S", p, l, st),
// 				fclose(s[1]),
// 				case x (exception close(x)),
// 				x))
// 		else
// 			// child process :
// 			(fclose(s[1]), 
// 			try serialize(s[2], apply(p, l)) // actually apply
// 			catch any serialize(s[2], exception!()),
// 			exit(0),
// 			0))]
// \/code
// When using serialize over a network one can use the same serialize_context object for
// the life time of the connection. The context object associates named objects with IDs
// and the reuse of the same context for multiple serialize operation will be more
// efficient than creating a new context for each serialized data, for instance :
// \code
// let c := client!("host.domain.com", 10000),
// 	ctx := serialize_context!()
// in (while (...)
// 		(serialize(c, ctx, ...),
// 		...))
// \/code
// @cat


VERSION_HEADER:string := "V2"

[claire/serialize(p:port, self:any, selfTree:any) : void -> 
	let old:port := use_as_output(p),
		ctx := serialize_context()
	in (preSerialize(self,ctx),
		preSerialize(selfTree,ctx),
		fwrite(VERSION_HEADER, p),
		putc(18,p),
		putc(28,p),
		putc(0,p),
		ctx.toplevel_only? := false,
		ibserialize(selfTree, p, ctx),
		ctx.toplevel_only? := true,
		ibserialize(self, p, ctx),
		putc(19,p),
		use_as_output(old))]
		
// @doc @xl Serialization
// When top? is true serialize(p,top?,self) writes on p a binary representation of
// self. When top? is false serialize(p,top?,self) writes on p the object tree
// starting at self (that is the object self and related objects). The data written
// on p can then be handle with unserialize to build back the object tree.
[serialize(p:port, top?:boolean, self:any) : serialize_context -> 
	let old:port := use_as_output(p),
		ctx := serialize_context()
	in (ctx.toplevel_only? := top?,
		preSerialize(self, ctx),
		fwrite(VERSION_HEADER, p),
		ibserialize(self, p, ctx),
		use_as_output(old),
		ctx)]

// @doc @xl Serialization
// serialize(p, self) is equivalent to serialize(p, true, self)
[serialize(p:port, self:any) : serialize_context -> serialize(p, true, self)]

[serialize(p:port, ctx:serialize_context, self:any) : serialize_context ->
	let old:port := use_as_output(p)
	in (preSerialize(self, ctx),
		fwrite(VERSION_HEADER, p),
		ibserialize(self, p, ctx),
		use_as_output(old),
		ctx)]

// @doc @xl Serialization
// unserialize(p) creates an object tree from a serialized data stream
// (as done with serialize). The calling process should have a correct reading
// environment, that is the same class definition that was used by the process
// that serialized the data.
[claire/unserialize(p:port) : any ->
	let ctx := unserialize_context(),
		ver_header := fread(p, 2)
	in (if eof?(p) error("unserialize has encountered a premature eof"),
		if (ver_header != VERSION_HEADER)
			error("Invalid version of serialized data ~A (~A expected)", ver_header, VERSION_HEADER),
		ibunserialize(p,ctx))]

[claire/serialize_context!() : serialize_context -> serialize_context()]
[claire/unserialize_context!() : unserialize_context -> unserialize_context()]

[claire/unserialize(p:port, ctx:unserialize_context) : any ->
	let ver_header := fread(p, 2)
	in (if eof?(p) error("unserialize has encountered a premature eof"),
		if (ver_header != VERSION_HEADER)
			error("Invalid version of serialized data ~A (~A expected)", ver_header, VERSION_HEADER),
		ibunserialize(p,ctx))]


/*[claire/fork_apply(p:property, l:list) : any ->
	let s := socketpair()
	in (if forker?()
			(fclose(s[2]),
			let x := (try unserialize(s[1]) catch any exception!()),
				st := waitpid(forked())
			in (if (st[1] != WEXITED & st[3] != 0)
					error("fork_apply(~S, ~S) failed with ~S", p, l, st),
				fclose(s[1]),
				case x (exception close(x)),
				x))
		else
			(fclose(s[1]),
			externC("LOGO = 0"),
			try serialize(s[2], apply(p, l))
			catch any serialize(s[2], exception!()),
			exit(0),
			0))]*/

