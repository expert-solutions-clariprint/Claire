/***** CLAIRE Compilation of file ./meta/function.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:32 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>

//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| function.cl                                                 |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+
// --------------------------------------------------------------------
// This file hold the methods that are defined by an external function
// and those that apply to a primitive type
// --------------------------------------------------------------------
// *********************************************************************
// *  Table of contents                                                *
// *   Part 1: Basics of pretty printing                               *
// *   Part 2: Methods for CLAIRE objects                              *
// *   Part 3: System Methods                                          *
// *   Part 4: Methods for Native entities                             *
// *********************************************************************
// we find here what is necessary for the minimal kernel of CLAIRE
// ==============================================================
// The c++ function for: min(x:integer,y:integer) [SAFE_RESULT]
int  min_integer1(int x,int y)
{ { CL_INT Result = 0;
    Result = (((CL_INT)x <= (CL_INT)y) ?
      x :
      y );
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: max(x:integer,y:integer) [SAFE_RESULT]
int  max_integer1(int x,int y)
{ { CL_INT Result = 0;
    Result = (((CL_INT)x <= (CL_INT)y) ?
      y :
      x );
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: min(g0058:any,g0059:any) [RETURN_ARG]
OID  min_float1_(OID g0058,OID g0059)
{ return _float_(min_float1(float_v(g0058),float_v(g0059)));}


// The c++ function for: min(x:float,y:float) [RETURN_ARG]
double  min_float1(double x,double y)
{ { double Result =0.0;
    Result = ((x <= y) ?
      x :
      y );
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: max(g0060:any,g0061:any) [RETURN_ARG]
OID  max_float1_(OID g0060,OID g0061)
{ return _float_(max_float1(float_v(g0060),float_v(g0061)));}


// The c++ function for: max(x:float,y:float) [RETURN_ARG]
double  max_float1(double x,double y)
{ { double Result =0.0;
    Result = ((x <= y) ?
      y :
      x );
    POP_SIGNAL; return (Result);}
  }


// *********************************************************************
// *   Part 1: Basics of pretty printing                               *
// *********************************************************************
// we use a nice object
// support reccursive print-in-string 
// buffered print
// new in v3.3.26: unbounded recursion is supported :-)
// The c++ function for: print_in_string(_CL_obj:void) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  print_in_string_void()
{ GC_BIND;
  { CL_INT  n = ((CL_INT)Core.pretty->cprevious+(CL_INT)2);
    blob * pp = GC_OBJECT(blob,Core.pretty->cpretty);
    blob * p1 = GC_OBJECT(blob,blob_I_void1());
    PortObject * p2 = use_as_output_port(p1);
    (Core.pretty->cprevious = n);
    (Core.pretty->cpretty = p1);
    if (equal(_oid_(Core.pretty->cpstack),Core.nil->value) == CTRUE)
     (Core.pretty->cpstack = list::alloc(Kernel._port,3,_oid_(pp),
      _oid_(p2),
      _oid_(p1)));
    else { GC_OBJECT(list,Core.pretty->cpstack)->addFast((OID)_oid_(p2));
        GC_OBJECT(list,Core.pretty->cpstack)->addFast((OID)_oid_(p1));
        }
      }
  GC_UNBIND; POP_SIGNAL;}


//pretty.cpstack[n] := p2,
// if (n = length(pretty.cpstack)) pretty.cpstack :add p1)) ]
// The c++ function for: end_of_string(_CL_obj:void) [NEW_ALLOC+SLOT_UPDATE]
char * end_of_string_void()
{ GC_BIND;
  if (Core.pretty->cprevious == 1)
   close_exception(((general_error *) (*Core._general_error)(_string_("[123] unbalanced use of print-in-string"),
    _oid_(Kernel.nil))));
  { char *Result ;
    { CL_INT  n = Core.pretty->cprevious;
      char * s = GC_STRING(string_I_blob1(GC_OBJECT(blob,Core.pretty->cpretty)));
      buffer * op = GC_OBJECT(buffer,OBJECT(buffer,(*(Core.pretty->cpstack))[((CL_INT)n-(CL_INT)2)]));
      PortObject * p = GC_OBJECT(PortObject,OBJECT(PortObject,(*(Core.pretty->cpstack))[((CL_INT)n-(CL_INT)1)]));
      use_as_output_port(p);
      rmlast_list(Core.pretty->cpstack);
      rmlast_list(Core.pretty->cpstack);
      fclose_device1(GC_OBJECT(blob,Core.pretty->cpretty));
      (Core.pretty->cpretty = ((blob *) op));
      (Core.pretty->cprevious = ((CL_INT)Core.pretty->cprevious-(CL_INT)2));
      Result = s;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: mClaire/buffer_length(_CL_obj:void) [RETURN_ARG]
int  buffer_length_void()
{ POP_SIGNAL; return (length_blob1(Core.pretty->cpretty));}


// The c++ function for: mClaire/buffer_set_length(i:integer) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  buffer_set_length_integer(int i)
{ set_length_blob1(Core.pretty->cpretty,i);
  POP_SIGNAL;}


// a method for calling the printer without issuing a message
// here we assume that self_print is always defined as a function
// The c++ function for: apply_self_print(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  apply_self_print_any(OID self)
{ GC_BIND;
  if (INHERIT(OWNER(self),Kernel._thing))
   princ_symbol(OBJECT(thing,self)->name);
  else if (INHERIT(OWNER(self),Kernel._class))
   princ_symbol(OBJECT(ClaireClass,self)->name);
  else if (INHERIT(OWNER(self),Kernel._integer))
   princ_integer(self);
  else if (Kernel._string == OWNER(self))
   (*Kernel.self_print)(self);
  else { method * _Zprop = ((method *) _at_property1(Kernel.self_print,OWNER(self)));
      if (INHERIT(OWNER(self),Kernel._exception))
       color(31,0);
      if ((boolean_I_any(_oid_(_Zprop)) == CTRUE) && 
          (((_Zprop->functional == (NULL)) ? CTRUE : CFALSE) != CTRUE))
       { list * l = _Zprop->srange;
        fcall1(_Zprop->evaluate,OBJECT(ClaireClass,(*(l))[1]),self,OBJECT(ClaireClass,(*(l))[2]));
        }
      else { ClaireHandler c_handle = ClaireHandler();
          if ERROR_IN 
          { (*Kernel.self_print)(self);
            ERROR_FREE;}
          else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
          { c_handle.catchIt();{ princ_string("<unprintable:");
              print_any(_oid_(OWNER(self)));
              princ_string(" (");
              print_any(GC_OID(_oid_(ClEnv->exception_I)));
              princ_string(")>");
              }
            }
          else PREVIOUS_HANDLER;}
        if (INHERIT(OWNER(self),Kernel._exception))
       color(30,0);
      }
    GC_UNBIND; POP_SIGNAL;}


// some basic definitions
// The c++ function for: self_print(self:any) [NEW_ALLOC+SLOT_UPDATE]
void  self_print_any_Core(OID self)
{ if (self == CNULL)
   princ_string("unknown");
  else { princ_string("<");
      print_any(_oid_(OWNER(self)));
      princ_string(">");
      }
    POP_SIGNAL;}


// The c++ function for: self_print(self:exception) [NEW_ALLOC]
void  self_print_exception1_Core(ClaireException *self)
{ princ_string("<");
  print_any(_oid_(OWNER(_oid_(self))));
  princ_string(">");
  POP_SIGNAL;}


// The c++ function for: self_print(self:boolean) [0]
void  self_print_boolean_Core(ClaireBoolean *self)
{ if (self == CTRUE)
   princ_string("true");
  else princ_string("false");
    POP_SIGNAL;}


// The c++ function for: self_print(self:function) [0]
void  self_print_function_Core(ClaireFunction *self)
{ princ_string("#'");
  princ_string(string_I_function(self));
  POP_SIGNAL;}


// prints the name of a restriction. If we have a close property and if a
// short-cut is possible, we use it.
// The c++ function for: self_print(self:restriction) [NEW_ALLOC]
void  self_print_restriction_Core(restriction *self)
{ if ((not_any(_oid_(((self->selector == (NULL)) ? CTRUE : CFALSE))) != CTRUE) || 
      (self->domain == (NULL)))
   { princ_string("<");
    print_any(_oid_(OWNER(_oid_(self))));
    princ_string(">");
    }
  else { property * p = self->selector;
      CL_INT  n = 0;
      ClaireClass * c = domain_I_restriction(self);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(r);
        for (START(p->restrictions); NEXT(r);)
        if (domain_I_restriction(OBJECT(restriction,r)) == c)
         ++n;
        }
      princ_symbol(p->name);
      princ_string(" @ ");
      { OID  g0065UU;
        if (n == 1)
         g0065UU = _oid_(c);
        else g0065UU = _oid_(self->domain);
          print_any(g0065UU);
        }
      }
    POP_SIGNAL;}


// we are too far
// The c++ function for: print(x:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  print_any(OID x)
{ if ((Core.pretty->pbreak == CTRUE) && 
      (Core.pretty->pprint == CTRUE))
   { CL_INT  b_index = buffer_length_void();
    ClaireBoolean * missed = CFALSE;
    CL_INT  _Zl = Core.pretty->index;
    if (short_enough_integer(((CL_INT)b_index+(CL_INT)10)) != CTRUE)
     { (Core.pretty->pprint = CFALSE);
      (Core.pretty->pbreak = CFALSE);
      print_any(x);
      (Core.pretty->pprint = CTRUE);
      }
    else { { ClaireHandler c_handle = ClaireHandler();
          if ERROR_IN 
          { { (Core.pretty->pbreak = CFALSE);
              apply_self_print_any(x);
              (Core.pretty->pbreak = CTRUE);
              }
            ERROR_FREE;}
          else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Core._much_too_far)) == CTRUE)
          { c_handle.catchIt();missed= CTRUE;
            }
          else PREVIOUS_HANDLER;}
        if (missed == CTRUE)
         { (Core.pretty->pprint = CTRUE);
          (Core.pretty->pbreak = CTRUE);
          buffer_set_length_integer(b_index);
          (Core.pretty->index = _Zl);
          apply_self_print_any(x);
          }
        }
      }
  else apply_self_print_any(x);
    ;POP_SIGNAL;}


// The c++ function for: short_enough(self:integer) [0]
ClaireBoolean * short_enough_integer(int self)
{ POP_SIGNAL; return (_inf_integer(self,Core.pretty->width));}


// *********************************************************************
// *   Part 2: Methods for CLAIRE objects                              *
// *********************************************************************
// the instantiation body is a sequence of words from which the initialization
// of the object must be built.
//  copied_def = object (for object) + float (for float) + integer (for all)
//               + NULL for objects
// v3.2.12: use a condition that is coherent with ClReflect.cl : a slot defaut value must be placed
// unless it is a copied_def
// The c++ function for: mClaire/complete!(self:object) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
ClaireObject * complete_I_object(ClaireObject *self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(s);
    for (START(self->isa->slots); NEXT(s);)
    { GC_LOOP;
      { property * p = OBJECT(restriction,s)->selector;
        ClaireClass * s2 = OBJECT(slot,s)->srange;
        OID  d = GC_OID(OBJECT(slot,s)->DEFAULT);
        if (d != CNULL)
         { OID  v = slot_get_object(self,OBJECT(slot,s)->index,OBJECT(slot,s)->srange);
          if ((v == CNULL) && 
              (((s2 == Kernel._object) ? CTRUE : ((INHERIT(OWNER(d),Kernel._integer)) ? CTRUE : ((s2 == Kernel._float) ? CTRUE : CFALSE))) != CTRUE))
           update_property(p,
            self,
            OBJECT(slot,s)->index,
            OBJECT(slot,s)->srange,
            d);
          else if (equal(d,v) == CTRUE)
           { if (p->multivalued_ask != CFALSE)
             { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(y);
              bag *y_support;
              y_support = GC_OBJECT(bag,enumerate_any(d));
              for (START(y_support); NEXT(y);)
              update_plus_relation(p,_oid_(self),y);
              }
            else update_plus_relation(p,_oid_(self),d);
              }
          }
        }
      GC_UNLOOP; POP_SIGNAL;}
    }
  { ClaireObject *Result ;
    { OID  m = GC_OID(_oid_(_at_property1(Kernel.close,OWNER(_oid_(self)))));
      Result = ((Kernel._method == OWNER(m)) ?
        OBJECT(ClaireObject,funcall_method1(OBJECT(method,m),_oid_(self))) :
        self );
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// v3.0.41  obviously
//-------------------------- ENTITY   --------------------------------------
// The c++ function for: not(self:any) [0]
ClaireBoolean * not_any(OID self)
{ { ClaireBoolean *Result ;
    Result = ((self == Kernel.ctrue) ?
      CFALSE :
      ((self == Kernel.cfalse) ?
        CTRUE :
        ((boolean_I_any(self) != CTRUE) ?
          CTRUE :
          CFALSE ) ) );
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: !=(self:any,x:any) [0]
ClaireBoolean * _I_equal_any(OID self,OID x)
{ { ClaireBoolean *Result ;
    Result = ((equal(self,x) == CTRUE) ?
      CFALSE :
      CTRUE );
    POP_SIGNAL; return (Result);}
  }


// gives the type of any object. This is open_coded.
// The c++ function for: owner(self:any) [0]
ClaireClass * owner_any(OID self)
{ POP_SIGNAL; return (OWNER(self));}


// some useful methods
// The c++ function for: known?(self:any) [0]
ClaireBoolean * known_ask_any(OID self)
{ POP_SIGNAL; return (_I_equal_any(CNULL,self));}


// The c++ function for: unknown?(self:any) [0]
ClaireBoolean * unknown_ask_any(OID self)
{ POP_SIGNAL; return (equal(CNULL,self));}


// needed by the compiled code
// The c++ function for: check_in(self:any,y:type) [RETURN_ARG]
OID  check_in_any(OID self,ClaireType *y)
{ { OID Result = 0;
    if (belong_to(self,_oid_(y)) == CTRUE)
     Result = self;
    else { OID  V_CL0066;close_exception(((general_error *) (*Core._general_error)(_string_("[124] the value ~S does not belong to the range ~S"),
          _oid_(list::alloc(2,self,_oid_(y))))));
        
        Result=_void_(V_CL0066);}
      POP_SIGNAL; return (Result);}
  }


// The c++ function for: check_in(self:bag,c:class,y:type) [NEW_ALLOC+RETURN_ARG]
bag * check_in_bag(bag *self,ClaireClass *c,ClaireType *y)
{ { bag *Result ;
    { ClaireObject *V_CC ;
      { ClaireBoolean * g0067I;
        { OID  g0068UU;
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(z);
            g0068UU= Kernel.cfalse;
            for (START(self); NEXT(z);)
            if (belong_to(z,_oid_(y)) != CTRUE)
             { g0068UU = Kernel.ctrue;
              ClEnv->cHandle = loop_handle;break;}
            }
          g0067I = not_any(g0068UU);
          }
        
        if (g0067I == CTRUE) V_CC = OBJECT(bag,(*Kernel.cast_I)(_oid_(self),
            _oid_(y)));
          else close_exception(((general_error *) (*Core._general_error)(_string_("[124] the value ~S does not belong to subtype[~S\262]"),
          _oid_(list::alloc(2,_oid_(self),_oid_(y))))));
        }
      Result= (bag *) V_CC;}
    POP_SIGNAL; return (Result);}
  }


// new in v3.00.48
// The c++ function for: <(self:any,x:any) [NEW_ALLOC]
ClaireBoolean * _inf_any(OID self,OID x)
{ { ClaireBoolean *Result ;
    Result = ((equal(self,x) == CTRUE) ?
      CFALSE :
      OBJECT(ClaireBoolean,(*Kernel._inf_equal)(self,
        x)) );
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: >(self:any,x:any) [NEW_ALLOC]
ClaireBoolean * _sup_any(OID self,OID x)
{ { ClaireBoolean *Result ;
    Result = ((equal(self,x) == CTRUE) ?
      CFALSE :
      OBJECT(ClaireBoolean,(*Kernel._inf_equal)(x,
        self)) );
    POP_SIGNAL; return (Result);}
  }


// >= is defined as a macro in file.cl
// ----------------------- CLASS ---------------------------------------------
// declares a class as ephemeral: the member set is not maintained
// v3.2.14 recusively applies to subclasses
// The c++ function for: ephemeral(self:class) [SLOT_UPDATE+RETURN_ARG]
OID  ephemeral_class(ClaireClass *self)
{ { OID Result = 0;
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(c);
      Result= Kernel.cfalse;
      for (START(self->descendents); NEXT(c);)
      if ((OBJECT(ClaireClass,c)->instances->length != 0) || 
          ((CL_INT)OBJECT(ClaireClass,c)->open <= 1))
       close_exception(((general_error *) (*Core._general_error)(_string_("[187] cannot declare ~S as ephemeral because of ~S"),
        _oid_(list::alloc(2,_oid_(self),c)))));
      else (OBJECT(ClaireClass,c)->open = ClEnv->ephemeral);
        }
    POP_SIGNAL; return (Result);}
  }


// declares a class as an abtract class (without instances)
// The c++ function for: abstract(c:class) [NEW_ALLOC+SLOT_UPDATE+SAFE_RESULT]
OID  abstract_class(ClaireClass *c)
{ { OID Result = 0;
    { CL_INT  n = c->open;
      if (n == ClEnv->ephemeral)
       close_exception(((general_error *) (*Core._general_error)(_string_("[125] ephemeral classes cannot be abstract"),
        _oid_(Kernel.nil))));
      else { if (c->instances->length != 0)
           { if (should_trace_ask_module1(Core.it,3) == CTRUE)
             mtformat_module1(Core.it,"--- note: ~S already has some instances",3,list::alloc(1,_oid_(c)));
            else ;}
          if (n == 2)
           (c->open = 0);
          else if (n == 1)
           (c->open = -1);
          }
        Result = _oid_(c);
      }
    POP_SIGNAL; return (Result);}
  }


// declares a class as totally defined in the hierarchy: no new subclasses can be added.
// The c++ function for: final(c:class) [SLOT_UPDATE+SAFE_RESULT]
OID  final_class(ClaireClass *c)
{ { OID Result = 0;
    { CL_INT  n = c->open;
      if (n == 3)
       close_exception(((general_error *) (*Core._general_error)(_string_("[126] ephemeral classes cannot be set as final"),
        _oid_(Kernel.nil))));
      else if (n == 2)
       (c->open = 1);
      else if (n == 0)
       (c->open = -1);
      Result = _oid_(c);
      }
    POP_SIGNAL; return (Result);}
  }


//instantiation with and without a name
// The c++ function for: new(self:class) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
ClaireObject * new_class1(ClaireClass *self)
{ GC_BIND;
  { ClaireObject *Result ;
    { ClaireObject * o;
      { { if ((CL_INT)self->open <= 0)
           close_exception(((general_error *) (*Core._general_error)(_string_("[105] cannot instantiate ~S"),
            _oid_(list::alloc(1,_oid_(self))))));
          o = new_object_class(self);
          }
        GC_OBJECT(ClaireObject,o);}
      if (self->open != ClEnv->ephemeral)
       self->instances->addFast((OID)_oid_(o));
      Result = complete_I_object(o);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: new_class1_type
ClaireType * new_class1_type(ClaireType *self)
{ GC_BIND;
  { ClaireType *Result ;
    Result = glb_class(Kernel._object,GC_OBJECT(ClaireType,member_type(self)));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// v3.2.26
// The c++ function for: new(self:class,%nom:symbol) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
thing * new_class2(ClaireClass *self,symbol *_Znom)
{ { thing *Result ;
    { ClaireObject *V_CC ;
      { thing * o;
        { if ((CL_INT)self->open <= 0)
           close_exception(((general_error *) (*Core._general_error)(_string_("[105] cannot instantiate ~S"),
            _oid_(list::alloc(1,_oid_(self))))));
          o = new_thing_class(self,_Znom);
          }
        V_CC = complete_I_object(o);
        }
      Result= (thing *) V_CC;}
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: new_class2_type
ClaireType * new_class2_type(ClaireType *self,ClaireType *_Znom)
{ GC_BIND;
  { ClaireType *Result ;
    Result = glb_class(Kernel._thing,GC_OBJECT(ClaireType,member_type(self)));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// v3.2.26
// internal version
// The c++ function for: new_object_class_type
ClaireType * new_object_class_type(ClaireType *self)
{ GC_BIND;
  { ClaireType *Result ;
    Result = glb_class(Kernel._object,GC_OBJECT(ClaireType,member_type(self)));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: new_thing_class_type
ClaireType * new_thing_class_type(ClaireType *self,ClaireType *_Znom)
{ GC_BIND;
  { ClaireType *Result ;
    Result = glb_class(Kernel._thing,GC_OBJECT(ClaireType,member_type(self)));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// the smallest super_set of two sets
// there is always any, so it always returns a class
// The c++ function for: meet(self:class,ens:class) [RETURN_ARG]
ClaireClass * meet_class(ClaireClass *self,ClaireClass *ens)
{ { ClaireClass *Result ;
    { list * l1 = self->ancestors;
      list * l2 = ens->ancestors;
      CL_INT  m = (((CL_INT)l1->length < (CL_INT)l2->length) ?
        l1->length :
        l2->length );
      { CL_INT loop_handle = ClEnv->cHandle;
        while ((equal((*(l1))[m],(*(l2))[m]) != CTRUE))
        { m= ((CL_INT)m-(CL_INT)1);
          POP_SIGNAL;}
        }
      Result = OBJECT(ClaireClass,(*(l1))[m]);
      }
    POP_SIGNAL; return (Result);}
  }


// fast inclusion method for lattice_sets (lattice order). The argument is
// either a lattice_set or {}
// The c++ function for: inherit?(self:class,ens:class) [0]
ClaireBoolean * inherit_ask_class(ClaireClass *self,ClaireClass *ens)
{ { ClaireBoolean *Result ;
    { list * l = self->ancestors;
      CL_INT  n = ens->ancestors->length;
      Result = (((CL_INT)n <= (CL_INT)l->length) ? (((*(l))[n] == _oid_(ens)) ? CTRUE: CFALSE): CFALSE);
      }
    POP_SIGNAL; return (Result);}
  }


//------------- PROPERTY ---------------------------------------------------
// the two methods to access open(r)
// an abstract property is extensible and can receive new restrictions
// The c++ function for: abstract(p:property) [SLOT_UPDATE+SAFE_RESULT]
OID  abstract_property(property *p)
{ { OID Result = 0;
    { CL_INT  n = p->open;
      if ((CL_INT)n < 2)
       close_exception(((general_error *) (*Core._general_error)(_string_("[127] ~S can no longer become abstract"),
        _oid_(list::alloc(1,_oid_(p))))));
      else (p->open = 3);
        Result = _oid_(p);
      }
    POP_SIGNAL; return (Result);}
  }


// a final property is completely defined and cannot receive a new restriction
// v3.2.04: the new value 4 will be used to represent (compiled but open)
// The c++ function for: final(r:relation) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  final_relation(ClaireRelation *r)
{ GC_BIND;
  if (INHERIT(r->isa,Kernel._property))
   { if ((CL_INT)r->open <= 2)
     { (r->open = 1);
      { ClaireRelation * g0069 = r; 
        ClaireType * g0070;
        { list * g0071UU;
          { { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID x; CL_INT CLcount;
              v_list = CLREAD(property,r,restrictions);
               g0071UU = v_list->clone();
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { x = (*(v_list))[CLcount];
                v_val = (*(OBJECT(restriction,x)->domain))[1];
                
                (*((list *) g0071UU))[CLcount] = v_val;}
              }
            GC_OBJECT(list,g0071UU);}
          g0070 = Uall_list(g0071UU);
          }
        (g0069->domain = g0070);}
      { ClaireRelation * g0072 = r; 
        ClaireType * g0073;
        { list * g0074UU;
          { { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID x; CL_INT CLcount;
              v_list = CLREAD(property,r,restrictions);
               g0074UU = v_list->clone();
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { x = (*(v_list))[CLcount];
                v_val = _oid_(OBJECT(restriction,x)->range);
                
                (*((list *) g0074UU))[CLcount] = v_val;}
              }
            GC_OBJECT(list,g0074UU);}
          g0073 = Uall_list(g0074UU);
          }
        (g0072->range = g0073);}
      }
    }
  GC_UNBIND; POP_SIGNAL;}


//------------- MODULES   --------------------------------------------------
// the close function gives its right value to the *internal* slot that
// is the order of the module in the system. The name is supposed to be
// read in the system module.
// The c++ function for: close(self:module) [NEW_ALLOC+SLOT_UPDATE+SAFE_RESULT]
module * close_module(module *self)
{ GC_BIND;
  if (self != claire.it)
   { if (((self->part_of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     { module * sup = self->part_of;
      GC_OBJECT(list,sup->parts)->addFast((OID)_oid_(self));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(x);
        bag *x_support;
        x_support = GC_OBJECT(list,sup->uses);
        for (START(x_support); NEXT(x);)
        { GC_LOOP;
          if ((contain_ask_list(self->uses,x) != CTRUE) && 
              (INHERIT(OWNER(x),Kernel._module)))
           GC_OBJECT(list,self->uses)->addFast((OID)x);
          GC_UNLOOP; POP_SIGNAL;}
        }
      }
    else if (should_trace_ask_module1(Core.it,3) == CTRUE)
     mtformat_module1(Core.it,"---- note: ~S is a root module !\n",3,GC_OBJECT(list,list::alloc(1,_oid_(self))));
    else ;}
  { module *Result ;
    Result = self;
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// note: dynamic modules are no longer supported
// The c++ function for: get_symbol(self:string) [0]
OID  get_symbol_string(char *self)
{ POP_SIGNAL; return (get_symbol_module(claire.it,self));}


// *********************************************************************
// *   Part 3: System Methods                                          *
// *********************************************************************
// all these methods will be open-coded by the compiler
//get_stack(self:integer) : any -> get_stack(self)
//put_stack(self:integer,x:any) : any -> put_stack(self, x)
//push!(self:meta_system,x:any) : void -> push!(self, x)
//stat() : void -> function!(claire_stat)
// The c++ function for: gensym(self:void) [0]
symbol * gensym_void()
{ POP_SIGNAL; return (gensym_string("g"));}


// world management
// The c++ function for: store(l:list,n:integer,y:any) [BAG_UPDATE+RETURN_ARG]
OID  store_list4(list *l,int n,OID y)
{ POP_SIGNAL; return (STOREI((*l)[n],y));}


// The c++ function for: store(l:array,n:integer,y:any) [RETURN_ARG]
OID  store_array1(OID *l,int n,OID y)
{ POP_SIGNAL; return (store_array(l,n,y,CTRUE));}


// The c++ function for: commit(n:integer) [0]
void  commit_integer(int n)
{ { CL_INT loop_handle = ClEnv->cHandle;
    while (((CL_INT)n < (CL_INT)world_number()))
    { world_remove();
      POP_SIGNAL;}
    }
  POP_SIGNAL;}


// The c++ function for: backtrack(n:integer) [0]
void  backtrack_integer(int n)
{ { CL_INT loop_handle = ClEnv->cHandle;
    while (((CL_INT)n < (CL_INT)world_number()))
    { world_pop();
      POP_SIGNAL;}
    }
  POP_SIGNAL;}


// allows to change the storage class
// The c++ function for: store(l:listargs) [SLOT_UPDATE+RETURN_ARG]
OID  store_listargs(listargs *l)
{ { OID Result = 0;
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(r);
      Result= Kernel.cfalse;
      for (START(l); NEXT(r);)
      if (INHERIT(OWNER(r),Kernel._relation))
       (OBJECT(ClaireRelation,r)->store_ask = CTRUE);
      else if (Kernel._string == OWNER(r))
       { OID  v = value_string(string_v(r));
        if (INHERIT(OWNER(v),Core._global_variable))
         (OBJECT(global_variable,v)->store_ask = CTRUE);
        }
      }
    POP_SIGNAL; return (Result);}
  }


// *********************************************************************
// *   Part 4: Methods for Native entities                             *
// *********************************************************************
//------------------- STRING -----------------------------------------------
//<sb> buffer
// The c++ function for: symbol!(self:string) [0]
symbol * symbol_I_string2(char *self)
{ POP_SIGNAL; return (symbol_I_string(self,claire.it));}


// The c++ function for: externC(s:string) [SAFE_RESULT]
void  externC_string(char *s)
{ close_exception(((general_error *) (*Core._general_error)(_string_("cannot execute C code: ~A"),
    _oid_(list::alloc(1,_string_(s))))));
  POP_SIGNAL;}


// The c++ function for: externC(s:string,c:class) [SAFE_RESULT]
OID  externC_string2(char *s,ClaireClass *c)
{ { OID Result = 0;
    { OID  V_CL0077;close_exception(((general_error *) (*Core._general_error)(_string_("cannot execute ~A"),
        _oid_(list::alloc(1,_string_(s))))));
      
      Result=_void_(V_CL0077);}
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: externC_string2_type
ClaireType * externC_string2_type(ClaireType *s,ClaireType *c)
{ POP_SIGNAL; return (member_type(c));}


// The c++ function for: nth_get(s:string,n:integer,max:integer) [RETURN_ARG]
ClaireChar * nth_get_string(char *s,int n,int max)
{ { ClaireChar *Result ;
    { ClaireObject *V_CC ;
      if ((CL_INT)n <= (CL_INT)max)
       V_CC = _char_(s[n - 1]);
      else close_exception(((general_error *) (*Core._general_error)(_string_("Buffer string access"),
          _oid_(Kernel.nil))));
        Result= (ClaireChar *) V_CC;}
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: nth_put(s:string,n:integer,c:char,max:integer) [BAG_UPDATE+RETURN_ARG]
void  nth_put_string(char *s,int n,ClaireChar *c,int max)
{ if ((CL_INT)n <= (CL_INT)max)
   (s[n - 1] = (unsigned char) c->ascii);
  else close_exception(((general_error *) (*Core._general_error)(_string_("Buffer string access"),
      _oid_(Kernel.nil))));
    POP_SIGNAL;}


//  v3.2.14
//------------------- SYMBOL -----------------------------------------------
// The c++ function for: make_string(self:symbol) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
char * make_string_symbol(symbol *self)
{ print_in_string_void();
  princ_symbol(self);
  POP_SIGNAL; return (end_of_string_void());}


//princ(self:symbol) : any -> function!(princ_symbol)
// The c++ function for: self_print(self:symbol) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  self_print_symbol_Core(symbol *self)
{ princ_symbol(self->module_I->name);
  princ_string("/");
  print_any(_string_(string_I_symbol(self)));
  POP_SIGNAL;}


//c_princ(self:symbol) : any -> function!(c_princ_symbol)
//gensym(self:string) : symbol -> function!(gensym_string, NEW_ALLOC)
//--------------------- INTEGER -----------------------------------------
// The c++ function for: +(self:integer,x:integer) [RETURN_ARG]
int  _plus_integer(int self,int x)
{ POP_SIGNAL; return (_integer_((CL_INT)self+(CL_INT)x));}


// The c++ function for: +_integer_type
ClaireType * _plus_integer_type(ClaireType *self,ClaireType *x)
{ POP_SIGNAL; return (abstract_type_operation(Core._plus,self,x));}


// The c++ function for: -(self:integer,x:integer) [RETURN_ARG]
int  _dash_integer1(int self,int x)
{ POP_SIGNAL; return (((CL_INT)self-(CL_INT)x));}


// The c++ function for: -_integer1_type
ClaireType * _dash_integer1_type(ClaireType *self,ClaireType *x)
{ POP_SIGNAL; return (abstract_type_operation(Kernel._dash,self,x));}


//-(self:integer) : integer -> function!(ch_sign)
//float!(self:integer) : float -> function!(to_float)
//mod(self:integer,x:integer) : integer -> function!(mod_integer)
//less_code(n:integer,i:integer) : boolean -> function!(less_code_integer)
// The c++ function for: <<(x:integer,y:integer) [0]
int  _inf_inf_integer(int x,int y)
{ POP_SIGNAL; return ((int )((x << y)));}


// v3.3.16
// The c++ function for: >>(x:integer,y:integer) [0]
int  _sup_sup_integer(int x,int y)
{ POP_SIGNAL; return ((int )((x >> y)));}


// The c++ function for: and(x:integer,y:integer) [0]
int  and_integer(int x,int y)
{ POP_SIGNAL; return ((int )((x & y)));}


// The c++ function for: or(x:integer,y:integer) [0]
int  or_integer(int x,int y)
{ POP_SIGNAL; return ((int )((x | y)));}


// open-coded
// The c++ function for: <(self:integer,x:integer) [0]
ClaireBoolean * _inf_integer(int self,int x)
{ { ClaireBoolean *Result ;
    Result = (((CL_INT)self < (CL_INT)x) ?
      CTRUE :
      CFALSE );
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: <=(self:integer,x:integer) [0]
ClaireBoolean * _inf_equal_integer(int self,int x)
{ { ClaireBoolean *Result ;
    Result = (((CL_INT)self <= (CL_INT)x) ?
      CTRUE :
      CFALSE );
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: >(self:integer,x:integer) [0]
ClaireBoolean * _sup_integer(int self,int x)
{ { ClaireBoolean *Result ;
    Result = (((CL_INT)self > (CL_INT)x) ?
      CTRUE :
      CFALSE );
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: nth(self:integer,y:integer) [0]
ClaireBoolean * nth_integer(int self,int y)
{ { ClaireBoolean *Result ;
    Result = ((BCONTAIN(self,y)) ?
      CTRUE :
      CFALSE );
    POP_SIGNAL; return (Result);}
  }


// used by the logic
// The c++ function for: factor?(x:integer,y:integer) [0]
ClaireBoolean * factor_ask_integer(int x,int y)
{ POP_SIGNAL; return (equal(((OID)mod_integer(x,y)),((OID)0)));}


// The c++ function for: divide?(x:integer,y:integer) [0]
ClaireBoolean * divide_ask_integer(int x,int y)
{ POP_SIGNAL; return (equal(((OID)mod_integer(y,x)),((OID)0)));}


// The c++ function for: Id(x:any) [RETURN_ARG]
OID  Id_any(OID x)
{ POP_SIGNAL; return (x);}


// The c++ function for: Id_any_type
ClaireType * Id_any_type(ClaireType *x)
{ POP_SIGNAL; return (x);}


// The c++ function for: pair(x:any,y:any) [NEW_ALLOC]
list * pair_any(OID x,OID y)
{ POP_SIGNAL; return (list::alloc(2,x,y));}


// The c++ function for: pair_1(x:list) [RETURN_ARG]
OID  pair_1_list(list *x)
{ POP_SIGNAL; return ((*(x))[1]);}


// The c++ function for: pair_1_list_type
ClaireType * pair_1_list_type(ClaireType *x)
{ POP_SIGNAL; return (member_type(x));}


// The c++ function for: pair_2(x:list) [RETURN_ARG]
OID  pair_2_list(list *x)
{ POP_SIGNAL; return ((*(x))[2]);}


// The c++ function for: pair_2_list_type
ClaireType * pair_2_list_type(ClaireType *x)
{ POP_SIGNAL; return (member_type(x));}


//------------------------ FLOAT ---------------------------------------------
// The c++ function for: +(g0078:any,g0079:any) [0]
OID  _plus_float_(OID g0078,OID g0079)
{ return _float_(_plus_float(float_v(g0078),float_v(g0079)));}


// The c++ function for: +(self:float,x:float) [0]
double  _plus_float(double self,double x)
{ { double Result =0.0;
    { double  y = (self+x);
      Result = y;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: -(g0080:any,g0081:any) [0]
OID  _dash_float_(OID g0080,OID g0081)
{ return _float_(_dash_float(float_v(g0080),float_v(g0081)));}


// The c++ function for: -(self:float,x:float) [0]
double  _dash_float(double self,double x)
{ { double Result =0.0;
    { double  y = (self-x);
      Result = y;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: *(g0082:any,g0083:any) [0]
OID  _star_float_(OID g0082,OID g0083)
{ return _float_(_star_float(float_v(g0082),float_v(g0083)));}


// The c++ function for: *(self:float,x:float) [0]
double  _star_float(double self,double x)
{ { double Result =0.0;
    { double  y = (self*x);
      Result = y;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: /(g0084:any,g0085:any) [0]
OID  _7_float_(OID g0084,OID g0085)
{ return _float_(_7_float(float_v(g0084),float_v(g0085)));}


// The c++ function for: /(self:float,x:float) [0]
double  _7_float(double self,double x)
{ { double Result =0.0;
    { double  y = (self/x);
      Result = y;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: -(g0086:any) [NEW_ALLOC]
OID  _dash_float2_(OID g0086)
{ return _float_(_dash_float2(float_v(g0086)));}


// The c++ function for: -(self:float) [NEW_ALLOC]
double  _dash_float2(double self)
{ POP_SIGNAL; return (((-1.0)*self));}


// The c++ function for: sqrt(g0087:any) [0]
OID  sqrt_float_(OID g0087)
{ return _float_(sqrt_float(float_v(g0087)));}


// The c++ function for: sqrt(self:float) [0]
double  sqrt_float(double self)
{ { double Result =0.0;
    { double  y = sqrt(self);
      Result = y;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: ^(g0088:any,g0089:any) [NEW_ALLOC]
OID  _exp_float_(OID g0088,OID g0089)
{ return _float_(_exp_float(float_v(g0088),float_v(g0089)));}


// The c++ function for: ^(self:float,x:float) [NEW_ALLOC]
double  _exp_float(double self,double x)
{ { double Result =0.0;
    { double  y = 0.0;
      y = pow(self,x);
      Result = y;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: log(g0090:any) [NEW_ALLOC]
OID  log_float_(OID g0090)
{ return _float_(log_float(float_v(g0090)));}


// The c++ function for: log(self:float) [NEW_ALLOC]
double  log_float(double self)
{ { double Result =0.0;
    { double  y = 0.0;
      y = log(self);
      Result = y;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: mClaire/atan(g0091:any) [NEW_ALLOC]
OID  atan_float_(OID g0091)
{ return _float_(atan_float(float_v(g0091)));}


// The c++ function for: mClaire/atan(self:float) [NEW_ALLOC]
double  atan_float(double self)
{ { double Result =0.0;
    { double  y = 0.0;
      y = atan(self);
      Result = y;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: string!(g0092:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
char * string_I_float_(OID g0092)
{ return string_I_float(float_v(g0092));}


// The c++ function for: string!(self:float) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
char * string_I_float(double self)
{ print_in_string_void();
  princ_float(self);
  POP_SIGNAL; return (end_of_string_void());}


//--------- BAG --------------------------------------------------------
// The c++ function for: length(self:bag) [RETURN_ARG]
int  length_bag(bag *self)
{ POP_SIGNAL; return (self->length);}


// The c++ function for: nth(self:bag,x:integer) [RETURN_ARG]
OID  nth_bag(bag *self,int x)
{ { OID Result = 0;
    if (((CL_INT)x > 0) && 
        ((CL_INT)x <= (CL_INT)self->length))
     Result = (*(self))[x];
    else { OID  V_CL0093;close_exception(((general_error *) (*Core._general_error)(_string_("[41] nth[~S] out of scope for ~S"),
          _oid_(list::alloc(2,((OID)x),_oid_(self))))));
        
        Result=_void_(V_CL0093);}
      POP_SIGNAL; return (Result);}
  }


// The c++ function for: nth_bag_type
ClaireType * nth_bag_type(ClaireType *self,ClaireType *x)
{ GC_BIND;
  { ClaireType *Result ;
    Result = (((INHERIT(self->isa,Kernel._tuple)) && 
        (unique_ask_type(x) == CTRUE)) ?
      OBJECT(ClaireType,(*Kernel.nth)(_oid_(self),
        GC_OID(the_type(x)))) :
      member_type(self) );
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: nth_get(self:bag,x:integer) [RETURN_ARG]
OID  nth_get_bag(bag *self,int x)
{ POP_SIGNAL; return ((*(self))[x]);}


// The c++ function for: min(f:method,self:bag) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  min_method(method *f,bag *self)
{ { OID Result = 0;
    if (self->length != 0)
     { OID  x = (*(self))[1];
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(y);
        for (START(self); NEXT(y);)
        if ((OBJECT(ClaireBoolean,funcall_method2(f,y,x))) == CTRUE)
         x= y;
        }
      Result = x;
      }
    else { OID  V_CL0094;close_exception(((general_error *) (*Core._general_error)(_string_("[183] min of empty set is undefined"),
          _oid_(Kernel.nil))));
        
        Result=_void_(V_CL0094);}
      POP_SIGNAL; return (Result);}
  }


// The c++ function for: min_method_type
ClaireType * min_method_type(ClaireType *f,ClaireType *self)
{ POP_SIGNAL; return (member_type(self));}


// The c++ function for: max(f:method,self:bag) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  max_method(method *f,bag *self)
{ { OID Result = 0;
    if (self->length != 0)
     { OID  x = (*(self))[1];
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(y);
        for (START(self); NEXT(y);)
        if (boolean_I_any(funcall_method2(f,y,x)) != CTRUE)
         x= y;
        }
      Result = x;
      }
    else { OID  V_CL0095;close_exception(((general_error *) (*Core._general_error)(_string_("[183] max of empty set is undefined"),
          _oid_(Kernel.nil))));
        
        Result=_void_(V_CL0095);}
      POP_SIGNAL; return (Result);}
  }


// The c++ function for: max_method_type
ClaireType * max_method_type(ClaireType *f,ClaireType *self)
{ POP_SIGNAL; return (member_type(self));}


// there seems to be a difficulty with providing this method with the proper type ..
// The c++ function for: /+(x:bag,y:bag) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
list * _7_plus_bag(bag *x,bag *y)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { list *Result ;
    { list * l;
      { { ClaireObject *V_CC ;
          if (INHERIT(x->isa,Kernel._list))
           V_CC = copy_bag(x);
          else if (Kernel._set == x->isa)
           V_CC = list_I_set(((set *) x));
          else if (INHERIT(x->isa,Kernel._tuple))
           V_CC = list_I_tuple(((tuple *) x));
          else V_CC = CFALSE;
            l= (list *) V_CC;}
        GC_OBJECT(list,l);}
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(z);
        for (START(y); NEXT(z);)
        { GC_LOOP;
          GC__ANY(l = l->addFast((OID)z), 1);
          GC_UNLOOP; POP_SIGNAL;}
        }
      { ClaireType * _Zx = of_bag(x);
        ClaireType * _Zy = of_bag(y);
        Result = ((equal(_oid_(_Zx),_oid_(_Zy)) == CTRUE) ?
          cast_I_list1(l,_Zx) :
          cast_I_list1(l,U_type(of_bag(x),of_bag(y))) );
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//--------- LIST --------------------------------------------------------
// last element of a list
// The c++ function for: last(self:list) [RETURN_ARG]
OID  last_list(list *self)
{ { OID Result = 0;
    if ((CL_INT)self->length > 0)
     Result = (*(self))[self->length];
    else { OID  V_CL0096;close_exception(((general_error *) (*Core._general_error)(_string_("[41] car(nil) is undefined"),
          _oid_(Kernel.nil))));
        
        Result=_void_(V_CL0096);}
      POP_SIGNAL; return (Result);}
  }


// The c++ function for: last_list_type
ClaireType * last_list_type(ClaireType *self)
{ POP_SIGNAL; return (member_type(self));}


// remove the last element
// The c++ function for: rmlast(self:list) [RETURN_ARG]
list * rmlast_list(list *self)
{ delete_at_list(self,self->length);
  POP_SIGNAL; return (self);}


// The c++ function for: nth=(self:list,x:integer,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  nth_set_list(list *self,int x,OID y)
{ if (((CL_INT)x <= 0) || 
      ((CL_INT)x > (CL_INT)self->length)) 
  { { OID Result = 0;
      { OID  V_CL0097;close_exception(((general_error *) (*Core._general_error)(_string_("[41] nth[~S] out of scope for ~S"),
          _oid_(list::alloc(2,((OID)x),_oid_(self))))));
        
        Result=_void_(V_CL0097);}
      return (Result);}
     }
  else{ GC_BIND;
    { OID Result = 0;
      if (belong_to(y,_oid_(of_bag(self))) == CTRUE)
       Result = ((*(self))[x]=y);
      else { system_error * _CL_obj = ((system_error *) GC_OBJECT(system_error,new_object_class(Kernel._system_error)));
          (_CL_obj->index = 17);
          (_CL_obj->arg = y);
          (_CL_obj->value = _oid_(self));
          add_I_property(Kernel.instances,Kernel._system_error,11,_oid_(_CL_obj));
          { OID  V_CL0098;close_exception(_CL_obj);
            
            Result=_void_(V_CL0098);}
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  }


// v3.2.00
// the old LISP method
// The c++ function for: car(self:list) [RETURN_ARG]
OID  car_list(list *self)
{ { OID Result = 0;
    if ((CL_INT)self->length > 0)
     Result = (*(self))[1];
    else { OID  V_CL0099;close_exception(((general_error *) (*Core._general_error)(_string_("[41] car(nil) is undefined"),
          _oid_(Kernel.nil))));
        
        Result=_void_(V_CL0099);}
      POP_SIGNAL; return (Result);}
  }


// hashtable basics
// The c++ function for: hashlist(n:integer) [NEW_ALLOC]
list * hashlist_integer(int n)
{ GC_BIND;
  { list *Result ;
    { list * l = GC_OBJECT(list,make_list_integer(n,CNULL));
      CL_INT  u = ((CL_INT)((*(l))[0])-(CL_INT)3);
      { CL_INT  i = ((CL_INT)n+(CL_INT)1);
        CL_INT  g0100 = u;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)i <= (CL_INT)g0100))
          { l->addFast((OID)CNULL);
            ++i;
            POP_SIGNAL;}
          }
        }
      Result = l;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: hashsize(l:list) [0]
int  hashsize_list(list *l)
{ { CL_INT Result = 0;
    { CL_INT  x = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(y);
        for (START(l); NEXT(y);)
        if (y != CNULL)
         ++x;
        }
      Result = x;
      }
    POP_SIGNAL; return (Result);}
  }


// this method sorts a list according to an order
// The c++ function for: sort(f:method,self:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
list * sort_method(method *f,list *self)
{ quicksort_list(self,f,1,self->length);
  POP_SIGNAL; return (self);}


// v3.0.38: upgrade the quicksort algorithm with a better pivot selection cf.bag.cpp
// this is also proposed as a macro: cf. file.cl
// The c++ function for: quicksort(self:list,f:method,n:integer,m:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  quicksort_list(list *self,method *f,int n,int m)
{ if ((CL_INT)m > (CL_INT)n)
   { OID  x = (*(self))[n];
    if (m == ((CL_INT)n+(CL_INT)1))
     { if ((OBJECT(ClaireBoolean,funcall_method2(f,(*(self))[m],x))) == CTRUE)
       { ((*(self))[n]=(*(self))[m]);
        ((*(self))[m]=x);
        }
      }
    else { CL_INT  p = ((CL_INT)((CL_INT)m+(CL_INT)n)>>(CL_INT)1);
        CL_INT  q = n;
        x= (*(self))[p];
        if (p != n)
         ((*(self))[p]=(*(self))[n]);
        { CL_INT  p = ((CL_INT)n+(CL_INT)1);
          CL_INT  g0101 = m;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)p <= (CL_INT)g0101))
            { if ((OBJECT(ClaireBoolean,funcall_method2(f,(*(self))[p],x))) == CTRUE)
               { ((*(self))[n]=(*(self))[p]);
                ++n;
                if ((CL_INT)p > (CL_INT)n)
                 ((*(self))[p]=(*(self))[n]);
                }
              ++p;
              POP_SIGNAL;}
            }
          }
        ((*(self))[n]=x);
        quicksort_list(self,f,q,((CL_INT)n-(CL_INT)1));
        quicksort_list(self,f,((CL_INT)n+(CL_INT)1),m);
        }
      }
  POP_SIGNAL;}


// destructive method that build the powerset
// The c++ function for: build_powerset(self:list) [NEW_ALLOC+BAG_UPDATE]
set * build_powerset_list(list *self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { set *Result ;
    if (self->length != 0)
     { OID  x = (*(self))[1];
      set * l1 = GC_OBJECT(set,build_powerset_list(skip_list(self,1)));
      set * l2 = l1;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(y);
        for (START(l1); NEXT(y);)
        { GC_LOOP;
          GC__ANY(l2 = l2->addFast((OID)GC_OID(_oid_(append_set(set::alloc(1,x),OBJECT(set,y))))), 1);
          GC_UNLOOP; POP_SIGNAL;}
        }
      Result = l2;
      }
    else Result = set::alloc(Kernel.emptySet,1,_oid_(Kernel.emptySet));
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// <<(x:list,y:integer) : list -> function!(skip_list) // v3.3.16
// new and useful (v3.1.06)
// The c++ function for: make_copy_list(n:integer,d:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
list * make_copy_list_integer(int n,OID d)
{ GC_BIND;
  { list *Result ;
    { list * l = GC_OBJECT(list,make_list_integer(n,d));
      if (INHERIT(OWNER(d),Kernel._bag))
       { CL_INT  i = 1;
        CL_INT  g0102 = n;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)i <= (CL_INT)g0102))
          { ((*(l))[i]=_oid_(copy_bag(OBJECT(bag,d))));
            ++i;
            POP_SIGNAL;}
          }
        }
      Result = l;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//----------------------  SET  ---------------------------------------------
// The c++ function for: difference(self:set,x:set) [NEW_ALLOC]
set * difference_set(set *self,set *x)
{ GC_BIND;
  { set *Result ;
    { bag * y_in = self;
      set * y_out = ((set *) empty_bag(y_in));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(y);
        for (START(y_in); NEXT(y);)
        if (contain_ask_set(x,y) != CTRUE)
         y_out->addFast((OID)y);
        }
      Result = GC_OBJECT(set,y_out);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//--------- ARRAY --------------------------------------------------------
// The c++ function for: nth=(self:array,x:integer,y:any) [RETURN_ARG]
void  nth_equal_array(OID *self,int x,OID y)
{ if (belong_to(y,_oid_(of_array(self))) != CTRUE)
   close_exception(((general_error *) (*Core._general_error)(_string_("type mismatch for array update ~S, ~S"),
    _oid_(list::alloc(2,y,_array_(self))))));
  else if (((CL_INT)x > 0) && 
      ((CL_INT)x <= (CL_INT)self[0]))
   nth_put_array(self,x,y);
  else close_exception(((general_error *) (*Core._general_error)(_string_("nth[~S] out of scope for ~S"),
      _oid_(list::alloc(2,((OID)x),_array_(self))))));
    POP_SIGNAL;}


// The c++ function for: self_print(self:array) [NEW_ALLOC]
void  self_print_array_Core(OID *self)
{ princ_string("array<");
  print_any(_oid_(of_array(self)));
  princ_string(">[");
  princ_integer(self[0]);
  princ_string("]");
  POP_SIGNAL;}


//---------------------- CHAR --------------------------------------------
//printf("'~A'", self)
// The c++ function for: <=(c1:char,c2:char) [0]
ClaireBoolean * _inf_equal_char(ClaireChar *c1,ClaireChar *c2)
{ POP_SIGNAL; return (_inf_equal_integer(c1->ascii,c2->ascii));}


// three methods that are useful for debugging !
//<sb> imported from Reader/file.cl
// This is the good version of kill, the nasty one is dangerous ....
// these restrictions of kill explain the dependencies among objects
//
// The c++ function for: kill(self:object) [SLOT_UPDATE]
OID  kill_object(ClaireObject *self)
{ if (INHERIT(self->isa,Kernel._thing))
   put_symbol(CLREAD(thing,self,name),CNULL);
  (self->isa->instances = ((list *) delete_bag(self->isa->instances,_oid_(self))));
  POP_SIGNAL; return (_oid_(Kernel.emptySet));}


// The c++ function for: kill(self:class) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  kill_class(ClaireClass *self)
{ { CL_INT loop_handle = ClEnv->cHandle;
    while ((self->instances->length != 0))
    { (*Kernel.kill)((*(self->instances))[1]);
      POP_SIGNAL;}
    }
  { CL_INT loop_handle = ClEnv->cHandle;
    ITERATE(x);
    for (START(self->descendents); NEXT(x);)
    if (OBJECT(ClaireClass,x)->superclass == self)
     kill_class(OBJECT(ClaireClass,x));
    }
  POP_SIGNAL; return (kill_object(self));}


// The c++ function for: float!(g0103:string) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
OID  float_I_string_(char *g0103)
{ return _float_(float_I_string(g0103));}


// The c++ function for: float!(self:string) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
double  float_I_string(char *self)
{ GC_BIND;
  { double Result =0.0;
    { blob * p = GC_OBJECT(blob,blob_I_string1(self));
      ClaireBoolean * neg = ((self[1 - 1] == ((unsigned char)45 /* '-' */)) ? CTRUE : CFALSE);
      OID  x;
      { if (neg == CTRUE)
         p->getNext();
        p->getNext();
        x = (OID )(read_number_port(p));
        }
      fclose_device1(p);
      if (Kernel._float == OWNER(x))
       { Result = ((neg == CTRUE) ?
          (-(float_v(x))) :
          float_v(x) );
        }
      else if (INHERIT(OWNER(x),Kernel._integer))
       { Result = ((neg == CTRUE) ?
          (-to_float (x)) :
          to_float (x) );
        }
      else close_exception(((general_error *) (*Core._general_error)(_string_("[??] ~A is not a float"),
          _oid_(list::alloc(1,_string_(self))))));
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: unix?(_CL_obj:void) [0]
ClaireBoolean * unix_ask_void1()
{ POP_SIGNAL; return (((ClaireBoolean *) (ClaireBoolean *)(
#ifdef CLPC
CFALSE
#else
CTRUE
#endif
)));}


// The c++ function for: strffloat(g0104:string,g0105:any) [NEW_ALLOC]
char * strffloat_string1_(char *g0104,OID g0105)
{ return strffloat_string1(g0104,float_v(g0105));}


// The c++ function for: strffloat(f:string,d:float) [NEW_ALLOC]
char * strffloat_string1(char *f,double d)
{ char buf[1024];
  sprintf(buf,f,d);
  POP_SIGNAL; return (copy_string((char *)(buf)));}


//<sb> fork, when called in claire applies all existing on_fork
// restrictions that have the domain boolean.
// the on_fork callback is applied with true when in the child and
// false when in the parent process.
// under win32 it produce a system error.
// this is used by wcl in debug mode to build the report of its (sub)child(s)
// processes
// The c++ function for: fork(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
int  fork_void1()
{ { CL_INT loop_handle = ClEnv->cHandle;
    ITERATE(r);
    for (START(Core.on_fork->restrictions); NEXT(r);)
    if ((OBJECT(restriction,r)->domain->length == 1) && 
        ((*(OBJECT(restriction,r)->domain))[1] == _oid_(Kernel._void)))
     apply_method(OBJECT(method,r),list::alloc(1,_oid_(ClEnv)));
    }
  { CL_INT Result = 0;
    { list * l = Core.on_forked->restrictions;
      CL_INT  i = cfork_void1();
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(r);
        for (START(l); NEXT(r);)
        if ((OBJECT(restriction,r)->domain->length == 1) && 
            ((*(OBJECT(restriction,r)->domain))[1] == _oid_(Kernel._boolean)))
         apply_method(OBJECT(method,r),list::alloc(1,_oid_(equal(((OID)i),((OID)0)))));
        }
      Result = i;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: forker?(_CL_obj:void) [0]
ClaireBoolean * forker_ask_void1()
{ POP_SIGNAL; return (_I_equal_any(((OID)fork_void1()),((OID)0)));}


// The c++ function for: forked?(_CL_obj:void) [0]
ClaireBoolean * forked_ask_void1()
{ POP_SIGNAL; return (equal(((OID)fork_void1()),((OID)0)));}



