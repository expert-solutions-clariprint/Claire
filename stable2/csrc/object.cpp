/***** CLAIRE Compilation of file ./meta/object.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:31 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>

//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| object.cl                                                   |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in about()                               |
//+-------------------------------------------------------------+
// ---------------------------------------------------------------------
// This file contains the definition of the objects that implement the
// core features of the microCLAIRE library: traceable & debug-able calls,
// tables, demons and exceptions
// ---------------------------------------------------------------------
// *********************************************************************
// *  Table of contents                                                *
// *   Part 1: Ask, debug & trace                                      *
// *   Part 2: Tables                                                  *
// *   Part 3: Demons & relations for the logic modules                *
// *   Part 4: Basics of Exceptions                                    *
// *********************************************************************
// The c++ function for: release(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  release_void()
{ GC_BIND;
  { OID Result = 0;
    Result = _string_(append_string("3.",GC_STRING(string_I_float(ClEnv->version))));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// the about method produces the legal warning, according to the GNU software
// recommendation
// The c++ function for: about(_CL_obj:void) [0]
OID  about_void()
{ princ_string("CLAIRE v3.");
  princ_float(ClEnv->version);
  princ_string("\nCopyright (C) 1994-2005 Yves Caseau.\n");
  princ_string("Copyright (C) 2000-2005 eXpert soLutions.\nAll Rights Reserved.\n");
  princ_string("Contact at www.claire-language.com.\n");
  princ_string("Use in binary forms is permitted, ");
  princ_string("redistribution or resale in any form are not permitted without the ");
  princ_string("explicit agreement of Yves Caseau.\n");
  princ_string("THIS SOFTWARE IS PROVIDED AS IS AND WITHOUT ANY WARRANTY, INCLUDING, ");
  princ_string("WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTABILTY AND FITNESS ");
  princ_string("FOR A PARTICULAR PURPOSE\n");
  POP_SIGNAL; return (Kernel.ctrue);}


// *********************************************************************
// *   Part 1: Ask, debug & trace                                      *
// *********************************************************************
// create the list of arguments if needed : allocate on the stack
// The c++ function for: mClaire/get_args(i:integer) [NEW_ALLOC]
list * get_args_integer(int i)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
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
// The c++ function for: funcall(self:method,x:any) [NEW_ALLOC+SLOT_UPDATE]
OID  funcall_method1(method *self,OID x)
{ { OID Result = 0;
    { CL_INT  start = ClEnv->index;
      PUSH(x);
      Result = execute_method(self,start,CFALSE);
      }
    POP_SIGNAL; return (Result);}
  }


// this is a simple method for calling directly a method with one argument
// The c++ function for: funcall(self:method,x:any,y:any) [NEW_ALLOC+SLOT_UPDATE]
OID  funcall_method2(method *self,OID x,OID y)
{ { OID Result = 0;
    { CL_INT  start = ClEnv->index;
      PUSH(x);
      PUSH(y);
      Result = execute_method(self,start,CFALSE);
      }
    POP_SIGNAL; return (Result);}
  }


// this is a simple method for calling directly a method with two arguments
// The c++ function for: funcall(self:method,x:any,y:any,z:any) [NEW_ALLOC+SLOT_UPDATE]
OID  funcall_method3(method *self,OID x,OID y,OID z)
{ { OID Result = 0;
    { CL_INT  start = ClEnv->index;
      PUSH(x);
      PUSH(y);
      PUSH(z);
      Result = execute_method(self,start,CFALSE);
      }
    POP_SIGNAL; return (Result);}
  }


// how to apply a function to a list
// The c++ function for: apply(self:function,ls:list,l:list) [0]
OID  apply_function(ClaireFunction *self,list *ls,list *l)
{ { OID Result = 0;
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


// The c++ function for: call(p:property,l:listargs) [NEW_ALLOC+SLOT_UPDATE]
OID  call_property(property *p,listargs *l)
{ POP_SIGNAL; return (apply_property(p,l));}


// The c++ function for: apply(p:property,l:list) [NEW_ALLOC+SLOT_UPDATE]
OID  apply_property(property *p,list *l)
{ { OID Result = 0;
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


// The c++ function for: apply(m:method,l:list) [NEW_ALLOC+SLOT_UPDATE]
OID  apply_method(method *m,list *l)
{ { OID Result = 0;
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


// push and pop debug info on the stack
// this method also does the tracing and the steppping
// NOTE: self should be either a property or a restriction
// The c++ function for: push_debug(prop:property,arity:integer,start:integer) [SLOT_UPDATE]
void  push_debug_property(property *prop,int arity,int start)
{ { CL_INT  v = ClEnv->debug_I;
    CL_INT  i = ClEnv->index;
    ClaireBoolean * b_ask;
    if ((OBJECT(ClaireBoolean,Core.SHOULD_BREAK_ask->value)) == CTRUE)
     { (Core.SHOULD_BREAK_ask->value= Kernel.cfalse);
      b_ask = CTRUE;
      }
    else b_ask = CFALSE;
      CL_INT  n = ((CL_INT)ClEnv->trace_I+(CL_INT)1);
    if (0 <= (CL_INT)v)
     { PUSH(((OID)v));
      PUSH(_oid_(prop));
      PUSH(((OID)arity));
      PUSH(((OID)start));
      (ClEnv->debug_I = i);
      (ClEnv->trace_I = n);
      if ((OBJECT(ClaireBoolean,Core.BREAK_SYSTEM_ask->value)) == CTRUE)
       { if ((OBJECT(ClaireBoolean,fcall1(OBJECT(method,(*(Core.should_break_ask->restrictions))[1])->functional,Kernel._object,_oid_(ClEnv),Kernel._object))) == CTRUE)
         fcall1(OBJECT(method,(*(Core.break_system->restrictions))[1])->functional,Kernel._object,_oid_(ClEnv),Kernel._any);
        else if ((b_ask == CTRUE) || 
            ((CL_INT)n <= (CL_INT)ClEnv->step_I))
         fcall1(OBJECT(method,(*(Core.break_system->restrictions))[1])->functional,Kernel._object,_oid_(ClEnv),Kernel._any);
        }
      }
    }
  POP_SIGNAL;}


// value of the previous debug
// n is 0 for interpreted code and 1 for compiled code
// The c++ function for: pop_debug(self:property,n:integer,val:any) [0]
void  pop_debug_property(property *self,int n,OID val)
{ { CL_INT  v = ClEnv->debug_I;
    if ((CL_INT)v > 0)
     { if (n != 0)
       (ClEnv->index= ClEnv->stack[((OID)((CL_INT)v+(CL_INT)3))]);
      (ClEnv->debug_I = ClEnv->stack[((OID)ClEnv->debug_I)]);
      if ((CL_INT)ClEnv->trace_I > 0)
       (ClEnv->trace_I = ((CL_INT)ClEnv->trace_I-(CL_INT)1));
      }
    }
  POP_SIGNAL;}


// print a nice indented mark
//tr_indent(return?:boolean,n:integer) : void -> printf("~S>", n)
// *********************************************************************
// *   Part 2: Tables                                                  *
// *********************************************************************
// finds if objects are identified
// The c++ function for: identified?(self:class) [0]
ClaireBoolean * identified_ask_class(ClaireClass *self)
{ POP_SIGNAL; return (((self == Kernel._integer) ? CTRUE : ((INHERIT(self,Kernel._object)) ? CTRUE : ((self == Kernel._symbol) ? CTRUE : ((self == Kernel._boolean) ? CTRUE : ((self == Kernel._char) ? CTRUE : CFALSE))))));}


// The c++ function for: identical?(x:any,y:any) [0]
ClaireBoolean * identical_ask_any(OID x,OID y)
{ POP_SIGNAL; return (((ClaireBoolean *) (ClaireBoolean *)(((x == y) ? CTRUE : CFALSE))));}


//  let x1: (if ((x as boolean) = (y as boolean)) true else false)
// writing a single value into a slot but does NOT trigger the rules !
// equivalent to is! of LAURE
// this definition should not be placed in the method.cl file
// (it requires some inheritance conflict processing)
// The c++ function for: put(self:property,x:object,y:any) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
OID  put_property2(property *self,ClaireObject *x,OID y)
{ GC_BIND;
  { OID Result = 0;
    { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
      if (Kernel._slot == s->isa)
       Result = store_object(x,
        CLREAD(slot,s,index),
        CLREAD(slot,s,srange),
        y,
        self->store_ask);
      else { OID  V_CL0044;close_exception(((selector_error *) (*Core._selector_error)(_oid_(self),
            _oid_(list::alloc(1,_oid_(x))))));
          
          Result=_void_(V_CL0044);}
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// v3.2 : same but multi valued
// The c++ function for: add_value(self:property,x:object,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  add_value_property3(property *self,ClaireObject *x,OID y)
{ GC_BIND;
  { ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(self,OWNER(_oid_(x))));
    if (boolean_I_any(_oid_(s)) != CTRUE)
     close_exception(((selector_error *) (*Core._selector_error)(_oid_(self),
      _oid_(list::alloc(1,_oid_(x))))));
    else if (multi_ask_any(_oid_(self)) != CTRUE)
     close_exception(((general_error *) (*Core._general_error)(_string_("[134] Cannot apply add to ~S"),
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
OID  nth_table1(table *a,OID x)
{ { OID Result = 0;
    { OID  p = a->params;
      if (belong_to(x,_oid_(a->domain)) != CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("[135] ~S does not belong to the domain of ~S"),
        _oid_(list::alloc(2,x,_oid_(a))))));
      { OID  v;
        if (INHERIT(OWNER(p),Kernel._integer))
         v = (*(a->graph))[((CL_INT)(x)-p)];
        else if (INHERIT(OWNER(p),Kernel._list))
         v = (*(a->graph))[get_index_table2(a,(*(OBJECT(list,x)))[1],(*(OBJECT(list,x)))[2])];
        else { CL_INT  i = index_table(a,x);
            v = (*(a->graph))[i];
            }
          if ((v != CNULL) || 
            (belong_to(v,_oid_(a->range)) == CTRUE))
         Result = v;
        else { OID  V_CL0045;close_exception(((general_error *) (*Core._general_error)(_string_("[138] the value ~S(~S) is unknown !"),
              _oid_(list::alloc(2,_oid_(a),x)))));
            
            Result=_void_(V_CL0045);}
          }
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: nth_table1_type
ClaireType * nth_table1_type(ClaireType *a,ClaireType *x)
{ GC_BIND;
  { ClaireType *Result ;
    if (unique_ask_type(a) == CTRUE)
     Result = OBJECT(ClaireType,(*Kernel.range)(GC_OID(the_type(a))));
    else Result = Kernel._any;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: get(a:table,x:any) [RETURN_ARG]
OID  get_table(table *a,OID x)
{ { OID Result = 0;
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
ClaireType * get_table_type(ClaireType *a,ClaireType *x)
{ GC_BIND;
  { ClaireType *Result ;
    if (unique_ask_type(a) == CTRUE)
     Result = U_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(GC_OID(the_type(a))))),set::alloc(Kernel.emptySet,1,CNULL));
    else Result = Kernel._any;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// interface update method for a[x] := y
// The c++ function for: nth=(a:table,x:any,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  nth_equal_table1(table *a,OID x,OID y)
{ if (belong_to(x,_oid_(a->domain)) != CTRUE)
   close_exception(((general_error *) (*Core._general_error)(_string_("[135] ~S does not belong to the domain of ~S"),
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
void  nth_put_table(table *a,OID x,OID y)
{ GC_BIND;
  if ((((a->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE) && 
      (multi_ask_any(_oid_(a)) != CTRUE))
   fastcall_relation2(a,x,y);
  else if (multi_ask_any(_oid_(a)) == CTRUE)
   { OID  r = GC_OID(get_property(Kernel.inverse,a));
    OID  old = get_table(a,x);
    { OID  g0046UU;
      { if ((old != CNULL) && 
            (OBJECT(set,old)->length == 0))
         g0046UU = old;
        else if (a->multivalued_ask == Kernel._list)
         g0046UU = _oid_(make_list_integer2(0,GC_OBJECT(ClaireType,member_type(a->range)),((OID)0)));
        else g0046UU = _oid_(Kernel.emptySet);
          GC_OID(g0046UU);}
      ((*(GC_OBJECT(list,((list *) a->graph))))[get_index_table1(a,x)]=g0046UU);
      }
    if ((r != CNULL) && 
        (old != CNULL))
     { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(z);
      bag *z_support;
      z_support = GC_OBJECT(bag,enumerate_any(old));
      for (START(z_support); NEXT(z);)
      update_dash_relation(OBJECT(ClaireRelation,r),z,x);
      }
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
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
void  put_table(table *a,OID x,OID y)
{ { OID  p = a->params;
    OID  z = get_table(a,x);
    if (equal(z,y) != CTRUE)
     { if (INHERIT(OWNER(p),Kernel._integer))
       store_list(((list *) a->graph),((CL_INT)(x)-p),y,a->store_ask);
      else if (INHERIT(OWNER(p),Kernel._list))
       store_list(((list *) a->graph),get_index_table2(a,(*(OBJECT(list,x)))[1],(*(OBJECT(list,x)))[2]),y,a->store_ask);
      else { CL_INT  i = index_table(a,x);
          store_list(((list *) a->graph),i,y,a->store_ask);
          }
        ;}
    }
  POP_SIGNAL;}


// adds a value to a multi-valued table: interface method
// The c++ function for: add(a:table,x:any,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  add_table(table *a,OID x,OID y)
{ if (belong_to(x,_oid_(a->domain)) != CTRUE)
   close_exception(((general_error *) (*Core._general_error)(_string_("[135] ~S does not belong to the domain of ~S"),
    _oid_(list::alloc(2,x,_oid_(a))))));
  if (belong_to(y,_oid_(member_type(a->range))) != CTRUE)
   close_exception(((range_error *) (*Core._range_error)(_oid_(a),
    y,
    _oid_(a->range))));
  add_I_table(a,x,y);
  POP_SIGNAL;}


// adds a value to a multi-valued table: internal version without type checks
// The c++ function for: add!(a:table,x:any,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  add_I_table(table *a,OID x,OID y)
{ GC_BIND;
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
ClaireBoolean * add_value_array(table *self,int n,bag *l,OID y)
{ GC_BIND;
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
void  add_value_table3(table *self,OID x,OID y)
{ GC_BIND;
  { OID  p = self->params;
    CL_INT  i = get_index_table1(self,x);
    bag * l = GC_OBJECT(bag,OBJECT(bag,(*(self->graph))[i]));
    add_value_array(self,i,l,y);
    }
  GC_UNBIND; POP_SIGNAL;}


// removes a value from an table
// The c++ function for: delete(a:table,x:any,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  delete_table(table *a,OID x,OID y)
{ GC_BIND;
  { OID Result = 0;
    { OID  p = GC_OID(a->params);
      CL_INT  i = get_index_table1(a,x);
      set * l1 = GC_OBJECT(set,OBJECT(set,(*(a->graph))[i]));
      set * l;
      { bag *V_CC ;
        { bag * g0047UU;
          if (a->store_ask == CTRUE)
           g0047UU = copy_bag(l1);
          else g0047UU = l1;
            V_CC = delete_bag(g0047UU,y);
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
OID  nth_table2(table *a,OID x,OID y)
{ { OID Result = 0;
    { OID  p = a->params;
      OID  v;
      if (INHERIT(OWNER(p),Kernel._list))
       { if (((belong_to(x,(*(((bag *) a->domain)))[1]) == CTRUE) ? ((belong_to(y,(*(((bag *) a->domain)))[2]) == CTRUE) ? CTRUE: CFALSE): CFALSE) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_("[135] ~S does not belong to the domain of ~S"),
          _oid_(list::alloc(2,x,_oid_(a))))));
        v = (*(a->graph))[get_index_table2(a,x,y)];
        }
      else v = ((OID)index_table2(a,x,y));
        if ((v != CNULL) || 
          (belong_to(v,_oid_(a->range)) == CTRUE))
       Result = v;
      else { OID  V_CL0048;close_exception(((general_error *) (*Core._general_error)(_string_("~S(~S) is unknown !"),
            _oid_(list::alloc(2,_oid_(a),x)))));
          
          Result=_void_(V_CL0048);}
        }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: nth_table2_type
ClaireType * nth_table2_type(ClaireType *a,ClaireType *x,ClaireType *y)
{ GC_BIND;
  { ClaireType *Result ;
    if (unique_ask_type(a) == CTRUE)
     Result = OBJECT(ClaireType,(*Kernel.range)(GC_OID(the_type(a))));
    else Result = Kernel._any;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// sets a value in a 2-dim table
// The c++ function for: nth=(a:table,x:any,y:any,z:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  nth_equal_table2(table *a,OID x,OID y,OID z)
{ GC_BIND;
  { OID  p = GC_OID(a->params);
    if (INHERIT(OWNER(p),Kernel._list))
     { if (((belong_to(x,(*(((bag *) a->domain)))[1]) == CTRUE) ? ((belong_to(y,(*(((bag *) a->domain)))[2]) == CTRUE) ? CTRUE: CFALSE): CFALSE) != CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("[135] ~S does not belong to the domain of ~S"),
        _oid_(list::alloc(2,_oid_(list::alloc(2,x,y)),_oid_(a))))));
      if (belong_to(z,_oid_(a->range)) != CTRUE)
       close_exception(((range_error *) (*Core._range_error)(_oid_(a),
        z,
        _oid_(a->range))));
      if ((((a->inverse == (NULL)) ? CTRUE : CFALSE) != CTRUE) || 
          (((a->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE))
       nth_put_table(a,_oid_(list::alloc(2,x,y)),z);
      else store_list(((list *) a->graph),get_index_table2(a,x,y),z,a->store_ask);
        }
    else nth_equal_table1(a,_oid_(tuple::alloc(2,x,y)),z);
      }
  GC_UNBIND; POP_SIGNAL;}


// v3.2.16 tuple(a,b) is not list(a,b) !
// The c++ function for: get_index(a:table,x:any) [RETURN_ARG]
int  get_index_table1(table *a,OID x)
{ { CL_INT Result = 0;
    { OID  p = a->params;
      Result = ((INHERIT(OWNER(p),Kernel._integer)) ?
        ((CL_INT)(x)-p) :
        ((INHERIT(OWNER(p),Kernel._list)) ?
          get_index_table2(a,(*(OBJECT(list,x)))[1],(*(OBJECT(list,x)))[2]) :
          index_table(a,x) ) );
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: get_index(a:table,x:integer,y:integer) [RETURN_ARG]
int  get_index_table2(table *a,int x,int y)
{ { CL_INT Result = 0;
    { list * p = OBJECT(list,a->params);
      Result = ((CL_INT)((CL_INT)((CL_INT)((*(p))[1])*(CL_INT)x)+(CL_INT)y)-(CL_INT)((*(p))[2]));
      }
    POP_SIGNAL; return (Result);}
  }


// erase an table means to clean its graph so that it becomes empty.
// The c++ function for: erase(a:table) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  erase_table(table *a)
{ GC_BIND;
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
        ((*(GC_OBJECT(list,((list *) a->graph))))[get_index_table2(a,(*(OBJECT(bag,l)))[1],(*(OBJECT(bag,l)))[2])]=GC_OID(a->DEFAULT));
        GC_UNLOOP; POP_SIGNAL;}
      }
    else { CL_INT  i = 1;
        CL_INT  g0049 = a->graph->length;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)i <= (CL_INT)g0049))
          { GC_LOOP;
            ((*(GC_OBJECT(list,((list *) a->graph))))[i]=CNULL);
            ++i;
            GC_UNLOOP;POP_SIGNAL;}
          }
        }
      }
  GC_UNBIND; POP_SIGNAL;}


//
// Our first table: a debuging tool which stores a list of stopping values
// *********************************************************************
//   Part 3: Demons & relations for the logic modules                  *
// *********************************************************************
// applying a lambda to one argument
// The c++ function for: funcall(self:lambda,x:any) [NEW_ALLOC]
OID  funcall_lambda1(lambda *self,OID x)
{ GC_BIND;
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
OID  funcall_lambda2(lambda *self,OID x,OID y)
{ GC_BIND;
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
OID  funcall_lambda3(lambda *self,OID x,OID y,OID z)
{ GC_BIND;
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
void  check_inverse_any(OID _Zr1,OID _Zr2)
{ GC_BIND;
  { ClaireRelation * r1 = OBJECT(ClaireRelation,_Zr1);
    ClaireRelation * r2 = OBJECT(ClaireRelation,_Zr2);
    (r1->inverse = r2);
    (r2->inverse = r1);
    final_relation(r1);
    final_relation(r2);
    if ((_inf_equal_type(r1->domain,GC_OBJECT(ClaireType,((multi_ask_any(_oid_(r2)) == CTRUE) ?
        member_type(r2->range) :
        r2->range ))) != CTRUE) || 
        (_inf_equal_type(r2->domain,GC_OBJECT(ClaireType,((multi_ask_any(_oid_(r1)) == CTRUE) ?
          member_type(r1->range) :
          r1->range ))) != CTRUE))
     close_exception(((general_error *) (*Core._general_error)(_string_("[137] ~S and ~S cannot be inverses for one another"),
      _oid_(list::alloc(2,_oid_(r1),_oid_(r2))))));
    }
  GC_UNBIND; POP_SIGNAL;}


// very useful
// The c++ function for: invert(r:relation,x:any) [NEW_ALLOC]
bag * invert_relation(ClaireRelation *r,OID x)
{ GC_BIND;
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
              OID gc_local;
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
                OID gc_local;
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
              OID gc_local;
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
                OID gc_local;
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
ClaireClass * domain_I_restriction(restriction *x)
{ POP_SIGNAL; return (class_I_type(OBJECT(ClaireType,(*(x->domain))[1])));}


// The c++ function for: methods(d:class,r:class) [NEW_ALLOC]
set * methods_class(ClaireClass *d,ClaireClass *r)
{ GC_BIND;
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
void  reify_listargs(listargs *l)
{ { CL_INT loop_handle = ClEnv->cHandle;
    ITERATE(p);
    for (START(l); NEXT(p);)
    if (INHERIT(OWNER(p),Kernel._property))
     (OBJECT(property,p)->reified = CTRUE);
    }
  POP_SIGNAL;}


// *********************************************************************
// *   Part 4: Basics of Exceptions                                    *
// *********************************************************************
// a generic error that is produced by the error(" ....") instruction
// The c++ function for: self_print(self:general_error) [NEW_ALLOC+SLOT_UPDATE]
void  self_print_general_error_Core(general_error *self)
{ GC_BIND;
  princ_string("**** An error has occurred.\n");
  format_string(GC_STRING(string_v(self->cause)),GC_OBJECT(list,OBJECT(list,self->arg)));
  GC_UNBIND; POP_SIGNAL;}


// a read_slot error is produced when an unknown value is found
// The c++ function for: self_print(self:read_slot_error) [NEW_ALLOC+SLOT_UPDATE]
void  self_print_read_slot_error_Core(read_slot_error *self)
{ GC_BIND;
  format_string("****[138] The value of ~S(~S) is unknown",list::alloc(2,GC_OID(self->wrong),GC_OID(self->arg)));
  GC_UNBIND; POP_SIGNAL;}


// range errors
// The c++ function for: self_print(self:range_error) [NEW_ALLOC+SLOT_UPDATE]
void  self_print_range_error_Core(range_error *self)
{ GC_BIND;
  format_string("****[139] ~S: range error, ~S does not belong? to ~S.",list::alloc(3,GC_OID(self->cause),
    GC_OID(self->arg),
    GC_OID(self->wrong)));
  GC_UNBIND; POP_SIGNAL;}


// selector errors
// The c++ function for: self_print(self:selector_error) [NEW_ALLOC+SLOT_UPDATE]
void  self_print_selector_error_Core(selector_error *self)
{ GC_BIND;
  { OID  p = GC_OID(self->selector);
    if (boolean_I_any(_oid_(OBJECT(property,p)->restrictions)) != CTRUE)
     format_string("[140] The property ~S is not defined (was applied to ~S).",list::alloc(2,p,GC_OID(self->arg)));
    else format_string("****[141] ~S is a wrong arg list for ~S.",list::alloc(2,GC_OID(self->arg),p));
      }
  GC_UNBIND; POP_SIGNAL;}


// produced by a return (usually trapped)
// The c++ function for: self_print(self:return_error) [0]
void  self_print_return_error_Core(return_error *self)
{ princ_string("****[142] return called outside of a loop (for or while).");
  POP_SIGNAL;}


// a global variable is a named object with a special evaluation
// NOTE: we need to refine the scheme for global constants !
// GV are defeasible
// The c++ function for: close(self:global_variable) [SAFE_RESULT]
global_variable * close_global_variable(global_variable *self)
{ if (((self->value == CNULL) ? CTRUE : (((Kernel._set == self->range->isa) || 
      (belong_to(self->value,_oid_(self->range)) == CTRUE)) ? CTRUE : CFALSE)) != CTRUE)
   close_exception(((range_error *) (*Core._range_error)(self->value,
    _oid_(self),
    _oid_(self->range))));
  POP_SIGNAL; return (self);}


// interpretation of all the error codes
// The c++ function for: self_print(self:system_error) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  self_print_system_error_Core(system_error *self)
{ GC_BIND;
  { CL_INT  n = self->index;
    char * str_err;
    { ((*(GC_OBJECT(list,OBJECT(list,Core.err_l->value))))[1]=_oid_(OWNER(_oid_(self))));
      ((*(GC_OBJECT(list,OBJECT(list,Core.err_l->value))))[2]=((OID)n));
      format_string("**** An internal error has occured [~S:~A]:\n",GC_OBJECT(list,OBJECT(list,Core.err_l->value)));
      if (n == 1)
       str_err = "Dynamic allocation, item is too big (~S)";
      else if (n == 2)
       str_err = "Dynamic allocation, too large for available memory (~S)";
      else if (n == 3)
       str_err = "Object allocation, too large for available memory (~S)";
      else if (n == 5)
       str_err = "nth[~S] outside of scope for ~S";
      else if (n == 7)
       str_err = "Skip applied on ~S with a negative argument ~S";
      else if (n == 8)
       str_err = "List operation: cdr(()) is undefined";
      else if (n == 9)
       str_err = "String buffer is full: ~S";
      else if (n == 10)
       str_err = "Cannot create an imported entity from NULL reference";
      else if (n == 11)
       str_err = "nth_string[~S]: string too short ~S";
      else if (n == 12)
       str_err = "Symbol Table table full";
      else if (n == 13)
       str_err = "Cannot create a subclass for ~S [~A]";
      else if (n == 16)
       str_err = "Temporary output string buffer too small";
      else if (n == 17)
       str_err = "Bag Type Error: ~S cannot be added to ~S";
      else if (n == 18)
       str_err = "Definition of ~S is in conflict with an object from ~S";
      else if (n == 19)
       str_err = "Integer overflow";
      else if (n == 20)
       str_err = "Integer arithmetic: division/modulo of ~A by 0";
      else if (n == 21)
       str_err = "Integer to character: ~S is a wrong value";
      else if (n == 22)
       str_err = "Cannote create a string with negative length ~S";
      else if (n == 23)
       str_err = "Not enough memory to instal claire";
      else if (n == 24)
       str_err = "Execution stack is full [~A]";
      else if (n == 26)
       str_err = "Wrong usage of time counter [~A]";
      else if (n == 27)
       str_err = "Internal garbage protection stack overflow";
      else if (n == 28)
       str_err = "The multivalued status of ~S is not compatible with ~S";
      else if (n == 29)
       str_err = "There is no module ~S";
      else if (n == 30)
       str_err = "Attempt to read a private symbol ~S";
      else if (n == 31)
       str_err = "External function not compiled yet";
      else if (n == 32)
       str_err = "Too many arguments (~S) for function ~S";
      else if (n == 33)
       str_err = "Exception handling: stack overflow";
      else if (n == 34)
       str_err = "User interrupt: EXECUTION ABORTED";
      else if (n == 35)
       str_err = "Reading char '~S': wrong char: ~S";
      else if (n == 36)
       str_err = "Cannot open file ~A";
      else if (n == 37)
       str_err = "World stack is full";
      else if (n == 38)
       str_err = "Undefined access to ~S";
      else if (n == 39)
       str_err = "Cannot convert ~S to an integer";
      else if (n == 40)
       str_err = "Integer multiplication overflow with ~S and ~S";
      else if (n == 41)
       str_err = "Wrong NTH access on ~S and ~S";
      else if (n == 42)
       str_err = "Wrong array[~S] init value: ~S";
      else if (n == 43)
       str_err = "Defeasible addition on list ~S requires pre-allocation (size ~S)";
      else if (n == 50)
       str_err = "C++ imported error (~S) : ~S";
      else if (n == 57)
       str_err = "Signal stack overflow";
      else if (n == 58)
       str_err = "Invalid file operation";
      else if (n == 59)
       str_err = "~S is an invalid index for external buffer";
      else if (n == 60)
       str_err = "External buffer too long too be converted in a string";
      else if (n == 61)
       str_err = "Failed to allocate external memory [~A]";
      else if (n == 62)
       str_err = "Unescape premature end of string in [~A]";
      else if (n == 63)
       str_err = "Unescape &#...; bad formater in [~A]";
      else if (n == 64)
       str_err = "setenv(~A) failed";
      else if (n == 65)
       str_err = "setcwd(~A) failed";
      else if (n == 66)
       str_err = "pwd failed";
      else if (n == 67)
       str_err = "Invalid index ~S for environ";
      else if (n == 68)
       str_err = "Out of range category index ~S for setlocale, required in range (0 .. 5)";
      else if (n == 69)
       str_err = "The given combination of category (~S) and locale (~A) makes no sense";
      else if (n == 70)
       str_err = "The calendar time cannot be represented";
      else if (n == 71)
       str_err = "Bad wildard formater after character '#' accept only '##' '#?' '#*'";
      else if (n == 72)
       str_err = "Iteration of ~A/~A failed";
      else if (n == 73)
       str_err = "Iteration of ~A/* failed";
      else if (n == 74)
       str_err = "~A";
      else if (n == 75)
       str_err = "~A not implemented on this mahine";
      else if (n == 76)
       str_err = "Invalid process id ~S";
      else if (n == 77)
       str_err = "Could not create the process";
      else if (n == 78)
       str_err = "unlink of ~A failed";
      else if (n == 79)
       str_err = "Could not make new directory ~A with mode ~A";
      else if (n == 80)
       str_err = "Could not remove directory ~A";
      else if (n == 81)
       str_err = "Could not change mode of ~A to ~S";
      else if (n == 82)
       str_err = "Could not create link with ~A and ~A";
      else if (n == 83)
       str_err = "Could not create symbolic link with ~A and ~A";
      else if (n == 84)
       str_err = "An error has occured while copying file ~A to ~A";
      else if (n == 85)
       str_err = "Can't get forked pid since you are not a forker";
      else if (n == 86)
       str_err = "kill(~S,~S) failed";
      else if (n == 87)
       str_err = "raise(~S) failed";
      else if (n == 88)
       str_err = "setitimer(~S) failed";
      else if (n == 89)
       str_err = "getitimer(~S) failed";
      else if (n == 90)
       str_err = "The calendar time cannot be represented during the winter summer time transition";
      else if (n == 91)
       str_err = "Incorrect access to file ~A in ~A";
      else if (n == 92)
       str_err = "Operation attempted on a closed port";
      else if (n == 93)
       str_err = "Attempt to close a standard port (~S)";
      else if (n == 94)
       str_err = "lock failed on ~S";
      else if (n == 95)
       str_err = "unlock failed on ~S";
      else if (n == 96)
       str_err = "fcntl on ~S failed";
      else if (n == 97)
       str_err = "~A error on ~S";
      else if (n == 98)
       str_err = "Failed to create a pipe";
      else { (self->value = ((OID)n));
          str_err = "What the hell is this ! [code: ~S^]";
          }
        }
    if (self->cerr == 0)
     { ((*(GC_OBJECT(list,OBJECT(list,Core.err_l->value))))[1]=GC_OID(self->value));
      ((*(GC_OBJECT(list,OBJECT(list,Core.err_l->value))))[2]=GC_OID(self->arg));
      format_string(str_err,GC_OBJECT(list,OBJECT(list,Core.err_l->value)));
      }
    else { ((*(GC_OBJECT(list,OBJECT(list,Core.err_l->value))))[1]=GC_OID(_string_(cerror_integer(self->cerr))));
        format_string("[~A] ",GC_OBJECT(list,OBJECT(list,Core.err_l->value)));
        ((*(GC_OBJECT(list,OBJECT(list,Core.err_l->value))))[1]=GC_OID(self->value));
        ((*(GC_OBJECT(list,OBJECT(list,Core.err_l->value))))[2]=GC_OID(self->arg));
        format_string(str_err,GC_OBJECT(list,OBJECT(list,Core.err_l->value)));
        }
      }
  GC_UNBIND; POP_SIGNAL;}


// contradictions are nice exceptions
// The c++ function for: self_print(x:contradiction) [0]
void  self_print_contradiction_Core(contradiction *x)
{ princ_string("A contradiction has occured.");
  POP_SIGNAL;}


// the format method is used to print error messages (similar to a printf)
// The c++ function for: format(self:string,larg:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  format_string(char *self,list *larg)
{ { char * s = self;
    CL_INT  n = find_string2(s,"~");
    CL_INT  nl = 1;
    CL_INT  idx = 1;
    CL_INT  len = LENGTH_STRING(s);
    CL_INT  col = (int )(current_color);
    CL_INT  bold = (int )(current_bold);
    CL_INT  ccol = col;
    CL_INT  cbold = bold;
    { CL_INT loop_handle = ClEnv->cHandle;
      while (((0 < (CL_INT)n) && 
          ((CL_INT)n < (CL_INT)len)))
      { { ClaireChar * m = _char_(s[((CL_INT)n+(CL_INT)1) - 1]);
          if ((CL_INT)n > 1)
           { color_princ_string2(s,idx,((CL_INT)n-(CL_INT)1));
            {ccol = current_color; cbold = current_bold;};
            }
          if (((unsigned char)65 /* 'A' */) == ((unsigned char) m->ascii))
           { color(30,0);
            (*Kernel.princ)((*(larg))[nl]);
            color(ccol,cbold);
            }
          else if (((unsigned char)83 /* 'S' */) == ((unsigned char) m->ascii))
           { color(30,0);
            print_any((*(larg))[nl]);
            color(ccol,cbold);
            }
          else if (((unsigned char)73 /* 'I' */) == ((unsigned char) m->ascii))
           close_exception(((general_error *) (*Core._general_error)(_string_("[143] ~I not allowed in format"),
            _oid_(list::alloc(1,CNULL)))));
          if (((unsigned char) m->ascii) != ((unsigned char)37 /* '%' */))
           ++nl;
          idx= ((CL_INT)n+(CL_INT)2);
          n= find_string(s,"~",idx);
          }
        POP_SIGNAL;}
      }
    if ((CL_INT)idx <= (CL_INT)len)
     color_princ_string2(s,idx,len);
    color(col,bold);
    }
  POP_SIGNAL;}


// special version that prints in the trace port
// The c++ function for: tformat(self:string,i:integer,l:list) [NEW_ALLOC+SLOT_UPDATE]
OID  tformat_string(char *self,int i,list *l)
{ GC_BIND;
  { OID Result = 0;
    if ((CL_INT)i <= (CL_INT)ClEnv->verbose)
     { ClaireBoolean * isforked_ask = ((ClaireBoolean *) (ClaireBoolean *)((isforked?CTRUE:CFALSE)));
      PortObject * p = use_as_output_port(ClEnv->ctrace);
      if (isforked_ask == CTRUE)
       self= GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string("[",GC_STRING(string_I_integer (getpid_void())))),"]")),self));
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
ClaireBoolean * should_trace_ask_module1(module *m,int i)
{ { ClaireBoolean *Result ;
    Result = (((INHERIT(OWNER(m->verbose),Kernel._integer)) && 
        ((CL_INT)i <= (CL_INT)m->verbose)) ?
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
OID  mtformat_module1(module *m,char *self,int i,list *l)
{ { OID Result = 0;
    if ((((ClEnv->ctrace == (NULL)) ? CTRUE : CFALSE) != CTRUE) && 
        ((m->verbose != Kernel.cfalse) && 
          (should_trace_ask_module1(m,i) == CTRUE)))
     { PortObject * p = use_as_output_port(ClEnv->ctrace);
      if ((((ClaireBoolean *) (ClaireBoolean *)((isforked?CTRUE:CFALSE)))) == CTRUE)
       { CL_INT  g0050 = (int )(current_color);
        CL_INT  g0051 = (int )(current_bold);
        CL_INT  g0052 = g0050;
        CL_INT  g0053 = g0051;
        color(g0050,g0051);
        color_princ_string1("`RED[");
        g0050= (int )(current_color);
        g0051= (int )(current_bold);
        color(g0052,g0053);
        print_any(((OID)getpid_void()));
        color(g0050,g0051);
        color(g0050,g0051);
        color_princ_string1("]");
        color(g0052,g0053);
        }
      if (((equal_string(m->name->name,"claire") == CTRUE) ? CTRUE : 
      ((equal_string(m->name->name,"Core") == CTRUE) ? CTRUE : 
      ((equal_string(m->name->name,"Reader") == CTRUE) ? CTRUE : 
      ((equal_string(m->name->name,"Language") == CTRUE) ? CTRUE : 
      ((equal_string(m->name->name,"Generate") == CTRUE) ? CTRUE : 
      ((equal_string(m->name->name,"Optimize") == CTRUE) ? CTRUE : 
      CFALSE)))))) != CTRUE)
       { CL_INT  g0054 = (int )(current_color);
        CL_INT  g0055 = (int )(current_bold);
        CL_INT  g0056 = g0054;
        CL_INT  g0057 = g0055;
        color(g0054,g0055);
        color_princ_string1("`GREEN[");
        g0054= (int )(current_color);
        g0055= (int )(current_bold);
        color(g0056,g0057);
        princ_string(m->name->name);
        color(g0054,g0055);
        color(g0054,g0055);
        color_princ_string1(":");
        g0054= (int )(current_color);
        g0055= (int )(current_bold);
        color(g0056,g0057);
        print_any(((OID)i));
        color(g0054,g0055);
        color(g0054,g0055);
        color_princ_string1("]");
        color(g0056,g0057);
        }
      princ_string(" ");
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
// The c++ function for: princ(s:bag) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  princ_bag(bag *s)
{ { ClaireBoolean * f = CTRUE;
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(x);
      for (START(s); NEXT(x);)
      { if (f == CTRUE)
         f= CFALSE;
        else princ_string(",");
          print_any(x);
        }
      }
    }
  POP_SIGNAL;}


// we create a spcial contraidiction that we shall reuse
// how to use it
// The c++ function for: contradiction!(_CL_obj:void) [RETURN_ARG]
void  contradiction_I_void()
{ close_exception(OBJECT(ClaireException,Core.contradiction_occurs->value));
  POP_SIGNAL;}


// v0.01
//<sb> moved from Reader/file.cl
// v3.2.52
//<sb> path separator (e.g. CLAIRE_LIBS)
// The c++ function for: /(s:string,s2:string) [NEW_ALLOC+RETURN_ARG]
char * _7_string(char *s,char *s2)
{ GC_RESERVE(4);  // v3.0.55 optim !
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
              lens= ((CL_INT)lens-(CL_INT)1);
              GC_UNLOOP;POP_SIGNAL;}
            }
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while ((find_string2(s2,string_v(Core._starfs_star->value)) == 1))
            { GC_LOOP;
              GC__STRING(s2 = substring_string(s2,2,lens2), 2);
              lens2= ((CL_INT)lens2-(CL_INT)1);
              GC_UNLOOP;POP_SIGNAL;}
            }
          Result = append_string(GC_STRING(append_string(s,GC_STRING(string_v(Core._starfs_star->value)))),s2);
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: /-(s1:string,s2:string) [NEW_ALLOC+RETURN_ARG]
char * _7_dash_string(char *s1,char *s2)
{ GC_BIND;
  { char *Result ;
    { CL_INT  p = rfind_string2(s1,string_v(Core._starfs_star->value));
      if (p == LENGTH_STRING(s1))
       p= rfind_string(s1,string_v(Core._starfs_star->value),((CL_INT)p-(CL_INT)1));
      Result = (((CL_INT)p > 0) ?
        _7_string(GC_STRING(substring_string(s1,1,p)),s2) :
        _7_string(s1,s2) );
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: self_print(self:ffor_error) [NEW_ALLOC]
void  self_print_ffor_error1_Core(Core_ffor_error *self)
{ princ_string("**** forked for error, child ");
  print_any(((OID)self->childpid));
  princ_string(" returned:\n");
  princ_string(self->childstr);
  POP_SIGNAL;}


// end of file

