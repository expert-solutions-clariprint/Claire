// Sylvain Benilan
// cross compilation of claire
//	This file is used to add entities at step 1
// the complier implies we know the meta definition of new entities 

// updated Oct 2011

Core/RELEASE :: version()

reset_sym(self:string, m:module) : void ->	
	let s := get_symbol(m,self)
	in (put(value, s, unknown),
		put(module!, s, claire),
		put(mClaire/definition, s, m))

(begin(Kernel))

(end(Kernel))


(begin(Core))

(end(Core))


(begin(Language))

iClaire/Tfor <: For()

claire/traceTfor?() : boolean -> false

// [claire/beforeTfor(fv:string,fsa:string) : any -> 0]
[claire/beforeTfor(fv:string,fsa:any) : any -> 0]

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
                                                            self.set_arg
                                                            //(print_in_string(),printf("~S",self.set_arg),end_of_string())
                                                            ))),
                                    apply(self_eval1,list(getFor(self))))))
        else apply(self_eval1,list<any>(getFor(self))))]


claire/traceTtry? :: property(open = 3, range = boolean)
claire/traceTtry?() : boolean -> false

claire/beforeTtry :: property(open = 3, range = any)
[claire/beforeTtry(ttest:any) : any -> 0]

//
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

(end(Language))


// (begin(Reader))
// (load("meta/scanf"))
// (end(Reader))
(Reader.made_of :delete "scanf")
// (Reader.made_of :add "codedoc")

(begin(Reader))

claire/tfor :: reserved_keyword() //<lr> 
claire/ttry :: reserved_keyword() //<lr>

(end(Reader))


(begin(Generate))


(end(Generate))


(begin(Optimize))

[c_type(self:Tfor) : type -> infers_from(return_type(self.arg),self)]

// notice that tfor is of sort any and may require a cast ..
[c_code(self:Tfor,s:class) : any
 -> let fv := self.var,
        fnv := Variable(pname = fv.pname, range = fv.range,
                      mClaire/index = fv.mClaire/index),
        narg := substitution(self.arg,fv,fnv),
        fsa := self.set_arg,
        doprintv := Do(list(Call(print_in_string,list(system)),
                             Printf(args = list("~S",fnv.pname)),
                            Call(end_of_string,list(system)))),
        i := If(test = Call(claire/traceTfor?,list(system)),
                arg = Call(claire/afterTfor,
                          list( Call(claire/beforeTfor,list(doprintv,fsa)),
                                For(var = fnv, set_arg = fsa, arg = narg)
                                )),
                other = For(var = fnv, set_arg = fsa, arg = narg))
    in c_code(i,s) ]

[c_code(self:Thandle,s:class) : any
 -> let vbr := Variable!(gensym(), 0, any),
        i := If(test = Call(claire/traceTtry?,list(system)),
                arg = Let(  var = vbr,
                            value = Call(claire/beforeTtry,list(self.test)),
                            arg = Handle( test = self.test,
                                          arg = Call(   claire/afterTtry, 
                                                        list( vbr, Call(eval,list(self.arg)) ) ),
                                          other = Call( claire/otherTtry,
                                                        list( vbr, Call(eval, list(self.other)) )   )
                                        )
                          ),
                other = Handle(test = any, arg = self.arg, other = self.other) )
    in c_code(i,s)   ]
    
(end(Optimize))


(begin(Serialize))
(end(Serialize))