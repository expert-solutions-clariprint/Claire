/***** CLAIRE Compilation of file ./compile/cgen.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:51 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>
#include <Optimize.h>
#include <Generate.h>
char * c_string_c_producer1(Generate_c_producer *v52319,Variable *v45520)
{ GC_BIND;
  { char *Result ;
    if (Optimize.compiler->naming == 2)
     Result = append_string("v",GC_STRING(string_I_integer (integer_I_symbol(v45520->pname))));
    else { print_in_string_void();
        ident_c_producer(v52319,v45520->pname);
        Result = end_of_string_void();
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

char * c_string_c_producer2(Generate_c_producer *v52319,symbol *v45520)
{ print_in_string_void();
  ident_c_producer(v52319,v45520);
  POP_SIGNAL; return (end_of_string_void());}

char * string_I_c_producer1(Generate_c_producer *v52319,Variable *v45520)
{ GC_BIND;
  { char *Result ;
    if (Optimize.compiler->naming == 2)
     Result = append_string("v",GC_STRING(string_I_integer (integer_I_symbol(v45520->pname))));
    else { print_in_string_void();
        ident_c_producer(v52319,v45520->pname);
        Result = end_of_string_void();
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

char * string_I_c_producer2(Generate_c_producer *v52319,symbol *v45520)
{ print_in_string_void();
  ident_c_producer(v52319,v45520);
  POP_SIGNAL; return (end_of_string_void());}

void  ident_c_producer3(Generate_c_producer *v52319,Variable *v52338)
{ GC_BIND;
  if (Optimize.compiler->naming == 2)
   princ_string(append_string("v",GC_STRING(string_I_integer (integer_I_symbol(v52338->pname)))));
  else { symbol * v52335 = v52338->pname;
      CL_INT  v52333 = index_list(v52319->bad_names,_oid_(v52335));
      if (v52333 == 0)
       { if ((LENGTH_STRING(v52335->name) == 2) && 
            (v52335->name[1 - 1] == ((unsigned char)95 /* '_' */)))
         princ_string("us");
        c_princ_string(string_I_symbol(v52335));
        }
      else c_princ_symbol(OBJECT(symbol,(*(v52319->good_names))[v52333]));
        }
    GC_UNBIND; POP_SIGNAL;}

void  ident_c_producer(Generate_c_producer *v52319,symbol *v52335)
{ { CL_INT  v52333 = index_list(v52319->bad_names,_oid_(v52335));
    if (v52333 == 0)
     { if ((LENGTH_STRING(v52335->name) == 2) && 
          (v52335->name[1 - 1] == ((unsigned char)95 /* '_' */)))
       princ_string("us");
      c_princ_string(string_I_symbol(v52335));
      }
    else c_princ_symbol(OBJECT(symbol,(*(v52319->good_names))[v52333]));
      }
  POP_SIGNAL;}

void  class_princ_c_producer(Generate_c_producer *v52319,ClaireClass *v45520)
{ if (v45520->name->module_I != claire.it)
   { ident_c_producer(v52319,v45520->name->module_I->name);
    princ_string("_");
    }
  ident_c_producer(v52319,v45520->name);
  POP_SIGNAL;}

void  produce_c_producer2(Generate_c_producer *v52319,OID v52340)
{ if (INHERIT(OWNER(v52340),Kernel._function))
   { princ_string("_function_(");
    c_princ_function(OBJECT(ClaireFunction,v52340));
    princ_string(",");
    print_any(_string_(string_I_function(OBJECT(ClaireFunction,v52340))));
    princ_string(")");
    }
  else if (INHERIT(OWNER(v52340),Kernel._char))
   { princ_string("_char_(((unsigned char)");
    print_any(((OID)OBJECT(ClaireChar,v52340)->ascii));
    princ_string(" /* ");
    print_any(v52340);
    princ_string(" */))");
    }
  else if (INHERIT(OWNER(v52340),Kernel._environment))
   princ_string("ClEnv");
  else if (Kernel._string == OWNER(v52340))
   print_any(v52340);
  else if (INHERIT(OWNER(v52340),Core._global_variable))
   globalVar_c_producer(v52319,OBJECT(global_variable,v52340));
  else if (Kernel._boolean == OWNER(v52340))
   { if ((OBJECT(ClaireBoolean,v52340)) == CTRUE)
     princ_string("CTRUE");
    else princ_string("CFALSE");
      }
  else if (INHERIT(OWNER(v52340),Kernel._symbol))
   { princ_string("symbol::make(");
    print_any(_string_(string_I_symbol(OBJECT(symbol,v52340))));
    princ_string(",");
    ident_symbol(OBJECT(symbol,v52340)->module_I->name);
    princ_string(",");
    ident_symbol(defined_symbol(OBJECT(symbol,v52340))->name);
    princ_string(")");
    }
  else if (INHERIT(OWNER(v52340),Kernel._class))
   { if (v52340 == _oid_(Kernel._cl_import))
     princ_string("Kernel._cl_import");
    else { ident_c_producer(v52319,defined_symbol(OBJECT(ClaireClass,v52340)->name)->name);
        princ_string("._");
        c_princ_string(string_I_symbol(OBJECT(ClaireClass,v52340)->name));
        }
      }
  else if (INHERIT(OWNER(v52340),Reader._reserved_keyword))
   { ident_c_producer(v52319,defined_symbol(OBJECT(thing,v52340)->name)->name);
    princ_string("._cl_");
    c_princ_string(string_I_symbol(OBJECT(thing,v52340)->name));
    }
  else if (INHERIT(OWNER(v52340),Kernel._thing))
   { if (INHERIT(OBJECT(ClaireObject,v52340)->isa,Kernel._module))
     { ident_c_producer(v52319,OBJECT(thing,v52340)->name);
      princ_string(".it");
      }
    else { ident_c_producer(v52319,defined_symbol(OBJECT(thing,v52340)->name)->name);
        princ_string(".");
        ident_symbol(OBJECT(thing,v52340)->name);
        }
      }
  else princ_string("CNULL");
    POP_SIGNAL;}

void  globalVar_c_producer(Generate_c_producer *v52319,global_variable *v52340)
{ GC_BIND;
  if ((equal(_oid_(v52340->range),_oid_(Kernel.emptySet)) == CTRUE) && 
      (INHERIT(OWNER(v52340->value),Kernel._integer)))
   { princ_string("(OID)(");
    print_any(GC_OID(v52340->value));
    princ_string(")");
    }
  else { ident_c_producer(v52319,defined_symbol(v52340->name)->name);
      princ_string(".");
      ident_symbol(v52340->name);
      if (nativeVar_ask_global_variable(v52340) != CTRUE)
       princ_string("->value");
      else ;}
    GC_UNBIND; POP_SIGNAL;}

void  stat_exp_c_producer(Generate_c_producer *v52319,OID v45520,OID v43304)
{ GC_BIND;
  if (INHERIT(OWNER(v45520),Optimize._to_C))
   stat_exp_c_producer(v52319,GC_OID(OBJECT(Compile_to_C,v45520)->arg),v43304);
  else if (INHERIT(OWNER(v45520),Optimize._to_CL))
   stat_exp_c_producer(v52319,GC_OID(OBJECT(Compile_to_CL,v45520)->arg),v43304);
  else if (designated_ask_any(v45520) == CTRUE)
   princ_string(";");
  else { (*Generate.expression)(v45520,
        v43304);
      princ_string(";");
      breakline_void();
      }
    GC_UNBIND; POP_SIGNAL;}

void  namespace_I_c_producer(Generate_c_producer *v52319,module *v52329)
{ princ_string("\n\n// namespace class for ");
  print_any(_oid_(v52329));
  princ_string(" \n");
  { princ_string("class ");
    ident_c_producer(v52319,v52329->name);
    princ_string("Class: public NameSpace {\npublic:\n");
    }
  POP_SIGNAL;}

void  module_I_c_producer(Generate_c_producer *v52319,module *v52329)
{ princ_string("\n\n// module definition \n");
  princ_string(" void metaLoad();};\n\n");
  princ_string("extern ");
  ident_c_producer(v52319,v52329->name);
  princ_string("Class ");
  ident_c_producer(v52319,v52329->name);
  princ_string(";\n");
  { module * v49385 = v52329->part_of;
    { CL_INT loop_handle = ClEnv->cHandle;
      while (((boolean_I_any(_oid_(v49385->made_of)) != CTRUE) && 
          (v49385 != claire.it)))
      { princ_string("extern NameSpace ");
        ident_c_producer(v52319,v49385->name);
        princ_string(";\n");
        v49385= v49385->part_of;
        POP_SIGNAL;}
      }
    }
  POP_SIGNAL;}

void  declare_c_producer(Generate_c_producer *v52319,property *v52332)
{ breakline_void();
  { expression_thing(v52332,Core.nil->value);
    princ_string(" = ");
    princ_string(((INHERIT(v52332->isa,Kernel._operation)) ?
      "operation" :
      "property" ));
    princ_string("::make(");
    print_any(_string_(string_I_symbol(v52332->name)));
    princ_string(",");
    if ((v52332->open != 1) || 
        ((CL_INT)v52332->dispatcher > 0))
     { expression_integer(v52332->open,_oid_(Kernel.emptySet));
      princ_string(",");
      }
    expression_thing(v52332->name->module_I,Core.nil->value);
    if (INHERIT(v52332->isa,Kernel._operation))
     { princ_string(",");
      princ_integer(CLREAD(operation,v52332,precedence));
      }
    else if ((CL_INT)v52332->dispatcher > 0)
     { princ_string(",");
      (*Generate.expression)(_oid_(v52332->domain),
        Core.nil->value);
      princ_string(",");
      princ_integer(v52332->dispatcher);
      }
    princ_string(");");
    }
  POP_SIGNAL;}

void  start_module_interface_c_producer(Generate_c_producer *v52319,module *v45520)
{ GC_BIND;
  { char * v46648 = GC_STRING(append_string(GC_STRING(Optimize.compiler->headers_dir),GC_STRING(append_string(GC_STRING(append_string(GC_STRING(string_v(Core._starfs_star->value)),GC_STRING(c_string_c_producer2(v52319,v45520->name)))),".h"))));
    (Optimize.OPT->cinterface = fopen_string1(v46648,"w"));
    use_as_output_port(Optimize.OPT->cinterface);
    princ_string("// interface definition for module ");
    print_any(_oid_(v45520));
    princ_string(", ");
    princ_string(date_I_integer(1));
    princ_string("#ifndef CLAIREH_");
    ident_thing(v45520);
    princ_string("\n#define CLAIREH_");
    ident_thing(v45520);
    princ_string("\n");
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52340);
      bag *v52340_support;
      v52340_support = GC_OBJECT(list,Optimize.compiler->headers);
      for (START(v52340_support); NEXT(v52340);)
      if (match_wildcard_ask_string(string_v(v52340),"*.*") == CTRUE)
       { princ_string("#include ");
        if (equal_string(left_string(string_v(v52340),1),"<") == CTRUE)
         princ_string(string_v(v52340));
        else print_any(v52340);
          princ_string("\n");
        }
      else { princ_string("#include \"");
          princ_string(string_v(v52340));
          princ_string(".h\"\n");
          }
        }
    use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value));
    }
  GC_UNBIND; POP_SIGNAL;}

void  end_module_interface_c_producer(Generate_c_producer *v52319,module *v45520)
{ princ_string("\n#endif\n");
  POP_SIGNAL;}

void  generate_end_file_c_producer(Generate_c_producer *v52326,module *v52329)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  close_block_void();
  putc_char1(_char_("\n"[1 - 1]),GC_OBJECT(PortObject,Optimize.OPT->outfile));
  (*Core.fclose)(GC_OID(_oid_(Optimize.OPT->outfile)));
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52319);
    bag *v52319_support;
    v52319_support = GC_OBJECT(list,Optimize.OPT->objects);
    for (START(v52319_support); NEXT(v52319);)
    { GC_LOOP;
      if (INHERIT(OWNER(v52319),Kernel._class))
       { buffer * v52332 = GC_OBJECT(buffer,fopen_string1(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),GC_STRING(c_string_c_producer2(v52326,OBJECT(symbol,(*Kernel.name)(v52319)))))),GC_STRING(v52326->extension))),"a"));
        use_as_output_port(v52332);
        close_block_void();
        putc_char1(_char_("\n"[1 - 1]),v52332);
        fclose_filter1(v52332);
        }
      GC_UNLOOP; POP_SIGNAL;}
    }
  GC_UNBIND; POP_SIGNAL;}

void  generate_classes_c_producer(Generate_c_producer *v52326,char *v52335,module *v52329)
{ princ_string("\n\n");
  ident_c_producer(v52326,v52329->name);
  princ_string("Class ");
  ident_c_producer(v52326,v52329->name);
  princ_string(";\n\n");
  { module * v49384 = v52329;
    module * v49385 = v49384->part_of;
    { CL_INT loop_handle = ClEnv->cHandle;
      while (((boolean_I_any(_oid_(v49385->made_of)) != CTRUE) && 
          ((v49385 != claire.it) && 
            ((*(v49385->parts))[1] == _oid_(v49384)))))
      { princ_string("NameSpace ");
        (*Language.ident)(Generate.PRODUCER->value,
          _oid_(v49385->name));
        princ_string(";\n");
        v49385= v49385->part_of;
        v49384= v49385;
        POP_SIGNAL;}
      }
    }
  POP_SIGNAL;}

void  generate_start_file_c_producer(Generate_c_producer *v52319,module *v52329)
{ GC_BIND;
  if (should_trace_ask_module1(Generate.it,2) == CTRUE)
   mtformat_module1(Generate.it,"++++ Creating the file ~A.cpp \n",2,list::alloc(1,GC_OID(_string_(c_string_c_producer2(v52319,v52329->name)))));
  else ;start_file_string(string_I_symbol(v52329->name),v52329);
  (Optimize.OPT->level = 0);
  princ_string("/* class file for module ");
  print_any(_oid_(v52329));
  princ_string(" */");
  breakline_void();
  breakline_void();
  princ_string("public class ");
  ident_c_producer(v52319,v52329->name);
  princ_string(" extends NameSpace");
  new_block_void();
  GC_UNBIND; POP_SIGNAL;}

void  generate_meta_load_c_producer(Generate_c_producer *v52319,module *v52329)
{ princ_string("void ");
  ident_c_producer(v52319,v52329->name);
  princ_string("Class::metaLoad() ");
  new_block_void();
  breakline_void();
  { breakline_void();
    princ_string("ClEnv->module_I = it;\n");
    }
  POP_SIGNAL;}

OID  start_file_string(char *v52335,module *v52329)
{ GC_BIND;
  use_as_output_port(Optimize.OPT->outfile);
  princ_string("/***** CLAIRE Compilation of file ");
  princ_string(v52335);
  princ_string(".cl \n         [version ");
  (*Kernel.princ)(GC_OID(release_void()));
  princ_string(" / safety ");
  print_any(((OID)Optimize.compiler->safety));
  princ_string("] ");
  princ_string(substring_string(GC_STRING(date_I_integer(1)),1,24));
  princ_string(" *****/\n\n");
  princ_string("#include <claire.h>\n");
  princ_string("#include <Kernel.h>\n");
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52340);
    bag *v52340_support;
    v52340_support = GC_OBJECT(list,add_modules_list(list::alloc(1,_oid_(v52329))));
    for (START(v52340_support); NEXT(v52340);)
    { GC_LOOP;
      { { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v52339);
          bag *v52339_support;
          v52339_support = GC_OBJECT(list,OBJECT(module,v52340)->uses);
          for (START(v52339_support); NEXT(v52339);)
          if (Kernel._string == OWNER(v52339))
           { princ_string("#include <");
            (*Kernel.princ)(v52339);
            princ_string(".h>\n");
            }
          }
        if (OBJECT(module,v52340)->made_of->length != 0)
         { princ_string("#include <");
          ident_symbol(OBJECT(symbol,(*Kernel.name)(v52340)));
          princ_string(".h>\n");
          }
        }
      GC_UNLOOP; POP_SIGNAL;}
    }
  if (boolean_I_any(Optimize.OPT->cfile) == CTRUE)
   { princ_string("#include <");
    (*Kernel.princ)(GC_OID(Optimize.OPT->cfile));
    princ_string(".h>\n");
    }
  { OID Result = 0;
    Result = _oid_(use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value)));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  define_variable_c_producer2(Generate_c_producer *v52319,ClaireClass *v52336,char *v52338)
{ interface_I_class(v52336);
  princ_string(v52338);
  princ_string(" ");
  if ((v52336 == Kernel._integer) || 
      (v52336 == Kernel._any))
   princ_string("= 0");
  else if (v52336 == Kernel._float)
   princ_string("=0.0");
  princ_string(";");
  POP_SIGNAL;}

void  generate_profile_c_producer(Generate_c_producer *v52319,OID v52329)
{ if (Kernel._method == OWNER(v52329))
   get_dependents_method(OBJECT(method,v52329));
  { princ_string("   PRcount *PR_x = PRstart(PRget_property(");
    expression_thing(((Kernel._method == OWNER(v52329)) ?
      OBJECT(restriction,v52329)->selector :
      Kernel.fastcall ),Core.nil->value);
    princ_string("));");
    breakline_void();
    }
  POP_SIGNAL;}

void  generate_interface_c_producer(Generate_c_producer *v52319,module *v45520)
{ GC_RESERVE(8);  // v3.0.55 optim !
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52340);
    bag *v52340_support;
    v52340_support = GC_OBJECT(list,Optimize.OPT->objects);
    for (START(v52340_support); NEXT(v52340);)
    if (INHERIT(OWNER(v52340),Kernel._class))
     { princ_string("\nclass ");
      class_princ_c_producer(v52319,OBJECT(ClaireClass,v52340));
      princ_string(";");
      }
    }
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52340);
    bag *v52340_support;
    v52340_support = GC_OBJECT(list,Optimize.OPT->objects);
    for (START(v52340_support); NEXT(v52340);)
    { GC_LOOP;
      if (INHERIT(OWNER(v52340),Kernel._class))
       { princ_string("\n\nclass ");
        class_princ_c_producer(v52319,OBJECT(ClaireClass,v52340));
        princ_string(": public ");
        class_princ_c_producer(v52319,OBJECT(ClaireClass,v52340)->superclass);
        new_block_void();
        breakline_void();
        princ_string("public:");
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v52341);
          bag *v52341_support;
          v52341_support = GC_OBJECT(list,OBJECT(bag,(*Optimize.get_indexed)(v52340)));
          for (START(v52341_support); NEXT(v52341);)
          { ClaireBoolean * g1861I;
            { OID  v63398;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(v49571);
                v63398= Kernel.cfalse;
                for (START(OBJECT(ClaireClass,v52340)->superclass->slots); NEXT(v49571);)
                if (_I_equal_any(_oid_(OBJECT(restriction,v49571)->selector),_oid_(OBJECT(restriction,v52341)->selector)) != CTRUE)
                 { v63398 = Kernel.ctrue;
                  ClEnv->cHandle = loop_handle;break;}
                }
              g1861I = not_any(v63398);
              }
            
            if (g1861I == CTRUE) { breakline_void();
                princ_string("   ");
                (*Generate.interface_I)(Generate.PRODUCER->value,
                  _oid_(psort_any(_oid_(OBJECT(restriction,v52341)->range))));
                ident_symbol(OBJECT(restriction,v52341)->selector->name);
                princ_string(";");
                }
              }
          }
        (*Generate.methods_interface)(Generate.PRODUCER->value,
          v52340);
        close_block_void();
        princ_string(";");
        }
      GC_UNLOOP; POP_SIGNAL;}
    }
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52331);
    bag *v52331_support;
    v52331_support = GC_OBJECT(list,Optimize.OPT->functions);
    for (START(v52331_support); NEXT(v52331);)
    { GC_LOOP;
      { OID  v47205 = GC_OID((*Kernel.nth)(v52331,
          ((OID)1)));
        OID  v61902 = GC_OID((*Kernel.nth)(v52331,
          ((OID)2)));
        OID  v52335 = GC_OID((*Kernel.nth)(v52331,
          ((OID)3)));
        princ_string("\nextern ");
        (*Generate.interface_I)(Generate.PRODUCER->value,
          v52335);
        princ_string(" ");
        (*Kernel.c_princ)(v47205);
        princ_string("(");
        typed_args_list_list(OBJECT(list,v61902));
        princ_string(");");
        }
      GC_UNLOOP; POP_SIGNAL;}
    }
  GC_UNBIND; POP_SIGNAL;}

void  global_var_def_I_c_producer(Generate_c_producer *v52319,module *v45520,Let *v52340)
{ GC_BIND;
  { global_variable * v27905 = OBJECT(global_variable,get_symbol(OBJECT(symbol,(*(OBJECT(bag,(*Core.args)(GC_OID(v52340->value)))))[1])));
    ClaireClass * v52335 = getRange_global_variable(v27905);
    OID  v43050 = GC_OID((*(OBJECT(Do,v52340->arg)->args))[2]);
    OID  v3877;
    { if (INHERIT(OWNER(v43050),Language._Update))
       v3877 = OBJECT(Update,v43050)->value;
      else if ((INHERIT(OWNER(v43050),Language._Call)) || 
          (INHERIT(OWNER(v43050),Language._Call_method)))
       v3877 = (*(OBJECT(bag,(*Core.args)(v43050))))[5];
      else { OID  v5914;close_exception(((general_error *) (*Core._general_error)(_string_("Design bug: make ~S a public global var !"),
            _oid_(list::alloc(1,_oid_(v27905))))));
          
          v3877=_void_(v5914);}
        GC_OID(v3877);}
    ClaireBoolean * v52318 = c_func_any(v3877);
    Variable * v164 = GC_OBJECT(Variable,build_Variable_string("V_C",_oid_(Kernel._any)));
    if (nativeVar_ask_global_variable(v27905) != CTRUE)
     statement_any(_oid_(v52340),Core.nil->value,Core.nil->value);
    else { if (v52318 != CTRUE)
         { new_block_void();
          princ_string("OID ");
          ident_c_producer3(v52319,v164);
          princ_string(";");
          breakline_void();
          statement_any(v3877,GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
            _oid_(v164))),Core.nil->value);
          }
        ident_c_producer(v52319,v45520->name);
        princ_string(".");
        ident_c_producer(v52319,v27905->name);
        princ_string(" = ");
        if (v52318 == CTRUE)
         to_c_c_producer1(v52319,v3877,v52335,Core.nil->value);
        else to_c_c_producer1(v52319,_oid_(v164),v52335,Core.nil->value);
          princ_string(";");
        if (v52318 != CTRUE)
         close_block_void();
        breakline_void();
        }
      }
  GC_UNBIND; POP_SIGNAL;}

void  gc_introduction_c_producer(Generate_c_producer *v52319,OID v47201)
{ GC_BIND;
  if (Optimize.OPT->protection == CTRUE)
   { OID  v52343 = GC_OID(gc_usage_any(v47201,CFALSE));
    if (should_trace_ask_module1(Generate.it,3) == CTRUE)
     mtformat_module1(Generate.it,"gc_introduction(~S) => ~S, loop_gc = ~S \n",3,list::alloc(3,v47201,
      v52343,
      _oid_(Optimize.OPT->loop_gc)));
    else ;if ((Optimize.OPT->loop_gc == CTRUE) && 
        (INHERIT(OWNER(v52343),Kernel._integer)))
     { if ((OBJECT(ClaireBoolean,(*Kernel._inf)(v52343,
        ((OID)100)))) == CTRUE)
       { (Optimize.OPT->loop_index = 0);
        princ_string("GC_RESERVE(1);  // HOHO v3.0.55 optim !");
        }
      else { princ_string("GC_RESERVE(");
          princ_integer(((CL_INT)Optimize.OPT->loop_index+(CL_INT)1));
          princ_string(");  // v3.0.55 optim !");
          }
        }
    else princ_string("GC_BIND;");
      breakline_void();
    }
  GC_UNBIND; POP_SIGNAL;}

OID  gc_usage_any(OID v45520,ClaireBoolean *v43304)
{ GC_BIND;
  { OID Result = 0;
    if (INHERIT(OWNER(v45520),Language._Instruction))
     { if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Construct))
       Result = gc_usage_star_list(GC_OBJECT(list,OBJECT(Construct,v45520)->args),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Definition))
       Result = Kernel.ctrue;
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Call_method))
       Result = gc_usage_star_list(GC_OBJECT(list,OBJECT(Call_method,v45520)->args),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Call_slot))
       Result = gc_usage_any(GC_OID(OBJECT(Call_slot,v45520)->arg),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Call_table))
       Result = gc_usage_any(GC_OID(OBJECT(Call_table,v45520)->arg),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Call_array))
       Result = gc_usage_any(GC_OID(OBJECT(Call_array,v45520)->arg),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Optimize._to_C))
       Result = gc_usage_any(GC_OID(OBJECT(Compile_to_C,v45520)->arg),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Optimize._to_CL))
       Result = gc_usage_any(GC_OID(OBJECT(Compile_to_CL,v45520)->arg),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Optimize._to_protect))
       Result = Kernel.ctrue;
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Update))
       Result = gc_usage_any(GC_OID(OBJECT(Update,v45520)->value),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Call))
       Result = gc_usage_star_list(GC_OBJECT(list,OBJECT(Call,v45520)->args),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._If))
       Result = gc_or_any(gc_usage_any(GC_OID(OBJECT(If,v45520)->test),v43304),gc_or_any(GC_OID(gc_usage_any(GC_OID(OBJECT(If,v45520)->arg),v43304)),GC_OID(gc_usage_any(GC_OID(OBJECT(If,v45520)->other),v43304))));
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Do))
       Result = gc_usage_star_list(GC_OBJECT(list,OBJECT(Do,v45520)->args),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Iteration))
       Result = gc_or_any(GC_OID(gc_usage_any(GC_OID(OBJECT(Iteration,v45520)->set_arg),v43304)),GC_OID(gc_usage_any(GC_OID(OBJECT(Iteration,v45520)->arg),CTRUE)));
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Ffor))
       Result = gc_or_any(gc_or_any(GC_OID(gc_usage_any(GC_OID(OBJECT(iClaire_Ffor,v45520)->set_arg),v43304)),GC_OID(gc_usage_any(GC_OID(OBJECT(iClaire_Ffor,v45520)->arg),v43304))),gc_usage_any(GC_OID(OBJECT(iClaire_Ffor,v45520)->forkedby),v43304));
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Let))
       { OID  v52340 = GC_OID(OBJECT(Let,v45520)->value);
        { OID  v65320;
          if ((v43304 == CTRUE) && 
              (INHERIT(OWNER(v52340),Optimize._to_protect)))
           v65320 = ((OID)OBJECT(Instruction_with_var,v45520)->var->index);
          else v65320 = Kernel.cfalse;
            Result = gc_or_any(v65320,gc_or_any(GC_OID(gc_usage_any(v52340,v43304)),GC_OID(gc_usage_any(GC_OID(OBJECT(Let,v45520)->arg),v43304))));
          }
        }
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Assign))
       { OID  v52340 = GC_OID(OBJECT(Assign,v45520)->arg);
        { OID  v745;
          { if ((v43304 == CTRUE) && 
                (inner2outer_ask_any(v52340) == CTRUE))
             v745 = (*Kernel.index)(GC_OID(OBJECT(Assign,v45520)->var));
            else v745 = Kernel.cfalse;
              GC_OID(v745);}
          Result = gc_or_any(v745,GC_OID(gc_usage_any(v52340,v43304)));
          }
        }
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Gassign))
       Result = gc_usage_any(GC_OID(OBJECT(Gassign,v45520)->arg),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._And))
       Result = gc_usage_star_list(GC_OBJECT(list,OBJECT(And,v45520)->args),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Or))
       Result = gc_usage_star_list(GC_OBJECT(list,OBJECT(Or,v45520)->args),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Cast))
       Result = gc_usage_any(GC_OID(OBJECT(Cast,v45520)->arg),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Super))
       Result = gc_usage_star_list(GC_OBJECT(list,OBJECT(Super,v45520)->args),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Case))
       Result = gc_usage_star_list(GC_OBJECT(list,OBJECT(Case,v45520)->args),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._While))
       Result = gc_or_any(GC_OID(gc_usage_any(GC_OID(OBJECT(While,v45520)->arg),CTRUE)),GC_OID(gc_usage_any(GC_OID(OBJECT(While,v45520)->test),v43304)));
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Return))
       Result = gc_usage_any(GC_OID(OBJECT(Return,v45520)->arg),v43304);
      else if (INHERIT(OBJECT(ClaireObject,v45520)->isa,Language._Handle))
       Result = gc_or_any(gc_or_any(GC_OID(gc_usage_any(GC_OID(OBJECT(ClaireHandle,v45520)->arg),v43304)),GC_OID(gc_usage_any(GC_OID(OBJECT(ClaireHandle,v45520)->other),v43304))),gc_usage_any(GC_OID(OBJECT(ClaireHandle,v45520)->test),v43304));
      else Result = Kernel.cfalse;
        }
    else Result = Kernel.cfalse;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  gc_or_any(OID v52340,OID v52341)
{ { OID Result = 0;
    if (v52340 == Kernel.cfalse)
     Result = v52341;
    else if (v52340 == Kernel.ctrue)
     { if (v52341 == Kernel.cfalse)
       Result = v52340;
      else Result = v52341;
        }
    else if (INHERIT(OWNER(v52341),Kernel._integer))
     { if (equal(v52340,v52341) == CTRUE)
       Result = v52341;
      else Result = ((OID)1000);
        }
    else Result = v52340;
      POP_SIGNAL; return (Result);}
  }

OID  gc_usage_star_list(list *v52331,ClaireBoolean *v43304)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { OID Result = 0;
    { OID  v52340 = Kernel.cfalse;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v52341);
        for (START(v52331); NEXT(v52341);)
        { GC_LOOP;
          GC__OID(v52340 = gc_or_any(v52340,gc_usage_any(v52341,v43304)), 1);
          GC_UNLOOP; POP_SIGNAL;}
        }
      Result = v52340;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  debug_intro_c_producer(Generate_c_producer *v52319,lambda *v45520,method *v52340)
{ GC_BIND;
  { module * v52329;
    { ClaireObject *V_CC ;
      if (Kernel._method == v52340->isa)
       V_CC = v52340->module_I;
      else V_CC = CFALSE;
        v52329= (module *) V_CC;}
    CL_INT  v52333 = 1;
    princ_string("DB_METHOD");
    if (boolean_I_any(_oid_(v52340->location)) != CTRUE)
     princ_string("0");
    princ_string("(");
    ident_thing(v52329);
    if (v52340->location->length != 0)
     { princ_string(",DB");
      princ_string(CL_Oid(_oid_(v52340)));
      }
    princ_string(")");
    breakline_void();
    if ((v45520->vars->length == 1) && 
        ((*Kernel.range)(GC_OID((*(v45520->vars))[1])) == _oid_(Kernel._void)))
     princ_string("PUSH(_oid_(ClEnv)); ");
    else { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v52338);
        bag *v52338_support;
        v52338_support = GC_OBJECT(list,v45520->vars);
        for (START(v52338_support); NEXT(v52338);)
        { princ_string("PUSH(");
          { OID  v52335 = (*(v52340->srange))[v52333];
            if (((v52335 == _oid_(Kernel._any)) && 
                  ((*Kernel.range)(v52338) != _oid_(Kernel._float))) || 
                (v52335 == _oid_(Kernel._integer)))
             (*Generate.expression)(v52338,
              Kernel.cfalse);
            else to_cl_c_producer(v52319,v52338,(((*Kernel.range)(v52338) == _oid_(Kernel._float)) ?
                Kernel._float :
                OBJECT(ClaireClass,v52335) ),Kernel.cfalse);
              }
          princ_string(");");
          ++v52333;
          }
        }
      { list * v49154 = GC_OBJECT(list,debug_build_lambda1(v45520));
      ClaireBoolean * v49181 = CTRUE;
      (Optimize._stardebug_build_star->value= _oid_(v49154));
      { CL_INT  v52325 = ((CL_INT)v45520->vars->length+(CL_INT)1);
        CL_INT  v30346 = v49154->length;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)v52325 <= (CL_INT)v30346))
          { if (v49181 == CTRUE)
             { breakline_void();
              v49181= CFALSE;
              }
            princ_string("DB_VAR(");
            print_any(((OID)v52325));
            princ_string(")");
            ++v52325;
            POP_SIGNAL;}
          }
        }
      }
    breakline_void();
    princ_string("DB_BIND(");
    expression_thing(v52340->selector,_oid_(Kernel.emptySet));
    princ_string(",");
    princ_integer(v45520->vars->length);
    princ_string(",");
    princ_integer(((CL_INT)OBJECT(bag,Optimize._stardebug_build_star->value)->length-(CL_INT)v45520->vars->length));
    princ_string(");");
    breakline_void();
    }
  GC_UNBIND; POP_SIGNAL;}

char * protect_result_c_producer(Generate_c_producer *v52319,ClaireClass *v52335,ClaireBoolean *v15384,OID v52340)
{ GC_BIND;
  if ((CL_INT)Optimize.compiler->safety > 5)
   { (Optimize.OPT->protection = CFALSE);
    v15384= CFALSE;
    (Optimize.OPT->loop_gc = CFALSE);
    }
  { char *Result ;
    { char * v49570 = ((v52335 != Kernel._void) ?
        ((Optimize.OPT->alloc_stack != CTRUE) ?
          ((v15384 == CTRUE) ?
            "GC_UNBIND; POP_SIGNAL; return " :
            "POP_SIGNAL; return " ) :
          ((v15384 == CTRUE) ?
            "GC_UNBIND; return " :
            "return " ) ) :
        ((v15384 == CTRUE) ?
          "GC_UNBIND; POP_SIGNAL;" :
          "POP_SIGNAL;" ) );
      ClaireObject * v52329;
      if (need_debug_ask_any(v52340) == CTRUE)
       v52329 = OBJECT(method,v52340)->module_I;
      else v52329 = CFALSE;
        if (INHERIT(v52329->isa,Kernel._module))
       { print_in_string_void();
        princ_string("DB_UNBIND(");
        (*Generate.expression)(GC_OID((*Kernel.selector)(v52340)),
          _oid_(Kernel.emptySet));
        princ_string(",");
        if (v52335 == Kernel._void)
         princ_string("CNULL");
        else if ((v52335 == Kernel._any) || 
            (v52335 == Kernel._integer))
         princ_string("Result");
        else to_cl_c_producer(v52319,GC_OID(_oid_(build_Variable_string("Result",_oid_(v52335)))),v52335,Core.nil->value);
          princ_string(");");
        breakline_void();
        princ_string("  ");
        princ_string(v49570);
        Result = end_of_string_void();
        }
      else Result = (((Optimize.OPT->profile_ask == CTRUE) && 
          ((Kernel._method == OWNER(v52340)) || 
              (v52340 == CNULL))) ?
        append_string("PRend(PR_x);",v49570) :
        v49570 );
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  generate_function_start_c_producer(Generate_c_producer *v52319,lambda *v45520,ClaireClass *v52335,OID v52329,char *v24332)
{ GC_BIND;
  { OID  v14721;
    { if (v45520->vars->length != 0)
       v14721 = (*Kernel.range)(GC_OID((*(v45520->vars))[1]));
      else v14721 = _oid_(Kernel._any);
        GC_OID(v14721);}
    ClaireFunction * v47205 = make_function_string(v24332);
    list * v49422 = GC_OBJECT(list,(((v45520->vars->length == 1) && 
        ((v14721 == _oid_(Kernel._environment)) || 
            (v14721 == _oid_(Kernel._void)))) ?
      Kernel.nil :
      v45520->vars ));
    update_function_entry_c_producer(v52319,v47205,v49422,v52335);
    use_as_output_port(Optimize.OPT->outfile);
    if (Kernel._method == OWNER(v52329))
     { if ((OBJECT(restriction,v52329)->range == Kernel._float) || 
          (OBJECT(restriction,v52329)->domain->memq(_oid_(Kernel._float)) == CTRUE))
       generate_float_function_c_producer(v52319,OBJECT(method,v52329),string_I_function(v47205));
      else if (INHERIT(OBJECT(restriction,v52329)->range->isa,Kernel._tuple))
       generate_tuple_function_c_producer(v52319,OBJECT(method,v52329),string_I_function(v47205));
      }
    generate_regular_function_c_producer(v52319,
      v45520,
      v47205,
      v52335,
      v52329,
      v49422);
    }
  GC_UNBIND; POP_SIGNAL;}

void  generate_regular_function_c_producer(Generate_c_producer *v52319,lambda *v45520,ClaireFunction *v47205,ClaireClass *v52335,OID v52329,list *v49422)
{ GC_BIND;
  if (Optimize.compiler->naming != 2)
   { princ_string("\n// The c++ function for: ");
    if (Kernel._method == OWNER(v52329))
     { print_any(_oid_(OBJECT(restriction,v52329)->selector));
      princ_string("(");
      ppvariable_list(GC_OBJECT(list,v45520->vars));
      princ_string(") [");
      if (Optimize.compiler->naming == 1)
       bitvectorSum_integer(status_I_restriction(OBJECT(restriction,v52329)));
      princ_string("]");
      }
    else princ_string(string_I_function(v47205));
      princ_string("\n");
    }
  { interface_I_c_producer(v52319,v52335);
    princ_string(" ");
    c_princ_function(v47205);
    princ_string("(");
    typed_args_list_list(v49422);
    princ_string(")\n");
    }
  GC_UNBIND; POP_SIGNAL;}

void  generate_float_function_c_producer(Generate_c_producer *v52319,method *v52329,char *v24332)
{ GC_BIND;
  { list * v49404 = (((v52329->domain->length == 1) && 
        (domain_I_restriction(v52329) == Kernel._void)) ?
      Kernel.nil :
      v52329->domain );
    CL_INT  v52333 = v49404->length;
    list * v49422;
    { { CL_INT loop_handle = ClEnv->cHandle;
        bag *v_list; OID v_val;
        OID v52340; CL_INT CLcount;
        v_list = v49404;
         v49422 = v_list->clone();
        for (CLcount= 1; CLcount <= v_list->length; CLcount++)
        { v52340 = (*(v_list))[CLcount];
          { Variable * v47292 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
            (v47292->pname = gensym_void());
            { Variable * v30349 = v47292; 
              ClaireType * v30371;
              if (v52340 == _oid_(Kernel._float))
               v30371 = Kernel._any;
              else v30371 = OBJECT(ClaireType,v52340);
                (v30349->range = v30371);}
            add_I_property(Kernel.instances,Language._Variable,11,_oid_(v47292));
            v_val = _oid_(v47292);
            }
          
          (*((list *) v49422))[CLcount] = v_val;}
        }
      GC_OBJECT(list,v49422);}
    char * v33460 = GC_STRING(append_string(v24332,"_"));
    ClaireFunction * v47205 = make_function_string(v33460);
    lambda * v49960 = GC_OBJECT(lambda,lambda_I_list(v49422,Core.nil->value));
    ClaireClass * v52335 = ((v52329->range == Kernel._float) ?
      Kernel._any :
      psort_any(_oid_(v52329->range)) );
    generate_regular_function_c_producer(v52319,
      v49960,
      v47205,
      v52335,
      _oid_(v52329),
      v49422);
    GC_OBJECT(list,Optimize.OPT->functions)->addFast((OID)_oid_(list::alloc(3,_oid_(v47205),
      _oid_(v49422),
      _oid_(v52335))));
    new_block_void();
    if (v52335 != Kernel._void)
     princ_string("return ");
    if (v52329->range == Kernel._float)
     princ_string("_float_(");
    c_princ_function(OBJECT(ClaireFunction,(*Optimize.functional_I)(_oid_(v52329))));
    princ_string("(");
    { CL_INT  v52325 = 1;
      CL_INT  v30348 = v52333;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)v52325 <= (CL_INT)v30348))
        { if (v52325 != 1)
           princ_string(",");
          if ((*(v52329->domain))[v52325] == _oid_(Kernel._float))
           { princ_string("float_v(");
            expression_Variable(OBJECT(Variable,(*(v49422))[v52325]),Core.nil->value);
            princ_string(")");
            }
          else expression_Variable(OBJECT(Variable,(*(v49422))[v52325]),Core.nil->value);
            ++v52325;
          POP_SIGNAL;}
        }
      }
    princ_string(")");
    if (v52329->range == Kernel._float)
     princ_string(")");
    princ_string(";");
    close_block_void();
    princ_string("\n");
    }
  GC_UNBIND; POP_SIGNAL;}

void  at_c_producer(Generate_c_producer *v52319)
{ princ_string("->");
  POP_SIGNAL;}

void  generate_tuple_function_c_producer(Generate_c_producer *v52319,method *v52329,char *v24332)
{ GC_BIND;
  { list * v49404 = (((v52329->domain->length == 1) && 
        (domain_I_restriction(v52329) == Kernel._void)) ?
      Kernel.nil :
      v52329->domain );
    CL_INT  v52333 = v49404->length;
    list * v49422;
    { { CL_INT loop_handle = ClEnv->cHandle;
        bag *v_list; OID v_val;
        OID v52340; CL_INT CLcount;
        v_list = v49404;
         v49422 = v_list->clone();
        for (CLcount= 1; CLcount <= v_list->length; CLcount++)
        { v52340 = (*(v_list))[CLcount];
          { Variable * v47292 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
            (v47292->pname = gensym_void());
            (v47292->range = OBJECT(ClaireType,v52340));
            add_I_property(Kernel.instances,Language._Variable,11,_oid_(v47292));
            v_val = _oid_(v47292);
            }
          
          (*((list *) v49422))[CLcount] = v_val;}
        }
      GC_OBJECT(list,v49422);}
    char * v33460 = GC_STRING(append_string(v24332,"_"));
    ClaireFunction * v47205 = make_function_string(v33460);
    lambda * v49960 = GC_OBJECT(lambda,lambda_I_list(v49422,Core.nil->value));
    ClaireClass * v52335 = Kernel._tuple;
    generate_regular_function_c_producer(v52319,
      v49960,
      v47205,
      v52335,
      _oid_(v52329),
      v49422);
    GC_OBJECT(list,Optimize.OPT->functions)->addFast((OID)_oid_(list::alloc(3,_oid_(v47205),
      _oid_(v49422),
      _oid_(v52335))));
    new_block_void();
    if (v52335 != Kernel._void)
     princ_string("return ");
    c_princ_function(OBJECT(ClaireFunction,(*Optimize.functional_I)(_oid_(v52329))));
    princ_string("(");
    { CL_INT  v52325 = 1;
      CL_INT  v30373 = v52333;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)v52325 <= (CL_INT)v30373))
        { if (v52325 != 1)
           princ_string(",");
          expression_Variable(OBJECT(Variable,(*(v49422))[v52325]),Core.nil->value);
          ++v52325;
          POP_SIGNAL;}
        }
      }
    princ_string(")");
    princ_string("->copyIfNeeded()");
    princ_string(";");
    close_block_void();
    princ_string("\n");
    }
  GC_UNBIND; POP_SIGNAL;}

OID  create_function_entry_c_producer(Generate_c_producer *v52319,lambda *v49403,char *v47205,OID v52329)
{ POP_SIGNAL; return (Core.nil->value);}

OID  update_function_entry_c_producer(Generate_c_producer *v52319,ClaireFunction *v47205,list *v49422,ClaireClass *v52335)
{ GC_BIND;
  GC_OBJECT(list,Optimize.OPT->functions)->addFast((OID)_oid_(list::alloc(3,_oid_(v47205),
    _oid_(v49422),
    _oid_(v52335))));
  { OID Result = 0;
    Result = Kernel.cfalse;
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

char * c_interface_class1_Generate(ClaireClass *v45520)
{ { char *Result ;
    { CL_INT  v52333 = index_list(OBJECT(Generate_producer,Generate.PRODUCER->value)->interfaces,_oid_(v45520));
      Result = ((v52333 == 0) ?
        "OID *" :
        string_v((*(OBJECT(Generate_producer,Generate.PRODUCER->value)->interfaces))[((CL_INT)v52333+(CL_INT)1)]) );
      }
    POP_SIGNAL; return (Result);}
  }

void  c_interface_class2_Generate(ClaireClass *v45520,char *v52335)
{ GC_BIND;
  { CL_INT  v52333 = index_list(OBJECT(Generate_producer,Generate.PRODUCER->value)->interfaces,_oid_(v45520));
    if (v52333 == 0)
     (OBJECT(Generate_producer,Generate.PRODUCER->value)->interfaces = GC_OBJECT(list,GC_OBJECT(list,OBJECT(Generate_producer,Generate.PRODUCER->value)->interfaces)->addFast((OID)_oid_(v45520)))->addFast((OID)_string_(v52335)));
    else ((*(GC_OBJECT(list,OBJECT(Generate_producer,Generate.PRODUCER->value)->interfaces)))[((CL_INT)v52333+(CL_INT)1)]=_string_(v52335));
      }
  GC_UNBIND; POP_SIGNAL;}

void  c_interface_method_Generate(method *v45520)
{ c_princ_string(string_v((*Optimize.function_name)(_oid_(v45520->selector),
    _oid_(v45520->domain),
    _oid_(v45520->functional))));
  POP_SIGNAL;}

void  interface_I_c_producer(Generate_c_producer *v52319,ClaireClass *v45520)
{ if (v45520 == Kernel._void)
   princ_string("void ");
  else if (v45520 == Kernel._integer)
   princ_string("int ");
  else if ((v45520 == Kernel._function) || 
      ((v45520 == Kernel._char) || 
        (v45520 == Kernel._boolean)))
   { ident_c_producer(v52319,v45520->name);
    princ_string(" *");
    }
  else if ((INHERIT(v45520,Kernel._cl_import)) || 
      ((v45520 == Kernel._string) || 
        (v45520 == Kernel._array)))
   princ_string(string_v((*Optimize.c_interface)(_oid_(v45520))));
  else if (INHERIT(v45520,Kernel._object))
   { class_princ_c_producer(v52319,v45520);
    princ_string(" *");
    }
  else if (INHERIT(v45520,Kernel._bag))
   { ident_c_producer(v52319,v45520->name);
    princ_string(" *");
    }
  else if (v45520 == Kernel._float)
   princ_string("double ");
  else princ_string("OID ");
    POP_SIGNAL;}

void  to_cl_c_producer(Generate_c_producer *v52319,OID v52340,ClaireClass *v52335,OID v43304)
{ if (v52335 == Kernel._void)
   { princ_string("_void_(");
    (*Generate.expression)(v52340,
      v43304);
    princ_string(")");
    }
  else if (INHERIT(v52335,Kernel._object))
   { if (v52340 == Kernel.ctrue)
     princ_string("Kernel.ctrue");
    else if (v52340 == Kernel.cfalse)
     princ_string("Kernel.cfalse");
    else { princ_string("_oid_(");
        (*Generate.expression)(v52340,
          v43304);
        princ_string(")");
        }
      }
  else if (v52335 == Kernel._integer)
   { if ((CL_INT)Optimize.compiler->safety > 1)
     { princ_string("((OID)");
      (*Generate.expression)(v52340,
        v43304);
      princ_string(")");
      }
    else { princ_string("_integer_(");
        (*Generate.expression)(v52340,
          v43304);
        princ_string(")");
        }
      }
  else if (v52335 == Kernel._char)
   { princ_string("_oid_(");
    (*Generate.expression)(v52340,
      v43304);
    princ_string(")");
    }
  else if (v52335 == Kernel._string)
   { princ_string("_string_(");
    (*Generate.expression)(v52340,
      v43304);
    princ_string(")");
    }
  else if (v52335 == Kernel._array)
   { princ_string("_array_(");
    (*Generate.expression)(v52340,
      v43304);
    princ_string(")");
    }
  else if (v52335 == Kernel._float)
   { princ_string("_float_(");
    (*Generate.expression)(v52340,
      v43304);
    princ_string(")");
    }
  else if (INHERIT(v52335,Kernel._cl_import))
   { princ_string("ClAlloc->import(");
    expression_any(_oid_(v52335),_oid_(Kernel.emptySet));
    princ_string(",(OID *) ");
    (*Generate.expression)(v52340,
      v43304);
    princ_string(")");
    }
  else if (v52335 == Kernel._any)
   (*Generate.expression)(v52340,
    v43304);
  else close_exception(((general_error *) (*Core._general_error)(_string_("[internal] to_cl for a ~S is not implemented"),
      _oid_(list::alloc(1,_oid_(v52335))))));
    POP_SIGNAL;}

void  to_c_c_producer1(Generate_c_producer *v52319,OID v52340,ClaireClass *v52335,OID v43304)
{ GC_BIND;
  if (v52335 == Kernel._integer)
   (*Generate.expression)(v52340,
    v43304);
  else if (v52340 == CNULL)
   { if (v52335 == Kernel._float)
     princ_string("0.0");
    else princ_string("NULL");
      }
  else if ((INHERIT(OWNER(v52340),Core._global_variable)) && 
      ((equal((*Kernel.range)(v52340),_oid_(Kernel.emptySet)) == CTRUE) && 
        (equal((*Kernel.value)(v52340),Core.nil->value) == CTRUE)))
   princ_string("Kernel.nil");
  else if ((INHERIT(v52335,Kernel._cl_import)) && 
      ((INHERIT(OWNER(v52340),Optimize._to_protect)) && 
        (INHERIT(owner_any(get_property(Kernel.arg,OBJECT(ClaireObject,v52340))),Optimize._to_CL))))
   (*Generate.expression)(GC_OID((*Kernel.arg)(GC_OID((*Kernel.arg)(v52340)))),
    v43304);
  else { to_c_c_producer2(v52319,v52335);
      (*Generate.expression)(v52340,
        v43304);
      princ_string(")");
      }
    GC_UNBIND; POP_SIGNAL;}

void  to_c_c_producer2(Generate_c_producer *v52319,ClaireClass *v52335)
{ if (INHERIT(v52335,Kernel._object))
   { princ_string("OBJECT(");
    class_princ_class(v52335);
    princ_string(",");
    }
  else if (v52335 == Kernel._float)
   princ_string("float_v(");
  else if (v52335 == Kernel._char)
   princ_string("char_v(");
  else if (v52335 == Kernel._string)
   princ_string("string_v(");
  else if (v52335 == Kernel._array)
   princ_string("array_v(");
  else if (INHERIT(v52335,Kernel._cl_import))
   { princ_string("EXPORT((");
    interface_I_class(v52335);
    princ_string("),");
    }
  else close_exception(((general_error *) (*Core._general_error)(_string_("[internal] to_c for a ~S is not implemented"),
      _oid_(list::alloc(1,_oid_(v52335))))));
    POP_SIGNAL;}

void  public_static_c_producer(Generate_c_producer *v52319)
{ ;POP_SIGNAL;}

void  bool_exp_I_c_producer(Generate_c_producer *v52319,OID v45520,OID v43304)
{ if (INHERIT(OWNER(v45520),Optimize._to_CL))
   { princ_string("(");
    (*Optimize.bool_exp)(v45520,
      Kernel.ctrue,
      v43304);
    princ_string(" ? Kernel.ctrue : Kernel.cfalse)");
    }
  else { princ_string("(");
      (*Optimize.bool_exp)(v45520,
        Kernel.ctrue,
        v43304);
      princ_string(" ? CTRUE : CFALSE)");
      }
    POP_SIGNAL;}

void  inherit_exp_c_producer(Generate_c_producer *v52319,OID v49012,OID v49013,OID v43304)
{ princ_string("INHERIT(");
  (*Generate.expression)(v49012,
    v43304);
  princ_string(",");
  (*Generate.expression)(v49013,
    v43304);
  princ_string(")");
  POP_SIGNAL;}

void  bitvector_exp_c_producer(Generate_c_producer *v52319,OID v49012,OID v49013,OID v43304)
{ princ_string("BCONTAIN(");
  (*Generate.expression)(v49012,
    v43304);
  princ_string(",");
  (*Generate.expression)(v49013,
    v43304);
  princ_string(")");
  POP_SIGNAL;}

void  equal_exp_c_producer(Generate_c_producer *v52319,OID v49012,ClaireBoolean *v31471,OID v49013,OID v21377)
{ GC_BIND;
  if ((INHERIT(OWNER(v49012),Optimize._to_CL)) && 
      ((INHERIT(OWNER(v49013),Optimize._to_CL)) && 
        ((osort_any(GC_OID((*Language.set_arg)(v49012))) == osort_any(GC_OID((*Language.set_arg)(v49013)))) && 
          ((identifiable_ask_any(GC_OID((*Kernel.arg)(v49012))) == CTRUE) || 
              ((identifiable_ask_any(GC_OID((*Kernel.arg)(v49013))) == CTRUE) || 
                (((*Language.set_arg)(v49012) == _oid_(Kernel._string)) || 
                  ((*Language.set_arg)(v49012) == _oid_(Kernel._float))))))))
   equal_exp_c_producer(v52319,
    GC_OID((*Kernel.arg)(v49012)),
    v31471,
    GC_OID((*Kernel.arg)(v49013)),
    Kernel.ctrue);
  else if ((INHERIT(OWNER(v49012),Optimize._to_protect)) && 
      ((INHERIT(owner_any((*Kernel.arg)(v49012)),Optimize._to_CL)) && 
        (((*Optimize.c_gc_ask)(GC_OID((*Kernel.arg)(GC_OID((*Kernel.arg)(v49012))))) != Kernel.ctrue) && 
          ((INHERIT(OWNER(v49013),Optimize._to_protect)) && 
            ((INHERIT(owner_any((*Kernel.arg)(v49013)),Optimize._to_CL)) && 
              ((*Optimize.c_gc_ask)(GC_OID((*Kernel.arg)(GC_OID((*Kernel.arg)(v49013))))) != Kernel.ctrue))))))
   equal_exp_c_producer(v52319,
    GC_OID((*Kernel.arg)(v49012)),
    v31471,
    GC_OID((*Kernel.arg)(v49013)),
    v21377);
  else { ClaireBoolean * g1874I;
    { ClaireBoolean *v_and;
      { v_and = (((*Optimize.c_sort)(v49012) == _oid_(Kernel._string)) ? CTRUE : CFALSE);
        if (v_and == CFALSE) g1874I =CFALSE; 
        else { v_and = (((*Optimize.c_sort)(v49013) == _oid_(Kernel._string)) ? CTRUE : CFALSE);
          if (v_and == CFALSE) g1874I =CFALSE; 
          else { { OID  v30536;
              if (INHERIT(OWNER(v49013),Optimize._to_C))
               v30536 = ((OBJECT(Compile_to_C,v49013)->arg == CNULL) ? Kernel.ctrue : Kernel.cfalse);
              else v30536 = Kernel.cfalse;
                v_and = not_any(v30536);
              }
            if (v_and == CFALSE) g1874I =CFALSE; 
            else g1874I = CTRUE;}
          }
        }
      }
    
    if (g1874I == CTRUE) { princ_string("(equal_string(");
        (*Generate.expression)(v49012,
          Core.nil->value);
        princ_string(",");
        (*Generate.expression)(v49013,
          Core.nil->value);
        princ_string(") ");
        sign_equal_boolean(v31471);
        princ_string(" CTRUE)");
        }
      else if ((INHERIT(OWNER(v49012),Optimize._to_CL)) && 
        (((*Language.set_arg)(v49012) != _oid_(Kernel._integer)) && 
          (v49013 == CNULL)))
     { princ_string("(");
      (*Generate.expression)(GC_OID((*Kernel.arg)(v49012)),
        Core.nil->value);
      princ_string(" ");
      sign_equal_boolean(v31471);
      princ_string(" ");
      if ((*Language.set_arg)(v49012) == _oid_(Kernel._float))
       princ_string("0.0");
      else princ_string("NULL");
        princ_string(")");
      }
    else if ((char_exp_ask_c_producer2(v52319,v49012) == CTRUE) || 
        (char_exp_ask_c_producer2(v52319,v49013) == CTRUE))
     { princ_string("(");
      char_exp_c_producer2(v52319,v49012,Core.nil->value);
      princ_string(" ");
      sign_equal_boolean(v31471);
      princ_string(" ");
      char_exp_c_producer2(v52319,v49013,Core.nil->value);
      princ_string(")");
      }
    else if ((boolean_I_any(v21377) == CTRUE) || 
        ((identifiable_ask_any(v49012) == CTRUE) || 
          ((identifiable_ask_any(v49013) == CTRUE) || 
            ((*Optimize.c_sort)(v49012) == _oid_(Kernel._float)))))
     { if (equal(_oid_(glb_class(stupid_t_any1(v49012),stupid_t_any1(v49013))),_oid_(Kernel.emptySet)) == CTRUE)
       { warn_void();
        if (should_trace_ask_module1(Generate.it,2) == CTRUE)
         mtformat_module1(Generate.it,"`BLUE ~S = ~S will fail ! [263]\n",2,list::alloc(2,v49012,v49013));
        else ;}
      princ_string("(");
      bexpression_any(v49012,Core.nil->value);
      princ_string(" ");
      sign_equal_boolean(v31471);
      princ_string(" ");
      bexpression_any(v49013,Core.nil->value);
      princ_string(")");
      }
    else { princ_string("(equal(");
        (*Generate.expression)(v49012,
          Core.nil->value);
        princ_string(",");
        (*Generate.expression)(v49013,
          Core.nil->value);
        princ_string(") ");
        sign_equal_boolean(v31471);
        princ_string(" CTRUE)");
        }
      }
  GC_UNBIND; POP_SIGNAL;}

ClaireBoolean * char_exp_ask_c_producer2(Generate_c_producer *v52319,OID v52340)
{ { ClaireBoolean *Result ;
    if (INHERIT(OWNER(v52340),Kernel._char))
     Result = CTRUE;
    else if (INHERIT(OWNER(v52340),Language._Call_method))
     { method * v52329 = OBJECT(Call_method,v52340)->arg;
      Result = ((_oid_(v52329) == Generate._starnth_1_string_star->value) ? CTRUE : (((_oid_(v52329) == Generate._starnth_string_star->value) && 
          (2 <= (CL_INT)Optimize.compiler->safety)) ? CTRUE : CFALSE));
      }
    else Result = CFALSE;
      POP_SIGNAL; return (Result);}
  }

void  char_exp_c_producer2(Generate_c_producer *v52319,OID v52340,OID v43304)
{ GC_BIND;
  if (INHERIT(OWNER(v52340),Kernel._char))
   { princ_string("((unsigned char)");
    print_any(((OID)OBJECT(ClaireChar,v52340)->ascii));
    princ_string(" /* ");
    print_any(v52340);
    princ_string(" */)");
    }
  else if (INHERIT(OWNER(v52340),Language._Call_method))
   { method * v52329 = OBJECT(Call_method,v52340)->arg;
    if ((_oid_(v52329) == Generate._starnth_1_string_star->value) || 
        (_oid_(v52329) == Generate._starnth_string_star->value))
     { OID  v49012 = GC_OID((*(OBJECT(Call_method,v52340)->args))[1]);
      OID  v49013 = GC_OID((*(OBJECT(Call_method,v52340)->args))[2]);
      (*Generate.expression)(v49012,
        v43304);
      princ_string("[");
      (*Generate.expression)(v49013,
        v43304);
      princ_string(" - 1]");
      }
    else { princ_string("((unsigned char) ");
        (*Generate.expression)(v52340,
          v43304);
        princ_string("->ascii)");
        }
      }
  else { princ_string("((unsigned char) ");
      (*Generate.expression)(v52340,
        v43304);
      princ_string("->ascii)");
      }
    GC_UNBIND; POP_SIGNAL;}

void  c_member_c_producer(Generate_c_producer *v52319,OID v45520,ClaireClass *v52335,property *v52340,OID v43304)
{ if (INHERIT(stupid_t_any1(v45520),v52335))
   { (*Generate.expression)(v45520,
      v43304);
    princ_string("->");
    ident_symbol(v52340->name);
    }
  else { princ_string("CLREAD(");
      class_princ_class(v52335);
      princ_string(",");
      (*Generate.expression)(v45520,
        v43304);
      princ_string(",");
      ident_symbol(v52340->name);
      princ_string(")");
      }
    POP_SIGNAL;}

void  addFast_c_producer(Generate_c_producer *v52319)
{ princ_string("->addFast");
  POP_SIGNAL;}

void  cast_I_c_producer(Generate_c_producer *v52319,Compile_C_cast *v45520,OID v43304)
{ GC_BIND;
  princ_string("((");
  class_princ_class(v45520->set_arg);
  princ_string(" *) ");
  (*Generate.expression)(v45520->arg,
    v43304);
  princ_string(")");
  GC_UNBIND; POP_SIGNAL;}

void  gc_protection_exp_c_producer(Generate_c_producer *v52319,Variable *v52338,ClaireBoolean *v40006,OID v52337,OID v43304)
{ GC_BIND;
  if ((osort_any(GC_OID(_oid_(v52338->range))) == Kernel._float) || 
      (osort_any(GC_OID(_oid_(v52338->range))) == Kernel._integer))
   { princ_string("(");
    ident_c_producer3(v52319,v52338);
    princ_string("=");
    if (v40006 == CTRUE)
     (*Generate.expression)(v52337,
      v43304);
    else c_princ_string(string_v(v52337));
      princ_string(")");
    }
  else { (v52319->stat = ((CL_INT)v52319->stat+(CL_INT)1));
      princ_string("GC__");
      princ_string(((osort_any(GC_OID(_oid_(v52338->range))) == Kernel._any) ?
        "OID" :
        ((osort_any(GC_OID(_oid_(v52338->range))) == Kernel._string) ?
          "STRING" :
          "ANY" ) ));
      princ_string("(");
      ident_c_producer3(v52319,v52338);
      if (v52337 != _oid_(v52338))
       { princ_string(" = ");
        if (v40006 == CTRUE)
         (*Generate.expression)(v52337,
          v43304);
        else c_princ_string(string_v(v52337));
          }
      princ_string(", ");
      princ_integer(((Optimize.OPT->loop_index == 0) ?
        1 :
        ((CL_INT)v52338->index+(CL_INT)1) ));
      princ_string(")");
      }
    GC_UNBIND; POP_SIGNAL;}

void  bag_expression_c_producer(Generate_c_producer *v49145,ClaireClass *v52319,bag *v52331,ClaireType *v52336,OID v43304)
{ GC_BIND;
  if (v52331->length == 0)
   { print_any(_oid_(v52319));
    princ_string("::empty(");
    if (v52336 != Kernel._void)
     { if (should_trace_ask_module1(Generate.it,5) == CTRUE)
       mtformat_module1(Generate.it,"t = ~S => ~S \n",5,list::alloc(2,_oid_(v52336),GC_OID((*Optimize.c_code)(_oid_(v52336),
        _oid_(Kernel._object)))));
      else ;(*Generate.expression)(GC_OID((*Optimize.c_code)(_oid_(v52336),
          _oid_(Kernel._object))),
        v43304);
      }
    princ_string(")");
    }
  else { print_any(_oid_(v52319));
      princ_string("::alloc");
      if ((v52319 == Kernel._tuple) && 
          (Optimize.OPT->alloc_stack == CTRUE))
       princ_string("Stack");
      princ_string("(");
      if (v52336 != Kernel._void)
       { (*Generate.expression)(GC_OID((*Optimize.c_code)(_oid_(v52336),
            _oid_(Kernel._object))),
          v43304);
        princ_string(",");
        }
      princ_integer(v52331->length);
      princ_string(",");
      args_list_bag(v52331,v43304,_sup_integer(v52331->length,2));
      princ_string(")");
      }
    GC_UNBIND; POP_SIGNAL;}

void  generate_s_file_string(char *v45520,list *v52331,OID v52329)
{ GC_BIND;
  { buffer * v52332 = GC_OBJECT(buffer,fopen_string1(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->source),v45520)),"-s")),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),"w"));
    list * v22838 = GC_OBJECT(list,add_modules_list(v52331));
    list * v31800 = GC_OBJECT(list,parents_list(v52331));
    if (should_trace_ask_module1(Generate.it,0) == CTRUE)
     mtformat_module1(Generate.it,"==== Generate system file ~A \n",0,list::alloc(1,GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->source),v45520)),"-s")),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))))));
    else ;(Optimize.OPT->cinterface = v52332);
    (Optimize.OPT->properties = set::empty(Kernel._property));
    (Optimize.OPT->objects = list::empty(Kernel._any));
    (Optimize.OPT->functions = list::empty(Kernel._any));
    (Optimize.OPT->need_to_close = set::empty(Kernel._any));
    (Optimize.OPT->legal_modules = set_I_bag(v31800));
    use_as_output_port(v52332);
    princ_string("// --- System configuration file for ");
    print_any(_string_(v45520));
    princ_string(" , [");
    print_any(GC_OID(_string_(date_I_integer(1))));
    princ_string("] ---\n\n");
    princ_string("#include <claire.h>\n");
    princ_string("#include <Kernel.h>\n");
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v52340);
      for (START(v22838); NEXT(v52340);)
      if (OBJECT(module,v52340)->made_of->length != 0)
       { princ_string("#include <");
        ident_symbol(OBJECT(symbol,(*Kernel.name)(v52340)));
        princ_string(".h>\n");
        }
      }
    create_load_modules_string(v45520,v52332,v31800,v52329);
    if ((boolean_I_any(_oid_(_at_property1(Core.main,Kernel._list))) == CTRUE) && 
        (domain_I_restriction(GC_OBJECT(restriction,((restriction *) _at_property1(Core.main,Kernel._list)))) == Kernel._list))
     { char * v52335 = "main_list";
      princ_string("\nextern void ");
      princ_string(v52335);
      princ_string("(list *l);\n");
      princ_string("void call_main() {");
      princ_string(v52335);
      princ_string("(ClEnv->params);}\n");
      }
    else princ_string("\nvoid call_main() {default_main();}\n");
      putc_char1(_char_("\n"[1 - 1]),v52332);
    fclose_filter1(v52332);
    }
  GC_UNBIND; POP_SIGNAL;}

void  create_load_modules_string(char *v45520,PortObject *v52332,list *v31800,OID v52329)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  breakline_void();
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52340);
    for (START(v31800); NEXT(v52340);)
    if ((*Kernel.status)(v52340) == ((OID)5))
     { princ_string("void load_");
      ident_symbol(OBJECT(symbol,(*Kernel.name)(v52340)));
      princ_string("() {");
      ident_symbol(OBJECT(symbol,(*Kernel.name)(v52340)));
      princ_string(".metaLoad();}\n");
      }
    }
  princ_string("\n\nvoid loadModules() \n");
  new_block_void();
  princ_string("//module definitions ");
  breakline_void();
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52340);
    for (START(v31800); NEXT(v52340);)
    { GC_LOOP;
      if (((v52340 == _oid_(claire.it)) ? CTRUE : ((v52340 == _oid_(mClaire.it)) ? CTRUE : ((v52340 == _oid_(Kernel.it)) ? CTRUE : CFALSE))) != CTRUE)
       { ident_symbol(OBJECT(symbol,(*Kernel.name)(v52340)));
        princ_string(".initModule(");
        print_any(_string_(string_I_symbol(OBJECT(symbol,(*Kernel.name)(v52340)))));
        princ_string(",");
        expression_thing(OBJECT(module,v52340)->part_of,Core.nil->value);
        princ_string(",");
        (*Generate.expression)(GC_OID((*Optimize.c_code)(GC_OID(_oid_(OBJECT(module,v52340)->uses)),
            _oid_(Kernel._list))),
          Core.nil->value);
        princ_string(",");
        breakline_void();
        print_any(GC_OID((*Kernel.source)(v52340)));
        princ_string(",");
        (*Generate.expression)(GC_OID((*Optimize.c_code)(GC_OID(_oid_(OBJECT(module,v52340)->made_of)),
            _oid_(Kernel._list))),
          Core.nil->value);
        princ_string(");");
        breakline_void();
        }
      GC_UNLOOP; POP_SIGNAL;}
    }
  princ_string("//module load ");
  breakline_void();
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52340);
    for (START(v31800); NEXT(v52340);)
    if (((CL_INT)OBJECT(module,v52340)->made_of->length > 0) && 
        ((*Kernel.status)(v52340) != ((OID)5)))
     { ident_symbol(OBJECT(symbol,(*Kernel.name)(v52340)));
      princ_string(".metaLoad();");
      breakline_void();
      }
    }
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52340);
    for (START(v31800); NEXT(v52340);)
    { GC_LOOP;
      { { OID  v52338 = GC_OID(get_property(Kernel.version,OBJECT(ClaireObject,v52340)));
          if (v52338 != CNULL)
           { ident_symbol(OBJECT(symbol,(*Kernel.name)(v52340)));
            princ_string(".it->version = ");
            print_any(v52338);
            princ_string(";");
            breakline_void();
            }
          else ;}
        if ((*Kernel.status)(v52340) == ((OID)5))
         { ident_symbol(OBJECT(symbol,(*Kernel.name)(v52340)));
          princ_string(".it->evaluate = ");
          expression_any(_oid_(make_function_string(append_string("load_",string_I_symbol(OBJECT(symbol,(*Kernel.name)(v52340)))))),Kernel.cfalse);
          breakline_void();
          ident_symbol(OBJECT(symbol,(*Kernel.name)(v52340)));
          princ_string(".it->status = 2;");
          breakline_void();
          }
        }
      GC_UNLOOP; POP_SIGNAL;}
    }
  princ_string("ClEnv->module_I = ");
  { OID  v32458;
    if (INHERIT(OWNER(v52329),Kernel._module))
     v32458 = v52329;
    else v32458 = _oid_(claire.it);
      (*Generate.expression)(v32458,
      Core.nil->value);
    }
  princ_string("; ");
  breakline_void();
  if ((CL_INT)Optimize.compiler->safety > 5)
   princ_string("ClAlloc->statusGC = 2;\n");
  if (Optimize.OPT->profile_ask == CTRUE)
   { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52332);
    bag *v52332_support;
    v52332_support = GC_OBJECT(bag,Reader.PRdependent->graph);
    for (START(v52332_support); NEXT(v52332);)
    if (INHERIT(OWNER(v52332),Kernel._property))
     { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v49478);
      bag *v49478_support;
      v49478_support = OBJECT(bag,nth_table1(Reader.PRdependent,v52332));
      for (START(v49478_support); NEXT(v49478);)
      if ((contain_ask_set(Optimize.OPT->to_remove,v49478) != CTRUE) && 
          (OBJECT(thing,v52332)->name->definition == OBJECT(thing,v49478)->name->definition))
       { princ_string("PRdepends_property(");
        expression_thing(OBJECT(thing,v52332),Core.nil->value);
        princ_string(",");
        expression_thing(OBJECT(thing,v49478),Core.nil->value);
        princ_string(");\n");
        }
      }
    }
  close_block_void();
  GC_UNBIND; POP_SIGNAL;}

void  methods_interface_c_producer(Generate_c_producer *v52319,ClaireClass *v52340)
{ GC_RESERVE(6);  // v3.0.55 optim !
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52332);
    bag *v52332_support;
    v52332_support = OBJECT(bag,nth_table1(Language.InterfaceList,_oid_(v52340)));
    for (START(v52332_support); NEXT(v52332);)
    { GC_LOOP;
      { ClaireObject * v52329 = GC_OBJECT(ClaireObject,_at_property1(OBJECT(property,v52332),v52340));
        if (should_trace_ask_module1(Generate.it,5) == CTRUE)
         mtformat_module1(Generate.it,"method interface ~S at ~S -> ~S \n",5,list::alloc(3,v52332,
          _oid_(v52340),
          _oid_(v52329)));
        else ;if ((Kernel._method == v52329->isa) && 
            (get_property(Kernel.formula,v52329) != CNULL))
         { ClaireClass * v52335 = class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(_oid_(v52329)))));
          list * v61902 = GC_OBJECT(list,cdr_list(GC_OBJECT(list,OBJECT(lambda,(*Kernel.formula)(_oid_(v52329)))->vars)));
          breakline_void();
          interface_I_c_producer(v52319,v52335);
          princ_string(" ");
          (*Kernel.c_princ)(GC_OID((*Kernel.name)(v52332)));
          princ_string("(");
          typed_args_list_list(v61902);
          princ_string(");  ");
          }
        }
      GC_UNLOOP; POP_SIGNAL;}
    }
  GC_UNBIND; POP_SIGNAL;}

void  methods_bodies_c_producer(Generate_c_producer *v52319,ClaireClass *v52340)
{ GC_RESERVE(6);  // v3.0.55 optim !
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52332);
    bag *v52332_support;
    v52332_support = OBJECT(bag,nth_table1(Language.InterfaceList,_oid_(v52340)));
    for (START(v52332_support); NEXT(v52332);)
    { GC_LOOP;
      { ClaireObject * v52329 = GC_OBJECT(ClaireObject,_at_property1(OBJECT(property,v52332),v52340));
        if (should_trace_ask_module1(Generate.it,5) == CTRUE)
         mtformat_module1(Generate.it,"write method body ~S at ~S -> ~S \n",5,list::alloc(3,v52332,
          _oid_(v52340),
          _oid_(v52329)));
        else ;if ((Kernel._method == v52329->isa) && 
            (get_property(Kernel.formula,v52329) != CNULL))
         { ClaireClass * v52335 = class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(_oid_(v52329)))));
          list * v61902 = GC_OBJECT(list,cdr_list(GC_OBJECT(list,OBJECT(lambda,(*Kernel.formula)(_oid_(v52329)))->vars)));
          breakline_void();
          princ_string("// interface method ");
          breakline_void();
          breakline_void();
          interface_I_c_producer(v52319,v52335);
          princ_string(" ");
          class_princ_class(v52340);
          princ_string("::");
          (*Kernel.c_princ)(GC_OID((*Kernel.name)(v52332)));
          princ_string("(");
          typed_args_list_list(v61902);
          princ_string(")");
          breakline_void();
          princ_string("  ");
          princ_string("\t{ ");
          if (v52335 != Kernel._void)
           { princ_string("return (");
            interface_I_c_producer(v52319,v52335);
            princ_string(") ");
            }
          if ((OBJECT(ClaireBoolean,(*Kernel._sup)(GC_OID((*Kernel.dispatcher)(v52332)),
            ((OID)0)))) == CTRUE)
           { (*Generate.expression)(v52332,
              Core.nil->value);
            princ_string("->fcall((CL_INT) this");
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(v52338);
              for (START(v61902); NEXT(v52338);)
              { princ_string(",(CL_INT) ");
                (*Generate.expression)(v52338,
                  Core.nil->value);
                }
              }
            princ_string(")");
            }
          else { c_princ_function(OBJECT(ClaireFunction,(*Optimize.functional_I)(_oid_(v52329))));
              princ_string("(this");
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(v52338);
                for (START(v61902); NEXT(v52338);)
                { princ_string(",");
                  (*Generate.expression)(v52338,
                    Core.nil->value);
                  }
                }
              princ_string(")");
              }
            princ_string(";}\n");
          breakline_void();
          }
        }
      GC_UNLOOP; POP_SIGNAL;}
    }
  GC_UNBIND; POP_SIGNAL;}



