/***** CLAIRE Compilation of file ./meta/method.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:31 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>

//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| method.cl                                                   |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file  object.cl: about()              |
//+-------------------------------------------------------------+
// ---------------------------------------------------------------------
// This file contains the reflective description of the most primitive
// CLAIRE kernel: the embryo of the class hierarchy and a set of methods
// to read/write objects and to evaluate messages.
// ---------------------------------------------------------------------
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
// the eval_message is a method that tells how to handle the message.
// it used to be distributed in CLAIRE (so that it was extensible) and each
// definition was called the behavior of a kind of restriction
// int? tells us if this is an interpreted message
// The c++ function for: eval_message(self:property,r:object,start:integer,int?:boolean) [NEW_ALLOC+SLOT_UPDATE+SAFE_GC]
OID  eval_message_property(property *self,ClaireObject *r,int start,ClaireBoolean *int_ask)
{ if (ClEnv->index + 100 >= ClAlloc->maxStack) error_execution_stack_full();
  { OID Result = 0;
    if (r->isa == Kernel._method)
     { if (ClEnv->debug_I != ((CL_INT)-1))
       Result = execute_method(((method *) r),start,int_ask);
      else { method * m = ((method *) r);
          if (((m->formula == (NULL)) ? CTRUE : CFALSE) != CTRUE)
           { CL_INT  retour = ClEnv->base;
            (ClEnv->base= ((OID)start));
            stack_add(m->formula->dimension);
            { CL_INT  i = ((CL_INT)start+(CL_INT)m->domain->length);
              CL_INT  g0000 = ((CL_INT)((CL_INT)start+(CL_INT)m->formula->dimension)-(CL_INT)1);
              { CL_INT loop_handle = ClEnv->cHandle;
                while (((CL_INT)i <= (CL_INT)g0000))
                { (ClEnv->stack[((OID)i)]=_oid_(Core.undefined_debug));
                  ++i;
                  POP_SIGNAL;}
                }
              }
            { OID  val = eval_any(m->formula->body);
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


// The c++ function for: noeval_message(self:property,start:integer) [NEW_ALLOC+SLOT_UPDATE]
OID  noeval_message_property2(property *self,int start)
{ GC_BIND;
  { OID Result = 0;
    { list * l = GC_OBJECT(list,get_args_integer(start));
      if (ClEnv->debug_I != ((CL_INT)-1))
       push_debug_property(self,((CL_INT)ClEnv->index-(CL_INT)start),start);
      close_exception(((selector_error *) (*Core._selector_error)(_oid_(self),
        _oid_(l))));
      Result = Core.nil->value;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// a generic method : same as previously but (1) can be called by other methods
// and (2) takes care of the debugging piece, which implies a slower run (GC)
// The c++ function for: execute(self:method,start:integer,int?:boolean) [NEW_ALLOC+SLOT_UPDATE]
OID  execute_method(method *self,int start,ClaireBoolean *int_ask)
{ GC_BIND;
  { OID Result = 0;
    { OID  val = CNULL;
      CL_INT  n = self->domain->length;
      if (((self->formula == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       { CL_INT  retour = ClEnv->base;
        ClaireBoolean * st_ask = ((ClEnv->debug_I != ((CL_INT)-1)) ? (((int_ask == CTRUE) || 
            (self->module_I->status != 4)) ? CTRUE: CFALSE): CFALSE);
        (ClEnv->base= ((OID)start));
        stack_add(self->formula->dimension);
        { CL_INT  i = ((CL_INT)start+(CL_INT)self->domain->length);
          CL_INT  g0001 = ((CL_INT)((CL_INT)start+(CL_INT)self->formula->dimension)-(CL_INT)1);
          { CL_INT loop_handle = ClEnv->cHandle;
            while (((CL_INT)i <= (CL_INT)g0001))
            { (ClEnv->stack[((OID)i)]=_oid_(Core.undefined_debug));
              ++i;
              POP_SIGNAL;}
            }
          }
        if (st_ask == CTRUE)
         push_debug_property(self->selector,n,start);
        val= eval_any(GC_OID(self->formula->body));
        if (st_ask == CTRUE)
         pop_debug_property(self->selector,0,val);
        (ClEnv->base= ((OID)retour));
        (ClEnv->index= ((OID)start));
        if ((ClEnv->debug_I != ((CL_INT)-1)) && 
            (belong_to(val,_oid_(self->range)) != CTRUE))
         close_exception(((range_error *) (*Core._range_error)(_oid_(self),
          val,
          _oid_(self->range))));
        Result = val;
        }
      else { ClaireBoolean * st_ask = ((ClEnv->debug_I != ((CL_INT)-1)) ? (((int_ask == CTRUE) || 
              ((self->module_I->status != 3) && 
                  (boolean_I_any(self->compiled_variables) != CTRUE))) ? ((self->selector != Core.debug) ? CTRUE: CFALSE): CFALSE): CFALSE);
          CL_INT  i = ClEnv->index;
          if (st_ask == CTRUE)
           push_debug_property(self->selector,n,start);
          val= stack_apply_function(self->evaluate,self->srange,start,i);
          if (st_ask == CTRUE)
           pop_debug_property(self->selector,0,val);
          if ((ClEnv->debug_I != ((CL_INT)-1)) && 
              (belong_to(val,_oid_(self->range)) != CTRUE))
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
OID  eval_any(OID self)
{ POP_SIGNAL; return (OPT_EVAL(self));}


// this is the standard evaluation
// The c++ function for: self_eval(self:object) [RETURN_ARG]
OID  self_eval_ClaireObject(ClaireObject *self)
{ POP_SIGNAL; return (_oid_(self));}


// evaluation for a list or enumeration
// reads an inline definition for a method
// The c++ function for: inlineok?(self:method,s:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT]
method * inlineok_ask_method(method *self,char *s)
{ GC_BIND;
  { ClaireHandler c_handle = ClaireHandler();
    if ERROR_IN 
    { { property * p = Core.read;
        OID  l = GC_OID((*Core.call)(_oid_(p),
          _string_(s)));
        (self->inline_ask = CTRUE);
        update_property(Kernel.formula,
          self,
          8,
          Kernel._object,
          l);
        }
      ERROR_FREE;}
    else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
    { c_handle.catchIt();if (should_trace_ask_module1(Core.it,0) == CTRUE)
       mtformat_module1(Core.it,"`RED---- WARNING: inline definition of ~S is wrong\n",0,list::alloc(1,_oid_(self)));
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
// The c++ function for: get(s:slot,x:object) [0]
OID  get_slot(slot *s,ClaireObject *x)
{ POP_SIGNAL; return (slot_get_object(x,s->index,s->srange));}


// The c++ function for: put(s:slot,x:object,y:any) [SLOT_UPDATE+RETURN_ARG]
OID  put_slot(slot *s,ClaireObject *x,OID y)
{ POP_SIGNAL; return (store_object(x,
    s->index,
    s->srange,
    y,
    s->selector->store_ask));}


// reading a value from a property (unknown is allowed)
// The c++ function for: get(self:property,x:object) [NEW_ALLOC]
OID  get_property(property *self,ClaireObject *x)
{ GC_BIND;
  { OID Result = 0;
    { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
      if (Kernel._slot == s->isa)
       Result = slot_get_object(x,CLREAD(slot,s,index),CLREAD(slot,s,srange));
      else Result = CNULL;
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// a more general value that is useful for types
// The c++ function for: funcall(self:property,x:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  funcall_property(property *self,OID x)
{ GC_BIND;
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
// The c++ function for: read(self:property,x:object) [NEW_ALLOC]
OID  read_property(property *self,ClaireObject *x)
{ GC_BIND;
  { OID Result = 0;
    { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
      if (Kernel._slot == s->isa)
       { OID  z = slot_get_object(x,CLREAD(slot,s,index),CLREAD(slot,s,srange));
        if ((z != CNULL) || 
            (belong_to(z,_oid_(CLREAD(restriction,s,range))) == CTRUE))
         Result = z;
        else { OID  V_CL0002;close_exception(((read_slot_error *) (*Core._read_slot_error)(_oid_(x),
              _oid_(self))));
            
            Result=_void_(V_CL0002);}
          }
      else { OID  V_CL0003;close_exception(((read_slot_error *) (*Core._read_slot_error)(_oid_(x),
            _oid_(self))));
          
          Result=_void_(V_CL0003);}
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// verifying
// The c++ function for: hold?(self:property,x:object,y:any) [NEW_ALLOC]
ClaireBoolean * hold_ask_property(property *self,ClaireObject *x,OID y)
{ GC_BIND;
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
// The c++ function for: write(self:property,x:object,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  write_property(property *self,ClaireObject *x,OID y)
{ GC_BIND;
  { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
    if (Kernel._slot == s->isa)
     { if (belong_to(y,_oid_(CLREAD(restriction,s,range))) != CTRUE)
       range_is_wrong_slot(((slot *) s),y);
      else if (((CL_INT)self->open < 1) && 
          (slot_get_object(x,CLREAD(slot,s,index),CLREAD(slot,s,srange)) != CNULL))
       close_exception(((general_error *) (*Core._general_error)(_string_("[132] Cannot change ~S(~S)"),
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
OID  range_is_wrong_slot(slot *self,OID y)
{ { OID Result = 0;
    { OID  V_CL0004;close_exception(((range_error *) (*Core._range_error)(_oid_(self),
        y,
        _oid_(self->range))));
      
      Result=_void_(V_CL0004);}
    POP_SIGNAL; return (Result);}
  }


// to remove
// The c++ function for: put(p:property,x:object,n:integer,s:class,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  put_property1(property *p,ClaireObject *x,int n,ClaireClass *s,OID y)
{ if (should_trace_ask_module1(Core.it,0) == CTRUE)
   mtformat_module1(Core.it,"are you still using this dead thing (put instead of update) ??? !! \n",0,list::empty());
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
void  update_property(property *p,ClaireObject *x,int n,ClaireClass *s,OID y)
{ GC_BIND;
  { OID  old = slot_get_object(x,n,s);
    if (p->multivalued_ask != CFALSE)
     { if ((CL_INT)(*Kernel.length)(old) > 0)
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
void  update_plus_relation(ClaireRelation *self,OID x,OID y)
{ GC_BIND;
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
        else close_exception(((general_error *) (*Core._general_error)(_string_("[133] Inversion of ~S(~S,~S) impossible"),
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
void  update_dash_relation(ClaireRelation *r,OID x,OID y)
{ GC_BIND;
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
void  add_I_property(property *self,ClaireObject *x,int n,OID y)
{ if (((self->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE)
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
ClaireBoolean * add_value_property(property *self,ClaireObject *x,int n,bag *l,OID y)
{ GC_BIND;
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
// The c++ function for: add(self:property,x:object,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  add_property(property *self,ClaireObject *x,OID y)
{ GC_BIND;
  { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
    if (boolean_I_any(_oid_(s)) != CTRUE)
     close_exception(((selector_error *) (*Core._selector_error)(_oid_(self),
      _oid_(list::alloc(1,_oid_(x))))));
    else if (multi_ask_any(_oid_(self)) != CTRUE)
     close_exception(((general_error *) (*Core._general_error)(_string_("[134] Cannot apply add to ~S"),
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
// The c++ function for: known?(self:property,x:object) [NEW_ALLOC]
ClaireBoolean * known_ask_property(property *self,ClaireObject *x)
{ GC_BIND;
  { ClaireBoolean *Result ;
    { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
      Result = ((Kernel._slot == s->isa) ?
        _I_equal_any(slot_get_object(x,CLREAD(slot,s,index),CLREAD(slot,s,srange)),CNULL) :
        CFALSE );
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: unknown?(self:property,x:object) [NEW_ALLOC]
ClaireBoolean * unknown_ask_property(property *self,ClaireObject *x)
{ GC_BIND;
  { ClaireBoolean *Result ;
    { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
      Result = ((Kernel._slot == s->isa) ?
        equal(slot_get_object(x,CLREAD(slot,s,index),CLREAD(slot,s,srange)),CNULL) :
        CTRUE );
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// delete takes care of the inverse also
// The c++ function for: delete(self:property,x:object,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  delete_property(property *self,ClaireObject *x,OID y)
{ GC_BIND;
  { OID Result = 0;
    { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
      if (boolean_I_any(_oid_(s)) != CTRUE)
       { OID  V_CL0005;close_exception(((selector_error *) (*Core._selector_error)(_oid_(self),
          _oid_(list::alloc(1,_oid_(x))))));
        
        Result=_void_(V_CL0005);}
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
// The c++ function for: erase(self:property,x:object) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  erase_property(property *self,ClaireObject *x)
{ GC_BIND;
  { OID Result = 0;
    { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
      if (boolean_I_any(_oid_(s)) != CTRUE)
       { OID  V_CL0006;close_exception(((selector_error *) (*Core._selector_error)(_oid_(self),
          _oid_(list::alloc(1,_oid_(x))))));
        
        Result=_void_(V_CL0006);}
      else { OID  y = slot_get_object(x,CLREAD(slot,s,index),OBJECT(ClaireClass,(*Kernel.srange)(_oid_(s))));
          if (self->multivalued_ask != CFALSE)
           { { ClaireRelation * r = self->inverse;
              if (r == (NULL))
               ;else { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(y1);
                  bag *y1_support;
                  y1_support = GC_OBJECT(bag,enumerate_any(y));
                  for (START(y1_support); NEXT(y1);)
                  update_dash_relation(r,y1,_oid_(x));
                  }
                }
            { OID  l;
              { { OID  g0007UU;
                  { if (self->store_ask == CTRUE)
                     g0007UU = (*Kernel.copy)(y);
                    else g0007UU = y;
                      GC_OID(g0007UU);}
                  l = (*Kernel.shrink)(g0007UU,
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
void  set_range_property(property *p,ClaireClass *c,ClaireType *r)
{ { slot * s = ((slot *) _at_property1(p,c));
    (s->range = r);
    (s->srange = sort_I_type(r));
    }
  POP_SIGNAL;}


// no longer needed because changing the range is not changing the prototype ?
// we should rather generate an error if the condition for dealing with
// defaults changes (TODO)
//        if (s.srange != any & s.srange != integer)
//           c.prototype[s.index] := 0))
// this method allows to bypass the storage mechanism - to be optimized ..
// The c++ function for: put_store(self:property,x:object,y:any,b:boolean) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  put_store_property2(property *self,ClaireObject *x,OID y,ClaireBoolean *b)
{ GC_BIND;
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
ClaireBoolean * multi_ask_any(OID x)
{ { ClaireBoolean *Result ;
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
void  fastcall_relation2(ClaireRelation *r,OID x,OID y)
{ GC_BIND;
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
void  insert_definition_property(property *p,restriction *r)
{ (p->definition = initialize_restriction1(r,class_I_type(OBJECT(ClaireType,(*(r->domain))[1])),p->definition));
  POP_SIGNAL;}


// insert a restriction with class-domain d into a property p
// The c++ function for: initialize(x:restriction,d:class,l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
list * initialize_restriction1(restriction *x,ClaireClass *d,list *l)
{ { list *Result ;
    { property * p = x->selector;
      CL_INT  ix = p->dispatcher;
      if ((p->restrictions->length == 5) && 
          (uniform_property(p) == CTRUE))
       { { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(r);
          for (START(p->restrictions); NEXT(r);)
          hashinsert_restriction(OBJECT(restriction,r));
          }
        (p->dictionary = CTRUE);
        }
      if (p->dictionary == CTRUE)
       { if (uniform_restriction(x) == CTRUE)
         { if (ClEnv->verbose == 4)
           { if (should_trace_ask_module1(Core.it,0) == CTRUE)
             mtformat_module1(Core.it,"--- hashinsert ~S \n",0,list::alloc(1,_oid_(x)));
            else ;}
          hashinsert_restriction(x);
          }
        else (p->dictionary = CFALSE);
          }
      if (((CL_INT)ix > 0) && 
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
            { ClaireBoolean * g0008I;
              { OID  g0009UU;
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(y);
                  g0009UU= Kernel.cfalse;
                  for (START(p->restrictions); NEXT(y);)
                  if (y != _oid_(x))
                   { { ClaireBoolean * g0010I;
                      { OID  g0011UU;
                        { ClaireClass * c3 = domain_I_restriction(OBJECT(restriction,y));
                          g0011UU = _oid_(not_any(_oid_(((INHERIT(OBJECT(ClaireClass,c2),c3)) ? ((INHERIT(c3,c)) ? CTRUE: CFALSE): CFALSE))));
                          }
                        g0010I = not_any(g0011UU);
                        }
                      
                      if (g0010I == CTRUE) { g0009UU = Kernel.ctrue;
                          ClEnv->cHandle = loop_handle;break;}
                        }
                    }
                  }
                g0008I = not_any(g0009UU);
                }
              
              if (g0008I == CTRUE) ((*(((list *) OBJECT(ClaireClass,c2)->dispatcher)))[ix]=_oid_(CLREAD(method,x,evaluate)));
                }
            }
          }
        else close_exception(((general_error *) (*Core._general_error)(_string_("Cannot create a non-uniform restriction ~S of interface ~S"),
            _oid_(list::alloc(2,_oid_(x),_oid_(p))))));
          }
      Result = initialize_restriction2(x,l);
      }
    POP_SIGNAL; return (Result);}
  }


// only uniform properties can use the dictionary representation
// The c++ function for: uniform(x:restriction) [NEW_ALLOC]
ClaireBoolean * uniform_restriction(restriction *x)
{ { ClaireBoolean *Result ;
    { list * l = x->domain;
      CL_INT  n = l->length;
      { OID  g0013UU;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(r);
          g0013UU= Kernel.cfalse;
          for (START(x->selector->restrictions); NEXT(r);)
          { ClaireBoolean * g0014I;
            { OID  g0015UU;
              { list * l2 = OBJECT(restriction,r)->domain;
                { ClaireBoolean * V_CL0016;{ ClaireBoolean *v_and;
                    { v_and = inherit_ask_class(OWNER((*(l))[1]),Kernel._class);
                      if (v_and == CFALSE) V_CL0016 =CFALSE; 
                      else { v_and = ((l2->length == n) ? CTRUE : CFALSE);
                        if (v_and == CFALSE) V_CL0016 =CFALSE; 
                        else { { OID  g0017UU;
                            { CL_INT  i = 2;
                              CL_INT  g0012 = n;
                              { CL_INT loop_handle = ClEnv->cHandle;
                                g0017UU= _oid_(CFALSE);
                                while (((CL_INT)i <= (CL_INT)g0012))
                                { if (((equal((*(l))[i],(*(l2))[i]) == CTRUE) ? CTRUE : (((OWNER((*(l))[i]) != Kernel._class) && 
                                      ((OWNER((*(l))[i]) == OWNER((*(l2))[i])) && 
                                        (_equaltype_ask_any(OBJECT(ClaireType,(*(l))[i]),OBJECT(ClaireType,(*(l2))[i])) == CTRUE))) ? CTRUE : CFALSE)) != CTRUE)
                                   { g0017UU = Kernel.ctrue;
                                    ClEnv->cHandle = loop_handle;break;}
                                  ++i;
                                  POP_SIGNAL;}
                                }
                              }
                            v_and = not_any(g0017UU);
                            }
                          if (v_and == CFALSE) V_CL0016 =CFALSE; 
                          else V_CL0016 = CTRUE;}
                        }
                      }
                    }
                  
                  g0015UU=_oid_(V_CL0016);}
                }
              g0014I = not_any(g0015UU);
              }
            
            if (g0014I == CTRUE) { g0013UU = Kernel.ctrue;
                ClEnv->cHandle = loop_handle;break;}
              }
          }
        Result = not_any(g0013UU);
        }
      }
    POP_SIGNAL; return (Result);}
  }


// v3.3.36      
// v3.0.54 check that a uniform property only uses methods !
// The c++ function for: uniform(p:property) [NEW_ALLOC]
ClaireBoolean * uniform_property(property *p)
{ { ClaireBoolean *Result ;
    { ClaireBoolean *v_and;
      { { OID  g0018UU;
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(x);
            g0018UU= Kernel.cfalse;
            for (START(p->restrictions); NEXT(x);)
            if (equal(_oid_(Kernel._method),_oid_(OBJECT(ClaireObject,x)->isa)) != CTRUE)
             { g0018UU = Kernel.ctrue;
              ClEnv->cHandle = loop_handle;break;}
            }
          v_and = not_any(g0018UU);
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
list * initialize_restriction2(restriction *x,list *l)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { list *Result ;
    { list * l1 = Kernel.nil;
      { CL_INT  i = 1;
        CL_INT  g0019 = l->length;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)i <= (CL_INT)g0019))
          { GC_LOOP;
            { list * l2 = OBJECT(restriction,(*(l))[i])->domain;
              if (tmatch_ask_list(x->domain,l2) == CTRUE)
               { if (tmatch_ask_list(l2,x->domain) == CTRUE)
                 { ((*(l))[i]=_oid_(x));
                  GC__ANY(l1 = l, 1);
                  { ;ClEnv->cHandle = loop_handle; break;}
                  }
                else { GC__ANY(l1 = add_at_list(l,i,_oid_(x)), 1);
                    { ;ClEnv->cHandle = loop_handle; break;}
                    }
                  }
              else if ((tmatch_ask_list(l2,x->domain) != CTRUE) && 
                  (join_list(x->domain,l2) == CTRUE))
               { if (should_trace_ask_module1(Core.it,2) == CTRUE)
                 mtformat_module1(Core.it,"`BLUE---- Warning: ~S and ~S are conflicting\n",2,list::alloc(2,(*(l))[1],_oid_(x)));
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
OID  hashinsert_restriction(restriction *m)
{ { OID Result = 0;
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
OID  hashinsert_class(ClaireClass *c,method *x)
{ if (boolean_I_any(_oid_(c->dictionary)) != CTRUE)
   (c->dictionary = hashlist_integer(29));
  (c->dictionary = OBJECT(list,hashinsert_list(c->dictionary,x)));
  POP_SIGNAL; return (_oid_(c->dictionary));}


// v3.3.06: returns the new hash list when x is inserted (not necessarily the same list since l may grow)
// The c++ function for: hashinsert(l:list,x:method) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  hashinsert_list(list *l,method *x)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
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
              { Result = _oid_(l);
                ClEnv->cHandle = loop_handle;break;}
              }
            else if (i == m)
             { if ((CL_INT)((CL_INT)hashsize_list(l)*(CL_INT)3) > (CL_INT)((CL_INT)l->length*(CL_INT)2))
               { list * myl2;
                { { list * g0020 = l;
                    list * g0021 = GC_OBJECT(list,make_list_integer(((CL_INT)((*(g0020))[0])*(CL_INT)2),CNULL));
                    { CL_INT loop_handle = ClEnv->cHandle;
                      OID gc_local;
                      ITERATE(g0022);
                      for (START(g0020); NEXT(g0022);)
                      if (g0022 != CNULL)
                       hashinsert_list(g0021,OBJECT(method,g0022));
                      }
                    myl2 = g0021;
                    }
                  GC_OBJECT(list,myl2);}
                { Result = hashinsert_list(myl2,x);
                  ClEnv->cHandle = loop_handle;break;}
                }
              else i= 1;
                }
            else ++i;
              }
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: hashget(c:class,p:property) [RETURN_ARG]
ClaireObject * hashget_class(ClaireClass *c,property *p)
{ { ClaireObject *Result ;
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
               i= 1;
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
ClaireBoolean * join_list(list *x,list *y)
{ { ClaireBoolean *Result ;
    { CL_INT  n = x->length;
      { ClaireBoolean *v_and;
        { v_and = ((n == y->length) ? CTRUE : CFALSE);
          if (v_and == CFALSE) Result =CFALSE; 
          else { { OID  g0025UU;
              { CL_INT  i = 1;
                CL_INT  g0023 = n;
                { CL_INT loop_handle = ClEnv->cHandle;
                  g0025UU= _oid_(CFALSE);
                  while (((CL_INT)i <= (CL_INT)g0023))
                  { if (boolean_I_any(_oid_(join_class(class_I_type(OBJECT(ClaireType,(*(x))[i])),class_I_type(OBJECT(ClaireType,(*(y))[i]))))) != CTRUE)
                     { g0025UU = Kernel.ctrue;
                      ClEnv->cHandle = loop_handle;break;}
                    ++i;
                    POP_SIGNAL;}
                  }
                }
              v_and = not_any(g0025UU);
              }
            if (v_and == CFALSE) Result =CFALSE; 
            else { { OID  g0026UU;
                { CL_INT  i = 1;
                  CL_INT  g0024 = n;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    g0026UU= _oid_(CFALSE);
                    while (((CL_INT)i <= (CL_INT)g0024))
                    { if (boolean_I_any((*Core.glb)((*(x))[i],
                        (*(y))[i])) != CTRUE)
                       { g0026UU = Kernel.ctrue;
                        ClEnv->cHandle = loop_handle;break;}
                      ++i;
                      POP_SIGNAL;}
                    }
                  }
                v_and = not_any(g0026UU);
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
ClaireObject * _at_property1(property *self,ClaireClass *x)
{ GC_BIND;
  { ClaireObject *Result ;
    if (self->dictionary == CTRUE)
     Result = hashget_class(x,self);
    else { OID  rx;
        { { OID  r_some = CNULL;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(r);
              for (START(self->definition); NEXT(r);)
              if (INHERIT(x,class_I_type(OBJECT(ClaireType,(*(OBJECT(restriction,r)->domain))[1]))))
               { r_some= r;
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
ClaireObject * _at_property2(property *self,list *lt)
{ GC_BIND;
  { ClaireObject *Result ;
    { ClaireObject *V_CC ;
      { OID  rx;
        { { OID  r_some = CNULL;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(r);
              for (START(self->definition); NEXT(r);)
              if (tmatch_ask_list(lt,OBJECT(restriction,r)->domain) == CTRUE)
               { r_some= r;
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
ClaireBoolean * matching_ask_list(list *l,int n,int m)
{ { ClaireBoolean *Result ;
    { CL_INT  x = ((CL_INT)m-(CL_INT)n);
      CL_INT  z = l->length;
      if ((z == x) && 
          ((*(l))[x] != _oid_(Kernel._listargs)))
       { OID  g0029UU;
        { CL_INT  i = 1;
          CL_INT  g0027 = x;
          { CL_INT loop_handle = ClEnv->cHandle;
            g0029UU= _oid_(CFALSE);
            while (((CL_INT)i <= (CL_INT)g0027))
            { { CL_INT  y = ((CL_INT)((CL_INT)n-(CL_INT)1)+(CL_INT)i);
                OID  u = (*(l))[i];
                if ((OWNER(u) == Kernel._class) ? (inherit_ask_class(OWNER(ClEnv->stack[((OID)y)]),OBJECT(ClaireClass,u)) != CTRUE) : (vmatch_ask_any(u,ClEnv->stack[((OID)y)],n) != CTRUE))
                 { g0029UU = Kernel.ctrue;
                  ClEnv->cHandle = loop_handle;break;}
                }
              ++i;
              POP_SIGNAL;}
            }
          }
        Result = not_any(g0029UU);
        }
      else if ((last_list(l) == _oid_(Kernel._listargs)) && 
          ((CL_INT)((CL_INT)z-(CL_INT)1) <= (CL_INT)x))
       { OID  g0030UU;
        { CL_INT  i = 1;
          CL_INT  g0028 = z;
          { CL_INT loop_handle = ClEnv->cHandle;
            g0030UU= _oid_(CFALSE);
            while (((CL_INT)i <= (CL_INT)g0028))
            { { CL_INT  y = ((CL_INT)((CL_INT)n-(CL_INT)1)+(CL_INT)i);
                if ((*(l))[i] == _oid_(Kernel._listargs))
                 { (ClEnv->stack[((OID)y)]=_oid_(get_args_integer(y)));
                  (ClEnv->index= ((OID)((CL_INT)y+(CL_INT)1)));
                  { g0030UU = Kernel.cfalse;
                    ClEnv->cHandle = loop_handle;break;}
                  }
                else if (vmatch_ask_any((*(l))[i],ClEnv->stack[((OID)y)],n) != CTRUE)
                 { g0030UU = Kernel.ctrue;
                  ClEnv->cHandle = loop_handle;break;}
                }
              ++i;
              POP_SIGNAL;}
            }
          }
        Result = not_any(g0030UU);
        }
      else Result = CFALSE;
        }
    POP_SIGNAL; return (Result);}
  }


// type's pattern matching
// v3.0.65: use %type for Param
// The c++ function for: vmatch?(t:any,x:any,n:integer) [SAFE_GC]
ClaireBoolean * vmatch_ask_any(OID t,OID x,int n)
{ { ClaireBoolean *Result ;
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
        else { { OID  g0033UU;
            { CL_INT  i = 1;
              CL_INT  g0031 = OBJECT(Param,t)->params->length;
              { CL_INT loop_handle = ClEnv->cHandle;
                g0033UU= _oid_(CFALSE);
                while (((CL_INT)i <= (CL_INT)g0031))
                { { ClaireBoolean * g0034I;
                    { OID  g0035UU;
                      { OID  _Zt = (*(OBJECT(Param,t)->args))[i];
                        OID  _Zv = funcall_property(OBJECT(property,(*(OBJECT(Param,t)->params))[i]),x);
                        if (Kernel._set == OWNER(_Zt))
                         g0035UU = _oid_(Ztype_any(_Zv,_Zt));
                        else g0035UU = _oid_(vmatch_ask_any(_Zt,_Zv,n));
                          }
                      g0034I = not_any(g0035UU);
                      }
                    
                    if (g0034I == CTRUE) { g0033UU = Kernel.ctrue;
                        ClEnv->cHandle = loop_handle;break;}
                      }
                  ++i;
                  POP_SIGNAL;}
                }
              }
            v_and = not_any(g0033UU);
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
          else { { OID  g0036UU;
              { CL_INT  i = 1;
                CL_INT  g0032 = OBJECT(bag,x)->length;
                { CL_INT loop_handle = ClEnv->cHandle;
                  g0036UU= _oid_(CFALSE);
                  while (((CL_INT)i <= (CL_INT)g0032))
                  { if (vmatch_ask_any((*(OBJECT(bag,t)))[i],(*(OBJECT(bag,x)))[i],n) != CTRUE)
                     { g0036UU = Kernel.ctrue;
                      ClEnv->cHandle = loop_handle;break;}
                    ++i;
                    POP_SIGNAL;}
                  }
                }
              v_and = not_any(g0036UU);
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
ClaireBoolean * tmatch_ask_list(list *l,list *l2)
{ { ClaireBoolean *Result ;
    { CL_INT  x = l2->length;
      CL_INT  z = l->length;
      if ((z != x) && 
          (((*(l2))[x] != _oid_(Kernel._listargs)) || 
              ((CL_INT)z < (CL_INT)((CL_INT)x-(CL_INT)1))))
       Result = CFALSE;
      else { OID  g0038UU;
          { CL_INT  i = 1;
            CL_INT  g0037 = x;
            { CL_INT loop_handle = ClEnv->cHandle;
              g0038UU= _oid_(CFALSE);
              while (((CL_INT)i <= (CL_INT)g0037))
              { if ((i == x) && 
                    ((*(l2))[i] == _oid_(Kernel._listargs)))
                 { g0038UU = Kernel.cfalse;
                  ClEnv->cHandle = loop_handle;break;}
                else if (tmatch_ask_any((*(l))[i],(*(l2))[i],l) != CTRUE)
                 { g0038UU = Kernel.ctrue;
                  ClEnv->cHandle = loop_handle;break;}
                ++i;
                POP_SIGNAL;}
              }
            }
          Result = not_any(g0038UU);
          }
        }
    POP_SIGNAL; return (Result);}
  }


// types pattern matching (t is the variable and t2 the pattern)
// note that less is redefinable
// The c++ function for: tmatch?(t:any,mClaire/t2:any,l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
ClaireBoolean * tmatch_ask_any(OID t,OID t2,list *l)
{ GC_BIND;
  { ClaireBoolean *Result ;
    if (inherit_ask_class(OWNER(t),Kernel._type) != CTRUE)
     { if (should_trace_ask_module1(Core.it,0) == CTRUE)
       mtformat_module1(Core.it,"Warning: tmatch?(~S,~S,~S), ~S is not a type\n \n",0,list::alloc(4,t,
        t2,
        _oid_(l),
        t));
      else ;Result = CFALSE;
      }
    else if (INHERIT(OWNER(t2),Kernel._class))
     { Result = ((INHERIT(OWNER(t),Kernel._class)) ?
        inherit_ask_class(OBJECT(ClaireClass,t),OBJECT(ClaireClass,t2)) :
        OBJECT(ClaireBoolean,(*Core._inf_equalt)(t,
          t2)) );
      }
    else if (INHERIT(OWNER(t2),Core._subtype))
     Result = (((OBJECT(subtype,t2)->arg == Core._subtype) ? ((OBJECT(ClaireBoolean,(*Core._inf_equalt)(t,
      _oid_(Kernel._type)))) == CTRUE) : (tmatch_ask_any(t,_oid_(OBJECT(subtype,t2)->arg),l) == CTRUE)) ? ((tmatch_ask_any(GC_OID(_oid_(member_type(OBJECT(ClaireType,t)))),GC_OID(_oid_(OBJECT(subtype,t2)->t1)),l) == CTRUE) ? CTRUE: CFALSE): CFALSE);
    else if (INHERIT(OWNER(t2),Core._Param))
     { ClaireBoolean *v_and;
      { v_and = tmatch_ask_any(t,_oid_(OBJECT(Param,t2)->arg),l);
        if (v_and == CFALSE) Result =CFALSE; 
        else { { OID  g0041UU;
            { CL_INT  i = 1;
              CL_INT  g0039 = OBJECT(Param,t2)->params->length;
              { CL_INT loop_handle = ClEnv->cHandle;
                g0041UU= _oid_(CFALSE);
                while (((CL_INT)i <= (CL_INT)g0039))
                { if (tmatch_ask_any(GC_OID(_oid_(_at_type(OBJECT(ClaireType,t),OBJECT(property,(*(OBJECT(Param,t2)->params))[i])))),GC_OID((*(OBJECT(Param,t2)->args))[i]),l) != CTRUE)
                   { g0041UU = Kernel.ctrue;
                    ClEnv->cHandle = loop_handle;break;}
                  ++i;
                  POP_SIGNAL;}
                }
              }
            v_and = not_any(g0041UU);
            }
          if (v_and == CFALSE) Result =CFALSE; 
          else Result = CTRUE;}
        }
      }
    else if (INHERIT(OWNER(t2),Core._Reference))
     { if (OBJECT(Reference,t2)->arg == CTRUE)
       Result = CFALSE;
      else { if (should_trace_ask_module1(Core.it,5) == CTRUE)
           mtformat_module1(Core.it,"question is ~S less than ~S ? \n",5,GC_OBJECT(list,list::alloc(2,t,t2)));
          else ;Result = OBJECT(ClaireBoolean,(*Core._inf_equalt)(t,
            GC_OID(_at_Reference(OBJECT(Reference,t2),GC_OBJECT(list,OBJECT(Reference,t2)->args),(*(l))[((CL_INT)OBJECT(Reference,t2)->index+(CL_INT)1)]))));
          }
        }
    else if (INHERIT(OWNER(t2),Kernel._tuple))
     { if (INHERIT(OWNER(t),Kernel._tuple))
       { ClaireBoolean *v_and;
        { v_and = ((OBJECT(bag,t2)->length == OBJECT(bag,t)->length) ? CTRUE : CFALSE);
          if (v_and == CFALSE) Result =CFALSE; 
          else { { OID  g0042UU;
              { CL_INT  i = 1;
                CL_INT  g0040 = OBJECT(bag,t2)->length;
                { CL_INT loop_handle = ClEnv->cHandle;
                  g0042UU= _oid_(CFALSE);
                  while (((CL_INT)i <= (CL_INT)g0040))
                  { if (tmatch_ask_any((*(OBJECT(bag,t)))[i],(*(OBJECT(bag,t2)))[i],l) != CTRUE)
                     { g0042UU = Kernel.ctrue;
                      ClEnv->cHandle = loop_handle;break;}
                    ++i;
                    POP_SIGNAL;}
                  }
                }
              v_and = not_any(g0042UU);
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
ClaireObject * find_which_list1(list *l,ClaireClass *c,int n,int m)
{ { ClaireObject *Result ;
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
ClaireObject * find_which_class1(ClaireClass *c,list *l,int n,int m)
{ { ClaireObject *Result ;
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



