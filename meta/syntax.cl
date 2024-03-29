//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| syntax.cl                                                   |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+


Call!(p:property,l:list) : Call -> Call(p,l)

// who is an operation?
//
operation?(y:any) : boolean
 -> (y = as | y = := | y % operation | y = OR | y = % | y = add) 

// produce an expression from an operation
//
combine(x:any, y:any, z:any) : any
 -> (let p := operation!(x) in
      (if (p & precedence!(y) < precedence!(p))
          combine!(operand!(x, 1), p, combine(operand!(x, 2), y, z))
       else combine!(x, y, z)) )

combine!(x:any, y:any, z:any) : any
 -> (if (y = as) Cast(arg = x, set_arg = extract_type(z))
    else if (y = :=)
       case x
        (global_variable Gassign(var = x, arg = z),
         Call (if (case z (Call (((selector(z) = add) | (selector(z) = delete)) &
                                 (args(z)[1] = x) &
                                 (if (length(args(x)) = 1) multi?(selector(x))
                                  else if (x.selector = nth & length(x.args) = 2)
                                       multi?(x.args[1])))))
                   Call!(selector(z),
                         list(
                           (if (length(args(x)) = 1) selector(x) else args(x)[1]),
                           (if (length(args(x)) = 1) args(x)[1] else args(x)[2]),
                           args(z)[2]))
               else if (selector(x) = nth)
                  Call!(nth=, add(copy(args(x)), z))
               else if (length(args(x)) = 1)
                 let p := make_a_property(selector(x)), y := args(x)[1] in
                   (if (p = read & (case y (Call+ (y.selector.reified = true)))) Call!(write,list(y,z))
                    else Call!(write, list(p,y,z)))
               else Serror(164, "~S cannot be assigned with :=", list(x))),
         Do let l := args(x), m := length(l),
                v := Variable(mClaire/pname = gensym()),
                %bind := bind!(reader, v),
                res := (Let*(var = v, value = z,
                   			arg = Do(list<any>{ 
                               Assign(var = l[i], arg = Call!(nth,list(v,i))) |
                               i in (1 .. m)})))
            in (unbind!(reader, %bind),
            	res),
         any Assign(var = x, arg = z))
    else if (y = OR)
       case x (Or (add!(args, x, z), x), any Or(args = list(x, z)))
    else if (y = AND)
       case x (And (add!(args, x, z), x), any And(args = list(x, z)))
    else if (y = %) Call!(%,list(x, z))
    else Call*(selector = y, args = list(x, z)))

// allows to treats Calls, Assigns, Gassign in an homogeneous way
//
operation!(x:any) : any
 -> (case x
     (Or OR,
      And AND,
      Assign :=,
      Gassign :=,
      Call let p := selector(x) in
             (if (x % Call* & operation?(p)) p
              else if (p = nth=) :=
              else if (p = write) :=),
      any false))

operand!(x:any, n:integer) : any
 -> (case x
     (Or (if (n = 1) Or(args = rmlast@list(copy(args(x))))
                        else last@list(args(x))),
      And (if (n = 1) And(args = rmlast@list(copy(args(x))))
                          else last@list(args(x))),
      Assign (if (n = 1) var(x) else arg(x)),
      Gassign (if (n = 1) var(x) else arg(x)),
      Call (if (selector(x) = write)
               (if (n = 2) args(x)[3]
                else Call!(args(x)[1],list(args(x)[2])))
            else if (selector(x) = nth=)
               (if (n = 2) last(args(x))
                else Call!(nth,rmlast(copy(args(x)))))
            else args(x)[n]),
      any false))

// precedence
//
precedence!(y:any) : integer
 -> (if (y = as) 0
    else if (y = :=) 100
    else if (y = AND) 1000
    else if (y = OR) 1010
    else precedence(y as operation))

// *********************************************************************
// *      Part 3: Syntactical Analysis                                 *
// *********************************************************************

nextstruct(r:meta_reader, %first:keyword, e:keyword) : any
 -> (if (%first = let) readlet(r, e)
    else if (%first = when) readwhen(r, e)
    else if (%first = case) readcase(r, e)
    else if (%first = for)
       let %var := extract_variable(nexts!(r, in)),
           %set := nexte(r),
           %bind := bind!(r, %var),
           x := (if (firstc(r) = #/,) next(r), ; to remove later
                 For(var = %var, set_arg = %set, arg = nexts(r, e))) in
         (unbind!(r, %bind), x)
    else if (%first = tfor)
       let %var := extract_variable(nexts!(r, in)),
           %set := nexte(r),
           %bind := bind!(r, %var),
           x := (if (firstc(r) = #/,) next(r), ; to remove later
                 Tfor(var = %var, set_arg = %set, arg = nexts(r, e))) in
         (unbind!(r, %bind), x)
    else if (%first = ffor) //<sb> v3.3.33: ffor
    	let %var := extract_variable(nexts!(r, in)),
           %set := nexts(r, by),
           %by := (if (firstc(r) = #/,) next(r), ; to remove later
           			nexte(r)),
           %bind := bind!(r, %var),
           x := (//if unknown?(range, %var) put(range,%var,any),
           		Ffor(var = %var, set_arg = %set, forkedby = %by, arg = nexts(r, e))) in
         (unbind!(r, %bind), x)
    else if (%first = while) While(test = nexte(r), arg = nexts(r, e), other = false)
    else if (%first = until) While(test = nexte(r), arg = nexts(r, e), other = true)
    else if (%first = try)
       let %a := nexts!(r, catch), %t := nexte(r) in
         Handle(test = %t, arg = %a, other = nexts(r, e))
    else if (%first = ttry)
       let %a := nexts!(r, catch), %t := nexte(r) in
         Thandle(test = %t, arg = %a, other = nexts(r, e))
    else %first)

// reads a let expression
//
readlet(r:meta_reader, e:keyword) : any
 -> (let %def := nexts!(r, in, #/,) in
      case %def
        (Assign let v := extract_variable(var(%def)),
                    %bind := bind!(r, v),
                    x := Let(var = v, value = get(arg, %def),
                            arg = (if (firstc(r) = #/,) readlet(cnext(r), e)
                                   else nexts(r, e))) in
                   (unbind!(r, %bind), x),
; I can't remember what this is ...
;         Defobj let v := var(%def),
;                    %bind := bind!(r, v),
;                    x := Let(var = v, value = get(arg, %def),
;                            arg = (if (firstc(r) = #/,) readlet(cnext(r), e)
;                                   else nexts(r, e))) in
;                   (unbind!(r, %bind), x),
         Let*  (let v := var(%def), //<sb> fix, add bind! / unbind! v3.3.19
                    %bind := bind!(r, v)
                in (arg(%def) := readlet*(r,args(arg(%def) as Do),1,e),
                   unbind!(r, %bind),
                   %def)),
         Call[selector = write]
           let v1 := Variable(gensym(), any),
               v2 := Variable(gensym(), any),
               %a := args(%def),
               %b1 := bind!(r, v1),
               %b2 := bind!(r, v2),
               %e := nexts(r, e),
               x := Let+(var = v1, value = Call+(selector = %a[1], args = list(%a[2])),   //<sb> add variable binding
                   arg = Do(list<any>(%def,
                                 Let(var = v2, value = %e,
                                     arg = Do(list<any>(Call!(write,list(%a[1],%a[2],v1)), v2))))))
           in (unbind!(r, %b2),
           		unbind!(r, %b1),
           		x),
         any Serror(165, "~S is illegal after a let", list(%def))))
         


// recursive construction of the tail of a Let*
//
readlet*(r:meta_reader, l:list, n:integer, e:keyword) : any
 -> (if (n > length(l)) 
 		(if (firstc(r) = #/,)
 			readlet(cnext(r), e) //<sb> support combinaison of Let* and Let
		else nexts(r, e))
    else let v := extract_variable(var(l[n])),
             %bind := bind!(r, v),
             x := Let(var = v, value = arg(l[n]), arg = readlet*(r,l,n + 1, e)) in
           (unbind!(r, %bind), x))


// reads a when expression
//
readwhen(r:meta_reader, e:keyword) : any
 -> (let %def := nexts!(r, in, #/,) in
      case %def
        (Assign let v := extract_variable(var(%def)),
                    %bind := bind!(r, v),
					%a := nexts(r,else),
					x := When(var = v, value = get(arg, %def), arg = %a,
                              other = (if wcl_start?(r, firstc(r))
           	 							(unget(r.fromp, '>'),
           	 							unknown)
    							         else if stop?(firstc(r)) unknown
                                	       else nexts(r, e))) in
                   (unbind!(r, %bind), x),
        any Serror(165, "~S is illegal after a when", list(%def))))
         

// read an if
//
readif(r:meta_reader, e:integer) : any
 -> (let %a1 := nexte(r),
        %a2 := nexts(r, else) in
      If(test = %a1, arg = %a2,
         other =
           ((if wcl_start?(r, firstc(r))
           	 	(unget(r.fromp, '>'),
           	 	false)
             else if (firstc(r) = #/, | firstc(r) = e) false
             else let x := nexte(r) in
                    (if (x = if) readif(r, e)
                     else if keyword?(x) nextstruct(r, x, none)
                     else loopexp(r, x, none, false))))))

// reads a member_of
//
readcase(r:meta_reader, e:keyword) : any
 -> (let %v := nexte(r) in
      (if (skipc!(r) != #/() Serror(166, "Missing ( after case ~S", list(%v)),
       let %x:Case := (Case(var = %v, args = list())), // v0.01
           %t:any := any in
         (while (firstc(r) != #/))
            (next(r),
             %t := extract_type(nexte(r)),
             put(args, %x, add(add(args(%x), %t), nexts(r, none))),
             if (not(stop?(firstc(r))) & not(stop?(skipc(r))))          ; because of toplevel ....
                Serror(167, "Missing ) or , after ~S",list(%x))),
          next(r),
          if (e != none & not(stop?(skipc(r))) & nexte(r) != e)
             Serror(161, "Missing ~S after ~S", list(e, %x)),
          %x)))

// if the expression begins with "{"
//
readset(r:meta_reader, %a1:any) : any
 -> (if (%a1 = curly(r)) (next(r), {})
    else (if keyword?(%a1) %a1 := nextstruct(r, %a1, none),
          let %a2 := nexte(r) in
            (if (%a2 = comma(r))
	       Kernel/cast!({dereference(u) | u in (%a1 cons nextseq(cnext(r), #/}))},{})
             else if (%a2 = curly(r))
               (next(r), Kernel/cast!(set(dereference(%a1)),{}))
             else if (%a2 = in)
                let v := extract_variable(%a1) in
                  Select(var = v, set_arg = nexte(r),
                         arg =
                           (let %bind := bind!(r, v),
                                x := ((if (nexte(r) != OR)
                                          Serror(168, "Missing | in selection",nil)
                                       else nexts!(r, #/}))) in
                              (unbind!(r, %bind), x)))
             else if (%a2 = OR)
                let v := extract_variable(nexts!(r, in)),
 					%bind := bind!(r, v),
					//res := lexical_build(Image(var = v, set_arg = nexts!(r, #/}),
                    //                  arg = substitution(%a1,v,v)), list(v), 0)
					res := Image(var = v, set_arg = nexts!(r, #/}),
                                      arg = substitution(%a1,v,v))
				in (unbind!(r, %bind),
					res)
             else if operation?(%a2)
                readset(r,
                        loopexp(r, combine(%a1, %a2, nexte(r)), none,
                                false))
             else Serror(169, "Missing separation between ~S and ~S",
                         list(%a1, %a2)))))


dereference(x:any) : any
  -> (case x (unbound_symbol Serror(170, "Cannot use ~S in a set constant",list(x)),
             Variable Serror(170, "Cannot use a variable (~S) in a set constant",list(x)),
             any eval(x)))
			
			
// reads a sequence of exp. Must end with a e = ) | ] | }
//
nextseq(r:meta_reader, e:integer) : any
 -> (if (firstc(r) = e) (next(r), list())  // <yc:v0.01>
    else let x := nexts(r, none) in
           (if (firstc(r) = integer!('\n') & r.toplevel) skipc(r),         // v3.2.22
            if (firstc(r) = e) (next(r), list(x))
            else if (firstc(r) = #/,) x cons nextseq(cnext(r), e)
            else Serror(171, "Read the character ~S inside a sequence",
                        list(char!(firstc(r))))))

// read the next block: a sequence of exp. Must end with a e = ) | ] | }
//
readblock(r:meta_reader, x:any, e:integer) : any
 -> (skipc(r),
	if (x = paren(r)) list()
    else if wcl_start?(r, firstc(r))  //<sb> wcl
        Do!(x, readblock(r, read_wcl(r), e))
    else if (firstc(r) = e) (cnext(r), x)
    else if (firstc(r) = #/,)
    	Do!(x, readblock(r, nexte(cnext(r)), e))
    else if stop?(firstc(r))
       Serror(172, "The sequence ...~S must end with ~A", list(x, char!(e)))
	else if (x = if) readblock(r, readif(r, e), e)
    else if (x = Zif) let %i := (readif(r,e) as If) in
                         readblock(r,(if eval(test(%i)) arg(%i) else other(%i)),e)
    else if (x = else) Serror(173, "Expression starting with else", nil)
    else if keyword?(x) readblock(r, nextstruct(r, x, none), e)
    else let y := loopexp(r, x, none, false) in
          (case y (Call* put(isa,y,Call)),
           readblock(r, y, e)))

Do!(x:any, y:any) : any
 -> (if (x % Do & y % Do)
 		(put(args, x, x.args /+ y.args),
 		x)
 	else case y
	     (Do (put(args, y, nth+(args(y), 1, x)), y),
    	  any
    	  	(case x
    	  		(Do (x.args add y, x),
    	  		any Do(list<any>(x, y))))))

// extract the type from a list<X> expression
extract_of_type(x:Call) : type
  -> let l := x.args in
       (if (length(l) > 2)
           let y := l[3] in
             (case y (List let z := y.args[1] in
                             (case z (Set extract_type(z.args[1] as type),
                                      any any)),
                      any any))
        else any)


// if the expression is a call -------------------------------------------
//
readcall(r:meta_reader, x:any, t:any) : any
 -> (let l := nextseq(cnext(r), #/)) in
      (if (x = printf) Printf(args = l)
       else if (x = error) Error(args = l)
       else if (x = assert)
           Assert(args = l, index = r.Reader/nb_line , external = external(r)) //<sb>
       else if (x = trace) Trace(args = l)
       else if (x = branch) Branch(args = l)
       else if (x = quote) Quote(arg = (if l l[1]))
       else if (x = tuple) Tuple(args = l)
       else if (x = list) List(args = l)
       else if (case x (Call (x.args[1] = list)))     // ------ the 3 parameterized constructor
           List(of = extract_of_type(x as Call), args = l)
       else if (case x (Call (x.args[1] = array)))              // new in v3.2.16
           Array(of = extract_of_type(x as Call), args = l)
       else if (case x (Call (x.args[1] = set)))
           Set(of = extract_of_type(x as Call), args = l)
       else if (x % class & x inherit? Macro)
			let o := mClaire/new!(x)
			in (put(args,o,l), Language/init_location(o), o)
       else if (x = set) Set(args = l)
       else if (x = return | x = break) Return(arg = (if l l[1] else true))
       else if (x % class)
          (if not(forall( y in l |
                          case y (Call (if (selector(y) = =)
                                       (args(y)[1] := make_a_property(args(y)[1]), true)))))
            let l2 := params(x as class),
                n :=  (case l2 (list length(l2), any 0)) in
             (if (length(l) = n)
                l := list{Call(selector = =, args = list(l2[i],l[i])) |
                          i in (1 .. n)}
              else Serror(174, "Wrong instantiation list ~S(~S...",list(x,list(l)))),
           Definition(arg = x, args = l))
       else if (x % Variable | (case x (global_variable x.range)))
           Call!(call,cons(x,(if l l else list(system))))
       else let p := make_a_property(x),
                l2 := ((if l l else list(system))) in
              (if known?(t) Super(selector = p, cast_to = t, args = l2)
               else Call!(p,l2))))

// reads a definition (CLAIRE2 syntax)   - x and y are two expressions that have been read
//
nextdefinition(r:meta_reader,x:any,y:any,old?:boolean) : any
 -> (r.last_arrow := false,
     if (y = triangle) nextDefclass(cnext(r),x,old?)
     else if (y = :)
     let table? := (case x (Call (selector(x) = nth &
                                  args(x)[1] % (unbound_symbol U table)))),
         z := nexte(r), w := nexte(r) in
          (if (if table? (w = :=) else (w = arrow | w = =>)) nil         //v3.3
           else Serror(149, "Wrong keyword (~S) after ~S",list(w,z)),
           nextmethod(r,x,z,table?,old?,( w = =>)))
    else if (y = ::)
     case x (Call let ru := nexte(r), z := nexts(r, =>) in
                   Defrule(ident = name(selector(x)), args = args(x),
                           arg = z,
                           body = (if (firstc(r) = #/)) (next(r),nil)
                                   else readblock(r, nexte(r), #/))) ),
             any nextinst(r,x))
    else if (y = arrow | y = =>)
     (r.last_arrow := (y = =>),
      //[3] ---- note: ~S - method's range is assumed to be void // x,
      nextmethod(r,x,void,false,old?,(y = =>)))       // v3.3 must be void
    else if (y = := & x % Vardef)
          Defobj(ident = mClaire/pname(x), arg = global_variable,
                 args = list(Call!(=, list(range, extract_type(range(x)))),     // v3.1.14
                             Call!(=, list(value, nexte(r)))))
     else Do(args = list<any>(x,y)))
    
    
nextmethod(r:meta_reader,x:any,y:any,table?:boolean,old?:boolean,inl?:boolean)  : any
  -> (let n := skipc(r),
          z := ( if old? readblock(r, nexte(r), #/])
                 else if (n = #/() (if toplevel(r) nexts(r, none)
                               else readblock(r, nexte(cnext(r)), #/)))
                 else nexte(r)),
          rs := Defmethod(arg = x, set_arg =  y, 
                          body = (if (z = let) readlet(r, None) else z), 
                          inline? = inl?) in
       (if table? put(isa,rs,Defarray), rs))

// reads an instantiation
//
nextinst(r:meta_reader, x:any) : any
 -> (case x
     (Variable (Defobj(ident = mClaire/pname(x), arg = global_variable,
                      args = list(Call(=, list(range, extract_type(range(x)))),  // v3.1.14
                                  Call(=, list(value, nexte(r)))))),
      Call let ru := nexte(r), z := nexts(r, =>) in
                   Defrule(ident = name(selector(x)), args = args(x),
                           arg = z,
                           body = (if (firstc(r) = #/)) (next(r),nil)
                                   else readblock(r, nexte(r), #/))) ),
      any let y := nexte(r) in
            (if (case x (global_variable unknown?(y))) y
			 else if (case y (Definition (arg(y) inherit? thing)))
                 Defobj(ident = extract_symbol(x), arg = arg(y),
                                args = args(y))
             else Defobj(ident = extract_symbol(x), arg = global_variable,
                         args =  list(Call(=,list(range, {})),
                                      Call(=,list(value, y)))))))


// reads a class Definition of the form C(p:t | p:t = v *)
// new in v2.5
nextDefclass(r:meta_reader,x:any,old?:boolean) : Defclass
 -> (skipc(r),
    let c := verify(class, Kernel/read_ident(r), Defclass),     // superclass
        y:Defclass :=                                    // create the Defclass
          (if (firstc(r) != #/() Defclass(arg = c, args = nil, forward? = true)
           else let l := nextseq(cnext(r), #/)) in
              (for y1 in l,
                 (if not(case y1
                          (Call (selector(y1) = = & args(y1)[1] % Vardef),
                           Vardef true,
                           any false))
                     Serror(175, "Wrong form ~S in ~S(~S)", list(y1, c, l))),
               Defclass(arg = c, args = l, forward? = false))),
        lp := nil,
        idt := (if (case x (Call selector(x) = nth))    // extract ident + list
                 let l := (x as Call).args in           // of parameters
                     (if (l[1] % class) lp := (l[2] as list)
                      else lp := list{make_a_property(y2) | y2 in cdr(l)},
                      extract_symbol(l[1]))
                 else extract_symbol(x)) in
        (if (old? & (skipc(r) != #/])) Serror(176, "Missing ] after ~S ", list(y))
         else if old? next(r),
         y.ident := idt,
         y.params := lp,
         y))


// end of file
