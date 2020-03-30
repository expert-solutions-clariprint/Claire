/***** CLAIRE Compilation of file ./compile/odefine.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:48 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>
#include <Optimize.h>
ClaireType * c_type_List_Optimize(List *v61776)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
   mtformat_module1(Optimize.it,"call c_type with ~S -> ~S \n",5,list::alloc(2,_oid_(v61776),GC_OID(get_property(Kernel.of,v61776))));
  else ;{ ClaireType *Result ;
    if (((v61776->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     Result = param_I_class(Kernel._list,GC_OBJECT(ClaireType,v61776->of));
    else { OID  v44127 = _oid_(Kernel.emptySet);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v55287);
          bag *v55287_support;
          v55287_support = GC_OBJECT(list,v61776->args);
          for (START(v55287_support); NEXT(v55287);)
          { GC_LOOP;
            if (boolean_I_any(v44127) == CTRUE)
             GC__OID(v44127 = _oid_(meet_class(OBJECT(ClaireClass,v44127),class_I_type(GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v55287))))))), 1);
            else GC__OID(v44127 = _oid_(class_I_type(GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v55287)))))), 1);
              GC_UNLOOP; POP_SIGNAL;}
          }
        Result = nth_class1(Kernel._list,OBJECT(ClaireType,v44127));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_List_Optimize(List *v61776)
{ GC_BIND;
  (Optimize.OPT->allocation = CTRUE);
  { OID Result = 0;
    { List * v48372;
      { { List * v47292 = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
          { Construct * v27402 = v47292; 
            list * v27403;
            { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID v55287; CL_INT CLcount;
              v_list = GC_OBJECT(list,v61776->args);
               v27403 = v_list->clone();
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { v55287 = (*(v_list))[CLcount];
                v_val = c_gc_I_any2(GC_OID((*Optimize.c_code)(v55287,
                  _oid_(Kernel._any))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v55287))));
                
                (*((list *) v27403))[CLcount] = v_val;}
              }
            (v27402->args = v27403);}
          add_I_property(Kernel.instances,Language._List,11,_oid_(v47292));
          v48372 = v47292;
          }
        GC_OBJECT(List,v48372);}
      if (((v61776->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       { { ClaireBoolean * g1549I;
          { ClaireBoolean *v_or;
            { v_or = (((CL_INT)Optimize.compiler->safety > 4) ? CTRUE : CFALSE);
              if (v_or == CTRUE) g1549I =CTRUE; 
              else { v_or = ((equal(_oid_(v61776->of),_oid_(Kernel.emptySet)) == CTRUE) ? CTRUE : CFALSE);
                if (v_or == CTRUE) g1549I =CTRUE; 
                else { { OID  v13634;
                    { CL_INT loop_handle = ClEnv->cHandle;
                      OID gc_local;
                      ITERATE(v55287);
                      v13634= Kernel.cfalse;
                      bag *v55287_support;
                      v55287_support = GC_OBJECT(list,v61776->args);
                      for (START(v55287_support); NEXT(v55287);)
                      { GC_LOOP;
                        if (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v55287))),GC_OBJECT(ClaireType,v61776->of)) != CTRUE)
                         { v13634 = Kernel.ctrue;
                          ClEnv->cHandle = loop_handle;break;}
                        GC_UNLOOP; POP_SIGNAL;}
                      }
                    v_or = not_any(v13634);
                    }
                  if (v_or == CTRUE) g1549I =CTRUE; 
                  else g1549I = CFALSE;}
                }
              }
            }
          
          if (g1549I == CTRUE) { (v48372->of = v61776->of);
              Result = _oid_(v48372);
              }
            else { warn_void();
            if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
             { list * v14595;
              { { OID v_bag;
                  GC_ANY(v14595= list::empty(Kernel.emptySet));
                  { { list * v2999;{ CL_INT loop_handle = ClEnv->cHandle;
                        bag *v_list; OID v_val;
                        OID v55287; CL_INT CLcount;
                        v_list = GC_OBJECT(list,v61776->args);
                         v2999 = v_list->clone();
                        for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                        { v55287 = (*(v_list))[CLcount];
                          v_val = (*Optimize.c_type)(v55287);
                          
                          (*((list *) v2999))[CLcount] = v_val;}
                        }
                      
                      v_bag=_oid_(v2999);}
                    GC_OID(v_bag);}
                  ((list *) v14595)->addFast((OID)v_bag);
                  ((list *) v14595)->addFast((OID)GC_OID(_oid_(v61776->of)));}
                GC_OBJECT(list,v14595);}
              mtformat_module1(Optimize.it,"`BLUE unsafe typed list: ~S not in ~S [262]\n",2,v14595);
              }
            else ;{ OID  v16517;
              { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                (v47292->selector = Core.check_in);
                (v47292->args = list::alloc(3,_oid_(v48372),
                  _oid_(Kernel._list),
                  GC_OID(_oid_(v61776->of))));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                v16517 = _oid_(v47292);
                }
              Result = (*Optimize.c_code)(v16517,
                _oid_(Kernel._list));
              }
            }
          }
        }
      else Result = _oid_(v48372);
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Set_Optimize(Set *v61776)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
   mtformat_module1(Optimize.it,"call c_type with ~S -> ~S \n",5,list::alloc(2,_oid_(v61776),GC_OID(get_property(Kernel.of,v61776))));
  else ;{ ClaireType *Result ;
    if (((v61776->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     Result = param_I_class(Kernel._set,GC_OBJECT(ClaireType,v61776->of));
    else { OID  v44127 = _oid_(Kernel.emptySet);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v55287);
          bag *v55287_support;
          v55287_support = GC_OBJECT(list,v61776->args);
          for (START(v55287_support); NEXT(v55287);)
          { GC_LOOP;
            if (boolean_I_any(v44127) == CTRUE)
             GC__OID(v44127 = _oid_(meet_class(OBJECT(ClaireClass,v44127),class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v55287)))))), 1);
            else GC__OID(v44127 = _oid_(class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v55287))))), 1);
              GC_UNLOOP; POP_SIGNAL;}
          }
        Result = nth_class1(Kernel._set,OBJECT(ClaireType,v44127));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Set_Optimize(Set *v61776)
{ GC_BIND;
  (Optimize.OPT->allocation = CTRUE);
  { OID Result = 0;
    { Set * v48372;
      { { Set * v47292 = ((Set *) GC_OBJECT(Set,new_object_class(Language._Set)));
          { Construct * v27430 = v47292; 
            list * v27431;
            { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID v55287; CL_INT CLcount;
              v_list = GC_OBJECT(list,v61776->args);
               v27431 = v_list->clone();
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { v55287 = (*(v_list))[CLcount];
                v_val = c_gc_I_any2(GC_OID((*Optimize.c_code)(v55287,
                  _oid_(Kernel._any))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v55287))));
                
                (*((list *) v27431))[CLcount] = v_val;}
              }
            (v27430->args = v27431);}
          add_I_property(Kernel.instances,Language._Set,11,_oid_(v47292));
          v48372 = v47292;
          }
        GC_OBJECT(Set,v48372);}
      if (((v61776->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       { { ClaireBoolean * g1556I;
          { ClaireBoolean *v_or;
            { v_or = (((CL_INT)Optimize.compiler->safety > 4) ? CTRUE : CFALSE);
              if (v_or == CTRUE) g1556I =CTRUE; 
              else { v_or = ((equal(_oid_(v61776->of),_oid_(Kernel.emptySet)) == CTRUE) ? CTRUE : CFALSE);
                if (v_or == CTRUE) g1556I =CTRUE; 
                else { { OID  v20361;
                    { CL_INT loop_handle = ClEnv->cHandle;
                      OID gc_local;
                      ITERATE(v55287);
                      v20361= Kernel.cfalse;
                      bag *v55287_support;
                      v55287_support = GC_OBJECT(list,v61776->args);
                      for (START(v55287_support); NEXT(v55287);)
                      { GC_LOOP;
                        if (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v55287))),GC_OBJECT(ClaireType,v61776->of)) != CTRUE)
                         { v20361 = Kernel.ctrue;
                          ClEnv->cHandle = loop_handle;break;}
                        GC_UNLOOP; POP_SIGNAL;}
                      }
                    v_or = not_any(v20361);
                    }
                  if (v_or == CTRUE) g1556I =CTRUE; 
                  else g1556I = CFALSE;}
                }
              }
            }
          
          if (g1556I == CTRUE) { (v48372->of = v61776->of);
              Result = _oid_(v48372);
              }
            else { warn_void();
            if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
             { list * v21322;
              { { OID v_bag;
                  GC_ANY(v21322= list::empty(Kernel.emptySet));
                  { { list * v3006;{ CL_INT loop_handle = ClEnv->cHandle;
                        bag *v_list; OID v_val;
                        OID v55287; CL_INT CLcount;
                        v_list = GC_OBJECT(list,v61776->args);
                         v3006 = v_list->clone();
                        for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                        { v55287 = (*(v_list))[CLcount];
                          v_val = (*Optimize.c_type)(v55287);
                          
                          (*((list *) v3006))[CLcount] = v_val;}
                        }
                      
                      v_bag=_oid_(v3006);}
                    GC_OID(v_bag);}
                  ((list *) v21322)->addFast((OID)v_bag);
                  ((list *) v21322)->addFast((OID)GC_OID(_oid_(v61776->of)));}
                GC_OBJECT(list,v21322);}
              mtformat_module1(Optimize.it,"`BLUE unsafe typed set: ~S not in ~S [262]\n",2,v21322);
              }
            else ;{ OID  v43425;
              { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                (v47292->selector = Core.check_in);
                (v47292->args = list::alloc(3,_oid_(v48372),
                  _oid_(Kernel._set),
                  GC_OID(_oid_(v61776->of))));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                v43425 = _oid_(v47292);
                }
              Result = (*Optimize.c_code)(v43425,
                _oid_(Kernel._set));
              }
            }
          }
        }
      else Result = _oid_(v48372);
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Tuple_Optimize(Tuple *v61776)
{ GC_BIND;
  { ClaireType *Result ;
    { list * v44386;
      { { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v48372; CL_INT CLcount;
          v_list = v61776->args;
           v44386 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v48372 = (*(v_list))[CLcount];
            v_val = (*Optimize.c_type)(v48372);
            
            (*((list *) v44386))[CLcount] = v_val;}
          }
        GC_OBJECT(list,v44386);}
      Result = tuple_I_list(v44386);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Tuple_Optimize(Tuple *v61776)
{ GC_BIND;
  (Optimize.OPT->allocation = CTRUE);
  { OID Result = 0;
    { Tuple * v47292 = ((Tuple *) GC_OBJECT(Tuple,new_object_class(Language._Tuple)));
      { Construct * v27459 = v47292; 
        list * v27460;
        { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v55287; CL_INT CLcount;
          v_list = GC_OBJECT(list,v61776->args);
           v27460 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v55287 = (*(v_list))[CLcount];
            v_val = c_gc_I_any2(GC_OID((*Optimize.c_code)(v55287,
              _oid_(Kernel._any))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v55287))));
            
            (*((list *) v27460))[CLcount] = v_val;}
          }
        (v27459->args = v27460);}
      add_I_property(Kernel.instances,Language._Tuple,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Definition_Optimize(Definition *v61776)
{ { ClaireType *Result ;
    if (_inf_equalt_class(v61776->arg,Kernel._exception) == CTRUE)
     Result = Kernel.emptySet;
    else Result = v61776->arg;
      POP_SIGNAL; return (Result);}
  }

OID  c_code_Definition_Optimize(Definition *v61776,ClaireClass *v48367)
{ GC_BIND;
  { OID Result = 0;
    { OID  v34702 = GC_OID(Optimize._starcall_star->value);
      ClaireClass * v55266 = v61776->arg;
      Variable * v55285;
      { { CL_INT  v48230;
          { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
            v48230 = 0;
            }
          v55285 = Variable_I_symbol(OBJECT(symbol,Optimize._starname_star->value),v48230,v55266);
          }
        GC_OBJECT(Variable,v55285);}
      OID  v55287 = GC_OID(total_ask_class(v55266,GC_OBJECT(list,v61776->args)));
      OID  v17948;
      { { (Optimize._starcall_star->value= _oid_(v61776));
          if ((CL_INT)v55266->open <= 0)
           close_exception(((general_error *) (*Core._general_error)(_string_("[105] cannot instantiate ~S"),
            _oid_(list::alloc(1,_oid_(v55266))))));
          if (boolean_I_any(v55287) == CTRUE)
           v17948 = (*Optimize.c_code)(v55287,
            _oid_(v48367));
          else { OID  v49191;
              { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                (v47292->var = v55285);
                { Let * v27464 = v47292; 
                  OID  v27465;
                  { Cast * v47292 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                    { Cast * v27466 = v47292; 
                      OID  v27488;
                      { OID  v8641;
                        { { OID  v9602;
                            { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                              (v47292->selector = Core.new_I);
                              (v47292->args = list::alloc(1,_oid_(v55266)));
                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                              v9602 = _oid_(v47292);
                              }
                            v8641 = (*Optimize.c_code)(v9602,
                              _oid_(Kernel._object));
                            }
                          GC_OID(v8641);}
                        v27488 = c_gc_I_any1(v8641);
                        }
                      (v27466->arg = v27488);}
                    (v47292->set_arg = v55266);
                    add_I_property(Kernel.instances,Language._Cast,11,_oid_(v47292));
                    v27465 = _oid_(v47292);
                    }
                  (v27464->value = v27465);}
                { Let * v27491 = v47292; 
                  OID  v27492;
                  { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                    store_object(v47292,
                      2,
                      Kernel._object,
                      analyze_I_class(v55266,_oid_(v55285),GC_OBJECT(list,v61776->args),list::empty()),
                      CFALSE);
                    add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                    v27492 = _oid_(v47292);
                    }
                  (v27491->arg = v27492);}
                add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                v49191 = _oid_(v47292);
                }
              v17948 = (*Optimize.c_code)(v49191,
                _oid_(v48367));
              }
            }
        GC_OID(v17948);}
      (Optimize._starcall_star->value= v34702);
      Result = v17948;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  total_ask_class(ClaireClass *v61776,list *v48360)
{ GC_BIND;
  { OID Result = 0;
    { list * v57480 = GC_OBJECT(list,OBJECT(list,(*Optimize.get_indexed)(_oid_(v61776))));
      CL_INT  v48362 = v57480->length;
      { ClaireBoolean * g1576I;
        { ClaireBoolean *v_and;
          { v_and = not_any(_oid_(Optimize.compiler->diet_ask));
            if (v_and == CFALSE) g1576I =CFALSE; 
            else { v_and = ((v48360->length == ((CL_INT)v48362-(CL_INT)1)) ? CTRUE : CFALSE);
              if (v_and == CFALSE) g1576I =CFALSE; 
              else { v_and = ((v61776->open == ClEnv->ephemeral) ? CTRUE : ((_inf_equalt_class(v61776,Kernel._exception) == CTRUE) ? CTRUE : CFALSE));
                if (v_and == CFALSE) g1576I =CFALSE; 
                else { v_and = (((CL_INT)v48362 <= 4) ? CTRUE : CFALSE);
                  if (v_and == CFALSE) g1576I =CFALSE; 
                  else { { OID  v14407;
                      { CL_INT  v48357 = 2;
                        CL_INT  v27493 = v48362;
                        { CL_INT loop_handle = ClEnv->cHandle;
                          v14407= _oid_(CFALSE);
                          while (((CL_INT)v48357 <= (CL_INT)v27493))
                          { if ((((*Kernel.srange)((*(v57480))[v48357]) == _oid_(Kernel._integer)) ? CTRUE : (((*Kernel.srange)((*(v57480))[v48357]) == _oid_(Kernel._any)) ? CTRUE : CFALSE)) != CTRUE)
                             { v14407 = Kernel.ctrue;
                              ClEnv->cHandle = loop_handle;break;}
                            ++v48357;
                            POP_SIGNAL;}
                          }
                        }
                      v_and = not_any(v14407);
                      }
                    if (v_and == CFALSE) g1576I =CFALSE; 
                    else g1576I = CTRUE;}
                  }
                }
              }
            }
          }
        
        if (g1576I == CTRUE) { OID  v55266;
            { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                (v47292->selector = ((v48360->length == 0) ?
                  Core.new_I :
                  Optimize.anyObject_I ));
                { Call * v27496 = v47292; 
                  list * v27497;
                  { list * v37471;
                    { { CL_INT loop_handle = ClEnv->cHandle;
                        bag *v_list; OID v_val;
                        OID v48372; CL_INT CLcount;
                        v_list = v48360;
                         v37471 = v_list->clone();
                        for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                        { v48372 = (*(v_list))[CLcount];
                          v_val = c_gc_I_any1(GC_OID((*Optimize.c_code)(GC_OID((*(OBJECT(bag,(*Core.args)(v48372))))[2]),
                            _oid_(Kernel._any))));
                          
                          (*((list *) v37471))[CLcount] = v_val;}
                        }
                      GC_OBJECT(list,v37471);}
                    v27497 = cons_any(_oid_(v61776),v37471);
                    }
                  (v27496->args = v27497);}
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                v55266 = _oid_(v47292);
                }
              GC_OID(v55266);}
            OID  v48361 = GC_OID(_oid_(_at_property1(Kernel.close,v61776)));
            if (_inf_equal_type(v61776,Kernel._exception) != CTRUE)
             (Optimize.OPT->allocation = CTRUE);
            if (v48360->length == 0)
             v55266= GC_OID((*Optimize.c_code)(v55266));
            if (boolean_I_any(v48361) == CTRUE)
             { Call_method1 * v3091;{ Call_method1 * v39393;
                { Call_method1 * v47292 = ((Call_method1 *) GC_OBJECT(Call_method1,new_object_class(Language._Call_method1)));
                  update_property(Kernel.arg,
                    v47292,
                    2,
                    Kernel._object,
                    v48361);
                  (v47292->args = list::alloc(1,v55266));
                  add_I_property(Kernel.instances,Language._Call_method1,11,_oid_(v47292));
                  v39393 = v47292;
                  }
                v3091 = loc_I_Call_method11(v39393);
                }
              
              Result=_oid_(v3091);}
            else Result = v55266;
              }
          else Result = Kernel.cfalse;
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  analyze_I_class(ClaireClass *v48351,OID v61776,list *v55275,list *v57480)
{ GC_RESERVE(15);  // v3.0.55 optim !
  { OID Result = 0;
    { ClaireBoolean * v34839 = ((v48351->open != ClEnv->ephemeral) ? ((boolean_I_any(_oid_(v57480)) != CTRUE) ? ((Optimize.compiler->class2file_ask != CTRUE) ? CTRUE: CFALSE): CFALSE): CFALSE);
      list * v48366;
      { { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v48372; CL_INT CLcount;
          v_list = v55275;
           v48366 = v_list->clone(Kernel._any);
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v48372 = (*(v_list))[CLcount];
            { OID  v48364 = GC_OID((*(OBJECT(Call,v48372)->args))[1]);
              OID  v48373 = GC_OID((*(OBJECT(Call,v48372)->args))[2]);
              ClaireObject * v48367 = GC_OBJECT(ClaireObject,_at_property1(OBJECT(property,v48364),v48351));
              ClaireBoolean * v22186 = (((*Kernel.open)(v48364) == ((OID)0)) ? ((Kernel._slot == v48367->isa) ? CTRUE: CFALSE): CFALSE);
              GC__ANY(v57480 = v57480->addFast((OID)v48364), 4);
              { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                (v47292->selector = ((v22186 == CTRUE) ?
                  Kernel.put :
                  Core.write ));
                { Call * v27523 = v47292; 
                  list * v27524;
                  { OID v_bag;
                    GC_ANY(v27524= list::empty(Kernel.emptySet));
                    ((list *) v27524)->addFast((OID)v48364);
                    ((list *) v27524)->addFast((OID)v61776);
                    { if ((v22186 != CTRUE) || 
                          (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v48373))),GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(_oid_(v48367))))) == CTRUE))
                       v_bag = v48373;
                      else v_bag = c_check_any(GC_OID((*Optimize.c_code)(v48373,
                          _oid_(Kernel._any))),GC_OID((*Optimize.c_code)(GC_OID((*Kernel.range)(_oid_(v48367))),
                          _oid_(Kernel._type))));
                        GC_OID(v_bag);}
                    ((list *) v27524)->addFast((OID)v_bag);}
                  (v27523->args = v27524);}
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                v_val = _oid_(v47292);
                }
              }
            
            (*((list *) v48366))[CLcount] = v_val;}
          }
        GC_OBJECT(list,v48366);}
      if (v34839 == CTRUE)
       { { OID  v42276;
          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            (v47292->selector = Kernel.add);
            (v47292->args = list::alloc(3,_oid_(Kernel.instances),
              _oid_(v48351),
              v61776));
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
            v42276 = _oid_(v47292);
            }
          v48366 = v48366->addFast((OID)v42276);
          }
        GC_OBJECT(list,v48366);}
      if (Optimize.compiler->class2file_ask != CTRUE)
       { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v48367);
        bag *v48367_support;
        v48367_support = GC_OBJECT(list,OBJECT(bag,(*Optimize.get_indexed)(_oid_(v48351))));
        for (START(v48367_support); NEXT(v48367);)
        { GC_LOOP;
          { property * v48364 = OBJECT(restriction,v48367)->selector;
            OID  v48370 = GC_OID(OBJECT(slot,v48367)->DEFAULT);
            { ClaireBoolean * g1586I;
              { ClaireBoolean *v_and;
                { v_and = known_ask_any(v48370);
                  if (v_and == CFALSE) g1586I =CFALSE; 
                  else { { OID  v44198;
                      if (multi_ask_any(_oid_(v48364)) == CTRUE)
                       v44198 = v48370;
                      else v44198 = Kernel.ctrue;
                        v_and = boolean_I_any(v44198);
                      }
                    if (v_and == CFALSE) g1586I =CFALSE; 
                    else { v_and = not_any(_oid_(v57480->memq(_oid_(v48364))));
                      if (v_and == CFALSE) g1586I =CFALSE; 
                      else { v_and = ((((v48364->inverse == (NULL)) ? CTRUE : CFALSE) != CTRUE) ? CTRUE : ((((v48364->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE) ? CTRUE : (((OBJECT(slot,v48367)->srange != Kernel._object) && 
                            ((OBJECT(slot,v48367)->srange != Kernel._float) && 
                              (inherit_ask_class(OWNER(v48370),Kernel._integer) != CTRUE))) ? CTRUE : CFALSE)));
                        if (v_and == CFALSE) g1586I =CFALSE; 
                        else g1586I = CTRUE;}
                      }
                    }
                  }
                }
              
              if (g1586I == CTRUE) { OID  v1244;
                  if (designated_ask_any(v48370) == CTRUE)
                   v1244 = v48370;
                  else { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      (v47292->selector = Kernel.DEFAULT);
                      { Call * v27528 = v47292; 
                        list * v27529;
                        { OID v_bag;
                          GC_ANY(v27529= list::empty(Kernel.emptySet));
                          { { Cast * v47292 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                              { Cast * v27551 = v47292; 
                                OID  v27552;
                                { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                  (v47292->selector = Core._at);
                                  (v47292->args = list::alloc(2,_oid_(v48364),_oid_(v48351)));
                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                  v27552 = _oid_(v47292);
                                  }
                                (v27551->arg = v27552);}
                              (v47292->set_arg = Kernel._slot);
                              add_I_property(Kernel.instances,Language._Cast,11,_oid_(v47292));
                              v_bag = _oid_(v47292);
                              }
                            GC_OID(v_bag);}
                          ((list *) v27529)->addFast((OID)v_bag);}
                        (v27528->args = v27529);}
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                      v1244 = _oid_(v47292);
                      }
                    { { OID  v3648;
                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        (v47292->selector = Core.write);
                        (v47292->args = list::alloc(3,_oid_(v48364),
                          v61776,
                          v1244));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                        v3648 = _oid_(v47292);
                        }
                      v48366 = v48366->addFast((OID)v3648);
                      }
                     GC__ANY(v48366, 7);}
                  }
                }
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      { OID  v48361 = GC_OID(_oid_(_at_property1(Kernel.close,v48351)));
        { OID  v4609;
          { if (boolean_I_any(v48361) == CTRUE)
             { Call_method1 * v3125;{ Call_method1 * v6531;
                { Call_method1 * v47292 = ((Call_method1 *) GC_OBJECT(Call_method1,new_object_class(Language._Call_method1)));
                  update_property(Kernel.arg,
                    v47292,
                    2,
                    Kernel._object,
                    v48361);
                  (v47292->args = list::alloc(1,v61776));
                  add_I_property(Kernel.instances,Language._Call_method1,11,_oid_(v47292));
                  v6531 = v47292;
                  }
                v3125 = loc_I_Call_method11(v6531);
                }
              
              v4609=_oid_(v3125);}
            else v4609 = v61776;
              GC_OID(v4609);}
          v48366 = v48366->addFast((OID)v4609);
          }
        }
      Result = _oid_(v48366);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Defobj_Optimize(Defobj *v61776,ClaireClass *v48367)
{ GC_BIND;
  { OID Result = 0;
    { ClaireBoolean * v55264 = Optimize.OPT->allocation;
      ClaireClass * v55266 = v61776->arg;
      OID  v48363 = get_symbol(v61776->ident);
      OID  v55285;
      { if ((v48363 != CNULL) && 
            (inherit_ask_class(OWNER(v48363),Core._global_variable) != CTRUE))
         v55285 = v48363;
        else { Variable * v3129;{ CL_INT  v10375;
              { (Optimize.OPT->max_vars = ((CL_INT)Optimize.OPT->max_vars+(CL_INT)1));
                v10375 = 0;
                }
              v3129 = Variable_I_symbol(OBJECT(symbol,Optimize._starname_star->value),v10375,v55266);
              }
            
            v55285=_oid_(v3129);}
          GC_OID(v55285);}
      Call * v10042;
      { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          (v47292->selector = Optimize.object_I);
          (v47292->args = list::alloc(2,_oid_(v61776->ident),_oid_(v55266)));
          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
          v10042 = v47292;
          }
        GC_OBJECT(Call,v10042);}
      OID  v10043 = GC_OID(analyze_I_class(v55266,v55285,GC_OBJECT(list,v61776->args),list::alloc(1,_oid_(Kernel.name))));
      OID  v55287;
      if (inherit_ask_class(OWNER(v55285),Language._Variable) != CTRUE)
       { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
        store_object(v47292,
          2,
          Kernel._object,
          (*Kernel.cons)(_oid_(v10042),
            v10043),
          CFALSE);
        add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
        v55287 = _oid_(v47292);
        }
      else { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
          store_object(v47292,
            2,
            Kernel._object,
            v55285,
            CFALSE);
          (v47292->value = _oid_(v10042));
          { Let * v28232 = v47292; 
            OID  v28233;
            { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
              store_object(v47292,
                2,
                Kernel._object,
                v10043,
                CFALSE);
              add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
              v28233 = _oid_(v47292);
              }
            (v28232->arg = v28233);}
          add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
          v55287 = _oid_(v47292);
          }
        if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
       mtformat_module1(Optimize.it,"compile defobj(~S) -> ~S \n",5,list::alloc(2,_oid_(v61776),v48363));
      else ;if ((CL_INT)v55266->open <= 0)
       close_exception(((general_error *) (*Core._general_error)(_string_("[105] cannot instantiate ~S"),
        _oid_(list::alloc(1,_oid_(v55266))))));
      if (v48363 != CNULL)
       { if (contain_ask_list(Optimize.OPT->objects,v48363) != CTRUE)
         { GC_OBJECT(list,Optimize.OPT->objects)->addFast((OID)v48363);
          (*Optimize.c_register)(v48363);
          }
        }
      else { warn_void();
          if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
           mtformat_module1(Optimize.it,"`BLUE ~S is unknown [265]\n",2,list::alloc(1,_oid_(v61776->ident)));
          else ;}
        v55287= GC_OID((*Optimize.c_code)(v55287,
        _oid_(v48367)));
      if (_inf_equal_type(v61776->arg,Kernel._exception) == CTRUE)
       (Optimize.OPT->allocation = v55264);
      Result = v55287;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  c_code_Defclass_Optimize(Defclass *v61776,ClaireClass *v48367)
{ GC_BIND;
  { OID Result = 0;
    { symbol * v65197 = v61776->ident;
      OID  v48363 = get_symbol(v65197);
      Call * v41181;
      { ClaireObject *V_CC ;
        if (v48363 != CNULL)
         { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          (v47292->selector = Core.class_I);
          (v47292->args = list::alloc(2,_oid_(v65197),_oid_(v61776->arg)));
          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
          V_CC = v47292;
          }
        else close_exception(((general_error *) (*Core._general_error)(_string_("[internal] cannot compile unknown class ~S"),
            _oid_(list::alloc(1,_oid_(v65197))))));
          v41181= (Call *) V_CC;}
      Do * v55287;
      { { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
          { Do * v28235 = v47292; 
            list * v28236;
            { list * v6573;
              { { list * v7534;
                  { { CL_INT loop_handle = ClEnv->cHandle;
                      bag *v_list; OID v_val;
                      OID v48372; CL_INT CLcount;
                      v_list = GC_OBJECT(list,v61776->args);
                       v7534 = v_list->clone();
                      for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                      { v48372 = (*(v_list))[CLcount];
                        { OID  v48370 = CNULL;
                          if (INHERIT(OWNER(v48372),Language._Call))
                           { v48370= GC_OID((*(OBJECT(Call,v48372)->args))[2]);
                            v48372= GC_OID((*(OBJECT(Call,v48372)->args))[1]);
                            }
                          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                            (v47292->selector = Kernel.add_slot);
                            (v47292->args = list::alloc(5,v48363,
                              _oid_(make_a_property_any(_oid_(OBJECT(Variable,v48372)->pname))),
                              GC_OID((*Kernel.range)(v48372)),
                              v48370,
                              ((OID)0)));
                            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                            v_val = _oid_(v47292);
                            }
                          }
                        
                        (*((list *) v7534))[CLcount] = v_val;}
                      }
                    GC_OBJECT(list,v7534);}
                  list * v8495;
                  if (v61776->params->length != 0)
                   { OID v_bag;
                    GC_ANY(v8495= list::empty(Kernel.emptySet));
                    { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        (v47292->selector = Kernel.put);
                        (v47292->args = list::alloc(3,_oid_(Kernel.params),
                          v48363,
                          GC_OID(_oid_(v61776->params))));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                        v_bag = _oid_(v47292);
                        }
                      GC_OID(v_bag);}
                    ((list *) v8495)->addFast((OID)v_bag);}
                  else v8495 = list::empty();
                    v6573 = append_list(v7534,v8495);
                  }
                GC_OBJECT(list,v6573);}
              v28236 = cons_any(_oid_(v41181),v6573);
              }
            (v28235->args = v28236);}
          add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
          v55287 = v47292;
          }
        GC_OBJECT(Do,v55287);}
      if (contain_ask_list(Optimize.OPT->objects,v48363) != CTRUE)
       { GC_OBJECT(list,Optimize.OPT->objects)->addFast((OID)v48363);
        (*Optimize.c_register)(v48363);
        }
      Result = (*Optimize.c_code)(_oid_(v55287),
        _oid_(v48367));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_Defmethod_Optimize(Defmethod *v61776)
{ POP_SIGNAL; return (Kernel._any);}

OID  c_code_Defmethod_Optimize(Defmethod *v61776)
{ GC_BIND;
  { OID Result = 0;
    { property * v57612 = v61776->arg->selector;
      list * v48360 = GC_OBJECT(list,v61776->arg->args);
      list * v57486 = (((v48360->length == 1) && 
          ((*(v48360))[1] == _oid_(ClEnv))) ?
        list::alloc(1,GC_OID(_oid_(Variable_I_symbol(OBJECT(symbol,Optimize._starname_star->value),0,Kernel._void)))) :
        v48360 );
      list * v57483 = GC_OBJECT(list,extract_signature_I_list(v57486));
      list * v19797 = GC_OBJECT(list,extract_range_any(GC_OID(v61776->set_arg),v57486,GC_OBJECT(list,OBJECT(list,Language.LDEF->value))));
      OID  v32219 = GC_OID((*Core._at)(_oid_(v57612),
        (*(v57483))[2]));
      method * v48361;
      { ClaireObject *V_CC ;
        if (Kernel._method == OBJECT(ClaireObject,v32219)->isa)
         V_CC = OBJECT(method,v32219);
        else close_exception(((general_error *) (*Core._general_error)(_string_("[internal] the method ~S @ ~S is not known"),
            _oid_(list::alloc(2,_oid_(v57612),(*(v57483))[2])))));
          v48361= (method *) V_CC;}
      OID  v60598;
      { if ((boolean_I_any(v61776->inline_ask) == CTRUE) && 
            (Optimize.compiler->inline_ask == CTRUE))
         { print_in_string_void();
          princ_string("lambda[(");
          ppvariable_list(v57486);
          princ_string("),");
          print_any(GC_OID(v61776->body));
          princ_string("]");
          v60598 = _string_(end_of_string_void());
          }
        else v60598 = Kernel.cfalse;
          GC_OID(v60598);}
      list * v17034 = GC_OBJECT(list,extract_status_new_any(GC_OID(v61776->body)));
      OID  v14640 = ((OID)v48361->status);
      ((*(v17034))[2]=GC_OID(get_property(Kernel.functional,v48361)));
      if ((Optimize.compiler->inline_ask != CTRUE) && 
          ((v57612 == Language.Iterate) || 
              (v57612 == Language.iterate)))
       Result = Core.nil->value;
      else if (((*(v19797))[1] == _oid_(Kernel._void)) && 
          (sort_pattern_ask_list(v57486,GC_OID(v61776->body)) == CTRUE))
       Result = sort_code_Defmethod(v61776,v57486);
      else { if ((*(v17034))[3] != _oid_(Kernel.body))
           { char * v57527 = GC_STRING(string_v((*Optimize.function_name)(_oid_(v57612),
              (*(v57483))[2],
              (*(v17034))[2])));
            lambda * v57465 = GC_OBJECT(lambda,lambda_I_list(v57486,(*(v17034))[3]));
            CL_INT  v44247 = ((Optimize.OPT->recompute == CTRUE) ?
              c_status_any(GC_OID(v57465->body),GC_OBJECT(list,v57465->vars)) :
              status_I_restriction(v48361) );
            compile_lambda_string(v57527,v57465,_oid_(v48361));
            if (((*(v17034))[1] == CNULL) || 
                (Optimize.OPT->recompute == CTRUE))
             { if ((Optimize.OPT->use_nth_equal != CTRUE) && 
                  (BCONTAIN(v44247,(OID)(2))))
               v44247= ((CL_INT)v44247-(CL_INT)exp2_integer(2));
              if ((Optimize.OPT->use_update != CTRUE) && 
                  (BCONTAIN(v44247,(OID)(3))))
               v44247= ((CL_INT)v44247-(CL_INT)exp2_integer(3));
              if ((Optimize.OPT->allocation != CTRUE) && 
                  (BCONTAIN(v44247,(OID)(1))))
               v44247= ((CL_INT)v44247-(CL_INT)exp2_integer(1));
              if (should_trace_ask_module1(Optimize.it,4) == CTRUE)
               mtformat_module1(Optimize.it,"---- CHANGE: status(~S)= ~S to ~S\n",4,list::alloc(3,_oid_(v48361),
                v14640,
                ((OID)v44247)));
              else ;((*(v17034))[1]=((OID)v44247));
              }
            ((*(v17034))[2]=_oid_(make_function_string(v57527)));
            }
          if (INHERIT(OWNER(v61776->set_arg),Core._global_variable))
           ((*(v19797))[1]=GC_OID(v61776->set_arg));
          else if ((INHERIT(v48361->range->isa,Kernel._class)) && 
              (inherit_ask_class(OWNER((*(v19797))[1]),Kernel._class) != CTRUE))
           ((*(v19797))[1]=_oid_(v48361->range));
          { OID  v55277 = GC_OID(add_method_I_method(v48361,
              OBJECT(list,(*(v57483))[1]),
              (*(v19797))[1],
              (*(v17034))[1],
              OBJECT(ClaireFunction,(*(v17034))[2])));
            { OID  v9456;
              if ((boolean_I_any(v61776->inline_ask) == CTRUE) && 
                  ((Optimize.compiler->inline_ask == CTRUE) && 
                    (Optimize.compiler->diet_ask != CTRUE)))
               { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                (v47292->selector = Core.inlineok_ask);
                (v47292->args = list::alloc(2,v55277,v60598));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                v9456 = _oid_(v47292);
                }
              else if ((Optimize.compiler->debug_ask->memq(_oid_(v48361->module_I)) == CTRUE) && 
                  (((v48361->formula == (NULL)) ? CTRUE : CFALSE) != CTRUE))
               { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                (v47292->selector = Core.write);
                { Call * v28241 = v47292; 
                  list * v28263;
                  { OID v_bag;
                    GC_ANY(v28263= list::empty(Kernel.emptySet));
                    ((list *) v28263)->addFast((OID)_oid_(Kernel.compiled_variables));
                    ((list *) v28263)->addFast((OID)v55277);
                    { { list * v3835;{ CL_INT loop_handle = ClEnv->cHandle;
                          bag *v_list; OID v_val;
                          OID v48370; CL_INT CLcount;
                          v_list = GC_OBJECT(list,OBJECT(bag,Optimize._stardebug_build_star->value));
                           v3835 = v_list->clone();
                          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                          { v48370 = (*(v_list))[CLcount];
                            if (INHERIT(OWNER(v48370),Language._Variable))
                             v_val = _string_(OBJECT(Variable,v48370)->pname->name);
                            else v_val = _string_("");
                              
                            (*((list *) v3835))[CLcount] = v_val;}
                          }
                        
                        v_bag=_oid_(v3835);}
                      GC_OID(v_bag);}
                    ((list *) v28263)->addFast((OID)v_bag);}
                  (v28241->args = v28263);}
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                v9456 = _oid_(v47292);
                }
              else if ((boolean_I_any((*(v19797))[2]) == CTRUE) && 
                  (Optimize.compiler->diet_ask != CTRUE))
               { char * v57527 = GC_STRING(append_string(GC_STRING(string_v((*Optimize.function_name)(_oid_(v57612),
                  (*(v57483))[2],
                  (*(v17034))[2]))),"_type"));
                compile_lambda_string(v57527,OBJECT(lambda,(*(v19797))[2]),_oid_(Kernel._type));
                { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  (v47292->selector = Core.write);
                  (v47292->args = list::alloc(3,Language.typing->value,
                    v55277,
                    _oid_(make_function_string(v57527))));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                  v9456 = _oid_(v47292);
                  }
                }
              else v9456 = v55277;
                Result = (*Optimize.c_code)(v9456);
              }
            }
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * sort_pattern_ask_list(list *v57486,OID v48579)
{ GC_BIND;
  { ClaireBoolean *Result ;
    { ClaireBoolean *v_and;
      { v_and = ((v57486->length == 1) ? CTRUE : CFALSE);
        if (v_and == CFALSE) Result =CFALSE; 
        else { if (INHERIT(OWNER(v48579),Language._Call))
           { ClaireBoolean *v_and1;
            { v_and1 = ((OBJECT(Call,v48579)->selector == Core.sort) ? CTRUE : CFALSE);
              if (v_and1 == CFALSE) v_and =CFALSE; 
              else { { OID  v57076 = GC_OID((*(OBJECT(Call,v48579)->args))[1]);
                  v_and1 = ((INHERIT(OWNER(v57076),Language._Call)) ?
                    ((OBJECT(Call,v57076)->selector == Core._at) ? ((INHERIT(OWNER((*(OBJECT(Call,v57076)->args))[1]),Kernel._property)) ? CTRUE: CFALSE): CFALSE) :
                    CFALSE );
                  }
                if (v_and1 == CFALSE) v_and =CFALSE; 
                else { v_and1 = ((equal(lexical_build_any(GC_OID((*(OBJECT(Call,v48579)->args))[2]),v57486,0),(*(v57486))[1]) == CTRUE) ? CTRUE : CFALSE);
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

OID  sort_code_Defmethod(Defmethod *v61776,list *v57486)
{ GC_BIND;
  { OID Result = 0;
    { OID  v48360 = (*(v57486))[1];
      OID  v48354 = GC_OID((*(OBJECT(bag,(*Core.args)(GC_OID((*(OBJECT(bag,(*Core.args)(GC_OID(v61776->body)))))[1])))))[1]);
      Variable * v48361 = GC_OBJECT(Variable,Variable_I_symbol(symbol_I_string2("m"),0,Kernel._integer));
      Variable * v48362 = GC_OBJECT(Variable,Variable_I_symbol(symbol_I_string2("n"),0,Kernel._integer));
      Variable * v48372 = GC_OBJECT(Variable,Variable_I_symbol(symbol_I_string2("x"),0,GC_OBJECT(ClaireType,member_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(v48360)))))));
      Variable * v48364 = GC_OBJECT(Variable,Variable_I_symbol(symbol_I_string2("p"),0,Kernel._integer));
      Variable * v33005 = GC_OBJECT(Variable,Variable_I_symbol(symbol_I_string2("q"),0,Kernel._integer));
      Defmethod * v7888;
      { { Defmethod * v47292 = ((Defmethod *) GC_OBJECT(Defmethod,new_object_class(Language._Defmethod)));
          (v47292->arg = v61776->arg);
          (v47292->inline_ask = Kernel.cfalse);
          (v47292->set_arg = v61776->set_arg);
          { Defmethod * v28265 = v47292; 
            OID  v28266;
            { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (v47292->selector = v61776->arg->selector);
              { Call * v28267 = v47292; 
                list * v28268;
                { OID v_bag;
                  GC_ANY(v28268= list::empty(Kernel.emptySet));
                  ((list *) v28268)->addFast((OID)((OID)1));
                  { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      (v47292->selector = Kernel.length);
                      (v47292->args = list::alloc(1,(*(v57486))[1]));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                      v_bag = _oid_(v47292);
                      }
                    GC_OID(v_bag);}
                  ((list *) v28268)->addFast((OID)v_bag);
                  ((list *) v28268)->addFast((OID)v48360);}
                (v28267->args = v28268);}
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
              v28266 = _oid_(v47292);
              }
            (v28265->body = v28266);}
          add_I_property(Kernel.instances,Language._Defmethod,11,_oid_(v47292));
          v7888 = v47292;
          }
        GC_OBJECT(Defmethod,v7888);}
      If * v9379;
      { { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
          { If * v28269 = v47292; 
            OID  v28271;
            { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (v47292->selector = Kernel._sup);
              (v47292->args = list::alloc(2,_oid_(v48361),_oid_(v48362)));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
              v28271 = _oid_(v47292);
              }
            (v28269->test = v28271);}
          { If * v28272 = v47292; 
            OID  v28273;
            { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
              (v47292->var = v48372);
              { Let * v28294 = v47292; 
                OID  v28295;
                { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  (v47292->selector = Kernel.nth);
                  (v47292->args = list::alloc(2,v48360,_oid_(v48362)));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                  v28295 = _oid_(v47292);
                  }
                (v28294->value = v28295);}
              { Let * v28296 = v47292; 
                OID  v28297;
                { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                  { If * v28298 = v47292; 
                    OID  v28299;
                    { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      (v47292->selector = Kernel._equal);
                      { Call * v28300 = v47292; 
                        list * v28301;
                        { OID v_bag;
                          GC_ANY(v28301= list::empty(Kernel.emptySet));
                          ((list *) v28301)->addFast((OID)_oid_(v48361));
                          { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                              (v47292->selector = Core._plus);
                              (v47292->args = list::alloc(2,_oid_(v48362),((OID)1)));
                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                              v_bag = _oid_(v47292);
                              }
                            GC_OID(v_bag);}
                          ((list *) v28301)->addFast((OID)v_bag);}
                        (v28300->args = v28301);}
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                      v28299 = _oid_(v47292);
                      }
                    (v28298->test = v28299);}
                  { If * v28302 = v47292; 
                    OID  v28303;
                    { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                      { If * v28325 = v47292; 
                        OID  v28326;
                        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          update_property(Kernel.selector,
                            v47292,
                            2,
                            Kernel._object,
                            v48354);
                          { Call * v28327 = v47292; 
                            list * v28328;
                            { OID v_bag;
                              GC_ANY(v28328= list::empty(Kernel.emptySet));
                              { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                  (v47292->selector = Kernel.nth);
                                  (v47292->args = list::alloc(2,v48360,_oid_(v48361)));
                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                  v_bag = _oid_(v47292);
                                  }
                                GC_OID(v_bag);}
                              ((list *) v28328)->addFast((OID)v_bag);
                              ((list *) v28328)->addFast((OID)_oid_(v48372));}
                            (v28327->args = v28328);}
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                          v28326 = _oid_(v47292);
                          }
                        (v28325->test = v28326);}
                      { If * v28329 = v47292; 
                        OID  v28330;
                        { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                          { Do * v28331 = v47292; 
                            list * v28332;
                            { OID v_bag;
                              GC_ANY(v28332= list::empty(Kernel.emptySet));
                              { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                  (v47292->selector = Kernel.nth_equal);
                                  { Call * v28333 = v47292; 
                                    list * v28334;
                                    { OID v_bag;
                                      GC_ANY(v28334= list::empty(Kernel.emptySet));
                                      ((list *) v28334)->addFast((OID)v48360);
                                      ((list *) v28334)->addFast((OID)_oid_(v48362));
                                      { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                          (v47292->selector = Kernel.nth);
                                          (v47292->args = list::alloc(2,v48360,_oid_(v48361)));
                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                          v_bag = _oid_(v47292);
                                          }
                                        GC_OID(v_bag);}
                                      ((list *) v28334)->addFast((OID)v_bag);}
                                    (v28333->args = v28334);}
                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                  v_bag = _oid_(v47292);
                                  }
                                GC_OID(v_bag);}
                              ((list *) v28332)->addFast((OID)v_bag);
                              { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                  (v47292->selector = Kernel.nth_equal);
                                  (v47292->args = list::alloc(3,v48360,
                                    _oid_(v48361),
                                    _oid_(v48372)));
                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                  v_bag = _oid_(v47292);
                                  }
                                GC_OID(v_bag);}
                              ((list *) v28332)->addFast((OID)v_bag);}
                            (v28331->args = v28332);}
                          add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                          v28330 = _oid_(v47292);
                          }
                        (v28329->arg = v28330);}
                      add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                      (v47292->other = Kernel.cfalse);
                      v28303 = _oid_(v47292);
                      }
                    (v28302->arg = v28303);}
                  { If * v28356 = v47292; 
                    OID  v28357;
                    { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                      (v47292->var = v48364);
                      { Let * v28358 = v47292; 
                        OID  v28359;
                        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          (v47292->selector = Core._sup_sup);
                          { Call * v28360 = v47292; 
                            list * v28361;
                            { OID v_bag;
                              GC_ANY(v28361= list::empty(Kernel.emptySet));
                              { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                  (v47292->selector = Core._plus);
                                  (v47292->args = list::alloc(2,_oid_(v48362),_oid_(v48361)));
                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                  v_bag = _oid_(v47292);
                                  }
                                GC_OID(v_bag);}
                              ((list *) v28361)->addFast((OID)v_bag);
                              ((list *) v28361)->addFast((OID)((OID)1));}
                            (v28360->args = v28361);}
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                          v28359 = _oid_(v47292);
                          }
                        (v28358->value = v28359);}
                      { Let * v28362 = v47292; 
                        OID  v28363;
                        { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                          (v47292->var = v33005);
                          (v47292->value = _oid_(v48362));
                          { Let * v28364 = v47292; 
                            OID  v28365;
                            { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                              { Do * v28387 = v47292; 
                                list * v28388;
                                { OID v_bag;
                                  GC_ANY(v28388= list::empty(Kernel.emptySet));
                                  { { Assign * v47292 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                      (v47292->var = _oid_(v48372));
                                      { Assign * v28389 = v47292; 
                                        OID  v28390;
                                        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                          (v47292->selector = Kernel.nth);
                                          (v47292->args = list::alloc(2,v48360,_oid_(v48364)));
                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                          v28390 = _oid_(v47292);
                                          }
                                        (v28389->arg = v28390);}
                                      add_I_property(Kernel.instances,Language._Assign,11,_oid_(v47292));
                                      v_bag = _oid_(v47292);
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v28388)->addFast((OID)v_bag);
                                  { { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                      { If * v28392 = v47292; 
                                        OID  v28393;
                                        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                          (v47292->selector = Core._I_equal);
                                          (v47292->args = list::alloc(2,_oid_(v48364),_oid_(v48362)));
                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                          v28393 = _oid_(v47292);
                                          }
                                        (v28392->test = v28393);}
                                      { If * v28394 = v47292; 
                                        OID  v28395;
                                        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                          (v47292->selector = Kernel.nth_equal);
                                          { Call * v28396 = v47292; 
                                            list * v28397;
                                            { OID v_bag;
                                              GC_ANY(v28397= list::empty(Kernel.emptySet));
                                              ((list *) v28397)->addFast((OID)v48360);
                                              ((list *) v28397)->addFast((OID)_oid_(v48364));
                                              { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                  (v47292->selector = Kernel.nth);
                                                  (v47292->args = list::alloc(2,v48360,_oid_(v48362)));
                                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                  v_bag = _oid_(v47292);
                                                  }
                                                GC_OID(v_bag);}
                                              ((list *) v28397)->addFast((OID)v_bag);}
                                            (v28396->args = v28397);}
                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                          v28395 = _oid_(v47292);
                                          }
                                        (v28394->arg = v28395);}
                                      add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                                      (v47292->other = Kernel.cfalse);
                                      v_bag = _oid_(v47292);
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v28388)->addFast((OID)v_bag);
                                  { { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                                      (v47292->var = v48364);
                                      { Iteration * v28418 = v47292; 
                                        OID  v28419;
                                        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                          (v47292->selector = Kernel._dot_dot);
                                          { Call * v28420 = v47292; 
                                            list * v28421;
                                            { OID v_bag;
                                              GC_ANY(v28421= list::empty(Kernel.emptySet));
                                              { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                  (v47292->selector = Core._plus);
                                                  (v47292->args = list::alloc(2,_oid_(v48362),((OID)1)));
                                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                  v_bag = _oid_(v47292);
                                                  }
                                                GC_OID(v_bag);}
                                              ((list *) v28421)->addFast((OID)v_bag);
                                              ((list *) v28421)->addFast((OID)_oid_(v48361));}
                                            (v28420->args = v28421);}
                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                          v28419 = _oid_(v47292);
                                          }
                                        (v28418->set_arg = v28419);}
                                      { Iteration * v28422 = v47292; 
                                        OID  v28423;
                                        { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                          { If * v28424 = v47292; 
                                            OID  v28425;
                                            { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                              update_property(Kernel.selector,
                                                v47292,
                                                2,
                                                Kernel._object,
                                                v48354);
                                              { Call * v28426 = v47292; 
                                                list * v28427;
                                                { OID v_bag;
                                                  GC_ANY(v28427= list::empty(Kernel.emptySet));
                                                  { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                      (v47292->selector = Kernel.nth);
                                                      (v47292->args = list::alloc(2,v48360,_oid_(v48364)));
                                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                      v_bag = _oid_(v47292);
                                                      }
                                                    GC_OID(v_bag);}
                                                  ((list *) v28427)->addFast((OID)v_bag);
                                                  ((list *) v28427)->addFast((OID)_oid_(v48372));}
                                                (v28426->args = v28427);}
                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                              v28425 = _oid_(v47292);
                                              }
                                            (v28424->test = v28425);}
                                          { If * v28449 = v47292; 
                                            OID  v28450;
                                            { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                              { Do * v28451 = v47292; 
                                                list * v28452;
                                                { OID v_bag;
                                                  GC_ANY(v28452= list::empty(Kernel.emptySet));
                                                  { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                      (v47292->selector = Kernel.nth_equal);
                                                      { Call * v28453 = v47292; 
                                                        list * v28454;
                                                        { OID v_bag;
                                                          GC_ANY(v28454= list::empty(Kernel.emptySet));
                                                          ((list *) v28454)->addFast((OID)v48360);
                                                          ((list *) v28454)->addFast((OID)_oid_(v48362));
                                                          { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                              (v47292->selector = Kernel.nth);
                                                              (v47292->args = list::alloc(2,v48360,_oid_(v48364)));
                                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                              v_bag = _oid_(v47292);
                                                              }
                                                            GC_OID(v_bag);}
                                                          ((list *) v28454)->addFast((OID)v_bag);}
                                                        (v28453->args = v28454);}
                                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                      v_bag = _oid_(v47292);
                                                      }
                                                    GC_OID(v_bag);}
                                                  ((list *) v28452)->addFast((OID)v_bag);
                                                  { { Assign * v47292 = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                                      (v47292->var = _oid_(v48362));
                                                      { Assign * v28455 = v47292; 
                                                        OID  v28456;
                                                        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                          (v47292->selector = Core._plus);
                                                          (v47292->args = list::alloc(2,_oid_(v48362),((OID)1)));
                                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                          v28456 = _oid_(v47292);
                                                          }
                                                        (v28455->arg = v28456);}
                                                      add_I_property(Kernel.instances,Language._Assign,11,_oid_(v47292));
                                                      v_bag = _oid_(v47292);
                                                      }
                                                    GC_OID(v_bag);}
                                                  ((list *) v28452)->addFast((OID)v_bag);
                                                  { { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                                                      { If * v28457 = v47292; 
                                                        OID  v28458;
                                                        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                          (v47292->selector = Kernel._sup);
                                                          (v47292->args = list::alloc(2,_oid_(v48364),_oid_(v48362)));
                                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                          v28458 = _oid_(v47292);
                                                          }
                                                        (v28457->test = v28458);}
                                                      { If * v28480 = v47292; 
                                                        OID  v28481;
                                                        { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                          (v47292->selector = Kernel.nth_equal);
                                                          { Call * v28482 = v47292; 
                                                            list * v28483;
                                                            { OID v_bag;
                                                              GC_ANY(v28483= list::empty(Kernel.emptySet));
                                                              ((list *) v28483)->addFast((OID)v48360);
                                                              ((list *) v28483)->addFast((OID)_oid_(v48364));
                                                              { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                                                  (v47292->selector = Kernel.nth);
                                                                  (v47292->args = list::alloc(2,v48360,_oid_(v48362)));
                                                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                                  v_bag = _oid_(v47292);
                                                                  }
                                                                GC_OID(v_bag);}
                                                              ((list *) v28483)->addFast((OID)v_bag);}
                                                            (v28482->args = v28483);}
                                                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                                          v28481 = _oid_(v47292);
                                                          }
                                                        (v28480->arg = v28481);}
                                                      add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                                                      (v47292->other = Kernel.cfalse);
                                                      v_bag = _oid_(v47292);
                                                      }
                                                    GC_OID(v_bag);}
                                                  ((list *) v28452)->addFast((OID)v_bag);}
                                                (v28451->args = v28452);}
                                              add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                                              v28450 = _oid_(v47292);
                                              }
                                            (v28449->arg = v28450);}
                                          add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                                          (v47292->other = Kernel.cfalse);
                                          v28423 = _oid_(v47292);
                                          }
                                        (v28422->arg = v28423);}
                                      add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
                                      v_bag = _oid_(v47292);
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v28388)->addFast((OID)v_bag);
                                  { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                      (v47292->selector = Kernel.nth_equal);
                                      (v47292->args = list::alloc(3,v48360,
                                        _oid_(v48362),
                                        _oid_(v48372)));
                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                      v_bag = _oid_(v47292);
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v28388)->addFast((OID)v_bag);
                                  { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                      (v47292->selector = v61776->arg->selector);
                                      { Call * v28484 = v47292; 
                                        list * v28485;
                                        { OID v_bag;
                                          GC_ANY(v28485= list::empty(Kernel.emptySet));
                                          ((list *) v28485)->addFast((OID)_oid_(v33005));
                                          { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                              (v47292->selector = Kernel._dash);
                                              (v47292->args = list::alloc(2,_oid_(v48362),((OID)1)));
                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                              v_bag = _oid_(v47292);
                                              }
                                            GC_OID(v_bag);}
                                          ((list *) v28485)->addFast((OID)v_bag);
                                          ((list *) v28485)->addFast((OID)v48360);}
                                        (v28484->args = v28485);}
                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                      v_bag = _oid_(v47292);
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v28388)->addFast((OID)v_bag);
                                  { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                      (v47292->selector = v61776->arg->selector);
                                      { Call * v28486 = v47292; 
                                        list * v28487;
                                        { OID v_bag;
                                          GC_ANY(v28487= list::empty(Kernel.emptySet));
                                          { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                              (v47292->selector = Core._plus);
                                              (v47292->args = list::alloc(2,_oid_(v48362),((OID)1)));
                                              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                              v_bag = _oid_(v47292);
                                              }
                                            GC_OID(v_bag);}
                                          ((list *) v28487)->addFast((OID)v_bag);
                                          ((list *) v28487)->addFast((OID)_oid_(v48361));
                                          ((list *) v28487)->addFast((OID)v48360);}
                                        (v28486->args = v28487);}
                                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                                      v_bag = _oid_(v47292);
                                      }
                                    GC_OID(v_bag);}
                                  ((list *) v28388)->addFast((OID)v_bag);}
                                (v28387->args = v28388);}
                              add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                              v28365 = _oid_(v47292);
                              }
                            (v28364->arg = v28365);}
                          add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                          v28363 = _oid_(v47292);
                          }
                        (v28362->arg = v28363);}
                      add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                      v28357 = _oid_(v47292);
                      }
                    (v28356->other = v28357);}
                  add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                  v28297 = _oid_(v47292);
                  }
                (v28296->arg = v28297);}
              add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
              v28273 = _oid_(v47292);
              }
            (v28272->arg = v28273);}
          add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
          (v47292->other = Kernel.cfalse);
          v9379 = v47292;
          }
        GC_OBJECT(If,v9379);}
      Defmethod * v7889;
      { { Defmethod * v47292 = ((Defmethod *) GC_OBJECT(Defmethod,new_object_class(Language._Defmethod)));
          { Defmethod * v28488 = v47292; 
            Call * v28489;
            { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (v47292->selector = v61776->arg->selector);
              (v47292->args = list::alloc(3,_oid_(v48362),
                _oid_(v48361),
                v48360));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
              v28489 = v47292;
              }
            (v28488->arg = v28489);}
          (v47292->inline_ask = Kernel.cfalse);
          (v47292->set_arg = v61776->set_arg);
          (v47292->body = _oid_(v9379));
          add_I_property(Kernel.instances,Language._Defmethod,11,_oid_(v47292));
          v7889 = v47292;
          }
        GC_OBJECT(Defmethod,v7889);}
      if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
       mtformat_module1(Optimize.it,"`GREEN ---- note: quick sort optimisation for ~S ---- \n",2,list::alloc(1,_oid_(v61776->arg->selector)));
      else ;OPT_EVAL(_oid_(v7889));
      { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
        (v47292->args = list::alloc(2,GC_OID((*Optimize.c_code)(_oid_(v7888))),GC_OID((*Optimize.c_code)(_oid_(v7889)))));
        add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
        Result = _oid_(v47292);
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

method * add_method_property2(property *v48364,list *v57483,ClaireType *v57657,int v57701,ClaireFunction *v57231,ClaireFunction *v57232)
{ POP_SIGNAL; return (add_method_property(v48364,
    v57483,
    v57657,
    ((OID)v57701),
    _oid_(v57231)));}

OID  add_method_I_method(method *v48361,list *v57483,OID v57657,OID v58456,ClaireFunction *v57299)
{ GC_BIND;
  { OID Result = 0;
    { Call_method * v55266;
      { { Call_method * v47292 = ((Call_method *) GC_OBJECT(Call_method,new_object_class(Language._Call_method)));
          (v47292->arg = ((method *) _at_property1(Kernel.add_method,Kernel._property)));
          (v47292->args = list::alloc(5,GC_OID((*Optimize.c_code)(_oid_(v48361->selector),
              _oid_(Kernel._property))),
            GC_OID((*Optimize.c_code)(_oid_(v57483),
              _oid_(Kernel._list))),
            GC_OID((*Optimize.c_code)(v57657,
              _oid_(Kernel._type))),
            v58456,
            _oid_(v57299)));
          add_I_property(Kernel.instances,Language._Call_method,11,_oid_(v47292));
          v55266 = v47292;
          }
        GC_OBJECT(Call_method,v55266);}
      if ((v48361->range == Kernel._float) || 
          ((v48361->domain->memq(_oid_(Kernel._float)) == CTRUE) || 
            (INHERIT(v48361->range->isa,Kernel._tuple))))
       GC_OBJECT(list,v55266->args)->addFast((OID)_oid_(make_function_string(append_string(string_I_function(v57299),"_"))));
      Result = _oid_(v55266);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

list * extract_status_new_any(OID v48372)
{ GC_BIND;
  { list *Result ;
    { OID  v48367 = CNULL;
      OID  v48354;
      if ((INHERIT(OWNER(v48372),Language._Call)) && (OBJECT(Call,v48372)->selector == Language.function_I))
       v48354 = v48372;
      else v48354 = CNULL;
        if (INHERIT(OWNER(v48372),Language._And))
       { OID  v48373 = GC_OID((*(OBJECT(And,v48372)->args))[1]);
        if ((INHERIT(OWNER(v48373),Language._Call)) && (OBJECT(Call,v48373)->selector == Language.function_I))
         { v48354= v48373;
          v48372= GC_OID((*(OBJECT(And,v48372)->args))[2]);
          }
        }
      else if (INHERIT(OWNER(v48372),Language._Call))
       { if (OBJECT(Call,v48372)->selector == Language.function_I)
         v48372= _oid_(Kernel.body);
        }
      if (v48354 != CNULL)
       { v48372= _oid_(Kernel.body);
        if ((CL_INT)length_bag(OBJECT(bag,(*Core.args)(v48354))) > 1)
         { ClaireHandler c_handle = ClaireHandler();
          if ERROR_IN 
          { { CL_INT  v4083;{ set * v9665;
                { set * v34746 = set::empty(Kernel.emptySet);
                  { CL_INT loop_handle = ClEnv->cHandle;
                    OID gc_local;
                    ITERATE(v48369);
                    bag *v48369_support;
                    v48369_support = GC_OBJECT(list,cdr_list(GC_OBJECT(list,OBJECT(list,(*Core.args)(v48354)))));
                    for (START(v48369_support); NEXT(v48369);)
                    { GC_LOOP;
                      v34746->addFast((OID)GC_OID(OPT_EVAL(v48369)));
                      GC_UNLOOP; POP_SIGNAL;}
                    }
                  v9665 = GC_OBJECT(set,v34746);
                  }
                v4083 = integer_I_set(v9665);
                }
              
              v48367=((OID)v4083);}
            ERROR_FREE;}
          else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
          { c_handle.catchIt();{ warn_void();
              (Optimize.SHIT->value= _oid_(cdr_list(GC_OBJECT(list,OBJECT(list,(*Core.args)(v48354))))));
              if (should_trace_ask_module1(Optimize.it,2) == CTRUE)
               mtformat_module1(Optimize.it,"`BLUE wrong status ~S -> ~S [266]\n",2,GC_OBJECT(list,list::alloc(2,v48354,_oid_(set_I_bag(cdr_list(GC_OBJECT(list,OBJECT(list,(*Core.args)(v48354)))))))));
              else ;v48367= ((OID)0);
              }
            }
          else PREVIOUS_HANDLER;}
        else v48367= ((OID)0);
          v48354= _oid_(make_function_string(string_I_symbol(extract_symbol_any((*(OBJECT(bag,(*Core.args)(v48354))))[1]))));
        }
      Result = list::alloc(3,v48367,
        v48354,
        v48372);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

list * extract_signature_I_list(list *v48360)
{ GC_BIND;
  (Language.LDEF->value= _oid_(list::empty(Kernel._any)));
  { list *Result ;
    { CL_INT  v48362 = 0;
      list * v57417 = list::empty(Kernel._type);
      list * v57419;
      { { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v48370; CL_INT CLcount;
          v_list = v48360;
           v57419 = v_list->clone(Kernel._any);
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v48370 = (*(v_list))[CLcount];
            { OID  v48364 = GC_OID(extract_pattern_any(GC_OID(_oid_(OBJECT(Variable,v48370)->range)),list::alloc(1,((OID)v48362))));
              ++v48362;
              { { OID  v10626;
                  { if (INHERIT(OBJECT(Variable,v48370)->range->isa,Core._global_variable))
                     v10626 = _oid_(OBJECT(Variable,v48370)->range);
                    else v10626 = v48364;
                      GC_OID(v10626);}
                  v57417 = v57417->addFast((OID)v10626);
                  }
                GC_OBJECT(list,v57417);}
              (OBJECT(Variable,v48370)->range = type_I_any(v48364));
              v_val = v48364;
              }
            
            (*((list *) v57419))[CLcount] = v_val;}
          }
        GC_OBJECT(list,v57419);}
      Result = list::alloc(2,_oid_(v57417),_oid_(v57419));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireBoolean * _equalsig_ask_list(list *v48372,list *v48373)
{ POP_SIGNAL; return (((tmatch_ask_list(v48372,v48373) == CTRUE) ? ((tmatch_ask_list(v48373,v48372) == CTRUE) ? CTRUE: CFALSE): CFALSE));}

char * function_name_property_Optimize(property *v48364,list *v48360,OID v48372)
{ GC_BIND;
  { char *Result ;
    if (INHERIT(OWNER(v48372),Kernel._function))
     Result = string_I_function(OBJECT(ClaireFunction,v48372));
    else { CL_INT  v48362 = 0;
        CL_INT  v48361 = 0;
        module * v57499 = v48364->name->module_I;
        ClaireClass * v48351 = class_I_type(OBJECT(ClaireType,(*(v48360))[1]));
        char * v48366 = GC_STRING(append_string(GC_STRING(append_string(string_I_symbol(v48364->name),"_")),string_I_symbol(v48351->name)));
        if ((Optimize.compiler->naming == 0) && 
            (v48364 != Core.main))
         v48366= GC_STRING(append_string(GC_STRING(append_string(string_I_symbol(v57499->name),"_")),v48366));
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(v48366);
          for (START(v48364->restrictions); NEXT(v48366);)
          { if (v48351 == domain_I_restriction(OBJECT(restriction,v48366)))
             ++v48362;
            if (_equalsig_ask_list(v48360,OBJECT(restriction,v48366)->domain) == CTRUE)
             v48361= v48362;
            }
          }
        v48366= GC_STRING(((v48364 == Core.main) ?
          v48366 :
          (((CL_INT)v48362 <= 1) ?
            append_string(v48366,"1") :
            append_string(v48366,GC_STRING(string_I_integer (v48361))) ) ));
        Result = (((stable_ask_relation(v48364) == CTRUE) || 
            (v48364 == Core.main)) ?
          v48366 :
          append_string(GC_STRING(append_string(v48366,"_")),string_I_symbol(ClEnv->module_I->name)) );
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  compile_lambda_string(char *v61776,lambda *v48360,OID v48361)
{ { OID Result = 0;
    { CL_INT  v48372 = Optimize.compiler->safety;
      lambda * v48373 = v48360;
      if (should_trace_ask_module1(Optimize.it,3) == CTRUE)
       mtformat_module1(Optimize.it,"---- Compiling ~A,\n",3,list::alloc(1,_string_(v61776)));
      else ;if (Kernel._method == OWNER(v48361))
       (Optimize.OPT->in_method = v48361);
      (Optimize.OPT->protection = CFALSE);
      (Optimize.OPT->allocation = CFALSE);
      if ((CL_INT)Optimize.OPT->loop_index > 0)
       (Optimize.OPT->loop_index = 0);
      (Optimize.OPT->loop_gc = CFALSE);
      (Optimize.OPT->use_update = CFALSE);
      (Optimize.OPT->use_nth_equal = CFALSE);
      (Optimize.OPT->max_vars = 0);
      if (contain_ask_list(Optimize.OPT->unsure,v48361) == CTRUE)
       (Optimize.compiler->safety = 1);
      (*Optimize.make_c_function)(_oid_(v48360),
        _string_(v61776),
        v48361);
      (Optimize.OPT->in_method = CNULL);
      (Optimize.compiler->safety = v48372);
      Result = Kernel.ctrue;
      }
    POP_SIGNAL; return (Result);}
  }

OID  c_code_Defarray_Optimize(Defarray *v61776)
{ GC_BIND;
  { OID Result = 0;
    { list * v48349 = GC_OBJECT(list,v61776->arg->args);
      OID  v55264 = get_symbol(extract_symbol_any((*(v48349))[1]));
      table * v55285;
      { ClaireObject *V_CC ;
        if (INHERIT(OWNER(v55264),Kernel._table))
         V_CC = OBJECT(table,v55264);
        else close_exception(((general_error *) (*Core._general_error)(_string_("[internal] the table ~S is unknown"),
            _oid_(list::alloc(1,(*(v48349))[1])))));
          v55285= (table *) V_CC;}
      OID  v48367 = GC_OID((*Kernel.domain)(v55264));
      OID  v48353;
      { { list * v48360 = GC_OBJECT(list,cdr_list(v48349));
          OID  v48350 = GC_OID(lexical_build_any(GC_OID(v61776->body),v48360,0));
          { ClaireBoolean * g1695I;
            { OID  v13509;
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(v57777);
                v13509= Kernel.cfalse;
                for (START(v48360); NEXT(v57777);)
                if ((CL_INT)(*Kernel.occurrence)(v48350,
                  v57777) > 0)
                 { v13509 = Kernel.ctrue;
                  ClEnv->cHandle = loop_handle;break;}
                }
              g1695I = boolean_I_any(v13509);
              }
            
            if (g1695I == CTRUE) v48353 = _oid_(lambda_I_list(v48360,v48350));
              else v48353 = v61776->body;
            }
          }
        GC_OID(v48353);}
      OID  v48352;
      { if (INHERIT(OWNER(v48353),Core._lambda))
         v48352 = CNULL;
        else v48352 = v61776->body;
          GC_OID(v48352);}
      list * v9640;
      if (boolean_I_any(_oid_(OBJECT(ClaireRelation,v55264)->multivalued_ask)) == CTRUE)
       { OID v_bag;
        GC_ANY(v9640= list::empty(Kernel._any));
        { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            (v47292->selector = Kernel.put);
            (v47292->args = list::alloc(3,_oid_(Kernel.multivalued_ask),
              _oid_(v55285),
              GC_OID(_oid_(OBJECT(ClaireRelation,v55264)->multivalued_ask))));
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
            v_bag = _oid_(v47292);
            }
          GC_OID(v_bag);}
        ((list *) v9640)->addFast((OID)v_bag);}
      else v9640 = list::empty(Kernel._any);
        list * v9639;
      { OID v_bag;
        GC_ANY(v9639= list::empty(Kernel._any));
        { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            (v47292->selector = Kernel.put);
            (v47292->args = list::alloc(3,_oid_(Kernel.range),
              _oid_(v55285),
              GC_OID((*Kernel.range)(v55264))));
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
            v_bag = _oid_(v47292);
            }
          GC_OID(v_bag);}
        ((list *) v9639)->addFast((OID)v_bag);
        { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            (v47292->selector = Kernel.put);
            (v47292->args = list::alloc(3,_oid_(Kernel.params),
              _oid_(v55285),
              GC_OID((*Kernel.params)(v55264))));
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
            v_bag = _oid_(v47292);
            }
          GC_OID(v_bag);}
        ((list *) v9639)->addFast((OID)v_bag);
        { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            (v47292->selector = Kernel.put);
            (v47292->args = list::alloc(3,_oid_(Kernel.domain),
              _oid_(v55285),
              v48367));
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
            v_bag = _oid_(v47292);
            }
          GC_OID(v_bag);}
        ((list *) v9639)->addFast((OID)v_bag);}
      (OBJECT(Variable,(*(v48349))[2])->range = extract_type_any(GC_OID(_oid_(OBJECT(Variable,(*(v48349))[2])->range))));
      if (v48349->length == 2)
       { { { OID  v14470;
            { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (v47292->selector = Kernel.put);
              { Call * v28519 = v47292; 
                list * v28521;
                { OID v_bag;
                  GC_ANY(v28521= list::empty(Kernel.emptySet));
                  ((list *) v28521)->addFast((OID)_oid_(Kernel.graph));
                  ((list *) v28521)->addFast((OID)_oid_(v55285));
                  if (INHERIT(OBJECT(ClaireObject,v48367)->isa,Core._Interval))
                   { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Core.make_copy_list);
                    (v47292->args = list::alloc(2,((OID)size_Interval(OBJECT(Interval,v48367))),v48352));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v_bag = _oid_(v47292);
                    }
                  else { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      (v47292->selector = Kernel.make_list);
                      (v47292->args = list::alloc(2,((OID)29),CNULL));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                      v_bag = _oid_(v47292);
                      }
                    ((list *) v28521)->addFast((OID)v_bag);}
                (v28519->args = v28521);}
              add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
              v14470 = _oid_(v47292);
              }
            v9639 = v9639->addFast((OID)v14470);
            }
          GC_OBJECT(list,v9639);}
        { { OID  v7785;
            if (INHERIT(OWNER(v48353),Core._lambda))
             { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
              store_object(v47292,
                2,
                Kernel._object,
                (*(v48349))[2],
                CFALSE);
              (v47292->set_arg = v48367);
              { Iteration * v29194 = v47292; 
                OID  v29195;
                { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  (v47292->selector = Kernel.nth_equal);
                  (v47292->args = list::alloc(3,_oid_(v55285),
                    (*(v48349))[2],
                    GC_OID(OBJECT(lambda,v48353)->body)));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                  v29195 = _oid_(v47292);
                  }
                (v29194->arg = v29195);}
              add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
              v7785 = _oid_(v47292);
              }
            else { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                (v47292->selector = Kernel.put);
                (v47292->args = list::alloc(3,_oid_(Kernel.DEFAULT),
                  _oid_(v55285),
                  v48352));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                v7785 = _oid_(v47292);
                }
              v9639 = v9639->addFast((OID)v7785);
            }
          GC_OBJECT(list,v9639);}
        }
      else { ClaireType * v57635 = GC_OBJECT(ClaireType,extract_type_any(GC_OID(_oid_(OBJECT(Variable,(*(v48349))[3])->range))));
          (OBJECT(Variable,(*(v48349))[3])->range = v57635);
          { { OID  v10668;
              { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                (v47292->selector = Kernel.put);
                { Call * v29197 = v47292; 
                  list * v29198;
                  { OID v_bag;
                    GC_ANY(v29198= list::empty(Kernel.emptySet));
                    ((list *) v29198)->addFast((OID)_oid_(Kernel.graph));
                    ((list *) v29198)->addFast((OID)_oid_(v55285));
                    { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        (v47292->selector = Core.make_copy_list);
                        { Call * v29199 = v47292; 
                          list * v29200;
                          { OID v_bag;
                            GC_ANY(v29200= list::empty(Kernel.emptySet));
                            ((list *) v29200)->addFast((OID)((OID)OBJECT(table,v55264)->graph->length));
                            { if ((*Kernel.params)(v55264) == _oid_(Kernel._any))
                               v_bag = CNULL;
                              else v_bag = (*Kernel.DEFAULT)(v55264);
                                GC_OID(v_bag);}
                            ((list *) v29200)->addFast((OID)v_bag);}
                          (v29199->args = v29200);}
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                        v_bag = _oid_(v47292);
                        }
                      GC_OID(v_bag);}
                    ((list *) v29198)->addFast((OID)v_bag);}
                  (v29197->args = v29198);}
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                v10668 = _oid_(v47292);
                }
              v9639 = v9639->addFast((OID)v10668);
              }
            GC_OBJECT(list,v9639);}
          { { OID  v15474;
              if (INHERIT(OWNER(v48353),Core._lambda))
               { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                store_object(v47292,
                  2,
                  Kernel._object,
                  (*(v48349))[2],
                  CFALSE);
                (v47292->set_arg = (*(OBJECT(bag,v48367)))[1]);
                { Iteration * v29202 = v47292; 
                  OID  v29224;
                  { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                    store_object(v47292,
                      2,
                      Kernel._object,
                      (*(v48349))[3],
                      CFALSE);
                    (v47292->set_arg = _oid_(v57635));
                    { Iteration * v29225 = v47292; 
                      OID  v29226;
                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        (v47292->selector = Kernel.nth_equal);
                        (v47292->args = list::alloc(4,_oid_(v55285),
                          (*(v48349))[2],
                          (*(v48349))[3],
                          GC_OID(OBJECT(lambda,v48353)->body)));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                        v29226 = _oid_(v47292);
                        }
                      (v29225->arg = v29226);}
                    add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
                    v29224 = _oid_(v47292);
                    }
                  (v29202->arg = v29224);}
                add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
                v15474 = _oid_(v47292);
                }
              else { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  (v47292->selector = Kernel.put);
                  (v47292->args = list::alloc(3,_oid_(Kernel.DEFAULT),
                    _oid_(v55285),
                    v48352));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                  v15474 = _oid_(v47292);
                  }
                v9639 = v9639->addFast((OID)v15474);
              }
            GC_OBJECT(list,v9639);}
          }
        GC_OBJECT(list,Optimize.OPT->objects)->addFast((OID)v55264);
      (*Optimize.c_register)(v55264);
      { OID  v40459;
        { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
          { Do * v29228 = v47292; 
            list * v29229;
            { OID  v43342;
              { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                (v47292->selector = Optimize.object_I);
                (v47292->args = list::alloc(2,GC_OID((*Kernel.name)(v55264)),_oid_(Kernel._table)));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                v43342 = _oid_(v47292);
                }
              v29229 = cons_any(v43342,GC_OBJECT(list,add_star_list(v9640,v9639)));
              }
            (v29228->args = v29229);}
          add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
          v40459 = _oid_(v47292);
          }
        Result = (*Optimize.c_code)(v40459,
          _oid_(Kernel._any));
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  compute_if_write_inverse_relation2(ClaireRelation *v48334)
{ GC_BIND;
  { Variable * v48372;
    { { Variable * v47292 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
        (v47292->pname = symbol_I_string2("XX"));
        (v47292->range = v48334->domain);
        add_I_property(Kernel.instances,Language._Variable,11,_oid_(v47292));
        v48372 = v47292;
        }
      GC_OBJECT(Variable,v48372);}
    Variable * v48373;
    { { Variable * v47292 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
        (v47292->pname = symbol_I_string2("YY"));
        (v47292->range = ((multi_ask_any(_oid_(v48334)) == CTRUE) ?
          member_type(v48334->range) :
          v48334->range ));
        add_I_property(Kernel.instances,Language._Variable,11,_oid_(v47292));
        v48373 = v47292;
        }
      GC_OBJECT(Variable,v48373);}
    Variable * v48374;
    { { Variable * v47292 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
        (v47292->pname = symbol_I_string2("ZZ"));
        (v47292->range = v48334->range);
        add_I_property(Kernel.instances,Language._Variable,11,_oid_(v47292));
        v48374 = v47292;
        }
      GC_OBJECT(Variable,v48374);}
    list * v57417 = list::empty(Kernel._any);
    if (multi_ask_any(_oid_(v48334)) == CTRUE)
     { v57417= list::alloc(Kernel._any,1,GC_OID((INHERIT(v48334->isa,Kernel._property) ?
        Produce_put_property2((property *) OBJECT(property,_oid_(v48334)),OBJECT(Variable,_oid_(v48372)),_oid_(v48373)) : 
        Produce_put_table2((table *) OBJECT(table,_oid_(v48334)),OBJECT(Variable,_oid_(v48372)),_oid_(v48373)))));
      if (((v48334->inverse == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       v57417= GC_OBJECT(list,v57417->addFast((OID)GC_OID((INHERIT(v48334->inverse->isa,Kernel._property) ?
        Produce_put_property2((property *) OBJECT(property,_oid_(v48334->inverse)),OBJECT(Variable,_oid_(v48373)),_oid_(v48372)) : 
        Produce_put_table2((table *) OBJECT(table,_oid_(v48334->inverse)),OBJECT(Variable,_oid_(v48373)),_oid_(v48372))))));
      { ClaireRelation * v29231 = v48334; 
        OID  v29232;
        { lambda * v4804;{ OID  v1831;
            { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
              { If * v29256 = v47292; 
                OID  v29257;
                { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  (v47292->selector = Core.NOT);
                  { Call * v29258 = v47292; 
                    list * v29259;
                    { OID v_bag;
                      GC_ANY(v29259= list::empty(Kernel.emptySet));
                      { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          (v47292->selector = Kernel._Z);
                          (v47292->args = list::alloc(2,_oid_(v48373),GC_OID(Produce_get_relation2(v48334,v48372))));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                          v_bag = _oid_(v47292);
                          }
                        GC_OID(v_bag);}
                      ((list *) v29259)->addFast((OID)v_bag);}
                    (v29258->args = v29259);}
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                  v29257 = _oid_(v47292);
                  }
                (v29256->test = v29257);}
              { If * v29260 = v47292; 
                OID  v29261;
                { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                  (v47292->args = v57417);
                  add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                  v29261 = _oid_(v47292);
                  }
                (v29260->arg = v29261);}
              add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
              (v47292->other = Kernel.cfalse);
              v1831 = _oid_(v47292);
              }
            v4804 = lambda_I_list(list::alloc(2,_oid_(v48372),_oid_(v48373)),v1831);
            }
          
          v29232=_oid_(v4804);}
        (v29231->if_write = v29232);}
      }
    else { v57417= list::alloc(Kernel._any,1,GC_OID((INHERIT(v48334->isa,Kernel._property) ?
          Produce_put_property2((property *) OBJECT(property,_oid_(v48334)),OBJECT(Variable,_oid_(v48372)),_oid_(v48373)) : 
          Produce_put_table2((table *) OBJECT(table,_oid_(v48334)),OBJECT(Variable,_oid_(v48372)),_oid_(v48373)))));
        if (((v48334->inverse == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         { { { OID  v8558;
              { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                { If * v29263 = v47292; 
                  OID  v29264;
                  { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Core.known_ask);
                    (v47292->args = list::alloc(1,_oid_(v48374)));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v29264 = _oid_(v47292);
                    }
                  (v29263->test = v29264);}
                (v47292->arg = (INHERIT(v48334->inverse->isa,Kernel._property) ?
                  Produce_remove_property2((property *) OBJECT(property,_oid_(v48334->inverse)),OBJECT(Variable,_oid_(v48374)),_oid_(v48372)) : 
                  Produce_remove_table2((table *) OBJECT(table,_oid_(v48334->inverse)),OBJECT(Variable,_oid_(v48374)),_oid_(v48372))));
                add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                (v47292->other = Kernel.cfalse);
                v8558 = _oid_(v47292);
                }
              v57417 = v57417->addFast((OID)v8558);
              }
            GC_OBJECT(list,v57417);}
          v57417= GC_OBJECT(list,v57417->addFast((OID)GC_OID((INHERIT(v48334->inverse->isa,Kernel._property) ?
            Produce_put_property2((property *) OBJECT(property,_oid_(v48334->inverse)),OBJECT(Variable,_oid_(v48373)),_oid_(v48372)) : 
            Produce_put_table2((table *) OBJECT(table,_oid_(v48334->inverse)),OBJECT(Variable,_oid_(v48373)),_oid_(v48372))))));
          }
        { ClaireRelation * v29286 = v48334; 
          OID  v29287;
          { lambda * v4859;{ OID  v34505;
              { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                (v47292->var = v48374);
                (v47292->value = Produce_get_relation2(v48334,v48372));
                { Let * v29290 = v47292; 
                  OID  v29291;
                  { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                    { If * v29292 = v47292; 
                      OID  v29293;
                      { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        (v47292->selector = Core._I_equal);
                        (v47292->args = list::alloc(2,_oid_(v48373),_oid_(v48374)));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                        v29293 = _oid_(v47292);
                        }
                      (v29292->test = v29293);}
                    { If * v29294 = v47292; 
                      OID  v29295;
                      { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                        (v47292->args = v57417);
                        add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                        v29295 = _oid_(v47292);
                        }
                      (v29294->arg = v29295);}
                    add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                    (v47292->other = Kernel.cfalse);
                    v29291 = _oid_(v47292);
                    }
                  (v29290->arg = v29291);}
                add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
                v34505 = _oid_(v47292);
                }
              v4859 = lambda_I_list(list::alloc(2,_oid_(v48372),_oid_(v48373)),v34505);
              }
            
            v29287=_oid_(v4859);}
          (v29286->if_write = v29287);}
        }
      { char * v57230 = GC_STRING(append_string(string_I_symbol(v48334->name),"_write"));
      compile_lambda_string(v57230,GC_OBJECT(lambda,OBJECT(lambda,v48334->if_write)),_oid_(Kernel._void));
      }
    }
  GC_UNBIND; POP_SIGNAL;}

OID  compute_set_write_relation2(ClaireRelation *v48334)
{ GC_BIND;
  { OID Result = 0;
    { Variable * v48372;
      { { Variable * v47292 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
          (v47292->pname = symbol_I_string2("XX"));
          (v47292->range = v48334->domain);
          add_I_property(Kernel.instances,Language._Variable,11,_oid_(v47292));
          v48372 = v47292;
          }
        GC_OBJECT(Variable,v48372);}
      Variable * v48373;
      { { Variable * v47292 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
          (v47292->pname = symbol_I_string2("YY"));
          (v47292->range = Kernel._bag);
          add_I_property(Kernel.instances,Language._Variable,11,_oid_(v47292));
          v48373 = v47292;
          }
        GC_OBJECT(Variable,v48373);}
      Variable * v48374;
      { { Variable * v47292 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
          (v47292->pname = symbol_I_string2("ZZ"));
          (v47292->range = member_type(v48334->range));
          add_I_property(Kernel.instances,Language._Variable,11,_oid_(v47292));
          v48374 = v47292;
          }
        GC_OBJECT(Variable,v48374);}
      list * v57417 = list::empty(Kernel._any);
      if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
       mtformat_module1(Optimize.it,"compute set_write for ~S \n",0,list::alloc(1,_oid_(v48334)));
      else ;if (((v48334->inverse == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       { { OID  v61413;
          { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
            (v47292->var = v48374);
            (v47292->set_arg = Produce_get_relation2(v48334,v48372));
            (v47292->arg = (INHERIT(v48334->inverse->isa,Kernel._property) ?
              Produce_remove_property2((property *) OBJECT(property,_oid_(v48334->inverse)),OBJECT(Variable,_oid_(v48374)),_oid_(v48372)) : 
              Produce_remove_table2((table *) OBJECT(table,_oid_(v48334->inverse)),OBJECT(Variable,_oid_(v48374)),_oid_(v48372))));
            add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
            v61413 = _oid_(v47292);
            }
          v57417 = v57417->addFast((OID)v61413);
          }
        GC_OBJECT(list,v57417);}
      v57417= GC_OBJECT(list,v57417->addFast((OID)GC_OID(Produce_erase_property2(((property *) v48334),v48372))));
      { { OID  v62374;
          { For * v47292 = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
            (v47292->var = v48374);
            (v47292->set_arg = _oid_(v48373));
            (v47292->arg = (INHERIT(v48334->isa,Kernel._property) ?
              Produce_put_property2((property *) OBJECT(property,_oid_(v48334)),OBJECT(Variable,_oid_(v48372)),_oid_(v48374)) : 
              Produce_put_table2((table *) OBJECT(table,_oid_(v48334)),OBJECT(Variable,_oid_(v48372)),_oid_(v48374))));
            add_I_property(Kernel.instances,Language._For,11,_oid_(v47292));
            v62374 = _oid_(v47292);
            }
          v57417 = v57417->addFast((OID)v62374);
          }
        GC_OBJECT(list,v57417);}
      { char * v57230 = GC_STRING(append_string(string_I_symbol(v48334->name),"_set_write"));
        { lambda * v63335;
          { { OID  v64296;
              { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                (v47292->args = v57417);
                add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                v64296 = _oid_(v47292);
                }
              v63335 = lambda_I_list(list::alloc(2,_oid_(v48372),_oid_(v48373)),v64296);
              }
            GC_OBJECT(lambda,v63335);}
          Result = compile_lambda_string(v57230,v63335,_oid_(Kernel._void));
          }
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  Produce_put_property2(property *v48366,Variable *v48372,OID v48373)
{ GC_BIND;
  { OID Result = 0;
    { list * v48360 = list::empty(Kernel._any);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v57855);
        for (START(v48366->restrictions); NEXT(v57855);)
        { GC_LOOP;
          if ((Kernel._slot == OBJECT(ClaireObject,v57855)->isa) && 
              (boolean_I_any(_oid_(_exp_type(GC_OBJECT(ClaireType,ptype_type(v48372->range)),domain_I_restriction(OBJECT(restriction,v57855))))) == CTRUE))
           { list * v65257;
            { { OID v_bag;
                GC_ANY(v65257= list::empty(Kernel.emptySet));
                ((list *) v65257)->addFast((OID)_oid_(domain_I_restriction(OBJECT(restriction,v57855))));
                if (boolean_I_any(_oid_(v48366->multivalued_ask)) == CTRUE)
                 { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  (v47292->selector = Kernel.add_I);
                  { Call * v29323 = v47292; 
                    list * v29324;
                    { OID v_bag;
                      GC_ANY(v29324= list::empty(Kernel.emptySet));
                      { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          (v47292->selector = v48366);
                          { Call * v29325 = v47292; 
                            list * v29326;
                            { OID v_bag;
                              GC_ANY(v29326= list::empty(Kernel.emptySet));
                              { { Cast * v47292 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                                  (v47292->arg = _oid_(v48372));
                                  (v47292->set_arg = domain_I_restriction(OBJECT(restriction,v57855)));
                                  add_I_property(Kernel.instances,Language._Cast,11,_oid_(v47292));
                                  v_bag = _oid_(v47292);
                                  }
                                GC_OID(v_bag);}
                              ((list *) v29326)->addFast((OID)v_bag);}
                            (v29325->args = v29326);}
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                          v_bag = _oid_(v47292);
                          }
                        GC_OID(v_bag);}
                      ((list *) v29324)->addFast((OID)v_bag);
                      ((list *) v29324)->addFast((OID)v48373);}
                    (v29323->args = v29324);}
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                  v_bag = _oid_(v47292);
                  }
                else { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Kernel.put);
                    { Call * v29327 = v47292; 
                      list * v29348;
                      { OID v_bag;
                        GC_ANY(v29348= list::empty(Kernel.emptySet));
                        ((list *) v29348)->addFast((OID)_oid_(v48366));
                        { { Cast * v47292 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                            (v47292->arg = _oid_(v48372));
                            (v47292->set_arg = domain_I_restriction(OBJECT(restriction,v57855)));
                            add_I_property(Kernel.instances,Language._Cast,11,_oid_(v47292));
                            v_bag = _oid_(v47292);
                            }
                          GC_OID(v_bag);}
                        ((list *) v29348)->addFast((OID)v_bag);
                        ((list *) v29348)->addFast((OID)v48373);}
                      (v29327->args = v29348);}
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v_bag = _oid_(v47292);
                    }
                  ((list *) v65257)->addFast((OID)v_bag);}
              GC_OBJECT(list,v65257);}
            v48360 = add_star_list(v48360,v65257);
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      if (v48360->length == 2)
       Result = (*(v48360))[2];
      else { Case * v47292 = ((Case *) GC_OBJECT(Case,new_object_class(Language._Case)));
          (v47292->var = _oid_(v48372));
          (v47292->args = v48360);
          add_I_property(Kernel.instances,Language._Case,11,_oid_(v47292));
          Result = _oid_(v47292);
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  Produce_erase_property2(property *v48366,Variable *v48372)
{ GC_BIND;
  { OID Result = 0;
    { list * v48360 = list::empty(Kernel._any);
      bag * v21661;
      if (v48366->multivalued_ask == Kernel._list)
       v21661 = list::empty(Kernel._any);
      else v21661 = set::empty(Kernel._any);
        _oid_((INHERIT(v21661->isa,Kernel._list) ?
       (ClaireObject *) cast_I_list1((list *) OBJECT(list,_oid_(v21661)),OBJECT(ClaireType,GC_OID(_oid_(member_type(v48366->range))))) : 
       (ClaireObject *)  cast_I_set1((set *) OBJECT(set,_oid_(v21661)),OBJECT(ClaireType,GC_OID(_oid_(member_type(v48366->range)))))));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v57855);
        for (START(v48366->restrictions); NEXT(v57855);)
        { GC_LOOP;
          if ((Kernel._slot == OBJECT(ClaireObject,v57855)->isa) && 
              (boolean_I_any(_oid_(_exp_type(GC_OBJECT(ClaireType,ptype_type(v48372->range)),domain_I_restriction(OBJECT(restriction,v57855))))) == CTRUE))
           { list * v26629;
            { { OID v_bag;
                GC_ANY(v26629= list::empty(Kernel.emptySet));
                ((list *) v26629)->addFast((OID)_oid_(domain_I_restriction(OBJECT(restriction,v57855))));
                { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Kernel.put);
                    { Call * v29350 = v47292; 
                      list * v29351;
                      { OID v_bag;
                        GC_ANY(v29351= list::empty(Kernel.emptySet));
                        ((list *) v29351)->addFast((OID)_oid_(v48366));
                        { { Cast * v47292 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                            (v47292->arg = _oid_(v48372));
                            (v47292->set_arg = domain_I_restriction(OBJECT(restriction,v57855)));
                            add_I_property(Kernel.instances,Language._Cast,11,_oid_(v47292));
                            v_bag = _oid_(v47292);
                            }
                          GC_OID(v_bag);}
                        ((list *) v29351)->addFast((OID)v_bag);
                        { if (boolean_I_any(_oid_(v48366->multivalued_ask)) == CTRUE)
                           v_bag = _oid_(v21661);
                          else v_bag = OBJECT(slot,v57855)->DEFAULT;
                            GC_OID(v_bag);}
                        ((list *) v29351)->addFast((OID)v_bag);}
                      (v29350->args = v29351);}
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v_bag = _oid_(v47292);
                    }
                  GC_OID(v_bag);}
                ((list *) v26629)->addFast((OID)v_bag);}
              GC_OBJECT(list,v26629);}
            v48360 = add_star_list(v48360,v26629);
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      if (v48360->length == 2)
       Result = (*(v48360))[2];
      else { Case * v47292 = ((Case *) GC_OBJECT(Case,new_object_class(Language._Case)));
          (v47292->var = _oid_(v48372));
          (v47292->args = v48360);
          add_I_property(Kernel.instances,Language._Case,11,_oid_(v47292));
          Result = _oid_(v47292);
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  Produce_put_table2(table *v48366,Variable *v48372,OID v48373)
{ GC_BIND;
  { OID Result = 0;
    { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
      (v47292->selector = Kernel.put);
      { Call * v29352 = v47292; 
        list * v29353;
        { OID v_bag;
          GC_ANY(v29353= list::empty(Kernel.emptySet));
          ((list *) v29353)->addFast((OID)_oid_(v48366));
          ((list *) v29353)->addFast((OID)_oid_(v48372));
          if (boolean_I_any(_oid_(v48366->multivalued_ask)) == CTRUE)
           { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            (v47292->selector = Kernel.add);
            (v47292->args = list::alloc(2,_oid_(list::alloc(2,_oid_(Kernel.nth),_oid_(list::alloc(2,_oid_(v48366),_oid_(v48372))))),v48373));
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
            v_bag = _oid_(v47292);
            }
          else v_bag = v48373;
            ((list *) v29353)->addFast((OID)v_bag);}
        (v29352->args = v29353);}
      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  Produce_get_relation2(ClaireRelation *v48366,Variable *v48372)
{ GC_BIND;
  { OID Result = 0;
    if (INHERIT(v48366->isa,Kernel._table))
     { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
      (v47292->selector = Kernel.nth);
      (v47292->args = list::alloc(2,_oid_(v48366),_oid_(v48372)));
      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    else if (INHERIT(v48366->isa,Kernel._property))
     { list * v48360 = list::empty(Kernel._any);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v57855);
        for (START(CLREAD(property,v48366,restrictions)); NEXT(v57855);)
        { GC_LOOP;
          if ((Kernel._slot == OBJECT(ClaireObject,v57855)->isa) && 
              (boolean_I_any(_oid_(_exp_type(GC_OBJECT(ClaireType,ptype_type(v48372->range)),domain_I_restriction(OBJECT(restriction,v57855))))) == CTRUE))
           { list * v31434;
            { { OID v_bag;
                GC_ANY(v31434= list::empty(Kernel.emptySet));
                ((list *) v31434)->addFast((OID)_oid_(domain_I_restriction(OBJECT(restriction,v57855))));
                { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = ((property *) v48366));
                    { Call * v29355 = v47292; 
                      list * v29356;
                      { OID v_bag;
                        GC_ANY(v29356= list::empty(Kernel.emptySet));
                        { { Cast * v47292 = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
                            (v47292->arg = _oid_(v48372));
                            (v47292->set_arg = domain_I_restriction(OBJECT(restriction,v57855)));
                            add_I_property(Kernel.instances,Language._Cast,11,_oid_(v47292));
                            v_bag = _oid_(v47292);
                            }
                          GC_OID(v_bag);}
                        ((list *) v29356)->addFast((OID)v_bag);}
                      (v29355->args = v29356);}
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v_bag = _oid_(v47292);
                    }
                  GC_OID(v_bag);}
                ((list *) v31434)->addFast((OID)v_bag);}
              GC_OBJECT(list,v31434);}
            v48360 = add_star_list(v48360,v31434);
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      if (v48360->length == 2)
       Result = (*(v48360))[2];
      else { Case * v47292 = ((Case *) GC_OBJECT(Case,new_object_class(Language._Case)));
          (v47292->var = _oid_(v48372));
          (v47292->args = v48360);
          add_I_property(Kernel.instances,Language._Case,11,_oid_(v47292));
          Result = _oid_(v47292);
          }
        }
    else Result = Kernel.cfalse;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  Produce_remove_property2(property *v48366,Variable *v48372,OID v48373)
{ GC_BIND;
  { OID Result = 0;
    { list * v48360 = list::empty(Kernel._any);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v57855);
        for (START(v48366->restrictions); NEXT(v57855);)
        { GC_LOOP;
          if (Kernel._slot == OBJECT(ClaireObject,v57855)->isa)
           { list * v34317;
            { { OID v_bag;
                GC_ANY(v34317= list::empty(Kernel.emptySet));
                ((list *) v34317)->addFast((OID)_oid_(domain_I_restriction(OBJECT(restriction,v57855))));
                if (boolean_I_any(_oid_(v48366->multivalued_ask)) == CTRUE)
                 { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  (v47292->selector = Kernel._delete);
                  { Call * v29379 = v47292; 
                    list * v29380;
                    { OID v_bag;
                      GC_ANY(v29380= list::empty(Kernel.emptySet));
                      { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          (v47292->selector = v48366);
                          (v47292->args = list::alloc(1,_oid_(v48372)));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                          v_bag = _oid_(v47292);
                          }
                        GC_OID(v_bag);}
                      ((list *) v29380)->addFast((OID)v_bag);
                      ((list *) v29380)->addFast((OID)v48373);}
                    (v29379->args = v29380);}
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                  v_bag = _oid_(v47292);
                  }
                else { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (v47292->selector = Kernel.put);
                    (v47292->args = list::alloc(3,_oid_(v48366),
                      _oid_(v48372),
                      CNULL));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                    v_bag = _oid_(v47292);
                    }
                  ((list *) v34317)->addFast((OID)v_bag);}
              GC_OBJECT(list,v34317);}
            v48360 = add_star_list(v48360,v34317);
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      if (v48360->length == 2)
       Result = (*(v48360))[2];
      else { Case * v47292 = ((Case *) GC_OBJECT(Case,new_object_class(Language._Case)));
          (v47292->var = _oid_(v48372));
          (v47292->args = v48360);
          add_I_property(Kernel.instances,Language._Case,11,_oid_(v47292));
          Result = _oid_(v47292);
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  Produce_remove_table2(table *v48366,Variable *v48372,OID v48373)
{ GC_BIND;
  { OID Result = 0;
    { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
      (v47292->selector = Kernel.put);
      { Call * v29381 = v47292; 
        list * v29382;
        { OID v_bag;
          GC_ANY(v29382= list::empty(Kernel.emptySet));
          ((list *) v29382)->addFast((OID)_oid_(v48366));
          ((list *) v29382)->addFast((OID)_oid_(v48372));
          if (boolean_I_any(_oid_(v48366->multivalued_ask)) == CTRUE)
           { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            (v47292->selector = Kernel._delete);
            (v47292->args = list::alloc(2,_oid_(list::alloc(2,_oid_(Kernel.nth),_oid_(list::alloc(2,_oid_(v48366),_oid_(v48372))))),v48373));
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
            v_bag = _oid_(v47292);
            }
          else v_bag = CNULL;
            ((list *) v29382)->addFast((OID)v_bag);}
        (v29381->args = v29382);}
      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
      Result = _oid_(v47292);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  Tighten_relation2(ClaireRelation *v48366)
{ GC_RESERVE(6);  // v3.0.55 optim !
  if (INHERIT(v48366->isa,Kernel._property))
   { ClaireType * v57127 = set::empty();
    ClaireType * v57141 = set::empty();
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v48367);
      for (START(CLREAD(property,v48366,restrictions)); NEXT(v48367);)
      { GC_LOOP;
        if (Kernel._slot == OBJECT(ClaireObject,v48367)->isa)
         { GC__ANY(v57127 = U_type(v57127,domain_I_restriction(OBJECT(restriction,v48367))), 3);
          GC__ANY(v57141 = U_type(v57141,GC_OBJECT(ClaireType,((multi_ask_any(_oid_(v48366)) == CTRUE) ?
            member_type(OBJECT(restriction,v48367)->range) :
            OBJECT(restriction,v48367)->range ))), 4);
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    (v48366->open = 1);
    (v48366->domain = class_I_type(v57127));
    (v48366->range = ((v48366->multivalued_ask == Kernel._list) ?
      param_I_class(Kernel._list,class_I_type(v57141)) :
      ((v48366->multivalued_ask == Kernel._set) ?
        param_I_class(Kernel._set,class_I_type(v57141)) :
        v57141 ) ));
    if (should_trace_ask_module1(Optimize.it,5) == CTRUE)
     mtformat_module1(Optimize.it,"~S -> ~S x ~S\n",5,GC_OBJECT(list,list::alloc(3,_oid_(v48366),
      _oid_(v48366->domain),
      _oid_(v48366->range))));
    else ;}
  GC_UNBIND; POP_SIGNAL;}

void  lexical_num_any2(OID v61776,int v48362)
{ GC_BIND;
  if (INHERIT(OWNER(v61776),Language._Call))
   lexical_num_any2(GC_OID(_oid_(OBJECT(Call,v61776)->args)),v48362);
  else if (INHERIT(OWNER(v61776),Language._Instruction))
   { ClaireClass * v4955 = OBJECT(ClaireObject,v61776)->isa;
    if (contain_ask_set(Language._Instruction_with_var->descendents,_oid_(v4955)) == CTRUE)
     { put_property2(Kernel.index,GC_OBJECT(ClaireObject,OBJECT(ClaireObject,(*Language.var)(v61776))),((OID)v48362));
      ++v48362;
      if ((CL_INT)v48362 > (CL_INT)Language._starvariable_index_star->value)
       (Language._starvariable_index_star->value= ((OID)v48362));
      }
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v48367);
      for (START(v4955->slots); NEXT(v48367);)
      lexical_num_any2(get_slot(OBJECT(slot,v48367),OBJECT(ClaireObject,v61776)),v48362);
      }
    }
  else if (INHERIT(OWNER(v61776),Kernel._bag))
   { CL_INT loop_handle = ClEnv->cHandle;
    ITERATE(v48372);
    for (START(OBJECT(bag,v61776)); NEXT(v48372);)
    lexical_num_any2(v48372,v48362);
    }
  else ;GC_UNBIND; POP_SIGNAL;}

ClaireType * c_type_Defrule2_Optimize(Defrule *v61776)
{ POP_SIGNAL; return (Kernel._any);}

OID  c_code_Defrule_Optimize(Defrule *v61776,ClaireClass *v48367)
{ GC_RESERVE(11);  // v3.0.55 optim !
  { OID Result = 0;
    { OID  v57671 = get_symbol(v61776->ident);
      list * v48360 = list::empty(Kernel._any);
      if (should_trace_ask_module1(Optimize.it,0) == CTRUE)
       mtformat_module1(Optimize.it,"compile a rule ~S \n",0,list::alloc(1,v57671));
      else ;{ CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v48366);
        bag *v48366_support;
        v48366_support = OBJECT(bag,nth_table1(Language.relations,v57671));
        for (START(v48366_support); NEXT(v48366);)
        if (eventMethod_ask_relation2(OBJECT(ClaireRelation,v48366)) != CTRUE)
         Tighten_relation2(OBJECT(ClaireRelation,v48366));
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v48366);
        bag *v48366_support;
        v48366_support = OBJECT(bag,nth_table1(Language.relations,v57671));
        for (START(v48366_support); NEXT(v48366);)
        { GC_LOOP;
          { if ((CL_INT)(*Kernel.open)(v48366) < 2)
             { { OID  v59308;
                { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  (v47292->selector = Kernel.FINAL);
                  (v47292->args = list::alloc(1,v48366));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                  v59308 = _oid_(v47292);
                  }
                v48360 = v48360->addFast((OID)v59308);
                }
               GC__ANY(v48360, 5);}
            compile_if_write_relation(OBJECT(ClaireRelation,v48366));
            { OID  v57230 = GC_OID((*Kernel._7_plus)(GC_OID((*Kernel.name)(v48366)),
                _string_("_write")));
              char * v48367 = string_I_symbol(OBJECT(symbol,v57230));
              OID  v57466 = GC_OID((*Kernel.if_write)(v48366));
              compile_lambda_string(v48367,OBJECT(lambda,v57466),_oid_(Kernel._void));
              { OID  v60267;
                { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  (v47292->selector = Kernel.put);
                  (v47292->args = list::alloc(3,Optimize.if_write->value,
                    v48366,
                    _oid_(make_function_string(v48367))));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                  v60267 = _oid_(v47292);
                  }
                v48360->addFast((OID)v60267);
                }
              }
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v48366);
        bag *v48366_support;
        v48366_support = OBJECT(bag,nth_table1(Language.relations,v57671));
        for (START(v48366_support); NEXT(v48366);)
        { GC_LOOP;
          if (eventMethod_ask_relation2(OBJECT(ClaireRelation,v48366)) == CTRUE)
           v48360= v48360->addFast((OID)GC_OID(compileEventMethod_property(OBJECT(property,v48366))));
          GC_UNLOOP; POP_SIGNAL;}
        }
      { OID  v61228;
        { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
          (v47292->args = v48360);
          add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
          v61228 = _oid_(v47292);
          }
        Result = (*Optimize.c_code)(v61228,
          _oid_(v48367));
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  compile_if_write_relation(ClaireRelation *v48334)
{ GC_BIND;
  { OID  v48360 = nth_table1(Language.demons,_oid_(v48334));
    list * v319 = GC_OBJECT(list,OBJECT(Language_demon,(*(OBJECT(bag,v48360)))[1])->formula->vars);
    list * v57417 = list::alloc(Kernel._any,1,GC_OID((*Optimize.Produce_put)(_oid_(v48334),
      (*(v319))[1],
      (*(v319))[2])));
    list * v57419;
    { { CL_INT loop_handle = ClEnv->cHandle;
        bag *v_list; OID v_val;
        OID v48372; CL_INT CLcount;
        v_list = OBJECT(bag,v48360);
         v57419 = v_list->clone(Kernel._any);
        for (CLcount= 1; CLcount <= v_list->length; CLcount++)
        { v48372 = (*(v_list))[CLcount];
          v_val = substitution_any(GC_OID(substitution_any(GC_OID(substitution_any(GC_OID(OBJECT(Language_demon,v48372)->formula->body),GC_OBJECT(Variable,OBJECT(Variable,(*(OBJECT(Language_demon,v48372)->formula->vars))[3])),(*(v319))[3])),GC_OBJECT(Variable,OBJECT(Variable,(*(OBJECT(Language_demon,v48372)->formula->vars))[1])),(*(v319))[1])),GC_OBJECT(Variable,OBJECT(Variable,(*(OBJECT(Language_demon,v48372)->formula->vars))[2])),(*(v319))[2]);
          
          (*((list *) v57419))[CLcount] = v_val;}
        }
      GC_OBJECT(list,v57419);}
    put_property2(Kernel.range,OBJECT(ClaireObject,(*(v319))[1]),_oid_(v48334->domain));
    put_property2(Kernel.range,OBJECT(ClaireObject,(*(v319))[2]),_oid_(v48334->range));
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v48370);
      for (START(v319); NEXT(v48370);)
      { GC_LOOP;
        put_property2(Kernel.range,OBJECT(ClaireObject,v48370),_oid_(class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(v48370))))));
        GC_UNLOOP; POP_SIGNAL;}
      }
    if ((INHERIT(OWNER((*(v57419))[1]),Language._If)) && 
        (eventMethod_ask_relation2(v48334) != CTRUE))
     { if (INHERIT(OWNER(OBJECT(If,(*(v57419))[1])->test),Language._And))
       { If * v29386 = OBJECT(If,(*(v57419))[1]); 
        OID  v29387;
        { And * v47292 = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
          (v47292->args = cdr_list(GC_OBJECT(list,OBJECT(list,(*Core.args)(GC_OID(OBJECT(If,(*(v57419))[1])->test))))));
          add_I_property(Kernel.instances,Language._And,11,_oid_(v47292));
          v29387 = _oid_(v47292);
          }
        (v29386->test = v29387);}
      else ((*(v57419))[1]=GC_OID(OBJECT(If,(*(v57419))[1])->arg));
        }
    if (((v48334->inverse == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     { if (multi_ask_any(_oid_(v48334)) != CTRUE)
       v57417= v57417->addFast((OID)GC_OID((*Optimize.Produce_remove)(_oid_(v48334->inverse),
        (*(v319))[3],
        (*(v319))[1])));
      v57417= v57417->addFast((OID)GC_OID((*Optimize.Produce_put)(_oid_(v48334->inverse),
        (*(v319))[2],
        (*(v319))[1])));
      }
    { ClaireRelation * v29388 = v48334; 
      OID  v29410;
      { lambda * v4982;{ OID  v21636;
          if (eventMethod_ask_relation2(v48334) == CTRUE)
           { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            (v47292->args = v57419);
            add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
            v21636 = _oid_(v47292);
            }
          else if (multi_ask_any(_oid_(v48334)) == CTRUE)
           { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
            { If * v29413 = v47292; 
              OID  v29414;
              { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                (v47292->selector = Core.NOT);
                { Call * v29415 = v47292; 
                  list * v29416;
                  { OID v_bag;
                    GC_ANY(v29416= list::empty(Kernel.emptySet));
                    { { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        (v47292->selector = Kernel._Z);
                        (v47292->args = list::alloc(2,(*(v319))[2],GC_OID(_oid_(readCall_relation(v48334,(*(v319))[1])))));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                        v_bag = _oid_(v47292);
                        }
                      GC_OID(v_bag);}
                    ((list *) v29416)->addFast((OID)v_bag);}
                  (v29415->args = v29416);}
                add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                v29414 = _oid_(v47292);
                }
              (v29413->test = v29414);}
            { If * v29417 = v47292; 
              OID  v29418;
              { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                (v47292->args = append_list(v57417,v57419));
                add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                v29418 = _oid_(v47292);
                }
              (v29417->arg = v29418);}
            add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
            (v47292->other = Kernel.cfalse);
            v21636 = _oid_(v47292);
            }
          else { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
              store_object(v47292,
                2,
                Kernel._object,
                (*(v319))[3],
                CFALSE);
              (v47292->value = _oid_(readCall_relation(v48334,(*(v319))[1])));
              { Let * v29419 = v47292; 
                OID  v29441;
                { If * v47292 = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                  { If * v29442 = v47292; 
                    OID  v29443;
                    { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      (v47292->selector = Core._I_equal);
                      (v47292->args = list::alloc(2,(*(v319))[2],(*(v319))[3]));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
                      v29443 = _oid_(v47292);
                      }
                    (v29442->test = v29443);}
                  { If * v29444 = v47292; 
                    OID  v29445;
                    { Do * v47292 = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                      (v47292->args = append_list(v57417,v57419));
                      add_I_property(Kernel.instances,Language._Do,11,_oid_(v47292));
                      v29445 = _oid_(v47292);
                      }
                    (v29444->arg = v29445);}
                  add_I_property(Kernel.instances,Language._If,11,_oid_(v47292));
                  (v47292->other = Kernel.cfalse);
                  v29441 = _oid_(v47292);
                  }
                (v29419->arg = v29441);}
              add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
              v21636 = _oid_(v47292);
              }
            v4982 = lambda_I_list(GC_OBJECT(list,list::alloc(2,(*(v319))[1],(*(v319))[2])),v21636);
          }
        
        v29410=_oid_(v4982);}
      (v29388->if_write = v29410);}
    }
  GC_UNBIND; POP_SIGNAL;}

OID  compileEventMethod_property(property *v48364)
{ GC_BIND;
  { OID Result = 0;
    { method * v48361 = OBJECT(method,(*(v48364->restrictions))[1]);
      char * v57527 = GC_STRING(append_string(string_I_symbol(v48364->name),"_write"));
      Result = add_method_I_method(v48361,
        list::alloc(2,_oid_(v48364->domain),_oid_(v48364->range)),
        _oid_(Kernel._void),
        ((OID)0),
        make_function_string(v57527));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }



