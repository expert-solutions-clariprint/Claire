//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| function.cl                                                 |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+

// This file hold the methods that are defined by an external function
// and those that apply to a primitive type

// *********************************************************************
// *  Table of contents                                                *
// *   Part 1: Basics of pretty printing                               *
// *   Part 2: Methods for CLAIRE objects                              *
// *   Part 3: System Methods                                          *
// *   Part 4: Methods for Native entities                             *
// *********************************************************************


// we find here what is necessary for the minimal kernel of CLAIRE
// ==============================================================
!= :: operation(precedence = 60)
<< :: operation()
>> :: operation()
and :: operation()
or :: operation()
U :: operation(precedence = 50)
less? :: operation(precedence = 60, range = boolean)
& :: operation()
min :: operation(precedence = 20)
max :: operation(precedence = 20)
meet :: operation()
inherit? :: operation()


// @doc number
// returns the lowest integer
min(x:integer,y:integer) : integer -> (if (x <= y) x else y)
// @doc number
// returns the greatest integer
max(x:integer,y:integer) : integer -> (if (x <= y) y else x)
// @doc number
// returns the lowest float
min(x:float,y:float) : float -> (if (x <= y) x else y)
// @doc number
// returns the greatest float
max(x:float,y:float) : float -> (if (x <= y) y else x)


// *********************************************************************
// *   Part 1: Basics of pretty printing                               *
// *********************************************************************

cpstack :: property()

// we use a nice object
pretty_printer <: thing(cpretty:port,       	// a string port
                        cprevious:integer = 1,  // index of the current port in the stack 
                        index:integer = 0,      // indentation level
                        width:integer = 120,	    // size of window
                        pprint:boolean = false, // active
		                pbreak:boolean = false,
                        cpstack:list)           // support recursive print-in-string 


pretty :: pretty_printer()

apply_self_print :: property()
short_enough :: property()
print :: property()

// buffered print
// new in v3.3.26: unbounded recursion is supported :-)
// @doc Printing
// print_in_string() opens a new output port that will be stored as a string.
// The user is given access to the string at the end of the transcription, when the
// call to end_of_string() returns this string. print_in_string may be used recursively.
[print_in_string() : void
 -> let n := pretty.cprevious + 2,
 		pp := pretty.cpretty,
        p1 := port!(), //(if (n < length(pretty.cpstack)) (pretty.cpstack[n + 1] as buffer)
               //else port!()),
        p2 := use_as_output(p1) in
      (pretty.cprevious := n,
       pretty.cpretty := p1,
       if (pretty.cpstack = nil) pretty.cpstack := list<port>(pp, p2, p1)        // initialisation
       else (pretty.cpstack :add p2,
       		pretty.cpstack :add p1))]
       		//pretty.cpstack[n] := p2,
            // if (n = length(pretty.cpstack)) pretty.cpstack :add p1)) ]


;pretty.cprevious := use_as_output(pretty.cpretty),
;    if (pretty.cprevious = pretty.cpretty)
;     error("[123] YOU ARE USING PRINT_in_string_void RECURSIVELY") ]

// @doc Printing
// end_of_string() returns the string containing everything
// that has been printed since the last call to print_in_string().
[end_of_string() : string
  -> if (pretty.cprevious = 1) error("[123] unbalanced use of print-in-string"),
     let n := pretty.cprevious,
         s := string!(pretty.cpretty),
         op := (pretty.cpstack[n - 2]) as buffer,
         p := (pretty.cpstack[n - 1]) as port in
       (//set_length(pretty.cpretty, 0),
        use_as_output(p),
        rmlast(pretty.cpstack),
        rmlast(pretty.cpstack),
        fclose(pretty.cpretty), //<sb> v3.3.35 close the port !
        pretty.cpretty := op,
        pretty.cprevious :- 2,
        s)]

[buffer_length() : integer
  -> length(pretty.cpretty) ]


[buffer_set_length(i:integer) : void
  -> set_length(pretty.cpretty,i) ]

// a method for calling the printer without issuing a message
// here we assume that self_print is always defined as a function
[apply_self_print(self:any) : void
 -> (if (externC("(INTEGERP(self) ? CFALSE : CTRUE)", boolean) &
			externC("((self << ADDRTRANS) ? CFALSE : CTRUE)", boolean)) princ("<NULL>")
	else case self
      (table self_print(self), //<sb> add a special print@table
       thing princ(self.name),
       class princ(self.name),
       integer princ(self),
       string self_print(self),
       any let %prop := (self_print @ owner(self)) as method in
             (case self (exception set_color(31,0)),
             if (%prop & known?(functional, %prop))
                 let l := %prop.srange in
                   funcall(%prop.evaluate, (l[1] as class), self,
                           (l[2] as class))
              else try self_print(self)
                   catch any printf("<unprintable:~S (~S)>", owner(self), exception!()),
              case self (exception set_color(30,0)))))]

// some basic definitions
[self_print(self:any) : void
 ->  if (self = unknown) princ("unknown")
     else printf("<~S>", owner(self)) ]

[self_print(self:exception) : void
 ->  printf("<~S>", owner(self))]
	
[self_print(self:boolean) : void
 -> if self princ("true") else princ("false") ]

[self_print(self:function) : void -> printf("#'~A", string!(self)) ]


// prints the name of a restriction. If we have a close property and if a
// short-cut is possible, we use it.
self_print(self:restriction) : void
 -> (if (not(known?(selector, self)) | unknown?(domain, self))
        printf("<~S>", owner(self))
     else let p := self.selector,
              n := 0,
              c := domain!(self) in
            (for r in p.restrictions (if (domain!(r) = c) n :+ 1),
             printf("~A @ ~S", p.name, (if (n = 1) c else self.domain))))

// we are too far
much_too_far <: error()


// @doc Printing
// prints the entity x (x can be anything) on the current output (cout()).
print(x:any) : void
 -> (if (pretty.pbreak & pretty.pprint)
        let b_index := buffer_length(), missed := false, %l := pretty.index in
          (if not(short_enough(b_index + 10))
              (pretty.pprint := false, pretty.pbreak := false,
               print(x), pretty.pprint := true)
           else (try (pretty.pbreak := false,
                      apply_self_print(x),
                      pretty.pbreak := true)
                 catch much_too_far (missed := true),
               if missed (pretty.pprint := true, pretty.pbreak := true,
                          buffer_set_length(b_index),
                          pretty.index := %l,
                          apply_self_print(x))))
     else apply_self_print(x),
     unknown)

short_enough(self:integer) : boolean -> (self < pretty.width)


// *********************************************************************
// *   Part 2: Methods for CLAIRE objects                              *
// *********************************************************************

// the instantiation body is a sequence of words from which the initialization
// of the object must be built.
//  copied_def = object (for object) + float (for float) + integer (for all)
//               + NULL for objects
// v3.2.12: use a condition that is coherent with ClReflect.cl : a slot defaut value must be placed
// unless it is a copied_def
complete!(self:object) : object
 -> (for s:slot in self.isa.slots
       let p := s.selector,
           s2 := s.srange,
           d := get(default, s) in
         (if known?(d)
             let v := slot_get(self, s.index, s.srange) in
               (if (unknown?(v) & not(s2 = object | d % integer | s2 = float))   // v3.2.12 coherence
                   // was: (s2 = any & not(d % integer) & unknown?(v))
                   update(p, self, s.index, s.srange, d)
                else if (d = v)
                   (if (p.multivalued? != false) for y in d update+(p, self, y)
                    else update+(p, self, d)))),
     let m := (close @ owner(self)) in
       (case m (method funcall(m, self) as object,
                any self)))  // v3.0.41  obviously



//-------------------------- ENTITY   --------------------------------------


claire/kill! :: property()
// @doc class
// kill!(x) is more brutal than kill and deallocates without any checking. 
claire/kill!(self:any) : any -> function!(kill_I_any)

;object?(self:any) : boolean -> (if (self % object) true else false)
;Ftuple?(self:any) : boolean -> (if (self % tuple) true else false)

// @doc entity
// not(self) returns false for all entity except false, nil, the empty set and the empty list.
not(self:any) : boolean
  -> (if (self = true) false
      else if (self = false) true
      else if not(self) true
      else false)

// @doc entity
// this is the negation of (x = y).
!=(x:any,y:any) : boolean -> (if (x = y) false else true)

// gives the type of any object. This is open_coded.
// @doc entity
// owner(self) returns the class from which the object is an instance.
// If x is an object, then owner(x) = isa(x) = the unique class c such that
// x % instances(c).
// \code
// owner(12) -> integer
// owner("12") -> string
// owner(integer) -> class
// owner(integer U string) -> Union
// \/code
owner(self:any) : class -> owner(self)

// some useful methods
// @doc entity
// The general method known? simply returns true whenever the object exists in the database
// (i.e. false is returned if x is unknown vs. unknown?).
known?(self:any) : boolean -> (unknown != self)
// @doc entity
// The general method unknown? simply returns true if the entity is unknown in
// the database (vs. known?).
unknown?(self:any) : boolean -> (unknown = self)

// needed by the compiled code
check_in(self:any,y:type) : any
 -> (if (self % y) self
     else error("[124] the value ~S does not belong to the range ~S", self, y))

check_in(self:bag,c:class,y:type) : bag
 -> (if forall(z in self | z % y) cast!(self,y)
     else error("[124] the value ~S does not belong to subtype[~S]",self, y))

// new in v3.00.48
<(self:any,x:any) : boolean -> (if (self = x) false else (self <= x))
>(self:any,x:any) : boolean -> (if (self = x) false else (x <= self))
// >= is defined as a macro in file.cl


// ----------------------- CLASS ---------------------------------------------

// v3.2.14 recursively applies to subclasses
// @doc class
// declares a class as ephemeral: the member set is not maintained (ephemeral_object)
ephemeral(self:class) : any
  -> (for c in self.descendents
       (if (c.instances | c.open <= 1)
           error("[187] cannot declare ~S as ephemeral because of ~S",self,c)
        else put(open, c, system.ephemeral)))

// @doc class
// declares a class as an abtract class (without instances)
abstract(c:class) : any
 -> let n := c.open in
       (if (n = system.ephemeral) error("[125] ephemeral classes cannot be abstract")
        else (if (length(c.instances) != 0)
                 trace(3, "--- note: ~S already has some instances", c),
              if (n = 2) write(open, c, 0)
              else if (n = 1) write(open, c, -1)),
        c)

// @doc class
// declares a class as totally defined in the hierarchy: no new subclasses can be added.
final(c:class) : any
 -> let n := c.open in
       (if (n = 3) error("[126] ephemeral classes cannot be set as final")
        else if (n = 2) write(open, c, 1)
        else if (n = 0) write(open, c, -1),
        c)

// instantiation with and without a name
// @doc class
// new(self) creates an instance of the class self
new(self:class) : type[object glb member(self)]
  -> let o := (if (self.open <= 0) error("[105] cannot instantiate ~S", self),  // v3.2.44
               new!(self)) in
        (if (self.open != ephemeral()) add!(instances, self, o),                  // v3.2.34
         complete!(o))                                                          // v3.2.26
        
// @doc class
// new(self, %nom) creates a named instance of the class v (assumed to be a subclass of thing)
// with the name self
new(self:class, %nom:symbol) : type[thing glb member(self)]
   -> let o := (if (self.open <= 0) error("[105] cannot instantiate ~S", self),  // v3.2.44
                new!(self,%nom)) in
       (complete!(o) as thing)      // v3.2.26

// internal version
mClaire/new!(self:class) :  type[object glb member(self)]
  -> function!(new_object_class, NEW_ALLOC)
mClaire/new!(self:class,%nom:symbol) :  type[thing glb member(self)]
   -> function!(new_thing_class, NEW_ALLOC)

// the smallest super_set of two sets
// there is always any, so it always returns a class
meet(self:class,ens:class) : class
 -> (let l1 := self.ancestors,
         l2 := ens.ancestors,
         m := (if (length(l1) < length(l2)) length(l1) else length(l2)) in
       (while (l1[m] != l2[m]) m :- 1, l1[m] as class))

// fast inclusion method for lattice_sets (lattice order). The argument is
// either a lattice_set or {}
// @doc type
// inherit?(self, ens) returns (self % ancestors(ens)).
inherit?(self:class,ens:class) : boolean
 -> (let l := self.ancestors,
         n := length(ens.ancestors) in
       (n <= length(l) & l[n] = ens))


class!(s:symbol,c:class) : class -> function!(class_I_symbol,NEW_ALLOC)


//------------- PROPERTY ---------------------------------------------------

// the two methods to access open(r)
// an abstract property is extensible and can receive new restrictions
abstract(p:property) : any
 -> let n := p.open in
       (if (n < 2) error("[127] ~S can no longer become abstract", p)
        else write(open, p, 3),
        p)

// a final property is completely defined and cannot receive a new restriction
// v3.2.04: the new value 4 will be used to represent (compiled but open)
final(r:relation) : void
 -> (case r
      (property (if (r.open <= 2)
                   (write(open, r, 1),                  // v3.2.04
                    put(domain, r,
                        Uall(list{ x.domain[1] | x in r.restrictions})),
                    put(range, r,
                        Uall(list{ x.range | x in r.restrictions}))))))


//------------- MODULES   --------------------------------------------------

// the close function gives its right value to the *internal* slot that
// is the order of the module in the system. The name is supposed to be
// read in the system module.
close(self:module) : module
 -> (if (self != claire)
        (if known?(part_of, self)
            let sup := self.part_of in
              (parts(sup) :add self,
               for x in sup.uses
                 (if (not(x % self.uses) & x % module) uses(self) :add x))
         else trace(3, "---- note: ~S is a root module !\n", self)),
     self)

// note: dynamic modules are no longer supported
claire/get_symbol(m:module,self:string) : any -> function!(get_symbol_module)
claire/get_symbol(self:string) : any -> get_symbol(claire,self)

// *********************************************************************
// *   Part 3: System Methods                                          *
// *********************************************************************

// all these methods will be open-coded by the compiler
//get_stack(self:integer) : any -> get_stack(self)
//put_stack(self:integer,x:any) : any -> put_stack(self, x)
//push!(self:meta_system,x:any) : void -> push!(self, x)

// @doc Miscellaneous
// gc() forces a garbage collection to take place.
gc() : void -> function!(claire_gc)
// @doc date
// time_get() stops a clock started by time_set() it and returns the elapsed time in milliseconds.
time_get() : integer -> function!(time_get_void)
time_read() : integer -> function!(time_read_void)
// @doc date
// time_set() starts a clock that will have to be stopped with time_get().
time_set() : void -> function!(time_set_void)
// @doc date
// time_show pretty prints the current value of a timer started by time_set().
time_show() : void -> function!(time_show)
//stat() : void -> function!(claire_stat)
// @doc symbol
// gensym() generates randomly a new symbol. 
gensym(self:void) : symbol -> gensym("g")

// world management
store(l:list,n:integer,y:any) : any -> store(l,n,y,true)
store(l:array,n:integer,y:any) : any -> store(l,n,y,true)
commit(n:integer) : void -> (while (n < world?()) commit())
backtrack(n:integer) : void -> (while (n < world?()) backtrack())
claire/world+ :: choice
claire/world- :: backtrack
claire/world-! :: commit

// allows to change the storage class
store(l:listargs) : any
  -> (for r in l
         case r (relation r.store? := true,
                  string let v := get_value(r) in
                          case v (global_variable v.store? := true)))


//<sb> faulting interface
claire/preread :: property(open = 3)

preread(p:property, o:any) : void -> none

// *********************************************************************
// *   Part 4: Methods for Native entities                             *
// *********************************************************************

//------------------- STRING -----------------------------------------------
// @doc string
// returns the length of a string
length(self:string) : integer -> function!(length_string) //<sb> buffer

make_function(self:string) : function -> function!(make_function_string)
// @doc symbol
// symbol!(s) returns the symbol associated to s in the claire module. A new symbol is
// created if no such symbol exists.
symbol!(self:string) : symbol -> symbol!(self, claire)

;<=(s:string,s2:string) : boolean
; -> (let n := length(s),
;         m := length(s2) in
;       for i in (1 .. n)
;         (if (i > m) break(false),
;          if ((s[i] as integer) <= (s2[i] as integer))
;             (if (s[i] != s2[i]) break(true))
;          else break(false),
;          if (i = n) break(true)))

externC(s:string) : void -> error("cannot execute C code: ~A", s)
externC(s:string,c:class) : type[member(c)] -> error("cannot execute ~A",s)

nth_get(s:string,n:integer,max:integer) : char
  -> (if (n <= max) s[n] else error("Buffer string access"))
nth_put(s:string,n:integer,c:char,max:integer) : void
  -> (if (n <= max) s[n] := c  else error("Buffer string access"))

// @doc Miscellaneous
// Passes the command s to the operating system (the shell) and returns the
// exit status of the command execution.
shell(self:string) : integer -> function!(claire_shell)

// @doc Environment variables
// getenv(s) returns the value of the environment variable s if it
// exists and an empty string otherwise. 
claire/getenv(self:string) : string -> function!(getenv_string, NEW_ALLOC)
// @doc symbol
// returns the object whose name (in the default claire namespace)
// corresponds to the string s.
claire/get_value(self:string) : any -> function!(value_string)
// @doc symbol
// returns the object whose name (search from the namespace m)
// corresponds to the string s.
claire/get_value(self:module,s:string) : any -> function!(value_module)  //  v3.2.14

//------------------- SYMBOL -----------------------------------------------
// @doc symbol
// make_string(s) returns a string denoting the same identifier.
// If s is given in the qualified form (module/identifier), than the
// result will contain the name of the module ("module/identifier").
make_string(self:symbol) : string
 -> (print_in_string(), princ(self), end_of_string())
//princ(self:symbol) : any -> function!(princ_symbol)
self_print(self:symbol) : void -> printf("~A/~S", module!(self).name,string!(self))
//c_princ(self:symbol) : any -> function!(c_princ_symbol)
//gensym(self:string) : symbol -> function!(gensym_string, NEW_ALLOC)

//--------------------- INTEGER -----------------------------------------
// @doc number
// returns the sum of two integers
+(self:integer,x:integer) : type[abstract_type(+, self, x)] -> (self + x)
// @doc number
// returns the difference of two integers
-(self:integer,x:integer) : type[abstract_type(-, self, x)] -> (self - x)
//-(self:integer) : integer -> function!(ch_sign)

//float!(self:integer) : float -> function!(to_float)
//mod(self:integer,x:integer) : integer -> function!(mod_integer)
--?(self:integer,x:integer) : set -> function!(sequence_integer, NEW_ALLOC)
// @doc Miscellaneous
// exit(n) stops CLAIRE and returns to the hosting system the value n.
// What can happen next is platform-dependent.
exit(self:integer) : void -> function!(CL_exit)
//less_code(n:integer,i:integer) : boolean -> function!(less_code_integer)
// @doc number
// (x << n) is the result of shifting the integer x seen as a bitvector to the
// left by n positions.
<<(x:integer,n:integer) : integer -> externC("(x << n)",integer) // v3.3.16
// @doc number
// (x >> n) is the result of shifting the integer x seen as a bitvector to the
// right by n positions.
>>(x:integer,n:integer) : integer -> externC("(x >> n)",integer)
// @doc number
// and(x,y) returns the bitwise intersection of two integers (seen as bitvectors).
and(x:integer,y:integer) : integer -> externC("(x & y)",integer)
// @doc number
// or(x, y) returns the bitwise union of two integers (seen as bitvectors).
or(x:integer,y:integer) : integer -> externC("(x | y)",integer)

// open-coded
// @doc number
// returns true if x is lower than y
<(x:integer,y:integer) : boolean -> (if (x < y) true else false)
// @doc number
// returns true if x is lower or equal to y
<=(x:integer,y:integer) : boolean -> (if (x <= y) true else false)
// @doc number
// returns true if x is greater than y
>(x:integer,y:integer) : boolean -> (if (x > y) true else false)
nth(self:integer,y:integer) : boolean -> (if self[y] true else false)

// used by the logic
// @doc number
// factor?(x,y) returns true if x is a multiple of y.
factor?(x:integer,y:integer) : boolean -> ((x mod y) = 0)

// @doc number
// divide?(x,y) returns true if y is a multiple of x.
divide?(x:integer,y:integer) : boolean -> ((y mod x) = 0)
// @doc driving optimizations
// Id(x) returns x. Id has a special behavior when compiled which makes it useful.
// The argument is evaluated before being compiled. The intended use is with global
// variables: the compiler uses the actual value of the variable instead of a reference
// to the global variable. This is very convenient to introduce parameters that are defined
// outside the module that is being compiled. This is also used to tell compiler that an
// iteration should make explicit use of all iterations rule that may apply to some subclasses
// of the set expression being iterated.
Id(x:any) : type[x] -> x
pair :: operation()
pair(x:any,y:any) : list -> list(x, y)
pair_1(x:list) : type[member(x)] -> x[1]
pair_2(x:list) : type[member(x)] -> x[2]

//------------------------ FLOAT ---------------------------------------------
self_print(self:float) : void -> function!(print_float)
// @doc number
// returns the sum of two floats
+(self:float,x:float) : float -> (let y:float := (self + x) in y)
// @doc number
// returns the difference of two floats
-(self:float,x:float) : float -> (let y:float := (self - x) in y)
// @doc number
// returns the product of two floats
*(self:float,x:float) : float -> (let y:float := (self * x) in y)
// @doc number
// returns the division of two floats
/(self:float,x:float) : float -> (let y:float := (self / x) in y)
// @doc number
// returns the opposite of x (i.e. -1.0 * x)
-(x:float) : float -> (-1.0 * x)
// @doc number
// returns the square root of x. Returns an irrelevant value when x is strictly negative.
sqrt(self:float) : float -> (let y := sqrt(self) in y)
// @doc number
// (x ^ y) returns the y exponent of x.
^(self:float,x:float) : float
 -> (let y := 0.0 in (externC("y = pow(self,x)"), y))
// @doc number
// log(x) returns the value of the natural logarithm of argument x.
claire/log(x:float) : float 
 -> (let y := 0.0 in (externC("y = log(x)"), y))

// @doc number
// tan(self) computes the tangent of self (measured in radians).
claire/tan(self:float) : float
 -> (let y := 0.0 in (externC("y = tan(self)"), y))

// @doc number
// cos(self) computes the cosine of self (measured in radians).
claire/cos(self:float) : float
 -> (let y := 0.0 in (externC("y = cos(self)"), y))

// @doc number
// sin(self) computes the sine of self (measured in radians).
claire/sin(self:float) : float
 -> (let y := 0.0 in (externC("y = sin(self)"), y))

// @doc number
// acos(self) computes the principal value of the arc cosine of self
// in the range [0, pi].
claire/acos(self:float) : float
 -> (let y := 0.0 in (externC("y = acos(self)"), y))

// @doc number
// asin(self) computes the principal value of the arc sine of self in
// the range [-pi/2, +pi/2].
claire/asin(self:float) : float
 -> (let y := 0.0 in (externC("y = asin(self)"), y))

// @doc number
// atan(self) returns the principal value of the arc tangent of self in the
// range [-pi/2, +pi/2].
claire/atan(self:float) : float
 -> (let y := 0.0 in (externC("y = atan(self)"), y))

// @doc number
// tanh(self) computes the hyperbolic tangent of self.
claire/tanh(self:float) : float
 -> (let y := 0.0 in (externC("y = tanh(self)"), y))

// @doc number
// cosh(self) computes the hyperbolic cosine of self.
claire/cosh(self:float) : float
 -> (let y := 0.0 in (externC("y = cosh(self)"), y))

// @doc number
// sinh(self) computes the hyperbolic sine.
claire/sinh(self:float) : float
 -> (let y := 0.0 in (externC("y = sinh(self)"), y))

 
// @doc number
// make a new string from a float x.
string!(self:float) : string -> (print_in_string(), princ(self), end_of_string())

// @doc @xl char
// make a new string from a a char self. The returned string always has
// of length of 1. One could use make_string to create a string of a given
// length filled with a given char.
string!(self:char) : string -> make_string(1, self)

//--------- BAG --------------------------------------------------------
// @doc bag
// returns the length of a list. The length of a list is not its size !
length(self:bag) : integer -> length(self)

nth(self:bag,x:integer) : type[(if (self % tuple & unique?(x)) self[the(x)]   // v3.3.22
                                else member(self))]
 -> (if (x > 0 & x <= length(self)) self[x]
     else error("[41] nth[~S] out of scope for ~S", x, self))
nth_get(self:bag,x:integer) : any -> nth_get(self, x)

// @doc bag
// min(f,self) return the element of self that has the lowest
// value according to the ordering method f. For instance :
// \code
// min(< @ integer, list(1,2,3,2,1)) -> 1
// \/code
min(f:method,self:bag) : type[member(self)]     // v3.1.08
 -> (if (length(self) != 0)
        let x := self[1] in
                 (for y in self (if (funcall(f, y, x) as boolean) x := y), x)
     else error("[183] min of empty set is undefined"))

// @doc bag
// max(f,self) return the element of self that has the greatest
// value according to the ordering method f. For instance :
// \code
// max(< @ integer, list(1,2,3,2,1)) -> 3
// \/code
max(f:method,self:bag) : type[member(self)]     // v3.1.08
 -> (if (length(self) != 0)
        let x := self[1] in
                  (for y in self (if not(funcall(f, y, x)) x := y), x)
     else error("[183] max of empty set is undefined"))

// there seems to be a difficulty with providing this method with the proper type ..
;/+(x:bag,y:bag) : type[list[member(x) U member(y)]]
; -> let l := (case x (list copy(x), set list!(x), tuple list!(x))) as list in  // v3.00.10
;       (case y (list l :/+ y, bag for z in y l :add z), l)

// @doc bag
// x /+ y returns a new list that is the concatenation of the two bag contents.
/+(x:bag,y:bag) : list
 -> let l := (case x (list copy(x), set list!(x), tuple list!(x))) as list in  
   (for z in y l :add z,
   let %x := of(x),
       %y := of(y) in 
      (if (%x = %y) cast!(l,%x)
       else cast!(l,x.of U y.of)))

//--------- LIST --------------------------------------------------------
// last element of a list
// @doc bag
// last(l) returns l[length(l)]
last(self:list) : type[member(self)] 
  -> (if (length(self) > 0) self[length(self)] else error("[41] car(nil) is undefined"))
  
// remove the last element
// @doc bag
// removes the last element of the list self.
rmlast(self:list) : list  -> (nth-(self,length(self)), self)

// @doc bag
// nth=(l,i,x) replace the i\sup th\/sup element of the bag l by x.
// nth(l,i,x) is equivalent to l[i] := x.
nth=(self:list,x:integer,y:any) : any
  -> (if (x <= 0 | x > length(self)) error("[41] nth[~S] out of scope for ~S", x, self) // v3.3.24
      else if (y % of(self)) self[x] := y                                              // v3.0.38
      else system_error(index = 17,arg = y, value = self))                             // v3.2.00

// the old LISP method
// @doc bag
// Classical LISP methods that return the head of the list (e.g. l[1]).
// \code
// car(list(1,2,3)) -> 1
// car(list(3,2,1)) -> 3
// \/code
car(self:list) : any
 -> (if (length(self) > 0) self[1] else error("[41] car(nil) is undefined"))

// hashtable basics
[hashlist(n:integer) : list
 -> let l := make_list(n, unknown),
        u := ((nth_get(l, 0) as integer) - 3) in
       (for i in ((n + 1) .. u) l add unknown,
        l) ]

[hashsize(l:list) : integer
 -> let x := 0 in (for y in l (if (y != unknown) x :+ 1), x) ]

// @doc bag
// this method sorts the list self according to the ordering method f
sort(f:method,self:list) : list
 -> (quicksort(self, f, 1, length(self)), self)

// v3.0.38: upgrade the quicksort algorithm with a better pivot selection cf.bag.cpp
// this is also proposed as a macro: cf. file.cl
quicksort(self:list,f:method,n:integer,m:integer) : void
 -> (if (m > n)
        let x := self[n] in
          (if (m = (n + 1))
              (if (funcall(f, self[m], x) as boolean)
                  (self[n] := self[m], self[m] := x))
           else let p := (m + n) >> 1, q := n in   // new: p is pivot's position
                  (x := self[p],
                   if (p != n) self[p] := self[n],
                   for p in ((n + 1) .. m)
                     (if (funcall(f, self[p], x) as boolean)
                         (self[n] := self[p],
                          n := n + 1,
                          if (p > n) self[p] := self[n])),
                   self[n] := x,
                   quicksort(self, f, q, n - 1),
                   quicksort(self, f, n + 1, m))))

 // destructive method that build the powerset
build_powerset(self:list) : set
 -> (if (length(self) != 0)
        let x := self[1],
            l1 := build_powerset(self << 1),
            l2 := l1 in
          (for y:set in l1 l2 :add (set(x) /+ y), l2)
     else {{}})

// <<(x:list,y:integer) : list -> function!(skip_list) // v3.3.16

// @doc bag
// makes a tuple from a list
[tuple!(x:list) : tuple -> function!(tuple_I_list,NEW_ALLOC)]

// new and useful (v3.1.06)
claire/make_copy_list(n:integer,d:any) : list
  -> let l := make_list(n,d) in
       (case d (bag  for i in (1 .. n) l[i] := copy(d)),
        l)

//----------------------  SET  ---------------------------------------------
// @doc bag
// difference(s, t) returns the difference set s - t, that is the set of all elements of
// s which are not elements of t.
difference(self:set,x:set) : set -> { y in self | not(contain?(x, y))}

//--------- ARRAY --------------------------------------------------------

// @doc array
// nth=(a,i,x) replace the i\sup th\/sup element of the array a by x.
// nth(a,i,x) is equivalent to a[i] := x.
nth=(self:array,x:integer,y:any) : void
 -> (if not(y % of(self)) error("type mismatch for array update ~S, ~S",y,self)
     else if (x > 0 & x <= length(self)) nth_put(self,x,y)
     else error("nth[~S] out of scope for ~S", x, self))

self_print(self:array) : void -> printf("array<~S>[~A]",of(self),length(self))
 
//---------------------- CHAR --------------------------------------------
self_print(self:char) : void -> function!(print_char) //printf("'~A'", self)

// @doc char
// returns true if ASCII code of x is lower or equal to ASCII code of y
<=(c1:char,c2:char) : boolean -> (integer!(c1) <= integer!(c2))


// three methods that are useful for debugging !
Address(self:any) : integer -> function!(Address)

Oid(self:any) : string -> function!(Oid)
Oid~(self:string) : any -> function!(Oid_inv)


//<sb> imported from Reader/file.cl

// This is the good version of kill, the nasty one is dangerous ....
// these restrictions of kill explain the dependencies among objects
//

// @doc class
// kill(x) is used to remove an object from the database of the language.
// kill(x) does it properly, removing the object from all the relation
// network but without deallocating.
claire/kill(self:object) : any
 -> (case self (thing put(self.name, unknown)),
     write(instances, self.isa, self.isa.instances delete self),
     {})

// @doc class
// kill(x) is used to remove an object from the database of the language.
// kill(x) does it properly, removing the object from all the relation
// network but without deallocating.
claire/kill(self:class) : any
 -> (while self.instances kill(self.instances[1]),
     for x in self.descendents (if (x.superclass = self) kill(x)),
     kill@object(self))


// @doc string
// transforms a string into a float.
float!(self:string) : float
 -> let p := port!(self), 
 		neg := (if (p[1] = '-') (p[1] := '0', true)
				else if (p[1] = '+') (p[1] := '0', false)
				else false),
		x := (p.Core/firstc := integer!('0'),
 			externC("read_number_port(p)",any))
     in (fclose(p),
      		case x (float  (if neg -(x) else x),
      			integer (if neg -(float!(x)) else float!(x)),  // v3.3.22
                any error("[??] ~A is not a float",self)))


//<sb> @doc @xl Miscellaneous
// unix?() tell if the underlying system is a UNIX (vs. windows).
[unix?() : boolean ->
	externC("\n#ifdef CLPC\nCFALSE\n#else\nCTRUE\n#endif\n",boolean)]


claire/strffloat(f:string, d:float) : string ->
	(externC("char buf[1024]"),
	externC("sprintf(buf,f,d)"),
	copy(externC("buf",string)))

//<sb> @doc @xl Miscellaneous
// chroot(dirname) causes dirname to become the root directory, that
// is, the starting point for path searches of pathnames beginning with '/'.\br
// This call is restricted to the super-user.
[claire/chroot(dir:string) : void ->
	externC("
		#ifndef CLPC
		if (::chroot(dir) == -1)
			Cerrorno(74, _string_(\"chroot @ string\"), 0);
		#endif
	")]



//<sb> @doc @xl Process handling
// fork, when called in CLAIRE applies all existing on_fork
// with the domain void.
// the on_fork callback is applied just before the fork, that is
// the parent process only. For instance :
// \code
// on_fork() : void -> printf("attemp to fork...\n")
// \/code
claire/on_fork :: property(open = 3)

//<sb> @doc @xl Process handling
// after a fork, CLAIRE applies all existing on_forked
// restrictions that have the domain boolean.
// the on_forked callback is applied with true from the child and
// false from the parent process. For instance :
// \code
// on_forked(parent?:boolean) : void ->
// 		printf("just forked (~I)\n",
// 					(if parent? princ("parent")
// 					else printf("child ~S", getpid())))
// \/code
claire/on_forked :: property(open = 3)

// on_fork this is used by wcl in debug mode to build the report of
// its (sub)child(s) processes

//<sb> @doc @xl Process handling
// fork is the standard UNIX interface to create new processes.
// fork creates a child process that is an image of the current
// process that only differs by the returned value which is:
// \ul
// \li 0 for the parent process\n
// \li n > 0 for the child process where n is the process id of the child\n
// \/ul
// under win32 it produce a system error.
[claire/fork() : integer ->
	for r in on_fork.restrictions
		(if (length(r.domain) = 1 & r.domain[1] = void)
			apply(r, list(system))),
	let l := on_forked.restrictions, //<sb> cache the list of restriction
		i := Kernel/cfork()
	in (for r in l
			(if (length(r.domain) = 1 & r.domain[1] = boolean)
				apply(r, list(i = 0))),
		i)]

claire/forker?() : boolean -> (fork() != 0)
claire/forked?() : boolean -> (fork() = 0)




