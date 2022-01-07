/***** CLAIRE Compilation of file ./compile/osystem.cl 
         [version 3.5.0 / safety 5] *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllexport)
#endif
#include <Optimize.h>

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllimport)
#endif

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllexport)
#endif
CL_EXPORT char * home_void() { 
    POP_SIGNAL; return (getenv_string(((char*)"CLAIRE3_HOME")));}
  

CL_EXPORT OID  safe_any2(OID v8240) { 
    POP_SIGNAL; return (v8240);}
  

CL_EXPORT ClaireType * safe_any2_type(ClaireType *v8240) { 
    POP_SIGNAL; return (v8240);}
  

CL_EXPORT ClaireType * c_type_any_Optimize(OID v62612) { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    { ClaireType *Result ;
      { ClaireObject *V_CC ;
        if (INHERIT(OWNER(v62612),Language._Variable))
         { OID  v8234 = GC_OID(get_property(Kernel.range,OBJECT(ClaireObject,v62612)));
          if (v8234 == CNULL)
           V_CC = Kernel._any;
          else V_CC = (((INHERIT(OWNER(v8234),Core._Union)) && (equal(_oid_(OBJECT(Union,v8234)->t1),_oid_(Kernel.emptySet)) == CTRUE)) ?
            CLREAD(Union,OBJECT(Union,v8234)->t2,t2) :
            ptype_type(OBJECT(ClaireType,v8234)) );
          }
        else if (INHERIT(OWNER(v62612),Core._global_variable))
         { ClaireType * v8234 = OBJECT(global_variable,v62612)->range;
          if (boolean_I_any(_oid_(v8234)) == CTRUE)
           V_CC = v8234;
          else V_CC = set::alloc(1,OBJECT(global_variable,v62612)->value);
            }
        else if (INHERIT(OWNER(v62612),Kernel._unbound_symbol))
         V_CC = OBJECT(ClaireType,(*Optimize.Cerror)(_string_(((char*)"[215] the symbol ~A is unbound_symbol")),
          _oid_(OBJECT(unbound_symbol,v62612)->name)));
        else if (INHERIT(OWNER(v62612),Kernel._error))
         V_CC = Kernel.emptySet;
        else if (INHERIT(OWNER(v62612),Language._Update))
         V_CC = OBJECT(ClaireType,(*Optimize.c_type)(OBJECT(Update,v62612)->value));
        else if (INHERIT(OWNER(v62612),Language._Construct))
         { if (((INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._List)) ? CTRUE : ((INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Set)) ? CTRUE : CFALSE)) != CTRUE)
           V_CC = Kernel._any;
          else { ClaireType * v44963 = Kernel.emptySet;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(v56379);
                for (START(OBJECT(Construct,v62612)->args); NEXT(v56379);)
                { GC_LOOP;
                  if (boolean_I_any(_oid_(v44963)) == CTRUE)
                   GC__ANY(v44963 = meet_class(((ClaireClass *) v44963),class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v56379))))), 1);
                  else GC__ANY(v44963 = class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v56379)))), 2);
                    GC_UNLOOP; POP_SIGNAL;}
                }
              V_CC = nth_class1(((INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Set)) ?
                Kernel._set :
                Kernel._list ),v44963);
              }
            }
        else if (INHERIT(OWNER(v62612),Language._Instruction))
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"c_type of ~S is not defined")),
          _oid_(list::alloc(1,_oid_(OWNER(v62612)))))));
        else V_CC = set::alloc(1,v62612);
          Result= (ClaireType *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_strict_code_any(OID v8240,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      Result = (*Optimize.c_strict_check)(GC_OID((*Optimize.c_code)(v8240,
          _oid_(v8235))),
        _oid_(v8235));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_strict_check_any_Optimize(OID v8240,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      if ((Optimize.OPT->online_ask != CTRUE) && 
          ((INHERIT(v8235,Kernel._object)) && 
            (inherit_ask_class(stupid_t_any1(v8240),v8235) != CTRUE)))
       { if ((*Optimize.c_type)(v8240) == _oid_(Kernel._any))
         (*Optimize.Cerror)(_string_(((char*)"Need explict cast: ~S is not a ~S")),
          v8240,
          _oid_(v8235));
        { Compile_C_cast * v60472 = ((Compile_C_cast *) GC_OBJECT(Compile_C_cast,new_object_class(Optimize._C_cast)));
          _void_(v60472->arg = v8240);
          _void_(v60472->set_arg = v8235);
          add_I_property(Kernel.instances,Optimize._C_cast,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        }
      else Result = v8240;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_any1_Optimize(OID v8240,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v8241;
        { if (INHERIT(OWNER(v8240),Language._Call))
           v8241 = c_code_call_Call(OBJECT(Call,v8240),v8235);
          else v8241 = (*Optimize.c_code)(v8240);
            GC_OID(v8241);}
        ClaireClass * v8242 = OBJECT(ClaireClass,(*Optimize.c_sort)(v8241));
        if ((v8235 == Kernel._void) || 
            ((v8242 == v8235) || 
              (Optimize.OPT->online_ask == CTRUE)))
         { if ((v8235 == Kernel._void) && 
              ((INHERIT(OWNER(v8240),Language._Call)) && (OBJECT(Call,v8240)->selector == Kernel._equal)))
           { warn_void();
            if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
             mtformat_module1(Optimize.it,((char*)"  `BLUE note: Equality meant as an assignment: ~S [264]\n"),2,list::alloc(1,v8240));
            else ;}
          Result = v8241;
          }
        else if (v8235 == Kernel._any)
         { if (INHERIT(OWNER(v8241),Optimize._to_C))
           Result = OBJECT(Compile_to_C,v8241)->arg;
          else { if (v8242 == Kernel._float)
               { _void_(Optimize.OPT->protection = CTRUE);
                _void_(Optimize.OPT->allocation = CTRUE);
                }
              { Compile_to_CL * v60472 = ((Compile_to_CL *) GC_OBJECT(Compile_to_CL,new_object_class(Optimize._to_CL)));
                _void_(v60472->arg = v8241);
                _void_(v60472->set_arg = psort_any(GC_OID((*Optimize.c_type)(v8241))));
                add_I_property(Kernel.instances,Optimize._to_CL,11,_oid_(v60472));
                Result = _oid_(close_Instruction1(v60472));
                }
              }
            }
        else if (v8242 == Kernel._any)
         { Compile_to_C * v60472 = ((Compile_to_C *) GC_OBJECT(Compile_to_C,new_object_class(Optimize._to_C)));
          _void_(v60472->arg = v8241);
          _void_(v60472->set_arg = v8235);
          add_I_property(Kernel.instances,Optimize._to_C,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        else Result = v8241;
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_any2_Optimize(OID v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      if (INHERIT(OWNER(v62612),Kernel._unbound_symbol))
       Result = (*Optimize.Cerror)(_string_(((char*)"[215] the symbol ~A is unbound_symbol")),
        _oid_(OBJECT(unbound_symbol,v62612)->name));
      else if (INHERIT(OWNER(v62612),Language._Variable))
       Result = v62612;
      else if (INHERIT(OWNER(v62612),Core._global_variable))
       { c_register_object(OBJECT(ClaireObject,v62612));
        Result = v62612;
        }
      else if (INHERIT(OWNER(v62612),Language._Optimized_instruction))
       Result = v62612;
      else if (INHERIT(OWNER(v62612),Language._Instruction))
       Result = (*Optimize.Cerror)(_string_(((char*)"[internal] c_code(~S) should have a parameter")),
        v62612);
      else if (Kernel._set == OWNER(v62612))
       { if (OBJECT(bag,v62612)->length != 0)
         { Set * v8240;
          { { Instruction *V_CC ;
              { Set * v60472 = ((Set *) GC_OBJECT(Set,new_object_class(Language._Set)));
                _void_(v60472->args = list_I_set(OBJECT(set,v62612)));
                add_I_property(Kernel.instances,Language._Set,11,_oid_(v60472));
                V_CC = close_Instruction1(v60472);
                }
              v8240= (Set *) V_CC;}
            GC_OBJECT(Set,v8240);}
          if (of_bag(OBJECT(bag,v62612)) != Kernel._void)
           _void_(v8240->of = of_bag(OBJECT(bag,v62612)));
          Result = (*Optimize.c_code)(_oid_(v8240));
          }
        else Result = v62612;
          }
      else if (INHERIT(OWNER(v62612),Kernel._list))
       { if (OBJECT(bag,v62612)->length != 0)
         { List * v8240;
          { { Instruction *V_CC ;
              { List * v60472 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                _void_(v60472->args = OBJECT(list,v62612));
                add_I_property(Kernel.instances,Language._List,11,_oid_(v60472));
                V_CC = close_Instruction1(v60472);
                }
              v8240= (List *) V_CC;}
            GC_OBJECT(List,v8240);}
          if (of_bag(OBJECT(bag,v62612)) != Kernel._void)
           _void_(v8240->of = of_bag(OBJECT(bag,v62612)));
          Result = (*Optimize.c_code)(_oid_(v8240));
          }
        else Result = v62612;
          }
      else if (INHERIT(OWNER(v62612),Kernel._tuple))
       { OID  v52899;
        { { Tuple * v60472 = ((Tuple *) GC_OBJECT(Tuple,new_object_class(Language._Tuple)));
            _void_(v60472->args = OBJECT(list,v62612));
            add_I_property(Kernel.instances,Language._Tuple,11,_oid_(v60472));
            v52899 = _oid_(close_Instruction1(v60472));
            }
          GC_OID(v52899);}
        Result = (*Optimize.c_code)(v52899);
        }
      else { if (INHERIT(OWNER(v62612),Kernel._thing))
           (*Optimize.c_register)(v62612);
          if ((Kernel._float == OWNER(v62612)) || 
              (INHERIT(OWNER(v62612),Kernel._function)))
           _void_(Optimize.OPT->allocation = CTRUE);
          Result = v62612;
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * c_gc_ask_any(OID v62612) { 
    { ClaireBoolean *Result ;
      Result = ((INHERIT(OWNER(v62612),Language._Variable)) ?
        CFALSE :
        ((INHERIT(OWNER(v62612),Core._global_variable)) ?
          not_any(_oid_((INHERIT(OBJECT(global_variable,v62612)->range->isa,Kernel._class) ?
           (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(OBJECT(global_variable,v62612)->range))) : 
           (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(OBJECT(global_variable,v62612)->range)))))) :
          ((INHERIT(OWNER(v62612),Language._Construct)) ?
            ((Optimize.OPT->loop_gc == CTRUE) ? (((INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._List)) || 
                (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Set))) ? CTRUE: CFALSE): CFALSE) :
            ((INHERIT(OWNER(v62612),Language._Instruction)) ?
              CFALSE :
              CFALSE ) ) ) );
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireClass * c_sort_any_Optimize(OID v62612) { 
    
    GC_BIND;
    { ClaireClass *Result ;
      { ClaireObject *V_CC ;
        if (INHERIT(OWNER(v62612),Core._global_variable))
         { V_CC = ((nativeVar_ask_global_variable(OBJECT(global_variable,v62612)) == CTRUE) ?
            ((equal(_oid_(OBJECT(global_variable,v62612)->range),_oid_(Kernel.emptySet)) == CTRUE) ?
              osort_any(_oid_(OWNER(OBJECT(global_variable,v62612)->value))) :
              osort_any(_oid_(OBJECT(global_variable,v62612)->range)) ) :
            Kernel._any );
          }
        else if (INHERIT(OWNER(v62612),Language._Instruction))
         { if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Variable))
           V_CC = sort_Variable(OBJECT(Variable,v62612));
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Assign))
           V_CC = sort_Variable(GC_OBJECT(Variable,OBJECT(Variable,OBJECT(Assign,v62612)->var)));
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Call))
           V_CC = osort_any(_oid_(selector_psort_Call(OBJECT(Call,v62612))));
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Call_method))
           { V_CC = (((OBJECT(Call_method,v62612)->arg->selector == Core.externC) && 
                (OBJECT(Call_method,v62612)->args->length == 2)) ?
              psort_any((*(OBJECT(Call_method,v62612)->args))[2]) :
              c_srange_method(OBJECT(Call_method,v62612)->arg) );
            }
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Call_slot))
           V_CC = OBJECT(Call_slot,v62612)->selector->srange;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Call_table))
           V_CC = Kernel._any;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Call_array))
           { V_CC = ((OBJECT(Call_array,v62612)->test == _oid_(Kernel._float)) ?
              Kernel._float :
              Kernel._any );
            }
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Definition))
           V_CC = Kernel._object;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Optimize._to_C))
           V_CC = OBJECT(Compile_to_C,v62612)->set_arg;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Optimize._to_protect))
           V_CC = OBJECT(ClaireClass,(*Optimize.c_sort)(OBJECT(Compile_to_protect,v62612)->arg));
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Update))
           V_CC = OBJECT(ClaireClass,(*Optimize.c_sort)(OBJECT(Update,v62612)->value));
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._If))
           V_CC = psort_any(_oid_(meet_class(OBJECT(ClaireClass,(*Optimize.c_sort)(OBJECT(If,v62612)->arg)),OBJECT(ClaireClass,(*Optimize.c_sort)(OBJECT(If,v62612)->other)))));
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Handle))
           V_CC = psort_any(_oid_(meet_class(OBJECT(ClaireClass,(*Optimize.c_sort)(OBJECT(ClaireHandle,v62612)->arg)),OBJECT(ClaireClass,(*Optimize.c_sort)(OBJECT(ClaireHandle,v62612)->other)))));
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Let))
           V_CC = OBJECT(ClaireClass,(*Optimize.c_sort)(OBJECT(Let,v62612)->arg));
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Optimize._to_CL))
           V_CC = Kernel._any;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Return))
           V_CC = Kernel._any;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._List))
           V_CC = Kernel._object;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Set))
           V_CC = Kernel._object;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Tuple))
           V_CC = Kernel._object;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Construct))
           V_CC = Kernel._any;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Gassign))
           V_CC = Kernel._any;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Super))
           V_CC = Kernel._any;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._For))
           V_CC = Kernel._any;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Ffor))
           V_CC = Kernel._object;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Exists))
           { V_CC = ((OBJECT(Exists,v62612)->other == CNULL) ?
              Kernel._any :
              Kernel._object );
            }
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Iteration))
           V_CC = Kernel._object;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._And))
           V_CC = Kernel._boolean;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Or))
           V_CC = Kernel._boolean;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._While))
           V_CC = Kernel._any;
          else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Do))
           V_CC = OBJECT(ClaireClass,(*Optimize.c_sort)(GC_OID(last_list(OBJECT(Do,v62612)->args))));
          else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[internal] c_sort is not implemented for ~S")),
              _oid_(list::alloc(1,_oid_(OWNER(v62612)))))));
            }
        else V_CC = ((Kernel._float == OWNER(v62612)) ?
          Kernel._float :
          psort_any(GC_OID((*Optimize.c_type)(v62612))) );
        Result= (ClaireClass *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireClass * selector_psort_Call(Call *v62612) { 
    { ClaireClass *Result ;
      { property * v8232 = v62612->selector;
        Result = (((v8232 == Core.base_I) || 
            (v8232 == Core.index_I)) ?
          Kernel._integer :
          ((v8232 == Optimize.anyObject_I) ?
            OBJECT(ClaireClass,(*(v62612->args))[1]) :
            ((v8232 == Optimize.object_I) ?
              OBJECT(ClaireClass,(*(v62612->args))[2]) :
              Kernel._any ) ) );
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT CL_INT  c_status_any(OID v62612,list *v8228) { 
    
    GC_BIND;
    { CL_INT Result = 0;
      if (INHERIT(OWNER(v62612),Language._Instruction))
       { if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Variable))
         { Result = (((OBJECT(Variable,v62612)->range == (NULL)) || 
              ((*Optimize.gcsafe_ask)(GC_OID(_oid_(OBJECT(Variable,v62612)->range))) != Kernel.ctrue)) ?
            ((contain_ask_list(v8228,v62612) == CTRUE) ?
              16 :
              (((((OBJECT(Variable,v62612)->range == (NULL)) ? CTRUE : CFALSE) != CTRUE) && 
                  (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(Variable,v62612)->range),Kernel._float) == CTRUE)) ?
                2 :
                0 ) ) :
            32 );
          }
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Error))
         Result = 32;
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Printf))
         { CL_INT  v14403;
          { CL_INT  v59588 = 0;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(v59590);
              bag *v59590_support;
              v59590_support = GC_OBJECT(list,OBJECT(Construct,v62612)->args);
              for (START(v59590_support); NEXT(v59590);)
              { CL_INT  v59589 = c_status_any(v59590,v8228);
                v59588= (CL_INT)(c_or_integer(v59588,v59589));
                }
              }
            v14403 = v59588;
            }
          Result = c_return_integer(0,v14403);
          }
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Construct))
         Result = 2;
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Definition))
         Result = 2;
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Call))
         { CL_INT  v58695 = c_status_property(OBJECT(Call,v62612)->selector);
          CL_INT  v58696;
          { CL_INT  v59591 = 0;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(v14910);
              bag *v14910_support;
              v14910_support = GC_OBJECT(list,OBJECT(Call,v62612)->args);
              for (START(v14910_support); NEXT(v14910);)
              { CL_INT  v59592 = c_status_any(v14910,v8228);
                v59591= (CL_INT)(c_or_integer(v59591,v59592));
                }
              }
            v58696 = v59591;
            }
          Result = c_return_integer(v58695,v58696);
          }
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._If))
         { CL_INT  v58695 = c_status_any(GC_OID(OBJECT(If,v62612)->arg),v8228);
          CL_INT  v58696 = c_status_any(GC_OID(OBJECT(If,v62612)->other),v8228);
          Result = c_return_integer(c_or_integer(v58695,v58696),c_status_any(GC_OID(OBJECT(If,v62612)->test),v8228));
          }
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Do))
         { OID  v8241 = GC_OID(last_list(OBJECT(Do,v62612)->args));
          CL_INT  v58695 = c_status_any(v8241,v8228);
          CL_INT  v58696;
          { CL_INT  v14911 = 0;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(v14913);
              bag *v14913_support;
              v14913_support = GC_OBJECT(list,OBJECT(Do,v62612)->args);
              for (START(v14913_support); NEXT(v14913);)
              if (equal(v14913,v8241) != CTRUE)
               { CL_INT  v14912 = c_status_any(v14913,v8228);
                v14911= (CL_INT)(c_or_integer(v14911,v14912));
                }
              }
            v58696 = v14911;
            }
          Result = c_return_integer(v58695,v58696);
          }
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._For))
         Result = c_return_integer(c_status_any(GC_OID(OBJECT(Iteration,v62612)->arg),v8228),c_status_any(GC_OID(OBJECT(Iteration,v62612)->set_arg),v8228));
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Ffor))
         Result = c_return_integer(c_status_any(GC_OID(OBJECT(iClaire_Ffor,v62612)->arg),v8228),c_or_integer(c_status_any(GC_OID(OBJECT(iClaire_Ffor,v62612)->set_arg),v8228),c_status_any(GC_OID(OBJECT(iClaire_Ffor,v62612)->forkedby),v8228)));
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Iteration))
         Result = c_return_integer(2,c_status_any(GC_OID(OBJECT(Iteration,v62612)->arg),v8228));
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Let))
         Result = c_return_integer(c_status_any(GC_OID(OBJECT(Let,v62612)->arg),v8228),c_status_any(GC_OID(OBJECT(Let,v62612)->value),v8228));
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Assign))
         Result = c_status_any(GC_OID(OBJECT(Assign,v62612)->arg),v8228);
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Gassign))
         Result = c_status_any(GC_OID(OBJECT(Gassign,v62612)->arg),v8228);
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._And))
         { CL_INT  v15364;
          { CL_INT  v14914 = 0;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(v14916);
              bag *v14916_support;
              v14916_support = GC_OBJECT(list,OBJECT(And,v62612)->args);
              for (START(v14916_support); NEXT(v14916);)
              { CL_INT  v14915 = c_status_any(v14916,v8228);
                v14914= (CL_INT)(c_or_integer(v14914,v14915));
                }
              }
            v15364 = v14914;
            }
          Result = c_return_integer(0,v15364);
          }
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Or))
         { CL_INT  v16325;
          { CL_INT  v14917 = 0;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(v14919);
              bag *v14919_support;
              v14919_support = GC_OBJECT(list,OBJECT(Or,v62612)->args);
              for (START(v14919_support); NEXT(v14919);)
              { CL_INT  v14918 = c_status_any(v14919,v8228);
                v14917= (CL_INT)(c_or_integer(v14917,v14918));
                }
              }
            v16325 = v14917;
            }
          Result = c_return_integer(0,v16325);
          }
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Cast))
         Result = c_status_any(GC_OID(OBJECT(Cast,v62612)->arg),v8228);
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Super))
         { CL_INT  v58695 = c_status_property(OBJECT(Super,v62612)->selector);
          CL_INT  v58696;
          { CL_INT  v14941 = 0;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(v14943);
              bag *v14943_support;
              v14943_support = GC_OBJECT(list,OBJECT(Super,v62612)->args);
              for (START(v14943_support); NEXT(v14943);)
              { CL_INT  v14942 = c_status_any(v14943,v8228);
                v14941= (CL_INT)(c_or_integer(v14941,v14942));
                }
              }
            v58696 = v14941;
            }
          Result = c_return_integer(v58695,v58696);
          }
        else if (INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Case))
         { CL_INT  v14944 = 0;
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(v14946);
            bag *v14946_support;
            v14946_support = GC_OBJECT(list,OBJECT(Case,v62612)->args);
            for (START(v14946_support); NEXT(v14946);)
            { CL_INT  v14945 = c_status_any(v14946,v8228);
              v14944= (CL_INT)(c_or_integer(v14944,v14945));
              }
            }
          Result = v14944;
          }
        else Result = ((INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._While)) ?
          c_return_integer(c_status_any(GC_OID(OBJECT(While,v62612)->arg),v8228),c_status_any(GC_OID(OBJECT(While,v62612)->test),v8228)) :
          ((INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Return)) ?
            c_status_any(GC_OID(OBJECT(Return,v62612)->arg),v8228) :
            ((INHERIT(OBJECT(ClaireObject,v62612)->isa,Language._Handle)) ?
              c_return_integer(c_or_integer(c_status_any(GC_OID(OBJECT(ClaireHandle,v62612)->arg),v8228),c_status_any(GC_OID(OBJECT(ClaireHandle,v62612)->other),v8228)),c_status_any(GC_OID(OBJECT(ClaireHandle,v62612)->test),v8228)) :
              ((INHERIT(OBJECT(ClaireObject,v62612)->isa,Kernel._unbound_symbol)) ?
                0 :
                ((CL_INT)(*Optimize.Cerror)(_string_(((char*)"[internal] oops .. I forgot ~S")),
                  _oid_(OWNER(v62612)))) ) ) ) );
        }
      else Result = ((Kernel._float == OWNER(v62612)) ?
        2 :
        ((Kernel._string == OWNER(v62612)) ?
          2 :
          ((INHERIT(OWNER(v62612),Kernel._function)) ?
            2 :
            ((INHERIT(OWNER(v62612),Core._Type)) ?
              2 :
              0 ) ) ) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT CL_INT  c_or_integer(CL_INT v8240,CL_INT v8241) { 
    { CL_INT Result = 0;
      { CL_INT  v8220 = or_integer(v8240,v8241);
        if ((BCONTAIN(v8220,((CL_INT)(OID)(5)))) && 
            (((BCONTAIN(v8240,((CL_INT)(OID)(5)))) ? ((BCONTAIN(v8241,((CL_INT)(OID)(5)))) ? CTRUE: CFALSE): CFALSE) != CTRUE))
         v8220= (CL_INT)(((CL_INT)v8220-(CL_INT)exp2_integer(5)));
        if ((BCONTAIN(v8220,((CL_INT)(OID)(6)))) && 
            (((BCONTAIN(v8240,((CL_INT)(OID)(6)))) ? ((BCONTAIN(v8241,((CL_INT)(OID)(6)))) ? CTRUE: CFALSE): CFALSE) != CTRUE))
         v8220= (CL_INT)(((CL_INT)v8220-(CL_INT)exp2_integer(6)));
        Result = v8220;
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT CL_INT  c_or_list(list *v8228) { 
    { CL_INT Result = 0;
      { CL_INT  v8220 = 0;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(v8240);
          for (START(v8228); NEXT(v8240);)
          v8220= (CL_INT)(c_or_integer(v8220,((CL_INT)v8240)));
          }
        Result = v8220;
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT CL_INT  status_I_restriction(restriction *v62612) { 
    
    GC_BIND;
    { CL_INT Result = 0;
      if (Kernel._method == v62612->isa)
       { if (((CLREAD(method,v62612,status) == (((CL_INT)CNULL))) ? CTRUE : CFALSE) != CTRUE)
         Result = CLREAD(method,v62612,status);
        else if (CLREAD(method,v62612,formula) == (NULL))
         { _void_(CLREAD(method,v62612,status) = 0);
          Result = 0;
          }
        else { _void_(CLREAD(method,v62612,status) = 0);
            _void_(CLREAD(method,v62612,status) = c_status_any(GC_OID(CLREAD(method,v62612,formula)->body),GC_OBJECT(list,CLREAD(method,v62612,formula)->vars)));
            if (should_trace_ask_module1(Optimize.it,4) == CTRUE)
             mtformat_module1(Optimize.it,((char*)"status(~S) = ~S \n"),4,list::alloc(2,_oid_(v62612),((OID)CLREAD(method,v62612,status))));
            else ;Result = CLREAD(method,v62612,status);
            }
          }
      else Result = 0;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT CL_INT  c_return_integer(CL_INT v8240,CL_INT v8241) { 
    { CL_INT Result = 0;
      { CL_INT  v8220 = or_integer(v8240,v8241);
        if ((nth_integer(v8240,((CL_INT)(OID)(5))) != CTRUE) && 
            (BCONTAIN(v8241,((CL_INT)(OID)(5)))))
         v8220= (CL_INT)(((CL_INT)v8220-(CL_INT)exp2_integer(5)));
        if ((nth_integer(v8240,((CL_INT)(OID)(4))) != CTRUE) && 
            (BCONTAIN(v8241,((CL_INT)(OID)(4)))))
         v8220= (CL_INT)(((CL_INT)v8220-(CL_INT)exp2_integer(4)));
        Result = v8220;
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT CL_INT  c_status_property(property *v62612) { 
    { CL_INT Result = 0;
      { CL_INT  v8234 = ((stable_ask_relation(v62612) == CTRUE) ?
          0 :
          ((CL_INT)(*Language.bit_vector)(((OID)1),
            (OID)(2),
            (OID)(3))) );
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(v8240);
          for (START(v62612->restrictions); NEXT(v8240);)
          { if ((((*Kernel.srange)(v8240) == _oid_(Kernel._integer)) ? CTRUE : (((*Kernel.srange)(v8240) == _oid_(Kernel._object)) ? CTRUE : (((*Kernel.srange)(v8240) == _oid_(Kernel._any)) ? CTRUE : CFALSE))) != CTRUE)
             v8234= (CL_INT)(c_or_integer(v8234,2));
            if (Kernel._method == OBJECT(ClaireObject,v8240)->isa)
             v8234= (CL_INT)(c_or_integer(v8234,status_I_restriction(OBJECT(restriction,v8240))));
            else if (Kernel._slot == OBJECT(ClaireObject,v8240)->isa)
             v8234= (CL_INT)(c_or_integer(v8234,exp2_integer(4)));
            }
          }
        Result = v8234;
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  showstatus_method2(method *v8229) { 
    { OID Result = 0;
      { list * v58509 = list::alloc(6,_string_(((char*)"NEW_ALLOC")),
          _string_(((char*)"BAG_UPDATE")),
          _string_(((char*)"SLOT_UPDATE")),
          _string_(((char*)"RETURN_ARG")),
          _string_(((char*)"SAFE_RESULT")),
          _string_(((char*)"SAFE_GC")));
        list * v8228 = list::empty(Kernel._any);
        CL_INT  v8235 = v8229->status;
        { CL_INT  v8225 = 1;
          CL_INT  v14950 = 6;
          { CL_INT loop_handle = ClEnv->cHandle;
            while (((CL_INT)v8225 <= (CL_INT)v14950))
            { if (BCONTAIN(v8235,v8225))
               v8228= (v8228->addFast((OID)(*(v58509))[v8225]));
              ++v8225;
              POP_SIGNAL;}
            }
          }
        Result = _oid_(v8228);
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  s_test_method2(method *v8229) { 
    
    GC_BIND;
    { lambda * v58557 = GC_OBJECT(lambda,v8229->formula);
      CL_INT  v45083 = c_status_any(GC_OID(v58557->body),GC_OBJECT(list,v58557->vars));
      if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
       mtformat_module1(Optimize.it,((char*)"status(~S) := ~S \n"),0,list::alloc(2,_oid_(v8229),((OID)v45083)));
      else ;_void_(v8229->status = v45083);
      showstatus_method2(v8229);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT ClaireBoolean * legal_ask_module(module *v62612,OID v8240) { 
    if ((v8240 == _oid_(Optimize.object_I)) || 
        (v8240 == _oid_(Optimize.anyObject_I))) 
    { { ClaireBoolean *Result ;
        Result = CTRUE;
        return (Result);}
       }
    else{ 
      GC_BIND;
      { ClaireBoolean *Result ;
        if (Optimize.OPT->legal_modules->length != 0)
         { if ((contain_ask_set(Optimize.OPT->legal_modules,_oid_(v62612)) != CTRUE) && 
              ((Kernel._method == OWNER(v8240)) && ((OBJECT(method,v8240)->inline_ask == CFALSE) || 
                  (Optimize.compiler->inline_ask != CTRUE))))
           { if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
             mtformat_module1(Optimize.it,((char*)"legal_modules = ~S\n"),0,list::alloc(1,GC_OID(_oid_(Optimize.OPT->legal_modules))));
            else ;if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
             mtformat_module1(Optimize.it,((char*)"---- ERROR: ~S implies using ~S !\n\n"),0,list::alloc(2,v8240,_oid_(v62612)));
            else ;Result = CFALSE;
            }
          else Result = CTRUE;
            }
        else { GC_OBJECT(set,Optimize.OPT->need_modules)->addFast((OID)_oid_(v62612));
            Result = CTRUE;
            }
          GC_UNBIND; POP_SIGNAL; return (Result);}
      }
    }
  

CL_EXPORT OID  legal_ask_environment(ClaireEnvironment *v62612,OID v8240) { 
    POP_SIGNAL; return (Kernel.ctrue);}
  

CL_EXPORT OID  c_register_object(ClaireObject *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v8240 = GC_OID(get_module_object(v62612));
        if (v8240 != _oid_(ClEnv))
         Result = (*Optimize.legal_ask)(v8240,
          _oid_(v62612));
        else Result = Kernel.ctrue;
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_register_property(property *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { module * v8229 = ClEnv->module_I;
        OID  v58541 = GC_OID(get_module_object(v62612));
        if (((v58541 == _oid_(claire.it)) || 
              (v58541 == _oid_(v8229))) && 
            (Optimize.OPT->objects->memq(_oid_(v62612)) != CTRUE))
         GC_OBJECT(set,Optimize.OPT->properties)->addFast((OID)_oid_(v62612));
        Result = c_register_object(v62612);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  selector_register_property(property *v62612) { 
    c_register_property(v62612);
    if (allocate_ask_property(v62612) == Kernel.ctrue)
     _void_(Optimize.OPT->allocation = CTRUE);
    POP_SIGNAL; return (_oid_(v62612));}
  

CL_EXPORT OID  allocate_ask_property(property *v62612) { 
    { OID Result = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v8240);
        Result= Kernel.cfalse;
        for (START(v62612->restrictions); NEXT(v8240);)
        if (Kernel._slot == OBJECT(ClaireObject,v8240)->isa)
         { if ((_oid_((INHERIT(OBJECT(restriction,v8240)->range->isa,Kernel._class) ?
             (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(OBJECT(restriction,v8240)->range))) : 
             (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(OBJECT(restriction,v8240)->range))))) != Kernel.ctrue) && 
              (OBJECT(slot,v8240)->srange != Kernel._any))
           { Result = Kernel.ctrue;
            ClEnv->cHandle = loop_handle;break;}
          else if ((_oid_((INHERIT(OBJECT(restriction,v8240)->range->isa,Kernel._class) ?
             (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(OBJECT(restriction,v8240)->range))) : 
             (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(OBJECT(restriction,v8240)->range))))) != Kernel.ctrue) && 
              (gcsafe_ask_class(domain_I_restriction(OBJECT(restriction,v8240))) != CTRUE))
           { Result = ((OID)0);
            ClEnv->cHandle = loop_handle;break;}
          }
        else if (Kernel._method == OBJECT(ClaireObject,v8240)->isa)
         { if ((BCONTAIN(status_I_restriction(OBJECT(restriction,v8240)),((CL_INT)(OID)(1)))) || 
              ((((c_srange_method(OBJECT(method,v8240)) == Kernel._integer) ? CTRUE : ((c_srange_method(OBJECT(method,v8240)) == Kernel._object) ? CTRUE : ((c_srange_method(OBJECT(method,v8240)) == Kernel._any) ? CTRUE : CFALSE))) != CTRUE) || 
                (_oid_((INHERIT(OBJECT(restriction,v8240)->range->isa,Kernel._class) ?
                 (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(OBJECT(restriction,v8240)->range))) : 
                 (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(OBJECT(restriction,v8240)->range))))) != Kernel.ctrue)))
           { Result = Kernel.ctrue;
            ClEnv->cHandle = loop_handle;break;}
          }
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * stable_ask_relation(ClaireRelation *v62612) { 
    
    GC_BIND;
    { OID  v8229 = GC_OID(get_module_object(v62612));
      if ((v62612->open == 2) && 
          ((contain_ask_set(Optimize.OPT->legal_modules,v8229) == CTRUE) || 
              (v8229 == _oid_(ClEnv))))
       _void_(v62612->open = 1);
      }
    { ClaireBoolean *Result ;
      Result = (((CL_INT)v62612->open <= (CL_INT)1) ? CTRUE : ((v62612->open == 4) ? CTRUE : CFALSE));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  get_module_object(ClaireObject *v62612) { 
    POP_SIGNAL; return (_oid_(defined_symbol(OBJECT(symbol,(*Kernel.name)(_oid_(v62612))))));}
  

CL_EXPORT OID  known_I_listargs(listargs *v8228) { 
    
    GC_BIND;
    GC_OBJECT(set,Optimize.OPT->to_remove)->addFast((OID)_oid_(Reader.known_I));
    { OID Result = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v8234);
        Result= Kernel.cfalse;
        for (START(v8228); NEXT(v8234);)
        { GC_LOOP;
          if (INHERIT(OWNER(v8234),Kernel._property))
           GC_OBJECT(set,Optimize.OPT->knowns)->addFast((OID)v8234);
          GC_UNLOOP; POP_SIGNAL;}
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  oload_module(module *v8229) { 
    load_module(v8229);
    POP_SIGNAL; return (turbo_module(v8229));}
  

CL_EXPORT OID  oload_string(char *v8222) { 
    load_string(v8222);
    POP_SIGNAL; return (turbo_module(ClEnv->module_I));}
  

CL_EXPORT OID  turbo_module(module *v8229) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT  v58868 = ClEnv->verbose;
        _void_(Optimize.OPT->online_ask = CTRUE);
        _void_(ClEnv->verbose = 0);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v8240);
          bag *v8240_support;
          v8240_support = Kernel._method->instances;
          for (START(v8240_support); NEXT(v8240);)
          { GC_LOOP;
            if ((OBJECT(restriction,v8240)->module_I == v8229) && 
                ((OBJECT(method,v8240)->inline_ask != CTRUE) && 
                  (((OBJECT(method,v8240)->formula == (NULL)) ? CTRUE : CFALSE) != CTRUE)))
             { lambda * v8228 = GC_OBJECT(lambda,OBJECT(method,v8240)->formula);
              OID  v8241 = GC_OID(v8228->body);
              { ClaireHandler c_handle = ClaireHandler();
                if ERROR_IN 
                { { if (OBJECT(restriction,v8240)->range == Kernel._any)
                     update_property(Kernel.range,
                      OBJECT(ClaireObject,v8240),
                      5,
                      Kernel._object,
                      GC_OID((*Optimize.c_type)(v8241)));
                    _void_(v8228->body = (*Optimize.c_code)(v8241,
                      _oid_(Kernel._any)));
                    (Language._starvariable_index_star->value= ((OID)((CL_INT)v8228->vars->length+(CL_INT)1)));
                    _void_(v8228->body = lexical_build_any(GC_OID(v8228->body),GC_OBJECT(list,v8228->vars),((CL_INT)Language._starvariable_index_star->value)));
                    _void_(v8228->dimension = ((CL_INT)Language._starvariable_index_star->value));
                    }
                  ERROR_FREE;}
                else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                { c_handle.catchIt();{ _void_(v8228->body = v8241);
                    ;}
                  }
                else PREVIOUS_HANDLER;}
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        _void_(Optimize.OPT->online_ask = CFALSE);
        _void_(ClEnv->verbose = v58868);
        Result = Kernel.ctrue;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  stats_meta_OPT(Optimize_meta_OPT *v8240) { 
    ;POP_SIGNAL;}
  



/***** CLAIRE Compilation of file ./compile/otool.cl 
         [version 3.5.0 / safety 5] *****/

CL_EXPORT void  self_print_to_protect(Compile_to_protect *v8240) { 
    
    GC_BIND;
    princ_string(((char*)"[to_protect "));
    print_any(GC_OID(v8240->arg));
    princ_string(((char*)"]"));
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT OID  self_eval_to_protect(Compile_to_protect *v8240) { 
    
    GC_BIND;
    { OID Result = 0;
      Result = OPT_EVAL(v8240->arg);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  self_print_to_CL(Compile_to_CL *v62612) { 
    
    GC_BIND;
    princ_string(((char*)"CL{"));
    print_any(GC_OID(v62612->arg));
    princ_string(((char*)"}:"));
    print_any(GC_OID(get_property(Language.set_arg,v62612)));
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT ClaireType * c_type_to_CL_Optimize(Compile_to_CL *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = sort_abstract_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v62612->arg))));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * c_gc_ask_to_CL(Compile_to_CL *v62612) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = (((gcsafe_ask_class(v62612->set_arg) != CTRUE) && 
          ((v62612->set_arg == Kernel._float) || 
              (_inf_equalt_class(v62612->set_arg,Kernel._cl_import) == CTRUE))) ? CTRUE : (((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(GC_OID(v62612->arg)))) == CTRUE) ? CTRUE : CFALSE));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  self_print_to_C(Compile_to_C *v62612) { 
    
    GC_BIND;
    princ_string(((char*)"C{"));
    print_any(GC_OID(v62612->arg));
    princ_string(((char*)"}:"));
    print_any(GC_OID(get_property(Language.set_arg,v62612)));
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT ClaireBoolean * c_gc_ask_to_C(Compile_to_C *v62612) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = ((gcsafe_ask_class(v62612->set_arg) != CTRUE) ? (((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(GC_OID(v62612->arg)))) == CTRUE) ? (((_inf_equalt_class(v62612->set_arg,Kernel._object) == CTRUE) || 
          (_inf_equalt_class(v62612->set_arg,Kernel._primitive) == CTRUE)) ? CTRUE: CFALSE): CFALSE): CFALSE);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_to_C_Optimize(Compile_to_C *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = glb_class(v62612->set_arg,GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->arg))))));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  self_print_C_cast(Compile_C_cast *v62612) { 
    
    GC_BIND;
    princ_string(((char*)"<"));
    print_any(GC_OID(v62612->arg));
    princ_string(((char*)":"));
    print_any(GC_OID(get_property(Language.set_arg,v62612)));
    princ_string(((char*)">"));
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT ClaireBoolean * c_gc_ask_C_cast(Compile_C_cast *v62612) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v62612->arg));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_C_cast_Optimize(Compile_C_cast *v62612) { 
    POP_SIGNAL; return (v62612->set_arg);}
  

CL_EXPORT OID  c_code_C_cast_Optimize(Compile_C_cast *v62612,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      if (INHERIT(v8235,Kernel._object))
       { Compile_C_cast * v60472 = ((Compile_C_cast *) GC_OBJECT(Compile_C_cast,new_object_class(Optimize._C_cast)));
        _void_(v60472->arg = (*Optimize.c_code)(GC_OID(v62612->arg),
          _oid_(v8235)));
        _void_(v60472->set_arg = v62612->set_arg);
        add_I_property(Kernel.instances,Optimize._C_cast,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      else Result = (*Optimize.c_code)(GC_OID(v62612->arg),
          _oid_(v8235));
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  self_print_Pattern(Optimize_ClairePattern *v62612) { 
    
    GC_BIND;
    print_any(GC_OID(get_property(Kernel.selector,v62612)));
    princ_string(((char*)"[tuple("));
    princ_bag(GC_OBJECT(list,v62612->arg));
    princ_string(((char*)")]"));
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT ClaireBoolean * _Z_any3(OID v8240,Optimize_ClairePattern *v8241) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      if (INHERIT(OWNER(v8240),Language._Call))
       { ClaireBoolean *v_and;
        { v_and = ((OBJECT(Call,v8240)->selector == v8241->selector) ? CTRUE : CFALSE);
          if (v_and == CFALSE) Result =CFALSE; 
          else { { list * v42272;
              { { CL_INT loop_handle = ClEnv->cHandle;
                  bag *v_list; OID v_val;
                  OID v8242; CL_INT CLcount;
                  v_list = GC_OBJECT(list,OBJECT(Call,v8240)->args);
                   v42272 = v_list->clone();
                  for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                  { v8242 = (*(v_list))[CLcount];
                    v_val = (*Optimize.c_type)(v8242);
                    
                    (*((list *) v42272))[CLcount] = v_val;}
                  }
                GC_OBJECT(list,v42272);}
              v_and = tmatch_ask_list(v42272,GC_OBJECT(list,v8241->arg));
              }
            if (v_and == CFALSE) Result =CFALSE; 
            else Result = CTRUE;}
          }
        }
      else Result = CFALSE;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * glb_Pattern(Optimize_ClairePattern *v8240,ClaireType *v8241) { 
    POP_SIGNAL; return (Kernel.emptySet);}
  

CL_EXPORT ClaireBoolean * less_ask_Pattern(Optimize_ClairePattern *v8240,OID v8241) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      if (INHERIT(OWNER(v8241),Optimize._Pattern))
       { ClaireBoolean *v_and;
        { v_and = ((v8240->selector == OBJECT(Optimize_ClairePattern,v8241)->selector) ? CTRUE : CFALSE);
          if (v_and == CFALSE) Result =CFALSE; 
          else { v_and = ((v8240->arg->length == OBJECT(Optimize_ClairePattern,v8241)->arg->length) ? CTRUE : CFALSE);
            if (v_and == CFALSE) Result =CFALSE; 
            else { { OID  v44194;
                { CL_INT  v8225 = 1;
                  CL_INT  v14977 = v8240->arg->length;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    OID gc_local;
                    v44194= _oid_(CFALSE);
                    while (((CL_INT)v8225 <= (CL_INT)v14977))
                    { GC_LOOP;
                      if (_equaltype_ask_any(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*(v8240->arg))[v8225])),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*(OBJECT(Optimize_ClairePattern,v8241)->arg))[v8225]))) != CTRUE)
                       { GC_UNLOOP;v44194 = Kernel.ctrue;
                        ClEnv->cHandle = loop_handle;break;}
                      ++v8225;
                      GC_UNLOOP;POP_SIGNAL;}
                    }
                  }
                v_and = not_any(v44194);
                }
              if (v_and == CFALSE) Result =CFALSE; 
              else Result = CTRUE;}
            }
          }
        }
      else Result = OBJECT(ClaireBoolean,(*Core._inf_equalt)(_oid_(Language._Call),
          v8241));
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * less_ask_any(OID v8240,Optimize_ClairePattern *v8241) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      if (INHERIT(OWNER(v8240),Optimize._Pattern))
       { ClaireBoolean *v_and;
        { v_and = ((OBJECT(Optimize_ClairePattern,v8240)->selector == v8241->selector) ? CTRUE : CFALSE);
          if (v_and == CFALSE) Result =CFALSE; 
          else { v_and = ((OBJECT(Optimize_ClairePattern,v8240)->arg->length == v8241->arg->length) ? CTRUE : CFALSE);
            if (v_and == CFALSE) Result =CFALSE; 
            else { { OID  v46116;
                { CL_INT  v8225 = 1;
                  CL_INT  v14979 = OBJECT(Optimize_ClairePattern,v8240)->arg->length;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    OID gc_local;
                    v46116= _oid_(CFALSE);
                    while (((CL_INT)v8225 <= (CL_INT)v14979))
                    { GC_LOOP;
                      if (_equaltype_ask_any(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*(OBJECT(Optimize_ClairePattern,v8240)->arg))[v8225])),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*(v8241->arg))[v8225]))) != CTRUE)
                       { GC_UNLOOP;v46116 = Kernel.ctrue;
                        ClEnv->cHandle = loop_handle;break;}
                      ++v8225;
                      GC_UNLOOP;POP_SIGNAL;}
                    }
                  }
                v_and = not_any(v46116);
                }
              if (v_and == CFALSE) Result =CFALSE; 
              else Result = CTRUE;}
            }
          }
        }
      else Result = CFALSE;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT Optimize_ClairePattern * nth_property(property *v8232,tuple *v8240) { 
    
    GC_BIND;
    { Optimize_ClairePattern *Result ;
      { Optimize_ClairePattern * v60472 = ((Optimize_ClairePattern *) GC_OBJECT(Optimize_ClairePattern,new_object_class(Optimize._Pattern)));
        _void_(v60472->selector = v8232);
        _void_(v60472->arg = list_I_tuple(v8240));
        add_I_property(Kernel.instances,Optimize._Pattern,11,_oid_(v60472));
        Result = v60472;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  show_opportunist_integer1(CL_INT v8230) { 
    
    GC_BIND;
    if (((CL_INT)v8230 <= (CL_INT)ClEnv->verbose) && 
        ((Kernel._method == OWNER(Optimize.OPT->in_method)) && (equal(Optimize.OPT->in_method,Optimize._staroportunist_method_star->value) != CTRUE)))
     { (Optimize._staroportunist_method_star->value= Optimize.OPT->in_method);
      { OID  v46328 = nth_table1(Language.CODE_LOCS,Optimize.OPT->in_method);
        if (v46328 != CNULL)
         { if (OBJECT(bag,v46328)->length != 0)
           { if (color_void() == 2)
             { char * v9331 = GC_STRING(getenv_string(((char*)"WCL_HREF_FORMATER")));
              buffer * v8232 = GC_OBJECT(buffer,buffer_I_port1(GC_OBJECT(PortObject,ClEnv->ctrace),4096));
              PortObject * v49119 = use_as_output_port(v8232);
              color_integer(0);
              if (LENGTH_STRING(v9331) == 0)
               v9331= (((char*)"txmt://open?url=$URLFILE&line=$LINE"));
              v9331= (GC_STRING(replace_string(v9331,((char*)"$FILE"),string_v((*(OBJECT(bag,v46328)))[1]))));
              v9331= (GC_STRING(replace_string(v9331,((char*)"$URLFILE"),GC_STRING(url_encode_string(GC_STRING(append_string(((char*)"file://"),string_v((*(OBJECT(bag,v46328)))[1]))))))));
              v9331= (GC_STRING(replace_string(v9331,((char*)"$LINE"),GC_STRING(string_v((*Kernel.string_I)((*(OBJECT(bag,v46328)))[2]))))));
              princ_string(((char*)"&nbsp;<a href='"));
              (*Language.echo)(_string_(v9331));
              princ_string(((char*)"'>"));
              (*Language.self_html)((*(OBJECT(bag,v46328)))[1]);
              princ_string(((char*)":"));
              (*Language.echo)((*(OBJECT(bag,v46328)))[2]);
              princ_string(((char*)"</a>&nbsp;"));
              use_as_output_port(v49119);
              fclose_port1(v8232);
              color_integer(2);
              }
            else { PortObject * v14981 = use_as_output_port(ClEnv->ctrace);
                (*Kernel.princ)((*(OBJECT(bag,v46328)))[1]);
                princ_string(((char*)":"));
                print_any((*(OBJECT(bag,v46328)))[2]);
                princ_string(((char*)" "));
                use_as_output_port(v14981);
                }
              }
          }
        else ;}
      if (color_void() == 2)
       { char * v9331 = GC_STRING(getenv_string(((char*)"WCL_HREF_FORMATER")));
        buffer * v8232 = GC_OBJECT(buffer,buffer_I_port1(GC_OBJECT(PortObject,ClEnv->ctrace),4096));
        PortObject * v49119 = use_as_output_port(v8232);
        color_integer(0);
        princ_string(((char*)"in "));
        (*Language.self_html)(_oid_(Optimize.in_method),
          _oid_(Optimize.OPT));
        princ_string(((char*)"<br>"));
        use_as_output_port(v49119);
        fclose_port1(v8232);
        color_integer(2);
        }
      else { PortObject * v15003 = use_as_output_port(ClEnv->ctrace);
          princ_string(((char*)"["));
          print_any(GC_OID(Optimize.OPT->in_method));
          princ_string(((char*)"]\n"));
          use_as_output_port(v15003);
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  warn_void() { 
    show_opportunist_integer1(2);
    if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
     mtformat_module1(Optimize.it,((char*)" `BLUE warning: "),2,list::empty());
    else ;POP_SIGNAL;}
  

CL_EXPORT void  Cerror_string(char *v8235,listargs *v8228) { 
    
    GC_BIND;
    show_opportunist_integer1(-1000);
    close_exception(((general_error *) (*Core._general_error)(GC_OID(_string_(append_string(((char*)"---- Compiler Error :\n"),v8235))),
      _oid_(v8228))));
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  notice_void() { 
    show_opportunist_integer1(3);
    if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
     mtformat_module1(Optimize.it,((char*)" `GREEN note: "),3,list::empty());
    else ;POP_SIGNAL;}
  

CL_EXPORT OID  c_warn_Call(Call *v62612,OID v30871) { 
    
    GC_BIND;
    { OID Result = 0;
      { property * v8235 = v62612->selector;
        if (v30871 == _oid_(Kernel._void))
         (*Optimize.Cerror)(_string_(((char*)"[205] message ~S sent to void object")),
          _oid_(v62612));
        else if ((boolean_I_any(_oid_(v8235->restrictions)) != CTRUE) && 
            (contain_ask_set(Optimize.OPT->ignore,_oid_(v8235)) != CTRUE))
         { warn_void();
          if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
           mtformat_module1(Optimize.it,((char*)"`BLUE the property ~S is undefined [255]\n"),2,list::alloc(1,_oid_(v8235)));
          else ;}
        else if ((contain_ask_set(Optimize.OPT->ignore,_oid_(v8235)) != CTRUE) && 
            ((((CL_INT)v8235->open <= (CL_INT)1) || 
                (v8235->open == 4)) && 
              ((INHERIT(OWNER(v30871),Kernel._list)) && (class_I_type(OBJECT(ClaireType,(*(OBJECT(bag,v30871)))[1]))->open != 3))))
         { warn_void();
          if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
           mtformat_module1(Optimize.it,((char*)"`BLUE wrongly typed message ~S (~S) [256]\n"),2,list::alloc(2,_oid_(v62612),v30871));
          else ;}
        else if (Optimize.compiler->optimize_ask == CTRUE)
         { notice_void();
          if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
           mtformat_module1(Optimize.it,((char*)"`GREEN poorly typed message ~S [~S]\n"),3,list::alloc(2,_oid_(v62612),v30871));
          else ;}
        Result = _oid_(open_message_property(v62612->selector,GC_OBJECT(list,v62612->args)));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_warn_Super(Super *v62612,OID v30871) { 
    
    GC_BIND;
    { OID Result = 0;
      { property * v8235 = v62612->selector;
        if (v30871 == _oid_(Kernel._void))
         (*Optimize.Cerror)(_string_(((char*)"[205] message ~S sent to void object")),
          _oid_(v62612));
        else if (boolean_I_any(_oid_(v8235->restrictions)) != CTRUE)
         { warn_void();
          if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
           mtformat_module1(Optimize.it,((char*)"`BLUE the property ~S is undefined [255]\n"),2,list::alloc(1,_oid_(v8235)));
          else ;}
        else if ((contain_ask_set(Optimize.OPT->ignore,_oid_(v8235)) != CTRUE) && 
            ((CL_INT)v8235->open <= (CL_INT)1))
         { show_opportunist_integer1(4);
          if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
           mtformat_module1(Optimize.it,((char*)"  `GREEN note: wrongly typed message ~S [~S]\n"),3,list::alloc(2,_oid_(v62612),v30871));
          else ;}
        { Call * v8229 = GC_OBJECT(Call,open_message_property(v62612->selector,GC_OBJECT(list,v62612->args)));
          Super * v60472 = ((Super *) GC_OBJECT(Super,new_object_class(Language._Super)));
          _void_(v60472->selector = v8229->selector);
          _void_(v60472->cast_to = v62612->cast_to);
          _void_(v60472->args = v8229->args);
          add_I_property(Kernel.instances,Language._Super,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_warn_property(property *v62612,list *v8228,list *v30871) { 
    if (((CL_INT)v62612->open <= (CL_INT)1) && 
        ((contain_ask_set(Optimize.OPT->ignore,_oid_(v62612)) != CTRUE) && 
          ((CL_INT)Optimize.compiler->safety > (CL_INT)1)))
     { show_opportunist_integer1(4);
      if (should_trace_ask_module1(Optimize.it,4) == CTRUE)
       mtformat_module1(Optimize.it,((char*)"`GREEN note: poor type matching with ~S(~S) [~S]\n"),4,list::alloc(3,_oid_(v62612),
        _oid_(v8228),
        _oid_(v30871)));
      else ;}
    POP_SIGNAL; return (_oid_(open_message_property(v62612,v8228)));}
  

CL_EXPORT OID  c_warn_Variable(Variable *v62612,OID v8240,ClaireType *v8241) { 
    
    GC_BIND;
    if (boolean_I_any((*Kernel._exp)(_oid_(v8241),
      GC_OID(_oid_(v62612->range)))) != CTRUE)
     { if ((CL_INT)Optimize.compiler->safety > (CL_INT)4)
       { warn_void();
        if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
         mtformat_module1(Optimize.it,((char*)"`BLUE ~S of type ~S is put in the variable ~S:~S [257]\n"),2,list::alloc(4,v8240,
          _oid_(v8241),
          _oid_(v62612),
          GC_OID(_oid_(v62612->range))));
        else ;}
      else (*Optimize.Cerror)(_string_(((char*)"[212] the value ~S of type ~S cannot be placed in the variable ~S:~S")),
          v8240,
          _oid_(v8241),
          _oid_(v62612),
          GC_OID(_oid_(v62612->range)));
        }
    else if (((CL_INT)Optimize.compiler->safety <= (CL_INT)1) || 
        (boolean_I_any(sort_equal_class(osort_any(GC_OID(_oid_(v62612->range))),osort_any(_oid_(v8241)))) != CTRUE))
     { warn_void();
      if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
       mtformat_module1(Optimize.it,((char*)"`BLUE ~S of type ~S is put in the variable ~S:~S [257]\n"),2,list::alloc(4,v8240,
        _oid_(v8241),
        _oid_(v62612),
        GC_OID(_oid_(v62612->range))));
      else ;}
    { OID Result = 0;
      if (((CL_INT)Optimize.compiler->safety <= (CL_INT)1) && 
          (_inf_equal_type(v8241,GC_OBJECT(ClaireType,v62612->range)) != CTRUE))
       Result = c_check_any(GC_OID((*Optimize.c_code)(v8240,
        _oid_(Kernel._any))),GC_OID((*Optimize.c_code)(GC_OID(_oid_(v62612->range)),
        _oid_(Kernel._type))));
      else Result = v8240;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  sort_equal_class(ClaireClass *v8219,ClaireClass *v58231) { 
    { OID Result = 0;
      if (INHERIT(v8219,Kernel._object))
       Result = _oid_(inherit_ask_class(v58231,Kernel._object));
      else Result = _oid_(((v8219 == v58231) ? CTRUE : ((((Optimize.compiler->overflow_ask != CTRUE) && 
              ((v8219 == Kernel._any) && 
                  (v58231 == Kernel._integer))) || 
            ((v8219 == Kernel._integer) && 
                (v58231 == Kernel._any))) ? CTRUE : CFALSE)));
        POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireClass * psort_any(OID v8240) { 
    { ClaireClass *Result ;
      { ClaireClass * v8219 = class_I_type(OBJECT(ClaireType,v8240));
        Result = ((INHERIT(v8219,Kernel._object)) ?
          v8219 :
          ((v8219 == Kernel._float) ?
            v8219 :
            sort_I_class(v8219) ) );
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireClass * osort_any(OID v8240) { 
    { ClaireClass *Result ;
      { ClaireClass * v8219 = class_I_type(OBJECT(ClaireType,v8240));
        Result = ((v8219 == Kernel._float) ?
          v8219 :
          sort_I_class(v8219) );
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireClass * sort_Variable(Variable *v8240) { 
    
    GC_BIND;
    { ClaireClass *Result ;
      { ClaireType * v8234 = v8240->range;
        Result = (((INHERIT(v8234->isa,Core._Union)) && (equal(_oid_(CLREAD(Union,v8234,t1)),_oid_(Kernel.emptySet)) == CTRUE)) ?
          psort_any(GC_OID(_oid_(CLREAD(Union,CLREAD(Union,v8234,t2),t2)))) :
          psort_any(_oid_(v8234)) );
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireClass * stupid_t_any1(OID v62612) { 
    
    GC_BIND;
    { ClaireClass *Result ;
      if (INHERIT(OWNER(v62612),Language._Variable))
       { ClaireType * v8234 = GC_OBJECT(ClaireType,OBJECT(Variable,v62612)->range);
        Result = ((sort_abstract_ask_type(v8234) == CTRUE) ?
          Kernel._any :
          (((INHERIT(v8234->isa,Core._Union)) && (equal(_oid_(CLREAD(Union,v8234,t1)),_oid_(Kernel.emptySet)) == CTRUE)) ?
            OBJECT(ClaireClass,(*Core.t1)(GC_OID(_oid_(CLREAD(Union,v8234,t2))))) :
            class_I_type(v8234) ) );
        }
      else if (INHERIT(OWNER(v62612),Core._global_variable))
       { ClaireType * v8234 = OBJECT(global_variable,v62612)->range;
        Result = ((boolean_I_any(_oid_(v8234)) == CTRUE) ?
          class_I_type(v8234) :
          OWNER(OBJECT(global_variable,v62612)->value) );
        }
      else if (INHERIT(OWNER(v62612),Language._And))
       Result = Kernel._boolean;
      else if (INHERIT(OWNER(v62612),Kernel._bag))
       Result = OWNER(v62612);
      else if (INHERIT(OWNER(v62612),Kernel._environment))
       Result = Kernel._environment;
      else if (INHERIT(OWNER(v62612),Kernel._class))
       Result = Kernel._class;
      else if (INHERIT(OWNER(v62612),Language._Call_slot))
       { slot * v8235 = OBJECT(Call_slot,v62612)->selector;
        property * v8232 = v8235->selector;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(v58727);
          for (START(v8232->definition); NEXT(v58727);)
          if (Kernel._slot == OBJECT(ClaireObject,v58727)->isa)
           { if (_inf_equal_type(domain_I_restriction(v8235),domain_I_restriction(OBJECT(restriction,v58727))) == CTRUE)
             v8235= (OBJECT(slot,v58727));
            }
          }
        Result = class_I_type(v8235->range);
        }
      else if (INHERIT(OWNER(v62612),Language._Call_method))
       Result = class_I_type(OBJECT(Call_method,v62612)->arg->range);
      else if (INHERIT(OWNER(v62612),Language._Call))
       Result = selector_psort_Call(OBJECT(Call,v62612));
      else if (INHERIT(OWNER(v62612),Optimize._to_C))
       Result = OBJECT(Compile_to_C,v62612)->set_arg;
      else if (INHERIT(OWNER(v62612),Optimize._to_protect))
       Result = stupid_t_any1(GC_OID(OBJECT(Compile_to_protect,v62612)->arg));
      else if (INHERIT(OWNER(v62612),Kernel._symbol))
       Result = OWNER(v62612);
      else if (INHERIT(OWNER(v62612),Kernel._char))
       Result = OWNER(v62612);
      else if (Kernel._boolean == OWNER(v62612))
       Result = OWNER(v62612);
      else if (INHERIT(OWNER(v62612),Kernel._primitive))
       Result = OWNER(v62612);
      else if (INHERIT(OWNER(v62612),Language._Assign))
       Result = stupid_t_any1(GC_OID(OBJECT(Assign,v62612)->arg));
      else if (INHERIT(OWNER(v62612),Language._Let))
       Result = stupid_t_any1(GC_OID(OBJECT(Let,v62612)->arg));
      else if (INHERIT(OWNER(v62612),Language._Do))
       Result = stupid_t_any1(GC_OID(last_list(OBJECT(Do,v62612)->args)));
      else if (INHERIT(OWNER(v62612),Language._If))
       Result = meet_class(stupid_t_any1(GC_OID(OBJECT(If,v62612)->arg)),stupid_t_any1(GC_OID(OBJECT(If,v62612)->other)));
      else if (INHERIT(OWNER(v62612),Language._Collect))
       Result = Kernel._list;
      else if (INHERIT(OWNER(v62612),Language._Image))
       Result = Kernel._set;
      else if (INHERIT(OWNER(v62612),Language._Or))
       Result = Kernel._boolean;
      else if (INHERIT(OWNER(v62612),Language._Select))
       Result = Kernel._set;
      else if (INHERIT(OWNER(v62612),Language._Lselect))
       Result = Kernel._list;
      else if (INHERIT(OWNER(v62612),Language._List))
       Result = Kernel._list;
      else if (INHERIT(OWNER(v62612),Language._Set))
       Result = Kernel._set;
      else Result = ((INHERIT(OWNER(v62612),Kernel._thing)) ?
        OWNER(v62612) :
        ((INHERIT(OWNER(v62612),Language._Tuple)) ?
          Kernel._tuple :
          ((INHERIT(OWNER(v62612),Language._Exists)) ?
            ((OBJECT(Exists,v62612)->other == CNULL) ?
              Kernel._any :
              Kernel._boolean ) :
            ((INHERIT(OWNER(v62612),Kernel._integer)) ?
              Kernel._integer :
              Kernel._any ) ) ) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * stupid_t_any2(OID v62612,OID v8240) { 
    { ClaireBoolean *Result ;
      { ClaireClass * v58230 = stupid_t_any1(v62612);
        ClaireClass * v58231 = stupid_t_any1(v8240);
        Result = ((v58230 != Kernel._any) ? ((v58230 == v58231) ? CTRUE: CFALSE): CFALSE);
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * extended_ask_type(ClaireType *v62612) { 
    { ClaireBoolean *Result ;
      Result = ((INHERIT(v62612->isa,Core._Union)) ?
        ((Kernel._set == CLREAD(Union,v62612,t2)->isa) ? ((boolean_I_any(_oid_(CLREAD(Union,v62612,t2))) == CTRUE) ? (((*(((bag *) CLREAD(Union,v62612,t2))))[1] == CNULL) ? CTRUE: CFALSE): CFALSE): CFALSE) :
        CFALSE );
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * extends_type(ClaireType *v8240) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { Optimize_optUnion * v60472 = ((Optimize_optUnion *) GC_OBJECT(Optimize_optUnion,new_object_class(Optimize._optUnion)));
        _void_(v60472->t1 = v8240);
        _void_(v60472->t2 = set::alloc(Kernel.emptySet,1,CNULL));
        Result = v60472;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * sort_abstract_I_type(ClaireType *v8240) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (((_oid_((INHERIT(v8240->isa,Kernel._class) ?
           (ClaireObject *) sort_I_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v8240))) : 
           (ClaireObject *)  sort_I_type((ClaireType *) OBJECT(ClaireType,_oid_(v8240))))) != _oid_(Kernel._any)) && 
            ((_oid_((INHERIT(v8240->isa,Kernel._class) ?
               (ClaireObject *) sort_I_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v8240))) : 
               (ClaireObject *)  sort_I_type((ClaireType *) OBJECT(ClaireType,_oid_(v8240))))) != _oid_(Kernel._integer)) || 
                (Optimize.compiler->overflow_ask == CTRUE))) || 
          (v8240 == Kernel._float))
       { Union * v60472 = ((Union *) GC_OBJECT(Union,new_object_class(Core._Union)));
        _void_(v60472->t1 = Kernel._any);
        _void_(v60472->t2 = v8240);
        Result = v60472;
        }
      else Result = v8240;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * sort_abstract_ask_type(ClaireType *v8240) { 
    { ClaireBoolean *Result ;
      Result = ((INHERIT(v8240->isa,Core._Union)) ?
        equal(_oid_(CLREAD(Union,v8240,t1)),_oid_(Kernel._any)) :
        CFALSE );
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * ptype_type(ClaireType *v8240) { 
    { ClaireType *Result ;
      Result = ((INHERIT(v8240->isa,Core._Union)) ?
        ((CLREAD(Union,v8240,t1) == Kernel._any) ?
          CLREAD(Union,v8240,t2) :
          v8240 ) :
        v8240 );
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * pmember_type(ClaireType *v8240) { 
    POP_SIGNAL; return (member_type(ptype_type(v8240)));}
  

CL_EXPORT OID  enumerate_code_any(OID v62612,ClaireType *v56375) { 
    
    GC_BIND;
    { OID Result = 0;
      if (_inf_equal_type(ptype_type(v56375),Kernel._bag) == CTRUE)
       Result = c_strict_code_any(v62612,Kernel._bag);
      else { if (Optimize.compiler->optimize_ask == CTRUE)
           { notice_void();
            if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
             mtformat_module1(Optimize.it,((char*)"`GREEN explicit enmeration of ~S\n"),3,list::alloc(1,v62612));
            else ;}
          Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property1(Core.enumerate,Kernel._any))),list::alloc(1,v62612),list::alloc(1,_oid_(v56375)));
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  range_infers_for_Variable(Variable *v62612,ClaireType *v8241,ClaireType *v58823) { 
    
    GC_BIND;
    if (v62612->range == (NULL))
     { if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
       mtformat_module1(Optimize.it,((char*)"infer type ~S for ~S \n"),5,list::alloc(2,_oid_(v8241),_oid_(v62612)));
      else ;if (INHERIT(v8241->isa,Core._Interval))
       v8241= (Kernel._integer);
      _void_(v62612->range = v8241);
      }
    else if ((_inf_equal_type(v8241,GC_OBJECT(ClaireType,v62612->range)) != CTRUE) && 
        ((CL_INT)Optimize.compiler->safety <= (CL_INT)1))
     { if (((boolean_I_any(_oid_(v8241)) == CTRUE) ? ((boolean_I_any(_oid_(v62612->range)) == CTRUE) ? CTRUE: CFALSE): CFALSE) != CTRUE)
       { warn_void();
        if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
         mtformat_module1(Optimize.it,((char*)"`BLUE range of variable in ~S is wrong [258]\n"),2,list::alloc(1,_oid_(v62612)));
        else ;}
      }
    { OID Result = 0;
      if ((sort_Variable(v62612) != Kernel._any) && 
          (((sort_Variable(v62612) != Kernel._integer) || 
              (Optimize.compiler->overflow_ask == CTRUE)) && 
            (((_inf_equal_type(v58823,Kernel._array) == CTRUE) ? ((_inf_equal_type(v8241,Kernel._float) == CTRUE) ? CTRUE: CFALSE): CFALSE) != CTRUE)))
       { if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
         mtformat_module1(Optimize.it,((char*)"protect original sort with ~S \n"),5,list::alloc(1,GC_OID(_oid_(sort_abstract_I_type(GC_OBJECT(ClaireType,v62612->range))))));
        else ;Result = _void_(_void_(v62612->range = sort_abstract_I_type(GC_OBJECT(ClaireType,v62612->range))));
        }
      else Result = Kernel.cfalse;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  range_infers_Variable(Variable *v62612,ClaireType *v8241) { 
    gc_register_Variable(v62612);
    if (should_trace_ask_module1(Optimize.it,4) == CTRUE)
     mtformat_module1(Optimize.it,((char*)"range_infers(~S,~S) \n"),4,list::alloc(2,_oid_(v62612),_oid_(v8241)));
    else ;{ OID Result = 0;
      if ((v62612->range == (NULL)) || 
          ((extended_ask_type(v62612->range) == CTRUE) && 
              (INHERIT(v62612->range->isa,Optimize._optUnion))))
       { if (Kernel._set == v8241->isa)
         Result = _void_(_void_(v62612->range = class_I_type(v8241)));
        else Result = _void_(_void_(v62612->range = v8241));
          }
      else Result = Kernel.cfalse;
        POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  range_infer_case_any(OID v62612,ClaireType *v8241) { 
    
    GC_BIND;
    if (INHERIT(OWNER(v62612),Language._Variable))
     { if (boolean_I_any(sort_equal_class(osort_any(GC_OID(_oid_(OBJECT(Variable,v62612)->range))),osort_any(_oid_(v8241)))) == CTRUE)
       { ClaireClass * v58230 = psort_any(_oid_(class_I_type(GC_OBJECT(ClaireType,OBJECT(Variable,v62612)->range))));
        if (v58230 != psort_any(_oid_(class_I_type(v8241))))
         { Variable * v15004 = OBJECT(Variable,v62612); 
          ClaireType * v15005;
          { Union * v60472 = ((Union *) GC_OBJECT(Union,new_object_class(Core._Union)));
            _void_(v60472->t1 = Kernel.emptySet);
            { Union * v15006 = v60472; 
              ClaireType * v15007;
              { Union * v60472 = ((Union *) GC_OBJECT(Union,new_object_class(Core._Union)));
                _void_(v60472->t1 = v58230);
                _void_(v60472->t2 = v8241);
                v15007 = v60472;
                }
              _void_(v15006->t2 = v15007);}
            v15005 = v60472;
            }
          _void_(v15004->range = v15005);}
        else _void_(OBJECT(Variable,v62612)->range = v8241);
          }
      else if (osort_any(GC_OID(_oid_(OBJECT(Variable,v62612)->range))) == Kernel._any)
       _void_(OBJECT(Variable,v62612)->range = sort_abstract_I_type(v8241));
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT OID  c_check_any(OID v8240,OID v8241) { 
    
    GC_BIND;
    { OID Result = 0;
      { method * v8229 = ((method *) _at_property1(Core.check_in,Kernel._any));
        if ((CL_INT)Optimize.compiler->safety > (CL_INT)3)
         Result = v8240;
        else { legal_ask_module(v8229->module_I,_oid_(v8229));
            { Call_method2 * v60472 = ((Call_method2 *) GC_OBJECT(Call_method2,new_object_class(Language._Call_method2)));
              _void_(v60472->arg = v8229);
              _void_(v60472->args = list::alloc(2,GC_OID(c_gc_I_any1(v8240)),GC_OID(c_gc_I_any1(v8241))));
              add_I_property(Kernel.instances,Language._Call_method2,11,_oid_(v60472));
              Result = _oid_(close_Instruction1(v60472));
              }
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  range_sets_any(OID v62612,ClaireType *v8241) { 
    
    GC_BIND;
    if (INHERIT(OWNER(v62612),Language._Variable))
     { ClaireType * v58750;
      { if (((OBJECT(Variable,v62612)->range == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         v58750 = OBJECT(Variable,v62612)->range;
        else v58750 = Kernel._any;
          GC_OBJECT(ClaireType,v58750);}
      if (boolean_I_any(sort_equal_class(osort_any(_oid_(v58750)),osort_any(_oid_(v8241)))) == CTRUE)
       { ClaireClass * v58230 = psort_any(_oid_(class_I_type(v58750)));
        if (v58230 != psort_any(_oid_(class_I_type(v8241))))
         { Variable * v15008 = OBJECT(Variable,v62612); 
          ClaireType * v15009;
          { Union * v60472 = ((Union *) GC_OBJECT(Union,new_object_class(Core._Union)));
            _void_(v60472->t1 = Kernel.emptySet);
            { Union * v15010 = v60472; 
              ClaireType * v15011;
              { Union * v60472 = ((Union *) GC_OBJECT(Union,new_object_class(Core._Union)));
                _void_(v60472->t1 = v58230);
                _void_(v60472->t2 = v8241);
                v15011 = v60472;
                }
              _void_(v15010->t2 = v15011);}
            v15009 = v60472;
            }
          _void_(v15008->range = v15009);}
        else _void_(OBJECT(Variable,v62612)->range = v8241);
          }
      else if (osort_any(_oid_(v58750)) == Kernel._any)
       _void_(OBJECT(Variable,v62612)->range = sort_abstract_I_type(v8241));
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT ClaireClass * c_srange_method(method *v8229) { 
    { ClaireClass *Result ;
      Result = ((v8229->range == Kernel._float) ?
        Kernel._float :
        OBJECT(ClaireClass,last_list(v8229->srange)) );
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * nativeVar_ask_global_variable(global_variable *v8240) { 
    POP_SIGNAL; return (CFALSE);}
  

CL_EXPORT ClaireType * return_type_any(OID v62612) { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    { ClaireType *Result ;
      if (INHERIT(OWNER(v62612),Optimize._to_C))
       Result = return_type_any(GC_OID(OBJECT(Compile_to_C,v62612)->arg));
      else if (INHERIT(OWNER(v62612),Optimize._to_protect))
       Result = return_type_any(GC_OID(OBJECT(Compile_to_protect,v62612)->arg));
      else if (INHERIT(OWNER(v62612),Language._Let))
       Result = return_type_any(GC_OID(OBJECT(Let,v62612)->arg));
      else if (INHERIT(OWNER(v62612),Language._Do))
       { set * v8240 = Kernel.emptySet;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v8241);
          bag *v8241_support;
          v8241_support = GC_OBJECT(list,OBJECT(Do,v62612)->args);
          for (START(v8241_support); NEXT(v8241);)
          { GC_LOOP;
            GC__ANY(v8240 = OBJECT(set,(*Kernel._exp)(_oid_(v8240),
              GC_OID(_oid_(return_type_any(v8241))))), 1);
            GC_UNLOOP; POP_SIGNAL;}
          }
        Result = v8240;
        }
      else if (INHERIT(OWNER(v62612),Language._If))
       Result = OBJECT(ClaireType,(*Kernel._exp)(GC_OID(_oid_(return_type_any(GC_OID(OBJECT(If,v62612)->arg)))),
        GC_OID(_oid_(return_type_any(GC_OID(OBJECT(If,v62612)->other))))));
      else if (INHERIT(OWNER(v62612),Language._Return))
       Result = OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(OBJECT(Return,v62612)->arg)));
      else if (INHERIT(OWNER(v62612),Language._Case))
       { set * v8240 = Kernel.emptySet;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v8241);
          bag *v8241_support;
          v8241_support = GC_OBJECT(list,OBJECT(Case,v62612)->args);
          for (START(v8241_support); NEXT(v8241);)
          { GC_LOOP;
            GC__ANY(v8240 = OBJECT(set,(*Kernel._exp)(_oid_(v8240),
              GC_OID(_oid_(return_type_any(v8241))))), 2);
            GC_UNLOOP; POP_SIGNAL;}
          }
        Result = v8240;
        }
      else if (INHERIT(OWNER(v62612),Language._Handle))
       Result = return_type_any(GC_OID(OBJECT(ClaireHandle,v62612)->arg));
      else Result = Kernel.emptySet;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Type_Optimize(Type *v62612,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      Result = (*Optimize.c_code)(GC_OID((*Optimize.self_code)(_oid_(v62612))),
        _oid_(v8235));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  self_code_subtype(subtype *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
        _void_(v60472->selector = Kernel.nth);
        _void_(v60472->args = list::alloc(2,_oid_(v62612->arg),GC_OID((*Optimize.c_code)(GC_OID(_oid_(v62612->t1)),
          _oid_(Kernel._type)))));
        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  self_code_Param(Param *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      if ((v62612->params->length == 1) && 
          (((*(v62612->params))[1] == _oid_(Kernel.of)) && 
            (Kernel._set == OWNER((*(v62612->args))[1]))))
       { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
        _void_(v60472->selector = Core.param_I);
        _void_(v60472->args = list::alloc(2,_oid_(v62612->arg),GC_OID((*Optimize.c_code)(GC_OID((*Kernel.nth)(GC_OID((*(v62612->args))[1]),
            ((OID)1))),
          _oid_(Kernel._type)))));
        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      else { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          _void_(v60472->selector = Kernel.nth);
          { Call * v15012 = v60472; 
            list * v15034;
            { OID v_bag;
              GC_ANY(v15034= list::empty(Kernel.emptySet));
              ((list *) v15034)->addFast((OID)_oid_(v62612->arg));
              ((list *) v15034)->addFast((OID)GC_OID(_oid_(v62612->params)));
              { { list * v13526;{ CL_INT loop_handle = ClEnv->cHandle;
                    bag *v_list; OID v_val;
                    OID v8241; CL_INT CLcount;
                    v_list = GC_OBJECT(list,v62612->args);
                     v13526 = v_list->clone();
                    for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                    { v8241 = (*(v_list))[CLcount];
                      v_val = (*Optimize.c_code)(v8241,
                        _oid_(Kernel._type));
                      
                      (*((list *) v13526))[CLcount] = v_val;}
                    }
                  
                  v_bag=_oid_(v13526);}
                GC_OID(v_bag);}
              ((list *) v15034)->addFast((OID)v_bag);}
            _void_(v15012->args = v15034);}
          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  self_code_Union(Union *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
        _void_(v60472->selector = Core.U);
        _void_(v60472->args = list::alloc(2,GC_OID((*Optimize.c_code)(GC_OID(_oid_(v62612->t1)),
          _oid_(Kernel._type))),GC_OID((*Optimize.c_code)(GC_OID(_oid_(v62612->t2)),
          _oid_(Kernel._type)))));
        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  self_code_Interval(Interval *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
        _void_(v60472->selector = Kernel._dot_dot);
        _void_(v60472->args = list::alloc(2,((OID)v62612->arg1),((OID)v62612->arg2)));
        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  self_code_Reference(Reference *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { Definition * v60472 = ((Definition *) GC_OBJECT(Definition,new_object_class(Language._Definition)));
        _void_(v60472->arg = Core._Reference);
        { Definition * v15036 = v60472; 
          list * v15037;
          { OID v_bag;
            GC_ANY(v15037= list::empty(Kernel.emptySet));
            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(v60472->selector = Kernel._equal);
                _void_(v60472->args = list::alloc(2,_oid_(Core.args),GC_OID(_oid_(v62612->args))));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v_bag = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v_bag);}
            ((list *) v15037)->addFast((OID)v_bag);
            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(v60472->selector = Kernel._equal);
                _void_(v60472->args = list::alloc(2,_oid_(Kernel.index),((OID)v62612->index)));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v_bag = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v_bag);}
            ((list *) v15037)->addFast((OID)v_bag);
            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(v60472->selector = Kernel._equal);
                _void_(v60472->args = list::alloc(2,_oid_(Kernel.arg),_oid_(v62612->arg)));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v_bag = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v_bag);}
            ((list *) v15037)->addFast((OID)v_bag);}
          _void_(v15036->args = v15037);}
        add_I_property(Kernel.instances,Language._Definition,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  self_code_Pattern(Optimize_ClairePattern *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      if (Optimize.compiler->inline_ask == CTRUE)
       { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
        _void_(v60472->selector = Kernel.nth);
        { Call * v15038 = v60472; 
          list * v15039;
          { OID v_bag;
            GC_ANY(v15039= list::empty(Kernel.emptySet));
            ((list *) v15039)->addFast((OID)_oid_(v62612->selector));
            { { Tuple * v60472 = ((Tuple *) GC_OBJECT(Tuple,new_object_class(Language._Tuple)));
                _void_(v60472->args = v62612->arg);
                add_I_property(Kernel.instances,Language._Tuple,11,_oid_(v60472));
                v_bag = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v_bag);}
            ((list *) v15039)->addFast((OID)v_bag);}
          _void_(v15038->args = v15039);}
        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      else Result = _oid_(Language._Call);
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  member_code_class2(ClaireClass *v62612,OID v8240) { 
    
    GC_BIND;
    { OID Result = 0;
      { Call * v43929;
        { { Instruction *V_CC ;
            { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(v60472->selector = ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v8240))),Kernel._object) == CTRUE) ?
                Kernel.isa :
                Core.owner ));
              _void_(v60472->args = list::alloc(1,v8240));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v43929= (Call *) V_CC;}
          GC_OBJECT(Call,v43929);}
        if ((((CL_INT)v62612->open <= (CL_INT)-1) || 
              (v62612->open == 1)) && 
            (boolean_I_any(_oid_(v62612->subclass)) != CTRUE))
         { OID  v38240;
          { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(v60472->selector = Kernel._equal);
              _void_(v60472->args = list::alloc(2,_oid_(v62612),_oid_(v43929)));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
              v38240 = _oid_(close_Instruction1(v60472));
              }
            GC_OID(v38240);}
          Result = (*Optimize.c_code)(v38240);
          }
        else { OID  v39201;
            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(v60472->selector = Core.inherit_ask);
                _void_(v60472->args = list::alloc(2,_oid_(v43929),_oid_(v62612)));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v39201 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v39201);}
            Result = (*Optimize.c_code)(v39201);
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  member_code_Type(Type *v62612,OID v8240) { 
    
    GC_BIND;
    { OID Result = 0;
      { Call_method2 * v60472 = ((Call_method2 *) GC_OBJECT(Call_method2,new_object_class(Language._Call_method2)));
        update_property(Kernel.arg,
          v60472,
          2,
          Kernel._object,
          GC_OID(_oid_(_at_property2(Kernel._Z,list::alloc(2,_oid_(Kernel._any),_oid_(Kernel._any))))));
        _void_(v60472->args = list::alloc(2,GC_OID((*Optimize.c_code)(v8240,
          _oid_(Kernel._any))),GC_OID((*Optimize.c_code)(_oid_(v62612),
          _oid_(Kernel._any)))));
        add_I_property(Kernel.instances,Language._Call_method2,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  member_code_Union(Union *v62612,OID v8240) { 
    
    GC_BIND;
    { OID Result = 0;
      { Or * v60472 = ((Or *) GC_OBJECT(Or,new_object_class(Language._Or)));
        _void_(v60472->args = list::alloc(2,GC_OID((*Optimize.member_code)(GC_OID(_oid_(v62612->t1)),
          v8240)),GC_OID((*Optimize.member_code)(GC_OID(_oid_(v62612->t2)),
          v8240))));
        add_I_property(Kernel.instances,Language._Or,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  member_code_Interval(Interval *v62612,OID v8240) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v40162;
        { { And * v60472 = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
            { And * v15043 = v60472; 
              list * v15065;
              { OID v_bag;
                GC_ANY(v15065= list::empty(Kernel.emptySet));
                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(v60472->selector = Kernel._sup_equal);
                    _void_(v60472->args = list::alloc(2,v8240,((OID)v62612->arg1)));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                    v_bag = _oid_(close_Instruction1(v60472));
                    }
                  GC_OID(v_bag);}
                ((list *) v15065)->addFast((OID)v_bag);
                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(v60472->selector = Kernel._inf_equal);
                    _void_(v60472->args = list::alloc(2,v8240,((OID)v62612->arg2)));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                    v_bag = _oid_(close_Instruction1(v60472));
                    }
                  GC_OID(v_bag);}
                ((list *) v15065)->addFast((OID)v_bag);}
              _void_(v15043->args = v15065);}
            add_I_property(Kernel.instances,Language._And,11,_oid_(v60472));
            v40162 = _oid_(close_Instruction1(v60472));
            }
          GC_OID(v40162);}
        Result = (*Optimize.c_code)(v40162,
          _oid_(Kernel._any));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  member_code_Param(Param *v62612,OID v8240) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v64187;
        { { And * v60472 = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
            { And * v15068 = v60472; 
              list * v15069;
              { list * v1534;
                { { OID v_bag;
                    GC_ANY(v1534= list::empty(Kernel.emptySet));
                    { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        _void_(v60472->selector = Kernel._Z);
                        _void_(v60472->args = list::alloc(2,v8240,_oid_(v62612->arg)));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                        v_bag = _oid_(close_Instruction1(v60472));
                        }
                      GC_OID(v_bag);}
                    ((list *) v1534)->addFast((OID)v_bag);}
                  GC_OBJECT(list,v1534);}
                list * v2495;
                { list * v53994 = list::empty(Kernel.emptySet);
                  { CL_INT  v8225 = 1;
                    CL_INT  v15066 = v62612->params->length;
                    { CL_INT loop_handle = ClEnv->cHandle;
                      OID gc_local;
                      while (((CL_INT)v8225 <= (CL_INT)v15066))
                      { GC_LOOP;
                        { OID  v3456;
                          { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                              _void_(v60472->selector = Kernel._Z);
                              { Call * v15073 = v60472; 
                                list * v15074;
                                { OID v_bag;
                                  GC_ANY(v15074= list::empty(Kernel.emptySet));
                                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                      update_property(Kernel.selector,
                                        v60472,
                                        2,
                                        Kernel._object,
                                        GC_OID((*(v62612->params))[v8225]));
                                      _void_(v60472->args = list::alloc(1,v8240));
                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                      v_bag = _oid_(close_Instruction1(v60472));
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v15074)->addFast((OID)v_bag);
                                  ((list *) v15074)->addFast((OID)GC_OID((*(v62612->args))[v8225]));}
                                _void_(v15073->args = v15074);}
                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                              v3456 = _oid_(close_Instruction1(v60472));
                              }
                            GC_OID(v3456);}
                          v53994->addFast((OID)v3456);
                          }
                        ++v8225;
                        GC_UNLOOP;POP_SIGNAL;}
                      }
                    }
                  v2495 = GC_OBJECT(list,v53994);
                  }
                v15069 = append_list(v1534,v2495);
                }
              _void_(v15068->args = v15069);}
            add_I_property(Kernel.instances,Language._And,11,_oid_(v60472));
            v64187 = _oid_(close_Instruction1(v60472));
            }
          GC_OID(v64187);}
        Result = (*Optimize.c_code)(v64187,
          _oid_(Kernel._any));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  member_code_tuple(tuple *v62612,OID v8240) { 
    
    GC_BIND;
    { OID Result = 0;
      if (INHERIT(OWNER(v8240),Language._Tuple))
       { if (length_bag(OBJECT(bag,(*Core.args)(v8240))) != v62612->length)
         Result = Kernel.cfalse;
        else { OID  v27481;
            { { And * v60472 = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
                { And * v15098 = v60472; 
                  list * v15099;
                  { list * v53994 = list::empty(Kernel.emptySet);
                    { CL_INT  v8225 = 1;
                      CL_INT  v15096 = v62612->length;
                      { CL_INT loop_handle = ClEnv->cHandle;
                        OID gc_local;
                        while (((CL_INT)v8225 <= (CL_INT)v15096))
                        { GC_LOOP;
                          { OID  v30364;
                            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                _void_(v60472->selector = Kernel._Z);
                                _void_(v60472->args = list::alloc(2,GC_OID((*(OBJECT(bag,(*Core.args)(v8240))))[v8225]),(*(v62612))[v8225]));
                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                v30364 = _oid_(close_Instruction1(v60472));
                                }
                              GC_OID(v30364);}
                            v53994->addFast((OID)v30364);
                            }
                          ++v8225;
                          GC_UNLOOP;POP_SIGNAL;}
                        }
                      }
                    v15099 = GC_OBJECT(list,v53994);
                    }
                  _void_(v15098->args = v15099);}
                add_I_property(Kernel.instances,Language._And,11,_oid_(v60472));
                v27481 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v27481);}
            Result = (*Optimize.c_code)(v27481,
              _oid_(Kernel._any));
            }
          }
      else Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property2(Kernel._Z,GC_OBJECT(list,list::alloc(2,_oid_(Kernel._any),_oid_(Kernel._any)))))),GC_OBJECT(list,list::alloc(2,v8240,_oid_(v62612))),GC_OBJECT(list,list::alloc(2,_oid_(Kernel._any),_oid_(Kernel._any))));
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  member_code_any(OID v62612,OID v8240) { 
    
    GC_BIND;
    (Language.LDEF->value= Core.nil->value);
    { OID Result = 0;
      { list * v30871 = list::alloc(2,GC_OID((*Optimize.c_type)(v8240)),GC_OID((*Optimize.c_type)(v62612)));
        OID  v8234 = GC_OID(extract_pattern_any(v62612,Kernel.nil));
        { ClaireBoolean * g1065I;
          { ClaireBoolean *v_or;
            { v_or = ((v8234 == CNULL) ? CTRUE : CFALSE);
              if (v_or == CTRUE) g1065I =CTRUE; 
              else { v_or = ((v62612 == _oid_(Kernel._object)) ? CTRUE : CFALSE);
                if (v_or == CTRUE) g1065I =CTRUE; 
                else { { OID  v32286;
                    if (INHERIT(OWNER(v62612),Core._global_variable))
                     v32286 = _oid_(OBJECT(global_variable,v62612)->range);
                    else v32286 = Kernel.cfalse;
                      v_or = boolean_I_any(v32286);
                    }
                  if (v_or == CTRUE) g1065I =CTRUE; 
                  else g1065I = CFALSE;}
                }
              }
            }
          
          if (g1065I == CTRUE) Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property2(Kernel._Z,v30871))),list::alloc(2,v8240,v62612),v30871);
            else Result = (*Optimize.member_code)(v8234,
            v8240);
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * _Z_any4(OID v8240,OID v8241) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = (((OBJECT(ClaireBoolean,(*Kernel._inf_equal)(v8240,
        GC_OID(OPT_EVAL((*(OBJECT(Call,v8241)->args))[2]))))) == CTRUE) ? (((OBJECT(ClaireBoolean,(*Kernel._inf_equal)(GC_OID(OPT_EVAL((*(OBJECT(Call,v8241)->args))[1])),
        v8240))) == CTRUE) ? CTRUE: CFALSE): CFALSE);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * _Z_any5(OID v8240,OID v8241) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = ((belong_to(v8240,OPT_EVAL((*(OBJECT(Call,v8241)->args))[1])) == CTRUE) ? ((equal(v8240,OPT_EVAL((*(OBJECT(Call,v8241)->args))[2])) != CTRUE) ? CTRUE: CFALSE): CFALSE);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * gcsafe_ask_class(ClaireClass *v62612) { 
    POP_SIGNAL; return (((v62612 == Kernel._void) ? CTRUE : 
    (((INHERIT(v62612,Kernel._thing)) && 
        (inherit_ask_class(v62612,Kernel._table) != CTRUE)) ? CTRUE : 
    ((INHERIT(v62612,Kernel._class)) ? CTRUE : 
    (((v62612 != Kernel._object) && 
        ((INHERIT(v62612,Kernel._object)) && 
          (((CL_INT)v62612->open < (CL_INT)3) && 
            ((inherit_ask_class(v62612,Kernel._collection) != CTRUE) && 
              (v62612 != Core._lambda))))) ? CTRUE : 
    ((v62612 == Kernel._integer) ? CTRUE : 
    ((v62612 == Kernel._char) ? CTRUE : 
    ((INHERIT(v62612,Kernel._boolean)) ? CTRUE : 
    ((v62612 == Kernel._function) ? CTRUE : 
    CFALSE)))))))));}
  

CL_EXPORT ClaireBoolean * gcsafe_ask_type(ClaireType *v62612) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = ((equal(_oid_(v62612),_oid_(Kernel.emptySet)) == CTRUE) ?
        CTRUE :
        ((INHERIT(v62612->isa,Core._Union)) ?
          (((OBJECT(ClaireBoolean,(*Optimize.gcsafe_ask)(GC_OID(_oid_(CLREAD(Union,v62612,t1)))))) == CTRUE) ? (((OBJECT(ClaireBoolean,(*Optimize.gcsafe_ask)(GC_OID(_oid_(CLREAD(Union,v62612,t2)))))) == CTRUE) ? CTRUE: CFALSE): CFALSE) :
          gcsafe_ask_class(class_I_type(v62612)) ) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * gcsafe_ask_property(property *v62612) { 
    { ClaireBoolean *Result ;
      { OID  v33247;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(v8240);
          v33247= Kernel.cfalse;
          for (START(v62612->restrictions); NEXT(v8240);)
          if (_oid_((INHERIT(v62612->range->isa,Kernel._class) ?
           (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v62612->range))) : 
           (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(v62612->range))))) != Kernel.ctrue)
           { v33247 = Kernel.ctrue;
            ClEnv->cHandle = loop_handle;break;}
          }
        Result = not_any(v33247);
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_gc_I_any1(OID v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      if ((Optimize.OPT->online_ask != CTRUE) && 
          ((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v62612))) == CTRUE))
       { show_opportunist_integer1(4);
        if (should_trace_ask_module1(Optimize.it,4) == CTRUE)
         mtformat_module1(Optimize.it,((char*)" `GREEN note: use GC protection on ~S \n"),4,list::alloc(1,v62612));
        else ;_void_(Optimize.OPT->protection = CTRUE);
        { Compile_to_protect * v60472 = ((Compile_to_protect *) GC_OBJECT(Compile_to_protect,new_object_class(Optimize._to_protect)));
          _void_(v60472->arg = v62612);
          add_I_property(Kernel.instances,Optimize._to_protect,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        }
      else Result = v62612;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_gc_I_any2(OID v62612,ClaireType *v8236) { 
    
    GC_BIND;
    { OID Result = 0;
      if ((Optimize.OPT->online_ask != CTRUE) && 
          ((((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v62612))) == CTRUE) || 
              ((INHERIT(OWNER(v62612),Language._Let)) && 
                  ((*Optimize.gcsafe_ask)(GC_OID((*Optimize.c_type)(v62612))) != Kernel.ctrue))) && 
            (_oid_((INHERIT(v8236->isa,Kernel._class) ?
             (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v8236))) : 
             (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(v8236))))) != Kernel.ctrue)))
       { show_opportunist_integer1(4);
        if (should_trace_ask_module1(Optimize.it,4) == CTRUE)
         mtformat_module1(Optimize.it,((char*)"`GREEN note: use GC protection on ~S:~S \n"),4,list::alloc(2,v62612,_oid_(v8236)));
        else ;_void_(Optimize.OPT->protection = CTRUE);
        { Compile_to_protect * v60472 = ((Compile_to_protect *) GC_OBJECT(Compile_to_protect,new_object_class(Optimize._to_protect)));
          _void_(v60472->arg = v62612);
          add_I_property(Kernel.instances,Optimize._to_protect,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        }
      else Result = v62612;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * need_protect_any(OID v8240) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = ((INHERIT(OWNER(v8240),Language._Call_slot)) ?
        Optimize.OPT->use_update :
        ((INHERIT(OWNER(v8240),Language._Call_method2)) ?
          ((OBJECT(Call_method,v8240)->arg->selector == Kernel.nth) ?
            ((Optimize.OPT->use_nth_equal == CTRUE) ? CTRUE : ((domain_I_restriction(OBJECT(Call_method,v8240)->arg) == Kernel._class) ? CTRUE : ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)((*(OBJECT(Call_method,v8240)->args))[1]))),Kernel._tuple) == CTRUE) ? CTRUE : CFALSE))) :
            CTRUE ) :
          CTRUE ) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT Variable * Variable_I_symbol(symbol *v8235,int v8230,ClaireType *v8236) { 
    
    GC_BIND;
    { Variable *Result ;
      { Instruction *V_CC ;
        { Variable * v60472 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
          _void_(v60472->pname = v8235);
          _void_(v60472->index = v8230);
          _void_(v60472->range = v8236);
          add_I_property(Kernel.instances,Language._Variable,11,_oid_(v60472));
          V_CC = close_Instruction1(v60472);
          }
        Result= (Variable *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT list * get_indexed_class_Optimize(ClaireClass *v8219) { 
    POP_SIGNAL; return (v8219->slots);}
  

CL_EXPORT ClaireBoolean * designated_ask_any(OID v62612) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      { ClaireBoolean *v_or;
        { v_or = inherit_ask_class(OWNER(v62612),Kernel._thing);
          if (v_or == CTRUE) Result =CTRUE; 
          else { v_or = inherit_ask_class(OWNER(v62612),Language._Variable);
            if (v_or == CTRUE) Result =CTRUE; 
            else { v_or = inherit_ask_class(OWNER(v62612),Kernel._integer);
              if (v_or == CTRUE) Result =CTRUE; 
              else { v_or = ((Kernel._boolean == OWNER(v62612)) ? CTRUE : CFALSE);
                if (v_or == CTRUE) Result =CTRUE; 
                else { v_or = ((equal(v62612,Core.nil->value) == CTRUE) ? CTRUE : CFALSE);
                  if (v_or == CTRUE) Result =CTRUE; 
                  else { v_or = ((equal(v62612,_oid_(Kernel.emptySet)) == CTRUE) ? CTRUE : CFALSE);
                    if (v_or == CTRUE) Result =CTRUE; 
                    else { v_or = ((v62612 == CNULL) ? CTRUE : CFALSE);
                      if (v_or == CTRUE) Result =CTRUE; 
                      else { v_or = ((Kernel._float == OWNER(v62612)) ? CTRUE : CFALSE);
                        if (v_or == CTRUE) Result =CTRUE; 
                        else { if (INHERIT(OWNER(v62612),Language._Call))
                           { OID  v8240 = GC_OID((*Optimize.c_code)(v62612));
                            v_or = (((inherit_ask_class(OWNER(v8240),Language._Call) != CTRUE) && 
                                (designated_ask_any(v8240) == CTRUE)) ? CTRUE : ((OBJECT(Call,v62612)->selector == Core.get_stack) ? CTRUE : CFALSE));
                            }
                          else if (INHERIT(OWNER(v62612),Language._Call_slot))
                           v_or = designated_ask_any(GC_OID(OBJECT(Call_slot,v62612)->arg));
                          else if (INHERIT(OWNER(v62612),Language._Call_table))
                           v_or = designated_ask_any(GC_OID(OBJECT(Call_table,v62612)->arg));
                          else if (INHERIT(OWNER(v62612),Optimize._to_protect))
                           v_or = ((need_protect_any(GC_OID(OBJECT(Compile_to_protect,v62612)->arg)) != CTRUE) ? ((designated_ask_any(GC_OID(OBJECT(Compile_to_protect,v62612)->arg)) == CTRUE) ? CTRUE: CFALSE): CFALSE);
                          else if (INHERIT(OWNER(v62612),Language._Call_method))
                           { ClaireBoolean *v_and;
                            { v_and = ((contain_ask_set(Optimize.OPT->simple_operations,_oid_(OBJECT(Call_method,v62612)->arg->selector)) == CTRUE) ? CTRUE : ((OBJECT(Call_method,v62612)->arg == _at_property1(Kernel.nth,Kernel._bag)) ? CTRUE : CFALSE));
                              if (v_and == CFALSE) v_or =CFALSE; 
                              else { { OID  v34208;
                                  { CL_INT loop_handle = ClEnv->cHandle;
                                    ITERATE(v8241);
                                    v34208= Kernel.cfalse;
                                    bag *v8241_support;
                                    v8241_support = GC_OBJECT(list,OBJECT(Call_method,v62612)->args);
                                    for (START(v8241_support); NEXT(v8241);)
                                    if (designated_ask_any(v8241) != CTRUE)
                                     { v34208 = Kernel.ctrue;
                                      ClEnv->cHandle = loop_handle;break;}
                                    }
                                  v_and = not_any(v34208);
                                  }
                                if (v_and == CFALSE) v_or =CFALSE; 
                                else v_or = CTRUE;}
                              }
                            }
                          else v_or = ((INHERIT(OWNER(v62612),Optimize._to_CL)) ?
                            designated_ask_any(GC_OID(OBJECT(Compile_to_CL,v62612)->arg)) :
                            ((INHERIT(OWNER(v62612),Optimize._to_C)) ?
                              designated_ask_any(GC_OID(OBJECT(Compile_to_C,v62612)->arg)) :
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
  

CL_EXPORT OID  gc_register_Variable(Variable *v62612) { 
    _void_(Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
    POP_SIGNAL; return (Kernel.ctrue);}
  

CL_EXPORT OID  gc_register_Variable2(Variable *v62612,OID v7502) { 
    if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
     mtformat_module1(Optimize.it,((char*)".... CALL REGISTER ON ~S := ~S \n"),5,list::alloc(2,_oid_(v62612),v7502));
    else ;{ OID Result = 0;
      if (inner2outer_ask_any(v7502) == CTRUE)
       Result = gc_register_Variable(v62612);
      else Result = Kernel.cfalse;
        POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * inner2outer_ask_any(OID v8240) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      if (INHERIT(OWNER(v8240),Optimize._to_protect))
       Result = CTRUE;
      else if (INHERIT(OWNER(v8240),Language._List))
       Result = CTRUE;
      else if (INHERIT(OWNER(v8240),Language._Set))
       Result = CTRUE;
      else if (INHERIT(OWNER(v8240),Language._Variable))
       Result = not_any((*Optimize.gcsafe_ask)(GC_OID(_oid_(OBJECT(Variable,v8240)->range))));
      else Result = ((INHERIT(OWNER(v8240),Language._Call_method)) ?
        (((OBJECT(Call_method,v8240)->arg->selector == Kernel.copy) && 
            (OBJECT(Call_method,v8240)->arg->range == Kernel._bag)) ? CTRUE : (((BCONTAIN(OBJECT(Call_method,v8240)->arg->status,((CL_INT)(OID)(4)))) && 
            (inner2outer_ask_any(GC_OID((*(OBJECT(Call_method,v8240)->args))[1])) == CTRUE)) ? CTRUE : CFALSE)) :
        ((INHERIT(OWNER(v8240),Optimize._to_CL)) ?
          inner2outer_ask_any(GC_OID(OBJECT(Compile_to_CL,v8240)->arg)) :
          ((INHERIT(OWNER(v8240),Optimize._to_C)) ?
            inner2outer_ask_any(GC_OID(OBJECT(Compile_to_C,v8240)->arg)) :
            ((INHERIT(OWNER(v8240),Language._Let)) ?
              inner2outer_ask_any(GC_OID(_oid_(OBJECT(Instruction_with_var,v8240)->var))) :
              CFALSE ) ) ) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * identifiable_ask_any(OID v62612) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      { ClaireBoolean *v_or;
        { v_or = ((v62612 == CNULL) ? CTRUE : CFALSE);
          if (v_or == CTRUE) Result =CTRUE; 
          else { if (INHERIT(OWNER(v62612),Optimize._to_CL))
             v_or = identifiable_ask_any(GC_OID(OBJECT(Compile_to_CL,v62612)->arg));
            else { ClaireClass * v8236 = class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v62612))));
                v_or = not_any(_oid_(contain_ask_set(Optimize.OPT->non_identifiable_set,_oid_(v8236))));
                }
              if (v_or == CTRUE) Result =CTRUE; 
            else Result = CFALSE;}
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_inline_method1(method *v62612,list *v8228,ClaireClass *v8235) { 
    
    GC_BIND;
    if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
     mtformat_module1(Optimize.it,((char*)"macroexpansion of ~S with method ~S \n"),5,list::alloc(2,_oid_(v8228),_oid_(v62612)));
    else ;{ OID Result = 0;
      Result = (*Optimize.c_code)(GC_OID(c_inline_method2(v62612,v8228)),
        _oid_(v8235));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_inline_method2(method *v62612,list *v8228) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { OID Result = 0;
      { lambda * v8222 = GC_OBJECT(lambda,v62612->formula);
        OID  v8240 = GC_OID(v8222->body);
        list * v45944 = GC_OBJECT(list,bound_variables_any(v8240));
        symbol * v50338 = (((v62612->selector == Language.iterate) || 
            (v62612->selector == Language.Iterate)) ?
          OBJECT(Variable,(*(v8222->vars))[2])->pname :
          Kernel._class->name );
        v8240= (GC_OID(instruction_copy_any(v8240)));
        if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
         mtformat_module1(Optimize.it,((char*)"c_inline(~S) on ~S: ~S is bound : ~S \n"),5,list::alloc(4,_oid_(v62612),
          _oid_(v8228),
          _oid_(v45944),
          v8240));
        else ;{ CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v8238);
          for (START(v45944); NEXT(v8238);)
          { GC_LOOP;
            { Variable * v58820;
              { { Instruction *V_CC ;
                  { Variable * v60472 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                    _void_(v60472->pname = ((OBJECT(Variable,v8238)->pname == v50338) ?
                      v50338 :
                      gensym_void() ));
                    _void_(v60472->index = 100000);
                    add_I_property(Kernel.instances,Language._Variable,11,_oid_(v60472));
                    V_CC = close_Instruction1(v60472);
                    }
                  v58820= (Variable *) V_CC;}
                GC_OBJECT(Variable,v58820);}
              store_object(v58820,
                3,
                Kernel._object,
                get_property(Kernel.range,OBJECT(ClaireObject,v8238)),
                CFALSE);
              GC__OID(v8240 = substitution_any(v8240,OBJECT(Variable,v8238),_oid_(v58820)), 1);
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        _void_(Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)v45944->length));
        Result = c_substitution_any(v8240,GC_OBJECT(list,v8222->vars),v8228,CFALSE);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_inline_arg_ask_any(OID v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      if (INHERIT(OWNER(v62612),Language._Call))
       { list * v8228 = GC_OBJECT(list,OBJECT(Call,v62612)->args);
        OID  v8229;
        { { list * v57272;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID v8240; CL_INT CLcount;
                v_list = v8228;
                 v57272 = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { v8240 = (*(v_list))[CLcount];
                  v_val = (*Optimize.c_type)(v8240);
                  
                  (*((list *) v57272))[CLcount] = v_val;}
                }
              GC_OBJECT(list,v57272);}
            v8229 = restriction_I_property(OBJECT(Call,v62612)->selector,v57272,CTRUE);
            }
          GC_OID(v8229);}
        if (Kernel._method == OWNER(v8229))
         { if ((OBJECT(method,v8229)->inline_ask == CTRUE) && 
              (c_inline_ask_method(OBJECT(method,v8229),v8228) == CTRUE))
           Result = c_inline_method2(OBJECT(method,v8229),v8228);
          else Result = Kernel.cfalse;
            }
        else Result = Core.nil->value;
          }
      else { OID  v58233;
          { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(v60472->selector = Kernel.set_I);
              _void_(v60472->args = list::alloc(1,v62612));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
              v58233 = _oid_(close_Instruction1(v60472));
              }
            GC_OID(v58233);}
          Result = c_inline_arg_ask_any(v58233);
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_substitution_any(OID v62612,list *v58580,list *v55513,ClaireBoolean *v59099) { 
    
    GC_BIND;
    { OID Result = 0;
      if (INHERIT(OWNER(v62612),Language._Variable))
       { OID  v8225;
        { { OID  v21233 = CNULL;
            { CL_INT  v8226 = 1;
              CL_INT  v15130 = v58580->length;
              { CL_INT loop_handle = ClEnv->cHandle;
                while (((CL_INT)v8226 <= (CL_INT)v15130))
                { if (OBJECT(Variable,v62612)->pname == OBJECT(Variable,(*(v58580))[v8226])->pname)
                   { v21233= (((OID)v8226));
                    ClEnv->cHandle = loop_handle; break;}
                  ++v8226;
                  POP_SIGNAL;}
                }
              }
            v8225 = v21233;
            }
          GC_OID(v8225);}
        if (((OID)v8225) != CNULL)
         Result = (*(v55513))[v8225];
        else Result = v62612;
          }
      else if (INHERIT(OWNER(v62612),Kernel._bag))
       { { CL_INT  v8225 = 1;
          CL_INT  v15131 = OBJECT(bag,v62612)->length;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)v8225 <= (CL_INT)v15131))
            { GC_LOOP;
              ((*(OBJECT(list,v62612)))[v8225]=GC_OID(c_substitution_any((*(OBJECT(bag,v62612)))[v8225],v58580,v55513,v59099)));
              ++v8225;
              GC_UNLOOP;POP_SIGNAL;}
            }
          }
        Result = v62612;
        }
      else if (INHERIT(OWNER(v62612),Language._Call))
       { if (OBJECT(Call,v62612)->selector == Core.eval)
         Result = c_substitution_any(GC_OID((*(OBJECT(Call,v62612)->args))[1]),v58580,v55513,((OBJECT(Call,v62612)->args->length == 1) ? CTRUE : (((OBJECT(Call,v62612)->args->length == 2) && 
            (belong_to((*(v55513))[1],(*(OBJECT(Call,v62612)->args))[2]) == CTRUE)) ? CTRUE : CFALSE)));
        else if (v59099 == CTRUE)
         { ClaireHandler c_handle = ClaireHandler();
          if ERROR_IN 
          { { list * v61117;
              { { CL_INT loop_handle = ClEnv->cHandle;
                  bag *v_list; OID v_val;
                  OID v8241; CL_INT CLcount;
                  v_list = GC_OBJECT(list,OBJECT(Call,v62612)->args);
                   v61117 = v_list->clone();
                  for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                  { v8241 = (*(v_list))[CLcount];
                    v_val = c_substitution_any(v8241,v58580,v55513,CTRUE);
                    
                    (*((list *) v61117))[CLcount] = v_val;}
                  }
                GC_OBJECT(list,v61117);}
              Result = apply_property(OBJECT(Call,v62612)->selector,v61117);
              }
            ERROR_FREE;}
          else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
          { c_handle.catchIt();{ if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
               mtformat_module1(Optimize.it,((char*)"a strange problem happens ~A \n"),0,GC_OBJECT(list,list::alloc(1,((OID)ClEnv->verbose))));
              else ;warn_void();
              if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
               mtformat_module1(Optimize.it,((char*)"`BLUE failed substitution: ~S"),2,GC_OBJECT(list,list::alloc(1,GC_OID(_oid_(ClEnv->exception_I)))));
              else ;c_substitution_any(GC_OID(_oid_(OBJECT(Call,v62612)->args)),v58580,v55513,CFALSE);
              Result = v62612;
              }
            }
          else PREVIOUS_HANDLER;}
        else { c_substitution_any(GC_OID(_oid_(OBJECT(Call,v62612)->args)),v58580,v55513,CFALSE);
            Result = v62612;
            }
          }
      else if (INHERIT(OWNER(v62612),Language._Instruction))
       { { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(v8235);
          bag *v8235_support;
          v8235_support = OWNER(v62612)->slots;
          for (START(v8235_support); NEXT(v8235);)
          { OID  v8241 = get_slot(OBJECT(slot,v8235),OBJECT(ClaireObject,v62612));
            put_slot(OBJECT(slot,v8235),OBJECT(ClaireObject,v62612),c_substitution_any(v8241,v58580,v55513,v59099));
            }
          }
        Result = v62612;
        }
      else Result = v62612;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  eval_any2(OID v8240,ClaireClass *v8241) { 
    POP_SIGNAL; return (OPT_EVAL(v8240));}
  

CL_EXPORT list * bound_variables_any(OID v62612) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { list *Result ;
      { list * v8228 = list::empty(Kernel._any);
        if (INHERIT(OWNER(v62612),Language._Instruction_with_var))
         v8228= (list::alloc(Kernel._any,1,GC_OID(_oid_(OBJECT(For,v62612)->var))));
        if (INHERIT(OWNER(v62612),Language._Variable))
         ;else if (INHERIT(OWNER(v62612),Language._Instruction))
         { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v8235);
          for (START(OBJECT(ClaireObject,v62612)->isa->slots); NEXT(v8235);)
          { GC_LOOP;
            GC__ANY(v8228 = add_star_list(v8228,GC_OBJECT(list,bound_variables_any(get_slot(OBJECT(slot,v8235),OBJECT(ClaireObject,v62612))))), 1);
            GC_UNLOOP; POP_SIGNAL;}
          }
        else if (INHERIT(OWNER(v62612),Kernel._bag))
         { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v8240);
          for (START(OBJECT(bag,v62612)); NEXT(v8240);)
          { GC_LOOP;
            v8228= (add_star_list(v8228,GC_OBJECT(list,bound_variables_any(v8240))));
            GC_UNLOOP; POP_SIGNAL;}
          }
        Result = v8228;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_boolean_any(OID v8240) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireType * v58828 = GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v8240)));
        ClaireType * v50349 = ptype_type(v58828);
        if (_inf_equal_type(v50349,Kernel._boolean) == CTRUE)
         { if (INHERIT(OWNER(v8240),Language._Call))
           { if ((OBJECT(Call,v8240)->selector == Core.NOT) && 
                (ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(GC_OID((*(OBJECT(Call,v8240)->args))[1])))) != Kernel._boolean))
             { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(v60472->selector = Core._I_equal);
                { Call * v15133 = v60472; 
                  list * v15134;
                  { OID v_bag;
                    GC_ANY(v15134= list::empty(Kernel.emptySet));
                    { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        _void_(v60472->selector = Kernel.boolean_I);
                        _void_(v60472->args = list::alloc(1,GC_OID((*(OBJECT(Call,v8240)->args))[1])));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                        v_bag = _oid_(close_Instruction1(v60472));
                        }
                      GC_OID(v_bag);}
                    ((list *) v15134)->addFast((OID)v_bag);
                    ((list *) v15134)->addFast((OID)Kernel.ctrue);}
                  _void_(v15133->args = v15134);}
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v8240 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v8240);}
            }
          if (_inf_equal_type(v58828,Kernel._boolean) == CTRUE)
           Result = c_strict_code_any(v8240,Kernel._boolean);
          else Result = (*Optimize.c_code)(v8240,
              _oid_(Kernel._boolean));
            }
        else if (_inf_equal_type(v58828,Kernel._bag) == CTRUE)
         { OID  v63999;
          { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(v60472->selector = Core._I_equal);
              { Call * v15136 = v60472; 
                list * v15158;
                { OID v_bag;
                  GC_ANY(v15158= list::empty(Kernel.emptySet));
                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Kernel.length);
                      _void_(v60472->args = list::alloc(1,v8240));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v_bag = _oid_(close_Instruction1(v60472));
                      }
                    GC_OID(v_bag);}
                  ((list *) v15158)->addFast((OID)v_bag);
                  ((list *) v15158)->addFast((OID)((OID)0));}
                _void_(v15136->args = v15158);}
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
              v63999 = _oid_(close_Instruction1(v60472));
              }
            GC_OID(v63999);}
          Result = (*Optimize.c_code)(v63999);
          }
        else { OID  v21527;
            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(v60472->selector = Kernel.boolean_I);
                _void_(v60472->args = list::alloc(1,v8240));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v21527 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v21527);}
            Result = (*Optimize.c_code)(v21527);
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  



/***** CLAIRE Compilation of file ./compile/ocall.cl 
         [version 3.5.0 / safety 5] *****/

CL_EXPORT OID  restriction_I_property(property *v62612,list *v8228,ClaireBoolean *v24299) { 
    { CL_INT  v8225 = 1;
      CL_INT  v15160 = v8228->length;
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((CL_INT)v8225 <= (CL_INT)v15160))
        { ((*(v8228))[v8225]=_oid_(ptype_type(OBJECT(ClaireType,(*(v8228))[v8225]))));
          ++v8225;
          POP_SIGNAL;}
        }
      }
    POP_SIGNAL; return (restriction_I_list(v62612->definition,v8228,v24299));}
  

CL_EXPORT OID  restriction_I_list(list *v58574,list *v8228,ClaireBoolean *v24299) { 
    
    GC_RESERVE(3);  // v3.3.39 optim !
    if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
     mtformat_module1(Optimize.it,((char*)"call restriction!(~S,~S) \n"),5,list::alloc(2,_oid_(v58574),_oid_(v8228)));
    else ;{ OID Result = 0;
      { ClaireBoolean * v62892 = ((class_I_type(OBJECT(ClaireType,(*(v8228))[1]))->open == 3) ? CTRUE : CFALSE);
        OID  v51797 = _oid_(Kernel.emptySet);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v8234);
          for (START(v58574); NEXT(v8234);)
          { GC_LOOP;
            if ((boolean_I_any(v51797) != CTRUE) && 
                (tmatch_ask_list(v8228,OBJECT(restriction,v8234)->domain) == CTRUE))
             { if (v24299 == CTRUE)
               GC__OID(v51797 = v8234, 1);
              else v51797= (_oid_(OBJECT(restriction,v8234)->range));
                { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
              }
            else if (length_bag(_exp_list(OBJECT(restriction,v8234)->domain,v8228)) != 0)
             { if (v24299 != CTRUE)
               { if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
                 mtformat_module1(Optimize.it,((char*)"~S add ~S \n"),5,list::alloc(2,v8234,_oid_(OBJECT(restriction,v8234)->range)));
                else ;GC__OID(v51797 = _oid_(U_type(OBJECT(ClaireType,v51797),OBJECT(restriction,v8234)->range)), 2);
                }
              else if (((CL_INT)Optimize.compiler->safety <= (CL_INT)3) || 
                  ((equal(v51797,_oid_(Kernel.emptySet)) != CTRUE) || 
                    (v62892 == CTRUE)))
               { v51797= (_oid_(Optimize.ambiguous));
                { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                }
              else GC__OID(v51797 = v8234, 3);
                }
            GC_UNLOOP; POP_SIGNAL;}
          }
        if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
         mtformat_module1(Optimize.it,((char*)"exit de restriction -> ~S \n"),5,GC_OBJECT(list,list::alloc(1,v51797)));
        else ;Result = v51797;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  restriction_I_class(ClaireClass *v8219,list *v58574,list *v8228) { 
    
    GC_BIND;
    if ((CL_INT)Optimize.compiler->safety > (CL_INT)3)
     ((*(v8228))[1]=GC_OID(_oid_(_exp_type(v8219,OBJECT(ClaireType,(*(v8228))[1])))));
    { OID Result = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v8234);
        Result= Kernel.cfalse;
        for (START(v58574); NEXT(v8234);)
        if (_inf_equalt_class(v8219,OBJECT(ClaireType,(*(OBJECT(restriction,v8234)->domain))[1])) == CTRUE)
         { if (tmatch_ask_list(v8228,OBJECT(restriction,v8234)->domain) == CTRUE)
           { Result = v8234;
            ClEnv->cHandle = loop_handle;break;}
          else if (length_bag(_exp_list(OBJECT(restriction,v8234)->domain,v8228)) != 0)
           { Result = _oid_(Optimize.ambiguous);
            ClEnv->cHandle = loop_handle;break;}
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * use_range_method(method *v62612,list *v56367) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if ((v62612->inline_ask == CTRUE) && 
          (v62612->typing == CNULL))
       { list * v58578 = GC_OBJECT(list,v62612->formula->vars);
        ClaireType * v56375 = Kernel._any;
        list * v43491;
        { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID v8238; CL_INT CLcount;
            v_list = v58578;
             v43491 = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { v8238 = (*(v_list))[CLcount];
              v_val = (*Kernel.range)(v8238);
              
              (*((list *) v43491))[CLcount] = v_val;}
            }
          GC_OBJECT(list,v43491);}
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(v8238);
          for (START(v58578); NEXT(v8238);)
          put_property2(Kernel.range,OBJECT(ClaireObject,v8238),(*(v56367))[((CL_INT)(((CL_INT)(*Kernel.index)(v8238)))+(CL_INT)1)]);
          }
        v56375= (GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->formula->body)))));
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(v8238);
          for (START(v58578); NEXT(v8238);)
          put_property2(Kernel.range,OBJECT(ClaireObject,v8238),(*(v43491))[((CL_INT)(((CL_INT)(*Kernel.index)(v8238)))+(CL_INT)1)]);
          }
        if (INHERIT(v62612->range->isa,Kernel._type))
         v56375= (GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel._exp)(_oid_(v56375),
          _oid_(v62612->range)))));
        if (boolean_I_any(_oid_(v56375)) != CTRUE)
         (*Optimize.Cerror)(_string_(((char*)"[207] inline ~S: range ~S is incompatible with ~S (inferred)")),
          _oid_(v62612),
          _oid_(v62612->range),
          GC_OID((*Optimize.c_type)(GC_OID(v62612->formula->body))));
        Result = v56375;
        }
      else { if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
           mtformat_module1(Optimize.it,((char*)"will try to use range type with ~S \n"),5,list::alloc(1,_oid_(v56367)));
          else ;{ OID  v8222 = GC_OID(v62612->typing);
            list * v43491;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID v8237; CL_INT CLcount;
                v_list = v56367;
                 v43491 = v_list->clone(Kernel._type);
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { v8237 = (*(v_list))[CLcount];
                  v_val = _oid_(ptype_type(OBJECT(ClaireType,v8237)));
                  
                  (*((list *) v43491))[CLcount] = v_val;}
                }
              GC_OBJECT(list,v43491);}
            ClaireType * v43738 = v62612->range;
            ClaireType * v43739;
            { { ClaireObject *V_CC ;
                { if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
                   mtformat_module1(Optimize.it,((char*)"apply typing ~S --- ~S \n"),5,list::alloc(2,_oid_(v56367),_oid_(v43491)));
                  else ;{ ClaireHandler c_handle = ClaireHandler();
                    if ERROR_IN 
                    { if (INHERIT(OWNER(v8222),Core._lambda))
                       V_CC = OBJECT(ClaireType,apply_lambda(OBJECT(lambda,v8222),v43491));
                      else if (INHERIT(OWNER(v8222),Kernel._property))
                       V_CC = OBJECT(ClaireType,apply_property(OBJECT(property,v8222),v43491));
                      else if (INHERIT(OWNER(v8222),Kernel._function))
                       { OID v61842;{ list * v24411;
                          { list * v18543 = list::empty(Kernel.emptySet);
                            { CL_INT  v8230 = 1;
                              CL_INT  v15161 = ((CL_INT)v56367->length+(CL_INT)1);
                              { CL_INT loop_handle = ClEnv->cHandle;
                                while (((CL_INT)v8230 <= (CL_INT)v15161))
                                { v18543->addFast((OID)_oid_(Kernel._object));
                                  ++v8230;
                                  POP_SIGNAL;}
                                }
                              }
                            v24411 = GC_OBJECT(list,v18543);
                            }
                          v61842 = apply_function(OBJECT(ClaireFunction,v8222),v24411,v43491);
                          }
                        
                        V_CC=OBJECT(ClaireType,v61842);}
                      else V_CC = v43738;
                        ERROR_FREE;}
                    else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                    { c_handle.catchIt();{ if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
                         mtformat_module1(Optimize.it,((char*)"~S's 2nd-order type failed on ~S \n"),0,GC_OBJECT(list,list::alloc(2,_oid_(v62612),_oid_(v56367))));
                        else ;V_CC = v43738;
                        }
                      }
                    else PREVIOUS_HANDLER;}
                  }
                v43739= (ClaireType *) V_CC;}
              GC_OBJECT(ClaireType,v43739);}
            if ((boolean_I_any(sort_equal_class(osort_any(_oid_(v43738)),osort_any(_oid_(v43739)))) == CTRUE) || 
                (v62612->selector == Core.externC))
             Result = v43739;
            else if (boolean_I_any(sort_equal_class(Kernel._any,osort_any(_oid_(v43738)))) == CTRUE)
             { Union * v60472 = ((Union *) GC_OBJECT(Union,new_object_class(Core._Union)));
              _void_(v60472->t1 = Kernel._any);
              _void_(v60472->t2 = v43739);
              Result = v60472;
              }
            else Result = v43738;
              }
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Call2_Optimize(Call *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { ClaireObject *V_CC ;
        if (v62612->selector == Language.function_I)
         V_CC = Kernel._function;
        else { property * v8235 = v62612->selector;
            list * v8228 = GC_OBJECT(list,v62612->args);
            list * v30871;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID v8240; CL_INT CLcount;
                v_list = v8228;
                 v30871 = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { v8240 = (*(v_list))[CLcount];
                  v_val = (*Optimize.c_type)(v8240);
                  
                  (*((list *) v30871))[CLcount] = v_val;}
                }
              GC_OBJECT(list,v30871);}
            if (v8235 == Optimize.safe)
             V_CC = OBJECT(ClaireType,(*(v30871))[1]);
            else if ((v8235 == Core.externC) && 
                ((v8228->length == 2) && 
                  (INHERIT(OWNER((*(v8228))[2]),Kernel._class))))
             V_CC = OBJECT(ClaireClass,(*(v8228))[2]);
            else if ((v8235 == Core.NEW) && 
                (INHERIT(OWNER((*(v8228))[1]),Kernel._class)))
             V_CC = OBJECT(ClaireClass,(*(v8228))[1]);
            else if ((v8235 == Core.check_in) && 
                (INHERIT(OWNER((*(v8228))[2]),Kernel._type)))
             { V_CC = ((v8228->length == 2) ?
                sort_abstract_I_type(OBJECT(ClaireType,(*(v8228))[2])) :
                OBJECT(ClaireType,(*(v8228))[2]) );
              }
            else if ((v8235 == Kernel.nth) && 
                (_inf_equal_type(OBJECT(ClaireType,(*(v30871))[1]),Kernel._array) == CTRUE))
             { if (_inf_equal_type(GC_OBJECT(ClaireType,member_type(OBJECT(ClaireType,(*(v30871))[1]))),Kernel._float) == CTRUE)
               V_CC = Kernel._float;
              else V_CC = member_type(OBJECT(ClaireType,(*(v30871))[1]));
                }
            else if ((v8235 == Core._at) && 
                (INHERIT(OWNER((*(v8228))[1]),Kernel._property)))
             { property * v8232 = OBJECT(property,(*(v8228))[1]);
              OID  v8219 = (*(v8228))[2];
              if ((INHERIT(OWNER(v8219),Kernel._class)) && 
                  (Kernel._method == owner_any((*Core._at)(_oid_(v8232),
                    v8219))))
               V_CC = set::alloc(1,GC_OID((*Core._at)(_oid_(v8232),
                v8219)));
              else V_CC = Kernel._any;
                }
            else if ((v8235 == Kernel.get) && 
                (INHERIT(OWNER((*(v8228))[1]),Kernel._relation)))
             { ClaireRelation * v8234 = OBJECT(ClaireRelation,(*(v8228))[1]);
              if (INHERIT(v8234->isa,Kernel._property))
               { ClaireObject * v58947 = GC_OBJECT(ClaireObject,_at_property1(((property *) v8234),class_I_type(OBJECT(ClaireType,(*(v30871))[2]))));
                if (Kernel._slot == v58947->isa)
                 { if ((_inf_equal_type(CLREAD(restriction,v58947,range),Kernel._bag) == CTRUE) && 
                      ((CL_INT)Optimize.compiler->safety < (CL_INT)3))
                   V_CC = class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)((*(v8228))[2]))));
                  else V_CC = ((belong_to(CLREAD(slot,v58947,DEFAULT),_oid_(CLREAD(restriction,v58947,range))) == CTRUE) ?
                    CLREAD(restriction,v58947,range) :
                    extends_type(CLREAD(restriction,v58947,range)) );
                  }
                else V_CC = v8234->range;
                  }
              else if (INHERIT(v8234->isa,Kernel._table))
               { V_CC = ((belong_to(CLREAD(table,v8234,DEFAULT),_oid_(v8234->range)) == CTRUE) ?
                  v8234->range :
                  extends_type(v8234->range) );
                }
              else V_CC = CFALSE;
                }
            else { OID  v8234 = GC_OID(restriction_I_property(v8235,v30871,CTRUE));
                if (Kernel._slot == OWNER(v8234))
                 { if ((v8235 == Kernel.instances) && 
                      (INHERIT(OWNER((*(v8228))[1]),Kernel._class)))
                   { Param * v60472 = ((Param *) GC_OBJECT(Param,new_object_class(Core._Param)));
                    _void_(v60472->arg = Kernel._list);
                    _void_(v60472->params = list::alloc(1,_oid_(Kernel.of)));
                    _void_(v60472->args = list::alloc(1,_oid_(set::alloc(1,(*(v8228))[1]))));
                    V_CC = v60472;
                    }
                  else V_CC = OBJECT(restriction,v8234)->range;
                    }
                else if (Kernel._method == OWNER(v8234))
                 V_CC = use_range_method(OBJECT(method,v8234),v30871);
                else if (boolean_I_any(_oid_(v8235->restrictions)) != CTRUE)
                 V_CC = selector_psort_Call(v62612);
                else V_CC = (((v8235->open == 3) || 
                    (v8234 != _oid_(Optimize.ambiguous))) ?
                  sort_abstract_I_type(v8235->range) :
                  sort_abstract_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,restriction_I_property(v8235,v30871,CFALSE)))) );
                }
              }
          Result= (ClaireType *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Call_Optimize(Call *v62612) { 
    POP_SIGNAL; return (c_code_call_Call(v62612,Kernel._void));}
  

CL_EXPORT OID  c_code_call_Call(Call *v62612,ClaireClass *v58797) { 
    
    GC_BIND;
    if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
     mtformat_module1(Optimize.it,((char*)"c_code_call(~S)  \n"),5,list::alloc(1,_oid_(v62612)));
    else ;{ OID Result = 0;
      { property * v8235 = v62612->selector;
        list * v8228 = GC_OBJECT(list,v62612->args);
        if ((v62612->selector == Core.update_location) && 
            ((v62612->args->length != 0) && 
              (equal((*(v62612->args))[1],Optimize._stardebug_local_file_star->value) == CTRUE)))
         { OID  v25371;
          { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(v60472->selector = Core.externC);
              { Call * v15164 = v60472; 
                list * v15166;
                { OID v_bag;
                  GC_ANY(v15166= list::empty(Kernel.emptySet));
                  { { print_in_string_void();
                      print_any(GC_OID(Optimize._stardebug_local_file_star->value));
                      v_bag = _string_(end_of_string_void());
                      }
                    GC_OID(v_bag);}
                  ((list *) v15166)->addFast((OID)v_bag);
                  ((list *) v15166)->addFast((OID)_oid_(Kernel._string));}
                _void_(v15164->args = v15166);}
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
              v25371 = _oid_(close_Instruction1(v60472));
              }
            GC_OID(v25371);}
          ((*(GC_OBJECT(list,v62612->args)))[1]=v25371);
          }
        if ((INHERIT(OWNER((*(v8228))[1]),Core._global_variable)) && 
            ((equal((*Kernel.range)((*(v8228))[1]),_oid_(Kernel.emptySet)) == CTRUE) && 
              (designated_ask_any(GC_OID((*Kernel.value)((*(v8228))[1]))) == CTRUE)))
         ((*(v8228))[1]=GC_OID((*Kernel.value)((*(v8228))[1])));
        { OID  v8229 = GC_OID(inline_optimize_ask_Call(v62612));
          ClaireBoolean * v8218 = inherit_ask_class(OWNER((*(v8228))[1]),Kernel._property);
          OID  v8220 = GC_OID(daccess_any(_oid_(v62612),_sup_integer(Optimize.compiler->safety,5)));
          if ((v8218 == CTRUE) && 
              (((v8235 == Kernel.put) || 
                  (v8235 == Core.write)) && 
                (v8228->length == 3)))
           Result = c_code_write_Call(v62612);
          else if ((v8218 == CTRUE) && 
              ((v8235 == Core.put_store) && 
                ((v8228->length == 4) && 
                  ((*(v8228))[4] == Kernel.ctrue))))
           Result = c_code_write_Call(v62612);
          else if ((v8218 == CTRUE) && 
              (v8235 == Core.unknown_ask))
           Result = c_code_hold_property(OBJECT(property,(*(v8228))[1]),(*(v8228))[2],CNULL,CTRUE);
          else if ((v8218 == CTRUE) && 
              (v8235 == Core.known_ask))
           Result = c_code_hold_property(OBJECT(property,(*(v8228))[1]),(*(v8228))[2],CNULL,CFALSE);
          else if ((v8218 == CTRUE) && 
              ((v8235 == Core.erase) && 
                (INHERIT(OWNER((*(v8228))[2]),Language._Variable))))
           Result = (*Optimize.c_code)(GC_OID(Produce_erase_property2(OBJECT(property,(*(v8228))[1]),OBJECT(Variable,(*(v8228))[2]))),
            _oid_(v58797));
          else if (v8235 == Optimize.safe)
           { CL_INT  v8241 = Optimize.compiler->safety;
            ClaireBoolean * v8218 = Optimize.compiler->overflow_ask;
            OID  v8240 = CNULL;
            _void_(Optimize.compiler->safety = 1);
            _void_(Optimize.compiler->overflow_ask = CTRUE);
            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(v60472->selector = Optimize.safe);
                _void_(v60472->args = list::alloc(1,GC_OID((*Optimize.c_code)((*(v8228))[1],
                  _oid_(v58797)))));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v8240 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v8240);}
            _void_(Optimize.compiler->safety = v8241);
            _void_(Optimize.compiler->overflow_ask = v8218);
            Result = v8240;
            }
          else if (((v8235 == Kernel.add) || 
                (v8235 == Kernel.add_I)) && 
              (v8218 == CTRUE))
           Result = c_code_add_Call(v62612);
          else if (((v8235 == Kernel.add) || 
                (v8235 == Kernel.add_I)) && 
              (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)((*(v8228))[1]))),Kernel._bag) == CTRUE))
           Result = c_code_add_bag_Call(v62612);
          else if ((v8218 == CTRUE) && 
              (v8235 == Kernel._delete))
           Result = c_code_delete_Call(v62612);
          else if ((contain_ask_set(Optimize.OPT->to_remove,_oid_(v8235)) == CTRUE) || 
              ((v8235 == Optimize.c_interface) && 
                  ((v8228->length == 2) && 
                    (contain_ask_set(GC_OBJECT(set,Optimize.OPT->legal_modules),GC_OID(get_module_object(v8235))) != CTRUE))))
           Result = Core.nil->value;
          else if (v8220 != CNULL)
           Result = v8220;
          else if (Kernel._method == OWNER(v8229))
           Result = c_inline_method1(OBJECT(method,v8229),v8228,c_srange_method(OBJECT(method,v8229)));
          else if (((v8235 == Kernel._equal) || 
                (v8235 == Core._I_equal)) && 
              (daccess_any((*(v8228))[1],CTRUE) != CNULL))
           Result = c_code_hold_property(OBJECT(property,(*(OBJECT(bag,(*Core.args)((*(v8228))[1]))))[1]),GC_OID((*(OBJECT(bag,(*Core.args)((*(v8228))[1]))))[2]),(*(v8228))[2],equal(_oid_(v8235),_oid_(Kernel._equal)));
          else if (((v8235 == Kernel._equal) || 
                (v8235 == Core._I_equal)) && 
              (daccess_any((*(v8228))[2],CTRUE) != CNULL))
           Result = c_code_hold_property(OBJECT(property,(*(OBJECT(bag,(*Core.args)((*(v8228))[2]))))[1]),GC_OID((*(OBJECT(bag,(*Core.args)((*(v8228))[2]))))[2]),(*(v8228))[1],equal(_oid_(v8235),_oid_(Kernel._equal)));
          else if (((v8235 == Kernel.nth_equal) || 
                (v8235 == Kernel.put)) && 
              ((INHERIT(OWNER((*(v8228))[1]),Kernel._table)) && 
                (v8228->length == 3)))
           Result = c_code_table_Call(v62612);
          else if (((v8235 == Kernel.nth_put) || 
                (v8235 == Kernel.nth_equal)) && 
              ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)((*(v8228))[1]))),Kernel._array) == CTRUE) && 
                (v8228->length == 3)))
           Result = c_code_array_Call(v62612);
          else if ((v8235 == Kernel.nth) || 
              (((v8235 == Kernel.get) && 
                  (INHERIT(OWNER((*(v8228))[1]),Kernel._table))) || 
                ((v8235 == Kernel.nth_get) && 
                    (Kernel._array == OWNER((*(v8228))[1])))))
           Result = c_code_nth_Call(v62612);
          else if (v8235 == Kernel._Z)
           Result = c_code_belong_Call(v62612);
          else if (v8235 == Core.Id)
           Result = (*Optimize.c_code)(GC_OID(OPT_EVAL((*(v8228))[1])));
          else if (v8235 == Language.function_I)
           Result = _oid_(make_function_string(string_I_symbol(extract_symbol_any((*(v8228))[1]))));
          else if ((v8235 == Core.NOT) && 
              (INHERIT(OWNER((*(v8228))[1]),Language._Select)))
           Result = c_code_not_Select(OBJECT(Select,(*(v8228))[1]));
          else if ((v8235 == Core.call) && 
              (INHERIT(OWNER((*(v8228))[1]),Kernel._property)))
           { OID  v28254;
            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                update_property(Kernel.selector,
                  v60472,
                  2,
                  Kernel._object,
                  (*(v8228))[1]);
                _void_(v60472->args = cdr_list(v8228));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v28254 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v28254);}
            Result = (*Optimize.c_code)(v28254);
            }
          else if (v8235->open == 3)
           { list * v29215;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID v8240; CL_INT CLcount;
                v_list = v8228;
                 v29215 = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { v8240 = (*(v_list))[CLcount];
                  v_val = (*Optimize.c_type)(v8240);
                  
                  (*((list *) v29215))[CLcount] = v_val;}
                }
              GC_OBJECT(list,v29215);}
            Result = c_warn_property(v8235,v8228,v29215);
            }
          else { ClaireBoolean * g1090I;
            { ClaireBoolean *v_and;
              { v_and = ((v8235 == Language.bit_vector) ? CTRUE : CFALSE);
                if (v_and == CFALSE) g1090I =CFALSE; 
                else { { OID  v51318;
                    { CL_INT loop_handle = ClEnv->cHandle;
                      ITERATE(v8241);
                      v51318= Kernel.cfalse;
                      bag *v8241_support;
                      v8241_support = GC_OBJECT(list,v62612->args);
                      for (START(v8241_support); NEXT(v8241);)
                      if (inherit_ask_class(OWNER(v8241),Kernel._integer) != CTRUE)
                       { v51318 = Kernel.ctrue;
                        ClEnv->cHandle = loop_handle;break;}
                      }
                    v_and = not_any(v51318);
                    }
                  if (v_and == CFALSE) g1090I =CFALSE; 
                  else g1090I = CTRUE;}
                }
              }
            
            if (g1090I == CTRUE) Result = OPT_EVAL(_oid_(v62612));
              else if ((v8235 == Optimize.anyObject_I) || 
                ((v8235 == Optimize.object_I) || 
                  ((v8235 == Kernel.add_method) && 
                      (v8218 == CTRUE))))
             Result = _oid_(v62612);
            else { list * v30871;
                { { CL_INT loop_handle = ClEnv->cHandle;
                    bag *v_list; OID v_val;
                    OID v8240; CL_INT CLcount;
                    v_list = v8228;
                     v30871 = v_list->clone();
                    for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                    { v8240 = (*(v_list))[CLcount];
                      v_val = (*Optimize.c_type)(v8240);
                      
                      (*((list *) v30871))[CLcount] = v_val;}
                    }
                  GC_OBJECT(list,v30871);}
                OID  v8242 = GC_OID(restriction_I_property(v8235,v30871,CTRUE));
                if (Kernel._slot == OWNER(v8242))
                 { ClaireBoolean * v27085 = ((belong_to(OBJECT(slot,v8242)->DEFAULT,_oid_(OBJECT(restriction,v8242)->range)) != CTRUE) ? ((contain_ask_set(Optimize.OPT->knowns,_oid_(v8235)) != CTRUE) ? (((CL_INT)Optimize.compiler->safety < (CL_INT)5) ? CTRUE: CFALSE): CFALSE): CFALSE);
                  if ((v27085 != CTRUE) || 
                      (designated_ask_any((*(v8228))[1]) == CTRUE))
                   { Call_slot * v60472 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
                    _void_(v60472->selector = OBJECT(slot,v8242));
                    _void_(v60472->arg = (*Optimize.c_code)((*(v8228))[1],
                      _oid_(psort_any(_oid_(domain_I_restriction(OBJECT(restriction,v8242)))))));
                    _void_(v60472->test = v27085);
                    add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v60472));
                    Result = _oid_(close_Instruction1(v60472));
                    }
                  else { show_opportunist_integer1(3);
                      if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
                       mtformat_module1(Optimize.it,((char*)" `GREEN note: ... unsafe access to unknown slot: ~S \n"),3,GC_OBJECT(list,list::alloc(1,_oid_(v62612))));
                      else ;if (Optimize.compiler->optimize_ask == CTRUE)
                       { notice_void();
                        if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
                         mtformat_module1(Optimize.it,((char*)"`GREEN poorly optimized slot access: ~S\n"),3,GC_OBJECT(list,list::alloc(1,_oid_(v62612))));
                        else ;}
                      Result = c_warn_property(v8235,v8228,v30871);
                      }
                    }
                else if (Kernel._method == OWNER(v8242))
                 { if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
                   mtformat_module1(Optimize.it,((char*)"found a method \n"),5,GC_OBJECT(list,list::empty()));
                  else ;if (v8235 == Kernel.nth_equal)
                   _void_(Optimize.OPT->use_nth_equal = CTRUE);
                  if (v30871->memq(_oid_(Kernel._void)) == CTRUE)
                   (*Optimize.Cerror)(_string_(((char*)"[205] call ~S uses a void argument [~S]")),
                    _oid_(v62612),
                    _oid_(v30871));
                  if (((v8235 == Kernel.begin) || 
                        (v8235 == Kernel.end)) && 
                      (INHERIT(OWNER((*(v8228))[1]),Kernel._module)))
                   OPT_EVAL(_oid_(v62612));
                  if ((last_list(OBJECT(restriction,v8242)->domain) == _oid_(Kernel._listargs)) || 
                      (((*(OBJECT(restriction,v8242)->domain))[1] == _oid_(Kernel._void)) && 
                          ((*(v8228))[1] != _oid_(ClEnv))))
                   Result = _oid_(open_message_property(v8235,v8228));
                  else Result = c_code_method_method2(OBJECT(method,v8242),v8228,v30871,v58797);
                    }
                else if (INHERIT(OWNER(v8242),Kernel._keyword))
                 Result = c_warn_property(v8235,v8228,v30871);
                else Result = c_warn_Call(v62612,_oid_(v30871));
                  }
              }
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT Call * open_message_property(property *v62612,list *v8228) { 
    
    GC_BIND;
    { Call *Result ;
      { Instruction *V_CC ;
        { selector_register_property(v62612);
          { list * v29017;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID v8240; CL_INT CLcount;
                v_list = v8228;
                 v29017 = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { v8240 = (*(v_list))[CLcount];
                  if ((*Optimize.c_type)(v8240) != _oid_(Kernel._void))
                   v_val = (*Optimize.c_code)(v8240,
                    _oid_(Kernel._any));
                  else v_val = (*Optimize.Cerror)(_string_(((char*)"[206] use of void ~S in ~S(~A)")),
                      v8240,
                      _oid_(v62612),
                      _oid_(v8228));
                    
                  (*((list *) v29017))[CLcount] = v_val;}
                }
              GC_OBJECT(list,v29017);}
            if (Optimize.OPT->allocation == CTRUE)
             { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID v8240; CL_INT CLcount;
                v_list = v29017;
                 v29017 = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { v8240 = (*(v_list))[CLcount];
                  v_val = c_gc_I_any1(v8240);
                  
                  (*((list *) v29017))[CLcount] = v_val;}
                }
              GC_OBJECT(list,v29017);}
            { ClaireBoolean * g1092I;
              { ClaireBoolean *v_and;
                { v_and = Optimize.compiler->diet_ask;
                  if (v_and == CFALSE) g1092I =CFALSE; 
                  else { { OID  v53242;
                      { CL_INT loop_handle = ClEnv->cHandle;
                        ITERATE(v8240);
                        v53242= Kernel.cfalse;
                        for (START(v8228); NEXT(v8240);)
                        if ((INHERIT(OWNER(v8240),Kernel._class)) || 
                            (INHERIT(OWNER(v8240),Kernel._property)))
                         { v53242 = Kernel.ctrue;
                          ClEnv->cHandle = loop_handle;break;}
                        }
                      v_and = boolean_I_any(v53242);
                      }
                    if (v_and == CFALSE) g1092I =CFALSE; 
                    else g1092I = CTRUE;}
                  }
                }
              
              if (g1092I == CTRUE) { warn_void();
                  if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
                   mtformat_module1(Optimize.it,((char*)"`BLUE Non diet call ~S(~A) [254]\n"),2,list::alloc(2,_oid_(v62612),_oid_(v8228)));
                  else ;}
                }
            { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(v60472->selector = v62612);
              _void_(v60472->args = v29017);
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            }
          }
        Result= (Call *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * c_gc_ask_Call(Call *v62612) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = ((v62612->selector == Language.function_I) ? CTRUE : (((v62612->selector == Optimize.safe) ? ((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)((*(v62612->args))[1]))) == CTRUE) : (((stable_ask_relation(v62612->selector) == CTRUE) ? (((OBJECT(ClaireBoolean,_oid_((INHERIT(v62612->selector->range->isa,Kernel._class) ?
       (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v62612->selector->range))) : 
       (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(v62612->selector->range))))))) == CTRUE) ? CTRUE: CFALSE): CFALSE) != CTRUE)) ? CTRUE : CFALSE));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  daccess_any(OID v62612,ClaireBoolean *v8218) { 
    
    GC_BIND;
    { OID Result = 0;
      if (INHERIT(OWNER(v62612),Language._Call))
       { list * v8228 = GC_OBJECT(list,OBJECT(Call,v62612)->args);
        ClaireObject * v58947;
        { if ((OBJECT(Call,v62612)->selector == Kernel.get) && 
              (INHERIT(OWNER((*(v8228))[1]),Kernel._property)))
           v58947 = _at_property1(OBJECT(property,(*(v8228))[1]),class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)((*(v8228))[2])))));
          else v58947 = CFALSE;
            GC_OBJECT(ClaireObject,v58947);}
        if ((OBJECT(ClaireBoolean,Language.DEBUG_ask->value)) == CTRUE)
         Result = CNULL;
        else if ((Kernel._slot == v58947->isa) && ((v8218 == CTRUE) || 
            ((belong_to(CLREAD(slot,v58947,DEFAULT),_oid_(CLREAD(restriction,v58947,range))) == CTRUE) || 
              ((CLREAD(slot,v58947,srange) == Kernel._any) || 
                (CLREAD(slot,v58947,srange) == Kernel._integer)))))
         { Call_slot * v60472 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
          _void_(v60472->selector = ((slot *) v58947));
          _void_(v60472->arg = (*Optimize.c_code)((*(v8228))[2],
            _oid_(psort_any(_oid_(domain_I_restriction(((restriction *) v58947)))))));
          _void_(v60472->test = CFALSE);
          add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        else Result = CNULL;
          }
      else Result = CNULL;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * c_gc_ask_Call_slot(Call_slot *v62612) { 
    { ClaireBoolean *Result ;
      { slot * v8235 = v62612->selector;
        Result = ((_oid_((INHERIT(v8235->range->isa,Kernel._class) ?
         (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v8235->range))) : 
         (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(v8235->range))))) != Kernel.ctrue) ? ((v8235->range != Kernel._float) ? ((((CL_INT)1 <= (CL_INT)v8235->selector->open) || 
            (gcsafe_ask_class(domain_I_restriction(v8235)) != CTRUE)) ? CTRUE: CFALSE): CFALSE): CFALSE);
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Call_slot_Optimize(Call_slot *v62612) { 
    POP_SIGNAL; return (v62612->selector->range);}
  

CL_EXPORT ClaireType * c_type_Call_table_Optimize(Call_table *v62612) { 
    POP_SIGNAL; return (v62612->selector->range);}
  

CL_EXPORT ClaireType * c_type_Call_array_Optimize(Call_array *v62612) { 
    POP_SIGNAL; return (OBJECT(ClaireType,v62612->test));}
  

CL_EXPORT OID  c_code_write_Call(Call *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v8232 = GC_OID((*(v62612->args))[1]);
        OID  v8240 = GC_OID((*(v62612->args))[2]);
        OID  v8241 = GC_OID((*(v62612->args))[3]);
        OID  v58979 = GC_OID((*Optimize.c_type)(v8241));
        property * v58792 = v62612->selector;
        OID  v8235 = GC_OID((*Optimize.restriction_I)(v8232,
          _oid_(list::alloc(1,GC_OID((*Optimize.c_type)(v8240)))),
          Kernel.ctrue));
        if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
         mtformat_module1(Optimize.it,((char*)"c_code_write(~S) \n"),5,list::alloc(1,_oid_(v62612)));
        else ;_void_(Optimize.OPT->use_update = CTRUE);
        if (contain_ask_set(Optimize.OPT->to_remove,v8232) == CTRUE)
         Result = Core.nil->value;
        else if ((Kernel._slot == OWNER(v8235)) && ((_inf_equal_type(OBJECT(ClaireType,v58979),OBJECT(restriction,v8235)->range) == CTRUE) || 
            ((CL_INT)4 <= (CL_INT)Optimize.compiler->safety)))
         { if ((v8241 != CNULL) && 
              (boolean_I_any((*Kernel._exp)(v58979,
                GC_OID((*Kernel.srange)(v8235)))) != CTRUE))
           { if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
             mtformat_module1(Optimize.it,((char*)"====> ~S ^ ~S = ~S \n"),5,list::alloc(3,v58979,
              GC_OID((*Kernel.srange)(v8235)),
              GC_OID((*Kernel._exp)(v58979,
                GC_OID((*Kernel.srange)(v8235))))));
            else ;warn_void();
            if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
             mtformat_module1(Optimize.it,((char*)"`BLUE sort error in ~S: ~S is a ~S [253]\n"),2,list::alloc(3,_oid_(v62612),
              v8241,
              v58979));
            else ;}
          if (((_inf_equal_type(OBJECT(ClaireType,v58979),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(v8235)))) == CTRUE) || 
                ((_inf_equal_type(OBJECT(ClaireType,v58979),Kernel._object) == CTRUE) || 
                  (((*Kernel.srange)(v8235) != _oid_(Kernel._object)) || 
                    (v8241 == CNULL)))) && 
              ((v58792 != Core.write) || 
                  ((Update_ask_relation(OBJECT(ClaireRelation,v8232),v8240,v8241) == CTRUE) && 
                      ((OBJECT(ClaireRelation,v8232)->multivalued_ask == CFALSE) || 
                          (get_property(Kernel.if_write,OBJECT(ClaireObject,v8232)) == CNULL)))))
           { OID  v56379 = GC_OID((*Optimize.c_code)(v8240,
              _oid_(psort_any(_oid_(domain_I_restriction(OBJECT(restriction,v8235)))))));
            OID  v56380 = GC_OID(c_strict_code_any(v8241,psort_any(GC_OID((*Kernel.range)(v8235)))));
            Update * v60472 = ((Update *) GC_OBJECT(Update,new_object_class(Language._Update)));
            _void_(v60472->selector = v8232);
            _void_(v60472->value = v56380);
            { Update * v15193 = v60472; 
              OID  v15194;
              if (v58792 != Core.write)
               v15194 = _oid_(v58792);
              else v15194 = (*Optimize.c_code)(v8240,
                  _oid_(Kernel._any));
                _void_(v15193->arg = v15194);}
            { Update * v15195 = v60472; 
              OID  v15196;
              { Call_slot * v60472 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
                update_property(Kernel.selector,
                  v60472,
                  2,
                  Kernel._object,
                  v8235);
                _void_(v60472->arg = v56379);
                _void_(v60472->test = CFALSE);
                add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v60472));
                v15196 = _oid_(close_Instruction1(v60472));
                }
              _void_(v15195->var = v15196);}
            add_I_property(Kernel.instances,Language._Update,11,_oid_(v60472));
            Result = _oid_(close_Instruction1(v60472));
            }
          else if (v58792 == Kernel.put)
           { OID  v58045;
            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(v60472->selector = Kernel.store);
                _void_(v60472->args = list::alloc(5,v8240,
                  GC_OID((*Kernel.index)(v8235)),
                  GC_OID((*Kernel.srange)(v8235)),
                  v8241,
                  GC_OID((*Kernel.store_ask)(v8232))));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v58045 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v58045);}
            Result = (*Optimize.c_code)(v58045);
            }
          else { if (Optimize.compiler->diet_ask == CTRUE)
               { warn_void();
                if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
                 mtformat_module1(Optimize.it,((char*)"`BLUE ~S is not a diet call [254]"),2,list::alloc(1,_oid_(v62612)));
                else ;}
              if ((Optimize.compiler->optimize_ask == CTRUE) && 
                  (v8232 != _oid_(Kernel.instances)))
               { notice_void();
                if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
                 mtformat_module1(Optimize.it,((char*)"`GREEN poorly typed update: ~S\n"),3,list::alloc(1,_oid_(v62612)));
                else ;}
              { OID  v59006;
                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(v60472->selector = Core.update);
                    _void_(v60472->args = list::alloc(5,v8232,
                      v8240,
                      GC_OID((*Kernel.index)(v8235)),
                      GC_OID((*Kernel.srange)(v8235)),
                      v8241));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                    v59006 = _oid_(close_Instruction1(v60472));
                    }
                  GC_OID(v59006);}
                Result = (*Optimize.c_code)(v59006);
                }
              }
            }
        else { list * v30871;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID v8240; CL_INT CLcount;
                v_list = GC_OBJECT(list,v62612->args);
                 v30871 = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { v8240 = (*(v_list))[CLcount];
                  v_val = (*Optimize.c_type)(v8240);
                  
                  (*((list *) v30871))[CLcount] = v_val;}
                }
              GC_OBJECT(list,v30871);}
            OID  v8242 = GC_OID(restriction_I_property(v58792,v30871,CTRUE));
            show_opportunist_integer1(3);
            if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
             mtformat_module1(Optimize.it,((char*)" `GREEN note: ~S is poorly typed (~S,~S) \n"),3,list::alloc(3,_oid_(v62612),
              GC_OID((*Optimize.c_type)(v8240)),
              v58979));
            else ;if (Kernel._method == OWNER(v8242))
             Result = c_code_method_method1(OBJECT(method,v8242),GC_OBJECT(list,v62612->args),v30871);
            else Result = c_warn_Call(v62612,_oid_(v30871));
              }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_hold_property(property *v8232,OID v8240,OID v8241,ClaireBoolean *v8218) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v8235 = GC_OID(restriction_I_property(v8232,list::alloc(1,GC_OID((*Optimize.c_type)(v8240))),CTRUE));
        if ((Kernel._slot == OWNER(v8235)) && ((v8241 == CNULL) || 
            ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v8241))),OBJECT(slot,v8235)->srange) == CTRUE) && 
                (identifiable_ask_any(v8241) == CTRUE))))
         { Call_slot * v58296;
          { { Instruction *V_CC ;
              { Call_slot * v60472 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
                update_property(Kernel.selector,
                  v60472,
                  2,
                  Kernel._object,
                  v8235);
                _void_(v60472->arg = (*Optimize.c_code)(v8240,
                  _oid_(psort_any(_oid_(domain_I_restriction(OBJECT(restriction,v8235)))))));
                _void_(v60472->test = CFALSE);
                add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v60472));
                V_CC = close_Instruction1(v60472);
                }
              v58296= (Call_slot *) V_CC;}
            GC_OBJECT(Call_slot,v58296);}
          Call_method2 * v58290;
          { { Instruction *V_CC ;
              { Call_method2 * v60472 = ((Call_method2 *) GC_OBJECT(Call_method2,new_object_class(Language._Call_method2)));
                _void_(v60472->arg = ((method *) _at_property1(Core.identical_ask,Kernel._any)));
                _void_(v60472->args = list::alloc(2,_oid_(v58296),GC_OID((*Optimize.c_code)(v8241,
                  GC_OID((*Kernel.srange)(v8235))))));
                add_I_property(Kernel.instances,Language._Call_method2,11,_oid_(v60472));
                V_CC = close_Instruction1(v60472);
                }
              v58290= (Call_method2 *) V_CC;}
            GC_OBJECT(Call_method2,v58290);}
          if (v8218 == CTRUE)
           Result = (*Optimize.c_code)(_oid_(v58290));
          else { OID  v50399;
              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  _void_(v60472->selector = Core.NOT);
                  _void_(v60472->args = list::alloc(1,_oid_(v58290)));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                  v50399 = _oid_(close_Instruction1(v60472));
                  }
                GC_OID(v50399);}
              Result = (*Optimize.c_code)(v50399);
              }
            }
        else { list * v8228 = list::alloc(2,_oid_(Kernel._any),_oid_(Kernel._any));
            { list * v51360;
              { OID v_bag;
                GC_ANY(v51360= list::empty(Kernel.emptySet));
                { { OID  v52321;
                    { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        _void_(v60472->selector = Kernel.get);
                        _void_(v60472->args = list::alloc(2,_oid_(v8232),v8240));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                        v52321 = _oid_(close_Instruction1(v60472));
                        }
                      GC_OID(v52321);}
                    v_bag = (*Optimize.c_code)(v52321,
                      _oid_(Kernel._any));
                    }
                  GC_OID(v_bag);}
                ((list *) v51360)->addFast((OID)v_bag);
                ((list *) v51360)->addFast((OID)GC_OID((*Optimize.c_code)(v8241,
                  _oid_(Kernel._any))));}
              Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property2(((v8218 == CTRUE) ?
                Kernel._equal :
                Core._I_equal ),v8228))),v51360,v8228);
              }
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_add_Call(Call *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { property * v8232 = OBJECT(property,(*(v62612->args))[1]);
        OID  v8240 = GC_OID((*(v62612->args))[2]);
        OID  v8241 = GC_OID((*(v62612->args))[3]);
        ClaireObject * v8235 = GC_OBJECT(ClaireObject,_at_property1(v8232,class_I_type(GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v8240)))))));
        _void_(Optimize.OPT->use_update = CTRUE);
        if ((Kernel._slot == v8235->isa) && ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v8241))),GC_OBJECT(ClaireType,member_type(CLREAD(restriction,v8235,range)))) == CTRUE) || 
            ((CL_INT)4 <= (CL_INT)Optimize.compiler->safety)))
         { if (Update_ask_relation2(v8232,v62612->selector) == CTRUE)
           { OID  v58882 = GC_OID((*Optimize.c_code)(v8240,
              _oid_(psort_any(_oid_(domain_I_restriction(((restriction *) v8235)))))));
            Update * v60472 = ((Update *) GC_OBJECT(Update,new_object_class(Language._Update)));
            _void_(v60472->selector = _oid_(v8232));
            _void_(v60472->arg = _oid_(Kernel.add));
            { Update * v15874 = v60472; 
              OID  v15875;
              { Call_slot * v60472 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
                _void_(v60472->selector = ((slot *) v8235));
                _void_(v60472->arg = v58882);
                _void_(v60472->test = CFALSE);
                add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v60472));
                v15875 = _oid_(close_Instruction1(v60472));
                }
              _void_(v15874->var = v15875);}
            _void_(v60472->value = (*Optimize.c_code)(v8241,
              _oid_(psort_any(GC_OID(_oid_(member_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(_oid_(v8235)))))))))));
            add_I_property(Kernel.instances,Language._Update,11,_oid_(v60472));
            Result = _oid_(close_Instruction1(v60472));
            }
          else if ((designated_ask_any(v8240) == CTRUE) && 
              ((v8232->store_ask != CTRUE) && 
                  ((v62612->selector == Kernel.add_I) || 
                      (v8232->inverse == (NULL)))))
           { OID  v58882 = GC_OID((*Optimize.c_code)(v8240,
              _oid_(psort_any(_oid_(domain_I_restriction(((restriction *) v8235)))))));
            { OID  v55204;
              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  _void_(v60472->selector = Kernel.add);
                  { Call * v15877 = v60472; 
                    list * v15878;
                    { OID v_bag;
                      GC_ANY(v15878= list::empty(Kernel.emptySet));
                      { { Call_slot * v60472 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
                          _void_(v60472->selector = ((slot *) v8235));
                          _void_(v60472->arg = v58882);
                          _void_(v60472->test = CFALSE);
                          add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v60472));
                          v_bag = _oid_(close_Instruction1(v60472));
                          }
                        GC_OID(v_bag);}
                      ((list *) v15878)->addFast((OID)v_bag);
                      ((list *) v15878)->addFast((OID)v8241);}
                    _void_(v15877->args = v15878);}
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                  v55204 = _oid_(close_Instruction1(v60472));
                  }
                GC_OID(v55204);}
              Result = (*Optimize.c_code)(v55204);
              }
            }
          else { if (Optimize.compiler->optimize_ask == CTRUE)
               { notice_void();
                if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
                 mtformat_module1(Optimize.it,((char*)"`GREEN poorly typed update: ~S\n"),3,list::alloc(1,_oid_(v62612)));
                else ;}
              Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property1(Kernel.add_I,Kernel._property))),list::alloc(4,_oid_(v8232),
                v8240,
                GC_OID((*Kernel.index)(_oid_(v8235))),
                v8241),list::alloc(4,_oid_(Kernel._property),
                GC_OID((*Optimize.c_type)(v8240)),
                _oid_(Kernel._integer),
                GC_OID((*Optimize.c_type)(v8241))));
              }
            }
        else { list * v58087;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID v8240; CL_INT CLcount;
                v_list = GC_OBJECT(list,v62612->args);
                 v58087 = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { v8240 = (*(v_list))[CLcount];
                  v_val = (*Optimize.c_type)(v8240);
                  
                  (*((list *) v58087))[CLcount] = v_val;}
                }
              GC_OBJECT(list,v58087);}
            Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property1(Kernel.add,Kernel._property))),GC_OBJECT(list,v62612->args),v58087);
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_add_bag_Call(Call *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v43738 = GC_OID((*Optimize.c_type)(GC_OID((*(v62612->args))[1])));
        ClaireType * v43739 = GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(GC_OID((*(v62612->args))[2])))));
        property * v56371;
        if (((INHERIT(OBJECT(ClaireObject,v43738)->isa,Core._Param)) && 
              (_inf_equal_type(v43739,GC_OBJECT(ClaireType,member_type(OBJECT(ClaireType,v43738)))) == CTRUE)) || 
            ((CL_INT)4 <= (CL_INT)Optimize.compiler->safety))
         v56371 = Kernel.add_I;
        else v56371 = v62612->selector;
          list * v48105 = list::alloc(2,v43738,_oid_(v43739));
        OID  v8242 = GC_OID(restriction_I_property(v56371,v48105,CTRUE));
        if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
         mtformat_module1(Optimize.it,((char*)"~S: ~S -> ~S \n"),5,list::alloc(3,_oid_(v62612),
          _oid_(v48105),
          v8242));
        else ;if ((_inf_equal_type(v43739,GC_OBJECT(ClaireType,member_type(OBJECT(ClaireType,v43738)))) != CTRUE) && 
            (v62612->selector == Kernel.add))
         { warn_void();
          if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
           mtformat_module1(Optimize.it,((char*)"`BLUE the bag addition ~S is poorly typed (~S) [251] \n"),2,list::alloc(2,_oid_(v62612),GC_OID(_oid_(member_type(OBJECT(ClaireType,v43738))))));
          else ;}
        if (Kernel._method == OWNER(v8242))
         Result = c_code_method_method1(OBJECT(method,v8242),GC_OBJECT(list,v62612->args),v48105);
        else Result = c_warn_Call(v62612,_oid_(v48105));
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_delete_Call(Call *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v8232 = GC_OID((*(v62612->args))[1]);
        OID  v8240 = GC_OID((*(v62612->args))[2]);
        OID  v8241 = GC_OID((*(v62612->args))[3]);
        ClaireObject * v8235 = GC_OBJECT(ClaireObject,_at_property1(OBJECT(property,v8232),class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v8240))))));
        _void_(Optimize.OPT->use_update = CTRUE);
        if ((OBJECT(ClaireRelation,v8232)->inverse == (NULL)) && 
            ((designated_ask_any(v8240) == CTRUE) && 
              ((Kernel._slot == v8235->isa) && ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v8241))),GC_OBJECT(ClaireType,member_type(CLREAD(restriction,v8235,range)))) == CTRUE) || 
                  ((CL_INT)4 <= (CL_INT)Optimize.compiler->safety)))))
         { OID  v58882 = GC_OID((*Optimize.c_code)(v8240,
            _oid_(psort_any(_oid_(domain_I_restriction(((restriction *) v8235)))))));
          { OID  v59048;
            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(v60472->selector = Kernel._delete);
                { Call * v15902 = v60472; 
                  list * v15903;
                  { OID v_bag;
                    GC_ANY(v15903= list::empty(Kernel.emptySet));
                    { { Call_slot * v60472 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
                        _void_(v60472->selector = ((slot *) v8235));
                        _void_(v60472->arg = v58882);
                        _void_(v60472->test = CFALSE);
                        add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v60472));
                        v_bag = _oid_(close_Instruction1(v60472));
                        }
                      GC_OID(v_bag);}
                    ((list *) v15903)->addFast((OID)v_bag);
                    ((list *) v15903)->addFast((OID)v8241);}
                  _void_(v15902->args = v15903);}
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v59048 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v59048);}
            Result = (*Optimize.c_code)(v59048);
            }
          }
        else { list * v16576;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID v8240; CL_INT CLcount;
                v_list = GC_OBJECT(list,v62612->args);
                 v16576 = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { v8240 = (*(v_list))[CLcount];
                  v_val = (*Optimize.c_type)(v8240);
                  
                  (*((list *) v16576))[CLcount] = v_val;}
                }
              GC_OBJECT(list,v16576);}
            Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property1(Kernel._delete,Kernel._property))),GC_OBJECT(list,v62612->args),v16576);
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_not_Select(Select *v8240) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v17537;
        { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            _void_(v60472->selector = Core.NOT);
            { Call * v15906 = v60472; 
              list * v15907;
              { OID v_bag;
                GC_ANY(v15907= list::empty(Kernel.emptySet));
                { { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                    _void_(v60472->var = v8240->var);
                    _void_(v60472->set_arg = v8240->set_arg);
                    { Iteration * v15908 = v60472; 
                      OID  v15909;
                      { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                        _void_(v60472->test = v8240->arg);
                        { If * v15910 = v60472; 
                          OID  v15911;
                          { Return * v60472 = ((Return *) GC_OBJECT(Return,new_object_class(Language._Return)));
                            _void_(v60472->arg = Kernel.ctrue);
                            add_I_property(Kernel.instances,Language._Return,11,_oid_(v60472));
                            v15911 = _oid_(close_Instruction1(v60472));
                            }
                          _void_(v15910->arg = v15911);}
                        _void_(v60472->other = CNULL);
                        add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                        v15909 = _oid_(close_Instruction1(v60472));
                        }
                      _void_(v15908->arg = v15909);}
                    add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                    v_bag = _oid_(close_Instruction1(v60472));
                    }
                  GC_OID(v_bag);}
                ((list *) v15907)->addFast((OID)v_bag);}
              _void_(v15906->args = v15907);}
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
            v17537 = _oid_(close_Instruction1(v60472));
            }
          GC_OID(v17537);}
        Result = (*Optimize.c_code)(v17537);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_belong_Call(Call *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v8240 = GC_OID((*(v62612->args))[1]);
        OID  v8241 = GC_OID((*(v62612->args))[2]);
        list * v30871 = list::alloc(2,GC_OID((*Optimize.c_type)(v8241)),GC_OID((*Optimize.c_type)(v8240)));
        if (Kernel._set == OWNER(v8241))
         { Or * v60472 = ((Or *) GC_OBJECT(Or,new_object_class(Language._Or)));
          { Or * v15933 = v60472; 
            list * v15934;
            { list * v25211 = list::empty(Kernel.emptySet);
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(v8242);
                bag *v8242_support;
                v8242_support = GC_OBJECT(bag,enumerate_any(v8241));
                for (START(v8242_support); NEXT(v8242);)
                { GC_LOOP;
                  { OID  v46367;
                    { { OID  v47328;
                        { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                            _void_(v60472->selector = Kernel._equal);
                            _void_(v60472->args = list::alloc(2,v8240,v8242));
                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                            v47328 = _oid_(close_Instruction1(v60472));
                            }
                          GC_OID(v47328);}
                        v46367 = (*Optimize.c_code)(v47328,
                          _oid_(Kernel._any));
                        }
                      GC_OID(v46367);}
                    v25211->addFast((OID)v46367);
                    }
                  GC_UNLOOP; POP_SIGNAL;}
                }
              v15934 = GC_OBJECT(list,v25211);
              }
            _void_(v15933->args = v15934);}
          add_I_property(Kernel.instances,Language._Or,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        else if (_inf_equal_type(OBJECT(ClaireType,(*(v30871))[1]),Kernel._list) == CTRUE)
         Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property2(Kernel.contain_ask,GC_OBJECT(list,list::alloc(2,_oid_(Kernel._list),_oid_(Kernel._any)))))),GC_OBJECT(list,list::alloc(2,v8241,v8240)),v30871);
        else if (_inf_equal_type(OBJECT(ClaireType,(*(v30871))[1]),Kernel._set) == CTRUE)
         Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property2(Kernel.contain_ask,GC_OBJECT(list,list::alloc(2,_oid_(Kernel._set),_oid_(Kernel._any)))))),GC_OBJECT(list,list::alloc(2,v8241,v8240)),v30871);
        else if (v8241 == _oid_(Kernel._object))
         Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property2(Kernel._Z,GC_OBJECT(list,list::alloc(2,_oid_(Kernel._any),_oid_(Kernel._class)))))),GC_OBJECT(list,list::alloc(2,v8240,v8241)),GC_OBJECT(list,list::alloc(2,_oid_(Kernel._any),_oid_(Kernel._class))));
        else Result = (*Optimize.member_code)(v8241,
            v8240);
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_nth_Call(Call *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { list * v8228 = GC_OBJECT(list,v62612->args);
        OID  v8240 = (*(v8228))[1];
        property * v8232 = v62612->selector;
        OID  v8236 = GC_OID((*Optimize.c_type)(v8240));
        ClaireType * v58607 = GC_OBJECT(ClaireType,member_type(OBJECT(ClaireType,v8236)));
        OID  v8234;
        { { list * v48289;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID v8237; CL_INT CLcount;
                v_list = v8228;
                 v48289 = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { v8237 = (*(v_list))[CLcount];
                  v_val = (*Optimize.c_type)(v8237);
                  
                  (*((list *) v48289))[CLcount] = v_val;}
                }
              GC_OBJECT(list,v48289);}
            v8234 = restriction_I_property(v8232,v48289,CTRUE);
            }
          GC_OID(v8234);}
        if (contain_ask_set(Optimize.OPT->to_remove,v8240) == CTRUE)
         Result = Core.nil->value;
        else if (((INHERIT(OWNER(v8240),Kernel._table)) && (INHERIT(OWNER(OBJECT(table,v8240)->params),Kernel._integer))) && 
            ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)((*(v8228))[2]))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.domain)(v8240)))) == CTRUE) || 
                ((v8232 == Kernel.nth) && 
                    ((CL_INT)Optimize.compiler->safety > (CL_INT)2))))
         { Call_table * v60472 = ((Call_table *) GC_OBJECT(Call_table,new_object_class(Language._Call_table)));
          update_property(Kernel.selector,
            v60472,
            2,
            Kernel._object,
            v8240);
          _void_(v60472->arg = (*Optimize.c_code)((*(v8228))[2],
            _oid_(Kernel._integer)));
          _void_(v60472->test = not_any(_oid_(((belong_to(GC_OID((*Kernel.DEFAULT)(v8240)),GC_OID((*Kernel.range)(v8240))) == CTRUE) ? CTRUE : (((*Kernel.DEFAULT)(v8240) == ((OID)0)) ? CTRUE : ((v8232 == Kernel.get) ? CTRUE : CFALSE))))));
          add_I_property(Kernel.instances,Language._Call_table,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        else if (((INHERIT(OWNER(v8240),Kernel._table)) && (INHERIT(OWNER(OBJECT(table,v8240)->params),Kernel._list))) && 
            ((v8228->length == 3) && 
              ((_inf_equal_type(GC_OBJECT(tuple,tuple_I_list(list::alloc(2,GC_OID((*Optimize.c_type)((*(v8228))[2])),GC_OID((*Optimize.c_type)((*(v8228))[3]))))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.domain)(v8240)))) == CTRUE) || 
                  ((CL_INT)Optimize.compiler->safety > (CL_INT)2))))
         { Call_table * v60472 = ((Call_table *) GC_OBJECT(Call_table,new_object_class(Language._Call_table)));
          update_property(Kernel.selector,
            v60472,
            2,
            Kernel._object,
            v8240);
          { Call_table * v15938 = v60472; 
            OID  v15939;
            { List * v60472 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
              _void_(v60472->args = list::alloc(2,GC_OID((*Optimize.c_code)((*(v8228))[2],
                _oid_(Kernel._integer))),GC_OID((*Optimize.c_code)((*(v8228))[3],
                _oid_(Kernel._integer)))));
              add_I_property(Kernel.instances,Language._List,11,_oid_(v60472));
              v15939 = _oid_(close_Instruction1(v60472));
              }
            _void_(v15938->arg = v15939);}
          _void_(v60472->test = not_any(_oid_(((belong_to(GC_OID((*Kernel.DEFAULT)(v8240)),GC_OID((*Kernel.range)(v8240))) == CTRUE) ? CTRUE : (((*Kernel.DEFAULT)(v8240) == ((OID)0)) ? CTRUE : ((v8232 == Kernel.get) ? CTRUE : CFALSE))))));
          add_I_property(Kernel.instances,Language._Call_table,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        else if ((_inf_equal_type(OBJECT(ClaireType,v8236),Kernel._array) == CTRUE) && 
            (((v8232 == Kernel.nth_get) || 
                ((CL_INT)Optimize.compiler->safety > (CL_INT)2)) && 
              ((_inf_equal_type(v58607,Kernel._float) == CTRUE) || 
                  (equal(_oid_(_exp_type(v58607,Kernel._float)),_oid_(Kernel.emptySet)) == CTRUE))))
         { Call_array * v60472 = ((Call_array *) GC_OBJECT(Call_array,new_object_class(Language._Call_array)));
          _void_(v60472->selector = (*Optimize.c_code)(v8240,
            _oid_(Kernel._array)));
          _void_(v60472->arg = (*Optimize.c_code)((*(v8228))[2],
            _oid_(Kernel._integer)));
          _void_(v60472->test = _oid_(v58607));
          add_I_property(Kernel.instances,Language._Call_array,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        else if (Kernel._method == OWNER(v8234))
         { if ((Optimize.compiler->optimize_ask == CTRUE) && 
              ((_inf_equal_type(OBJECT(ClaireType,v8236),Kernel._array) == CTRUE) || 
                  (_inf_equal_type(OBJECT(ClaireType,v8236),Kernel._table) == CTRUE)))
           { notice_void();
            if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
             mtformat_module1(Optimize.it,((char*)"`GREEN poorly typed call: ~S\n"),3,list::alloc(1,_oid_(v62612)));
            else ;}
          { list * v51172;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID v8240; CL_INT CLcount;
                v_list = GC_OBJECT(list,v62612->args);
                 v51172 = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { v8240 = (*(v_list))[CLcount];
                  v_val = (*Optimize.c_type)(v8240);
                  
                  (*((list *) v51172))[CLcount] = v_val;}
                }
              GC_OBJECT(list,v51172);}
            Result = c_code_method_method1(OBJECT(method,v8234),GC_OBJECT(list,v62612->args),v51172);
            }
          }
        else { list * v52133;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID v8240; CL_INT CLcount;
                v_list = GC_OBJECT(list,v62612->args);
                 v52133 = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { v8240 = (*(v_list))[CLcount];
                  v_val = (*Optimize.c_type)(v8240);
                  
                  (*((list *) v52133))[CLcount] = v_val;}
                }
              GC_OBJECT(list,v52133);}
            Result = c_warn_property(v8232,GC_OBJECT(list,v62612->args),v52133);
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_table_Call(Call *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { property * v58789 = v62612->selector;
        table * v8232 = GC_OBJECT(table,OBJECT(table,(*(v62612->args))[1]));
        OID  v8240 = GC_OID((*(v62612->args))[2]);
        OID  v8241 = GC_OID((*(v62612->args))[3]);
        if (contain_ask_set(Optimize.OPT->to_remove,_oid_(v8232)) == CTRUE)
         Result = Core.nil->value;
        else if ((v58789 == Kernel.put) || 
            (((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v8240))),v8232->domain) == CTRUE) || 
                  ((CL_INT)5 <= (CL_INT)Optimize.compiler->safety)) && 
                ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v8241))),v8232->range) == CTRUE) || 
                    ((CL_INT)4 <= (CL_INT)Optimize.compiler->safety))))
         { if ((Update_ask_relation(v8232,v8240,v8241) == CTRUE) && 
              ((INHERIT(OWNER(v8232->params),Kernel._list)) || 
                  (INHERIT(OWNER(v8232->params),Kernel._integer))))
           { OID  v56379 = GC_OID((*Optimize.c_code)(v8240,
              _oid_(Kernel._any)));
            OID  v56380 = GC_OID((*Optimize.c_code)(v8241,
              _oid_(Kernel._any)));
            Update * v60472 = ((Update *) GC_OBJECT(Update,new_object_class(Language._Update)));
            _void_(v60472->selector = _oid_(v8232));
            _void_(v60472->value = v56380);
            { Update * v15942 = v60472; 
              OID  v15964;
              if (v58789 == Kernel.put)
               v15964 = _oid_(Kernel.put);
              else v15964 = v56379;
                _void_(v15942->arg = v15964);}
            { Update * v15965 = v60472; 
              OID  v15966;
              { Call_table * v60472 = ((Call_table *) GC_OBJECT(Call_table,new_object_class(Language._Call_table)));
                _void_(v60472->selector = v8232);
                _void_(v60472->arg = v56379);
                _void_(v60472->test = CFALSE);
                add_I_property(Kernel.instances,Language._Call_table,11,_oid_(v60472));
                v15966 = _oid_(close_Instruction1(v60472));
                }
              _void_(v15965->var = v15966);}
            add_I_property(Kernel.instances,Language._Update,11,_oid_(v60472));
            Result = _oid_(close_Instruction1(v60472));
            }
          else if ((v58789 == Kernel.put) || 
              ((v8232->inverse == (NULL)) && 
                  (v8232->if_write == CNULL)))
           { if (Optimize.compiler->optimize_ask == CTRUE)
             { notice_void();
              if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
               mtformat_module1(Optimize.it,((char*)"`GREEN poorly typed update: ~S\n"),3,list::alloc(1,_oid_(v62612)));
              else ;}
            Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property1(Kernel.put,Kernel._table))),GC_OBJECT(list,v62612->args),list::alloc(3,_oid_(Kernel._table),
              _oid_(Kernel._any),
              _oid_(Kernel._any)));
            }
          else Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property1(Kernel.nth_put,Kernel._table))),GC_OBJECT(list,v62612->args),list::alloc(3,_oid_(Kernel._table),
              _oid_(Kernel._any),
              _oid_(Kernel._any)));
            }
        else Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property1(Kernel.nth_equal,Kernel._table))),GC_OBJECT(list,v62612->args),list::alloc(3,_oid_(Kernel._table),
            _oid_(Kernel._any),
            _oid_(Kernel._any)));
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_array_Call(Call *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { property * v58789 = v62612->selector;
        OID  v8232 = GC_OID((*(v62612->args))[1]);
        OID  v58821 = GC_OID((*Optimize.c_type)(v8232));
        ClaireType * v58607 = GC_OBJECT(ClaireType,member_type(OBJECT(ClaireType,v58821)));
        OID  v8240 = GC_OID((*(v62612->args))[2]);
        OID  v8241 = GC_OID((*(v62612->args))[3]);
        ClaireBoolean * v43486 = ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v8241))),GC_OBJECT(ClaireType,member_type(OBJECT(ClaireType,v58821)))) == CTRUE) ? CTRUE : (((CL_INT)4 <= (CL_INT)Optimize.compiler->safety) ? CTRUE : CFALSE));
        if (((v58789 == Kernel.nth_put) || 
              (v43486 == CTRUE)) && 
            ((_inf_equal_type(v58607,Kernel._float) == CTRUE) || 
                (equal(_oid_(_exp_type(v58607,Kernel._float)),_oid_(Kernel.emptySet)) == CTRUE)))
         { OID  v56379 = GC_OID((*Optimize.c_code)(v8240,
            _oid_(Kernel._integer)));
          OID  v56380;
          { { OID  v11584;
              if (_inf_equal_type(v58607,Kernel._float) == CTRUE)
               v11584 = _oid_(Kernel._float);
              else v11584 = _oid_(Kernel._any);
                v56380 = (*Optimize.c_code)(v8241,
                v11584);
              }
            GC_OID(v56380);}
          Update * v60472 = ((Update *) GC_OBJECT(Update,new_object_class(Language._Update)));
          _void_(v60472->selector = v8232);
          _void_(v60472->value = v56380);
          _void_(v60472->arg = _oid_(Kernel.put));
          { Update * v15968 = v60472; 
            OID  v15969;
            { Call_array * v60472 = ((Call_array *) GC_OBJECT(Call_array,new_object_class(Language._Call_array)));
              _void_(v60472->selector = (*Optimize.c_code)(v8232,
                _oid_(Kernel._array)));
              _void_(v60472->arg = v56379);
              _void_(v60472->test = _oid_(v58607));
              add_I_property(Kernel.instances,Language._Call_array,11,_oid_(v60472));
              v15969 = _oid_(close_Instruction1(v60472));
              }
            _void_(v15968->var = v15969);}
          add_I_property(Kernel.instances,Language._Update,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        else { if (Optimize.compiler->optimize_ask == CTRUE)
             { notice_void();
              if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
               mtformat_module1(Optimize.it,((char*)"`GREEN poorly typed update: ~S\n"),3,list::alloc(1,_oid_(v62612)));
              else ;}
            Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property1(((v43486 == CTRUE) ?
              Kernel.nth_put :
              v58789 ),Kernel._array))),GC_OBJECT(list,v62612->args),list::alloc(3,v58821,
              _oid_(Kernel._any),
              _oid_(Kernel._any)));
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * Update_ask_relation(ClaireRelation *v8232,OID v8240,OID v8241) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = ((v8232 != Kernel.inverse) ? ((((((v8232->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE) && 
            (inherit_ask_class(OWNER(v8232->if_write),Kernel._list) != CTRUE)) || 
          ((v8232->inverse == (NULL)) && 
              (((INHERIT(v8232->isa,Kernel._table)) ? (INHERIT(OWNER(CLREAD(table,v8232,params)),Kernel._integer)) : (CTRUE == CTRUE)) && 
                ((v8232->store_ask == CTRUE) ? ((designated_ask_any(v8240) == CTRUE) && 
                    ((designated_ask_any(v8241) == CTRUE) && 
                      ((multi_ask_any(_oid_(v8232)) != CTRUE) && 
                        ((identifiable_ask_any(v8241) == CTRUE) || 
                            (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v8241))),Kernel._float) == CTRUE))))) : (CTRUE == CTRUE))))) ? CTRUE: CFALSE): CFALSE);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * Update_ask_relation2(ClaireRelation *v8232,ClaireRelation *v8235) { 
    POP_SIGNAL; return (((((v8232->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE) ? ((inherit_ask_class(OWNER(v8232->if_write),Kernel._list) != CTRUE) ? ((v8235 == Kernel.add) ? CTRUE: CFALSE): CFALSE): CFALSE));}
  

CL_EXPORT ClaireType * c_type_Update_Optimize(Update *v62612) { 
    POP_SIGNAL; return (Kernel._void);}
  

CL_EXPORT OID  c_code_method_method1(method *v62612,list *v8228,list *v30871) { 
    POP_SIGNAL; return (c_code_method_method2(v62612,v8228,v30871,c_srange_method(v62612)));}
  

CL_EXPORT OID  c_code_method_method2(method *v62612,list *v8228,list *v30871,ClaireClass *v58797) { 
    
    GC_BIND;
    { OID Result = 0;
      if ((v62612->module_I != claire.it) || 
          (((CL_INT)Optimize.compiler->safety > (CL_INT)4) || 
            (((v62612->functional == (NULL)) ? CTRUE : CFALSE) != CTRUE)))
       { list * v58570 = v62612->domain;
        CL_INT  v8230 = v58570->length;
        if (v8230 != v8228->length)
         { list * v17349;
          { list * v53994 = list::empty(Kernel.emptySet);
            { CL_INT  v8225 = 1;
              CL_INT  v15970 = ((CL_INT)v8230-(CL_INT)1);
              { CL_INT loop_handle = ClEnv->cHandle;
                while (((CL_INT)v8225 <= (CL_INT)v15970))
                { v53994->addFast((OID)(*(v8228))[v8225]);
                  ++v8225;
                  POP_SIGNAL;}
                }
              }
            v17349 = GC_OBJECT(list,v53994);
            }
          OID  v38491;
          { list * v14487;{ list * v53994 = list::empty(Kernel.emptySet);
              { CL_INT  v8225 = v8230;
                CL_INT  v15971 = v8228->length;
                { CL_INT loop_handle = ClEnv->cHandle;
                  while (((CL_INT)v8225 <= (CL_INT)v15971))
                  { v53994->addFast((OID)(*(v8228))[v8225]);
                    ++v8225;
                    POP_SIGNAL;}
                  }
                }
              v14487 = GC_OBJECT(list,v53994);
              }
            
            v38491=_oid_(v14487);}
          v8228 = v17349->addFast((OID)v38491);
          }
        if ((v62612->inline_ask == CTRUE) && 
            (c_inline_ask_method(v62612,v8228) == CTRUE))
         Result = c_inline_method1(v62612,v8228,v58797);
        else { ClaireBoolean * v8218 = Optimize.OPT->allocation;
            OID  v8240 = Core.nil->value;
            _void_(Optimize.OPT->allocation = CFALSE);
            { { list * v40413;
                { list * v53994 = list::empty(Kernel.emptySet);
                  { CL_INT  v8225 = 1;
                    CL_INT  v15972 = v8230;
                    { CL_INT loop_handle = ClEnv->cHandle;
                      OID gc_local;
                      while (((CL_INT)v8225 <= (CL_INT)v15972))
                      { GC_LOOP;
                        v53994->addFast((OID)GC_OID(c_strict_code_any((*(v8228))[v8225],psort_any((*(v58570))[v8225]))));
                        ++v8225;
                        GC_UNLOOP;POP_SIGNAL;}
                      }
                    }
                  v40413 = GC_OBJECT(list,v53994);
                  }
                v8240 = Call_method_I_method(v62612,v40413);
                }
              GC_OID(v8240);}
            if (Optimize.OPT->allocation != CTRUE)
             _void_(Optimize.OPT->allocation = v8218);
            Result = v8240;
            }
          }
      else { if (Optimize.compiler->optimize_ask == CTRUE)
           { notice_void();
            if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
             mtformat_module1(Optimize.it,((char*)"`GREEN poorly typed update: ~S\n"),3,GC_OBJECT(list,list::alloc(1,_oid_(v62612))));
            else ;}
          Result = _oid_(open_message_property(v62612->selector,v8228));
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  Call_method_I_method(method *v62612,list *v38730) { 
    
    GC_BIND;
    if (BCONTAIN(status_I_restriction(v62612),((CL_INT)(OID)(1))))
     { _void_(Optimize.OPT->allocation = CTRUE);
      if (nth_integer(v62612->status,((CL_INT)(OID)(6))) != CTRUE)
       { { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v8240; CL_INT CLcount;
          v_list = v38730;
           v38730 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v8240 = (*(v_list))[CLcount];
            v_val = c_gc_I_any1(v8240);
            
            (*((list *) v38730))[CLcount] = v_val;}
          }
        GC_OBJECT(list,v38730);}
      }
    else { ClaireBoolean * g1143I;
      { ClaireBoolean *v_and;
        { v_and = Optimize.OPT->allocation;
          if (v_and == CFALSE) g1143I =CFALSE; 
          else { { CL_INT  v42335;
              { list * v43296;
                { bag * v9108 = v38730;
                  list * v26303 = ((list *) empty_bag(v9108));
                  { CL_INT loop_handle = ClEnv->cHandle;
                    ITERATE(v8240);
                    for (START(v9108); NEXT(v8240);)
                    if ((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v8240))) == CTRUE)
                     v26303->addFast((OID)v8240);
                    }
                  v43296 = GC_OBJECT(list,v26303);
                  }
                v42335 = v43296->length;
                }
              v_and = (((CL_INT)v42335 > (CL_INT)1) ? CTRUE : CFALSE);
              }
            if (v_and == CFALSE) g1143I =CFALSE; 
            else g1143I = CTRUE;}
          }
        }
      
      if (g1143I == CTRUE) { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID v8240; CL_INT CLcount;
            v_list = v38730;
             v38730 = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { v8240 = (*(v_list))[CLcount];
              v_val = c_gc_I_any1(v8240);
              
              (*((list *) v38730))[CLcount] = v_val;}
            }
          GC_OBJECT(list,v38730);}
        }
    if (BCONTAIN(v62612->status,((CL_INT)(OID)(2))))
     _void_(Optimize.OPT->use_nth_equal = CTRUE);
    if (BCONTAIN(v62612->status,((CL_INT)(OID)(3))))
     _void_(Optimize.OPT->use_update = CTRUE);
    if (legal_ask_module(v62612->module_I,_oid_(v62612)) != CTRUE)
     { if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
       mtformat_module1(Optimize.it,((char*)"in call ~S~S\n"),0,list::alloc(2,_oid_(v62612->selector),_oid_(v38730)));
      else ;}
    { OID Result = 0;
      if (v38730->length == 1)
       { Call_method1 * v60472 = ((Call_method1 *) GC_OBJECT(Call_method1,new_object_class(Language._Call_method1)));
        _void_(v60472->arg = v62612);
        _void_(v60472->args = v38730);
        add_I_property(Kernel.instances,Language._Call_method1,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      else if (v38730->length == 2)
       { Call_method2 * v60472 = ((Call_method2 *) GC_OBJECT(Call_method2,new_object_class(Language._Call_method2)));
        _void_(v60472->arg = v62612);
        _void_(v60472->args = v38730);
        add_I_property(Kernel.instances,Language._Call_method2,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      else { Call_method * v60472 = ((Call_method *) GC_OBJECT(Call_method,new_object_class(Language._Call_method)));
          _void_(v60472->arg = v62612);
          _void_(v60472->args = v38730);
          add_I_property(Kernel.instances,Language._Call_method,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Call_method_Optimize(Call_method *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { list * v44257;
        { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID v8240; CL_INT CLcount;
            v_list = GC_OBJECT(list,v62612->args);
             v44257 = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { v8240 = (*(v_list))[CLcount];
              v_val = (*Optimize.c_type)(v8240);
              
              (*((list *) v44257))[CLcount] = v_val;}
            }
          GC_OBJECT(list,v44257);}
        Result = use_range_method(v62612->arg,v44257);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Call_method_Optimize(Call_method *v62612) { 
    POP_SIGNAL; return (_oid_(v62612));}
  

CL_EXPORT ClaireBoolean * c_gc_ask_Call_method(Call_method *v62612) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      { method * v8229 = v62612->arg;
        { ClaireBoolean *v_and;
          { v_and = not_any(_oid_((INHERIT(v8229->range->isa,Kernel._class) ?
             (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v8229->range))) : 
             (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(v8229->range))))));
            if (v_and == CFALSE) Result =CFALSE; 
            else { v_and = ((v8229->range != Kernel._float) ? CTRUE : CFALSE);
              if (v_and == CFALSE) Result =CFALSE; 
              else { v_and = ((nth_integer(status_I_restriction(v8229),((CL_INT)(OID)(5))) != CTRUE) ? CTRUE : ((((_inf_equal_type(v8229->range,Kernel._bag) == CTRUE) ? ((Optimize.OPT->loop_gc == CTRUE) ? CTRUE: CFALSE): CFALSE) != CTRUE) ? CTRUE : CFALSE));
                if (v_and == CFALSE) Result =CFALSE; 
                else { { ClaireBoolean *v_or;
                    { v_or = nth_integer(status_I_restriction(v8229),((CL_INT)(OID)(1)));
                      if (v_or == CTRUE) v_and =CTRUE; 
                      else { { ClaireBoolean *v_and;
                          { v_and = nth_integer(v8229->status,((CL_INT)(OID)(4)));
                            if (v_and == CFALSE) v_or =CFALSE; 
                            else { { OID  v45218;
                                { CL_INT loop_handle = ClEnv->cHandle;
                                  ITERATE(v8240);
                                  v45218= Kernel.cfalse;
                                  bag *v8240_support;
                                  v8240_support = GC_OBJECT(list,v62612->args);
                                  for (START(v8240_support); NEXT(v8240);)
                                  if ((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v8240))) == CTRUE)
                                   { v45218 = Kernel.ctrue;
                                    ClEnv->cHandle = loop_handle;break;}
                                  }
                                v_and = boolean_I_any(v45218);
                                }
                              if (v_and == CFALSE) v_or =CFALSE; 
                              else v_or = CTRUE;}
                            }
                          }
                        if (v_or == CTRUE) v_and =CTRUE; 
                        else v_and = CFALSE;}
                      }
                    }
                  if (v_and == CFALSE) Result =CFALSE; 
                  else Result = CTRUE;}
                }
              }
            }
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireFunction * functional_I_method_Optimize(method *v62612) { 
    
    GC_BIND;
    { ClaireFunction *Result ;
      { OID  v8222 = GC_OID(get_property(Kernel.functional,v62612));
        property * v8232 = v62612->selector;
        Result = ((INHERIT(OWNER(v8222),Kernel._function)) ?
          OBJECT(ClaireFunction,v8222) :
          make_function_string(string_v((*Optimize.function_name)(_oid_(v8232),
            _oid_(v62612->domain),
            v8222))) );
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  nth_type_check_type(ClaireType *v58816,ClaireType *v58813,ClaireType *v58828) { 
    
    GC_BIND;
    if (_inf_equal_type(v58828,GC_OBJECT(ClaireType,member_type(v58816))) != CTRUE)
     { warn_void();
      if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
       mtformat_module1(Optimize.it,((char*)"`BLUE unsafe update on bag: type ~S into ~S [252]\n"),2,list::alloc(2,_oid_(v58828),_oid_(v58816)));
      else ;}
    { OID Result = 0;
      Result = _oid_(v58828);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * c_inline_ask_method(method *v62612,list *v8228) { 
    if (((OBJECT(ClaireBoolean,Language.DEBUG_ask->value)) == CTRUE) && 
        (((v62612->module_I == Core.it) ? CTRUE : ((v62612->module_I == Language.it) ? CTRUE : ((v62612->module_I == Reader.it) ? CTRUE : CFALSE))) != CTRUE)) 
    { { ClaireBoolean *Result ;
        Result = CFALSE;
        return (Result);}
       }
    else{ 
      GC_BIND;
      { ClaireBoolean *Result ;
        { lambda * v8222 = GC_OBJECT(lambda,v62612->formula);
          list * v58557 = GC_OBJECT(list,v8222->vars);
          OID  v8240 = GC_OID(v8222->body);
          CL_INT  v8230 = 1;
          { OID  v46179;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(v8238);
              v46179= Kernel.cfalse;
              bag *v8238_support;
              v8238_support = GC_OBJECT(list,v8222->vars);
              for (START(v8238_support); NEXT(v8238);)
              if (((CL_INT)((CL_INT)(*Kernel.occurrence)(v8240,
                  v8238)) > (CL_INT)1) && 
                  ((designated_ask_any((*(v8228))[v8230]) != CTRUE) && 
                    (inherit_ask_class(owner_any((*Kernel.range)(v8238)),Optimize._Pattern) != CTRUE)))
               { v46179 = Kernel.ctrue;
                ClEnv->cHandle = loop_handle;break;}
              else ++v8230;
                }
            Result = not_any(v46179);
            }
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
      }
    }
  

CL_EXPORT OID  inline_optimize_ask_Call(Call *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { list * v8228 = GC_OBJECT(list,v62612->args);
        OID  v8229;
        { { list * v47140;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID v8240; CL_INT CLcount;
                v_list = v8228;
                 v47140 = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { v8240 = (*(v_list))[CLcount];
                  v_val = _oid_(set::alloc(1,v8240));
                  
                  (*((list *) v47140))[CLcount] = v_val;}
                }
              GC_OBJECT(list,v47140);}
            v8229 = restriction_I_property(v62612->selector,v47140,CTRUE);
            }
          GC_OID(v8229);}
        if (Kernel._method == OWNER(v8229))
         { { ClaireBoolean * g1150I;
            { ClaireBoolean *v_and;
              { v_and = OBJECT(method,v8229)->inline_ask;
                if (v_and == CFALSE) g1150I =CFALSE; 
                else { { OID  v3707;
                    { CL_INT loop_handle = ClEnv->cHandle;
                      ITERATE(v8235);
                      v3707= Kernel.cfalse;
                      for (START(OBJECT(restriction,v8229)->domain); NEXT(v8235);)
                      if (INHERIT(OBJECT(ClaireObject,v8235)->isa,Optimize._Pattern))
                       { v3707 = Kernel.ctrue;
                        ClEnv->cHandle = loop_handle;break;}
                      }
                    v_and = boolean_I_any(v3707);
                    }
                  if (v_and == CFALSE) g1150I =CFALSE; 
                  else { v_and = c_inline_ask_method(OBJECT(method,v8229),v8228);
                    if (v_and == CFALSE) g1150I =CFALSE; 
                    else g1150I = CTRUE;}
                  }
                }
              }
            
            if (g1150I == CTRUE) Result = v8229;
              else Result = Kernel.cfalse;
            }
          }
        else Result = Kernel.cfalse;
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  



/***** CLAIRE Compilation of file ./compile/ocontrol.cl 
         [version 3.5.0 / safety 5] *****/

CL_EXPORT ClaireType * c_type_Assign_Optimize(Assign *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = OBJECT(ClaireType,(*Optimize.c_type)(v62612->arg));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Assign_Optimize(Assign *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v8238 = GC_OID(v62612->var);
        OID  v8240 = GC_OID(v62612->arg);
        ClaireType * v30871 = GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v8240))));
        if (inherit_ask_class(OWNER(v8238),Language._Variable) != CTRUE)
         (*Optimize.Cerror)(_string_(((char*)"[213] ~S is not a variable")),
          v8238);
        if (_oid_((ClaireObject *) Core._inf_equalt->fcall(((CL_INT) v30871),((CL_INT) OBJECT(ClaireObject,GC_OID((*Kernel.range)(v8238)))))) != Kernel.ctrue)
         v8240= (GC_OID((*Optimize.c_warn)(GC_OID(v62612->var),
          v8240,
          _oid_(v30871))));
        { OID  v29017 = GC_OID(c_gc_I_any2(GC_OID(c_strict_code_any(v8240,psort_any(GC_OID((*Kernel.range)(v8238))))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel._exp)(GC_OID((*Kernel.range)(v8238)),
            _oid_(v30871))))));
          gc_register_Variable2(OBJECT(Variable,v8238),v29017);
          { Assign * v60472 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
            _void_(v60472->var = v8238);
            _void_(v60472->arg = v29017);
            add_I_property(Kernel.instances,Language._Assign,11,_oid_(v60472));
            Result = _oid_(close_Instruction1(v60472));
            }
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * c_gc_ask_Assign(Assign *v62612) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v62612->arg));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Gassign_Optimize(Gassign *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = OBJECT(ClaireType,(*Optimize.c_type)(v62612->arg));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Gassign_Optimize(Gassign *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v56377 = GC_OID(v62612->arg);
        ClaireType * v30871 = GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v56377))));
        if (boolean_I_any(_oid_(v62612->var->range)) != CTRUE)
         (*Optimize.Cerror)(_string_(((char*)"[214] cannot assign ~S")),
          _oid_(v62612));
        if (_oid_((ClaireObject *) Core._inf_equalt->fcall(((CL_INT) v30871),((CL_INT) v62612->var->range))) != Kernel.ctrue)
         v56377= (GC_OID(c_check_any(GC_OID((*Optimize.c_code)(v56377,
          _oid_(Kernel._any))),GC_OID((*Optimize.c_code)(_oid_(v62612->var->range),
          _oid_(Kernel._type))))));
        { Gassign * v60472 = ((Gassign *) GC_OBJECT(Gassign,new_object_class(Language._Gassign)));
          store_object(v60472,
            2,
            Kernel._object,
            (*Optimize.c_code)(_oid_(v62612->var)),
            CFALSE);
          { Gassign * v16030 = v60472; 
            OID  v16031;
            if (nativeVar_ask_global_variable(v62612->var) == CTRUE)
             v16031 = c_strict_code_any(v56377,psort_any(_oid_(v62612->var->range)));
            else v16031 = (*Optimize.c_code)(v56377,
                _oid_(Kernel._any));
              _void_(v16030->arg = v16031);}
          add_I_property(Kernel.instances,Language._Gassign,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * c_gc_ask_Gassign(Gassign *v62612) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v62612->arg));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_And_Optimize(And *v62612) { 
    POP_SIGNAL; return (Kernel._boolean);}
  

CL_EXPORT OID  c_code_And_Optimize(And *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { And * v60472 = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
        { And * v16032 = v60472; 
          list * v16033;
          { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID v8240; CL_INT CLcount;
            v_list = GC_OBJECT(list,v62612->args);
             v16033 = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { v8240 = (*(v_list))[CLcount];
              { if ((*Optimize.c_type)(v8240) == _oid_(Kernel._void))
                 (*Optimize.Cerror)(_string_(((char*)"[206] void ~S in ~S")),
                  v8240,
                  _oid_(v62612));
                v_val = c_boolean_any(v8240);
                }
              
              (*((list *) v16033))[CLcount] = v_val;}
            }
          _void_(v16032->args = v16033);}
        add_I_property(Kernel.instances,Language._And,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Or_Optimize(Or *v62612) { 
    POP_SIGNAL; return (Kernel._boolean);}
  

CL_EXPORT OID  c_code_Or_Optimize(Or *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { Or * v60472 = ((Or *) GC_OBJECT(Or,new_object_class(Language._Or)));
        { Or * v16034 = v60472; 
          list * v16035;
          { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID v8240; CL_INT CLcount;
            v_list = GC_OBJECT(list,v62612->args);
             v16035 = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { v8240 = (*(v_list))[CLcount];
              { if ((*Optimize.c_type)(v8240) == _oid_(Kernel._void))
                 (*Optimize.Cerror)(_string_(((char*)"[206] void ~S in ~S")),
                  v8240,
                  _oid_(v62612));
                v_val = c_boolean_any(v8240);
                }
              
              (*((list *) v16035))[CLcount] = v_val;}
            }
          _void_(v16034->args = v16035);}
        add_I_property(Kernel.instances,Language._Or,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Quote_Optimize(Quote *v62612) { 
    POP_SIGNAL; return (OWNER(v62612->arg));}
  

CL_EXPORT void  c_code_Quote_Optimize(Quote *v62612) { 
    (*Optimize.Cerror)(_string_(((char*)"[internal] optimization of quote not implemented yet! ~S")),
      _oid_(v62612));
    POP_SIGNAL;}
  

CL_EXPORT ClaireType * c_type_to_protect_Optimize(Compile_to_protect *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = OBJECT(ClaireType,(*Optimize.c_type)(v62612->arg));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_to_protect_Optimize(Compile_to_protect *v62612) { 
    POP_SIGNAL; return (_oid_(v62612));}
  

CL_EXPORT ClaireBoolean * c_gc_ask_to_protect(Compile_to_protect *v62612) { 
    POP_SIGNAL; return (CFALSE);}
  

CL_EXPORT ClaireType * c_type_Return_Optimize(Return *v62612) { 
    POP_SIGNAL; return (Kernel._any);}
  

CL_EXPORT OID  c_code_Return_Optimize(Return *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { Return * v60472 = ((Return *) GC_OBJECT(Return,new_object_class(Language._Return)));
        _void_(v60472->arg = (*Optimize.c_code)(GC_OID(v62612->arg),
          _oid_(Kernel._any)));
        add_I_property(Kernel.instances,Language._Return,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Handle_Optimize(ClaireHandle *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = U_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->arg)))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->other)))));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Handle_Optimize(ClaireHandle *v62612,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireHandle * v8240;
        { { Instruction *V_CC ;
            { ClaireHandle * v60472 = ((ClaireHandle *) GC_OBJECT(ClaireHandle,new_object_class(Language._Handle)));
              _void_(v60472->test = _oid_(Kernel._any));
              _void_(v60472->arg = (*Optimize.c_code)(GC_OID(v62612->arg),
                _oid_(v8235)));
              _void_(v60472->other = (*Optimize.c_code)(GC_OID(v62612->other),
                _oid_(v8235)));
              add_I_property(Kernel.instances,Language._Handle,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v8240= (ClaireHandle *) V_CC;}
          GC_OBJECT(ClaireHandle,v8240);}
        if (v62612->test != _oid_(Core._contradiction))
         _void_(Optimize.OPT->allocation = CTRUE);
        _void_(v8240->test = v62612->test);
        Result = _oid_(v8240);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * c_gc_ask_Handle(ClaireHandle *v62612) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = (((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v62612->arg))) == CTRUE) ? CTRUE : (((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v62612->other))) == CTRUE) ? CTRUE : CFALSE));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Cast_Optimize(Cast *v62612) { 
    POP_SIGNAL; return (v62612->set_arg);}
  

CL_EXPORT OID  c_code_Cast2_Optimize(Cast *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireType * v8241 = GC_OBJECT(ClaireType,v62612->set_arg);
        ClaireClass * v28760 = psort_any(_oid_(v8241));
        if ((INHERIT(v8241->isa,Core._Param)) && (((CLREAD(Param,v8241,arg) == Kernel._list) || 
              (CLREAD(Param,v8241,arg) == Kernel._set)) && 
            (Kernel._set == OWNER((*(CLREAD(Param,v8241,args)))[1]))))
         { OID  v53479 = GC_OID((*(OBJECT(set,(*(CLREAD(Param,v8241,args)))[1])))[1]);
          if ((equal(_oid_(_at_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->arg)))),Kernel.of)),v53479) == CTRUE) || 
              ((CL_INT)Optimize.compiler->safety > (CL_INT)4))
           Result = (*Optimize.c_code)(GC_OID(v62612->arg),
            _oid_(v28760));
          else { OID  v10434;
              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  _void_(v60472->selector = Core.check_in);
                  _void_(v60472->args = list::alloc(3,GC_OID(v62612->arg),
                    _oid_(CLREAD(Param,v8241,arg)),
                    v53479));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                  v10434 = _oid_(close_Instruction1(v60472));
                  }
                GC_OID(v10434);}
              Result = (*Optimize.c_code)(v10434,
                _oid_(v28760));
              }
            }
        else if ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->arg)))),v8241) == CTRUE) || 
            ((CL_INT)Optimize.compiler->safety > (CL_INT)1))
         Result = (*Optimize.c_code)(GC_OID(v62612->arg),
          _oid_(v28760));
        else { OID  v11395;
            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(v60472->selector = Core.check_in);
                _void_(v60472->args = list::alloc(2,GC_OID(v62612->arg),_oid_(v8241)));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v11395 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v11395);}
            Result = (*Optimize.c_code)(v11395,
              _oid_(v28760));
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Super_Optimize(Super *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { list * v30871;
        { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID v8240; CL_INT CLcount;
            v_list = GC_OBJECT(list,v62612->args);
             v30871 = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { v8240 = (*(v_list))[CLcount];
              v_val = (*Optimize.c_type)(v8240);
              
              (*((list *) v30871))[CLcount] = v_val;}
            }
          GC_OBJECT(list,v30871);}
        property * v8235 = v62612->selector;
        ((*(v30871))[1]=GC_OID(_oid_(v62612->cast_to)));
        { OID  v51371;
          { if (v8235->open == 3)
             v51371 = Core.nil->value;
            else v51371 = restriction_I_class(class_I_type(GC_OBJECT(ClaireType,v62612->cast_to)),v8235->definition,v30871);
              GC_OID(v51371);}
          Result = ((Kernel._slot == OWNER(v51371)) ?
            OBJECT(restriction,v51371)->range :
            ((Kernel._method == OWNER(v51371)) ?
              use_range_method(OBJECT(method,v51371),v30871) :
              v8235->range ) );
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Super_Optimize(Super *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { property * v8235 = v62612->selector;
        list * v8228 = GC_OBJECT(list,v62612->args);
        list * v30871;
        { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID v8240; CL_INT CLcount;
            v_list = GC_OBJECT(list,v62612->args);
             v30871 = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { v8240 = (*(v_list))[CLcount];
              v_val = (*Optimize.c_type)(v8240);
              
              (*((list *) v30871))[CLcount] = v_val;}
            }
          GC_OBJECT(list,v30871);}
        OID  v51371;
        { if (v8235->open == 3)
           v51371 = Core.nil->value;
          else v51371 = restriction_I_class(class_I_type(GC_OBJECT(ClaireType,v62612->cast_to)),v8235->definition,v30871);
            GC_OID(v51371);}
        if (Kernel._slot == OWNER(v51371))
         { Call_slot * v60472 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
          _void_(v60472->selector = OBJECT(slot,v51371));
          _void_(v60472->arg = (*Optimize.c_code)((*(v8228))[1],
            _oid_(psort_any(_oid_(domain_I_restriction(OBJECT(restriction,v51371)))))));
          _void_(v60472->test = ((belong_to(OBJECT(slot,v51371)->DEFAULT,_oid_(OBJECT(restriction,v51371)->range)) != CTRUE) ? (((CL_INT)Optimize.compiler->safety < (CL_INT)5) ? CTRUE: CFALSE): CFALSE));
          add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        else if (Kernel._method == OWNER(v51371))
         Result = c_code_method_method1(OBJECT(method,v51371),v8228,v30871);
        else Result = c_warn_Super(v62612,_oid_(v30871));
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  self_print_Call_function2(Optimize_Call_function2 *v62612) { 
    
    GC_BIND;
    print_any(GC_OID(get_property(Kernel.arg,v62612)));
    princ_string(((char*)"("));
    princ_bag(v62612->args);
    princ_string(((char*)")"));
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT ClaireType * c_type_Call_function2_Optimize(Optimize_Call_function2 *v62612) { 
    POP_SIGNAL; return (Kernel._any);}
  

CL_EXPORT OID  c_code_Call_function2_Optimize(Optimize_Call_function2 *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { Optimize_Call_function2 * v60472 = ((Optimize_Call_function2 *) GC_OBJECT(Optimize_Call_function2,new_object_class(Optimize._Call_function2)));
        _void_(v60472->arg = v62612->arg);
        { Optimize_Call_function2 * v16057 = v60472; 
          list * v16058;
          { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID v8240; CL_INT CLcount;
            v_list = v62612->args;
             v16058 = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { v8240 = (*(v_list))[CLcount];
              v_val = (*Optimize.c_code)(v8240,
                _oid_(Kernel._any));
              
              (*((list *) v16058))[CLcount] = v_val;}
            }
          _void_(v16057->args = v16058);}
        add_I_property(Kernel.instances,Optimize._Call_function2,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Assert_Optimize(Assert *v62612) { 
    if (Optimize.OPT->online_ask == CTRUE) 
    { { OID Result = 0;
        Result = _oid_(v62612);
        return (Result);}
       }
    else{ 
      GC_BIND;
      { OID Result = 0;
        if ((Optimize.compiler->safety == 0) || 
            (Optimize.compiler->debug_ask->length != 0))
         { OID  v34459;
          { { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
              { If * v16060 = v60472; 
                OID  v16061;
                { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  _void_(v60472->selector = Core.NOT);
                  _void_(v60472->args = list::alloc(1,GC_OID((*(v62612->args))[1])));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                  v16061 = _oid_(close_Instruction1(v60472));
                  }
                _void_(v16060->test = v16061);}
              { If * v16062 = v60472; 
                OID  v16063;
                { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  _void_(v60472->selector = Core.tformat);
                  { Call * v16064 = v60472; 
                    list * v16065;
                    { OID v_bag;
                      GC_ANY(v16065= list::empty(Kernel.emptySet));
                      ((list *) v16065)->addFast((OID)_string_(((char*)"Assertion violation in ~A line ~A\n")));
                      ((list *) v16065)->addFast((OID)((OID)0));
                      { { List * v60472 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                          _void_(v60472->args = list::alloc(2,GC_OID(_string_(v62612->external)),((OID)v62612->index)));
                          add_I_property(Kernel.instances,Language._List,11,_oid_(v60472));
                          v_bag = _oid_(close_Instruction1(v60472));
                          }
                        GC_OID(v_bag);}
                      ((list *) v16065)->addFast((OID)v_bag);}
                    _void_(v16064->args = v16065);}
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                  v16063 = _oid_(close_Instruction1(v60472));
                  }
                _void_(v16062->arg = v16063);}
              _void_(v60472->other = Kernel.cfalse);
              add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
              v34459 = _oid_(close_Instruction1(v60472));
              }
            GC_OID(v34459);}
          Result = (*Optimize.c_code)(v34459,
            _oid_(Kernel._any));
          }
        else Result = Kernel.cfalse;
          GC_UNBIND; POP_SIGNAL; return (Result);}
      }
    }
  

CL_EXPORT OID  c_code_Trace_Optimize(Trace *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { list * v8217 = GC_OBJECT(list,v62612->args);
        if (Optimize.OPT->online_ask == CTRUE)
         Result = _oid_(v62612);
        else if ((v8217->length == 1) && 
            (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)((*(v8217))[1]))),Kernel._integer) == CTRUE))
         { OID  v41186;
          { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(v60472->selector = Core.write);
              _void_(v60472->args = list::alloc(3,_oid_(Kernel.verbose),
                _oid_(ClEnv),
                (*(v8217))[1]));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
              v41186 = _oid_(close_Instruction1(v60472));
              }
            GC_OID(v41186);}
          Result = (*Optimize.c_code)(v41186);
          }
        else if (((CL_INT)v8217->length > (CL_INT)1) && 
            (Kernel._string == OWNER((*(v8217))[2])))
         { OID  v62328;
          { { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
              { If * v16089 = v60472; 
                OID  v16090;
                { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  _void_(v60472->selector = Core.should_trace_ask);
                  _void_(v60472->args = list::alloc(2,_oid_(ClEnv->module_I),(*(v8217))[1]));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                  v16090 = _oid_(close_Instruction1(v60472));
                  }
                _void_(v16089->test = v16090);}
              { If * v16091 = v60472; 
                OID  v16092;
                { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  _void_(v60472->selector = Core.mtformat);
                  { Call * v16093 = v60472; 
                    list * v16094;
                    { OID v_bag;
                      GC_ANY(v16094= list::empty(Kernel.emptySet));
                      ((list *) v16094)->addFast((OID)_oid_(ClEnv->module_I));
                      ((list *) v16094)->addFast((OID)(*(v8217))[2]);
                      ((list *) v16094)->addFast((OID)(*(v8217))[1]);
                      { { List * v60472 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                          _void_(v60472->args = skip_list(((list *) copy_bag(v8217)),2));
                          add_I_property(Kernel.instances,Language._List,11,_oid_(v60472));
                          v_bag = _oid_(close_Instruction1(v60472));
                          }
                        GC_OID(v_bag);}
                      ((list *) v16094)->addFast((OID)v_bag);}
                    _void_(v16093->args = v16094);}
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                  v16092 = _oid_(close_Instruction1(v60472));
                  }
                _void_(v16091->arg = v16092);}
              add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
              _void_(v60472->other = Kernel.cfalse);
              v62328 = _oid_(close_Instruction1(v60472));
              }
            GC_OID(v62328);}
          Result = (*Optimize.c_code)(v62328,
            _oid_(Kernel._any));
          }
        else Result = Kernel.cfalse;
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Assert_Optimize(Assert *v62612) { 
    POP_SIGNAL; return (Kernel._any);}
  

CL_EXPORT ClaireType * c_type_Trace_Optimize(Trace *v62612) { 
    POP_SIGNAL; return (Kernel._any);}
  

CL_EXPORT ClaireType * c_type_Branch_Optimize(Branch *v62612) { 
    POP_SIGNAL; return (Kernel._boolean);}
  

CL_EXPORT OID  c_code_Branch_Optimize(Branch *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v3519;
        { { ClaireHandle * v60472 = ((ClaireHandle *) GC_OBJECT(ClaireHandle,new_object_class(Language._Handle)));
            { ClaireHandle * v16098 = v60472; 
              OID  v16099;
              { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                { Do * v16119 = v60472; 
                  list * v16120;
                  { OID v_bag;
                    GC_ANY(v16120= list::empty(Kernel.emptySet));
                    { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        _void_(v60472->selector = Kernel.choice);
                        _void_(v60472->args = list::alloc(1,_oid_(ClEnv)));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                        v_bag = _oid_(close_Instruction1(v60472));
                        }
                      GC_OID(v_bag);}
                    ((list *) v16120)->addFast((OID)v_bag);
                    { { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                        _void_(v60472->test = (*(v62612->args))[1]);
                        _void_(v60472->arg = Kernel.ctrue);
                        { If * v16121 = v60472; 
                          OID  v16122;
                          { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                            { Do * v16123 = v60472; 
                              list * v16124;
                              { OID v_bag;
                                GC_ANY(v16124= list::empty(Kernel.emptySet));
                                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                    _void_(v60472->selector = Kernel.backtrack);
                                    _void_(v60472->args = list::alloc(1,_oid_(ClEnv)));
                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                    v_bag = _oid_(close_Instruction1(v60472));
                                    }
                                  GC_OID(v_bag);}
                                ((list *) v16124)->addFast((OID)v_bag);
                                ((list *) v16124)->addFast((OID)Kernel.cfalse);}
                              _void_(v16123->args = v16124);}
                            add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                            v16122 = _oid_(close_Instruction1(v60472));
                            }
                          _void_(v16121->other = v16122);}
                        add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                        v_bag = _oid_(close_Instruction1(v60472));
                        }
                      GC_OID(v_bag);}
                    ((list *) v16120)->addFast((OID)v_bag);}
                  _void_(v16119->args = v16120);}
                add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                v16099 = _oid_(close_Instruction1(v60472));
                }
              _void_(v16098->arg = v16099);}
            _void_(v60472->test = _oid_(Core._contradiction));
            { ClaireHandle * v16125 = v60472; 
              OID  v16126;
              { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                { Do * v16127 = v60472; 
                  list * v16128;
                  { OID v_bag;
                    GC_ANY(v16128= list::empty(Kernel.emptySet));
                    { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        _void_(v60472->selector = Kernel.backtrack);
                        _void_(v60472->args = list::alloc(1,_oid_(ClEnv)));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                        v_bag = _oid_(close_Instruction1(v60472));
                        }
                      GC_OID(v_bag);}
                    ((list *) v16128)->addFast((OID)v_bag);
                    ((list *) v16128)->addFast((OID)Kernel.cfalse);}
                  _void_(v16127->args = v16128);}
                add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                v16126 = _oid_(close_Instruction1(v60472));
                }
              _void_(v16125->other = v16126);}
            add_I_property(Kernel.instances,Language._Handle,11,_oid_(v60472));
            v3519 = _oid_(close_Instruction1(v60472));
            }
          GC_OID(v3519);}
        Result = (*Optimize.c_code)(v3519,
          _oid_(Kernel._any));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Macro_Optimize(Macro *v62612,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      Result = (*Optimize.c_code)(GC_OID((*Language.macroexpand)(_oid_(v62612))),
        _oid_(v8235));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Macro_Optimize(Macro *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = OBJECT(ClaireType,(*Optimize.c_type)(GC_OID((*Language.macroexpand)(_oid_(v62612)))));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Printf_Optimize(Printf *v62612) { 
    POP_SIGNAL; return (Kernel._any);}
  

CL_EXPORT OID  c_code_Printf_Optimize(Printf *v62612) { 
    
    GC_RESERVE(8);  // v3.3.39 optim !
    { OID Result = 0;
      { list * v47026 = GC_OBJECT(list,v62612->args);
        list * v8234 = list::empty(Kernel._any);
        OID  v51800;
        { { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            _void_(v60472->args = v8234);
            add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
            v51800 = _oid_(close_Instruction1(v60472));
            }
          GC_OID(v51800);}
        ClaireBoolean * v45847 = ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)((*(v47026))[1]))),Kernel._port) == CTRUE) ? CTRUE : CFALSE);
        OID  v8235;
        if (v45847 == CTRUE)
         v8235 = (*(v47026))[2];
        else v8235 = (*(v47026))[1];
          if (equal(_oid_(Kernel._string),_oid_(OWNER(v8235))) != CTRUE)
         (*Optimize.Cerror)(_string_(((char*)"[209] the first argument in ~S must be a string or a port")),
          _oid_(v62612));
        else { CL_INT  v8230 = find_string2(string_v(v8235),((char*)"~"));
            ClaireBoolean * v45188 = (((CL_INT)((CL_INT)((CL_INT)((CL_INT)((CL_INT)((CL_INT)((CL_INT)((CL_INT)find_string2(string_v(v8235),((char*)"`BLACK"))+(CL_INT)find_string2(string_v(v8235),((char*)"`BLUE")))+(CL_INT)find_string2(string_v(v8235),((char*)"`MAGENTA")))+(CL_INT)find_string2(string_v(v8235),((char*)"`RED")))+(CL_INT)find_string2(string_v(v8235),((char*)"`CYAN")))+(CL_INT)find_string2(string_v(v8235),((char*)"YELLOW")))+(CL_INT)find_string2(string_v(v8235),((char*)"`WHITE")))+(CL_INT)find_string2(string_v(v8235),((char*)"`GREEN"))) > (CL_INT)0) ? CTRUE : CFALSE);
            CL_INT  v43125 = 1;
            OID  v63138 = CNULL;
            OID  v42885 = CNULL;
            OID  v54560 = CNULL;
            OID  v37688 = CNULL;
            OID  v24525 = CNULL;
            CL_INT  v58632 = ((v45847 == CTRUE) ?
              3 :
              2 );
            CL_INT  v46029 = ((CL_INT)(*Kernel.length)(v8235));
            if (v45847 == CTRUE)
             { v63138= (GC_OID(_oid_(Variable_I_symbol(gensym_void(),0,Kernel._port))));
              { { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                  store_object(v60472,
                    2,
                    Kernel._object,
                    v63138,
                    CFALSE);
                  { Let * v16150 = v60472; 
                    OID  v16151;
                    { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Kernel.use_as_output);
                      _void_(v60472->args = list::alloc(1,(*(v47026))[1]));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v16151 = _oid_(close_Instruction1(v60472));
                      }
                    _void_(v16150->value = v16151);}
                  _void_(v60472->arg = v51800);
                  add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                  v51800 = _oid_(close_Instruction1(v60472));
                  }
                GC_OID(v51800);}
              }
            if (v45188 == CTRUE)
             { v42885= (GC_OID(_oid_(Variable_I_symbol(gensym_void(),0,Kernel._integer))));
              v54560= (GC_OID(_oid_(Variable_I_symbol(gensym_void(),0,Kernel._integer))));
              v37688= (GC_OID(_oid_(Variable_I_symbol(gensym_void(),0,Kernel._integer))));
              v24525= (GC_OID(_oid_(Variable_I_symbol(gensym_void(),0,Kernel._integer))));
              { { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                  store_object(v60472,
                    2,
                    Kernel._object,
                    v42885,
                    CFALSE);
                  { Let * v16152 = v60472; 
                    OID  v16153;
                    { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Core.externC);
                      _void_(v60472->args = list::alloc(2,_string_(((char*)"current_color")),_oid_(Kernel._integer)));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v16153 = _oid_(close_Instruction1(v60472));
                      }
                    _void_(v16152->value = v16153);}
                  { Let * v16154 = v60472; 
                    OID  v16155;
                    { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                      store_object(v60472,
                        2,
                        Kernel._object,
                        v54560,
                        CFALSE);
                      { Let * v16156 = v60472; 
                        OID  v16157;
                        { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          _void_(v60472->selector = Core.externC);
                          _void_(v60472->args = list::alloc(2,_string_(((char*)"current_bold")),_oid_(Kernel._integer)));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                          v16157 = _oid_(close_Instruction1(v60472));
                          }
                        _void_(v16156->value = v16157);}
                      { Let * v16158 = v60472; 
                        OID  v16159;
                        { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                          store_object(v60472,
                            2,
                            Kernel._object,
                            v37688,
                            CFALSE);
                          _void_(v60472->value = v42885);
                          { Let * v16832 = v60472; 
                            OID  v16833;
                            { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                              store_object(v60472,
                                2,
                                Kernel._object,
                                v24525,
                                CFALSE);
                              _void_(v60472->value = v54560);
                              _void_(v60472->arg = v51800);
                              add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                              v16833 = _oid_(close_Instruction1(v60472));
                              }
                            _void_(v16832->arg = v16833);}
                          add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                          v16159 = _oid_(close_Instruction1(v60472));
                          }
                        _void_(v16158->arg = v16159);}
                      add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                      v16155 = _oid_(close_Instruction1(v60472));
                      }
                    _void_(v16154->arg = v16155);}
                  add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                  v51800 = _oid_(close_Instruction1(v60472));
                  }
                GC_OID(v51800);}
              }
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while ((((CL_INT)0 < (CL_INT)v8230) && 
                  ((CL_INT)v8230 < (CL_INT)v46029)))
              { GC_LOOP;
                { OID  v8229 = GC_OID((*Kernel.nth)(v8235,
                    ((OID)((CL_INT)v8230+(CL_INT)1))));
                  if ((CL_INT)v8230 > (CL_INT)1)
                   { if ((CL_INT)0 <= (CL_INT)((CL_INT)((CL_INT)v8230-(CL_INT)1)-(CL_INT)v43125))
                     { if (v45188 == CTRUE)
                       { { OID  v58338;
                          { { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                              { Do * v16835 = v60472; 
                                list * v16836;
                                { OID v_bag;
                                  GC_ANY(v16836= list::empty(Kernel.emptySet));
                                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                      _void_(v60472->selector = Core.set_color);
                                      _void_(v60472->args = list::alloc(2,v42885,v54560));
                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                      v_bag = _oid_(close_Instruction1(v60472));
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v16836)->addFast((OID)v_bag);
                                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                      _void_(v60472->selector = Kernel.color_princ);
                                      _void_(v60472->args = list::alloc(1,GC_OID((*Kernel.substring)(v8235,
                                        ((OID)v43125),
                                        ((OID)((CL_INT)v8230-(CL_INT)1))))));
                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                      v_bag = _oid_(close_Instruction1(v60472));
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v16836)->addFast((OID)v_bag);}
                                _void_(v16835->args = v16836);}
                              add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                              v58338 = _oid_(close_Instruction1(v60472));
                              }
                            GC_OID(v58338);}
                          v8234 = v8234->addFast((OID)v58338);
                          }
                         GC__ANY(v8234, 1);}
                      else { { OID  v61222;
                            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                _void_(v60472->selector = Kernel.princ);
                                _void_(v60472->args = list::alloc(1,GC_OID((*Kernel.substring)(v8235,
                                  ((OID)v43125),
                                  ((OID)((CL_INT)v8230-(CL_INT)1))))));
                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                v61222 = _oid_(close_Instruction1(v60472));
                                }
                              GC_OID(v61222);}
                            v8234 = v8234->addFast((OID)v61222);
                            }
                           GC__ANY(v8234, 2);}
                        if (v45188 == CTRUE)
                       { { OID  v62182;
                          { { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                              { Do * v16839 = v60472; 
                                list * v16840;
                                { OID v_bag;
                                  GC_ANY(v16840= list::empty(Kernel.emptySet));
                                  { { Assign * v60472 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                      _void_(v60472->var = v42885);
                                      { Assign * v16841 = v60472; 
                                        OID  v16863;
                                        { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                          _void_(v60472->selector = Core.externC);
                                          _void_(v60472->args = list::alloc(2,_string_(((char*)"current_color")),_oid_(Kernel._integer)));
                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                          v16863 = _oid_(close_Instruction1(v60472));
                                          }
                                        _void_(v16841->arg = v16863);}
                                      add_I_property(Kernel.instances,Language._Assign,11,_oid_(v60472));
                                      v_bag = _oid_(close_Instruction1(v60472));
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v16840)->addFast((OID)v_bag);
                                  { { Assign * v60472 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                      _void_(v60472->var = v54560);
                                      { Assign * v16864 = v60472; 
                                        OID  v16865;
                                        { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                          _void_(v60472->selector = Core.externC);
                                          _void_(v60472->args = list::alloc(2,_string_(((char*)"current_bold")),_oid_(Kernel._integer)));
                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                          v16865 = _oid_(close_Instruction1(v60472));
                                          }
                                        _void_(v16864->arg = v16865);}
                                      add_I_property(Kernel.instances,Language._Assign,11,_oid_(v60472));
                                      v_bag = _oid_(close_Instruction1(v60472));
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v16840)->addFast((OID)v_bag);}
                                _void_(v16839->args = v16840);}
                              add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                              v62182 = _oid_(close_Instruction1(v60472));
                              }
                            GC_OID(v62182);}
                          v8234 = v8234->addFast((OID)v62182);
                          }
                         GC__ANY(v8234, 3);}
                      }
                    }
                  if (v45188 == CTRUE)
                   { { OID  v23554;
                      { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          _void_(v60472->selector = Core.set_color);
                          _void_(v60472->args = list::alloc(2,v37688,v24525));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                          v23554 = _oid_(close_Instruction1(v60472));
                          }
                        GC_OID(v23554);}
                      v8234 = v8234->addFast((OID)v23554);
                      }
                     GC__ANY(v8234, 4);}
                  if ((CL_INT)v58632 > (CL_INT)v47026->length)
                   (*Optimize.Cerror)(_string_(((char*)"[209] missing argument in ~S")),
                    _oid_(v62612));
                  if (_oid_(_char_(((unsigned char)'A'))) == v8229)
                   { { OID  v24515;
                      { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          _void_(v60472->selector = Kernel.princ);
                          _void_(v60472->args = list::alloc(1,(*(v47026))[v58632]));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                          v24515 = _oid_(close_Instruction1(v60472));
                          }
                        GC_OID(v24515);}
                      v8234 = v8234->addFast((OID)v24515);
                      }
                     GC__ANY(v8234, 5);}
                  else if (_oid_(_char_(((unsigned char)'S'))) == v8229)
                   { { OID  v25476;
                      { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          _void_(v60472->selector = Kernel.print);
                          _void_(v60472->args = list::alloc(1,(*(v47026))[v58632]));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                          v25476 = _oid_(close_Instruction1(v60472));
                          }
                        GC_OID(v25476);}
                      v8234 = v8234->addFast((OID)v25476);
                      }
                     GC__ANY(v8234, 6);}
                  else if (_oid_(_char_(((unsigned char)'I'))) == v8229)
                   GC__ANY(v8234 = v8234->addFast((OID)(*(v47026))[v58632]), 7);
                  if (v45188 == CTRUE)
                   { { OID  v26437;
                      { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          _void_(v60472->selector = Core.set_color);
                          _void_(v60472->args = list::alloc(2,v42885,v54560));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                          v26437 = _oid_(close_Instruction1(v60472));
                          }
                        GC_OID(v26437);}
                      v8234 = v8234->addFast((OID)v26437);
                      }
                     GC__ANY(v8234, 8);}
                  if (v8229 != _oid_(_char_(((unsigned char)'%'))))
                   ++v58632;
                  v43125= (CL_INT)(((CL_INT)v8230+(CL_INT)2));
                  v8230= (CL_INT)(find_string(string_v(v8235),((char*)"~"),v43125));
                  }
                GC_UNLOOP;POP_SIGNAL;}
              }
            if ((CL_INT)v43125 <= (CL_INT)v46029)
             { if (v45188 == CTRUE)
               { OID  v27398;
                { { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                    { Do * v16871 = v60472; 
                      list * v16872;
                      { OID v_bag;
                        GC_ANY(v16872= list::empty(Kernel.emptySet));
                        { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                            _void_(v60472->selector = Core.set_color);
                            _void_(v60472->args = list::alloc(2,v42885,v54560));
                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                            v_bag = _oid_(close_Instruction1(v60472));
                            }
                          GC_OID(v_bag);}
                        ((list *) v16872)->addFast((OID)v_bag);
                        { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                            _void_(v60472->selector = Kernel.color_princ);
                            _void_(v60472->args = list::alloc(1,GC_OID((*Kernel.substring)(v8235,
                              ((OID)v43125),
                              ((OID)v46029)))));
                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                            v_bag = _oid_(close_Instruction1(v60472));
                            }
                          GC_OID(v_bag);}
                        ((list *) v16872)->addFast((OID)v_bag);}
                      _void_(v16871->args = v16872);}
                    add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                    v27398 = _oid_(close_Instruction1(v60472));
                    }
                  GC_OID(v27398);}
                v8234 = v8234->addFast((OID)v27398);
                }
              else { OID  v50462;
                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Kernel.princ);
                      _void_(v60472->args = list::alloc(1,GC_OID((*Kernel.substring)(v8235,
                        ((OID)v43125),
                        ((OID)v46029)))));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v50462 = _oid_(close_Instruction1(v60472));
                      }
                    GC_OID(v50462);}
                  v8234 = v8234->addFast((OID)v50462);
                  }
                }
            if (v45188 == CTRUE)
             { OID  v51423;
              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  _void_(v60472->selector = Core.set_color);
                  _void_(v60472->args = list::alloc(2,v37688,v24525));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                  v51423 = _oid_(close_Instruction1(v60472));
                  }
                GC_OID(v51423);}
              v8234 = v8234->addFast((OID)v51423);
              }
            if (v45847 == CTRUE)
             { OID  v52384;
              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  _void_(v60472->selector = Kernel.use_as_output);
                  _void_(v60472->args = list::alloc(1,v63138));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                  v52384 = _oid_(close_Instruction1(v60472));
                  }
                GC_OID(v52384);}
              v8234 = v8234->addFast((OID)v52384);
              }
            }
          Result = (*Optimize.c_code)(v51800,
          _oid_(Kernel._any));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Error_Optimize(Error *v62612) { 
    POP_SIGNAL; return (Kernel.emptySet);}
  

CL_EXPORT OID  c_code_Error_Optimize(Error *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireBoolean * v8240 = Optimize.OPT->allocation;
        OID  v8241;
        { { OID  v53345;
            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(v60472->selector = Kernel.close);
                { Call * v16898 = v60472; 
                  list * v16899;
                  { OID v_bag;
                    GC_ANY(v16899= list::empty(Kernel.emptySet));
                    { { Cast * v60472 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                        { Cast * v16900 = v60472; 
                          OID  v16901;
                          { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                            _void_(v60472->selector = Optimize.anyObject_I);
                            { Call * v16902 = v60472; 
                              list * v16903;
                              { OID v_bag;
                                GC_ANY(v16903= list::empty(Kernel.emptySet));
                                ((list *) v16903)->addFast((OID)_oid_(Core._general_error));
                                ((list *) v16903)->addFast((OID)GC_OID((*Optimize.c_code)(GC_OID(car_list(v62612->args)),
                                  _oid_(Kernel._any))));
                                { { OID  v14717;
                                    { if (v62612->args->length != 1)
                                       { List * v60472 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                                        _void_(v60472->args = cdr_list(GC_OBJECT(list,v62612->args)));
                                        add_I_property(Kernel.instances,Language._List,11,_oid_(v60472));
                                        v14717 = _oid_(close_Instruction1(v60472));
                                        }
                                      else v14717 = Core.nil->value;
                                        GC_OID(v14717);}
                                    v_bag = (*Optimize.c_code)(v14717,
                                      _oid_(Kernel._any));
                                    }
                                  GC_OID(v_bag);}
                                ((list *) v16903)->addFast((OID)v_bag);}
                              _void_(v16902->args = v16903);}
                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                            v16901 = _oid_(close_Instruction1(v60472));
                            }
                          _void_(v16900->arg = v16901);}
                        _void_(v60472->set_arg = Kernel._exception);
                        add_I_property(Kernel.instances,Language._Cast,11,_oid_(v60472));
                        v_bag = _oid_(close_Instruction1(v60472));
                        }
                      GC_OID(v_bag);}
                    ((list *) v16899)->addFast((OID)v_bag);}
                  _void_(v16898->args = v16899);}
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v53345 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v53345);}
            v8241 = (*Optimize.c_code)(v53345,
              _oid_(Kernel._void));
            }
          GC_OID(v8241);}
        _void_(Optimize.OPT->allocation = v8240);
        Result = v8241;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * extendedTest_ask_If(If *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { OID  v56375 = v62612->test;
        if (INHERIT(OWNER(v56375),Language._Call))
         { if ((INHERIT(OWNER((*(OBJECT(Call,v56375)->args))[1]),Language._Variable)) && 
              (OBJECT(Call,v56375)->selector == Core.known_ask))
           Result = OBJECT(ClaireType,(*Kernel.range)((*(OBJECT(Call,v56375)->args))[1]));
          else Result = Kernel._any;
            }
        else Result = Kernel._any;
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_If_Optimize(If *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { ClaireType * v56373 = GC_OBJECT(ClaireType,extendedTest_ask_If(v62612));
        if (extended_ask_type(v56373) == CTRUE)
         range_sets_any(GC_OID((*(OBJECT(bag,(*Core.args)(GC_OID(v62612->test)))))[1]),GC_OBJECT(ClaireType,sort_abstract_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Core.t1)(_oid_(v56373)))))));
        { ClaireType * v47973 = GC_OBJECT(ClaireType,U_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->arg)))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->other))))));
          if (extended_ask_type(v56373) == CTRUE)
           put_property2(Kernel.range,GC_OBJECT(ClaireObject,OBJECT(ClaireObject,(*(OBJECT(bag,(*Core.args)(GC_OID(v62612->test)))))[1])),_oid_(v56373));
          Result = v47973;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_If_Optimize(If *v62612,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireType * v56373 = GC_OBJECT(ClaireType,extendedTest_ask_If(v62612));
        if (extended_ask_type(v56373) == CTRUE)
         range_sets_any(GC_OID((*(OBJECT(bag,(*Core.args)(GC_OID(v62612->test)))))[1]),GC_OBJECT(ClaireType,sort_abstract_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Core.t1)(_oid_(v56373)))))));
        if ((_inf_equal_type(GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->test))))),Kernel._boolean) != CTRUE) && 
            (Optimize.PENIBLE->value == Kernel.ctrue))
         { warn_void();
          if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
           mtformat_module1(Optimize.it,((char*)"`BLUE CLAIRE 3.3 SYNTAX - Test in ~S should be a boolean [260]\n"),2,list::alloc(1,_oid_(v62612)));
          else ;}
        { If * v47973;
          { { Instruction *V_CC ;
              { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                _void_(v60472->test = c_boolean_any(GC_OID(v62612->test)));
                _void_(v60472->arg = (*Optimize.c_code)(GC_OID(v62612->arg),
                  _oid_(v8235)));
                _void_(v60472->other = (*Optimize.c_code)(GC_OID(v62612->other),
                  _oid_(v8235)));
                add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                V_CC = close_Instruction1(v60472);
                }
              v47973= (If *) V_CC;}
            GC_OBJECT(If,v47973);}
          if (extended_ask_type(v56373) == CTRUE)
           put_property2(Kernel.range,GC_OBJECT(ClaireObject,OBJECT(ClaireObject,(*(OBJECT(bag,(*Core.args)(GC_OID(v62612->test)))))[1])),_oid_(v56373));
          Result = _oid_(v47973);
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * c_gc_ask_If(If *v62612) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = (((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v62612->arg))) == CTRUE) ? CTRUE : (((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v62612->other))) == CTRUE) ? CTRUE : CFALSE));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Case_Optimize(Case *v62612) { 
    
    GC_RESERVE(3);  // v3.3.39 optim !
    { ClaireType *Result ;
      { OID  v48682 = GC_OID(v62612->var);
        OID  v30871;
        { if (INHERIT(OWNER(v48682),Language._Variable))
           v30871 = get_property(Kernel.range,OBJECT(ClaireObject,v48682));
          else v30871 = _oid_(Kernel._any);
            GC_OID(v30871);}
        list * v8228 = ((list *) copy_bag(v62612->args));
        ClaireType * v35428 = Kernel.emptySet;
        ClaireType * v53479 = Kernel.emptySet;
        if (v30871 == CNULL)
         v30871= (_oid_(Kernel._any));
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)v8228->length > (CL_INT)0))
          { GC_LOOP;
            if (INHERIT(OWNER((*(v8228))[1]),Kernel._type))
             { GC__ANY(v53479 = U_type(v53479,OBJECT(ClaireType,(*(v8228))[1])), 1);
              if (osort_any(v30871) == osort_any((*(v8228))[1]))
               range_sets_any(v48682,OBJECT(ClaireType,(*(v8228))[1]));
              else if (osort_any(v30871) == Kernel._any)
               range_sets_any(v48682,GC_OBJECT(ClaireType,sort_abstract_I_type(OBJECT(ClaireType,(*(v8228))[1]))));
              }
            else (*Optimize.Cerror)(_string_(((char*)"[208] wrong type declaration for case: ~S in ~S")),
                car_list(v8228),
                _oid_(v62612));
              if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
             mtformat_module1(Optimize.it,((char*)"so far rtype -> ~S \n"),5,list::alloc(1,_oid_(v35428)));
            else ;{ ClaireType * v58297 = GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)((*(v8228))[2])));
              if ((sort_abstract_ask_type(v58297) == CTRUE) || 
                  (sort_abstract_ask_type(v35428) == CTRUE))
               GC__ANY(v35428 = sort_abstract_I_type(GC_OBJECT(ClaireType,U_type(ptype_type(v35428),ptype_type(v58297)))), 2);
              else GC__ANY(v35428 = U_type(v35428,v58297), 3);
                }
            if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
             mtformat_module1(Optimize.it,((char*)"so far rtype -> ~S because of ~S branch \n"),5,list::alloc(2,_oid_(v35428),(*(v8228))[1]));
            else ;if (INHERIT(OWNER(v48682),Language._Variable))
             store_object(OBJECT(ClaireObject,v48682),
              3,
              Kernel._object,
              v30871,
              CFALSE);
            v8228= (skip_list(v8228,2));
            GC_UNLOOP;POP_SIGNAL;}
          }
        if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
         mtformat_module1(Optimize.it,((char*)"case c_type %type = ~S utype = ~S %type <= utype : ~S \n"),5,GC_OBJECT(list,list::alloc(3,v30871,
          _oid_(v53479),
          _oid_(_inf_equal_type(OBJECT(ClaireType,v30871),v53479)))));
        else ;if (_inf_equal_type(OBJECT(ClaireType,v30871),v53479) == CTRUE)
         Result = v35428;
        else Result = ((_inf_equal_type(v35428,Kernel._boolean) == CTRUE) ?
          Kernel._boolean :
          Kernel._any );
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Case_Optimize(Case *v62612,ClaireClass *v8235) { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    { OID Result = 0;
      { OID  v48682 = GC_OID(v62612->var);
        OID  v30871;
        { if (INHERIT(OWNER(v48682),Language._Variable))
           v30871 = get_property(Kernel.range,OBJECT(ClaireObject,v48682));
          else v30871 = _oid_(Kernel._any);
            GC_OID(v30871);}
        list * v8228 = ((list *) copy_bag(v62612->args));
        OID  v53479 = _oid_(Kernel.emptySet);
        OID  v1700;
        { { OID  v15678;
            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(v60472->selector = Kernel._Z);
                _void_(v60472->args = list::alloc(2,v48682,(*(v8228))[1]));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v15678 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v15678);}
            v1700 = c_boolean_any(v15678);
            }
          GC_OID(v1700);}
        range_sets_any(v48682,OBJECT(ClaireType,(*(v8228))[1]));
        { If * v51797;
          { { Instruction *V_CC ;
              { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                _void_(v60472->test = v1700);
                _void_(v60472->arg = (*Optimize.c_code)((*(v8228))[2],
                  _oid_(v8235)));
                _void_(v60472->other = (*Optimize.c_code)(Kernel.cfalse,
                  _oid_(v8235)));
                add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                V_CC = close_Instruction1(v60472);
                }
              v51797= (If *) V_CC;}
            GC_OBJECT(If,v51797);}
          If * v46069 = v51797;
          if (INHERIT(OWNER(v48682),Language._Variable))
           store_object(OBJECT(ClaireObject,v48682),
            3,
            Kernel._object,
            v30871,
            CFALSE);
          v8228= (skip_list(v8228,2));
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)v8228->length > (CL_INT)0))
            { GC_LOOP;
              GC__OID(v53479 = _oid_(U_type(OBJECT(ClaireType,v53479),OBJECT(ClaireType,(*(v8228))[1]))), 1);
              if (_inf_equal_type(OBJECT(ClaireType,v30871),OBJECT(ClaireType,v53479)) == CTRUE)
               { if (osort_any(v30871) == osort_any((*(v8228))[1]))
                 range_sets_any(v48682,OBJECT(ClaireType,(*(v8228))[1]));
                else if (osort_any(v30871) == Kernel._any)
                 range_sets_any(v48682,GC_OBJECT(ClaireType,sort_abstract_I_type(OBJECT(ClaireType,(*(v8228))[1]))));
                _void_(v46069->other = (*Optimize.c_code)((*(v8228))[2],
                  _oid_(v8235)));
                if (INHERIT(OWNER(v48682),Language._Variable))
                 store_object(OBJECT(ClaireObject,v48682),
                  3,
                  Kernel._object,
                  v30871,
                  CFALSE);
                { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                }
              else { OID  v57133;
                  { { OID  v16639;
                      { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          _void_(v60472->selector = Kernel._Z);
                          _void_(v60472->args = list::alloc(2,v48682,(*(v8228))[1]));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                          v16639 = _oid_(close_Instruction1(v60472));
                          }
                        GC_OID(v16639);}
                      v57133 = c_boolean_any(v16639);
                      }
                    GC_OID(v57133);}
                  range_sets_any(v48682,OBJECT(ClaireType,(*(v8228))[1]));
                  { If * v16928 = v46069; 
                    OID  v16929;
                    { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                      _void_(v60472->test = v57133);
                      _void_(v60472->arg = (*Optimize.c_code)((*(v8228))[2],
                        _oid_(v8235)));
                      _void_(v60472->other = (*Optimize.c_code)(Kernel.cfalse,
                        _oid_(v8235)));
                      add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                      v16929 = _oid_(close_Instruction1(v60472));
                      }
                    _void_(v16928->other = v16929);}
                  GC__ANY(v46069 = OBJECT(If,v46069->other), 2);
                  }
                if (INHERIT(OWNER(v48682),Language._Variable))
               store_object(OBJECT(ClaireObject,v48682),
                3,
                Kernel._object,
                v30871,
                CFALSE);
              v8228= (skip_list(v8228,2));
              GC_UNLOOP;POP_SIGNAL;}
            }
          if ((INHERIT(OWNER(v48682),Language._Definition)) && (INHERIT(OBJECT(Definition,v48682)->arg->isa,Kernel._exception)))
           Result = v48682;
          else Result = _oid_(v51797);
            }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Do_Optimize(Do *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(last_list(v62612->args))));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Do_Optimize(Do *v62612,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
        { Do * v16930 = v60472; 
          list * v16932;
          { CL_INT  v8229 = v62612->args->length;
            CL_INT  v8230 = 0;
            { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID v8240; CL_INT CLcount;
              v_list = GC_OBJECT(list,v62612->args);
               v16932 = v_list->clone();
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { v8240 = (*(v_list))[CLcount];
                { ++v8230;
                  { OID  v21444;
                    if (v8230 == v8229)
                     v21444 = _oid_(v8235);
                    else v21444 = _oid_(Kernel._void);
                      v_val = (*Optimize.c_code)(v8240,
                      v21444);
                    }
                  }
                
                (*((list *) v16932))[CLcount] = v_val;}
              }
            }
          _void_(v16930->args = v16932);}
        add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * c_gc_ask_Do(Do *v62612) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(GC_OID(last_list(v62612->args))));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Let_Optimize(Let *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { OID  v56377 = GC_OID(v62612->value);
        OID  v58297 = GC_OID((*Optimize.c_type)(v56377));
        ClaireType * v30871 = ptype_type(OBJECT(ClaireType,v58297));
        if (((CL_INT)v62612->var->dindex > (CL_INT)0) && 
            ((Kernel._void == v30871) || 
                (v62612->var->range == Kernel._void)))
         Result = Kernel._void;
        else { if (should_trace_ask_module1(Optimize.it,4) == CTRUE)
             mtformat_module1(Optimize.it,((char*)"c_type Let\n"),4,list::empty());
            else ;range_infers_Variable(GC_OBJECT(Variable,v62612->var),OBJECT(ClaireType,v58297));
            Result = OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->arg)));
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Let_Optimize(Let *v62612,ClaireClass *v8235) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { OID Result = 0;
      { OID  v56377 = GC_OID(v62612->value);
        ClaireType * v30871 = GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v56377))));
        if (should_trace_ask_module1(Optimize.it,4) == CTRUE)
         mtformat_module1(Optimize.it,((char*)"c_code Let\n"),4,list::empty());
        else ;range_infers_Variable(GC_OBJECT(Variable,v62612->var),v30871);
        if (((CL_INT)v62612->var->dindex > (CL_INT)0) && 
            ((Kernel._void == v30871) || 
                (v62612->var->range == Kernel._void)))
         { list * v37680 = list::alloc(Kernel._any,1,GC_OID(v62612->value));
          OID  v8217 = GC_OID(v62612->arg);
          if (INHERIT(OWNER(v8217),Language._Do))
           { CL_INT  v8225 = 1;
            CL_INT  v16935 = ((CL_INT)OBJECT(Do,v8217)->args->length-(CL_INT)1);
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while (((CL_INT)v8225 <= (CL_INT)v16935))
              { GC_LOOP;
                v37680->addFast((OID)GC_OID((*(OBJECT(Do,v8217)->args))[v8225]));
                ++v8225;
                GC_UNLOOP;POP_SIGNAL;}
              }
            }
          { OID  v23366;
            { { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                _void_(v60472->args = v37680);
                add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                v23366 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v23366);}
            Result = (*Optimize.c_code)(v23366,
              _oid_(v8235));
            }
          }
        else { if (_inf_equal_type(v30871,GC_OBJECT(ClaireType,v62612->var->range)) != CTRUE)
             v56377= (GC_OID(c_warn_Variable(GC_OBJECT(Variable,v62612->var),v56377,v30871)));
            { Let * v8240;
              { { Instruction *V_CC ;
                  { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                    _void_(v60472->var = v62612->var);
                    _void_(v60472->value = c_gc_I_any2(GC_OID(c_strict_code_any(v56377,psort_any(GC_OID(_oid_(v62612->var->range))))),v30871));
                    _void_(v60472->arg = (*Optimize.c_code)(GC_OID(v62612->arg),
                      _oid_(v8235)));
                    add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                    V_CC = close_Instruction1(v60472);
                    }
                  v8240= (Let *) V_CC;}
                GC_OBJECT(Let,v8240);}
              _void_(v8240->isa = v62612->isa);
              if ((INHERIT(v8240->isa,Language._Let_star)) && 
                  ((INHERIT(v30871->isa,Kernel._tuple)) && 
                    (BCONTAIN(c_status_any(GC_OID(v62612->value),Kernel.nil),((CL_INT)(OID)(1))))))
               { CL_INT  v8225 = 1;
                OID  v8242 = GC_OID(v8240->arg);
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  while (((INHERIT(OWNER(v8242),Language._Let)) && 
                      ((CL_INT)v8225 <= (CL_INT)((bag *) v30871)->length)))
                  { GC_LOOP;
                    if ((((OBJECT(ClaireBoolean,(*Optimize.gcsafe_ask)((*(((bag *) v30871)))[v8225]))) == CTRUE) ? CTRUE : ((INHERIT(owner_any((*Kernel.value)(v8242)),Optimize._to_protect)) ? CTRUE : CFALSE)) != CTRUE)
                     { _void_(Optimize.OPT->protection = CTRUE);
                      { OID  v44508;
                        { { Compile_to_protect * v60472 = ((Compile_to_protect *) GC_OBJECT(Compile_to_protect,new_object_class(Optimize._to_protect)));
                            _void_(v60472->arg = (*Kernel.value)(v8242));
                            add_I_property(Kernel.instances,Optimize._to_protect,11,_oid_(v60472));
                            v44508 = _oid_(close_Instruction1(v60472));
                            }
                          GC_OID(v44508);}
                        write_property(Kernel.value,OBJECT(ClaireObject,v8242),v44508);
                        }
                      }
                    ++v8225;
                    GC__OID(v8242 = (*Kernel.arg)(v8242), 1);
                    GC_UNLOOP;POP_SIGNAL;}
                  }
                }
              Result = _oid_(v8240);
              }
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_When_Optimize(When *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { OID  v56377 = GC_OID(v62612->value);
        Variable * v8238 = GC_OBJECT(Variable,v62612->var);
        OID  v8220 = GC_OID(daccess_any(v56377,CTRUE));
        OID  v30871;
        { if (v8220 != CNULL)
           v30871 = (*Optimize.c_type)(v8220);
          else v30871 = (*Optimize.c_type)(v56377);
            GC_OID(v30871);}
        if (extended_ask_type(OBJECT(ClaireType,v30871)) == CTRUE)
         v30871= (GC_OID((*Core.t1)(v30871)));
        range_infers_Variable(v8238,OBJECT(ClaireType,v30871));
        Result = U_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->arg)))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->other)))));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_When_Optimize(When *v62612,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v56377 = GC_OID(v62612->value);
        Variable * v8238 = GC_OBJECT(Variable,v62612->var);
        OID  v8220 = GC_OID(daccess_any(v56377,CTRUE));
        Variable * v58820 = GC_OBJECT(Variable,Variable_I_symbol(append_symbol(v62612->var->pname,_string_(((char*)"test"))),v62612->var->index,Kernel._any));
        OID  v30871;
        { if (v8220 != CNULL)
           v30871 = (*Optimize.c_type)(v8220);
          else v30871 = (*Optimize.c_type)(v56377);
            GC_OID(v30871);}
        if (extended_ask_type(OBJECT(ClaireType,v30871)) == CTRUE)
         v30871= (GC_OID((*Core.t1)(v30871)));
        range_infers_Variable(v8238,OBJECT(ClaireType,v30871));
        if ((v8220 != CNULL) && 
            (extended_ask_type(OBJECT(ClaireType,(*Kernel.range)(GC_OID((*Kernel.selector)(v8220))))) != CTRUE))
         { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
          _void_(v60472->var = v8238);
          _void_(v60472->value = c_gc_I_any2(v8220,OBJECT(ClaireType,v30871)));
          { Let * v16957 = v60472; 
            OID  v16958;
            { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
              { If * v16959 = v60472; 
                OID  v16960;
                { Call_method2 * v60472 = ((Call_method2 *) GC_OBJECT(Call_method2,new_object_class(Language._Call_method2)));
                  _void_(v60472->arg = ((method *) _at_property1(Core.identical_ask,Kernel._any)));
                  _void_(v60472->args = list::alloc(2,_oid_(v8238),GC_OID((*Optimize.c_code)(CNULL,
                    GC_OID((*Optimize.c_sort)(_oid_(v8238)))))));
                  add_I_property(Kernel.instances,Language._Call_method2,11,_oid_(v60472));
                  v16960 = _oid_(close_Instruction1(v60472));
                  }
                _void_(v16959->test = v16960);}
              _void_(v60472->arg = (*Optimize.c_code)(GC_OID(v62612->other),
                _oid_(v8235)));
              _void_(v60472->other = (*Optimize.c_code)(GC_OID(v62612->arg),
                _oid_(v8235)));
              add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
              v16958 = _oid_(close_Instruction1(v60472));
              }
            _void_(v16957->arg = v16958);}
          add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        else if (((*Optimize.c_sort)(_oid_(v8238)) == _oid_(Kernel._any)) && 
            ((_inf_equal_type(OBJECT(ClaireType,v30871),GC_OBJECT(ClaireType,v8238->range)) == CTRUE) && 
              ((CL_INT)3 <= (CL_INT)Optimize.compiler->safety)))
         { OID  v49313;
          { { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
              _void_(v60472->var = v8238);
              _void_(v60472->value = v56377);
              { Let * v16962 = v60472; 
                OID  v16963;
                { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                  { If * v16965 = v60472; 
                    OID  v16966;
                    { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Core._I_equal);
                      _void_(v60472->args = list::alloc(2,_oid_(v8238),CNULL));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v16966 = _oid_(close_Instruction1(v60472));
                      }
                    _void_(v16965->test = v16966);}
                  _void_(v60472->arg = v62612->arg);
                  _void_(v60472->other = v62612->other);
                  add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                  v16963 = _oid_(close_Instruction1(v60472));
                  }
                _void_(v16962->arg = v16963);}
              add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
              v49313 = _oid_(close_Instruction1(v60472));
              }
            GC_OID(v49313);}
          Result = (*Optimize.c_code)(v49313,
            _oid_(v8235));
          }
        else { OID  v8763;
            { { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                _void_(v60472->var = v58820);
                _void_(v60472->value = v56377);
                { Let * v16989 = v60472; 
                  OID  v16990;
                  { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                    { If * v16991 = v60472; 
                      OID  v16992;
                      { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        _void_(v60472->selector = Core._I_equal);
                        _void_(v60472->args = list::alloc(2,_oid_(v58820),CNULL));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                        v16992 = _oid_(close_Instruction1(v60472));
                        }
                      _void_(v16991->test = v16992);}
                    { If * v16993 = v60472; 
                      OID  v16994;
                      { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                        _void_(v60472->var = v8238);
                        { Let * v16995 = v60472; 
                          OID  v16996;
                          { Cast * v60472 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                            _void_(v60472->arg = _oid_(v58820));
                            _void_(v60472->set_arg = OBJECT(ClaireType,v30871));
                            add_I_property(Kernel.instances,Language._Cast,11,_oid_(v60472));
                            v16996 = _oid_(close_Instruction1(v60472));
                            }
                          _void_(v16995->value = v16996);}
                        _void_(v60472->arg = v62612->arg);
                        add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                        v16994 = _oid_(close_Instruction1(v60472));
                        }
                      _void_(v16993->arg = v16994);}
                    _void_(v60472->other = (*Optimize.c_code)(GC_OID(v62612->other),
                      _oid_(v8235)));
                    add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                    v16990 = _oid_(close_Instruction1(v60472));
                    }
                  _void_(v16989->arg = v16990);}
                add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                v8763 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v8763);}
            Result = (*Optimize.c_code)(v8763,
              _oid_(v8235));
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * c_gc_ask_Let(Let *v62612) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v62612->arg));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_For_Optimize(For *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = infers_from_type2(GC_OBJECT(ClaireType,return_type_any(GC_OID(v62612->arg))),_oid_(v62612));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * infers_from_type2(ClaireType *v8236,OID v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (equal(_oid_(v8236),_oid_(Kernel.emptySet)) == CTRUE)
       Result = sort_abstract_I_type(Kernel._boolean);
      else if ((CL_INT)Optimize.compiler->safety > (CL_INT)3)
       { if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
         mtformat_module1(Optimize.it,((char*)"... c_type(~S) -> ~S - ~S \n"),2,list::alloc(3,v62612,
          _oid_(v8236),
          GC_OID(_oid_(sort_abstract_I_type(v8236)))));
        else ;Result = sort_abstract_I_type(v8236);
        }
      else Result = Kernel._any;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_For_Optimize(For *v62612,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v58797 = GC_OID(v62612->set_arg);
        ClaireBoolean * v8218 = Optimize.OPT->protection;
        CL_INT  v58637 = Optimize.compiler->safety;
        Variable * v30521 = GC_OBJECT(Variable,v62612->var);
        Variable * v8238;
        { { Instruction *V_CC ;
            { Variable * v60472 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(v60472->pname = v30521->pname);
              _void_(v60472->range = v30521->range);
              _void_(v60472->index = v30521->index);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v8238= (Variable *) V_CC;}
          GC_OBJECT(Variable,v8238);}
        OID  v41072 = GC_OID(substitution_any(GC_OID(v62612->arg),v30521,_oid_(v8238)));
        OID  v52699 = GC_OID(c_inline_arg_ask_any(v58797));
        _void_(Optimize.OPT->protection = CFALSE);
        if (INHERIT(OWNER(v58797),Core._global_variable))
         { if (boolean_I_any(_oid_(OBJECT(global_variable,v58797)->range)) != CTRUE)
           { _void_(v62612->set_arg = OBJECT(global_variable,v58797)->value);
            v58797= (GC_OID(OBJECT(global_variable,v58797)->value));
            }
          }
        else if (INHERIT(OWNER(v58797),Language._Select))
         { ClaireType * v56375 = GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v58797)));
          if ((_inf_equal_type(v56375,Kernel._bag) != CTRUE) || 
              (_inf_equal_type(v56375,Kernel._set) == CTRUE))
           { v62612= (GC_OBJECT(For,((For *) copy_object(v62612))));
            _void_(v62612->isa = Language._Select);
            }
          }
        else if (INHERIT(OWNER(v58797),Kernel._class))
         { if (((CL_INT)OBJECT(ClaireClass,v58797)->open <= (CL_INT)1) && 
              (boolean_I_any(_oid_(OBJECT(ClaireClass,v58797)->subclass)) != CTRUE))
           { Iteration * v16997 = v62612; 
            OID  v17018;
            { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(v60472->selector = Kernel.instances);
              _void_(v60472->args = list::alloc(1,v58797));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
              v17018 = _oid_(close_Instruction1(v60472));
              }
            _void_(v16997->set_arg = v17018);}
          }
        { OID  v56375 = GC_OID((*Optimize.c_type)(GC_OID(v62612->set_arg)));
          ClaireType * v43739 = GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v56375)));
          ClaireType * v43740;
          { { ClaireType * v39515;
              { { OID v61842;{ OID  v40476;
                    { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        _void_(v60472->selector = Kernel.set_I);
                        _void_(v60472->args = list::alloc(1,v58797));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                        v40476 = _oid_(close_Instruction1(v60472));
                        }
                      GC_OID(v40476);}
                    v61842 = (*Optimize.c_type)(v40476);
                    }
                  
                  v39515=OBJECT(ClaireType,v61842);}
                GC_OBJECT(ClaireType,v39515);}
              v43740 = pmember_type(v39515);
              }
            GC_OBJECT(ClaireType,v43740);}
          if (_inf_equal_type(v43740,v43739) == CTRUE)
           v43739= (v43740);
          range_infers_for_Variable(v8238,v43739,OBJECT(ClaireType,v56375));
          _void_(Optimize.compiler->safety = 1);
          v43739= (GC_OBJECT(ClaireType,v8238->range));
          _void_(v8238->range = ptype_type(v43739));
          { OID  v8229;
            { if ((OBJECT(ClaireBoolean,Language.DEBUG_ask->value)) == CTRUE)
               v8229 = Kernel.cfalse;
              else v8229 = Iterate_I_Iteration(v62612);
                GC_OID(v8229);}
            if (equal(_oid_(Kernel._method),_oid_(OWNER(v8229))) != CTRUE)
             { OID  v58541;
              { if ((OBJECT(ClaireBoolean,Language.DEBUG_ask->value)) == CTRUE)
                 v58541 = Kernel.cfalse;
                else v58541 = restriction_I_property(Language.iterate,list::alloc(3,v56375,
                    _oid_(set::alloc(1,_oid_(v8238))),
                    _oid_(Kernel._any)),CTRUE);
                  GC_OID(v58541);}
              if (Kernel._method == OWNER(v58541))
               v8229= (v58541);
              }
            _void_(Optimize.compiler->safety = v58637);
            _void_(v8238->range = v43739);
            { OID  v8234;
              { if ((Kernel._method == OWNER(v8229)) && (OBJECT(method,v8229)->inline_ask == CTRUE))
                 { if (((CL_INT)Optimize.compiler->safety < (CL_INT)6) && 
                      (BCONTAIN(c_status_any(v41072,Kernel.nil),((CL_INT)(OID)(1)))))
                   _void_(Optimize.OPT->loop_gc = CTRUE);
                  if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
                   mtformat_module1(Optimize.it,((char*)"iteration found -> ~S \n"),5,list::alloc(1,v8229));
                  else ;if (sort_abstract_ask_type(v8238->range) == CTRUE)
                   _void_(v8238->range = CLREAD(Union,v8238->range,t2));
                  v8234 = c_inline_method1(OBJECT(method,v8229),list::alloc(3,GC_OID(instruction_copy_any(GC_OID(v62612->set_arg))),
                    _oid_(v8238),
                    v41072),v8235);
                  }
                else if (boolean_I_any(v52699) == CTRUE)
                 { OID  v41438;
                  { { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                      _void_(v60472->var = v8238);
                      _void_(v60472->set_arg = v52699);
                      _void_(v60472->arg = v41072);
                      add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                      v41438 = _oid_(close_Instruction1(v60472));
                      }
                    GC_OID(v41438);}
                  v8234 = (*Optimize.c_code)(v41438,
                    _oid_(v8235));
                  }
                else if ((INHERIT(OWNER(v58797),Language._Call)) && (OBJECT(Call,v58797)->selector == Core.Id))
                 v8234 = c_code_multiple_For(v62612,OBJECT(ClaireType,v56375),v8235);
                else { For * v58696;
                    { { Instruction *V_CC ;
                        { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                          _void_(v60472->var = v8238);
                          _void_(v60472->set_arg = c_gc_I_any1(GC_OID(enumerate_code_any(GC_OID(v62612->set_arg),OBJECT(ClaireType,v56375)))));
                          _void_(v60472->arg = (*Optimize.c_code)(v41072,
                            _oid_(Kernel._void)));
                          add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                          V_CC = close_Instruction1(v60472);
                          }
                        v58696= (For *) V_CC;}
                      GC_OBJECT(For,v58696);}
                    if (v8235 == Kernel._any)
                     v8234 = _oid_(v58696);
                    else { Compile_to_C * v60472 = ((Compile_to_C *) GC_OBJECT(Compile_to_C,new_object_class(Optimize._to_C)));
                        _void_(v60472->arg = _oid_(v58696));
                        _void_(v60472->set_arg = v8235);
                        add_I_property(Kernel.instances,Optimize._to_C,11,_oid_(v60472));
                        v8234 = _oid_(close_Instruction1(v60472));
                        }
                      }
                  GC_OID(v8234);}
              if ((Optimize.OPT->protection == CTRUE) && 
                  (((CL_INT)0 <= (CL_INT)Optimize.OPT->max_vars) && 
                    ((CL_INT)Optimize.compiler->safety < (CL_INT)6)))
               _void_(Optimize.OPT->loop_gc = CTRUE);
              _void_(Optimize.OPT->protection = ((Optimize.OPT->protection == CTRUE) ? CTRUE : ((v8218 == CTRUE) ? CTRUE : CFALSE)));
              Result = v8234;
              }
            }
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_multiple_For(For *v62612,ClaireType *v56375,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      { Variable * v8238 = GC_OBJECT(Variable,v62612->var);
        OID  v58797 = GC_OID((*(OBJECT(Call,v62612->set_arg)->args))[1]);
        Variable * v58820 = GC_OBJECT(Variable,Variable_I_symbol(append_symbol(v8238->pname,_string_(((char*)"test"))),v62612->var->index,v56375));
        Let * v8230;
        { { Instruction *V_CC ;
            { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
              _void_(v60472->var = v58820);
              _void_(v60472->value = v58797);
              { Let * v17022 = v60472; 
                OID  v17023;
                { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                  _void_(v60472->var = v62612->var);
                  _void_(v60472->set_arg = enumerate_code_any(v58797,v56375));
                  _void_(v60472->arg = v62612->arg);
                  add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                  v17023 = _oid_(close_Instruction1(v60472));
                  }
                _void_(v17022->arg = v17023);}
              add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v8230= (Let *) V_CC;}
          GC_OBJECT(Let,v8230);}
        show_opportunist_integer1(0);
        if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
         mtformat_module1(Optimize.it,((char*)" `GREEN note: use an expended iteration for {~S} \n"),0,list::alloc(1,_oid_(v62612)));
        else ;{ CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v8234);
          for (START(Language.iterate->restrictions); NEXT(v8234);)
          { GC_LOOP;
            if ((_inf_equalt_class(domain_I_restriction(OBJECT(restriction,v8234)),v56375) == CTRUE) && 
                ((_inf_equalt_class(domain_I_restriction(OBJECT(restriction,v8234)),Kernel._collection) == CTRUE) && 
                  ((OBJECT(method,v8234)->inline_ask == CTRUE) && 
                    (belong_to(_oid_(v8238),(*(OBJECT(restriction,v8234)->domain))[2]) == CTRUE))))
             { Variable * v29362;
              { { Instruction *V_CC ;
                  { Variable * v60472 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                    _void_(v60472->pname = v8238->pname);
                    _void_(v60472->range = v8238->range);
                    _void_(v60472->index = v8238->index);
                    add_I_property(Kernel.instances,Language._Variable,11,_oid_(v60472));
                    V_CC = close_Instruction1(v60472);
                    }
                  v29362= (Variable *) V_CC;}
                GC_OBJECT(Variable,v29362);}
              OID  v41072 = GC_OID(substitution_any(GC_OID(v62612->arg),v8238,_oid_(v29362)));
              { Let * v17024 = v8230; 
                OID  v17025;
                { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                  { If * v17026 = v60472; 
                    OID  v17027;
                    { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Kernel._Z);
                      _void_(v60472->args = list::alloc(2,_oid_(v58820),(*(OBJECT(restriction,v8234)->domain))[1]));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v17027 = _oid_(close_Instruction1(v60472));
                      }
                    _void_(v17026->test = v17027);}
                  { If * v17049 = v60472; 
                    OID  v17050;
                    { if (((CL_INT)Optimize.compiler->safety < (CL_INT)6) && 
                          (BCONTAIN(c_status_any(GC_OID(v62612->arg),Kernel.nil),((CL_INT)(OID)(1)))))
                       _void_(Optimize.OPT->loop_gc = CTRUE);
                      if (sort_abstract_ask_type(v29362->range) == CTRUE)
                       _void_(v29362->range = CLREAD(Union,v8238->range,t2));
                      v17050 = c_inline_method1(OBJECT(method,v8234),GC_OBJECT(list,list::alloc(3,_oid_(v58820),
                        _oid_(v29362),
                        v41072)),v8235);
                      }
                    _void_(v17049->arg = v17050);}
                  _void_(v60472->other = v8230->arg);
                  add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                  v17025 = _oid_(close_Instruction1(v60472));
                  }
                _void_(v17024->arg = v17025);}
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        Result = (*Optimize.c_code)(_oid_(v8230),
          _oid_(v8235));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * c_gc_ask_Iteration(Iteration *v62612) { 
    POP_SIGNAL; return (CTRUE);}
  

CL_EXPORT ClaireBoolean * c_gc_ask_Ffor1(iClaire_Ffor *v62612) { 
    POP_SIGNAL; return (CTRUE);}
  

CL_EXPORT ClaireType * c_type_Iteration_Optimize(Iteration *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { OID  v56375 = GC_OID((*Optimize.c_type)(GC_OID(v62612->set_arg)));
        range_infers_for_Variable(GC_OBJECT(Variable,v62612->var),GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v56375))),OBJECT(ClaireType,v56375));
        Result = ((get_property(Kernel.of,v62612) != CNULL) ?
          param_I_class((((INHERIT(v62612->isa,Language._Select)) || 
              (INHERIT(v62612->isa,Language._Image))) ?
            Kernel._set :
            Kernel._list ),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.of)(_oid_(v62612))))) :
          nth_class1((((INHERIT(v62612->isa,Language._Select)) || 
              (INHERIT(v62612->isa,Language._Image))) ?
            Kernel._set :
            Kernel._list ),GC_OBJECT(ClaireType,(((INHERIT(v62612->isa,Language._Select)) || 
              (INHERIT(v62612->isa,Language._Lselect))) ?
            pmember_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->set_arg))))) :
            ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->arg)))) ))) );
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Iteration_Optimize(Iteration *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v58797 = GC_OID(v62612->set_arg);
        OID  v56375 = GC_OID((*Optimize.c_type)(v58797));
        if (INHERIT(v62612->isa,Language._For))
         Result = (*Optimize.c_code)(_oid_(v62612),
          _oid_(Kernel._any));
        else if ((INHERIT(v62612->isa,Language._Collect)) && (_inf_equal_type(OBJECT(ClaireType,v56375),Kernel._bag) == CTRUE))
         { _void_(Optimize.OPT->allocation = CTRUE);
          range_infers_for_Variable(GC_OBJECT(Variable,v62612->var),GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v56375))),OBJECT(ClaireType,v56375));
          { ClaireType * v58829 = GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->arg)))));
            Collect * v8240;
            { { Instruction *V_CC ;
                { Collect * v60472 = ((Collect *) GC_OBJECT(Collect,new_object_class(Language._Collect)));
                  _void_(v60472->var = v62612->var);
                  _void_(v60472->set_arg = c_gc_I_any1(GC_OID(c_strict_code_any(v58797,Kernel._bag))));
                  _void_(v60472->arg = (*Optimize.c_code)(GC_OID(v62612->arg),
                    _oid_(Kernel._any)));
                  add_I_property(Kernel.instances,Language._Collect,11,_oid_(v60472));
                  V_CC = close_Instruction1(v60472);
                  }
                v8240= (Collect *) V_CC;}
              GC_OBJECT(Collect,v8240);}
            if (v58829 == Kernel._void)
             (*Optimize.Cerror)(_string_(((char*)"[205] use of void expression ~S in ~S")),
              GC_OID(v62612->arg),
              _oid_(v62612));
            if (get_property(Kernel.of,v62612) != CNULL)
             { if (((CL_INT)Optimize.compiler->safety > (CL_INT)4) || 
                  (_inf_equal_type(v58829,GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.of)(_oid_(v62612))))) == CTRUE))
               { update_property(Kernel.of,
                  v8240,
                  5,
                  Kernel._object,
                  GC_OID((*Kernel.of)(_oid_(v62612))));
                Result = _oid_(v8240);
                }
              else { warn_void();
                  if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
                   mtformat_module1(Optimize.it,((char*)"`BLUE unsafe typed collect (~S): ~S not in ~S [261]\n"),2,list::alloc(3,_oid_(v62612),
                    GC_OID((*Optimize.c_type)(GC_OID(v62612->arg))),
                    GC_OID((*Kernel.of)(_oid_(v62612)))));
                  else ;{ OID  v4731;
                    { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        _void_(v60472->selector = Core.check_in);
                        _void_(v60472->args = list::alloc(3,_oid_(v8240),
                          _oid_(Kernel._list),
                          GC_OID((*Kernel.of)(_oid_(v62612)))));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                        v4731 = _oid_(close_Instruction1(v60472));
                        }
                      GC_OID(v4731);}
                    Result = (*Optimize.c_code)(v4731,
                      _oid_(Kernel._list));
                    }
                  }
                }
            else Result = _oid_(v8240);
              }
          }
        else { OID  v55513;
            if (INHERIT(v62612->isa,Language._Image))
             v55513 = _oid_(set::empty());
            else v55513 = _oid_(list::empty());
              Variable * v8238 = GC_OBJECT(Variable,Variable_I_symbol(append_symbol(v62612->var->pname,_string_(((char*)"_bag"))),0,((INHERIT(v62612->isa,Language._Image)) ?
              Kernel._set :
              Kernel._list )));
            if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
             mtformat_module1(Optimize.it,((char*)"(~S:~S) v = ~S range = ~S (arg:~S)\n"),5,list::alloc(5,_oid_(v62612),
              _oid_(v62612->isa),
              GC_OID(_oid_(v62612->var)),
              GC_OID(_oid_(v62612->var->range)),
              GC_OID(v62612->arg)));
            else ;if (get_property(Kernel.of,v62612) != CNULL)
             { ClaireType * v47132 = GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->arg))));
              if ((_inf_equal_type(ptype_type(v47132),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.of)(_oid_(v62612))))) != CTRUE) && 
                  ((CL_INT)Optimize.compiler->safety <= (CL_INT)4))
               { warn_void();
                if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
                 mtformat_module1(Optimize.it,((char*)"`BLUE unsafe bag construction (~S) : a ~S is not a ~S [262]\n"),2,list::alloc(3,GC_OID(_oid_(v62612->var)),
                  _oid_(v47132),
                  GC_OID((*Kernel.of)(_oid_(v62612)))));
                else ;}
              (*Kernel.cast_I)(v55513,
                GC_OID((*Kernel.of)(_oid_(v62612))));
              _void_(v8238->range = param_I_class(GC_OBJECT(ClaireClass,((ClaireClass *) v8238->range)),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.of)(_oid_(v62612))))));
              }
            else { if (Kernel._set == OWNER(v55513))
                 { Set * v60472 = ((Set *) GC_OBJECT(Set,new_object_class(Language._Set)));
                  _void_(v60472->of = Kernel.emptySet);
                  add_I_property(Kernel.instances,Language._Set,11,_oid_(v60472));
                  v55513 = _oid_(close_Instruction1(v60472));
                  }
                else { List * v60472 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                    _void_(v60472->of = Kernel.emptySet);
                    add_I_property(Kernel.instances,Language._List,11,_oid_(v60472));
                    v55513 = _oid_(close_Instruction1(v60472));
                    }
                  GC_OID(v55513);}
              { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
              _void_(v60472->var = v8238);
              _void_(v60472->value = v55513);
              { Let * v17052 = v60472; 
                OID  v17053;
                { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                  { Do * v17054 = v60472; 
                    list * v17055;
                    { OID v_bag;
                      GC_ANY(v17055= list::empty(Kernel.emptySet));
                      { { OID  v9536;
                          { { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                              _void_(v60472->var = v62612->var);
                              _void_(v60472->set_arg = v58797);
                              { Iteration * v17057 = v60472; 
                                OID  v17058;
                                { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                  _void_(v60472->selector = Kernel.add_I);
                                  _void_(v60472->args = list::alloc(2,_oid_(v8238),GC_OID(v62612->arg)));
                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                  v17058 = _oid_(close_Instruction1(v60472));
                                  }
                                _void_(v17057->arg = v17058);}
                              add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                              v9536 = _oid_(close_Instruction1(v60472));
                              }
                            GC_OID(v9536);}
                          v_bag = (*Optimize.c_code)(v9536,
                            _oid_(Kernel._any));
                          }
                        GC_OID(v_bag);}
                      ((list *) v17055)->addFast((OID)v_bag);
                      { if (Optimize.OPT->online_ask != CTRUE)
                         { _void_(Optimize.OPT->protection = CTRUE);
                          { Compile_to_protect * v60472 = ((Compile_to_protect *) GC_OBJECT(Compile_to_protect,new_object_class(Optimize._to_protect)));
                            _void_(v60472->arg = _oid_(v8238));
                            add_I_property(Kernel.instances,Optimize._to_protect,11,_oid_(v60472));
                            v_bag = _oid_(close_Instruction1(v60472));
                            }
                          }
                        else v_bag = _oid_(v8238);
                          GC_OID(v_bag);}
                      ((list *) v17055)->addFast((OID)v_bag);}
                    _void_(v17054->args = v17055);}
                  add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                  v17053 = _oid_(close_Instruction1(v60472));
                  }
                _void_(v17052->arg = v17053);}
              add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
              Result = _oid_(close_Instruction1(v60472));
              }
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Select_Optimize(Select *v62612) { 
    POP_SIGNAL; return (c_code_select_Iteration(v62612,Kernel._set));}
  

CL_EXPORT OID  c_code_Lselect_Optimize(Lselect *v62612) { 
    POP_SIGNAL; return (c_code_select_Iteration(v62612,Kernel._list));}
  

CL_EXPORT OID  c_code_select_Iteration(Iteration *v62612,ClaireClass *v8240) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v58797 = GC_OID(v62612->set_arg);
        OID  v56375 = GC_OID((*Optimize.c_type)(v58797));
        OID  v58793 = GC_OID(enumerate_code_any(v58797,OBJECT(ClaireType,v56375)));
        bag * v55513;
        if (v8240 == Kernel._set)
         v55513 = set::empty();
        else v55513 = list::empty();
          Variable * v58819 = GC_OBJECT(Variable,Variable_I_symbol(append_symbol(v62612->var->pname,_string_(((char*)"_in"))),0,Kernel._bag));
        Variable * v58820 = GC_OBJECT(Variable,Variable_I_symbol(append_symbol(v62612->var->pname,_string_(((char*)"_out"))),0,v8240));
        if (get_property(Kernel.of,v62612) != CNULL)
         { ClaireType * v47132 = GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v56375)));
          if ((_inf_equal_type(ptype_type(v47132),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.of)(_oid_(v62612))))) != CTRUE) && 
              ((CL_INT)Optimize.compiler->safety <= (CL_INT)4))
           { warn_void();
            if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
             mtformat_module1(Optimize.it,((char*)"`BLUE unsafe bag construction (~S) : a ~S is not a ~S [262]\n"),2,list::alloc(3,GC_OID(_oid_(v62612->var)),
              _oid_(v47132),
              GC_OID((*Kernel.of)(_oid_(v62612)))));
            else ;}
          _oid_((INHERIT(v55513->isa,Kernel._list) ?
           (ClaireObject *) cast_I_list1((list *) OBJECT(list,_oid_(v55513)),OBJECT(ClaireType,GC_OID((*Kernel.of)(_oid_(v62612))))) : 
           (ClaireObject *)  cast_I_set1((set *) OBJECT(set,_oid_(v55513)),OBJECT(ClaireType,GC_OID((*Kernel.of)(_oid_(v62612)))))));
          _void_(v58820->range = param_I_class(v8240,GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.of)(_oid_(v62612))))));
          Result = inner_select_Iteration(v62612,_oid_(v58820),v58797,_oid_(v55513));
          }
        else if (_inf_equal_type(OBJECT(ClaireType,v56375),v8240) == CTRUE)
         { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
          _void_(v60472->var = v58819);
          _void_(v60472->value = v58793);
          { Let * v17080 = v60472; 
            OID  v17081;
            { OID  v34522;
              { { Compile_C_cast * v60472 = ((Compile_C_cast *) GC_OBJECT(Compile_C_cast,new_object_class(Optimize._C_cast)));
                  { Compile_to_C * v17083 = v60472; 
                    OID  v17084;
                    { OID  v37405;
                      { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          _void_(v60472->selector = Kernel.empty);
                          _void_(v60472->args = list::alloc(1,_oid_(v58819)));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                          v37405 = _oid_(close_Instruction1(v60472));
                          }
                        GC_OID(v37405);}
                      v17084 = (*Optimize.c_code)(v37405,
                        _oid_(Kernel._bag));
                      }
                    _void_(v17083->arg = v17084);}
                  _void_(v60472->set_arg = v8240);
                  add_I_property(Kernel.instances,Optimize._C_cast,11,_oid_(v60472));
                  v34522 = _oid_(close_Instruction1(v60472));
                  }
                GC_OID(v34522);}
              v17081 = inner_select_Iteration(v62612,_oid_(v58820),_oid_(v58819),v34522);
              }
            _void_(v17080->arg = v17081);}
          add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        else { OID  v38366;
            { if (v8240 == Kernel._set)
               { Set * v60472 = ((Set *) GC_OBJECT(Set,new_object_class(Language._Set)));
                _void_(v60472->of = Kernel.emptySet);
                add_I_property(Kernel.instances,Language._Set,11,_oid_(v60472));
                v38366 = _oid_(close_Instruction1(v60472));
                }
              else { List * v60472 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                  _void_(v60472->of = Kernel.emptySet);
                  add_I_property(Kernel.instances,Language._List,11,_oid_(v60472));
                  v38366 = _oid_(close_Instruction1(v60472));
                  }
                GC_OID(v38366);}
            Result = inner_select_Iteration(v62612,_oid_(v58820),v58797,v38366);
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  inner_select_Iteration(Iteration *v62612,OID v58820,OID v58797,OID v55513) { 
    
    GC_BIND;
    { OID Result = 0;
      { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
        store_object(v60472,
          2,
          Kernel._object,
          v58820,
          CFALSE);
        _void_(v60472->value = v55513);
        { Let * v17087 = v60472; 
          OID  v17088;
          { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            { Do * v17089 = v60472; 
              list * v17111;
              { OID v_bag;
                GC_ANY(v17111= list::empty(Kernel.emptySet));
                { { OID  v63353;
                    { { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                        _void_(v60472->var = v62612->var);
                        _void_(v60472->set_arg = v58797);
                        { Iteration * v17113 = v60472; 
                          OID  v17114;
                          { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                            _void_(v60472->test = v62612->arg);
                            { If * v17115 = v60472; 
                              OID  v17116;
                              { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                _void_(v60472->selector = Kernel.add_I);
                                _void_(v60472->args = list::alloc(2,v58820,GC_OID(_oid_(v62612->var))));
                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                v17116 = _oid_(close_Instruction1(v60472));
                                }
                              _void_(v17115->arg = v17116);}
                            add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                            _void_(v60472->other = Kernel.cfalse);
                            v17114 = _oid_(close_Instruction1(v60472));
                            }
                          _void_(v17113->arg = v17114);}
                        add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                        v63353 = _oid_(close_Instruction1(v60472));
                        }
                      GC_OID(v63353);}
                    v_bag = (*Optimize.c_code)(v63353,
                      _oid_(Kernel._any));
                    }
                  GC_OID(v_bag);}
                ((list *) v17111)->addFast((OID)v_bag);
                { if (Optimize.OPT->online_ask != CTRUE)
                   { _void_(Optimize.OPT->protection = CTRUE);
                    { Compile_to_protect * v60472 = ((Compile_to_protect *) GC_OBJECT(Compile_to_protect,new_object_class(Optimize._to_protect)));
                      _void_(v60472->arg = v58820);
                      add_I_property(Kernel.instances,Optimize._to_protect,11,_oid_(v60472));
                      v_bag = _oid_(close_Instruction1(v60472));
                      }
                    }
                  else v_bag = v58820;
                    GC_OID(v_bag);}
                ((list *) v17111)->addFast((OID)v_bag);}
              _void_(v17089->args = v17111);}
            add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
            v17088 = _oid_(close_Instruction1(v60472));
            }
          _void_(v17087->arg = v17088);}
        add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Exists_Optimize(Exists *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { OID  v56375 = GC_OID((*Optimize.c_type)(GC_OID(v62612->set_arg)));
        range_infers_for_Variable(GC_OBJECT(Variable,v62612->var),GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v56375))),OBJECT(ClaireType,v56375));
        if (v62612->other == CNULL)
         Result = extends_type(GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v56375))));
        else Result = Kernel._boolean;
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Exists_Optimize(Exists *v62612,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v56375 = GC_OID((*Optimize.c_type)(GC_OID(v62612->set_arg)));
        range_infers_for_Variable(GC_OBJECT(Variable,v62612->var),GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v56375))),OBJECT(ClaireType,v56375));
        if (v62612->other == Kernel.ctrue)
         { OID  v2621;
          { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(v60472->selector = Core.NOT);
              { Call * v17118 = v60472; 
                list * v17119;
                { OID v_bag;
                  GC_ANY(v17119= list::empty(Kernel.emptySet));
                  { { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                      _void_(v60472->var = v62612->var);
                      _void_(v60472->set_arg = v62612->set_arg);
                      { Iteration * v17120 = v60472; 
                        OID  v17793;
                        { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                          { If * v17794 = v60472; 
                            OID  v17795;
                            { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                              _void_(v60472->selector = Core.NOT);
                              _void_(v60472->args = list::alloc(1,GC_OID(v62612->arg)));
                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                              v17795 = _oid_(close_Instruction1(v60472));
                              }
                            _void_(v17794->test = v17795);}
                          { If * v17796 = v60472; 
                            OID  v17797;
                            { Return * v60472 = ((Return *) GC_OBJECT(Return,new_object_class(Language._Return)));
                              _void_(v60472->arg = Kernel.ctrue);
                              add_I_property(Kernel.instances,Language._Return,11,_oid_(v60472));
                              v17797 = _oid_(close_Instruction1(v60472));
                              }
                            _void_(v17796->arg = v17797);}
                          add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                          _void_(v60472->other = Kernel.cfalse);
                          v17793 = _oid_(close_Instruction1(v60472));
                          }
                        _void_(v17120->arg = v17793);}
                      add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                      v_bag = _oid_(close_Instruction1(v60472));
                      }
                    GC_OID(v_bag);}
                  ((list *) v17119)->addFast((OID)v_bag);}
                _void_(v17118->args = v17119);}
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
              v2621 = _oid_(close_Instruction1(v60472));
              }
            GC_OID(v2621);}
          Result = (*Optimize.c_code)(v2621,
            _oid_(v8235));
          }
        else if (v62612->other == CNULL)
         { Variable * v8238 = GC_OBJECT(Variable,Variable_I_symbol(append_symbol(v62612->var->pname,_string_(((char*)"_some"))),0,GC_OBJECT(ClaireType,extends_type(GC_OBJECT(ClaireType,v62612->var->range)))));
          { OID  v1703;
            { { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                _void_(v60472->var = v8238);
                _void_(v60472->value = CNULL);
                { Let * v17799 = v60472; 
                  OID  v17800;
                  { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                    { Do * v17801 = v60472; 
                      list * v17802;
                      { OID v_bag;
                        GC_ANY(v17802= list::empty(Kernel.emptySet));
                        { { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                            _void_(v60472->var = v62612->var);
                            _void_(v60472->set_arg = v62612->set_arg);
                            { Iteration * v17824 = v60472; 
                              OID  v17825;
                              { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                _void_(v60472->test = v62612->arg);
                                { If * v17827 = v60472; 
                                  OID  v17828;
                                  { Return * v60472 = ((Return *) GC_OBJECT(Return,new_object_class(Language._Return)));
                                    { Return * v17829 = v60472; 
                                      OID  v17830;
                                      { Assign * v60472 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                        _void_(v60472->var = _oid_(v8238));
                                        _void_(v60472->arg = _oid_(v62612->var));
                                        add_I_property(Kernel.instances,Language._Assign,11,_oid_(v60472));
                                        v17830 = _oid_(close_Instruction1(v60472));
                                        }
                                      _void_(v17829->arg = v17830);}
                                    add_I_property(Kernel.instances,Language._Return,11,_oid_(v60472));
                                    v17828 = _oid_(close_Instruction1(v60472));
                                    }
                                  _void_(v17827->arg = v17828);}
                                add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                                _void_(v60472->other = Kernel.cfalse);
                                v17825 = _oid_(close_Instruction1(v60472));
                                }
                              _void_(v17824->arg = v17825);}
                            add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                            v_bag = _oid_(close_Instruction1(v60472));
                            }
                          GC_OID(v_bag);}
                        ((list *) v17802)->addFast((OID)v_bag);
                        ((list *) v17802)->addFast((OID)_oid_(v8238));}
                      _void_(v17801->args = v17802);}
                    add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                    v17800 = _oid_(close_Instruction1(v60472));
                    }
                  _void_(v17799->arg = v17800);}
                add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                v1703 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v1703);}
            Result = (*Optimize.c_code)(v1703,
              _oid_(v8235));
            }
          }
        else { OID  v32454;
            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(v60472->selector = Kernel.boolean_I);
                { Call * v17832 = v60472; 
                  list * v17833;
                  { OID v_bag;
                    GC_ANY(v17833= list::empty(Kernel.emptySet));
                    { { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                        _void_(v60472->var = v62612->var);
                        _void_(v60472->set_arg = v62612->set_arg);
                        { Iteration * v17834 = v60472; 
                          OID  v17855;
                          { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                            _void_(v60472->test = v62612->arg);
                            { If * v17856 = v60472; 
                              OID  v17857;
                              { Return * v60472 = ((Return *) GC_OBJECT(Return,new_object_class(Language._Return)));
                                _void_(v60472->arg = Kernel.ctrue);
                                add_I_property(Kernel.instances,Language._Return,11,_oid_(v60472));
                                v17857 = _oid_(close_Instruction1(v60472));
                                }
                              _void_(v17856->arg = v17857);}
                            add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                            _void_(v60472->other = Kernel.cfalse);
                            v17855 = _oid_(close_Instruction1(v60472));
                            }
                          _void_(v17834->arg = v17855);}
                        add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                        v_bag = _oid_(close_Instruction1(v60472));
                        }
                      GC_OID(v_bag);}
                    ((list *) v17833)->addFast((OID)v_bag);}
                  _void_(v17832->args = v17833);}
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v32454 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v32454);}
            Result = (*Optimize.c_code)(v32454,
              _oid_(v8235));
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Image_Optimize(Image *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { ClaireType * v56375 = GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->set_arg)))));
        range_infers_for_Variable(GC_OBJECT(Variable,v62612->var),GC_OBJECT(ClaireType,pmember_type(v56375)),v56375);
        Result = ((((v62612->of == (NULL)) ? CTRUE : CFALSE) != CTRUE) ?
          param_I_class(Kernel._set,GC_OBJECT(ClaireType,v62612->of)) :
          nth_class1(Kernel._set,GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->arg))))) );
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Select_Optimize(Select *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { OID  v56375 = GC_OID((*Optimize.c_type)(GC_OID(v62612->set_arg)));
        range_infers_for_Variable(GC_OBJECT(Variable,v62612->var),GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v56375))),OBJECT(ClaireType,v56375));
        Result = ((((v62612->of == (NULL)) ? CTRUE : CFALSE) != CTRUE) ?
          param_I_class(Kernel._set,GC_OBJECT(ClaireType,v62612->of)) :
          nth_class1(Kernel._set,GC_OBJECT(ClaireType,pmember_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->set_arg))))))) );
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Lselect_Optimize(Lselect *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { OID  v56375 = GC_OID((*Optimize.c_type)(GC_OID(v62612->set_arg)));
        range_infers_for_Variable(GC_OBJECT(Variable,v62612->var),GC_OBJECT(ClaireType,pmember_type(OBJECT(ClaireType,v56375))),OBJECT(ClaireType,v56375));
        Result = ((((v62612->of == (NULL)) ? CTRUE : CFALSE) != CTRUE) ?
          param_I_class(Kernel._list,GC_OBJECT(ClaireType,v62612->of)) :
          nth_class1(Kernel._list,GC_OBJECT(ClaireType,pmember_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->set_arg))))))) );
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_While_Optimize(While *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      Result = infers_from_type2(GC_OBJECT(ClaireType,return_type_any(GC_OID(v62612->arg))),_oid_(v62612));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_While_Optimize(While *v62612,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireBoolean * v8218 = Optimize.OPT->protection;
        _void_(Optimize.OPT->protection = CFALSE);
        { While * v8234;
          { { Instruction *V_CC ;
              { While * v60472 = ((While *) GC_OBJECT(While,new_object_class(Language._While)));
                _void_(v60472->test = c_boolean_any(GC_OID(v62612->test)));
                _void_(v60472->arg = (*Optimize.c_code)(GC_OID(v62612->arg),
                  _oid_(Kernel._void)));
                _void_(v60472->other = v62612->other);
                add_I_property(Kernel.instances,Language._While,11,_oid_(v60472));
                V_CC = close_Instruction1(v60472);
                }
              v8234= (While *) V_CC;}
            GC_OBJECT(While,v8234);}
          if ((Optimize.OPT->protection == CTRUE) && 
              ((CL_INT)0 <= (CL_INT)Optimize.OPT->max_vars))
           _void_(Optimize.OPT->loop_gc = CTRUE);
          _void_(Optimize.OPT->protection = ((Optimize.OPT->protection == CTRUE) ? CTRUE : ((v8218 == CTRUE) ? CTRUE : CFALSE)));
          if ((v8235 != Kernel._void) && 
              (v8235 != Kernel._any))
           { if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
             mtformat_module1(Optimize.it,((char*)"... insert a to_C with s = ~S for ~S \n"),5,list::alloc(2,_oid_(v8235),_oid_(v62612)));
            else ;{ Compile_to_C * v60472 = ((Compile_to_C *) GC_OBJECT(Compile_to_C,new_object_class(Optimize._to_C)));
              _void_(v60472->arg = _oid_(v8234));
              _void_(v60472->set_arg = v8235);
              add_I_property(Kernel.instances,Optimize._to_C,11,_oid_(v60472));
              Result = _oid_(close_Instruction1(v60472));
              }
            }
          else Result = _oid_(v8234);
            }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  option_respond_string58_Optimize(char *v49259,list *v8228) { 
    (Optimize.NO_FFOR_ask->value= Kernel.ctrue);
    POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string38_Optimize_(char *v17858) { 
    return option_usage_string38_Optimize(v17858)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string38_Optimize(char *v62612) { 
      { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"No ffor construct")),
        _string_(((char*)"-noffor")),
        _string_(((char*)"Compiles ffor instructions without using fork.")));
      return (Result);}
    }
  

CL_EXPORT OID  c_type_Ffor1_Optimize(iClaire_Ffor *v62612) { 
    POP_SIGNAL; return (_oid_(Kernel._list));}
  

CL_EXPORT OID  c_code_Ffor1_Optimize(iClaire_Ffor *v62612,ClaireClass *v58792) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v47973;
        { if (((OBJECT(ClaireBoolean,Optimize.NO_FFOR_ask->value)) == CTRUE) || 
              (unix_ask_void1() != CTRUE))
           { Variable * v51800 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._list));
            Variable * v39880 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Core._ffor_error));
            Variable * v53967 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._any));
            Variable * v8228 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._list));
            Variable * v8225 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._any));
            Variable * v8226 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._any));
            Variable * v30521 = GC_OBJECT(Variable,v62612->var);
            Variable * v8238;
            { { Instruction *V_CC ;
                { Variable * v60472 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                  _void_(v60472->pname = v30521->pname);
                  _void_(v60472->range = v30521->range);
                  _void_(v60472->index = v30521->index);
                  add_I_property(Kernel.instances,Language._Variable,11,_oid_(v60472));
                  V_CC = close_Instruction1(v60472);
                  }
                v8238= (Variable *) V_CC;}
              GC_OBJECT(Variable,v8238);}
            OID  v41072 = GC_OID(substitution_any(GC_OID(v62612->arg),v30521,_oid_(v8238)));
            { OID  v60323;
              { { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                  _void_(v60472->var = v8228);
                  { Let * v17860 = v60472; 
                    OID  v17861;
                    { Collect * v60472 = ((Collect *) GC_OBJECT(Collect,new_object_class(Language._Collect)));
                      _void_(v60472->var = v8225);
                      _void_(v60472->set_arg = v62612->set_arg);
                      _void_(v60472->arg = _oid_(v8225));
                      add_I_property(Kernel.instances,Language._Collect,11,_oid_(v60472));
                      v17861 = _oid_(close_Instruction1(v60472));
                      }
                    _void_(v17860->value = v17861);}
                  { Let * v17862 = v60472; 
                    OID  v17863;
                    { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                      _void_(v60472->var = v51800);
                      { Let * v17864 = v60472; 
                        OID  v17886;
                        { List * v60472 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                          _void_(v60472->of = Kernel._any);
                          add_I_property(Kernel.instances,Language._List,11,_oid_(v60472));
                          v17886 = _oid_(close_Instruction1(v60472));
                          }
                        _void_(v17864->value = v17886);}
                      { Let * v17887 = v60472; 
                        OID  v17888;
                        { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                          _void_(v60472->var = v8238);
                          _void_(v60472->value = CNULL);
                          { Let * v17889 = v60472; 
                            OID  v17890;
                            { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                              { Do * v17891 = v60472; 
                                list * v17892;
                                { OID v_bag;
                                  GC_ANY(v17892= list::empty(Kernel.emptySet));
                                  { { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                                      _void_(v60472->var = v8226);
                                      _void_(v60472->set_arg = _oid_(v8228));
                                      { Iteration * v17893 = v60472; 
                                        OID  v17894;
                                        { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                          { Do * v17895 = v60472; 
                                            list * v17917;
                                            { OID v_bag;
                                              GC_ANY(v17917= list::empty(Kernel.emptySet));
                                              { { Assign * v60472 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                                  _void_(v60472->var = _oid_(v8238));
                                                  _void_(v60472->arg = _oid_(v8226));
                                                  add_I_property(Kernel.instances,Language._Assign,11,_oid_(v60472));
                                                  v_bag = _oid_(close_Instruction1(v60472));
                                                  }
                                                GC_OID(v_bag);}
                                              ((list *) v17917)->addFast((OID)v_bag);
                                              { { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                  _void_(v60472->var = v53967);
                                                  _void_(v60472->value = CNULL);
                                                  { Let * v17918 = v60472; 
                                                    OID  v17919;
                                                    { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                      { Do * v17920 = v60472; 
                                                        list * v17921;
                                                        { OID v_bag;
                                                          GC_ANY(v17921= list::empty(Kernel.emptySet));
                                                          { { Assign * v60472 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                                              _void_(v60472->var = _oid_(v53967));
                                                              { Assign * v17922 = v60472; 
                                                                OID  v17923;
                                                                { ClaireHandle * v60472 = ((ClaireHandle *) GC_OBJECT(ClaireHandle,new_object_class(Language._Handle)));
                                                                  _void_(v60472->test = _oid_(Kernel._any));
                                                                  _void_(v60472->arg = v41072);
                                                                  { ClaireHandle * v17924 = v60472; 
                                                                    OID  v17925;
                                                                    { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                      _void_(v60472->var = v39880);
                                                                      { Let * v17926 = v60472; 
                                                                        OID  v17948;
                                                                        { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                          _void_(v60472->selector = Core.new_I);
                                                                          _void_(v60472->args = list::alloc(1,_oid_(Core._ffor_error)));
                                                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                          v17948 = _oid_(close_Instruction1(v60472));
                                                                          }
                                                                        _void_(v17926->value = v17948);}
                                                                      { Let * v17949 = v60472; 
                                                                        OID  v17950;
                                                                        { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                          { Do * v17951 = v60472; 
                                                                            list * v17952;
                                                                            { OID v_bag;
                                                                              GC_ANY(v17952= list::empty(Kernel.emptySet));
                                                                              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                  _void_(v60472->selector = Kernel.put);
                                                                                  { Call * v17953 = v60472; 
                                                                                    list * v17954;
                                                                                    { OID v_bag;
                                                                                      GC_ANY(v17954= list::empty(Kernel.emptySet));
                                                                                      ((list *) v17954)->addFast((OID)_oid_(Core.childstr));
                                                                                      ((list *) v17954)->addFast((OID)_oid_(v39880));
                                                                                      { { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                          { Do * v17955 = v60472; 
                                                                                            list * v17956;
                                                                                            { OID v_bag;
                                                                                              GC_ANY(v17956= list::empty(Kernel.emptySet));
                                                                                              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                  _void_(v60472->selector = Core.print_in_string);
                                                                                                  _void_(v60472->args = list::alloc(1,_oid_(ClEnv)));
                                                                                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                  v_bag = _oid_(close_Instruction1(v60472));
                                                                                                  }
                                                                                                GC_OID(v_bag);}
                                                                                              ((list *) v17956)->addFast((OID)v_bag);
                                                                                              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                  _void_(v60472->selector = Kernel.print);
                                                                                                  { Call * v17957 = v60472; 
                                                                                                    list * v17979;
                                                                                                    { OID v_bag;
                                                                                                      GC_ANY(v17979= list::empty(Kernel.emptySet));
                                                                                                      { { Call_star * v60472 = ((Call_star *) GC_OBJECT(Call_star,new_object_class(Language._Call_star)));
                                                                                                          _void_(v60472->selector = Kernel.exception_I);
                                                                                                          _void_(v60472->args = list::alloc(1,_oid_(ClEnv)));
                                                                                                          add_I_property(Kernel.instances,Language._Call_star,11,_oid_(v60472));
                                                                                                          v_bag = _oid_(close_Instruction1(v60472));
                                                                                                          }
                                                                                                        GC_OID(v_bag);}
                                                                                                      ((list *) v17979)->addFast((OID)v_bag);}
                                                                                                    _void_(v17957->args = v17979);}
                                                                                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                  v_bag = _oid_(close_Instruction1(v60472));
                                                                                                  }
                                                                                                GC_OID(v_bag);}
                                                                                              ((list *) v17956)->addFast((OID)v_bag);
                                                                                              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                  _void_(v60472->selector = Core.end_of_string);
                                                                                                  _void_(v60472->args = list::alloc(1,_oid_(ClEnv)));
                                                                                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                  v_bag = _oid_(close_Instruction1(v60472));
                                                                                                  }
                                                                                                GC_OID(v_bag);}
                                                                                              ((list *) v17956)->addFast((OID)v_bag);}
                                                                                            _void_(v17955->args = v17956);}
                                                                                          add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                                                          v_bag = _oid_(close_Instruction1(v60472));
                                                                                          }
                                                                                        GC_OID(v_bag);}
                                                                                      ((list *) v17954)->addFast((OID)v_bag);}
                                                                                    _void_(v17953->args = v17954);}
                                                                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                  v_bag = _oid_(close_Instruction1(v60472));
                                                                                  }
                                                                                GC_OID(v_bag);}
                                                                              ((list *) v17952)->addFast((OID)v_bag);
                                                                              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                  _void_(v60472->selector = Kernel.put);
                                                                                  { Call * v17981 = v60472; 
                                                                                    list * v17982;
                                                                                    { OID v_bag;
                                                                                      GC_ANY(v17982= list::empty(Kernel.emptySet));
                                                                                      ((list *) v17982)->addFast((OID)_oid_(Core.childpid));
                                                                                      ((list *) v17982)->addFast((OID)_oid_(v39880));
                                                                                      { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                          _void_(v60472->selector = Kernel.getpid);
                                                                                          _void_(v60472->args = list::alloc(1,_oid_(ClEnv)));
                                                                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                          v_bag = _oid_(close_Instruction1(v60472));
                                                                                          }
                                                                                        GC_OID(v_bag);}
                                                                                      ((list *) v17982)->addFast((OID)v_bag);}
                                                                                    _void_(v17981->args = v17982);}
                                                                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                  v_bag = _oid_(close_Instruction1(v60472));
                                                                                  }
                                                                                GC_OID(v_bag);}
                                                                              ((list *) v17952)->addFast((OID)v_bag);
                                                                              ((list *) v17952)->addFast((OID)_oid_(v39880));}
                                                                            _void_(v17951->args = v17952);}
                                                                          add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                                          v17950 = _oid_(close_Instruction1(v60472));
                                                                          }
                                                                        _void_(v17949->arg = v17950);}
                                                                      add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                                                      v17925 = _oid_(close_Instruction1(v60472));
                                                                      }
                                                                    _void_(v17924->other = v17925);}
                                                                  add_I_property(Kernel.instances,Language._Handle,11,_oid_(v60472));
                                                                  v17923 = _oid_(close_Instruction1(v60472));
                                                                  }
                                                                _void_(v17922->arg = v17923);}
                                                              add_I_property(Kernel.instances,Language._Assign,11,_oid_(v60472));
                                                              v_bag = _oid_(close_Instruction1(v60472));
                                                              }
                                                            GC_OID(v_bag);}
                                                          ((list *) v17921)->addFast((OID)v_bag);
                                                          { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                              _void_(v60472->selector = Kernel.add_I);
                                                              _void_(v60472->args = list::alloc(2,_oid_(v51800),_oid_(v53967)));
                                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                              v_bag = _oid_(close_Instruction1(v60472));
                                                              }
                                                            GC_OID(v_bag);}
                                                          ((list *) v17921)->addFast((OID)v_bag);}
                                                        _void_(v17920->args = v17921);}
                                                      add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                      v17919 = _oid_(close_Instruction1(v60472));
                                                      }
                                                    _void_(v17918->arg = v17919);}
                                                  add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                                  v_bag = _oid_(close_Instruction1(v60472));
                                                  }
                                                GC_OID(v_bag);}
                                              ((list *) v17917)->addFast((OID)v_bag);}
                                            _void_(v17895->args = v17917);}
                                          add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                          v17894 = _oid_(close_Instruction1(v60472));
                                          }
                                        _void_(v17893->arg = v17894);}
                                      add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                                      v_bag = _oid_(close_Instruction1(v60472));
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v17892)->addFast((OID)v_bag);
                                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                      _void_(v60472->selector = Kernel.cast_I);
                                      _void_(v60472->args = list::alloc(2,_oid_(v51800),_oid_(Kernel.emptySet)));
                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                      v_bag = _oid_(close_Instruction1(v60472));
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v17892)->addFast((OID)v_bag);}
                                _void_(v17891->args = v17892);}
                              add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                              v17890 = _oid_(close_Instruction1(v60472));
                              }
                            _void_(v17889->arg = v17890);}
                          add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                          v17888 = _oid_(close_Instruction1(v60472));
                          }
                        _void_(v17887->arg = v17888);}
                      add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                      v17863 = _oid_(close_Instruction1(v60472));
                      }
                    _void_(v17862->arg = v17863);}
                  add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                  v60323 = _oid_(close_Instruction1(v60472));
                  }
                GC_OID(v60323);}
              v47973 = (*Optimize.c_code)(v60323,
                _oid_(v58792));
              }
            }
          else { Variable * v30521 = GC_OBJECT(Variable,v62612->var);
              CL_INT  v58875 = v30521->index;
              Variable * v41503 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._list))));
              Variable * v51800 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._list));
              Variable * v39880 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Core._ffor_error));
              Variable * v53967 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._any));
              Variable * v34627 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._any));
              Variable * v46516 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._integer));
              Variable * v32558 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._integer));
              Variable * v46029 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._integer));
              Variable * v8219 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._list));
              Variable * v58231 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._list));
              Variable * v58728 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Core._socket));
              Variable * v36907 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Core._blob));
              Variable * v49987 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._integer));
              Variable * v13105 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._any));
              Variable * v8235 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,tuple::alloc(2,_oid_(Core._socket),_oid_(Core._socket))));
              Variable * v58726 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Core._socket));
              Variable * v58727 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Core._socket));
              Variable * v58793 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,tuple::alloc(3,_oid_(Core._process_status),
                _oid_(Kernel._integer),
                _oid_(Kernel._any))));
              Variable * v8198 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._integer));
              Variable * v8228 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._list));
              Variable * v8225;
              { { Instruction *V_CC ;
                  { Variable * v60472 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                    _void_(v60472->pname = gensym_void());
                    _void_(v60472->index = 0);
                    add_I_property(Kernel.instances,Language._Variable,11,_oid_(v60472));
                    V_CC = close_Instruction1(v60472);
                    }
                  v8225= (Variable *) V_CC;}
                GC_OBJECT(Variable,v8225);}
              Variable * v8226 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._integer));
              Variable * v8227 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._integer));
              Variable * v8231 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._integer));
              Variable * v8229 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,Kernel._list));
              Variable * v8238;
              { { Instruction *V_CC ;
                  { Variable * v60472 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                    _void_(v60472->pname = v30521->pname);
                    _void_(v60472->range = v30521->range);
                    _void_(v60472->index = v58875);
                    add_I_property(Kernel.instances,Language._Variable,11,_oid_(v60472));
                    V_CC = close_Instruction1(v60472);
                    }
                  v8238= (Variable *) V_CC;}
                GC_OBJECT(Variable,v8238);}
              OID  v41072 = GC_OID(substitution_any(GC_OID(v62612->arg),v30521,_oid_(v8238)));
              if (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v62612->forkedby)))),Kernel._integer) != CTRUE)
               close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Can't compile ~S, ~S does not belong to integer")),
                _oid_(list::alloc(2,_oid_(v62612),GC_OID(v62612->forkedby))))));
              { OID  v47454;
                { { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                    _void_(v60472->var = v8228);
                    { Let * v17984 = v60472; 
                      OID  v17985;
                      { Collect * v60472 = ((Collect *) GC_OBJECT(Collect,new_object_class(Language._Collect)));
                        _void_(v60472->var = v8225);
                        _void_(v60472->set_arg = v62612->set_arg);
                        _void_(v60472->arg = _oid_(v8225));
                        add_I_property(Kernel.instances,Language._Collect,11,_oid_(v60472));
                        v17985 = _oid_(close_Instruction1(v60472));
                        }
                      _void_(v17984->value = v17985);}
                    { Let * v17986 = v60472; 
                      OID  v17987;
                      { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                        _void_(v60472->var = v51800);
                        { Let * v17988 = v60472; 
                          OID  v17991;
                          { OID  v8826;
                            { { List * v60472 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                                _void_(v60472->of = Kernel._any);
                                add_I_property(Kernel.instances,Language._List,11,_oid_(v60472));
                                v8826 = _oid_(close_Instruction1(v60472));
                                }
                              GC_OID(v8826);}
                            v17991 = (*Optimize.c_code)(v8826);
                            }
                          _void_(v17988->value = v17991);}
                        { Let * v18011 = v60472; 
                          OID  v18012;
                          { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                            _void_(v60472->var = v8198);
                            { Let * v18013 = v60472; 
                              OID  v18014;
                              { OID  v13631;
                                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                    _void_(v60472->selector = Core.min);
                                    { Call * v18016 = v60472; 
                                      list * v18017;
                                      { OID v_bag;
                                        GC_ANY(v18017= list::empty(Kernel.emptySet));
                                        { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                            _void_(v60472->selector = Kernel.length);
                                            _void_(v60472->args = list::alloc(1,_oid_(v8228)));
                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                            v_bag = _oid_(close_Instruction1(v60472));
                                            }
                                          GC_OID(v_bag);}
                                        ((list *) v18017)->addFast((OID)v_bag);
                                        ((list *) v18017)->addFast((OID)GC_OID(v62612->forkedby));}
                                      _void_(v18016->args = v18017);}
                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                    v13631 = _oid_(close_Instruction1(v60472));
                                    }
                                  GC_OID(v13631);}
                                v18014 = (*Optimize.c_code)(v13631);
                                }
                              _void_(v18013->value = v18014);}
                            { Let * v18018 = v60472; 
                              OID  v18019;
                              { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                _void_(v60472->var = v8238);
                                _void_(v60472->value = CNULL);
                                { Let * v18041 = v60472; 
                                  OID  v18042;
                                  { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                    _void_(v60472->var = v32558);
                                    _void_(v60472->value = ((OID)1));
                                    { Let * v18043 = v60472; 
                                      OID  v18044;
                                      { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                        _void_(v60472->var = v41503);
                                        { Let * v18045 = v60472; 
                                          OID  v18046;
                                          { Collect * v60472 = ((Collect *) GC_OBJECT(Collect,new_object_class(Language._Collect)));
                                            _void_(v60472->var = v8226);
                                            { Iteration * v18047 = v60472; 
                                              OID  v18048;
                                              { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                _void_(v60472->selector = Kernel._dot_dot);
                                                _void_(v60472->args = list::alloc(2,((OID)1),_oid_(v8198)));
                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                v18048 = _oid_(close_Instruction1(v60472));
                                                }
                                              _void_(v18047->set_arg = v18048);}
                                            { Iteration * v18049 = v60472; 
                                              OID  v18050;
                                              { List * v60472 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                                                _void_(v60472->of = Kernel._any);
                                                { Construct * v18072 = v60472; 
                                                  list * v18073;
                                                  { OID v_bag;
                                                    GC_ANY(v18073= list::empty(Kernel.emptySet));
                                                    ((list *) v18073)->addFast((OID)((OID)-1));
                                                    ((list *) v18073)->addFast((OID)CNULL);
                                                    { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                        _void_(v60472->selector = OBJECT(property,Core.port_I->value));
                                                        _void_(v60472->args = list::alloc(1,_oid_(ClEnv)));
                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                        }
                                                      GC_OID(v_bag);}
                                                    ((list *) v18073)->addFast((OID)v_bag);
                                                    ((list *) v18073)->addFast((OID)CNULL);}
                                                  _void_(v18072->args = v18073);}
                                                add_I_property(Kernel.instances,Language._List,11,_oid_(v60472));
                                                v18050 = _oid_(close_Instruction1(v60472));
                                                }
                                              _void_(v18049->arg = v18050);}
                                            add_I_property(Kernel.instances,Language._Collect,11,_oid_(v60472));
                                            v18046 = _oid_(close_Instruction1(v60472));
                                            }
                                          _void_(v18045->value = v18046);}
                                        { Let * v18074 = v60472; 
                                          OID  v18075;
                                          { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                            _void_(v60472->var = v46516);
                                            { Let * v18076 = v60472; 
                                              OID  v18077;
                                              { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                _void_(v60472->selector = Kernel.length);
                                                _void_(v60472->args = list::alloc(1,_oid_(v8228)));
                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                v18077 = _oid_(close_Instruction1(v60472));
                                                }
                                              _void_(v18076->value = v18077);}
                                            { Let * v18078 = v60472; 
                                              OID  v18079;
                                              { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                _void_(v60472->var = v46029);
                                                _void_(v60472->value = _oid_(v46516));
                                                { Let * v18080 = v60472; 
                                                  OID  v18081;
                                                  { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                    { Do * v18754 = v60472; 
                                                      list * v18755;
                                                      { OID v_bag;
                                                        GC_ANY(v18755= list::empty(Kernel.emptySet));
                                                        { { While * v60472 = ((While *) GC_OBJECT(While,new_object_class(Language._While)));
                                                            { While * v18756 = v60472; 
                                                              OID  v18757;
                                                              { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                _void_(v60472->selector = Kernel._inf);
                                                                { Call * v18758 = v60472; 
                                                                  list * v18759;
                                                                  { OID v_bag;
                                                                    GC_ANY(v18759= list::empty(Kernel.emptySet));
                                                                    { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                        _void_(v60472->selector = Kernel.length);
                                                                        _void_(v60472->args = list::alloc(1,_oid_(v51800)));
                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                        }
                                                                      GC_OID(v_bag);}
                                                                    ((list *) v18759)->addFast((OID)v_bag);
                                                                    ((list *) v18759)->addFast((OID)_oid_(v46029));}
                                                                  _void_(v18758->args = v18759);}
                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                v18757 = _oid_(close_Instruction1(v60472));
                                                                }
                                                              _void_(v18756->test = v18757);}
                                                            { While * v18760 = v60472; 
                                                              OID  v18761;
                                                              { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                { Do * v18763 = v60472; 
                                                                  list * v18764;
                                                                  { OID v_bag;
                                                                    GC_ANY(v18764= list::empty(Kernel.emptySet));
                                                                    { { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                                        { If * v18785 = v60472; 
                                                                          OID  v18786;
                                                                          { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                            _void_(v60472->selector = Kernel._sup);
                                                                            _void_(v60472->args = list::alloc(2,_oid_(v46516),((OID)0)));
                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                            v18786 = _oid_(close_Instruction1(v60472));
                                                                            }
                                                                          _void_(v18785->test = v18786);}
                                                                        { If * v18787 = v60472; 
                                                                          OID  v18788;
                                                                          { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                                                                            _void_(v60472->var = v8227);
                                                                            { Iteration * v18789 = v60472; 
                                                                              OID  v18790;
                                                                              { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                _void_(v60472->selector = Kernel._dot_dot);
                                                                                _void_(v60472->args = list::alloc(2,((OID)1),_oid_(v8198)));
                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                v18790 = _oid_(close_Instruction1(v60472));
                                                                                }
                                                                              _void_(v18789->set_arg = v18790);}
                                                                            { Iteration * v18791 = v60472; 
                                                                              OID  v18792;
                                                                              { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                { Do * v18793 = v60472; 
                                                                                  list * v18794;
                                                                                  { OID v_bag;
                                                                                    GC_ANY(v18794= list::empty(Kernel.emptySet));
                                                                                    { { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                                                        { If * v18816 = v60472; 
                                                                                          OID  v18817;
                                                                                          { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                            _void_(v60472->selector = Kernel._equal);
                                                                                            _void_(v60472->args = list::alloc(2,_oid_(v46516),((OID)0)));
                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                            v18817 = _oid_(close_Instruction1(v60472));
                                                                                            }
                                                                                          _void_(v18816->test = v18817);}
                                                                                        { If * v18818 = v60472; 
                                                                                          OID  v18819;
                                                                                          { Return * v60472 = ((Return *) GC_OBJECT(Return,new_object_class(Language._Return)));
                                                                                            _void_(v60472->arg = Kernel.ctrue);
                                                                                            add_I_property(Kernel.instances,Language._Return,11,_oid_(v60472));
                                                                                            v18819 = _oid_(close_Instruction1(v60472));
                                                                                            }
                                                                                          _void_(v18818->arg = v18819);}
                                                                                        add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                                                                                        _void_(v60472->other = Kernel.cfalse);
                                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                                        }
                                                                                      GC_OID(v_bag);}
                                                                                    ((list *) v18794)->addFast((OID)v_bag);
                                                                                    { { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                                                        { If * v18820 = v60472; 
                                                                                          OID  v18821;
                                                                                          { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                            _void_(v60472->selector = Kernel._equal);
                                                                                            { Call * v18822 = v60472; 
                                                                                              list * v18823;
                                                                                              { OID v_bag;
                                                                                                GC_ANY(v18823= list::empty(Kernel.emptySet));
                                                                                                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                    _void_(v60472->selector = Kernel.nth);
                                                                                                    { Call * v18824 = v60472; 
                                                                                                      list * v18825;
                                                                                                      { OID v_bag;
                                                                                                        GC_ANY(v18825= list::empty(Kernel.emptySet));
                                                                                                        { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                            _void_(v60472->selector = Kernel.nth);
                                                                                                            _void_(v60472->args = list::alloc(2,_oid_(v41503),_oid_(v8227)));
                                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                            v_bag = _oid_(close_Instruction1(v60472));
                                                                                                            }
                                                                                                          GC_OID(v_bag);}
                                                                                                        ((list *) v18825)->addFast((OID)v_bag);
                                                                                                        ((list *) v18825)->addFast((OID)((OID)1));}
                                                                                                      _void_(v18824->args = v18825);}
                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                    v_bag = _oid_(close_Instruction1(v60472));
                                                                                                    }
                                                                                                  GC_OID(v_bag);}
                                                                                                ((list *) v18823)->addFast((OID)v_bag);
                                                                                                ((list *) v18823)->addFast((OID)((OID)-1));}
                                                                                              _void_(v18822->args = v18823);}
                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                            v18821 = _oid_(close_Instruction1(v60472));
                                                                                            }
                                                                                          _void_(v18820->test = v18821);}
                                                                                        { If * v18847 = v60472; 
                                                                                          OID  v18848;
                                                                                          { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                            _void_(v60472->var = v13105);
                                                                                            { Let * v18849 = v60472; 
                                                                                              OID  v18850;
                                                                                              { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                _void_(v60472->selector = Kernel.nth);
                                                                                                _void_(v60472->args = list::alloc(2,_oid_(v8228),_oid_(v32558)));
                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                v18850 = _oid_(close_Instruction1(v60472));
                                                                                                }
                                                                                              _void_(v18849->value = v18850);}
                                                                                            { Let * v18851 = v60472; 
                                                                                              OID  v18852;
                                                                                              { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                { Do * v18853 = v60472; 
                                                                                                  list * v18854;
                                                                                                  { OID v_bag;
                                                                                                    GC_ANY(v18854= list::empty(Kernel.emptySet));
                                                                                                    { { Assign * v60472 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                                                                                        _void_(v60472->var = _oid_(v8238));
                                                                                                        _void_(v60472->arg = _oid_(v13105));
                                                                                                        add_I_property(Kernel.instances,Language._Assign,11,_oid_(v60472));
                                                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                                                        }
                                                                                                      GC_OID(v_bag);}
                                                                                                    ((list *) v18854)->addFast((OID)v_bag);
                                                                                                    { { ClaireHandle * v60472 = ((ClaireHandle *) GC_OBJECT(ClaireHandle,new_object_class(Language._Handle)));
                                                                                                        _void_(v60472->test = _oid_(Kernel._any));
                                                                                                        { ClaireHandle * v18855 = v60472; 
                                                                                                          OID  v18856;
                                                                                                          { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                                            _void_(v60472->var = v8235);
                                                                                                            { Let * v18878 = v60472; 
                                                                                                              OID  v18879;
                                                                                                              { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                _void_(v60472->selector = Core.socketpair);
                                                                                                                _void_(v60472->args = list::alloc(1,_oid_(ClEnv)));
                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                v18879 = _oid_(close_Instruction1(v60472));
                                                                                                                }
                                                                                                              _void_(v18878->value = v18879);}
                                                                                                            { Let * v18880 = v60472; 
                                                                                                              OID  v18881;
                                                                                                              { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                                                _void_(v60472->var = v58726);
                                                                                                                { Let * v18882 = v60472; 
                                                                                                                  OID  v18883;
                                                                                                                  { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                    _void_(v60472->selector = Kernel.nth);
                                                                                                                    _void_(v60472->args = list::alloc(2,_oid_(v8235),((OID)1)));
                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                    v18883 = _oid_(close_Instruction1(v60472));
                                                                                                                    }
                                                                                                                  _void_(v18882->value = v18883);}
                                                                                                                { Let * v18884 = v60472; 
                                                                                                                  OID  v18885;
                                                                                                                  { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                                                    _void_(v60472->var = v58727);
                                                                                                                    { Let * v18886 = v60472; 
                                                                                                                      OID  v18887;
                                                                                                                      { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                        _void_(v60472->selector = Kernel.nth);
                                                                                                                        _void_(v60472->args = list::alloc(2,_oid_(v8235),((OID)2)));
                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                        v18887 = _oid_(close_Instruction1(v60472));
                                                                                                                        }
                                                                                                                      _void_(v18886->value = v18887);}
                                                                                                                    { Let * v18909 = v60472; 
                                                                                                                      OID  v18910;
                                                                                                                      { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                                                                                        { If * v18911 = v60472; 
                                                                                                                          OID  v18912;
                                                                                                                          { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                            _void_(v60472->selector = Core.forker_ask);
                                                                                                                            _void_(v60472->args = list::alloc(1,_oid_(ClEnv)));
                                                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                            v18912 = _oid_(close_Instruction1(v60472));
                                                                                                                            }
                                                                                                                          _void_(v18911->test = v18912);}
                                                                                                                        { If * v18913 = v60472; 
                                                                                                                          OID  v18914;
                                                                                                                          { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                                                            _void_(v60472->var = v8219);
                                                                                                                            { Let * v18915 = v60472; 
                                                                                                                              OID  v18916;
                                                                                                                              { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                _void_(v60472->selector = Kernel.nth);
                                                                                                                                _void_(v60472->args = list::alloc(2,_oid_(v41503),_oid_(v8227)));
                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                v18916 = _oid_(close_Instruction1(v60472));
                                                                                                                                }
                                                                                                                              _void_(v18915->value = v18916);}
                                                                                                                            { Let * v18917 = v60472; 
                                                                                                                              OID  v18919;
                                                                                                                              { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                                                { Do * v18940 = v60472; 
                                                                                                                                  list * v18941;
                                                                                                                                  { OID v_bag;
                                                                                                                                    GC_ANY(v18941= list::empty(Kernel.emptySet));
                                                                                                                                    { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                        _void_(v60472->selector = Core.fclose);
                                                                                                                                        _void_(v60472->args = list::alloc(1,_oid_(v58726)));
                                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                        }
                                                                                                                                      GC_OID(v_bag);}
                                                                                                                                    ((list *) v18941)->addFast((OID)v_bag);
                                                                                                                                    { { Assign * v60472 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                                                                                                                        _void_(v60472->var = _oid_(v46516));
                                                                                                                                        { Assign * v18942 = v60472; 
                                                                                                                                          OID  v18943;
                                                                                                                                          { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                            _void_(v60472->selector = Kernel._dash);
                                                                                                                                            _void_(v60472->args = list::alloc(2,_oid_(v46516),((OID)1)));
                                                                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                            v18943 = _oid_(close_Instruction1(v60472));
                                                                                                                                            }
                                                                                                                                          _void_(v18942->arg = v18943);}
                                                                                                                                        add_I_property(Kernel.instances,Language._Assign,11,_oid_(v60472));
                                                                                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                        }
                                                                                                                                      GC_OID(v_bag);}
                                                                                                                                    ((list *) v18941)->addFast((OID)v_bag);
                                                                                                                                    { { Assign * v60472 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                                                                                                                        _void_(v60472->var = _oid_(v32558));
                                                                                                                                        { Assign * v18944 = v60472; 
                                                                                                                                          OID  v18945;
                                                                                                                                          { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                            _void_(v60472->selector = Core._plus);
                                                                                                                                            _void_(v60472->args = list::alloc(2,_oid_(v32558),((OID)1)));
                                                                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                            v18945 = _oid_(close_Instruction1(v60472));
                                                                                                                                            }
                                                                                                                                          _void_(v18944->arg = v18945);}
                                                                                                                                        add_I_property(Kernel.instances,Language._Assign,11,_oid_(v60472));
                                                                                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                        }
                                                                                                                                      GC_OID(v_bag);}
                                                                                                                                    ((list *) v18941)->addFast((OID)v_bag);
                                                                                                                                    { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                        _void_(v60472->selector = Kernel.nth_equal);
                                                                                                                                        { Call * v18946 = v60472; 
                                                                                                                                          list * v18947;
                                                                                                                                          { OID v_bag;
                                                                                                                                            GC_ANY(v18947= list::empty(Kernel.emptySet));
                                                                                                                                            ((list *) v18947)->addFast((OID)_oid_(v8219));
                                                                                                                                            ((list *) v18947)->addFast((OID)((OID)1));
                                                                                                                                            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                _void_(v60472->selector = Kernel.forked);
                                                                                                                                                _void_(v60472->args = list::alloc(1,_oid_(ClEnv)));
                                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                                v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                                }
                                                                                                                                              GC_OID(v_bag);}
                                                                                                                                            ((list *) v18947)->addFast((OID)v_bag);}
                                                                                                                                          _void_(v18946->args = v18947);}
                                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                        }
                                                                                                                                      GC_OID(v_bag);}
                                                                                                                                    ((list *) v18941)->addFast((OID)v_bag);
                                                                                                                                    { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                        _void_(v60472->selector = Kernel.nth_equal);
                                                                                                                                        _void_(v60472->args = list::alloc(3,_oid_(v8219),
                                                                                                                                          ((OID)2),
                                                                                                                                          _oid_(v58727)));
                                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                        }
                                                                                                                                      GC_OID(v_bag);}
                                                                                                                                    ((list *) v18941)->addFast((OID)v_bag);
                                                                                                                                    { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                        _void_(v60472->selector = Kernel.nth_equal);
                                                                                                                                        _void_(v60472->args = list::alloc(3,_oid_(v8219),
                                                                                                                                          ((OID)4),
                                                                                                                                          _oid_(v13105)));
                                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                        }
                                                                                                                                      GC_OID(v_bag);}
                                                                                                                                    ((list *) v18941)->addFast((OID)v_bag);}
                                                                                                                                  _void_(v18940->args = v18941);}
                                                                                                                                add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                                                                                                v18919 = _oid_(close_Instruction1(v60472));
                                                                                                                                }
                                                                                                                              _void_(v18917->arg = v18919);}
                                                                                                                            add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                                                                                                            v18914 = _oid_(close_Instruction1(v60472));
                                                                                                                            }
                                                                                                                          _void_(v18913->arg = v18914);}
                                                                                                                        { If * v18948 = v60472; 
                                                                                                                          OID  v18949;
                                                                                                                          { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                                            { Do * v18971 = v60472; 
                                                                                                                              list * v18972;
                                                                                                                              { OID v_bag;
                                                                                                                                GC_ANY(v18972= list::empty(Kernel.emptySet));
                                                                                                                                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                    _void_(v60472->selector = Core.fclose);
                                                                                                                                    _void_(v60472->args = list::alloc(1,_oid_(v58727)));
                                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                    v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                    }
                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                ((list *) v18972)->addFast((OID)v_bag);
                                                                                                                                { { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                                                                    _void_(v60472->var = v53967);
                                                                                                                                    _void_(v60472->value = CNULL);
                                                                                                                                    { Let * v18973 = v60472; 
                                                                                                                                      OID  v18974;
                                                                                                                                      { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                                                        { Do * v18975 = v60472; 
                                                                                                                                          list * v18976;
                                                                                                                                          { OID v_bag;
                                                                                                                                            GC_ANY(v18976= list::empty(Kernel.emptySet));
                                                                                                                                            { { Assign * v60472 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                                                                                                                                _void_(v60472->var = _oid_(v53967));
                                                                                                                                                { Assign * v18977 = v60472; 
                                                                                                                                                  OID  v18978;
                                                                                                                                                  { ClaireHandle * v60472 = ((ClaireHandle *) GC_OBJECT(ClaireHandle,new_object_class(Language._Handle)));
                                                                                                                                                    _void_(v60472->test = _oid_(Kernel._any));
                                                                                                                                                    { ClaireHandle * v18979 = v60472; 
                                                                                                                                                      OID  v18980;
                                                                                                                                                      if ((*Optimize.c_type)(v41072) == _oid_(Kernel._void))
                                                                                                                                                       { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                                                                        _void_(v60472->args = list::alloc(2,v41072,CNULL));
                                                                                                                                                        add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                                                                                                                        v18980 = _oid_(close_Instruction1(v60472));
                                                                                                                                                        }
                                                                                                                                                      else v18980 = v41072;
                                                                                                                                                        _void_(v18979->arg = v18980);}
                                                                                                                                                    { ClaireHandle * v19003 = v60472; 
                                                                                                                                                      OID  v19004;
                                                                                                                                                      { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                                                                        { Do * v19005 = v60472; 
                                                                                                                                                          list * v19006;
                                                                                                                                                          { OID v_bag;
                                                                                                                                                            GC_ANY(v19006= list::empty(Kernel.emptySet));
                                                                                                                                                            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                                _void_(v60472->selector = Core.exit);
                                                                                                                                                                _void_(v60472->args = list::alloc(1,((OID)1)));
                                                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                                                v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                                                }
                                                                                                                                                              GC_OID(v_bag);}
                                                                                                                                                            ((list *) v19006)->addFast((OID)v_bag);}
                                                                                                                                                          _void_(v19005->args = v19006);}
                                                                                                                                                        add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                                                                                                                        v19004 = _oid_(close_Instruction1(v60472));
                                                                                                                                                        }
                                                                                                                                                      _void_(v19003->other = v19004);}
                                                                                                                                                    add_I_property(Kernel.instances,Language._Handle,11,_oid_(v60472));
                                                                                                                                                    v18978 = _oid_(close_Instruction1(v60472));
                                                                                                                                                    }
                                                                                                                                                  _void_(v18977->arg = v18978);}
                                                                                                                                                add_I_property(Kernel.instances,Language._Assign,11,_oid_(v60472));
                                                                                                                                                v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                                }
                                                                                                                                              GC_OID(v_bag);}
                                                                                                                                            ((list *) v18976)->addFast((OID)v_bag);
                                                                                                                                            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                _void_(v60472->selector = Serialize.serialize);
                                                                                                                                                _void_(v60472->args = list::alloc(2,_oid_(v58726),_oid_(v53967)));
                                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                                v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                                }
                                                                                                                                              GC_OID(v_bag);}
                                                                                                                                            ((list *) v18976)->addFast((OID)v_bag);}
                                                                                                                                          _void_(v18975->args = v18976);}
                                                                                                                                        add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                                                                                                        v18974 = _oid_(close_Instruction1(v60472));
                                                                                                                                        }
                                                                                                                                      _void_(v18973->arg = v18974);}
                                                                                                                                    add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                                                                                                                    v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                    }
                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                ((list *) v18972)->addFast((OID)v_bag);
                                                                                                                                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                    _void_(v60472->selector = Core.fclose);
                                                                                                                                    _void_(v60472->args = list::alloc(1,_oid_(v58726)));
                                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                    v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                    }
                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                ((list *) v18972)->addFast((OID)v_bag);
                                                                                                                                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                    _void_(v60472->selector = Core.exit);
                                                                                                                                    _void_(v60472->args = list::alloc(1,((OID)0)));
                                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                    v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                    }
                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                ((list *) v18972)->addFast((OID)v_bag);}
                                                                                                                              _void_(v18971->args = v18972);}
                                                                                                                            add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                                                                                            v18949 = _oid_(close_Instruction1(v60472));
                                                                                                                            }
                                                                                                                          _void_(v18948->other = v18949);}
                                                                                                                        add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                                                                                                                        v18910 = _oid_(close_Instruction1(v60472));
                                                                                                                        }
                                                                                                                      _void_(v18909->arg = v18910);}
                                                                                                                    add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                                                                                                    v18885 = _oid_(close_Instruction1(v60472));
                                                                                                                    }
                                                                                                                  _void_(v18884->arg = v18885);}
                                                                                                                add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                                                                                                v18881 = _oid_(close_Instruction1(v60472));
                                                                                                                }
                                                                                                              _void_(v18880->arg = v18881);}
                                                                                                            add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                                                                                            v18856 = _oid_(close_Instruction1(v60472));
                                                                                                            }
                                                                                                          _void_(v18855->arg = v18856);}
                                                                                                        add_I_property(Kernel.instances,Language._Handle,11,_oid_(v60472));
                                                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                                                        }
                                                                                                      GC_OID(v_bag);}
                                                                                                    ((list *) v18854)->addFast((OID)v_bag);}
                                                                                                  _void_(v18853->args = v18854);}
                                                                                                add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                                                                v18852 = _oid_(close_Instruction1(v60472));
                                                                                                }
                                                                                              _void_(v18851->arg = v18852);}
                                                                                            add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                                                                            v18848 = _oid_(close_Instruction1(v60472));
                                                                                            }
                                                                                          _void_(v18847->arg = v18848);}
                                                                                        add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                                                                                        _void_(v60472->other = Kernel.cfalse);
                                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                                        }
                                                                                      GC_OID(v_bag);}
                                                                                    ((list *) v18794)->addFast((OID)v_bag);}
                                                                                  _void_(v18793->args = v18794);}
                                                                                add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                                                v18792 = _oid_(close_Instruction1(v60472));
                                                                                }
                                                                              _void_(v18791->arg = v18792);}
                                                                            add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                                                                            v18788 = _oid_(close_Instruction1(v60472));
                                                                            }
                                                                          _void_(v18787->arg = v18788);}
                                                                        add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                                                                        _void_(v60472->other = Kernel.cfalse);
                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                        }
                                                                      GC_OID(v_bag);}
                                                                    ((list *) v18764)->addFast((OID)v_bag);
                                                                    { { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                                                                        _void_(v60472->var = v8231);
                                                                        { Iteration * v19007 = v60472; 
                                                                          OID  v19008;
                                                                          { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                            _void_(v60472->selector = Kernel._dot_dot);
                                                                            _void_(v60472->args = list::alloc(2,((OID)1),_oid_(v8198)));
                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                            v19008 = _oid_(close_Instruction1(v60472));
                                                                            }
                                                                          _void_(v19007->set_arg = v19008);}
                                                                        { Iteration * v19009 = v60472; 
                                                                          OID  v19010;
                                                                          { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                            _void_(v60472->var = v58231);
                                                                            { Let * v19011 = v60472; 
                                                                              OID  v19012;
                                                                              { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                _void_(v60472->selector = Kernel.nth);
                                                                                _void_(v60472->args = list::alloc(2,_oid_(v41503),_oid_(v8231)));
                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                v19012 = _oid_(close_Instruction1(v60472));
                                                                                }
                                                                              _void_(v19011->value = v19012);}
                                                                            { Let * v19034 = v60472; 
                                                                              OID  v19035;
                                                                              { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                _void_(v60472->var = v58728);
                                                                                { Let * v19036 = v60472; 
                                                                                  OID  v19037;
                                                                                  { Cast * v60472 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                                                                                    { Cast * v19038 = v60472; 
                                                                                      OID  v19039;
                                                                                      { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                        _void_(v60472->selector = Kernel.nth);
                                                                                        _void_(v60472->args = list::alloc(2,_oid_(v58231),((OID)2)));
                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                        v19039 = _oid_(close_Instruction1(v60472));
                                                                                        }
                                                                                      _void_(v19038->arg = v19039);}
                                                                                    _void_(v60472->set_arg = Core._socket);
                                                                                    add_I_property(Kernel.instances,Language._Cast,11,_oid_(v60472));
                                                                                    v19037 = _oid_(close_Instruction1(v60472));
                                                                                    }
                                                                                  _void_(v19036->value = v19037);}
                                                                                { Let * v19041 = v60472; 
                                                                                  OID  v19042;
                                                                                  { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                    _void_(v60472->var = v49987);
                                                                                    { Let * v19043 = v60472; 
                                                                                      OID  v19044;
                                                                                      { Cast * v60472 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                                                                                        { Cast * v19715 = v60472; 
                                                                                          OID  v19716;
                                                                                          { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                            _void_(v60472->selector = Kernel.nth);
                                                                                            _void_(v60472->args = list::alloc(2,_oid_(v58231),((OID)1)));
                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                            v19716 = _oid_(close_Instruction1(v60472));
                                                                                            }
                                                                                          _void_(v19715->arg = v19716);}
                                                                                        _void_(v60472->set_arg = Kernel._integer);
                                                                                        add_I_property(Kernel.instances,Language._Cast,11,_oid_(v60472));
                                                                                        v19044 = _oid_(close_Instruction1(v60472));
                                                                                        }
                                                                                      _void_(v19043->value = v19044);}
                                                                                    { Let * v19717 = v60472; 
                                                                                      OID  v19718;
                                                                                      { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                        _void_(v60472->var = v36907);
                                                                                        { Let * v19719 = v60472; 
                                                                                          OID  v19720;
                                                                                          { Cast * v60472 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                                                                                            { Cast * v19722 = v60472; 
                                                                                              OID  v19723;
                                                                                              { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                _void_(v60472->selector = Kernel.nth);
                                                                                                _void_(v60472->args = list::alloc(2,_oid_(v58231),((OID)3)));
                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                v19723 = _oid_(close_Instruction1(v60472));
                                                                                                }
                                                                                              _void_(v19722->arg = v19723);}
                                                                                            _void_(v60472->set_arg = Core._blob);
                                                                                            add_I_property(Kernel.instances,Language._Cast,11,_oid_(v60472));
                                                                                            v19720 = _oid_(close_Instruction1(v60472));
                                                                                            }
                                                                                          _void_(v19719->value = v19720);}
                                                                                        { Let * v19724 = v60472; 
                                                                                          OID  v19725;
                                                                                          { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                                                            { If * v19746 = v60472; 
                                                                                              OID  v19747;
                                                                                              { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                _void_(v60472->selector = Core._I_equal);
                                                                                                _void_(v60472->args = list::alloc(2,_oid_(v49987),((OID)-1)));
                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                v19747 = _oid_(close_Instruction1(v60472));
                                                                                                }
                                                                                              _void_(v19746->test = v19747);}
                                                                                            { If * v19748 = v60472; 
                                                                                              OID  v19749;
                                                                                              { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                { Do * v19750 = v60472; 
                                                                                                  list * v19751;
                                                                                                  { OID v_bag;
                                                                                                    GC_ANY(v19751= list::empty(Kernel.emptySet));
                                                                                                    { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                        _void_(v60472->selector = Core.read_I);
                                                                                                        _void_(v60472->args = list::alloc(1,_oid_(v58728)));
                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                                                        }
                                                                                                      GC_OID(v_bag);}
                                                                                                    ((list *) v19751)->addFast((OID)v_bag);
                                                                                                    { { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                                                                        { If * v19752 = v60472; 
                                                                                                          OID  v19753;
                                                                                                          { And * v60472 = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
                                                                                                            { And * v19754 = v60472; 
                                                                                                              list * v19755;
                                                                                                              { OID v_bag;
                                                                                                                GC_ANY(v19755= list::empty(Kernel.emptySet));
                                                                                                                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                    _void_(v60472->selector = Core.select_ask);
                                                                                                                    _void_(v60472->args = list::alloc(1,((OID)10)));
                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                    v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                    }
                                                                                                                  GC_OID(v_bag);}
                                                                                                                ((list *) v19755)->addFast((OID)v_bag);
                                                                                                                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                    _void_(v60472->selector = Core.readable_ask);
                                                                                                                    _void_(v60472->args = list::alloc(1,_oid_(v58728)));
                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                    v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                    }
                                                                                                                  GC_OID(v_bag);}
                                                                                                                ((list *) v19755)->addFast((OID)v_bag);}
                                                                                                              _void_(v19754->args = v19755);}
                                                                                                            add_I_property(Kernel.instances,Language._And,11,_oid_(v60472));
                                                                                                            v19753 = _oid_(close_Instruction1(v60472));
                                                                                                            }
                                                                                                          _void_(v19752->test = v19753);}
                                                                                                        { If * v19777 = v60472; 
                                                                                                          OID  v19778;
                                                                                                          { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                            { Do * v19779 = v60472; 
                                                                                                              list * v19780;
                                                                                                              { OID v_bag;
                                                                                                                GC_ANY(v19780= list::empty(Kernel.emptySet));
                                                                                                                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                    _void_(v60472->selector = Kernel.fwrite);
                                                                                                                    { Call * v19781 = v60472; 
                                                                                                                      list * v19782;
                                                                                                                      { OID v_bag;
                                                                                                                        GC_ANY(v19782= list::empty(Kernel.emptySet));
                                                                                                                        { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                            _void_(v60472->selector = Kernel.fread);
                                                                                                                            _void_(v60472->args = list::alloc(2,_oid_(v58728),((OID)1024)));
                                                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                            v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                            }
                                                                                                                          GC_OID(v_bag);}
                                                                                                                        ((list *) v19782)->addFast((OID)v_bag);
                                                                                                                        ((list *) v19782)->addFast((OID)_oid_(v36907));}
                                                                                                                      _void_(v19781->args = v19782);}
                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                    v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                    }
                                                                                                                  GC_OID(v_bag);}
                                                                                                                ((list *) v19780)->addFast((OID)v_bag);
                                                                                                                { { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                                                                                    { If * v19783 = v60472; 
                                                                                                                      OID  v19784;
                                                                                                                      { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                        _void_(v60472->selector = Core.eof_ask);
                                                                                                                        _void_(v60472->args = list::alloc(1,_oid_(v58728)));
                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                        v19784 = _oid_(close_Instruction1(v60472));
                                                                                                                        }
                                                                                                                      _void_(v19783->test = v19784);}
                                                                                                                    { If * v19785 = v60472; 
                                                                                                                      OID  v19786;
                                                                                                                      { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                                                        _void_(v60472->var = v58793);
                                                                                                                        { Let * v19808 = v60472; 
                                                                                                                          OID  v19809;
                                                                                                                          { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                            _void_(v60472->selector = Core.waitpid);
                                                                                                                            _void_(v60472->args = list::alloc(1,_oid_(v49987)));
                                                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                            v19809 = _oid_(close_Instruction1(v60472));
                                                                                                                            }
                                                                                                                          _void_(v19808->value = v19809);}
                                                                                                                        { Let * v19810 = v60472; 
                                                                                                                          OID  v19811;
                                                                                                                          { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                                            { Do * v19812 = v60472; 
                                                                                                                              list * v19813;
                                                                                                                              { OID v_bag;
                                                                                                                                GC_ANY(v19813= list::empty(Kernel.emptySet));
                                                                                                                                { { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                                                                                                    { If * v19814 = v60472; 
                                                                                                                                      OID  v19816;
                                                                                                                                      { And * v60472 = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
                                                                                                                                        { And * v19817 = v60472; 
                                                                                                                                          list * v19819;
                                                                                                                                          { OID v_bag;
                                                                                                                                            GC_ANY(v19819= list::empty(Kernel.emptySet));
                                                                                                                                            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                _void_(v60472->selector = Kernel._equal);
                                                                                                                                                { Call * v19839 = v60472; 
                                                                                                                                                  list * v19840;
                                                                                                                                                  { OID v_bag;
                                                                                                                                                    GC_ANY(v19840= list::empty(Kernel.emptySet));
                                                                                                                                                    { { Cast * v60472 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                                                                                                                                                        { Cast * v19841 = v60472; 
                                                                                                                                                          OID  v19842;
                                                                                                                                                          { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                            _void_(v60472->selector = Kernel.nth);
                                                                                                                                                            _void_(v60472->args = list::alloc(2,_oid_(v58793),((OID)1)));
                                                                                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                                            v19842 = _oid_(close_Instruction1(v60472));
                                                                                                                                                            }
                                                                                                                                                          _void_(v19841->arg = v19842);}
                                                                                                                                                        _void_(v60472->set_arg = Core._process_status);
                                                                                                                                                        add_I_property(Kernel.instances,Language._Cast,11,_oid_(v60472));
                                                                                                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                                        }
                                                                                                                                                      GC_OID(v_bag);}
                                                                                                                                                    ((list *) v19840)->addFast((OID)v_bag);
                                                                                                                                                    ((list *) v19840)->addFast((OID)_oid_(Core.CL_WEXITED));}
                                                                                                                                                  _void_(v19839->args = v19840);}
                                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                                v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                                }
                                                                                                                                              GC_OID(v_bag);}
                                                                                                                                            ((list *) v19819)->addFast((OID)v_bag);
                                                                                                                                            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                _void_(v60472->selector = Kernel._equal);
                                                                                                                                                { Call * v19843 = v60472; 
                                                                                                                                                  list * v19844;
                                                                                                                                                  { OID v_bag;
                                                                                                                                                    GC_ANY(v19844= list::empty(Kernel.emptySet));
                                                                                                                                                    { { Cast * v60472 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                                                                                                                                                        { Cast * v19845 = v60472; 
                                                                                                                                                          OID  v19846;
                                                                                                                                                          { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                            _void_(v60472->selector = Kernel.nth);
                                                                                                                                                            _void_(v60472->args = list::alloc(2,_oid_(v58793),((OID)3)));
                                                                                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                                            v19846 = _oid_(close_Instruction1(v60472));
                                                                                                                                                            }
                                                                                                                                                          _void_(v19845->arg = v19846);}
                                                                                                                                                        _void_(v60472->set_arg = Kernel._integer);
                                                                                                                                                        add_I_property(Kernel.instances,Language._Cast,11,_oid_(v60472));
                                                                                                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                                        }
                                                                                                                                                      GC_OID(v_bag);}
                                                                                                                                                    ((list *) v19844)->addFast((OID)v_bag);
                                                                                                                                                    ((list *) v19844)->addFast((OID)((OID)0));}
                                                                                                                                                  _void_(v19843->args = v19844);}
                                                                                                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                                v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                                }
                                                                                                                                              GC_OID(v_bag);}
                                                                                                                                            ((list *) v19819)->addFast((OID)v_bag);}
                                                                                                                                          _void_(v19817->args = v19819);}
                                                                                                                                        add_I_property(Kernel.instances,Language._And,11,_oid_(v60472));
                                                                                                                                        v19816 = _oid_(close_Instruction1(v60472));
                                                                                                                                        }
                                                                                                                                      _void_(v19814->test = v19816);}
                                                                                                                                    { If * v19847 = v60472; 
                                                                                                                                      OID  v19848;
                                                                                                                                      { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                                                                                                                                        _void_(v60472->var = v34627);
                                                                                                                                        _void_(v60472->value = CNULL);
                                                                                                                                        { Let * v19870 = v60472; 
                                                                                                                                          OID  v19871;
                                                                                                                                          { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                                                                                                            { Do * v19872 = v60472; 
                                                                                                                                              list * v19873;
                                                                                                                                              { OID v_bag;
                                                                                                                                                GC_ANY(v19873= list::empty(Kernel.emptySet));
                                                                                                                                                { { Assign * v60472 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                                                                                                                                    _void_(v60472->var = _oid_(v34627));
                                                                                                                                                    { Assign * v19874 = v60472; 
                                                                                                                                                      OID  v19875;
                                                                                                                                                      { ClaireHandle * v60472 = ((ClaireHandle *) GC_OBJECT(ClaireHandle,new_object_class(Language._Handle)));
                                                                                                                                                        _void_(v60472->test = _oid_(Kernel._any));
                                                                                                                                                        { ClaireHandle * v19876 = v60472; 
                                                                                                                                                          OID  v19877;
                                                                                                                                                          { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                            _void_(v60472->selector = Serialize.unserialize);
                                                                                                                                                            _void_(v60472->args = list::alloc(1,_oid_(v36907)));
                                                                                                                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                                            v19877 = _oid_(close_Instruction1(v60472));
                                                                                                                                                            }
                                                                                                                                                          _void_(v19876->arg = v19877);}
                                                                                                                                                        { ClaireHandle * v19878 = v60472; 
                                                                                                                                                          OID  v19879;
                                                                                                                                                          { Call_star * v60472 = ((Call_star *) GC_OBJECT(Call_star,new_object_class(Language._Call_star)));
                                                                                                                                                            _void_(v60472->selector = Kernel.exception_I);
                                                                                                                                                            _void_(v60472->args = list::alloc(1,_oid_(ClEnv)));
                                                                                                                                                            add_I_property(Kernel.instances,Language._Call_star,11,_oid_(v60472));
                                                                                                                                                            v19879 = _oid_(close_Instruction1(v60472));
                                                                                                                                                            }
                                                                                                                                                          _void_(v19878->other = v19879);}
                                                                                                                                                        add_I_property(Kernel.instances,Language._Handle,11,_oid_(v60472));
                                                                                                                                                        v19875 = _oid_(close_Instruction1(v60472));
                                                                                                                                                        }
                                                                                                                                                      _void_(v19874->arg = v19875);}
                                                                                                                                                    add_I_property(Kernel.instances,Language._Assign,11,_oid_(v60472));
                                                                                                                                                    v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                                    }
                                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                                ((list *) v19873)->addFast((OID)v_bag);
                                                                                                                                                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                                    _void_(v60472->selector = Kernel.add_I);
                                                                                                                                                    _void_(v60472->args = list::alloc(2,_oid_(v51800),_oid_(v34627)));
                                                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                                    v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                                    }
                                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                                ((list *) v19873)->addFast((OID)v_bag);}
                                                                                                                                              _void_(v19872->args = v19873);}
                                                                                                                                            add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                                                                                                            v19871 = _oid_(close_Instruction1(v60472));
                                                                                                                                            }
                                                                                                                                          _void_(v19870->arg = v19871);}
                                                                                                                                        add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                                                                                                                        v19848 = _oid_(close_Instruction1(v60472));
                                                                                                                                        }
                                                                                                                                      _void_(v19847->arg = v19848);}
                                                                                                                                    { If * v19901 = v60472; 
                                                                                                                                      OID  v19902;
                                                                                                                                      { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                        _void_(v60472->selector = Kernel.add_I);
                                                                                                                                        _void_(v60472->args = list::alloc(2,_oid_(v51800),_oid_(v58793)));
                                                                                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                        v19902 = _oid_(close_Instruction1(v60472));
                                                                                                                                        }
                                                                                                                                      _void_(v19901->other = v19902);}
                                                                                                                                    add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                                                                                                                                    v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                    }
                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                ((list *) v19813)->addFast((OID)v_bag);
                                                                                                                                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                    _void_(v60472->selector = Core.fclose);
                                                                                                                                    _void_(v60472->args = list::alloc(1,_oid_(v58728)));
                                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                    v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                    }
                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                ((list *) v19813)->addFast((OID)v_bag);
                                                                                                                                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                    _void_(v60472->selector = Core.set_length);
                                                                                                                                    _void_(v60472->args = list::alloc(2,_oid_(v36907),((OID)0)));
                                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                    v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                    }
                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                ((list *) v19813)->addFast((OID)v_bag);
                                                                                                                                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                                                                                    _void_(v60472->selector = Kernel.nth_equal);
                                                                                                                                    _void_(v60472->args = list::alloc(3,_oid_(v58231),
                                                                                                                                      ((OID)1),
                                                                                                                                      ((OID)-1)));
                                                                                                                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                                                                                    v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                    }
                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                ((list *) v19813)->addFast((OID)v_bag);
                                                                                                                                { { Return * v60472 = ((Return *) GC_OBJECT(Return,new_object_class(Language._Return)));
                                                                                                                                    _void_(v60472->arg = Kernel.ctrue);
                                                                                                                                    add_I_property(Kernel.instances,Language._Return,11,_oid_(v60472));
                                                                                                                                    v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                                    }
                                                                                                                                  GC_OID(v_bag);}
                                                                                                                                ((list *) v19813)->addFast((OID)v_bag);}
                                                                                                                              _void_(v19812->args = v19813);}
                                                                                                                            add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                                                                                            v19811 = _oid_(close_Instruction1(v60472));
                                                                                                                            }
                                                                                                                          _void_(v19810->arg = v19811);}
                                                                                                                        add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                                                                                                        v19786 = _oid_(close_Instruction1(v60472));
                                                                                                                        }
                                                                                                                      _void_(v19785->arg = v19786);}
                                                                                                                    add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                                                                                                                    _void_(v60472->other = Kernel.cfalse);
                                                                                                                    v_bag = _oid_(close_Instruction1(v60472));
                                                                                                                    }
                                                                                                                  GC_OID(v_bag);}
                                                                                                                ((list *) v19780)->addFast((OID)v_bag);}
                                                                                                              _void_(v19779->args = v19780);}
                                                                                                            add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                                                                            v19778 = _oid_(close_Instruction1(v60472));
                                                                                                            }
                                                                                                          _void_(v19777->arg = v19778);}
                                                                                                        add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                                                                                                        _void_(v60472->other = Kernel.cfalse);
                                                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                                                        }
                                                                                                      GC_OID(v_bag);}
                                                                                                    ((list *) v19751)->addFast((OID)v_bag);}
                                                                                                  _void_(v19750->args = v19751);}
                                                                                                add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                                                                v19749 = _oid_(close_Instruction1(v60472));
                                                                                                }
                                                                                              _void_(v19748->arg = v19749);}
                                                                                            add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                                                                                            _void_(v60472->other = Kernel.cfalse);
                                                                                            v19725 = _oid_(close_Instruction1(v60472));
                                                                                            }
                                                                                          _void_(v19724->arg = v19725);}
                                                                                        add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                                                                        v19718 = _oid_(close_Instruction1(v60472));
                                                                                        }
                                                                                      _void_(v19717->arg = v19718);}
                                                                                    add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                                                                    v19042 = _oid_(close_Instruction1(v60472));
                                                                                    }
                                                                                  _void_(v19041->arg = v19042);}
                                                                                add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                                                                v19035 = _oid_(close_Instruction1(v60472));
                                                                                }
                                                                              _void_(v19034->arg = v19035);}
                                                                            add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                                                            v19010 = _oid_(close_Instruction1(v60472));
                                                                            }
                                                                          _void_(v19009->arg = v19010);}
                                                                        add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                        }
                                                                      GC_OID(v_bag);}
                                                                    ((list *) v18764)->addFast((OID)v_bag);}
                                                                  _void_(v18763->args = v18764);}
                                                                add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                                v18761 = _oid_(close_Instruction1(v60472));
                                                                }
                                                              _void_(v18760->arg = v18761);}
                                                            add_I_property(Kernel.instances,Language._While,11,_oid_(v60472));
                                                            v_bag = _oid_(close_Instruction1(v60472));
                                                            }
                                                          GC_OID(v_bag);}
                                                        ((list *) v18755)->addFast((OID)v_bag);
                                                        { { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                                                            _void_(v60472->var = v8229);
                                                            _void_(v60472->set_arg = _oid_(v41503));
                                                            { Iteration * v19903 = v60472; 
                                                              OID  v19904;
                                                              { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                _void_(v60472->selector = Core.fclose);
                                                                { Call * v19905 = v60472; 
                                                                  list * v19906;
                                                                  { OID v_bag;
                                                                    GC_ANY(v19906= list::empty(Kernel.emptySet));
                                                                    { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                        _void_(v60472->selector = Kernel.nth);
                                                                        _void_(v60472->args = list::alloc(2,_oid_(v8229),((OID)3)));
                                                                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                        v_bag = _oid_(close_Instruction1(v60472));
                                                                        }
                                                                      GC_OID(v_bag);}
                                                                    ((list *) v19906)->addFast((OID)v_bag);}
                                                                  _void_(v19905->args = v19906);}
                                                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                v19904 = _oid_(close_Instruction1(v60472));
                                                                }
                                                              _void_(v19903->arg = v19904);}
                                                            add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                                                            v_bag = _oid_(close_Instruction1(v60472));
                                                            }
                                                          GC_OID(v_bag);}
                                                        ((list *) v18755)->addFast((OID)v_bag);
                                                        { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                            _void_(v60472->selector = Kernel.cast_I);
                                                            _void_(v60472->args = list::alloc(2,_oid_(v51800),_oid_(Kernel.emptySet)));
                                                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                            v_bag = _oid_(close_Instruction1(v60472));
                                                            }
                                                          GC_OID(v_bag);}
                                                        ((list *) v18755)->addFast((OID)v_bag);}
                                                      _void_(v18754->args = v18755);}
                                                    add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                    v18081 = _oid_(close_Instruction1(v60472));
                                                    }
                                                  _void_(v18080->arg = v18081);}
                                                add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                                v18079 = _oid_(close_Instruction1(v60472));
                                                }
                                              _void_(v18078->arg = v18079);}
                                            add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                            v18075 = _oid_(close_Instruction1(v60472));
                                            }
                                          _void_(v18074->arg = v18075);}
                                        add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                        v18044 = _oid_(close_Instruction1(v60472));
                                        }
                                      _void_(v18043->arg = v18044);}
                                    add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                    v18042 = _oid_(close_Instruction1(v60472));
                                    }
                                  _void_(v18041->arg = v18042);}
                                add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                                v18019 = _oid_(close_Instruction1(v60472));
                                }
                              _void_(v18018->arg = v18019);}
                            add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                            v18012 = _oid_(close_Instruction1(v60472));
                            }
                          _void_(v18011->arg = v18012);}
                        add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                        v17987 = _oid_(close_Instruction1(v60472));
                        }
                      _void_(v17986->arg = v17987);}
                    add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                    v47454 = _oid_(close_Instruction1(v60472));
                    }
                  GC_OID(v47454);}
                v47973 = (*Optimize.c_code)(v47454,
                  _oid_(v58792));
                }
              }
            GC_OID(v47973);}
        _void_(Optimize.OPT->loop_gc = CTRUE);
        _void_(Optimize.OPT->protection = CTRUE);
        Result = v47973;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  Iterate_I_Iteration(Iteration *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      Result = restriction_I_property(Language.Iterate,list::alloc(3,_oid_(set::alloc(1,GC_OID(v62612->set_arg))),
        _oid_(set::alloc(1,GC_OID(_oid_(v62612->var)))),
        _oid_(Kernel._any)),CTRUE);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  iterate_Interval(Interval *v8240,Variable *v8238,OID v8221) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { OID Result = 0;
      { OID  v8238 = GC_OID(eval_any2(((OID)v8240->arg1),Core._Interval));
        CL_INT  v40039 = ((CL_INT)eval_any2(((OID)v8240->arg2),Core._Interval));
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          Result= _oid_(CFALSE);
          while (((CL_INT)((CL_INT)v8238) <= (CL_INT)v40039))
          { GC_LOOP;
            ;GC__OID(v8238 = (*Core._plus)(v8238,
              ((OID)1)), 1);
            GC_UNLOOP;POP_SIGNAL;}
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  iterate_array(OID *v8240,Variable *v8238,OID v8221) { 
    { OID Result = 0;
      { CL_INT  v56365 = 1;
        OID * v56356 = v8240;
        CL_INT  v40039 = v56356[0];
        { CL_INT loop_handle = ClEnv->cHandle;
          Result= _oid_(CFALSE);
          while (((CL_INT)v56365 <= (CL_INT)v40039))
          { { OID  v8238 = nth_array(v56356,v56365);
              ;++v56365;
              }
            POP_SIGNAL;}
          }
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  Iterate_class(ClaireClass *v8240,Variable *v8238,OID v8221) { 
    { OID Result = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v48555);
        Result= Kernel.cfalse;
        for (START(v8240->descendents); NEXT(v48555);)
        { ClaireBoolean * v48556;
          { OID v61842;{ CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(v8238);
              v61842= Kernel.cfalse;
              for (START(OBJECT(ClaireClass,v48555)->instances); NEXT(v8238);)
              ;}
            
            v48556=OBJECT(ClaireBoolean,v61842);}
          if (v48556 == CTRUE)
           { Result = _oid_(v48556);
            ClEnv->cHandle = loop_handle;break;}
          }
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  Iterate_any1(OID v8240,Variable *v8238,OID v8221) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { OID Result = 0;
      { OID  v8238 = GC_OID(OPT_EVAL((*(OBJECT(Call,v8240)->args))[1]));
        OID  v40039 = GC_OID(OPT_EVAL((*(OBJECT(Call,v8240)->args))[2]));
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          Result= _oid_(CFALSE);
          while (((OBJECT(ClaireBoolean,(*Kernel._inf_equal)(v8238,
            v40039))) == CTRUE))
          { GC_LOOP;
            ;GC__OID(v8238 = (*Core._plus)(v8238,
              ((OID)1)), 1);
            GC_UNLOOP;POP_SIGNAL;}
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  Iterate_Lselect(Lselect *v8240,Variable *v8238,OID v8221) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v8238);
        Result= Kernel.cfalse;
        bag *v8238_support;
        v8238_support = GC_OBJECT(bag,enumerate_any(GC_OID(eval_any(GC_OID(v8240->set_arg)))));
        for (START(v8238_support); NEXT(v8238);)
        { GC_LOOP;
          if (boolean_I_any(eval_any(GC_OID(substitution_any(GC_OID(v8240->arg),GC_OBJECT(Variable,v8240->var),v8238)))) == CTRUE)
           ;GC_UNLOOP; POP_SIGNAL;}
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  Iterate_Select(Select *v8240,Variable *v8238,OID v8221) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v8238);
        Result= Kernel.cfalse;
        bag *v8238_support;
        v8238_support = GC_OBJECT(bag,enumerate_any(GC_OID(eval_any(GC_OID(v8240->set_arg)))));
        for (START(v8238_support); NEXT(v8238);)
        { GC_LOOP;
          if (boolean_I_any(eval_any(GC_OID(substitution_any(GC_OID(v8240->arg),GC_OBJECT(Variable,v8240->var),v8238)))) == CTRUE)
           ;GC_UNLOOP; POP_SIGNAL;}
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  Iterate_Collect(Collect *v8240,Variable *v8238,OID v8221) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v4652);
        Result= Kernel.cfalse;
        bag *v4652_support;
        v4652_support = GC_OBJECT(bag,enumerate_any(GC_OID(eval_any(GC_OID(v8240->set_arg)))));
        for (START(v4652_support); NEXT(v4652);)
        { GC_LOOP;
          { OID  v8238 = GC_OID(eval_any(GC_OID(substitution_any(GC_OID(v8240->arg),GC_OBJECT(Variable,v8240->var),v4652))));
            ;}
          GC_UNLOOP; POP_SIGNAL;}
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  Iterate_any2(OID v8240,Variable *v8238,OID v8221) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v8238);
        Result= Kernel.cfalse;
        bag *v8238_support;
        v8238_support = GC_OBJECT(bag,enumerate_any(GC_OID(OPT_EVAL((*(OBJECT(Call,v8240)->args))[1]))));
        for (START(v8238_support); NEXT(v8238);)
        { GC_LOOP;
          if (equal(v8238,OPT_EVAL((*(OBJECT(Call,v8240)->args))[2])) != CTRUE)
           ;GC_UNLOOP; POP_SIGNAL;}
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  Iterate_any3(OID v8240,Variable *v8238,OID v8221) { 
    
    GC_BIND;
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v8238);
      bag *v8238_support;
      v8238_support = GC_OBJECT(bag,enumerate_any(GC_OID(OPT_EVAL((*(OBJECT(Call,v8240)->args))[1]))));
      for (START(v8238_support); NEXT(v8238);)
      ;}
    { OID Result = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v8238);
        Result= Kernel.cfalse;
        bag *v8238_support;
        v8238_support = GC_OBJECT(bag,enumerate_any(GC_OID(OPT_EVAL((*(OBJECT(Call,v8240)->args))[2]))));
        for (START(v8238_support); NEXT(v8238);)
        ;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  



/***** CLAIRE Compilation of file ./compile/odefine.cl 
         [version 3.5.0 / safety 5] *****/

CL_EXPORT ClaireType * c_type_List_Optimize(List *v62612) { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
     mtformat_module1(Optimize.it,((char*)"call c_type with ~S -> ~S \n"),5,list::alloc(2,_oid_(v62612),GC_OID(get_property(Kernel.of,v62612))));
    else ;{ ClaireType *Result ;
      if (((v62612->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       Result = param_I_class(Kernel._list,GC_OBJECT(ClaireType,v62612->of));
      else { OID  v44963 = _oid_(Kernel.emptySet);
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v56379);
            bag *v56379_support;
            v56379_support = GC_OBJECT(list,v62612->args);
            for (START(v56379_support); NEXT(v56379);)
            { GC_LOOP;
              if (boolean_I_any(v44963) == CTRUE)
               GC__OID(v44963 = _oid_(meet_class(OBJECT(ClaireClass,v44963),class_I_type(GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v56379))))))), 1);
              else GC__OID(v44963 = _oid_(class_I_type(GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v56379)))))), 2);
                GC_UNLOOP; POP_SIGNAL;}
            }
          Result = nth_class1(Kernel._list,OBJECT(ClaireType,v44963));
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_List_Optimize(List *v62612) { 
    
    GC_BIND;
    _void_(Optimize.OPT->allocation = CTRUE);
    { OID Result = 0;
      { List * v8240;
        { { Instruction *V_CC ;
            { List * v60472 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
              { Construct * v19907 = v60472; 
                list * v19908;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  bag *v_list; OID v_val;
                  OID v56379; CL_INT CLcount;
                  v_list = GC_OBJECT(list,v62612->args);
                   v19908 = v_list->clone();
                  for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                  { GC_LOOP;
                    v56379 = (*(v_list))[CLcount];
                    v_val = c_gc_I_any2(GC_OID((*Optimize.c_code)(v56379,
                      _oid_(Kernel._any))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v56379))));
                    
                    (*((list *) v19908))[CLcount] = v_val;GC_UNLOOP; POP_SIGNAL;}
                  }
                _void_(v19907->args = v19908);}
              add_I_property(Kernel.instances,Language._List,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v8240= (List *) V_CC;}
          GC_OBJECT(List,v8240);}
        if (((v62612->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         { { ClaireBoolean * g1568I;
            { ClaireBoolean *v_or;
              { v_or = (((CL_INT)Optimize.compiler->safety > (CL_INT)4) ? CTRUE : CFALSE);
                if (v_or == CTRUE) g1568I =CTRUE; 
                else { v_or = ((equal(_oid_(v62612->of),_oid_(Kernel.emptySet)) == CTRUE) ? CTRUE : CFALSE);
                  if (v_or == CTRUE) g1568I =CTRUE; 
                  else { { OID  v65254;
                      { CL_INT loop_handle = ClEnv->cHandle;
                        OID gc_local;
                        ITERATE(v56379);
                        v65254= Kernel.cfalse;
                        bag *v56379_support;
                        v56379_support = GC_OBJECT(list,v62612->args);
                        for (START(v56379_support); NEXT(v56379);)
                        { GC_LOOP;
                          if (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v56379))),GC_OBJECT(ClaireType,v62612->of)) != CTRUE)
                           { GC_UNLOOP;v65254 = Kernel.ctrue;
                            ClEnv->cHandle = loop_handle;break;}
                          GC_UNLOOP; POP_SIGNAL;}
                        }
                      v_or = not_any(v65254);
                      }
                    if (v_or == CTRUE) g1568I =CTRUE; 
                    else g1568I = CFALSE;}
                  }
                }
              }
            
            if (g1568I == CTRUE) { _void_(v8240->of = v62612->of);
                Result = _oid_(v8240);
                }
              else { warn_void();
              if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
               { list * v20860;
                { { OID v_bag;
                    GC_ANY(v20860= list::empty(Kernel.emptySet));
                    { { list * v18424;{ CL_INT loop_handle = ClEnv->cHandle;
                          bag *v_list; OID v_val;
                          OID v56379; CL_INT CLcount;
                          v_list = GC_OBJECT(list,v62612->args);
                           v18424 = v_list->clone();
                          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                          { v56379 = (*(v_list))[CLcount];
                            v_val = (*Optimize.c_type)(v56379);
                            
                            (*((list *) v18424))[CLcount] = v_val;}
                          }
                        
                        v_bag=_oid_(v18424);}
                      GC_OID(v_bag);}
                    ((list *) v20860)->addFast((OID)v_bag);
                    ((list *) v20860)->addFast((OID)GC_OID(_oid_(v62612->of)));}
                  GC_OBJECT(list,v20860);}
                mtformat_module1(Optimize.it,((char*)"`BLUE unsafe typed list: ~S not in ~S [262]\n"),2,v20860);
                }
              else ;{ OID  v22782;
                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(v60472->selector = Core.check_in);
                    _void_(v60472->args = list::alloc(3,_oid_(v8240),
                      _oid_(Kernel._list),
                      GC_OID(_oid_(v62612->of))));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                    v22782 = _oid_(close_Instruction1(v60472));
                    }
                  GC_OID(v22782);}
                Result = (*Optimize.c_code)(v22782,
                  _oid_(Kernel._list));
                }
              }
            }
          }
        else Result = _oid_(v8240);
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Set_Optimize(Set *v62612) { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
     mtformat_module1(Optimize.it,((char*)"call c_type with ~S -> ~S \n"),5,list::alloc(2,_oid_(v62612),GC_OID(get_property(Kernel.of,v62612))));
    else ;{ ClaireType *Result ;
      if (((v62612->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       Result = param_I_class(Kernel._set,GC_OBJECT(ClaireType,v62612->of));
      else { OID  v44963 = _oid_(Kernel.emptySet);
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v56379);
            bag *v56379_support;
            v56379_support = GC_OBJECT(list,v62612->args);
            for (START(v56379_support); NEXT(v56379);)
            { GC_LOOP;
              if (boolean_I_any(v44963) == CTRUE)
               GC__OID(v44963 = _oid_(meet_class(OBJECT(ClaireClass,v44963),class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v56379)))))), 1);
              else GC__OID(v44963 = _oid_(class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v56379))))), 2);
                GC_UNLOOP; POP_SIGNAL;}
            }
          Result = nth_class1(Kernel._set,OBJECT(ClaireType,v44963));
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Set_Optimize(Set *v62612) { 
    
    GC_BIND;
    _void_(Optimize.OPT->allocation = CTRUE);
    { OID Result = 0;
      { Set * v8240;
        { { Instruction *V_CC ;
            { Set * v60472 = ((Set *) GC_OBJECT(Set,new_object_class(Language._Set)));
              { Construct * v19935 = v60472; 
                list * v19936;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  bag *v_list; OID v_val;
                  OID v56379; CL_INT CLcount;
                  v_list = GC_OBJECT(list,v62612->args);
                   v19936 = v_list->clone();
                  for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                  { GC_LOOP;
                    v56379 = (*(v_list))[CLcount];
                    v_val = c_gc_I_any2(GC_OID((*Optimize.c_code)(v56379,
                      _oid_(Kernel._any))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v56379))));
                    
                    (*((list *) v19936))[CLcount] = v_val;GC_UNLOOP; POP_SIGNAL;}
                  }
                _void_(v19935->args = v19936);}
              add_I_property(Kernel.instances,Language._Set,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v8240= (Set *) V_CC;}
          GC_OBJECT(Set,v8240);}
        if (((v62612->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         { { ClaireBoolean * g1575I;
            { ClaireBoolean *v_or;
              { v_or = (((CL_INT)Optimize.compiler->safety > (CL_INT)4) ? CTRUE : CFALSE);
                if (v_or == CTRUE) g1575I =CTRUE; 
                else { v_or = ((equal(_oid_(v62612->of),_oid_(Kernel.emptySet)) == CTRUE) ? CTRUE : CFALSE);
                  if (v_or == CTRUE) g1575I =CTRUE; 
                  else { { OID  v26626;
                      { CL_INT loop_handle = ClEnv->cHandle;
                        OID gc_local;
                        ITERATE(v56379);
                        v26626= Kernel.cfalse;
                        bag *v56379_support;
                        v56379_support = GC_OBJECT(list,v62612->args);
                        for (START(v56379_support); NEXT(v56379);)
                        { GC_LOOP;
                          if (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v56379))),GC_OBJECT(ClaireType,v62612->of)) != CTRUE)
                           { GC_UNLOOP;v26626 = Kernel.ctrue;
                            ClEnv->cHandle = loop_handle;break;}
                          GC_UNLOOP; POP_SIGNAL;}
                        }
                      v_or = not_any(v26626);
                      }
                    if (v_or == CTRUE) g1575I =CTRUE; 
                    else g1575I = CFALSE;}
                  }
                }
              }
            
            if (g1575I == CTRUE) { _void_(v8240->of = v62612->of);
                Result = _oid_(v8240);
                }
              else { warn_void();
              if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
               { list * v27587;
                { { OID v_bag;
                    GC_ANY(v27587= list::empty(Kernel.emptySet));
                    { { list * v18431;{ CL_INT loop_handle = ClEnv->cHandle;
                          bag *v_list; OID v_val;
                          OID v56379; CL_INT CLcount;
                          v_list = GC_OBJECT(list,v62612->args);
                           v18431 = v_list->clone();
                          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                          { v56379 = (*(v_list))[CLcount];
                            v_val = (*Optimize.c_type)(v56379);
                            
                            (*((list *) v18431))[CLcount] = v_val;}
                          }
                        
                        v_bag=_oid_(v18431);}
                      GC_OID(v_bag);}
                    ((list *) v27587)->addFast((OID)v_bag);
                    ((list *) v27587)->addFast((OID)GC_OID(_oid_(v62612->of)));}
                  GC_OBJECT(list,v27587);}
                mtformat_module1(Optimize.it,((char*)"`BLUE unsafe typed set: ~S not in ~S [262]\n"),2,v27587);
                }
              else ;{ OID  v29509;
                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(v60472->selector = Core.check_in);
                    _void_(v60472->args = list::alloc(3,_oid_(v8240),
                      _oid_(Kernel._set),
                      GC_OID(_oid_(v62612->of))));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                    v29509 = _oid_(close_Instruction1(v60472));
                    }
                  GC_OID(v29509);}
                Result = (*Optimize.c_code)(v29509,
                  _oid_(Kernel._set));
                }
              }
            }
          }
        else Result = _oid_(v8240);
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Tuple_Optimize(Tuple *v62612) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { list * v50651;
        { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID v8240; CL_INT CLcount;
            v_list = v62612->args;
             v50651 = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { v8240 = (*(v_list))[CLcount];
              v_val = (*Optimize.c_type)(v8240);
              
              (*((list *) v50651))[CLcount] = v_val;}
            }
          GC_OBJECT(list,v50651);}
        Result = tuple_I_list(v50651);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Tuple_Optimize(Tuple *v62612) { 
    
    GC_BIND;
    _void_(Optimize.OPT->allocation = CTRUE);
    { OID Result = 0;
      { Tuple * v60472 = ((Tuple *) GC_OBJECT(Tuple,new_object_class(Language._Tuple)));
        { Construct * v19964 = v60472; 
          list * v19965;
          { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID v56379; CL_INT CLcount;
            v_list = GC_OBJECT(list,v62612->args);
             v19965 = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { v56379 = (*(v_list))[CLcount];
              v_val = c_gc_I_any2(GC_OID((*Optimize.c_code)(v56379,
                _oid_(Kernel._any))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v56379))));
              
              (*((list *) v19965))[CLcount] = v_val;}
            }
          _void_(v19964->args = v19965);}
        add_I_property(Kernel.instances,Language._Tuple,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Definition_Optimize(Definition *v62612) { 
    { ClaireType *Result ;
      if (_inf_equalt_class(v62612->arg,Kernel._exception) == CTRUE)
       Result = Kernel.emptySet;
      else Result = v62612->arg;
        POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Definition_Optimize(Definition *v62612,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireClass * v56358 = v62612->arg;
        Variable * v56377 = GC_OBJECT(Variable,Variable_I_symbol(OBJECT(symbol,Optimize._starname_star->value),0,v56358));
        OID  v56379 = GC_OID(total_ask_class(v56358,GC_OBJECT(list,v62612->args)));
        if ((CL_INT)v56358->open <= (CL_INT)0)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[105] cannot instantiate ~S")),
          _oid_(list::alloc(1,_oid_(v56358))))));
        if (boolean_I_any(v56379) == CTRUE)
         Result = (*Optimize.c_code)(v56379,
          _oid_(v8235));
        else { OID  v53534;
            { { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                _void_(v60472->var = v56377);
                { Let * v19967 = v60472; 
                  OID  v19968;
                  { Cast * v60472 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                    { Cast * v19969 = v60472; 
                      OID  v19970;
                      { OID  v58339;
                        { { OID  v59300;
                            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                _void_(v60472->selector = Core.new_I);
                                _void_(v60472->args = list::alloc(1,_oid_(v56358)));
                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                v59300 = _oid_(close_Instruction1(v60472));
                                }
                              GC_OID(v59300);}
                            v58339 = (*Optimize.c_code)(v59300,
                              _oid_(Kernel._object));
                            }
                          GC_OID(v58339);}
                        v19970 = c_gc_I_any1(v58339);
                        }
                      _void_(v19969->arg = v19970);}
                    _void_(v60472->set_arg = v56358);
                    add_I_property(Kernel.instances,Language._Cast,11,_oid_(v60472));
                    v19968 = _oid_(close_Instruction1(v60472));
                    }
                  _void_(v19967->value = v19968);}
                { Let * v19994 = v60472; 
                  OID  v19995;
                  { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                    store_object(v60472,
                      2,
                      Kernel._object,
                      analyze_I_class(v56358,_oid_(v56377),GC_OBJECT(list,v62612->args),list::empty()),
                      CFALSE);
                    add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                    v19995 = _oid_(close_Instruction1(v60472));
                    }
                  _void_(v19994->arg = v19995);}
                add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                v53534 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v53534);}
            Result = (*Optimize.c_code)(v53534,
              _oid_(v8235));
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  total_ask_class(ClaireClass *v62612,list *v8228) { 
    
    GC_BIND;
    { OID Result = 0;
      { list * v58572 = GC_OBJECT(list,OBJECT(list,(*Optimize.get_indexed)(_oid_(v62612))));
        CL_INT  v8230 = v58572->length;
        { ClaireBoolean * g1593I;
          { ClaireBoolean *v_and;
            { v_and = not_any(_oid_(Optimize.compiler->diet_ask));
              if (v_and == CFALSE) g1593I =CFALSE; 
              else { v_and = ((v8228->length == ((CL_INT)v8230-(CL_INT)1)) ? CTRUE : CFALSE);
                if (v_and == CFALSE) g1593I =CFALSE; 
                else { v_and = ((v62612->open == ClEnv->ephemeral) ? CTRUE : ((_inf_equalt_class(v62612,Kernel._exception) == CTRUE) ? CTRUE : CFALSE));
                  if (v_and == CFALSE) g1593I =CFALSE; 
                  else { v_and = (((CL_INT)v8230 <= (CL_INT)4) ? CTRUE : CFALSE);
                    if (v_and == CFALSE) g1593I =CFALSE; 
                    else { { OID  v18750;
                        { CL_INT  v8225 = 2;
                          CL_INT  v19996 = v8230;
                          { CL_INT loop_handle = ClEnv->cHandle;
                            v18750= _oid_(CFALSE);
                            while (((CL_INT)v8225 <= (CL_INT)v19996))
                            { if ((((*Kernel.srange)((*(v58572))[v8225]) == _oid_(Kernel._integer)) ? CTRUE : (((*Kernel.srange)((*(v58572))[v8225]) == _oid_(Kernel._any)) ? CTRUE : CFALSE)) != CTRUE)
                               { v18750 = Kernel.ctrue;
                                ClEnv->cHandle = loop_handle;break;}
                              ++v8225;
                              POP_SIGNAL;}
                            }
                          }
                        v_and = not_any(v18750);
                        }
                      if (v_and == CFALSE) g1593I =CFALSE; 
                      else g1593I = CTRUE;}
                    }
                  }
                }
              }
            }
          
          if (g1593I == CTRUE) { OID  v56358;
              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  _void_(v60472->selector = ((v8228->length == 0) ?
                    Core.new_I :
                    Optimize.anyObject_I ));
                  { Call * v19999 = v60472; 
                    list * v20000;
                    { list * v21633;
                      { { CL_INT loop_handle = ClEnv->cHandle;
                          OID gc_local;
                          bag *v_list; OID v_val;
                          OID v8240; CL_INT CLcount;
                          v_list = v8228;
                           v21633 = v_list->clone();
                          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                          { GC_LOOP;
                            v8240 = (*(v_list))[CLcount];
                            v_val = c_gc_I_any1(GC_OID((*Optimize.c_code)(GC_OID((*(OBJECT(bag,(*Core.args)(v8240))))[2]),
                              _oid_(Kernel._any))));
                            
                            (*((list *) v21633))[CLcount] = v_val;GC_UNLOOP; POP_SIGNAL;}
                          }
                        GC_OBJECT(list,v21633);}
                      v20000 = cons_any(_oid_(v62612),v21633);
                      }
                    _void_(v19999->args = v20000);}
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                  v56358 = _oid_(close_Instruction1(v60472));
                  }
                GC_OID(v56358);}
              OID  v8229 = GC_OID(_oid_(_at_property1(Kernel.close,v62612)));
              if (_inf_equal_type(v62612,Kernel._exception) != CTRUE)
               _void_(Optimize.OPT->allocation = CTRUE);
              if (v8228->length == 0)
               v56358= (GC_OID((*Optimize.c_code)(v56358)));
              if (boolean_I_any(v8229) == CTRUE)
               { Call_method1 * v60472 = ((Call_method1 *) GC_OBJECT(Call_method1,new_object_class(Language._Call_method1)));
                update_property(Kernel.arg,
                  v60472,
                  2,
                  Kernel._object,
                  v8229);
                _void_(v60472->args = list::alloc(1,v56358));
                add_I_property(Kernel.instances,Language._Call_method1,11,_oid_(v60472));
                Result = _oid_(close_Instruction1(v60472));
                }
              else Result = v56358;
                }
            else Result = Kernel.cfalse;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  analyze_I_class(ClaireClass *v8219,OID v62612,list *v56367,list *v58572) { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    { OID Result = 0;
      { ClaireBoolean * v35674 = ((v8219->open != ClEnv->ephemeral) ? ((boolean_I_any(_oid_(v58572)) != CTRUE) ? ((Optimize.compiler->class2file_ask != CTRUE) ? CTRUE: CFALSE): CFALSE): CFALSE);
        list * v8234;
        { { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            bag *v_list; OID v_val;
            OID v8240; CL_INT CLcount;
            v_list = v56367;
             v8234 = v_list->clone(Kernel._any);
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { GC_LOOP;
              v8240 = (*(v_list))[CLcount];
              { if (inherit_ask_class(OWNER((*(OBJECT(Call,v8240)->args))[1]),Kernel._property) != CTRUE)
                 close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[internal] Wrong instantiation body for ~S, ~S is not a property")),
                  _oid_(list::alloc(2,_oid_(v8219),GC_OID((*(OBJECT(Call,v8240)->args))[1]))))));
                { OID  v8232 = GC_OID((*(OBJECT(Call,v8240)->args))[1]);
                  OID  v8241 = GC_OID((*(OBJECT(Call,v8240)->args))[2]);
                  ClaireObject * v8235 = GC_OBJECT(ClaireObject,_at_property1(OBJECT(property,v8232),v8219));
                  ClaireBoolean * v6126 = (((*Kernel.open)(v8232) == ((OID)0)) ? ((Kernel._slot == v8235->isa) ? CTRUE: CFALSE): CFALSE);
                  GC__ANY(v58572 = v58572->addFast((OID)v8232), 1);
                  { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(v60472->selector = ((v6126 == CTRUE) ?
                      Kernel.put :
                      Core.write ));
                    { Call * v20002 = v60472; 
                      list * v20003;
                      { OID v_bag;
                        GC_ANY(v20003= list::empty(Kernel.emptySet));
                        ((list *) v20003)->addFast((OID)v8232);
                        ((list *) v20003)->addFast((OID)v62612);
                        { if ((v6126 != CTRUE) || 
                              (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v8241))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(_oid_(v8235))))) == CTRUE))
                           v_bag = v8241;
                          else v_bag = c_check_any(GC_OID((*Optimize.c_code)(v8241,
                              _oid_(Kernel._any))),GC_OID((*Optimize.c_code)(GC_OID((*Kernel.range)(_oid_(v8235))),
                              _oid_(Kernel._type))));
                            GC_OID(v_bag);}
                        ((list *) v20003)->addFast((OID)v_bag);}
                      _void_(v20002->args = v20003);}
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                    v_val = _oid_(close_Instruction1(v60472));
                    }
                  }
                }
              
              (*((list *) v8234))[CLcount] = v_val;GC_UNLOOP; POP_SIGNAL;}
            }
          GC_OBJECT(list,v8234);}
        if (v35674 == CTRUE)
         { { OID  v14951;
            { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(v60472->selector = Kernel.add);
                _void_(v60472->args = list::alloc(3,_oid_(Kernel.instances),
                  _oid_(v8219),
                  v62612));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v14951 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v14951);}
            v8234 = v8234->addFast((OID)v14951);
            }
          GC_OBJECT(list,v8234);}
        if (Optimize.compiler->class2file_ask != CTRUE)
         { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v8235);
          bag *v8235_support;
          v8235_support = GC_OBJECT(list,OBJECT(bag,(*Optimize.get_indexed)(_oid_(v8219))));
          for (START(v8235_support); NEXT(v8235);)
          { GC_LOOP;
            { property * v8232 = OBJECT(restriction,v8235)->selector;
              OID  v8238 = GC_OID(OBJECT(slot,v8235)->DEFAULT);
              { ClaireBoolean * g1601I;
                { ClaireBoolean *v_and;
                  { v_and = known_ask_any(v8238);
                    if (v_and == CFALSE) g1601I =CFALSE; 
                    else { { OID  v16873;
                        if (multi_ask_any(_oid_(v8232)) == CTRUE)
                         v16873 = v8238;
                        else v16873 = Kernel.ctrue;
                          v_and = boolean_I_any(v16873);
                        }
                      if (v_and == CFALSE) g1601I =CFALSE; 
                      else { v_and = not_any(_oid_(v58572->memq(_oid_(v8232))));
                        if (v_and == CFALSE) g1601I =CFALSE; 
                        else { v_and = ((((v8232->inverse == (NULL)) ? CTRUE : CFALSE) != CTRUE) ? CTRUE : ((((v8232->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE) ? CTRUE : (((OBJECT(slot,v8235)->srange != Kernel._object) && 
                              ((OBJECT(slot,v8235)->srange != Kernel._float) && 
                                (inherit_ask_class(OWNER(v8238),Kernel._integer) != CTRUE))) ? CTRUE : CFALSE)));
                          if (v_and == CFALSE) g1601I =CFALSE; 
                          else g1601I = CTRUE;}
                        }
                      }
                    }
                  }
                
                if (g1601I == CTRUE) { OID  v18208;
                    { if (designated_ask_any(v8238) == CTRUE)
                       v18208 = v8238;
                      else { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          _void_(v60472->selector = Kernel.DEFAULT);
                          { Call * v20679 = v60472; 
                            list * v20680;
                            { OID v_bag;
                              GC_ANY(v20680= list::empty(Kernel.emptySet));
                              { { Cast * v60472 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                                  { Cast * v20681 = v60472; 
                                    OID  v20682;
                                    { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                      _void_(v60472->selector = Core._at);
                                      _void_(v60472->args = list::alloc(2,_oid_(v8232),_oid_(v8219)));
                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                      v20682 = _oid_(close_Instruction1(v60472));
                                      }
                                    _void_(v20681->arg = v20682);}
                                  _void_(v60472->set_arg = Kernel._slot);
                                  add_I_property(Kernel.instances,Language._Cast,11,_oid_(v60472));
                                  v_bag = _oid_(close_Instruction1(v60472));
                                  }
                                GC_OID(v_bag);}
                              ((list *) v20680)->addFast((OID)v_bag);}
                            _void_(v20679->args = v20680);}
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                          v18208 = _oid_(close_Instruction1(v60472));
                          }
                        GC_OID(v18208);}
                    { { OID  v21675;
                        { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                            _void_(v60472->selector = Core.write);
                            _void_(v60472->args = list::alloc(3,_oid_(v8232),
                              v62612,
                              v18208));
                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                            v21675 = _oid_(close_Instruction1(v60472));
                            }
                          GC_OID(v21675);}
                        v8234 = v8234->addFast((OID)v21675);
                        }
                       GC__ANY(v8234, 2);}
                    }
                  }
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        { OID  v8229 = GC_OID(_oid_(_at_property1(Kernel.close,v8219)));
          { OID  v22636;
            { if (boolean_I_any(v8229) == CTRUE)
               { Call_method1 * v60472 = ((Call_method1 *) GC_OBJECT(Call_method1,new_object_class(Language._Call_method1)));
                update_property(Kernel.arg,
                  v60472,
                  2,
                  Kernel._object,
                  v8229);
                _void_(v60472->args = list::alloc(1,v62612));
                add_I_property(Kernel.instances,Language._Call_method1,11,_oid_(v60472));
                v22636 = _oid_(close_Instruction1(v60472));
                }
              else v22636 = v62612;
                GC_OID(v22636);}
            v8234 = v8234->addFast((OID)v22636);
            }
          }
        Result = _oid_(v8234);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Defobj_Optimize(Defobj *v62612,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireBoolean * v56356 = Optimize.OPT->allocation;
        ClaireClass * v56358 = v62612->arg;
        OID  v8231 = get_symbol(v62612->ident);
        OID  v56377;
        { if ((v8231 != CNULL) && 
              (inherit_ask_class(OWNER(v8231),Core._global_variable) != CTRUE))
           v56377 = v8231;
          else v56377 = _oid_(Variable_I_symbol(OBJECT(symbol,Optimize._starname_star->value),0,v56358));
            GC_OID(v56377);}
        Call * v43893;
        { { Instruction *V_CC ;
            { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(v60472->selector = Optimize.object_I);
              _void_(v60472->args = list::alloc(2,_oid_(v62612->ident),_oid_(v56358)));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v43893= (Call *) V_CC;}
          GC_OBJECT(Call,v43893);}
        OID  v43894 = GC_OID(analyze_I_class(v56358,v56377,GC_OBJECT(list,v62612->args),list::alloc(1,_oid_(Kernel.name))));
        OID  v56379;
        { if (inherit_ask_class(OWNER(v56377),Language._Variable) != CTRUE)
           { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            store_object(v60472,
              2,
              Kernel._object,
              (*Kernel.cons)(_oid_(v43893),
                v43894),
              CFALSE);
            add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
            v56379 = _oid_(close_Instruction1(v60472));
            }
          else { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
              store_object(v60472,
                2,
                Kernel._object,
                v56377,
                CFALSE);
              _void_(v60472->value = _oid_(v43893));
              { Let * v20707 = v60472; 
                OID  v20708;
                { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                  store_object(v60472,
                    2,
                    Kernel._object,
                    v43894,
                    CFALSE);
                  add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                  v20708 = _oid_(close_Instruction1(v60472));
                  }
                _void_(v20707->arg = v20708);}
              add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
              v56379 = _oid_(close_Instruction1(v60472));
              }
            GC_OID(v56379);}
        if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
         mtformat_module1(Optimize.it,((char*)"compile defobj(~S) -> ~S \n"),5,list::alloc(2,_oid_(v62612),v8231));
        else ;if ((CL_INT)v56358->open <= (CL_INT)0)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[105] cannot instantiate ~S")),
          _oid_(list::alloc(1,_oid_(v56358))))));
        if (v8231 != CNULL)
         { if (contain_ask_list(Optimize.OPT->objects,v8231) != CTRUE)
           { GC_OBJECT(list,Optimize.OPT->objects)->addFast((OID)v8231);
            (*Optimize.c_register)(v8231);
            }
          }
        else { warn_void();
            if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
             mtformat_module1(Optimize.it,((char*)"`BLUE ~S is unknown [265]\n"),2,list::alloc(1,_oid_(v62612->ident)));
            else ;}
          v56379= (GC_OID((*Optimize.c_code)(v56379,
          _oid_(v8235))));
        if (_inf_equal_type(v62612->arg,Kernel._exception) == CTRUE)
         _void_(Optimize.OPT->allocation = v56356);
        Result = v56379;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Defclass_Optimize(Defclass *v62612,ClaireClass *v8235) { 
    
    GC_BIND;
    { OID Result = 0;
      { symbol * v25576 = v62612->ident;
        OID  v8231 = get_symbol(v25576);
        Call * v42777;
        { { ClaireObject *V_CC ;
            if (v8231 != CNULL)
             { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(v60472->selector = Core.class_I);
              _void_(v60472->args = list::alloc(2,_oid_(v25576),_oid_(v62612->arg)));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[internal] cannot compile unknown class ~S")),
                _oid_(list::alloc(1,_oid_(v25576))))));
              v42777= (Call *) V_CC;}
          GC_OBJECT(Call,v42777);}
        Do * v56379;
        { { Instruction *V_CC ;
            { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
              { Do * v20710 = v60472; 
                list * v20711;
                { list * v49544;
                  { { list * v50505;
                      { { CL_INT loop_handle = ClEnv->cHandle;
                          bag *v_list; OID v_val;
                          OID v8240; CL_INT CLcount;
                          v_list = GC_OBJECT(list,v62612->args);
                           v50505 = v_list->clone();
                          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                          { v8240 = (*(v_list))[CLcount];
                            { OID  v8238 = CNULL;
                              if (INHERIT(OWNER(v8240),Language._Call))
                               { v8238= (GC_OID((*(OBJECT(Call,v8240)->args))[2]));
                                v8240= (GC_OID((*(OBJECT(Call,v8240)->args))[1]));
                                }
                              { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                _void_(v60472->selector = Kernel.add_slot);
                                _void_(v60472->args = list::alloc(5,v8231,
                                  _oid_(make_a_property_any(_oid_(OBJECT(Variable,v8240)->pname))),
                                  GC_OID((*Kernel.range)(v8240)),
                                  v8238,
                                  ((OID)0)));
                                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                v_val = _oid_(close_Instruction1(v60472));
                                }
                              }
                            
                            (*((list *) v50505))[CLcount] = v_val;}
                          }
                        GC_OBJECT(list,v50505);}
                      list * v51466;
                      if (v62612->params->length != 0)
                       { OID v_bag;
                        GC_ANY(v51466= list::empty(Kernel.emptySet));
                        { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                            _void_(v60472->selector = Kernel.put);
                            _void_(v60472->args = list::alloc(3,_oid_(Kernel.params),
                              v8231,
                              GC_OID(_oid_(v62612->params))));
                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                            v_bag = _oid_(close_Instruction1(v60472));
                            }
                          GC_OID(v_bag);}
                        ((list *) v51466)->addFast((OID)v_bag);}
                      else v51466 = list::empty();
                        v49544 = append_list(v50505,v51466);
                      }
                    GC_OBJECT(list,v49544);}
                  v20711 = cons_any(_oid_(v42777),v49544);
                  }
                _void_(v20710->args = v20711);}
              add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v56379= (Do *) V_CC;}
          GC_OBJECT(Do,v56379);}
        if (contain_ask_list(Optimize.OPT->objects,v8231) != CTRUE)
         { GC_OBJECT(list,Optimize.OPT->objects)->addFast((OID)v8231);
          (*Optimize.c_register)(v8231);
          }
        Result = (*Optimize.c_code)(_oid_(v56379),
          _oid_(v8235));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_Defmethod_Optimize(Defmethod *v62612) { 
    POP_SIGNAL; return (Kernel._any);}
  

CL_EXPORT OID  c_code_Defmethod_Optimize(Defmethod *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { property * v58704 = v62612->arg->selector;
        list * v8228 = GC_OBJECT(list,v62612->arg->args);
        list * v58578 = (((v8228->length == 1) && 
            ((*(v8228))[1] == _oid_(ClEnv))) ?
          list::alloc(1,GC_OID(_oid_(Variable_I_symbol(OBJECT(symbol,Optimize._starname_star->value),0,Kernel._void)))) :
          v8228 );
        list * v58575 = GC_OBJECT(list,extract_signature_I_list(v58578));
        list * v36761 = GC_OBJECT(list,extract_range_any(GC_OID(v62612->set_arg),v58578,GC_OBJECT(list,OBJECT(list,Language.LDEF->value))));
        OID  v61434;
        { if ((boolean_I_any(v62612->inline_ask) == CTRUE) && 
              (Optimize.compiler->inline_ask == CTRUE))
           { print_in_string_void();
            princ_string(((char*)"lambda[("));
            ppvariable_list(v58578);
            princ_string(((char*)"),"));
            print_any(GC_OID(v62612->body));
            princ_string(((char*)"]"));
            v61434 = _string_(end_of_string_void());
            }
          else v61434 = Kernel.cfalse;
            GC_OID(v61434);}
        list * v42950 = GC_OBJECT(list,extract_status_new_any(GC_OID(v62612->body)));
        OID  v33055 = GC_OID((*Core._at)(_oid_(v58704),
          (*(v58575))[2]));
        method * v8229;
        { ClaireObject *V_CC ;
          if (Kernel._method == OBJECT(ClaireObject,v33055)->isa)
           V_CC = OBJECT(method,v33055);
          else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[internal] the method ~S @ ~S is not known")),
              _oid_(list::alloc(2,_oid_(v58704),(*(v58575))[2])))));
            v8229= (method *) V_CC;}
        OID  v15476 = ((OID)v8229->status);
        ((*(v42950))[2]=GC_OID(get_property(Kernel.functional,v8229)));
        if ((Optimize.compiler->inline_ask != CTRUE) && 
            ((v58704 == Language.Iterate) || 
                (v58704 == Language.iterate)))
         Result = Core.nil->value;
        else if (((*(v36761))[1] == _oid_(Kernel._void)) && 
            (sort_pattern_ask_list(v58578,GC_OID(v62612->body)) == CTRUE))
         Result = sort_code_Defmethod(v62612,v58578);
        else { if ((*(v42950))[3] != _oid_(Kernel.body))
             { char * v58619 = GC_STRING(string_v((*Optimize.function_name)(_oid_(v58704),
                (*(v58575))[2],
                (*(v42950))[2])));
              lambda * v58557 = GC_OBJECT(lambda,lambda_I_list(v58578,(*(v42950))[3]));
              CL_INT  v45083 = ((Optimize.OPT->recompute == CTRUE) ?
                c_status_any(GC_OID(v58557->body),GC_OBJECT(list,v58557->vars)) :
                status_I_restriction(v8229) );
              tuple * v58821 = tuple::alloc(2,_oid_(v8229->module_I),_oid_(v8229->selector));
              put_table(Language.CODE_LOCS,_oid_(v58821),nth_table1(Language.CODE_LOCS,_oid_(v62612->arg)));
              if ((OBJECT(ClaireBoolean,Language.DEBUG_ask->value)) == CTRUE)
               fill_debug_placeholder_any1(GC_OID(v58557->body),_oid_(v58821));
              compile_lambda_string(v58619,v58557,_oid_(v8229));
              if (((*(v42950))[1] == CNULL) || 
                  (Optimize.OPT->recompute == CTRUE))
               { if ((Optimize.OPT->use_nth_equal != CTRUE) && 
                    (BCONTAIN(v45083,((CL_INT)(OID)(2)))))
                 v45083= (CL_INT)(((CL_INT)v45083-(CL_INT)exp2_integer(2)));
                if ((Optimize.OPT->use_update != CTRUE) && 
                    (BCONTAIN(v45083,((CL_INT)(OID)(3)))))
                 v45083= (CL_INT)(((CL_INT)v45083-(CL_INT)exp2_integer(3)));
                if ((Optimize.OPT->allocation != CTRUE) && 
                    (BCONTAIN(v45083,((CL_INT)(OID)(1)))))
                 v45083= (CL_INT)(((CL_INT)v45083-(CL_INT)exp2_integer(1)));
                if (should_trace_ask_module1(Optimize.it,4) == CTRUE)
                 mtformat_module1(Optimize.it,((char*)"---- CHANGE: status(~S)= ~S to ~S\n"),4,list::alloc(3,_oid_(v8229),
                  v15476,
                  ((OID)v45083)));
                else ;((*(v42950))[1]=((OID)v45083));
                }
              ((*(v42950))[2]=_oid_(make_function_string(v58619)));
              }
            if (INHERIT(OWNER(v62612->set_arg),Core._global_variable))
             ((*(v36761))[1]=GC_OID(v62612->set_arg));
            else if ((INHERIT(v8229->range->isa,Kernel._class)) && 
                (inherit_ask_class(OWNER((*(v36761))[1]),Kernel._class) != CTRUE))
             ((*(v36761))[1]=_oid_(v8229->range));
            { OID  v56368 = GC_OID(add_method_I_method(v8229,
                OBJECT(list,(*(v58575))[1]),
                (*(v36761))[1],
                (*(v42950))[1],
                OBJECT(ClaireFunction,(*(v42950))[2])));
              { OID  v52427;
                { if ((boolean_I_any(v62612->inline_ask) == CTRUE) && 
                      ((Optimize.compiler->inline_ask == CTRUE) && 
                        (Optimize.compiler->diet_ask != CTRUE)))
                   { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(v60472->selector = Core.inlineok_ask);
                    _void_(v60472->args = list::alloc(2,v56368,v61434));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                    v52427 = _oid_(close_Instruction1(v60472));
                    }
                  else if ((boolean_I_any((*(v36761))[2]) == CTRUE) && 
                      (Optimize.compiler->diet_ask != CTRUE))
                   { char * v58619 = GC_STRING(append_string(GC_STRING(string_v((*Optimize.function_name)(_oid_(v58704),
                      (*(v58575))[2],
                      (*(v42950))[2]))),((char*)"_type")));
                    compile_lambda_string(v58619,OBJECT(lambda,(*(v36761))[2]),_oid_(Kernel._type));
                    { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Core.write);
                      _void_(v60472->args = list::alloc(3,Language.typing->value,
                        v56368,
                        _oid_(make_function_string(v58619))));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v52427 = _oid_(close_Instruction1(v60472));
                      }
                    }
                  else v52427 = v56368;
                    GC_OID(v52427);}
                Result = (*Optimize.c_code)(v52427);
                }
              }
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * sort_pattern_ask_list(list *v58578,OID v8959) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      { ClaireBoolean *v_and;
        { v_and = ((v58578->length == 1) ? CTRUE : CFALSE);
          if (v_and == CFALSE) Result =CFALSE; 
          else { if (INHERIT(OWNER(v8959),Language._Call))
             { ClaireBoolean *v_and1;
              { v_and1 = ((OBJECT(Call,v8959)->selector == Core.sort) ? CTRUE : CFALSE);
                if (v_and1 == CFALSE) v_and =CFALSE; 
                else { { OID  v58168 = GC_OID((*(OBJECT(Call,v8959)->args))[1]);
                    v_and1 = ((INHERIT(OWNER(v58168),Language._Call)) ?
                      ((OBJECT(Call,v58168)->selector == Core._at) ? ((INHERIT(OWNER((*(OBJECT(Call,v58168)->args))[1]),Kernel._property)) ? CTRUE: CFALSE): CFALSE) :
                      CFALSE );
                    }
                  if (v_and1 == CFALSE) v_and =CFALSE; 
                  else { v_and1 = ((equal(lexical_build_any(GC_OID((*(OBJECT(Call,v8959)->args))[2]),v58578,0),(*(v58578))[1]) == CTRUE) ? CTRUE : CFALSE);
                    if (v_and1 == CFALSE) v_and =CFALSE; 
                    else v_and = CTRUE;}
                  }
                }
              }
            else v_and = CFALSE;
              if (v_and == CFALSE) Result =CFALSE; 
            else Result = CTRUE;}
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  sort_code_Defmethod(Defmethod *v62612,list *v58578) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  v8228 = (*(v58578))[1];
        OID  v8222 = GC_OID((*(OBJECT(bag,(*Core.args)(GC_OID((*(OBJECT(bag,(*Core.args)(GC_OID(v62612->body)))))[1])))))[1]);
        Variable * v8229 = GC_OBJECT(Variable,Variable_I_symbol(symbol_I_string2(((char*)"m")),0,Kernel._integer));
        Variable * v8230 = GC_OBJECT(Variable,Variable_I_symbol(symbol_I_string2(((char*)"n")),0,Kernel._integer));
        Variable * v8240 = GC_OBJECT(Variable,Variable_I_symbol(symbol_I_string2(((char*)"x")),0,GC_OBJECT(ClaireType,member_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(v8228)))))));
        Variable * v8232 = GC_OBJECT(Variable,Variable_I_symbol(symbol_I_string2(((char*)"p")),0,Kernel._integer));
        Variable * v361 = GC_OBJECT(Variable,Variable_I_symbol(symbol_I_string2(((char*)"q")),0,Kernel._integer));
        Defmethod * v8725;
        { { Instruction *V_CC ;
            { Defmethod * v60472 = ((Defmethod *) GC_OBJECT(Defmethod,new_object_class(Language._Defmethod)));
              _void_(v60472->arg = v62612->arg);
              _void_(v60472->inline_ask = Kernel.cfalse);
              _void_(v60472->set_arg = v62612->set_arg);
              { Defmethod * v20716 = v60472; 
                OID  v20738;
                { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  _void_(v60472->selector = v62612->arg->selector);
                  { Call * v20739 = v60472; 
                    list * v20740;
                    { OID v_bag;
                      GC_ANY(v20740= list::empty(Kernel.emptySet));
                      ((list *) v20740)->addFast((OID)((OID)1));
                      { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          _void_(v60472->selector = Kernel.length);
                          _void_(v60472->args = list::alloc(1,(*(v58578))[1]));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                          v_bag = _oid_(close_Instruction1(v60472));
                          }
                        GC_OID(v_bag);}
                      ((list *) v20740)->addFast((OID)v_bag);
                      ((list *) v20740)->addFast((OID)v8228);}
                    _void_(v20739->args = v20740);}
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                  v20738 = _oid_(close_Instruction1(v60472));
                  }
                _void_(v20716->body = v20738);}
              add_I_property(Kernel.instances,Language._Defmethod,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v8725= (Defmethod *) V_CC;}
          GC_OBJECT(Defmethod,v8725);}
        If * v43231;
        { { Instruction *V_CC ;
            { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
              { If * v20741 = v60472; 
                OID  v20742;
                { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  _void_(v60472->selector = Kernel._sup);
                  _void_(v60472->args = list::alloc(2,_oid_(v8229),_oid_(v8230)));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                  v20742 = _oid_(close_Instruction1(v60472));
                  }
                _void_(v20741->test = v20742);}
              { If * v20743 = v60472; 
                OID  v20744;
                { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                  _void_(v60472->var = v8240);
                  { Let * v20745 = v60472; 
                    OID  v20746;
                    { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Kernel.nth);
                      _void_(v60472->args = list::alloc(2,v8228,_oid_(v8230)));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v20746 = _oid_(close_Instruction1(v60472));
                      }
                    _void_(v20745->value = v20746);}
                  { Let * v20747 = v60472; 
                    OID  v20769;
                    { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                      { If * v20770 = v60472; 
                        OID  v20771;
                        { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          _void_(v60472->selector = Kernel._equal);
                          { Call * v20772 = v60472; 
                            list * v20773;
                            { OID v_bag;
                              GC_ANY(v20773= list::empty(Kernel.emptySet));
                              ((list *) v20773)->addFast((OID)_oid_(v8229));
                              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                  _void_(v60472->selector = Core._plus);
                                  _void_(v60472->args = list::alloc(2,_oid_(v8230),((OID)1)));
                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                  v_bag = _oid_(close_Instruction1(v60472));
                                  }
                                GC_OID(v_bag);}
                              ((list *) v20773)->addFast((OID)v_bag);}
                            _void_(v20772->args = v20773);}
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                          v20771 = _oid_(close_Instruction1(v60472));
                          }
                        _void_(v20770->test = v20771);}
                      { If * v20774 = v60472; 
                        OID  v20775;
                        { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                          { If * v20776 = v60472; 
                            OID  v20777;
                            { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                              update_property(Kernel.selector,
                                v60472,
                                2,
                                Kernel._object,
                                v8222);
                              { Call * v20778 = v60472; 
                                list * v20800;
                                { OID v_bag;
                                  GC_ANY(v20800= list::empty(Kernel.emptySet));
                                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                      _void_(v60472->selector = Kernel.nth);
                                      _void_(v60472->args = list::alloc(2,v8228,_oid_(v8229)));
                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                      v_bag = _oid_(close_Instruction1(v60472));
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v20800)->addFast((OID)v_bag);
                                  ((list *) v20800)->addFast((OID)_oid_(v8240));}
                                _void_(v20778->args = v20800);}
                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                              v20777 = _oid_(close_Instruction1(v60472));
                              }
                            _void_(v20776->test = v20777);}
                          { If * v20801 = v60472; 
                            OID  v20802;
                            { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                              { Do * v20803 = v60472; 
                                list * v20804;
                                { OID v_bag;
                                  GC_ANY(v20804= list::empty(Kernel.emptySet));
                                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                      _void_(v60472->selector = Kernel.nth_equal);
                                      { Call * v20805 = v60472; 
                                        list * v20806;
                                        { OID v_bag;
                                          GC_ANY(v20806= list::empty(Kernel.emptySet));
                                          ((list *) v20806)->addFast((OID)v8228);
                                          ((list *) v20806)->addFast((OID)_oid_(v8230));
                                          { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                              _void_(v60472->selector = Kernel.nth);
                                              _void_(v60472->args = list::alloc(2,v8228,_oid_(v8229)));
                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                              v_bag = _oid_(close_Instruction1(v60472));
                                              }
                                            GC_OID(v_bag);}
                                          ((list *) v20806)->addFast((OID)v_bag);}
                                        _void_(v20805->args = v20806);}
                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                      v_bag = _oid_(close_Instruction1(v60472));
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v20804)->addFast((OID)v_bag);
                                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                      _void_(v60472->selector = Kernel.nth_equal);
                                      _void_(v60472->args = list::alloc(3,v8228,
                                        _oid_(v8229),
                                        _oid_(v8240)));
                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                      v_bag = _oid_(close_Instruction1(v60472));
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v20804)->addFast((OID)v_bag);}
                                _void_(v20803->args = v20804);}
                              add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                              v20802 = _oid_(close_Instruction1(v60472));
                              }
                            _void_(v20801->arg = v20802);}
                          add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                          _void_(v60472->other = Kernel.cfalse);
                          v20775 = _oid_(close_Instruction1(v60472));
                          }
                        _void_(v20774->arg = v20775);}
                      { If * v20807 = v60472; 
                        OID  v20808;
                        { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                          _void_(v60472->var = v8232);
                          { Let * v20809 = v60472; 
                            OID  v20831;
                            { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                              _void_(v60472->selector = Core._sup_sup);
                              { Call * v20832 = v60472; 
                                list * v20833;
                                { OID v_bag;
                                  GC_ANY(v20833= list::empty(Kernel.emptySet));
                                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                      _void_(v60472->selector = Core._plus);
                                      _void_(v60472->args = list::alloc(2,_oid_(v8230),_oid_(v8229)));
                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                      v_bag = _oid_(close_Instruction1(v60472));
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v20833)->addFast((OID)v_bag);
                                  ((list *) v20833)->addFast((OID)((OID)1));}
                                _void_(v20832->args = v20833);}
                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                              v20831 = _oid_(close_Instruction1(v60472));
                              }
                            _void_(v20809->value = v20831);}
                          { Let * v20834 = v60472; 
                            OID  v20835;
                            { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                              _void_(v60472->var = v361);
                              _void_(v60472->value = _oid_(v8230));
                              { Let * v20836 = v60472; 
                                OID  v20837;
                                { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                  { Do * v20838 = v60472; 
                                    list * v20840;
                                    { OID v_bag;
                                      GC_ANY(v20840= list::empty(Kernel.emptySet));
                                      { { Assign * v60472 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                          _void_(v60472->var = _oid_(v8240));
                                          { Assign * v20841 = v60472; 
                                            OID  v20862;
                                            { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                              _void_(v60472->selector = Kernel.nth);
                                              _void_(v60472->args = list::alloc(2,v8228,_oid_(v8232)));
                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                              v20862 = _oid_(close_Instruction1(v60472));
                                              }
                                            _void_(v20841->arg = v20862);}
                                          add_I_property(Kernel.instances,Language._Assign,11,_oid_(v60472));
                                          v_bag = _oid_(close_Instruction1(v60472));
                                          }
                                        GC_OID(v_bag);}
                                      ((list *) v20840)->addFast((OID)v_bag);
                                      { { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                          { If * v20863 = v60472; 
                                            OID  v20864;
                                            { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                              _void_(v60472->selector = Core._I_equal);
                                              _void_(v60472->args = list::alloc(2,_oid_(v8232),_oid_(v8230)));
                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                              v20864 = _oid_(close_Instruction1(v60472));
                                              }
                                            _void_(v20863->test = v20864);}
                                          { If * v20865 = v60472; 
                                            OID  v20866;
                                            { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                              _void_(v60472->selector = Kernel.nth_equal);
                                              { Call * v20867 = v60472; 
                                                list * v20868;
                                                { OID v_bag;
                                                  GC_ANY(v20868= list::empty(Kernel.emptySet));
                                                  ((list *) v20868)->addFast((OID)v8228);
                                                  ((list *) v20868)->addFast((OID)_oid_(v8232));
                                                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                      _void_(v60472->selector = Kernel.nth);
                                                      _void_(v60472->args = list::alloc(2,v8228,_oid_(v8230)));
                                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                      v_bag = _oid_(close_Instruction1(v60472));
                                                      }
                                                    GC_OID(v_bag);}
                                                  ((list *) v20868)->addFast((OID)v_bag);}
                                                _void_(v20867->args = v20868);}
                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                              v20866 = _oid_(close_Instruction1(v60472));
                                              }
                                            _void_(v20865->arg = v20866);}
                                          add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                                          _void_(v60472->other = Kernel.cfalse);
                                          v_bag = _oid_(close_Instruction1(v60472));
                                          }
                                        GC_OID(v_bag);}
                                      ((list *) v20840)->addFast((OID)v_bag);
                                      { { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                                          _void_(v60472->var = v8232);
                                          { Iteration * v20869 = v60472; 
                                            OID  v20870;
                                            { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                              _void_(v60472->selector = Kernel._dot_dot);
                                              { Call * v20871 = v60472; 
                                                list * v20893;
                                                { OID v_bag;
                                                  GC_ANY(v20893= list::empty(Kernel.emptySet));
                                                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                      _void_(v60472->selector = Core._plus);
                                                      _void_(v60472->args = list::alloc(2,_oid_(v8230),((OID)1)));
                                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                      v_bag = _oid_(close_Instruction1(v60472));
                                                      }
                                                    GC_OID(v_bag);}
                                                  ((list *) v20893)->addFast((OID)v_bag);
                                                  ((list *) v20893)->addFast((OID)_oid_(v8229));}
                                                _void_(v20871->args = v20893);}
                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                              v20870 = _oid_(close_Instruction1(v60472));
                                              }
                                            _void_(v20869->set_arg = v20870);}
                                          { Iteration * v20894 = v60472; 
                                            OID  v20895;
                                            { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                              { If * v20896 = v60472; 
                                                OID  v20897;
                                                { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                  update_property(Kernel.selector,
                                                    v60472,
                                                    2,
                                                    Kernel._object,
                                                    v8222);
                                                  { Call * v20898 = v60472; 
                                                    list * v20899;
                                                    { OID v_bag;
                                                      GC_ANY(v20899= list::empty(Kernel.emptySet));
                                                      { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                          _void_(v60472->selector = Kernel.nth);
                                                          _void_(v60472->args = list::alloc(2,v8228,_oid_(v8232)));
                                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                          v_bag = _oid_(close_Instruction1(v60472));
                                                          }
                                                        GC_OID(v_bag);}
                                                      ((list *) v20899)->addFast((OID)v_bag);
                                                      ((list *) v20899)->addFast((OID)_oid_(v8240));}
                                                    _void_(v20898->args = v20899);}
                                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                  v20897 = _oid_(close_Instruction1(v60472));
                                                  }
                                                _void_(v20896->test = v20897);}
                                              { If * v20900 = v60472; 
                                                OID  v20901;
                                                { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                                  { Do * v20902 = v60472; 
                                                    list * v20924;
                                                    { OID v_bag;
                                                      GC_ANY(v20924= list::empty(Kernel.emptySet));
                                                      { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                          _void_(v60472->selector = Kernel.nth_equal);
                                                          { Call * v20925 = v60472; 
                                                            list * v20926;
                                                            { OID v_bag;
                                                              GC_ANY(v20926= list::empty(Kernel.emptySet));
                                                              ((list *) v20926)->addFast((OID)v8228);
                                                              ((list *) v20926)->addFast((OID)_oid_(v8230));
                                                              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                  _void_(v60472->selector = Kernel.nth);
                                                                  _void_(v60472->args = list::alloc(2,v8228,_oid_(v8232)));
                                                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                  v_bag = _oid_(close_Instruction1(v60472));
                                                                  }
                                                                GC_OID(v_bag);}
                                                              ((list *) v20926)->addFast((OID)v_bag);}
                                                            _void_(v20925->args = v20926);}
                                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                          v_bag = _oid_(close_Instruction1(v60472));
                                                          }
                                                        GC_OID(v_bag);}
                                                      ((list *) v20924)->addFast((OID)v_bag);
                                                      { { Assign * v60472 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                                          _void_(v60472->var = _oid_(v8230));
                                                          { Assign * v20927 = v60472; 
                                                            OID  v20928;
                                                            { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                              _void_(v60472->selector = Core._plus);
                                                              _void_(v60472->args = list::alloc(2,_oid_(v8230),((OID)1)));
                                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                              v20928 = _oid_(close_Instruction1(v60472));
                                                              }
                                                            _void_(v20927->arg = v20928);}
                                                          add_I_property(Kernel.instances,Language._Assign,11,_oid_(v60472));
                                                          v_bag = _oid_(close_Instruction1(v60472));
                                                          }
                                                        GC_OID(v_bag);}
                                                      ((list *) v20924)->addFast((OID)v_bag);
                                                      { { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                          { If * v20929 = v60472; 
                                                            OID  v20930;
                                                            { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                              _void_(v60472->selector = Kernel._sup);
                                                              _void_(v60472->args = list::alloc(2,_oid_(v8232),_oid_(v8230)));
                                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                              v20930 = _oid_(close_Instruction1(v60472));
                                                              }
                                                            _void_(v20929->test = v20930);}
                                                          { If * v20931 = v60472; 
                                                            OID  v20933;
                                                            { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                              _void_(v60472->selector = Kernel.nth_equal);
                                                              { Call * v20934 = v60472; 
                                                                list * v20955;
                                                                { OID v_bag;
                                                                  GC_ANY(v20955= list::empty(Kernel.emptySet));
                                                                  ((list *) v20955)->addFast((OID)v8228);
                                                                  ((list *) v20955)->addFast((OID)_oid_(v8232));
                                                                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                      _void_(v60472->selector = Kernel.nth);
                                                                      _void_(v60472->args = list::alloc(2,v8228,_oid_(v8230)));
                                                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                                      v_bag = _oid_(close_Instruction1(v60472));
                                                                      }
                                                                    GC_OID(v_bag);}
                                                                  ((list *) v20955)->addFast((OID)v_bag);}
                                                                _void_(v20934->args = v20955);}
                                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                              v20933 = _oid_(close_Instruction1(v60472));
                                                              }
                                                            _void_(v20931->arg = v20933);}
                                                          add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                                                          _void_(v60472->other = Kernel.cfalse);
                                                          v_bag = _oid_(close_Instruction1(v60472));
                                                          }
                                                        GC_OID(v_bag);}
                                                      ((list *) v20924)->addFast((OID)v_bag);}
                                                    _void_(v20902->args = v20924);}
                                                  add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                                  v20901 = _oid_(close_Instruction1(v60472));
                                                  }
                                                _void_(v20900->arg = v20901);}
                                              add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                                              _void_(v60472->other = Kernel.cfalse);
                                              v20895 = _oid_(close_Instruction1(v60472));
                                              }
                                            _void_(v20894->arg = v20895);}
                                          add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                                          v_bag = _oid_(close_Instruction1(v60472));
                                          }
                                        GC_OID(v_bag);}
                                      ((list *) v20840)->addFast((OID)v_bag);
                                      { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                          _void_(v60472->selector = Kernel.nth_equal);
                                          _void_(v60472->args = list::alloc(3,v8228,
                                            _oid_(v8230),
                                            _oid_(v8240)));
                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                          v_bag = _oid_(close_Instruction1(v60472));
                                          }
                                        GC_OID(v_bag);}
                                      ((list *) v20840)->addFast((OID)v_bag);
                                      { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                          _void_(v60472->selector = v62612->arg->selector);
                                          { Call * v20956 = v60472; 
                                            list * v20957;
                                            { OID v_bag;
                                              GC_ANY(v20957= list::empty(Kernel.emptySet));
                                              ((list *) v20957)->addFast((OID)_oid_(v361));
                                              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                  _void_(v60472->selector = Kernel._dash);
                                                  _void_(v60472->args = list::alloc(2,_oid_(v8230),((OID)1)));
                                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                  v_bag = _oid_(close_Instruction1(v60472));
                                                  }
                                                GC_OID(v_bag);}
                                              ((list *) v20957)->addFast((OID)v_bag);
                                              ((list *) v20957)->addFast((OID)v8228);}
                                            _void_(v20956->args = v20957);}
                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                          v_bag = _oid_(close_Instruction1(v60472));
                                          }
                                        GC_OID(v_bag);}
                                      ((list *) v20840)->addFast((OID)v_bag);
                                      { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                          _void_(v60472->selector = v62612->arg->selector);
                                          { Call * v20958 = v60472; 
                                            list * v20959;
                                            { OID v_bag;
                                              GC_ANY(v20959= list::empty(Kernel.emptySet));
                                              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                  _void_(v60472->selector = Core._plus);
                                                  _void_(v60472->args = list::alloc(2,_oid_(v8230),((OID)1)));
                                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                                  v_bag = _oid_(close_Instruction1(v60472));
                                                  }
                                                GC_OID(v_bag);}
                                              ((list *) v20959)->addFast((OID)v_bag);
                                              ((list *) v20959)->addFast((OID)_oid_(v8229));
                                              ((list *) v20959)->addFast((OID)v8228);}
                                            _void_(v20958->args = v20959);}
                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                                          v_bag = _oid_(close_Instruction1(v60472));
                                          }
                                        GC_OID(v_bag);}
                                      ((list *) v20840)->addFast((OID)v_bag);}
                                    _void_(v20838->args = v20840);}
                                  add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                                  v20837 = _oid_(close_Instruction1(v60472));
                                  }
                                _void_(v20836->arg = v20837);}
                              add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                              v20835 = _oid_(close_Instruction1(v60472));
                              }
                            _void_(v20834->arg = v20835);}
                          add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                          v20808 = _oid_(close_Instruction1(v60472));
                          }
                        _void_(v20807->other = v20808);}
                      add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                      v20769 = _oid_(close_Instruction1(v60472));
                      }
                    _void_(v20747->arg = v20769);}
                  add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                  v20744 = _oid_(close_Instruction1(v60472));
                  }
                _void_(v20743->arg = v20744);}
              add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
              _void_(v60472->other = Kernel.cfalse);
              V_CC = close_Instruction1(v60472);
              }
            v43231= (If *) V_CC;}
          GC_OBJECT(If,v43231);}
        Defmethod * v8726;
        { { Instruction *V_CC ;
            { Defmethod * v60472 = ((Defmethod *) GC_OBJECT(Defmethod,new_object_class(Language._Defmethod)));
              { Defmethod * v20960 = v60472; 
                Call * v20961;
                { Instruction *V_CC ;
                  { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(v60472->selector = v62612->arg->selector);
                    _void_(v60472->args = list::alloc(3,_oid_(v8230),
                      _oid_(v8229),
                      v8228));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                    V_CC = close_Instruction1(v60472);
                    }
                  v20961= (Call *) V_CC;}
                _void_(v20960->arg = v20961);}
              _void_(v60472->inline_ask = Kernel.cfalse);
              _void_(v60472->set_arg = v62612->set_arg);
              _void_(v60472->body = _oid_(v43231));
              add_I_property(Kernel.instances,Language._Defmethod,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v8726= (Defmethod *) V_CC;}
          GC_OBJECT(Defmethod,v8726);}
        show_opportunist_integer1(2);
        if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
         mtformat_module1(Optimize.it,((char*)" `GREEN note: quick sort optimisation for ~S ---- \n"),2,list::alloc(1,_oid_(v62612->arg->selector)));
        else ;OPT_EVAL(_oid_(v8726));
        { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
          _void_(v60472->args = list::alloc(2,GC_OID((*Optimize.c_code)(_oid_(v8725))),GC_OID((*Optimize.c_code)(_oid_(v8726)))));
          add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
          Result = _oid_(close_Instruction1(v60472));
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT method * add_method_property2(property *v8232,list *v58575,ClaireType *v58750,int v58793,ClaireFunction *v58323,ClaireFunction *v58324) { 
    POP_SIGNAL; return (add_method_property(v8232,
      v58575,
      v58750,
      ((OID)v58793),
      _oid_(v58323)));}
  

CL_EXPORT OID  add_method_I_method(method *v8229,list *v58575,OID v58750,OID v49756,ClaireFunction *v58391) { 
    
    GC_BIND;
    { OID Result = 0;
      { Call_method * v56358;
        { { Instruction *V_CC ;
            { Call_method * v60472 = ((Call_method *) GC_OBJECT(Call_method,new_object_class(Language._Call_method)));
              _void_(v60472->arg = ((method *) _at_property1(Kernel.add_method,Kernel._property)));
              _void_(v60472->args = list::alloc(5,GC_OID((*Optimize.c_code)(_oid_(v8229->selector),
                  _oid_(Kernel._property))),
                GC_OID((*Optimize.c_code)(_oid_(v58575),
                  _oid_(Kernel._list))),
                GC_OID((*Optimize.c_code)(v58750,
                  _oid_(Kernel._type))),
                v49756,
                _oid_(v58391)));
              add_I_property(Kernel.instances,Language._Call_method,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v56358= (Call_method *) V_CC;}
          GC_OBJECT(Call_method,v56358);}
        if ((v8229->range == Kernel._float) || 
            ((v8229->domain->memq(_oid_(Kernel._float)) == CTRUE) || 
              (INHERIT(v8229->range->isa,Kernel._tuple))))
         GC_OBJECT(list,v56358->args)->addFast((OID)_oid_(make_function_string(append_string(string_I_function(v58391),((char*)"_")))));
        Result = _oid_(v56358);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT list * extract_status_new_any(OID v8240) { 
    
    GC_BIND;
    { list *Result ;
      { OID  v8235 = CNULL;
        OID  v8222;
        if ((INHERIT(OWNER(v8240),Language._Call)) && (OBJECT(Call,v8240)->selector == Language.function_I))
         v8222 = v8240;
        else v8222 = CNULL;
          if (INHERIT(OWNER(v8240),Language._And))
         { OID  v8241 = GC_OID((*(OBJECT(And,v8240)->args))[1]);
          if ((INHERIT(OWNER(v8241),Language._Call)) && (OBJECT(Call,v8241)->selector == Language.function_I))
           { v8222= (v8241);
            v8240= (GC_OID((*(OBJECT(And,v8240)->args))[2]));
            }
          }
        else if (INHERIT(OWNER(v8240),Language._Call))
         { if (OBJECT(Call,v8240)->selector == Language.function_I)
           v8240= (_oid_(Kernel.body));
          }
        if (v8222 != CNULL)
         { v8240= (_oid_(Kernel.body));
          if ((CL_INT)length_bag(OBJECT(bag,(*Core.args)(v8222))) > (CL_INT)1)
           { ClaireHandler c_handle = ClaireHandler();
            if ERROR_IN 
            { { CL_INT  v19454;{ set * v29572;
                  { set * v60662 = set::empty(Kernel.emptySet);
                    { CL_INT loop_handle = ClEnv->cHandle;
                      OID gc_local;
                      ITERATE(v8237);
                      bag *v8237_support;
                      v8237_support = GC_OBJECT(list,cdr_list(GC_OBJECT(list,OBJECT(list,(*Core.args)(v8222)))));
                      for (START(v8237_support); NEXT(v8237);)
                      { GC_LOOP;
                        v60662->addFast((OID)GC_OID(OPT_EVAL(v8237)));
                        GC_UNLOOP; POP_SIGNAL;}
                      }
                    v29572 = GC_OBJECT(set,v60662);
                    }
                  v19454 = integer_I_set(v29572);
                  }
                
                v8235=((OID)v19454);}
              ERROR_FREE;}
            else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
            { c_handle.catchIt();{ warn_void();
                (Optimize.SHIT->value= _oid_(cdr_list(GC_OBJECT(list,OBJECT(list,(*Core.args)(v8222))))));
                if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
                 mtformat_module1(Optimize.it,((char*)"`BLUE wrong status ~S -> ~S [266]\n"),2,GC_OBJECT(list,list::alloc(2,v8222,_oid_(set_I_bag(cdr_list(GC_OBJECT(list,OBJECT(list,(*Core.args)(v8222)))))))));
                else ;v8235= (((OID)0));
                }
              }
            else PREVIOUS_HANDLER;}
          else v8235= (((OID)0));
            v8222= (_oid_(make_function_string(string_I_symbol(extract_symbol_any((*(OBJECT(bag,(*Core.args)(v8222))))[1])))));
          }
        Result = list::alloc(3,v8235,
          v8222,
          v8240);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT list * extract_signature_I_list(list *v8228) { 
    
    GC_BIND;
    (Language.LDEF->value= _oid_(list::empty(Kernel._any)));
    { list *Result ;
      { CL_INT  v8230 = 0;
        list * v58509 = list::empty(Kernel._type);
        list * v58510;
        { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID v8238; CL_INT CLcount;
            v_list = v8228;
             v58510 = v_list->clone(Kernel._any);
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { v8238 = (*(v_list))[CLcount];
              { OID  v8232 = GC_OID(extract_pattern_any(GC_OID(_oid_(OBJECT(Variable,v8238)->range)),list::alloc(1,((OID)v8230))));
                ++v8230;
                { { OID  v20965;
                    { if (INHERIT(OBJECT(Variable,v8238)->range->isa,Core._global_variable))
                       v20965 = _oid_(OBJECT(Variable,v8238)->range);
                      else v20965 = v8232;
                        GC_OID(v20965);}
                    v58509 = v58509->addFast((OID)v20965);
                    }
                  GC_OBJECT(list,v58509);}
                _void_(OBJECT(Variable,v8238)->range = type_I_any(v8232));
                v_val = v8232;
                }
              
              (*((list *) v58510))[CLcount] = v_val;}
            }
          GC_OBJECT(list,v58510);}
        Result = list::alloc(2,_oid_(v58509),_oid_(v58510));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireBoolean * _equalsig_ask_list(list *v8240,list *v8241) { 
    POP_SIGNAL; return (((tmatch_ask_list(v8240,v8241) == CTRUE) ? ((tmatch_ask_list(v8241,v8240) == CTRUE) ? CTRUE: CFALSE): CFALSE));}
  

CL_EXPORT char * function_name_property_Optimize(property *v8232,list *v8228,OID v8240) { 
    
    GC_BIND;
    { char *Result ;
      if (INHERIT(OWNER(v8240),Kernel._function))
       Result = string_I_function(OBJECT(ClaireFunction,v8240));
      else { CL_INT  v8230 = 0;
          CL_INT  v8229 = 0;
          module * v58602 = v8232->name->module_I;
          ClaireClass * v8219 = class_I_type(OBJECT(ClaireType,(*(v8228))[1]));
          char * v8234 = GC_STRING(append_string(GC_STRING(append_string(string_I_symbol(v8232->name),((char*)"_"))),string_I_symbol(v8219->name)));
          if ((Optimize.compiler->naming == 0) && 
              (v8232 != Core.main))
           v8234= (GC_STRING(append_string(GC_STRING(append_string(string_I_symbol(v58602->name),((char*)"_"))),v8234)));
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(v8234);
            for (START(v8232->restrictions); NEXT(v8234);)
            { if (v8219 == domain_I_restriction(OBJECT(restriction,v8234)))
               ++v8230;
              if (_equalsig_ask_list(v8228,OBJECT(restriction,v8234)->domain) == CTRUE)
               v8229= (CL_INT)(v8230);
              }
            }
          v8234= (GC_STRING(((v8232 == Core.main) ?
            v8234 :
            (((CL_INT)v8230 <= (CL_INT)1) ?
              append_string(v8234,((char*)"1")) :
              append_string(v8234,GC_STRING(string_I_integer (v8229))) ) )));
          Result = (((stable_ask_relation(v8232) == CTRUE) || 
              (v8232 == Core.main)) ?
            v8234 :
            append_string(GC_STRING(append_string(v8234,((char*)"_"))),string_I_symbol(ClEnv->module_I->name)) );
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  compile_lambda_string(char *v62612,lambda *v8228,OID v8229) { 
    { OID Result = 0;
      { CL_INT  v8240 = Optimize.compiler->safety;
        lambda * v8241 = v8228;
        if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
         mtformat_module1(Optimize.it,((char*)"---- Compiling ~A,\n"),3,list::alloc(1,_string_(v62612)));
        else ;if (Kernel._method == OWNER(v8229))
         _void_(Optimize.OPT->in_method = v8229);
        _void_(Optimize.OPT->protection = CFALSE);
        _void_(Optimize.OPT->allocation = CFALSE);
        _void_(Optimize.OPT->loop_index = 0);
        _void_(Optimize.OPT->loop_gc = CFALSE);
        _void_(Optimize.OPT->use_update = CFALSE);
        _void_(Optimize.OPT->use_nth_equal = CFALSE);
        _void_(Optimize.OPT->max_vars = 0);
        if (contain_ask_list(Optimize.OPT->unsure,v8229) == CTRUE)
         _void_(Optimize.compiler->safety = 1);
        (*Optimize.make_c_function)(_oid_(v8228),
          _string_(v62612),
          v8229);
        _void_(Optimize.OPT->in_method = CNULL);
        _void_(Optimize.compiler->safety = v8240);
        Result = Kernel.ctrue;
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  c_code_Defarray_Optimize(Defarray *v62612) { 
    
    GC_BIND;
    { OID Result = 0;
      { list * v8217 = GC_OBJECT(list,v62612->arg->args);
        OID  v56356 = get_symbol(extract_symbol_any((*(v8217))[1]));
        table * v56377;
        { ClaireObject *V_CC ;
          if (INHERIT(OWNER(v56356),Kernel._table))
           V_CC = OBJECT(table,v56356);
          else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[internal] the table ~S is unknown")),
              _oid_(list::alloc(1,(*(v8217))[1])))));
            v56377= (table *) V_CC;}
        OID  v8235 = GC_OID((*Kernel.domain)(v56356));
        OID  v8221;
        { { list * v8228 = GC_OBJECT(list,cdr_list(v8217));
            OID  v8218 = GC_OID(lexical_build_any(GC_OID(v62612->body),v8228,0));
            { ClaireBoolean * g1702I;
              { OID  v23848;
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(v58867);
                  v23848= Kernel.cfalse;
                  for (START(v8228); NEXT(v58867);)
                  if ((CL_INT)((CL_INT)(*Kernel.occurrence)(v8218,
                    v58867)) > (CL_INT)0)
                   { v23848 = Kernel.ctrue;
                    ClEnv->cHandle = loop_handle;break;}
                  }
                g1702I = boolean_I_any(v23848);
                }
              
              if (g1702I == CTRUE) v8221 = _oid_(lambda_I_list(v8228,v8218));
                else v8221 = v62612->body;
              }
            }
          GC_OID(v8221);}
        OID  v8220;
        { if (INHERIT(OWNER(v8221),Core._lambda))
           v8220 = CNULL;
          else v8220 = v62612->body;
            GC_OID(v8220);}
        list * v43490;
        if (boolean_I_any(_oid_(OBJECT(ClaireRelation,v56356)->multivalued_ask)) == CTRUE)
         { OID v_bag;
          GC_ANY(v43490= list::empty(Kernel._any));
          { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(v60472->selector = Kernel.put);
              _void_(v60472->args = list::alloc(3,_oid_(Kernel.multivalued_ask),
                _oid_(v56377),
                GC_OID(_oid_(OBJECT(ClaireRelation,v56356)->multivalued_ask))));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
              v_bag = _oid_(close_Instruction1(v60472));
              }
            GC_OID(v_bag);}
          ((list *) v43490)->addFast((OID)v_bag);}
        else v43490 = list::empty(Kernel._any);
          list * v43491;
        { OID v_bag;
          GC_ANY(v43491= list::empty(Kernel._any));
          { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(v60472->selector = Kernel.put);
              _void_(v60472->args = list::alloc(3,_oid_(Kernel.range),
                _oid_(v56377),
                GC_OID((*Kernel.range)(v56356))));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
              v_bag = _oid_(close_Instruction1(v60472));
              }
            GC_OID(v_bag);}
          ((list *) v43491)->addFast((OID)v_bag);
          { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(v60472->selector = Kernel.put);
              _void_(v60472->args = list::alloc(3,_oid_(Kernel.params),
                _oid_(v56377),
                GC_OID((*Kernel.params)(v56356))));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
              v_bag = _oid_(close_Instruction1(v60472));
              }
            GC_OID(v_bag);}
          ((list *) v43491)->addFast((OID)v_bag);
          { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(v60472->selector = Kernel.put);
              _void_(v60472->args = list::alloc(3,_oid_(Kernel.domain),
                _oid_(v56377),
                v8235));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
              v_bag = _oid_(close_Instruction1(v60472));
              }
            GC_OID(v_bag);}
          ((list *) v43491)->addFast((OID)v_bag);}
        _void_(OBJECT(Variable,(*(v8217))[2])->range = extract_type_any(GC_OID(_oid_(OBJECT(Variable,(*(v8217))[2])->range))));
        if (v8217->length == 2)
         { { { OID  v24809;
              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  _void_(v60472->selector = Kernel.put);
                  { Call * v21644 = v60472; 
                    list * v21645;
                    { OID v_bag;
                      GC_ANY(v21645= list::empty(Kernel.emptySet));
                      ((list *) v21645)->addFast((OID)_oid_(Kernel.graph));
                      ((list *) v21645)->addFast((OID)_oid_(v56377));
                      { if (INHERIT(OBJECT(ClaireObject,v8235)->isa,Core._Interval))
                         { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          _void_(v60472->selector = Core.make_copy_list);
                          _void_(v60472->args = list::alloc(2,((OID)size_Interval(OBJECT(Interval,v8235))),v8220));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                          v_bag = _oid_(close_Instruction1(v60472));
                          }
                        else { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                            _void_(v60472->selector = Kernel.make_list);
                            _void_(v60472->args = list::alloc(2,((OID)29),CNULL));
                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                            v_bag = _oid_(close_Instruction1(v60472));
                            }
                          GC_OID(v_bag);}
                      ((list *) v21645)->addFast((OID)v_bag);}
                    _void_(v21644->args = v21645);}
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                  v24809 = _oid_(close_Instruction1(v60472));
                  }
                GC_OID(v24809);}
              v43491 = v43491->addFast((OID)v24809);
              }
            GC_OBJECT(list,v43491);}
          { { OID  v27692;
              { if (INHERIT(OWNER(v8221),Core._lambda))
                 { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                  store_object(v60472,
                    2,
                    Kernel._object,
                    (*(v8217))[2],
                    CFALSE);
                  _void_(v60472->set_arg = v8235);
                  { Iteration * v21647 = v60472; 
                    OID  v21648;
                    { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Kernel.nth_equal);
                      _void_(v60472->args = list::alloc(3,_oid_(v56377),
                        (*(v8217))[2],
                        GC_OID(OBJECT(lambda,v8221)->body)));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v21648 = _oid_(close_Instruction1(v60472));
                      }
                    _void_(v21647->arg = v21648);}
                  add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                  v27692 = _oid_(close_Instruction1(v60472));
                  }
                else { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(v60472->selector = Kernel.put);
                    _void_(v60472->args = list::alloc(3,_oid_(Kernel.DEFAULT),
                      _oid_(v56377),
                      v8220));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                    v27692 = _oid_(close_Instruction1(v60472));
                    }
                  GC_OID(v27692);}
              v43491 = v43491->addFast((OID)v27692);
              }
            GC_OBJECT(list,v43491);}
          }
        else { ClaireType * v58727 = GC_OBJECT(ClaireType,extract_type_any(GC_OID(_oid_(OBJECT(Variable,(*(v8217))[3])->range))));
            _void_(OBJECT(Variable,(*(v8217))[3])->range = v58727);
            { { OID  v50758;
                { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(v60472->selector = Kernel.put);
                    { Call * v21669 = v60472; 
                      list * v21670;
                      { OID v_bag;
                        GC_ANY(v21670= list::empty(Kernel.emptySet));
                        ((list *) v21670)->addFast((OID)_oid_(Kernel.graph));
                        ((list *) v21670)->addFast((OID)_oid_(v56377));
                        { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                            _void_(v60472->selector = Core.make_copy_list);
                            { Call * v21671 = v60472; 
                              list * v21672;
                              { OID v_bag;
                                GC_ANY(v21672= list::empty(Kernel.emptySet));
                                ((list *) v21672)->addFast((OID)((OID)OBJECT(table,v56356)->graph->length));
                                { if ((*Kernel.params)(v56356) == _oid_(Kernel._any))
                                   v_bag = CNULL;
                                  else v_bag = (*Kernel.DEFAULT)(v56356);
                                    GC_OID(v_bag);}
                                ((list *) v21672)->addFast((OID)v_bag);}
                              _void_(v21671->args = v21672);}
                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                            v_bag = _oid_(close_Instruction1(v60472));
                            }
                          GC_OID(v_bag);}
                        ((list *) v21670)->addFast((OID)v_bag);}
                      _void_(v21669->args = v21670);}
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                    v50758 = _oid_(close_Instruction1(v60472));
                    }
                  GC_OID(v50758);}
                v43491 = v43491->addFast((OID)v50758);
                }
              GC_OBJECT(list,v43491);}
            { { OID  v55563;
                { if (INHERIT(OWNER(v8221),Core._lambda))
                   { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                    store_object(v60472,
                      2,
                      Kernel._object,
                      (*(v8217))[2],
                      CFALSE);
                    _void_(v60472->set_arg = (*(OBJECT(bag,v8235)))[1]);
                    { Iteration * v21676 = v60472; 
                      OID  v21677;
                      { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                        store_object(v60472,
                          2,
                          Kernel._object,
                          (*(v8217))[3],
                          CFALSE);
                        _void_(v60472->set_arg = _oid_(v58727));
                        { Iteration * v21678 = v60472; 
                          OID  v21679;
                          { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                            _void_(v60472->selector = Kernel.nth_equal);
                            _void_(v60472->args = list::alloc(4,_oid_(v56377),
                              (*(v8217))[2],
                              (*(v8217))[3],
                              GC_OID(OBJECT(lambda,v8221)->body)));
                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                            v21679 = _oid_(close_Instruction1(v60472));
                            }
                          _void_(v21678->arg = v21679);}
                        add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                        v21677 = _oid_(close_Instruction1(v60472));
                        }
                      _void_(v21676->arg = v21677);}
                    add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                    v55563 = _oid_(close_Instruction1(v60472));
                    }
                  else { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Kernel.put);
                      _void_(v60472->args = list::alloc(3,_oid_(Kernel.DEFAULT),
                        _oid_(v56377),
                        v8220));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v55563 = _oid_(close_Instruction1(v60472));
                      }
                    GC_OID(v55563);}
                v43491 = v43491->addFast((OID)v55563);
                }
              GC_OBJECT(list,v43491);}
            }
          GC_OBJECT(list,Optimize.OPT->objects)->addFast((OID)v56356);
        (*Optimize.c_register)(v56356);
        { OID  v15013;
          { { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
              { Do * v21700 = v60472; 
                list * v21701;
                { OID  v17896;
                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Optimize.object_I);
                      _void_(v60472->args = list::alloc(2,GC_OID((*Kernel.name)(v56356)),_oid_(Kernel._table)));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v17896 = _oid_(close_Instruction1(v60472));
                      }
                    GC_OID(v17896);}
                  v21701 = cons_any(v17896,GC_OBJECT(list,add_star_list(v43490,v43491)));
                  }
                _void_(v21700->args = v21701);}
              add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
              v15013 = _oid_(close_Instruction1(v60472));
              }
            GC_OID(v15013);}
          Result = (*Optimize.c_code)(v15013,
            _oid_(Kernel._any));
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  compute_if_write_inverse_relation2(ClaireRelation *v8203) { 
    
    GC_BIND;
    { Variable * v8240;
      { { Instruction *V_CC ;
          { Variable * v60472 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
            _void_(v60472->pname = symbol_I_string2(((char*)"XX")));
            _void_(v60472->range = v8203->domain);
            add_I_property(Kernel.instances,Language._Variable,11,_oid_(v60472));
            V_CC = close_Instruction1(v60472);
            }
          v8240= (Variable *) V_CC;}
        GC_OBJECT(Variable,v8240);}
      Variable * v8241;
      { { Instruction *V_CC ;
          { Variable * v60472 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
            _void_(v60472->pname = symbol_I_string2(((char*)"YY")));
            _void_(v60472->range = ((multi_ask_any(_oid_(v8203)) == CTRUE) ?
              member_type(v8203->range) :
              v8203->range ));
            add_I_property(Kernel.instances,Language._Variable,11,_oid_(v60472));
            V_CC = close_Instruction1(v60472);
            }
          v8241= (Variable *) V_CC;}
        GC_OBJECT(Variable,v8241);}
      Variable * v8242;
      { { Instruction *V_CC ;
          { Variable * v60472 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
            _void_(v60472->pname = symbol_I_string2(((char*)"ZZ")));
            _void_(v60472->range = v8203->range);
            add_I_property(Kernel.instances,Language._Variable,11,_oid_(v60472));
            V_CC = close_Instruction1(v60472);
            }
          v8242= (Variable *) V_CC;}
        GC_OBJECT(Variable,v8242);}
      list * v58509 = list::empty(Kernel._any);
      if (multi_ask_any(_oid_(v8203)) == CTRUE)
       { v58509= (list::alloc(Kernel._any,1,GC_OID((INHERIT(v8203->isa,Kernel._property) ?
          Produce_put_property2((property *) OBJECT(property,_oid_(v8203)),OBJECT(Variable,_oid_(v8240)),_oid_(v8241)) : 
          Produce_put_table2((table *) OBJECT(table,_oid_(v8203)),OBJECT(Variable,_oid_(v8240)),_oid_(v8241))))));
        if (((v8203->inverse == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         v58509= (GC_OBJECT(list,v58509->addFast((OID)GC_OID((INHERIT(v8203->inverse->isa,Kernel._property) ?
          Produce_put_property2((property *) OBJECT(property,_oid_(v8203->inverse)),OBJECT(Variable,_oid_(v8241)),_oid_(v8240)) : 
          Produce_put_table2((table *) OBJECT(table,_oid_(v8203->inverse)),OBJECT(Variable,_oid_(v8241)),_oid_(v8240)))))));
        { ClaireRelation * v21703 = v8203; 
          OID  v21704;
          { lambda * v20196;{ OID  v21738;
              { { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                  { If * v21707 = v60472; 
                    OID  v21708;
                    { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Core.NOT);
                      { Call * v21730 = v60472; 
                        list * v21731;
                        { OID v_bag;
                          GC_ANY(v21731= list::empty(Kernel.emptySet));
                          { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                              _void_(v60472->selector = Kernel._Z);
                              _void_(v60472->args = list::alloc(2,_oid_(v8241),GC_OID(Produce_get_relation2(v8203,v8240))));
                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                              v_bag = _oid_(close_Instruction1(v60472));
                              }
                            GC_OID(v_bag);}
                          ((list *) v21731)->addFast((OID)v_bag);}
                        _void_(v21730->args = v21731);}
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v21708 = _oid_(close_Instruction1(v60472));
                      }
                    _void_(v21707->test = v21708);}
                  { If * v21732 = v60472; 
                    OID  v21733;
                    { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                      _void_(v60472->args = v58509);
                      add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                      v21733 = _oid_(close_Instruction1(v60472));
                      }
                    _void_(v21732->arg = v21733);}
                  add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                  _void_(v60472->other = Kernel.cfalse);
                  v21738 = _oid_(close_Instruction1(v60472));
                  }
                GC_OID(v21738);}
              v20196 = lambda_I_list(list::alloc(2,_oid_(v8240),_oid_(v8241)),v21738);
              }
            
            v21704=_oid_(v20196);}
          _void_(v21703->if_write = v21704);}
        }
      else { v58509= (list::alloc(Kernel._any,1,GC_OID((INHERIT(v8203->isa,Kernel._property) ?
            Produce_put_property2((property *) OBJECT(property,_oid_(v8203)),OBJECT(Variable,_oid_(v8240)),_oid_(v8241)) : 
            Produce_put_table2((table *) OBJECT(table,_oid_(v8203)),OBJECT(Variable,_oid_(v8240)),_oid_(v8241))))));
          if (((v8203->inverse == (NULL)) ? CTRUE : CFALSE) != CTRUE)
           { { { OID  v48646;
                { { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                    { If * v21735 = v60472; 
                      OID  v21736;
                      { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        _void_(v60472->selector = Core.known_ask);
                        _void_(v60472->args = list::alloc(1,_oid_(v8242)));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                        v21736 = _oid_(close_Instruction1(v60472));
                        }
                      _void_(v21735->test = v21736);}
                    _void_(v60472->arg = (INHERIT(v8203->inverse->isa,Kernel._property) ?
                      Produce_remove_property2((property *) OBJECT(property,_oid_(v8203->inverse)),OBJECT(Variable,_oid_(v8242)),_oid_(v8240)) : 
                      Produce_remove_table2((table *) OBJECT(table,_oid_(v8203->inverse)),OBJECT(Variable,_oid_(v8242)),_oid_(v8240))));
                    add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                    _void_(v60472->other = Kernel.cfalse);
                    v48646 = _oid_(close_Instruction1(v60472));
                    }
                  GC_OID(v48646);}
                v58509 = v58509->addFast((OID)v48646);
                }
              GC_OBJECT(list,v58509);}
            v58509= (GC_OBJECT(list,v58509->addFast((OID)GC_OID((INHERIT(v8203->inverse->isa,Kernel._property) ?
              Produce_put_property2((property *) OBJECT(property,_oid_(v8203->inverse)),OBJECT(Variable,_oid_(v8241)),_oid_(v8240)) : 
              Produce_put_table2((table *) OBJECT(table,_oid_(v8203->inverse)),OBJECT(Variable,_oid_(v8241)),_oid_(v8240)))))));
            }
          { ClaireRelation * v21737 = v8203; 
            OID  v21739;
            { lambda * v20230;{ OID  v9057;
                { { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                    _void_(v60472->var = v8242);
                    _void_(v60472->value = Produce_get_relation2(v8203,v8240));
                    { Let * v21762 = v60472; 
                      OID  v21763;
                      { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                        { If * v21764 = v60472; 
                          OID  v21765;
                          { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                            _void_(v60472->selector = Core._I_equal);
                            _void_(v60472->args = list::alloc(2,_oid_(v8241),_oid_(v8242)));
                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                            v21765 = _oid_(close_Instruction1(v60472));
                            }
                          _void_(v21764->test = v21765);}
                        { If * v21766 = v60472; 
                          OID  v21767;
                          { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                            _void_(v60472->args = v58509);
                            add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                            v21767 = _oid_(close_Instruction1(v60472));
                            }
                          _void_(v21766->arg = v21767);}
                        add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                        _void_(v60472->other = Kernel.cfalse);
                        v21763 = _oid_(close_Instruction1(v60472));
                        }
                      _void_(v21762->arg = v21763);}
                    add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                    v9057 = _oid_(close_Instruction1(v60472));
                    }
                  GC_OID(v9057);}
                v20230 = lambda_I_list(list::alloc(2,_oid_(v8240),_oid_(v8241)),v9057);
                }
              
              v21739=_oid_(v20230);}
            _void_(v21737->if_write = v21739);}
          }
        { char * v58322 = GC_STRING(append_string(string_I_symbol(v8203->name),((char*)"_write")));
        compile_lambda_string(v58322,GC_OBJECT(lambda,OBJECT(lambda,v8203->if_write)),_oid_(Kernel._void));
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT OID  compute_set_write_relation2(ClaireRelation *v8203) { 
    
    GC_BIND;
    { OID Result = 0;
      { Variable * v8240;
        { { Instruction *V_CC ;
            { Variable * v60472 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(v60472->pname = symbol_I_string2(((char*)"XX")));
              _void_(v60472->range = v8203->domain);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v8240= (Variable *) V_CC;}
          GC_OBJECT(Variable,v8240);}
        Variable * v8241;
        { { Instruction *V_CC ;
            { Variable * v60472 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(v60472->pname = symbol_I_string2(((char*)"YY")));
              _void_(v60472->range = Kernel._bag);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v8241= (Variable *) V_CC;}
          GC_OBJECT(Variable,v8241);}
        Variable * v8242;
        { { Instruction *V_CC ;
            { Variable * v60472 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(v60472->pname = symbol_I_string2(((char*)"ZZ")));
              _void_(v60472->range = member_type(v8203->range));
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v8242= (Variable *) V_CC;}
          GC_OBJECT(Variable,v8242);}
        list * v58509 = list::empty(Kernel._any);
        if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
         mtformat_module1(Optimize.it,((char*)"compute set_write for ~S \n"),0,list::alloc(1,_oid_(v8203)));
        else ;if (((v8203->inverse == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         { { OID  v15784;
            { { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                _void_(v60472->var = v8242);
                _void_(v60472->set_arg = Produce_get_relation2(v8203,v8240));
                _void_(v60472->arg = (INHERIT(v8203->inverse->isa,Kernel._property) ?
                  Produce_remove_property2((property *) OBJECT(property,_oid_(v8203->inverse)),OBJECT(Variable,_oid_(v8242)),_oid_(v8240)) : 
                  Produce_remove_table2((table *) OBJECT(table,_oid_(v8203->inverse)),OBJECT(Variable,_oid_(v8242)),_oid_(v8240))));
                add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                v15784 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v15784);}
            v58509 = v58509->addFast((OID)v15784);
            }
          GC_OBJECT(list,v58509);}
        v58509= (GC_OBJECT(list,v58509->addFast((OID)GC_OID(Produce_erase_property2(((property *) v8203),v8240)))));
        { { OID  v16745;
            { { For * v60472 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                _void_(v60472->var = v8242);
                _void_(v60472->set_arg = _oid_(v8241));
                _void_(v60472->arg = (INHERIT(v8203->isa,Kernel._property) ?
                  Produce_put_property2((property *) OBJECT(property,_oid_(v8203)),OBJECT(Variable,_oid_(v8240)),_oid_(v8242)) : 
                  Produce_put_table2((table *) OBJECT(table,_oid_(v8203)),OBJECT(Variable,_oid_(v8240)),_oid_(v8242))));
                add_I_property(Kernel.instances,Language._For,11,_oid_(v60472));
                v16745 = _oid_(close_Instruction1(v60472));
                }
              GC_OID(v16745);}
            v58509 = v58509->addFast((OID)v16745);
            }
          GC_OBJECT(list,v58509);}
        { char * v58322 = GC_STRING(append_string(string_I_symbol(v8203->name),((char*)"_set_write")));
          { lambda * v17706;
            { { OID  v38848;
                { { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                    _void_(v60472->args = v58509);
                    add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                    v38848 = _oid_(close_Instruction1(v60472));
                    }
                  GC_OID(v38848);}
                v17706 = lambda_I_list(list::alloc(2,_oid_(v8240),_oid_(v8241)),v38848);
                }
              GC_OBJECT(lambda,v17706);}
            Result = compile_lambda_string(v58322,v17706,_oid_(Kernel._void));
            }
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  Produce_put_property2(property *v8234,Variable *v8240,OID v8241) { 
    
    GC_BIND;
    { OID Result = 0;
      { list * v8228 = list::empty(Kernel._any);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v58947);
          for (START(v8234->restrictions); NEXT(v58947);)
          { GC_LOOP;
            if ((Kernel._slot == OBJECT(ClaireObject,v58947)->isa) && 
                (boolean_I_any(_oid_(_exp_type(GC_OBJECT(ClaireType,ptype_type(v8240->range)),domain_I_restriction(OBJECT(restriction,v58947))))) == CTRUE))
             { list * v39809;
              { { OID v_bag;
                  GC_ANY(v39809= list::empty(Kernel.emptySet));
                  ((list *) v39809)->addFast((OID)_oid_(domain_I_restriction(OBJECT(restriction,v58947))));
                  { if (boolean_I_any(_oid_(v8234->multivalued_ask)) == CTRUE)
                     { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Kernel.add_I);
                      { Call * v21794 = v60472; 
                        list * v21795;
                        { OID v_bag;
                          GC_ANY(v21795= list::empty(Kernel.emptySet));
                          { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                              _void_(v60472->selector = v8234);
                              { Call * v21796 = v60472; 
                                list * v21797;
                                { OID v_bag;
                                  GC_ANY(v21797= list::empty(Kernel.emptySet));
                                  { { Cast * v60472 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                                      _void_(v60472->arg = _oid_(v8240));
                                      _void_(v60472->set_arg = domain_I_restriction(OBJECT(restriction,v58947)));
                                      add_I_property(Kernel.instances,Language._Cast,11,_oid_(v60472));
                                      v_bag = _oid_(close_Instruction1(v60472));
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v21797)->addFast((OID)v_bag);}
                                _void_(v21796->args = v21797);}
                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                              v_bag = _oid_(close_Instruction1(v60472));
                              }
                            GC_OID(v_bag);}
                          ((list *) v21795)->addFast((OID)v_bag);
                          ((list *) v21795)->addFast((OID)v8241);}
                        _void_(v21794->args = v21795);}
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v_bag = _oid_(close_Instruction1(v60472));
                      }
                    else { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        _void_(v60472->selector = Kernel.put);
                        { Call * v21798 = v60472; 
                          list * v21799;
                          { OID v_bag;
                            GC_ANY(v21799= list::empty(Kernel.emptySet));
                            ((list *) v21799)->addFast((OID)_oid_(v8234));
                            { { Cast * v60472 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                                _void_(v60472->arg = _oid_(v8240));
                                _void_(v60472->set_arg = domain_I_restriction(OBJECT(restriction,v58947)));
                                add_I_property(Kernel.instances,Language._Cast,11,_oid_(v60472));
                                v_bag = _oid_(close_Instruction1(v60472));
                                }
                              GC_OID(v_bag);}
                            ((list *) v21799)->addFast((OID)v_bag);
                            ((list *) v21799)->addFast((OID)v8241);}
                          _void_(v21798->args = v21799);}
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                        v_bag = _oid_(close_Instruction1(v60472));
                        }
                      GC_OID(v_bag);}
                  ((list *) v39809)->addFast((OID)v_bag);}
                GC_OBJECT(list,v39809);}
              v8228 = add_star_list(v8228,v39809);
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        if (v8228->length == 2)
         Result = (*(v8228))[2];
        else { Case * v60472 = ((Case *) GC_OBJECT(Case,new_object_class(Language._Case)));
            _void_(v60472->var = _oid_(v8240));
            _void_(v60472->args = v8228);
            add_I_property(Kernel.instances,Language._Case,11,_oid_(v60472));
            Result = _oid_(close_Instruction1(v60472));
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  Produce_erase_property2(property *v8234,Variable *v8240) { 
    
    GC_BIND;
    { OID Result = 0;
      { list * v8228 = list::empty(Kernel._any);
        bag * v55513;
        if (v8234->multivalued_ask == Kernel._list)
         v55513 = list::empty(Kernel._any);
        else v55513 = set::empty(Kernel._any);
          _oid_((INHERIT(v55513->isa,Kernel._list) ?
         (ClaireObject *) cast_I_list1((list *) OBJECT(list,_oid_(v55513)),OBJECT(ClaireType,GC_OID(_oid_(member_type(v8234->range))))) : 
         (ClaireObject *)  cast_I_set1((set *) OBJECT(set,_oid_(v55513)),OBJECT(ClaireType,GC_OID(_oid_(member_type(v8234->range)))))));
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v58947);
          for (START(v8234->restrictions); NEXT(v58947);)
          { GC_LOOP;
            if ((Kernel._slot == OBJECT(ClaireObject,v58947)->isa) && 
                (boolean_I_any(_oid_(_exp_type(GC_OBJECT(ClaireType,ptype_type(v8240->range)),domain_I_restriction(OBJECT(restriction,v58947))))) == CTRUE))
             { list * v46536;
              { { OID v_bag;
                  GC_ANY(v46536= list::empty(Kernel.emptySet));
                  ((list *) v46536)->addFast((OID)_oid_(domain_I_restriction(OBJECT(restriction,v58947))));
                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Kernel.put);
                      { Call * v21801 = v60472; 
                        list * v21823;
                        { OID v_bag;
                          GC_ANY(v21823= list::empty(Kernel.emptySet));
                          ((list *) v21823)->addFast((OID)_oid_(v8234));
                          { { Cast * v60472 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                              _void_(v60472->arg = _oid_(v8240));
                              _void_(v60472->set_arg = domain_I_restriction(OBJECT(restriction,v58947)));
                              add_I_property(Kernel.instances,Language._Cast,11,_oid_(v60472));
                              v_bag = _oid_(close_Instruction1(v60472));
                              }
                            GC_OID(v_bag);}
                          ((list *) v21823)->addFast((OID)v_bag);
                          { if (boolean_I_any(_oid_(v8234->multivalued_ask)) == CTRUE)
                             v_bag = _oid_(v55513);
                            else v_bag = OBJECT(slot,v58947)->DEFAULT;
                              GC_OID(v_bag);}
                          ((list *) v21823)->addFast((OID)v_bag);}
                        _void_(v21801->args = v21823);}
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v_bag = _oid_(close_Instruction1(v60472));
                      }
                    GC_OID(v_bag);}
                  ((list *) v46536)->addFast((OID)v_bag);}
                GC_OBJECT(list,v46536);}
              v8228 = add_star_list(v8228,v46536);
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        if (v8228->length == 2)
         Result = (*(v8228))[2];
        else { Case * v60472 = ((Case *) GC_OBJECT(Case,new_object_class(Language._Case)));
            _void_(v60472->var = _oid_(v8240));
            _void_(v60472->args = v8228);
            add_I_property(Kernel.instances,Language._Case,11,_oid_(v60472));
            Result = _oid_(close_Instruction1(v60472));
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  Produce_put_table2(table *v8234,Variable *v8240,OID v8241) { 
    
    GC_BIND;
    { OID Result = 0;
      { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
        _void_(v60472->selector = Kernel.put);
        { Call * v21824 = v60472; 
          list * v21825;
          { OID v_bag;
            GC_ANY(v21825= list::empty(Kernel.emptySet));
            ((list *) v21825)->addFast((OID)_oid_(v8234));
            ((list *) v21825)->addFast((OID)_oid_(v8240));
            { if (boolean_I_any(_oid_(v8234->multivalued_ask)) == CTRUE)
               { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(v60472->selector = Kernel.add);
                _void_(v60472->args = list::alloc(2,_oid_(list::alloc(2,_oid_(Kernel.nth),_oid_(list::alloc(2,_oid_(v8234),_oid_(v8240))))),v8241));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v_bag = _oid_(close_Instruction1(v60472));
                }
              else v_bag = v8241;
                GC_OID(v_bag);}
            ((list *) v21825)->addFast((OID)v_bag);}
          _void_(v21824->args = v21825);}
        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  Produce_get_relation2(ClaireRelation *v8234,Variable *v8240) { 
    
    GC_BIND;
    { OID Result = 0;
      if (INHERIT(v8234->isa,Kernel._table))
       { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
        _void_(v60472->selector = Kernel.nth);
        _void_(v60472->args = list::alloc(2,_oid_(v8234),_oid_(v8240)));
        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      else if (INHERIT(v8234->isa,Kernel._property))
       { list * v8228 = list::empty(Kernel._any);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v58947);
          for (START(CLREAD(property,v8234,restrictions)); NEXT(v58947);)
          { GC_LOOP;
            if ((Kernel._slot == OBJECT(ClaireObject,v58947)->isa) && 
                (boolean_I_any(_oid_(_exp_type(GC_OBJECT(ClaireType,ptype_type(v8240->range)),domain_I_restriction(OBJECT(restriction,v58947))))) == CTRUE))
             { list * v5986;
              { { OID v_bag;
                  GC_ANY(v5986= list::empty(Kernel.emptySet));
                  ((list *) v5986)->addFast((OID)_oid_(domain_I_restriction(OBJECT(restriction,v58947))));
                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = ((property *) v8234));
                      { Call * v21827 = v60472; 
                        list * v21828;
                        { OID v_bag;
                          GC_ANY(v21828= list::empty(Kernel.emptySet));
                          { { Cast * v60472 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                              _void_(v60472->arg = _oid_(v8240));
                              _void_(v60472->set_arg = domain_I_restriction(OBJECT(restriction,v58947)));
                              add_I_property(Kernel.instances,Language._Cast,11,_oid_(v60472));
                              v_bag = _oid_(close_Instruction1(v60472));
                              }
                            GC_OID(v_bag);}
                          ((list *) v21828)->addFast((OID)v_bag);}
                        _void_(v21827->args = v21828);}
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v_bag = _oid_(close_Instruction1(v60472));
                      }
                    GC_OID(v_bag);}
                  ((list *) v5986)->addFast((OID)v_bag);}
                GC_OBJECT(list,v5986);}
              v8228 = add_star_list(v8228,v5986);
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        if (v8228->length == 2)
         Result = (*(v8228))[2];
        else { Case * v60472 = ((Case *) GC_OBJECT(Case,new_object_class(Language._Case)));
            _void_(v60472->var = _oid_(v8240));
            _void_(v60472->args = v8228);
            add_I_property(Kernel.instances,Language._Case,11,_oid_(v60472));
            Result = _oid_(close_Instruction1(v60472));
            }
          }
      else Result = Kernel.cfalse;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  Produce_remove_property2(property *v8234,Variable *v8240,OID v8241) { 
    
    GC_BIND;
    { OID Result = 0;
      { list * v8228 = list::empty(Kernel._any);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v58947);
          for (START(v8234->restrictions); NEXT(v58947);)
          { GC_LOOP;
            if (Kernel._slot == OBJECT(ClaireObject,v58947)->isa)
             { list * v8869;
              { { OID v_bag;
                  GC_ANY(v8869= list::empty(Kernel.emptySet));
                  ((list *) v8869)->addFast((OID)_oid_(domain_I_restriction(OBJECT(restriction,v58947))));
                  { if (boolean_I_any(_oid_(v8234->multivalued_ask)) == CTRUE)
                     { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Kernel._delete);
                      { Call * v21830 = v60472; 
                        list * v21831;
                        { OID v_bag;
                          GC_ANY(v21831= list::empty(Kernel.emptySet));
                          { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                              _void_(v60472->selector = v8234);
                              _void_(v60472->args = list::alloc(1,_oid_(v8240)));
                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                              v_bag = _oid_(close_Instruction1(v60472));
                              }
                            GC_OID(v_bag);}
                          ((list *) v21831)->addFast((OID)v_bag);
                          ((list *) v21831)->addFast((OID)v8241);}
                        _void_(v21830->args = v21831);}
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v_bag = _oid_(close_Instruction1(v60472));
                      }
                    else { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        _void_(v60472->selector = Kernel.put);
                        _void_(v60472->args = list::alloc(3,_oid_(v8234),
                          _oid_(v8240),
                          CNULL));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                        v_bag = _oid_(close_Instruction1(v60472));
                        }
                      GC_OID(v_bag);}
                  ((list *) v8869)->addFast((OID)v_bag);}
                GC_OBJECT(list,v8869);}
              v8228 = add_star_list(v8228,v8869);
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        if (v8228->length == 2)
         Result = (*(v8228))[2];
        else { Case * v60472 = ((Case *) GC_OBJECT(Case,new_object_class(Language._Case)));
            _void_(v60472->var = _oid_(v8240));
            _void_(v60472->args = v8228);
            add_I_property(Kernel.instances,Language._Case,11,_oid_(v60472));
            Result = _oid_(close_Instruction1(v60472));
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  Produce_remove_table2(table *v8234,Variable *v8240,OID v8241) { 
    
    GC_BIND;
    { OID Result = 0;
      { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
        _void_(v60472->selector = Kernel.put);
        { Call * v21832 = v60472; 
          list * v21854;
          { OID v_bag;
            GC_ANY(v21854= list::empty(Kernel.emptySet));
            ((list *) v21854)->addFast((OID)_oid_(v8234));
            ((list *) v21854)->addFast((OID)_oid_(v8240));
            { if (boolean_I_any(_oid_(v8234->multivalued_ask)) == CTRUE)
               { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(v60472->selector = Kernel._delete);
                _void_(v60472->args = list::alloc(2,_oid_(list::alloc(2,_oid_(Kernel.nth),_oid_(list::alloc(2,_oid_(v8234),_oid_(v8240))))),v8241));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                v_bag = _oid_(close_Instruction1(v60472));
                }
              else v_bag = CNULL;
                GC_OID(v_bag);}
            ((list *) v21854)->addFast((OID)v_bag);}
          _void_(v21832->args = v21854);}
        add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
        Result = _oid_(close_Instruction1(v60472));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  Tighten_relation2(ClaireRelation *v8234) { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    if (INHERIT(v8234->isa,Kernel._property))
     { ClaireType * v58220 = set::empty();
      ClaireType * v58234 = set::empty();
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v8235);
        for (START(CLREAD(property,v8234,restrictions)); NEXT(v8235);)
        { GC_LOOP;
          if (Kernel._slot == OBJECT(ClaireObject,v8235)->isa)
           { GC__ANY(v58220 = U_type(v58220,domain_I_restriction(OBJECT(restriction,v8235))), 1);
            GC__ANY(v58234 = U_type(v58234,GC_OBJECT(ClaireType,((multi_ask_any(_oid_(v8234)) == CTRUE) ?
              member_type(OBJECT(restriction,v8235)->range) :
              OBJECT(restriction,v8235)->range ))), 2);
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      _void_(v8234->open = 1);
      _void_(v8234->domain = class_I_type(v58220));
      _void_(v8234->range = ((v8234->multivalued_ask == Kernel._list) ?
        param_I_class(Kernel._list,class_I_type(v58234)) :
        ((v8234->multivalued_ask == Kernel._set) ?
          param_I_class(Kernel._set,class_I_type(v58234)) :
          v58234 ) ));
      if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
       mtformat_module1(Optimize.it,((char*)"~S -> ~S x ~S\n"),5,GC_OBJECT(list,list::alloc(3,_oid_(v8234),
        _oid_(v8234->domain),
        _oid_(v8234->range))));
      else ;}
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  lexical_num_any2(OID v62612,int v8230) { 
    
    GC_BIND;
    if (INHERIT(OWNER(v62612),Language._Call))
     lexical_num_any2(GC_OID(_oid_(OBJECT(Call,v62612)->args)),v8230);
    else if (INHERIT(OWNER(v62612),Language._Instruction))
     { ClaireClass * v30871 = OBJECT(ClaireObject,v62612)->isa;
      if (contain_ask_set(Language._Instruction_with_var->descendents,_oid_(v30871)) == CTRUE)
       { put_property2(Kernel.index,GC_OBJECT(ClaireObject,OBJECT(ClaireObject,(*Language.var)(v62612))),((OID)v8230));
        ++v8230;
        if ((CL_INT)v8230 > (CL_INT)((CL_INT)Language._starvariable_index_star->value))
         (Language._starvariable_index_star->value= ((OID)v8230));
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v8235);
        for (START(v30871->slots); NEXT(v8235);)
        lexical_num_any2(get_slot(OBJECT(slot,v8235),OBJECT(ClaireObject,v62612)),v8230);
        }
      }
    else if (INHERIT(OWNER(v62612),Kernel._bag))
     { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v8240);
      for (START(OBJECT(bag,v62612)); NEXT(v8240);)
      lexical_num_any2(v8240,v8230);
      }
    else ;GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT ClaireType * c_type_Defrule2_Optimize(Defrule *v62612) { 
    POP_SIGNAL; return (Kernel._any);}
  

CL_EXPORT OID  c_code_Defrule_Optimize(Defrule *v62612,ClaireClass *v8235) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { OID Result = 0;
      { OID  v58763 = get_symbol(v62612->ident);
        list * v8228 = list::empty(Kernel._any);
        if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
         mtformat_module1(Optimize.it,((char*)"compile a rule ~S \n"),0,list::alloc(1,v58763));
        else ;{ CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(v8234);
          bag *v8234_support;
          v8234_support = OBJECT(set,nth_table1(Language.relations,v58763));
          for (START(v8234_support); NEXT(v8234);)
          if (eventMethod_ask_relation2(OBJECT(ClaireRelation,v8234)) != CTRUE)
           Tighten_relation2(OBJECT(ClaireRelation,v8234));
          }
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v8234);
          bag *v8234_support;
          v8234_support = OBJECT(set,nth_table1(Language.relations,v58763));
          for (START(v8234_support); NEXT(v8234);)
          { GC_LOOP;
            { if ((CL_INT)((CL_INT)(*Kernel.open)(v8234)) < (CL_INT)2)
               { { OID  v33855;
                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Kernel.FINAL);
                      _void_(v60472->args = list::alloc(1,v8234));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v33855 = _oid_(close_Instruction1(v60472));
                      }
                    GC_OID(v33855);}
                  v8228 = v8228->addFast((OID)v33855);
                  }
                 GC__ANY(v8228, 1);}
              compile_if_write_relation(OBJECT(ClaireRelation,v8234));
              { OID  v58322 = GC_OID((*Kernel._7_plus)(GC_OID((*Kernel.name)(v8234)),
                  _string_(((char*)"_write"))));
                char * v8235 = string_I_symbol(OBJECT(symbol,v58322));
                OID  v58558 = GC_OID((*Kernel.if_write)(v8234));
                compile_lambda_string(v8235,OBJECT(lambda,v58558),_oid_(Kernel._void));
                { OID  v34816;
                  { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(v60472->selector = Kernel.put);
                      _void_(v60472->args = list::alloc(3,Optimize.if_write->value,
                        v8234,
                        _oid_(make_function_string(v8235))));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                      v34816 = _oid_(close_Instruction1(v60472));
                      }
                    GC_OID(v34816);}
                  v8228->addFast((OID)v34816);
                  }
                }
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v8234);
          bag *v8234_support;
          v8234_support = OBJECT(set,nth_table1(Language.relations,v58763));
          for (START(v8234_support); NEXT(v8234);)
          { GC_LOOP;
            if (eventMethod_ask_relation2(OBJECT(ClaireRelation,v8234)) == CTRUE)
             v8228= (v8228->addFast((OID)GC_OID(compileEventMethod_property(OBJECT(property,v8234)))));
            GC_UNLOOP; POP_SIGNAL;}
          }
        { OID  v35777;
          { { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
              _void_(v60472->args = v8228);
              add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
              v35777 = _oid_(close_Instruction1(v60472));
              }
            GC_OID(v35777);}
          Result = (*Optimize.c_code)(v35777,
            _oid_(v8235));
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  compile_if_write_relation(ClaireRelation *v8203) { 
    
    GC_BIND;
    { OID  v8228 = nth_table1(Language.demons,_oid_(v8203));
      list * v1155 = GC_OBJECT(list,OBJECT(Language_demon,(*(OBJECT(bag,v8228)))[1])->formula->vars);
      list * v58509 = list::alloc(Kernel._any,1,GC_OID((*Optimize.Produce_put)(_oid_(v8203),
        (*(v1155))[1],
        (*(v1155))[2])));
      list * v58510;
      { { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          bag *v_list; OID v_val;
          OID v8240; CL_INT CLcount;
          v_list = OBJECT(list,v8228);
           v58510 = v_list->clone(Kernel._any);
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { GC_LOOP;
            v8240 = (*(v_list))[CLcount];
            v_val = substitution_any(GC_OID(substitution_any(GC_OID(substitution_any(GC_OID(OBJECT(Language_demon,v8240)->formula->body),GC_OBJECT(Variable,OBJECT(Variable,(*(OBJECT(Language_demon,v8240)->formula->vars))[3])),(*(v1155))[3])),GC_OBJECT(Variable,OBJECT(Variable,(*(OBJECT(Language_demon,v8240)->formula->vars))[1])),(*(v1155))[1])),GC_OBJECT(Variable,OBJECT(Variable,(*(OBJECT(Language_demon,v8240)->formula->vars))[2])),(*(v1155))[2]);
            
            (*((list *) v58510))[CLcount] = v_val;GC_UNLOOP; POP_SIGNAL;}
          }
        GC_OBJECT(list,v58510);}
      put_property2(Kernel.range,OBJECT(ClaireObject,(*(v1155))[1]),_oid_(v8203->domain));
      put_property2(Kernel.range,OBJECT(ClaireObject,(*(v1155))[2]),_oid_(v8203->range));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v8238);
        for (START(v1155); NEXT(v8238);)
        { GC_LOOP;
          put_property2(Kernel.range,OBJECT(ClaireObject,v8238),_oid_(class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(v8238))))));
          GC_UNLOOP; POP_SIGNAL;}
        }
      if ((INHERIT(OWNER((*(v58510))[1]),Language._If)) && 
          (eventMethod_ask_relation2(v8203) != CTRUE))
       { if (INHERIT(OWNER(OBJECT(If,(*(v58510))[1])->test),Language._And))
         { If * v21858 = OBJECT(If,(*(v58510))[1]); 
          OID  v21859;
          { And * v60472 = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
            _void_(v60472->args = cdr_list(GC_OBJECT(list,OBJECT(list,(*Core.args)(GC_OID(OBJECT(If,(*(v58510))[1])->test))))));
            add_I_property(Kernel.instances,Language._And,11,_oid_(v60472));
            v21859 = _oid_(close_Instruction1(v60472));
            }
          _void_(v21858->test = v21859);}
        else ((*(v58510))[1]=GC_OID(OBJECT(If,(*(v58510))[1])->arg));
          }
      if (((v8203->inverse == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       { if (multi_ask_any(_oid_(v8203)) != CTRUE)
         v58509= (v58509->addFast((OID)GC_OID((*Optimize.Produce_remove)(_oid_(v8203->inverse),
          (*(v1155))[3],
          (*(v1155))[1]))));
        v58509= (v58509->addFast((OID)GC_OID((*Optimize.Produce_put)(_oid_(v8203->inverse),
          (*(v1155))[2],
          (*(v1155))[1]))));
        }
      { ClaireRelation * v21860 = v8203; 
        OID  v21861;
        { lambda * v20353;{ OID  v41543;
            { if (eventMethod_ask_relation2(v8203) == CTRUE)
               { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                _void_(v60472->args = v58510);
                add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                v41543 = _oid_(close_Instruction1(v60472));
                }
              else if (multi_ask_any(_oid_(v8203)) == CTRUE)
               { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                { If * v21885 = v60472; 
                  OID  v21886;
                  { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(v60472->selector = Core.NOT);
                    { Call * v21887 = v60472; 
                      list * v21888;
                      { OID v_bag;
                        GC_ANY(v21888= list::empty(Kernel.emptySet));
                        { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                            _void_(v60472->selector = Kernel._Z);
                            _void_(v60472->args = list::alloc(2,(*(v1155))[2],GC_OID(_oid_(readCall_relation(v8203,(*(v1155))[1])))));
                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                            v_bag = _oid_(close_Instruction1(v60472));
                            }
                          GC_OID(v_bag);}
                        ((list *) v21888)->addFast((OID)v_bag);}
                      _void_(v21887->args = v21888);}
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                    v21886 = _oid_(close_Instruction1(v60472));
                    }
                  _void_(v21885->test = v21886);}
                { If * v21889 = v60472; 
                  OID  v21891;
                  { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                    _void_(v60472->args = append_list(v58509,v58510));
                    add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                    v21891 = _oid_(close_Instruction1(v60472));
                    }
                  _void_(v21889->arg = v21891);}
                add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                _void_(v60472->other = Kernel.cfalse);
                v41543 = _oid_(close_Instruction1(v60472));
                }
              else { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                  store_object(v60472,
                    2,
                    Kernel._object,
                    (*(v1155))[3],
                    CFALSE);
                  _void_(v60472->value = _oid_(readCall_relation(v8203,(*(v1155))[1])));
                  { Let * v21892 = v60472; 
                    OID  v21893;
                    { If * v60472 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                      { If * v21895 = v60472; 
                        OID  v21896;
                        { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          _void_(v60472->selector = Core._I_equal);
                          _void_(v60472->args = list::alloc(2,(*(v1155))[2],(*(v1155))[3]));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                          v21896 = _oid_(close_Instruction1(v60472));
                          }
                        _void_(v21895->test = v21896);}
                      { If * v21916 = v60472; 
                        OID  v21917;
                        { Do * v60472 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                          _void_(v60472->args = append_list(v58509,v58510));
                          add_I_property(Kernel.instances,Language._Do,11,_oid_(v60472));
                          v21917 = _oid_(close_Instruction1(v60472));
                          }
                        _void_(v21916->arg = v21917);}
                      add_I_property(Kernel.instances,Language._If,11,_oid_(v60472));
                      _void_(v60472->other = Kernel.cfalse);
                      v21893 = _oid_(close_Instruction1(v60472));
                      }
                    _void_(v21892->arg = v21893);}
                  add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
                  v41543 = _oid_(close_Instruction1(v60472));
                  }
                GC_OID(v41543);}
            v20353 = lambda_I_list(GC_OBJECT(list,list::alloc(2,(*(v1155))[1],(*(v1155))[2])),v41543);
            }
          
          v21861=_oid_(v20353);}
        _void_(v21860->if_write = v21861);}
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT OID  compileEventMethod_property(property *v8232) { 
    
    GC_BIND;
    { OID Result = 0;
      { method * v8229 = OBJECT(method,(*(v8232->restrictions))[1]);
        char * v58619 = GC_STRING(append_string(string_I_symbol(v8232->name),((char*)"_write")));
        Result = add_method_I_method(v8229,
          list::alloc(2,_oid_(v8232->domain),_oid_(v8232->range)),
          _oid_(Kernel._void),
          ((OID)0),
          make_function_string(v58619));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  




  

extern "C" CL_EXPORT void dynLoadOptimize() 
{ Optimize.initModule("Optimize",Compile.it,list::alloc(Kernel._module,2,_oid_(Reader.it),_oid_(mClaire.it)),
    "./compile",list::alloc(Kernel._string,5,_string_(((char*)"osystem")),
      _string_(((char*)"otool")),
      _string_(((char*)"ocall")),
      _string_(((char*)"ocontrol")),
      _string_(((char*)"odefine"))));
    Optimize.metaLoad();
    Optimize.it->comment = "Optimize";
    }
  /***** CLAIRE Compilation of file Optimize.cl 
         [version 3.5.0 / safety 5] *****/



CL_EXPORT OptimizeClass Optimize;

CL_EXPORT NameSpace Compile;
// definition of the meta-model for Optimize
  void OptimizeClass::metaLoad() { 
    
    ClEnv->module_I = it;
// definition of the properties 
    
    Optimize.sort_abstract_I = property::make("sort_abstract!",Optimize.it);
    Optimize.warn = property::make("warn",Compile.it);
    Optimize.c_warn = property::make("c_warn",Optimize.it);
    Optimize.open_message = property::make("open_message",Optimize.it);
    Optimize.sort_abstract_ask = property::make("sort_abstract?",Optimize.it);
    Optimize.extended_ask = property::make("extended?",Optimize.it);
    Optimize.extends = property::make("extends",Optimize.it);
    Optimize.enumerate_code = property::make("enumerate_code",Optimize.it);
    Optimize.c_code_method = property::make("c_code_method",Optimize.it);
    Optimize.range_infers_for = property::make("range_infers_for",Optimize.it);
    Optimize.range_infers = property::make("range_infers",Optimize.it);
    Optimize.gc_register = property::make("gc_register",Optimize.it);
    Optimize.range_infer_case = property::make("range_infer_case",Optimize.it);
    Optimize.c_gc_I = property::make("c_gc!",Optimize.it);
    Optimize.range_sets = property::make("range_sets",Optimize.it);
    Optimize.Variable_I = property::make("Variable!",Compile.it);
    Optimize.identifiable_ask = property::make("identifiable?",Compile.it);
    Optimize.c_inline = property::make("c_inline",Optimize.it);
    Optimize.bound_variables = property::make("bound_variables",Optimize.it);
    Optimize.c_substitution = property::make("c_substitution",Optimize.it);
    Optimize.c_inline_arg_ask = property::make("c_inline_arg?",Optimize.it);
    Optimize.restriction_I = property::make("restriction!",Optimize.it);
    Optimize.c_inline_ask = property::make("c_inline?",Optimize.it);
    Optimize.c_boolean = property::make("c_boolean",Optimize.it);
    Optimize.use_range = property::make("use_range",Optimize.it);
    Optimize.inline_optimize_ask = property::make("inline_optimize?",Optimize.it);
    Optimize.daccess = property::make("daccess",Optimize.it);
    Optimize.c_code_write = property::make("c_code_write",Optimize.it);
    Optimize.c_code_hold = property::make("c_code_hold",Optimize.it);
    Optimize.c_code_add = property::make("c_code_add",Optimize.it);
    Optimize.c_code_delete = property::make("c_code_delete",Optimize.it);
    Optimize.c_code_table = property::make("c_code_table",Optimize.it);
    Optimize.c_code_array = property::make("c_code_array",Optimize.it);
    Optimize.c_code_nth = property::make("c_code_nth",Optimize.it);
    Optimize.c_code_belong = property::make("c_code_belong",Optimize.it);
    Optimize.c_code_not = property::make("c_code_not",Optimize.it);
    Optimize.Update_ask = property::make("Update?",Optimize.it);
    Optimize.Call_method_I = property::make("Call_method!",Optimize.it);
    Optimize.nth_type_check = property::make("nth_type_check",Optimize.it);
    Optimize.extendedTest_ask = property::make("extendedTest?",Optimize.it);
    Optimize.Iterate_I = property::make("Iterate!",Optimize.it);
    Optimize.total_ask = property::make("total?",Optimize.it);
    Optimize.analyze_I = property::make("analyze!",Optimize.it);
    Optimize.extract_signature_I = property::make("extract_signature!",Optimize.it);
    Optimize.extract_status_new = property::make("extract_status_new",Optimize.it);
    Optimize.add_method_I = property::make("add_method!",Optimize.it);
    Optimize.showstatus = property::make("showstatus",claire.it);
    Optimize.safe = property::make("safe",claire.it);
    Optimize.overflow_ask = property::make("overflow?",claire.it);
    Optimize.c_code_multiple = property::make("c_code_multiple",Optimize.it);
    Optimize.Produce_put = property::make("Produce_put",Compile.it);
    Optimize.Produce_get = property::make("Produce_get",Compile.it);
    Optimize.Produce_remove = property::make("Produce_remove",Compile.it);
    Optimize.compute_if_write_inverse = property::make("compute_if_write_inverse",Compile.it);
    Optimize.compute_set_write = property::make("compute_set_write",Compile.it);
    Optimize.Tighten = property::make("Tighten",Compile.it);
    Optimize.c_code_add_bag = property::make("c_code_add_bag",Optimize.it);
    Optimize.diet_ask = property::make("diet?",claire.it);
    Optimize.Produce_erase = property::make("Produce_erase",Compile.it);
    Optimize.lexical_num = property::make("lexical_num",Compile.it);
    Optimize.inner2outer_ask = property::make("inner2outer?",Compile.it);
    Optimize.pmember = property::make("pmember",Optimize.it);
    Optimize.c_code_select = property::make("c_code_select",Optimize.it);
    Optimize.inner_select = property::make("inner_select",Optimize.it);
    Optimize.compile_if_write = property::make("compile_if_write",Optimize.it);
    Optimize.compileEventMethod = property::make("compileEventMethod",Optimize.it);
    Optimize.s_test = property::make("s_test",claire.it);
    Optimize.c_srange = property::make("c_srange",Compile.it);
    Optimize.optimize_ask = property::make("optimize?",claire.it);
    Optimize.nativeVar_ask = property::make("nativeVar?",Compile.it);
    Optimize.simple_operations = property::make("simple_operations",Compile.it);
    Optimize.non_identifiable_set = property::make("non_identifiable_set",Compile.it);
    Optimize.sort_pattern_ask = property::make("sort_pattern?",Optimize.it);
    Optimize.sort_code = property::make("sort_code",Optimize.it);
    Optimize.return_type = property::make("return_type",Compile.it);
    Optimize.notice = property::make("notice",Compile.it);
    Optimize.infers_from = property::make("infers_from",Optimize.it);
    Optimize.show_opportunist = property::make("show_opportunist",Optimize.it);
    Optimize.home = property::make("home",claire.it);
    Optimize.instructions = property::make("instructions",2,Compile.it);
    Optimize.objects = property::make("objects",Compile.it);
    Optimize.properties = property::make("properties",Compile.it);
    Optimize.functions = property::make("functions",2,Compile.it);
    Optimize.need_to_close = property::make("need_to_close",2,Compile.it);
    Optimize.need_modules = property::make("need_modules",2,Compile.it);
    Optimize.legal_modules = property::make("legal_modules",Compile.it);
    Optimize.allocation = property::make("allocation",Compile.it);
    Optimize.protection = property::make("protection",Compile.it);
    Optimize.alloc_stack = property::make("alloc_stack",2,Compile.it);
    Optimize.ignore = property::make("ignore",Compile.it);
    Optimize.to_remove = property::make("to_remove",Compile.it);
    Optimize.cinterface = property::make("cinterface",2,Compile.it);
    Optimize.outfile = property::make("outfile",2,Compile.it);
    Optimize.max_vars = property::make("max_vars",Compile.it);
    Optimize.loop_gc = property::make("loop_gc",Compile.it);
    Optimize.loop_index = property::make("loop_index",Compile.it);
    Optimize.level = property::make("level",2,Compile.it);
    Optimize.in_method = property::make("in_method",Compile.it);
    Optimize.profile_ask = property::make("profile?",2,Compile.it);
    Optimize.cfile = property::make("cfile",2,Compile.it);
    Optimize.use_update = property::make("use_update",Optimize.it);
    Optimize.use_nth_equal = property::make("use_nth=",Optimize.it);
    Optimize.online_ask = property::make("online?",Optimize.it);
    Optimize.recompute = property::make("recompute",Optimize.it);
    Optimize.unsure = property::make("unsure",Optimize.it);
    Optimize.knowns = property::make("knowns",Optimize.it);
    Optimize.headers = property::make("headers",2,claire.it);
    Optimize.debug_ask = property::make("debug?",claire.it);
    Optimize.active_ask = property::make("active?",2,claire.it);
    Optimize.safety = property::make("safety",claire.it);
    Optimize.env = property::make("env",2,claire.it);
    Optimize.naming = property::make("naming",claire.it);
    Optimize.libraries = property::make("libraries",2,claire.it);
    Optimize.loading_ask = property::make("loading?",2,claire.it);
    Optimize.class2file_ask = property::make("class2file?",claire.it);
    Optimize.greedy_ask = property::make("greedy?",2,claire.it);
    Optimize.libraries_dir = property::make("libraries_dir",2,claire.it);
    Optimize.headers_dir = property::make("headers_dir",2,claire.it);
    Optimize.options = property::make("options",2,claire.it);
    Optimize.ptype = property::make("ptype",Optimize.it);
    Optimize.c_code_call = property::make("c_code_call",Optimize.it);
    Optimize.c_register = property::make("c_register",Optimize.it);
    Optimize.c_gc_ask = property::make("c_gc?",Compile.it);
    Optimize.gcsafe_ask = property::make("gcsafe?",Optimize.it);
    Optimize.selector_psort = property::make("selector_psort",Optimize.it);
    Optimize.c_status = property::make("c_status",Optimize.it);
    Optimize.c_or = property::make("c_or",Optimize.it);
    Optimize.c_return = property::make("c_return",Optimize.it);
    Optimize.status_I = property::make("status!",Compile.it);
    Optimize.stable_ask = property::make("stable?",Optimize.it);
    Optimize.legal_ask = property::make("legal?",Optimize.it);
    Optimize.selector_register = property::make("selector_register",Optimize.it);
    Optimize.allocate_ask = property::make("allocate?",Optimize.it);
    Optimize.oload = property::make("oload",Optimize.it);
    Optimize.turbo = property::make("turbo",Optimize.it);
    Optimize.stats = property::make("stats",Optimize.it);
    
    // instructions from module sources 
    
    { global_variable * v60472 = (Optimize.srange = (global_variable *) Core._global_variable->instantiate("srange",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(Kernel.srange));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Language.typing = (global_variable *) Core._global_variable->instantiate("typing",iClaire.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(Kernel.typing));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Optimize.status = (global_variable *) Core._global_variable->instantiate("status",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(Kernel.status));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Optimize.tmatch_ask = (global_variable *) Core._global_variable->instantiate("tmatch?",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(Core.tmatch_ask));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Optimize.pname = (global_variable *) Core._global_variable->instantiate("pname",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(Core.pname));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Optimize.if_write = (global_variable *) Core._global_variable->instantiate("if_write",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(Kernel.if_write));
      close_global_variable(v60472);
      }
    
    GC_BIND;
Optimize.home->addMethod(list::domain(1,Kernel._void),Kernel._string,
    	NEW_ALLOC,_function_(home_void,"home_void"));
    
    { (Optimize._meta_OPT = ClaireClass::make("meta_OPT",Kernel._thing,Optimize.it));
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.instructions,instructions,Kernel._list,CNULL);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.objects,objects,Kernel._list,CNULL);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.properties,properties,nth_class2(Kernel._set,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,_oid_(Kernel._property))))),CNULL);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.functions,functions,Kernel._list,CNULL);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.need_to_close,need_to_close,Kernel._set,CNULL);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.need_modules,need_modules,Kernel._set,CNULL);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.legal_modules,legal_modules,Kernel._set,CNULL);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.allocation,allocation,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.protection,protection,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.alloc_stack,alloc_stack,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.ignore,ignore,Kernel._set,CNULL);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.to_remove,to_remove,Kernel._set,CNULL);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.cinterface,cinterface,Kernel._port,CNULL);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.outfile,outfile,Kernel._port,CNULL);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.max_vars,max_vars,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.loop_gc,loop_gc,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.loop_index,loop_index,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.level,level,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.in_method,in_method,Kernel._any,CNULL);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.profile_ask,profile_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.cfile,cfile,Kernel._any,Kernel.cfalse);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.use_update,use_update,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.use_nth_equal,use_nth_equal,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.online_ask,online_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.recompute,recompute,Kernel._boolean,Kernel.ctrue);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.unsure,unsure,Kernel._list,Core.nil->value);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.knowns,knowns,nth_class2(Kernel._set,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,_oid_(Kernel._relation))))),CNULL);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.simple_operations,simple_operations,nth_class2(Kernel._set,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,_oid_(Kernel._property))))),CNULL);
      CL_ADD_SLOT(Optimize._meta_OPT,Optimize_meta_OPT,Optimize.non_identifiable_set,non_identifiable_set,nth_class2(Kernel._set,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,_oid_(Kernel._class))))),CNULL);
      }
    
    { (Optimize._meta_compiler = ClaireClass::make("meta_compiler",Kernel._thing,Optimize.it));
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Kernel.external,external,Kernel._string,CNULL);
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Optimize.headers,headers,nth_class2(Kernel._list,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,_oid_(Kernel._string))))),CNULL);
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Kernel.source,source,Kernel._string,CNULL);
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Optimize.debug_ask,debug_ask,nth_class2(Kernel._list,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,_oid_(Kernel._module))))),CNULL);
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Kernel.version,version,Kernel._any,CNULL);
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Optimize.active_ask,active_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Optimize.safety,safety,Kernel._integer,((OID)1));
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Optimize.env,env,Kernel._string,_string_(((char*)"ntv")));
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Optimize.naming,naming,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Optimize.libraries,libraries,nth_class2(Kernel._list,list::alloc(Kernel._any,1,_oid_(Kernel.of)),list::alloc(1,_oid_(set::alloc(1,_oid_(Kernel._string))))),CNULL);
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Kernel.inline_ask,inline_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Optimize.loading_ask,loading_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Optimize.class2file_ask,class2file_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Optimize.greedy_ask,greedy_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Optimize.libraries_dir,libraries_dir,Kernel._list,CNULL);
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Optimize.headers_dir,headers_dir,Kernel._string,CNULL);
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Optimize.options,options,Kernel._list,CNULL);
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Optimize.overflow_ask,overflow_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Optimize.diet_ask,diet_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Optimize._meta_compiler,Optimize_meta_compiler,Optimize.optimize_ask,optimize_ask,Kernel._boolean,Kernel.cfalse);
      }
    
    GC_UNBIND;
{ global_variable * v60472 = (Optimize.claire_options = (global_variable *) Core._global_variable->instantiate("claire_options",claire.it));
      _void_(v60472->range = Kernel._string);
      _void_(v60472->value = _string_(((char*)"/w0 /zq")));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Optimize.claire_lib = (global_variable *) Core._global_variable->instantiate("claire_lib",claire.it));
      _void_(v60472->range = Kernel._string);
      _void_(v60472->value = _string_(((char*)"")));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Optimize.claire_modules = (global_variable *) Core._global_variable->instantiate("claire_modules",claire.it));
      _void_(v60472->range = Kernel._list);
      { global_variable * v21918 = v60472; 
        OID  v21919;
        { list * v20411;{ CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID v8240; CL_INT CLcount;
            v_list = list::alloc(4,_string_(((char*)"Kernel")),
              _string_(((char*)"Core")),
              _string_(((char*)"Language")),
              _string_(((char*)"Reader")));
             v20411 = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { v8240 = (*(v_list))[CLcount];
              v_val = value_string(string_v(v8240));
              
              (*((list *) v20411))[CLcount] = v_val;}
            }
          
          v21919=_oid_(v20411);}
        _void_(v21918->value = v21919);}
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Optimize.claire_prefix = (global_variable *) Core._global_variable->instantiate("claire_prefix",claire.it));
      _void_(v60472->range = Kernel._string);
      _void_(v60472->value = _string_(((char*)"NONE")));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Optimize.have_prefix_ask = (global_variable *) Core._global_variable->instantiate("have_prefix?",claire.it));
      _void_(v60472->range = Kernel._boolean);
      _void_(v60472->value = _oid_(((equal(Optimize.claire_prefix->value,_string_(((char*)"NONE"))) != CTRUE) ? ((string_v(Optimize.claire_prefix->value)[1 - 1] != ((unsigned char)'@')) ? CTRUE: CFALSE): CFALSE)));
      close_global_variable(v60472);
      }
    
    GC_BIND;
{ (Optimize.compiler = (Optimize_meta_compiler *) Optimize._meta_compiler->instantiate("compiler",claire.it));
      _void_(Optimize.compiler->external = ((char*)"g++"));
      _void_(Optimize.compiler->version = _float_(5.0));
      _void_(Optimize.compiler->source = ((char*)""));
      _void_(Optimize.compiler->headers_dir = ((char*)""));
      _void_(Optimize.compiler->libraries = list::alloc(Kernel._string,1,_string_(((char*)"Kernel"))));
      update_property(Optimize.options,
        Optimize.compiler,
        19,
        Kernel._object,
        _oid_(list::alloc(Kernel._any,3,_string_(((char*)"")),
          _string_(((char*)"")),
          _string_(((char*)"")))));
      _void_(Optimize.compiler->env = string_v(CLREAD(slot,_at_property1(Optimize.env,Optimize._meta_compiler),DEFAULT)));
      ;}
    
    { 
#ifndef CLPC
;
      _void_(Optimize.compiler->env = ((char*)"Darwin-i386-g++13.0.0"));
      
#endif
;
      }
    
    { (Optimize.c_type = property::make("c_type",3,claire.it,Kernel._any,0));
      _void_(Optimize.c_type->open = 3);
      _void_(Optimize.c_type->range = Kernel._type);
      ;}
    
    { (Optimize.c_code = property::make("c_code",3,claire.it,Kernel._any,0));
      _void_(Optimize.c_code->open = 3);
      ;}
    
    { (Optimize.c_gc = property::make("c_gc",3,claire.it,Kernel._any,0));
      _void_(Optimize.c_gc->open = 3);
      ;}
    
    { (Optimize.get_index = property::make("get_index",3,Compile.it,Kernel._any,0));
      _void_(Optimize.get_index->range = Kernel._integer);
      _void_(Optimize.get_index->open = 3);
      ;}
    
    { (Optimize.get_indexed = property::make("get_indexed",3,Compile.it,Kernel._any,0));
      _void_(Optimize.get_indexed->range = Kernel._bag);
      _void_(Optimize.get_indexed->open = 3);
      ;}
    
    { (Optimize.make_c_function = property::make("make_c_function",3,Compile.it,Kernel._any,0));
      _void_(Optimize.make_c_function->open = 3);
      ;}
    
    { (Optimize.make_float_function = property::make("make_float_function",3,Compile.it,Kernel._any,0));
      _void_(Optimize.make_float_function->open = 3);
      ;}
    
    { (Optimize.c_expression = property::make("c_expression",3,Compile.it,Kernel._any,0));
      _void_(Optimize.c_expression->open = 3);
      ;}
    
    { (Optimize.bool_exp = property::make("bool_exp",3,Compile.it,Kernel._any,0));
      _void_(Optimize.bool_exp->open = 3);
      ;}
    
    { (Optimize.c_statement = property::make("c_statement",2,Compile.it,Kernel._any,0));
      ;}
    
    { (Optimize.c_interface = property::make("c_interface",3,claire.it,Kernel._any,0));
      _void_(Optimize.c_interface->open = 3);
      ;}
    
    { (Optimize.c_sort = property::make("c_sort",3,Compile.it,Kernel._any,0));
      _void_(Optimize.c_sort->open = 3);
      ;}
    
    { (Optimize.designated_ask = property::make("designated?",1,Compile.it,Kernel._any,0));
      ;}
    
    { (Optimize.sort_equal = property::make("sort=",1,Compile.it,Kernel._any,0));
      ;}
    
    { (Optimize.psort = property::make("psort",1,Compile.it,Kernel._any,0));
      ;}
    
    { (Optimize.osort = property::make("osort",1,Compile.it,Kernel._any,0));
      ;}
    
    { (Optimize.compile_lambda = property::make("compile_lambda",1,Compile.it,Kernel._any,0));
      ;}
    
    { (Optimize.c_check = property::make("c_check",1,Compile.it,Kernel._any,0));
      ;}
    
    { (Optimize.need_protect = property::make("need_protect",1,Compile.it,Kernel._any,0));
      ;}
    
    { (Optimize.member_code = property::make("member_code",1,Optimize.it,Kernel._any,0));
      ;}
    
    { (Optimize.c_strict_code = property::make("c_strict_code",1,Compile.it,Kernel._any,0));
      ;}
    
    { (Optimize.c_strict_check = property::make("c_strict_check",3,Compile.it,Kernel._any,0));
      _void_(Optimize.c_strict_check->open = 3);
      ;}
    
    { (Optimize.stupid_t = property::make("stupid_t",1,Compile.it,Kernel._any,0));
      ;}
    
    { (Optimize.object_I = property::make("object!",1,Compile.it,Kernel._any,0));
      ;}
    
    { (Optimize.anyObject_I = property::make("anyObject!",2,Compile.it,Kernel._any,0));
      _void_(Optimize.anyObject_I->range = Kernel._object);
      ;}
    
    { (Optimize.Cerror = property::make("Cerror",1,Compile.it,Kernel._any,0));
      ;}
    
    { (Optimize.self_code = property::make("self_code",1,Compile.it,Kernel._any,0));
      ;}
    
    { (Optimize.get_module = property::make("get_module",1,Compile.it,Kernel._any,0));
      ;}
    
    { (Core.main = property::make("main",2,claire.it,Kernel._any,0));
      ;}
    
    { (Optimize._to_protect = ClaireClass::make("to_protect",Language._Optimized_instruction,Compile.it));
      CL_ADD_SLOT(Optimize._to_protect,Compile_to_protect,Kernel.arg,arg,Kernel._any,CNULL);
      }
    
    { (Optimize._to_CL = ClaireClass::make("to_CL",Language._Optimized_instruction,Compile.it));
      CL_ADD_SLOT(Optimize._to_CL,Compile_to_CL,Kernel.arg,arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Optimize._to_CL,Compile_to_CL,Language.set_arg,set_arg,Kernel._class,CNULL);
      }
    
    { (Optimize._to_C = ClaireClass::make("to_C",Language._Optimized_instruction,Compile.it));
      CL_ADD_SLOT(Optimize._to_C,Compile_to_C,Kernel.arg,arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Optimize._to_C,Compile_to_C,Language.set_arg,set_arg,Kernel._class,CNULL);
      }
    
    (Optimize._C_cast = ClaireClass::make("C_cast",Optimize._to_C,Compile.it));
    
    { (Optimize._Pattern = ClaireClass::make("Pattern",Core._Type,Optimize.it));
      CL_ADD_SLOT(Optimize._Pattern,Optimize_ClairePattern,Kernel.selector,selector,Kernel._property,CNULL);
      CL_ADD_SLOT(Optimize._Pattern,Optimize_ClairePattern,Kernel.arg,arg,Kernel._list,CNULL);
      }
    
    { (Optimize.OPT = (Optimize_meta_OPT *) Optimize._meta_OPT->instantiate("OPT",claire.it));
      _void_(Optimize.OPT->outfile = OBJECT(PortObject,Core.cl_stdin->value));
      _void_(Optimize.OPT->cinterface = OBJECT(PortObject,Core.cl_stdin->value));
      _void_(Optimize.OPT->ignore = set::alloc(9,_oid_(Core.index_I),
        _oid_(Kernel.set_index),
        _oid_(Optimize.object_I),
        _oid_(Core.base_I),
        _oid_(Core.set_base),
        _oid_(Core.push_I),
        _oid_(Optimize.anyObject_I),
        _oid_(Core.get_stack),
        _oid_(Core.put_stack)));
      _void_(Optimize.OPT->to_remove = set::alloc(1,_oid_(Language.ClaireInterface)));
      _void_(Optimize.OPT->knowns = set::alloc(Kernel._relation,2,_oid_(Core.arg1),_oid_(Core.arg2)));
      _void_(Optimize.OPT->unsure = list::alloc(3,_oid_(_at_property1(Core._plus,Kernel._integer)),
        _oid_(_at_property1(Kernel._star,Kernel._integer)),
        _oid_(_at_property1(Kernel._dash,Kernel._integer))));
      _void_(Optimize.OPT->simple_operations = set::alloc(Kernel.emptySet,4,_oid_(Kernel._dash),
        _oid_(Kernel._7),
        _oid_(Kernel._star),
        _oid_(Core._plus)));
      update_property(Optimize.non_identifiable_set,
        Optimize.OPT,
        31,
        Kernel._object,
        _oid_(set::alloc(Kernel._class,12,_oid_(Kernel._object),
          _oid_(Kernel._primitive),
          _oid_(Kernel._string),
          _oid_(Kernel._collection),
          _oid_(Kernel._bag),
          _oid_(Kernel._tuple),
          _oid_(Kernel._set),
          _oid_(Kernel._list),
          _oid_(Kernel._any),
          _oid_(Kernel._type),
          _oid_(Kernel._float),
          _oid_(Kernel._void))));
      _void_(Optimize.OPT->cfile = Kernel.cfalse);
      ;}
    
    _void_(Optimize.safe->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	RETURN_ARG,_function_(safe_any2,"safe_any2"))->typing = _oid_(_function_(safe_any2_type,"safe_any2_type")));
    
    Optimize.c_type->addMethod(list::domain(1,Kernel._any),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(c_type_any_Optimize,"c_type_any_Optimize"));
    
    Optimize.c_strict_code->addMethod(list::domain(2,Kernel._any,Kernel._class),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(c_strict_code_any,"c_strict_code_any"));
    
    Optimize.c_strict_check->addMethod(list::domain(2,Kernel._any,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_strict_check_any_Optimize,"c_strict_check_any_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(2,Kernel._any,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_any1_Optimize,"c_code_any1_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_any2_Optimize,"c_code_any2_Optimize"));
    
    Optimize.c_gc_ask->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	NEW_ALLOC,_function_(c_gc_ask_any,"c_gc?_any"));
    
    Optimize.c_sort->addMethod(list::domain(1,Kernel._any),Kernel._class,
    	NEW_ALLOC+RETURN_ARG,_function_(c_sort_any_Optimize,"c_sort_any_Optimize"));
    
    Optimize.selector_psort->addMethod(list::domain(1,Language._Call),Kernel._class,
    	RETURN_ARG,_function_(selector_psort_Call,"selector_psort_Call"));
    
    Optimize.c_status->addMethod(list::domain(2,Kernel._any,Kernel._list),Kernel._integer,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_status_any,"c_status_any"));
    
    Optimize.c_or->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._integer,
    	0,_function_(c_or_integer,"c_or_integer"));
    
    Optimize.c_or->addMethod(list::domain(1,Kernel._list),Kernel._integer,
    	0,_function_(c_or_list,"c_or_list"))->inlineDef("lambda[(l:list),let d := 0 in (for x in l d := c_or(d, x), d)]");
    
    Optimize.status_I->addMethod(list::domain(1,Kernel._restriction),Kernel._integer,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(status_I_restriction,"status!_restriction"));
    
    Optimize.c_return->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._integer,
    	0,_function_(c_return_integer,"c_return_integer"));
    
    Optimize.c_status->addMethod(list::domain(1,Kernel._property),Kernel._integer,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_status_property,"c_status_property"));
    
    { _void_(CLREAD(method,_at_property1(Core.vmatch_ask,Kernel._any),status) = 64);
      _void_(CLREAD(method,_at_property1(Core.matching_ask,Kernel._list),status) = 64);
      _void_(CLREAD(method,_at_property1(Core.eval_message,Kernel._property),status) = ((CL_INT)(*Language.bit_vector)(((OID)1),
        (OID)(3),
        (OID)(6))));
      _void_(CLREAD(method,_at_property1(Kernel.nth,Kernel._bag),status) = 16);
      _void_(CLREAD(method,_at_property1(Core.eval,Kernel._any),status) = 2);
      _void_(CLREAD(method,_at_property1(Core.self_eval,Language._Call),status) = 64);
      _void_(CLREAD(method,_at_property1(Core.self_eval,Language._If),status) = 64);
      _void_(CLREAD(method,_at_property1(Core.self_eval,Language._Do),status) = 64);
      }
    
    Optimize.showstatus->addMethod(list::domain(1,Kernel._method),Kernel._any,
    	NEW_ALLOC,_function_(showstatus_method2,"showstatus_method2"));
    
    Optimize.s_test->addMethod(list::domain(1,Kernel._method),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(s_test_method2,"s_test_method2"));
    
    Optimize.legal_ask->addMethod(list::domain(2,Kernel._module,Kernel._any),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(legal_ask_module,"legal?_module"));
    
    Optimize.legal_ask->addMethod(list::domain(2,Kernel._environment,Kernel._any),Kernel._any,
    	0,_function_(legal_ask_environment,"legal?_environment"));
    
    Optimize.c_register->addMethod(list::domain(1,GC_OBJECT(ClaireType,U_type(Kernel._thing,Kernel._class))),Kernel._any,
    	NEW_ALLOC,_function_(c_register_object,"c_register_object"));
    
    Optimize.c_register->addMethod(list::domain(1,Kernel._property),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE,_function_(c_register_property,"c_register_property"));
    
    Optimize.selector_register->addMethod(list::domain(1,Kernel._property),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT,_function_(selector_register_property,"selector_register_property"));
    
    Optimize.allocate_ask->addMethod(list::domain(1,Kernel._property),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(allocate_ask_property,"allocate?_property"));
    
    Optimize.stable_ask->addMethod(list::domain(1,Kernel._relation),Kernel._boolean,
    	NEW_ALLOC+SLOT_UPDATE,_function_(stable_ask_relation,"stable?_relation"));
    
    Optimize.get_module->addMethod(list::domain(1,GC_OBJECT(ClaireType,U_type(Kernel._thing,Kernel._class))),Kernel._any,
    	NEW_ALLOC,_function_(get_module_object,"get_module_object"));
    
    Reader.known_I->addMethod(list::domain(1,Kernel._listargs),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(known_I_listargs,"known!_listargs"));
    
    Optimize.oload->addMethod(list::domain(1,Kernel._module),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(oload_module,"oload_module"));
    
    Optimize.oload->addMethod(list::domain(1,Kernel._string),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(oload_string,"oload_string"));
    
    Optimize.turbo->addMethod(list::domain(1,Kernel._module),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(turbo_module,"turbo_module"));
    
    Optimize.stats->addMethod(list::domain(1,Optimize._meta_OPT),Kernel._void,
    	0,_function_(stats_meta_OPT,"stats_meta_OPT"));
    
    Kernel.self_print->addMethod(list::domain(1,Optimize._to_protect),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_to_protect,"self_print_to_protect"));
    
    Core.self_eval->addMethod(list::domain(1,Optimize._to_protect),Kernel._any,
    	NEW_ALLOC,_function_(self_eval_to_protect,"self_eval_to_protect"));
    
    Kernel.self_print->addMethod(list::domain(1,Optimize._to_CL),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_to_CL,"self_print_to_CL"));
    
    Optimize.c_type->addMethod(list::domain(1,Optimize._to_CL),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(c_type_to_CL_Optimize,"c_type_to_CL_Optimize"));
    
    Optimize.c_gc_ask->addMethod(list::domain(1,Optimize._to_CL),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_gc_ask_to_CL,"c_gc?_to_CL"));
    
    Kernel.self_print->addMethod(list::domain(1,Optimize._to_C),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_to_C,"self_print_to_C"));
    
    Optimize.c_gc_ask->addMethod(list::domain(1,Optimize._to_C),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_gc_ask_to_C,"c_gc?_to_C"));
    
    Optimize.c_type->addMethod(list::domain(1,Optimize._to_C),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_type_to_C_Optimize,"c_type_to_C_Optimize"));
    
    Kernel.self_print->addMethod(list::domain(1,Optimize._C_cast),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_C_cast,"self_print_C_cast"));
    
    Optimize.c_gc_ask->addMethod(list::domain(1,Optimize._C_cast),Kernel._boolean,
    	NEW_ALLOC,_function_(c_gc_ask_C_cast,"c_gc?_C_cast"));
    
    Optimize.c_type->addMethod(list::domain(1,Optimize._C_cast),Kernel._type,
    	RETURN_ARG,_function_(c_type_C_cast_Optimize,"c_type_C_cast_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(2,Optimize._C_cast,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_C_cast_Optimize,"c_code_C_cast_Optimize"));
    
    Kernel.self_print->addMethod(list::domain(1,Optimize._Pattern),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Pattern,"self_print_Pattern"));
    
    Kernel._Z->addMethod(list::domain(2,Kernel._any,Optimize._Pattern),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(_Z_any3,"%_any3"));
    
    Core.glb->addMethod(list::domain(2,Optimize._Pattern,Kernel._type),Kernel._type,
    	0,_function_(glb_Pattern,"glb_Pattern"));
    
    Core.less_ask->addMethod(list::domain(2,Optimize._Pattern,Kernel._any),Kernel._boolean,
    	NEW_ALLOC,_function_(less_ask_Pattern,"less?_Pattern"));
    
    Core.less_ask->addMethod(list::domain(2,Kernel._any,Optimize._Pattern),Kernel._boolean,
    	NEW_ALLOC,_function_(less_ask_any,"less?_any"));
    
    Kernel.nth->addMethod(list::domain(2,Kernel._property,Kernel._tuple),Optimize._Pattern,
    	NEW_ALLOC,_function_(nth_property,"nth_property"));
    
    (Optimize._optUnion = ClaireClass::make("optUnion",Core._Union,Optimize.it));
    
    GC_UNBIND;
{ global_variable * v60472 = (Optimize._staroportunist_method_star = (global_variable *) Core._global_variable->instantiate("*oportunist_method*",Optimize.it));
      _void_(v60472->range = Kernel._any);
      _void_(v60472->value = CNULL);
      close_global_variable(v60472);
      }
    
    GC_BIND;
Optimize.show_opportunist->addMethod(list::domain(1,Kernel._integer),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(show_opportunist_integer1,"show_opportunist_integer1"));
    
    Optimize.warn->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(warn_void,"warn_void"));
    
    Optimize.Cerror->addMethod(list::domain(2,Kernel._string,Kernel._listargs),Kernel.emptySet,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(Cerror_string,"Cerror_string"));
    
    Optimize.notice->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(notice_void,"notice_void"));
    
    Optimize.c_warn->addMethod(list::domain(2,Language._Call,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_warn_Call,"c_warn_Call"));
    
    Optimize.c_warn->addMethod(list::domain(2,Language._Super,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_warn_Super,"c_warn_Super"));
    
    Optimize.c_warn->addMethod(list::domain(3,Kernel._property,Kernel._list,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_warn_property,"c_warn_property"));
    
    Optimize.c_warn->addMethod(list::domain(3,Language._Variable,Kernel._any,Kernel._type),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_warn_Variable,"c_warn_Variable"));
    
    Optimize.sort_equal->addMethod(list::domain(2,Kernel._class,Kernel._class),Kernel._any,
    	0,_function_(sort_equal_class,"sort=_class"));
    
    Optimize.psort->addMethod(list::domain(1,Kernel._any),Kernel._class,
    	NEW_ALLOC+RETURN_ARG,_function_(psort_any,"psort_any"));
    
    Optimize.osort->addMethod(list::domain(1,Kernel._any),Kernel._class,
    	NEW_ALLOC+RETURN_ARG,_function_(osort_any,"osort_any"));
    
    Core.sort->addMethod(list::domain(1,Language._Variable),Kernel._class,
    	NEW_ALLOC+RETURN_ARG,_function_(sort_Variable,"sort_Variable"));
    
    Optimize.stupid_t->addMethod(list::domain(1,Kernel._any),Kernel._class,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(stupid_t_any1,"stupid_t_any1"));
    
    Optimize.stupid_t->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(stupid_t_any2,"stupid_t_any2"));
    
    Optimize.extended_ask->addMethod(list::domain(1,Kernel._type),Kernel._boolean,
    	0,_function_(extended_ask_type,"extended?_type"));
    
    Optimize.extends->addMethod(list::domain(1,Kernel._type),Kernel._type,
    	NEW_ALLOC,_function_(extends_type,"extends_type"));
    
    Optimize.sort_abstract_I->addMethod(list::domain(1,Kernel._type),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(sort_abstract_I_type,"sort_abstract!_type"));
    
    Optimize.sort_abstract_ask->addMethod(list::domain(1,Kernel._type),Kernel._boolean,
    	0,_function_(sort_abstract_ask_type,"sort_abstract?_type"));
    
    Optimize.ptype->addMethod(list::domain(1,Kernel._type),Kernel._type,
    	RETURN_ARG,_function_(ptype_type,"ptype_type"));
    
    Optimize.pmember->addMethod(list::domain(1,Kernel._type),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(pmember_type,"pmember_type"));
    
    Optimize.enumerate_code->addMethod(list::domain(2,Kernel._any,Kernel._type),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(enumerate_code_any,"enumerate_code_any"));
    
    Optimize.range_infers_for->addMethod(list::domain(3,Language._Variable,Kernel._type,Kernel._type),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(range_infers_for_Variable,"range_infers_for_Variable"));
    
    Optimize.range_infers->addMethod(list::domain(2,Language._Variable,Kernel._type),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(range_infers_Variable,"range_infers_Variable"));
    
    Optimize.range_infer_case->addMethod(list::domain(2,Kernel._any,Kernel._type),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(range_infer_case_any,"range_infer_case_any"));
    
    Optimize.c_check->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_check_any,"c_check_any"));
    
    Optimize.range_sets->addMethod(list::domain(2,Kernel._any,Kernel._type),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(range_sets_any,"range_sets_any"));
    
    Optimize.c_srange->addMethod(list::domain(1,Kernel._method),Kernel._class,
    	RETURN_ARG,_function_(c_srange_method,"c_srange_method"));
    
    Optimize.nativeVar_ask->addMethod(list::domain(1,Core._global_variable),Kernel._boolean,
    	0,_function_(nativeVar_ask_global_variable,"nativeVar?_global_variable"));
    
    Optimize.return_type->addMethod(list::domain(1,Kernel._any),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(return_type_any,"return_type_any"));
    
    Optimize.c_code->addMethod(list::domain(2,Core._Type,Kernel._class),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(c_code_Type_Optimize,"c_code_Type_Optimize"));
    
    Optimize.self_code->addMethod(list::domain(1,Core._subtype),Kernel._any,
    	NEW_ALLOC,_function_(self_code_subtype,"self_code_subtype"));
    
    Optimize.self_code->addMethod(list::domain(1,Core._Param),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_code_Param,"self_code_Param"));
    
    Optimize.self_code->addMethod(list::domain(1,Core._Union),Kernel._any,
    	NEW_ALLOC,_function_(self_code_Union,"self_code_Union"));
    
    Optimize.self_code->addMethod(list::domain(1,Core._Interval),Kernel._any,
    	NEW_ALLOC,_function_(self_code_Interval,"self_code_Interval"));
    
    Optimize.self_code->addMethod(list::domain(1,Core._Reference),Kernel._any,
    	NEW_ALLOC,_function_(self_code_Reference,"self_code_Reference"));
    
    Optimize.self_code->addMethod(list::domain(1,Optimize._Pattern),Kernel._any,
    	NEW_ALLOC,_function_(self_code_Pattern,"self_code_Pattern"));
    
    Optimize.member_code->addMethod(list::domain(2,Kernel._class,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(member_code_class2,"member_code_class2"));
    
    Optimize.member_code->addMethod(list::domain(2,Core._Type,Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(member_code_Type,"member_code_Type"));
    
    Optimize.member_code->addMethod(list::domain(2,Core._Union,Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(member_code_Union,"member_code_Union"));
    
    Optimize.member_code->addMethod(list::domain(2,Core._Interval,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(member_code_Interval,"member_code_Interval"));
    
    Optimize.member_code->addMethod(list::domain(2,Core._Param,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(member_code_Param,"member_code_Param"));
    
    Optimize.member_code->addMethod(list::domain(2,Kernel._tuple,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(member_code_tuple,"member_code_tuple"));
    
    Optimize.member_code->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(member_code_any,"member_code_any"));
    
    Kernel._Z->addMethod(list::domain(2,Kernel._any,GC_OBJECT(Optimize_ClairePattern,nth_property(Kernel._dot_dot,tuple::alloc(2,_oid_(Kernel._any),_oid_(Kernel._any))))),Kernel._boolean,
    	NEW_ALLOC,_function_(_Z_any4,"%_any4"))->inlineDef("lambda[(x:any,y:..[tuple(any,any)]),(x <= eval(y.args[2]) & eval(y.args[1]) <= x)]");
    
    Kernel._Z->addMethod(list::domain(2,Kernel._any,GC_OBJECT(Optimize_ClairePattern,nth_property(Core.but,tuple::alloc(2,_oid_(Kernel._any),_oid_(Kernel._any))))),Kernel._boolean,
    	NEW_ALLOC,_function_(_Z_any5,"%_any5"))->inlineDef("lambda[(x:any,y:but[tuple(any,any)]),(x % eval(y.args[1]) & x != eval(y.args[2]))]");
    
    Optimize.gcsafe_ask->addMethod(list::domain(1,Kernel._class),Kernel._boolean,
    	0,_function_(gcsafe_ask_class,"gcsafe?_class"));
    
    Optimize.gcsafe_ask->addMethod(list::domain(1,Kernel._type),Kernel._boolean,
    	NEW_ALLOC,_function_(gcsafe_ask_type,"gcsafe?_type"));
    
    Optimize.gcsafe_ask->addMethod(list::domain(1,Kernel._property),Kernel._boolean,
    	NEW_ALLOC,_function_(gcsafe_ask_property,"gcsafe?_property"));
    
    Optimize.c_gc_I->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_gc_I_any1,"c_gc!_any1"));
    
    Optimize.c_gc_I->addMethod(list::domain(2,Kernel._any,Kernel._type),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_gc_I_any2,"c_gc!_any2"));
    
    Optimize.need_protect->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	NEW_ALLOC+RETURN_ARG,_function_(need_protect_any,"need_protect_any"));
    
    Optimize.Variable_I->addMethod(list::domain(3,Kernel._symbol,Kernel._integer,Kernel._type),Language._Variable,
    	NEW_ALLOC,_function_(Variable_I_symbol,"Variable!_symbol"));
    
    Optimize.get_indexed->addMethod(list::domain(1,Kernel._class),Kernel._list,
    	RETURN_ARG,_function_(get_indexed_class_Optimize,"get_indexed_class_Optimize"));
    
    Optimize.designated_ask->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(designated_ask_any,"designated?_any"));
    
    Optimize.gc_register->addMethod(list::domain(1,Language._Variable),Kernel._any,
    	SLOT_UPDATE,_function_(gc_register_Variable,"gc_register_Variable"));
    
    Optimize.gc_register->addMethod(list::domain(2,Language._Variable,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(gc_register_Variable2,"gc_register_Variable2"));
    
    Optimize.inner2outer_ask->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(inner2outer_ask_any,"inner2outer?_any"));
    
    Optimize.identifiable_ask->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(identifiable_ask_any,"identifiable?_any"));
    
    Optimize.c_inline->addMethod(list::domain(3,Kernel._method,Kernel._list,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_inline_method1,"c_inline_method1"));
    
    Optimize.c_inline->addMethod(list::domain(2,Kernel._method,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_inline_method2,"c_inline_method2"));
    
    Optimize.c_inline_arg_ask->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_inline_arg_ask_any,"c_inline_arg?_any"));
    
    Optimize.c_substitution->addMethod(list::domain(4,Kernel._any,
      GC_OBJECT(ClaireType,nth_class1(Kernel._list,Language._Variable)),
      Kernel._list,
      Kernel._boolean),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_substitution_any,"c_substitution_any"));
    
    Core.eval->addMethod(list::domain(2,Kernel._any,Kernel._class),Kernel._any,
    	NEW_ALLOC,_function_(eval_any2,"eval_any2"));
    
    Optimize.bound_variables->addMethod(list::domain(1,Kernel._any),Kernel._list,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(bound_variables_any,"bound_variables_any"));
    
    Optimize.c_boolean->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_boolean_any,"c_boolean_any"));
    
    { (Optimize.ambiguous = (keyword *) Kernel._keyword->instantiate("ambiguous",Optimize.it));
      ;}
    
    Optimize.restriction_I->addMethod(list::domain(3,Kernel._property,Kernel._list,Kernel._boolean),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(restriction_I_property,"restriction!_property"));
    
    Optimize.restriction_I->addMethod(list::domain(3,Kernel._list,Kernel._list,Kernel._boolean),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(restriction_I_list,"restriction!_list"));
    
    Optimize.restriction_I->addMethod(list::domain(3,Kernel._class,Kernel._list,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(restriction_I_class,"restriction!_class"));
    
    Optimize.use_range->addMethod(list::domain(2,Kernel._method,Kernel._list),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(use_range_method,"use_range_method"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Call),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_type_Call2_Optimize,"c_type_Call2_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Call),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_Call_Optimize,"c_code_Call_Optimize"));
    
    Optimize.c_code_call->addMethod(list::domain(2,Language._Call,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_call_Call,"c_code_call_Call"));
    
    GC_UNBIND;
{ global_variable * v60472 = (Optimize._stardebug_local_file_star = (global_variable *) Core._global_variable->instantiate("*debug_local_file*",Optimize.it));
      _void_(v60472->range = Kernel._string);
      _void_(v60472->value = _string_(((char*)"")));
      close_global_variable(v60472);
      }
    
    GC_BIND;
Optimize.open_message->addMethod(list::domain(2,Kernel._property,Kernel._list),Language._Call,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(open_message_property,"open_message_property"));
    
    Optimize.c_gc_ask->addMethod(list::domain(1,Language._Call),Kernel._boolean,
    	NEW_ALLOC+SLOT_UPDATE,_function_(c_gc_ask_Call,"c_gc?_Call"));
    
    Optimize.daccess->addMethod(list::domain(2,Kernel._any,Kernel._boolean),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(daccess_any,"daccess_any"));
    
    Optimize.c_gc_ask->addMethod(list::domain(1,Language._Call_slot),Kernel._boolean,
    	NEW_ALLOC,_function_(c_gc_ask_Call_slot,"c_gc?_Call_slot"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Call_slot),Kernel._type,
    	RETURN_ARG,_function_(c_type_Call_slot_Optimize,"c_type_Call_slot_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Call_table),Kernel._type,
    	RETURN_ARG,_function_(c_type_Call_table_Optimize,"c_type_Call_table_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Call_array),Kernel._type,
    	RETURN_ARG,_function_(c_type_Call_array_Optimize,"c_type_Call_array_Optimize"));
    
    Optimize.c_code_write->addMethod(list::domain(1,Language._Call),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_write_Call,"c_code_write_Call"));
    
    Optimize.c_code_hold->addMethod(list::domain(4,Kernel._property,
      Kernel._any,
      Kernel._any,
      Kernel._boolean),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_hold_property,"c_code_hold_property"));
    
    Optimize.c_code_add->addMethod(list::domain(1,Language._Call),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_add_Call,"c_code_add_Call"));
    
    Optimize.c_code_add_bag->addMethod(list::domain(1,Language._Call),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_add_bag_Call,"c_code_add_bag_Call"));
    
    Optimize.c_code_delete->addMethod(list::domain(1,Language._Call),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_delete_Call,"c_code_delete_Call"));
    
    Optimize.c_code_not->addMethod(list::domain(1,Language._Select),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_not_Select,"c_code_not_Select"));
    
    Optimize.c_code_belong->addMethod(list::domain(1,Language._Call),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_belong_Call,"c_code_belong_Call"));
    
    Optimize.c_code_nth->addMethod(list::domain(1,Language._Call),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_nth_Call,"c_code_nth_Call"));
    
    Optimize.c_code_table->addMethod(list::domain(1,Language._Call),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_table_Call,"c_code_table_Call"));
    
    Optimize.c_code_array->addMethod(list::domain(1,Language._Call),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_array_Call,"c_code_array_Call"));
    
    Optimize.Update_ask->addMethod(list::domain(3,Kernel._relation,Kernel._any,Kernel._any),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(Update_ask_relation,"Update?_relation"));
    
    Optimize.Update_ask->addMethod(list::domain(2,Kernel._relation,Kernel._relation),Kernel._boolean,
    	0,_function_(Update_ask_relation2,"Update?_relation2"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Update),Kernel._type,
    	0,_function_(c_type_Update_Optimize,"c_type_Update_Optimize"));
    
    Optimize.c_code_method->addMethod(list::domain(3,Kernel._method,Kernel._list,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_method_method1,"c_code_method_method1"));
    
    Optimize.c_code_method->addMethod(list::domain(4,Kernel._method,
      Kernel._list,
      Kernel._list,
      Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_method_method2,"c_code_method_method2"));
    
    Optimize.Call_method_I->addMethod(list::domain(2,Kernel._method,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(Call_method_I_method,"Call_method!_method"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Call_method),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_type_Call_method_Optimize,"c_type_Call_method_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Call_method),Kernel._any,
    	RETURN_ARG,_function_(c_code_Call_method_Optimize,"c_code_Call_method_Optimize"));
    
    Optimize.c_gc_ask->addMethod(list::domain(1,Language._Call_method),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_gc_ask_Call_method,"c_gc?_Call_method"));
    
    { (Optimize.functional_I = property::make("functional!",3,Compile.it,Kernel._any,0));
      _void_(Optimize.functional_I->open = 3);
      ;}
    
    Optimize.functional_I->addMethod(list::domain(1,Kernel._method),Kernel._function,
    	NEW_ALLOC,_function_(functional_I_method_Optimize,"functional!_method_Optimize"));
    
    Optimize.nth_type_check->addMethod(list::domain(3,Kernel._type,Kernel._type,Kernel._type),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(nth_type_check_type,"nth_type_check_type"))->inlineDef("lambda[(tl:type,ti:type,tx:type),(if not(tx <= member(tl)) (Compile/warn(), trace(2, \"`BLUE unsafe update on bag: type ~S into ~S [252]\\n\", tx, tl)), tx)]");
    
    _void_(CLREAD(method,_at_property1(Kernel.nth_equal,Kernel._list),typing) = _oid_(Optimize.nth_type_check));
    
    Optimize.c_inline_ask->addMethod(list::domain(2,Kernel._method,Kernel._list),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_inline_ask_method,"c_inline?_method"));
    
    Optimize.inline_optimize_ask->addMethod(list::domain(1,Language._Call),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(inline_optimize_ask_Call,"inline_optimize?_Call"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Assign),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(c_type_Assign_Optimize,"c_type_Assign_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Assign),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_code_Assign_Optimize,"c_code_Assign_Optimize"));
    
    Optimize.c_gc_ask->addMethod(list::domain(1,Language._Assign),Kernel._boolean,
    	NEW_ALLOC,_function_(c_gc_ask_Assign,"c_gc?_Assign"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Gassign),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(c_type_Gassign_Optimize,"c_type_Gassign_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Gassign),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_code_Gassign_Optimize,"c_code_Gassign_Optimize"));
    
    Optimize.c_gc_ask->addMethod(list::domain(1,Language._Gassign),Kernel._boolean,
    	NEW_ALLOC,_function_(c_gc_ask_Gassign,"c_gc?_Gassign"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._And),Kernel._type,
    	0,_function_(c_type_And_Optimize,"c_type_And_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._And),Kernel._any,
    	NEW_ALLOC,_function_(c_code_And_Optimize,"c_code_And_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Or),Kernel._type,
    	0,_function_(c_type_Or_Optimize,"c_type_Or_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Or),Kernel._any,
    	NEW_ALLOC,_function_(c_code_Or_Optimize,"c_code_Or_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Quote),Kernel._type,
    	0,_function_(c_type_Quote_Optimize,"c_type_Quote_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Quote),Kernel.emptySet,
    	NEW_ALLOC,_function_(c_code_Quote_Optimize,"c_code_Quote_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Optimize._to_protect),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(c_type_to_protect_Optimize,"c_type_to_protect_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Optimize._to_protect),Kernel._any,
    	SAFE_RESULT,_function_(c_code_to_protect_Optimize,"c_code_to_protect_Optimize"));
    
    Optimize.c_gc_ask->addMethod(list::domain(1,Optimize._to_protect),Kernel._boolean,
    	0,_function_(c_gc_ask_to_protect,"c_gc?_to_protect"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Return),Kernel._type,
    	0,_function_(c_type_Return_Optimize,"c_type_Return_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Return),Kernel._any,
    	NEW_ALLOC,_function_(c_code_Return_Optimize,"c_code_Return_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Handle),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_type_Handle_Optimize,"c_type_Handle_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(2,Language._Handle,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_code_Handle_Optimize,"c_code_Handle_Optimize"));
    
    Optimize.c_gc_ask->addMethod(list::domain(1,Language._Handle),Kernel._boolean,
    	NEW_ALLOC,_function_(c_gc_ask_Handle,"c_gc?_Handle"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Cast),Kernel._type,
    	RETURN_ARG,_function_(c_type_Cast_Optimize,"c_type_Cast_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Cast),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_Cast2_Optimize,"c_code_Cast2_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Super),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_type_Super_Optimize,"c_type_Super_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Super),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_Super_Optimize,"c_code_Super_Optimize"));
    
    { (Optimize._Call_function2 = ClaireClass::make("Call_function2",Language._Optimized_instruction,Optimize.it));
      CL_ADD_SLOT(Optimize._Call_function2,Optimize_Call_function2,Kernel.arg,arg,Kernel._function,CNULL);
      CL_ADD_SLOT(Optimize._Call_function2,Optimize_Call_function2,Core.args,args,Kernel._list,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Optimize._Call_function2),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Call_function2,"self_print_Call_function2"));
    
    Optimize.c_type->addMethod(list::domain(1,Optimize._Call_function2),Kernel._type,
    	0,_function_(c_type_Call_function2_Optimize,"c_type_Call_function2_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Optimize._Call_function2),Kernel._any,
    	NEW_ALLOC,_function_(c_code_Call_function2_Optimize,"c_code_Call_function2_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Assert),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_Assert_Optimize,"c_code_Assert_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Trace),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_Trace_Optimize,"c_code_Trace_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Assert),Kernel._type,
    	0,_function_(c_type_Assert_Optimize,"c_type_Assert_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Trace),Kernel._type,
    	0,_function_(c_type_Trace_Optimize,"c_type_Trace_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Branch),Kernel._type,
    	0,_function_(c_type_Branch_Optimize,"c_type_Branch_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Branch),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_Branch_Optimize,"c_code_Branch_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(2,Language._Macro,Kernel._class),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(c_code_Macro_Optimize,"c_code_Macro_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Macro),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(c_type_Macro_Optimize,"c_type_Macro_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Printf),Kernel._type,
    	0,_function_(c_type_Printf_Optimize,"c_type_Printf_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Printf),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_Printf_Optimize,"c_code_Printf_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Error),Kernel._type,
    	0,_function_(c_type_Error_Optimize,"c_type_Error_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Error),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_code_Error_Optimize,"c_code_Error_Optimize"));
    
    Optimize.extendedTest_ask->addMethod(list::domain(1,Language._If),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(extendedTest_ask_If,"extendedTest?_If"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._If),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_type_If_Optimize,"c_type_If_Optimize"));
    
    GC_UNBIND;
{ global_variable * v60472 = (Optimize.PENIBLE = (global_variable *) Core._global_variable->instantiate("PENIBLE",claire.it));
      _void_(v60472->range = Kernel._boolean);
      _void_(v60472->value = Kernel.cfalse);
      close_global_variable(v60472);
      }
    
    GC_BIND;
Optimize.c_code->addMethod(list::domain(2,Language._If,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_code_If_Optimize,"c_code_If_Optimize"));
    
    Optimize.c_gc_ask->addMethod(list::domain(1,Language._If),Kernel._boolean,
    	NEW_ALLOC,_function_(c_gc_ask_If,"c_gc?_If"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Case),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_type_Case_Optimize,"c_type_Case_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(2,Language._Case,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_code_Case_Optimize,"c_code_Case_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Do),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(c_type_Do_Optimize,"c_type_Do_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(2,Language._Do,Kernel._class),Kernel._any,
    	NEW_ALLOC,_function_(c_code_Do_Optimize,"c_code_Do_Optimize"));
    
    Optimize.c_gc_ask->addMethod(list::domain(1,Language._Do),Kernel._boolean,
    	NEW_ALLOC,_function_(c_gc_ask_Do,"c_gc?_Do"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Let),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_type_Let_Optimize,"c_type_Let_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(2,Language._Let,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_Let_Optimize,"c_code_Let_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._When),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_type_When_Optimize,"c_type_When_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(2,Language._When,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_When_Optimize,"c_code_When_Optimize"));
    
    Optimize.c_gc_ask->addMethod(list::domain(1,Language._Let),Kernel._boolean,
    	NEW_ALLOC,_function_(c_gc_ask_Let,"c_gc?_Let"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._For),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_type_For_Optimize,"c_type_For_Optimize"));
    
    Optimize.infers_from->addMethod(list::domain(2,Kernel._type,Kernel._any),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(infers_from_type2,"infers_from_type2"));
    
    Optimize.c_code->addMethod(list::domain(2,Language._For,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_code_For_Optimize,"c_code_For_Optimize"));
    
    Optimize.c_code_multiple->addMethod(list::domain(3,Language._For,Kernel._type,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_multiple_For,"c_code_multiple_For"));
    
    Optimize.c_gc_ask->addMethod(list::domain(1,Language._Iteration),Kernel._boolean,
    	0,_function_(c_gc_ask_Iteration,"c_gc?_Iteration"));
    
    Optimize.c_gc_ask->addMethod(list::domain(1,Language._Ffor),Kernel._boolean,
    	0,_function_(c_gc_ask_Ffor1,"c_gc?_Ffor1"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Iteration),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_type_Iteration_Optimize,"c_type_Iteration_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Iteration),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_Iteration_Optimize,"c_code_Iteration_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Select),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_code_Select_Optimize,"c_code_Select_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Lselect),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_code_Lselect_Optimize,"c_code_Lselect_Optimize"));
    
    Optimize.c_code_select->addMethod(list::domain(2,Language._Iteration,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_code_select_Iteration,"c_code_select_Iteration"));
    
    Optimize.inner_select->addMethod(list::domain(4,Language._Iteration,
      Kernel._any,
      Kernel._any,
      Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(inner_select_Iteration,"inner_select_Iteration"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Exists),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_type_Exists_Optimize,"c_type_Exists_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(2,Language._Exists,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_Exists_Optimize,"c_code_Exists_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Image),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_type_Image_Optimize,"c_type_Image_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Select),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_type_Select_Optimize,"c_type_Select_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Lselect),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_type_Lselect_Optimize,"c_type_Lselect_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._While),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_type_While_Optimize,"c_type_While_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(2,Language._While,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_code_While_Optimize,"c_code_While_Optimize"));
    
    GC_UNBIND;
{ global_variable * v60472 = (Optimize.NO_FFOR_ask = (global_variable *) Core._global_variable->instantiate("NO_FFOR?",Optimize.it));
      _void_(v60472->range = Kernel._boolean);
      _void_(v60472->value = Kernel.cfalse);
      close_global_variable(v60472);
      }
    
    GC_BIND;
Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-noffor"))),GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	0,_function_(option_respond_string58_Optimize,"option_respond_string58_Optimize"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-noffor")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string38_Optimize,"option_usage_string38_Optimize"),
    _function_(option_usage_string38_Optimize_,"option_usage_string38_Optimize_"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Ffor),Kernel._any,
    	0,_function_(c_type_Ffor1_Optimize,"c_type_Ffor1_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(2,Language._Ffor,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_code_Ffor1_Optimize,"c_code_Ffor1_Optimize"));
    
    Optimize.Iterate_I->addMethod(list::domain(1,Language._Iteration),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(Iterate_I_Iteration,"Iterate!_Iteration"));
    
    Language.iterate->addMethod(list::domain(3,Core._Interval,GC_OBJECT(ClaireType,nth_class2(Language._Variable,GC_OBJECT(list,list::alloc(Kernel._any,1,_oid_(Kernel.range))),GC_OBJECT(list,list::alloc(Kernel.emptySet,1,GC_OID(_oid_(nth_class1(Kernel._type,Kernel._integer))))))),Kernel._any),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(iterate_Interval,"iterate_Interval"))->inlineDef("lambda[(x:Interval,v:Variable[range:(subtype[integer])],e:any),let v := eval(x.arg1, Interval),%max:integer := eval(x.arg2, Interval) in while (v <= %max) (e, v := v + 1)]");
    
    Language.iterate->addMethod(list::domain(3,Kernel._array,Language._Variable,Kernel._any),Kernel._any,
    	RETURN_ARG,_function_(iterate_array,"iterate_array"))->inlineDef("lambda[(x:array,v:Variable,e:any),let %i := 1,%a := x,%max := length(%a) in while (%i <= %max) let v := %a[%i] in (e, %i := %i + 1)]");
    
    Language.Iterate->addMethod(list::domain(3,Kernel._class,Language._Variable,Kernel._any),Kernel._any,
    	0,_function_(Iterate_class,"Iterate_class"))->inlineDef("lambda[(x:class,v:Variable,e:any),for %v_1 in x.descendents let %v_2 := (for v in %v_1.instances e) in (if %v_2 break(%v_2))]");
    
    Language.Iterate->addMethod(list::domain(3,GC_OBJECT(Optimize_ClairePattern,nth_property(Kernel._dot_dot,tuple::alloc(2,_oid_(Kernel._integer),_oid_(Kernel._integer)))),Language._Variable,Kernel._any),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(Iterate_any1,"Iterate_any1"))->inlineDef("lambda[(x:..[tuple(integer,integer)],v:Variable,e:any),let v := eval(x.args[1]),%max := eval(x.args[2]) in while (v <= %max) (e, v := v + 1)]");
    
    Language.Iterate->addMethod(list::domain(3,Language._Lselect,Language._Variable,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(Iterate_Lselect,"Iterate_Lselect"))->inlineDef("lambda[(x:Lselect,v:Variable,e:any),for v in eval(x.iClaire/set_arg) (if eval(substitution(x.arg, x.var, v)) e)]");
    
    Language.Iterate->addMethod(list::domain(3,Language._Select,Language._Variable,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(Iterate_Select,"Iterate_Select"))->inlineDef("lambda[(x:Select,v:Variable,e:any),for v in eval(x.iClaire/set_arg) (if eval(substitution(x.arg, x.var, v)) e)]");
    
    Language.Iterate->addMethod(list::domain(3,Language._Collect,Language._Variable,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(Iterate_Collect,"Iterate_Collect"))->inlineDef("lambda[(x:Collect,v:Variable,e:any),for C%v in eval(x.iClaire/set_arg) let v := eval(substitution(x.arg, x.var, C%v)) in e]");
    
    Language.Iterate->addMethod(list::domain(3,GC_OBJECT(Optimize_ClairePattern,nth_property(Core.but,tuple::alloc(2,_oid_(Kernel._any),_oid_(Kernel._any)))),Language._Variable,Kernel._any),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(Iterate_any2,"Iterate_any2"))->inlineDef("lambda[(x:but[tuple(any,any)],v:Variable,e:any),for v in eval(x.args[1]) (if (v != eval(x.args[2])) e)]");
    
    Language.Iterate->addMethod(list::domain(3,GC_OBJECT(Optimize_ClairePattern,nth_property(Kernel._7_plus,tuple::alloc(2,_oid_(Kernel._any),_oid_(Kernel._any)))),Language._Variable,Kernel._any),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(Iterate_any3,"Iterate_any3"))->inlineDef("lambda[(x:/+[tuple(any,any)],v:Variable,e:any),(for v in eval(x.args[1]) e, for v in eval(x.args[2]) e)]");
    
    Optimize.c_type->addMethod(list::domain(1,Language._List),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_type_List_Optimize,"c_type_List_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._List),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_List_Optimize,"c_code_List_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Set),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_type_Set_Optimize,"c_type_Set_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Set),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_Set_Optimize,"c_code_Set_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Tuple),Kernel._type,
    	NEW_ALLOC,_function_(c_type_Tuple_Optimize,"c_type_Tuple_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Tuple),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_code_Tuple_Optimize,"c_code_Tuple_Optimize"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Definition),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_type_Definition_Optimize,"c_type_Definition_Optimize"));
    
    GC_UNBIND;
{ global_variable * v60472 = (Optimize._starname_star = (global_variable *) Core._global_variable->instantiate("*name*",Compile.it));
      _void_(v60472->range = Kernel._symbol);
      _void_(v60472->value = _oid_(symbol_I_string2(((char*)"_CL_obj"))));
      close_global_variable(v60472);
      }
    
    GC_BIND;
Optimize.c_code->addMethod(list::domain(2,Language._Definition,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_Definition_Optimize,"c_code_Definition_Optimize"));
    
    Optimize.total_ask->addMethod(list::domain(2,Kernel._class,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(total_ask_class,"total?_class"));
    
    Optimize.analyze_I->addMethod(list::domain(4,Kernel._class,
      Kernel._any,
      Kernel._list,
      Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(analyze_I_class,"analyze!_class"));
    
    Optimize.c_code->addMethod(list::domain(2,Language._Defobj,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_code_Defobj_Optimize,"c_code_Defobj_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(2,Language._Defclass,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_Defclass_Optimize,"c_code_Defclass_Optimize"));
    
    GC_UNBIND;
{ global_variable * v60472 = (Optimize.SHIT = (global_variable *) Core._global_variable->instantiate("SHIT",claire.it));
      _void_(v60472->range = Kernel._any);
      _void_(v60472->value = ((OID)1));
      close_global_variable(v60472);
      }
    
    GC_BIND;
Optimize.c_type->addMethod(list::domain(1,Language._Defmethod),Kernel._type,
    	0,_function_(c_type_Defmethod_Optimize,"c_type_Defmethod_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Defmethod),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_Defmethod_Optimize,"c_code_Defmethod_Optimize"));
    
    Optimize.sort_pattern_ask->addMethod(list::domain(2,Kernel._list,Kernel._any),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(sort_pattern_ask_list,"sort_pattern?_list"));
    
    Optimize.sort_code->addMethod(list::domain(2,Language._Defmethod,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(sort_code_Defmethod,"sort_code_Defmethod"));
    
    Kernel.add_method->addMethod(list::domain(6,Kernel._property,
      Kernel._list,
      Kernel._type,
      Kernel._integer,
      Kernel._function,
      Kernel._function),Kernel._method,
    	0,_function_(add_method_property2,"add_method_property2"));
    
    Optimize.add_method_I->addMethod(list::domain(5,Kernel._method,
      Kernel._list,
      Kernel._any,
      Kernel._any,
      Kernel._function),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(add_method_I_method,"add_method!_method"));
    
    Optimize.extract_status_new->addMethod(list::domain(1,Kernel._any),Kernel._list,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(extract_status_new_any,"extract_status_new_any"));
    
    Optimize.extract_signature_I->addMethod(list::domain(1,Kernel._list),Kernel._list,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(extract_signature_I_list,"extract_signature!_list"));
    
    { (Optimize._equalsig_ask = (operation *) Kernel._operation->instantiate("=sig?",Optimize.it));
      ;}
    
    Optimize._equalsig_ask->addMethod(list::domain(2,Kernel._list,Kernel._list),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(_equalsig_ask_list,"=sig?_list"));
    
    { (Optimize.function_name = property::make("function_name",3,Optimize.it,Kernel._any,0));
      _void_(Optimize.function_name->open = 3);
      ;}
    
    Optimize.function_name->addMethod(list::domain(3,Kernel._property,Kernel._list,Kernel._any),Kernel._string,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(function_name_property_Optimize,"function_name_property_Optimize"));
    
    Optimize.compile_lambda->addMethod(list::domain(3,Kernel._string,Core._lambda,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(compile_lambda_string,"compile_lambda_string"));
    
    Optimize.c_code->addMethod(list::domain(1,Language._Defarray),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_Defarray_Optimize,"c_code_Defarray_Optimize"));
    
    Optimize.compute_if_write_inverse->addMethod(list::domain(1,Kernel._relation),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(compute_if_write_inverse_relation2,"compute_if_write_inverse_relation2"));
    
    Optimize.compute_set_write->addMethod(list::domain(1,Kernel._relation),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(compute_set_write_relation2,"compute_set_write_relation2"));
    
    Optimize.Produce_put->addMethod(list::domain(3,Kernel._property,Language._Variable,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(Produce_put_property2,"Produce_put_property2"));
    
    Optimize.Produce_erase->addMethod(list::domain(2,Kernel._property,Language._Variable),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(Produce_erase_property2,"Produce_erase_property2"));
    
    Optimize.Produce_put->addMethod(list::domain(3,Kernel._table,Language._Variable,Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(Produce_put_table2,"Produce_put_table2"));
    
    Optimize.Produce_get->addMethod(list::domain(2,Kernel._relation,Language._Variable),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(Produce_get_relation2,"Produce_get_relation2"));
    
    Optimize.Produce_remove->addMethod(list::domain(3,Kernel._property,Language._Variable,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(Produce_remove_property2,"Produce_remove_property2"));
    
    Optimize.Produce_remove->addMethod(list::domain(3,Kernel._table,Language._Variable,Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(Produce_remove_table2,"Produce_remove_table2"));
    
    Optimize.Tighten->addMethod(list::domain(1,Kernel._relation),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(Tighten_relation2,"Tighten_relation2"));
    
    Optimize.lexical_num->addMethod(list::domain(2,Kernel._any,Kernel._integer),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(lexical_num_any2,"lexical_num_any2"));
    
    Optimize.c_type->addMethod(list::domain(1,Language._Defrule),Kernel._type,
    	0,_function_(c_type_Defrule2_Optimize,"c_type_Defrule2_Optimize"));
    
    Optimize.c_code->addMethod(list::domain(2,Language._Defrule,Kernel._class),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_code_Defrule_Optimize,"c_code_Defrule_Optimize"));
    
    Optimize.compile_if_write->addMethod(list::domain(1,Kernel._relation),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(compile_if_write_relation,"compile_if_write_relation"));
    
    Optimize.compileEventMethod->addMethod(list::domain(1,Kernel._property),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(compileEventMethod_property,"compileEventMethod_property"));
    GC_UNBIND;

    }
  
  