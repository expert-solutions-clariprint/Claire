/***** CLAIRE Compilation of file ./compile/ocall.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:45 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>
#include <Optimize.h>
OID  restriction_I_property(property *v61776,list *v48360,ClaireBoolean *v23463)
{ { CL_INT  v48357 = 1;
    CL_INT  v1581 = v48360->length;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while (((CL_INT)v48357 <= (CL_INT)v1581))
      { ((*(v48360))[v48357]=_oid_(ptype_type(OBJECT(ClaireType,(*(v48360))[v48357]))));
        ++v48357;
        POP_SIGNAL;}
      }
    }
  POP_SIGNAL; return (restriction_I_list(v61776->definition,v48360,v23463));}

OID  restriction_I_list(list *v57482,list *v48360,ClaireBoolean *v23463)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
   mtformat_module1(Optimize.it,"call restriction!(~S,~S) \n",5,list::alloc(2,_oid_(v57482),_oid_(v48360)));
  else ;{ OID Result = 0;
    { ClaireBoolean * v35952 = ((class_I_type(OBJECT(ClaireType,(*(v48360))[1]))->open == 3) ? CTRUE : CFALSE);
      OID  v17945 = _oid_(Kernel.emptySet);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v48366);
        for (START(v57482); NEXT(v48366);)
        { GC_LOOP;
          if ((boolean_I_any(v17945) != CTRUE) && 
              (tmatch_ask_list(v48360,OBJECT(restriction,v48366)->domain) == CTRUE))
           { if (v23463 == CTRUE)
             GC__OID(v17945 = v48366, 1);
            else v17945= _oid_(OBJECT(restriction,v48366)->range);
              { ;ClEnv->cHandle = loop_handle; break;}
            }
          else if (length_bag(_exp_list(OBJECT(restriction,v48366)->domain,v48360)) != 0)
           { if (v23463 != CTRUE)
             { if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
               mtformat_module1(Optimize.it,"~S add ~S \n",5,list::alloc(2,v48366,_oid_(OBJECT(restriction,v48366)->range)));
              else ;GC__OID(v17945 = _oid_(U_type(OBJECT(ClaireType,v17945),OBJECT(restriction,v48366)->range)), 1);
              }
            else if (((CL_INT)Optimize.compiler->safety <= 3) || 
                ((equal(v17945,_oid_(Kernel.emptySet)) != CTRUE) || 
                  (v35952 == CTRUE)))
             { v17945= _oid_(Optimize.ambiguous);
              { ;ClEnv->cHandle = loop_handle; break;}
              }
            else GC__OID(v17945 = v48366, 1);
              }
          GC_UNLOOP; POP_SIGNAL;}
        }
      if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
       mtformat_module1(Optimize.it,"exit de restriction -> ~S \n",5,GC_OBJECT(list,list::alloc(1,v17945)));
      else ;Result = v17945;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  restriction_I_class(ClaireClass *v48351,list *v57482,list *v48360)
{ GC_BIND;
  if ((CL_INT)Optimize.compiler->safety > 3)
   ((*(v48360))[1]=GC_OID(_oid_(_exp_type(v48351,OBJECT(ClaireType,(*(v48360))[1])))));
  { OID Result = 0;
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v48366);
      Result= Kernel.cfalse;
      for (START(v57482); NEXT(v48366);)
      if (_inf_equalt_class(v48351,OBJECT(ClaireType,(*(OBJECT(restriction,v48366)->domain))[1])) == CTRUE)
       { if (tmatch_ask_list(v48360,OBJECT(restriction,v48366)->domain) == CTRUE)
         { Result = v48366;
          ClEnv->cHandle = loop_handle;break;}
        else if (length_bag(_exp_list(OBJECT(restriction,v48366)->domain,v48360)) != 0)
         { Result = _oid_(Optimize.ambiguous);
          ClEnv->cHandle = loop_handle;break;}
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * use_range_method(method *v61776,list *v55275)
{ GC_BIND;
  { ClaireType *Result ;
    if ((v61776->inline_ask == CTRUE) && 
        (v61776->typing == CNULL))
     { list * v57486 = GC_OBJECT(list,v61776->formula->vars);
      ClaireType * v55283 = Kernel._any;
      list * v9639;
      { { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v48370; CL_INT CLcount;
          v_list = v57486;
           v9639 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v48370 = (*(v_list))[CLcount];
            v_val = (*Kernel.range)(v48370);
            
            (*((list *) v9639))[CLcount] = v_val;}
          }
        GC_OBJECT(list,v9639);}
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v48370);
        for (START(v57486); NEXT(v48370);)
        put_property2(Kernel.range,OBJECT(ClaireObject,v48370),(*(v55275))[((CL_INT)((*Kernel.index)(v48370))+(CL_INT)1)]);
        }
      v55283= GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(GC_OID(v61776->formula->body))));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v48370);
        for (START(v57486); NEXT(v48370);)
        put_property2(Kernel.range,OBJECT(ClaireObject,v48370),(*(v9639))[((CL_INT)((*Kernel.index)(v48370))+(CL_INT)1)]);
        }
      if (INHERIT(v61776->range->isa,Kernel._type))
       v55283= GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel._exp)(_oid_(v55283),
        _oid_(v61776->range))));
      if (boolean_I_any(_oid_(v55283)) != CTRUE)
       (*Optimize.Cerror)(_string_("[207] inline ~S: range ~S is incompatible with ~S (inferred)"),
        _oid_(v61776),
        _oid_(v61776->range),
        GC_OID((*Optimize.c_type)(GC_OID(v61776->formula->body))));
      Result = v55283;
      }
    else { if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
         mtformat_module1(Optimize.it,"will try to use range type with ~S \n",5,list::alloc(1,_oid_(v55275)));
        else ;{ OID  v48354 = GC_OID(v61776->typing);
          list * v9639;
          { { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID v48369; CL_INT CLcount;
              v_list = v55275;
               v9639 = v_list->clone(Kernel._type);
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { v48369 = (*(v_list))[CLcount];
                v_val = _oid_(ptype_type(OBJECT(ClaireType,v48369)));
                
                (*((list *) v9639))[CLcount] = v_val;}
              }
            GC_OBJECT(list,v9639);}
          ClaireType * v9886 = v61776->range;
          ClaireType * v9887;
          { { ClaireObject *V_CC ;
              { if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
                 mtformat_module1(Optimize.it,"apply typing ~S --- ~S \n",5,list::alloc(2,_oid_(v55275),_oid_(v9639)));
                else ;{ ClaireHandler c_handle = ClaireHandler();
                  if ERROR_IN 
                  { if (INHERIT(OWNER(v48354),Core._lambda))
                     V_CC = OBJECT(ClaireType,apply_lambda(OBJECT(lambda,v48354),v9639));
                    else if (INHERIT(OWNER(v48354),Kernel._property))
                     V_CC = OBJECT(ClaireType,apply_property(OBJECT(property,v48354),v9639));
                    else if (INHERIT(OWNER(v48354),Kernel._function))
                     { OID v40982;{ list * v36836;
                        { list * v58163 = list::empty(Kernel.emptySet);
                          { CL_INT  v48362 = 1;
                            CL_INT  v1603 = ((CL_INT)v55275->length+(CL_INT)1);
                            { CL_INT loop_handle = ClEnv->cHandle;
                              OID gc_local;
                              while (((CL_INT)v48362 <= (CL_INT)v1603))
                              { v58163->addFast((OID)_oid_(Kernel._object));
                                ++v48362;
                                POP_SIGNAL;}
                              }
                            }
                          v36836 = GC_OBJECT(list,v58163);
                          }
                        v40982 = apply_function(OBJECT(ClaireFunction,v48354),v36836,v9639);
                        }
                      
                      V_CC=OBJECT(ClaireType,v40982);}
                    else V_CC = v9886;
                      ERROR_FREE;}
                  else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                  { c_handle.catchIt();{ if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
                       mtformat_module1(Optimize.it,"~S's 2nd-order type failed on ~S \n",0,GC_OBJECT(list,list::alloc(2,_oid_(v61776),_oid_(v55275))));
                      else ;V_CC = v9886;
                      }
                    }
                  else PREVIOUS_HANDLER;}
                }
              v9887= (ClaireType *) V_CC;}
            GC_OBJECT(ClaireType,v9887);}
          if ((boolean_I_any(sort_equal_class(osort_any(_oid_(v9886)),osort_any(_oid_(v9887)))) == CTRUE) || 
              (v61776->selector == Core.externC))
           Result = v9887;
          else if (boolean_I_any(sort_equal_class(Kernel._any,osort_any(_oid_(v9886)))) == CTRUE)
           { Union * v47292 = ((Union *) GC_OBJECT(Union,new_object_class(Core._Union)));
            (v47292->t1 = Kernel._any);
            (v47292->t2 = v9887);
            Result = v47292;
            }
          else Result = v9886;
            }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

Call * loc_I_Call1(Call *v61776)
{ GC_BIND;
  if (boolean_I_any(_oid_(v61776->location)) != CTRUE)
   update_property(Kernel.location,
    v61776,
    4,
    Kernel._object,
    GC_OID((*Kernel.location)(GC_OID(Optimize._starcall_star->value))));
  { Call *Result ;
    Result = v61776;
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * loc_I_Call1_type(ClaireType *v61776)
{ POP_SIGNAL; return (v61776);}

Call_method * loc_I_Call_method1(Call_method *v61776)
{ GC_BIND;
  if (boolean_I_any(_oid_(v61776->location)) != CTRUE)
   update_property(Kernel.location,
    v61776,
    4,
    Kernel._object,
    GC_OID((*Kernel.location)(GC_OID(Optimize._starcall_star->value))));
  { Call_method *Result ;
    Result = v61776;
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * loc_I_Call_method1_type(ClaireType *v61776)
{ POP_SIGNAL; return (v61776);}

Call_method1 * loc_I_Call_method11(Call_method1 *v61776)
{ GC_BIND;
  if (boolean_I_any(_oid_(v61776->location)) != CTRUE)
   update_property(Kernel.location,
    v61776,
    4,
    Kernel._object,
    GC_OID((*Kernel.location)(GC_OID(Optimize._starcall_star->value))));
  { Call_method1 *Result ;
    Result = v61776;
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * loc_I_Call_method11_type(ClaireType *v61776)
{ POP_SIGNAL; return (v61776);}

Call_method2 * loc_I_Call_method21(Call_method2 *v61776)
{ GC_BIND;
  if (boolean_I_any(_oid_(v61776->location)) != CTRUE)
   update_property(Kernel.location,
    v61776,
    4,
    Kernel._object,
    GC_OID((*Kernel.location)(GC_OID(Optimize._starcall_star->value))));
  { Call_method2 *Result ;
    Result = v61776;
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * loc_I_Call_method21_type(ClaireType *v61776)
{ POP_SIGNAL; return (v61776);}

ClaireType * c_type_Call2_Optimize(Call *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    { ClaireObject *V_CC ;
      if (v61776->selector == Language.function_I)
       V_CC = Kernel._function;
      else { property * v48367 = v61776->selector;
          list * v48360 = GC_OBJECT(list,v61776->args);
          list * v4955;
          { { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID v48372; CL_INT CLcount;
              v_list = v48360;
               v4955 = v_list->clone();
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { v48372 = (*(v_list))[CLcount];
                v_val = (*Optimize.c_type)(v48372);
                
                (*((list *) v4955))[CLcount] = v_val;}
              }
            GC_OBJECT(list,v4955);}
          if (v48367 == Optimize.safe)
           V_CC = OBJECT(ClaireType,(*(v4955))[1]);
          else if ((v48367 == Core.externC) && 
              ((v48360->length == 2) && 
                (INHERIT(OWNER((*(v48360))[2]),Kernel._class))))
           V_CC = OBJECT(ClaireClass,(*(v48360))[2]);
          else if ((v48367 == Core.NEW) && 
              (INHERIT(OWNER((*(v48360))[1]),Kernel._class)))
           V_CC = OBJECT(ClaireClass,(*(v48360))[1]);
          else if ((v48367 == Core.check_in) && 
              (INHERIT(OWNER((*(v48360))[2]),Kernel._type)))
           { V_CC = ((v48360->length == 2) ?
              sort_abstract_I_type(OBJECT(ClaireType,(*(v48360))[2])) :
              OBJECT(ClaireType,(*(v48360))[2]) );
            }
          else if ((v48367 == Kernel.nth) && 
              (_inf_equal_type(OBJECT(ClaireType,(*(v4955))[1]),Kernel._array) == CTRUE))
           { if (_inf_equal_type(GC_OBJECT(ClaireType,member_type(OBJECT(ClaireType,(*(v4955))[1]))),Kernel._float) == CTRUE)
             V_CC = Kernel._float;
            else V_CC = member_type(OBJECT(ClaireType,(*(v4955))[1]));
              }
          else if ((v48367 == Core._at) && 
              (INHERIT(OWNER((*(v48360))[1]),Kernel._property)))
           { property * v48364 = OBJECT(property,(*(v48360))[1]);
            OID  v48351 = (*(v48360))[2];
            if ((INHERIT(OWNER(v48351),Kernel._class)) && 
                (Kernel._method == owner_any((*Core._at)(_oid_(v48364),
                  v48351))))
             V_CC = set::alloc(1,GC_OID((*Core._at)(_oid_(v48364),
              v48351)));
            else V_CC = Kernel._any;
              }
          else if ((v48367 == Kernel.get) && 
              (INHERIT(OWNER((*(v48360))[1]),Kernel._relation)))
           { ClaireRelation * v48366 = OBJECT(ClaireRelation,(*(v48360))[1]);
            if (INHERIT(v48366->isa,Kernel._property))
             { ClaireObject * v57855 = GC_OBJECT(ClaireObject,_at_property1(((property *) v48366),class_I_type(OBJECT(ClaireType,(*(v4955))[2]))));
              if (Kernel._slot == v57855->isa)
               { if ((_inf_equal_type(CLREAD(restriction,v57855,range),Kernel._bag) == CTRUE) && 
                    ((CL_INT)Optimize.compiler->safety < 3))
                 V_CC = class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)((*(v48360))[2]))));
                else V_CC = ((belong_to(CLREAD(slot,v57855,DEFAULT),_oid_(CLREAD(restriction,v57855,range))) == CTRUE) ?
                  CLREAD(restriction,v57855,range) :
                  extends_type(CLREAD(restriction,v57855,range)) );
                }
              else V_CC = v48366->range;
                }
            else if (INHERIT(v48366->isa,Kernel._table))
             { V_CC = ((belong_to(CLREAD(table,v48366,DEFAULT),_oid_(v48366->range)) == CTRUE) ?
                v48366->range :
                extends_type(v48366->range) );
              }
            else V_CC = CFALSE;
              }
          else { OID  v48366 = GC_OID(restriction_I_property(v48367,v4955,CTRUE));
              if (Kernel._slot == OWNER(v48366))
               { if ((v48367 == Kernel.instances) && 
                    (INHERIT(OWNER((*(v48360))[1]),Kernel._class)))
                 { Param * v47292 = ((Param *) GC_OBJECT(Param,new_object_class(Core._Param)));
                  (v47292->arg = Kernel._list);
                  (v47292->params = list::alloc(1,_oid_(Kernel.of)));
                  (v47292->args = list::alloc(1,_oid_(set::alloc(1,(*(v48360))[1]))));
                  V_CC = v47292;
                  }
                else V_CC = OBJECT(restriction,v48366)->range;
                  }
              else if (Kernel._method == OWNER(v48366))
               V_CC = use_range_method(OBJECT(method,v48366),v4955);
              else if (boolean_I_any(_oid_(v48367->restrictions)) != CTRUE)
               V_CC = selector_psort_Call(v61776);
              else V_CC = (((v48367->open == 3) || 
                  (v48366 != _oid_(Optimize.ambiguous))) ?
                sort_abstract_I_type(v48367->range) :
                sort_abstract_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,restriction_I_property(v48367,v4955,CFALSE)))) );
              }
            }
        Result= (ClaireType *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Call_Optimize(Call *v61776)
{ POP_SIGNAL; return (c_code_call_Call(v61776,Kernel._void));}

OID  c_code_call_Call(Call *v61776,ClaireClass *v57706)
{ GC_BIND;
  if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
   mtformat_module1(Optimize.it,"c_code_call(~S)  \n",5,list::alloc(1,_oid_(v61776)));
  else ;{ OID Result = 0;
    { OID  v34702 = GC_OID(Optimize._starcall_star->value);
      OID  v17948;
      { { if (v61776->location->length != 0)
           (Optimize._starcall_star->value= _oid_(v61776));
          { property * v48367 = v61776->selector;
            list * v48360 = GC_OBJECT(list,v61776->args);
            if ((INHERIT(OWNER((*(v48360))[1]),Core._global_variable)) && 
                ((equal((*Kernel.range)((*(v48360))[1]),_oid_(Kernel.emptySet)) == CTRUE) && 
                  (designated_ask_any(GC_OID((*Kernel.value)((*(v48360))[1]))) == CTRUE)))
             ((*(v48360))[1]=GC_OID((*Kernel.value)((*(v48360))[1])));
            { OID  v48361 = GC_OID(inline_optimize_ask_Call(v61776));
              ClaireBoolean * v48350 = inherit_ask_class(OWNER((*(v48360))[1]),Kernel._property);
              OID  v48352 = GC_OID(daccess_any(_oid_(v61776),_sup_integer(Optimize.compiler->safety,5)));
              if ((v48350 == CTRUE) && 
                  (((v48367 == Kernel.put) || 
                      (v48367 == Core.write)) && 
                    (v48360->length == 3)))
               v17948 = c_code_write_Call(v61776);
              else if ((v48350 == CTRUE) && 
                  ((v48367 == Core.put_store) && 
                    ((v48360->length == 4) && 
                      ((*(v48360))[4] == Kernel.ctrue))))
               v17948 = c_code_write_Call(v61776);
              else if ((v48350 == CTRUE) && 
                  (v48367 == Core.unknown_ask))
               v17948 = c_code_hold_property(OBJECT(property,(*(v48360))[1]),(*(v48360))[2],CNULL,CTRUE);
              else if ((v48350 == CTRUE) && 
                  (v48367 == Core.known_ask))
               v17948 = c_code_hold_property(OBJECT(property,(*(v48360))[1]),(*(v48360))[2],CNULL,CFALSE);
              else if ((v48350 == CTRUE) && 
                  ((v48367 == Core.erase) && 
                    (INHERIT(OWNER((*(v48360))[2]),Language._Variable))))
               v17948 = (*Optimize.c_code)(GC_OID(Produce_erase_property2(OBJECT(property,(*(v48360))[1]),OBJECT(Variable,(*(v48360))[2]))),
                _oid_(v57706));
              else if (v48367 == Optimize.safe)
               { CL_INT  v48373 = Optimize.compiler->safety;
                ClaireBoolean * v48350 = Optimize.compiler->overflow_ask;
                OID  v48372 = CNULL;
                (Optimize.compiler->safety = 1);
                (Optimize.compiler->overflow_ask = CTRUE);
                { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Optimize.safe);
                    (v47292->args = list::alloc(1,GC_OID((*Optimize.c_code)((*(v48360))[1],
                      _oid_(v57706)))));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v48372 = _oid_(v47292);
                    }
                  GC_OID(v48372);}
                (Optimize.compiler->safety = v48373);
                (Optimize.compiler->overflow_ask = v48350);
                v17948 = v48372;
                }
              else if (((v48367 == Kernel.add) || 
                    (v48367 == Kernel.add_I)) && 
                  (v48350 == CTRUE))
               v17948 = c_code_add_Call(v61776);
              else if (((v48367 == Kernel.add) || 
                    (v48367 == Kernel.add_I)) && 
                  (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)((*(v48360))[1]))),Kernel._bag) == CTRUE))
               v17948 = c_code_add_bag_Call(v61776);
              else if ((v48350 == CTRUE) && 
                  (v48367 == Kernel._delete))
               v17948 = c_code_delete_Call(v61776);
              else if ((contain_ask_set(Optimize.OPT->to_remove,_oid_(v48367)) == CTRUE) || 
                  ((v48367 == Optimize.c_interface) && 
                      ((v48360->length == 2) && 
                        (contain_ask_set(GC_OBJECT(set,Optimize.OPT->legal_modules),GC_OID(get_module_object(v48367))) != CTRUE))))
               v17948 = Core.nil->value;
              else if (v48352 != CNULL)
               v17948 = v48352;
              else if (Kernel._method == OWNER(v48361))
               v17948 = c_inline_method1(OBJECT(method,v48361),v48360,c_srange_method(OBJECT(method,v48361)));
              else if (((v48367 == Kernel._equal) || 
                    (v48367 == Core._I_equal)) && 
                  (daccess_any((*(v48360))[1],CTRUE) != CNULL))
               v17948 = c_code_hold_property(OBJECT(property,(*(OBJECT(bag,(*Core.args)((*(v48360))[1]))))[1]),GC_OID((*(OBJECT(bag,(*Core.args)((*(v48360))[1]))))[2]),(*(v48360))[2],equal(_oid_(v48367),_oid_(Kernel._equal)));
              else if (((v48367 == Kernel._equal) || 
                    (v48367 == Core._I_equal)) && 
                  (daccess_any((*(v48360))[2],CTRUE) != CNULL))
               v17948 = c_code_hold_property(OBJECT(property,(*(OBJECT(bag,(*Core.args)((*(v48360))[2]))))[1]),GC_OID((*(OBJECT(bag,(*Core.args)((*(v48360))[2]))))[2]),(*(v48360))[1],equal(_oid_(v48367),_oid_(Kernel._equal)));
              else if (((v48367 == Kernel.nth_equal) || 
                    (v48367 == Kernel.put)) && 
                  ((INHERIT(OWNER((*(v48360))[1]),Kernel._table)) && 
                    (v48360->length == 3)))
               v17948 = c_code_table_Call(v61776);
              else if (((v48367 == Kernel.nth_put) || 
                    (v48367 == Kernel.nth_equal)) && 
                  ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)((*(v48360))[1]))),Kernel._array) == CTRUE) && 
                    (v48360->length == 3)))
               v17948 = c_code_array_Call(v61776);
              else if ((v48367 == Kernel.nth) || 
                  (((v48367 == Kernel.get) && 
                      (INHERIT(OWNER((*(v48360))[1]),Kernel._table))) || 
                    ((v48367 == Kernel.nth_get) && 
                        (Kernel._array == OWNER((*(v48360))[1])))))
               v17948 = c_code_nth_Call(v61776);
              else if (v48367 == Kernel._Z)
               v17948 = c_code_belong_Call(v61776);
              else if (v48367 == Core.Id)
               v17948 = (*Optimize.c_code)(GC_OID(OPT_EVAL((*(v48360))[1])));
              else if (v48367 == Language.function_I)
               v17948 = _oid_(make_function_string(string_I_symbol(extract_symbol_any((*(v48360))[1]))));
              else if ((v48367 == Core.NOT) && 
                  (INHERIT(OWNER((*(v48360))[1]),Language._Select)))
               v17948 = c_code_not_Select(OBJECT(Select,(*(v48360))[1]));
              else if ((v48367 == Core.call) && 
                  (INHERIT(OWNER((*(v48360))[1]),Kernel._property)))
               { OID  v37797;
                { { Call * v42713;{ Call * v39719;
                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        update_property(Kernel.selector,
                          v47292,
                          2,
                          Kernel._object,
                          (*(v48360))[1]);
                        (v47292->args = cdr_list(v48360));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                        v39719 = v47292;
                        }
                      v42713 = loc_I_Call1(v39719);
                      }
                    
                    v37797=_oid_(v42713);}
                  GC_OID(v37797);}
                v17948 = (*Optimize.c_code)(v37797);
                }
              else if (v48367->open == 3)
               { list * v40680;
                { { CL_INT loop_handle = ClEnv->cHandle;
                    bag *v_list; OID v_val;
                    OID v48372; CL_INT CLcount;
                    v_list = v48360;
                     v40680 = v_list->clone();
                    for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                    { v48372 = (*(v_list))[CLcount];
                      v_val = (*Optimize.c_type)(v48372);
                      
                      (*((list *) v40680))[CLcount] = v_val;}
                    }
                  GC_OBJECT(list,v40680);}
                v17948 = c_warn_property(v48367,v48360,v40680);
                }
              else { ClaireBoolean * g0996I;
                { ClaireBoolean *v_and;
                  { v_and = ((v48367 == Language.bit_vector) ? CTRUE : CFALSE);
                    if (v_and == CFALSE) g0996I =CFALSE; 
                    else { { OID  v42602;
                        { CL_INT loop_handle = ClEnv->cHandle;
                          OID gc_local;
                          ITERATE(v48373);
                          v42602= Kernel.cfalse;
                          bag *v48373_support;
                          v48373_support = GC_OBJECT(list,v61776->args);
                          for (START(v48373_support); NEXT(v48373);)
                          if (inherit_ask_class(OWNER(v48373),Kernel._integer) != CTRUE)
                           { v42602 = Kernel.ctrue;
                            ClEnv->cHandle = loop_handle;break;}
                          }
                        v_and = not_any(v42602);
                        }
                      if (v_and == CFALSE) g0996I =CFALSE; 
                      else g0996I = CTRUE;}
                    }
                  }
                
                if (g0996I == CTRUE) v17948 = OPT_EVAL(_oid_(v61776));
                  else if ((v48367 == Optimize.anyObject_I) || 
                    ((v48367 == Optimize.object_I) || 
                      ((v48367 == Kernel.add_method) && 
                          (v48350 == CTRUE))))
                 v17948 = _oid_(v61776);
                else { list * v4955;
                    { { CL_INT loop_handle = ClEnv->cHandle;
                        bag *v_list; OID v_val;
                        OID v48372; CL_INT CLcount;
                        v_list = v48360;
                         v4955 = v_list->clone();
                        for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                        { v48372 = (*(v_list))[CLcount];
                          v_val = (*Optimize.c_type)(v48372);
                          
                          (*((list *) v4955))[CLcount] = v_val;}
                        }
                      GC_OBJECT(list,v4955);}
                    OID  v48374 = GC_OID(restriction_I_property(v48367,v4955,CTRUE));
                    if (Kernel._slot == OWNER(v48374))
                     { ClaireBoolean * v43145 = ((belong_to(OBJECT(slot,v48374)->DEFAULT,_oid_(OBJECT(restriction,v48374)->range)) != CTRUE) ? ((contain_ask_set(Optimize.OPT->knowns,_oid_(v48367)) != CTRUE) ? (((CL_INT)Optimize.compiler->safety < 5) ? CTRUE: CFALSE): CFALSE): CFALSE);
                      if ((v43145 != CTRUE) || 
                          (designated_ask_any((*(v48360))[1]) == CTRUE))
                       { Call_slot * v47292 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
                        (v47292->selector = OBJECT(slot,v48374));
                        (v47292->arg = (*Optimize.c_code)((*(v48360))[1],
                          _oid_(psort_any(_oid_(domain_I_restriction(OBJECT(restriction,v48374)))))));
                        (v47292->test = v43145);
                        add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v47292));
                        v17948 = _oid_(v47292);
                        }
                      else { if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
                           mtformat_module1(Optimize.it,"`GREEN ---- note: ... unsafe access to unknown slot: ~S \n",3,GC_OBJECT(list,list::alloc(1,_oid_(v61776))));
                          else ;if (Optimize.compiler->optimize_ask == CTRUE)
                           { notice_void();
                            if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
                             mtformat_module1(Optimize.it,"`GREEN poorly optimized slot access: ~S\n",3,GC_OBJECT(list,list::alloc(1,_oid_(v61776))));
                            else ;}
                          v17948 = c_warn_property(v48367,v48360,v4955);
                          }
                        }
                    else if (Kernel._method == OWNER(v48374))
                     { if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
                       mtformat_module1(Optimize.it,"found a method \n",5,GC_OBJECT(list,list::empty()));
                      else ;if (v48367 == Kernel.nth_equal)
                       (Optimize.OPT->use_nth_equal = CTRUE);
                      if (v4955->memq(_oid_(Kernel._void)) == CTRUE)
                       (*Optimize.Cerror)(_string_("[205] call ~S uses a void argument [~S]"),
                        _oid_(v61776),
                        _oid_(v4955));
                      if (((v48367 == Kernel.begin) || 
                            (v48367 == Kernel.end)) && 
                          (INHERIT(OWNER((*(v48360))[1]),Kernel._module)))
                       OPT_EVAL(_oid_(v61776));
                      if ((last_list(OBJECT(restriction,v48374)->domain) == _oid_(Kernel._listargs)) || 
                          (((*(OBJECT(restriction,v48374)->domain))[1] == _oid_(Kernel._void)) && 
                              ((*(v48360))[1] != _oid_(ClEnv))))
                       v17948 = _oid_(open_message_property(v48367,v48360));
                      else v17948 = c_code_method_method2(OBJECT(method,v48374),v48360,v4955,v57706);
                        }
                    else if (INHERIT(OWNER(v48374),Kernel._keyword))
                     v17948 = c_warn_property(v48367,v48360,v4955);
                    else v17948 = c_warn_Call(v61776,_oid_(v4955));
                      }
                  }
              }
            }
          }
        GC_OID(v17948);}
      (Optimize._starcall_star->value= v34702);
      Result = v17948;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

Call * open_message_property(property *v61776,list *v48360)
{ GC_BIND;
  selector_register_property(v61776);
  { Call *Result ;
    { list * v28181;
      { { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v48372; CL_INT CLcount;
          v_list = v48360;
           v28181 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v48372 = (*(v_list))[CLcount];
            if ((*Optimize.c_type)(v48372) != _oid_(Kernel._void))
             v_val = (*Optimize.c_code)(v48372,
              _oid_(Kernel._any));
            else v_val = (*Optimize.Cerror)(_string_("[206] use of void ~S in ~S(~A)"),
                v48372,
                _oid_(v61776),
                _oid_(v48360));
              
            (*((list *) v28181))[CLcount] = v_val;}
          }
        GC_OBJECT(list,v28181);}
      if (Optimize.OPT->allocation == CTRUE)
       { { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v48372; CL_INT CLcount;
          v_list = v28181;
           v28181 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v48372 = (*(v_list))[CLcount];
            v_val = c_gc_I_any1(v48372);
            
            (*((list *) v28181))[CLcount] = v_val;}
          }
        GC_OBJECT(list,v28181);}
      { ClaireBoolean * g0998I;
        { ClaireBoolean *v_and;
          { v_and = Optimize.compiler->diet_ask;
            if (v_and == CFALSE) g0998I =CFALSE; 
            else { { OID  v44524;
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(v48372);
                  v44524= Kernel.cfalse;
                  for (START(v48360); NEXT(v48372);)
                  if ((INHERIT(OWNER(v48372),Kernel._class)) || 
                      (INHERIT(OWNER(v48372),Kernel._property)))
                   { v44524 = Kernel.ctrue;
                    ClEnv->cHandle = loop_handle;break;}
                  }
                v_and = boolean_I_any(v44524);
                }
              if (v_and == CFALSE) g0998I =CFALSE; 
              else g0998I = CTRUE;}
            }
          }
        
        if (g0998I == CTRUE) { warn_void();
            if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
             mtformat_module1(Optimize.it,"`BLUE Non diet call ~S(~A) [254]\n",2,list::alloc(2,_oid_(v61776),_oid_(v48360)));
            else ;}
          }
      { Call * v31202;
        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          (v47292->selector = v61776);
          (v47292->args = v28181);
          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
          v31202 = v47292;
          }
        Result = loc_I_Call1(v31202);
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * c_gc_ask_Call(Call *v61776)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = ((v61776->selector == Language.function_I) ? CTRUE : (((v61776->selector == Optimize.safe) ? ((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)((*(v61776->args))[1]))) == CTRUE) : (((stable_ask_relation(v61776->selector) == CTRUE) ? (((OBJECT(ClaireBoolean,_oid_((INHERIT(v61776->selector->range->isa,Kernel._class) ?
     (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v61776->selector->range))) : 
     (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(v61776->selector->range))))))) == CTRUE) ? CTRUE: CFALSE): CFALSE) != CTRUE)) ? CTRUE : CFALSE));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  daccess_any(OID v61776,ClaireBoolean *v48350)
{ GC_BIND;
  { OID Result = 0;
    if (INHERIT(OWNER(v61776),Language._Call))
     { list * v48360 = GC_OBJECT(list,OBJECT(Call,v61776)->args);
      ClaireObject * v57855;
      { if ((OBJECT(Call,v61776)->selector == Kernel.get) && 
            (INHERIT(OWNER((*(v48360))[1]),Kernel._property)))
         v57855 = _at_property1(OBJECT(property,(*(v48360))[1]),class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)((*(v48360))[2])))));
        else v57855 = CFALSE;
          GC_OBJECT(ClaireObject,v57855);}
      if ((Kernel._slot == v57855->isa) && ((v48350 == CTRUE) || 
          ((belong_to(CLREAD(slot,v57855,DEFAULT),_oid_(CLREAD(restriction,v57855,range))) == CTRUE) || 
            ((CLREAD(slot,v57855,srange) == Kernel._any) || 
              (CLREAD(slot,v57855,srange) == Kernel._integer)))))
       { Call_slot * v47292 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
        (v47292->selector = ((slot *) v57855));
        (v47292->arg = (*Optimize.c_code)((*(v48360))[2],
          _oid_(psort_any(_oid_(domain_I_restriction(((restriction *) v57855)))))));
        (v47292->test = CFALSE);
        add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      else Result = CNULL;
        }
    else Result = CNULL;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * c_gc_ask_Call_slot(Call_slot *v61776)
{ GC_BIND;
  { ClaireBoolean *Result ;
    { slot * v48367 = v61776->selector;
      OID  v48372 = v61776->arg;
      Result = ((_oid_((INHERIT(v48367->range->isa,Kernel._class) ?
       (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v48367->range))) : 
       (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(v48367->range))))) != Kernel.ctrue) ? ((v48367->range != Kernel._float) ? (((1 <= (CL_INT)v48367->selector->open) || 
          (gcsafe_ask_class(domain_I_restriction(v48367)) != CTRUE)) ? CTRUE: CFALSE): CFALSE): CFALSE);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Call_slot_Optimize(Call_slot *v61776)
{ POP_SIGNAL; return (v61776->selector->range);}

ClaireType * c_type_Call_table_Optimize(Call_table *v61776)
{ POP_SIGNAL; return (v61776->selector->range);}

ClaireType * c_type_Call_array_Optimize(Call_array *v61776)
{ POP_SIGNAL; return (OBJECT(ClaireType,v61776->test));}

OID  c_code_write_Call(Call *v61776)
{ GC_BIND;
  loc_I_Call1(v61776);
  { OID Result = 0;
    { OID  v48364 = GC_OID((*(v61776->args))[1]);
      OID  v48372 = GC_OID((*(v61776->args))[2]);
      OID  v48373 = GC_OID((*(v61776->args))[3]);
      OID  v57887 = GC_OID((*Optimize.c_type)(v48373));
      property * v57700 = v61776->selector;
      OID  v48367 = GC_OID((*Optimize.restriction_I)(v48364,
        _oid_(list::alloc(1,GC_OID((*Optimize.c_type)(v48372)))),
        Kernel.ctrue));
      if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
       mtformat_module1(Optimize.it,"c_code_write(~S) \n",5,list::alloc(1,_oid_(v61776)));
      else ;(Optimize.OPT->use_update = CTRUE);
      if (contain_ask_set(Optimize.OPT->to_remove,v48364) == CTRUE)
       Result = Core.nil->value;
      else if ((Kernel._slot == OWNER(v48367)) && ((_inf_equal_type(OBJECT(ClaireType,v57887),OBJECT(restriction,v48367)->range) == CTRUE) || 
          (4 <= (CL_INT)Optimize.compiler->safety)))
       { if ((v48373 != CNULL) && 
            (boolean_I_any((*Kernel._exp)(v57887,
              GC_OID((*Kernel.srange)(v48367)))) != CTRUE))
         { if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
           mtformat_module1(Optimize.it,"====> ~S ^ ~S = ~S \n",5,list::alloc(3,v57887,
            GC_OID((*Kernel.srange)(v48367)),
            GC_OID((*Kernel._exp)(v57887,
              GC_OID((*Kernel.srange)(v48367))))));
          else ;warn_void();
          if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
           mtformat_module1(Optimize.it,"`BLUE sort error in ~S: ~S is a ~S [253]\n",2,list::alloc(3,_oid_(v61776),
            v48373,
            v57887));
          else ;}
        if (((_inf_equal_type(OBJECT(ClaireType,v57887),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(v48367)))) == CTRUE) || 
              ((_inf_equal_type(OBJECT(ClaireType,v57887),Kernel._object) == CTRUE) || 
                (((*Kernel.srange)(v48367) != _oid_(Kernel._object)) || 
                  (v48373 == CNULL)))) && 
            ((v57700 != Core.write) || 
                ((Update_ask_relation(OBJECT(ClaireRelation,v48364),v48372,v48373) == CTRUE) && 
                    ((OBJECT(ClaireRelation,v48364)->multivalued_ask == CFALSE) || 
                        (get_property(Kernel.if_write,OBJECT(ClaireObject,v48364)) == CNULL)))))
         { OID  v55287 = GC_OID((*Optimize.c_code)(v48372,
            _oid_(psort_any(_oid_(domain_I_restriction(OBJECT(restriction,v48367)))))));
          OID  v55288 = GC_OID(c_strict_code_any(v48373,psort_any(GC_OID((*Kernel.range)(v48367)))));
          Update * v47292 = ((Update *) GC_OBJECT(Update,new_object_class(Language._Update)));
          (v47292->selector = v48364);
          (v47292->value = v55288);
          { Update * v22467 = v47292; 
            OID  v22468;
            if (v57700 != Core.write)
             v22468 = _oid_(v57700);
            else v22468 = (*Optimize.c_code)(v48372,
                _oid_(Kernel._any));
              (v22467->arg = v22468);}
          { Update * v22469 = v47292; 
            OID  v22470;
            { Call_slot * v47292 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
              update_property(Kernel.selector,
                v47292,
                2,
                Kernel._object,
                v48367);
              (v47292->arg = v55287);
              (v47292->test = CFALSE);
              add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v47292));
              v22470 = _oid_(v47292);
              }
            (v22469->var = v22470);}
          add_I_property(Kernel.instances,Language._Update,11,_oid_(v47292));
          Result = _oid_(v47292);
          }
        else if (v57700 == Kernel.put)
         { OID  v36007;
          { { Call * v63579;{ Call * v37929;
                { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  (v47292->selector = Kernel.store);
                  (v47292->args = list::alloc(5,v48372,
                    (*Kernel.index)(v48367),
                    GC_OID((*Kernel.srange)(v48367)),
                    v48373,
                    GC_OID((*Kernel.store_ask)(v48364))));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                  v37929 = v47292;
                  }
                v63579 = loc_I_Call1(v37929);
                }
              
              v36007=_oid_(v63579);}
            GC_OID(v36007);}
          Result = (*Optimize.c_code)(v36007);
          }
        else { if (Optimize.compiler->diet_ask == CTRUE)
             { warn_void();
              if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
               mtformat_module1(Optimize.it,"`BLUE ~S is not a diet call [254]",2,list::alloc(1,_oid_(v61776)));
              else ;}
            if ((Optimize.compiler->optimize_ask == CTRUE) && 
                (v48364 != _oid_(Kernel.instances)))
             { notice_void();
              if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
               mtformat_module1(Optimize.it,"`GREEN poorly typed update: ~S\n",3,list::alloc(1,_oid_(v61776)));
              else ;}
            { OID  v38890;
              { { Call * v63582;{ Call * v60993;
                    { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      (v47292->selector = Core.update);
                      (v47292->args = list::alloc(5,v48364,
                        v48372,
                        (*Kernel.index)(v48367),
                        GC_OID((*Kernel.srange)(v48367)),
                        v48373));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                      v60993 = v47292;
                      }
                    v63582 = loc_I_Call1(v60993);
                    }
                  
                  v38890=_oid_(v63582);}
                GC_OID(v38890);}
              Result = (*Optimize.c_code)(v38890);
              }
            }
          }
      else { list * v4955;
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
          OID  v48374 = GC_OID(restriction_I_property(v57700,v4955,CTRUE));
          if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
           mtformat_module1(Optimize.it,"`GREEN ---- note: ~S is poorly typed (~S,~S) \n",3,list::alloc(3,_oid_(v61776),
            GC_OID((*Optimize.c_type)(v48372)),
            v57887));
          else ;if (Kernel._method == OWNER(v48374))
           Result = c_code_method_method1(OBJECT(method,v48374),GC_OBJECT(list,v61776->args),v4955);
          else Result = c_warn_Call(v61776,_oid_(v4955));
            }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_hold_property(property *v48364,OID v48372,OID v48373,ClaireBoolean *v48350)
{ GC_BIND;
  { OID Result = 0;
    { OID  v48367 = GC_OID(restriction_I_property(v48364,list::alloc(1,GC_OID((*Optimize.c_type)(v48372))),CTRUE));
      if ((Kernel._slot == OWNER(v48367)) && ((v48373 == CNULL) || 
          ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v48373))),OBJECT(slot,v48367)->srange) == CTRUE) && 
              (identifiable_ask_any(v48373) == CTRUE))))
       { Call_slot * v57204;
        { { Call_slot * v47292 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
            update_property(Kernel.selector,
              v47292,
              2,
              Kernel._object,
              v48367);
            (v47292->arg = (*Optimize.c_code)(v48372,
              _oid_(psort_any(_oid_(domain_I_restriction(OBJECT(restriction,v48367)))))));
            (v47292->test = CFALSE);
            add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v47292));
            v57204 = v47292;
            }
          GC_OBJECT(Call_slot,v57204);}
        Call_method2 * v57198;
        { { Call_method2 * v61954;
            { Call_method2 * v47292 = ((Call_method2 *) GC_OBJECT(Call_method2,new_object_class(Language._Call_method2)));
              (v47292->arg = ((method *) _at_property1(Core.identical_ask,Kernel._any)));
              (v47292->args = list::alloc(2,_oid_(v57204),GC_OID((*Optimize.c_code)(v48373,
                GC_OID((*Kernel.srange)(v48367))))));
              add_I_property(Kernel.instances,Language._Call_method2,11,_oid_(v47292));
              v61954 = v47292;
              }
            v57198 = loc_I_Call_method21(v61954);
            }
          GC_OBJECT(Call_method2,v57198);}
        if (v48350 == CTRUE)
         Result = (*Optimize.c_code)(_oid_(v57198));
        else { OID  v62915;
            { { Call * v63607;{ Call * v64837;
                  { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Core.NOT);
                    (v47292->args = list::alloc(1,_oid_(v57198)));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v64837 = v47292;
                    }
                  v63607 = loc_I_Call1(v64837);
                  }
                
                v62915=_oid_(v63607);}
              GC_OID(v62915);}
            Result = (*Optimize.c_code)(v62915);
            }
          }
      else { list * v48360 = list::alloc(2,_oid_(Kernel._any),_oid_(Kernel._any));
          { list * v262;
            { OID v_bag;
              GC_ANY(v262= list::empty(Kernel.emptySet));
              { { OID  v1223;
                  { { Call * v63611;{ Call * v3145;
                        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          (v47292->selector = Kernel.get);
                          (v47292->args = list::alloc(2,_oid_(v48364),v48372));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                          v3145 = v47292;
                          }
                        v63611 = loc_I_Call1(v3145);
                        }
                      
                      v1223=_oid_(v63611);}
                    GC_OID(v1223);}
                  v_bag = (*Optimize.c_code)(v1223,
                    _oid_(Kernel._any));
                  }
                GC_OID(v_bag);}
              ((list *) v262)->addFast((OID)v_bag);
              ((list *) v262)->addFast((OID)GC_OID((*Optimize.c_code)(v48373,
                _oid_(Kernel._any))));}
            Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property2(((v48350 == CTRUE) ?
              Kernel._equal :
              Core._I_equal ),v48360))),v262,v48360);
            }
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_add_Call(Call *v61776)
{ GC_BIND;
  loc_I_Call1(v61776);
  { OID Result = 0;
    { property * v48364 = OBJECT(property,(*(v61776->args))[1]);
      OID  v48372 = GC_OID((*(v61776->args))[2]);
      OID  v48373 = GC_OID((*(v61776->args))[3]);
      ClaireObject * v48367 = GC_OBJECT(ClaireObject,_at_property1(v48364,class_I_type(GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v48372)))))));
      (Optimize.OPT->use_update = CTRUE);
      if ((Kernel._slot == v48367->isa) && ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v48373))),GC_OBJECT(ClaireType,member_type(CLREAD(restriction,v48367,range)))) == CTRUE) || 
          (4 <= (CL_INT)Optimize.compiler->safety)))
       { if (Update_ask_relation2(v48364,v61776->selector) == CTRUE)
         { OID  v57790 = GC_OID((*Optimize.c_code)(v48372,
            _oid_(psort_any(_oid_(domain_I_restriction(((restriction *) v48367)))))));
          Update * v47292 = ((Update *) GC_OBJECT(Update,new_object_class(Language._Update)));
          (v47292->selector = _oid_(v48364));
          (v47292->arg = _oid_(Kernel.add));
          { Update * v22507 = v47292; 
            OID  v22528;
            { Call_slot * v47292 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
              (v47292->selector = ((slot *) v48367));
              (v47292->arg = v57790);
              (v47292->test = CFALSE);
              add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v47292));
              v22528 = _oid_(v47292);
              }
            (v22507->var = v22528);}
          (v47292->value = (*Optimize.c_code)(v48373,
            _oid_(psort_any(GC_OID(_oid_(member_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(_oid_(v48367)))))))))));
          add_I_property(Kernel.instances,Language._Update,11,_oid_(v47292));
          Result = _oid_(v47292);
          }
        else if ((designated_ask_any(v48372) == CTRUE) && 
            ((v48364->store_ask != CTRUE) && 
                ((v61776->selector == Kernel.add_I) || 
                    (v48364->inverse == (NULL)))))
         { OID  v57790 = GC_OID((*Optimize.c_code)(v48372,
            _oid_(psort_any(_oid_(domain_I_restriction(((restriction *) v48367)))))));
          { OID  v26209;
            { { Call * v63637;{ Call * v28131;
                  { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Kernel.add);
                    { Call * v22532 = v47292; 
                      list * v22533;
                      { OID v_bag;
                        GC_ANY(v22533= list::empty(Kernel.emptySet));
                        { { Call_slot * v47292 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
                            (v47292->selector = ((slot *) v48367));
                            (v47292->arg = v57790);
                            (v47292->test = CFALSE);
                            add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v47292));
                            v_bag = _oid_(v47292);
                            }
                          GC_OID(v_bag);}
                        ((list *) v22533)->addFast((OID)v_bag);
                        ((list *) v22533)->addFast((OID)v48373);}
                      (v22532->args = v22533);}
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v28131 = v47292;
                    }
                  v63637 = loc_I_Call1(v28131);
                  }
                
                v26209=_oid_(v63637);}
              GC_OID(v26209);}
            Result = (*Optimize.c_code)(v26209);
            }
          }
        else { if (Optimize.compiler->optimize_ask == CTRUE)
             { notice_void();
              if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
               mtformat_module1(Optimize.it,"`GREEN poorly typed update: ~S\n",3,list::alloc(1,_oid_(v61776)));
              else ;}
            Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property1(Kernel.add_I,Kernel._property))),list::alloc(4,_oid_(v48364),
              v48372,
              (*Kernel.index)(_oid_(v48367)),
              v48373),list::alloc(4,_oid_(Kernel._property),
              GC_OID((*Optimize.c_type)(v48372)),
              _oid_(Kernel._integer),
              GC_OID((*Optimize.c_type)(v48373))));
            }
          }
      else { list * v31014;
          { { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID v48372; CL_INT CLcount;
              v_list = GC_OBJECT(list,v61776->args);
               v31014 = v_list->clone();
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { v48372 = (*(v_list))[CLcount];
                v_val = (*Optimize.c_type)(v48372);
                
                (*((list *) v31014))[CLcount] = v_val;}
              }
            GC_OBJECT(list,v31014);}
          Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property1(Kernel.add,Kernel._property))),GC_OBJECT(list,v61776->args),v31014);
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_add_bag_Call(Call *v61776)
{ GC_BIND;
  loc_I_Call1(v61776);
  { OID Result = 0;
    { OID  v9886 = GC_OID((*Optimize.c_type)(GC_OID((*(v61776->args))[1])));
      ClaireType * v9887 = GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(GC_OID((*(v61776->args))[2])))));
      property * v55279;
      if (((INHERIT(OBJECT(ClaireObject,v9886)->isa,Core._Param)) && 
            (_inf_equal_type(v9887,GC_OBJECT(ClaireType,member_type(OBJECT(ClaireType,v9886)))) == CTRUE)) || 
          (4 <= (CL_INT)Optimize.compiler->safety))
       v55279 = Kernel.add_I;
      else v55279 = v61776->selector;
        list * v31141 = list::alloc(2,v9886,_oid_(v9887));
      OID  v48374 = GC_OID(restriction_I_property(v55279,v31141,CTRUE));
      if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
       mtformat_module1(Optimize.it,"~S: ~S -> ~S \n",5,list::alloc(3,_oid_(v61776),
        _oid_(v31141),
        v48374));
      else ;if ((_inf_equal_type(v9887,GC_OBJECT(ClaireType,member_type(OBJECT(ClaireType,v9886)))) != CTRUE) && 
          (v61776->selector == Kernel.add))
       { warn_void();
        if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
         mtformat_module1(Optimize.it,"`BLUE the bag addition ~S is poorly typed (~S) [251] \n",2,list::alloc(2,_oid_(v61776),GC_OID(_oid_(member_type(OBJECT(ClaireType,v9886))))));
        else ;}
      if (Kernel._method == OWNER(v48374))
       Result = c_code_method_method1(OBJECT(method,v48374),GC_OBJECT(list,v61776->args),v31141);
      else Result = c_warn_Call(v61776,_oid_(v31141));
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_delete_Call(Call *v61776)
{ GC_BIND;
  loc_I_Call1(v61776);
  { OID Result = 0;
    { OID  v48364 = GC_OID((*(v61776->args))[1]);
      OID  v48372 = GC_OID((*(v61776->args))[2]);
      OID  v48373 = GC_OID((*(v61776->args))[3]);
      ClaireObject * v48367 = GC_OBJECT(ClaireObject,_at_property1(OBJECT(property,v48364),class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v48372))))));
      (Optimize.OPT->use_update = CTRUE);
      if ((OBJECT(ClaireRelation,v48364)->inverse == (NULL)) && 
          ((designated_ask_any(v48372) == CTRUE) && 
            ((Kernel._slot == v48367->isa) && ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v48373))),GC_OBJECT(ClaireType,member_type(CLREAD(restriction,v48367,range)))) == CTRUE) || 
                (4 <= (CL_INT)Optimize.compiler->safety)))))
       { OID  v57790 = GC_OID((*Optimize.c_code)(v48372,
          _oid_(psort_any(_oid_(domain_I_restriction(((restriction *) v48367)))))));
        { OID  v31975;
          { { Call * v63643;{ Call * v33897;
                { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  (v47292->selector = Kernel._delete);
                  { Call * v22559 = v47292; 
                    list * v22560;
                    { OID v_bag;
                      GC_ANY(v22560= list::empty(Kernel.emptySet));
                      { { Call_slot * v47292 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
                          (v47292->selector = ((slot *) v48367));
                          (v47292->arg = v57790);
                          (v47292->test = CFALSE);
                          add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v47292));
                          v_bag = _oid_(v47292);
                          }
                        GC_OID(v_bag);}
                      ((list *) v22560)->addFast((OID)v_bag);
                      ((list *) v22560)->addFast((OID)v48373);}
                    (v22559->args = v22560);}
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                  v33897 = v47292;
                  }
                v63643 = loc_I_Call1(v33897);
                }
              
              v31975=_oid_(v63643);}
            GC_OID(v31975);}
          Result = (*Optimize.c_code)(v31975);
          }
        }
      else { list * v56961;
          { { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID v48372; CL_INT CLcount;
              v_list = GC_OBJECT(list,v61776->args);
               v56961 = v_list->clone();
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { v48372 = (*(v_list))[CLcount];
                v_val = (*Optimize.c_type)(v48372);
                
                (*((list *) v56961))[CLcount] = v_val;}
              }
            GC_OBJECT(list,v56961);}
          Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property1(Kernel._delete,Kernel._property))),GC_OBJECT(list,v61776->args),v56961);
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_not_Select(Select *v48372)
{ GC_BIND;
  { OID Result = 0;
    { OID  v57922;
      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
        (v47292->selector = Core.NOT);
        { Call * v22563 = v47292; 
          list * v22564;
          { OID v_bag;
            GC_ANY(v22564= list::empty(Kernel.emptySet));
            { { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                (v47292->var = v48372->var);
                (v47292->set_arg = v48372->set_arg);
                { Iteration * v22565 = v47292; 
                  OID  v22566;
                  { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                    (v47292->test = v48372->arg);
                    { If * v22567 = v47292; 
                      OID  v22568;
                      { Return * v47292 = ((Return *) GC_OBJECT(Return,new_object_class(Language._Return)));
                        (v47292->arg = Kernel.ctrue);
                        add_I_property(Kernel.instances,Language._Return,11,_oid_(v47292));
                        v22568 = _oid_(v47292);
                        }
                      (v22567->arg = v22568);}
                    (v47292->other = CNULL);
                    add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                    v22566 = _oid_(v47292);
                    }
                  (v22565->arg = v22566);}
                add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
                v_bag = _oid_(v47292);
                }
              GC_OID(v_bag);}
            ((list *) v22564)->addFast((OID)v_bag);}
          (v22563->args = v22564);}
        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
        v57922 = _oid_(v47292);
        }
      Result = (*Optimize.c_code)(v57922);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_belong_Call(Call *v61776)
{ GC_BIND;
  loc_I_Call1(v61776);
  { OID Result = 0;
    { OID  v48372 = GC_OID((*(v61776->args))[1]);
      OID  v48373 = GC_OID((*(v61776->args))[2]);
      list * v4955 = list::alloc(2,GC_OID((*Optimize.c_type)(v48373)),GC_OID((*Optimize.c_type)(v48372)));
      if (Kernel._set == OWNER(v48373))
       { Or * v47292 = ((Or *) GC_OBJECT(Or,new_object_class(Language._Or)));
        { Or * v22590 = v47292; 
          list * v22591;
          { list * v64831 = list::empty(Kernel.emptySet);
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(v48374);
              bag *v48374_support;
              v48374_support = GC_OBJECT(bag,enumerate_any(v48373));
              for (START(v48374_support); NEXT(v48374);)
              { GC_LOOP;
                { OID  v21216;
                  { { OID  v22177;
                      { { Call * v63701;{ Call * v24099;
                            { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                              (v47292->selector = Kernel._equal);
                              (v47292->args = list::alloc(2,v48372,v48374));
                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                              v24099 = v47292;
                              }
                            v63701 = loc_I_Call1(v24099);
                            }
                          
                          v22177=_oid_(v63701);}
                        GC_OID(v22177);}
                      v21216 = (*Optimize.c_code)(v22177,
                        _oid_(Kernel._any));
                      }
                    GC_OID(v21216);}
                  v64831->addFast((OID)v21216);
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            v22591 = GC_OBJECT(list,v64831);
            }
          (v22590->args = v22591);}
        add_I_property(Kernel.instances,Language._Or,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      else if (_inf_equal_type(OBJECT(ClaireType,(*(v4955))[1]),Kernel._list) == CTRUE)
       Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property2(Kernel.contain_ask,GC_OBJECT(list,list::alloc(2,_oid_(Kernel._list),_oid_(Kernel._any)))))),GC_OBJECT(list,list::alloc(2,v48373,v48372)),v4955);
      else if (_inf_equal_type(OBJECT(ClaireType,(*(v4955))[1]),Kernel._set) == CTRUE)
       Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property2(Kernel.contain_ask,GC_OBJECT(list,list::alloc(2,_oid_(Kernel._set),_oid_(Kernel._any)))))),GC_OBJECT(list,list::alloc(2,v48373,v48372)),v4955);
      else if (v48373 == _oid_(Kernel._object))
       Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property2(Kernel._Z,GC_OBJECT(list,list::alloc(2,_oid_(Kernel._any),_oid_(Kernel._class)))))),GC_OBJECT(list,list::alloc(2,v48372,v48373)),GC_OBJECT(list,list::alloc(2,_oid_(Kernel._any),_oid_(Kernel._class))));
      else Result = (*Optimize.member_code)(v48373,
          v48372);
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_nth_Call(Call *v61776)
{ GC_BIND;
  loc_I_Call1(v61776);
  { OID Result = 0;
    { list * v48360 = GC_OBJECT(list,v61776->args);
      OID  v48372 = (*(v48360))[1];
      property * v48364 = v61776->selector;
      OID  v48368 = GC_OID((*Optimize.c_type)(v48372));
      ClaireType * v57515 = GC_OBJECT(ClaireType,member_type(OBJECT(ClaireType,v48368)));
      OID  v48366;
      { { list * v25060;
          { { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID v48369; CL_INT CLcount;
              v_list = v48360;
               v25060 = v_list->clone();
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { v48369 = (*(v_list))[CLcount];
                v_val = (*Optimize.c_type)(v48369);
                
                (*((list *) v25060))[CLcount] = v_val;}
              }
            GC_OBJECT(list,v25060);}
          v48366 = restriction_I_property(v48364,v25060,CTRUE);
          }
        GC_OID(v48366);}
      if (contain_ask_set(Optimize.OPT->to_remove,v48372) == CTRUE)
       Result = Core.nil->value;
      else if (((INHERIT(OWNER(v48372),Kernel._table)) && (INHERIT(OWNER(OBJECT(table,v48372)->params),Kernel._integer))) && 
          ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)((*(v48360))[2]))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.domain)(v48372)))) == CTRUE) || 
              ((v48364 == Kernel.nth) && 
                  ((CL_INT)Optimize.compiler->safety > 2))))
       { Call_table * v47292 = ((Call_table *) GC_OBJECT(Call_table,new_object_class(Language._Call_table)));
        update_property(Kernel.selector,
          v47292,
          2,
          Kernel._object,
          v48372);
        (v47292->arg = (*Optimize.c_code)((*(v48360))[2],
          _oid_(Kernel._integer)));
        (v47292->test = not_any(_oid_(((belong_to(GC_OID((*Kernel.DEFAULT)(v48372)),GC_OID((*Kernel.range)(v48372))) == CTRUE) ? CTRUE : (((*Kernel.DEFAULT)(v48372) == ((OID)0)) ? CTRUE : ((v48364 == Kernel.get) ? CTRUE : CFALSE))))));
        add_I_property(Kernel.instances,Language._Call_table,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      else if (((INHERIT(OWNER(v48372),Kernel._table)) && (INHERIT(OWNER(OBJECT(table,v48372)->params),Kernel._list))) && 
          ((v48360->length == 3) && 
            ((_inf_equal_type(GC_OBJECT(tuple,tuple_I_list(list::alloc(2,GC_OID((*Optimize.c_type)((*(v48360))[2])),GC_OID((*Optimize.c_type)((*(v48360))[3]))))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.domain)(v48372)))) == CTRUE) || 
                ((CL_INT)Optimize.compiler->safety > 2))))
       { Call_table * v47292 = ((Call_table *) GC_OBJECT(Call_table,new_object_class(Language._Call_table)));
        update_property(Kernel.selector,
          v47292,
          2,
          Kernel._object,
          v48372);
        { Call_table * v22597 = v47292; 
          OID  v22598;
          { List * v47292 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
            (v47292->args = list::alloc(2,GC_OID((*Optimize.c_code)((*(v48360))[2],
              _oid_(Kernel._integer))),GC_OID((*Optimize.c_code)((*(v48360))[3],
              _oid_(Kernel._integer)))));
            add_I_property(Kernel.instances,Language._List,11,_oid_(v47292));
            v22598 = _oid_(v47292);
            }
          (v22597->arg = v22598);}
        (v47292->test = not_any(_oid_(((belong_to(GC_OID((*Kernel.DEFAULT)(v48372)),GC_OID((*Kernel.range)(v48372))) == CTRUE) ? CTRUE : (((*Kernel.DEFAULT)(v48372) == ((OID)0)) ? CTRUE : ((v48364 == Kernel.get) ? CTRUE : CFALSE))))));
        add_I_property(Kernel.instances,Language._Call_table,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      else if ((_inf_equal_type(OBJECT(ClaireType,v48368),Kernel._array) == CTRUE) && 
          (((v48364 == Kernel.nth_get) || 
              ((CL_INT)Optimize.compiler->safety > 2)) && 
            ((_inf_equal_type(v57515,Kernel._float) == CTRUE) || 
                (equal(_oid_(_exp_type(v57515,Kernel._float)),_oid_(Kernel.emptySet)) == CTRUE))))
       { Call_array * v47292 = ((Call_array *) GC_OBJECT(Call_array,new_object_class(Language._Call_array)));
        (v47292->selector = (*Optimize.c_code)(v48372,
          _oid_(Kernel._array)));
        (v47292->arg = (*Optimize.c_code)((*(v48360))[2],
          _oid_(Kernel._integer)));
        (v47292->test = _oid_(v57515));
        add_I_property(Kernel.instances,Language._Call_array,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      else if (Kernel._method == OWNER(v48366))
       { if ((Optimize.compiler->optimize_ask == CTRUE) && 
            ((_inf_equal_type(OBJECT(ClaireType,v48368),Kernel._array) == CTRUE) || 
                (_inf_equal_type(OBJECT(ClaireType,v48368),Kernel._table) == CTRUE)))
         { notice_void();
          if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
           mtformat_module1(Optimize.it,"`GREEN poorly typed call: ~S\n",3,list::alloc(1,_oid_(v61776)));
          else ;}
        { list * v27943;
          { { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID v48372; CL_INT CLcount;
              v_list = GC_OBJECT(list,v61776->args);
               v27943 = v_list->clone();
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { v48372 = (*(v_list))[CLcount];
                v_val = (*Optimize.c_type)(v48372);
                
                (*((list *) v27943))[CLcount] = v_val;}
              }
            GC_OBJECT(list,v27943);}
          Result = c_code_method_method1(OBJECT(method,v48366),GC_OBJECT(list,v61776->args),v27943);
          }
        }
      else { list * v49085;
          { { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID v48372; CL_INT CLcount;
              v_list = GC_OBJECT(list,v61776->args);
               v49085 = v_list->clone();
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { v48372 = (*(v_list))[CLcount];
                v_val = (*Optimize.c_type)(v48372);
                
                (*((list *) v49085))[CLcount] = v_val;}
              }
            GC_OBJECT(list,v49085);}
          Result = c_warn_property(v48364,GC_OBJECT(list,v61776->args),v49085);
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_table_Call(Call *v61776)
{ GC_BIND;
  loc_I_Call1(v61776);
  { OID Result = 0;
    { property * v57697 = v61776->selector;
      table * v48364 = GC_OBJECT(table,OBJECT(table,(*(v61776->args))[1]));
      OID  v48372 = GC_OID((*(v61776->args))[2]);
      OID  v48373 = GC_OID((*(v61776->args))[3]);
      if (contain_ask_set(Optimize.OPT->to_remove,_oid_(v48364)) == CTRUE)
       Result = Core.nil->value;
      else if ((v57697 == Kernel.put) || 
          (((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v48372))),v48364->domain) == CTRUE) || 
                (5 <= (CL_INT)Optimize.compiler->safety)) && 
              ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v48373))),v48364->range) == CTRUE) || 
                  (4 <= (CL_INT)Optimize.compiler->safety))))
       { if ((Update_ask_relation(v48364,v48372,v48373) == CTRUE) && 
            ((INHERIT(OWNER(v48364->params),Kernel._list)) || 
                (INHERIT(OWNER(v48364->params),Kernel._integer))))
         { OID  v55287 = GC_OID((*Optimize.c_code)(v48372,
            _oid_(Kernel._any)));
          OID  v55288 = GC_OID((*Optimize.c_code)(v48373,
            _oid_(Kernel._any)));
          Update * v47292 = ((Update *) GC_OBJECT(Update,new_object_class(Language._Update)));
          (v47292->selector = _oid_(v48364));
          (v47292->value = v55288);
          { Update * v22622 = v47292; 
            OID  v22623;
            if (v57697 == Kernel.put)
             v22623 = _oid_(Kernel.put);
            else v22623 = v55287;
              (v22622->arg = v22623);}
          { Update * v22624 = v47292; 
            OID  v22625;
            { Call_table * v47292 = ((Call_table *) GC_OBJECT(Call_table,new_object_class(Language._Call_table)));
              (v47292->selector = v48364);
              (v47292->arg = v55287);
              (v47292->test = CFALSE);
              add_I_property(Kernel.instances,Language._Call_table,11,_oid_(v47292));
              v22625 = _oid_(v47292);
              }
            (v22624->var = v22625);}
          add_I_property(Kernel.instances,Language._Update,11,_oid_(v47292));
          Result = _oid_(v47292);
          }
        else if ((v57697 == Kernel.put) || 
            ((v48364->inverse == (NULL)) && 
                (v48364->if_write == CNULL)))
         { if (Optimize.compiler->optimize_ask == CTRUE)
           { notice_void();
            if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
             mtformat_module1(Optimize.it,"`GREEN poorly typed update: ~S\n",3,list::alloc(1,_oid_(v61776)));
            else ;}
          Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property1(Kernel.put,Kernel._table))),GC_OBJECT(list,v61776->args),list::alloc(3,_oid_(Kernel._table),
            _oid_(Kernel._any),
            _oid_(Kernel._any)));
          }
        else Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property1(Kernel.nth_put,Kernel._table))),GC_OBJECT(list,v61776->args),list::alloc(3,_oid_(Kernel._table),
            _oid_(Kernel._any),
            _oid_(Kernel._any)));
          }
      else Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property1(Kernel.nth_equal,Kernel._table))),GC_OBJECT(list,v61776->args),list::alloc(3,_oid_(Kernel._table),
          _oid_(Kernel._any),
          _oid_(Kernel._any)));
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_array_Call(Call *v61776)
{ GC_BIND;
  loc_I_Call1(v61776);
  { OID Result = 0;
    { property * v57697 = v61776->selector;
      OID  v48364 = GC_OID((*(v61776->args))[1]);
      OID  v57729 = GC_OID((*Optimize.c_type)(v48364));
      ClaireType * v57515 = GC_OBJECT(ClaireType,member_type(OBJECT(ClaireType,v57729)));
      OID  v48372 = GC_OID((*(v61776->args))[2]);
      OID  v48373 = GC_OID((*(v61776->args))[3]);
      ClaireBoolean * v26522 = ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v48373))),GC_OBJECT(ClaireType,member_type(OBJECT(ClaireType,v57729)))) == CTRUE) ? CTRUE : ((4 <= (CL_INT)Optimize.compiler->safety) ? CTRUE : CFALSE));
      if (((v57697 == Kernel.nth_put) || 
            (v26522 == CTRUE)) && 
          ((_inf_equal_type(v57515,Kernel._float) == CTRUE) || 
              (equal(_oid_(_exp_type(v57515,Kernel._float)),_oid_(Kernel.emptySet)) == CTRUE)))
       { OID  v55287 = GC_OID((*Optimize.c_code)(v48372,
          _oid_(Kernel._integer)));
        OID  v55288;
        { { OID  v53890;
            if (_inf_equal_type(v57515,Kernel._float) == CTRUE)
             v53890 = _oid_(Kernel._float);
            else v53890 = _oid_(Kernel._any);
              v55288 = (*Optimize.c_code)(v48373,
              v53890);
            }
          GC_OID(v55288);}
        Update * v47292 = ((Update *) GC_OBJECT(Update,new_object_class(Language._Update)));
        (v47292->selector = v48364);
        (v47292->value = v55288);
        (v47292->arg = _oid_(Kernel.put));
        { Update * v22628 = v47292; 
          OID  v22629;
          { Call_array * v47292 = ((Call_array *) GC_OBJECT(Call_array,new_object_class(Language._Call_array)));
            (v47292->selector = (*Optimize.c_code)(v48364,
              _oid_(Kernel._array)));
            (v47292->arg = v55287);
            (v47292->test = _oid_(v57515));
            add_I_property(Kernel.instances,Language._Call_array,11,_oid_(v47292));
            v22629 = _oid_(v47292);
            }
          (v22628->var = v22629);}
        add_I_property(Kernel.instances,Language._Update,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      else { if (Optimize.compiler->optimize_ask == CTRUE)
           { notice_void();
            if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
             mtformat_module1(Optimize.it,"`GREEN poorly typed update: ~S\n",3,list::alloc(1,_oid_(v61776)));
            else ;}
          Result = c_code_method_method1(GC_OBJECT(method,((method *) _at_property1(((v26522 == CTRUE) ?
            Kernel.nth_put :
            v57697 ),Kernel._array))),GC_OBJECT(list,v61776->args),list::alloc(3,v57729,
            _oid_(Kernel._any),
            _oid_(Kernel._any)));
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * Update_ask_relation(ClaireRelation *v48364,OID v48372,OID v48373)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = ((v48364 != Kernel.inverse) ? ((((((v48364->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE) && 
          (inherit_ask_class(OWNER(v48364->if_write),Kernel._list) != CTRUE)) || 
        ((v48364->inverse == (NULL)) && 
            (((INHERIT(v48364->isa,Kernel._table)) ? (INHERIT(OWNER(CLREAD(table,v48364,params)),Kernel._integer)) : (CTRUE == CTRUE)) && 
              ((v48364->store_ask == CTRUE) ? ((designated_ask_any(v48372) == CTRUE) && 
                  ((designated_ask_any(v48373) == CTRUE) && 
                    ((multi_ask_any(_oid_(v48364)) != CTRUE) && 
                      ((identifiable_ask_any(v48373) == CTRUE) || 
                          (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v48373))),Kernel._float) == CTRUE))))) : (CTRUE == CTRUE))))) ? CTRUE: CFALSE): CFALSE);
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * Update_ask_relation2(ClaireRelation *v48364,ClaireRelation *v48367)
{ POP_SIGNAL; return (((((v48364->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE) ? ((inherit_ask_class(OWNER(v48364->if_write),Kernel._list) != CTRUE) ? ((v48367 == Kernel.add) ? CTRUE: CFALSE): CFALSE): CFALSE));}

ClaireType * c_type_Update_Optimize(Update *v61776)
{ POP_SIGNAL; return (Kernel._void);}

OID  c_code_method_method1(method *v61776,list *v48360,list *v4955)
{ POP_SIGNAL; return (c_code_method_method2(v61776,v48360,v4955,c_srange_method(v61776)));}

OID  c_code_method_method2(method *v61776,list *v48360,list *v4955,ClaireClass *v57706)
{ GC_BIND;
  { OID Result = 0;
    if ((v61776->module_I != claire.it) || 
        (((CL_INT)Optimize.compiler->safety > 4) || 
          (((v61776->functional == (NULL)) ? CTRUE : CFALSE) != CTRUE)))
     { list * v57468 = v61776->domain;
      CL_INT  v48362 = v57468->length;
      if (v48362 != v48360->length)
       { list * v14301;
        { list * v28078 = list::empty(Kernel.emptySet);
          { CL_INT  v48357 = 1;
            CL_INT  v22631 = ((CL_INT)v48362-(CL_INT)1);
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while (((CL_INT)v48357 <= (CL_INT)v22631))
              { v28078->addFast((OID)(*(v48360))[v48357]);
                ++v48357;
                POP_SIGNAL;}
              }
            }
          v14301 = GC_OBJECT(list,v28078);
          }
        OID  v15262;
        { list * v63762;{ list * v28078 = list::empty(Kernel.emptySet);
            { CL_INT  v48357 = v48362;
              CL_INT  v22632 = v48360->length;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                while (((CL_INT)v48357 <= (CL_INT)v22632))
                { v28078->addFast((OID)(*(v48360))[v48357]);
                  ++v48357;
                  POP_SIGNAL;}
                }
              }
            v63762 = GC_OBJECT(list,v28078);
            }
          
          v15262=_oid_(v63762);}
        v48360 = v14301->addFast((OID)v15262);
        }
      if ((v61776->inline_ask == CTRUE) && 
          (c_inline_ask_method(v61776,v48360) == CTRUE))
       Result = c_inline_method1(v61776,v48360,v57706);
      else { ClaireBoolean * v48350 = Optimize.OPT->allocation;
          OID  v48372 = Core.nil->value;
          (Optimize.OPT->allocation = CFALSE);
          { { list * v17184;
              { list * v28078 = list::empty(Kernel.emptySet);
                { CL_INT  v48357 = 1;
                  CL_INT  v22652 = v48362;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    OID gc_local;
                    while (((CL_INT)v48357 <= (CL_INT)v22652))
                    { GC_LOOP;
                      v28078->addFast((OID)GC_OID(c_strict_code_any((*(v48360))[v48357],psort_any((*(v57468))[v48357]))));
                      ++v48357;
                      GC_UNLOOP;POP_SIGNAL;}
                    }
                  }
                v17184 = GC_OBJECT(list,v28078);
                }
              v48372 = Call_method_I_method(v61776,v17184);
              }
            GC_OID(v48372);}
          if (Optimize.OPT->allocation != CTRUE)
           (Optimize.OPT->allocation = v48350);
          Result = v48372;
          }
        }
    else { if (Optimize.compiler->optimize_ask == CTRUE)
         { notice_void();
          if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
           mtformat_module1(Optimize.it,"`GREEN poorly typed update: ~S\n",3,GC_OBJECT(list,list::alloc(1,_oid_(v61776))));
          else ;}
        Result = _oid_(open_message_property(v61776->selector,v48360));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  Call_method_I_method(method *v61776,list *v12814)
{ GC_BIND;
  if (BCONTAIN(status_I_restriction(v61776),(OID)(1)))
   { (Optimize.OPT->allocation = CTRUE);
    if (nth_integer(v61776->status,(OID)(6)) != CTRUE)
     { { CL_INT loop_handle = ClEnv->cHandle;
        bag *v_list; OID v_val;
        OID v48372; CL_INT CLcount;
        v_list = v12814;
         v12814 = v_list->clone();
        for (CLcount= 1; CLcount <= v_list->length; CLcount++)
        { v48372 = (*(v_list))[CLcount];
          v_val = c_gc_I_any1(v48372);
          
          (*((list *) v12814))[CLcount] = v_val;}
        }
      GC_OBJECT(list,v12814);}
    }
  else { ClaireBoolean * g1065I;
    { ClaireBoolean *v_and;
      { v_and = Optimize.OPT->allocation;
        if (v_and == CFALSE) g1065I =CFALSE; 
        else { { CL_INT  v19106;
            { list * v20067;
              { bag * v8272 = v12814;
                list * v387 = ((list *) empty_bag(v8272));
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(v48372);
                  for (START(v8272); NEXT(v48372);)
                  if ((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v48372))) == CTRUE)
                   v387->addFast((OID)v48372);
                  }
                v20067 = GC_OBJECT(list,v387);
                }
              v19106 = v20067->length;
              }
            v_and = (((CL_INT)v19106 > 1) ? CTRUE : CFALSE);
            }
          if (v_and == CFALSE) g1065I =CFALSE; 
          else g1065I = CTRUE;}
        }
      }
    
    if (g1065I == CTRUE) { { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v48372; CL_INT CLcount;
          v_list = v12814;
           v12814 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v48372 = (*(v_list))[CLcount];
            v_val = c_gc_I_any1(v48372);
            
            (*((list *) v12814))[CLcount] = v_val;}
          }
        GC_OBJECT(list,v12814);}
      }
  if (BCONTAIN(v61776->status,(OID)(2)))
   (Optimize.OPT->use_nth_equal = CTRUE);
  if (BCONTAIN(v61776->status,(OID)(3)))
   (Optimize.OPT->use_update = CTRUE);
  if (legal_ask_module(v61776->module_I,_oid_(v61776)) != CTRUE)
   { if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
     mtformat_module1(Optimize.it,"in call ~S~S\n",0,list::alloc(2,_oid_(v61776->selector),_oid_(v12814)));
    else ;}
  { OID Result = 0;
    if (v12814->length == 1)
     { Call_method1 * v63767;{ Call_method1 * v21989;
        { Call_method1 * v47292 = ((Call_method1 *) GC_OBJECT(Call_method1,new_object_class(Language._Call_method1)));
          (v47292->arg = v61776);
          (v47292->args = v12814);
          add_I_property(Kernel.instances,Language._Call_method1,11,_oid_(v47292));
          v21989 = v47292;
          }
        v63767 = loc_I_Call_method11(v21989);
        }
      
      Result=_oid_(v63767);}
    else if (v12814->length == 2)
     { Call_method2 * v63790;{ Call_method2 * v44092;
        { Call_method2 * v47292 = ((Call_method2 *) GC_OBJECT(Call_method2,new_object_class(Language._Call_method2)));
          (v47292->arg = v61776);
          (v47292->args = v12814);
          add_I_property(Kernel.instances,Language._Call_method2,11,_oid_(v47292));
          v44092 = v47292;
          }
        v63790 = loc_I_Call_method21(v44092);
        }
      
      Result=_oid_(v63790);}
    else { OID  v45053;
        { Call_method * v47292 = ((Call_method *) GC_OBJECT(Call_method,new_object_class(Language._Call_method)));
          (v47292->arg = v61776);
          (v47292->args = v12814);
          add_I_property(Kernel.instances,Language._Call_method,11,_oid_(v47292));
          v45053 = _oid_(v47292);
          }
        Result = (*Optimize.loc_I)(v45053);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Call_method_Optimize(Call_method *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    { list * v46014;
      { { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v48372; CL_INT CLcount;
          v_list = GC_OBJECT(list,v61776->args);
           v46014 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v48372 = (*(v_list))[CLcount];
            v_val = (*Optimize.c_type)(v48372);
            
            (*((list *) v46014))[CLcount] = v_val;}
          }
        GC_OBJECT(list,v46014);}
      Result = use_range_method(v61776->arg,v46014);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Call_method_Optimize(Call_method *v61776)
{ POP_SIGNAL; return (_oid_(v61776));}

ClaireBoolean * c_gc_ask_Call_method(Call_method *v61776)
{ GC_BIND;
  { ClaireBoolean *Result ;
    { method * v48361 = v61776->arg;
      { ClaireBoolean *v_and;
        { v_and = not_any(_oid_((INHERIT(v48361->range->isa,Kernel._class) ?
           (ClaireObject *) gcsafe_ask_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v48361->range))) : 
           (ClaireObject *)  gcsafe_ask_type((ClaireType *) OBJECT(ClaireType,_oid_(v48361->range))))));
          if (v_and == CFALSE) Result =CFALSE; 
          else { v_and = ((v48361->range != Kernel._float) ? CTRUE : CFALSE);
            if (v_and == CFALSE) Result =CFALSE; 
            else { v_and = ((nth_integer(status_I_restriction(v48361),(OID)(5)) != CTRUE) ? CTRUE : ((((_inf_equal_type(v48361->range,Kernel._bag) == CTRUE) ? ((Optimize.OPT->loop_gc == CTRUE) ? CTRUE: CFALSE): CFALSE) != CTRUE) ? CTRUE : CFALSE));
              if (v_and == CFALSE) Result =CFALSE; 
              else { { ClaireBoolean *v_or;
                  { v_or = nth_integer(status_I_restriction(v48361),(OID)(1));
                    if (v_or == CTRUE) v_and =CTRUE; 
                    else { { ClaireBoolean *v_and;
                        { v_and = nth_integer(v48361->status,(OID)(4));
                          if (v_and == CFALSE) v_or =CFALSE; 
                          else { { OID  v46975;
                              { CL_INT loop_handle = ClEnv->cHandle;
                                OID gc_local;
                                ITERATE(v48372);
                                v46975= Kernel.cfalse;
                                bag *v48372_support;
                                v48372_support = GC_OBJECT(list,v61776->args);
                                for (START(v48372_support); NEXT(v48372);)
                                if ((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v48372))) == CTRUE)
                                 { v46975 = Kernel.ctrue;
                                  ClEnv->cHandle = loop_handle;break;}
                                }
                              v_and = boolean_I_any(v46975);
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

ClaireFunction * functional_I_method_Optimize(method *v61776)
{ GC_BIND;
  { ClaireFunction *Result ;
    { OID  v48354 = GC_OID(get_property(Kernel.functional,v61776));
      property * v48364 = v61776->selector;
      Result = ((INHERIT(OWNER(v48354),Kernel._function)) ?
        OBJECT(ClaireFunction,v48354) :
        make_function_string(string_v((*Optimize.function_name)(_oid_(v48364),
          _oid_(v61776->domain),
          v48354))) );
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  nth_type_check_type(ClaireType *v57724,ClaireType *v57721,ClaireType *v57736)
{ GC_BIND;
  if (_inf_equal_type(v57736,GC_OBJECT(ClaireType,member_type(v57724))) != CTRUE)
   { warn_void();
    if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
     mtformat_module1(Optimize.it,"`BLUE unsafe update on bag: type ~S into ~S [252]\n",2,list::alloc(2,_oid_(v57736),_oid_(v57724)));
    else ;}
  { OID Result = 0;
    Result = _oid_(v57736);
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * c_inline_ask_method(method *v61776,list *v48360)
{ GC_BIND;
  { ClaireBoolean *Result ;
    { lambda * v48354 = GC_OBJECT(lambda,v61776->formula);
      list * v57465 = GC_OBJECT(list,v48354->vars);
      OID  v48372 = GC_OID(v48354->body);
      CL_INT  v48362 = 1;
      { OID  v47938;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v48370);
          v47938= Kernel.cfalse;
          bag *v48370_support;
          v48370_support = GC_OBJECT(list,v48354->vars);
          for (START(v48370_support); NEXT(v48370);)
          if (((CL_INT)(*Kernel.occurrence)(v48372,
              v48370) > 1) && 
              ((designated_ask_any((*(v48360))[v48362]) != CTRUE) && 
                (inherit_ask_class(owner_any((*Kernel.range)(v48370)),Optimize._Pattern) != CTRUE)))
           { v47938 = Kernel.ctrue;
            ClEnv->cHandle = loop_handle;break;}
          else ++v48362;
            }
        Result = not_any(v47938);
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  inline_optimize_ask_Call(Call *v61776)
{ GC_BIND;
  { OID Result = 0;
    { list * v48360 = GC_OBJECT(list,v61776->args);
      OID  v48361;
      { { list * v48897;
          { { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID v48372; CL_INT CLcount;
              v_list = v48360;
               v48897 = v_list->clone();
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { v48372 = (*(v_list))[CLcount];
                v_val = _oid_(set::alloc(1,v48372));
                
                (*((list *) v48897))[CLcount] = v_val;}
              }
            GC_OBJECT(list,v48897);}
          v48361 = restriction_I_property(v61776->selector,v48897,CTRUE);
          }
        GC_OID(v48361);}
      if (Kernel._method == OWNER(v48361))
       { { ClaireBoolean * g1077I;
          { ClaireBoolean *v_and;
            { v_and = OBJECT(method,v48361)->inline_ask;
              if (v_and == CFALSE) g1077I =CFALSE; 
              else { { OID  v50819;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    ITERATE(v48367);
                    v50819= Kernel.cfalse;
                    for (START(OBJECT(restriction,v48361)->domain); NEXT(v48367);)
                    if (INHERIT(OBJECT(ClaireObject,v48367)->isa,Optimize._Pattern))
                     { v50819 = Kernel.ctrue;
                      ClEnv->cHandle = loop_handle;break;}
                    }
                  v_and = boolean_I_any(v50819);
                  }
                if (v_and == CFALSE) g1077I =CFALSE; 
                else { v_and = c_inline_ask_method(OBJECT(method,v48361),v48360);
                  if (v_and == CFALSE) g1077I =CFALSE; 
                  else g1077I = CTRUE;}
                }
              }
            }
          
          if (g1077I == CTRUE) Result = v48361;
            else Result = Kernel.cfalse;
          }
        }
      else Result = Kernel.cfalse;
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }



