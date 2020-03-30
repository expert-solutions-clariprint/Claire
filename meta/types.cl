//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| types.cl                                                    |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+

// This file contains the definition of the CLAIRE type system (a true lattice).
// that is used both at compile- and at run-time.


// ******************************************************************
// *  Table of contents                                             *
// *                                                                *
// *    Part 1: Common Set Methods                                  *
// *    Part 2: definition of the type operators                    *
// *    Part 3: Interface methods                                   *
// *    Part 4: Lattice methods                                     *
// *    Part 5: Type methods                                        *
// *                                                                *
// ******************************************************************

claire/arg1 :: property()
claire/arg2 :: property()
claire/-- :: operation(precedence = precedence(..))

// *********************************************************************
// *   Part 1: Common Set Methods                                      *
// *********************************************************************

// ----------------------- useful methods ------------------------------
// @doc type
// finite?(self) returns true if the type self represents a finite set.
// Set iteration (with the for loop) can only be done over finite sets.
[finite?(self:type) : boolean
 -> case self
      (set true,
       list not({ t in self | not(finite?(t))}),
       class let n := self.open in (n >= 0 & n <= 2 & self != any),
       any false) ]


// making a bag from an abstract_set
[enumerate(self:any) : bag
 -> case self
      (bag self,
       array list!(self),
       integer make_set(self),
       collection set!(self),
       any error("[178] cannot enumerate ~S",self)) ]

// =type? is an operation (equality on types)
=type? :: operation()

// @doc type
// returns true if x and y denote the same type. For example =type?(boolean, {true, false})
// returns true because defined(boolean) was declared after the two instances true and false
// were created, so the system knows that no other instances of boolean may ever be created
// in the future. This equality is stronger than set equality in the sense that the system
// answers true if it knows that the answer will hold everafter.
[=type?(self:type,ens:type) : boolean -> (self <= ens & ens <= self)]

// finds the sort associated to a type
[sort!(x:type) : class
 -> case x
      (class sort!(x),
       any sort!(class!(x))) ]


// the membership membership for lattice_sets
[%(self:any,ens:class) : boolean
  -> if inherit?(owner(self),ens) true else false]

// an extension for %
[%type(x:any,y:any) : boolean
  -> if (x % type & y % set) exists(z in (y as set) | =type?(x,z))     // v3.2.28
     else (x % y) ]


// ****************************************************************
// *         Part 2: definition of the type operators             *
// ****************************************************************
Type <: type()

// union of two types ---------------------------------------------

// Disjonctive Union Axiom (DU): Each union (A U B) is strictly disjunctive:
//       (1) A ^ B = 0
//       (2) x < A U B <=> x < A or x < B
// Producing disjunction union is a form of normalization (the previous notion
// of distributivity was a lousy bug)
// DU Axiom is necessary to make <= and ^ easier to define
// This is achieved in the U method
Union <: Type(t1:type,t2:type)
self_print(self:Union) : void -> printf("(~S U ~S)", self.t1, self.t2)
finite?(self:Union) : boolean -> (finite?(self.t1) & finite?(self.t2))

// Intervals of integers ----------
Interval <: Type(arg1:integer,arg2:integer)
self_print(self:Interval) : void
 -> (printf("(~S .. ~S)", self.arg1, self.arg2))

finite?(self:Interval) : boolean -> true

// true constructor
--(x:integer,y:integer) : Interval
  -> (if (x <= y) (x .. y) as Interval // Interval(arg1 = x, arg2 = y)
      else error("[182] the interval (~S -- ~S) is empty",x,y))

// Parameterized class. -------------------------------------------
Param <: Type(arg:class,params:list,args:list)

[self_print(self:Param) : void
 -> if (length(self.params) = 1 & self.params[1] = of & self.args[1] % set)
       printf("~S<~S>", self.arg, (self.args[1] as set)[1])
    else printf("~S[~I]", self.arg,
           (for i in (1 .. length(self.args))
              (if (i != 1) princ(", "),
               printf("~S:(~S)", self.params[i], self.args[i])))) ]

finite?(self:Param) : boolean -> finite?(self.arg)

// subtype[X] ----------------------------------------------
// subtype[X] = {u in type | u <= t}
// for closure purposes, we add an arg Y -> Y inter st[X]
// Y can be any type class, but we forbid parametrisation on such classes !
// thus we can ensure that Y is a class
subtype <: Type(arg:class,t1:type)
[self_print(self:subtype) : void
   -> if (self.arg = type) printf("subtype[~S]", self.t1)
      else printf("~S[~S]", self.arg, self.t1) ]            // v3.2

finite?(self:subtype) : boolean -> (self.arg = set & finite?(self.t1))


// creates a subtype, with some normalization
// v3.2 list[t] -> subtype 
[nth(self:class,x:type) : type
 -> (if (self = set | self = list)  subtype(arg = self, t1 = x)
            ;   Param(arg = self, params = list(of),
            ;         args = list(subtype( arg = type, t1 = x)))
      else if not(self inherit? type) error("[177] subtyping of ~S not allowed",self)
      else subtype(arg =  (if (self = subtype) type else self), t1 = x)) ]

// create a Param with a list of parameters (constant properties) l1 and a list
// of types l2
[nth(self:class,l1:list,l2:list) : type
 -> // patch in v3.2.36  -> rather ugly ... the whole processing of X[Y..] pattern should be revised
    if ((self = list | self = set) & l2[1] % subtype)
        nth(self, (l2[1] as subtype).t1)   // this is the patch
    else if ((self = list | self = set) & l1[1] != of)
        error("[177] the subtyping expression ~S[~A] is not allowed",self,l1) // v3.2.36
    else Param(arg = self, params = l1, args = l2)]

// create a Param of the stack[X] kind
[param!(self:class,tx:type) : type
 ->  Param(arg = self, params = list(of), args = list(set(tx))) ]

// create the t[] param
[nth(self:type) : type
 ->  Param(arg = array, params = list(of), args = list(set(self))) ]

// tuple are types
finite?(self:tuple) : boolean -> forall(x in self | finite?(x))

// reference to a previous variable, not a type but a pattern -------
// index is the position of the stack of the referred type
// args is a list representing the path (a sequence of properties (parameters))
// a property is applied to the referred type
// if arg = true, the reference is the singleton containing the ref. value
// TODO check that arg is still used !
Reference <: Type(args:list,index:integer,arg:boolean = false)
self_print(self:Reference) : void -> printf("<ref:~S(ltype[~A])>",self.args,self.index)
get(self:Reference,y:any) : any
 -> (let l := self.args in
       (for i in (1 .. length(l)) y := (funcall(l[i] as property, y)), y))

// apply a reference to a type (l is args(self), passed for disambiguation)
@(self:Reference,l:list,y:any) : any
 -> (//[5] apply[@] ~S to ~S // self,y,
     for i in (1 .. length(l)) y := y @ (l[i] as property), y)

// type to set coercion  -------------------------------------------------

// new in v3.0.5 = use an interface method for type enumeration

// the default strategy is extensible: we look if there exists
// a proper definition that could be interpreted !
set!(x:collection) : set
  -> let m := (set! @ x.isa) in
       (if (domain!(m) != collection) (funcall(m,x) as set)
        else error("[178] cannot enumerate ~S",x))

size(x:collection) : integer
  -> let m := (size @ x.isa) in
       (if (domain!(m) != collection) (funcall(m,x) as integer)
        else length(set!(x)))                 // v3.2.34  -> makes the API simpler

(interface(size))

// set is needed for recursive def
set!(x:set) : set -> x
size(x:set) : integer -> length(x)

// set is needed for recursive def
size(x:list) : integer -> length(set!(x))

// class  -> return a read-only list  (v3.2)
set!(x:class) : set
  -> let rep := list<class>() in
       (for c in x.descendents
          (if (inherit?(c,primitive) & c != boolean)
              error("[178] cannot enumerate ~S",c)
           else rep := rep /+ c.instances),
        set!(rep))

size(self:class) : integer
  -> let n:integer := 0 in
        (for x in self.descendents n :+ length(x.instances), n)


// Union
set!(x:Union) : set -> (set!(x.t1) /+ set!(x.t2))

size(x:Union) : integer
  ->  (if (x.t1 % Interval | x.t1 % set)  (size(x.t1) + size(x.t2))
       else length(set!(x)))

// interval
set!(x:Interval) : set
  -> --?(x.arg1, x.arg2)

size(self:Interval) : integer
  -> (self.arg2 + 1 - self.arg1)

// param
set!(x:Param) : set
  -> { y in set!(x.arg) | y % x}
size(x:Param) : integer -> length(set!(x))

// subtype
set!(x:subtype) : set
  ->  (if (x.arg = set) build_powerset(list!(set!(x.t1)))
       else error("[178] cannot enumerate ~S",x))
size(x:subtype) : integer
  -> (if (x.arg = set) ^2(size(x.t1))
      else error("[178] cannot enumerate ~S",x))

// tuple
set!(x:tuple) : set
  ->  let l := (x as list) in    // v3.0.54
        (if not(l) {{}}
         else let l1 := { list(y) | y in set!(l[1])} in
           (for n in (2 .. length(l))
             let l2 := set<any>() in
                (for z in set!(l[n])
                   for l3 in l1 l2 :add copy(l3) add z,
                 l1 := l2),
            l1))

size(l:tuple) : integer
  ->  (if not(l) 1
       else let m := size(l[1] as type) as integer in
          (for n in (2 .. length(l)) m :* size(l[n] as type),
           m))


// generic collection membership
// v3.2.24: this is extensible through the redefinition of %
[member?(x:any,y:type) : boolean
 -> case y
      (Union (member?(x, y.t1) | member?(x, y.t2)),
       Interval (case x (integer (y.arg1 <= x & x <= y.arg2), any false)),
       Param let n := 1,
                 l := y.args in
               (x % y.arg &
                not((for p:property in y.params
                       (if not(%type(funcall(p, x),l[n])) break(true) else n :+ 1)))),
       subtype ((if (y.arg = subtype) x % type else x % y.arg)
                 & (x <=t y.t1)),  // y.arg < type !
       tuple let n := length(y) in
               case x
                (tuple (length(x) = n &
                        forall( i in (1 .. n) | x[i] % y[i])),
                 any false),
       bag x % y,
       class x % y,
       Reference true,
       any let start := index!() in         // this is the extensibility part
             (push!(x),
              push!(y),
              let m := find_which(%, start, owner(x)) in
                (if (case m
                      (method
                         (length(m.domain) = 2 & m.domain[2] != any)))
                    (eval_message(%, m, start, true) as boolean)
                 else error("[179] (~S % ~S): not implemented!", x, y)))) ]

// @doc class
// class!(x) returns the intersection of all classes y such that x <= y that is
// the best class approximation
// (Such an intersection always exists since classes are organized in a lattice).
// Hence, if c is a class class!(c) = c.
[class!(x:type) : class
 -> case x
      (class x,
       set (if (length(x) = 0) void
           else let rep := owner(x[1]) in
                  (for y in x rep := ((rep meet owner(y)) as class), rep)),
       Union (class!(x.t1) meet class!(x.t2)) as class,
       Interval integer,
       subtype (if (x.arg = subtype) any else x.arg),
       Param x.arg,
       Reference any,
       tuple tuple,
       any any) ]

// declarations
(ephemeral(Union),
 ephemeral(Param),
 ephemeral(Interval),
 ephemeral(subtype))

// ********************************************************************
// *                Part 3: Interface Methods                         *
// ********************************************************************

// there is a special restriction for + to specify the way the inheritance
// conflict should be solved
//U(self:set,ens:type) : type -> (case ens (set self /+ ens, any ens U self))

// the union makes a partial reduction to the normal form. The complete
// reduction is done by enumeration if needed during the type subsumption
// union is left-associative: A U B U C is represented by (A U B) U C  => never(t2(x:Union) % union)
// a union of intervals is ALWAYS disjoint
U(x:type,y:type) : type
 -> (case x
      (set case y (set x /+ y, any y U x),
       any (if (y <=t x) x
           else if (x <=t y) y
           else if (y % Union) (x U y.t1) U y.t2
           else if (case x (Interval (y % Interval)))
              (if (y.arg1 - 1 <= x.arg2 & x.arg1 <= y.arg1)       // adjacent
                  x.arg1 .. y.arg2
               else if (x.arg1 - 1 <= y.arg2 & y.arg1 <= x.arg1)
                  y.arg1 .. x.arg2
               else Union(t1 = x, t2 = y))
           else if (case x (Union y % Interval))
              let z := (x.t2 U y) in
                case z
                 (Union Union(t1 = (x.t1 U y), t2 = x.t2),
                  any x.t1 U z)
           else if (case x (Interval (y % set & (x.arg1 - 1 % y | x.arg2 + 1 % y))))
               let a := x.arg1, b := x.arg2 in    // new in v0.30
                 (if (a - 1 % y) a :- 1,
                  if (b + 1 % y) b :+ 1,
                  (a .. b) U y)
           else (if (y % set) y := {z in y | not(z % x)},
                 Union(t1 = x, t2 = y)))))


// the Interval construction method has a smart second-order type  - fix on v3.1.06
[..(x:integer,y:integer) :  type[(if (unique?(x) & unique?(y) & the(x) <= the(y))
                                    set(the(x) .. the(y))
                                  else subtype[integer]) ]
 -> if (x <= y) Interval(arg1 = x, arg2 = y) else {} ]

// exception
but :: operation()
but(s:any,x:any) : type[nth(bag,member(s))]      // <yc> 16/3/98
 -> (case s (list list{y in s | y != x},         // v3.3.36 (thanks to fxj)
             set copy(s) delete x, 
             any set!(s) delete x))

\ :: operation(precedence = U.precedence)
\(x:type,y:type) : set -> {z in x | not(z % y)}


// ******************************************************************
// *    Part 4: Lattice methods                                     *
// ******************************************************************

// glb operation ---------------------------------------------------
// should use type

// new in v3.0.60: we reintroduce a glb method
claire/glb :: operation(precedence = precedence(^), domain = type, range = type,     // v3.2.32 error !
                        mClaire/dispatcher = 4)

glb(x:set,y:type) : set -> { z in x | z % y}

glb(x:Union,y:type) : type ->  ((x.t1 glb y) U (x.t2 glb y))

glb(x:Interval,y:type) : type
 ->  (case y
       (class (if (integer <=t y) x else {}),
        set y glb x,
        Interval  (if (x.arg1 <= y.arg1)
                     (if (y.arg1 <= x.arg2)
                        (if (x.arg2 <= y.arg2) y.arg1 .. x.arg2
                         else y)
                      else {})
                   else y glb x),
        Union ((x glb y.t1) U (x glb y.t2)),    // v3.0.44
        any {}))

glb(x:class,y:type) : type
 -> (if (x.open = system.abstract & not(x.subclass)) { z in x | z % y}
     else if (x.open = system.abstract & not(x.instances))
        Uall(list{ (z glb y) | z:type in x.subclass})
     else case y (class x join y, any y glb x))

glb(x:Param,y:type) : type
 -> (case y
      (Param let c := (x.arg join y.arg),
                 lp := list!(set!(x.params /+ y.params)),
                 l := list<any>() in
               (for p in lp
                  let t := ((x @ p) glb (y @ p)) in
                    (if (t != {}) l :add t else (c := {}, break(true))),
                if (c != {}) Param(arg = c, params = lp, args = l)
                else {}),
       class let c := (x.arg join y) in
               (if (c != {}) Param(arg = c, params = x.params, args = x.args)
                else {}),
       any y glb x))

// notice that a param whose class is a type must use of (only parameter allowed!)
// the result is a subtype
glb(x:subtype,y:type) : type
 -> (case y
      (class (if ((x.arg join y) != {}) nth(x.arg join y, x.t1)       // v3.00.07
             else {}),
       Param (if ((x.arg join y.arg) != {})
                 param!(x.arg join y.arg, member(x) glb member(y))
              else {}),
       subtype (if ((x.arg join y.arg) != {})
                  let t := (x.t1 glb y.t1) in
                    (if (t != {}) nth(x.arg join y.arg, t) else {})
               else {}),
       any y glb x))

// set, Interval, list
glb(x:tuple,y:type) : type
 -> (case y
      (class (if (tuple inherit? y) x else {}),    // v2.4 BUG
       Param {},
       tuple tuple!((x as list) ^ (y as list)),    // ^ on lists implements Cartesian product ^
       subtype (if (y.arg = tuple) tuple!(list{ (z glb y.t1) | z in x})
               else {}),
       any y glb x))


// a reference is seen as "any"
glb(x:Reference,y:type) : type -> y

// this will be greatly simplified in a few minutes !
^(x:type,y:type) : type -> (x glb y)

// the old lattice_glb
[join(x:class,y:class) : type
 -> let l1 := x.ancestors, n1 := length(l1),
        l2 := y.ancestors, n2 := length(l2) in
       (if (n1 < n2)
           (if (l2[n1] = x) y else {})
        else if (l1[n2] = y) x
        else {}) ]

// for lists
[^(x:list,y:list) : list
 ->  let n := length(x),
         r:list := list() in
       (if (n = length(y))
           for i in (1 .. n)
             let z := (x[i] glb y[i]) in
               (if (z != {}) r :add z else (r := nil, break(true))),
        r) ]


// a combined union
Uall(l:list) : type -> (let rep := {} in (for x in l rep :U x, rep))

// ------------------- The inclusion operation ------------------------


<=t :: operation(precedence = precedence(<=), domain = type, range = boolean,
                 mClaire/dispatcher = 5)   // hand-made

// v3.2: extend from set to bags
<=t(s:bag,y:type) : boolean 
  -> let z := of(s) in
      (if (z != {}) (z <=t y)
       else forall( x in s | %type(x, y)))

// class
<=t(x:class,y:type) : boolean
 -> (case y
      (class y % x.ancestors,
       tuple false,
       Union (if (x.open = 0 & not(x.instances))
                not({ c in x.subclass | not(c <=t y)})
             else (x <=t y.t1 | x <=t y.t2)),
       set (if (x.open = 0 & not(x.subclass)) forall(u in x | u % y)
            else false),   // <yc>:2/98, 7:98
       any <=t@type(x,y)))

// Union
<=t(x:Union, y:type) : boolean  -> (x.t1 <=t y & x.t2 <=t y)

// Interval
<=t(x:Interval, y:type) : boolean
  -> (case y (Interval (y.arg1 <= x.arg1 & x.arg2 <= y.arg2),
              set ((set!(x) as bag) <=t y),
              Union (x <=t y.t1 | x <=t y.t2),
              class (integer inherit? y),
              any <=t@type(x, y)))

// subtype
<=t(x:subtype,y:type) : boolean
 -> (case y (Param <=t@type(x, y),
             subtype <=t@type(x, y),
             Union (x <=t y.t1 | x <=t y.t2),  // Requires DU Axiom
             any x.arg <=t y))

// Param is similar !
<=t(x:Param,y:type) : boolean
 -> (case y (Param <=t@type(x, y),
             subtype <=t@type(x, y),
             Union (x <=t y.t1 | x <=t y.t2),    // same
             any x.arg <=t y))

// Reference
<=t(x:Reference,y:type) : boolean -> true

// tuple : the only subtlety is the de-normalization of U within a tuple type
<=t(x:tuple,y:type) : boolean
  -> (when i := some(j in (1 .. length(x)) | x[j] % Union) in
               let ui := (x[i] as Union), x1 := copy(x), x2 := copy(x) in
                 (nth=(x1 as list,i,ui.t1),           // v3.1.14
                  nth=(x2 as list,i,ui.t2),
                  x1 <=t y & x2 <=t y)                   // lazy  normalization
      else case y
            (tuple (length(x) = length(y) &          // 3.1.16 <fxj>
                    forall( i in (1 .. length(x)) | x[i] <=t y[i])),
             Union (x <=t y.t1 | x <=t y.t2),    // same  v3.1.14
             any tuple <=t y))



// this is a generic ordering when y is a type Interval, a subtype or a Param
// x <= one such type is actually easy
<=t(x:type,y:type) : boolean
 -> (case y
      (Param (x <=t y.arg &
              forall(n in (1 .. length(y.params)) |
                     (x @ y.params[n] <=t y.args[n]))),
       Reference true,
       subtype (x <=t y.arg & member(x) <=t y.t1),               // new
       Interval false,
       any less?(x,y)))                                       // for extensibility !


// default order for types
<=(x:type,y:type) : boolean  -> (x <=t y)


// ******************************************************************
// *    Part 5: type methods                                        *
// ******************************************************************

// --------------------- extract tuple type information -------------

// extract a member type, that is a valid type for all members (z) of instances of
// the type x. This is much simpler in v3.0
// @doc type
// member(x) returns the type of all instances of type x, assuming that x
// is a CLAIRE type which contains objects y such that other objects z can
// belong to. If this is the case, member(x) is a valid type for all such z,
// otherwise the returned value is the empty set. For instance, if x is
// list[integer], all instances of x are lists that contain integers, and all
// members of these lists are integers. Therefore, member(list[integer]) is integer.
[member(x:type) : type
 ->  case x
        (class (if (x = Interval) integer else any),
         Union member(x.t1) U member(x.t2),
         Interval {},
         Param member(x @ of),
         tuple Uall(x as list),
         subtype x.t1,
         set Uall(list{ (case y (list set!(y), type y, any {})) | y in x}),
         any {}) ]

// a simpler version (projection on bag subtypes)
// dumb code because it is used early in the bootstrap
[of_extract(x:type) : type
 -> let c := x.isa in
      (if (c = subtype) (x as subtype).t1
       else if  (c = Param)
         (if ((x as Param).params[1] = of)
             let y := ((x as Param).args[1] as type) in
               case y (set (y[1] as type),
                       subtype y.t1,
                       any any)
          else any)
       else any) ]


// --------------------- extract range information ------------------
// the method @ is used to extract the range information contained
// in a type. This method returns a type and is crucial for compiling !
[@(x:type,p:property) : type
 -> case x
      (class let r := (p @ x) in (if (r != false) (r as restriction).range else any),
       Param let i := get(x.params, p) in
               (if (i > 0) (x.args[i] as type) else x.arg @ p),
       Union (x.t1 @ p) U (x.t2 @ p),
       set Uall(list{ set(funcall(p, y)) | y in x}),     // v3.2.50: needs funcal vs get !
       any (class!(x) @ p)) ]

// useful type functions for the compiler
[unique?(x:type) : boolean
 -> case x
      (set size(x) = 1,
       class (x.open = 0 & size(x) = 1),
       any false) ]

// returns the unique element of the type
the(x:type) : any -> set!(x)[1]

// bitvector made easy
// v0.01: should not use set[0 .. 29] => burden on caller is too heavy
// @doc number
// integer!(l) returns the integer represented by the bitvector l,
// i.e. the sum of all 2i for i in l.
[integer!(s:set[integer]) : integer
 -> let n := 0 in
       (for y in s (if (y % (0 .. 29))  n :+ ^2(y)), n) ]

// @doc number
// make_set(x) returns the set of bit index that are set in the integer x
// seen as a bitvector.
claire/make_set(x:integer) : set -> {i in (0 .. 29) | x[i]}

// asbtract coercion of a set into an interval
[abstract_type(xt1:set) : type
 -> let m1 := 1,
        m2 := 0 in
       (for x in xt1
          case x
           (integer (if (m1 > m2) (m1 := x, m2 := x)
                    else if (x > m2) m2 := x
                    else if (x < m1) m1 := x),
            any (m1 := 1, m2 := 0, break(true))),
        m1 .. m2) ]

// abstract interpretation of integer arithmetique
[abstract_type(p:operation,xt1:type,xt2:type) : type
 -> case xt1
      (set (if (xt1 != {}) abstract_type(p, abstract_type(xt1), xt2) else xt1),
       Interval case xt2
                (Interval
                   (if (p = +)
                       (xt1.arg1 + xt2.arg1) .. (xt1.arg2 + xt2.arg2)
                    else if (p = -)
                       (xt1.arg1 - xt2.arg2) .. (xt1.arg2 - xt2.arg1)
                    else integer),
                 set (if (xt2 != {}) abstract_type(p, xt1, abstract_type(xt2))
                     else xt2),
                 Union abstract_type(p, xt1, xt2.t1) U abstract_type(p, xt1, xt2.t2),
                 any integer),
       Union abstract_type(p, xt1.t1, xt2) U abstract_type(p, xt1.t2, xt2),
       any integer) ]

// we create some types that we need
(set_range(subclass, class, set<class>),
 set_range(ancestors, class, list<class>),
 set_range(descendents, class, set<class>),
 set_range(definition, property, list<restriction>),
 set_range(restrictions, property, list<restriction>),
 set_range(domain,restriction,list<type>),
 set_range(slots, class, list<slot>))

// a useful second ortder type
first_arg_type(x:type,y:type) : type -> x
first_arg_type(x:type,y:type,z:type) : type -> x
second_arg_type(x:type,y:type) : type -> y
meet_arg_types(x:type,y:type) : type -> (x U y)
first_member_type(x:type,y:type) : type -> member(x)  // v3.3.10

//<sb> v3.3.33 rewrite second order type for /+ and cast!
append_type(x:type,y:type) : type ->
 (case x
  (subtype[set] set[member(x) U member(y)],
  subtype[bag] list[member(x) U member(y)],
  any meet_arg_types(x,y)))

cast!_type(x:type,y:type) : type ->
 (case x
  (subtype[set] (if unique?(y) set[the(y)] else set),
  subtype[list] (if unique?(y) list[the(y)] else list),
  any tuple))

prealloc_set_type(x:type,y:type) : type ->
 (if unique?(x) set[the(x)]
 else set)

prealloc_list_type(x:type,y:type) : type ->
 (if unique?(x) list[the(x)]
 else list)

// we place here all methods that require second order types !!!!
//nth_get(a:array,n:integer) : type[member(a)] -> function!(nth_get_array)
nth(self:array,x:integer) : type[member(self)]
 -> (if (x > 0 & x <= length(self)) nth_get(self,x)
     else error("[180] nth[~S] out of scope for ~S", x, self))
// @doc array
// returns an array of length n filled with x. The parameter t is the member_type of
// the array, thus x must belong to t, as well as any future value that will be put
// in the array.
make_array(i:integer,t:type,v:any) : type[ (if unique?(t) (the(t))[] else array)]
 -> function!(make_array_integer,NEW_ALLOC)
 
make_list(n:integer,t:type,x:any) : type[ (if unique?(t) list[the(t)] else list)]
  -> (cast!(make_list(n,x),t) as list)

make_list_type(x:type,y:type) : type ->
 (if unique?(x) list[the(x)]
 else list)

make_set(self:array<X>) : type[(if (X = any) set else set<X>)]
  -> set!(list!(self))
list!(a:array<X>) : type[(if (X = any) list else list<X>)]
 -> function!(list_I_array, NEW_ALLOC)
array!(a:list<X>) : type[(if (X = any) array else array<X>)]
 -> function!(array_I_list, NEW_ALLOC)      // v3.0.72

set!(l:list<X>) : type[(if (X = any) set else set<X>)]  // v3.1.06
  -> function!(set_I_bag,NEW_ALLOC,SAFE_RESULT)
list!(l:set<X>) : type[(if (X = any) list else list<X>)]
  -> function!(list_I_set,NEW_ALLOC,SAFE_RESULT)


// new in v3.0.60 : second-order type for copy
//<sb> exclude copy@(string,integer)
(for r in list{r in copy.restrictions|length(r.domain) = 1} (r as method).Kernel/typing := Id,
 for r in empty.restrictions (r as method).Kernel/typing := Id,
 for r in sort.restrictions (r as method).Kernel/typing := second_arg_type,
 for r in /+.restrictions (r as method).Kernel/typing := append_type, //meet_arg_types,
 (cast! @ set).Kernel/typing := cast!_type,
 (cast! @ list).Kernel/typing := cast!_type,
 (prealloc_set @ type).Kernel/typing := prealloc_set_type,
 (prealloc_list @ type).Kernel/typing := prealloc_list_type,
 (make_list @ type).Kernel/typing := make_list_type,
 // here we add some simple second orders
 (nth_get @ array).Kernel/typing := first_member_type,
 for r in nth+.restrictions (r as method).Kernel/typing := first_arg_type,
 for r in add.restrictions
    (if (length(r.domain) = 2) (r as method).Kernel/typing := first_arg_type),
 for r in delete.restrictions
    (if (length(r.domain) = 2) (r as method).Kernel/typing := first_arg_type))


refine_append_of(self:bag,x:bag,y:bag) : void ->
	let %x := of(x), %y := of(y) in 
      (if (%x = %y) cast!(self, %x)
       else cast!(self, x.of U y.of))

(#if compiler.loading?
	externC("callback_refine_append_of = refine_append_of_bag1"))


claire/set_color(c:(30 .. 37), b:{0,1}) : void -> function!(color)

//<sb> refine freadline range
(put(range,freadline.restrictions[5],tuple(string,(string U char))))
(put(range,freadline.restrictions[6],tuple(string,(string U char))))
(put(range,freadline.restrictions[7],tuple(string,(string U char))))


[claire/set_user(username:string) : void ->
	externC("
		#ifndef CLPC
		#ifdef HAVE_PWD_H
	"),
	externC("struct passwd *pw = getpwnam(username)"),
	if externC("(pw == NULL ? CTRUE : CFALSE)", boolean)
		externC("Cerrorno(74,_string_(\"getpwnam\"),0)"),
	if externC("(setgid(pw->pw_gid) ? CTRUE : CFALSE)", boolean)
		externC("Cerrorno(74,_string_(\"setgid\"),0)"),
	if externC("(setuid(pw->pw_uid) ? CTRUE : CFALSE)", boolean)
		externC("Cerrorno(74,_string_(\"setuid\"),0)"),
	externC("
		#endif
		#endif
	")]
	

[claire/sizeof(x:any) : tuple(integer, integer) ->
	tuple(
		(case x
			(string length(x),
			array length(x),
			bag length(x),
			object
				let s := last(owner(x).slots)
				in (s.mClaire/index +
						(if (s.mClaire/srange = float) 1 else 0)),
			any 1)),
		(case x
			(string length(x),
			array externC("*(((int*)OBJECT(ClaireAny, x)) - 1)", integer),
			bag externC("*(OBJECT(bag,x)->content)", integer),
			object externC("*(((int*)array_v(x)) - 3)", integer),
			any 1)))]

[claire/sizeof(c:class) : tuple(integer, integer) ->
	if (c <= object) sizeof(mClaire/new!(c))
	else tuple(0, 0)]


// *********************************************************************
// *   Part 5: Debug                                                   *
// *********************************************************************


// @cat @xl Debugging
// @section Using XL Claire
// XL Claire comes with a debugger that let the user control and step during
// a program execution and locate the place where an exception was thrown.
// The debugger interface is inspired by gdb (the popular
// GNU debugger) and provide backtrace, source file listing, frame inspection
// including local variables.\br
// In order to be debugged some code have to be instrumented which is done
// by specifying the -debug option on the command line. Since the instrumentation
// is performed at the meta level the debugger would handle interpreted and compiled
// code homogeneously.
// @cat


claire/none :: keyword()

//<sb> a debug frame holds a location and a remainder for
// the local context (i.e. method arguments and local variables)
// the location is updated while the program runs because the
// loaded meta code is instrumented with instructions that modifies
// the current frame.
// A new frame is usually created for the scope of a method body such
// to hold the context of that method.
// note : variable of a given context may be given the same name to
// avoid problem when a variable comes out of scope we keep a list
// of all local vars and just pop variable one time at a time.
dbg_frame <: ephemeral_object
dbg_frame <: ephemeral_object(
		vars:list[any],
		num:integer = 0,
		step?:boolean = false,
		dimension:integer = 0,
		frame_source:any, // selector, class, rule name
		compiled?:boolean,
		source:string = "", // file name
		line:integer = 0,
		column:integer = 0,
		length:integer = 0,
		catch?:boolean = false,
		new?:boolean = true,
		prev:dbg_frame, // bidirectional linked list
		next:dbg_frame)


//<sb> the top and the innermost frames, the innermost frame
// is updated while the program runs
top_frame :: dbg_frame()
current_frame:dbg_frame := top_frame

[reset_frame_stack() : void ->
	current_frame := top_frame,
	when p := get(next, current_frame)
	in (erase(prev, current_frame.next),
		erase(next, current_frame))]

// 0: continue
// -1: step all
// >0: index of frame to step
STEP:integer := 0



//<sb> builds a new debug frame
[push_frame(self:any) : void ->
	let nf := dbg_frame(frame_source = self, num = current_frame.num + 1)
	in (current_frame.next := nf,
		nf.prev := current_frame,
		current_frame := nf)]

//<sb> drop the last debug frame
[pop_frame() : void ->
	current_frame := current_frame.prev,
	erase(prev, current_frame.next),
	erase(next, current_frame)]

[push_arg(nam:string, val:any) : void ->
	let fr := current_frame
	in (fr.vars add nam,
		fr.vars add val,
		fr.dimension :+ 1)]

[push_var(nam:string, val:any) : void ->
	let fr := current_frame
	in (fr.vars add nam,
		fr.vars add val)]

[pop_var() : void ->
	let vs := current_frame.vars
	in shrink(vs, length(vs) - 2)]


[update_var(nam:string, val:any) : void ->
	let fr := current_frame,
		vs := fr.vars,
		i := length(vs) - 1
	in (while (i > 0)
			(if (vs[i] = nam)
				(vs[i + 1] := val,
				break()),
			i :- 2))]



claire/BREAKPOINTS :: set<any>() 
on_break_program :: property(open = 3)


//<sb> update in the current frame with the current execution location, i.e.
// a transition occurs between two states : this is where the stepper and
// breakpoints are checked
[update_location(f:string, l:integer, c:integer, n:integer) : void ->
	let fr := current_frame,
		same? := (n = fr.length & c = fr.column & l = fr.line & fr.source = f)
	in (fr.source := f,
		fr.line := l,
		fr.column := c,
		fr.length := n,
		if (fr.new? & get(frame_source, fr) % tuple & fr.frame_source[2] % BREAKPOINTS)
		  (fr.new? := false,
		  on_break_program())
		else if (not(same?) & STEP != 0)
			break_if_needed(fr, STEP),
		fr.new? := false)]

[break_if_needed(fr:dbg_frame, st:integer) : void ->
	if (st = -1 | st = fr.num)
		on_break_program()]

HANDLE_FRAMES[oid:string] : dbg_frame := top_frame

[push_handle(oid:string) : void -> HANDLE_FRAMES[oid] := current_frame]
[pop_handle(oid:string) : void ->
	let fr := HANDLE_FRAMES[oid]
	in (HANDLE_FRAMES[oid] := top_frame,
		current_frame := fr,
		when nfr := get(next, fr)
		in erase(prev, nfr),
		erase(next, fr))]


[push_handle_frame(f:string, l:integer, c:integer, n:integer, oid:string) : void ->
	let nf := copy(HANDLE_FRAMES[oid])
	in (nf.num := current_frame.num + 1,
		current_frame.next := nf,
		nf.prev := current_frame,
		current_frame := nf,
		nf.catch? := true,
		nf.source := f,
		nf.line := l,
		nf.column := c,
		nf.length := n,
		if (STEP != 0) break_if_needed(nf, STEP))]



[claire/dload(m:string, path:string) : void ->
  if not(get_value(m) % module)
    let sym := (print_in_string(),
                printf("dynLoad~I", c_princ(m)),
                end_of_string()),
        curmod := module!()
    in (externC("
#ifdef CLPC

HINSTANCE h = LoadLibrary(path);
if (h == NULL) Cerrorno(102, _string_(m), 0);

void (*proc)() = (void (*)())GetProcAddress(h, sym);
if (proc == NULL) Cerrorno(102, _string_(m), 0);
proc();

#elif defined(__hpux)

shl_t h = shl_load(path,DLOAD_FLAGS,0L);
if (h == NULL) Cerrorno(102, _string_(path), 0);
void (*proc)();

shl_findsym(&h, sym, TYPE_UNDEFINED, (void*)&(proc));
if (proc == NULL) Cerrorno(102, _string_(path), 0);
proc();

#elif defined(HAVE_DLOPEN)

void *h = dlopen(path,DLOAD_FLAGS);
if (h == NULL) Cerror(102, _string_(m), _string_(dlerror()));

void (*proc)() = (void (*)())dlsym(h, sym);
if (proc == NULL) Cerrorno(102, _string_(m), _string_(dlerror()));
proc();

#else

Cerror(103, _string_(path), 0);

#endif
        "),
    module!() := curmod)]

