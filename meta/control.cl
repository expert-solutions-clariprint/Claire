//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| control.cl                                                  |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+

// *********************************************************************
// *     Part 1: If, Do, Let                                           *
// *     Part 2: set control structures                                *
// *     Part 3: other control structures                              *
// *     Part 4: the constructs                                        *
// *********************************************************************
// *********************************************************************
// *     Part 1: If, Do, Let                                           *
// *********************************************************************

//--------------- the IF --------------------------------------------
If <: Control_structure(test:any,arg:any,other:any = false)

self_print(self:If) : void
 -> printf("(~I~I~I)", (pretty.index :+ 1), printstat(self),
           (pretty.index :- 1))

printstat(self:If) : void
 -> printf("`BLUEif `BLACK~I ~I~I~I", (printexp(self.test, false), checkfar()),
           printif(self.arg), (pretty.index :- 3), printelse(self))

printif(self:any) : void
 -> (pretty.index :+ 3,
     if pretty.mClaire/pbreak
        let b_index := mClaire/buffer_length(),
            %l := pretty.index in
          (pretty.mClaire/pbreak := false,
           try print(self) catch much_too_far {},
         pretty.mClaire/pbreak := true,
         if short_enough(mClaire/buffer_length()) {}
         else (mClaire/buffer_set_length(b_index),
               pretty.index := %l,
               lbreak(),
               print(self)))
     else print(self))

printelse(self:If) : void
 -> (let e := get(other, self) in
       case e
        (If printf(" ~I`BLUEelse if `BLACK~I ~I~I~I", lbreak(),
                   printexp(e.test, false), printif(e.arg),
                   (pretty.index :- 3), printelse(e)),
         any (if (e != nil & e != false)
                let %l := pretty.index in
                  (printf(" ~I`BLUEelse `BLACK~I~S", lbreak(), set_level(1), e),
                   pretty.index := %l))))

// notice that the eval(test) is not a boolean thus the compiler will add
// something
// TODO: check that is is not too slow (may use a constant for _oid_(true))
self_eval(self:If) : any
 -> (let n := system.trace!,
 		 d := system.Kernel/debug!,
     	 x := eval(self.test) in
      (if (n > 0 & n <= system.Core/step!)
           (put(trace!, system, 0),
            put(Kernel/debug!, system, -1),
            printf("  `BLUEif ~S\n", x),
            put(Kernel/debug!, system, d),
            put(trace!, system, n)),
      let res :=
		 (if (x = true) eval(self.arg)
		   else if (x = false) eval(self.other)
		   else if x eval(self.arg)
		   else eval(self.other))
		in (if (n > 0 & n <= system.Core/step!)
	           (put(trace!, system, 0),
    	        put(Kernel/debug!, system, -1),
            	printf("  `BLUEif -> ~S\n", res),
    	        put(Kernel/debug!, system, d),
	            put(trace!, system, n)),
			res)))

//--------------------- block structure------------------------------
Do[args] <: Control_structure(args:list)

self_print(self:Do) : void
 -> (let %l := pretty.index in
       (printf("("),
        set_level(1),
        printdo(self.args, true),
        pretty.index := %l))

printdo(l:list,clo:boolean) : void
 -> (let len := length(l), n := len in
       for i in (1 .. len)
         let x := l[i], c := owner(x) in
         (if (c = Princ_wcl) princ(" "),
         case x (If printstat(x), any print(x)),
          n :- 1,
          if (c = Princ_wcl)
          	(if (i = len | owner(l[i + 1]) != Call_wcl)
          		princ(" ")),
          if (n = 0) (if clo princ(")"))
          else if (c != Princ_wcl & c != Call_wcl)
          		(printf(", "), lbreak())))


printblock(x:any) : void
 -> (case x (Do printdo(x.args, false), If printstat(x), any print(x)))

self_eval(self:Do) : any
 -> (let res:any := {} in (for %x in self.args res := eval(%x), res))

// ----------------- lexical variable definition -----------------------
Let <: Instruction_with_var(value:any,arg:any)

self_print(self:Let) : void
 -> (let %l := pretty.index in
       (set_level(1),
        printf("`BLUElet `BLACK~I := ~I~I", ppvariable(self.var),
               printexp(get(value, self), false), printbody(self)),
        pretty.index := %l))

printbody(self:Let) : void
 -> (let a := self.arg in
       case a
        (Let printf(",~I~I := ~I~I~I", lbreak(4), ppvariable(a.var),
                    printexp(get(value, a), false), (pretty.index :- 4),
                    printbody(a)),
         any printf(" `BLUEin `BLACK~I~S", lbreak(2), a)))

self_eval(self:Let) : any
 -> (let val := eval(self.value),
         n := system.trace!,
 		 d := system.Kernel/debug! in
       (write_value@Variable(self.var, val),
        let res := eval(self.arg)
        in (if (n > 0 & n <= system.Core/step!)
	           (put(trace!, system, 0),
    	        put(Kernel/debug!, system, -1),
    	        printf("  `BLUE~S := ~S\n", self.var, res),
    	        put(Kernel/debug!, system, d),
    	        put(trace!, system, n)),
        	res)))

// a when is a special Let that filters out the unknown value !
//
When <: Let(other:any = unknown)
self_print(self:When) : void
 -> (let %l := pretty.index in
       (set_level(1),
        printf("`BLUEwhen `BLACK~I := ~I `BLUEin `BLACK~I~S", ppvariable(self.var),
               printexp(get(value, self), false), lbreak(2), self.arg),
        if known?(other, self)
           printf(" ~I`BLUEelse `BLACK~I~S", lbreak(), set_level(1), self.other),
        pretty.index := %l))

self_eval(self:When) : any
 -> (let val := eval(self.value),
         n := system.trace!,
 		 d := system.Kernel/debug! in
       (if (n > 0 & n <= system.Core/step!)
           (put(trace!, system, 0),
            put(Kernel/debug!, system, -1),
            printf("  `BLUEwhen ~S := ~S\n", self.var, val),
            put(Kernel/debug!, system, d),
            put(trace!, system, n)),
        let res :=
			(if (val != unknown)
			   (write_value@Variable(self.var, val), eval(self.arg))
			else eval(self.other))
		in (if (n > 0 & n <= system.Core/step!)
	           (put(trace!, system, 0),
	           	put(Kernel/debug!, system, -1),
	            printf("  `BLUEwhen -> ~S\n", res),
    	        put(Kernel/debug!, system, d),
            	put(trace!, system, n)),
			res)))

// two special forms of Let:
// Let+(v,r(x),(r(x) := y),Let(v2,e,(r(x) := v,v2)))    <=>  let r(x) = y in e
// Let*(v,f(),Let(v1,v[1],...(Let(vn,v[n],e))   <=> let (v1,v2,...vn) := f() in e
//
Let+ <: Let()
Let* <: Let()

//note: the Let* is also used for multi-assignments
// Let*(v,f(),(v1 := v[1], v2 := v[2], ...))   <=>  (v1,v2,...vn) := f()
//
self_print(self:Let+) : void
 -> (let %l := pretty.index,
         l := (self.arg as Do).args in
       (set_level(1),
        printf("`BLUElet `BLACK~I := ~I `BLUEin `BLACK~I~S", printexp(self.value, false),
               printexp(l[1].args[3], false), lbreak(2), (l[2] as Let).value),
        pretty.index := %l))

self_print(self:Let*) : void
 -> (let %l := pretty.index,
         l := self.arg in
       (set_level(1),
        if (l % Let)
           printf("`BLUElet `BLACK(~I) := ~I~I",
                  (while true
                     (ppvariable(l.var),
                      let lnext := l.arg in
                        (if (case lnext
                              (Let
                                 (lnext.value % Call &
                                  lnext.value.args[1] = self.var)))
                            (princ(","), l := lnext)
                         else break(true)))),
                  printexp(get(value, self), false), printbody(l))
        else printf("(~I) := ~I",
                    (let %f := true in
                       for %a in l.args
                         (if %f %f := false
                          else princ(","),
                          ppvariable(%a.var))),
                    printexp(get(value, self), false)),
        pretty.index := %l))

// *********************************************************************
// *     Part 2: set control structures                                *
// *********************************************************************
Iteration <: Instruction_with_var(set_arg:any,arg:any)
iterate :: property()
Iterate :: property()

// for is the simplest evaluation loop
//
For <: Iteration()
self_print(self:For) : void
 -> printf("`BLUEfor `BLACK~I `BLUEin `BLACK~I ~I", ppvariable(self.var),
           (let %l := pretty.index in
              (set_level(),
               printexp(self.set_arg, false),
               pretty.index := %l)),
           (pretty.index :+ 2,
            lbreak(),
            print(self.arg),
            pretty.index :- 2))

self_eval(self:For) : any
 -> (let x := eval(self.set_arg),
         n := system.trace!,
 		 d := system.Kernel/debug! in
       (if (n > 0 & n <= system.Core/step!)
           (put(trace!, system, 0),
            put(Kernel/debug!, system, -1),
            printf("  `BLUEfor ~S in ~S\n", self.var, x),
            put(Kernel/debug!, system, d),
            put(trace!, system, n)),
        let res :=
			(try case x
			 (class for y in x.descendents
					 for z in y.instances
					   (write_value(self.var, z), eval(self.arg)),
			  array let n := length(x) in
					  for z in list{nth_get(x,i) | i in (1 .. n)}
						(write_value(self.var, z), eval(self.arg)),
			  Interval for y in (x.arg1 .. x.arg2)
						  (write_value(self.var, y), eval(self.arg)),
			  collection for y in x (write_value(self.var, y), eval(self.arg)),
			  any error("[136] ~S is not a collection !", x))
			catch return_error system.exception!.arg)
		in (if (n > 0 & n <= system.Core/step!)
           		(put(trace!, system, 0),
           		put(Kernel/debug!, system, -1),
	            printf("  `BLUEfor -> ~S\n", res),
	            put(Kernel/debug!, system, d),
    	        put(trace!, system, n)),
			res)))

//<lr>

iClaire/Tfor <: Iteration()

claire/traceTfor? :: property(open = 3, range = boolean)
claire/traceTfor?() : boolean -> false

claire/beforeTfor :: property(open = 3, range = any)
// [claire/beforeTfor(sfv:string,sfsa:string) : any -> 0]
[claire/beforeTfor(sfv:string,fsa:any) : any -> 0]

// tfor catch exceptions afterTfor must close(exception!()) at last
claire/afterTfor :: property(open = 3, range = any)
[claire/afterTfor(br:any,fr:any) : any -> fr]

[getFor(self:Tfor) : For -> For(var = self.var, set_arg = self.set_arg, arg = self.arg)]

[self_print(self:Tfor) : void
 -> printf("`BLUEtfor `BLACK~I `BLUEin `BLACK~I ~I", ppvariable(self.var),
           (let %l := pretty.index in
              (set_level(),
               printexp(self.set_arg, false),
               pretty.index := %l)),
           (pretty.index :+ 2,
            lbreak(),
            print(self.arg),
            pretty.index :- 2))]

[self_eval(self:Tfor) : any
-> let self_eval1 := @(self_eval,For)
    in ( if eval(Call(selector = traceTfor?, args = list<any>(void))) 
            eval(Call(selector = afterTfor, 
                        args = list(eval(Call(selector = beforeTfor, 
                                                args = list((print_in_string(),printf("~S",self.var),end_of_string()),
                                                            self.set_arg))),
                                    (try apply(self_eval1,list(getFor(self))) catch any exception!())   )))
        else apply(self_eval1,list<any>(getFor(self))))]

//<sb> v3.3.33 ffor
iClaire/Ffor <: Instruction_with_var(set_arg:any, arg:any, iClaire/forkedby:any)

[self_print(self:Ffor) : void
 -> let %l := pretty.index in
 	printf("`BLUEffor `BLACK~I `BLUEin `BLACK~I `BLUEby `BLACK~I ~I",
 			ppvariable(self.var),
           (set_level(),
            printexp(self.set_arg, false)),
           (printexp(self.forkedby, false),
           pretty.index := %l),
           (pretty.index :+ 2,
            lbreak(),
            print(self.arg),
            pretty.index :- 2))]

//<sb> parallel programing
[self_eval(self:Ffor) : any ->
	if not(Core/unix?()) //<sb> on window we can't fork !
		let res := list<any>(),
			l := list{i | i in eval(self.set_arg)}
		in (for i in l
				(write_value(self.var, i),
				res :add (try try eval(self.arg)
							catch any 
								Core/ffor_error(Core/childpid = getpid(),
										Core/childstr = (print_in_string(),print(exception!()),end_of_string()))
							catch any exception!())),
			cast!(res,{}))
	else let l := list{i | i in eval(self.set_arg)},
			N := eval(self.forkedby),
			childs := unknown,
			res := list<any>(),
			remain := length(l),
			len := remain,
			lindex := 1,
			n := system.trace!,
			d := system.Kernel/debug!
		in (if not(N % integer) error("[200] ~S : by range error ~S does not belong to integer", self, N),
			if (N <= 0) error("[201] ~S : negative by (~S) argument in dangerous", self, N),
			childs := list<list>{list<any>(-1,0,port!(),0)|i in (1 .. N)},
			if (n > 0 & n <= system.Core/step!)
	           (put(trace!, system, 0),
	            put(Kernel/debug!, system, -1),
	            printf("  `BLUEffor ~S in ~S by ~S\n", self.var, l, self.forkedby),
	            put(Kernel/debug!, system, d),
	            put(trace!, system, n)),
	        while (length(res) < len)
				(// start as much as possible childs (<= N)
				if (remain > 0)
					for i in (1 .. N)
						(if (remain = 0) break(),
						if (childs[i][1] = -1)
							let current := l[lindex]
							in (write_value(self.var, current),
								try let (s1, s2) := socketpair()
									in (if forker?()
											let c := childs[i]
											in (fclose(s1),
												//nonblock!(s2),
												remain :- 1,
												lindex :+ 1,						
												c[1] := forked(),
												c[2] := s2,
												c[4] := current)
										else
											(fclose(s2),
											serialize(s1,
													(try try eval(self.arg)
													catch any 
														Core/ffor_error(Core/childpid = getpid(),
																Core/childstr = (print_in_string(),print(exception!()),end_of_string()))
													catch any (fclose(s1), exit(1), 0))),
											fclose(s1),
											exit(0)))
								catch any none)), //<sb> must be a resource allocation error
				// read as much data as possible sent by pending childs
				for i in (1 .. N)
					let c := childs[i], s := c[2], pid := c[1], buf := c[3]
					in (if (pid != -1)
							(read!(s),
							if (select?(10) & readable?(s))
								(fwrite(fread(s, 1024), buf),
								if eof?(s)
									let st := waitpid(pid)
									in (if (st[1] = WEXITED & st[3] = 0)
											res :add (try unserialize(buf) catch any exception!())
										else res :add st,
										fclose(s),
										set_length(buf, 0),
										c[1] := -1,
										break()))))),
			for i in childs fclose(i[3]), //<sb> free buffers ...
			cast!(res,{}))]


// [collect VAR in SET_EXPR, ...] is the same as a "for", but returns the list of values
//
Collect <: Iteration(of:type)

self_print(self:Collect) : void
 -> printf("list{ ~I | ~I~I `BLUEin `BLACK~I}",
           (pretty.index :+ 2, printexp(self.arg, false)),
           lbreak(),
           ppvariable(self.var),
           (let %l := pretty.index in
              (set_level(),
               printexp(self.set_arg, false),
               pretty.index := %l - 2)))

self_eval(self:Collect) : any
 -> (let x := eval(self.set_arg),
         res:list := list() in
       (case x
         (class for y in x.descendents
                 for z in y.instances
                   (write_value(self.var, z), res :add eval(self.arg)),
          any for y in x
               (write_value(self.var, y), res :add eval(self.arg))),
        if known?(of,self)
          (when x := some(x in res | not(x % self.of)) in   // v3.1.06
               range_error(cause = self,arg = x,wrong = self.of),
           Kernel/cast!(res,self.of)),
        res))

// this is a set image version, that produces a set
//
Image <: Iteration(of:type)

self_print(self:Image) : void
 -> printf("{ ~I | ~I~I `BLUEin `BLACK~I}",
           (pretty.index :+ 2, printexp(self.arg, false)), lbreak(),
           ppvariable(self.var),
           (let %l := pretty.index in
              (set_level(),
               printexp(self.set_arg, false),
               pretty.index := %l - 2)))

self_eval(self:Image) : any
 -> (let x := eval(self.set_arg),
         res:set := set() in
       (for y in x (write_value(self.var, y), res :add eval(self.arg)),
        if known?(of,self)
          (when x := some(x in res | not(x % self.of)) in   // v3.1.06
               range_error(cause = self,arg = x,wrong = self.of),
           Kernel/cast!(res,self.of)),
       res))

// [select VAR in SET_EXPR, ...] is the same as a "for" but returns the subset of
//  members that produce a true value
//
Select <: Iteration(of:type)
self_print(self:Select) : void
 -> printf("{ ~I `BLUEin `BLACK~I | ~I}", ppvariable(self.var),
           (let %l := pretty.index in
              (set_level(),
               printexp(self.set_arg, false),
               pretty.index := %l)),
           (lbreak(2), print(self.arg), pretty.index :- 2))

self_eval(self:Select) : any
 -> (let x := eval(self.set_arg),
         res:set := (case x (set empty(x), any set())) in
       (case x
         (class for y in x.descendents
                 for z in y.instances
                   (write_value(self.var, z),
                    if (eval(self.arg) != false) res :add z),
          any for y in x
               (write_value(self.var, y), if (eval(self.arg) != false) res :add y)),
        if known?(of,self)
          (when x := some(x in res | not(x % self.of)) in   // v3.1.06
               range_error(cause = self,arg = x,wrong = self.of),
           Kernel/cast!(res,self.of)),
        res))

// [select VAR in SET_EXPR, ...] is the same as a "for" but returns the subset of
//  members that produce a true value
//
Lselect <: Iteration(of:type)

self_print(self:Lselect) : void
 -> printf("list{ ~I `BLUEin `BLACK~I | ~I}", ppvariable(self.var),
           (let %l := pretty.index in
              (set_level(),
               printexp(self.set_arg, false),
               pretty.index := %l)),
           (lbreak(2), print(self.arg), pretty.index :- 2))

self_eval(self:Lselect) : any
 -> (let x := eval(self.set_arg),
         res:list := (case x (list empty(x), any list())) in
       (case x
         (class for y in x.descendents
                 for z in y.instances
                   (write_value(self.var, z),
                    if (eval(self.arg) != false) res :add z),
          any for y in x
               (write_value(self.var, y), if (eval(self.arg) != false) res :add y)),
        if known?(of,self)
          (when x := some(x in res | not(x % self.of)) in   // v3.1.06
               range_error(cause = self,arg = x,wrong = self.of),
           Kernel/cast!(res,self.of)),
        res))

// Exists is an iteration that checks a condition
// other = true => forall,  other = false => exists, other = unknown => some
Exists <: Iteration(other:any = false)

self_print(self:Exists) : void
 -> (if (self.other = true) color_princ("`BLUEforall`BLACK")
     else if (self.other = false) color_princ("`BLUEexists`BLACK")
     else color_princ("`BLUEsome`BLACK"),
     if (self.set_arg = any)
        printf("(~I,~I)", ppvariable(self.var), print(self.arg))
     else printf("(~I `BLUEin `BLACK~I | ~I)", ppvariable(self.var),
                 (let %l := pretty.index in
                    (set_level(),
                     printexp(self.set_arg, false),
                     pretty.index := %l)),
                 (lbreak(2), print(self.arg), pretty.index :- 2)))

self_eval(self:Exists) : any
 -> (let x := eval(self.set_arg),
         b := self.other,
         res:any := b in
       (case x
         (class for y in x.descendents
                 for z in y.instances
                   (write_value(self.var, z),
                    if (eval(self.arg) != false)
                       (if (b != true) break(res := (if b z else true)))
                    else if (b = true) break(res := false)),
          any for y in x
               (write_value(self.var, y),
                if (eval(self.arg) != false)
                   (if (b != true) break(res := (if b y else true)))
                else if (b = true) break(res := false))),
        res))

// *********************************************************************
// *     Part 3: other control structures                              *
// *********************************************************************

// ----------------- case  --------------------------------------
Case <: Control_structure(var:any,args:list)

self_print(self:Case) : void
 -> (printf("`BLUEcase `BLACK~S ~I(", self.var, lbreak(1)),
     let n := 1,
         m := length(self.args) in
       (pretty.index :+ 1,
        while (n <= m)
          let %l := pretty.index in
            (printf("~I ~I~I", printexp(self.args[n], false),
                    (if (mClaire/buffer_length() > (pretty.mClaire/width - 50))
                        lbreak(2)
                     else set_level(),
                     print(self.args[n + 1])),
                    (pretty.index := %l,
                     if ((n + 1) != m) printf(", ~I", lbreak()))),
             n :+ 2),
        printf(")"),
        pretty.index :- 2))

[self_eval(self:Case) : any
 -> let truc := eval(self.var),
         flip:boolean := true,
         previous:any := false,
         n := system.trace!,
         d := system.Kernel/debug! in
     (if (n > 0 & n <= system.Core/step!)
           (put(trace!, system, 0),
            put(Kernel/debug!, system, -1),
            printf("  `BLUEcase ~S\n", truc),
            put(Kernel/debug!, system, d),
            put(trace!, system, n)),
     let res :=
			 (if (for x in self.args
				  (if flip (flip := false, previous := eval(x))
				   else if (truc % previous)
						  (previous := eval(x), break(true))
				   else flip := true))
				previous
			  else false)
		in
		  (if (n > 0 & n <= system.Core/step!)
           (put(trace!, system, 0),
            put(Kernel/debug!, system, -1),
            printf("  `BLUEcase -> ~S\n", res),
            put(Kernel/debug!, system, d),
            put(trace!, system, n)),
           res))]

// ------------------ WHILE  and UNTIL  -----------------------------
// the "other" while is until, where the first test is skipped
While <: Control_structure(test:any,arg:any,other:boolean = false)

self_print(self:While) : void
 -> (printf("`BLUE~A `BLACK~I ~I~S", (if self.other "until" else "while"),
            printexp(self.test, false), lbreak(2), self.arg),
     pretty.index :- 2)

self_eval(self:While) : any
 -> (let n := system.trace!,
 		d := system.Kernel/debug!,
     	a := self.other,
         b := a,
         res :=
		   (try while (b | not(eval(self.test)) = a)
			 (b := false, eval(self.arg))
		   catch return_error system.exception!.arg)
      in (if (n > 0 & n <= system.Core/step!)
           (put(trace!, system, 0),
           put(Kernel/debug!, system, -1),
           if self.other
            	printf("  `BLUEuntil -> ~S\n", res)
            else
            	printf("  `BLUEwhile -> ~S\n", res),
            put(Kernel/debug!, system, d),
            put(trace!, system, n)),
      	res))

//-------------- handling errors -----------------------------------
// This is the control structure associated with these errors. Its real
// semantics is defined in the C compiler file
//
Handle <: Control_structure(test:any,arg:any,other:any)

self_print(self:Handle) : void
 -> (printf("`BLUEtry `BLACK~S ~I`BLUEcatch `BLACK~S ~S", self.arg, lbreak(0), self.test,
            self.other),
     pretty.index :- 2)

self_eval(self:Handle) : any
 -> (let x := eval(self.test) in
       try eval(self.arg)
       catch x (if (exception!() % return_error) close(exception!())
                else eval(self.other)))     // <yc> 6/98



claire/traceTtry? :: property(open = 3, range = boolean)
claire/traceTtry?() : boolean -> false

claire/beforeTtry :: property(open = 3, range = any)
[claire/beforeTtry(ttest:any) : any -> 0]

claire/afterTtry :: property(open = 3, range = any)
[claire/afterTtry(br:any,tr:any) : any -> tr]

claire/otherTtry :: property(open = 3, range = any)
[claire/otherTtry(br:any,tc:any) : any -> tc]

iClaire/Thandle <: Handle()

[self_eval(self:Thandle) : any
-> (if traceTtry?() 
        let x := eval(self.test), 
             br := beforeTtry(x) 
        in (try afterTtry(br, eval(self.arg))
            catch x otherTtry(br, eval(self.other))   )
    else self_eval@Handle(self))]

// *********************************************************************
// *     Part 4: the constructs                                         *
// *********************************************************************

Construct <: Complex_instruction(args:list)

List <: Construct(of:type)
Tuple <: Construct()
Set <: Construct(of:type)
Array <: Construct(of:type)        // v3.2.16   constructor for arrays
Printf <: Construct()
Error <: Construct()
Branch <: Construct()

self_print(self:Construct) : void
 -> (let %l := pretty.index in
       (printf("~I~I(~I~I)",       // v3.2.56-58 add a <type> when needed
               (case self
                 (List princ("list"),
                  Set princ("set"),
                  Tuple princ("tuple"),
                  Printf color_princ("`BLUEprintf`BLACK"),
                  Error princ("error"),
                  Trace color_princ("`BLUEtrace`BLACK"),
                  Assert color_princ("`BLUEassert`BLACK"),
                  Branch color_princ("`BLUEbranch`BLACK"),
                  any princ(string!(self.isa.name)))),
               (case self ((List U Set)
                            when %t := get(of,self) in (if (%t != {}) printf("<~S>", %t) ))),
               set_level(), printbox(self.args)),
        pretty.index := %l))

// constructors: how to create a list, a set, a tuple or an array
// note that the constructor is typed
self_eval(self:List) : any
 -> let l := list{ eval(x) | x in self.args} in
      (if known?(of,self)
          (when x := some(x in l | not(x % self.of)) in   // v3.0.72
               range_error(cause = self,arg = x,wrong = self.of),
           Kernel/cast!(l,self.of))  // v0.01
       else Kernel/cast!(l,{}))      // v3.2

self_eval(self:Set) : any
 -> let s := set!(list{ eval(x) | x in self.args}) in
      (if known?(of,self)
          (when x := some(x in s | not(x % self.of)) in   // v3.0.72
               range_error(cause = self,arg = x,wrong = self.of),
           Kernel/cast!(s,self.of))   // v0.01
       else Kernel/cast!(s,{}))
       
self_eval(self:Tuple) : any
 -> tuple!(list{ eval(x) | x in self.args})

// v3.2.16 - introduce a nicer way to create an array
self_eval(self:Array) : any
 -> let l := list{ eval(x) | x in self.args} in
      (if known?(of,self)
          (when x := some(x in l | not(x % self.of)) in   // v3.0.72
               range_error(cause = self,arg = x,wrong = self.of),
           Kernel/cast!(l,self.of))   // v0.01
       else Kernel/cast!(l,any),
       array!(l))
       

// Macros are a nice but undocumented feature of CLAIRE. This is deliberate
//
Macro <: Construct()
macroexpand :: property(open = 3)
self_eval(self:Macro) : any -> eval(call(macroexpand,self))

// error produces an exception of type general_error
self_eval(self:Error) : void
 -> (if (system.Kernel/debug! != -1)
		let d! := system.Kernel/debug!,
			st := (1 + Core/index!())
		in (Core/push!(self),
			for x in self.args Core/push!(x),
			system.Kernel/debug! := Core/index!(),
			Core/push!(d!),
			Core/push!(error),
			Core/push!(length(self.args)),
			Core/push!(st)),
	if (not(self.args) | not(self.args[1] % string))
        error("Syntax error: ~S", self),
     let x:general_error := mClaire/new!(general_error) in      // v3.2.26
        (x.mClaire/cause := car(self.args),
         x.arg := list{ eval(x) | x in cdr(self.args)},
         close@exception(x)))


// this is the basic tool for printing in CLAIRE. A complex statement
// is macroexpanded into basic printing instructions
//
[self_eval(self:Printf) : any
 -> let larg := self.args,
 		onport? := eval(larg[1]) % port,
 		s := (if onport? larg[2] else larg[1])
    in (if not(s % string)
           error("[102] the first argument in ~S must be a string or a port", self)
        else 
        	let n := find(s, "~"),
		         idx := 1,
		         p := use_as_output((if onport? eval(larg[1]) else cout())),
        		 nl := (if onport? 3 else 2),
        		 len := length(s),
		         col:integer := externC("current_color",integer),
		         bold:integer := externC("current_bold",integer),
		         ccol:integer := col,
		         cbold:integer := bold
		     in (while (0 < n & n < len)
		          let m := s[n + 1] in
		            (if (n > 1) (set_color(ccol,cbold),
		            			color_princ(s, idx, n - 1),
		            			externC("{ccol = current_color; cbold = current_bold;}")),
		             if ('A' = m) (set_color(col,bold),princ(eval(larg[nl])), set_color(ccol,cbold))
		             else if ('S' = m) (set_color(col,bold),print(eval(larg[nl])), set_color(ccol,cbold))
		             else if ('I' = m) (set_color(col,bold),eval(larg[nl]),set_color(ccol,cbold)),
		             if (m != '%') nl :+ 1,
		             idx := n + 2,
		             n := find(s, "~", idx)),
		        if (idx <= len)
		        	(set_color(ccol,cbold),
		        	color_princ(s,idx,len)),
		        set_color(col,bold),
		        use_as_output(p)),
            unknown)]

// trace is refined in inspect.cl
// If trace_output() is known, use it, else use current output.
//<sb> v3.3.33 forked process also print their pid 
Trace <: Construct()

//<sb> modified trace strategy (see mtformat)
self_eval(self:Trace) : any
 -> let a := self.args,
         l := list{eval(x) | x in a},
         i := l[1],
         a2 := (if (length(a) > 1) a[2])
     in (if (a2 % string & (case i (integer true)))
           mtformat(module!(), a2, i, l << 2),
        {})

// assert is refined in trace.la
//
Assert <: Construct(Core/index:integer,external:string)

self_eval(self:Assert) : any
 -> (let a := self.args in
       (if (length(a) > 0 & known?(get(ctrace,system)) & not(eval(a[1])))
           let p := use_as_output(system.ctrace) in
             (printf("~S,line=~A: (ASSERT) ~S\n", self.external,
                     self.index, a[1]),
              use_as_output(p),
              if (system.Core/debug! >= 0) error("Assertion Violation"),
              {})))

self_eval(self:Branch) : any
 -> (if (length(self.args) != 1)
         error("[104] Syntax error with ~S (one arg. expected)",self),
     try (choice(), if (eval(self.args[1]) != false) true else (backtrack(), false))
     catch contradiction (backtrack(), false))

// end of file
