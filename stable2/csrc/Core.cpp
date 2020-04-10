/***** CLAIRE Compilation of file ./meta/method.cl 
         [version 3.5.0 / safety 5] *****/

#include <claire.h>
#include <Kernel.h>
#include <dlfcn.h>

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllexport)
#endif
#include <Core.h>

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllimport)
#endif

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllexport)
#endif

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
// a root
// explicit definition of the functions that are used in method [to avoid out_of-place
// implicit definitions]
//find_which :: property() //<sb> moved in Kernel for hand-made optim
//<sb> a value that is used to fill the stack
// The c++ function for: mClaire/index_jump(n:integer) [0]
CL_EXPORT void  index_jump_integer1(CL_INT n) { 
  
		OID fill = _oid_(Core.undefined_debug);
		while (ClEnv->index <= n)
			ClEnv->stack[ClEnv->index++] = fill;
		ClEnv->index = n;
    POP_SIGNAL;}
  


// the eval_message is a method that tells how to handle the message.
// it used to be distributed in CLAIRE (so that it was extensible) and each
// definition was called the behavior of a kind of restriction
// int? tells us if this is an interpreted message
// The c++ function for: eval_message(self:property,r:object,start:integer,int?:boolean) [NEW_ALLOC+SLOT_UPDATE+SAFE_GC]
CL_EXPORT OID  eval_message_property(property *self,ClaireObject *r,CL_INT start,ClaireBoolean *int_ask) { 
    if (ClEnv->index + 100 >= ClAlloc->maxStack) error_execution_stack_full();
    { OID Result = 0;
      if (r->isa == Kernel._method)
       { if (ClEnv->debug_I != ((CL_INT)-1))
         Result = execute_method(((method *) r),start,int_ask);
        else { method * m = ((method *) r);
            if (((m->formula == (NULL)) ? CTRUE : CFALSE) != CTRUE)
             { CL_INT  retour = ClEnv->base;
              (ClEnv->base= ((OID)start));
              stack_add(m->formula->dimension);
              { OID  val = OPT_EVAL(m->formula->body);
                (ClEnv->base= ((OID)retour));
                (ClEnv->index= ((OID)start));
                Result = val;
                }
              }
            else Result = stack_apply_function(m->evaluate,m->srange,start,ClEnv->index);
              }
          }
      else if ((OWNER(_oid_(r)) == Kernel._slot) && 
          (ClEnv->index == ((CL_INT)start+(CL_INT)1)))
       { OID  val = get_slot(((slot *) r),OBJECT(ClaireObject,ClEnv->stack[((OID)start)]));
        if ((val == CNULL) && 
            (belong_to(val,_oid_(CLREAD(restriction,r,range))) != CTRUE))
         close_exception(((read_slot_error *) (*Core._read_slot_error)(ClEnv->stack[((OID)start)],
          _oid_(self))));
        (ClEnv->index= ((OID)start));
        Result = val;
        }
      else Result = noeval_message_property2(self,start);
        POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: noeval_message(self:property,start:integer) [NEW_ALLOC]
CL_EXPORT OID  noeval_message_property2(property *self,CL_INT start) { 
    
    GC_BIND;
    { OID Result = 0;
      { list * l = GC_OBJECT(list,get_args_integer(start));
        close_exception(((selector_error *) (*Core._selector_error)(_oid_(self),
          _oid_(l))));
        Result = Core.nil->value;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// a generic method : same as previously but (1) can be called by other methods
// and (2) takes care of the debugging piece, which implies a slower run (GC)
//<sb> changed debug handling
// The c++ function for: execute(self:method,start:integer,int?:boolean) [NEW_ALLOC]
CL_EXPORT OID  execute_method(method *self,CL_INT start,ClaireBoolean *int_ask) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  val = CNULL;
        CL_INT  n = self->domain->length;
        if (((self->formula == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         { CL_INT  retour = ClEnv->base;
          (ClEnv->base= ((OID)start));
          stack_add(self->formula->dimension);
          val= (OPT_EVAL(self->formula->body));
          (ClEnv->base= ((OID)retour));
          (ClEnv->index= ((OID)start));
          if (belong_to(val,_oid_(self->range)) != CTRUE)
           close_exception(((range_error *) (*Core._range_error)(_oid_(self),
            val,
            _oid_(self->range))));
          Result = val;
          }
        else { CL_INT  i = ClEnv->index;
            val= (stack_apply_function(self->evaluate,self->srange,start,i));
            if (belong_to(val,_oid_(self->range)) != CTRUE)
             close_exception(((range_error *) (*Core._range_error)(_oid_(self),
              val,
              _oid_(self->range))));
            Result = val;
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// the evaluator is open coded
// The c++ function for: eval(self:any) [NEW_ALLOC]
CL_EXPORT OID  eval_any(OID self) { 
    POP_SIGNAL; return (OPT_EVAL(self));}
  


// this is the standard evaluation
// The c++ function for: self_eval(self:object) [RETURN_ARG]
CL_EXPORT OID  self_eval_ClaireObject(ClaireObject *self) { 
    POP_SIGNAL; return (_oid_(self));}
  


// evaluation for a list or enumeration
// reads an inline definition for a method
// The c++ function for: inlineok?(self:method,s:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT]
CL_EXPORT method * inlineok_ask_method(method *self,char *s) { 
    
    GC_BIND;
    { ClaireHandler c_handle = ClaireHandler();
      if ERROR_IN 
      { { property * p = Core.read;
          OID  l = GC_OID((*Core.call)(_oid_(p),
            _string_(s)));
          _void_(self->inline_ask = CTRUE);
          update_property(Kernel.formula,
            self,
            8,
            Kernel._object,
            l);
          }
        ERROR_FREE;}
      else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
      { c_handle.catchIt();if (should_trace_ask_module1(Core.it,0) == CTRUE)
         mtformat_module1(Core.it,((char*)"`RED---- WARNING: inline definition of ~S is wrong\n"),0,list::alloc(1,_oid_(self)));
        else ;}
      else PREVIOUS_HANDLER;}
    { method *Result ;
      Result = self;
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// ****************************************************************
// *    Part 2: Update methods                                    *
// ****************************************************************
//get/put for a slot: should be inline
// @doc class
// get(s,x) returns the value of x associated with slot s
// The c++ function for: get(s:slot,x:object) [0]
CL_EXPORT OID  get_slot(slot *s,ClaireObject *x) { 
    POP_SIGNAL; return (slot_get_object(x,s->index,s->srange));}
  


// The c++ function for: put(s:slot,x:object,y:any) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  put_slot(slot *s,ClaireObject *x,OID y) { 
    POP_SIGNAL; return (store_object(x,
      s->index,
      s->srange,
      y,
      s->selector->store_ask));}
  


// reading a value from a property (unknown is allowed)
// @doc class
// get(self,x) is equivalent to self(x), but without any verification on unknown.
// The c++ function for: get(self:property,x:object) [NEW_ALLOC]
CL_EXPORT OID  get_property(property *self,ClaireObject *x) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
        if (Kernel._slot == s->isa)
         Result = slot_get_object(x,CLREAD(slot,s,index),CLREAD(slot,s,srange));
        else Result = CNULL;
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// a more general value that is useful for types
// The c++ function for: funcall(self:property,x:any) [NEW_ALLOC]
CL_EXPORT OID  funcall_property(property *self,OID x) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(x)));
        if (Kernel._slot == s->isa)
         Result = slot_get_object(OBJECT(ClaireObject,x),CLREAD(slot,s,index),CLREAD(slot,s,srange));
        else if (Kernel._method == s->isa)
         Result = funcall_method1(((method *) s),x);
        else Result = CNULL;
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// reading a value from a property (unknown is not allowed)
// @doc class
// read(self,x) is strictly equivalent to self(x) : it reads the value and raises an
// exception if it is unknown.
// The c++ function for: read(self:property,x:object) [NEW_ALLOC]
CL_EXPORT OID  read_property(property *self,ClaireObject *x) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
        if (Kernel._slot == s->isa)
         { OID  z = slot_get_object(x,CLREAD(slot,s,index),CLREAD(slot,s,srange));
          if ((z != CNULL) || 
              (belong_to(z,_oid_(CLREAD(restriction,s,range))) == CTRUE))
           Result = z;
          else { OID  V_CL0000;close_exception(((read_slot_error *) (*Core._read_slot_error)(_oid_(x),
                _oid_(self))));
              
              Result=_void_(V_CL0000);}
            }
        else { OID  V_CL0001;close_exception(((read_slot_error *) (*Core._read_slot_error)(_oid_(x),
              _oid_(self))));
            
            Result=_void_(V_CL0001);}
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// verifying
// The c++ function for: hold?(self:property,x:object,y:any) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * hold_ask_property(property *self,ClaireObject *x,OID y) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
        if (Kernel._slot == s->isa)
         { OID  z = slot_get_object(x,CLREAD(slot,s,index),CLREAD(slot,s,srange));
          Result = ((Kernel._set == OWNER(z)) ?
            contain_ask_set(OBJECT(set,z),y) :
            equal(y,z) );
          }
        else Result = CFALSE;
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// writing a single value into a slot & trigger rules
//  write = check + put + put_inverse + propagate
//  if_write = put + put_inverse + propagate  (propagate => if_write)
//  update = put + put_inverse
// @doc class
// This method is used to store a value in a slot of an object. write(p, x, y)
// is equivalent to p(x) := y.
// The c++ function for: write(self:property,x:object,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  write_property(property *self,ClaireObject *x,OID y) { 
    
    GC_BIND;
    { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
      if (Kernel._slot == s->isa)
       { if (belong_to(y,_oid_(CLREAD(restriction,s,range))) != CTRUE)
         range_is_wrong_slot(((slot *) s),y);
        else if (((CL_INT)self->open < (CL_INT)1) && 
            (slot_get_object(x,CLREAD(slot,s,index),CLREAD(slot,s,srange)) != CNULL))
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[132] Cannot change ~S(~S)")),
          _oid_(list::alloc(2,_oid_(self),_oid_(x))))));
        else if ((((self->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE) && 
            (multi_ask_any(_oid_(self)) != CTRUE))
         fastcall_relation2(self,_oid_(x),y);
        else update_property(self,
            x,
            CLREAD(slot,s,index),
            CLREAD(slot,s,srange),
            y);
          }
      else close_exception(((selector_error *) (*Core._selector_error)(_oid_(self),
          _oid_(list::alloc(1,_oid_(x))))));
        }
    ;GC_UNBIND; POP_SIGNAL;}
  


// the value does not belong to the range: error!
// The c++ function for: range_is_wrong(self:slot,y:any) [0]
CL_EXPORT OID  range_is_wrong_slot(slot *self,OID y) { 
    { OID Result = 0;
      { OID  V_CL0002;close_exception(((range_error *) (*Core._range_error)(_oid_(self),
          y,
          _oid_(self->range))));
        
        Result=_void_(V_CL0002);}
      POP_SIGNAL; return (Result);}
    }
  


// to remove
// The c++ function for: put(p:property,x:object,n:integer,s:class,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  put_property1(property *p,ClaireObject *x,CL_INT n,ClaireClass *s,OID y) { 
    if (should_trace_ask_module1(Core.it,0) == CTRUE)
     mtformat_module1(Core.it,((char*)"are you still using this dead thing (put instead of update) ??? !! \n"),0,list::empty());
    else ;update_property(p,
      x,
      n,
      s,
      y);
    POP_SIGNAL;}
  


// update (method called by the compiler)     // v3.0.20: renamed from put !
// update = put + put_inverse  (complex links)
// update uses two satellite methods: update+ and update-
// The c++ function for: mClaire/update(p:property,x:object,n:integer,s:class,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  update_property(property *p,ClaireObject *x,CL_INT n,ClaireClass *s,OID y) { 
    
    GC_BIND;
    { OID  old = slot_get_object(x,n,s);
      if (p->multivalued_ask != CFALSE)
       { if ((CL_INT)((CL_INT)(*Kernel.length)(old)) > (CL_INT)0)
         { bag * v;
          if (p->multivalued_ask == CTRUE)
           v = set::empty();
          else v = list::empty();
            if ((*Kernel.of)(old) != _oid_(Kernel._void))
           _oid_((INHERIT(v->isa,Kernel._list) ?
           (ClaireObject *) cast_I_list1((list *) OBJECT(list,_oid_(v)),OBJECT(ClaireType,GC_OID((*Kernel.of)(old)))) : 
           (ClaireObject *)  cast_I_set1((set *) OBJECT(set,_oid_(v)),OBJECT(ClaireType,GC_OID((*Kernel.of)(old))))));
          store_object(x,
            n,
            s,
            _oid_(v),
            p->store_ask);
          }
        { ClaireRelation * r = p->inverse;
          if (r == (NULL))
           ;else { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(z);
              for (START(OBJECT(bag,old)); NEXT(z);)
              update_dash_relation(r,z,_oid_(x));
              }
            }
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(z);
          for (START(OBJECT(set,y)); NEXT(z);)
          add_I_property(p,x,n,z);
          }
        }
      else if (equal(old,y) != CTRUE)
       { { ClaireRelation * r = p->inverse;
          if (r == (NULL))
           ;else if ((old != CNULL) && 
              ((r != p) || 
                  (equal(_oid_(x),old) != CTRUE)))
           update_dash_relation(r,old,_oid_(x));
          }
        store_object(x,
          n,
          s,
          y,
          p->store_ask);
        update_plus_relation(p,_oid_(x),y);
        }
      ;}
    GC_UNBIND; POP_SIGNAL;}
  


// this method checks the correctness of the inverse from a global view.
// The c++ function for: update+(self:relation,x:any,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  update_plus_relation(ClaireRelation *self,OID x,OID y) { 
    
    GC_BIND;
    { ClaireRelation * r = self->inverse;
      if ((r != NULL) && 
          ((r != self) || 
              (equal(x,y) != CTRUE)))
       { if (INHERIT(r->isa,Kernel._property))
         { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(((property *) r),OWNER(y)));
          if (Kernel._slot == s->isa)
           { OID  old_y = get_slot(((slot *) s),OBJECT(ClaireObject,y));
            if (r->multivalued_ask != CFALSE)
             add_value_property(((property *) r),
              OBJECT(ClaireObject,y),
              CLREAD(slot,s,index),
              OBJECT(bag,old_y),
              x);
            else store_object(OBJECT(ClaireObject,y),
                CLREAD(slot,s,index),
                CLREAD(slot,s,srange),
                x,
                r->store_ask);
              }
          else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[133] Inversion of ~S(~S,~S) impossible")),
              _oid_(list::alloc(3,_oid_(self),
                x,
                y)))));
            }
        else if (INHERIT(r->isa,Kernel._table))
         { OID  old_y = get_table(((table *) r),y);
          CL_INT  i = get_index_table1(((table *) r),y);
          if (r->multivalued_ask != CFALSE)
           add_value_array(((table *) r),i,OBJECT(bag,old_y),x);
          else { if (old_y != CNULL)
               update_dash_relation(self,old_y,y);
              store_list(((list *) CLREAD(table,r,graph)),i,x,r->store_ask);
              }
            }
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// this methods deletes a value in the inverse of a global_relation
// The c++ function for: update-(r:relation,x:any,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  update_dash_relation(ClaireRelation *r,OID x,OID y) { 
    
    GC_BIND;
    if (INHERIT(r->isa,Kernel._property))
     { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(((property *) r),OWNER(x)));
      if (Kernel._slot == s->isa)
       { OID  l = get_slot(((slot *) s),OBJECT(ClaireObject,x));
        OID  v;
        if (INHERIT(OWNER(l),Kernel._bag))
         v = _oid_(delete_bag(((r->store_ask == CTRUE) ?
          copy_bag(OBJECT(bag,l)) :
          OBJECT(bag,l) ),y));
        else v = CNULL;
          put_slot(((slot *) s),OBJECT(ClaireObject,x),v);
        }
      }
    else if (INHERIT(r->isa,Kernel._table))
     { OID  l = get_table(((table *) r),x);
      CL_INT  i = get_index_table1(((table *) r),x);
      OID  v;
      if (INHERIT(OWNER(l),Kernel._bag))
       v = _oid_(delete_bag(((r->store_ask == CTRUE) ?
        copy_bag(OBJECT(bag,l)) :
        OBJECT(bag,l) ),y));
      else v = CNULL;
        store_list(((list *) CLREAD(table,r,graph)),i,v,r->store_ask);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// this methods adds a value to a multi-slot (used by the compiler)
// this is the multi-valued equivalent of update
// The c++ function for: add!(self:property,x:object,n:integer,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  add_I_property(property *self,ClaireObject *x,CL_INT n,OID y) { 
    if (((self->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE)
     fastcall_relation2(self,_oid_(x),y);
    else { bag * l1 = OBJECT(bag,slot_get_object(x,n,Kernel._object));
        if (add_value_property(self,
          x,
          n,
          l1,
          y) == CTRUE)
         update_plus_relation(self,_oid_(x),y);
        }
      POP_SIGNAL;}
  


// this methods adds a value to a multi-slot (internal form)
// this is the multi-valued equivalent of put
// The c++ function for: add_value(self:property,x:object,n:integer,l:bag,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireBoolean * add_value_property(property *self,ClaireObject *x,CL_INT n,bag *l,OID y) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      if (Kernel._set == l->isa)
       { if (contain_ask_set(((set *) l),y) != CTRUE)
         { set * l1 = GC_OBJECT(set,((set *) ((self->store_ask == CTRUE) ?
            copy_bag(l) :
            l ))->addFast((OID)y));
          store_object(x,
            n,
            Kernel._object,
            _oid_(l1),
            self->store_ask);
          Result = CTRUE;
          }
        else Result = CFALSE;
          }
      else if (INHERIT(l->isa,Kernel._list))
       { if (self->store_ask == CTRUE)
         store_add(((list *) l),y);
        else ((list *) l)->addFast((OID)y);
          Result = CTRUE;
        }
      else Result = CFALSE;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// same method with error checking
// @doc class
// add(self,x,y) is equivalent to self(x) :add y
// (This form is interesting when one wants to write such an expression for a variable self)
// The c++ function for: add(self:property,x:object,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  add_property(property *self,ClaireObject *x,OID y) { 
    
    GC_BIND;
    { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
      if (boolean_I_any(_oid_(s)) != CTRUE)
       close_exception(((selector_error *) (*Core._selector_error)(_oid_(self),
        _oid_(list::alloc(1,_oid_(x))))));
      else if (multi_ask_any(_oid_(self)) != CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[134] Cannot apply add to ~S")),
        _oid_(list::alloc(1,_oid_(self))))));
      else if (belong_to(y,_oid_(member_type(CLREAD(restriction,s,range)))) == CTRUE)
       { if (((self->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE)
         fastcall_relation2(self,_oid_(x),y);
        else add_I_property(self,x,CLREAD(slot,s,index),y);
          }
      else range_is_wrong_slot(((slot *) s),y);
        }
    ;GC_UNBIND; POP_SIGNAL;}
  


// known ?
// @doc class
// known?(p, x) is equivalent to get(p, x) != unknown
// The c++ function for: known?(self:property,x:object) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * known_ask_property(property *self,ClaireObject *x) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
        Result = ((Kernel._slot == s->isa) ?
          _I_equal_any(slot_get_object(x,CLREAD(slot,s,index),CLREAD(slot,s,srange)),CNULL) :
          CFALSE );
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// @doc class
// unknown?(p, x) is equivalent to get(p, x) = unknown
// The c++ function for: unknown?(self:property,x:object) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * unknown_ask_property(property *self,ClaireObject *x) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
        Result = ((Kernel._slot == s->isa) ?
          equal(slot_get_object(x,CLREAD(slot,s,index),CLREAD(slot,s,srange)),CNULL) :
          CTRUE );
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// delete takes care of the inverse also
// @doc class
// delete(s, x) returns s if x is not in the list (resp. set) s without x otherwise.
// The c++ function for: delete(self:property,x:object,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  delete_property(property *self,ClaireObject *x,OID y) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
        if (boolean_I_any(_oid_(s)) != CTRUE)
         { OID  V_CL0003;close_exception(((selector_error *) (*Core._selector_error)(_oid_(self),
            _oid_(list::alloc(1,_oid_(x))))));
          
          Result=_void_(V_CL0003);}
        else { bag * l1 = OBJECT(bag,slot_get_object(x,CLREAD(slot,s,index),Kernel._object));
            bag * l = delete_bag(((self->store_ask == CTRUE) ?
              copy_bag(l1) :
              l1 ),y);
            store_object(x,
              CLREAD(slot,s,index),
              Kernel._object,
              _oid_(l),
              self->store_ask);
            { ClaireRelation * r = self->inverse;
              if (r != NULL)
               update_dash_relation(r,y,_oid_(x));
              }
            Result = _oid_(l);
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// erase is similar for mono-valued properties takes care of the inverse also
// v3.2.22: take care of multi-valued slot as well
// @doc class
// erase(p, x) removes the value associated to x with the property p.
// The default value, or the unknown value, is placed in the slot x.p,
// and the inverse if updated (if any).
// The c++ function for: erase(self:property,x:object) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  erase_property(property *self,ClaireObject *x) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
        if (boolean_I_any(_oid_(s)) != CTRUE)
         { OID  V_CL0004;close_exception(((selector_error *) (*Core._selector_error)(_oid_(self),
            _oid_(list::alloc(1,_oid_(x))))));
          
          Result=_void_(V_CL0004);}
        else { OID  y = slot_get_object(x,CLREAD(slot,s,index),OBJECT(ClaireClass,(*Kernel.srange)(_oid_(s))));
            if (self->multivalued_ask != CFALSE)
             { { ClaireRelation * r = self->inverse;
                if (r == (NULL))
                 ;else { CL_INT loop_handle = ClEnv->cHandle;
                    ITERATE(y1);
                    bag *y1_support;
                    y1_support = GC_OBJECT(bag,enumerate_any(y));
                    for (START(y1_support); NEXT(y1);)
                    update_dash_relation(r,y1,_oid_(x));
                    }
                  }
              { OID  l;
                { { OID  g0005UU;
                    { if (self->store_ask == CTRUE)
                       g0005UU = (*Kernel.copy)(y);
                      else g0005UU = y;
                        GC_OID(g0005UU);}
                    l = (*Kernel.shrink)(g0005UU,
                      ((OID)0));
                    }
                  GC_OID(l);}
                store_object(x,
                  CLREAD(slot,s,index),
                  Kernel._object,
                  l,
                  self->store_ask);
                Result = l;
                }
              }
            else { store_object(x,
                  CLREAD(slot,s,index),
                  OBJECT(ClaireClass,(*Kernel.srange)(_oid_(s))),
                  (*Kernel.DEFAULT)(_oid_(s)),
                  self->store_ask);
                { ClaireRelation * r = self->inverse;
                  if ((r != NULL) && 
                      (y != CNULL))
                   update_dash_relation(r,y,_oid_(x));
                  }
                Result = (*Kernel.DEFAULT)(_oid_(s));
                }
              }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: set_range(p:property,c:class,r:type) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  set_range_property(property *p,ClaireClass *c,ClaireType *r) { 
    { slot * s = ((slot *) _at_property1(p,c));
      _void_(s->range = r);
      _void_(s->srange = sort_I_type(r));
      }
    POP_SIGNAL;}
  


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
// The c++ function for: put_store(self:property,x:object,y:any,b:boolean) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  put_store_property2(property *self,ClaireObject *x,OID y,ClaireBoolean *b) { 
    
    GC_BIND;
    { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
      if (Kernel._slot == s->isa)
       { OID  z = slot_get_object(x,CLREAD(slot,s,index),CLREAD(slot,s,srange));
        if (equal(z,y) != CTRUE)
         store_object(x,
          CLREAD(slot,s,index),
          CLREAD(slot,s,srange),
          y,
          b);
        }
      else close_exception(((selector_error *) (*Core._selector_error)(_oid_(self),
          _oid_(list::alloc(1,_oid_(x))))));
        }
    GC_UNBIND; POP_SIGNAL;}
  


// tells if we have a multivalued relation
// The c++ function for: multi?(x:any) [0]
CL_EXPORT ClaireBoolean * multi_ask_any(OID x) { 
    { ClaireBoolean *Result ;
      Result = ((INHERIT(OWNER(x),Kernel._relation)) ?
        _I_equal_any(_oid_(OBJECT(ClaireRelation,x)->multivalued_ask),Kernel.cfalse) :
        CFALSE );
      POP_SIGNAL; return (Result);}
    }
  


// new: (v3.0) we have a simpler management of demons thus fastcall can be
// written in CLAIRE. A demon is either a lambda or a function, which
// arguments have precise sorts that match the relation sort
// the demon does everything: put + inverse + propagation
// thus write(R,x,y) <=> fastcall(R,x,y) <=> f(x,y)
// The c++ function for: fastcall(r:relation,x:any,y:any) [NEW_ALLOC]
CL_EXPORT void  fastcall_relation2(ClaireRelation *r,OID x,OID y) { 
    
    GC_BIND;
    { OID  f = r->if_write;
      if (INHERIT(OWNER(f),Core._lambda))
       (*Kernel.funcall)(f,
        x,
        y);
      else { OID  c1 = _oid_((INHERIT(r->domain->isa,Kernel._class) ?
           (ClaireObject *) sort_I_class((ClaireClass *) OBJECT(ClaireClass,_oid_(r->domain))) : 
           (ClaireObject *)  sort_I_type((ClaireType *) OBJECT(ClaireType,_oid_(r->domain)))));
          OID  c2 = _oid_((INHERIT(r->range->isa,Kernel._class) ?
           (ClaireObject *) sort_I_class((ClaireClass *) OBJECT(ClaireClass,_oid_(r->range))) : 
           (ClaireObject *)  sort_I_type((ClaireType *) OBJECT(ClaireType,_oid_(r->range)))));
          fcall2(OBJECT(ClaireFunction,f),
            OBJECT(ClaireClass,c1),
            x,
            OBJECT(ClaireClass,c2),
            y,
            Kernel._void);
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  


// *********************************************************************
// *   Part 3: Management of definition(p)                             *
// *********************************************************************
// the dictionarty slot
// insertion in the definition tree
// The c++ function for: insert_definition(p:property,r:restriction) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  insert_definition_property(property *p,restriction *r) { 
    _void_(p->definition = initialize_restriction1(r,class_I_type(OBJECT(ClaireType,(*(r->domain))[1])),p->definition));
    POP_SIGNAL;}
  


// insert a restriction with class-domain d into a property p
// The c++ function for: initialize(x:restriction,d:class,l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT list * initialize_restriction1(restriction *x,ClaireClass *d,list *l) { 
    { list *Result ;
      { property * p = x->selector;
        CL_INT  ix = p->dispatcher;
        if ((p->restrictions->length == 5) && 
            (uniform_property(p) == CTRUE))
         { { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(r);
            for (START(p->restrictions); NEXT(r);)
            hashinsert_restriction(OBJECT(restriction,r));
            }
          _void_(p->dictionary = CTRUE);
          }
        if (p->dictionary == CTRUE)
         { if (uniform_restriction(x) == CTRUE)
           { if (ClEnv->verbose == 4)
             { if (should_trace_ask_module1(Core.it,0) == CTRUE)
               mtformat_module1(Core.it,((char*)"--- hashinsert ~S \n"),0,list::alloc(1,_oid_(x)));
              else ;}
            hashinsert_restriction(x);
            }
          else _void_(p->dictionary = CFALSE);
            }
        if (((CL_INT)ix > (CL_INT)0) && 
            ((Kernel._method == x->isa) && (((CLREAD(method,x,evaluate) == (NULL)) ? CTRUE : CFALSE) != CTRUE)))
         { ClaireClass * c = domain_I_restriction(x);
          if ((uniform_property(p) == CTRUE) && 
              (INHERIT(c,Kernel._object)))
           { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(c2);
            for (START(c->descendents); NEXT(c2);)
            { { CL_INT loop_handle = ClEnv->cHandle;
                while (((CL_INT)((bag *) OBJECT(ClaireClass,c2)->dispatcher)->length < (CL_INT)ix))
                { ((list *) OBJECT(ClaireClass,c2)->dispatcher)->addFast((OID)((OID)0));
                  POP_SIGNAL;}
                }
              { ClaireBoolean * g0006I;
                { OID  g0007UU;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    ITERATE(y);
                    g0007UU= Kernel.cfalse;
                    for (START(p->restrictions); NEXT(y);)
                    if (y != _oid_(x))
                     { { ClaireBoolean * g0008I;
                        { OID  g0009UU;
                          { ClaireClass * c3 = domain_I_restriction(OBJECT(restriction,y));
                            g0009UU = _oid_(not_any(_oid_(((INHERIT(OBJECT(ClaireClass,c2),c3)) ? ((INHERIT(c3,c)) ? CTRUE: CFALSE): CFALSE))));
                            }
                          g0008I = not_any(g0009UU);
                          }
                        
                        if (g0008I == CTRUE) { g0007UU = Kernel.ctrue;
                            ClEnv->cHandle = loop_handle;break;}
                          }
                      }
                    }
                  g0006I = not_any(g0007UU);
                  }
                
                if (g0006I == CTRUE) ((*(((list *) OBJECT(ClaireClass,c2)->dispatcher)))[ix]=_oid_(CLREAD(method,x,evaluate)));
                  }
              }
            }
          else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Cannot create a non-uniform restriction ~S of interface ~S")),
              _oid_(list::alloc(2,_oid_(x),_oid_(p))))));
            }
        Result = initialize_restriction2(x,l);
        }
      POP_SIGNAL; return (Result);}
    }
  


// only uniform properties can use the dictionary representation
// The c++ function for: uniform(x:restriction) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * uniform_restriction(restriction *x) { 
    { ClaireBoolean *Result ;
      { list * l = x->domain;
        CL_INT  n = l->length;
        { OID  g0011UU;
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(r);
            g0011UU= Kernel.cfalse;
            for (START(x->selector->restrictions); NEXT(r);)
            { ClaireBoolean * g0012I;
              { OID  g0013UU;
                { list * l2 = OBJECT(restriction,r)->domain;
                  { ClaireBoolean * V_CL0014;{ ClaireBoolean *v_and;
                      { v_and = inherit_ask_class(OWNER((*(l))[1]),Kernel._class);
                        if (v_and == CFALSE) V_CL0014 =CFALSE; 
                        else { v_and = ((l2->length == n) ? CTRUE : CFALSE);
                          if (v_and == CFALSE) V_CL0014 =CFALSE; 
                          else { { OID  g0015UU;
                              { CL_INT  i = 2;
                                CL_INT  g0010 = n;
                                { CL_INT loop_handle = ClEnv->cHandle;
                                  g0015UU= _oid_(CFALSE);
                                  while (((CL_INT)i <= (CL_INT)g0010))
                                  { if (((equal((*(l))[i],(*(l2))[i]) == CTRUE) ? CTRUE : (((OWNER((*(l))[i]) != Kernel._class) && 
                                        ((OWNER((*(l))[i]) == OWNER((*(l2))[i])) && 
                                          (_equaltype_ask_any(OBJECT(ClaireType,(*(l))[i]),OBJECT(ClaireType,(*(l2))[i])) == CTRUE))) ? CTRUE : CFALSE)) != CTRUE)
                                     { g0015UU = Kernel.ctrue;
                                      ClEnv->cHandle = loop_handle;break;}
                                    ++i;
                                    POP_SIGNAL;}
                                  }
                                }
                              v_and = not_any(g0015UU);
                              }
                            if (v_and == CFALSE) V_CL0014 =CFALSE; 
                            else V_CL0014 = CTRUE;}
                          }
                        }
                      }
                    
                    g0013UU=_oid_(V_CL0014);}
                  }
                g0012I = not_any(g0013UU);
                }
              
              if (g0012I == CTRUE) { g0011UU = Kernel.ctrue;
                  ClEnv->cHandle = loop_handle;break;}
                }
            }
          Result = not_any(g0011UU);
          }
        }
      POP_SIGNAL; return (Result);}
    }
  


// v3.3.36      
// v3.0.54 check that a uniform property only uses methods !
// The c++ function for: uniform(p:property) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * uniform_property(property *p) { 
    { ClaireBoolean *Result ;
      { ClaireBoolean *v_and;
        { { OID  g0016UU;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(x);
              g0016UU= Kernel.cfalse;
              for (START(p->restrictions); NEXT(x);)
              if (equal(_oid_(Kernel._method),_oid_(OBJECT(ClaireObject,x)->isa)) != CTRUE)
               { g0016UU = Kernel.ctrue;
                ClEnv->cHandle = loop_handle;break;}
              }
            v_and = not_any(g0016UU);
            }
          if (v_and == CFALSE) Result =CFALSE; 
          else { v_and = ((p->restrictions->length != 0) ? CTRUE : CFALSE);
            if (v_and == CFALSE) Result =CFALSE; 
            else { v_and = uniform_restriction(OBJECT(restriction,(*(p->restrictions))[1]));
              if (v_and == CFALSE) Result =CFALSE; 
              else Result = CTRUE;}
            }
          }
        }
      POP_SIGNAL; return (Result);}
    }
  


//<sb> add test on p.restrictions
// insert a restriction in a list with the good order
// The c++ function for: initialize(x:restriction,l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT list * initialize_restriction2(restriction *x,list *l) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { list *Result ;
      { list * l1 = Kernel.nil;
        { CL_INT  i = 1;
          CL_INT  g0017 = l->length;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)i <= (CL_INT)g0017))
            { GC_LOOP;
              { list * l2 = OBJECT(restriction,(*(l))[i])->domain;
                if (tmatch_ask_list(x->domain,l2) == CTRUE)
                 { if (tmatch_ask_list(l2,x->domain) == CTRUE)
                   { ((*(l))[i]=_oid_(x));
                    GC__ANY(l1 = l, 1);
                    { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                    }
                  else { l1= (add_at_list(l,i,_oid_(x)));
                      { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                      }
                    }
                else if ((tmatch_ask_list(l2,x->domain) != CTRUE) && 
                    (join_list(x->domain,l2) == CTRUE))
                 { if (should_trace_ask_module1(Core.it,2) == CTRUE)
                   mtformat_module1(Core.it,((char*)"`BLUE---- Warning: ~S and ~S are conflicting\n"),2,GC_OBJECT(list,list::alloc(2,(*(l))[1],_oid_(x))));
                  else ;}
                }
              ++i;
              GC_UNLOOP;POP_SIGNAL;}
            }
          }
        Result = ((l1->length != 0) ?
          l1 :
          l->addFast((OID)_oid_(x)) );
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// definition of dictionary: standart hash-table
// The c++ function for: hashinsert(m:restriction) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  hashinsert_restriction(restriction *m) { 
    { OID Result = 0;
      { ClaireClass * c = domain_I_restriction(m);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(c2);
          Result= Kernel.cfalse;
          for (START(c->descendents); NEXT(c2);)
          hashinsert_class(OBJECT(ClaireClass,c2),((method *) m));
          }
        }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: hashinsert(c:class,x:method) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  hashinsert_class(ClaireClass *c,method *x) { 
    if (boolean_I_any(_oid_(c->dictionary)) != CTRUE)
     _void_(c->dictionary = hashlist_integer(29));
    _void_(c->dictionary = OBJECT(list,hashinsert_list(c->dictionary,x)));
    POP_SIGNAL; return (_oid_(c->dictionary));}
  


// v3.3.06: returns the new hash list when x is inserted (not necessarily the same list since l may grow)
// The c++ function for: hashinsert(l:list,x:method) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  hashinsert_list(list *l,method *x) { 
    
    GC_BIND;
    { OID Result = 0;
      { property * p = x->selector;
        CL_INT  i = hash_list(l,_oid_(p));
        CL_INT  m = l->length;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          Result= _oid_(CFALSE);
          while ((CTRUE == CTRUE))
          { GC_LOOP;
            { OID  li = (*(l))[i];
              if ((li == CNULL) || 
                  (OBJECT(method,li)->selector == p))
               { if ((li == CNULL) || 
                    (INHERIT(domain_I_restriction(x),domain_I_restriction(OBJECT(method,li)))))
                 ((*(l))[i]=_oid_(x));
                { GC_UNLOOP;Result = _oid_(l);
                  ClEnv->cHandle = loop_handle;break;}
                }
              else if (i == m)
               { if ((CL_INT)((CL_INT)hashsize_list(l)*(CL_INT)3) > (CL_INT)((CL_INT)l->length*(CL_INT)2))
                 { list * myl2;
                  { { list * g0018 = l;
                      list * g0019 = GC_OBJECT(list,make_list_integer(((CL_INT)(((CL_INT)(*(g0018))[0]))*(CL_INT)2),CNULL));
                      { CL_INT loop_handle = ClEnv->cHandle;
                        ITERATE(g0020);
                        for (START(g0018); NEXT(g0020);)
                        if (g0020 != CNULL)
                         hashinsert_list(g0019,OBJECT(method,g0020));
                        }
                      myl2 = g0019;
                      }
                    GC_OBJECT(list,myl2);}
                  { GC_UNLOOP;Result = hashinsert_list(myl2,x);
                    ClEnv->cHandle = loop_handle;break;}
                  }
                else i= (CL_INT)(1);
                  }
              else ++i;
                }
            GC_UNLOOP;POP_SIGNAL;}
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: hashget(c:class,p:property) [RETURN_ARG]
CL_EXPORT ClaireObject * hashget_class(ClaireClass *c,property *p) { 
    { ClaireObject *Result ;
      { list * l = c->dictionary;
        CL_INT  i = hash_list(l,_oid_(p));
        CL_INT  m = l->length;
        { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
            V_C= _oid_(CFALSE);
            while ((CTRUE == CTRUE))
            { { OID  x = (*(l))[i];
                if (x == CNULL)
                 { V_C = Kernel.cfalse;
                  ClEnv->cHandle = loop_handle;break;}
                else if (OBJECT(method,x)->selector == p)
                 { V_C = x;
                  ClEnv->cHandle = loop_handle;break;}
                else if (i == m)
                 i= (CL_INT)(1);
                else ++i;
                  }
              POP_SIGNAL;}
            }
          
          Result=OBJECT(ClaireObject,V_C);}
        }
      POP_SIGNAL; return (Result);}
    }
  


// look if two signature have a non-empty intersection
// note that the first case with classes is necessary for bootstraping
// The c++ function for: join(x:list,y:list) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * join_list(list *x,list *y) { 
    { ClaireBoolean *Result ;
      { CL_INT  n = x->length;
        { ClaireBoolean *v_and;
          { v_and = ((n == y->length) ? CTRUE : CFALSE);
            if (v_and == CFALSE) Result =CFALSE; 
            else { { OID  g0023UU;
                { CL_INT  i = 1;
                  CL_INT  g0021 = n;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    g0023UU= _oid_(CFALSE);
                    while (((CL_INT)i <= (CL_INT)g0021))
                    { if (boolean_I_any(_oid_(join_class(class_I_type(OBJECT(ClaireType,(*(x))[i])),class_I_type(OBJECT(ClaireType,(*(y))[i]))))) != CTRUE)
                       { g0023UU = Kernel.ctrue;
                        ClEnv->cHandle = loop_handle;break;}
                      ++i;
                      POP_SIGNAL;}
                    }
                  }
                v_and = not_any(g0023UU);
                }
              if (v_and == CFALSE) Result =CFALSE; 
              else { { OID  g0024UU;
                  { CL_INT  i = 1;
                    CL_INT  g0022 = n;
                    { CL_INT loop_handle = ClEnv->cHandle;
                      g0024UU= _oid_(CFALSE);
                      while (((CL_INT)i <= (CL_INT)g0022))
                      { if (boolean_I_any((*Core.glb)((*(x))[i],
                          (*(y))[i])) != CTRUE)
                         { g0024UU = Kernel.ctrue;
                          ClEnv->cHandle = loop_handle;break;}
                        ++i;
                        POP_SIGNAL;}
                      }
                    }
                  v_and = not_any(g0024UU);
                  }
                if (v_and == CFALSE) Result =CFALSE; 
                else Result = CTRUE;}
              }
            }
          }
        }
      POP_SIGNAL; return (Result);}
    }
  


// *********************************************************************
// *      Part 3: Matching Methods                                     *
// *********************************************************************
// find the correct restrictions to be applied on a given set
// This is also optimized because it is very useful (it returns false if none is found)
// The c++ function for: @(self:property,x:class) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT ClaireObject * _at_property1(property *self,ClaireClass *x) { 
    
    GC_BIND;
    { ClaireObject *Result ;
      if (self->dictionary == CTRUE)
       Result = hashget_class(x,self);
      else { OID  rx;
          { { OID  r_some = CNULL;
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(r);
                for (START(self->definition); NEXT(r);)
                if (INHERIT(x,class_I_type(OBJECT(ClaireType,(*(OBJECT(restriction,r)->domain))[1]))))
                 { r_some= (r);
                  ClEnv->cHandle = loop_handle; break;}
                }
              rx = r_some;
              }
            GC_OID(rx);}
          if (rx != CNULL)
           Result = OBJECT(ClaireObject,rx);
          else Result = CFALSE;
            }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// finds a property through its full domain
// The c++ function for: @(self:property,lt:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireObject * _at_property2(property *self,list *lt) { 
    
    GC_BIND;
    { ClaireObject *Result ;
      { ClaireObject *V_CC ;
        { OID  rx;
          { { OID  r_some = CNULL;
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(r);
                for (START(self->definition); NEXT(r);)
                if (tmatch_ask_list(lt,OBJECT(restriction,r)->domain) == CTRUE)
                 { r_some= (r);
                  ClEnv->cHandle = loop_handle; break;}
                }
              rx = r_some;
              }
            GC_OID(rx);}
          if (rx != CNULL)
           V_CC = OBJECT(ClaireObject,rx);
          else V_CC = CFALSE;
            }
        Result= (SystemObject *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// method's pattern matching
// The c++ function for: matching?(l:list,n:integer,m:integer) [SAFE_GC]
CL_EXPORT ClaireBoolean * matching_ask_list(list *l,CL_INT n,CL_INT m) { 
    { ClaireBoolean *Result ;
      { CL_INT  x = ((CL_INT)m-(CL_INT)n);
        CL_INT  z = l->length;
        if ((z == x) && 
            ((*(l))[x] != _oid_(Kernel._listargs)))
         { OID  g0027UU;
          { CL_INT  i = 1;
            CL_INT  g0025 = x;
            { CL_INT loop_handle = ClEnv->cHandle;
              g0027UU= _oid_(CFALSE);
              while (((CL_INT)i <= (CL_INT)g0025))
              { { CL_INT  y = ((CL_INT)((CL_INT)n-(CL_INT)1)+(CL_INT)i);
                  OID  u = (*(l))[i];
                  if ((OWNER(u) == Kernel._class) ? (inherit_ask_class(OWNER(ClEnv->stack[((OID)y)]),OBJECT(ClaireClass,u)) != CTRUE) : (vmatch_ask_any(u,ClEnv->stack[((OID)y)],n) != CTRUE))
                   { g0027UU = Kernel.ctrue;
                    ClEnv->cHandle = loop_handle;break;}
                  }
                ++i;
                POP_SIGNAL;}
              }
            }
          Result = not_any(g0027UU);
          }
        else if ((last_list(l) == _oid_(Kernel._listargs)) && 
            ((CL_INT)((CL_INT)z-(CL_INT)1) <= (CL_INT)x))
         { OID  g0028UU;
          { CL_INT  i = 1;
            CL_INT  g0026 = z;
            { CL_INT loop_handle = ClEnv->cHandle;
              g0028UU= _oid_(CFALSE);
              while (((CL_INT)i <= (CL_INT)g0026))
              { { CL_INT  y = ((CL_INT)((CL_INT)n-(CL_INT)1)+(CL_INT)i);
                  if ((*(l))[i] == _oid_(Kernel._listargs))
                   { (ClEnv->stack[((OID)y)]=_oid_(get_args_integer(y)));
                    (ClEnv->index= ((OID)((CL_INT)y+(CL_INT)1)));
                    { g0028UU = Kernel.cfalse;
                      ClEnv->cHandle = loop_handle;break;}
                    }
                  else if (vmatch_ask_any((*(l))[i],ClEnv->stack[((OID)y)],n) != CTRUE)
                   { g0028UU = Kernel.ctrue;
                    ClEnv->cHandle = loop_handle;break;}
                  }
                ++i;
                POP_SIGNAL;}
              }
            }
          Result = not_any(g0028UU);
          }
        else Result = CFALSE;
          }
      POP_SIGNAL; return (Result);}
    }
  


// type's pattern matching
// v3.0.65: use %type for Param
// The c++ function for: vmatch?(t:any,x:any,n:integer) [SAFE_GC]
CL_EXPORT ClaireBoolean * vmatch_ask_any(OID t,OID x,CL_INT n) { 
    { ClaireBoolean *Result ;
      if (INHERIT(OWNER(t),Kernel._class))
       Result = inherit_ask_class(OWNER(x),OBJECT(ClaireClass,t));
      else if (Kernel._set == OWNER(t))
       Result = contain_ask_set(OBJECT(set,t),x);
      else if (INHERIT(OWNER(t),Core._subtype))
       Result = (((OBJECT(subtype,t)->arg == Core._subtype) ? (INHERIT(OWNER(x),Kernel._type)) : (_Z_any1(x,OBJECT(subtype,t)->arg) == CTRUE)) ? (((OBJECT(ClaireBoolean,(*Core._inf_equalt)(x,
        _oid_(OBJECT(subtype,t)->t1)))) == CTRUE) ? CTRUE: CFALSE): CFALSE);
      else if (INHERIT(OWNER(t),Core._Param))
       { ClaireBoolean *v_and;
        { v_and = vmatch_ask_any(_oid_(OBJECT(Param,t)->arg),x,n);
          if (v_and == CFALSE) Result =CFALSE; 
          else { { OID  g0031UU;
              { CL_INT  i = 1;
                CL_INT  g0029 = OBJECT(Param,t)->params->length;
                { CL_INT loop_handle = ClEnv->cHandle;
                  g0031UU= _oid_(CFALSE);
                  while (((CL_INT)i <= (CL_INT)g0029))
                  { { ClaireBoolean * g0032I;
                      { OID  g0033UU;
                        { OID  _Zt = (*(OBJECT(Param,t)->args))[i];
                          OID  _Zv = funcall_property(OBJECT(property,(*(OBJECT(Param,t)->params))[i]),x);
                          if (Kernel._set == OWNER(_Zt))
                           g0033UU = _oid_(Ztype_any(_Zv,_Zt));
                          else g0033UU = _oid_(vmatch_ask_any(_Zt,_Zv,n));
                            }
                        g0032I = not_any(g0033UU);
                        }
                      
                      if (g0032I == CTRUE) { g0031UU = Kernel.ctrue;
                          ClEnv->cHandle = loop_handle;break;}
                        }
                    ++i;
                    POP_SIGNAL;}
                  }
                }
              v_and = not_any(g0031UU);
              }
            if (v_and == CFALSE) Result =CFALSE; 
            else Result = CTRUE;}
          }
        }
      else if (INHERIT(OWNER(t),Core._Reference))
       { OID  v = get_Reference(OBJECT(Reference,t),ClEnv->stack[((OID)((CL_INT)n+(CL_INT)OBJECT(Reference,t)->index))]);
        Result = ((OBJECT(Reference,t)->arg == CTRUE) ?
          equal(x,v) :
          belong_to(x,v) );
        }
      else if (INHERIT(OWNER(t),Kernel._tuple))
       { if (INHERIT(OWNER(x),Kernel._tuple))
         { ClaireBoolean *v_and;
          { v_and = ((OBJECT(bag,t)->length == OBJECT(bag,x)->length) ? CTRUE : CFALSE);
            if (v_and == CFALSE) Result =CFALSE; 
            else { { OID  g0034UU;
                { CL_INT  i = 1;
                  CL_INT  g0030 = OBJECT(bag,x)->length;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    g0034UU= _oid_(CFALSE);
                    while (((CL_INT)i <= (CL_INT)g0030))
                    { if (vmatch_ask_any((*(OBJECT(bag,t)))[i],(*(OBJECT(bag,x)))[i],n) != CTRUE)
                       { g0034UU = Kernel.ctrue;
                        ClEnv->cHandle = loop_handle;break;}
                      ++i;
                      POP_SIGNAL;}
                    }
                  }
                v_and = not_any(g0034UU);
                }
              if (v_and == CFALSE) Result =CFALSE; 
              else Result = CTRUE;}
            }
          }
        else Result = CFALSE;
          }
      else Result = belong_to(x,t);
        POP_SIGNAL; return (Result);}
    }
  


// method's pattern matching based on types (i.e. l2 is another list
// of types).
// The c++ function for: tmatch?(l:list,l2:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireBoolean * tmatch_ask_list(list *l,list *l2) { 
    { ClaireBoolean *Result ;
      { CL_INT  x = l2->length;
        CL_INT  z = l->length;
        if ((z != x) && 
            (((*(l2))[x] != _oid_(Kernel._listargs)) || 
                ((CL_INT)z < (CL_INT)((CL_INT)x-(CL_INT)1))))
         Result = CFALSE;
        else { OID  g0036UU;
            { CL_INT  i = 1;
              CL_INT  g0035 = x;
              { CL_INT loop_handle = ClEnv->cHandle;
                g0036UU= _oid_(CFALSE);
                while (((CL_INT)i <= (CL_INT)g0035))
                { if ((i == x) && 
                      ((*(l2))[i] == _oid_(Kernel._listargs)))
                   { g0036UU = Kernel.cfalse;
                    ClEnv->cHandle = loop_handle;break;}
                  else if (tmatch_ask_any((*(l))[i],(*(l2))[i],l) != CTRUE)
                   { g0036UU = Kernel.ctrue;
                    ClEnv->cHandle = loop_handle;break;}
                  ++i;
                  POP_SIGNAL;}
                }
              }
            Result = not_any(g0036UU);
            }
          }
      POP_SIGNAL; return (Result);}
    }
  


// types pattern matching (t is the variable and t2 the pattern)
// note that less is redefinable
// The c++ function for: tmatch?(t:any,mClaire/t2:any,l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireBoolean * tmatch_ask_any(OID t,OID t2,list *l) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      if (inherit_ask_class(OWNER(t),Kernel._type) != CTRUE)
       { if (should_trace_ask_module1(Core.it,0) == CTRUE)
         mtformat_module1(Core.it,((char*)"Warning: tmatch?(~S,~S,~S), ~S is not a type\n \n"),0,list::alloc(4,t,
          t2,
          _oid_(l),
          t));
        else ;Result = CFALSE;
        }
      else if (INHERIT(OWNER(t2),Kernel._class))
       { if (INHERIT(OWNER(t),Kernel._class))
         Result = inherit_ask_class(OBJECT(ClaireClass,t),OBJECT(ClaireClass,t2));
        else { ClaireType * ty1 = OBJECT(ClaireType,t);
            ClaireType * ty2 = OBJECT(ClaireType,t2);
            Result = OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core._inf_equalt->fcall(((CL_INT) ty1),((CL_INT) ty2))));
            }
          }
      else if (INHERIT(OWNER(t2),Core._subtype))
       Result = (((OBJECT(subtype,t2)->arg == Core._subtype) ? ((OBJECT(ClaireBoolean,(*Core._inf_equalt)(t,
        _oid_(Kernel._type)))) == CTRUE) : (tmatch_ask_any(t,_oid_(OBJECT(subtype,t2)->arg),l) == CTRUE)) ? ((tmatch_ask_any(GC_OID(_oid_(member_type(OBJECT(ClaireType,t)))),GC_OID(_oid_(OBJECT(subtype,t2)->t1)),l) == CTRUE) ? CTRUE: CFALSE): CFALSE);
      else if (INHERIT(OWNER(t2),Core._Param))
       { ClaireBoolean *v_and;
        { v_and = tmatch_ask_any(t,_oid_(OBJECT(Param,t2)->arg),l);
          if (v_and == CFALSE) Result =CFALSE; 
          else { { OID  g0039UU;
              { CL_INT  i = 1;
                CL_INT  g0037 = OBJECT(Param,t2)->params->length;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  g0039UU= _oid_(CFALSE);
                  while (((CL_INT)i <= (CL_INT)g0037))
                  { GC_LOOP;
                    if (tmatch_ask_any(GC_OID(_oid_(_at_type(OBJECT(ClaireType,t),OBJECT(property,(*(OBJECT(Param,t2)->params))[i])))),GC_OID((*(OBJECT(Param,t2)->args))[i]),l) != CTRUE)
                     { GC_UNLOOP;g0039UU = Kernel.ctrue;
                      ClEnv->cHandle = loop_handle;break;}
                    ++i;
                    GC_UNLOOP;POP_SIGNAL;}
                  }
                }
              v_and = not_any(g0039UU);
              }
            if (v_and == CFALSE) Result =CFALSE; 
            else Result = CTRUE;}
          }
        }
      else if (INHERIT(OWNER(t2),Core._Reference))
       { if (OBJECT(Reference,t2)->arg == CTRUE)
         Result = CFALSE;
        else { if (should_trace_ask_module1(Core.it,5) == CTRUE)
             mtformat_module1(Core.it,((char*)"question is ~S less than ~S ? \n"),5,GC_OBJECT(list,list::alloc(2,t,t2)));
            else ;Result = OBJECT(ClaireBoolean,(*Core._inf_equalt)(t,
              GC_OID(_at_Reference(OBJECT(Reference,t2),GC_OBJECT(list,OBJECT(Reference,t2)->args),(*(l))[((CL_INT)OBJECT(Reference,t2)->index+(CL_INT)1)]))));
            }
          }
      else if (INHERIT(OWNER(t2),Kernel._tuple))
       { if (INHERIT(OWNER(t),Kernel._tuple))
         { ClaireBoolean *v_and;
          { v_and = ((OBJECT(bag,t2)->length == OBJECT(bag,t)->length) ? CTRUE : CFALSE);
            if (v_and == CFALSE) Result =CFALSE; 
            else { { OID  g0040UU;
                { CL_INT  i = 1;
                  CL_INT  g0038 = OBJECT(bag,t2)->length;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    g0040UU= _oid_(CFALSE);
                    while (((CL_INT)i <= (CL_INT)g0038))
                    { if (tmatch_ask_any((*(OBJECT(bag,t)))[i],(*(OBJECT(bag,t2)))[i],l) != CTRUE)
                       { g0040UU = Kernel.ctrue;
                        ClEnv->cHandle = loop_handle;break;}
                      ++i;
                      POP_SIGNAL;}
                    }
                  }
                v_and = not_any(g0040UU);
                }
              if (v_and == CFALSE) Result =CFALSE; 
              else Result = CTRUE;}
            }
          }
        else Result = CFALSE;
          }
      else Result = OBJECT(ClaireBoolean,(*Core._inf_equalt)(t,
          t2));
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// find the restriction
//
// The c++ function for: find_which(l:list,c:class,n:integer,m:integer) [0]
CL_EXPORT ClaireObject * find_which_list1(list *l,ClaireClass *c,CL_INT n,CL_INT m) { 
    { ClaireObject *Result ;
      { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(r);
          V_C= Kernel.cfalse;
          for (START(l); NEXT(r);)
          if (matching_ask_list(OBJECT(restriction,r)->domain,n,m) == CTRUE)
           { V_C = r;
            ClEnv->cHandle = loop_handle;break;}
          }
        
        Result=OBJECT(ClaireObject,V_C);}
      POP_SIGNAL; return (Result);}
    }
  


// special version for super
// The c++ function for: find_which(c:class,l:list,n:integer,m:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireObject * find_which_class1(ClaireClass *c,list *l,CL_INT n,CL_INT m) { 
    { ClaireObject *Result ;
      { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(r);
          V_C= Kernel.cfalse;
          for (START(l); NEXT(r);)
          if ((_inf_equalt_class(c,OBJECT(ClaireType,(*(OBJECT(restriction,r)->domain))[1])) == CTRUE) && 
              (matching_ask_list(OBJECT(restriction,r)->domain,n,m) == CTRUE))
           { V_C = r;
            ClEnv->cHandle = loop_handle;break;}
          }
        
        Result=OBJECT(ClaireObject,V_C);}
      POP_SIGNAL; return (Result);}
    }
  



/***** CLAIRE Compilation of file ./meta/object.cl 
         [version 3.5.0 / safety 5] *****/


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
// The c++ function for: release(_CL_obj:void) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT char * release_void() { 
    
    GC_BIND;
    { char *Result ;
      Result = append_string(((char*)"3."),GC_STRING(string_I_float(ClEnv->version)));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// *********************************************************************
// *   Part 1: Ask, debug & trace                                      *
// *********************************************************************
// create the list of arguments if needed : allocate on the stack
// The c++ function for: mClaire/get_args(i:integer) [NEW_ALLOC]
CL_EXPORT list * get_args_integer(CL_INT i) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { list *Result ;
      { list * liste = list::empty(Kernel._any);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)i < (CL_INT)ClEnv->index))
          { GC_LOOP;
            GC__ANY(liste = liste->addFast((OID)GC_OID(ClEnv->stack[((OID)i)])), 1);
            ++i;
            GC_UNLOOP;POP_SIGNAL;}
          }
        Result = liste;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// evaluation of a message without the message structure, with a list
// of arguments. This method must be garbage-protected, because it is
// used as an entry point.
// to remove !!!!
// a simple method for a direct call with no argument
// The c++ function for: funcall(self:method,x:any) [NEW_ALLOC]
CL_EXPORT OID  funcall_method1(method *self,OID x) { 
    { OID Result = 0;
      { CL_INT  start = ClEnv->index;
        PUSH(x);
        Result = execute_method(self,start,CFALSE);
        }
      POP_SIGNAL; return (Result);}
    }
  


// this is a simple method for calling directly a method with one argument
// The c++ function for: funcall(self:method,x:any,y:any) [NEW_ALLOC]
CL_EXPORT OID  funcall_method2(method *self,OID x,OID y) { 
    { OID Result = 0;
      { CL_INT  start = ClEnv->index;
        PUSH(x);
        PUSH(y);
        Result = execute_method(self,start,CFALSE);
        }
      POP_SIGNAL; return (Result);}
    }
  


// this is a simple method for calling directly a method with two arguments
// The c++ function for: funcall(self:method,x:any,y:any,z:any) [NEW_ALLOC]
CL_EXPORT OID  funcall_method3(method *self,OID x,OID y,OID z) { 
    { OID Result = 0;
      { CL_INT  start = ClEnv->index;
        PUSH(x);
        PUSH(y);
        PUSH(z);
        Result = execute_method(self,start,CFALSE);
        }
      POP_SIGNAL; return (Result);}
    }
  


// how to apply a function to a list
// @doc calls
// apply(self,ls,l) applies the function self to the argument list l, where
// ls is the list of sort of the arguments and the result (i.e. length(ls) = length(l) + 1).
// For instance, if self is the external function that defines + @ integer :
// \code
// apply(f, list(integer,integer,integer), list(1,2)) -> 1 + 2
// \/code
// The c++ function for: apply(self:function,ls:list,l:list) [0]
CL_EXPORT OID  apply_function(ClaireFunction *self,list *ls,list *l) { 
    { OID Result = 0;
      { CL_INT  start = ClEnv->index;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(x);
          for (START(l); NEXT(x);)
          PUSH(x);
          }
        Result = stack_apply_function(self,ls,start,ClEnv->index);
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc calls
// call(p, x1, x2, ..., xn) is equivalent to apply(p, list(x1 ,x2 , ... , xn)).
// The c++ function for: call(p:property,l:listargs) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT OID  call_property(property *p,listargs *l) { 
    POP_SIGNAL; return (apply_property(p,l));}
  


// @doc calls
// apply(p,l) is equivalent to a function call where the selector is p and the argument
// list is l. For instance the following expressions are equivalent :
// \code
// apply(+, list(1,2)) -> 3
// 1 + 2 -> 3
// call(+, 1, 2) -> 3
// \/code
// The c++ function for: apply(p:property,l:list) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT OID  apply_property(property *p,list *l) { 
    { OID Result = 0;
      { CL_INT  start = ClEnv->index;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(x);
          for (START(l); NEXT(x);)
          PUSH(x);
          }
        Result = eval_message_property(p,find_which_property1(p,start,OWNER((*(l))[1])),start,CFALSE);
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc calls
// apply(m,lx) applies the method m to the argument list lx.
// For instance the following expressions are equivalent :
// \code
// apply(+ @ integer, list(1, 3)) -> 4
// 1 + 3 -> 4
// \/code
// The c++ function for: apply(m:method,l:list) [NEW_ALLOC]
CL_EXPORT OID  apply_method(method *m,list *l) { 
    { OID Result = 0;
      { CL_INT  start = ClEnv->index;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(x);
          for (START(l); NEXT(x);)
          PUSH(x);
          }
        Result = execute_method(m,start,CFALSE);
        }
      POP_SIGNAL; return (Result);}
    }
  


// *********************************************************************
// *   Part 2: Tables                                                  *
// *********************************************************************
// finds if objects are identified
// The c++ function for: identified?(self:class) [0]
CL_EXPORT ClaireBoolean * identified_ask_class(ClaireClass *self) { 
    POP_SIGNAL; return (((self == Kernel._integer) ? CTRUE : ((INHERIT(self,Kernel._object)) ? CTRUE : ((self == Kernel._symbol) ? CTRUE : ((self == Kernel._boolean) ? CTRUE : ((self == Kernel._char) ? CTRUE : CFALSE))))));}
  


// The c++ function for: identical?(x:any,y:any) [0]
CL_EXPORT ClaireBoolean * identical_ask_any(OID x,OID y) { 
    POP_SIGNAL; return (((ClaireBoolean *) (ClaireBoolean *)(((x == y) ? CTRUE : CFALSE))));}
  


//  let x1: (if ((x as boolean) = (y as boolean)) true else false)
// writing a single value into a slot but does NOT trigger the rules !
// equivalent to is! of LAURE
// this definition should not be placed in the method.cl file
// (it requires some inheritance conflict processing)
// The c++ function for: put(self:property,x:object,y:any) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  put_property2(property *self,ClaireObject *x,OID y) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
        if (Kernel._slot == s->isa)
         Result = store_object(x,
          CLREAD(slot,s,index),
          CLREAD(slot,s,srange),
          y,
          self->store_ask);
        else { OID  V_CL0041;close_exception(((selector_error *) (*Core._selector_error)(_oid_(self),
              _oid_(list::alloc(1,_oid_(x))))));
            
            Result=_void_(V_CL0041);}
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// v3.2 : same but multi valued
// The c++ function for: add_value(self:property,x:object,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  add_value_property3(property *self,ClaireObject *x,OID y) { 
    
    GC_BIND;
    { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
      if (boolean_I_any(_oid_(s)) != CTRUE)
       close_exception(((selector_error *) (*Core._selector_error)(_oid_(self),
        _oid_(list::alloc(1,_oid_(x))))));
      else if (multi_ask_any(_oid_(self)) != CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[134] Cannot apply add to ~S")),
        _oid_(list::alloc(1,_oid_(self))))));
      else { CL_INT  n = CLREAD(slot,s,index);
          bag * l1 = OBJECT(bag,slot_get_object(x,n,Kernel._object));
          add_value_property(self,
            x,
            n,
            l1,
            y);
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  


// access
// The c++ function for: nth(a:table,x:any) [0]
CL_EXPORT OID  nth_table1(table *a,OID x) { 
    { OID Result = 0;
      { OID  p = a->params;
        if (belong_to(x,_oid_(a->domain)) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[135] ~S does not belong to the domain of ~S")),
          _oid_(list::alloc(2,x,_oid_(a))))));
        { OID  v;
          if (INHERIT(OWNER(p),Kernel._integer))
           v = (*(a->graph))[((CL_INT)(((CL_INT)x))-p)];
          else if (INHERIT(OWNER(p),Kernel._list))
           v = (*(a->graph))[get_index_table2(a,((CL_INT)(*(OBJECT(list,x)))[1]),((CL_INT)(*(OBJECT(list,x)))[2]))];
          else { CL_INT  i = index_table(a,x);
              v = (*(a->graph))[i];
              }
            if ((v != CNULL) || 
              (belong_to(v,_oid_(a->range)) == CTRUE))
           Result = v;
          else { OID  V_CL0042;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[138] the value ~S(~S) is unknown !")),
                _oid_(list::alloc(2,_oid_(a),x)))));
              
              Result=_void_(V_CL0042);}
            }
        }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: nth_table1_type
CL_EXPORT ClaireType * nth_table1_type(ClaireType *a,ClaireType *x) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (unique_ask_type(a) == CTRUE)
       Result = OBJECT(ClaireType,(*Kernel.range)(GC_OID(the_type(a))));
      else Result = Kernel._any;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: get(a:table,x:any) [RETURN_ARG]
CL_EXPORT OID  get_table(table *a,OID x) { 
    { OID Result = 0;
      { OID  p = a->params;
        if (belong_to(x,_oid_(a->domain)) != CTRUE)
         Result = CNULL;
        else { CL_INT  i = get_index_table1(a,x);
            Result = (*(a->graph))[i];
            }
          }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: get_table_type
CL_EXPORT ClaireType * get_table_type(ClaireType *a,ClaireType *x) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (unique_ask_type(a) == CTRUE)
       Result = U_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(GC_OID(the_type(a))))),set::alloc(Kernel.emptySet,1,CNULL));
      else Result = Kernel._any;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// interface update method for a[x] := y
// The c++ function for: nth=(a:table,x:any,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  nth_equal_table1(table *a,OID x,OID y) { 
    if (belong_to(x,_oid_(a->domain)) != CTRUE)
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[135] ~S does not belong to the domain of ~S")),
      _oid_(list::alloc(2,x,_oid_(a))))));
    if (belong_to(y,_oid_(a->range)) != CTRUE)
     close_exception(((range_error *) (*Core._range_error)(_oid_(a),
      y,
      _oid_(a->range))));
    nth_put_table(a,x,y);
    POP_SIGNAL;}
  


// internal form without checks
// equivalent of update = put + put_inverse
// The c++ function for: nth_put(a:table,x:any,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  nth_put_table(table *a,OID x,OID y) { 
    
    GC_BIND;
    if ((((a->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE) && 
        (multi_ask_any(_oid_(a)) != CTRUE))
     fastcall_relation2(a,x,y);
    else if (multi_ask_any(_oid_(a)) == CTRUE)
     { OID  r = GC_OID(get_property(Kernel.inverse,a));
      OID  old = get_table(a,x);
      { OID  g0043UU;
        { if ((old != CNULL) && 
              (OBJECT(set,old)->length == 0))
           g0043UU = old;
          else if (a->multivalued_ask == Kernel._list)
           g0043UU = _oid_(make_list_integer2(0,GC_OBJECT(ClaireType,member_type(a->range)),((OID)0)));
          else g0043UU = _oid_(Kernel.emptySet);
            GC_OID(g0043UU);}
        ((*(GC_OBJECT(list,((list *) a->graph))))[get_index_table1(a,x)]=g0043UU);
        }
      if ((r != CNULL) && 
          (old != CNULL))
       { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(z);
        bag *z_support;
        z_support = GC_OBJECT(bag,enumerate_any(old));
        for (START(z_support); NEXT(z);)
        update_dash_relation(OBJECT(ClaireRelation,r),z,x);
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(z);
        for (START(OBJECT(set,y)); NEXT(z);)
        add_I_table(a,x,z);
        }
      }
    else { OID  r = GC_OID(get_property(Kernel.inverse,a));
        OID  z = get_table(a,x);
        if (equal(z,y) != CTRUE)
         { if (r != CNULL)
           { OID  z = get_table(a,x);
            if ((z != CNULL) && 
                ((r != _oid_(a)) || 
                    (equal(x,z) != CTRUE)))
             update_dash_relation(OBJECT(ClaireRelation,r),z,x);
            }
          put_table(a,x,y);
          update_plus_relation(a,x,y);
          }
        }
      GC_UNBIND; POP_SIGNAL;}
  


// put does NOT update the inverse
// The c++ function for: put(a:table,x:any,y:any) [BAG_UPDATE]
CL_EXPORT void  put_table(table *a,OID x,OID y) { 
    { OID  p = a->params;
      OID  z = get_table(a,x);
      if (equal(z,y) != CTRUE)
       { if (INHERIT(OWNER(p),Kernel._integer))
         store_list(((list *) a->graph),((CL_INT)(((CL_INT)x))-p),y,a->store_ask);
        else if (INHERIT(OWNER(p),Kernel._list))
         store_list(((list *) a->graph),get_index_table2(a,((CL_INT)(*(OBJECT(list,x)))[1]),((CL_INT)(*(OBJECT(list,x)))[2])),y,a->store_ask);
        else { CL_INT  i = index_table(a,x);
            store_list(((list *) a->graph),i,y,a->store_ask);
            }
          ;}
      }
    POP_SIGNAL;}
  


// adds a value to a multi-valued table: interface method
// The c++ function for: add(a:table,x:any,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  add_table(table *a,OID x,OID y) { 
    if (belong_to(x,_oid_(a->domain)) != CTRUE)
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[135] ~S does not belong to the domain of ~S")),
      _oid_(list::alloc(2,x,_oid_(a))))));
    if (belong_to(y,_oid_(member_type(a->range))) != CTRUE)
     close_exception(((range_error *) (*Core._range_error)(_oid_(a),
      y,
      _oid_(a->range))));
    add_I_table(a,x,y);
    POP_SIGNAL;}
  


// adds a value to a multi-valued table: internal version without type checks
// The c++ function for: add!(a:table,x:any,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  add_I_table(table *a,OID x,OID y) { 
    
    GC_BIND;
    if (((a->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE)
     fastcall_relation2(a,x,y);
    else { OID  p = GC_OID(a->params);
        CL_INT  i = get_index_table1(a,x);
        bag * l = GC_OBJECT(bag,OBJECT(bag,(*(a->graph))[i]));
        if (add_value_array(a,i,l,y) == CTRUE)
         update_plus_relation(a,x,y);
        }
      GC_UNBIND; POP_SIGNAL;}
  


// this methods adds a value to a multi-slot (used by the compiler)
// The c++ function for: add_value(self:table,n:integer,l:bag,y:any) [NEW_ALLOC+BAG_UPDATE]
CL_EXPORT ClaireBoolean * add_value_array(table *self,CL_INT n,bag *l,OID y) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      if (self->multivalued_ask == CTRUE)
       { if (belong_to(y,_oid_(l)) != CTRUE)
         { set * l1 = GC_OBJECT(set,((set *) ((self->store_ask == CTRUE) ?
            copy_bag(l) :
            l ))->addFast((OID)y));
          store_list(((list *) self->graph),n,_oid_(l1),self->store_ask);
          Result = CTRUE;
          }
        else Result = CFALSE;
          }
      else { list * l1 = GC_OBJECT(list,((self->store_ask == CTRUE) ?
            store_add(((list *) l),y) :
            ((list *) l)->addFast((OID)y) ));
          store_list(((list *) self->graph),n,_oid_(l1),self->store_ask);
          Result = CTRUE;
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// a direct version (v3.2) that can be used in lieu of add!
// The c++ function for: add_value(self:table,x:any,y:any) [NEW_ALLOC+BAG_UPDATE]
CL_EXPORT void  add_value_table3(table *self,OID x,OID y) { 
    
    GC_BIND;
    { OID  p = self->params;
      CL_INT  i = get_index_table1(self,x);
      bag * l = GC_OBJECT(bag,OBJECT(bag,(*(self->graph))[i]));
      add_value_array(self,i,l,y);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// removes a value from an table
// The c++ function for: delete(a:table,x:any,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  delete_table(table *a,OID x,OID y) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  p = GC_OID(a->params);
        CL_INT  i = get_index_table1(a,x);
        set * l1 = GC_OBJECT(set,OBJECT(set,(*(a->graph))[i]));
        set * l;
        { bag *V_CC ;
          { bag * g0044UU;
            if (a->store_ask == CTRUE)
             g0044UU = (set *)copy_bag(l1);
            else g0044UU = l1;
              V_CC = delete_bag(g0044UU,y);
            }
          l= (set *) V_CC;}
        store_list(((list *) a->graph),i,_oid_(l),a->store_ask);
        { ClaireRelation * r = a->inverse;
          if (r != NULL)
           update_dash_relation(r,y,x);
          }
        Result = _oid_(l);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// direct access to 2-dim tables
// The c++ function for: nth(a:table,x:any,y:any) [0]
CL_EXPORT OID  nth_table2(table *a,OID x,OID y) { 
    { OID Result = 0;
      { OID  p = a->params;
        OID  v;
        if (INHERIT(OWNER(p),Kernel._list))
         { if (((belong_to(x,(*(((bag *) a->domain)))[1]) == CTRUE) ? ((belong_to(y,(*(((bag *) a->domain)))[2]) == CTRUE) ? CTRUE: CFALSE): CFALSE) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[135] ~S does not belong to the domain of ~S")),
            _oid_(list::alloc(2,x,_oid_(a))))));
          v = (*(a->graph))[get_index_table2(a,((CL_INT)x),((CL_INT)y))];
          }
        else v = ((OID)index_table2(a,x,y));
          if ((v != CNULL) || 
            (belong_to(v,_oid_(a->range)) == CTRUE))
         Result = v;
        else { OID  V_CL0045;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~S(~S) is unknown !")),
              _oid_(list::alloc(2,_oid_(a),x)))));
            
            Result=_void_(V_CL0045);}
          }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: nth_table2_type
CL_EXPORT ClaireType * nth_table2_type(ClaireType *a,ClaireType *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (unique_ask_type(a) == CTRUE)
       Result = OBJECT(ClaireType,(*Kernel.range)(GC_OID(the_type(a))));
      else Result = Kernel._any;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// sets a value in a 2-dim table
// The c++ function for: nth=(a:table,x:any,y:any,z:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  nth_equal_table2(table *a,OID x,OID y,OID z) { 
    
    GC_BIND;
    { OID  p = GC_OID(a->params);
      if (INHERIT(OWNER(p),Kernel._list))
       { if (((belong_to(x,(*(((bag *) a->domain)))[1]) == CTRUE) ? ((belong_to(y,(*(((bag *) a->domain)))[2]) == CTRUE) ? CTRUE: CFALSE): CFALSE) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[135] ~S does not belong to the domain of ~S")),
          _oid_(list::alloc(2,_oid_(list::alloc(2,x,y)),_oid_(a))))));
        if (belong_to(z,_oid_(a->range)) != CTRUE)
         close_exception(((range_error *) (*Core._range_error)(_oid_(a),
          z,
          _oid_(a->range))));
        if ((((a->inverse == (NULL)) ? CTRUE : CFALSE) != CTRUE) || 
            (((a->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE))
         nth_put_table(a,_oid_(list::alloc(2,x,y)),z);
        else store_list(((list *) a->graph),get_index_table2(a,((CL_INT)x),((CL_INT)y)),z,a->store_ask);
          }
      else nth_equal_table1(a,_oid_(tuple::alloc(2,x,y)),z);
        }
    GC_UNBIND; POP_SIGNAL;}
  


// v3.2.16 tuple(a,b) is not list(a,b) !
// The c++ function for: get_index(a:table,x:any) [RETURN_ARG]
CL_EXPORT CL_INT  get_index_table1(table *a,OID x) { 
    { CL_INT Result = 0;
      { OID  p = a->params;
        Result = ((INHERIT(OWNER(p),Kernel._integer)) ?
          ((CL_INT)(((CL_INT)x))-p) :
          ((INHERIT(OWNER(p),Kernel._list)) ?
            get_index_table2(a,((CL_INT)(*(OBJECT(list,x)))[1]),((CL_INT)(*(OBJECT(list,x)))[2])) :
            index_table(a,x) ) );
        }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: get_index(a:table,x:integer,y:integer) [RETURN_ARG]
CL_EXPORT CL_INT  get_index_table2(table *a,CL_INT x,CL_INT y) { 
    { CL_INT Result = 0;
      { list * p = OBJECT(list,a->params);
        Result = ((CL_INT)((CL_INT)((CL_INT)(((CL_INT)(*(p))[1]))*(CL_INT)x)+(CL_INT)y)-(CL_INT)(((CL_INT)(*(p))[2])));
        }
      POP_SIGNAL; return (Result);}
    }
  


// erase an table means to clean its graph so that it becomes empty.
// @doc tables
// erase(a) removes all value pairs contained in the table. This means that,
// on one hand, the value a[x] becomes unknown for each object x, and also
// that any references to an object from the table's domain or an associated
// value is lost, which may be useful to allow for complete garbage collection. 
// The c++ function for: erase(a:table) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  erase_table(table *a) { 
    
    GC_BIND;
    { OID  p = GC_OID(a->params);
      if (INHERIT(OWNER(p),Kernel._integer))
       { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(i);
        bag *i_support;
        i_support = GC_OBJECT(bag,enumerate_any(_oid_(a->domain)));
        for (START(i_support); NEXT(i);)
        { GC_LOOP;
          ((*(GC_OBJECT(list,((list *) a->graph))))[get_index_table1(a,i)]=GC_OID(a->DEFAULT));
          GC_UNLOOP; POP_SIGNAL;}
        }
      else if (INHERIT(OWNER(p),Kernel._list))
       { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(l);
        bag *l_support;
        l_support = GC_OBJECT(bag,enumerate_any(_oid_(a->domain)));
        for (START(l_support); NEXT(l);)
        { GC_LOOP;
          ((*(GC_OBJECT(list,((list *) a->graph))))[get_index_table2(a,((CL_INT)(*(OBJECT(bag,l)))[1]),((CL_INT)(*(OBJECT(bag,l)))[2]))]=GC_OID(a->DEFAULT));
          GC_UNLOOP; POP_SIGNAL;}
        }
      else { CL_INT  i = 1;
          CL_INT  g0046 = a->graph->length;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)i <= (CL_INT)g0046))
            { GC_LOOP;
              ((*(GC_OBJECT(list,((list *) a->graph))))[i]=CNULL);
              ++i;
              GC_UNLOOP;POP_SIGNAL;}
            }
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  


//
//<sb> add a nice self_print @ table
// The c++ function for: self_print(self:table) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_table1_Core(table *self) { 
    
    GC_BIND;
    princ_string(((char*)"<"));
    if (equal_string(self->name->name,((char*)"unamed")) != CTRUE)
     princ_string(self->name->name);
    princ_string(((char*)"["));
    { ClaireBoolean * first_ask = CTRUE;
      bag * g = GC_OBJECT(bag,self->graph);
      CL_INT  x = 1;
      CL_INT  g0047 = g->length;
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((CL_INT)x <= (CL_INT)g0047))
        { if ((mod_integer(((CL_INT)x+(CL_INT)2),2) == 1) && 
              ((*(g))[x] != CNULL))
           { if (first_ask == CTRUE)
             first_ask= (CFALSE);
            else princ_string(((char*)","));
              print_any((*(g))[x]);
            princ_string(((char*)" => "));
            print_any((*(g))[((CL_INT)x+(CL_INT)1)]);
            }
          ++x;
          POP_SIGNAL;}
        }
      }
    princ_string(((char*)"]>"));
    GC_UNBIND; POP_SIGNAL;}
  


// Our first table: a debugging tool which stores a list of stopping values
// *********************************************************************
//   Part 3: Demons & relations for the logic modules                  *
// *********************************************************************
// applying a lambda to one argument
// The c++ function for: funcall(self:lambda,x:any) [NEW_ALLOC]
CL_EXPORT OID  funcall_lambda1(lambda *self,OID x) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT  start = ClEnv->index;
        CL_INT  retour = ClEnv->base;
        (ClEnv->base= ((OID)start));
        PUSH(x);
        stack_add(self->dimension);
        { OID  val = GC_OID(OPT_EVAL(self->body));
          (ClEnv->base= ((OID)retour));
          (ClEnv->index= ((OID)start));
          Result = val;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// applying a lambda to two argument
// The c++ function for: funcall(self:lambda,x:any,y:any) [NEW_ALLOC]
CL_EXPORT OID  funcall_lambda2(lambda *self,OID x,OID y) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT  start = ClEnv->index;
        CL_INT  retour = ClEnv->base;
        (ClEnv->base= ((OID)start));
        PUSH(x);
        PUSH(y);
        stack_add(self->dimension);
        { OID  val = GC_OID(OPT_EVAL(self->body));
          (ClEnv->base= ((OID)retour));
          (ClEnv->index= ((OID)start));
          Result = val;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// applying a lambda to two argument
// The c++ function for: funcall(self:lambda,x:any,y:any,z:any) [NEW_ALLOC]
CL_EXPORT OID  funcall_lambda3(lambda *self,OID x,OID y,OID z) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT  start = ClEnv->index;
        CL_INT  retour = ClEnv->base;
        (ClEnv->base= ((OID)start));
        PUSH(x);
        PUSH(y);
        PUSH(z);
        stack_add(self->dimension);
        { OID  val = GC_OID(OPT_EVAL(self->body));
          (ClEnv->base= ((OID)retour));
          (ClEnv->index= ((OID)start));
          Result = val;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// for historical reasons
// dealing with inverse
// The c++ function for: check_inverse(%r1:any,%r2:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  check_inverse_any(OID _Zr1,OID _Zr2) { 
    
    GC_BIND;
    { ClaireRelation * r1 = OBJECT(ClaireRelation,_Zr1);
      ClaireRelation * r2 = OBJECT(ClaireRelation,_Zr2);
      _void_(r1->inverse = r2);
      _void_(r2->inverse = r1);
      final_relation(r1);
      final_relation(r2);
      if ((_inf_equal_type(r1->domain,GC_OBJECT(ClaireType,((multi_ask_any(_oid_(r2)) == CTRUE) ?
          member_type(r2->range) :
          r2->range ))) != CTRUE) || 
          (_inf_equal_type(r2->domain,GC_OBJECT(ClaireType,((multi_ask_any(_oid_(r1)) == CTRUE) ?
            member_type(r1->range) :
            r1->range ))) != CTRUE))
       close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[137] ~S and ~S cannot be inverses for one another")),
        _oid_(list::alloc(2,_oid_(r1),_oid_(r2))))));
      }
    GC_UNBIND; POP_SIGNAL;}
  


// very useful
// The c++ function for: invert(r:relation,x:any) [NEW_ALLOC]
CL_EXPORT bag * invert_relation(ClaireRelation *r,OID x) { 
    
    GC_BIND;
    { bag *Result ;
      { ClaireObject *V_CC ;
        { OID  r2 = GC_OID(get_property(Kernel.inverse,r));
          if (INHERIT(OWNER(r2),Kernel._table))
           { OID  v = nth_table1(OBJECT(table,r2),x);
            if (OBJECT(ClaireRelation,r2)->multivalued_ask != CFALSE)
             V_CC = OBJECT(bag,v);
            else V_CC = set::alloc(1,v);
              }
          else if (INHERIT(OWNER(r2),Kernel._property))
           { OID  v = GC_OID(get_property(OBJECT(property,r2),OBJECT(ClaireObject,x)));
            if (OBJECT(ClaireRelation,r2)->multivalued_ask != CFALSE)
             V_CC = OBJECT(bag,v);
            else V_CC = set::alloc(1,v);
              }
          else if (INHERIT(r->isa,Kernel._property))
           { if (r->multivalued_ask != CFALSE)
             { set * z_out = set::empty(Kernel.emptySet);
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(z);
                bag *z_support;
                z_support = GC_OBJECT(bag,enumerate_any(_oid_(r->domain)));
                for (START(z_support); NEXT(z);)
                if (belong_to(x,get_property(((property *) r),OBJECT(ClaireObject,z))) == CTRUE)
                 z_out->addFast((OID)z);
                }
              V_CC = GC_OBJECT(set,z_out);
              }
            else { set * z_out = set::empty(Kernel.emptySet);
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(z);
                  bag *z_support;
                  z_support = GC_OBJECT(bag,enumerate_any(_oid_(r->domain)));
                  for (START(z_support); NEXT(z);)
                  if (equal(get_property(((property *) r),OBJECT(ClaireObject,z)),x) == CTRUE)
                   z_out->addFast((OID)z);
                  }
                V_CC = GC_OBJECT(set,z_out);
                }
              }
          else if (INHERIT(r->isa,Kernel._table))
           { if (r->multivalued_ask != CFALSE)
             { set * z_out = set::empty(Kernel.emptySet);
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(z);
                bag *z_support;
                z_support = GC_OBJECT(bag,enumerate_any(_oid_(r->domain)));
                for (START(z_support); NEXT(z);)
                if (belong_to(x,nth_table1(((table *) r),z)) == CTRUE)
                 z_out->addFast((OID)z);
                }
              V_CC = GC_OBJECT(set,z_out);
              }
            else { set * z_out = set::empty(Kernel.emptySet);
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(z);
                  bag *z_support;
                  z_support = GC_OBJECT(bag,enumerate_any(_oid_(r->domain)));
                  for (START(z_support); NEXT(z);)
                  if (equal(nth_table1(((table *) r),z),x) == CTRUE)
                   z_out->addFast((OID)z);
                  }
                V_CC = GC_OBJECT(set,z_out);
                }
              }
          else V_CC = CFALSE;
            }
        Result= (bag *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// same: two useful methods that are used often
// The c++ function for: domain!(x:restriction) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT ClaireClass * domain_I_restriction(restriction *x) { 
    POP_SIGNAL; return (class_I_type(OBJECT(ClaireType,(*(x->domain))[1])));}
  


// The c++ function for: methods(d:class,r:class) [NEW_ALLOC]
CL_EXPORT set * methods_class(ClaireClass *d,ClaireClass *r) { 
    
    GC_BIND;
    { set *Result ;
      { set * m_out = set::empty(Kernel.emptySet);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(m);
          bag *m_support;
          m_support = Kernel._method->instances;
          for (START(m_support); NEXT(m);)
          if ((_inf_equal_type(OBJECT(ClaireType,(*(OBJECT(restriction,m)->domain))[1]),d) == CTRUE) && 
              (_inf_equal_type(OBJECT(restriction,m)->range,r) == CTRUE))
           m_out->addFast((OID)m);
          }
        Result = GC_OBJECT(set,m_out);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// sets the reified flag
// The c++ function for: reify(l:listargs) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  reify_listargs(listargs *l) { 
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(p);
      for (START(l); NEXT(p);)
      if (INHERIT(OWNER(p),Kernel._property))
       _void_(OBJECT(property,p)->reified = CTRUE);
      }
    POP_SIGNAL;}
  


// *********************************************************************
// *   Part 4: Basics of Exceptions                                    *
// *********************************************************************
// a generic error that is produced by the error(" ....") instruction
// The c++ function for: self_print(self:general_error) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_general_error_Core(general_error *self) { 
    
    GC_BIND;
    format_string(GC_STRING(string_v(self->cause)),GC_OBJECT(list,OBJECT(list,self->arg)));
    GC_UNBIND; POP_SIGNAL;}
  


// a read_slot error is produced when an unknown value is found
// The c++ function for: self_print(self:read_slot_error) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_read_slot_error_Core(read_slot_error *self) { 
    
    GC_BIND;
    format_string(((char*)"[138] The value of ~S(~S) is unknown"),list::alloc(2,GC_OID(self->wrong),GC_OID(self->arg)));
    GC_UNBIND; POP_SIGNAL;}
  


// range errors
// The c++ function for: self_print(self:range_error) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_range_error_Core(range_error *self) { 
    
    GC_BIND;
    format_string(((char*)"[139] ~S: range error, ~S does not belong? to ~S."),list::alloc(3,GC_OID(self->cause),
      GC_OID(self->arg),
      GC_OID(self->wrong)));
    GC_UNBIND; POP_SIGNAL;}
  


// selector errors
// The c++ function for: self_print(self:selector_error) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_selector_error_Core(selector_error *self) { 
    
    GC_BIND;
    { OID  p = GC_OID(self->selector);
      if (boolean_I_any(_oid_(OBJECT(property,p)->restrictions)) != CTRUE)
       format_string(((char*)"[140] The property ~S is not defined (was applied to ~S)."),list::alloc(2,p,GC_OID(self->arg)));
      else format_string(((char*)"[141] ~S is a wrong arg list for ~S."),list::alloc(2,GC_OID(self->arg),p));
        }
    GC_UNBIND; POP_SIGNAL;}
  


// produced by a return (usually trapped)
// The c++ function for: self_print(self:return_error) [0]
CL_EXPORT void  self_print_return_error_Core(return_error *self) { 
    princ_string(((char*)"[142] return called outside of a loop (for or while)."));
    POP_SIGNAL;}
  


// a global variable is a named object with a special evaluation
// NOTE: we need to refine the scheme for global constants !
// GV are defeasible
// The c++ function for: close(self:global_variable) [SAFE_RESULT]
CL_EXPORT global_variable * close_global_variable(global_variable *self) { 
    if (((self->value == CNULL) ? CTRUE : (((Kernel._set == self->range->isa) || 
        (belong_to(self->value,_oid_(self->range)) == CTRUE)) ? CTRUE : CFALSE)) != CTRUE)
     close_exception(((range_error *) (*Core._range_error)(self->value,
      _oid_(self),
      _oid_(self->range))));
    POP_SIGNAL; return (self);}
  


// interpretation of all the error codes
// The c++ function for: self_print(self:system_error) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_system_error_Core(system_error *self) { 
    
    GC_BIND;
    { CL_INT  n = self->index;
      char * str_err;
      { ((*(GC_OBJECT(list,OBJECT(list,Core.err_l->value))))[1]=_oid_(OWNER(_oid_(self))));
        ((*(GC_OBJECT(list,OBJECT(list,Core.err_l->value))))[2]=((OID)n));
        format_string(((char*)"An internal error has occurred [~S:~A]:\n"),GC_OBJECT(list,OBJECT(list,Core.err_l->value)));
        if (n == 1)
         str_err = ((char*)"Dynamic allocation, item is too big (~S)");
        else if (n == 2)
         str_err = ((char*)"Dynamic allocation, too large for available memory (~S)");
        else if (n == 3)
         str_err = ((char*)"Object allocation, too large for available memory (~S)");
        else if (n == 4)
         str_err = ((char*)"Failed to load dynamic module ~A due to missing dependent module");
        else if (n == 5)
         str_err = ((char*)"nth[~S] outside of scope for ~S");
        else if (n == 7)
         str_err = ((char*)"Skip applied on ~S with a negative argument ~S");
        else if (n == 8)
         str_err = ((char*)"List operation: cdr(()) is undefined");
        else if (n == 9)
         str_err = ((char*)"String buffer is full: ~S");
        else if (n == 10)
         str_err = ((char*)"Cannot create an imported entity from NULL reference");
        else if (n == 11)
         str_err = ((char*)"nth_string[~S]: string too short ~S");
        else if (n == 12)
         str_err = ((char*)"Symbol Table table full");
        else if (n == 13)
         str_err = ((char*)"Cannot create a subclass for ~S [~A]");
        else if (n == 16)
         str_err = ((char*)"Temporary output string buffer too small");
        else if (n == 17)
         str_err = ((char*)"Bag Type Error: ~S cannot be added to ~S");
        else if (n == 18)
         str_err = ((char*)"Definition of ~S is in conflict with an object from ~S");
        else if (n == 19)
         str_err = ((char*)"Integer overflow");
        else if (n == 20)
         str_err = ((char*)"Integer arithmetic: division/modulo of ~A by 0");
        else if (n == 21)
         str_err = ((char*)"Integer to character: ~S is a wrong value");
        else if (n == 22)
         str_err = ((char*)"Cannote create a string with negative length ~S");
        else if (n == 23)
         str_err = ((char*)"Not enough memory to instal claire");
        else if (n == 24)
         str_err = ((char*)"Execution stack is full [~A]");
        else if (n == 26)
         str_err = ((char*)"Wrong usage of time counter [~A]");
        else if (n == 27)
         str_err = ((char*)"Internal garbage protection stack overflow (~S)");
        else if (n == 28)
         str_err = ((char*)"The multivalued status of ~S is not compatible with ~S");
        else if (n == 29)
         str_err = ((char*)"There is no module ~S");
        else if (n == 30)
         str_err = ((char*)"Attempt to read a private symbol ~S");
        else if (n == 31)
         str_err = ((char*)"External function not compiled yet");
        else if (n == 32)
         str_err = ((char*)"Too many arguments (~S) for function ~S");
        else if (n == 33)
         str_err = ((char*)"Exception handling: stack overflow");
        else if (n == 34)
         str_err = ((char*)"User interrupt: EXECUTION ABORTED");
        else if (n == 35)
         str_err = ((char*)"Reading char '~S': wrong char: ~S");
        else if (n == 36)
         str_err = ((char*)"Cannot open file ~A");
        else if (n == 37)
         str_err = ((char*)"World stack is full");
        else if (n == 38)
         str_err = ((char*)"Undefined access to ~S");
        else if (n == 39)
         str_err = ((char*)"Cannot convert ~S to an integer");
        else if (n == 40)
         str_err = ((char*)"Integer multiplication overflow with ~S and ~S");
        else if (n == 41)
         str_err = ((char*)"Wrong NTH access on ~S and ~S");
        else if (n == 42)
         str_err = ((char*)"Wrong array[~S] init value: ~S");
        else if (n == 43)
         str_err = ((char*)"Defeasible addition on list ~S requires pre-allocation (size ~S)");
        else if (n == 50)
         str_err = ((char*)"C++ imported error (~S) : ~S");
        else if (n == 57)
         str_err = ((char*)"Signal stack overflow");
        else if (n == 58)
         str_err = ((char*)"Invalid file operation");
        else if (n == 59)
         str_err = ((char*)"~S is an invalid index for external buffer");
        else if (n == 60)
         str_err = ((char*)"External buffer too long too be converted in a string");
        else if (n == 61)
         str_err = ((char*)"Failed to allocate external memory [~A]");
        else if (n == 62)
         str_err = ((char*)"Unescape premature end of string in [~A]");
        else if (n == 63)
         str_err = ((char*)"Unescape &#...; bad formater in [~A]");
        else if (n == 64)
         str_err = ((char*)"setenv(~A) failed");
        else if (n == 65)
         str_err = ((char*)"setcwd(~A) failed");
        else if (n == 66)
         str_err = ((char*)"pwd failed");
        else if (n == 67)
         str_err = ((char*)"Invalid index ~S for environ");
        else if (n == 68)
         str_err = ((char*)"Out of range category index ~S for setlocale, required in range (0 .. 5)");
        else if (n == 69)
         str_err = ((char*)"The given combination of category (~S) and locale (~A) makes no sense");
        else if (n == 70)
         str_err = ((char*)"The calendar time cannot be represented");
        else if (n == 71)
         str_err = ((char*)"Bad wildard formater after character '#' accept only '##' '#?' '#*'");
        else if (n == 72)
         str_err = ((char*)"Iteration of ~A/~A failed");
        else if (n == 73)
         str_err = ((char*)"Iteration of ~A/* failed");
        else if (n == 74)
         str_err = ((char*)"~A");
        else if (n == 75)
         str_err = ((char*)"~A not implemented on this machine");
        else if (n == 76)
         str_err = ((char*)"Invalid process id ~S");
        else if (n == 77)
         str_err = ((char*)"Could not create the process");
        else if (n == 78)
         str_err = ((char*)"unlink of ~A failed");
        else if (n == 79)
         str_err = ((char*)"Could not make new directory ~A with mode ~A");
        else if (n == 80)
         str_err = ((char*)"Could not remove directory ~A");
        else if (n == 81)
         str_err = ((char*)"Could not change mode of ~A to ~S");
        else if (n == 82)
         str_err = ((char*)"Could not create link with ~A and ~A");
        else if (n == 83)
         str_err = ((char*)"Could not create symbolic link with ~A and ~A");
        else if (n == 84)
         str_err = ((char*)"An error has occurred while copying file ~A to ~A");
        else if (n == 85)
         str_err = ((char*)"Can't get forked pid since you are not a forker");
        else if (n == 86)
         str_err = ((char*)"kill(~S,~S) failed");
        else if (n == 87)
         str_err = ((char*)"raise(~S) failed");
        else if (n == 88)
         str_err = ((char*)"setitimer(~S) failed");
        else if (n == 89)
         str_err = ((char*)"getitimer(~S) failed");
        else if (n == 90)
         str_err = ((char*)"The calendar time cannot be represented during the winter summer time transition");
        else if (n == 91)
         str_err = ((char*)"Incorrect access to file ~A in ~A");
        else if (n == 92)
         str_err = ((char*)"Operation attempted on a closed port");
        else if (n == 93)
         str_err = ((char*)"Attempt to close a standard port (~S)");
        else if (n == 94)
         str_err = ((char*)"lock failed on ~S");
        else if (n == 95)
         str_err = ((char*)"unlock failed on ~S");
        else if (n == 96)
         str_err = ((char*)"fcntl on ~S failed");
        else if (n == 97)
         str_err = ((char*)"~A error on ~S");
        else if (n == 98)
         str_err = ((char*)"Failed to create a pipe");
        else if (n == 99)
         str_err = ((char*)"Failed to move file ~A to ~A");
        else if (n == 100)
         str_err = ((char*)"There is no child process with pid ~S");
        else if (n == 101)
         str_err = ((char*)"Too much child process, failed to create process ~A (args: ~A)");
        else if (n == 101)
         str_err = ((char*)"No more process");
        else if (n == 102)
         str_err = ((char*)"Failed to load dynamic module ~A - ~A");
        else if (n == 103)
         str_err = ((char*)"Failed to load dynamic module ~A - unsupported");
        else { _void_(self->value = ((OID)n));
            str_err = ((char*)"What the hell is this ! [code: ~S^]");
            }
          }
      if (self->cerr == 0)
       { ((*(GC_OBJECT(list,OBJECT(list,Core.err_l->value))))[1]=GC_OID(self->value));
        ((*(GC_OBJECT(list,OBJECT(list,Core.err_l->value))))[2]=GC_OID(self->arg));
        format_string(str_err,GC_OBJECT(list,OBJECT(list,Core.err_l->value)));
        }
      else { ((*(GC_OBJECT(list,OBJECT(list,Core.err_l->value))))[1]=GC_OID(_string_(cerror_integer(self->cerr))));
          format_string(((char*)"[~A] "),GC_OBJECT(list,OBJECT(list,Core.err_l->value)));
          ((*(GC_OBJECT(list,OBJECT(list,Core.err_l->value))))[1]=GC_OID(self->value));
          ((*(GC_OBJECT(list,OBJECT(list,Core.err_l->value))))[2]=GC_OID(self->arg));
          format_string(str_err,GC_OBJECT(list,OBJECT(list,Core.err_l->value)));
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  


// contradictions are nice exceptions
// The c++ function for: self_print(x:contradiction) [0]
CL_EXPORT void  self_print_contradiction_Core(contradiction *x) { 
    princ_string(((char*)"A contradiction has occurred."));
    POP_SIGNAL;}
  


// the format method is used to print error messages (similar to a printf)
// @doc Printing
// This method does the same thing as printf, except that there are always two
// arguments, thus the arguments must be replaced by an explicit list. Unlike
// with the printf construction \i ~I \/i cannot be used in a format. Last the string
// s may contain color escapes.
// The c++ function for: format(self:string,larg:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  format_string(char *self,list *larg) { 
    { char * s = self;
      CL_INT  n = find_string2(s,((char*)"~"));
      CL_INT  nl = 1;
      CL_INT  idx = 1;
      CL_INT  len = LENGTH_STRING(s);
      CL_INT  col = (CL_INT )(current_color);
      CL_INT  bold = (CL_INT )(current_bold);
      CL_INT  ccol = col;
      CL_INT  cbold = bold;
      { CL_INT loop_handle = ClEnv->cHandle;
        while ((((CL_INT)0 < (CL_INT)n) && 
            ((CL_INT)n < (CL_INT)len)))
        { { ClaireChar * m = _char_(s[((CL_INT)n+(CL_INT)1) - 1]);
            if ((CL_INT)n > (CL_INT)1)
             { color_princ_string2(s,idx,((CL_INT)n-(CL_INT)1));
              {ccol = current_color; cbold = current_bold;};
              }
            if (((unsigned char)'A') == ((unsigned char) m->ascii))
             { color(30,0);
              (*Kernel.princ)((*(larg))[nl]);
              color(ccol,cbold);
              }
            else if (((unsigned char)'S') == ((unsigned char) m->ascii))
             { color(30,0);
              print_any((*(larg))[nl]);
              color(ccol,cbold);
              }
            else if (((unsigned char)'I') == ((unsigned char) m->ascii))
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[143] ~I not allowed in format")),
              _oid_(list::alloc(1,CNULL)))));
            if (((unsigned char) m->ascii) != ((unsigned char)'%'))
             ++nl;
            idx= (CL_INT)(((CL_INT)n+(CL_INT)2));
            n= (CL_INT)(find_string(s,((char*)"~"),idx));
            }
          POP_SIGNAL;}
        }
      if ((CL_INT)idx <= (CL_INT)len)
       color_princ_string2(s,idx,len);
      color(col,bold);
      }
    POP_SIGNAL;}
  


// special version that prints in the trace port
// The c++ function for: tformat(self:string,i:integer,l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  tformat_string(char *self,CL_INT i,list *l) { 
    
    GC_BIND;
    { OID Result = 0;
      if ((CL_INT)i <= (CL_INT)ClEnv->verbose)
       { ClaireBoolean * isforked_ask = ((ClaireBoolean *) (ClaireBoolean *)((isforked?CTRUE:CFALSE)));
        PortObject * p = use_as_output_port(ClEnv->ctrace);
        if (isforked_ask == CTRUE)
         self= (GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"["),GC_STRING(string_I_integer (getpid_void())))),((char*)"]"))),self)));
        format_string(self,l);
        Result = _oid_(use_as_output_port(p));
        }
      else Result = Kernel.cfalse;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> in xl claire we can define per module trace policy :
// if m.verbose is exactly true -> standard trace methods (tformat)
// if m.verbose is exactly false -> no trace at all
// if m.verbose is an integer -> like standard trace but we use m.verbose instead of system.verbose
// if m.verbose is a bag or an interval -> the trace line is generated if the trace level is in m.verbose
// The c++ function for: should_trace?(m:module,i:integer) [0]
CL_EXPORT ClaireBoolean * should_trace_ask_module1(module *m,CL_INT i) { 
    { ClaireBoolean *Result ;
      Result = (((INHERIT(OWNER(m->verbose),Kernel._integer)) && 
          ((CL_INT)i <= (CL_INT)((CL_INT)m->verbose))) ?
        CTRUE :
        ((((INHERIT(OWNER(m->verbose),Kernel._bag)) || 
              (INHERIT(OWNER(m->verbose),Core._Interval))) && 
            (belong_to(((OID)i),m->verbose) == CTRUE)) ?
          CTRUE :
          (((m->verbose == Kernel.ctrue) && 
              ((CL_INT)i <= (CL_INT)ClEnv->verbose)) ?
            CTRUE :
            CFALSE ) ) );
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: mtformat(m:module,self:string,i:integer,l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  mtformat_module1(module *m,char *self,CL_INT i,list *l) { 
    { OID Result = 0;
      if ((((ClEnv->ctrace == (NULL)) ? CTRUE : CFALSE) != CTRUE) && 
          ((m->verbose != Kernel.cfalse) && 
            (should_trace_ask_module1(m,i) == CTRUE)))
       { PortObject * p = use_as_output_port(ClEnv->ctrace);
        if ((((ClaireBoolean *) (ClaireBoolean *)((isforked?CTRUE:CFALSE)))) == CTRUE)
         { CL_INT  g0048 = (CL_INT )(current_color);
          CL_INT  g0049 = (CL_INT )(current_bold);
          CL_INT  g0050 = g0048;
          CL_INT  g0051 = g0049;
          color(g0048,g0049);
          color_princ_string1(((char*)"`RED["));
          g0048= (CL_INT)((CL_INT )(current_color));
          g0049= (CL_INT)((CL_INT )(current_bold));
          color(g0050,g0051);
          print_any(((OID)getpid_void()));
          color(g0048,g0049);
          color(g0048,g0049);
          color_princ_string1(((char*)"]"));
          color(g0050,g0051);
          }
        if (((equal_string(m->name->name,((char*)"claire")) == CTRUE) ? CTRUE : 
        ((equal_string(m->name->name,((char*)"Core")) == CTRUE) ? CTRUE : 
        ((equal_string(m->name->name,((char*)"Reader")) == CTRUE) ? CTRUE : 
        ((equal_string(m->name->name,((char*)"Language")) == CTRUE) ? CTRUE : 
        ((equal_string(m->name->name,((char*)"Generate")) == CTRUE) ? CTRUE : 
        ((equal_string(m->name->name,((char*)"Optimize")) == CTRUE) ? CTRUE : 
        CFALSE)))))) != CTRUE)
         { CL_INT  g0052 = (CL_INT )(current_color);
          CL_INT  g0053 = (CL_INT )(current_bold);
          CL_INT  g0054 = g0052;
          CL_INT  g0055 = g0053;
          color(g0052,g0053);
          color_princ_string1(((char*)"`GREEN["));
          g0052= (CL_INT)((CL_INT )(current_color));
          g0053= (CL_INT)((CL_INT )(current_bold));
          color(g0054,g0055);
          princ_string(m->name->name);
          color(g0052,g0053);
          color(g0052,g0053);
          color_princ_string1(((char*)":"));
          g0052= (CL_INT)((CL_INT )(current_color));
          g0053= (CL_INT)((CL_INT )(current_bold));
          color(g0054,g0055);
          print_any(((OID)i));
          color(g0052,g0053);
          color(g0052,g0053);
          color_princ_string1(((char*)"]"));
          color(g0054,g0055);
          }
        princ_string(((char*)" "));
        format_string(self,l);
        use_as_output_port(p);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(r);
          Result= Kernel.cfalse;
          for (START(Core.on_trace->restrictions); NEXT(r);)
          if (((OBJECT(method,r)->functional == (NULL)) ? CTRUE : CFALSE) != CTRUE)
           { ClaireFunction * f = OBJECT(method,r)->functional;
            ((fptr4)f->value)((CL_INT)m,(CL_INT)self,(CL_INT)i,(CL_INT)l);
            }
          }
        }
      else Result = Kernel.cfalse;
        POP_SIGNAL; return (Result);}
    }
  


// printing a bag without ( )
// @doc Printing
// prints the content of the bag l on the current output (cout()).
// elements are separated by a comma ','.
// The c++ function for: princ(s:bag) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  princ_bag(bag *s) { 
    { ClaireBoolean * f = CTRUE;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(x);
        for (START(s); NEXT(x);)
        { if (f == CTRUE)
           f= (CFALSE);
          else princ_string(((char*)","));
            print_any(x);
          }
        }
      }
    POP_SIGNAL;}
  


// we create a special contradiction that we shall reuse
// how to use it
// @doc versioning
// contradiction!() throws a contradiction. contradiction!() uses a
// unique instance of the contradiction exception class such to save
// a little memory.
// The c++ function for: contradiction!(_CL_obj:void) [RETURN_ARG]
CL_EXPORT void  contradiction_I_void() { 
    close_exception(OBJECT(ClaireException,Core.contradiction_occurs->value));
    POP_SIGNAL;}
  


// @doc list
// nil is the empty list instance.
// v0.01
//<sb> moved from Reader/file.cl
// v3.2.52
// @doc File system
// *fs* is a global variable that is set to a string that represent
// the file separator (system dependent). Usually "/" on UNIX and "\\"
// on windows.
//<sb> path separator (e.g. CLAIRE_LIBS)
// @doc File system
// *ps* is a global variable that is set to a string that represent
// the path separator (system dependent). Usually ":" on UNIX and ";"
// on windows.
// @doc string
// s1 / s2 returns the concatenation of two path components.
// it is equivalent two s1 /+ *fs* /+ s2 where *fs* is the file
// separator ('/' under UNIX and '\' under win32)
// \code
// "toto" / "titi" -> "toto/titi".
// \/code
// The c++ function for: /(s:string,s2:string) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT char * _7_string(char *s,char *s2) { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    { char *Result ;
      { CL_INT  lens = LENGTH_STRING(s);
        CL_INT  lens2 = LENGTH_STRING(s2);
        if (lens == 0)
         Result = s2;
        else if (lens2 == 0)
         Result = s;
        else { { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while ((rfind_string2(s,string_v(Core._starfs_star->value)) == lens))
              { GC_LOOP;
                GC__STRING(s = substring_string(s,1,((CL_INT)lens-(CL_INT)1)), 1);
                lens= (CL_INT)(((CL_INT)lens-(CL_INT)1));
                GC_UNLOOP;POP_SIGNAL;}
              }
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while ((find_string2(s2,string_v(Core._starfs_star->value)) == 1))
              { GC_LOOP;
                GC__STRING(s2 = substring_string(s2,2,lens2), 2);
                lens2= (CL_INT)(((CL_INT)lens2-(CL_INT)1));
                GC_UNLOOP;POP_SIGNAL;}
              }
            Result = append_string(GC_STRING(append_string(s,GC_STRING(string_v(Core._starfs_star->value)))),s2);
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// @doc @xl string
// s1 /- s2 returns the concatenation of two path components where the
// last path component of s1 has been removed. For instance
// \code
// "toto/tata" /- "titi" -> "toto/titi".
// \/code
// The c++ function for: /-(s1:string,s2:string) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT char * _7_dash_string(char *s1,char *s2) { 
    
    GC_BIND;
    { char *Result ;
      { CL_INT  p = rfind_string2(s1,string_v(Core._starfs_star->value));
        if (p == LENGTH_STRING(s1))
         p= (CL_INT)(rfind_string(s1,string_v(Core._starfs_star->value),((CL_INT)p-(CL_INT)1)));
        Result = (((CL_INT)p > (CL_INT)0) ?
          _7_string(GC_STRING(substring_string(s1,1,p)),s2) :
          _7_string(s1,s2) );
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: self_print(self:ffor_error) [NEW_ALLOC]
CL_EXPORT void  self_print_ffor_error1_Core(Core_ffor_error *self) { 
    princ_string(((char*)"forked for error, child "));
    print_any(((OID)self->childpid));
    princ_string(((char*)" returned:\n"));
    princ_string(self->childstr);
    POP_SIGNAL;}
  


// end of file

/***** CLAIRE Compilation of file ./meta/function.cl 
         [version 3.5.0 / safety 5] *****/


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
// @doc number
// returns the lowest integer
// The c++ function for: min(x:integer,y:integer) [SAFE_RESULT]
CL_EXPORT CL_INT  min_integer1(CL_INT x,CL_INT y) { 
    { CL_INT Result = 0;
      Result = (((CL_INT)x <= (CL_INT)y) ?
        x :
        y );
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// returns the greatest integer
// The c++ function for: max(x:integer,y:integer) [SAFE_RESULT]
CL_EXPORT CL_INT  max_integer1(CL_INT x,CL_INT y) { 
    { CL_INT Result = 0;
      Result = (((CL_INT)x <= (CL_INT)y) ?
        y :
        x );
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// returns the lowest float
// The c++ function for: min(g0056:any,g0057:any) [RETURN_ARG]
CL_EXPORT OID  min_float1_(OID g0056,OID g0057) { 
    return _float_(min_float1(float_v(g0056),float_v(g0057)));
}


// The c++ function for: min(x:float,y:float) [RETURN_ARG]
CL_EXPORT double  min_float1(double x,double y) { 
      { double Result =0.0;
      Result = ((x <= y) ?
        x :
        y );
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// returns the greatest float
// The c++ function for: max(g0058:any,g0059:any) [RETURN_ARG]
CL_EXPORT OID  max_float1_(OID g0058,OID g0059) { 
    return _float_(max_float1(float_v(g0058),float_v(g0059)));
}


// The c++ function for: max(x:float,y:float) [RETURN_ARG]
CL_EXPORT double  max_float1(double x,double y) { 
      { double Result =0.0;
      Result = ((x <= y) ?
        y :
        x );
      POP_SIGNAL; return (Result);}
    }
  


// *********************************************************************
// *   Part 1: Basics of pretty printing                               *
// *********************************************************************
// we use a nice object
// support recursive print-in-string 
// buffered print
// new in v3.3.26: unbounded recursion is supported :-)
// @doc Printing
// print_in_string() opens a new output port that will be stored as a string.
// The user is given access to the string at the end of the transcription, when the
// call to end_of_string() returns this string. print_in_string may be used recursively.
// The c++ function for: print_in_string(_CL_obj:void) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  print_in_string_void() { 
    
    GC_BIND;
    { CL_INT  n = ((CL_INT)Core.pretty->cprevious+(CL_INT)2);
      blob * pp = GC_OBJECT(blob,Core.pretty->cpretty);
      blob * p1 = GC_OBJECT(blob,blob_I_void1());
      PortObject * p2 = use_as_output_port(p1);
      _void_(Core.pretty->cprevious = n);
      _void_(Core.pretty->cpretty = p1);
      if (equal(_oid_(Core.pretty->cpstack),Core.nil->value) == CTRUE)
       _void_(Core.pretty->cpstack = list::alloc(Kernel._port,3,_oid_(pp),
        _oid_(p2),
        _oid_(p1)));
      else { GC_OBJECT(list,Core.pretty->cpstack)->addFast((OID)_oid_(p2));
          GC_OBJECT(list,Core.pretty->cpstack)->addFast((OID)_oid_(p1));
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  


//pretty.cpstack[n] := p2,
// if (n = length(pretty.cpstack)) pretty.cpstack :add p1)) ]
// @doc Printing
// end_of_string() returns the string containing everything
// that has been printed since the last call to print_in_string().
// The c++ function for: end_of_string(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT char * end_of_string_void() { 
    
    GC_BIND;
    if (Core.pretty->cprevious == 1)
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[123] unbalanced use of print-in-string")),
      _oid_(Kernel.nil))));
    { char *Result ;
      { CL_INT  n = Core.pretty->cprevious;
        char * s = GC_STRING(string_I_blob1(GC_OBJECT(blob,Core.pretty->cpretty)));
        buffer * op = GC_OBJECT(buffer,OBJECT(buffer,(*(Core.pretty->cpstack))[((CL_INT)n-(CL_INT)2)]));
        PortObject * p = GC_OBJECT(PortObject,OBJECT(PortObject,(*(Core.pretty->cpstack))[((CL_INT)n-(CL_INT)1)]));
        use_as_output_port(p);
        rmlast_list(Core.pretty->cpstack);
        rmlast_list(Core.pretty->cpstack);
        fclose_port1(GC_OBJECT(blob,Core.pretty->cpretty));
        _void_(Core.pretty->cpretty = ((blob *) op));
        _void_(Core.pretty->cprevious = ((CL_INT)Core.pretty->cprevious-(CL_INT)2));
        Result = s;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: mClaire/buffer_length(_CL_obj:void) [RETURN_ARG]
CL_EXPORT CL_INT  buffer_length_void() { 
    POP_SIGNAL; return (length_blob1(Core.pretty->cpretty));}
  


// The c++ function for: mClaire/buffer_set_length(i:integer) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  buffer_set_length_integer(CL_INT i) { 
    set_length_blob1(Core.pretty->cpretty,i);
    POP_SIGNAL;}
  


// a method for calling the printer without issuing a message
// here we assume that self_print is always defined as a function
// The c++ function for: apply_self_print(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  apply_self_print_any(OID self) { 
    
    GC_BIND;
    if (((((ClaireBoolean *) (ClaireBoolean *)((INTEGERP(self) ? CFALSE : CTRUE)))) == CTRUE) && 
        ((((ClaireBoolean *) (ClaireBoolean *)(((self << ADDRTRANS) ? CFALSE : CTRUE)))) == CTRUE))
     princ_string(((char*)"<NULL>"));
    else if (INHERIT(OWNER(self),Kernel._table))
     (*Kernel.self_print)(self);
    else if (INHERIT(OWNER(self),Kernel._thing))
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
            { c_handle.catchIt();{ princ_string(((char*)"<unprintable:"));
                print_any(_oid_(OWNER(self)));
                princ_string(((char*)" ("));
                print_any(GC_OID(_oid_(ClEnv->exception_I)));
                princ_string(((char*)")>"));
                }
              }
            else PREVIOUS_HANDLER;}
          if (INHERIT(OWNER(self),Kernel._exception))
         color(30,0);
        }
      GC_UNBIND; POP_SIGNAL;}
  


// some basic definitions
// The c++ function for: self_print(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_any_Core(OID self) { 
    if (self == CNULL)
     princ_string(((char*)"unknown"));
    else { princ_string(((char*)"<"));
        print_any(_oid_(OWNER(self)));
        princ_string(((char*)">"));
        }
      POP_SIGNAL;}
  


// The c++ function for: self_print(self:exception) [NEW_ALLOC]
CL_EXPORT void  self_print_exception1_Core(ClaireException *self) { 
    princ_string(((char*)"<"));
    print_any(_oid_(OWNER(_oid_(self))));
    princ_string(((char*)">"));
    POP_SIGNAL;}
  


// The c++ function for: self_print(self:boolean) [0]
CL_EXPORT void  self_print_boolean_Core(ClaireBoolean *self) { 
    if (self == CTRUE)
     princ_string(((char*)"true"));
    else princ_string(((char*)"false"));
      POP_SIGNAL;}
  


// The c++ function for: self_print(self:function) [0]
CL_EXPORT void  self_print_function_Core(ClaireFunction *self) { 
    princ_string(((char*)"#'"));
    princ_string(string_I_function(self));
    POP_SIGNAL;}
  


// prints the name of a restriction. If we have a close property and if a
// short-cut is possible, we use it.
// The c++ function for: self_print(self:restriction) [NEW_ALLOC]
CL_EXPORT void  self_print_restriction_Core(restriction *self) { 
    if ((not_any(_oid_(((self->selector == (NULL)) ? CTRUE : CFALSE))) != CTRUE) || 
        (self->domain == (NULL)))
     { princ_string(((char*)"<"));
      print_any(_oid_(OWNER(_oid_(self))));
      princ_string(((char*)">"));
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
        princ_string(((char*)" @ "));
        { OID  g0063UU;
          if (n == 1)
           g0063UU = _oid_(c);
          else g0063UU = _oid_(self->domain);
            print_any(g0063UU);
          }
        }
      POP_SIGNAL;}
  


// we are too far
// @doc Printing
// prints the entity x (x can be anything) on the current output (cout()).
// The c++ function for: print(x:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  print_any(OID x) { 
    if ((Core.pretty->pbreak == CTRUE) && 
        (Core.pretty->pprint == CTRUE))
     { CL_INT  b_index = buffer_length_void();
      ClaireBoolean * missed = CFALSE;
      CL_INT  _Zl = Core.pretty->index;
      if (short_enough_integer(((CL_INT)b_index+(CL_INT)10)) != CTRUE)
       { _void_(Core.pretty->pprint = CFALSE);
        _void_(Core.pretty->pbreak = CFALSE);
        print_any(x);
        _void_(Core.pretty->pprint = CTRUE);
        }
      else { { ClaireHandler c_handle = ClaireHandler();
            if ERROR_IN 
            { { _void_(Core.pretty->pbreak = CFALSE);
                apply_self_print_any(x);
                _void_(Core.pretty->pbreak = CTRUE);
                }
              ERROR_FREE;}
            else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Core._much_too_far)) == CTRUE)
            { c_handle.catchIt();missed= (CTRUE);
              }
            else PREVIOUS_HANDLER;}
          if (missed == CTRUE)
           { _void_(Core.pretty->pprint = CTRUE);
            _void_(Core.pretty->pbreak = CTRUE);
            buffer_set_length_integer(b_index);
            _void_(Core.pretty->index = _Zl);
            apply_self_print_any(x);
            }
          }
        }
    else apply_self_print_any(x);
      ;POP_SIGNAL;}
  


// The c++ function for: short_enough(self:integer) [0]
CL_EXPORT ClaireBoolean * short_enough_integer(CL_INT self) { 
    POP_SIGNAL; return (_inf_integer(self,Core.pretty->width));}
  


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
CL_EXPORT ClaireObject * complete_I_object(ClaireObject *self) { 
    
    GC_BIND;
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
// @doc class
// kill!(x) is more brutal than kill and deallocates without any checking. 
// @doc entity
// not(self) returns false for all entity except false, nil, the empty set and the empty list.
// The c++ function for: not(self:any) [0]
CL_EXPORT ClaireBoolean * not_any(OID self) { 
    { ClaireBoolean *Result ;
      Result = ((self == Kernel.ctrue) ?
        CFALSE :
        ((self == Kernel.cfalse) ?
          CTRUE :
          ((boolean_I_any(self) != CTRUE) ?
            CTRUE :
            CFALSE ) ) );
      POP_SIGNAL; return (Result);}
    }
  


// @doc entity
// this is the negation of (x = y).
// The c++ function for: !=(x:any,y:any) [0]
CL_EXPORT ClaireBoolean * _I_equal_any(OID x,OID y) { 
    { ClaireBoolean *Result ;
      Result = ((equal(x,y) == CTRUE) ?
        CFALSE :
        CTRUE );
      POP_SIGNAL; return (Result);}
    }
  


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
// The c++ function for: owner(self:any) [0]
CL_EXPORT ClaireClass * owner_any(OID self) { 
    POP_SIGNAL; return (OWNER(self));}
  


// some useful methods
// @doc entity
// The general method known? simply returns true whenever the object exists in the database
// (i.e. false is returned if x is unknown vs. unknown?).
// The c++ function for: known?(self:any) [0]
CL_EXPORT ClaireBoolean * known_ask_any(OID self) { 
    POP_SIGNAL; return (_I_equal_any(CNULL,self));}
  


// @doc entity
// The general method unknown? simply returns true if the entity is unknown in
// the database (vs. known?).
// The c++ function for: unknown?(self:any) [0]
CL_EXPORT ClaireBoolean * unknown_ask_any(OID self) { 
    POP_SIGNAL; return (equal(CNULL,self));}
  


// needed by the compiled code
// The c++ function for: check_in(self:any,y:type) [RETURN_ARG]
CL_EXPORT OID  check_in_any(OID self,ClaireType *y) { 
    { OID Result = 0;
      if (belong_to(self,_oid_(y)) == CTRUE)
       Result = self;
      else { OID  V_CL0064;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[124] the value ~S does not belong to the range ~S")),
            _oid_(list::alloc(2,self,_oid_(y))))));
          
          Result=_void_(V_CL0064);}
        POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: check_in(self:bag,c:class,y:type) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT bag * check_in_bag(bag *self,ClaireClass *c,ClaireType *y) { 
    { bag *Result ;
      { ClaireObject *V_CC ;
        { ClaireBoolean * g0065I;
          { OID  g0066UU;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(z);
              g0066UU= Kernel.cfalse;
              for (START(self); NEXT(z);)
              if (belong_to(z,_oid_(y)) != CTRUE)
               { g0066UU = Kernel.ctrue;
                ClEnv->cHandle = loop_handle;break;}
              }
            g0065I = not_any(g0066UU);
            }
          
          if (g0065I == CTRUE) V_CC = OBJECT(bag,(*Kernel.cast_I)(_oid_(self),
              _oid_(y)));
            else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[124] the value ~S does not belong to subtype[~S]")),
            _oid_(list::alloc(2,_oid_(self),_oid_(y))))));
          }
        Result= (bag *) V_CC;}
      POP_SIGNAL; return (Result);}
    }
  


// new in v3.00.48
// The c++ function for: <(self:any,x:any) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * _inf_any(OID self,OID x) { 
    { ClaireBoolean *Result ;
      Result = ((equal(self,x) == CTRUE) ?
        CFALSE :
        OBJECT(ClaireBoolean,(*Kernel._inf_equal)(self,
          x)) );
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: >(self:any,x:any) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * _sup_any(OID self,OID x) { 
    { ClaireBoolean *Result ;
      Result = ((equal(self,x) == CTRUE) ?
        CFALSE :
        OBJECT(ClaireBoolean,(*Kernel._inf_equal)(x,
          self)) );
      POP_SIGNAL; return (Result);}
    }
  


// >= is defined as a macro in file.cl
// ----------------------- CLASS ---------------------------------------------
// v3.2.14 recursively applies to subclasses
// @doc class
// declares a class as ephemeral: the member set is not maintained (ephemeral_object)
// The c++ function for: ephemeral(self:class) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  ephemeral_class(ClaireClass *self) { 
    { OID Result = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(c);
        Result= Kernel.cfalse;
        for (START(self->descendents); NEXT(c);)
        if ((OBJECT(ClaireClass,c)->instances->length != 0) || 
            ((CL_INT)OBJECT(ClaireClass,c)->open <= (CL_INT)1))
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[187] cannot declare ~S as ephemeral because of ~S")),
          _oid_(list::alloc(2,_oid_(self),c)))));
        else _void_(OBJECT(ClaireClass,c)->open = ClEnv->ephemeral);
          }
      POP_SIGNAL; return (Result);}
    }
  


// @doc class
// declares a class as an abtract class (without instances)
// The c++ function for: abstract(c:class) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT]
CL_EXPORT OID  abstract_class(ClaireClass *c) { 
    { OID Result = 0;
      { CL_INT  n = c->open;
        if (n == ClEnv->ephemeral)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[125] ephemeral classes cannot be abstract")),
          _oid_(Kernel.nil))));
        else { if (c->instances->length != 0)
             { if (should_trace_ask_module1(Core.it,3) == CTRUE)
               mtformat_module1(Core.it,((char*)"--- note: ~S already has some instances"),3,list::alloc(1,_oid_(c)));
              else ;}
            if (n == 2)
             _void_(c->open = 0);
            else if (n == 1)
             _void_(c->open = -1);
            }
          Result = _oid_(c);
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc class
// declares a class as totally defined in the hierarchy: no new subclasses can be added.
// The c++ function for: final(c:class) [SLOT_UPDATE+SAFE_RESULT]
CL_EXPORT OID  final_class(ClaireClass *c) { 
    { OID Result = 0;
      { CL_INT  n = c->open;
        if (n == 3)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[126] ephemeral classes cannot be set as final")),
          _oid_(Kernel.nil))));
        else if (n == 2)
         _void_(c->open = 1);
        else if (n == 0)
         _void_(c->open = -1);
        Result = _oid_(c);
        }
      POP_SIGNAL; return (Result);}
    }
  


// instantiation with and without a name
// @doc class
// new(self) creates an instance of the class self
// The c++ function for: new(self:class) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT ClaireObject * new_class1(ClaireClass *self) { 
    
    GC_BIND;
    { ClaireObject *Result ;
      { ClaireObject * o;
        { { if ((CL_INT)self->open <= (CL_INT)0)
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[105] cannot instantiate ~S")),
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
CL_EXPORT ClaireType * new_class1_type(ClaireType *self) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = glb_class(Kernel._object,GC_OBJECT(ClaireType,member_type(self)));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// v3.2.26
// @doc class
// new(self, %nom) creates a named instance of the class v (assumed to be a subclass of thing)
// with the name self
// The c++ function for: new(self:class,%nom:symbol) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT thing * new_class2(ClaireClass *self,symbol *_Znom) { 
    { thing *Result ;
      { ClaireObject *V_CC ;
        { thing * o;
          { if ((CL_INT)self->open <= (CL_INT)0)
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[105] cannot instantiate ~S")),
              _oid_(list::alloc(1,_oid_(self))))));
            o = new_thing_class(self,_Znom);
            }
          V_CC = complete_I_object(o);
          }
        Result= (thing *) V_CC;}
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: new_class2_type
CL_EXPORT ClaireType * new_class2_type(ClaireType *self,ClaireType *_Znom) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = glb_class(Kernel._thing,GC_OBJECT(ClaireType,member_type(self)));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// v3.2.26
// internal version
// The c++ function for: new_object_class_type
CL_EXPORT ClaireType * new_object_class_type(ClaireType *self) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = glb_class(Kernel._object,GC_OBJECT(ClaireType,member_type(self)));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: new_thing_class_type
CL_EXPORT ClaireType * new_thing_class_type(ClaireType *self,ClaireType *_Znom) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = glb_class(Kernel._thing,GC_OBJECT(ClaireType,member_type(self)));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// the smallest super_set of two sets
// there is always any, so it always returns a class
// The c++ function for: meet(self:class,ens:class) [RETURN_ARG]
CL_EXPORT ClaireClass * meet_class(ClaireClass *self,ClaireClass *ens) { 
    { ClaireClass *Result ;
      { list * l1 = self->ancestors;
        list * l2 = ens->ancestors;
        CL_INT  m = (((CL_INT)l1->length < (CL_INT)l2->length) ?
          l1->length :
          l2->length );
        { CL_INT loop_handle = ClEnv->cHandle;
          while ((equal((*(l1))[m],(*(l2))[m]) != CTRUE))
          { m= (CL_INT)(((CL_INT)m-(CL_INT)1));
            POP_SIGNAL;}
          }
        Result = OBJECT(ClaireClass,(*(l1))[m]);
        }
      POP_SIGNAL; return (Result);}
    }
  


// fast inclusion method for lattice_sets (lattice order). The argument is
// either a lattice_set or {}
// @doc type
// inherit?(self, ens) returns (self % ancestors(ens)).
// The c++ function for: inherit?(self:class,ens:class) [0]
CL_EXPORT ClaireBoolean * inherit_ask_class(ClaireClass *self,ClaireClass *ens) { 
    { ClaireBoolean *Result ;
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
CL_EXPORT OID  abstract_property(property *p) { 
    { OID Result = 0;
      { CL_INT  n = p->open;
        if ((CL_INT)n < (CL_INT)2)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[127] ~S can no longer become abstract")),
          _oid_(list::alloc(1,_oid_(p))))));
        else _void_(p->open = 3);
          Result = _oid_(p);
        }
      POP_SIGNAL; return (Result);}
    }
  


// a final property is completely defined and cannot receive a new restriction
// v3.2.04: the new value 4 will be used to represent (compiled but open)
// The c++ function for: final(r:relation) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  final_relation(ClaireRelation *r) { 
    
    GC_BIND;
    if (INHERIT(r->isa,Kernel._property))
     { if ((CL_INT)r->open <= (CL_INT)2)
       { _void_(r->open = 1);
        { ClaireRelation * g0067 = r; 
          ClaireType * g0068;
          { list * g0069UU;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID x; CL_INT CLcount;
                v_list = CLREAD(property,r,restrictions);
                 g0069UU = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { x = (*(v_list))[CLcount];
                  v_val = (*(OBJECT(restriction,x)->domain))[1];
                  
                  (*((list *) g0069UU))[CLcount] = v_val;}
                }
              GC_OBJECT(list,g0069UU);}
            g0068 = Uall_list(g0069UU);
            }
          _void_(g0067->domain = g0068);}
        { ClaireRelation * g0070 = r; 
          ClaireType * g0071;
          { list * g0072UU;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID x; CL_INT CLcount;
                v_list = CLREAD(property,r,restrictions);
                 g0072UU = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { x = (*(v_list))[CLcount];
                  v_val = _oid_(OBJECT(restriction,x)->range);
                  
                  (*((list *) g0072UU))[CLcount] = v_val;}
                }
              GC_OBJECT(list,g0072UU);}
            g0071 = Uall_list(g0072UU);
            }
          _void_(g0070->range = g0071);}
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


//------------- MODULES   --------------------------------------------------
// the close function gives its right value to the *internal* slot that
// is the order of the module in the system. The name is supposed to be
// read in the system module.
// The c++ function for: close(self:module) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT]
CL_EXPORT module * close_module(module *self) { 
    
    GC_BIND;
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
       mtformat_module1(Core.it,((char*)"---- note: ~S is a root module !\n"),3,GC_OBJECT(list,list::alloc(1,_oid_(self))));
      else ;}
    { module *Result ;
      Result = self;
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// note: dynamic modules are no longer supported
// The c++ function for: get_symbol(self:string) [0]
CL_EXPORT OID  get_symbol_string(char *self) { 
    POP_SIGNAL; return (get_symbol_module(claire.it,self));}
  


// *********************************************************************
// *   Part 3: System Methods                                          *
// *********************************************************************
// all these methods will be open-coded by the compiler
//get_stack(self:integer) : any -> get_stack(self)
//put_stack(self:integer,x:any) : any -> put_stack(self, x)
//push!(self:meta_system,x:any) : void -> push!(self, x)
// @doc Miscellaneous
// gc() forces a garbage collection to take place.
// @doc date
// time_get() stops a clock started by time_set() it and returns the elapsed time in milliseconds.
// @doc date
// time_set() starts a clock that will have to be stopped with time_get().
// @doc date
// time_show pretty prints the current value of a timer started by time_set().
//stat() : void -> function!(claire_stat)
// @doc symbol
// gensym() generates randomly a new symbol. 
// The c++ function for: gensym(self:void) [0]
CL_EXPORT symbol * gensym_void() { 
    POP_SIGNAL; return (gensym_string(((char*)"g")));}
  


// world management
// The c++ function for: store(l:list,n:integer,y:any) [0]
CL_EXPORT OID  store_list4(list *l,CL_INT n,OID y) { 
    POP_SIGNAL; return ((OID )(STOREI(l,&(*l)[n],y)));}
  


// The c++ function for: store(l:array,n:integer,y:any) [RETURN_ARG]
CL_EXPORT OID  store_array1(OID *l,CL_INT n,OID y) { 
    POP_SIGNAL; return (store_array(l,n,y,CTRUE));}
  


// The c++ function for: commit(n:integer) [0]
CL_EXPORT void  commit_integer(CL_INT n) { 
    { CL_INT loop_handle = ClEnv->cHandle;
      while (((CL_INT)n < (CL_INT)world_number()))
      { world_remove();
        POP_SIGNAL;}
      }
    POP_SIGNAL;}
  


// The c++ function for: backtrack(n:integer) [0]
CL_EXPORT void  backtrack_integer(CL_INT n) { 
    { CL_INT loop_handle = ClEnv->cHandle;
      while (((CL_INT)n < (CL_INT)world_number()))
      { world_pop();
        POP_SIGNAL;}
      }
    POP_SIGNAL;}
  


// allows to change the storage class
// The c++ function for: store(l:listargs) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  store_listargs(listargs *l) { 
    { OID Result = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(r);
        Result= Kernel.cfalse;
        for (START(l); NEXT(r);)
        if (INHERIT(OWNER(r),Kernel._relation))
         _void_(OBJECT(ClaireRelation,r)->store_ask = CTRUE);
        else if (Kernel._string == OWNER(r))
         { OID  v = value_string(string_v(r));
          if (INHERIT(OWNER(v),Core._global_variable))
           _void_(OBJECT(global_variable,v)->store_ask = CTRUE);
          }
        }
      POP_SIGNAL; return (Result);}
    }
  


//<sb> faulting interface
// The c++ function for: preread(p:property,o:any) [0]
CL_EXPORT void  preread_property1_Core(property *p,OID o) { 
    ;POP_SIGNAL;}
  


// *********************************************************************
// *   Part 4: Methods for Native entities                             *
// *********************************************************************
//------------------- STRING -----------------------------------------------
// @doc string
// returns the length of a string
//<sb> buffer
// @doc symbol
// symbol!(s) returns the symbol associated to s in the claire module. A new symbol is
// created if no such symbol exists.
// The c++ function for: symbol!(self:string) [0]
CL_EXPORT symbol * symbol_I_string2(char *self) { 
    POP_SIGNAL; return (symbol_I_string(self,claire.it));}
  


// The c++ function for: externC(s:string) [SAFE_RESULT]
CL_EXPORT void  externC_string(char *s) { 
    close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"cannot execute C code: ~A")),
      _oid_(list::alloc(1,_string_(s))))));
    POP_SIGNAL;}
  


// The c++ function for: externC(s:string,c:class) [SAFE_RESULT]
CL_EXPORT OID  externC_string2(char *s,ClaireClass *c) { 
    { OID Result = 0;
      { OID  V_CL0075;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"cannot execute ~A")),
          _oid_(list::alloc(1,_string_(s))))));
        
        Result=_void_(V_CL0075);}
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: externC_string2_type
CL_EXPORT ClaireType * externC_string2_type(ClaireType *s,ClaireType *c) { 
    POP_SIGNAL; return (member_type(c));}
  


// The c++ function for: nth_get(s:string,n:integer,max:integer) [RETURN_ARG]
CL_EXPORT ClaireChar * nth_get_string(char *s,CL_INT n,CL_INT max) { 
    { ClaireChar *Result ;
      { ClaireObject *V_CC ;
        if ((CL_INT)n <= (CL_INT)max)
         V_CC = _char_(s[n - 1]);
        else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Buffer string access")),
            _oid_(Kernel.nil))));
          Result= (ClaireChar *) V_CC;}
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: nth_put(s:string,n:integer,c:char,max:integer) [BAG_UPDATE+RETURN_ARG]
CL_EXPORT void  nth_put_string(char *s,CL_INT n,ClaireChar *c,CL_INT max) { 
    if ((CL_INT)n <= (CL_INT)max)
     (s[n - 1] = (unsigned char) c->ascii);
    else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Buffer string access")),
        _oid_(Kernel.nil))));
      POP_SIGNAL;}
  


// @doc Miscellaneous
// Passes the command s to the operating system (the shell) and returns the
// exit status of the command execution.
// @doc Environment variables
// getenv(s) returns the value of the environment variable s if it
// exists and an empty string otherwise. 
// @doc symbol
// returns the object whose name (in the default claire namespace)
// corresponds to the string s.
// @doc symbol
// returns the object whose name (search from the namespace m)
// corresponds to the string s.
//  v3.2.14
//------------------- SYMBOL -----------------------------------------------
// @doc symbol
// make_string(s) returns a string denoting the same identifier.
// If s is given in the qualified form (module/identifier), than the
// result will contain the name of the module ("module/identifier").
// The c++ function for: make_string(self:symbol) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT char * make_string_symbol(symbol *self) { 
    print_in_string_void();
    princ_symbol(self);
    POP_SIGNAL; return (end_of_string_void());}
  


//princ(self:symbol) : any -> function!(princ_symbol)
// The c++ function for: self_print(self:symbol) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT void  self_print_symbol_Core(symbol *self) { 
    princ_symbol(self->module_I->name);
    princ_string(((char*)"/"));
    print_any(_string_(string_I_symbol(self)));
    POP_SIGNAL;}
  


//c_princ(self:symbol) : any -> function!(c_princ_symbol)
//gensym(self:string) : symbol -> function!(gensym_string, NEW_ALLOC)
//--------------------- INTEGER -----------------------------------------
// @doc number
// returns the sum of two integers
// The c++ function for: +(self:integer,x:integer) [RETURN_ARG]
CL_EXPORT CL_INT  _plus_integer(CL_INT self,CL_INT x) { 
    POP_SIGNAL; return (_integer_((CL_INT)self+(CL_INT)x));}
  


// The c++ function for: +_integer_type
CL_EXPORT ClaireType * _plus_integer_type(ClaireType *self,ClaireType *x) { 
    POP_SIGNAL; return (abstract_type_operation(Core._plus,self,x));}
  


// @doc number
// returns the difference of two integers
// The c++ function for: -(self:integer,x:integer) [RETURN_ARG]
CL_EXPORT CL_INT  _dash_integer1(CL_INT self,CL_INT x) { 
    POP_SIGNAL; return (((CL_INT)self-(CL_INT)x));}
  


// The c++ function for: -_integer1_type
CL_EXPORT ClaireType * _dash_integer1_type(ClaireType *self,ClaireType *x) { 
    POP_SIGNAL; return (abstract_type_operation(Kernel._dash,self,x));}
  


//-(self:integer) : integer -> function!(ch_sign)
//float!(self:integer) : float -> function!(to_float)
//mod(self:integer,x:integer) : integer -> function!(mod_integer)
// @doc Miscellaneous
// exit(n) stops CLAIRE and returns to the hosting system the value n.
// What can happen next is platform-dependent.
//less_code(n:integer,i:integer) : boolean -> function!(less_code_integer)
// @doc number
// (x << n) is the result of shifting the integer x seen as a bitvector to the
// left by n positions.
// The c++ function for: <<(x:integer,n:integer) [0]
CL_EXPORT CL_INT  _inf_inf_integer(CL_INT x,CL_INT n) { 
    POP_SIGNAL; return ((CL_INT )((x << n)));}
  


// v3.3.16
// @doc number
// (x >> n) is the result of shifting the integer x seen as a bitvector to the
// right by n positions.
// The c++ function for: >>(x:integer,n:integer) [0]
CL_EXPORT CL_INT  _sup_sup_integer(CL_INT x,CL_INT n) { 
    POP_SIGNAL; return ((CL_INT )((x >> n)));}
  


// @doc number
// and(x,y) returns the bitwise intersection of two integers (seen as bitvectors).
// The c++ function for: and(x:integer,y:integer) [0]
CL_EXPORT CL_INT  and_integer(CL_INT x,CL_INT y) { 
    POP_SIGNAL; return ((CL_INT )((x & y)));}
  


// @doc number
// or(x, y) returns the bitwise union of two integers (seen as bitvectors).
// The c++ function for: or(x:integer,y:integer) [0]
CL_EXPORT CL_INT  or_integer(CL_INT x,CL_INT y) { 
    POP_SIGNAL; return ((CL_INT)((x | y)));}
  


// open-coded
// @doc number
// returns true if x is lower than y
// The c++ function for: <(x:integer,y:integer) [0]
CL_EXPORT ClaireBoolean * _inf_integer(CL_INT x,CL_INT y) { 
    { ClaireBoolean *Result ;
      Result = (((CL_INT)x < (CL_INT)y) ?
        CTRUE :
        CFALSE );
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// returns true if x is lower or equal to y
// The c++ function for: <=(x:integer,y:integer) [0]
CL_EXPORT ClaireBoolean * _inf_equal_integer(CL_INT x,CL_INT y) { 
    { ClaireBoolean *Result ;
      Result = (((CL_INT)x <= (CL_INT)y) ?
        CTRUE :
        CFALSE );
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// returns true if x is greater than y
// The c++ function for: >(x:integer,y:integer) [0]
CL_EXPORT ClaireBoolean * _sup_integer(CL_INT x,CL_INT y) { 
    { ClaireBoolean *Result ;
      Result = (((CL_INT)x > (CL_INT)y) ?
        CTRUE :
        CFALSE );
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: nth(self:integer,y:integer) [0]
CL_EXPORT ClaireBoolean * nth_integer(CL_INT self,CL_INT y) { 
    { ClaireBoolean *Result ;
      Result = ((BCONTAIN(self,y)) ?
        CTRUE :
        CFALSE );
      POP_SIGNAL; return (Result);}
    }
  


// used by the logic
// @doc number
// factor?(x,y) returns true if x is a multiple of y.
// The c++ function for: factor?(x:integer,y:integer) [0]
CL_EXPORT ClaireBoolean * factor_ask_integer(CL_INT x,CL_INT y) { 
    POP_SIGNAL; return (equal(((OID)mod_integer(x,y)),((OID)0)));}
  


// @doc number
// divide?(x,y) returns true if y is a multiple of x.
// The c++ function for: divide?(x:integer,y:integer) [0]
CL_EXPORT ClaireBoolean * divide_ask_integer(CL_INT x,CL_INT y) { 
    POP_SIGNAL; return (equal(((OID)mod_integer(y,x)),((OID)0)));}
  


// @doc driving optimizations
// Id(x) returns x. Id has a special behavior when compiled which makes it useful.
// The argument is evaluated before being compiled. The intended use is with global
// variables: the compiler uses the actual value of the variable instead of a reference
// to the global variable. This is very convenient to introduce parameters that are defined
// outside the module that is being compiled. This is also used to tell compiler that an
// iteration should make explicit use of all iterations rule that may apply to some subclasses
// of the set expression being iterated.
// The c++ function for: Id(x:any) [RETURN_ARG]
CL_EXPORT OID  Id_any(OID x) { 
    POP_SIGNAL; return (x);}
  


// The c++ function for: Id_any_type
CL_EXPORT ClaireType * Id_any_type(ClaireType *x) { 
    POP_SIGNAL; return (x);}
  


// The c++ function for: pair(x:any,y:any) [NEW_ALLOC]
CL_EXPORT list * pair_any(OID x,OID y) { 
    POP_SIGNAL; return (list::alloc(2,x,y));}
  


// The c++ function for: pair_1(x:list) [RETURN_ARG]
CL_EXPORT OID  pair_1_list(list *x) { 
    POP_SIGNAL; return ((*(x))[1]);}
  


// The c++ function for: pair_1_list_type
CL_EXPORT ClaireType * pair_1_list_type(ClaireType *x) { 
    POP_SIGNAL; return (member_type(x));}
  


// The c++ function for: pair_2(x:list) [RETURN_ARG]
CL_EXPORT OID  pair_2_list(list *x) { 
    POP_SIGNAL; return ((*(x))[2]);}
  


// The c++ function for: pair_2_list_type
CL_EXPORT ClaireType * pair_2_list_type(ClaireType *x) { 
    POP_SIGNAL; return (member_type(x));}
  


//------------------------ FLOAT ---------------------------------------------
// @doc number
// returns the sum of two floats
// The c++ function for: +(g0076:any,g0077:any) [0]
CL_EXPORT OID  _plus_float_(OID g0076,OID g0077) { 
    return _float_(_plus_float(float_v(g0076),float_v(g0077)));
}


// The c++ function for: +(self:float,x:float) [0]
CL_EXPORT double  _plus_float(double self,double x) { 
      { double Result =0.0;
      { double  y = (self+x);
        Result = y;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// returns the difference of two floats
// The c++ function for: -(g0078:any,g0079:any) [0]
CL_EXPORT OID  _dash_float_(OID g0078,OID g0079) { 
    return _float_(_dash_float(float_v(g0078),float_v(g0079)));
}


// The c++ function for: -(self:float,x:float) [0]
CL_EXPORT double  _dash_float(double self,double x) { 
      { double Result =0.0;
      { double  y = (self-x);
        Result = y;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// returns the product of two floats
// The c++ function for: *(g0080:any,g0081:any) [0]
CL_EXPORT OID  _star_float_(OID g0080,OID g0081) { 
    return _float_(_star_float(float_v(g0080),float_v(g0081)));
}


// The c++ function for: *(self:float,x:float) [0]
CL_EXPORT double  _star_float(double self,double x) { 
      { double Result =0.0;
      { double  y = (self*x);
        Result = y;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// returns the division of two floats
// The c++ function for: /(g0082:any,g0083:any) [0]
CL_EXPORT OID  _7_float_(OID g0082,OID g0083) { 
    return _float_(_7_float(float_v(g0082),float_v(g0083)));
}


// The c++ function for: /(self:float,x:float) [0]
CL_EXPORT double  _7_float(double self,double x) { 
      { double Result =0.0;
      { double  y = (self/x);
        Result = y;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// returns the opposite of x (i.e. -1.0 * x)
// The c++ function for: -(g0084:any) [NEW_ALLOC]
CL_EXPORT OID  _dash_float2_(OID g0084) { 
    return _float_(_dash_float2(float_v(g0084)));
}


// The c++ function for: -(x:float) [NEW_ALLOC]
CL_EXPORT double  _dash_float2(double x) { 
      POP_SIGNAL; return (((-1.0)*x));}
  


// @doc number
// returns the square root of x. Returns an irrelevant value when x is strictly negative.
// The c++ function for: sqrt(g0085:any) [0]
CL_EXPORT OID  sqrt_float_(OID g0085) { 
    return _float_(sqrt_float(float_v(g0085)));
}


// The c++ function for: sqrt(self:float) [0]
CL_EXPORT double  sqrt_float(double self) { 
      { double Result =0.0;
      { double  y = sqrt(self);
        Result = y;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// (x ^ y) returns the y exponent of x.
// The c++ function for: ^(g0086:any,g0087:any) [NEW_ALLOC]
CL_EXPORT OID  _exp_float_(OID g0086,OID g0087) { 
    return _float_(_exp_float(float_v(g0086),float_v(g0087)));
}


// The c++ function for: ^(self:float,x:float) [NEW_ALLOC]
CL_EXPORT double  _exp_float(double self,double x) { 
      { double Result =0.0;
      { double  y = 0.0;
        y = pow(self,x);
        Result = y;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// log(x) returns the value of the natural logarithm of argument x.
// The c++ function for: log(g0088:any) [NEW_ALLOC]
CL_EXPORT OID  log_float_(OID g0088) { 
    return _float_(log_float(float_v(g0088)));
}


// The c++ function for: log(x:float) [NEW_ALLOC]
CL_EXPORT double  log_float(double x) { 
      { double Result =0.0;
      { double  y = 0.0;
        y = log(x);
        Result = y;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// tan(self) computes the tangent of self (measured in radians).
// The c++ function for: tan(g0089:any) [NEW_ALLOC]
CL_EXPORT OID  tan_float1_(OID g0089) { 
    return _float_(tan_float1(float_v(g0089)));
}


// The c++ function for: tan(self:float) [NEW_ALLOC]
CL_EXPORT double  tan_float1(double self) { 
      { double Result =0.0;
      { double  y = 0.0;
        y = tan(self);
        Result = y;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// cos(self) computes the cosine of self (measured in radians).
// The c++ function for: cos(g0090:any) [NEW_ALLOC]
CL_EXPORT OID  cos_float1_(OID g0090) { 
    return _float_(cos_float1(float_v(g0090)));
}


// The c++ function for: cos(self:float) [NEW_ALLOC]
CL_EXPORT double  cos_float1(double self) { 
      { double Result =0.0;
      { double  y = 0.0;
        y = cos(self);
        Result = y;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// sin(self) computes the sine of self (measured in radians).
// The c++ function for: sin(g0091:any) [NEW_ALLOC]
CL_EXPORT OID  sin_float1_(OID g0091) { 
    return _float_(sin_float1(float_v(g0091)));
}


// The c++ function for: sin(self:float) [NEW_ALLOC]
CL_EXPORT double  sin_float1(double self) { 
      { double Result =0.0;
      { double  y = 0.0;
        y = sin(self);
        Result = y;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// acos(self) computes the principal value of the arc cosine of self
// in the range [0, pi].
// The c++ function for: acos(g0092:any) [NEW_ALLOC]
CL_EXPORT OID  acos_float1_(OID g0092) { 
    return _float_(acos_float1(float_v(g0092)));
}


// The c++ function for: acos(self:float) [NEW_ALLOC]
CL_EXPORT double  acos_float1(double self) { 
      { double Result =0.0;
      { double  y = 0.0;
        y = acos(self);
        Result = y;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// asin(self) computes the principal value of the arc sine of self in
// the range [-pi/2, +pi/2].
// The c++ function for: asin(g0093:any) [NEW_ALLOC]
CL_EXPORT OID  asin_float1_(OID g0093) { 
    return _float_(asin_float1(float_v(g0093)));
}


// The c++ function for: asin(self:float) [NEW_ALLOC]
CL_EXPORT double  asin_float1(double self) { 
      { double Result =0.0;
      { double  y = 0.0;
        y = asin(self);
        Result = y;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// atan(self) returns the principal value of the arc tangent of self in the
// range [-pi/2, +pi/2].
// The c++ function for: atan(g0094:any) [NEW_ALLOC]
CL_EXPORT OID  atan_float1_(OID g0094) { 
    return _float_(atan_float1(float_v(g0094)));
}


// The c++ function for: atan(self:float) [NEW_ALLOC]
CL_EXPORT double  atan_float1(double self) { 
      { double Result =0.0;
      { double  y = 0.0;
        y = atan(self);
        Result = y;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// tanh(self) computes the hyperbolic tangent of self.
// The c++ function for: tanh(g0095:any) [NEW_ALLOC]
CL_EXPORT OID  tanh_float1_(OID g0095) { 
    return _float_(tanh_float1(float_v(g0095)));
}


// The c++ function for: tanh(self:float) [NEW_ALLOC]
CL_EXPORT double  tanh_float1(double self) { 
      { double Result =0.0;
      { double  y = 0.0;
        y = tanh(self);
        Result = y;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// cosh(self) computes the hyperbolic cosine of self.
// The c++ function for: cosh(g0096:any) [NEW_ALLOC]
CL_EXPORT OID  cosh_float1_(OID g0096) { 
    return _float_(cosh_float1(float_v(g0096)));
}


// The c++ function for: cosh(self:float) [NEW_ALLOC]
CL_EXPORT double  cosh_float1(double self) { 
      { double Result =0.0;
      { double  y = 0.0;
        y = cosh(self);
        Result = y;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// sinh(self) computes the hyperbolic sine.
// The c++ function for: sinh(g0097:any) [NEW_ALLOC]
CL_EXPORT OID  sinh_float1_(OID g0097) { 
    return _float_(sinh_float1(float_v(g0097)));
}


// The c++ function for: sinh(self:float) [NEW_ALLOC]
CL_EXPORT double  sinh_float1(double self) { 
      { double Result =0.0;
      { double  y = 0.0;
        y = sinh(self);
        Result = y;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// make a new string from a float x.
// The c++ function for: string!(g0098:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT char * string_I_float_(OID g0098) { 
    return string_I_float(float_v(g0098));
}


// The c++ function for: string!(self:float) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT char * string_I_float(double self) { 
      print_in_string_void();
    princ_float(self);
    POP_SIGNAL; return (end_of_string_void());}
  


// @doc @xl char
// make a new string from a a char self. The returned string always has
// of length of 1. One could use make_string to create a string of a given
// length filled with a given char.
// The c++ function for: string!(self:char) [NEW_ALLOC]
CL_EXPORT char * string_I_char1(ClaireChar *self) { 
    POP_SIGNAL; return (make_string_integer(1,self));}
  


//--------- BAG --------------------------------------------------------
// @doc bag
// returns the length of a list. The length of a list is not its size !
// The c++ function for: length(self:bag) [RETURN_ARG]
CL_EXPORT CL_INT  length_bag(bag *self) { 
    POP_SIGNAL; return (self->length);}
  


// The c++ function for: nth(self:bag,x:integer) [RETURN_ARG]
CL_EXPORT OID  nth_bag(bag *self,CL_INT x) { 
    { OID Result = 0;
      if (((CL_INT)x > (CL_INT)0) && 
          ((CL_INT)x <= (CL_INT)self->length))
       Result = (*(self))[x];
      else { OID  V_CL0099;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[41] nth[~S] out of scope for ~S")),
            _oid_(list::alloc(2,((OID)x),_oid_(self))))));
          
          Result=_void_(V_CL0099);}
        POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: nth_bag_type
CL_EXPORT ClaireType * nth_bag_type(ClaireType *self,ClaireType *x) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = (((INHERIT(self->isa,Kernel._tuple)) && 
          (unique_ask_type(x) == CTRUE)) ?
        OBJECT(ClaireType,(*Kernel.nth)(_oid_(self),
          GC_OID(the_type(x)))) :
        member_type(self) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: nth_get(self:bag,x:integer) [RETURN_ARG]
CL_EXPORT OID  nth_get_bag(bag *self,CL_INT x) { 
    POP_SIGNAL; return ((*(self))[x]);}
  


// @doc bag
// min(f,self) return the element of self that has the lowest
// value according to the ordering method f. For instance :
// \code
// min(< @ integer, list(1,2,3,2,1)) -> 1
// \/code
// The c++ function for: min(f:method,self:bag) [NEW_ALLOC]
CL_EXPORT OID  min_method(method *f,bag *self) { 
    { OID Result = 0;
      if (self->length != 0)
       { OID  x = (*(self))[1];
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(y);
          for (START(self); NEXT(y);)
          if ((OBJECT(ClaireBoolean,funcall_method2(f,y,x))) == CTRUE)
           x= (y);
          }
        Result = x;
        }
      else { OID  V_CL0100;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[183] min of empty set is undefined")),
            _oid_(Kernel.nil))));
          
          Result=_void_(V_CL0100);}
        POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: min_method_type
CL_EXPORT ClaireType * min_method_type(ClaireType *f,ClaireType *self) { 
    POP_SIGNAL; return (member_type(self));}
  


// @doc bag
// max(f,self) return the element of self that has the greatest
// value according to the ordering method f. For instance :
// \code
// max(< @ integer, list(1,2,3,2,1)) -> 3
// \/code
// The c++ function for: max(f:method,self:bag) [NEW_ALLOC]
CL_EXPORT OID  max_method(method *f,bag *self) { 
    { OID Result = 0;
      if (self->length != 0)
       { OID  x = (*(self))[1];
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(y);
          for (START(self); NEXT(y);)
          if (boolean_I_any(funcall_method2(f,y,x)) != CTRUE)
           x= (y);
          }
        Result = x;
        }
      else { OID  V_CL0101;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[183] max of empty set is undefined")),
            _oid_(Kernel.nil))));
          
          Result=_void_(V_CL0101);}
        POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: max_method_type
CL_EXPORT ClaireType * max_method_type(ClaireType *f,ClaireType *self) { 
    POP_SIGNAL; return (member_type(self));}
  


// there seems to be a difficulty with providing this method with the proper type ..
// @doc bag
// x /+ y returns a new list that is the concatenation of the two bag contents.
// The c++ function for: /+(x:bag,y:bag) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT list * _7_plus_bag(bag *x,bag *y) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
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
// @doc bag
// last(l) returns l[length(l)]
// The c++ function for: last(self:list) [RETURN_ARG]
CL_EXPORT OID  last_list(list *self) { 
    { OID Result = 0;
      if ((CL_INT)self->length > (CL_INT)0)
       Result = (*(self))[self->length];
      else { OID  V_CL0102;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[41] car(nil) is undefined")),
            _oid_(Kernel.nil))));
          
          Result=_void_(V_CL0102);}
        POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: last_list_type
CL_EXPORT ClaireType * last_list_type(ClaireType *self) { 
    POP_SIGNAL; return (member_type(self));}
  


// remove the last element
// @doc bag
// removes the last element of the list self.
// The c++ function for: rmlast(self:list) [RETURN_ARG]
CL_EXPORT list * rmlast_list(list *self) { 
    delete_at_list(self,self->length);
    POP_SIGNAL; return (self);}
  


// @doc bag
// nth=(l,i,x) replace the i\sup th\/sup element of the bag l by x.
// nth(l,i,x) is equivalent to l[i] := x.
// The c++ function for: nth=(self:list,x:integer,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  nth_set_list(list *self,CL_INT x,OID y) { 
    if (((CL_INT)x <= (CL_INT)0) || 
        ((CL_INT)x > (CL_INT)self->length)) 
    { { OID Result = 0;
        { OID  V_CL0103;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[41] nth[~S] out of scope for ~S")),
            _oid_(list::alloc(2,((OID)x),_oid_(self))))));
          
          Result=_void_(V_CL0103);}
        return (Result);}
       }
    else{ 
      GC_BIND;
      { OID Result = 0;
        if (belong_to(y,_oid_(of_bag(self))) == CTRUE)
         Result = ((*(self))[x]=y);
        else { system_error * _CL_obj = ((system_error *) GC_OBJECT(system_error,new_object_class(Kernel._system_error)));
            _void_(_CL_obj->index = 17);
            _void_(_CL_obj->arg = y);
            _void_(_CL_obj->value = _oid_(self));
            add_I_property(Kernel.instances,Kernel._system_error,11,_oid_(_CL_obj));
            { OID  V_CL0104;close_exception(_CL_obj);
              
              Result=_void_(V_CL0104);}
            }
          GC_UNBIND; POP_SIGNAL; return (Result);}
      }
    }
  


// v3.2.00
// the old LISP method
// @doc bag
// Classical LISP methods that return the head of the list (e.g. l[1]).
// \code
// car(list(1,2,3)) -> 1
// car(list(3,2,1)) -> 3
// \/code
// The c++ function for: car(self:list) [RETURN_ARG]
CL_EXPORT OID  car_list(list *self) { 
    { OID Result = 0;
      if ((CL_INT)self->length > (CL_INT)0)
       Result = (*(self))[1];
      else { OID  V_CL0105;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[41] car(nil) is undefined")),
            _oid_(Kernel.nil))));
          
          Result=_void_(V_CL0105);}
        POP_SIGNAL; return (Result);}
    }
  


// hashtable basics
// The c++ function for: hashlist(n:integer) [NEW_ALLOC]
CL_EXPORT list * hashlist_integer(CL_INT n) { 
    
    GC_BIND;
    { list *Result ;
      { list * l = GC_OBJECT(list,make_list_integer(n,CNULL));
        CL_INT  u = ((CL_INT)(((CL_INT)(*(l))[0]))-(CL_INT)3);
        { CL_INT  i = ((CL_INT)n+(CL_INT)1);
          CL_INT  g0106 = u;
          { CL_INT loop_handle = ClEnv->cHandle;
            while (((CL_INT)i <= (CL_INT)g0106))
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
CL_EXPORT CL_INT  hashsize_list(list *l) { 
    { CL_INT Result = 0;
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
  


// @doc bag
// this method sorts the list self according to the ordering method f
// The c++ function for: sort(f:method,self:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT list * sort_method(method *f,list *self) { 
    quicksort_list(self,f,1,self->length);
    POP_SIGNAL; return (self);}
  


// v3.0.38: upgrade the quicksort algorithm with a better pivot selection cf.bag.cpp
// this is also proposed as a macro: cf. file.cl
// The c++ function for: quicksort(self:list,f:method,n:integer,m:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  quicksort_list(list *self,method *f,CL_INT n,CL_INT m) { 
    if ((CL_INT)m > (CL_INT)n)
     { OID  x = (*(self))[n];
      if (m == ((CL_INT)n+(CL_INT)1))
       { if ((OBJECT(ClaireBoolean,funcall_method2(f,(*(self))[m],x))) == CTRUE)
         { ((*(self))[n]=(*(self))[m]);
          ((*(self))[m]=x);
          }
        }
      else { CL_INT  p = ((CL_INT)((CL_INT)m+(CL_INT)n)>>(CL_INT)1);
          CL_INT  q = n;
          x= ((*(self))[p]);
          if (p != n)
           ((*(self))[p]=(*(self))[n]);
          { CL_INT  p = ((CL_INT)n+(CL_INT)1);
            CL_INT  g0107 = m;
            { CL_INT loop_handle = ClEnv->cHandle;
              while (((CL_INT)p <= (CL_INT)g0107))
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
CL_EXPORT set * build_powerset_list(list *self) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
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
// @doc bag
// makes a tuple from a list
// new and useful (v3.1.06)
// The c++ function for: make_copy_list(n:integer,d:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT list * make_copy_list_integer(CL_INT n,OID d) { 
    
    GC_BIND;
    { list *Result ;
      { list * l = GC_OBJECT(list,make_list_integer(n,d));
        if (INHERIT(OWNER(d),Kernel._bag))
         { CL_INT  i = 1;
          CL_INT  g0108 = n;
          { CL_INT loop_handle = ClEnv->cHandle;
            while (((CL_INT)i <= (CL_INT)g0108))
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
// @doc bag
// difference(s, t) returns the difference set s - t, that is the set of all elements of
// s which are not elements of t.
// The c++ function for: difference(self:set,x:set) [NEW_ALLOC]
CL_EXPORT set * difference_set(set *self,set *x) { 
    
    GC_BIND;
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
// @doc array
// nth=(a,i,x) replace the i\sup th\/sup element of the array a by x.
// nth(a,i,x) is equivalent to a[i] := x.
// The c++ function for: nth=(self:array,x:integer,y:any) [RETURN_ARG]
CL_EXPORT void  nth_equal_array(OID *self,CL_INT x,OID y) { 
    if (belong_to(y,_oid_(of_array(self))) != CTRUE)
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"type mismatch for array update ~S, ~S")),
      _oid_(list::alloc(2,y,_array_(self))))));
    else if (((CL_INT)x > (CL_INT)0) && 
        ((CL_INT)x <= (CL_INT)self[0]))
     nth_put_array(self,x,y);
    else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"nth[~S] out of scope for ~S")),
        _oid_(list::alloc(2,((OID)x),_array_(self))))));
      POP_SIGNAL;}
  


// The c++ function for: self_print(self:array) [NEW_ALLOC]
CL_EXPORT void  self_print_array_Core(OID *self) { 
    princ_string(((char*)"array<"));
    print_any(_oid_(of_array(self)));
    princ_string(((char*)">["));
    princ_integer(self[0]);
    princ_string(((char*)"]"));
    POP_SIGNAL;}
  


//---------------------- CHAR --------------------------------------------
//printf("'~A'", self)
// @doc char
// returns true if ASCII code of x is lower or equal to ASCII code of y
// The c++ function for: <=(c1:char,c2:char) [0]
CL_EXPORT ClaireBoolean * _inf_equal_char(ClaireChar *c1,ClaireChar *c2) { 
    POP_SIGNAL; return (_inf_equal_integer((CL_INT)c1->ascii,c2->ascii));}
  


// three methods that are useful for debugging !
//<sb> imported from Reader/file.cl
// This is the good version of kill, the nasty one is dangerous ....
// these restrictions of kill explain the dependencies among objects
//
// @doc class
// kill(x) is used to remove an object from the database of the language.
// kill(x) does it properly, removing the object from all the relation
// network but without deallocating.
// The c++ function for: kill(self:object) [SLOT_UPDATE]
CL_EXPORT OID  kill_object(ClaireObject *self) { 
    if (INHERIT(self->isa,Kernel._thing))
     put_symbol(CLREAD(thing,self,name),CNULL);
    _void_(self->isa->instances = ((list *) delete_bag(self->isa->instances,_oid_(self))));
    POP_SIGNAL; return (_oid_(Kernel.emptySet));}
  


// @doc class
// kill(x) is used to remove an object from the database of the language.
// kill(x) does it properly, removing the object from all the relation
// network but without deallocating.
// The c++ function for: kill(self:class) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  kill_class(ClaireClass *self) { 
    { CL_INT loop_handle = ClEnv->cHandle;
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
  


// @doc string
// transforms a string into a float.
// The c++ function for: float!(g0109:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  float_I_string_(char *g0109) { 
    return _float_(float_I_string(g0109));
}


// The c++ function for: float!(self:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT double  float_I_string(char *self) { 
      
    GC_BIND;
    { double Result =0.0;
      { blob * p = GC_OBJECT(blob,blob_I_string1(self));
        ClaireBoolean * neg;
        if (((unsigned char) nth_blob1(p,1)->ascii) == ((unsigned char)'-'))
         { nth_equal_blob1(p,1,_char_(((unsigned char)'0')));
          neg = CTRUE;
          }
        else if (((unsigned char) nth_blob1(p,1)->ascii) == ((unsigned char)'+'))
         { nth_equal_blob1(p,1,_char_(((unsigned char)'0')));
          neg = CFALSE;
          }
        else neg = CFALSE;
          OID  x;
        { _void_(p->firstc = integer_I_char(_char_(((unsigned char)'0'))));
          x = (OID )(read_number_port(p));
          }
        fclose_port1(p);
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
        else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[??] ~A is not a float")),
            _oid_(list::alloc(1,_string_(self))))));
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl Miscellaneous
// unix?() tell if the underlying system is a UNIX (vs. windows).
// The c++ function for: unix?(_CL_obj:void) [0]
CL_EXPORT ClaireBoolean * unix_ask_void1() { 
    POP_SIGNAL; return (((ClaireBoolean *) (ClaireBoolean *)(
#ifdef CLPC
CFALSE
#else
CTRUE
#endif
)));}
  


// The c++ function for: strffloat(g0110:string,g0111:any) [NEW_ALLOC]
CL_EXPORT char * strffloat_string1_(char *g0110,OID g0111) { 
    return strffloat_string1(g0110,float_v(g0111));
}


// The c++ function for: strffloat(f:string,d:float) [NEW_ALLOC]
CL_EXPORT char * strffloat_string1(char *f,double d) { 
      char buf[1024];
    sprintf(buf,f,d);
    POP_SIGNAL; return (copy_string((char *)(buf)));}
  


//<sb> @doc @xl Miscellaneous
// chroot(dirname) causes dirname to become the root directory, that
// is, the starting point for path searches of pathnames beginning with '/'.\br
// This call is restricted to the super-user.
// The c++ function for: chroot(dir:string) [0]
CL_EXPORT void  chroot_string1(char *dir) { 
    
		#ifndef CLPC
		if (::chroot(dir) == -1)
			Cerrorno(74, _string_("chroot @ string"), 0);
		#endif
	;
    POP_SIGNAL;}
  


//<sb> @doc @xl Process handling
// fork, when called in CLAIRE applies all existing on_fork
// with the domain void.
// the on_fork callback is applied just before the fork, that is
// the parent process only. For instance :
// \code
// on_fork() : void -> printf("attemp to fork...\n")
// \/code
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
// The c++ function for: fork(_CL_obj:void) [NEW_ALLOC]
CL_EXPORT CL_INT  fork_void1() { 
    { CL_INT loop_handle = ClEnv->cHandle;
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
  


// The c++ function for: forker?(_CL_obj:void) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT ClaireBoolean * forker_ask_void1() { 
    POP_SIGNAL; return (_I_equal_any(((OID)fork_void1()),((OID)0)));}
  


// The c++ function for: forked?(_CL_obj:void) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT ClaireBoolean * forked_ask_void1() { 
    POP_SIGNAL; return (equal(((OID)fork_void1()),((OID)0)));}
  



/***** CLAIRE Compilation of file ./meta/types.cl 
         [version 3.5.0 / safety 5] *****/


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
// *********************************************************************
// *   Part 1: Common Set Methods                                      *
// *********************************************************************
// ----------------------- useful methods ------------------------------
// @doc type
// finite?(self) returns true if the type self represents a finite set.
// Set iteration (with the for loop) can only be done over finite sets.
// The c++ function for: finite?(self:type) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * finite_ask_type(ClaireType *self) { 
    { ClaireBoolean *Result ;
      if (Kernel._set == self->isa)
       Result = CTRUE;
      else if (INHERIT(self->isa,Kernel._list))
       { OID  g0112UU;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(t);
          g0112UU= Kernel.cfalse;
          for (START(((bag *) self)); NEXT(t);)
          if ((*Core.finite_ask)(t) != Kernel.ctrue)
           { g0112UU = Kernel.ctrue;
            ClEnv->cHandle = loop_handle;break;}
          else ;}
        Result = not_any(g0112UU);
        }
      else if (INHERIT(self->isa,Kernel._class))
       { CL_INT  n = CLREAD(ClaireClass,self,open);
        Result = (((CL_INT)0 <= (CL_INT)n) ? (((CL_INT)n <= (CL_INT)2) ? ((self != Kernel._any) ? CTRUE: CFALSE): CFALSE): CFALSE);
        }
      else Result = CFALSE;
        POP_SIGNAL; return (Result);}
    }
  


// making a bag from an abstract_set
// The c++ function for: enumerate(self:any) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT bag * enumerate_any(OID self) { 
    { bag *Result ;
      { ClaireObject *V_CC ;
        if (INHERIT(OWNER(self),Kernel._bag))
         V_CC = OBJECT(bag,self);
        else if (Kernel._array == OWNER(self))
         V_CC = list_I_array(array_v(self));
        else if (INHERIT(OWNER(self),Kernel._integer))
         V_CC = make_set_integer(self);
        else if (INHERIT(OWNER(self),Kernel._collection))
         V_CC = OBJECT(set,(*Kernel.set_I)(self));
        else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[178] cannot enumerate ~S")),
            _oid_(list::alloc(1,self)))));
          Result= (bag *) V_CC;}
      POP_SIGNAL; return (Result);}
    }
  


// =type? is an operation (equality on types)
// @doc type
// returns true if x and y denote the same type. For example =type?(boolean, {true, false})
// returns true because defined(boolean) was declared after the two instances true and false
// were created, so the system knows that no other instances of boolean may ever be created
// in the future. This equality is stronger than set equality in the sense that the system
// answers true if it knows that the answer will hold everafter.
// The c++ function for: =type?(self:type,ens:type) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * _equaltype_ask_any(ClaireType *self,ClaireType *ens) { 
    POP_SIGNAL; return (((_inf_equal_type(self,ens) == CTRUE) ? ((_inf_equal_type(ens,self) == CTRUE) ? CTRUE: CFALSE): CFALSE));}
  


// finds the sort associated to a type
// The c++ function for: sort!(x:type) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT ClaireClass * sort_I_type(ClaireType *x) { 
    { ClaireClass *Result ;
      Result = ((INHERIT(x->isa,Kernel._class)) ?
        sort_I_class(((ClaireClass *) x)) :
        sort_I_class(class_I_type(x)) );
      POP_SIGNAL; return (Result);}
    }
  


// the membership membership for lattice_sets
// The c++ function for: %(self:any,ens:class) [0]
CL_EXPORT ClaireBoolean * _Z_any1(OID self,ClaireClass *ens) { 
    { ClaireBoolean *Result ;
      Result = ((INHERIT(OWNER(self),ens)) ?
        CTRUE :
        CFALSE );
      POP_SIGNAL; return (Result);}
    }
  


// an extension for %
// The c++ function for: mClaire/%type(x:any,y:any) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * Ztype_any(OID x,OID y) { 
    { ClaireBoolean *Result ;
      if ((INHERIT(OWNER(x),Kernel._type)) && 
          (Kernel._set == OWNER(y)))
       { OID  g0113UU;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(z);
          g0113UU= Kernel.cfalse;
          for (START(OBJECT(set,y)); NEXT(z);)
          if (_equaltype_ask_any(OBJECT(ClaireType,x),OBJECT(ClaireType,z)) == CTRUE)
           { g0113UU = Kernel.ctrue;
            ClEnv->cHandle = loop_handle;break;}
          }
        Result = boolean_I_any(g0113UU);
        }
      else Result = belong_to(x,y);
        POP_SIGNAL; return (Result);}
    }
  


// ****************************************************************
// *         Part 2: definition of the type operators             *
// ****************************************************************
// union of two types ---------------------------------------------
// Disjonctive Union Axiom (DU): Each union (A U B) is strictly disjunctive:
//       (1) A ^ B = 0
//       (2) x < A U B <=> x < A or x < B
// Producing disjunction union is a form of normalization (the previous notion
// of distributivity was a lousy bug)
// DU Axiom is necessary to make <= and ^ easier to define
// This is achieved in the U method
// The c++ function for: self_print(self:Union) [NEW_ALLOC]
CL_EXPORT void  self_print_Union_Core(Union *self) { 
    
    GC_BIND;
    princ_string(((char*)"("));
    print_any(GC_OID(_oid_(self->t1)));
    princ_string(((char*)" U "));
    print_any(GC_OID(_oid_(self->t2)));
    princ_string(((char*)")"));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: finite?(self:Union) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * finite_ask_Union(Union *self) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = (((OBJECT(ClaireBoolean,(*Core.finite_ask)(GC_OID(_oid_(self->t1))))) == CTRUE) ? (((OBJECT(ClaireBoolean,(*Core.finite_ask)(GC_OID(_oid_(self->t2))))) == CTRUE) ? CTRUE: CFALSE): CFALSE);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// Intervals of integers ----------
// The c++ function for: self_print(self:Interval) [NEW_ALLOC]
CL_EXPORT void  self_print_Interval_Core(Interval *self) { 
    princ_string(((char*)"("));
    print_any(((OID)self->arg1));
    princ_string(((char*)" .. "));
    print_any(((OID)self->arg2));
    princ_string(((char*)")"));
    POP_SIGNAL;}
  


// The c++ function for: finite?(self:Interval) [0]
CL_EXPORT ClaireBoolean * finite_ask_Interval(Interval *self) { 
    POP_SIGNAL; return (CTRUE);}
  


// true constructor
// The c++ function for: --(x:integer,y:integer) [NEW_ALLOC]
CL_EXPORT Interval * _dash_dash_integer(CL_INT x,CL_INT y) { 
    { Interval *Result ;
      { ClaireObject *V_CC ;
        if ((CL_INT)x <= (CL_INT)y)
         V_CC = (ClaireType *)_dot_dot_integer(x,y);
        else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[182] the interval (~S -- ~S) is empty")),
            _oid_(list::alloc(2,((OID)x),((OID)y))))));
          Result= (Interval *) V_CC;}
      POP_SIGNAL; return (Result);}
    }
  


// Parameterized class. -------------------------------------------
// The c++ function for: self_print(self:Param) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_Param_Core(Param *self) { 
    
    GC_BIND;
    if ((self->params->length == 1) && 
        (((*(self->params))[1] == _oid_(Kernel.of)) && 
          (Kernel._set == OWNER((*(self->args))[1]))))
     { print_any(_oid_(self->arg));
      princ_string(((char*)"<"));
      print_any(GC_OID((*(OBJECT(set,(*(self->args))[1])))[1]));
      princ_string(((char*)">"));
      }
    else { print_any(_oid_(self->arg));
        princ_string(((char*)"["));
        { CL_INT  i = 1;
          CL_INT  g0114 = self->args->length;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)i <= (CL_INT)g0114))
            { GC_LOOP;
              if (i != 1)
               princ_string(((char*)", "));
              print_any(GC_OID((*(self->params))[i]));
              princ_string(((char*)":("));
              print_any(GC_OID((*(self->args))[i]));
              princ_string(((char*)")"));
              ++i;
              GC_UNLOOP;POP_SIGNAL;}
            }
          }
        princ_string(((char*)"]"));
        }
      GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: finite?(self:Param) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * finite_ask_Param(Param *self) { 
    POP_SIGNAL; return (finite_ask_type(self->arg));}
  


// subtype[X] ----------------------------------------------
// subtype[X] = {u in type | u <= t}
// for closure purposes, we add an arg Y -> Y inter st[X]
// Y can be any type class, but we forbid parametrisation on such classes !
// thus we can ensure that Y is a class
// The c++ function for: self_print(self:subtype) [NEW_ALLOC]
CL_EXPORT void  self_print_subtype_Core(subtype *self) { 
    
    GC_BIND;
    if (self->arg == Kernel._type)
     { princ_string(((char*)"subtype["));
      print_any(GC_OID(_oid_(self->t1)));
      princ_string(((char*)"]"));
      }
    else { print_any(_oid_(self->arg));
        princ_string(((char*)"["));
        print_any(GC_OID(_oid_(self->t1)));
        princ_string(((char*)"]"));
        }
      GC_UNBIND; POP_SIGNAL;}
  


// v3.2
// The c++ function for: finite?(self:subtype) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * finite_ask_subtype(subtype *self) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = ((self->arg == Kernel._set) ? (((OBJECT(ClaireBoolean,(*Core.finite_ask)(GC_OID(_oid_(self->t1))))) == CTRUE) ? CTRUE: CFALSE): CFALSE);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// creates a subtype, with some normalization
// v3.2 list[t] -> subtype 
// The c++ function for: nth(self:class,x:type) [NEW_ALLOC]
CL_EXPORT ClaireType * nth_class1(ClaireClass *self,ClaireType *x) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { ClaireObject *V_CC ;
        if ((self == Kernel._set) || 
            (self == Kernel._list))
         { subtype * _CL_obj = ((subtype *) GC_OBJECT(subtype,new_object_class(Core._subtype)));
          _void_(_CL_obj->arg = self);
          _void_(_CL_obj->t1 = x);
          V_CC = _CL_obj;
          }
        else if (inherit_ask_class(self,Kernel._type) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[177] subtyping of ~S not allowed")),
          _oid_(list::alloc(1,_oid_(self))))));
        else { subtype * _CL_obj = ((subtype *) GC_OBJECT(subtype,new_object_class(Core._subtype)));
            _void_(_CL_obj->arg = ((self == Core._subtype) ?
              Kernel._type :
              self ));
            _void_(_CL_obj->t1 = x);
            V_CC = _CL_obj;
            }
          Result= (ClaireType *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// create a Param with a list of parameters (constant properties) l1 and a list
// of types l2
// The c++ function for: nth(self:class,l1:list,l2:list) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT ClaireType * nth_class2(ClaireClass *self,list *l1,list *l2) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { ClaireObject *V_CC ;
        if (((self == Kernel._list) || 
              (self == Kernel._set)) && 
            (INHERIT(OWNER((*(l2))[1]),Core._subtype)))
         V_CC = nth_class1(self,GC_OBJECT(ClaireType,OBJECT(subtype,(*(l2))[1])->t1));
        else if (((self == Kernel._list) || 
              (self == Kernel._set)) && 
            ((*(l1))[1] != _oid_(Kernel.of)))
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[177] the subtyping expression ~S[~A] is not allowed")),
          _oid_(list::alloc(2,_oid_(self),_oid_(l1))))));
        else { Param * _CL_obj = ((Param *) GC_OBJECT(Param,new_object_class(Core._Param)));
            _void_(_CL_obj->arg = self);
            _void_(_CL_obj->params = l1);
            _void_(_CL_obj->args = l2);
            V_CC = _CL_obj;
            }
          Result= (ClaireType *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// create a Param of the stack[X] kind
// The c++ function for: param!(self:class,tx:type) [NEW_ALLOC]
CL_EXPORT ClaireType * param_I_class(ClaireClass *self,ClaireType *tx) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { Param * _CL_obj = ((Param *) GC_OBJECT(Param,new_object_class(Core._Param)));
        _void_(_CL_obj->arg = self);
        _void_(_CL_obj->params = list::alloc(1,_oid_(Kernel.of)));
        _void_(_CL_obj->args = list::alloc(1,_oid_(set::alloc(1,_oid_(tx)))));
        Result = _CL_obj;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// create the t[] param
// The c++ function for: nth(self:type) [NEW_ALLOC]
CL_EXPORT ClaireType * nth_type(ClaireType *self) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { Param * _CL_obj = ((Param *) GC_OBJECT(Param,new_object_class(Core._Param)));
        _void_(_CL_obj->arg = Kernel._array);
        _void_(_CL_obj->params = list::alloc(1,_oid_(Kernel.of)));
        _void_(_CL_obj->args = list::alloc(1,_oid_(set::alloc(1,_oid_(self)))));
        Result = _CL_obj;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// tuple are types
// The c++ function for: finite?(self:tuple) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * finite_ask_tuple(tuple *self) { 
    { ClaireBoolean *Result ;
      { OID  g0115UU;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(x);
          g0115UU= Kernel.cfalse;
          for (START(self); NEXT(x);)
          if ((*Core.finite_ask)(x) != Kernel.ctrue)
           { g0115UU = Kernel.ctrue;
            ClEnv->cHandle = loop_handle;break;}
          }
        Result = not_any(g0115UU);
        }
      POP_SIGNAL; return (Result);}
    }
  


// reference to a previous variable, not a type but a pattern -------
// index is the position of the stack of the referred type
// args is a list representing the path (a sequence of properties (parameters))
// a property is applied to the referred type
// if arg = true, the reference is the singleton containing the ref. value
// TODO check that arg is still used !
// The c++ function for: self_print(self:Reference) [NEW_ALLOC]
CL_EXPORT void  self_print_Reference_Core(Reference *self) { 
    
    GC_BIND;
    princ_string(((char*)"<ref:"));
    print_any(GC_OID(_oid_(self->args)));
    princ_string(((char*)"(ltype["));
    princ_integer(self->index);
    princ_string(((char*)"])>"));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: get(self:Reference,y:any) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  get_Reference(Reference *self,OID y) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { OID Result = 0;
      { list * l = self->args;
        { CL_INT  i = 1;
          CL_INT  g0116 = l->length;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)i <= (CL_INT)g0116))
            { GC_LOOP;
              GC__OID(y = funcall_property(OBJECT(property,(*(l))[i]),y), 1);
              ++i;
              GC_UNLOOP;POP_SIGNAL;}
            }
          }
        Result = y;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// apply a reference to a type (l is args(self), passed for disambiguation)
// The c++ function for: @(self:Reference,l:list,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  _at_Reference(Reference *self,list *l,OID y) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    if (should_trace_ask_module1(Core.it,5) == CTRUE)
     mtformat_module1(Core.it,((char*)"apply[@] ~S to ~S \n"),5,list::alloc(2,_oid_(self),y));
    else ;{ CL_INT  i = 1;
      CL_INT  g0117 = l->length;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)i <= (CL_INT)g0117))
        { GC_LOOP;
          GC__OID(y = _oid_(_at_type(OBJECT(ClaireType,y),OBJECT(property,(*(l))[i]))), 1);
          ++i;
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    { OID Result = 0;
      Result = y;
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// type to set coercion  -------------------------------------------------
// new in v3.0.5 = use an interface method for type enumeration
// the default strategy is extensible: we look if there exists
// a proper definition that could be interpreted !
// The c++ function for: set!(x:collection) [NEW_ALLOC]
CL_EXPORT set * set_I_collection(ClaireCollection *x) { 
    
    GC_BIND;
    { set *Result ;
      { ClaireObject *V_CC ;
        { OID  m = GC_OID(_oid_(_at_property1(Kernel.set_I,x->isa)));
          if (domain_I_restriction(OBJECT(restriction,m)) != Kernel._collection)
           V_CC = OBJECT(set,(*Kernel.funcall)(m,
            _oid_(x)));
          else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[178] cannot enumerate ~S")),
              _oid_(list::alloc(1,_oid_(x))))));
            }
        Result= (set *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: size(x:collection) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT CL_INT  size_collection(ClaireCollection *x) { 
    
    GC_BIND;
    { CL_INT Result = 0;
      { OID  m = GC_OID(_oid_(_at_property1(Core.size,x->isa)));
        Result = ((domain_I_restriction(OBJECT(restriction,m)) != Kernel._collection) ?
          ((CL_INT)(*Kernel.funcall)(m,
            _oid_(x))) :
          length_bag(OBJECT(bag,(*Kernel.set_I)(_oid_(x)))) );
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// v3.2.34  -> makes the API simpler
// set is needed for recursive def
// The c++ function for: set!(x:set) [RETURN_ARG]
CL_EXPORT set * set_I_set(set *x) { 
    POP_SIGNAL; return (x);}
  


// The c++ function for: size(x:set) [RETURN_ARG]
CL_EXPORT CL_INT  size_set(set *x) { 
    POP_SIGNAL; return (x->length);}
  


// set is needed for recursive def
// The c++ function for: size(x:list) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT CL_INT  size_list2_Core(list *x) { 
    POP_SIGNAL; return (length_bag(set_I_bag(x)));}
  


// class  -> return a read-only list  (v3.2)
// The c++ function for: set!(x:class) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT set * set_I_class(ClaireClass *x) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { set *Result ;
      { list * rep = list::empty(Kernel._class);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(c);
          for (START(x->descendents); NEXT(c);)
          { GC_LOOP;
            if ((INHERIT(OBJECT(ClaireClass,c),Kernel._primitive)) && 
                (c != _oid_(Kernel._boolean)))
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[178] cannot enumerate ~S")),
              _oid_(list::alloc(1,c)))));
            else GC__ANY(rep = append_list(rep,OBJECT(ClaireClass,c)->instances), 1);
              GC_UNLOOP; POP_SIGNAL;}
          }
        Result = set_I_bag(rep);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: size(self:class) [SAFE_RESULT]
CL_EXPORT CL_INT  size_class(ClaireClass *self) { 
    { CL_INT Result = 0;
      { CL_INT  n = 0;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(x);
          for (START(self->descendents); NEXT(x);)
          n= (CL_INT)(((CL_INT)n+(CL_INT)OBJECT(ClaireClass,x)->instances->length));
          }
        Result = n;
        }
      POP_SIGNAL; return (Result);}
    }
  


// Union
// The c++ function for: set!(x:Union) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT set * set_I_Union(Union *x) { 
    
    GC_BIND;
    { set *Result ;
      Result = append_set(GC_OBJECT(set,OBJECT(set,(*Kernel.set_I)(GC_OID(_oid_(x->t1))))),GC_OBJECT(set,OBJECT(set,(*Kernel.set_I)(GC_OID(_oid_(x->t2))))));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: size(x:Union) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT CL_INT  size_Union(Union *x) { 
    
    GC_BIND;
    { CL_INT Result = 0;
      Result = (((INHERIT(x->t1->isa,Core._Interval)) || 
          (Kernel._set == x->t1->isa)) ?
        ((CL_INT)(((CL_INT)Core.size->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(x->t1)))))))+(CL_INT)(((CL_INT)Core.size->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(x->t2)))))))) :
        length_bag(set_I_Union(x)) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// interval
// The c++ function for: set!(x:Interval) [NEW_ALLOC]
CL_EXPORT set * set_I_Interval(Interval *x) { 
    POP_SIGNAL; return (sequence_integer(x->arg1,x->arg2));}
  


// The c++ function for: size(self:Interval) [RETURN_ARG]
CL_EXPORT CL_INT  size_Interval(Interval *self) { 
    POP_SIGNAL; return (((CL_INT)((CL_INT)self->arg2+(CL_INT)1)-(CL_INT)self->arg1));}
  


// param
// The c++ function for: set!(x:Param) [NEW_ALLOC]
CL_EXPORT set * set_I_Param(Param *x) { 
    
    GC_BIND;
    { set *Result ;
      { bag * y_in = set_I_class(x->arg);
        set * y_out = ((set *) empty_bag(y_in));
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(y);
          for (START(y_in); NEXT(y);)
          if (belong_to(y,_oid_(x)) == CTRUE)
           y_out->addFast((OID)y);
          }
        Result = GC_OBJECT(set,y_out);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: size(x:Param) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT CL_INT  size_Param(Param *x) { 
    POP_SIGNAL; return (length_bag(set_I_Param(x)));}
  


// subtype
// The c++ function for: set!(x:subtype) [NEW_ALLOC+BAG_UPDATE]
CL_EXPORT set * set_I_subtype(subtype *x) { 
    
    GC_BIND;
    { set *Result ;
      { ClaireObject *V_CC ;
        if (x->arg == Kernel._set)
         V_CC = build_powerset_list(GC_OBJECT(list,list_I_set(GC_OBJECT(set,OBJECT(set,(*Kernel.set_I)(GC_OID(_oid_(x->t1))))))));
        else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[178] cannot enumerate ~S")),
            _oid_(list::alloc(1,_oid_(x))))));
          Result= (set *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: size(x:subtype) [NEW_ALLOC]
CL_EXPORT CL_INT  size_subtype(subtype *x) { 
    
    GC_BIND;
    { CL_INT Result = 0;
      if (x->arg == Kernel._set)
       Result = exp2_integer(((CL_INT)Core.size->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(x->t1)))))));
      else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[178] cannot enumerate ~S")),
          _oid_(list::alloc(1,_oid_(x))))));
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// tuple
// The c++ function for: set!(x:tuple) [NEW_ALLOC]
CL_EXPORT set * set_I_tuple(tuple *x) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { set *Result ;
      { list * l = ((list *) x);
        if (boolean_I_any(_oid_(l)) != CTRUE)
         Result = set::alloc(Kernel.emptySet,1,_oid_(Kernel.emptySet));
        else { set * l1;
            { { set * y_bag = set::empty(Kernel.emptySet);
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(y);
                  bag *y_support;
                  y_support = GC_OBJECT(set,OBJECT(bag,(*Kernel.set_I)((*(l))[1])));
                  for (START(y_support); NEXT(y);)
                  y_bag->addFast((OID)_oid_(list::alloc(1,y)));
                  }
                l1 = GC_OBJECT(set,y_bag);
                }
              GC_OBJECT(set,l1);}
            { CL_INT  n = 2;
              CL_INT  g0118 = l->length;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                while (((CL_INT)n <= (CL_INT)g0118))
                { GC_LOOP;
                  { set * l2 = GC_OBJECT(set,set::empty(Kernel._any));
                    { CL_INT loop_handle = ClEnv->cHandle;
                      ITERATE(z);
                      bag *z_support;
                      z_support = GC_OBJECT(set,OBJECT(bag,(*Kernel.set_I)((*(l))[n])));
                      for (START(z_support); NEXT(z);)
                      { CL_INT loop_handle = ClEnv->cHandle;
                        ITERATE(l3);
                        for (START(l1); NEXT(l3);)
                        l2= (l2->addFast((OID)_oid_(((list *) copy_bag(OBJECT(bag,l3)))->addFast((OID)z))));
                        }
                      }
                    GC__ANY(l1 = l2, 1);
                    }
                  ++n;
                  GC_UNLOOP;POP_SIGNAL;}
                }
              }
            Result = l1;
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: size(l:tuple) [NEW_ALLOC]
CL_EXPORT CL_INT  size_tuple(tuple *l) { 
    { CL_INT Result = 0;
      if (boolean_I_any(_oid_(l)) != CTRUE)
       Result = 1;
      else { CL_INT  m = ((CL_INT)(*Core.size)((*(l))[1]));
          { CL_INT  n = 2;
            CL_INT  g0119 = l->length;
            { CL_INT loop_handle = ClEnv->cHandle;
              while (((CL_INT)n <= (CL_INT)g0119))
              { m= (CL_INT)(((CL_INT)m*(CL_INT)(((CL_INT)(*Core.size)((*(l))[n])))));
                ++n;
                POP_SIGNAL;}
              }
            }
          Result = m;
          }
        POP_SIGNAL; return (Result);}
    }
  


// generic collection membership
// v3.2.24: this is extensible through the redefinition of %
// The c++ function for: member?(x:any,y:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireBoolean * member_ask_any(OID x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      { ClaireObject *V_CC ;
        if (INHERIT(y->isa,Core._Union))
         V_CC = ((member_ask_any(x,GC_OBJECT(ClaireType,CLREAD(Union,y,t1))) == CTRUE) ? CTRUE : ((member_ask_any(x,GC_OBJECT(ClaireType,CLREAD(Union,y,t2))) == CTRUE) ? CTRUE : CFALSE));
        else if (INHERIT(y->isa,Core._Interval))
         { V_CC = ((INHERIT(OWNER(x),Kernel._integer)) ?
            (((CL_INT)CLREAD(Interval,y,arg1) <= (CL_INT)x) ? (((CL_INT)x <= (CL_INT)CLREAD(Interval,y,arg2)) ? CTRUE: CFALSE): CFALSE) :
            CFALSE );
          }
        else if (INHERIT(y->isa,Core._Param))
         { CL_INT  n = 1;
          list * l = GC_OBJECT(list,CLREAD(Param,y,args));
          { ClaireBoolean *v_and;
            { v_and = _Z_any1(x,CLREAD(Param,y,arg));
              if (v_and == CFALSE) V_CC =CFALSE; 
              else { { OID  g0121UU;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    OID gc_local;
                    ITERATE(p);
                    g0121UU= Kernel.cfalse;
                    bag *p_support;
                    p_support = GC_OBJECT(list,CLREAD(Param,y,params));
                    for (START(p_support); NEXT(p);)
                    { GC_LOOP;
                      if (Ztype_any(GC_OID(funcall_property(OBJECT(property,p),x)),(*(l))[n]) != CTRUE)
                       { GC_UNLOOP;g0121UU = Kernel.ctrue;
                        ClEnv->cHandle = loop_handle;break;}
                      else ++n;
                        GC_UNLOOP; POP_SIGNAL;}
                    }
                  v_and = not_any(g0121UU);
                  }
                if (v_and == CFALSE) V_CC =CFALSE; 
                else V_CC = CTRUE;}
              }
            }
          }
        else if (INHERIT(y->isa,Core._subtype))
         V_CC = (((CLREAD(subtype,y,arg) == Core._subtype) ? (INHERIT(OWNER(x),Kernel._type)) : (_Z_any1(x,CLREAD(subtype,y,arg)) == CTRUE)) ? (((OBJECT(ClaireBoolean,(*Core._inf_equalt)(x,
          GC_OID(_oid_(CLREAD(subtype,y,t1)))))) == CTRUE) ? CTRUE: CFALSE): CFALSE);
        else if (INHERIT(y->isa,Kernel._tuple))
         { CL_INT  n = ((bag *) y)->length;
          if (INHERIT(OWNER(x),Kernel._tuple))
           { ClaireBoolean *v_and;
            { v_and = ((OBJECT(bag,x)->length == n) ? CTRUE : CFALSE);
              if (v_and == CFALSE) V_CC =CFALSE; 
              else { { OID  g0122UU;
                  { CL_INT  i = 1;
                    CL_INT  g0120 = n;
                    { CL_INT loop_handle = ClEnv->cHandle;
                      g0122UU= _oid_(CFALSE);
                      while (((CL_INT)i <= (CL_INT)g0120))
                      { if (belong_to((*(OBJECT(bag,x)))[i],(*(((bag *) y)))[i]) != CTRUE)
                         { g0122UU = Kernel.ctrue;
                          ClEnv->cHandle = loop_handle;break;}
                        ++i;
                        POP_SIGNAL;}
                      }
                    }
                  v_and = not_any(g0122UU);
                  }
                if (v_and == CFALSE) V_CC =CFALSE; 
                else V_CC = CTRUE;}
              }
            }
          else V_CC = CFALSE;
            }
        else if (INHERIT(y->isa,Kernel._bag))
         V_CC = belong_to(x,_oid_(y));
        else if (INHERIT(y->isa,Kernel._class))
         V_CC = _Z_any1(x,((ClaireClass *) y));
        else if (INHERIT(y->isa,Core._Reference))
         V_CC = CTRUE;
        else { CL_INT  start = ClEnv->index;
            PUSH(x);
            PUSH(_oid_(y));
            { ClaireObject * m = find_which_property1(Kernel._Z,start,OWNER(x));
              if ((Kernel._method == m->isa) && ((CLREAD(restriction,m,domain)->length == 2) && 
                  ((*(CLREAD(restriction,m,domain)))[2] != _oid_(Kernel._any))))
               V_CC = OBJECT(ClaireBoolean,eval_message_property(Kernel._Z,m,start,CTRUE));
              else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[179] (~S % ~S): not implemented!")),
                  _oid_(list::alloc(2,x,_oid_(y))))));
                }
            }
          Result= (ClaireBoolean *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// @doc class
// class!(x) returns the intersection of all classes y such that x <= y that is
// the best class approximation
// (Such an intersection always exists since classes are organized in a lattice).
// Hence, if c is a class class!(c) = c.
// The c++ function for: class!(x:type) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT ClaireClass * class_I_type(ClaireType *x) { 
    
    GC_BIND;
    { ClaireClass *Result ;
      { ClaireType *V_CC ;
        if (INHERIT(x->isa,Kernel._class))
         V_CC = x;
        else if (Kernel._set == x->isa)
         { if (((bag *) x)->length == 0)
           V_CC = Kernel._void;
          else { ClaireClass * rep = OWNER((*(((bag *) x)))[1]);
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(y);
                for (START(((bag *) x)); NEXT(y);)
                rep= (meet_class(rep,OWNER(y)));
                }
              V_CC = rep;
              }
            }
        else if (INHERIT(x->isa,Core._Union))
         V_CC = meet_class(class_I_type(CLREAD(Union,x,t1)),class_I_type(CLREAD(Union,x,t2)));
        else if (INHERIT(x->isa,Core._Interval))
         V_CC = Kernel._integer;
        else V_CC = ((INHERIT(x->isa,Core._subtype)) ?
          ((CLREAD(subtype,x,arg) == Core._subtype) ?
            Kernel._any :
            CLREAD(subtype,x,arg) ) :
          ((INHERIT(x->isa,Core._Param)) ?
            CLREAD(Param,x,arg) :
            ((INHERIT(x->isa,Core._Reference)) ?
              Kernel._any :
              ((INHERIT(x->isa,Kernel._tuple)) ?
                Kernel._tuple :
                Kernel._any ) ) ) );
        Result= (ClaireClass *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// declarations
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
// The c++ function for: U(x:type,y:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT ClaireType * U_type(ClaireType *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (Kernel._set == x->isa)
       { if (Kernel._set == y->isa)
         Result = append_set(((set *) x),((set *) y));
        else Result = U_type(y,x);
          }
      else if ((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core._inf_equalt->fcall(((CL_INT) y),((CL_INT) x))))) == CTRUE)
       Result = x;
      else if ((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core._inf_equalt->fcall(((CL_INT) x),((CL_INT) y))))) == CTRUE)
       Result = y;
      else if (INHERIT(y->isa,Core._Union))
       Result = U_type(GC_OBJECT(ClaireType,U_type(x,GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Core.t1)(_oid_(y)))))),GC_OBJECT(ClaireType,CLREAD(Union,y,t2)));
      else if ((INHERIT(x->isa,Core._Interval)) && (INHERIT(y->isa,Core._Interval)))
       { if (((CL_INT)((CL_INT)CLREAD(Interval,y,arg1)-(CL_INT)1) <= (CL_INT)CLREAD(Interval,x,arg2)) && 
            ((CL_INT)CLREAD(Interval,x,arg1) <= (CL_INT)CLREAD(Interval,y,arg1)))
         Result = (ClaireType *)_dot_dot_integer(CLREAD(Interval,x,arg1),CLREAD(Interval,y,arg2));
        else if (((CL_INT)((CL_INT)CLREAD(Interval,x,arg1)-(CL_INT)1) <= (CL_INT)CLREAD(Interval,y,arg2)) && 
            ((CL_INT)CLREAD(Interval,y,arg1) <= (CL_INT)CLREAD(Interval,x,arg1)))
         Result = (ClaireType *)_dot_dot_integer(CLREAD(Interval,y,arg1),CLREAD(Interval,x,arg2));
        else { Union * _CL_obj = ((Union *) GC_OBJECT(Union,new_object_class(Core._Union)));
            _void_(_CL_obj->t1 = x);
            _void_(_CL_obj->t2 = y);
            Result = _CL_obj;
            }
          }
      else if ((INHERIT(x->isa,Core._Union)) && (INHERIT(y->isa,Core._Interval)))
       { ClaireType * z = GC_OBJECT(ClaireType,U_type(GC_OBJECT(ClaireType,CLREAD(Union,x,t2)),y));
        if (INHERIT(z->isa,Core._Union))
         { Union * _CL_obj = ((Union *) GC_OBJECT(Union,new_object_class(Core._Union)));
          _void_(_CL_obj->t1 = U_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Core.t1)(_oid_(x)))),y));
          _void_(_CL_obj->t2 = CLREAD(Union,x,t2));
          Result = _CL_obj;
          }
        else Result = U_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Core.t1)(_oid_(x)))),z);
          }
      else if ((INHERIT(x->isa,Core._Interval)) && ((Kernel._set == y->isa) && 
          ((belong_to(((OID)((CL_INT)CLREAD(Interval,x,arg1)-(CL_INT)1)),_oid_(y)) == CTRUE) || 
              (belong_to(((OID)((CL_INT)CLREAD(Interval,x,arg2)+(CL_INT)1)),_oid_(y)) == CTRUE))))
       { CL_INT  a = CLREAD(Interval,x,arg1);
        CL_INT  b = CLREAD(Interval,x,arg2);
        if (belong_to(((OID)((CL_INT)a-(CL_INT)1)),_oid_(y)) == CTRUE)
         a= (CL_INT)(((CL_INT)a-(CL_INT)1));
        if (belong_to(((OID)((CL_INT)b+(CL_INT)1)),_oid_(y)) == CTRUE)
         ++b;
        Result = U_type(GC_OBJECT(ClaireType,_dot_dot_integer(a,b)),y);
        }
      else { if (Kernel._set == y->isa)
           { { set * z_out = set::empty(Kernel.emptySet);
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(z);
                bag *z_support;
                z_support = GC_OBJECT(bag,enumerate_any(_oid_(y)));
                for (START(z_support); NEXT(z);)
                if (belong_to(z,_oid_(x)) != CTRUE)
                 z_out->addFast((OID)z);
                }
              y = GC_OBJECT(set,z_out);
              }
            GC_OBJECT(set,y);}
          { Union * _CL_obj = ((Union *) GC_OBJECT(Union,new_object_class(Core._Union)));
            _void_(_CL_obj->t1 = x);
            _void_(_CL_obj->t2 = y);
            Result = _CL_obj;
            }
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// the Interval construction method has a smart second-order type  - fix on v3.1.06
// The c++ function for: ..(x:integer,y:integer) [NEW_ALLOC]
CL_EXPORT ClaireType * _dot_dot_integer(CL_INT x,CL_INT y) { 
    { ClaireType *Result ;
      if ((CL_INT)x <= (CL_INT)y)
       Result = ((Interval *) (*Core._Interval)(((OID)x),
        ((OID)y)));
      else Result = Kernel.emptySet;
        POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: .._integer_type
CL_EXPORT ClaireType * _dot_dot_integer_type(ClaireType *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if ((unique_ask_type(x) == CTRUE) && 
          ((unique_ask_type(y) == CTRUE) && 
            ((OBJECT(ClaireBoolean,(*Kernel._inf_equal)(GC_OID(the_type(x)),
              GC_OID(the_type(y))))) == CTRUE)))
       Result = set::alloc(1,GC_OID(_oid_(_dot_dot_integer(((CL_INT)the_type(x)),((CL_INT)the_type(y))))));
      else Result = nth_class1(Core._subtype,Kernel._integer);
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// exception
// The c++ function for: but(s:any,x:any) [NEW_ALLOC]
CL_EXPORT bag * but_any(OID s,OID x) { 
    
    GC_BIND;
    { bag *Result ;
      if (INHERIT(OWNER(s),Kernel._list))
       { bag * y_in = OBJECT(bag,s);
        list * y_out = ((list *) empty_bag(y_in));
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(y);
          for (START(y_in); NEXT(y);)
          if (equal(y,x) != CTRUE)
           y_out->addFast((OID)y);
          }
        Result = GC_OBJECT(list,y_out);
        }
      else Result = ((Kernel._set == OWNER(s)) ?
        delete_bag(copy_bag(OBJECT(bag,s)),x) :
        delete_bag(OBJECT(bag,(*Kernel.set_I)(s)),x) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: but_any_type
CL_EXPORT ClaireType * but_any_type(ClaireType *s,ClaireType *x) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = nth_class1(Kernel._bag,GC_OBJECT(ClaireType,member_type(s)));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: \(x:type,y:type) [NEW_ALLOC]
CL_EXPORT set * _backslash_type(ClaireType *x,ClaireType *y) { 
    
    GC_BIND;
    { set *Result ;
      { set * z_out = set::empty(Kernel.emptySet);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(z);
          bag *z_support;
          z_support = GC_OBJECT(bag,enumerate_any(_oid_(x)));
          for (START(z_support); NEXT(z);)
          if (belong_to(z,_oid_(y)) != CTRUE)
           z_out->addFast((OID)z);
          }
        Result = GC_OBJECT(set,z_out);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// ******************************************************************
// *    Part 4: Lattice methods                                     *
// ******************************************************************
// glb operation ---------------------------------------------------
// should use type
// new in v3.0.60: we reintroduce a glb method
// The c++ function for: glb(x:set,y:type) [NEW_ALLOC]
CL_EXPORT set * glb_set(set *x,ClaireType *y) { 
    
    GC_BIND;
    { set *Result ;
      { bag * z_in = x;
        set * z_out = ((set *) empty_bag(z_in));
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(z);
          for (START(z_in); NEXT(z);)
          if (belong_to(z,_oid_(y)) == CTRUE)
           z_out->addFast((OID)z);
          }
        Result = GC_OBJECT(set,z_out);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: glb(x:Union,y:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT ClaireType * glb_Union(Union *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = U_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Core.glb)(GC_OID(_oid_(x->t1)),
        _oid_(y)))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Core.glb)(GC_OID(_oid_(x->t2)),
        _oid_(y)))));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: glb(x:Interval,y:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT ClaireType * glb_Interval(Interval *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (INHERIT(y->isa,Kernel._class))
       { if (_inf_equalt_class(Kernel._integer,y) == CTRUE)
         Result = x;
        else Result = Kernel.emptySet;
          }
      else if (Kernel._set == y->isa)
       Result = glb_set(((set *) y),x);
      else if (INHERIT(y->isa,Core._Interval))
       { if ((CL_INT)x->arg1 <= (CL_INT)CLREAD(Interval,y,arg1))
         { if ((CL_INT)CLREAD(Interval,y,arg1) <= (CL_INT)x->arg2)
           { Result = (((CL_INT)x->arg2 <= (CL_INT)CLREAD(Interval,y,arg2)) ?
              _dot_dot_integer(CLREAD(Interval,y,arg1),x->arg2) :
              y );
            }
          else Result = Kernel.emptySet;
            }
        else Result = glb_Interval(((Interval *) y),x);
          }
      else if (INHERIT(y->isa,Core._Union))
       Result = U_type(GC_OBJECT(ClaireType,glb_Interval(x,GC_OBJECT(ClaireType,CLREAD(Union,y,t1)))),GC_OBJECT(ClaireType,glb_Interval(x,GC_OBJECT(ClaireType,CLREAD(Union,y,t2)))));
      else Result = Kernel.emptySet;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: glb(x:class,y:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT ClaireType * glb_class(ClaireClass *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if ((x->open == ClEnv->ABSTRACT) && 
          (boolean_I_any(_oid_(x->subclass)) != CTRUE))
       { set * z_out = set::empty(Kernel.emptySet);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(z);
          bag *z_support;
          z_support = GC_OBJECT(bag,enumerate_any(_oid_(x)));
          for (START(z_support); NEXT(z);)
          if (belong_to(z,_oid_(y)) == CTRUE)
           z_out->addFast((OID)z);
          }
        Result = GC_OBJECT(set,z_out);
        }
      else if ((x->open == ClEnv->ABSTRACT) && 
          (boolean_I_any(_oid_(x->instances)) != CTRUE))
       { list * g0123UU;
        { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID z; CL_INT CLcount;
            v_list = x->subclass;
             g0123UU = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { z = (*(v_list))[CLcount];
              v_val = (*Core.glb)(z,
                _oid_(y));
              
              (*((list *) g0123UU))[CLcount] = v_val;}
            }
          GC_OBJECT(list,g0123UU);}
        Result = Uall_list(g0123UU);
        }
      else Result = ((INHERIT(y->isa,Kernel._class)) ?
        join_class(x,((ClaireClass *) y)) :
        OBJECT(ClaireType,(*Core.glb)(_oid_(y),
          _oid_(x))) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: glb(x:Param,y:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT ClaireType * glb_Param(Param *x,ClaireType *y) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { ClaireType *Result ;
      if (INHERIT(y->isa,Core._Param))
       { ClaireType * c = join_class(x->arg,CLREAD(Param,y,arg));
        list * lp = GC_OBJECT(list,list_I_set(GC_OBJECT(set,set_I_bag(GC_OBJECT(list,append_list(GC_OBJECT(list,x->params),GC_OBJECT(list,CLREAD(Param,y,params))))))));
        list * l = list::empty(Kernel._any);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(p);
          for (START(lp); NEXT(p);)
          { GC_LOOP;
            { ClaireType * t = GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Core.glb)(GC_OID(_oid_(_at_type(x,OBJECT(property,p)))),
                GC_OID(_oid_(_at_type(y,OBJECT(property,p)))))));
              if (equal(_oid_(t),_oid_(Kernel.emptySet)) != CTRUE)
               GC__ANY(l = l->addFast((OID)_oid_(t)), 1);
              else { c= (Kernel.emptySet);
                  { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                  }
                }
            GC_UNLOOP; POP_SIGNAL;}
          }
        if (equal(_oid_(c),_oid_(Kernel.emptySet)) != CTRUE)
         { Param * _CL_obj = ((Param *) GC_OBJECT(Param,new_object_class(Core._Param)));
          _void_(_CL_obj->arg = ((ClaireClass *) c));
          _void_(_CL_obj->params = lp);
          _void_(_CL_obj->args = l);
          Result = _CL_obj;
          }
        else Result = Kernel.emptySet;
          }
      else if (INHERIT(y->isa,Kernel._class))
       { ClaireType * c = join_class(x->arg,((ClaireClass *) y));
        if (equal(_oid_(c),_oid_(Kernel.emptySet)) != CTRUE)
         { Param * _CL_obj = ((Param *) GC_OBJECT(Param,new_object_class(Core._Param)));
          _void_(_CL_obj->arg = ((ClaireClass *) c));
          _void_(_CL_obj->params = x->params);
          _void_(_CL_obj->args = x->args);
          Result = _CL_obj;
          }
        else Result = Kernel.emptySet;
          }
      else Result = OBJECT(ClaireType,(*Core.glb)(_oid_(y),
          _oid_(x)));
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// notice that a param whose class is a type must use of (only parameter allowed!)
// the result is a subtype
// The c++ function for: glb(x:subtype,y:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT ClaireType * glb_subtype(subtype *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (INHERIT(y->isa,Kernel._class))
       { if (equal(_oid_(join_class(x->arg,((ClaireClass *) y))),_oid_(Kernel.emptySet)) != CTRUE)
         Result = nth_class1(((ClaireClass *) join_class(x->arg,((ClaireClass *) y))),GC_OBJECT(ClaireType,x->t1));
        else Result = Kernel.emptySet;
          }
      else if (INHERIT(y->isa,Core._Param))
       { if (equal(_oid_(join_class(x->arg,CLREAD(Param,y,arg))),_oid_(Kernel.emptySet)) != CTRUE)
         Result = param_I_class(((ClaireClass *) join_class(x->arg,CLREAD(Param,y,arg))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Core.glb)(GC_OID(_oid_(member_type(x))),
          GC_OID(_oid_(member_type(y)))))));
        else Result = Kernel.emptySet;
          }
      else if (INHERIT(y->isa,Core._subtype))
       { if (equal(_oid_(join_class(x->arg,CLREAD(subtype,y,arg))),_oid_(Kernel.emptySet)) != CTRUE)
         { OID  t = GC_OID((*Core.glb)(GC_OID(_oid_(x->t1)),
            GC_OID(_oid_(CLREAD(subtype,y,t1)))));
          if (equal(t,_oid_(Kernel.emptySet)) != CTRUE)
           Result = nth_class1(((ClaireClass *) join_class(x->arg,CLREAD(subtype,y,arg))),OBJECT(ClaireType,t));
          else Result = Kernel.emptySet;
            }
        else Result = Kernel.emptySet;
          }
      else Result = OBJECT(ClaireType,(*Core.glb)(_oid_(y),
          _oid_(x)));
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// set, Interval, list
// The c++ function for: glb(x:tuple,y:type) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT ClaireType * glb_tuple(tuple *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (INHERIT(y->isa,Kernel._class))
       { if (INHERIT(Kernel._tuple,((ClaireClass *) y)))
         Result = x;
        else Result = Kernel.emptySet;
          }
      else if (INHERIT(y->isa,Core._Param))
       Result = Kernel.emptySet;
      else if (INHERIT(y->isa,Kernel._tuple))
       Result = tuple_I_list(GC_OBJECT(list,_exp_list(((list *) x),((list *) y))));
      else if (INHERIT(y->isa,Core._subtype))
       { if (CLREAD(subtype,y,arg) == Kernel._tuple)
         { list * g0124UU;
          { { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID z; CL_INT CLcount;
              v_list = x;
               g0124UU = v_list->clone();
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { z = (*(v_list))[CLcount];
                v_val = (*Core.glb)(z,
                  GC_OID(_oid_(CLREAD(subtype,y,t1))));
                
                (*((list *) g0124UU))[CLcount] = v_val;}
              }
            GC_OBJECT(list,g0124UU);}
          Result = tuple_I_list(g0124UU);
          }
        else Result = Kernel.emptySet;
          }
      else Result = OBJECT(ClaireType,(*Core.glb)(_oid_(y),
          _oid_(x)));
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// a reference is seen as "any"
// The c++ function for: glb(x:Reference,y:type) [RETURN_ARG]
CL_EXPORT ClaireType * glb_Reference(Reference *x,ClaireType *y) { 
    POP_SIGNAL; return (y);}
  


// this will be greatly simplified in a few minutes !
// The c++ function for: ^(x:type,y:type) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT ClaireType * _exp_type(ClaireType *x,ClaireType *y) { 
    POP_SIGNAL; return (OBJECT(ClaireType,(*Core.glb)(_oid_(x),
      _oid_(y))));}
  


// the old lattice_glb
// The c++ function for: join(x:class,y:class) [0]
CL_EXPORT ClaireType * join_class(ClaireClass *x,ClaireClass *y) { 
    { ClaireType *Result ;
      { list * l1 = x->ancestors;
        CL_INT  n1 = l1->length;
        list * l2 = y->ancestors;
        CL_INT  n2 = l2->length;
        if ((CL_INT)n1 < (CL_INT)n2)
         { if ((*(l2))[n1] == _oid_(x))
           Result = y;
          else Result = Kernel.emptySet;
            }
        else if ((*(l1))[n2] == _oid_(y))
         Result = x;
        else Result = Kernel.emptySet;
          }
      POP_SIGNAL; return (Result);}
    }
  


// for lists
// The c++ function for: ^(x:list,y:list) [NEW_ALLOC]
CL_EXPORT list * _exp_list(list *x,list *y) { 
    
    GC_BIND;
    { list *Result ;
      { CL_INT  n = x->length;
        list * r = list::empty();
        if (n == y->length)
         { CL_INT  i = 1;
          CL_INT  g0125 = n;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)i <= (CL_INT)g0125))
            { GC_LOOP;
              { ClaireType * z = GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Core.glb)((*(x))[i],
                  (*(y))[i])));
                if (equal(_oid_(z),_oid_(Kernel.emptySet)) != CTRUE)
                 r= (r->addFast((OID)_oid_(z)));
                else { r= (Kernel.nil);
                    { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                    }
                  }
              ++i;
              GC_UNLOOP;POP_SIGNAL;}
            }
          }
        Result = r;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// a combined union
// The c++ function for: Uall(l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireType * Uall_list(list *l) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { ClaireType *Result ;
      { set * rep = Kernel.emptySet;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(x);
          for (START(l); NEXT(x);)
          { GC_LOOP;
            GC__ANY(rep = ((set *) U_type(rep,OBJECT(ClaireType,x))), 1);
            GC_UNLOOP; POP_SIGNAL;}
          }
        Result = rep;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// ------------------- The inclusion operation ------------------------
// hand-made
// v3.2: extend from set to bags
// The c++ function for: <=t(s:bag,y:type) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * _inf_equalt_bag2(bag *s,ClaireType *y) { 
    { ClaireBoolean *Result ;
      { ClaireType * z = of_bag(s);
        if (equal(_oid_(z),_oid_(Kernel.emptySet)) != CTRUE)
         Result = OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core._inf_equalt->fcall(((CL_INT) z),((CL_INT) y))));
        else { OID  g0126UU;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(x);
              g0126UU= Kernel.cfalse;
              for (START(s); NEXT(x);)
              if (Ztype_any(x,_oid_(y)) != CTRUE)
               { g0126UU = Kernel.ctrue;
                ClEnv->cHandle = loop_handle;break;}
              }
            Result = not_any(g0126UU);
            }
          }
      POP_SIGNAL; return (Result);}
    }
  


// class
// The c++ function for: <=t(x:class,y:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireBoolean * _inf_equalt_class(ClaireClass *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      if (INHERIT(y->isa,Kernel._class))
       Result = contain_ask_list(x->ancestors,_oid_(y));
      else if (INHERIT(y->isa,Kernel._tuple))
       Result = CFALSE;
      else if (INHERIT(y->isa,Core._Union))
       { if ((x->open == 0) && 
            (boolean_I_any(_oid_(x->instances)) != CTRUE))
         { OID  g0127UU;
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(c);
            g0127UU= Kernel.cfalse;
            for (START(x->subclass); NEXT(c);)
            if (_inf_equalt_class(OBJECT(ClaireClass,c),y) != CTRUE)
             { g0127UU = Kernel.ctrue;
              ClEnv->cHandle = loop_handle;break;}
            else ;}
          Result = not_any(g0127UU);
          }
        else Result = ((_inf_equalt_class(x,GC_OBJECT(ClaireType,CLREAD(Union,y,t1))) == CTRUE) ? CTRUE : ((_inf_equalt_class(x,GC_OBJECT(ClaireType,CLREAD(Union,y,t2))) == CTRUE) ? CTRUE : CFALSE));
          }
      else if (Kernel._set == y->isa)
       { if ((x->open == 0) && 
            (boolean_I_any(_oid_(x->subclass)) != CTRUE))
         { OID  g0128UU;
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(u);
            g0128UU= Kernel.cfalse;
            bag *u_support;
            u_support = GC_OBJECT(bag,enumerate_any(_oid_(x)));
            for (START(u_support); NEXT(u);)
            if (contain_ask_set(((set *) y),u) != CTRUE)
             { g0128UU = Kernel.ctrue;
              ClEnv->cHandle = loop_handle;break;}
            }
          Result = not_any(g0128UU);
          }
        else Result = CFALSE;
          }
      else Result = _inf_equalt_type(x,y);
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// Union
// The c++ function for: <=t(x:Union,y:type) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * _inf_equalt_Union(Union *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = (((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core._inf_equalt->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(x->t1)))),((CL_INT) y))))) == CTRUE) ? (((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core._inf_equalt->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(x->t2)))),((CL_INT) y))))) == CTRUE) ? CTRUE: CFALSE): CFALSE);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// Interval
// The c++ function for: <=t(x:Interval,y:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireBoolean * _inf_equalt_Interval(Interval *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = ((INHERIT(y->isa,Core._Interval)) ?
        (((CL_INT)CLREAD(Interval,y,arg1) <= (CL_INT)x->arg1) ? (((CL_INT)x->arg2 <= (CL_INT)CLREAD(Interval,y,arg2)) ? CTRUE: CFALSE): CFALSE) :
        ((Kernel._set == y->isa) ?
          OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core._inf_equalt->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(set_I_Interval(x))))),((CL_INT) y)))) :
          ((INHERIT(y->isa,Core._Union)) ?
            ((_inf_equalt_Interval(x,GC_OBJECT(ClaireType,CLREAD(Union,y,t1))) == CTRUE) ? CTRUE : ((_inf_equalt_Interval(x,GC_OBJECT(ClaireType,CLREAD(Union,y,t2))) == CTRUE) ? CTRUE : CFALSE)) :
            ((INHERIT(y->isa,Kernel._class)) ?
              inherit_ask_class(Kernel._integer,((ClaireClass *) y)) :
              _inf_equalt_type(x,y) ) ) ) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// subtype
// The c++ function for: <=t(x:subtype,y:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireBoolean * _inf_equalt_subtype(subtype *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = ((INHERIT(y->isa,Core._Param)) ?
        _inf_equalt_type(x,y) :
        ((INHERIT(y->isa,Core._subtype)) ?
          _inf_equalt_type(x,y) :
          ((INHERIT(y->isa,Core._Union)) ?
            ((_inf_equalt_subtype(x,GC_OBJECT(ClaireType,CLREAD(Union,y,t1))) == CTRUE) ? CTRUE : ((_inf_equalt_subtype(x,GC_OBJECT(ClaireType,CLREAD(Union,y,t2))) == CTRUE) ? CTRUE : CFALSE)) :
            _inf_equalt_class(x->arg,y) ) ) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// Param is similar !
// The c++ function for: <=t(x:Param,y:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireBoolean * _inf_equalt_Param(Param *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = ((INHERIT(y->isa,Core._Param)) ?
        _inf_equalt_type(x,y) :
        ((INHERIT(y->isa,Core._subtype)) ?
          _inf_equalt_type(x,y) :
          ((INHERIT(y->isa,Core._Union)) ?
            ((_inf_equalt_Param(x,GC_OBJECT(ClaireType,CLREAD(Union,y,t1))) == CTRUE) ? CTRUE : ((_inf_equalt_Param(x,GC_OBJECT(ClaireType,CLREAD(Union,y,t2))) == CTRUE) ? CTRUE : CFALSE)) :
            _inf_equalt_class(x->arg,y) ) ) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// Reference
// The c++ function for: <=t(x:Reference,y:type) [0]
CL_EXPORT ClaireBoolean * _inf_equalt_Reference(Reference *x,ClaireType *y) { 
    POP_SIGNAL; return (CTRUE);}
  


// tuple : the only subtlety is the de-normalization of U within a tuple type
// The c++ function for: <=t(x:tuple,y:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireBoolean * _inf_equalt_tuple(tuple *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      { OID  itest;
        { { OID  j_some = CNULL;
            { CL_INT  j = 1;
              CL_INT  g0130 = x->length;
              { CL_INT loop_handle = ClEnv->cHandle;
                while (((CL_INT)j <= (CL_INT)g0130))
                { if (INHERIT(OWNER((*(x))[j]),Core._Union))
                   { j_some= (((OID)j));
                    ClEnv->cHandle = loop_handle; break;}
                  ++j;
                  POP_SIGNAL;}
                }
              }
            itest = j_some;
            }
          GC_OID(itest);}
        if (itest != CNULL)
         { CL_INT  i = ((CL_INT)itest);
          Union * ui = OBJECT(Union,(*(x))[i]);
          tuple * x1 = ((tuple *) copy_bag(x));
          tuple * x2 = ((tuple *) copy_bag(x));
          ((*(((list *) x1)))[i]=GC_OID(_oid_(ui->t1)));
          ((*(((list *) x2)))[i]=GC_OID(_oid_(ui->t2)));
          Result = ((_inf_equalt_tuple(x1,y) == CTRUE) ? ((_inf_equalt_tuple(x2,y) == CTRUE) ? CTRUE: CFALSE): CFALSE);
          }
        else if (INHERIT(y->isa,Kernel._tuple))
         { ClaireBoolean *v_and;
          { v_and = ((x->length == ((bag *) y)->length) ? CTRUE : CFALSE);
            if (v_and == CFALSE) Result =CFALSE; 
            else { { OID  g0131UU;
                { CL_INT  i = 1;
                  CL_INT  g0129 = x->length;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    g0131UU= _oid_(CFALSE);
                    while (((CL_INT)i <= (CL_INT)g0129))
                    { if ((*Core._inf_equalt)((*(x))[i],
                        (*(((bag *) y)))[i]) != Kernel.ctrue)
                       { g0131UU = Kernel.ctrue;
                        ClEnv->cHandle = loop_handle;break;}
                      ++i;
                      POP_SIGNAL;}
                    }
                  }
                v_and = not_any(g0131UU);
                }
              if (v_and == CFALSE) Result =CFALSE; 
              else Result = CTRUE;}
            }
          }
        else Result = ((INHERIT(y->isa,Core._Union)) ?
          ((_inf_equalt_tuple(x,GC_OBJECT(ClaireType,CLREAD(Union,y,t1))) == CTRUE) ? CTRUE : ((_inf_equalt_tuple(x,GC_OBJECT(ClaireType,CLREAD(Union,y,t2))) == CTRUE) ? CTRUE : CFALSE)) :
          _inf_equalt_class(Kernel._tuple,y) );
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// this is a generic ordering when y is a type Interval, a subtype or a Param
// x <= one such type is actually easy
// The c++ function for: <=t(x:type,y:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireBoolean * _inf_equalt_type(ClaireType *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      if (INHERIT(y->isa,Core._Param))
       { ClaireBoolean *v_and;
        { v_and = OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core._inf_equalt->fcall(((CL_INT) x),((CL_INT) CLREAD(Param,y,arg)))));
          if (v_and == CFALSE) Result =CFALSE; 
          else { { OID  g0133UU;
              { CL_INT  n = 1;
                CL_INT  g0132 = CLREAD(Param,y,params)->length;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  g0133UU= _oid_(CFALSE);
                  while (((CL_INT)n <= (CL_INT)g0132))
                  { GC_LOOP;
                    if ((*Core._inf_equalt)(GC_OID(_oid_(_at_type(x,OBJECT(property,(*(CLREAD(Param,y,params)))[n])))),
                      GC_OID((*(CLREAD(Param,y,args)))[n])) != Kernel.ctrue)
                     { GC_UNLOOP;g0133UU = Kernel.ctrue;
                      ClEnv->cHandle = loop_handle;break;}
                    ++n;
                    GC_UNLOOP;POP_SIGNAL;}
                  }
                }
              v_and = not_any(g0133UU);
              }
            if (v_and == CFALSE) Result =CFALSE; 
            else Result = CTRUE;}
          }
        }
      else Result = ((INHERIT(y->isa,Core._Reference)) ?
        CTRUE :
        ((INHERIT(y->isa,Core._subtype)) ?
          (((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core._inf_equalt->fcall(((CL_INT) x),((CL_INT) CLREAD(subtype,y,arg)))))) == CTRUE) ? (((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core._inf_equalt->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(member_type(x))))),((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(CLREAD(subtype,y,t1))))))))) == CTRUE) ? CTRUE: CFALSE): CFALSE) :
          ((INHERIT(y->isa,Core._Interval)) ?
            CFALSE :
            OBJECT(ClaireBoolean,(*Core.less_ask)(_oid_(x),
              _oid_(y))) ) ) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// for extensibility !
// default order for types
// The c++ function for: <=(x:type,y:type) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * _inf_equal_type(ClaireType *x,ClaireType *y) { 
    POP_SIGNAL; return (OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core._inf_equalt->fcall(((CL_INT) x),((CL_INT) y)))));}
  


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
// The c++ function for: member(x:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT ClaireType * member_type(ClaireType *x) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (INHERIT(x->isa,Kernel._class))
       { Result = ((x == Core._Interval) ?
          Kernel._integer :
          Kernel._any );
        }
      else if (INHERIT(x->isa,Core._Union))
       Result = U_type(GC_OBJECT(ClaireType,member_type(GC_OBJECT(ClaireType,CLREAD(Union,x,t1)))),GC_OBJECT(ClaireType,member_type(GC_OBJECT(ClaireType,CLREAD(Union,x,t2)))));
      else if (INHERIT(x->isa,Core._Interval))
       Result = Kernel.emptySet;
      else if (INHERIT(x->isa,Core._Param))
       Result = member_type(GC_OBJECT(ClaireType,_at_type(x,Kernel.of)));
      else if (INHERIT(x->isa,Kernel._tuple))
       Result = Uall_list(((list *) x));
      else if (INHERIT(x->isa,Core._subtype))
       Result = CLREAD(subtype,x,t1);
      else if (Kernel._set == x->isa)
       { list * g0134UU;
        { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID y; CL_INT CLcount;
            v_list = ((bag *) x);
             g0134UU = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { y = (*(v_list))[CLcount];
              if (INHERIT(OWNER(y),Kernel._list))
               v_val = _oid_(set_I_bag(OBJECT(list,y)));
              else if (INHERIT(OWNER(y),Kernel._type))
               v_val = y;
              else v_val = _oid_(Kernel.emptySet);
                
              (*((list *) g0134UU))[CLcount] = v_val;}
            }
          GC_OBJECT(list,g0134UU);}
        Result = Uall_list(g0134UU);
        }
      else Result = Kernel.emptySet;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// a simpler version (projection on bag subtypes)
// dumb code because it is used early in the bootstrap
// The c++ function for: of_extract(x:type) [RETURN_ARG]
CL_EXPORT ClaireType * of_extract_type(ClaireType *x) { 
    { ClaireType *Result ;
      { ClaireClass * c = x->isa;
        if (c == Core._subtype)
         Result = CLREAD(subtype,x,t1);
        else if (c == Core._Param)
         { if ((*(CLREAD(Param,x,params)))[1] == _oid_(Kernel.of))
           { ClaireType * y = OBJECT(ClaireType,(*(CLREAD(Param,x,args)))[1]);
            if (Kernel._set == y->isa)
             Result = OBJECT(ClaireType,(*(((bag *) y)))[1]);
            else if (INHERIT(y->isa,Core._subtype))
             Result = CLREAD(subtype,y,t1);
            else Result = Kernel._any;
              }
          else Result = Kernel._any;
            }
        else Result = Kernel._any;
          }
      POP_SIGNAL; return (Result);}
    }
  


// --------------------- extract range information ------------------
// the method @ is used to extract the range information contained
// in a type. This method returns a type and is crucial for compiling !
// The c++ function for: @(x:type,p:property) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT ClaireType * _at_type(ClaireType *x,property *p) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (INHERIT(x->isa,Kernel._class))
       { ClaireObject * r = GC_OBJECT(ClaireObject,_at_property1(p,((ClaireClass *) x)));
        if (r != CFALSE)
         Result = CLREAD(restriction,r,range);
        else Result = Kernel._any;
          }
      else if (INHERIT(x->isa,Core._Param))
       { CL_INT  i = index_list(CLREAD(Param,x,params),_oid_(p));
        Result = (((CL_INT)i > (CL_INT)0) ?
          OBJECT(ClaireType,(*(CLREAD(Param,x,args)))[i]) :
          _at_type(CLREAD(Param,x,arg),p) );
        }
      else if (INHERIT(x->isa,Core._Union))
       Result = U_type(GC_OBJECT(ClaireType,_at_type(GC_OBJECT(ClaireType,CLREAD(Union,x,t1)),p)),GC_OBJECT(ClaireType,_at_type(GC_OBJECT(ClaireType,CLREAD(Union,x,t2)),p)));
      else if (Kernel._set == x->isa)
       { list * g0135UU;
        { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID y; CL_INT CLcount;
            v_list = ((bag *) x);
             g0135UU = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { y = (*(v_list))[CLcount];
              v_val = _oid_(set::alloc(1,GC_OID(funcall_property(p,y))));
              
              (*((list *) g0135UU))[CLcount] = v_val;}
            }
          GC_OBJECT(list,g0135UU);}
        Result = Uall_list(g0135UU);
        }
      else Result = _at_type(class_I_type(x),p);
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// useful type functions for the compiler
// The c++ function for: unique?(x:type) [0]
CL_EXPORT ClaireBoolean * unique_ask_type(ClaireType *x) { 
    { ClaireBoolean *Result ;
      Result = ((Kernel._set == x->isa) ?
        equal(((OID)size_set(((set *) x))),((OID)1)) :
        ((INHERIT(x->isa,Kernel._class)) ?
          ((CLREAD(ClaireClass,x,open) == 0) ? ((size_class(((ClaireClass *) x)) == 1) ? CTRUE: CFALSE): CFALSE) :
          CFALSE ) );
      POP_SIGNAL; return (Result);}
    }
  


// returns the unique element of the type
// The c++ function for: the(x:type) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  the_type(ClaireType *x) { 
    POP_SIGNAL; return ((*(OBJECT(bag,(*Kernel.set_I)(_oid_(x)))))[1]);}
  


// bitvector made easy
// v0.01: should not use set[0 .. 29] => burden on caller is too heavy
// @doc number
// integer!(l) returns the integer represented by the bitvector l,
// i.e. the sum of all 2i for i in l.
// The c++ function for: integer!(s:set[integer]) [NEW_ALLOC]
CL_EXPORT CL_INT  integer_I_set(set *s) { 
    { CL_INT Result = 0;
      { CL_INT  n = 0;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(y);
          for (START(s); NEXT(y);)
          if (((CL_INT)y <= (CL_INT)29) && 
              ((CL_INT)0 <= (CL_INT)y))
           n= (CL_INT)(((CL_INT)n+(CL_INT)exp2_integer(y)));
          }
        Result = n;
        }
      POP_SIGNAL; return (Result);}
    }
  


// @doc number
// make_set(x) returns the set of bit index that are set in the integer x
// seen as a bitvector.
// The c++ function for: make_set(x:integer) [NEW_ALLOC]
CL_EXPORT set * make_set_integer(CL_INT x) { 
    
    GC_BIND;
    { set *Result ;
      { set * i_out = set::empty(Kernel.emptySet);
        { CL_INT  i = 0;
          CL_INT  g0136 = 29;
          { CL_INT loop_handle = ClEnv->cHandle;
            while (((CL_INT)i <= (CL_INT)g0136))
            { if (BCONTAIN(x,i))
               i_out->addFast((OID)((OID)i));
              ++i;
              POP_SIGNAL;}
            }
          }
        Result = GC_OBJECT(set,i_out);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// asbtract coercion of a set into an interval
// The c++ function for: abstract_type(xt1:set) [NEW_ALLOC]
CL_EXPORT ClaireType * abstract_type_set(set *xt1) { 
    { ClaireType *Result ;
      { CL_INT  m1 = 1;
        CL_INT  m2 = 0;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(x);
          for (START(xt1); NEXT(x);)
          if (INHERIT(OWNER(x),Kernel._integer))
           { if ((CL_INT)m1 > (CL_INT)m2)
             { m1= (CL_INT)(x);
              m2= (CL_INT)(x);
              }
            else if ((CL_INT)x > (CL_INT)m2)
             m2= (CL_INT)(x);
            else if ((CL_INT)x < (CL_INT)m1)
             m1= (CL_INT)(x);
            }
          else { m1= (CL_INT)(1);
              m2= (CL_INT)(0);
              { ;ClEnv->cHandle = loop_handle; break;}
              }
            }
        Result = (ClaireType *)_dot_dot_integer(m1,m2);
        }
      POP_SIGNAL; return (Result);}
    }
  


// abstract interpretation of integer arithmetique
// The c++ function for: abstract_type(p:operation,xt1:type,xt2:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT ClaireType * abstract_type_operation(operation *p,ClaireType *xt1,ClaireType *xt2) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (Kernel._set == xt1->isa)
       { Result = ((equal(_oid_(xt1),_oid_(Kernel.emptySet)) != CTRUE) ?
          abstract_type_operation(p,GC_OBJECT(ClaireType,abstract_type_set(((set *) xt1))),xt2) :
          xt1 );
        }
      else if (INHERIT(xt1->isa,Core._Interval))
       { if (INHERIT(xt2->isa,Core._Interval))
         { if (p == Core._plus)
           Result = (ClaireType *)_dot_dot_integer(((CL_INT)CLREAD(Interval,xt1,arg1)+(CL_INT)CLREAD(Interval,xt2,arg1)),((CL_INT)CLREAD(Interval,xt1,arg2)+(CL_INT)CLREAD(Interval,xt2,arg2)));
          else if (p == Kernel._dash)
           Result = (ClaireType *)_dot_dot_integer(((CL_INT)CLREAD(Interval,xt1,arg1)-(CL_INT)CLREAD(Interval,xt2,arg2)),((CL_INT)CLREAD(Interval,xt1,arg2)-(CL_INT)CLREAD(Interval,xt2,arg1)));
          else Result = Kernel._integer;
            }
        else if (Kernel._set == xt2->isa)
         { Result = ((equal(_oid_(xt2),_oid_(Kernel.emptySet)) != CTRUE) ?
            abstract_type_operation(p,xt1,GC_OBJECT(ClaireType,abstract_type_set(((set *) xt2)))) :
            xt2 );
          }
        else if (INHERIT(xt2->isa,Core._Union))
         Result = U_type(GC_OBJECT(ClaireType,abstract_type_operation(p,xt1,GC_OBJECT(ClaireType,CLREAD(Union,xt2,t1)))),GC_OBJECT(ClaireType,abstract_type_operation(p,xt1,GC_OBJECT(ClaireType,CLREAD(Union,xt2,t2)))));
        else Result = Kernel._integer;
          }
      else if (INHERIT(xt1->isa,Core._Union))
       Result = U_type(GC_OBJECT(ClaireType,abstract_type_operation(p,GC_OBJECT(ClaireType,CLREAD(Union,xt1,t1)),xt2)),GC_OBJECT(ClaireType,abstract_type_operation(p,GC_OBJECT(ClaireType,CLREAD(Union,xt1,t2)),xt2)));
      else Result = Kernel._integer;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// we create some types that we need
// a useful second ortder type
// The c++ function for: first_arg_type(x:type,y:type) [RETURN_ARG]
CL_EXPORT ClaireType * first_arg_type_type(ClaireType *x,ClaireType *y) { 
    POP_SIGNAL; return (x);}
  


// The c++ function for: first_arg_type(x:type,y:type,z:type) [RETURN_ARG]
CL_EXPORT ClaireType * first_arg_type_type2(ClaireType *x,ClaireType *y,ClaireType *z) { 
    POP_SIGNAL; return (x);}
  


// The c++ function for: second_arg_type(x:type,y:type) [RETURN_ARG]
CL_EXPORT ClaireType * second_arg_type_type(ClaireType *x,ClaireType *y) { 
    POP_SIGNAL; return (y);}
  


// The c++ function for: meet_arg_types(x:type,y:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT ClaireType * meet_arg_types_type(ClaireType *x,ClaireType *y) { 
    POP_SIGNAL; return (U_type(x,y));}
  


// The c++ function for: first_member_type(x:type,y:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT ClaireType * first_member_type_type(ClaireType *x,ClaireType *y) { 
    POP_SIGNAL; return (member_type(x));}
  


// v3.3.10
//<sb> v3.3.33 rewrite second order type for /+ and cast!
// The c++ function for: append_type(x:type,y:type) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT ClaireType * append_type_type1(ClaireType *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = ((belong_to(_oid_(x),_oid_(nth_class1(Kernel._type,Kernel._set))) == CTRUE) ?
        nth_class1(Kernel._set,GC_OBJECT(ClaireType,U_type(GC_OBJECT(ClaireType,member_type(x)),GC_OBJECT(ClaireType,member_type(y))))) :
        ((belong_to(_oid_(x),_oid_(nth_class1(Kernel._type,Kernel._bag))) == CTRUE) ?
          nth_class1(Kernel._list,GC_OBJECT(ClaireType,U_type(GC_OBJECT(ClaireType,member_type(x)),GC_OBJECT(ClaireType,member_type(y))))) :
          meet_arg_types_type(x,y) ) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: cast!_type(x:type,y:type) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT ClaireType * cast_I_type_type1(ClaireType *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (belong_to(_oid_(x),_oid_(nth_class1(Kernel._type,Kernel._set))) == CTRUE)
       { if (unique_ask_type(y) == CTRUE)
         Result = nth_class1(Kernel._set,GC_OBJECT(ClaireType,OBJECT(ClaireType,the_type(y))));
        else Result = Kernel._set;
          }
      else if (belong_to(_oid_(x),_oid_(nth_class1(Kernel._type,Kernel._list))) == CTRUE)
       { if (unique_ask_type(y) == CTRUE)
         Result = nth_class1(Kernel._list,GC_OBJECT(ClaireType,OBJECT(ClaireType,the_type(y))));
        else Result = Kernel._list;
          }
      else Result = Kernel._tuple;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: prealloc_set_type(x:type,y:type) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT ClaireType * prealloc_set_type_type1(ClaireType *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (unique_ask_type(x) == CTRUE)
       Result = nth_class1(Kernel._set,GC_OBJECT(ClaireType,OBJECT(ClaireType,the_type(x))));
      else Result = Kernel._set;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: prealloc_list_type(x:type,y:type) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT ClaireType * prealloc_list_type_type1(ClaireType *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (unique_ask_type(x) == CTRUE)
       Result = nth_class1(Kernel._list,GC_OBJECT(ClaireType,OBJECT(ClaireType,the_type(x))));
      else Result = Kernel._list;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// we place here all methods that require second order types !!!!
//nth_get(a:array,n:integer) : type[member(a)] -> function!(nth_get_array)
// The c++ function for: nth(self:array,x:integer) [RETURN_ARG]
CL_EXPORT OID  nth_array(OID *self,CL_INT x) { 
    { OID Result = 0;
      if (((CL_INT)x > (CL_INT)0) && 
          ((CL_INT)x <= (CL_INT)self[0]))
       Result = nth_get_array(self,x);
      else { OID  V_CL0137;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[180] nth[~S] out of scope for ~S")),
            _oid_(list::alloc(2,((OID)x),_array_(self))))));
          
          Result=_void_(V_CL0137);}
        POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: nth_array_type
CL_EXPORT ClaireType * nth_array_type(ClaireType *self,ClaireType *x) { 
    POP_SIGNAL; return (member_type(self));}
  


// @doc array
// returns an array of length n filled with x. The parameter t is the member_type of
// the array, thus x must belong to t, as well as any future value that will be put
// in the array.
// The c++ function for: make_array_integer_type
CL_EXPORT ClaireType * make_array_integer_type(ClaireType *i,ClaireType *t,ClaireType *v) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (unique_ask_type(t) == CTRUE)
       Result = nth_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,the_type(t))));
      else Result = Kernel._array;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: make_list(n:integer,t:type,x:any) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT list * make_list_integer2(CL_INT n,ClaireType *t,OID x) { 
    POP_SIGNAL; return (cast_I_list1(make_list_integer(n,x),t));}
  


// The c++ function for: make_list_integer2_type
CL_EXPORT ClaireType * make_list_integer2_type(ClaireType *n,ClaireType *t,ClaireType *x) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (unique_ask_type(t) == CTRUE)
       Result = nth_class1(Kernel._list,GC_OBJECT(ClaireType,OBJECT(ClaireType,the_type(t))));
      else Result = Kernel._list;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: make_list_type(x:type,y:type) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT ClaireType * make_list_type_type1(ClaireType *x,ClaireType *y) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (unique_ask_type(x) == CTRUE)
       Result = nth_class1(Kernel._list,GC_OBJECT(ClaireType,OBJECT(ClaireType,the_type(x))));
      else Result = Kernel._list;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: make_set(self:array[of:(any)]) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT set * make_set_array(OID *self) { 
    
    GC_BIND;
    { set *Result ;
      Result = set_I_bag(GC_OBJECT(list,list_I_array(self)));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: make_set_array_type
CL_EXPORT ClaireType * make_set_array_type(ClaireType *self) { 
    if (member_type(GC_OBJECT(ClaireType,_at_type(self,Kernel.of))) == Kernel._any) 
    { { ClaireType *Result ;
        Result = Kernel._set;
        return (Result);}
       }
    else{ 
      GC_BIND;
      { ClaireType *Result ;
        Result = nth_class2(Kernel._set,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,GC_OID(_oid_(member_type(GC_OBJECT(ClaireType,_at_type(self,Kernel.of)))))))));
        GC_UNBIND; POP_SIGNAL; return (Result);}
      }
    }
  


// The c++ function for: list_I_array_type
CL_EXPORT ClaireType * list_I_array_type(ClaireType *a) { 
    if (member_type(GC_OBJECT(ClaireType,_at_type(a,Kernel.of))) == Kernel._any) 
    { { ClaireType *Result ;
        Result = Kernel._list;
        return (Result);}
       }
    else{ 
      GC_BIND;
      { ClaireType *Result ;
        Result = nth_class2(Kernel._list,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,GC_OID(_oid_(member_type(GC_OBJECT(ClaireType,_at_type(a,Kernel.of)))))))));
        GC_UNBIND; POP_SIGNAL; return (Result);}
      }
    }
  


// The c++ function for: array_I_list_type
CL_EXPORT ClaireType * array_I_list_type(ClaireType *a) { 
    if (member_type(GC_OBJECT(ClaireType,_at_type(a,Kernel.of))) == Kernel._any) 
    { { ClaireType *Result ;
        Result = Kernel._array;
        return (Result);}
       }
    else{ 
      GC_BIND;
      { ClaireType *Result ;
        Result = nth_class2(Kernel._array,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,GC_OID(_oid_(member_type(GC_OBJECT(ClaireType,_at_type(a,Kernel.of)))))))));
        GC_UNBIND; POP_SIGNAL; return (Result);}
      }
    }
  


// v3.0.72
// The c++ function for: set_I_bag_type
CL_EXPORT ClaireType * set_I_bag_type(ClaireType *l) { 
    if (member_type(GC_OBJECT(ClaireType,_at_type(l,Kernel.of))) == Kernel._any) 
    { { ClaireType *Result ;
        Result = Kernel._set;
        return (Result);}
       }
    else{ 
      GC_BIND;
      { ClaireType *Result ;
        Result = nth_class2(Kernel._set,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,GC_OID(_oid_(member_type(GC_OBJECT(ClaireType,_at_type(l,Kernel.of)))))))));
        GC_UNBIND; POP_SIGNAL; return (Result);}
      }
    }
  


// The c++ function for: list_I_set_type
CL_EXPORT ClaireType * list_I_set_type(ClaireType *l) { 
    if (member_type(GC_OBJECT(ClaireType,_at_type(l,Kernel.of))) == Kernel._any) 
    { { ClaireType *Result ;
        Result = Kernel._list;
        return (Result);}
       }
    else{ 
      GC_BIND;
      { ClaireType *Result ;
        Result = nth_class2(Kernel._list,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,GC_OID(_oid_(member_type(GC_OBJECT(ClaireType,_at_type(l,Kernel.of)))))))));
        GC_UNBIND; POP_SIGNAL; return (Result);}
      }
    }
  


// new in v3.0.60 : second-order type for copy
//<sb> exclude copy@(string,integer)
// The c++ function for: refine_append_of(self:bag,x:bag,y:bag) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  refine_append_of_bag1(bag *self,bag *x,bag *y) { 
    
    GC_BIND;
    { ClaireType * _Zx = of_bag(x);
      ClaireType * _Zy = of_bag(y);
      if (equal(_oid_(_Zx),_oid_(_Zy)) == CTRUE)
       (*Kernel.cast_I)(_oid_(self),
        _oid_(_Zx));
      else (*Kernel.cast_I)(_oid_(self),
          GC_OID(_oid_(U_type(of_bag(x),of_bag(y)))));
        }
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> refine freadline range
// The c++ function for: set_user(username:string) [0]
CL_EXPORT void  set_user_string1(char *username) { 
    
		#ifndef CLPC
		#ifdef HAVE_PWD_H
	;
    struct passwd *pw = getpwnam(username);
    if ((((ClaireBoolean *) (ClaireBoolean *)((pw == NULL ? CTRUE : CFALSE)))) == CTRUE)
     Cerrorno(74,_string_("getpwnam"),0);
    if ((((ClaireBoolean *) (ClaireBoolean *)((setgid(pw->pw_gid) ? CTRUE : CFALSE)))) == CTRUE)
     Cerrorno(74,_string_("setgid"),0);
    if ((((ClaireBoolean *) (ClaireBoolean *)((setuid(pw->pw_uid) ? CTRUE : CFALSE)))) == CTRUE)
     Cerrorno(74,_string_("setuid"),0);
    
		#endif
		#endif
	;
    POP_SIGNAL;}
  


// The c++ function for: sizeof(g0138:any) [NEW_ALLOC]
CL_EXPORT tuple * sizeof_any1_(OID g0138) { 
    return sizeof_any1(g0138)->copyIfNeeded();
}


// The c++ function for: sizeof(x:any) [NEW_ALLOC]
CL_EXPORT tuple * sizeof_any1(OID x) { 
      { tuple *Result ;
      { OID v_bag;
        Result= tuple::empty();
        if (Kernel._string == OWNER(x))
         v_bag = ((OID)LENGTH_STRING(string_v(x)));
        else if (Kernel._array == OWNER(x))
         v_bag = ((OID)array_v(x)[0]);
        else if (INHERIT(OWNER(x),Kernel._bag))
         v_bag = ((OID)OBJECT(bag,x)->length);
        else if (_Z_any1(x,Kernel._object) == CTRUE)
         { OID  s = last_list(OWNER(x)->slots);
          v_bag = ((OID)((CL_INT)OBJECT(slot,s)->index+(CL_INT)((OBJECT(slot,s)->srange == Kernel._float) ?
            1 :
            0 )));
          }
        else v_bag = ((OID)1);
          ((tuple *) Result)->addFast((OID)v_bag);
        if (Kernel._string == OWNER(x))
         v_bag = ((OID)LENGTH_STRING(string_v(x)));
        else if (Kernel._array == OWNER(x))
         v_bag = ((OID)(CL_INT )(*(((CL_INT*)OBJECT(ClaireAny, x)) - 1)));
        else if (INHERIT(OWNER(x),Kernel._bag))
         v_bag = ((OID)(CL_INT )(*(OBJECT(bag,x)->content)));
        else if (_Z_any1(x,Kernel._object) == CTRUE)
         v_bag = ((OID)(CL_INT )(*(((CL_INT*)array_v(x)) - 3)));
        else v_bag = ((OID)1);
          ((tuple *) Result)->addFast((OID)v_bag);}
      return (Result);}
    }
  


// The c++ function for: sizeof(g0139:class) [NEW_ALLOC]
CL_EXPORT tuple * sizeof_class1_(ClaireClass *g0139) { 
    return sizeof_class1(g0139)->copyIfNeeded();
}


// The c++ function for: sizeof(c:class) [NEW_ALLOC]
CL_EXPORT tuple * sizeof_class1(ClaireClass *c) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = ((_inf_equal_type(c,Kernel._object) == CTRUE) ?
        OBJECT(tuple,(*Core.cl_sizeof)(GC_OID(_oid_(new_object_class(c))))) :
        tuple::alloc(2,((OID)0),((OID)0)) );
      GC_UNBIND; return (Result);}
    }
  


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
//<sb> the top and the innermost frames, the innermost frame
// is updated while the program runs
// The c++ function for: reset_frame_stack(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  reset_frame_stack_void1() { 
    
    GC_BIND;
    (Core.current_frame->value= Core.top_frame->value);
    { Core_dbg_frame * p = GC_OBJECT(Core_dbg_frame,OBJECT(Core_dbg_frame,Core.current_frame->value)->next);
      if (p == (NULL))
       ;else { erase_property(Core.prev,GC_OBJECT(Core_dbg_frame,OBJECT(Core_dbg_frame,Core.current_frame->value)->next));
          erase_property(Core.next,GC_OBJECT(Core_dbg_frame,OBJECT(ClaireObject,Core.current_frame->value)));
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  


// 0: continue
// -1: step all
// >0: index of frame to step
//<sb> builds a new debug frame
// The c++ function for: push_frame(self:any) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT void  push_frame_any1(OID self) { 
    
    GC_BIND;
    { Core_dbg_frame * nf;
      { { Core_dbg_frame * _CL_obj = ((Core_dbg_frame *) GC_OBJECT(Core_dbg_frame,new_object_class(Core._dbg_frame)));
          _void_(_CL_obj->frame_source = self);
          _void_(_CL_obj->num = ((CL_INT)OBJECT(Core_dbg_frame,Core.current_frame->value)->num+(CL_INT)1));
          _void_(_CL_obj->source = string_v(CLREAD(slot,_at_property1(Kernel.source,Core._dbg_frame),DEFAULT)));
          nf = _CL_obj;
          }
        GC_OBJECT(Core_dbg_frame,nf);}
      _void_(OBJECT(Core_dbg_frame,Core.current_frame->value)->next = nf);
      _void_(nf->prev = OBJECT(Core_dbg_frame,Core.current_frame->value));
      (Core.current_frame->value= _oid_(nf));
      }
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> drop the last debug frame
// The c++ function for: pop_frame(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  pop_frame_void1() { 
    
    GC_BIND;
    (Core.current_frame->value= _oid_(OBJECT(Core_dbg_frame,Core.current_frame->value)->prev));
    erase_property(Core.prev,GC_OBJECT(Core_dbg_frame,OBJECT(Core_dbg_frame,Core.current_frame->value)->next));
    erase_property(Core.next,GC_OBJECT(Core_dbg_frame,OBJECT(ClaireObject,Core.current_frame->value)));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: push_arg(nam:string,val:any) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  push_arg_string1(char *nam,OID val) { 
    
    GC_BIND;
    { Core_dbg_frame * fr = GC_OBJECT(Core_dbg_frame,OBJECT(Core_dbg_frame,Core.current_frame->value));
      GC_OBJECT(list,fr->vars)->addFast((OID)_string_(nam));
      GC_OBJECT(list,fr->vars)->addFast((OID)val);
      _void_(fr->dimension = ((CL_INT)fr->dimension+(CL_INT)1));
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: push_var(nam:string,val:any) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT void  push_var_string1(char *nam,OID val) { 
    
    GC_BIND;
    { Core_dbg_frame * fr = GC_OBJECT(Core_dbg_frame,OBJECT(Core_dbg_frame,Core.current_frame->value));
      fr->vars->addFast((OID)_string_(nam));
      fr->vars->addFast((OID)val);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: pop_var(_CL_obj:void) [0]
CL_EXPORT void  pop_var_void1() { 
    { list * vs = OBJECT(Core_dbg_frame,Core.current_frame->value)->vars;
      shrink_list(vs,((CL_INT)vs->length-(CL_INT)2));
      }
    POP_SIGNAL;}
  


// The c++ function for: update_var(nam:string,val:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  update_var_string1(char *nam,OID val) { 
    
    GC_BIND;
    { Core_dbg_frame * fr = GC_OBJECT(Core_dbg_frame,OBJECT(Core_dbg_frame,Core.current_frame->value));
      list * vs = GC_OBJECT(list,fr->vars);
      CL_INT  i = ((CL_INT)vs->length-(CL_INT)1);
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((CL_INT)i > (CL_INT)0))
        { if (equal((*(vs))[i],_string_(nam)) == CTRUE)
           { ((*(vs))[((CL_INT)i+(CL_INT)1)]=val);
            { ;ClEnv->cHandle = loop_handle; break;}
            }
          i= (CL_INT)(((CL_INT)i-(CL_INT)2));
          POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> update in the current frame with the current execution location, i.e.
// a transition occurs between two states : this is where the stepper and
// breakpoints are checked
// The c++ function for: update_location(f:string,l:integer,c:integer,n:integer) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  update_location_string1(char *f,CL_INT l,CL_INT c,CL_INT n) { 
    
    GC_BIND;
    { Core_dbg_frame * fr = GC_OBJECT(Core_dbg_frame,OBJECT(Core_dbg_frame,Core.current_frame->value));
      ClaireBoolean * same_ask = ((n == fr->length) ? ((c == fr->column) ? ((l == fr->line) ? ((equal_string(fr->source,f) == CTRUE) ? CTRUE: CFALSE): CFALSE): CFALSE): CFALSE);
      _void_(fr->source = f);
      _void_(fr->line = l);
      _void_(fr->column = c);
      _void_(fr->length = n);
      if ((fr->new_ask == CTRUE) && 
          ((INHERIT(OWNER(fr->frame_source),Kernel._tuple)) && 
            (contain_ask_set(OBJECT(set,Core.BREAKPOINTS->value),(*Kernel.nth)(GC_OID(fr->frame_source),
              ((OID)2))) == CTRUE)))
       { _void_(fr->new_ask = CFALSE);
        (*Core.on_break_program)(_oid_(ClEnv));
        }
      else if ((same_ask != CTRUE) && 
          (Core.STEP->value != ((OID)0)))
       break_if_needed_dbg_frame1(fr,((CL_INT)Core.STEP->value));
      _void_(fr->new_ask = CFALSE);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: break_if_needed(fr:dbg_frame,st:integer) [NEW_ALLOC]
CL_EXPORT void  break_if_needed_dbg_frame1(Core_dbg_frame *fr,CL_INT st) { 
    if ((st == ((CL_INT)-1)) || 
        (st == fr->num))
     (*Core.on_break_program)(_oid_(ClEnv));
    POP_SIGNAL;}
  


// The c++ function for: push_handle(oid:string) [BAG_UPDATE+RETURN_ARG]
CL_EXPORT void  push_handle_string1(char *oid) { 
    put_table(Core.HANDLE_FRAMES,_string_(oid),Core.current_frame->value);
    POP_SIGNAL;}
  


// The c++ function for: pop_handle(oid:string) [BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  pop_handle_string1(char *oid) { 
    { OID  fr = nth_table1(Core.HANDLE_FRAMES,_string_(oid));
      put_table(Core.HANDLE_FRAMES,_string_(oid),Core.top_frame->value);
      (Core.current_frame->value= fr);
      { Core_dbg_frame * nfr = OBJECT(Core_dbg_frame,fr)->next;
        if (nfr == (NULL))
         ;else _void_(nfr->prev = NULL);
          }
      _void_(OBJECT(Core_dbg_frame,fr)->next = NULL);
      }
    POP_SIGNAL;}
  


// The c++ function for: push_handle_frame(f:string,l:integer,c:integer,n:integer,oid:string) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT void  push_handle_frame_string1(char *f,CL_INT l,CL_INT c,CL_INT n,char *oid) { 
    
    GC_BIND;
    { Core_dbg_frame * nf = GC_OBJECT(Core_dbg_frame,((Core_dbg_frame *) copy_object(OBJECT(ClaireObject,nth_table1(Core.HANDLE_FRAMES,_string_(oid))))));
      _void_(nf->num = ((CL_INT)OBJECT(Core_dbg_frame,Core.current_frame->value)->num+(CL_INT)1));
      _void_(OBJECT(Core_dbg_frame,Core.current_frame->value)->next = nf);
      _void_(nf->prev = OBJECT(Core_dbg_frame,Core.current_frame->value));
      (Core.current_frame->value= _oid_(nf));
      _void_(nf->catch_ask = CTRUE);
      _void_(nf->source = f);
      _void_(nf->line = l);
      _void_(nf->column = c);
      _void_(nf->length = n);
      if (Core.STEP->value != ((OID)0))
       break_if_needed_dbg_frame1(nf,((CL_INT)Core.STEP->value));
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: dload(m:string,path:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  dload_string1(char *m,char *path) { 
    
    GC_BIND;
    if (inherit_ask_class(owner_any(value_string(m)),Kernel._module) != CTRUE)
     { char * sym;
      { { print_in_string_void();
          princ_string(((char*)"dynLoad"));
          c_princ_string(m);
          sym = end_of_string_void();
          }
        GC_STRING(sym);}
      module * curmod = ClEnv->module_I;
      
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
        ;
      _void_(ClEnv->module_I = curmod);
      }
    GC_UNBIND; POP_SIGNAL;}
  



/***** CLAIRE Compilation of file ./meta/signal.cl 
         [version 3.5.0 / safety 5] *****/


//*********************************************************************
//* CLAIRE                                            Sylvain Benilan *
//* signal.cl                                                         *
//* Copyright (C) 2000 - 2005 xl. All Rights Reserved                 *
//*********************************************************************
// This file contains signal handling methods and some tools to
// manipulate the process signal mask.
// *********************************************************************
// *  Table of contents                                                *
// *   Part 1: signal handler definition                               *
// *   Part 2: signal API                                              *
// *   Part 3: signal mask                                             *
// *   Part 4: itimer                                                  *
// *   Part 5: waitpid                                                 *
// *********************************************************************
//<sb> @cat @xl Signal Handling
// @section Platform
// Starting with XL CLAIRE we can install an Interrupt Service Routine written in CLAIRE
// for a particular signal.
// Signals, in XL CLAIRE, are not true asynchronous event since they are
// always caught by the Kernel as a first step and redistributed to the meta
// code from an appropriate execution point (necessary to preserve 
// memory integrity) : the meta handling is always performed in the program execution
// flow (i.e. not in the stack of the signal handler) so that the code of the handler
// may be arbitrary complex.\br
// The signal interface is very similar to C interface, we use
// signal(sig:signal_handler, p:property) to install a signal handler :
// \code
// user_interrupt() : void -> error("User interrupt")
//
// (signal(SIGUSR1, user_interrupt))
// (raise(SIGUSR1)) // would throw the error above
// \/code
// Notice that in XL CLAIRE after the delivery of a signal the signal is always
// re-installed. To uninstall a handler one should use the special property SIG_DFL
// which correspond to a default handling :
// \code
// (signal(SIGUSR1, SIG_DFL))
// \/code
// We could also ignore a signal using the special property SIG_IGN :
// \code
// (signal(SIGUSR1, SIG_IGN))
// \/code
// Last, XL CLAIRE comes with another special property SIG_EXT that is set by default to
// a signal already installed at the time of CLAIRE initialization (as may be done by a
// library linked with CLAIRE).\br
// However, SIGINT is handled in a particular way (SIGINT is on most UNIX
// raised with the keyboard when the user types ^C - Control + C).
// The SIGINT handler, when set to SIG_DFL (default), throws a user interrupt error such to
// abort the current computation and come back to the interpreter. If, additionally, the
// debugger is active, SIGINT would behave as a breakpoint.
// @cat
// *********************************************************************
// *   Part 1: signal handler definition                               *
// *********************************************************************
//<sb> @doc @xl Signal Handling
// In claire signals are named objects. signal handling is system dependent and a
// signal_handler instance may not correspond to a supported signal in which case
// its value signo will be set to -1.
// something different from SIG_DFL or SIG_IGN (i.e. external)
//<sb> setup signal handlers
// *********************************************************************
// *   Part 2: signal API                                              *
// *********************************************************************
//<sb> @doc @xl Signal Handling
// Install a signal handler for the given signal_handler. A restriction p
// should exists with the domain void.
// signal returns the old property associated with the signal handler.
// One may use special values for the handler p:
// \ul
// \li SIG_IGN : ignore the signal
// \li SIG_EXT : this value is used by signal initializer if a signal is found
// to be already installed (e.g. by an external library).
// \li SIG_DFL : restore the default handler (system dependent). SIGINT is handled
// \/ul
// in a special way when assigned to SIG_DFL: the USER INTERRUPT.
// In CLAIRE signals are synchronously distributed to the meta code such to
// keep CLAIRE memory in a good shape. That is, there is a delay between the
// kernel routine that catches the signal and the execution of the meta handler.
// The c++ function for: signal(sig:signal_handler,p:property) [SLOT_UPDATE]
CL_EXPORT property * signal_signal_handler(signal_handler *sig,property *p) { 
    if (unix_ask_void1() == CTRUE)
     { if (sig->signo == ((CL_INT)-1))
       close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"signal ~S not available on this machine")),
        _oid_(list::alloc(1,_oid_(sig))))));
      if ((p == Core.CL_SIG_DFL) && 
          (sig != Core.CL_SIGINT))
       { if ((CL_INT )((signal(sig->signo, SIG_DFL)==SIG_ERR)) == 1)
         { if ((sig == Core.CL_SIGKILL) || 
              (sig == Core.CL_SIGSTOP))
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"an attempt is made to ignore or supply a handler (~S) for ~S")),
            _oid_(list::alloc(2,_oid_(p),_oid_(sig))))));
          else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"signal ~S is not a valid signal number")),
              _oid_(list::alloc(1,_oid_(sig))))));
            }
        }
      else if (p == Core.CL_SIG_IGN)
       { if ((CL_INT )((signal(sig->signo, SIG_IGN)==SIG_ERR)) == 1)
         { if ((sig == Core.CL_SIGKILL) || 
              (sig == Core.CL_SIGSTOP))
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"an attempt is made to ignore or supply a handler (~S) for ~S")),
            _oid_(list::alloc(2,_oid_(p),_oid_(sig))))));
          else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"signal ~S is not a valid signal number")),
              _oid_(list::alloc(1,_oid_(sig))))));
            }
        }
      else if ((CL_INT )((signal((CL_INT)sig->signo, kernel_sighandler_integer)==SIG_ERR)) == 1)
       { if ((sig == Core.CL_SIGKILL) || 
            (sig == Core.CL_SIGSTOP))
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"an attempt is made to ignore or supply a handler (~S) for ~S")),
          _oid_(list::alloc(2,_oid_(p),_oid_(sig))))));
        else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"signal ~S is not a valid signal number")),
            _oid_(list::alloc(1,_oid_(sig))))));
          }
      }
    { property *Result ;
      { property * old = sig->handler;
        _void_(sig->handler = p);
        Result = old;
        }
      POP_SIGNAL; return (Result);}
    }
  


//<sb> this is the meta signal handler
// we dispatch it according to the current mapping sig/handler in claire.
// note that we catch any exception that can occur during the handler
// a false value is returned in such situation, this tell kernel handler
// to re-close the exception after having restore a correct sigprocmask
// IN CLAIRE A SIGNAL HANDLER REMAINS INSTALLED AFTER ITS DELIVERY
// The c++ function for: meta_sighandler(sigv:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireBoolean * meta_sighandler_integer(CL_INT sigv) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      { ClaireObject *V_CC ;
        { ClaireHandler c_handle = ClaireHandler();
          if ERROR_IN 
          { { OID  sig = nth_table1(Core.SIG_MAP,((OID)sigv));
              property * p = OBJECT(signal_handler,sig)->handler;
              if (sigv == ((CL_INT)-1))
               { system_error * _CL_obj = ((system_error *) GC_OBJECT(system_error,new_object_class(Kernel._system_error)));
                _void_(_CL_obj->index = 57);
                add_I_property(Kernel.instances,Kernel._system_error,11,_oid_(_CL_obj));
                close_exception(_CL_obj);
                }
              else if ((p != Core.CL_SIG_DFL) && 
                  ((p != Core.CL_SIG_IGN) && 
                    (p != Core.SIG_EXT)))
               { OID  htest;
                { { OID  m_some = CNULL;
                    { CL_INT loop_handle = ClEnv->cHandle;
                      ITERATE(m);
                      for (START(p->restrictions); NEXT(m);)
                      { ClaireBoolean * g0145I;
                        { list * dom = OBJECT(restriction,m)->domain;
                          g0145I = (((dom->length == 1) && 
                              ((*(dom))[1] == _oid_(Kernel._void))) ? CTRUE : ((belong_to(sig,(*(dom))[1]) == CTRUE) ? CTRUE : CFALSE));
                          }
                        
                        if (g0145I == CTRUE) { m_some= (m);
                            ClEnv->cHandle = loop_handle; break;}
                          }
                      }
                    htest = m_some;
                    }
                  GC_OID(htest);}
                if (htest != CNULL)
                 { restriction * h = OBJECT(restriction,htest);
                  if ((*(h->domain))[1] == _oid_(Kernel._integer))
                   apply_property(p,list::alloc(1,sig));
                  else apply_property(p,list::alloc(1,_oid_(Kernel._void)));
                    }
                else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"No available restriction of ~S to deliver signal ~S")),
                    _oid_(list::alloc(2,_oid_(p),sig)))));
                  }
              else if ((sig == _oid_(Core.CL_SIGINT)) && 
                  (p != Core.CL_SIG_IGN))
               { system_error * _CL_obj = ((system_error *) GC_OBJECT(system_error,new_object_class(Kernel._system_error)));
                _void_(_CL_obj->index = 34);
                add_I_property(Kernel.instances,Kernel._system_error,11,_oid_(_CL_obj));
                close_exception(_CL_obj);
                }
              V_CC = CTRUE;
              }
            ERROR_FREE;}
          else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
          { c_handle.catchIt();V_CC = CFALSE;
            }
          else PREVIOUS_HANDLER;}
        Result= (ClaireBoolean *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl Signal Handling
// raise the given signal to the calling process
// The c++ function for: raise(sig:signal_handler) [0]
CL_EXPORT void  raise_signal_handler(signal_handler *sig) { 
    if ((CL_INT )((raise(sig->signo) == -1)) == 1)
     Cerrorno(87,_integer_(sig->signo),0);
    POP_SIGNAL;}
  


//<sb> @doc @xl Signal Handling
// send the signal sig to the process with pid p.
// The c++ function for: kill(p:integer,sig:signal_handler) [0]
CL_EXPORT void  kill_integer(CL_INT p,signal_handler *sig) { 
    
#if defined(CLPC) || !defined(HAVE_KILL)
		Cerror(75,_string_("kill"),0);
	#else
		if(kill(p,sig->signo) == -1)
			Cerrorno(86,_integer_(p),_integer_(sig->signo));
	#endif
	;
    POP_SIGNAL;}
  


// *********************************************************************
// *   Part 3: signal mask                                             *
// *********************************************************************
//<sb> @doc @xl Signal Handling
// sigprocmask returns the set of signal that are part of the process signal mask,
// that is the set of signal that the subsystem blocks from delivery.
// The c++ function for: sigprocmask(_CL_obj:void) [NEW_ALLOC]
CL_EXPORT set * sigprocmask_void() { 
    { set *Result ;
      { set * l = set::empty(Core._signal_handler);
        
#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)
;
        Cerror(75,_string_("sigprocmask"),0);
        
#else
;
        sigset_t ss;
        sigemptyset(&ss);
        sigprocmask(SIG_SETMASK,0,&ss);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(g0146);
          bag *g0146_support;
          g0146_support = Core._signal_handler->descendents;
          for (START(g0146_support); NEXT(g0146);)
          { ClaireBoolean * g0147;
            { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(sig);
                V_C= Kernel.cfalse;
                for (START(OBJECT(ClaireClass,g0146)->instances); NEXT(sig);)
                if (OBJECT(signal_handler,sig)->signo != ((CL_INT)-1))
                 { signal_handler * sh = OBJECT(signal_handler,sig);
                  if ((CL_INT )(sigismember(&ss,sh->signo)) != 0)
                   l= (l->addFast((OID)sig));
                  }
                }
              
              g0147=OBJECT(ClaireBoolean,V_C);}
            if (g0147 == CTRUE)
             { ;ClEnv->cHandle = loop_handle; break;}
            }
          }
        
#endif
;
        Result = l;
        }
      POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl Signal Handling
// sigsetmask sets the set of signal for the process signal mask,
// that is the set of signal that the subsystem blocks from delivery.
// The c++ function for: sigsetmask(self:subtype[signal_handler]) [NEW_ALLOC]
CL_EXPORT set * sigsetmask_type(ClaireType *self) { 
    
    GC_BIND;
    { set *Result ;
      { set * l = set::empty(Core._signal_handler);
        
#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)
;
        Cerror(75,_string_("sigprocmask"),0);
        
#else
;
        sigset_t ss,so;
        sigemptyset(&ss);sigemptyset(&so);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(sig);
          bag *sig_support;
          sig_support = GC_OBJECT(bag,enumerate_any(_oid_(self)));
          for (START(sig_support); NEXT(sig);)
          { signal_handler * sh = OBJECT(signal_handler,sig);
            sigaddset(&ss,sh->signo);
            }
          }
        sigprocmask(SIG_SETMASK,&ss,&so);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(g0148);
          bag *g0148_support;
          g0148_support = Core._signal_handler->descendents;
          for (START(g0148_support); NEXT(g0148);)
          { ClaireBoolean * g0149;
            { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(sig);
                V_C= Kernel.cfalse;
                for (START(OBJECT(ClaireClass,g0148)->instances); NEXT(sig);)
                if (OBJECT(signal_handler,sig)->signo != ((CL_INT)-1))
                 { signal_handler * sh = OBJECT(signal_handler,sig);
                  if ((CL_INT )(sigismember(&so,sh->signo)) != 0)
                   l= (l->addFast((OID)sig));
                  }
                }
              
              g0149=OBJECT(ClaireBoolean,V_C);}
            if (g0149 == CTRUE)
             { ;ClEnv->cHandle = loop_handle; break;}
            }
          }
        
#endif
;
        Result = l;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl Signal Handling
// sigpending returns the set of signals that are currently blocked from delivery,
// i.e. the process has been signaled but the delivery is blocked until the signal
// is unblocked (sigunblock).
// The c++ function for: sigpending(_CL_obj:void) [NEW_ALLOC]
CL_EXPORT set * sigpending_void() { 
    { set *Result ;
      { set * l = set::empty(Core._signal_handler);
        
#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)
;
        Cerror(75,_string_("sigpending"),0);
        
#else
;
        sigset_t ss;
        if(sigpending(&ss) == -1) Cerrorno(74,_string_("sigpending @ void"),0);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(g0150);
          bag *g0150_support;
          g0150_support = Core._signal_handler->descendents;
          for (START(g0150_support); NEXT(g0150);)
          { ClaireBoolean * g0151;
            { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(sig);
                V_C= Kernel.cfalse;
                for (START(OBJECT(ClaireClass,g0150)->instances); NEXT(sig);)
                if (OBJECT(signal_handler,sig)->signo != ((CL_INT)-1))
                 { signal_handler * sh = OBJECT(signal_handler,sig);
                  if ((CL_INT )(sigismember(&ss,sh->signo)) != 0)
                   l= (l->addFast((OID)sig));
                  }
                }
              
              g0151=OBJECT(ClaireBoolean,V_C);}
            if (g0151 == CTRUE)
             { ;ClEnv->cHandle = loop_handle; break;}
            }
          }
        
#endif
;
        Result = l;
        }
      POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl Signal Handling
// sigblock adds a set of signal to the process signal mask.
// The c++ function for: sigblock(self:subtype[signal_handler]) [NEW_ALLOC]
CL_EXPORT set * sigblock_type(ClaireType *self) { 
    
    GC_BIND;
    { set *Result ;
      { set * l = set::empty(Core._signal_handler);
        
#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)
;
        Cerror(75,_string_("sigprocmask"),0);
        
#else
;
        sigset_t ss,so;
        sigemptyset(&ss);sigemptyset(&so);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(sig);
          bag *sig_support;
          sig_support = GC_OBJECT(bag,enumerate_any(_oid_(self)));
          for (START(sig_support); NEXT(sig);)
          { signal_handler * sh = OBJECT(signal_handler,sig);
            sigaddset(&ss,sh->signo);
            }
          }
        sigprocmask(SIG_BLOCK,&ss,&so);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(g0152);
          bag *g0152_support;
          g0152_support = Core._signal_handler->descendents;
          for (START(g0152_support); NEXT(g0152);)
          { ClaireBoolean * g0153;
            { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(sig);
                V_C= Kernel.cfalse;
                for (START(OBJECT(ClaireClass,g0152)->instances); NEXT(sig);)
                if (OBJECT(signal_handler,sig)->signo != ((CL_INT)-1))
                 { signal_handler * sh = OBJECT(signal_handler,sig);
                  if ((CL_INT )(sigismember(&so,sh->signo)) != 0)
                   l= (l->addFast((OID)sig));
                  }
                }
              
              g0153=OBJECT(ClaireBoolean,V_C);}
            if (g0153 == CTRUE)
             { ;ClEnv->cHandle = loop_handle; break;}
            }
          }
        
#endif
;
        Result = l;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl Signal Handling
// sigunblock removes a set of signal to the process signal mask.
// The c++ function for: sigunblock(self:subtype[signal_handler]) [NEW_ALLOC]
CL_EXPORT set * sigunblock_type(ClaireType *self) { 
    
    GC_BIND;
    { set *Result ;
      { set * l = set::empty(Core._signal_handler);
        
#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)
;
        Cerror(75,_string_("sigprocmask"),0);
        
#else
;
        sigset_t ss,so;
        sigemptyset(&ss);sigemptyset(&so);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(sig);
          bag *sig_support;
          sig_support = GC_OBJECT(bag,enumerate_any(_oid_(self)));
          for (START(sig_support); NEXT(sig);)
          { signal_handler * sh = OBJECT(signal_handler,sig);
            sigaddset(&ss,sh->signo);
            }
          }
        sigprocmask(SIG_UNBLOCK,&ss,&so);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(g0154);
          bag *g0154_support;
          g0154_support = Core._signal_handler->descendents;
          for (START(g0154_support); NEXT(g0154);)
          { ClaireBoolean * g0155;
            { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(sig);
                V_C= Kernel.cfalse;
                for (START(OBJECT(ClaireClass,g0154)->instances); NEXT(sig);)
                if (OBJECT(signal_handler,sig)->signo != ((CL_INT)-1))
                 { signal_handler * sh = OBJECT(signal_handler,sig);
                  if ((CL_INT )(sigismember(&so,sh->signo)) != 0)
                   l= (l->addFast((OID)sig));
                  }
                }
              
              g0155=OBJECT(ClaireBoolean,V_C);}
            if (g0155 == CTRUE)
             { ;ClEnv->cHandle = loop_handle; break;}
            }
          }
        
#endif
;
        Result = l;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl Signal Handling
// sigsuspend temporarily changes the process signal mask to the set sigs, and then
// wait for a signal to arrive; on return the previous set of masked signals is restored.
// The signal mask set is usually empty to indicate that all signals are to be unblocked
// for the duration of the call.
// The c++ function for: sigsuspend(self:subtype[signal_handler]) [NEW_ALLOC]
CL_EXPORT void  sigsuspend_type(ClaireType *self) { 
    
    GC_BIND;
    
#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)
;
    Cerror(75,_string_("sigsuspend"),0);
    
#else
;
    sigset_t ss;
    sigemptyset(&ss);
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(sig);
      bag *sig_support;
      sig_support = GC_OBJECT(bag,enumerate_any(_oid_(self)));
      for (START(sig_support); NEXT(sig);)
      { signal_handler * sh = OBJECT(signal_handler,sig);
        sigaddset(&ss,sh->signo);
        }
      }
    sigsuspend(&ss);
    
#endif
;
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> install the SIGINT (system_error 34) handler
// *********************************************************************
// *   Part 4: itimer                                                  *
// *********************************************************************
//<sb> @doc @xl Signal Handling
// UNIX timer interface can handle 3 kind of timers:
// \ul
// \li The ITIMER_REAL timer decrements in real time.
// A SIGALRM signal is delivered when this timer expires.
// \li The ITIMER_VIRTUAL timer decrements in process virtual time.
// It runs only when the process is executing. A SIGVTALRM signal is
// delivered when it expires.
// \li The ITIMER_PROF timer decrements both in process virtual time and
// when the system is running on behalf of the process. It is designed
// to be used by interpreters in statistically profiling the execution
// of interpreted programs. Each time the ITIMER_PROF timer expires, the
// SIGPROF signal is delivered. Because this signal may interrupt in-progress
// system calls, programs using this timer must be prepared to restart
// interrupted system calls.
// \/ul
//<sb> @doc @xl Signal Handling
// setitimer sets a timer to the specified interval / value (in milliseconds). If value is non-zero,
// it indicates the time to the next timer expiration (at reload). If interval is non-zero, it
// specifies a value to be used in reloading value when the timer expires. Setting interval/value
// to 0/0 disables a timer. Setting interval to 0 causes a timer to be disabled after its next
// expiration (assuming value is non-zero). For instance we could implement a timeout as follow :
// \code
// timeout() : void -> error("Time out !")
//
// (signal(SIGALRM, timeout))
//
// (setitimer(ITIMER_REAL, 0, 10000))
// \/code
// which would raise a time out exception after 10 seconds of (real time) processing.
// The c++ function for: setitimer(g0156:itimer,g0157:integer,g0158:integer) [NEW_ALLOC]
CL_EXPORT tuple * setitimer_itimer_(Core_itimer *g0156,CL_INT g0157,CL_INT g0158) { 
    return setitimer_itimer(g0156,g0157,g0158)->copyIfNeeded();
}


// The c++ function for: setitimer(it:itimer,interval:integer,value:integer) [NEW_ALLOC]
CL_EXPORT tuple * setitimer_itimer(Core_itimer *it,CL_INT interval,CL_INT value) { 
      { tuple *Result ;
      { CL_INT  ointerval = 0;
        CL_INT  ovalue = 0;
        
#if defined(CLPC) || !defined(HAVE_SETITIMER)
;
        Cerror(75,_string_("setitimer"),0);
        
#else
;
        struct itimerval sit,osit;
        sit.it_interval.tv_sec = interval / 1000;
        sit.it_interval.tv_usec = interval % 1000;
        sit.it_value.tv_sec = value / 1000;
        sit.it_value.tv_usec = value % 1000;
        if(setitimer(it->timerno, &sit, &osit) == -1) {;
        Cerrorno(88, it->timerno, 0); };
        ointerval= (CL_INT)((CL_INT )(osit.it_interval.tv_sec * 1000 + osit.it_interval.tv_usec));
        ovalue= (CL_INT)((CL_INT )(osit.it_value.tv_sec * 1000 + osit.it_value.tv_usec));
        
#endif
;
        Result = tuple::allocStack(2,((OID)ointerval),((OID)ovalue));
        }
      return (Result);}
    }
  


//<sb> @doc @xl Signal Handling
// getitimer returns the current values for timer it (i.e. the interval and the value).
// The c++ function for: getitimer(g0159:itimer) [NEW_ALLOC]
CL_EXPORT tuple * getitimer_itimer_(Core_itimer *g0159) { 
    return getitimer_itimer(g0159)->copyIfNeeded();
}


// The c++ function for: getitimer(it:itimer) [NEW_ALLOC]
CL_EXPORT tuple * getitimer_itimer(Core_itimer *it) { 
      { tuple *Result ;
      { CL_INT  interval = 0;
        CL_INT  value = 0;
        
#if defined(CLPC) || !defined(HAVE_GETITIMER)
;
        Cerror(75,_string_("getitimer"),0);
        
#else
;
        struct itimerval sit;
        if(getitimer(it->timerno, &sit) == -1) {;
        Cerrorno(89, it->timerno, 0); };
        interval= (CL_INT)((CL_INT )(sit.it_interval.tv_sec * 1000 + sit.it_interval.tv_usec));
        value= (CL_INT)((CL_INT )(sit.it_value.tv_sec * 1000 + sit.it_value.tv_usec));
        
#endif
;
        Result = tuple::allocStack(2,((OID)interval),((OID)value));
        }
      return (Result);}
    }
  


// *********************************************************************
// *   Part 5: waitpid                                                 *
// *********************************************************************
//<sb> @doc @xl Process handling
// A process status is returned by waitpid and tell how a child process
// has exited:
// \ul
// \li WRUNNING : the child still runs
// \li WEXITED : the child exited normally with a call to exit
// \li WSIGNALED : the child was terminated by a signal, this may be an
// abnormal termination that caused the creation a core dump file.
// \li WSTOPPED : the child was stopped
// \/ul
//<sb> @doc @xl Process handling
// waitpid is a the UNIX interface to get status of child process.
// The parameter p specifies the set of child processes to wait for:
// \ul
// \li p = -1 : the call waits for any child process.
// \li p = 0 : the call waits for any child process in the process group of the caller.
// \li p > 0 : the call waits for the process with process id p.
// \li else : the call waits for any process whose process group id equals the absolute value of p.
// \/ul
// block?, when true, tell that the call should block until a waited child terminates.
// The c++ function for: (CL_INT *)g0163:integer,g0164:boolean) [NEW_ALLOC]
CL_EXPORT tuple * waitpid_integer1_(CL_INT g0163,ClaireBoolean *g0164) { 
    return waitpid_integer1(g0163,g0164)->copyIfNeeded();
}


// The c++ function for: (CL_INT *)p:integer,block?:boolean) [NEW_ALLOC]
CL_EXPORT tuple * waitpid_integer1(CL_INT p,ClaireBoolean *block_ask) { 
      
    GC_BIND;
    { tuple *Result ;
      { tuple * g0160 = waitpid_status_integer(p,block_ask);
        CL_INT  status = ((CL_INT)(*(g0160))[1]);
        CL_INT  pid = ((CL_INT)(*(g0160))[2]);
        CL_INT  no = ((CL_INT)(*(g0160))[3]);
        process_status * pstatus = ((status == 0) ?
          Core.CL_WRUNNING :
          ((status == 3) ?
            Core.CL_WSIGNALED :
            ((status == 2) ?
              Core.CL_WSTOPPED :
              Core.CL_WEXITED ) ) );
        if (pstatus == Core.CL_WEXITED)
         { OID v_bag;
          GC_ANY(Result= tuple::empty());
          ((tuple *) Result)->addFast((OID)_oid_(pstatus));
          ((tuple *) Result)->addFast((OID)((OID)pid));
          if (no == ((CL_INT)-1))
           v_bag = CNULL;
          else v_bag = ((OID)no);
            ((tuple *) Result)->addFast((OID)v_bag);}
        else { OID  sigtest;
            { { OID  sig_some = CNULL;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(g0161);
                  bag *g0161_support;
                  g0161_support = Core._signal_handler->descendents;
                  for (START(g0161_support); NEXT(g0161);)
                  { GC_LOOP;
                    { ClaireBoolean * g0162;
                      { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                          OID gc_local;
                          ITERATE(sig);
                          V_C= Kernel.cfalse;
                          for (START(OBJECT(ClaireClass,g0161)->instances); NEXT(sig);)
                          { GC_LOOP;
                            if (OBJECT(signal_handler,sig)->signo == no)
                             { GC_UNLOOP;V_C = sig_some= (sig);
                              ClEnv->cHandle = loop_handle;break;}
                            GC_UNLOOP; POP_SIGNAL;}
                          }
                        
                        g0162=OBJECT(ClaireBoolean,V_C);}
                      if (g0162 == CTRUE)
                       { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                      }
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                sigtest = sig_some;
                }
              GC_OID(sigtest);}
            if (sigtest != CNULL)
             { signal_handler * sig = OBJECT(signal_handler,sigtest);
              Result = tuple::alloc(3,_oid_(pstatus),
                ((OID)pid),
                _oid_(sig));
              }
            else { OID v_bag;
                GC_ANY(Result= tuple::empty());
                ((tuple *) Result)->addFast((OID)_oid_(pstatus));
                ((tuple *) Result)->addFast((OID)((OID)pid));
                if (no == ((CL_INT)-1))
                 v_bag = CNULL;
                else v_bag = ((OID)no);
                  ((tuple *) Result)->addFast((OID)v_bag);}
              }
          }
      GC_UNBIND; return (Result);}
    }
  


//<sb> @doc @xl Process handling
// (CL_INT *)p) is equivalent to (CL_INT *)p, true)
// The c++ function for: (CL_INT *)g0165:integer) [NEW_ALLOC]
CL_EXPORT tuple * waitpid_integer2_(CL_INT g0165) { 
    return waitpid_integer2(g0165)->copyIfNeeded();
}


// The c++ function for: (CL_INT *)p:integer) [NEW_ALLOC]
CL_EXPORT tuple * waitpid_integer2(CL_INT p) { 
      { tuple *Result ;
      Result = (tuple *)waitpid_integer1(p,CTRUE)->copyIfNeeded();
      return (Result);}
    }
  



/***** CLAIRE Compilation of file ./meta/port.cl 
         [version 3.5.0 / safety 5] *****/


// *********************************************************************
// * CLAIRE                                            Sylvain Benilan *
// * port.cl                                                           *
// * Copyright (C) 2005 xl. All Rights Reserved                        *
// *********************************************************************
// In XL CLAIRE port are implemented in claire and are
// compatible with CLAIRE 3 (<ycs>) C++ implementation.
// In this implementation ports are organized into an extensible hierarchy
// of objects (instead of a primitive in <ycs>).
// Two sorts are defined, on the one hand device that are 'physical' port
// like a descriptor or a blob that may be handled through a chain of filter
// and on the other hand filters that are port that may analyze and/or
// transform and/or collect read and/or written data like a buffer, a line
// counter or even a MIME decoder or any kind embedded protocols.
// ***************************************************************************
// * part 1: low level char*                                                 *
// * part 1: model                                                           *
// * part 2: default interface                                               *
// * part 3: API                                                             *
// * part 4: null port                                                       *
// * part 4: blob                                                            *
// * part 5: buffer                                                          *
// * part 6: line_buffer                                                     *
// * part 7: byte_counter                                                    *
// * part 8: line_counter                                                    *
// * part 9: descriptor                                                      *
// * part 10: disk_file                                                      *
// * part 11: pipe                                                           *
// * part 12: socket                                                         *
// ***************************************************************************
// ***************************************************************************
// * part 1: low level char*                                                 *
// ***************************************************************************
//<sb> @doc @xl port
// read_port and write_port operate on a given buffer of a given size. these
// buffers are char* imported from C, this way we have an interface
// similar to read(2) and write(2)
//<sb> @doc @xl port
// translate the char* pointer self with an offset of n bytes
// The c++ function for: +(self:char*,n:integer) [SAFE_RESULT+SAFE_GC]
CL_EXPORT char* _plus_char_star1(char*self,CL_INT n) { 
    POP_SIGNAL; return ((char*)((self + n)));}
  


//<sb> Warning: no bound check on char*
//<sb> @doc @xl port
// get the char at position n in self (n is a 1 based index).\n
// \b Warning \/b : there is no bound check !
// The c++ function for: nth(self:char*,n:integer) [SAFE_RESULT+SAFE_GC]
CL_EXPORT ClaireChar * nth_char_star1(char*self,CL_INT n) { 
    POP_SIGNAL; return (char_I_integer((CL_INT )(((unsigned char)(self[n-1])))));}
  


//<sb> @doc @xl port
// sets the n\sup th\/sup char in self with c (n is a 1 based index).\n
// \b Warning \/b : there is no bound check !
// The c++ function for: nth=(self:char*,n:integer,c:char) [SAFE_GC]
CL_EXPORT void  nth_equal_char_star1(char*self,CL_INT n,ClaireChar *c) { 
    self[n-1] = (char)c->ascii;
    POP_SIGNAL;}
  


//<sb> @doc @xl port
// make a new string of length len from a char*
// The c++ function for: string!(self:char*,len:integer) [NEW_ALLOC+SAFE_GC]
CL_EXPORT char * string_I_char_star1(char*self,CL_INT len) { 
    { char *Result ;
      { char * s = make_string_integer1(len);
        memcpy(s, self, len);
        Result = s;
        }
      POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// acquire the memory address of a string.
// The c++ function for: char*!(self:string) [0]
CL_EXPORT char* char_star_I_string1(char *self) { 
    POP_SIGNAL; return ((char*)(self));}
  


//<sb> do not protect arguments in char* tools
// ***************************************************************************
// * part 1: model                                                           *
// ***************************************************************************
//<sb> port inherit from freeable_object, this way we can
// catch an instance deallocation (for instance to close an
// open descriptor).
// note: the class port is defined in the kernel, some slots
// needs to be added by hand :
//<sb> @doc @xl port
// physical port like a descriptor or a blob that may be handled
// through a chain of filter
//<sb> @doc @xl port
// port that may analyze and/or transform and/or collect read
// and/or written data like a buffer, a line counter or even a
// MIME decoder or any kind embedded protocols.
// The c++ function for: get_top_most(self:port) [RETURN_ARG]
CL_EXPORT PortObject * get_top_most_port1(PortObject *self) { 
    { PortObject *Result ;
      Result = ((INHERIT(self->isa,Core._device)) ?
        ((CLREAD(device,self,filters)->length != 0) ?
          OBJECT(PortObject,last_list(CLREAD(device,self,filters))) :
          self ) :
        ((INHERIT(self->isa,Core._filter)) ?
          OBJECT(PortObject,last_list(CLREAD(filter,self,dev)->filters)) :
          self ) );
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: get_device(self:port) [RETURN_ARG]
CL_EXPORT device * get_device_port1(PortObject *self) { 
    { device *Result ;
      { ClaireObject *V_CC ;
        if (INHERIT(self->isa,Core._filter))
         V_CC = CLREAD(filter,self,dev);
        else if (INHERIT(self->isa,Core._device))
         V_CC = self;
        else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~S is not a device")),
            _oid_(list::alloc(1,_oid_(self))))));
          Result= (device *) V_CC;}
      POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// filter! should be used by filter constructors, it ensures
// the good shape of the inner relations (i.e. between the filter
// and its device)
// The c++ function for: filter!(self:filter,p:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT filter * filter_I_filter1(filter *self,PortObject *p) { 
    
    GC_BIND;
    if (p->closed_ask == CTRUE)
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Attempt to add filter ~S to ~S that is already closed")),
      _oid_(Kernel.nil))));
    { filter *Result ;
      { OID  d;
        { if (INHERIT(p->isa,Core._device))
           d = _oid_(p);
          else if (INHERIT(p->isa,Core._filter))
           d = _oid_(CLREAD(filter,p,dev));
          else d = Kernel.cfalse;
            GC_OID(d);}
        list * fs = GC_OBJECT(list,OBJECT(device,d)->filters);
        OID  p;
        if (fs->length != 0)
         p = last_list(fs);
        else p = d;
          update_property(Core.dev,
          self,
          5,
          Kernel._object,
          d);
        _void_(self->target = OBJECT(PortObject,p));
        Result = self;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: filter!_filter1_type
CL_EXPORT ClaireType * filter_I_filter1_type(ClaireType *self,ClaireType *p) { 
    POP_SIGNAL; return (self);}
  


//<sb> @doc @xl port
// tell that the filter should close its target when it is
// itself closed (cascading close)
// The c++ function for: close_target!(self:filter) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT filter * close_target_I_filter1(filter *self) { 
    _void_(self->close_target_ask = CTRUE);
    POP_SIGNAL; return (self);}
  


// The c++ function for: close_target!_filter1_type
CL_EXPORT ClaireType * close_target_I_filter1_type(ClaireType *self) { 
    POP_SIGNAL; return (self);}
  


// The c++ function for: inner_print(self:device) [NEW_ALLOC]
CL_EXPORT void  inner_print_device1(device *self) { 
    (*Kernel.princ)(_oid_(self));
    POP_SIGNAL;}
  


// The c++ function for: inner_print(self:filter) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  inner_print_filter1(filter *self) { 
    
    GC_BIND;
    if (self->dev == (NULL))
     { princ_string(((char*)"unconneted "));
      print_any(_oid_(OWNER(_oid_(self))));
      }
    else { (*Kernel.princ)(_oid_(self));
        princ_string(((char*)"("));
        (*Core.inner_print)(GC_OID(_oid_(self->target)));
        princ_string(((char*)")"));
        }
      GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_print(self:filter) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_filter1_Core(filter *self) { 
    if (self->dev == (NULL))
     { princ_string(((char*)"<unconneted "));
      print_any(_oid_(OWNER(_oid_(self))));
      princ_string(((char*)">"));
      }
    else { princ_string(((char*)"<"));
        inner_print_filter1(self);
        princ_string(((char*)">"));
        }
      POP_SIGNAL;}
  


// The c++ function for: self_print(self:device) [NEW_ALLOC]
CL_EXPORT void  self_print_device1_Core(device *self) { 
    princ_string(((char*)"<"));
    (*Kernel.princ)(_oid_(self));
    princ_string(((char*)">"));
    POP_SIGNAL;}
  


// The c++ function for: princ(self:port) [0]
CL_EXPORT void  princ_port1(PortObject *self) { 
    princ_string(OWNER(_oid_(self))->name->name);
    POP_SIGNAL;}
  


// ***************************************************************************
// * part 2: default interface                                               *
// ***************************************************************************
// The port interface :
//	- eof_port? : check the end-of-file
//	- read_port : read n bytes
//	- unget_port : gives a chance for the port to unget data
//	- write_port : write n bytes
//	- flush_port : gives a chance for the port to write out any pending
//		datas (buffer)
//	- close_port : gives a chance for the port to clean internal data
//<sb> @doc @xl port
// interface to check the end-of-file condition on a given port :
// \code
// eof_port?(self:my_port) : boolean ->
// 	...
// \/code
//<sb> @doc @xl port
// interface to read a chunk of data :
// \code
// read_port(self:my_port, buf:data*, len:integer) : integer ->
// 	...
// \/code
// the returned value should be the amount of bytes that were
// actually read
//<sb> @doc @xl port
// interface to unget a chunk of data :
// \code
// unget_port(self:my_port, buf:data*, len:integer) : void ->
// 	...
// \/code
//<sb> @doc @xl port
// interface to write a chunk of data
// \code
// write_port(self:my_port, buf:data*, len:integer) : integer ->
// 	...
// \/code
// the returned value should be the amount of bytes that were
// actualy written
//<sb> @doc @xl port
// interface to flush pending buffered data
// \code
// flush_port(self:my_port) : void ->
// 	...
// \/code
//<sb> @doc @xl port
// interface to close the port :
// \code
// close_port(self:my_port) : void ->
// 	...
// \/code
// The c++ function for: write_port(self:port,buf:char*,len:integer) [NEW_ALLOC]
CL_EXPORT CL_INT  write_port_port1_Core(PortObject *self,char*buf,CL_INT len) { 
    
    GC_BIND;
    { CL_INT Result = 0;
      { ClaireClass * c = OWNER(_oid_(self));
        OID  r = GC_OID(_oid_(_at_property1(Core.write_port,c)));
        if ((boolean_I_any(r) == CTRUE) && 
            ((*(OBJECT(bag,(*Kernel.domain)(r))))[1] == _oid_(c)))
         Result = ((CL_INT)apply_method(OBJECT(method,r),list::alloc(3,_oid_(self),
          GC_OID(ClAlloc->import(Core._char_star,(OID *) buf)),
          ((OID)len))));
        else if (INHERIT(self->isa,Core._filter))
         Result = ((CL_INT)Core.write_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(CLREAD(filter,self,target))))),((CL_INT) buf),((CL_INT) len)));
        else { close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"write_port @ ~S not implemented")),
              _oid_(list::alloc(1,_oid_(OWNER(_oid_(self))))))));
            Result = 0;
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: read_port(self:port,buf:char*,len:integer) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT CL_INT  read_port_port1_Core(PortObject *self,char*buf,CL_INT len) { 
    
    GC_BIND;
    { CL_INT Result = 0;
      { ClaireClass * c = OWNER(_oid_(self));
        OID  r = GC_OID(_oid_(_at_property1(Core.read_port,c)));
        if ((boolean_I_any(r) == CTRUE) && 
            ((*(OBJECT(bag,(*Kernel.domain)(r))))[1] == _oid_(c)))
         Result = ((CL_INT)apply_method(OBJECT(method,r),list::alloc(3,_oid_(self),
          GC_OID(ClAlloc->import(Core._char_star,(OID *) buf)),
          ((OID)len))));
        else if (INHERIT(self->isa,Core._filter))
         Result = ((CL_INT)Core.read_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(CLREAD(filter,self,target))))),((CL_INT) buf),((CL_INT) len)));
        else { close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"read_port @ ~S not implemented")),
              _oid_(list::alloc(1,_oid_(OWNER(_oid_(self))))))));
            Result = 0;
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: unget_port(self:port,buf:char*,len:integer) [NEW_ALLOC]
CL_EXPORT void  unget_port_port1_Core(PortObject *self,char*buf,CL_INT len) { 
    
    GC_BIND;
    { ClaireClass * c = OWNER(_oid_(self));
      OID  r = GC_OID(_oid_(_at_property1(Core.unget_port,c)));
      if ((boolean_I_any(r) == CTRUE) && 
          ((*(OBJECT(bag,(*Kernel.domain)(r))))[1] == _oid_(c)))
       apply_method(OBJECT(method,r),list::alloc(3,_oid_(self),
        GC_OID(ClAlloc->import(Core._char_star,(OID *) buf)),
        ((OID)len)));
      else if (INHERIT(self->isa,Core._filter))
       _void_(Core.unget_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(CLREAD(filter,self,target))))),((CL_INT) buf),((CL_INT) len)));
      else { close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"unget_port @ ~S not implemented")),
            _oid_(list::alloc(1,_oid_(OWNER(_oid_(self))))))));
          ;}
        }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: eof_port?(self:port) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT ClaireBoolean * eof_port_ask_port1_Core(PortObject *self) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      { ClaireObject *V_CC ;
        { ClaireClass * c = OWNER(_oid_(self));
          OID  r = GC_OID(_oid_(_at_property1(Core.eof_port_ask,c)));
          if ((boolean_I_any(r) == CTRUE) && 
              ((*(OBJECT(bag,(*Kernel.domain)(r))))[1] == _oid_(c)))
           V_CC = OBJECT(ClaireBoolean,apply_method(OBJECT(method,r),list::alloc(1,_oid_(self))));
          else if (INHERIT(self->isa,Core._filter))
           V_CC = OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(CLREAD(filter,self,target))))))));
          else { close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"eof_port? @ ~S not implemented")),
                _oid_(list::alloc(1,_oid_(OWNER(_oid_(self))))))));
              V_CC = 0;
              }
            }
        Result= (ClaireBoolean *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: flush_port(self:port) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT void  flush_port_port1_Core(PortObject *self) { 
    
    GC_BIND;
    { ClaireClass * c = OWNER(_oid_(self));
      OID  r = GC_OID(_oid_(_at_property1(Core.flush_port,c)));
      if ((boolean_I_any(r) == CTRUE) && 
          ((*(OBJECT(bag,(*Kernel.domain)(r))))[1] == _oid_(c)))
       apply_method(OBJECT(method,r),list::alloc(1,_oid_(self)));
      else if (INHERIT(self->isa,Core._filter))
       _void_(Core.flush_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(CLREAD(filter,self,target)))))));
      else ;}
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: close_port(self:port) [NEW_ALLOC]
CL_EXPORT void  close_port_port1_Core(PortObject *self) { 
    
    GC_BIND;
    { ClaireClass * c = OWNER(_oid_(self));
      OID  r = GC_OID(_oid_(_at_property1(Core.close_port,c)));
      if ((boolean_I_any(r) == CTRUE) && 
          ((*(OBJECT(bag,(*Kernel.domain)(r))))[1] == _oid_(c)))
       apply_method(OBJECT(method,r),list::alloc(1,_oid_(self)));
      else ;}
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> activate fast dispatch on port interface
// Note: interpreted messages won't be handled automatically since the
// interface for port uses fast dispatch. In default handlers we try to
// dispatch the message by hand. This is a limited support of dynamic
// dispatch, it will only work with interpreted code if it is based on
// default handlers (i.e. with domain port). The dynamic dispatch is safe
// on interpreted classes derived from device or filter whereas, for
// instance, an attempt to write on a port derived from descriptor will
// fail.
// ***************************************************************************
// * part 3: API                                                             *
// ***************************************************************************
//<sb> @doc @xl port
// check whether the end-of-file condition has been reached
// The c++ function for: eof?(self:port) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT ClaireBoolean * eof_ask_port1(PortObject *self) { 
    POP_SIGNAL; return (OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) self)))));}
  


//<sb> @doc @xl port
// read a string of n bytes on self
// the length of the returned string may be
// lower than n if an eof condition is reached
// on self
// The c++ function for: fread(self:port,n:integer) [NEW_ALLOC]
CL_EXPORT char * fread_port4(PortObject *self,CL_INT n) { 
    
    GC_BIND;
    { char *Result ;
      { char * s = GC_STRING(make_string_integer1(n));
        shrink_string(s,((CL_INT)Core.read_port->fcall(((CL_INT) self),((CL_INT) (char*)(s)),((CL_INT) n))));
        Result = s;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// read inside an existing string, this overwrites
// the string content and may modify the string length
// if an eof condition is reached on self. the amount
// of queried bytes is the length of the input string
// The c++ function for: fread(self:port,s:string) [NEW_ALLOC]
CL_EXPORT CL_INT  fread_port5(PortObject *self,char *s) { 
    
    GC_BIND;
    { CL_INT Result = 0;
      { CL_INT  n = LENGTH_STRING(s);
        CL_INT  on = ((CL_INT)Core.read_port->fcall(((CL_INT) self),((CL_INT) (char*)(s)),((CL_INT) n)));
        shrink_string(s,on);
        Result = on;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// read all data on self until eof
// The c++ function for: fread(self:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT char * fread_port6(PortObject *self) { 
    
    GC_BIND;
    { char *Result ;
      if (INHERIT(self->isa,Core._blob))
       { blob * b = ((blob *) self);
        CL_INT  n = remain_to_read_blob1(((blob *) self));
        char * s = GC_STRING(make_string_integer1(n));
        memcpy(s,b->data,n);
        _void_(b->read_index = b->write_index);
        Result = s;
        }
      else { blob * b = GC_OBJECT(blob,blob_I_integer1(4096));
          freadwrite_port3(self,b);
          { char * res = GC_STRING(string_I_blob1(b));
            fclose_port1(b);
            Result = res;
            }
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// read a single char on self
// reading an EOF char does not mean that
// the end-of-file is reached, one should use
// eof? @ port to check the eof condition
// The c++ function for: getc(self:port) [NEW_ALLOC]
CL_EXPORT ClaireChar * getc_port1(PortObject *self) { 
    
    GC_BIND;
    { ClaireChar *Result ;
      { ClaireObject *V_CC ;
        { char c;
          if (((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) self))))) == CTRUE) || 
              (Core.read_port->fcall(((CL_INT) self),((CL_INT) (char*)(&c)),((CL_INT) 1)) == ((OID)0)))
           V_CC = OBJECT(ClaireChar,Core._eof->value);
          else V_CC = (ClaireChar *)(ClaireChar *)(_char_(c));
            }
        Result= (ClaireChar *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// unget a string such the next data that can be read is s
// The c++ function for: unget(self:port,s:string) [NEW_ALLOC]
CL_EXPORT void  unget_port1(PortObject *self,char *s) { 
    
    GC_BIND;
    _void_(Core.unget_port->fcall(((CL_INT) self),((CL_INT) (char*)(s)),((CL_INT) LENGTH_STRING(s))));
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> @doc @xl port
// unget a string such the next char that can be read is c
// The c++ function for: unget(self:port,c:char) [NEW_ALLOC]
CL_EXPORT void  unget_port2(PortObject *self,ClaireChar *c) { 
    
    GC_BIND;
    char ch = (char)c->ascii;
    _void_(Core.unget_port->fcall(((CL_INT) self),((CL_INT) (char*)((&ch))),((CL_INT) 1)));
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> TODO: read a single UTF-8 sequence
//
//<sb> @doc port
// flush pending buffers in the filter chain such
// pending data are actually written on the device
// The c++ function for: flush(self:port) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT void  flush_port1(PortObject *self) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { PortObject * p = self;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((INHERIT(p->isa,Core._filter)))
        { GC_LOOP;
          _void_(Core.flush_port->fcall(((CL_INT) p)));
          GC__ANY(p = CLREAD(filter,p,target), 1);
          GC_UNLOOP;POP_SIGNAL;}
        }
      _void_(Core.flush_port->fcall(((CL_INT) p)));
      }
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> @doc port
// for compatibility with <ycs> mainly used for stdin
// The c++ function for: flush(self:port,n:integer) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  flush_port2(PortObject *self,CL_INT n) { 
    _void_(self->firstc = n);
    POP_SIGNAL;}
  


//<sb> @doc @xl port
// writes a raw string on the port p
// The c++ function for: fwrite(self:string,p:port) [NEW_ALLOC]
CL_EXPORT CL_INT  fwrite_string2(char *self,PortObject *p) { 
    
    GC_BIND;
    { CL_INT Result = 0;
      Result = ((CL_INT)Core.write_port->fcall(((CL_INT) p),((CL_INT) (char*)(self)),((CL_INT) LENGTH_STRING(self))));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc port
// writes a single byte on p
// The c++ function for: putc(self:char,p:port) [NEW_ALLOC]
CL_EXPORT void  putc_char1(ClaireChar *self,PortObject *p) { 
    
    GC_BIND;
    char c = (char)self->ascii;
    Core.write_port->fcall(((CL_INT) p),((CL_INT) (char*)(&c)),((CL_INT) 1));
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> @doc @xl port
// read all data from src until eof and write it on trgt
// without performing any allocation. returns the amount of byte
// transfered.
// The c++ function for: freadwrite(src:port,trgt:port) [NEW_ALLOC]
CL_EXPORT CL_INT  freadwrite_port3(PortObject *src,PortObject *trgt) { 
    
    GC_BIND;
    if (src == trgt)
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Attempt to freadwrite ~S on itself !")),
      _oid_(list::alloc(1,_oid_(src))))));
    char tmp[4096];
    { CL_INT Result = 0;
      { CL_INT  n = 0;
        char* buf = (char*)(tmp);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) src))) != Kernel.ctrue))
          { GC_LOOP;
            { CL_INT  m = ((CL_INT)Core.read_port->fcall(((CL_INT) src),((CL_INT) buf),((CL_INT) 4096)));
              n= (CL_INT)(((CL_INT)n+(CL_INT)m));
              Core.write_port->fcall(((CL_INT) trgt),((CL_INT) buf),((CL_INT) m));
              }
            GC_UNLOOP;POP_SIGNAL;}
          }
        Result = n;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// read up-to len bytes from src and write them on trgt
// without performing any allocation.
// returns the amount of bytes actually transferred (may be
// lower than len if an eof condition is reached on src)
// The c++ function for: freadwrite(src:port,trgt:port,len:integer) [NEW_ALLOC]
CL_EXPORT CL_INT  freadwrite_port4(PortObject *src,PortObject *trgt,CL_INT len) { 
    
    GC_BIND;
    if (src == trgt)
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Attempt to freadwrite ~S on itself !")),
      _oid_(list::alloc(1,_oid_(src))))));
    char tmp[4096];
    { CL_INT Result = 0;
      { CL_INT  n = 0;
        char* buf = (char*)(tmp);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) src))) != Kernel.ctrue) && 
              ((CL_INT)len > (CL_INT)0)))
          { GC_LOOP;
            { CL_INT  toread = (((CL_INT)len <= (CL_INT)4096) ?
                len :
                4096 );
              CL_INT  m = ((CL_INT)Core.read_port->fcall(((CL_INT) src),((CL_INT) buf),((CL_INT) toread)));
              n= (CL_INT)(((CL_INT)n+(CL_INT)m));
              len= (CL_INT)(((CL_INT)len-(CL_INT)m));
              Core.write_port->fcall(((CL_INT) trgt),((CL_INT) buf),((CL_INT) m));
              }
            GC_UNLOOP;POP_SIGNAL;}
          }
        Result = n;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// skip n bytes from self (dummy read) without performing
// any allocation and return the amount of bytes actually skipped
// (may be lower than len if an eof condition is reached)
// The c++ function for: fskip(self:port,len:integer) [NEW_ALLOC]
CL_EXPORT CL_INT  fskip_port1(PortObject *self,CL_INT len) { 
    
    GC_BIND;
    char tmp[256];
    { CL_INT Result = 0;
      { CL_INT  n = 0;
        char* buf = (char*)(tmp);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) self))) != Kernel.ctrue) && 
              ((CL_INT)len > (CL_INT)0)))
          { GC_LOOP;
            { CL_INT  nread = (((CL_INT)len <= (CL_INT)256) ?
                len :
                256 );
              CL_INT  m = ((CL_INT)Core.read_port->fcall(((CL_INT) self),((CL_INT) buf),((CL_INT) nread)));
              n= (CL_INT)(((CL_INT)n+(CL_INT)m));
              len= (CL_INT)(((CL_INT)len-(CL_INT)m));
              }
            GC_UNLOOP;POP_SIGNAL;}
          }
        Result = n;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//
// The c++ function for: fclose(self:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  fclose_port1(PortObject *self) { 
    
    GC_BIND;
    if (INHERIT(self->isa,Core._device))
     { if (self->closed_ask != CTRUE)
       { { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while ((CLREAD(device,self,filters)->length != 0))
          { GC_LOOP;
            { filter * f = GC_OBJECT(filter,OBJECT(filter,last_list(CLREAD(device,self,filters))));
              fclose_port1(f);
              if ((CLREAD(device,self,filters)->length != 0) && 
                  (last_list(CLREAD(device,self,filters)) == _oid_(f)))
               { if (should_trace_ask_module1(Core.it,1) == CTRUE)
                 mtformat_module1(Core.it,((char*)"failed to close filter ~S \n"),1,list::alloc(1,_oid_(f)));
                else ;}
              }
            GC_UNLOOP;POP_SIGNAL;}
          }
        if (self->closed_ask != CTRUE)
         { _void_(Core.flush_port->fcall(((CL_INT) self)));
          _void_(self->closed_ask = CTRUE);
          _void_(Core.close_port->fcall(((CL_INT) self)));
          }
        }
      if (_oid_(self) == Core.Clib_stdout->value)
       _void_(ClEnv->cout = null_I_void1());
      if (ClEnv->cout == self)
       _void_(ClEnv->cout = OBJECT(PortObject,Core.Clib_stdout->value));
      if (ClEnv->ctrace == self)
       _void_(ClEnv->ctrace = OBJECT(PortObject,Core.Clib_stdout->value));
      }
    else if (INHERIT(self->isa,Core._filter))
     { device * d = GC_OBJECT(device,CLREAD(filter,self,dev));
      if (d == (NULL))
       ;else { if (self->closed_ask != CTRUE)
           { if (_oid_(self) == last_list(d->filters))
             { { ClaireHandler c_handle = ClaireHandler();
                if ERROR_IN 
                { _void_(Core.flush_port->fcall(((CL_INT) self)));
                  ERROR_FREE;}
                else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                { c_handle.catchIt();if (should_trace_ask_module1(Core.it,1) == CTRUE)
                   mtformat_module1(Core.it,((char*)"failed to flush filter ~S - ignore \n"),1,GC_OBJECT(list,list::alloc(1,_oid_(self))));
                  else ;}
                else PREVIOUS_HANDLER;}
              _void_(self->closed_ask = CTRUE);
              _void_(Core.close_port->fcall(((CL_INT) self)));
              rmlast_list(d->filters);
              _void_(CLREAD(filter,self,dev) = NULL);
              if (CLREAD(filter,self,close_target_ask) == CTRUE)
               fclose_port1(GC_OBJECT(PortObject,CLREAD(filter,self,target)));
              }
            }
          if (ClEnv->cout == self)
           _void_(ClEnv->cout = OBJECT(PortObject,Core.Clib_stdout->value));
          if (ClEnv->ctrace == self)
           _void_(ClEnv->ctrace = OBJECT(PortObject,Core.Clib_stdout->value));
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: get_filter(self:port,c:class) [0]
CL_EXPORT PortObject * get_filter_port1(PortObject *self,ClaireClass *c) { 
    { PortObject *Result ;
      { device * d = get_device_port1(self);
        list * fs = d->filters;
        CL_INT  len = fs->length;
        PortObject * p = self;
        { CL_INT  i = 1;
          CL_INT  g0166 = len;
          { CL_INT loop_handle = ClEnv->cHandle;
            while (((CL_INT)i <= (CL_INT)g0166))
            { if (_Z_any1((*(fs))[i],c) == CTRUE)
               { p= (OBJECT(PortObject,(*(fs))[i]));
                { ;ClEnv->cHandle = loop_handle; break;}
                }
              ++i;
              POP_SIGNAL;}
            }
          }
        Result = p;
        }
      POP_SIGNAL; return (Result);}
    }
  


//<sb> GC callback raised when the object is freed
// The c++ function for: prefree!(self:filter) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  prefree_I_filter1(filter *self) { 
    
    GC_BIND;
    if (self->closed_ask != CTRUE)
     { device * d = GC_OBJECT(device,self->dev);
      if (d == (NULL))
       ;else { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while ((d->filters->length != 0))
          { GC_LOOP;
            { filter * f = GC_OBJECT(filter,OBJECT(filter,last_list(d->filters)));
              if (ClEnv->cout == f)
               _void_(ClEnv->cout = OBJECT(PortObject,Core.Clib_stdout->value));
              if (ClEnv->ctrace == f)
               _void_(ClEnv->ctrace = OBJECT(PortObject,Core.Clib_stdout->value));
              _void_(Core.flush_port->fcall(((CL_INT) f)));
              _void_(f->closed_ask = CTRUE);
              _void_(Core.close_port->fcall(((CL_INT) f)));
              rmlast_list(d->filters);
              _void_(f->dev = NULL);
              }
            GC_UNLOOP;POP_SIGNAL;}
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: free!(self:device) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  free_I_port2_Core(device *self) { 
    if (self->closed_ask != CTRUE)
     { if (ClEnv->cout == self)
       _void_(ClEnv->cout = OBJECT(PortObject,Core.Clib_stdout->value));
      if (ClEnv->ctrace == self)
       _void_(ClEnv->ctrace = OBJECT(PortObject,Core.Clib_stdout->value));
      _void_(Core.flush_port->fcall(((CL_INT) self)));
      _void_(self->closed_ask = CTRUE);
      _void_(Core.close_port->fcall(((CL_INT) self)));
      }
    POP_SIGNAL;}
  


// ***************************************************************************
// * part 4: null port                                                       *
// ***************************************************************************
// The c++ function for: null!(_CL_obj:void) [0]
CL_EXPORT null_port * null_I_void1() { 
    POP_SIGNAL; return (OBJECT(null_port,Core.null->value));}
  


//<sb> null port does nothing
// The c++ function for: read_port(self:null_port,buf:char*,len:integer) [0]
CL_EXPORT CL_INT  read_port_null_port1_Core(null_port *self,char*buf,CL_INT len) { 
    POP_SIGNAL; return (0);}
  


// The c++ function for: eof_port?(self:null_port) [0]
CL_EXPORT ClaireBoolean * eof_port_ask_null_port1_Core(null_port *self) { 
    POP_SIGNAL; return (CTRUE);}
  


// The c++ function for: write_port(self:null_port,buf:char*,len:integer) [SAFE_RESULT]
CL_EXPORT CL_INT  write_port_null_port1_Core(null_port *self,char*buf,CL_INT len) { 
    POP_SIGNAL; return (len);}
  


// The c++ function for: flush_port(self:null_port) [0]
CL_EXPORT void  flush_port_null_port1_Core(null_port *self) { 
    ;POP_SIGNAL;}
  


//<sb> keep the singleton opened
// The c++ function for: close_port(self:null_port) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  close_port_null_port1_Core(null_port *self) { 
    _void_(self->closed_ask = CFALSE);
    POP_SIGNAL;}
  


// ***************************************************************************
// * part 4: blob                                                            *
// ***************************************************************************
// When a new blob is instantiated
// it is important to allocate the container chunk first (the container is
// the claire blob object) and only then the data chunk, as such we always
// have a valid container to hold the mallocated data.
//<sb> @doc @xl port
// blob is a port interface for strings, data are stored in a chunk of
// memory allocated outside claire memory.
//<sb> index in data of the next byte to write
//<sb> blobs have a pretty printing that shows the content
// of the blob around the reading index
// The c++ function for: princ(self:blob) [NEW_ALLOC]
CL_EXPORT void  princ_blob1(blob *self) { 
    if (self->write_index == 0)
     princ_string(((char*)"empty blob"));
    else if ((CL_INT)self->write_index < (CL_INT)40)
     { CL_INT  g0167 = (CL_INT )(current_color);
      CL_INT  g0168 = (CL_INT )(current_bold);
      CL_INT  g0169 = g0167;
      CL_INT  g0170 = g0168;
      color(g0169,g0170);
      print_any(_oid_(OWNER(_oid_(self))));
      color(g0167,g0168);
      color(g0167,g0168);
      color_princ_string1(((char*)"["));
      g0167= (CL_INT)((CL_INT )(current_color));
      g0168= (CL_INT)((CL_INT )(current_bold));
      color(g0169,g0170);
      print_any(((OID)self->write_index));
      color(g0167,g0168);
      color(g0167,g0168);
      color_princ_string1(((char*)":`BLACK"));
      g0167= (CL_INT)((CL_INT )(current_color));
      g0168= (CL_INT)((CL_INT )(current_bold));
      color(g0169,g0170);
      if ((CL_INT)self->read_index > (CL_INT)0)
       internal_print_string(self->data, self->read_index);
      color(g0167,g0168);
      color(g0167,g0168);
      color_princ_string1(((char*)"``RED|`BLACK"));
      g0167= (CL_INT)((CL_INT )(current_color));
      g0168= (CL_INT)((CL_INT )(current_bold));
      color(g0169,g0170);
      if ((CL_INT)self->read_index < (CL_INT)self->write_index)
       internal_print_string(self->data + self->read_index, self->write_index - self->read_index);
      color(g0167,g0168);
      color(g0167,g0168);
      color_princ_string1(((char*)"`BLACK]"));
      color(g0169,g0170);
      }
    else if ((CL_INT)self->read_index < (CL_INT)20)
     { CL_INT  g0171 = (CL_INT )(current_color);
      CL_INT  g0172 = (CL_INT )(current_bold);
      CL_INT  g0173 = g0171;
      CL_INT  g0174 = g0172;
      color(g0173,g0174);
      print_any(_oid_(OWNER(_oid_(self))));
      color(g0171,g0172);
      color(g0171,g0172);
      color_princ_string1(((char*)"["));
      g0171= (CL_INT)((CL_INT )(current_color));
      g0172= (CL_INT)((CL_INT )(current_bold));
      color(g0173,g0174);
      print_any(((OID)self->write_index));
      color(g0171,g0172);
      color(g0171,g0172);
      color_princ_string1(((char*)":`BLACK"));
      g0171= (CL_INT)((CL_INT )(current_color));
      g0172= (CL_INT)((CL_INT )(current_bold));
      color(g0173,g0174);
      if ((CL_INT)self->read_index > (CL_INT)0)
       internal_print_string(self->data, self->read_index);
      color(g0171,g0172);
      color(g0171,g0172);
      color_princ_string1(((char*)"``RED|`BLACK"));
      g0171= (CL_INT)((CL_INT )(current_color));
      g0172= (CL_INT)((CL_INT )(current_bold));
      color(g0173,g0174);
      internal_print_string(self->data + self->read_index, 20);
      color(g0171,g0172);
      color(g0171,g0172);
      color_princ_string1(((char*)"`RED...`BLACK]"));
      color(g0173,g0174);
      }
    else if ((CL_INT)self->write_index <= (CL_INT)((CL_INT)self->read_index+(CL_INT)20))
     { CL_INT  g0175 = (CL_INT )(current_color);
      CL_INT  g0176 = (CL_INT )(current_bold);
      CL_INT  g0177 = g0175;
      CL_INT  g0178 = g0176;
      color(g0177,g0178);
      print_any(_oid_(OWNER(_oid_(self))));
      color(g0175,g0176);
      color(g0175,g0176);
      color_princ_string1(((char*)"["));
      g0175= (CL_INT)((CL_INT )(current_color));
      g0176= (CL_INT)((CL_INT )(current_bold));
      color(g0177,g0178);
      print_any(((OID)self->write_index));
      color(g0175,g0176);
      color(g0175,g0176);
      color_princ_string1(((char*)":`RED...`BLACK"));
      g0175= (CL_INT)((CL_INT )(current_color));
      g0176= (CL_INT)((CL_INT )(current_bold));
      color(g0177,g0178);
      if ((CL_INT)self->read_index > (CL_INT)0)
       internal_print_string(self->data + self->read_index - 20, 20);
      color(g0175,g0176);
      color(g0175,g0176);
      color_princ_string1(((char*)"``RED|`BLACK"));
      g0175= (CL_INT)((CL_INT )(current_color));
      g0176= (CL_INT)((CL_INT )(current_bold));
      color(g0177,g0178);
      internal_print_string(self->data + self->read_index, self->write_index - self->read_index);
      color(g0175,g0176);
      color(g0175,g0176);
      color_princ_string1(((char*)"`BLACK]"));
      color(g0177,g0178);
      }
    else { CL_INT  g0179 = (CL_INT )(current_color);
        CL_INT  g0180 = (CL_INT )(current_bold);
        CL_INT  g0181 = g0179;
        CL_INT  g0182 = g0180;
        color(g0181,g0182);
        print_any(_oid_(OWNER(_oid_(self))));
        color(g0179,g0180);
        color(g0179,g0180);
        color_princ_string1(((char*)"["));
        g0179= (CL_INT)((CL_INT )(current_color));
        g0180= (CL_INT)((CL_INT )(current_bold));
        color(g0181,g0182);
        print_any(((OID)self->write_index));
        color(g0179,g0180);
        color(g0179,g0180);
        color_princ_string1(((char*)":`RED...`BLACK"));
        g0179= (CL_INT)((CL_INT )(current_color));
        g0180= (CL_INT)((CL_INT )(current_bold));
        color(g0181,g0182);
        internal_print_string(self->data + self->read_index - 20, 20);
        color(g0179,g0180);
        color(g0179,g0180);
        color_princ_string1(((char*)"``RED|`BLACK"));
        g0179= (CL_INT)((CL_INT )(current_color));
        g0180= (CL_INT)((CL_INT )(current_bold));
        color(g0181,g0182);
        internal_print_string(self->data + self->read_index, 20);
        color(g0179,g0180);
        color(g0179,g0180);
        color_princ_string1(((char*)"`RED...`BLACK]"));
        color(g0181,g0182);
        }
      POP_SIGNAL;}
  


//<sb> ensure that the internal buffer is large enough to
// hold n bytes at the current write index
// The c++ function for: write_attempt(self:blob,n:integer) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  write_attempt_blob1(blob *self,CL_INT n) { 
    if ((CL_INT)remain_for_write_blob1(self) < (CL_INT)n)
     { CL_INT  len_after = ((CL_INT)((CL_INT)self->write_index+(CL_INT)n)+(CL_INT)1);
      CL_INT  new_length = 1024;
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((CL_INT)new_length < (CL_INT)len_after))
        { new_length= (CL_INT)(((CL_INT)new_length*(CL_INT)2));
          POP_SIGNAL;}
        }
      { char* new_data = (char*)(((char*)realloc(self->data, new_length)));
        if ((((ClaireBoolean *) (ClaireBoolean *)((new_data == NULL ? CTRUE : CFALSE)))) == CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"failed to allocate external memory for blob ~S")),
          _oid_(list::alloc(1,_oid_(self))))));
        _void_(self->alloc_length = ((CL_INT)new_length-(CL_INT)1));
        _void_(self->data = new_data);
        }
      }
    POP_SIGNAL;}
  


// The c++ function for: unget_port(self:blob,buf:char*,len:integer) [SLOT_UPDATE]
CL_EXPORT void  unget_port_blob1_Core(blob *self,char*buf,CL_INT len) { 
    { CL_INT  room = self->read_index;
      if ((CL_INT)len <= (CL_INT)room)
       _void_(self->read_index = ((CL_INT)self->read_index-(CL_INT)len));
      else { CL_INT  grow = ((CL_INT)len-(CL_INT)room);
          CL_INT  remain = remain_to_read_blob1(self);
          write_attempt_blob1(self,grow);
          if ((CL_INT)remain > (CL_INT)0)
           memmove(self->data + self->read_index + grow, self->data + self->read_index, remain);
          _void_(self->write_index = ((CL_INT)self->write_index+(CL_INT)grow));
          _void_(self->read_index = 0);
          }
        memcpy(self->data + self->read_index, buf, len);
      }
    POP_SIGNAL;}
  


//<sb> @doc @xl port
// allocate an empty blob
// The c++ function for: blob!(_CL_obj:void) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT blob * blob_I_void1() { 
    
    GC_BIND;
    { blob *Result ;
      { blob * b;
        { { blob * _CL_obj = ((blob *) GC_OBJECT(blob,new_object_class(Core._blob)));
            b = _CL_obj;
            }
          GC_OBJECT(blob,b);}
        char* buf = (char*)(((char*)malloc(8192)));
        if ((((ClaireBoolean *) (ClaireBoolean *)((buf == NULL ? CTRUE : CFALSE)))) == CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"failed to allocate external memory in blob! @ void")),
          _oid_(Kernel.nil))));
        _void_(b->data = buf);
        _void_(b->alloc_length = 8191);
        Result = b;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// allocate a blob that is a copy of the given blob
// The c++ function for: blob!(p:blob) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT blob * blob_I_blob1(blob *p) { 
    
    GC_BIND;
    { blob *Result ;
      { blob * b;
        { { blob * _CL_obj = ((blob *) GC_OBJECT(blob,new_object_class(Core._blob)));
            b = _CL_obj;
            }
          GC_OBJECT(blob,b);}
        char* buf = (char*)(((char*)malloc(p->alloc_length+1)));
        if ((((ClaireBoolean *) (ClaireBoolean *)((buf == NULL ? CTRUE : CFALSE)))) == CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"failed to allocate external memory for blob!(~S)")),
          _oid_(list::alloc(1,_oid_(p))))));
        memcpy(buf, p->data, p->write_index);
        _void_(b->data = buf);
        _void_(b->firstc = p->firstc);
        _void_(b->read_index = p->read_index);
        _void_(b->write_index = p->write_index);
        _void_(b->alloc_length = p->alloc_length);
        Result = b;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// allocate a blob that is filled with all data that can
// be read on p
// The c++ function for: blob!(p:port) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT blob * blob_I_port1(PortObject *p) { 
    
    GC_BIND;
    { blob *Result ;
      { blob * b = GC_OBJECT(blob,blob_I_void1());
        freadwrite_port3(p,b);
        Result = b;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// allocate a blob with the string self has the initial data
// The c++ function for: blob!(self:string) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT blob * blob_I_string1(char *self) { 
    
    GC_BIND;
    { blob *Result ;
      { blob * b;
        { { blob * _CL_obj = ((blob *) GC_OBJECT(blob,new_object_class(Core._blob)));
            b = _CL_obj;
            }
          GC_OBJECT(blob,b);}
        CL_INT  len = LENGTH_STRING(self);
        CL_INT  alloclen = ((len == 0) ?
          1 :
          len );
        char* buf = (char*)(((char*)malloc(alloclen+1)));
        if ((((ClaireBoolean *) (ClaireBoolean *)((buf == NULL ? CTRUE : CFALSE)))) == CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"failed to allocate external memory for blob!(~S)")),
          _oid_(list::alloc(1,_string_(self))))));
        if ((CL_INT)len > (CL_INT)0)
         memcpy(buf, self, len);
        _void_(b->data = buf);
        _void_(b->write_index = len);
        _void_(b->alloc_length = alloclen);
        Result = b;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// allocate a blob that can receive at least n bytes
// (i.e. writing more than n bytes may cause further allocation)
// The c++ function for: blob!(n:integer) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT blob * blob_I_integer1(CL_INT n) { 
    
    GC_BIND;
    { blob *Result ;
      { blob * b;
        { { blob * _CL_obj = ((blob *) GC_OBJECT(blob,new_object_class(Core._blob)));
            b = _CL_obj;
            }
          GC_OBJECT(blob,b);}
        char* buf = (char*)(((char*)malloc(n+1)));
        if ((((ClaireBoolean *) (ClaireBoolean *)((buf == NULL ? CTRUE : CFALSE)))) == CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"failed to allocate external memory for blob!(~S)")),
          _oid_(list::alloc(1,((OID)n))))));
        _void_(b->data = buf);
        _void_(b->write_index = 0);
        _void_(b->alloc_length = n);
        Result = b;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: clob!(_CL_obj:void) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT clob * clob_I_void1() { 
    
    GC_BIND;
    { clob *Result ;
      { ClaireObject *V_CC ;
        { blob * b = GC_OBJECT(blob,blob_I_void1());
          b->isa = Core._clob;
          V_CC = (clob *)(clob *)(b);
          }
        Result= (clob *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: clob!(self:string) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT clob * clob_I_string1(char *self) { 
    
    GC_BIND;
    { clob *Result ;
      { ClaireObject *V_CC ;
        { blob * b = GC_OBJECT(blob,blob_I_string1(self));
          b->isa = Core._clob;
          V_CC = (clob *)(clob *)(b);
          }
        Result= (clob *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: clob!(self:port) [NEW_ALLOC]
CL_EXPORT clob * clob_I_port1(PortObject *self) { 
    
    GC_BIND;
    { clob *Result ;
      { ClaireObject *V_CC ;
        { blob * b = GC_OBJECT(blob,OBJECT(blob,(*Core.blob_I)(_oid_(self))));
          b->isa = Core._clob;
          V_CC = (clob *)(clob *)(b);
          }
        Result= (clob *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: clob!(n:integer) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT clob * clob_I_integer1(CL_INT n) { 
    
    GC_BIND;
    { clob *Result ;
      { ClaireObject *V_CC ;
        { blob * b = GC_OBJECT(blob,blob_I_integer1(n));
          b->isa = Core._clob;
          V_CC = (clob *)(clob *)(b);
          }
        Result= (clob *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// compatibility with <ycs>, one should use blob! instead.
//<sb> return the amount of bytes remaining for writing or reading
// The c++ function for: remain_for_write(self:blob) [RETURN_ARG]
CL_EXPORT CL_INT  remain_for_write_blob1(blob *self) { 
    POP_SIGNAL; return (((CL_INT)self->alloc_length-(CL_INT)self->write_index));}
  


// The c++ function for: remain_to_read(self:blob) [RETURN_ARG]
CL_EXPORT CL_INT  remain_to_read_blob1(blob *self) { 
    POP_SIGNAL; return (((CL_INT)self->write_index-(CL_INT)self->read_index));}
  


// The c++ function for: eof_port?(self:blob) [0]
CL_EXPORT ClaireBoolean * eof_port_ask_blob1_Core(blob *self) { 
    POP_SIGNAL; return (((ClaireBoolean *) (ClaireBoolean *)((self->read_index == self->write_index ? CTRUE : CFALSE))));}
  


// The c++ function for: read_port(self:blob,buf:char*,len:integer) [SLOT_UPDATE]
CL_EXPORT CL_INT  read_port_blob1_Core(blob *self,char*buf,CL_INT len) { 
    { CL_INT Result = 0;
      { CL_INT  avail = remain_to_read_blob1(self);
        if ((CL_INT)len < (CL_INT)avail)
         avail= (CL_INT)(len);
        memcpy(buf, self->data + self->read_index, avail);
        _void_(self->read_index = ((CL_INT)self->read_index+(CL_INT)avail));
        Result = avail;
        }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: write_port(self:blob,buf:char*,len:integer) [SLOT_UPDATE+SAFE_RESULT]
CL_EXPORT CL_INT  write_port_blob1_Core(blob *self,char*buf,CL_INT len) { 
    write_attempt_blob1(self,len);
    memcpy(self->data + self->write_index, buf, len);
    _void_(self->write_index = ((CL_INT)self->write_index+(CL_INT)len));
    POP_SIGNAL; return (len);}
  


// The c++ function for: close_port(self:blob) [0]
CL_EXPORT void  close_port_blob1_Core(blob *self) { 
    {if (self->data) {::free(self->data);self->data = NULL;}};
    POP_SIGNAL;}
  


//<sb> @doc @xl port
// string! converts a blob in a string
// The c++ function for: string!(self:blob) [NEW_ALLOC]
CL_EXPORT char * string_I_blob1(blob *self) { 
    
    GC_BIND;
    { char *Result ;
      { CL_INT  len = self->write_index;
        char * s = GC_STRING(make_string_integer1(len));
        memcpy(s, self->data, len);
        Result = s;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// buffer access on the blob
// The c++ function for: nth(self:blob,n:integer) [0]
CL_EXPORT ClaireChar * nth_blob1(blob *self,CL_INT n) { 
    { ClaireChar *Result ;
      { ClaireObject *V_CC ;
        { n= (CL_INT)((((CL_INT)1 <= (CL_INT)n) ?
            n :
            1 ));
          n= (CL_INT)((((CL_INT)n <= (CL_INT)self->alloc_length) ?
            n :
            self->alloc_length ));
          if (n == 0)
           V_CC = OBJECT(ClaireChar,Core._eof->value);
          else V_CC = (ClaireChar *)(ClaireChar *)(_char_(self->data[n-1]));
            }
        Result= (ClaireChar *) V_CC;}
      POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// buffer access on the blob
// The c++ function for: nth=(self:blob,n:integer,c:char) [0]
CL_EXPORT void  nth_equal_blob1(blob *self,CL_INT n,ClaireChar *c) { 
    n= (CL_INT)((((CL_INT)1 <= (CL_INT)n) ?
      n :
      1 ));
    n= (CL_INT)((((CL_INT)n <= (CL_INT)self->alloc_length) ?
      n :
      self->alloc_length ));
    if (n == 0)
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"nth=@blob: the blob ~S is empty")),
      _oid_(list::alloc(1,_oid_(self))))));
    self->data[n-1] = c->ascii;
    POP_SIGNAL;}
  


//<sb> @doc @xl port
// return the total amount of bytes contained in the blob,
// string! @ blob will return a string with that length
// The c++ function for: length(self:blob) [RETURN_ARG]
CL_EXPORT CL_INT  length_blob1(blob *self) { 
    POP_SIGNAL; return (self->write_index);}
  


//<sb> @doc @xl port
// sets the amount of bytes contained in the blob, when 0 is given
// a new chunk is reallocated for the internal data
// The c++ function for: set_length(self:blob,n:integer) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  set_length_blob1(blob *self,CL_INT n) { 
    if ((CL_INT)n <= (CL_INT)0)
     { char* new_data = (char*)(((char*)realloc(self->data, 8192)));
      if ((((ClaireBoolean *) (ClaireBoolean *)((new_data == NULL ? CTRUE : CFALSE)))) == CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"failed to allocate external memory in set_length(~S, ~S)")),
        _oid_(list::alloc(2,_oid_(self),((OID)n))))));
      _void_(self->data = new_data);
      _void_(self->alloc_length = 8191);
      _void_(self->read_index = 0);
      _void_(self->write_index = 0);
      }
    else { CL_INT  maxn = self->alloc_length;
        if ((CL_INT)n > (CL_INT)maxn)
         write_attempt_blob1(self,((CL_INT)n-(CL_INT)maxn));
        else { _void_(self->write_index = (((CL_INT)self->write_index <= (CL_INT)n) ?
              self->write_index :
              n ));
            _void_(self->read_index = (((CL_INT)self->read_index <= (CL_INT)n) ?
              self->read_index :
              n ));
            }
          }
      POP_SIGNAL;}
  


//<sb> @doc @xl port
// returns a substring of the internal data considered, i and j are
// 1 base indexed
// The c++ function for: substring(self:blob,i:integer,j:integer) [NEW_ALLOC]
CL_EXPORT char * substring_blob1(blob *self,CL_INT i,CL_INT j) { 
    
    GC_BIND;
    i= (CL_INT)((((CL_INT)1 <= (CL_INT)i) ?
      i :
      1 ));
    j= (CL_INT)((((CL_INT)((CL_INT)i-(CL_INT)1) <= (CL_INT)j) ?
      j :
      ((CL_INT)i-(CL_INT)1) ));
    i= (CL_INT)((((CL_INT)i <= (CL_INT)self->alloc_length) ?
      i :
      self->alloc_length ));
    j= (CL_INT)((((CL_INT)j <= (CL_INT)self->alloc_length) ?
      j :
      self->alloc_length ));
    { char *Result ;
      { CL_INT  len = ((CL_INT)((CL_INT)j-(CL_INT)i)+(CL_INT)1);
        char * s = GC_STRING(make_string_integer1(len));
        memcpy(s, self->data + i - 1, len);
        Result = s;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// returns the current reading index 
// The c++ function for: get_index(self:blob) [RETURN_ARG]
CL_EXPORT CL_INT  get_index_blob1(blob *self) { 
    POP_SIGNAL; return (self->read_index);}
  


//<sb> @doc @xl port
// sets the current reading index 
// The c++ function for: set_index(self:blob,n:integer) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  set_index_blob1(blob *self,CL_INT n) { 
    { CL_INT  i = (((CL_INT)self->write_index <= (CL_INT)n) ?
        self->write_index :
        n );
      _void_(self->read_index = (((CL_INT)i <= (CL_INT)0) ?
        0 :
        i ));
      }
    POP_SIGNAL;}
  


// ***************************************************************************
// * part 5: reverser                                                        *
// ***************************************************************************
// The c++ function for: reverser!(self:blob) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT Core_reverser * reverser_I_blob1(blob *self) { 
    
    GC_BIND;
    { Core_reverser *Result ;
      { filter *V_CC ;
        { if (get_top_most_port1(self) != self)
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Cannot create a reverser on ~S that is already filtered")),
            _oid_(list::alloc(1,_oid_(self))))));
          { Core_reverser * g0189UU;
            { Core_reverser * _CL_obj = ((Core_reverser *) GC_OBJECT(Core_reverser,new_object_class(Core._reverser)));
              _void_(_CL_obj->left_to_read = self->write_index);
              g0189UU = _CL_obj;
              }
            V_CC = (Core_reverser *)filter_I_filter1(g0189UU,self);
            }
          }
        Result= (Core_reverser *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: eof_port?(self:reverser) [0]
CL_EXPORT ClaireBoolean * eof_port_ask_reverser1_Core(Core_reverser *self) { 
    POP_SIGNAL; return (equal(((OID)self->left_to_read),((OID)0)));}
  


// The c++ function for: read_port(self:reverser,buf:char*,len:integer) [SLOT_UPDATE]
CL_EXPORT CL_INT  read_port_reverser1_Core(Core_reverser *self,char*buf,CL_INT len) { 
    { CL_INT Result = 0;
      { blob * bl = ((blob *) self->target);
        char* d = bl->data;
        CL_INT  n = 0;
        CL_INT  left_after = ((CL_INT)self->left_to_read-(CL_INT)len);
        if ((CL_INT)self->left_to_read > (CL_INT)bl->write_index)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"dangerous read_port @ reverser since the blob has changed !")),
          _oid_(Kernel.nil))));
        left_after= (CL_INT)((((CL_INT)0 <= (CL_INT)left_after) ?
          left_after :
          0 ));
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)self->left_to_read > (CL_INT)left_after))
          { *buf = d[self->left_to_read - 1];
						buf++;
            ++n;
            _void_(self->left_to_read = ((CL_INT)self->left_to_read-(CL_INT)1));
            POP_SIGNAL;}
          }
        Result = n;
        }
      POP_SIGNAL; return (Result);}
    }
  


// ***************************************************************************
// * part 5: buffer                                                          *
// ***************************************************************************
//<sb> @doc @xl port
// a buffer filter performs a single read/write call on its target
// for each data raw of a given size (buffer_length). It comes as
// replacement of the C FILE* buffering capability.
//<sb> @doc @xl port
// buffer! creates a buffer filter on the port self with an internal
// buffer bufsize bytes long.
// The c++ function for: buffer!(self:port,bufsize:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT buffer * buffer_I_port1(PortObject *self,CL_INT bufsize) { 
    
    GC_BIND;
    { buffer *Result ;
      { filter *V_CC ;
        { buffer * g0191UU;
          { buffer * _CL_obj = ((buffer *) GC_OBJECT(buffer,new_object_class(Core._buffer)));
            _void_(_CL_obj->buffer_length = bufsize);
            g0191UU = _CL_obj;
            }
          V_CC = (buffer *)filter_I_filter1(g0191UU,self);
          }
        Result= (buffer *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: buffer!(self:buffer,p:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT buffer * buffer_I_buffer1(buffer *self,PortObject *p) { 
    
    GC_BIND;
    { buffer *Result ;
      { buffer * f;
        { { filter *V_CC ;
            { buffer * g0192UU;
              { buffer * _CL_obj = ((buffer *) GC_OBJECT(buffer,new_object_class(Core._buffer)));
                _void_(_CL_obj->buffer_length = self->buffer_length);
                _void_(_CL_obj->close_target_ask = self->close_target_ask);
                _void_(_CL_obj->firstc = self->firstc);
                g0192UU = _CL_obj;
                }
              V_CC = (buffer *)filter_I_filter1(g0192UU,p);
              }
            f= (buffer *) V_CC;}
          GC_OBJECT(buffer,f);}
        if (((self->pending_r == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         _void_(f->pending_r = blob_I_blob1(GC_OBJECT(blob,self->pending_r)));
        if (((self->pending_w == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         _void_(f->pending_w = blob_I_blob1(GC_OBJECT(blob,self->pending_w)));
        Result = f;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: princ(self:buffer) [NEW_ALLOC]
CL_EXPORT void  princ_buffer1(buffer *self) { 
    
    GC_BIND;
    princ_string(((char*)"buffer["));
    if (((self->pending_r == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     { princ_string(((char*)"R<"));
      princ_blob1(self->pending_r);
      princ_string(((char*)">"));
      }
    if ((((self->pending_r == (NULL)) ? CTRUE : CFALSE) != CTRUE) && 
        (((self->pending_w == (NULL)) ? CTRUE : CFALSE) != CTRUE))
     princ_string(((char*)" "));
    if (((self->pending_w == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     { princ_string(((char*)"W<"));
      princ_blob1(self->pending_w);
      princ_string(((char*)">"));
      }
    princ_string(((char*)"]"));
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> read
// The c++ function for: reset_buffer(self:port) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  reset_buffer_port1(PortObject *self) { 
    { PortObject * p = get_filter_port1(self,Core._buffer);
      if (INHERIT(p->isa,Core._buffer))
       { if (((CLREAD(buffer,p,pending_r) == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         { _void_(CLREAD(buffer,p,pending_r)->write_index = 0);
          _void_(CLREAD(buffer,p,pending_r)->read_index = 0);
          }
        }
      else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~S is not connected to a buffer")),
          _oid_(list::alloc(1,_oid_(self))))));
        }
    POP_SIGNAL;}
  


//<sb> the buffer reads its target by chunks of buffer_length bytes
// Note wcl: in order to have a toplevel compatible with wcl
// we have to connect the input to a buffer (wcl reader uses unget),
// the length of such a buffer is 1 such it always reads on the terminal
// input a single char at a time
// The c++ function for: fill_read_buffer(self:buffer) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  fill_read_buffer_buffer1(buffer *self) { 
    
    GC_BIND;
    if (self->pending_r == (NULL))
     _void_(self->pending_r = blob_I_integer1(self->buffer_length));
    { blob * pend = GC_OBJECT(blob,self->pending_r);
      _void_(pend->read_index = 0);
      _void_(pend->write_index = ((CL_INT)Core.read_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))),((CL_INT) (char*)(pend->data)),((CL_INT) self->buffer_length))));
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: eof_port?(self:buffer) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * eof_port_ask_buffer1_Core(buffer *self) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = ((((self->pending_r == (NULL)) ? CTRUE : CFALSE) != CTRUE) ? ((remain_to_read_blob1(self->pending_r) == 0) ? (((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))))))) == CTRUE) ? CTRUE: CFALSE): CFALSE): CFALSE);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: read_port(self:buffer,buf:char*,len:integer) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT CL_INT  read_port_buffer1_Core(buffer *self,char*buf,CL_INT len) { 
    if (self->pending_r == (NULL))
     _void_(self->pending_r = blob_I_integer1(self->buffer_length));
    { CL_INT Result = 0;
      { blob * pend = ((blob *) (blob *)(self->pending_r));
        CL_INT  disp = ((CL_INT)pend->write_index-(CL_INT)pend->read_index);
        CL_INT  n = 0;
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)len > (CL_INT)0))
          { { CL_INT  m = (((CL_INT)disp <= (CL_INT)len) ?
                disp :
                len );
              if ((CL_INT)m > (CL_INT)0)
               { memcpy(buf, pend->data + pend->read_index, m);
                len= (CL_INT)(((CL_INT)len-(CL_INT)m));
                n= (CL_INT)(((CL_INT)n+(CL_INT)m));
                _void_(pend->read_index = ((CL_INT)pend->read_index+(CL_INT)m));
                buf= ((buf + m));
                }
              disp= (CL_INT)(((CL_INT)pend->write_index-(CL_INT)pend->read_index));
              if (disp == 0)
               { if ((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) (PortObject *)(self->target)))))) == CTRUE)
                 { ;ClEnv->cHandle = loop_handle; break;}
                fill_read_buffer_buffer1(self);
                disp= (CL_INT)(remain_to_read_blob1(pend));
                }
              }
            POP_SIGNAL;}
          }
        Result = n;
        }
      POP_SIGNAL; return (Result);}
    }
  


//<sb> this is our unget interface for stream. the given data
// is copied back in the buffer and the read index is moved
// such the next data to read is s
// Note: the message is not transmitted to the target, a buffer
// always accumulate ungotten data and then return
// The c++ function for: unget_port(self:buffer,buf:char*,len:integer) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT void  unget_port_buffer1_Core(buffer *self,char*buf,CL_INT len) { 
    
    GC_BIND;
    if (self->pending_r == (NULL))
     { _void_(self->pending_r = blob_I_integer1(self->buffer_length));
      Core.write_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->pending_r)))),((CL_INT) buf),((CL_INT) len));
      }
    else _void_(Core.unget_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->pending_r)))),((CL_INT) buf),((CL_INT) len)));
      GC_UNBIND; POP_SIGNAL;}
  


//<sb> write
// The c++ function for: flush_port(self:buffer) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  flush_port_buffer1_Core(buffer *self) { 
    
    GC_BIND;
    if (((self->pending_w == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     { blob * pend = GC_OBJECT(blob,self->pending_w);
      if ((CL_INT)pend->write_index > (CL_INT)0)
       Core.write_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))),((CL_INT) (char*)(pend->data)),((CL_INT) pend->write_index));
      _void_(pend->write_index = 0);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: write_port(self:buffer,buf:char*,len:integer) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT CL_INT  write_port_buffer1_Core(buffer *self,char*buf,CL_INT len) { 
    
    GC_BIND;
    if (self->pending_w == (NULL))
     _void_(self->pending_w = blob_I_integer1(self->buffer_length));
    { CL_INT Result = 0;
      { blob * pend = ((blob *) (blob *)(self->pending_w));
        CL_INT  blen = self->buffer_length;
        CL_INT  disp = ((CL_INT)blen-(CL_INT)pend->write_index);
        CL_INT  n = 0;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)len > (CL_INT)0))
          { GC_LOOP;
            { CL_INT  m = (((CL_INT)disp <= (CL_INT)len) ?
                disp :
                len );
              if ((CL_INT)m > (CL_INT)0)
               { memcpy(pend->data + pend->write_index, buf, m);
                len= (CL_INT)(((CL_INT)len-(CL_INT)m));
                n= (CL_INT)(((CL_INT)n+(CL_INT)m));
                _void_(pend->write_index = ((CL_INT)pend->write_index+(CL_INT)m));
                buf= ((buf + m));
                }
              disp= (CL_INT)(((CL_INT)blen-(CL_INT)pend->write_index));
              if (disp == 0)
               { Core.write_port->fcall(((CL_INT) (PortObject *)(self->target)),((CL_INT) (char*)(pend->data)),((CL_INT) blen));
                _void_(pend->write_index = 0);
                disp= (CL_INT)(blen);
                }
              }
            GC_UNLOOP;POP_SIGNAL;}
          }
        Result = n;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: close_port(self:buffer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  close_port_buffer1_Core(buffer *self) { 
    
    GC_BIND;
    if (((self->pending_r == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     fclose_port1(GC_OBJECT(blob,self->pending_r));
    if (((self->pending_w == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     fclose_port1(GC_OBJECT(blob,self->pending_w));
    GC_UNBIND; POP_SIGNAL;}
  


// ***************************************************************************
// * part 6: line_buffer                                                     *
// ***************************************************************************
//<sb> @doc @xl port
// line_buffer is a write filter that collects written data
// until a new line character. each line is flushed with a single
// write on the target port. It is mainly used for terminal output
// such to prevent line overlap when multiple process share the same
// terminal output or when a trace file is shared by multiple process.
//<sb> a pending line
//<sb> @doc @xl port
// line_buffer! creates a new line_buffer filter on the port self.
// The c++ function for: line_buffer!(self:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT line_buffer * line_buffer_I_port1(PortObject *self) { 
    
    GC_BIND;
    { line_buffer *Result ;
      { line_buffer * lb;
        { { filter *V_CC ;
            { line_buffer * g0195UU;
              { line_buffer * _CL_obj = ((line_buffer *) GC_OBJECT(line_buffer,new_object_class(Core._line_buffer)));
                g0195UU = _CL_obj;
                }
              V_CC = (line_buffer *)filter_I_filter1(g0195UU,self);
              }
            lb= (line_buffer *) V_CC;}
          GC_OBJECT(line_buffer,lb);}
        _void_(lb->pending = blob_I_void1());
        Result = lb;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: flush_port(self:line_buffer) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  flush_port_line_buffer1_Core(line_buffer *self) { 
    
    GC_BIND;
    { blob * pend = GC_OBJECT(blob,self->pending);
      CL_INT  len = remain_to_read_blob1(pend);
      if ((CL_INT)len > (CL_INT)0)
       { Core.write_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))),((CL_INT) (char*)(pend->data)),((CL_INT) len));
        _void_(pend->read_index = 0);
        _void_(pend->write_index = 0);
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: close_port(self:line_buffer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  close_port_line_buffer1_Core(line_buffer *self) { 
    
    GC_BIND;
    fclose_port1(GC_OBJECT(blob,self->pending));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: write_port(self:line_buffer,buf:char*,len:integer) [NEW_ALLOC+SAFE_RESULT]
CL_EXPORT CL_INT  write_port_line_buffer1_Core(line_buffer *self,char*buf,CL_INT len) { 
    
    GC_BIND;
    { CL_INT Result = 0;
      { blob * pend = self->pending;
        ClaireBoolean * nl = CFALSE;
        CL_INT  n = 0;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)n < (CL_INT)len))
          { GC_LOOP;
            { CL_INT  n0 = n;
              while (1) {if (buf[n] == '\n') nl = CTRUE;
									if (n + 1 == len) break;
									n++;};
              Core.write_port->fcall(((CL_INT) pend),((CL_INT) (buf + n0)),((CL_INT) ((CL_INT)((CL_INT)n-(CL_INT)n0)+(CL_INT)1)));
              if (nl == CTRUE)
               { _void_(Core.flush_port->fcall(((CL_INT) self)));
                nl= (CFALSE);
                }
              ++n;
              }
            GC_UNLOOP;POP_SIGNAL;}
          }
        Result = len;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// ***************************************************************************
// * part 7: byte_counter                                                    *
// ***************************************************************************
//<sb> @doc @xl port
// byte_counter is a pure filter that count the number of bytes
// transfered in both directions
// The c++ function for: byte_counter!(self:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT byte_counter * byte_counter_I_port1(PortObject *self) { 
    
    GC_BIND;
    { byte_counter *Result ;
      { filter *V_CC ;
        { byte_counter * g0196UU;
          { byte_counter * _CL_obj = ((byte_counter *) GC_OBJECT(byte_counter,new_object_class(Core._byte_counter)));
            g0196UU = _CL_obj;
            }
          V_CC = (byte_counter *)filter_I_filter1(g0196UU,self);
          }
        Result= (byte_counter *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: byte_counter!(self:byte_counter,p:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT byte_counter * byte_counter_I_byte_counter1(byte_counter *self,PortObject *p) { 
    
    GC_BIND;
    { byte_counter *Result ;
      { filter *V_CC ;
        { byte_counter * g0197UU;
          { byte_counter * _CL_obj = ((byte_counter *) GC_OBJECT(byte_counter,new_object_class(Core._byte_counter)));
            _void_(_CL_obj->close_target_ask = self->close_target_ask);
            _void_(_CL_obj->firstc = self->firstc);
            _void_(_CL_obj->written_bytes = self->written_bytes);
            _void_(_CL_obj->read_bytes = self->read_bytes);
            g0197UU = _CL_obj;
            }
          V_CC = (byte_counter *)filter_I_filter1(g0197UU,p);
          }
        Result= (byte_counter *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: write_port(self:byte_counter,buf:char*,len:integer) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT CL_INT  write_port_byte_counter1_Core(byte_counter *self,char*buf,CL_INT len) { 
    
    GC_BIND;
    { CL_INT Result = 0;
      { CL_INT  n = ((CL_INT)Core.write_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))),((CL_INT) buf),((CL_INT) len)));
        _void_(self->written_bytes = ((CL_INT)self->written_bytes+(CL_INT)n));
        Result = n;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: read_port(self:byte_counter,buf:char*,len:integer) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT CL_INT  read_port_byte_counter1_Core(byte_counter *self,char*buf,CL_INT len) { 
    
    GC_BIND;
    { CL_INT Result = 0;
      { CL_INT  n = ((CL_INT)Core.read_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))),((CL_INT) buf),((CL_INT) len)));
        _void_(self->read_bytes = ((CL_INT)self->read_bytes+(CL_INT)n));
        Result = n;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: eof_port?(self:byte_counter) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT ClaireBoolean * eof_port_ask_byte_counter1_Core(byte_counter *self) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))))));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// ***************************************************************************
// * part 8: line_counter                                                    *
// ***************************************************************************
//<sb> @doc @xl port
// line_counter is a pure filter that count the number of lines
// transfered in both directions
// The c++ function for: princ(self:line_counter) [NEW_ALLOC]
CL_EXPORT void  princ_line_counter1(line_counter *self) { 
    if ((CL_INT)self->written_lines > (CL_INT)0)
     { princ_string(((char*)"wrote "));
      print_any(((OID)self->written_lines));
      princ_string(((char*)" line(s)"));
      }
    if ((CL_INT)self->read_lines > (CL_INT)0)
     { princ_string(((char*)"read "));
      print_any(((OID)self->read_lines));
      princ_string(((char*)" line(s)"));
      }
    POP_SIGNAL;}
  


// The c++ function for: line_counter!(self:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT line_counter * line_counter_I_port1(PortObject *self) { 
    
    GC_BIND;
    { line_counter *Result ;
      { filter *V_CC ;
        { line_counter * g0200UU;
          { line_counter * _CL_obj = ((line_counter *) GC_OBJECT(line_counter,new_object_class(Core._line_counter)));
            g0200UU = _CL_obj;
            }
          V_CC = (line_counter *)filter_I_filter1(g0200UU,self);
          }
        Result= (line_counter *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: line_counter!(self:line_counter,p:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT line_counter * line_counter_I_line_counter1(line_counter *self,PortObject *p) { 
    
    GC_BIND;
    { line_counter *Result ;
      { filter *V_CC ;
        { line_counter * g0201UU;
          { line_counter * _CL_obj = ((line_counter *) GC_OBJECT(line_counter,new_object_class(Core._line_counter)));
            _void_(_CL_obj->close_target_ask = self->close_target_ask);
            _void_(_CL_obj->firstc = self->firstc);
            _void_(_CL_obj->written_lines = self->written_lines);
            _void_(_CL_obj->read_lines = self->read_lines);
            g0201UU = _CL_obj;
            }
          V_CC = (line_counter *)filter_I_filter1(g0201UU,p);
          }
        Result= (line_counter *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: write_port(self:line_counter,buf:char*,len:integer) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT CL_INT  write_port_line_counter1_Core(line_counter *self,char*buf,CL_INT len) { 
    
    GC_BIND;
    { CL_INT Result = 0;
      { CL_INT  n = ((CL_INT)Core.write_port->fcall(((CL_INT) (PortObject *)(self->target)),((CL_INT) buf),((CL_INT) len)));
        CL_INT  slashn = 0;
        CL_INT  i = 0;
        while (i < n) {if (buf[i++] == '\n') slashn++;};
        _void_(self->written_lines = ((CL_INT)self->written_lines+(CL_INT)slashn));
        Result = n;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: read_port(self:line_counter,buf:char*,len:integer) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT CL_INT  read_port_line_counter1_Core(line_counter *self,char*buf,CL_INT len) { 
    
    GC_BIND;
    { CL_INT Result = 0;
      { CL_INT  n = ((CL_INT)Core.read_port->fcall(((CL_INT) (PortObject *)(self->target)),((CL_INT) buf),((CL_INT) len)));
        CL_INT  slashn = 0;
        CL_INT  i = 0;
        while (i < n) {if (buf[i++] == '\n') slashn++;};
        if (slashn == 0)
         _void_(self->line_offset = ((CL_INT)self->line_offset+(CL_INT)len));
        else { CL_INT  o = 0;
            _void_(self->prev_line_offset = self->line_offset);
            len--; while (len) {if (buf[len] == '\n') break; len--; o++;};
            _void_(self->line_offset = o);
            }
          _void_(self->read_lines = ((CL_INT)self->read_lines+(CL_INT)slashn));
        Result = n;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: unget_port(self:line_counter,buf:char*,len:integer) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT void  unget_port_line_counter1_Core(line_counter *self,char*buf,CL_INT len) { 
    
    GC_BIND;
    { CL_INT  i = 0;
      CL_INT  slashn = 0;
      while (i < len) {if (buf[i++] == '\n') slashn++;};
      if (slashn == 0)
       _void_(self->line_offset = ((CL_INT)self->line_offset-(CL_INT)len));
      else _void_(self->line_offset = self->prev_line_offset);
        _void_(self->read_lines = ((CL_INT)self->read_lines-(CL_INT)slashn));
      _void_(Core.unget_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))),((CL_INT) buf),((CL_INT) len)));
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: eof_port?(self:line_counter) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT ClaireBoolean * eof_port_ask_line_counter1_Core(line_counter *self) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))))));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// ***************************************************************************
// * part 9: descriptor                                                      *
// ***************************************************************************
//<sb> @doc @xl port
// UNIX file descriptor wrapping. we do not use C stream capabilities
// (FILE*) but the descriptor itself, which make the API relying on system
// calls read(2) and write(2), stream interface is provided by filters (buffer)
//<sb> wan't write error on closed descriptors
// The c++ function for: princ(self:descriptor) [NEW_ALLOC]
CL_EXPORT void  princ_descriptor1(descriptor *self) { 
    print_any(_oid_(OWNER(_oid_(self))));
    princ_string(((char*)"("));
    print_any(((OID)self->fd));
    princ_string(((char*)")"));
    POP_SIGNAL;}
  


// The c++ function for: close_port(self:descriptor) [0]
CL_EXPORT void  close_port_descriptor1_Core(descriptor *self) { 
    if (_oid_(self) == Core.Clib_stdout->value)
     if (LOGO) ::write(1, "bye...\n", 7);
    if (self->fd != -1) ::close(self->fd);
    POP_SIGNAL;}
  


// The c++ function for: eof_port?(self:descriptor) [RETURN_ARG]
CL_EXPORT ClaireBoolean * eof_port_ask_descriptor1_Core(descriptor *self) { 
    POP_SIGNAL; return (self->eof_reached_ask);}
  


// The c++ function for: read_port(self:descriptor,buf:char*,len:integer) [SLOT_UPDATE]
CL_EXPORT CL_INT  read_port_descriptor1_Core(descriptor *self,char*buf,CL_INT len) { 
    { CL_INT Result = 0;
      { CL_INT  r = 0;
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)r < (CL_INT)len))
          { { CL_INT  n = (CL_INT )(::read(self->fd, buf + r, len - r));
              if (n == 0)
               { _void_(self->eof_reached_ask = CTRUE);
                { ;ClEnv->cHandle = loop_handle; break;}
                }
              else if ((n == ((CL_INT)-1)) && 
                  ((((ClaireBoolean *) (ClaireBoolean *)((errno != EINTR ? CTRUE : CFALSE)))) == CTRUE))
               Cerrorno(97, _string_("read"), _oid_(self));
              else r= (CL_INT)(((CL_INT)r+(CL_INT)n));
                }
            POP_SIGNAL;}
          }
        Result = r;
        }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: write_port(self:descriptor,buf:char*,len:integer) [0]
CL_EXPORT CL_INT  write_port_descriptor1_Core(descriptor *self,char*buf,CL_INT len) { 
    { CL_INT Result = 0;
      if (self->closed_ask == CTRUE)
       Result = len;
      else { CL_INT  r = 0;
          CL_INT  retry = 0;
          { CL_INT loop_handle = ClEnv->cHandle;
            while (((CL_INT)r < (CL_INT)len))
            { { CL_INT  n = (CL_INT )(::write(self->fd, buf + r, len - r));
                if ((n == ((CL_INT)-1)) && 
                    ((((ClaireBoolean *) (ClaireBoolean *)((errno != EINTR ? CTRUE : CFALSE)))) == CTRUE))
                 Cerrorno(97, _string_("write"), _oid_(self));
                else r= (CL_INT)(((CL_INT)r+(CL_INT)n));
                  }
              POP_SIGNAL;}
            }
          Result = r;
          }
        POP_SIGNAL; return (Result);}
    }
  


//<sb> check whether a descriptor is connected to a terminal device
// The c++ function for: terminal?(p:port) [0]
CL_EXPORT ClaireBoolean * terminal_ask_port1(PortObject *p) { 
    p= (get_device_port1(p));
    { ClaireBoolean *Result ;
      if (INHERIT(p->isa,Core._descriptor))
       { descriptor * self = ((descriptor *) p);
        
					struct stat sb;
					if(fstat(self->fd, &sb) != -1)
						return ((sb.st_mode) & S_IFMT) != S_IFCHR ? CFALSE : CTRUE;
				;
        Result = CFALSE;
        }
      else Result = CFALSE;
        POP_SIGNAL; return (Result);}
    }
  


//<sb> duplicate a descriptor to be used in place of another
// Note : the new descriptor will be set to the lowest available
// descriptor (small int) for the current process.
// The c++ function for: duplicate(anfd:descriptor) [NEW_ALLOC]
CL_EXPORT descriptor * duplicate_descriptor1(descriptor *anfd) { 
    
    GC_BIND;
    { descriptor *Result ;
      { CL_INT  desc = 0;
        if (anfd->closed_ask == CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Attemp to duplicate descriptor ~S that is already closed.")),
          _oid_(list::alloc(1,_oid_(anfd))))));
        desc = dup(anfd->fd);
        if (desc == ((CL_INT)-1))
         Cerrorno(97, _string_("duplicate"), _oid_(anfd));
        { descriptor * _CL_obj = ((descriptor *) GC_OBJECT(descriptor,new_object_class(Core._descriptor)));
          _void_(_CL_obj->fd = desc);
          Result = close_descriptor1(_CL_obj);
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> here we initialize Clib standard ports by hand assuming that
// the underlying lib defines 0,1,2 respectively standard in,out,err
// program descriptor and already opened.
//<sb> new! avoid a call to close
//<sb> here we catch whether a standard port is redirected and update
// our knowledge about Clib standard ports accordingly.
// e.g. closing stdout and dup(2)
// The c++ function for: close(self:descriptor) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT descriptor * close_descriptor1(descriptor *self) { 
    if ((INHERIT(self->isa,Core._disk_file)) || 
        (INHERIT(self->isa,Core._pipe)))
     
    		#ifdef CLPC
    			_setmode(self->fd, _O_BINARY);
    		#endif
    	;
    if (self->fd == 0)
     write_property(Kernel.value,OBJECT(ClaireObject,value_module(Core.it,((char*)"Clib_stdin"))),_oid_(self));
    else if (self->fd == 1)
     write_property(Kernel.value,OBJECT(ClaireObject,value_module(Core.it,((char*)"Clib_stdout"))),_oid_(self));
    else if (self->fd == 2)
     write_property(Kernel.value,OBJECT(ClaireObject,value_module(Core.it,((char*)"Clib_stderr"))),_oid_(self));
    POP_SIGNAL; return (self);}
  


//<sb> here we initialize standard ports and system ports.
// note 1: if something is wrong until there during the meta load
// the behavior is undefined, even error printing cannot be achieved safely
// note 2 : for standard out (intended for write) we check whether
// the actual device is a terminal in which case a line buffer filter is added
// note 3 : stderr is always unbuffered
//<sb> @doc @xl port
// the standard input port
//<sb> @doc @xl port
// the standard output port
//<sb> @doc @xl port
// the standard error output port
//<sb> add color support
// release() should produce a version number
//<sb> @xl @doc port
// select?() waits for selected descriptors for a write or read
// condition to occur. This method blocks until a condition occur
// and will always return true as soon as a condition is satisfied.
// selected descriptors are the one for which read! or write! has been
// called first. In order to test whether a condition was satisfied on a
// selected descriptor one should use readable? or writeable?.
// The c++ function for: select?(_CL_obj:void) [0]
CL_EXPORT ClaireBoolean * select_ask_void1() { 
    { ClaireBoolean *Result ;
      { ClaireObject *V_CC ;
        { 
		CL_INT rs = fdMaxfd == -1 ? 0 : select(fdMaxfd+1,&readset,&writeset,0,0);
		fdMaxfd = -1;
          V_CC = (ClaireBoolean *)(ClaireBoolean *)((rs<=0 ? CFALSE : CTRUE));
          }
        Result= (ClaireBoolean *) V_CC;}
      POP_SIGNAL; return (Result);}
    }
  


//<sb> @xl @doc port
// select?(ms) is the non-blocking version of select?. It returns true whenever
// a read or write condition is satisfied on a selected descriptor before a timeout
// of ms milliseconds could occur. If the timeout is reached before a condition
// could occur then select?(ms) returns false.\br
// When true is returned a read (resp. write) operation is guaranteed to succeed on
// a descriptor for which readable? (resp. writable?) returns true. If the descriptor
// is a listener socket and readable? returns true then accept is guaranteed to succeed.
// \code
// get_one_char(c:socket) : string ->
// 	(read!(c),
// 	if (select?(10) & readable?(c))
// 		fread(c, 1) // always succeed
// 	else "")
// \/code
// The c++ function for: select?(ms:integer) [0]
CL_EXPORT ClaireBoolean * select_ask_integer1(CL_INT ms) { 
    { ClaireBoolean *Result ;
      { ClaireObject *V_CC ;
        { 
		timeval timeout;
		timeout.tv_sec = ms / 1000;
		timeout.tv_usec = 1000 * (ms % 1000);
		CL_INT rs = fdMaxfd == -1 ? 0 : select(fdMaxfd+1,&readset,&writeset,0,&timeout);
		fdMaxfd = -1;
          V_CC = (ClaireBoolean *)(ClaireBoolean *)((rs<=0 ? CFALSE : CTRUE));
          }
        Result= (ClaireBoolean *) V_CC;}
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: get_descriptor(self:port) [0]
CL_EXPORT descriptor * get_descriptor_port1(PortObject *self) { 
    { descriptor *Result ;
      { device *V_CC ;
        { device * p = get_device_port1(self);
          if (inherit_ask_class(p->isa,Core._descriptor) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~S is not a descriptor")),
            _oid_(list::alloc(1,_oid_(self))))));
          V_CC = p;
          }
        Result= (descriptor *) V_CC;}
      POP_SIGNAL; return (Result);}
    }
  


//<sb> @xl @doc port
// readable?(self) returns true when self has been selected (see select?)
// and that a read operation is guaranteed to succeed.
// The c++ function for: readable?(self:port) [0]
CL_EXPORT ClaireBoolean * readable_ask_port1(PortObject *self) { 
    { ClaireBoolean *Result ;
      { ClaireObject *V_CC ;
        { descriptor * p = get_descriptor_port1(self);
          V_CC = (ClaireBoolean *)(ClaireBoolean *)((FD_ISSET(p->fd, &readset) ? CTRUE : CFALSE));
          }
        Result= (ClaireBoolean *) V_CC;}
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: readable?(p:descriptor) [0]
CL_EXPORT ClaireBoolean * readable_ask_descriptor1(descriptor *p) { 
    POP_SIGNAL; return (((ClaireBoolean *) (ClaireBoolean *)((FD_ISSET(p->fd, &readset) ? CTRUE : CFALSE))));}
  


//<sb> @xl @doc port
// writable?(self) returns true when self has been selected (see select?)
// and that a write operation is guaranteed to succeed.
// The c++ function for: writable?(self:port) [0]
CL_EXPORT ClaireBoolean * writable_ask_port1(PortObject *self) { 
    { ClaireBoolean *Result ;
      { ClaireObject *V_CC ;
        { descriptor * p = get_descriptor_port1(self);
          V_CC = (ClaireBoolean *)(ClaireBoolean *)((FD_ISSET(p->fd, &writeset) ? CTRUE : CFALSE));
          }
        Result= (ClaireBoolean *) V_CC;}
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: writable?(p:descriptor) [0]
CL_EXPORT ClaireBoolean * writable_ask_descriptor1(descriptor *p) { 
    POP_SIGNAL; return (((ClaireBoolean *) (ClaireBoolean *)((FD_ISSET(p->fd, &writeset) ? CTRUE : CFALSE))));}
  


//<sb> @xl @doc port
// read!(self) put the descriptor self in the selection set used for
// the select? operation
// The c++ function for: read!(self:port) [0]
CL_EXPORT void  read_I_port1(PortObject *self) { 
    { descriptor * p = get_descriptor_port1(self);
      
		if(fdMaxfd == -1) {FD_ZERO(&readset); FD_ZERO(&writeset);}
		if(p->fd > fdMaxfd) fdMaxfd = p->fd;
		FD_SET(p->fd, &readset);;
      }
    POP_SIGNAL;}
  


// The c++ function for: read!(p:descriptor) [0]
CL_EXPORT void  read_I_descriptor1(descriptor *p) { 
    
		if(fdMaxfd == -1) {FD_ZERO(&readset); FD_ZERO(&writeset);}
		if(p->fd > fdMaxfd) fdMaxfd = p->fd;
		FD_SET(p->fd, &readset);;
    POP_SIGNAL;}
  


//<sb> @xl @doc port
// write!(self) put the descriptor self in the selection set used for
// the select? operation
// The c++ function for: write!(self:port) [0]
CL_EXPORT void  write_I_port1(PortObject *self) { 
    { descriptor * p = get_descriptor_port1(self);
      
		if(fdMaxfd == -1) {FD_ZERO(&readset); FD_ZERO(&writeset);}
		if(p->fd > fdMaxfd) fdMaxfd = p->fd;
		FD_SET(p->fd, &writeset);;
      }
    POP_SIGNAL;}
  


// The c++ function for: write!(p:descriptor) [0]
CL_EXPORT void  write_I_descriptor1(descriptor *p) { 
    
		if(fdMaxfd == -1) {FD_ZERO(&readset); FD_ZERO(&writeset);}
		if(p->fd > fdMaxfd) fdMaxfd = p->fd;
		FD_SET(p->fd, &writeset);;
    POP_SIGNAL;}
  


// claire/readwrite!(self:port) : void -> (read!(self), write!(self))
// ***************************************************************************
// * part 10: disk_file                                                      *
// ***************************************************************************
//<sb> @doc @xl port
// disk_file is the interface for file located on the hard drive
// The c++ function for: princ(self:disk_file) [NEW_ALLOC]
CL_EXPORT void  princ_disk_file1(disk_file *self) { 
    
    GC_BIND;
    { char * g0207UU;
      { list * l = GC_OBJECT(list,explode_string(GC_STRING(self->file_path),GC_STRING(string_v(Core._starfs_star->value))));
        g0207UU = ((l->length != 0) ?
          string_v(last_list(l)) :
          self->file_path );
        }
      princ_string(g0207UU);
      }
    princ_string(((char*)"("));
    print_any(((OID)self->fd));
    princ_string(((char*)")"));
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> opening a descriptor relies on open(2)
// The c++ function for: disk_file!(self:string,mod:{"ab", "wb", "rb", "wr", "rw", "a", "w", "r"}) [NEW_ALLOC]
CL_EXPORT disk_file * disk_file_I_string1(char *self,char *mod) { 
    
    GC_BIND;
    { disk_file *Result ;
      { descriptor *V_CC ;
        { CL_INT  desc;
          if ((equal_string(mod,((char*)"r")) == CTRUE) || 
              (equal_string(mod,((char*)"rb")) == CTRUE))
           desc = (CL_INT )(CL_INT )(open(self, O_RDONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
          else if ((equal_string(mod,((char*)"rw")) == CTRUE) || 
              (equal_string(mod,((char*)"wr")) == CTRUE))
           desc = (CL_INT )(CL_INT )(open(self, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
          else if ((equal_string(mod,((char*)"w")) == CTRUE) || 
              (equal_string(mod,((char*)"wb")) == CTRUE))
           desc = (CL_INT )(CL_INT )(open(self, O_WRONLY|O_APPEND|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
          else desc = (CL_INT )(CL_INT )(open(self, O_WRONLY|O_APPEND|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
            if (desc == ((CL_INT)-1))
           Cerrorno(36, _string_(self), 0);
          { disk_file * _CL_obj = ((disk_file *) GC_OBJECT(disk_file,new_object_class(Core._disk_file)));
            _void_(_CL_obj->file_path = self);
            _void_(_CL_obj->fd = desc);
            _void_(_CL_obj->file_path = realpath_string(self));
            _void_(_CL_obj->mode = (((equal_string(mod,((char*)"r")) == CTRUE) || 
                (equal_string(mod,((char*)"rb")) == CTRUE)) ?
              1 :
              (((equal_string(mod,((char*)"w")) == CTRUE) || 
                  ((equal_string(mod,((char*)"wb")) == CTRUE) || 
                    ((equal_string(mod,((char*)"a")) == CTRUE) || 
                      (equal_string(mod,((char*)"ab")) == CTRUE)))) ?
                0 :
                2 ) ));
            V_CC = close_descriptor1(_CL_obj);
            }
          }
        Result= (disk_file *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// reopen a file for read, the current offset
// of the reopened file is moved at the same place
// if a buffer is present on the filter chain then
// it contents and index are restored
// The c++ function for: reopen(self:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT PortObject * reopen_port1(PortObject *self) { 
    
    GC_RESERVE(3);  // v3.3.39 optim !
    { PortObject *Result ;
      { disk_file * s = get_disk_file_port1(self);
        CL_INT  pos = (CL_INT )((CL_INT)lseek(s->fd, (off_t)0, SEEK_CUR));
        disk_file * n = GC_OBJECT(disk_file,disk_file_I_string1(GC_STRING(s->file_path),((char*)"r")));
        PortObject * t = n;
        _void_(n->firstc = s->firstc);
        lseek(n->fd, (off_t)pos, SEEK_SET);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(f);
          bag *f_support;
          f_support = GC_OBJECT(list,s->filters);
          for (START(f_support); NEXT(f);)
          { GC_LOOP;
            if (INHERIT(OBJECT(ClaireObject,f)->isa,Core._buffer))
             GC__ANY(t = buffer_I_buffer1(OBJECT(buffer,f),t), 1);
            else if (INHERIT(OBJECT(ClaireObject,f)->isa,Core._line_counter))
             GC__ANY(t = line_counter_I_line_counter1(OBJECT(line_counter,f),t), 2);
            else if (INHERIT(OBJECT(ClaireObject,f)->isa,Core._byte_counter))
             GC__ANY(t = byte_counter_I_byte_counter1(OBJECT(byte_counter,f),t), 3);
            GC_UNLOOP; POP_SIGNAL;}
          }
        Result = t;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: filepos(self:disk_file) [0]
CL_EXPORT CL_INT  filepos_disk_file1(disk_file *self) { 
    POP_SIGNAL; return ((CL_INT )((CL_INT)lseek(self->fd, (off_t)0, SEEK_CUR)));}
  


// The c++ function for: setfilepos(self:disk_file,pos:integer) [0]
CL_EXPORT void  setfilepos_disk_file1(disk_file *self,CL_INT pos) { 
    if ((CL_INT )((CL_INT)lseek(self->fd, (off_t)pos, SEEK_SET)) == ((CL_INT)-1))
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"lseek(~S, ~S, SEEK_SET) failed")),
      _oid_(list::alloc(2,_oid_(self),((OID)pos))))));
    POP_SIGNAL;}
  


// The c++ function for: setfileend(self:disk_file) [0]
CL_EXPORT void  setfileend_disk_file1(disk_file *self) { 
    if ((CL_INT )((CL_INT)lseek(self->fd, (off_t)0, SEEK_END)) == ((CL_INT)-1))
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"lseek(~S, SEEK_END) failed")),
      _oid_(list::alloc(1,_oid_(self))))));
    POP_SIGNAL;}
  


//<sb> @doc @xl port
// open a file on disk. the returned port is buffered.
// This is a lib C like fopen API (see man for details).
// note: unlike in C lib there is no support for the 'b'
// mode (binary) i.e. always open in binary mode. For
// instance here is a simple file copy method :
// \code
// file_copy(src:string, cpy:string) : void ->
// 	let fsrc := fopen(src, "r"),
// 		fcpy := fopen(cpy,"w")
// 	in (freadwrite(fsrc, fcpy),
// 		fclose(fsrc),
// 		fclose(fcpy))
// \/code
// Notice this method does not properly set the mode of the copied
// file as done by fcopy.
// The c++ function for: fopen(self:string,mode:{"ab", "wb", "rb", "wr", "rw", "a", "w", "r"}) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT buffer * fopen_string1(char *self,char *mode) { 
    
    GC_BIND;
    { buffer *Result ;
      { filter *V_CC ;
        { disk_file * f = GC_OBJECT(disk_file,disk_file_I_string1(self,mode));
          V_CC = (buffer *)close_target_I_filter1(buffer_I_port1(f,8192));
          }
        Result= (buffer *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: get_disk_file(self:port) [0]
CL_EXPORT disk_file * get_disk_file_port1(PortObject *self) { 
    { disk_file *Result ;
      { device *V_CC ;
        { device * p = get_device_port1(self);
          if (inherit_ask_class(p->isa,Core._disk_file) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~S is not a disk file")),
            _oid_(list::alloc(1,_oid_(self))))));
          V_CC = p;
          }
        Result= (disk_file *) V_CC;}
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: flock(self:port) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  flock_port1(PortObject *self) { 
    { disk_file * f = get_disk_file_port1(self);
      if (f->locked_ask != CTRUE)
       { 
			CL_INT rc = -1;
			#ifdef CLPC
				long p = _tell(f->fd);
				_lseek(f->fd, 0, SEEK_SET);
				while(rc < 0) {
					rc = _locking(f->fd, _LK_LOCK, 1);
				}
				_lseek(f->fd, p, SEEK_SET);
				p = _tell(f->fd);
			#else 
				#ifdef HAVE_FCNTL
					struct flock lock_it;
					lock_it.l_whence = SEEK_SET;
					lock_it.l_start = 0;
					lock_it.l_len = 0;
					lock_it.l_type = (f->mode == 1 ? F_RDLCK :
										(f->mode == 2 ? (F_WRLCK|F_RDLCK) :
											F_WRLCK));
					lock_it.l_pid = 0;
					while ( ((rc = fcntl(f->fd, F_SETLKW, &lock_it)) < 0) &&
								(errno == EINTR) ) {
						continue;
					}
				#endif
			#endif
			if (rc < 0)
				Cerrorno(94,_oid_(f),0);;
        _void_(f->locked_ask = CTRUE);
        }
      }
    POP_SIGNAL;}
  


// The c++ function for: funlock(self:port) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  funlock_port1(PortObject *self) { 
    { disk_file * f = get_disk_file_port1(self);
      if (f->locked_ask == CTRUE)
       { 
			CL_INT rc = 0;
			#ifdef CLPC
				long p = _tell(f->fd);
				_lseek(f->fd, 0, SEEK_SET);
				rc = _locking(f->fd, _LK_UNLCK, 1);
				_lseek(f->fd, p, SEEK_SET);
				p = _tell(f->fd);
			#else 
				#ifdef HAVE_FCNTL
					struct flock unlock_it;
					unlock_it.l_whence = SEEK_SET;
					unlock_it.l_start  = 0;
					unlock_it.l_len    = 0;
					unlock_it.l_type   = F_UNLCK;
					unlock_it.l_pid    = 0;
					rc = fcntl(f->fd, F_SETLKW, &unlock_it);
				#endif
			#endif
			if (rc < 0)
				Cerrorno(95,_oid_(self),0);;
        _void_(f->locked_ask = CFALSE);
        }
      }
    POP_SIGNAL;}
  


// The c++ function for: islocked?(self:port) [0]
CL_EXPORT ClaireBoolean * islocked_ask_port1(PortObject *self) { 
    { ClaireBoolean *Result ;
      { ClaireBoolean * l = CFALSE;
        disk_file * f = get_disk_file_port1(self);
        
			CL_INT rc = 0;
			#ifdef CLPC
				long p = _tell(f->fd);
				_lseek(f->fd, 0, SEEK_SET);
				rc = _locking(f->fd, _LK_NBLCK, 1);
				if (rc == 0) {
					_lseek(f->fd, 0, SEEK_SET);
					_locking(f->fd, _LK_UNLCK, 1);
					_lseek(f->fd, p, SEEK_SET);
					p = _tell(f->fd);
					l = CFALSE;
				} else if (rc > 0) {
					lseek(f->fd, p, SEEK_SET);
					p = _tell(f->fd);
					l = CTRUE;
				}
			#else 
				#ifdef HAVE_FCNTL
					struct flock lock_it;
					lock_it.l_whence = SEEK_SET;
					lock_it.l_start = 0;
					lock_it.l_len = 0;
					lock_it.l_type = f->mode == 1 ? F_RDLCK : F_WRLCK;
					lock_it.l_pid = 0;
					rc = fcntl(f->fd, F_GETLK, &lock_it);
					l = (lock_it.l_type != F_UNLCK) ? CTRUE : CFALSE;
				#endif
			#endif
			if (rc < 0)
				Cerrorno(94,_oid_(self),0);;
        Result = l;
        }
      POP_SIGNAL; return (Result);}
    }
  


// ***************************************************************************
// * part 11: pipe                                                           *
// ***************************************************************************
//<sb> @doc @xl port
// interface for UNIX pipes
//<sb> @doc @xl port
// create a pair of unidirectional pipe connected to each other.
// The first one is intended for read and the second one for write.
// note: some system may return bi-directional pipes...
// The c++ function for: pipe!() [NEW_ALLOC]
CL_EXPORT tuple * pipe_I_void1_() { 
    return pipe_I_void1()->copyIfNeeded();
}


// The c++ function for: pipe!(_CL_obj:void) [NEW_ALLOC]
CL_EXPORT tuple * pipe_I_void1() { 
      
    GC_BIND;
    int fds[2];
    if ((CL_INT )(::pipe(fds)) == ((CL_INT)-1))
     Cerrorno(98, 0, 0);
    { tuple *Result ;
      { OID v_bag;
        GC_ANY(Result= tuple::empty());
        { { cl_pipe * _CL_obj = ((cl_pipe *) GC_OBJECT(cl_pipe,new_object_class(Core._pipe)));
            _void_(_CL_obj->fd = *fds);
            v_bag = _oid_(close_descriptor1(_CL_obj));
            }
          GC_OID(v_bag);}
        ((tuple *) Result)->addFast((OID)v_bag);
        { { cl_pipe * _CL_obj = ((cl_pipe *) GC_OBJECT(cl_pipe,new_object_class(Core._pipe)));
            _void_(_CL_obj->fd = *(fds+1));
            v_bag = _oid_(close_descriptor1(_CL_obj));
            }
          GC_OID(v_bag);}
        ((tuple *) Result)->addFast((OID)v_bag);}
      GC_UNBIND; return (Result);}
    }
  


// The c++ function for: princ(self:pipe) [NEW_ALLOC]
CL_EXPORT void  princ_pipe1(cl_pipe *self) { 
    princ_string(((char*)"pipe("));
    print_any(((OID)self->fd));
    princ_string(((char*)")"));
    POP_SIGNAL;}
  


// ***************************************************************************
// * part 12: socket                                                         *
// ***************************************************************************
//<sb> @doc @xl port
// the interface for UNIX stream oriented sockets, sockets are two
// way communication ports connected to a remote client.
//<sb> @doc @xl port
// the interface for listening sockets. such socket are
// used with accept to handle new connections.
// The c++ function for: princ(self:socket) [NEW_ALLOC]
CL_EXPORT void  princ_socket1(cl_socket *self) { 
    princ_string(self->address);
    princ_string(((char*)":"));
    print_any(((OID)self->tcpport));
    princ_string(((char*)"("));
    print_any(((OID)self->fd));
    princ_string(((char*)")"));
    POP_SIGNAL;}
  


// The c++ function for: close_port(self:socket) [0]
CL_EXPORT void  close_port_socket1_Core(cl_socket *self) { 
    
	#ifdef CLPC
		closesocket(self->fd);
	#else
		::close(self->fd)
	#endif
	;
    POP_SIGNAL;}
  


//<sb> @doc @xl port
// unlink the UNIX domain socket file associated with the given
// listener socket
// The c++ function for: unlink(self:listener) [0]
CL_EXPORT void  unlink_listener1(listener *self) { 
    unlink_string(self->address);
    POP_SIGNAL;}
  


//<sb> @doc @xl port
// returns the name of the host running CLAIRE
// The c++ function for: gethostname(_CL_obj:void) [NEW_ALLOC]
CL_EXPORT char * gethostname_void1() { 
    char tmp[500];
    { char *Result ;
      Result = (((((ClaireBoolean *) (ClaireBoolean *)((gethostname(tmp, 500) == 0 ? CTRUE : CFALSE)))) == CTRUE) ?
        copy_string((char *)(tmp)) :
        ((char*)"unknown host name") );
      POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// creates a connected socket at the address "addr:p", addr
// may be a numeric IP or a server name and p is the TCP port on
// which the connection should be made. For instance we could
// implement a simple HTTP GET :
// \code
// httpget(addr:string, f:string) : string ->
// 	let c := client!(addr, 80)
// 	in (printf(c, "GET /~A HTTP/1.0\r\n\r\n", f),
// 		let response := fread(c)
// 		in (fclose(c), response))
// \/code
// The c++ function for: client!(addr:string,p:integer) [NEW_ALLOC]
CL_EXPORT cl_socket * client_I_string1(char *addr,CL_INT p) { 
    
    GC_BIND;
    { cl_socket *Result ;
      { descriptor *V_CC ;
        { if (((OID)LENGTH_STRING(addr)) == _string_(((char*)"")))
           addr= (((char*)"127.0.0.1"));
          { cl_socket * _CL_obj = ((cl_socket *) GC_OBJECT(cl_socket,new_object_class(Core._socket)));
            _void_(_CL_obj->address = addr);
            _void_(_CL_obj->tcpport = p);
            _void_(_CL_obj->fd = connect_string1(addr,p));
            V_CC = close_descriptor1(_CL_obj);
            }
          }
        Result= (cl_socket *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// creates a UNIX domain connected socket on the UNIX domain
// server at file addr
// The c++ function for: client!(addr:string) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT cl_socket * client_I_string2(char *addr) { 
    
    GC_BIND;
    { cl_socket *Result ;
      { descriptor *V_CC ;
        { char * sad = ((char*)"");
          char * spt = ((char*)"");
          CL_INT  pt = -1;
          if (match_wildcard_ask_string(addr,((char*)"*:*")) == CTRUE)
           { { list * g0208 = GC_OBJECT(list,explode_wildcard_string(addr,((char*)"*:*")));
              sad= (string_v((*(g0208))[1]));
              spt= (string_v((*(g0208))[2]));
              }
            if (digit_ask_string(spt) == CTRUE)
             pt= (CL_INT)(integer_I_string(spt));
            }
          else if (digit_ask_string(addr) == CTRUE)
           pt= (CL_INT)(integer_I_string(addr));
          else sad= (addr);
            if ((pt == ((CL_INT)-1)) && 
              ((CL_INT)LENGTH_STRING(spt) > (CL_INT)0))
           {
            struct servent *p;
            p = getservbyname(spt, "tcp");
            if (p) pt = ntohs(p->s_port);
            };
          if (equal_string(sad,((char*)"")) == CTRUE)
           sad= (((char*)"127.0.0.1"));
          { cl_socket * _CL_obj = ((cl_socket *) GC_OBJECT(cl_socket,new_object_class(Core._socket)));
            _void_(_CL_obj->address = sad);
            _void_(_CL_obj->tcpport = pt);
            _void_(_CL_obj->fd = connect_string1(sad,pt));
            V_CC = close_descriptor1(_CL_obj);
            }
          }
        Result= (cl_socket *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: connect(addr:string,p:integer) [0]
CL_EXPORT CL_INT  connect_string1(char *addr,CL_INT p) { 
    
		CL_INT sock;
		CL_INT unix_domain = 0;
		#ifdef CLPC
			struct sockaddr_in inAddr;
		#else
			struct sockaddr_in inAddr;
			struct sockaddr_un unAddr;
			unix_domain = (strlen(addr) > 0 && addr[0] == '/');
		#endif
		if((sock = socket(unix_domain ? AF_UNIX : AF_INET, SOCK_STREAM, 0)) < 0)
			Cerrorno(74,_string_("connect @ string"),0);
		if (unix_domain) {
			#ifndef CLPC
			strcpy(unAddr.sun_path, addr);
			#endif
		} else if((addr[0] >= '0' && addr[0] <= '9') || *addr == 0) {
			if(*addr == 0) inAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
			else inAddr.sin_addr.s_addr = inet_addr(addr);
		} else {
			struct hostent *servent;
			if((servent = gethostbyname(addr)) == 0) {
				#ifdef CLPC
					closesocket(sock);
				#else
					::close(sock);
				#endif
				Cerrorno(74,_string_("connect @ string"),0);
			}
			memcpy(&inAddr.sin_addr, servent->h_addr, servent->h_length);
		}
		if (unix_domain) {
			#ifndef CLPC
			unAddr.sun_family = AF_UNIX;
			#endif
		} else {
			inAddr.sin_family = AF_INET;
			inAddr.sin_port = htons(p);
		}
		#ifdef CLPC
		if((connect(sock, (sockaddr*)&inAddr, sizeof(inAddr))) != 0) {
		#else
		if( (unix_domain && connect(sock, (sockaddr*)&unAddr, sizeof(unAddr)) != 0) ||
			(unix_domain == 0 && connect(sock, (sockaddr*)&inAddr, sizeof(inAddr))) != 0) {
		#endif
			#ifdef CLPC
				closesocket(sock);
			#else
				::close(sock);
			#endif
			Cerrorno(74,_string_("connect @ string"),0);
		};
    POP_SIGNAL; return ((CL_INT )(sock));}
  


//<sb> @doc @xl port
// creates a UNIX domain listener socket. addr is the \b absolute\/b path (i.e. must start with '/')
// to a file that will be used by the subsystem as listener descriptor.
// The c++ function for: server!(addr:string) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT listener * server_I_string2(char *addr) { 
    { listener *Result ;
      if (digit_ask_string(addr) == CTRUE)
       Result = server_I_string1(((char*)""),integer_I_string(addr),5);
      else { CL_INT  pt = -1;
          
          struct servent *p;
          p = getservbyname(addr, "tcp");
          if (p) pt = ntohs(p->s_port);
          ;
          Result = ((pt == ((CL_INT)-1)) ?
            server_I_string1(addr,-1,5) :
            server_I_string1(((char*)""),pt,5) );
          }
        POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// creates a INET domain listener socket listening on the port p. For instance
// here is a basic HTTP server :
// \code
// http_server(n:integer) : void ->
// 	let s := server!(n)
// 	in (while true
// 			let c := accept(s)
// 			in serve_client(c))
//
// serve_client(c:socket) : void ->
// 	(printf(c, "Hello world\n"),
// 	fclose(c))
//
// (http_server(80))
// \/code
// The c++ function for: server!(p:integer) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT listener * server_I_integer1(CL_INT p) { 
    POP_SIGNAL; return (server_I_string1(((char*)""),p,5));}
  


//<sb> @doc @xl port
// creates a INET domain listener socket listening on the port p
// with an internal queue of qlen connections.
// The c++ function for: server!(addr:string,p:integer,qlen:integer) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT listener * server_I_string1(char *addr,CL_INT p,CL_INT qlen) { 
    
    GC_BIND;
    
		CL_INT sock;
		CL_INT unix_domain = 0;
		#ifdef CLPC
			struct sockaddr_in inAddr;
		#else
			struct sockaddr_in inAddr;
			struct sockaddr_un unAddr;
			unix_domain = (strlen(addr) > 0 && addr[0] == '/');
		#endif
		if((sock = socket(unix_domain ? AF_UNIX : AF_INET, SOCK_STREAM, 0)) == 0) {
			#ifdef CLPC
				closesocket(sock);
			#else
				::close(sock);
			#endif
			Cerrorno(74,_string_("server! @ string"),0);
		}
		CL_INT val = 1;
		setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&val, sizeof(val));
		// ensure a previously used socket won't prevent to call to succeed
		val = 1;
		setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char*)&val,sizeof(val));
		#ifdef SO_REUSEPORT
		val = 1;
		setsockopt(sock,SOL_SOCKET,SO_REUSEPORT,(char*)&val,sizeof(val));
		#endif
		#if !defined(CLPC)
		if(fcntl(sock, F_GETFL, 0) == -1) {
			::close(sock);
			Cerrorno(74,_string_("server! @ string"),0);
		}
		#endif
		if (unix_domain) {
			#ifndef CLPC
			strcpy(unAddr.sun_path, addr);
			#endif
		} else if(strlen(addr)==0) inAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		else inAddr.sin_addr.s_addr = inet_addr(addr);
		if (unix_domain) {
			#ifndef CLPC
			unAddr.sun_family = unix_domain ? AF_UNIX : AF_INET;
			#endif
		} else {
			inAddr.sin_family = unix_domain ? AF_UNIX : AF_INET;
			inAddr.sin_port = p < 0 ? htons((unsigned short)0) : htons(p);
		}
		#ifdef CLPC
		if( (bind(sock, (sockaddr*)&inAddr, sizeof(inAddr)) != 0)) {
		#else
		if( (unix_domain && bind(sock, (sockaddr*)&unAddr, sizeof(unAddr)) != 0) ||
			(unix_domain == 0 && bind(sock, (sockaddr*)&inAddr, sizeof(inAddr)) != 0)) {
		#endif
			#ifdef CLPC
				closesocket(sock);
			#else
				::close(sock);
			#endif
			Cerrorno(74,_string_("server! @ string"),0);
		}
		if (p < 0) {
		  #ifdef CLPC
		  CL_INT len;
		  #else
		  GETPEERNAME_ARG3 len;
		  #endif
		  len = sizeof(struct sockaddr_in);
		  getsockname(sock, (sockaddr*)&inAddr, &len);
		  p = ntohs(inAddr.sin_port);
		}
		if(listen(sock, qlen) != 0) {
			#ifdef CLPC
				closesocket(sock);
			#else
				::close(sock);
			#endif
			Cerrorno(74,_string_("server! @ string"),0);
		};
    { listener *Result ;
      { listener * s;
        { { descriptor *V_CC ;
            { listener * _CL_obj = ((listener *) GC_OBJECT(listener,new_object_class(Core._listener)));
              _void_(_CL_obj->fd = (CL_INT )(sock));
              _void_(_CL_obj->address = string_v(CLREAD(slot,_at_property1(Core.address,Core._listener),DEFAULT)));
              V_CC = close_descriptor1(_CL_obj);
              }
            s= (listener *) V_CC;}
          GC_OBJECT(listener,s);}
        if (addr[1 - 1] == ((unsigned char)'/'))
         _void_(s->address = addr);
        else { _void_(s->address = gethostname_void1());
            _void_(s->tcpport = p);
            }
          Result = s;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> doc
// close a single communication way on the given socket.
// The c++ function for: shutdown(self:socket,mod:{"r", "w"}) [0]
CL_EXPORT void  shutdown_socket1(cl_socket *self,char *mod) { 
    if (equal_string(mod,((char*)"r")) == CTRUE)
     { {
		#if defined(CLPC)
			::shutdown(self->fd, SD_RECEIVE);
		#else 
			::shutdown(self->fd, SHUT_RD);
		#endif
		};
      ;}
    else { {
		#if defined(CLPC)
			::shutdown(self->fd, SD_SEND);
		#else 
			::shutdown(self->fd, SHUT_WR);
		#endif
		};
        ;}
      POP_SIGNAL;}
  


//<sb> @doc @xl port
// since socket are bi-channel communication ports a simple
// close (i.e. the two channel at once) may cause the client to
// miss information already sent on the socket but still unsent
// from the underlying system point of view. This is the purpose
// of the linger that will ensure that what is sent is actually
// received: first, the write channel is closed then we wait for
// the read channel to be closed by the remote part. For sanity
// this operation has a timeout of 3 seconds
// The c++ function for: linger(self:socket) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  linger_socket1(cl_socket *self) { 
    flush_port1(self);
    
		#if defined(CLPC)
			CL_INT how = SD_SEND;
		#else 
			CL_INT how = SHUT_WR;
		#endif
		if(!::shutdown(self->fd, how)) {
			CL_INT t = 0;
			do {
				fd_set fdset;
				struct timeval tv;
				tv.tv_sec = 1;
				tv.tv_usec = 0;
				FD_ZERO(&fdset);
				FD_SET(self->fd, &fdset);
				if(select(self->fd+1, &fdset, NULL, NULL, &tv) > 0) {
					char dummy[4096];
					if (recv(self->fd,dummy,4096,0) <= 0)
						break;
				}
				t++;
			} while(t < 5);
		};
    fclose_port1(self);
    POP_SIGNAL;}
  


//<sb> doc
// accept a new connection on a listener port. the returned
// socket can be handle like a normal socket.
// The c++ function for: accept(self:listener) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT cl_socket * accept_listener1(listener *self) { 
    
    GC_BIND;
    { cl_socket *Result ;
      { cl_socket * c;
        { { descriptor *V_CC ;
            { cl_socket * _CL_obj = ((cl_socket *) GC_OBJECT(cl_socket,new_object_class(Core._socket)));
              _void_(_CL_obj->tcpport = self->tcpport);
              _void_(_CL_obj->address = string_v(CLREAD(slot,_at_property1(Core.address,Core._socket),DEFAULT)));
              V_CC = close_descriptor1(_CL_obj);
              }
            c= (cl_socket *) V_CC;}
          GC_OBJECT(cl_socket,c);}
        
		CL_INT s;
		#ifdef CLPC
			struct sockaddr_in inAddr;
			CL_INT sin_size = sizeof(struct sockaddr_in);
			s = accept(self->fd, (struct sockaddr*)(&inAddr), &sin_size);
			if(s == INVALID_SOCKET) {
				Cerrorno(74,_string_("accept @ listener"),0);
			}
		#else
			struct sockaddr_in inAddr;
			GETPEERNAME_ARG3 sin_size = (GETPEERNAME_ARG3)sizeof(struct sockaddr_in);
			s = accept(self->fd, (struct sockaddr*)(&inAddr), &sin_size);
			if(s == -1) {
				Cerrorno(74,_string_("accept @ listener"),0);
			}
		#endif
		;
        _void_(c->fd = (CL_INT )(s));
        _void_(c->address = copy_string((char *)(inet_ntoa(inAddr.sin_addr))));
        Result = c;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// return a pair of inter-connected socket
// The c++ function for: socketpair() [NEW_ALLOC]
CL_EXPORT tuple * socketpair_void1_() { 
    return socketpair_void1()->copyIfNeeded();
}


// The c++ function for: socketpair(_CL_obj:void) [NEW_ALLOC]
CL_EXPORT tuple * socketpair_void1() { 
      
    GC_BIND;
    { tuple *Result ;
      { cl_socket * s1;
        { { descriptor *V_CC ;
            { cl_socket * _CL_obj = ((cl_socket *) GC_OBJECT(cl_socket,new_object_class(Core._socket)));
              _void_(_CL_obj->address = string_v(CLREAD(slot,_at_property1(Core.address,Core._socket),DEFAULT)));
              V_CC = close_descriptor1(_CL_obj);
              }
            s1= (cl_socket *) V_CC;}
          GC_OBJECT(cl_socket,s1);}
        cl_socket * s2;
        { { descriptor *V_CC ;
            { cl_socket * _CL_obj = ((cl_socket *) GC_OBJECT(cl_socket,new_object_class(Core._socket)));
              _void_(_CL_obj->address = string_v(CLREAD(slot,_at_property1(Core.address,Core._socket),DEFAULT)));
              V_CC = close_descriptor1(_CL_obj);
              }
            s2= (cl_socket *) V_CC;}
          GC_OBJECT(cl_socket,s2);}
        tuple * res = tuple::alloc(2,_oid_(s1),_oid_(s2));
        
		#if defined(CLPC) || !defined(HAVE_SOCKETPAIR)
			Cerror(75,_string_("socketpair"),0);
		#else
			int socks[2];
			if(socketpair(AF_UNIX, SOCK_STREAM, 0, socks) < 0) {
				Cerrorno(74,_string_("socketpair @ void"),0);
			}
			s1->fd = socks[0];
			s2->fd = socks[1];
		#endif
		;
        Result = res;
        }
      GC_UNBIND; return (Result);}
    }
  


// The c++ function for: read_port(self:socket,buf:char*,len:integer) [SLOT_UPDATE]
CL_EXPORT CL_INT  read_port_socket1_Core(cl_socket *self,char*buf,CL_INT len) { 
    { CL_INT Result = 0;
      { CL_INT  r = 0;
        
#if 1
;
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)r < (CL_INT)len))
          { { CL_INT  n = (CL_INT )(::recv(self->fd, buf + r, len - r,0));
              if (n == 0)
               { _void_(self->eof_reached_ask = CTRUE);
                { ;ClEnv->cHandle = loop_handle; break;}
                }
              else if ((n == ((CL_INT)-1)) && 
                  ((((ClaireBoolean *) (ClaireBoolean *)((errno != EINTR ? CTRUE : CFALSE)))) == CTRUE))
               Cerrorno(97, _string_("read"), _oid_(self));
              else r= (CL_INT)(((CL_INT)r+(CL_INT)n));
                }
            POP_SIGNAL;}
          }
        
#else
;
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)r < (CL_INT)len))
          { { CL_INT  n = (CL_INT )(::read(self->fd, buf + r, len - r));
              if (n == 0)
               { _void_(self->eof_reached_ask = CTRUE);
                { ;ClEnv->cHandle = loop_handle; break;}
                }
              else if ((n == ((CL_INT)-1)) && 
                  ((((ClaireBoolean *) (ClaireBoolean *)((errno != EINTR ? CTRUE : CFALSE)))) == CTRUE))
               Cerrorno(97, _string_("read"), _oid_(self));
              else r= (CL_INT)(((CL_INT)r+(CL_INT)n));
                }
            POP_SIGNAL;}
          }
        
#endif
;
        Result = r;
        }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: write_port(self:socket,buf:char*,len:integer) [0]
CL_EXPORT CL_INT  write_port_socket1_Core(cl_socket *self,char*buf,CL_INT len) { 
    { CL_INT Result = 0;
      { CL_INT  r = 0;
        
#if 1
;
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)r < (CL_INT)len))
          { { CL_INT  n = (CL_INT )(::send(self->fd, buf + r, len - r,0));
              if ((n == ((CL_INT)-1)) && 
                  ((((ClaireBoolean *) (ClaireBoolean *)((errno != EINTR ? CTRUE : CFALSE)))) == CTRUE))
               Cerrorno(97, _string_("write"), _oid_(self));
              else r= (CL_INT)(((CL_INT)r+(CL_INT)n));
                }
            POP_SIGNAL;}
          }
        
#else
;
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)r < (CL_INT)len))
          { { CL_INT  n = (CL_INT )(::write(self->fd, buf + r, len - r));
              if ((n == ((CL_INT)-1)) && 
                  ((((ClaireBoolean *) (ClaireBoolean *)((errno != EINTR ? CTRUE : CFALSE)))) == CTRUE))
               Cerrorno(97, _string_("write"), _oid_(self));
              else r= (CL_INT)(((CL_INT)r+(CL_INT)n));
                }
            POP_SIGNAL;}
          }
        
#endif
;
        Result = r;
        }
      POP_SIGNAL; return (Result);}
    }
  


// ***************************************************************************
// * part 13: source location                                                *
// ***************************************************************************
//<sb> print the location associated with the current state
// of the given port without issuing a dynamic message (debug proof).
// mainly used to print "<file>:<line>"
// The c++ function for: print_source_location(self:port) [NEW_ALLOC]
CL_EXPORT void  print_source_location_port1(PortObject *self) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { CL_INT  line = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((INHERIT(self->isa,Core._filter)))
        { GC_LOOP;
          if (OWNER(_oid_(self)) == Core._line_counter)
           line= (CL_INT)(((CL_INT)1+(CL_INT)CLREAD(line_counter,self,read_lines)));
          GC__ANY(self = CLREAD(filter,self,target), 1);
          GC_UNLOOP;POP_SIGNAL;}
        }
      { device * d = ((device *) self);
        if (INHERIT(d->isa,Core._disk_file))
         princ_string(CLREAD(disk_file,d,file_path));
        else if (INHERIT(d->isa,Core._socket))
         princ_string(append_string(CLREAD(cl_socket,d,address),GC_STRING(string_I_integer (CLREAD(cl_socket,d,tcpport)))));
        else if (INHERIT(d->isa,Core._descriptor))
         princ_string(append_string(((char*)"descriptor "),GC_STRING(string_I_integer (CLREAD(descriptor,d,fd)))));
        else princ_string(OWNER(_oid_(d))->name->name);
          if ((CL_INT)line > (CL_INT)0)
         { princ_string(((char*)":"));
          princ_integer(line);
          }
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> return the current file and position in that file
// in the form of tuple(<filename>, <line>, <offset in the line>)
// The c++ function for: get_location(g0209:port) [NEW_ALLOC]
CL_EXPORT tuple * get_location_port1_(PortObject *g0209) { 
    return get_location_port1(g0209)->copyIfNeeded();
}


// The c++ function for: get_location(self:port) [NEW_ALLOC]
CL_EXPORT tuple * get_location_port1(PortObject *self) { 
      
    GC_RESERVE(1);  // v3.3.39 optim !
    { tuple *Result ;
      { CL_INT  line = 0;
        CL_INT  off = 0;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while ((INHERIT(self->isa,Core._filter)))
          { GC_LOOP;
            if (OWNER(_oid_(self)) == Core._line_counter)
             { line= (CL_INT)(((CL_INT)1+(CL_INT)CLREAD(line_counter,self,read_lines)));
              off= (CL_INT)(((CL_INT)CLREAD(line_counter,self,line_offset)+(CL_INT)1));
              }
            GC__ANY(self = CLREAD(filter,self,target), 1);
            GC_UNLOOP;POP_SIGNAL;}
          }
        { device * d = ((device *) self);
          { OID v_bag;
            GC_ANY(Result= tuple::empty());
            { if (INHERIT(d->isa,Core._disk_file))
               v_bag = _string_(CLREAD(disk_file,d,file_path));
              else if (INHERIT(d->isa,Core._socket))
               v_bag = _string_(append_string(CLREAD(cl_socket,d,address),GC_STRING(string_I_integer (CLREAD(cl_socket,d,tcpport)))));
              else if (INHERIT(d->isa,Core._descriptor))
               v_bag = _string_(append_string(((char*)"descriptor "),GC_STRING(string_I_integer (CLREAD(descriptor,d,fd)))));
              else v_bag = _string_(OWNER(_oid_(d))->name->name);
                GC_OID(v_bag);}
            ((tuple *) Result)->addFast((OID)v_bag);
            ((tuple *) Result)->addFast((OID)((OID)line));
            ((tuple *) Result)->addFast((OID)((OID)off));}
          }
        }
      GC_UNBIND; return (Result);}
    }
  


// ***************************************************************************
// * part 5: popen                                                           *
// ***************************************************************************
//<sb> our only C FILE* interface: redirected process
// The c++ function for: eof_port?(self:popen_device) [0]
CL_EXPORT ClaireBoolean * eof_port_ask_popen_device1_Core(Core_popen_device *self) { 
    POP_SIGNAL; return (((ClaireBoolean *) (ClaireBoolean *)((feof(self->child_comm) ? CTRUE : CFALSE))));}
  


// The c++ function for: close_port(self:popen_device) [0]
CL_EXPORT void  close_port_popen_device1_Core(Core_popen_device *self) { 
    
	  self->exitcode = ::pclose(self->child_comm);
	  #ifndef CLPC
      if (WIFEXITED(self->exitcode)) {
        self->exitcode = WEXITSTATUS(self->exitcode);
      } else {
        self->exitcode = 1;
      }
    #endif
    ;
    POP_SIGNAL;}
  


// The c++ function for: read_port(self:popen_device,buf:char*,len:integer) [0]
CL_EXPORT CL_INT  read_port_popen_device1_Core(Core_popen_device *self,char*buf,CL_INT len) { 
    { CL_INT Result = 0;
      { CL_INT  rc = (CL_INT )(::fread(buf,1,len,self->child_comm));
        if ((((ClaireBoolean *) (ClaireBoolean *)((ferror(self->child_comm) ? CTRUE : CFALSE)))) == CTRUE)
         Cerrorno(74,_string_("read_port @ popen_device"),0);
        Result = rc;
        }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: flush_port(self:popen_device) [0]
CL_EXPORT void  flush_port_popen_device1_Core(Core_popen_device *self) { 
    ::fflush(self->child_comm);
    POP_SIGNAL;}
  


// The c++ function for: write_port(self:popen_device,buf:char*,len:integer) [0]
CL_EXPORT CL_INT  write_port_popen_device1_Core(Core_popen_device *self,char*buf,CL_INT len) { 
    { CL_INT Result = 0;
      { CL_INT  rc = (CL_INT )(::fwrite(buf,1,len,self->child_comm));
        if ((((ClaireBoolean *) (ClaireBoolean *)((ferror(self->child_comm) ? CTRUE : CFALSE)))) == CTRUE)
         Cerrorno(74,_string_("write_port @ popen_device"),0);
        Result = rc;
        }
      POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// popen creates a new process with a redirected input ("r")
// or output (w).
// popen may be a two way communication device, this
// is system dependent
// The c++ function for: popen(file:string,mod:{"r", "w", "rw"}) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT Core_popen_device * popen_string1(char *file,char *mod) { 
    
    GC_BIND;
    { Core_popen_device *Result ;
      { char * m = GC_STRING(((unix_ask_void1() == CTRUE) ?
          mod :
          append_string(mod,((char*)"b")) ));
        FILE* f = (FILE*)(::popen(file, m));
        if ((((ClaireBoolean *) (ClaireBoolean *)((f == NULL ? CTRUE : CFALSE)))) == CTRUE)
         Cerrorno(74,_string_("popen @ string"),0);
        { Core_popen_device * _CL_obj = ((Core_popen_device *) GC_OBJECT(Core_popen_device,new_object_class(Core._popen_device)));
          _void_(_CL_obj->child_comm = f);
          Result = _CL_obj;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> @doc @xl port
// perform a back-quote expansion of the system command s.
// subexpressions enclosed by '`' are substituted by the
// output generated by the corresponding command
// ex: bexpand("`ls`") returns the result of an ls command
// The c++ function for: bqexpand(s:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT char * bqexpand_string1(char *s) { 
    
    GC_RESERVE(3);  // v3.3.39 optim !
    { char *Result ;
      { list * subs = GC_OBJECT(list,explode_string(s,((char*)"`")));
        char * res = ((char*)"");
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while ((subs->length != 0))
          { GC_LOOP;
            GC__STRING(res = append_string(res,string_v((*(subs))[1])), 1);
            subs= (skip_list(subs,1));
            if (subs->length != 0)
             { Core_popen_device * p = GC_OBJECT(Core_popen_device,popen_string1(string_v((*(subs))[1]),((char*)"r")));
              char * tmp = ((char*)"");
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))) != Kernel.ctrue))
                { GC_LOOP;
                  GC__STRING(tmp = append_string(tmp,GC_STRING(fread_port4(p,1024))), 2);
                  GC_UNLOOP;POP_SIGNAL;}
                }
              GC__STRING(res = append_string(res,GC_STRING(trim_string(tmp))), 3);
              subs= (skip_list(subs,1));
              fclose_port1(p);
              }
            GC_UNLOOP;POP_SIGNAL;}
          }
        Result = res;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  



/***** CLAIRE Compilation of file ./meta/cmdline.cl 
         [version 3.5.0 / safety 5] *****/


// *********************************************************************
// * CLAIRE                                            Sylvain Benilan *
// * cmdline.cl                                                        *
// * Copyright (C) 2005 xl. All Rights Reserved                        *
// *********************************************************************
//<sb> @cat @xl Command line handling
// @section I/O, Modules and System Interface
// In XL CLAIRE, additionally to the main @ list redefinition, we have
// a command line processor that make a module able to define a particular
// set of option responder and associated command line documentation through
// 2 handlers. For instance the Reader implement the option -f used to load
// a file from the command line. The Reader implements :
// \code
// [option_usage(opt:{"-f", "-ef"}) : tuple(string, string, string) ->
// 	tuple("Load file",
// 			"{-f | -ef} <file:path> ...",
// 			"Load the CLAIRE file(s) <file>. The given path may contain an extension " /+
// 			"assuming .cl by default. When the <-f> option is used, the file is " /+
// 			"assumed to contain CLAIRE definitions (variables, class, methods) whereas " /+
// 			" <-ef> attempts to read a file made of CLAIRE expression.")]
// 	
// 
// [option_respond(opt:{"-f", "-ef"}, l:list) : void ->
// 	if not(l) invalid_option_argument(),
// 	if (not(isfile?(l[1])) & not(isfile?(l[1] /+ ".cl")))
// 		error("~A cannot be opened", l[1]),
// 	while (l & (isfile?(l[1]) | isfile?(l[1] /+ ".cl")))
// 		let path := l[1]
// 		in (l << 1,
// 			case opt
// 				({"-f"} load(path),
// 				{"-ef"} eload(path)))]
// \/code
// It comes with this implementation that when an executable is linked with a set
// of module the whole option set defined by these module is implicitly supported
// by the executable. For instance, when an executable is linked with the Reader
// module is support the -f option.\br
// Additionally to this two handlers, a module can define a single restriction of
// option_parsed that will be called once the full command line has been parsed.
// With such an handler, a module can perform a job that depends on multiple
// independent option responder (that would have initialize global flags). For
// instance :
// \code
// *myopt*:boolean := false
//
// [option_respond(opt:{"myopt"}, l:list) : void -> *myopt* := true]
//
// [option_parsed() : void ->
// 	if *myopt* ...
// 	else ...]
// \/code
// Restrictions of option_usage are used by the command line help which
// is handled with the particular option -h in the Core module :
// \code
// {-h | -help} +[<m> | <option> | <index>]
// \/code
// Which would provide the help for all options defined by a module <m> or for
// a particular option <option> or for the option having the index <index> in
// the option index as generated by option -h when used without arguments.
// @cat
// @doc @xl Command line handling
// A module can define multiple option_respond restrictions that will be called
// by the command line option parser at startup. option_respond will take two
// arguments:
// \code
// option_respond(opt:{"-opt"}, l:list[string]) : void ->
// 	...
// \/code
// \ul
// \li a set constant that contain the option name ("-opt")
// \li a list argument that represent the remaining arguments
// in the command line (where the option as already been removed).
// \/ul
// It is up to the handler to remove used arguments from the given list.
// @doc @xl Command line handling
// A module can define a single option_parsed restriction that will be called
// by the command line option parser at startup as soon as the full command
// line is parsed. It will be used inside a module to perform an operation
// that rely on multiple options (for which option_respond as already been called):
// \code
// option_parsed() : void ->
// 	...
// \/code
// @doc @xl Command line handling
// A module can define multiple option_usage restrictions that will be called
// by the command line option parser when the command line help is invoked.
// option_usage takes a single argument that is a constant set that contain
// names of multiple related options. The handler should return of tuple of
// 3 strings :
// \ul
// \li A short single line description
// \li The usage syntax of the (set of) option
// \li A detailed description
// \/ul
// \code
// option_usage(opt:{"-opt"}) : tuple(string, string, string) ->
// 	tuple("short description",
// 			"-opt <f:file>", 
// 			"long description on how to use option -opt
// 			we may use <f> to reference the argument f
// 			it can also span multiple line if needed")
// \/code
// The usage should be written following a few guidelines such the command line
// help can produce a description with a nice appearance :
// \ul
// \li <argument> or <argument:domain> is used to describe an argument of the option. As seen
// in the above example we may then use <argument> in the long description as a reference to this
// particular argument.
// \li {...} is used to enclose a non-optional part of the option expression, mostly used if it
// encloses various alternatives
// \li [...] is used to enclose optional part of the option expression
// \li +[...] is used for the repetition one or more time
// \li ...|... (the pipe) is used for possible alternatives
// \/ul
// *********************************************************************
// * Part 1: main options usage                                        *
// * Part 2: option help parsing                                       *
// * Part 3: option dispatch                                           *
// *********************************************************************
// *********************************************************************
// * Part 1: main options usage                                        *
// *********************************************************************
// The c++ function for: option_usage(g0210:{"-help", "-h"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string1_Core_(char *g0210) { 
    return option_usage_string1_Core(g0210)->copyIfNeeded();
}


// The c++ function for: option_usage(opt:{"-h", "-help"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string1_Core(char *opt) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Command line help")),
        _string_(((char*)"{-h | -help} +[<m:module> | <option:string> | <index:integer>]")),
        GC_OID(_string_(append_string(((char*)"Display an option index. When <module>, <option> or <index> are given "),((char*)"the full help is displayed for the requested entities.")))));
      GC_UNBIND; return (Result);}
    }
  


// The c++ function for: option_usage(g0211:{"-s", "-auto"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string3_Core_(char *g0211) { 
    return option_usage_string3_Core(g0211)->copyIfNeeded();
}


// The c++ function for: option_usage(opt:{"-auto", "-s"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string3_Core(char *opt) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Memory initialization")),
        _string_(((char*)"[-auto] -s <main:(0 .. 9)> <world:(0 .. 9)>")),
        GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"Sets parameters used to initialize CLAIRE memory. The main/world "),((char*)"memory is increased in a chunk of a two exponent of <main>/<world> argument. "))),((char*)"The main memory is used for normal object allocation and the world "))),((char*)"memory is used to store defeasible updates.\n"))),((char*)"When <-auto> is specified the memory is silently allocated to its maximum "))),((char*)"but still constrained in a chunk as specified by the <-s> option. "))),((char*)"The option <-auto> takes effect around memory congestion (near an overflow) "))),((char*)"where it let the concerned memory to be silently increased such a program "))),((char*)"that require more memory (than specified by the <-s> option) can achieve it task. "))),((char*)"A program ran in <-auto> will take advantage of modern OS that "))),((char*)"actually manage true virtual pages. The <-auto> flag only controls "))),((char*)"the memory congestion issue but never perform any de-congestion.")))));
      GC_UNBIND; return (Result);}
    }
  


// The c++ function for: option_usage(g0212:{"-v"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string4_Core_(char *g0212) { 
    return option_usage_string4_Core(g0212)->copyIfNeeded();
}


// The c++ function for: option_usage(opt:{"-v"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string4_Core(char *opt) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Verbose")),
        _string_(((char*)"-v [<m:module>] <level:integer>")),
        GC_OID(_string_(append_string(GC_STRING(append_string(((char*)"Sets the system verbosity level. Any trace instruction with a level "),((char*)"lower or equal to <verbose> are issued and others prevented. "))),((char*)"When <m> is specified the verbosity of the given module is set instead.")))));
      GC_UNBIND; return (Result);}
    }
  


// The c++ function for: option_usage(g0213:{"-q"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string5_Core_(char *g0213) { 
    return option_usage_string5_Core(g0213)->copyIfNeeded();
}


// The c++ function for: option_usage(opt:{"-q"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string5_Core(char *opt) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Exit now")),
        _string_(((char*)"-q [<exitcode:integer>]")),
        GC_OID(_string_(append_string(GC_STRING(append_string(((char*)"Exit now, do not process the end of the command line, do not start an interpreter. "),((char*)"When <exitcode> is specified, it is used as the program exit code which is 0 otherwise.\n"))),((char*)"The <-q> option is always reached even if an exception has occurred before.")))));
      GC_UNBIND; return (Result);}
    }
  


// The c++ function for: option_usage(g0214:{"-errassegv", "-qonerror"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string6_Core_(char *g0214) { 
    return option_usage_string6_Core(g0214)->copyIfNeeded();
}


// The c++ function for: option_usage(opt:{"-qonerror", "-errassegv"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string6_Core(char *opt) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Early termination")),
        _string_(((char*)"-qonerror | -errassegv")),
        GC_OID(_string_(append_string(GC_STRING(append_string(((char*)"These options produce an early termination when an uncaught exception occurs. "),((char*)"With <-qonerror> the program will exit with code 1 and with <-errassegv> it "))),((char*)"will raise a segmentation violation signal.")))));
      GC_UNBIND; return (Result);}
    }
  


// The c++ function for: option_usage(g0215:{"-noel"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string8_Core_(char *g0215) { 
    return option_usage_string8_Core(g0215)->copyIfNeeded();
}


// The c++ function for: option_usage(opt:{"-noel"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string8_Core(char *opt) { 
      { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Avoid editline")),
        _string_(((char*)"-noel")),
        _string_(((char*)"Do not use editline for the interpreter.")));
      return (Result);}
    }
  


// The c++ function for: option_usage(g0216:{"-nocolor", "-color"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string9_Core_(char *g0216) { 
    return option_usage_string9_Core(g0216)->copyIfNeeded();
}


// The c++ function for: option_usage(opt:{"-color", "-nocolor"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string9_Core(char *opt) { 
      { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Terminal color")),
        _string_(((char*)"-color | -nocolor")),
        _string_(((char*)"Enable (or not) the support for terminal colors. Disabled by default.")));
      return (Result);}
    }
  


// The c++ function for: option_usage(g0217:{"-trace"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string10_Core_(char *g0217) { 
    return option_usage_string10_Core(g0217)->copyIfNeeded();
}


// The c++ function for: option_usage(opt:{"-trace"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string10_Core(char *opt) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Trace file")),
        _string_(((char*)"-trace [a | append] <file:path>")),
        GC_OID(_string_(append_string(((char*)"Redirect traces to <file>. The file is overwritten unless 'a' or 'append' "),((char*)"is specified. Traces depends on the verbosity level (see option <-v>).")))));
      GC_UNBIND; return (Result);}
    }
  


// The c++ function for: option_usage(g0218:{"-sample"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string11_Core_(char *g0218) { 
    return option_usage_string11_Core(g0218)->copyIfNeeded();
}


// The c++ function for: option_usage(opt:{"-sample"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string11_Core(char *opt) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Sampling Cmemory")),
        _string_(((char*)"-sample <period:integer>")),
        GC_OID(_string_(append_string(GC_STRING(append_string(((char*)"Perform photos of Cmemory at intervals of <period> milliseconds. "),((char*)"A file clmeormy.samples is issued and may be used with gnuplot to "))),((char*)"produce a graph.")))));
      GC_UNBIND; return (Result);}
    }
  


// The c++ function for: option_usage(g0219:{"-chdir"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string12_Core_(char *g0219) { 
    return option_usage_string12_Core(g0219)->copyIfNeeded();
}


// The c++ function for: option_usage(opt:{"-chdir"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string12_Core(char *opt) { 
      { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Change directory")),
        _string_(((char*)"-chdir <dir:relative path>")),
        _string_(((char*)"Change the current working directory to <dir>")));
      return (Result);}
    }
  


// The c++ function for: option_usage(g0220:{"-options"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string32_Core_(char *g0220) { 
    return option_usage_string32_Core(g0220)->copyIfNeeded();
}


// The c++ function for: option_usage(opt:{"-options"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string32_Core(char *opt) { 
      { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Load a file of options")),
        _string_(((char*)"-options <cfg:file>")),
        _string_(((char*)"Load file <cfg> containing command line options.")));
      return (Result);}
    }
  


// *********************************************************************
// * Part 2: option help parsing                                       *
// *********************************************************************
// The c++ function for: print_var(self:string) [0]
CL_EXPORT void  print_var_string1(char *self) { 
    color(32,0);
    princ_string(((char*)"<"));
    princ_string(self);
    princ_string(((char*)">"));
    color(30,0);
    POP_SIGNAL;}
  


// The c++ function for: print_option(self:string) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT void  print_option_string1(char *self) { 
    
    GC_BIND;
    { blob * p = GC_OBJECT(blob,blob_I_string1(self));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))) != Kernel.ctrue))
        { GC_LOOP;
          { tuple * g0221 = freadline_port4(p,set::alloc(Kernel.emptySet,1,_string_(((char*)"<"))));
            char * o = GC_STRING(string_v((*(g0221))[1]));
            OID  sep = GC_OID((*(g0221))[2]);
            color(34,0);
            princ_string(o);
            color(30,0);
            if (equal(sep,_string_(((char*)"<"))) == CTRUE)
             print_var_string1(freadline_port1(p,((char*)">")));
            }
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: print_module(self:module) [NEW_ALLOC]
CL_EXPORT void  print_module_module1(module *self) { 
    princ_string(((char*)"====== "));
    print_any(_oid_(self));
    princ_string(((char*)" options ======\n"));
    POP_SIGNAL;}
  


// The c++ function for: parse_var(p:port,opts:list[string],vars:list[string],rngs:list[string]) [NEW_ALLOC]
CL_EXPORT char * parse_var_port1(PortObject *p,list *opts,list *vars,list *rngs) { 
    
    GC_BIND;
    { char *Result ;
      { tuple * g0222 = freadline_port4(p,OBJECT(bag,Core.VAR_END->value));
        OID  var = GC_OID((*(g0222))[1]);
        OID  sep = GC_OID((*(g0222))[2]);
        vars= (GC_OBJECT(list,vars->addFast((OID)var)));
        if (equal(sep,_string_(((char*)":"))) == CTRUE)
         { char * rng = GC_STRING(freadline_port1(p,((char*)">")));
          rngs= (GC_OBJECT(list,rngs->addFast((OID)_string_(rng))));
          }
        else rngs= (GC_OBJECT(list,rngs->addFast((OID)_string_(((char*)"unknown")))));
          Result = string_v(var);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: parse_option(p:port,opts:list[string],vars:list[string],rngs:list[string]) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  parse_option_port1(PortObject *p,list *opts,list *vars,list *rngs) { 
    
    GC_RESERVE(3);  // v3.3.39 optim !
    { char * opt = ((char*)"-");
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))) != Kernel.ctrue))
        { GC_LOOP;
          { tuple * g0223 = freadline_port4(p,OBJECT(bag,Core.OPT_END->value));
            char * o = GC_STRING(string_v((*(g0223))[1]));
            OID  sep = GC_OID((*(g0223))[2]);
            GC__STRING(opt = append_string(opt,o), 1);
            if (equal(sep,_string_(((char*)"<"))) == CTRUE)
             GC__STRING(opt = append_string(opt,GC_STRING(append_string(GC_STRING(append_string(((char*)"<"),GC_STRING(parse_var_port1(p,opts,vars,rngs)))),((char*)">")))), 2);
            else { GC__ANY(opts = opts->addFast((OID)_string_(opt)), 3);
                print_option_string1(opt);
                (*Kernel.princ)(sep);
                { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                }
              }
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: print_back_option_usage(self:string) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT list * print_back_option_usage_string1(char *self) { 
    
    GC_BIND;
    { list *Result ;
      { blob * p = GC_OBJECT(blob,blob_I_string1(self));
        Result = print_back_option_usage_port1(p);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: print_back_option_usage(p:port) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT list * print_back_option_usage_port1(PortObject *p) { 
    
    GC_BIND;
    { list *Result ;
      { list * vars = list::empty(Kernel._string);
        list * rngs = list::empty(Kernel._string);
        list * opts = list::empty(Kernel._string);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))) != Kernel.ctrue))
          { GC_LOOP;
            { tuple * g0224 = freadline_port4(p,OBJECT(bag,Core.CMD_SEPS->value));
              char * dummy = GC_STRING(string_v((*(g0224))[1]));
              OID  sep = GC_OID((*(g0224))[2]);
              princ_string(dummy);
              if ((equal(sep,_string_(((char*)"["))) == CTRUE) || 
                  ((equal(sep,_string_(((char*)"]"))) == CTRUE) || 
                    ((equal(sep,_string_(((char*)"|"))) == CTRUE) || 
                      ((equal(sep,_string_(((char*)"{"))) == CTRUE) || 
                        (equal(sep,_string_(((char*)"}"))) == CTRUE)))))
               princ_string(string_v(sep));
              else if (equal(sep,_string_(((char*)"-"))) == CTRUE)
               { if ((CL_INT)LENGTH_STRING(dummy) > (CL_INT)0)
                 princ_string(((char*)"-"));
                else parse_option_port1(p,opts,vars,rngs);
                  }
              else if (equal(sep,_string_(((char*)"<"))) == CTRUE)
               print_var_string1(parse_var_port1(p,opts,vars,rngs));
              else if (equal(sep,_string_(((char*)" "))) == CTRUE)
               princ_string(((char*)" "));
              }
            GC_UNLOOP;POP_SIGNAL;}
          }
        Result = list::alloc(3,_oid_(opts),
          _oid_(vars),
          _oid_(rngs));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: print_back_option_help(self:string,l:list) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT void  print_back_option_help_string1(char *self,list *l) { 
    
    GC_BIND;
    { blob * p = GC_OBJECT(blob,blob_I_string1(self));
      print_back_option_help_port1(p,l);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: print_back_option_help(p:port,l:list) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT void  print_back_option_help_port1(PortObject *p,list *l) { 
    
    GC_BIND;
    princ_string(((char*)"    "));
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))) != Kernel.ctrue))
      { GC_LOOP;
        { tuple * g0225 = freadline_port4(p,set::alloc(Kernel.emptySet,2,_string_(((char*)"<")),_string_(((char*)"\n"))));
          char * data = GC_STRING(string_v((*(g0225))[1]));
          OID  sep = GC_OID((*(g0225))[2]);
          color_princ_string1(data);
          if (equal(sep,_string_(((char*)"\n"))) == CTRUE)
           princ_string(((char*)"\n    "));
          else if (_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))) != Kernel.ctrue)
           { char * varopt = GC_STRING(freadline_port1(p,((char*)">")));
            if (belong_to(_string_(varopt),(*(l))[1]) == CTRUE)
             print_option_string1(varopt);
            else print_var_string1(varopt);
              }
          }
        GC_UNLOOP;POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: find_option_usage(self:integer) [0]
CL_EXPORT OID  find_option_usage_integer1(CL_INT self) { 
    { OID Result = 0;
      { list * l = Core.option_usage->restrictions;
        CL_INT  idx = 0;
        OID  good = CNULL;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(g0226);
          bag *g0226_support;
          g0226_support = Kernel._module->descendents;
          for (START(g0226_support); NEXT(g0226);)
          { ClaireBoolean * g0227;
            { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(m);
                V_C= Kernel.cfalse;
                for (START(OBJECT(ClaireClass,g0226)->instances); NEXT(m);)
                { if (good != CNULL)
                   { V_C = Kernel.ctrue;
                    ClEnv->cHandle = loop_handle;break;}
                  { CL_INT loop_handle = ClEnv->cHandle;
                    ITERATE(r);
                    for (START(l); NEXT(r);)
                    if (_oid_(OBJECT(restriction,r)->module_I) == m)
                     { ++idx;
                      if (idx == self)
                       { good= (r);
                        { ;ClEnv->cHandle = loop_handle; break;}
                        }
                      }
                    }
                  }
                }
              
              g0227=OBJECT(ClaireBoolean,V_C);}
            if (g0227 == CTRUE)
             { ;ClEnv->cHandle = loop_handle; break;}
            }
          }
        Result = good;
        }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: find_option_usage(self:string) [NEW_ALLOC]
CL_EXPORT OID  find_option_usage_string1(char *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  r_some = CNULL;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(r);
          for (START(Core.option_usage->restrictions); NEXT(r);)
          { GC_LOOP;
            { ClaireBoolean * g0228I;
              { OID  g0229UU;
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(w);
                  g0229UU= Kernel.cfalse;
                  bag *w_support;
                  w_support = GC_OBJECT(bag,enumerate_any((*(OBJECT(restriction,r)->domain))[1]));
                  for (START(w_support); NEXT(w);)
                  if (match_wildcard_ask_string(self,string_v(w)) == CTRUE)
                   { g0229UU = Kernel.ctrue;
                    ClEnv->cHandle = loop_handle;break;}
                  }
                g0228I = boolean_I_any(g0229UU);
                }
              
              if (g0228I == CTRUE) { r_some= (r);
                  GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                }
            GC_UNLOOP; POP_SIGNAL;}
          }
        Result = r_some;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: print_option_usage(r:method,m:module) [NEW_ALLOC]
CL_EXPORT void  print_option_usage_method1(method *r,module *m) { 
    
    GC_BIND;
    { OID  g0230 = GC_OID(apply_method(r,list::alloc(1,(*(OBJECT(bag,(*(r->domain))[1])))[1])));
      OID  title = GC_OID((*Kernel.nth)(g0230,
        ((OID)1)));
      OID  syntax = GC_OID((*Kernel.nth)(g0230,
        ((OID)2)));
      OID  help = GC_OID((*Kernel.nth)(g0230,
        ((OID)3)));
      princ_string(((char*)"  "));
      { OID  l = GC_OID((*Core.print_back_option_usage)(syntax));
        princ_string(((char*)"\n"));
        if ((CL_INT)((CL_INT)(*Kernel.length)((*(OBJECT(bag,l)))[2])) > (CL_INT)0)
         { CL_INT  i = 1;
          CL_INT  g0231 = ((CL_INT)(*Kernel.length)((*(OBJECT(bag,l)))[2]));
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)i <= (CL_INT)g0231))
            { GC_LOOP;
              { ClaireBoolean * g0233I;
                { OID  g0234UU;
                  { ClaireBoolean * V_CL0235;{ OID  g0236UU;
                      { CL_INT  j = 1;
                        CL_INT  g0232 = ((CL_INT)i-(CL_INT)1);
                        { CL_INT loop_handle = ClEnv->cHandle;
                          OID gc_local;
                          g0236UU= _oid_(CFALSE);
                          while (((CL_INT)j <= (CL_INT)g0232))
                          { GC_LOOP;
                            if (equal(GC_OID((*Kernel.nth)((*(OBJECT(bag,l)))[2],
                              ((OID)i))),GC_OID((*Kernel.nth)((*(OBJECT(bag,l)))[2],
                              ((OID)j)))) == CTRUE)
                             { GC_UNLOOP;g0236UU = Kernel.ctrue;
                              ClEnv->cHandle = loop_handle;break;}
                            ++j;
                            GC_UNLOOP;POP_SIGNAL;}
                          }
                        }
                      V_CL0235 = boolean_I_any(g0236UU);
                      }
                    
                    g0234UU=_oid_(V_CL0235);}
                  g0233I = not_any(g0234UU);
                  }
                
                if (g0233I == CTRUE) { princ_string(((char*)"    "));
                    print_var_string1(string_v((*Kernel.nth)((*(OBJECT(bag,l)))[2],
                      ((OID)i))));
                    princ_string(((char*)" % "));
                    (*Kernel.princ)(GC_OID((*Kernel.nth)((*(OBJECT(bag,l)))[3],
                      ((OID)i))));
                    princ_string(((char*)"\n"));
                    }
                  }
              ++i;
              GC_UNLOOP;POP_SIGNAL;}
            }
          }
        princ_string(((char*)"\n"));
        (*Core.print_back_option_help)(help,
          l);
        princ_string(((char*)"\n\n"));
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: print_option_usage(r:method) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT void  print_option_usage_method2(method *r) { 
    print_option_usage_method1(r,r->module_I);
    POP_SIGNAL;}
  


// The c++ function for: print_option_usage(opt:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  print_option_usage_string1(char *opt) { 
    
    GC_BIND;
    { OID  rtest = GC_OID(find_option_usage_string1(opt));
      if (rtest != CNULL)
       { method * r = OBJECT(method,rtest);
        print_option_usage_method2(r);
        }
      else { CL_INT  g0237 = (CL_INT )(current_color);
          CL_INT  g0238 = (CL_INT )(current_bold);
          CL_INT  g0239 = g0237;
          CL_INT  g0240 = g0238;
          color(g0237,g0238);
          color_princ_string1(((char*)"`REDInvalid option "));
          g0237= (CL_INT)((CL_INT )(current_color));
          g0238= (CL_INT)((CL_INT )(current_bold));
          color(g0239,g0240);
          print_any(_string_(opt));
          color(g0237,g0238);
          color(g0237,g0238);
          color_princ_string1(((char*)"\n"));
          color(g0239,g0240);
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: print_option_usage(m:module) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT void  print_option_usage_module1(module *m) { 
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(r);
      for (START(Core.option_usage->restrictions); NEXT(r);)
      if (OBJECT(restriction,r)->module_I == m)
       print_option_usage_method1(OBJECT(method,r),m);
      }
    POP_SIGNAL;}
  


// The c++ function for: print_option_usage(_CL_obj:void) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT void  print_option_usage_void1() { 
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(g0241);
      bag *g0241_support;
      g0241_support = Kernel._module->descendents;
      for (START(g0241_support); NEXT(g0241);)
      { ClaireBoolean * g0242;
        { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(m);
            V_C= Kernel.cfalse;
            for (START(OBJECT(ClaireClass,g0241)->instances); NEXT(m);)
            { ClaireBoolean * first_ask = CTRUE;
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(r);
                for (START(Core.option_usage->restrictions); NEXT(r);)
                if (_oid_(OBJECT(restriction,r)->module_I) == m)
                 { if (first_ask == CTRUE)
                   { first_ask= (CFALSE);
                    print_module_module1(OBJECT(module,m));
                    }
                  print_option_usage_method1(OBJECT(method,r),OBJECT(module,m));
                  }
                }
              }
            }
          
          g0242=OBJECT(ClaireBoolean,V_C);}
        if (g0242 == CTRUE)
         { ;ClEnv->cHandle = loop_handle; break;}
        }
      }
    POP_SIGNAL;}
  


// The c++ function for: print_option_index(r:method,i:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  print_option_index_method1(method *r,CL_INT i) { 
    
    GC_BIND;
    { OID  g0243 = GC_OID(apply_method(r,list::alloc(1,(*(OBJECT(bag,(*(r->domain))[1])))[1])));
      OID  title = GC_OID((*Kernel.nth)(g0243,
        ((OID)1)));
      OID  syntax = GC_OID((*Kernel.nth)(g0243,
        ((OID)2)));
      OID  help = GC_OID((*Kernel.nth)(g0243,
        ((OID)3)));
      color(32,0);
      print_any(((OID)i));
      color(30,0);
      princ_string(((char*)" - "));
      (*Kernel.princ)(title);
      princ_string(((char*)" : "));
      (*Core.print_back_option_usage)(syntax);
      princ_string(((char*)"\n"));
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: print_option_index(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  print_option_index_void1() { 
    princ_string(((char*)"====== Option syntax ======\n"));
    { CL_INT  g0244 = (CL_INT )(current_color);
      CL_INT  g0245 = (CL_INT )(current_bold);
      CL_INT  g0246 = g0244;
      CL_INT  g0247 = g0245;
      color(g0244,g0245);
      color_princ_string1(((char*)"  ``BLACK[`BLACKx``BLACK]\t`BLACK-> x is optional\n"));
      color(g0246,g0247);
      }
    { CL_INT  g0248 = (CL_INT )(current_color);
      CL_INT  g0249 = (CL_INT )(current_bold);
      CL_INT  g0250 = g0248;
      CL_INT  g0251 = g0249;
      color(g0248,g0249);
      color_princ_string1(((char*)"  ``BLACK{`BLACKx``BLACK}\t`BLACK-> x (identity)\n"));
      color(g0250,g0251);
      }
    { CL_INT  g0252 = (CL_INT )(current_color);
      CL_INT  g0253 = (CL_INT )(current_bold);
      CL_INT  g0254 = g0252;
      CL_INT  g0255 = g0253;
      color(g0252,g0253);
      color_princ_string1(((char*)"  x ``BLACK| `BLACKy\t-> x or y\n"));
      color(g0254,g0255);
      }
    { CL_INT  g0256 = (CL_INT )(current_color);
      CL_INT  g0257 = (CL_INT )(current_bold);
      CL_INT  g0258 = g0256;
      CL_INT  g0259 = g0257;
      color(g0256,g0257);
      color_princ_string1(((char*)"  ``BLACK+`BLACKx\t-> x is repeated at least one\n"));
      color(g0258,g0259);
      }
    { CL_INT  g0260 = (CL_INT )(current_color);
      CL_INT  g0261 = (CL_INT )(current_bold);
      CL_INT  g0262 = g0260;
      CL_INT  g0263 = g0261;
      color(g0260,g0261);
      color_princ_string1(((char*)"  ``BLACK*`BLACKx\t-> x is repeated 0 or more times\n"));
      color(g0262,g0263);
      }
    { list * l = Core.option_usage->restrictions;
      CL_INT  idx = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(g0264);
        bag *g0264_support;
        g0264_support = Kernel._module->descendents;
        for (START(g0264_support); NEXT(g0264);)
        { ClaireBoolean * g0265;
          { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(m);
              V_C= Kernel.cfalse;
              for (START(OBJECT(ClaireClass,g0264)->instances); NEXT(m);)
              { ClaireBoolean * first_ask = CTRUE;
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(r);
                  for (START(l); NEXT(r);)
                  if (_oid_(OBJECT(restriction,r)->module_I) == m)
                   { ++idx;
                    if (first_ask == CTRUE)
                     { print_module_module1(OBJECT(module,m));
                      first_ask= (CFALSE);
                      }
                    print_option_index_method1(OBJECT(method,r),idx);
                    }
                  }
                }
              }
            
            g0265=OBJECT(ClaireBoolean,V_C);}
          if (g0265 == CTRUE)
           { ;ClEnv->cHandle = loop_handle; break;}
          }
        }
      }
    POP_SIGNAL;}
  


// The c++ function for: apply_option_begin_parse(_CL_obj:void) [NEW_ALLOC]
CL_EXPORT void  apply_option_begin_parse_void1() { 
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(r);
      for (START(Core.option_begin_parse->restrictions); NEXT(r);)
      apply_method(OBJECT(method,r),list::alloc(1,_oid_(Kernel._void)));
      }
    POP_SIGNAL;}
  


// The c++ function for: apply_option_parsed(_CL_obj:void) [NEW_ALLOC]
CL_EXPORT void  apply_option_parsed_void1() { 
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(r);
      for (START(Core.option_parsed->restrictions); NEXT(r);)
      apply_method(OBJECT(method,r),list::alloc(1,_oid_(Kernel._void)));
      }
    POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-h", "-help"},l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  option_respond_string1_Core(char *opt,list *l) { 
    
    GC_BIND;
    color_integer(1);
    if (boolean_I_any(_oid_(l)) != CTRUE)
     print_option_index_void1();
    else { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((l->length != 0))
        { GC_LOOP;
          { OID  opt = (*(l))[1];
            char * lopt = GC_STRING(lower_string(string_v(opt)));
            OID  mod;
            { { OID  m_some = CNULL;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(g0266);
                  bag *g0266_support;
                  g0266_support = Kernel._module->descendents;
                  for (START(g0266_support); NEXT(g0266);)
                  { GC_LOOP;
                    { ClaireBoolean * g0267;
                      { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                          OID gc_local;
                          ITERATE(m);
                          V_C= Kernel.cfalse;
                          for (START(OBJECT(ClaireClass,g0266)->instances); NEXT(m);)
                          { GC_LOOP;
                            if (equal_string(lower_string(OBJECT(thing,m)->name->name),lopt) == CTRUE)
                             { GC_UNLOOP;V_C = m_some= (m);
                              ClEnv->cHandle = loop_handle;break;}
                            GC_UNLOOP; POP_SIGNAL;}
                          }
                        
                        g0267=OBJECT(ClaireBoolean,V_C);}
                      if (g0267 == CTRUE)
                       { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                      }
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                mod = m_some;
                }
              GC_OID(mod);}
            if (INHERIT(OWNER(mod),Kernel._module))
             { princ_string(((char*)"====== ["));
              print_any(mod);
              princ_string(((char*)"] ======\n\n"));
              if (OBJECT(module,mod)->made_of->length != 0)
               print_option_usage_module1(OBJECT(module,mod));
              else { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(m);
                  bag *m_support;
                  m_support = GC_OBJECT(list,OBJECT(module,mod)->parts);
                  for (START(m_support); NEXT(m);)
                  (*Core.print_option_usage)(m);
                  }
                }
            else { OID  rtest = GC_OID((*Core.find_option_usage)(opt));
                if (rtest != CNULL)
                 { method * r = OBJECT(method,rtest);
                  print_option_usage_method2(r);
                  }
                else { OID  rtest = find_option_usage_integer1(((CL_INT)(*Kernel.integer_I)(opt)));
                    if (rtest != CNULL)
                     { method * r = OBJECT(method,rtest);
                      print_option_usage_method2(r);
                      }
                    else { CL_INT  g0268 = (CL_INT )(current_color);
                        CL_INT  g0269 = (CL_INT )(current_bold);
                        CL_INT  g0270 = g0268;
                        CL_INT  g0271 = g0269;
                        color(g0268,g0269);
                        color_princ_string1(((char*)"`RED"));
                        g0268= (CL_INT)((CL_INT )(current_color));
                        g0269= (CL_INT)((CL_INT )(current_bold));
                        color(g0270,g0271);
                        (*Kernel.princ)(opt);
                        color(g0268,g0269);
                        color(g0268,g0269);
                        color_princ_string1(((char*)" is unbound (try "));
                        g0268= (CL_INT)((CL_INT )(current_color));
                        g0269= (CL_INT)((CL_INT )(current_bold));
                        color(g0270,g0271);
                        (*Kernel.princ)((*(ClEnv->params))[1]);
                        color(g0268,g0269);
                        color(g0268,g0269);
                        color_princ_string1(((char*)" -h)\n"));
                        color(g0270,g0271);
                        }
                      }
                  }
              skip_list(l,1);
            }
          GC_UNLOOP;POP_SIGNAL;}
        }
      CL_exit(0);
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-s"},l:list) [0]
CL_EXPORT void  option_respond_string2_Core(char *opt,list *l) { 
    skip_list(l,2);
    POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-color", "-nocolor", "-logo", "-auto", "-noel", "-alt", "-gcstress"},l:list) [0]
CL_EXPORT void  option_respond_string48_Core(char *opt,list *l) { 
    ;POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-qonerror"},l:list) [0]
CL_EXPORT void  option_respond_string4_Core(char *opt,list *l) { 
    (Core._Zqonerror->value= Kernel.ctrue);
    POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-errassegv"},l:list) [0]
CL_EXPORT void  option_respond_string5_Core(char *opt,list *l) { 
    (Core._Zerrassegv->value= Kernel.ctrue);
    POP_SIGNAL;}
  


// The c++ function for: number?(s:string) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * number_ask_string1(char *s) { 
    { ClaireBoolean *Result ;
      Result = ((digit_ask_string(s) == CTRUE) ?
        CTRUE :
        (((CL_INT)LENGTH_STRING(s) < (CL_INT)2) ?
          CFALSE :
          ((s[1 - 1] != ((unsigned char)'-')) ?
            CFALSE :
            digit_ask_string(substring_string(s,2,LENGTH_STRING(s))) ) ) );
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: option_respond(opt:{"-q"},l:list) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT void  option_respond_string7_Core(char *opt,list *l) { 
    { OID  l1;
      if (l->length != 0)
       l1 = (*(l))[1];
      else l1 = _string_(((char*)""));
        apply_option_parsed_void1();
      CL_exit(((CL_INT)(*Kernel.integer_I)(l1)));
      }
    POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-v"},l:list) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  option_respond_string8_Core(char *opt,list *l) { 
    if (boolean_I_any(_oid_(l)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    { OID  opt = (*(l))[1];
      OID  mod = value_string(string_v(opt));
      CL_INT  v = ((CL_INT)(*Kernel.integer_I)(opt));
      if (INHERIT(OWNER(mod),Kernel._module))
       { skip_list(l,1);
        if ((boolean_I_any(_oid_(l)) != CTRUE) || 
            (number_ask_string1(string_v((*(l))[1])) != CTRUE))
         close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
        _void_(OBJECT(module,mod)->verbose = (*Kernel.integer_I)((*(l))[1]));
        skip_list(l,1);
        }
      else { if (number_ask_string1(string_v((*(l))[1])) != CTRUE)
           close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
          skip_list(l,1);
          _void_(ClEnv->verbose = ((CL_INT)(*Kernel.integer_I)(opt)));
          }
        }
    POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-trace"},l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  option_respond_string9_Core(char *opt,list *l) { 
    { char * m = ((char*)"w");
      if (boolean_I_any(_oid_(l)) != CTRUE)
       close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
      if ((equal((*(l))[1],_string_(((char*)"a"))) == CTRUE) || 
          (equal((*(l))[1],_string_(((char*)"append"))) == CTRUE))
       { m= (((char*)"a"));
        skip_list(l,1);
        if (boolean_I_any(_oid_(l)) != CTRUE)
         close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
        }
      { OID  path = (*(l))[1];
        skip_list(l,1);
        _void_(ClEnv->ctrace = fopen_string1(string_v(path),m));
        }
      }
    POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-sample"},l:list) [NEW_ALLOC]
CL_EXPORT void  option_respond_string41_Core(char *opt,list *l) { 
    if (boolean_I_any(_oid_(l)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    skip_list(l,1);
    POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-chdir"},l:list[string]) [NEW_ALLOC]
CL_EXPORT void  option_respond_string40_Core(char *opt,list *l) { 
    if (boolean_I_any(_oid_(l)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    { OID  dir = (*(l))[1];
      skip_list(l,1);
      setcwd_string(string_v(dir));
      }
    POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-dynload"},l:list[string]) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  option_respond_string49_Core(char *opt,list *l) { 
    
    GC_BIND;
    if (boolean_I_any(_oid_(l)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    { OID  m = (*(l))[1];
      char * ext = ((char*)".dll");
      if (unix_ask_void1() == CTRUE)
       ext= (((char*)".so"));
      else m= (GC_OID(_string_(replace_string(string_v(m),((char*)"/"),GC_STRING(string_v(Core._starfs_star->value))))));
        m= (GC_OID(_string_(replace_string(GC_STRING(replace_string(string_v(m),((char*)".so"),((char*)""))),((char*)".dll"),((char*)"")))));
      { OID  mname = GC_OID(last_list(explode_string(string_v(m),GC_STRING(string_v(Core._starfs_star->value)))));
        skip_list(l,1);
        GC_OBJECT(list,OBJECT(list,Core.DYNLOADS->value))->addFast((OID)GC_OID(_string_(realpath_string(GC_STRING(append_string(string_v(m),ext))))));
        dload_string1(string_v(mname),GC_STRING(append_string(string_v(m),ext)));
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: option_usage(g0272:{"-dynload"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string33_Core_(char *g0272) { 
    return option_usage_string33_Core(g0272)->copyIfNeeded();
}


// The c++ function for: option_usage(self:{"-dynload"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string33_Core(char *self) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Load module dynamically")),
        _string_(((char*)"-dynload <m:dll/so>")),
        GC_OID(_string_(append_string(GC_STRING(append_string(((char*)"Loads module identified by the file <m> dynamically, the file extension "),((char*)"can be omitted it would be set automatically to .dll or .so depending on "))),((char*)"the host platform.")))));
      GC_UNBIND; return (Result);}
    }
  


// *********************************************************************
// * Part 3: option dispatch                                           *
// *********************************************************************
// The c++ function for: print_cmline_exception(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  print_cmline_exception_void1() { 
    
    GC_BIND;
    if (INHERIT(owner_any(value_string(((char*)"Reader"))),Kernel._module))
     { OID  p = value_module(OBJECT(module,value_string(((char*)"Reader"))),((char*)"print_exception"));
      fcall1(OBJECT(method,(*(OBJECT(property,p)->restrictions))[1])->functional,Kernel._any,_oid_(ClEnv),Kernel._void);
      }
    else { avoid_signal_handling++;
        { PortObject * p = use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value));
          ClaireException * _Zerr = GC_OBJECT(ClaireException,ClEnv->exception_I);
          method * _Zprop = ((method *) _at_property1(Kernel.self_print,OWNER(_oid_(_Zerr))));
          { ClaireHandler c_handle = ClaireHandler();
            if ERROR_IN 
            { { color(31,0);
                if (((_Zprop->functional == (NULL)) ? CTRUE : CFALSE) != CTRUE)
                 fcall1(_Zprop->functional,Kernel._object,_oid_(_Zerr),Kernel._any);
                else funcall_method1(_Zprop,_oid_(_Zerr));
                  princ_string(((char*)"\n"));
                }
              ERROR_FREE;}
            else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
            { c_handle.catchIt();{ color(31,0);
                princ_string(((char*)"\n[121] unprintable error <"));
                print_any(_oid_(OWNER(_oid_(_Zerr))));
                princ_string(((char*)">.\n"));
                }
              }
            else PREVIOUS_HANDLER;}
          color(30,0);
          use_as_output_port(p);
          avoid_signal_handling--;
          }
        }
      GC_UNBIND; POP_SIGNAL;}
  


//<sb> v3.3.35 this is our new entry point
// The c++ function for: parse_command_line(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  parse_command_line_void1() { 
    
    GC_BIND;
    if (unix_ask_void1() == CTRUE)
     { OID  prog = (*(ClEnv->params))[1];
      if ((match_wildcard_ask_string(string_v(prog),((char*)"./*")) == CTRUE) || 
          ((match_wildcard_ask_string(string_v(prog),((char*)"/*")) == CTRUE) || 
            (match_wildcard_ask_string(string_v(prog),((char*)"../*")) == CTRUE)))
       setenv_string(append_string(((char*)"_="),string_v(prog)));
      else { list * paths = GC_OBJECT(list,explode_string(GC_STRING(getenv_string(((char*)"PATH"))),((char*)":")));
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(p);
            for (START(paths); NEXT(p);)
            { GC_LOOP;
              { ClaireBoolean * g0273I;
                { ClaireBoolean *v_and;
                  { { ClaireObject *V_CC ;
                      { ClaireHandler c_handle = ClaireHandler();
                        if ERROR_IN 
                        { V_CC = contain_ask_list(entries_string2(string_v(p)),prog);
                          ERROR_FREE;}
                        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                        { c_handle.catchIt();V_CC = CFALSE;
                          }
                        else PREVIOUS_HANDLER;}
                      v_and= (ClaireBoolean *) V_CC;}
                    if (v_and == CFALSE) g0273I =CFALSE; 
                    else { v_and = isfile_ask_string(_7_string(string_v(p),string_v(prog)));
                      if (v_and == CFALSE) g0273I =CFALSE; 
                      else g0273I = CTRUE;}
                    }
                  }
                
                if (g0273I == CTRUE) { setenv_string(_7_string(GC_STRING(append_string(((char*)"_="),string_v(p))),string_v(prog)));
                    { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                    }
                  }
              GC_UNLOOP; POP_SIGNAL;}
            }
          }
        }
    { list * argv = ((list *) copy_bag(ClEnv->params));
      skip_list(argv,1);
      apply_command_line_list1(argv,CTRUE);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: apply_command_line(argv:list[string],exit?:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  apply_command_line_list1(list *argv,ClaireBoolean *exit_ask) { 
    
    GC_BIND;
    { ClaireBoolean * cmd_line_err_ask = CFALSE;
      { ClaireHandler c_handle = ClaireHandler();
        if ERROR_IN 
        { { if (exit_ask == CTRUE)
             apply_option_begin_parse_void1();
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while ((argv->length != 0))
              { GC_LOOP;
                { char * opt = string_v((*(argv))[1]);
                  skip_list(argv,1);
                  { ClaireHandler c_handle = ClaireHandler();
                    if ERROR_IN 
                    { { OID  rtest;
                        { { OID  r_some = CNULL;
                            { CL_INT loop_handle = ClEnv->cHandle;
                              OID gc_local;
                              ITERATE(r);
                              for (START(Core.option_respond->restrictions); NEXT(r);)
                              { GC_LOOP;
                                { ClaireBoolean * g0290I;
                                  { OID  g0291UU;
                                    { CL_INT loop_handle = ClEnv->cHandle;
                                      ITERATE(w);
                                      g0291UU= Kernel.cfalse;
                                      bag *w_support;
                                      w_support = GC_OBJECT(bag,enumerate_any((*(OBJECT(restriction,r)->domain))[1]));
                                      for (START(w_support); NEXT(w);)
                                      if (match_wildcard_ask_string(opt,string_v(w)) == CTRUE)
                                       { g0291UU = Kernel.ctrue;
                                        ClEnv->cHandle = loop_handle;break;}
                                      }
                                    g0290I = boolean_I_any(g0291UU);
                                    }
                                  
                                  if (g0290I == CTRUE) { r_some= (r);
                                      GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                                    }
                                GC_UNLOOP; POP_SIGNAL;}
                              }
                            rtest = r_some;
                            }
                          GC_OID(rtest);}
                        if (rtest != CNULL)
                         { restriction * r = OBJECT(restriction,rtest);
                          apply_method(((method *) r),GC_OBJECT(list,list::alloc(2,_string_(opt),_oid_(argv))));
                          }
                        else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Invalid option ~A (try ~A -h)\n")),
                            _oid_(list::alloc(2,_string_(opt),(*(ClEnv->params))[1])))));
                          }
                      ERROR_FREE;}
                    else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Core._invalid_option_argument)) == CTRUE)
                    { c_handle.catchIt();{ { CL_INT loop_handle = ClEnv->cHandle;
                          OID gc_local;
                          ITERATE(x);
                          for (START(Core.on_option_error->restrictions); NEXT(x);)
                          { GC_LOOP;
                            apply_method(OBJECT(method,x),GC_OBJECT(list,list::alloc(1,_string_(opt))));
                            GC_UNLOOP; POP_SIGNAL;}
                          }
                        color_integer(1);
                        print_option_usage_string1(opt);
                        if (argv->length != 0)
                         { CL_INT  g0274 = (CL_INT )(current_color);
                          CL_INT  g0275 = (CL_INT )(current_bold);
                          CL_INT  g0276 = g0274;
                          CL_INT  g0277 = g0275;
                          color(g0274,g0275);
                          color_princ_string1(((char*)"`REDInvalid argument "));
                          g0274= (CL_INT)((CL_INT )(current_color));
                          g0275= (CL_INT)((CL_INT )(current_bold));
                          color(g0276,g0277);
                          princ_string(string_v((*(argv))[1]));
                          color(g0274,g0275);
                          color(g0274,g0275);
                          color_princ_string1(((char*)" for option "));
                          g0274= (CL_INT)((CL_INT )(current_color));
                          g0275= (CL_INT)((CL_INT )(current_bold));
                          color(g0276,g0277);
                          princ_string(opt);
                          color(g0274,g0275);
                          color(g0274,g0275);
                          color_princ_string1(((char*)"\n"));
                          color(g0276,g0277);
                          }
                        else { CL_INT  g0278 = (CL_INT )(current_color);
                            CL_INT  g0279 = (CL_INT )(current_bold);
                            CL_INT  g0280 = g0278;
                            CL_INT  g0281 = g0279;
                            color(g0278,g0279);
                            color_princ_string1(((char*)"`REDMissing argument for option "));
                            g0278= (CL_INT)((CL_INT )(current_color));
                            g0279= (CL_INT)((CL_INT )(current_bold));
                            color(g0280,g0281);
                            princ_string(opt);
                            color(g0278,g0279);
                            color(g0278,g0279);
                            color_princ_string1(((char*)"\n"));
                            color(g0280,g0281);
                            }
                          if (exit_ask != CTRUE)
                         close_exception(ClEnv->exception_I);
                        CL_exit(1);
                        }
                      }
                    else PREVIOUS_HANDLER;}
                  }
                GC_UNLOOP;POP_SIGNAL;}
              }
            if (exit_ask == CTRUE)
             apply_option_parsed_void1();
            }
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
        { c_handle.catchIt();{ if (exit_ask != CTRUE)
             close_exception(ClEnv->exception_I);
            cmd_line_err_ask= (CTRUE);
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(x);
              for (START(Core.on_option_error->restrictions); NEXT(x);)
              { GC_LOOP;
                apply_method(OBJECT(method,x),GC_OBJECT(list,list::alloc(1,_oid_(Kernel._void))));
                GC_UNLOOP; POP_SIGNAL;}
              }
            if ((OBJECT(ClaireBoolean,Core._Zqonerror->value)) == CTRUE)
             { color_integer(1);
              { CL_INT  g0282 = (CL_INT )(current_color);
                CL_INT  g0283 = (CL_INT )(current_bold);
                CL_INT  g0284 = g0282;
                CL_INT  g0285 = g0283;
                color(g0282,g0283);
                color_princ_string1(((char*)"`RED-qonerror handled by exception:\n"));
                g0282= (CL_INT)((CL_INT )(current_color));
                g0283= (CL_INT)((CL_INT )(current_bold));
                color(g0284,g0285);
                print_cmline_exception_void1();
                color(g0282,g0283);
                color(g0284,g0285);
                }
              CL_exit(1);
              }
            else if (contain_ask_list(ClEnv->params,_string_(((char*)"-q"))) == CTRUE)
             { { CL_INT  g0286 = (CL_INT )(current_color);
                CL_INT  g0287 = (CL_INT )(current_bold);
                CL_INT  g0288 = g0286;
                CL_INT  g0289 = g0287;
                color(g0286,g0287);
                color_princ_string1(((char*)"`RED-q handled by exception:\n"));
                g0286= (CL_INT)((CL_INT )(current_color));
                g0287= (CL_INT)((CL_INT )(current_bold));
                color(g0288,g0289);
                print_cmline_exception_void1();
                color(g0286,g0287);
                color(g0288,g0289);
                }
              CL_exit(1);
              }
            print_cmline_exception_void1();
            }
          }
        else PREVIOUS_HANDLER;}
      if (exit_ask == CTRUE)
       { if ((Core.toplevel->restrictions->length != 0) && 
            ((((ClaireBoolean *) (ClaireBoolean *)(TOPLEVEL ? CTRUE : CFALSE))) == CTRUE))
         { color_integer(1);
          (*Core.toplevel)(_oid_(ClEnv));
          }
        if (cmd_line_err_ask == CTRUE)
         CL_exit(1);
        else CL_exit(0);
          }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-source-editor"},l:list) [NEW_ALLOC]
CL_EXPORT void  option_respond_string45_Core(char *opt,list *l) { 
    if (l->length != 0)
     { setenv_string(append_string(((char*)"WCL_EDITOR="),string_v((*(l))[1])));
      skip_list(l,1);
      }
    POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-source-edit"},l:list) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT void  option_respond_string46_Core(char *opt,list *l) { 
    if (l->length != 0)
     open_link_string1(string_v((*(l))[1]));
    else close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
      CL_exit(0);
    POP_SIGNAL;}
  


// The c++ function for: read_cmd_string(b:port,eos:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT char * read_cmd_string_port1(PortObject *b,char *eos) { 
    
    GC_BIND;
    { char *Result ;
      { blob * p = GC_OBJECT(blob,blob_I_void1());
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) b))) != Kernel.ctrue))
          { GC_LOOP;
            { tuple * g0292 = freadline_port4(b,set::alloc(Kernel._string,6,_string_(((char*)"\\n")),
                _string_(((char*)"\\t")),
                _string_(((char*)"\\r")),
                _string_(((char*)"\\\"")),
                _string_(((char*)"\\\\")),
                _string_(eos)));
              char * s = GC_STRING(string_v((*(g0292))[1]));
              OID  sep = GC_OID((*(g0292))[2]);
              fwrite_string2(s,p);
              if (equal(sep,_string_(((char*)""))) == CTRUE)
               close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Premature end of string.")),
                _oid_(Kernel.nil))));
              else if (equal(sep,_string_(((char*)"\\n"))) == CTRUE)
               fwrite_string2(((char*)"\n"),p);
              else if (equal(sep,_string_(((char*)"\\r"))) == CTRUE)
               fwrite_string2(((char*)"\r"),p);
              else if (equal(sep,_string_(((char*)"\\t"))) == CTRUE)
               fwrite_string2(((char*)"\t"),p);
              else if (equal(sep,_string_(((char*)"\\\""))) == CTRUE)
               fwrite_string2(((char*)"\""),p);
              else if (equal(sep,_string_(((char*)"\\\\"))) == CTRUE)
               fwrite_string2(((char*)"\\"),p);
              else { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                }
            GC_UNLOOP;POP_SIGNAL;}
          }
        { char * s = GC_STRING(string_I_blob1(p));
          fclose_port1(p);
          Result = s;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: shell_expand(s:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT char * shell_expand_string1(char *s) { 
    
    GC_BIND;
    { char *Result ;
      { blob * b = GC_OBJECT(blob,blob_I_string1(s));
        blob * res = GC_OBJECT(blob,blob_I_void1());
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) b))) != Kernel.ctrue))
          { GC_LOOP;
            { tuple * g0293 = freadline_port4(b,set::alloc(Kernel.emptySet,1,_string_(((char*)"$("))));
              char * data = GC_STRING(string_v((*(g0293))[1]));
              OID  sep = GC_OID((*(g0293))[2]);
              fwrite_string2(data,res);
              if (equal(sep,_string_(((char*)"$("))) == CTRUE)
               fwrite_string2(GC_STRING(getenv_string(GC_STRING(freadline_port1(b,((char*)")"))))),res);
              }
            GC_UNLOOP;POP_SIGNAL;}
          }
        fclose_port1(b);
        s= (GC_STRING(string_I_blob1(res)));
        fclose_port1(res);
        Result = s;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: read_option_line(f:port,opts:list[string]) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  read_option_line_port1(PortObject *f,list *opts) { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) f))) != Kernel.ctrue))
      { GC_LOOP;
        { tuple * g0294 = freadline_port4(f,set::alloc(Kernel.emptySet,8,_string_(((char*)"'")),
            _string_(((char*)" ")),
            _string_(((char*)"\n")),
            _string_(((char*)"\r")),
            _string_(((char*)"\t")),
            _string_(((char*)"%")),
            _string_(((char*)"#")),
            _string_(((char*)"\\"))));
          char * s = GC_STRING(string_v((*(g0294))[1]));
          OID  sep = GC_OID((*(g0294))[2]);
          if (equal(sep,_string_(((char*)"'"))) == CTRUE)
           { if (equal_string(s,((char*)"")) != CTRUE)
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Error handling option file ~A:~S\nseparation missing between ~S and ~S")),
              _oid_(list::alloc(4,GC_OID(Core.OPTION_PATH->value),
                Core.OPTION_LINE->value,
                _string_(s),
                sep)))));
            GC__STRING(s = freadline_port1(f,((char*)"'")), 1);
            }
          else GC__STRING(s = shell_expand_string1(s), 2);
            if (equal_string(s,((char*)"")) != CTRUE)
           { if (boolean_I_any(_oid_(opts)) != CTRUE)
             opts->addFast((OID)GC_OID(_string_(append_string(((char*)"-"),s))));
            else opts->addFast((OID)_string_(s));
              }
          if (equal(sep,_string_(((char*)"\\"))) == CTRUE)
           { freadline_port(f);
            (Core.OPTION_LINE->value= ((OID)((CL_INT)(((CL_INT)Core.OPTION_LINE->value))+(CL_INT)1)));
            }
          if ((equal(sep,_string_(((char*)"%"))) == CTRUE) || 
              (equal(sep,_string_(((char*)"#"))) == CTRUE))
           { freadline_port(f);
            sep= (_string_(((char*)"\n")));
            }
          if (equal(sep,_string_(((char*)"\n"))) == CTRUE)
           (Core.OPTION_LINE->value= ((OID)((CL_INT)(((CL_INT)Core.OPTION_LINE->value))+(CL_INT)1)));
          if (((equal(sep,_string_(((char*)"\n"))) == CTRUE) || 
                (equal(sep,_string_(((char*)""))) == CTRUE)) && 
              (opts->length != 0))
           { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
          }
        GC_UNLOOP;POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: close(self:option_instruction) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT Core_option_instruction * close_option_instruction1(Core_option_instruction *self) { 
    _void_(self->line = ((CL_INT)Core.OPTION_LINE->value));
    _void_(self->filename = string_v(Core.OPTION_PATH->value));
    POP_SIGNAL; return (self);}
  


// The c++ function for: read_option_file(b:port,ado:option_do) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  read_option_file_port1(PortObject *b,Core_option_do *ado) { 
    
    GC_BIND;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) b))) != Kernel.ctrue))
      { GC_LOOP;
        { list * opts = list::empty(Kernel._string);
          read_option_line_port1(b,opts);
          if (opts->length != 0)
           { if (equal((*(opts))[1],_string_(((char*)"-end"))) == CTRUE)
             { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
            else if (equal((*(opts))[1],_string_(((char*)"-while"))) == CTRUE)
             GC_OBJECT(list,ado->args)->addFast((OID)GC_OID(_oid_(read_option_while_port1(b,opts))));
            else if (equal((*(opts))[1],_string_(((char*)"-for"))) == CTRUE)
             GC_OBJECT(list,ado->args)->addFast((OID)GC_OID(_oid_(read_option_for_port1(b,opts))));
            else if (equal((*(opts))[1],_string_(((char*)"-if"))) == CTRUE)
             GC_OBJECT(list,ado->args)->addFast((OID)GC_OID(_oid_(read_option_if_port1(b,opts))));
            else if (equal((*(opts))[1],_string_(((char*)"-elif"))) == CTRUE)
             { if (INHERIT(ado->isa,Core._option_if))
               { _void_(CLREAD(Core_option_if,ado,other) = read_option_if_port1(b,opts));
                { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                }
              else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Syntax error near 'elif'")),
                  _oid_(Kernel.nil))));
                }
            else if (equal((*(opts))[1],_string_(((char*)"-else"))) == CTRUE)
             { if (opts->length != 1)
               close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
              if (INHERIT(ado->isa,Core._option_if))
               { { Core_option_if * g0295 = ((Core_option_if *) ado); 
                  Core_option_instruction * g0296;
                  { Core_option_do * _CL_obj = ((Core_option_do *) GC_OBJECT(Core_option_do,new_object_class(Core._option_do)));
                    g0296 = close_option_instruction1(_CL_obj);
                    }
                  _void_(g0295->other = g0296);}
                read_option_file_port1(b,GC_OBJECT(Core_option_do,((Core_option_do *) CLREAD(Core_option_if,ado,other))));
                { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                }
              else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Syntax error near 'else'")),
                  _oid_(Kernel.nil))));
                }
            else { OID  g0297UU;
                { Core_option_apply * _CL_obj = ((Core_option_apply *) GC_OBJECT(Core_option_apply,new_object_class(Core._option_apply)));
                  _void_(_CL_obj->args = opts);
                  g0297UU = _oid_(close_option_instruction1(_CL_obj));
                  }
                GC_OBJECT(list,ado->args)->addFast((OID)g0297UU);
                }
              }
          }
        GC_UNLOOP;POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: read_option_if(b:port,opts:list[string]) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT Core_option_if * read_option_if_port1(PortObject *b,list *opts) { 
    
    GC_BIND;
    if (opts->length != 2)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    { Core_option_if *Result ;
      { Core_option_if * x;
        { Core_option_instruction *V_CC ;
          { Core_option_if * _CL_obj = ((Core_option_if *) GC_OBJECT(Core_option_if,new_object_class(Core._option_if)));
            _void_(_CL_obj->test = string_v((*(opts))[2]));
            V_CC = close_option_instruction1(_CL_obj);
            }
          x= (Core_option_if *) V_CC;}
        read_option_file_port1(b,x);
        Result = x;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: read_option_while(b:port,opts:list[string]) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT Core_option_while * read_option_while_port1(PortObject *b,list *opts) { 
    
    GC_BIND;
    if (opts->length != 2)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    { Core_option_while *Result ;
      { Core_option_while * x;
        { Core_option_instruction *V_CC ;
          { Core_option_while * _CL_obj = ((Core_option_while *) GC_OBJECT(Core_option_while,new_object_class(Core._option_while)));
            _void_(_CL_obj->test = string_v((*(opts))[2]));
            V_CC = close_option_instruction1(_CL_obj);
            }
          x= (Core_option_while *) V_CC;}
        read_option_file_port1(b,x);
        Result = x;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: read_option_for(b:port,opts:list[string]) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT Core_option_for * read_option_for_port1(PortObject *b,list *opts) { 
    
    GC_BIND;
    if (((CL_INT)opts->length < (CL_INT)3) || 
        ((CL_INT)opts->length > (CL_INT)4))
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    { Core_option_for *Result ;
      { Core_option_for * x;
        { Core_option_instruction *V_CC ;
          { Core_option_for * _CL_obj = ((Core_option_for *) GC_OBJECT(Core_option_for,new_object_class(Core._option_for)));
            _void_(_CL_obj->forvar = string_v((*(opts))[2]));
            _void_(_CL_obj->forsetarg = string_v((*(opts))[3]));
            _void_(_CL_obj->such = string_v(CLREAD(slot,_at_property1(Core.such,Core._option_for),DEFAULT)));
            V_CC = close_option_instruction1(_CL_obj);
            }
          x= (Core_option_for *) V_CC;}
        if (opts->length == 4)
         _void_(x->such = string_v((*(opts))[4]));
        read_option_file_port1(b,x);
        Result = x;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: eval_options(self:option_apply) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  eval_options_option_apply1(Core_option_apply *self) { 
    (Core.OPTION_LINE->value= ((OID)self->line));
    apply_command_line_list1(((list *) copy_bag(self->args)),CFALSE);
    POP_SIGNAL;}
  


// The c++ function for: eval_options(self:option_do) [NEW_ALLOC]
CL_EXPORT void  eval_options_option_do1(Core_option_do *self) { 
    
    GC_BIND;
    (Core.OPTION_LINE->value= ((OID)self->line));
    (*Core.option_push)(_oid_(ClEnv));
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(x);
      for (START(self->args); NEXT(x);)
      (*Core.eval_options)(x);
      }
    (*Core.option_pop)(_oid_(ClEnv));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: eval_options(self:option_if) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT void  eval_options_option_if1(Core_option_if *self) { 
    
    GC_BIND;
    (Core.OPTION_LINE->value= ((OID)self->line));
    if (boolean_I_any((*Core.option_test)(_string_(self->test))) == CTRUE)
     { (*Core.option_push)(_oid_(ClEnv));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(x);
        for (START(self->args); NEXT(x);)
        (*Core.eval_options)(x);
        }
      (*Core.option_pop)(_oid_(ClEnv));
      }
    else if (((self->other == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     (*Core.eval_options)(GC_OID(_oid_(self->other)));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: eval_options(self:option_while) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT void  eval_options_option_while1(Core_option_while *self) { 
    
    GC_BIND;
    (Core.OPTION_LINE->value= ((OID)self->line));
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while ((boolean_I_any((*Core.option_test)(_string_(self->test))) == CTRUE))
      { GC_LOOP;
        (*Core.option_push)(_oid_(ClEnv));
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(x);
          for (START(self->args); NEXT(x);)
          (*Core.eval_options)(x);
          }
        (*Core.option_pop)(_oid_(ClEnv));
        (Core.OPTION_LINE->value= ((OID)self->line));
        GC_UNLOOP;POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: eval_options(self:option_for) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT void  eval_options_option_for1(Core_option_for *self) { 
    
    GC_BIND;
    (Core.OPTION_LINE->value= ((OID)self->line));
    { OID  ctx = GC_OID((*Core.option_start_loop)(_string_(self->forvar),
        _string_(self->forsetarg),
        _string_(self->such)));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((boolean_I_any((*Core.option_continue_ask)(ctx)) == CTRUE))
        { GC_LOOP;
          (*Core.option_push)(_oid_(ClEnv));
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(x);
            for (START(self->args); NEXT(x);)
            (*Core.eval_options)(x);
            }
          (*Core.option_pop)(_oid_(ClEnv));
          (Core.OPTION_LINE->value= ((OID)self->line));
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-options"},l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  option_respond_string47_Core(char *opt,list *l) { 
    
    GC_BIND;
    if (boolean_I_any(_oid_(l)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    if (isfile_ask_string(string_v((*(l))[1])) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    { OID  path = (*(l))[1];
      buffer * f = GC_OBJECT(buffer,fopen_string1(string_v(path),((char*)"r")));
      CL_INT  oldl = ((CL_INT)Core.OPTION_LINE->value);
      char * oldp = GC_STRING(string_v(Core.OPTION_PATH->value));
      skip_list(l,1);
      (Core.OPTION_LINE->value= ((OID)0));
      (Core.OPTION_PATH->value= path);
      { ClaireHandler c_handle = ClaireHandler();
        if ERROR_IN 
        { { { Core_option_do * ado;
              { Core_option_instruction *V_CC ;
                { Core_option_do * _CL_obj = ((Core_option_do *) GC_OBJECT(Core_option_do,new_object_class(Core._option_do)));
                  V_CC = close_option_instruction1(_CL_obj);
                  }
                ado= (Core_option_do *) V_CC;}
              { CL_INT loop_handle = ClEnv->cHandle;
                while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) f))) != Kernel.ctrue))
                { read_option_file_port1(f,ado);
                  POP_SIGNAL;}
                }
              fclose_port1(f);
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(x);
                bag *x_support;
                x_support = GC_OBJECT(list,ado->args);
                for (START(x_support); NEXT(x);)
                (*Core.eval_options)(x);
                }
              }
            (Core.OPTION_LINE->value= ((OID)oldl));
            (Core.OPTION_PATH->value= _string_(oldp));
            }
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
        { c_handle.catchIt();close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Error handling option file ~A:~S\n~S\n")),
            _oid_(list::alloc(3,path,
              Core.OPTION_LINE->value,
              GC_OID(_oid_(ClEnv->exception_I)))))));
          }
        else PREVIOUS_HANDLER;}
      }
    GC_UNBIND; POP_SIGNAL;}
  


//
// The c++ function for: open_link(url:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  open_link_string1(char *url) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { list * parms;
      { { list * expl = GC_OBJECT(list,explode_wildcard_string(url,((char*)"claire://source-edit#?file=*&line=*&editor=*")));
          if (expl->length == 0)
           expl= (GC_OBJECT(list,explode_wildcard_string(url,((char*)"claire://source-edit/#?file=*&line=*&editor=*"))));
          if (expl->length == 0)
           expl= (GC_OBJECT(list,explode_wildcard_string(url,((char*)"claire://source-edit#?file=*&line=*&editor=*"))));
          parms = expl;
          }
        GC_OBJECT(list,parms);}
      blob * cmd = GC_OBJECT(blob,blob_I_void1());
      if ((CL_INT)LENGTH_STRING(getenv_string(((char*)"WCL_EDITOR"))) > (CL_INT)0)
       fwrite_string2(GC_STRING(getenv_string(((char*)"WCL_EDITOR"))),cmd);
      else if (((CL_INT)3 <= (CL_INT)parms->length) && 
          ((CL_INT)LENGTH_STRING(string_v((*(parms))[3])) > (CL_INT)0))
       fwrite_string2(GC_STRING(url_decode_string(string_v((*(parms))[3]))),cmd);
      { ClaireHandler c_handle = ClaireHandler();
        if ERROR_IN 
        { { print_in_string_void();
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) cmd))) != Kernel.ctrue))
              { GC_LOOP;
                { tuple * g0298 = freadline_port4(cmd,set::alloc(Kernel.emptySet,3,_string_(((char*)"$(FILE::")),
                    _string_(((char*)"$(FILE)")),
                    _string_(((char*)"$(LINE)"))));
                  char * data = GC_STRING(string_v((*(g0298))[1]));
                  OID  sep = GC_OID((*(g0298))[2]);
                  princ_string(data);
                  if (equal(sep,_string_(((char*)"$(LINE)"))) == CTRUE)
                   { if ((CL_INT)2 <= (CL_INT)parms->length)
                     princ_string(string_v((*(parms))[2]));
                    else princ_integer(1);
                      }
                  else if (equal(sep,_string_(((char*)"$(FILE)"))) == CTRUE)
                   { if ((CL_INT)1 <= (CL_INT)parms->length)
                     princ_string(url_decode_string(string_v((*(parms))[1])));
                    }
                  else if (equal(sep,_string_(((char*)"$(FILE::"))) == CTRUE)
                   { list * bases = list::empty(Kernel._string);
                    list * reps = list::empty(Kernel._string);
                    { CL_INT loop_handle = ClEnv->cHandle;
                      OID gc_local;
                      while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) cmd))) != Kernel.ctrue))
                      { GC_LOOP;
                        bases->addFast((OID)GC_OID(_string_(freadline_port1(cmd,((char*)"::")))));
                        { tuple * g0299 = freadline_port4(cmd,set::alloc(Kernel.emptySet,2,_string_(((char*)"::")),_string_(((char*)")"))));
                          char * rep = GC_STRING(string_v((*(g0299))[1]));
                          OID  e = GC_OID((*(g0299))[2]);
                          reps->addFast((OID)_string_(rep));
                          if (equal(e,_string_(((char*)"::"))) != CTRUE)
                           { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                          }
                        GC_UNLOOP;POP_SIGNAL;}
                      }
                    if ((CL_INT)1 <= (CL_INT)parms->length)
                     { char * bs = ((char*)"");
                      CL_INT  idx = 0;
                      CL_INT  bsidx = 0;
                      char * str = GC_STRING(url_decode_string(string_v((*(parms))[1])));
                      { CL_INT loop_handle = ClEnv->cHandle;
                        OID gc_local;
                        ITERATE(e);
                        for (START(bases); NEXT(e);)
                        { GC_LOOP;
                          { ++idx;
                            if ((find_string2(str,string_v(e)) == 1) && 
                                ((CL_INT)LENGTH_STRING(string_v(e)) > (CL_INT)LENGTH_STRING(bs)))
                             { bsidx= (CL_INT)(idx);
                              GC__STRING(bs = string_v(e), 1);
                              }
                            }
                          GC_UNLOOP; POP_SIGNAL;}
                        }
                      if ((CL_INT)bsidx > (CL_INT)0)
                       princ_string(replace_string(str,bs,string_v((*(reps))[bsidx])));
                      else princ_string(str);
                        }
                    }
                  }
                GC_UNLOOP;POP_SIGNAL;}
              }
            claire_shell(end_of_string_void());
            }
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
        { c_handle.catchIt();;}
        else PREVIOUS_HANDLER;}
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: edit_link(b:bag) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  edit_link_bag1(bag *b) { 
    
    GC_BIND;
    if (((CL_INT)2 <= (CL_INT)b->length) && 
        ((Kernel._string == OWNER((*(b))[1])) && 
          (INHERIT(OWNER((*(b))[2]),Kernel._integer))))
     { princ_string(((char*)"<a href='claire://source-edit?file="));
      princ_string(url_encode_string(string_v((*(b))[1])));
      princ_string(((char*)"&line="));
      print_any((*(b))[2]);
      princ_string(((char*)"&editor="));
      princ_string(url_encode_string(GC_STRING(getenv_string(((char*)"WCL_EDITOR")))));
      princ_string(((char*)"'>"));
      (*Kernel.princ)((*(b))[1]);
      princ_string(((char*)":"));
      print_any((*(b))[2]);
      princ_string(((char*)"</a>"));
      }
    else if (((CL_INT)1 <= (CL_INT)b->length) && 
        (Kernel._string == OWNER((*(b))[1])))
     { princ_string(((char*)"<a href='claire://source-edit?file="));
      princ_string(url_encode_string(string_v((*(b))[1])));
      princ_string(((char*)"&line=1&editor="));
      princ_string(url_encode_string(GC_STRING(getenv_string(((char*)"WCL_EDITOR")))));
      princ_string(((char*)"'>"));
      (*Kernel.princ)((*(b))[1]);
      princ_string(((char*)"</a>"));
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: edit_link(src:string,l:integer,s:string) [NEW_ALLOC]
CL_EXPORT void  edit_link_string1(char *src,CL_INT l,char *s) { 
    
    GC_BIND;
    princ_string(((char*)"<a href='claire://source-edit?file="));
    princ_string(url_encode_string(src));
    princ_string(((char*)"&line="));
    print_any(((OID)l));
    princ_string(((char*)"&editor="));
    princ_string(url_encode_string(GC_STRING(getenv_string(((char*)"WCL_EDITOR")))));
    princ_string(((char*)"'>"));
    princ_string(s);
    princ_string(((char*)"</a>"));
    GC_UNBIND; POP_SIGNAL;}
  




  

extern "C" CL_EXPORT void dynLoadCore() 
{ Core.initModule("Core",mClaire.it,list::alloc(Kernel.emptySet,1,_oid_(Kernel.it)),
    "./meta",list::alloc(Kernel.emptySet,7,_string_(((char*)"method")),
      _string_(((char*)"object")),
      _string_(((char*)"function")),
      _string_(((char*)"types")),
      _string_(((char*)"signal")),
      _string_(((char*)"port")),
      _string_(((char*)"cmdline"))));
    Core.metaLoad();
    Core.it->comment = "Core";
    }
  /***** CLAIRE Compilation of file Core.cl 
         [version 3.5.0 / safety 5] *****/



CL_EXPORT CoreClass Core;

// definition of the meta-model for Core
  void CoreClass::metaLoad() { 
    
    ClEnv->module_I = it;
// definition of the properties 
    
    Core.initialize = property::make("initialize",Core.it);
    Core.uniform = property::make("uniform",Core.it);
    Core.hashinsert = property::make("hashinsert",Core.it);
    Core.hashget = property::make("hashget",Core.it);
    Core.param_I = property::make("param!",Core.it);
    Core.size = property::make("size",1,claire.it,Kernel._any,2);
    Core.end_of_string = property::make("end_of_string",claire.it);
    Core.apply = property::make("apply",claire.it);
    Core.finite_ask = property::make("finite?",claire.it);
    Core.release = property::make("release",claire.it);
    Core._at = operation::make("@",claire.it,10);
    Core.methods = property::make("methods",claire.it);
    Core.get_args = property::make("get_args",mClaire.it);
    Core._plus = operation::make("+",claire.it,20);
    Core.identified_ask = property::make("identified?",Core.it);
    Core.identical_ask = property::make("identical?",claire.it);
    Core.factor_ask = property::make("factor?",claire.it);
    Core.divide_ask = property::make("divide?",claire.it);
    Core.Id = property::make("Id",claire.it);
    Core.pair_1 = property::make("pair_1",claire.it);
    Core.pair_2 = property::make("pair_2",claire.it);
    Core.check_inverse = property::make("check_inverse",Core.it);
    Core.invert = property::make("invert",claire.it);
    Core.cause = property::make("cause",mClaire.it);
    Core.domain_I = property::make("domain!",claire.it);
    Core.class_I = property::make("class!",claire.it);
    Core.owner = property::make("owner",claire.it);
    Core.check_in = property::make("check_in",2,claire.it);
    Core.wrong = property::make("wrong",Core.it);
    Core.format = property::make("format",claire.it);
    Core.tformat = property::make("tformat",Core.it);
    Core.contradiction_I = property::make("contradiction!",claire.it);
    Core.get_stack = property::make("get_stack",mClaire.it);
    Core.put_stack = property::make("put_stack",mClaire.it);
    Core.push_I = property::make("push!",mClaire.it);
    Core.gc = property::make("gc",claire.it);
    Core.read_option_line = property::make("read_option_line",Core.it);
    Core.filename = property::make("filename",2,Core.it);
    Core.test = property::make("test",Core.it);
    Core.other = property::make("other",Core.it);
    Core.forvar = property::make("forvar",Core.it);
    Core.forsetarg = property::make("forsetarg",Core.it);
    Core.such = property::make("such",Core.it);
    Core.read_option_file = property::make("read_option_file",Core.it);
    Core.read_option_if = property::make("read_option_if",Core.it);
    Core.read_option_while = property::make("read_option_while",Core.it);
    Core.read_option_for = property::make("read_option_for",Core.it);
    Core.eval_options = property::make("eval_options",Core.it);
    Core.time_get = property::make("time_get",claire.it);
    Core.time_set = property::make("time_set",claire.it);
    Core.time_show = property::make("time_show",2,claire.it);
    Core.print_in_string = property::make("print_in_string",claire.it);
    Core.buffer_length = property::make("buffer_length",mClaire.it);
    Core.buffer_set_length = property::make("buffer_set_length",mClaire.it);
    Core.NOT = property::make("not",claire.it);
    Core.make_function = property::make("make_function",claire.it);
    Core.externC = property::make("externC",claire.it);
    Core.shell = property::make("shell",claire.it);
    Core.getenv = property::make("getenv",claire.it);
    Core._dash_dash_ask = property::make("--?",Core.it);
    Core.exit = property::make("exit",claire.it);
    Core.last = property::make("last",claire.it);
    Core.rmlast = property::make("rmlast",claire.it);
    Core.car = property::make("car",claire.it);
    Core.hashlist = property::make("hashlist",Core.it);
    Core.hashsize = property::make("hashsize",Core.it);
    Core.sort = property::make("sort",claire.it);
    Core.quicksort = property::make("quicksort",Core.it);
    Core.build_powerset = property::make("build_powerset",Core.it);
    Core.difference = property::make("difference",claire.it);
    Core.of_extract = property::make("of_extract",Core.it);
    Core.member = property::make("member",claire.it);
    Core.Address = property::make("Address",Core.it);
    Core.Oid = property::make("Oid",Core.it);
    Core.Oid_tilda = property::make("Oid~",Core.it);
    Core.get_value = property::make("get_value",claire.it);
    Core.enumerate = property::make("enumerate",Core.it);
    Core.t1 = property::make("t1",mClaire.it);
    Core.t2 = property::make("t2",mClaire.it);
    Core.tuple_I = property::make("tuple!",claire.it);
    Core.Uall = property::make("Uall",claire.it);
    Core.unique_ask = property::make("unique?",claire.it);
    Core.the = property::make("the",claire.it);
    Core.abstract_type = property::make("abstract_type",Core.it);
    Core.NEW = property::make("new",claire.it);
    Core.sqrt = property::make("sqrt",claire.it);
    Core.insert_definition = property::make("insert_definition",Core.it);
    Core.make_array = property::make("make_array",claire.it);
    Core.cpretty = property::make("cpretty",mClaire.it);
    Core.cprevious = property::make("cprevious",mClaire.it);
    Core.width = property::make("width",mClaire.it);
    Core.pprint = property::make("pprint",mClaire.it);
    Core.pbreak = property::make("pbreak",mClaire.it);
    Core.base_I = property::make("base!",mClaire.it);
    Core.set_base = property::make("set_base",mClaire.it);
    Core.index_I = property::make("index!",mClaire.it);
    Core.complete_I = property::make("complete!",mClaire.it);
    Core._Ztype = property::make("%type",mClaire.it);
    Core.update = property::make("update",mClaire.it);
    Core.make_set = property::make("make_set",claire.it);
    Core.get_symbol = property::make("get_symbol",claire.it);
    Core.time_read = property::make("time_read",2,claire.it);
    Core.first_arg_type = property::make("first_arg_type",Core.it);
    Core.second_arg_type = property::make("second_arg_type",Core.it);
    Core.meet_arg_types = property::make("meet_arg_types",Core.it);
    Core.make_copy_list = property::make("make_copy_list",claire.it);
    Core.log = property::make("log",claire.it);
    Core.new_I = property::make("new!",mClaire.it);
    Core.first_member_type = property::make("first_member_type",Core.it);
    Core.signo = property::make("signo",Core.it);
    Core.handler = property::make("handler",Core.it);
    Core.signal = property::make("signal",claire.it);
    Core.meta_sighandler = property::make("meta_sighandler",Core.it);
    Core.raise = property::make("raise",claire.it);
    Core.sigprocmask = property::make("sigprocmask",claire.it);
    Core.sigsetmask = property::make("sigsetmask",claire.it);
    Core.sigpending = property::make("sigpending",claire.it);
    Core.sigblock = property::make("sigblock",claire.it);
    Core.sigunblock = property::make("sigunblock",claire.it);
    Core.sigsuspend = property::make("sigsuspend",claire.it);
    Core.timerno = property::make("timerno",2,Core.it);
    Core.setitimer = property::make("setitimer",claire.it);
    Core.getitimer = property::make("getitimer",claire.it);
    Core.waitpid = property::make("waitpid",claire.it);
    Core.childstr = property::make("childstr",Core.it);
    Core.childpid = property::make("childpid",Core.it);
    Core.set_color = property::make("set_color",claire.it);
    Core.mtformat = property::make("mtformat",claire.it);
    Core.unix_ask = property::make("unix?",Core.it);
    Core.refine_append_of = property::make("refine_append_of",Core.it);
    Core.append_type = property::make("append_type",Core.it);
    Core.cast_I_type = property::make("cast!_type",Core.it);
    Core.prealloc_set_type = property::make("prealloc_set_type",Core.it);
    Core.prealloc_list_type = property::make("prealloc_list_type",Core.it);
    Core.make_list_type = property::make("make_list_type",Core.it);
    Core.strffloat = property::make("strffloat",claire.it);
    Core.print_option_index = property::make("print_option_index",Core.it);
    Core.print_var = property::make("print_var",Core.it);
    Core.print_option = property::make("print_option",Core.it);
    Core.print_module = property::make("print_module",Core.it);
    Core.parse_var = property::make("parse_var",Core.it);
    Core.parse_option = property::make("parse_option",Core.it);
    Core.print_back_option_usage = property::make("print_back_option_usage",Core.it);
    Core.print_back_option_help = property::make("print_back_option_help",Core.it);
    Core.find_option_usage = property::make("find_option_usage",Core.it);
    Core.print_option_usage = property::make("print_option_usage",Core.it);
    Core.apply_option_parsed = property::make("apply_option_parsed",Core.it);
    Core.number_ask = property::make("number?",Core.it);
    Core.print_cmline_exception = property::make("print_cmline_exception",Core.it);
    Core.parse_command_line = property::make("parse_command_line",Core.it);
    Core.set_user = property::make("set_user",claire.it);
    Core.putc = property::make("putc",claire.it);
    Core.flush = property::make("flush",claire.it);
    Core.eof_ask = property::make("eof?",claire.it);
    Core.fopen = property::make("fopen",claire.it);
    Core.firstc = property::make("firstc",Core.it);
    Core.closed_ask = property::make("closed?",Core.it);
    Core.filters = property::make("filters",Core.it);
    Core.dev = property::make("dev",Core.it);
    Core.target = property::make("target",claire.it);
    Core.close_target_ask = property::make("close_target?",Core.it);
    Core.get_top_most = property::make("get_top_most",Core.it);
    Core.get_device = property::make("get_device",Core.it);
    Core.filter_I = property::make("filter!",claire.it);
    Core.close_target_I = property::make("close_target!",claire.it);
    Core.remain_to_read = property::make("remain_to_read",claire.it);
    Core.getc = property::make("getc",claire.it);
    Core.unget = property::make("unget",claire.it);
    Core.pending = property::make("pending",Core.it);
    Core.line_buffer_I = property::make("line_buffer!",claire.it);
    Core.duplicate = property::make("duplicate",Core.it);
    Core.fskip = property::make("fskip",claire.it);
    Core.get_filter = property::make("get_filter",claire.it);
    Core.null_I = property::make("null!",claire.it);
    Core.data = property::make("data",Core.it);
    Core.alloc_length = property::make("alloc_length",Core.it);
    Core.read_index = property::make("read_index",Core.it);
    Core.write_index = property::make("write_index",Core.it);
    Core.write_attempt = property::make("write_attempt",Core.it);
    Core.remain_for_write = property::make("remain_for_write",Core.it);
    Core.blob_I = property::make("blob!",claire.it);
    Core.shutdown = property::make("shutdown",claire.it);
    Core.set_length = property::make("set_length",claire.it);
    Core.left_to_read = property::make("left_to_read",Core.it);
    Core.reverser_I = property::make("reverser!",claire.it);
    Core.pending_r = property::make("pending_r",Core.it);
    Core.pending_w = property::make("pending_w",Core.it);
    Core.buffer_I = property::make("buffer!",claire.it);
    Core.reset_buffer = property::make("reset_buffer",claire.it);
    Core.fill_read_buffer = property::make("fill_read_buffer",Core.it);
    Core.written_bytes = property::make("written_bytes",claire.it);
    Core.read_bytes = property::make("read_bytes",claire.it);
    Core.byte_counter_I = property::make("byte_counter!",claire.it);
    Core.written_lines = property::make("written_lines",claire.it);
    Core.read_lines = property::make("read_lines",claire.it);
    Core.line_counter_I = property::make("line_counter!",claire.it);
    Core.fd = property::make("fd",Core.it);
    Core.eof_reached_ask = property::make("eof_reached?",Core.it);
    Core.terminal_ask = property::make("terminal?",Core.it);
    Core.select_ask = property::make("select?",claire.it);
    Core.get_descriptor = property::make("get_descriptor",Core.it);
    Core.file_path = property::make("file_path",Core.it);
    Core.locked_ask = property::make("locked?",Core.it);
    Core.mode = property::make("mode",2,Core.it);
    Core.disk_file_I = property::make("disk_file!",Core.it);
    Core.get_disk_file = property::make("get_disk_file",Core.it);
    Core.pipe_I = property::make("pipe!",Core.it);
    Core.address = property::make("address",Core.it);
    Core.tcpport = property::make("tcpport",Core.it);
    Core.gethostname = property::make("gethostname",claire.it);
    Core.client_I = property::make("client!",claire.it);
    Core.connect = property::make("connect",Core.it);
    Core.server_I = property::make("server!",claire.it);
    Core.linger = property::make("linger",claire.it);
    Core.accept = property::make("accept",claire.it);
    Core.socketpair = property::make("socketpair",claire.it);
    Core.print_source_location = property::make("print_source_location",Core.it);
    Core.get_location = property::make("get_location",Core.it);
    Core.line_offset = property::make("line_offset",claire.it);
    Core.prev_line_offset = property::make("prev_line_offset",claire.it);
    Core.fork = property::make("fork",claire.it);
    Core.forker_ask = property::make("forker?",claire.it);
    Core.forked_ask = property::make("forked?",claire.it);
    Core.reopen = property::make("reopen",claire.it);
    Core.should_trace_ask = property::make("should_trace?",Core.it);
    Core.child_comm = property::make("child_comm",2,Core.it);
    Core.popen = property::make("popen",claire.it);
    Core.bqexpand = property::make("bqexpand",claire.it);
    Core.tan = property::make("tan",claire.it);
    Core.edit_link = property::make("edit_link",Core.it);
    Core.cos = property::make("cos",claire.it);
    Core.sin = property::make("sin",claire.it);
    Core.acos = property::make("acos",claire.it);
    Core.asin = property::make("asin",claire.it);
    Core.atan = property::make("atan",claire.it);
    Core.tanh = property::make("tanh",claire.it);
    Core.cosh = property::make("cosh",claire.it);
    Core.sinh = property::make("sinh",claire.it);
    Core.fclose = property::make("fclose",claire.it);
    Core.chroot = property::make("chroot",claire.it);
    Core.inner_print = property::make("inner_print",Core.it);
    Core.exitcode = property::make("exitcode",2,Core.it);
    Core.clob_I = property::make("clob!",claire.it);
    Core.cl_sizeof = property::make("sizeof",claire.it);
    Core.filepos = property::make("filepos",claire.it);
    Core.setfilepos = property::make("setfilepos",claire.it);
    Core.setfileend = property::make("setfileend",claire.it);
    Core.readable_ask = property::make("readable?",claire.it);
    Core.writable_ask = property::make("writable?",claire.it);
    Core.read_I = property::make("read!",claire.it);
    Core.write_I = property::make("write!",claire.it);
    Core.char_star_I = property::make("char*!",claire.it);
    Core.shell_expand = property::make("shell_expand",claire.it);
    Core.open_link = property::make("open_link",Core.it);
    Core.apply_command_line = property::make("apply_command_line",Core.it);
    Core.read_cmd_string = property::make("read_cmd_string",Core.it);
    Core.apply_option_begin_parse = property::make("apply_option_begin_parse",Core.it);
    Core.num = property::make("num",Core.it);
    Core.step_ask = property::make("step?",2,Core.it);
    Core.frame_source = property::make("frame_source",Core.it);
    Core.compiled_ask = property::make("compiled?",2,Core.it);
    Core.line = property::make("line",Core.it);
    Core.column = property::make("column",Core.it);
    Core.catch_ask = property::make("catch?",2,Core.it);
    Core.new_ask = property::make("new?",Core.it);
    Core.prev = property::make("prev",Core.it);
    Core.next = property::make("next",Core.it);
    Core.reset_frame_stack = property::make("reset_frame_stack",Core.it);
    Core.push_frame = property::make("push_frame",Core.it);
    Core.pop_frame = property::make("pop_frame",Core.it);
    Core.push_arg = property::make("push_arg",Core.it);
    Core.push_var = property::make("push_var",Core.it);
    Core.pop_var = property::make("pop_var",Core.it);
    Core.update_var = property::make("update_var",Core.it);
    Core.update_location = property::make("update_location",Core.it);
    Core.break_if_needed = property::make("break_if_needed",Core.it);
    Core.push_handle = property::make("push_handle",Core.it);
    Core.pop_handle = property::make("pop_handle",Core.it);
    Core.push_handle_frame = property::make("push_handle_frame",Core.it);
    Core.dload = property::make("dload",claire.it);
    
    // instructions from module sources 
    
    GC_BIND;
{ (Core.vars = property::make("vars",1,claire.it,Kernel._any,0));
      ;}
    
    { (Core.dimension = property::make("dimension",1,claire.it,Kernel._any,0));
      ;}
    
    { (Kernel.version = property::make("version",1,claire.it,Kernel._any,0));
      ;}
    
    (Core._ephemeral_object = ClaireClass::make("ephemeral_object",Kernel._object,claire.it));
    
    { (Core._lambda = ClaireClass::make("lambda",Kernel._object,claire.it));
      CL_ADD_SLOT(Core._lambda,lambda,Core.vars,vars,Kernel._list,CNULL);
      CL_ADD_SLOT(Core._lambda,lambda,Kernel.body,body,Kernel._any,CNULL);
      CL_ADD_SLOT(Core._lambda,lambda,Core.dimension,dimension,Kernel._integer,CNULL);
      }
    
    { set_range_property(Kernel.formula,Kernel._method,Core._lambda);
      ephemeral_class(Core._ephemeral_object);
      final_class(Kernel._method);
      }
    
    { (Core.execute = property::make("execute",1,claire.it,Kernel._any,0));
      ;}
    
    { (Core.debug = property::make("debug",2,claire.it,Kernel._any,0));
      ;}
    
    { (Core.eval_message = property::make("eval_message",1,claire.it,Kernel._any,0));
      ;}
    
    { (Core.noeval_message = property::make("noeval_message",1,Core.it,Kernel._any,0));
      ;}
    
    { (Core.eval = property::make("eval",1,claire.it,Kernel._any,0));
      ;}
    
    { (Core.call = property::make("call",1,claire.it,Kernel._any,0));
      ;}
    
    { (Core.self_eval = property::make("self_eval",2,claire.it,Kernel._any,0));
      ;}
    
    { (Core.read = property::make("read",2,claire.it,Kernel._any,0));
      ;}
    
    { (Core.inlineok_ask = property::make("inlineok?",2,claire.it,Kernel._any,0));
      ;}
    
    { (Kernel.restore_state = property::make("restore_state",1,mClaire.it,Kernel._any,0));
      ;}
    
    { (Core.hold_ask = property::make("hold?",2,claire.it,Kernel._any,0));
      ;}
    
    { (Core.write = property::make("write",1,claire.it,Kernel._any,0));
      ;}
    
    { (Core.range_is_wrong = property::make("range_is_wrong",1,claire.it,Kernel._any,0));
      ;}
    
    { (Core.update_plus = property::make("update+",1,Core.it,Kernel._any,0));
      ;}
    
    { (Core.update_dash = property::make("update-",1,Core.it,Kernel._any,0));
      ;}
    
    { (Core.add_value = property::make("add_value",1,claire.it,Kernel._any,0));
      ;}
    
    { (Core.known_ask = property::make("known?",1,claire.it,Kernel._any,0));
      ;}
    
    { (Core.unknown_ask = property::make("unknown?",1,claire.it,Kernel._any,0));
      ;}
    
    { (Core.erase = property::make("erase",1,claire.it,Kernel._any,0));
      ;}
    
    { (Core.set_range = property::make("set_range",2,claire.it,Kernel._any,0));
      ;}
    
    { (Core.put_store = property::make("put_store",2,claire.it,Kernel._any,0));
      ;}
    
    { (Core.matching_ask = property::make("matching?",1,Core.it,Kernel._any,0));
      ;}
    
    { (Core.vmatch_ask = property::make("vmatch?",1,Core.it,Kernel._any,0));
      ;}
    
    { (Core.tmatch_ask = property::make("tmatch?",1,Core.it,Kernel._any,0));
      ;}
    
    { (Core.main = property::make("main",2,claire.it,Kernel._any,0));
      ;}
    
    { (Core.undefined_debug = property::make("undefined_debug",2,Core.it,Kernel._any,0));
      ;}
    
    Kernel.index_jump->addMethod(list::domain(1,Kernel._integer),Kernel._void,
    	0,_function_(index_jump_integer1,"index_jump_integer1"));
    
    Core.eval_message->addMethod(list::domain(4,Kernel._property,
      Kernel._object,
      Kernel._integer,
      Kernel._boolean),Kernel._any,
    	NEW_ALLOC,_function_(eval_message_property,"eval_message_property"));
    
    Core.noeval_message->addMethod(list::domain(2,Kernel._property,Kernel._integer),Kernel._any,
    	NEW_ALLOC,_function_(noeval_message_property2,"noeval_message_property2"));
    
    Core.execute->addMethod(list::domain(3,Kernel._method,Kernel._integer,Kernel._boolean),Kernel._any,
    	NEW_ALLOC,_function_(execute_method,"execute_method"));
    
    Core.eval->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(eval_any,"eval_any"));
    
    Core.self_eval->addMethod(list::domain(1,Kernel._object),Kernel._any,
    	RETURN_ARG,_function_(self_eval_ClaireObject,"self_eval_ClaireObject"));
    
    { ClaireFunction * f = ((ClaireFunction *) _function_(self_eval_ClaireObject,"self_eval_ClaireObject"));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(x);
        bag *x_support;
        x_support = Kernel._class->instances;
        for (START(x_support); NEXT(x);)
        _void_(OBJECT(ClaireClass,x)->evaluate = f);
        }
      }
    
    Core.inlineok_ask->addMethod(list::domain(2,Kernel._method,Kernel._string),Kernel._method,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT,_function_(inlineok_ask_method,"inlineok?_method"));
    
    Kernel.get->addMethod(list::domain(2,Kernel._slot,Kernel._object),Kernel._any,
    	0,_function_(get_slot,"get_slot"));
    
    Kernel.put->addMethod(list::domain(3,Kernel._slot,Kernel._object,Kernel._any),Kernel._any,
    	SLOT_UPDATE+RETURN_ARG,_function_(put_slot,"put_slot"));
    
    Kernel.get->addMethod(list::domain(2,Kernel._property,Kernel._object),Kernel._any,
    	NEW_ALLOC,_function_(get_property,"get_property"));
    
    Kernel.funcall->addMethod(list::domain(2,Kernel._property,Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(funcall_property,"funcall_property"));
    
    Core.read->addMethod(list::domain(2,Kernel._property,Kernel._object),Kernel._any,
    	NEW_ALLOC,_function_(read_property,"read_property"));
    
    Core.hold_ask->addMethod(list::domain(3,Kernel._property,Kernel._object,Kernel._any),Kernel._boolean,
    	NEW_ALLOC,_function_(hold_ask_property,"hold?_property"));
    
    Core.write->addMethod(list::domain(3,Kernel._property,Kernel._object,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(write_property,"write_property"));
    
    Core.range_is_wrong->addMethod(list::domain(2,Kernel._slot,Kernel._any),Kernel._any,
    	0,_function_(range_is_wrong_slot,"range_is_wrong_slot"));
    
    Kernel.put->addMethod(list::domain(5,Kernel._property,
      Kernel._object,
      Kernel._integer,
      Kernel._class,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(put_property1,"put_property1"));
    
    Core.update->addMethod(list::domain(5,Kernel._property,
      Kernel._object,
      Kernel._integer,
      Kernel._class,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(update_property,"update_property"));
    
    Core.update_plus->addMethod(list::domain(3,Kernel._relation,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(update_plus_relation,"update+_relation"));
    
    Core.update_dash->addMethod(list::domain(3,Kernel._relation,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(update_dash_relation,"update-_relation"));
    
    Kernel.add_I->addMethod(list::domain(4,Kernel._property,
      Kernel._object,
      Kernel._integer,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(add_I_property,"add!_property"));
    
    Core.add_value->addMethod(list::domain(5,Kernel._property,
      Kernel._object,
      Kernel._integer,
      Kernel._bag,
      Kernel._any),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(add_value_property,"add_value_property"));
    
    Kernel.add->addMethod(list::domain(3,Kernel._property,Kernel._object,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(add_property,"add_property"));
    
    Core.known_ask->addMethod(list::domain(2,Kernel._property,Kernel._object),Kernel._boolean,
    	NEW_ALLOC,_function_(known_ask_property,"known?_property"));
    
    Core.unknown_ask->addMethod(list::domain(2,Kernel._property,Kernel._object),Kernel._boolean,
    	NEW_ALLOC,_function_(unknown_ask_property,"unknown?_property"));
    
    Kernel._delete->addMethod(list::domain(3,Kernel._property,Kernel._object,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(delete_property,"delete_property"));
    
    Core.erase->addMethod(list::domain(2,Kernel._property,Kernel._object),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(erase_property,"erase_property"));
    
    Core.set_range->addMethod(list::domain(3,Kernel._property,Kernel._class,Kernel._type),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(set_range_property,"set_range_property"));
    
    Core.put_store->addMethod(list::domain(4,Kernel._property,
      Kernel._object,
      Kernel._any,
      Kernel._boolean),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(put_store_property2,"put_store_property2"));
    
    { (Core.multi_ask = property::make("multi?",1,claire.it,Kernel._any,0));
      ;}
    
    Core.multi_ask->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	0,_function_(multi_ask_any,"multi?_any"));
    
    Kernel.fastcall->addMethod(list::domain(3,Kernel._relation,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(fastcall_relation2,"fastcall_relation2"));
    
    { (Core.join = (operation *) Kernel._operation->instantiate("join",claire.it));
      ;}
    
    Core.insert_definition->addMethod(list::domain(2,Kernel._property,Kernel._restriction),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(insert_definition_property,"insert_definition_property"));
    
    Core.initialize->addMethod(list::domain(3,Kernel._restriction,Kernel._class,Kernel._list),Kernel._list,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(initialize_restriction1,"initialize_restriction1"));
    
    Core.uniform->addMethod(list::domain(1,Kernel._restriction),Kernel._boolean,
    	NEW_ALLOC,_function_(uniform_restriction,"uniform_restriction"));
    
    Core.uniform->addMethod(list::domain(1,Kernel._property),Kernel._boolean,
    	NEW_ALLOC,_function_(uniform_property,"uniform_property"));
    
    Core.initialize->addMethod(list::domain(2,Kernel._restriction,Kernel._list),Kernel._list,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(initialize_restriction2,"initialize_restriction2"));
    
    Core.hashinsert->addMethod(list::domain(1,Kernel._restriction),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(hashinsert_restriction,"hashinsert_restriction"));
    
    Core.hashinsert->addMethod(list::domain(2,Kernel._class,Kernel._method),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(hashinsert_class,"hashinsert_class"));
    
    Core.hashinsert->addMethod(list::domain(2,Kernel._list,Kernel._method),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(hashinsert_list,"hashinsert_list"));
    
    Core.hashget->addMethod(list::domain(2,Kernel._class,Kernel._property),Kernel._object,
    	RETURN_ARG,_function_(hashget_class,"hashget_class"));
    
    Core.join->addMethod(list::domain(2,Kernel._list,Kernel._list),Kernel._boolean,
    	NEW_ALLOC,_function_(join_list,"join_list"));
    
    Core._at->addMethod(list::domain(2,Kernel._property,Kernel._class),Kernel._object,
    	NEW_ALLOC+RETURN_ARG,_function_(_at_property1,"@_property1"));
    
    Core._at->addMethod(list::domain(2,Kernel._property,Kernel._list),Kernel._object,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(_at_property2,"@_property2"));
    
    Core.matching_ask->addMethod(list::domain(3,Kernel._list,Kernel._integer,Kernel._integer),Kernel._boolean,
    	NEW_ALLOC,_function_(matching_ask_list,"matching?_list"));
    
    Core.vmatch_ask->addMethod(list::domain(3,Kernel._any,Kernel._any,Kernel._integer),Kernel._boolean,
    	NEW_ALLOC+SLOT_UPDATE,_function_(vmatch_ask_any,"vmatch?_any"));
    
    Core.tmatch_ask->addMethod(list::domain(2,Kernel._list,Kernel._list),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(tmatch_ask_list,"tmatch?_list"));
    
    Core.tmatch_ask->addMethod(list::domain(3,Kernel._any,Kernel._any,Kernel._list),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(tmatch_ask_any,"tmatch?_any"));
    
    Kernel.find_which->addMethod(list::domain(4,Kernel._list,
      Kernel._class,
      Kernel._integer,
      Kernel._integer),Kernel._object,
    	0,_function_(find_which_list1,"find_which_list1"));
    
    Kernel.find_which->addMethod(list::domain(4,Kernel._class,
      Kernel._list,
      Kernel._integer,
      Kernel._integer),Kernel._object,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(find_which_class1,"find_which_class1"));
    
    Core.release->addMethod(list::domain(1,Kernel._void),Kernel._string,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(release_void,"release_void"));
    
    Core.get_args->addMethod(list::domain(1,Kernel._integer),Kernel._list,
    	NEW_ALLOC,_function_(get_args_integer,"get_args_integer"));
    
    Kernel.funcall->addMethod(list::domain(2,Kernel._method,Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(funcall_method1,"funcall_method1"));
    
    Kernel.funcall->addMethod(list::domain(3,Kernel._method,Kernel._any,Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(funcall_method2,"funcall_method2"));
    
    Kernel.funcall->addMethod(list::domain(4,Kernel._method,
      Kernel._any,
      Kernel._any,
      Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(funcall_method3,"funcall_method3"));
    
    Core.apply->addMethod(list::domain(3,Kernel._function,Kernel._list,Kernel._list),Kernel._any,
    	0,_function_(apply_function,"apply_function"));
    
    Core.call->addMethod(list::domain(2,Kernel._property,Kernel._listargs),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE,_function_(call_property,"call_property"));
    
    Core.apply->addMethod(list::domain(2,Kernel._property,Kernel._list),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE,_function_(apply_property,"apply_property"));
    
    Core.apply->addMethod(list::domain(2,Kernel._method,Kernel._list),Kernel._any,
    	NEW_ALLOC,_function_(apply_method,"apply_method"));
    
    Core.identified_ask->addMethod(list::domain(1,Kernel._class),Kernel._boolean,
    	0,_function_(identified_ask_class,"identified?_class"));
    
    Core.identical_ask->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._boolean,
    	0,_function_(identical_ask_any,"identical?_any"));
    
    Kernel.put->addMethod(list::domain(3,Kernel._property,Kernel._object,Kernel._any),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(put_property2,"put_property2"));
    
    Core.add_value->addMethod(list::domain(3,Kernel._property,Kernel._object,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(add_value_property3,"add_value_property3"));
    
    _void_(Kernel.nth->addMethod(list::domain(2,Kernel._table,Kernel._any),Kernel._any,
    	0,_function_(nth_table1,"nth_table1"))->typing = _oid_(_function_(nth_table1_type,"nth_table1_type")));
    
    _void_(Kernel.get->addMethod(list::domain(2,Kernel._table,Kernel._any),Kernel._any,
    	RETURN_ARG,_function_(get_table,"get_table"))->typing = _oid_(_function_(get_table_type,"get_table_type")));
    
    Kernel.nth_equal->addMethod(list::domain(3,Kernel._table,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(nth_equal_table1,"nth=_table1"));
    
    Kernel.nth_put->addMethod(list::domain(3,Kernel._table,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(nth_put_table,"nth_put_table"));
    
    Kernel.put->addMethod(list::domain(3,Kernel._table,Kernel._any,Kernel._any),Kernel._void,
    	BAG_UPDATE,_function_(put_table,"put_table"));
    
    Kernel.add->addMethod(list::domain(3,Kernel._table,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(add_table,"add_table"));
    
    Kernel.add_I->addMethod(list::domain(3,Kernel._table,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(add_I_table,"add!_table"));
    
    Core.add_value->addMethod(list::domain(4,Kernel._table,
      Kernel._integer,
      Kernel._bag,
      Kernel._any),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE,_function_(add_value_array,"add_value_array"));
    
    Core.add_value->addMethod(list::domain(3,Kernel._table,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE,_function_(add_value_table3,"add_value_table3"));
    
    Kernel._delete->addMethod(list::domain(3,Kernel._table,Kernel._any,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(delete_table,"delete_table"));
    
    _void_(Kernel.nth->addMethod(list::domain(3,Kernel._table,Kernel._any,Kernel._any),Kernel._any,
    	0,_function_(nth_table2,"nth_table2"))->typing = _oid_(_function_(nth_table2_type,"nth_table2_type")));
    
    Kernel.nth_equal->addMethod(list::domain(4,Kernel._table,
      Kernel._any,
      Kernel._any,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(nth_equal_table2,"nth=_table2"));
    
    Kernel.get_index->addMethod(list::domain(2,Kernel._table,Kernel._any),Kernel._integer,
    	RETURN_ARG,_function_(get_index_table1,"get_index_table1"));
    
    Kernel.get_index->addMethod(list::domain(3,Kernel._table,Kernel._integer,Kernel._integer),Kernel._integer,
    	RETURN_ARG,_function_(get_index_table2,"get_index_table2"));
    
    Core.erase->addMethod(list::domain(1,Kernel._table),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(erase_table,"erase_table"));
    
    Kernel.self_print->addMethod(list::domain(1,Kernel._table),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_table1_Core,"self_print_table1_Core"));
    
    { (Core.StopProperty = (table *) Kernel._table->instantiate("StopProperty",Core.it));
      _void_(Core.StopProperty->multivalued_ask = Kernel._list);
      _void_(Core.StopProperty->range = Kernel._list);
      _void_(Core.StopProperty->params = _oid_(Kernel._any));
      _void_(Core.StopProperty->domain = Kernel._property);
      _void_(Core.StopProperty->graph = make_list_integer(29,CNULL));
      _void_(Core.StopProperty->DEFAULT = CNULL);
      }
    
    Kernel.funcall->addMethod(list::domain(2,Core._lambda,Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(funcall_lambda1,"funcall_lambda1"));
    
    Kernel.funcall->addMethod(list::domain(3,Core._lambda,Kernel._any,Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(funcall_lambda2,"funcall_lambda2"));
    
    Kernel.funcall->addMethod(list::domain(4,Core._lambda,
      Kernel._any,
      Kernel._any,
      Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(funcall_lambda3,"funcall_lambda3"));
    
    { (Core.pname = property::make("pname",2,mClaire.it,Kernel._any,0));
      ;}
    
    Core.check_inverse->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(check_inverse_any,"check_inverse_any"));
    
    { _void_(Kernel._relation->open = 0);
      update_property(Kernel.inverse,
        Kernel.inverse,
        8,
        Kernel._object,
        _oid_(Kernel.inverse));
      _void_(Kernel.inverse->if_write = _oid_(CLREAD(method,_at_property1(Core.check_inverse,Kernel._any),functional)));
      }
    
    Core.invert->addMethod(list::domain(2,Kernel._relation,Kernel._any),Kernel._bag,
    	NEW_ALLOC,_function_(invert_relation,"invert_relation"));
    
    Core.domain_I->addMethod(list::domain(1,Kernel._restriction),Kernel._class,
    	NEW_ALLOC+RETURN_ARG,_function_(domain_I_restriction,"domain!_restriction"));
    
    Core.methods->addMethod(list::domain(2,Kernel._class,Kernel._class),Kernel._set,
    	NEW_ALLOC,_function_(methods_class,"methods_class"));
    
    { (Core.reify = property::make("reify",1,claire.it,Kernel._any,0));
      ;}
    
    Core.reify->addMethod(list::domain(1,Kernel._listargs),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(reify_listargs,"reify_listargs"));
    
    { (Core._star_stararg = property::make("**arg",0,Core.it,Kernel._any,0));
      _void_(Core._star_stararg->open = 0);
      ;}
    
    { (Core.args = property::make("args",0,claire.it,Kernel._any,0));
      _void_(Core.args->open = 0);
      ;}
    
    { (Kernel.value = property::make("value",1,claire.it,Kernel._any,0));
      ;}
    
    { (Core._general_error = ClaireClass::make("general_error",Kernel._error,claire.it));
      CL_ADD_SLOT(Core._general_error,general_error,Core.cause,cause,Kernel._any,CNULL);
      CL_ADD_SLOT(Core._general_error,general_error,Kernel.arg,arg,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Core._general_error),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_general_error_Core,"self_print_general_error_Core"));
    
    { (Core._read_slot_error = ClaireClass::make("read_slot_error",Kernel._error,claire.it));
      CL_ADD_SLOT(Core._read_slot_error,read_slot_error,Kernel.arg,arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Core._read_slot_error,read_slot_error,Core.wrong,wrong,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Core._read_slot_error),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_read_slot_error_Core,"self_print_read_slot_error_Core"));
    
    { (Core._range_error = ClaireClass::make("range_error",Kernel._error,claire.it));
      CL_ADD_SLOT(Core._range_error,range_error,Core.cause,cause,Kernel._any,CNULL);
      CL_ADD_SLOT(Core._range_error,range_error,Kernel.arg,arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Core._range_error,range_error,Core.wrong,wrong,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Core._range_error),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_range_error_Core,"self_print_range_error_Core"));
    
    { (Core._selector_error = ClaireClass::make("selector_error",Kernel._error,claire.it));
      CL_ADD_SLOT(Core._selector_error,selector_error,Kernel.selector,selector,Kernel._any,CNULL);
      CL_ADD_SLOT(Core._selector_error,selector_error,Kernel.arg,arg,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Core._selector_error),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_selector_error_Core,"self_print_selector_error_Core"));
    
    { (Core._return_error = ClaireClass::make("return_error",Kernel._error,claire.it));
      CL_ADD_SLOT(Core._return_error,return_error,Kernel.arg,arg,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Core._return_error),Kernel._void,
    	0,_function_(self_print_return_error_Core,"self_print_return_error_Core"));
    
    { (Core._global_variable = ClaireClass::make("global_variable",Kernel._system_thing,claire.it));
      CL_ADD_SLOT(Core._global_variable,global_variable,Kernel.value,value,Kernel._any,CNULL);
      CL_ADD_SLOT(Core._global_variable,global_variable,Kernel.range,range,Kernel._type,_oid_(Kernel._any));
      CL_ADD_SLOT(Core._global_variable,global_variable,Kernel.store_ask,store_ask,Kernel._boolean,Kernel.cfalse);
      }
    
    Kernel.close->addMethod(list::domain(1,Core._global_variable),Core._global_variable,
    	SAFE_RESULT,_function_(close_global_variable,"close_global_variable"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core.err_l = (global_variable *) Core._global_variable->instantiate("err_l",Core.it));
      _void_(_CL_obj->range = Kernel._list);
      _void_(_CL_obj->value = _oid_(list::alloc(Kernel._any,2,((OID)0),((OID)0))));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Kernel.self_print->addMethod(list::domain(1,Kernel._system_error),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_system_error_Core,"self_print_system_error_Core"));
    
    (Core._contradiction = ClaireClass::make("contradiction",Kernel._exception,claire.it));
    
    Kernel.self_print->addMethod(list::domain(1,Core._contradiction),Kernel._void,
    	0,_function_(self_print_contradiction_Core,"self_print_contradiction_Core"));
    
    Core.format->addMethod(list::domain(2,Kernel._string,Kernel._list),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(format_string,"format_string"));
    
    Core.tformat->addMethod(list::domain(3,Kernel._string,Kernel._integer,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(tformat_string,"tformat_string"));
    
    { (Core.on_trace = property::make("on_trace",3,claire.it,Kernel._any,0));
      _void_(Core.on_trace->open = 3);
      ;}
    
    Core.should_trace_ask->addMethod(list::domain(2,Kernel._module,Kernel._integer),Kernel._boolean,
    	0,_function_(should_trace_ask_module1,"should_trace?_module1"));
    
    Core.mtformat->addMethod(list::domain(4,Kernel._module,
      Kernel._string,
      Kernel._integer,
      Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(mtformat_module1,"mtformat_module1"));
    
    Kernel.princ->addMethod(list::domain(1,Kernel._bag),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(princ_bag,"princ_bag"));
    
    { (Core._inf_equal2 = (operation *) Kernel._operation->instantiate("<=2",claire.it));
      ;}
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core.contradiction_occurs = (global_variable *) Core._global_variable->instantiate("contradiction_occurs",claire.it));
      _void_(_CL_obj->range = Core._contradiction);
      _void_(_CL_obj->value = _oid_(new_object_class(Core._contradiction)));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Core.contradiction_I->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	RETURN_ARG,_function_(contradiction_I_void,"contradiction!_void"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core.nil = (global_variable *) Core._global_variable->instantiate("nil",claire.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(Kernel.nil));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Core.claire_date = (global_variable *) Core._global_variable->instantiate("claire_date",claire.it));
      _void_(_CL_obj->range = Kernel._string);
      _void_(_CL_obj->value = _string_(((char*)"Sun Oct 30 09:54:15 2011\n")));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Core._eof = (global_variable *) Core._global_variable->instantiate("EOF",claire.it));
      _void_(_CL_obj->range = Kernel._char);
      _void_(_CL_obj->value = _oid_(char_I_integer(255)));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Core.EOS = (global_variable *) Core._global_variable->instantiate("EOS",claire.it));
      _void_(_CL_obj->range = Kernel._char);
      _void_(_CL_obj->value = _oid_(char_I_integer(0)));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Core._starfs_star = (global_variable *) Core._global_variable->instantiate("*fs*",claire.it));
      _void_(_CL_obj->range = Kernel._string);
      { global_variable * g0300 = _CL_obj; 
        OID  g0301;
        if ((((ClaireBoolean *) (ClaireBoolean *)(
#ifdef CLPC
CTRUE
#else
CFALSE
#endif
))) == CTRUE)
         g0301 = _string_(((char*)"\\"));
        else g0301 = _string_(((char*)"/"));
          _void_(g0300->value = g0301);}
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Core._starps_star = (global_variable *) Core._global_variable->instantiate("*ps*",claire.it));
      _void_(_CL_obj->range = Kernel._string);
      { global_variable * g0302 = _CL_obj; 
        OID  g0303;
        if ((((ClaireBoolean *) (ClaireBoolean *)(
#ifdef CLPC
CTRUE
#else
CFALSE
#endif
))) == CTRUE)
         g0303 = _string_(((char*)";"));
        else g0303 = _string_(((char*)":"));
          _void_(g0302->value = g0303);}
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Kernel._7->addMethod(list::domain(2,Kernel._string,Kernel._string),Kernel._string,
    	NEW_ALLOC+RETURN_ARG,_function_(_7_string,"/_string"));
    
    { (Core._7_dash = (operation *) Kernel._operation->instantiate("/-",claire.it));
      _void_(Core._7_dash->precedence = Kernel._7->precedence);
      ;}
    
    Core._7_dash->addMethod(list::domain(2,Kernel._string,Kernel._string),Kernel._string,
    	NEW_ALLOC+RETURN_ARG,_function_(_7_dash_string,"/-_string"));
    
    { (Core._ffor_error = ClaireClass::make("ffor_error",Kernel._exception,Core.it));
      CL_ADD_SLOT(Core._ffor_error,Core_ffor_error,Core.childstr,childstr,Kernel._string,CNULL);
      CL_ADD_SLOT(Core._ffor_error,Core_ffor_error,Core.childpid,childpid,Kernel._integer,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Core._ffor_error),Kernel._void,
    	NEW_ALLOC,_function_(self_print_ffor_error1_Core,"self_print_ffor_error1_Core"));
    
    { (Core._I_equal = (operation *) Kernel._operation->instantiate("!=",claire.it));
      _void_(Core._I_equal->precedence = 60);
      ;}
    
    { (Kernel._inf_inf = (operation *) Kernel._operation->instantiate("<<",claire.it));
      ;}
    
    { (Core._sup_sup = (operation *) Kernel._operation->instantiate(">>",claire.it));
      ;}
    
    { (Core.ClaireAnd = (operation *) Kernel._operation->instantiate("and",claire.it));
      ;}
    
    { (Core.ClaireOr = (operation *) Kernel._operation->instantiate("or",claire.it));
      ;}
    
    { (Core.U = (operation *) Kernel._operation->instantiate("U",claire.it));
      _void_(Core.U->precedence = 50);
      ;}
    
    { (Core.less_ask = (operation *) Kernel._operation->instantiate("less?",claire.it));
      _void_(Core.less_ask->precedence = 60);
      _void_(Core.less_ask->range = Kernel._boolean);
      ;}
    
    { (Core._and = (operation *) Kernel._operation->instantiate("&",claire.it));
      ;}
    
    { (Core.min = (operation *) Kernel._operation->instantiate("min",claire.it));
      _void_(Core.min->precedence = 20);
      ;}
    
    { (Core.max = (operation *) Kernel._operation->instantiate("max",claire.it));
      _void_(Core.max->precedence = 20);
      ;}
    
    { (Core.meet = (operation *) Kernel._operation->instantiate("meet",claire.it));
      ;}
    
    { (Core.inherit_ask = (operation *) Kernel._operation->instantiate("inherit?",claire.it));
      ;}
    
    Core.min->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._integer,
    	SAFE_RESULT,_function_(min_integer1,"min_integer1"));
    
    Core.max->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._integer,
    	SAFE_RESULT,_function_(max_integer1,"max_integer1"));
    
    Core.min->addFloatMethod(list::domain(2,Kernel._float,Kernel._float),Kernel._float,
    	RETURN_ARG,_function_(min_float1,"min_float1"),
    _function_(min_float1_,"min_float1_"));
    
    Core.max->addFloatMethod(list::domain(2,Kernel._float,Kernel._float),Kernel._float,
    	RETURN_ARG,_function_(max_float1,"max_float1"),
    _function_(max_float1_,"max_float1_"));
    
    { (Core.cpstack = property::make("cpstack",1,Core.it,Kernel._any,0));
      ;}
    
    { (Core._pretty_printer = ClaireClass::make("pretty_printer",Kernel._thing,claire.it));
      CL_ADD_SLOT(Core._pretty_printer,pretty_printer,Core.cpretty,cpretty,Kernel._port,CNULL);
      CL_ADD_SLOT(Core._pretty_printer,pretty_printer,Core.cprevious,cprevious,Kernel._integer,((OID)1));
      CL_ADD_SLOT(Core._pretty_printer,pretty_printer,Kernel.index,index,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Core._pretty_printer,pretty_printer,Core.width,width,Kernel._integer,((OID)120));
      CL_ADD_SLOT(Core._pretty_printer,pretty_printer,Core.pprint,pprint,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Core._pretty_printer,pretty_printer,Core.pbreak,pbreak,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Core._pretty_printer,pretty_printer,Core.cpstack,cpstack,Kernel._list,CNULL);
      }
    
    { (Core.pretty = (pretty_printer *) Core._pretty_printer->instantiate("pretty",claire.it));
      ;}
    
    { (Core.apply_self_print = property::make("apply_self_print",1,claire.it,Kernel._any,0));
      ;}
    
    { (Core.short_enough = property::make("short_enough",1,claire.it,Kernel._any,0));
      ;}
    
    { (Kernel.print = property::make("print",1,claire.it,Kernel._any,0));
      ;}
    
    Core.print_in_string->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(print_in_string_void,"print_in_string_void"));
    
    Core.end_of_string->addMethod(list::domain(1,Kernel._void),Kernel._string,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(end_of_string_void,"end_of_string_void"));
    
    Core.buffer_length->addMethod(list::domain(1,Kernel._void),Kernel._integer,
    	RETURN_ARG,_function_(buffer_length_void,"buffer_length_void"));
    
    Core.buffer_set_length->addMethod(list::domain(1,Kernel._integer),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(buffer_set_length_integer,"buffer_set_length_integer"));
    
    Core.apply_self_print->addMethod(list::domain(1,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(apply_self_print_any,"apply_self_print_any"));
    
    Kernel.self_print->addMethod(list::domain(1,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_any_Core,"self_print_any_Core"));
    
    Kernel.self_print->addMethod(list::domain(1,Kernel._exception),Kernel._void,
    	NEW_ALLOC,_function_(self_print_exception1_Core,"self_print_exception1_Core"));
    
    Kernel.self_print->addMethod(list::domain(1,Kernel._boolean),Kernel._void,
    	0,_function_(self_print_boolean_Core,"self_print_boolean_Core"));
    
    Kernel.self_print->addMethod(list::domain(1,Kernel._function),Kernel._void,
    	0,_function_(self_print_function_Core,"self_print_function_Core"));
    
    Kernel.self_print->addMethod(list::domain(1,Kernel._restriction),Kernel._void,
    	NEW_ALLOC,_function_(self_print_restriction_Core,"self_print_restriction_Core"));
    
    (Core._much_too_far = ClaireClass::make("much_too_far",Kernel._error,claire.it));
    
    Kernel.print->addMethod(list::domain(1,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(print_any,"print_any"));
    
    Core.short_enough->addMethod(list::domain(1,Kernel._integer),Kernel._boolean,
    	0,_function_(short_enough_integer,"short_enough_integer"));
    
    Core.complete_I->addMethod(list::domain(1,Kernel._object),Kernel._object,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(complete_I_object,"complete_I_object"));
    
    { (Core.kill_I = property::make("kill!",2,claire.it,Kernel._any,0));
      ;}
    
    Core.kill_I->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	0,_function_(kill_I_any,"kill_I_any"));
    
    Core.NOT->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	0,_function_(not_any,"not_any"));
    
    Core._I_equal->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._boolean,
    	0,_function_(_I_equal_any,"!=_any"));
    
    Core.owner->addMethod(list::domain(1,Kernel._any),Kernel._class,
    	0,_function_(owner_any,"owner_any"));
    
    Core.known_ask->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	0,_function_(known_ask_any,"known?_any"));
    
    Core.unknown_ask->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	0,_function_(unknown_ask_any,"unknown?_any"));
    
    Core.check_in->addMethod(list::domain(2,Kernel._any,Kernel._type),Kernel._any,
    	RETURN_ARG,_function_(check_in_any,"check_in_any"));
    
    Core.check_in->addMethod(list::domain(3,Kernel._bag,Kernel._class,Kernel._type),Kernel._bag,
    	NEW_ALLOC+RETURN_ARG,_function_(check_in_bag,"check_in_bag"));
    
    Kernel._inf->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._boolean,
    	NEW_ALLOC,_function_(_inf_any,"<_any"));
    
    Kernel._sup->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._boolean,
    	NEW_ALLOC,_function_(_sup_any,">_any"));
    
    Kernel.ephemeral->addMethod(list::domain(1,Kernel._class),Kernel._any,
    	SLOT_UPDATE+RETURN_ARG,_function_(ephemeral_class,"ephemeral_class"));
    
    Kernel.ABSTRACT->addMethod(list::domain(1,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT,_function_(abstract_class,"abstract_class"));
    
    Kernel.FINAL->addMethod(list::domain(1,Kernel._class),Kernel._any,
    	SLOT_UPDATE+SAFE_RESULT,_function_(final_class,"final_class"));
    
    _void_(Core.NEW->addMethod(list::domain(1,Kernel._class),Kernel._object,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(new_class1,"new_class1"))->typing = _oid_(_function_(new_class1_type,"new_class1_type")));
    
    _void_(Core.NEW->addMethod(list::domain(2,Kernel._class,Kernel._symbol),Kernel._thing,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(new_class2,"new_class2"))->typing = _oid_(_function_(new_class2_type,"new_class2_type")));
    
    _void_(Core.new_I->addMethod(list::domain(1,Kernel._class),Kernel._object,
    	NEW_ALLOC,_function_(new_object_class,"new_object_class"))->typing = _oid_(_function_(new_object_class_type,"new_object_class_type")));
    
    _void_(Core.new_I->addMethod(list::domain(2,Kernel._class,Kernel._symbol),Kernel._thing,
    	NEW_ALLOC,_function_(new_thing_class,"new_thing_class"))->typing = _oid_(_function_(new_thing_class_type,"new_thing_class_type")));
    
    Core.meet->addMethod(list::domain(2,Kernel._class,Kernel._class),Kernel._class,
    	RETURN_ARG,_function_(meet_class,"meet_class"));
    
    Core.inherit_ask->addMethod(list::domain(2,Kernel._class,Kernel._class),Kernel._boolean,
    	0,_function_(inherit_ask_class,"inherit?_class"));
    
    Core.class_I->addMethod(list::domain(2,Kernel._symbol,Kernel._class),Kernel._class,
    	NEW_ALLOC,_function_(class_I_symbol,"class!_symbol"));
    
    Kernel.ABSTRACT->addMethod(list::domain(1,Kernel._property),Kernel._any,
    	SLOT_UPDATE+SAFE_RESULT,_function_(abstract_property,"abstract_property"));
    
    Kernel.FINAL->addMethod(list::domain(1,Kernel._relation),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(final_relation,"final_relation"));
    
    Kernel.close->addMethod(list::domain(1,Kernel._module),Kernel._module,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT,_function_(close_module,"close_module"));
    
    Core.get_symbol->addMethod(list::domain(2,Kernel._module,Kernel._string),Kernel._any,
    	0,_function_(get_symbol_module,"get_symbol_module"));
    
    Core.get_symbol->addMethod(list::domain(1,Kernel._string),Kernel._any,
    	0,_function_(get_symbol_string,"get_symbol_string"));
    
    Core.gc->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	0,_function_(claire_gc,"claire_gc"));
    
    Core.time_get->addMethod(list::domain(1,Kernel._void),Kernel._integer,
    	0,_function_(time_get_void,"time_get_void"));
    
    Core.time_read->addMethod(list::domain(1,Kernel._void),Kernel._integer,
    	0,_function_(time_read_void,"time_read_void"));
    
    Core.time_set->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	0,_function_(time_set_void,"time_set_void"));
    
    Core.time_show->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	0,_function_(time_show_void,"time_show_void"));
    
    Kernel.gensym->addMethod(list::domain(1,Kernel._void),Kernel._symbol,
    	0,_function_(gensym_void,"gensym_void"));
    
    Kernel.store->addMethod(list::domain(3,Kernel._list,Kernel._integer,Kernel._any),Kernel._any,
    	0,_function_(store_list4,"store_list4"));
    
    Kernel.store->addMethod(list::domain(3,Kernel._array,Kernel._integer,Kernel._any),Kernel._any,
    	RETURN_ARG,_function_(store_array1,"store_array1"));
    
    Kernel.commit->addMethod(list::domain(1,Kernel._integer),Kernel._void,
    	0,_function_(commit_integer,"commit_integer"));
    
    Kernel.backtrack->addMethod(list::domain(1,Kernel._integer),Kernel._void,
    	0,_function_(backtrack_integer,"backtrack_integer"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core.world_plus = (global_variable *) Core._global_variable->instantiate("world+",claire.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(Kernel.choice));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Core.world_dash = (global_variable *) Core._global_variable->instantiate("world-",claire.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(Kernel.backtrack));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Core.world_dash_I = (global_variable *) Core._global_variable->instantiate("world-!",claire.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(Kernel.commit));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Kernel.store->addMethod(list::domain(1,Kernel._listargs),Kernel._any,
    	SLOT_UPDATE+RETURN_ARG,_function_(store_listargs,"store_listargs"));
    
    { (Core.preread = property::make("preread",3,claire.it,Kernel._any,0));
      _void_(Core.preread->open = 3);
      ;}
    
    Core.preread->addMethod(list::domain(2,Kernel._property,Kernel._any),Kernel._void,
    	0,_function_(preread_property1_Core,"preread_property1_Core"));
    
    Kernel.length->addMethod(list::domain(1,Kernel._string),Kernel._integer,
    	0,_function_(length_string,"length_string"));
    
    Core.make_function->addMethod(list::domain(1,Kernel._string),Kernel._function,
    	0,_function_(make_function_string,"make_function_string"));
    
    Kernel.symbol_I->addMethod(list::domain(1,Kernel._string),Kernel._symbol,
    	0,_function_(symbol_I_string2,"symbol!_string2"));
    
    Core.externC->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	SAFE_RESULT,_function_(externC_string,"externC_string"));
    
    _void_(Core.externC->addMethod(list::domain(2,Kernel._string,Kernel._class),Kernel._any,
    	SAFE_RESULT,_function_(externC_string2,"externC_string2"))->typing = _oid_(_function_(externC_string2_type,"externC_string2_type")));
    
    Kernel.nth_get->addMethod(list::domain(3,Kernel._string,Kernel._integer,Kernel._integer),Kernel._char,
    	RETURN_ARG,_function_(nth_get_string,"nth_get_string"));
    
    Kernel.nth_put->addMethod(list::domain(4,Kernel._string,
      Kernel._integer,
      Kernel._char,
      Kernel._integer),Kernel._void,
    	BAG_UPDATE+RETURN_ARG,_function_(nth_put_string,"nth_put_string"));
    
    Core.shell->addMethod(list::domain(1,Kernel._string),Kernel._integer,
    	0,_function_(claire_shell,"claire_shell"));
    
    Core.getenv->addMethod(list::domain(1,Kernel._string),Kernel._string,
    	NEW_ALLOC,_function_(getenv_string,"getenv_string"));
    
    Core.get_value->addMethod(list::domain(1,Kernel._string),Kernel._any,
    	0,_function_(value_string,"value_string"));
    
    Core.get_value->addMethod(list::domain(2,Kernel._module,Kernel._string),Kernel._any,
    	0,_function_(value_module,"value_module"));
    
    Kernel.make_string->addMethod(list::domain(1,Kernel._symbol),Kernel._string,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(make_string_symbol,"make_string_symbol"));
    
    Kernel.self_print->addMethod(list::domain(1,Kernel._symbol),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_symbol_Core,"self_print_symbol_Core"));
    
    _void_(Core._plus->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._integer,
    	RETURN_ARG,_function_(_plus_integer,"+_integer"))->typing = _oid_(_function_(_plus_integer_type,"+_integer_type")));
    
    _void_(Kernel._dash->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._integer,
    	RETURN_ARG,_function_(_dash_integer1,"-_integer1"))->typing = _oid_(_function_(_dash_integer1_type,"-_integer1_type")));
    
    Core._dash_dash_ask->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._set,
    	NEW_ALLOC,_function_(sequence_integer,"sequence_integer"));
    
    Core.exit->addMethod(list::domain(1,Kernel._integer),Kernel._void,
    	0,_function_(CL_exit,"CL_exit"));
    
    Kernel._inf_inf->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._integer,
    	0,_function_(_inf_inf_integer,"<<_integer"));
    
    Core._sup_sup->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._integer,
    	0,_function_(_sup_sup_integer,">>_integer"));
    
    Core.ClaireAnd->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._integer,
    	0,_function_(and_integer,"and_integer"));
    
    Core.ClaireOr->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._integer,
    	0,_function_(or_integer,"or_integer"));
    
    Kernel._inf->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._boolean,
    	0,_function_(_inf_integer,"<_integer"));
    
    Kernel._inf_equal->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._boolean,
    	0,_function_(_inf_equal_integer,"<=_integer"));
    
    Kernel._sup->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._boolean,
    	0,_function_(_sup_integer,">_integer"));
    
    Kernel.nth->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._boolean,
    	0,_function_(nth_integer,"nth_integer"));
    
    Core.factor_ask->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._boolean,
    	0,_function_(factor_ask_integer,"factor?_integer"));
    
    Core.divide_ask->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._boolean,
    	0,_function_(divide_ask_integer,"divide?_integer"));
    
    _void_(Core.Id->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	RETURN_ARG,_function_(Id_any,"Id_any"))->typing = _oid_(_function_(Id_any_type,"Id_any_type")));
    
    { (Core.pair = (operation *) Kernel._operation->instantiate("pair",claire.it));
      ;}
    
    Core.pair->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._list,
    	NEW_ALLOC,_function_(pair_any,"pair_any"));
    
    _void_(Core.pair_1->addMethod(list::domain(1,Kernel._list),Kernel._any,
    	RETURN_ARG,_function_(pair_1_list,"pair_1_list"))->typing = _oid_(_function_(pair_1_list_type,"pair_1_list_type")));
    
    _void_(Core.pair_2->addMethod(list::domain(1,Kernel._list),Kernel._any,
    	RETURN_ARG,_function_(pair_2_list,"pair_2_list"))->typing = _oid_(_function_(pair_2_list_type,"pair_2_list_type")));
    
    Kernel.self_print->addFloatMethod(list::domain(1,Kernel._float),Kernel._void,
    	0,_function_(print_float,"print_float"),
    _function_(print_float_,"print_float_"));
    
    Core._plus->addFloatMethod(list::domain(2,Kernel._float,Kernel._float),Kernel._float,
    	0,_function_(_plus_float,"_plus_float"),
    _function_(_plus_float_,"_plus_float_"));
    
    Kernel._dash->addFloatMethod(list::domain(2,Kernel._float,Kernel._float),Kernel._float,
    	0,_function_(_dash_float,"_dash_float"),
    _function_(_dash_float_,"_dash_float_"));
    
    Kernel._star->addFloatMethod(list::domain(2,Kernel._float,Kernel._float),Kernel._float,
    	0,_function_(_star_float,"_star_float"),
    _function_(_star_float_,"_star_float_"));
    
    Kernel._7->addFloatMethod(list::domain(2,Kernel._float,Kernel._float),Kernel._float,
    	0,_function_(_7_float,"_7_float"),
    _function_(_7_float_,"_7_float_"));
    
    Kernel._dash->addFloatMethod(list::domain(1,Kernel._float),Kernel._float,
    	NEW_ALLOC,_function_(_dash_float2,"-_float2"),
    _function_(_dash_float2_,"-_float2_"));
    
    Core.sqrt->addFloatMethod(list::domain(1,Kernel._float),Kernel._float,
    	0,_function_(sqrt_float,"sqrt_float"),
    _function_(sqrt_float_,"sqrt_float_"));
    
    Kernel._exp->addFloatMethod(list::domain(2,Kernel._float,Kernel._float),Kernel._float,
    	NEW_ALLOC,_function_(_exp_float,"_exp_float"),
    _function_(_exp_float_,"_exp_float_"));
    
    Core.log->addFloatMethod(list::domain(1,Kernel._float),Kernel._float,
    	NEW_ALLOC,_function_(log_float,"log_float"),
    _function_(log_float_,"log_float_"));
    
    Core.tan->addFloatMethod(list::domain(1,Kernel._float),Kernel._float,
    	NEW_ALLOC,_function_(tan_float1,"tan_float1"),
    _function_(tan_float1_,"tan_float1_"));
    
    Core.cos->addFloatMethod(list::domain(1,Kernel._float),Kernel._float,
    	NEW_ALLOC,_function_(cos_float1,"cos_float1"),
    _function_(cos_float1_,"cos_float1_"));
    
    Core.sin->addFloatMethod(list::domain(1,Kernel._float),Kernel._float,
    	NEW_ALLOC,_function_(sin_float1,"sin_float1"),
    _function_(sin_float1_,"sin_float1_"));
    
    Core.acos->addFloatMethod(list::domain(1,Kernel._float),Kernel._float,
    	NEW_ALLOC,_function_(acos_float1,"acos_float1"),
    _function_(acos_float1_,"acos_float1_"));
    
    Core.asin->addFloatMethod(list::domain(1,Kernel._float),Kernel._float,
    	NEW_ALLOC,_function_(asin_float1,"asin_float1"),
    _function_(asin_float1_,"asin_float1_"));
    
    Core.atan->addFloatMethod(list::domain(1,Kernel._float),Kernel._float,
    	NEW_ALLOC,_function_(atan_float1,"atan_float1"),
    _function_(atan_float1_,"atan_float1_"));
    
    Core.tanh->addFloatMethod(list::domain(1,Kernel._float),Kernel._float,
    	NEW_ALLOC,_function_(tanh_float1,"tanh_float1"),
    _function_(tanh_float1_,"tanh_float1_"));
    
    Core.cosh->addFloatMethod(list::domain(1,Kernel._float),Kernel._float,
    	NEW_ALLOC,_function_(cosh_float1,"cosh_float1"),
    _function_(cosh_float1_,"cosh_float1_"));
    
    Core.sinh->addFloatMethod(list::domain(1,Kernel._float),Kernel._float,
    	NEW_ALLOC,_function_(sinh_float1,"sinh_float1"),
    _function_(sinh_float1_,"sinh_float1_"));
    
    Kernel.string_I->addFloatMethod(list::domain(1,Kernel._float),Kernel._string,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(string_I_float,"string!_float"),
    _function_(string_I_float_,"string!_float_"));
    
    Kernel.string_I->addMethod(list::domain(1,Kernel._char),Kernel._string,
    	NEW_ALLOC,_function_(string_I_char1,"string!_char1"));
    
    Kernel.length->addMethod(list::domain(1,Kernel._bag),Kernel._integer,
    	RETURN_ARG,_function_(length_bag,"length_bag"));
    
    _void_(Kernel.nth->addMethod(list::domain(2,Kernel._bag,Kernel._integer),Kernel._any,
    	RETURN_ARG,_function_(nth_bag,"nth_bag"))->typing = _oid_(_function_(nth_bag_type,"nth_bag_type")));
    
    Kernel.nth_get->addMethod(list::domain(2,Kernel._bag,Kernel._integer),Kernel._any,
    	RETURN_ARG,_function_(nth_get_bag,"nth_get_bag"));
    
    _void_(Core.min->addMethod(list::domain(2,Kernel._method,Kernel._bag),Kernel._any,
    	NEW_ALLOC,_function_(min_method,"min_method"))->typing = _oid_(_function_(min_method_type,"min_method_type")));
    
    _void_(Core.max->addMethod(list::domain(2,Kernel._method,Kernel._bag),Kernel._any,
    	NEW_ALLOC,_function_(max_method,"max_method"))->typing = _oid_(_function_(max_method_type,"max_method_type")));
    
    Kernel._7_plus->addMethod(list::domain(2,Kernel._bag,Kernel._bag),Kernel._list,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(_7_plus_bag,"/+_bag"));
    
    _void_(Core.last->addMethod(list::domain(1,Kernel._list),Kernel._any,
    	RETURN_ARG,_function_(last_list,"last_list"))->typing = _oid_(_function_(last_list_type,"last_list_type")));
    
    Core.rmlast->addMethod(list::domain(1,Kernel._list),Kernel._list,
    	RETURN_ARG,_function_(rmlast_list,"rmlast_list"));
    
    Kernel.nth_equal->addMethod(list::domain(3,Kernel._list,Kernel._integer,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(nth_set_list,"nth_set_list"));
    
    Core.car->addMethod(list::domain(1,Kernel._list),Kernel._any,
    	RETURN_ARG,_function_(car_list,"car_list"));
    
    Core.hashlist->addMethod(list::domain(1,Kernel._integer),Kernel._list,
    	NEW_ALLOC,_function_(hashlist_integer,"hashlist_integer"));
    
    Core.hashsize->addMethod(list::domain(1,Kernel._list),Kernel._integer,
    	0,_function_(hashsize_list,"hashsize_list"));
    
    Core.sort->addMethod(list::domain(2,Kernel._method,Kernel._list),Kernel._list,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(sort_method,"sort_method"));
    
    Core.quicksort->addMethod(list::domain(4,Kernel._list,
      Kernel._method,
      Kernel._integer,
      Kernel._integer),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(quicksort_list,"quicksort_list"));
    
    Core.build_powerset->addMethod(list::domain(1,Kernel._list),Kernel._set,
    	NEW_ALLOC+BAG_UPDATE,_function_(build_powerset_list,"build_powerset_list"));
    
    Core.tuple_I->addMethod(list::domain(1,Kernel._list),Kernel._tuple,
    	NEW_ALLOC,_function_(tuple_I_list,"tuple!_list"));
    
    Core.make_copy_list->addMethod(list::domain(2,Kernel._integer,Kernel._any),Kernel._list,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(make_copy_list_integer,"make_copy_list_integer"));
    
    Core.difference->addMethod(list::domain(2,Kernel._set,Kernel._set),Kernel._set,
    	NEW_ALLOC,_function_(difference_set,"difference_set"));
    
    Kernel.nth_equal->addMethod(list::domain(3,Kernel._array,Kernel._integer,Kernel._any),Kernel._void,
    	RETURN_ARG,_function_(nth_equal_array,"nth=_array"));
    
    Kernel.self_print->addMethod(list::domain(1,Kernel._array),Kernel._void,
    	NEW_ALLOC,_function_(self_print_array_Core,"self_print_array_Core"));
    
    Kernel.self_print->addMethod(list::domain(1,Kernel._char),Kernel._void,
    	0,_function_(print_char,"print_char"));
    
    Kernel._inf_equal->addMethod(list::domain(2,Kernel._char,Kernel._char),Kernel._boolean,
    	0,_function_(_inf_equal_char,"<=_char"));
    
    Core.Address->addMethod(list::domain(1,Kernel._any),Kernel._integer,
    	0,_function_(CL_Address,"CL_Address"));
    
    Core.Oid->addMethod(list::domain(1,Kernel._any),Kernel._string,
    	0,_function_(CL_Oid,"CL_Oid"));
    
    Core.Oid_tilda->addMethod(list::domain(1,Kernel._string),Kernel._any,
    	0,_function_(CL_Oid_inv,"CL_Oid_inv"));
    
    Kernel.kill->addMethod(list::domain(1,Kernel._object),Kernel._any,
    	SLOT_UPDATE,_function_(kill_object,"kill_object"));
    
    Kernel.kill->addMethod(list::domain(1,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(kill_class,"kill_class"));
    
    Kernel.float_I->addFloatMethod(list::domain(1,Kernel._string),Kernel._float,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(float_I_string,"float!_string"),
    _function_(float_I_string_,"float!_string_"));
    
    Core.unix_ask->addMethod(list::domain(1,Kernel._void),Kernel._boolean,
    	0,_function_(unix_ask_void1,"unix?_void1"));
    
    Core.strffloat->addFloatMethod(list::domain(2,Kernel._string,Kernel._float),Kernel._string,
    	NEW_ALLOC,_function_(strffloat_string1,"strffloat_string1"),
    _function_(strffloat_string1_,"strffloat_string1_"));
    
    Core.chroot->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	0,_function_(chroot_string1,"chroot_string1"));
    
    { (Core.on_fork = property::make("on_fork",3,claire.it,Kernel._any,0));
      _void_(Core.on_fork->open = 3);
      ;}
    
    { (Core.on_forked = property::make("on_forked",3,claire.it,Kernel._any,0));
      _void_(Core.on_forked->open = 3);
      ;}
    
    Core.fork->addMethod(list::domain(1,Kernel._void),Kernel._integer,
    	NEW_ALLOC,_function_(fork_void1,"fork_void1"));
    
    Core.forker_ask->addMethod(list::domain(1,Kernel._void),Kernel._boolean,
    	NEW_ALLOC,_function_(forker_ask_void1,"forker?_void1"));
    
    Core.forked_ask->addMethod(list::domain(1,Kernel._void),Kernel._boolean,
    	NEW_ALLOC,_function_(forked_ask_void1,"forked?_void1"));
    
    { (Core.arg1 = property::make("arg1",1,claire.it,Kernel._any,0));
      ;}
    
    { (Core.arg2 = property::make("arg2",1,claire.it,Kernel._any,0));
      ;}
    
    { (Core._dash_dash = (operation *) Kernel._operation->instantiate("--",claire.it));
      _void_(Core._dash_dash->precedence = Kernel._dot_dot->precedence);
      ;}
    
    Core.finite_ask->addMethod(list::domain(1,Kernel._type),Kernel._boolean,
    	NEW_ALLOC,_function_(finite_ask_type,"finite?_type"));
    
    Core.enumerate->addMethod(list::domain(1,Kernel._any),Kernel._bag,
    	NEW_ALLOC+RETURN_ARG,_function_(enumerate_any,"enumerate_any"));
    
    { (Core._equaltype_ask = (operation *) Kernel._operation->instantiate("=type?",claire.it));
      ;}
    
    Core._equaltype_ask->addMethod(list::domain(2,Kernel._type,Kernel._type),Kernel._boolean,
    	NEW_ALLOC,_function_(_equaltype_ask_any,"=type?_any"));
    
    Kernel.sort_I->addMethod(list::domain(1,Kernel._type),Kernel._class,
    	NEW_ALLOC+RETURN_ARG,_function_(sort_I_type,"sort!_type"));
    
    Kernel._Z->addMethod(list::domain(2,Kernel._any,Kernel._class),Kernel._boolean,
    	0,_function_(_Z_any1,"%_any1"));
    
    Core._Ztype->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._boolean,
    	NEW_ALLOC,_function_(Ztype_any,"Ztype_any"));
    
    (Core._Type = ClaireClass::make("Type",Kernel._type,claire.it));
    
    { (Core._Union = ClaireClass::make("Union",Core._Type,claire.it));
      CL_ADD_SLOT(Core._Union,Union,Core.t1,t1,Kernel._type,CNULL);
      CL_ADD_SLOT(Core._Union,Union,Core.t2,t2,Kernel._type,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Core._Union),Kernel._void,
    	NEW_ALLOC,_function_(self_print_Union_Core,"self_print_Union_Core"));
    
    Core.finite_ask->addMethod(list::domain(1,Core._Union),Kernel._boolean,
    	NEW_ALLOC,_function_(finite_ask_Union,"finite?_Union"));
    
    { (Core._Interval = ClaireClass::make("Interval",Core._Type,claire.it));
      CL_ADD_SLOT(Core._Interval,Interval,Core.arg1,arg1,Kernel._integer,CNULL);
      CL_ADD_SLOT(Core._Interval,Interval,Core.arg2,arg2,Kernel._integer,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Core._Interval),Kernel._void,
    	NEW_ALLOC,_function_(self_print_Interval_Core,"self_print_Interval_Core"));
    
    Core.finite_ask->addMethod(list::domain(1,Core._Interval),Kernel._boolean,
    	0,_function_(finite_ask_Interval,"finite?_Interval"));
    
    Core._dash_dash->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Core._Interval,
    	NEW_ALLOC,_function_(_dash_dash_integer,"--_integer"));
    
    { (Core._Param = ClaireClass::make("Param",Core._Type,claire.it));
      CL_ADD_SLOT(Core._Param,Param,Kernel.arg,arg,Kernel._class,CNULL);
      CL_ADD_SLOT(Core._Param,Param,Kernel.params,params,Kernel._list,CNULL);
      CL_ADD_SLOT(Core._Param,Param,Core.args,args,Kernel._list,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Core._Param),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Param_Core,"self_print_Param_Core"));
    
    Core.finite_ask->addMethod(list::domain(1,Core._Param),Kernel._boolean,
    	NEW_ALLOC,_function_(finite_ask_Param,"finite?_Param"));
    
    { (Core._subtype = ClaireClass::make("subtype",Core._Type,claire.it));
      CL_ADD_SLOT(Core._subtype,subtype,Kernel.arg,arg,Kernel._class,CNULL);
      CL_ADD_SLOT(Core._subtype,subtype,Core.t1,t1,Kernel._type,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Core._subtype),Kernel._void,
    	NEW_ALLOC,_function_(self_print_subtype_Core,"self_print_subtype_Core"));
    
    Core.finite_ask->addMethod(list::domain(1,Core._subtype),Kernel._boolean,
    	NEW_ALLOC,_function_(finite_ask_subtype,"finite?_subtype"));
    
    Kernel.nth->addMethod(list::domain(2,Kernel._class,Kernel._type),Kernel._type,
    	NEW_ALLOC,_function_(nth_class1,"nth_class1"));
    
    Kernel.nth->addMethod(list::domain(3,Kernel._class,Kernel._list,Kernel._list),Kernel._type,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(nth_class2,"nth_class2"));
    
    Core.param_I->addMethod(list::domain(2,Kernel._class,Kernel._type),Kernel._type,
    	NEW_ALLOC,_function_(param_I_class,"param_I_class"));
    
    Kernel.nth->addMethod(list::domain(1,Kernel._type),Kernel._type,
    	NEW_ALLOC,_function_(nth_type,"nth_type"));
    
    Core.finite_ask->addMethod(list::domain(1,Kernel._tuple),Kernel._boolean,
    	NEW_ALLOC,_function_(finite_ask_tuple,"finite?_tuple"));
    
    { (Core._Reference = ClaireClass::make("Reference",Core._Type,claire.it));
      CL_ADD_SLOT(Core._Reference,Reference,Core.args,args,Kernel._list,CNULL);
      CL_ADD_SLOT(Core._Reference,Reference,Kernel.index,index,Kernel._integer,CNULL);
      CL_ADD_SLOT(Core._Reference,Reference,Kernel.arg,arg,Kernel._boolean,Kernel.cfalse);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Core._Reference),Kernel._void,
    	NEW_ALLOC,_function_(self_print_Reference_Core,"self_print_Reference_Core"));
    
    Kernel.get->addMethod(list::domain(2,Core._Reference,Kernel._any),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(get_Reference,"get_Reference"));
    
    Core._at->addMethod(list::domain(3,Core._Reference,Kernel._list,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(_at_Reference,"@_Reference"));
    
    Kernel.set_I->addMethod(list::domain(1,Kernel._collection),Kernel._set,
    	NEW_ALLOC,_function_(set_I_collection,"set!_collection"));
    
    Core.size->addMethod(list::domain(1,Kernel._collection),Kernel._integer,
    	NEW_ALLOC+RETURN_ARG,_function_(size_collection,"size_collection"));
    
    ;
    Kernel.set_I->addMethod(list::domain(1,Kernel._set),Kernel._set,
    	RETURN_ARG,_function_(set_I_set,"set!_set"));
    
    Core.size->addMethod(list::domain(1,Kernel._set),Kernel._integer,
    	RETURN_ARG,_function_(size_set,"size_set"));
    
    Core.size->addMethod(list::domain(1,Kernel._list),Kernel._integer,
    	NEW_ALLOC+RETURN_ARG,_function_(size_list2_Core,"size_list2_Core"));
    
    Kernel.set_I->addMethod(list::domain(1,Kernel._class),Kernel._set,
    	NEW_ALLOC+RETURN_ARG,_function_(set_I_class,"set!_class"));
    
    Core.size->addMethod(list::domain(1,Kernel._class),Kernel._integer,
    	SAFE_RESULT,_function_(size_class,"size_class"));
    
    Kernel.set_I->addMethod(list::domain(1,Core._Union),Kernel._set,
    	NEW_ALLOC+RETURN_ARG,_function_(set_I_Union,"set!_Union"));
    
    Core.size->addMethod(list::domain(1,Core._Union),Kernel._integer,
    	NEW_ALLOC+RETURN_ARG,_function_(size_Union,"size_Union"));
    
    Kernel.set_I->addMethod(list::domain(1,Core._Interval),Kernel._set,
    	NEW_ALLOC,_function_(set_I_Interval,"set!_Interval"));
    
    Core.size->addMethod(list::domain(1,Core._Interval),Kernel._integer,
    	RETURN_ARG,_function_(size_Interval,"size_Interval"));
    
    Kernel.set_I->addMethod(list::domain(1,Core._Param),Kernel._set,
    	NEW_ALLOC,_function_(set_I_Param,"set!_Param"));
    
    Core.size->addMethod(list::domain(1,Core._Param),Kernel._integer,
    	NEW_ALLOC+RETURN_ARG,_function_(size_Param,"size_Param"));
    
    Kernel.set_I->addMethod(list::domain(1,Core._subtype),Kernel._set,
    	NEW_ALLOC+BAG_UPDATE,_function_(set_I_subtype,"set!_subtype"));
    
    Core.size->addMethod(list::domain(1,Core._subtype),Kernel._integer,
    	NEW_ALLOC,_function_(size_subtype,"size_subtype"));
    
    Kernel.set_I->addMethod(list::domain(1,Kernel._tuple),Kernel._set,
    	NEW_ALLOC,_function_(set_I_tuple,"set!_tuple"));
    
    Core.size->addMethod(list::domain(1,Kernel._tuple),Kernel._integer,
    	NEW_ALLOC,_function_(size_tuple,"size_tuple"));
    
    Kernel.member_ask->addMethod(list::domain(2,Kernel._any,Kernel._type),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(member_ask_any,"member?_any"));
    
    Core.class_I->addMethod(list::domain(1,Kernel._type),Kernel._class,
    	NEW_ALLOC+RETURN_ARG,_function_(class_I_type,"class!_type"));
    
    { ephemeral_class(Core._Union);
      ephemeral_class(Core._Param);
      ephemeral_class(Core._Interval);
      ephemeral_class(Core._subtype);
      }
    
    Core.U->addMethod(list::domain(2,Kernel._type,Kernel._type),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(U_type,"U_type"));
    
    _void_(Kernel._dot_dot->addMethod(list::domain(2,Kernel._integer,Kernel._integer),nth_class1(Kernel._type,Kernel._integer),
    	NEW_ALLOC,_function_(_dot_dot_integer,".._integer"))->typing = _oid_(_function_(_dot_dot_integer_type,".._integer_type")));
    
    { (Core.but = (operation *) Kernel._operation->instantiate("but",claire.it));
      ;}
    
    _void_(Core.but->addMethod(list::domain(2,Kernel._any,Kernel._any),nth_class1(Kernel._bag,Kernel._any),
    	NEW_ALLOC,_function_(but_any,"but_any"))->typing = _oid_(_function_(but_any_type,"but_any_type")));
    
    { (Core._backslash = (operation *) Kernel._operation->instantiate("\\",claire.it));
      _void_(Core._backslash->precedence = Core.U->precedence);
      ;}
    
    Core._backslash->addMethod(list::domain(2,Kernel._type,Kernel._type),Kernel._set,
    	NEW_ALLOC,_function_(_backslash_type,"\\_type"));
    
    { (Core.glb = (operation *) Kernel._operation->instantiate("glb",claire.it));
      _void_(Core.glb->precedence = Kernel._exp->precedence);
      _void_(Core.glb->domain = Kernel._type);
      _void_(Core.glb->range = Kernel._type);
      _void_(Core.glb->dispatcher = 4);
      ;}
    
    Core.glb->addMethod(list::domain(2,Kernel._set,Kernel._type),Kernel._set,
    	NEW_ALLOC,_function_(glb_set,"glb_set"));
    
    Core.glb->addMethod(list::domain(2,Core._Union,Kernel._type),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(glb_Union,"glb_Union"));
    
    Core.glb->addMethod(list::domain(2,Core._Interval,Kernel._type),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(glb_Interval,"glb_Interval"));
    
    Core.glb->addMethod(list::domain(2,Kernel._class,Kernel._type),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(glb_class,"glb_class"));
    
    Core.glb->addMethod(list::domain(2,Core._Param,Kernel._type),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(glb_Param,"glb_Param"));
    
    Core.glb->addMethod(list::domain(2,Core._subtype,Kernel._type),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(glb_subtype,"glb_subtype"));
    
    Core.glb->addMethod(list::domain(2,Kernel._tuple,Kernel._type),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(glb_tuple,"glb_tuple"));
    
    Core.glb->addMethod(list::domain(2,Core._Reference,Kernel._type),Kernel._type,
    	RETURN_ARG,_function_(glb_Reference,"glb_Reference"));
    
    Kernel._exp->addMethod(list::domain(2,Kernel._type,Kernel._type),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(_exp_type,"^_type"));
    
    Core.join->addMethod(list::domain(2,Kernel._class,Kernel._class),Kernel._type,
    	0,_function_(join_class,"join_class"));
    
    Kernel._exp->addMethod(list::domain(2,Kernel._list,Kernel._list),Kernel._list,
    	NEW_ALLOC,_function_(_exp_list,"^_list"));
    
    Core.Uall->addMethod(list::domain(1,Kernel._list),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(Uall_list,"Uall_list"));
    
    { (Core._inf_equalt = (operation *) Kernel._operation->instantiate("<=t",Core.it));
      _void_(Core._inf_equalt->precedence = Kernel._inf_equal->precedence);
      _void_(Core._inf_equalt->domain = Kernel._type);
      _void_(Core._inf_equalt->range = Kernel._boolean);
      _void_(Core._inf_equalt->dispatcher = 5);
      ;}
    
    Core._inf_equalt->addMethod(list::domain(2,Kernel._bag,Kernel._type),Kernel._boolean,
    	NEW_ALLOC,_function_(_inf_equalt_bag2,"<=t_bag2"));
    
    Core._inf_equalt->addMethod(list::domain(2,Kernel._class,Kernel._type),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(_inf_equalt_class,"<=t_class"));
    
    Core._inf_equalt->addMethod(list::domain(2,Core._Union,Kernel._type),Kernel._boolean,
    	NEW_ALLOC,_function_(_inf_equalt_Union,"<=t_Union"));
    
    Core._inf_equalt->addMethod(list::domain(2,Core._Interval,Kernel._type),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(_inf_equalt_Interval,"<=t_Interval"));
    
    Core._inf_equalt->addMethod(list::domain(2,Core._subtype,Kernel._type),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(_inf_equalt_subtype,"<=t_subtype"));
    
    Core._inf_equalt->addMethod(list::domain(2,Core._Param,Kernel._type),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(_inf_equalt_Param,"<=t_Param"));
    
    Core._inf_equalt->addMethod(list::domain(2,Core._Reference,Kernel._type),Kernel._boolean,
    	0,_function_(_inf_equalt_Reference,"<=t_Reference"));
    
    Core._inf_equalt->addMethod(list::domain(2,Kernel._tuple,Kernel._type),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(_inf_equalt_tuple,"<=t_tuple"));
    
    Core._inf_equalt->addMethod(list::domain(2,Kernel._type,Kernel._type),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(_inf_equalt_type,"<=t_type"));
    
    Kernel._inf_equal->addMethod(list::domain(2,Kernel._type,Kernel._type),Kernel._boolean,
    	NEW_ALLOC,_function_(_inf_equal_type,"<=_type"));
    
    Core.member->addMethod(list::domain(1,Kernel._type),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(member_type,"member_type"));
    
    Core.of_extract->addMethod(list::domain(1,Kernel._type),Kernel._type,
    	RETURN_ARG,_function_(of_extract_type,"of_extract_type"));
    
    Core._at->addMethod(list::domain(2,Kernel._type,Kernel._property),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(_at_type,"@_type"));
    
    Core.unique_ask->addMethod(list::domain(1,Kernel._type),Kernel._boolean,
    	0,_function_(unique_ask_type,"unique?_type"));
    
    Core.the->addMethod(list::domain(1,Kernel._type),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(the_type,"the_type"));
    
    Kernel.integer_I->addMethod(list::domain(1,GC_OBJECT(ClaireType,nth_class1(Kernel._set,Kernel._integer))),Kernel._integer,
    	NEW_ALLOC,_function_(integer_I_set,"integer!_set"));
    
    Core.make_set->addMethod(list::domain(1,Kernel._integer),Kernel._set,
    	NEW_ALLOC,_function_(make_set_integer,"make_set_integer"));
    
    Core.abstract_type->addMethod(list::domain(1,Kernel._set),Kernel._type,
    	NEW_ALLOC,_function_(abstract_type_set,"abstract_type_set"));
    
    Core.abstract_type->addMethod(list::domain(3,Kernel._operation,Kernel._type,Kernel._type),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(abstract_type_operation,"abstract_type_operation"));
    
    { set_range_property(Kernel.subclass,Kernel._class,GC_OBJECT(ClaireType,nth_class2(Kernel._set,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,_oid_(Kernel._class)))))));
      set_range_property(Kernel.ancestors,Kernel._class,GC_OBJECT(ClaireType,nth_class2(Kernel._list,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,_oid_(Kernel._class)))))));
      set_range_property(Kernel.descendents,Kernel._class,GC_OBJECT(ClaireType,nth_class2(Kernel._set,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,_oid_(Kernel._class)))))));
      set_range_property(Kernel.definition,Kernel._property,GC_OBJECT(ClaireType,nth_class2(Kernel._list,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,_oid_(Kernel._restriction)))))));
      set_range_property(Kernel.restrictions,Kernel._property,GC_OBJECT(ClaireType,nth_class2(Kernel._list,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,_oid_(Kernel._restriction)))))));
      set_range_property(Kernel.domain,Kernel._restriction,GC_OBJECT(ClaireType,nth_class2(Kernel._list,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,_oid_(Kernel._type)))))));
      set_range_property(Kernel.slots,Kernel._class,GC_OBJECT(ClaireType,nth_class2(Kernel._list,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,_oid_(Kernel._slot)))))));
      }
    
    Core.first_arg_type->addMethod(list::domain(2,Kernel._type,Kernel._type),Kernel._type,
    	RETURN_ARG,_function_(first_arg_type_type,"first_arg_type_type"));
    
    Core.first_arg_type->addMethod(list::domain(3,Kernel._type,Kernel._type,Kernel._type),Kernel._type,
    	RETURN_ARG,_function_(first_arg_type_type2,"first_arg_type_type2"));
    
    Core.second_arg_type->addMethod(list::domain(2,Kernel._type,Kernel._type),Kernel._type,
    	RETURN_ARG,_function_(second_arg_type_type,"second_arg_type_type"));
    
    Core.meet_arg_types->addMethod(list::domain(2,Kernel._type,Kernel._type),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(meet_arg_types_type,"meet_arg_types_type"));
    
    Core.first_member_type->addMethod(list::domain(2,Kernel._type,Kernel._type),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(first_member_type_type,"first_member_type_type"));
    
    Core.append_type->addMethod(list::domain(2,Kernel._type,Kernel._type),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(append_type_type1,"append_type_type1"));
    
    Core.cast_I_type->addMethod(list::domain(2,Kernel._type,Kernel._type),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(cast_I_type_type1,"cast!_type_type1"));
    
    Core.prealloc_set_type->addMethod(list::domain(2,Kernel._type,Kernel._type),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(prealloc_set_type_type1,"prealloc_set_type_type1"));
    
    Core.prealloc_list_type->addMethod(list::domain(2,Kernel._type,Kernel._type),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(prealloc_list_type_type1,"prealloc_list_type_type1"));
    
    _void_(Kernel.nth->addMethod(list::domain(2,Kernel._array,Kernel._integer),Kernel._any,
    	RETURN_ARG,_function_(nth_array,"nth_array"))->typing = _oid_(_function_(nth_array_type,"nth_array_type")));
    
    _void_(Core.make_array->addMethod(list::domain(3,Kernel._integer,Kernel._type,Kernel._any),Kernel._array,
    	NEW_ALLOC,_function_(make_array_integer,"make_array_integer"))->typing = _oid_(_function_(make_array_integer_type,"make_array_integer_type")));
    
    _void_(Kernel.make_list->addMethod(list::domain(3,Kernel._integer,Kernel._type,Kernel._any),Kernel._list,
    	NEW_ALLOC+RETURN_ARG,_function_(make_list_integer2,"make_list_integer2"))->typing = _oid_(_function_(make_list_integer2_type,"make_list_integer2_type")));
    
    Core.make_list_type->addMethod(list::domain(2,Kernel._type,Kernel._type),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(make_list_type_type1,"make_list_type_type1"));
    
    _void_(Core.make_set->addMethod(list::domain(1,GC_OBJECT(ClaireType,nth_class2(Kernel._array,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(Kernel.emptySet,1,_oid_(Kernel._any))))),Kernel._set,
    	NEW_ALLOC+RETURN_ARG,_function_(make_set_array,"make_set_array"))->typing = _oid_(_function_(make_set_array_type,"make_set_array_type")));
    
    _void_(Kernel.list_I->addMethod(list::domain(1,GC_OBJECT(ClaireType,nth_class2(Kernel._array,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(Kernel.emptySet,1,_oid_(Kernel._any))))),Kernel._list,
    	NEW_ALLOC,_function_(list_I_array,"list_I_array"))->typing = _oid_(_function_(list_I_array_type,"list_I_array_type")));
    
    _void_(Kernel.array_I->addMethod(list::domain(1,GC_OBJECT(ClaireType,nth_class2(Kernel._list,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(Kernel.emptySet,1,_oid_(Kernel._any))))),Kernel._array,
    	NEW_ALLOC,_function_(array_I_list,"array_I_list"))->typing = _oid_(_function_(array_I_list_type,"array_I_list_type")));
    
    _void_(Kernel.set_I->addMethod(list::domain(1,GC_OBJECT(ClaireType,nth_class2(Kernel._list,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(Kernel.emptySet,1,_oid_(Kernel._any))))),Kernel._set,
    	NEW_ALLOC+SAFE_RESULT,_function_(set_I_bag,"set_I_bag"))->typing = _oid_(_function_(set_I_bag_type,"set_I_bag_type")));
    
    _void_(Kernel.list_I->addMethod(list::domain(1,GC_OBJECT(ClaireType,nth_class2(Kernel._set,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(Kernel.emptySet,1,_oid_(Kernel._any))))),Kernel._list,
    	NEW_ALLOC+SAFE_RESULT,_function_(list_I_set,"list_I_set"))->typing = _oid_(_function_(list_I_set_type,"list_I_set_type")));
    
    { { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(r);
        for (START(Kernel.copy->restrictions); NEXT(r);)
        if (OBJECT(restriction,r)->domain->length == 1)
         _void_(OBJECT(method,r)->typing = _oid_(Core.Id));
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(r);
        for (START(Kernel.empty->restrictions); NEXT(r);)
        _void_(OBJECT(method,r)->typing = _oid_(Core.Id));
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(r);
        for (START(Core.sort->restrictions); NEXT(r);)
        _void_(OBJECT(method,r)->typing = _oid_(Core.second_arg_type));
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(r);
        for (START(Kernel._7_plus->restrictions); NEXT(r);)
        _void_(OBJECT(method,r)->typing = _oid_(Core.append_type));
        }
      _void_(CLREAD(method,_at_property1(Kernel.cast_I,Kernel._set),typing) = _oid_(Core.cast_I_type));
      _void_(CLREAD(method,_at_property1(Kernel.cast_I,Kernel._list),typing) = _oid_(Core.cast_I_type));
      _void_(CLREAD(method,_at_property1(Kernel.prealloc_set,Kernel._type),typing) = _oid_(Core.prealloc_set_type));
      _void_(CLREAD(method,_at_property1(Kernel.prealloc_list,Kernel._type),typing) = _oid_(Core.prealloc_list_type));
      _void_(CLREAD(method,_at_property1(Kernel.make_list,Kernel._type),typing) = _oid_(Core.make_list_type));
      _void_(CLREAD(method,_at_property1(Kernel.nth_get,Kernel._array),typing) = _oid_(Core.first_member_type));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(r);
        for (START(Kernel.nth_plus->restrictions); NEXT(r);)
        _void_(OBJECT(method,r)->typing = _oid_(Core.first_arg_type));
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(r);
        for (START(Kernel.add->restrictions); NEXT(r);)
        if (OBJECT(restriction,r)->domain->length == 2)
         _void_(OBJECT(method,r)->typing = _oid_(Core.first_arg_type));
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(r);
        for (START(Kernel._delete->restrictions); NEXT(r);)
        if (OBJECT(restriction,r)->domain->length == 2)
         _void_(OBJECT(method,r)->typing = _oid_(Core.first_arg_type));
        }
      }
    
    Core.refine_append_of->addMethod(list::domain(3,Kernel._bag,Kernel._bag,Kernel._bag),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(refine_append_of_bag1,"refine_append_of_bag1"));
    
    callback_refine_append_of = refine_append_of_bag1;
    
    Core.set_color->addMethod(list::domain(2,GC_OBJECT(Interval,_dot_dot_integer(30,37)),set::alloc(Kernel.emptySet,2,((OID)0),((OID)1))),Kernel._void,
    	0,_function_(color,"color"));
    
    _void_(OBJECT(restriction,(*(Kernel.freadline->restrictions))[5])->range = tuple::alloc(2,_oid_(Kernel._string),GC_OID(_oid_(U_type(Kernel._string,Kernel._char)))));
    
    _void_(OBJECT(restriction,(*(Kernel.freadline->restrictions))[6])->range = tuple::alloc(2,_oid_(Kernel._string),GC_OID(_oid_(U_type(Kernel._string,Kernel._char)))));
    
    _void_(OBJECT(restriction,(*(Kernel.freadline->restrictions))[7])->range = tuple::alloc(2,_oid_(Kernel._string),GC_OID(_oid_(U_type(Kernel._string,Kernel._char)))));
    
    Core.set_user->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	0,_function_(set_user_string1,"set_user_string1"));
    
    Core.cl_sizeof->addFloatMethod(list::domain(1,Kernel._any),tuple::alloc(2,_oid_(Kernel._integer),_oid_(Kernel._integer)),
    	NEW_ALLOC,_function_(sizeof_any1,"sizeof_any1"),
    _function_(sizeof_any1_,"sizeof_any1_"));
    
    Core.cl_sizeof->addFloatMethod(list::domain(1,Kernel._class),tuple::alloc(2,_oid_(Kernel._integer),_oid_(Kernel._integer)),
    	NEW_ALLOC,_function_(sizeof_class1,"sizeof_class1"),
    _function_(sizeof_class1_,"sizeof_class1_"));
    
    { (Core.none = (keyword *) Kernel._keyword->instantiate("none",claire.it));
      ;}
    
    (Core._dbg_frame = ClaireClass::make("dbg_frame",Core._ephemeral_object,Core.it));
    
    { (Core._dbg_frame = ClaireClass::make("dbg_frame",Core._ephemeral_object,Core.it));
      CL_ADD_SLOT(Core._dbg_frame,Core_dbg_frame,Core.vars,vars,nth_class1(Kernel._list,Kernel._any),CNULL);
      CL_ADD_SLOT(Core._dbg_frame,Core_dbg_frame,Core.num,num,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Core._dbg_frame,Core_dbg_frame,Core.step_ask,step_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Core._dbg_frame,Core_dbg_frame,Core.dimension,dimension,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Core._dbg_frame,Core_dbg_frame,Core.frame_source,frame_source,Kernel._any,CNULL);
      CL_ADD_SLOT(Core._dbg_frame,Core_dbg_frame,Core.compiled_ask,compiled_ask,Kernel._boolean,CNULL);
      CL_ADD_SLOT(Core._dbg_frame,Core_dbg_frame,Kernel.source,source,Kernel._string,_string_(((char*)"")));
      CL_ADD_SLOT(Core._dbg_frame,Core_dbg_frame,Core.line,line,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Core._dbg_frame,Core_dbg_frame,Core.column,column,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Core._dbg_frame,Core_dbg_frame,Kernel.length,length,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Core._dbg_frame,Core_dbg_frame,Core.catch_ask,catch_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Core._dbg_frame,Core_dbg_frame,Core.new_ask,new_ask,Kernel._boolean,Kernel.ctrue);
      CL_ADD_SLOT(Core._dbg_frame,Core_dbg_frame,Core.prev,prev,Core._dbg_frame,CNULL);
      CL_ADD_SLOT(Core._dbg_frame,Core_dbg_frame,Core.next,next,Core._dbg_frame,CNULL);
      }
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core.top_frame = (global_variable *) Core._global_variable->instantiate("top_frame",Core.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      { global_variable * g0304 = _CL_obj; 
        OID  g0305;
        { Core_dbg_frame * _CL_obj = ((Core_dbg_frame *) GC_OBJECT(Core_dbg_frame,new_object_class(Core._dbg_frame)));
          _void_(_CL_obj->source = string_v(CLREAD(slot,_at_property1(Kernel.source,Core._dbg_frame),DEFAULT)));
          g0305 = _oid_(_CL_obj);
          }
        _void_(g0304->value = g0305);}
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Core.current_frame = (global_variable *) Core._global_variable->instantiate("current_frame",Core.it));
      _void_(_CL_obj->range = Core._dbg_frame);
      _void_(_CL_obj->value = Core.top_frame->value);
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Core.reset_frame_stack->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(reset_frame_stack_void1,"reset_frame_stack_void1"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core.STEP = (global_variable *) Core._global_variable->instantiate("STEP",Core.it));
      _void_(_CL_obj->range = Kernel._integer);
      _void_(_CL_obj->value = ((OID)0));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Core.push_frame->addMethod(list::domain(1,Kernel._any),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE,_function_(push_frame_any1,"push_frame_any1"));
    
    Core.pop_frame->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(pop_frame_void1,"pop_frame_void1"));
    
    Core.push_arg->addMethod(list::domain(2,Kernel._string,Kernel._any),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(push_arg_string1,"push_arg_string1"));
    
    Core.push_var->addMethod(list::domain(2,Kernel._string,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(push_var_string1,"push_var_string1"));
    
    Core.pop_var->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	0,_function_(pop_var_void1,"pop_var_void1"));
    
    Core.update_var->addMethod(list::domain(2,Kernel._string,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(update_var_string1,"update_var_string1"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core.BREAKPOINTS = (global_variable *) Core._global_variable->instantiate("BREAKPOINTS",claire.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(set::empty(Kernel._any)));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
{ (Core.on_break_program = property::make("on_break_program",3,Core.it,Kernel._any,0));
      _void_(Core.on_break_program->open = 3);
      ;}
    
    Core.update_location->addMethod(list::domain(4,Kernel._string,
      Kernel._integer,
      Kernel._integer,
      Kernel._integer),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(update_location_string1,"update_location_string1"));
    
    Core.break_if_needed->addMethod(list::domain(2,Core._dbg_frame,Kernel._integer),Kernel._void,
    	NEW_ALLOC,_function_(break_if_needed_dbg_frame1,"break_if_needed_dbg_frame1"));
    
    { (Core.HANDLE_FRAMES = (table *) Kernel._table->instantiate("HANDLE_FRAMES",Core.it));
      _void_(Core.HANDLE_FRAMES->range = Core._dbg_frame);
      _void_(Core.HANDLE_FRAMES->params = _oid_(Kernel._any));
      _void_(Core.HANDLE_FRAMES->domain = Kernel._string);
      _void_(Core.HANDLE_FRAMES->graph = make_list_integer(29,CNULL));
      _void_(Core.HANDLE_FRAMES->DEFAULT = Core.top_frame->value);
      }
    
    Core.push_handle->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	BAG_UPDATE+RETURN_ARG,_function_(push_handle_string1,"push_handle_string1"));
    
    Core.pop_handle->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(pop_handle_string1,"pop_handle_string1"));
    
    Core.push_handle_frame->addMethod(list::domain(5,Kernel._string,
      Kernel._integer,
      Kernel._integer,
      Kernel._integer,
      Kernel._string),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE,_function_(push_handle_frame_string1,"push_handle_frame_string1"));
    
    Core.dload->addMethod(list::domain(2,Kernel._string,Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(dload_string1,"dload_string1"));
    
    { (Core._signal_handler = ClaireClass::make("signal_handler",Kernel._thing,claire.it));
      CL_ADD_SLOT(Core._signal_handler,signal_handler,Core.signo,signo,Kernel._integer,((OID)-1));
      CL_ADD_SLOT(Core._signal_handler,signal_handler,Core.handler,handler,Kernel._property,CNULL);
      }
    
    { (Core.CL_SIGHUP = (signal_handler *) Core._signal_handler->instantiate("SIGHUP",claire.it));
      ;}
    
    { 
#ifdef SIGHUP
;
      _void_(Core.CL_SIGHUP->signo = (CL_INT )(SIGHUP));
      
#endif
;
      }
    
    { (Core.CL_SIGQUIT = (signal_handler *) Core._signal_handler->instantiate("SIGQUIT",claire.it));
      ;}
    
    { 
#ifdef SIGQUIT
;
      _void_(Core.CL_SIGQUIT->signo = (CL_INT )(SIGQUIT));
      
#endif
;
      }
    
    { (Core.CL_SIGILL = (signal_handler *) Core._signal_handler->instantiate("SIGILL",claire.it));
      ;}
    
    { 
#ifdef SIGILL
;
      _void_(Core.CL_SIGILL->signo = (CL_INT )(SIGILL));
      
#endif
;
      }
    
    { (Core.CL_SIGTRAP = (signal_handler *) Core._signal_handler->instantiate("SIGTRAP",claire.it));
      ;}
    
    { 
#ifdef SIGTRAP
;
      _void_(Core.CL_SIGTRAP->signo = (CL_INT )(SIGTRAP));
      
#endif
;
      }
    
    { (Core.CL_SIGABRT = (signal_handler *) Core._signal_handler->instantiate("SIGABRT",claire.it));
      ;}
    
    { 
#ifdef SIGABRT
;
      _void_(Core.CL_SIGABRT->signo = (CL_INT )(SIGABRT));
      
#endif
;
      }
    
    { (Core.CL_SIGEMT = (signal_handler *) Core._signal_handler->instantiate("SIGEMT",claire.it));
      ;}
    
    { 
#ifdef SIGEMT
;
      _void_(Core.CL_SIGEMT->signo = (CL_INT )(SIGEMT));
      
#endif
;
      }
    
    { (Core.CL_SIGFPE = (signal_handler *) Core._signal_handler->instantiate("SIGFPE",claire.it));
      ;}
    
    { 
#ifdef SIGFPE
;
      _void_(Core.CL_SIGFPE->signo = (CL_INT )(SIGFPE));
      
#endif
;
      }
    
    { (Core.CL_SIGKILL = (signal_handler *) Core._signal_handler->instantiate("SIGKILL",claire.it));
      ;}
    
    { 
#ifdef SIGKILL
;
      _void_(Core.CL_SIGKILL->signo = (CL_INT )(SIGKILL));
      
#endif
;
      }
    
    { (Core.CL_SIGBUS = (signal_handler *) Core._signal_handler->instantiate("SIGBUS",claire.it));
      ;}
    
    { 
#ifdef SIGBUS
;
      _void_(Core.CL_SIGBUS->signo = (CL_INT )(SIGBUS));
      
#endif
;
      }
    
    { (Core.CL_SIGSEGV = (signal_handler *) Core._signal_handler->instantiate("SIGSEGV",claire.it));
      ;}
    
    { 
#ifdef SIGSEGV
;
      _void_(Core.CL_SIGSEGV->signo = (CL_INT )(SIGSEGV));
      
#endif
;
      }
    
    { (Core.CL_SIGSYS = (signal_handler *) Core._signal_handler->instantiate("SIGSYS",claire.it));
      ;}
    
    { 
#ifdef SIGSYS
;
      _void_(Core.CL_SIGSYS->signo = (CL_INT )(SIGSYS));
      
#endif
;
      }
    
    { (Core.CL_SIGPIPE = (signal_handler *) Core._signal_handler->instantiate("SIGPIPE",claire.it));
      ;}
    
    { 
#ifdef SIGPIPE
;
      _void_(Core.CL_SIGPIPE->signo = (CL_INT )(SIGPIPE));
      
#endif
;
      }
    
    { (Core.CL_SIGALRM = (signal_handler *) Core._signal_handler->instantiate("SIGALRM",claire.it));
      ;}
    
    { 
#ifdef SIGALRM
;
      _void_(Core.CL_SIGALRM->signo = (CL_INT )(SIGALRM));
      
#endif
;
      }
    
    { (Core.CL_SIGTERM = (signal_handler *) Core._signal_handler->instantiate("SIGTERM",claire.it));
      ;}
    
    { 
#ifdef SIGTERM
;
      _void_(Core.CL_SIGTERM->signo = (CL_INT )(SIGTERM));
      
#endif
;
      }
    
    { (Core.CL_SIGURG = (signal_handler *) Core._signal_handler->instantiate("SIGURG",claire.it));
      ;}
    
    { 
#ifdef SIGURG
;
      _void_(Core.CL_SIGURG->signo = (CL_INT )(SIGURG));
      
#endif
;
      }
    
    { (Core.CL_SIGSTOP = (signal_handler *) Core._signal_handler->instantiate("SIGSTOP",claire.it));
      ;}
    
    { 
#ifdef SIGSTOP
;
      _void_(Core.CL_SIGSTOP->signo = (CL_INT )(SIGSTOP));
      
#endif
;
      }
    
    { (Core.CL_SIGTSTP = (signal_handler *) Core._signal_handler->instantiate("SIGTSTP",claire.it));
      ;}
    
    { 
#ifdef SIGTSTP
;
      _void_(Core.CL_SIGTSTP->signo = (CL_INT )(SIGTSTP));
      
#endif
;
      }
    
    { (Core.CL_SIGCONT = (signal_handler *) Core._signal_handler->instantiate("SIGCONT",claire.it));
      ;}
    
    { 
#ifdef SIGCONT
;
      _void_(Core.CL_SIGCONT->signo = (CL_INT )(SIGCONT));
      
#endif
;
      }
    
    { (Core.CL_SIGCHLD = (signal_handler *) Core._signal_handler->instantiate("SIGCHLD",claire.it));
      ;}
    
    { 
#ifdef SIGCHLD
;
      _void_(Core.CL_SIGCHLD->signo = (CL_INT )(SIGCHLD));
      
#endif
;
      }
    
    { (Core.CL_SIGTTIN = (signal_handler *) Core._signal_handler->instantiate("SIGTTIN",claire.it));
      ;}
    
    { 
#ifdef SIGTTIN
;
      _void_(Core.CL_SIGTTIN->signo = (CL_INT )(SIGTTIN));
      
#endif
;
      }
    
    { (Core.CL_SIGTTOU = (signal_handler *) Core._signal_handler->instantiate("SIGTTOU",claire.it));
      ;}
    
    { 
#ifdef SIGTTOU
;
      _void_(Core.CL_SIGTTOU->signo = (CL_INT )(SIGTTOU));
      
#endif
;
      }
    
    { (Core.CL_SIGIO = (signal_handler *) Core._signal_handler->instantiate("SIGIO",claire.it));
      ;}
    
    { 
#ifdef SIGIO
;
      _void_(Core.CL_SIGIO->signo = (CL_INT )(SIGIO));
      
#endif
;
      }
    
    { (Core.CL_SIGXCPU = (signal_handler *) Core._signal_handler->instantiate("SIGXCPU",claire.it));
      ;}
    
    { 
#ifdef SIGXCPU
;
      _void_(Core.CL_SIGXCPU->signo = (CL_INT )(SIGXCPU));
      
#endif
;
      }
    
    { (Core.CL_SIGXFSZ = (signal_handler *) Core._signal_handler->instantiate("SIGXFSZ",claire.it));
      ;}
    
    { 
#ifdef SIGXFSZ
;
      _void_(Core.CL_SIGXFSZ->signo = (CL_INT )(SIGXFSZ));
      
#endif
;
      }
    
    { (Core.CL_SIGVTALRM = (signal_handler *) Core._signal_handler->instantiate("SIGVTALRM",claire.it));
      ;}
    
    { 
#ifdef SIGVTALRM
;
      _void_(Core.CL_SIGVTALRM->signo = (CL_INT )(SIGVTALRM));
      
#endif
;
      }
    
    { (Core.CL_SIGPROF = (signal_handler *) Core._signal_handler->instantiate("SIGPROF",claire.it));
      ;}
    
    { 
#ifdef SIGPROF
;
      _void_(Core.CL_SIGPROF->signo = (CL_INT )(SIGPROF));
      
#endif
;
      }
    
    { (Core.CL_SIGWINCH = (signal_handler *) Core._signal_handler->instantiate("SIGWINCH",claire.it));
      ;}
    
    { 
#ifdef SIGWINCH
;
      _void_(Core.CL_SIGWINCH->signo = (CL_INT )(SIGWINCH));
      
#endif
;
      }
    
    { (Core.CL_SIGINFO = (signal_handler *) Core._signal_handler->instantiate("SIGINFO",claire.it));
      ;}
    
    { 
#ifdef SIGINFO
;
      _void_(Core.CL_SIGINFO->signo = (CL_INT )(SIGINFO));
      
#endif
;
      }
    
    { (Core.CL_SIGUSR1 = (signal_handler *) Core._signal_handler->instantiate("SIGUSR1",claire.it));
      ;}
    
    { 
#ifdef SIGUSR1
;
      _void_(Core.CL_SIGUSR1->signo = (CL_INT )(SIGUSR1));
      
#endif
;
      }
    
    { (Core.CL_SIGUSR2 = (signal_handler *) Core._signal_handler->instantiate("SIGUSR2",claire.it));
      ;}
    
    { 
#ifdef SIGUSR2
;
      _void_(Core.CL_SIGUSR2->signo = (CL_INT )(SIGUSR2));
      
#endif
;
      }
    
    { (Core.CL_SIGINT = (signal_handler *) Core._signal_handler->instantiate("SIGINT",claire.it));
      ;}
    
    { 
#ifdef SIGINT
;
      _void_(Core.CL_SIGINT->signo = (CL_INT )(SIGINT));
      
#endif
;
      }
    
    { (Core.CL_SIG_DFL = property::make("SIG_DFL",2,claire.it,Kernel._any,0));
      ;}
    
    { (Core.CL_SIG_IGN = property::make("SIG_IGN",2,claire.it,Kernel._any,0));
      ;}
    
    { (Core.SIG_EXT = property::make("SIG_EXT",2,claire.it,Kernel._any,0));
      ;}
    
    { (Core.SIG_MAP = (table *) Kernel._table->instantiate("SIG_MAP",Core.it));
      _void_(Core.SIG_MAP->range = Core._signal_handler);
      _void_(Core.SIG_MAP->params = _oid_(Kernel._any));
      _void_(Core.SIG_MAP->domain = Kernel._integer);
      _void_(Core.SIG_MAP->graph = make_list_integer(29,CNULL));
      _void_(Core.SIG_MAP->DEFAULT = _oid_(Core.CL_SIGHUP));
      }
    
    { 
#ifndef CLPC
;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(g0141);
        bag *g0141_support;
        g0141_support = Core._signal_handler->descendents;
        for (START(g0141_support); NEXT(g0141);)
        { ClaireBoolean * g0142;
          { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(sig);
              V_C= Kernel.cfalse;
              for (START(OBJECT(ClaireClass,g0141)->instances); NEXT(sig);)
              if (OBJECT(signal_handler,sig)->signo != ((CL_INT)-1))
               { put_table(Core.SIG_MAP,((OID)OBJECT(signal_handler,sig)->signo),sig);
                { signal_handler * sh = OBJECT(signal_handler,sig);
                  void (*h)(CL_INT) = (void (*)(CL_INT))::signal(sh->signo, SIG_DFL);
                  { signal_handler * g0306 = sh; 
                    property * g0307;
                    if ((CL_INT )((h == (void (*)(CL_INT))SIG_DFL)) == 1)
                     g0307 = Core.CL_SIG_DFL;
                    else if ((CL_INT )((h == (void (*)(CL_INT))SIG_IGN)) == 1)
                     { ::signal(sh->signo, SIG_IGN);
                      g0307 = Core.CL_SIG_IGN;
                      }
                    else { ::signal(sh->signo, (void (*)(int))h);
                        if (should_trace_ask_module1(Core.it,1) == CTRUE)
                         mtformat_module1(Core.it,((char*)"---- Warning : signal ~S:~S is in use\n"),1,GC_OBJECT(list,list::alloc(2,_oid_(sh),((OID)sh->signo))));
                        else ;g0307 = Core.SIG_EXT;
                        }
                      _void_(g0306->handler = g0307);}
                  }
                }
              }
            
            g0142=OBJECT(ClaireBoolean,V_C);}
          if (g0142 == CTRUE)
           { ;ClEnv->cHandle = loop_handle; break;}
          }
        }
      
#else
;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(g0143);
        bag *g0143_support;
        g0143_support = Core._signal_handler->descendents;
        for (START(g0143_support); NEXT(g0143);)
        { ClaireBoolean * g0144;
          { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(sig);
              V_C= Kernel.cfalse;
              for (START(OBJECT(ClaireClass,g0143)->instances); NEXT(sig);)
              if (OBJECT(signal_handler,sig)->signo != ((CL_INT)-1))
               { _void_(OBJECT(signal_handler,sig)->handler = Core.CL_SIG_DFL);
                put_table(Core.SIG_MAP,((OID)OBJECT(signal_handler,sig)->signo),sig);
                }
              }
            
            g0144=OBJECT(ClaireBoolean,V_C);}
          if (g0144 == CTRUE)
           { ;ClEnv->cHandle = loop_handle; break;}
          }
        }
      
#endif
;
      }
    
    Core.signal->addMethod(list::domain(2,Core._signal_handler,Kernel._property),Kernel._property,
    	SLOT_UPDATE,_function_(signal_signal_handler,"signal_signal_handler"));
    
    Core.meta_sighandler->addMethod(list::domain(1,Kernel._integer),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(meta_sighandler_integer,"meta_sighandler_integer"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core.SHOULD_BREAK_ask = (global_variable *) Core._global_variable->instantiate("SHOULD_BREAK?",Core.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.cfalse);
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Core.raise->addMethod(list::domain(1,Core._signal_handler),Kernel._void,
    	0,_function_(raise_signal_handler,"raise_signal_handler"));
    
    Kernel.kill->addMethod(list::domain(2,Kernel._integer,Core._signal_handler),Kernel._void,
    	0,_function_(kill_integer,"kill_integer"));
    
    Core.sigprocmask->addMethod(list::domain(1,Kernel._void),nth_class1(Kernel._set,Core._signal_handler),
    	NEW_ALLOC,_function_(sigprocmask_void,"sigprocmask_void"));
    
    Core.sigsetmask->addMethod(list::domain(1,GC_OBJECT(ClaireType,nth_class1(Kernel._type,Core._signal_handler))),nth_class1(Kernel._set,Core._signal_handler),
    	NEW_ALLOC,_function_(sigsetmask_type,"sigsetmask_type"));
    
    Core.sigpending->addMethod(list::domain(1,Kernel._void),nth_class1(Kernel._set,Core._signal_handler),
    	NEW_ALLOC,_function_(sigpending_void,"sigpending_void"));
    
    Core.sigblock->addMethod(list::domain(1,GC_OBJECT(ClaireType,nth_class1(Kernel._type,Core._signal_handler))),nth_class1(Kernel._set,Core._signal_handler),
    	NEW_ALLOC,_function_(sigblock_type,"sigblock_type"));
    
    Core.sigunblock->addMethod(list::domain(1,GC_OBJECT(ClaireType,nth_class1(Kernel._type,Core._signal_handler))),nth_class1(Kernel._set,Core._signal_handler),
    	NEW_ALLOC,_function_(sigunblock_type,"sigunblock_type"));
    
    Core.sigsuspend->addMethod(list::domain(1,GC_OBJECT(ClaireType,nth_class1(Kernel._type,Core._signal_handler))),Kernel._void,
    	NEW_ALLOC,_function_(sigsuspend_type,"sigsuspend_type"));
    
    
#ifndef CLPC
	    ::signal(SIGINT, kernel_sighandler_integer);
	      #ifdef HAVE_SIGINTERRUPT
	        siginterrupt(SIGINT, 1);
	      #endif
	    #endif
;
    
    { (Core._itimer = ClaireClass::make("itimer",Kernel._thing,Core.it));
      CL_ADD_SLOT(Core._itimer,Core_itimer,Core.timerno,timerno,Kernel._integer,CNULL);
      }
    
    { (Core.CL_ITIMER_REAL = (Core_itimer *) Core._itimer->instantiate("ITIMER_REAL",claire.it));
      ;}
    
    { 
#ifdef ITIMER_REAL
;
      _void_(Core.CL_ITIMER_REAL->timerno = (CL_INT )(ITIMER_REAL));
      
#endif
;
      }
    
    { (Core.CL_ITIMER_VIRTUAL = (Core_itimer *) Core._itimer->instantiate("ITIMER_VIRTUAL",claire.it));
      ;}
    
    { 
#ifdef ITIMER_VIRTUAL
;
      _void_(Core.CL_ITIMER_VIRTUAL->timerno = (CL_INT )(ITIMER_VIRTUAL));
      
#endif
;
      }
    
    { (Core.CL_ITIMER_PROF = (Core_itimer *) Core._itimer->instantiate("ITIMER_PROF",claire.it));
      ;}
    
    { 
#ifdef ITIMER_PROF
;
      _void_(Core.CL_ITIMER_PROF->timerno = (CL_INT )(ITIMER_PROF));
      
#endif
;
      }
    
    Core.setitimer->addFloatMethod(list::domain(3,Core._itimer,Kernel._integer,Kernel._integer),tuple::alloc(2,_oid_(Kernel._integer),_oid_(Kernel._integer)),
    	NEW_ALLOC,_function_(setitimer_itimer,"setitimer_itimer"),
    _function_(setitimer_itimer_,"setitimer_itimer_"));
    
    Core.getitimer->addFloatMethod(list::domain(1,Core._itimer),tuple::alloc(2,_oid_(Kernel._integer),_oid_(Kernel._integer)),
    	NEW_ALLOC,_function_(getitimer_itimer,"getitimer_itimer"),
    _function_(getitimer_itimer_,"getitimer_itimer_"));
    
    (Core._process_status = ClaireClass::make("process_status",Kernel._thing,claire.it));
    
    { (Core.CL_WRUNNING = (process_status *) Core._process_status->instantiate("WRUNNING",claire.it));
      ;}
    
    { (Core.CL_WEXITED = (process_status *) Core._process_status->instantiate("WEXITED",claire.it));
      ;}
    
    { (Core.CL_WSIGNALED = (process_status *) Core._process_status->instantiate("WSIGNALED",claire.it));
      ;}
    
    { (Core.CL_WSTOPPED = (process_status *) Core._process_status->instantiate("WSTOPPED",claire.it));
      ;}
    
    Core.waitpid->addFloatMethod(list::domain(2,Kernel._integer,Kernel._boolean),tuple::alloc(3,_oid_(Core._process_status),
      _oid_(Kernel._integer),
      _oid_(Kernel._any)),
    	NEW_ALLOC,_function_(waitpid_integer1,"waitpid_integer1"),
    _function_(waitpid_integer1_,"waitpid_integer1_"));
    
    Core.waitpid->addFloatMethod(list::domain(1,Kernel._integer),tuple::alloc(3,_oid_(Core._process_status),
      _oid_(Kernel._integer),
      _oid_(Kernel._any)),
    	NEW_ALLOC,_function_(waitpid_integer2,"waitpid_integer2"),
    _function_(waitpid_integer2_,"waitpid_integer2_"));
    
    (Core._char_star = ClaireClass::make("char*",Kernel._cl_import,claire.it));
    
    Core._plus->addMethod(list::domain(2,Core._char_star,Kernel._integer),Core._char_star,
    	0,_function_(_plus_char_star1,"+_char*1"));
    
    Kernel.nth->addMethod(list::domain(2,Core._char_star,Kernel._integer),Kernel._char,
    	0,_function_(nth_char_star1,"nth_char*1"));
    
    Kernel.nth_equal->addMethod(list::domain(3,Core._char_star,Kernel._integer,Kernel._char),Kernel._void,
    	0,_function_(nth_equal_char_star1,"nth=_char*1"));
    
    Kernel.string_I->addMethod(list::domain(2,Core._char_star,Kernel._integer),Kernel._string,
    	NEW_ALLOC,_function_(string_I_char_star1,"string!_char*1"));
    
    Core.char_star_I->addMethod(list::domain(1,Kernel._string),Core._char_star,
    	0,_function_(char_star_I_string1,"char*!_string1"));
    
    _void_(CLREAD(method,_at_property1(Core._plus,Core._char_star),status) = ((CL_INT)exp2_integer(6)+(CL_INT)exp2_integer(5)));
    
    _void_(CLREAD(method,_at_property1(Kernel.nth,Core._char_star),status) = ((CL_INT)exp2_integer(6)+(CL_INT)exp2_integer(5)));
    
    _void_(CLREAD(method,_at_property1(Kernel.nth_equal,Core._char_star),status) = exp2_integer(6));
    
    _void_(CLREAD(method,_at_property1(Kernel.string_I,Core._char_star),status) = ((CL_INT)exp2_integer(6)+(CL_INT)exp2_integer(1)));
    
    { CL_ADD_SLOT(Kernel._port,PortObject,Core.firstc,firstc,Kernel._integer,((OID)integer_I_char(_char_(((unsigned char)' ')))));
      CL_ADD_SLOT(Kernel._port,PortObject,Core.closed_ask,closed_ask,Kernel._boolean,Kernel.cfalse);
      }
    
    (Core._device = ClaireClass::make("device",Kernel._port,claire.it));
    
    (Core._filter = ClaireClass::make("filter",Kernel._port,claire.it));
    
    { (Core._device = ClaireClass::make("device",Kernel._port,claire.it));
      CL_ADD_SLOT(Core._device,device,Core.filters,filters,nth_class1(Kernel._list,Core._filter),CNULL);
      }
    
    { (Core._filter = ClaireClass::make("filter",Kernel._port,claire.it));
      CL_ADD_SLOT(Core._filter,filter,Core.dev,dev,Core._device,CNULL);
      CL_ADD_SLOT(Core._filter,filter,Core.target,target,Kernel._port,CNULL);
      CL_ADD_SLOT(Core._filter,filter,Core.close_target_ask,close_target_ask,Kernel._boolean,Kernel.cfalse);
      }
    
    update_property(Kernel.inverse,
      Core.dev,
      8,
      Kernel._object,
      _oid_(Core.filters));
    
    (Core._null_port = ClaireClass::make("null_port",Core._device,claire.it));
    
    (Core._blob = ClaireClass::make("blob",Core._device,claire.it));
    
    (Core._descriptor = ClaireClass::make("descriptor",Core._device,claire.it));
    
    (Core._disk_file = ClaireClass::make("disk_file",Core._descriptor,claire.it));
    
    (Core._pipe = ClaireClass::make("pipe",Core._descriptor,claire.it));
    
    (Core._socket = ClaireClass::make("socket",Core._descriptor,claire.it));
    
    (Core._listener = ClaireClass::make("listener",Core._socket,claire.it));
    
    (Core._buffer = ClaireClass::make("buffer",Core._filter,claire.it));
    
    (Core._line_buffer = ClaireClass::make("line_buffer",Core._filter,claire.it));
    
    (Core._line_counter = ClaireClass::make("line_counter",Core._filter,claire.it));
    
    (Core._byte_counter = ClaireClass::make("byte_counter",Core._filter,claire.it));
    
    Core.get_top_most->addMethod(list::domain(1,Kernel._port),Kernel._port,
    	RETURN_ARG,_function_(get_top_most_port1,"get_top_most_port1"));
    
    Core.get_device->addMethod(list::domain(1,Kernel._port),Core._device,
    	RETURN_ARG,_function_(get_device_port1,"get_device_port1"));
    
    _void_(Core.filter_I->addMethod(list::domain(2,Core._filter,Kernel._port),Core._filter,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(filter_I_filter1,"filter!_filter1"))->typing = _oid_(_function_(filter_I_filter1_type,"filter!_filter1_type")));
    
    _void_(Core.close_target_I->addMethod(list::domain(1,Core._filter),Core._filter,
    	SLOT_UPDATE+RETURN_ARG,_function_(close_target_I_filter1,"close_target!_filter1"))->typing = _oid_(_function_(close_target_I_filter1_type,"close_target!_filter1_type")));
    
    Core.inner_print->addMethod(list::domain(1,Core._device),Kernel._void,
    	NEW_ALLOC,_function_(inner_print_device1,"inner_print_device1"));
    
    Core.inner_print->addMethod(list::domain(1,Core._filter),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(inner_print_filter1,"inner_print_filter1"));
    
    Kernel.self_print->addMethod(list::domain(1,Core._filter),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_filter1_Core,"self_print_filter1_Core"));
    
    Kernel.self_print->addMethod(list::domain(1,Core._device),Kernel._void,
    	NEW_ALLOC,_function_(self_print_device1_Core,"self_print_device1_Core"));
    
    Kernel.princ->addMethod(list::domain(1,Kernel._port),Kernel._void,
    	0,_function_(princ_port1,"princ_port1"));
    
    { (Core.eof_port_ask = property::make("eof_port?",3,claire.it,Kernel._port,3));
      _void_(Core.eof_port_ask->open = 3);
      _void_(Core.eof_port_ask->range = Kernel._boolean);
      ;}
    
    { (Core.read_port = property::make("read_port",3,claire.it,Kernel._port,6));
      _void_(Core.read_port->open = 3);
      _void_(Core.read_port->range = Kernel._integer);
      ;}
    
    { (Core.unget_port = property::make("unget_port",3,claire.it,Kernel._port,7));
      _void_(Core.unget_port->open = 3);
      _void_(Core.unget_port->range = Kernel._void);
      ;}
    
    { (Core.write_port = property::make("write_port",3,claire.it,Kernel._port,8));
      _void_(Core.write_port->open = 3);
      _void_(Core.write_port->range = Kernel._integer);
      ;}
    
    { (Core.flush_port = property::make("flush_port",3,claire.it,Kernel._port,10));
      _void_(Core.flush_port->open = 3);
      _void_(Core.flush_port->range = Kernel._void);
      ;}
    
    { (Core.close_port = property::make("close_port",3,claire.it,Kernel._port,9));
      _void_(Core.close_port->open = 3);
      _void_(Core.close_port->range = Kernel._void);
      ;}
    
    Core.write_port->addMethod(list::domain(3,Kernel._port,Core._char_star,Kernel._integer),Kernel._integer,
    	NEW_ALLOC,_function_(write_port_port1_Core,"write_port_port1_Core"));
    
    Core.read_port->addMethod(list::domain(3,Kernel._port,Core._char_star,Kernel._integer),Kernel._integer,
    	NEW_ALLOC+RETURN_ARG,_function_(read_port_port1_Core,"read_port_port1_Core"));
    
    Core.unget_port->addMethod(list::domain(3,Kernel._port,Core._char_star,Kernel._integer),Kernel._void,
    	NEW_ALLOC,_function_(unget_port_port1_Core,"unget_port_port1_Core"));
    
    Core.eof_port_ask->addMethod(list::domain(1,Kernel._port),Kernel._boolean,
    	NEW_ALLOC+RETURN_ARG,_function_(eof_port_ask_port1_Core,"eof_port?_port1_Core"));
    
    Core.flush_port->addMethod(list::domain(1,Kernel._port),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(flush_port_port1_Core,"flush_port_port1_Core"));
    
    Core.close_port->addMethod(list::domain(1,Kernel._port),Kernel._void,
    	NEW_ALLOC,_function_(close_port_port1_Core,"close_port_port1_Core"));
    
    ;
    ;
    ;
    ;
    ;
    ;
    Core.eof_ask->addMethod(list::domain(1,Kernel._port),Kernel._boolean,
    	NEW_ALLOC+RETURN_ARG,_function_(eof_ask_port1,"eof?_port1"));
    
    Kernel.fread->addMethod(list::domain(2,Kernel._port,Kernel._integer),Kernel._string,
    	NEW_ALLOC,_function_(fread_port4,"fread_port4"));
    
    Kernel.fread->addMethod(list::domain(2,Kernel._port,Kernel._string),Kernel._integer,
    	NEW_ALLOC,_function_(fread_port5,"fread_port5"));
    
    Kernel.fread->addMethod(list::domain(1,Kernel._port),Kernel._string,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(fread_port6,"fread_port6"));
    
    Core.getc->addMethod(list::domain(1,Kernel._port),Kernel._char,
    	NEW_ALLOC,_function_(getc_port1,"getc_port1"));
    
    Core.unget->addMethod(list::domain(2,Kernel._port,Kernel._string),Kernel._void,
    	NEW_ALLOC,_function_(unget_port1,"unget_port1"));
    
    Core.unget->addMethod(list::domain(2,Kernel._port,Kernel._char),Kernel._void,
    	NEW_ALLOC,_function_(unget_port2,"unget_port2"));
    
    Core.flush->addMethod(list::domain(1,Kernel._port),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(flush_port1,"flush_port1"));
    
    Core.flush->addMethod(list::domain(2,Kernel._port,Kernel._integer),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(flush_port2,"flush_port2"));
    
    Kernel.fwrite->addMethod(list::domain(2,Kernel._string,Kernel._port),Kernel._integer,
    	NEW_ALLOC,_function_(fwrite_string2,"fwrite_string2"));
    
    Core.putc->addMethod(list::domain(2,Kernel._char,Kernel._port),Kernel._void,
    	NEW_ALLOC,_function_(putc_char1,"putc_char1"));
    
    Kernel.freadwrite->addMethod(list::domain(2,Kernel._port,Kernel._port),Kernel._integer,
    	NEW_ALLOC,_function_(freadwrite_port3,"freadwrite_port3"));
    
    Kernel.freadwrite->addMethod(list::domain(3,Kernel._port,Kernel._port,Kernel._integer),Kernel._integer,
    	NEW_ALLOC,_function_(freadwrite_port4,"freadwrite_port4"));
    
    Core.fskip->addMethod(list::domain(2,Kernel._port,Kernel._integer),Kernel._integer,
    	NEW_ALLOC,_function_(fskip_port1,"fskip_port1"));
    
    Core.fclose->addMethod(list::domain(1,Kernel._port),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(fclose_port1,"fclose_port1"));
    
    Core.get_filter->addMethod(list::domain(2,Kernel._port,Kernel._class),Kernel._port,
    	0,_function_(get_filter_port1,"get_filter_port1"));
    
    Kernel.prefree_I->addMethod(list::domain(1,Core._filter),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(prefree_I_filter1,"prefree!_filter1"));
    
    Kernel.free_I->addMethod(list::domain(1,Core._device),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(free_I_port2_Core,"free!_port2_Core"));
    
    (Core._null_port = ClaireClass::make("null_port",Core._device,claire.it));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core.null = (global_variable *) Core._global_variable->instantiate("null",claire.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      { global_variable * g0308 = _CL_obj; 
        OID  g0309;
        { null_port * _CL_obj = ((null_port *) GC_OBJECT(null_port,new_object_class(Core._null_port)));
          g0309 = _oid_(_CL_obj);
          }
        _void_(g0308->value = g0309);}
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Core.null_I->addMethod(list::domain(1,Kernel._void),Core._null_port,
    	0,_function_(null_I_void1,"null!_void1"));
    
    Core.read_port->addMethod(list::domain(3,Core._null_port,Core._char_star,Kernel._integer),Kernel._integer,
    	0,_function_(read_port_null_port1_Core,"read_port_null_port1_Core"));
    
    Core.eof_port_ask->addMethod(list::domain(1,Core._null_port),Kernel._boolean,
    	0,_function_(eof_port_ask_null_port1_Core,"eof_port?_null_port1_Core"));
    
    Core.write_port->addMethod(list::domain(3,Core._null_port,Core._char_star,Kernel._integer),Kernel._integer,
    	SAFE_RESULT,_function_(write_port_null_port1_Core,"write_port_null_port1_Core"));
    
    Core.flush_port->addMethod(list::domain(1,Core._null_port),Kernel._void,
    	0,_function_(flush_port_null_port1_Core,"flush_port_null_port1_Core"));
    
    Core.close_port->addMethod(list::domain(1,Core._null_port),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(close_port_null_port1_Core,"close_port_null_port1_Core"));
    
    { (Core._blob = ClaireClass::make("blob",Core._device,claire.it));
      CL_ADD_SLOT(Core._blob,blob,Core.data,data,Core._char_star,CNULL);
      CL_ADD_SLOT(Core._blob,blob,Core.alloc_length,alloc_length,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Core._blob,blob,Core.read_index,read_index,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Core._blob,blob,Core.write_index,write_index,Kernel._integer,((OID)0));
      }
    
    (Core._clob = ClaireClass::make("clob",Core._blob,claire.it));
    
    Kernel.princ->addMethod(list::domain(1,Core._blob),Kernel._void,
    	NEW_ALLOC,_function_(princ_blob1,"princ_blob1"));
    
    Core.write_attempt->addMethod(list::domain(2,Core._blob,Kernel._integer),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(write_attempt_blob1,"write_attempt_blob1"));
    
    Core.unget_port->addMethod(list::domain(3,Core._blob,Core._char_star,Kernel._integer),Kernel._void,
    	SLOT_UPDATE,_function_(unget_port_blob1_Core,"unget_port_blob1_Core"));
    
    Core.blob_I->addMethod(list::domain(1,Kernel._void),Core._blob,
    	NEW_ALLOC+SLOT_UPDATE,_function_(blob_I_void1,"blob!_void1"));
    
    Core.blob_I->addMethod(list::domain(1,Core._blob),Core._blob,
    	NEW_ALLOC+SLOT_UPDATE,_function_(blob_I_blob1,"blob!_blob1"));
    
    Core.blob_I->addMethod(list::domain(1,Kernel._port),Core._blob,
    	NEW_ALLOC+SLOT_UPDATE,_function_(blob_I_port1,"blob!_port1"));
    
    Core.blob_I->addMethod(list::domain(1,Kernel._string),Core._blob,
    	NEW_ALLOC+SLOT_UPDATE,_function_(blob_I_string1,"blob!_string1"));
    
    Core.blob_I->addMethod(list::domain(1,Kernel._integer),Core._blob,
    	NEW_ALLOC+SLOT_UPDATE,_function_(blob_I_integer1,"blob!_integer1"));
    
    Core.clob_I->addMethod(list::domain(1,Kernel._void),Core._clob,
    	NEW_ALLOC+SLOT_UPDATE,_function_(clob_I_void1,"clob!_void1"));
    
    Core.clob_I->addMethod(list::domain(1,Kernel._string),Core._clob,
    	NEW_ALLOC+SLOT_UPDATE,_function_(clob_I_string1,"clob!_string1"));
    
    Core.clob_I->addMethod(list::domain(1,Kernel._port),Core._clob,
    	NEW_ALLOC,_function_(clob_I_port1,"clob!_port1"));
    
    Core.clob_I->addMethod(list::domain(1,Kernel._integer),Core._clob,
    	NEW_ALLOC+SLOT_UPDATE,_function_(clob_I_integer1,"clob!_integer1"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core.port_I = (global_variable *) Core._global_variable->instantiate("port!",claire.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(Core.blob_I));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Core.remain_for_write->addMethod(list::domain(1,Core._blob),Kernel._integer,
    	RETURN_ARG,_function_(remain_for_write_blob1,"remain_for_write_blob1"));
    
    Core.remain_to_read->addMethod(list::domain(1,Core._blob),Kernel._integer,
    	RETURN_ARG,_function_(remain_to_read_blob1,"remain_to_read_blob1"));
    
    Core.eof_port_ask->addMethod(list::domain(1,Core._blob),Kernel._boolean,
    	0,_function_(eof_port_ask_blob1_Core,"eof_port?_blob1_Core"));
    
    Core.read_port->addMethod(list::domain(3,Core._blob,Core._char_star,Kernel._integer),Kernel._integer,
    	SLOT_UPDATE,_function_(read_port_blob1_Core,"read_port_blob1_Core"));
    
    Core.write_port->addMethod(list::domain(3,Core._blob,Core._char_star,Kernel._integer),Kernel._integer,
    	SLOT_UPDATE+SAFE_RESULT,_function_(write_port_blob1_Core,"write_port_blob1_Core"));
    
    Core.close_port->addMethod(list::domain(1,Core._blob),Kernel._void,
    	0,_function_(close_port_blob1_Core,"close_port_blob1_Core"));
    
    Kernel.string_I->addMethod(list::domain(1,Core._blob),Kernel._string,
    	NEW_ALLOC,_function_(string_I_blob1,"string!_blob1"));
    
    Kernel.nth->addMethod(list::domain(2,Core._blob,Kernel._integer),Kernel._char,
    	0,_function_(nth_blob1,"nth_blob1"));
    
    Kernel.nth_equal->addMethod(list::domain(3,Core._blob,Kernel._integer,Kernel._char),Kernel._void,
    	0,_function_(nth_equal_blob1,"nth=_blob1"));
    
    Kernel.length->addMethod(list::domain(1,Core._blob),Kernel._integer,
    	RETURN_ARG,_function_(length_blob1,"length_blob1"));
    
    Core.set_length->addMethod(list::domain(2,Core._blob,Kernel._integer),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(set_length_blob1,"set_length_blob1"));
    
    Kernel.substring->addMethod(list::domain(3,Core._blob,Kernel._integer,Kernel._integer),Kernel._string,
    	NEW_ALLOC,_function_(substring_blob1,"substring_blob1"));
    
    Kernel.get_index->addMethod(list::domain(1,Core._blob),Kernel._integer,
    	RETURN_ARG,_function_(get_index_blob1,"get_index_blob1"));
    
    Kernel.set_index->addMethod(list::domain(2,Core._blob,Kernel._integer),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(set_index_blob1,"set_index_blob1"));
    
    { (Core._reverser = ClaireClass::make("reverser",Core._filter,Core.it));
      CL_ADD_SLOT(Core._reverser,Core_reverser,Core.left_to_read,left_to_read,Kernel._integer,((OID)0));
      }
    
    Core.reverser_I->addMethod(list::domain(1,Core._blob),Core._reverser,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(reverser_I_blob1,"reverser!_blob1"));
    
    Core.eof_port_ask->addMethod(list::domain(1,Core._reverser),Kernel._boolean,
    	0,_function_(eof_port_ask_reverser1_Core,"eof_port?_reverser1_Core"));
    
    Core.read_port->addMethod(list::domain(3,Core._reverser,Core._char_star,Kernel._integer),Kernel._integer,
    	SLOT_UPDATE,_function_(read_port_reverser1_Core,"read_port_reverser1_Core"));
    
    { (Core._buffer = ClaireClass::make("buffer",Core._filter,claire.it));
      CL_ADD_SLOT(Core._buffer,buffer,Core.buffer_length,buffer_length,Kernel._integer,CNULL);
      CL_ADD_SLOT(Core._buffer,buffer,Core.pending_r,pending_r,Core._blob,CNULL);
      CL_ADD_SLOT(Core._buffer,buffer,Core.pending_w,pending_w,Core._blob,CNULL);
      }
    
    Core.buffer_I->addMethod(list::domain(2,Kernel._port,Kernel._integer),Core._buffer,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(buffer_I_port1,"buffer!_port1"));
    
    Core.buffer_I->addMethod(list::domain(2,Core._buffer,Kernel._port),Core._buffer,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(buffer_I_buffer1,"buffer!_buffer1"));
    
    Kernel.princ->addMethod(list::domain(1,Core._buffer),Kernel._void,
    	NEW_ALLOC,_function_(princ_buffer1,"princ_buffer1"));
    
    Core.reset_buffer->addMethod(list::domain(1,Kernel._port),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(reset_buffer_port1,"reset_buffer_port1"));
    
    Core.fill_read_buffer->addMethod(list::domain(1,Core._buffer),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(fill_read_buffer_buffer1,"fill_read_buffer_buffer1"));
    
    Core.eof_port_ask->addMethod(list::domain(1,Core._buffer),Kernel._boolean,
    	NEW_ALLOC,_function_(eof_port_ask_buffer1_Core,"eof_port?_buffer1_Core"));
    
    Core.read_port->addMethod(list::domain(3,Core._buffer,Core._char_star,Kernel._integer),Kernel._integer,
    	NEW_ALLOC+SLOT_UPDATE,_function_(read_port_buffer1_Core,"read_port_buffer1_Core"));
    
    Core.unget_port->addMethod(list::domain(3,Core._buffer,Core._char_star,Kernel._integer),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE,_function_(unget_port_buffer1_Core,"unget_port_buffer1_Core"));
    
    Core.flush_port->addMethod(list::domain(1,Core._buffer),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(flush_port_buffer1_Core,"flush_port_buffer1_Core"));
    
    Core.write_port->addMethod(list::domain(3,Core._buffer,Core._char_star,Kernel._integer),Kernel._integer,
    	NEW_ALLOC+SLOT_UPDATE,_function_(write_port_buffer1_Core,"write_port_buffer1_Core"));
    
    Core.close_port->addMethod(list::domain(1,Core._buffer),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(close_port_buffer1_Core,"close_port_buffer1_Core"));
    
    { (Core._line_buffer = ClaireClass::make("line_buffer",Core._filter,claire.it));
      CL_ADD_SLOT(Core._line_buffer,line_buffer,Core.pending,pending,Core._blob,CNULL);
      }
    
    Core.line_buffer_I->addMethod(list::domain(1,Kernel._port),Core._line_buffer,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(line_buffer_I_port1,"line_buffer!_port1"));
    
    Core.flush_port->addMethod(list::domain(1,Core._line_buffer),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(flush_port_line_buffer1_Core,"flush_port_line_buffer1_Core"));
    
    Core.close_port->addMethod(list::domain(1,Core._line_buffer),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(close_port_line_buffer1_Core,"close_port_line_buffer1_Core"));
    
    Core.write_port->addMethod(list::domain(3,Core._line_buffer,Core._char_star,Kernel._integer),Kernel._integer,
    	NEW_ALLOC+SAFE_RESULT,_function_(write_port_line_buffer1_Core,"write_port_line_buffer1_Core"));
    
    { (Core._byte_counter = ClaireClass::make("byte_counter",Core._filter,claire.it));
      CL_ADD_SLOT(Core._byte_counter,byte_counter,Core.written_bytes,written_bytes,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Core._byte_counter,byte_counter,Core.read_bytes,read_bytes,Kernel._integer,((OID)0));
      }
    
    Core.byte_counter_I->addMethod(list::domain(1,Kernel._port),Core._byte_counter,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(byte_counter_I_port1,"byte_counter!_port1"));
    
    Core.byte_counter_I->addMethod(list::domain(2,Core._byte_counter,Kernel._port),Core._byte_counter,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(byte_counter_I_byte_counter1,"byte_counter!_byte_counter1"));
    
    Core.write_port->addMethod(list::domain(3,Core._byte_counter,Core._char_star,Kernel._integer),Kernel._integer,
    	NEW_ALLOC+SLOT_UPDATE,_function_(write_port_byte_counter1_Core,"write_port_byte_counter1_Core"));
    
    Core.read_port->addMethod(list::domain(3,Core._byte_counter,Core._char_star,Kernel._integer),Kernel._integer,
    	NEW_ALLOC+SLOT_UPDATE,_function_(read_port_byte_counter1_Core,"read_port_byte_counter1_Core"));
    
    Core.eof_port_ask->addMethod(list::domain(1,Core._byte_counter),Kernel._boolean,
    	NEW_ALLOC+RETURN_ARG,_function_(eof_port_ask_byte_counter1_Core,"eof_port?_byte_counter1_Core"));
    
    { (Core._line_counter = ClaireClass::make("line_counter",Core._filter,claire.it));
      CL_ADD_SLOT(Core._line_counter,line_counter,Core.written_lines,written_lines,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Core._line_counter,line_counter,Core.line_offset,line_offset,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Core._line_counter,line_counter,Core.prev_line_offset,prev_line_offset,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Core._line_counter,line_counter,Core.read_lines,read_lines,Kernel._integer,((OID)0));
      }
    
    Kernel.princ->addMethod(list::domain(1,Core._line_counter),Kernel._void,
    	NEW_ALLOC,_function_(princ_line_counter1,"princ_line_counter1"));
    
    Core.line_counter_I->addMethod(list::domain(1,Kernel._port),Core._line_counter,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(line_counter_I_port1,"line_counter!_port1"));
    
    Core.line_counter_I->addMethod(list::domain(2,Core._line_counter,Kernel._port),Core._line_counter,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(line_counter_I_line_counter1,"line_counter!_line_counter1"));
    
    Core.write_port->addMethod(list::domain(3,Core._line_counter,Core._char_star,Kernel._integer),Kernel._integer,
    	NEW_ALLOC+SLOT_UPDATE,_function_(write_port_line_counter1_Core,"write_port_line_counter1_Core"));
    
    Core.read_port->addMethod(list::domain(3,Core._line_counter,Core._char_star,Kernel._integer),Kernel._integer,
    	NEW_ALLOC+SLOT_UPDATE,_function_(read_port_line_counter1_Core,"read_port_line_counter1_Core"));
    
    Core.unget_port->addMethod(list::domain(3,Core._line_counter,Core._char_star,Kernel._integer),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE,_function_(unget_port_line_counter1_Core,"unget_port_line_counter1_Core"));
    
    Core.eof_port_ask->addMethod(list::domain(1,Core._line_counter),Kernel._boolean,
    	NEW_ALLOC+RETURN_ARG,_function_(eof_port_ask_line_counter1_Core,"eof_port?_line_counter1_Core"));
    
    { (Core._descriptor = ClaireClass::make("descriptor",Core._device,claire.it));
      CL_ADD_SLOT(Core._descriptor,descriptor,Core.fd,fd,Kernel._integer,((OID)-1));
      CL_ADD_SLOT(Core._descriptor,descriptor,Core.eof_reached_ask,eof_reached_ask,Kernel._boolean,Kernel.cfalse);
      }
    
    signal_signal_handler(Core.CL_SIGPIPE,Core.CL_SIG_IGN);
    
    Kernel.princ->addMethod(list::domain(1,Core._descriptor),Kernel._void,
    	NEW_ALLOC,_function_(princ_descriptor1,"princ_descriptor1"));
    
    Core.close_port->addMethod(list::domain(1,Core._descriptor),Kernel._void,
    	0,_function_(close_port_descriptor1_Core,"close_port_descriptor1_Core"));
    
    Core.eof_port_ask->addMethod(list::domain(1,Core._descriptor),Kernel._boolean,
    	RETURN_ARG,_function_(eof_port_ask_descriptor1_Core,"eof_port?_descriptor1_Core"));
    
    Core.read_port->addMethod(list::domain(3,Core._descriptor,Core._char_star,Kernel._integer),Kernel._integer,
    	SLOT_UPDATE,_function_(read_port_descriptor1_Core,"read_port_descriptor1_Core"));
    
    Core.write_port->addMethod(list::domain(3,Core._descriptor,Core._char_star,Kernel._integer),Kernel._integer,
    	0,_function_(write_port_descriptor1_Core,"write_port_descriptor1_Core"));
    
    Core.terminal_ask->addMethod(list::domain(1,Kernel._port),Kernel._boolean,
    	0,_function_(terminal_ask_port1,"terminal?_port1"));
    
    Core.duplicate->addMethod(list::domain(1,Core._descriptor),Core._descriptor,
    	NEW_ALLOC,_function_(duplicate_descriptor1,"duplicate_descriptor1"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core.Clib_stdin = (global_variable *) Core._global_variable->instantiate("Clib_stdin",Core.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(new_object_class(Core._descriptor)));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Core.Clib_stdout = (global_variable *) Core._global_variable->instantiate("Clib_stdout",Core.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(new_object_class(Core._descriptor)));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Core.Clib_stderr = (global_variable *) Core._global_variable->instantiate("Clib_stderr",Core.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(new_object_class(Core._descriptor)));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;

	#ifdef CLPC
	_setmode(0, _O_BINARY);
	_setmode(1, _O_BINARY);
	_setmode(2, _O_BINARY);
	#endif
;
    
    { _void_(OBJECT(descriptor,Core.Clib_stdin->value)->fd = 0);
      _void_(OBJECT(PortObject,Core.Clib_stdin->value)->closed_ask = CFALSE);
      _void_(OBJECT(device,Core.Clib_stdin->value)->filters = list::empty(Core._filter));
      }
    
    { _void_(OBJECT(descriptor,Core.Clib_stdout->value)->fd = 1);
      _void_(OBJECT(PortObject,Core.Clib_stdout->value)->closed_ask = CFALSE);
      _void_(OBJECT(device,Core.Clib_stdout->value)->filters = list::empty(Core._filter));
      }
    
    { _void_(OBJECT(descriptor,Core.Clib_stderr->value)->fd = 2);
      _void_(OBJECT(PortObject,Core.Clib_stderr->value)->closed_ask = CFALSE);
      _void_(OBJECT(device,Core.Clib_stderr->value)->filters = list::empty(Core._filter));
      }
    
    Kernel.close->addMethod(list::domain(1,Core._descriptor),Core._descriptor,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(close_descriptor1,"close_descriptor1"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core.cl_stdin = (global_variable *) Core._global_variable->instantiate("stdin",claire.it));
      _void_(_CL_obj->range = Kernel._port);
      _void_(_CL_obj->value = Core.Clib_stdin->value);
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Core.cl_stdout = (global_variable *) Core._global_variable->instantiate("stdout",claire.it));
      _void_(_CL_obj->range = Kernel._port);
      { global_variable * g0310 = _CL_obj; 
        OID  g0311;
        if (terminal_ask_port1(OBJECT(PortObject,Core.Clib_stdout->value)) == CTRUE)
         g0311 = _oid_(line_buffer_I_port1(OBJECT(PortObject,Core.Clib_stdout->value)));
        else g0311 = Core.Clib_stdout->value;
          _void_(g0310->value = g0311);}
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Core.cl_stderr = (global_variable *) Core._global_variable->instantiate("stderr",claire.it));
      _void_(_CL_obj->range = Kernel._port);
      _void_(_CL_obj->value = Core.Clib_stderr->value);
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
{ _void_(ClEnv->cout = OBJECT(PortObject,Core.cl_stdout->value));
      _void_(ClEnv->ctrace = OBJECT(PortObject,Core.cl_stdout->value));
      }
    
    { put_property2(Kernel.range,GC_OBJECT(ClaireObject,_at_property1(Core.cpretty,Core._pretty_printer)),_oid_(Core._blob));
      _void_(Core.pretty->cpretty = blob_I_void1());
      }
    
    { _void_(ClEnv->version = 5.0);
      if(LOGO) {;
      princ_string(((char*)"-- CLAIRE run-time library v3."));
      princ_float(5.0);
      princ_string(((char*)" [os:"));
      princ_string(((char*)"Darwin-i386-g++4.2.1"));
      princ_string(((char*)", C++:"));
      princ_string(((char*)"g++"));
      princ_string(((char*)"] --\n"));
      };
      }
    
    Core.select_ask->addMethod(list::domain(1,Kernel._void),Kernel._boolean,
    	0,_function_(select_ask_void1,"select?_void1"));
    
    Core.select_ask->addMethod(list::domain(1,Kernel._integer),Kernel._boolean,
    	0,_function_(select_ask_integer1,"select?_integer1"));
    
    Core.get_descriptor->addMethod(list::domain(1,Kernel._port),Core._descriptor,
    	0,_function_(get_descriptor_port1,"get_descriptor_port1"));
    
    Core.readable_ask->addMethod(list::domain(1,Kernel._port),Kernel._boolean,
    	0,_function_(readable_ask_port1,"readable?_port1"));
    
    Core.readable_ask->addMethod(list::domain(1,Core._descriptor),Kernel._boolean,
    	0,_function_(readable_ask_descriptor1,"readable?_descriptor1"));
    
    Core.writable_ask->addMethod(list::domain(1,Kernel._port),Kernel._boolean,
    	0,_function_(writable_ask_port1,"writable?_port1"));
    
    Core.writable_ask->addMethod(list::domain(1,Core._descriptor),Kernel._boolean,
    	0,_function_(writable_ask_descriptor1,"writable?_descriptor1"));
    
    Core.read_I->addMethod(list::domain(1,Kernel._port),Kernel._void,
    	0,_function_(read_I_port1,"read!_port1"));
    
    Core.read_I->addMethod(list::domain(1,Core._descriptor),Kernel._void,
    	0,_function_(read_I_descriptor1,"read!_descriptor1"));
    
    Core.write_I->addMethod(list::domain(1,Kernel._port),Kernel._void,
    	0,_function_(write_I_port1,"write!_port1"));
    
    Core.write_I->addMethod(list::domain(1,Core._descriptor),Kernel._void,
    	0,_function_(write_I_descriptor1,"write!_descriptor1"));
    
    { (Core._disk_file = ClaireClass::make("disk_file",Core._descriptor,claire.it));
      CL_ADD_SLOT(Core._disk_file,disk_file,Core.file_path,file_path,Kernel._string,CNULL);
      CL_ADD_SLOT(Core._disk_file,disk_file,Core.locked_ask,locked_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Core._disk_file,disk_file,Core.mode,mode,Kernel._integer,CNULL);
      }
    
    Kernel.princ->addMethod(list::domain(1,Core._disk_file),Kernel._void,
    	NEW_ALLOC,_function_(princ_disk_file1,"princ_disk_file1"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core.OPEN_MODE = (global_variable *) Core._global_variable->instantiate("OPEN_MODE",Core.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(set::alloc(Kernel.emptySet,8,_string_(((char*)"r")),
        _string_(((char*)"w")),
        _string_(((char*)"a")),
        _string_(((char*)"rw")),
        _string_(((char*)"wr")),
        _string_(((char*)"rb")),
        _string_(((char*)"wb")),
        _string_(((char*)"ab")))));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Core.disk_file_I->addMethod(list::domain(2,Kernel._string,OBJECT(ClaireType,Core.OPEN_MODE->value)),Core._disk_file,
    	NEW_ALLOC,_function_(disk_file_I_string1,"disk_file!_string1"));
    
    Core.reopen->addMethod(list::domain(1,Kernel._port),Kernel._port,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(reopen_port1,"reopen_port1"));
    
    Core.filepos->addMethod(list::domain(1,Core._disk_file),Kernel._integer,
    	0,_function_(filepos_disk_file1,"filepos_disk_file1"));
    
    Core.setfilepos->addMethod(list::domain(2,Core._disk_file,Kernel._integer),Kernel._void,
    	0,_function_(setfilepos_disk_file1,"setfilepos_disk_file1"));
    
    Core.setfileend->addMethod(list::domain(1,Core._disk_file),Kernel._void,
    	0,_function_(setfileend_disk_file1,"setfileend_disk_file1"));
    
    Core.fopen->addMethod(list::domain(2,Kernel._string,OBJECT(ClaireType,Core.OPEN_MODE->value)),Core._buffer,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(fopen_string1,"fopen_string1"));
    
    Core.get_disk_file->addMethod(list::domain(1,Kernel._port),Core._disk_file,
    	0,_function_(get_disk_file_port1,"get_disk_file_port1"));
    
    Kernel.flock->addMethod(list::domain(1,Kernel._port),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(flock_port1,"flock_port1"));
    
    Kernel.funlock->addMethod(list::domain(1,Kernel._port),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(funlock_port1,"funlock_port1"));
    
    Kernel.islocked_ask->addMethod(list::domain(1,Kernel._port),Kernel._boolean,
    	0,_function_(islocked_ask_port1,"islocked?_port1"));
    
    (Core._pipe = ClaireClass::make("pipe",Core._descriptor,claire.it));
    
    Core.pipe_I->addFloatMethod(list::domain(1,Kernel._void),tuple::alloc(2,_oid_(Core._pipe),_oid_(Core._pipe)),
    	NEW_ALLOC,_function_(pipe_I_void1,"pipe!_void1"),
    _function_(pipe_I_void1_,"pipe!_void1_"));
    
    Kernel.princ->addMethod(list::domain(1,Core._pipe),Kernel._void,
    	NEW_ALLOC,_function_(princ_pipe1,"princ_pipe1"));
    
    { (Core._socket = ClaireClass::make("socket",Core._descriptor,claire.it));
      CL_ADD_SLOT(Core._socket,cl_socket,Core.address,address,Kernel._string,_string_(((char*)"localhost")));
      CL_ADD_SLOT(Core._socket,cl_socket,Core.tcpport,tcpport,Kernel._integer,((OID)-1));
      }
    
    (Core._listener = ClaireClass::make("listener",Core._socket,claire.it));
    
    Kernel.princ->addMethod(list::domain(1,Core._socket),Kernel._void,
    	NEW_ALLOC,_function_(princ_socket1,"princ_socket1"));
    
    Core.close_port->addMethod(list::domain(1,Core._socket),Kernel._void,
    	0,_function_(close_port_socket1_Core,"close_port_socket1_Core"));
    
    Kernel.unlink->addMethod(list::domain(1,Core._listener),Kernel._void,
    	0,_function_(unlink_listener1,"unlink_listener1"));
    
    Core.gethostname->addMethod(list::domain(1,Kernel._void),Kernel._string,
    	NEW_ALLOC,_function_(gethostname_void1,"gethostname_void1"));
    
    Core.client_I->addMethod(list::domain(2,Kernel._string,Kernel._integer),Core._socket,
    	NEW_ALLOC,_function_(client_I_string1,"client!_string1"));
    
    Core.client_I->addMethod(list::domain(1,Kernel._string),Core._socket,
    	NEW_ALLOC+SLOT_UPDATE,_function_(client_I_string2,"client!_string2"));
    
    Core.connect->addMethod(list::domain(2,Kernel._string,Kernel._integer),Kernel._integer,
    	0,_function_(connect_string1,"connect_string1"));
    
    Core.server_I->addMethod(list::domain(1,Kernel._string),Core._listener,
    	NEW_ALLOC+SLOT_UPDATE,_function_(server_I_string2,"server!_string2"));
    
    Core.server_I->addMethod(list::domain(1,Kernel._integer),Core._listener,
    	NEW_ALLOC+SLOT_UPDATE,_function_(server_I_integer1,"server!_integer1"));
    
    Core.server_I->addMethod(list::domain(3,Kernel._string,Kernel._integer,Kernel._integer),Core._listener,
    	NEW_ALLOC+SLOT_UPDATE,_function_(server_I_string1,"server!_string1"));
    
    Core.shutdown->addMethod(list::domain(2,Core._socket,set::alloc(Kernel.emptySet,2,_string_(((char*)"r")),_string_(((char*)"w")))),Kernel._void,
    	0,_function_(shutdown_socket1,"shutdown_socket1"));
    
    Core.linger->addMethod(list::domain(1,Core._socket),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(linger_socket1,"linger_socket1"));
    
    Core.accept->addMethod(list::domain(1,Core._listener),Core._socket,
    	NEW_ALLOC+SLOT_UPDATE,_function_(accept_listener1,"accept_listener1"));
    
    Core.socketpair->addFloatMethod(list::domain(1,Kernel._void),tuple::alloc(2,_oid_(Core._socket),_oid_(Core._socket)),
    	NEW_ALLOC,_function_(socketpair_void1,"socketpair_void1"),
    _function_(socketpair_void1_,"socketpair_void1_"));
    
    Core.read_port->addMethod(list::domain(3,Core._socket,Core._char_star,Kernel._integer),Kernel._integer,
    	SLOT_UPDATE,_function_(read_port_socket1_Core,"read_port_socket1_Core"));
    
    Core.write_port->addMethod(list::domain(3,Core._socket,Core._char_star,Kernel._integer),Kernel._integer,
    	0,_function_(write_port_socket1_Core,"write_port_socket1_Core"));
    
    Core.print_source_location->addMethod(list::domain(1,Kernel._port),Kernel._void,
    	NEW_ALLOC,_function_(print_source_location_port1,"print_source_location_port1"));
    
    Core.get_location->addFloatMethod(list::domain(1,Kernel._port),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._integer),
      _oid_(Kernel._integer)),
    	NEW_ALLOC,_function_(get_location_port1,"get_location_port1"),
    _function_(get_location_port1_,"get_location_port1_"));
    
    (Core._FILE_star = ClaireClass::make("FILE*",Kernel._cl_import,Core.it));
    
    ;
    { (Core._popen_device = ClaireClass::make("popen_device",Core._device,Core.it));
      CL_ADD_SLOT(Core._popen_device,Core_popen_device,Core.child_comm,child_comm,Core._FILE_star,CNULL);
      CL_ADD_SLOT(Core._popen_device,Core_popen_device,Core.exitcode,exitcode,Kernel._integer,((OID)0));
      }
    
    Core.eof_port_ask->addMethod(list::domain(1,Core._popen_device),Kernel._boolean,
    	0,_function_(eof_port_ask_popen_device1_Core,"eof_port?_popen_device1_Core"));
    
    Core.close_port->addMethod(list::domain(1,Core._popen_device),Kernel._void,
    	0,_function_(close_port_popen_device1_Core,"close_port_popen_device1_Core"));
    
    Core.read_port->addMethod(list::domain(3,Core._popen_device,Core._char_star,Kernel._integer),Kernel._integer,
    	0,_function_(read_port_popen_device1_Core,"read_port_popen_device1_Core"));
    
    Core.flush_port->addMethod(list::domain(1,Core._popen_device),Kernel._void,
    	0,_function_(flush_port_popen_device1_Core,"flush_port_popen_device1_Core"));
    
    Core.write_port->addMethod(list::domain(3,Core._popen_device,Core._char_star,Kernel._integer),Kernel._integer,
    	0,_function_(write_port_popen_device1_Core,"write_port_popen_device1_Core"));
    
    Core.popen->addMethod(list::domain(2,Kernel._string,set::alloc(Kernel.emptySet,3,_string_(((char*)"r")),
      _string_(((char*)"w")),
      _string_(((char*)"rw")))),Core._popen_device,
    	NEW_ALLOC+SLOT_UPDATE,_function_(popen_string1,"popen_string1"));
    
    Core.bqexpand->addMethod(list::domain(1,Kernel._string),Kernel._string,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(bqexpand_string1,"bqexpand_string1"));
    
    { (Core.option_respond = property::make("option_respond",3,claire.it,Kernel._any,0));
      _void_(Core.option_respond->open = 3);
      ;}
    
    { (Core.option_parsed = property::make("option_parsed",3,claire.it,Kernel._any,0));
      _void_(Core.option_parsed->open = 3);
      ;}
    
    { (Core.option_begin_parse = property::make("option_begin_parse",3,claire.it,Kernel._any,0));
      _void_(Core.option_begin_parse->open = 3);
      ;}
    
    { (Core.option_usage = property::make("option_usage",3,claire.it,Kernel._any,0));
      _void_(Core.option_usage->open = 3);
      ;}
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,2,_string_(((char*)"-h")),_string_(((char*)"-help")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string1_Core,"option_usage_string1_Core"),
    _function_(option_usage_string1_Core_,"option_usage_string1_Core_"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,2,_string_(((char*)"-auto")),_string_(((char*)"-s")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string3_Core,"option_usage_string3_Core"),
    _function_(option_usage_string3_Core_,"option_usage_string3_Core_"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-v")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string4_Core,"option_usage_string4_Core"),
    _function_(option_usage_string4_Core_,"option_usage_string4_Core_"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-q")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string5_Core,"option_usage_string5_Core"),
    _function_(option_usage_string5_Core_,"option_usage_string5_Core_"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,2,_string_(((char*)"-qonerror")),_string_(((char*)"-errassegv")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string6_Core,"option_usage_string6_Core"),
    _function_(option_usage_string6_Core_,"option_usage_string6_Core_"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-noel")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string8_Core,"option_usage_string8_Core"),
    _function_(option_usage_string8_Core_,"option_usage_string8_Core_"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,2,_string_(((char*)"-color")),_string_(((char*)"-nocolor")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string9_Core,"option_usage_string9_Core"),
    _function_(option_usage_string9_Core_,"option_usage_string9_Core_"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-trace")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string10_Core,"option_usage_string10_Core"),
    _function_(option_usage_string10_Core_,"option_usage_string10_Core_"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-sample")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string11_Core,"option_usage_string11_Core"),
    _function_(option_usage_string11_Core_,"option_usage_string11_Core_"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-chdir")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string12_Core,"option_usage_string12_Core"),
    _function_(option_usage_string12_Core_,"option_usage_string12_Core_"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-options")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string32_Core,"option_usage_string32_Core"),
    _function_(option_usage_string32_Core_,"option_usage_string32_Core_"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core.CMD_SEPS = (global_variable *) Core._global_variable->instantiate("CMD_SEPS",Core.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(set::alloc(Kernel.emptySet,8,_string_(((char*)"[")),
        _string_(((char*)"{")),
        _string_(((char*)"}")),
        _string_(((char*)"|")),
        _string_(((char*)"-")),
        _string_(((char*)"]")),
        _string_(((char*)"<")),
        _string_(((char*)" ")))));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Core.VAR_END = (global_variable *) Core._global_variable->instantiate("VAR_END",Core.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(set::alloc(Kernel.emptySet,2,_string_(((char*)">")),_string_(((char*)":")))));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Core.OPT_END = (global_variable *) Core._global_variable->instantiate("OPT_END",Core.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(set::alloc(Kernel.emptySet,5,_string_(((char*)" ")),
        _string_(((char*)"]")),
        _string_(((char*)"}")),
        _string_(((char*)"|")),
        _string_(((char*)"<")))));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Core.print_var->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	0,_function_(print_var_string1,"print_var_string1"));
    
    Core.print_option->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE,_function_(print_option_string1,"print_option_string1"));
    
    Core.print_module->addMethod(list::domain(1,Kernel._module),Kernel._void,
    	NEW_ALLOC,_function_(print_module_module1,"print_module_module1"));
    
    Core.parse_var->addMethod(list::domain(4,Kernel._port,
      GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string)),
      GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string)),
      GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._string,
    	NEW_ALLOC,_function_(parse_var_port1,"parse_var_port1"));
    
    Core.parse_option->addMethod(list::domain(4,Kernel._port,
      GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string)),
      GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string)),
      GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(parse_option_port1,"parse_option_port1"));
    
    Core.print_back_option_usage->addMethod(list::domain(1,Kernel._string),Kernel._list,
    	NEW_ALLOC+SLOT_UPDATE,_function_(print_back_option_usage_string1,"print_back_option_usage_string1"));
    
    Core.print_back_option_usage->addMethod(list::domain(1,Kernel._port),Kernel._list,
    	NEW_ALLOC+SLOT_UPDATE,_function_(print_back_option_usage_port1,"print_back_option_usage_port1"));
    
    Core.print_back_option_help->addMethod(list::domain(2,Kernel._string,Kernel._list),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE,_function_(print_back_option_help_string1,"print_back_option_help_string1"));
    
    Core.print_back_option_help->addMethod(list::domain(2,Kernel._port,Kernel._list),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE,_function_(print_back_option_help_port1,"print_back_option_help_port1"));
    
    Core.find_option_usage->addMethod(list::domain(1,Kernel._integer),U_type(Kernel._method,set::alloc(Kernel.emptySet,1,CNULL)),
    	0,_function_(find_option_usage_integer1,"find_option_usage_integer1"));
    
    Core.find_option_usage->addMethod(list::domain(1,Kernel._string),U_type(Kernel._method,GC_OBJECT(set,set::alloc(Kernel.emptySet,1,CNULL))),
    	NEW_ALLOC,_function_(find_option_usage_string1,"find_option_usage_string1"));
    
    Core.print_option_usage->addMethod(list::domain(2,Kernel._method,Kernel._module),Kernel._void,
    	NEW_ALLOC,_function_(print_option_usage_method1,"print_option_usage_method1"));
    
    Core.print_option_usage->addMethod(list::domain(1,Kernel._method),Kernel._void,
    	NEW_ALLOC,_function_(print_option_usage_method2,"print_option_usage_method2"));
    
    Core.print_option_usage->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(print_option_usage_string1,"print_option_usage_string1"));
    
    Core.print_option_usage->addMethod(list::domain(1,Kernel._module),Kernel._void,
    	NEW_ALLOC,_function_(print_option_usage_module1,"print_option_usage_module1"));
    
    Core.print_option_usage->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC,_function_(print_option_usage_void1,"print_option_usage_void1"));
    
    Core.print_option_index->addMethod(list::domain(2,Kernel._method,Kernel._integer),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(print_option_index_method1,"print_option_index_method1"));
    
    Core.print_option_index->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(print_option_index_void1,"print_option_index_void1"));
    
    Core.apply_option_begin_parse->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC,_function_(apply_option_begin_parse_void1,"apply_option_begin_parse_void1"));
    
    Core.apply_option_parsed->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC,_function_(apply_option_parsed_void1,"apply_option_parsed_void1"));
    
    (Core._invalid_option_argument = ClaireClass::make("invalid_option_argument",Kernel._exception,claire.it));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,2,_string_(((char*)"-h")),_string_(((char*)"-help"))),Kernel._list),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(option_respond_string1_Core,"option_respond_string1_Core"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-s"))),Kernel._list),Kernel._void,
    	0,_function_(option_respond_string2_Core,"option_respond_string2_Core"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core._Zqonerror = (global_variable *) Core._global_variable->instantiate("%qonerror",Core.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.cfalse);
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Core._Zerrassegv = (global_variable *) Core._global_variable->instantiate("%errassegv",Core.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.cfalse);
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,7,_string_(((char*)"-color")),
      _string_(((char*)"-nocolor")),
      _string_(((char*)"-logo")),
      _string_(((char*)"-auto")),
      _string_(((char*)"-noel")),
      _string_(((char*)"-alt")),
      _string_(((char*)"-gcstress"))),Kernel._list),Kernel._void,
    	0,_function_(option_respond_string48_Core,"option_respond_string48_Core"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-qonerror"))),Kernel._list),Kernel._void,
    	0,_function_(option_respond_string4_Core,"option_respond_string4_Core"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-errassegv"))),Kernel._list),Kernel._void,
    	0,_function_(option_respond_string5_Core,"option_respond_string5_Core"));
    
    Core.number_ask->addMethod(list::domain(1,Kernel._string),Kernel._boolean,
    	NEW_ALLOC,_function_(number_ask_string1,"number?_string1"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-q"))),Kernel._list),Kernel._void,
    	NEW_ALLOC,_function_(option_respond_string7_Core,"option_respond_string7_Core"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-v"))),Kernel._list),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(option_respond_string8_Core,"option_respond_string8_Core"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-trace"))),Kernel._list),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(option_respond_string9_Core,"option_respond_string9_Core"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-sample"))),Kernel._list),Kernel._void,
    	NEW_ALLOC,_function_(option_respond_string41_Core,"option_respond_string41_Core"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-chdir"))),GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC,_function_(option_respond_string40_Core,"option_respond_string40_Core"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core.DYNLOADS = (global_variable *) Core._global_variable->instantiate("DYNLOADS",Core.it));
      _void_(_CL_obj->range = nth_class1(Kernel._list,Kernel._string));
      _void_(_CL_obj->value = _oid_(list::empty(Kernel._string)));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-dynload"))),GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(option_respond_string49_Core,"option_respond_string49_Core"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-dynload")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string33_Core,"option_usage_string33_Core"),
    _function_(option_usage_string33_Core_,"option_usage_string33_Core_"));
    
    { (Core.toplevel = property::make("toplevel",3,Core.it,Kernel._any,0));
      _void_(Core.toplevel->open = 3);
      ;}
    
    Core.print_cmline_exception->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(print_cmline_exception_void1,"print_cmline_exception_void1"));
    
    Core.parse_command_line->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(parse_command_line_void1,"parse_command_line_void1"));
    
    { (Core.on_option_error = property::make("on_option_error",3,claire.it,Kernel._any,0));
      _void_(Core.on_option_error->open = 3);
      ;}
    
    Core.apply_command_line->addMethod(list::domain(2,GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string)),Kernel._boolean),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(apply_command_line_list1,"apply_command_line_list1"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-source-editor"))),Kernel._list),Kernel._void,
    	NEW_ALLOC,_function_(option_respond_string45_Core,"option_respond_string45_Core"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-source-edit"))),Kernel._list),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(option_respond_string46_Core,"option_respond_string46_Core"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Core.OPTION_LINE = (global_variable *) Core._global_variable->instantiate("OPTION_LINE",Core.it));
      _void_(_CL_obj->range = Kernel._integer);
      _void_(_CL_obj->value = ((OID)0));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Core.OPTION_PATH = (global_variable *) Core._global_variable->instantiate("OPTION_PATH",Core.it));
      _void_(_CL_obj->range = Kernel._string);
      _void_(_CL_obj->value = _string_(((char*)"")));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Core.read_cmd_string->addMethod(list::domain(2,Kernel._port,Kernel._string),Kernel._string,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(read_cmd_string_port1,"read_cmd_string_port1"));
    
    Core.shell_expand->addMethod(list::domain(1,Kernel._string),Kernel._string,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(shell_expand_string1,"shell_expand_string1"));
    
    Core.read_option_line->addMethod(list::domain(2,Kernel._port,GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(read_option_line_port1,"read_option_line_port1"));
    
    { (Core._option_instruction = ClaireClass::make("option_instruction",Core._ephemeral_object,Core.it));
      CL_ADD_SLOT(Core._option_instruction,Core_option_instruction,Core.filename,filename,Kernel._string,CNULL);
      CL_ADD_SLOT(Core._option_instruction,Core_option_instruction,Core.line,line,Kernel._integer,CNULL);
      }
    
    { (Core._option_apply = ClaireClass::make("option_apply",Core._option_instruction,Core.it));
      CL_ADD_SLOT(Core._option_apply,Core_option_apply,Core.args,args,nth_class1(Kernel._list,Kernel._string),CNULL);
      }
    
    { (Core._option_do = ClaireClass::make("option_do",Core._option_instruction,Core.it));
      CL_ADD_SLOT(Core._option_do,Core_option_do,Core.args,args,nth_class1(Kernel._list,Core._option_instruction),CNULL);
      }
    
    { (Core._option_if = ClaireClass::make("option_if",Core._option_do,Core.it));
      CL_ADD_SLOT(Core._option_if,Core_option_if,Core.test,test,Kernel._string,CNULL);
      CL_ADD_SLOT(Core._option_if,Core_option_if,Core.other,other,Core._option_instruction,CNULL);
      }
    
    { (Core._option_while = ClaireClass::make("option_while",Core._option_do,Core.it));
      CL_ADD_SLOT(Core._option_while,Core_option_while,Core.test,test,Kernel._string,CNULL);
      }
    
    { (Core._option_for = ClaireClass::make("option_for",Core._option_do,Core.it));
      CL_ADD_SLOT(Core._option_for,Core_option_for,Core.forvar,forvar,Kernel._string,CNULL);
      CL_ADD_SLOT(Core._option_for,Core_option_for,Core.forsetarg,forsetarg,Kernel._string,CNULL);
      CL_ADD_SLOT(Core._option_for,Core_option_for,Core.such,such,Kernel._string,_string_(((char*)"")));
      }
    
    Kernel.close->addMethod(list::domain(1,Core._option_instruction),Core._option_instruction,
    	SLOT_UPDATE+RETURN_ARG,_function_(close_option_instruction1,"close_option_instruction1"));
    
    Core.read_option_file->addMethod(list::domain(2,Kernel._port,Core._option_do),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(read_option_file_port1,"read_option_file_port1"));
    
    Core.read_option_if->addMethod(list::domain(2,Kernel._port,GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Core._option_if,
    	NEW_ALLOC+SLOT_UPDATE,_function_(read_option_if_port1,"read_option_if_port1"));
    
    Core.read_option_while->addMethod(list::domain(2,Kernel._port,GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Core._option_while,
    	NEW_ALLOC+SLOT_UPDATE,_function_(read_option_while_port1,"read_option_while_port1"));
    
    Core.read_option_for->addMethod(list::domain(2,Kernel._port,GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Core._option_for,
    	NEW_ALLOC+SLOT_UPDATE,_function_(read_option_for_port1,"read_option_for_port1"));
    
    Core.eval_options->addMethod(list::domain(1,Core._option_apply),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(eval_options_option_apply1,"eval_options_option_apply1"));
    
    { (Core.option_push = property::make("option_push",3,claire.it,Kernel._any,0));
      _void_(Core.option_push->open = 3);
      ;}
    
    { (Core.option_test = property::make("option_test",3,claire.it,Kernel._any,0));
      _void_(Core.option_test->open = 3);
      ;}
    
    { (Core.option_pop = property::make("option_pop",3,claire.it,Kernel._any,0));
      _void_(Core.option_pop->open = 3);
      ;}
    
    { (Core.option_continue_ask = property::make("option_continue?",3,claire.it,Kernel._any,0));
      _void_(Core.option_continue_ask->open = 3);
      ;}
    
    { (Core.option_start_loop = property::make("option_start_loop",3,claire.it,Kernel._any,0));
      _void_(Core.option_start_loop->open = 3);
      ;}
    
    Core.eval_options->addMethod(list::domain(1,Core._option_do),Kernel._void,
    	NEW_ALLOC,_function_(eval_options_option_do1,"eval_options_option_do1"));
    
    Core.eval_options->addMethod(list::domain(1,Core._option_if),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(eval_options_option_if1,"eval_options_option_if1"));
    
    Core.eval_options->addMethod(list::domain(1,Core._option_while),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(eval_options_option_while1,"eval_options_option_while1"));
    
    Core.eval_options->addMethod(list::domain(1,Core._option_for),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(eval_options_option_for1,"eval_options_option_for1"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-options"))),Kernel._list),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(option_respond_string47_Core,"option_respond_string47_Core"));
    
    Core.open_link->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(open_link_string1,"open_link_string1"));
    
    Core.edit_link->addMethod(list::domain(1,Kernel._bag),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(edit_link_bag1,"edit_link_bag1"));
    
    Core.edit_link->addMethod(list::domain(3,Kernel._string,Kernel._integer,Kernel._string),Kernel._void,
    	NEW_ALLOC,_function_(edit_link_string1,"edit_link_string1"));
    GC_UNBIND;

    }
  
  