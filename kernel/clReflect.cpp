/***********************************************************************/
/**   microCLAIRE                                       Yves Caseau    */
/**   clReflect.cpp                                                    */
/**  Copyright (C) 1998-2003 Yves Caseau. All Rights Reserved.         */
/**  cf claire.h                                                       */
/***********************************************************************/

#include <claire.h>
#include <Kernel.h>
#include <marie.h>

// ----------------------------------------------------------------------------
// this file contains the methods for reflective objects (and classes)
// it uses a set of external functions that are defined in System (claire code)
// ----------------------------------------------------------------------------

/*********************************************************************/
/** Contents                                                         */
/**    1. Objects                                                    */
/**    2. Class                                                      */
/**    3. Properties                                                 */
/**    4. Tables                                                     */
/*********************************************************************/


/*********************************************************************/
/**    1. Objects                                                    */
/*********************************************************************/

// v3.2.24: was awfully slow -> introduce a direct link to member? method
ClaireBoolean *ClaireCollection::contains(OID oself)
{ if (isa == Kernel._class)
     return (INHERIT(OWNER(oself),((ClaireClass *) this)) ? CTRUE : CFALSE);
  else if (isa == Kernel._list) return contain_ask_list((list *) this, oself);
  else if (isa == Kernel._set) return contain_ask_set((set *) this, oself);
  else {method  *m = OBJECT(method, (*Kernel.member_ask->definition)[1]);
        return ( (ClaireBoolean*)
                 ( ((fptr2) (m->functional->value))(oself, (CL_INT) this)));  }}

// ---------------------- API functions ----------------------------------------

// copy an object (or an item) */
ClaireObject *copy_object(ClaireObject *x)
{CL_INT i,m = *SLOTADR(x,0);
 ClaireObject *y = (ClaireObject *) ClAlloc->makeAny(m);
 for (i = 1; i<= m; i++) *SLOTADR(y,i) = *SLOTADR(x,i);
 return y;}

// logical equality
ClaireBoolean *equal(OID n, OID m)
{  if (n == m) return CTRUE;
   else if (IDENTIFIED(n) || IDENTIFIED(m)) return CFALSE;
   else {ClaireAny *x = OBJECT(ClaireAny,n);
         ClaireAny *y = OBJECT(ClaireAny,m);
         ClaireClass *sx = x->isa;
         if (sx != y->isa) return CFALSE;
         else if (sx == Kernel._list || sx == Kernel._tuple)
            return((list *) x)->equalList((list *) y);
         else if (sx == Kernel._set) return((set *) x)->equalSet((set *) y);
         else if (sx == Kernel._string) return equal_string(string_v(n),string_v(m));
         else if (sx == Kernel._float)
             {if (((ClaireFloat *) x)->value == ((ClaireFloat *) y)->value) return CTRUE;
              else return CFALSE;}
         else {if (((ClaireImport *) x)->value == ((ClaireImport *) y)->value) return CTRUE;
               else return CFALSE;}}}

// reading a value in a slot
// new in v2.5: floats
OID slot_get_object(ClaireObject *x, CL_INT y, ClaireClass *s)
{if (s == Kernel._float)
    {return _float_(*( (double *) SLOTADR(x,y) )); }
 else {CL_INT z = *SLOTADR(x,y);
        if (ClEnv->verbose > 10) printf("read slot[%d] of %d -> %d\n",y,x,z);
        return ((z == 0) ? (((s == Kernel._integer) || (s == Kernel._any)) ? 0 : CNULL) :
                 ((z == CNULL) ? CNULL : CLAIREOID(z,s)));}}

// membership for any collection
ClaireBoolean *belong_to(OID oself, OID ens)
{ ClaireClass *c = OWNER(ens);
   if (c == Kernel._integer)
       return ((oself >= 1 && oself <= 29 && BCONTAIN(ens,oself)) ? CTRUE : CFALSE);
   else if (c == Kernel._array) return contain_ask_array(array_v(ens),oself);
   else return OBJECT(ClaireCollection,ens)->contains(oself);}

// hashing for a generic list of length 2^n - 2
CL_INT hash_list(list *l, OID x)
{CL_INT i = ClRes->hashOid(l->content[0] - 1,x);
   if (i < l->length) return (i + 1);
   else return (1 + (i % l->length));}

//convert anything into a Boolean
ClaireBoolean *boolean_I_ClaireAny(ClaireAny *x)
 {if (x->isa == Kernel._boolean) return (ClaireBoolean *) x;
  else if (x->isa == Kernel._set || x->isa == Kernel._list)
      return ( (((list *) x)->length != 0) ? CTRUE : CFALSE);
  else if (x == CFALSE) return CFALSE;     // to remove later on
  else return CTRUE;}

ClaireBoolean *boolean_I_any(OID n)
 { if ((INT_MASK & n) != OBJ_CODE) return CTRUE;
   else return boolean_I_ClaireAny(OBJECT(ClaireAny,n)); }


// ---- three debugging functions which are quite useful ------------------------------------
CL_INT CL_Address(OID x) {return ADR(x);}

char *CL_Oid(OID x)
{char *s = make_string_integer(15,ClRes->ascii[32]);
  CL_INT n = sprintf(s,"%u",x);
  *((CL_INT*)s - 1) = n;
  return s;}

OID CL_Oid_inv(char *s)
{OID x; sscanf(s,"%u",&x); return x;}

/*********************************************************************/
/**    2. Class                                                      */
/*********************************************************************/




// new in v3.1.16: float alignment parity is an option
// for 99% of C++ compilers, float slots need to be aligned (even)
// so the C++ compiler wastes memory if needed
//<sb> some architecture may need structure alignment and/or field alignment
class align_struct : ClaireObject {double d;};
class align_field : ClaireObject {CL_INT pad1; CL_INT pad2; double d;};

#define ALIGN_STRUCT (sizeof(class align_struct) != sizeof(double) + sizeof(CL_INT))
#define ALIGN_FIELD (sizeof(class align_field) != sizeof(double) + 3 * sizeof(CL_INT))

// this first constructor works with no environment and is used to create the
// first classes
ClaireClass *ClaireClass::make(ClaireAny *x)
{ClaireClass *c = (ClaireClass *) x;
   if (ClEnv->verbose > 11) printf("=== class::make allocates a class @ %x \n",(CL_INT) c);
   c->ancestors = list::empty();
   c->slots = list::empty();
   c->instances = list::empty();
   c->subclass = set::empty();
   c->isa = Kernel._class;
   c->evaluate = (ClaireFunction *) NULL;        // will be setup later
   c->open = 2;
   c->params = list::empty();
   c->dictionary = list::empty();
   c->dispatcher = list::empty();
   c->ident_ask = CTRUE;
   c->if_write = CNULL;
   c->comment = "";
   return c;
   }

// same with a name
ClaireClass *ClaireClass::make(char *n)
{ClaireClass *c = make( ClAlloc->makeStatic(sizeof(ClaireClass) / 4)) ;
 symbol *s = symbol::make(n,claire.it,ClEnv->module_I);
 s->value = _oid_(c);
 c->name = s;
 c->comment = n;
 c->if_write = CNULL;
 Kernel._class->instances->addFast(_oid_(c));
 return c;}


// this is the regular constructor
// open(p) = 0 <=> read only, 1 <=> compiled (cannot be overwritten)
//           2 <=> default (unknown), 3 <=> open (extensible)
//           -1 : system property that may be overwritten  (v3.2.24)
// V3.2 PATCH : final(p) => open(p) = 0 because we allow overwriting open=1 properties !
// open(c) = -2 <=> system_set, -1 <=> no changes !
//           0  <=> no more instance, 1 <=> no new subclasses
//           2 <=> default, 3 <=>open
//           4 <=> ephemeral
ClaireClass *ClaireClass::make(char *name, ClaireClass *c2, module *def)
{ClaireClass *c = (ClaireClass *) Kernel._class->instantiate(name,def);
   c->comment = name;
   c->superclass = c2;
   c->slots = (list *) copy_bag(c2->slots);
   if (c2->open == ClEnv->ephemeral) c->open = ClEnv->ephemeral;
   c->prototype = (list *) copy_bag(c2->prototype),
   c->evaluate = c2->evaluate;
   c->if_write = CNULL;
   c->genealogy();
//   if (c->code == 0) c->encode();
   c->dictionary = (list *) copy_bag(c2->dictionary);
   c->dispatcher = (list *) copy_bag(c2->dispatcher);
   return c;}

// instantiation methods from simple to more complex
ClaireObject *ClaireClass::instantiate(CL_INT n)
{ClaireObject *o = (ClaireObject *) ClAlloc->makeAny(n);
 o->isa = this;
 return o;}

// here we use the prototype list as the pattern
// note: the prototype only contains things that can be copied directly !!!
// in 2.9 we extend this to floats (need to skip the index count: +2)
//     copied_defaults = object (for object) + float (for float) + integer (for anything)
//                       + NULL for objects
// IMPORTANT: do not put a float or an object in the prototype if the range is ANY !!!
//            because an object in prototype means a slot of srange object
//            CNULL means please put 0 (object representation)
//            Nodefault means please put CNULL (OID representation)
// v3.2.52: there is no alighnment problem here IF (1) instantiate respects the parity of the
// object allocation (2) addSlot respects the parity of the position of the float default value
// in the prototype


ClaireObject *ClaireClass::instantiate()
{CL_INT i, n = prototype->length;
 ClaireObject *o = instantiate(n);
 ClAlloc->currentNew = o;                           // protect the object but NOT the content !
 CL_INT u = _oid_(o), rep = ADR(u) + 1;
 // <debug for alignment> printf("alloc object size %d -> rep = %d @ %d\n",n,rep, &o);
 for (i= 2; i<=n ; i++)
    {//CL_INT look = rep - ADR(_oid_(o));
	 OID v = (*prototype)[i];                          // value in the prototype
     ClaireClass *c = OWNER(v);                        // owner(v)
     if (c == Kernel._float)                           // implies a range float !
         { // <debug for alignment> printf("rep = %d, i = %d, & = %x v = %g\n",rep,i,&Cmemory[rep],float_v(v));
           *((double *)(rep << 2)) = float_v(v);
#ifdef __LP64__
           rep += 2; i += 1;
#else
           rep++;
#endif
	 }                      // v3.0.68 ! i changes => v changes
     else if ((c == Kernel._set) || (c == Kernel._list))
             {// printf("--- put a copy of %x into C[%d]\n",v,rep + 1);
             *((CL_INT*)(rep++ << 2)) = (CL_INT) copy_bag(OBJECT(bag,v)); }       // copy may cause GC!
     else if (CTAG(v) == OBJ_CODE && v != CNULL)
         {if (v == _oid_(Kernel.NoDefault)) *((CL_INT*)(rep++ << 2)) = CNULL;  // NEW in V3.0.41
          else  *((CL_INT*)(rep++ << 2)) = (CL_INT) OBJECT(ClaireAny,v);}
     else *((CL_INT*)(rep++ << 2)) = v; }
#ifdef CLDEBUG
 if (ClEnv->verbose > 11) printf("<<< instantiate returns %x at adress %d [-> %d]\n",o,getADR(o),rep - 1);
 checkOID(u); // debug !
#endif
 if (Kernel._freeable_object && INHERIT(this, Kernel._freeable_object))
	Kernel._freeable_object->instances->addFast(u);
 ClAlloc->currentNew = NULL;
 return o;}


// instantiation (for named object) m is the module for the symbol, the definition module
// is taken as the current module
thing *ClaireClass::instantiate(char *n, module *m)
{symbol *s = symbol::make(n,m,ClEnv->module_I);
   if (s->value != CNULL && CTAG(s->value) == OBJ_CODE)
      {thing *o = OBJECT(thing,s->value);
        if (o->isa != this)
            { // ClEnv->verbose = 11;
              // see("--- try to make a ",_oid_(this));
              // printf("--- with name %s\n", n);
              // see("--- and found a ",_oid_(o->isa));
              Cerror(18,_oid_(s),_oid_(o->isa));}
        // printf("reuse address %d for object named %s \n",getADR(o),n);
        return o;}
    else {thing *o = (thing *) instantiate();
           o->name = s;
           s->value = _oid_(o);
           if (open != 4) instances->addFast(_oid_(o));
           if (ClEnv->verbose > 10) printf("create a new |%s| @ adr %d\n",n,getADR(o));
           return o;}}

// creates the genealogy for a class
void ClaireClass::genealogy()
{OID self = _oid_(this);
 ClaireClass *c = superclass;
 ITERATE(y);
   descendents = set::alloc(Kernel._class,1,self);
   for (START(c->ancestors); NEXT(y);)
      { OBJECT(ClaireClass,y)->descendents->addFast(self);}
   c->subclass->addFast(self);
   ancestors = (list *) copy_bag(c->ancestors);
   ancestors->addFast(self); }

  
// how to create a new slot
// v3.2: this method is modified so that it may receive ix = the position of 
// the slot (obtained through a macro) in the C++ object [warning: ix may
// also be provided directly by the interpreter, thus the safety check on parity]
slot *ClaireClass::addSlot(property *p,ClaireType *t,OID def,CL_INT ix)
{slot *s = (slot *) instantiate(9);
 OID soid = _oid_(s);
 s->isa = Kernel._slot;
 ClAlloc->currentNew = s; //<sb> fix: keep track of the current allocated slot !
 ClaireClass *c1 = class_I_type(t);
 ClaireClass *s1 = sort_I_class(c1);     // sort: range for the slot
 CL_INT i = slots->length;                  // v3.2: number of existing slots
    s->domain = list::alloc(Kernel._type,1,_oid_(this));
    s->selector = p;
    if (c1 == Kernel._list || c1 == Kernel._set)
       {if (p->restrictions->length == 0)
          if (c1 == Kernel._set) p->multivalued_ask = CTRUE;
          else p->multivalued_ask = Kernel._list;
        if (def == CNULL)
          if (c1 == Kernel._set) def = _oid_(set::empty(of_extract_type(t)));
          else def = _oid_(list::empty(of_extract_type(t))); }
    else if (c1 == Kernel._float && def == CNULL) def = _float_(0.0); //NOTE: test on c !!
    s->DEFAULT = def;
    if ((s1 != Kernel._integer) &&
              (s1 != Kernel._any) &&
              (def == CNULL)) def = 0;      // NULL
    
    if ((p->multivalued_ask == CTRUE && c1 != Kernel._set) ||
        (p->multivalued_ask == Kernel._list && c1 != Kernel._list)) {
       ClAlloc->currentNew = NULL;							//<sb> release the mark ...
       Cerror(28,_oid_(p),GC_OID(soid));        // v3.1.08 //<sb> ... and protect it for the error instanciation
    }
    //<sb> insert the slot in class/selector
    Kernel._slot->instances->addFast(soid);
    p->restrictions->addFast(soid);
    ClAlloc->currentNew = NULL; //<sb> release our mark
#ifndef __LP64__
    if (c1 == Kernel._float && ix % 2 == 0) {     // some architecture requires even float indexes
      if (ALIGN_FIELD ||
            (ALIGN_STRUCT &&
               //<sb> test that the new slot is the first slot of its domain
               // note : i is always positive due to isa @ object !
               OBJECT(ClaireClass,(*(OBJECT(slot,(*slots)[i])->domain))[1]) != this))
         ix++;
    }
#endif
    // change the default representation that will be stored in the prototype
    //  copied_default = object (for object) + float (for float) + integer (for all) + NULL for objects
    if (s1 == Kernel._object || OWNER(def) == Kernel._integer || c1 == Kernel._float) ; // nothing (store def)
    else if (s1 == Kernel._any || s1 == Kernel._integer) 
       {if (def != CNULL) def = _oid_(Kernel.NoDefault);}    // this is the case that wa cannot handle
    else def = 0;
    // new in v3.2 : allow overiding of existing slots
    while (i > 1 && OBJECT(slot,(*slots)[i])->selector != p)  i--;
    if (i <= 1) 
        {slots->addFast(soid);     // a new slot
         // compute the index for slot s (needed for the interpreter :-( )
#ifndef __LP64__
         if (ix > 1) 
            {slot * sprev = OBJECT(slot,slots->content[slots->length - 1]);
             CL_INT i = sprev->index + ((sprev->srange == Kernel._float) ? 2 : 1);
             if (i != ix)                 // alignment constraint: ix was add +1 !
                prototype->addFast(0);}   // maintain length(proto) = size(object)
          s->index = ix;
#endif
	    };                 // ix is given by the interpreter or the C++ compiler !
    else {s->index = OBJECT(slot,(*slots)[i])->index;
          (*slots)[i] = soid;
          (*prototype)[s->index] = def;}
    //  copied_default = object (for object) + float (for float) + integer (for all) + NULL for objects
    if (i <= 1)                                // new slot ! 
     {prototype->addFast(def);
#ifndef __LP64__
      if (c1 == Kernel._float) prototype->addFast(0);
#endif
     }  // maintain length consistency
    s->comment = NULL;			//<sb> fixed in v3.3.35
    s->srange = ((c1 == Kernel._float) ? c1 : s1);      // sort = float allowed only for slots
    s->module_I = ClEnv->module_I;
    s->range = t;
    insert_definition_property(p,s);           // defined in system (unless CLKTEST is defined)
    return s;}                 
    

// --------------------- API method -------------------------------------------

// create a slot
void add_slot_class(ClaireClass *c, property *p, ClaireType *t, OID def, CL_INT ix) 
  {c->addSlot(p,t,def,ix);}


// create an instance
ClaireObject *new_object_class(ClaireClass *c) {return c->instantiate();}
thing *new_thing_class(ClaireClass *c, symbol *s)
   {return c->instantiate(s->name,s->module_I);}

// create a class
ClaireClass *class_I_symbol(symbol *s, ClaireClass *c2)
{return ClaireClass::make(s->name,c2,s->module_I);}

// class to sort mapping
// note that the sort float does not exist as such (mapped to any for the methods's sake)
// float-specific tests must use the range.
ClaireClass *sort_I_class(ClaireClass *c)
{ if (c == Kernel._array || c == Kernel._any || /*c == Kernel._port ||*/  //<sb> port are now of sort object!
     c == Kernel._integer || c == Kernel._string || c == Kernel._void)  return c;
  else if (c == Kernel._float || c == Kernel._primitive) return Kernel._any;
  else if (c == Kernel._class) return Kernel._object;
  else if (c->superclass == Kernel._cl_import) return c;   // v3.3.22
  else return Kernel._object;}


/*********************************************************************/
/**    3. Property                                                   */
/*********************************************************************/

// create a property
property *property::make(char *name, module *m)
{property *ob = (property *) Kernel._property->instantiate(name,m);
  ob->comment = name;               // for debug
  ob->range = Kernel._any;
  ob->open = 1;
  if (ClEnv->verbose > 10) printf("--- create property %s @ %d\n",ob->comment,getADR(ob));
  return ob;}

// same with a status
property *property::make(char *name, CL_INT op, module *m)
{property *ob = make(name,m);
  ob->open = op;
  return ob;}

// temporaty
property *property::make(char *name, CL_INT op, module *m, CL_INT i)
{property *ob = make(name,m);
  ob->open = op;
  ob->dispatcher = i;
  return ob;}

// new (v3.1) same with a dispatcher index !
property *property::make(char *name, CL_INT op, module *m,ClaireClass *c, CL_INT i)
{property *ob = make(name,m);
  ob->open = op;
  ob->dispatcher = i;
  ob->domain = c;
  return ob;}

// constructor for operations
operation *operation::make(char *name, module *m, CL_INT p)
{operation *ob = (operation *) Kernel._operation->instantiate(name,m);
  ob->comment = name;               // for debug
  ob->range = Kernel._any;
  ob->open = 1;
  ob->precedence = p;
  return ob;}
  
// constructor for operations that supports an  open status 
operation *operation::make(char *name, CL_INT op, module *m, CL_INT p)
{operation *ob = (operation *) Kernel._operation->instantiate(name,m);
  ob->comment = name;               // for debug
  ob->range = Kernel._any;
  ob->open = op;
  ob->precedence = p;
  return ob;}
  
// dynamic binding for a message (call) - We got rid of variable argument and use C++
// polymorphism

OID property::operator() (OID arg1)
{PUSH(arg1);
return stack_apply(1);}
   
OID property::operator() (OID arg1, OID arg2)
{PUSH(arg1); PUSH(arg2);
return stack_apply(2);}

OID property::operator() (OID arg1, OID arg2, OID arg3)
{PUSH(arg1); PUSH(arg2); PUSH(arg3);
return stack_apply(3);}

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4);
return stack_apply(4);}

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);
return stack_apply(5);}

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);
 return stack_apply(6); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);
 return stack_apply(7); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);
 return stack_apply(8); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8); PUSH(arg9);
 return stack_apply(9); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8); PUSH(arg9); PUSH(arg10);
 return stack_apply(10); }

// v3.2.54
OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10, OID arg11)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8); PUSH(arg9); PUSH(arg10); PUSH(arg11);
 return stack_apply(11);}
   
OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,OID arg11, OID arg12)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);PUSH(arg9); PUSH(arg10); PUSH(arg11); PUSH(arg12);
    return stack_apply(12); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,
                          OID arg11, OID arg12, OID arg13)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6); PUSH(arg7);PUSH(arg8);PUSH(arg9); PUSH(arg10);PUSH(arg11); PUSH(arg12); PUSH(arg13);
 return stack_apply(13); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,
                          OID arg11, OID arg12, OID arg13, OID arg14)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);
 PUSH(arg9); PUSH(arg10); PUSH(arg11); PUSH(arg12); PUSH(arg13); PUSH(arg14);
 return stack_apply(14); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,
                          OID arg11, OID arg12, OID arg13, OID arg14, OID arg15)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);
 PUSH(arg9); PUSH(arg10); PUSH(arg11); PUSH(arg12); PUSH(arg13); PUSH(arg14); PUSH(arg15);
 return stack_apply(15); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,
                          OID arg11, OID arg12, OID arg13, OID arg14, OID arg15, OID arg16)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);
 PUSH(arg9); PUSH(arg10);PUSH(arg11); PUSH(arg12); PUSH(arg13); PUSH(arg14); PUSH(arg15);PUSH(arg16);
 return stack_apply(16); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,
                          OID arg11, OID arg12, OID arg13, OID arg14, OID arg15,
                          OID arg16, OID arg17)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);
 PUSH(arg9); PUSH(arg10);PUSH(arg11); PUSH(arg12); PUSH(arg13); PUSH(arg14); PUSH(arg15);PUSH(arg16);
 PUSH(arg17);
 return stack_apply(17); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,
                          OID arg11, OID arg12, OID arg13, OID arg14, OID arg15,
                          OID arg16, OID arg17, OID arg18)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);
 PUSH(arg9); PUSH(arg10);PUSH(arg11); PUSH(arg12); PUSH(arg13); PUSH(arg14); PUSH(arg15);PUSH(arg16);
 PUSH(arg17);PUSH(arg8);
 return stack_apply(18); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,
                          OID arg11, OID arg12, OID arg13, OID arg14, OID arg15,
                          OID arg16, OID arg17, OID arg18, OID arg19)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);
 PUSH(arg9); PUSH(arg10);PUSH(arg11); PUSH(arg12); PUSH(arg13); PUSH(arg14); PUSH(arg15);PUSH(arg16);
 PUSH(arg17);PUSH(arg18); PUSH(arg19);
 return stack_apply(19); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,
                          OID arg11, OID arg12, OID arg13, OID arg14, OID arg15,
                          OID arg16, OID arg17, OID arg18, OID arg19, OID arg20)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);
 PUSH(arg9); PUSH(arg10);PUSH(arg11); PUSH(arg12); PUSH(arg13); PUSH(arg14); PUSH(arg15);PUSH(arg16);
 PUSH(arg17);PUSH(arg18); PUSH(arg19); PUSH(arg20);
 return stack_apply(20); }

// this is used by the compiler
OID property::super(ClaireClass *c,CL_INT size)
{CL_INT j = ClEnv->index, i = j - size;
 return eval_message_property(this, find_which_class1(c,definition,i,j),i,CFALSE);}


OID property::stack_apply(CL_INT size)
{CL_INT i = ClEnv->index - size;
 return eval_message_property(this,
              find_which_property1(this,i,OWNER(ClEnv->stack[i])), i, CFALSE);}


// how to create a new method
method *property::addMethod(list *dom, ClaireType *ran, CL_INT sta, ClaireFunction *f)
{method *m = (method *) Kernel._method->instantiate();
   Kernel._method->instances->addFast(_oid_(m));
   m->selector = this;
   restrictions->addFast(_oid_(m));
   m->domain = dom;
   m->range = ran;
   m->module_I = ClEnv->module_I;
   m->functional = f;
   m->evaluate = f;
   m->status = sta;
   // computes the list of sorts
   {list* l = list::empty(Kernel._class);
    ITERATE(z);
    for (START(dom); NEXT(z);)
         l->addFast(_oid_(sort_I_class(class_I_type(OBJECT(ClaireType,z)))));
    l->addFast(_oid_(sort_I_class(class_I_type(ran))));
    m->srange = l;}
   insert_definition_property(this,m);
   return m;}


// special case for a float method
method *property::addFloatMethod(list *dom, ClaireType *ran, CL_INT sta, ClaireFunction *f,
                                 ClaireFunction *f2)
{method *m = addMethod(dom,ran,sta,f);
  m->evaluate = f2;
  return m;}


// add an inlining definition
method *method::inlineDef(char *def)
{return inlineok_ask_method(this,def); }

// --------------------- API method -------------------------------------------

method *add_method_property(property *p, list *dom, ClaireType *r,
                   CL_INT status, OID f)
 { return p->addMethod(dom,r,status,
                       ((f == CNULL) ? NULL : OBJECT(ClaireFunction,f)));}

 
/*********************************************************************/
/**    4. Tables                                                     */
/*********************************************************************/

// expand the alist (hash table) and then creates the item
// the size is 2^n - 4 (even)
CL_INT table::expand(OID x)
{list *old = (list *) graph;
 CL_INT i, j = old->content[0];             // j = chunk size
 list *NEW = make_list_integer(2 * (*old)[0] - 4,CNULL);
   for (i=1; i < j - 4; i = i+2)
       if ((*old)[i] != CNULL) insertHash(NEW,(*old)[i],(*old)[i + 1]);
   graph = NEW;
   if (ClRes->cWorld != 0 && store_ask == CTRUE)      // new from 2.5
     STOREOBJ(((CL_INT *) &graph),(ClaireObject *) old);
   return index_table(this,x);}

// insert a new bucket in a alist without problem. This only works for
// buckets !
CL_INT table::insertHash (list *l, OID x, OID val)
{CL_INT i,chsize = l->content[0],end = chsize - 4,
     mask = (chsize >> 1) - 1, entry = (ClRes->hashOid(mask,x) << 1) + 1;
     for (i = entry; i < end; i = i + 2)
        if ((*l)[i] == CNULL) {(*l)[i] = x; (*l)[i+1] = val; return 1;}
     for (i = 1; i < entry; i = i + 2)
        if ((*l)[i] == CNULL) {(*l)[i] = x; (*l)[i + 1] = val; return 1;}
     return 1;}

// -------------------- API functions -----------------------------------

// add an item in an association list (of size 2^n - 3, full of unknown)
// uses a hash insertion in a list (use the cardinal to find is a new list
// must be allocated). Returns the position in the list
CL_INT index_table(table *a, OID x)
{list *l = (list *) a->graph;
 CL_INT i, chsize = (*l)[0], end = chsize - 4,
     mask = (chsize >> 1) - 1, entry = (ClRes->hashOid(mask,x) << 1) + 1;
   for (i = entry; i < end; i = i + 2)
        if (equal((*l)[i],x) == CTRUE) return i + 1;
        else if ((*l)[i] == CNULL)
          {ClaireClass *c = OWNER(a->DEFAULT);
           if ((i - entry) > (chsize >> 2)) return a->expand(x);
           (*l)[i] = x;
           if ((c == Kernel._set) || (c == Kernel._list))
                (*l)[i+1] = _oid_(copy_bag(OBJECT(bag,a->DEFAULT)));
           else (*l)[i+1] = a->DEFAULT;
           return (i + 1);}
   if ((i - entry) > (chsize >> 2)) return a->expand(x);
   if (entry > end) entry = end;    // <yc> 9/98 do not cross the bound
   for (i = 1; i < entry; i = i + 2)
       if (equal((*l)[i],x) == CTRUE) return i + 1;
       else if ((*l)[i] == CNULL)
          {ClaireClass *c = OWNER(a->DEFAULT);
           (*l)[i] = x;
           if ((c == Kernel._set) || (c == Kernel._list))   // v3.0.29 : copy
                (*l)[i+1] = _oid_(copy_bag(OBJECT(bag,a->DEFAULT)));
           else (*l)[i+1] = a->DEFAULT;
           return (i + 1);}
   return a->expand(x);}


// a nice version that takes two args and does not allocate the tuple.
// WARNING: this does not return the index but the value !!!!
//          it is thus simpler, because it is only used for reading
// v3.2.16: was completely false !!!!
CL_INT index_table2(table *a, OID x, OID y)
{list *l = (list *) a->graph;
 CL_INT i,chsize = (*l)[0], end = chsize - 4,
     mask = (chsize >> 1) - 1,
     hash2 = (ClRes->hashOid(mask,x) + ClRes->hashOid(mask,y)) & mask,
     entry = (hash2 << 1) + 1;
   for (i = entry; i < end; i = i + 2)
      {if ((*l)[i] == CNULL) return a->DEFAULT;
       else if (equal((*(OBJECT(list,(*l)[i])))[1],x) == CTRUE &&
                equal((*OBJECT(list,(*l)[i]))[2],y) == CTRUE) return (*l)[i + 1];}
   if (entry > end) entry = end;    // <yc> 9/98 do not cross the bound
   for (i = 1; i < entry; i = i + 2)
     {if ((*l)[i] == CNULL) return a->DEFAULT;
      else if (equal((*OBJECT(list,(*l)[i]))[1],x) == CTRUE &&
               equal((*OBJECT(list,(*l)[i]))[2],y) == CTRUE) return (*l)[i + 1];}
   return a->DEFAULT;}



//<sb> put make_table at the kernel level -> we need a special protection
// new in v3.2.50 a constructor for building a table dynamically
table * make_table_type(ClaireType *dom, ClaireType *rng, OID def)
{ table * t = (table *)new_object_class(Kernel._table);
  t->range = rng;
  t->domain = dom;
  t->DEFAULT = def;
  t->params = _oid_(Kernel._any);
  t->graph = 0;
  if (ClAlloc->statusGC != 2)  GC_PUSH(t);
  t->graph = make_list_integer(29, CNULL);
  return t;}


//<sb> moved find_wich_property into Kernel, here any program spends
// many time. It as been carefully optimized :
//		- handles the case when there is no dictionary, an inline 
// version (in Kernel.h) handles the dictionary case (early exit optim)
// 		- it manages a cache containing the sort of arguments pushed on the stack,
// and perform the restriction match check against the cache

/*
struct fw_cache_item {
	restriction *r;
	property *def;
	CL_INT narg;
	ClaireClass *owners[4];
	CL_INT conflict;
};

static fw_cache_item fw_cache[1024];

#define FW_HASH_BEGIN CL_INT hash = 0;
#define FW_HASH_MORE(n) {hash += n; hash += (hash << 10);hash ^= (hash >> 6);}
#define FW_HASH_END {hash += (hash << 3); hash ^= (hash >> 11); hash += (hash << 15); hash &= 1023;}
#define FW_HASH_INSERT(restr) {fw_cache_item &it = fw_cache[hash]; \
			if (it.r == NULL) {it.r = restr; it.def = p; it.narg = x; memcpy(&it.owners, sts+1, 4*sizeof(CL_INT));}}

void reset_find_which_cache() {
	memset(fw_cache, 0, sizeof(fw_cache));
}

static ClaireClass* sts[21];

ClaireObject * find_which_property_no_dictionary_more(property *p, CL_INT n, CL_INT *st, CL_INT x, unsigned hash);
ClaireObject * find_which_property_no_dictionary(property *p,CL_INT n)
{   CL_INT  x = ClEnv->index - n;
	CL_INT *st = ClEnv->stack;
	CL_INT j = 1;
	CL_INT y = n;
	//<sb> fill a cache of arguments sorts
	FW_HASH_BEGIN
	FW_HASH_MORE((CL_UNSIGNED)p);
	FW_HASH_MORE((CL_UNSIGNED)x);
	for(;j <= x; j++) {
		CL_INT d = st[y++];
		ClaireClass *c = OWNER(d);
		sts[j] = c;
		FW_HASH_MORE((CL_UNSIGNED)c);
	}
	FW_HASH_END
	fw_cache_item &it = fw_cache[hash];
	if (it.r && it.def == p && x == it.narg && memcmp(&it.owners, sts+1, x*sizeof(CL_INT)) == 0) {
		return it.r;
	}
	return find_which_property_no_dictionary_more(p, n, st, x, hash);
}

ClaireObject * find_which_property_no_dictionary_more(property *p, CL_INT n, CL_INT *st, CL_INT x, unsigned hash) {

	static OID lla = 0;
	static ClaireClass *lcl;
	static ClaireClass *lany;
	static ClaireClass *lint;
	if(lla == 0) {
		lla = _oid_(Kernel._listargs);
		lcl = Kernel._class;
		lany = Kernel._any;
		lCL_INT = Kernel._integer;
		memset(fw_cache, 0, sizeof(fw_cache));
	}
	list *ldef = p->definition;
	OID *ar = ldef->content;
	CL_INT len = ldef->length;
	CL_INT j;
	//<sb> lookup for a mathing restriction
	for(j = 1;j <= len; j++) {
		restriction *r = OBJECT(restriction,ar[j]);
		list *l = r->domain;
		CL_INT z = l->length;
		OID *ct = l->content;
		if ((z == x) && ct[x] != lla) {
			CL_INT i = 1;
			CL_INT y = n;
			while (i <= x) {
				OID  u = ct[i];
				ClaireClass* ens = OBJECT(ClaireClass,u);
				if (ens->isa == lcl) {
					ClaireClass *c = sts[i];
					if ((INT_MASK & u) != OBJ_CODE) {
						if (c == lany || c == lCL_INT)
							break;
					} else if (!INHERIT(c, ens)) {
						break;
					}
				} else if (vmatch_ask_any(u,st[y],n) != CTRUE)
					break;
				++y;
				++i;
			}
			if (i > x) {FW_HASH_INSERT(r) return r;}
		} else if ((z-1) <= x && ct[z] == lla) {
		   CL_INT  i = 1;
		   while ((i <= z))
				{ { CL_INT  y = ((n-1)+i);
					if (ct[i] == lla)
					 { st[y] = _oid_(get_args_integer(y));
					  ClEnv->index = y + 1;
					  return r;
					  }
					else if (vmatch_ask_any(ct[i],st[y],n) != CTRUE)
					 {
						break;
					 }
					}
				  ++i;
			}
		}			
	}
return CFALSE;
}*/


ClaireObject * find_which_property1(property *p,CL_INT n,ClaireClass *c)
{   static OID lla = 0;
	static ClaireClass *lcl;
	static ClaireClass *lany;
	static ClaireClass *lint;
	static ClaireClass* sts[21];
	if (p->dictionary == CTRUE) return hashget_class(c, p);
	else {
		if(lla == 0) {
			lla = _oid_(Kernel._listargs);
			lcl = Kernel._class;
			lany = Kernel._any;
			lCL_INT = Kernel._integer;
		}
		list *ldef = p->definition;
		OID *ar = ldef->content;
		CL_INT len = ldef->length;
		CL_INT  x = ClEnv->index - n;
		CL_INT *st = ClEnv->stack;
		CL_INT j = 1;
		CL_INT  y = n;
		//<sb> fill a cache of arguments sorts
		for(;j <= x; j++) {
			CL_INT d = st[y++];
			sts[j] = OWNER(d);
		}
		//<sb> lookup for a mathing restriction
		for(j = 1;j <= len; j++) {
			restriction *r = OBJECT(restriction,ar[j]);
			list *l = r->domain;
			CL_INT z = l->length;
			OID *ct = l->content;
			if ((z == x) && ct[x] != lla) {
				CL_INT i = 1;
				CL_INT y = n;
				while (i <= x) {
					OID  u = ct[i];
					ClaireClass* ens = OBJECT(ClaireClass,u);
					if (ens->isa == lcl) {
						ClaireClass *c = sts[i];
							if ((INT_MASK & u) != OBJ_CODE) {
								if (c == lCL_INT || c == lany)
									break;
							} else if (!INHERIT(c, ens)) {
								break;
							}
					} else if (vmatch_ask_any(u,st[y],n) != CTRUE)
						break;
					++y;
					++i;
				}
				if (i > x) return r;
			} else if ((z-1) <= x && ct[z] == lla) {
			   CL_INT  i = 1;
			   while ((i <= z))
					{ { CL_INT  y = ((n-1)+i);
						if (ct[i] == lla)
						 { st[y] = _oid_(get_args_integer(y));
						  ClEnv->index = y + 1;
						  return r;
						  }
						else if (vmatch_ask_any(ct[i],st[y],n) != CTRUE)
						 {
							break;
						 }
						}
					  ++i;
				}
			}			
		}
	}
	return CFALSE;
}
