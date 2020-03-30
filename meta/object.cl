//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| object.cl                                                   |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in about()                               |
//+-------------------------------------------------------------+

// This file contains the definition of the objects that implement the
// core features of the microCLAIRE library: traceable & debug-able calls,
// tables, demons and exceptions

// *********************************************************************
// *  Table of contents                                                *
// *   Part 1: Ask, debug & trace                                      *
// *   Part 2: Tables                                                  *
// *   Part 3: Demons & relations for the logic modules                *
// *   Part 4: Basics of Exceptions                                    *
// *********************************************************************



// @doc Miscellaneous
// returns a release number of your CLAIRE system (<release>.<version>.<revision>).
[release() : string -> ("3." /+ string!(system.version)) ]


// *********************************************************************
// *   Part 1: Ask, debug & trace                                      *
// *********************************************************************

// create the list of arguments if needed : allocate on the stack
[get_args(i:integer) : list
 -> let liste := list<any>() in
       (while (i < index!()) (liste :add get_stack(i), i := i + 1), liste) ]

// evaluation of a message without the message structure, with a list
// of arguments. This method must be garbage-protected, because it is
// used as an entry point.
// to remove !!!!
;ask(self:any,p:property,arg:list) : any
; -> (let start := index!() in
;       (push!(self),
;        for x in arg push!(x),
;        eval_message(p, find_which(p, start, owner(self)), start, true)))

// a simple method for a direct call with no argument
funcall(self:method,x:any) : any
 -> (let start := index!() in
       (push!(x), execute(self, start, false)))

// this is a simple method for calling directly a method with one argument
funcall(self:method,x:any,y:any) : any
 -> (let start := index!() in
       (push!(x), push!(y), execute(self, start, false)))

// this is a simple method for calling directly a method with two arguments
funcall(self:method,x:any,y:any,z:any) : any
 -> (let start := index!() in
       (push!(x),
        push!(y),
        push!(z),
        execute(self, start, false)))

// how to apply a function to a list
// @doc calls
// apply(self,ls,l) applies the function self to the argument list l, where
// ls is the list of sort of the arguments and the result (i.e. length(ls) = length(l) + 1).
// For instance, if self is the external function that defines + @ integer :
// \code
// apply(f, list(integer,integer,integer), list(1,2)) -> 1 + 2
// \/code
apply(self:function,ls:list,l:list) : any
 -> (let start := index!() in
       (for x in l push!(x),
        stack_apply(self, ls, start, index!())))

// @doc calls
// call(p, x1, x2, ..., xn) is equivalent to apply(p, list(x1 ,x2 , ... , xn)).
call(p:property, l:listargs) : any -> apply(p, l)


// @doc calls
// apply(p,l) is equivalent to a function call where the selector is p and the argument
// list is l. For instance the following expressions are equivalent :
// \code
// apply(+, list(1,2)) -> 3
// 1 + 2 -> 3
// call(+, 1, 2) -> 3
// \/code
apply(p:property,l:list) : any
 -> let start := index!() in
            (for x in l push!(x),
             eval_message(p, find_which(p, start, owner(l[1])), start,
                          false))

// @doc calls
// apply(m,lx) applies the method m to the argument list lx.
// For instance the following expressions are equivalent :
// \code
// apply(+ @ integer, list(1, 3)) -> 4
// 1 + 3 -> 4
// \/code
apply(m:method,l:list) : any
 -> (let start := index!() in
       (for x in l push!(x), execute(m, start, false)))



// *********************************************************************
// *   Part 2: Tables                                                  *
// *********************************************************************

// finds if objects are identified
identified?(self:class) : boolean
 -> (self = integer | self inherit? object | self = symbol | self = boolean |
     self = char)

identical?(x:any,y:any) : boolean
  ->  externC("((x == y) ? CTRUE : CFALSE)",boolean)

//  let x1: (if ((x as boolean) = (y as boolean)) true else false)

// writing a single value into a slot but does NOT trigger the rules !
// equivalent to is! of LAURE
// this definition should not be placed in the method.cl file
// (it requires some inheritance conflict processing)
put(self:property,x:object,y:any) : any
 -> (let s := (self @ owner(x)) in
       case s
        (slot store(x, s.index, s.srange, y, self.store?),
         any selector_error(selector = self, args = list(x))))

         
// v3.2 : same but multi valued
[add_value(self:property,x:object,y:any) : void
  -> let s := (self @ owner(x)) in
    (if not(s) selector_error(selector = self, args = list(x))
     else if not(multi?(self)) error("[134] Cannot apply add to ~S", self)
     else let n := (s as slot).index,
              l1 := (slot_get(x, n, object) as bag) in
            add_value(self, x, n, l1, y)) ]

         
// access
nth(a:table,x:any) : type[(if unique?(a) the(a).range else any)]
 -> let p := a.params in
       (if not(x % a.domain)
           error("[135] ~S does not belong to the domain of ~S", x, a),
        let v := (case p
                  (integer a.graph[(x as integer) - p],
                   list a.graph[get_index(a, (x as list)[1], (x as list)[2])],
                   any let i := index(a, x) in a.graph[i])) in
          (if (known?(v) | v % a.range) v
           else error("[138] the value ~S(~S) is unknown !",a,x)))

get(a:table,x:any) : type[(if unique?(a) (the(a).range U {unknown}) else any)]
 -> (let p := a.params in
       (if not(x % a.domain) unknown
        else let i := get_index(a, x) in a.graph[i]))

// interface update method for a[x] := y
nth=(a:table,x:any,y:any) : void
 -> (if not(x % a.domain)
        error("[135] ~S does not belong to the domain of ~S", x, a),
     if not(y % a.range) range_error(cause = a, arg = y, wrong = a.range),
     nth_put(a, x, y))

// internal form without checks
// equivalent of update = put + put_inverse
nth_put(a:table,x:any,y:any) : void
 -> (if  (known?(if_write,a) & not(multi?(a))) fastcall(a,x,y)
     else if multi?(a)
        let r := get(inverse, a),
            old := get(a,x) in
          (a.graph[get_index(a, x)] :=
             (if (known?(old) & length((old as set)) = 0) old  //<sb> was "if (length((y as set)) = 0) y"
             else if (a.multivalued? = list)
                make_list(0,member(a.range),0) //<sb> was returning unknown
             else {}),
           if (known?(r) & known?(old)) for z in old update-(r, z, x),
           for z in (y as set) add!(a, x, z))
     else let  r := get(inverse, a), z := get(a,x) in
             (if (z != y)
                 (if known?(r)
                   let z := get(a,x) in
                      (if (known?(z) & (r != a | x != z)) update-(r, z, x)),
                       put(a, x, y),
                       update+(a, x, y))))

// put does NOT update the inverse
put(a:table,x:any,y:any) : void
 -> let p := a.params, z := get(a,x)  in
       (if (z != y)
           (case p
             (integer store(a.graph, x - p, y, a.store?),
              list store(a.graph,
                         get_index(a, (x as list)[1], (x as list)[2]), y,
                         a.store?),
              any let i := index(a, x) in store(a.graph, i, y, a.store?)),
            true))

// adds a value to a multi-valued table: interface method
add(a:table,x:any,y:any) : void
 -> (if not(x % a.domain)
        error("[135] ~S does not belong to the domain of ~S", x, a),
     if not(y % member(a.range)) range_error(cause = a, arg = y, wrong = a.range),
     add!(a, x, y))

// adds a value to a multi-valued table: internal version without type checks
add!(a:table,x:any,y:any) : void
 -> (if known?(if_write,a) fastcall(a,x,y)
     else let p := a.params,
         i := get_index(a, x),
         l := (a.graph[i] as bag) in
       (if add_value(a, i, l, y) update+(a, x, y)))

// this methods adds a value to a multi-slot (used by the compiler)
add_value(self:table,n:integer,l:bag,y:any) : boolean
 -> (if (self.multivalued? = true)
        (if not(y % l)
            let l1 := (add!@set((if self.store? copy(l) else l), y)) in
              (store(self.graph, n, l1, self.store?), true)
         else false)
     else let l1 := (if self.store? store(l, y) else add!@list(l, y)) in
            (store(self.graph, n, l1, self.store?), true))

// a direct version (v3.2) that can be used in lieu of add!
add_value(self:table,x:any,y:any) : void
 -> (let p := self.params,
         i := get_index(self, x),
         l := (self.graph[i] as bag) in
       add_value(self, i, l, y))
            
// removes a value from an table
delete(a:table,x:any,y:any) : any
 -> (let p := a.params,
         i := get_index(a, x),
         l1 := (a.graph[i] as set),
         l := ((if a.store? copy(l1) else l1) delete y) in
       (store(a.graph, i, l, a.store?),
        let r := a.inverse in (if known?(r) update-(r, y, x)),
        l))

// direct access to 2-dim tables
[nth(a:table,x:any,y:any) : type[(if unique?(a) the(a).range else any)]
 -> let p := a.params,
        v := (case p
                (list (if not((x % (a.domain as tuple)[1] &
                               y % (a.domain as tuple)[2]))
                         error("[135] ~S does not belong to the domain of ~S", x, a),
                       a.graph[get_index(a, x, y)]),
                 any index(a, x, y)))  in
         (if (known?(v) | v % a.range) v else error("~S(~S) is unknown !",a,x))]

// sets a value in a 2-dim table
nth=(a:table,x:any,y:any,z:any) : void
 -> let p := a.params in
      (case p
        (list (if not((x % (a.domain as tuple)[1] &
                       y % (a.domain as tuple)[2]))
                  error("[135] ~S does not belong to the domain of ~S", list(x,y), a),
               if not(z % a.range)
                  range_error(cause = a, arg = z, wrong = a.range),
               if (known?(inverse, a) | known?(if_write, a))
                  nth_put(a, list(x, y), z)
               else store(a.graph, get_index(a, x, y), z, a.store?)),
         any nth=(a, tuple(x, y), z)))          // v3.2.16 tuple(a,b) is not list(a,b) !

get_index(a:table,x:any) : integer
 -> (let p := a.params in
       case p
        (integer (x as integer) - p,
         list get_index(a, (x as list)[1], (x as list)[2]),
         any index(a, x)))

get_index(a:table,x:integer,y:integer) : integer
 -> let p := (a.params as list) in (((p[1] * x) + y) - p[2])


// erase an table means to clean its graph so that it becomes empty.
// @doc tables
// erase(a) removes all value pairs contained in the table. This means that,
// on one hand, the value a[x] becomes unknown for each object x, and also
// that any references to an object from the table's domain or an associated
// value is lost, which may be useful to allow for complete garbage collection. 
erase(a:table)  : void
  -> let p := a.params in
       (case p
         (integer (for i in domain(a) a.graph[get_index(a,i)] := a.default),
          list (for l:list in domain(a) a.graph[get_index(a,l[1],l[2])] := a.default),
          any (for i in (1 .. length(a.graph))
                  (a.graph as list)[i] := unknown)))

/* //<sb> moved to Kernel for protection consideration
// new in v3.2.50 a constructor for building a table dynamically
claire/make_table(%domain:type, %range:type, %default:any) : table
  -> let t := (mClaire/new!(table) as table) in
       (t.range := %range,
        t.domain := %domain,
        t.default := %default,
        t.params := any,
        t.mClaire/graph := make_list(29,unknown),
        t)
*/

//<sb> add a nice self_print @ table
self_print(self:table) : void ->
	printf("<~I[~I]>", (if (self.name.name != "unamed") princ(self.name.name)),
			let first? := true,
				g := self.mClaire/graph
			in for x in (1 .. length(g))
				(if ((x + 2) mod 2 = 1 & known?(g[x]))
					(if first? first? := false else princ(","),
						printf("~S => ~S", g[x], g[x + 1]))))

// Our first table: a debugging tool which stores a list of stopping values
StopProperty[p:property] : list := unknown

// *********************************************************************
//   Part 3: Demons & relations for the logic modules                  *
// *********************************************************************

// applying a lambda to one argument
funcall(self:lambda,x:any) : any
 -> (let start := mClaire/index!(),
         retour := mClaire/base!() in
       (mClaire/set_base(start),
        mClaire/push!(x),
        mClaire/stack_apply(self.dimension),
        let val := eval(self.body) in
          (mClaire/set_base(retour), mClaire/set_index(start), val)))

// applying a lambda to two argument
[funcall(self:lambda,x:any,y:any) : any
 ->  let start := mClaire/index!(),
         retour := mClaire/base!() in
       (mClaire/set_base(start),
        mClaire/push!(x),
        mClaire/push!(y),
        mClaire/stack_apply(self.dimension),
        let val := eval(self.body) in
          (mClaire/set_base(retour),
           mClaire/set_index(start),
           val)) ]

// applying a lambda to two argument
[funcall(self:lambda,x:any,y:any,z:any) : any
 ->  let start := mClaire/index!(),
         retour := mClaire/base!() in
       (mClaire/set_base(start),
        mClaire/push!(x),
        mClaire/push!(y),
        mClaire/push!(z),
        mClaire/stack_apply(self.dimension),
        let val := eval(self.body) in
          (mClaire/set_base(retour),
           mClaire/set_index(start),
           val)) ]


// for historical reasons
mClaire/pname :: property()

// dealing with inverse
check_inverse(%r1:any,%r2:any) : void
 -> (let r1 := (%r1 as relation),
         r2 := (%r2 as relation) in
       (put(inverse,r1,r2),
        put(inverse,r2,r1),
        final(r1),
        final(r2),
        if (not(r1.domain <=  (if multi?(r2) member(r2.range) else r2.range)) |
            not(r2.domain <=  (if multi?(r1) member(r1.range) else r1.range)))
           error("[137] ~S and ~S cannot be inverses for one another", r1, r2)))

(relation.open := 0,
 write(inverse, inverse, inverse),
 write(if_write, inverse, (check_inverse @ any).functional))


// very useful
invert(r:relation,x:any) : bag
 -> (let r2 := get(inverse, r) in
       case r2
        (table let v := r2[x] in (if (r2.multivalued? != false) (v as bag) else set(v)),
         property let v := get(r2, x) in
                    (if (r2.multivalued? != false) (v as bag) else set(v)),
         any case r
             (property (if (r.multivalued? != false) { z in r.domain | x % get(r, z)}
                       else { z in r.domain | get(r, z) = x}),
              table (if (r.multivalued? != false) { z in r.domain | x % r[z]}
                     else { z in r.domain | r[z] = x}))))

// same: two useful methods that are used often
domain!(x:restriction) : class -> class!(x.domain[1])
methods(d:class,r:class) : set
 -> { m in method | (m.domain[1] <= d & m.range <= r)}

// sets the reified flag
claire/reify  :: property()
reify(l:listargs) : void
  -> (for p in l
       (case p (property p.reified := true)))

// *********************************************************************
// *   Part 4: Basics of Exceptions                                    *
// *********************************************************************

**arg :: property(open = 0)
args :: property(open = 0)
value :: property()

// a generic error that is produced by the error(" ....") instruction
general_error <: error(cause:any,arg:any)
self_print(self:general_error) : void
 -> format(self.cause, self.arg)

// a read_slot error is produced when an unknown value is found
read_slot_error <: error(arg:any,wrong:any)
self_print(self:read_slot_error) : void
    -> format("[138] The value of ~S(~S) is unknown", list(self.wrong, self.arg))

// range errors
range_error <: error(cause:any,arg:any,wrong:any)
self_print(self:range_error) : void
    -> format("[139] ~S: range error, ~S does not belong? to ~S.",
              list(self.cause, self.arg, self.wrong))

// selector errors
selector_error <: error(selector:any,arg:any)
self_print(self:selector_error) : void
  -> (let p := self.selector in
        (if not(p.restrictions)
          format("[140] The property ~S is not defined (was applied to ~S).", list(p, self.arg))
         else format("[141] ~S is a wrong arg list for ~S.",list(self.arg, p))))

// produced by a return (usually trapped)
return_error <: error(arg:any)
self_print(self:return_error) : void
  -> printf("[142] return called outside of a loop (for or while).")

// a global variable is a named object with a special evaluation
// NOTE: we need to refine the scheme for global constants !
global_variable <: system_thing(
    value:any,                    // the value
    range:type = any,             // the range is a type, {} means a global constant
    store?:boolean = false)       // GV are defeasible

close(self:global_variable) : global_variable
 -> (if not((unknown?(value, self) |
             (self.range % set | self.value % self.range)))
        range_error(arg = self.value, cause = self, wrong = self.range),
     self)


err_l:list :: list<any>(0,0)

// interpretation of all the error codes
self_print(self:system_error) : void
 -> (let n := self.index, 
         str_err := (err_l[1] := owner(self),
         			err_l[2] := n,
         			format("An internal error has occurred [~S:~A]:\n", err_l),
        			(if (n = 1) "Dynamic allocation, item is too big (~S)"
                else if (n = 2) "Dynamic allocation, too large for available memory (~S)"
                else if (n = 3) "Object allocation, too large for available memory (~S)"
                else if (n = 4) "Failed to load dynamic module ~A due to missing dependent module"
                else if (n = 5) "nth[~S] outside of scope for ~S"
                else if (n = 7) "Skip applied on ~S with a negative argument ~S"
                else if (n = 8) "List operation: cdr(()) is undefined"
                else if (n = 9) "String buffer is full: ~S"
                else if (n = 10) "Cannot create an imported entity from NULL reference"
                else if (n = 11) "nth_string[~S]: string too short ~S" //<sb> was short~S
                else if (n = 12) "Symbol Table table full"
                else if (n = 13) "Cannot create a subclass for ~S [~A]"
                else if (n = 16) "Temporary output string buffer too small"
                else if (n = 17) "Bag Type Error: ~S cannot be added to ~S"
                else if (n = 18) "Definition of ~S is in conflict with an object from ~S"
                else if (n = 19) "Integer overflow"
                else if (n = 20) "Integer arithmetic: division/modulo of ~A by 0"
                else if (n = 21) "Integer to character: ~S is a wrong value"
                else if (n = 22) "Cannote create a string with negative length ~S"
                else if (n = 23) "Not enough memory to instal claire"
                else if (n = 24) "Execution stack is full [~A]"
                else if (n = 26) "Wrong usage of time counter [~A]"
                else if (n = 27) "Internal garbage protection stack overflow (~S)"
                else if (n = 28) "The multivalued status of ~S is not compatible with ~S"
                else if (n = 29) "There is no module ~S"
                else if (n = 30) "Attempt to read a private symbol ~S"
                else if (n = 31) "External function not compiled yet"
                else if (n = 32) "Too many arguments (~S) for function ~S"
                else if (n = 33) "Exception handling: stack overflow"
                else if (n = 34) "User interrupt: EXECUTION ABORTED"
                else if (n = 35) "Reading char '~S': wrong char: ~S"
                else if (n = 36) "Cannot open file ~A"
                else if (n = 37) "World stack is full"
                else if (n = 38) "Undefined access to ~S"
                else if (n = 39) "Cannot convert ~S to an integer"
                else if (n = 40) "Integer multiplication overflow with ~S and ~S"
                else if (n = 41) "Wrong NTH access on ~S and ~S"
                else if (n = 42) "Wrong array[~S] init value: ~S"
                else if (n = 43) "Defeasible addition on list ~S requires pre-allocation (size ~S)" // v3.3.06
                else if (n = 50) "C++ imported error (~S) : ~S"   // NEW IN v3.1.04 (backdoor)
                //<sb> error mapping kernel additions
                else if (n = 57) "Signal stack overflow"
                else if (n = 58) "Invalid file operation"
                else if (n = 59) "~S is an invalid index for external buffer"
                else if (n = 60) "External buffer too long too be converted in a string"
                else if (n = 61) "Failed to allocate external memory [~A]"
                else if (n = 62) "Unescape premature end of string in [~A]"
                else if (n = 63) "Unescape &#...; bad formater in [~A]"
                else if (n = 64) "setenv(~A) failed"
                else if (n = 65) "setcwd(~A) failed"
                else if (n = 66) "pwd failed"
                else if (n = 67) "Invalid index ~S for environ"
                else if (n = 68) "Out of range category index ~S for setlocale, required in range (0 .. 5)"
                else if (n = 69) "The given combination of category (~S) and locale (~A) makes no sense"
                else if (n = 70) "The calendar time cannot be represented"
                else if (n = 71) "Bad wildard formater after character '#' accept only '##' '#?' '#*'"
                else if (n = 72) "Iteration of ~A/~A failed"
                else if (n = 73) "Iteration of ~A/* failed"
                else if (n = 74) "~A"
                else if (n = 75) "~A not implemented on this machine"
                else if (n = 76) "Invalid process id ~S"
                else if (n = 77) "Could not create the process"
                else if (n = 78) "unlink of ~A failed"
                else if (n = 79) "Could not make new directory ~A with mode ~A"
                else if (n = 80) "Could not remove directory ~A"
                else if (n = 81) "Could not change mode of ~A to ~S"
                else if (n = 82) "Could not create link with ~A and ~A"
                else if (n = 83) "Could not create symbolic link with ~A and ~A"
                else if (n = 84) "An error has occurred while copying file ~A to ~A"
                else if (n = 85) "Can't get forked pid since you are not a forker"
                else if (n = 86) "kill(~S,~S) failed"
                else if (n = 87) "raise(~S) failed"
                else if (n = 88) "setitimer(~S) failed"
                else if (n = 89) "getitimer(~S) failed"
                else if (n = 90) "The calendar time cannot be represented during the winter summer time transition"
                else if (n = 91) "Incorrect access to file ~A in ~A"
                else if (n = 92) "Operation attempted on a closed port"
                else if (n = 93) "Attempt to close a standard port (~S)"
                else if (n = 94) "lock failed on ~S"
                else if (n = 95) "unlock failed on ~S"
                else if (n = 96) "fcntl on ~S failed"
                else if (n = 97) "~A error on ~S"
                else if (n = 98) "Failed to create a pipe"
                else if (n = 99) "Failed to move file ~A to ~A"
                else if (n = 100) "There is no child process with pid ~S"
                else if (n = 101) "Too much child process, failed to create process ~A (args: ~A)"
                else if (n = 101) "No more process"
                else if (n = 102) "Failed to load dynamic module ~A - ~A"
                else if (n = 103) "Failed to load dynamic module ~A - unsupported"
                else (self.value := n,
                      "What the hell is this ! [code: ~S^]")))
           in (if (self.mClaire/cerr = 0)
           			(err_l[1] := self.value,
           			err_l[2] := self.arg,
           			format(str_err,err_l))
               else (err_l[1] := claire/cerror@integer(self.mClaire/cerr),
               		format("[~A] ", err_l),
               		err_l[1] := self.value,
               		err_l[2] := self.arg,
               		format(str_err, err_l))))

// contradictions are nice exceptions
contradiction <: exception()
self_print(x:contradiction) : void
 -> printf("A contradiction has occurred.")

// the format method is used to print error messages (similar to a printf)
// @doc Printing
// This method does the same thing as printf, except that there are always two
// arguments, thus the arguments must be replaced by an explicit list. Unlike
// with the printf construction \i ~I \/i cannot be used in a format. Last the string
// s may contain color escapes.
[format(self:string,larg:list) : void
 ->  let s := self,
         n := find(s, "~"),
         nl := 1,
         idx := 1,
         len := length(s),
         col:integer := externC("current_color",integer),
         bold:integer := externC("current_bold",integer),
         ccol:integer := col,
         cbold:integer := bold
     in
       (while (0 < n & n < len)
          let m := s[n + 1] in
            (if (n > 1) (color_princ(s, idx, n - 1),
            			externC("{ccol = current_color; cbold = current_bold;}")),
             if ('A' = m) (set_color(30,0),princ(larg[nl]), set_color(ccol,cbold))
             else if ('S' = m) (set_color(30,0),print(larg[nl]), set_color(ccol,cbold))
             else if ('I' = m) error("[143] ~I not allowed in format", unknown),
             if (m != '%') nl :+ 1,
             idx := n + 2,
             n := find(s, "~", idx)),
        if (idx <= len) color_princ(s,idx,len),
        set_color(col,bold))]
        

// special version that prints in the trace port
tformat(self:string,i:integer,l:list) : any
 -> (if (i <= system.verbose)
        let isforked? := externC("(isforked?CTRUE:CFALSE)", boolean),
        	p := use_as_output(system.ctrace)
        in (if isforked? self := "[" /+ string!(getpid()) /+ "]" /+ self,
        	format(self, l),
        	use_as_output(p)))

claire/on_trace :: property(open = 3)


//<sb> in xl claire we can define per module trace policy :
// if m.verbose is exactly true -> standard trace methods (tformat)
// if m.verbose is exactly false -> no trace at all
// if m.verbose is an integer -> like standard trace but we use m.verbose instead of system.verbose
// if m.verbose is a bag or an interval -> the trace line is generated if the trace level is in m.verbose
[should_trace?(m:module, i:integer) : boolean ->
	if (m.verbose % integer & i <= m.verbose)
		true
	else if ((m.verbose % bag | m.verbose % Interval) & i % m.verbose)
		true
	else if (m.verbose = true & i <= system.verbose)
		true
	else false]

[claire/mtformat(m:module, self:string, i:integer, l:list) : any ->
	if (known?(ctrace, system) & m.verbose != false & should_trace?(m, i))
		let p := use_as_output(ctrace())
		in (if externC("(isforked?CTRUE:CFALSE)", boolean)
				printf("`RED[~S]", getpid()),
			if not(m.name.name % {"claire", "Core", "Reader", "Language", "Generate", "Optimize"})
				printf("`GREEN[~A:~S]", m.name.name, i),
			princ(" "),
			format(self, l),
			use_as_output(p),
			for r in on_trace.restrictions
				(if known?(functional, r)
					let f:function := r.functional
					in externC("((fptr4)f->value)((CL_INT)m,(CL_INT)self,(CL_INT)i,(CL_INT)l)")))]

// printing a bag without ( )
// @doc Printing
// prints the content of the bag l on the current output (cout()).
// elements are separated by a comma ','.
princ(s:bag) : void
 -> (let f := true in
       for x in s (if f f := false else princ(","), print(x)))


<=2 :: operation()

// we create a special contradiction that we shall reuse
contradiction_occurs :: global_variable(range = contradiction,
                                        value = new!(contradiction))

// how to use it
// @doc versioning
// contradiction!() throws a contradiction. contradiction!() uses a
// unique instance of the contradiction exception class such to save
// a little memory.
contradiction!(system) : void -> close(contradiction_occurs)

// @doc list
// nil is the empty list instance.
nil :: global_variable(range = {}, value = Id(nil))       // v0.01
claire_date:string :: Id(date!(1))


//<sb> moved from Reader/file.cl


EOF :: global_variable(range = char, value = char!(255)) // v3.2.52
EOS :: global_variable(range = char, value = char!(0))

// @doc File system
// *fs* is a global variable that is set to a string that represent
// the file separator (system dependent). Usually "/" on UNIX and "\\"
// on windows.
claire/*fs*:string :: (if externC("\n#ifdef CLPC\nCTRUE\n#else\nCFALSE\n#endif\n", boolean) //<sb> was Id(*fs*) // */
							"\\"
						else "/")

//<sb> path separator (e.g. CLAIRE_LIBS)
// @doc File system
// *ps* is a global variable that is set to a string that represent
// the path separator (system dependent). Usually ":" on UNIX and ";"
// on windows.
claire/*ps*:string :: (if externC("\n#ifdef CLPC\nCTRUE\n#else\nCFALSE\n#endif\n", boolean)   // */
							";"
						else ":")


// @doc string
// s1 / s2 returns the concatenation of two path components.
// it is equivalent two s1 /+ *fs* /+ s2 where *fs* is the file
// separator ('/' under UNIX and '\' under win32)
// \code
// "toto" / "titi" -> "toto/titi".
// \/code
/(s:string,s2:string) : string ->
	let lens := length(s), lens2 := length(s2)
	in (if (lens = 0) s2
		else if (lens2 = 0) s
		else (while (rfind(s, *fs*) = lens) (s := substring(s, 1, lens - 1), lens :- 1),
			while (find(s2, *fs*) = 1) (s2 := substring(s2, 2, lens2), lens2 :- 1),
			(s /+ *fs*) /+ s2))

claire//- :: operation(precedence = precedence(/))

// @doc @xl string
// s1 /- s2 returns the concatenation of two path components where the
// last path component of s1 has been removed. For instance
// \code
// "toto/tata" /- "titi" -> "toto/titi".
// \/code
[/-(s1:string, s2:string) : string ->
	let p := rfind(s1,*fs*)
	in (if (p = length(s1)) p := rfind(s1,*fs*,p - 1),
		if (p > 0) substring(s1, 1, p) / s2
		else s1 / s2)]


ffor_error <: exception(childstr:string,childpid:integer)

[self_print(self:ffor_error) : void ->
	printf("forked for error, child ~S returned:\n~A",
		self.childpid, self.childstr)]

// end of file


