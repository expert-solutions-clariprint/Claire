/***** CLAIRE Compilation of file ./meta/define.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:39 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>

//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| define.cl                                                   |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+
// ---------------------------------------------------------------------
// Contents:
//   Part 2: the instantiation macros
//   Part 3: the useful stuff
//   Part 4: the other macros
// ---------------------------------------------------------------------
// *********************************************************************
// *     Part 1: Definition                                            *
// *********************************************************************
// this is the basic class instantiation
//
// The c++ function for: self_print(self:Definition) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_print_Definition_Language(Definition *self)
{ GC_BIND;
  print_any(_oid_(self->arg));
  princ_string("(");
  printbox_bag2(GC_OBJECT(list,self->args));
  { OID Result = 0;
    princ_string(")");
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// ------------- named object definition ------------------------------
//
// The c++ function for: self_print(self:Defobj) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  self_print_Defobj_Language(Defobj *self)
{ GC_RESERVE(3);  // v3.0.55 optim !
  if (self->arg == Core._global_variable)
   { OID  r = _oid_(Kernel._any);
    OID  v = CNULL;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(x);
      bag *x_support;
      x_support = GC_OBJECT(list,self->args);
      for (START(x_support); NEXT(x);)
      { GC_LOOP;
        if ((*(OBJECT(Call,x)->args))[1] == _oid_(Kernel.value))
         GC__OID(v = (*(OBJECT(Call,x)->args))[2], 3);
        else if ((*(OBJECT(Call,x)->args))[1] == _oid_(Kernel.range))
         GC__OID(r = (*(OBJECT(Call,x)->args))[2], 2);
        GC_UNLOOP; POP_SIGNAL;}
      }
    if (boolean_I_any(r) == CTRUE)
     { princ_symbol(self->ident);
      princ_string(":");
      print_any(r);
      princ_string(" := ");
      printexp_any(v,CFALSE);
      }
    else { princ_symbol(self->ident);
        princ_string(" :: ");
        printexp_any(v,CFALSE);
        }
      }
  else { princ_symbol(self->ident);
      princ_string(" :: ");
      print_any(_oid_(self->arg));
      princ_string("(");
      printbox_bag2(GC_OBJECT(list,self->args));
      princ_string(")");
      }
    GC_UNBIND; POP_SIGNAL;}


// ------------- class definition ------------------------------------
//
// The c++ function for: self_print(self:Defclass) [NEW_ALLOC+SLOT_UPDATE]
void  self_print_Defclass_Language(Defclass *self)
{ GC_BIND;
  princ_symbol(self->ident);
  if (self->params->length != 0)
   { princ_string("[");
    princ_bag(GC_OBJECT(list,self->params));
    princ_string("]");
    }
  princ_string(" <: ");
  print_any(_oid_(self->arg));
  princ_string("(");
  { CL_INT  _Zl = Core.pretty->index;
    list * l = GC_OBJECT(list,self->args);
    CL_INT  n = l->length;
    CL_INT  i = 1;
    CL_INT  g0530 = n;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while (((CL_INT)i <= (CL_INT)g0530))
      { GC_LOOP;
        if (i == 1)
         set_level_void();
        else lbreak_void();
          if (INHERIT(OWNER((*(l))[i]),Language._Vardef))
         (*Language.ppvariable)((*(l))[i]);
        else { (*Language.ppvariable)(GC_OID((*(OBJECT(bag,(*Core.args)((*(l))[i]))))[1]));
            princ_string(" = ");
            print_any(GC_OID((*(OBJECT(bag,(*Core.args)((*(l))[i]))))[2]));
            }
          if ((CL_INT)i < (CL_INT)n)
         princ_string(",");
        ++i;
        GC_UNLOOP;POP_SIGNAL;}
      }
    }
  princ_string(")");
  GC_UNBIND; POP_SIGNAL;}


// -------------- method definition ----------------------------------
//
// The c++ function for: self_print(self:Defmethod) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  self_print_Defmethod_Language(Defmethod *self)
{ GC_BIND;
  print_any(_oid_(self->arg->selector));
  princ_string("(");
  if (((self->arg->args == (NULL)) ? CTRUE : CFALSE) != CTRUE)
   ppvariable_list(GC_OBJECT(list,self->arg->args));
  princ_string(") : ");
  printexp_any(GC_OID(self->set_arg),CFALSE);
  lbreak_void();
  (Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)4));
  princ_string(" ");
  princ_string(((boolean_I_any(self->inline_ask) == CTRUE) ?
    "=>" :
    "->" ));
  princ_string(" ");
  printexp_any(GC_OID(self->body),CFALSE);
  princ_string(" ");
  (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)4));
  GC_UNBIND; POP_SIGNAL;}


// -------------- array definition -----------------------------------
// The c++ function for: self_print(self:Defarray) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  self_print_Defarray_Language(Defarray *self)
{ GC_BIND;
  print_any(GC_OID((*(self->arg->args))[1]));
  princ_string("[");
  ppvariable_list(GC_OBJECT(list,cdr_list(GC_OBJECT(list,self->arg->args))));
  princ_string("] : ");
  print_any(GC_OID(self->set_arg));
  lbreak_void();
  (Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)4));
  princ_string(" := ");
  printexp_any(GC_OID(self->body),CFALSE);
  princ_string(" ");
  (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)4));
  GC_UNBIND; POP_SIGNAL;}


// -------------- rule definition ------------------------------------
// The c++ function for: self_print(self:Defrule) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  self_print_Defrule_Language(Defrule *self)
{ GC_BIND;
  princ_symbol(self->ident);
  princ_string("(");
  ppvariable_list(GC_OBJECT(list,self->args));
  princ_string(") :: rule(");
  lbreak_integer(4);
  princ_string(" ");
  print_any(GC_OID(self->arg));
  princ_string(" ");
  lbreak_integer(4);
  princ_string("=> ");
  print_any(GC_OID(self->body));
  princ_string(")");
  (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)4));
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_print(self:Defvar) [NEW_ALLOC+SLOT_UPDATE]
void  self_print_Defvar_Language(Defvar *self)
{ GC_BIND;
  ppvariable_Variable(GC_OBJECT(Variable,self->ident));
  princ_string(" := ");
  printexp_any(GC_OID(self->arg),CFALSE);
  GC_UNBIND; POP_SIGNAL;}


// *********************************************************************
// *     Part 2: the general instantiation macro                       *
// *********************************************************************
// creation of a new object
//
// The c++ function for: self_eval(self:Definition) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  self_eval_Definition(Definition *self)
{ GC_BIND;
  { OID Result = 0;
    { ClaireClass * _Zc = self->arg;
      ClaireObject * _Zo;
      { { if ((CL_INT)_Zc->open <= 0)
           close_exception(((general_error *) (*Core._general_error)(_string_("[105] cannot instantiate ~S"),
            _oid_(list::alloc(1,_oid_(_Zc))))));
          _Zo = new_object_class(_Zc);
          }
        GC_OBJECT(ClaireObject,_Zo);}
      if (_Zc->open != ClEnv->ephemeral)
       (_Zc->instances = _Zc->instances->addFast((OID)_oid_(_Zo)));
      Result = complete_object(_Zo,GC_OBJECT(list,self->args));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// the instantiation body is a sequence of words from which the initialization
// of the object must be built.
//
// The c++ function for: complete(self:object,%l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  complete_object(ClaireObject *self,list *_Zl)
{ GC_RESERVE(6);  // v3.0.55 optim !
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(x);
    for (START(_Zl); NEXT(x);)
    { GC_LOOP;
      { property * p = make_a_property_any(GC_OID((*(OBJECT(Call,x)->args))[1]));
        OID  y = GC_OID(eval_any(GC_OID((*(OBJECT(Call,x)->args))[2])));
        ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(p,self->isa));
        if (Kernel._slot == s->isa)
         { if (belong_to(y,_oid_(CLREAD(restriction,s,range))) != CTRUE)
           range_is_wrong_slot(((slot *) s),y);
          else update_property(p,
              self,
              CLREAD(slot,s,index),
              CLREAD(slot,s,srange),
              y);
            }
        else close_exception(((general_error *) (*Core._general_error)(_string_("[106] the object ~S does not understand ~S"),
            _oid_(list::alloc(2,_oid_(self),_oid_(p))))));
          }
      GC_UNLOOP; POP_SIGNAL;}
    }
  { OID Result = 0;
    Result = _oid_(complete_I_object(self));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// creation of a new named object
//
// The c++ function for: self_eval(self:Defobj) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  self_eval_Defobj(Defobj *self)
{ GC_BIND;
  { OID Result = 0;
    { ClaireClass * _Zc = self->arg;
      if ((CL_INT)_Zc->open <= 0)
       close_exception(((general_error *) (*Core._general_error)(_string_("[105] cannot instantiate ~S"),
        _oid_(list::alloc(1,_oid_(_Zc))))));
      if (INHERIT(_Zc,Kernel._thing))
       { thing * _Zo = new_thing_class(_Zc,self->ident);
        if (INHERIT(_Zo->isa,Kernel._property))
         { if ((CL_INT)CLREAD(property,_Zo,restrictions)->length > 0)
           close_exception(((general_error *) (*Core._general_error)(_string_("[188] the property ~S is already defined"),
            _oid_(list::alloc(1,_oid_(_Zo))))));
          }
        Result = complete_object(_Zo,GC_OBJECT(list,self->args));
        }
      else { ClaireObject * ob = GC_OBJECT(ClaireObject,new_object_class(_Zc));
          if (_Zc->open != ClEnv->ephemeral)
           _Zc->instances->addFast((OID)_oid_(ob));
          Result = put_symbol(self->ident,complete_object(ob,GC_OBJECT(list,self->args)));
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// creation of a new named object
// The c++ function for: self_eval(self:Defclass) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_eval_Defclass(Defclass *self)
{ if ((INHERIT(owner_any(get_symbol(self->ident)),Kernel._class)) && 
      ((OBJECT(ClaireClass,get_symbol(self->ident))->open != ((CL_INT)-2)) || 
          (self->arg != OBJECT(ClaireClass,get_symbol(self->ident))->superclass))) 
  { { OID Result = 0;
      { OID  V_CL0536;close_exception(((general_error *) (*Core._general_error)(_string_("[107] class re-definition is not valid: ~S"),
          _oid_(list::alloc(1,_oid_(self))))));
        
        Result=_void_(V_CL0536);}
      return (Result);}
     }
  else{ if ((self->arg->open == 1) || 
        (self->arg->open == ((CL_INT)-1))) 
    { { OID Result = 0;
        { OID  V_CL0537;close_exception(((general_error *) (*Core._general_error)(_string_("[109] the parent class ~S of ~S is closed"),
            _oid_(list::alloc(2,_oid_(self->arg),_oid_(self))))));
          
          Result=_void_(V_CL0537);}
        return (Result);}
       }
    else{ GC_RESERVE(8);  // v3.0.55 optim !
      { OID Result = 0;
        { ClaireClass * _Zo = class_I_symbol(self->ident,self->arg);
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(x);
            bag *x_support;
            x_support = GC_OBJECT(list,self->args);
            for (START(x_support); NEXT(x);)
            { GC_LOOP;
              { OID  v = CNULL;
                if (INHERIT(OWNER(x),Language._Call))
                 { GC__OID(v = eval_any(GC_OID((*(OBJECT(Call,x)->args))[2])), 4);
                  GC__OID(x = (*(OBJECT(Call,x)->args))[1], 3);
                  }
                { ClaireType * rt = GC_OBJECT(ClaireType,extract_type_any(GC_OID((*Kernel.range)(x))));
                  property * p = make_a_property_any(_oid_(OBJECT(Variable,x)->pname));
                  slot * ps = OBJECT(slot,last_list(_Zo->slots));
                  CL_INT  ix = ps->index;
                  if ((v != CNULL) && 
                      (belong_to(v,_oid_(rt)) != CTRUE))
                   close_exception(((general_error *) (*Core._general_error)(_string_("[108] default(~S) = ~S does not belong to ~S"),
                    _oid_(list::alloc(3,x,
                      v,
                      _oid_(rt))))));
                  { ClaireBoolean * g0538I;
                    { ClaireBoolean *v_and;
                      { v_and = (((CL_INT)p->open <= 0) ? CTRUE : CFALSE);
                        if (v_and == CFALSE) g0538I =CFALSE; 
                        else { { OID  g0539UU;
                            { CL_INT loop_handle = ClEnv->cHandle;
                              OID gc_local;
                              ITERATE(sx);
                              g0539UU= Kernel.cfalse;
                              for (START(self->arg->slots); NEXT(sx);)
                              if (OBJECT(restriction,sx)->selector == p)
                               { g0539UU = Kernel.ctrue;
                                ClEnv->cHandle = loop_handle;break;}
                              }
                            v_and = boolean_I_any(g0539UU);
                            }
                          if (v_and == CFALSE) g0538I =CFALSE; 
                          else g0538I = CTRUE;}
                        }
                      }
                    
                    if (g0538I == CTRUE) close_exception(((general_error *) (*Core._general_error)(_string_("[181] cannot overide a slot for a closed property ~S"),
                        _oid_(list::alloc(1,_oid_(p))))));
                      }
                  if (ps->range == Kernel._float)
                   ++ix;
                  add_slot_class(_Zo,
                    p,
                    rt,
                    v,
                    ((CL_INT)ix+(CL_INT)1));
                  }
                }
              GC_UNLOOP; POP_SIGNAL;}
            }
          close_class(_Zo);
          if (self->forward_ask == CTRUE)
           (_Zo->open = -2);
          else if (_Zo->open == ((CL_INT)-2))
           (_Zo->open = 2);
          if (_inf_equal_type(_Zo,Kernel._cl_import) == CTRUE)
           (_Zo->open = -1);
          (_Zo->params = self->params);
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(p);
            bag *p_support;
            p_support = GC_OBJECT(list,self->params);
            for (START(p_support); NEXT(p);)
            (OBJECT(property,p)->open = 0);
            }
          attach_comment_any(_oid_(_Zo));
          Result = _oid_(_Zo);
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
      }
    }
  }


// method definition
// v0.01
// The c++ function for: self_eval(self:Defmethod) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT]
OID  self_eval_Defmethod(Defmethod *self)
{ GC_BIND;
  if (inherit_ask_class(self->arg->isa,Language._Call) != CTRUE)
   close_exception(((general_error *) (*Core._general_error)(_string_("[110] wrong signature definition ~S"),
    _oid_(list::alloc(1,GC_OID(_oid_(self->arg)))))));
  { OID Result = 0;
    { property * p = make_a_property_any(_oid_(self->arg->selector));
      list * l = GC_OBJECT(list,self->arg->args);
      list * lv;
      if ((l->length == 1) && 
          ((*(l))[1] == _oid_(ClEnv)))
       { OID v_bag;
        GC_ANY(lv= list::empty(Kernel.emptySet));
        { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
            (_CL_obj->pname = symbol_I_string2("XfakeParameter"));
            (_CL_obj->range = Kernel._void);
            add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
            v_bag = _oid_(_CL_obj);
            }
          GC_OID(v_bag);}
        ((list *) lv)->addFast((OID)v_bag);}
      else lv = l;
        list * lp = GC_OBJECT(list,extract_signature_list(lv));
      list * lrange = GC_OBJECT(list,extract_range_any(GC_OID(self->set_arg),lv,GC_OBJECT(list,OBJECT(list,Language.LDEF->value))));
      list * lbody = GC_OBJECT(list,extract_status_any(GC_OID(self->body)));
      method * m = add_method_property(p,
        lp,
        OBJECT(ClaireType,(*(lrange))[1]),
        (*(lbody))[1],
        (*(lbody))[2]);
      if (((CL_INT)p->open > 0) && 
          (((CL_INT)p->open <= 1) && 
            (p->dispatcher == 0)))
       { OID  rtest;
        { { OID  r_some = CNULL;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(r);
              for (START(p->restrictions); NEXT(r);)
              if (r != _oid_(m))
               { if (length_bag(_exp_list(OBJECT(restriction,r)->domain,m->domain)) != 0)
                 { r_some= r;
                  ClEnv->cHandle = loop_handle; break;}
                }
              }
            rtest = r_some;
            }
          GC_OID(rtest);}
        if (rtest != CNULL)
         { restriction * r = OBJECT(restriction,rtest);
          if (should_trace_ask_module1(Language.it,1) == CTRUE)
           mtformat_module1(Language.it,"`BLUE--- WARNING ! [186] conflict between ~S and ~S is dangerous since ~S is closed\n",1,list::alloc(3,_oid_(m),
            _oid_(r),
            _oid_(p)));
          else ;}
        else ;}
      (Language.LDEF->value= _oid_(list::empty(Kernel._any)));
      if ((*(lbody))[3] != _oid_(Kernel.body))
       (m->formula = lambda_I_list(lv,(*(lbody))[3]));
      if ((CL_INT)lrange->length > 1)
       (m->typing = (*(lrange))[2]);
      update_property(Kernel.inline_ask,
        m,
        13,
        Kernel._object,
        GC_OID(self->inline_ask));
      attach_comment_any(_oid_(m));
      if ((p == Kernel.close) && 
          (_inf_equal_type(m->range,domain_I_restriction(m)) != CTRUE))
       close_exception(((general_error *) (*Core._general_error)(_string_("[184] the close method ~S has a wrong range"),
        _oid_(list::alloc(1,_oid_(m))))));
      (m->location = self->arg->location);
      Result = _oid_(m);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// v3.2.24
// attach a cute comment if needed ... to a defclass or a defmethod
// The c++ function for: attach_comment(x:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  attach_comment_any(OID x)
{ GC_BIND;
  if (((OBJECT(ClaireBoolean,Language.NeedComment->value)) == CTRUE) && 
      (Language.LastComment->value != CNULL))
   write_property(Kernel.comment,OBJECT(ClaireObject,x),GC_OID(Language.LastComment->value));
  GC_UNBIND; POP_SIGNAL;}


// returns the list of types AND modifies LDEF
// The c++ function for: iClaire/extract_signature(l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
list * extract_signature_list(list *l)
{ GC_BIND;
  (Language.LDEF->value= _oid_(list::empty(Kernel._any)));
  { list *Result ;
    { CL_INT  n = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        bag *v_list; OID v_val;
        OID v; CL_INT CLcount;
        v_list = l;
         Result = v_list->clone();
        for (CLcount= 1; CLcount <= v_list->length; CLcount++)
        { v = (*(v_list))[CLcount];
          if (inherit_ask_class(OBJECT(ClaireObject,v)->isa,Language._Variable) != CTRUE)
           { OID  V_CL0540;close_exception(((general_error *) (*Core._general_error)(_string_("[111] wrong typed argument ~S"),
              _oid_(list::alloc(1,v)))));
            
            v_val=_void_(V_CL0540);}
          else { OID  p = GC_OID(extract_pattern_any(GC_OID(_oid_(OBJECT(Variable,v)->range)),list::alloc(1,((OID)n))));
              ++n;
              if (p == CNULL)
               close_exception(((general_error *) (*Core._general_error)(_string_("[111] wrong typed argument ~S (~S)"),
                _oid_(list::alloc(2,v,GC_OID(_oid_(OBJECT(Variable,v)->range)))))));
              (OBJECT(Variable,v)->range = type_I_any(p));
              v_val = p;
              }
            
          (*((list *) Result))[CLcount] = v_val;}
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// takes an <exp> that must belong to <type> and returns the CLAIRE type
// if LDEF is non-empty, it is used as a list of type variable and patterns
// may be returned. In addition, if the path list is non empty, new type
// variables may be defined. a syntax error will produce the unknown value
//
// The c++ function for: iClaire/extract_pattern(x:any,path:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  extract_pattern_any(OID x,list *path)
{ GC_BIND;
  { OID Result = 0;
    if (INHERIT(OWNER(x),Kernel._class))
     Result = x;
    else if (Kernel._set == OWNER(x))
     { OID  z;
      { if (OBJECT(bag,x)->length == 1)
         z = extract_pattern_any((*(OBJECT(bag,x)))[1],Kernel.nil);
        else z = Kernel.cfalse;
          GC_OID(z);}
      if (INHERIT(OWNER(z),Core._Reference))
       { Reference * w = GC_OBJECT(Reference,((Reference *) copy_object(OBJECT(ClaireObject,z))));
        (w->arg = CTRUE);
        Result = _oid_(w);
        }
      else Result = x;
        }
    else if (INHERIT(OWNER(x),Language._Tuple))
     { list * ltp;
      { { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID z; CL_INT CLcount;
          v_list = GC_OBJECT(list,OBJECT(Construct,x)->args);
           ltp = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { z = (*(v_list))[CLcount];
            v_val = extract_pattern_any(z,path);
            
            (*((list *) ltp))[CLcount] = v_val;}
          }
        GC_OBJECT(list,ltp);}
      { ClaireBoolean * g0541I;
        { OID  g0542UU;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(y);
            g0542UU= Kernel.cfalse;
            for (START(ltp); NEXT(y);)
            if (y == CNULL)
             { g0542UU = Kernel.ctrue;
              ClEnv->cHandle = loop_handle;break;}
            }
          g0541I = boolean_I_any(g0542UU);
          }
        
        if (g0541I == CTRUE) Result = CNULL;
          else Result = _oid_(tuple_I_list(ltp));
        }
      }
    else if (INHERIT(OWNER(x),Core._global_variable))
     Result = extract_pattern_any(GC_OID(OBJECT(global_variable,x)->value),path);
    else if (INHERIT(OWNER(x),Language._Call))
     { property * p = OBJECT(Call,x)->selector;
      if (p == Core.U)
       { OID  x1 = GC_OID(extract_pattern_any(GC_OID((*(OBJECT(Call,x)->args))[1]),Kernel.nil));
        OID  x2 = GC_OID(extract_pattern_any(GC_OID((*(OBJECT(Call,x)->args))[2]),Kernel.nil));
        if ((x1 == CNULL) || 
            (x2 == CNULL))
         Result = CNULL;
        else Result = _oid_(U_type(OBJECT(ClaireType,x1),OBJECT(ClaireType,x2)));
          }
      else if (p == Kernel._exp)
       Result = (*Kernel._exp)(GC_OID(extract_pattern_any(GC_OID((*(OBJECT(Call,x)->args))[1]),Kernel.nil)),
        GC_OID(extract_pattern_any(GC_OID((*(OBJECT(Call,x)->args))[2]),Kernel.nil)));
      else if (p == Kernel._dot_dot)
       { OID  v1 = GC_OID(extract_item_any(GC_OID((*(OBJECT(Call,x)->args))[1]),Core.nil->value));
        OID  v2 = GC_OID(extract_item_any(GC_OID((*(OBJECT(Call,x)->args))[2]),Core.nil->value));
        if ((INHERIT(OWNER(v1),Kernel._integer)) && 
            (INHERIT(OWNER(v2),Kernel._integer)))
         Result = _oid_(_dot_dot_integer(v1,v2));
        else Result = CNULL;
          }
      else if (p == Kernel.nth)
       Result = extract_pattern_nth_list(GC_OBJECT(list,OBJECT(Call,x)->args),path);
      else if (p == Kernel._star)
       { OID  z = GC_OID(extract_pattern_any(GC_OID((*(OBJECT(Call,x)->args))[1]),path));
        if (z != CNULL)
         Result = _oid_(U_type(OBJECT(ClaireType,z),set::alloc(Kernel.emptySet,1,CNULL)));
        else Result = CNULL;
          }
      else Result = CNULL;
        }
    else if (INHERIT(OWNER(x),Kernel._type))
     Result = x;
    else if (INHERIT(OWNER(x),Kernel._unbound_symbol))
     { symbol * s = extract_symbol_any(x);
      OID  v;
      { { OID  z_some = CNULL;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(z);
            bag *z_support;
            z_support = GC_OBJECT(bag,enumerate_any(GC_OID(Language.LDEF->value)));
            for (START(z_support); NEXT(z);)
            { GC_LOOP;
              if (OBJECT(Variable,z)->pname == s)
               { z_some= z;
                ClEnv->cHandle = loop_handle; break;}
              GC_UNLOOP; POP_SIGNAL;}
            }
          v = z_some;
          }
        GC_OID(v);}
      if (v != CNULL)
       Result = (*Kernel.range)(v);
      else if ((INHERIT(path->isa,Kernel._list)) && ((CL_INT)path->length > 1))
       { Reference * y;
        { { Reference * _CL_obj = ((Reference *) GC_OBJECT(Reference,new_object_class(Core._Reference)));
            (_CL_obj->index = (*(path))[1]);
            (_CL_obj->args = cdr_list(path));
            add_I_property(Kernel.instances,Core._Reference,11,_oid_(_CL_obj));
            y = _CL_obj;
            }
          GC_OBJECT(Reference,y);}
        Variable * v;
        { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
            (_CL_obj->pname = s);
            (_CL_obj->range = y);
            add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
            v = _CL_obj;
            }
          GC_OBJECT(Variable,v);}
        (Language.LDEF->value= (*Kernel.add)(GC_OID(Language.LDEF->value),
          _oid_(v)));
        Result = _oid_(Kernel._void);
        }
      else Result = CNULL;
        }
    else Result = CNULL;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// takes an <exp> that must belong to <type> and returns the CLAIRE type
//
// The c++ function for: iClaire/extract_type(x:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
ClaireType * extract_type_any(OID x)
{ GC_BIND;
  { ClaireType *Result ;
    { ClaireObject *V_CC ;
      { (Language.LDEF->value= _oid_(list::empty(Kernel._any)));
        { OID  r = GC_OID(extract_pattern_any(x,Kernel.nil));
          if (r == CNULL)
           close_exception(((general_error *) (*Core._general_error)(_string_("[112] wrong type expression ~S"),
            _oid_(list::alloc(1,x)))));
          else V_CC = OBJECT(ClaireType,r);
            }
        }
      Result= (ClaireType *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// an item is an integer, a float, a symbol, a string or a type
//
// The c++ function for: extract_item(x:any,y:any) [NEW_ALLOC+RETURN_ARG]
OID  extract_item_any(OID x,OID y)
{ if (((((INHERIT(OWNER(x),Kernel._integer)) || 
            (Kernel._float == OWNER(x))) || 
          (INHERIT(OWNER(x),Kernel._symbol))) || 
        (Kernel._string == OWNER(x))) || 
      (INHERIT(OWNER(x),Kernel._type))) 
  { { OID Result = 0;
      Result = x;
      return (Result);}
     }
  else{ GC_BIND;
    { OID Result = 0;
      if (INHERIT(OWNER(x),Core._global_variable))
       Result = extract_item_any(GC_OID((*Kernel.value)(x)),y);
      else Result = CNULL;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  }


// version for X[...] which is the most complex case - note the extensibility
// patch.
// The c++ function for: extract_pattern_nth(l:list,path:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  extract_pattern_nth_list(list *l,list *path)
{ GC_BIND;
  { OID Result = 0;
    { CL_INT  m = l->length;
      OID  x = (*(l))[1];
      if (m == 1)
       { OID  y = GC_OID(extract_pattern_any((*(l))[1],Kernel.nil));
        if (y == CNULL)
         Result = CNULL;
        else { Param * _CL_obj = ((Param *) GC_OBJECT(Param,new_object_class(Core._Param)));
            (_CL_obj->arg = Kernel._array);
            (_CL_obj->params = list::alloc(1,_oid_(Kernel.of)));
            (_CL_obj->args = list::alloc(1,_oid_(set::alloc(1,y))));
            Result = _oid_(_CL_obj);
            }
          }
      else if (m == 2)
       { if (((x == _oid_(Core._subtype)) || 
              ((x == _oid_(Kernel._set)) || 
                (x == _oid_(Kernel._list)))) || 
            (inherit_ask_class(OWNER(x),Kernel._class) != CTRUE))
         { OID  y = GC_OID(extract_pattern_any((*(l))[2],Kernel.nil));
          { ClaireHandler c_handle = ClaireHandler();
            if ERROR_IN 
            { if (y != CNULL)
               Result = (*Kernel.nth)((*(l))[1],
                y);
              else Result = CNULL;
                ERROR_FREE;}
            else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
            { c_handle.catchIt();Result = CNULL;
              }
            else PREVIOUS_HANDLER;}
          }
        else Result = CNULL;
          }
      else { OID  l1 = (*(l))[2];
          OID  l2 = GC_OID((*Core.args)((*(l))[3]));
          list * l3 = list::empty(Kernel._any);
          { CL_INT  n = 1;
            CL_INT  g0543 = (*Kernel.length)(l1);
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while (((CL_INT)n <= (CL_INT)g0543))
              { GC_LOOP;
                { OID  y = (*(OBJECT(bag,l2)))[n];
                  { OID  g0544UU;
                    { if (INHERIT(OWNER(y),Language._Set))
                       { OID  v = GC_OID(extract_pattern_any(GC_OID((*(OBJECT(Construct,y)->args))[1]),((list *) copy_bag(path))->addFast((OID)GC_OID((*Kernel.nth)(l1,
                          ((OID)n))))));
                        if (v == _oid_(Kernel._void))
                         g0544UU = _oid_(Kernel._any);
                        else if (INHERIT(OWNER(v),Core._Reference))
                         { Reference * z = GC_OBJECT(Reference,((Reference *) copy_object(OBJECT(ClaireObject,v))));
                          (z->arg = CTRUE);
                          g0544UU = _oid_(z);
                          }
                        else { set * V_CL0545;{ OID v_bag;
                              GC_ANY(V_CL0545= set::empty(Kernel.emptySet));
                              { if (v != CNULL)
                                 v_bag = v;
                                else v_bag = eval_any(GC_OID((*(OBJECT(Construct,y)->args))[1]));
                                  GC_OID(v_bag);}
                              ((set *) V_CL0545)->addFast((OID)v_bag);}
                            
                            g0544UU=_oid_(V_CL0545);}
                          }
                      else { list * g0546UU;
                          { ClaireObject *V_CC ;
                            if (path->length != 0)
                             V_CC = path->addFast((OID)GC_OID((*Kernel.nth)(l1,
                              ((OID)n))));
                            else V_CC = CFALSE;
                              g0546UU= (list *) V_CC;}
                          g0544UU = extract_pattern_any(y,g0546UU);
                          }
                        GC_OID(g0544UU);}
                    l3 = l3->addFast((OID)g0544UU);
                    }
                  }
                ++n;
                GC_UNLOOP;POP_SIGNAL;}
              }
            }
          if (l3->memq(CNULL) == CTRUE)
           Result = CNULL;
          else { Param * _CL_obj = ((Param *) GC_OBJECT(Param,new_object_class(Core._Param)));
              update_property(Kernel.arg,
                _CL_obj,
                2,
                Kernel._object,
                x);
              update_property(Kernel.params,
                _CL_obj,
                3,
                Kernel._object,
                l1);
              (_CL_obj->args = l3);
              Result = _oid_(_CL_obj);
              }
            }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// we perform some pre-processing on x[l] at reading time to make evaluation easier
// The c++ function for: iClaire/extract_class_call(self:class,l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
ClaireObject * extract_class_call_class(ClaireClass *self,list *l)
{ GC_RESERVE(13);  // v3.0.55 optim !
  { ClaireObject *Result ;
    { ClaireObject *V_CC ;
      { ClaireBoolean * g0548I;
        { ClaireBoolean *v_and;
          { v_and = ((self == Core._subtype) ? CTRUE : ((self == Kernel._set) ? CTRUE : ((self == Kernel._list) ? CTRUE : CFALSE)));
            if (v_and == CFALSE) g0548I =CFALSE; 
            else { v_and = ((l->length == 1) ? CTRUE : CFALSE);
              if (v_and == CFALSE) g0548I =CFALSE; 
              else { { OID  y = (*(l))[1];
                  OID  z = GC_OID(extract_pattern_any(y,Kernel.nil));
                  if (INHERIT(OWNER(y),Core._global_variable))
                   y= GC_OID((*Kernel.value)((*(l))[1]));
                  v_and = ((INHERIT(OWNER(z),Kernel._type)) ? CTRUE : ((self == Core._subtype) ? CTRUE : (((INHERIT(OWNER(y),Language._Call)) ? ((OBJECT(Call,y)->selector != Kernel._equal) || 
                      (OBJECT(Call,y)->args->length != 2)) : ((INHERIT(OWNER(y),Language._Tuple)) && (CTRUE == CTRUE))) ? CTRUE : CFALSE)));
                  }
                if (v_and == CFALSE) g0548I =CFALSE; 
                else g0548I = CTRUE;}
              }
            }
          }
        
        if (g0548I == CTRUE) { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            (_CL_obj->selector = Kernel.nth);
            (_CL_obj->args = cons_any(_oid_(self),l));
            add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
            V_CC = _CL_obj;
            }
          else if (self == Core._lambda)
         { if ((l->length == 2) && 
              ((INHERIT(OWNER((*(l))[1]),Language._Do)) || 
                  (INHERIT(OWNER((*(l))[1]),Language._Variable))))
           { list * lv;
            { if (INHERIT(OWNER((*(l))[1]),Language._Do))
               { list * v_out = list::empty(Kernel.emptySet);
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(v);
                  bag *v_support;
                  v_support = GC_OBJECT(list,OBJECT(bag,(*Core.args)((*(l))[1])));
                  for (START(v_support); NEXT(v);)
                  if (INHERIT(OWNER(v),Language._Variable))
                   v_out->addFast((OID)v);
                  }
                lv = GC_OBJECT(list,v_out);
                }
              else lv = list::alloc(1,(*(l))[1]);
                GC_OBJECT(list,lv);}
            extract_signature_list(lv);
            V_CC = lambda_I_list(lv,(*(l))[2]);
            }
          else close_exception(((general_error *) (*Core._general_error)(_string_("[113] Wrong lambda definition lambda[~S]"),
              _oid_(list::alloc(1,_oid_(l))))));
            }
        else { list * l1 = GC_OBJECT(list,list::empty(Kernel._any));
            list * l2 = GC_OBJECT(list,list::empty(Kernel._any));
            CL_INT  m = l->length;
            { CL_INT  n = 1;
              CL_INT  g0547 = m;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                while (((CL_INT)n <= (CL_INT)g0547))
                { GC_LOOP;
                  { OID  y = (*(l))[n];
                    OID  p = CNULL;
                    OID  v = CNULL;
                    if (INHERIT(OWNER(y),Language._Call))
                     { if (((OBJECT(Call,y)->selector == Kernel._equal) ? ((OBJECT(Call,y)->args->length == 2) ? CTRUE: CFALSE): CFALSE) != CTRUE)
                       close_exception(((general_error *) (*Core._general_error)(_string_("[114] Wrong parametrization ~S"),
                        _oid_(list::alloc(1,y)))));
                      GC__OID(p = _oid_(make_a_property_any(GC_OID((*(OBJECT(Call,y)->args))[1]))), 10);
                      { { Set * _CL_obj = ((Set *) GC_OBJECT(Set,new_object_class(Language._Set)));
                          (_CL_obj->args = list::alloc(1,GC_OID((*(OBJECT(Call,y)->args))[2])));
                          add_I_property(Kernel.instances,Language._Set,11,_oid_(_CL_obj));
                          v = _oid_(_CL_obj);
                          }
                         GC__OID(v, 11);}
                      }
                    else if (INHERIT(OWNER(y),Language._Vardef))
                     { p= _oid_(make_a_property_any(_oid_(OBJECT(Variable,y)->pname)));
                      GC__OID(v = _oid_(OBJECT(Variable,y)->range), 11);
                      }
                    else { GC__OID(p = _oid_(make_a_property_any(y)), 10);
                        v= _oid_(Kernel.emptySet);
                        }
                      l1= l1->addFast((OID)p);
                    l2= l2->addFast((OID)v);
                    }
                  ++n;
                  GC_UNLOOP;POP_SIGNAL;}
                }
              }
            { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (_CL_obj->selector = Kernel.nth);
              { Call * g0549 = _CL_obj; 
                list * g0550;
                { list * g0551UU;
                  { { OID v_bag;
                      GC_ANY(g0551UU= list::empty(Kernel.emptySet));
                      ((list *) g0551UU)->addFast((OID)_oid_(l1));
                      { { List * _CL_obj = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                          (_CL_obj->args = l2);
                          add_I_property(Kernel.instances,Language._List,11,_oid_(_CL_obj));
                          v_bag = _oid_(_CL_obj);
                          }
                        GC_OID(v_bag);}
                      ((list *) g0551UU)->addFast((OID)v_bag);}
                    GC_OBJECT(list,g0551UU);}
                  g0550 = cons_any(_oid_(self),g0551UU);
                  }
                (g0549->args = g0550);}
              add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
              V_CC = _CL_obj;
              }
            }
          }
      Result= (ClaireObject *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// extract the range (type and/or second-order function)
// lvar is the list of arguments that will serve as second-o. args
// ldef is the list of extra type variables that are defined in the sig.
// The c++ function for: iClaire/extract_range(x:any,lvar:list,ldef:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
list * extract_range_any(OID x,list *lvar,list *ldef)
{ GC_RESERVE(13);  // v3.0.55 optim !
  { list *Result ;
    { ClaireBoolean * g0553I;
      { OID  g0554UU;
        if (INHERIT(OWNER(x),Language._Call))
         g0554UU = _oid_(((OBJECT(Call,x)->selector == Kernel.nth) ? (((*(OBJECT(Call,x)->args))[1] == _oid_(Kernel._type)) ? CTRUE: CFALSE): CFALSE));
        else g0554UU = Kernel.cfalse;
          g0553I = not_any(g0554UU);
        }
      
      if (g0553I == CTRUE) Result = list::alloc(2,GC_OID(_oid_(extract_type_any(x))),_oid_(Kernel.emptySet));
        else { { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v);
          for (START(ldef); NEXT(v);)
          { GC_LOOP;
            { Reference * r = GC_OBJECT(Reference,OBJECT(Reference,(*Kernel.range)(v)));
              list * path = GC_OBJECT(list,r->args);
              CL_INT  n = path->length;
              OID  y = (*(lvar))[((CL_INT)r->index+(CL_INT)1)];
              { CL_INT  i = 1;
                CL_INT  g0552 = path->length;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  while (((CL_INT)i <= (CL_INT)g0552))
                  { GC_LOOP;
                    { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        (_CL_obj->selector = Core._at);
                        (_CL_obj->args = list::alloc(2,y,(*(path))[i]));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                        y = _oid_(_CL_obj);
                        }
                       GC__OID(y, 9);}
                    ++i;
                    GC_UNLOOP;POP_SIGNAL;}
                  }
                }
              { { OID  g0555UU;
                  { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (_CL_obj->selector = Core.member);
                    (_CL_obj->args = list::alloc(1,y));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                    g0555UU = _oid_(_CL_obj);
                    }
                  x = substitution_any(x,OBJECT(Variable,v),g0555UU);
                  }
                 GC__OID(x, 1);}
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        { list * lv2 = GC_OBJECT(list,list::empty(Kernel._any));
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v);
            for (START(lvar); NEXT(v);)
            { GC_LOOP;
              { Variable * v2;
                { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                    (_CL_obj->pname = OBJECT(Variable,v)->pname);
                    (_CL_obj->range = Kernel._type);
                    add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                    v2 = _CL_obj;
                    }
                  GC_OBJECT(Variable,v2);}
                lv2= lv2->addFast((OID)_oid_(v2));
                GC__OID(x = substitution_any(x,OBJECT(Variable,v),_oid_(v2)), 1);
                }
              GC_UNLOOP; POP_SIGNAL;}
            }
          { lambda * lb = GC_OBJECT(lambda,lambda_I_list(lv2,GC_OID((*(OBJECT(bag,(*Core.args)(x))))[2])));
            OID  ur = CNULL;
            { ClaireHandler c_handle = ClaireHandler();
              if ERROR_IN 
              { { { list * g0556UU;
                    { { CL_INT loop_handle = ClEnv->cHandle;
                        bag *v_list; OID v_val;
                        OID v; CL_INT CLcount;
                        v_list = lvar;
                         g0556UU = v_list->clone();
                        for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                        { v = (*(v_list))[CLcount];
                          v_val = (*Kernel.range)(v);
                          
                          (*((list *) g0556UU))[CLcount] = v_val;}
                        }
                      GC_OBJECT(list,g0556UU);}
                    ur = apply_lambda(lb,g0556UU);
                    }
                  GC_OID(ur);}
                ERROR_FREE;}
              else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
              { c_handle.catchIt();{ princ_string("The type expression ");
                  print_any(x);
                  princ_string(" is not a valid because\n");
                  princ_string("lambda = ");
                  print_any(_oid_(lb));
                  princ_string(", l = ");
                  { OID  g0557UU;
                    { { list * V_CL0558;{ CL_INT loop_handle = ClEnv->cHandle;
                          bag *v_list; OID v_val;
                          OID v; CL_INT CLcount;
                          v_list = lvar;
                           V_CL0558 = v_list->clone();
                          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                          { v = (*(v_list))[CLcount];
                            v_val = (*Kernel.range)(v);
                            
                            (*((list *) V_CL0558))[CLcount] = v_val;}
                          }
                        
                        g0557UU=_oid_(V_CL0558);}
                      GC_OID(g0557UU);}
                    print_any(g0557UU);
                    }
                  princ_string("\n");
                  close_exception(ClEnv->exception_I);
                  }
                }
              else PREVIOUS_HANDLER;}
            if (inherit_ask_class(OWNER(ur),Kernel._type) != CTRUE)
             close_exception(((general_error *) (*Core._general_error)(_string_("[115] the (resulting) range ~S is not a type"),
              _oid_(list::alloc(1,ur)))));
            Result = list::alloc(2,ur,_oid_(lb));
            }
          }
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// define the different components of status(m), which is a bit vector
// a new allocation may be done by running the method
// a list is updated whose content is not gcsafe
// an slot is updated whose content is not gcsafe
// the method returns one of its args
// the result (not gcsafe) does not need protection
// the result (not gcsafe) does not need protection
// create a bitvector from a list of flags
// The c++ function for: bit_vector(l:listargs) [0]
int  bit_vector_listargs2(listargs *l)
{ { CL_INT Result = 0;
    { CL_INT  d = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(x);
        for (START(l); NEXT(x);)
        d= ((CL_INT)d+(CL_INT)exp2_integer(x));
        }
      Result = d;
      }
    POP_SIGNAL; return (Result);}
  }


// parse the body and return (status, functional, body)
// the input is  body | (function!(f) | function!(f,s)) < | body> opt
//
// The c++ function for: iClaire/extract_status(x:any) [NEW_ALLOC]
list * extract_status_any(OID x)
{ GC_BIND;
  { list *Result ;
    { OID  s = CNULL;
      OID  f;
      if ((INHERIT(OWNER(x),Language._Call)) && (OBJECT(Call,x)->selector == Language.function_I))
       f = x;
      else f = CNULL;
        if (INHERIT(OWNER(x),Language._And))
       { OID  y = (*(OBJECT(And,x)->args))[1];
        if ((INHERIT(OWNER(y),Language._Call)) && (OBJECT(Call,y)->selector == Language.function_I))
         { f= y;
          x= (*(OBJECT(And,x)->args))[2];
          }
        }
      else if (INHERIT(OWNER(x),Language._Call))
       { if (OBJECT(Call,x)->selector == Language.function_I)
         x= _oid_(Kernel.body);
        }
      else ;if (f != CNULL)
       { x= _oid_(Kernel.body);
        if ((CL_INT)length_bag(OBJECT(bag,(*Core.args)(f))) > 1)
         { CL_INT  V_CL0559;{ set * g0560UU;
            { set * u_bag = set::empty(Kernel.emptySet);
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(u);
                bag *u_support;
                u_support = GC_OBJECT(list,cdr_list(GC_OBJECT(list,OBJECT(list,(*Core.args)(f)))));
                for (START(u_support); NEXT(u);)
                { GC_LOOP;
                  { OID  g0561UU;
                    { if (INHERIT(OWNER(u),Kernel._integer))
                       g0561UU = ((OID)u);
                      else if (INHERIT(OWNER(u),Core._global_variable))
                       g0561UU = OBJECT(global_variable,u)->value;
                      else { OID  V_CL0562;close_exception(((general_error *) (*Core._general_error)(_string_("[116] ~S not allowed in function!"),
                            _oid_(list::alloc(1,u)))));
                          
                          g0561UU=_void_(V_CL0562);}
                        GC_OID(g0561UU);}
                    u_bag->addFast((OID)g0561UU);
                    }
                  GC_UNLOOP; POP_SIGNAL;}
                }
              g0560UU = GC_OBJECT(set,u_bag);
              }
            V_CL0559 = integer_I_set(g0560UU);
            }
          
          s=((OID)V_CL0559);}
        else s= ((OID)0);
          f= _oid_(make_function_string(string_I_symbol(extract_symbol_any((*(OBJECT(bag,(*Core.args)(f))))[1]))));
        }
      Result = list::alloc(3,s,
        f,
        x);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// cleans a pattern into a type
//
// The c++ function for: iClaire/type!(x:any) [NEW_ALLOC+RETURN_ARG]
ClaireType * type_I_any(OID x)
{ GC_BIND;
  { ClaireType *Result ;
    if (INHERIT(OWNER(x),Kernel._list))
     { CL_INT loop_handle = ClEnv->cHandle;
      bag *v_list; OID v_val;
      OID y; CL_INT CLcount;
      v_list = OBJECT(bag,x);
       Result = v_list->clone();
      for (CLcount= 1; CLcount <= v_list->length; CLcount++)
      { y = (*(v_list))[CLcount];
        v_val = _oid_(type_I_any(y));
        
        (*((list *) Result))[CLcount] = v_val;}
      }
    else if (INHERIT(OWNER(x),Core._Param))
     { Param * _CL_obj = ((Param *) GC_OBJECT(Param,new_object_class(Core._Param)));
      (_CL_obj->arg = OBJECT(Param,x)->arg);
      (_CL_obj->params = OBJECT(Param,x)->params);
      { Param * g0563 = _CL_obj; 
        list * g0564;
        { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID y; CL_INT CLcount;
          v_list = GC_OBJECT(list,OBJECT(Param,x)->args);
           g0564 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { y = (*(v_list))[CLcount];
            v_val = _oid_(type_I_any(y));
            
            (*((list *) g0564))[CLcount] = v_val;}
          }
        (g0563->args = g0564);}
      Result = _CL_obj;
      }
    else if (INHERIT(OWNER(x),Core._Reference))
     Result = Kernel._any;
    else Result = OBJECT(ClaireType,x);
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// creates a table
// to do in later versions: use an array if direct indexed access
// in the meanwhile, arrays of float should be used with care (indexed arrays)
//
// The c++ function for: self_eval(self:Defarray) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_eval_Defarray(Defarray *self)
{ GC_BIND;
  { OID Result = 0;
    { list * a = GC_OBJECT(list,self->arg->args);
      table * ar = ((table *) new_thing_class(Kernel._table,extract_symbol_any((*(a))[1])));
      Variable * v = OBJECT(Variable,(*(a))[2]);
      ClaireType * s = GC_OBJECT(ClaireType,extract_type_any(GC_OID(_oid_(v->range))));
      OID  e;
      { { list * l = GC_OBJECT(list,cdr_list(a));
          OID  b = GC_OID(lexical_build_any(GC_OID(self->body),l,0));
          { ClaireBoolean * g0565I;
            { OID  g0566UU;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(va);
                g0566UU= Kernel.cfalse;
                for (START(l); NEXT(va);)
                if ((CL_INT)(*Kernel.occurrence)(b,
                  va) > 0)
                 { g0566UU = Kernel.ctrue;
                  ClEnv->cHandle = loop_handle;break;}
                }
              g0565I = boolean_I_any(g0566UU);
              }
            
            if (g0565I == CTRUE) e = _oid_(lambda_I_list(l,b));
              else e = self->body;
            }
          }
        GC_OID(e);}
      OID  d;
      { if (INHERIT(OWNER(e),Core._lambda))
         d = CNULL;
        else d = eval_any(GC_OID(self->body));
          GC_OID(d);}
      update_property(Kernel.range,
        ar,
        5,
        Kernel._object,
        GC_OID(extract_pattern_any(GC_OID(self->set_arg),Kernel.nil)));
      if (ar->range == (NULL))
       close_exception(((range_error *) (*Core._range_error)(_oid_(Kernel._table),
        GC_OID(self->set_arg),
        _oid_(Kernel._type))));
      if ((d != CNULL) && 
          (belong_to(d,_oid_(ar->range)) != CTRUE))
       close_exception(((range_error *) (*Core._range_error)(_oid_(ar),
        d,
        _oid_(ar->range))));
      (v->range = s);
      attach_comment_any(_oid_(ar));
      if (INHERIT(class_I_type(ar->range),Kernel._set))
       (ar->multivalued_ask = CTRUE);
      else if ((INHERIT(class_I_type(ar->range),Kernel._list)) && 
          (inherit_ask_class(ar->range->isa,Language._Tuple) != CTRUE))
       (ar->multivalued_ask = Kernel._list);
      if (a->length == 2)
       { (ar->domain = s);
        if (INHERIT(s->isa,Core._Interval))
         { (ar->params = ((OID)((CL_INT)CLREAD(Interval,s,arg1)-(CL_INT)1)));
          (ar->graph = make_copy_list_integer(size_Interval(((Interval *) s)),d));
          }
        else { (ar->params = _oid_(Kernel._any));
            (ar->graph = make_list_integer(29,CNULL));
            }
          if (INHERIT(OWNER(e),Core._lambda))
         { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(y);
          bag *y_support;
          y_support = GC_OBJECT(bag,enumerate_any(_oid_(ar->domain)));
          for (START(y_support); NEXT(y);)
          { GC_LOOP;
            nth_equal_table1(ar,y,GC_OID(funcall_lambda1(OBJECT(lambda,e),y)));
            GC_UNLOOP; POP_SIGNAL;}
          }
        else (ar->DEFAULT = d);
          }
      else { ClaireType * s2 = GC_OBJECT(ClaireType,extract_type_any(GC_OID(_oid_(OBJECT(Variable,(*(a))[3])->range))));
          (ar->domain = tuple_I_list(GC_OBJECT(list,list::alloc(2,_oid_(s),_oid_(s2)))));
          (OBJECT(Variable,(*(a))[3])->range = s2);
          if ((INHERIT(s->isa,Core._Interval)) && 
              (INHERIT(s2->isa,Core._Interval)))
           { (ar->params = _oid_(list::alloc(2,Core.size->fcall(((CL_INT) s2)),((OID)((CL_INT)((CL_INT)((CL_INT)CLREAD(Interval,s,arg1)*(CL_INT)(Core.size->fcall(((CL_INT) s2))))+(CL_INT)CLREAD(Interval,s2,arg1))-(CL_INT)1)))));
            (ar->graph = make_copy_list_integer(((CL_INT)(Core.size->fcall(((CL_INT) s)))*(CL_INT)(Core.size->fcall(((CL_INT) s2)))),d));
            }
          else { (ar->params = _oid_(Kernel._any));
              (ar->graph = make_list_integer(29,CNULL));
              }
            if (INHERIT(OWNER(e),Core._lambda))
           { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(y1);
            bag *y1_support;
            y1_support = GC_OBJECT(bag,enumerate_any(_oid_(s)));
            for (START(y1_support); NEXT(y1);)
            { GC_LOOP;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(y2);
                bag *y2_support;
                y2_support = GC_OBJECT(bag,enumerate_any(_oid_(s2)));
                for (START(y2_support); NEXT(y2);)
                { GC_LOOP;
                  nth_equal_table2(ar,y1,y2,GC_OID((*Kernel.funcall)(e,
                    y1,
                    y2)));
                  GC_UNLOOP; POP_SIGNAL;}
                }
              GC_UNLOOP; POP_SIGNAL;}
            }
          else (ar->DEFAULT = d);
            }
        Result = _oid_(ar);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// ------------------ NEW in v3.2 : definition of rules -----------------------
//
// a demon is a lambda with a name and a priority
// The c++ function for: self_print(self:demon) [0]
void  self_print_demon(Language_demon *self)
{ princ_symbol(self->pname);
  POP_SIGNAL;}


// The c++ function for: funcall(self:demon,x:any,y:any) [NEW_ALLOC]
OID  funcall_demon1(Language_demon *self,OID x,OID y)
{ GC_BIND;
  { OID Result = 0;
    Result = (*Kernel.funcall)(GC_OID(_oid_(self->formula)),
      x,
      y);
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: funcall(self:demon,x:any,y:any,z:any) [NEW_ALLOC]
OID  funcall_demon2(Language_demon *self,OID x,OID y,OID z)
{ GC_BIND;
  { OID Result = 0;
    Result = (*Kernel.funcall)(GC_OID(_oid_(self->formula)),
      x,
      y,
      z);
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// in the interpreted mode we store the list of demons using a table
// list of relevant demons
// the last rule/axiom that was defined on each relation
// this is used to find when the relation may be compiled
// list of involved relations
// compile(ru) => may compile(r)
// evaluate a rule definition: create a new demon and, if needed, the if_write 
// function
// The c++ function for: self_eval(self:Defrule) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_eval_Defrule(Defrule *self)
{ GC_BIND;
  { OID Result = 0;
    if ((*(self->args))[1] != _oid_(ClEnv))
     Result = (*Language.eval_rule)(_oid_(self));
    else { OID  _Zcondition = GC_OID(self->arg);
        OID  ru = get_symbol(self->ident);
        (OBJECT(ClaireObject,ru)->isa = Language._rule_object);
        add_I_property(Kernel.instances,Language._rule_object,11,ru);
        { tuple * g0568 = make_filter_any(_Zcondition);
          OID  R = (*(g0568))[1];
          OID  lvar = GC_OID((*(g0568))[2]);
          Language_demon * d = make_demon_relation(OBJECT(ClaireRelation,R),
            OBJECT(symbol,(*Kernel.name)(ru)),
            OBJECT(list,lvar),
            _Zcondition,
            GC_OID(lexical_build_any(GC_OID(self->body),OBJECT(list,lvar),0)));
          if (INHERIT(OWNER(OBJECT(ClaireRelation,R)->if_write),Kernel._function))
           close_exception(((general_error *) (*Core._general_error)(_string_("cannot define a new rule on ~S which is closed"),
            _oid_(list::alloc(1,R)))));
          add_table(Language.demons,R,_oid_(d));
          nth_put_table(Language.last_rule,R,ru);
          if (length_bag(OBJECT(bag,nth_table1(Language.demons,R))) == 1)
           eval_if_write_relation(OBJECT(ClaireRelation,R));
          if ((INHERIT(OBJECT(ClaireObject,R)->isa,Kernel._property)) && (OBJECT(property,R)->restrictions->length == 0))
           eventMethod_property(OBJECT(property,R));
          Result = ru;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// an eventMethod is a property whose unique (?) restriction is a method
// The c++ function for: eventMethod?(r:relation) [0]
ClaireBoolean * eventMethod_ask_relation2(ClaireRelation *r)
{ { ClaireBoolean *Result ;
    if (INHERIT(r->isa,Kernel._property))
     { OID  g0570UU;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(x);
        g0570UU= Kernel.cfalse;
        for (START(CLREAD(property,r,restrictions)); NEXT(x);)
        if (not_any(_oid_(equal(_oid_(Kernel._slot),_oid_(OBJECT(ClaireObject,x)->isa)))) != CTRUE)
         { g0570UU = Kernel.ctrue;
          ClEnv->cHandle = loop_handle;break;}
        }
      Result = not_any(g0570UU);
      }
    else Result = CFALSE;
      POP_SIGNAL; return (Result);}
  }


// check that condition is either a filter or the conjunction of a filter and a 
// condition
// a filter is R(x) := y | R(x) := (y <- z) | R(x) :add y | P(x,y)
// R(x) is x.r or A[x]
// the list of variable is of length 3 if R is mono-valued
// The c++ function for: make_filter(g0571:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
tuple * make_filter_any_(OID g0571)
{ return make_filter_any(g0571)->copyIfNeeded();}


// The c++ function for: make_filter(cond:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
tuple * make_filter_any(OID cond)
{ GC_BIND;
  { tuple *Result ;
    { ClaireObject *V_CC ;
      { OID  c;
        { if (INHERIT(OWNER(cond),Language._And))
           c = (*(OBJECT(And,cond)->args))[1];
          else c = cond;
            GC_OID(c);}
        if (should_trace_ask_module1(Language.it,5) == CTRUE)
         mtformat_module1(Language.it,"make_filter : ~S (~S) \n",5,list::alloc(2,c,_oid_(OBJECT(ClaireObject,c)->isa)));
        else ;if ((INHERIT(OWNER(c),Language._Call)) && (((OBJECT(Call,c)->selector == Core.write) || 
              (OBJECT(Call,c)->selector == Kernel.nth_equal)) && 
            (INHERIT(OWNER((*(OBJECT(Call,c)->args))[1]),Kernel._relation))))
         { ClaireRelation * R = OBJECT(ClaireRelation,(*(OBJECT(bag,(*Core.args)(c))))[1]);
          Variable * x;
          { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              (_CL_obj->pname = extract_symbol_any((*(OBJECT(bag,(*Core.args)(c))))[2]));
              (_CL_obj->range = R->domain);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              x = _CL_obj;
              }
            GC_OBJECT(Variable,x);}
          OID  y1 = GC_OID((*(OBJECT(bag,(*Core.args)(c))))[3]);
          if (multi_ask_any(_oid_(R)) == CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_("[188] wrong event filter ~S for multi-valued relation"),
            _oid_(list::alloc(2,c,_oid_(R))))));
          if ((INHERIT(OWNER(y1),Language._Call)) && (OBJECT(Call,y1)->selector == Language._inf_dash))
           { OID v_bag;
            GC_ANY(V_CC= tuple::empty());
            ((tuple *) V_CC)->addFast((OID)_oid_(R));
            { list * V_CL0572;{ OID v_bag;
                GC_ANY(V_CL0572= list::empty(Kernel.emptySet));
                ((list *) V_CL0572)->addFast((OID)_oid_(x));
                { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                    (_CL_obj->pname = extract_symbol_any((*(OBJECT(bag,(*Core.args)(y1))))[1]));
                    (_CL_obj->range = R->range);
                    add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                    v_bag = _oid_(_CL_obj);
                    }
                  GC_OID(v_bag);}
                ((list *) V_CL0572)->addFast((OID)v_bag);
                { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                    (_CL_obj->pname = extract_symbol_any((*(OBJECT(bag,(*Core.args)(y1))))[2]));
                    (_CL_obj->range = R->range);
                    add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                    v_bag = _oid_(_CL_obj);
                    }
                  GC_OID(v_bag);}
                ((list *) V_CL0572)->addFast((OID)v_bag);}
              
              v_bag=_oid_(V_CL0572);}
            ((tuple *) V_CC)->addFast((OID)v_bag);}
          else { OID v_bag;
              GC_ANY(V_CC= tuple::empty());
              ((tuple *) V_CC)->addFast((OID)_oid_(R));
              { list * V_CL0573;{ OID v_bag;
                  GC_ANY(V_CL0573= list::empty(Kernel.emptySet));
                  ((list *) V_CL0573)->addFast((OID)_oid_(x));
                  { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                      (_CL_obj->pname = extract_symbol_any(y1));
                      (_CL_obj->range = safeRange_relation(R));
                      add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                      v_bag = _oid_(_CL_obj);
                      }
                    GC_OID(v_bag);}
                  ((list *) V_CL0573)->addFast((OID)v_bag);
                  { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                      (_CL_obj->pname = gensym_void());
                      (_CL_obj->range = safeRange_relation(R));
                      add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                      v_bag = _oid_(_CL_obj);
                      }
                    GC_OID(v_bag);}
                  ((list *) V_CL0573)->addFast((OID)v_bag);}
                
                v_bag=_oid_(V_CL0573);}
              ((tuple *) V_CC)->addFast((OID)v_bag);}
            }
        else if ((INHERIT(OWNER(c),Language._Call)) && ((OBJECT(Call,c)->selector == Kernel.add) && 
            (INHERIT(OWNER((*(OBJECT(Call,c)->args))[1]),Kernel._relation))))
         { ClaireRelation * R = OBJECT(ClaireRelation,(*(OBJECT(bag,(*Core.args)(c))))[1]);
          Variable * x;
          { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              (_CL_obj->pname = extract_symbol_any((*(OBJECT(bag,(*Core.args)(c))))[2]));
              (_CL_obj->range = R->domain);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              x = _CL_obj;
              }
            GC_OBJECT(Variable,x);}
          Variable * y;
          { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              (_CL_obj->pname = extract_symbol_any((*(OBJECT(bag,(*Core.args)(c))))[3]));
              (_CL_obj->range = R->range);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              y = _CL_obj;
              }
            GC_OBJECT(Variable,y);}
          V_CC = tuple::alloc(2,_oid_(R),_oid_(list::alloc(2,_oid_(x),_oid_(y))));
          }
        else if ((INHERIT(OWNER(c),Language._Call)) && (OBJECT(Call,c)->args->length == 2))
         { property * R = OBJECT(Call,c)->selector;
          Variable * x;
          { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              (_CL_obj->pname = extract_symbol_any((*(OBJECT(bag,(*Core.args)(c))))[1]));
              (_CL_obj->range = R->domain);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              x = _CL_obj;
              }
            GC_OBJECT(Variable,x);}
          Variable * y;
          { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              (_CL_obj->pname = extract_symbol_any((*(OBJECT(bag,(*Core.args)(c))))[2]));
              (_CL_obj->range = R->range);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              y = _CL_obj;
              }
            GC_OBJECT(Variable,y);}
          V_CC = tuple::alloc(2,_oid_(R),_oid_(list::alloc(2,_oid_(x),_oid_(y))));
          }
        else close_exception(((general_error *) (*Core._general_error)(_string_("[188] wrong event filter: ~S"),
            _oid_(list::alloc(1,c)))));
          }
      Result= (tuple *) V_CC;}
    GC_UNBIND; return (Result);}
  }


// create a demon
// notice that a demon has 3 args if R is monovalued 
// The c++ function for: make_demon(R:relation,n:symbol,lvar:list[Variable],cond:any,conc:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
Language_demon * make_demon_relation(ClaireRelation *R,symbol *n,list *lvar,OID cond,OID conc)
{ GC_BIND;
  { Language_demon *Result ;
    { OID  x = (*(lvar))[1];
      OID  y = (*(lvar))[2];
      OID  _Ztest;
      { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          (_CL_obj->selector = ((multi_ask_any(_oid_(R)) == CTRUE) ?
            Kernel._Z :
            Kernel._equal ));
          (_CL_obj->args = list::alloc(2,y,GC_OID(_oid_(readCall_relation(R,x)))));
          add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
          _Ztest = _oid_(_CL_obj);
          }
        GC_OID(_Ztest);}
      OID  _Zbody = conc;
      if ((CL_INT)Kernel.if_write->trace_I > (CL_INT)ClEnv->verbose)
       { { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
          { Do * g0574 = _CL_obj; 
            list * g0575;
            { OID v_bag;
              GC_ANY(g0575= list::empty(Kernel.emptySet));
              { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  (_CL_obj->selector = Core.format);
                  { Call * g0576 = _CL_obj; 
                    list * g0577;
                    { OID v_bag;
                      GC_ANY(g0577= list::empty(Kernel.emptySet));
                      ((list *) g0577)->addFast((OID)_string_("--- trigger ~A(~S,~S)\n"));
                      { { List * _CL_obj = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                          (_CL_obj->args = list::alloc(3,_string_(string_I_symbol(n)),
                            x,
                            y));
                          add_I_property(Kernel.instances,Language._List,11,_oid_(_CL_obj));
                          v_bag = _oid_(_CL_obj);
                          }
                        GC_OID(v_bag);}
                      ((list *) g0577)->addFast((OID)v_bag);}
                    (g0576->args = g0577);}
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                  v_bag = _oid_(_CL_obj);
                  }
                GC_OID(v_bag);}
              ((list *) g0575)->addFast((OID)v_bag);
              ((list *) g0575)->addFast((OID)conc);}
            (g0574->args = g0575);}
          add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
          conc = _oid_(_CL_obj);
          }
        GC_OID(conc);}
      { { If * _CL_obj = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
          (_CL_obj->arg = conc);
          add_I_property(Kernel.instances,Language._If,11,_oid_(_CL_obj));
          (_CL_obj->other = Kernel.cfalse);
          _Zbody = _oid_(_CL_obj);
          }
        GC_OID(_Zbody);}
      if (eventMethod_ask_relation2(R) == CTRUE)
       { if (INHERIT(OWNER(cond),Language._And))
         { if ((CL_INT)OBJECT(And,cond)->args->length > 2)
           { And * _CL_obj = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
            (_CL_obj->args = cdr_list(GC_OBJECT(list,OBJECT(And,cond)->args)));
            add_I_property(Kernel.instances,Language._And,11,_oid_(_CL_obj));
            _Ztest = _oid_(_CL_obj);
            }
          else _Ztest = (*(OBJECT(And,cond)->args))[2];
            GC_OID(_Ztest);}
        else _Zbody= conc;
          }
      else if (INHERIT(OWNER(cond),Language._And))
       { { And * _CL_obj = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
          (_CL_obj->args = append_list(list::alloc(1,_Ztest),GC_OBJECT(list,cdr_list(GC_OBJECT(list,OBJECT(And,cond)->args)))));
          add_I_property(Kernel.instances,Language._And,11,_oid_(_CL_obj));
          _Ztest = _oid_(_CL_obj);
          }
        GC_OID(_Ztest);}
      if (INHERIT(OWNER(_Zbody),Language._If))
       (OBJECT(If,_Zbody)->test = _Ztest);
      { Language_demon * _CL_obj = ((Language_demon *) GC_OBJECT(Language_demon,new_object_class(Language._demon)));
        (_CL_obj->pname = n);
        (_CL_obj->formula = lambda_I_list(lvar,_Zbody));
        add_I_property(Kernel.instances,Language._demon,11,_oid_(_CL_obj));
        Result = _CL_obj;
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// cute litle guy
// The c++ function for: readCall(R:relation,x:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
Call * readCall_relation(ClaireRelation *R,OID x)
{ GC_BIND;
  { Call *Result ;
    if (INHERIT(R->isa,Kernel._table))
     { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
      (_CL_obj->selector = Kernel.get);
      (_CL_obj->args = list::alloc(2,_oid_(R),x));
      add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
      Result = _CL_obj;
      }
    else { Call_plus * _CL_obj = ((Call_plus *) GC_OBJECT(Call_plus,new_object_class(Language._Call_plus)));
        (_CL_obj->selector = ((property *) R));
        (_CL_obj->args = list::alloc(1,x));
        add_I_property(Kernel.instances,Language._Call_plus,11,_oid_(_CL_obj));
        Result = _CL_obj;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// a small brother
// The c++ function for: putCall(R:relation,x:any,y:any) [NEW_ALLOC]
Call * putCall_relation2(ClaireRelation *R,OID x,OID y)
{ GC_BIND;
  { Call *Result ;
    if (multi_ask_any(_oid_(R)) == CTRUE)
     { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
      (_CL_obj->selector = Core.add_value);
      (_CL_obj->args = list::alloc(3,_oid_(R),
        x,
        y));
      add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
      Result = _CL_obj;
      }
    else { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
        (_CL_obj->selector = Kernel.put);
        (_CL_obj->args = list::alloc(3,_oid_(R),
          x,
          y));
        add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
        Result = _CL_obj;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// v3.3 : find the range when we read the current value     
// The c++ function for: safeRange(x:relation) [RETURN_ARG]
ClaireType * safeRange_relation(ClaireRelation *x)
{ { ClaireType *Result ;
    if (INHERIT(x->isa,Kernel._property))
     { { ClaireBoolean * g0578I;
        { OID  g0579UU;
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(s);
            g0579UU= Kernel.cfalse;
            for (START(CLREAD(property,x,restrictions)); NEXT(s);)
            { ClaireBoolean * g0580I;
              { OID  g0581UU;
                { ClaireBoolean * V_CL0582;{ OID  g0583UU;
                    if (Kernel._slot == OBJECT(ClaireObject,s)->isa)
                     g0583UU = _oid_(belong_to(OBJECT(slot,s)->DEFAULT,_oid_(OBJECT(restriction,s)->range)));
                    else g0583UU = Kernel.cfalse;
                      V_CL0582 = boolean_I_any(g0583UU);
                    }
                  
                  g0581UU=_oid_(V_CL0582);}
                g0580I = ((g0581UU != Kernel.ctrue) ? CTRUE : CFALSE);
                }
              
              if (g0580I == CTRUE) { g0579UU = Kernel.ctrue;
                  ClEnv->cHandle = loop_handle;break;}
                }
            }
          g0578I = not_any(g0579UU);
          }
        
        if (g0578I == CTRUE) Result = x->range;
          else Result = Kernel._any;
        }
      }
    else if (INHERIT(x->isa,Kernel._table))
     { if (belong_to(CLREAD(table,x,DEFAULT),_oid_(x->range)) == CTRUE)
       Result = x->range;
      else Result = Kernel._any;
        }
    else Result = Kernel._any;
      POP_SIGNAL; return (Result);}
  }


// generate an if_write "daemon", only the first time, which uses
// the list in demons[R]
// the first step is to make the update (with inverse management)
// The c++ function for: eval_if_write(R:relation) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  eval_if_write_relation(ClaireRelation *R)
{ GC_BIND;
  { OID  l = nth_table1(Language.demons,_oid_(R));
    list * lvar = GC_OBJECT(list,OBJECT(Language_demon,(*(OBJECT(bag,l)))[1])->formula->vars);
    Variable * dv;
    { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
        (_CL_obj->pname = gensym_void());
        (_CL_obj->range = Language._demon);
        add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
        dv = _CL_obj;
        }
      GC_OBJECT(Variable,dv);}
    list * l1 = list::alloc(Kernel._any,1,GC_OID(_oid_(putCall_relation2(R,(*(lvar))[1],(*(lvar))[2]))));
    list * l2;
    { OID v_bag;
      GC_ANY(l2= list::empty(Kernel._any));
      { { For * _CL_obj = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
          (_CL_obj->var = dv);
          { Iteration * g0584 = _CL_obj; 
            OID  g0585;
            { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (_CL_obj->selector = Kernel.nth);
              (_CL_obj->args = list::alloc(2,_oid_(Language.demons),_oid_(R)));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
              g0585 = _oid_(_CL_obj);
              }
            (g0584->set_arg = g0585);}
          { Iteration * g0586 = _CL_obj; 
            OID  g0587;
            { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (_CL_obj->selector = Kernel.funcall);
              (_CL_obj->args = append_list(list::alloc(1,_oid_(dv)),lvar));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
              g0587 = _oid_(_CL_obj);
              }
            (g0586->arg = g0587);}
          add_I_property(Kernel.instances,Language._For,11,_oid_(_CL_obj));
          v_bag = _oid_(_CL_obj);
          }
        GC_OID(v_bag);}
      ((list *) l2)->addFast((OID)v_bag);}
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v);
      for (START(lvar); NEXT(v);)
      { GC_LOOP;
        put_property2(Kernel.range,OBJECT(ClaireObject,v),_oid_(class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(v))))));
        GC_UNLOOP; POP_SIGNAL;}
      }
    if (((R->inverse == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     { if (multi_ask_any(_oid_(R)) != CTRUE)
       { OID  g0588UU;
        { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          (_CL_obj->selector = Core.update_dash);
          (_CL_obj->args = list::alloc(3,_oid_(R->inverse),
            (*(lvar))[3],
            (*(lvar))[1]));
          add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
          g0588UU = _oid_(_CL_obj);
          }
        l1 = l1->addFast((OID)g0588UU);
        }
      l1= l1->addFast((OID)GC_OID(_oid_(putCall_relation2(R->inverse,(*(lvar))[2],(*(lvar))[1]))));
      }
    { ClaireRelation * g0589 = R; 
      OID  g0590;
      { lambda * V_CL0591;{ OID  g0592UU;
          if (eventMethod_ask_relation2(R) == CTRUE)
           { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            (_CL_obj->args = l2);
            add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
            g0592UU = _oid_(_CL_obj);
            }
          else if (multi_ask_any(_oid_(R)) == CTRUE)
           { If * _CL_obj = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
            { If * g0593 = _CL_obj; 
              OID  g0594;
              { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                (_CL_obj->selector = Core.NOT);
                { Call * g0595 = _CL_obj; 
                  list * g0596;
                  { OID v_bag;
                    GC_ANY(g0596= list::empty(Kernel.emptySet));
                    { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        (_CL_obj->selector = Kernel._Z);
                        (_CL_obj->args = list::alloc(2,(*(lvar))[2],GC_OID(_oid_(readCall_relation(R,(*(lvar))[1])))));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                        v_bag = _oid_(_CL_obj);
                        }
                      GC_OID(v_bag);}
                    ((list *) g0596)->addFast((OID)v_bag);}
                  (g0595->args = g0596);}
                add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                g0594 = _oid_(_CL_obj);
                }
              (g0593->test = g0594);}
            { If * g0597 = _CL_obj; 
              OID  g0598;
              { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                (_CL_obj->args = append_list(l1,l2));
                add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
                g0598 = _oid_(_CL_obj);
                }
              (g0597->arg = g0598);}
            add_I_property(Kernel.instances,Language._If,11,_oid_(_CL_obj));
            (_CL_obj->other = Kernel.cfalse);
            g0592UU = _oid_(_CL_obj);
            }
          else { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
              store_object(_CL_obj,
                2,
                Kernel._object,
                (*(lvar))[3],
                CFALSE);
              (_CL_obj->value = _oid_(readCall_relation(R,(*(lvar))[1])));
              { Let * g0599 = _CL_obj; 
                OID  g0600;
                { If * _CL_obj = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                  { If * g0601 = _CL_obj; 
                    OID  g0602;
                    { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      (_CL_obj->selector = Core._I_equal);
                      (_CL_obj->args = list::alloc(2,(*(lvar))[2],(*(lvar))[3]));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                      g0602 = _oid_(_CL_obj);
                      }
                    (g0601->test = g0602);}
                  { If * g0603 = _CL_obj; 
                    OID  g0604;
                    { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                      (_CL_obj->args = append_list(l1,l2));
                      add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
                      g0604 = _oid_(_CL_obj);
                      }
                    (g0603->arg = g0604);}
                  add_I_property(Kernel.instances,Language._If,11,_oid_(_CL_obj));
                  (_CL_obj->other = Kernel.cfalse);
                  g0600 = _oid_(_CL_obj);
                  }
                (g0599->arg = g0600);}
              add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
              g0592UU = _oid_(_CL_obj);
              }
            V_CL0591 = lambda_I_list(GC_OBJECT(list,list::alloc(2,(*(lvar))[1],(*(lvar))[2])),g0592UU);
          }
        
        g0590=_oid_(V_CL0591);}
      (g0589->if_write = g0590);}
    }
  GC_UNBIND; POP_SIGNAL;}


// create a restriction (method) that will trigger an event
// The c++ function for: eventMethod(p:property) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  eventMethod_property(property *p)
{ { method * m = add_method_property(p,
      list::alloc(2,_oid_(p->domain),_oid_(p->range)),
      Kernel._void,
      ((OID)0),
      CNULL);
    store_object(m,
      8,
      Kernel._object,
      p->if_write,
      CFALSE);
    (m->functional = make_function_string(append_string(string_I_symbol(p->name),"_write")));
    }
  POP_SIGNAL;}


// new in v3.1: the inter face pragma ******************************
// this array is used to store the declarations
// define a property as an interface
// The c++ function for: interface(p:property) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  interface_property(property *p)
{ if (boolean_I_any(_oid_(p->restrictions)) != CTRUE)
   close_exception(((general_error *) (*Core._general_error)(_string_("[185] cannot define an empty property ~S as an interface"),
    _oid_(list::alloc(1,_oid_(p))))));
  if ((uniform_property(p) != CTRUE) || 
      (OBJECT(restriction,(*(p->restrictions))[1])->domain->memq(_oid_(Kernel._float)) == CTRUE))
   close_exception(((general_error *) (*Core._general_error)(_string_("[185] cannot define an non-uniform property ~S as an interface"),
    _oid_(list::alloc(1,_oid_(p))))));
  { ClaireClass * d = domain_I_restriction(OBJECT(restriction,(*(p->restrictions))[1]));
    list * ls = list::empty(Kernel._any);
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(g0605);
      bag *g0605_support;
      g0605_support = Kernel._property->descendents;
      for (START(g0605_support); NEXT(g0605);)
      { ClaireBoolean * g0606;
        { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(p2);
            V_C= Kernel.cfalse;
            for (START(OBJECT(ClaireClass,g0605)->instances); NEXT(p2);)
            if (((CL_INT)OBJECT(property,p2)->dispatcher > 0) && 
                (boolean_I_any((*Core.glb)(_oid_(OBJECT(ClaireRelation,p2)->domain),
                  _oid_(p->domain))) == CTRUE))
             ls= ls->addFast((OID)((OID)OBJECT(property,p2)->dispatcher));
            }
          
          g0606=OBJECT(ClaireBoolean,V_C);}
        if (g0606 == CTRUE)
         { ;ClEnv->cHandle = loop_handle; break;}
        }
      }
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(x);
      for (START(p->restrictions); NEXT(x);)
      d= meet_class(d,domain_I_restriction(OBJECT(restriction,x)));
      }
    (p->domain = d);
    { property * g0608 = p; 
      CL_INT  g0609;
      { OID  i_some = CNULL;
        { CL_INT  i = 1;
          CL_INT  g0607 = ((CL_INT)ls->length+(CL_INT)1);
          { CL_INT loop_handle = ClEnv->cHandle;
            while (((CL_INT)i <= (CL_INT)g0607))
            { if (ls->memq(((OID)i)) != CTRUE)
               { i_some= ((OID)i);
                ClEnv->cHandle = loop_handle; break;}
              ++i;
              POP_SIGNAL;}
            }
          }
        g0609 = i_some;
        }
      (g0608->dispatcher = g0609);}
    }
  POP_SIGNAL;}


// The c++ function for: interface(c:class,l:listargs) [NEW_ALLOC+BAG_UPDATE]
void  interface_class(ClaireClass *c,listargs *l)
{ GC_BIND;
  { OID  g0610UU;
    { list * V_CL0611;{ list * x_out = list::empty(Kernel._property);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(x);
          for (START(l); NEXT(x);)
          if (INHERIT(OWNER(x),Kernel._property))
           x_out->addFast((OID)x);
          }
        V_CL0611 = GC_OBJECT(list,x_out);
        }
      
      g0610UU=_oid_(V_CL0611);}
    put_table(Language.InterfaceList,_oid_(c),g0610UU);
    }
  { property * px = Language.ClaireInterface;
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(p);
      bag *p_support;
      p_support = OBJECT(bag,nth_table1(Language.InterfaceList,_oid_(c)));
      for (START(p_support); NEXT(p);)
      if ((*Kernel.open)(p) == ((OID)3))
       (*Core.call)(_oid_(px),
        p);
      }
    }
  GC_UNBIND; POP_SIGNAL;}


// only implied for open properties !!!!
// ****************** Construction *********************************
// filling the evaluation form

