/***** CLAIRE Compilation of file ./compile/otool.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:45 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>
#include <Optimize.h>
void  self_print_to_protect(Compile_to_protect *v48372)
{ GC_BIND;
  princ_string("[to_protect ");
  print_any(GC_OID(v48372->arg));
  princ_string("]");
  GC_UNBIND; POP_SIGNAL;}

OID  self_eval_to_protect(Compile_to_protect *v48372)
{ GC_BIND;
  { OID Result = 0;
    Result = OPT_EVAL(v48372->arg);
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  self_print_to_CL(Compile_to_CL *v61776)
{ GC_BIND;
  princ_string("CL{");
  print_any(GC_OID(v61776->arg));
  princ_string("}:");
  print_any(GC_OID(get_property(Language.set_arg,v61776)));
  GC_UNBIND; POP_SIGNAL;}

ClaireType * c_type_to_CL_Optimize(Compile_to_CL *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    Result = sort_abstract_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v61776->arg))));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * c_gc_ask_to_CL(Compile_to_CL *v61776)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = (((gcsafe_ask_class(v61776->set_arg) != CTRUE) && 
        ((v61776->set_arg == Kernel._float) || 
            (_inf_equalt_class(v61776->set_arg,Kernel._cl_import) == CTRUE))) ? CTRUE : (((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(GC_OID(v61776->arg)))) == CTRUE) ? CTRUE : CFALSE));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  self_print_to_C(Compile_to_C *v61776)
{ GC_BIND;
  princ_string("C{");
  print_any(GC_OID(v61776->arg));
  princ_string("}:");
  print_any(GC_OID(get_property(Language.set_arg,v61776)));
  GC_UNBIND; POP_SIGNAL;}

ClaireBoolean * c_gc_ask_to_C(Compile_to_C *v61776)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = ((gcsafe_ask_class(v61776->set_arg) != CTRUE) ? (((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(GC_OID(v61776->arg)))) == CTRUE) ? (((_inf_equalt_class(v61776->set_arg,Kernel._object) == CTRUE) || 
        (_inf_equalt_class(v61776->set_arg,Kernel._primitive) == CTRUE)) ? CTRUE: CFALSE): CFALSE): CFALSE);
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_to_C_Optimize(Compile_to_C *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    Result = glb_class(v61776->set_arg,GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->arg))))));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  self_print_C_cast(Compile_C_cast *v61776)
{ GC_BIND;
  princ_string("<");
  print_any(GC_OID(v61776->arg));
  princ_string(":");
  print_any(GC_OID(get_property(Language.set_arg,v61776)));
  princ_string(">");
  GC_UNBIND; POP_SIGNAL;}

ClaireBoolean * c_gc_ask_C_cast(Compile_C_cast *v61776)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v61776->arg));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_C_cast_Optimize(Compile_C_cast *v61776)
{ POP_SIGNAL; return (v61776->set_arg);}

OID  c_code_C_cast_Optimize(Compile_C_cast *v61776,ClaireClass *v48367)
{ GC_BIND;
  { OID Result = 0;
    if (INHERIT(v48367,Kernel._object))
     { Compile_C_cast * v47292 = ((Compile_C_cast *) GC_OBJECT(Compile_C_cast,new_object_class(Optimize._C_cast)));
      (v47292->arg = (*Optimize.c_code)(GC_OID(v61776->arg),
        _oid_(v48367)));
      (v47292->set_arg = v61776->set_arg);
      add_I_property(Kernel.instances,Optimize._C_cast,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    else Result = (*Optimize.c_code)(GC_OID(v61776->arg),
        _oid_(v48367));
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  self_print_Pattern(Optimize_ClairePattern *v61776)
{ GC_BIND;
  print_any(GC_OID(get_property(Kernel.selector,v61776)));
  princ_string("[tuple(");
  princ_bag(GC_OBJECT(list,v61776->arg));
  princ_string(")]");
  GC_UNBIND; POP_SIGNAL;}

ClaireBoolean * _Z_any3(OID v48372,Optimize_ClairePattern *v48373)
{ GC_BIND;
  { ClaireBoolean *Result ;
    if (INHERIT(OWNER(v48372),Language._Call))
     { ClaireBoolean *v_and;
      { v_and = ((OBJECT(Call,v48372)->selector == v48373->selector) ? CTRUE : CFALSE);
        if (v_and == CFALSE) Result =CFALSE; 
        else { { list * v53737;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID v48374; CL_INT CLcount;
                v_list = GC_OBJECT(list,OBJECT(Call,v48372)->args);
                 v53737 = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { v48374 = (*(v_list))[CLcount];
                  v_val = (*Optimize.c_type)(v48374);
                  
                  (*((list *) v53737))[CLcount] = v_val;}
                }
              GC_OBJECT(list,v53737);}
            v_and = tmatch_ask_list(v53737,GC_OBJECT(list,v48373->arg));
            }
          if (v_and == CFALSE) Result =CFALSE; 
          else Result = CTRUE;}
        }
      }
    else Result = CFALSE;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * glb_Pattern(Optimize_ClairePattern *v48372,ClaireType *v48373)
{ POP_SIGNAL; return (Kernel.emptySet);}

ClaireBoolean * less_ask_Pattern(Optimize_ClairePattern *v48372,OID v48373)
{ GC_BIND;
  { ClaireBoolean *Result ;
    if (INHERIT(OWNER(v48373),Optimize._Pattern))
     { ClaireBoolean *v_and;
      { v_and = ((v48372->selector == OBJECT(Optimize_ClairePattern,v48373)->selector) ? CTRUE : CFALSE);
        if (v_and == CFALSE) Result =CFALSE; 
        else { v_and = ((v48372->arg->length == OBJECT(Optimize_ClairePattern,v48373)->arg->length) ? CTRUE : CFALSE);
          if (v_and == CFALSE) Result =CFALSE; 
          else { { OID  v55659;
              { CL_INT  v48357 = 1;
                CL_INT  v1418 = v48372->arg->length;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  v55659= _oid_(CFALSE);
                  while (((CL_INT)v48357 <= (CL_INT)v1418))
                  { GC_LOOP;
                    if (_equaltype_ask_any(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*(v48372->arg))[v48357])),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*(OBJECT(Optimize_ClairePattern,v48373)->arg))[v48357]))) != CTRUE)
                     { v55659 = Kernel.ctrue;
                      ClEnv->cHandle = loop_handle;break;}
                    ++v48357;
                    GC_UNLOOP;POP_SIGNAL;}
                  }
                }
              v_and = not_any(v55659);
              }
            if (v_and == CFALSE) Result =CFALSE; 
            else Result = CTRUE;}
          }
        }
      }
    else Result = OBJECT(ClaireBoolean,(*Core._inf_equalt)(_oid_(Language._Call),
        v48373));
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * less_ask_any(OID v48372,Optimize_ClairePattern *v48373)
{ GC_BIND;
  { ClaireBoolean *Result ;
    if (INHERIT(OWNER(v48372),Optimize._Pattern))
     { ClaireBoolean *v_and;
      { v_and = ((OBJECT(Optimize_ClairePattern,v48372)->selector == v48373->selector) ? CTRUE : CFALSE);
        if (v_and == CFALSE) Result =CFALSE; 
        else { v_and = ((OBJECT(Optimize_ClairePattern,v48372)->arg->length == v48373->arg->length) ? CTRUE : CFALSE);
          if (v_and == CFALSE) Result =CFALSE; 
          else { { OID  v57581;
              { CL_INT  v48357 = 1;
                CL_INT  v1420 = OBJECT(Optimize_ClairePattern,v48372)->arg->length;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  v57581= _oid_(CFALSE);
                  while (((CL_INT)v48357 <= (CL_INT)v1420))
                  { GC_LOOP;
                    if (_equaltype_ask_any(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*(OBJECT(Optimize_ClairePattern,v48372)->arg))[v48357])),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*(v48373->arg))[v48357]))) != CTRUE)
                     { v57581 = Kernel.ctrue;
                      ClEnv->cHandle = loop_handle;break;}
                    ++v48357;
                    GC_UNLOOP;POP_SIGNAL;}
                  }
                }
              v_and = not_any(v57581);
              }
            if (v_and == CFALSE) Result =CFALSE; 
            else Result = CTRUE;}
          }
        }
      }
    else Result = CFALSE;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

Optimize_ClairePattern * nth_property(property *v48364,tuple *v48372)
{ GC_BIND;
  { Optimize_ClairePattern *Result ;
    { Optimize_ClairePattern * v47292 = ((Optimize_ClairePattern *) GC_OBJECT(Optimize_ClairePattern,new_object_class(Optimize._Pattern)));
      (v47292->selector = v48364);
      (v47292->arg = list_I_tuple(v48372));
      add_I_property(Kernel.instances,Optimize._Pattern,11,_oid_(v47292));
      Result = v47292;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  warn_void()
{ GC_BIND;
  if (((Optimize.OPT->in_method == CNULL) ? CTRUE : CFALSE) != CTRUE)
   { if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
     mtformat_module1(Optimize.it,"`BLUE ---- WARNING[in ~S]: ",2,list::alloc(1,GC_OID(Optimize.OPT->in_method)));
    else ;}
  else if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
   mtformat_module1(Optimize.it,"`BLUE ---- WARNING[in ~S]: ",2,list::alloc(1,GC_OID(Reader.reader->last_form)));
  else ;GC_UNBIND; POP_SIGNAL;}

void  Cerror_string(char *v48367,listargs *v48360)
{ GC_BIND;
  { general_error * v58542;
    { OID  v59503;
      { { list * v42531;{ list * v61425;
            { OID v_bag;
              GC_ANY(v61425= list::empty(Kernel.emptySet));
              { if (((Optimize.OPT->in_method == CNULL) ? CTRUE : CFALSE) != CTRUE)
                 v_bag = Optimize.OPT->in_method;
                else v_bag = Reader.reader->last_form;
                  GC_OID(v_bag);}
              ((list *) v61425)->addFast((OID)v_bag);}
            v42531 = append_list(v61425,v48360);
            }
          
          v59503=_oid_(v42531);}
        GC_OID(v59503);}
      v58542 = ((general_error *) (*Core._general_error)(GC_OID(_string_(append_string("---- Compiler Error [in ~S]:\n",v48367))),
        v59503));
      }
    close_exception(v58542);
    }
  GC_UNBIND; POP_SIGNAL;}

void  notice_void()
{ GC_BIND;
  if (((Optimize.OPT->in_method == CNULL) ? CTRUE : CFALSE) != CTRUE)
   { if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
     mtformat_module1(Optimize.it,"`GREEN ---- note[in ~S]: ",3,list::alloc(1,GC_OID(Optimize.OPT->in_method)));
    else ;}
  else if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
   mtformat_module1(Optimize.it,"`GREEN ---- note[in ~S]: ",3,list::alloc(1,GC_OID(Reader.reader->last_form)));
  else ;GC_UNBIND; POP_SIGNAL;}

OID  c_warn_Call(Call *v61776,OID v4955)
{ GC_BIND;
  { OID Result = 0;
    { property * v48367 = v61776->selector;
      if (v4955 == _oid_(Kernel._void))
       (*Optimize.Cerror)(_string_("[205] message ~S sent to void object"),
        _oid_(v61776));
      else if ((boolean_I_any(_oid_(v48367->restrictions)) != CTRUE) && 
          (contain_ask_set(Optimize.OPT->ignore,_oid_(v48367)) != CTRUE))
       { warn_void();
        if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
         mtformat_module1(Optimize.it,"`BLUE the property ~S is undefined [255]\n",2,list::alloc(1,_oid_(v48367)));
        else ;}
      else if ((contain_ask_set(Optimize.OPT->ignore,_oid_(v48367)) != CTRUE) && 
          ((((CL_INT)v48367->open <= 1) || 
              (v48367->open == 4)) && 
            ((INHERIT(OWNER(v4955),Kernel._list)) && (class_I_type(OBJECT(ClaireType,(*(OBJECT(bag,v4955)))[1]))->open != 3))))
       { warn_void();
        if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
         mtformat_module1(Optimize.it,"`BLUE wrongly typed message ~S (~S) [256]\n",2,list::alloc(2,_oid_(v61776),v4955));
        else ;}
      else if (Optimize.compiler->optimize_ask == CTRUE)
       { notice_void();
        if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
         mtformat_module1(Optimize.it,"`GREEN poorly typed message ~S [~S]\n",3,list::alloc(2,_oid_(v61776),v4955));
        else ;}
      Result = _oid_(open_message_property(v61776->selector,GC_OBJECT(list,v61776->args)));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_warn_Super(Super *v61776,OID v4955)
{ GC_BIND;
  { OID Result = 0;
    { property * v48367 = v61776->selector;
      if (v4955 == _oid_(Kernel._void))
       (*Optimize.Cerror)(_string_("[205] message ~S sent to void object"),
        _oid_(v61776));
      else if (boolean_I_any(_oid_(v48367->restrictions)) != CTRUE)
       { warn_void();
        if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
         mtformat_module1(Optimize.it,"`BLUE the property ~S is undefined [255]\n",2,list::alloc(1,_oid_(v48367)));
        else ;}
      else if ((contain_ask_set(Optimize.OPT->ignore,_oid_(v48367)) != CTRUE) && 
          ((CL_INT)v48367->open <= 1))
       { if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
         mtformat_module1(Optimize.it,"`GREEN ---- note: wrongly typed message ~S [~S]\n",3,list::alloc(2,_oid_(v61776),v4955));
        else ;}
      { Call * v48361 = GC_OBJECT(Call,open_message_property(v61776->selector,GC_OBJECT(list,v61776->args)));
        Super * v47292 = ((Super *) GC_OBJECT(Super,new_object_class(Language._Super)));
        (v47292->selector = v48361->selector);
        (v47292->cast_to = v61776->cast_to);
        (v47292->args = v48361->args);
        add_I_property(Kernel.instances,Language._Super,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_warn_property(property *v61776,list *v48360,list *v4955)
{ if (((CL_INT)v61776->open <= 1) && 
      ((contain_ask_set(Optimize.OPT->ignore,_oid_(v61776)) != CTRUE) && 
        ((CL_INT)Optimize.compiler->safety > 1)))
   { if (should_trace_ask_module1(Optimize.it,4) == CTRUE)
     mtformat_module1(Optimize.it,"`GREEN ---- note: poor type matching with ~S(~S) [~S]\n",4,list::alloc(3,_oid_(v61776),
      _oid_(v48360),
      _oid_(v4955)));
    else ;}
  POP_SIGNAL; return (_oid_(open_message_property(v61776,v48360)));}

OID  c_warn_Variable(Variable *v61776,OID v48372,ClaireType *v48373)
{ GC_BIND;
  if (boolean_I_any((*Kernel._exp)(_oid_(v48373),
    GC_OID(_oid_(v61776->range)))) != CTRUE)
   { if ((CL_INT)Optimize.compiler->safety > 4)
     { warn_void();
      if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
       mtformat_module1(Optimize.it,"`BLUE ~S of type ~S is put in the variable ~S:~S [257]\n",2,list::alloc(4,v48372,
        _oid_(v48373),
        _oid_(v61776),
        GC_OID(_oid_(v61776->range))));
      else ;}
    else (*Optimize.Cerror)(_string_("[212] the value ~S of type ~S cannot be placed in the variable ~S:~S"),
        v48372,
        _oid_(v48373),
        _oid_(v61776),
        GC_OID(_oid_(v61776->range)));
      }
  else if (((CL_INT)Optimize.compiler->safety <= 1) || 
      (boolean_I_any(sort_equal_class(osort_any(GC_OID(_oid_(v61776->range))),osort_any(_oid_(v48373)))) != CTRUE))
   { warn_void();
    if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
     mtformat_module1(Optimize.it,"`BLUE ~S of type ~S is put in the variable ~S:~S [257]\n",2,list::alloc(4,v48372,
      _oid_(v48373),
      _oid_(v61776),
      GC_OID(_oid_(v61776->range))));
    else ;}
  { OID Result = 0;
    if (((CL_INT)Optimize.compiler->safety <= 1) && 
        (_inf_equal_type(v48373,GC_OBJECT(ClaireType,v61776->range)) != CTRUE))
     Result = c_check_any(GC_OID((*Optimize.c_code)(v48372,
      _oid_(Kernel._any))),GC_OID((*Optimize.c_code)(GC_OID(_oid_(v61776->range)),
      _oid_(Kernel._type))));
    else Result = v48372;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  sort_equal_class(ClaireClass *v48351,ClaireClass *v57140)
{ { OID Result = 0;
    if (INHERIT(v48351,Kernel._object))
     Result = _oid_(inherit_ask_class(v57140,Kernel._object));
    else Result = _oid_(((v48351 == v57140) ? CTRUE : ((((Optimize.compiler->overflow_ask != CTRUE) && 
            ((v48351 == Kernel._any) && 
                (v57140 == Kernel._integer))) || 
          ((v48351 == Kernel._integer) && 
              (v57140 == Kernel._any))) ? CTRUE : CFALSE)));
      POP_SIGNAL; return (Result);}
  }

ClaireClass * psort_any(OID v48372)
{ { ClaireClass *Result ;
    { ClaireClass * v48351 = class_I_type(OBJECT(ClaireType,v48372));
      Result = ((INHERIT(v48351,Kernel._object)) ?
        v48351 :
        ((v48351 == Kernel._float) ?
          v48351 :
          sort_I_class(v48351) ) );
      }
    POP_SIGNAL; return (Result);}
  }

ClaireClass * osort_any(OID v48372)
{ { ClaireClass *Result ;
    { ClaireClass * v48351 = class_I_type(OBJECT(ClaireType,v48372));
      Result = ((v48351 == Kernel._float) ?
        v48351 :
        sort_I_class(v48351) );
      }
    POP_SIGNAL; return (Result);}
  }

ClaireClass * sort_Variable(Variable *v48372)
{ GC_BIND;
  { ClaireClass *Result ;
    { ClaireType * v48366 = v48372->range;
      Result = (((INHERIT(v48366->isa,Core._Union)) && (equal(_oid_(CLREAD(Union,v48366,t1)),_oid_(Kernel.emptySet)) == CTRUE)) ?
        psort_any(GC_OID(_oid_(CLREAD(Union,CLREAD(Union,v48366,t2),t2)))) :
        psort_any(_oid_(v48366)) );
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireClass * stupid_t_any1(OID v61776)
{ GC_BIND;
  { ClaireClass *Result ;
    if (INHERIT(OWNER(v61776),Language._Variable))
     { ClaireType * v48366 = GC_OBJECT(ClaireType,OBJECT(Variable,v61776)->range);
      Result = ((sort_abstract_ask_type(v48366) == CTRUE) ?
        Kernel._any :
        (((INHERIT(v48366->isa,Core._Union)) && (equal(_oid_(CLREAD(Union,v48366,t1)),_oid_(Kernel.emptySet)) == CTRUE)) ?
          OBJECT(ClaireClass,(*Core.t1)(GC_OID(_oid_(CLREAD(Union,v48366,t2))))) :
          class_I_type(v48366) ) );
      }
    else if (INHERIT(OWNER(v61776),Core._global_variable))
     { ClaireType * v48366 = OBJECT(global_variable,v61776)->range;
      Result = ((boolean_I_any(_oid_(v48366)) == CTRUE) ?
        class_I_type(v48366) :
        OWNER(OBJECT(global_variable,v61776)->value) );
      }
    else if (INHERIT(OWNER(v61776),Language._And))
     Result = Kernel._boolean;
    else if (INHERIT(OWNER(v61776),Kernel._bag))
     Result = OWNER(v61776);
    else if (INHERIT(OWNER(v61776),Kernel._environment))
     Result = Kernel._environment;
    else if (INHERIT(OWNER(v61776),Kernel._class))
     Result = Kernel._class;
    else if (INHERIT(OWNER(v61776),Language._Call_slot))
     { slot * v48367 = OBJECT(Call_slot,v61776)->selector;
      property * v48364 = v48367->selector;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v57635);
        for (START(v48364->definition); NEXT(v57635);)
        if (Kernel._slot == OBJECT(ClaireObject,v57635)->isa)
         { if (_inf_equal_type(domain_I_restriction(v48367),domain_I_restriction(OBJECT(restriction,v57635))) == CTRUE)
           v48367= OBJECT(slot,v57635);
          }
        }
      Result = class_I_type(v48367->range);
      }
    else if (INHERIT(OWNER(v61776),Language._Call_method))
     Result = class_I_type(OBJECT(Call_method,v61776)->arg->range);
    else if (INHERIT(OWNER(v61776),Language._Call))
     Result = selector_psort_Call(OBJECT(Call,v61776));
    else if (INHERIT(OWNER(v61776),Optimize._to_C))
     Result = OBJECT(Compile_to_C,v61776)->set_arg;
    else if (INHERIT(OWNER(v61776),Optimize._to_protect))
     Result = stupid_t_any1(GC_OID(OBJECT(Compile_to_protect,v61776)->arg));
    else if (INHERIT(OWNER(v61776),Kernel._symbol))
     Result = OWNER(v61776);
    else if (INHERIT(OWNER(v61776),Kernel._char))
     Result = OWNER(v61776);
    else if (Kernel._boolean == OWNER(v61776))
     Result = OWNER(v61776);
    else if (INHERIT(OWNER(v61776),Kernel._primitive))
     Result = OWNER(v61776);
    else if (INHERIT(OWNER(v61776),Language._Assign))
     Result = stupid_t_any1(GC_OID(OBJECT(Assign,v61776)->arg));
    else if (INHERIT(OWNER(v61776),Language._Let))
     Result = stupid_t_any1(GC_OID(OBJECT(Let,v61776)->arg));
    else if (INHERIT(OWNER(v61776),Language._Do))
     Result = stupid_t_any1(GC_OID(last_list(OBJECT(Do,v61776)->args)));
    else if (INHERIT(OWNER(v61776),Language._If))
     Result = meet_class(stupid_t_any1(GC_OID(OBJECT(If,v61776)->arg)),stupid_t_any1(GC_OID(OBJECT(If,v61776)->other)));
    else if (INHERIT(OWNER(v61776),Language._Collect))
     Result = Kernel._list;
    else if (INHERIT(OWNER(v61776),Language._Image))
     Result = Kernel._set;
    else if (INHERIT(OWNER(v61776),Language._Or))
     Result = Kernel._boolean;
    else if (INHERIT(OWNER(v61776),Language._Select))
     Result = Kernel._set;
    else if (INHERIT(OWNER(v61776),Language._Lselect))
     Result = Kernel._list;
    else if (INHERIT(OWNER(v61776),Language._List))
     Result = Kernel._list;
    else if (INHERIT(OWNER(v61776),Language._Set))
     Result = Kernel._set;
    else Result = ((INHERIT(OWNER(v61776),Kernel._thing)) ?
      OWNER(v61776) :
      ((INHERIT(OWNER(v61776),Language._Tuple)) ?
        Kernel._tuple :
        ((INHERIT(OWNER(v61776),Language._Exists)) ?
          ((OBJECT(Exists,v61776)->other == CNULL) ?
            Kernel._any :
            Kernel._boolean ) :
          ((INHERIT(OWNER(v61776),Kernel._integer)) ?
            Kernel._integer :
            Kernel._any ) ) ) );
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * stupid_t_any2(OID v61776,OID v48372)
{ { ClaireBoolean *Result ;
    { ClaireClass * v57138 = stupid_t_any1(v61776);
      ClaireClass * v57140 = stupid_t_any1(v48372);
      Result = ((v57138 != Kernel._any) ? ((v57138 == v57140) ? CTRUE: CFALSE): CFALSE);
      }
    POP_SIGNAL; return (Result);}
  }

ClaireBoolean * extended_ask_type(ClaireType *v61776)
{ { ClaireBoolean *Result ;
    Result = ((INHERIT(v61776->isa,Core._Union)) ?
      ((Kernel._set == CLREAD(Union,v61776,t2)->isa) ? ((boolean_I_any(_oid_(CLREAD(Union,v61776,t2))) == CTRUE) ? (((*(((bag *) CLREAD(Union,v61776,t2))))[1] == CNULL) ? CTRUE: CFALSE): CFALSE): CFALSE) :
      CFALSE );
    POP_SIGNAL; return (Result);}
  }

ClaireType * extends_type(ClaireType *v48372)
{ GC_BIND;
  { ClaireType *Result ;
    { Optimize_optUnion * v47292 = ((Optimize_optUnion *) GC_OBJECT(Optimize_optUnion,new_object_class(Optimize._optUnion)));
      (v47292->t1 = v48372);
      (v47292->t2 = set::alloc(Kernel.emptySet,1,CNULL));
      Result = v47292;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * sort_abstract_I_type(ClaireType *v48372)
{ GC_BIND;
  { ClaireType *Result ;
    if (((_oid_((INHERIT(v48372->isa,Kernel._class) ?
         (ClaireObject *) sort_I_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v48372))) : 
         (ClaireObject *)  sort_I_type((ClaireType *) OBJECT(ClaireType,_oid_(v48372))))) != _oid_(Kernel._any)) && 
          ((_oid_((INHERIT(v48372->isa,Kernel._class) ?
             (ClaireObject *) sort_I_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v48372))) : 
             (ClaireObject *)  sort_I_type((ClaireType *) OBJECT(ClaireType,_oid_(v48372))))) != _oid_(Kernel._integer)) || 
              (Optimize.compiler->overflow_ask == CTRUE))) || 
        (v48372 == Kernel._float))
     { Union * v47292 = ((Union *) GC_OBJECT(Union,new_object_class(Core._Union)));
      (v47292->t1 = Kernel._any);
      (v47292->t2 = v48372);
      Result = v47292;
      }
    else Result = v48372;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * sort_abstract_ask_type(ClaireType *v48372)
{ { ClaireBoolean *Result ;
    Result = ((INHERIT(v48372->isa,Core._Union)) ?
      equal(_oid_(CLREAD(Union,v48372,t1)),_oid_(Kernel._any)) :
      CFALSE );
    POP_SIGNAL; return (Result);}
  }

ClaireType * ptype_type(ClaireType *v48372)
{ { ClaireType *Result ;
    Result = ((INHERIT(v48372->isa,Core._Union)) ?
      ((CLREAD(Union,v48372,t1) == Kernel._any) ?
        CLREAD(Union,v48372,t2) :
        v48372 ) :
      v48372 );
    POP_SIGNAL; return (Result);}
  }

ClaireType * pmember_type(ClaireType *v48372)
{ POP_SIGNAL; return (member_type(ptype_type(v48372)));}

OID  enumerate_code_any(OID v61776,ClaireType *v55283)
{ GC_BIND;
  { OID Result = 0;
    if (_inf_equal_type(ptype_type(v55283),Kernel._bag) == CTRUE)
     Result = c_strict_code_any(v61776,Kernel._bag);
    else { if (Optimize.compiler->optimize_ask == CTRUE)
         { notice_void();
          if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
           mtformat_module1(Optimize.it,"`GREEN explicit enmeration of ~S\n",3,list::alloc(1,v61776));
          else ;}
        Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property1(Core.enumerate,Kernel._any))),list::alloc(1,v61776),list::alloc(1,_oid_(v55283)));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  range_infers_for_Variable(Variable *v61776,ClaireType *v48373,ClaireType *v57731)
{ GC_BIND;
  if (v61776->range == (NULL))
   { if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
     mtformat_module1(Optimize.it,"infer type ~S for ~S \n",5,list::alloc(2,_oid_(v48373),_oid_(v61776)));
    else ;if (INHERIT(v48373->isa,Core._Interval))
     v48373= Kernel._integer;
    (v61776->range = v48373);
    }
  else if ((_inf_equal_type(v48373,GC_OBJECT(ClaireType,v61776->range)) != CTRUE) && 
      ((CL_INT)Optimize.compiler->safety <= 1))
   { if (((boolean_I_any(_oid_(v48373)) == CTRUE) ? ((boolean_I_any(_oid_(v61776->range)) == CTRUE) ? CTRUE: CFALSE): CFALSE) != CTRUE)
     { warn_void();
      if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
       mtformat_module1(Optimize.it,"`BLUE range of variable in ~S is wrong [258]\n",2,list::alloc(1,_oid_(v61776)));
      else ;}
    }
  { OID Result = 0;
    if ((sort_Variable(v61776) != Kernel._any) && 
        (((sort_Variable(v61776) != Kernel._integer) || 
            (Optimize.compiler->overflow_ask == CTRUE)) && 
          (((_inf_equal_type(v57731,Kernel._array) == CTRUE) ? ((_inf_equal_type(v48373,Kernel._float) == CTRUE) ? CTRUE: CFALSE): CFALSE) != CTRUE)))
     { if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
       mtformat_module1(Optimize.it,"protect original sort with ~S \n",5,list::alloc(1,GC_OID(_oid_(sort_abstract_I_type(GC_OBJECT(ClaireType,v61776->range))))));
      else ;Result = _void_((v61776->range = sort_abstract_I_type(GC_OBJECT(ClaireType,v61776->range))));
      }
    else Result = Kernel.cfalse;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  range_infers_Variable(Variable *v61776,ClaireType *v48373)
{ gc_register_Variable(v61776);
  { OID Result = 0;
    if ((v61776->range == (NULL)) || 
        ((extended_ask_type(v61776->range) == CTRUE) && 
            (INHERIT(v61776->range->isa,Optimize._optUnion))))
     { if (Kernel._set == v48373->isa)
       Result = _void_((v61776->range = class_I_type(v48373)));
      else Result = _void_((v61776->range = v48373));
        }
    else Result = Kernel.cfalse;
      POP_SIGNAL; return (Result);}
  }

void  range_infer_case_any(OID v61776,ClaireType *v48373)
{ GC_BIND;
  if (INHERIT(OWNER(v61776),Language._Variable))
   { if (boolean_I_any(sort_equal_class(osort_any(GC_OID(_oid_(OBJECT(Variable,v61776)->range))),osort_any(_oid_(v48373)))) == CTRUE)
     { ClaireClass * v57138 = psort_any(_oid_(class_I_type(GC_OBJECT(ClaireType,OBJECT(Variable,v61776)->range))));
      if (v57138 != psort_any(_oid_(class_I_type(v48373))))
       { Variable * v1426 = OBJECT(Variable,v61776); 
        ClaireType * v1448;
        { Union * v47292 = ((Union *) GC_OBJECT(Union,new_object_class(Core._Union)));
          (v47292->t1 = Kernel.emptySet);
          { Union * v1449 = v47292; 
            ClaireType * v1450;
            { Union * v47292 = ((Union *) GC_OBJECT(Union,new_object_class(Core._Union)));
              (v47292->t1 = v57138);
              (v47292->t2 = v48373);
              v1450 = v47292;
              }
            (v1449->t2 = v1450);}
          v1448 = v47292;
          }
        (v1426->range = v1448);}
      else (OBJECT(Variable,v61776)->range = v48373);
        }
    else if (osort_any(GC_OID(_oid_(OBJECT(Variable,v61776)->range))) == Kernel._any)
     (OBJECT(Variable,v61776)->range = sort_abstract_I_type(v48373));
    }
  GC_UNBIND; POP_SIGNAL;}

OID  c_check_any(OID v48372,OID v48373)
{ GC_BIND;
  { OID Result = 0;
    { method * v48361 = ((method *) _at_property1(Core.check_in,Kernel._any));
      if ((CL_INT)Optimize.compiler->safety > 3)
       Result = v48372;
      else { legal_ask_module(v48361->module_I,_oid_(v48361));
          { Call_method2 * v47292 = ((Call_method2 *) GC_OBJECT(Call_method2,new_object_class(Language._Call_method2)));
            (v47292->arg = v48361);
            (v47292->args = list::alloc(2,GC_OID(c_gc_I_any1(v48372)),GC_OID(c_gc_I_any1(v48373))));
            add_I_property(Kernel.instances,Language._Call_method2,11,_oid_(v47292));
            Result = _oid_(v47292);
            }
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  range_sets_any(OID v61776,ClaireType *v48373)
{ GC_BIND;
  if (INHERIT(OWNER(v61776),Language._Variable))
   { if (boolean_I_any(sort_equal_class(osort_any(GC_OID(_oid_(OBJECT(Variable,v61776)->range))),osort_any(_oid_(v48373)))) == CTRUE)
     { ClaireClass * v57138 = psort_any(_oid_(class_I_type(GC_OBJECT(ClaireType,OBJECT(Variable,v61776)->range))));
      if (v57138 != psort_any(_oid_(class_I_type(v48373))))
       { Variable * v1451 = OBJECT(Variable,v61776); 
        ClaireType * v1452;
        { Union * v47292 = ((Union *) GC_OBJECT(Union,new_object_class(Core._Union)));
          (v47292->t1 = Kernel.emptySet);
          { Union * v1453 = v47292; 
            ClaireType * v1454;
            { Union * v47292 = ((Union *) GC_OBJECT(Union,new_object_class(Core._Union)));
              (v47292->t1 = v57138);
              (v47292->t2 = v48373);
              v1454 = v47292;
              }
            (v1453->t2 = v1454);}
          v1452 = v47292;
          }
        (v1451->range = v1452);}
      else (OBJECT(Variable,v61776)->range = v48373);
        }
    else if (osort_any(GC_OID(_oid_(OBJECT(Variable,v61776)->range))) == Kernel._any)
     (OBJECT(Variable,v61776)->range = sort_abstract_I_type(v48373));
    }
  GC_UNBIND; POP_SIGNAL;}

ClaireClass * c_srange_method(method *v48361)
{ { ClaireClass *Result ;
    Result = ((v48361->range == Kernel._float) ?
      Kernel._float :
      OBJECT(ClaireClass,last_list(v48361->srange)) );
    POP_SIGNAL; return (Result);}
  }

ClaireBoolean * nativeVar_ask_global_variable(global_variable *v48372)
{ POP_SIGNAL; return (CFALSE);}

ClaireType * return_type_any(OID v61776)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { ClaireType *Result ;
    if (INHERIT(OWNER(v61776),Optimize._to_C))
     Result = return_type_any(GC_OID(OBJECT(Compile_to_C,v61776)->arg));
    else if (INHERIT(OWNER(v61776),Optimize._to_protect))
     Result = return_type_any(GC_OID(OBJECT(Compile_to_protect,v61776)->arg));
    else if (INHERIT(OWNER(v61776),Language._Let))
     Result = return_type_any(GC_OID(OBJECT(Let,v61776)->arg));
    else if (INHERIT(OWNER(v61776),Language._Do))
     { set * v48372 = Kernel.emptySet;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v48373);
        bag *v48373_support;
        v48373_support = GC_OBJECT(list,OBJECT(Do,v61776)->args);
        for (START(v48373_support); NEXT(v48373);)
        { GC_LOOP;
          GC__ANY(v48372 = OBJECT(set,(*Kernel._exp)(_oid_(v48372),
            GC_OID(_oid_(return_type_any(v48373))))), 1);
          GC_UNLOOP; POP_SIGNAL;}
        }
      Result = v48372;
      }
    else if (INHERIT(OWNER(v61776),Language._If))
     Result = OBJECT(ClaireType,(*Kernel._exp)(GC_OID(_oid_(return_type_any(GC_OID(OBJECT(If,v61776)->arg)))),
      GC_OID(_oid_(return_type_any(GC_OID(OBJECT(If,v61776)->other))))));
    else if (INHERIT(OWNER(v61776),Language._Return))
     Result = OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(OBJECT(Return,v61776)->arg)));
    else if (INHERIT(OWNER(v61776),Language._Case))
     { set * v48372 = Kernel.emptySet;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v48373);
        bag *v48373_support;
        v48373_support = GC_OBJECT(list,OBJECT(Case,v61776)->args);
        for (START(v48373_support); NEXT(v48373);)
        { GC_LOOP;
          GC__ANY(v48372 = OBJECT(set,(*Kernel._exp)(_oid_(v48372),
            GC_OID(_oid_(return_type_any(v48373))))), 1);
          GC_UNLOOP; POP_SIGNAL;}
        }
      Result = v48372;
      }
    else if (INHERIT(OWNER(v61776),Language._Handle))
     Result = return_type_any(GC_OID(OBJECT(ClaireHandle,v61776)->arg));
    else Result = Kernel.emptySet;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Type_Optimize(Type *v61776,ClaireClass *v48367)
{ GC_BIND;
  { OID Result = 0;
    Result = (*Optimize.c_code)(GC_OID((*Optimize.self_code)(_oid_(v61776))),
      _oid_(v48367));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  self_code_subtype(subtype *v61776)
{ GC_BIND;
  { OID Result = 0;
    { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
      (v47292->selector = Kernel.nth);
      (v47292->args = list::alloc(2,_oid_(v61776->arg),GC_OID((*Optimize.c_code)(GC_OID(_oid_(v61776->t1)),
        _oid_(Kernel._type)))));
      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  self_code_Param(Param *v61776)
{ GC_BIND;
  { OID Result = 0;
    if ((v61776->params->length == 1) && 
        (((*(v61776->params))[1] == _oid_(Kernel.of)) && 
          (Kernel._set == OWNER((*(v61776->args))[1]))))
     { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
      (v47292->selector = Core.param_I);
      (v47292->args = list::alloc(2,_oid_(v61776->arg),GC_OID((*Optimize.c_code)(GC_OID((*Kernel.nth)(GC_OID((*(v61776->args))[1]),
          ((OID)1))),
        _oid_(Kernel._type)))));
      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    else { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
        (v47292->selector = Kernel.nth);
        { Call * v1455 = v47292; 
          list * v1456;
          { OID v_bag;
            GC_ANY(v1456= list::empty(Kernel.emptySet));
            ((list *) v1456)->addFast((OID)_oid_(v61776->arg));
            ((list *) v1456)->addFast((OID)GC_OID(_oid_(v61776->params)));
            { { list * v42564;{ CL_INT loop_handle = ClEnv->cHandle;
                  bag *v_list; OID v_val;
                  OID v48373; CL_INT CLcount;
                  v_list = GC_OBJECT(list,v61776->args);
                   v42564 = v_list->clone();
                  for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                  { v48373 = (*(v_list))[CLcount];
                    v_val = (*Optimize.c_code)(v48373,
                      _oid_(Kernel._type));
                    
                    (*((list *) v42564))[CLcount] = v_val;}
                  }
                
                v_bag=_oid_(v42564);}
              GC_OID(v_bag);}
            ((list *) v1456)->addFast((OID)v_bag);}
          (v1455->args = v1456);}
        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  self_code_Union(Union *v61776)
{ GC_BIND;
  { OID Result = 0;
    { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
      (v47292->selector = Core.U);
      (v47292->args = list::alloc(2,GC_OID((*Optimize.c_code)(GC_OID(_oid_(v61776->t1)),
        _oid_(Kernel._type))),GC_OID((*Optimize.c_code)(GC_OID(_oid_(v61776->t2)),
        _oid_(Kernel._type)))));
      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  self_code_Interval(Interval *v61776)
{ GC_BIND;
  { OID Result = 0;
    { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
      (v47292->selector = Kernel._dot_dot);
      (v47292->args = list::alloc(2,((OID)v61776->arg1),((OID)v61776->arg2)));
      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  self_code_Reference(Reference *v61776)
{ GC_BIND;
  { OID Result = 0;
    { Definition * v47292 = ((Definition *) GC_OBJECT(Definition,new_object_class(Language._Definition)));
      (v47292->arg = Core._Reference);
      { Definition * v1479 = v47292; 
        list * v1480;
        { OID v_bag;
          GC_ANY(v1480= list::empty(Kernel.emptySet));
          { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (v47292->selector = Kernel._equal);
              (v47292->args = list::alloc(2,_oid_(Core.args),GC_OID(_oid_(v61776->args))));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
              v_bag = _oid_(v47292);
              }
            GC_OID(v_bag);}
          ((list *) v1480)->addFast((OID)v_bag);
          { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (v47292->selector = Kernel._equal);
              (v47292->args = list::alloc(2,_oid_(Kernel.index),((OID)v61776->index)));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
              v_bag = _oid_(v47292);
              }
            GC_OID(v_bag);}
          ((list *) v1480)->addFast((OID)v_bag);
          { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (v47292->selector = Kernel._equal);
              (v47292->args = list::alloc(2,_oid_(Kernel.arg),_oid_(v61776->arg)));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
              v_bag = _oid_(v47292);
              }
            GC_OID(v_bag);}
          ((list *) v1480)->addFast((OID)v_bag);}
        (v1479->args = v1480);}
      add_I_property(Kernel.instances,Language._Definition,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  self_code_Pattern(Optimize_ClairePattern *v61776)
{ GC_BIND;
  { OID Result = 0;
    if (Optimize.compiler->inline_ask == CTRUE)
     { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
      (v47292->selector = Kernel.nth);
      { Call * v1481 = v47292; 
        list * v1482;
        { OID v_bag;
          GC_ANY(v1482= list::empty(Kernel.emptySet));
          ((list *) v1482)->addFast((OID)_oid_(v61776->selector));
          { { Tuple * v47292 = ((Tuple *) GC_OBJECT(Tuple,new_object_class(Language._Tuple)));
              (v47292->args = v61776->arg);
              add_I_property(Kernel.instances,Language._Tuple,11,_oid_(v47292));
              v_bag = _oid_(v47292);
              }
            GC_OID(v_bag);}
          ((list *) v1482)->addFast((OID)v_bag);}
        (v1481->args = v1482);}
      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    else Result = _oid_(Language._Call);
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  member_code_class2(ClaireClass *v61776,OID v48372)
{ GC_BIND;
  { OID Result = 0;
    { Call * v10078;
      { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          (v47292->selector = ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v48372))),Kernel._object) == CTRUE) ?
            Kernel.isa :
            Core.owner ));
          (v47292->args = list::alloc(1,v48372));
          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
          v10078 = v47292;
          }
        GC_OBJECT(Call,v10078);}
      if ((((CL_INT)v61776->open <= -1) || 
            (v61776->open == 1)) && 
          (boolean_I_any(_oid_(v61776->subclass)) != CTRUE))
       { OID  v51627;
        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          (v47292->selector = Kernel._equal);
          (v47292->args = list::alloc(2,_oid_(v61776),_oid_(v10078)));
          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
          v51627 = _oid_(v47292);
          }
        Result = (*Optimize.c_code)(v51627);
        }
      else { OID  v52589;
          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            (v47292->selector = Core.inherit_ask);
            (v47292->args = list::alloc(2,_oid_(v10078),_oid_(v61776)));
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
            v52589 = _oid_(v47292);
            }
          Result = (*Optimize.c_code)(v52589);
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  member_code_Type(Type *v61776,OID v48372)
{ GC_BIND;
  { OID Result = 0;
    { Call_method2 * v47292 = ((Call_method2 *) GC_OBJECT(Call_method2,new_object_class(Language._Call_method2)));
      update_property(Kernel.arg,
        v47292,
        2,
        Kernel._object,
        GC_OID(_oid_(_at_property2(Kernel._Z,list::alloc(2,_oid_(Kernel._any),_oid_(Kernel._any))))));
      (v47292->args = list::alloc(2,GC_OID((*Optimize.c_code)(v48372,
        _oid_(Kernel._any))),GC_OID((*Optimize.c_code)(_oid_(v61776),
        _oid_(Kernel._any)))));
      add_I_property(Kernel.instances,Language._Call_method2,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  member_code_Union(Union *v61776,OID v48372)
{ GC_BIND;
  { OID Result = 0;
    { Or * v47292 = ((Or *) GC_OBJECT(Or,new_object_class(Language._Or)));
      (v47292->args = list::alloc(2,GC_OID((*Optimize.member_code)(GC_OID(_oid_(v61776->t1)),
        v48372)),GC_OID((*Optimize.member_code)(GC_OID(_oid_(v61776->t2)),
        v48372))));
      add_I_property(Kernel.instances,Language._Or,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  member_code_Interval(Interval *v61776,OID v48372)
{ GC_BIND;
  { OID Result = 0;
    { OID  v53549;
      { And * v47292 = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
        { And * v1486 = v47292; 
          list * v1487;
          { OID v_bag;
            GC_ANY(v1487= list::empty(Kernel.emptySet));
            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                (v47292->selector = Kernel._sup_equal);
                (v47292->args = list::alloc(2,v48372,((OID)v61776->arg1)));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                v_bag = _oid_(v47292);
                }
              GC_OID(v_bag);}
            ((list *) v1487)->addFast((OID)v_bag);
            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                (v47292->selector = Kernel._inf_equal);
                (v47292->args = list::alloc(2,v48372,((OID)v61776->arg2)));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                v_bag = _oid_(v47292);
                }
              GC_OID(v_bag);}
            ((list *) v1487)->addFast((OID)v_bag);}
          (v1486->args = v1487);}
        add_I_property(Kernel.instances,Language._And,11,_oid_(v47292));
        v53549 = _oid_(v47292);
        }
      Result = (*Optimize.c_code)(v53549,
        _oid_(Kernel._any));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  member_code_Param(Param *v61776,OID v48372)
{ GC_BIND;
  { OID Result = 0;
    { OID  v12038;
      { And * v47292 = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
        { And * v1511 = v47292; 
          list * v1512;
          { list * v14921;
            { { OID v_bag;
                GC_ANY(v14921= list::empty(Kernel.emptySet));
                { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Kernel._Z);
                    (v47292->args = list::alloc(2,v48372,_oid_(v61776->arg)));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v_bag = _oid_(v47292);
                    }
                  GC_OID(v_bag);}
                ((list *) v14921)->addFast((OID)v_bag);}
              GC_OBJECT(list,v14921);}
            list * v15882;
            { list * v28078 = list::empty(Kernel.emptySet);
              { CL_INT  v48357 = 1;
                CL_INT  v1490 = v61776->params->length;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  while (((CL_INT)v48357 <= (CL_INT)v1490))
                  { GC_LOOP;
                    { OID  v16843;
                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        (v47292->selector = Kernel._Z);
                        { Call * v1516 = v47292; 
                          list * v1517;
                          { OID v_bag;
                            GC_ANY(v1517= list::empty(Kernel.emptySet));
                            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                update_property(Kernel.selector,
                                  v47292,
                                  2,
                                  Kernel._object,
                                  GC_OID((*(v61776->params))[v48357]));
                                (v47292->args = list::alloc(1,v48372));
                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                v_bag = _oid_(v47292);
                                }
                              GC_OID(v_bag);}
                            ((list *) v1517)->addFast((OID)v_bag);
                            ((list *) v1517)->addFast((OID)GC_OID((*(v61776->args))[v48357]));}
                          (v1516->args = v1517);}
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                        v16843 = _oid_(v47292);
                        }
                      v28078->addFast((OID)v16843);
                      }
                    ++v48357;
                    GC_UNLOOP;POP_SIGNAL;}
                  }
                }
              v15882 = GC_OBJECT(list,v28078);
              }
            v1512 = append_list(v14921,v15882);
            }
          (v1511->args = v1512);}
        add_I_property(Kernel.instances,Language._And,11,_oid_(v47292));
        v12038 = _oid_(v47292);
        }
      Result = (*Optimize.c_code)(v12038,
        _oid_(Kernel._any));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  member_code_tuple(tuple *v61776,OID v48372)
{ GC_BIND;
  { OID Result = 0;
    if (INHERIT(OWNER(v48372),Language._Tuple))
     { if (length_bag(OBJECT(bag,(*Core.args)(v48372))) != v61776->length)
       Result = Kernel.cfalse;
      else { OID  v20687;
          { And * v47292 = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
            { And * v1541 = v47292; 
              list * v1542;
              { list * v28078 = list::empty(Kernel.emptySet);
                { CL_INT  v48357 = 1;
                  CL_INT  v1518 = v61776->length;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    OID gc_local;
                    while (((CL_INT)v48357 <= (CL_INT)v1518))
                    { GC_LOOP;
                      { OID  v43751;
                        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          (v47292->selector = Kernel._Z);
                          (v47292->args = list::alloc(2,GC_OID((*(OBJECT(bag,(*Core.args)(v48372))))[v48357]),(*(v61776))[v48357]));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                          v43751 = _oid_(v47292);
                          }
                        v28078->addFast((OID)v43751);
                        }
                      ++v48357;
                      GC_UNLOOP;POP_SIGNAL;}
                    }
                  }
                v1542 = GC_OBJECT(list,v28078);
                }
              (v1541->args = v1542);}
            add_I_property(Kernel.instances,Language._And,11,_oid_(v47292));
            v20687 = _oid_(v47292);
            }
          Result = (*Optimize.c_code)(v20687,
            _oid_(Kernel._any));
          }
        }
    else Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property2(Kernel._Z,GC_OBJECT(list,list::alloc(2,_oid_(Kernel._any),_oid_(Kernel._any)))))),GC_OBJECT(list,list::alloc(2,v48372,_oid_(v61776))),GC_OBJECT(list,list::alloc(2,_oid_(Kernel._any),_oid_(Kernel._any))));
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  member_code_any(OID v61776,OID v48372)
{ GC_BIND;
  (Language.LDEF->value= Core.nil->value);
  { OID Result = 0;
    { list * v4955 = list::alloc(2,GC_OID((*Optimize.c_type)(v48372)),GC_OID((*Optimize.c_type)(v61776)));
      OID  v48366 = GC_OID(extract_pattern_any(v61776,Kernel.nil));
      { ClaireBoolean * g0973I;
        { ClaireBoolean *v_or;
          { v_or = ((v48366 == CNULL) ? CTRUE : CFALSE);
            if (v_or == CTRUE) g0973I =CTRUE; 
            else { v_or = ((v61776 == _oid_(Kernel._object)) ? CTRUE : CFALSE);
              if (v_or == CTRUE) g0973I =CTRUE; 
              else { { OID  v45673;
                  if (INHERIT(OWNER(v61776),Core._global_variable))
                   v45673 = _oid_(OBJECT(global_variable,v61776)->range);
                  else v45673 = Kernel.cfalse;
                    v_or = boolean_I_any(v45673);
                  }
                if (v_or == CTRUE) g0973I =CTRUE; 
                else g0973I = CFALSE;}
              }
            }
          }
        
        if (g0973I == CTRUE) Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property2(Kernel._Z,v4955))),list::alloc(2,v48372,v61776),v4955);
          else Result = (*Optimize.member_code)(v48366,
          v48372);
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * _Z_any4(OID v48372,OID v48373)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = (((OBJECT(ClaireBoolean,(*Kernel._inf_equal)(v48372,
      GC_OID(OPT_EVAL((*(OBJECT(Call,v48373)->args))[2]))))) == CTRUE) ? (((OBJECT(ClaireBoolean,(*Kernel._inf_equal)(GC_OID(OPT_EVAL((*(OBJECT(Call,v48373)->args))[1])),
      v48372))) == CTRUE) ? CTRUE: CFALSE): CFALSE);
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * _Z_any5(OID v48372,OID v48373)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = ((belong_to(v48372,OPT_EVAL((*(OBJECT(Call,v48373)->args))[1])) == CTRUE) ? ((equal(v48372,OPT_EVAL((*(OBJECT(Call,v48373)->args))[2])) != CTRUE) ? CTRUE: CFALSE): CFALSE);
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * gcsafe_ask_class(ClaireClass *v61776)
{ POP_SIGNAL; return (((v61776 == Kernel._void) ? CTRUE : 
  (((INHERIT(v61776,Kernel._thing)) && 
      (inherit_ask_class(v61776,Kernel._table) != CTRUE)) ? CTRUE : 
  ((INHERIT(v61776,Kernel._class)) ? CTRUE : 
  (((v61776 != Kernel._object) && 
      ((INHERIT(v61776,Kernel._object)) && 
        (((CL_INT)v61776->open < 3) && 
          ((inherit_ask_class(v61776,Kernel._collection) != CTRUE) && 
            (v61776 != Core._lambda))))) ? CTRUE : 
  ((v61776 == Kernel._integer) ? CTRUE : 
  ((v61776 == Kernel._char) ? CTRUE : 
  ((INHERIT(v61776,Kernel._boolean)) ? CTRUE : 
  ((v61776 == Kernel._function) ? CTRUE : 
  CFALSE)))))))));}

ClaireBoolean * gcsafe_ask_type(ClaireType *v61776)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = ((equal(_oid_(v61776),_oid_(Kernel.emptySet)) == CTRUE) ?
      CTRUE :
      ((INHERIT(v61776->isa,Core._Union)) ?
        (((OBJECT(ClaireBoolean,(*Optimize.gcsafe_ask)(GC_OID(_oid_(CLREAD(Union,v61776,t1)))))) == CTRUE) ? (((OBJECT(ClaireBoolean,(*Optimize.gcsafe_ask)(GC_OID(_oid_(CLREAD(Union,v61776,t2)))))) == CTRUE) ? CTRUE: CFALSE): CFALSE) :
        gcsafe_ask_class(class_I_type(v61776)) ) );
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * gcsafe_ask_property(property *v61776)
{ { ClaireBoolean *Result ;
    { OID  v46634;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v48372);
        v46634= Kernel.cfalse;
        for (START(v61776->restrictions); NEXT(v48372);)
        if (_oid_((INHERIT(v61776->range->isa,Kernel._class) ?
         (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v61776->range))) : 
         (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(v61776->range))))) != Kernel.ctrue)
         { v46634 = Kernel.ctrue;
          ClEnv->cHandle = loop_handle;break;}
        }
      Result = not_any(v46634);
      }
    POP_SIGNAL; return (Result);}
  }

OID  c_gc_I_any1(OID v61776)
{ GC_BIND;
  { OID Result = 0;
    if ((Optimize.OPT->online_ask != CTRUE) && 
        ((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v61776))) == CTRUE))
     { if (should_trace_ask_module1(Optimize.it,4) == CTRUE)
       mtformat_module1(Optimize.it,"`GREEN ---- note: use GC protection on ~S \n",4,list::alloc(1,v61776));
      else ;(Optimize.OPT->protection = CTRUE);
      { Compile_to_protect * v47292 = ((Compile_to_protect *) GC_OBJECT(Compile_to_protect,new_object_class(Optimize._to_protect)));
        (v47292->arg = v61776);
        add_I_property(Kernel.instances,Optimize._to_protect,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      }
    else Result = v61776;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_gc_I_any2(OID v61776,ClaireType *v48368)
{ GC_BIND;
  { OID Result = 0;
    if ((Optimize.OPT->online_ask != CTRUE) && 
        ((((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v61776))) == CTRUE) || 
            ((INHERIT(OWNER(v61776),Language._Let)) && 
                ((*Optimize.gcsafe_ask)(GC_OID((*Optimize.c_type)(v61776))) != Kernel.ctrue))) && 
          (_oid_((INHERIT(v48368->isa,Kernel._class) ?
           (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v48368))) : 
           (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(v48368))))) != Kernel.ctrue)))
     { if (should_trace_ask_module1(Optimize.it,4) == CTRUE)
       mtformat_module1(Optimize.it,"`GREEN ---- note: use GC protection on ~S:~S \n",4,list::alloc(2,v61776,_oid_(v48368)));
      else ;(Optimize.OPT->protection = CTRUE);
      { Compile_to_protect * v47292 = ((Compile_to_protect *) GC_OBJECT(Compile_to_protect,new_object_class(Optimize._to_protect)));
        (v47292->arg = v61776);
        add_I_property(Kernel.instances,Optimize._to_protect,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      }
    else Result = v61776;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * need_protect_any(OID v48372)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = ((INHERIT(OWNER(v48372),Language._Call_slot)) ?
      Optimize.OPT->use_update :
      ((INHERIT(OWNER(v48372),Language._Call_method2)) ?
        ((OBJECT(Call_method,v48372)->arg->selector == Kernel.nth) ?
          ((Optimize.OPT->use_nth_equal == CTRUE) ? CTRUE : ((domain_I_restriction(OBJECT(Call_method,v48372)->arg) == Kernel._class) ? CTRUE : ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)((*(OBJECT(Call_method,v48372)->args))[1]))),Kernel._tuple) == CTRUE) ? CTRUE : CFALSE))) :
          CTRUE ) :
        CTRUE ) );
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

Variable * Variable_I_symbol(symbol *v48367,int v48362,ClaireType *v48368)
{ GC_BIND;
  { Variable *Result ;
    { Variable * v47292 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
      (v47292->pname = v48367);
      (v47292->index = v48362);
      (v47292->range = v48368);
      add_I_property(Kernel.instances,Language._Variable,11,_oid_(v47292));
      Result = v47292;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

list * get_indexed_class_Optimize(ClaireClass *v48351)
{ POP_SIGNAL; return (v48351->slots);}

ClaireBoolean * designated_ask_any(OID v61776)
{ GC_BIND;
  { ClaireBoolean *Result ;
    { ClaireBoolean *v_or;
      { v_or = inherit_ask_class(OWNER(v61776),Kernel._thing);
        if (v_or == CTRUE) Result =CTRUE; 
        else { v_or = inherit_ask_class(OWNER(v61776),Language._Variable);
          if (v_or == CTRUE) Result =CTRUE; 
          else { v_or = inherit_ask_class(OWNER(v61776),Kernel._integer);
            if (v_or == CTRUE) Result =CTRUE; 
            else { v_or = ((Kernel._boolean == OWNER(v61776)) ? CTRUE : CFALSE);
              if (v_or == CTRUE) Result =CTRUE; 
              else { v_or = ((equal(v61776,Core.nil->value) == CTRUE) ? CTRUE : CFALSE);
                if (v_or == CTRUE) Result =CTRUE; 
                else { v_or = ((equal(v61776,_oid_(Kernel.emptySet)) == CTRUE) ? CTRUE : CFALSE);
                  if (v_or == CTRUE) Result =CTRUE; 
                  else { v_or = ((v61776 == CNULL) ? CTRUE : CFALSE);
                    if (v_or == CTRUE) Result =CTRUE; 
                    else { v_or = ((Kernel._float == OWNER(v61776)) ? CTRUE : CFALSE);
                      if (v_or == CTRUE) Result =CTRUE; 
                      else { if (INHERIT(OWNER(v61776),Language._Call))
                         { OID  v48372 = GC_OID((*Optimize.c_code)(v61776));
                          v_or = (((inherit_ask_class(OWNER(v48372),Language._Call) != CTRUE) && 
                              (designated_ask_any(v48372) == CTRUE)) ? CTRUE : ((OBJECT(Call,v61776)->selector == Core.get_stack) ? CTRUE : CFALSE));
                          }
                        else if (INHERIT(OWNER(v61776),Language._Call_slot))
                         v_or = designated_ask_any(GC_OID(OBJECT(Call_slot,v61776)->arg));
                        else if (INHERIT(OWNER(v61776),Language._Call_table))
                         v_or = designated_ask_any(GC_OID(OBJECT(Call_table,v61776)->arg));
                        else if (INHERIT(OWNER(v61776),Optimize._to_protect))
                         v_or = ((need_protect_any(GC_OID(OBJECT(Compile_to_protect,v61776)->arg)) != CTRUE) ? ((designated_ask_any(GC_OID(OBJECT(Compile_to_protect,v61776)->arg)) == CTRUE) ? CTRUE: CFALSE): CFALSE);
                        else if (INHERIT(OWNER(v61776),Language._Call_method))
                         { ClaireBoolean *v_and;
                          { v_and = ((contain_ask_set(Optimize.OPT->simple_operations,_oid_(OBJECT(Call_method,v61776)->arg->selector)) == CTRUE) ? CTRUE : ((OBJECT(Call_method,v61776)->arg == _at_property1(Kernel.nth,Kernel._bag)) ? CTRUE : CFALSE));
                            if (v_and == CFALSE) v_or =CFALSE; 
                            else { { OID  v47595;
                                { CL_INT loop_handle = ClEnv->cHandle;
                                  OID gc_local;
                                  ITERATE(v48373);
                                  v47595= Kernel.cfalse;
                                  bag *v48373_support;
                                  v48373_support = GC_OBJECT(list,OBJECT(Call_method,v61776)->args);
                                  for (START(v48373_support); NEXT(v48373);)
                                  if (designated_ask_any(v48373) != CTRUE)
                                   { v47595 = Kernel.ctrue;
                                    ClEnv->cHandle = loop_handle;break;}
                                  }
                                v_and = not_any(v47595);
                                }
                              if (v_and == CFALSE) v_or =CFALSE; 
                              else v_or = CTRUE;}
                            }
                          }
                        else v_or = ((INHERIT(OWNER(v61776),Optimize._to_CL)) ?
                          designated_ask_any(GC_OID(OBJECT(Compile_to_CL,v61776)->arg)) :
                          ((INHERIT(OWNER(v61776),Optimize._to_C)) ?
                            designated_ask_any(GC_OID(OBJECT(Compile_to_C,v61776)->arg)) :
                            CFALSE ) );
                        if (v_or == CTRUE) Result =CTRUE; 
                        else Result = CFALSE;}
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  gc_register_Variable(Variable *v61776)
{ if ((0 <= (CL_INT)Optimize.OPT->loop_index) && 
      ((CL_INT)v61776->index > (CL_INT)Optimize.OPT->loop_index))
   (Optimize.OPT->loop_index = v61776->index);
  POP_SIGNAL; return (Kernel.ctrue);}

OID  gc_register_Variable2(Variable *v61776,OID v52178)
{ if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
   mtformat_module1(Optimize.it,".... CALL REGISTER ON ~S := ~S \n",5,list::alloc(2,_oid_(v61776),v52178));
  else ;{ OID Result = 0;
    if (inner2outer_ask_any(v52178) == CTRUE)
     Result = gc_register_Variable(v61776);
    else Result = Kernel.cfalse;
      POP_SIGNAL; return (Result);}
  }

ClaireBoolean * inner2outer_ask_any(OID v48372)
{ GC_BIND;
  { ClaireBoolean *Result ;
    if (INHERIT(OWNER(v48372),Optimize._to_protect))
     Result = CTRUE;
    else if (INHERIT(OWNER(v48372),Language._List))
     Result = CTRUE;
    else if (INHERIT(OWNER(v48372),Language._Set))
     Result = CTRUE;
    else if (INHERIT(OWNER(v48372),Language._Variable))
     Result = not_any((*Optimize.gcsafe_ask)(GC_OID(_oid_(OBJECT(Variable,v48372)->range))));
    else Result = ((INHERIT(OWNER(v48372),Language._Call_method)) ?
      (((OBJECT(Call_method,v48372)->arg->selector == Kernel.copy) && 
          (OBJECT(Call_method,v48372)->arg->range == Kernel._bag)) ? CTRUE : (((BCONTAIN(OBJECT(Call_method,v48372)->arg->status,(OID)(4))) && 
          (inner2outer_ask_any(GC_OID((*(OBJECT(Call_method,v48372)->args))[1])) == CTRUE)) ? CTRUE : CFALSE)) :
      ((INHERIT(OWNER(v48372),Optimize._to_CL)) ?
        inner2outer_ask_any(GC_OID(OBJECT(Compile_to_CL,v48372)->arg)) :
        ((INHERIT(OWNER(v48372),Optimize._to_C)) ?
          inner2outer_ask_any(GC_OID(OBJECT(Compile_to_C,v48372)->arg)) :
          ((INHERIT(OWNER(v48372),Language._Let)) ?
            inner2outer_ask_any(GC_OID(_oid_(OBJECT(Instruction_with_var,v48372)->var))) :
            CFALSE ) ) ) );
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * identifiable_ask_any(OID v61776)
{ GC_BIND;
  { ClaireBoolean *Result ;
    { ClaireBoolean *v_or;
      { v_or = ((v61776 == CNULL) ? CTRUE : CFALSE);
        if (v_or == CTRUE) Result =CTRUE; 
        else { if (INHERIT(OWNER(v61776),Optimize._to_CL))
           v_or = identifiable_ask_any(GC_OID(OBJECT(Compile_to_CL,v61776)->arg));
          else { ClaireClass * v48368 = class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v61776))));
              v_or = not_any(_oid_(contain_ask_set(Optimize.OPT->non_identifiable_set,_oid_(v48368))));
              }
            if (v_or == CTRUE) Result =CTRUE; 
          else Result = CFALSE;}
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_inline_method1(method *v61776,list *v48360,ClaireClass *v48367)
{ GC_BIND;
  if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
   mtformat_module1(Optimize.it,"macroexpansion of ~S with method ~S \n",5,list::alloc(2,_oid_(v48360),_oid_(v61776)));
  else ;{ OID Result = 0;
    Result = (*Optimize.c_code)(GC_OID(c_inline_method2(v61776,v48360)),
      _oid_(v48367));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_inline_method2(method *v61776,list *v48360)
{ GC_RESERVE(11);  // v3.0.55 optim !
  { OID Result = 0;
    { lambda * v48354 = GC_OBJECT(lambda,v61776->formula);
      OID  v48372 = GC_OID(v48354->body);
      list * v12092 = GC_OBJECT(list,bound_variables_any(v48372));
      symbol * v16486 = (((v61776->selector == Language.iterate) || 
          (v61776->selector == Language.Iterate)) ?
        OBJECT(Variable,(*(v48354->vars))[2])->pname :
        Kernel._class->name );
      v48372= GC_OID(instruction_copy_any(v48372));
      if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
       mtformat_module1(Optimize.it,"c_inline(~S) on ~S: ~S is bound : ~S \n",5,list::alloc(4,_oid_(v61776),
        _oid_(v48360),
        _oid_(v12092),
        v48372));
      else ;{ CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v48370);
        for (START(v12092); NEXT(v48370);)
        { GC_LOOP;
          { Variable * v57728;
            { { Variable * v47292 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                (v47292->pname = ((OBJECT(Variable,v48370)->pname == v16486) ?
                  v16486 :
                  gensym_void() ));
                (v47292->index = 1000);
                add_I_property(Kernel.instances,Language._Variable,11,_oid_(v47292));
                v57728 = v47292;
                }
              GC_OBJECT(Variable,v57728);}
            store_object(v57728,
              3,
              Kernel._object,
              get_property(Kernel.range,OBJECT(ClaireObject,v48370)),
              CFALSE);
            GC__OID(v48372 = substitution_any(v48372,OBJECT(Variable,v48370),_oid_(v57728)), 5);
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)v12092->length));
      Result = c_substitution_any(v48372,GC_OBJECT(list,v48354->vars),v48360,CFALSE);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_inline_arg_ask_any(OID v61776)
{ GC_BIND;
  { OID Result = 0;
    if (INHERIT(OWNER(v61776),Language._Call))
     { list * v48360 = GC_OBJECT(list,OBJECT(Call,v61776)->args);
      OID  v48361;
      { { list * v49517;
          { { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID v48372; CL_INT CLcount;
              v_list = v48360;
               v49517 = v_list->clone();
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { v48372 = (*(v_list))[CLcount];
                v_val = (*Optimize.c_type)(v48372);
                
                (*((list *) v49517))[CLcount] = v_val;}
              }
            GC_OBJECT(list,v49517);}
          v48361 = restriction_I_property(OBJECT(Call,v61776)->selector,v49517,CTRUE);
          }
        GC_OID(v48361);}
      if (Kernel._method == OWNER(v48361))
       { if ((OBJECT(method,v48361)->inline_ask == CTRUE) && 
            (c_inline_ask_method(OBJECT(method,v48361),v48360) == CTRUE))
         Result = c_inline_method2(OBJECT(method,v48361),v48360);
        else Result = Kernel.cfalse;
          }
      else Result = Core.nil->value;
        }
    else { OID  v50478;
        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          (v47292->selector = Kernel.set_I);
          (v47292->args = list::alloc(1,v61776));
          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
          v50478 = _oid_(v47292);
          }
        Result = c_inline_arg_ask_any(v50478);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_substitution_any(OID v61776,list *v57488,list *v21661,ClaireBoolean *v33183)
{ GC_BIND;
  { OID Result = 0;
    if (INHERIT(OWNER(v61776),Language._Variable))
     { OID  v48357;
      { { OID  v4269 = CNULL;
          { CL_INT  v48358 = 1;
            CL_INT  v1572 = v57488->length;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while (((CL_INT)v48358 <= (CL_INT)v1572))
              { if (OBJECT(Variable,v61776)->pname == OBJECT(Variable,(*(v57488))[v48358])->pname)
                 { v4269= ((OID)v48358);
                  ClEnv->cHandle = loop_handle; break;}
                ++v48358;
                POP_SIGNAL;}
              }
            }
          v48357 = v4269;
          }
        GC_OID(v48357);}
      if (((OID)v48357) != CNULL)
       Result = (*(v21661))[v48357];
      else Result = v61776;
        }
    else if (INHERIT(OWNER(v61776),Kernel._bag))
     { { CL_INT  v48357 = 1;
        CL_INT  v1573 = OBJECT(bag,v61776)->length;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)v48357 <= (CL_INT)v1573))
          { GC_LOOP;
            ((*(OBJECT(list,v61776)))[v48357]=GC_OID(c_substitution_any((*(OBJECT(bag,v61776)))[v48357],v57488,v21661,v33183)));
            ++v48357;
            GC_UNLOOP;POP_SIGNAL;}
          }
        }
      Result = v61776;
      }
    else if (INHERIT(OWNER(v61776),Language._Call))
     { if (OBJECT(Call,v61776)->selector == Core.eval)
       Result = c_substitution_any(GC_OID((*(OBJECT(Call,v61776)->args))[1]),v57488,v21661,((OBJECT(Call,v61776)->args->length == 1) ? CTRUE : (((OBJECT(Call,v61776)->args->length == 2) && 
          (belong_to((*(v21661))[1],(*(OBJECT(Call,v61776)->args))[2]) == CTRUE)) ? CTRUE : CFALSE)));
      else if (v33183 == CTRUE)
       { ClaireHandler c_handle = ClaireHandler();
        if ERROR_IN 
        { { list * v8006;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID v48373; CL_INT CLcount;
                v_list = GC_OBJECT(list,OBJECT(Call,v61776)->args);
                 v8006 = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { v48373 = (*(v_list))[CLcount];
                  v_val = c_substitution_any(v48373,v57488,v21661,CTRUE);
                  
                  (*((list *) v8006))[CLcount] = v_val;}
                }
              GC_OBJECT(list,v8006);}
            Result = apply_property(OBJECT(Call,v61776)->selector,v8006);
            }
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
        { c_handle.catchIt();{ if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
             mtformat_module1(Optimize.it,"a strange problem happens ~A \n",0,GC_OBJECT(list,list::alloc(1,((OID)ClEnv->verbose))));
            else ;warn_void();
            if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
             mtformat_module1(Optimize.it,"`BLUE failed substitution: ~S",2,GC_OBJECT(list,list::alloc(1,GC_OID(_oid_(ClEnv->exception_I)))));
            else ;c_substitution_any(GC_OID(_oid_(OBJECT(Call,v61776)->args)),v57488,v21661,CFALSE);
            Result = v61776;
            }
          }
        else PREVIOUS_HANDLER;}
      else { c_substitution_any(GC_OID(_oid_(OBJECT(Call,v61776)->args)),v57488,v21661,CFALSE);
          Result = v61776;
          }
        }
    else if (INHERIT(OWNER(v61776),Language._Instruction))
     { { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v48367);
        bag *v48367_support;
        v48367_support = OWNER(v61776)->slots;
        for (START(v48367_support); NEXT(v48367);)
        { OID  v48373 = get_slot(OBJECT(slot,v48367),OBJECT(ClaireObject,v61776));
          put_slot(OBJECT(slot,v48367),OBJECT(ClaireObject,v61776),c_substitution_any(v48373,v57488,v21661,v33183));
          }
        }
      Result = v61776;
      }
    else Result = v61776;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  eval_any2(OID v48372,ClaireClass *v48373)
{ POP_SIGNAL; return (OPT_EVAL(v48372));}

list * bound_variables_any(OID v61776)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { list *Result ;
    { list * v48360 = list::empty(Kernel._any);
      if (INHERIT(OWNER(v61776),Language._Instruction_with_var))
       v48360= list::alloc(Kernel._any,1,GC_OID(_oid_(OBJECT(For,v61776)->var)));
      if (INHERIT(OWNER(v61776),Language._Variable))
       ;else if (INHERIT(OWNER(v61776),Language._Instruction))
       { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v48367);
        for (START(OBJECT(ClaireObject,v61776)->isa->slots); NEXT(v48367);)
        { GC_LOOP;
          GC__ANY(v48360 = add_star_list(v48360,GC_OBJECT(list,bound_variables_any(get_slot(OBJECT(slot,v48367),OBJECT(ClaireObject,v61776))))), 1);
          GC_UNLOOP; POP_SIGNAL;}
        }
      else if (INHERIT(OWNER(v61776),Kernel._bag))
       { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v48372);
        for (START(OBJECT(bag,v61776)); NEXT(v48372);)
        { GC_LOOP;
          v48360= add_star_list(v48360,GC_OBJECT(list,bound_variables_any(v48372)));
          GC_UNLOOP; POP_SIGNAL;}
        }
      Result = v48360;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_boolean_any(OID v48372)
{ GC_BIND;
  { OID Result = 0;
    { ClaireType * v57736 = GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v48372)));
      ClaireType * v16496 = ptype_type(v57736);
      if (_inf_equal_type(v16496,Kernel._boolean) == CTRUE)
       { if (INHERIT(OWNER(v48372),Language._Call))
         { if ((OBJECT(Call,v48372)->selector == Core.NOT) && 
              (ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(GC_OID((*(OBJECT(Call,v48372)->args))[1])))) != Kernel._boolean))
           { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (v47292->selector = Core._I_equal);
              { Call * v1575 = v47292; 
                list * v1576;
                { OID v_bag;
                  GC_ANY(v1576= list::empty(Kernel.emptySet));
                  { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      (v47292->selector = Kernel.boolean_I);
                      (v47292->args = list::alloc(1,GC_OID((*(OBJECT(Call,v48372)->args))[1])));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                      v_bag = _oid_(v47292);
                      }
                    GC_OID(v_bag);}
                  ((list *) v1576)->addFast((OID)v_bag);
                  ((list *) v1576)->addFast((OID)Kernel.ctrue);}
                (v1575->args = v1576);}
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
              v48372 = _oid_(v47292);
              }
            GC_OID(v48372);}
          }
        if (_inf_equal_type(v57736,Kernel._boolean) == CTRUE)
         Result = c_strict_code_any(v48372,Kernel._boolean);
        else Result = (*Optimize.c_code)(v48372,
            _oid_(Kernel._boolean));
          }
      else if (_inf_equal_type(v57736,Kernel._bag) == CTRUE)
       { OID  v10889;
        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          (v47292->selector = Core._I_equal);
          { Call * v1578 = v47292; 
            list * v1579;
            { OID v_bag;
              GC_ANY(v1579= list::empty(Kernel.emptySet));
              { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  (v47292->selector = Kernel.length);
                  (v47292->args = list::alloc(1,v48372));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                  v_bag = _oid_(v47292);
                  }
                GC_OID(v_bag);}
              ((list *) v1579)->addFast((OID)v_bag);
              ((list *) v1579)->addFast((OID)((OID)0));}
            (v1578->args = v1579);}
          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
          v10889 = _oid_(v47292);
          }
        Result = (*Optimize.c_code)(v10889);
        }
      else { OID  v13772;
          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            (v47292->selector = Kernel.boolean_I);
            (v47292->args = list::alloc(1,v48372));
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
            v13772 = _oid_(v47292);
            }
          Result = (*Optimize.c_code)(v13772);
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }



