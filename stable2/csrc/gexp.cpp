/***** CLAIRE Compilation of file ./compile/gexp.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:50 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>
#include <Optimize.h>
#include <Generate.h>
ClaireBoolean * c_func_any(OID v45520)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { ClaireBoolean *Result ;
    if (INHERIT(OWNER(v45520),Kernel._bag))
     { OID  v15724;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v52340);
        v15724= Kernel.cfalse;
        for (START(OBJECT(bag,v45520)); NEXT(v52340);)
        if (c_func_any(v52340) != CTRUE)
         { v15724 = Kernel.ctrue;
          ClEnv->cHandle = loop_handle;break;}
        else ;}
      Result = not_any(v15724);
      }
    else if (INHERIT(OWNER(v45520),Language._Construct))
     { if (((INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Set)) || 
            (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._List))) || 
          (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Tuple)))
       { ClaireBoolean *v_and;
        { v_and = (((CL_INT)OBJECT(Construct,v45520)->args->length < 15) ? CTRUE : CFALSE);
          if (v_and == CFALSE) Result =CFALSE; 
          else { { OID  v16685;
              { ClaireBoolean * v5729;{ OID  v18607;
                  { set * v5731;{ set * v20739 = set::empty(Kernel.emptySet);
                      { CL_INT loop_handle = ClEnv->cHandle;
                        OID gc_local;
                        ITERATE(v52340);
                        bag *v52340_support;
                        v52340_support = GC_OBJECT(list,OBJECT(Construct,v45520)->args);
                        for (START(v52340_support); NEXT(v52340);)
                        if (c_func_any(v52340) != CTRUE)
                         v20739->addFast((OID)v52340);
                        }
                      v5731 = GC_OBJECT(set,v20739);
                      }
                    
                    v18607=_oid_(v5731);}
                  v5729 = boolean_I_any(v18607);
                  }
                
                v16685=_oid_(v5729);}
              v_and = ((v16685 != Kernel.ctrue) ? CTRUE : CFALSE);
              }
            if (v_and == CFALSE) Result =CFALSE; 
            else Result = CTRUE;}
          }
        }
      else Result = CFALSE;
        }
    else if (INHERIT(OWNER(v45520),Language._If))
     { ClaireBoolean *v_and;
      { v_and = c_func_any(GC_OID(OBJECT(If,v45520)->test));
        if (v_and == CFALSE) Result =CFALSE; 
        else { v_and = c_func_any(GC_OID(OBJECT(If,v45520)->arg));
          if (v_and == CFALSE) Result =CFALSE; 
          else { v_and = c_func_any(GC_OID(OBJECT(If,v45520)->other));
            if (v_and == CFALSE) Result =CFALSE; 
            else { v_and = stupid_t_any2(GC_OID(OBJECT(If,v45520)->arg),GC_OID(OBJECT(If,v45520)->other));
              if (v_and == CFALSE) Result =CFALSE; 
              else { { CL_INT  v52333 = 4;
                  OID  v52340 = GC_OID(OBJECT(If,v45520)->other);
                  { OID v40982;{ CL_INT loop_handle = ClEnv->cHandle;
                      OID gc_local;
                      v40982= _oid_(CFALSE);
                      while (((CL_INT)v52333 > 0))
                      { GC_LOOP;
                        if (INHERIT(OWNER(v52340),Language._If))
                         { GC__OID(v52340 = OBJECT(If,v52340)->other, 1);
                          v52333= ((CL_INT)v52333-(CL_INT)1);
                          }
                        else { v40982 = Kernel.ctrue;
                            ClEnv->cHandle = loop_handle;break;}
                          GC_UNLOOP;POP_SIGNAL;}
                      }
                    
                    v_and=OBJECT(ClaireBoolean,v40982);}
                  }
                if (v_and == CFALSE) Result =CFALSE; 
                else Result = CTRUE;}
              }
            }
          }
        }
      }
    else if (INHERIT(OWNER(v45520),Language._Assign))
     Result = c_func_any(GC_OID(OBJECT(Assign,v45520)->arg));
    else if (INHERIT(OWNER(v45520),Language._Gassign))
     Result = c_func_any(GC_OID(OBJECT(Gassign,v45520)->arg));
    else if (INHERIT(OWNER(v45520),Optimize._to_protect))
     Result = c_func_any(GC_OID(OBJECT(Compile_to_protect,v45520)->arg));
    else if (INHERIT(OWNER(v45520),Language._And))
     Result = c_func_any(GC_OID(_oid_(OBJECT(And,v45520)->args)));
    else if (INHERIT(OWNER(v45520),Language._Or))
     Result = c_func_any(GC_OID(_oid_(OBJECT(Or,v45520)->args)));
    else if (INHERIT(OWNER(v45520),Language._Call))
     Result = c_func_any(GC_OID(_oid_(OBJECT(Call,v45520)->args)));
    else if (INHERIT(OWNER(v45520),Language._Call_method))
     Result = ((c_func_any(GC_OID(_oid_(OBJECT(Call_method,v45520)->args))) == CTRUE) ? ((_oid_(OBJECT(Call_method,v45520)->arg) != Generate._starclose_exception_star->value) ? CTRUE: CFALSE): CFALSE);
    else if (INHERIT(OWNER(v45520),Language._Call_slot))
     Result = c_func_any(GC_OID(OBJECT(Call_slot,v45520)->arg));
    else if (INHERIT(OWNER(v45520),Language._Call_table))
     Result = c_func_any(GC_OID(OBJECT(Call_table,v45520)->arg));
    else if (INHERIT(OWNER(v45520),Language._Call_array))
     Result = c_func_any(GC_OID(OBJECT(Call_array,v45520)->arg));
    else Result = ((INHERIT(OWNER(v45520),Language._Update)) ?
      ((c_func_any(GC_OID(OBJECT(Update,v45520)->value)) == CTRUE) ? ((c_func_any(GC_OID(OBJECT(Update,v45520)->arg)) == CTRUE) ? CTRUE: CFALSE): CFALSE) :
      ((INHERIT(OWNER(v45520),Language._Cast)) ?
        c_func_any(GC_OID(OBJECT(Cast,v45520)->arg)) :
        ((INHERIT(OWNER(v45520),Optimize._to_C)) ?
          c_func_any(GC_OID(OBJECT(Compile_to_C,v45520)->arg)) :
          ((INHERIT(OWNER(v45520),Optimize._to_CL)) ?
            c_func_any(GC_OID(OBJECT(Compile_to_CL,v45520)->arg)) :
            ((INHERIT(OWNER(v45520),Kernel._thing)) ? CTRUE : 
            ((INHERIT(OWNER(v45520),Kernel._integer)) ? CTRUE : 
            ((Kernel._string == OWNER(v45520)) ? CTRUE : 
            ((INHERIT(OWNER(v45520),Kernel._char)) ? CTRUE : 
            ((Kernel._float == OWNER(v45520)) ? CTRUE : 
            ((INHERIT(OWNER(v45520),Language._Variable)) ? CTRUE : 
            ((INHERIT(OWNER(v45520),Core._global_variable)) ? CTRUE : 
            ((INHERIT(OWNER(v45520),Kernel._function)) ? CTRUE : 
            ((INHERIT(OWNER(v45520),Kernel._symbol)) ? CTRUE : 
            ((v45520 == CNULL) ? CTRUE : 
            ((Kernel._boolean == OWNER(v45520)) ? CTRUE : 
            ((INHERIT(OWNER(v45520),Kernel._class)) ? CTRUE : 
            ((INHERIT(OWNER(v45520),Kernel._environment)) ? CTRUE : 
            CFALSE))))))))))))) ) ) ) );
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  expression_thing(thing *v45520,OID v43304)
{ (*Generate.produce)(Generate.PRODUCER->value,
    _oid_(v45520));
  POP_SIGNAL;}

void  expression_integer(int v45520,OID v43304)
{ princ_integer(v45520);
  POP_SIGNAL;}

void  expression_any(OID v45520,OID v43304)
{ (*Generate.produce)(Generate.PRODUCER->value,
    v45520);
  POP_SIGNAL;}

void  expression_string(char *v45520,OID v43304)
{ (*Generate.produce)(Generate.PRODUCER->value,
    _string_(v45520));
  POP_SIGNAL;}

void  expression_float_(OID v30161,OID v30162)
{ expression_float(float_v(v30161),v30162);}

void  expression_float(double v45520,OID v43304)
{ princ_float(v45520);
  POP_SIGNAL;}

void  expression_boolean(ClaireBoolean *v45520,OID v43304)
{ (*Generate.produce)(Generate.PRODUCER->value,
    _oid_(v45520));
  POP_SIGNAL;}

void  expression_environment(ClaireEnvironment *v45520,OID v43304)
{ (*Generate.produce)(Generate.PRODUCER->value,
    _oid_(v45520));
  POP_SIGNAL;}

void  expression_Variable(Variable *v45520,OID v43304)
{ (*Language.ident)(Generate.PRODUCER->value,
    _oid_(v45520));
  POP_SIGNAL;}

void  expression_global_variable(global_variable *v45520,OID v43304)
{ (*Generate.produce)(Generate.PRODUCER->value,
    _oid_(v45520));
  POP_SIGNAL;}

void  expression_Set(Set *v45520,OID v43304)
{ GC_BIND;
  { OID  v22451;
    { if (((v45520->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       v22451 = _oid_(v45520->of);
      else v22451 = _oid_(Kernel._void);
        GC_OID(v22451);}
    (*Generate.bag_expression)(Generate.PRODUCER->value,
      _oid_(Kernel._set),
      GC_OID(_oid_(v45520->args)),
      v22451,
      v43304);
    }
  GC_UNBIND; POP_SIGNAL;}

void  expression_set2(set *v45520,OID v43304)
{ if ((v45520->length == 0) && 
      (equal(_oid_(of_bag(v45520)),_oid_(Kernel.emptySet)) == CTRUE))
   princ_string("Kernel.emptySet");
  else (*Generate.bag_expression)(Generate.PRODUCER->value,
      _oid_(Kernel._set),
      _oid_(v45520),
      _oid_(of_bag(v45520)),
      v43304);
    POP_SIGNAL;}

void  expression_Tuple(Tuple *v45520,OID v43304)
{ GC_BIND;
  (*Generate.bag_expression)(Generate.PRODUCER->value,
    _oid_(Kernel._tuple),
    GC_OID(_oid_(v45520->args)),
    _oid_(Kernel._void),
    v43304);
  GC_UNBIND; POP_SIGNAL;}

void  expression_tuple(tuple *v45520,OID v43304)
{ (*Generate.bag_expression)(Generate.PRODUCER->value,
    _oid_(Kernel._tuple),
    _oid_(v45520),
    _oid_(Kernel._void),
    v43304);
  POP_SIGNAL;}

void  expression_List(List *v45520,OID v43304)
{ GC_BIND;
  { OID  v43593;
    { if (((v45520->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       v43593 = _oid_(v45520->of);
      else v43593 = _oid_(Kernel._void);
        GC_OID(v43593);}
    (*Generate.bag_expression)(Generate.PRODUCER->value,
      _oid_(Kernel._list),
      GC_OID(_oid_(v45520->args)),
      v43593,
      v43304);
    }
  GC_UNBIND; POP_SIGNAL;}

void  expression_list(list *v45520,OID v43304)
{ if ((v45520->length == 0) && 
      (equal(_oid_(of_bag(v45520)),_oid_(Kernel.emptySet)) == CTRUE))
   princ_string("Kernel.nil");
  else (*Generate.bag_expression)(Generate.PRODUCER->value,
      _oid_(Kernel._list),
      _oid_(v45520),
      _oid_(of_bag(v45520)),
      v43304);
    POP_SIGNAL;}

ClaireBoolean * debug_call_intro_Complex_instruction1(Complex_instruction *v45520)
{ GC_BIND;
  { ClaireBoolean *Result ;
    { ClaireBoolean * g1811I;
      { ClaireBoolean *v_and;
        { v_and = boolean_I_any((*Kernel.location)(_oid_(v45520)));
          if (v_and == CFALSE) g1811I =CFALSE; 
          else { v_and = OBJECT(ClaireBoolean,Optimize._starin_c_func_star->value);
            if (v_and == CFALSE) g1811I =CFALSE; 
            else { { OID  v45515;
                if (INHERIT(owner_any((*(OBJECT(bag,(*Core.args)(_oid_(v45520)))))[1]),Optimize._to_CL))
                 v45515 = (((*Kernel.arg)((*(OBJECT(bag,(*Core.args)(_oid_(v45520)))))[1]) == _oid_(ClEnv)) ? Kernel.ctrue : Kernel.cfalse);
                else v45515 = Kernel.cfalse;
                  v_and = not_any(v45515);
                }
              if (v_and == CFALSE) g1811I =CFALSE; 
              else { v_and = ((Kernel._method == OWNER(Optimize.OPT->in_method)) ?
                  need_debug_ask_any(Optimize.OPT->in_method) :
                  CFALSE );
                if (v_and == CFALSE) g1811I =CFALSE; 
                else g1811I = CTRUE;}
              }
            }
          }
        }
      
      if (g1811I == CTRUE) if ((boolean_I_any(Generate._stardebug_calls_star->value) != CTRUE) || 
            (equal(GC_OID((*Kernel.location)(GC_OID(last_list(OBJECT(list,Generate._stardebug_calls_star->value))))),GC_OID((*Kernel.location)(_oid_(v45520)))) != CTRUE))
         { GC_OBJECT(list,OBJECT(list,Generate._stardebug_calls_star->value))->addFast((OID)_oid_(v45520));
          princ_string("DB_CALL");
          { ClaireClass * v49620;
            { ClaireObject *V_CC ;
              if (INHERIT(v45520->isa,Language._Call_method))
               V_CC = psort_any(_oid_(CLREAD(Call_method,v45520,arg)->range));
              else if (INHERIT(v45520->isa,Language._Call))
               V_CC = class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(_oid_(v45520)))));
              else V_CC = CFALSE;
                v49620= (ClaireClass *) V_CC;}
            if (v49620 == Kernel._void)
             princ_string("_VOID");
            }
          princ_string("(DB");
          princ_string(CL_Oid(_oid_(v45520)));
          princ_string(",");
          Result = CTRUE;
          }
        else Result = CFALSE;
          else Result = CFALSE;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  debug_call_end_void1()
{ princ_string(")");
  POP_SIGNAL;}

void  expression_Call2(Call *v45520,OID v43304)
{ { ClaireBoolean * v13003 = debug_call_intro_Complex_instruction1(v45520);
    (*Generate.inline_exp)(Generate.PRODUCER->value,
      _oid_(v45520),
      v43304);
    if (v13003 == CTRUE)
     (*Generate.debug_call_end)(_oid_(v45520));
    }
  POP_SIGNAL;}

void  expression_Call_method12(Call_method1 *v45520,OID v43304)
{ { ClaireBoolean * v13003 = ((v45520->arg->selector != Core.externC) ?
      debug_call_intro_Complex_instruction1(v45520) :
      CFALSE );
    (*Generate.inline_exp)(Generate.PRODUCER->value,
      _oid_(v45520),
      v43304);
    if (v13003 == CTRUE)
     (*Generate.debug_call_end)(_oid_(v45520));
    }
  POP_SIGNAL;}

void  expression_Call_method22(Call_method2 *v45520,OID v43304)
{ { ClaireBoolean * v13003 = debug_call_intro_Complex_instruction1(v45520);
    (*Generate.inline_exp)(Generate.PRODUCER->value,
      _oid_(v45520),
      v43304);
    if (v13003 == CTRUE)
     (*Generate.debug_call_end)(_oid_(v45520));
    }
  POP_SIGNAL;}

void  expression_Call_method2(Call_method *v45520,OID v43304)
{ { ClaireBoolean * v13003 = debug_call_intro_Complex_instruction1(v45520);
    (*Generate.inline_exp)(Generate.PRODUCER->value,
      _oid_(v45520),
      v43304);
    if (v13003 == CTRUE)
     (*Generate.debug_call_end)(_oid_(v45520));
    }
  POP_SIGNAL;}

void  bexpression_any(OID v45520,OID v43304)
{ if (INHERIT(OWNER(v45520),Language._Assign))
   { princ_string("(");
    expression_Assign(OBJECT(Assign,v45520),v43304);
    princ_string(")");
    }
  else if (INHERIT(OWNER(v45520),Optimize._to_C))
   { princ_string("(");
    (*Generate.expression)(v45520,
      v43304);
    princ_string(")");
    }
  else if (INHERIT(OWNER(v45520),Kernel._integer))
   { if (v45520 < 0)
     { princ_string("((CL_INT)");
      expression_integer(v45520,v43304);
      princ_string(")");
      }
    else expression_integer(v45520,v43304);
      }
  else if (Kernel._float == OWNER(v45520))
   { if (float_v(v45520) < 0.0)
     { princ_string("(");
      expression_float(float_v(v45520),v43304);
      princ_string(")");
      }
    else expression_float(float_v(v45520),v43304);
      }
  else (*Generate.expression)(v45520,
      v43304);
    POP_SIGNAL;}

void  expression_If(If *v45520,OID v43304)
{ GC_BIND;
  princ_string("(");
  (*Optimize.bool_exp)(GC_OID(v45520->test),
    Kernel.ctrue,
    v43304);
  princ_string(" ?");
  (Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
  breakline_void();
  (*Generate.expression)(GC_OID(v45520->arg),
    v43304);
  princ_string(" :");
  breakline_void();
  (*Generate.expression)(GC_OID(v45520->other),
    v43304);
  princ_string(" )");
  (Optimize.OPT->level = ((CL_INT)Optimize.OPT->level-(CL_INT)1));
  GC_UNBIND; POP_SIGNAL;}

void  expression_Assign(Assign *v45520,OID v43304)
{ GC_BIND;
  { OID  v52340 = GC_OID(v45520->arg);
    OID  v52338 = GC_OID(v45520->var);
    ClaireBoolean * v49119 = (((OBJECT(ClaireBoolean,Optimize._starin_c_func_star->value)) == CTRUE) ? (((Kernel._method == OWNER(Optimize.OPT->in_method)) && ((need_debug_ask_any(GC_OID(Optimize.OPT->in_method)) == CTRUE) && 
        (contain_ask_list(OBJECT(list,Optimize._stardebug_build_star->value),v52338) == CTRUE))) ? CTRUE: CFALSE): CFALSE);
    if (v49119 == CTRUE)
     princ_string("DB_UPDATE((");
    if ((INHERIT(OWNER(v52340),Language._Call_method2)) && ((_oid_(OBJECT(Call_method,v52340)->arg) == Generate._star_plus_integer_star->value) && 
        ((equal((*(OBJECT(Call_method,v52340)->args))[1],v45520->var) == CTRUE) && 
          ((*(OBJECT(Call_method,v52340)->args))[2] == ((OID)1)))))
     { princ_string("++");
      (*Generate.expression)(v52338,
        v43304);
      }
    else if ((boolean_I_any(v43304) == CTRUE) && 
        ((Optimize.OPT->loop_gc == CTRUE) && 
          (inner2outer_ask_any(v52340) == CTRUE)))
     { OID  v48398;
      { if (INHERIT(OWNER(v52340),Optimize._to_protect))
         v48398 = OBJECT(Compile_to_protect,v52340)->arg;
        else v48398 = v52340;
          GC_OID(v48398);}
      (*Generate.gc_protection_exp)(Generate.PRODUCER->value,
        v52338,
        Kernel.ctrue,
        v48398,
        v43304);
      }
    else (*Generate.exp_Assign)(Generate.PRODUCER->value,
        _oid_(v45520),
        v43304);
      if (v49119 == CTRUE)
     { princ_string("),");
      print_any(((OID)OBJECT(Variable,v52338)->dindex));
      princ_string(",");
      (*Generate.expression)(v52338,
        Kernel.cfalse);
      princ_string(",");
      { ClaireClass * v52335 = OBJECT(ClaireClass,(*Kernel.sort_I)(GC_OID((*Kernel.range)(v52338))));
        if (((v52335 == Kernel._any) && 
              ((*Kernel.range)(v52338) != _oid_(Kernel._float))) || 
            (v52335 == Kernel._integer))
         (*Generate.expression)(v52338,
          Kernel.cfalse);
        else { OID  v49359;
            if ((*Kernel.range)(v52338) == _oid_(Kernel._float))
             v49359 = _oid_(Kernel._float);
            else v49359 = _oid_(v52335);
              (*Generate.to_cl)(Generate.PRODUCER->value,
              v52338,
              v49359,
              Kernel.cfalse);
            }
          }
      princ_string(")");
      }
    else ;}
  GC_UNBIND; POP_SIGNAL;}

void  expression_to_protect(Compile_to_protect *v45520,OID v43304)
{ (*Generate.exp_to_protect)(Generate.PRODUCER->value,
    _oid_(v45520),
    v43304);
  POP_SIGNAL;}

char * gc_protect_class(ClaireClass *v52319)
{ (OBJECT(Generate_producer,Generate.PRODUCER->value)->stat = ((CL_INT)OBJECT(Generate_producer,Generate.PRODUCER->value)->stat+(CL_INT)1));
  { char *Result ;
    if (v52319 == Kernel._any)
     Result = "GC_OID";
    else if (v52319 == Kernel._string)
     Result = "GC_STRING";
    else if (v52319 == Kernel._array)
     Result = "GC_ARRAY";
    else if (INHERIT(v52319,Kernel._object))
     Result = "GC_OBJECT";
    else { (OBJECT(Generate_producer,Generate.PRODUCER->value)->stat = ((CL_INT)OBJECT(Generate_producer,Generate.PRODUCER->value)->stat-(CL_INT)1));
        Result = "";
        }
      POP_SIGNAL; return (Result);}
  }

void  expression_Gassign(Gassign *v45520,OID v43304)
{ (*Generate.gassign)(Generate.PRODUCER->value,
    _oid_(v45520),
    v43304);
  POP_SIGNAL;}

void  expression_And(And *v45520,OID v43304)
{ GC_BIND;
  { ClaireBoolean * v52318 = (((CL_INT)v45520->args->length > 5) ? CTRUE : CFALSE);
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52340);
      for (START(v45520->args); NEXT(v52340);)
      { princ_string("(");
        (*Optimize.bool_exp)(v52340,
          Kernel.ctrue,
          v43304);
        princ_string(" ? ");
        if (v52318 == CTRUE)
         breakline_void();
        }
      }
    expression_boolean(CTRUE,v43304);
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52340);
      for (START(v45520->args); NEXT(v52340);)
      { princ_string(": ");
        expression_boolean(CFALSE,v43304);
        princ_string(")");
        }
      }
    }
  GC_UNBIND; POP_SIGNAL;}

void  expression_Or(Or *v45520,OID v43304)
{ GC_BIND;
  { ClaireBoolean * v52318 = (((CL_INT)v45520->args->length > 5) ? CTRUE : CFALSE);
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52340);
      for (START(v45520->args); NEXT(v52340);)
      { princ_string("(");
        (*Optimize.bool_exp)(v52340,
          Kernel.ctrue,
          v43304);
        princ_string(" ? ");
        expression_boolean(CTRUE,v43304);
        princ_string(" : ");
        if (v52318 == CTRUE)
         breakline_void();
        }
      }
    expression_boolean(CFALSE,v43304);
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52340);
      for (START(v45520->args); NEXT(v52340);)
      princ_string(")");
      }
    }
  GC_UNBIND; POP_SIGNAL;}

void  expression_to_CL(Compile_to_CL *v45520,OID v43304)
{ GC_BIND;
  (*Generate.to_cl)(Generate.PRODUCER->value,
    v45520->arg,
    _oid_(v45520->set_arg),
    v43304);
  GC_UNBIND; POP_SIGNAL;}

void  expression_to_C(Compile_to_C *v45520,OID v43304)
{ GC_BIND;
  (*Generate.to_c)(Generate.PRODUCER->value,
    v45520->arg,
    _oid_(v45520->set_arg),
    v43304);
  GC_UNBIND; POP_SIGNAL;}

void  expression_C_cast(Compile_C_cast *v45520,OID v43304)
{ (*Kernel.cast_I)(Generate.PRODUCER->value,
    _oid_(v45520),
    v43304);
  POP_SIGNAL;}

void  expression_Call_slot(Call_slot *v45520,OID v43304)
{ (*Generate.call_slot)(Generate.PRODUCER->value,
    _oid_(v45520),
    v43304);
  POP_SIGNAL;}

void  expression_Call_table(Call_table *v45520,OID v43304)
{ (*Generate.call_table)(Generate.PRODUCER->value,
    _oid_(v45520),
    v43304);
  POP_SIGNAL;}

void  expression_Call_array(Call_array *v45520,OID v43304)
{ (*Generate.call_array)(Generate.PRODUCER->value,
    _oid_(v45520),
    v43304);
  POP_SIGNAL;}

void  expression_Update(Update *v45520,OID v43304)
{ (*Generate.update)(Generate.PRODUCER->value,
    _oid_(v45520),
    v43304);
  POP_SIGNAL;}

void  sign_equal_boolean(ClaireBoolean *v45520)
{ if (v45520 == CTRUE)
   princ_string("==");
  else princ_string("!=");
    POP_SIGNAL;}

void  sign_or_boolean(ClaireBoolean *v45520)
{ if (v45520 == CTRUE)
   princ_string("||");
  else princ_string("&&");
    POP_SIGNAL;}

void  bool_exp_any_Generate(OID v45520,ClaireBoolean *v31471,OID v43304)
{ any_bool_exp_any(v45520,v31471,v43304,not_any(_oid_(((INHERIT(OWNER(v45520),Core._global_variable)) ? ((nativeVar_ask_global_variable(OBJECT(global_variable,v45520)) != CTRUE) ? CTRUE: CFALSE): CFALSE))));
  POP_SIGNAL;}

void  any_bool_exp_any(OID v45520,ClaireBoolean *v31471,OID v43304,ClaireBoolean *v24003)
{ princ_string("(");
  bexpression_any(v45520,v43304);
  princ_string(" ");
  if (v31471 != CTRUE)
   princ_string("!=");
  else princ_string("==");
    princ_string(" ");
  if (v24003 != CTRUE)
   (*Generate.to_cl)(Generate.PRODUCER->value,
    Kernel.ctrue,
    _oid_(Kernel._boolean),
    v43304);
  else expression_boolean(CTRUE,v43304);
    princ_string(")");
  POP_SIGNAL;}

void  bool_exp_to_CL_Generate(Compile_to_CL *v45520,ClaireBoolean *v31471,OID v43304)
{ GC_BIND;
  (*Optimize.bool_exp)(v45520->arg,
    _oid_(v31471),
    v43304);
  GC_UNBIND; POP_SIGNAL;}

void  bool_exp_If_Generate(If *v45520,ClaireBoolean *v31471,OID v43304)
{ GC_BIND;
  if (boolean_I_any(v45520->other) == CTRUE)
   { princ_string("(");
    (*Optimize.bool_exp)(v45520->test,
      Kernel.ctrue,
      v43304);
    princ_string(" ? ");
    (*Optimize.bool_exp)(v45520->arg,
      _oid_(v31471),
      v43304);
    princ_string(" : ");
    (*Optimize.bool_exp)(v45520->other,
      _oid_(v31471),
      v43304);
    princ_string(")");
    }
  else { princ_string("(");
      (*Optimize.bool_exp)(v45520->test,
        _oid_(v31471),
        v43304);
      princ_string(" ");
      sign_or_boolean(not_any(_oid_(v31471)));
      princ_string(" ");
      (*Optimize.bool_exp)(v45520->arg,
        _oid_(v31471),
        v43304);
      princ_string(")");
      }
    GC_UNBIND; POP_SIGNAL;}

void  bool_exp_And_Generate(And *v45520,ClaireBoolean *v31471,OID v43304)
{ GC_BIND;
  { list * v52331 = GC_OBJECT(list,v45520->args);
    CL_INT  v52329 = v52331->length;
    CL_INT  v52333 = 0;
    CL_INT  v47211 = Optimize.OPT->level;
    (Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52340);
      for (START(v52331); NEXT(v52340);)
      { ++v52333;
        if (v52333 == v52329)
         (*Optimize.bool_exp)(v52340,
          _oid_(v31471),
          v43304);
        else { princ_string("(");
            (*Optimize.bool_exp)(v52340,
              _oid_(v31471),
              v43304);
            princ_string(" ");
            sign_or_boolean(not_any(_oid_(v31471)));
            princ_string(" ");
            (Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
            breakline_void();
            }
          }
      }
    { CL_INT  v52340 = 2;
      CL_INT  v30217 = v52329;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)v52340 <= (CL_INT)v30217))
        { princ_string(")");
          ++v52340;
          POP_SIGNAL;}
        }
      }
    (Optimize.OPT->level = v47211);
    }
  GC_UNBIND; POP_SIGNAL;}

void  bool_exp_Or_Generate(Or *v45520,ClaireBoolean *v31471,OID v43304)
{ GC_BIND;
  { list * v52331 = GC_OBJECT(list,v45520->args);
    CL_INT  v52329 = v52331->length;
    CL_INT  v52333 = 0;
    CL_INT  v47211 = Optimize.OPT->level;
    (Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52340);
      for (START(v52331); NEXT(v52340);)
      { ++v52333;
        if (v52333 == v52329)
         (*Optimize.bool_exp)(v52340,
          _oid_(v31471),
          v43304);
        else { princ_string("(");
            (*Optimize.bool_exp)(v52340,
              _oid_(v31471),
              v43304);
            princ_string(" ");
            sign_or_boolean(v31471);
            princ_string(" ");
            (Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
            breakline_void();
            }
          }
      }
    { CL_INT  v52340 = 2;
      CL_INT  v30220 = v52329;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)v52340 <= (CL_INT)v30220))
        { princ_string(")");
          ++v52340;
          POP_SIGNAL;}
        }
      }
    (Optimize.OPT->level = v47211);
    }
  GC_UNBIND; POP_SIGNAL;}

void  bool_exp_Call_method1_Generate(Call_method1 *v45520,ClaireBoolean *v31471,OID v43304)
{ GC_BIND;
  { method * v52329 = v45520->arg;
    OID  v49012 = GC_OID((*(v45520->args))[1]);
    if (_oid_(v52329) == Generate._starnot_star->value)
     { if (INHERIT(OWNER(v49012),Optimize._to_CL))
       any_bool_exp_any(GC_OID((*Kernel.arg)(v49012)),not_any(_oid_(v31471)),v43304,CTRUE);
      else any_bool_exp_any(v49012,not_any(_oid_(v31471)),v43304,CFALSE);
        }
    else if (_oid_(v52329) == Generate._starknown_star->value)
     (*Generate.equal_exp)(Generate.PRODUCER->value,
      v49012,
      _oid_(not_any(_oid_(v31471))),
      CNULL,
      v43304);
    else if (_oid_(v52329) == Generate._starunknown_star->value)
     (*Generate.equal_exp)(Generate.PRODUCER->value,
      v49012,
      _oid_(v31471),
      CNULL,
      v43304);
    else if (_inf_equal_type(v52329->range,Kernel._boolean) == CTRUE)
     { princ_string("(");
      expression_Call_method12(v45520,v43304);
      princ_string(" ");
      sign_equal_boolean(v31471);
      princ_string(" ");
      expression_boolean(CTRUE,v43304);
      princ_string(")");
      }
    else { OID v_rec;
        v_rec = _oid_(v45520);
        PUSH(v_rec);
        v_rec = _oid_(v31471);
        PUSH(v_rec);
        v_rec = v43304;
        PUSH(v_rec);
        Optimize.bool_exp->super(Kernel._any,3);}
      }
  GC_UNBIND; POP_SIGNAL;}

void  bool_exp_Call_method2_Generate(Call_method2 *v45520,ClaireBoolean *v31471,OID v43304)
{ GC_BIND;
  { method * v52329 = v45520->arg;
    property * v52332 = v52329->selector;
    list * v24649 = GC_OBJECT(list,OBJECT(Generate_producer,Generate.PRODUCER->value)->open_comparators);
    OID  v49012 = GC_OID((*(v45520->args))[1]);
    OID  v49013 = GC_OID((*(v45520->args))[2]);
    if (v52332 == Core._I_equal)
     (*Generate.equal_exp)(Generate.PRODUCER->value,
      v49012,
      _oid_(not_any(_oid_(v31471))),
      v49013,
      Core.nil->value);
    else if (v52332 == Core.identical_ask)
     (*Generate.equal_exp)(Generate.PRODUCER->value,
      v49012,
      _oid_(v31471),
      v49013,
      Kernel.ctrue);
    else if (v52332 == Kernel._equal)
     (*Generate.equal_exp)(Generate.PRODUCER->value,
      v49012,
      _oid_(v31471),
      v49013,
      Core.nil->value);
    else if ((v24649->memq(_oid_(v52332)) == CTRUE) && 
        ((domain_I_restriction(v52329) == Kernel._integer) || 
            (domain_I_restriction(v52329) == Kernel._float)))
     { princ_string("(");
      if ((*Optimize.c_type)(v49012) == _oid_(Kernel._integer))
       princ_string("(CL_INT)");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(" ");
      if (v31471 == CTRUE)
       print_any(_oid_(v52332));
      else print_any((*(v24649))[((CL_INT)mod_integer(((CL_INT)index_list(v24649,_oid_(v52332))+(CL_INT)1),4)+(CL_INT)1)]);
        princ_string(" ");
      if ((*Optimize.c_type)(v49013) == _oid_(Kernel._integer))
       princ_string("(CL_INT)");
      (*Generate.expression)(v49013,
        v43304);
      princ_string(")");
      }
    else if (_oid_(v52329) == Generate._starnth_integer_star->value)
     { princ_string("(");
      if (v31471 != CTRUE)
       princ_string("!");
      (*Generate.bitvector_exp)(Generate.PRODUCER->value,
        v49012,
        v49013,
        v43304);
      princ_string(")");
      }
    else if ((v52332 == Core.inherit_ask) && 
        (domain_I_restriction(v52329) == Kernel._class))
     { princ_string("(");
      if (v31471 != CTRUE)
       princ_string("!");
      (*Generate.inherit_exp)(Generate.PRODUCER->value,
        v49012,
        v49013,
        v43304);
      princ_string(")");
      }
    else if (_inf_equal_type(v52329->range,Kernel._boolean) == CTRUE)
     { princ_string("(");
      expression_Call_method22(v45520,v43304);
      princ_string(" ");
      sign_equal_boolean(v31471);
      princ_string(" ");
      expression_boolean(CTRUE,v43304);
      princ_string(")");
      }
    else { OID v_rec;
        v_rec = _oid_(v45520);
        PUSH(v_rec);
        v_rec = _oid_(v31471);
        PUSH(v_rec);
        v_rec = v43304;
        PUSH(v_rec);
        Optimize.bool_exp->super(Kernel._any,3);}
      }
  GC_UNBIND; POP_SIGNAL;}

ClaireBoolean * bool_exp_ask_any(OID v52340)
{ GC_BIND;
  { ClaireBoolean *Result ;
    if (INHERIT(OWNER(v52340),Optimize._to_CL))
     Result = bool_exp_ask_any(OBJECT(Compile_to_CL,v52340)->arg);
    else if (INHERIT(OWNER(v52340),Language._Call_method))
     { property * v52332 = OBJECT(Call_method,v52340)->arg->selector;
      Result = (((OBJECT(Call_method,v52340)->arg->range == Kernel._boolean) && 
          ((v52332 == Kernel._equal) || 
              ((v52332 == Core._I_equal) || 
                ((v52332 == Kernel._sup) || 
                  ((v52332 == Kernel._sup_equal) || 
                    ((v52332 == Kernel._inf) || 
                      (v52332 == Kernel._inf_equal))))))) ? CTRUE : (((v52332 == Core.NOT) && 
          (bool_exp_ask_any((*(OBJECT(Call_method,v52340)->args))[1]) == CTRUE)) ? CTRUE : CFALSE));
      }
    else Result = CFALSE;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  args_list_bag(bag *v45520,OID v43304,ClaireBoolean *v14866)
{ { ClaireBoolean * v29487 = CTRUE;
    if (v14866 == CTRUE)
     (Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v52340);
      for (START(v45520); NEXT(v52340);)
      if (v29487 == CTRUE)
       { (*Generate.expression)(v52340,
          v43304);
        v29487= CFALSE;
        }
      else { princ_string(",");
          if (v14866 == CTRUE)
           breakline_void();
          (*Generate.expression)(v52340,
            v43304);
          }
        }
    if (v14866 == CTRUE)
     (Optimize.OPT->level = ((CL_INT)Optimize.OPT->level-(CL_INT)1));
    }
  POP_SIGNAL;}

char * check_var_string(char *v45520,OID v52335,OID v43304)
{ { char *Result ;
    Result = (((equal(_string_(v45520),v52335) == CTRUE) || 
        (equal(_string_(v45520),v43304) == CTRUE)) ?
      append_string(v45520,"1") :
      v45520 );
    POP_SIGNAL; return (Result);}
  }

Variable * build_Variable_string(char *v52335,OID v52336)
{ POP_SIGNAL; return (Variable_I_symbol(symbol_I_string2(v52335),0,OBJECT(ClaireType,v52336)));}



