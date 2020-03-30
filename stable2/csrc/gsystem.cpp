/***** CLAIRE Compilation of file ./compile/gsystem.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:49 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>
#include <Optimize.h>
#include <Generate.h>
void  ident_symbol(symbol *v45520)
{ (*Language.ident)(Generate.PRODUCER->value,
    _oid_(v45520));
  POP_SIGNAL;}

void  ident_thing(thing *v45520)
{ (*Language.ident)(Generate.PRODUCER->value,
    _oid_(v45520->name));
  POP_SIGNAL;}

void  ident_class(ClaireClass *v45520)
{ (*Language.ident)(Generate.PRODUCER->value,
    _oid_(v45520->name));
  POP_SIGNAL;}

void  interface_I_class(ClaireClass *v52319)
{ (*Generate.interface_I)(Generate.PRODUCER->value,
    _oid_(v52319));
  POP_SIGNAL;}

void  class_princ_class(ClaireClass *v52319)
{ (*Generate.class_princ)(Generate.PRODUCER->value,
    _oid_(v52319));
  POP_SIGNAL;}

OID  indent_c_void()
{ { OID Result = 0;
    { CL_INT  v52340 = Optimize.OPT->level;
      { CL_INT loop_handle = ClEnv->cHandle;
        Result= _oid_(CFALSE);
        while (((CL_INT)v52340 > 0))
        { princ_string("  ");
          v52340= ((CL_INT)v52340-(CL_INT)1);
          POP_SIGNAL;}
        }
      }
    POP_SIGNAL; return (Result);}
  }

OID  breakline_void()
{ princ_string("\n");
  POP_SIGNAL; return (indent_c_void());}

void  new_block_void()
{ (Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
  princ_string("{ ");
  POP_SIGNAL;}

void  close_block_void()
{ (Optimize.OPT->level = ((CL_INT)Optimize.OPT->level-(CL_INT)1));
  princ_string("}");
  breakline_void();
  POP_SIGNAL;}

void  c_test_any(OID v52340)
{ GC_BIND;
  { OID  v52336 = GC_OID((*Optimize.c_type)(v52340));
    ClaireClass * v52335 = osort_any(v52336);
    OID  v52337 = GC_OID((*Optimize.c_code)(v52340,
      _oid_(v52335)));
    ClaireBoolean * v52322 = c_func_any(v52337);
    princ_string("type -> ");
    print_any(v52336);
    princ_string(" [sort ");
    print_any(_oid_(v52335));
    princ_string("]\n");
    princ_string("opt[");
    print_any(_oid_(OWNER(v52337)));
    princ_string("] -> ");
    print_any(v52337);
    princ_string(" \n");
    if (v52322 == CTRUE)
     { princ_string("exp  -> ");
      (*Generate.expression)(v52337,
        Core.nil->value);
      princ_string("\n");
      }
    else { princ_string("stat -> ");
        statement_any(v52337,_string_("result"),Core.nil->value);
        princ_string("\n");
        }
      }
  GC_UNBIND; POP_SIGNAL;}

void  c_test_method(method *v52329)
{ GC_BIND;
  { lambda * v52331 = GC_OBJECT(lambda,v52329->formula);
    if (v52331 == (NULL))
     ;else { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
         mtformat_module1(Generate.it,"---- Compiling ~S ---- \n",0,list::alloc(1,_oid_(v52329)));
        else ;(Optimize.OPT->in_method = _oid_(v52329));
        (Optimize.OPT->protection = CFALSE);
        (Optimize.OPT->allocation = CFALSE);
        if ((CL_INT)Optimize.OPT->loop_index > 0)
         (Optimize.OPT->loop_index = 0);
        (Optimize.OPT->loop_gc = CFALSE);
        (Optimize.OPT->use_update = CFALSE);
        (Optimize.OPT->use_nth_equal = CFALSE);
        (Optimize.OPT->max_vars = 0);
        (Optimize.OPT->online_ask = CFALSE);
        (Optimize.OPT->legal_modules = ((set *) Kernel._module->instances));
        (OBJECT(Generate_producer,Generate.PRODUCER->value)->body = v52331->body);
        { ClaireClass * v52335 = Kernel._void;
          OID  v3395;
          { { v52335= check_sort_method(v52329);
              v3395 = OBJECT(Generate_producer,Generate.PRODUCER->value)->body;
              }
            GC_OID(v3395);}
          char * v15642 = GC_STRING(string_v((*Generate.protect_result)(Generate.PRODUCER->value,
            _oid_(v52335),
            _oid_(Optimize.OPT->protection),
            _oid_(v52329))));
          princ_string("Opt => ");
          print_any(v3395);
          princ_string(" \n\n");
          new_block_void();
          (*Generate.print_body)(v3395,
            _string_(v15642),
            _oid_(v52335),
            GC_OID(v52331->body),
            Kernel.ctrue);
          close_block_void();
          }
        (Optimize.OPT->in_method = CNULL);
        }
      }
  GC_UNBIND; POP_SIGNAL;}

void  compile_module(module *v45520)
{ GC_BIND;
  (Optimize.OPT->need_modules = Kernel.emptySet);
  (OBJECT(Generate_producer,Generate.PRODUCER->value)->stat = 0);
  { bag * v49353 = GC_OBJECT(list,parents_list(GC_OBJECT(list,add_modules_list(list::alloc(1,_oid_(v45520))))));
    list * v49295 = GC_OBJECT(list,Optimize.compiler->headers);
    { Optimize_meta_compiler * v29475 = Optimize.compiler; 
      list * v29476;
      { list * v18565;
        { list * v20739 = list::empty(Kernel._string);
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v52340);
            bag *v52340_support;
            v52340_support = GC_OBJECT(list,v45520->made_of);
            for (START(v52340_support); NEXT(v52340);)
            if (match_wildcard_ask_string(string_v(v52340),"*.h*") == CTRUE)
             v20739->addFast((OID)v52340);
            }
          v18565 = GC_OBJECT(list,v20739);
          }
        v29476 = append_list(GC_OBJECT(list,Optimize.compiler->headers),v18565);
        }
      (v29475->headers = v29476);}
    update_property(Optimize.legal_modules,
      Optimize.OPT,
      9,
      Kernel._object,
      GC_OID((*Kernel.set_I)(_oid_(v49353))));
    if (Optimize.compiler->class2file_ask == CTRUE)
     { if (should_trace_ask_module1(Generate.it,2) == CTRUE)
       mtformat_module1(Generate.it,"**** Compiling the module ~A [v. 3.~A - verbose:~A opt:~S] \n",2,GC_OBJECT(list,list::alloc(4,_string_(string_I_symbol(v45520->name)),
        GC_OID(Optimize.compiler->version),
        ((OID)ClEnv->verbose),
        _oid_(Optimize.compiler->optimize_ask))));
      else ;write_property(Generate.outmodule,Optimize.OPT,GC_OID(_oid_(fopen_string1(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),GC_STRING(string_v((*Generate.c_string)(Generate.PRODUCER->value,
        _oid_(v45520->name)))))),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),"w"))));
      generate_files_module(v45520);
      begin_module(v45520);
      generate_classes_module(v45520);
      generate_c2f_module(v45520);
      end_module(v45520);
      }
    else { if (should_trace_ask_module1(Generate.it,5) == CTRUE)
         mtformat_module1(Generate.it,"call generate_files ~S  \n",5,GC_OBJECT(list,list::alloc(1,_oid_(v45520))));
        else ;generate_files_module(v45520);
        generate_f2f_module(v45520);
        generate_interface_module(v45520,GC_OBJECT(set,Optimize.OPT->legal_modules));
        }
      (Optimize.compiler->headers = v49295);
    v49353= GC_OBJECT(set,difference_set(GC_OBJECT(set,set_I_set(Optimize.OPT->need_modules)),GC_OBJECT(set,Optimize.OPT->legal_modules)));
    if (should_trace_ask_module1(Generate.it,1) == CTRUE)
     mtformat_module1(Generate.it,"++++ v3.3.32 info: ~A GC protection inserted in ~S. \n",1,GC_OBJECT(list,list::alloc(2,((OID)OBJECT(Generate_producer,Generate.PRODUCER->value)->stat),_oid_(v45520))));
    else ;if (v49353->length != 0)
     { if (should_trace_ask_module1(Generate.it,2) == CTRUE)
       mtformat_module1(Generate.it,"---- WARNING: ~S should be declared for ~S\n",2,GC_OBJECT(list,list::alloc(2,_oid_(v49353),_oid_(v45520))));
      else ;}
    }
  GC_UNBIND; POP_SIGNAL;}

void  generate_files_module(module *v45520)
{ GC_RESERVE(6);  // v3.0.55 optim !
  if (should_trace_ask_module1(Generate.it,0) == CTRUE)
   mtformat_module1(Generate.it,"==== Generate ~A files for module ~S [verbose = ~A, Opt? = ~S] \n",0,list::alloc(4,GC_OID(_string_(OBJECT(Generate_producer,Generate.PRODUCER->value)->comment)),
    _oid_(v45520),
    ((OID)ClEnv->verbose),
    _oid_(Optimize.compiler->optimize_ask)));
  else ;(Optimize.OPT->instructions = list::empty(Kernel._any));
  (Optimize.OPT->properties = set::empty(Kernel._property));
  (Optimize.OPT->objects = list::empty(Kernel._object));
  (Optimize.OPT->functions = list::empty(Kernel._any));
  (Optimize.OPT->need_to_close = set::empty(Kernel._any));
  (*Generate.start_module_interface)(Generate.PRODUCER->value,
    _oid_(v45520));
  begin_module(v45520);
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52340);
    bag *v52340_support;
    v52340_support = GC_OBJECT(list,entries_string2(GC_STRING(v45520->source)));
    for (START(v52340_support); NEXT(v52340);)
    { GC_LOOP;
      if ((match_wildcard_ask_string(string_v(v52340),"*.o") == CTRUE) || 
          (match_wildcard_ask_string(string_v(v52340),"*.obj") == CTRUE))
       { if (isfile_ask_string(append_string(GC_STRING(append_string(GC_STRING(v45520->source),GC_STRING(string_v(Core._starfs_star->value)))),string_v(v52340))) == CTRUE)
         { if (should_trace_ask_module1(Generate.it,3) == CTRUE)
           mtformat_module1(Generate.it,"++++ Unlink file ~A \n",3,GC_OBJECT(list,list::alloc(1,v52340)));
          else ;unlink_string(append_string(GC_STRING(append_string(GC_STRING(v45520->source),GC_STRING(string_v(Core._starfs_star->value)))),string_v(v52340)));
          }
        }
      GC_UNLOOP; POP_SIGNAL;}
    }
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52340);
    bag *v52340_support;
    v52340_support = GC_OBJECT(list,entries_string2(GC_STRING(Optimize.compiler->source)));
    for (START(v52340_support); NEXT(v52340);)
    { GC_LOOP;
      if ((match_wildcard_ask_string(string_v(v52340),"*.o") == CTRUE) || 
          (match_wildcard_ask_string(string_v(v52340),"*.obj") == CTRUE))
       { if (isfile_ask_string(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),string_v(v52340))) == CTRUE)
         { if (should_trace_ask_module1(Generate.it,3) == CTRUE)
           mtformat_module1(Generate.it,"++++ Unlink file ~A \n",3,GC_OBJECT(list,list::alloc(1,v52340)));
          else ;unlink_string(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),string_v(v52340)));
          }
        }
      GC_UNLOOP; POP_SIGNAL;}
    }
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52340);
    bag *v52340_support;
    v52340_support = GC_OBJECT(list,v45520->made_of);
    for (START(v52340_support); NEXT(v52340);)
    { GC_LOOP;
      if ((match_wildcard_ask_string(string_v(v52340),"*.cl") == CTRUE) || 
          (match_wildcard_ask_string(string_v(v52340),"*.*") != CTRUE))
       { GC__OID(v52340 = _string_(replace_string(string_v(v52340),".cl","")), 3);
        if (equal(v52340,_string_(string_I_symbol(v45520->name))) == CTRUE)
         (*Optimize.Cerror)(_string_("[211] ~S cannot be used both as a file and module name"),
          v52340);
        generate_file_string2(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(v45520->source),GC_STRING(string_v(Core._starfs_star->value)))),string_v(v52340))),GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),string_v(v52340))));
        }
      GC_UNLOOP; POP_SIGNAL;}
    }
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52340);
    bag *v52340_support;
    v52340_support = GC_OBJECT(list,v45520->made_of);
    for (START(v52340_support); NEXT(v52340);)
    { GC_LOOP;
      if (match_wildcard_ask_string(string_v(v52340),"*@PATH_INFO@*") == CTRUE)
       { list * v52336 = GC_OBJECT(list,explode_string(string_v(v52340),"@PATH_INFO@"));
        char * v17901 = GC_STRING(replace_string(string_v((*(v52336))[1]),GC_STRING(string_v(Core._starfs_star->value)),"-"));
        if (equal_string(left_string(v17901,2),"./") == CTRUE)
         GC__STRING(v17901 = substring_string(v17901,3,LENGTH_STRING(v17901)), 5);
        if (equal_string(left_string(v17901,1),".") == CTRUE)
         GC__STRING(v17901 = substring_string(v17901,2,LENGTH_STRING(v17901)), 5);
        if (equal_string(v17901,string_I_symbol(v45520->name)) == CTRUE)
         (*Optimize.Cerror)(_string_("[211] ~S cannot be used both as a file and module name"),
          _string_(v17901));
        generate_wcl_file_string(string_v((*(v52336))[1]),string_v(v52340),GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),v17901)));
        }
      GC_UNLOOP; POP_SIGNAL;}
    }
  end_module(v45520);
  GC_UNBIND; POP_SIGNAL;}

void  generate_f2f_module(module *v52329)
{ GC_BIND;
  { buffer * v52332 = GC_OBJECT(buffer,fopen_string1(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),string_I_symbol(v52329->name))),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),"w"));
    if (should_trace_ask_module1(Generate.it,0) == CTRUE)
     mtformat_module1(Generate.it,"==== generate file for module ~S ==== \n",0,list::alloc(1,_oid_(v52329)));
    else ;(Optimize.OPT->outfile = v52332);
    generate_file_string1(string_I_symbol(v52329->name),v52329);
    }
  GC_UNBIND; POP_SIGNAL;}

void  generate_file_string1(char *v52335,module *v52329)
{ GC_BIND;
  start_file_string(v52335,v52329);
  use_as_output_port(Optimize.OPT->outfile);
  (*Generate.generate_classes)(Generate.PRODUCER->value,
    _string_(v52335),
    _oid_(v52329));
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52319);
    bag *v52319_support;
    v52319_support = GC_OBJECT(list,Optimize.OPT->objects);
    for (START(v52319_support); NEXT(v52319);)
    if (INHERIT(OWNER(v52319),Kernel._class))
     (*Generate.methods_bodies)(Generate.PRODUCER->value,
      v52319);
    }
  generate_meta_load_module(v52329);
  breakline_void();
  close_block_void();
  breakline_void();
  (*Core.fclose)(GC_OID(_oid_(Optimize.OPT->outfile)));
  GC_UNBIND; POP_SIGNAL;}

void  generate_classes_module(module *v45520)
{ GC_BIND;
  erase_table(Generate.classFile);
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52319);
    bag *v52319_support;
    v52319_support = GC_OBJECT(list,Optimize.OPT->objects);
    for (START(v52319_support); NEXT(v52319);)
    { GC_LOOP;
      if (INHERIT(OWNER(v52319),Kernel._class))
       { put_table(Generate.classFile,v52319,_oid_(fopen_string1(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),GC_STRING(string_v((*Generate.c_string)(Generate.PRODUCER->value,
          GC_OID((*Kernel.name)(v52319))))))),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),"w")));
        use_as_output_port(OBJECT(PortObject,nth_table1(Generate.classFile,v52319)));
        if (should_trace_ask_module1(Generate.it,2) == CTRUE)
         mtformat_module1(Generate.it,"++++ Creating the file ~A.java\n",2,GC_OBJECT(list,list::alloc(1,GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
          GC_OID((*Kernel.name)(v52319)))))));
        else ;(Optimize.OPT->level = 0);
        princ_string("// class file for ");
        print_any(v52319);
        princ_string(" in module ");
        print_any(_oid_(v45520));
        princ_string(" ");
        breakline_void();
        breakline_void();
        breakline_void();
        princ_string("public class ");
        ident_symbol(OBJECT(symbol,(*Kernel.name)(v52319)));
        princ_string(" extends ");
        ident_symbol(OBJECT(ClaireClass,v52319)->superclass->name);
        new_block_void();
        breakline_void();
        breakline_void();
        princ_string("/* empty constructor by default */");
        breakline_void();
        princ_string("public ");
        ident_symbol(OBJECT(symbol,(*Kernel.name)(v52319)));
        princ_string("() {}");
        breakline_void();
        breakline_void();
        breakline_void();
        princ_string("/* declaration of fields */");
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v52341);
          bag *v52341_support;
          v52341_support = GC_OBJECT(list,OBJECT(bag,(*Optimize.get_indexed)(v52319)));
          for (START(v52341_support); NEXT(v52341);)
          if (_oid_(domain_I_restriction(OBJECT(restriction,v52341))) == v52319)
           { breakline_void();
            princ_string("public  ");
            interface_I_class(psort_any(_oid_(OBJECT(restriction,v52341)->range)));
            princ_string(" ");
            ident_symbol(OBJECT(restriction,v52341)->selector->name);
            princ_string(";");
            }
          }
        breakline_void();
        (*Core.fclose)(nth_table1(Generate.classFile,v52319));
        }
      GC_UNLOOP; POP_SIGNAL;}
    }
  GC_UNBIND; POP_SIGNAL;}

void  generate_c2f_module(module *v45520)
{ GC_BIND;
  { buffer * v35985 = GC_OBJECT(buffer,fopen_string1(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),GC_STRING(string_v((*Generate.c_string)(Generate.PRODUCER->value,
      _oid_(v45520->name)))))),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),"w"));
    (Optimize.OPT->outfile = v35985);
    use_as_output_port(v35985);
    (*Generate.generate_start_file)(Generate.PRODUCER->value,
      _oid_(v45520));
    putc_char1(_char_("\n"[1 - 1]),v35985);
    fclose_filter1(v35985);
    generate_functions_module(v45520);
    v35985= GC_OBJECT(buffer,fopen_string1(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),GC_STRING(string_v((*Generate.c_string)(Generate.PRODUCER->value,
      _oid_(v45520->name)))))),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),"a"));
    use_as_output_port(v35985);
    (Optimize.OPT->outfile = v35985);
    (Optimize.OPT->level = 2);
    generate_objects_module(v45520);
    generate_meta_load_module(v45520);
    (*Generate.generate_end_file)(Generate.PRODUCER->value,
      _oid_(v45520));
    }
  GC_UNBIND; POP_SIGNAL;}

void  generate_interface_module(module *v45520,bag *v52331)
{ GC_BIND;
  if (should_trace_ask_module1(Generate.it,0) == CTRUE)
   mtformat_module1(Generate.it,"==== Generate interface (.h) files for module ~S \n",0,list::alloc(1,_oid_(v45520)));
  else ;use_as_output_port(Optimize.OPT->cinterface);
  breakline_void();
  (*Generate.generate_interface)(Generate.PRODUCER->value,
    _oid_(v45520));
  (*Generate.namespace_I)(Generate.PRODUCER->value,
    _oid_(v45520));
  generate_objects_module(v45520);
  (*Kernel.module_I)(Generate.PRODUCER->value,
    _oid_(v45520));
  (*Generate.end_module_interface)(Generate.PRODUCER->value,
    _oid_(v45520));
  putc_char1(_char_("\n"[1 - 1]),GC_OBJECT(PortObject,Optimize.OPT->cinterface));
  (*Core.fclose)(GC_OID(_oid_(Optimize.OPT->cinterface)));
  use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value));
  GC_UNBIND; POP_SIGNAL;}

void  generate_objects_module(module *v45520)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52340);
    bag *v52340_support;
    v52340_support = GC_OBJECT(list,Optimize.OPT->objects);
    for (START(v52340_support); NEXT(v52340);)
    { breakline_void();
      (*Generate.public_static)(Generate.PRODUCER->value);
      if (INHERIT(OWNER(v52340),Core._global_variable))
       { { OID  v19526;
          if (nativeVar_ask_global_variable(OBJECT(global_variable,v52340)) == CTRUE)
           v19526 = _oid_(getRange_global_variable(OBJECT(global_variable,v52340)));
          else v19526 = _oid_(Core._global_variable);
            (*Generate.interface_I)(Generate.PRODUCER->value,
            v19526);
          }
        princ_string(" ");
        ident_symbol(OBJECT(thing,v52340)->name);
        princ_string(";");
        }
      else { (*Generate.interface_I)(Generate.PRODUCER->value,
            _oid_(psort_any(_oid_(OWNER(v52340)))));
          princ_string(" ");
          if (INHERIT(OWNER(v52340),Kernel._class))
           { princ_string("_");
            c_princ_string(string_I_symbol(OBJECT(symbol,(*Kernel.name)(v52340))));
            }
          else if (INHERIT(OWNER(v52340),Reader._reserved_keyword))
           { princ_string("_cl_");
            c_princ_string(string_I_symbol(OBJECT(symbol,(*Kernel.name)(v52340))));
            }
          else ident_symbol(OBJECT(symbol,(*Kernel.name)(v52340)));
            princ_string(";");
          }
        }
    }
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52340);
    bag *v52340_support;
    v52340_support = GC_OBJECT(set,Optimize.OPT->properties);
    for (START(v52340_support); NEXT(v52340);)
    { GC_LOOP;
      if (Optimize.OPT->objects->memq(v52340) != CTRUE)
       { { OID  v62168;
          { { OID  v51277 = CNULL;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(v49478);
                bag *v49478_support;
                v49478_support = GC_OBJECT(set,Optimize.OPT->properties);
                for (START(v49478_support); NEXT(v49478);)
                { GC_LOOP;
                  if (v49478 != v52340)
                   { if (equal_string(string_I_symbol(OBJECT(thing,v49478)->name),string_I_symbol(OBJECT(thing,v52340)->name)) == CTRUE)
                     { v51277= v49478;
                      ClEnv->cHandle = loop_handle; break;}
                    }
                  GC_UNLOOP; POP_SIGNAL;}
                }
              v62168 = v51277;
              }
            GC_OID(v62168);}
          if (v62168 != CNULL)
           { property * v49478 = OBJECT(property,v62168);
            close_exception(((general_error *) (*Core._general_error)(_string_("[217] ~S and ~S cannot be defined in the same module"),
              _oid_(list::alloc(2,_oid_(v49478),v52340)))));
            }
          else ;}
        princ_string("\n");
        (*Generate.public_static)(Generate.PRODUCER->value);
        (*Generate.interface_I)(Generate.PRODUCER->value,
          _oid_(psort_any(_oid_(OWNER(v52340)))));
        princ_string(" ");
        ident_symbol(OBJECT(thing,v52340)->name);
        princ_string(";// ");
        print_any(_oid_(OBJECT(thing,v52340)->name));
        }
      GC_UNLOOP; POP_SIGNAL;}
    }
  GC_UNBIND; POP_SIGNAL;}

void  generate_meta_load_module(module *v45520)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  princ_string("// definition of the meta-model for ");
  print_any(_oid_(v45520));
  breakline_void();
  (*Generate.generate_meta_load)(Generate.PRODUCER->value,
    _oid_(v45520));
  princ_string("// definition of the properties ");
  breakline_void();
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52340);
    bag *v52340_support;
    v52340_support = GC_OBJECT(set,Optimize.OPT->properties);
    for (START(v52340_support); NEXT(v52340);)
    if (Optimize.OPT->objects->memq(v52340) != CTRUE)
     (*Generate.declare)(Generate.PRODUCER->value,
      v52340);
    }
  breakline_void();
  breakline_void();
  princ_string("// instructions from module sources ");
  breakline_void();
  { OID  v52326 = CNULL;
    ClaireBoolean * v57154 = CFALSE;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52325);
      bag *v52325_support;
      v52325_support = GC_OBJECT(list,Optimize.OPT->instructions);
      for (START(v52325_support); NEXT(v52325);)
      { GC_LOOP;
        { breakline_void();
          if (Kernel._string == OWNER(v52325))
           { if (equal(_oid_(Kernel._string),_oid_(OWNER(v52326))) != CTRUE)
             breakline_void();
            princ_string("// ");
            (*Kernel.princ)(v52325);
            }
          else if (global_var_def_ask_any(v52325) == CTRUE)
           { if (v57154 == CTRUE)
             { princ_string("GC_UNBIND;\n");
              v57154= CFALSE;
              }
            (*Generate.global_var_def_I)(Generate.PRODUCER->value,
              _oid_(v45520),
              v52325);
            }
          else { if (v57154 != CTRUE)
               { princ_string("GC_BIND;\n");
                v57154= CTRUE;
                }
              statement_any(v52325,_oid_(Kernel.emptySet),_oid_(Kernel.emptySet));
              }
            GC__OID(v52326 = v52325, 1);
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    if (v57154 == CTRUE)
     princ_string("GC_UNBIND;\n");
    }
  GC_UNBIND; POP_SIGNAL;}

ClaireBoolean * global_var_def_ask_any(OID v52340)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = ((INHERIT(OWNER(v52340),Language._Let)) ?
      ((INHERIT(OWNER(OBJECT(Let,v52340)->value),Language._Call)) ? (((*Kernel.selector)(OBJECT(Let,v52340)->value) == _oid_(Optimize.object_I)) ? (((*(OBJECT(bag,(*Core.args)(OBJECT(Let,v52340)->value))))[2] == _oid_(Core._global_variable)) ? CTRUE: CFALSE): CFALSE): CFALSE) :
      CFALSE );
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

ClaireClass * getRange_global_variable(global_variable *v52340)
{ { ClaireClass *Result ;
    Result = ((equal(_oid_(v52340->range),_oid_(Kernel.emptySet)) == CTRUE) ?
      OWNER(v52340->value) :
      class_I_type(v52340->range) );
    POP_SIGNAL; return (Result);}
  }

void  generate_functions_module(module *v45520)
{ GC_BIND;
  princ_string("// definition of class methods ");
  { PortObject * v52332 = GC_OBJECT(PortObject,Optimize.OPT->outfile);
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52322);
      bag *v52322_support;
      v52322_support = GC_OBJECT(list,Optimize.OPT->functions);
      for (START(v52322_support); NEXT(v52322);)
      { GC_LOOP;
        { (Optimize.OPT->level = 2);
          (Optimize.OPT->outfile = v52332);
          print_c_function_lambda2(GC_OBJECT(lambda,OBJECT(lambda,(*Kernel.nth)(v52322,
            ((OID)1)))),GC_STRING(string_v((*Kernel.nth)(v52322,
            ((OID)2)))),GC_OID((*Kernel.nth)(v52322,
            ((OID)3))));
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    }
  GC_UNBIND; POP_SIGNAL;}

list * parents_module(module *v45520,list *v52331)
{ if (v52331->memq(_oid_(v45520)) == CTRUE) 
  { { list *Result ;
      Result = v52331;
      return (Result);}
     }
  else{ GC_BIND;
    if (((v45520->part_of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     v52331= GC_OBJECT(list,parents_module(v45520->part_of,v52331));
    v52331= GC_OBJECT(list,v52331->addFast((OID)_oid_(v45520)));
    { list *Result ;
      Result = v52331;
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  }

list * parents_list(list *v45520)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { list *Result ;
    { list * v52331 = list::empty(Kernel._module);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v52340);
        for (START(v45520); NEXT(v52340);)
        { GC_LOOP;
          GC__ANY(v52331 = parents_module(OBJECT(module,v52340),v52331), 1);
          GC_UNLOOP; POP_SIGNAL;}
        }
      Result = v52331;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  get_module2(module *v52329)
{ load_module(v52329);
  begin_module(v52329);
  POP_SIGNAL;}

void  generate_file_string2(char *v45520,char *v49168)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { PortObject * v49477 = GC_OBJECT(PortObject,fopen_source_string1(v45520));
    OID  v52322 = GC_OID((*(get_location_port1(v49477)->copyIfNeeded()))[1]);
    ClaireBoolean * v52318 = Reader.reader->toplevel;
    PortObject * v49479 = GC_OBJECT(PortObject,Reader.reader->fromp);
    if (should_trace_ask_module1(Generate.it,2) == CTRUE)
     mtformat_module1(Generate.it,"++++ Generate the file ~A [v3.~A - safety:~A] \n",2,list::alloc(3,v52322,
      GC_OID(Optimize.compiler->version),
      ((OID)Optimize.compiler->safety)));
    else ;if (Optimize.compiler->class2file_ask != CTRUE)
     (Optimize.OPT->outfile = fopen_string1(GC_STRING(append_string(v49168,GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),"w"));
    (Reader.reader->toplevel = CFALSE);
    (Optimize.compiler->loading_ask = CTRUE);
    (Reader.reader->nb_line = 1);
    (Reader.reader->external = v45520);
    (Reader.reader->fromp = v49477);
    if (Optimize.compiler->class2file_ask != CTRUE)
     { start_file_string(v45520,ClEnv->module_I);
      if (Optimize.compiler->debug_ask->memq(_oid_(ClEnv->module_I)) == CTRUE)
       { PortObject * v52332 = use_as_output_port(Optimize.OPT->outfile);
        princ_string("\nstatic char *debug_local_file = ");
        print_any(GC_OID(_string_(realpath_string(string_v(v52322)))));
        princ_string(";\n");
        use_as_output_port(v52332);
        }
      }
    { OID  v61901 = GC_OID(readblock_port(v49477));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((equal(v61901,Core._eof->value) != CTRUE))
        { GC_LOOP;
          if ((CL_INT)ClEnv->verbose > 5)
           { princ_string("[");
            princ_integer(Reader.reader->nb_line);
            princ_string("] ");
            print_any(_oid_(OWNER(v61901)));
            princ_string(" (");
            print_any(GC_OID(_oid_(Optimize.OPT->need_modules)));
            princ_string("%)\n");
            }
          if ((Kernel._string == OWNER(v61901)) && 
              (Optimize.compiler->class2file_ask != CTRUE))
           { if ((CL_INT)Optimize.compiler->naming < 2)
             { PortObject * v49540 = use_as_output_port(Optimize.OPT->outfile);
              princ_string("\n//");
              (*Kernel.princ)(v61901);
              use_as_output_port(v49540);
              }
            }
          else GC_OBJECT(list,Optimize.OPT->instructions)->addFast((OID)GC_OID((*Optimize.c_code)(v61901,
              _oid_(Kernel._void))));
            GC__OID(v61901 = readblock_port(v49477), 1);
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    putc_char1(_char_("\n"[1 - 1]),GC_OBJECT(PortObject,Optimize.OPT->outfile));
    (*Core.fclose)(_oid_(v49477));
    (Optimize.compiler->loading_ask = CFALSE);
    (Reader.reader->toplevel = v52318);
    (Reader.reader->external = "toplevel");
    (Reader.reader->fromp = v49479);
    if (Optimize.compiler->class2file_ask != CTRUE)
     { putc_char1(_char_("\n"[1 - 1]),GC_OBJECT(PortObject,Optimize.OPT->outfile));
      (*Core.fclose)(GC_OID(_oid_(Optimize.OPT->outfile)));
      }
    }
  GC_UNBIND; POP_SIGNAL;}

void  generate_wcl_file_string(char *v45520,char *v25607,char *v49168)
{ GC_BIND;
  if (should_trace_ask_module1(Generate.it,2) == CTRUE)
   mtformat_module1(Generate.it,"++++ Generate the WCL file ~A [v3.~A - safety:~A] \n",2,list::alloc(3,_string_(v45520),
    GC_OID(Optimize.compiler->version),
    ((OID)Optimize.compiler->safety)));
  else ;(Optimize.compiler->loading_ask = CTRUE);
  (Optimize.OPT->outfile = fopen_string1(GC_STRING(append_string(v49168,GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),"w"));
  start_file_string(v45520,ClEnv->module_I);
  if (Optimize.compiler->debug_ask->memq(_oid_(ClEnv->module_I)) == CTRUE)
   { PortObject * v52332 = use_as_output_port(Optimize.OPT->outfile);
    princ_string("\nstatic char *debug_local_file = ");
    print_any(GC_OID(_string_(realpath_string(v45520))));
    princ_string(";\n");
    use_as_output_port(v52332);
    }
  { list * v57234 = GC_OBJECT(list,load_wcl_I_string1(v25607));
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v52340);
      for (START(v57234); NEXT(v52340);)
      { GC_LOOP;
        GC_OBJECT(list,Optimize.OPT->instructions)->addFast((OID)GC_OID((*Optimize.c_code)(v52340,
          _oid_(Kernel._void))));
        GC_UNLOOP; POP_SIGNAL;}
      }
    putc_char1(_char_("\n"[1 - 1]),GC_OBJECT(PortObject,Optimize.OPT->outfile));
    (Optimize.compiler->loading_ask = CFALSE);
    if (Optimize.compiler->class2file_ask != CTRUE)
     { putc_char1(_char_("\n"[1 - 1]),GC_OBJECT(PortObject,Optimize.OPT->outfile));
      (*Core.fclose)(GC_OID(_oid_(Optimize.OPT->outfile)));
      }
    }
  GC_UNBIND; POP_SIGNAL;}

OID  make_c_function_lambda_Generate(lambda *v45520,char *v24332,OID v52329)
{ { OID Result = 0;
    if (Optimize.compiler->class2file_ask == CTRUE)
     Result = (*Generate.create_function_entry)(Generate.PRODUCER->value,
      _oid_(v45520),
      _string_(v24332),
      v52329);
    else Result = print_c_function_lambda2(v45520,v24332,v52329);
      POP_SIGNAL; return (Result);}
  }

OID  print_c_function_lambda2(lambda *v45520,char *v24332,OID v52329)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  (OBJECT(Generate_producer,Generate.PRODUCER->value)->body = v45520->body);
  (Optimize._starin_c_func_star->value= Kernel.ctrue);
  (Generate._stardebug_calls_star->value= _oid_(list::empty(U_type(Language._Call,Language._Call_method))));
  { OID Result = 0;
    { blob * v55600 = GC_OBJECT(blob,blob_I_void1());
      PortObject * v19787 = GC_OBJECT(PortObject,Optimize.OPT->outfile);
      (Optimize.OPT->outfile = v55600);
      { ClaireClass * v52335 = Kernel._void;
        OID  v3395;
        { if (boolean_I_any(v52329) != CTRUE)
           v3395 = (*Optimize.c_code)(GC_OID(v45520->body),
            _oid_(Kernel._void));
          else if (Kernel._method == OWNER(v52329))
           { v52335= check_sort_method(OBJECT(method,v52329));
            v3395 = OBJECT(Generate_producer,Generate.PRODUCER->value)->body;
            }
          else if (INHERIT(OWNER(v52329),Kernel._class))
           { v52335= OBJECT(ClaireClass,v52329);
            v3395 = (*Optimize.c_code)(GC_OID(v45520->body),
              v52329);
            }
          else { v52335= Kernel._any;
              v3395 = (*Optimize.c_code)(GC_OID(v45520->body),
                _oid_(Kernel._any));
              }
            GC_OID(v3395);}
        char * v15642 = GC_STRING(string_v((*Generate.protect_result)(Generate.PRODUCER->value,
          _oid_(v52335),
          _oid_(Optimize.OPT->protection),
          v52329)));
        ClaireBoolean * v14034 = need_debug_ask_any(v52329);
        ClaireBoolean * v1640 = ((Optimize.OPT->profile_ask == CTRUE) ? (((Kernel._method == OWNER(v52329)) || 
            (v52329 == CNULL)) ? CTRUE: CFALSE): CFALSE);
        (*Generate.generate_function_start)(Generate.PRODUCER->value,
          _oid_(v45520),
          _oid_(v52335),
          v52329,
          _string_(v24332));
        if ((CL_INT)Optimize.OPT->max_vars > 0)
         { (Language._starvariable_index_star->value= ((OID)0));
          lexical_num_any2(v3395,((CL_INT)v45520->vars->length+(CL_INT)1));
          (Optimize.OPT->loop_index = Language._starvariable_index_star->value);
          }
        new_block_void();
        if (v1640 == CTRUE)
         (*Generate.generate_profile)(Generate.PRODUCER->value,
          v52329);
        if (v14034 == CTRUE)
         (*Generate.debug_intro)(Generate.PRODUCER->value,
          _oid_(v45520),
          v52329);
        (*Generate.print_body)(v3395,
          _string_(v15642),
          _oid_(v52335),
          GC_OID(v45520->body),
          _oid_(not_any(_oid_(((Optimize.OPT->protection == CTRUE) ? CTRUE : ((v1640 == CTRUE) ? CTRUE : ((v14034 == CTRUE) ? CTRUE : ((Optimize.OPT->alloc_stack == CTRUE) ? CTRUE : CFALSE))))))));
        close_block_void();
        breakline_void();
        (Optimize.OPT->alloc_stack = CFALSE);
        (Optimize._starin_c_func_star->value= Kernel.cfalse);
        (Optimize.OPT->outfile = v19787);
        use_as_output_port(v19787);
        if (Kernel._method == OWNER(v52329))
         { if (Optimize.compiler->debug_ask->memq(_oid_(OBJECT(restriction,v52329)->module_I)) == CTRUE)
           { CL_INT  v52333 = 0;
            if (OBJECT(method,v52329)->location->length != 0)
             { princ_string("\nDB_METHOD_LOCATION(DB");
              princ_string(CL_Oid(v52329));
              princ_string(",");
              print_any(GC_OID((*(OBJECT(method,v52329)->location))[2]));
              princ_string(",");
              print_any(GC_OID((*(OBJECT(method,v52329)->location))[3]));
              princ_string(",");
              print_any(GC_OID((*(OBJECT(method,v52329)->location))[4]));
              princ_string(")");
              }
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(v52319);
              bag *v52319_support;
              v52319_support = GC_OBJECT(set,set_I_bag(GC_OBJECT(list,OBJECT(list,Generate._stardebug_calls_star->value))));
              for (START(v52319_support); NEXT(v52319);)
              { GC_LOOP;
                { OID  v49620;
                  { if (INHERIT(OWNER(v52319),Language._Call_method))
                     { method * v52329 = OBJECT(Call_method,v52319)->arg;
                      if ((v52329->selector == Core.externC) && 
                          ((OBJECT(Call_method,v52319)->args->length == 2) && 
                            (INHERIT(OWNER((*(OBJECT(Call_method,v52319)->args))[2]),Kernel._class))))
                       v49620 = (*(OBJECT(Call_method,v52319)->args))[2];
                      else v49620 = _oid_(psort_any(_oid_(v52329->range)));
                        }
                    else if (INHERIT(OWNER(v52319),Language._Call))
                     { if ((OBJECT(ClaireBoolean,(*Generate.fcall_ask)(v52319))) == CTRUE)
                       v49620 = _oid_(Kernel._integer);
                      else if (Kernel._void == class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v52319)))))
                       v49620 = _oid_(Kernel._void);
                      else v49620 = _oid_(Kernel._any);
                        }
                    else v49620 = Kernel.cfalse;
                      GC_OID(v49620);}
                  ++v52333;
                  if (mod_integer(v52333,2) == 0)
                   princ_string("\t");
                  else princ_string("\n");
                    princ_string("DB_CALL_LOCATION");
                  if (v49620 == _oid_(Kernel._void))
                   princ_string("_VOID");
                  princ_string("(DB");
                  princ_string(CL_Oid(v52319));
                  princ_string(",");
                  print_any(GC_OID((*(OBJECT(bag,(*Kernel.location)(v52319))))[2]));
                  princ_string(",");
                  print_any(GC_OID((*(OBJECT(bag,(*Kernel.location)(v52319))))[3]));
                  princ_string(",");
                  print_any(GC_OID((*(OBJECT(bag,(*Kernel.location)(v52319))))[4]));
                  if (v49620 != _oid_(Kernel._void))
                   { princ_string(",");
                    (*Generate.interface_I)(Generate.PRODUCER->value,
                      v49620);
                    }
                  princ_string(")");
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            }
          }
        }
      freadwrite_port3(v55600,v19787);
      (Optimize.OPT->outfile = v19787);
      Result = _oid_(use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value)));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  print_body_If(If *v3395,char *v15642,ClaireClass *v52335,If *v42226,ClaireBoolean *v14243)
{ GC_BIND;
  if ((c_func_any(GC_OID(v3395->test)) == CTRUE) && 
      ((Optimize.OPT->protection == CTRUE) && 
        ((c_safe_any(GC_OID(v42226->arg)) == CTRUE) && 
          (Optimize.compiler->debug_ask->memq(_oid_(ClEnv->module_I)) != CTRUE))))
   { char * v26200 = ((v52335 != Kernel._void) ?
      "return " :
      "" );
    princ_string("if ");
    (*Optimize.bool_exp)(GC_OID(v3395->test),
      Kernel.ctrue,
      Core.nil->value);
    princ_string(" ");
    breakline_void();
    new_block_void();
    outer_statement_any(GC_OID(v3395->arg),v26200,v52335,v14243);
    princ_string(" ");
    close_block_void();
    princ_string("else");
    new_block_void();
    (*Generate.print_body)(GC_OID(v3395->other),
      _string_(v15642),
      _oid_(v52335),
      GC_OID(v42226->other),
      _oid_(v14243));
    close_block_void();
    }
  else print_body_any(_oid_(v3395),
      v15642,
      v52335,
      _oid_(v42226),
      v14243);
    GC_UNBIND; POP_SIGNAL;}

void  print_body_any(OID v3395,char *v15642,ClaireClass *v52335,OID v42226,ClaireBoolean *v14243)
{ (*Generate.gc_introduction)(Generate.PRODUCER->value,
    v3395);
  outer_statement_any(v3395,v15642,v52335,v14243);
  POP_SIGNAL;}

OID  print_body_Do(Do *v3395,char *v15642,ClaireClass *v52335,OID v42226,ClaireBoolean *v14243)
{ GC_BIND;
  { OID Result = 0;
    { list * v52331 = GC_OBJECT(list,v3395->args);
      CL_INT  v43591 = v52331->length;
      CL_INT  v52329 = 0;
      (*Generate.gc_introduction)(Generate.PRODUCER->value,
        _oid_(v3395));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v52340);
        Result= Kernel.cfalse;
        for (START(v52331); NEXT(v52340);)
        { ++v52329;
          if (v52329 == v43591)
           outer_statement_any(v52340,v15642,v52335,v14243);
          else inner_statement_any(v52340,_oid_(Kernel.emptySet),_oid_(Kernel.emptySet));
            }
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

void  outer_statement_any(OID v3395,char *v15642,ClaireClass *v52335,ClaireBoolean *v14243)
{ if ((c_func_any(v3395) == CTRUE) && 
      ((v14243 == CTRUE) && 
        ((v52335 != Kernel._void) && 
          (inherit_ask_class(OWNER(v3395),Language._If) != CTRUE))))
   { if (equal_string(v15642,"") != CTRUE)
     { princ_string(v15642);
      princ_string("(");
      (*Generate.expression)(v3395,
        Core.nil->value);
      princ_string(");");
      }
    else { (*Generate.expression)(v3395,
          Core.nil->value);
        princ_string(";");
        }
      }
  else if (v52335 != Kernel._void)
   { new_block_void();
    (*Generate.define_variable)(Generate.PRODUCER->value,
      _oid_(v52335),
      _string_("Result"));
    breakline_void();
    statement_any(v3395,_string_("Result"),_oid_(Kernel.emptySet));
    if (equal_string(v15642,"") != CTRUE)
     { princ_string(v15642);
      princ_string("(Result);");
      close_block_void();
      }
    }
  else { statement_any(v3395,_oid_(Kernel.emptySet),_oid_(Kernel.emptySet));
      princ_string(v15642);
      }
    POP_SIGNAL;}

ClaireBoolean * c_safe_any(OID v52340)
{ POP_SIGNAL; return (not_any(_oid_(((Optimize.OPT->allocation == CTRUE) ? ((BCONTAIN(c_status_any(v52340,Kernel.nil),(OID)(1))) ? CTRUE: CFALSE): CFALSE))));}

ClaireClass * check_sort_method(method *v45520)
{ GC_BIND;
  { ClaireClass *Result ;
    { ClaireType * v49570 = v45520->range;
      OID  v52318 = GC_OID(OBJECT(Generate_producer,Generate.PRODUCER->value)->body);
      ClaireType * v49571 = GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v52318))));
      ClaireClass * v52335 = psort_any(_oid_(v49570));
      (OBJECT(Generate_producer,Generate.PRODUCER->value)->body = c_strict_code_any(v52318,v52335));
      if (should_trace_ask_module1(Generate.it,5) == CTRUE)
       mtformat_module1(Generate.it,"`GREEN ---- note: ~S's range was found to be ~S (vs. ~S) \n",5,list::alloc(3,_oid_(v45520),
        _oid_(v49571),
        _oid_(v49570)));
      else ;if (_inf_equal_type(v49571,v49570) != CTRUE)
       { if (should_trace_ask_module1(Generate.it,2) == CTRUE)
         mtformat_module1(Generate.it,"`GREEN ---- note: ~S's range was found to be ~S (vs. ~S) \n",2,list::alloc(3,_oid_(v45520),
          _oid_(v49571),
          _oid_(v49570)));
        else ;if (Generate.WrongMethod->value == ((OID)0))
         { (Generate.WrongMethod->value= v52318);
          close_exception(((general_error *) (*Core._general_error)(_string_("You can look at WrongMethod"),
            _oid_(Kernel.nil))));
          }
        if (((CL_INT)Optimize.compiler->safety < 2) || 
            (((CL_INT)Optimize.compiler->safety < 4) && 
                (boolean_I_any(sort_equal_class(osort_any(_oid_(v49571)),v52335)) != CTRUE)))
         (OBJECT(Generate_producer,Generate.PRODUCER->value)->body = c_strict_code_any(GC_OID(c_check_any(GC_OID((*Optimize.c_code)(v52318,
          _oid_(Kernel._any))),GC_OID((*Optimize.c_code)(_oid_(v49570),
          _oid_(Kernel._type))))),v52335));
        if (boolean_I_any(sort_equal_class(osort_any(_oid_(v49571)),v52335)) != CTRUE)
         { if ((v52335 != Kernel._void) && 
              ((_oid_((INHERIT(v49571->isa,Kernel._class) ?
                 (ClaireObject *) sort_I_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v49571))) : 
                 (ClaireObject *)  sort_I_type((ClaireType *) OBJECT(ClaireType,_oid_(v49571))))) == _oid_(Kernel._void)) || 
                  (inherit_ask_class(v52335,OBJECT(ClaireClass,_oid_((INHERIT(v49571->isa,Kernel._class) ?
                   (ClaireObject *) sort_I_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v49571))) : 
                   (ClaireObject *)  sort_I_type((ClaireType *) OBJECT(ClaireType,_oid_(v49571))))))) != CTRUE)))
           (*Optimize.Cerror)(_string_("[218] Sort error: Cannot compile ~S."),
            _oid_(v45520));
          }
        }
      { ClaireType * v49572 = GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel._exp)(_oid_(v49570),
          _oid_(v49571))));
        if (((CL_INT)Optimize.compiler->safety > 1) && 
            (osort_any(_oid_(v49572)) == v52335))
         { (OBJECT(Generate_producer,Generate.PRODUCER->value)->body = (*Optimize.c_strict_check)(GC_OID(OBJECT(Generate_producer,Generate.PRODUCER->value)->body),
            _oid_(class_I_type(v49572))));
          ;}
        }
      if (INHERIT(v49570->isa,Kernel._tuple))
       { if (should_trace_ask_module1(Generate.it,3) == CTRUE)
         mtformat_module1(Generate.it,"`GREEN --- note: ~S is a method with range <= tuple => use stack allocation \n",3,list::alloc(1,_oid_(v45520)));
        else ;(Optimize.OPT->alloc_stack = CTRUE);
        }
      if ((Optimize.OPT->allocation == CTRUE) && 
          (nth_integer(status_I_restriction(v45520),(OID)(6)) != CTRUE))
       { if (nth_integer(status_I_restriction(v45520),(OID)(1)) != CTRUE)
         { if (should_trace_ask_module1(Generate.it,3) == CTRUE)
           mtformat_module1(Generate.it,"`GREEN ---- note: ~S may provoke an allocation \n",3,list::alloc(1,_oid_(v45520)));
          else ;}
        }
      else { (Optimize.OPT->loop_gc = CFALSE);
          (Optimize.OPT->protection = CFALSE);
          }
        Result = psort_any(_oid_(v45520->range));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }

OID  typed_args_list_list(list *v45520)
{ { OID Result = 0;
    { ClaireBoolean * v4486 = CTRUE;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v52340);
        Result= Kernel.cfalse;
        for (START(v45520); NEXT(v52340);)
        { if (v4486 == CTRUE)
           v4486= CFALSE;
          else princ_string(",");
            (*Generate.interface_I)(Generate.PRODUCER->value,
            _oid_(sort_Variable(OBJECT(Variable,v52340))));
          (*Language.ident)(Generate.PRODUCER->value,
            v52340);
          }
        }
      }
    POP_SIGNAL; return (Result);}
  }

ClaireBoolean * need_debug_ask_any(OID v52329)
{ { ClaireBoolean *Result ;
    if (Kernel._method == OWNER(v52329))
     { property * v52332 = OBJECT(restriction,v52329)->selector;
      Result = ((Optimize.compiler->debug_ask->memq(_oid_(OBJECT(restriction,v52329)->module_I)) == CTRUE) ? 
      ((domain_I_restriction(OBJECT(restriction,v52329)) != Kernel._environment) ? 
      ((contain_ask_list(OBJECT(list,Reader.NO_DEBUG_METHOD->value),v52329) != CTRUE) ? 
      ((OBJECT(restriction,v52329)->module_I != claire.it) ? 
      ((v52332 != Core.self_eval) ? 
      ((v52332 != Core.execute) ? 
      ((v52332 != Core.eval_message) ? 
      ((v52332 != Core.push_debug) ? 
      ((v52332 != Core.pop_debug) ? 
      ((v52332 != Kernel.find_which) ? 
      ((v52332 != Core.matching_ask) ? 
      ((v52332 != Core.vmatch_ask) ? 
      CTRUE: CFALSE): CFALSE): CFALSE): CFALSE): CFALSE): CFALSE): CFALSE): CFALSE): CFALSE): CFALSE): CFALSE): CFALSE);
      }
    else Result = CFALSE;
      POP_SIGNAL; return (Result);}
  }

void  get_dependents_method(method *v52329)
{ GC_BIND;
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(v52332);
    bag *v52332_support;
    v52332_support = GC_OBJECT(set,dependents_method(v52329));
    for (START(v52332_support); NEXT(v52332);)
    { property * v29482 = v52329->selector;
      add_table(Reader.PRdependent,_oid_(v29482),v52332);
      }
    }
  GC_UNBIND; POP_SIGNAL;}

void  c_princ_function(ClaireFunction *v45520)
{ c_princ_string(string_I_function(v45520));
  POP_SIGNAL;}

void  set_outfile_lambda(lambda *v45520)
{ GC_BIND;
  { module * v52329 = ClEnv->module_I;
    char * v49133 = string_I_symbol(v52329->name);
    PortObject * v52332 = GC_OBJECT(PortObject,Optimize.OPT->outfile);
    OID  v14721;
    { if (v45520->vars->length != 0)
       v14721 = (*Kernel.range)(GC_OID((*(v45520->vars))[1]));
      else v14721 = CNULL;
        GC_OID(v14721);}
    if (v14721 != CNULL)
     { { ClaireBoolean * g1800I;
        { OID  v14763;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v52319);
            v14763= Kernel.cfalse;
            bag *v52319_support;
            v52319_support = GC_OBJECT(list,Optimize.OPT->objects);
            for (START(v52319_support); NEXT(v52319);)
            if ((INHERIT(OWNER(v52319),Kernel._class)) && 
                (equal(v52319,v14721) == CTRUE))
             { v14763 = Kernel.ctrue;
              ClEnv->cHandle = loop_handle;break;}
            }
          g1800I = boolean_I_any(v14763);
          }
        
        if (g1800I == CTRUE) v49133= GC_STRING(string_v((*Generate.c_string)(Generate.PRODUCER->value,
            _oid_(OBJECT(ClaireClass,v14721)->name))));
          }
      if (equal_string(v49133,string_I_symbol(ClEnv->module_I->name)) != CTRUE)
       v52332= GC_OBJECT(buffer,fopen_string1(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),v49133)),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),"a"));
      (Optimize.OPT->outfile = v52332);
      }
    ;}
  GC_UNBIND; POP_SIGNAL;}



