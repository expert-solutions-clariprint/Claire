/***** CLAIRE Compilation of file ./compile/ocontrol.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:46 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>
#include <Optimize.h>
ClaireType * c_type_Assign_Optimize(Assign *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    Result = OBJECT(ClaireType,(*Optimize.c_type)(v61776->arg));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Assign_Optimize(Assign *v61776)
{ GC_BIND;
  { OID Result = 0;
    { OID  v48370 = GC_OID(v61776->var);
      OID  v48372 = GC_OID(v61776->arg);
      ClaireType * v4955 = GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v48372))));
      if (inherit_ask_class(OWNER(v48370),Language._Variable) != CTRUE)
       (*Optimize.Cerror)(_string_("[213] ~S is not a variable"),
        v48370);
      if (_oid_((ClaireObject *) Core._inf_equalt->fcall(((CL_INT) v4955),((CL_INT) OBJECT(ClaireObject,GC_OID((*Kernel.range)(v48370)))))) != Kernel.ctrue)
       v48372= GC_OID((*Optimize.c_warn)(GC_OID(v61776->var),
        v48372,
        _oid_(v4955)));
      { OID  v28181 = GC_OID(c_gc_I_any2(GC_OID(c_strict_code_any(v48372,psort_any(GC_OID((*Kernel.range)(v48370))))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel._exp)(GC_OID((*Kernel.range)(v48370)),
          _oid_(v4955))))));
        gc_register_Variable2(OBJECT(Variable,v48370),v28181);
        { Assign * v47292 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
          (v47292->var = v48370);
          (v47292->arg = v28181);
          add_I_property(Kernel.instances,Language._Assign,11,_oid_(v47292));
          Result = _oid_(v47292);
          }
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * c_gc_ask_Assign(Assign *v61776)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v61776->arg));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Gassign_Optimize(Gassign *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    Result = OBJECT(ClaireType,(*Optimize.c_type)(v61776->arg));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Gassign_Optimize(Gassign *v61776)
{ GC_BIND;
  { OID Result = 0;
    { OID  v55285 = GC_OID(v61776->arg);
      ClaireType * v4955 = GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v55285))));
      if (boolean_I_any(_oid_(v61776->var->range)) != CTRUE)
       (*Optimize.Cerror)(_string_("[214] cannot assign ~S"),
        _oid_(v61776));
      if (_oid_((ClaireObject *) Core._inf_equalt->fcall(((CL_INT) v4955),((CL_INT) v61776->var->range))) != Kernel.ctrue)
       v55285= GC_OID(c_check_any(GC_OID((*Optimize.c_code)(v55285,
        _oid_(Kernel._any))),GC_OID((*Optimize.c_code)(_oid_(v61776->var->range),
        _oid_(Kernel._type)))));
      { Gassign * v47292 = ((Gassign *) GC_OBJECT(Gassign,new_object_class(Language._Gassign)));
        store_object(v47292,
          2,
          Kernel._object,
          (*Optimize.c_code)(_oid_(v61776->var)),
          CFALSE);
        { Gassign * v22692 = v47292; 
          OID  v22714;
          if (nativeVar_ask_global_variable(v61776->var) == CTRUE)
           v22714 = c_strict_code_any(v55285,psort_any(_oid_(v61776->var->range)));
          else v22714 = (*Optimize.c_code)(v55285,
              _oid_(Kernel._any));
            (v22692->arg = v22714);}
        add_I_property(Kernel.instances,Language._Gassign,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * c_gc_ask_Gassign(Gassign *v61776)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v61776->arg));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_And_Optimize(And *v61776)
{ POP_SIGNAL; return (Kernel._boolean);}

OID  c_code_And_Optimize(And *v61776)
{ GC_BIND;
  { OID Result = 0;
    { And * v47292 = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
      { And * v22715 = v47292; 
        list * v22716;
        { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v48372; CL_INT CLcount;
          v_list = GC_OBJECT(list,v61776->args);
           v22716 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v48372 = (*(v_list))[CLcount];
            { if ((*Optimize.c_type)(v48372) == _oid_(Kernel._void))
               (*Optimize.Cerror)(_string_("[206] void ~S in ~S"),
                v48372,
                _oid_(v61776));
              v_val = c_boolean_any(v48372);
              }
            
            (*((list *) v22716))[CLcount] = v_val;}
          }
        (v22715->args = v22716);}
      add_I_property(Kernel.instances,Language._And,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Or_Optimize(Or *v61776)
{ POP_SIGNAL; return (Kernel._boolean);}

OID  c_code_Or_Optimize(Or *v61776)
{ GC_BIND;
  { OID Result = 0;
    { Or * v47292 = ((Or *) GC_OBJECT(Or,new_object_class(Language._Or)));
      { Or * v22717 = v47292; 
        list * v22718;
        { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v48372; CL_INT CLcount;
          v_list = GC_OBJECT(list,v61776->args);
           v22718 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v48372 = (*(v_list))[CLcount];
            { if ((*Optimize.c_type)(v48372) == _oid_(Kernel._void))
               (*Optimize.Cerror)(_string_("[206] void ~S in ~S"),
                v48372,
                _oid_(v61776));
              v_val = c_boolean_any(v48372);
              }
            
            (*((list *) v22718))[CLcount] = v_val;}
          }
        (v22717->args = v22718);}
      add_I_property(Kernel.instances,Language._Or,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Quote_Optimize(Quote *v61776)
{ POP_SIGNAL; return (OWNER(v61776->arg));}

void  c_code_Quote_Optimize(Quote *v61776)
{ (*Optimize.Cerror)(_string_("[internal] optimization of quote not implemented yet! ~S"),
    _oid_(v61776));
  POP_SIGNAL;}

ClaireType * c_type_to_protect_Optimize(Compile_to_protect *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    Result = OBJECT(ClaireType,(*Optimize.c_type)(v61776->arg));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_to_protect_Optimize(Compile_to_protect *v61776)
{ POP_SIGNAL; return (_oid_(v61776));}

ClaireBoolean * c_gc_ask_to_protect(Compile_to_protect *v61776)
{ POP_SIGNAL; return (CFALSE);}

ClaireType * c_type_Return_Optimize(Return *v61776)
{ POP_SIGNAL; return (Kernel._any);}

OID  c_code_Return_Optimize(Return *v61776)
{ GC_BIND;
  (Optimize.OPT->loop_gc = CFALSE);
  { OID Result = 0;
    { Return * v47292 = ((Return *) GC_OBJECT(Return,new_object_class(Language._Return)));
      (v47292->arg = (*Optimize.c_code)(GC_OID(v61776->arg),
        _oid_(Kernel._any)));
      add_I_property(Kernel.instances,Language._Return,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Handle_Optimize(ClaireHandle *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    Result = U_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->arg)))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->other)))));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Handle_Optimize(ClaireHandle *v61776,ClaireClass *v48367)
{ GC_BIND;
  { OID Result = 0;
    { ClaireHandle * v48372;
      { { ClaireHandle * v47292 = ((ClaireHandle *) GC_OBJECT(ClaireHandle,new_object_class(Language._Handle)));
          (v47292->test = _oid_(Kernel._any));
          (v47292->arg = (*Optimize.c_code)(GC_OID(v61776->arg),
            _oid_(v48367)));
          (v47292->other = (*Optimize.c_code)(GC_OID(v61776->other),
            _oid_(v48367)));
          add_I_property(Kernel.instances,Language._Handle,11,_oid_(v47292));
          v48372 = v47292;
          }
        GC_OBJECT(ClaireHandle,v48372);}
      if (v61776->test != _oid_(Core._contradiction))
       (Optimize.OPT->allocation = CTRUE);
      (v48372->test = v61776->test);
      Result = _oid_(v48372);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * c_gc_ask_Handle(ClaireHandle *v61776)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = (((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v61776->arg))) == CTRUE) ? CTRUE : (((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v61776->other))) == CTRUE) ? CTRUE : CFALSE));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Cast_Optimize(Cast *v61776)
{ POP_SIGNAL; return (v61776->set_arg);}

OID  c_code_Cast2_Optimize(Cast *v61776)
{ GC_BIND;
  { OID Result = 0;
    { ClaireType * v48373 = GC_OBJECT(ClaireType,v61776->set_arg);
      ClaireClass * v2844 = psort_any(_oid_(v48373));
      if ((INHERIT(v48373->isa,Core._Param)) && (((CLREAD(Param,v48373,arg) == Kernel._list) || 
            (CLREAD(Param,v48373,arg) == Kernel._set)) && 
          (Kernel._set == OWNER((*(CLREAD(Param,v48373,args)))[1]))))
       { OID  v27563 = GC_OID((*(OBJECT(set,(*(CLREAD(Param,v48373,args)))[1])))[1]);
        if ((equal(_oid_(_at_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->arg)))),Kernel.of)),v27563) == CTRUE) || 
            ((CL_INT)Optimize.compiler->safety > 4))
         Result = (*Optimize.c_code)(GC_OID(v61776->arg),
          _oid_(v2844));
        else { OID  v12191;
            { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (v47292->selector = Core.check_in);
              (v47292->args = list::alloc(3,GC_OID(v61776->arg),
                _oid_(CLREAD(Param,v48373,arg)),
                v27563));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
              v12191 = _oid_(v47292);
              }
            Result = (*Optimize.c_code)(v12191,
              _oid_(v2844));
            }
          }
      else if ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->arg)))),v48373) == CTRUE) || 
          ((CL_INT)Optimize.compiler->safety > 1))
       Result = (*Optimize.c_code)(GC_OID(v61776->arg),
        _oid_(v2844));
      else { OID  v13152;
          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            (v47292->selector = Core.check_in);
            (v47292->args = list::alloc(2,GC_OID(v61776->arg),_oid_(v48373)));
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
            v13152 = _oid_(v47292);
            }
          Result = (*Optimize.c_code)(v13152,
            _oid_(v2844));
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Super_Optimize(Super *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    { list * v4955;
      { { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v48372; CL_INT CLcount;
          v_list = GC_OBJECT(list,v61776->args);
           v4955 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v48372 = (*(v_list))[CLcount];
            v_val = (*Optimize.c_type)(v48372);
            
            (*((list *) v4955))[CLcount] = v_val;}
          }
        GC_OBJECT(list,v4955);}
      property * v48367 = v61776->selector;
      ((*(v4955))[1]=GC_OID(_oid_(v61776->cast_to)));
      { OID  v50535;
        { if (v48367->open == 3)
           v50535 = Core.nil->value;
          else v50535 = restriction_I_class(class_I_type(GC_OBJECT(ClaireType,v61776->cast_to)),v48367->definition,v4955);
            GC_OID(v50535);}
        Result = ((Kernel._slot == OWNER(v50535)) ?
          OBJECT(restriction,v50535)->range :
          ((Kernel._method == OWNER(v50535)) ?
            use_range_method(OBJECT(method,v50535),v4955) :
            v48367->range ) );
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Super_Optimize(Super *v61776)
{ GC_BIND;
  { OID Result = 0;
    { property * v48367 = v61776->selector;
      list * v48360 = GC_OBJECT(list,v61776->args);
      list * v4955;
      { { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v48372; CL_INT CLcount;
          v_list = GC_OBJECT(list,v61776->args);
           v4955 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v48372 = (*(v_list))[CLcount];
            v_val = (*Optimize.c_type)(v48372);
            
            (*((list *) v4955))[CLcount] = v_val;}
          }
        GC_OBJECT(list,v4955);}
      OID  v50535;
      { if (v48367->open == 3)
         v50535 = Core.nil->value;
        else v50535 = restriction_I_class(class_I_type(GC_OBJECT(ClaireType,v61776->cast_to)),v48367->definition,v4955);
          GC_OID(v50535);}
      if (Kernel._slot == OWNER(v50535))
       { Call_slot * v47292 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
        (v47292->selector = OBJECT(slot,v50535));
        (v47292->arg = (*Optimize.c_code)((*(v48360))[1],
          _oid_(psort_any(_oid_(domain_I_restriction(OBJECT(restriction,v50535)))))));
        (v47292->test = ((belong_to(OBJECT(slot,v50535)->DEFAULT,_oid_(OBJECT(restriction,v50535)->range)) != CTRUE) ? (((CL_INT)Optimize.compiler->safety < 5) ? CTRUE: CFALSE): CFALSE));
        add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      else if (Kernel._method == OWNER(v50535))
       Result = c_code_method_method1(OBJECT(method,v50535),v48360,v4955);
      else Result = c_warn_Super(v61776,_oid_(v4955));
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  self_print_Call_function2(Optimize_Call_function2 *v61776)
{ GC_BIND;
  print_any(GC_OID(get_property(Kernel.arg,v61776)));
  princ_string("(");
  princ_bag(v61776->args);
  princ_string(")");
  GC_UNBIND; POP_SIGNAL;}

ClaireType * c_type_Call_function2_Optimize(Optimize_Call_function2 *v61776)
{ POP_SIGNAL; return (Kernel._any);}

OID  c_code_Call_function2_Optimize(Optimize_Call_function2 *v61776)
{ GC_BIND;
  { OID Result = 0;
    { Optimize_Call_function2 * v47292 = ((Optimize_Call_function2 *) GC_OBJECT(Optimize_Call_function2,new_object_class(Optimize._Call_function2)));
      (v47292->arg = v61776->arg);
      { Optimize_Call_function2 * v22721 = v47292; 
        list * v22722;
        { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v48372; CL_INT CLcount;
          v_list = v61776->args;
           v22722 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v48372 = (*(v_list))[CLcount];
            v_val = (*Optimize.c_code)(v48372,
              _oid_(Kernel._any));
            
            (*((list *) v22722))[CLcount] = v_val;}
          }
        (v22721->args = v22722);}
      add_I_property(Kernel.instances,Optimize._Call_function2,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Assert_Optimize(Assert *v61776)
{ if (Optimize.OPT->online_ask == CTRUE) 
  { { OID Result = 0;
      Result = _oid_(v61776);
      return (Result);}
     }
  else{ GC_BIND;
    { OID Result = 0;
      if ((Optimize.compiler->safety == 0) || 
          (Optimize.compiler->debug_ask->length != 0))
       { OID  v16035;
        { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
          { If * v22745 = v47292; 
            OID  v22746;
            { Call * v63854;{ Call * v40060;
                { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  (v47292->selector = Core.NOT);
                  (v47292->args = list::alloc(1,GC_OID((*(v61776->args))[1])));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                  v40060 = v47292;
                  }
                v63854 = loc_I_Call1(v40060);
                }
              
              v22746=_oid_(v63854);}
            (v22745->test = v22746);}
          { If * v22749 = v47292; 
            OID  v22750;
            { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (v47292->selector = Core.tformat);
              { Call * v22751 = v47292; 
                list * v22752;
                { OID v_bag;
                  GC_ANY(v22752= list::empty(Kernel.emptySet));
                  ((list *) v22752)->addFast((OID)_string_("Assertion violation in ~A line ~A\n"));
                  ((list *) v22752)->addFast((OID)((OID)0));
                  { { List * v47292 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                      (v47292->args = list::alloc(2,GC_OID(_string_(v61776->external)),((OID)v61776->index)));
                      add_I_property(Kernel.instances,Language._List,11,_oid_(v47292));
                      v_bag = _oid_(v47292);
                      }
                    GC_OID(v_bag);}
                  ((list *) v22752)->addFast((OID)v_bag);}
                (v22751->args = v22752);}
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
              v22750 = _oid_(v47292);
              }
            (v22749->arg = v22750);}
          (v47292->other = Kernel.cfalse);
          add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
          v16035 = _oid_(v47292);
          }
        Result = (*Optimize.c_code)(v16035,
          _oid_(Kernel._any));
        }
      else Result = Kernel.cfalse;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  }

OID  c_code_Trace_Optimize(Trace *v61776)
{ GC_BIND;
  { OID Result = 0;
    { list * v48349 = GC_OBJECT(list,v61776->args);
      if (Optimize.OPT->online_ask == CTRUE)
       Result = _oid_(v61776);
      else if ((v48349->length == 1) && 
          (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)((*(v48349))[1]))),Kernel._integer) == CTRUE))
       { OID  v44865;
        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          (v47292->selector = Core.write);
          (v47292->args = list::alloc(3,_oid_(Kernel.verbose),
            _oid_(ClEnv),
            (*(v48349))[1]));
          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
          v44865 = _oid_(v47292);
          }
        Result = (*Optimize.c_code)(v44865);
        }
      else if (((CL_INT)v48349->length > 1) && 
          (Kernel._string == OWNER((*(v48349))[2])))
       { OID  v45826;
        { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
          { If * v23428 = v47292; 
            OID  v23429;
            { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (v47292->selector = Core.should_trace_ask);
              (v47292->args = list::alloc(2,_oid_(ClEnv->module_I),(*(v48349))[1]));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
              v23429 = _oid_(v47292);
              }
            (v23428->test = v23429);}
          { If * v23430 = v47292; 
            OID  v23431;
            { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (v47292->selector = Core.mtformat);
              { Call * v23432 = v47292; 
                list * v23433;
                { OID v_bag;
                  GC_ANY(v23433= list::empty(Kernel.emptySet));
                  ((list *) v23433)->addFast((OID)_oid_(ClEnv->module_I));
                  ((list *) v23433)->addFast((OID)(*(v48349))[2]);
                  ((list *) v23433)->addFast((OID)(*(v48349))[1]);
                  { { List * v47292 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                      (v47292->args = skip_list(((list *) copy_bag(v48349)),2));
                      add_I_property(Kernel.instances,Language._List,11,_oid_(v47292));
                      v_bag = _oid_(v47292);
                      }
                    GC_OID(v_bag);}
                  ((list *) v23433)->addFast((OID)v_bag);}
                (v23432->args = v23433);}
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
              v23431 = _oid_(v47292);
              }
            (v23430->arg = v23431);}
          add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
          (v47292->other = Kernel.cfalse);
          v45826 = _oid_(v47292);
          }
        Result = (*Optimize.c_code)(v45826,
          _oid_(Kernel._any));
        }
      else Result = Kernel.cfalse;
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Assert_Optimize(Assert *v61776)
{ POP_SIGNAL; return (Kernel._any);}

ClaireType * c_type_Trace_Optimize(Trace *v61776)
{ POP_SIGNAL; return (Kernel._any);}

ClaireType * c_type_Branch_Optimize(Branch *v61776)
{ POP_SIGNAL; return (Kernel._boolean);}

OID  c_code_Branch_Optimize(Branch *v61776)
{ GC_BIND;
  { OID Result = 0;
    { OID  v42985;
      { ClaireHandle * v47292 = ((ClaireHandle *) GC_OBJECT(ClaireHandle,new_object_class(Language._Handle)));
        { ClaireHandle * v23435 = v47292; 
          OID  v23436;
          { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            { Do * v23437 = v47292; 
              list * v23458;
              { OID v_bag;
                GC_ANY(v23458= list::empty(Kernel.emptySet));
                { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Kernel.choice);
                    (v47292->args = list::alloc(1,_oid_(ClEnv)));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v_bag = _oid_(v47292);
                    }
                  GC_OID(v_bag);}
                ((list *) v23458)->addFast((OID)v_bag);
                { { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                    (v47292->test = (*(v61776->args))[1]);
                    (v47292->arg = Kernel.ctrue);
                    { If * v23459 = v47292; 
                      OID  v23460;
                      { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                        { Do * v23461 = v47292; 
                          list * v23462;
                          { OID v_bag;
                            GC_ANY(v23462= list::empty(Kernel.emptySet));
                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                (v47292->selector = Kernel.backtrack);
                                (v47292->args = list::alloc(1,_oid_(ClEnv)));
                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                v_bag = _oid_(v47292);
                                }
                              GC_OID(v_bag);}
                            ((list *) v23462)->addFast((OID)v_bag);
                            ((list *) v23462)->addFast((OID)Kernel.cfalse);}
                          (v23461->args = v23462);}
                        add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                        v23460 = _oid_(v47292);
                        }
                      (v23459->other = v23460);}
                    add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                    v_bag = _oid_(v47292);
                    }
                  GC_OID(v_bag);}
                ((list *) v23458)->addFast((OID)v_bag);}
              (v23437->args = v23458);}
            add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
            v23436 = _oid_(v47292);
            }
          (v23435->arg = v23436);}
        (v47292->test = _oid_(Core._contradiction));
        { ClaireHandle * v23464 = v47292; 
          OID  v23465;
          { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            { Do * v23466 = v47292; 
              list * v23467;
              { OID v_bag;
                GC_ANY(v23467= list::empty(Kernel.emptySet));
                { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Kernel.backtrack);
                    (v47292->args = list::alloc(1,_oid_(ClEnv)));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v_bag = _oid_(v47292);
                    }
                  GC_OID(v_bag);}
                ((list *) v23467)->addFast((OID)v_bag);
                ((list *) v23467)->addFast((OID)Kernel.cfalse);}
              (v23466->args = v23467);}
            add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
            v23465 = _oid_(v47292);
            }
          (v23464->other = v23465);}
        add_I_property(Kernel.instances,Language._Handle,11,_oid_(v47292));
        v42985 = _oid_(v47292);
        }
      Result = (*Optimize.c_code)(v42985,
        _oid_(Kernel._any));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Macro_Optimize(Macro *v61776,ClaireClass *v48367)
{ GC_BIND;
  { OID Result = 0;
    Result = (*Optimize.c_code)(GC_OID((*Language.macroexpand)(_oid_(v61776))),
      _oid_(v48367));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Macro_Optimize(Macro *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    Result = OBJECT(ClaireType,(*Optimize.c_type)(GC_OID((*Language.macroexpand)(_oid_(v61776)))));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Printf_Optimize(Printf *v61776)
{ POP_SIGNAL; return (Kernel._any);}

OID  c_code_Printf_Optimize(Printf *v61776)
{ GC_RESERVE(22);  // v3.0.55 optim !
  { OID Result = 0;
    { list * v46190 = GC_OBJECT(list,v61776->args);
      list * v48366 = list::empty(Kernel._any);
      OID  v17948;
      { { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
          (v47292->args = v48366);
          add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
          v17948 = _oid_(v47292);
          }
        GC_OID(v17948);}
      ClaireBoolean * v44251 = ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)((*(v46190))[1]))),Kernel._port) == CTRUE) ? CTRUE : CFALSE);
      OID  v48367;
      if (v44251 == CTRUE)
       v48367 = (*(v46190))[2];
      else v48367 = (*(v46190))[1];
        if (equal(_oid_(Kernel._string),_oid_(OWNER(v48367))) != CTRUE)
       (*Optimize.Cerror)(_string_("[209] the first argument in ~S must be a string or a port"),
        _oid_(v61776));
      else { CL_INT  v48362 = find_string2(string_v(v48367),"~");
          ClaireBoolean * v28224 = (((CL_INT)((CL_INT)((CL_INT)((CL_INT)((CL_INT)((CL_INT)((CL_INT)((CL_INT)find_string2(string_v(v48367),"`BLACK")+(CL_INT)find_string2(string_v(v48367),"`BLUE"))+(CL_INT)find_string2(string_v(v48367),"`MAGENTA"))+(CL_INT)find_string2(string_v(v48367),"`RED"))+(CL_INT)find_string2(string_v(v48367),"`CYAN"))+(CL_INT)find_string2(string_v(v48367),"YELLOW"))+(CL_INT)find_string2(string_v(v48367),"`WHITE"))+(CL_INT)find_string2(string_v(v48367),"`GREEN")) > 0) ? CTRUE : CFALSE);
          CL_INT  v9273 = 1;
          OID  v30302 = CNULL;
          OID  v42049 = CNULL;
          OID  v28644 = CNULL;
          OID  v3836 = CNULL;
          OID  v23689 = CNULL;
          CL_INT  v57538 = ((v44251 == CTRUE) ?
            3 :
            2 );
          CL_INT  v12177 = (*Kernel.length)(v48367);
          if (v44251 == CTRUE)
           { v30302= GC_OID(_oid_(Variable_I_symbol(gensym_void(),0,Kernel._port)));
            { { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                store_object(v47292,
                  2,
                  Kernel._object,
                  v30302,
                  CFALSE);
                { Let * v23468 = v47292; 
                  OID  v23489;
                  { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Kernel.use_as_output);
                    (v47292->args = list::alloc(1,(*(v46190))[1]));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v23489 = _oid_(v47292);
                    }
                  (v23468->value = v23489);}
                (v47292->arg = v17948);
                add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                v17948 = _oid_(v47292);
                }
              GC_OID(v17948);}
            }
          if (v28224 == CTRUE)
           { v42049= GC_OID(_oid_(Variable_I_symbol(gensym_void(),0,Kernel._integer)));
            v28644= GC_OID(_oid_(Variable_I_symbol(gensym_void(),0,Kernel._integer)));
            v3836= GC_OID(_oid_(Variable_I_symbol(gensym_void(),0,Kernel._integer)));
            v23689= GC_OID(_oid_(Variable_I_symbol(gensym_void(),0,Kernel._integer)));
            { { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                store_object(v47292,
                  2,
                  Kernel._object,
                  v42049,
                  CFALSE);
                { Let * v23490 = v47292; 
                  OID  v23491;
                  { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Core.externC);
                    (v47292->args = list::alloc(2,_string_("current_color"),_oid_(Kernel._integer)));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v23491 = _oid_(v47292);
                    }
                  (v23490->value = v23491);}
                { Let * v23492 = v47292; 
                  OID  v23493;
                  { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                    store_object(v47292,
                      2,
                      Kernel._object,
                      v28644,
                      CFALSE);
                    { Let * v23494 = v47292; 
                      OID  v23495;
                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        (v47292->selector = Core.externC);
                        (v47292->args = list::alloc(2,_string_("current_bold"),_oid_(Kernel._integer)));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                        v23495 = _oid_(v47292);
                        }
                      (v23494->value = v23495);}
                    { Let * v23496 = v47292; 
                      OID  v23497;
                      { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                        store_object(v47292,
                          2,
                          Kernel._object,
                          v3836,
                          CFALSE);
                        (v47292->value = v42049);
                        { Let * v23498 = v47292; 
                          OID  v23520;
                          { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                            store_object(v47292,
                              2,
                              Kernel._object,
                              v23689,
                              CFALSE);
                            (v47292->value = v28644);
                            (v47292->arg = v17948);
                            add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                            v23520 = _oid_(v47292);
                            }
                          (v23498->arg = v23520);}
                        add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                        v23497 = _oid_(v47292);
                        }
                      (v23496->arg = v23497);}
                    add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                    v23493 = _oid_(v47292);
                    }
                  (v23492->arg = v23493);}
                add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                v17948 = _oid_(v47292);
                }
              GC_OID(v17948);}
            }
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((0 < (CL_INT)v48362) && 
                ((CL_INT)v48362 < (CL_INT)v12177)))
            { GC_LOOP;
              { OID  v48361 = GC_OID((*Kernel.nth)(v48367,
                  ((OID)((CL_INT)v48362+(CL_INT)1))));
                if ((CL_INT)v48362 > 1)
                 { if (0 <= (CL_INT)((CL_INT)((CL_INT)v48362-(CL_INT)1)-(CL_INT)v9273))
                   { if (v28224 == CTRUE)
                     { { OID  v62017;
                        { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                          { Do * v23522 = v47292; 
                            list * v23523;
                            { OID v_bag;
                              GC_ANY(v23523= list::empty(Kernel.emptySet));
                              { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                  (v47292->selector = Core.set_color);
                                  (v47292->args = list::alloc(2,v42049,v28644));
                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                  v_bag = _oid_(v47292);
                                  }
                                GC_OID(v_bag);}
                              ((list *) v23523)->addFast((OID)v_bag);
                              { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                  (v47292->selector = Kernel.color_princ);
                                  (v47292->args = list::alloc(1,GC_OID((*Kernel.substring)(v48367,
                                    ((OID)v9273),
                                    ((OID)((CL_INT)v48362-(CL_INT)1))))));
                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                  v_bag = _oid_(v47292);
                                  }
                                GC_OID(v_bag);}
                              ((list *) v23523)->addFast((OID)v_bag);}
                            (v23522->args = v23523);}
                          add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                          v62017 = _oid_(v47292);
                          }
                        v48366 = v48366->addFast((OID)v62017);
                        }
                       GC__ANY(v48366, 4);}
                    else { { OID  v64900;
                          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                            (v47292->selector = Kernel.princ);
                            (v47292->args = list::alloc(1,GC_OID((*Kernel.substring)(v48367,
                              ((OID)v9273),
                              ((OID)((CL_INT)v48362-(CL_INT)1))))));
                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                            v64900 = _oid_(v47292);
                            }
                          v48366 = v48366->addFast((OID)v64900);
                          }
                         GC__ANY(v48366, 4);}
                      if (v28224 == CTRUE)
                     { { OID  v325;
                        { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                          { Do * v23526 = v47292; 
                            list * v23527;
                            { OID v_bag;
                              GC_ANY(v23527= list::empty(Kernel.emptySet));
                              { { Assign * v47292 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                  (v47292->var = v42049);
                                  { Assign * v23528 = v47292; 
                                    OID  v23529;
                                    { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                      (v47292->selector = Core.externC);
                                      (v47292->args = list::alloc(2,_string_("current_color"),_oid_(Kernel._integer)));
                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                      v23529 = _oid_(v47292);
                                      }
                                    (v23528->arg = v23529);}
                                  add_I_property(Kernel.instances,Language._Assign,11,_oid_(v47292));
                                  v_bag = _oid_(v47292);
                                  }
                                GC_OID(v_bag);}
                              ((list *) v23527)->addFast((OID)v_bag);
                              { { Assign * v47292 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                  (v47292->var = v28644);
                                  { Assign * v23551 = v47292; 
                                    OID  v23552;
                                    { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                      (v47292->selector = Core.externC);
                                      (v47292->args = list::alloc(2,_string_("current_bold"),_oid_(Kernel._integer)));
                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                      v23552 = _oid_(v47292);
                                      }
                                    (v23551->arg = v23552);}
                                  add_I_property(Kernel.instances,Language._Assign,11,_oid_(v47292));
                                  v_bag = _oid_(v47292);
                                  }
                                GC_OID(v_bag);}
                              ((list *) v23527)->addFast((OID)v_bag);}
                            (v23526->args = v23527);}
                          add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                          v325 = _oid_(v47292);
                          }
                        v48366 = v48366->addFast((OID)v325);
                        }
                       GC__ANY(v48366, 4);}
                    }
                  }
                if (v28224 == CTRUE)
                 { { OID  v27233;
                    { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      (v47292->selector = Core.set_color);
                      (v47292->args = list::alloc(2,v3836,v23689));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                      v27233 = _oid_(v47292);
                      }
                    v48366 = v48366->addFast((OID)v27233);
                    }
                   GC__ANY(v48366, 4);}
                if ((CL_INT)v57538 > (CL_INT)v46190->length)
                 (*Optimize.Cerror)(_string_("[209] missing argument in ~S"),
                  _oid_(v61776));
                if (_oid_(_char_(((unsigned char)65 /* 'A' */))) == v48361)
                 { { OID  v28194;
                    { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      (v47292->selector = Kernel.princ);
                      (v47292->args = list::alloc(1,(*(v46190))[v57538]));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                      v28194 = _oid_(v47292);
                      }
                    v48366 = v48366->addFast((OID)v28194);
                    }
                   GC__ANY(v48366, 4);}
                else if (_oid_(_char_(((unsigned char)83 /* 'S' */))) == v48361)
                 { { OID  v29156;
                    { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      (v47292->selector = Kernel.print);
                      (v47292->args = list::alloc(1,(*(v46190))[v57538]));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                      v29156 = _oid_(v47292);
                      }
                    v48366 = v48366->addFast((OID)v29156);
                    }
                   GC__ANY(v48366, 4);}
                else if (_oid_(_char_(((unsigned char)73 /* 'I' */))) == v48361)
                 GC__ANY(v48366 = v48366->addFast((OID)(*(v46190))[v57538]), 4);
                if (v28224 == CTRUE)
                 { { OID  v30116;
                    { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      (v47292->selector = Core.set_color);
                      (v47292->args = list::alloc(2,v42049,v28644));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                      v30116 = _oid_(v47292);
                      }
                    v48366 = v48366->addFast((OID)v30116);
                    }
                   GC__ANY(v48366, 4);}
                if (v48361 != _oid_(_char_(((unsigned char)37 /* '%' */))))
                 ++v57538;
                v9273= ((CL_INT)v48362+(CL_INT)2);
                v48362= find_string(string_v(v48367),"~",v9273);
                }
              GC_UNLOOP;POP_SIGNAL;}
            }
          if ((CL_INT)v9273 <= (CL_INT)v12177)
           { if (v28224 == CTRUE)
             { OID  v31077;
              { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                { Do * v23558 = v47292; 
                  list * v23559;
                  { OID v_bag;
                    GC_ANY(v23559= list::empty(Kernel.emptySet));
                    { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        (v47292->selector = Core.set_color);
                        (v47292->args = list::alloc(2,v42049,v28644));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                        v_bag = _oid_(v47292);
                        }
                      GC_OID(v_bag);}
                    ((list *) v23559)->addFast((OID)v_bag);
                    { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        (v47292->selector = Kernel.color_princ);
                        (v47292->args = list::alloc(1,GC_OID((*Kernel.substring)(v48367,
                          ((OID)v9273),
                          ((OID)v12177)))));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                        v_bag = _oid_(v47292);
                        }
                      GC_OID(v_bag);}
                    ((list *) v23559)->addFast((OID)v_bag);}
                  (v23558->args = v23559);}
                add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                v31077 = _oid_(v47292);
                }
              v48366 = v48366->addFast((OID)v31077);
              }
            else { OID  v33960;
                { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  (v47292->selector = Kernel.princ);
                  (v47292->args = list::alloc(1,GC_OID((*Kernel.substring)(v48367,
                    ((OID)v9273),
                    ((OID)v12177)))));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                  v33960 = _oid_(v47292);
                  }
                v48366 = v48366->addFast((OID)v33960);
                }
              }
          if (v28224 == CTRUE)
           { OID  v55102;
            { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (v47292->selector = Core.set_color);
              (v47292->args = list::alloc(2,v3836,v23689));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
              v55102 = _oid_(v47292);
              }
            v48366 = v48366->addFast((OID)v55102);
            }
          if (v44251 == CTRUE)
           { OID  v56063;
            { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (v47292->selector = Kernel.use_as_output);
              (v47292->args = list::alloc(1,v30302));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
              v56063 = _oid_(v47292);
              }
            v48366 = v48366->addFast((OID)v56063);
            }
          }
        Result = (*Optimize.c_code)(v17948,
        _oid_(Kernel._any));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Scanf1_Optimize(Scanf *v61776)
{ POP_SIGNAL; return (U_type(set::alloc(Kernel.emptySet,1,Kernel.cfalse),Kernel._integer));}

OID  c_code_Scanf1_Optimize(Scanf *v61776)
{ GC_BIND;
  { OID Result = 0;
    Result = (*Optimize.c_code)(v61776->compiled,
      _oid_(Kernel._any));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Error_Optimize(Error *v61776)
{ POP_SIGNAL; return (Kernel.emptySet);}

OID  c_code_Error_Optimize(Error *v61776)
{ GC_BIND;
  { OID Result = 0;
    { ClaireBoolean * v48372 = Optimize.OPT->allocation;
      OID  v48373;
      { { OID  v57024;
          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            (v47292->selector = Kernel.close);
            { Call * v23585 = v47292; 
              list * v23587;
              { OID v_bag;
                GC_ANY(v23587= list::empty(Kernel.emptySet));
                { { Cast * v47292 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                    { Cast * v23588 = v47292; 
                      OID  v23589;
                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        (v47292->selector = Optimize.anyObject_I);
                        { Call * v23590 = v47292; 
                          list * v23591;
                          { OID v_bag;
                            GC_ANY(v23591= list::empty(Kernel.emptySet));
                            ((list *) v23591)->addFast((OID)_oid_(Core._general_error));
                            ((list *) v23591)->addFast((OID)GC_OID((*Optimize.c_code)(GC_OID(car_list(v61776->args)),
                              _oid_(Kernel._any))));
                            { { OID  v63751;
                                if (v61776->args->length != 1)
                                 { List * v47292 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                                  (v47292->args = cdr_list(GC_OBJECT(list,v61776->args)));
                                  add_I_property(Kernel.instances,Language._List,11,_oid_(v47292));
                                  v63751 = _oid_(v47292);
                                  }
                                else v63751 = Core.nil->value;
                                  v_bag = (*Optimize.c_code)(v63751,
                                  _oid_(Kernel._any));
                                }
                              GC_OID(v_bag);}
                            ((list *) v23591)->addFast((OID)v_bag);}
                          (v23590->args = v23591);}
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                        v23589 = _oid_(v47292);
                        }
                      (v23588->arg = v23589);}
                    (v47292->set_arg = Kernel._exception);
                    add_I_property(Kernel.instances,Language._Cast,11,_oid_(v47292));
                    v_bag = _oid_(v47292);
                    }
                  GC_OID(v_bag);}
                ((list *) v23587)->addFast((OID)v_bag);}
              (v23585->args = v23587);}
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
            v57024 = _oid_(v47292);
            }
          v48373 = (*Optimize.c_code)(v57024,
            _oid_(Kernel._void));
          }
        GC_OID(v48373);}
      (Optimize.OPT->allocation = v48372);
      Result = v48373;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * extendedTest_ask_If(If *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    { OID  v55283 = v61776->test;
      if (INHERIT(OWNER(v55283),Language._Call))
       { if ((INHERIT(OWNER((*(OBJECT(Call,v55283)->args))[1]),Language._Variable)) && 
            (OBJECT(Call,v55283)->selector == Core.known_ask))
         Result = OBJECT(ClaireType,(*Kernel.range)((*(OBJECT(Call,v55283)->args))[1]));
        else Result = Kernel._any;
          }
      else Result = Kernel._any;
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_If_Optimize(If *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    { ClaireType * v55281 = GC_OBJECT(ClaireType,extendedTest_ask_If(v61776));
      if (extended_ask_type(v55281) == CTRUE)
       range_sets_any(GC_OID((*(OBJECT(bag,(*Core.args)(GC_OID(v61776->test)))))[1]),GC_OBJECT(ClaireType,sort_abstract_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Core.t1)(_oid_(v55281)))))));
      { ClaireType * v31009 = GC_OBJECT(ClaireType,U_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->arg)))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->other))))));
        if (extended_ask_type(v55281) == CTRUE)
         put_property2(Kernel.range,GC_OBJECT(ClaireObject,OBJECT(ClaireObject,(*(OBJECT(bag,(*Core.args)(GC_OID(v61776->test)))))[1])),_oid_(v55281));
        Result = v31009;
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_If_Optimize(If *v61776,ClaireClass *v48367)
{ GC_BIND;
  { OID Result = 0;
    { ClaireType * v55281 = GC_OBJECT(ClaireType,extendedTest_ask_If(v61776));
      if (extended_ask_type(v55281) == CTRUE)
       range_sets_any(GC_OID((*(OBJECT(bag,(*Core.args)(GC_OID(v61776->test)))))[1]),GC_OBJECT(ClaireType,sort_abstract_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Core.t1)(_oid_(v55281)))))));
      if ((_inf_equal_type(GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->test))))),Kernel._boolean) != CTRUE) && 
          (Optimize.PENIBLE->value == Kernel.ctrue))
       { warn_void();
        if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
         mtformat_module1(Optimize.it,"`BLUE CLAIRE 3.3 SYNTAX - Test in ~S should be a boolean [260]\n",2,list::alloc(1,_oid_(v61776)));
        else ;}
      { If * v31009;
        { { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
            (v47292->test = c_boolean_any(GC_OID(v61776->test)));
            (v47292->arg = (*Optimize.c_code)(GC_OID(v61776->arg),
              _oid_(v48367)));
            (v47292->other = (*Optimize.c_code)(GC_OID(v61776->other),
              _oid_(v48367)));
            add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
            v31009 = v47292;
            }
          GC_OBJECT(If,v31009);}
        if (extended_ask_type(v55281) == CTRUE)
         put_property2(Kernel.range,GC_OBJECT(ClaireObject,OBJECT(ClaireObject,(*(OBJECT(bag,(*Core.args)(GC_OID(v61776->test)))))[1])),_oid_(v55281));
        Result = _oid_(v31009);
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * c_gc_ask_If(If *v61776)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = (((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v61776->arg))) == CTRUE) ? CTRUE : (((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v61776->other))) == CTRUE) ? CTRUE : CFALSE));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Case_Optimize(Case *v61776)
{ GC_RESERVE(6);  // v3.0.55 optim !
  { ClaireType *Result ;
    { OID  v47846 = GC_OID(v61776->var);
      OID  v4955;
      { if (INHERIT(OWNER(v47846),Language._Variable))
         v4955 = get_property(Kernel.range,OBJECT(ClaireObject,v47846));
        else v4955 = _oid_(Kernel._any);
          GC_OID(v4955);}
      list * v48360 = ((list *) copy_bag(v61776->args));
      ClaireType * v9512 = Kernel.emptySet;
      ClaireType * v27563 = Kernel.emptySet;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)v48360->length > 0))
        { GC_LOOP;
          if (INHERIT(OWNER((*(v48360))[1]),Kernel._type))
           { GC__ANY(v27563 = U_type(v27563,OBJECT(ClaireType,(*(v48360))[1])), 6);
            if (osort_any(v4955) == osort_any((*(v48360))[1]))
             range_sets_any(v47846,OBJECT(ClaireType,(*(v48360))[1]));
            else if (osort_any(v4955) == Kernel._any)
             range_sets_any(v47846,GC_OBJECT(ClaireType,sort_abstract_I_type(OBJECT(ClaireType,(*(v48360))[1]))));
            }
          else (*Optimize.Cerror)(_string_("[208] wrong type declaration for case: ~S in ~S"),
              car_list(v48360),
              _oid_(v61776));
            GC__ANY(v9512 = U_type(v9512,GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)((*(v48360))[2])))), 5);
          if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
           mtformat_module1(Optimize.it,"so far rtype -> ~S because of ~S branch \n",5,list::alloc(2,_oid_(v9512),(*(v48360))[1]));
          else ;if (INHERIT(OWNER(v47846),Language._Variable))
           store_object(OBJECT(ClaireObject,v47846),
            3,
            Kernel._object,
            v4955,
            CFALSE);
          v48360= skip_list(v48360,2);
          GC_UNLOOP;POP_SIGNAL;}
        }
      if (_inf_equal_type(OBJECT(ClaireType,v4955),v27563) == CTRUE)
       Result = v9512;
      else Result = ((_inf_equal_type(v9512,Kernel._boolean) == CTRUE) ?
        Kernel._boolean :
        Kernel._any );
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Case_Optimize(Case *v61776,ClaireClass *v48367)
{ GC_RESERVE(13);  // v3.0.55 optim !
  { OID Result = 0;
    { OID  v47846 = GC_OID(v61776->var);
      OID  v4955;
      { if (INHERIT(OWNER(v47846),Language._Variable))
         v4955 = get_property(Kernel.range,OBJECT(ClaireObject,v47846));
        else v4955 = _oid_(Kernel._any);
          GC_OID(v4955);}
      list * v48360 = ((list *) copy_bag(v61776->args));
      OID  v27563 = _oid_(Kernel.emptySet);
      OID  v50272;
      { { OID  v19357;
          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            (v47292->selector = Kernel._Z);
            (v47292->args = list::alloc(2,v47846,(*(v48360))[1]));
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
            v19357 = _oid_(v47292);
            }
          v50272 = c_boolean_any(v19357);
          }
        GC_OID(v50272);}
      range_sets_any(v47846,OBJECT(ClaireType,(*(v48360))[1]));
      { If * v17945;
        { { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
            (v47292->test = v50272);
            (v47292->arg = (*Optimize.c_code)((*(v48360))[2],
              _oid_(v48367)));
            (v47292->other = (*Optimize.c_code)(Kernel.cfalse,
              _oid_(v48367)));
            add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
            v17945 = v47292;
            }
          GC_OBJECT(If,v17945);}
        If * v44473 = v17945;
        if (INHERIT(OWNER(v47846),Language._Variable))
         store_object(OBJECT(ClaireObject,v47846),
          3,
          Kernel._object,
          v4955,
          CFALSE);
        v48360= skip_list(v48360,2);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)v48360->length > 0))
          { GC_LOOP;
            GC__OID(v27563 = _oid_(U_type(OBJECT(ClaireType,v27563),OBJECT(ClaireType,(*(v48360))[1]))), 7);
            if (_inf_equal_type(OBJECT(ClaireType,v4955),OBJECT(ClaireType,v27563)) == CTRUE)
             { if (osort_any(v4955) == osort_any((*(v48360))[1]))
               range_sets_any(v47846,OBJECT(ClaireType,(*(v48360))[1]));
              else if (osort_any(v4955) == Kernel._any)
               range_sets_any(v47846,GC_OBJECT(ClaireType,sort_abstract_I_type(OBJECT(ClaireType,(*(v48360))[1]))));
              (v44473->other = (*Optimize.c_code)((*(v48360))[2],
                _oid_(v48367)));
              if (INHERIT(OWNER(v47846),Language._Variable))
               store_object(OBJECT(ClaireObject,v47846),
                3,
                Kernel._object,
                v4955,
                CFALSE);
              { ;ClEnv->cHandle = loop_handle; break;}
              }
            else { OID  v31217;
                { { OID  v20318;
                    { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      (v47292->selector = Kernel._Z);
                      (v47292->args = list::alloc(2,v47846,(*(v48360))[1]));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                      v20318 = _oid_(v47292);
                      }
                    v31217 = c_boolean_any(v20318);
                    }
                  GC_OID(v31217);}
                range_sets_any(v47846,OBJECT(ClaireType,(*(v48360))[1]));
                { If * v23615 = v44473; 
                  OID  v23616;
                  { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                    (v47292->test = v31217);
                    (v47292->arg = (*Optimize.c_code)((*(v48360))[2],
                      _oid_(v48367)));
                    (v47292->other = (*Optimize.c_code)(Kernel.cfalse,
                      _oid_(v48367)));
                    add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                    v23616 = _oid_(v47292);
                    }
                  (v23615->other = v23616);}
                GC__ANY(v44473 = OBJECT(If,v44473->other), 10);
                }
              if (INHERIT(OWNER(v47846),Language._Variable))
             store_object(OBJECT(ClaireObject,v47846),
              3,
              Kernel._object,
              v4955,
              CFALSE);
            v48360= skip_list(v48360,2);
            GC_UNLOOP;POP_SIGNAL;}
          }
        if ((INHERIT(OWNER(v47846),Language._Definition)) && (INHERIT(OBJECT(Definition,v47846)->arg->isa,Kernel._exception)))
         Result = v47846;
        else Result = _oid_(v17945);
          }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Do_Optimize(Do *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    Result = OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(last_list(v61776->args))));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Do_Optimize(Do *v61776,ClaireClass *v48367)
{ GC_BIND;
  { OID Result = 0;
    { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
      { Do * v23617 = v47292; 
        list * v23618;
        { CL_INT  v48361 = v61776->args->length;
          CL_INT  v48362 = 0;
          { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID v48372; CL_INT CLcount;
            v_list = GC_OBJECT(list,v61776->args);
             v23618 = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { v48372 = (*(v_list))[CLcount];
              { ++v48362;
                { OID  v25123;
                  if (v48362 == v48361)
                   v25123 = _oid_(v48367);
                  else v25123 = _oid_(Kernel._void);
                    v_val = (*Optimize.c_code)(v48372,
                    v25123);
                  }
                }
              
              (*((list *) v23618))[CLcount] = v_val;}
            }
          }
        (v23617->args = v23618);}
      add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * c_gc_ask_Do(Do *v61776)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(GC_OID(last_list(v61776->args))));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Let_Optimize(Let *v61776)
{ GC_BIND;
  range_infers_Variable(GC_OBJECT(Variable,v61776->var),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->value)))));
  { ClaireType *Result ;
    Result = OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->arg)));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Let_Optimize(Let *v61776,ClaireClass *v48367)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { OID Result = 0;
    { OID  v55285 = GC_OID(v61776->value);
      ClaireType * v4955 = GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v55285))));
      range_infers_Variable(GC_OBJECT(Variable,v61776->var),v4955);
      if (_inf_equal_type(v4955,GC_OBJECT(ClaireType,v61776->var->range)) != CTRUE)
       v55285= GC_OID(c_warn_Variable(GC_OBJECT(Variable,v61776->var),v55285,v4955));
      { Let * v48372;
        { { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
            (v47292->var = v61776->var);
            (v47292->value = c_gc_I_any2(GC_OID(c_strict_code_any(v55285,psort_any(GC_OID(_oid_(v61776->var->range))))),v4955));
            (v47292->arg = (*Optimize.c_code)(GC_OID(v61776->arg),
              _oid_(v48367)));
            add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
            v48372 = v47292;
            }
          GC_OBJECT(Let,v48372);}
        (v48372->isa = v61776->isa);
        if ((INHERIT(v48372->isa,Language._Let_star)) && 
            ((INHERIT(v4955->isa,Kernel._tuple)) && 
              (BCONTAIN(c_status_any(GC_OID(v61776->value),Kernel.nil),(OID)(1)))))
         { CL_INT  v48357 = 1;
          OID  v48374 = GC_OID(v48372->arg);
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((INHERIT(OWNER(v48374),Language._Let)) && 
                ((CL_INT)v48357 <= (CL_INT)((bag *) v4955)->length)))
            { GC_LOOP;
              if ((((OBJECT(ClaireBoolean,(*Optimize.gcsafe_ask)((*(((bag *) v4955)))[v48357]))) == CTRUE) ? CTRUE : ((INHERIT(owner_any((*Kernel.value)(v48374)),Optimize._to_protect)) ? CTRUE : CFALSE)) != CTRUE)
               { (Optimize.OPT->protection = CTRUE);
                { OID  v26084;
                  { Compile_to_protect * v47292 = ((Compile_to_protect *) GC_OBJECT(Compile_to_protect,new_object_class(Optimize._to_protect)));
                    (v47292->arg = (*Kernel.value)(v48374));
                    add_I_property(Kernel.instances,Optimize._to_protect,11,_oid_(v47292));
                    v26084 = _oid_(v47292);
                    }
                  write_property(Kernel.value,OBJECT(ClaireObject,v48374),v26084);
                  }
                }
              ++v48357;
              GC__OID(v48374 = (*Kernel.arg)(v48374), 8);
              GC_UNLOOP;POP_SIGNAL;}
            }
          }
        Result = _oid_(v48372);
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_When_Optimize(When *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    { OID  v55285 = GC_OID(v61776->value);
      Variable * v48370 = GC_OBJECT(Variable,v61776->var);
      OID  v48352 = GC_OID(daccess_any(v55285,CTRUE));
      OID  v4955;
      { if (v48352 != CNULL)
         v4955 = (*Optimize.c_type)(v48352);
        else v4955 = (*Optimize.c_type)(v55285);
          GC_OID(v4955);}
      if (extended_ask_type(OBJECT(ClaireType,v4955)) == CTRUE)
       v4955= GC_OID((*Core.t1)(v4955));
      range_infers_Variable(v48370,OBJECT(ClaireType,v4955));
      Result = U_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->arg)))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->other)))));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_When_Optimize(When *v61776,ClaireClass *v48367)
{ GC_BIND;
  { OID Result = 0;
    { OID  v55285 = GC_OID(v61776->value);
      Variable * v48370 = GC_OBJECT(Variable,v61776->var);
      OID  v48352 = GC_OID(daccess_any(v55285,CTRUE));
      Variable * v57728 = GC_OBJECT(Variable,Variable_I_symbol(append_symbol(v61776->var->pname,_string_("test")),v61776->var->index,Kernel._any));
      OID  v4955;
      { if (v48352 != CNULL)
         v4955 = (*Optimize.c_type)(v48352);
        else v4955 = (*Optimize.c_type)(v55285);
          GC_OID(v4955);}
      if (extended_ask_type(OBJECT(ClaireType,v4955)) == CTRUE)
       v4955= GC_OID((*Core.t1)(v4955));
      range_infers_Variable(v48370,OBJECT(ClaireType,v4955));
      if ((v48352 != CNULL) && 
          (extended_ask_type(OBJECT(ClaireType,(*Kernel.range)(GC_OID((*Kernel.selector)(v48352))))) != CTRUE))
       { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
        (v47292->var = v48370);
        (v47292->value = c_gc_I_any2(v48352,OBJECT(ClaireType,v4955)));
        { Let * v23621 = v47292; 
          OID  v23622;
          { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
            { If * v23644 = v47292; 
              OID  v23645;
              { Call_method2 * v47292 = ((Call_method2 *) GC_OBJECT(Call_method2,new_object_class(Language._Call_method2)));
                (v47292->arg = ((method *) _at_property1(Core.identical_ask,Kernel._any)));
                (v47292->args = list::alloc(2,_oid_(v48370),GC_OID((*Optimize.c_code)(CNULL,
                  GC_OID((*Optimize.c_sort)(_oid_(v48370)))))));
                add_I_property(Kernel.instances,Language._Call_method2,11,_oid_(v47292));
                v23645 = _oid_(v47292);
                }
              (v23644->test = v23645);}
            (v47292->arg = (*Optimize.c_code)(GC_OID(v61776->other),
              _oid_(v48367)));
            (v47292->other = (*Optimize.c_code)(GC_OID(v61776->arg),
              _oid_(v48367)));
            add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
            v23622 = _oid_(v47292);
            }
          (v23621->arg = v23622);}
        add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      else if (((*Optimize.c_sort)(_oid_(v48370)) == _oid_(Kernel._any)) && 
          ((_inf_equal_type(OBJECT(ClaireType,v4955),GC_OBJECT(ClaireType,v48370->range)) == CTRUE) && 
            (3 <= (CL_INT)Optimize.compiler->safety)))
       { OID  v51070;
        { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
          (v47292->var = v48370);
          (v47292->value = v55285);
          { Let * v23647 = v47292; 
            OID  v23648;
            { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
              { If * v23649 = v47292; 
                OID  v23650;
                { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  (v47292->selector = Core._I_equal);
                  (v47292->args = list::alloc(2,_oid_(v48370),CNULL));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                  v23650 = _oid_(v47292);
                  }
                (v23649->test = v23650);}
              (v47292->arg = v61776->arg);
              (v47292->other = v61776->other);
              add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
              v23648 = _oid_(v47292);
              }
            (v23647->arg = v23648);}
          add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
          v51070 = _oid_(v47292);
          }
        Result = (*Optimize.c_code)(v51070,
          _oid_(v48367));
        }
      else { OID  v55875;
          { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
            (v47292->var = v57728);
            (v47292->value = v55285);
            { Let * v23652 = v47292; 
              OID  v23653;
              { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                { If * v23675 = v47292; 
                  OID  v23676;
                  { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Core._I_equal);
                    (v47292->args = list::alloc(2,_oid_(v57728),CNULL));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v23676 = _oid_(v47292);
                    }
                  (v23675->test = v23676);}
                { If * v23677 = v47292; 
                  OID  v23678;
                  { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                    (v47292->var = v48370);
                    { Let * v23679 = v47292; 
                      OID  v23680;
                      { Cast * v47292 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                        (v47292->arg = _oid_(v57728));
                        (v47292->set_arg = OBJECT(ClaireType,v4955));
                        add_I_property(Kernel.instances,Language._Cast,11,_oid_(v47292));
                        v23680 = _oid_(v47292);
                        }
                      (v23679->value = v23680);}
                    (v47292->arg = v61776->arg);
                    add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                    v23678 = _oid_(v47292);
                    }
                  (v23677->arg = v23678);}
                (v47292->other = (*Optimize.c_code)(GC_OID(v61776->other),
                  _oid_(v48367)));
                add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                v23653 = _oid_(v47292);
                }
              (v23652->arg = v23653);}
            add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
            v55875 = _oid_(v47292);
            }
          Result = (*Optimize.c_code)(v55875,
            _oid_(v48367));
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * c_gc_ask_Let(Let *v61776)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v61776->arg));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_For_Optimize(For *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    Result = infers_from_type2(GC_OBJECT(ClaireType,return_type_any(GC_OID(v61776->arg))),_oid_(v61776));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * infers_from_type2(ClaireType *v48368,OID v61776)
{ GC_BIND;
  { ClaireType *Result ;
    if (equal(_oid_(v48368),_oid_(Kernel.emptySet)) == CTRUE)
     Result = sort_abstract_I_type(Kernel._boolean);
    else if ((CL_INT)Optimize.compiler->safety > 3)
     { if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
       mtformat_module1(Optimize.it,"... c_type(~S) -> ~S - ~S \n",2,list::alloc(3,v61776,
        _oid_(v48368),
        GC_OID(_oid_(sort_abstract_I_type(v48368)))));
      else ;Result = sort_abstract_I_type(v48368);
      }
    else Result = Kernel._any;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_For_Optimize(For *v61776,ClaireClass *v48367)
{ GC_BIND;
  { OID Result = 0;
    { OID  v57706 = GC_OID(v61776->set_arg);
      ClaireBoolean * v48350 = Optimize.OPT->protection;
      CL_INT  v57545 = Optimize.compiler->safety;
      Variable * v29685 = GC_OBJECT(Variable,v61776->var);
      Variable * v48370;
      { { Variable * v47292 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
          (v47292->pname = v29685->pname);
          (v47292->range = v29685->range);
          (v47292->index = v29685->index);
          add_I_property(Kernel.instances,Language._Variable,11,_oid_(v47292));
          v48370 = v47292;
          }
        GC_OBJECT(Variable,v48370);}
      OID  v40236 = GC_OID(substitution_any(GC_OID(v61776->arg),v29685,_oid_(v48370)));
      OID  v18847 = GC_OID(c_inline_arg_ask_any(v57706));
      (Optimize.OPT->protection = CFALSE);
      if (INHERIT(OWNER(v57706),Core._global_variable))
       { if (boolean_I_any(_oid_(OBJECT(global_variable,v57706)->range)) != CTRUE)
         { (v61776->set_arg = OBJECT(global_variable,v57706)->value);
          v57706= GC_OID(OBJECT(global_variable,v57706)->value);
          }
        }
      else if (INHERIT(OWNER(v57706),Language._Select))
       { ClaireType * v55283 = GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v57706)));
        if ((_inf_equal_type(v55283,Kernel._bag) != CTRUE) || 
            (_inf_equal_type(v55283,Kernel._set) == CTRUE))
         { v61776= GC_OBJECT(For,((For *) copy_object(v61776)));
          (v61776->isa = Language._Select);
          }
        }
      else if (INHERIT(OWNER(v57706),Kernel._class))
       { if (((CL_INT)OBJECT(ClaireClass,v57706)->open <= 1) && 
            (boolean_I_any(_oid_(OBJECT(ClaireClass,v57706)->subclass)) != CTRUE))
         { Iteration * v23681 = v61776; 
          OID  v23682;
          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            (v47292->selector = Kernel.instances);
            (v47292->args = list::alloc(1,v57706));
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
            v23682 = _oid_(v47292);
            }
          (v23681->set_arg = v23682);}
        }
      { OID  v55283 = GC_OID((*Optimize.c_type)(GC_OID(v61776->set_arg)));
        ClaireType * v9887 = GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v55283)));
        ClaireType * v9889;
        { { ClaireType * v21091;
            { { OID v40982;{ OID  v22052;
                  { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Kernel.set_I);
                    (v47292->args = list::alloc(1,v57706));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v22052 = _oid_(v47292);
                    }
                  v40982 = (*Optimize.c_type)(v22052);
                  }
                
                v21091=OBJECT(ClaireType,v40982);}
              GC_OBJECT(ClaireType,v21091);}
            v9889 = pmember_type(v21091);
            }
          GC_OBJECT(ClaireType,v9889);}
        if (_inf_equal_type(v9889,v9887) == CTRUE)
         v9887= v9889;
        range_infers_for_Variable(v48370,v9887,OBJECT(ClaireType,v55283));
        (Optimize.compiler->safety = 1);
        v9887= GC_OBJECT(ClaireType,v48370->range);
        (v48370->range = ptype_type(v9887));
        { OID  v48361 = GC_OID(Iterate_I_Iteration(v61776));
          if (equal(_oid_(Kernel._method),_oid_(OWNER(v48361))) != CTRUE)
           { OID  v57449 = GC_OID(restriction_I_property(Language.iterate,list::alloc(3,v55283,
              _oid_(set::alloc(1,_oid_(v48370))),
              _oid_(Kernel._any)),CTRUE));
            if (Kernel._method == OWNER(v57449))
             v48361= v57449;
            }
          (Optimize.compiler->safety = v57545);
          (v48370->range = v9887);
          { OID  v48366;
            { if ((Kernel._method == OWNER(v48361)) && (OBJECT(method,v48361)->inline_ask == CTRUE))
               { if (((CL_INT)Optimize.compiler->safety < 6) && 
                    (BCONTAIN(c_status_any(v40236,Kernel.nil),(OID)(1))))
                 (Optimize.OPT->loop_gc = CTRUE);
                if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
                 mtformat_module1(Optimize.it,"iteration found -> ~S \n",5,list::alloc(1,v48361));
                else ;if (sort_abstract_ask_type(v48370->range) == CTRUE)
                 (v48370->range = CLREAD(Union,v48370->range,t2));
                v48366 = c_inline_method1(OBJECT(method,v48361),list::alloc(3,GC_OID(instruction_copy_any(GC_OID(v61776->set_arg))),
                  _oid_(v48370),
                  v40236),v48367);
                }
              else if (boolean_I_any(v18847) == CTRUE)
               { OID  v43194;
                { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                  (v47292->var = v48370);
                  (v47292->set_arg = v18847);
                  (v47292->arg = v40236);
                  add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
                  v43194 = _oid_(v47292);
                  }
                v48366 = (*Optimize.c_code)(v43194,
                  _oid_(v48367));
                }
              else if ((INHERIT(OWNER(v57706),Language._Call)) && (OBJECT(Call,v57706)->selector == Core.Id))
               v48366 = c_code_multiple_For(v61776,OBJECT(ClaireType,v55283),v48367);
              else { For * v57604;
                  { { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                      (v47292->var = v48370);
                      (v47292->set_arg = c_gc_I_any1(GC_OID(enumerate_code_any(GC_OID(v61776->set_arg),OBJECT(ClaireType,v55283)))));
                      (v47292->arg = (*Optimize.c_code)(v40236,
                        _oid_(Kernel._void)));
                      add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
                      v57604 = v47292;
                      }
                    GC_OBJECT(For,v57604);}
                  if (v48367 == Kernel._any)
                   v48366 = _oid_(v57604);
                  else { Compile_to_C * v47292 = ((Compile_to_C *) GC_OBJECT(Compile_to_C,new_object_class(Optimize._to_C)));
                      (v47292->arg = _oid_(v57604));
                      (v47292->set_arg = v48367);
                      add_I_property(Kernel.instances,Optimize._to_C,11,_oid_(v47292));
                      v48366 = _oid_(v47292);
                      }
                    }
                GC_OID(v48366);}
            if ((Optimize.OPT->protection == CTRUE) && 
                ((0 <= (CL_INT)Optimize.OPT->loop_index) && 
                  ((CL_INT)Optimize.compiler->safety < 6)))
             (Optimize.OPT->loop_gc = CTRUE);
            (Optimize.OPT->protection = ((Optimize.OPT->protection == CTRUE) ? CTRUE : ((v48350 == CTRUE) ? CTRUE : CFALSE)));
            Result = v48366;
            }
          }
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_multiple_For(For *v61776,ClaireType *v55283,ClaireClass *v48367)
{ GC_RESERVE(14);  // v3.0.55 optim !
  { OID Result = 0;
    { Variable * v48370 = GC_OBJECT(Variable,v61776->var);
      OID  v57706 = GC_OID((*(OBJECT(Call,v61776->set_arg)->args))[1]);
      Variable * v57728 = GC_OBJECT(Variable,Variable_I_symbol(append_symbol(v48370->pname,_string_("test")),v61776->var->index,v55283));
      Let * v48362;
      { { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
          (v47292->var = v57728);
          (v47292->value = v57706);
          { Let * v23707 = v47292; 
            OID  v23708;
            { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
              (v47292->var = v61776->var);
              (v47292->set_arg = enumerate_code_any(v57706,v55283));
              (v47292->arg = v61776->arg);
              add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
              v23708 = _oid_(v47292);
              }
            (v23707->arg = v23708);}
          add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
          v48362 = v47292;
          }
        GC_OBJECT(Let,v48362);}
      if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
       mtformat_module1(Optimize.it,"`GREEN ---- note: use an expended iteration for {~S} \n",0,list::alloc(1,_oid_(v61776)));
      else ;{ CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v48366);
        for (START(Language.iterate->restrictions); NEXT(v48366);)
        { GC_LOOP;
          if ((_inf_equalt_class(domain_I_restriction(OBJECT(restriction,v48366)),v55283) == CTRUE) && 
              ((_inf_equalt_class(domain_I_restriction(OBJECT(restriction,v48366)),Kernel._collection) == CTRUE) && 
                ((OBJECT(method,v48366)->inline_ask == CTRUE) && 
                  (belong_to(_oid_(v48370),(*(OBJECT(restriction,v48366)->domain))[2]) == CTRUE))))
           { Variable * v28526;
            { { Variable * v47292 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                (v47292->pname = v48370->pname);
                (v47292->range = v48370->range);
                (v47292->index = v48370->index);
                add_I_property(Kernel.instances,Language._Variable,11,_oid_(v47292));
                v28526 = v47292;
                }
              GC_OBJECT(Variable,v28526);}
            OID  v40236 = GC_OID(substitution_any(GC_OID(v61776->arg),v48370,_oid_(v28526)));
            { Let * v23709 = v48362; 
              OID  v23710;
              { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                { If * v23711 = v47292; 
                  OID  v23712;
                  { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Kernel._Z);
                    (v47292->args = list::alloc(2,_oid_(v57728),(*(OBJECT(restriction,v48366)->domain))[1]));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v23712 = _oid_(v47292);
                    }
                  (v23711->test = v23712);}
                { If * v23713 = v47292; 
                  OID  v23714;
                  { if (((CL_INT)Optimize.compiler->safety < 6) && 
                        (BCONTAIN(c_status_any(GC_OID(v61776->arg),Kernel.nil),(OID)(1))))
                     (Optimize.OPT->loop_gc = CTRUE);
                    if (sort_abstract_ask_type(v28526->range) == CTRUE)
                     (v28526->range = CLREAD(Union,v48370->range,t2));
                    v23714 = c_inline_method1(OBJECT(method,v48366),GC_OBJECT(list,list::alloc(3,_oid_(v57728),
                      _oid_(v28526),
                      v40236)),v48367);
                    }
                  (v23713->arg = v23714);}
                (v47292->other = v48362->arg);
                add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                v23710 = _oid_(v47292);
                }
              (v23709->arg = v23710);}
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      Result = (*Optimize.c_code)(_oid_(v48362),
        _oid_(v48367));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * c_gc_ask_Iteration(Iteration *v61776)
{ POP_SIGNAL; return (CTRUE);}

ClaireBoolean * c_gc_ask_Ffor1(iClaire_Ffor *v61776)
{ POP_SIGNAL; return (CTRUE);}

ClaireType * c_type_Iteration_Optimize(Iteration *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    { OID  v55283 = GC_OID((*Optimize.c_type)(GC_OID(v61776->set_arg)));
      range_infers_for_Variable(GC_OBJECT(Variable,v61776->var),GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v55283))),OBJECT(ClaireType,v55283));
      Result = ((get_property(Kernel.of,v61776) != CNULL) ?
        param_I_class((((INHERIT(v61776->isa,Language._Select)) || 
            (INHERIT(v61776->isa,Language._Image))) ?
          Kernel._set :
          Kernel._list ),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.of)(_oid_(v61776))))) :
        nth_class1((((INHERIT(v61776->isa,Language._Select)) || 
            (INHERIT(v61776->isa,Language._Image))) ?
          Kernel._set :
          Kernel._list ),GC_OBJECT(ClaireType,(((INHERIT(v61776->isa,Language._Select)) || 
            (INHERIT(v61776->isa,Language._Lselect))) ?
          pmember_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->set_arg))))) :
          ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->arg)))) ))) );
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Iteration_Optimize(Iteration *v61776)
{ GC_BIND;
  { OID Result = 0;
    { OID  v57706 = GC_OID(v61776->set_arg);
      OID  v55283 = GC_OID((*Optimize.c_type)(v57706));
      if (INHERIT(v61776->isa,Language._For))
       Result = (*Optimize.c_code)(_oid_(v61776),
        _oid_(Kernel._any));
      else if ((INHERIT(v61776->isa,Language._Collect)) && (_inf_equal_type(OBJECT(ClaireType,v55283),Kernel._bag) == CTRUE))
       { (Optimize.OPT->allocation = CTRUE);
        range_infers_for_Variable(GC_OBJECT(Variable,v61776->var),GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v55283))),OBJECT(ClaireType,v55283));
        { ClaireType * v57737 = GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->arg)))));
          Collect * v48372;
          { { Collect * v47292 = ((Collect *) GC_OBJECT(Collect,new_object_class(Language._Collect)));
              (v47292->var = v61776->var);
              (v47292->set_arg = c_gc_I_any1(GC_OID(c_strict_code_any(v57706,Kernel._bag))));
              (v47292->arg = (*Optimize.c_code)(GC_OID(v61776->arg),
                _oid_(Kernel._any)));
              add_I_property(Kernel.instances,Language._Collect,11,_oid_(v47292));
              v48372 = v47292;
              }
            GC_OBJECT(Collect,v48372);}
          if (v57737 == Kernel._void)
           (*Optimize.Cerror)(_string_("[205] use of void expression ~S in ~S"),
            GC_OID(v61776->arg),
            _oid_(v61776));
          if (get_property(Kernel.of,v61776) != CNULL)
           { if (((CL_INT)Optimize.compiler->safety > 4) || 
                (_inf_equal_type(v57737,GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.of)(_oid_(v61776))))) == CTRUE))
             { update_property(Kernel.of,
                v48372,
                5,
                Kernel._object,
                GC_OID((*Kernel.of)(_oid_(v61776))));
              Result = _oid_(v48372);
              }
            else { warn_void();
                if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
                 mtformat_module1(Optimize.it,"`BLUE unsafe typed collect (~S): ~S not in ~S [261]\n",2,list::alloc(3,_oid_(v61776),
                  GC_OID((*Optimize.c_type)(GC_OID(v61776->arg))),
                  GC_OID((*Kernel.of)(_oid_(v61776)))));
                else ;{ OID  v43236;
                  { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Core.check_in);
                    (v47292->args = list::alloc(3,_oid_(v48372),
                      _oid_(Kernel._list),
                      GC_OID((*Kernel.of)(_oid_(v61776)))));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v43236 = _oid_(v47292);
                    }
                  Result = (*Optimize.c_code)(v43236,
                    _oid_(Kernel._list));
                  }
                }
              }
          else Result = _oid_(v48372);
            }
        }
      else { OID  v21661;
          if (INHERIT(v61776->isa,Language._Image))
           v21661 = _oid_(set::empty());
          else v21661 = _oid_(list::empty());
            Variable * v48370;
          { { CL_INT  v44197;
              { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                v44197 = 0;
                }
              v48370 = Variable_I_symbol(append_symbol(v61776->var->pname,_string_("_bag")),v44197,((INHERIT(v61776->isa,Language._Image)) ?
                Kernel._set :
                Kernel._list ));
              }
            GC_OBJECT(Variable,v48370);}
          if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
           mtformat_module1(Optimize.it,"(~S:~S) v = ~S range = ~S (arg:~S)\n",5,list::alloc(5,_oid_(v61776),
            _oid_(v61776->isa),
            GC_OID(_oid_(v61776->var)),
            GC_OID(_oid_(v61776->var->range)),
            GC_OID(v61776->arg)));
          else ;if (get_property(Kernel.of,v61776) != CNULL)
           { ClaireType * v45536 = GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->arg))));
            if ((_inf_equal_type(ptype_type(v45536),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.of)(_oid_(v61776))))) != CTRUE) && 
                ((CL_INT)Optimize.compiler->safety <= 4))
             { warn_void();
              if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
               mtformat_module1(Optimize.it,"`BLUE unsafe bag construction (~S) : a ~S is not a ~S [262]\n",2,list::alloc(3,GC_OID(_oid_(v61776->var)),
                _oid_(v45536),
                GC_OID((*Kernel.of)(_oid_(v61776)))));
              else ;}
            (*Kernel.cast_I)(v21661,
              GC_OID((*Kernel.of)(_oid_(v61776))));
            (v48370->range = param_I_class(GC_OBJECT(ClaireClass,((ClaireClass *) v48370->range)),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.of)(_oid_(v61776))))));
            }
          else if (Kernel._set == OWNER(v21661))
             { Set * v47292 = ((Set *) GC_OBJECT(Set,new_object_class(Language._Set)));
              (v47292->of = Kernel.emptySet);
              add_I_property(Kernel.instances,Language._Set,11,_oid_(v47292));
              v21661 = _oid_(v47292);
              }
            else { List * v47292 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                (v47292->of = Kernel.emptySet);
                add_I_property(Kernel.instances,Language._List,11,_oid_(v47292));
                v21661 = _oid_(v47292);
                }
              { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
            (v47292->var = v48370);
            (v47292->value = v21661);
            { Let * v24390 = v47292; 
              OID  v24391;
              { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                { Do * v24392 = v47292; 
                  list * v24393;
                  { OID v_bag;
                    GC_ANY(v24393= list::empty(Kernel.emptySet));
                    { { OID  v49002;
                        { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                          (v47292->var = v61776->var);
                          (v47292->set_arg = v57706);
                          { Iteration * v24396 = v47292; 
                            OID  v24397;
                            { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                              (v47292->selector = Kernel.add_I);
                              (v47292->args = list::alloc(2,_oid_(v48370),GC_OID(v61776->arg)));
                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                              v24397 = _oid_(v47292);
                              }
                            (v24396->arg = v24397);}
                          add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
                          v49002 = _oid_(v47292);
                          }
                        v_bag = (*Optimize.c_code)(v49002,
                          _oid_(Kernel._any));
                        }
                      GC_OID(v_bag);}
                    ((list *) v24393)->addFast((OID)v_bag);
                    if (Optimize.OPT->online_ask != CTRUE)
                     { (Optimize.OPT->protection = CTRUE);
                      { Compile_to_protect * v47292 = ((Compile_to_protect *) GC_OBJECT(Compile_to_protect,new_object_class(Optimize._to_protect)));
                        (v47292->arg = _oid_(v48370));
                        add_I_property(Kernel.instances,Optimize._to_protect,11,_oid_(v47292));
                        v_bag = _oid_(v47292);
                        }
                      }
                    else v_bag = _oid_(v48370);
                      ((list *) v24393)->addFast((OID)v_bag);}
                  (v24392->args = v24393);}
                add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                v24391 = _oid_(v47292);
                }
              (v24390->arg = v24391);}
            add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
            Result = _oid_(v47292);
            }
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Select_Optimize(Select *v61776)
{ POP_SIGNAL; return (c_code_select_Iteration(v61776,Kernel._set));}

OID  c_code_Lselect_Optimize(Lselect *v61776)
{ POP_SIGNAL; return (c_code_select_Iteration(v61776,Kernel._list));}

OID  c_code_select_Iteration(Iteration *v61776,ClaireClass *v48372)
{ GC_BIND;
  { OID Result = 0;
    { OID  v57706 = GC_OID(v61776->set_arg);
      OID  v55283 = GC_OID((*Optimize.c_type)(v57706));
      OID  v57701 = GC_OID(enumerate_code_any(v57706,OBJECT(ClaireType,v55283)));
      bag * v21661;
      if (v48372 == Kernel._set)
       v21661 = set::empty();
      else v21661 = list::empty();
        Variable * v57727;
      { { CL_INT  v8452;
          { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
            v8452 = 0;
            }
          v57727 = Variable_I_symbol(append_symbol(v61776->var->pname,_string_("_in")),v8452,Kernel._bag);
          }
        GC_OBJECT(Variable,v57727);}
      Variable * v57728;
      { { CL_INT  v9413;
          { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
            v9413 = 0;
            }
          v57728 = Variable_I_symbol(append_symbol(v61776->var->pname,_string_("_out")),v9413,v48372);
          }
        GC_OBJECT(Variable,v57728);}
      if (get_property(Kernel.of,v61776) != CNULL)
       { ClaireType * v45536 = GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v55283)));
        if ((_inf_equal_type(ptype_type(v45536),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.of)(_oid_(v61776))))) != CTRUE) && 
            ((CL_INT)Optimize.compiler->safety <= 4))
         { warn_void();
          if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
           mtformat_module1(Optimize.it,"`BLUE unsafe bag construction (~S) : a ~S is not a ~S [262]\n",2,list::alloc(3,GC_OID(_oid_(v61776->var)),
            _oid_(v45536),
            GC_OID((*Kernel.of)(_oid_(v61776)))));
          else ;}
        _oid_((INHERIT(v21661->isa,Kernel._list) ?
         (ClaireObject *) cast_I_list1((list *) OBJECT(list,_oid_(v21661)),OBJECT(ClaireType,GC_OID((*Kernel.of)(_oid_(v61776))))) : 
         (ClaireObject *)  cast_I_set1((set *) OBJECT(set,_oid_(v21661)),OBJECT(ClaireType,GC_OID((*Kernel.of)(_oid_(v61776)))))));
        (v57728->range = param_I_class(v48372,GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.of)(_oid_(v61776))))));
        Result = inner_select_Iteration(v61776,_oid_(v57728),v57706,_oid_(v21661));
        }
      else if (_inf_equal_type(OBJECT(ClaireType,v55283),v48372) == CTRUE)
       { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
        (v47292->var = v57727);
        (v47292->value = v57701);
        { Let * v24422 = v47292; 
          OID  v24423;
          { OID  v12296;
            { Compile_C_cast * v47292 = ((Compile_C_cast *) GC_OBJECT(Compile_C_cast,new_object_class(Optimize._C_cast)));
              { Compile_to_C * v24425 = v47292; 
                OID  v24426;
                { OID  v15179;
                  { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Kernel.empty);
                    (v47292->args = list::alloc(1,_oid_(v57727)));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v15179 = _oid_(v47292);
                    }
                  v24426 = (*Optimize.c_code)(v15179,
                    _oid_(Kernel._bag));
                  }
                (v24425->arg = v24426);}
              (v47292->set_arg = v48372);
              add_I_property(Kernel.instances,Optimize._C_cast,11,_oid_(v47292));
              v12296 = _oid_(v47292);
              }
            v24423 = inner_select_Iteration(v61776,_oid_(v57728),_oid_(v57727),v12296);
            }
          (v24422->arg = v24423);}
        add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      else { OID  v16140;
          if (v48372 == Kernel._set)
           { Set * v47292 = ((Set *) GC_OBJECT(Set,new_object_class(Language._Set)));
            (v47292->of = Kernel.emptySet);
            add_I_property(Kernel.instances,Language._Set,11,_oid_(v47292));
            v16140 = _oid_(v47292);
            }
          else { List * v47292 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
              (v47292->of = Kernel.emptySet);
              add_I_property(Kernel.instances,Language._List,11,_oid_(v47292));
              v16140 = _oid_(v47292);
              }
            Result = inner_select_Iteration(v61776,_oid_(v57728),v57706,v16140);
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  inner_select_Iteration(Iteration *v61776,OID v57728,OID v57706,OID v21661)
{ GC_BIND;
  { OID Result = 0;
    { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
      store_object(v47292,
        2,
        Kernel._object,
        v57728,
        CFALSE);
      (v47292->value = v21661);
      { Let * v24450 = v47292; 
        OID  v24451;
        { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
          { Do * v24452 = v47292; 
            list * v24453;
            { OID v_bag;
              GC_ANY(v24453= list::empty(Kernel.emptySet));
              { { OID  v41126;
                  { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                    (v47292->var = v61776->var);
                    (v47292->set_arg = v57706);
                    { Iteration * v24457 = v47292; 
                      OID  v24458;
                      { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                        (v47292->test = v61776->arg);
                        { If * v24459 = v47292; 
                          OID  v24460;
                          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                            (v47292->selector = Kernel.add_I);
                            (v47292->args = list::alloc(2,v57728,GC_OID(_oid_(v61776->var))));
                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                            v24460 = _oid_(v47292);
                            }
                          (v24459->arg = v24460);}
                        add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                        (v47292->other = Kernel.cfalse);
                        v24458 = _oid_(v47292);
                        }
                      (v24457->arg = v24458);}
                    add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
                    v41126 = _oid_(v47292);
                    }
                  v_bag = (*Optimize.c_code)(v41126,
                    _oid_(Kernel._any));
                  }
                GC_OID(v_bag);}
              ((list *) v24453)->addFast((OID)v_bag);
              if (Optimize.OPT->online_ask != CTRUE)
               { (Optimize.OPT->protection = CTRUE);
                { Compile_to_protect * v47292 = ((Compile_to_protect *) GC_OBJECT(Compile_to_protect,new_object_class(Optimize._to_protect)));
                  (v47292->arg = v57728);
                  add_I_property(Kernel.instances,Optimize._to_protect,11,_oid_(v47292));
                  v_bag = _oid_(v47292);
                  }
                }
              else v_bag = v57728;
                ((list *) v24453)->addFast((OID)v_bag);}
            (v24452->args = v24453);}
          add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
          v24451 = _oid_(v47292);
          }
        (v24450->arg = v24451);}
      add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Exists_Optimize(Exists *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    { OID  v55283 = GC_OID((*Optimize.c_type)(GC_OID(v61776->set_arg)));
      range_infers_for_Variable(GC_OBJECT(Variable,v61776->var),GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v55283))),OBJECT(ClaireType,v55283));
      if (v61776->other == CNULL)
       Result = extends_type(GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v55283))));
      else Result = Kernel._boolean;
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Exists_Optimize(Exists *v61776,ClaireClass *v48367)
{ GC_BIND;
  { OID Result = 0;
    { OID  v55283 = GC_OID((*Optimize.c_type)(GC_OID(v61776->set_arg)));
      range_infers_for_Variable(GC_OBJECT(Variable,v61776->var),GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v55283))),OBJECT(ClaireType,v55283));
      if (v61776->other == Kernel.ctrue)
       { OID  v1537;
        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          (v47292->selector = Core.NOT);
          { Call * v24482 = v47292; 
            list * v24483;
            { OID v_bag;
              GC_ANY(v24483= list::empty(Kernel.emptySet));
              { { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                  (v47292->var = v61776->var);
                  (v47292->set_arg = v61776->set_arg);
                  { Iteration * v24484 = v47292; 
                    OID  v24485;
                    { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                      { If * v24486 = v47292; 
                        OID  v24487;
                        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          (v47292->selector = Core.NOT);
                          (v47292->args = list::alloc(1,GC_OID(v61776->arg)));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                          v24487 = _oid_(v47292);
                          }
                        (v24486->test = v24487);}
                      { If * v24488 = v47292; 
                        OID  v24489;
                        { Return * v47292 = ((Return *) GC_OBJECT(Return,new_object_class(Language._Return)));
                          (v47292->arg = Kernel.ctrue);
                          add_I_property(Kernel.instances,Language._Return,11,_oid_(v47292));
                          v24489 = _oid_(v47292);
                          }
                        (v24488->arg = v24489);}
                      add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                      (v47292->other = Kernel.cfalse);
                      v24485 = _oid_(v47292);
                      }
                    (v24484->arg = v24485);}
                  add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
                  v_bag = _oid_(v47292);
                  }
                GC_OID(v_bag);}
              ((list *) v24483)->addFast((OID)v_bag);}
            (v24482->args = v24483);}
          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
          v1537 = _oid_(v47292);
          }
        Result = (*Optimize.c_code)(v1537,
          _oid_(v48367));
        }
      else if (v61776->other == CNULL)
       { Variable * v48370;
        { { CL_INT  v10186;
            { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
              v10186 = 0;
              }
            v48370 = Variable_I_symbol(append_symbol(v61776->var->pname,_string_("_some")),v10186,GC_OBJECT(ClaireType,extends_type(GC_OBJECT(ClaireType,v61776->var->range))));
            }
          GC_OBJECT(Variable,v48370);}
        { OID  v31328;
          { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
            (v47292->var = v48370);
            (v47292->value = CNULL);
            { Let * v24513 = v47292; 
              OID  v24514;
              { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                { Do * v24515 = v47292; 
                  list * v24516;
                  { OID v_bag;
                    GC_ANY(v24516= list::empty(Kernel.emptySet));
                    { { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                        (v47292->var = v61776->var);
                        (v47292->set_arg = v61776->set_arg);
                        { Iteration * v24517 = v47292; 
                          OID  v24518;
                          { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                            (v47292->test = v61776->arg);
                            { If * v24519 = v47292; 
                              OID  v24520;
                              { Return * v47292 = ((Return *) GC_OBJECT(Return,new_object_class(Language._Return)));
                                { Return * v24521 = v47292; 
                                  OID  v24543;
                                  { Assign * v47292 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                    (v47292->var = _oid_(v48370));
                                    (v47292->arg = _oid_(v61776->var));
                                    add_I_property(Kernel.instances,Language._Assign,11,_oid_(v47292));
                                    v24543 = _oid_(v47292);
                                    }
                                  (v24521->arg = v24543);}
                                add_I_property(Kernel.instances,Language._Return,11,_oid_(v47292));
                                v24520 = _oid_(v47292);
                                }
                              (v24519->arg = v24520);}
                            add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                            (v47292->other = Kernel.cfalse);
                            v24518 = _oid_(v47292);
                            }
                          (v24517->arg = v24518);}
                        add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
                        v_bag = _oid_(v47292);
                        }
                      GC_OID(v_bag);}
                    ((list *) v24516)->addFast((OID)v_bag);
                    ((list *) v24516)->addFast((OID)_oid_(v48370));}
                  (v24515->args = v24516);}
                add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                v24514 = _oid_(v47292);
                }
              (v24513->arg = v24514);}
            add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
            v31328 = _oid_(v47292);
            }
          Result = (*Optimize.c_code)(v31328,
            _oid_(v48367));
          }
        }
      else { OID  v62080;
          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            (v47292->selector = Kernel.boolean_I);
            { Call * v24545 = v47292; 
              list * v24546;
              { OID v_bag;
                GC_ANY(v24546= list::empty(Kernel.emptySet));
                { { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                    (v47292->var = v61776->var);
                    (v47292->set_arg = v61776->set_arg);
                    { Iteration * v24547 = v47292; 
                      OID  v24548;
                      { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                        (v47292->test = v61776->arg);
                        { If * v24549 = v47292; 
                          OID  v24550;
                          { Return * v47292 = ((Return *) GC_OBJECT(Return,new_object_class(Language._Return)));
                            (v47292->arg = Kernel.ctrue);
                            add_I_property(Kernel.instances,Language._Return,11,_oid_(v47292));
                            v24550 = _oid_(v47292);
                            }
                          (v24549->arg = v24550);}
                        add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                        (v47292->other = Kernel.cfalse);
                        v24548 = _oid_(v47292);
                        }
                      (v24547->arg = v24548);}
                    add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
                    v_bag = _oid_(v47292);
                    }
                  GC_OID(v_bag);}
                ((list *) v24546)->addFast((OID)v_bag);}
              (v24545->args = v24546);}
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
            v62080 = _oid_(v47292);
            }
          Result = (*Optimize.c_code)(v62080,
            _oid_(v48367));
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Image_Optimize(Image *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    { ClaireType * v55283 = GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->set_arg)))));
      range_infers_for_Variable(GC_OBJECT(Variable,v61776->var),GC_OBJECT(ClaireType,pmember_type(v55283)),v55283);
      Result = ((((v61776->of == (NULL)) ? CTRUE : CFALSE) != CTRUE) ?
        param_I_class(Kernel._set,GC_OBJECT(ClaireType,v61776->of)) :
        nth_class1(Kernel._set,GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->arg))))) );
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Select_Optimize(Select *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    { OID  v55283 = GC_OID((*Optimize.c_type)(GC_OID(v61776->set_arg)));
      range_infers_for_Variable(GC_OBJECT(Variable,v61776->var),GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v55283))),OBJECT(ClaireType,v55283));
      Result = ((((v61776->of == (NULL)) ? CTRUE : CFALSE) != CTRUE) ?
        param_I_class(Kernel._set,GC_OBJECT(ClaireType,v61776->of)) :
        nth_class1(Kernel._set,GC_OBJECT(ClaireType,pmember_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->set_arg))))))) );
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Lselect_Optimize(Lselect *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    { OID  v55283 = GC_OID((*Optimize.c_type)(GC_OID(v61776->set_arg)));
      range_infers_for_Variable(GC_OBJECT(Variable,v61776->var),GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v55283))),OBJECT(ClaireType,v55283));
      Result = ((((v61776->of == (NULL)) ? CTRUE : CFALSE) != CTRUE) ?
        param_I_class(Kernel._list,GC_OBJECT(ClaireType,v61776->of)) :
        nth_class1(Kernel._list,GC_OBJECT(ClaireType,pmember_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->set_arg))))))) );
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_While_Optimize(While *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    Result = infers_from_type2(GC_OBJECT(ClaireType,return_type_any(GC_OID(v61776->arg))),_oid_(v61776));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_While_Optimize(While *v61776,ClaireClass *v48367)
{ GC_BIND;
  { OID Result = 0;
    { ClaireBoolean * v48350 = Optimize.OPT->protection;
      (Optimize.OPT->protection = CFALSE);
      { While * v48366;
        { { While * v47292 = ((While *) GC_OBJECT(While,new_object_class(Language._While)));
            (v47292->test = c_boolean_any(GC_OID(v61776->test)));
            (v47292->arg = (*Optimize.c_code)(GC_OID(v61776->arg),
              _oid_(Kernel._void)));
            (v47292->other = v61776->other);
            add_I_property(Kernel.instances,Language._While,11,_oid_(v47292));
            v48366 = v47292;
            }
          GC_OBJECT(While,v48366);}
        if ((Optimize.OPT->protection == CTRUE) && 
            (0 <= (CL_INT)Optimize.OPT->loop_index))
         (Optimize.OPT->loop_gc = CTRUE);
        (Optimize.OPT->protection = ((Optimize.OPT->protection == CTRUE) ? CTRUE : ((v48350 == CTRUE) ? CTRUE : CFALSE)));
        if ((v48367 != Kernel._void) && 
            (v48367 != Kernel._any))
         { if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
           mtformat_module1(Optimize.it,"... insert a to_C with s = ~S for ~S \n",5,list::alloc(2,_oid_(v48367),_oid_(v61776)));
          else ;{ Compile_to_C * v47292 = ((Compile_to_C *) GC_OBJECT(Compile_to_C,new_object_class(Optimize._to_C)));
            (v47292->arg = _oid_(v48366));
            (v47292->set_arg = v48367);
            add_I_property(Kernel.instances,Optimize._to_C,11,_oid_(v47292));
            Result = _oid_(v47292);
            }
          }
        else Result = _oid_(v48366);
          }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_type_Ffor1_Optimize(iClaire_Ffor *v61776)
{ POP_SIGNAL; return (_oid_(Kernel._list));}

OID  c_code_Ffor1_Optimize(iClaire_Ffor *v61776,ClaireClass *v57700)
{ GC_BIND;
  { OID Result = 0;
    { OID  v31009;
      { if (unix_ask_void1() != CTRUE)
         { Variable * v17948 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._list));
          Variable * v6028 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Core._ffor_error));
          Variable * v20115 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._any));
          Variable * v48360 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._list));
          Variable * v48357 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._any));
          Variable * v48358 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._any));
          Variable * v29685 = GC_OBJECT(Variable,v61776->var);
          Variable * v48370;
          { { Variable * v47292 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              (v47292->pname = v29685->pname);
              (v47292->range = v29685->range);
              (v47292->index = v29685->index);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(v47292));
              v48370 = v47292;
              }
            GC_OBJECT(Variable,v48370);}
          OID  v40236 = GC_OID(substitution_any(GC_OID(v61776->arg),v29685,_oid_(v48370)));
          { OID  v21342;
            { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
              (v47292->var = v48360);
              { Let * v24639 = v47292; 
                OID  v24640;
                { Collect * v47292 = ((Collect *) GC_OBJECT(Collect,new_object_class(Language._Collect)));
                  (v47292->var = v48357);
                  (v47292->set_arg = v61776->set_arg);
                  (v47292->arg = _oid_(v48357));
                  add_I_property(Kernel.instances,Language._Collect,11,_oid_(v47292));
                  v24640 = _oid_(v47292);
                  }
                (v24639->value = v24640);}
              { Let * v24641 = v47292; 
                OID  v24642;
                { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                  (v47292->var = v17948);
                  { Let * v24643 = v47292; 
                    OID  v24644;
                    { List * v47292 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                      (v47292->of = Kernel._any);
                      add_I_property(Kernel.instances,Language._List,11,_oid_(v47292));
                      v24644 = _oid_(v47292);
                      }
                    (v24643->value = v24644);}
                  { Let * v24645 = v47292; 
                    OID  v24667;
                    { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                      (v47292->var = v48370);
                      (v47292->value = CNULL);
                      { Let * v24668 = v47292; 
                        OID  v24669;
                        { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                          { Do * v24670 = v47292; 
                            list * v24671;
                            { OID v_bag;
                              GC_ANY(v24671= list::empty(Kernel.emptySet));
                              { { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                                  (v47292->var = v48358);
                                  (v47292->set_arg = _oid_(v48360));
                                  { Iteration * v24672 = v47292; 
                                    OID  v24673;
                                    { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                      { Do * v24674 = v47292; 
                                        list * v24677;
                                        { OID v_bag;
                                          GC_ANY(v24677= list::empty(Kernel.emptySet));
                                          { { Assign * v47292 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                              (v47292->var = _oid_(v48370));
                                              (v47292->arg = _oid_(v48358));
                                              add_I_property(Kernel.instances,Language._Assign,11,_oid_(v47292));
                                              v_bag = _oid_(v47292);
                                              }
                                            GC_OID(v_bag);}
                                          ((list *) v24677)->addFast((OID)v_bag);
                                          { { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                              (v47292->var = v20115);
                                              (v47292->value = CNULL);
                                              { Let * v24678 = v47292; 
                                                OID  v25349;
                                                { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                  { Do * v25350 = v47292; 
                                                    list * v25351;
                                                    { OID v_bag;
                                                      GC_ANY(v25351= list::empty(Kernel.emptySet));
                                                      { { Assign * v47292 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                                          (v47292->var = _oid_(v20115));
                                                          { Assign * v25352 = v47292; 
                                                            OID  v25353;
                                                            { ClaireHandle * v47292 = ((ClaireHandle *) GC_OBJECT(ClaireHandle,new_object_class(Language._Handle)));
                                                              (v47292->test = _oid_(Kernel._any));
                                                              (v47292->arg = v40236);
                                                              { ClaireHandle * v25354 = v47292; 
                                                                OID  v25355;
                                                                { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                  (v47292->var = v6028);
                                                                  { Let * v25356 = v47292; 
                                                                    OID  v25357;
                                                                    { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                      (v47292->selector = Core.new_I);
                                                                      (v47292->args = list::alloc(1,_oid_(Core._ffor_error)));
                                                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                      v25357 = _oid_(v47292);
                                                                      }
                                                                    (v25356->value = v25357);}
                                                                  { Let * v25358 = v47292; 
                                                                    OID  v25380;
                                                                    { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                      { Do * v25381 = v47292; 
                                                                        list * v25382;
                                                                        { OID v_bag;
                                                                          GC_ANY(v25382= list::empty(Kernel.emptySet));
                                                                          { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                              (v47292->selector = Kernel.put);
                                                                              { Call * v25383 = v47292; 
                                                                                list * v25384;
                                                                                { OID v_bag;
                                                                                  GC_ANY(v25384= list::empty(Kernel.emptySet));
                                                                                  ((list *) v25384)->addFast((OID)_oid_(Core.childstr));
                                                                                  ((list *) v25384)->addFast((OID)_oid_(v6028));
                                                                                  { { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                      { Do * v25385 = v47292; 
                                                                                        list * v25386;
                                                                                        { OID v_bag;
                                                                                          GC_ANY(v25386= list::empty(Kernel.emptySet));
                                                                                          { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                              (v47292->selector = Core.print_in_string);
                                                                                              (v47292->args = list::alloc(1,_oid_(ClEnv)));
                                                                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                              v_bag = _oid_(v47292);
                                                                                              }
                                                                                            GC_OID(v_bag);}
                                                                                          ((list *) v25386)->addFast((OID)v_bag);
                                                                                          { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                              (v47292->selector = Kernel.print);
                                                                                              { Call * v25387 = v47292; 
                                                                                                list * v25389;
                                                                                                { OID v_bag;
                                                                                                  GC_ANY(v25389= list::empty(Kernel.emptySet));
                                                                                                  { { Call_star * v47292 = ((Call_star *) GC_OBJECT(Call_star,new_object_class(Language._Call_star)));
                                                                                                      (v47292->selector = Kernel.exception_I);
                                                                                                      (v47292->args = list::alloc(1,_oid_(ClEnv)));
                                                                                                      add_I_property(Kernel.instances,Language._Call_star,11,_oid_(v47292));
                                                                                                      v_bag = _oid_(v47292);
                                                                                                      }
                                                                                                    GC_OID(v_bag);}
                                                                                                  ((list *) v25389)->addFast((OID)v_bag);}
                                                                                                (v25387->args = v25389);}
                                                                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                              v_bag = _oid_(v47292);
                                                                                              }
                                                                                            GC_OID(v_bag);}
                                                                                          ((list *) v25386)->addFast((OID)v_bag);
                                                                                          { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                              (v47292->selector = Core.end_of_string);
                                                                                              (v47292->args = list::alloc(1,_oid_(ClEnv)));
                                                                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                              v_bag = _oid_(v47292);
                                                                                              }
                                                                                            GC_OID(v_bag);}
                                                                                          ((list *) v25386)->addFast((OID)v_bag);}
                                                                                        (v25385->args = v25386);}
                                                                                      add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                                                                      v_bag = _oid_(v47292);
                                                                                      }
                                                                                    GC_OID(v_bag);}
                                                                                  ((list *) v25384)->addFast((OID)v_bag);}
                                                                                (v25383->args = v25384);}
                                                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                              v_bag = _oid_(v47292);
                                                                              }
                                                                            GC_OID(v_bag);}
                                                                          ((list *) v25382)->addFast((OID)v_bag);
                                                                          { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                              (v47292->selector = Kernel.put);
                                                                              { Call * v25390 = v47292; 
                                                                                list * v25411;
                                                                                { OID v_bag;
                                                                                  GC_ANY(v25411= list::empty(Kernel.emptySet));
                                                                                  ((list *) v25411)->addFast((OID)_oid_(Core.childpid));
                                                                                  ((list *) v25411)->addFast((OID)_oid_(v6028));
                                                                                  { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                      (v47292->selector = Kernel.getpid);
                                                                                      (v47292->args = list::alloc(1,_oid_(ClEnv)));
                                                                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                      v_bag = _oid_(v47292);
                                                                                      }
                                                                                    GC_OID(v_bag);}
                                                                                  ((list *) v25411)->addFast((OID)v_bag);}
                                                                                (v25390->args = v25411);}
                                                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                              v_bag = _oid_(v47292);
                                                                              }
                                                                            GC_OID(v_bag);}
                                                                          ((list *) v25382)->addFast((OID)v_bag);
                                                                          ((list *) v25382)->addFast((OID)_oid_(v6028));}
                                                                        (v25381->args = v25382);}
                                                                      add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                                                      v25380 = _oid_(v47292);
                                                                      }
                                                                    (v25358->arg = v25380);}
                                                                  add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                                                  v25355 = _oid_(v47292);
                                                                  }
                                                                (v25354->other = v25355);}
                                                              add_I_property(Kernel.instances,Language._Handle,11,_oid_(v47292));
                                                              v25353 = _oid_(v47292);
                                                              }
                                                            (v25352->arg = v25353);}
                                                          add_I_property(Kernel.instances,Language._Assign,11,_oid_(v47292));
                                                          v_bag = _oid_(v47292);
                                                          }
                                                        GC_OID(v_bag);}
                                                      ((list *) v25351)->addFast((OID)v_bag);
                                                      { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                          (v47292->selector = Kernel.add_I);
                                                          (v47292->args = list::alloc(2,_oid_(v17948),_oid_(v20115)));
                                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                          v_bag = _oid_(v47292);
                                                          }
                                                        GC_OID(v_bag);}
                                                      ((list *) v25351)->addFast((OID)v_bag);}
                                                    (v25350->args = v25351);}
                                                  add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                                  v25349 = _oid_(v47292);
                                                  }
                                                (v24678->arg = v25349);}
                                              add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                              v_bag = _oid_(v47292);
                                              }
                                            GC_OID(v_bag);}
                                          ((list *) v24677)->addFast((OID)v_bag);}
                                        (v24674->args = v24677);}
                                      add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                      v24673 = _oid_(v47292);
                                      }
                                    (v24672->arg = v24673);}
                                  add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
                                  v_bag = _oid_(v47292);
                                  }
                                GC_OID(v_bag);}
                              ((list *) v24671)->addFast((OID)v_bag);
                              { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                  (v47292->selector = Kernel.cast_I);
                                  (v47292->args = list::alloc(2,_oid_(v17948),_oid_(Kernel.emptySet)));
                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                  v_bag = _oid_(v47292);
                                  }
                                GC_OID(v_bag);}
                              ((list *) v24671)->addFast((OID)v_bag);}
                            (v24670->args = v24671);}
                          add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                          v24669 = _oid_(v47292);
                          }
                        (v24668->arg = v24669);}
                      add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                      v24667 = _oid_(v47292);
                      }
                    (v24645->arg = v24667);}
                  add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                  v24642 = _oid_(v47292);
                  }
                (v24641->arg = v24642);}
              add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
              v21342 = _oid_(v47292);
              }
            v31009 = (*Optimize.c_code)(v21342,
              _oid_(v57700));
            }
          }
        else { Variable * v29685 = GC_OBJECT(Variable,v61776->var);
            CL_INT  v57783 = v29685->index;
            Variable * v24539;
            { { CL_INT  v44260;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v44260 = 0;
                  }
                v24539 = Variable_I_symbol(gensym_void(),v44260,GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._list)));
                }
              GC_OBJECT(Variable,v24539);}
            Variable * v17948;
            { { CL_INT  v45221;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v45221 = 0;
                  }
                v17948 = Variable_I_symbol(gensym_void(),v45221,Kernel._list);
                }
              GC_OBJECT(Variable,v17948);}
            Variable * v6028;
            { { CL_INT  v46182;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v46182 = 0;
                  }
                v6028 = Variable_I_symbol(gensym_void(),v46182,Core._ffor_error);
                }
              GC_OBJECT(Variable,v6028);}
            Variable * v20115;
            { { CL_INT  v47143;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v47143 = 0;
                  }
                v20115 = Variable_I_symbol(gensym_void(),v47143,Kernel._any);
                }
              GC_OBJECT(Variable,v20115);}
            Variable * v33791;
            { { CL_INT  v48104;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v48104 = 0;
                  }
                v33791 = Variable_I_symbol(gensym_void(),v48104,Kernel._any);
                }
              GC_OBJECT(Variable,v33791);}
            Variable * v29552;
            { { CL_INT  v49065;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v49065 = 0;
                  }
                v29552 = Variable_I_symbol(gensym_void(),v49065,Kernel._integer);
                }
              GC_OBJECT(Variable,v29552);}
            Variable * v15594;
            { { CL_INT  v50026;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v50026 = 0;
                  }
                v15594 = Variable_I_symbol(gensym_void(),v50026,Kernel._integer);
                }
              GC_OBJECT(Variable,v15594);}
            Variable * v12177;
            { { CL_INT  v50987;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v50987 = 0;
                  }
                v12177 = Variable_I_symbol(gensym_void(),v50987,Kernel._integer);
                }
              GC_OBJECT(Variable,v12177);}
            Variable * v48351;
            { { CL_INT  v51948;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v51948 = 0;
                  }
                v48351 = Variable_I_symbol(gensym_void(),v51948,Kernel._list);
                }
              GC_OBJECT(Variable,v48351);}
            Variable * v57140;
            { { CL_INT  v7554;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v7554 = 0;
                  }
                v57140 = Variable_I_symbol(gensym_void(),v7554,Kernel._list);
                }
              GC_OBJECT(Variable,v57140);}
            Variable * v57636;
            { { CL_INT  v8515;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v8515 = 0;
                  }
                v57636 = Variable_I_symbol(gensym_void(),v8515,Core._socket);
                }
              GC_OBJECT(Variable,v57636);}
            Variable * v3055;
            { { CL_INT  v9476;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v9476 = 0;
                  }
                v3055 = Variable_I_symbol(gensym_void(),v9476,Core._buffer);
                }
              GC_OBJECT(Variable,v3055);}
            Variable * v16135;
            { { CL_INT  v10437;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v10437 = 0;
                  }
                v16135 = Variable_I_symbol(gensym_void(),v10437,Kernel._integer);
                }
              GC_OBJECT(Variable,v16135);}
            Variable * v11509;
            { { CL_INT  v11399;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v11399 = 0;
                  }
                v11509 = Variable_I_symbol(gensym_void(),v11399,Kernel._any);
                }
              GC_OBJECT(Variable,v11509);}
            Variable * v48367;
            { { CL_INT  v12359;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v12359 = 0;
                  }
                v48367 = Variable_I_symbol(gensym_void(),v12359,tuple::alloc(2,_oid_(Core._socket),_oid_(Core._socket)));
                }
              GC_OBJECT(Variable,v48367);}
            Variable * v57634;
            { { CL_INT  v13320;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v13320 = 0;
                  }
                v57634 = Variable_I_symbol(gensym_void(),v13320,Core._socket);
                }
              GC_OBJECT(Variable,v57634);}
            Variable * v57635;
            { { CL_INT  v14281;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v14281 = 0;
                  }
                v57635 = Variable_I_symbol(gensym_void(),v14281,Core._socket);
                }
              GC_OBJECT(Variable,v57635);}
            Variable * v57701;
            { { CL_INT  v15242;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v15242 = 0;
                  }
                v57701 = Variable_I_symbol(gensym_void(),v15242,tuple::alloc(3,_oid_(Core._process_status),
                  _oid_(Kernel._integer),
                  _oid_(Kernel._any)));
                }
              GC_OBJECT(Variable,v57701);}
            Variable * v48330;
            { { CL_INT  v16203;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v16203 = 0;
                  }
                v48330 = Variable_I_symbol(gensym_void(),v16203,Kernel._integer);
                }
              GC_OBJECT(Variable,v48330);}
            Variable * v48360;
            { { CL_INT  v37345;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v37345 = 0;
                  }
                v48360 = Variable_I_symbol(gensym_void(),v37345,Kernel._list);
                }
              GC_OBJECT(Variable,v48360);}
            Variable * v48357;
            { { Variable * v47292 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                (v47292->pname = gensym_void());
                (v47292->index = 0);
                add_I_property(Kernel.instances,Language._Variable,11,_oid_(v47292));
                v48357 = v47292;
                }
              GC_OBJECT(Variable,v48357);}
            Variable * v48358;
            { { CL_INT  v38306;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v38306 = 0;
                  }
                v48358 = Variable_I_symbol(gensym_void(),v38306,Kernel._integer);
                }
              GC_OBJECT(Variable,v48358);}
            Variable * v48359;
            { { CL_INT  v39267;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v39267 = 0;
                  }
                v48359 = Variable_I_symbol(gensym_void(),v39267,Kernel._integer);
                }
              GC_OBJECT(Variable,v48359);}
            Variable * v48363;
            { { CL_INT  v40228;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v40228 = 0;
                  }
                v48363 = Variable_I_symbol(gensym_void(),v40228,Kernel._integer);
                }
              GC_OBJECT(Variable,v48363);}
            Variable * v48361;
            { { CL_INT  v41189;
                { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                  v41189 = 0;
                  }
                v48361 = Variable_I_symbol(gensym_void(),v41189,Kernel._list);
                }
              GC_OBJECT(Variable,v48361);}
            Variable * v48370;
            { { Variable * v47292 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                (v47292->pname = v29685->pname);
                (v47292->range = v29685->range);
                (v47292->index = v57783);
                add_I_property(Kernel.instances,Language._Variable,11,_oid_(v47292));
                v48370 = v47292;
                }
              GC_OBJECT(Variable,v48370);}
            OID  v40236 = GC_OID(substitution_any(GC_OID(v61776->arg),v29685,_oid_(v48370)));
            if (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->forkedby)))),Kernel._integer) != CTRUE)
             close_exception(((general_error *) (*Core._general_error)(_string_("Can't compile ~S, ~S does not belong to integer"),
              _oid_(list::alloc(2,_oid_(v61776),GC_OID(v61776->forkedby))))));
            { OID  v42150;
              { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                (v47292->var = v48360);
                { Let * v25480 = v47292; 
                  OID  v25481;
                  { Collect * v47292 = ((Collect *) GC_OBJECT(Collect,new_object_class(Language._Collect)));
                    (v47292->var = v48357);
                    (v47292->set_arg = v61776->set_arg);
                    (v47292->arg = _oid_(v48357));
                    add_I_property(Kernel.instances,Language._Collect,11,_oid_(v47292));
                    v25481 = _oid_(v47292);
                    }
                  (v25480->value = v25481);}
                { Let * v25482 = v47292; 
                  OID  v25483;
                  { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                    (v47292->var = v17948);
                    { Let * v25504 = v47292; 
                      OID  v25505;
                      { OID  v3522;
                        { List * v47292 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                          (v47292->of = Kernel._any);
                          add_I_property(Kernel.instances,Language._List,11,_oid_(v47292));
                          v3522 = _oid_(v47292);
                          }
                        v25505 = (*Optimize.c_code)(v3522);
                        }
                      (v25504->value = v25505);}
                    { Let * v25507 = v47292; 
                      OID  v25508;
                      { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                        (v47292->var = v48330);
                        (v47292->value = (*Optimize.c_code)(GC_OID(v61776->forkedby)));
                        { Let * v25509 = v47292; 
                          OID  v25510;
                          { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                            (v47292->var = v48370);
                            (v47292->value = CNULL);
                            { Let * v25511 = v47292; 
                              OID  v25512;
                              { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                (v47292->var = v15594);
                                (v47292->value = ((OID)1));
                                { Let * v25513 = v47292; 
                                  OID  v25535;
                                  { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                    (v47292->var = v24539);
                                    { Let * v25536 = v47292; 
                                      OID  v25537;
                                      { Collect * v47292 = ((Collect *) GC_OBJECT(Collect,new_object_class(Language._Collect)));
                                        (v47292->var = v48358);
                                        { Iteration * v25538 = v47292; 
                                          OID  v25539;
                                          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                            (v47292->selector = Kernel._dot_dot);
                                            (v47292->args = list::alloc(2,((OID)1),_oid_(v48330)));
                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                            v25539 = _oid_(v47292);
                                            }
                                          (v25538->set_arg = v25539);}
                                        { Iteration * v25540 = v47292; 
                                          OID  v25541;
                                          { List * v47292 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                                            (v47292->of = Kernel._any);
                                            { Construct * v25542 = v47292; 
                                              list * v25543;
                                              { OID v_bag;
                                                GC_ANY(v25543= list::empty(Kernel.emptySet));
                                                ((list *) v25543)->addFast((OID)((OID)-1));
                                                ((list *) v25543)->addFast((OID)CNULL);
                                                { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                    (v47292->selector = OBJECT(property,Core.port_I->value));
                                                    (v47292->args = list::alloc(1,_oid_(ClEnv)));
                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                    v_bag = _oid_(v47292);
                                                    }
                                                  GC_OID(v_bag);}
                                                ((list *) v25543)->addFast((OID)v_bag);
                                                ((list *) v25543)->addFast((OID)CNULL);}
                                              (v25542->args = v25543);}
                                            add_I_property(Kernel.instances,Language._List,11,_oid_(v47292));
                                            v25541 = _oid_(v47292);
                                            }
                                          (v25540->arg = v25541);}
                                        add_I_property(Kernel.instances,Language._Collect,11,_oid_(v47292));
                                        v25537 = _oid_(v47292);
                                        }
                                      (v25536->value = v25537);}
                                    { Let * v25544 = v47292; 
                                      OID  v25566;
                                      { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                        (v47292->var = v29552);
                                        { Let * v25567 = v47292; 
                                          OID  v25568;
                                          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                            (v47292->selector = Kernel.length);
                                            (v47292->args = list::alloc(1,_oid_(v48360)));
                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                            v25568 = _oid_(v47292);
                                            }
                                          (v25567->value = v25568);}
                                        { Let * v25569 = v47292; 
                                          OID  v25571;
                                          { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                            (v47292->var = v12177);
                                            (v47292->value = _oid_(v29552));
                                            { Let * v25572 = v47292; 
                                              OID  v25573;
                                              { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                { Do * v25574 = v47292; 
                                                  list * v25575;
                                                  { OID v_bag;
                                                    GC_ANY(v25575= list::empty(Kernel.emptySet));
                                                    { { While * v47292 = ((While *) GC_OBJECT(While,new_object_class(Language._While)));
                                                        { While * v25576 = v47292; 
                                                          OID  v25597;
                                                          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                            (v47292->selector = Kernel._inf);
                                                            { Call * v25598 = v47292; 
                                                              list * v25599;
                                                              { OID v_bag;
                                                                GC_ANY(v25599= list::empty(Kernel.emptySet));
                                                                { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                    (v47292->selector = Kernel.length);
                                                                    (v47292->args = list::alloc(1,_oid_(v17948)));
                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                    v_bag = _oid_(v47292);
                                                                    }
                                                                  GC_OID(v_bag);}
                                                                ((list *) v25599)->addFast((OID)v_bag);
                                                                ((list *) v25599)->addFast((OID)_oid_(v12177));}
                                                              (v25598->args = v25599);}
                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                            v25597 = _oid_(v47292);
                                                            }
                                                          (v25576->test = v25597);}
                                                        { While * v25600 = v47292; 
                                                          OID  v25601;
                                                          { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                            { Do * v25602 = v47292; 
                                                              list * v25603;
                                                              { OID v_bag;
                                                                GC_ANY(v25603= list::empty(Kernel.emptySet));
                                                                { { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                                    { If * v25604 = v47292; 
                                                                      OID  v25605;
                                                                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                        (v47292->selector = Kernel._sup);
                                                                        (v47292->args = list::alloc(2,_oid_(v29552),((OID)0)));
                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                        v25605 = _oid_(v47292);
                                                                        }
                                                                      (v25604->test = v25605);}
                                                                    { If * v25606 = v47292; 
                                                                      OID  v25628;
                                                                      { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                                                                        (v47292->var = v48359);
                                                                        { Iteration * v25629 = v47292; 
                                                                          OID  v25630;
                                                                          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                            (v47292->selector = Kernel._dot_dot);
                                                                            (v47292->args = list::alloc(2,((OID)1),_oid_(v48330)));
                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                            v25630 = _oid_(v47292);
                                                                            }
                                                                          (v25629->set_arg = v25630);}
                                                                        { Iteration * v25631 = v47292; 
                                                                          OID  v25632;
                                                                          { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                            { Do * v25633 = v47292; 
                                                                              list * v25634;
                                                                              { OID v_bag;
                                                                                GC_ANY(v25634= list::empty(Kernel.emptySet));
                                                                                { { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                                                    { If * v25635 = v47292; 
                                                                                      OID  v25636;
                                                                                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                        (v47292->selector = Kernel._equal);
                                                                                        (v47292->args = list::alloc(2,_oid_(v29552),((OID)0)));
                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                        v25636 = _oid_(v47292);
                                                                                        }
                                                                                      (v25635->test = v25636);}
                                                                                    { If * v25638 = v47292; 
                                                                                      OID  v26310;
                                                                                      { Return * v47292 = ((Return *) GC_OBJECT(Return,new_object_class(Language._Return)));
                                                                                        (v47292->arg = Kernel.ctrue);
                                                                                        add_I_property(Kernel.instances,Language._Return,11,_oid_(v47292));
                                                                                        v26310 = _oid_(v47292);
                                                                                        }
                                                                                      (v25638->arg = v26310);}
                                                                                    add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                                                                                    (v47292->other = Kernel.cfalse);
                                                                                    v_bag = _oid_(v47292);
                                                                                    }
                                                                                  GC_OID(v_bag);}
                                                                                ((list *) v25634)->addFast((OID)v_bag);
                                                                                { { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                                                    { If * v26311 = v47292; 
                                                                                      OID  v26312;
                                                                                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                        (v47292->selector = Kernel._equal);
                                                                                        { Call * v26313 = v47292; 
                                                                                          list * v26314;
                                                                                          { OID v_bag;
                                                                                            GC_ANY(v26314= list::empty(Kernel.emptySet));
                                                                                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                (v47292->selector = Kernel.nth);
                                                                                                { Call * v26315 = v47292; 
                                                                                                  list * v26316;
                                                                                                  { OID v_bag;
                                                                                                    GC_ANY(v26316= list::empty(Kernel.emptySet));
                                                                                                    { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                        (v47292->selector = Kernel.nth);
                                                                                                        (v47292->args = list::alloc(2,_oid_(v24539),_oid_(v48359)));
                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                        v_bag = _oid_(v47292);
                                                                                                        }
                                                                                                      GC_OID(v_bag);}
                                                                                                    ((list *) v26316)->addFast((OID)v_bag);
                                                                                                    ((list *) v26316)->addFast((OID)((OID)1));}
                                                                                                  (v26315->args = v26316);}
                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                v_bag = _oid_(v47292);
                                                                                                }
                                                                                              GC_OID(v_bag);}
                                                                                            ((list *) v26314)->addFast((OID)v_bag);
                                                                                            ((list *) v26314)->addFast((OID)((OID)-1));}
                                                                                          (v26313->args = v26314);}
                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                        v26312 = _oid_(v47292);
                                                                                        }
                                                                                      (v26311->test = v26312);}
                                                                                    { If * v26317 = v47292; 
                                                                                      OID  v26318;
                                                                                      { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                        (v47292->var = v11509);
                                                                                        { Let * v26320 = v47292; 
                                                                                          OID  v26341;
                                                                                          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                            (v47292->selector = Kernel.nth);
                                                                                            (v47292->args = list::alloc(2,_oid_(v48360),_oid_(v15594)));
                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                            v26341 = _oid_(v47292);
                                                                                            }
                                                                                          (v26320->value = v26341);}
                                                                                        { Let * v26342 = v47292; 
                                                                                          OID  v26343;
                                                                                          { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                            { Do * v26344 = v47292; 
                                                                                              list * v26345;
                                                                                              { OID v_bag;
                                                                                                GC_ANY(v26345= list::empty(Kernel.emptySet));
                                                                                                { { Assign * v47292 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                                                                                    (v47292->var = _oid_(v48370));
                                                                                                    (v47292->arg = _oid_(v11509));
                                                                                                    add_I_property(Kernel.instances,Language._Assign,11,_oid_(v47292));
                                                                                                    v_bag = _oid_(v47292);
                                                                                                    }
                                                                                                  GC_OID(v_bag);}
                                                                                                ((list *) v26345)->addFast((OID)v_bag);
                                                                                                { { ClaireHandle * v47292 = ((ClaireHandle *) GC_OBJECT(ClaireHandle,new_object_class(Language._Handle)));
                                                                                                    (v47292->test = _oid_(Kernel._any));
                                                                                                    { ClaireHandle * v26346 = v47292; 
                                                                                                      OID  v26347;
                                                                                                      { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                                        (v47292->var = v48367);
                                                                                                        { Let * v26348 = v47292; 
                                                                                                          OID  v26349;
                                                                                                          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                            (v47292->selector = Core.socketpair);
                                                                                                            (v47292->args = list::alloc(1,_oid_(ClEnv)));
                                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                            v26349 = _oid_(v47292);
                                                                                                            }
                                                                                                          (v26348->value = v26349);}
                                                                                                        { Let * v26350 = v47292; 
                                                                                                          OID  v26372;
                                                                                                          { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                                            (v47292->var = v57634);
                                                                                                            { Let * v26373 = v47292; 
                                                                                                              OID  v26374;
                                                                                                              { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                (v47292->selector = Kernel.nth);
                                                                                                                (v47292->args = list::alloc(2,_oid_(v48367),((OID)1)));
                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                v26374 = _oid_(v47292);
                                                                                                                }
                                                                                                              (v26373->value = v26374);}
                                                                                                            { Let * v26375 = v47292; 
                                                                                                              OID  v26376;
                                                                                                              { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                                                (v47292->var = v57635);
                                                                                                                { Let * v26377 = v47292; 
                                                                                                                  OID  v26378;
                                                                                                                  { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                    (v47292->selector = Kernel.nth);
                                                                                                                    (v47292->args = list::alloc(2,_oid_(v48367),((OID)2)));
                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                    v26378 = _oid_(v47292);
                                                                                                                    }
                                                                                                                  (v26377->value = v26378);}
                                                                                                                { Let * v26379 = v47292; 
                                                                                                                  OID  v26380;
                                                                                                                  { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                                                                                    { If * v26381 = v47292; 
                                                                                                                      OID  v26403;
                                                                                                                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                        (v47292->selector = Core.forker_ask);
                                                                                                                        (v47292->args = list::alloc(1,_oid_(ClEnv)));
                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                        v26403 = _oid_(v47292);
                                                                                                                        }
                                                                                                                      (v26381->test = v26403);}
                                                                                                                    { If * v26404 = v47292; 
                                                                                                                      OID  v26405;
                                                                                                                      { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                                                        (v47292->var = v48351);
                                                                                                                        { Let * v26406 = v47292; 
                                                                                                                          OID  v26407;
                                                                                                                          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                            (v47292->selector = Kernel.nth);
                                                                                                                            (v47292->args = list::alloc(2,_oid_(v24539),_oid_(v48359)));
                                                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                            v26407 = _oid_(v47292);
                                                                                                                            }
                                                                                                                          (v26406->value = v26407);}
                                                                                                                        { Let * v26408 = v47292; 
                                                                                                                          OID  v26409;
                                                                                                                          { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                                            { Do * v26411 = v47292; 
                                                                                                                              list * v26412;
                                                                                                                              { OID v_bag;
                                                                                                                                GC_ANY(v26412= list::empty(Kernel.emptySet));
                                                                                                                                { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                    (v47292->selector = Core.fclose);
                                                                                                                                    (v47292->args = list::alloc(1,_oid_(v57634)));
                                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                    v_bag = _oid_(v47292);
                                                                                                                                    }
                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                ((list *) v26412)->addFast((OID)v_bag);
                                                                                                                                { { Assign * v47292 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                                                                                                                    (v47292->var = _oid_(v29552));
                                                                                                                                    { Assign * v26413 = v47292; 
                                                                                                                                      OID  v26434;
                                                                                                                                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                        (v47292->selector = Kernel._dash);
                                                                                                                                        (v47292->args = list::alloc(2,_oid_(v29552),((OID)1)));
                                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                        v26434 = _oid_(v47292);
                                                                                                                                        }
                                                                                                                                      (v26413->arg = v26434);}
                                                                                                                                    add_I_property(Kernel.instances,Language._Assign,11,_oid_(v47292));
                                                                                                                                    v_bag = _oid_(v47292);
                                                                                                                                    }
                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                ((list *) v26412)->addFast((OID)v_bag);
                                                                                                                                { { Assign * v47292 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                                                                                                                    (v47292->var = _oid_(v15594));
                                                                                                                                    { Assign * v26435 = v47292; 
                                                                                                                                      OID  v26436;
                                                                                                                                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                        (v47292->selector = Core._plus);
                                                                                                                                        (v47292->args = list::alloc(2,_oid_(v15594),((OID)1)));
                                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                        v26436 = _oid_(v47292);
                                                                                                                                        }
                                                                                                                                      (v26435->arg = v26436);}
                                                                                                                                    add_I_property(Kernel.instances,Language._Assign,11,_oid_(v47292));
                                                                                                                                    v_bag = _oid_(v47292);
                                                                                                                                    }
                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                ((list *) v26412)->addFast((OID)v_bag);
                                                                                                                                { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                    (v47292->selector = Kernel.nth_equal);
                                                                                                                                    { Call * v26437 = v47292; 
                                                                                                                                      list * v26438;
                                                                                                                                      { OID v_bag;
                                                                                                                                        GC_ANY(v26438= list::empty(Kernel.emptySet));
                                                                                                                                        ((list *) v26438)->addFast((OID)_oid_(v48351));
                                                                                                                                        ((list *) v26438)->addFast((OID)((OID)1));
                                                                                                                                        { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                            (v47292->selector = Kernel.forked);
                                                                                                                                            (v47292->args = list::alloc(1,_oid_(ClEnv)));
                                                                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                            v_bag = _oid_(v47292);
                                                                                                                                            }
                                                                                                                                          GC_OID(v_bag);}
                                                                                                                                        ((list *) v26438)->addFast((OID)v_bag);}
                                                                                                                                      (v26437->args = v26438);}
                                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                    v_bag = _oid_(v47292);
                                                                                                                                    }
                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                ((list *) v26412)->addFast((OID)v_bag);
                                                                                                                                { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                    (v47292->selector = Kernel.nth_equal);
                                                                                                                                    (v47292->args = list::alloc(3,_oid_(v48351),
                                                                                                                                      ((OID)2),
                                                                                                                                      _oid_(v57635)));
                                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                    v_bag = _oid_(v47292);
                                                                                                                                    }
                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                ((list *) v26412)->addFast((OID)v_bag);
                                                                                                                                { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                    (v47292->selector = Kernel.nth_equal);
                                                                                                                                    (v47292->args = list::alloc(3,_oid_(v48351),
                                                                                                                                      ((OID)4),
                                                                                                                                      _oid_(v11509)));
                                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                    v_bag = _oid_(v47292);
                                                                                                                                    }
                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                ((list *) v26412)->addFast((OID)v_bag);}
                                                                                                                              (v26411->args = v26412);}
                                                                                                                            add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                                                                                                            v26409 = _oid_(v47292);
                                                                                                                            }
                                                                                                                          (v26408->arg = v26409);}
                                                                                                                        add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                                                                                                        v26405 = _oid_(v47292);
                                                                                                                        }
                                                                                                                      (v26404->arg = v26405);}
                                                                                                                    { If * v26439 = v47292; 
                                                                                                                      OID  v26440;
                                                                                                                      { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                                        { Do * v26441 = v47292; 
                                                                                                                          list * v26442;
                                                                                                                          { OID v_bag;
                                                                                                                            GC_ANY(v26442= list::empty(Kernel.emptySet));
                                                                                                                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                (v47292->selector = Core.fclose);
                                                                                                                                (v47292->args = list::alloc(1,_oid_(v57635)));
                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                v_bag = _oid_(v47292);
                                                                                                                                }
                                                                                                                              GC_OID(v_bag);}
                                                                                                                            ((list *) v26442)->addFast((OID)v_bag);
                                                                                                                            { { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                                                                (v47292->var = v20115);
                                                                                                                                (v47292->value = CNULL);
                                                                                                                                { Let * v26443 = v47292; 
                                                                                                                                  OID  v26465;
                                                                                                                                  { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                                                    { Do * v26466 = v47292; 
                                                                                                                                      list * v26467;
                                                                                                                                      { OID v_bag;
                                                                                                                                        GC_ANY(v26467= list::empty(Kernel.emptySet));
                                                                                                                                        { { Assign * v47292 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                                                                                                                            (v47292->var = _oid_(v20115));
                                                                                                                                            { Assign * v26468 = v47292; 
                                                                                                                                              OID  v26469;
                                                                                                                                              { ClaireHandle * v47292 = ((ClaireHandle *) GC_OBJECT(ClaireHandle,new_object_class(Language._Handle)));
                                                                                                                                                (v47292->test = _oid_(Kernel._any));
                                                                                                                                                (v47292->arg = v40236);
                                                                                                                                                { ClaireHandle * v26470 = v47292; 
                                                                                                                                                  OID  v26471;
                                                                                                                                                  { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                                                                                    (v47292->var = v6028);
                                                                                                                                                    { Let * v26472 = v47292; 
                                                                                                                                                      OID  v26473;
                                                                                                                                                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                        (v47292->selector = Core.new_I);
                                                                                                                                                        (v47292->args = list::alloc(1,_oid_(Core._ffor_error)));
                                                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                                        v26473 = _oid_(v47292);
                                                                                                                                                        }
                                                                                                                                                      (v26472->value = v26473);}
                                                                                                                                                    { Let * v26475 = v47292; 
                                                                                                                                                      OID  v26496;
                                                                                                                                                      { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                                                                        { Do * v26497 = v47292; 
                                                                                                                                                          list * v26498;
                                                                                                                                                          { OID v_bag;
                                                                                                                                                            GC_ANY(v26498= list::empty(Kernel.emptySet));
                                                                                                                                                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                                (v47292->selector = Kernel.put);
                                                                                                                                                                { Call * v26499 = v47292; 
                                                                                                                                                                  list * v26500;
                                                                                                                                                                  { OID v_bag;
                                                                                                                                                                    GC_ANY(v26500= list::empty(Kernel.emptySet));
                                                                                                                                                                    ((list *) v26500)->addFast((OID)_oid_(Core.childstr));
                                                                                                                                                                    ((list *) v26500)->addFast((OID)_oid_(v6028));
                                                                                                                                                                    { { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                                                                                        { Do * v26502 = v47292; 
                                                                                                                                                                          list * v26503;
                                                                                                                                                                          { OID v_bag;
                                                                                                                                                                            GC_ANY(v26503= list::empty(Kernel.emptySet));
                                                                                                                                                                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                                                (v47292->selector = Core.print_in_string);
                                                                                                                                                                                (v47292->args = list::alloc(1,_oid_(ClEnv)));
                                                                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                                                                v_bag = _oid_(v47292);
                                                                                                                                                                                }
                                                                                                                                                                              GC_OID(v_bag);}
                                                                                                                                                                            ((list *) v26503)->addFast((OID)v_bag);
                                                                                                                                                                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                                                (v47292->selector = Kernel.print);
                                                                                                                                                                                { Call * v26504 = v47292; 
                                                                                                                                                                                  list * v26505;
                                                                                                                                                                                  { OID v_bag;
                                                                                                                                                                                    GC_ANY(v26505= list::empty(Kernel.emptySet));
                                                                                                                                                                                    { { Call_star * v47292 = ((Call_star *) GC_OBJECT(Call_star,new_object_class(Language._Call_star)));
                                                                                                                                                                                        (v47292->selector = Kernel.exception_I);
                                                                                                                                                                                        (v47292->args = list::alloc(1,_oid_(ClEnv)));
                                                                                                                                                                                        add_I_property(Kernel.instances,Language._Call_star,11,_oid_(v47292));
                                                                                                                                                                                        v_bag = _oid_(v47292);
                                                                                                                                                                                        }
                                                                                                                                                                                      GC_OID(v_bag);}
                                                                                                                                                                                    ((list *) v26505)->addFast((OID)v_bag);}
                                                                                                                                                                                  (v26504->args = v26505);}
                                                                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                                                                v_bag = _oid_(v47292);
                                                                                                                                                                                }
                                                                                                                                                                              GC_OID(v_bag);}
                                                                                                                                                                            ((list *) v26503)->addFast((OID)v_bag);
                                                                                                                                                                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                                                (v47292->selector = Core.end_of_string);
                                                                                                                                                                                (v47292->args = list::alloc(1,_oid_(ClEnv)));
                                                                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                                                                v_bag = _oid_(v47292);
                                                                                                                                                                                }
                                                                                                                                                                              GC_OID(v_bag);}
                                                                                                                                                                            ((list *) v26503)->addFast((OID)v_bag);}
                                                                                                                                                                          (v26502->args = v26503);}
                                                                                                                                                                        add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                                                                                                                                                        v_bag = _oid_(v47292);
                                                                                                                                                                        }
                                                                                                                                                                      GC_OID(v_bag);}
                                                                                                                                                                    ((list *) v26500)->addFast((OID)v_bag);}
                                                                                                                                                                  (v26499->args = v26500);}
                                                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                                                v_bag = _oid_(v47292);
                                                                                                                                                                }
                                                                                                                                                              GC_OID(v_bag);}
                                                                                                                                                            ((list *) v26498)->addFast((OID)v_bag);
                                                                                                                                                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                                (v47292->selector = Kernel.put);
                                                                                                                                                                { Call * v26506 = v47292; 
                                                                                                                                                                  list * v26527;
                                                                                                                                                                  { OID v_bag;
                                                                                                                                                                    GC_ANY(v26527= list::empty(Kernel.emptySet));
                                                                                                                                                                    ((list *) v26527)->addFast((OID)_oid_(Core.childpid));
                                                                                                                                                                    ((list *) v26527)->addFast((OID)_oid_(v6028));
                                                                                                                                                                    { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                                        (v47292->selector = Kernel.getpid);
                                                                                                                                                                        (v47292->args = list::alloc(1,_oid_(ClEnv)));
                                                                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                                                        v_bag = _oid_(v47292);
                                                                                                                                                                        }
                                                                                                                                                                      GC_OID(v_bag);}
                                                                                                                                                                    ((list *) v26527)->addFast((OID)v_bag);}
                                                                                                                                                                  (v26506->args = v26527);}
                                                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                                                v_bag = _oid_(v47292);
                                                                                                                                                                }
                                                                                                                                                              GC_OID(v_bag);}
                                                                                                                                                            ((list *) v26498)->addFast((OID)v_bag);
                                                                                                                                                            ((list *) v26498)->addFast((OID)_oid_(v6028));}
                                                                                                                                                          (v26497->args = v26498);}
                                                                                                                                                        add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                                                                                                                                        v26496 = _oid_(v47292);
                                                                                                                                                        }
                                                                                                                                                      (v26475->arg = v26496);}
                                                                                                                                                    add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                                                                                                                                    v26471 = _oid_(v47292);
                                                                                                                                                    }
                                                                                                                                                  (v26470->other = v26471);}
                                                                                                                                                add_I_property(Kernel.instances,Language._Handle,11,_oid_(v47292));
                                                                                                                                                v26469 = _oid_(v47292);
                                                                                                                                                }
                                                                                                                                              (v26468->arg = v26469);}
                                                                                                                                            add_I_property(Kernel.instances,Language._Assign,11,_oid_(v47292));
                                                                                                                                            v_bag = _oid_(v47292);
                                                                                                                                            }
                                                                                                                                          GC_OID(v_bag);}
                                                                                                                                        ((list *) v26467)->addFast((OID)v_bag);
                                                                                                                                        { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                            (v47292->selector = Serialize.serialize);
                                                                                                                                            (v47292->args = list::alloc(2,_oid_(v57634),_oid_(v20115)));
                                                                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                            v_bag = _oid_(v47292);
                                                                                                                                            }
                                                                                                                                          GC_OID(v_bag);}
                                                                                                                                        ((list *) v26467)->addFast((OID)v_bag);}
                                                                                                                                      (v26466->args = v26467);}
                                                                                                                                    add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                                                                                                                    v26465 = _oid_(v47292);
                                                                                                                                    }
                                                                                                                                  (v26443->arg = v26465);}
                                                                                                                                add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                                                                                                                v_bag = _oid_(v47292);
                                                                                                                                }
                                                                                                                              GC_OID(v_bag);}
                                                                                                                            ((list *) v26442)->addFast((OID)v_bag);
                                                                                                                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                (v47292->selector = Core.fclose);
                                                                                                                                (v47292->args = list::alloc(1,_oid_(v57634)));
                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                v_bag = _oid_(v47292);
                                                                                                                                }
                                                                                                                              GC_OID(v_bag);}
                                                                                                                            ((list *) v26442)->addFast((OID)v_bag);
                                                                                                                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                (v47292->selector = Core.exit);
                                                                                                                                (v47292->args = list::alloc(1,((OID)0)));
                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                v_bag = _oid_(v47292);
                                                                                                                                }
                                                                                                                              GC_OID(v_bag);}
                                                                                                                            ((list *) v26442)->addFast((OID)v_bag);}
                                                                                                                          (v26441->args = v26442);}
                                                                                                                        add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                                                                                                        v26440 = _oid_(v47292);
                                                                                                                        }
                                                                                                                      (v26439->other = v26440);}
                                                                                                                    add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                                                                                                                    v26380 = _oid_(v47292);
                                                                                                                    }
                                                                                                                  (v26379->arg = v26380);}
                                                                                                                add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                                                                                                v26376 = _oid_(v47292);
                                                                                                                }
                                                                                                              (v26375->arg = v26376);}
                                                                                                            add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                                                                                            v26372 = _oid_(v47292);
                                                                                                            }
                                                                                                          (v26350->arg = v26372);}
                                                                                                        add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                                                                                        v26347 = _oid_(v47292);
                                                                                                        }
                                                                                                      (v26346->arg = v26347);}
                                                                                                    add_I_property(Kernel.instances,Language._Handle,11,_oid_(v47292));
                                                                                                    v_bag = _oid_(v47292);
                                                                                                    }
                                                                                                  GC_OID(v_bag);}
                                                                                                ((list *) v26345)->addFast((OID)v_bag);}
                                                                                              (v26344->args = v26345);}
                                                                                            add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                                                                            v26343 = _oid_(v47292);
                                                                                            }
                                                                                          (v26342->arg = v26343);}
                                                                                        add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                                                                        v26318 = _oid_(v47292);
                                                                                        }
                                                                                      (v26317->arg = v26318);}
                                                                                    add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                                                                                    (v47292->other = Kernel.cfalse);
                                                                                    v_bag = _oid_(v47292);
                                                                                    }
                                                                                  GC_OID(v_bag);}
                                                                                ((list *) v25634)->addFast((OID)v_bag);}
                                                                              (v25633->args = v25634);}
                                                                            add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                                                            v25632 = _oid_(v47292);
                                                                            }
                                                                          (v25631->arg = v25632);}
                                                                        add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
                                                                        v25628 = _oid_(v47292);
                                                                        }
                                                                      (v25606->arg = v25628);}
                                                                    add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                                                                    (v47292->other = Kernel.cfalse);
                                                                    v_bag = _oid_(v47292);
                                                                    }
                                                                  GC_OID(v_bag);}
                                                                ((list *) v25603)->addFast((OID)v_bag);
                                                                { { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                                                                    (v47292->var = v48363);
                                                                    { Iteration * v26528 = v47292; 
                                                                      OID  v26529;
                                                                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                        (v47292->selector = Kernel._dot_dot);
                                                                        (v47292->args = list::alloc(2,((OID)1),_oid_(v48330)));
                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                        v26529 = _oid_(v47292);
                                                                        }
                                                                      (v26528->set_arg = v26529);}
                                                                    { Iteration * v26530 = v47292; 
                                                                      OID  v26531;
                                                                      { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                        (v47292->var = v57140);
                                                                        { Let * v26532 = v47292; 
                                                                          OID  v26533;
                                                                          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                            (v47292->selector = Kernel.nth);
                                                                            (v47292->args = list::alloc(2,_oid_(v24539),_oid_(v48363)));
                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                            v26533 = _oid_(v47292);
                                                                            }
                                                                          (v26532->value = v26533);}
                                                                        { Let * v26534 = v47292; 
                                                                          OID  v26535;
                                                                          { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                            (v47292->var = v57636);
                                                                            { Let * v26536 = v47292; 
                                                                              OID  v26558;
                                                                              { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                (v47292->selector = Kernel.nth);
                                                                                (v47292->args = list::alloc(2,_oid_(v57140),((OID)2)));
                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                v26558 = _oid_(v47292);
                                                                                }
                                                                              (v26536->value = v26558);}
                                                                            { Let * v26559 = v47292; 
                                                                              OID  v26560;
                                                                              { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                (v47292->var = v16135);
                                                                                { Let * v26561 = v47292; 
                                                                                  OID  v26562;
                                                                                  { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                    (v47292->selector = Kernel.nth);
                                                                                    (v47292->args = list::alloc(2,_oid_(v57140),((OID)1)));
                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                    v26562 = _oid_(v47292);
                                                                                    }
                                                                                  (v26561->value = v26562);}
                                                                                { Let * v26563 = v47292; 
                                                                                  OID  v26564;
                                                                                  { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                    (v47292->var = v3055);
                                                                                    { Let * v26565 = v47292; 
                                                                                      OID  v26566;
                                                                                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                        (v47292->selector = Kernel.nth);
                                                                                        (v47292->args = list::alloc(2,_oid_(v57140),((OID)3)));
                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                        v26566 = _oid_(v47292);
                                                                                        }
                                                                                      (v26565->value = v26566);}
                                                                                    { Let * v26567 = v47292; 
                                                                                      OID  v26589;
                                                                                      { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                                                        { If * v26590 = v47292; 
                                                                                          OID  v26591;
                                                                                          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                            (v47292->selector = Core._I_equal);
                                                                                            (v47292->args = list::alloc(2,_oid_(v16135),((OID)-1)));
                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                            v26591 = _oid_(v47292);
                                                                                            }
                                                                                          (v26590->test = v26591);}
                                                                                        { If * v26592 = v47292; 
                                                                                          OID  v26593;
                                                                                          { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                            { Do * v26594 = v47292; 
                                                                                              list * v26595;
                                                                                              { OID v_bag;
                                                                                                GC_ANY(v26595= list::empty(Kernel.emptySet));
                                                                                                { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                    (v47292->selector = Core.read_I);
                                                                                                    (v47292->args = list::alloc(1,_oid_(v57636)));
                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                    v_bag = _oid_(v47292);
                                                                                                    }
                                                                                                  GC_OID(v_bag);}
                                                                                                ((list *) v26595)->addFast((OID)v_bag);
                                                                                                { { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                                                                    { If * v26596 = v47292; 
                                                                                                      OID  v26597;
                                                                                                      { And * v47292 = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
                                                                                                        { And * v26598 = v47292; 
                                                                                                          list * v27271;
                                                                                                          { OID v_bag;
                                                                                                            GC_ANY(v27271= list::empty(Kernel.emptySet));
                                                                                                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                (v47292->selector = Core.select_ask);
                                                                                                                (v47292->args = list::alloc(1,((OID)10)));
                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                v_bag = _oid_(v47292);
                                                                                                                }
                                                                                                              GC_OID(v_bag);}
                                                                                                            ((list *) v27271)->addFast((OID)v_bag);
                                                                                                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                (v47292->selector = Core.readable_ask);
                                                                                                                (v47292->args = list::alloc(1,_oid_(v57636)));
                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                v_bag = _oid_(v47292);
                                                                                                                }
                                                                                                              GC_OID(v_bag);}
                                                                                                            ((list *) v27271)->addFast((OID)v_bag);}
                                                                                                          (v26598->args = v27271);}
                                                                                                        add_I_property(Kernel.instances,Language._And,11,_oid_(v47292));
                                                                                                        v26597 = _oid_(v47292);
                                                                                                        }
                                                                                                      (v26596->test = v26597);}
                                                                                                    { If * v27272 = v47292; 
                                                                                                      OID  v27273;
                                                                                                      { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                        { Do * v27274 = v47292; 
                                                                                                          list * v27275;
                                                                                                          { OID v_bag;
                                                                                                            GC_ANY(v27275= list::empty(Kernel.emptySet));
                                                                                                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                (v47292->selector = Kernel.fwrite);
                                                                                                                { Call * v27276 = v47292; 
                                                                                                                  list * v27277;
                                                                                                                  { OID v_bag;
                                                                                                                    GC_ANY(v27277= list::empty(Kernel.emptySet));
                                                                                                                    { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                        (v47292->selector = Kernel.fread);
                                                                                                                        (v47292->args = list::alloc(2,_oid_(v57636),((OID)1024)));
                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                        v_bag = _oid_(v47292);
                                                                                                                        }
                                                                                                                      GC_OID(v_bag);}
                                                                                                                    ((list *) v27277)->addFast((OID)v_bag);
                                                                                                                    ((list *) v27277)->addFast((OID)_oid_(v3055));}
                                                                                                                  (v27276->args = v27277);}
                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                v_bag = _oid_(v47292);
                                                                                                                }
                                                                                                              GC_OID(v_bag);}
                                                                                                            ((list *) v27275)->addFast((OID)v_bag);
                                                                                                            { { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                                                                                { If * v27278 = v47292; 
                                                                                                                  OID  v27279;
                                                                                                                  { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                    (v47292->selector = Core.eof_ask);
                                                                                                                    (v47292->args = list::alloc(1,_oid_(v57636)));
                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                    v27279 = _oid_(v47292);
                                                                                                                    }
                                                                                                                  (v27278->test = v27279);}
                                                                                                                { If * v27280 = v47292; 
                                                                                                                  OID  v27302;
                                                                                                                  { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                                                    (v47292->var = v57701);
                                                                                                                    { Let * v27304 = v47292; 
                                                                                                                      OID  v27305;
                                                                                                                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                        (v47292->selector = Core.waitpid);
                                                                                                                        (v47292->args = list::alloc(1,_oid_(v16135)));
                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                        v27305 = _oid_(v47292);
                                                                                                                        }
                                                                                                                      (v27304->value = v27305);}
                                                                                                                    { Let * v27306 = v47292; 
                                                                                                                      OID  v27307;
                                                                                                                      { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                                        { Do * v27308 = v47292; 
                                                                                                                          list * v27309;
                                                                                                                          { OID v_bag;
                                                                                                                            GC_ANY(v27309= list::empty(Kernel.emptySet));
                                                                                                                            { { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                                                                                                { If * v27310 = v47292; 
                                                                                                                                  OID  v27311;
                                                                                                                                  { And * v47292 = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
                                                                                                                                    { And * v27312 = v47292; 
                                                                                                                                      list * v27333;
                                                                                                                                      { OID v_bag;
                                                                                                                                        GC_ANY(v27333= list::empty(Kernel.emptySet));
                                                                                                                                        { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                            (v47292->selector = Kernel._equal);
                                                                                                                                            { Call * v27334 = v47292; 
                                                                                                                                              list * v27335;
                                                                                                                                              { OID v_bag;
                                                                                                                                                GC_ANY(v27335= list::empty(Kernel.emptySet));
                                                                                                                                                { { Cast * v47292 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                                                                                                                                                    { Cast * v27336 = v47292; 
                                                                                                                                                      OID  v27337;
                                                                                                                                                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                        (v47292->selector = Kernel.nth);
                                                                                                                                                        (v47292->args = list::alloc(2,_oid_(v57701),((OID)1)));
                                                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                                        v27337 = _oid_(v47292);
                                                                                                                                                        }
                                                                                                                                                      (v27336->arg = v27337);}
                                                                                                                                                    (v47292->set_arg = Core._process_status);
                                                                                                                                                    add_I_property(Kernel.instances,Language._Cast,11,_oid_(v47292));
                                                                                                                                                    v_bag = _oid_(v47292);
                                                                                                                                                    }
                                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                                ((list *) v27335)->addFast((OID)v_bag);
                                                                                                                                                ((list *) v27335)->addFast((OID)_oid_(Core.CL_WEXITED));}
                                                                                                                                              (v27334->args = v27335);}
                                                                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                            v_bag = _oid_(v47292);
                                                                                                                                            }
                                                                                                                                          GC_OID(v_bag);}
                                                                                                                                        ((list *) v27333)->addFast((OID)v_bag);
                                                                                                                                        { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                            (v47292->selector = Kernel._equal);
                                                                                                                                            { Call * v27338 = v47292; 
                                                                                                                                              list * v27339;
                                                                                                                                              { OID v_bag;
                                                                                                                                                GC_ANY(v27339= list::empty(Kernel.emptySet));
                                                                                                                                                { { Cast * v47292 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                                                                                                                                                    { Cast * v27340 = v47292; 
                                                                                                                                                      OID  v27341;
                                                                                                                                                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                        (v47292->selector = Kernel.nth);
                                                                                                                                                        (v47292->args = list::alloc(2,_oid_(v57701),((OID)3)));
                                                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                                        v27341 = _oid_(v47292);
                                                                                                                                                        }
                                                                                                                                                      (v27340->arg = v27341);}
                                                                                                                                                    (v47292->set_arg = Kernel._integer);
                                                                                                                                                    add_I_property(Kernel.instances,Language._Cast,11,_oid_(v47292));
                                                                                                                                                    v_bag = _oid_(v47292);
                                                                                                                                                    }
                                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                                ((list *) v27339)->addFast((OID)v_bag);
                                                                                                                                                ((list *) v27339)->addFast((OID)((OID)0));}
                                                                                                                                              (v27338->args = v27339);}
                                                                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                            v_bag = _oid_(v47292);
                                                                                                                                            }
                                                                                                                                          GC_OID(v_bag);}
                                                                                                                                        ((list *) v27333)->addFast((OID)v_bag);}
                                                                                                                                      (v27312->args = v27333);}
                                                                                                                                    add_I_property(Kernel.instances,Language._And,11,_oid_(v47292));
                                                                                                                                    v27311 = _oid_(v47292);
                                                                                                                                    }
                                                                                                                                  (v27310->test = v27311);}
                                                                                                                                { If * v27342 = v47292; 
                                                                                                                                  OID  v27364;
                                                                                                                                  { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                                                                    (v47292->var = v33791);
                                                                                                                                    (v47292->value = CNULL);
                                                                                                                                    { Let * v27365 = v47292; 
                                                                                                                                      OID  v27366;
                                                                                                                                      { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                                                        { Do * v27367 = v47292; 
                                                                                                                                          list * v27368;
                                                                                                                                          { OID v_bag;
                                                                                                                                            GC_ANY(v27368= list::empty(Kernel.emptySet));
                                                                                                                                            { { Assign * v47292 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                                                                                                                                (v47292->var = _oid_(v33791));
                                                                                                                                                { Assign * v27369 = v47292; 
                                                                                                                                                  OID  v27370;
                                                                                                                                                  { ClaireHandle * v47292 = ((ClaireHandle *) GC_OBJECT(ClaireHandle,new_object_class(Language._Handle)));
                                                                                                                                                    (v47292->test = _oid_(Kernel._any));
                                                                                                                                                    { ClaireHandle * v27371 = v47292; 
                                                                                                                                                      OID  v27372;
                                                                                                                                                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                        (v47292->selector = Serialize.unserialize);
                                                                                                                                                        (v47292->args = list::alloc(1,_oid_(v3055)));
                                                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                                        v27372 = _oid_(v47292);
                                                                                                                                                        }
                                                                                                                                                      (v27371->arg = v27372);}
                                                                                                                                                    { ClaireHandle * v27373 = v47292; 
                                                                                                                                                      OID  v27395;
                                                                                                                                                      { Call_star * v47292 = ((Call_star *) GC_OBJECT(Call_star,new_object_class(Language._Call_star)));
                                                                                                                                                        (v47292->selector = Kernel.exception_I);
                                                                                                                                                        (v47292->args = list::alloc(1,_oid_(ClEnv)));
                                                                                                                                                        add_I_property(Kernel.instances,Language._Call_star,11,_oid_(v47292));
                                                                                                                                                        v27395 = _oid_(v47292);
                                                                                                                                                        }
                                                                                                                                                      (v27373->other = v27395);}
                                                                                                                                                    add_I_property(Kernel.instances,Language._Handle,11,_oid_(v47292));
                                                                                                                                                    v27370 = _oid_(v47292);
                                                                                                                                                    }
                                                                                                                                                  (v27369->arg = v27370);}
                                                                                                                                                add_I_property(Kernel.instances,Language._Assign,11,_oid_(v47292));
                                                                                                                                                v_bag = _oid_(v47292);
                                                                                                                                                }
                                                                                                                                              GC_OID(v_bag);}
                                                                                                                                            ((list *) v27368)->addFast((OID)v_bag);
                                                                                                                                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                (v47292->selector = Kernel.add_I);
                                                                                                                                                (v47292->args = list::alloc(2,_oid_(v17948),_oid_(v33791)));
                                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                                v_bag = _oid_(v47292);
                                                                                                                                                }
                                                                                                                                              GC_OID(v_bag);}
                                                                                                                                            ((list *) v27368)->addFast((OID)v_bag);}
                                                                                                                                          (v27367->args = v27368);}
                                                                                                                                        add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                                                                                                                        v27366 = _oid_(v47292);
                                                                                                                                        }
                                                                                                                                      (v27365->arg = v27366);}
                                                                                                                                    add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                                                                                                                    v27364 = _oid_(v47292);
                                                                                                                                    }
                                                                                                                                  (v27342->arg = v27364);}
                                                                                                                                { If * v27396 = v47292; 
                                                                                                                                  OID  v27397;
                                                                                                                                  { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                    (v47292->selector = Kernel.add_I);
                                                                                                                                    (v47292->args = list::alloc(2,_oid_(v17948),_oid_(v57701)));
                                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                    v27397 = _oid_(v47292);
                                                                                                                                    }
                                                                                                                                  (v27396->other = v27397);}
                                                                                                                                add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                                                                                                                                v_bag = _oid_(v47292);
                                                                                                                                }
                                                                                                                              GC_OID(v_bag);}
                                                                                                                            ((list *) v27309)->addFast((OID)v_bag);
                                                                                                                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                (v47292->selector = Core.fclose);
                                                                                                                                (v47292->args = list::alloc(1,_oid_(v57636)));
                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                v_bag = _oid_(v47292);
                                                                                                                                }
                                                                                                                              GC_OID(v_bag);}
                                                                                                                            ((list *) v27309)->addFast((OID)v_bag);
                                                                                                                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                (v47292->selector = Core.set_length);
                                                                                                                                (v47292->args = list::alloc(2,_oid_(v3055),((OID)0)));
                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                v_bag = _oid_(v47292);
                                                                                                                                }
                                                                                                                              GC_OID(v_bag);}
                                                                                                                            ((list *) v27309)->addFast((OID)v_bag);
                                                                                                                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                (v47292->selector = Kernel.nth_equal);
                                                                                                                                (v47292->args = list::alloc(3,_oid_(v57140),
                                                                                                                                  ((OID)1),
                                                                                                                                  ((OID)-1)));
                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                                                                                v_bag = _oid_(v47292);
                                                                                                                                }
                                                                                                                              GC_OID(v_bag);}
                                                                                                                            ((list *) v27309)->addFast((OID)v_bag);
                                                                                                                            { { Return * v47292 = ((Return *) GC_OBJECT(Return,new_object_class(Language._Return)));
                                                                                                                                (v47292->arg = Kernel.ctrue);
                                                                                                                                add_I_property(Kernel.instances,Language._Return,11,_oid_(v47292));
                                                                                                                                v_bag = _oid_(v47292);
                                                                                                                                }
                                                                                                                              GC_OID(v_bag);}
                                                                                                                            ((list *) v27309)->addFast((OID)v_bag);}
                                                                                                                          (v27308->args = v27309);}
                                                                                                                        add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                                                                                                        v27307 = _oid_(v47292);
                                                                                                                        }
                                                                                                                      (v27306->arg = v27307);}
                                                                                                                    add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                                                                                                    v27302 = _oid_(v47292);
                                                                                                                    }
                                                                                                                  (v27280->arg = v27302);}
                                                                                                                add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                                                                                                                (v47292->other = Kernel.cfalse);
                                                                                                                v_bag = _oid_(v47292);
                                                                                                                }
                                                                                                              GC_OID(v_bag);}
                                                                                                            ((list *) v27275)->addFast((OID)v_bag);}
                                                                                                          (v27274->args = v27275);}
                                                                                                        add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                                                                                        v27273 = _oid_(v47292);
                                                                                                        }
                                                                                                      (v27272->arg = v27273);}
                                                                                                    add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                                                                                                    (v47292->other = Kernel.cfalse);
                                                                                                    v_bag = _oid_(v47292);
                                                                                                    }
                                                                                                  GC_OID(v_bag);}
                                                                                                ((list *) v26595)->addFast((OID)v_bag);}
                                                                                              (v26594->args = v26595);}
                                                                                            add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                                                                            v26593 = _oid_(v47292);
                                                                                            }
                                                                                          (v26592->arg = v26593);}
                                                                                        add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                                                                                        (v47292->other = Kernel.cfalse);
                                                                                        v26589 = _oid_(v47292);
                                                                                        }
                                                                                      (v26567->arg = v26589);}
                                                                                    add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                                                                    v26564 = _oid_(v47292);
                                                                                    }
                                                                                  (v26563->arg = v26564);}
                                                                                add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                                                                v26560 = _oid_(v47292);
                                                                                }
                                                                              (v26559->arg = v26560);}
                                                                            add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                                                            v26535 = _oid_(v47292);
                                                                            }
                                                                          (v26534->arg = v26535);}
                                                                        add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                                                        v26531 = _oid_(v47292);
                                                                        }
                                                                      (v26530->arg = v26531);}
                                                                    add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
                                                                    v_bag = _oid_(v47292);
                                                                    }
                                                                  GC_OID(v_bag);}
                                                                ((list *) v25603)->addFast((OID)v_bag);}
                                                              (v25602->args = v25603);}
                                                            add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                                            v25601 = _oid_(v47292);
                                                            }
                                                          (v25600->arg = v25601);}
                                                        add_I_property(Kernel.instances,Language._While,11,_oid_(v47292));
                                                        v_bag = _oid_(v47292);
                                                        }
                                                      GC_OID(v_bag);}
                                                    ((list *) v25575)->addFast((OID)v_bag);
                                                    { { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                                                        (v47292->var = v48361);
                                                        (v47292->set_arg = _oid_(v24539));
                                                        { Iteration * v27398 = v47292; 
                                                          OID  v27399;
                                                          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                            (v47292->selector = Core.fclose);
                                                            { Call * v27400 = v47292; 
                                                              list * v27401;
                                                              { OID v_bag;
                                                                GC_ANY(v27401= list::empty(Kernel.emptySet));
                                                                { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                    (v47292->selector = Kernel.nth);
                                                                    (v47292->args = list::alloc(2,_oid_(v48361),((OID)3)));
                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                    v_bag = _oid_(v47292);
                                                                    }
                                                                  GC_OID(v_bag);}
                                                                ((list *) v27401)->addFast((OID)v_bag);}
                                                              (v27400->args = v27401);}
                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                            v27399 = _oid_(v47292);
                                                            }
                                                          (v27398->arg = v27399);}
                                                        add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
                                                        v_bag = _oid_(v47292);
                                                        }
                                                      GC_OID(v_bag);}
                                                    ((list *) v25575)->addFast((OID)v_bag);
                                                    { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                        (v47292->selector = Kernel.cast_I);
                                                        (v47292->args = list::alloc(2,_oid_(v17948),_oid_(Kernel.emptySet)));
                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                        v_bag = _oid_(v47292);
                                                        }
                                                      GC_OID(v_bag);}
                                                    ((list *) v25575)->addFast((OID)v_bag);}
                                                  (v25574->args = v25575);}
                                                add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                                v25573 = _oid_(v47292);
                                                }
                                              (v25572->arg = v25573);}
                                            add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                            v25571 = _oid_(v47292);
                                            }
                                          (v25569->arg = v25571);}
                                        add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                        v25566 = _oid_(v47292);
                                        }
                                      (v25544->arg = v25566);}
                                    add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                    v25535 = _oid_(v47292);
                                    }
                                  (v25513->arg = v25535);}
                                add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                                v25512 = _oid_(v47292);
                                }
                              (v25511->arg = v25512);}
                            add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                            v25510 = _oid_(v47292);
                            }
                          (v25509->arg = v25510);}
                        add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                        v25508 = _oid_(v47292);
                        }
                      (v25507->arg = v25508);}
                    add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                    v25483 = _oid_(v47292);
                    }
                  (v25482->arg = v25483);}
                add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                v42150 = _oid_(v47292);
                }
              v31009 = (*Optimize.c_code)(v42150,
                _oid_(v57700));
              }
            }
          GC_OID(v31009);}
      (Optimize.OPT->loop_gc = CTRUE);
      (Optimize.OPT->protection = CTRUE);
      Result = v31009;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  Iterate_I_Iteration(Iteration *v61776)
{ GC_BIND;
  { OID Result = 0;
    Result = restriction_I_property(Language.Iterate,list::alloc(3,_oid_(set::alloc(1,GC_OID(v61776->set_arg))),
      _oid_(set::alloc(1,GC_OID(_oid_(v61776->var)))),
      _oid_(Kernel._any)),CTRUE);
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  iterate_Interval(Interval *v48372,Variable *v48370,OID v48353)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { OID Result = 0;
    { OID  v48370 = GC_OID(eval_any2(((OID)v48372->arg1),Core._Interval));
      CL_INT  v39203 = eval_any2(((OID)v48372->arg2),Core._Interval);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        Result= _oid_(CFALSE);
        while (((CL_INT)v48370 <= (CL_INT)v39203))
        { GC_LOOP;
          ;GC__OID(v48370 = (*Core._plus)(v48370,
            ((OID)1)), 1);
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  iterate_array(OID *v48372,Variable *v48370,OID v48353)
{ { OID Result = 0;
    { CL_INT  v55272 = 1;
      OID * v55264 = v48372;
      CL_INT  v39203 = v55264[0];
      { CL_INT loop_handle = ClEnv->cHandle;
        Result= _oid_(CFALSE);
        while (((CL_INT)v55272 <= (CL_INT)v39203))
        { { OID  v48370 = nth_array(v55264,v55272);
            ;++v55272;
            }
          POP_SIGNAL;}
        }
      }
    POP_SIGNAL; return (Result);}
  }

OID  Iterate_class(ClaireClass *v48372,Variable *v48370,OID v48353)
{ { OID Result = 0;
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v47719);
      Result= Kernel.cfalse;
      for (START(v48372->descendents); NEXT(v47719);)
      { ClaireBoolean * v47720;
        { OID v40982;{ CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(v48370);
            v40982= Kernel.cfalse;
            for (START(OBJECT(ClaireClass,v47719)->instances); NEXT(v48370);)
            ;}
          
          v47720=OBJECT(ClaireBoolean,v40982);}
        if (v47720 == CTRUE)
         { Result = _oid_(v47720);
          ClEnv->cHandle = loop_handle;break;}
        }
      }
    POP_SIGNAL; return (Result);}
  }

OID  Iterate_any1(OID v48372,Variable *v48370,OID v48353)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { OID Result = 0;
    { OID  v48370 = GC_OID(OPT_EVAL((*(OBJECT(Call,v48372)->args))[1]));
      OID  v39203 = GC_OID(OPT_EVAL((*(OBJECT(Call,v48372)->args))[2]));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        Result= _oid_(CFALSE);
        while (((OBJECT(ClaireBoolean,(*Kernel._inf_equal)(v48370,
          v39203))) == CTRUE))
        { GC_LOOP;
          ;GC__OID(v48370 = (*Core._plus)(v48370,
            ((OID)1)), 1);
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  Iterate_Lselect(Lselect *v48372,Variable *v48370,OID v48353)
{ GC_BIND;
  { OID Result = 0;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v48370);
      Result= Kernel.cfalse;
      bag *v48370_support;
      v48370_support = GC_OBJECT(bag,enumerate_any(GC_OID(eval_any(GC_OID(v48372->set_arg)))));
      for (START(v48370_support); NEXT(v48370);)
      { GC_LOOP;
        if (boolean_I_any(eval_any(GC_OID(substitution_any(GC_OID(v48372->arg),GC_OBJECT(Variable,v48372->var),v48370)))) == CTRUE)
         ;GC_UNLOOP; POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  Iterate_Select(Select *v48372,Variable *v48370,OID v48353)
{ GC_BIND;
  { OID Result = 0;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v48370);
      Result= Kernel.cfalse;
      bag *v48370_support;
      v48370_support = GC_OBJECT(bag,enumerate_any(GC_OID(eval_any(GC_OID(v48372->set_arg)))));
      for (START(v48370_support); NEXT(v48370);)
      { GC_LOOP;
        if (boolean_I_any(eval_any(GC_OID(substitution_any(GC_OID(v48372->arg),GC_OBJECT(Variable,v48372->var),v48370)))) == CTRUE)
         ;GC_UNLOOP; POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  Iterate_Collect(Collect *v48372,Variable *v48370,OID v48353)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { OID Result = 0;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v36336);
      Result= Kernel.cfalse;
      bag *v36336_support;
      v36336_support = GC_OBJECT(bag,enumerate_any(GC_OID(eval_any(GC_OID(v48372->set_arg)))));
      for (START(v36336_support); NEXT(v36336);)
      { GC_LOOP;
        { OID  v48370 = GC_OID(eval_any(GC_OID(substitution_any(GC_OID(v48372->arg),GC_OBJECT(Variable,v48372->var),v36336))));
          ;}
        GC_UNLOOP; POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  Iterate_any2(OID v48372,Variable *v48370,OID v48353)
{ GC_BIND;
  { OID Result = 0;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v48370);
      Result= Kernel.cfalse;
      bag *v48370_support;
      v48370_support = GC_OBJECT(bag,enumerate_any(GC_OID(OPT_EVAL((*(OBJECT(Call,v48372)->args))[1]))));
      for (START(v48370_support); NEXT(v48370);)
      { GC_LOOP;
        if (equal(v48370,OPT_EVAL((*(OBJECT(Call,v48372)->args))[2])) != CTRUE)
         ;GC_UNLOOP; POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  Iterate_any3(OID v48372,Variable *v48370,OID v48353)
{ GC_BIND;
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v48370);
    bag *v48370_support;
    v48370_support = GC_OBJECT(bag,enumerate_any(GC_OID(OPT_EVAL((*(OBJECT(Call,v48372)->args))[1]))));
    for (START(v48370_support); NEXT(v48370);)
    ;}
  { OID Result = 0;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v48370);
      Result= Kernel.cfalse;
      bag *v48370_support;
      v48370_support = GC_OBJECT(bag,enumerate_any(GC_OID(OPT_EVAL((*(OBJECT(Call,v48372)->args))[2]))));
      for (START(v48370_support); NEXT(v48370);)
      ;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }



