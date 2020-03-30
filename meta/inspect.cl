//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| inspect.cl                                                  |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+

// *********************************************************************
// * Contents                                                          *
// *      Part 1: Inspection                                           *
// *      Part 2: Trace                                                *
// *      Part 3: Stepper                                              *
// *      Part 4: Profiler                                             *
// *      Part 5: Code instrumentation (debug) XL                      *
// *********************************************************************


//<sb> in XL claire this file is quite different from <ycs> since
// the debugger has been entirely rewritten. Indeed, in XL claire
// the debugger uses an instrumented code which provide an
// homogeneous behavior in debug mode between interpreted and
// compiled code.


*showall*:boolean := true               // v0.01 stop the ... !

// *********************************************************************
// *      Part 1: Inspection                                           *
// *********************************************************************
// this is the method that the user calls
//


//<sb> v3.3.35 : meta toplevel (context)
inspect(self:any) : any
 -> let %read:any := {}, m0 := module!(), ix := 0
 	in (inspect_system(list<any>()),
 		case self
         (bag for i in (1 .. length(self)) printf("~A: ~S\n", i,self[i]),
          object for rel in owner(self).slots
                  let m := module!(name(selector(rel))) in
                    (ix :+ 1,            // ix is the position in the slots list
                     if (m = m0 | m = claire | *showall*)
                       let val := get(rel,self) in
                        printf("~A: ~I = ~I\n", ix,
                        			(set_color(34,0),
         							print(rel.selector),
         							set_color(30,0)),
                           (case val (bag (if (length(val) < 10) pretty_print(val)
                                           else (pretty_print(
                                                   list{val[i] | i in (1 .. 9)}),
                                                 color_princ(" `RED...`BLACK"))),
                                      any pretty_print(val))))),
          any printf("~I\n", pretty_print(self))),
        inspect_system(list<any>(self)),
        None)

// this is the inspect top_level
//<sb> v3.3.35 : meta toplevel (context)
inspect_loop(%read:any, old:list) : any
 -> (let self:any := old[1] in
       (if (case %read (Call %read.selector = put))
           let n:integer := %read.args[1],
               s:symbol := extract_symbol(%read.args[2]) in
             (if not(n % integer) error("[128] ~S should be an integer", n),
              let val := get_from_integer(self, n) in
                (put(value, new(global_variable, s), val),
                 inspect(val),
                 old := val cons old))
        else if (case %read (unbound_symbol %read.name.name = "up")) //<sb> was (%read = up)
           (if (length(old) > 1) (old := cdr(old), inspect(old[1]))
           else printf("`RED => top of inspect stack.\n"))
        else if (%read % integer)
           let val := get_from_integer(self, %read) in
             (if (val % bag & not(val))
                 	printf("`RED => the bag is empty\n") //<sb> v3.3.35
                 else
		             (old := val cons old, inspect(val)))
        else if (%read % object) (shrink(old,0), old :add %read,
        		/*old := %read cons old,*/ inspect(%read)) //<sb> v3.3.35 was % thing
        else printf("`RED => given to inspector is wrong.`BLACK \n")),
     inspect_system(old),
     0)

// get the information bound to the index
//
get_from_integer(self:any,n:integer) : any
 -> (if (self % bag)
        (if (n > 0 & n <= length(self)) self[n]
         else error("~A is not a good index for ~S", n))
     else let l := owner(self).slots in
            (if (n > 0 & n <= length(l)) get@slot(l[n], self)
             else error("~A is not a good index for ~S", n)))

// *********************************************************************
// *      Part 2: Trace methods                                        *
// *********************************************************************
// instrument the code generated from the rules

/*trace_on(self:any) : any
 -> (case self
      (property (if (self = spy)
                   let m := (spy @ void) in (if m put(Kernel/spy!, system, m))
                 else if (self = where) system.Kernel/call_count := 1
                 else (put(trace!, self, 5 - system.verbose),
                 		printf("`GREENactivate trace on ~S\n", self))),
       environment put(trace!, system, 1),
       module (if (self.mClaire/status > 2) self.mClaire/status := 4,
               for m in self.parts trace_on(m)),
       port put(ctrace, system, self),
       string put(ctrace, system, fopen(self, "w")),
       integer put(verbose,system,self),
       any error("[129] trace not implemented on ~S\n", self)),
      self)

untrace(self:any) : any
 -> (case self
      (property (if (self = spy) put(Kernel/spy!, system, unknown)
                 else if (self = where) system.Kernel/call_count := -1
                 else (put(trace!, self, 0),
                 		printf("`GREENdeactivate trace on ~S\n", self))),
       environment put(trace!, system, 0),
       module (if (self.mClaire/status = 4) self.mClaire/status := 3,
               for m in self.parts untrace(m)),
       port put(ctrace, system, stdout),
       any error("[130] untrace not implemented on ~S\n", self)),
      self)
*/
// a filter to restrict the impact of spy
// we put the special value nil (emply list of demons => OK) to mark that spying
// should be waken up on properties from l
/*spy(l:listargs)  : void
  -> (let m := (spy @ void) in
       (if m (put(Kernel/spy!, system, m),
              for f in property (if (f % l) f.mClaire/if_write := nil))))

*/
/*
// note: trace behavior for output statements defined in CLAIRE1 (self_eval)
self_trace(self:Trace) : any
 ->  let a := self.args in
       (if (length(a) = 1)
           let a1 := eval(a[1]) in
             (if (system.trace! = 0) put(trace!, system, 1), trace_on(a1))
        else self_eval(self))

(let x := get(functional, self_trace @ Trace) in
  (if known?(x) put(mClaire/evaluate, Trace, x)))
*/
// used to trace the trigger of a rule
//
trace_rule(R:relation,s:string,x:any,y:any,u:any,v:any) : void
 -> (if ((mClaire/if_write.trace! + system.verbose) >= 5)
        let p := get(ctrace, system) in
          (if known?(p) p := use_as_output(p),
           printf("--- the rule ~A is triggered for (~S,~S) by an update ~S(~S) ~A ~S \n",
                  s, u, v, R, x, (if multi?(R) ":add" else ":="), y),
           if known?(p) use_as_output(p)))



// ******************************************************************
// *    Part 3: The Stepper                                         *
// ******************************************************************
// the stepper interface is quite simple and could be improved
//

// memory usage statistics for a class
mem(c:class) : integer
  -> let n := 0 in
       (for x in c.instances
          (n :+ slot_get(x,0,integer),         // size of chunk
           for sl in c.slots
             let rs := sl.range in
               (if (rs = float) n :+ 5
                else if (rs = string)
                  (when st := get(sl,x) in 
                    n :+ min(5, length(st as string) / 2))    // upper bound !
                else if (rs <= bag)
                  (when l := get(sl,x) in
                    n :+ nth_get(l as bag,0)))),
        n)

// *********************************************************************
// *      Part 4: Profiler                                             *
// *********************************************************************

// we use a counter object for the 5 interesting values  and
// we use the reified slot to store the counter (thus no profiling on reified)
claire/PRcount <: object(rtime:integer = 0,     // time that has elapsed in the property
                         rdepth:integer = 0,    // counter of recursion (only register 1st)
                         rnum:integer = 0,      // number of calls
                         rloop:integer = 0,     // counter of loops
                         rstart:integer = 0)    // start time (1st entry)

// get & create if needed a PRcounter
claire/PRget(p:property) : PRcount
 -> let x := p.reified in
     (if (owner(x) = PRcount) (x as PRcount)
      else if (x = true) error("[131] Cannot profile a reified property ~S",p)
      else (x := PRcount(), p.reified := x, x as PRcount))

// get & create if needed a PRcounter
claire/PRlook(p:property) : any -> show(PRget(p))

// show the profiler statistics on one property
claire/PRshow(p:property) : void
 -> let x := p.reified in
      (case x (PRcount printf("~S: ~A calls -> ~A clock tics\n",p, x.rnum, x.rtime)))

// elapsed time
claire/PRtime(p:property)  : integer
 -> let x := p.reified in
      (case x (PRcount x.rtime, any 0))

claire/PRcounter(p:property)  : integer
 -> let x := p.reified in
      (case x (PRcount x.rnum, any 0))


// show the profiler statistics on the 10 most important properties
claire/PRshow() : void
 -> let l := list<property>() in
      (for p in property
        (if exists(i in (1 .. min(10,length(l))) |
                    (if ((PRtime(p) > PRtime(l[i])) |
                         (PRtime(p) = PRtime(l[i]) & PRcounter(p) > PRcounter(l[i])))
                        (l := nth+(l,i,p), true))) nil
         else if (length(l) < 10) l :add p),
       shrink(l,10),
       for p in l
          (if (PRcounter(p) > 0)
              (printf("-----------------------------------\n"),
               PRshow(p),
               for p2 in PRdependent[p]
                  (if (PRtime(p2) > 0) printf("   * ~I",PRshow(p2))))))

// reuse from lexical_build in pretty.cl
// returns the list of properties that are used by a method
PRdependent[p:property] : set[property] := set<property>()
PRdependentOf[p:property] : set[property] := set<property>()
dependents(self:method) : set[property] //
 -> set<property>{p in dependents(self.formula.body) |
                  exists(r in p.restrictions | r % method)}

// this is really cute ....   v3.2.58: fix typing
dependents(self:any) : any
 -> (case self
       (Call add(dependents(self.args),self.selector),
        Instruction let s := set<property>() in
                      (for sl in self.isa.slots
                         s := s U dependents(get(sl, self)),
                       s),
         bag let s := set<property>() in
                (for x in self s := s U dependents(x),
                 s),
         property set<property>(self),
         any set<property>()))

// used to set up the dependence
(PRdependent.inverse := PRdependentOf)
claire/PRdepends(p:property,p2:property) : void
 -> (PRdependent[p] :add p2, unknown)


// ******************************************************************
// *    Part 5: Code instrumentation (debug)                        *
// ******************************************************************


claire/dump_stack() : void ->
	printf("===== Dump stack ======\n~I~I======================\n",
		for i in (0 .. system.mClaire/index - 1)
			printf("~S: ~S\n", i, mClaire/get_stack(i)),
		(printf("index: ~S\n", system.mClaire/index),
		printf("base: ~S\n", system.mClaire/base),
		printf("trace!: ~S\n", system.mClaire/trace!),
		printf("debug!: ~S\n", system.mClaire/debug!)))

//<sb> this file contains code for the debugger, how to
// locate instruction in a source file and how to equip the
// code such to control a program execution: generate
// backtrace and handle breakpoints/watchpoints.

// In this implementation (vs Yves's one) the code is equipped
// before being compiled such that we can homogeneously perform
// debug session for both interpreted and compiled code :)


//<sb> called by the close@Instruction constructor (in pretty.cl) 
// Here we try to locate the
// given instruction and map it in CODE_LOCS.
[Language/init_location(self:any) : void ->
	let matchident :=
			(case self
				(unbound_symbol self.name.name,
				Definition self.arg.name.name,
				Call+ ".",
				Call self.selector.name.name,
				Error "error",
				Handle "catch",
				While "while",
				Macro self.isa.name.name,
				Variable self.mClaire/pname.name,
				Assign "=",
				any ""))
	in (if (length(matchident) > 0)
			let idents := Reader/IDENTS,
				i := length(idents)
			in (while (i > 0)
					let loc := idents[i]
					in (if (loc[1] = matchident |
									(case self (Call (self.selector % {write,nth=} & loc[1] = "="))) |
									(case self (Call (self.selector = nth & loc[1] = "["))))
							(if (self % unbound_symbol | self % Variable)
								let l := copy(loc)
								in (l << 1,
									CODE_LOCS[self] := l)
							else
								(loc << 1,
								CODE_LOCS[self] := loc,
								shrink(idents, i - 1)),
							break()),
						i :- 1)))]

(Language/CAN_INIT_LOCATION? := true)

//<sb> equip method family takes an Instruction and a location that should
// de restore when the instruction terminates : the returned instruction is
// instrumented for debug.

[update_location!(loc:list) : any ->
	if loc Call(Core/update_location, loc)
	else 1]

[update_location!(self:any, loc:list) : any ->
	if loc
		let v := Variable(mClaire/pname = gensym("ULOCDBG"), iClaire/dindex = 1)
		in (Let(var = v, value = self,
				arg = Do(list(Call(Core/update_location, loc), v))))
	else self]

[pop_frame!(self:any) : any ->
	let v := Variable(mClaire/pname = gensym("POPFDBG"), iClaire/dindex = 1, index = *variable_index*)
	in (*variable_index* :+ 1,
		Let(var = v, value = self,
			arg = Do(list(Call(Core/pop_frame, list(system)), v))))]

[pop_handle!(self:any, hid:Variable) : any ->
	let v := Variable(mClaire/pname = gensym("POPHDBG"), iClaire/dindex = 1)
	in (Let(var = v, value = self,
			arg = Do(list(Call(Core/pop_handle, list(hid)), v))))]


[equip(self:any, poploc:list) : any ->
//	if (self = none) self := 1,
	if poploc
		Do(list(update_location!(poploc), self))
	else self]
//	update_location!(self, poploc)]

[equip(self:Instruction, poploc:list) : any ->
	when x := get(arg, self) in put(arg, self, equip(x, poploc)),
	when x := get(body, self) in put(body, self, equip(x, poploc)),
	when x := get(value, self) in put(value, self, equip(x, poploc)),
	when x := get(of, self) in put(of, self, equip(x, poploc)),
	when x := get(iClaire/other, self) in put(iClaire/other, self, equip(x, poploc)),
	when x := get(iClaire/test, self) in put(iClaire/test, self, equip(x, poploc)),
	when x := get(args, self) in put(args, self, equip_list(self.args, poploc, 1)),
	self]



[equip_list(self:list, poploc:list, indexstart:integer) : list ->
	let len := length(self),
		res := make_list(any, len)
	in (for i in (1 .. indexstart - 1)
			res add self[i],
		for i in (indexstart .. len - 1)
			res add equip(self[i], nil),
		if (len > indexstart - 1)
			res add equip(self[len], poploc),
		res)]
	

[equip(self:unbound_symbol, poploc:list) : any ->
	let loc := CODE_LOCS[self]
	in (if loc
			Do(list(update_location!(loc), self))
		else if poploc
			Do(list(update_location!(poploc), self))
		else self)]

[equip(self:Variable, poploc:list) : any ->
	update_location!(self, poploc)]


[equip(self:While, poploc:list) : any ->
	let loc := CODE_LOCS[self]
	in (put(test, self, equip(self.test, nil)),
		put(arg, self, equip(self.arg, nil)),
		update_location!(Do(list(update_location!(loc), self)), poploc))]

[equip(self:Error, poploc:list) : any ->
	let loc := CODE_LOCS[self],
		res:any := self
	in (if loc
			(if (length(self.args) > 1)
				put(args, self, equip_list(self.args, loc, 2)) // 2: skip the first static string
			else
				res := Do(list(update_location!(loc), self))),
		res)]

[equip(self:Construct, poploc:list) : any ->
	if not(self.args)
		(if poploc
			Do(list(update_location!(poploc), self))
		else self)
	else
		(put(args, self, equip_list(self.args, poploc, 1)),
		self)]


[equip(self:Call, poploc:list) : any ->
	if forall(x in self.args | case x (Variable true,
										Call[selector = externC] true,
										Instruction false,
										any true))
		update_location!(Do(list(update_location!(CODE_LOCS[self]), self)), poploc)
	else
		let loc := CODE_LOCS[self],
			res:any := self
		in (if not(loc) loc := poploc,
			if loc
				(if self.args
					put(args, self, equip_list(self.args, loc, 1))
				else
					res := update_location!(self, loc)),
			if (poploc & poploc != loc)
				update_location!(self, poploc)
			else res)]


[equip(self:Do, poploc:list) : any ->
	put(args, self, equip_list(self.args, poploc, 1)),
	self]

[equip(self:Case, poploc:list) : any ->
	let res:any := self
	in (if not(self.var % Variable)
			let v := Variable(mClaire/pname = gensym("CASEDBG"), iClaire/dindex = 1)
			in (res := Let(var = v, value = equip(self.var, nil),
							arg = self),
				self.var := v),
		let l := self.args,
			len := length(l),
			nl := make_list(any, len)
		in (for i in (1 .. len)
				(if (i mod 2 = 0) nl add equip(l[i], nil)
				else nl add l[i]),			
			put(args, self, nl)),
		update_location!(res, poploc))]

[equip(self:If, poploc:list) : any ->
	let res:any := self
	in (put(arg, self, equip(self.arg, nil)),
		put(iClaire/other, self, equip(self.iClaire/other, nil)),
		if (case self.iClaire/test (Variable false, Instruction true, any false))
			let vtest := Variable(mClaire/pname = gensym("IFDBG"), iClaire/dindex = 1)
			in (res := Let(var = vtest, value = equip(self.iClaire/test, nil), arg = self),
				put(iClaire/test, self, vtest)),
		update_location!(res, poploc))]

[equip(self:Let, poploc:list) : any ->
	let loc := CODE_LOCS[self.var],
		v := Variable(mClaire/pname = gensym("LETDBG"), iClaire/dindex = 1)
	in (put(value, self, equip(self.value, nil)),
		put(arg, self, Do(list(
				Call(Core/push_var, list(self.var.mClaire/pname.name, self.var)),
				update_location!(loc),
				Let(var = v, value = equip(self.arg, nil),
						arg = Do(list(
							Call(Core/pop_var, list(system)),
							v)))))),
		update_location!(self, poploc))]


[equip(self:When, poploc:list) : any ->
	let loc := CODE_LOCS[self.var],
		v := Variable(mClaire/pname = gensym("LETDBG"), iClaire/dindex = 1)
	in (put(value, self, equip(self.value, nil)),
		when ot := get(iClaire/other, self)
		in put(iClaire/other, self, equip(ot, nil)),
		put(arg, self, Do(list(
				Call(Core/push_var, list(self.var.mClaire/pname.name, self.var)),
				update_location!(loc),
				Let(var = v, value = equip(self.arg, nil),
						arg = Do(list(
							Call(Core/pop_var, list(system)),
							v)))))),
		update_location!(self, poploc))]


[equip(self:Iteration, poploc:list) : any ->
	let loc := CODE_LOCS[self.var],
		vbag := Variable(mClaire/pname = gensym("BITERDBG"), iClaire/dindex = 1),
		ivar := Variable(mClaire/pname = gensym("IITERDBG"), iClaire/dindex = 1),
		res := Let(var = vbag, value = equip(self.set_arg, nil), arg = self),
		doargs := list<any>()
	in (put(set_arg, self, vbag),
		doargs add Call(Core/push_var, list(self.var.mClaire/pname.name, self.var)),
		doargs add update_location!(loc),
		doargs add Let(var = ivar, value = equip(self.arg, nil),
						arg = Do(list(Call(Core/pop_var, list(system)), ivar))),
		self.arg := Do(doargs),
		update_location!(res, poploc))]

[equip(self:For, poploc:list) : any ->
	let loc := CODE_LOCS[self.var],
		vbag := Variable(mClaire/pname = gensym("BFORDBG"), iClaire/dindex = 1),
		vfor := Variable(mClaire/pname = gensym("RFORDBG"), iClaire/dindex = 1),
;		vidx := Variable(mClaire/pname = gensym("VFORDBG"), iClaire/dindex = 1),
;		letidx := Let(var = vidx, value = Call(Core/push_vars, list(system))),
		letbag := Let(var = vbag, value = equip(self.set_arg, nil)),
		letfor := Let(var = vfor, value = self),
		forargs := list<any>()
	in (put(set_arg, self, vbag),
		put(arg, letbag, Do(list(Call(Core/push_var, list(self.var.mClaire/pname.name, unknown)),
										letfor))),
		put(arg, self, Do(list(Call(Core/update_var,list(self.var.mClaire/pname.name, self.var)),
					update_location!(loc), equip(self.arg, nil)))),
		put(arg, letfor, Do(list(Call(Core/pop_var, list(system)), vfor))),
		update_location!(letbag, poploc))]


//<sb> a handle is a little tricky since we need a unique
// value that identifies the frame of the handle
[equip(self:Handle, poploc:list) : any ->
	let loc := CODE_LOCS[self],
		hid := Variable(range = string, iClaire/dindex = 1,
						mClaire/pname = gensym("HDLDBG")),
		lt := Let(var = hid, value = Call(uid, list(system)))
	in (put(arg, self,
				Do(list(Call(Core/push_handle, list(hid)),
						equip(self.arg, nil)))),
		put(iClaire/other, self, equip(self.iClaire/other, nil)),
		if loc
			//<sb> create a new frame for the handler (a copy of the original
			// handler frame - i.e. the frame containing try/catch keywords)
			// so that the broken frame still exists and that it
			// can be inspected through the stepper
			put(iClaire/other, self,
				Do(list(Call(Core/push_handle_frame, loc /+ list(hid)),
					self.iClaire/other))), //<sb> keep frames during handle...
		lt.arg := pop_handle!(self, hid),
		if poploc
			lt.arg := update_location!(lt.arg, poploc),
		lt)]


[equip(self:Assign, poploc:list) : any ->
	let loc := CODE_LOCS[self],
		v := Variable(mClaire/pname = gensym("ASGDBG"), iClaire/dindex = 1),
		narg := equip(self.arg, loc)
	in (put(arg, self, v),
		Let(var = v, value = narg,
			arg = Do(list(Call(Core/update_var, list(self.var.mClaire/pname.name, self.var)),
							self,
							update_location!(poploc),
							v))))]


[equip(self:Defclaire, poploc:list) : any -> self]

[equip(self:Definition, poploc:list) : any ->
	let loc := CODE_LOCS[self],
		vs := self.args,
		len := length(vs),
		res:any := self
	in (for i in (1 .. len)
			let a := vs[i]
			in (if (length(a.args) = 2)
					put(args, a, list(a.args[1], equip(a.args[2], (if (i < len) nil else loc))))),
		if (loc & len = 0)
			res := Do(list(update_location!(loc), res)),
		if poploc
			res := update_location!(res, poploc),
		res)]

[equip(self:Defobj, poploc:list) : any -> self]


[equip(self:Defrule, poploc:list) : any ->
	put(body, self, equip(self.body, nil)),
	self]

[equip(self:any) : any ->
	let x := equip(self, nil)
	in (lexical_build_equip(x, *variable_index*),
		reader.maxstack := *variable_index*,
		x)]

[equip(self:lambda) : any ->
	let loc := (if known?(body,self) CODE_LOCS[self.body] else nil)
	in (let b := Do()
		in (b.args add Call(Core/push_frame, list("placeholder")),
			for i in (1 .. length(self.vars))
				let x := self.vars[i]
				in (if (x.range != void)
						b.args add Call(Core/push_arg, list(x.mClaire/pname.name, x))),
			b.args add pop_frame!(self.body),
			put(body, self, b)),
		put(dimension, self, *variable_index*),
		self)]

[lexical_build_equip(self:any, n:integer) : void ->
	case self
		(bag for x in self lexical_build_equip(x, n),
		Let
			(if (self.var.iClaire/dindex > 0)
				(put(index, self.var, n),
				if (n > *variable_index*)
					*variable_index* := n,
				lexical_build_equip(self.value, n + 1),
				lexical_build_equip(self.arg, n + 1))
			else
				(lexical_build_equip(self.value, n),
				lexical_build_equip(self.arg, n))),
		Instruction
			for s in owner(self).slots
				let y := get(s, self)
				in lexical_build_equip(y, n),
		any none)]

