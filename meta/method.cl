//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| method.cl                                                   |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file  object.cl: about()              |
//+-------------------------------------------------------------+

// This file contains the reflective description of the most primitive
// CLAIRE kernel: the embryo of the class hierarchy and a set of methods
// to read/write objects and to evaluate messages.

// *********************************************************************
// *  Table of contents                                                *
// *      Part 1: Lambda & Methods Evaluation                          *
// *      Part 2: Update methods                                       *
// *      Part 3: Management of definition(p)                          *
// *      Part 4: Matching Methods                                     *
// *********************************************************************

// *********************************************************************
// *      Part 1: Lambda & Methods Evaluation                          *
// *********************************************************************

// explicit definition
vars :: property()
dimension :: property()
claire/version :: property()

claire/ephemeral_object <: object()                            // a root
claire/lambda <: object(vars:list,body:any,dimension:integer)

(set_range(formula,method,lambda),
 ephemeral(ephemeral_object),
 final(method))

// explicit definition of the functions that are used in method [to avoid out_of-place
// implicit definitions]
execute :: property()
debug :: property()
eval_message :: property()
noeval_message :: property()
eval :: property()
call :: property()
self_eval :: property()
read :: property()
inlineok? :: property()
restore_state :: property()
hold? :: property()
write :: property()
range_is_wrong :: property()
update+ :: property()
update- :: property()
add_value :: property()
known? :: property()
unknown?  :: property()
erase :: property()
set_range  :: property()
put_store :: property()
matching? :: property()
vmatch?  :: property()
tmatch? :: property()
//find_which :: property() //<sb> moved in Kernel for hand-made optim
claire/main :: property()

undefined_debug :: property() //<sb> a value that is used to fill the stack

mClaire/index_jump(n:integer) : void ->
	externC("
		OID fill = _oid_(Core.undefined_debug);
		while (ClEnv->index <= n)
			ClEnv->stack[ClEnv->index++] = fill;
		ClEnv->index = n")

// the eval_message is a method that tells how to handle the message.
// it used to be distributed in CLAIRE (so that it was extensible) and each
// definition was called the behavior of a kind of restriction
// int? tells us if this is an interpreted message
eval_message(self:property,r:object,start:integer,int?:boolean) : any
 -> (externC("if (ClEnv->index + 100 >= ClAlloc->maxStack) error_execution_stack_full()"),
    if (r.isa = method)
       (if (system.debug! != -1) execute(r as method, start, int?)
        else let m:method := (r as method) in
          (if known?(formula, m)
            let retour := base!() in
              (set_base(start),
               stack_apply(m.formula.dimension),
               //<sb> fill stack with the defined property undefined_debug !
               // this ensures that the access to the variable is always defined
               // even if it hasn't been initialized yet
               let val := eval(m.formula.body) in
                  (set_base(retour),                   // to change ....
                   set_index(start),
                   val))
           else stack_apply(m.evaluate, m.srange, start, index!())))
    else if ( owner(r) = slot & index!() = (start + 1))
               let val := get(r as slot, get_stack(start) as object) in
                 (if (unknown?(val) & not(val % range(r as slot)))
                     read_slot_error(arg = get_stack(start), wrong = self),
                  set_index(start),
                  val)
    else noeval_message(self,start))


noeval_message(self:property, start:integer) : any
  -> let l := get_args(start) in
       (selector_error(selector = self, args = l),
        nil)


// a generic method : same as previously but (1) can be called by other methods
// and (2) takes care of the debugging piece, which implies a slower run (GC)
//<sb> changed debug handling
execute(self:method,start:integer,int?:boolean) : any
 -> (let val := unknown,
         n := length(self.domain) in
       (if known?(formula, self)
           let retour := base!() in
             (set_base(start),
              stack_apply(self.formula.dimension),
              val := (eval(self.formula.body) as integer),   // do not protect ...
              set_base(retour),
              set_index(start),
              if not(val % self.range)     // v3.2.01 
                 range_error(cause = self, arg = val, wrong = self.range), 
              val)
        else let i := index!() in
               (val := stack_apply(self.evaluate, self.srange, start, i),
                if not(val % self.range)    // v3.2.01
                   range_error(cause = self, arg = val, wrong = self.range), 
                val)))

// the evaluator is open coded
eval(self:any) : any -> eval(self)

// this is the standard evaluation
self_eval(self:object) : any -> self

// evaluation for a list or enumeration
(let f := function!(self_eval_ClaireObject) in
  for x in class.instances put(Kernel/evaluate, x as class, f))

// reads an inline definition for a method
[inlineok?(self:method,s:string) : method
 -> try let p := read,
            l := call(p, s) in
        (self.inline? := true, self.formula := l)
     catch any trace(0,"`RED---- WARNING: inline definition of ~S is wrong\n", self),
     self ]


// ****************************************************************
// *    Part 2: Update methods                                    *
// ****************************************************************

//get/put for a slot: should be inline
// @doc class
// get(s,x) returns the value of x associated with slot s
get(s:slot,x:object) : any -> slot_get(x, s.index, s.srange)
put(s:slot,x:object,y:any) : any
 -> store(x, s.index, s.srange, y, s.selector.store?)

// reading a value from a property (unknown is allowed)
// @doc class
// get(self,x) is equivalent to self(x), but without any verification on unknown.
get(self:property,x:object) : any
 -> (let s := (self @ owner(x)) in
       case s (slot slot_get(x, s.index, s.srange), any unknown))

// a more general value that is useful for types
funcall(self:property,x:any) : any
 -> (let s := (self @ owner(x)) in
       case s (slot slot_get(x as object, s.index, s.srange),
               method funcall(s,x),
               any unknown))

// reading a value from a property (unknown is not allowed)
// @doc class
// read(self,x) is strictly equivalent to self(x) : it reads the value and raises an
// exception if it is unknown.
read(self:property,x:object) : any
 -> (let s := (self @ owner(x)) in
       case s
        (slot let z := slot_get(x, s.index, s.srange) in
                (if (known?(z) | z % s.range) z
                 else read_slot_error(arg = x, wrong = self)),
         any read_slot_error(arg = x, wrong = self)))

// verifying
hold?(self:property,x:object,y:any) : boolean
 -> (let s := (self @ owner(x)) in
       case s
        (slot let z := slot_get(x, s.index, s.srange) in
                case z (set contain?(z, y), any y = z),
         any false))

// writing a single value into a slot & trigger rules
//  write = check + put + put_inverse + propagate
//  if_write = put + put_inverse + propagate  (propagate => if_write)
//  update = put + put_inverse
// @doc class
// This method is used to store a value in a slot of an object. write(p, x, y)
// is equivalent to p(x) := y.
write(self:property,x:object,y:any) : void
 -> (let s := (self @ owner(x)) in
       case s
        (slot (if not(y % s.range) range_is_wrong(s, y)
              else if (self.open < 1 &
                       known?(slot_get(x, s.index, s.srange)))
                 error("[132] Cannot change ~S(~S)", self, x)
              else if (known?(if_write,self) & not(multi?(self))) 
                 fastcall(self,x,y)
              else update(self, x, s.index, s.srange, y)),
         any selector_error(selector = self, args = list(x))),
     y)

// the value does not belong to the range: error!
range_is_wrong(self:slot,y:any) : any
 -> range_error(cause = self, arg = y, wrong = self.range)

// to remove
[put(p:property,x:object,n:integer,s:class,y:any) : void
 -> //[0] are you still using this dead thing (put instead of update) ??? !! //,
    update(p,x,n,s,y) ]

// update (method called by the compiler)     // v3.0.20: renamed from put !
// update = put + put_inverse  (complex links)
// update uses two satellite methods: update+ and update-
update(p:property,x:object,n:integer,s:class,y:any) : void
 -> let old := slot_get(x, n, s) in
       (if (p.multivalued? != false)
           (if (length(old) > 0)
               let v := (if (p.multivalued? = true) set() else list()) in
                 (if (of(old) != void) cast!(v,of(old)),
                  store(x, n, s, v, p.store?)),
            when r := get(inverse, p) in for z in (old as bag) update-(r, z, x),
            for z in (y as set) add!(p, x, n, z))
        else if (old != y)
           (when r := get(inverse, p) in
                (if (known?(old) & (r != p | x != old)) update-(r, old, x)),
            store(x, n, s, y, p.store?),
            update+(p, x, y)),
        y)

// this method checks the correctness of the inverse from a global view.
update+(self:relation,x:any,y:any) : void
 -> let r := self.inverse in
       (if (known?(r) & (r != self | x != y))
           (case r
             (property let s := (r @ owner(y)) in
                         case s
                          (slot
                             let old_y := get(s, (y as object)) in
                               (if (r.multivalued? != false)
                                   add_value(r, (y as object), s.index, old_y, x)
                                else store(y, s.index, s.srange, x, r.store?)),
                           any error("[133] Inversion of ~S(~S,~S) impossible", self, x, y)),
              table let old_y := get(r,y),
                        i := get_index(r, y) in
                      (if (r.multivalued? != false) add_value(r, i, old_y, x)
                       else (if known?(old_y) update-(self, old_y, y),
                             store(r.graph, i, x, r.store?))))))

// this methods deletes a value in the inverse of a global_relation
update-(r:relation,x:any,y:any) : void
 -> (case r
      (property let s := (r @ owner(x)) in
                  case s
                   (slot let l := get(s, x),
                             v := (case l
                                    (bag (if r.store? copy(l) else l) delete y,
                                     any  unknown)) in
                           put(s, x, v)),
       table let l := get(r,x), i := get_index(r, x),
                 v := (case l (bag (if r.store? copy(l) else l) delete y,
                               any unknown)) in
               store(r.graph, i, v, r.store?)))

// this methods adds a value to a multi-slot (used by the compiler)
// this is the multi-valued equivalent of update
[add!(self:property,x:object,n:integer,y:any) : void
 -> if known?(if_write,self) fastcall(self,x,y)
    else let l1 := (slot_get(x, n, object) as bag) in
       (if add_value(self, x, n, l1, y) update+(self, x, y)) ]


// this methods adds a value to a multi-slot (internal form)
// this is the multi-valued equivalent of put
[add_value(self:property,x:object,n:integer,l:bag,y:any) : boolean
 -> case l
      (set (if not(y % l)
              let l1 := (add!@set((if self.store? copy(l) else l), y)) in
                (store(x, n, object, l1, self.store?), true)
            else false),
       list (if self.store? store(l, y) else add!@list(l, y), true),
       any false) ]

// same method with error checking
// @doc class
// add(self,x,y) is equivalent to self(x) :add y
// (This form is interesting when one wants to write such an expression for a variable self)
[add(self:property,x:object,y:any) : void
 -> let s := (self @ owner(x)) in
       (if not(s) selector_error(selector = self, args = list(x))
        else if not(multi?(self)) error("[134] Cannot apply add to ~S", self)
        else if (y % member((s as slot).range))
          (if known?(if_write,self) fastcall(self,x,y)
           else add!(self, x, (s as slot).index, y))
        else range_is_wrong((s as slot), y)),
     y ]

// known ?
// @doc class
// known?(p, x) is equivalent to get(p, x) != unknown
known?(self:property,x:object) : boolean
 -> (let s := (self @ owner(x)) in
       case s (slot slot_get(x, s.index, s.srange) != unknown, any false))
// @doc class
// unknown?(p, x) is equivalent to get(p, x) = unknown
unknown?(self:property,x:object) : boolean
 -> (let s := (self @ owner(x)) in
       case s (slot slot_get(x, s.index, s.srange) = unknown, any true))

// delete takes care of the inverse also
// @doc class
// delete(s, x) returns s if x is not in the list (resp. set) s without x otherwise.
delete(self:property,x:object,y:any) : any
 -> (let s := (self @ owner(x)) in
       (if not(s) selector_error(selector = self, args = list(x))
        else let l1 := (slot_get(x, (s as slot).index, object) as bag),
                 l := ((if self.store? copy(l1) else l1) delete y) in
               (store(x, (s as slot).index, object, l, self.store?),
                let r := self.inverse in (if known?(r) update-(r, y, x)),
                l)))

// erase is similar for mono-valued properties takes care of the inverse also
// v3.2.22: take care of multi-valued slot as well
// @doc class
// erase(p, x) removes the value associated to x with the property p.
// The default value, or the unknown value, is placed in the slot x.p,
// and the inverse if updated (if any).
erase(self:property,x:object) : any
 -> let s := (self @ owner(x)) in
       (if not(s) selector_error(selector = self, args = list(x))
        else let y := slot_get(x, (s as slot).index, s.srange) in
               (if (self.multivalued? != false)
                   (when r := get(inverse,self) in for y1 in y update-(r,y1,x),
                    let l := shrink((if self.store? copy(y) else y),0) in
                      (store(x, (s as slot).index, object, l, self.store?),
                       l))
                else (store(x, (s as slot).index, s.srange, default(s), self.store?),
                      let r := self.inverse in (if (known?(r) & known?(y)) update-(r, y, x)),
                      default(s))))



[set_range(p:property,c:class,r:type) : void
 -> let s := ((p @ c) as slot) in
       (s.range := r,
        s.srange := sort!@type(r)) ]

// no longer needed because changing the range is not changing the prototype ?
// we should rather generate an error if the condition for dealing with
// defaults changes (TODO)
//        if (s.srange != any & s.srange != integer)
//           c.prototype[s.index] := 0))

// this method allows to bypass the storage mechanism - to be optimized ..
// @doc world
// put_store(r,x,v,b) is equivalent to put(r,x,v) but also stores this update
// in the current world if b is true. The difference with the use of the
// statement store(p) is that put_store allows the user to control precisely
// which update should be backtracked.
put_store(self:property,x:object,y:any,b:boolean) : void
 -> let s := (self @ owner(x)) in
      (case s
        (slot let z := slot_get(x, s.index, s.srange) in
                   (if (z != y) store(x, s.index, s.srange, y, b)),     // v3.2.04 same behavior compiled/interpreted !
         any selector_error(selector = self, args = list(x))))


// tells if we have a multivalued relation
multi? :: property()
[multi?(x:any) : boolean
  -> case x (relation (x.multivalued? != false), any false) ]

// new: (v3.0) we have a simpler management of demons thus fastcall can be
// written in CLAIRE. A demon is either a lambda or a function, which
// arguments have precise sorts that match the relation sort
// the demon does everything: put + inverse + propagation
// thus write(R,x,y) <=> fastcall(R,x,y) <=> f(x,y)
fastcall(r:relation,x:any,y:any) : void
 -> let f := r.if_write in
      (if (f % lambda) funcall(f as lambda, x , y)
       else let c1 := sort!(r.domain), c2 := sort!(r.range) in
               funcall((f as function),c1,x,c2,y,void))



// *********************************************************************
// *   Part 3: Management of definition(p)                             *
// *********************************************************************
join :: operation()


// the dictionarty slot

// insertion in the definition tree
insert_definition(p:property,r:restriction) : void
 -> (// if (verbose() = 4) //[0] insert ~S into ~S // p,r,
     put(definition, p,
         initialize(r, class!(r.domain[1]), p.definition)))


// insert a restriction with class-domain d into a property p
initialize(x:restriction,d:class,l:list) : list
 -> let p := x.selector, ix := p.mClaire/dispatcher in
       (if (length(p.restrictions) = 5 & uniform(p))
           // dictionary = true means uniform => restrictions are stored in c.dictionary
           (for r in p.restrictions hashinsert(r),
            p.dictionary := true),
        if p.dictionary
           (if uniform(x) (if (verbose() = 4) //[0] --- hashinsert ~S // x,
                           hashinsert(x))
            else (// printf("// ---- note: ~S is not uniform because of ~S \n", p, x),  // not necessarily a bug :-)
                  p.dictionary := false)),
        if (ix > 0 & (case x (method known?(evaluate,x))))
           let c := domain!(x) in
             (if (uniform(p) & c inherit? object)
                for c2 in c.descendents
                 (while (length(c2.mClaire/dispatcher as list) < ix)
                     add(c2.mClaire/dispatcher as list, 0),
                  if forall(y in (p.restrictions but x) |
                             (let c3 := domain!(y) in not(c2 inherit? c3 & c3 inherit? c)))
                    (c2.mClaire/dispatcher as list)[ix] := x.evaluate)
              else error("Cannot create a non-uniform restriction ~S of interface ~S",
                         x,p)),
        initialize(x, l))

// only uniform properties can use the dictionary representation
uniform(x:restriction) : boolean
 -> let l := x.domain,
         n := length(l) in
       forall(r in x.selector.restrictions |
         let l2 := r.domain in
           (l[1] % class & length(l2) = n &
            (forall(i in (2 .. n) | 
                    (l[i] = l2[i] |                   // v3.3.34
                     (owner(l[i]) != class &          // introduce a protected call to =type !
                      owner(l[i]) = owner(l2[i]) & l[i] =type? l2[i]))))))    // v3.3.36      

// v3.0.54 check that a uniform property only uses methods !
uniform(p:property) : boolean
  -> (forall(x in p.restrictions | x % method) & p.restrictions & uniform(p.restrictions[1])) //<sb> add test on p.restrictions

// insert a restriction in a list with the good order
[initialize(x:restriction,l:list) : list
 -> let l1:list := nil in                       // no updates on nil
       (for i in (1 .. length(l))
          let l2 := (l[i] as restriction).domain in
            (if tmatch?(x.domain, l2)
                (if tmatch?(l2, x.domain)
                    (l[i] := x, l1 := l, break(true))
                 else (l1 := nth+(l, i, x), break(true)))
             else if (not(tmatch?(l2, x.domain)) & x.domain join l2)
                trace(2, ("`BLUE---- Warning: ~S and ~S are conflicting\n"), l[1], x)),
        if (length(l1) != 0) l1
        else add!(l, x)) ]

// definition of dictionary: standart hash-table
[hashinsert(m:restriction) : any
 -> // if (verbose() = 4) //[0] hashinsert(~S) // m,
    let c := (domain!(m) as class) in
       for c2 in c.descendents hashinsert(c2, (m as method)) ]

[hashinsert(c:class,x:method) : any
 -> if not(c.dictionary) c.dictionary := hashlist(29),
    // if (verbose() = 4) //[0] hashinsert(~S) into ~S // x,c,
    c.dictionary := hashinsert(c.dictionary, x) as list,
    c.dictionary ]

// v3.3.06: returns the new hash list when x is inserted (not necessarily the same list since l may grow)
hashinsert(l:list,x:method) : any
 -> let p := x.selector,
        i := hash(l, p),
        m := length(l) in
       (while true
         let li := l[i]
         in (if (li = unknown | (li as method).selector = p)
             (if (li = unknown | domain!(x) inherit? domain!((li as method)))
                 l[i] := x,
              break(l))
          else if (i = m)
             (if ((hashsize(l) * 3) > (length(l) * 2))
                 let myl2 := hashgrow(l, hashinsert) in
                   break(hashinsert(myl2, x))
              else i := 1)
          else i :+ 1))

[hashget(c:class,p:property) : object
 -> let l := c.dictionary,
         i := hash(l, p),
         m := length(l) in
       ((while true
         let x := l[i]
         in (if (x = unknown) break(false)
          else if ((x as method).selector = p) break(x)
          else if (i = m) i := 1
          else i :+ 1)) as object) ]

// look if two signature have a non-empty intersection
// note that the first case with classes is necessary for bootstraping
[join(x:list,y:list) : boolean
 -> let n := length(x) in
       (n = length(y) &
        forall(i in (1 .. n) |class!(x[i] as type) join class!(y[i] as type)) &
        forall(i in (1 .. n) | x[i] glb y[i])) ]

// *********************************************************************
// *      Part 3: Matching Methods                                     *
// *********************************************************************

// find the correct restrictions to be applied on a given set
// This is also optimized because it is very useful (it returns false if none is found)
[@(self:property,x:class) : object
 ->  if self.dictionary hashget(x, self)
     else let rx := some(r in self.definition |
                          (x inherit? class!(r.domain[1]))) in
       (if known?(rx) rx else false) ]


// finds a property through its full domain
[@(self:property,lt:list) : object
 ->  let rx := some(r in self.definition | tmatch?(lt, r.domain)) in
       (if known?(rx) rx else false) ]


// method's pattern matching
matching?(l:list,n:integer,m:integer) : boolean
 -> (let x := (m - n), z := length(l) in
       (if (z = x & l[x] != listargs)
           not((for i in (1 .. x)
                  let y := ((n - 1) + i),
                      u := l[i] in
                    (if (if (owner(u) = class)
                         not(owner(get_stack(y)) inherit? (u as class))
                      else not(vmatch?(u, get_stack(y), n))) break(true))))
        else if (last(l) = listargs & x >= z - 1)   // v3.2.24
           not((for i in (1 .. z)
                  let y := ((n - 1) + i) in
                    (if (l[i] = listargs)
                        (put_stack(y, get_args(y)),
                         set_index(y + 1),
                         break(false))
                     else if not(vmatch?(l[i], get_stack(y), n))
                        break(true))))
        else false))

// type's pattern matching
// v3.0.65: use %type for Param
[vmatch?(t:any,x:any,n:integer) : boolean
 -> case t
      (class owner(x) inherit? t,
       set contain?(t, x),
       subtype ((if (t.arg = subtype) x % type else x % t.arg) &
                 (x as type) <=t  t.t1),
       Param (vmatch?(t.arg, x, n) &
              forall(i in (1 .. length(t.params)) |
                      let %t := t.args[i], %v :=  funcall((t.params[i] as property),x) in
                         (if (%t % set) %type(%v,%t) else vmatch?(%t, %v, n)))),
       Reference let v := get(t, get_stack(n + t.index)) in
                   (if t.arg x = v else x % v),
       tuple case x
             (tuple (length(t) = length(x) &
                     forall( i in (1 .. length(x)) | vmatch?(t[i], x[i], n))),
              any false),
       any x % t) ]

// method's pattern matching based on types (i.e. l2 is another list
// of types).
tmatch?(l:list,l2:list) : boolean
 -> (let x := length(l2), z := length(l) in
       (if (z != x & (l2[x] != listargs | z < x - 1)) false           // v3.2.24
        else not((for i in (1 .. x)
                    (if (i = x & l2[i] = listargs) break(false)
                     else if not(tmatch?(l[i], l2[i], l)) break(true))))))

// types pattern matching (t is the variable and t2 the pattern)
// note that less is redefinable
[tmatch?(t:any,t2:any,l:list) : boolean
 -> if not(t % type) //<sb> sometimes t is given as a type var !
 		(//[0] Warning: tmatch?(~S,~S,~S), ~S is not a type\n // t,t2,l,t,
 		false)
    else case t2
      (class case t (class t inherit? t2,
					any let ty1 := (t as type), ty2 := (t2 as type)
						in ty1 <=t ty2), //<sb> local vars ty1/ty2 help fcall to occur...
       subtype ((if (t2.arg = subtype) ((t as type) <=t type)
                 else tmatch?(t, t2.arg, l)) &
                tmatch?(member(t), t2.t1, l)),
       Param (tmatch?(t, t2.arg, l) &
              forall( i in (1 .. length(t2.params)) |
                      tmatch?((t as type) @ (t2.params[i] as property),
                                t2.args[i], l))),
       Reference (if t2.arg false
                  else (//[5] question is ~S less than ~S ? // t,t2,
                        (t as type) <=t @(t2, t2.args, l[t2.index + 1]))),  // how could we
       tuple case t
             (tuple (length(t2) = length(t) &
                     forall(i in (1 .. length(t2)) |
                            tmatch?(t[i], t2[i], l))),
              any false),
       any ((t as type) <=t (t2 as type)))  ]

// find the restriction
/*[find_which(p:property,n:integer,c:class) : object
 -> (if p.dictionary hashget(c, p) // v3.2.58  was ... (length(p.dictionary) != 0) hashget(c, p)
     else for r:restriction in p.definition
            (if matching?(r.domain, n, index!()) break(r))) as object]
*/
[find_which(l:list,c:class,n:integer,m:integer) : object
 -> (for r:restriction in l (if matching?(r.domain, n, m) break(r))) as object]

// special version for super
[find_which(c:class,l:list,n:integer,m:integer) : object
 -> (for r:restriction in l
       (if (c <=t r.domain[1] & matching?(r.domain, n, m)) break(r))) as object]



