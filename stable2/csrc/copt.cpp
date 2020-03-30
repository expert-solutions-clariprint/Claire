/***** CLAIRE Compilation of file ./compile/copt.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:52 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>
#include <Optimize.h>
#include <Generate.h>
void  inline_exp_c_producer1(Generate_c_producer *v52319,Call_method1 *v45520,OID v43304)
{ GC_BIND;
  { method * v52329 = v45520->arg;
    property * v52332 = v52329->selector;
    OID  v49012 = GC_OID(car_list(v45520->args));
    if ((v52332 == Kernel._dash) && 
        ((domain_I_restriction(v52329) == Kernel._integer) || 
            (domain_I_restriction(v52329) == Kernel._float)))
     { princ_string("(-");
      bexpression_any(v49012,v43304);
      princ_string(")");
      }
    else if ((v52332 == Core.owner) && 
        (designated_ask_any(v49012) == CTRUE))
     { princ_string("OWNER(");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(")");
      }
    else if ((v52332 == Core.sqrt) && 
        (domain_I_restriction(v52329) == Kernel._float))
     { princ_string("sqrt(");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(")");
      }
    else if ((v52332 == Core.eval) && 
        (designated_ask_any(v49012) == CTRUE))
     { princ_string("OPT_EVAL(");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(")");
      }
    else if (v52332 == Core.externC)
     (*Kernel.princ)(v49012);
    else if ((_oid_(v52329) == Generate._starlength_bag_star->value) && 
        (designated_ask_any(v49012) == CTRUE))
     { (*Generate.expression)(v49012,
        v43304);
      princ_string("->length");
      }
    else if (_oid_(v52329) == Generate._starlength_string_star->value)
     { princ_string("LENGTH_STRING(");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(")");
      }
    else if ((v52332 == Kernel.integer_I) && 
        ((domain_I_restriction(v52329) == Kernel._char) && 
          (designated_ask_any(v49012) == CTRUE)))
     { (*Generate.expression)(v49012,
        v43304);
      princ_string("->ascii");
      }
    else if (_oid_(v52329) == Generate._starlength_array_star->value)
     { (*Generate.expression)(v49012,
        v43304);
      princ_string("[0]");
      }
    else if ((_oid_(v52329) == Generate._starnot_star->value) && 
        (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v49012))),Kernel._boolean) == CTRUE))
     { princ_string("((");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(" == Kernel.ctrue) ? CFALSE : CTRUE)");
      }
    else print_external_call_c_producer(v52319,v45520,v43304);
      }
  GC_UNBIND; POP_SIGNAL;}

void  inline_exp_c_producer2(Generate_c_producer *v52319,Call_method2 *v45520,OID v43304)
{ GC_BIND;
  { method * v52329 = v45520->arg;
    property * v52332 = v52329->selector;
    OID  v49012 = GC_OID((*(v45520->args))[1]);
    OID  v49013 = GC_OID((*(v45520->args))[2]);
    if (should_trace_ask_module1(Generate.it,4) == CTRUE)
     mtformat_module1(Generate.it,"inline_exp2: a1 = ~S, a2 = ~S \n",4,list::alloc(2,v49012,v49013));
    else ;if ((_oid_(v52329) == Generate._starmin_integer_star->value) && 
        ((designated_ask_any(v49012) == CTRUE) && 
          (designated_ask_any(v49013) == CTRUE)))
     { princ_string("((");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(" <= ");
      (*Generate.expression)(v49013,
        v43304);
      princ_string(") ? ");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(" : ");
      (*Generate.expression)(v49013,
        v43304);
      princ_string(")");
      }
    else if (_oid_(v52329) == Generate._starnth_char_star_star->value)
     { princ_string("_char_(");
      (*Generate.expression)(v49012,
        v43304);
      princ_string("[(CL_INT)(");
      (*Generate.expression)(v49013,
        v43304);
      princ_string(") - 1])");
      }
    else if (_oid_(v52329) == Generate._star_plus_char_star_star->value)
     { princ_string("(");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(" + ");
      (*Generate.expression)(v49013,
        v43304);
      princ_string(")");
      }
    else if ((_oid_(v52329) == Generate._starmax_integer_star->value) && 
        ((designated_ask_any(v49012) == CTRUE) && 
          (designated_ask_any(v49013) == CTRUE)))
     { princ_string("((");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(" <= ");
      (*Generate.expression)(v49013,
        v43304);
      princ_string(") ? ");
      (*Generate.expression)(v49013,
        v43304);
      princ_string(" : ");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(")");
      }
    else if ((v52332 == Core.class_I) && 
        (INHERIT(OWNER(v49012),Kernel._symbol)))
     { princ_string("(");
      ident_thing(defined_symbol(OBJECT(symbol,v49012)));
      princ_string("._");
      c_princ_string(string_v((*Kernel.string_I)(v49012)));
      princ_string(" = ClaireClass::make(");
      print_any(GC_OID((*Kernel.string_I)(v49012)));
      princ_string(",");
      (*Generate.expression)(v49013,
        v43304);
      princ_string(",");
      ident_thing(OBJECT(thing,(*Kernel.module_I)(v49012)));
      princ_string(".it))");
      }
    else if ((v52319->open_operators->memq(_oid_(v52332)) == CTRUE) && 
        (((v52332 != Kernel._7) || 
            (5 <= (CL_INT)Optimize.compiler->safety)) && 
          ((equal((*(v52329->domain))[1],(*(v52329->domain))[2]) == CTRUE) && 
            ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v49012))),Kernel._integer) == CTRUE) || 
                (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v49012))),Kernel._float) == CTRUE)))))
     { if (((CL_INT)Optimize.compiler->safety < 2) && 
          (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v49012))),Kernel._integer) == CTRUE))
       princ_string("_integer_");
      princ_string("(");
      if (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v49012))),Kernel._integer) == CTRUE)
       princ_string("(CL_INT)");
      bexpression_any(v49012,v43304);
      princ_string(string_I_symbol(v52332->name));
      if (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v49013))),Kernel._integer) == CTRUE)
       princ_string("(CL_INT)");
      bexpression_any(v49013,v43304);
      princ_string(")");
      }
    else if ((_oid_(v52329) == Generate._starcontain_star->value) && 
        (identifiable_ask_any(v49013) == CTRUE))
     { (*Generate.expression)(v49012,
        v43304);
      princ_string("->memq(");
      (*Generate.expression)(v49013,
        v43304);
      princ_string(")");
      }
    else if (((_oid_(v52329) == Generate._starnth_list_star->value) && 
          (2 <= (CL_INT)Optimize.compiler->safety)) || 
        (_oid_(v52329) == Generate._starnth_1_bag_star->value))
     { princ_string("(*(");
      (*Generate.expression)(v49012,
        v43304);
      princ_string("))[");
      (*Generate.expression)(v49013,
        v43304);
      princ_string("]");
      }
    else if ((v52332 == Kernel.add_I) && 
        (_inf_equal_type(domain_I_restriction(v52329),Kernel._bag) == CTRUE))
     { (*Generate.expression)(v49012,
        v43304);
      princ_string("->addFast((OID)");
      (*Generate.expression)(v49013,
        v43304);
      princ_string(")");
      }
    else if ((_oid_(v52329) == Generate._starnth_string_star->value) && 
        (2 <= (CL_INT)Optimize.compiler->safety))
     { princ_string("_char_(");
      (*Generate.expression)(v49012,
        v43304);
      princ_string("[");
      (*Generate.expression)(v49013,
        v43304);
      princ_string(" - 1])");
      }
    else if (v52329->selector == Core.identical_ask)
     { princ_string("(");
      (*Optimize.bool_exp)(_oid_(v45520),
        Kernel.ctrue,
        v43304);
      princ_string(" ? CTRUE : CFALSE)");
      }
    else if (v52329->selector == Core.externC)
     { princ_string("(");
      (*Generate.interface_I)(Generate.PRODUCER->value,
        v49013);
      princ_string(")(");
      (*Kernel.princ)(v49012);
      princ_string(")");
      }
    else if ((v52332 == Core.inlineok_ask) && 
        (Kernel._string == OWNER(v49013)))
     { (*Generate.expression)(v49012,
        v43304);
      princ_string("->inlineDef(");
      print_any(v49013);
      princ_string(")");
      }
    else print_external_call_c_producer(v52319,v45520,v43304);
      }
  GC_UNBIND; POP_SIGNAL;}

void  inline_exp_c_producer3(Generate_c_producer *v52319,Call_method *v45520,OID v43304)
{ GC_BIND;
  { method * v52329 = v45520->arg;
    ClaireBoolean * v52318 = Optimize.OPT->alloc_stack;
    OID  v49012 = GC_OID((*(v45520->args))[1]);
    OID  v49013 = GC_OID((*(v45520->args))[2]);
    OID  v49014 = GC_OID((*(v45520->args))[3]);
    (Optimize.OPT->alloc_stack = CFALSE);
    if (should_trace_ask_module1(Generate.it,4) == CTRUE)
     mtformat_module1(Generate.it,"inline_exp: a1 = ~S, a2 = ~S, a3 = ~S \n",4,list::alloc(3,v49012,
      v49013,
      v49014));
    else ;if ((_oid_(v52329) == Generate._starnth_equal_list_star->value) && 
        (3 <= (CL_INT)Optimize.compiler->safety))
     { princ_string("((*(");
      (*Generate.expression)(v49012,
        v43304);
      princ_string("))[");
      (*Generate.expression)(v49013,
        v43304);
      princ_string("]=");
      (*Generate.expression)(v49014,
        v43304);
      princ_string(")");
      }
    else if ((domain_I_restriction(v52329) == Kernel._string) && 
        (((v52329->selector == Kernel.nth_equal) && 
              (2 <= (CL_INT)Optimize.compiler->safety)) || 
            (v52329->selector == Kernel.nth_put)))
     { princ_string("(");
      (*Generate.expression)(v49012,
        v43304);
      princ_string("[");
      (*Generate.expression)(v49013,
        v43304);
      princ_string(" - 1] = (unsigned char) ");
      (*Generate.expression)(v49014,
        v43304);
      princ_string("->ascii)");
      }
    else if (_oid_(v52329) == Generate._starnth_1_string_star->value)
     { princ_string("_char_(");
      (*Generate.expression)(v49012,
        v43304);
      princ_string("[");
      (*Generate.expression)(v49013,
        v43304);
      princ_string(" - 1])");
      }
    else if ((v52329->selector == Kernel.store) && 
        ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v49012))),Kernel._list) == CTRUE) && 
          (((v45520->args->length == 4) && 
                ((*(v45520->args))[4] == Kernel.ctrue)) || 
              (v45520->args->length == 3))))
     { princ_string("STOREI((*");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(")[");
      (*Generate.expression)(v49013,
        v43304);
      princ_string("],");
      (*Generate.expression)(v49014,
        v43304);
      princ_string(")");
      }
    else if ((v52329->selector == Kernel.store) && 
        ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v49012))),Kernel._array) == CTRUE) && 
          ((equal(_oid_(_exp_type(GC_OBJECT(ClaireType,member_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v49012))))),Kernel._float)),_oid_(Kernel.emptySet)) == CTRUE) && 
            (((v45520->args->length == 4) && 
                  ((*(v45520->args))[4] == Kernel.ctrue)) || 
                (v45520->args->length == 3)))))
     { princ_string("STOREI(");
      (*Generate.expression)(v49012,
        v43304);
      princ_string("[");
      (*Generate.expression)(v49013,
        v43304);
      princ_string("],");
      (*Generate.expression)(v49014,
        v43304);
      princ_string(")");
      }
    else if ((v52329->selector == Kernel.add_slot) && 
        (INHERIT(owner_any(getC_any(v49012)),Kernel._class)))
     { princ_string("CL_ADD_SLOT(");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(",");
      class_princ_class(OBJECT(ClaireClass,getC_any(v49012)));
      princ_string(",");
      (*Generate.expression)(v49013,
        v43304);
      princ_string(",");
      ident_symbol(OBJECT(symbol,(*Kernel.name)(GC_OID(getC_any(v49013)))));
      princ_string(",");
      (*Generate.expression)(GC_OID(getC_any(v49014)),
        v43304);
      princ_string(",");
      (*Generate.expression)(GC_OID((*(v45520->args))[4]),
        v43304);
      princ_string(")");
      }
    else if (v52329->selector == Kernel.add_method)
     { if (INHERIT(OWNER(v49012),Kernel._property))
       { (*Generate.expression)(v49012,
          v43304);
        princ_string("->add");
        if ((CL_INT)v45520->args->length > 5)
         princ_string("Float");
        princ_string("Method(");
        signature_I_c_producer(v52319,v49013);
        princ_string(",");
        (*Generate.expression)(v49014,
          v43304);
        princ_string(",");
        breakline_void();
        princ_string("\t");
        bitvector_I_c_producer(v52319,GC_OID((*(v45520->args))[4]));
        princ_string(",");
        (*Generate.expression)(GC_OID((*(v45520->args))[5]),
          v43304);
        if ((CL_INT)v45520->args->length > 5)
         { princ_string(",");
          breakline_void();
          expression_any(_oid_(make_function_string(append_string(GC_STRING(string_v((*Kernel.string_I)(GC_OID((*(v45520->args))[5])))),"_"))),v43304);
          }
        princ_string(")");
        }
      else { princ_string("add_method_property(");
          args_list_bag(GC_OBJECT(list,v45520->args),v43304,CTRUE);
          princ_string(")");
          }
        }
    else { (Optimize.OPT->alloc_stack = v52318);
        print_external_call_c_producer(v52319,v45520,v43304);
        }
      (Optimize.OPT->alloc_stack = v52318);
    }
  GC_UNBIND; POP_SIGNAL;}

void  print_external_call_c_producer(Generate_c_producer *v52319,Call_method *v45520,OID v43304)
{ GC_BIND;
  { method * v52329 = v45520->arg;
    list * v52331 = GC_OBJECT(list,v45520->args);
    CL_INT  v52333 = 1;
    list * v49404 = v52329->domain;
    ClaireBoolean * v49119 = Optimize.compiler->debug_ask->memq(_oid_(v52329->module_I));
    c_princ_function(OBJECT(ClaireFunction,(*Optimize.functional_I)(_oid_(v52329))));
    princ_string("(");
    if ((CL_INT)v52331->length > 4)
     (Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
    if ((v52331->length == 1) && 
        (domain_I_restriction(v52329) == Kernel._void))
     v52331= Kernel.nil;
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v52340);
      for (START(v52331); NEXT(v52340);)
      { if (v52333 != 1)
         { princ_string(",");
          if ((CL_INT)v52331->length > 4)
           breakline_void();
          }
        { ClaireClass * v49570 = psort_any((*(v49404))[v52333]);
          ClaireClass * v49571 = stupid_t_any1(v52340);
          if ((_inf_equalt_class(v49570,Kernel._object) == CTRUE) && 
              (_inf_equalt_class(v49571,v49570) != CTRUE))
           { princ_string("(");
            class_princ_class(v49570);
            princ_string(" *) ");
            }
          }
        (*Generate.expression)(v52340,
          v43304);
        ++v52333;
        }
      }
    princ_string(")");
    if ((INHERIT(v52329->range->isa,Kernel._tuple)) && 
        (Optimize.OPT->alloc_stack != CTRUE))
     princ_string("->copyIfNeeded()");
    if ((CL_INT)v52331->length > 4)
     (Optimize.OPT->level = ((CL_INT)Optimize.OPT->level-(CL_INT)1));
    }
  GC_UNBIND; POP_SIGNAL;}

void  inline_exp_c_producer5(Generate_c_producer *v52319,Call *v45520,OID v43304)
{ GC_BIND;
  { property * v52332 = v45520->selector;
    OID  v49012 = GC_OID(car_list(v45520->args));
    CL_INT  v52333 = v45520->args->length;
    if (v52332 == Core.get_stack)
     { princ_string("ClEnv->stack[");
      (*Generate.expression)(v49012,
        v43304);
      princ_string("]");
      }
    else if (v52332 == Optimize.safe)
     { CL_INT  v52341 = Optimize.compiler->safety;
      (Optimize.compiler->safety = 1);
      (*Generate.expression)(GC_OID((*(v45520->args))[1]),
        v43304);
      (Optimize.compiler->safety = v52341);
      }
    else if (v52332 == Core.base_I)
     princ_string("ClEnv->base");
    else if ((v52332 == Core.index_I) && 
        (v52333 == 1))
     princ_string("ClEnv->index");
    else if ((v52332 == Core.push_I) && 
        (v52333 == 1))
     { princ_string("PUSH(");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(")");
      }
    else if (v52332 == Core.put_stack)
     { princ_string("(ClEnv->stack[");
      (*Generate.expression)(v49012,
        v43304);
      princ_string("]=");
      (*Generate.expression)(GC_OID((*(v45520->args))[2]),
        v43304);
      princ_string(")");
      }
    else if (v52332 == Core.set_base)
     { princ_string("(ClEnv->base= ");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(")");
      }
    else if (v52332 == Kernel.set_index && v45520->args->length == 1)
     { princ_string("(ClEnv->index= ");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(")");
      }
    else if (v52332 == Optimize.object_I)
     { OID  v49013 = GC_OID((*(v45520->args))[2]);
      princ_string("(");
      ident_thing(defined_symbol(OBJECT(symbol,v49012)));
      princ_string(".");
      if (_inf_equal_type(OBJECT(ClaireType,v49013),Reader._reserved_keyword) == CTRUE)
       { princ_string("_cl_");
        c_princ_string(string_v((*Kernel.string_I)(v49012)));
        }
      else (*Language.ident)(v49012);
        princ_string(" = ");
      if ((v49013 == _oid_(Kernel._property)) && 
          (INHERIT(owner_any((*Kernel.value)(v49012)),Kernel._property)))
       { princ_string("property::make(");
        print_any(GC_OID((*Kernel.string_I)(v49012)));
        princ_string(",");
        princ_integer((*Kernel.open)(GC_OID((*Kernel.value)(v49012))));
        princ_string(",");
        expression_thing(OBJECT(thing,(*Kernel.module_I)(v49012)),Core.nil->value);
        princ_string(",");
        (*Generate.expression)(GC_OID((*Kernel.domain)(GC_OID((*Kernel.value)(v49012)))),
          Core.nil->value);
        princ_string(",");
        (*Kernel.princ)(GC_OID((*Kernel.dispatcher)(GC_OID((*Kernel.value)(v49012)))));
        princ_string(")");
        }
      else { princ_string("(");
          class_princ_class(OBJECT(ClaireClass,v49013));
          princ_string(" *) ");
          (*Generate.expression)(v49013,
            v43304);
          princ_string("->instantiate(");
          print_any(GC_OID((*Kernel.string_I)(v49012)));
          princ_string(",");
          expression_thing(OBJECT(thing,(*Kernel.module_I)(v49012)),Core.nil->value);
          princ_string(")");
          }
        princ_string(")");
      }
    else if (v52332 == Optimize.anyObject_I)
     { princ_string("((");
      class_princ_class(OBJECT(ClaireClass,v49012));
      princ_string(" *) (*");
      (*Generate.expression)(v49012,
        v43304);
      princ_string(")(");
      args_list_bag(GC_OBJECT(list,cdr_list(GC_OBJECT(list,v45520->args))),v43304,_sup_integer(v45520->args->length,2));
      princ_string("))");
      }
    else if ((OBJECT(ClaireBoolean,(*Generate.fcall_ask)(_oid_(v45520)))) == CTRUE)
     (*Generate.fcall_exp)(_oid_(v45520),
      v43304);
    else if ((CL_INT)v45520->args->length > 20)
     { if (v45520->selector == Kernel.store)
       { list * v52331 = GC_OBJECT(list,v45520->args);
        CL_INT  v52333 = v52331->length;
        CL_INT  v52329 = ((CL_INT)v52333/(CL_INT)10);
        princ_string("(");
        { CL_INT  v52325 = 0;
          CL_INT  v30402 = v52329;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)v52325 <= (CL_INT)v30402))
            { GC_LOOP;
              princ_string("(*");
              expression_thing(Kernel.store,v43304);
              princ_string(")(");
              { list * v57444;
                { list * v54447 = list::empty(Kernel.emptySet);
                  { CL_INT  v52326 = ((CL_INT)((CL_INT)v52325*(CL_INT)10)+(CL_INT)1);
                    CL_INT  v30403 = ((v52325 == v52329) ?
                      v52333 :
                      ((CL_INT)((CL_INT)v52325*(CL_INT)10)+(CL_INT)10) );
                    { CL_INT loop_handle = ClEnv->cHandle;
                      OID gc_local;
                      while (((CL_INT)v52326 <= (CL_INT)v30403))
                      { v54447->addFast((OID)(*(v52331))[v52326]);
                        ++v52326;
                        POP_SIGNAL;}
                      }
                    }
                  v57444 = GC_OBJECT(list,v54447);
                  }
                args_list_bag(v57444,v43304,CTRUE);
                }
              princ_string(")");
              if (v52325 != v52329)
               princ_string(",");
              ++v52325;
              GC_UNLOOP;POP_SIGNAL;}
            }
          }
        princ_string(")");
        }
      else close_exception(((general_error *) (*Core._general_error)(_string_("[216] ~S has more than 20 parameters"),
          _oid_(list::alloc(1,_oid_(v45520))))));
        }
    else { princ_string("(*");
        expression_thing(v45520->selector,v43304);
        princ_string(")(");
        args_list_bag(GC_OBJECT(list,v45520->args),v43304,_sup_integer(v45520->args->length,1));
        princ_string(")");
        }
      }
  GC_UNBIND; POP_SIGNAL;}

ClaireBoolean * fcall_ask_Call2_Generate(Call *v52340)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { ClaireBoolean *Result ;
    { property * v52332 = v52340->selector;
      OID  v49012 = GC_OID((*(v52340->args))[1]);
      CL_INT  v46853;
      { list * v58407;
        { bag * v21807 = v52340->args;
          list * v26756 = ((list *) empty_bag(v21807));
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v52341);
            for (START(v21807); NEXT(v52341);)
            if ((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v52341))) == CTRUE)
             v26756->addFast((OID)v52341);
            }
          v58407 = GC_OBJECT(list,v26756);
          }
        v46853 = v58407->length;
        }
      { ClaireBoolean *v_and;
        { v_and = ((designated_ask_any(v49012) == CTRUE) ? CTRUE : (((CL_INT)v52332->dispatcher > 0) ? CTRUE : CFALSE));
          if (v_and == CFALSE) Result =CFALSE; 
          else { { list * v52331 = GC_OBJECT(list,cdr_list(GC_OBJECT(list,v52340->args)));
              ClaireType * v25307 = Kernel.emptySet;
              list * v49420;
              { { CL_INT loop_handle = ClEnv->cHandle;
                  bag *v_list; OID v_val;
                  OID v52341; CL_INT CLcount;
                  v_list = GC_OBJECT(list,v52340->args);
                   v49420 = v_list->clone();
                  for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                  { v52341 = (*(v_list))[CLcount];
                    v_val = _oid_(ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v52341))));
                    
                    (*((list *) v49420))[CLcount] = v_val;}
                  }
                GC_OBJECT(list,v49420);}
              list * v24742 = GC_OBJECT(list,cdr_list(v49420));
              list * v49418 = GC_OBJECT(list,get_restrictions_Call2(v52340,v49420));
              ClaireBoolean * v34226;
              { ClaireBoolean *v_and;
                { v_and = (((CL_INT)v49418->length > 0) ? CTRUE : CFALSE);
                  if (v_and == CFALSE) v34226 =CFALSE; 
                  else { { ClaireBoolean *v_or;
                      { v_or = ((v46853 == 0) ? CTRUE : CFALSE);
                        if (v_or == CTRUE) v_and =CTRUE; 
                        else { { OID  v59368;
                            { CL_INT loop_handle = ClEnv->cHandle;
                              OID gc_local;
                              ITERATE(v52329);
                              v59368= Kernel.cfalse;
                              for (START(v49418); NEXT(v52329);)
                              if (not_any(_oid_(nth_integer(status_I_restriction(OBJECT(restriction,v52329)),(OID)(1)))) != CTRUE)
                               { v59368 = Kernel.ctrue;
                                ClEnv->cHandle = loop_handle;break;}
                              }
                            v_or = not_any(v59368);
                            }
                          if (v_or == CTRUE) v_and =CTRUE; 
                          else v_and = CFALSE;}
                        }
                      }
                    if (v_and == CFALSE) v34226 =CFALSE; 
                    else { v_and = ((((CL_INT)v52332->dispatcher > 0) && 
                          ((CL_INT)v52331->length <= 4)) ? CTRUE : (((CL_INT)v49418->length < (OID)(3)) ? CTRUE : CFALSE));
                      if (v_and == CFALSE) v34226 =CFALSE; 
                      else v34226 = CTRUE;}
                    }
                  }
                }
              ClaireClass * v52335 = (((CL_INT)v49418->length > 0) ?
                c_srange_method(OBJECT(method,(*(v49418))[1])) :
                Kernel._void );
              ClaireBoolean * v45158;
              { OID  v60329;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(v52334);
                  v60329= Kernel.cfalse;
                  for (START(v49418); NEXT(v52334);)
                  { GC_LOOP;
                    { ClaireBoolean * g1886I;
                      { OID  v62251;
                        { GC__ANY(v25307 = U_type(v25307,domain_I_restriction(OBJECT(restriction,v52334))), 1);
                          v62251 = _oid_(((INHERIT(OWNER((*(OBJECT(restriction,v52334)->domain))[1]),Kernel._class)) ? ((last_list(OBJECT(restriction,v52334)->domain) != _oid_(Kernel._listargs)) ? ((tmatch_ask_list(v24742,GC_OBJECT(list,cdr_list(OBJECT(restriction,v52334)->domain))) == CTRUE) ? ((c_srange_method(OBJECT(method,v52334)) == v52335) ? CTRUE: CFALSE): CFALSE): CFALSE): CFALSE));
                          }
                        g1886I = not_any(v62251);
                        }
                      
                      if (g1886I == CTRUE) { v60329 = Kernel.ctrue;
                          ClEnv->cHandle = loop_handle;break;}
                        }
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                v45158 = not_any(v60329);
                }
              ClaireBoolean * v46654 = (((v52335 == Kernel._integer) || 
                  ((v52335 == Kernel._object) || 
                    ((v52335 == Kernel._any) || 
                      (v52335 == Kernel._void)))) ? ((_inf_equal_type(v25307,Kernel._object) == CTRUE) ? ((_inf_equal_type(GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v49012)))),v25307) == CTRUE) ? CTRUE: CFALSE): CFALSE): CFALSE);
              if (((OBJECT(ClaireBoolean,Generate.FCALLSTINKS->value)) == CTRUE) && 
                  ((((v34226 == CTRUE) ? ((v45158 == CTRUE) ? ((v46654 == CTRUE) ? CTRUE: CFALSE): CFALSE): CFALSE) != CTRUE) && 
                    ((CL_INT)v52332->dispatcher > 0)))
               { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
                 mtformat_module1(Generate.it,"****> fcall(~S) fails (selectorOK = ~S , lrOK = ~S, callOK = ~S)\n",0,GC_OBJECT(list,list::alloc(4,_oid_(v52340),
                  _oid_(v34226),
                  _oid_(v45158),
                  _oid_(v46654))));
                else ;}
              v_and = ((v34226 == CTRUE) ? ((v45158 == CTRUE) ? ((v46654 == CTRUE) ? CTRUE: CFALSE): CFALSE): CFALSE);
              }
            if (v_and == CFALSE) Result =CFALSE; 
            else Result = CTRUE;}
          }
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

list * get_restrictions_Call2(Call *v52340,list *v49420)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { list *Result ;
    { property * v52332 = v52340->selector;
      ClaireBoolean * v23536 = ((class_I_type(OBJECT(ClaireType,(*(v49420))[1]))->open == ClEnv->open) ? CTRUE : CFALSE);
      list * v49418 = list::empty(Kernel._method);
      if ((v52332->dispatcher == 0) && 
          ((v23536 == CTRUE) || 
              (v52332->open == ClEnv->open)))
       ;else { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v52334);
          for (START(v52332->restrictions); NEXT(v52334);)
          { GC_LOOP;
            if (length_bag(_exp_list(OBJECT(restriction,v52334)->domain,v49420)) != 0)
             { if (Kernel._method == OBJECT(ClaireObject,v52334)->isa)
               GC__ANY(v49418 = v49418->addFast((OID)v52334), 1);
              else { shrink_list(v49418,0);
                  ClEnv->cHandle = loop_handle; break;}
                }
            GC_UNLOOP; POP_SIGNAL;}
          }
        Result = v49418;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  fcall_exp_Call2_Generate(Call *v52340,OID v43304)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { property * v52332 = v52340->selector;
    OID  v49012 = GC_OID((*(v52340->args))[1]);
    list * v49420;
    { { CL_INT loop_handle = ClEnv->cHandle;
        bag *v_list; OID v_val;
        OID v52341; CL_INT CLcount;
        v_list = GC_OBJECT(list,v52340->args);
         v49420 = v_list->clone();
        for (CLcount= 1; CLcount <= v_list->length; CLcount++)
        { v52341 = (*(v_list))[CLcount];
          v_val = _oid_(ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v52341))));
          
          (*((list *) v49420))[CLcount] = v_val;}
        }
      GC_OBJECT(list,v49420);}
    list * v49418 = GC_OBJECT(list,get_restrictions_Call2(v52340,v49420));
    method * v52329 = OBJECT(method,(*(v49418))[1]);
    ClaireClass * v52335 = c_srange_method(v52329);
    if (v52335 == Kernel._void)
     princ_string("_void_(");
    else if (v52335 == Kernel._object)
     princ_string("_oid_(");
    else if ((v52335 == Kernel._integer) && 
        ((CL_INT)Optimize.compiler->safety <= 2))
     princ_string("_integer_(");
    if (((CL_INT)v52332->dispatcher > 0) && 
        ((CL_INT)v49420->length <= 4))
     { if (should_trace_ask_module1(Generate.it,4) == CTRUE)
       mtformat_module1(Generate.it,"`GREEN ---- note: ~S is compiled with fast dispatch \n",4,list::alloc(1,_oid_(v52340)));
      else ;if (v52335 == Kernel._object)
       princ_string("(ClaireObject *) ");
      expression_thing(v52332,v43304);
      princ_string("->fcall(");
      c_sorted_args_Call(v52340,v52329->srange,v43304,CTRUE);
      princ_string(")");
      }
    else { list * v24680;
        { { bag * v57552 = v52332->definition;
            list * v20739 = ((list *) empty_bag(v57552));
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(v52340);
              for (START(v57552); NEXT(v52340);)
              if (v49418->memq(v52340) == CTRUE)
               v20739->addFast((OID)v52340);
              }
            v24680 = GC_OBJECT(list,v20739);
            }
          GC_OBJECT(list,v24680);}
        if (should_trace_ask_module1(Generate.it,4) == CTRUE)
         mtformat_module1(Generate.it,"`GREEN ---- note: ~S is compiled with explicit dispatch (s = ~S) \n",4,list::alloc(2,_oid_(v52340),_oid_(v52335)));
        else ;{ CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v52329);
          for (START(v24680); NEXT(v52329);)
          { GC_LOOP;
            { list * v13514;
              { { CL_INT loop_handle = ClEnv->cHandle;
                  bag *v_list; OID v_val;
                  OID v52340; CL_INT CLcount;
                  v_list = OBJECT(restriction,v52329)->domain;
                   v13514 = v_list->clone();
                  for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                  { v52340 = (*(v_list))[CLcount];
                    v_val = _oid_(psort_any(v52340));
                    
                    (*((list *) v13514))[CLcount] = v_val;}
                  }
                GC_OBJECT(list,v13514);}
              if (v52329 != last_list(v24680))
               { princ_string("(INHERIT(");
                if (INHERIT(OWNER(v49012),Optimize._to_CL))
                 { (*Generate.expression)(GC_OID((*Kernel.arg)(v49012)),
                    v43304);
                  princ_string("->isa");
                  }
                else { princ_string("OWNER(");
                    (*Generate.expression)(v49012,
                      v43304);
                    princ_string(")");
                    }
                  princ_string(",");
                expression_any(_oid_(domain_I_restriction(OBJECT(restriction,v52329))),v43304);
                princ_string(") ?");
                breakline_void();
                princ_string(" ");
                if (v52335 == Kernel._object)
                 princ_string("(ClaireObject *)");
                princ_string(" ");
                c_princ_function(OBJECT(ClaireFunction,(*Optimize.functional_I)(v52329)));
                princ_string("((");
                class_princ_class(domain_I_restriction(OBJECT(restriction,v52329)));
                princ_string(" *) ");
                c_sorted_args_Call(v52340,v13514,v43304,CFALSE);
                princ_string(")");
                if ((INHERIT(OBJECT(restriction,v52329)->range->isa,Kernel._tuple)) && 
                    (Optimize.OPT->alloc_stack != CTRUE))
                 princ_string("->copyIfNeeded()");
                princ_string(" : ");
                breakline_void();
                princ_string(" ");
                }
              else { if (v52335 == Kernel._object)
                   princ_string("(ClaireObject *) ");
                  princ_string(" ");
                  c_princ_function(OBJECT(ClaireFunction,(*Optimize.functional_I)(v52329)));
                  princ_string("((");
                  (*Generate.interface_I)(Generate.PRODUCER->value,
                    _oid_(domain_I_restriction(OBJECT(restriction,v52329))));
                  princ_string(") ");
                  c_sorted_args_Call(v52340,v13514,v43304,CFALSE);
                  princ_string(")");
                  if ((INHERIT(OBJECT(restriction,v52329)->range->isa,Kernel._tuple)) && 
                      (Optimize.OPT->alloc_stack != CTRUE))
                   princ_string("->copyIfNeeded()");
                  else ;{ CL_INT  v52325 = 1;
                    CL_INT  v30410 = ((CL_INT)v24680->length-(CL_INT)1);
                    { CL_INT loop_handle = ClEnv->cHandle;
                      OID gc_local;
                      while (((CL_INT)v52325 <= (CL_INT)v30410))
                      { princ_string(")");
                        ++v52325;
                        POP_SIGNAL;}
                      }
                    }
                  }
                }
            GC_UNLOOP; POP_SIGNAL;}
          }
        }
      if ((v52335 == Kernel._void) || 
        ((v52335 == Kernel._object) || 
          ((v52335 == Kernel._float) || 
            ((v52335 == Kernel._integer) && 
                ((CL_INT)Optimize.compiler->safety <= 2)))))
     princ_string(")");
    }
  GC_UNBIND; POP_SIGNAL;}

void  c_sorted_arg_any(OID v52340,ClaireClass *v52335,OID v43304,ClaireBoolean *v20192)
{ GC_BIND;
  if (v20192 == CTRUE)
   princ_string("((CL_INT) ");
  if ((INHERIT(OWNER(v52340),Optimize._to_CL)) && (osort_any(_oid_(OBJECT(Compile_to_CL,v52340)->set_arg)) == v52335))
   (*Generate.expression)(GC_OID((*Kernel.arg)(v52340)),
    v43304);
  else if (v52335 == Kernel._any)
   (*Generate.expression)(v52340,
    v43304);
  else (*Generate.to_c)(Generate.PRODUCER->value,
      v52340,
      _oid_(v52335),
      v43304);
    if (v20192 == CTRUE)
   princ_string(")");
  GC_UNBIND; POP_SIGNAL;}

void  c_sorted_args_Call(Call *v52340,list *v49419,OID v43304,ClaireBoolean *v20192)
{ GC_BIND;
  { CL_INT  v52325 = 0;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52341);
      for (START(v52340->args); NEXT(v52341);)
      { if (v52325 != 0)
         princ_string(",");
        ++v52325;
        c_sorted_arg_any(v52341,OBJECT(ClaireClass,(*(v49419))[v52325]),v43304,v20192);
        }
      }
    }
  GC_UNBIND; POP_SIGNAL;}

void  bitvector_I_c_producer(Generate_c_producer *v52319,OID v52340)
{ GC_BIND;
  if (INHERIT(OWNER(v52340),Kernel._integer))
   bitvectorSum_integer(v52340);
  else if (INHERIT(OWNER(v52340),Optimize._to_CL))
   bitvector_I_c_producer(v52319,GC_OID(OBJECT(Compile_to_CL,v52340)->arg));
  else if (INHERIT(OWNER(v52340),Optimize._to_protect))
   bitvector_I_c_producer(v52319,GC_OID(OBJECT(Compile_to_protect,v52340)->arg));
  else (*Generate.expression)(v52340,
      Core.nil->value);
    GC_UNBIND; POP_SIGNAL;}

void  bitvectorSum_integer(int v52340)
{ if (v52340 == 0)
   princ_string("0");
  else { ClaireBoolean * v52318 = CFALSE;
      CL_INT  v52325 = 1;
      CL_INT  v30411 = 6;
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((CL_INT)v52325 <= (CL_INT)v30411))
        { if (BCONTAIN(v52340,v52325))
           { if (v52318 == CTRUE)
             princ_string("+");
            else v52318= CTRUE;
              princ_string(string_v((*(OBJECT(bag,Generate.bitvectorList->value)))[v52325]));
            }
          ++v52325;
          POP_SIGNAL;}
        }
      }
    POP_SIGNAL;}

void  signature_I_c_producer(Generate_c_producer *v52319,OID v52340)
{ GC_BIND;
  if (INHERIT(OWNER(v52340),Kernel._list))
   { princ_string("list::domain(");
    princ_integer(OBJECT(bag,v52340)->length);
    princ_string(",");
    { list * v19777;
      { { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v52341; CL_INT CLcount;
          v_list = OBJECT(bag,v52340);
           v19777 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v52341 = (*(v_list))[CLcount];
            v_val = getC_any(v52341);
            
            (*((list *) v19777))[CLcount] = v_val;}
          }
        GC_OBJECT(list,v19777);}
      args_list_bag(v19777,Core.nil->value,_sup_integer(OBJECT(bag,v52340)->length,3));
      }
    princ_string(")");
    }
  else if (INHERIT(OWNER(v52340),Optimize._to_C))
   signature_I_c_producer(v52319,GC_OID(OBJECT(Compile_to_C,v52340)->arg));
  else if (INHERIT(OWNER(v52340),Optimize._to_protect))
   signature_I_c_producer(v52319,GC_OID(OBJECT(Compile_to_protect,v52340)->arg));
  else if (INHERIT(OWNER(v52340),Language._List))
   signature_I_c_producer(v52319,GC_OID(_oid_(OBJECT(Construct,v52340)->args)));
  else if (INHERIT(OWNER(v52340),Language._Variable))
   expression_Variable(OBJECT(Variable,v52340),Core.nil->value);
  else { princ_string("<fucking ");
      print_any(_oid_(OWNER(v52340)));
      princ_string(":");
      print_any(v52340);
      princ_string(">");
      }
    GC_UNBIND; POP_SIGNAL;}

OID  getC_any(OID v52340)
{ GC_BIND;
  { OID Result = 0;
    if (INHERIT(OWNER(v52340),Optimize._to_CL))
     Result = getC_any(GC_OID(OBJECT(Compile_to_CL,v52340)->arg));
    else if (INHERIT(OWNER(v52340),Optimize._to_protect))
     Result = getC_any(GC_OID(OBJECT(Compile_to_protect,v52340)->arg));
    else if (INHERIT(OWNER(v52340),Core._global_variable))
     { if (nativeVar_ask_global_variable(OBJECT(global_variable,v52340)) == CTRUE)
       Result = v52340;
      else { Compile_to_C * v47292 = ((Compile_to_C *) GC_OBJECT(Compile_to_C,new_object_class(Optimize._to_C)));
          (v47292->arg = v52340);
          (v47292->set_arg = Kernel._type);
          add_I_property(Kernel.instances,Optimize._to_C,11,_oid_(v47292));
          Result = _oid_(v47292);
          }
        }
    else Result = v52340;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  gassign_c_producer(Generate_c_producer *v52319,Gassign *v45520,OID v43304)
{ GC_BIND;
  if (v45520->var->store_ask == CTRUE)
   { princ_string("(STOREI(");
    expression_global_variable(v45520->var,v43304);
    princ_string(",");
    (*Generate.expression)(v45520->arg,
      v43304);
    princ_string("))");
    }
  else { princ_string("(");
      expression_global_variable(v45520->var,v43304);
      princ_string("= ");
      (*Generate.expression)(v45520->arg,
        v43304);
      princ_string(")");
      }
    GC_UNBIND; POP_SIGNAL;}

void  call_slot_c_producer(Generate_c_producer *v52319,Call_slot *v45520,OID v43304)
{ GC_BIND;
  if (v45520->test == CTRUE)
   { princ_string((((INHERIT(v45520->selector->srange,Kernel._cl_import)) || 
        ((INHERIT(v45520->selector->srange,Kernel._string)) || 
          ((INHERIT(v45520->selector->srange,Kernel._array)) || 
            (INHERIT(v45520->selector->srange,Kernel._object))))) ?
      "NOTNULL" :
      "KNOWN" ));
    princ_string("(");
    expression_thing(v45520->selector->selector,v43304);
    princ_string(",");
    }
  c_member_c_producer(v52319,
    GC_OID(v45520->arg),
    psort_any(_oid_(domain_I_restriction(v45520->selector))),
    v45520->selector->selector,
    v43304);
  if (v45520->test == CTRUE)
   princ_string(")");
  GC_UNBIND; POP_SIGNAL;}

void  call_table_c_producer(Generate_c_producer *v52319,Call_table *v45520,OID v43304)
{ GC_BIND;
  { table * v52317 = v45520->selector;
    OID  v52332 = v52317->params;
    OID  v52331 = v45520->arg;
    if (v45520->test == CTRUE)
     { princ_string("KNOWN(");
      expression_thing(v52317,v43304);
      princ_string(",");
      }
    princ_string("(*(");
    expression_thing(v52317,v43304);
    princ_string("->graph))[");
    if (INHERIT(OWNER(v52332),Kernel._integer))
     { (*Generate.expression)(v52331,
        v43304);
      princ_string(" - ");
      princ_integer(v52332);
      }
    else if (INHERIT(OWNER(v52332),Kernel._list))
     { (*Generate.expression)((*(OBJECT(bag,(*Core.args)(v52331))))[1],
        v43304);
      princ_string(" * ");
      (*Kernel.princ)((*(OBJECT(bag,v52332)))[1]);
      princ_string(" + ");
      (*Generate.expression)((*(OBJECT(bag,(*Core.args)(v52331))))[2],
        v43304);
      princ_string(" - ");
      (*Kernel.princ)((*(OBJECT(bag,v52332)))[2]);
      }
    princ_string("]");
    if (v45520->test == CTRUE)
     princ_string(")");
    }
  GC_UNBIND; POP_SIGNAL;}

void  call_array_c_producer(Generate_c_producer *v52319,Call_array *v45520,OID v43304)
{ GC_BIND;
  if (v45520->test == _oid_(Kernel._float))
   { princ_string("((double *) ");
    (*Generate.expression)(v45520->selector,
      v43304);
    princ_string(")[");
    (*Generate.expression)(v45520->arg,
      v43304);
    princ_string("]");
    }
  else { princ_string("((OID *) ");
      (*Generate.expression)(v45520->selector,
        v43304);
      princ_string(")[");
      (*Generate.expression)(v45520->arg,
        v43304);
      princ_string("]");
      }
    GC_UNBIND; POP_SIGNAL;}

void  update_c_producer(Generate_c_producer *v52319,Update *v45520,OID v43304)
{ GC_BIND;
  { OID  v52332 = v45520->selector;
    OID  v52317 = v45520->arg;
    OID  v52338 = v45520->value;
    OID  v52340 = v45520->var;
    ClaireClass * v52335 = OBJECT(ClaireClass,(*Optimize.c_sort)(v52338));
    if ((INHERIT(OWNER(v52332),Kernel._relation)) && ((((OBJECT(ClaireRelation,v52332)->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE) && 
        ((v52317 != _oid_(Kernel.put)) && 
          (v52317 != _oid_(Core.put_store)))))
     { c_princ_string(string_I_symbol(OBJECT(symbol,(*Kernel.name)(v52332))));
      princ_string("_write(");
      (*Generate.expression)(GC_OID((*Kernel.arg)(v52340)),
        v43304);
      princ_string(",");
      (*Generate.expression)(v52338,
        v43304);
      princ_string(")");
      }
    else if ((INHERIT(OWNER(v52332),Kernel._relation)) && ((OBJECT(ClaireRelation,v52332)->store_ask == CTRUE) || 
        (v52317 == _oid_(Core.put_store))))
     { princ_string("STORE");
      princ_string((((v52335 == Kernel._any) || 
          (v52335 == Kernel._integer)) ?
        "I" :
        ((v52335 == Kernel._float) ?
          "F" :
          "O" ) ));
      princ_string("(");
      (*Generate.expression)(v52340,
        v43304);
      princ_string(",");
      (*Generate.expression)(v52338,
        v43304);
      princ_string(")");
      }
    else { princ_string("(");
        (*Generate.expression)(v52340,
          v43304);
        princ_string(" = ");
        (*Generate.expression)(v52338,
          v43304);
        princ_string(")");
        }
      }
  GC_UNBIND; POP_SIGNAL;}

void  object_test_c_producer(Generate_c_producer *v52319,OID v49012,ClaireBoolean *v31471,OID v43304)
{ princ_string("(CTAG(");
  (*Generate.expression)(v49012,
    v43304);
  princ_string(") ");
  sign_equal_boolean(v31471);
  princ_string(" OBJ_CODE)");
  POP_SIGNAL;}

void  exp_to_protect_c_producer(Generate_c_producer *v52319,Compile_to_protect *v45520,OID v43304)
{ GC_BIND;
  { OID  v49637 = GC_OID((*Optimize.c_type)(GC_OID(v45520->arg)));
    if ((Optimize.OPT->protection == CTRUE) && 
        ((need_protect_any(GC_OID(v45520->arg)) == CTRUE) && 
          (((Optimize.OPT->alloc_stack == CTRUE) ? ((_inf_equal_type(OBJECT(ClaireType,v49637),Kernel._tuple) == CTRUE) ? CTRUE: CFALSE): CFALSE) != CTRUE)))
     { OID  v52340 = GC_OID(v45520->arg);
      ClaireClass * v52335 = OBJECT(ClaireClass,(*Optimize.c_sort)(v52340));
      princ_string(gc_protect_class(v52335));
      princ_string("(");
      if (INHERIT(v52335,Kernel._object))
       { class_princ_class(psort_any(GC_OID((*Core.glb)(GC_OID((*Optimize.c_type)(v52340)),
          _oid_(v52335)))));
        princ_string(",");
        (*Generate.expression)(GC_OID(v45520->arg),
          v43304);
        }
      else (*Generate.expression)(GC_OID(v45520->arg),
          v43304);
        princ_string(")");
      }
    else (*Generate.expression)(GC_OID(v45520->arg),
        v43304);
      }
  GC_UNBIND; POP_SIGNAL;}

void  macro_c_producer(Generate_c_producer *v52319)
{ ;POP_SIGNAL;}

void  init_var_c_producer(Generate_c_producer *v52319,ClaireClass *v52335)
{ ;POP_SIGNAL;}

void  any_interface_c_producer(Generate_c_producer *v52319)
{ princ_string("OID");
  POP_SIGNAL;}

void  pointer_cast_c_producer(Generate_c_producer *v52319,ClaireClass *v52335)
{ princ_string("(");
  class_princ_c_producer(v52319,v52335);
  princ_string(" *)");
  POP_SIGNAL;}

void  exp_Assign_c_producer(Generate_c_producer *v52319,Assign *v45520,OID v43304)
{ GC_BIND;
  { OID  v52340 = v45520->arg;
    OID  v52338 = v45520->var;
    (*Language.ident)(Generate.PRODUCER->value,
      v52338);
    princ_string("= ");
    (*Generate.expression)(v52340,
      v43304);
    }
  GC_UNBIND; POP_SIGNAL;}

void  stat_handle_c_producer(Generate_c_producer *v52319,ClaireHandle *v45520,OID v52335,OID v43304)
{ GC_BIND;
  new_block_void();
  princ_string("ClaireHandler c_handle = ClaireHandler();");
  breakline_void();
  princ_string("if ERROR_IN ");
  breakline_void();
  new_block_void();
  statement_any(GC_OID(v45520->arg),v52335,v43304);
  princ_string("ERROR_FREE;");
  close_block_void();
  princ_string("else if (belong_to(_oid_(ClEnv->exception_I),");
  (*Generate.expression)(GC_OID((*Optimize.c_code)(GC_OID(v45520->test),
      _oid_(Kernel._any))),
    _oid_(Kernel.emptySet));
  princ_string(") == CTRUE)");
  breakline_void();
  new_block_void();
  princ_string("c_handle.catchIt();");
  statement_any(GC_OID(v45520->other),v52335,v43304);
  close_block_void();
  princ_string("else PREVIOUS_HANDLER;");
  close_block_void();
  GC_UNBIND; POP_SIGNAL;}

void  stat_construct_c_producer(Generate_c_producer *v52319,Construct *v45520,OID v52335,OID v43304)
{ GC_BIND;
  if (boolean_I_any(v52335) != CTRUE)
   close_exception(((general_error *) (*Core._general_error)(_string_("[202] A do should have been used for ~S"),
    _oid_(list::alloc(1,_oid_(v45520))))));
  { char * v52338 = GC_STRING(check_var_string("v_bag",v52335,v43304));
    bag * v45301;
    { ClaireObject *V_CC ;
      if (INHERIT(v45520->isa,Language._List))
       V_CC = list::empty();
      else if (INHERIT(v45520->isa,Language._Set))
       V_CC = set::empty();
      else if (INHERIT(v45520->isa,Language._Tuple))
       V_CC = tuple::empty();
      else close_exception(((general_error *) (*Core._general_error)(_string_("BUG: ~S"),
          _oid_(list::alloc(1,_oid_(v45520))))));
        v45301= (bag *) V_CC;}
    new_block_void();
    if (get_property(Kernel.of,v45520) != CNULL)
     (*Kernel.cast_I)(_oid_(v45301),
      GC_OID((*Kernel.of)(_oid_(v45520))));
    { ClaireBoolean * g1892I;
      { OID  v22660;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v52340);
          v22660= Kernel.cfalse;
          bag *v52340_support;
          v52340_support = GC_OBJECT(list,v45520->args);
          for (START(v52340_support); NEXT(v52340);)
          if (c_func_any(v52340) != CTRUE)
           { v22660 = Kernel.ctrue;
            ClEnv->cHandle = loop_handle;break;}
          }
        g1892I = boolean_I_any(v22660);
        }
      
      if (g1892I == CTRUE) { princ_string("OID ");
          princ_string(v52338);
          princ_string(";");
          breakline_void();
          }
        }
    if (Optimize.OPT->protection == CTRUE)
     { (v52319->stat = ((CL_INT)v52319->stat+(CL_INT)1));
      princ_string("GC_ANY(");
      }
    (*Kernel.c_princ)(v52335);
    princ_string("= ");
    (*Generate.bag_expression)(Generate.PRODUCER->value,
      _oid_(v45301->isa),
      _oid_(v45301),
      _oid_(of_bag(v45301)),
      v43304);
    if (Optimize.OPT->protection == CTRUE)
     princ_string(")");
    princ_string(";");
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52340);
      bag *v52340_support;
      v52340_support = GC_OBJECT(list,v45520->args);
      for (START(v52340_support); NEXT(v52340);)
      { ClaireBoolean * v52322 = c_func_any(v52340);
        breakline_void();
        if (v52322 != CTRUE)
         statement_any(v52340,_string_(v52338),v43304);
        princ_string("((");
        { OID  v23623;
          if (INHERIT(v45520->isa,Language._List))
           v23623 = _oid_(Kernel._list);
          else if (INHERIT(v45520->isa,Language._Set))
           v23623 = _oid_(Kernel._set);
          else v23623 = _oid_(Kernel._tuple);
            print_any(v23623);
          }
        princ_string(" *) ");
        (*Kernel.c_princ)(v52335);
        princ_string(")");
        addFast_c_producer(v52319);
        princ_string("((OID)");
        if (v52322 == CTRUE)
         (*Generate.expression)(v52340,
          v43304);
        else c_princ_string(v52338);
          princ_string(");");
        }
      }
    close_block_void();
    }
  GC_UNBIND; POP_SIGNAL;}

void  stat_while_c_producer(Generate_c_producer *v52319,While *v45520,OID v52335,OID v43304)
{ GC_BIND;
  new_block_void();
  { ClaireBoolean * v49181 = ((c_func_any(GC_OID(v45520->test)) == CTRUE) ? ((v45520->other != CTRUE) ? ((gc_usage_any(GC_OID(v45520->test),OBJECT(ClaireBoolean,v43304)) == Kernel.cfalse) ? CTRUE: CFALSE): CFALSE): CFALSE);
    char * v52338 = GC_STRING(check_var_string("v_while",v52335,v43304));
    princ_string("int loop_handle = ClEnv->cHandle;");
    breakline_void();
    if (Optimize.OPT->loop_gc == CTRUE)
     { princ_string("OID gc_local;");
      breakline_void();
      }
    if (v49181 != CTRUE)
     { interface_I_class(Kernel._boolean);
      princ_string(v52338);
      princ_string(";");
      breakline_void();
      }
    if (Kernel._string == OWNER(v52335))
     { (*Kernel.c_princ)(v52335);
      princ_string("= _oid_(");
      expression_boolean(CFALSE,v43304);
      princ_string(");");
      breakline_void();
      }
    if (v49181 == CTRUE)
     { princ_string("while (");
      (*Optimize.bool_exp)(GC_OID(v45520->test),
        _oid_(not_any(_oid_(v45520->other))),
        v43304);
      princ_string(")");
      }
    else { { OID  v24584;
          { if (v45520->other == CTRUE)
             v24584 = Kernel.cfalse;
            else v24584 = v45520->test;
              GC_OID(v24584);}
          statement_any(v24584,_string_(v52338),Kernel.ctrue);
          }
        breakline_void();
        princ_string("while (");
        princ_string(v52338);
        princ_string(" ");
        if (v45520->other == CTRUE)
         princ_string("!=");
        else princ_string("==");
          princ_string(" CTRUE)");
        }
      breakline_void();
    new_block_void();
    { ClaireBoolean * v13314 = ((Optimize.OPT->loop_gc == CTRUE) ? ((gc_usage_any(GC_OID(v45520->arg),CTRUE) != Kernel.cfalse) ? CTRUE: CFALSE): CFALSE);
      if (v13314 == CTRUE)
       { princ_string("GC_LOOP;");
        breakline_void();
        }
      { OID  v25545;
        if (Kernel._string == OWNER(v52335))
         v25545 = v52335;
        else v25545 = CNULL;
          inner_statement_any(GC_OID(v45520->arg),_oid_(Kernel.emptySet),v25545);
        }
      if (v49181 != CTRUE)
       statement_any(GC_OID(v45520->test),_string_(v52338),Kernel.ctrue);
      if (v13314 == CTRUE)
       princ_string("GC_UNLOOP;");
      princ_string("POP_SIGNAL;");
      }
    close_block_void();
    }
  close_block_void();
  GC_UNBIND; POP_SIGNAL;}

void  stat_gassign_c_producer(Generate_c_producer *v52319,Gassign *v45520,OID v52335,OID v43304)
{ GC_BIND;
  new_block_void();
  interface_I_c_producer(v52319,((nativeVar_ask_global_variable(v45520->var) == CTRUE) ?
    getRange_global_variable(v45520->var) :
    Kernel._any ));
  princ_string(" truc;");
  statement_any(GC_OID(v45520->arg),_string_("truc"),v43304);
  breakline_void();
  if (v45520->var->store_ask == CTRUE)
   { princ_string("STOREI(");
    expression_global_variable(v45520->var,v43304);
    princ_string(",truc);");
    }
  else { princ_string("(");
      expression_global_variable(v45520->var,v43304);
      princ_string(" = truc);");
      }
    close_block_void();
  GC_UNBIND; POP_SIGNAL;}

void  stat_for_c_producer(Generate_c_producer *v52319,For *v45520,OID v52335,OID v43304)
{ GC_BIND;
  { char * v52338 = GC_STRING(c_string_c_producer1(v52319,GC_OBJECT(Variable,v45520->var)));
    new_block_void();
    princ_string("int loop_handle = ClEnv->cHandle;");
    breakline_void();
    if (Optimize.OPT->loop_gc == CTRUE)
     { princ_string("OID gc_local;");
      breakline_void();
      }
    princ_string("ITERATE(");
    c_princ_string(v52338);
    princ_string(");");
    if (Kernel._string == OWNER(v52335))
     { breakline_void();
      (*Kernel.c_princ)(v52335);
      princ_string("= Kernel.cfalse;");
      }
    breakline_void();
    if ((c_func_any(GC_OID(v45520->set_arg)) == CTRUE) && 
        (designated_ask_any(GC_OID(v45520->set_arg)) == CTRUE))
     { princ_string("for (START(");
      (*Generate.expression)(GC_OID(v45520->set_arg),
        v43304);
      princ_string("); NEXT(");
      c_princ_string(v52338);
      princ_string(");)");
      }
    else { char * v49664 = GC_STRING(append_string(v52338,"_support"));
        princ_string("bag *");
        c_princ_string(v49664);
        princ_string(";");
        breakline_void();
        statement_any(GC_OID(v45520->set_arg),_string_(v49664),v43304);
        princ_string("for (START(");
        c_princ_string(v49664);
        princ_string("); NEXT(");
        c_princ_string(v52338);
        princ_string(");)");
        }
      breakline_void();
    { ClaireBoolean * v13314 = ((Optimize.OPT->loop_gc == CTRUE) ? ((gc_usage_any(GC_OID(v45520->arg),CTRUE) != Kernel.cfalse) ? CTRUE: CFALSE): CFALSE);
      if (v13314 == CTRUE)
       { new_block_void();
        princ_string("GC_LOOP;");
        breakline_void();
        }
      if ((Optimize.OPT->profile_ask == CTRUE) && 
          (_Z_any1(Optimize.OPT->in_method,Kernel._object) == CTRUE))
       { if (Optimize.OPT->loop_gc != CTRUE)
         new_block_void();
        princ_string("PRloop(PR_x);");
        breakline_void();
        }
      { OID  v26507;
        if (Kernel._string == OWNER(v52335))
         v26507 = v52335;
        else v26507 = CNULL;
          statement_any(GC_OID(v45520->arg),_oid_(Kernel.emptySet),v26507);
        }
      if (v13314 == CTRUE)
       { princ_string("GC_UNLOOP; POP_SIGNAL;");
        close_block_void();
        }
      if ((Optimize.OPT->profile_ask == CTRUE) && 
          ((_Z_any1(Optimize.OPT->in_method,Kernel._object) == CTRUE) && 
            (Optimize.OPT->loop_gc != CTRUE)))
       close_block_void();
      close_block_void();
      }
    }
  GC_UNBIND; POP_SIGNAL;}

void  stat_iteration_c_producer(Generate_c_producer *v52319,Iteration *v45520,OID v52335,OID v43304)
{ GC_BIND;
  if (boolean_I_any(v52335) != CTRUE)
   close_exception(((general_error *) (*Core._general_error)(_string_("[203] you should have used a FOR here:~S"),
    _oid_(list::alloc(1,_oid_(v45520))))));
  { char * v52338 = GC_STRING(c_string_c_producer1(v52319,GC_OBJECT(Variable,v45520->var)));
    char * v19815 = GC_STRING(check_var_string("v_val",v52335,v43304));
    char * v53635 = GC_STRING(check_var_string("v_list",v52335,v43304));
    new_block_void();
    princ_string("int loop_handle = ClEnv->cHandle;");
    breakline_void();
    princ_string("bag *");
    princ_string(v53635);
    princ_string("; OID ");
    princ_string(v19815);
    princ_string(";");
    breakline_void();
    princ_string("OID ");
    c_princ_string(v52338);
    princ_string(",CLcount;");
    breakline_void();
    statement_any(GC_OID(v45520->set_arg),_string_(v53635),v43304);
    princ_string(" ");
    (*Kernel.c_princ)(v52335);
    princ_string(" = ");
    princ_string(v53635);
    princ_string("->clone(");
    if (get_property(Kernel.of,v45520) != CNULL)
     (*Generate.expression)(GC_OID((*Optimize.c_code)(GC_OID((*Kernel.of)(_oid_(v45520))),
        _oid_(Kernel._type))),
      Core.nil->value);
    princ_string(")");
    princ_string(";");
    breakline_void();
    princ_string("for (CLcount= 1; CLcount <= ");
    princ_string(v53635);
    princ_string("->length; CLcount++)");
    breakline_void();
    new_block_void();
    c_princ_string(v52338);
    princ_string(" = (*(");
    princ_string(v53635);
    princ_string("))[CLcount];");
    breakline_void();
    statement_any(GC_OID(v45520->arg),_string_(v19815),Kernel.ctrue);
    breakline_void();
    princ_string("(*((list *) ");
    (*Kernel.princ)(v52335);
    princ_string("))[CLcount] = ");
    princ_string(v19815);
    princ_string(";");
    close_block_void();
    close_block_void();
    }
  GC_UNBIND; POP_SIGNAL;}

void  stat_super_c_producer(Generate_c_producer *v52319,Super *v45520,OID v52335,OID v43304)
{ GC_BIND;
  { char * v30092 = GC_STRING(check_var_string("v_rec",v52335,v43304));
    new_block_void();
    princ_string("OID ");
    princ_string(v30092);
    princ_string(";");
    breakline_void();
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52340);
      bag *v52340_support;
      v52340_support = GC_OBJECT(list,v45520->args);
      for (START(v52340_support); NEXT(v52340);)
      { statement_any(v52340,_string_(v30092),v43304);
        princ_string("PUSH(");
        princ_string(v30092);
        princ_string(");");
        breakline_void();
        }
      }
    if (Kernel._string == OWNER(v52335))
     { c_princ_string(string_v(v52335));
      princ_string("=");
      }
    expression_thing(v45520->selector,v43304);
    princ_string("->super(");
    (*Generate.expression)(GC_OID(_oid_(v45520->cast_to)),
      v43304);
    princ_string(",");
    princ_integer(v45520->args->length);
    princ_string(");");
    close_block_void();
    }
  GC_UNBIND; POP_SIGNAL;}

void  stat_let_c_producer(Generate_c_producer *v52319,Let *v45520,OID v52335,OID v43304)
{ GC_RESERVE(10);  // v3.0.55 optim !
  { char * v49481 = GC_STRING(string_v((*Generate.c_string)(Generate.PRODUCER->value,
      _oid_(v45520->var->pname))));
    if ((v49481[1 - 1] == ((unsigned char)67 /* 'C' */)) && 
        (v49481[2 - 1] == ((unsigned char)37 /* '%' */)))
     (v45520->var->pname = gensym_void());
    }
  { OID  v52338 = GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
      GC_OID(_oid_(v45520->var))));
    ClaireBoolean * v52318 = Optimize.OPT->alloc_stack;
    OID  v52340 = GC_OID(v45520->value);
    ClaireBoolean * v52322 = CTRUE;
    new_block_void();
    (Optimize.OPT->alloc_stack = CFALSE);
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while ((v52322 == CTRUE))
      { GC_LOOP;
        if (INHERIT(v45520->isa,Language._Let_star))
         (Optimize.OPT->alloc_stack = CTRUE);
        interface_I_class(sort_Variable(GC_OBJECT(Variable,v45520->var)));
        princ_string(" ");
        c_princ_string(string_v(v52338));
        if (c_func_any(v52340) == CTRUE)
         { princ_string(" = ");
          if (bool_exp_ask_any(v52340) == CTRUE)
           (*Generate.bool_exp_I)(Generate.PRODUCER->value,
            v52340,
            v43304);
          else (*Generate.expression)(v52340,
              v43304);
            princ_string(";");
          breakline_void();
          }
        else { (*Generate.init_var)(Generate.PRODUCER->value,
              _oid_(sort_Variable(GC_OBJECT(Variable,v45520->var))));
            princ_string(";");
            breakline_void();
            statement_any(v52340,v52338,v43304);
            }
          if (((OBJECT(ClaireBoolean,Optimize._starin_c_func_star->value)) == CTRUE) && 
            ((Kernel._method == OWNER(Optimize.OPT->in_method)) && ((need_debug_ask_any(GC_OID(Optimize.OPT->in_method)) == CTRUE) && 
                (OBJECT(list,Optimize._stardebug_build_star->value)->memq(_oid_(v45520->var)) == CTRUE))))
         { { Variable * v49728 = GC_OBJECT(Variable,v45520->var);
            princ_string("DB_SET(");
            print_any(((OID)v49728->dindex));
            princ_string(",");
            { ClaireClass * v52335 = OBJECT(ClaireClass,(*Kernel.sort_I)(GC_OID(_oid_(v49728->range))));
              if (((v52335 == Kernel._any) && 
                    (v49728->range != Kernel._float)) || 
                  (v52335 == Kernel._integer))
               expression_Variable(v49728,Kernel.cfalse);
              else to_cl_c_producer(v52319,_oid_(v49728),((v49728->range == Kernel._float) ?
                  Kernel._float :
                  v52335 ),Kernel.cfalse);
                }
            princ_string(")");
            }
          breakline_void();
          }
        if (INHERIT(v45520->isa,Language._Let_star))
         (Optimize.OPT->alloc_stack = CFALSE);
        if (INHERIT(OWNER(v45520->arg),Language._Let))
         { GC__ANY(v45520 = OBJECT(Let,v45520->arg), 2);
          GC__OID(v52338 = (*Generate.c_string)(Generate.PRODUCER->value,
            GC_OID(_oid_(v45520->var))), 5);
          GC__OID(v52340 = v45520->value, 7);
          }
        else v52322= CFALSE;
          GC_UNLOOP;POP_SIGNAL;}
      }
    (Optimize.OPT->alloc_stack = v52318);
    inner_statement_any(GC_OID(v45520->arg),v52335,v43304);
    close_block_void();
    }
  GC_UNBIND; POP_SIGNAL;}



