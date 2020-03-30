/***** CLAIRE Compilation of file ./compile/osystem.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:44 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>
#include <Optimize.h>
char * home_void()
{ POP_SIGNAL; return (getenv_string("CLAIRE3_HOME"));}

OID  safe_any2(OID v48372)
{ POP_SIGNAL; return (v48372);}

ClaireType * safe_any2_type(ClaireType *v48372)
{ POP_SIGNAL; return (v48372);}

ClaireType * c_type_any_Optimize(OID v61776)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { ClaireType *Result ;
    { ClaireObject *V_CC ;
      if (INHERIT(OWNER(v61776),Language._Variable))
       { OID  v48366 = GC_OID(get_property(Kernel.range,OBJECT(ClaireObject,v61776)));
        if (v48366 == CNULL)
         V_CC = Kernel._any;
        else V_CC = (((INHERIT(OWNER(v48366),Core._Union)) && (equal(_oid_(OBJECT(Union,v48366)->t1),_oid_(Kernel.emptySet)) == CTRUE)) ?
          CLREAD(Union,OBJECT(Union,v48366)->t2,t2) :
          ptype_type(OBJECT(ClaireType,v48366)) );
        }
      else if (INHERIT(OWNER(v61776),Core._global_variable))
       { ClaireType * v48366 = OBJECT(global_variable,v61776)->range;
        if (boolean_I_any(_oid_(v48366)) == CTRUE)
         V_CC = v48366;
        else V_CC = set::alloc(1,OBJECT(global_variable,v61776)->value);
          }
      else if (INHERIT(OWNER(v61776),Kernel._unbound_symbol))
       V_CC = OBJECT(ClaireType,(*Optimize.Cerror)(_string_("[215] the symbol ~A is unbound_symbol"),
        _oid_(OBJECT(unbound_symbol,v61776)->name)));
      else if (INHERIT(OWNER(v61776),Kernel._error))
       V_CC = Kernel.emptySet;
      else if (INHERIT(OWNER(v61776),Language._Update))
       V_CC = OBJECT(ClaireType,(*Optimize.c_type)(OBJECT(Update,v61776)->value));
      else if (INHERIT(OWNER(v61776),Language._Construct))
       { if (((INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._List)) ? CTRUE : ((INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Set)) ? CTRUE : CFALSE)) != CTRUE)
         V_CC = Kernel._any;
        else { ClaireType * v44127 = Kernel.emptySet;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(v55287);
              for (START(OBJECT(Construct,v61776)->args); NEXT(v55287);)
              { GC_LOOP;
                if (boolean_I_any(_oid_(v44127)) == CTRUE)
                 GC__ANY(v44127 = meet_class(((ClaireClass *) v44127),class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v55287))))), 1);
                else GC__ANY(v44127 = class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v55287)))), 1);
                  GC_UNLOOP; POP_SIGNAL;}
              }
            V_CC = nth_class1(((INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Set)) ?
              Kernel._set :
              Kernel._list ),v44127);
            }
          }
      else if (INHERIT(OWNER(v61776),Language._Instruction))
       close_exception(((general_error *) (*Core._general_error)(_string_("c_type of ~S is not defined"),
        _oid_(list::alloc(1,_oid_(OWNER(v61776)))))));
      else V_CC = set::alloc(1,v61776);
        Result= (ClaireType *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_strict_code_any(OID v48372,ClaireClass *v48367)
{ GC_BIND;
  { OID Result = 0;
    Result = (*Optimize.c_strict_check)(GC_OID((*Optimize.c_code)(v48372,
        _oid_(v48367))),
      _oid_(v48367));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_strict_check_any_Optimize(OID v48372,ClaireClass *v48367)
{ GC_BIND;
  { OID Result = 0;
    if ((Optimize.OPT->online_ask != CTRUE) && 
        ((INHERIT(v48367,Kernel._object)) && 
          (inherit_ask_class(stupid_t_any1(v48372),v48367) != CTRUE)))
     { if ((*Optimize.c_type)(v48372) == _oid_(Kernel._any))
       (*Optimize.Cerror)(_string_("Need explict cast: ~S is not a ~S"),
        v48372,
        _oid_(v48367));
      { Compile_C_cast * v47292 = ((Compile_C_cast *) GC_OBJECT(Compile_C_cast,new_object_class(Optimize._C_cast)));
        (v47292->arg = v48372);
        (v47292->set_arg = v48367);
        add_I_property(Kernel.instances,Optimize._C_cast,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      }
    else Result = v48372;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_any1_Optimize(OID v48372,ClaireClass *v48367)
{ GC_BIND;
  { OID Result = 0;
    { OID  v48373;
      { if (INHERIT(OWNER(v48372),Language._Call))
         v48373 = c_code_call_Call(OBJECT(Call,v48372),v48367);
        else v48373 = (*Optimize.c_code)(v48372);
          GC_OID(v48373);}
      ClaireClass * v48374 = OBJECT(ClaireClass,(*Optimize.c_sort)(v48373));
      if ((v48367 == Kernel._void) || 
          ((v48374 == v48367) || 
            (Optimize.OPT->online_ask == CTRUE)))
       { if ((v48367 == Kernel._void) && 
            ((INHERIT(OWNER(v48372),Language._Call)) && (OBJECT(Call,v48372)->selector == Kernel._equal)))
         { warn_void();
          if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
           mtformat_module1(Optimize.it,"`BLUE -- Equality meant as an assignment: ~S [264]\n",2,list::alloc(1,v48372));
          else ;}
        Result = v48373;
        }
      else if (v48367 == Kernel._any)
       { if (INHERIT(OWNER(v48373),Optimize._to_C))
         Result = OBJECT(Compile_to_C,v48373)->arg;
        else { if (v48374 == Kernel._float)
             { (Optimize.OPT->protection = CTRUE);
              (Optimize.OPT->allocation = CTRUE);
              }
            { Compile_to_CL * v47292 = ((Compile_to_CL *) GC_OBJECT(Compile_to_CL,new_object_class(Optimize._to_CL)));
              (v47292->arg = v48373);
              (v47292->set_arg = psort_any(GC_OID((*Optimize.c_type)(v48373))));
              add_I_property(Kernel.instances,Optimize._to_CL,11,_oid_(v47292));
              Result = _oid_(v47292);
              }
            }
          }
      else if (v48374 == Kernel._any)
       { Compile_to_C * v47292 = ((Compile_to_C *) GC_OBJECT(Compile_to_C,new_object_class(Optimize._to_C)));
        (v47292->arg = v48373);
        (v47292->set_arg = v48367);
        add_I_property(Kernel.instances,Optimize._to_C,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      else Result = v48373;
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_any2_Optimize(OID v61776)
{ GC_BIND;
  { OID Result = 0;
    if (INHERIT(OWNER(v61776),Kernel._unbound_symbol))
     Result = (*Optimize.Cerror)(_string_("[215] the symbol ~A is unbound_symbol"),
      _oid_(OBJECT(unbound_symbol,v61776)->name));
    else if (INHERIT(OWNER(v61776),Language._Variable))
     Result = v61776;
    else if (INHERIT(OWNER(v61776),Core._global_variable))
     { c_register_object(OBJECT(ClaireObject,v61776));
      Result = v61776;
      }
    else if (INHERIT(OWNER(v61776),Language._Optimized_instruction))
     Result = v61776;
    else if (INHERIT(OWNER(v61776),Language._Instruction))
     Result = (*Optimize.Cerror)(_string_("[internal] c_code(~S) should have a parameter"),
      v61776);
    else if (Kernel._set == OWNER(v61776))
     { if (OBJECT(bag,v61776)->length != 0)
       { Set * v48372;
        { { Set * v47292 = ((Set *) GC_OBJECT(Set,new_object_class(Language._Set)));
            (v47292->args = list_I_set(OBJECT(set,v61776)));
            add_I_property(Kernel.instances,Language._Set,11,_oid_(v47292));
            v48372 = v47292;
            }
          GC_OBJECT(Set,v48372);}
        if (of_bag(OBJECT(bag,v61776)) != Kernel._void)
         (v48372->of = of_bag(OBJECT(bag,v61776)));
        Result = (*Optimize.c_code)(_oid_(v48372));
        }
      else Result = v61776;
        }
    else if (INHERIT(OWNER(v61776),Kernel._list))
     { if (OBJECT(bag,v61776)->length != 0)
       { List * v48372;
        { { List * v47292 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
            (v47292->args = OBJECT(list,v61776));
            add_I_property(Kernel.instances,Language._List,11,_oid_(v47292));
            v48372 = v47292;
            }
          GC_OBJECT(List,v48372);}
        if (of_bag(OBJECT(bag,v61776)) != Kernel._void)
         (v48372->of = of_bag(OBJECT(bag,v61776)));
        Result = (*Optimize.c_code)(_oid_(v48372));
        }
      else Result = v61776;
        }
    else if (INHERIT(OWNER(v61776),Kernel._tuple))
     { OID  v29900;
      { Tuple * v47292 = ((Tuple *) GC_OBJECT(Tuple,new_object_class(Language._Tuple)));
        (v47292->args = OBJECT(list,v61776));
        add_I_property(Kernel.instances,Language._Tuple,11,_oid_(v47292));
        v29900 = _oid_(v47292);
        }
      Result = (*Optimize.c_code)(v29900);
      }
    else { if (INHERIT(OWNER(v61776),Kernel._thing))
         (*Optimize.c_register)(v61776);
        if ((Kernel._float == OWNER(v61776)) || 
            (INHERIT(OWNER(v61776),Kernel._function)))
         (Optimize.OPT->allocation = CTRUE);
        Result = v61776;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * c_gc_ask_any(OID v61776)
{ { ClaireBoolean *Result ;
    Result = ((INHERIT(OWNER(v61776),Language._Variable)) ?
      CFALSE :
      ((INHERIT(OWNER(v61776),Core._global_variable)) ?
        not_any(_oid_((INHERIT(OBJECT(global_variable,v61776)->range->isa,Kernel._class) ?
         (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(OBJECT(global_variable,v61776)->range))) : 
         (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(OBJECT(global_variable,v61776)->range)))))) :
        ((INHERIT(OWNER(v61776),Language._Construct)) ?
          ((Optimize.OPT->loop_gc == CTRUE) ? (((INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._List)) || 
              (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Set))) ? CTRUE: CFALSE): CFALSE) :
          ((INHERIT(OWNER(v61776),Language._Instruction)) ?
            CFALSE :
            CFALSE ) ) ) );
    POP_SIGNAL; return (Result);}
  }

ClaireClass * c_sort_any_Optimize(OID v61776)
{ GC_BIND;
  { ClaireClass *Result ;
    { ClaireObject *V_CC ;
      if (INHERIT(OWNER(v61776),Core._global_variable))
       { V_CC = ((nativeVar_ask_global_variable(OBJECT(global_variable,v61776)) == CTRUE) ?
          ((equal(_oid_(OBJECT(global_variable,v61776)->range),_oid_(Kernel.emptySet)) == CTRUE) ?
            osort_any(_oid_(OWNER(OBJECT(global_variable,v61776)->value))) :
            osort_any(_oid_(OBJECT(global_variable,v61776)->range)) ) :
          Kernel._any );
        }
      else if (INHERIT(OWNER(v61776),Language._Instruction))
       { if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Variable))
         V_CC = sort_Variable(OBJECT(Variable,v61776));
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Assign))
         V_CC = sort_Variable(GC_OBJECT(Variable,OBJECT(Variable,OBJECT(Assign,v61776)->var)));
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Call))
         V_CC = osort_any(_oid_(selector_psort_Call(OBJECT(Call,v61776))));
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Call_method))
         { V_CC = (((OBJECT(Call_method,v61776)->arg->selector == Core.externC) && 
              (OBJECT(Call_method,v61776)->args->length == 2)) ?
            psort_any((*(OBJECT(Call_method,v61776)->args))[2]) :
            c_srange_method(OBJECT(Call_method,v61776)->arg) );
          }
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Call_slot))
         V_CC = OBJECT(Call_slot,v61776)->selector->srange;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Call_table))
         V_CC = Kernel._any;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Call_array))
         { V_CC = ((OBJECT(Call_array,v61776)->test == _oid_(Kernel._float)) ?
            Kernel._float :
            Kernel._any );
          }
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Definition))
         V_CC = Kernel._object;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Optimize._to_C))
         V_CC = OBJECT(Compile_to_C,v61776)->set_arg;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Optimize._to_protect))
         V_CC = OBJECT(ClaireClass,(*Optimize.c_sort)(OBJECT(Compile_to_protect,v61776)->arg));
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Update))
         V_CC = OBJECT(ClaireClass,(*Optimize.c_sort)(OBJECT(Update,v61776)->value));
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._If))
         V_CC = psort_any(_oid_(meet_class(OBJECT(ClaireClass,(*Optimize.c_sort)(OBJECT(If,v61776)->arg)),OBJECT(ClaireClass,(*Optimize.c_sort)(OBJECT(If,v61776)->other)))));
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Handle))
         V_CC = psort_any(_oid_(meet_class(OBJECT(ClaireClass,(*Optimize.c_sort)(OBJECT(ClaireHandle,v61776)->arg)),OBJECT(ClaireClass,(*Optimize.c_sort)(OBJECT(ClaireHandle,v61776)->other)))));
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Let))
         V_CC = OBJECT(ClaireClass,(*Optimize.c_sort)(OBJECT(Let,v61776)->arg));
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Optimize._to_CL))
         V_CC = Kernel._any;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Return))
         V_CC = Kernel._any;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._List))
         V_CC = Kernel._object;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Set))
         V_CC = Kernel._object;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Tuple))
         V_CC = Kernel._object;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Construct))
         V_CC = Kernel._any;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Gassign))
         V_CC = Kernel._any;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Super))
         V_CC = Kernel._any;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._For))
         V_CC = Kernel._any;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Ffor))
         V_CC = Kernel._object;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Exists))
         { V_CC = ((OBJECT(Exists,v61776)->other == CNULL) ?
            Kernel._any :
            Kernel._object );
          }
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Iteration))
         V_CC = Kernel._object;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._And))
         V_CC = Kernel._boolean;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Or))
         V_CC = Kernel._boolean;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._While))
         V_CC = Kernel._any;
        else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Do))
         V_CC = OBJECT(ClaireClass,(*Optimize.c_sort)(GC_OID(last_list(OBJECT(Do,v61776)->args))));
        else close_exception(((general_error *) (*Core._general_error)(_string_("[internal] c_sort is not implemented for ~S"),
            _oid_(list::alloc(1,_oid_(OWNER(v61776)))))));
          }
      else V_CC = ((Kernel._float == OWNER(v61776)) ?
        Kernel._float :
        psort_any(GC_OID((*Optimize.c_type)(v61776))) );
      Result= (ClaireClass *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireClass * selector_psort_Call(Call *v61776)
{ { ClaireClass *Result ;
    { property * v48364 = v61776->selector;
      Result = (((v48364 == Core.base_I) || 
          (v48364 == Core.index_I)) ?
        Kernel._integer :
        ((v48364 == Optimize.anyObject_I) ?
          OBJECT(ClaireClass,(*(v61776->args))[1]) :
          ((v48364 == Optimize.object_I) ?
            OBJECT(ClaireClass,(*(v61776->args))[2]) :
            Kernel._any ) ) );
      }
    POP_SIGNAL; return (Result);}
  }

CL_INT  c_status_any(OID v61776,list *v48360)
{ GC_BIND;
  { CL_INT Result = 0;
    if (INHERIT(OWNER(v61776),Language._Instruction))
     { if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Variable))
       { Result = (((OBJECT(Variable,v61776)->range == (NULL)) || 
            ((*Optimize.gcsafe_ask)(GC_OID(_oid_(OBJECT(Variable,v61776)->range))) != Kernel.ctrue)) ?
          ((contain_ask_list(v48360,v61776) == CTRUE) ?
            16 :
            (((((OBJECT(Variable,v61776)->range == (NULL)) ? CTRUE : CFALSE) != CTRUE) && 
                (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(Variable,v61776)->range),Kernel._float) == CTRUE)) ?
              2 :
              0 ) ) :
          32 );
        }
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Error))
       Result = 32;
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Printf))
       { CL_INT  v25868;
        { CL_INT  v1325 = 0;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v1327);
            bag *v1327_support;
            v1327_support = GC_OBJECT(list,OBJECT(Construct,v61776)->args);
            for (START(v1327_support); NEXT(v1327);)
            { CL_INT  v1326 = c_status_any(v1327,v48360);
              v1325= c_or_integer(v1325,v1326);
              }
            }
          v25868 = v1325;
          }
        Result = c_return_integer(0,v25868);
        }
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Construct))
       Result = 2;
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Definition))
       Result = 2;
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Call))
       { CL_INT  v57603 = c_status_property(OBJECT(Call,v61776)->selector);
        CL_INT  v57604;
        { CL_INT  v1328 = 0;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v1330);
            bag *v1330_support;
            v1330_support = GC_OBJECT(list,OBJECT(Call,v61776)->args);
            for (START(v1330_support); NEXT(v1330);)
            { CL_INT  v1329 = c_status_any(v1330,v48360);
              v1328= c_or_integer(v1328,v1329);
              }
            }
          v57604 = v1328;
          }
        Result = c_return_integer(v57603,v57604);
        }
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._If))
       { CL_INT  v57603 = c_status_any(GC_OID(OBJECT(If,v61776)->arg),v48360);
        CL_INT  v57604 = c_status_any(GC_OID(OBJECT(If,v61776)->other),v48360);
        Result = c_return_integer(c_or_integer(v57603,v57604),c_status_any(GC_OID(OBJECT(If,v61776)->test),v48360));
        }
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Do))
       { OID  v48373 = GC_OID(last_list(OBJECT(Do,v61776)->args));
        CL_INT  v57603 = c_status_any(v48373,v48360);
        CL_INT  v57604;
        { CL_INT  v1331 = 0;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v1333);
            bag *v1333_support;
            v1333_support = GC_OBJECT(list,OBJECT(Do,v61776)->args);
            for (START(v1333_support); NEXT(v1333);)
            if (equal(v1333,v48373) != CTRUE)
             { CL_INT  v1332 = c_status_any(v1333,v48360);
              v1331= c_or_integer(v1331,v1332);
              }
            }
          v57604 = v1331;
          }
        Result = c_return_integer(v57603,v57604);
        }
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._For))
       Result = c_return_integer(c_status_any(GC_OID(OBJECT(Iteration,v61776)->arg),v48360),c_status_any(GC_OID(OBJECT(Iteration,v61776)->set_arg),v48360));
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Ffor))
       Result = c_return_integer(c_status_any(GC_OID(OBJECT(iClaire_Ffor,v61776)->arg),v48360),c_or_integer(c_status_any(GC_OID(OBJECT(iClaire_Ffor,v61776)->set_arg),v48360),c_status_any(GC_OID(OBJECT(iClaire_Ffor,v61776)->forkedby),v48360)));
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Iteration))
       Result = c_return_integer(2,c_status_any(GC_OID(OBJECT(Iteration,v61776)->arg),v48360));
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Let))
       Result = c_return_integer(c_status_any(GC_OID(OBJECT(Let,v61776)->arg),v48360),c_status_any(GC_OID(OBJECT(Let,v61776)->value),v48360));
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Assign))
       Result = c_status_any(GC_OID(OBJECT(Assign,v61776)->arg),v48360);
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Gassign))
       Result = c_status_any(GC_OID(OBJECT(Gassign,v61776)->arg),v48360);
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._And))
       { CL_INT  v26829;
        { CL_INT  v1355 = 0;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v1357);
            bag *v1357_support;
            v1357_support = GC_OBJECT(list,OBJECT(And,v61776)->args);
            for (START(v1357_support); NEXT(v1357);)
            { CL_INT  v1356 = c_status_any(v1357,v48360);
              v1355= c_or_integer(v1355,v1356);
              }
            }
          v26829 = v1355;
          }
        Result = c_return_integer(0,v26829);
        }
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Or))
       { CL_INT  v27790;
        { CL_INT  v1358 = 0;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v1360);
            bag *v1360_support;
            v1360_support = GC_OBJECT(list,OBJECT(Or,v61776)->args);
            for (START(v1360_support); NEXT(v1360);)
            { CL_INT  v1359 = c_status_any(v1360,v48360);
              v1358= c_or_integer(v1358,v1359);
              }
            }
          v27790 = v1358;
          }
        Result = c_return_integer(0,v27790);
        }
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Cast))
       Result = c_status_any(GC_OID(OBJECT(Cast,v61776)->arg),v48360);
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Super))
       { CL_INT  v57603 = c_status_property(OBJECT(Super,v61776)->selector);
        CL_INT  v57604;
        { CL_INT  v1361 = 0;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v1363);
            bag *v1363_support;
            v1363_support = GC_OBJECT(list,OBJECT(Super,v61776)->args);
            for (START(v1363_support); NEXT(v1363);)
            { CL_INT  v1362 = c_status_any(v1363,v48360);
              v1361= c_or_integer(v1361,v1362);
              }
            }
          v57604 = v1361;
          }
        Result = c_return_integer(v57603,v57604);
        }
      else if (INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Case))
       { CL_INT  v1364 = 0;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v1387);
          bag *v1387_support;
          v1387_support = GC_OBJECT(list,OBJECT(Case,v61776)->args);
          for (START(v1387_support); NEXT(v1387);)
          { CL_INT  v1386 = c_status_any(v1387,v48360);
            v1364= c_or_integer(v1364,v1386);
            }
          }
        Result = v1364;
        }
      else Result = ((INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._While)) ?
        c_return_integer(c_status_any(GC_OID(OBJECT(While,v61776)->arg),v48360),c_status_any(GC_OID(OBJECT(While,v61776)->test),v48360)) :
        ((INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Return)) ?
          c_status_any(GC_OID(OBJECT(Return,v61776)->arg),v48360) :
          ((INHERIT(OBJECT(ClaireObject,v61776)->isa,Language._Handle)) ?
            c_return_integer(c_or_integer(c_status_any(GC_OID(OBJECT(ClaireHandle,v61776)->arg),v48360),c_status_any(GC_OID(OBJECT(ClaireHandle,v61776)->other),v48360)),c_status_any(GC_OID(OBJECT(ClaireHandle,v61776)->test),v48360)) :
            ((INHERIT(OBJECT(ClaireObject,v61776)->isa,Kernel._unbound_symbol)) ?
              0 :
              (*Optimize.Cerror)(_string_("[internal] oops .. I forgot ~S"),
                _oid_(OWNER(v61776))) ) ) ) );
      }
    else Result = ((Kernel._float == OWNER(v61776)) ?
      2 :
      ((Kernel._string == OWNER(v61776)) ?
        2 :
        ((INHERIT(OWNER(v61776),Kernel._function)) ?
          2 :
          ((INHERIT(OWNER(v61776),Core._Type)) ?
            2 :
            0 ) ) ) );
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

CL_INT  c_or_integer(CL_INT v48372,CL_INT v48373)
{ { CL_INT Result = 0;
    { CL_INT  v48352 = or_integer(v48372,v48373);
      if ((BCONTAIN(v48352,(OID)(5))) && 
          (((BCONTAIN(v48372,(OID)(5))) ? ((BCONTAIN(v48373,(OID)(5))) ? CTRUE: CFALSE): CFALSE) != CTRUE))
       v48352= ((CL_INT)v48352-(CL_INT)exp2_integer(5));
      if ((BCONTAIN(v48352,(OID)(6))) && 
          (((BCONTAIN(v48372,(OID)(6))) ? ((BCONTAIN(v48373,(OID)(6))) ? CTRUE: CFALSE): CFALSE) != CTRUE))
       v48352= ((CL_INT)v48352-(CL_INT)exp2_integer(6));
      Result = v48352;
      }
    POP_SIGNAL; return (Result);}
  }

CL_INT  c_or_list(list *v48360)
{ { CL_INT Result = 0;
    { CL_INT  v48352 = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v48372);
        for (START(v48360); NEXT(v48372);)
        v48352= c_or_integer(v48352,v48372);
        }
      Result = v48352;
      }
    POP_SIGNAL; return (Result);}
  }

CL_INT  status_I_restriction(restriction *v61776)
{ GC_BIND;
  { CL_INT Result = 0;
    if (Kernel._method == v61776->isa)
     { if (((CLREAD(method,v61776,status) == (CNULL)) ? CTRUE : CFALSE) != CTRUE)
       Result = CLREAD(method,v61776,status);
      else if (CLREAD(method,v61776,formula) == (NULL))
       { (CLREAD(method,v61776,status) = 0);
        Result = 0;
        }
      else { (CLREAD(method,v61776,status) = 0);
          (CLREAD(method,v61776,status) = c_status_any(GC_OID(CLREAD(method,v61776,formula)->body),GC_OBJECT(list,CLREAD(method,v61776,formula)->vars)));
          if (should_trace_ask_module1(Optimize.it,4) == CTRUE)
           mtformat_module1(Optimize.it,"status(~S) = ~S \n",4,list::alloc(2,_oid_(v61776),((OID)CLREAD(method,v61776,status))));
          else ;Result = CLREAD(method,v61776,status);
          }
        }
    else Result = 0;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

CL_INT  c_return_integer(CL_INT v48372,CL_INT v48373)
{ { CL_INT Result = 0;
    { CL_INT  v48352 = or_integer(v48372,v48373);
      if ((nth_integer(v48372,(OID)(5)) != CTRUE) && 
          (BCONTAIN(v48373,(OID)(5))))
       v48352= ((CL_INT)v48352-(CL_INT)exp2_integer(5));
      if ((nth_integer(v48372,(OID)(4)) != CTRUE) && 
          (BCONTAIN(v48373,(OID)(4))))
       v48352= ((CL_INT)v48352-(CL_INT)exp2_integer(4));
      Result = v48352;
      }
    POP_SIGNAL; return (Result);}
  }

CL_INT  c_status_property(property *v61776)
{ { CL_INT Result = 0;
    { CL_INT  v48366 = ((stable_ask_relation(v61776) == CTRUE) ?
        0 :
        (*Language.bit_vector)(((OID)1),
          (OID)(2),
          (OID)(3)) );
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v48372);
        for (START(v61776->restrictions); NEXT(v48372);)
        { if ((((*Kernel.srange)(v48372) == _oid_(Kernel._integer)) ? CTRUE : (((*Kernel.srange)(v48372) == _oid_(Kernel._object)) ? CTRUE : (((*Kernel.srange)(v48372) == _oid_(Kernel._any)) ? CTRUE : CFALSE))) != CTRUE)
           v48366= c_or_integer(v48366,2);
          if (Kernel._method == OBJECT(ClaireObject,v48372)->isa)
           v48366= c_or_integer(v48366,status_I_restriction(OBJECT(restriction,v48372)));
          else if (Kernel._slot == OBJECT(ClaireObject,v48372)->isa)
           v48366= c_or_integer(v48366,exp2_integer(4));
          }
        }
      Result = v48366;
      }
    POP_SIGNAL; return (Result);}
  }

OID  showstatus_method2(method *v48361)
{ { OID Result = 0;
    { list * v57417 = list::alloc(6,_string_("NEW_ALLOC"),
        _string_("BAG_UPDATE"),
        _string_("SLOT_UPDATE"),
        _string_("RETURN_ARG"),
        _string_("SAFE_RESULT"),
        _string_("SAFE_GC"));
      list * v48360 = list::empty(Kernel._any);
      CL_INT  v48367 = v48361->status;
      { CL_INT  v48357 = 1;
        CL_INT  v1391 = 6;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)v48357 <= (CL_INT)v1391))
          { if (BCONTAIN(v48367,v48357))
             v48360= v48360->addFast((OID)(*(v57417))[v48357]);
            ++v48357;
            POP_SIGNAL;}
          }
        }
      Result = _oid_(v48360);
      }
    POP_SIGNAL; return (Result);}
  }

void  s_test_method2(method *v48361)
{ GC_BIND;
  { lambda * v57465 = GC_OBJECT(lambda,v48361->formula);
    CL_INT  v44247 = c_status_any(GC_OID(v57465->body),GC_OBJECT(list,v57465->vars));
    if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
     mtformat_module1(Optimize.it,"status(~S) := ~S \n",0,list::alloc(2,_oid_(v48361),((OID)v44247)));
    else ;(v48361->status = v44247);
    showstatus_method2(v48361);
    }
  GC_UNBIND; POP_SIGNAL;}

ClaireBoolean * legal_ask_module(module *v61776,OID v48372)
{ if ((v48372 == _oid_(Optimize.object_I)) || 
      (v48372 == _oid_(Optimize.anyObject_I))) 
  { { ClaireBoolean *Result ;
      Result = CTRUE;
      return (Result);}
     }
  else{ GC_BIND;
    { ClaireBoolean *Result ;
      if (Optimize.OPT->legal_modules->length != 0)
       { if ((contain_ask_set(Optimize.OPT->legal_modules,_oid_(v61776)) != CTRUE) && 
            ((Kernel._method == OWNER(v48372)) && ((OBJECT(method,v48372)->inline_ask == CFALSE) || 
                (Optimize.compiler->inline_ask != CTRUE))))
         { if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
           mtformat_module1(Optimize.it,"legal_modules = ~S\n",0,list::alloc(1,GC_OID(_oid_(Optimize.OPT->legal_modules))));
          else ;if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
           mtformat_module1(Optimize.it,"---- ERROR: ~S implies using ~S !\n\n",0,list::alloc(2,v48372,_oid_(v61776)));
          else ;Result = CFALSE;
          }
        else Result = CTRUE;
          }
      else { GC_OBJECT(set,Optimize.OPT->need_modules)->addFast((OID)_oid_(v61776));
          Result = CTRUE;
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  }

OID  legal_ask_environment(ClaireEnvironment *v61776,OID v48372)
{ POP_SIGNAL; return (Kernel.ctrue);}

OID  c_register_object(ClaireObject *v61776)
{ GC_BIND;
  { OID Result = 0;
    { OID  v48372 = GC_OID(get_module_object(v61776));
      if (v48372 != _oid_(ClEnv))
       Result = (*Optimize.legal_ask)(v48372,
        _oid_(v61776));
      else Result = Kernel.ctrue;
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_register_property(property *v61776)
{ GC_BIND;
  { OID Result = 0;
    { module * v48361 = ClEnv->module_I;
      OID  v57449 = GC_OID(get_module_object(v61776));
      if (((v57449 == _oid_(claire.it)) || 
            (v57449 == _oid_(v48361))) && 
          (Optimize.OPT->objects->memq(_oid_(v61776)) != CTRUE))
       GC_OBJECT(set,Optimize.OPT->properties)->addFast((OID)_oid_(v61776));
      Result = c_register_object(v61776);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  selector_register_property(property *v61776)
{ c_register_property(v61776);
  if (allocate_ask_property(v61776) == Kernel.ctrue)
   (Optimize.OPT->allocation = CTRUE);
  POP_SIGNAL; return (_oid_(v61776));}

OID  allocate_ask_property(property *v61776)
{ { OID Result = 0;
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v48372);
      Result= Kernel.cfalse;
      for (START(v61776->restrictions); NEXT(v48372);)
      if (Kernel._slot == OBJECT(ClaireObject,v48372)->isa)
       { if ((_oid_((INHERIT(OBJECT(restriction,v48372)->range->isa,Kernel._class) ?
           (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(OBJECT(restriction,v48372)->range))) : 
           (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(OBJECT(restriction,v48372)->range))))) != Kernel.ctrue) && 
            (OBJECT(slot,v48372)->srange != Kernel._any))
         { Result = Kernel.ctrue;
          ClEnv->cHandle = loop_handle;break;}
        else if ((_oid_((INHERIT(OBJECT(restriction,v48372)->range->isa,Kernel._class) ?
           (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(OBJECT(restriction,v48372)->range))) : 
           (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(OBJECT(restriction,v48372)->range))))) != Kernel.ctrue) && 
            (gcsafe_ask_class(domain_I_restriction(OBJECT(restriction,v48372))) != CTRUE))
         { Result = ((OID)0);
          ClEnv->cHandle = loop_handle;break;}
        }
      else if (Kernel._method == OBJECT(ClaireObject,v48372)->isa)
       { if ((BCONTAIN(status_I_restriction(OBJECT(restriction,v48372)),(OID)(1))) || 
            ((((c_srange_method(OBJECT(method,v48372)) == Kernel._integer) ? CTRUE : ((c_srange_method(OBJECT(method,v48372)) == Kernel._object) ? CTRUE : ((c_srange_method(OBJECT(method,v48372)) == Kernel._any) ? CTRUE : CFALSE))) != CTRUE) || 
              (_oid_((INHERIT(OBJECT(restriction,v48372)->range->isa,Kernel._class) ?
               (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(OBJECT(restriction,v48372)->range))) : 
               (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(OBJECT(restriction,v48372)->range))))) != Kernel.ctrue)))
         { Result = Kernel.ctrue;
          ClEnv->cHandle = loop_handle;break;}
        }
      }
    POP_SIGNAL; return (Result);}
  }

ClaireBoolean * stable_ask_relation(ClaireRelation *v61776)
{ GC_BIND;
  { OID  v48361 = GC_OID(get_module_object(v61776));
    if ((v61776->open == 2) && 
        ((contain_ask_set(Optimize.OPT->legal_modules,v48361) == CTRUE) || 
            (v48361 == _oid_(ClEnv))))
     (v61776->open = 1);
    }
  { ClaireBoolean *Result ;
    Result = (((CL_INT)v61776->open <= 1) ? CTRUE : ((v61776->open == 4) ? CTRUE : CFALSE));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  get_module_object(ClaireObject *v61776)
{ POP_SIGNAL; return (_oid_(defined_symbol(OBJECT(symbol,(*Kernel.name)(_oid_(v61776))))));}

OID  known_I_listargs(listargs *v48360)
{ GC_BIND;
  GC_OBJECT(set,Optimize.OPT->to_remove)->addFast((OID)_oid_(Reader.known_I));
  { OID Result = 0;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v48366);
      Result= Kernel.cfalse;
      for (START(v48360); NEXT(v48366);)
      { GC_LOOP;
        if (INHERIT(OWNER(v48366),Kernel._property))
         GC_OBJECT(set,Optimize.OPT->knowns)->addFast((OID)v48366);
        GC_UNLOOP; POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  oload_module(module *v48361)
{ load_module(v48361);
  POP_SIGNAL; return (turbo_module(v48361));}

OID  oload_string(char *v48354)
{ load_string(v48354);
  POP_SIGNAL; return (turbo_module(ClEnv->module_I));}

OID  turbo_module(module *v48361)
{ GC_RESERVE(5);  // v3.0.55 optim !
  { OID Result = 0;
    { CL_INT  v57776 = ClEnv->verbose;
      (Optimize.OPT->online_ask = CTRUE);
      (ClEnv->verbose = 0);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v48372);
        bag *v48372_support;
        v48372_support = Kernel._method->instances;
        for (START(v48372_support); NEXT(v48372);)
        { GC_LOOP;
          if ((OBJECT(restriction,v48372)->module_I == v48361) && 
              ((OBJECT(method,v48372)->inline_ask != CTRUE) && 
                (((OBJECT(method,v48372)->formula == (NULL)) ? CTRUE : CFALSE) != CTRUE)))
           { lambda * v48360 = GC_OBJECT(lambda,OBJECT(method,v48372)->formula);
            OID  v48373 = GC_OID(v48360->body);
            { ClaireHandler c_handle = ClaireHandler();
              if ERROR_IN 
              { { if (OBJECT(restriction,v48372)->range == Kernel._any)
                   update_property(Kernel.range,
                    OBJECT(ClaireObject,v48372),
                    5,
                    Kernel._object,
                    GC_OID((*Optimize.c_type)(v48373)));
                  (v48360->body = (*Optimize.c_code)(v48373,
                    _oid_(Kernel._any)));
                  (Language._starvariable_index_star->value= ((OID)((CL_INT)v48360->vars->length+(CL_INT)1)));
                  (v48360->body = lexical_build_any(GC_OID(v48360->body),GC_OBJECT(list,v48360->vars),Language._starvariable_index_star->value));
                  (v48360->dimension = Language._starvariable_index_star->value);
                  }
                ERROR_FREE;}
              else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
              { c_handle.catchIt();{ (v48360->body = v48373);
                  ;}
                }
              else PREVIOUS_HANDLER;}
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      (Optimize.OPT->online_ask = CFALSE);
      (ClEnv->verbose = v57776);
      Result = Kernel.ctrue;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  stats_meta_OPT(Optimize_meta_OPT *v48372)
{ ;POP_SIGNAL;}



