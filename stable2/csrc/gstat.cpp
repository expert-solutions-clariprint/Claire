/***** CLAIRE Compilation of file ./compile/gstat.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:50 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>
#include <Optimize.h>
#include <Generate.h>
list * unfold_args_list(list *v52331)
{ GC_BIND;
  { list *Result ;
    { list * v30365;
      { { list * v61556 = list::empty(Kernel.emptySet);
          { CL_INT  v52325 = 1;
            CL_INT  v30224 = v52331->length;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while (((CL_INT)v52325 <= (CL_INT)v30224))
              { if (c_func_any((*(v52331))[v52325]) != CTRUE)
                 v61556->addFast((OID)((OID)v52325));
                ++v52325;
                POP_SIGNAL;}
              }
            }
          v30365 = GC_OBJECT(list,v61556);
          }
        GC_OBJECT(list,v30365);}
      if (should_trace_ask_module1(Generate.it,5) == CTRUE)
       { list * v15536;
        { { OID v_bag;
            GC_ANY(v15536= list::empty(Kernel.emptySet));
            { { list * v5796;{ CL_INT loop_handle = ClEnv->cHandle;
                  bag *v_list; OID v_val;
                  OID v52340; CL_INT CLcount;
                  v_list = v30365;
                   v5796 = v_list->clone();
                  for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                  { v52340 = (*(v_list))[CLcount];
                    v_val = (*(v52331))[v52340];
                    
                    (*((list *) v5796))[CLcount] = v_val;}
                  }
                
                v_bag=_oid_(v5796);}
              GC_OID(v_bag);}
            ((list *) v15536)->addFast((OID)v_bag);
            { { list * v5818;{ CL_INT loop_handle = ClEnv->cHandle;
                  bag *v_list; OID v_val;
                  OID v52340; CL_INT CLcount;
                  v_list = v30365;
                   v5818 = v_list->clone();
                  for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                  { v52340 = (*(v_list))[CLcount];
                    v_val = (*Optimize.c_sort)((*(v52331))[v52340]);
                    
                    (*((list *) v5818))[CLcount] = v_val;}
                  }
                
                v_bag=_oid_(v5818);}
              GC_OID(v_bag);}
            ((list *) v15536)->addFast((OID)v_bag);
            { { list * v5819;{ CL_INT loop_handle = ClEnv->cHandle;
                  bag *v_list; OID v_val;
                  OID v52340; CL_INT CLcount;
                  v_list = v30365;
                   v5819 = v_list->clone();
                  for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                  { v52340 = (*(v_list))[CLcount];
                    v_val = _oid_(stupid_t_any1((*(v52331))[v52340]));
                    
                    (*((list *) v5819))[CLcount] = v_val;}
                  }
                
                v_bag=_oid_(v5819);}
              GC_OID(v_bag);}
            ((list *) v15536)->addFast((OID)v_bag);}
          GC_OBJECT(list,v15536);}
        mtformat_module1(Generate.it,"unfold -> ~S : ~S - ~S \n",5,v15536);
        }
      else ;{ CL_INT loop_handle = ClEnv->cHandle;
        bag *v_list; OID v_val;
        OID v52325; CL_INT CLcount;
        v_list = v30365;
         Result = v_list->clone();
        for (CLcount= 1; CLcount <= v_list->length; CLcount++)
        { v52325 = (*(v_list))[CLcount];
          { Let * v47292 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
            (v47292->var = Variable_I_symbol(append_symbol(gensym_void(),_string_("UU")),0,GC_OBJECT(ClaireType,c_type_sort_any((*(v52331))[v52325]))));
            (v47292->value = (*(v52331))[v52325]);
            add_I_property(Kernel.instances,Language._Let,11,_oid_(v47292));
            v_val = _oid_(v47292);
            }
          
          (*((list *) Result))[CLcount] = v_val;}
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireType * c_type_sort_any(OID v52340)
{ GC_BIND;
  { ClaireType *Result ;
    { ClaireClass * v52335 = OBJECT(ClaireClass,(*Optimize.c_sort)(v52340));
      ClaireClass * v52336 = stupid_t_any1(v52340);
      if (should_trace_ask_module1(Generate.it,5) == CTRUE)
       mtformat_module1(Generate.it,"AHA infer a stupid type ~S [sort ~S] in ~S \n",5,list::alloc(3,_oid_(v52336),
        _oid_(v52335),
        v52340));
      else ;Result = ((v52335 == Kernel._void) ?
        osort_any(GC_OID((*Optimize.c_type)(v52340))) :
        ((boolean_I_any(sort_equal_class(osort_any(_oid_(v52336)),v52335)) == CTRUE) ?
          v52336 :
          v52335 ) );
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  unfold_arg_list(list *v52331,list *v49404,OID v52340)
{ { OID Result = 0;
    { CL_INT  v52325 = 1;
      CL_INT  v52326 = 0;
      CL_INT  v52329 = v52331->length;
      { ClaireBoolean * g1832I;
        { OID v40982;{ CL_INT loop_handle = ClEnv->cHandle;
            v40982= _oid_(CFALSE);
            while (((CL_INT)v52325 <= (CL_INT)v52329))
            { if (c_func_any((*(v52331))[v52325]) != CTRUE)
               { ++v52326;
                if (equal((*(v52331))[v52325],v52340) == CTRUE)
                 { v40982 = Kernel.ctrue;
                  ClEnv->cHandle = loop_handle;break;}
                }
              else if (equal((*(v52331))[v52325],v52340) == CTRUE)
               { v40982 = Kernel.cfalse;
                ClEnv->cHandle = loop_handle;break;}
              ++v52325;
              POP_SIGNAL;}
            }
          
          g1832I=OBJECT(ClaireBoolean,v40982);}
        
        if (g1832I == CTRUE) Result = (*Language.var)((*(v49404))[v52326]);
          else Result = (*(v52331))[v52325];
        }
      }
    POP_SIGNAL; return (Result);}
  }

void  unfold_use_list(list *v32413,OID v52340,OID v52335,OID v43304)
{ { CL_INT  v52333 = v32413->length;
    CL_INT  v52338 = ClEnv->verbose;
    (ClEnv->verbose = 0);
    if (boolean_I_any(_oid_(v32413)) != CTRUE)
     close_exception(((general_error *) (*Core._general_error)(_string_("[internal] design bug c_func(~S) should be true"),
      _oid_(list::alloc(1,v52340)))));
    if (equal((*Optimize.c_type)(v52340),_oid_(Kernel.emptySet)) == CTRUE)
     v52335= _oid_(Kernel._void);
    { CL_INT  v52325 = 1;
      CL_INT  v30250 = ((CL_INT)v52333-(CL_INT)1);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)v52325 <= (CL_INT)v30250))
        { write_property(Kernel.arg,OBJECT(ClaireObject,(*(v32413))[v52325]),(*(v32413))[((CL_INT)v52325+(CL_INT)1)]);
          ++v52325;
          POP_SIGNAL;}
        }
      }
    (OBJECT(Let,(*(v32413))[v52333])->arg = v52340);
    (ClEnv->verbose = v52338);
    self_statement_Let(OBJECT(Let,(*(v32413))[1]),v52335,v43304);
    }
  POP_SIGNAL;}

void  statement_any(OID v45520,OID v52335,OID v43304)
{ GC_BIND;
  { ClaireBoolean * v52318 = Optimize.OPT->alloc_stack;
    if ((((INHERIT(OWNER(v45520),Language._Tuple)) || 
        (INHERIT(OWNER(v45520),Language._Do))) ? CTRUE : ((INHERIT(OWNER(v45520),Language._Let)) ? CTRUE : CFALSE)) != CTRUE)
     (Optimize.OPT->alloc_stack = CFALSE);
    if (c_func_any(v45520) == CTRUE)
     { { ClaireBoolean * g1834I;
        { ClaireBoolean *v_and;
          { v_and = ((Kernel._string == OWNER(v52335)) ? CTRUE : CFALSE);
            if (v_and == CFALSE) g1834I =CFALSE; 
            else { { OID  v42444;
                { OID  v43405;
                  { if (INHERIT(OWNER(v45520),Optimize._to_CL))
                     v43405 = OBJECT(Compile_to_CL,v45520)->arg;
                    else v43405 = v45520;
                      GC_OID(v43405);}
                  v42444 = (*Optimize.c_sort)(v43405);
                  }
                v_and = ((v42444 != _oid_(Kernel._void)) ? CTRUE : CFALSE);
                }
              if (v_and == CFALSE) g1834I =CFALSE; 
              else g1834I = CTRUE;}
            }
          }
        
        if (g1834I == CTRUE) { (*Kernel.c_princ)(v52335);
            princ_string(" = ");
            if (bool_exp_ask_any(v45520) == CTRUE)
             (*Generate.bool_exp_I)(Generate.PRODUCER->value,
              v45520,
              v43304);
            else (*Generate.expression)(v45520,
                v43304);
              princ_string(";");
            breakline_void();
            }
          else if (INHERIT(OWNER(v45520),Language._If))
         (*Generate.self_statement)(v45520,
          v52335,
          v43304);
        else if (INHERIT(OWNER(v45520),Reader._delimiter))
         close_exception(((general_error *) (*Core._general_error)(_string_("[201] Loose delimiter in program: ~S"),
          _oid_(list::alloc(1,v45520)))));
        else (*Generate.stat_exp)(Generate.PRODUCER->value,
            v45520,
            v43304);
          }
      }
    else if ((INHERIT(OWNER(v45520),Language._Call_method)) && 
        (((*Kernel.arg)(v45520) == Generate._starclose_exception_star->value) && 
          (c_func_any(GC_OID((*(OBJECT(bag,(*Core.args)(v45520))))[1])) == CTRUE)))
     { (*Generate.expression)(v45520,
        v43304);
      princ_string(";");
      breakline_void();
      }
    else (*Generate.self_statement)(v45520,
        v52335,
        v43304);
      (Optimize.OPT->alloc_stack = v52318);
    }
  GC_UNBIND; POP_SIGNAL;}

void  self_statement_Construct(Construct *v45520,OID v52335,OID v43304)
{ (*Generate.stat_construct)(Generate.PRODUCER->value,
    _oid_(v45520),
    v52335,
    v43304);
  POP_SIGNAL;}

void  self_statement_If(If *v45520,OID v52335,OID v43304)
{ GC_BIND;
  if (c_func_any(GC_OID(v45520->test)) == CTRUE)
   { princ_string("if ");
    (*Optimize.bool_exp)(GC_OID(v45520->test),
      Kernel.ctrue,
      v43304);
    breakline_void();
    princ_string(" ");
    if (INHERIT(OWNER(v45520->arg),Language._If))
     new_block_void();
    statement_any(GC_OID(v45520->arg),v52335,v43304);
    if (INHERIT(OWNER(v45520->arg),Language._If))
     close_block_void();
    if ((Kernel._string == OWNER(v52335)) || 
        (boolean_I_any(v45520->other) == CTRUE))
     { OID  v49777 = GC_OID(v45520->other);
      if (inherit_ask_class(OWNER(v49777),Language._If) != CTRUE)
       (Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
      princ_string("else ");
      statement_any(v49777,v52335,v43304);
      if (inherit_ask_class(OWNER(v49777),Language._If) != CTRUE)
       (Optimize.OPT->level = ((CL_INT)Optimize.OPT->level-(CL_INT)1));
      }
    }
  else { OID  v52338 = GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
        _oid_(append_symbol(gensym_void(),_string_("I")))));
      new_block_void();
      interface_I_class(Kernel._boolean);
      princ_string(" ");
      princ_string(string_v(v52338));
      princ_string(";");
      breakline_void();
      statement_any(GC_OID(v45520->test),v52338,v43304);
      breakline_void();
      (Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
      princ_string("if (");
      princ_string(string_v(v52338));
      princ_string(" == ");
      (*Generate.produce)(Generate.PRODUCER->value,
        Kernel.ctrue);
      princ_string(") ");
      statement_any(GC_OID(v45520->arg),v52335,v43304);
      (Optimize.OPT->level = ((CL_INT)Optimize.OPT->level-(CL_INT)1));
      if ((Kernel._string == OWNER(v52335)) || 
          (boolean_I_any(v45520->other) == CTRUE))
       { princ_string("else ");
        statement_any(GC_OID(v45520->other),v52335,v43304);
        }
      close_block_void();
      }
    GC_UNBIND; POP_SIGNAL;}

void  self_statement_Do(Do *v45520,OID v52335,OID v43304)
{ GC_BIND;
  if (v45520->args->length == 1)
   statement_any(GC_OID((*(v45520->args))[1]),v52335,v43304);
  else { list * v52331 = GC_OBJECT(list,v45520->args);
      CL_INT  v52329 = v52331->length;
      ClaireBoolean * v52318 = Optimize.OPT->alloc_stack;
      CL_INT  v52333 = 0;
      (Optimize.OPT->alloc_stack = CFALSE);
      new_block_void();
      inner_statement_any(_oid_(v45520),v52335,v43304);
      close_block_void();
      }
    GC_UNBIND; POP_SIGNAL;}

void  inner_statement_any(OID v45520,OID v52335,OID v43304)
{ GC_BIND;
  if (INHERIT(OWNER(v45520),Language._Do))
   { list * v52331 = GC_OBJECT(list,OBJECT(Do,v45520)->args);
    CL_INT  v52329 = v52331->length;
    ClaireBoolean * v52318 = Optimize.OPT->alloc_stack;
    CL_INT  v52333 = 0;
    (Optimize.OPT->alloc_stack = CFALSE);
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v52340);
      for (START(v52331); NEXT(v52340);)
      { ++v52333;
        if (v52333 == v52329)
         { (Optimize.OPT->alloc_stack = v52318);
          inner_statement_any(v52340,v52335,v43304);
          }
        else if (boolean_I_any(v52340) == CTRUE)
         inner_statement_any(v52340,_oid_(Kernel.emptySet),v43304);
        }
      }
    }
  else statement_any(v45520,v52335,v43304);
    GC_UNBIND; POP_SIGNAL;}

void  self_statement_Let(Let *v45520,OID v52335,OID v43304)
{ (*Generate.stat_let)(Generate.PRODUCER->value,
    _oid_(v45520),
    v52335,
    v43304);
  POP_SIGNAL;}

void  self_statement_And(And *v45520,OID v52335,OID v43304)
{ GC_BIND;
  { char * v52338 = GC_STRING(check_var_string("v_and",v52335,v43304));
    new_block_void();
    interface_I_class(Kernel._boolean);
    princ_string(v52338);
    princ_string(";");
    breakline_void();
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52340);
      bag *v52340_support;
      v52340_support = GC_OBJECT(list,v45520->args);
      for (START(v52340_support); NEXT(v52340);)
      { new_block_void();
        statement_any(v52340,_string_(v52338),v43304);
        princ_string("if (");
        princ_string(v52338);
        princ_string(" == ");
        (*Generate.produce)(Generate.PRODUCER->value,
          Kernel.cfalse);
        princ_string(") ");
        if (Kernel._string == OWNER(v52335))
         { c_princ_string(string_v(v52335));
          princ_string(" =");
          }
        expression_boolean(CFALSE,v43304);
        princ_string("; ");
        breakline_void();
        princ_string("else ");
        }
      }
    if (Kernel._string == OWNER(v52335))
     { c_princ_string(string_v(v52335));
      princ_string(" = ");
      expression_boolean(CTRUE,v43304);
      princ_string(";");
      }
    else { expression_boolean(CTRUE,v43304);
        princ_string(";");
        }
      { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52340);
      bag *v52340_support;
      v52340_support = GC_OBJECT(list,v45520->args);
      for (START(v52340_support); NEXT(v52340);)
      close_block_void();
      }
    close_block_void();
    }
  GC_UNBIND; POP_SIGNAL;}

void  self_statement_Or(Or *v45520,OID v52335,OID v43304)
{ GC_BIND;
  { char * v52338 = GC_STRING(check_var_string("v_or",v52335,v43304));
    new_block_void();
    interface_I_class(Kernel._boolean);
    princ_string(v52338);
    princ_string(";");
    breakline_void();
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52340);
      bag *v52340_support;
      v52340_support = GC_OBJECT(list,v45520->args);
      for (START(v52340_support); NEXT(v52340);)
      { new_block_void();
        statement_any(v52340,_string_(v52338),v43304);
        princ_string("if (");
        princ_string(v52338);
        princ_string(" == ");
        (*Generate.produce)(Generate.PRODUCER->value,
          Kernel.ctrue);
        princ_string(") ");
        if (Kernel._string == OWNER(v52335))
         { c_princ_string(string_v(v52335));
          princ_string(" =");
          }
        expression_boolean(CTRUE,v43304);
        princ_string("; ");
        breakline_void();
        princ_string("else ");
        }
      }
    if (Kernel._string == OWNER(v52335))
     { c_princ_string(string_v(v52335));
      princ_string(" = ");
      expression_boolean(CFALSE,v43304);
      princ_string(";");
      }
    else { expression_boolean(CFALSE,v43304);
        princ_string(";");
        }
      { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52340);
      bag *v52340_support;
      v52340_support = GC_OBJECT(list,v45520->args);
      for (START(v52340_support); NEXT(v52340);)
      close_block_void();
      }
    close_block_void();
    }
  GC_UNBIND; POP_SIGNAL;}

void  self_statement_While(While *v45520,OID v52335,OID v43304)
{ (*Generate.stat_while)(Generate.PRODUCER->value,
    _oid_(v45520),
    v52335,
    v43304);
  POP_SIGNAL;}

void  self_statement_Assign(Assign *v45520,OID v52335,OID v43304)
{ GC_BIND;
  { OID  v52338 = GC_OID(v45520->var);
    OID  v52340 = GC_OID(v45520->arg);
    ClaireBoolean * v47218 = ((boolean_I_any(v43304) == CTRUE) ? ((Optimize.OPT->loop_gc == CTRUE) ? ((inner2outer_ask_any(v52340) == CTRUE) ? CTRUE: CFALSE): CFALSE): CFALSE);
    OID  v52341;
    { if ((v47218 == CTRUE) && 
          (INHERIT(OWNER(v52340),Optimize._to_protect)))
       v52341 = (*Kernel.arg)(v52340);
      else v52341 = v52340;
        GC_OID(v52341);}
    if (Kernel._string == OWNER(v52335))
     { new_block_void();
      statement_any(v52341,v52335,v43304);
      princ_string(" ");
      if (v47218 == CTRUE)
       (*Generate.gc_protection_exp)(Generate.PRODUCER->value,
        v52338,
        Kernel.cfalse,
        v52335,
        v43304);
      else { ident_symbol(OBJECT(Variable,v52338)->pname);
          princ_string(" = ");
          (*Kernel.c_princ)(v52335);
          }
        princ_string(";");
      close_block_void();
      }
    else if (v47218 == CTRUE)
     { new_block_void();
      statement_any(v52341,GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
        v52338)),v43304);
      princ_string(" ");
      (*Generate.gc_protection_exp)(Generate.PRODUCER->value,
        v52338,
        Kernel.ctrue,
        v52338,
        v43304);
      princ_string(";");
      close_block_void();
      }
    else statement_any(v52340,GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
        v52338)),v43304);
      }
  GC_UNBIND; POP_SIGNAL;}

void  self_statement_Gassign(Gassign *v45520,OID v52335,OID v43304)
{ (*Generate.stat_gassign)(Generate.PRODUCER->value,
    _oid_(v45520),
    v52335,
    v43304);
  POP_SIGNAL;}

void  self_statement_to_protect(Compile_to_protect *v45520,OID v52335,OID v43304)
{ GC_BIND;
  if ((Optimize.OPT->protection == CTRUE) && 
      (Kernel._string == OWNER(v52335)))
   { ClaireClass * v52319 = OBJECT(ClaireClass,(*Optimize.c_sort)(GC_OID(v45520->arg)));
    new_block_void();
    statement_any(GC_OID(v45520->arg),v52335,v43304);
    princ_string(gc_protect_class(v52319));
    princ_string("(");
    if (INHERIT(v52319,Kernel._object))
     { class_princ_class(psort_any(GC_OID((*Optimize.c_type)(GC_OID(v45520->arg)))));
      princ_string(",");
      }
    (*Kernel.c_princ)(v52335);
    princ_string(");");
    close_block_void();
    }
  else statement_any(GC_OID(v45520->arg),v52335,v43304);
    GC_UNBIND; POP_SIGNAL;}

void  self_statement_For(For *v45520,OID v52335,OID v43304)
{ (*Generate.stat_for)(Generate.PRODUCER->value,
    _oid_(v45520),
    v52335,
    v43304);
  POP_SIGNAL;}

void  self_statement_Iteration(Iteration *v45520,OID v52335,OID v43304)
{ (*Generate.stat_iteration)(Generate.PRODUCER->value,
    _oid_(v45520),
    v52335,
    v43304);
  POP_SIGNAL;}

void  self_statement_Return(Return *v45520,OID v52335,OID v43304)
{ GC_BIND;
  if (v43304 == CNULL)
   { new_block_void();
    statement_any(GC_OID(v45520->arg),_oid_(Kernel.emptySet),_oid_(Kernel.emptySet));
    princ_string("ClEnv->cHandle = loop_handle; break;");
    close_block_void();
    }
  else if (Kernel._string == OWNER(v43304))
   { new_block_void();
    statement_any(GC_OID(v45520->arg),v43304,_oid_(Kernel.emptySet));
    princ_string("ClEnv->cHandle = loop_handle;break;");
    close_block_void();
    }
  else close_exception(((general_error *) (*Core._general_error)(_string_("[204] break not inside a For or While:~S"),
      _oid_(list::alloc(1,_oid_(v45520))))));
    GC_UNBIND; POP_SIGNAL;}

void  self_statement_Call(Call *v45520,OID v52335,OID v43304)
{ GC_BIND;
  { OID  v39937 = GC_OID(Optimize._starcall_star->value);
    if (v45520->location->length != 0)
     (Optimize._starcall_star->value= _oid_(v45520));
    { list * v52331 = GC_OBJECT(list,v45520->args);
      list * v49404 = GC_OBJECT(list,unfold_args_list(v52331));
      Call * v52319;
      { { Call * v2855;
          { Call * v47292 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            (v47292->selector = v45520->selector);
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v47292));
            v2855 = v47292;
            }
          v52319 = loc_I_Call1(v2855);
          }
        GC_OBJECT(Call,v52319);}
      { Call * v30280 = v52319; 
        list * v30281;
        { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v52343; CL_INT CLcount;
          v_list = v52331;
           v30281 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v52343 = (*(v_list))[CLcount];
            v_val = unfold_arg_list(v52331,v49404,v52343);
            
            (*((list *) v30281))[CLcount] = v_val;}
          }
        (v30280->args = v30281);}
      unfold_use_list(v49404,_oid_(v52319),v52335,v43304);
      }
    (Optimize._starcall_star->value= v39937);
    }
  GC_UNBIND; POP_SIGNAL;}

void  self_statement_Call_method(Call_method *v45520,OID v52335,OID v43304)
{ GC_BIND;
  { OID  v39937 = GC_OID(Optimize._starcall_star->value);
    if (v45520->location->length != 0)
     (Optimize._starcall_star->value= _oid_(v45520));
    { list * v52331 = GC_OBJECT(list,v45520->args);
      list * v49404 = GC_OBJECT(list,unfold_args_list(v52331));
      Call_method * v52319;
      { { OID v40982;{ OID  v5738;
            { Call_method * v47292 = ((Call_method *) GC_OBJECT(Call_method,new_object_class(Language._Call_method)));
              (v47292->arg = v45520->arg);
              add_I_property(Kernel.instances,Language._Call_method,11,_oid_(v47292));
              v5738 = _oid_(v47292);
              }
            v40982 = (*Optimize.loc_I)(v5738);
            }
          
          v52319=OBJECT(Call_method,v40982);}
        GC_OBJECT(Call_method,v52319);}
      { Call_method * v30283 = v52319; 
        list * v30285;
        { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v52343; CL_INT CLcount;
          v_list = v52331;
           v30285 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v52343 = (*(v_list))[CLcount];
            v_val = unfold_arg_list(v52331,v49404,v52343);
            
            (*((list *) v30285))[CLcount] = v_val;}
          }
        (v30283->args = v30285);}
      unfold_use_list(v49404,_oid_(v52319),v52335,v43304);
      }
    (Optimize._starcall_star->value= v39937);
    }
  GC_UNBIND; POP_SIGNAL;}

void  self_statement_Call_method1(Call_method1 *v45520,OID v52335,OID v43304)
{ GC_BIND;
  { OID  v39937 = GC_OID(Optimize._starcall_star->value);
    if (v45520->location->length != 0)
     (Optimize._starcall_star->value= _oid_(v45520));
    { list * v52331 = GC_OBJECT(list,v45520->args);
      list * v49404 = GC_OBJECT(list,unfold_args_list(v52331));
      Call_method1 * v52319;
      { { Call_method1 * v8621;
          { Call_method1 * v47292 = ((Call_method1 *) GC_OBJECT(Call_method1,new_object_class(Language._Call_method1)));
            (v47292->arg = v45520->arg);
            add_I_property(Kernel.instances,Language._Call_method1,11,_oid_(v47292));
            v8621 = v47292;
            }
          v52319 = loc_I_Call_method11(v8621);
          }
        GC_OBJECT(Call_method1,v52319);}
      { Call_method * v30287 = v52319; 
        list * v30288;
        { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v52343; CL_INT CLcount;
          v_list = v52331;
           v30288 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v52343 = (*(v_list))[CLcount];
            v_val = unfold_arg_list(v52331,v49404,v52343);
            
            (*((list *) v30288))[CLcount] = v_val;}
          }
        (v30287->args = v30288);}
      unfold_use_list(v49404,_oid_(v52319),v52335,v43304);
      }
    (Optimize._starcall_star->value= v39937);
    }
  GC_UNBIND; POP_SIGNAL;}

void  self_statement_Call_method2(Call_method2 *v45520,OID v52335,OID v43304)
{ GC_BIND;
  { OID  v39937 = GC_OID(Optimize._starcall_star->value);
    if (v45520->location->length != 0)
     (Optimize._starcall_star->value= _oid_(v45520));
    { list * v52331 = GC_OBJECT(list,v45520->args);
      list * v49404 = GC_OBJECT(list,unfold_args_list(v52331));
      Call_method2 * v52319;
      { { Call_method2 * v31685;
          { Call_method2 * v47292 = ((Call_method2 *) GC_OBJECT(Call_method2,new_object_class(Language._Call_method2)));
            (v47292->arg = v45520->arg);
            add_I_property(Kernel.instances,Language._Call_method2,11,_oid_(v47292));
            v31685 = v47292;
            }
          v52319 = loc_I_Call_method21(v31685);
          }
        GC_OBJECT(Call_method2,v52319);}
      { Call_method * v30310 = v52319; 
        list * v30311;
        { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v52343; CL_INT CLcount;
          v_list = v52331;
           v30311 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v52343 = (*(v_list))[CLcount];
            v_val = unfold_arg_list(v52331,v49404,v52343);
            
            (*((list *) v30311))[CLcount] = v_val;}
          }
        (v30310->args = v30311);}
      unfold_use_list(v49404,_oid_(v52319),v52335,v43304);
      }
    (Optimize._starcall_star->value= v39937);
    }
  GC_UNBIND; POP_SIGNAL;}

void  self_statement_Super(Super *v45520,OID v52335,OID v43304)
{ (*Generate.stat_super)(Generate.PRODUCER->value,
    _oid_(v45520),
    v52335,
    v43304);
  POP_SIGNAL;}

void  self_statement_Cast(Cast *v45520,OID v52335,OID v43304)
{ GC_BIND;
  statement_any(GC_OID(v45520->arg),v52335,v43304);
  GC_UNBIND; POP_SIGNAL;}

void  self_statement_Handle(ClaireHandle *v45520,OID v52335,OID v43304)
{ (*Generate.stat_handle)(Generate.PRODUCER->value,
    _oid_(v45520),
    v52335,
    v43304);
  POP_SIGNAL;}

void  self_statement_to_CL(Compile_to_CL *v45520,OID v52335,OID v43304)
{ GC_BIND;
  if (Kernel._string == OWNER(v52335))
   { Variable * v164 = GC_OBJECT(Variable,build_Variable_string(string_I_symbol(gensym_string("V_CL")),_oid_(v45520->set_arg)));
    ClaireClass * v49571 = ((v45520->set_arg == Kernel._void) ?
      Kernel._any :
      v45520->set_arg );
    new_block_void();
    interface_I_class(v49571);
    princ_string(" ");
    expression_Variable(v164,v43304);
    princ_string(";");
    statement_any(GC_OID(v45520->arg),GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
      _oid_(v164))),v43304);
    breakline_void();
    princ_string(string_v(v52335));
    princ_string("=");
    (*Generate.to_cl)(Generate.PRODUCER->value,
      _oid_(v164),
      _oid_(v45520->set_arg),
      v43304);
    princ_string(";");
    close_block_void();
    }
  else statement_any(GC_OID(v45520->arg),v52335,v43304);
    GC_UNBIND; POP_SIGNAL;}

void  self_statement_to_C(Compile_to_C *v45520,OID v52335,OID v43304)
{ GC_BIND;
  if (Kernel._string == OWNER(v52335))
   { Variable * v164 = GC_OBJECT(Variable,build_Variable_string("V_C",_oid_(Kernel._any)));
    new_block_void();
    (*Generate.any_interface)(Generate.PRODUCER->value);
    princ_string(" ");
    (*Language.ident)(Generate.PRODUCER->value,
      _oid_(v164));
    princ_string(";");
    statement_any(GC_OID(v45520->arg),GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
      _oid_(v164))),v43304);
    breakline_void();
    princ_string(string_v(v52335));
    princ_string("=");
    (*Generate.to_c)(Generate.PRODUCER->value,
      _oid_(v164),
      _oid_(v45520->set_arg),
      v43304);
    princ_string(";");
    close_block_void();
    }
  else statement_any(GC_OID(v45520->arg),v52335,v43304);
    GC_UNBIND; POP_SIGNAL;}

void  self_statement_C_cast(Compile_C_cast *v45520,OID v52335,OID v43304)
{ GC_BIND;
  if (Kernel._string == OWNER(v52335))
   { char * v164 = GC_STRING(check_var_string("V_CC",v52335,v43304));
    ClaireClass * v49571 = v45520->set_arg;
    ClaireClass * v49572 = stupid_t_any1(GC_OID(v45520->arg));
    ClaireType * v49602 = join_class(osort_any(_oid_(v49571)),v49572);
    new_block_void();
    (*Generate.define_variable)(Generate.PRODUCER->value,
      _oid_(v49602),
      _string_(v164));
    breakline_void();
    statement_any(GC_OID(v45520->arg),_string_(v164),v43304);
    princ_string(string_v(v52335));
    princ_string("= ");
    (*Generate.pointer_cast)(Generate.PRODUCER->value,
      _oid_(v49571));
    princ_string(" ");
    princ_string(v164);
    princ_string(";");
    close_block_void();
    }
  else statement_any(GC_OID(v45520->arg),v52335,v43304);
    GC_UNBIND; POP_SIGNAL;}

void  self_statement_Call_slot(Call_slot *v45520,OID v52335,OID v43304)
{ GC_BIND;
  { char * v24120 = string_I_symbol(gensym_void());
    Variable * v164 = GC_OBJECT(Variable,build_Variable_string(v24120,GC_OID((*Optimize.c_type)(GC_OID(v45520->arg)))));
    new_block_void();
    interface_I_class(sort_Variable(v164));
    princ_string(" ");
    expression_Variable(v164,_oid_(Kernel.emptySet));
    princ_string(";");
    breakline_void();
    statement_any(GC_OID(v45520->arg),_string_(v24120),v43304);
    breakline_void();
    if (Kernel._string == OWNER(v52335))
     { c_princ_string(string_v(v52335));
      princ_string(" = ");
      }
    { Call_slot * v34568;
      { Call_slot * v47292 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
        (v47292->selector = v45520->selector);
        (v47292->arg = _oid_(v164));
        add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v47292));
        v34568 = v47292;
        }
      expression_Call_slot(v34568,v43304);
      }
    princ_string(";");
    close_block_void();
    }
  GC_UNBIND; POP_SIGNAL;}

void  self_statement_Call_table(Call_table *v45520,OID v52335,OID v43304)
{ GC_BIND;
  { char * v24120 = string_I_symbol(gensym_void());
    Variable * v164 = GC_OBJECT(Variable,build_Variable_string(v24120,GC_OID((*Optimize.c_type)(GC_OID(v45520->arg)))));
    new_block_void();
    interface_I_class(sort_Variable(v164));
    princ_string(" ");
    expression_Variable(v164,_oid_(Kernel.emptySet));
    princ_string(";");
    breakline_void();
    statement_any(GC_OID(v45520->arg),_string_(v24120),v43304);
    breakline_void();
    if (Kernel._string == OWNER(v52335))
     { c_princ_string(string_v(v52335));
      princ_string(" = ");
      }
    { Call_table * v35529;
      { Call_table * v47292 = ((Call_table *) GC_OBJECT(Call_table,new_object_class(Language._Call_table)));
        (v47292->selector = v45520->selector);
        (v47292->arg = _oid_(v164));
        add_I_property(Kernel.instances,Language._Call_table,11,_oid_(v47292));
        v35529 = v47292;
        }
      expression_Call_table(v35529,v43304);
      }
    princ_string(";");
    close_block_void();
    }
  GC_UNBIND; POP_SIGNAL;}

void  self_statement_Call_array(Call_array *v45520,OID v52335,OID v43304)
{ GC_BIND;
  { Variable * v5133 = GC_OBJECT(Variable,build_Variable_string("va_arg1",_oid_(Kernel._array)));
    Variable * v5134 = GC_OBJECT(Variable,build_Variable_string("va_arg2",_oid_(Kernel._integer)));
    new_block_void();
    interface_I_class(Kernel._array);
    princ_string(" ");
    expression_Variable(v5133,_oid_(Kernel.emptySet));
    princ_string(";");
    breakline_void();
    interface_I_class(Kernel._integer);
    princ_string(" ");
    expression_Variable(v5134,_oid_(Kernel.emptySet));
    princ_string(";");
    breakline_void();
    statement_any(GC_OID(v45520->selector),_string_("va_arg1"),v43304);
    statement_any(GC_OID(v45520->arg),_string_("va_arg2"),v43304);
    if (Kernel._string == OWNER(v52335))
     { c_princ_string(string_v(v52335));
      princ_string(" = ");
      }
    { Call_array * v36490;
      { Call_array * v47292 = ((Call_array *) GC_OBJECT(Call_array,new_object_class(Language._Call_array)));
        (v47292->selector = _oid_(v5133));
        (v47292->arg = _oid_(v5134));
        (v47292->test = v45520->test);
        add_I_property(Kernel.instances,Language._Call_array,11,_oid_(v47292));
        v36490 = v47292;
        }
      expression_Call_array(v36490,v43304);
      }
    princ_string(";");
    close_block_void();
    }
  GC_UNBIND; POP_SIGNAL;}

void  self_statement_Update(Update *v45520,OID v52335,OID v43304)
{ GC_BIND;
  { OID  v52308 = GC_OID(v45520->var);
    OID  v52332 = GC_OID(v45520->selector);
    ClaireType * v49570;
    { if (INHERIT(OWNER(v52308),Language._Call_slot))
       v49570 = domain_I_restriction(OBJECT(Call_slot,v52308)->selector);
      else if (INHERIT(OWNER(v52308),Language._Call_array))
       v49570 = Kernel._integer;
      else v49570 = U_type(Kernel._any,GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.domain)(v52332))));
        GC_OBJECT(ClaireType,v49570);}
    ClaireType * v49571;
    { if (INHERIT(OWNER(v52308),Language._Call_slot))
       { v49571 = ((v45520->arg == _oid_(Kernel.add)) ?
          member_type(OBJECT(Call_slot,v52308)->selector->range) :
          OBJECT(Call_slot,v52308)->selector->range );
        }
      else if (INHERIT(OWNER(v52308),Language._Call_array))
       { v49571 = (((OBJECT(ClaireBoolean,(*Core._inf_equalt)(GC_OID(OBJECT(Call_array,v52308)->test),
          _oid_(Kernel._float)))) == CTRUE) ?
          Kernel._float :
          Kernel._any );
        }
      else v49571 = U_type(Kernel._any,GC_OBJECT(ClaireType,((v45520->arg == _oid_(Kernel.add)) ?
          member_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(v52332)))) :
          OBJECT(ClaireType,(*Kernel.range)(v52332)) )));
        GC_OBJECT(ClaireType,v49571);}
    ClaireClass * v31437 = stupid_t_any1(GC_OID((*Kernel.arg)(v45520->var)));
    ClaireClass * v31438 = stupid_t_any1(GC_OID(v45520->value));
    OID  v11925;
    { if ((_inf_equalt_class(v31437,psort_any(_oid_(v49570))) != CTRUE) && 
          (_inf_equalt_class(v31437,Kernel._object) == CTRUE))
       { Compile_C_cast * v47292 = ((Compile_C_cast *) GC_OBJECT(Compile_C_cast,new_object_class(Optimize._C_cast)));
        (v47292->arg = (*Kernel.arg)(GC_OID(v45520->var)));
        (v47292->set_arg = psort_any(_oid_(v49570)));
        add_I_property(Kernel.instances,Optimize._C_cast,11,_oid_(v47292));
        v11925 = _oid_(v47292);
        }
      else v11925 = (*Kernel.arg)(GC_OID(v45520->var));
        GC_OID(v11925);}
    OID  v12784;
    { if ((_inf_equalt_class(v31438,psort_any(_oid_(v49571))) != CTRUE) && 
          (_inf_equalt_class(v31438,Kernel._object) == CTRUE))
       { Compile_C_cast * v47292 = ((Compile_C_cast *) GC_OBJECT(Compile_C_cast,new_object_class(Optimize._C_cast)));
        (v47292->arg = v45520->value);
        (v47292->set_arg = psort_any(_oid_(v49571)));
        add_I_property(Kernel.instances,Optimize._C_cast,11,_oid_(v47292));
        v12784 = _oid_(v47292);
        }
      else v12784 = v45520->value;
        GC_OID(v12784);}
    Variable * v5133 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,v49570));
    Variable * v5134 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,v49571));
    ClaireBoolean * v49043 = c_func_any(v11925);
    new_block_void();
    interface_I_class(psort_any(_oid_(v49570)));
    princ_string(" ");
    expression_Variable(v5133,_oid_(Kernel.emptySet));
    princ_string(" ");
    if (v49043 == CTRUE)
     { princ_string("= ");
      (*Generate.expression)(v11925,
        _oid_(Kernel.emptySet));
      }
    princ_string("; ");
    breakline_void();
    interface_I_class(psort_any(_oid_(v49571)));
    princ_string(" ");
    expression_Variable(v5134,_oid_(Kernel.emptySet));
    princ_string(";");
    breakline_void();
    if (v49043 != CTRUE)
     statement_any(v11925,GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
      _oid_(v5133))),v43304);
    statement_any(v12784,GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
      _oid_(v5134))),v43304);
    if (Kernel._string == OWNER(v52335))
     { c_princ_string(string_v(v52335));
      princ_string(" = ");
      }
    { Update * v37451;
      { Update * v47292 = ((Update *) GC_OBJECT(Update,new_object_class(Language._Update)));
        (v47292->selector = v52332);
        { Update * v30316 = v47292; 
          OID  v30317;
          if (v45520->arg == _oid_(Kernel.add))
           v30317 = _oid_(Kernel.add);
          else if (sort_Variable(v5133) == Kernel._any)
           v30317 = _oid_(v5133);
          else { Compile_to_CL * v47292 = ((Compile_to_CL *) GC_OBJECT(Compile_to_CL,new_object_class(Optimize._to_CL)));
              (v47292->arg = _oid_(v5133));
              (v47292->set_arg = sort_Variable(v5133));
              add_I_property(Kernel.instances,Optimize._to_CL,11,_oid_(v47292));
              v30317 = _oid_(v47292);
              }
            (v30316->arg = v30317);}
        (v47292->value = _oid_(v5134));
        { Update * v30318 = v47292; 
          OID  v30340;
          { OID  v49796 = GC_OID((*Kernel.copy)(v52308));
            put_property2(Kernel.arg,OBJECT(ClaireObject,v49796),_oid_(v5133));
            v30340 = v49796;
            }
          (v30318->var = v30340);}
        add_I_property(Kernel.instances,Language._Update,11,_oid_(v47292));
        v37451 = v47292;
        }
      expression_Update(v37451,v43304);
      }
    princ_string(";");
    close_block_void();
    }
  GC_UNBIND; POP_SIGNAL;}



