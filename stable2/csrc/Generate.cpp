/***** CLAIRE Compilation of file ./compile/gsystem.cl 
         [version 3.5.0 / safety 5] *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>
#include <Optimize.h>

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllexport)
#endif
#include <Generate.h>

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllimport)
#endif

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllexport)
#endif
CL_EXPORT void  ident_symbol(symbol *v46356) { 
    (*Language.ident)(Generate.PRODUCER->value,
      _oid_(v46356));
    POP_SIGNAL;}
  

CL_EXPORT void  ident_thing(thing *v46356) { 
    (*Language.ident)(Generate.PRODUCER->value,
      _oid_(v46356->name));
    POP_SIGNAL;}
  

CL_EXPORT void  ident_class(ClaireClass *v46356) { 
    (*Language.ident)(Generate.PRODUCER->value,
      _oid_(v46356->name));
    POP_SIGNAL;}
  

CL_EXPORT void  interface_I_class(ClaireClass *v12187) { 
    (*Generate.interface_I)(Generate.PRODUCER->value,
      _oid_(v12187));
    POP_SIGNAL;}
  

CL_EXPORT void  class_princ_class(ClaireClass *v12187) { 
    (*Generate.class_princ)(Generate.PRODUCER->value,
      _oid_(v12187));
    POP_SIGNAL;}
  

CL_EXPORT OID  indent_c_void() { 
    { OID Result = 0;
      { CL_INT  v12208 = Optimize.OPT->level;
        { CL_INT loop_handle = ClEnv->cHandle;
          Result= _oid_(CFALSE);
          while (((CL_INT)v12208 > (CL_INT)0))
          { princ_string(((char*)"  "));
            v12208= (CL_INT)(((CL_INT)v12208-(CL_INT)1));
            POP_SIGNAL;}
          }
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  breakline_void() { 
    princ_string(((char*)"\n"));
    POP_SIGNAL; return (indent_c_void());}
  

CL_EXPORT void  new_block_void() { 
    _void_(Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
    princ_string(((char*)"{ "));
    POP_SIGNAL;}
  

CL_EXPORT void  close_block_void() { 
    _void_(Optimize.OPT->level = ((CL_INT)Optimize.OPT->level-(CL_INT)1));
    princ_string(((char*)"}"));
    breakline_void();
    POP_SIGNAL;}
  

CL_EXPORT void  c_test_any(OID v12208) { 
    
    GC_BIND;
    { OID  v12204 = GC_OID((*Optimize.c_type)(v12208));
      ClaireClass * v12203 = osort_any(v12204);
      OID  v12205 = GC_OID((*Optimize.c_code)(v12208,
        _oid_(v12203)));
      ClaireBoolean * v12190 = c_func_any(v12205);
      princ_string(((char*)"type -> "));
      print_any(v12204);
      princ_string(((char*)" [sort "));
      print_any(_oid_(v12203));
      princ_string(((char*)"]\n"));
      princ_string(((char*)"opt["));
      print_any(_oid_(OWNER(v12205)));
      princ_string(((char*)"] -> "));
      print_any(v12205);
      princ_string(((char*)" \n"));
      if (v12190 == CTRUE)
       { princ_string(((char*)"exp  -> "));
        (*Generate.expression)(v12205,
          Core.nil->value);
        princ_string(((char*)"\n"));
        }
      else { princ_string(((char*)"stat -> "));
          statement_any(v12205,_string_(((char*)"result")),Core.nil->value);
          princ_string(((char*)"\n"));
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  c_test_method(method *v12197) { 
    
    GC_BIND;
    { lambda * v12196 = GC_OBJECT(lambda,v12197->formula);
      if (v12196 == (NULL))
       ;else { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
           mtformat_module1(Generate.it,((char*)"---- Compiling ~S ---- \n"),0,list::alloc(1,_oid_(v12197)));
          else ;_void_(Optimize.OPT->in_method = _oid_(v12197));
          _void_(Optimize.OPT->protection = CFALSE);
          _void_(Optimize.OPT->allocation = CFALSE);
          _void_(Optimize.OPT->loop_index = 0);
          _void_(Optimize.OPT->loop_gc = CFALSE);
          _void_(Optimize.OPT->use_update = CFALSE);
          _void_(Optimize.OPT->use_nth_equal = CFALSE);
          _void_(Optimize.OPT->max_vars = 0);
          _void_(Optimize.OPT->online_ask = CFALSE);
          _void_(Optimize.OPT->legal_modules = ((set *) Kernel._module->instances));
          _void_(OBJECT(Generate_producer,Generate.PRODUCER->value)->body = v12196->body);
          { ClaireClass * v12203 = Kernel._void;
            OID  v29311;
            { { v12203= (check_sort_method(v12197));
                v29311 = OBJECT(Generate_producer,Generate.PRODUCER->value)->body;
                }
              GC_OID(v29311);}
            char * v16478 = GC_STRING(string_v((*Generate.protect_result)(Generate.PRODUCER->value,
              _oid_(v12203),
              _oid_(Optimize.OPT->protection),
              _oid_(v12197))));
            princ_string(((char*)"Opt => "));
            print_any(v29311);
            princ_string(((char*)" \n\n"));
            new_block_void();
            (*Generate.print_body)(v29311,
              _string_(v16478),
              _oid_(v12203),
              GC_OID(v12196->body),
              Kernel.ctrue);
            close_block_void();
            }
          _void_(Optimize.OPT->in_method = CNULL);
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  compile_module(module *v46356) { 
    
    GC_BIND;
    _void_(Optimize.OPT->need_modules = Kernel.emptySet);
    _void_(OBJECT(Generate_producer,Generate.PRODUCER->value)->stat = 0);
    { bag * v50445 = GC_OBJECT(list,parents_list(GC_OBJECT(list,add_modules_list(list::alloc(1,_oid_(v46356))))));
      list * v50387 = GC_OBJECT(list,Optimize.compiler->headers);
      { Optimize_meta_compiler * v21924 = Optimize.compiler; 
        list * v21925;
        { list * v26982;
          { list * v46655 = list::empty(Kernel._string);
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(v12208);
              bag *v12208_support;
              v12208_support = GC_OBJECT(list,v46356->made_of);
              for (START(v12208_support); NEXT(v12208);)
              if (match_wildcard_ask_string(string_v(v12208),((char*)"*.h*")) == CTRUE)
               v46655->addFast((OID)v12208);
              }
            v26982 = GC_OBJECT(list,v46655);
            }
          v21925 = append_list(GC_OBJECT(list,Optimize.compiler->headers),v26982);
          }
        _void_(v21924->headers = v21925);}
      update_property(Optimize.legal_modules,
        Optimize.OPT,
        9,
        Kernel._object,
        GC_OID((*Kernel.set_I)(_oid_(v50445))));
      if (Optimize.compiler->class2file_ask == CTRUE)
       { if (should_trace_ask_module1(Generate.it,2) == CTRUE)
         mtformat_module1(Generate.it,((char*)"**** Compiling the module ~A [v. 3.~A - verbose:~A opt:~S] \n"),2,GC_OBJECT(list,list::alloc(4,_string_(string_I_symbol(v46356->name)),
          GC_OID(Optimize.compiler->version),
          ((OID)ClEnv->verbose),
          _oid_(Optimize.compiler->optimize_ask))));
        else ;write_property(Generate.outmodule,Optimize.OPT,GC_OID(_oid_(fopen_string1(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),GC_STRING(string_v((*Generate.c_string)(Generate.PRODUCER->value,
          _oid_(v46356->name)))))),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),((char*)"w")))));
        generate_files_module(v46356);
        begin_module(v46356);
        generate_classes_module(v46356);
        generate_c2f_module(v46356);
        end_module(v46356);
        }
      else { if (should_trace_ask_module1(Generate.it,5) == CTRUE)
           mtformat_module1(Generate.it,((char*)"call generate_files ~S  \n"),5,GC_OBJECT(list,list::alloc(1,_oid_(v46356))));
          else ;if (isfile_ask_string(append_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->source),external_I_module1(v46356))),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))) == CTRUE)
           unlink_string(append_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->source),external_I_module1(v46356))),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension)));
          generate_files_module(v46356);
          generate_f2f_module(v46356);
          generate_interface_module(v46356,GC_OBJECT(set,Optimize.OPT->legal_modules));
          }
        _void_(Optimize.compiler->headers = v50387);
      v50445= (GC_OBJECT(set,difference_set(GC_OBJECT(set,set_I_set(Optimize.OPT->need_modules)),GC_OBJECT(set,Optimize.OPT->legal_modules))));
      if (should_trace_ask_module1(Generate.it,1) == CTRUE)
       mtformat_module1(Generate.it,((char*)"++++ v3.3.32 info: ~A GC protection inserted in ~S. \n"),1,GC_OBJECT(list,list::alloc(2,((OID)OBJECT(Generate_producer,Generate.PRODUCER->value)->stat),_oid_(v46356))));
      else ;if (v50445->length != 0)
       { if (should_trace_ask_module1(Generate.it,2) == CTRUE)
         mtformat_module1(Generate.it,((char*)"---- WARNING: ~S should be declared for ~S\n"),2,GC_OBJECT(list,list::alloc(2,_oid_(v50445),_oid_(v46356))));
        else ;}
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  generate_files_module(module *v46356) { 
    
    GC_RESERVE(3);  // v3.3.39 optim !
    if (should_trace_ask_module1(Generate.it,0) == CTRUE)
     mtformat_module1(Generate.it,((char*)"==== Generate ~A files for module ~S [verbose = ~A, Opt? = ~S] \n"),0,list::alloc(4,GC_OID(_string_(OBJECT(Generate_producer,Generate.PRODUCER->value)->comment)),
      _oid_(v46356),
      ((OID)ClEnv->verbose),
      _oid_(Optimize.compiler->optimize_ask)));
    else ;_void_(Optimize.OPT->instructions = list::empty(Kernel._any));
    _void_(Optimize.OPT->properties = set::empty(Kernel._property));
    _void_(Optimize.OPT->objects = list::empty(Kernel._object));
    _void_(Optimize.OPT->functions = list::empty(Kernel._any));
    _void_(Optimize.OPT->need_to_close = set::empty(Kernel._any));
    (*Generate.start_module_interface)(Generate.PRODUCER->value,
      _oid_(v46356));
    begin_module(v46356);
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v12208);
      bag *v12208_support;
      v12208_support = GC_OBJECT(list,entries_string2(GC_STRING(v46356->source)));
      for (START(v12208_support); NEXT(v12208);)
      { GC_LOOP;
        if ((match_wildcard_ask_string(string_v(v12208),((char*)"*.o")) == CTRUE) || 
            (match_wildcard_ask_string(string_v(v12208),((char*)"*.obj")) == CTRUE))
         { if (isfile_ask_string(append_string(GC_STRING(append_string(GC_STRING(v46356->source),GC_STRING(string_v(Core._starfs_star->value)))),string_v(v12208))) == CTRUE)
           { if (should_trace_ask_module1(Generate.it,3) == CTRUE)
             mtformat_module1(Generate.it,((char*)"++++ Unlink file ~A \n"),3,GC_OBJECT(list,list::alloc(1,v12208)));
            else ;unlink_string(append_string(GC_STRING(append_string(GC_STRING(v46356->source),GC_STRING(string_v(Core._starfs_star->value)))),string_v(v12208)));
            }
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v12208);
      bag *v12208_support;
      v12208_support = GC_OBJECT(list,entries_string2(GC_STRING(Optimize.compiler->source)));
      for (START(v12208_support); NEXT(v12208);)
      { GC_LOOP;
        if ((match_wildcard_ask_string(string_v(v12208),((char*)"*.o")) == CTRUE) || 
            (match_wildcard_ask_string(string_v(v12208),((char*)"*.obj")) == CTRUE))
         { if (isfile_ask_string(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),string_v(v12208))) == CTRUE)
           { if (should_trace_ask_module1(Generate.it,3) == CTRUE)
             mtformat_module1(Generate.it,((char*)"++++ Unlink file ~A \n"),3,GC_OBJECT(list,list::alloc(1,v12208)));
            else ;unlink_string(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),string_v(v12208)));
            }
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v12208);
      bag *v12208_support;
      v12208_support = GC_OBJECT(list,v46356->made_of);
      for (START(v12208_support); NEXT(v12208);)
      { GC_LOOP;
        if ((match_wildcard_ask_string(string_v(v12208),((char*)"*.cl")) == CTRUE) || 
            (match_wildcard_ask_string(string_v(v12208),((char*)"*.*")) != CTRUE))
         { GC__OID(v12208 = _string_(replace_string(string_v(v12208),((char*)".cl"),((char*)""))), 1);
          if (equal(v12208,_string_(string_I_symbol(v46356->name))) == CTRUE)
           (*Optimize.Cerror)(_string_(((char*)"[211] ~S cannot be used both as a file and module name")),
            v12208);
          generate_file_string2(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(v46356->source),GC_STRING(string_v(Core._starfs_star->value)))),string_v(v12208))),GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),external_I_module1(v46356))));
          }
        else if (match_wildcard_ask_string(string_v(v12208),((char*)"*.cpp")) == CTRUE)
         { _void_(Optimize.OPT->outfile = fopen_string1(GC_STRING(append_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->source),external_I_module1(v46356))),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),((char*)"a")));
          start_file_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->source),external_I_module1(v46356))),v46356);
          { buffer * v12190 = GC_OBJECT(buffer,fopen_string1(GC_STRING(_7_string(GC_STRING(v46356->source),string_v(v12208))),((char*)"r")));
            freadwrite_port3(v12190,GC_OBJECT(PortObject,Optimize.OPT->outfile));
            fclose_port1(v12190);
            }
          fclose_port1(GC_OBJECT(PortObject,Optimize.OPT->outfile));
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    { buffer * v12200 = GC_OBJECT(buffer,fopen_string1(GC_STRING(append_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->source),external_I_module1(v46356))),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),((char*)"a")));
      PortObject * v61279 = use_as_output_port(v12200);
      create_dynload_module_module1(v46356);
      use_as_output_port(v61279);
      fclose_port1(v12200);
      }
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v12208);
      bag *v12208_support;
      v12208_support = GC_OBJECT(list,v46356->made_of);
      for (START(v12208_support); NEXT(v12208);)
      { GC_LOOP;
        if (match_wildcard_ask_string(string_v(v12208),((char*)"*@PATH_INFO@*")) == CTRUE)
         { list * v12204 = GC_OBJECT(list,explode_string(string_v(v12208),((char*)"@PATH_INFO@")));
          char * v43817 = GC_STRING(replace_string(string_v((*(v12204))[1]),GC_STRING(string_v(Core._starfs_star->value)),((char*)"-")));
          if (equal_string(left_string(v43817,2),((char*)"./")) == CTRUE)
           GC__STRING(v43817 = substring_string(v43817,3,LENGTH_STRING(v43817)), 2);
          if (equal_string(left_string(v43817,1),((char*)".")) == CTRUE)
           GC__STRING(v43817 = substring_string(v43817,2,LENGTH_STRING(v43817)), 3);
          if (equal_string(v43817,string_I_symbol(v46356->name)) == CTRUE)
           (*Optimize.Cerror)(_string_(((char*)"[211] ~S cannot be used both as a file and module name")),
            _string_(v43817));
          generate_wcl_file_string(string_v((*(v12204))[1]),string_v(v12208),GC_STRING(_7_string(GC_STRING(Optimize.compiler->source),external_I_module1(v46356))));
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    end_module(v46356);
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  generate_f2f_module(module *v12197) { 
    
    GC_BIND;
    { buffer * v12200 = GC_OBJECT(buffer,fopen_string1(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),string_I_symbol(v12197->name))),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),((char*)"a")));
      if (should_trace_ask_module1(Generate.it,0) == CTRUE)
       mtformat_module1(Generate.it,((char*)"==== generate file for module ~S ==== \n"),0,list::alloc(1,_oid_(v12197)));
      else ;_void_(Optimize.OPT->outfile = v12200);
      generate_file_string1(string_I_symbol(v12197->name),v12197);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  generate_file_string1(char *v12203,module *v12197) { 
    
    GC_BIND;
    start_file_string(v12203,v12197);
    use_as_output_port(Optimize.OPT->outfile);
    (*Generate.generate_classes)(Generate.PRODUCER->value,
      _string_(v12203),
      _oid_(v12197));
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v12187);
      bag *v12187_support;
      v12187_support = GC_OBJECT(list,Optimize.OPT->objects);
      for (START(v12187_support); NEXT(v12187);)
      if (INHERIT(OWNER(v12187),Kernel._class))
       (*Generate.methods_bodies)(Generate.PRODUCER->value,
        v12187);
      }
    generate_meta_load_module(v12197);
    breakline_void();
    close_block_void();
    breakline_void();
    fclose_port1(GC_OBJECT(PortObject,Optimize.OPT->outfile));
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  generate_classes_module(module *v46356) { 
    
    GC_BIND;
    erase_table(Generate.classFile);
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v12187);
      bag *v12187_support;
      v12187_support = GC_OBJECT(list,Optimize.OPT->objects);
      for (START(v12187_support); NEXT(v12187);)
      { GC_LOOP;
        if (INHERIT(OWNER(v12187),Kernel._class))
         { put_table(Generate.classFile,v12187,_oid_(fopen_string1(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),GC_STRING(string_v((*Generate.c_string)(Generate.PRODUCER->value,
            GC_OID((*Kernel.name)(v12187))))))),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),((char*)"w"))));
          use_as_output_port(OBJECT(PortObject,nth_table1(Generate.classFile,v12187)));
          if (should_trace_ask_module1(Generate.it,2) == CTRUE)
           mtformat_module1(Generate.it,((char*)"++++ Creating the file ~A.java\n"),2,GC_OBJECT(list,list::alloc(1,GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
            GC_OID((*Kernel.name)(v12187)))))));
          else ;_void_(Optimize.OPT->level = 0);
          princ_string(((char*)"// class file for "));
          print_any(v12187);
          princ_string(((char*)" in module "));
          print_any(_oid_(v46356));
          princ_string(((char*)" "));
          breakline_void();
          breakline_void();
          breakline_void();
          princ_string(((char*)"public class "));
          ident_symbol(OBJECT(symbol,(*Kernel.name)(v12187)));
          princ_string(((char*)" extends "));
          ident_symbol(OBJECT(symbol,(*Kernel.name)(GC_OID((*Kernel.superclass)(v12187)))));
          new_block_void();
          breakline_void();
          breakline_void();
          princ_string(((char*)"/* empty constructor by default */"));
          breakline_void();
          princ_string(((char*)"public "));
          ident_symbol(OBJECT(symbol,(*Kernel.name)(v12187)));
          princ_string(((char*)"() {}"));
          breakline_void();
          breakline_void();
          breakline_void();
          princ_string(((char*)"/* declaration of fields */"));
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(v12209);
            bag *v12209_support;
            v12209_support = GC_OBJECT(list,OBJECT(bag,(*Optimize.get_indexed)(v12187)));
            for (START(v12209_support); NEXT(v12209);)
            if (_oid_(domain_I_restriction(OBJECT(restriction,v12209))) == v12187)
             { breakline_void();
              princ_string(((char*)"public  "));
              interface_I_class(psort_any(_oid_(OBJECT(restriction,v12209)->range)));
              princ_string(((char*)" "));
              ident_symbol(OBJECT(restriction,v12209)->selector->name);
              princ_string(((char*)";"));
              }
            }
          breakline_void();
          fclose_port1(OBJECT(PortObject,nth_table1(Generate.classFile,v12187)));
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  generate_c2f_module(module *v46356) { 
    
    GC_BIND;
    { buffer * v3285 = GC_OBJECT(buffer,fopen_string1(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),GC_STRING(string_v((*Generate.c_string)(Generate.PRODUCER->value,
        _oid_(v46356->name)))))),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),((char*)"a")));
      _void_(Optimize.OPT->outfile = v3285);
      use_as_output_port(v3285);
      (*Generate.generate_start_file)(Generate.PRODUCER->value,
        _oid_(v46356));
      putc_char1(_char_(((char*)"\n")[1 - 1]),v3285);
      fclose_port1(v3285);
      generate_functions_module(v46356);
      v3285= (GC_OBJECT(buffer,fopen_string1(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),GC_STRING(string_v((*Generate.c_string)(Generate.PRODUCER->value,
        _oid_(v46356->name)))))),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),((char*)"a"))));
      use_as_output_port(v3285);
      _void_(Optimize.OPT->outfile = v3285);
      _void_(Optimize.OPT->level = 2);
      generate_objects_module(v46356);
      generate_meta_load_module(v46356);
      (*Generate.generate_end_file)(Generate.PRODUCER->value,
        _oid_(v46356));
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  generate_interface_module(module *v46356,bag *v12196) { 
    
    GC_BIND;
    if (should_trace_ask_module1(Generate.it,0) == CTRUE)
     mtformat_module1(Generate.it,((char*)"==== Generate interface (.h) files for module ~S \n"),0,list::alloc(1,_oid_(v46356)));
    else ;use_as_output_port(Optimize.OPT->cinterface);
    breakline_void();
    (*Generate.generate_interface)(Generate.PRODUCER->value,
      _oid_(v46356));
    (*Generate.namespace_I)(Generate.PRODUCER->value,
      _oid_(v46356));
    generate_objects_module(v46356);
    (*Kernel.module_I)(Generate.PRODUCER->value,
      _oid_(v46356));
    (*Generate.end_module_interface)(Generate.PRODUCER->value,
      _oid_(v46356));
    putc_char1(_char_(((char*)"\n")[1 - 1]),GC_OBJECT(PortObject,Optimize.OPT->cinterface));
    fclose_port1(GC_OBJECT(PortObject,Optimize.OPT->cinterface));
    use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value));
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  generate_objects_module(module *v46356) { 
    
    GC_BIND;
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v12208);
      bag *v12208_support;
      v12208_support = GC_OBJECT(list,Optimize.OPT->objects);
      for (START(v12208_support); NEXT(v12208);)
      { breakline_void();
        (*Generate.public_static)(Generate.PRODUCER->value);
        if (INHERIT(OWNER(v12208),Core._global_variable))
         { { OID  v27943;
            if (nativeVar_ask_global_variable(OBJECT(global_variable,v12208)) == CTRUE)
             v27943 = _oid_(getRange_global_variable(OBJECT(global_variable,v12208)));
            else v27943 = _oid_(Core._global_variable);
              (*Generate.interface_I)(Generate.PRODUCER->value,
              v27943);
            }
          princ_string(((char*)" "));
          ident_symbol(OBJECT(thing,v12208)->name);
          princ_string(((char*)";"));
          }
        else { (*Generate.interface_I)(Generate.PRODUCER->value,
              _oid_(psort_any(_oid_(OWNER(v12208)))));
            princ_string(((char*)" "));
            if (INHERIT(OWNER(v12208),Kernel._class))
             { princ_string(((char*)"_"));
              c_princ_string(string_I_symbol(OBJECT(symbol,(*Kernel.name)(v12208))));
              }
            else if (INHERIT(OWNER(v12208),Reader._reserved_keyword))
             { princ_string(((char*)"_cl_"));
              c_princ_string(string_I_symbol(OBJECT(symbol,(*Kernel.name)(v12208))));
              }
            else ident_symbol(OBJECT(symbol,(*Kernel.name)(v12208)));
              princ_string(((char*)";"));
            }
          }
      }
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v12208);
      bag *v12208_support;
      v12208_support = GC_OBJECT(set,Optimize.OPT->properties);
      for (START(v12208_support); NEXT(v12208);)
      { GC_LOOP;
        if (Optimize.OPT->objects->memq(v12208) != CTRUE)
         { { OID  v13596;
            { { OID  v52873 = CNULL;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(v50570);
                  bag *v50570_support;
                  v50570_support = GC_OBJECT(set,Optimize.OPT->properties);
                  for (START(v50570_support); NEXT(v50570);)
                  { GC_LOOP;
                    if (v50570 != v12208)
                     { if (equal_string(string_I_symbol(OBJECT(thing,v50570)->name),string_I_symbol(OBJECT(thing,v12208)->name)) == CTRUE)
                       { v52873= (v50570);
                        GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                      }
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                v13596 = v52873;
                }
              GC_OID(v13596);}
            if (v13596 != CNULL)
             { property * v50570 = OBJECT(property,v13596);
              close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[217] ~S and ~S cannot be defined in the same module")),
                _oid_(list::alloc(2,_oid_(v50570),v12208)))));
              }
            else ;}
          princ_string(((char*)"\n"));
          (*Generate.public_static)(Generate.PRODUCER->value);
          (*Generate.interface_I)(Generate.PRODUCER->value,
            _oid_(psort_any(_oid_(OWNER(v12208)))));
          princ_string(((char*)" "));
          ident_symbol(OBJECT(thing,v12208)->name);
          princ_string(((char*)";// "));
          print_any(_oid_(OBJECT(thing,v12208)->name));
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  generate_meta_load_module(module *v46356) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    princ_string(((char*)"// definition of the meta-model for "));
    print_any(_oid_(v46356));
    breakline_void();
    (*Generate.generate_meta_load)(Generate.PRODUCER->value,
      _oid_(v46356));
    princ_string(((char*)"// definition of the properties "));
    breakline_void();
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v12208);
      bag *v12208_support;
      v12208_support = GC_OBJECT(set,Optimize.OPT->properties);
      for (START(v12208_support); NEXT(v12208);)
      if (Optimize.OPT->objects->memq(v12208) != CTRUE)
       (*Generate.declare)(Generate.PRODUCER->value,
        v12208);
      }
    breakline_void();
    breakline_void();
    princ_string(((char*)"// instructions from module sources "));
    breakline_void();
    { OID  v12194 = CNULL;
      ClaireBoolean * v58751 = CFALSE;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v12193);
        bag *v12193_support;
        v12193_support = GC_OBJECT(list,Optimize.OPT->instructions);
        for (START(v12193_support); NEXT(v12193);)
        { GC_LOOP;
          { breakline_void();
            if (Kernel._string == OWNER(v12193))
             { if (equal(_oid_(Kernel._string),_oid_(OWNER(v12194))) != CTRUE)
               breakline_void();
              princ_string(((char*)"/* "));
              (*Kernel.princ)(v12193);
              princ_string(((char*)" */"));
              }
            else if (global_var_def_ask_any(v12193) == CTRUE)
             { if (v58751 == CTRUE)
               { princ_string(((char*)"GC_UNBIND;\n"));
                v58751= (CFALSE);
                }
              (*Generate.global_var_def_I)(Generate.PRODUCER->value,
                _oid_(v46356),
                v12193);
              }
            else { if (v58751 != CTRUE)
                 { princ_string(((char*)"GC_BIND;\n"));
                  v58751= (CTRUE);
                  }
                _void_(Optimize.OPT->protection = CTRUE);
                statement_any(v12193,_oid_(Kernel.emptySet),_oid_(Kernel.emptySet));
                }
              GC__OID(v12194 = v12193, 1);
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      if (v58751 == CTRUE)
       princ_string(((char*)"GC_UNBIND;\n"));
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT ClaireBoolean * global_var_def_ask_any(OID v12208) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = ((INHERIT(OWNER(v12208),Language._Let)) ?
        ((INHERIT(OWNER(OBJECT(Let,v12208)->value),Language._Call)) ? (((*Kernel.selector)(OBJECT(Let,v12208)->value) == _oid_(Optimize.object_I)) ? (((*(OBJECT(bag,(*Core.args)(OBJECT(Let,v12208)->value))))[2] == _oid_(Core._global_variable)) ? CTRUE: CFALSE): CFALSE): CFALSE) :
        CFALSE );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireClass * getRange_global_variable(global_variable *v12208) { 
    { ClaireClass *Result ;
      Result = ((equal(_oid_(v12208->range),_oid_(Kernel.emptySet)) == CTRUE) ?
        OWNER(v12208->value) :
        class_I_type(v12208->range) );
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  generate_functions_module(module *v46356) { 
    
    GC_BIND;
    princ_string(((char*)"// definition of class methods "));
    { PortObject * v12200 = GC_OBJECT(PortObject,Optimize.OPT->outfile);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v12190);
        bag *v12190_support;
        v12190_support = GC_OBJECT(list,Optimize.OPT->functions);
        for (START(v12190_support); NEXT(v12190);)
        { GC_LOOP;
          { _void_(Optimize.OPT->level = 2);
            _void_(Optimize.OPT->outfile = v12200);
            print_c_function_lambda2(GC_OBJECT(lambda,OBJECT(lambda,(*Kernel.nth)(v12190,
              ((OID)1)))),GC_STRING(string_v((*Kernel.nth)(v12190,
              ((OID)2)))),GC_OID((*Kernel.nth)(v12190,
              ((OID)3))));
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT list * parents_module(module *v46356,list *v12196) { 
    if (v12196->memq(_oid_(v46356)) == CTRUE) 
    { { list *Result ;
        Result = v12196;
        return (Result);}
       }
    else{ 
      GC_BIND;
      if (((v46356->part_of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       v12196= (GC_OBJECT(list,parents_module(v46356->part_of,v12196)));
      v12196= (GC_OBJECT(list,v12196->addFast((OID)_oid_(v46356))));
      { list *Result ;
        Result = v12196;
        GC_UNBIND; POP_SIGNAL; return (Result);}
      }
    }
  

CL_EXPORT list * parents_list(list *v46356) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { list *Result ;
      { list * v12196 = list::empty(Kernel._module);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v12208);
          for (START(v46356); NEXT(v12208);)
          { GC_LOOP;
            GC__ANY(v12196 = parents_module(OBJECT(module,v12208),v12196), 1);
            GC_UNLOOP; POP_SIGNAL;}
          }
        Result = v12196;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  get_module2(module *v12197) { 
    load_module(v12197);
    begin_module(v12197);
    POP_SIGNAL;}
  

CL_EXPORT void  generate_file_string2(char *v46356,char *v50260) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { PortObject * v50569 = GC_OBJECT(PortObject,fopen_source_string1(v46356));
      OID  v12190 = GC_OID((*(get_location_port1(v50569)->copyIfNeeded()))[1]);
      ClaireBoolean * v12186 = Reader.reader->toplevel;
      PortObject * v50568 = GC_OBJECT(PortObject,Reader.reader->fromp);
      if (should_trace_ask_module1(Generate.it,2) == CTRUE)
       mtformat_module1(Generate.it,((char*)"++++ Generate the file ~A [v3.~A - safety:~A] \n"),2,list::alloc(3,v12190,
        GC_OID(Optimize.compiler->version),
        ((OID)Optimize.compiler->safety)));
      else ;if (Optimize.compiler->class2file_ask != CTRUE)
       _void_(Optimize.OPT->outfile = fopen_string1(GC_STRING(append_string(v50260,GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),((char*)"a")));
      _void_(Reader.reader->toplevel = CFALSE);
      _void_(Optimize.compiler->loading_ask = CTRUE);
      _void_(Reader.reader->nb_line = 1);
      _void_(Reader.reader->external = v46356);
      _void_(Reader.reader->fromp = v50569);
      if (Optimize.compiler->class2file_ask != CTRUE)
       { start_file_string(v46356,ClEnv->module_I);
        if ((OBJECT(ClaireBoolean,Language.DEBUG_ask->value)) == CTRUE)
         { PortObject * v12200 = use_as_output_port(Optimize.OPT->outfile);
          (Optimize._stardebug_local_file_star->value= _string_(realpath_string(string_v(v12190))));
          use_as_output_port(v12200);
          }
        }
      { OID  v28945 = GC_OID(readblock_port(v50569));
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while ((equal(v28945,Core._eof->value) != CTRUE))
          { GC_LOOP;
            if ((CL_INT)ClEnv->verbose > (CL_INT)5)
             { princ_string(((char*)"["));
              princ_integer(Reader.reader->nb_line);
              princ_string(((char*)"] "));
              print_any(_oid_(OWNER(v28945)));
              princ_string(((char*)" ("));
              print_any(GC_OID(_oid_(Optimize.OPT->need_modules)));
              princ_string(((char*)"%)\n"));
              }
            if ((Kernel._string == OWNER(v28945)) && 
                (Optimize.compiler->class2file_ask != CTRUE))
             { if ((CL_INT)Optimize.compiler->naming < (CL_INT)2)
               { PortObject * v50632 = use_as_output_port(Optimize.OPT->outfile);
                princ_string(((char*)"\n//"));
                (*Kernel.princ)(v28945);
                use_as_output_port(v50632);
                }
              }
            else GC_OBJECT(list,Optimize.OPT->instructions)->addFast((OID)GC_OID((*Optimize.c_code)(v28945,
                _oid_(Kernel._void))));
              GC__OID(v28945 = readblock_port(v50569), 1);
            GC_UNLOOP;POP_SIGNAL;}
          }
        }
      putc_char1(_char_(((char*)"\n")[1 - 1]),GC_OBJECT(PortObject,Optimize.OPT->outfile));
      fclose_port1(v50569);
      _void_(Optimize.compiler->loading_ask = CFALSE);
      _void_(Reader.reader->toplevel = v12186);
      _void_(Reader.reader->external = ((char*)"toplevel"));
      _void_(Reader.reader->fromp = v50568);
      (Optimize._stardebug_local_file_star->value= _string_(((char*)"")));
      if (Optimize.compiler->class2file_ask != CTRUE)
       { putc_char1(_char_(((char*)"\n")[1 - 1]),GC_OBJECT(PortObject,Optimize.OPT->outfile));
        fclose_port1(GC_OBJECT(PortObject,Optimize.OPT->outfile));
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  generate_wcl_file_string(char *v46356,char *v59452,char *v50260) { 
    
    GC_BIND;
    if (should_trace_ask_module1(Generate.it,2) == CTRUE)
     mtformat_module1(Generate.it,((char*)"++++ Generate the WCL file ~A [v3.~A - safety:~A] \n"),2,list::alloc(3,_string_(v46356),
      GC_OID(Optimize.compiler->version),
      ((OID)Optimize.compiler->safety)));
    else ;_void_(Optimize.compiler->loading_ask = CTRUE);
    _void_(Optimize.OPT->outfile = fopen_string1(GC_STRING(append_string(v50260,GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),((char*)"a")));
    start_file_string(v46356,ClEnv->module_I);
    if ((OBJECT(ClaireBoolean,Language.DEBUG_ask->value)) == CTRUE)
     { PortObject * v12200 = use_as_output_port(Optimize.OPT->outfile);
      (Optimize._stardebug_local_file_star->value= _string_(realpath_string(v46356)));
      use_as_output_port(v12200);
      }
    { list * v58070 = GC_OBJECT(list,load_wcl_I_string1(v59452));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v12208);
        for (START(v58070); NEXT(v12208);)
        { GC_LOOP;
          GC_OBJECT(list,Optimize.OPT->instructions)->addFast((OID)GC_OID((*Optimize.c_code)(v12208,
            _oid_(Kernel._void))));
          GC_UNLOOP; POP_SIGNAL;}
        }
      putc_char1(_char_(((char*)"\n")[1 - 1]),GC_OBJECT(PortObject,Optimize.OPT->outfile));
      _void_(Optimize.compiler->loading_ask = CFALSE);
      if (Optimize.compiler->class2file_ask != CTRUE)
       { putc_char1(_char_(((char*)"\n")[1 - 1]),GC_OBJECT(PortObject,Optimize.OPT->outfile));
        (Optimize._stardebug_local_file_star->value= _string_(((char*)"")));
        fclose_port1(GC_OBJECT(PortObject,Optimize.OPT->outfile));
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT OID  make_c_function_lambda_Generate(lambda *v46356,char *v25167,OID v12197) { 
    { OID Result = 0;
      if (Optimize.compiler->class2file_ask == CTRUE)
       Result = (*Generate.create_function_entry)(Generate.PRODUCER->value,
        _oid_(v46356),
        _string_(v25167),
        v12197);
      else Result = print_c_function_lambda2(v46356,v25167,v12197);
        POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  print_c_function_lambda2(lambda *v46356,char *v25167,OID v12197) { 
    
    GC_BIND;
    _void_(OBJECT(Generate_producer,Generate.PRODUCER->value)->body = v46356->body);
    { OID Result = 0;
      { ClaireClass * v12203 = Kernel._void;
        OID  v29311;
        { if (boolean_I_any(v12197) != CTRUE)
           v29311 = (*Optimize.c_code)(GC_OID(v46356->body),
            _oid_(Kernel._void));
          else if (Kernel._method == OWNER(v12197))
           { v12203= (check_sort_method(OBJECT(method,v12197)));
            v29311 = OBJECT(Generate_producer,Generate.PRODUCER->value)->body;
            }
          else if (INHERIT(OWNER(v12197),Kernel._class))
           { v12203= (OBJECT(ClaireClass,v12197));
            v29311 = (*Optimize.c_code)(GC_OID(v46356->body),
              v12197);
            }
          else { v12203= (Kernel._any);
              v29311 = (*Optimize.c_code)(GC_OID(v46356->body),
                _oid_(Kernel._any));
              }
            GC_OID(v29311);}
        OID  v16478 = GC_OID((*Generate.protect_result)(Generate.PRODUCER->value,
          _oid_(v12203),
          _oid_(Optimize.OPT->protection),
          v12197));
        ClaireBoolean * v51116 = ((Optimize.OPT->profile_ask == CTRUE) ? (((Kernel._method == OWNER(v12197)) || 
            (v12197 == CNULL)) ? CTRUE: CFALSE): CFALSE);
        (*Generate.generate_function_start)(Generate.PRODUCER->value,
          _oid_(v46356),
          _oid_(v12203),
          v12197,
          _string_(v25167));
        _void_(Optimize.OPT->level = 2);
        if (v51116 == CTRUE)
         (*Generate.generate_profile)(Generate.PRODUCER->value,
          v12197);
        (*Generate.print_body)(v29311,
          v16478,
          _oid_(v12203),
          GC_OID(v46356->body),
          _oid_(not_any(_oid_(((Optimize.OPT->protection == CTRUE) ? CTRUE : ((v51116 == CTRUE) ? CTRUE : ((Optimize.OPT->alloc_stack == CTRUE) ? CTRUE : CFALSE)))))));
        _void_(Optimize.OPT->alloc_stack = CFALSE);
        { PortObject * v22602 = use_as_output_port(Optimize.OPT->outfile);
          close_block_void();
          princ_string(((char*)"\n\n"));
          use_as_output_port(v22602);
          }
        Result = _oid_(use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value)));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  print_body_If(If *v29311,char *v16478,ClaireClass *v12203,If *v3118,ClaireBoolean *v40159) { 
    
    GC_BIND;
    if ((c_func_any(GC_OID(v29311->test)) == CTRUE) && 
        ((Optimize.OPT->protection == CTRUE) && 
          ((c_safe_any(GC_OID(v3118->arg)) == CTRUE) && 
            (Optimize.compiler->debug_ask->memq(_oid_(ClEnv->module_I)) != CTRUE))))
     { char * v52116 = ((v12203 != Kernel._void) ?
        ((char*)"return ") :
        ((char*)"") );
      princ_string(((char*)"if "));
      (*Optimize.bool_exp)(GC_OID(v29311->test),
        Kernel.ctrue,
        Core.nil->value);
      princ_string(((char*)" "));
      breakline_void();
      new_block_void();
      outer_statement_any(GC_OID(v29311->arg),v52116,v12203,v40159);
      princ_string(((char*)" "));
      close_block_void();
      princ_string(((char*)"else"));
      new_block_void();
      (*Generate.print_body)(GC_OID(v29311->other),
        _string_(v16478),
        _oid_(v12203),
        GC_OID(v3118->other),
        _oid_(v40159));
      close_block_void();
      }
    else print_body_any(_oid_(v29311),
        v16478,
        v12203,
        _oid_(v3118),
        v40159);
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  print_body_any(OID v29311,char *v16478,ClaireClass *v12203,OID v3118,ClaireBoolean *v40159) { 
    
    GC_BIND;
    { blob * v15980 = GC_OBJECT(blob,blob_I_void1());
      PortObject * v36751 = GC_OBJECT(PortObject,Optimize.OPT->outfile);
      _void_(Optimize.OPT->outfile = v15980);
      use_as_output_port(v15980);
      outer_statement_any(v29311,v16478,v12203,v40159);
      _void_(Optimize.OPT->outfile = v36751);
      use_as_output_port(Optimize.OPT->outfile);
      if ((CL_INT)Optimize.OPT->loop_index > (CL_INT)0)
       { breakline_void();
        princ_string(((char*)"GC_RESERVE("));
        princ_integer(Optimize.OPT->loop_index);
        princ_string(((char*)");  // v3.3.39 optim !"));
        breakline_void();
        }
      else if (Optimize.OPT->protection == CTRUE)
       { breakline_void();
        princ_string(((char*)"GC_BIND;"));
        breakline_void();
        }
      freadwrite_port3(v15980,v36751);
      fclose_port1(v15980);
      ;}
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT OID  print_body_Do(Do *v29311,char *v16478,ClaireClass *v12203,OID v3118,ClaireBoolean *v40159) { 
    
    GC_BIND;
    { OID Result = 0;
      { list * v12196 = GC_OBJECT(list,v29311->args);
        CL_INT  v45187 = v12196->length;
        CL_INT  v12197 = 0;
        blob * v15980 = GC_OBJECT(blob,blob_I_void1());
        PortObject * v36751 = GC_OBJECT(PortObject,Optimize.OPT->outfile);
        _void_(Optimize.OPT->outfile = v15980);
        use_as_output_port(v15980);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(v12208);
          for (START(v12196); NEXT(v12208);)
          { ++v12197;
            if (v12197 == v45187)
             outer_statement_any(v12208,v16478,v12203,v40159);
            else inner_statement_any(v12208,_oid_(Kernel.emptySet),_oid_(Kernel.emptySet));
              }
          }
        _void_(Optimize.OPT->outfile = v36751);
        use_as_output_port(Optimize.OPT->outfile);
        if ((CL_INT)Optimize.OPT->loop_index > (CL_INT)0)
         { breakline_void();
          princ_string(((char*)"GC_RESERVE("));
          princ_integer(Optimize.OPT->loop_index);
          princ_string(((char*)");  // v3.3.39 optim !"));
          breakline_void();
          }
        else if (Optimize.OPT->protection == CTRUE)
         { breakline_void();
          princ_string(((char*)"GC_BIND;"));
          breakline_void();
          }
        freadwrite_port3(v15980,v36751);
        fclose_port1(v15980);
        Result = Kernel.ctrue;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  outer_statement_any(OID v29311,char *v16478,ClaireClass *v12203,ClaireBoolean *v40159) { 
    if ((c_func_any(v29311) == CTRUE) && 
        ((v40159 == CTRUE) && 
          ((v12203 != Kernel._void) && 
            (inherit_ask_class(OWNER(v29311),Language._If) != CTRUE))))
     { if (equal_string(v16478,((char*)"")) != CTRUE)
       { princ_string(v16478);
        princ_string(((char*)"("));
        (*Generate.expression)(v29311,
          Core.nil->value);
        princ_string(((char*)");"));
        }
      else { (*Generate.expression)(v29311,
            Core.nil->value);
          princ_string(((char*)";"));
          }
        }
    else if (v12203 != Kernel._void)
     { new_block_void();
      (*Generate.define_variable)(Generate.PRODUCER->value,
        _oid_(v12203),
        _string_(((char*)"Result")));
      breakline_void();
      statement_any(v29311,_string_(((char*)"Result")),_oid_(Kernel.emptySet));
      if (equal_string(v16478,((char*)"")) != CTRUE)
       { princ_string(v16478);
        princ_string(((char*)"(Result);"));
        close_block_void();
        }
      }
    else { statement_any(v29311,_oid_(Kernel.emptySet),_oid_(Kernel.emptySet));
        princ_string(v16478);
        }
      POP_SIGNAL;}
  

CL_EXPORT ClaireBoolean * c_safe_any(OID v12208) { 
    POP_SIGNAL; return (not_any(_oid_(((Optimize.OPT->allocation == CTRUE) ? ((BCONTAIN(c_status_any(v12208,Kernel.nil),((CL_INT)(OID)(1)))) ? CTRUE: CFALSE): CFALSE))));}
  

CL_EXPORT ClaireClass * check_sort_method(method *v46356) { 
    
    GC_BIND;
    { ClaireClass *Result ;
      { ClaireType * v50665 = v46356->range;
        OID  v12186 = GC_OID(OBJECT(Generate_producer,Generate.PRODUCER->value)->body);
        ClaireType * v50666 = GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v12186))));
        ClaireClass * v12203 = psort_any(_oid_(v50665));
        _void_(OBJECT(Generate_producer,Generate.PRODUCER->value)->body = c_strict_code_any(v12186,v12203));
        show_opportunist_integer1(5);
        if (should_trace_ask_module1(Generate.it,5) == CTRUE)
         mtformat_module1(Generate.it,((char*)" `GREEN note: ~S's range was found to be ~S (vs. ~S) \n"),5,list::alloc(3,_oid_(v46356),
          _oid_(v50666),
          _oid_(v50665)));
        else ;if (_inf_equal_type(v50666,v50665) != CTRUE)
         { show_opportunist_integer1(2);
          if (should_trace_ask_module1(Generate.it,2) == CTRUE)
           mtformat_module1(Generate.it,((char*)" `GREEN note: ~S's range was found to be ~S (vs. ~S) \n"),2,list::alloc(3,_oid_(v46356),
            _oid_(v50666),
            _oid_(v50665)));
          else ;if (Generate.WrongMethod->value == ((OID)0))
           { (Generate.WrongMethod->value= v12186);
            close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"You can look at WrongMethod")),
              _oid_(Kernel.nil))));
            }
          if (((CL_INT)Optimize.compiler->safety < (CL_INT)2) || 
              (((CL_INT)Optimize.compiler->safety < (CL_INT)4) && 
                  (boolean_I_any(sort_equal_class(osort_any(_oid_(v50666)),v12203)) != CTRUE)))
           _void_(OBJECT(Generate_producer,Generate.PRODUCER->value)->body = c_strict_code_any(GC_OID(c_check_any(GC_OID((*Optimize.c_code)(v12186,
            _oid_(Kernel._any))),GC_OID((*Optimize.c_code)(_oid_(v50665),
            _oid_(Kernel._type))))),v12203));
          if (boolean_I_any(sort_equal_class(osort_any(_oid_(v50666)),v12203)) != CTRUE)
           { if ((v12203 != Kernel._void) && 
                ((_oid_((INHERIT(v50666->isa,Kernel._class) ?
                   (ClaireObject *) sort_I_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v50666))) : 
                   (ClaireObject *)  sort_I_type((ClaireType *) OBJECT(ClaireType,_oid_(v50666))))) == _oid_(Kernel._void)) || 
                    (inherit_ask_class(v12203,OBJECT(ClaireClass,_oid_((INHERIT(v50666->isa,Kernel._class) ?
                     (ClaireObject *) sort_I_class((ClaireClass *) OBJECT(ClaireClass,_oid_(v50666))) : 
                     (ClaireObject *)  sort_I_type((ClaireType *) OBJECT(ClaireType,_oid_(v50666))))))) != CTRUE)))
             (*Optimize.Cerror)(_string_(((char*)"[218] Sort error: Cannot compile ~S.")),
              _oid_(v46356));
            }
          }
        { ClaireType * v50667 = GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel._exp)(_oid_(v50665),
            _oid_(v50666))));
          if (((CL_INT)Optimize.compiler->safety > (CL_INT)1) && 
              (osort_any(_oid_(v50667)) == v12203))
           { _void_(OBJECT(Generate_producer,Generate.PRODUCER->value)->body = (*Optimize.c_strict_check)(GC_OID(OBJECT(Generate_producer,Generate.PRODUCER->value)->body),
              _oid_(class_I_type(v50667))));
            ;}
          }
        if (INHERIT(v50665->isa,Kernel._tuple))
         { show_opportunist_integer1(3);
          if (should_trace_ask_module1(Generate.it,3) == CTRUE)
           mtformat_module1(Generate.it,((char*)" `GREEN note: ~S is a method with range <= tuple => use stack allocation \n"),3,list::alloc(1,_oid_(v46356)));
          else ;_void_(Optimize.OPT->alloc_stack = CTRUE);
          }
        if ((Optimize.OPT->allocation == CTRUE) && 
            (nth_integer(status_I_restriction(v46356),((CL_INT)(OID)(6))) != CTRUE))
         { if (nth_integer(status_I_restriction(v46356),((CL_INT)(OID)(1))) != CTRUE)
           { show_opportunist_integer1(3);
            if (should_trace_ask_module1(Generate.it,3) == CTRUE)
             mtformat_module1(Generate.it,((char*)"  `GREEN note: ~S may provoke an allocation \n"),3,list::alloc(1,_oid_(v46356)));
            else ;}
          }
        else { _void_(Optimize.OPT->loop_gc = CFALSE);
            _void_(Optimize.OPT->protection = CFALSE);
            }
          Result = psort_any(_oid_(v46356->range));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  typed_args_list_list(list *v46356) { 
    { OID Result = 0;
      { ClaireBoolean * v30401 = CTRUE;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(v12208);
          Result= Kernel.cfalse;
          for (START(v46356); NEXT(v12208);)
          { if (v30401 == CTRUE)
             v30401= (CFALSE);
            else princ_string(((char*)","));
              (*Generate.interface_I)(Generate.PRODUCER->value,
              _oid_(sort_Variable(OBJECT(Variable,v12208))));
            (*Language.ident)(Generate.PRODUCER->value,
              v12208);
            }
          }
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  get_dependents_method(method *v12197) { 
    
    GC_BIND;
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v12200);
      bag *v12200_support;
      v12200_support = GC_OBJECT(set,dependents_method(v12197));
      for (START(v12200_support); NEXT(v12200);)
      { property * v22603 = v12197->selector;
        add_table(Reader.PRdependent,_oid_(v22603),v12200);
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  c_princ_function(ClaireFunction *v46356) { 
    c_princ_string(string_I_function(v46356));
    POP_SIGNAL;}
  

CL_EXPORT void  set_outfile_lambda(lambda *v46356) { 
    
    GC_BIND;
    { module * v12197 = ClEnv->module_I;
      char * v50225 = string_I_symbol(v12197->name);
      PortObject * v12200 = GC_OBJECT(PortObject,Optimize.OPT->outfile);
      OID  v15557;
      { if (v46356->vars->length != 0)
         v15557 = (*Kernel.range)(GC_OID((*(v46356->vars))[1]));
        else v15557 = CNULL;
          GC_OID(v15557);}
      if (v15557 != CNULL)
       { { ClaireBoolean * g1806I;
          { OID  v33709;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(v12187);
              v33709= Kernel.cfalse;
              bag *v12187_support;
              v12187_support = GC_OBJECT(list,Optimize.OPT->objects);
              for (START(v12187_support); NEXT(v12187);)
              if ((INHERIT(OWNER(v12187),Kernel._class)) && 
                  (equal(v12187,v15557) == CTRUE))
               { v33709 = Kernel.ctrue;
                ClEnv->cHandle = loop_handle;break;}
              }
            g1806I = boolean_I_any(v33709);
            }
          
          if (g1806I == CTRUE) v50225= (GC_STRING(string_v((*Generate.c_string)(Generate.PRODUCER->value,
              _oid_(OBJECT(ClaireClass,v15557)->name)))));
            }
        if (equal_string(v50225,string_I_symbol(ClEnv->module_I->name)) != CTRUE)
         v12200= (GC_OBJECT(buffer,fopen_string1(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),v50225)),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),((char*)"a"))));
        _void_(Optimize.OPT->outfile = v12200);
        }
      ;}
    GC_UNBIND; POP_SIGNAL;}
  



/***** CLAIRE Compilation of file ./compile/gexp.cl 
         [version 3.5.0 / safety 5] *****/

CL_EXPORT ClaireBoolean * c_func_any(OID v46356) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { ClaireBoolean *Result ;
      if (INHERIT(OWNER(v46356),Kernel._bag))
       { OID  v34670;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(v12208);
          v34670= Kernel.cfalse;
          for (START(OBJECT(bag,v46356)); NEXT(v12208);)
          if (c_func_any(v12208) != CTRUE)
           { v34670 = Kernel.ctrue;
            ClEnv->cHandle = loop_handle;break;}
          else ;}
        Result = not_any(v34670);
        }
      else if (INHERIT(OWNER(v46356),Language._Construct))
       { if (((INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Set)) || 
              (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._List))) || 
            (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Tuple)))
         { ClaireBoolean *v_and;
          { v_and = (((CL_INT)OBJECT(Construct,v46356)->args->length < (CL_INT)15) ? CTRUE : CFALSE);
            if (v_and == CFALSE) Result =CFALSE; 
            else { { OID  v35631;
                { ClaireBoolean * v21120;{ OID  v57734;
                    { set * v21122;{ set * v46655 = set::empty(Kernel.emptySet);
                        { CL_INT loop_handle = ClEnv->cHandle;
                          ITERATE(v12208);
                          bag *v12208_support;
                          v12208_support = GC_OBJECT(list,OBJECT(Construct,v46356)->args);
                          for (START(v12208_support); NEXT(v12208);)
                          if (c_func_any(v12208) != CTRUE)
                           v46655->addFast((OID)v12208);
                          }
                        v21122 = GC_OBJECT(set,v46655);
                        }
                      
                      v57734=_oid_(v21122);}
                    v21120 = boolean_I_any(v57734);
                    }
                  
                  v35631=_oid_(v21120);}
                v_and = ((v35631 != Kernel.ctrue) ? CTRUE : CFALSE);
                }
              if (v_and == CFALSE) Result =CFALSE; 
              else Result = CTRUE;}
            }
          }
        else Result = CFALSE;
          }
      else if (INHERIT(OWNER(v46356),Language._If))
       { ClaireBoolean *v_and;
        { v_and = c_func_any(GC_OID(OBJECT(If,v46356)->test));
          if (v_and == CFALSE) Result =CFALSE; 
          else { v_and = c_func_any(GC_OID(OBJECT(If,v46356)->arg));
            if (v_and == CFALSE) Result =CFALSE; 
            else { v_and = c_func_any(GC_OID(OBJECT(If,v46356)->other));
              if (v_and == CFALSE) Result =CFALSE; 
              else { v_and = stupid_t_any2(GC_OID(OBJECT(If,v46356)->arg),GC_OID(OBJECT(If,v46356)->other));
                if (v_and == CFALSE) Result =CFALSE; 
                else { { CL_INT  v12198 = 4;
                    OID  v12208 = GC_OID(OBJECT(If,v46356)->other);
                    { OID v61842;{ CL_INT loop_handle = ClEnv->cHandle;
                        OID gc_local;
                        v61842= _oid_(CFALSE);
                        while (((CL_INT)v12198 > (CL_INT)0))
                        { GC_LOOP;
                          if (INHERIT(OWNER(v12208),Language._If))
                           { GC__OID(v12208 = OBJECT(If,v12208)->other, 1);
                            v12198= (CL_INT)(((CL_INT)v12198-(CL_INT)1));
                            }
                          else { GC_UNLOOP;v61842 = Kernel.ctrue;
                              ClEnv->cHandle = loop_handle;break;}
                            GC_UNLOOP;POP_SIGNAL;}
                        }
                      
                      v_and=OBJECT(ClaireBoolean,v61842);}
                    }
                  if (v_and == CFALSE) Result =CFALSE; 
                  else Result = CTRUE;}
                }
              }
            }
          }
        }
      else if (INHERIT(OWNER(v46356),Language._Assign))
       Result = c_func_any(GC_OID(OBJECT(Assign,v46356)->arg));
      else if (INHERIT(OWNER(v46356),Language._Gassign))
       Result = c_func_any(GC_OID(OBJECT(Gassign,v46356)->arg));
      else if (INHERIT(OWNER(v46356),Optimize._to_protect))
       Result = c_func_any(GC_OID(OBJECT(Compile_to_protect,v46356)->arg));
      else if (INHERIT(OWNER(v46356),Language._And))
       Result = c_func_any(GC_OID(_oid_(OBJECT(And,v46356)->args)));
      else if (INHERIT(OWNER(v46356),Language._Or))
       Result = c_func_any(GC_OID(_oid_(OBJECT(Or,v46356)->args)));
      else if (INHERIT(OWNER(v46356),Language._Call))
       Result = c_func_any(GC_OID(_oid_(OBJECT(Call,v46356)->args)));
      else if (INHERIT(OWNER(v46356),Language._Call_method))
       Result = ((c_func_any(GC_OID(_oid_(OBJECT(Call_method,v46356)->args))) == CTRUE) ? ((_oid_(OBJECT(Call_method,v46356)->arg) != Generate._starclose_exception_star->value) ? CTRUE: CFALSE): CFALSE);
      else if (INHERIT(OWNER(v46356),Language._Call_slot))
       Result = c_func_any(GC_OID(OBJECT(Call_slot,v46356)->arg));
      else if (INHERIT(OWNER(v46356),Language._Call_table))
       Result = c_func_any(GC_OID(OBJECT(Call_table,v46356)->arg));
      else if (INHERIT(OWNER(v46356),Language._Call_array))
       Result = c_func_any(GC_OID(OBJECT(Call_array,v46356)->arg));
      else Result = ((INHERIT(OWNER(v46356),Language._Update)) ?
        ((c_func_any(GC_OID(OBJECT(Update,v46356)->value)) == CTRUE) ? ((c_func_any(GC_OID(OBJECT(Update,v46356)->arg)) == CTRUE) ? CTRUE: CFALSE): CFALSE) :
        ((INHERIT(OWNER(v46356),Language._Cast)) ?
          c_func_any(GC_OID(OBJECT(Cast,v46356)->arg)) :
          ((INHERIT(OWNER(v46356),Optimize._to_C)) ?
            c_func_any(GC_OID(OBJECT(Compile_to_C,v46356)->arg)) :
            ((INHERIT(OWNER(v46356),Optimize._to_CL)) ?
              c_func_any(GC_OID(OBJECT(Compile_to_CL,v46356)->arg)) :
              ((INHERIT(OWNER(v46356),Kernel._thing)) ? CTRUE : 
              ((INHERIT(OWNER(v46356),Kernel._integer)) ? CTRUE : 
              ((Kernel._string == OWNER(v46356)) ? CTRUE : 
              ((INHERIT(OWNER(v46356),Kernel._char)) ? CTRUE : 
              ((Kernel._float == OWNER(v46356)) ? CTRUE : 
              ((INHERIT(OWNER(v46356),Language._Variable)) ? CTRUE : 
              ((INHERIT(OWNER(v46356),Core._global_variable)) ? CTRUE : 
              ((INHERIT(OWNER(v46356),Kernel._function)) ? CTRUE : 
              ((INHERIT(OWNER(v46356),Kernel._symbol)) ? CTRUE : 
              ((v46356 == CNULL) ? CTRUE : 
              ((Kernel._boolean == OWNER(v46356)) ? CTRUE : 
              ((INHERIT(OWNER(v46356),Kernel._class)) ? CTRUE : 
              ((INHERIT(OWNER(v46356),Kernel._environment)) ? CTRUE : 
              CFALSE))))))))))))) ) ) ) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  expression_thing(thing *v46356,OID v44140) { 
    (*Generate.produce)(Generate.PRODUCER->value,
      _oid_(v46356));
    POP_SIGNAL;}
  

CL_EXPORT void  expression_integer(CL_INT v46356,OID v44140) { 
    princ_integer(v46356);
    POP_SIGNAL;}
  

CL_EXPORT void  expression_any(OID v46356,OID v44140) { 
    (*Generate.produce)(Generate.PRODUCER->value,
      v46356);
    POP_SIGNAL;}
  

CL_EXPORT void  expression_string(char *v46356,OID v44140) { 
    (*Generate.produce)(Generate.PRODUCER->value,
      _string_(v46356));
    POP_SIGNAL;}
  

CL_EXPORT void  expression_float_(OID v22632,OID v22633) { 
    expression_float(float_v(v22632),v22633);
}

CL_EXPORT void  expression_float(double v46356,OID v44140) { 
      princ_float(v46356);
    POP_SIGNAL;}
  

CL_EXPORT void  expression_boolean(ClaireBoolean *v46356,OID v44140) { 
    (*Generate.produce)(Generate.PRODUCER->value,
      _oid_(v46356));
    POP_SIGNAL;}
  

CL_EXPORT void  expression_environment(ClaireEnvironment *v46356,OID v44140) { 
    (*Generate.produce)(Generate.PRODUCER->value,
      _oid_(v46356));
    POP_SIGNAL;}
  

CL_EXPORT void  expression_Variable(Variable *v46356,OID v44140) { 
    (*Language.ident)(Generate.PRODUCER->value,
      _oid_(v46356));
    POP_SIGNAL;}
  

CL_EXPORT void  expression_global_variable(global_variable *v46356,OID v44140) { 
    (*Generate.produce)(Generate.PRODUCER->value,
      _oid_(v46356));
    POP_SIGNAL;}
  

CL_EXPORT void  expression_Set(Set *v46356,OID v44140) { 
    
    GC_BIND;
    { OID  v61578;
      { if (((v46356->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         v61578 = _oid_(v46356->of);
        else v61578 = _oid_(Kernel._void);
          GC_OID(v61578);}
      (*Generate.bag_expression)(Generate.PRODUCER->value,
        _oid_(Kernel._set),
        GC_OID(_oid_(v46356->args)),
        v61578,
        v44140);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  expression_set2(set *v46356,OID v44140) { 
    if ((v46356->length == 0) && 
        (equal(_oid_(of_bag(v46356)),_oid_(Kernel.emptySet)) == CTRUE))
     princ_string(((char*)"Kernel.emptySet"));
    else (*Generate.bag_expression)(Generate.PRODUCER->value,
        _oid_(Kernel._set),
        _oid_(v46356),
        _oid_(of_bag(v46356)),
        v44140);
      POP_SIGNAL;}
  

CL_EXPORT void  expression_Tuple(Tuple *v46356,OID v44140) { 
    
    GC_BIND;
    (*Generate.bag_expression)(Generate.PRODUCER->value,
      _oid_(Kernel._tuple),
      GC_OID(_oid_(v46356->args)),
      _oid_(Kernel._void),
      v44140);
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  expression_tuple(tuple *v46356,OID v44140) { 
    (*Generate.bag_expression)(Generate.PRODUCER->value,
      _oid_(Kernel._tuple),
      _oid_(v46356),
      _oid_(Kernel._void),
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  expression_List(List *v46356,OID v44140) { 
    
    GC_BIND;
    { OID  v62539;
      { if (((v46356->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         v62539 = _oid_(v46356->of);
        else v62539 = _oid_(Kernel._void);
          GC_OID(v62539);}
      (*Generate.bag_expression)(Generate.PRODUCER->value,
        _oid_(Kernel._list),
        GC_OID(_oid_(v46356->args)),
        v62539,
        v44140);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  expression_list(list *v46356,OID v44140) { 
    if ((v46356->length == 0) && 
        (equal(_oid_(of_bag(v46356)),_oid_(Kernel.emptySet)) == CTRUE))
     princ_string(((char*)"Kernel.nil"));
    else (*Generate.bag_expression)(Generate.PRODUCER->value,
        _oid_(Kernel._list),
        _oid_(v46356),
        _oid_(of_bag(v46356)),
        v44140);
      POP_SIGNAL;}
  

CL_EXPORT void  expression_Call2(Call *v46356,OID v44140) { 
    (*Generate.inline_exp)(Generate.PRODUCER->value,
      _oid_(v46356),
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  expression_Call_method12(Call_method1 *v46356,OID v44140) { 
    (*Generate.inline_exp)(Generate.PRODUCER->value,
      _oid_(v46356),
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  expression_Call_method22(Call_method2 *v46356,OID v44140) { 
    (*Generate.inline_exp)(Generate.PRODUCER->value,
      _oid_(v46356),
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  expression_Call_method2(Call_method *v46356,OID v44140) { 
    (*Generate.inline_exp)(Generate.PRODUCER->value,
      _oid_(v46356),
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  bexpression_any(OID v46356,OID v44140) { 
    if (INHERIT(OWNER(v46356),Language._Assign))
     { princ_string(((char*)"("));
      expression_Assign(OBJECT(Assign,v46356),v44140);
      princ_string(((char*)")"));
      }
    else if (INHERIT(OWNER(v46356),Optimize._to_C))
     { princ_string(((char*)"("));
      (*Generate.expression)(v46356,
        v44140);
      princ_string(((char*)")"));
      }
    else if (INHERIT(OWNER(v46356),Kernel._integer))
     { if ((CL_INT)v46356 < (CL_INT)0)
       { princ_string(((char*)"((CL_INT)"));
        expression_integer(v46356,v44140);
        princ_string(((char*)")"));
        }
      else expression_integer(v46356,v44140);
        }
    else if (Kernel._float == OWNER(v46356))
     { if (float_v(v46356) < 0.0)
       { princ_string(((char*)"("));
        expression_float(float_v(v46356),v44140);
        princ_string(((char*)")"));
        }
      else expression_float(float_v(v46356),v44140);
        }
    else (*Generate.expression)(v46356,
        v44140);
      POP_SIGNAL;}
  

CL_EXPORT void  expression_If(If *v46356,OID v44140) { 
    
    GC_BIND;
    princ_string(((char*)"("));
    (*Optimize.bool_exp)(GC_OID(v46356->test),
      Kernel.ctrue,
      v44140);
    princ_string(((char*)" ?"));
    _void_(Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
    breakline_void();
    (*Generate.expression)(GC_OID(v46356->arg),
      v44140);
    princ_string(((char*)" :"));
    breakline_void();
    (*Generate.expression)(GC_OID(v46356->other),
      v44140);
    princ_string(((char*)" )"));
    _void_(Optimize.OPT->level = ((CL_INT)Optimize.OPT->level-(CL_INT)1));
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  expression_Assign(Assign *v46356,OID v44140) { 
    
    GC_BIND;
    { OID  v12208 = GC_OID(v46356->arg);
      OID  v12206 = GC_OID(v46356->var);
      if ((INHERIT(OWNER(v12208),Language._Call_method2)) && ((_oid_(OBJECT(Call_method,v12208)->arg) == Generate._star_plus_integer_star->value) && 
          ((equal((*(OBJECT(Call_method,v12208)->args))[1],v46356->var) == CTRUE) && 
            ((*(OBJECT(Call_method,v12208)->args))[2] == ((OID)1)))))
       { princ_string(((char*)"++"));
        (*Generate.expression)(v12206,
          v44140);
        }
      else if ((boolean_I_any(v44140) == CTRUE) && 
          ((Optimize.OPT->loop_gc == CTRUE) && 
            (inner2outer_ask_any(v12208) == CTRUE)))
       { OID  v65422;
        { if (INHERIT(OWNER(v12208),Optimize._to_protect))
           v65422 = OBJECT(Compile_to_protect,v12208)->arg;
          else v65422 = v12208;
            GC_OID(v65422);}
        (*Generate.gc_protection_exp)(Generate.PRODUCER->value,
          v12206,
          Kernel.ctrue,
          v65422,
          v44140);
        }
      else (*Generate.exp_Assign)(Generate.PRODUCER->value,
          _oid_(v46356),
          v44140);
        }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  expression_to_protect(Compile_to_protect *v46356,OID v44140) { 
    (*Generate.exp_to_protect)(Generate.PRODUCER->value,
      _oid_(v46356),
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT char * gc_protect_class(ClaireClass *v12187) { 
    _void_(OBJECT(Generate_producer,Generate.PRODUCER->value)->stat = ((CL_INT)OBJECT(Generate_producer,Generate.PRODUCER->value)->stat+(CL_INT)1));
    { char *Result ;
      if (v12187 == Kernel._any)
       Result = ((char*)"GC_OID");
      else if (v12187 == Kernel._string)
       Result = ((char*)"GC_STRING");
      else if (v12187 == Kernel._array)
       Result = ((char*)"GC_ARRAY");
      else if (INHERIT(v12187,Kernel._object))
       Result = ((char*)"GC_OBJECT");
      else { _void_(OBJECT(Generate_producer,Generate.PRODUCER->value)->stat = ((CL_INT)OBJECT(Generate_producer,Generate.PRODUCER->value)->stat-(CL_INT)1));
          Result = ((char*)"");
          }
        POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  expression_Gassign(Gassign *v46356,OID v44140) { 
    (*Generate.gassign)(Generate.PRODUCER->value,
      _oid_(v46356),
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  expression_And(And *v46356,OID v44140) { 
    
    GC_BIND;
    { ClaireBoolean * v12186 = (((CL_INT)v46356->args->length > (CL_INT)5) ? CTRUE : CFALSE);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        for (START(v46356->args); NEXT(v12208);)
        { princ_string(((char*)"("));
          (*Optimize.bool_exp)(v12208,
            Kernel.ctrue,
            v44140);
          princ_string(((char*)" ? "));
          if (v12186 == CTRUE)
           breakline_void();
          }
        }
      expression_boolean(CTRUE,v44140);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        for (START(v46356->args); NEXT(v12208);)
        { princ_string(((char*)": "));
          expression_boolean(CFALSE,v44140);
          princ_string(((char*)")"));
          }
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  expression_Or(Or *v46356,OID v44140) { 
    
    GC_BIND;
    { ClaireBoolean * v12186 = (((CL_INT)v46356->args->length > (CL_INT)5) ? CTRUE : CFALSE);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        for (START(v46356->args); NEXT(v12208);)
        { princ_string(((char*)"("));
          (*Optimize.bool_exp)(v12208,
            Kernel.ctrue,
            v44140);
          princ_string(((char*)" ? "));
          expression_boolean(CTRUE,v44140);
          princ_string(((char*)" : "));
          if (v12186 == CTRUE)
           breakline_void();
          }
        }
      expression_boolean(CFALSE,v44140);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        for (START(v46356->args); NEXT(v12208);)
        princ_string(((char*)")"));
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  expression_to_CL(Compile_to_CL *v46356,OID v44140) { 
    
    GC_BIND;
    (*Generate.to_cl)(Generate.PRODUCER->value,
      v46356->arg,
      _oid_(v46356->set_arg),
      v44140);
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  expression_to_C(Compile_to_C *v46356,OID v44140) { 
    
    GC_BIND;
    (*Generate.to_c)(Generate.PRODUCER->value,
      v46356->arg,
      _oid_(v46356->set_arg),
      v44140);
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  expression_C_cast(Compile_C_cast *v46356,OID v44140) { 
    (*Kernel.cast_I)(Generate.PRODUCER->value,
      _oid_(v46356),
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  expression_Call_slot(Call_slot *v46356,OID v44140) { 
    (*Generate.call_slot)(Generate.PRODUCER->value,
      _oid_(v46356),
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  expression_Call_table(Call_table *v46356,OID v44140) { 
    (*Generate.call_table)(Generate.PRODUCER->value,
      _oid_(v46356),
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  expression_Call_array(Call_array *v46356,OID v44140) { 
    (*Generate.call_array)(Generate.PRODUCER->value,
      _oid_(v46356),
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  expression_Update(Update *v46356,OID v44140) { 
    (*Generate.update)(Generate.PRODUCER->value,
      _oid_(v46356),
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  sign_equal_boolean(ClaireBoolean *v46356) { 
    if (v46356 == CTRUE)
     princ_string(((char*)"=="));
    else princ_string(((char*)"!="));
      POP_SIGNAL;}
  

CL_EXPORT void  sign_or_boolean(ClaireBoolean *v46356) { 
    if (v46356 == CTRUE)
     princ_string(((char*)"||"));
    else princ_string(((char*)"&&"));
      POP_SIGNAL;}
  

CL_EXPORT void  bool_exp_any_Generate(OID v46356,ClaireBoolean *v32308,OID v44140) { 
    any_bool_exp_any(v46356,v32308,v44140,not_any(_oid_(((INHERIT(OWNER(v46356),Core._global_variable)) ? ((nativeVar_ask_global_variable(OBJECT(global_variable,v46356)) != CTRUE) ? CTRUE: CFALSE): CFALSE))));
    POP_SIGNAL;}
  

CL_EXPORT void  any_bool_exp_any(OID v46356,ClaireBoolean *v32308,OID v44140,ClaireBoolean *v24838) { 
    princ_string(((char*)"("));
    bexpression_any(v46356,v44140);
    princ_string(((char*)" "));
    if (v32308 != CTRUE)
     princ_string(((char*)"!="));
    else princ_string(((char*)"=="));
      princ_string(((char*)" "));
    if (v24838 != CTRUE)
     (*Generate.to_cl)(Generate.PRODUCER->value,
      Kernel.ctrue,
      _oid_(Kernel._boolean),
      v44140);
    else expression_boolean(CTRUE,v44140);
      princ_string(((char*)")"));
    POP_SIGNAL;}
  

CL_EXPORT void  bool_exp_to_CL_Generate(Compile_to_CL *v46356,ClaireBoolean *v32308,OID v44140) { 
    
    GC_BIND;
    (*Optimize.bool_exp)(v46356->arg,
      _oid_(v32308),
      v44140);
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  bool_exp_If_Generate(If *v46356,ClaireBoolean *v32308,OID v44140) { 
    
    GC_BIND;
    if (boolean_I_any(v46356->other) == CTRUE)
     { princ_string(((char*)"("));
      (*Optimize.bool_exp)(v46356->test,
        Kernel.ctrue,
        v44140);
      princ_string(((char*)" ? "));
      (*Optimize.bool_exp)(v46356->arg,
        _oid_(v32308),
        v44140);
      princ_string(((char*)" : "));
      (*Optimize.bool_exp)(v46356->other,
        _oid_(v32308),
        v44140);
      princ_string(((char*)")"));
      }
    else { princ_string(((char*)"("));
        (*Optimize.bool_exp)(v46356->test,
          _oid_(v32308),
          v44140);
        princ_string(((char*)" "));
        sign_or_boolean(not_any(_oid_(v32308)));
        princ_string(((char*)" "));
        (*Optimize.bool_exp)(v46356->arg,
          _oid_(v32308),
          v44140);
        princ_string(((char*)")"));
        }
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  bool_exp_And_Generate(And *v46356,ClaireBoolean *v32308,OID v44140) { 
    
    GC_BIND;
    { list * v12196 = GC_OBJECT(list,v46356->args);
      CL_INT  v12197 = v12196->length;
      CL_INT  v12198 = 0;
      CL_INT  v48303 = Optimize.OPT->level;
      _void_(Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        for (START(v12196); NEXT(v12208);)
        { ++v12198;
          if (v12198 == v12197)
           (*Optimize.bool_exp)(v12208,
            _oid_(v32308),
            v44140);
          else { princ_string(((char*)"("));
              (*Optimize.bool_exp)(v12208,
                _oid_(v32308),
                v44140);
              princ_string(((char*)" "));
              sign_or_boolean(not_any(_oid_(v32308)));
              princ_string(((char*)" "));
              _void_(Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
              breakline_void();
              }
            }
        }
      { CL_INT  v12208 = 2;
        CL_INT  v22665 = v12197;
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)v12208 <= (CL_INT)v22665))
          { princ_string(((char*)")"));
            ++v12208;
            POP_SIGNAL;}
          }
        }
      _void_(Optimize.OPT->level = v48303);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  bool_exp_Or_Generate(Or *v46356,ClaireBoolean *v32308,OID v44140) { 
    
    GC_BIND;
    { list * v12196 = GC_OBJECT(list,v46356->args);
      CL_INT  v12197 = v12196->length;
      CL_INT  v12198 = 0;
      CL_INT  v48303 = Optimize.OPT->level;
      _void_(Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        for (START(v12196); NEXT(v12208);)
        { ++v12198;
          if (v12198 == v12197)
           (*Optimize.bool_exp)(v12208,
            _oid_(v32308),
            v44140);
          else { princ_string(((char*)"("));
              (*Optimize.bool_exp)(v12208,
                _oid_(v32308),
                v44140);
              princ_string(((char*)" "));
              sign_or_boolean(v32308);
              princ_string(((char*)" "));
              _void_(Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
              breakline_void();
              }
            }
        }
      { CL_INT  v12208 = 2;
        CL_INT  v22668 = v12197;
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)v12208 <= (CL_INT)v22668))
          { princ_string(((char*)")"));
            ++v12208;
            POP_SIGNAL;}
          }
        }
      _void_(Optimize.OPT->level = v48303);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  bool_exp_Call_method1_Generate(Call_method1 *v46356,ClaireBoolean *v32308,OID v44140) { 
    
    GC_BIND;
    { method * v12197 = v46356->arg;
      OID  v50104 = GC_OID((*(v46356->args))[1]);
      if (_oid_(v12197) == Generate._starnot_star->value)
       { if (INHERIT(OWNER(v50104),Optimize._to_CL))
         any_bool_exp_any(GC_OID((*Kernel.arg)(v50104)),not_any(_oid_(v32308)),v44140,CTRUE);
        else any_bool_exp_any(v50104,not_any(_oid_(v32308)),v44140,CFALSE);
          }
      else if (_oid_(v12197) == Generate._starknown_star->value)
       (*Generate.equal_exp)(Generate.PRODUCER->value,
        v50104,
        _oid_(not_any(_oid_(v32308))),
        CNULL,
        v44140);
      else if (_oid_(v12197) == Generate._starunknown_star->value)
       (*Generate.equal_exp)(Generate.PRODUCER->value,
        v50104,
        _oid_(v32308),
        CNULL,
        v44140);
      else if (_inf_equal_type(v12197->range,Kernel._boolean) == CTRUE)
       { princ_string(((char*)"("));
        expression_Call_method12(v46356,v44140);
        princ_string(((char*)" "));
        sign_equal_boolean(v32308);
        princ_string(((char*)" "));
        expression_boolean(CTRUE,v44140);
        princ_string(((char*)")"));
        }
      else { OID v_rec;
          v_rec = _oid_(v46356);
          PUSH(v_rec);
          v_rec = _oid_(v32308);
          PUSH(v_rec);
          v_rec = v44140;
          PUSH(v_rec);
          Optimize.bool_exp->super(Kernel._any,3);}
        }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  bool_exp_Call_method2_Generate(Call_method2 *v46356,ClaireBoolean *v32308,OID v44140) { 
    
    GC_BIND;
    { method * v12197 = v46356->arg;
      property * v12200 = v12197->selector;
      list * v58504 = GC_OBJECT(list,OBJECT(Generate_producer,Generate.PRODUCER->value)->open_comparators);
      OID  v50104 = GC_OID((*(v46356->args))[1]);
      OID  v50105 = GC_OID((*(v46356->args))[2]);
      if (v12200 == Core._I_equal)
       (*Generate.equal_exp)(Generate.PRODUCER->value,
        v50104,
        _oid_(not_any(_oid_(v32308))),
        v50105,
        Core.nil->value);
      else if (v12200 == Core.identical_ask)
       (*Generate.equal_exp)(Generate.PRODUCER->value,
        v50104,
        _oid_(v32308),
        v50105,
        Kernel.ctrue);
      else if (v12200 == Kernel._equal)
       (*Generate.equal_exp)(Generate.PRODUCER->value,
        v50104,
        _oid_(v32308),
        v50105,
        Core.nil->value);
      else if ((v58504->memq(_oid_(v12200)) == CTRUE) && 
          ((domain_I_restriction(v12197) == Kernel._integer) || 
              (domain_I_restriction(v12197) == Kernel._float)))
       { princ_string(((char*)"("));
        if (domain_I_restriction(v12197) == Kernel._integer)
         princ_string(((char*)"(CL_INT)"));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)" "));
        if (v32308 == CTRUE)
         print_any(_oid_(v12200));
        else print_any((*(v58504))[((CL_INT)mod_integer(((CL_INT)index_list(v58504,_oid_(v12200))+(CL_INT)1),4)+(CL_INT)1)]);
          princ_string(((char*)" "));
        if (domain_I_restriction(v12197) == Kernel._integer)
         princ_string(((char*)"(CL_INT)"));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)")"));
        }
      else if (_oid_(v12197) == Generate._starnth_integer_star->value)
       { princ_string(((char*)"("));
        if (v32308 != CTRUE)
         princ_string(((char*)"!"));
        (*Generate.bitvector_exp)(Generate.PRODUCER->value,
          v50104,
          v50105,
          v44140);
        princ_string(((char*)")"));
        }
      else if ((v12200 == Core.inherit_ask) && 
          (domain_I_restriction(v12197) == Kernel._class))
       { princ_string(((char*)"("));
        if (v32308 != CTRUE)
         princ_string(((char*)"!"));
        (*Generate.inherit_exp)(Generate.PRODUCER->value,
          v50104,
          v50105,
          v44140);
        princ_string(((char*)")"));
        }
      else if (_inf_equal_type(v12197->range,Kernel._boolean) == CTRUE)
       { princ_string(((char*)"("));
        expression_Call_method22(v46356,v44140);
        princ_string(((char*)" "));
        sign_equal_boolean(v32308);
        princ_string(((char*)" "));
        expression_boolean(CTRUE,v44140);
        princ_string(((char*)")"));
        }
      else { OID v_rec;
          v_rec = _oid_(v46356);
          PUSH(v_rec);
          v_rec = _oid_(v32308);
          PUSH(v_rec);
          v_rec = v44140;
          PUSH(v_rec);
          Optimize.bool_exp->super(Kernel._any,3);}
        }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT ClaireBoolean * bool_exp_ask_any(OID v12208) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      if (INHERIT(OWNER(v12208),Optimize._to_CL))
       Result = bool_exp_ask_any(OBJECT(Compile_to_CL,v12208)->arg);
      else if (INHERIT(OWNER(v12208),Language._Call_method))
       { property * v12200 = OBJECT(Call_method,v12208)->arg->selector;
        Result = (((OBJECT(Call_method,v12208)->arg->range == Kernel._boolean) && 
            ((v12200 == Kernel._equal) || 
                ((v12200 == Core._I_equal) || 
                  ((v12200 == Kernel._sup) || 
                    ((v12200 == Kernel._sup_equal) || 
                      ((v12200 == Kernel._inf) || 
                        (v12200 == Kernel._inf_equal))))))) ? CTRUE : (((v12200 == Core.NOT) && 
            (bool_exp_ask_any((*(OBJECT(Call_method,v12208)->args))[1]) == CTRUE)) ? CTRUE : CFALSE));
        }
      else Result = CFALSE;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  args_list_bag(bag *v46356,OID v44140,ClaireBoolean *v48718) { 
    { ClaireBoolean * v46451 = CTRUE;
      if (v48718 == CTRUE)
       _void_(Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        for (START(v46356); NEXT(v12208);)
        if (v46451 == CTRUE)
         { (*Generate.expression)(v12208,
            v44140);
          v46451= (CFALSE);
          }
        else { princ_string(((char*)","));
            if (v48718 == CTRUE)
             breakline_void();
            (*Generate.expression)(v12208,
              v44140);
            }
          }
      if (v48718 == CTRUE)
       _void_(Optimize.OPT->level = ((CL_INT)Optimize.OPT->level-(CL_INT)1));
      }
    POP_SIGNAL;}
  

CL_EXPORT char * check_var_string(char *v46356,OID v12203,OID v44140) { 
    { char *Result ;
      Result = (((equal(_string_(v46356),v12203) == CTRUE) || 
          (equal(_string_(v46356),v44140) == CTRUE)) ?
        append_string(v46356,((char*)"1")) :
        v46356 );
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT Variable * build_Variable_string(char *v12203,OID v12204) { 
    POP_SIGNAL; return (Variable_I_symbol(symbol_I_string2(v12203),0,OBJECT(ClaireType,v12204)));}
  



/***** CLAIRE Compilation of file ./compile/gstat.cl 
         [version 3.5.0 / safety 5] *****/

CL_EXPORT list * unfold_args_list(list *v12196) { 
    
    GC_BIND;
    { list *Result ;
      { list * v31202;
        { { list * v21936 = list::empty(Kernel.emptySet);
            { CL_INT  v12193 = 1;
              CL_INT  v22691 = v12196->length;
              { CL_INT loop_handle = ClEnv->cHandle;
                while (((CL_INT)v12193 <= (CL_INT)v22691))
                { if (c_func_any((*(v12196))[v12193]) != CTRUE)
                   v21936->addFast((OID)((OID)v12193));
                  ++v12193;
                  POP_SIGNAL;}
                }
              }
            v31202 = GC_OBJECT(list,v21936);
            }
          GC_OBJECT(list,v31202);}
        if (should_trace_ask_module1(Generate.it,5) == CTRUE)
         { list * v51781;
          { { OID v_bag;
              GC_ANY(v51781= list::empty(Kernel.emptySet));
              { { list * v21184;{ CL_INT loop_handle = ClEnv->cHandle;
                    bag *v_list; OID v_val;
                    OID v12208; CL_INT CLcount;
                    v_list = v31202;
                     v21184 = v_list->clone();
                    for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                    { v12208 = (*(v_list))[CLcount];
                      v_val = (*(v12196))[v12208];
                      
                      (*((list *) v21184))[CLcount] = v_val;}
                    }
                  
                  v_bag=_oid_(v21184);}
                GC_OID(v_bag);}
              ((list *) v51781)->addFast((OID)v_bag);
              { { list * v21185;{ CL_INT loop_handle = ClEnv->cHandle;
                    bag *v_list; OID v_val;
                    OID v12208; CL_INT CLcount;
                    v_list = v31202;
                     v21185 = v_list->clone();
                    for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                    { v12208 = (*(v_list))[CLcount];
                      v_val = (*Optimize.c_sort)((*(v12196))[v12208]);
                      
                      (*((list *) v21185))[CLcount] = v_val;}
                    }
                  
                  v_bag=_oid_(v21185);}
                GC_OID(v_bag);}
              ((list *) v51781)->addFast((OID)v_bag);
              { { list * v21186;{ CL_INT loop_handle = ClEnv->cHandle;
                    bag *v_list; OID v_val;
                    OID v12208; CL_INT CLcount;
                    v_list = v31202;
                     v21186 = v_list->clone();
                    for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                    { v12208 = (*(v_list))[CLcount];
                      v_val = _oid_(stupid_t_any1((*(v12196))[v12208]));
                      
                      (*((list *) v21186))[CLcount] = v_val;}
                    }
                  
                  v_bag=_oid_(v21186);}
                GC_OID(v_bag);}
              ((list *) v51781)->addFast((OID)v_bag);}
            GC_OBJECT(list,v51781);}
          mtformat_module1(Generate.it,((char*)"unfold -> ~S : ~S - ~S \n"),5,v51781);
          }
        else ;{ CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          bag *v_list; OID v_val;
          OID v12193; CL_INT CLcount;
          v_list = v31202;
           Result = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { GC_LOOP;
            v12193 = (*(v_list))[CLcount];
            { Let * v60472 = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
              _void_(v60472->var = Variable_I_symbol(append_symbol(gensym_void(),_string_(((char*)"UU"))),0,GC_OBJECT(ClaireType,c_type_sort_any((*(v12196))[v12193]))));
              _void_(v60472->value = (*(v12196))[v12193]);
              add_I_property(Kernel.instances,Language._Let,11,_oid_(v60472));
              v_val = _oid_(close_Instruction1(v60472));
              }
            
            (*((list *) Result))[CLcount] = v_val;GC_UNLOOP; POP_SIGNAL;}
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT ClaireType * c_type_sort_any(OID v12208) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { ClaireClass * v12203 = OBJECT(ClaireClass,(*Optimize.c_sort)(v12208));
        ClaireClass * v12204 = stupid_t_any1(v12208);
        if (should_trace_ask_module1(Generate.it,5) == CTRUE)
         mtformat_module1(Generate.it,((char*)"AHA infer a stupid type ~S [sort ~S] in ~S \n"),5,list::alloc(3,_oid_(v12204),
          _oid_(v12203),
          v12208));
        else ;Result = ((v12203 == Kernel._void) ?
          osort_any(GC_OID((*Optimize.c_type)(v12208))) :
          ((boolean_I_any(sort_equal_class(osort_any(_oid_(v12204)),v12203)) == CTRUE) ?
            v12204 :
            v12203 ) );
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  unfold_arg_list(list *v12196,list *v50496,OID v12208) { 
    { OID Result = 0;
      { CL_INT  v12193 = 1;
        CL_INT  v12194 = 0;
        CL_INT  v12197 = v12196->length;
        { ClaireBoolean * g1835I;
          { OID v61842;{ CL_INT loop_handle = ClEnv->cHandle;
              v61842= _oid_(CFALSE);
              while (((CL_INT)v12193 <= (CL_INT)v12197))
              { if (c_func_any((*(v12196))[v12193]) != CTRUE)
                 { ++v12194;
                  if (equal((*(v12196))[v12193],v12208) == CTRUE)
                   { v61842 = Kernel.ctrue;
                    ClEnv->cHandle = loop_handle;break;}
                  }
                else if (equal((*(v12196))[v12193],v12208) == CTRUE)
                 { v61842 = Kernel.cfalse;
                  ClEnv->cHandle = loop_handle;break;}
                ++v12193;
                POP_SIGNAL;}
              }
            
            g1835I=OBJECT(ClaireBoolean,v61842);}
          
          if (g1835I == CTRUE) Result = (*Language.var)((*(v50496))[v12194]);
            else Result = (*(v12196))[v12193];
          }
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  unfold_use_list(list *v33249,OID v12208,OID v12203,OID v44140) { 
    { CL_INT  v12198 = v33249->length;
      CL_INT  v12206 = ClEnv->verbose;
      _void_(ClEnv->verbose = 0);
      if (boolean_I_any(_oid_(v33249)) != CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[internal] design bug c_func(~S) should be true")),
        _oid_(list::alloc(1,v12208)))));
      if (equal((*Optimize.c_type)(v12208),_oid_(Kernel.emptySet)) == CTRUE)
       v12203= (_oid_(Kernel._void));
      { CL_INT  v12193 = 1;
        CL_INT  v22697 = ((CL_INT)v12198-(CL_INT)1);
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)v12193 <= (CL_INT)v22697))
          { write_property(Kernel.arg,OBJECT(ClaireObject,(*(v33249))[v12193]),(*(v33249))[((CL_INT)v12193+(CL_INT)1)]);
            ++v12193;
            POP_SIGNAL;}
          }
        }
      _void_(OBJECT(Let,(*(v33249))[v12198])->arg = v12208);
      _void_(ClEnv->verbose = v12206);
      self_statement_Let(OBJECT(Let,(*(v33249))[1]),v12203,v44140);
      }
    POP_SIGNAL;}
  

CL_EXPORT void  statement_any(OID v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    { ClaireBoolean * v12186 = Optimize.OPT->alloc_stack;
      OID  v50233 = GC_OID((*Optimize.c_type)(v46356));
      ClaireClass * v50635 = psort_any(v50233);
      if ((((INHERIT(OWNER(v46356),Language._Tuple)) || 
          (INHERIT(OWNER(v46356),Language._Do))) ? CTRUE : ((INHERIT(OWNER(v46356),Language._Let)) ? CTRUE : CFALSE)) != CTRUE)
       _void_(Optimize.OPT->alloc_stack = CFALSE);
      if (c_func_any(v46356) == CTRUE)
       { { ClaireBoolean * g1837I;
          { ClaireBoolean *v_and;
            { v_and = ((Kernel._string == OWNER(v12203)) ? CTRUE : CFALSE);
              if (v_and == CFALSE) g1837I =CFALSE; 
              else { { OID  v58508;
                  { OID  v59469;
                    { if (INHERIT(OWNER(v46356),Optimize._to_CL))
                       v59469 = OBJECT(Compile_to_CL,v46356)->arg;
                      else v59469 = v46356;
                        GC_OID(v59469);}
                    v58508 = (*Optimize.c_sort)(v59469);
                    }
                  v_and = ((v58508 != _oid_(Kernel._void)) ? CTRUE : CFALSE);
                  }
                if (v_and == CFALSE) g1837I =CFALSE; 
                else g1837I = CTRUE;}
              }
            }
          
          if (g1837I == CTRUE) { (*Kernel.c_princ)(v12203);
              princ_string(((char*)" = "));
              if (INHERIT(OWNER(v46356),Language._Call_method))
               { if ((v50635 != Kernel._void) && 
                    (v50635 != OBJECT(Call_method,v46356)->arg->range))
                 { princ_string(((char*)"("));
                  interface_I_class(v50635);
                  princ_string(((char*)")"));
                  }
                }
              else if (INHERIT(OWNER(v46356),Optimize._to_C))
               { if ((v50635 != Kernel._void) && 
                    (v50635 != OBJECT(Compile_to_C,v46356)->set_arg))
                 _void_(OBJECT(Compile_to_C,v46356)->set_arg = v50635);
                }
              if (bool_exp_ask_any(v46356) == CTRUE)
               (*Generate.bool_exp_I)(Generate.PRODUCER->value,
                v46356,
                v44140);
              else (*Generate.expression)(v46356,
                  v44140);
                princ_string(((char*)";"));
              breakline_void();
              }
            else if (INHERIT(OWNER(v46356),Language._If))
           (*Generate.self_statement)(v46356,
            v12203,
            v44140);
          else if (INHERIT(OWNER(v46356),Reader._delimiter))
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[201] Loose delimiter in program: ~S")),
            _oid_(list::alloc(1,v46356)))));
          else (*Generate.stat_exp)(Generate.PRODUCER->value,
              v46356,
              v44140);
            }
        }
      else if ((INHERIT(OWNER(v46356),Language._Call_method)) && 
          (((*Kernel.arg)(v46356) == Generate._starclose_exception_star->value) && 
            (c_func_any(GC_OID((*(OBJECT(bag,(*Core.args)(v46356))))[1])) == CTRUE)))
       { (*Generate.expression)(v46356,
          v44140);
        princ_string(((char*)";"));
        breakline_void();
        }
      else (*Generate.self_statement)(v46356,
          v12203,
          v44140);
        _void_(Optimize.OPT->alloc_stack = v12186);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Construct(Construct *v46356,OID v12203,OID v44140) { 
    (*Generate.stat_construct)(Generate.PRODUCER->value,
      _oid_(v46356),
      v12203,
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  self_statement_If(If *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    if (c_func_any(GC_OID(v46356->test)) == CTRUE)
     { princ_string(((char*)"if "));
      (*Optimize.bool_exp)(GC_OID(v46356->test),
        Kernel.ctrue,
        v44140);
      breakline_void();
      princ_string(((char*)" "));
      if (INHERIT(OWNER(v46356->arg),Language._If))
       new_block_void();
      statement_any(GC_OID(v46356->arg),v12203,v44140);
      if (INHERIT(OWNER(v46356->arg),Language._If))
       close_block_void();
      if ((Kernel._string == OWNER(v12203)) || 
          (boolean_I_any(v46356->other) == CTRUE))
       { OID  v50869 = GC_OID(v46356->other);
        if (inherit_ask_class(OWNER(v50869),Language._If) != CTRUE)
         _void_(Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
        princ_string(((char*)"else "));
        statement_any(v50869,v12203,v44140);
        if (inherit_ask_class(OWNER(v50869),Language._If) != CTRUE)
         _void_(Optimize.OPT->level = ((CL_INT)Optimize.OPT->level-(CL_INT)1));
        }
      }
    else { OID  v12206 = GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
          _oid_(append_symbol(gensym_void(),_string_(((char*)"I"))))));
        new_block_void();
        interface_I_class(Kernel._boolean);
        princ_string(((char*)" "));
        princ_string(string_v(v12206));
        princ_string(((char*)";"));
        breakline_void();
        statement_any(GC_OID(v46356->test),v12206,v44140);
        breakline_void();
        _void_(Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
        princ_string(((char*)"if ("));
        princ_string(string_v(v12206));
        princ_string(((char*)" == "));
        (*Generate.produce)(Generate.PRODUCER->value,
          Kernel.ctrue);
        princ_string(((char*)") "));
        statement_any(GC_OID(v46356->arg),v12203,v44140);
        _void_(Optimize.OPT->level = ((CL_INT)Optimize.OPT->level-(CL_INT)1));
        if ((Kernel._string == OWNER(v12203)) || 
            (boolean_I_any(v46356->other) == CTRUE))
         { princ_string(((char*)"else "));
          statement_any(GC_OID(v46356->other),v12203,v44140);
          }
        close_block_void();
        }
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Do(Do *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    if (v46356->args->length == 1)
     statement_any(GC_OID((*(v46356->args))[1]),v12203,v44140);
    else { list * v12196 = GC_OBJECT(list,v46356->args);
        CL_INT  v12197 = v12196->length;
        ClaireBoolean * v12186 = Optimize.OPT->alloc_stack;
        CL_INT  v12198 = 0;
        _void_(Optimize.OPT->alloc_stack = CFALSE);
        new_block_void();
        inner_statement_any(_oid_(v46356),v12203,v44140);
        close_block_void();
        }
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  inner_statement_any(OID v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    if (INHERIT(OWNER(v46356),Language._Do))
     { list * v12196 = GC_OBJECT(list,OBJECT(Do,v46356)->args);
      CL_INT  v12197 = v12196->length;
      ClaireBoolean * v12186 = Optimize.OPT->alloc_stack;
      CL_INT  v12198 = 0;
      _void_(Optimize.OPT->alloc_stack = CFALSE);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        for (START(v12196); NEXT(v12208);)
        { ++v12198;
          if (v12198 == v12197)
           { _void_(Optimize.OPT->alloc_stack = v12186);
            inner_statement_any(v12208,v12203,v44140);
            }
          else if (boolean_I_any(v12208) == CTRUE)
           inner_statement_any(v12208,_oid_(Kernel.emptySet),v44140);
          }
        }
      }
    else statement_any(v46356,v12203,v44140);
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Let(Let *v46356,OID v12203,OID v44140) { 
    (*Generate.stat_let)(Generate.PRODUCER->value,
      _oid_(v46356),
      v12203,
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  self_statement_And(And *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    { char * v12206 = GC_STRING(check_var_string(((char*)"v_and"),v12203,v44140));
      new_block_void();
      interface_I_class(Kernel._boolean);
      princ_string(v12206);
      princ_string(((char*)";"));
      breakline_void();
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        bag *v12208_support;
        v12208_support = GC_OBJECT(list,v46356->args);
        for (START(v12208_support); NEXT(v12208);)
        { new_block_void();
          statement_any(v12208,_string_(v12206),v44140);
          princ_string(((char*)"if ("));
          princ_string(v12206);
          princ_string(((char*)" == "));
          (*Generate.produce)(Generate.PRODUCER->value,
            Kernel.cfalse);
          princ_string(((char*)") "));
          if (Kernel._string == OWNER(v12203))
           { c_princ_string(string_v(v12203));
            princ_string(((char*)" ="));
            }
          expression_boolean(CFALSE,v44140);
          princ_string(((char*)"; "));
          breakline_void();
          princ_string(((char*)"else "));
          }
        }
      if (Kernel._string == OWNER(v12203))
       { c_princ_string(string_v(v12203));
        princ_string(((char*)" = "));
        expression_boolean(CTRUE,v44140);
        princ_string(((char*)";"));
        }
      else { expression_boolean(CTRUE,v44140);
          princ_string(((char*)";"));
          }
        { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        bag *v12208_support;
        v12208_support = GC_OBJECT(list,v46356->args);
        for (START(v12208_support); NEXT(v12208);)
        close_block_void();
        }
      close_block_void();
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Or(Or *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    { char * v12206 = GC_STRING(check_var_string(((char*)"v_or"),v12203,v44140));
      new_block_void();
      interface_I_class(Kernel._boolean);
      princ_string(v12206);
      princ_string(((char*)";"));
      breakline_void();
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        bag *v12208_support;
        v12208_support = GC_OBJECT(list,v46356->args);
        for (START(v12208_support); NEXT(v12208);)
        { new_block_void();
          statement_any(v12208,_string_(v12206),v44140);
          princ_string(((char*)"if ("));
          princ_string(v12206);
          princ_string(((char*)" == "));
          (*Generate.produce)(Generate.PRODUCER->value,
            Kernel.ctrue);
          princ_string(((char*)") "));
          if (Kernel._string == OWNER(v12203))
           { c_princ_string(string_v(v12203));
            princ_string(((char*)" ="));
            }
          expression_boolean(CTRUE,v44140);
          princ_string(((char*)"; "));
          breakline_void();
          princ_string(((char*)"else "));
          }
        }
      if (Kernel._string == OWNER(v12203))
       { c_princ_string(string_v(v12203));
        princ_string(((char*)" = "));
        expression_boolean(CFALSE,v44140);
        princ_string(((char*)";"));
        }
      else { expression_boolean(CFALSE,v44140);
          princ_string(((char*)";"));
          }
        { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        bag *v12208_support;
        v12208_support = GC_OBJECT(list,v46356->args);
        for (START(v12208_support); NEXT(v12208);)
        close_block_void();
        }
      close_block_void();
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_While(While *v46356,OID v12203,OID v44140) { 
    (*Generate.stat_while)(Generate.PRODUCER->value,
      _oid_(v46356),
      v12203,
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Assign(Assign *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    { OID  v12206 = GC_OID(v46356->var);
      OID  v12208 = GC_OID(v46356->arg);
      ClaireBoolean * v48310 = ((boolean_I_any(v44140) == CTRUE) ? ((Optimize.OPT->loop_gc == CTRUE) ? ((inner2outer_ask_any(v12208) == CTRUE) ? CTRUE: CFALSE): CFALSE): CFALSE);
      OID  v12209;
      { if ((v48310 == CTRUE) && 
            (INHERIT(OWNER(v12208),Optimize._to_protect)))
         v12209 = (*Kernel.arg)(v12208);
        else v12209 = v12208;
          GC_OID(v12209);}
      if (Kernel._string == OWNER(v12203))
       { new_block_void();
        statement_any(v12209,v12203,v44140);
        princ_string(((char*)" "));
        if (v48310 == CTRUE)
         (*Generate.gc_protection_exp)(Generate.PRODUCER->value,
          v12206,
          Kernel.cfalse,
          v12203,
          v44140);
        else { ident_symbol(OBJECT(Variable,v12206)->pname);
            princ_string(((char*)" = "));
            (*Kernel.c_princ)(v12203);
            }
          princ_string(((char*)";"));
        close_block_void();
        }
      else if (v48310 == CTRUE)
       { new_block_void();
        statement_any(v12209,GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
          v12206)),v44140);
        princ_string(((char*)" "));
        (*Generate.gc_protection_exp)(Generate.PRODUCER->value,
          v12206,
          Kernel.ctrue,
          v12206,
          v44140);
        princ_string(((char*)";"));
        close_block_void();
        }
      else statement_any(v12208,GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
          v12206)),v44140);
        }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Gassign(Gassign *v46356,OID v12203,OID v44140) { 
    (*Generate.stat_gassign)(Generate.PRODUCER->value,
      _oid_(v46356),
      v12203,
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  self_statement_to_protect(Compile_to_protect *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    if ((Optimize.OPT->protection == CTRUE) && 
        (Kernel._string == OWNER(v12203)))
     { ClaireClass * v12187 = OBJECT(ClaireClass,(*Optimize.c_sort)(GC_OID(v46356->arg)));
      new_block_void();
      statement_any(GC_OID(v46356->arg),v12203,v44140);
      princ_string(gc_protect_class(v12187));
      princ_string(((char*)"("));
      if (INHERIT(v12187,Kernel._object))
       { class_princ_class(psort_any(GC_OID((*Optimize.c_type)(GC_OID(v46356->arg)))));
        princ_string(((char*)","));
        }
      (*Kernel.c_princ)(v12203);
      princ_string(((char*)");"));
      close_block_void();
      }
    else statement_any(GC_OID(v46356->arg),v12203,v44140);
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_For(For *v46356,OID v12203,OID v44140) { 
    (*Generate.stat_for)(Generate.PRODUCER->value,
      _oid_(v46356),
      v12203,
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Iteration(Iteration *v46356,OID v12203,OID v44140) { 
    (*Generate.stat_iteration)(Generate.PRODUCER->value,
      _oid_(v46356),
      v12203,
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Return(Return *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    if (v44140 == CNULL)
     { new_block_void();
      statement_any(GC_OID(v46356->arg),_oid_(Kernel.emptySet),_oid_(Kernel.emptySet));
      if (Optimize.OPT->loop_gc == CTRUE)
       princ_string(((char*)"GC_UNLOOP;"));
      princ_string(((char*)"ClEnv->cHandle = loop_handle; break;"));
      close_block_void();
      }
    else if (Kernel._string == OWNER(v44140))
     { new_block_void();
      if (Optimize.OPT->loop_gc == CTRUE)
       princ_string(((char*)"GC_UNLOOP;"));
      statement_any(GC_OID(v46356->arg),v44140,_oid_(Kernel.emptySet));
      princ_string(((char*)"ClEnv->cHandle = loop_handle;break;"));
      close_block_void();
      }
    else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[204] break not inside a For or While:~S")),
        _oid_(list::alloc(1,_oid_(v46356))))));
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Call(Call *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    { list * v12196 = GC_OBJECT(list,v46356->args);
      list * v50496 = GC_OBJECT(list,unfold_args_list(v12196));
      Call * v12187;
      { { Instruction *V_CC ;
          { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            _void_(v60472->selector = v46356->selector);
            add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
            V_CC = close_Instruction1(v60472);
            }
          v12187= (Call *) V_CC;}
        GC_OBJECT(Call,v12187);}
      { Call * v22726 = v12187; 
        list * v22727;
        { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v12210; CL_INT CLcount;
          v_list = v12196;
           v22727 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v12210 = (*(v_list))[CLcount];
            v_val = unfold_arg_list(v12196,v50496,v12210);
            
            (*((list *) v22727))[CLcount] = v_val;}
          }
        _void_(v22726->args = v22727);}
      unfold_use_list(v50496,_oid_(v12187),v12203,v44140);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Call_method(Call_method *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    { list * v12196 = GC_OBJECT(list,v46356->args);
      list * v50496 = GC_OBJECT(list,unfold_args_list(v12196));
      Call_method * v12187;
      { { Instruction *V_CC ;
          { Call_method * v60472 = ((Call_method *) GC_OBJECT(Call_method,new_object_class(Language._Call_method)));
            _void_(v60472->arg = v46356->arg);
            add_I_property(Kernel.instances,Language._Call_method,11,_oid_(v60472));
            V_CC = close_Instruction1(v60472);
            }
          v12187= (Call_method *) V_CC;}
        GC_OBJECT(Call_method,v12187);}
      { Call_method * v22728 = v12187; 
        list * v22729;
        { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v12210; CL_INT CLcount;
          v_list = v12196;
           v22729 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v12210 = (*(v_list))[CLcount];
            v_val = unfold_arg_list(v12196,v50496,v12210);
            
            (*((list *) v22729))[CLcount] = v_val;}
          }
        _void_(v22728->args = v22729);}
      unfold_use_list(v50496,_oid_(v12187),v12203,v44140);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Call_method1(Call_method1 *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    { list * v12196 = GC_OBJECT(list,v46356->args);
      list * v50496 = GC_OBJECT(list,unfold_args_list(v12196));
      Call_method1 * v12187;
      { { Instruction *V_CC ;
          { Call_method1 * v60472 = ((Call_method1 *) GC_OBJECT(Call_method1,new_object_class(Language._Call_method1)));
            _void_(v60472->arg = v46356->arg);
            add_I_property(Kernel.instances,Language._Call_method1,11,_oid_(v60472));
            V_CC = close_Instruction1(v60472);
            }
          v12187= (Call_method1 *) V_CC;}
        GC_OBJECT(Call_method1,v12187);}
      { Call_method * v22730 = v12187; 
        list * v22731;
        { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v12210; CL_INT CLcount;
          v_list = v12196;
           v22731 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v12210 = (*(v_list))[CLcount];
            v_val = unfold_arg_list(v12196,v50496,v12210);
            
            (*((list *) v22731))[CLcount] = v_val;}
          }
        _void_(v22730->args = v22731);}
      unfold_use_list(v50496,_oid_(v12187),v12203,v44140);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Call_method2(Call_method2 *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    { list * v12196 = GC_OBJECT(list,v46356->args);
      list * v50496 = GC_OBJECT(list,unfold_args_list(v12196));
      Call_method2 * v12187;
      { { Instruction *V_CC ;
          { Call_method2 * v60472 = ((Call_method2 *) GC_OBJECT(Call_method2,new_object_class(Language._Call_method2)));
            _void_(v60472->arg = v46356->arg);
            add_I_property(Kernel.instances,Language._Call_method2,11,_oid_(v60472));
            V_CC = close_Instruction1(v60472);
            }
          v12187= (Call_method2 *) V_CC;}
        GC_OBJECT(Call_method2,v12187);}
      { Call_method * v22753 = v12187; 
        list * v22754;
        { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v12210; CL_INT CLcount;
          v_list = v12196;
           v22754 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v12210 = (*(v_list))[CLcount];
            v_val = unfold_arg_list(v12196,v50496,v12210);
            
            (*((list *) v22754))[CLcount] = v_val;}
          }
        _void_(v22753->args = v22754);}
      unfold_use_list(v50496,_oid_(v12187),v12203,v44140);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Super(Super *v46356,OID v12203,OID v44140) { 
    (*Generate.stat_super)(Generate.PRODUCER->value,
      _oid_(v46356),
      v12203,
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Cast(Cast *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    statement_any(GC_OID(v46356->arg),v12203,v44140);
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Handle(ClaireHandle *v46356,OID v12203,OID v44140) { 
    (*Generate.stat_handle)(Generate.PRODUCER->value,
      _oid_(v46356),
      v12203,
      v44140);
    POP_SIGNAL;}
  

CL_EXPORT void  self_statement_to_CL(Compile_to_CL *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    if (Kernel._string == OWNER(v12203))
     { Variable * v1000 = GC_OBJECT(Variable,build_Variable_string(string_I_symbol(gensym_string(((char*)"V_CL"))),_oid_(v46356->set_arg)));
      ClaireClass * v50666 = ((v46356->set_arg == Kernel._void) ?
        Kernel._any :
        v46356->set_arg );
      new_block_void();
      interface_I_class(v50666);
      princ_string(((char*)" "));
      expression_Variable(v1000,v44140);
      princ_string(((char*)";"));
      statement_any(GC_OID(v46356->arg),GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
        _oid_(v1000))),v44140);
      breakline_void();
      princ_string(string_v(v12203));
      princ_string(((char*)"="));
      (*Generate.to_cl)(Generate.PRODUCER->value,
        _oid_(v1000),
        _oid_(v46356->set_arg),
        v44140);
      princ_string(((char*)";"));
      close_block_void();
      }
    else statement_any(GC_OID(v46356->arg),v12203,v44140);
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_to_C(Compile_to_C *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    if (Kernel._string == OWNER(v12203))
     { Variable * v1000 = GC_OBJECT(Variable,build_Variable_string(((char*)"V_C"),_oid_(Kernel._any)));
      new_block_void();
      (*Generate.any_interface)(Generate.PRODUCER->value);
      princ_string(((char*)" "));
      (*Language.ident)(Generate.PRODUCER->value,
        _oid_(v1000));
      princ_string(((char*)";"));
      statement_any(GC_OID(v46356->arg),GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
        _oid_(v1000))),v44140);
      breakline_void();
      princ_string(string_v(v12203));
      princ_string(((char*)"="));
      (*Generate.to_c)(Generate.PRODUCER->value,
        _oid_(v1000),
        _oid_(v46356->set_arg),
        v44140);
      princ_string(((char*)";"));
      close_block_void();
      }
    else statement_any(GC_OID(v46356->arg),v12203,v44140);
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_C_cast(Compile_C_cast *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    if (Kernel._string == OWNER(v12203))
     { char * v1000 = GC_STRING(check_var_string(((char*)"V_CC"),v12203,v44140));
      ClaireClass * v50666 = v46356->set_arg;
      ClaireClass * v50667 = stupid_t_any1(GC_OID(v46356->arg));
      ClaireType * v50697 = join_class(osort_any(_oid_(v50666)),v50667);
      new_block_void();
      (*Generate.define_variable)(Generate.PRODUCER->value,
        _oid_(v50697),
        _string_(v1000));
      breakline_void();
      statement_any(GC_OID(v46356->arg),_string_(v1000),v44140);
      princ_string(string_v(v12203));
      princ_string(((char*)"= "));
      (*Generate.pointer_cast)(Generate.PRODUCER->value,
        _oid_(v50666));
      princ_string(((char*)" "));
      princ_string(v1000);
      princ_string(((char*)";"));
      close_block_void();
      }
    else statement_any(GC_OID(v46356->arg),v12203,v44140);
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Call_slot(Call_slot *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    { char * v41084 = string_I_symbol(gensym_void());
      Variable * v1000 = GC_OBJECT(Variable,build_Variable_string(v41084,GC_OID((*Optimize.c_type)(GC_OID(v46356->arg)))));
      new_block_void();
      interface_I_class(sort_Variable(v1000));
      princ_string(((char*)" "));
      expression_Variable(v1000,_oid_(Kernel.emptySet));
      princ_string(((char*)";"));
      breakline_void();
      statement_any(GC_OID(v46356->arg),_string_(v41084),v44140);
      breakline_void();
      if (Kernel._string == OWNER(v12203))
       { c_princ_string(string_v(v12203));
        princ_string(((char*)" = "));
        }
      { Call_slot * v46787;
        { { Instruction *V_CC ;
            { Call_slot * v60472 = ((Call_slot *) GC_OBJECT(Call_slot,new_object_class(Language._Call_slot)));
              _void_(v60472->selector = v46356->selector);
              _void_(v60472->arg = _oid_(v1000));
              add_I_property(Kernel.instances,Language._Call_slot,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v46787= (Call_slot *) V_CC;}
          GC_OBJECT(Call_slot,v46787);}
        expression_Call_slot(v46787,v44140);
        }
      princ_string(((char*)";"));
      close_block_void();
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Call_table(Call_table *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    { char * v41084 = string_I_symbol(gensym_void());
      Variable * v1000 = GC_OBJECT(Variable,build_Variable_string(v41084,GC_OID((*Optimize.c_type)(GC_OID(v46356->arg)))));
      new_block_void();
      interface_I_class(sort_Variable(v1000));
      princ_string(((char*)" "));
      expression_Variable(v1000,_oid_(Kernel.emptySet));
      princ_string(((char*)";"));
      breakline_void();
      statement_any(GC_OID(v46356->arg),_string_(v41084),v44140);
      breakline_void();
      if (Kernel._string == OWNER(v12203))
       { c_princ_string(string_v(v12203));
        princ_string(((char*)" = "));
        }
      { Call_table * v47749;
        { { Instruction *V_CC ;
            { Call_table * v60472 = ((Call_table *) GC_OBJECT(Call_table,new_object_class(Language._Call_table)));
              _void_(v60472->selector = v46356->selector);
              _void_(v60472->arg = _oid_(v1000));
              add_I_property(Kernel.instances,Language._Call_table,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v47749= (Call_table *) V_CC;}
          GC_OBJECT(Call_table,v47749);}
        expression_Call_table(v47749,v44140);
        }
      princ_string(((char*)";"));
      close_block_void();
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Call_array(Call_array *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    { Variable * v31049 = GC_OBJECT(Variable,build_Variable_string(((char*)"va_arg1"),_oid_(Kernel._array)));
      Variable * v31050 = GC_OBJECT(Variable,build_Variable_string(((char*)"va_arg2"),_oid_(Kernel._integer)));
      new_block_void();
      interface_I_class(Kernel._array);
      princ_string(((char*)" "));
      expression_Variable(v31049,_oid_(Kernel.emptySet));
      princ_string(((char*)";"));
      breakline_void();
      interface_I_class(Kernel._integer);
      princ_string(((char*)" "));
      expression_Variable(v31050,_oid_(Kernel.emptySet));
      princ_string(((char*)";"));
      breakline_void();
      statement_any(GC_OID(v46356->selector),_string_(((char*)"va_arg1")),v44140);
      statement_any(GC_OID(v46356->arg),_string_(((char*)"va_arg2")),v44140);
      if (Kernel._string == OWNER(v12203))
       { c_princ_string(string_v(v12203));
        princ_string(((char*)" = "));
        }
      { Call_array * v48709;
        { { Instruction *V_CC ;
            { Call_array * v60472 = ((Call_array *) GC_OBJECT(Call_array,new_object_class(Language._Call_array)));
              _void_(v60472->selector = _oid_(v31049));
              _void_(v60472->arg = _oid_(v31050));
              _void_(v60472->test = v46356->test);
              add_I_property(Kernel.instances,Language._Call_array,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v48709= (Call_array *) V_CC;}
          GC_OBJECT(Call_array,v48709);}
        expression_Call_array(v48709,v44140);
        }
      princ_string(((char*)";"));
      close_block_void();
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  self_statement_Update(Update *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    { OID  v12176 = GC_OID(v46356->var);
      OID  v12200 = GC_OID(v46356->selector);
      ClaireType * v50665;
      { if (INHERIT(OWNER(v12176),Language._Call_slot))
         v50665 = domain_I_restriction(OBJECT(Call_slot,v12176)->selector);
        else if (INHERIT(OWNER(v12176),Language._Call_array))
         v50665 = Kernel._integer;
        else v50665 = U_type(Kernel._any,GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.domain)(v12200))));
          GC_OBJECT(ClaireType,v50665);}
      ClaireType * v50666;
      { if (INHERIT(OWNER(v12176),Language._Call_slot))
         { v50666 = ((v46356->arg == _oid_(Kernel.add)) ?
            member_type(OBJECT(Call_slot,v12176)->selector->range) :
            OBJECT(Call_slot,v12176)->selector->range );
          }
        else if (INHERIT(OWNER(v12176),Language._Call_array))
         { v50666 = (((OBJECT(ClaireBoolean,(*Core._inf_equalt)(GC_OID(OBJECT(Call_array,v12176)->test),
            _oid_(Kernel._float)))) == CTRUE) ?
            Kernel._float :
            Kernel._any );
          }
        else v50666 = U_type(Kernel._any,GC_OBJECT(ClaireType,((v46356->arg == _oid_(Kernel.add)) ?
            member_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(v12200)))) :
            OBJECT(ClaireType,(*Kernel.range)(v12200)) )));
          GC_OBJECT(ClaireType,v50666);}
      ClaireClass * v65289 = stupid_t_any1(GC_OID((*Kernel.arg)(v46356->var)));
      ClaireClass * v65290 = stupid_t_any1(GC_OID(v46356->value));
      OID  v12761;
      { if ((_inf_equalt_class(v65289,psort_any(_oid_(v50665))) != CTRUE) && 
            (_inf_equalt_class(v65289,Kernel._object) == CTRUE))
         { Compile_C_cast * v60472 = ((Compile_C_cast *) GC_OBJECT(Compile_C_cast,new_object_class(Optimize._C_cast)));
          _void_(v60472->arg = (*Kernel.arg)(GC_OID(v46356->var)));
          _void_(v60472->set_arg = psort_any(_oid_(v50665)));
          add_I_property(Kernel.instances,Optimize._C_cast,11,_oid_(v60472));
          v12761 = _oid_(close_Instruction1(v60472));
          }
        else v12761 = (*Kernel.arg)(GC_OID(v46356->var));
          GC_OID(v12761);}
      OID  v29748;
      { if ((_inf_equalt_class(v65290,psort_any(_oid_(v50666))) != CTRUE) && 
            (_inf_equalt_class(v65290,Kernel._object) == CTRUE))
         { Compile_C_cast * v60472 = ((Compile_C_cast *) GC_OBJECT(Compile_C_cast,new_object_class(Optimize._C_cast)));
          _void_(v60472->arg = v46356->value);
          _void_(v60472->set_arg = psort_any(_oid_(v50666)));
          add_I_property(Kernel.instances,Optimize._C_cast,11,_oid_(v60472));
          v29748 = _oid_(close_Instruction1(v60472));
          }
        else v29748 = v46356->value;
          GC_OID(v29748);}
      Variable * v31049 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,v50665));
      Variable * v31050 = GC_OBJECT(Variable,Variable_I_symbol(gensym_void(),0,v50666));
      ClaireBoolean * v50135 = c_func_any(v12761);
      new_block_void();
      interface_I_class(psort_any(_oid_(v50665)));
      princ_string(((char*)" "));
      expression_Variable(v31049,_oid_(Kernel.emptySet));
      princ_string(((char*)" "));
      if (v50135 == CTRUE)
       { princ_string(((char*)"= "));
        (*Generate.expression)(v12761,
          _oid_(Kernel.emptySet));
        }
      princ_string(((char*)"; "));
      breakline_void();
      interface_I_class(psort_any(_oid_(v50666)));
      princ_string(((char*)" "));
      expression_Variable(v31050,_oid_(Kernel.emptySet));
      princ_string(((char*)";"));
      breakline_void();
      if (v50135 != CTRUE)
       statement_any(v12761,GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
        _oid_(v31049))),v44140);
      statement_any(v29748,GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
        _oid_(v31050))),v44140);
      if (Kernel._string == OWNER(v12203))
       { c_princ_string(string_v(v12203));
        princ_string(((char*)" = "));
        }
      { Update * v49670;
        { { Instruction *V_CC ;
            { Update * v60472 = ((Update *) GC_OBJECT(Update,new_object_class(Language._Update)));
              _void_(v60472->selector = v12200);
              { Update * v22759 = v60472; 
                OID  v22760;
                if (v46356->arg == _oid_(Kernel.add))
                 v22760 = _oid_(Kernel.add);
                else if (sort_Variable(v31049) == Kernel._any)
                 v22760 = _oid_(v31049);
                else { Compile_to_CL * v60472 = ((Compile_to_CL *) GC_OBJECT(Compile_to_CL,new_object_class(Optimize._to_CL)));
                    _void_(v60472->arg = _oid_(v31049));
                    _void_(v60472->set_arg = sort_Variable(v31049));
                    add_I_property(Kernel.instances,Optimize._to_CL,11,_oid_(v60472));
                    v22760 = _oid_(close_Instruction1(v60472));
                    }
                  _void_(v22759->arg = v22760);}
              _void_(v60472->value = _oid_(v31050));
              { Update * v22761 = v60472; 
                OID  v22762;
                { OID  v50888 = GC_OID((*Kernel.copy)(v12176));
                  put_property2(Kernel.arg,OBJECT(ClaireObject,v50888),_oid_(v31049));
                  v22762 = v50888;
                  }
                _void_(v22761->var = v22762);}
              add_I_property(Kernel.instances,Language._Update,11,_oid_(v60472));
              V_CC = close_Instruction1(v60472);
              }
            v49670= (Update *) V_CC;}
          GC_OBJECT(Update,v49670);}
        expression_Update(v49670,v44140);
        }
      princ_string(((char*)";"));
      close_block_void();
      }
    GC_UNBIND; POP_SIGNAL;}
  



/***** CLAIRE Compilation of file ./compile/cgen.cl 
         [version 3.5.0 / safety 5] *****/

CL_EXPORT char * c_string_c_producer1(Generate_c_producer *v12187,Variable *v46356) { 
    
    GC_BIND;
    { char *Result ;
      if (Optimize.compiler->naming == 2)
       Result = append_string(((char*)"v"),GC_STRING(string_I_integer (integer_I_symbol(v46356->pname))));
      else { print_in_string_void();
          ident_c_producer(v12187,v46356->pname);
          Result = end_of_string_void();
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT char * c_string_c_producer2(Generate_c_producer *v12187,symbol *v46356) { 
    print_in_string_void();
    ident_c_producer(v12187,v46356);
    POP_SIGNAL; return (end_of_string_void());}
  

CL_EXPORT char * string_I_c_producer1(Generate_c_producer *v12187,Variable *v46356) { 
    
    GC_BIND;
    { char *Result ;
      if (Optimize.compiler->naming == 2)
       Result = append_string(((char*)"v"),GC_STRING(string_I_integer (integer_I_symbol(v46356->pname))));
      else { print_in_string_void();
          ident_c_producer(v12187,v46356->pname);
          Result = end_of_string_void();
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT char * string_I_c_producer2(Generate_c_producer *v12187,symbol *v46356) { 
    print_in_string_void();
    ident_c_producer(v12187,v46356);
    POP_SIGNAL; return (end_of_string_void());}
  

CL_EXPORT void  ident_c_producer3(Generate_c_producer *v12187,Variable *v12206) { 
    
    GC_BIND;
    if (Optimize.compiler->naming == 2)
     princ_string(append_string(((char*)"v"),GC_STRING(string_I_integer (integer_I_symbol(v12206->pname)))));
    else { symbol * v12203 = v12206->pname;
        CL_INT  v12198 = index_list(v12187->bad_names,_oid_(v12203));
        if (v12198 == 0)
         { if ((LENGTH_STRING(v12203->name) == 2) && 
              (v12203->name[1 - 1] == ((unsigned char)'_')))
           princ_string(((char*)"us"));
          c_princ_string(string_I_symbol(v12203));
          }
        else c_princ_symbol(OBJECT(symbol,(*(v12187->good_names))[v12198]));
          }
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  ident_c_producer(Generate_c_producer *v12187,symbol *v12203) { 
    { CL_INT  v12198 = index_list(v12187->bad_names,_oid_(v12203));
      if (v12198 == 0)
       { if ((LENGTH_STRING(v12203->name) == 2) && 
            (v12203->name[1 - 1] == ((unsigned char)'_')))
         princ_string(((char*)"us"));
        c_princ_string(string_I_symbol(v12203));
        }
      else c_princ_symbol(OBJECT(symbol,(*(v12187->good_names))[v12198]));
        }
    POP_SIGNAL;}
  

CL_EXPORT void  class_princ_c_producer(Generate_c_producer *v12187,ClaireClass *v46356) { 
    if (v46356->name->module_I != claire.it)
     { ident_c_producer(v12187,v46356->name->module_I->name);
      princ_string(((char*)"_"));
      }
    ident_c_producer(v12187,v46356->name);
    POP_SIGNAL;}
  

CL_EXPORT void  produce_c_producer2(Generate_c_producer *v12187,OID v12208) { 
    if (INHERIT(OWNER(v12208),Kernel._function))
     { princ_string(((char*)"_function_("));
      c_princ_function(OBJECT(ClaireFunction,v12208));
      princ_string(((char*)","));
      print_any(_string_(string_I_function(OBJECT(ClaireFunction,v12208))));
      princ_string(((char*)")"));
      }
    else if (INHERIT(OWNER(v12208),Kernel._char))
     { princ_string(((char*)"_char_(((unsigned char)"));
      print_any(v12208);
      princ_string(((char*)"))"));
      }
    else if (INHERIT(OWNER(v12208),Kernel._environment))
     princ_string(((char*)"ClEnv"));
    else if (Kernel._string == OWNER(v12208))
     { princ_string(((char*)"((char*)"));
      print_any(v12208);
      princ_string(((char*)")"));
      }
    else if (INHERIT(OWNER(v12208),Core._global_variable))
     globalVar_c_producer(v12187,OBJECT(global_variable,v12208));
    else if (Kernel._boolean == OWNER(v12208))
     { if ((OBJECT(ClaireBoolean,v12208)) == CTRUE)
       princ_string(((char*)"CTRUE"));
      else princ_string(((char*)"CFALSE"));
        }
    else if (INHERIT(OWNER(v12208),Kernel._symbol))
     { princ_string(((char*)"symbol::make("));
      print_any(_string_(string_I_symbol(OBJECT(symbol,v12208))));
      princ_string(((char*)","));
      ident_symbol(OBJECT(symbol,v12208)->module_I->name);
      princ_string(((char*)","));
      ident_symbol(defined_symbol(OBJECT(symbol,v12208))->name);
      princ_string(((char*)")"));
      }
    else if (INHERIT(OWNER(v12208),Kernel._class))
     { if (v12208 == _oid_(Kernel._cl_import))
       princ_string(((char*)"Kernel._cl_import"));
      else { ident_c_producer(v12187,defined_symbol(OBJECT(ClaireClass,v12208)->name)->name);
          princ_string(((char*)"._"));
          c_princ_string(string_I_symbol(OBJECT(ClaireClass,v12208)->name));
          }
        }
    else if (INHERIT(OWNER(v12208),Reader._reserved_keyword))
     { ident_c_producer(v12187,defined_symbol(OBJECT(thing,v12208)->name)->name);
      princ_string(((char*)"._cl_"));
      c_princ_string(string_I_symbol(OBJECT(thing,v12208)->name));
      }
    else if (INHERIT(OWNER(v12208),Kernel._thing))
     { if (INHERIT(OBJECT(ClaireObject,v12208)->isa,Kernel._module))
       { ident_c_producer(v12187,OBJECT(thing,v12208)->name);
        princ_string(((char*)".it"));
        }
      else { ident_c_producer(v12187,defined_symbol(OBJECT(thing,v12208)->name)->name);
          princ_string(((char*)"."));
          ident_symbol(OBJECT(thing,v12208)->name);
          }
        }
    else princ_string(((char*)"CNULL"));
      POP_SIGNAL;}
  

CL_EXPORT void  globalVar_c_producer(Generate_c_producer *v12187,global_variable *v12208) { 
    
    GC_BIND;
    if ((equal(_oid_(v12208->range),_oid_(Kernel.emptySet)) == CTRUE) && 
        (INHERIT(OWNER(v12208->value),Kernel._integer)))
     { princ_string(((char*)"(OID)("));
      print_any(GC_OID(v12208->value));
      princ_string(((char*)")"));
      }
    else { ident_c_producer(v12187,defined_symbol(v12208->name)->name);
        princ_string(((char*)"."));
        ident_symbol(v12208->name);
        if (nativeVar_ask_global_variable(v12208) != CTRUE)
         princ_string(((char*)"->value"));
        else ;}
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  stat_exp_c_producer(Generate_c_producer *v12187,OID v46356,OID v44140) { 
    
    GC_BIND;
    if (INHERIT(OWNER(v46356),Optimize._to_C))
     stat_exp_c_producer(v12187,GC_OID(OBJECT(Compile_to_C,v46356)->arg),v44140);
    else if (INHERIT(OWNER(v46356),Optimize._to_CL))
     stat_exp_c_producer(v12187,GC_OID(OBJECT(Compile_to_CL,v46356)->arg),v44140);
    else if (designated_ask_any(v46356) == CTRUE)
     princ_string(((char*)";"));
    else { (*Generate.expression)(v46356,
          v44140);
        princ_string(((char*)";"));
        breakline_void();
        }
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  namespace_I_c_producer(Generate_c_producer *v12187,module *v12197) { 
    princ_string(((char*)"\n\n// namespace class for "));
    print_any(_oid_(v12197));
    princ_string(((char*)" \n"));
    { princ_string(((char*)"class CL_EXPORT "));
      ident_c_producer(v12187,v12197->name);
      princ_string(((char*)"Class: public NameSpace {\npublic:\n"));
      }
    POP_SIGNAL;}
  

CL_EXPORT void  module_I_c_producer(Generate_c_producer *v12187,module *v12197) { 
    princ_string(((char*)"\n\n// module definition \n"));
    princ_string(((char*)" void metaLoad();};\n\n"));
    princ_string(((char*)"extern CL_EXPORT "));
    ident_c_producer(v12187,v12197->name);
    princ_string(((char*)"Class "));
    ident_c_producer(v12187,v12197->name);
    princ_string(((char*)";\n"));
    { module * v50476 = v12197;
      module * v50477 = v50476->part_of;
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((boolean_I_any(_oid_(v50477->made_of)) != CTRUE) && 
            ((v50477 != claire.it) && 
              ((*(v50477->parts))[1] == _oid_(v50476)))))
        { princ_string(((char*)"extern CL_EXPORT NameSpace "));
          (*Language.ident)(Generate.PRODUCER->value,
            _oid_(v50477->name));
          princ_string(((char*)";\n"));
          v50477= (v50477->part_of);
          v50476= (v50477);
          POP_SIGNAL;}
        }
      }
    POP_SIGNAL;}
  

CL_EXPORT void  declare_c_producer(Generate_c_producer *v12187,property *v12200) { 
    breakline_void();
    { expression_thing(v12200,Core.nil->value);
      princ_string(((char*)" = "));
      princ_string(((INHERIT(v12200->isa,Kernel._operation)) ?
        ((char*)"operation") :
        ((char*)"property") ));
      princ_string(((char*)"::make("));
      print_any(_string_(string_I_symbol(v12200->name)));
      princ_string(((char*)","));
      if ((v12200->open != 1) || 
          ((CL_INT)v12200->dispatcher > (CL_INT)0))
       { expression_integer(v12200->open,_oid_(Kernel.emptySet));
        princ_string(((char*)","));
        }
      expression_thing(v12200->name->module_I,Core.nil->value);
      if (INHERIT(v12200->isa,Kernel._operation))
       { princ_string(((char*)","));
        princ_integer(CLREAD(operation,v12200,precedence));
        }
      else if ((CL_INT)v12200->dispatcher > (CL_INT)0)
       { princ_string(((char*)","));
        (*Generate.expression)(_oid_(v12200->domain),
          Core.nil->value);
        princ_string(((char*)","));
        princ_integer(v12200->dispatcher);
        }
      princ_string(((char*)");"));
      if (boolean_I_any(_oid_(v12200->reified)) == CTRUE)
       { princ_string(((char*)" "));
        expression_thing(v12200,Core.nil->value);
        princ_string(((char*)"->reified = CTRUE;"));
        }
      else ;}
    POP_SIGNAL;}
  

CL_EXPORT void  start_module_interface_c_producer(Generate_c_producer *v12187,module *v46356) { 
    
    GC_BIND;
    { char * v13948 = GC_STRING(append_string(GC_STRING(Optimize.compiler->headers_dir),GC_STRING(append_string(GC_STRING(append_string(GC_STRING(string_v(Core._starfs_star->value)),GC_STRING(c_string_c_producer2(v12187,v46356->name)))),((char*)".h")))));
      _void_(Optimize.OPT->cinterface = fopen_string1(v13948,((char*)"w")));
      use_as_output_port(Optimize.OPT->cinterface);
      princ_string(((char*)"// interface definition for module "));
      print_any(_oid_(v46356));
      princ_string(((char*)"\n"));
      princ_string(((char*)"#ifndef CLAIREH_"));
      ident_thing(v46356);
      princ_string(((char*)"\n#define CLAIREH_"));
      ident_thing(v46356);
      princ_string(((char*)"\n"));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        bag *v12208_support;
        v12208_support = GC_OBJECT(list,Optimize.compiler->headers);
        for (START(v12208_support); NEXT(v12208);)
        if (match_wildcard_ask_string(string_v(v12208),((char*)"*.*")) == CTRUE)
         { princ_string(((char*)"#include "));
          if (equal_string(left_string(string_v(v12208),1),((char*)"<")) == CTRUE)
           princ_string(string_v(v12208));
          else print_any(v12208);
            princ_string(((char*)"\n"));
          }
        else { princ_string(((char*)"#include \""));
            princ_string(string_v(v12208));
            princ_string(((char*)".h\"\n"));
            }
          }
      use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value));
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  end_module_interface_c_producer(Generate_c_producer *v12187,module *v46356) { 
    princ_string(((char*)"\n#endif\n"));
    POP_SIGNAL;}
  

CL_EXPORT void  generate_end_file_c_producer(Generate_c_producer *v12194,module *v12197) { 
    
    GC_BIND;
    close_block_void();
    putc_char1(_char_(((char*)"\n")[1 - 1]),GC_OBJECT(PortObject,Optimize.OPT->outfile));
    fclose_port1(GC_OBJECT(PortObject,Optimize.OPT->outfile));
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v12187);
      bag *v12187_support;
      v12187_support = GC_OBJECT(list,Optimize.OPT->objects);
      for (START(v12187_support); NEXT(v12187);)
      { GC_LOOP;
        if (INHERIT(OWNER(v12187),Kernel._class))
         { buffer * v12200 = GC_OBJECT(buffer,fopen_string1(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(Optimize.compiler->source),GC_STRING(string_v(Core._starfs_star->value)))),GC_STRING(c_string_c_producer2(v12194,OBJECT(symbol,(*Kernel.name)(v12187)))))),GC_STRING(v12194->extension))),((char*)"a")));
          use_as_output_port(v12200);
          close_block_void();
          putc_char1(_char_(((char*)"\n")[1 - 1]),v12200);
          fclose_port1(v12200);
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  generate_classes_c_producer(Generate_c_producer *v12194,char *v12203,module *v12197) { 
    princ_string(((char*)"\n\nCL_EXPORT "));
    ident_c_producer(v12194,v12197->name);
    princ_string(((char*)"Class "));
    ident_c_producer(v12194,v12197->name);
    princ_string(((char*)";\n\n"));
    { module * v50476 = v12197;
      module * v50477 = v50476->part_of;
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((boolean_I_any(_oid_(v50477->made_of)) != CTRUE) && 
            ((v50477 != claire.it) && 
              ((*(v50477->parts))[1] == _oid_(v50476)))))
        { princ_string(((char*)"CL_EXPORT NameSpace "));
          (*Language.ident)(Generate.PRODUCER->value,
            _oid_(v50477->name));
          princ_string(((char*)";\n"));
          v50477= (v50477->part_of);
          v50476= (v50477);
          POP_SIGNAL;}
        }
      }
    POP_SIGNAL;}
  

CL_EXPORT void  generate_start_file_c_producer(Generate_c_producer *v12187,module *v12197) { 
    
    GC_BIND;
    if (should_trace_ask_module1(Generate.it,2) == CTRUE)
     mtformat_module1(Generate.it,((char*)"++++ Creating the file ~A.cpp \n"),2,list::alloc(1,GC_OID(_string_(c_string_c_producer2(v12187,v12197->name)))));
    else ;start_file_string(string_I_symbol(v12197->name),v12197);
    _void_(Optimize.OPT->level = 0);
    princ_string(((char*)"/* class file for module "));
    print_any(_oid_(v12197));
    princ_string(((char*)" */"));
    breakline_void();
    breakline_void();
    princ_string(((char*)"public class "));
    ident_c_producer(v12187,v12197->name);
    princ_string(((char*)" extends NameSpace"));
    new_block_void();
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  generate_meta_load_c_producer(Generate_c_producer *v12187,module *v12197) { 
    princ_string(((char*)"void "));
    ident_c_producer(v12187,v12197->name);
    princ_string(((char*)"Class::metaLoad() "));
    new_block_void();
    breakline_void();
    { breakline_void();
      princ_string(((char*)"ClEnv->module_I = it;\n"));
      }
    POP_SIGNAL;}
  

CL_EXPORT OID  start_file_string(char *v12203,module *v12197) { 
    
    GC_BIND;
    use_as_output_port(Optimize.OPT->outfile);
    { OID Result = 0;
      { ClaireBoolean * v47194 = ((fsize_string(GC_STRING(get_disk_file_port1(Optimize.OPT->outfile)->file_path)) == 0.0) ? CTRUE : CFALSE);
        princ_string(((char*)"/***** CLAIRE Compilation of file "));
        princ_string(v12203);
        princ_string(((char*)".cl \n         [version "));
        princ_string(release_void());
        princ_string(((char*)" / safety "));
        print_any(((OID)Optimize.compiler->safety));
        princ_string(((char*)"] *****/\n\n"));
        if (v47194 == CTRUE)
         { princ_string(((char*)"#include <claire.h>\n"));
          princ_string(((char*)"#include <Kernel.h>\n"));
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v12208);
            bag *v12208_support;
            v12208_support = GC_OBJECT(list,add_modules_list(list::alloc(1,_oid_(v12197))));
            for (START(v12208_support); NEXT(v12208);)
            { GC_LOOP;
              { { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(v12207);
                  bag *v12207_support;
                  v12207_support = GC_OBJECT(list,OBJECT(module,v12208)->uses);
                  for (START(v12207_support); NEXT(v12207);)
                  if (Kernel._string == OWNER(v12207))
                   { princ_string(((char*)"#include <"));
                    (*Kernel.princ)(v12207);
                    princ_string(((char*)".h>\n"));
                    }
                  }
                if (v12208 == _oid_(v12197))
                 { princ_string(((char*)"\n#if defined(CLPC) && !defined(CLPCNODLL)\n"));
                  princ_string(((char*)"  #undef CL_EXPORT\n"));
                  princ_string(((char*)"  #define CL_EXPORT __declspec(dllexport)\n"));
                  princ_string(((char*)"#endif\n"));
                  }
                if (OBJECT(module,v12208)->made_of->length != 0)
                 { princ_string(((char*)"#include <"));
                  ident_symbol(OBJECT(symbol,(*Kernel.name)(v12208)));
                  princ_string(((char*)".h>\n"));
                  }
                if (v12208 == _oid_(v12197))
                 { princ_string(((char*)"\n#if defined(CLPC) && !defined(CLPCNODLL)\n"));
                  princ_string(((char*)"  #undef CL_EXPORT\n"));
                  princ_string(((char*)"  #define CL_EXPORT __declspec(dllimport)\n"));
                  princ_string(((char*)"#endif\n"));
                  }
                }
              GC_UNLOOP; POP_SIGNAL;}
            }
          if (boolean_I_any(Optimize.OPT->cfile) == CTRUE)
           { princ_string(((char*)"#include <"));
            (*Kernel.princ)(GC_OID(Optimize.OPT->cfile));
            princ_string(((char*)".h>\n"));
            }
          princ_string(((char*)"\n#if defined(CLPC) && !defined(CLPCNODLL)\n"));
          princ_string(((char*)"  #undef CL_EXPORT\n"));
          if (boolean_I_any(Optimize.OPT->cfile) == CTRUE)
           princ_string(((char*)"  #define CL_EXPORT\n"));
          else princ_string(((char*)"  #define CL_EXPORT __declspec(dllexport)\n"));
            princ_string(((char*)"#endif\n"));
          }
        Result = _oid_(use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value)));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  define_variable_c_producer2(Generate_c_producer *v12187,ClaireClass *v12204,char *v12206) { 
    interface_I_class(v12204);
    princ_string(v12206);
    princ_string(((char*)" "));
    if ((v12204 == Kernel._integer) || 
        (v12204 == Kernel._any))
     princ_string(((char*)"= 0"));
    else if (v12204 == Kernel._float)
     princ_string(((char*)"=0.0"));
    princ_string(((char*)";"));
    POP_SIGNAL;}
  

CL_EXPORT void  generate_profile_c_producer(Generate_c_producer *v12187,OID v12197) { 
    if (Kernel._method == OWNER(v12197))
     get_dependents_method(OBJECT(method,v12197));
    { princ_string(((char*)"   PRcount *PR_x = PRstart(PRget_property("));
      expression_thing(((Kernel._method == OWNER(v12197)) ?
        OBJECT(restriction,v12197)->selector :
        Kernel.fastcall ),Core.nil->value);
      princ_string(((char*)"));"));
      breakline_void();
      }
    POP_SIGNAL;}
  

CL_EXPORT void  generate_interface_c_producer(Generate_c_producer *v12187,module *v46356) { 
    
    GC_BIND;
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v12208);
      bag *v12208_support;
      v12208_support = GC_OBJECT(list,Optimize.OPT->objects);
      for (START(v12208_support); NEXT(v12208);)
      if (INHERIT(OWNER(v12208),Kernel._class))
       { princ_string(((char*)"\nclass CL_EXPORT "));
        class_princ_c_producer(v12187,OBJECT(ClaireClass,v12208));
        princ_string(((char*)";"));
        }
      }
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v12208);
      bag *v12208_support;
      v12208_support = GC_OBJECT(list,Optimize.OPT->objects);
      for (START(v12208_support); NEXT(v12208);)
      { GC_LOOP;
        if (INHERIT(OWNER(v12208),Kernel._class))
         { princ_string(((char*)"\n\nclass CL_EXPORT "));
          class_princ_c_producer(v12187,OBJECT(ClaireClass,v12208));
          princ_string(((char*)": public "));
          class_princ_c_producer(v12187,OBJECT(ClaireClass,(*Kernel.superclass)(v12208)));
          new_block_void();
          breakline_void();
          princ_string(((char*)"public:"));
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(v12209);
            bag *v12209_support;
            v12209_support = GC_OBJECT(list,OBJECT(bag,(*Optimize.get_indexed)(v12208)));
            for (START(v12209_support); NEXT(v12209);)
            { ClaireBoolean * g1860I;
              { OID  v10081;
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(v50666);
                  v10081= Kernel.cfalse;
                  bag *v50666_support;
                  v50666_support = OBJECT(ClaireClass,(*Kernel.superclass)(v12208))->slots;
                  for (START(v50666_support); NEXT(v50666);)
                  if (_I_equal_any(_oid_(OBJECT(restriction,v50666)->selector),_oid_(OBJECT(restriction,v12209)->selector)) != CTRUE)
                   { v10081 = Kernel.ctrue;
                    ClEnv->cHandle = loop_handle;break;}
                  }
                g1860I = not_any(v10081);
                }
              
              if (g1860I == CTRUE) { breakline_void();
                  princ_string(((char*)"   "));
                  (*Generate.interface_I)(Generate.PRODUCER->value,
                    _oid_(psort_any(_oid_(OBJECT(restriction,v12209)->range))));
                  ident_symbol(OBJECT(restriction,v12209)->selector->name);
                  princ_string(((char*)";"));
                  }
                }
            }
          (*Generate.methods_interface)(Generate.PRODUCER->value,
            v12208);
          close_block_void();
          princ_string(((char*)";"));
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v12196);
      bag *v12196_support;
      v12196_support = GC_OBJECT(list,Optimize.OPT->functions);
      for (START(v12196_support); NEXT(v12196);)
      { GC_LOOP;
        { OID  v48297 = GC_OID((*Kernel.nth)(v12196,
            ((OID)1)));
          OID  v22281 = GC_OID((*Kernel.nth)(v12196,
            ((OID)2)));
          OID  v12203 = GC_OID((*Kernel.nth)(v12196,
            ((OID)3)));
          princ_string(((char*)"\nextern CL_EXPORT "));
          (*Generate.interface_I)(Generate.PRODUCER->value,
            v12203);
          princ_string(((char*)" "));
          (*Kernel.c_princ)(v48297);
          princ_string(((char*)"("));
          typed_args_list_list(OBJECT(list,v22281));
          princ_string(((char*)");"));
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  global_var_def_I_c_producer(Generate_c_producer *v12187,module *v46356,Let *v12208) { 
    
    GC_BIND;
    { global_variable * v53827 = OBJECT(global_variable,get_symbol(OBJECT(symbol,(*(OBJECT(bag,(*Core.args)(GC_OID(v12208->value)))))[1])));
      ClaireClass * v12203 = getRange_global_variable(v53827);
      OID  v44646 = GC_OID((*(OBJECT(Do,v12208->arg)->args))[2]);
      OID  v20842;
      { if (INHERIT(OWNER(v44646),Language._Update))
         v20842 = OBJECT(Update,v44646)->value;
        else if ((INHERIT(OWNER(v44646),Language._Call)) || 
            (INHERIT(OWNER(v44646),Language._Call_method)))
         v20842 = (*(OBJECT(bag,(*Core.args)(v44646))))[5];
        else { OID  v21277;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Design bug: make ~S a public global var !")),
              _oid_(list::alloc(1,_oid_(v53827))))));
            
            v20842=_void_(v21277);}
          GC_OID(v20842);}
      ClaireBoolean * v12186 = c_func_any(v20842);
      Variable * v1000 = GC_OBJECT(Variable,build_Variable_string(((char*)"V_C"),_oid_(Kernel._any)));
      if (nativeVar_ask_global_variable(v53827) != CTRUE)
       statement_any(_oid_(v12208),Core.nil->value,Core.nil->value);
      else { if (v12186 != CTRUE)
           { new_block_void();
            princ_string(((char*)"OID "));
            ident_c_producer3(v12187,v1000);
            princ_string(((char*)";"));
            breakline_void();
            statement_any(v20842,GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
              _oid_(v1000))),Core.nil->value);
            }
          ident_c_producer(v12187,v46356->name);
          princ_string(((char*)"."));
          ident_c_producer(v12187,v53827->name);
          princ_string(((char*)" = "));
          if (v12186 == CTRUE)
           to_c_c_producer1(v12187,v20842,v12203,Core.nil->value);
          else to_c_c_producer1(v12187,_oid_(v1000),v12203,Core.nil->value);
            princ_string(((char*)";"));
          if (v12186 != CTRUE)
           close_block_void();
          breakline_void();
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT OID  gc_usage_any(OID v46356,ClaireBoolean *v44140) { 
    
    GC_BIND;
    { OID Result = 0;
      if (INHERIT(OWNER(v46356),Language._Instruction))
       { if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Construct))
         Result = gc_usage_star_list(GC_OBJECT(list,OBJECT(Construct,v46356)->args),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Definition))
         Result = Kernel.ctrue;
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Call_method))
         Result = gc_usage_star_list(GC_OBJECT(list,OBJECT(Call_method,v46356)->args),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Call_slot))
         Result = gc_usage_any(GC_OID(OBJECT(Call_slot,v46356)->arg),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Call_table))
         Result = gc_usage_any(GC_OID(OBJECT(Call_table,v46356)->arg),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Call_array))
         Result = gc_usage_any(GC_OID(OBJECT(Call_array,v46356)->arg),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Optimize._to_C))
         Result = gc_usage_any(GC_OID(OBJECT(Compile_to_C,v46356)->arg),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Optimize._to_CL))
         Result = gc_usage_any(GC_OID(OBJECT(Compile_to_CL,v46356)->arg),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Optimize._to_protect))
         Result = gc_or_any(gc_usage_any(GC_OID(OBJECT(Compile_to_protect,v46356)->arg),v44140),Kernel.ctrue);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Update))
         Result = gc_usage_any(GC_OID(OBJECT(Update,v46356)->value),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Call))
         Result = gc_usage_star_list(GC_OBJECT(list,OBJECT(Call,v46356)->args),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._If))
         Result = gc_or_any(gc_usage_any(GC_OID(OBJECT(If,v46356)->test),v44140),gc_or_any(GC_OID(gc_usage_any(GC_OID(OBJECT(If,v46356)->arg),v44140)),GC_OID(gc_usage_any(GC_OID(OBJECT(If,v46356)->other),v44140))));
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Do))
         Result = gc_usage_star_list(GC_OBJECT(list,OBJECT(Do,v46356)->args),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Iteration))
         Result = gc_or_any(GC_OID(gc_usage_any(GC_OID(OBJECT(Iteration,v46356)->set_arg),v44140)),GC_OID(gc_usage_any(GC_OID(OBJECT(Iteration,v46356)->arg),CTRUE)));
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Ffor))
         Result = Kernel.ctrue;
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Let))
         { OID  v12208 = GC_OID(OBJECT(Let,v46356)->value);
          { OID  v12003;
            if ((v44140 == CTRUE) && 
                (INHERIT(OWNER(v12208),Optimize._to_protect)))
             v12003 = Kernel.ctrue;
            else v12003 = Kernel.cfalse;
              Result = gc_or_any(v12003,gc_or_any(GC_OID(gc_usage_any(v12208,v44140)),GC_OID(gc_usage_any(GC_OID(OBJECT(Let,v46356)->arg),v44140))));
            }
          }
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Assign))
         { OID  v12208 = GC_OID(OBJECT(Assign,v46356)->arg);
          { OID  v12964;
            if ((v44140 == CTRUE) && 
                (inner2outer_ask_any(v12208) == CTRUE))
             v12964 = Kernel.ctrue;
            else v12964 = Kernel.cfalse;
              Result = gc_or_any(v12964,gc_usage_any(v12208,v44140));
            }
          }
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Gassign))
         Result = gc_usage_any(GC_OID(OBJECT(Gassign,v46356)->arg),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._And))
         Result = gc_usage_star_list(GC_OBJECT(list,OBJECT(And,v46356)->args),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Or))
         Result = gc_usage_star_list(GC_OBJECT(list,OBJECT(Or,v46356)->args),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Cast))
         Result = gc_usage_any(GC_OID(OBJECT(Cast,v46356)->arg),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Super))
         Result = gc_usage_star_list(GC_OBJECT(list,OBJECT(Super,v46356)->args),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Case))
         Result = gc_usage_star_list(GC_OBJECT(list,OBJECT(Case,v46356)->args),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._While))
         Result = gc_or_any(GC_OID(gc_usage_any(GC_OID(OBJECT(While,v46356)->arg),CTRUE)),GC_OID(gc_usage_any(GC_OID(OBJECT(While,v46356)->test),v44140)));
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Return))
         Result = gc_usage_any(GC_OID(OBJECT(Return,v46356)->arg),v44140);
        else if (INHERIT(OBJECT(ClaireObject,v46356)->isa,Language._Handle))
         Result = gc_or_any(gc_or_any(GC_OID(gc_usage_any(GC_OID(OBJECT(ClaireHandle,v46356)->arg),v44140)),GC_OID(gc_usage_any(GC_OID(OBJECT(ClaireHandle,v46356)->other),v44140))),gc_usage_any(GC_OID(OBJECT(ClaireHandle,v46356)->test),v44140));
        else Result = Kernel.cfalse;
          }
      else Result = Kernel.cfalse;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  gc_or_any(OID v12208,OID v12209) { 
    { OID Result = 0;
      if (v12208 == Kernel.cfalse)
       Result = v12209;
      else if (v12208 == Kernel.ctrue)
       { if (v12209 == Kernel.cfalse)
         Result = v12208;
        else Result = v12209;
          }
      else if (INHERIT(OWNER(v12209),Kernel._integer))
       { if (equal(v12208,v12209) == CTRUE)
         Result = v12209;
        else Result = ((OID)100000);
          }
      else Result = v12208;
        POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT OID  gc_usage_star_list(list *v12196,ClaireBoolean *v44140) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { OID Result = 0;
      { OID  v12208 = Kernel.cfalse;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v12209);
          for (START(v12196); NEXT(v12209);)
          { GC_LOOP;
            GC__OID(v12208 = gc_or_any(v12208,gc_usage_any(v12209,v44140)), 1);
            GC_UNLOOP; POP_SIGNAL;}
          }
        Result = v12208;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT char * protect_result_c_producer(Generate_c_producer *v12187,ClaireClass *v12203,ClaireBoolean *v32348,OID v12208) { 
    if ((CL_INT)Optimize.compiler->safety > (CL_INT)5)
     { _void_(Optimize.OPT->protection = CFALSE);
      v32348= (CFALSE);
      _void_(Optimize.OPT->loop_gc = CFALSE);
      }
    { char *Result ;
      { char * v50665 = ((v12203 != Kernel._void) ?
          ((Optimize.OPT->alloc_stack != CTRUE) ?
            ((v32348 == CTRUE) ?
              ((char*)"GC_UNBIND; POP_SIGNAL; return ") :
              ((char*)"POP_SIGNAL; return ") ) :
            ((v32348 == CTRUE) ?
              ((char*)"GC_UNBIND; return ") :
              ((char*)"return ") ) ) :
          ((v32348 == CTRUE) ?
            ((char*)"GC_UNBIND; POP_SIGNAL;") :
            ((char*)"POP_SIGNAL;") ) );
        _void_(Optimize.OPT->protection = v32348);
        Result = (((Optimize.OPT->profile_ask == CTRUE) && 
            ((Kernel._method == OWNER(v12208)) || 
                (v12208 == CNULL))) ?
          append_string(((char*)"PRend(PR_x);"),v50665) :
          v50665 );
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  generate_function_start_c_producer(Generate_c_producer *v12187,lambda *v46356,ClaireClass *v12203,OID v12197,char *v25167) { 
    
    GC_BIND;
    { OID  v15557;
      { if (v46356->vars->length != 0)
         v15557 = (*Kernel.range)(GC_OID((*(v46356->vars))[1]));
        else v15557 = _oid_(Kernel._any);
          GC_OID(v15557);}
      ClaireFunction * v48297 = make_function_string(v25167);
      list * v50514 = GC_OBJECT(list,(((v46356->vars->length == 1) && 
          ((v15557 == _oid_(Kernel._environment)) || 
              (v15557 == _oid_(Kernel._void)))) ?
        Kernel.nil :
        v46356->vars ));
      update_function_entry_c_producer(v12187,v48297,v50514,v12203);
      use_as_output_port(Optimize.OPT->outfile);
      if (Kernel._method == OWNER(v12197))
       { if ((OBJECT(restriction,v12197)->range == Kernel._float) || 
            (OBJECT(restriction,v12197)->domain->memq(_oid_(Kernel._float)) == CTRUE))
         generate_float_function_c_producer(v12187,OBJECT(method,v12197),string_I_function(v48297));
        else if (INHERIT(OBJECT(restriction,v12197)->range->isa,Kernel._tuple))
         generate_tuple_function_c_producer(v12187,OBJECT(method,v12197),string_I_function(v48297));
        }
      generate_regular_function_c_producer(v12187,
        v46356,
        v48297,
        v12203,
        v12197,
        v50514);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  generate_regular_function_c_producer(Generate_c_producer *v12187,lambda *v46356,ClaireFunction *v48297,ClaireClass *v12203,OID v12197,list *v50514) { 
    
    GC_BIND;
    if (Optimize.compiler->naming != 2)
     { princ_string(((char*)"\n// The c++ function for: "));
      if (Kernel._method == OWNER(v12197))
       { print_any(_oid_(OBJECT(restriction,v12197)->selector));
        princ_string(((char*)"("));
        ppvariable_list(GC_OBJECT(list,v46356->vars));
        princ_string(((char*)") ["));
        if (Optimize.compiler->naming == 1)
         bitvectorSum_integer(status_I_restriction(OBJECT(restriction,v12197)));
        princ_string(((char*)"]"));
        }
      else princ_string(string_I_function(v48297));
        princ_string(((char*)"\n"));
      }
    { princ_string(((char*)"CL_EXPORT "));
      interface_I_c_producer(v12187,v12203);
      princ_string(((char*)" "));
      c_princ_function(v48297);
      princ_string(((char*)"("));
      typed_args_list_list(v50514);
      princ_string(((char*)") "));
      new_block_void();
      breakline_void();
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  generate_float_function_c_producer(Generate_c_producer *v12187,method *v12197,char *v25167) { 
    
    GC_BIND;
    { list * v50496 = (((v12197->domain->length == 1) && 
          (domain_I_restriction(v12197) == Kernel._void)) ?
        Kernel.nil :
        v12197->domain );
      CL_INT  v12198 = v50496->length;
      list * v50514;
      { { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          bag *v_list; OID v_val;
          OID v12208; CL_INT CLcount;
          v_list = v50496;
           v50514 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { GC_LOOP;
            v12208 = (*(v_list))[CLcount];
            { Variable * v60472 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(v60472->pname = gensym_void());
              { Variable * v22791 = v60472; 
                ClaireType * v22792;
                if (v12208 == _oid_(Kernel._float))
                 v22792 = Kernel._any;
                else v22792 = OBJECT(ClaireType,v12208);
                  _void_(v22791->range = v22792);}
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(v60472));
              v_val = _oid_(close_Instruction1(v60472));
              }
            
            (*((list *) v50514))[CLcount] = v_val;GC_UNLOOP; POP_SIGNAL;}
          }
        GC_OBJECT(list,v50514);}
      char * v59377 = GC_STRING(append_string(v25167,((char*)"_")));
      ClaireFunction * v48297 = make_function_string(v59377);
      lambda * v51556 = GC_OBJECT(lambda,lambda_I_list(v50514,Core.nil->value));
      ClaireClass * v12203 = ((v12197->range == Kernel._float) ?
        Kernel._any :
        psort_any(_oid_(v12197->range)) );
      generate_regular_function_c_producer(v12187,
        v51556,
        v48297,
        v12203,
        _oid_(v12197),
        v50514);
      GC_OBJECT(list,Optimize.OPT->functions)->addFast((OID)_oid_(list::alloc(3,_oid_(v48297),
        _oid_(v50514),
        _oid_(v12203))));
      if (v12203 != Kernel._void)
       princ_string(((char*)"return "));
      if (v12197->range == Kernel._float)
       princ_string(((char*)"_float_("));
      c_princ_function(OBJECT(ClaireFunction,(*Optimize.functional_I)(_oid_(v12197))));
      princ_string(((char*)"("));
      { CL_INT  v12193 = 1;
        CL_INT  v22790 = v12198;
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)v12193 <= (CL_INT)v22790))
          { if (v12193 != 1)
             princ_string(((char*)","));
            if ((*(v12197->domain))[v12193] == _oid_(Kernel._float))
             { princ_string(((char*)"float_v("));
              expression_Variable(OBJECT(Variable,(*(v50514))[v12193]),Core.nil->value);
              princ_string(((char*)")"));
              }
            else expression_Variable(OBJECT(Variable,(*(v50514))[v12193]),Core.nil->value);
              ++v12193;
            POP_SIGNAL;}
          }
        }
      princ_string(((char*)")"));
      if (v12197->range == Kernel._float)
       princ_string(((char*)")"));
      princ_string(((char*)";\n"));
      princ_string(((char*)"}\n\n"));
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  at_c_producer(Generate_c_producer *v12187) { 
    princ_string(((char*)"->"));
    POP_SIGNAL;}
  

CL_EXPORT void  generate_tuple_function_c_producer(Generate_c_producer *v12187,method *v12197,char *v25167) { 
    
    GC_BIND;
    { list * v50496 = (((v12197->domain->length == 1) && 
          (domain_I_restriction(v12197) == Kernel._void)) ?
        Kernel.nil :
        v12197->domain );
      CL_INT  v12198 = v50496->length;
      list * v50514;
      { { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          bag *v_list; OID v_val;
          OID v12208; CL_INT CLcount;
          v_list = v50496;
           v50514 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { GC_LOOP;
            v12208 = (*(v_list))[CLcount];
            { Variable * v60472 = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(v60472->pname = gensym_void());
              _void_(v60472->range = OBJECT(ClaireType,v12208));
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(v60472));
              v_val = _oid_(close_Instruction1(v60472));
              }
            
            (*((list *) v50514))[CLcount] = v_val;GC_UNLOOP; POP_SIGNAL;}
          }
        GC_OBJECT(list,v50514);}
      char * v59377 = GC_STRING(append_string(v25167,((char*)"_")));
      ClaireFunction * v48297 = make_function_string(v59377);
      lambda * v51556 = GC_OBJECT(lambda,lambda_I_list(v50514,Core.nil->value));
      ClaireClass * v12203 = Kernel._tuple;
      generate_regular_function_c_producer(v12187,
        v51556,
        v48297,
        v12203,
        _oid_(v12197),
        v50514);
      GC_OBJECT(list,Optimize.OPT->functions)->addFast((OID)_oid_(list::alloc(3,_oid_(v48297),
        _oid_(v50514),
        _oid_(v12203))));
      if (v12203 != Kernel._void)
       princ_string(((char*)"return "));
      c_princ_function(OBJECT(ClaireFunction,(*Optimize.functional_I)(_oid_(v12197))));
      princ_string(((char*)"("));
      { CL_INT  v12193 = 1;
        CL_INT  v22815 = v12198;
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)v12193 <= (CL_INT)v22815))
          { if (v12193 != 1)
             princ_string(((char*)","));
            expression_Variable(OBJECT(Variable,(*(v50514))[v12193]),Core.nil->value);
            ++v12193;
            POP_SIGNAL;}
          }
        }
      princ_string(((char*)")"));
      princ_string(((char*)"->copyIfNeeded();\n"));
      princ_string(((char*)"}\n\n"));
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT OID  create_function_entry_c_producer(Generate_c_producer *v12187,lambda *v50494,char *v48297,OID v12197) { 
    POP_SIGNAL; return (Core.nil->value);}
  

CL_EXPORT OID  update_function_entry_c_producer(Generate_c_producer *v12187,ClaireFunction *v48297,list *v50514,ClaireClass *v12203) { 
    
    GC_BIND;
    GC_OBJECT(list,Optimize.OPT->functions)->addFast((OID)_oid_(list::alloc(3,_oid_(v48297),
      _oid_(v50514),
      _oid_(v12203))));
    { OID Result = 0;
      Result = Kernel.cfalse;
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT char * c_interface_class1_Generate(ClaireClass *v46356) { 
    { char *Result ;
      { CL_INT  v12198 = index_list(OBJECT(Generate_producer,Generate.PRODUCER->value)->interfaces,_oid_(v46356));
        Result = ((v12198 == 0) ?
          ((char*)"OID *") :
          string_v((*(OBJECT(Generate_producer,Generate.PRODUCER->value)->interfaces))[((CL_INT)v12198+(CL_INT)1)]) );
        }
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  c_interface_class2_Generate(ClaireClass *v46356,char *v12203) { 
    
    GC_BIND;
    { CL_INT  v12198 = index_list(OBJECT(Generate_producer,Generate.PRODUCER->value)->interfaces,_oid_(v46356));
      if (v12198 == 0)
       _void_(OBJECT(Generate_producer,Generate.PRODUCER->value)->interfaces = GC_OBJECT(list,GC_OBJECT(list,OBJECT(Generate_producer,Generate.PRODUCER->value)->interfaces)->addFast((OID)_oid_(v46356)))->addFast((OID)_string_(v12203)));
      else ((*(GC_OBJECT(list,OBJECT(Generate_producer,Generate.PRODUCER->value)->interfaces)))[((CL_INT)v12198+(CL_INT)1)]=_string_(v12203));
        }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  c_interface_method_Generate(method *v46356) { 
    c_princ_string(string_v((*Optimize.function_name)(_oid_(v46356->selector),
      _oid_(v46356->domain),
      _oid_(v46356->functional))));
    POP_SIGNAL;}
  

CL_EXPORT void  interface_I_c_producer(Generate_c_producer *v12187,ClaireClass *v46356) { 
    if (v46356 == Kernel._void)
     princ_string(((char*)"void "));
    else if (v46356 == Kernel._integer)
     princ_string(((char*)"CL_INT "));
    else if ((v46356 == Kernel._function) || 
        ((v46356 == Kernel._char) || 
          (v46356 == Kernel._boolean)))
     { ident_c_producer(v12187,v46356->name);
      princ_string(((char*)" *"));
      }
    else if ((INHERIT(v46356,Kernel._cl_import)) || 
        ((v46356 == Kernel._string) || 
          (v46356 == Kernel._array)))
     princ_string(string_v((*Optimize.c_interface)(_oid_(v46356))));
    else if (INHERIT(v46356,Kernel._object))
     { class_princ_c_producer(v12187,v46356);
      princ_string(((char*)" *"));
      }
    else if (INHERIT(v46356,Kernel._bag))
     { ident_c_producer(v12187,v46356->name);
      princ_string(((char*)" *"));
      }
    else if (v46356 == Kernel._float)
     princ_string(((char*)"double "));
    else princ_string(((char*)"OID "));
      POP_SIGNAL;}
  

CL_EXPORT void  to_cl_c_producer(Generate_c_producer *v12187,OID v12208,ClaireClass *v12203,OID v44140) { 
    if (v12203 == Kernel._void)
     { princ_string(((char*)"_void_("));
      (*Generate.expression)(v12208,
        v44140);
      princ_string(((char*)")"));
      }
    else if (INHERIT(v12203,Kernel._object))
     { if (v12208 == Kernel.ctrue)
       princ_string(((char*)"Kernel.ctrue"));
      else if (v12208 == Kernel.cfalse)
       princ_string(((char*)"Kernel.cfalse"));
      else { princ_string(((char*)"_oid_("));
          (*Generate.expression)(v12208,
            v44140);
          princ_string(((char*)")"));
          }
        }
    else if (v12203 == Kernel._integer)
     { if ((CL_INT)Optimize.compiler->safety > (CL_INT)1)
       { princ_string(((char*)"((OID)"));
        (*Generate.expression)(v12208,
          v44140);
        princ_string(((char*)")"));
        }
      else { princ_string(((char*)"_integer_("));
          (*Generate.expression)(v12208,
            v44140);
          princ_string(((char*)")"));
          }
        }
    else if (v12203 == Kernel._char)
     { princ_string(((char*)"_oid_("));
      (*Generate.expression)(v12208,
        v44140);
      princ_string(((char*)")"));
      }
    else if (v12203 == Kernel._string)
     { princ_string(((char*)"_string_("));
      (*Generate.expression)(v12208,
        v44140);
      princ_string(((char*)")"));
      }
    else if (v12203 == Kernel._array)
     { princ_string(((char*)"_array_("));
      (*Generate.expression)(v12208,
        v44140);
      princ_string(((char*)")"));
      }
    else if (v12203 == Kernel._float)
     { princ_string(((char*)"_float_("));
      (*Generate.expression)(v12208,
        v44140);
      princ_string(((char*)")"));
      }
    else if (INHERIT(v12203,Kernel._cl_import))
     { princ_string(((char*)"ClAlloc->import("));
      expression_any(_oid_(v12203),_oid_(Kernel.emptySet));
      princ_string(((char*)",(OID *) "));
      (*Generate.expression)(v12208,
        v44140);
      princ_string(((char*)")"));
      }
    else if (v12203 == Kernel._any)
     (*Generate.expression)(v12208,
      v44140);
    else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[internal] to_cl for a ~S is not implemented")),
        _oid_(list::alloc(1,_oid_(v12203))))));
      POP_SIGNAL;}
  

CL_EXPORT void  to_c_c_producer1(Generate_c_producer *v12187,OID v12208,ClaireClass *v12203,OID v44140) { 
    
    GC_BIND;
    if (v12203 == Kernel._integer)
     { if (inherit_ask_class(OWNER(v12208),Kernel._integer) != CTRUE)
       { princ_string(((char*)"((CL_INT)"));
        (*Generate.expression)(v12208,
          v44140);
        princ_string(((char*)")"));
        }
      else (*Generate.expression)(v12208,
          v44140);
        }
    else if (v12208 == CNULL)
     { if (v12203 == Kernel._float)
       princ_string(((char*)"0.0"));
      else princ_string(((char*)"NULL"));
        }
    else if ((INHERIT(OWNER(v12208),Core._global_variable)) && 
        ((equal((*Kernel.range)(v12208),_oid_(Kernel.emptySet)) == CTRUE) && 
          (equal((*Kernel.value)(v12208),Core.nil->value) == CTRUE)))
     princ_string(((char*)"Kernel.nil"));
    else if ((INHERIT(v12203,Kernel._cl_import)) && 
        ((INHERIT(OWNER(v12208),Optimize._to_protect)) && 
          (INHERIT(owner_any(get_property(Kernel.arg,OBJECT(ClaireObject,v12208))),Optimize._to_CL))))
     (*Generate.expression)(GC_OID((*Kernel.arg)(GC_OID((*Kernel.arg)(v12208)))),
      v44140);
    else { to_c_c_producer2(v12187,v12203);
        (*Generate.expression)(v12208,
          v44140);
        princ_string(((char*)")"));
        }
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  to_c_c_producer2(Generate_c_producer *v12187,ClaireClass *v12203) { 
    if (INHERIT(v12203,Kernel._object))
     { princ_string(((char*)"OBJECT("));
      class_princ_class(v12203);
      princ_string(((char*)","));
      }
    else if (v12203 == Kernel._float)
     princ_string(((char*)"float_v("));
    else if (v12203 == Kernel._char)
     princ_string(((char*)"char_v("));
    else if (v12203 == Kernel._string)
     princ_string(((char*)"string_v("));
    else if (v12203 == Kernel._array)
     princ_string(((char*)"array_v("));
    else if (INHERIT(v12203,Kernel._cl_import))
     { princ_string(((char*)"EXPORT(("));
      interface_I_class(v12203);
      princ_string(((char*)"),"));
      }
    else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[internal] to_c for a ~S is not implemented")),
        _oid_(list::alloc(1,_oid_(v12203))))));
      POP_SIGNAL;}
  

CL_EXPORT void  public_static_c_producer(Generate_c_producer *v12187) { 
    ;POP_SIGNAL;}
  

CL_EXPORT void  bool_exp_I_c_producer(Generate_c_producer *v12187,OID v46356,OID v44140) { 
    if (INHERIT(OWNER(v46356),Optimize._to_CL))
     { princ_string(((char*)"("));
      (*Optimize.bool_exp)(v46356,
        Kernel.ctrue,
        v44140);
      princ_string(((char*)" ? Kernel.ctrue : Kernel.cfalse)"));
      }
    else { princ_string(((char*)"("));
        (*Optimize.bool_exp)(v46356,
          Kernel.ctrue,
          v44140);
        princ_string(((char*)" ? CTRUE : CFALSE)"));
        }
      POP_SIGNAL;}
  

CL_EXPORT void  inherit_exp_c_producer(Generate_c_producer *v12187,OID v50104,OID v50105,OID v44140) { 
    princ_string(((char*)"INHERIT("));
    (*Generate.expression)(v50104,
      v44140);
    princ_string(((char*)","));
    (*Generate.expression)(v50105,
      v44140);
    princ_string(((char*)")"));
    POP_SIGNAL;}
  

CL_EXPORT void  bitvector_exp_c_producer(Generate_c_producer *v12187,OID v50104,OID v50105,OID v44140) { 
    princ_string(((char*)"BCONTAIN("));
    (*Generate.expression)(v50104,
      v44140);
    princ_string(((char*)","));
    (*Generate.expression)(v50105,
      v44140);
    princ_string(((char*)")"));
    POP_SIGNAL;}
  

CL_EXPORT void  equal_exp_c_producer(Generate_c_producer *v12187,OID v50104,ClaireBoolean *v32308,OID v50105,OID v55228) { 
    
    GC_BIND;
    if ((INHERIT(OWNER(v50104),Optimize._to_CL)) && 
        ((INHERIT(OWNER(v50105),Optimize._to_CL)) && 
          ((osort_any(GC_OID((*Language.set_arg)(v50104))) == osort_any(GC_OID((*Language.set_arg)(v50105)))) && 
            ((identifiable_ask_any(GC_OID((*Kernel.arg)(v50104))) == CTRUE) || 
                ((identifiable_ask_any(GC_OID((*Kernel.arg)(v50105))) == CTRUE) || 
                  (((*Language.set_arg)(v50104) == _oid_(Kernel._string)) || 
                    ((*Language.set_arg)(v50104) == _oid_(Kernel._float))))))))
     equal_exp_c_producer(v12187,
      GC_OID((*Kernel.arg)(v50104)),
      v32308,
      GC_OID((*Kernel.arg)(v50105)),
      Kernel.ctrue);
    else if ((INHERIT(OWNER(v50104),Optimize._to_protect)) && 
        ((INHERIT(owner_any((*Kernel.arg)(v50104)),Optimize._to_CL)) && 
          (((*Optimize.c_gc_ask)(GC_OID((*Kernel.arg)(GC_OID((*Kernel.arg)(v50104))))) != Kernel.ctrue) && 
            ((INHERIT(OWNER(v50105),Optimize._to_protect)) && 
              ((INHERIT(owner_any((*Kernel.arg)(v50105)),Optimize._to_CL)) && 
                ((*Optimize.c_gc_ask)(GC_OID((*Kernel.arg)(GC_OID((*Kernel.arg)(v50105))))) != Kernel.ctrue))))))
     equal_exp_c_producer(v12187,
      GC_OID((*Kernel.arg)(v50104)),
      v32308,
      GC_OID((*Kernel.arg)(v50105)),
      v55228);
    else { ClaireBoolean * g1872I;
      { ClaireBoolean *v_and;
        { v_and = (((*Optimize.c_sort)(v50104) == _oid_(Kernel._string)) ? CTRUE : CFALSE);
          if (v_and == CFALSE) g1872I =CFALSE; 
          else { v_and = (((*Optimize.c_sort)(v50105) == _oid_(Kernel._string)) ? CTRUE : CFALSE);
            if (v_and == CFALSE) g1872I =CFALSE; 
            else { { OID  v41794;
                if (INHERIT(OWNER(v50105),Optimize._to_C))
                 v41794 = ((OBJECT(Compile_to_C,v50105)->arg == CNULL) ? Kernel.ctrue : Kernel.cfalse);
                else v41794 = Kernel.cfalse;
                  v_and = not_any(v41794);
                }
              if (v_and == CFALSE) g1872I =CFALSE; 
              else g1872I = CTRUE;}
            }
          }
        }
      
      if (g1872I == CTRUE) { princ_string(((char*)"(equal_string("));
          (*Generate.expression)(v50104,
            Core.nil->value);
          princ_string(((char*)","));
          (*Generate.expression)(v50105,
            Core.nil->value);
          princ_string(((char*)") "));
          sign_equal_boolean(v32308);
          princ_string(((char*)" CTRUE)"));
          }
        else if ((INHERIT(OWNER(v50104),Optimize._to_CL)) && 
          (((*Language.set_arg)(v50104) != _oid_(Kernel._integer)) && 
            (v50105 == CNULL)))
       { princ_string(((char*)"("));
        (*Generate.expression)(GC_OID((*Kernel.arg)(v50104)),
          Core.nil->value);
        princ_string(((char*)" "));
        sign_equal_boolean(v32308);
        princ_string(((char*)" "));
        if ((*Language.set_arg)(v50104) == _oid_(Kernel._float))
         princ_string(((char*)"0.0"));
        else princ_string(((char*)"NULL"));
          princ_string(((char*)")"));
        }
      else if ((char_exp_ask_c_producer2(v12187,v50104) == CTRUE) || 
          (char_exp_ask_c_producer2(v12187,v50105) == CTRUE))
       { princ_string(((char*)"("));
        char_exp_c_producer2(v12187,v50104,Core.nil->value);
        princ_string(((char*)" "));
        sign_equal_boolean(v32308);
        princ_string(((char*)" "));
        char_exp_c_producer2(v12187,v50105,Core.nil->value);
        princ_string(((char*)")"));
        }
      else if ((boolean_I_any(v55228) == CTRUE) || 
          ((identifiable_ask_any(v50104) == CTRUE) || 
            ((identifiable_ask_any(v50105) == CTRUE) || 
              ((*Optimize.c_sort)(v50104) == _oid_(Kernel._float)))))
       { if (equal(_oid_(glb_class(stupid_t_any1(v50104),stupid_t_any1(v50105))),_oid_(Kernel.emptySet)) == CTRUE)
         { warn_void();
          if (should_trace_ask_module1(Generate.it,2) == CTRUE)
           mtformat_module1(Generate.it,((char*)"`BLUE ~S = ~S will fail ! [263]\n"),2,list::alloc(2,v50104,v50105));
          else ;}
        princ_string(((char*)"("));
        bexpression_any(v50104,Core.nil->value);
        princ_string(((char*)" "));
        sign_equal_boolean(v32308);
        princ_string(((char*)" "));
        bexpression_any(v50105,Core.nil->value);
        princ_string(((char*)")"));
        }
      else { princ_string(((char*)"(equal("));
          (*Generate.expression)(v50104,
            Core.nil->value);
          princ_string(((char*)","));
          (*Generate.expression)(v50105,
            Core.nil->value);
          princ_string(((char*)") "));
          sign_equal_boolean(v32308);
          princ_string(((char*)" CTRUE)"));
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT ClaireBoolean * char_exp_ask_c_producer2(Generate_c_producer *v12187,OID v12208) { 
    { ClaireBoolean *Result ;
      if (INHERIT(OWNER(v12208),Kernel._char))
       Result = CTRUE;
      else if (INHERIT(OWNER(v12208),Language._Call_method))
       { method * v12197 = OBJECT(Call_method,v12208)->arg;
        Result = ((_oid_(v12197) == Generate._starnth_1_string_star->value) ? CTRUE : (((_oid_(v12197) == Generate._starnth_string_star->value) && 
            ((CL_INT)2 <= (CL_INT)Optimize.compiler->safety)) ? CTRUE : CFALSE));
        }
      else Result = CFALSE;
        POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  char_exp_c_producer2(Generate_c_producer *v12187,OID v12208,OID v44140) { 
    
    GC_BIND;
    if (INHERIT(OWNER(v12208),Kernel._char))
     { princ_string(((char*)"((unsigned char)"));
      print_any(v12208);
      princ_string(((char*)")"));
      }
    else if (INHERIT(OWNER(v12208),Language._Call_method))
     { method * v12197 = OBJECT(Call_method,v12208)->arg;
      if ((_oid_(v12197) == Generate._starnth_1_string_star->value) || 
          (_oid_(v12197) == Generate._starnth_string_star->value))
       { OID  v50104 = GC_OID((*(OBJECT(Call_method,v12208)->args))[1]);
        OID  v50105 = GC_OID((*(OBJECT(Call_method,v12208)->args))[2]);
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"["));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)" - 1]"));
        }
      else { princ_string(((char*)"((unsigned char) "));
          (*Generate.expression)(v12208,
            v44140);
          princ_string(((char*)"->ascii)"));
          }
        }
    else { princ_string(((char*)"((unsigned char) "));
        (*Generate.expression)(v12208,
          v44140);
        princ_string(((char*)"->ascii)"));
        }
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  c_member_c_producer(Generate_c_producer *v12187,OID v46356,ClaireClass *v12203,property *v12208,OID v44140) { 
    if (INHERIT(stupid_t_any1(v46356),v12203))
     { (*Generate.expression)(v46356,
        v44140);
      princ_string(((char*)"->"));
      ident_symbol(v12208->name);
      }
    else { princ_string(((char*)"CLREAD("));
        class_princ_class(v12203);
        princ_string(((char*)","));
        if ((OBJECT(ClaireBoolean,Generate._starin_store_star->value)) == CTRUE)
         { princ_string(((char*)"STOREREF("));
          (*Generate.expression)(v46356,
            v44140);
          princ_string(((char*)")"));
          }
        else (*Generate.expression)(v46356,
            v44140);
          princ_string(((char*)","));
        ident_symbol(v12208->name);
        princ_string(((char*)")"));
        }
      POP_SIGNAL;}
  

CL_EXPORT void  addFast_c_producer(Generate_c_producer *v12187) { 
    princ_string(((char*)"->addFast"));
    POP_SIGNAL;}
  

CL_EXPORT void  cast_I_c_producer(Generate_c_producer *v12187,Compile_C_cast *v46356,OID v44140) { 
    
    GC_BIND;
    princ_string(((char*)"(("));
    class_princ_class(v46356->set_arg);
    princ_string(((char*)" *) "));
    (*Generate.expression)(v46356->arg,
      v44140);
    princ_string(((char*)")"));
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  gc_protection_exp_c_producer(Generate_c_producer *v12187,Variable *v12206,ClaireBoolean *v40842,OID v12205,OID v44140) { 
    
    GC_BIND;
    if ((INHERIT(osort_any(GC_OID(_oid_(v12206->range))),Kernel._cl_import)) || 
        ((osort_any(GC_OID(_oid_(v12206->range))) == Kernel._float) || 
          (osort_any(GC_OID(_oid_(v12206->range))) == Kernel._integer)))
     { princ_string(((char*)"("));
      ident_c_producer3(v12187,v12206);
      princ_string(((char*)"="));
      if (v40842 == CTRUE)
       (*Generate.expression)(v12205,
        v44140);
      else c_princ_string(string_v(v12205));
        princ_string(((char*)")"));
      }
    else { _void_(v12187->stat = ((CL_INT)v12187->stat+(CL_INT)1));
        princ_string(((char*)"GC__"));
        princ_string(((osort_any(GC_OID(_oid_(v12206->range))) == Kernel._any) ?
          ((char*)"OID") :
          ((osort_any(GC_OID(_oid_(v12206->range))) == Kernel._string) ?
            ((char*)"STRING") :
            ((char*)"ANY") ) ));
        princ_string(((char*)"("));
        ident_c_producer3(v12187,v12206);
        if (v12205 != _oid_(v12206))
         { princ_string(((char*)" = "));
          if (v40842 == CTRUE)
           (*Generate.expression)(v12205,
            v44140);
          else c_princ_string(string_v(v12205));
            }
        princ_string(((char*)", "));
        { CL_INT  v44678;
          { _void_(Optimize.OPT->loop_index = ((CL_INT)Optimize.OPT->loop_index+(CL_INT)1));
            v44678 = Optimize.OPT->loop_index;
            }
          princ_integer(v44678);
          }
        princ_string(((char*)")"));
        }
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  bag_expression_c_producer(Generate_c_producer *v50237,ClaireClass *v12187,bag *v12196,ClaireType *v12204,OID v44140) { 
    
    GC_BIND;
    if (v12196->length == 0)
     { print_any(_oid_(v12187));
      princ_string(((char*)"::empty("));
      if (v12204 != Kernel._void)
       { if (should_trace_ask_module1(Generate.it,5) == CTRUE)
         mtformat_module1(Generate.it,((char*)"t = ~S => ~S \n"),5,list::alloc(2,_oid_(v12204),GC_OID((*Optimize.c_code)(_oid_(v12204),
          _oid_(Kernel._object)))));
        else ;(*Generate.expression)(GC_OID((*Optimize.c_code)(_oid_(v12204),
            _oid_(Kernel._object))),
          v44140);
        }
      princ_string(((char*)")"));
      }
    else { print_any(_oid_(v12187));
        princ_string(((char*)"::alloc"));
        if ((v12187 == Kernel._tuple) && 
            (Optimize.OPT->alloc_stack == CTRUE))
         princ_string(((char*)"Stack"));
        princ_string(((char*)"("));
        if (v12204 != Kernel._void)
         { (*Generate.expression)(GC_OID((*Optimize.c_code)(_oid_(v12204),
              _oid_(Kernel._object))),
            v44140);
          princ_string(((char*)","));
          }
        princ_integer(v12196->length);
        princ_string(((char*)","));
        args_list_bag(v12196,v44140,_sup_integer(v12196->length,2));
        princ_string(((char*)")"));
        }
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  generate_s_file_string(char *v46356,list *v12196,OID v12197) { 
    
    GC_BIND;
    { buffer * v12200 = GC_OBJECT(buffer,fopen_string1(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->source),v46356)),((char*)"-s"))),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))),((char*)"w")));
      list * v39800 = GC_OBJECT(list,add_modules_list(v12196));
      list * v1140 = GC_OBJECT(list,parents_list(v12196));
      if (should_trace_ask_module1(Generate.it,0) == CTRUE)
       mtformat_module1(Generate.it,((char*)"==== Generate system file ~A \n"),0,list::alloc(1,GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->source),v46356)),((char*)"-s"))),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))))));
      else ;_void_(Optimize.OPT->cinterface = v12200);
      _void_(Optimize.OPT->properties = set::empty(Kernel._property));
      _void_(Optimize.OPT->objects = list::empty(Kernel._any));
      _void_(Optimize.OPT->functions = list::empty(Kernel._any));
      _void_(Optimize.OPT->need_to_close = set::empty(Kernel._any));
      _void_(Optimize.OPT->legal_modules = set_I_bag(v1140));
      use_as_output_port(v12200);
      princ_string(((char*)"// --- System configuration file for "));
      print_any(_string_(v46356));
      princ_string(((char*)" ---\n\n"));
      princ_string(((char*)"#include <claire.h>\n"));
      princ_string(((char*)"#include <Kernel.h>\n"));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        for (START(v39800); NEXT(v12208);)
        if (OBJECT(module,v12208)->made_of->length != 0)
         { princ_string(((char*)"#include <"));
          ident_symbol(OBJECT(symbol,(*Kernel.name)(v12208)));
          princ_string(((char*)".h>\n"));
          }
        }
      create_load_modules_string(v46356,v12200,v1140,v12197);
      if ((boolean_I_any(_oid_(_at_property1(Core.main,Kernel._list))) == CTRUE) && 
          (domain_I_restriction(GC_OBJECT(restriction,((restriction *) _at_property1(Core.main,Kernel._list)))) == Kernel._list))
       { char * v12203 = ((char*)"main_list");
        princ_string(((char*)"\nextern void "));
        princ_string(v12203);
        princ_string(((char*)"(list *l);\n"));
        princ_string(((char*)"void call_main() {"));
        princ_string(v12203);
        princ_string(((char*)"(ClEnv->params);}\n"));
        }
      else princ_string(((char*)"\nvoid call_main() {default_main();}\n"));
        putc_char1(_char_(((char*)"\n")[1 - 1]),v12200);
      breakline_void();
      breakline_void();
      princ_string(((char*)"class InitLoadModule {\n"));
      princ_string(((char*)"public:\n"));
      princ_string(((char*)"  static InitLoadModule single;\n"));
      princ_string(((char*)"  InitLoadModule() {\n"));
      princ_string(((char*)"    set_load_module(loadModules);\n"));
      princ_string(((char*)"    set_call_main(call_main);\n"));
      princ_string(((char*)"  }\n"));
      princ_string(((char*)"};\n\n"));
      princ_string(((char*)"InitLoadModule InitLoadModule::single = InitLoadModule();\n"));
      fclose_port1(v12200);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  create_load_modules_string(char *v46356,PortObject *v12200,list *v1140,OID v12197) { 
    
    GC_BIND;
    breakline_void();
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v12208);
      for (START(v1140); NEXT(v12208);)
      if ((*Kernel.status)(v12208) == ((OID)5))
       { princ_string(((char*)"void load_"));
        ident_symbol(OBJECT(symbol,(*Kernel.name)(v12208)));
        princ_string(((char*)"() {"));
        ident_symbol(OBJECT(symbol,(*Kernel.name)(v12208)));
        princ_string(((char*)".metaLoad();}\n"));
        }
      }
    princ_string(((char*)"\n\nvoid loadModules() \n"));
    new_block_void();
    princ_string(((char*)"//module definitions "));
    breakline_void();
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v12208);
      for (START(v1140); NEXT(v12208);)
      { GC_LOOP;
        if (((v12208 == _oid_(claire.it)) ? CTRUE : ((v12208 == _oid_(mClaire.it)) ? CTRUE : ((v12208 == _oid_(Kernel.it)) ? CTRUE : CFALSE))) != CTRUE)
         { ident_symbol(OBJECT(symbol,(*Kernel.name)(v12208)));
          princ_string(((char*)".initModule("));
          print_any(_string_(string_I_symbol(OBJECT(symbol,(*Kernel.name)(v12208)))));
          princ_string(((char*)","));
          expression_thing(OBJECT(module,v12208)->part_of,Core.nil->value);
          princ_string(((char*)","));
          (*Generate.expression)(GC_OID((*Optimize.c_code)(GC_OID(_oid_(OBJECT(module,v12208)->uses)),
              _oid_(Kernel._list))),
            Core.nil->value);
          princ_string(((char*)","));
          breakline_void();
          print_any(GC_OID((*Kernel.source)(v12208)));
          princ_string(((char*)","));
          (*Generate.expression)(GC_OID((*Optimize.c_code)(GC_OID(_oid_(OBJECT(module,v12208)->made_of)),
              _oid_(Kernel._list))),
            Core.nil->value);
          princ_string(((char*)");"));
          breakline_void();
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    princ_string(((char*)"//module load "));
    breakline_void();
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v12208);
      for (START(v1140); NEXT(v12208);)
      if (((CL_INT)OBJECT(module,v12208)->made_of->length > (CL_INT)0) && 
          ((*Kernel.status)(v12208) != ((OID)5)))
       { ident_symbol(OBJECT(symbol,(*Kernel.name)(v12208)));
        princ_string(((char*)".metaLoad();"));
        breakline_void();
        }
      }
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v12208);
      for (START(v1140); NEXT(v12208);)
      { GC_LOOP;
        { { OID  v12206 = GC_OID(get_property(Kernel.version,OBJECT(ClaireObject,v12208)));
            if (v12206 != CNULL)
             { ident_symbol(OBJECT(symbol,(*Kernel.name)(v12208)));
              princ_string(((char*)".it->version = "));
              print_any(v12206);
              princ_string(((char*)";"));
              breakline_void();
              }
            else ;}
          { OID  v12206 = GC_OID(get_property(Kernel.comment,OBJECT(ClaireObject,v12208)));
            if (v12206 != CNULL)
             { ident_symbol(OBJECT(symbol,(*Kernel.name)(v12208)));
              princ_string(((char*)".it->comment = "));
              print_any(v12206);
              princ_string(((char*)";"));
              breakline_void();
              }
            else ;}
          if ((*Kernel.status)(v12208) == ((OID)5))
           { ident_symbol(OBJECT(symbol,(*Kernel.name)(v12208)));
            princ_string(((char*)".it->evaluate = "));
            expression_any(_oid_(make_function_string(append_string(((char*)"load_"),string_I_symbol(OBJECT(symbol,(*Kernel.name)(v12208)))))),Kernel.cfalse);
            breakline_void();
            ident_symbol(OBJECT(symbol,(*Kernel.name)(v12208)));
            princ_string(((char*)".it->status = 2;"));
            breakline_void();
            }
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    princ_string(((char*)"ClEnv->module_I = "));
    { OID  v45638;
      if (INHERIT(OWNER(v12197),Kernel._module))
       v45638 = v12197;
      else v45638 = _oid_(claire.it);
        (*Generate.expression)(v45638,
        Core.nil->value);
      }
    princ_string(((char*)"; "));
    breakline_void();
    if ((CL_INT)Optimize.compiler->safety > (CL_INT)5)
     princ_string(((char*)"ClAlloc->statusGC = 2;\n"));
    if (Optimize.OPT->profile_ask == CTRUE)
     { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v12200);
      bag *v12200_support;
      v12200_support = GC_OBJECT(bag,Reader.PRdependent->graph);
      for (START(v12200_support); NEXT(v12200);)
      if (INHERIT(OWNER(v12200),Kernel._property))
       { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v50570);
        bag *v50570_support;
        v50570_support = OBJECT(set,nth_table1(Reader.PRdependent,v12200));
        for (START(v50570_support); NEXT(v50570);)
        if ((contain_ask_set(Optimize.OPT->to_remove,v50570) != CTRUE) && 
            (OBJECT(thing,v12200)->name->definition == OBJECT(thing,v50570)->name->definition))
         { princ_string(((char*)"PRdepends_property("));
          expression_thing(OBJECT(thing,v12200),Core.nil->value);
          princ_string(((char*)","));
          expression_thing(OBJECT(thing,v50570),Core.nil->value);
          princ_string(((char*)");\n"));
          }
        }
      }
    close_block_void();
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  create_dynload_module_module1(module *v12208) { 
    
    GC_BIND;
    breakline_void();
    princ_string(((char*)"\n\nextern \"C\" CL_EXPORT void dynLoad"));
    c_princ_symbol(v12208->name);
    princ_string(((char*)"() \n"));
    new_block_void();
    ident_symbol(v12208->name);
    princ_string(((char*)".initModule("));
    print_any(_string_(string_I_symbol(v12208->name)));
    princ_string(((char*)","));
    expression_thing(v12208->part_of,Core.nil->value);
    princ_string(((char*)","));
    (*Generate.expression)(GC_OID((*Optimize.c_code)(GC_OID(_oid_(v12208->uses)),
        _oid_(Kernel._list))),
      Core.nil->value);
    princ_string(((char*)","));
    breakline_void();
    print_any(GC_OID(_string_(v12208->source)));
    princ_string(((char*)","));
    (*Generate.expression)(GC_OID((*Optimize.c_code)(GC_OID(_oid_(v12208->made_of)),
        _oid_(Kernel._list))),
      Core.nil->value);
    princ_string(((char*)");"));
    breakline_void();
    if (((CL_INT)v12208->made_of->length > (CL_INT)0) && 
        (v12208->status != 5))
     { ident_symbol(v12208->name);
      princ_string(((char*)".metaLoad();"));
      breakline_void();
      }
    { char * v12206 = GC_STRING(v12208->version);
      if (v12206 == (NULL))
       ;else { ident_symbol(v12208->name);
          princ_string(((char*)".it->version = "));
          print_any(_string_(v12206));
          princ_string(((char*)";"));
          breakline_void();
          }
        }
    { char * v12206 = GC_STRING(v12208->comment);
      if (v12206 == (NULL))
       ;else { ident_symbol(v12208->name);
          princ_string(((char*)".it->comment = "));
          print_any(_string_(v12206));
          princ_string(((char*)";"));
          breakline_void();
          }
        }
    close_block_void();
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  methods_interface_c_producer(Generate_c_producer *v12187,ClaireClass *v12208) { 
    
    GC_BIND;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v12200);
      bag *v12200_support;
      v12200_support = OBJECT(list,nth_table1(Language.InterfaceList,_oid_(v12208)));
      for (START(v12200_support); NEXT(v12200);)
      { GC_LOOP;
        { ClaireObject * v12197 = GC_OBJECT(ClaireObject,_at_property1(OBJECT(property,v12200),v12208));
          if (should_trace_ask_module1(Generate.it,5) == CTRUE)
           mtformat_module1(Generate.it,((char*)"method interface ~S at ~S -> ~S \n"),5,list::alloc(3,v12200,
            _oid_(v12208),
            _oid_(v12197)));
          else ;if ((Kernel._method == v12197->isa) && 
              (get_property(Kernel.formula,v12197) != CNULL))
           { ClaireClass * v12203 = class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(_oid_(v12197)))));
            list * v22281 = GC_OBJECT(list,cdr_list(GC_OBJECT(list,OBJECT(lambda,(*Kernel.formula)(_oid_(v12197)))->vars)));
            breakline_void();
            princ_string(((char*)"CL_EXPORT "));
            interface_I_c_producer(v12187,v12203);
            princ_string(((char*)" "));
            (*Kernel.c_princ)(GC_OID((*Kernel.name)(v12200)));
            princ_string(((char*)"("));
            typed_args_list_list(v22281);
            princ_string(((char*)");  "));
            }
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  methods_bodies_c_producer(Generate_c_producer *v12187,ClaireClass *v12208) { 
    
    GC_BIND;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v12200);
      bag *v12200_support;
      v12200_support = OBJECT(list,nth_table1(Language.InterfaceList,_oid_(v12208)));
      for (START(v12200_support); NEXT(v12200);)
      { GC_LOOP;
        { ClaireObject * v12197 = GC_OBJECT(ClaireObject,_at_property1(OBJECT(property,v12200),v12208));
          if (should_trace_ask_module1(Generate.it,5) == CTRUE)
           mtformat_module1(Generate.it,((char*)"write method body ~S at ~S -> ~S \n"),5,list::alloc(3,v12200,
            _oid_(v12208),
            _oid_(v12197)));
          else ;if ((Kernel._method == v12197->isa) && 
              (get_property(Kernel.formula,v12197) != CNULL))
           { ClaireClass * v12203 = class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(_oid_(v12197)))));
            list * v22281 = GC_OBJECT(list,cdr_list(GC_OBJECT(list,OBJECT(lambda,(*Kernel.formula)(_oid_(v12197)))->vars)));
            breakline_void();
            princ_string(((char*)"// interface method "));
            breakline_void();
            breakline_void();
            princ_string(((char*)"CL_EXPORT "));
            interface_I_c_producer(v12187,v12203);
            princ_string(((char*)" "));
            class_princ_class(v12208);
            princ_string(((char*)"::"));
            (*Kernel.c_princ)(GC_OID((*Kernel.name)(v12200)));
            princ_string(((char*)"("));
            typed_args_list_list(v22281);
            princ_string(((char*)")"));
            breakline_void();
            princ_string(((char*)"  "));
            princ_string(((char*)"\t{ "));
            if (v12203 != Kernel._void)
             { princ_string(((char*)"return ("));
              interface_I_c_producer(v12187,v12203);
              princ_string(((char*)") "));
              }
            if ((OBJECT(ClaireBoolean,(*Kernel._sup)(GC_OID((*Kernel.dispatcher)(v12200)),
              ((OID)0)))) == CTRUE)
             { (*Generate.expression)(v12200,
                Core.nil->value);
              princ_string(((char*)"->fcall((CL_INT) this"));
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(v12206);
                for (START(v22281); NEXT(v12206);)
                { princ_string(((char*)",(CL_INT) "));
                  (*Generate.expression)(v12206,
                    Core.nil->value);
                  }
                }
              princ_string(((char*)")"));
              }
            else { c_princ_function(OBJECT(ClaireFunction,(*Optimize.functional_I)(_oid_(v12197))));
                princ_string(((char*)"(this"));
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(v12206);
                  for (START(v22281); NEXT(v12206);)
                  { princ_string(((char*)","));
                    (*Generate.expression)(v12206,
                      Core.nil->value);
                    }
                  }
                princ_string(((char*)")"));
                }
              princ_string(((char*)";}\n"));
            breakline_void();
            }
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL;}
  



/***** CLAIRE Compilation of file ./compile/copt.cl 
         [version 3.5.0 / safety 5] *****/

CL_EXPORT void  inline_exp_c_producer1(Generate_c_producer *v12187,Call_method1 *v46356,OID v44140) { 
    
    GC_BIND;
    { method * v12197 = v46356->arg;
      property * v12200 = v12197->selector;
      OID  v50104 = GC_OID(car_list(v46356->args));
      if ((v12200 == Kernel._dash) && 
          ((domain_I_restriction(v12197) == Kernel._integer) || 
              (domain_I_restriction(v12197) == Kernel._float)))
       { princ_string(((char*)"(-"));
        bexpression_any(v50104,v44140);
        princ_string(((char*)")"));
        }
      else if ((v12200 == Core.owner) && 
          (designated_ask_any(v50104) == CTRUE))
       { princ_string(((char*)"OWNER("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)")"));
        }
      else if ((v12200 == Core.sqrt) && 
          (domain_I_restriction(v12197) == Kernel._float))
       { princ_string(((char*)"sqrt("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)")"));
        }
      else if ((v12200 == Core.eval) && 
          (designated_ask_any(v50104) == CTRUE))
       { princ_string(((char*)"OPT_EVAL("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)")"));
        }
      else if (v12200 == Core.externC)
       (*Kernel.princ)(v50104);
      else if ((_oid_(v12197) == Generate._starlength_bag_star->value) && 
          (designated_ask_any(v50104) == CTRUE))
       { (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"->length"));
        }
      else if (_oid_(v12197) == Generate._starlength_string_star->value)
       { princ_string(((char*)"LENGTH_STRING("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)")"));
        }
      else if ((v12200 == Kernel.integer_I) && 
          ((domain_I_restriction(v12197) == Kernel._char) && 
            (designated_ask_any(v50104) == CTRUE)))
       { (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"->ascii"));
        }
      else if (_oid_(v12197) == Generate._starlength_array_star->value)
       { (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"[0]"));
        }
      else if ((_oid_(v12197) == Generate._starnot_star->value) && 
          (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v50104))),Kernel._boolean) == CTRUE))
       { princ_string(((char*)"(("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)" == Kernel.ctrue) ? CFALSE : CTRUE)"));
        }
      else print_external_call_c_producer(v12187,v46356,v44140);
        }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  inline_exp_c_producer2(Generate_c_producer *v12187,Call_method2 *v46356,OID v44140) { 
    
    GC_BIND;
    { method * v12197 = v46356->arg;
      property * v12200 = v12197->selector;
      OID  v50104 = GC_OID((*(v46356->args))[1]);
      OID  v50105 = GC_OID((*(v46356->args))[2]);
      if (should_trace_ask_module1(Generate.it,4) == CTRUE)
       mtformat_module1(Generate.it,((char*)"inline_exp2: a1 = ~S, a2 = ~S \n"),4,list::alloc(2,v50104,v50105));
      else ;if ((_oid_(v12197) == Generate._starmin_integer_star->value) && 
          ((designated_ask_any(v50104) == CTRUE) && 
            (designated_ask_any(v50105) == CTRUE)))
       { princ_string(((char*)"(("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)" <= "));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)") ? "));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)" : "));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)")"));
        }
      else if (_oid_(v12197) == Generate._starnth_char_star_star->value)
       { princ_string(((char*)"_char_("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"[(CL_INT)("));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)") - 1])"));
        }
      else if (_oid_(v12197) == Generate._star_plus_char_star_star->value)
       { princ_string(((char*)"("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)" + "));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)")"));
        }
      else if ((_oid_(v12197) == Generate._starmax_integer_star->value) && 
          ((designated_ask_any(v50104) == CTRUE) && 
            (designated_ask_any(v50105) == CTRUE)))
       { princ_string(((char*)"(("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)" <= "));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)") ? "));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)" : "));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)")"));
        }
      else if ((v12200 == Core.class_I) && 
          (INHERIT(OWNER(v50104),Kernel._symbol)))
       { princ_string(((char*)"("));
        ident_thing(defined_symbol(OBJECT(symbol,v50104)));
        princ_string(((char*)"._"));
        c_princ_string(string_v((*Kernel.string_I)(v50104)));
        princ_string(((char*)" = ClaireClass::make("));
        print_any(GC_OID((*Kernel.string_I)(v50104)));
        princ_string(((char*)","));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)","));
        ident_thing(OBJECT(thing,(*Kernel.module_I)(v50104)));
        princ_string(((char*)".it))"));
        }
      else if ((v12187->open_operators->memq(_oid_(v12200)) == CTRUE) && 
          (((v12200 != Kernel._7) || 
              ((CL_INT)5 <= (CL_INT)Optimize.compiler->safety)) && 
            ((equal((*(v12197->domain))[1],(*(v12197->domain))[2]) == CTRUE) && 
              ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v50104))),Kernel._integer) == CTRUE) || 
                  (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v50104))),Kernel._float) == CTRUE)))))
       { if (((CL_INT)Optimize.compiler->safety < (CL_INT)2) && 
            (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v50104))),Kernel._integer) == CTRUE))
         princ_string(((char*)"_integer_"));
        princ_string(((char*)"("));
        if (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v50104))),Kernel._integer) == CTRUE)
         princ_string(((char*)"(CL_INT)"));
        bexpression_any(v50104,v44140);
        princ_string(string_I_symbol(v12200->name));
        if (_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v50105))),Kernel._integer) == CTRUE)
         princ_string(((char*)"(CL_INT)"));
        bexpression_any(v50105,v44140);
        princ_string(((char*)")"));
        }
      else if ((_oid_(v12197) == Generate._starcontain_star->value) && 
          (identifiable_ask_any(v50105) == CTRUE))
       { (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"->memq("));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)")"));
        }
      else if (((_oid_(v12197) == Generate._starnth_list_star->value) && 
            ((CL_INT)2 <= (CL_INT)Optimize.compiler->safety)) || 
          (_oid_(v12197) == Generate._starnth_1_bag_star->value))
       { princ_string(((char*)"(*("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"))["));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)"]"));
        }
      else if ((v12200 == Kernel.add_I) && 
          (_inf_equal_type(domain_I_restriction(v12197),Kernel._bag) == CTRUE))
       { (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"->addFast((OID)"));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)")"));
        }
      else if ((_oid_(v12197) == Generate._starnth_string_star->value) && 
          ((CL_INT)2 <= (CL_INT)Optimize.compiler->safety))
       { princ_string(((char*)"_char_("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"["));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)" - 1])"));
        }
      else if (v12197->selector == Core.identical_ask)
       { princ_string(((char*)"("));
        (*Optimize.bool_exp)(_oid_(v46356),
          Kernel.ctrue,
          v44140);
        princ_string(((char*)" ? CTRUE : CFALSE)"));
        }
      else if (v12197->selector == Core.externC)
       { princ_string(((char*)"("));
        (*Generate.interface_I)(Generate.PRODUCER->value,
          v50105);
        princ_string(((char*)")("));
        (*Kernel.princ)(v50104);
        princ_string(((char*)")"));
        }
      else if ((v12200 == Core.inlineok_ask) && 
          (Kernel._string == OWNER(v50105)))
       { (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"->inlineDef("));
        print_any(v50105);
        princ_string(((char*)")"));
        }
      else print_external_call_c_producer(v12187,v46356,v44140);
        }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  inline_exp_c_producer3(Generate_c_producer *v12187,Call_method *v46356,OID v44140) { 
    
    GC_BIND;
    { method * v12197 = v46356->arg;
      ClaireBoolean * v12186 = Optimize.OPT->alloc_stack;
      OID  v50104 = GC_OID((*(v46356->args))[1]);
      OID  v50105 = GC_OID((*(v46356->args))[2]);
      OID  v50106 = GC_OID((*(v46356->args))[3]);
      _void_(Optimize.OPT->alloc_stack = CFALSE);
      if (should_trace_ask_module1(Generate.it,4) == CTRUE)
       mtformat_module1(Generate.it,((char*)"inline_exp: a1 = ~S, a2 = ~S, a3 = ~S \n"),4,list::alloc(3,v50104,
        v50105,
        v50106));
      else ;if ((_oid_(v12197) == Generate._starnth_equal_list_star->value) && 
          ((CL_INT)3 <= (CL_INT)Optimize.compiler->safety))
       { princ_string(((char*)"((*("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"))["));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)"]="));
        (*Generate.expression)(v50106,
          v44140);
        princ_string(((char*)")"));
        }
      else if ((domain_I_restriction(v12197) == Kernel._string) && 
          (((v12197->selector == Kernel.nth_equal) && 
                ((CL_INT)2 <= (CL_INT)Optimize.compiler->safety)) || 
              (v12197->selector == Kernel.nth_put)))
       { princ_string(((char*)"("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"["));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)" - 1] = (unsigned char) "));
        (*Generate.expression)(v50106,
          v44140);
        princ_string(((char*)"->ascii)"));
        }
      else if (_oid_(v12197) == Generate._starnth_1_string_star->value)
       { princ_string(((char*)"_char_("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"["));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)" - 1])"));
        }
      else if ((v12197->selector == Kernel.store) && 
          ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v50104))),Kernel._list) == CTRUE) && 
            (((v46356->args->length == 4) && 
                  ((*(v46356->args))[4] == Kernel.ctrue)) || 
                (v46356->args->length == 3))))
       { princ_string(((char*)"STOREI("));
        bexpression_any(v50104,v44140);
        princ_string(((char*)" /* 121 */,(CL_INT*)&("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"["));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)"]),(CL_INT)"));
        (*Generate.expression)(v50106,
          v44140);
        princ_string(((char*)")"));
        }
      else if ((v12197->selector == Kernel.store) && 
          ((_inf_equal_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v50104))),Kernel._array) == CTRUE) && 
            ((equal(_oid_(_exp_type(GC_OBJECT(ClaireType,member_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Optimize.c_type)(v50104))))),Kernel._float)),_oid_(Kernel.emptySet)) == CTRUE) && 
              (((v46356->args->length == 4) && 
                    ((*(v46356->args))[4] == Kernel.ctrue)) || 
                  (v46356->args->length == 3)))))
       { princ_string(((char*)"STOREI("));
        (*Generate.expression)(GC_OID(getC_any(v50104)),
          v50104);
        princ_string(((char*)" /* 129 */,(CL_INT*)&("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"["));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)"]),(CL_INT)"));
        (*Generate.expression)(v50106,
          v44140);
        princ_string(((char*)")"));
        }
      else if ((v12197->selector == Kernel.add_slot) && 
          (INHERIT(owner_any(getC_any(v50104)),Kernel._class)))
       { princ_string(((char*)"CL_ADD_SLOT("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)","));
        class_princ_class(OBJECT(ClaireClass,getC_any(v50104)));
        princ_string(((char*)","));
        (*Generate.expression)(v50105,
          v44140);
        princ_string(((char*)","));
        ident_symbol(OBJECT(symbol,(*Kernel.name)(GC_OID(getC_any(v50105)))));
        princ_string(((char*)","));
        (*Generate.expression)(GC_OID(getC_any(v50106)),
          v44140);
        princ_string(((char*)","));
        (*Generate.expression)(GC_OID((*(v46356->args))[4]),
          v44140);
        princ_string(((char*)")"));
        }
      else if (v12197->selector == Kernel.add_method)
       { if (INHERIT(OWNER(v50104),Kernel._property))
         { (*Generate.expression)(v50104,
            v44140);
          princ_string(((char*)"->add"));
          if ((CL_INT)v46356->args->length > (CL_INT)5)
           princ_string(((char*)"Float"));
          princ_string(((char*)"Method("));
          signature_I_c_producer(v12187,v50105);
          princ_string(((char*)","));
          (*Generate.expression)(v50106,
            v44140);
          princ_string(((char*)","));
          breakline_void();
          princ_string(((char*)"\t"));
          bitvector_I_c_producer(v12187,GC_OID((*(v46356->args))[4]));
          princ_string(((char*)","));
          (*Generate.expression)(GC_OID((*(v46356->args))[5]),
            v44140);
          if ((CL_INT)v46356->args->length > (CL_INT)5)
           { princ_string(((char*)","));
            breakline_void();
            expression_any(_oid_(make_function_string(append_string(GC_STRING(string_v((*Kernel.string_I)(GC_OID((*(v46356->args))[5])))),((char*)"_")))),v44140);
            }
          princ_string(((char*)")"));
          }
        else { princ_string(((char*)"add_method_property("));
            args_list_bag(GC_OBJECT(list,v46356->args),v44140,CTRUE);
            princ_string(((char*)")"));
            }
          }
      else { _void_(Optimize.OPT->alloc_stack = v12186);
          print_external_call_c_producer(v12187,v46356,v44140);
          }
        _void_(Optimize.OPT->alloc_stack = v12186);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  print_external_call_c_producer(Generate_c_producer *v12187,Call_method *v46356,OID v44140) { 
    
    GC_BIND;
    { method * v12197 = v46356->arg;
      list * v12196 = GC_OBJECT(list,v46356->args);
      CL_INT  v12198 = 1;
      list * v50496 = v12197->domain;
      ClaireBoolean * v50211 = Optimize.compiler->debug_ask->memq(_oid_(v12197->module_I));
      c_princ_function(OBJECT(ClaireFunction,(*Optimize.functional_I)(_oid_(v12197))));
      princ_string(((char*)"("));
      if ((CL_INT)v12196->length > (CL_INT)4)
       _void_(Optimize.OPT->level = ((CL_INT)Optimize.OPT->level+(CL_INT)1));
      if ((v12196->length == 1) && 
          (domain_I_restriction(v12197) == Kernel._void))
       v12196= (Kernel.nil);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        for (START(v12196); NEXT(v12208);)
        { if (v12198 != 1)
           { princ_string(((char*)","));
            if ((CL_INT)v12196->length > (CL_INT)4)
             breakline_void();
            }
          { ClaireClass * v50665 = psort_any((*(v50496))[v12198]);
            ClaireClass * v50666 = stupid_t_any1(v12208);
            if ((_inf_equalt_class(v50665,Kernel._object) == CTRUE) && 
                (_inf_equalt_class(v50666,v50665) != CTRUE))
             { princ_string(((char*)"("));
              class_princ_class(v50665);
              princ_string(((char*)" *) "));
              }
            }
          (*Generate.expression)(v12208,
            v44140);
          ++v12198;
          }
        }
      princ_string(((char*)")"));
      if ((INHERIT(v12197->range->isa,Kernel._tuple)) && 
          (Optimize.OPT->alloc_stack != CTRUE))
       princ_string(((char*)"->copyIfNeeded()"));
      if ((CL_INT)v12196->length > (CL_INT)4)
       _void_(Optimize.OPT->level = ((CL_INT)Optimize.OPT->level-(CL_INT)1));
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  inline_exp_c_producer5(Generate_c_producer *v12187,Call *v46356,OID v44140) { 
    
    GC_BIND;
    { property * v12200 = v46356->selector;
      OID  v50104 = GC_OID(car_list(v46356->args));
      CL_INT  v12198 = v46356->args->length;
      if (v12200 == Core.get_stack)
       { princ_string(((char*)"ClEnv->stack["));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"]"));
        }
      else if (v12200 == Optimize.safe)
       { CL_INT  v12209 = Optimize.compiler->safety;
        _void_(Optimize.compiler->safety = 1);
        (*Generate.expression)(GC_OID((*(v46356->args))[1]),
          v44140);
        _void_(Optimize.compiler->safety = v12209);
        }
      else if (v12200 == Core.base_I)
       princ_string(((char*)"ClEnv->base"));
      else if ((v12200 == Core.index_I) && 
          (v12198 == 1))
       princ_string(((char*)"ClEnv->index"));
      else if ((v12200 == Core.push_I) && 
          (v12198 == 1))
       { princ_string(((char*)"PUSH("));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)")"));
        }
      else if (v12200 == Core.put_stack)
       { princ_string(((char*)"(ClEnv->stack["));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)"]="));
        (*Generate.expression)(GC_OID((*(v46356->args))[2]),
          v44140);
        princ_string(((char*)")"));
        }
      else if (v12200 == Core.set_base)
       { princ_string(((char*)"(ClEnv->base= "));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)")"));
        }
      else if ((v12200 == Kernel.set_index) && 
          (v46356->args->length == 1))
       { princ_string(((char*)"(ClEnv->index= "));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)")"));
        }
      else if (v12200 == Optimize.object_I)
       { OID  v50105 = GC_OID((*(v46356->args))[2]);
        princ_string(((char*)"("));
        ident_thing(defined_symbol(OBJECT(symbol,v50104)));
        princ_string(((char*)"."));
        if (_inf_equal_type(OBJECT(ClaireType,v50105),Reader._reserved_keyword) == CTRUE)
         { princ_string(((char*)"_cl_"));
          c_princ_string(string_v((*Kernel.string_I)(v50104)));
          }
        else (*Language.ident)(v50104);
          princ_string(((char*)" = "));
        if ((v50105 == _oid_(Kernel._property)) && 
            (INHERIT(owner_any((*Kernel.value)(v50104)),Kernel._property)))
         { princ_string(((char*)"property::make("));
          print_any(GC_OID((*Kernel.string_I)(v50104)));
          princ_string(((char*)","));
          princ_integer(((CL_INT)(*Kernel.open)(GC_OID((*Kernel.value)(v50104)))));
          princ_string(((char*)","));
          expression_thing(OBJECT(thing,(*Kernel.module_I)(v50104)),Core.nil->value);
          princ_string(((char*)","));
          (*Generate.expression)(GC_OID((*Kernel.domain)(GC_OID((*Kernel.value)(v50104)))),
            Core.nil->value);
          princ_string(((char*)","));
          (*Kernel.princ)(GC_OID((*Kernel.dispatcher)(GC_OID((*Kernel.value)(v50104)))));
          princ_string(((char*)")"));
          }
        else { princ_string(((char*)"("));
            class_princ_class(OBJECT(ClaireClass,v50105));
            princ_string(((char*)" *) "));
            (*Generate.expression)(v50105,
              v44140);
            princ_string(((char*)"->instantiate("));
            print_any(GC_OID((*Kernel.string_I)(v50104)));
            princ_string(((char*)","));
            expression_thing(OBJECT(thing,(*Kernel.module_I)(v50104)),Core.nil->value);
            princ_string(((char*)")"));
            }
          princ_string(((char*)")"));
        }
      else if (v12200 == Optimize.anyObject_I)
       { princ_string(((char*)"(("));
        class_princ_class(OBJECT(ClaireClass,v50104));
        princ_string(((char*)" *) (*"));
        (*Generate.expression)(v50104,
          v44140);
        princ_string(((char*)")("));
        args_list_bag(GC_OBJECT(list,cdr_list(GC_OBJECT(list,v46356->args))),v44140,_sup_integer(v46356->args->length,2));
        princ_string(((char*)"))"));
        }
      else if ((OBJECT(ClaireBoolean,(*Generate.fcall_ask)(_oid_(v46356)))) == CTRUE)
       (*Generate.fcall_exp)(_oid_(v46356),
        v44140);
      else if ((CL_INT)v46356->args->length > (CL_INT)20)
       { if (v46356->selector == Kernel.store)
         { list * v12196 = GC_OBJECT(list,v46356->args);
          CL_INT  v12198 = v12196->length;
          CL_INT  v12197 = ((CL_INT)v12198/(CL_INT)10);
          princ_string(((char*)"("));
          { CL_INT  v12193 = 0;
            CL_INT  v22846 = v12197;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while (((CL_INT)v12193 <= (CL_INT)v22846))
              { GC_LOOP;
                princ_string(((char*)"(*"));
                expression_thing(Kernel.store,v44140);
                princ_string(((char*)")("));
                { list * v5088;
                  { list * v14827 = list::empty(Kernel.emptySet);
                    { CL_INT  v12194 = ((CL_INT)((CL_INT)v12193*(CL_INT)10)+(CL_INT)1);
                      CL_INT  v22847 = ((v12193 == v12197) ?
                        v12198 :
                        ((CL_INT)((CL_INT)v12193*(CL_INT)10)+(CL_INT)10) );
                      { CL_INT loop_handle = ClEnv->cHandle;
                        while (((CL_INT)v12194 <= (CL_INT)v22847))
                        { v14827->addFast((OID)(*(v12196))[v12194]);
                          ++v12194;
                          POP_SIGNAL;}
                        }
                      }
                    v5088 = GC_OBJECT(list,v14827);
                    }
                  args_list_bag(v5088,v44140,CTRUE);
                  }
                princ_string(((char*)")"));
                if (v12193 != v12197)
                 princ_string(((char*)","));
                ++v12193;
                GC_UNLOOP;POP_SIGNAL;}
              }
            }
          princ_string(((char*)")"));
          }
        else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[216] ~S has more than 20 parameters")),
            _oid_(list::alloc(1,_oid_(v46356))))));
          }
      else { princ_string(((char*)"(*"));
          expression_thing(v46356->selector,v44140);
          princ_string(((char*)")("));
          args_list_bag(GC_OBJECT(list,v46356->args),v44140,_sup_integer(v46356->args->length,1));
          princ_string(((char*)")"));
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT ClaireBoolean * fcall_ask_Call2_Generate(Call *v12208) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { ClaireBoolean *Result ;
      { property * v12200 = v12208->selector;
        OID  v50104 = GC_OID((*(v12208->args))[1]);
        CL_INT  v30793;
        { list * v6049;
          { bag * v22643 = v12208->args;
            list * v52675 = ((list *) empty_bag(v22643));
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(v12209);
              for (START(v22643); NEXT(v12209);)
              if ((OBJECT(ClaireBoolean,(*Optimize.c_gc_ask)(v12209))) == CTRUE)
               v52675->addFast((OID)v12209);
              }
            v6049 = GC_OBJECT(list,v52675);
            }
          v30793 = v6049->length;
          }
        { ClaireBoolean *v_and;
          { v_and = ((designated_ask_any(v50104) == CTRUE) ? CTRUE : (((CL_INT)v12200->dispatcher > (CL_INT)0) ? CTRUE : CFALSE));
            if (v_and == CFALSE) Result =CFALSE; 
            else { { list * v12196 = GC_OBJECT(list,cdr_list(GC_OBJECT(list,v12208->args)));
                ClaireType * v51223 = Kernel.emptySet;
                list * v50512;
                { { CL_INT loop_handle = ClEnv->cHandle;
                    bag *v_list; OID v_val;
                    OID v12209; CL_INT CLcount;
                    v_list = GC_OBJECT(list,v12208->args);
                     v50512 = v_list->clone();
                    for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                    { v12209 = (*(v_list))[CLcount];
                      v_val = _oid_(ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v12209))));
                      
                      (*((list *) v50512))[CLcount] = v_val;}
                    }
                  GC_OBJECT(list,v50512);}
                list * v58603 = GC_OBJECT(list,cdr_list(v50512));
                list * v50510 = GC_OBJECT(list,get_restrictions_Call2(v12208,v50512));
                ClaireBoolean * v60142;
                { ClaireBoolean *v_and;
                  { v_and = (((CL_INT)v50510->length > (CL_INT)0) ? CTRUE : CFALSE);
                    if (v_and == CFALSE) v60142 =CFALSE; 
                    else { { ClaireBoolean *v_or;
                        { v_or = ((v30793 == 0) ? CTRUE : CFALSE);
                          if (v_or == CTRUE) v_and =CTRUE; 
                          else { { OID  v7011;
                              { CL_INT loop_handle = ClEnv->cHandle;
                                ITERATE(v12197);
                                v7011= Kernel.cfalse;
                                for (START(v50510); NEXT(v12197);)
                                if (not_any(_oid_(nth_integer(status_I_restriction(OBJECT(restriction,v12197)),((CL_INT)(OID)(1))))) != CTRUE)
                                 { v7011 = Kernel.ctrue;
                                  ClEnv->cHandle = loop_handle;break;}
                                }
                              v_or = not_any(v7011);
                              }
                            if (v_or == CTRUE) v_and =CTRUE; 
                            else v_and = CFALSE;}
                          }
                        }
                      if (v_and == CFALSE) v60142 =CFALSE; 
                      else { v_and = ((((CL_INT)v12200->dispatcher > (CL_INT)0) && 
                            ((CL_INT)v12196->length <= (CL_INT)4)) ? CTRUE : (((CL_INT)v50510->length < (CL_INT)((CL_INT)(OID)(3))) ? CTRUE : CFALSE));
                        if (v_and == CFALSE) v60142 =CFALSE; 
                        else v60142 = CTRUE;}
                      }
                    }
                  }
                ClaireClass * v12203 = (((CL_INT)v50510->length > (CL_INT)0) ?
                  c_srange_method(OBJECT(method,(*(v50510))[1])) :
                  Kernel._void );
                ClaireBoolean * v45994;
                { OID  v7971;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    OID gc_local;
                    ITERATE(v12202);
                    v7971= Kernel.cfalse;
                    for (START(v50510); NEXT(v12202);)
                    { GC_LOOP;
                      { ClaireBoolean * g1886I;
                        { OID  v9893;
                          { GC__ANY(v51223 = U_type(v51223,domain_I_restriction(OBJECT(restriction,v12202))), 1);
                            v9893 = _oid_(((INHERIT(OWNER((*(OBJECT(restriction,v12202)->domain))[1]),Kernel._class)) ? ((last_list(OBJECT(restriction,v12202)->domain) != _oid_(Kernel._listargs)) ? ((tmatch_ask_list(v58603,GC_OBJECT(list,cdr_list(OBJECT(restriction,v12202)->domain))) == CTRUE) ? ((c_srange_method(OBJECT(method,v12202)) == v12203) ? CTRUE: CFALSE): CFALSE): CFALSE): CFALSE));
                            }
                          g1886I = not_any(v9893);
                          }
                        
                        if (g1886I == CTRUE) { GC_UNLOOP;v7971 = Kernel.ctrue;
                            ClEnv->cHandle = loop_handle;break;}
                          }
                      GC_UNLOOP; POP_SIGNAL;}
                    }
                  v45994 = not_any(v7971);
                  }
                ClaireBoolean * v63618 = (((v12203 == Kernel._integer) || 
                    ((v12203 == Kernel._object) || 
                      ((v12203 == Kernel._any) || 
                        (v12203 == Kernel._void)))) ? ((_inf_equal_type(v51223,Kernel._object) == CTRUE) ? ((_inf_equal_type(GC_OBJECT(ClaireType,ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v50104)))),v51223) == CTRUE) ? CTRUE: CFALSE): CFALSE): CFALSE);
                if (((OBJECT(ClaireBoolean,Generate.FCALLSTINKS->value)) == CTRUE) && 
                    ((((v60142 == CTRUE) ? ((v45994 == CTRUE) ? ((v63618 == CTRUE) ? CTRUE: CFALSE): CFALSE): CFALSE) != CTRUE) && 
                      ((CL_INT)v12200->dispatcher > (CL_INT)0)))
                 { if (should_trace_ask_module1(Generate.it,1) == CTRUE)
                   mtformat_module1(Generate.it,((char*)"**** fcall(~S) fails : selectorOK = ~S, lrOK = ~S, callOK = ~S\n"),1,GC_OBJECT(list,list::alloc(4,_oid_(v12208),
                    _oid_(v60142),
                    _oid_(v45994),
                    _oid_(v63618))));
                  else ;}
                v_and = ((v60142 == CTRUE) ? ((v45994 == CTRUE) ? ((v63618 == CTRUE) ? CTRUE: CFALSE): CFALSE): CFALSE);
                }
              if (v_and == CFALSE) Result =CFALSE; 
              else Result = CTRUE;}
            }
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT list * get_restrictions_Call2(Call *v12208,list *v50512) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { list *Result ;
      { property * v12200 = v12208->selector;
        ClaireBoolean * v50478 = ((class_I_type(OBJECT(ClaireType,(*(v50512))[1]))->open == ClEnv->open) ? CTRUE : CFALSE);
        list * v50510 = list::empty(Kernel._method);
        if ((v12200->dispatcher == 0) && 
            ((v50478 == CTRUE) || 
                (v12200->open == ClEnv->open)))
         ;else { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v12202);
            for (START(v12200->restrictions); NEXT(v12202);)
            { GC_LOOP;
              if (length_bag(_exp_list(OBJECT(restriction,v12202)->domain,v50512)) != 0)
               { if (Kernel._method == OBJECT(ClaireObject,v12202)->isa)
                 GC__ANY(v50510 = v50510->addFast((OID)v12202), 1);
                else { shrink_list(v50510,0);
                    GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                  }
              GC_UNLOOP; POP_SIGNAL;}
            }
          Result = v50510;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  fcall_exp_Call2_Generate(Call *v12208,OID v44140) { 
    
    GC_BIND;
    { property * v12200 = v12208->selector;
      OID  v50104 = GC_OID((*(v12208->args))[1]);
      list * v50512;
      { { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v12209; CL_INT CLcount;
          v_list = GC_OBJECT(list,v12208->args);
           v50512 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v12209 = (*(v_list))[CLcount];
            v_val = _oid_(ptype_type(OBJECT(ClaireType,(*Optimize.c_type)(v12209))));
            
            (*((list *) v50512))[CLcount] = v_val;}
          }
        GC_OBJECT(list,v50512);}
      list * v50510 = GC_OBJECT(list,get_restrictions_Call2(v12208,v50512));
      method * v12197 = OBJECT(method,(*(v50510))[1]);
      ClaireClass * v12203 = c_srange_method(v12197);
      if (v12203 == Kernel._void)
       princ_string(((char*)"_void_("));
      else if (v12203 == Kernel._object)
       princ_string(((char*)"_oid_("));
      else if ((v12203 == Kernel._integer) && 
          ((CL_INT)Optimize.compiler->safety <= (CL_INT)2))
       princ_string(((char*)"_integer_("));
      if (((CL_INT)v12200->dispatcher > (CL_INT)0) && 
          ((CL_INT)v50512->length <= (CL_INT)4))
       { show_opportunist_integer1(4);
        if (should_trace_ask_module1(Generate.it,4) == CTRUE)
         mtformat_module1(Generate.it,((char*)" `GREEN note: ~S is compiled with fast dispatch \n"),4,list::alloc(1,_oid_(v12208)));
        else ;if (v12203 == Kernel._object)
         princ_string(((char*)"(ClaireObject *) "));
        expression_thing(v12200,v44140);
        princ_string(((char*)"->fcall("));
        c_sorted_args_Call(v12208,v12197->srange,v44140,CTRUE);
        princ_string(((char*)")"));
        }
      else { list * v58540;
          { { bag * v58388 = v12200->definition;
              list * v46655 = ((list *) empty_bag(v58388));
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(v12208);
                for (START(v58388); NEXT(v12208);)
                if (v50510->memq(v12208) == CTRUE)
                 v46655->addFast((OID)v12208);
                }
              v58540 = GC_OBJECT(list,v46655);
              }
            GC_OBJECT(list,v58540);}
          show_opportunist_integer1(4);
          if (should_trace_ask_module1(Generate.it,4) == CTRUE)
           mtformat_module1(Generate.it,((char*)" `GREEN note: ~S is compiled with explicit dispatch (s = ~S) \n"),4,list::alloc(2,_oid_(v12208),_oid_(v12203)));
          else ;{ CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v12197);
            for (START(v58540); NEXT(v12197);)
            { GC_LOOP;
              { list * v39430;
                { { CL_INT loop_handle = ClEnv->cHandle;
                    bag *v_list; OID v_val;
                    OID v12208; CL_INT CLcount;
                    v_list = OBJECT(restriction,v12197)->domain;
                     v39430 = v_list->clone();
                    for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                    { v12208 = (*(v_list))[CLcount];
                      v_val = _oid_(psort_any(v12208));
                      
                      (*((list *) v39430))[CLcount] = v_val;}
                    }
                  GC_OBJECT(list,v39430);}
                if (v12197 != last_list(v58540))
                 { princ_string(((char*)"(INHERIT("));
                  if (INHERIT(OWNER(v50104),Optimize._to_CL))
                   { (*Generate.expression)(GC_OID((*Kernel.arg)(v50104)),
                      v44140);
                    princ_string(((char*)"->isa"));
                    }
                  else { princ_string(((char*)"OWNER("));
                      (*Generate.expression)(v50104,
                        v44140);
                      princ_string(((char*)")"));
                      }
                    princ_string(((char*)","));
                  expression_any(_oid_(domain_I_restriction(OBJECT(restriction,v12197))),v44140);
                  princ_string(((char*)") ?"));
                  breakline_void();
                  princ_string(((char*)" "));
                  if (v12203 == Kernel._object)
                   princ_string(((char*)"(ClaireObject *)"));
                  princ_string(((char*)" "));
                  c_princ_function(OBJECT(ClaireFunction,(*Optimize.functional_I)(v12197)));
                  princ_string(((char*)"(("));
                  class_princ_class(domain_I_restriction(OBJECT(restriction,v12197)));
                  princ_string(((char*)" *) "));
                  c_sorted_args_Call(v12208,v39430,v44140,CFALSE);
                  princ_string(((char*)")"));
                  if ((INHERIT(OBJECT(restriction,v12197)->range->isa,Kernel._tuple)) && 
                      (Optimize.OPT->alloc_stack != CTRUE))
                   princ_string(((char*)"->copyIfNeeded()"));
                  princ_string(((char*)" : "));
                  breakline_void();
                  princ_string(((char*)" "));
                  }
                else { if (v12203 == Kernel._object)
                     princ_string(((char*)"(ClaireObject *) "));
                    princ_string(((char*)" "));
                    c_princ_function(OBJECT(ClaireFunction,(*Optimize.functional_I)(v12197)));
                    princ_string(((char*)"(("));
                    (*Generate.interface_I)(Generate.PRODUCER->value,
                      _oid_(domain_I_restriction(OBJECT(restriction,v12197))));
                    princ_string(((char*)") "));
                    c_sorted_args_Call(v12208,v39430,v44140,CFALSE);
                    princ_string(((char*)")"));
                    if ((INHERIT(OBJECT(restriction,v12197)->range->isa,Kernel._tuple)) && 
                        (Optimize.OPT->alloc_stack != CTRUE))
                     princ_string(((char*)"->copyIfNeeded()"));
                    else ;{ CL_INT  v12193 = 1;
                      CL_INT  v22856 = ((CL_INT)v58540->length-(CL_INT)1);
                      { CL_INT loop_handle = ClEnv->cHandle;
                        while (((CL_INT)v12193 <= (CL_INT)v22856))
                        { princ_string(((char*)")"));
                          ++v12193;
                          POP_SIGNAL;}
                        }
                      }
                    }
                  }
              GC_UNLOOP; POP_SIGNAL;}
            }
          }
        if ((v12203 == Kernel._void) || 
          ((v12203 == Kernel._object) || 
            ((v12203 == Kernel._float) || 
              ((v12203 == Kernel._integer) && 
                  ((CL_INT)Optimize.compiler->safety <= (CL_INT)2)))))
       princ_string(((char*)")"));
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  c_sorted_arg_any(OID v12208,ClaireClass *v12203,OID v44140,ClaireBoolean *v46108) { 
    
    GC_BIND;
    if (v46108 == CTRUE)
     princ_string(((char*)"((CL_INT) "));
    if ((INHERIT(OWNER(v12208),Optimize._to_CL)) && (osort_any(_oid_(OBJECT(Compile_to_CL,v12208)->set_arg)) == v12203))
     (*Generate.expression)(GC_OID((*Kernel.arg)(v12208)),
      v44140);
    else if (v12203 == Kernel._any)
     (*Generate.expression)(v12208,
      v44140);
    else (*Generate.to_c)(Generate.PRODUCER->value,
        v12208,
        _oid_(v12203),
        v44140);
      if (v46108 == CTRUE)
     princ_string(((char*)")"));
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  c_sorted_args_Call(Call *v12208,list *v50511,OID v44140,ClaireBoolean *v46108) { 
    
    GC_BIND;
    { CL_INT  v12193 = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12209);
        for (START(v12208->args); NEXT(v12209);)
        { if (v12193 != 0)
           princ_string(((char*)","));
          ++v12193;
          c_sorted_arg_any(v12209,OBJECT(ClaireClass,(*(v50511))[v12193]),v44140,v46108);
          }
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  bitvector_I_c_producer(Generate_c_producer *v12187,OID v12208) { 
    
    GC_BIND;
    if (INHERIT(OWNER(v12208),Kernel._integer))
     bitvectorSum_integer(v12208);
    else if (INHERIT(OWNER(v12208),Optimize._to_CL))
     bitvector_I_c_producer(v12187,GC_OID(OBJECT(Compile_to_CL,v12208)->arg));
    else if (INHERIT(OWNER(v12208),Optimize._to_protect))
     bitvector_I_c_producer(v12187,GC_OID(OBJECT(Compile_to_protect,v12208)->arg));
    else (*Generate.expression)(v12208,
        Core.nil->value);
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  bitvectorSum_integer(CL_INT v12208) { 
    if (v12208 == 0)
     princ_string(((char*)"0"));
    else { ClaireBoolean * v12186 = CFALSE;
        CL_INT  v12193 = 1;
        CL_INT  v22857 = 6;
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)v12193 <= (CL_INT)v22857))
          { if (BCONTAIN(v12208,v12193))
             { if (v12186 == CTRUE)
               princ_string(((char*)"+"));
              else v12186= (CTRUE);
                princ_string(string_v((*(OBJECT(bag,Generate.bitvectorList->value)))[v12193]));
              }
            ++v12193;
            POP_SIGNAL;}
          }
        }
      POP_SIGNAL;}
  

CL_EXPORT void  signature_I_c_producer(Generate_c_producer *v12187,OID v12208) { 
    
    GC_BIND;
    if (INHERIT(OWNER(v12208),Kernel._list))
     { princ_string(((char*)"list::domain("));
      princ_integer(OBJECT(bag,v12208)->length);
      princ_string(((char*)","));
      { list * v32957;
        { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID v12209; CL_INT CLcount;
            v_list = OBJECT(bag,v12208);
             v32957 = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { v12209 = (*(v_list))[CLcount];
              v_val = c_gc_I_any1(GC_OID(getC_any(v12209)));
              
              (*((list *) v32957))[CLcount] = v_val;}
            }
          GC_OBJECT(list,v32957);}
        args_list_bag(v32957,Core.nil->value,_sup_integer(OBJECT(bag,v12208)->length,3));
        }
      princ_string(((char*)")"));
      }
    else if (INHERIT(OWNER(v12208),Optimize._to_C))
     signature_I_c_producer(v12187,GC_OID(OBJECT(Compile_to_C,v12208)->arg));
    else if (INHERIT(OWNER(v12208),Optimize._to_protect))
     signature_I_c_producer(v12187,GC_OID(OBJECT(Compile_to_protect,v12208)->arg));
    else if (INHERIT(OWNER(v12208),Language._List))
     signature_I_c_producer(v12187,GC_OID(_oid_(OBJECT(Construct,v12208)->args)));
    else if (INHERIT(OWNER(v12208),Language._Variable))
     expression_Variable(OBJECT(Variable,v12208),Core.nil->value);
    else { princ_string(((char*)"<fucking "));
        print_any(_oid_(OWNER(v12208)));
        princ_string(((char*)":"));
        print_any(v12208);
        princ_string(((char*)">"));
        }
      setenv_string(((char*)"CLDEBUG=0"));
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT OID  getC_any(OID v12208) { 
    
    GC_BIND;
    { OID Result = 0;
      if (INHERIT(OWNER(v12208),Optimize._to_CL))
       Result = getC_any(GC_OID(OBJECT(Compile_to_CL,v12208)->arg));
      else if (INHERIT(OWNER(v12208),Optimize._to_protect))
       Result = getC_any(GC_OID(OBJECT(Compile_to_protect,v12208)->arg));
      else if (INHERIT(OWNER(v12208),Core._global_variable))
       { if (nativeVar_ask_global_variable(OBJECT(global_variable,v12208)) == CTRUE)
         Result = v12208;
        else { Compile_to_C * v60472 = ((Compile_to_C *) GC_OBJECT(Compile_to_C,new_object_class(Optimize._to_C)));
            _void_(v60472->arg = v12208);
            _void_(v60472->set_arg = Kernel._type);
            add_I_property(Kernel.instances,Optimize._to_C,11,_oid_(v60472));
            Result = _oid_(close_Instruction1(v60472));
            }
          }
      else Result = v12208;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  gassign_c_producer(Generate_c_producer *v12187,Gassign *v46356,OID v44140) { 
    
    GC_BIND;
    if (v46356->var->store_ask == CTRUE)
     { princ_string(((char*)"(STOREI("));
      expression_global_variable(v46356->var,_oid_(v46356->var));
      princ_string(((char*)" /*  404 */,(CL_INT*)&("));
      expression_global_variable(v46356->var,v44140);
      princ_string(((char*)"),(CL_INT)"));
      (*Generate.expression)(v46356->arg,
        v44140);
      princ_string(((char*)"))"));
      }
    else { princ_string(((char*)"("));
        expression_global_variable(v46356->var,v44140);
        princ_string(((char*)"= "));
        (*Generate.expression)(v46356->arg,
          v44140);
        princ_string(((char*)")"));
        }
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  call_slot_c_producer(Generate_c_producer *v12187,Call_slot *v46356,OID v44140) { 
    
    GC_BIND;
    { OID  v12202;
      { { OID  v47209 = CNULL;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v12202);
            for (START(Core.preread->restrictions); NEXT(v12202);)
            { GC_LOOP;
              if ((v12202 != (*(Core.preread->restrictions))[1]) && 
                  (tmatch_ask_list(list::alloc(2,_oid_(OWNER(_oid_(v46356->selector->selector))),GC_OID((*Optimize.c_type)(GC_OID(v46356->arg)))),OBJECT(restriction,v12202)->domain) == CTRUE))
               { v47209= (v12202);
                GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
              GC_UNLOOP; POP_SIGNAL;}
            }
          v12202 = v47209;
          }
        GC_OID(v12202);}
      if (v12202 != CNULL)
       { princ_string(((char*)"("));
        { OID  v33918;
          { { OID  v34879;
              { { Call * v60472 = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  _void_(v60472->selector = Core.preread);
                  _void_(v60472->args = list::alloc(2,_oid_(v46356->selector->selector),GC_OID(v46356->arg)));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(v60472));
                  v34879 = _oid_(close_Instruction1(v60472));
                  }
                GC_OID(v34879);}
              v33918 = (*Optimize.c_code)(v34879);
              }
            GC_OID(v33918);}
          (*Generate.expression)(v33918,
            v44140);
          }
        princ_string(((char*)","));
        }
      if (v46356->test == CTRUE)
       { princ_string((((INHERIT(v46356->selector->srange,Kernel._cl_import)) || 
            ((INHERIT(v46356->selector->srange,Kernel._string)) || 
              ((INHERIT(v46356->selector->srange,Kernel._array)) || 
                (INHERIT(v46356->selector->srange,Kernel._object))))) ?
          ((char*)"NOTNULL") :
          ((char*)"KNOWN") ));
        princ_string(((char*)"("));
        expression_thing(v46356->selector->selector,v44140);
        princ_string(((char*)","));
        }
      c_member_c_producer(v12187,
        GC_OID(v46356->arg),
        psort_any(_oid_(domain_I_restriction(v46356->selector))),
        v46356->selector->selector,
        v44140);
      if (v46356->test == CTRUE)
       princ_string(((char*)")"));
      if (v12202 != CNULL)
       princ_string(((char*)")"));
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  call_table_c_producer(Generate_c_producer *v12187,Call_table *v46356,OID v44140) { 
    
    GC_BIND;
    { table * v12185 = v46356->selector;
      OID  v12200 = v12185->params;
      OID  v12196 = v46356->arg;
      if (v46356->test == CTRUE)
       { princ_string(((char*)"KNOWN("));
        expression_thing(v12185,v44140);
        princ_string(((char*)","));
        }
      princ_string(((char*)"(*("));
      expression_thing(v12185,v44140);
      princ_string(((char*)"->graph))["));
      if (INHERIT(OWNER(v12200),Kernel._integer))
       { (*Generate.expression)(v12196,
          v44140);
        princ_string(((char*)" - "));
        princ_integer(v12200);
        }
      else if (INHERIT(OWNER(v12200),Kernel._list))
       { (*Generate.expression)((*(OBJECT(bag,(*Core.args)(v12196))))[1],
          v44140);
        princ_string(((char*)" * "));
        (*Kernel.princ)((*(OBJECT(bag,v12200)))[1]);
        princ_string(((char*)" + "));
        (*Generate.expression)((*(OBJECT(bag,(*Core.args)(v12196))))[2],
          v44140);
        princ_string(((char*)" - "));
        (*Kernel.princ)((*(OBJECT(bag,v12200)))[2]);
        }
      princ_string(((char*)"]"));
      if (v46356->test == CTRUE)
       princ_string(((char*)")"));
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  call_array_c_producer(Generate_c_producer *v12187,Call_array *v46356,OID v44140) { 
    
    GC_BIND;
    if (v46356->test == _oid_(Kernel._float))
     { princ_string(((char*)"((double *) "));
      (*Generate.expression)(v46356->selector,
        v44140);
      princ_string(((char*)")["));
      (*Generate.expression)(v46356->arg,
        v44140);
      princ_string(((char*)"]"));
      }
    else { princ_string(((char*)"((OID *) "));
        (*Generate.expression)(v46356->selector,
          v44140);
        princ_string(((char*)")["));
        (*Generate.expression)(v46356->arg,
          v44140);
        princ_string(((char*)"]"));
        }
      GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  update_c_producer(Generate_c_producer *v12187,Update *v46356,OID v44140) { 
    
    GC_BIND;
    { OID  v12200 = v46356->selector;
      OID  v12185 = v46356->arg;
      OID  v12206 = v46356->value;
      OID  v12208 = v46356->var;
      ClaireClass * v12203 = OBJECT(ClaireClass,(*Optimize.c_sort)(v12206));
      if ((INHERIT(OWNER(v12200),Kernel._relation)) && ((((OBJECT(ClaireRelation,v12200)->if_write == CNULL) ? CTRUE : CFALSE) != CTRUE) && 
          ((v12185 != _oid_(Kernel.put)) && 
            (v12185 != _oid_(Core.put_store)))))
       { c_princ_string(string_I_symbol(OBJECT(symbol,(*Kernel.name)(v12200))));
        princ_string(((char*)"_write("));
        (*Generate.expression)(GC_OID((*Kernel.arg)(v12208)),
          v44140);
        princ_string(((char*)","));
        (*Generate.expression)(v12206,
          v44140);
        princ_string(((char*)")"));
        }
      else if ((INHERIT(OWNER(v12200),Kernel._relation)) && ((OBJECT(ClaireRelation,v12200)->store_ask == CTRUE) || 
          (v12185 == _oid_(Core.put_store))))
       { if ((v12203 == Kernel._any) || 
            (v12203 == Kernel._integer))
         { princ_string(((char*)"STOREI("));
          (*Generate.expression)(GC_OID((*Kernel.arg)(v12208)),
            v44140);
          princ_string(((char*)" /* 464 */,(CL_INT*)&("));
          (*Generate.expression)(v12208,
            v44140);
          princ_string(((char*)"),(CL_INT)"));
          (*Generate.expression)(v12206,
            v44140);
          princ_string(((char*)")"));
          }
        else if (v12203 == Kernel._float)
         { princ_string(((char*)"STOREF("));
          (*Generate.expression)(v12208,
            v44140);
          princ_string(((char*)",(double*)&("));
          (*Generate.expression)(v12208,
            v44140);
          princ_string(((char*)"),"));
          (*Generate.expression)(v12206,
            v44140);
          princ_string(((char*)")"));
          }
        else { princ_string(((char*)"STOREO("));
            (*Generate.expression)(v12208,
              v44140);
            princ_string(((char*)",&("));
            (*Generate.expression)(v12208,
              v44140);
            princ_string(((char*)"),"));
            (*Generate.expression)(v12206,
              v44140);
            princ_string(((char*)")"));
            }
          }
      else { princ_string(((char*)"_void_("));
          (*Generate.expression)(v12208,
            v44140);
          princ_string(((char*)" = "));
          (*Generate.expression)(v12206,
            v44140);
          princ_string(((char*)")"));
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  object_test_c_producer(Generate_c_producer *v12187,OID v50104,ClaireBoolean *v32308,OID v44140) { 
    princ_string(((char*)"(CTAG("));
    (*Generate.expression)(v50104,
      v44140);
    princ_string(((char*)") "));
    sign_equal_boolean(v32308);
    princ_string(((char*)" OBJ_CODE)"));
    POP_SIGNAL;}
  

CL_EXPORT void  exp_to_protect_c_producer(Generate_c_producer *v12187,Compile_to_protect *v46356,OID v44140) { 
    
    GC_BIND;
    { OID  v50729 = GC_OID((*Optimize.c_type)(GC_OID(v46356->arg)));
      if ((Optimize.OPT->protection == CTRUE) && 
          ((need_protect_any(GC_OID(v46356->arg)) == CTRUE) && 
            (((Optimize.OPT->alloc_stack == CTRUE) ? ((_inf_equal_type(OBJECT(ClaireType,v50729),Kernel._tuple) == CTRUE) ? CTRUE: CFALSE): CFALSE) != CTRUE)))
       { OID  v12208 = GC_OID(v46356->arg);
        ClaireClass * v12203 = OBJECT(ClaireClass,(*Optimize.c_sort)(v12208));
        princ_string(gc_protect_class(v12203));
        princ_string(((char*)"("));
        if (INHERIT(v12203,Kernel._object))
         { class_princ_class(psort_any(GC_OID((*Core.glb)(GC_OID((*Optimize.c_type)(v12208)),
            _oid_(v12203)))));
          princ_string(((char*)","));
          (*Generate.expression)(GC_OID(v46356->arg),
            v44140);
          }
        else (*Generate.expression)(GC_OID(v46356->arg),
            v44140);
          princ_string(((char*)")"));
        }
      else (*Generate.expression)(GC_OID(v46356->arg),
          v44140);
        }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  macro_c_producer(Generate_c_producer *v12187) { 
    ;POP_SIGNAL;}
  

CL_EXPORT void  init_var_c_producer(Generate_c_producer *v12187,ClaireClass *v12203) { 
    ;POP_SIGNAL;}
  

CL_EXPORT void  any_interface_c_producer(Generate_c_producer *v12187) { 
    princ_string(((char*)"OID"));
    POP_SIGNAL;}
  

CL_EXPORT void  pointer_cast_c_producer(Generate_c_producer *v12187,ClaireClass *v12203) { 
    princ_string(((char*)"("));
    class_princ_c_producer(v12187,v12203);
    princ_string(((char*)" *)"));
    POP_SIGNAL;}
  

CL_EXPORT void  exp_Assign_c_producer(Generate_c_producer *v12187,Assign *v46356,OID v44140) { 
    
    GC_BIND;
    { OID  v12208 = v46356->arg;
      OID  v12206 = v46356->var;
      (*Language.ident)(Generate.PRODUCER->value,
        v12206);
      princ_string(((char*)"= "));
      if (get_property(Kernel.range,OBJECT(ClaireObject,v12206)) == _oid_(Kernel._integer))
       princ_string(((char*)"(CL_INT)"));
      princ_string(((char*)"("));
      (*Generate.expression)(v12208,
        v44140);
      princ_string(((char*)")"));
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  stat_handle_c_producer(Generate_c_producer *v12187,ClaireHandle *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    new_block_void();
    princ_string(((char*)"ClaireHandler c_handle = ClaireHandler();"));
    breakline_void();
    princ_string(((char*)"if ERROR_IN "));
    breakline_void();
    new_block_void();
    statement_any(GC_OID(v46356->arg),v12203,v44140);
    princ_string(((char*)"ERROR_FREE;"));
    close_block_void();
    princ_string(((char*)"else if (belong_to(_oid_(ClEnv->exception_I),"));
    (*Generate.expression)(GC_OID((*Optimize.c_code)(GC_OID(v46356->test),
        _oid_(Kernel._any))),
      _oid_(Kernel.emptySet));
    princ_string(((char*)") == CTRUE)"));
    breakline_void();
    new_block_void();
    princ_string(((char*)"c_handle.catchIt();"));
    statement_any(GC_OID(v46356->other),v12203,v44140);
    close_block_void();
    princ_string(((char*)"else PREVIOUS_HANDLER;"));
    close_block_void();
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  stat_construct_c_producer(Generate_c_producer *v12187,Construct *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    if (boolean_I_any(v12203) != CTRUE)
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[202] A do should have been used for ~S")),
      _oid_(list::alloc(1,_oid_(v46356))))));
    { char * v12206 = GC_STRING(check_var_string(((char*)"v_bag"),v12203,v44140));
      bag * v46137;
      { ClaireObject *V_CC ;
        if (INHERIT(v46356->isa,Language._List))
         V_CC = list::empty();
        else if (INHERIT(v46356->isa,Language._Set))
         V_CC = set::empty();
        else if (INHERIT(v46356->isa,Language._Tuple))
         V_CC = tuple::empty();
        else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"BUG: ~S")),
            _oid_(list::alloc(1,_oid_(v46356))))));
          v46137= (bag *) V_CC;}
      new_block_void();
      if (get_property(Kernel.of,v46356) != CNULL)
       (*Kernel.cast_I)(_oid_(v46137),
        GC_OID((*Kernel.of)(_oid_(v46356))));
      { ClaireBoolean * g1894I;
        { OID  v37762;
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(v12208);
            v37762= Kernel.cfalse;
            bag *v12208_support;
            v12208_support = GC_OBJECT(list,v46356->args);
            for (START(v12208_support); NEXT(v12208);)
            if (c_func_any(v12208) != CTRUE)
             { v37762 = Kernel.ctrue;
              ClEnv->cHandle = loop_handle;break;}
            }
          g1894I = boolean_I_any(v37762);
          }
        
        if (g1894I == CTRUE) { princ_string(((char*)"OID "));
            princ_string(v12206);
            princ_string(((char*)";"));
            breakline_void();
            }
          }
      if (Optimize.OPT->protection == CTRUE)
       { _void_(v12187->stat = ((CL_INT)v12187->stat+(CL_INT)1));
        princ_string(((char*)"GC_ANY("));
        }
      (*Kernel.c_princ)(v12203);
      princ_string(((char*)"= "));
      (*Generate.bag_expression)(Generate.PRODUCER->value,
        _oid_(v46137->isa),
        _oid_(v46137),
        _oid_(of_bag(v46137)),
        v44140);
      if (Optimize.OPT->protection == CTRUE)
       princ_string(((char*)")"));
      princ_string(((char*)";"));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        bag *v12208_support;
        v12208_support = GC_OBJECT(list,v46356->args);
        for (START(v12208_support); NEXT(v12208);)
        { ClaireBoolean * v12190 = c_func_any(v12208);
          breakline_void();
          if (v12190 != CTRUE)
           statement_any(v12208,_string_(v12206),v44140);
          princ_string(((char*)"(("));
          { OID  v38723;
            if (INHERIT(v46356->isa,Language._List))
             v38723 = _oid_(Kernel._list);
            else if (INHERIT(v46356->isa,Language._Set))
             v38723 = _oid_(Kernel._set);
            else v38723 = _oid_(Kernel._tuple);
              print_any(v38723);
            }
          princ_string(((char*)" *) "));
          (*Kernel.c_princ)(v12203);
          princ_string(((char*)")"));
          addFast_c_producer(v12187);
          princ_string(((char*)"((OID)"));
          if (v12190 == CTRUE)
           (*Generate.expression)(v12208,
            v44140);
          else c_princ_string(v12206);
            princ_string(((char*)");"));
          }
        }
      close_block_void();
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  stat_while_c_producer(Generate_c_producer *v12187,While *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    new_block_void();
    { ClaireBoolean * v50273 = ((c_func_any(GC_OID(v46356->test)) == CTRUE) ? ((v46356->other != CTRUE) ? ((gc_usage_any(GC_OID(v46356->test),OBJECT(ClaireBoolean,v44140)) == Kernel.cfalse) ? CTRUE: CFALSE): CFALSE): CFALSE);
      char * v12206 = GC_STRING(check_var_string(((char*)"v_while"),v12203,v44140));
      ClaireBoolean * v45471 = Optimize.OPT->loop_gc;
      ClaireBoolean * v39230 = ((Optimize.OPT->loop_gc == CTRUE) ? ((gc_usage_any(GC_OID(v46356->arg),CTRUE) != Kernel.cfalse) ? CTRUE: CFALSE): CFALSE);
      princ_string(((char*)"CL_INT loop_handle = ClEnv->cHandle;"));
      breakline_void();
      _void_(Optimize.OPT->loop_gc = v39230);
      if (v39230 == CTRUE)
       { princ_string(((char*)"OID gc_local;"));
        breakline_void();
        }
      if (v50273 != CTRUE)
       { interface_I_class(Kernel._boolean);
        princ_string(v12206);
        princ_string(((char*)";"));
        breakline_void();
        }
      if (Kernel._string == OWNER(v12203))
       { (*Kernel.c_princ)(v12203);
        princ_string(((char*)"= _oid_("));
        expression_boolean(CFALSE,v44140);
        princ_string(((char*)");"));
        breakline_void();
        }
      if (v50273 == CTRUE)
       { princ_string(((char*)"while ("));
        (*Optimize.bool_exp)(GC_OID(v46356->test),
          _oid_(not_any(_oid_(v46356->other))),
          v44140);
        princ_string(((char*)")"));
        }
      else { { OID  v39684;
            { if (v46356->other == CTRUE)
               v39684 = Kernel.cfalse;
              else v39684 = v46356->test;
                GC_OID(v39684);}
            statement_any(v39684,_string_(v12206),Kernel.ctrue);
            }
          breakline_void();
          princ_string(((char*)"while ("));
          princ_string(v12206);
          princ_string(((char*)" "));
          if (v46356->other == CTRUE)
           princ_string(((char*)"!="));
          else princ_string(((char*)"=="));
            princ_string(((char*)" CTRUE)"));
          }
        breakline_void();
      new_block_void();
      if (v39230 == CTRUE)
       { princ_string(((char*)"GC_LOOP;"));
        breakline_void();
        }
      { OID  v40645;
        if (Kernel._string == OWNER(v12203))
         v40645 = v12203;
        else v40645 = CNULL;
          inner_statement_any(GC_OID(v46356->arg),_oid_(Kernel.emptySet),v40645);
        }
      if (v50273 != CTRUE)
       statement_any(GC_OID(v46356->test),_string_(v12206),Kernel.ctrue);
      if (v39230 == CTRUE)
       princ_string(((char*)"GC_UNLOOP;"));
      _void_(Optimize.OPT->loop_gc = v45471);
      princ_string(((char*)"POP_SIGNAL;"));
      close_block_void();
      }
    close_block_void();
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  stat_gassign_c_producer(Generate_c_producer *v12187,Gassign *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    new_block_void();
    interface_I_c_producer(v12187,((nativeVar_ask_global_variable(v46356->var) == CTRUE) ?
      getRange_global_variable(v46356->var) :
      Kernel._any ));
    princ_string(((char*)" truc;"));
    statement_any(GC_OID(v46356->arg),_string_(((char*)"truc")),v44140);
    breakline_void();
    if (v46356->var->store_ask == CTRUE)
     { princ_string(((char*)"STOREI("));
      expression_global_variable(v46356->var,v44140);
      princ_string(((char*)" /* 590 */ ,(CL_INT*)&("));
      expression_global_variable(v46356->var,v44140);
      princ_string(((char*)"),truc);"));
      }
    else { princ_string(((char*)"("));
        expression_global_variable(v46356->var,v44140);
        princ_string(((char*)" = truc);"));
        }
      close_block_void();
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  stat_for_c_producer(Generate_c_producer *v12187,For *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    { char * v12206 = GC_STRING(c_string_c_producer1(v12187,GC_OBJECT(Variable,v46356->var)));
      ClaireBoolean * v45471 = Optimize.OPT->loop_gc;
      ClaireBoolean * v39230 = ((Optimize.OPT->loop_gc == CTRUE) ? ((gc_usage_any(GC_OID(v46356->arg),CTRUE) != Kernel.cfalse) ? CTRUE: CFALSE): CFALSE);
      new_block_void();
      princ_string(((char*)"CL_INT loop_handle = ClEnv->cHandle;"));
      breakline_void();
      _void_(Optimize.OPT->loop_gc = v39230);
      if (v39230 == CTRUE)
       { princ_string(((char*)"OID gc_local;"));
        breakline_void();
        }
      princ_string(((char*)"ITERATE("));
      c_princ_string(v12206);
      princ_string(((char*)");"));
      if (Kernel._string == OWNER(v12203))
       { breakline_void();
        (*Kernel.c_princ)(v12203);
        princ_string(((char*)"= Kernel.cfalse;"));
        }
      breakline_void();
      if ((c_func_any(GC_OID(v46356->set_arg)) == CTRUE) && 
          (designated_ask_any(GC_OID(v46356->set_arg)) == CTRUE))
       { princ_string(((char*)"for (START("));
        (*Generate.expression)(GC_OID(v46356->set_arg),
          v44140);
        princ_string(((char*)"); NEXT("));
        c_princ_string(v12206);
        princ_string(((char*)");)"));
        }
      else { char * v50759 = GC_STRING(append_string(v12206,((char*)"_support")));
          princ_string(((char*)"bag *"));
          c_princ_string(v50759);
          princ_string(((char*)";"));
          breakline_void();
          statement_any(GC_OID(v46356->set_arg),_string_(v50759),v44140);
          princ_string(((char*)"for (START("));
          c_princ_string(v50759);
          princ_string(((char*)"); NEXT("));
          c_princ_string(v12206);
          princ_string(((char*)");)"));
          }
        breakline_void();
      if (v39230 == CTRUE)
       { new_block_void();
        princ_string(((char*)"GC_LOOP;"));
        breakline_void();
        }
      if ((Optimize.OPT->profile_ask == CTRUE) && 
          (_Z_any1(Optimize.OPT->in_method,Kernel._object) == CTRUE))
       { if (Optimize.OPT->loop_gc != CTRUE)
         new_block_void();
        princ_string(((char*)"PRloop(PR_x);"));
        breakline_void();
        }
      { OID  v41606;
        if (Kernel._string == OWNER(v12203))
         v41606 = v12203;
        else v41606 = CNULL;
          statement_any(GC_OID(v46356->arg),_oid_(Kernel.emptySet),v41606);
        }
      if (v39230 == CTRUE)
       { princ_string(((char*)"GC_UNLOOP; POP_SIGNAL;"));
        close_block_void();
        }
      if ((Optimize.OPT->profile_ask == CTRUE) && 
          ((_Z_any1(Optimize.OPT->in_method,Kernel._object) == CTRUE) && 
            (Optimize.OPT->loop_gc != CTRUE)))
       close_block_void();
      _void_(Optimize.OPT->loop_gc = v45471);
      close_block_void();
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  stat_iteration_c_producer(Generate_c_producer *v12187,Iteration *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    if (boolean_I_any(v12203) != CTRUE)
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[203] you should have used a FOR here:~S")),
      _oid_(list::alloc(1,_oid_(v46356))))));
    { char * v12206 = GC_STRING(c_string_c_producer1(v12187,GC_OBJECT(Variable,v46356->var)));
      char * v45731 = GC_STRING(check_var_string(((char*)"v_val"),v12203,v44140));
      char * v14015 = GC_STRING(check_var_string(((char*)"v_list"),v12203,v44140));
      ClaireBoolean * v45471 = Optimize.OPT->loop_gc;
      ClaireBoolean * v39230 = ((Optimize.OPT->loop_gc == CTRUE) ? ((gc_usage_any(GC_OID(v46356->arg),CTRUE) != Kernel.cfalse) ? CTRUE: CFALSE): CFALSE);
      new_block_void();
      princ_string(((char*)"CL_INT loop_handle = ClEnv->cHandle;"));
      breakline_void();
      _void_(Optimize.OPT->loop_gc = v39230);
      if (v39230 == CTRUE)
       { princ_string(((char*)"OID gc_local;"));
        breakline_void();
        }
      princ_string(((char*)"bag *"));
      princ_string(v14015);
      princ_string(((char*)"; OID "));
      princ_string(v45731);
      princ_string(((char*)";"));
      breakline_void();
      princ_string(((char*)"OID "));
      c_princ_string(v12206);
      princ_string(((char*)"; CL_INT CLcount;"));
      breakline_void();
      statement_any(GC_OID(v46356->set_arg),_string_(v14015),v44140);
      princ_string(((char*)" "));
      (*Kernel.c_princ)(v12203);
      princ_string(((char*)" = "));
      princ_string(v14015);
      princ_string(((char*)"->clone("));
      if (get_property(Kernel.of,v46356) != CNULL)
       (*Generate.expression)(GC_OID((*Optimize.c_code)(GC_OID((*Kernel.of)(_oid_(v46356))),
          _oid_(Kernel._type))),
        Core.nil->value);
      princ_string(((char*)")"));
      princ_string(((char*)";"));
      breakline_void();
      princ_string(((char*)"for (CLcount= 1; CLcount <= "));
      princ_string(v14015);
      princ_string(((char*)"->length; CLcount++)"));
      breakline_void();
      new_block_void();
      if (v39230 == CTRUE)
       { princ_string(((char*)"GC_LOOP;"));
        breakline_void();
        }
      c_princ_string(v12206);
      princ_string(((char*)" = (*("));
      princ_string(v14015);
      princ_string(((char*)"))[CLcount];"));
      breakline_void();
      statement_any(GC_OID(v46356->arg),_string_(v45731),Kernel.ctrue);
      breakline_void();
      princ_string(((char*)"(*((list *) "));
      (*Kernel.princ)(v12203);
      princ_string(((char*)"))[CLcount] = "));
      princ_string(v45731);
      princ_string(((char*)";"));
      if (v39230 == CTRUE)
       princ_string(((char*)"GC_UNLOOP; POP_SIGNAL;"));
      _void_(Optimize.OPT->loop_gc = v45471);
      close_block_void();
      close_block_void();
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  stat_super_c_producer(Generate_c_producer *v12187,Super *v46356,OID v12203,OID v44140) { 
    
    GC_BIND;
    { char * v63944 = GC_STRING(check_var_string(((char*)"v_rec"),v12203,v44140));
      new_block_void();
      princ_string(((char*)"OID "));
      princ_string(v63944);
      princ_string(((char*)";"));
      breakline_void();
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        bag *v12208_support;
        v12208_support = GC_OBJECT(list,v46356->args);
        for (START(v12208_support); NEXT(v12208);)
        { statement_any(v12208,_string_(v63944),v44140);
          princ_string(((char*)"PUSH("));
          princ_string(v63944);
          princ_string(((char*)");"));
          breakline_void();
          }
        }
      if (Kernel._string == OWNER(v12203))
       { c_princ_string(string_v(v12203));
        princ_string(((char*)"="));
        }
      expression_thing(v46356->selector,v44140);
      princ_string(((char*)"->super("));
      (*Generate.expression)(GC_OID(_oid_(v46356->cast_to)),
        v44140);
      princ_string(((char*)","));
      princ_integer(v46356->args->length);
      princ_string(((char*)");"));
      close_block_void();
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  stat_let_c_producer(Generate_c_producer *v12187,Let *v46356,OID v12203,OID v44140) { 
    
    GC_RESERVE(3);  // v3.3.39 optim !
    { char * v50573 = GC_STRING(string_v((*Generate.c_string)(Generate.PRODUCER->value,
        _oid_(v46356->var->pname))));
      if ((v50573[1 - 1] == ((unsigned char)'C')) && 
          (v50573[2 - 1] == ((unsigned char)'%')))
       _void_(v46356->var->pname = gensym_void());
      }
    { OID  v12206 = GC_OID((*Generate.c_string)(Generate.PRODUCER->value,
        GC_OID(_oid_(v46356->var))));
      ClaireBoolean * v12186 = Optimize.OPT->alloc_stack;
      OID  v12208 = GC_OID(v46356->value);
      ClaireBoolean * v12190 = CTRUE;
      new_block_void();
      _void_(Optimize.OPT->alloc_stack = CFALSE);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((v12190 == CTRUE))
        { GC_LOOP;
          if (INHERIT(v46356->isa,Language._Let_star))
           _void_(Optimize.OPT->alloc_stack = CTRUE);
          interface_I_class(sort_Variable(GC_OBJECT(Variable,v46356->var)));
          princ_string(((char*)" "));
          c_princ_string(string_v(v12206));
          if (c_func_any(v12208) == CTRUE)
           { princ_string(((char*)" = "));
            if (bool_exp_ask_any(v12208) == CTRUE)
             (*Generate.bool_exp_I)(Generate.PRODUCER->value,
              v12208,
              v44140);
            else (*Generate.expression)(v12208,
                v44140);
              princ_string(((char*)";"));
            breakline_void();
            }
          else { (*Generate.init_var)(Generate.PRODUCER->value,
                _oid_(sort_Variable(GC_OBJECT(Variable,v46356->var))));
              princ_string(((char*)";"));
              breakline_void();
              statement_any(v12208,v12206,v44140);
              }
            if (INHERIT(v46356->isa,Language._Let_star))
           _void_(Optimize.OPT->alloc_stack = CFALSE);
          if (INHERIT(OWNER(v46356->arg),Language._Let))
           { GC__ANY(v46356 = OBJECT(Let,v46356->arg), 1);
            GC__OID(v12206 = (*Generate.c_string)(Generate.PRODUCER->value,
              GC_OID(_oid_(v46356->var))), 2);
            GC__OID(v12208 = v46356->value, 3);
            }
          else v12190= (CFALSE);
            GC_UNLOOP;POP_SIGNAL;}
        }
      _void_(Optimize.OPT->alloc_stack = v12186);
      inner_statement_any(GC_OID(v46356->arg),v12203,v44140);
      close_block_void();
      }
    GC_UNBIND; POP_SIGNAL;}
  



/***** CLAIRE Compilation of file ./compile/gusage.cl 
         [version 3.5.0 / safety 5] *****/

CL_EXPORT char * external_I_module1(module *v12197) { 
    { char *Result ;
      Result = ((((v12197->external == (NULL)) ? CTRUE : CFALSE) != CTRUE) ?
        v12197->external :
        string_I_symbol(v12197->name) );
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT module * string2module_string1(char *v12203) { 
    { module *Result ;
      { ClaireObject *V_CC ;
        { OID  v12197 = value_string(v12203);
          if (INHERIT(OWNER(v12197),Kernel._module))
           V_CC = OBJECT(module,v12197);
          else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~A is not a module")),
              _oid_(list::alloc(1,_string_(v12203))))));
            }
        Result= (module *) V_CC;}
      POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT char * home_path_void1() { 
    
    GC_BIND;
    { char *Result ;
      { char * v12190 = GC_STRING(realpath_string(GC_STRING(getenv_string(((char*)"_")))));
        CL_INT  v12196 = rfind_string2(v12190,string_v(Core._starfs_star->value));
        Result = substring_string(v12190,1,((CL_INT)v12196-(CL_INT)5));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  function_compile_string1(char *v46356,char *v32610) { 
    
    GC_BIND;
    _void_(Optimize.OPT->need_modules = set::empty());
    { char * v13948 = GC_STRING(append_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->headers_dir),v46356)),((char*)".h")));
      _void_(Optimize.OPT->legal_modules = set_I_class(Kernel._module));
      _void_(Optimize.OPT->properties = set::empty(Kernel._property));
      _void_(Optimize.OPT->objects = list::empty(Kernel._any));
      _void_(Optimize.OPT->functions = list::empty(Kernel._any));
      _void_(Optimize.OPT->cinterface = fopen_string1(v13948,((char*)"w")));
      _void_(Optimize.OPT->cfile = _string_(v46356));
      if (isfile_ask_string(append_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->source),v46356)),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension))) == CTRUE)
       unlink_string(append_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->source),v46356)),GC_STRING(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension)));
      generate_file_string2(v32610,GC_STRING(_7_string(GC_STRING(Optimize.compiler->source),v46356)));
      use_as_output_port(Optimize.OPT->cinterface);
      breakline_void();
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v12208);
        bag *v12208_support;
        v12208_support = GC_OBJECT(set,Optimize.OPT->need_modules);
        for (START(v12208_support); NEXT(v12208);)
        if ((OBJECT(module,v12208)->made_of->length != 0) && 
            (contain_ask_list(OBJECT(list,Optimize.claire_modules->value),v12208) != CTRUE))
         { princ_string(((char*)"#include <"));
          ident_symbol(OBJECT(symbol,(*Kernel.name)(v12208)));
          princ_string(((char*)".h>\n"));
          }
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v12196);
        bag *v12196_support;
        v12196_support = GC_OBJECT(list,Optimize.OPT->functions);
        for (START(v12196_support); NEXT(v12196);)
        { GC_LOOP;
          { OID  v48297 = GC_OID((*Kernel.nth)(v12196,
              ((OID)1)));
            OID  v22281 = GC_OID((*Kernel.nth)(v12196,
              ((OID)2)));
            OID  v12203 = GC_OID((*Kernel.nth)(v12196,
              ((OID)3)));
            princ_string(((char*)"\nextern "));
            (*Generate.interface_I)(Generate.PRODUCER->value,
              v12203);
            princ_string(((char*)" "));
            (*Kernel.c_princ)(v48297);
            princ_string(((char*)"("));
            typed_args_list_list(OBJECT(list,v22281));
            princ_string(((char*)");"));
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      princ_string(((char*)"\n"));
      fclose_port1(GC_OBJECT(PortObject,Optimize.OPT->cinterface));
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT char * libpath_void1() { 
    
    GC_BIND;
    { char *Result ;
      Result = (((isfile_ask_string(_7_string(Optimize.compiler->env,((char*)"sclaire"))) == CTRUE) || 
          (isfile_ask_string(_7_string(Optimize.compiler->env,((char*)"sclaire.exe"))) == CTRUE)) ?
        Optimize.compiler->env :
        _7_string(GC_STRING(home_path_void1()),((char*)"lib")) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  libpath_I_module1(module *v12197) { 
    
    GC_BIND;
    { char * v52057 = ((equal_string(Optimize.compiler->env,((char*)"ntv")) == CTRUE) ?
        ((char*)".lib") :
        ((equal_string(lower_string(sys_name_void()),((char*)"os/390")) == CTRUE) ?
          ((char*)".x") :
          ((char*)".o") ) );
      OID  v7235;
      { { OID  v52259 = CNULL;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v12208);
            bag *v12208_support;
            v12208_support = GC_OBJECT(list,OBJECT(bag,Reader.used_modules->value));
            for (START(v12208_support); NEXT(v12208);)
            { GC_LOOP;
              if ((*(OBJECT(bag,v12208)))[1] == _oid_(v12197))
               { v52259= (v12208);
                GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
              GC_UNLOOP; POP_SIGNAL;}
            }
          v7235 = v52259;
          }
        GC_OID(v7235);}
      if (v7235 != CNULL)
       { tuple * v12208 = OBJECT(tuple,v7235);
        char * v50539 = GC_STRING(_7_string(string_v((*(v12208))[2]),GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"v"),GC_STRING(release_void()))),((char*)"-"))),GC_STRING(Optimize.compiler->env)))));
        char * v59500 = GC_STRING(_7_string(string_v((*(v12208))[2]),GC_STRING(Optimize.compiler->env)));
        if (isdir_ask_string(v59500) == CTRUE)
         { if (isfile_ask_string(append_string(GC_STRING(_7_string(v59500,external_I_module1(v12197))),((char*)".dll"))) == CTRUE)
           fcopy_string(GC_STRING(append_string(GC_STRING(_7_string(v59500,external_I_module1(v12197))),((char*)".dll"))),GC_STRING(append_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->env),external_I_module1(v12197))),((char*)".dll"))));
          if (isfile_ask_string(append_string(GC_STRING(_7_string(v59500,external_I_module1(v12197))),v52057)) == CTRUE)
           princ_string(append_string(GC_STRING(_7_string(v59500,external_I_module1(v12197))),v52057));
          else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Local module ~S have no library file [~A]")),
              _oid_(list::alloc(2,_oid_(v12197),_string_(v59500))))));
            }
        else { if (isfile_ask_string(append_string(GC_STRING(_7_string(v50539,external_I_module1(v12197))),((char*)".dll"))) == CTRUE)
             fcopy_string(GC_STRING(append_string(GC_STRING(_7_string(v50539,external_I_module1(v12197))),((char*)".dll"))),GC_STRING(append_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->env),external_I_module1(v12197))),((char*)".dll"))));
            if (isfile_ask_string(append_string(GC_STRING(_7_string(v50539,external_I_module1(v12197))),v52057)) == CTRUE)
             princ_string(append_string(GC_STRING(_7_string(v50539,external_I_module1(v12197))),v52057));
            else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"External module ~S have no library file [~A]")),
                _oid_(list::alloc(2,_oid_(v12197),_string_(v50539))))));
              }
          }
      else if (isfile_ask_string(append_string(GC_STRING(_7_string(GC_STRING(libpath_void1()),external_I_module1(v12197))),v52057)) == CTRUE)
       princ_string(append_string(GC_STRING(_7_string(GC_STRING(libpath_void1()),external_I_module1(v12197))),v52057));
      else if (equal_string(lower_string(sys_name_void()),((char*)"os/390")) == CTRUE)
       princ_string(append_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->env),external_I_module1(v12197))),((char*)".o")));
      else princ_string(append_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->env),external_I_module1(v12197))),v52057));
        }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  headers_I_void1() { 
    
    GC_BIND;
    { char * v16496 = GC_STRING(Optimize.compiler->env);
      char * v48268 = ((char*)"-I");
      char * v52057 = ((equal_string(Optimize.compiler->env,((char*)"ntv")) == CTRUE) ?
        ((char*)".obj") :
        ((char*)".o") );
      if (((CL_INT)LENGTH_STRING(Optimize.compiler->headers_dir) > (CL_INT)0) && 
          (length_bag(entries_string1(GC_STRING(Optimize.compiler->headers_dir),((char*)"*.h*"))) != 0))
       { princ_string(v48268);
        princ_string(Optimize.compiler->headers_dir);
        princ_string(((char*)" "));
        }
      if ((isdir_ask_string(((char*)"include")) == CTRUE) && 
          ((equal_string(Optimize.compiler->headers_dir,((char*)"include")) != CTRUE) && 
            (length_bag(entries_string1(((char*)"include"),((char*)"*.h*"))) != 0)))
       { princ_string(v48268);
        princ_string(((char*)"include "));
        }
      if ((((isfile_ask_string(_7_string(GC_STRING(Optimize.compiler->env),((char*)"sclaire"))) == CTRUE) ? CTRUE : ((isfile_ask_string(_7_string(GC_STRING(Optimize.compiler->env),((char*)"sclaire.exe"))) == CTRUE) ? CTRUE : CFALSE)) != CTRUE) && 
          (isdir_ask_string(_7_string(GC_STRING(home_path_void1()),((char*)"include"))) == CTRUE))
       { princ_string(v48268);
        princ_string(_7_string(GC_STRING(home_path_void1()),((char*)"include")));
        princ_string(((char*)" "));
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v12193);
        bag *v12193_support;
        v12193_support = GC_OBJECT(list,OBJECT(bag,Reader.used_modules->value));
        for (START(v12193_support); NEXT(v12193);)
        { GC_LOOP;
          { char * v50539 = GC_STRING(_7_string(string_v((*(OBJECT(bag,v12193)))[2]),GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"v"),GC_STRING(release_void()))),((char*)"-"))),GC_STRING(Optimize.compiler->env)))));
            char * v59500 = string_v((*(OBJECT(bag,v12193)))[2]);
            module * v12197 = OBJECT(module,(*(OBJECT(bag,v12193)))[1]);
            if (isdir_ask_string(_7_string(v59500,GC_STRING(Optimize.compiler->env))) == CTRUE)
             { if ((isdir_ask_string(_7_string(v59500,((char*)"include"))) == CTRUE) && 
                  (length_bag(entries_string2(GC_STRING(_7_string(v59500,((char*)"include"))))) != 0))
               { princ_string(v48268);
                princ_string(_7_string(v59500,((char*)"include")));
                princ_string(((char*)" "));
                }
              }
            else if (isfile_ask_string(append_string(GC_STRING(_7_string(v50539,external_I_module1(v12197))),v52057)) == CTRUE)
             { princ_string(v48268);
              princ_string(v50539);
              princ_string(((char*)" "));
              }
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  lib_I_any1(OID v12197,list *v12196) { 
    
    GC_BIND;
    { char * v6727 = ((equal_string(Optimize.compiler->env,((char*)"ntv")) == CTRUE) ?
        ((char*)".lib") :
        ((equal_string(lower_string(sys_name_void()),((char*)"os/390")) == CTRUE) ?
          ((char*)".x") :
          ((char*)".o") ) );
      ClaireBoolean * v42472 = CTRUE;
      char * v19914 = ((char*)" ");
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v50477);
        for (START(v12196); NEXT(v50477);)
        { GC_LOOP;
          if (OBJECT(module,v50477)->made_of->length != 0)
           { if (((equal_string(lower_string(sys_name_void()),((char*)"os/390")) == CTRUE) ? ((v50477 == _oid_(Core.it)) ? CTRUE: CFALSE): CFALSE) != CTRUE)
             { if (v42472 == CTRUE)
               v42472= (CFALSE);
              else princ_string(v19914);
                libpath_I_module1(OBJECT(module,v50477));
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(v12203);
                bag *v12203_support;
                v12203_support = GC_OBJECT(list,OBJECT(module,v50477)->uses);
                for (START(v12203_support); NEXT(v12203);)
                if (Kernel._string == OWNER(v12203))
                 { princ_string(v19914);
                  (*Kernel.princ)(v12203);
                  princ_string(v6727);
                  }
                }
              }
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v50477);
        bag *v50477_support;
        v50477_support = GC_OBJECT(list,Optimize.compiler->libraries);
        for (START(v50477_support); NEXT(v50477);)
        { if (v42472 == CTRUE)
           v42472= (CFALSE);
          else princ_string(v19914);
            if (equal(v50477,_string_(((char*)"Kernel"))) == CTRUE)
           { princ_string(v19914);
            princ_string(libpath_void1());
            princ_string(string_v(Core._starfs_star->value));
            princ_string(((equal_string(v6727,((char*)".x")) == CTRUE) ?
              ((char*)"boot") :
              string_v(v50477) ));
            princ_string(v6727);
            }
          else if ((equal(v50477,_string_(((char*)"wclConsole"))) == CTRUE) || 
              ((equal(v50477,_string_(((char*)"noConsole"))) == CTRUE) || 
                (equal(v50477,_string_(((char*)"Console"))) == CTRUE)))
           { princ_string(v19914);
            princ_string(libpath_void1());
            princ_string(string_v(Core._starfs_star->value));
            princ_string(string_v(v50477));
            princ_string(((equal_string(v6727,((char*)".x")) == CTRUE) ?
              ((char*)".o") :
              v6727 ));
            }
          else { princ_string(v19914);
              princ_string(string_v(v50477));
              }
            }
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  importlib_I_any1(OID v12197,list *v12196) { 
    
    GC_BIND;
    { char * v6727 = ((equal_string(Optimize.compiler->env,((char*)"ntv")) == CTRUE) ?
        ((char*)".lib") :
        ((equal_string(lower_string(sys_name_void()),((char*)"os/390")) == CTRUE) ?
          ((char*)".x") :
          ((char*)".o") ) );
      ClaireBoolean * v42472 = CTRUE;
      char * v19914 = ((char*)" ");
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v50477);
        for (START(v12196); NEXT(v50477);)
        { GC_LOOP;
          if ((OBJECT(module,v50477)->made_of->length != 0) && 
              (equal(v12197,v50477) != CTRUE))
           { if (((equal_string(lower_string(sys_name_void()),((char*)"os/390")) == CTRUE) ? ((v50477 == _oid_(Core.it)) ? CTRUE: CFALSE): CFALSE) != CTRUE)
             { if (v42472 == CTRUE)
               v42472= (CFALSE);
              else princ_string(v19914);
                libpath_I_module1(OBJECT(module,v50477));
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(v12203);
                bag *v12203_support;
                v12203_support = GC_OBJECT(list,OBJECT(module,v50477)->uses);
                for (START(v12203_support); NEXT(v12203);)
                if (Kernel._string == OWNER(v12203))
                 { princ_string(v19914);
                  (*Kernel.princ)(v12203);
                  princ_string(v6727);
                  }
                }
              }
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v50477);
        bag *v50477_support;
        v50477_support = GC_OBJECT(list,Optimize.compiler->libraries);
        for (START(v50477_support); NEXT(v50477);)
        if (((equal(v50477,_string_(((char*)"wclConsole"))) == CTRUE) ? CTRUE : ((equal(v50477,_string_(((char*)"noConsole"))) == CTRUE) ? CTRUE : ((equal(v50477,_string_(((char*)"Console"))) == CTRUE) ? CTRUE : CFALSE))) != CTRUE)
         { if (v42472 == CTRUE)
           v42472= (CFALSE);
          else princ_string(v19914);
            if (equal(v50477,_string_(((char*)"Kernel"))) == CTRUE)
           { princ_string(v19914);
            princ_string(libpath_void1());
            princ_string(string_v(Core._starfs_star->value));
            princ_string(((equal_string(v6727,((char*)".x")) == CTRUE) ?
              ((char*)"boot") :
              string_v(v50477) ));
            princ_string(v6727);
            }
          else if ((equal(v50477,_string_(((char*)"Core"))) == CTRUE) && 
              (equal_string(v6727,((char*)".x")) == CTRUE))
           ;else { princ_string(v19914);
              princ_string(string_v(v50477));
              }
            }
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  files_I_any1(OID v12197,ClaireBoolean *v8893,char *v26321) { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    { char * v13318 = GC_STRING(((v8893 == CTRUE) ?
        ((char*)"") :
        append_string(((char*)"$T"),GC_STRING(string_v(Core._starfs_star->value))) ));
      char * v46621 = GC_STRING(((v8893 == CTRUE) ?
        ((char*)"") :
        append_string(((char*)"$U"),GC_STRING(string_v(Core._starfs_star->value))) ));
      char * v16478 = ((equal_string(Optimize.compiler->env,((char*)"ntv")) == CTRUE) ?
        ((char*)"obj") :
        ((char*)"o") );
      char * v29665 = ((v8893 == CTRUE) ?
        ((char*)",") :
        ((char*)" ") );
      princ_string(v13318);
      princ_string((((v8893 == CTRUE) || 
          (Kernel._string == OWNER(v12197))) ?
        append_string(v26321,((char*)"-s")) :
        external_I_module1(OBJECT(module,v12197)) ));
      princ_string(((char*)"."));
      princ_string(v16478);
      if (INHERIT(OWNER(v12197),Kernel._module))
       { if (v8893 != CTRUE)
         { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v50312);
          for (START(OBJECT(module,v12197)->made_of); NEXT(v50312);)
          { GC_LOOP;
            if (match_wildcard_ask_string(string_v(v50312),((char*)"*@PATH_INFO@*")) == CTRUE)
             { list * v12204 = GC_OBJECT(list,explode_string(string_v(v50312),((char*)"@PATH_INFO@")));
              char * v43817 = GC_STRING(replace_string(string_v((*(v12204))[1]),GC_STRING(string_v(Core._starfs_star->value)),((char*)"-")));
              if (equal_string(left_string(v43817,2),((char*)"./")) == CTRUE)
               GC__STRING(v43817 = substring_string(v43817,3,LENGTH_STRING(v43817)), 1);
              if (equal_string(left_string(v43817,1),((char*)".")) == CTRUE)
               GC__STRING(v43817 = substring_string(v43817,2,LENGTH_STRING(v43817)), 2);
              princ_string(v29665);
              princ_string(v13318);
              princ_string(v43817);
              princ_string(((char*)"."));
              princ_string(v16478);
              princ_string(((char*)" "));
              }
            else if ((match_wildcard_ask_string(string_v(v50312),((char*)"*.cl")) == CTRUE) || 
                (match_wildcard_ask_string(string_v(v50312),((char*)"*.*")) != CTRUE))
             { princ_string(v29665);
              princ_string(v13318);
              princ_string(replace_string(string_v(v50312),((char*)".cl"),((char*)"")));
              princ_string(((char*)"."));
              princ_string(v16478);
              princ_string(((char*)" "));
              }
            else if (match_wildcard_ask_string(string_v(v50312),((char*)"*.h*")) != CTRUE)
             { princ_string(v29665);
              princ_string(v46621);
              princ_string(replace_string(GC_STRING(replace_string(string_v(v50312),((char*)".cpp"),((char*)""))),((char*)".cc"),((char*)"")));
              princ_string(((char*)"."));
              princ_string(v16478);
              princ_string(((char*)" "));
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        else ;}
      else if (Kernel._string == OWNER(v12197))
       { princ_string(v29665);
        princ_string(v13318);
        princ_string(string_v(v12197));
        princ_string(((char*)"."));
        princ_string(v16478);
        }
      else ;}
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT char * job_option_void1() { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { char *Result ;
      { char * v63960 = ((char*)"");
        { CL_INT  v12193 = 1;
          CL_INT  v23559 = ((CL_INT)length_bag(ClEnv->params)-(CL_INT)1);
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)v12193 <= (CL_INT)v23559))
            { GC_LOOP;
              if (equal((*(ClEnv->params))[v12193],_string_(((char*)"-make"))) == CTRUE)
               { GC__STRING(v63960 = append_string(string_v((*(ClEnv->params))[((CL_INT)v12193+(CL_INT)1)]),((char*)" ")), 1);
                ++v12193;
                }
              ++v12193;
              GC_UNLOOP;POP_SIGNAL;}
            }
          }
        Result = v63960;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  cmakefile_any1(OID v12197,char *v61574) { 
    
    GC_BIND;
    { list * v12196 = GC_OBJECT(list,add_modules_list(GC_OBJECT(list,OBJECT(list,Optimize.claire_modules->value))));
      char * v12190 = ((INHERIT(OWNER(v12197),Kernel._module)) ?
        string_I_symbol(OBJECT(thing,v12197)->name) :
        v61574 );
      char * v55809 = GC_STRING(Optimize.compiler->env);
      if (contain_ask_list(ClEnv->params,_string_(((char*)"-relink"))) != CTRUE)
       { if ((equal_string(v61574,((char*)"")) != CTRUE) && 
            ((OBJECT(ClaireBoolean,Generate.clcc_ask->value)) == CTRUE))
         generate_s_file_string(v61574,v12196,v12197);
        if ((contain_ask_list(Optimize.compiler->libraries,_string_(((char*)"noConsole"))) != CTRUE) && 
            (contain_ask_list(Optimize.compiler->libraries,_string_(((char*)"wclConsole"))) != CTRUE))
         GC_OBJECT(list,Optimize.compiler->libraries)->addFast((OID)_string_(((char*)"Console")));
        if (equal_string(v55809,((char*)"ntv")) == CTRUE)
         create_makefile_nt_any1(v12197,v61574,v12196);
        else create_makefile_unix_any1(v12197,v61574,v12196);
          }
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  create_makefile_nt_any1(OID v12197,char *v61574,list *v12196) { 
    
    GC_BIND;
    print_in_string_void();
    princ_string(((char*)"CL /nologo /DCLPC "));
    headers_I_void1();
    princ_string(string_v(Optimize.claire_options->value));
    if (INHERIT(OWNER(v12197),Kernel._module))
     { princ_string(((char*)" /Tp"));
      princ_string(Optimize.compiler->source);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(external_I_module1(OBJECT(module,v12197)));
      princ_string(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension);
      princ_string(((char*)" /Fo"));
      princ_string(Optimize.compiler->env);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(external_I_module1(OBJECT(module,v12197)));
      princ_string(((char*)".obj"));
      }
    else { princ_string(((char*)" /Tp"));
        princ_string(Optimize.compiler->source);
        princ_string(string_v(Core._starfs_star->value));
        (*Kernel.princ)(v12197);
        princ_string(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension);
        princ_string(((char*)" /Fo"));
        princ_string(Optimize.compiler->source);
        princ_string(string_v(Core._starfs_star->value));
        (*Kernel.princ)(v12197);
        princ_string(((char*)".obj"));
        }
      { char * v49778 = GC_STRING(end_of_string_void());
      princ_string(v49778);
      princ_string(((char*)"\n"));
      if (claire_shell(v49778) != 0)
       { princ_string(((char*)"Compilation error - abort\n"));
        CL_exit(1);
        }
      }
    if (INHERIT(OWNER(v12197),Kernel._module))
     { print_in_string_void();
      princ_string(((char*)"LIB /NOLOGO /DEF "));
      princ_string(Optimize.compiler->env);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(external_I_module1(OBJECT(module,v12197)));
      princ_string(((char*)".obj /OUT:"));
      princ_string(Optimize.compiler->env);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(external_I_module1(OBJECT(module,v12197)));
      princ_string(((char*)".lib"));
      { char * v49778 = GC_STRING(end_of_string_void());
        princ_string(v49778);
        princ_string(((char*)"\n"));
        if (claire_shell(v49778) != 0)
         princ_string(((char*)"Failed to generate import library\n"));
        }
      print_in_string_void();
      princ_string(((char*)"LINK /SUBSYSTEM:CONSOLE /NOLOGO /STACK:1600000 "));
      if (Optimize.compiler->debug_ask->length != 0)
       princ_string(((char*)"/DEBUG /MAP "));
      princ_string(((char*)"user32.lib gdi32.lib shell32.lib comdlg32.lib ws2_32.lib"));
      princ_string(((char*)" "));
      importlib_I_any1(v12197,v12196);
      princ_string(((char*)" "));
      princ_string(Optimize.compiler->env);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(external_I_module1(OBJECT(module,v12197)));
      princ_string(((char*)".obj /DLL /OUT:"));
      princ_string(Optimize.compiler->env);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(external_I_module1(OBJECT(module,v12197)));
      princ_string(((char*)".dll"));
      { char * v49778 = GC_STRING(end_of_string_void());
        princ_string(v49778);
        princ_string(((char*)"\n"));
        if (claire_shell(v49778) != 0)
         { princ_string(((char*)"DLL Link error\n"));
          CL_exit(1);
          }
        }
      }
    if (equal_string(v61574,((char*)"")) != CTRUE)
     { print_in_string_void();
      princ_string(((char*)"CL /nologo /DCLPC "));
      headers_I_void1();
      princ_string(string_v(Optimize.claire_options->value));
      princ_string(((char*)" /Tp"));
      princ_string(Optimize.compiler->source);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(v61574);
      princ_string(((char*)"-s"));
      princ_string(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension);
      princ_string(((char*)" /Fo"));
      princ_string(Optimize.compiler->source);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(v61574);
      princ_string(((char*)"-s.obj"));
      { char * v49778 = GC_STRING(end_of_string_void());
        princ_string(v49778);
        princ_string(((char*)"\n"));
        if (claire_shell(v49778) != 0)
         { princ_string(((char*)"Compilation error - abort\n"));
          CL_exit(1);
          }
        }
      print_in_string_void();
      princ_string(((char*)"LINK /SUBSYSTEM:CONSOLE /NOLOGO "));
      if (Optimize.compiler->debug_ask->length != 0)
       princ_string(((char*)"/DEBUG /MAP "));
      princ_string(((char*)"/STACK:1600000 user32.lib gdi32.lib shell32.lib comdlg32.lib ws2_32.lib"));
      princ_string(((char*)" /IMPLIB:"));
      princ_string(Optimize.compiler->env);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(((char*)"dummy.exe /OUT:"));
      princ_string(Optimize.compiler->env);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(v61574);
      princ_string(((char*)".exe "));
      princ_string(Optimize.compiler->source);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(v61574);
      princ_string(((char*)"-s.obj"));
      princ_string(((char*)" "));
      lib_I_any1(v12197,v12196);
      if (Kernel._string == OWNER(v12197))
       { princ_string(((char*)" "));
        princ_string(Optimize.compiler->source);
        princ_string(string_v(Core._starfs_star->value));
        (*Kernel.princ)(v12197);
        princ_string(((char*)".obj"));
        }
      { char * v49778 = GC_STRING(end_of_string_void());
        princ_string(v49778);
        princ_string(((char*)"\n"));
        if (claire_shell(v49778) != 0)
         { princ_string(((char*)"Link error - abort\n"));
          CL_exit(1);
          }
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  create_makefile_unix_any1(OID v12197,char *v61574,list *v12196) { 
    
    GC_BIND;
    print_in_string_void();
    princ_string(((char*)"g++  -Wno-write-strings "));
    headers_I_void1();
    princ_string(string_v(Optimize.claire_options->value));
    princ_string(string_v(Generate.cxx_options->value));
    if (INHERIT(OWNER(v12197),Kernel._module))
     { princ_string(((char*)" -o "));
      princ_string(Optimize.compiler->env);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(external_I_module1(OBJECT(module,v12197)));
      princ_string(((char*)".o"));
      princ_string(((char*)" -c "));
      princ_string(Optimize.compiler->source);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(external_I_module1(OBJECT(module,v12197)));
      princ_string(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension);
      }
    else { princ_string(((char*)" -o "));
        princ_string(Optimize.compiler->source);
        princ_string(string_v(Core._starfs_star->value));
        (*Kernel.princ)(v12197);
        princ_string(((char*)".o"));
        princ_string(((char*)" -c "));
        princ_string(Optimize.compiler->source);
        princ_string(string_v(Core._starfs_star->value));
        (*Kernel.princ)(v12197);
        princ_string(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension);
        }
      { char * v49778 = GC_STRING(end_of_string_void());
      princ_string(v49778);
      princ_string(((char*)"\n"));
      { CL_INT  v50681 = claire_shell(v49778);
        if (((equal_string(lower_string(sys_name_void()),((char*)"os/390")) == CTRUE) && 
              (((v50681 == 0) ? CTRUE : ((v50681 == 4) ? CTRUE : CFALSE)) != CTRUE)) || 
            ((equal_string(lower_string(sys_name_void()),((char*)"os/390")) != CTRUE) && 
                (((v50681 == 0) ? CTRUE : CFALSE) != CTRUE)))
         { princ_string(((char*)"Compilation error - abort\n"));
          CL_exit(1);
          }
        }
      }
    if (INHERIT(OWNER(v12197),Kernel._module))
     { print_in_string_void();
      princ_string(((char*)"g++ "));
      princ_string(string_v(Generate.so_options->value));
      princ_string(((char*)" -o "));
      princ_string(Optimize.compiler->env);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(external_I_module1(OBJECT(module,v12197)));
      princ_string(((char*)".so  "));
      princ_string(Optimize.compiler->env);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(external_I_module1(OBJECT(module,v12197)));
      princ_string(((char*)".o "));
      if (equal_string(lower_string(sys_name_void()),((char*)"os/390")) == CTRUE)
       importlib_I_any1(v12197,v12196);
      else ;{ char * v49778 = GC_STRING(end_of_string_void());
        princ_string(v49778);
        princ_string(((char*)"\n"));
        { CL_INT  v50681 = claire_shell(v49778);
          if (((equal_string(lower_string(sys_name_void()),((char*)"os/390")) == CTRUE) && 
                (((v50681 == 0) ? CTRUE : ((v50681 == 4) ? CTRUE : CFALSE)) != CTRUE)) || 
              ((equal_string(lower_string(sys_name_void()),((char*)"os/390")) != CTRUE) && 
                  (((v50681 == 0) ? CTRUE : CFALSE) != CTRUE)))
           { princ_string(((char*)"Failed to generate shared object\n"));
            CL_exit(1);
            }
          }
        }
      if (equal_string(lower_string(sys_name_void()),((char*)"os/390")) == CTRUE)
       claire_shell(append_string(((char*)"mv *.x "),GC_STRING(Optimize.compiler->env)));
      }
    if (equal_string(v61574,((char*)"")) != CTRUE)
     { print_in_string_void();
      princ_string(((char*)"g++  -Wno-write-strings "));
      headers_I_void1();
      princ_string(string_v(Optimize.claire_options->value));
      princ_string(string_v(Generate.cxx_options->value));
      princ_string(((char*)" -o "));
      princ_string(Optimize.compiler->source);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(v61574);
      princ_string(((char*)"-s.o"));
      princ_string(((char*)" -c "));
      princ_string(Optimize.compiler->source);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(v61574);
      princ_string(((char*)"-s"));
      princ_string(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension);
      { char * v49778 = GC_STRING(end_of_string_void());
        princ_string(v49778);
        princ_string(((char*)"\n"));
        { CL_INT  v50681 = claire_shell(v49778);
          if (((equal_string(lower_string(sys_name_void()),((char*)"os/390")) == CTRUE) && 
                (((v50681 == 0) ? CTRUE : ((v50681 == 4) ? CTRUE : CFALSE)) != CTRUE)) || 
              ((equal_string(lower_string(sys_name_void()),((char*)"os/390")) != CTRUE) && 
                  (((v50681 == 0) ? CTRUE : CFALSE) != CTRUE)))
           { princ_string(((char*)"Compilation error - abort\n"));
            CL_exit(1);
            }
          }
        }
      print_in_string_void();
      princ_string(((char*)"g++ "));
      princ_string(((char*)" "));
      princ_string(string_v(Generate.ld_options->value));
      princ_string(((char*)" -o "));
      princ_string(Optimize.compiler->env);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(v61574);
      princ_string(((char*)" "));
      princ_string(Optimize.compiler->source);
      princ_string(string_v(Core._starfs_star->value));
      princ_string(v61574);
      princ_string(((char*)"-s.o"));
      princ_string(((char*)" "));
      lib_I_any1(v12197,v12196);
      princ_string(((char*)" -lpthread -ldl  -ledit "));
      if (Kernel._string == OWNER(v12197))
       { princ_string(((char*)" "));
        princ_string(Optimize.compiler->source);
        princ_string(string_v(Core._starfs_star->value));
        (*Kernel.princ)(v12197);
        princ_string(((char*)".o"));
        }
      { char * v49778 = GC_STRING(end_of_string_void());
        princ_string(v49778);
        princ_string(((char*)"\n"));
        { CL_INT  v50681 = claire_shell(v49778);
          if (((equal_string(lower_string(sys_name_void()),((char*)"os/390")) == CTRUE) && 
                (((v50681 == 0) ? CTRUE : ((v50681 == 4) ? CTRUE : CFALSE)) != CTRUE)) || 
              ((equal_string(lower_string(sys_name_void()),((char*)"os/390")) != CTRUE) && 
                  (((v50681 == 0) ? CTRUE : CFALSE) != CTRUE)))
           { princ_string(((char*)"Link error - abort\n"));
            CL_exit(1);
            }
          }
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  ensure_module_directories_exist_void1() { 
    
    GC_BIND;
    if (isdir_ask_string(((char*)"include")) != CTRUE)
     { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
       mtformat_module1(Generate.it,((char*)"---- creating directory .~Ainclude \n"),0,list::alloc(1,GC_OID(Core._starfs_star->value)));
      else ;mkdir_string2(((char*)"include"));
      }
    if (isdir_ask_string(((char*)"include")) != CTRUE)
     { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
       mtformat_module1(Generate.it,((char*)"---- creating directory ~A \n"),0,list::alloc(1,_string_(((char*)"include"))));
      else ;mkdir_string2(((char*)"include"));
      }
    if (isdir_ask_string(((char*)"csrc")) != CTRUE)
     { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
       mtformat_module1(Generate.it,((char*)"---- creating directory ~A \n"),0,list::alloc(1,_string_(((char*)"csrc"))));
      else ;mkdir_string2(((char*)"csrc"));
      }
    if (isdir_ask_string(Optimize.compiler->env) != CTRUE)
     { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
       mtformat_module1(Generate.it,((char*)"---- creating directory ~A \n"),0,list::alloc(1,GC_OID(_string_(Optimize.compiler->env))));
      else ;mkdir_string2(Optimize.compiler->env);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  new_module_list1(list *v12196) { 
    
    GC_BIND;
    { list * v12200 = GC_OBJECT(list,explode_string(string_v((*(v12196))[1]),GC_STRING(string_v(Core._starfs_star->value))));
      if ((CL_INT)v12200->length > (CL_INT)2)
       close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"option -nm <[partof/[version/]]module> [m f.cl f.cpp ...]")),
        _oid_(Kernel.nil))));
      { ClaireHandler c_handle = ClaireHandler();
        if ERROR_IN 
        { { if (isdir_ask_string(string_v(last_list(v12200))) == CTRUE)
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"The Directory ~A already exists")),
              _oid_(list::alloc(1,last_list(v12200))))));
            if (isfile_ask_string(_7_string(string_v(last_list(v12200)),((char*)"init.cl"))) == CTRUE)
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~A already exists")),
              _oid_(list::alloc(1,GC_OID(_string_(_7_string(string_v(last_list(v12200)),((char*)"init.cl")))))))));
            if (should_trace_ask_module1(Generate.it,0) == CTRUE)
             mtformat_module1(Generate.it,((char*)"==== Creating new module ~A ==== \n"),0,list::alloc(1,last_list(v12200)));
            else ;mkdir_string2(string_v(last_list(v12200)));
            mkdir_string2(_7_string(string_v(last_list(v12200)),((char*)"include")));
            mkdir_string2(_7_string(string_v(last_list(v12200)),((char*)"source")));
            mkdir_string2(_7_string(string_v(last_list(v12200)),((char*)"csrc")));
            mkdir_string2(_7_string(string_v(last_list(v12200)),GC_STRING(Optimize.compiler->env)));
            { buffer * v19160 = GC_OBJECT(buffer,fopen_string1(GC_STRING(_7_string(string_v(last_list(v12200)),((char*)"init.cl"))),((char*)"w")));
              use_as_output_port(v19160);
              princ_string(((char*)"\n// init file for module "));
              princ_string(string_v(last_list(v12200)));
              princ_string(((char*)"\n// created "));
              princ_string(strftime_string(((char*)"%c"),now_void()));
              princ_string(((char*)" by claire v"));
              princ_string(release_void());
              princ_string(((char*)"\n\n"));
              if (v12200->length == 2)
               ((*(v12196))[1]=(*(v12200))[1]);
              else if (v12200->length == 3)
               ((*(v12196))[1]=GC_OID(_string_(_7_string(string_v((*(v12200))[1]),string_v((*(v12200))[2])))));
              else v12196= (skip_list(v12196,1));
                { list * v2378 = list::empty(Kernel._string);
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(v12194);
                  for (START(v12196); NEXT(v12194);)
                  if ((match_wildcard_ask_string(string_v(v12194),((char*)"*.*")) != CTRUE) || 
                      (match_wildcard_ask_string(string_v(v12194),((char*)"*/*")) == CTRUE))
                   { if (contain_ask_list(v2378,v12194) != CTRUE)
                     { v2378= (v2378->addFast((OID)v12194));
                      use_module_string(string_v(v12194));
                      use_as_output_port(v19160);
                      princ_string(((char*)"(use_module(\""));
                      princ_string(string_v(v12194));
                      princ_string(((char*)"\"))\n"));
                      }
                    }
                  }
                }
              princ_string(((char*)"\n\n"));
              princ_string(string_v(last_list(v12200)));
              princ_string(((char*)" :: module(\n"));
              if (v12200->length == 2)
               { princ_string(((char*)"\tpart_of = "));
                princ_string(string_v((*(v12200))[1]));
                princ_string(((char*)",\n"));
                }
              princ_string(((char*)"\tuses = list("));
              { ClaireBoolean * v5975 = CTRUE;
                if (v12200->length == 2)
                 { princ_string(string_v((*(v12200))[1]));
                  v5975= (CFALSE);
                  }
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(v12194);
                  for (START(v12196); NEXT(v12194);)
                  { GC_LOOP;
                    if ((match_wildcard_ask_string(string_v(v12194),((char*)"*.*")) != CTRUE) || 
                        (match_wildcard_ask_string(string_v(v12194),((char*)"*/*")) == CTRUE))
                     { if (v5975 == CTRUE)
                       v5975= (CFALSE);
                      else princ_string(((char*)", "));
                        princ_string(string_v((*(explode_string(string_v(v12194),GC_STRING(string_v(Core._starfs_star->value)))))[1]));
                      }
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                if (v5975 == CTRUE)
                 princ_string(((char*)"Core"));
                }
              princ_string(((char*)"),\n"));
              princ_string(((char*)"\tmade_of = list("));
              { ClaireBoolean * v5975 = CTRUE;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(v12194);
                  for (START(v12196); NEXT(v12194);)
                  { GC_LOOP;
                    if ((match_wildcard_ask_string(string_v(v12194),((char*)"*.*")) == CTRUE) && 
                        (match_wildcard_ask_string(string_v(v12194),((char*)"*/*")) != CTRUE))
                     { if (v5975 == CTRUE)
                       v5975= (CFALSE);
                      else princ_string(((char*)", "));
                        if (match_wildcard_ask_string(string_v(v12194),((char*)"*.h*")) == CTRUE)
                       fclose_port1(GC_OBJECT(buffer,fopen_string1(GC_STRING(_7_string(GC_STRING(_7_string(string_v(last_list(v12200)),((char*)"include"))),string_v(v12194))),((char*)"w"))));
                      else fclose_port1(GC_OBJECT(buffer,fopen_string1(GC_STRING(_7_string(GC_STRING(_7_string(string_v(last_list(v12200)),((char*)"source"))),string_v(v12194))),((char*)"w"))));
                        princ_string(((char*)"\""));
                      princ_string(string_v(v12194));
                      princ_string(((char*)"\""));
                      }
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                }
              princ_string(((char*)"),\n"));
              princ_string(((char*)"\tsource = \"source\",\n"));
              princ_string(((char*)"\tversion = \"v1.0.0\") // put your version here\n\n\n"));
              if (v12200->length == 2)
               { princ_string(((char*)"(begin("));
                princ_string(string_v((*(v12200))[1]));
                princ_string(((char*)"))\n"));
                }
              princ_string(((char*)"(load("));
              princ_string(string_v(last_list(v12200)));
              princ_string(((char*)"))\n"));
              if (v12200->length == 2)
               { princ_string(((char*)"(end("));
                princ_string(string_v((*(v12200))[1]));
                princ_string(((char*)"))\n"));
                }
              princ_string(((char*)"\n\n// Here you can customize the C++ compiler.\n// You can uncomment and set any of the following option :\n\n"));
              princ_string(((char*)"// ==== external libraries needed at link time ====\n"));
              princ_string(((char*)";(compiler.libraries :add \"-lsome_lib\")\n\n"));
              princ_string(((char*)"// ==== C++ compiler options ====\n"));
              princ_string(((char*)";(compiler.options[1] :/+ \"-a_cpp_option\") // Optimize mode (-O)\n"));
              princ_string(((char*)";(compiler.options[2] :/+ \"-a_cpp_option\") // Debug mode (-D)\n"));
              princ_string(((char*)";(compiler.options[3] :/+ \"-a_cpp_option\") // Release mode\n\n"));
              princ_string(((char*)"\n// Here you can customize the CLAIRE compiler.\n// You can uncomment and set any of the following option :\n\n"));
              princ_string(((char*)"// ==== compiler safety ====\n// 0 -> super safe\n// 1 -> safe\n// 2 -> trust explicit types & super\n// 3 -> no overflow checking\n// 4 -> assumes no selector or range error\n// 5 -> assume no type errors of any kind\n"));
              princ_string(((char*)";(compiler.safety := 1)\n\n"));
              princ_string(((char*)"// ==== compiler naming convention ====\n// 0 -> long & explicit names\n// 1 -> shorter names\n// 2 -> protected names\n"));
              princ_string(((char*)";(compiler.naming := 0)\n\n"));
              princ_string(((char*)"// ==== compiler inline flag ====\n// set it to true if you want to include inline definitions in the generated library\n"));
              princ_string(((char*)";(compiler.inline? := false)\n\n"));
              princ_string(((char*)"// ==== compiler overflow flag ====\n// set it to true to produce safe code with respect to owerflow\n"));
              princ_string(((char*)";(compiler.overflow? := false)\n\n"));
              princ_string(((char*)"// ==== fast dispatch flag ====\n"));
              princ_string(((char*)";(FCALLSTINKS := false)\n\n"));
              princ_string(((char*)"\n// Here you can customize the CLAIRE code generator.\n"));
              princ_string(((char*)"// Some symbol may be reserved in the target language,\n"));
              princ_string(((char*)"// for such symbol you have to define a translation :\n\n"));
              princ_string(((char*)";(Generate/C++PRODUCER.Generate/bad_names :add some_symbol)\n"));
              princ_string(((char*)";(Generate/C++PRODUCER.Generate/good_names :add symbol!(\"some_symbol_translated\"))\n\n"));
              fclose_port1(v19160);
              }
            }
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
        { c_handle.catchIt();{ use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value));
            print_any(GC_OID(_oid_(ClEnv->exception_I)));
            princ_string(((char*)"\n"));
            CL_exit(1);
            }
          }
        else PREVIOUS_HANDLER;}
      CL_exit(0);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  rcopy_string1(char *v50324,char *v50760) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { list * v12197 = GC_OBJECT(list,explode_string(v50760,GC_STRING(string_v(Core._starfs_star->value))));
      char * v591 = GC_STRING(((equal_string(Optimize.compiler->env,((char*)"ntv")) == CTRUE) ?
        left_string(v50760,2) :
        ((((CL_INT)LENGTH_STRING(v50760) > (CL_INT)0) && 
            (v50760[1 - 1] == ((unsigned char)'/'))) ?
          ((char*)"/") :
          ((char*)".") ) ));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v12193);
        for (START(v12197); NEXT(v12193);)
        { GC_LOOP;
          if (((CL_INT)LENGTH_STRING(string_v(v12193)) > (CL_INT)0) && 
              (((equal_string(Optimize.compiler->env,((char*)"ntv")) == CTRUE) ? ((equal(v12193,_string_(left_string(v50760,2))) == CTRUE) ? CTRUE: CFALSE): CFALSE) != CTRUE))
           { GC__STRING(v591 = _7_string(v591,string_v(v12193)), 1);
            if (isdir_ask_string(v591) != CTRUE)
             mkdir_string2(v591);
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      }
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(v12193);
      bag *v12193_support;
      v12193_support = GC_OBJECT(list,entries_string2(v50324));
      for (START(v12193_support); NEXT(v12193);)
      { GC_LOOP;
        if (isfile_ask_string(_7_string(v50324,string_v(v12193))) == CTRUE)
         { fcopy_string(GC_STRING(_7_string(v50324,string_v(v12193))),GC_STRING(_7_string(v50760,string_v(v12193))));
          chmod_string(_7_string(v50760,string_v(v12193)),33188);
          }
        else if (((equal_string(v50324,((char*)".svn")) == CTRUE) ? CTRUE : ((equal_string(v50324,((char*)"CVS")) == CTRUE) ? CTRUE : CFALSE)) != CTRUE)
         rcopy_string1(GC_STRING(_7_string(v50324,string_v(v12193))),GC_STRING(_7_string(v50760,string_v(v12193))));
        GC_UNLOOP; POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  export_module_boolean1(ClaireBoolean *v40842) { 
    
    GC_BIND;
    { ClaireHandler c_handle = ClaireHandler();
      if ERROR_IN 
      { { if (isfile_ask_string(((char*)"init.cl")) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"The current directory doesn't not contain an init.cl file")),
            _oid_(Kernel.nil))));
          { char * v50542 = GC_STRING(string_v(last_list(explode_string(GC_STRING(pwd_void()),GC_STRING(string_v(Core._starfs_star->value))))));
            char * v52057 = ((equal_string(Optimize.compiler->env,((char*)"ntv")) == CTRUE) ?
              ((char*)".obj") :
              ((char*)".o") );
            if (isfile_ask_string(append_string(GC_STRING(_7_string(GC_STRING(Optimize.compiler->env),v50542)),v52057)) != CTRUE)
             { general_error * v34921;
              { OID  v35882;
                { list * v22054;{ OID v_bag;
                    GC_ANY(v22054= list::empty(Kernel.emptySet));
                    if (v40842 == CTRUE)
                     v_bag = _string_(((char*)"export"));
                    else v_bag = _string_(((char*)"publish"));
                      ((list *) v22054)->addFast((OID)v_bag);
                    ((list *) v22054)->addFast((OID)_string_(v50542));
                    ((list *) v22054)->addFast((OID)_string_(v50542));}
                  
                  v35882=_oid_(v22054);}
                v34921 = ((general_error *) (*Core._general_error)(_string_(((char*)"Attempt to ~A the module ~A that does not have any lib yet, compile the module ~A first")),
                  v35882));
                }
              close_exception(v34921);
              }
            }
          { char * v54666 = GC_STRING(realpath_string(GC_STRING(_7_string(GC_STRING(_7_string(GC_STRING(home_path_void1()),((char*)".."))),((char*)"..")))));
            if ((v40842 != CTRUE) && 
                ((OBJECT(ClaireBoolean,Generate._Zsudo->value)) == CTRUE))
             { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
               mtformat_module1(Generate.it,((char*)"---- note: attempt to publish ~A at ~A \n"),0,list::alloc(2,GC_OID(last_list(explode_string(GC_STRING(pwd_void()),GC_STRING(string_v(Core._starfs_star->value))))),_string_(v54666)));
              else ;if (should_trace_ask_module1(Generate.it,0) == CTRUE)
               mtformat_module1(Generate.it,((char*)"==== Require permission for publication ====\n"),0,list::empty());
              else ;print_in_string_void();
              princ_string(((char*)"sudo "));
              (*Kernel.princ)((*(ClEnv->params))[1]);
              princ_string(((char*)" "));
              if ((OBJECT(ClaireBoolean,Generate._Zov->value)) == CTRUE)
               princ_string(((char*)" -ov"));
              princ_string(((char*)" -publish\n"));
              if (claire_shell(end_of_string_void()) != 0)
               CL_exit(1);
              CL_exit(0);
              }
            load_string(((char*)"init"));
            { char * v12197 = GC_STRING(string_v(last_list(explode_string(GC_STRING(pwd_void()),GC_STRING(string_v(Core._starfs_star->value))))));
              OID  v18938 = value_string(v12197);
              char * v50319;
              { { char * v37804;
                  { OID  v12206 = GC_OID(get_property(Kernel.version,OBJECT(ClaireObject,v18938)));
                    if (v12206 != CNULL)
                     v37804 = string_v(v12206);
                    else { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
                         mtformat_module1(Generate.it,((char*)"---- note: ~S.version undefined, default is [v0.0.0] \n"),0,list::alloc(1,v18938));
                        else ;v37804 = ((char*)"v0.0.0");
                        }
                      }
                  v50319 = _7_string(v12197,v37804);
                  }
                GC_STRING(v50319);}
              list * v37974 = GC_OBJECT(list,explode_string(GC_STRING(getenv_string(((char*)"CLAIRE_LIBS"))),GC_STRING(string_v(Core._starps_star->value))));
              OID  v12200;
              { if (v40842 != CTRUE)
                 v12200 = _string_(_7_string(v54666,((char*)"lib")));
                else if (INHERIT(OWNER(Generate._Zexport->value),Kernel._integer))
                 { if (((OBJECT(ClaireBoolean,(*Kernel._inf)(GC_OID(Generate._Zexport->value),
                      ((OID)1)))) == CTRUE) || 
                      ((OBJECT(ClaireBoolean,(*Kernel._sup)(GC_OID(Generate._Zexport->value),
                        ((OID)v37974->length)))) == CTRUE))
                   close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"-export ~A, ~A is a invalid index for CLAIRE_LIBS [~A]")),
                    _oid_(list::alloc(3,GC_OID(Generate._Zexport->value),
                      GC_OID(Generate._Zexport->value),
                      _oid_(v37974))))));
                  v12200 = (*(v37974))[((CL_INT)Generate._Zexport->value)];
                  }
                else if (Kernel._string == OWNER(Generate._Zexport->value))
                 { if (contain_ask_list(v37974,Generate._Zexport->value) != CTRUE)
                   { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
                     mtformat_module1(Generate.it,((char*)"---- warning: ~A not found in CLAIRE_LIBS environment variable \n"),0,list::alloc(1,GC_OID(Generate._Zexport->value)));
                    else ;}
                  v12200 = Generate._Zexport->value;
                  }
                else { if (boolean_I_any(_oid_(v37974)) != CTRUE)
                     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"export path ommited, can't guess it since environment variable CLAIRE_LIBS is undefined")),
                      _oid_(Kernel.nil))));
                    v12200 = (*(v37974))[1];
                    }
                  GC_OID(v12200);}
              char * v55749 = GC_STRING(_7_string(GC_STRING(_7_string(string_v(v12200),v50319)),GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"v"),GC_STRING(release_void()))),((char*)"-"))),GC_STRING(Optimize.compiler->env)))));
              if (should_trace_ask_module1(Generate.it,0) == CTRUE)
               { list * v38765;
                { OID v_bag;
                  GC_ANY(v38765= list::empty(Kernel.emptySet));
                  if (v40842 == CTRUE)
                   v_bag = _string_(((char*)"Export"));
                  else v_bag = _string_(((char*)"Publish"));
                    ((list *) v38765)->addFast((OID)v_bag);
                  ((list *) v38765)->addFast((OID)_string_(v50319));}
                mtformat_module1(Generate.it,((char*)"==== ~A ~A ==== \n"),0,v38765);
                }
              else ;if ((Generate._Zov->value != Kernel.ctrue) && 
                  (isdir_ask_string(_7_string(string_v(v12200),v50319)) == CTRUE))
               close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Sorry, directory ~S already exists (try with -ov to overwrite)")),
                _oid_(list::alloc(1,GC_OID(_string_(_7_string(string_v(v12200),v50319))))))));
              if (isdir_ask_string(_7_string(string_v(v12200),v50319)) != CTRUE)
               { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
                 mtformat_module1(Generate.it,((char*)"     creating ~A \n"),0,list::alloc(1,GC_OID(_string_(_7_string(string_v(v12200),v50319)))));
                else ;}
              if (isdir_ask_string(_7_string(string_v(v12200),v12197)) != CTRUE)
               mkdir_string2(_7_string(string_v(v12200),v12197));
              if (isdir_ask_string(_7_string(string_v(v12200),v50319)) != CTRUE)
               mkdir_string2(_7_string(string_v(v12200),v50319));
              if (should_trace_ask_module1(Generate.it,3) == CTRUE)
               mtformat_module1(Generate.it,((char*)"     copying files in ~A \n"),3,list::alloc(1,GC_OID(_string_(_7_string(string_v(v12200),v50319)))));
              else ;if (should_trace_ask_module1(Generate.it,3) == CTRUE)
               mtformat_module1(Generate.it,((char*)"     init.cl, include, source and lib\n"),3,list::empty());
              else ;fcopy_string(((char*)"init.cl"),_7_string(GC_STRING(_7_string(string_v(v12200),v50319)),((char*)"init.cl")));
              chmod_string(_7_string(GC_STRING(_7_string(string_v(v12200),v50319)),((char*)"init.cl")),33188);
              rcopy_string1(GC_STRING(Optimize.compiler->env),v55749);
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(v12193);
                bag *v12193_support;
                v12193_support = GC_OBJECT(list,entries_string1(((char*)"include"),((char*)"*.h*")));
                for (START(v12193_support); NEXT(v12193);)
                { GC_LOOP;
                  { fcopy_string(GC_STRING(_7_string(((char*)"include"),string_v(v12193))),GC_STRING(_7_string(v55749,string_v(v12193))));
                    chmod_string(_7_string(v55749,string_v(v12193)),33188);
                    }
                  GC_UNLOOP; POP_SIGNAL;}
                }
              rcopy_string1(((char*)"include"),v55749);
              rcopy_string1(GC_STRING(string_v((*Kernel.source)(v18938))),GC_STRING(_7_string(GC_STRING(_7_string(string_v(v12200),v50319)),GC_STRING(string_v((*Kernel.source)(v18938))))));
              if (isdir_ask_string(((char*)"doc")) == CTRUE)
               rcopy_string1(((char*)"doc"),GC_STRING(_7_string(GC_STRING(_7_string(string_v(v12200),v50319)),((char*)"doc"))));
              if (should_trace_ask_module1(Generate.it,3) == CTRUE)
               mtformat_module1(Generate.it,((char*)"== Call exported callback\n"),3,GC_OBJECT(list,list::empty()));
              else ;{ ClaireHandler c_handle = ClaireHandler();
                if ERROR_IN 
                { (*Core.apply)(value_module(OBJECT(module,v18938),((char*)"exported")),
                    GC_OID(_oid_(list::alloc(4,_oid_(v40842),
                      Generate._Zov->value,
                      GC_OID(_string_(_7_string(string_v(v12200),v50319))),
                      GC_OID(_string_(home_path_void1()))))));
                  ERROR_FREE;}
                else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                { c_handle.catchIt();;}
                else PREVIOUS_HANDLER;}
              if (should_trace_ask_module1(Generate.it,0) == CTRUE)
               mtformat_module1(Generate.it,((char*)"Time : ~A \n"),0,GC_OBJECT(list,list::alloc(1,GC_OID(_string_(strftime_string(((char*)"%c"),now_void()))))));
              else ;if (should_trace_ask_module1(Generate.it,0) == CTRUE)
               { list * v39726;
                { { OID v_bag;
                    GC_ANY(v39726= list::empty(Kernel.emptySet));
                    ((list *) v39726)->addFast((OID)_string_(v50319));
                    if (v40842 == CTRUE)
                     v_bag = _string_(((char*)"exported"));
                    else v_bag = _string_(((char*)"published"));
                      ((list *) v39726)->addFast((OID)v_bag);}
                  GC_OBJECT(list,v39726);}
                mtformat_module1(Generate.it,((char*)"==== ~A ~A ==== \n"),0,v39726);
                }
              else ;}
            }
          }
        ERROR_FREE;}
      else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
      { c_handle.catchIt();{ print_any(GC_OID(_oid_(ClEnv->exception_I)));
          princ_string(((char*)"\n"));
          CL_exit(1);
          }
        }
      else PREVIOUS_HANDLER;}
    CL_exit(0);
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT char * relayed_params_void1() { 
    
    GC_RESERVE(6);  // v3.3.39 optim !
    { char *Result ;
      { char * v63960 = ((char*)" -qonerror");
        CL_INT  v58189 = length_bag(ClEnv->params);
        { CL_INT  v12193 = 1;
          CL_INT  v23568 = v58189;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)v12193 <= (CL_INT)v23568))
            { GC_LOOP;
              if ((equal((*(ClEnv->params))[v12193],_string_(((char*)"-s"))) == CTRUE) && 
                  ((CL_INT)((CL_INT)v12193+(CL_INT)2) <= (CL_INT)v58189))
               GC__STRING(v63960 = append_string(v63960,GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)" -s "),string_v((*(ClEnv->params))[((CL_INT)v12193+(CL_INT)1)]))),((char*)" "))),string_v((*(ClEnv->params))[((CL_INT)v12193+(CL_INT)2)])))), 1);
              else if ((equal((*(ClEnv->params))[v12193],_string_(((char*)"-cpp"))) == CTRUE) && 
                  ((CL_INT)((CL_INT)v12193+(CL_INT)1) <= (CL_INT)v58189))
               GC__STRING(v63960 = append_string(v63960,GC_STRING(append_string(GC_STRING(append_string(((char*)" -cpp '"),string_v((*(ClEnv->params))[((CL_INT)v12193+(CL_INT)1)]))),((char*)"'")))), 2);
              else if ((equal((*(ClEnv->params))[v12193],_string_(((char*)"-make"))) == CTRUE) && 
                  ((CL_INT)((CL_INT)v12193+(CL_INT)1) <= (CL_INT)v58189))
               GC__STRING(v63960 = append_string(v63960,GC_STRING(append_string(GC_STRING(append_string(((char*)" -make '"),string_v((*(ClEnv->params))[((CL_INT)v12193+(CL_INT)1)]))),((char*)"'")))), 3);
              else if ((equal((*(ClEnv->params))[v12193],_string_(((char*)"-link"))) == CTRUE) && 
                  ((CL_INT)((CL_INT)v12193+(CL_INT)1) <= (CL_INT)v58189))
               GC__STRING(v63960 = append_string(v63960,GC_STRING(append_string(GC_STRING(append_string(((char*)" -link '"),string_v((*(ClEnv->params))[((CL_INT)v12193+(CL_INT)1)]))),((char*)"'")))), 4);
              else if ((equal((*(ClEnv->params))[v12193],_string_(((char*)"-os"))) == CTRUE) && 
                  ((CL_INT)((CL_INT)v12193+(CL_INT)1) <= (CL_INT)v58189))
               GC__STRING(v63960 = append_string(v63960,GC_STRING(append_string(((char*)" -os "),string_v((*(ClEnv->params))[((CL_INT)v12193+(CL_INT)1)])))), 5);
              else if ((equal((*(ClEnv->params))[v12193],_string_(((char*)"-color"))) == CTRUE) || 
                  ((equal((*(ClEnv->params))[v12193],_string_(((char*)"-noel"))) == CTRUE) || 
                    ((equal((*(ClEnv->params))[v12193],_string_(((char*)"-zerobuffer"))) == CTRUE) || 
                      ((equal((*(ClEnv->params))[v12193],_string_(((char*)"-safe"))) == CTRUE) || 
                        ((equal((*(ClEnv->params))[v12193],_string_(((char*)"-p"))) == CTRUE) || 
                          ((equal((*(ClEnv->params))[v12193],_string_(((char*)"-auto"))) == CTRUE) || 
                            (equal((*(ClEnv->params))[v12193],_string_(((char*)"-relink"))) == CTRUE)))))))
               GC__STRING(v63960 = append_string(v63960,GC_STRING(append_string(((char*)" "),string_v((*(ClEnv->params))[v12193])))), 6);
              ++v12193;
              GC_UNLOOP;POP_SIGNAL;}
            }
          }
        if (ClEnv->verbose != 0)
         v63960= (GC_STRING(append_string(v63960,GC_STRING(append_string(((char*)" -v "),GC_STRING(string_I_integer (ClEnv->verbose)))))));
        Result = append_string(((char*)" "),v63960);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  

CL_EXPORT void  compile_module_libs_void1() { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { OID  v12197 = GC_OID(last_list(explode_string(GC_STRING(pwd_void()),GC_STRING(string_v(Core._starfs_star->value)))));
      ClaireBoolean * v62112 = CFALSE;
      ClaireBoolean * v62453 = CFALSE;
      char * v3560 = ((char*)"");
      { CL_INT  v12193 = 1;
        CL_INT  v23569 = length_bag(ClEnv->params);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)v12193 <= (CL_INT)v23569))
          { GC_LOOP;
            { OID  v12200 = (*(ClEnv->params))[v12193];
              if (equal(v12200,_string_(((char*)"-D"))) == CTRUE)
               v62112= (CTRUE);
              else if (equal(v12200,_string_(((char*)"-O"))) == CTRUE)
               v62453= (CTRUE);
              else if (equal(v12200,_string_(((char*)"-chdir"))) == CTRUE)
               ++v12193;
              else if ((equal(v12200,_string_(((char*)"-export"))) == CTRUE) || 
                  ((equal(v12200,_string_(((char*)"-publish"))) == CTRUE) || 
                    ((equal(v12200,_string_(((char*)"-ov"))) == CTRUE) || 
                      ((equal(v12200,_string_(((char*)"-both"))) == CTRUE) || 
                        ((equal(v12200,_string_(((char*)"-cls"))) == CTRUE) || 
                          (equal(v12200,_string_(((char*)"-call"))) == CTRUE))))))
               ;else GC__STRING(v3560 = append_string(v3560,GC_STRING(append_string(((char*)" "),string_v(v12200)))), 1);
                }
            ++v12193;
            GC_UNLOOP;POP_SIGNAL;}
          }
        }
      if (((OBJECT(ClaireBoolean,Generate._Zboth->value)) == CTRUE) || 
          (v62112 == CTRUE))
       { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
         mtformat_module1(Generate.it,((char*)"==== Compile ~A's debug library ==== \n"),0,GC_OBJECT(list,list::alloc(1,v12197)));
        else ;if (claire_shell(append_string(v3560,((char*)" -D -cl"))) != 0)
         CL_exit(1);
        }
      if (((OBJECT(ClaireBoolean,Generate._Zboth->value)) == CTRUE) || 
          ((v62112 != CTRUE) || 
            (v62453 == CTRUE)))
       { if (Optimize.compiler->optimize_ask == CTRUE)
         { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
           mtformat_module1(Generate.it,((char*)"\n\n==== Compile ~A's release library (optimized) ==== \n"),0,GC_OBJECT(list,list::alloc(1,v12197)));
          else ;if (claire_shell(append_string(v3560,((char*)" -O -cl"))) != 0)
           CL_exit(1);
          }
        else { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
             mtformat_module1(Generate.it,((char*)"\n\n==== Compile ~A's release library ==== \n"),0,GC_OBJECT(list,list::alloc(1,v12197)));
            else ;if (claire_shell(append_string(v3560,((char*)" -cl"))) != 0)
             CL_exit(1);
            }
          }
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  compile_all_module_libs_void1() { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    if (LENGTH_STRING(getenv_string(((char*)"CLAIRE_LIBS"))) == 0)
     setenv_string(((char*)"CLAIRE_LIBS=.."));
    else setenv_string(append_string(GC_STRING(append_string(((char*)"CLAIRE_LIBS=.."),GC_STRING(string_v(Core._starps_star->value)))),GC_STRING(getenv_string(((char*)"CLAIRE_LIBS")))));
      { list * v59378;
      { { bag * v4739 = entries_string2(((char*)"."));
          list * v21936 = ((list *) empty_bag(v4739));
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(v12193);
            for (START(v4739); NEXT(v12193);)
            if ((isdir_ask_string(string_v(v12193)) == CTRUE) && 
                (isfile_ask_string(_7_string(string_v(v12193),((char*)"init.cl"))) == CTRUE))
             v21936->addFast((OID)v12193);
            }
          v59378 = GC_OBJECT(list,v21936);
          }
        GC_OBJECT(list,v59378);}
      list * v8057 = list::empty(Kernel._module);
      char * v3560 = ((char*)"");
      if (boolean_I_any(_oid_(v59378)) != CTRUE)
       { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
         mtformat_module1(Generate.it,((char*)"---- warning: there is no module folder in ~A \n"),0,list::alloc(1,GC_OID(_string_(pwd_void()))));
        else ;CL_exit(1);
        }
      if (should_trace_ask_module1(Generate.it,0) == CTRUE)
       mtformat_module1(Generate.it,((char*)"==== Compile all modules from ~A ==== \n"),0,list::alloc(1,GC_OID(_string_(pwd_void()))));
      else ;{ CL_INT  v12193 = 1;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)v12193 <= (CL_INT)length_bag(ClEnv->params)))
          { GC_LOOP;
            { OID  v12200 = (*(ClEnv->params))[v12193];
              if (equal(v12200,_string_(((char*)"-call"))) == CTRUE)
               ;else if (equal(v12200,_string_(((char*)"-chdir"))) == CTRUE)
               ++v12193;
              else GC__STRING(v3560 = append_string(v3560,GC_STRING(append_string(((char*)" "),string_v(v12200)))), 1);
                ++v12193;
              }
            GC_UNLOOP;POP_SIGNAL;}
          }
        }
      set_load_module_boolean(CFALSE);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v12193);
        for (START(v59378); NEXT(v12193);)
        { GC_LOOP;
          { OID  v12197 = value_string(string_v(v12193));
            if ((v12197 == CNULL) || 
                (inherit_ask_class(OWNER(v12197),Kernel._module) != CTRUE))
             { if (should_trace_ask_module1(Generate.it,3) == CTRUE)
               mtformat_module1(Generate.it,((char*)"==== note: load module ~A ==== \n"),3,GC_OBJECT(list,list::alloc(1,v12193)));
              else ;read_string(((char*)"begin(claire)"));
              setcwd_string(string_v(v12193));
              load_string(((char*)"init.cl"));
              setcwd_string(((char*)".."));
              { OID  v50536 = value_string(string_v(v12193));
                if (v50536 != CNULL)
                 { v8057= (v8057->addFast((OID)v50536));
                  GC__ANY(v8057 = add_modules_list(v8057), 2);
                  }
                else ;}
              }
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      if ((CL_INT)LENGTH_STRING(string_v(Generate._Zem->value)) > (CL_INT)0)
       { OID  v50536 = value_string(string_v(Generate._Zem->value));
        if (INHERIT(OWNER(v50536),Kernel._module))
         { list * v40265 = GC_OBJECT(list,list::alloc(Kernel._module,1,v50536));
          v8057= (GC_OBJECT(list,add_modules_list(v40265)));
          }
        else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Unknown module specified in option -call -em ~A")),
            _oid_(list::alloc(1,GC_OID(Generate._Zem->value))))));
          }
      if ((CL_INT)LENGTH_STRING(string_v(Generate._Zsm->value)) > (CL_INT)0)
       { OID  v50536 = value_string(string_v(Generate._Zsm->value));
        if (INHERIT(OWNER(v50536),Kernel._module))
         { list * v9815 = ((list *) copy_bag(v8057));
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v12197);
            for (START(v8057); NEXT(v12197);)
            { GC_LOOP;
              { list * v50503 = GC_OBJECT(list,add_modules_list(GC_OBJECT(list,list::alloc(Kernel._module,1,v12197))));
                if (contain_ask_list(v50503,v50536) != CTRUE)
                 { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(v63050);
                  for (START(v50503); NEXT(v63050);)
                  v9815= (((list *) delete_bag(v9815,v63050)));
                  }
                }
              GC_UNLOOP; POP_SIGNAL;}
            }
          v8057= (v9815);
          }
        else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Unknown module specified in option -call -sm ~A")),
            _oid_(list::alloc(1,GC_OID(Generate._Zsm->value))))));
          }
      if (should_trace_ask_module1(Generate.it,0) == CTRUE)
       { list * v62790;
        { { OID v_bag;
            GC_ANY(v62790= list::empty(Kernel.emptySet));
            { list * v22082;{ bag * v58367 = v8057;
                list * v46004 = ((list *) empty_bag(v58367));
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(v12197);
                  for (START(v58367); NEXT(v12197);)
                  if (isdir_ask_string(external_I_module1(OBJECT(module,v12197))) == CTRUE)
                   v46004->addFast((OID)v12197);
                  }
                v22082 = GC_OBJECT(list,v46004);
                }
              
              v_bag=_oid_(v22082);}
            ((list *) v62790)->addFast((OID)v_bag);}
          GC_OBJECT(list,v62790);}
        mtformat_module1(Generate.it,((char*)"==== Recompile ~A ==== \n"),0,v62790);
        }
      else ;{ CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v50536);
        for (START(v8057); NEXT(v50536);)
        { GC_LOOP;
          if (contain_ask_list(v59378,_string_(external_I_module1(OBJECT(module,v50536)))) == CTRUE)
           { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
             mtformat_module1(Generate.it,((char*)"\n\n\n\n =============================================\n"),0,GC_OBJECT(list,list::empty()));
            else ;if (should_trace_ask_module1(Generate.it,0) == CTRUE)
             mtformat_module1(Generate.it,((char*)"== Module ~S \n"),0,GC_OBJECT(list,list::alloc(1,v50536)));
            else ;if (should_trace_ask_module1(Generate.it,0) == CTRUE)
             mtformat_module1(Generate.it,((char*)"=============================================\n"),0,GC_OBJECT(list,list::empty()));
            else ;if (should_trace_ask_module1(Generate.it,3) == CTRUE)
             mtformat_module1(Generate.it,((char*)"---- note: enter directory ~A \n"),3,GC_OBJECT(list,list::alloc(1,_string_(external_I_module1(OBJECT(module,v50536))))));
            else ;setcwd_string(external_I_module1(OBJECT(module,v50536)));
            if (claire_shell(append_string(v3560,((char*)" -qonerror -cls"))) != 0)
             CL_exit(1);
            if (should_trace_ask_module1(Generate.it,3) == CTRUE)
             mtformat_module1(Generate.it,((char*)"---- note: leave directory ~A \n"),3,GC_OBJECT(list,list::alloc(1,_string_(external_I_module1(OBJECT(module,v50536))))));
            else ;setcwd_string(((char*)".."));
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      if (should_trace_ask_module1(Generate.it,0) == CTRUE)
       { list * v64712;
        { { OID v_bag;
            GC_ANY(v64712= list::empty(Kernel.emptySet));
            { list * v22084;{ bag * v58367 = v8057;
                list * v46004 = ((list *) empty_bag(v58367));
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(v12197);
                  for (START(v58367); NEXT(v12197);)
                  if (isdir_ask_string(external_I_module1(OBJECT(module,v12197))) == CTRUE)
                   v46004->addFast((OID)v12197);
                  }
                v22084 = GC_OBJECT(list,v46004);
                }
              
              v_bag=_oid_(v22084);}
            ((list *) v64712)->addFast((OID)v_bag);}
          GC_OBJECT(list,v64712);}
        mtformat_module1(Generate.it,((char*)"==== ~A recompiled ==== \n"),0,v64712);
        }
      else ;CL_exit(0);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  module_list_list1(list *v12196) { 
    
    GC_BIND;
    { char * v12190 = GC_STRING(realpath_string(GC_STRING(getenv_string(((char*)"_")))));
      char * v54666 = GC_STRING(_7_string(GC_STRING(realpath_string(GC_STRING(_7_string(GC_STRING(_7_string(GC_STRING(_7_string(GC_STRING(substring_string(v12190,1,((CL_INT)rfind_string2(v12190,string_v(Core._starfs_star->value))-(CL_INT)1))),((char*)".."))),((char*)".."))),((char*)".."))))),((char*)"lib")));
      list * v50539;
      { { bag * v16647 = entries_string2(v54666);
          list * v63404 = ((list *) empty_bag(v16647));
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(v12189);
            for (START(v16647); NEXT(v12189);)
            if (isdir_ask_string(_7_string(v54666,string_v(v12189))) == CTRUE)
             v63404->addFast((OID)v12189);
            }
          v50539 = GC_OBJECT(list,v63404);
          }
        GC_OBJECT(list,v50539);}
      list * v37974 = GC_OBJECT(list,explode_string(GC_STRING(getenv_string(((char*)"CLAIRE_LIBS"))),GC_STRING(string_v(Core._starps_star->value))));
      list * v50535;
      { { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          bag *v_list; OID v_val;
          OID v12193; CL_INT CLcount;
          v_list = v37974;
           v50535 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { GC_LOOP;
            v12193 = (*(v_list))[CLcount];
            { tuple * v22085;{ OID v_bag;
                GC_ANY(v22085= tuple::empty());
                ((tuple *) v22085)->addFast((OID)v12193);
                { list * v22086;{ bag * v58367 = entries_string2(string_v(v12193));
                    list * v46004 = ((list *) empty_bag(v58367));
                    { CL_INT loop_handle = ClEnv->cHandle;
                      ITERATE(v12197);
                      for (START(v58367); NEXT(v12197);)
                      if (isdir_ask_string(_7_string(string_v(v12193),string_v(v12197))) == CTRUE)
                       v46004->addFast((OID)v12197);
                      }
                    v22086 = GC_OBJECT(list,v46004);
                    }
                  
                  v_bag=_oid_(v22086);}
                ((tuple *) v22085)->addFast((OID)v_bag);}
              
              v_val=_oid_(v22085);}
            
            (*((list *) v50535))[CLcount] = v_val;GC_UNLOOP; POP_SIGNAL;}
          }
        GC_OBJECT(list,v50535);}
      char * v65400;
      { { char * v3020;
          { { v12196= (skip_list(v12196,1));
              v3020 = ((v12196->length != 0) ?
                string_v((*(v12196))[1]) :
                Optimize.compiler->env );
              }
            GC_STRING(v3020);}
          v65400 = append_string(GC_STRING(append_string(GC_STRING(((v12196->length != 0) ?
            string_v((*(v12196))[1]) :
            append_string(((char*)"v"),GC_STRING(release_void())) )),((char*)"-"))),v3020);
          }
        GC_STRING(v65400);}
      if (should_trace_ask_module1(Generate.it,0) == CTRUE)
       mtformat_module1(Generate.it,((char*)"==== Query available modules for ~A ==== \n"),0,list::alloc(1,_string_(v65400)));
      else ;if (v50539->length != 0)
       { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
         mtformat_module1(Generate.it,((char*)"==== Published modules [~A] ==== \n"),0,list::alloc(1,_string_(v54666)));
        else ;{ CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v12197);
          for (START(v50539); NEXT(v12197);)
          { GC_LOOP;
            { princ_string(((char*)"   "));
              princ_string(string_v(v12197));
              princ_string(((char*)": "));
              { ClaireBoolean * v5975 = CTRUE;
                list * v50559;
                { { bag * v64342 = entries_string2(GC_STRING(_7_string(v54666,string_v(v12197))));
                    list * v34621 = ((list *) empty_bag(v64342));
                    { CL_INT loop_handle = ClEnv->cHandle;
                      OID gc_local;
                      ITERATE(v12206);
                      for (START(v64342); NEXT(v12206);)
                      { GC_LOOP;
                        if ((isdir_ask_string(_7_string(GC_STRING(_7_string(v54666,string_v(v12197))),string_v(v12206))) == CTRUE) && 
                            ((isfile_ask_string(_7_string(GC_STRING(_7_string(GC_STRING(_7_string(v54666,string_v(v12197))),string_v(v12206))),((char*)"init.cl"))) == CTRUE) && 
                              (isdir_ask_string(_7_string(GC_STRING(_7_string(GC_STRING(_7_string(v54666,string_v(v12197))),string_v(v12206))),v65400)) == CTRUE)))
                         v34621->addFast((OID)v12206);
                        GC_UNLOOP; POP_SIGNAL;}
                      }
                    v50559 = GC_OBJECT(list,v34621);
                    }
                  GC_OBJECT(list,v50559);}
                if (boolean_I_any(_oid_(v50559)) != CTRUE)
                 { princ_string(((char*)"unavailable for "));
                  princ_string(v65400);
                  }
                else { CL_INT loop_handle = ClEnv->cHandle;
                    ITERATE(v12206);
                    for (START(v50559); NEXT(v12206);)
                    { if (v5975 == CTRUE)
                       v5975= (CFALSE);
                      else princ_string(((char*)", "));
                        princ_string(string_v(v12206));
                      }
                    }
                  }
              princ_string(((char*)"\n"));
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v12196);
        for (START(v50535); NEXT(v12196);)
        { GC_LOOP;
          { if (boolean_I_any((*(OBJECT(bag,v12196)))[2]) == CTRUE)
             { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
               mtformat_module1(Generate.it,((char*)"==== Exported modules [~A] ==== \n"),0,GC_OBJECT(list,list::alloc(1,(*(OBJECT(bag,v12196)))[1])));
              else ;}
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(v12197);
              for (START(OBJECT(bag,(*(OBJECT(bag,v12196)))[2])); NEXT(v12197);)
              { GC_LOOP;
                { princ_string(((char*)"   "));
                  princ_string(string_v(v12197));
                  princ_string(((char*)": "));
                  { ClaireBoolean * v5975 = CTRUE;
                    list * v50559;
                    { { bag * v64342 = entries_string2(GC_STRING(_7_string(string_v((*(OBJECT(bag,v12196)))[1]),string_v(v12197))));
                        list * v34621 = ((list *) empty_bag(v64342));
                        { CL_INT loop_handle = ClEnv->cHandle;
                          OID gc_local;
                          ITERATE(v12206);
                          for (START(v64342); NEXT(v12206);)
                          { GC_LOOP;
                            if ((isdir_ask_string(_7_string(GC_STRING(_7_string(string_v((*(OBJECT(bag,v12196)))[1]),string_v(v12197))),string_v(v12206))) == CTRUE) && 
                                ((isfile_ask_string(_7_string(GC_STRING(_7_string(GC_STRING(_7_string(string_v((*(OBJECT(bag,v12196)))[1]),string_v(v12197))),string_v(v12206))),((char*)"init.cl"))) == CTRUE) && 
                                  (isdir_ask_string(_7_string(GC_STRING(_7_string(GC_STRING(_7_string(string_v((*(OBJECT(bag,v12196)))[1]),string_v(v12197))),string_v(v12206))),v65400)) == CTRUE)))
                             v34621->addFast((OID)v12206);
                            GC_UNLOOP; POP_SIGNAL;}
                          }
                        v50559 = GC_OBJECT(list,v34621);
                        }
                      GC_OBJECT(list,v50559);}
                    if (boolean_I_any(_oid_(v50559)) != CTRUE)
                     { princ_string(((char*)"unavailable for "));
                      princ_string(v65400);
                      }
                    else { CL_INT loop_handle = ClEnv->cHandle;
                        ITERATE(v12206);
                        for (START(v50559); NEXT(v12206);)
                        { if (v5975 == CTRUE)
                           v5975= (CFALSE);
                          else princ_string(((char*)", "));
                            princ_string(string_v(v12206));
                          }
                        }
                      }
                  princ_string(((char*)"\n"));
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      CL_exit(0);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  module_info_list1(list *v12196) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    if (boolean_I_any(_oid_(v12196)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    { OID  v12197 = (*(v12196))[1];
      v12196= (skip_list(v12196,1));
      if (boolean_I_any(_oid_(v12196)) != CTRUE)
       { char * v12190 = GC_STRING(realpath_string(GC_STRING(getenv_string(((char*)"_")))));
        char * v54666 = GC_STRING(_7_string(GC_STRING(realpath_string(GC_STRING(_7_string(GC_STRING(_7_string(GC_STRING(_7_string(GC_STRING(substring_string(v12190,1,((CL_INT)rfind_string2(v12190,string_v(Core._starfs_star->value))-(CL_INT)1))),((char*)".."))),((char*)".."))),((char*)".."))))),((char*)"lib")));
        list * v37974 = GC_OBJECT(list,explode_string(GC_STRING(getenv_string(((char*)"CLAIRE_LIBS"))),GC_STRING(string_v(Core._starps_star->value))));
        ClaireBoolean * v27322 = CFALSE;
        if (isdir_ask_string(_7_string(v54666,string_v(v12197))) == CTRUE)
         { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v12206);
          bag *v12206_support;
          v12206_support = GC_OBJECT(list,entries_string2(GC_STRING(_7_string(v54666,string_v(v12197)))));
          for (START(v12206_support); NEXT(v12206);)
          { GC_LOOP;
            if (isdir_ask_string(_7_string(GC_STRING(_7_string(v54666,string_v(v12197))),string_v(v12206))) == CTRUE)
             { v27322= (CTRUE);
              if (claire_shell(string_v((*Kernel._7_plus)(GC_OID((*Kernel._7_plus)(GC_OID((*Kernel._7_plus)(GC_OID((*Kernel._7_plus)(GC_OID((*Kernel._7_plus)((*(ClEnv->params))[1],
                        GC_OID(_string_(relayed_params_void1())))),
                      _string_(((char*)" -mi ")))),
                    v12197)),
                  _string_(((char*)" ")))),
                v12206))) != 0)
               CL_exit(1);
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v50494);
          for (START(v37974); NEXT(v50494);)
          { GC_LOOP;
            if (isdir_ask_string(_7_string(string_v(v50494),string_v(v12197))) == CTRUE)
             { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(v12206);
              bag *v12206_support;
              v12206_support = GC_OBJECT(list,entries_string2(GC_STRING(_7_string(string_v(v50494),string_v(v12197)))));
              for (START(v12206_support); NEXT(v12206);)
              { GC_LOOP;
                if (isdir_ask_string(_7_string(GC_STRING(_7_string(string_v(v50494),string_v(v12197))),string_v(v12206))) == CTRUE)
                 { v27322= (CTRUE);
                  if (claire_shell(string_v((*Kernel._7_plus)(GC_OID((*Kernel._7_plus)(GC_OID((*Kernel._7_plus)(GC_OID((*Kernel._7_plus)(GC_OID((*Kernel._7_plus)((*(ClEnv->params))[1],
                            GC_OID(_string_(relayed_params_void1())))),
                          _string_(((char*)" -mi ")))),
                        v12197)),
                      _string_(((char*)" ")))),
                    v12206))) != 0)
                   CL_exit(1);
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        if (v27322 != CTRUE)
         { princ_string(((char*)"There is no module module "));
          princ_string(string_v(v12197));
          princ_string(((char*)".\n"));
          CL_exit(1);
          }
        }
      else { char * v12190 = GC_STRING(realpath_string(GC_STRING(getenv_string(((char*)"_")))));
          char * v54666 = GC_STRING(_7_string(GC_STRING(realpath_string(GC_STRING(_7_string(GC_STRING(_7_string(GC_STRING(_7_string(GC_STRING(substring_string(v12190,1,((CL_INT)rfind_string2(v12190,string_v(Core._starfs_star->value))-(CL_INT)1))),((char*)".."))),((char*)".."))),((char*)".."))))),((char*)"lib")));
          list * v37974 = GC_OBJECT(list,explode_string(GC_STRING(getenv_string(((char*)"CLAIRE_LIBS"))),GC_STRING(string_v(Core._starps_star->value))));
          char * v12206 = string_v((*(v12196))[1]);
          ClaireBoolean * v37546 = isdir_ask_string(_7_string(GC_STRING(_7_string(v54666,string_v(v12197))),v12206));
          char * v65400 = GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"v"),GC_STRING(release_void()))),((char*)"-"))),GC_STRING(Optimize.compiler->env)));
          char * v50539 = ((char*)"");
          if (v37546 == CTRUE)
           v50539= (GC_STRING(_7_string(GC_STRING(_7_string(v54666,string_v(v12197))),v12206)));
          else { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(v12200);
              for (START(v37974); NEXT(v12200);)
              { GC_LOOP;
                if (isdir_ask_string(_7_string(GC_STRING(_7_string(string_v(v12200),string_v(v12197))),v12206)) == CTRUE)
                 { GC__STRING(v50539 = _7_string(GC_STRING(_7_string(string_v(v12200),string_v(v12197))),v12206), 1);
                  { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            if (isdir_ask_string(v50539) != CTRUE)
           { princ_string(((char*)"The module "));
            princ_string(string_v(v12197));
            princ_string(((char*)" with version "));
            princ_string(v12206);
            princ_string(((char*)" doesn't exists.\n"));
            CL_exit(1);
            }
          princ_string(((char*)"==== module "));
          princ_string(string_v(v12197));
          princ_string(((char*)" version "));
          princ_string(v12206);
          princ_string(((char*)" ====\n"));
          princ_string(((char*)"- "));
          princ_string(((v37546 == CTRUE) ?
            ((char*)"Published") :
            ((char*)"Exported") ));
          princ_string(((char*)" at "));
          princ_string(v50539);
          princ_string(((char*)"\n"));
          _void_(ClEnv->verbose = -1);
          set_load_module_boolean(CFALSE);
          load_string(GC_STRING(_7_string(v50539,((char*)"init.cl"))));
          _void_(ClEnv->verbose = 0);
          { OID  v18938 = value_string(string_v(v12197));
            if (v18938 != CNULL)
             { princ_string(((char*)"- Uses "));
              princ_bag(GC_OBJECT(list,OBJECT(module,v18938)->uses));
              princ_string(((char*)"\n"));
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(v50164);
                bag *v50164_support;
                v50164_support = (list *)delete_bag(add_modules_list(GC_OBJECT(list,list::alloc(Kernel._module,1,v18938))),v18938);
                for (START(v50164_support); NEXT(v50164);)
                { GC_LOOP;
                  if (get_property(Kernel.version,OBJECT(ClaireObject,v50164)) != CNULL)
                   { princ_string(((char*)"- Depends on "));
                    print_any(v50164);
                    princ_string(((char*)" "));
                    (*Kernel.princ)(GC_OID((*Kernel.version)(v50164)));
                    princ_string(((char*)"\n"));
                    }
                  else { princ_string(((char*)"- Depends on "));
                      print_any(v50164);
                      princ_string(((char*)"\n"));
                      }
                    GC_UNLOOP; POP_SIGNAL;}
                }
              }
            else { princ_string(_7_string(v50539,((char*)"init.cl")));
                princ_string(((char*)" doesn't defines the module "));
                princ_string(v12206);
                princ_string(((char*)", please fix this init file.\n"));
                CL_exit(1);
                }
              }
          }
        CL_exit(0);
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  list_fcall_void1() { 
    
    GC_BIND;
    load_string(((char*)"init"));
    (Generate._Zcm->value= value_string(string_v(last_list(explode_string(GC_STRING(pwd_void()),GC_STRING(string_v(Core._starfs_star->value)))))));
    princ_string(((char*)"==== list of uniform property for "));
    print_any(GC_OID(Generate._Zcm->value));
    princ_string(((char*)" ====\n"));
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v23597);
      bag *v23597_support;
      v23597_support = Kernel._property->descendents;
      for (START(v23597_support); NEXT(v23597);)
      { ClaireBoolean * v23598;
        { OID v61842;{ CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(v12200);
            v61842= Kernel.cfalse;
            for (START(OBJECT(ClaireClass,v23597)->instances); NEXT(v12200);)
            if ((((OBJECT(thing,v12200)->name->definition == (NULL)) && 
                    (equal(get_property(Kernel.module_I,OBJECT(thing,v12200)->name),Generate._Zcm->value) == CTRUE)) || 
                  (_oid_(OBJECT(thing,v12200)->name->definition) == Generate._Zcm->value)) && 
                (((CL_INT)OBJECT(property,v12200)->restrictions->length > (CL_INT)1) && 
                  (uniform_property(OBJECT(property,v12200)) == CTRUE)))
             { CL_INT  v23599 = (int )(current_color);
              CL_INT  v23621 = (int )(current_bold);
              CL_INT  v23622 = v23599;
              CL_INT  v23623 = v23621;
              color(v23599,v23621);
              color_princ_string1(((char*)"``BLACK"));
              v23599= (CL_INT)((int )(current_color));
              v23621= (CL_INT)((int )(current_bold));
              color(v23622,v23623);
              print_any(v12200);
              color(v23599,v23621);
              color(v23599,v23621);
              color_princ_string1(((char*)" "));
              v23599= (CL_INT)((int )(current_color));
              v23621= (CL_INT)((int )(current_bold));
              color(v23622,v23623);
              if ((CL_INT)OBJECT(property,v12200)->dispatcher > (CL_INT)0)
               princ_string(((char*)"`REDinterface"));
              color(v23599,v23621);
              color(v23599,v23621);
              color_princ_string1(((char*)"`BLACK\n"));
              v23599= (CL_INT)((int )(current_color));
              v23621= (CL_INT)((int )(current_bold));
              color(v23622,v23623);
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(v12202);
                for (START(OBJECT(property,v12200)->restrictions); NEXT(v12202);)
                { princ_string(((char*)"  "));
                  print_any(v12202);
                  princ_string(((char*)"\n"));
                  }
                }
              color(v23599,v23621);
              color(v23622,v23623);
              }
            }
          
          v23598=OBJECT(ClaireBoolean,v61842);}
        if (v23598 == CTRUE)
         { ;ClEnv->cHandle = loop_handle; break;}
        }
      }
    CL_exit(0);
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string16_Generate_(char *v23624) { 
    return option_usage_string16_Generate(v23624)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string16_Generate(char *v61419) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Compiler environment")),
        _string_(((char*)"-env <env:string>")),
        GC_OID(_string_(append_string(((char*)"Sets the compiler environment to <env>. This is an expert option "),((char*)"used for cross-compilation.")))));
      GC_UNBIND; return (Result);}
    }
  

CL_EXPORT void  option_respond_string15_Generate(char *v61419,list *v12196) { 
    if (boolean_I_any(_oid_(v12196)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    _void_(Optimize.compiler->env = string_v((*(v12196))[1]));
    skip_list(v12196,1);
    POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string17_Generate_(char *v23625) { 
    return option_usage_string17_Generate(v23625)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string17_Generate(char *v61419) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Link with module")),
        _string_(((char*)"-m <m:module>[/<version:string>] | -l <library:path>")),
        GC_OID(_string_(append_string(GC_STRING(append_string(((char*)"claire <-m> <m> loads the module <m> in the system and add it to the list of linked modules. "),((char*)"You may specify a <version> to focus on particular version of the module.\n"))),((char*)"You may additionnaly link with a particular library using the <-l> option.")))));
      GC_UNBIND; return (Result);}
    }
  

CL_EXPORT void  option_respond_string16_Generate(char *v61419,list *v12196) { 
    
    GC_BIND;
    if (boolean_I_any(_oid_(v12196)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    { char * v18938 = string_v((*(v12196))[1]);
      skip_list(v12196,1);
      if (equal_string(v61419,((char*)"-m")) == CTRUE)
       { use_module_string(v18938);
        { module * v12197 = string2module_string1(string_v((*(explode_string(v18938,GC_STRING(string_v(Core._starfs_star->value)))))[1]));
          load_module(v12197);
          (Optimize.claire_modules->value= _oid_(GC_OBJECT(list,OBJECT(list,Optimize.claire_modules->value))->addFast((OID)_oid_(v12197))));
          }
        }
      else if (equal_string(v61419,((char*)"-l")) == CTRUE)
       GC_OBJECT(list,Optimize.compiler->libraries)->addFast((OID)_string_(v18938));
      }
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string18_Generate_(char *v23627) { 
    return option_usage_string18_Generate(v23627)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string18_Generate(char *v61419) { 
      { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Output directory")),
        _string_(((char*)"-od <directory:path>")),
        _string_(((char*)"Sets the output directory for generated C++ files.")));
      return (Result);}
    }
  

CL_EXPORT void  option_respond_string17_Generate(char *v61419,list *v12196) { 
    if (boolean_I_any(_oid_(v12196)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    _void_(Optimize.compiler->source = string_v((*(v12196))[1]));
    skip_list(v12196,1);
    POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string19_Generate_(char *v23628) { 
    return option_usage_string19_Generate(v23628)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string19_Generate(char *v61419) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Safety")),
        _string_(((char*)"-safe | -os <safety:(0 .. 6)>")),
        GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"Controls compiler safety. <-safe> put the compiler in the safest mode "),((char*)"and <-os> set the safety to a particular level :\n"))),((char*)"0 : Super-safe, the type of each value returned by a method is checked against its "))),((char*)"range, and the size of the GC protection stack is minimized. All assertions are checked.\n"))),((char*)"1 : Safe (default).\n"))),((char*)"2 : We trust explicit types & super. The type information contained in local variable "))),((char*)"definition (inside a let) and in a super (f@c(...)) has priority over type inference "))),((char*)"and run-time checks are removed.\n"))),((char*)"3 : No overflow checking (integer & arrays), in addition to level 2.\n"))),((char*)"4 : We assume that there will be no selector errors or range errors at run-time. "))),((char*)"This allows the compiler to perform further static binding.\n"))),((char*)"5 : We assume that there will be no type errors of any kind at run-time.\n"))),((char*)"6 : Unsafe (level 5 + no GC protection). Assumes that garbage collection will "))),((char*)"never be used at run-time.")))));
      GC_UNBIND; return (Result);}
    }
  

CL_EXPORT void  option_respond_string18_Generate(char *v61419,list *v12196) { 
    _void_(Optimize.compiler->safety = ((Generate.dblevel->value == ((OID)0)) ?
      0 :
      1 ));
    (Optimize.claire_lib->value= (*(Optimize.compiler->libraries_dir))[2]);
    (Optimize.claire_options->value= (*(Optimize.compiler->options))[2]);
    POP_SIGNAL;}
  

CL_EXPORT void  option_respond_string19_Generate(char *v61419,list *v12196) { 
    if (boolean_I_any(_oid_(v12196)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    (Generate.slevel->value= (*Kernel.integer_I)((*(v12196))[1]));
    skip_list(v12196,1);
    POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string20_Generate_(char *v23629) { 
    return option_usage_string20_Generate(v23629)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string20_Generate(char *v61419) { 
      { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Output name")),
        _string_(((char*)"-o <name:string>")),
        _string_(((char*)"Sets the output executable file name.")));
      return (Result);}
    }
  

CL_EXPORT void  option_respond_string20_Generate(char *v61419,list *v12196) { 
    if (boolean_I_any(_oid_(v12196)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    (Generate._Zout->value= (*(v12196))[1]);
    skip_list(v12196,1);
    POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string21_Generate_(char *v23630) { 
    return option_usage_string21_Generate(v23630)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string21_Generate(char *v61419) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Optimization")),
        _string_(((char*)"-D | -O")),
        GC_OID(_string_(append_string(GC_STRING(append_string(((char*)"Adjust the optimization level. <-D> generates a code instrumented for "),((char*)"the CLAIRE debugger without any optimization (implicitely implies -debug). "))),((char*)"<-O> enable CLAIRE compiler optimization.")))));
      GC_UNBIND; return (Result);}
    }
  

CL_EXPORT void  option_respond_string21_Generate(char *v61419,list *v12196) { 
    (Language.DEBUG_ask->value= Kernel.ctrue);
    (Generate.dblevel->value= ((OID)0));
    POP_SIGNAL;}
  

CL_EXPORT void  option_respond_string22_Generate(char *v61419,list *v12196) { 
    _void_(Optimize.compiler->optimize_ask = CTRUE);
    (Generate.dblevel->value= ((OID)2));
    POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string22_Generate_(char *v23652) { 
    return option_usage_string22_Generate(v23652)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string22_Generate(char *v61419) { 
      { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Profiler")),
        _string_(((char*)"-p")),
        _string_(((char*)"Enables profiling. The generated code is instrumented for profiling.")));
      return (Result);}
    }
  

CL_EXPORT void  option_respond_string24_Generate(char *v61419,list *v12196) { 
    _void_(Optimize.OPT->profile_ask = CTRUE);
    { OID  truc;if ((CL_INT)1 <= (CL_INT)((CL_INT)Generate.dblevel->value))
       truc = Generate.dblevel->value;
      else truc = ((OID)1);
        
      (Generate.dblevel->value = truc);}
    POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string23_Generate_(char *v23653) { 
    return option_usage_string23_Generate(v23653)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string23_Generate(char *v61419) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"C++ compiler")),
        _string_(((char*)"-cpp <cxxoption:string> | -link <linkeroption:string> | -make <makeroption:string>")),
        GC_OID(_string_(append_string(((char*)"Customize the generated makefile by adding some options "),((char*)"to the C++ compiler and linker command lines and additionaly some maker option.")))));
      GC_UNBIND; return (Result);}
    }
  

CL_EXPORT void  option_respond_string25_Generate(char *v61419,list *v12196) { 
    
    GC_BIND;
    if (boolean_I_any(_oid_(v12196)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    (Generate.cppopts->value= _string_(append_string(GC_STRING(string_v(Generate.cppopts->value)),GC_STRING(append_string(((char*)" "),string_v((*(v12196))[1]))))));
    skip_list(v12196,1);
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  option_respond_string43_Generate(char *v61419,list *v12196) { 
    if (boolean_I_any(_oid_(v12196)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    skip_list(v12196,1);
    POP_SIGNAL;}
  

CL_EXPORT void  option_respond_string26_Generate(char *v61419,list *v12196) { 
    
    GC_BIND;
    if (boolean_I_any(_oid_(v12196)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    (Generate.linkopts->value= _string_(append_string(GC_STRING(string_v(Generate.linkopts->value)),GC_STRING(append_string(((char*)" "),string_v((*(v12196))[1]))))));
    skip_list(v12196,1);
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string24_Generate_(char *v23654) { 
    return option_usage_string24_Generate(v23654)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string24_Generate(char *v61419) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Compile module")),
        _string_(((char*)"{-cc | -cl | -cm} [<m:module>]")),
        GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"Compile the module <m>. If <m> is unspecified the last module defined in the init.cl "),((char*)"from the current directory is taken.\n"))),((char*)"The <-cc> option is the lightest compiling strategy for a module: claire <-cc> will "))),((char*)"produce a C++ file for each claire file in <m>.made_of. It does not produce a makefile "))),((char*)"or system file, and assumes that the user want to keep a complete control over the generation "))),((char*)"of the executable.\n"))),((char*)"A more friendly option is <-cl>, which adds a linking step so that all generated C++ files are "))),((char*)"compiled and linked into a library <m>.lib (the name of the library can be redefined with -o or "))),((char*)"by using the external slot of the module).\n"))),((char*)"The easier way to use the compiler is the <-cm> option which produces an executable from a module. "))),((char*)"It is similar to <-cl>, but in addition it produces a system file for the module that is being "))),((char*)"compiled and a makefile which is executed by claire, producing an executable that includes the interpreter.")))));
      GC_UNBIND; return (Result);}
    }
  

CL_EXPORT void  option_respond_string27_Generate(char *v61419,list *v12196) { 
    
    GC_BIND;
    if (isfile_ask_string(((char*)"init.cl")) != CTRUE)
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Option ~A used outside a module directory")),
      _oid_(list::alloc(1,_string_(v61419))))));
    ensure_module_directories_exist_void1();
    (Generate._Zcm->value= last_list(explode_string(GC_STRING(pwd_void()),GC_STRING(string_v(Core._starfs_star->value)))));
    if (equal_string(v61419,((char*)"-cc")) == CTRUE)
     (Generate.clevel->value= ((OID)0));
    else if (equal_string(v61419,((char*)"-cm")) == CTRUE)
     (Generate.clevel->value= ((OID)2));
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string33_Generate_(char *v23655) { 
    return option_usage_string33_Generate(v23655)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string33_Generate(char *v61419) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Compile module library")),
        _string_(((char*)"[-both] {-cls | -call [-sm <m:module>] [-em <m:module>]}")),
        GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"<-cls> compiles a release module library for the current module. "),((char*)"When <-both> is specified a debug version is also generated.\n"))),((char*)"<-call> attempts to do so for a set of module located in subdirectories. "))),((char*)"If <-sm> (resp. <-em>) is specified (and match a module located in a sub directory) "))),((char*)" then any modules before (resp. after) this one are not recompiled.")))));
      GC_UNBIND; return (Result);}
    }
  

CL_EXPORT void  option_respond_string28_Generate(char *v61419,list *v12196) { 
    (Generate._Zboth->value= Kernel.ctrue);
    POP_SIGNAL;}
  

CL_EXPORT void  option_respond_string29_Generate(char *v61419,list *v12196) { 
    (Generate._Zcls->value= Kernel.ctrue);
    POP_SIGNAL;}
  

CL_EXPORT void  option_respond_string30_Generate(char *v61419,list *v12196) { 
    (Generate._Zcall->value= Kernel.ctrue);
    POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string26_Generate_(char *v23656) { 
    return option_usage_string26_Generate(v23656)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string26_Generate(char *v61419) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Module publication")),
        _string_(((char*)"[-sudo] [-ov] {-publish | -export [<i:integer> | <directory:path>]}")),
        GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"Perform a module publication. A published module can be used "),((char*)"by other modules or linked with a program (see option <-m>). "))),((char*)"The publication consist of a copy of the module (i.e. headers, library, init file and sources).\n"))),((char*)"With the <-publish> option, the copy is placed in the CLAIRE home folder. "))),((char*)"It is intended for general purpose modules that may be used by any program. "))),((char*)"According to the permission of the current user, the publication may fail. One, "))),((char*)"that have sudoer privileges may specify <-sudo> option such the copy is acheived "))),((char*)"from a sudoed process.\n"))),((char*)"The <-export> option is an alternative that allow local publication. The user "))),((char*)"may define a CLAIRE_LIBS environment variable that tell CLAIRE where to find "))),((char*)"exported modules. CLAIRE_LIBS should contain a list of path separated by a "))),((char*)"'"))),GC_STRING(string_v(Core._starps_star->value)))),((char*)"' (path separator). The path where the module is exported "))),((char*)"is determined as follow :\n"))),((char*)"- The <i>th path of CLAIRE_LIBS list\n"))),((char*)"- The given <directory>\n"))),((char*)"- By default, the first path of CLAIRE_LIBS list\n"))),((char*)"Last, one have to specify <-ov> to force the overwrite of an existing publication.")))));
      GC_UNBIND; return (Result);}
    }
  

CL_EXPORT void  option_respond_string31_Generate(char *v61419,list *v12196) { 
    (Generate._Zsudo->value= Kernel.ctrue);
    POP_SIGNAL;}
  

CL_EXPORT void  option_respond_string32_Generate(char *v61419,list *v12196) { 
    (Generate._Zov->value= Kernel.ctrue);
    POP_SIGNAL;}
  

CL_EXPORT void  option_respond_string33_Generate(char *v61419,list *v12196) { 
    (Generate._Zpublish->value= Kernel.ctrue);
    POP_SIGNAL;}
  

CL_EXPORT void  option_respond_string42_Generate(char *v61419,list *v12196) { 
    if (boolean_I_any(_oid_(v12196)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    (Generate._Zsm->value= (*(v12196))[1]);
    skip_list(v12196,1);
    POP_SIGNAL;}
  

CL_EXPORT void  option_respond_string44_Generate(char *v61419,list *v12196) { 
    if (boolean_I_any(_oid_(v12196)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    (Generate._Zem->value= (*(v12196))[1]);
    skip_list(v12196,1);
    POP_SIGNAL;}
  

CL_EXPORT void  option_respond_string34_Generate(char *v61419,list *v12196) { 
    (Generate._Zpublish->value= Kernel.ctrue);
    (Generate._Zexport->value= Kernel.ctrue);
    if (v12196->length != 0)
     { OID  v61419 = (*(v12196))[1];
      if ((CL_INT)((CL_INT)(*Kernel.integer_I)(v61419)) > (CL_INT)0)
       { skip_list(v12196,1);
        (Generate._Zexport->value= (*Kernel.integer_I)(v61419));
        }
      else if (isdir_ask_string(string_v(v61419)) == CTRUE)
       { skip_list(v12196,1);
        (Generate._Zexport->value= v61419);
        }
      }
    POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string27_Generate_(char *v23657) { 
    return option_usage_string27_Generate(v23657)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string27_Generate(char *v61419) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"New module")),
        _string_(((char*)"-nm [<partof:module>/]<name:string> +[<m:module> | <f:filename>{.cpp | .cl | .h}]")),
        GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"Create a new module with name <name>. If <partof> is specified the new module "),((char*)"is created as a part of <partof>. You may specify a list of used module <m> and a "))),((char*)"list of source file <f> for this module.\n"))),((char*)"A new directory is created with the name of the module, it contains an init.cl "))),((char*)"that defines the CLAIRE instance, when specified subdirectories containing emtpy source files "))),((char*)"are also created.\n"))),((char*)"The option <-nm> is always the last command line option, following arguments have to "))),((char*)"be a module (<m>) or a source file (<f>).")))));
      GC_UNBIND; return (Result);}
    }
  

CL_EXPORT void  option_respond_string35_Generate(char *v61419,list *v12196) { 
    new_module_list1(v12196);
    POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string28_Generate_(char *v23658) { 
    return option_usage_string28_Generate(v23658)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string28_Generate(char *v61419) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Module info")),
        _string_(((char*)"-ml | {-mi <m:module>[/<version:string>]}")),
        GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"Provide a list of available module or with <-mi> informations "),((char*)"relative to a partivular module.\n"))),((char*)"These options are always the last command line option, following arguments are "))),((char*)"ignored.")))));
      GC_UNBIND; return (Result);}
    }
  

CL_EXPORT void  option_respond_string36_Generate(char *v61419,list *v12196) { 
    module_list_list1(v12196);
    POP_SIGNAL;}
  

CL_EXPORT void  option_respond_string37_Generate(char *v61419,list *v12196) { 
    module_info_list1(v12196);
    POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string29_Generate_(char *v23659) { 
    return option_usage_string29_Generate(v23659)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string29_Generate(char *v61419) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Configuration file")),
        _string_(((char*)"-cx <test:path>")),
        GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"When claire <-cx> <test> is invoked, the compiler takes a claire configuration file <test>, "),((char*)"produces an equivalent C++ file and another C++ file called the system file. The first "))),((char*)"file is named <test>.cpp and the second file is named <test>-s.cpp. They are both placed "))),((char*)"in the directory source(compiler). The output name may be is changed with the <-o> option. "))),((char*)"The generated files are compiled and linked directly by claire. This is done by producing a "))),((char*)"makefile <test>.mk that links the generated binaries with the necessary claire modules. The "))),((char*)"option <-cx> is used to generate multi-module executable and is aimed at serious claire developers. "))),((char*)"A configuration file is a file that contains only methods without any type-checking ambiguity.")))));
      GC_UNBIND; return (Result);}
    }
  

CL_EXPORT void  option_respond_string38_Generate(char *v61419,list *v12196) { 
    if (boolean_I_any(_oid_(v12196)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    (Generate._Zcf->value= (*(v12196))[1]);
    skip_list(v12196,1);
    (Generate.clevel->value= ((OID)2));
    POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string30_Generate_(char *v23660) { 
    return option_usage_string30_Generate(v23660)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string30_Generate(char *v61419) { 
      { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"No init")),
        _string_(((char*)"-n")),
        _string_(((char*)"Prevent to load an init.cl file that is loaded by default.")));
      return (Result);}
    }
  

CL_EXPORT void  option_respond_string39_Generate(char *v61419,list *v12196) { 
    (Generate._Zinit_ask->value= Kernel.cfalse);
    POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string31_Generate_(char *v23661) { 
    return option_usage_string31_Generate(v23661)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string31_Generate(char *v61419) { 
      { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Fast dispatch")),
        _string_(((char*)"-fcall")),
        _string_(((char*)"Prints a list of uniform properties candidate for fast dispatch and exits.")));
      return (Result);}
    }
  

CL_EXPORT void  option_respond_string40_Generate(char *v61419,list *v12196) { 
    list_fcall_void1();
    POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string32_Generate_(char *v23683) { 
    return option_usage_string32_Generate(v23683)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string32_Generate(char *v61419) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Console")),
        _string_(((char*)"-noConsole | -wclConsole")),
        GC_OID(_string_(append_string(((char*)"Do not build an interpreter. <-wclConsole> is used to generate a web "),((char*)"agent that works behind an HTTP server (e.g. behind mod_wcl & Apache).")))));
      GC_UNBIND; return (Result);}
    }
  

CL_EXPORT void  option_respond_string41_Generate(char *v61419,list *v12196) { 
    
    GC_BIND;
    (Optimize.claire_modules->value= _oid_(delete_bag(OBJECT(bag,Optimize.claire_modules->value),_oid_(Language.it))));
    (Optimize.claire_modules->value= _oid_(delete_bag(OBJECT(bag,Optimize.claire_modules->value),_oid_(Reader.it))));
    if (equal_string(v61419,((char*)"-noConsole")) == CTRUE)
     GC_OBJECT(list,Optimize.compiler->libraries)->addFast((OID)_string_(((char*)"noConsole")));
    else if (equal_string(v61419,((char*)"-wclConsole")) == CTRUE)
     GC_OBJECT(list,Optimize.compiler->libraries)->addFast((OID)_string_(((char*)"wclConsole")));
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  option_parsed_void2_Generate() { 
    
    GC_BIND;
    if ((OBJECT(ClaireBoolean,Generate._Zcls->value)) == CTRUE)
     compile_module_libs_void1();
    else if ((OBJECT(ClaireBoolean,Generate._Zcall->value)) == CTRUE)
     compile_all_module_libs_void1();
    else if (((CL_INT)LENGTH_STRING(string_v(Generate._Zcf->value)) > (CL_INT)0) || 
        (((CL_INT)LENGTH_STRING(string_v(Generate._Zcxf->value)) > (CL_INT)0) || 
          ((CL_INT)LENGTH_STRING(string_v(Generate._Zcm->value)) > (CL_INT)0)))
     { if (equal(Generate._Zout->value,_string_(((char*)""))) == CTRUE)
       { if (equal(Generate._Zcm->value,_string_(((char*)""))) != CTRUE)
         (Generate._Zout->value= Generate._Zcm->value);
        else if (equal(Generate._Zcf->value,_string_(((char*)""))) != CTRUE)
         (Generate._Zout->value= _string_(replace_string(GC_STRING(string_v(Generate._Zcf->value)),((char*)".cl"),((char*)""))));
        }
      if ((OBJECT(ClaireBoolean,Generate._Zinit_ask->value)) == CTRUE)
       { if (Generate.clcc_ask->value != Kernel.ctrue)
         set_load_module_boolean(CFALSE);
        load_string(((char*)"init"));
        }
      if ((CL_INT)LENGTH_STRING(string_v(Generate.cppopts->value)) > (CL_INT)0)
       { ((*(GC_OBJECT(list,Optimize.compiler->options)))[1]=GC_OID((*Kernel._7_plus)(GC_OID((*(Optimize.compiler->options))[1]),
          GC_OID(_string_(append_string(GC_STRING(append_string(((char*)" "),GC_STRING(string_v(Generate.cppopts->value)))),((char*)" ")))))));
        ((*(GC_OBJECT(list,Optimize.compiler->options)))[2]=GC_OID((*Kernel._7_plus)(GC_OID((*(Optimize.compiler->options))[2]),
          GC_OID(_string_(append_string(GC_STRING(append_string(((char*)" "),GC_STRING(string_v(Generate.cppopts->value)))),((char*)" ")))))));
        ((*(GC_OBJECT(list,Optimize.compiler->options)))[3]=GC_OID((*Kernel._7_plus)(GC_OID((*(Optimize.compiler->options))[3]),
          GC_OID(_string_(append_string(GC_STRING(append_string(((char*)" "),GC_STRING(string_v(Generate.cppopts->value)))),((char*)" ")))))));
        }
      if ((CL_INT)LENGTH_STRING(string_v(Generate.linkopts->value)) > (CL_INT)0)
       GC_OBJECT(list,Optimize.compiler->libraries)->addFast((OID)GC_OID(_string_(append_string(((char*)" "),GC_STRING(string_v(Generate.linkopts->value))))));
      (Optimize.claire_options->value= (*(Optimize.compiler->options))[((Generate.dblevel->value == ((OID)0)) ?
        2 :
        ((Generate.dblevel->value == ((OID)2)) ?
          1 :
          3 ) )]);
      (Optimize.claire_lib->value= (*(Optimize.compiler->libraries_dir))[((Generate.dblevel->value == ((OID)0)) ?
        2 :
        ((Generate.dblevel->value == ((OID)2)) ?
          1 :
          3 ) )]);
      if ((CL_INT)((CL_INT)Generate.slevel->value) > (CL_INT)0)
       _void_(Optimize.compiler->safety = ((CL_INT)Generate.slevel->value));
      if (equal(Generate._Zcm->value,_string_(((char*)""))) != CTRUE)
       { module * v12197 = string2module_string1(string_v(Generate._Zcm->value));
        _void_(Optimize.compiler->active_ask = CTRUE);
        if (equal(_oid_(v12197->uses),_oid_(list::alloc(1,GC_OID((*(OBJECT(bag,Optimize.claire_modules->value)))[2])))) == CTRUE)
         { if (should_trace_ask_module1(Generate.it,0) == CTRUE)
           mtformat_module1(Generate.it,((char*)"=== Light Module ~S uses ~A ===\n"),0,list::alloc(2,_oid_(v12197),GC_OID(_oid_(v12197->uses))));
          else ;}
        (Optimize.claire_modules->value= _oid_(GC_OBJECT(list,OBJECT(list,Optimize.claire_modules->value))->addFast((OID)_oid_(v12197))));
        (*Reader.load)(value_string(((char*)"Compile")));
        if (equal(Generate._Zout->value,_string_(((char*)""))) != CTRUE)
         _void_(v12197->external = string_v(Generate._Zout->value));
        if ((OBJECT(ClaireBoolean,Generate.clcc_ask->value)) == CTRUE)
         load_module(v12197);
        if ((CL_INT)((CL_INT)Generate.dblevel->value) < (CL_INT)1)
         { _void_(Optimize.compiler->safety = (((CL_INT)Optimize.compiler->safety <= (CL_INT)4) ?
            Optimize.compiler->safety :
            4 ));
          GC_OBJECT(list,Optimize.compiler->debug_ask)->addFast((OID)_oid_(v12197));
          }
        if ((OBJECT(ClaireBoolean,Generate.clcc_ask->value)) == CTRUE)
         compile_module(v12197);
        if (Generate.clevel->value == ((OID)1))
         { if (equal(Generate._Zout->value,_string_(((char*)""))) != CTRUE)
           _void_(v12197->external = string_v(Generate._Zout->value));
          cmakefile_any1(_oid_(v12197),((char*)""));
          }
        else if (Generate.clevel->value == ((OID)2))
         cmakefile_any1(_oid_(v12197),GC_STRING(string_v(Generate._Zout->value)));
        CL_exit(0);
        }
      else if (equal(Generate._Zcj->value,_string_(((char*)""))) != CTRUE)
       apply_property(OBJECT(property,value_string(((char*)"jcmakefile"))),list::alloc(3,_oid_(string2module_string1(string_v(Generate._Zcj->value))),
        GC_OID(Generate._Zout->value),
        _oid_(equal(Generate.clevel->value,((OID)0)))));
      else if (equal(Generate._Zcf->value,_string_(((char*)""))) != CTRUE)
       { _void_(Optimize.compiler->active_ask = CTRUE);
        (*Reader.load)(value_string(((char*)"Compile")));
        load_string(GC_STRING(string_v(Generate._Zcf->value)));
        if ((match_wildcard_ask_string(string_v(Generate._Zcf->value),((char*)"*.cl")) != CTRUE) && 
            (isfile_ask_string(append_string(GC_STRING(string_v(Generate._Zcf->value)),((char*)".cl"))) == CTRUE))
         (Generate._Zcf->value= _string_(append_string(GC_STRING(string_v(Generate._Zcf->value)),((char*)".cl"))));
        function_compile_string1(GC_STRING(replace_string(GC_STRING(string_v(Generate._Zcf->value)),((char*)".cl"),((char*)""))),GC_STRING(string_v(Generate._Zcf->value)));
        cmakefile_any1(GC_OID(_string_(replace_string(GC_STRING(string_v(Generate._Zcf->value)),((char*)".cl"),((char*)"")))),GC_STRING(string_v(Generate._Zout->value)));
        CL_exit(0);
        }
      else if (equal(Generate._Zcxf->value,_string_(((char*)""))) != CTRUE)
       { _void_(Optimize.compiler->active_ask = CTRUE);
        (*Reader.load)(value_string(((char*)"Compile")));
        load_string(GC_STRING(string_v(Generate._Zcxf->value)));
        if ((match_wildcard_ask_string(string_v(Generate._Zcxf->value),((char*)"*.cl")) != CTRUE) && 
            (isfile_ask_string(append_string(GC_STRING(string_v(Generate._Zcxf->value)),((char*)".cl"))) == CTRUE))
         (Generate._Zcxf->value= _string_(append_string(GC_STRING(string_v(Generate._Zcxf->value)),((char*)".cl"))));
        function_compile_string1(GC_STRING(replace_string(GC_STRING(string_v(Generate._Zcxf->value)),((char*)".cl"),((char*)""))),GC_STRING(string_v(Generate._Zcxf->value)));
        CL_exit(0);
        }
      }
    if ((OBJECT(ClaireBoolean,Generate._Zpublish->value)) == CTRUE)
     export_module_boolean1(_I_equal_any(Generate._Zexport->value,Kernel.cfalse));
    if ((OBJECT(ClaireBoolean,Generate._Zcls->value)) == CTRUE)
     CL_exit(0);
    GC_UNBIND; POP_SIGNAL;}
  

CL_EXPORT void  option_respond_string57_Generate(char *v61419,list *v12196) { 
    (Generate.clcc_ask->value= Kernel.cfalse);
    POP_SIGNAL;}
  

CL_EXPORT tuple * option_usage_string37_Generate_(char *v23692) { 
    return option_usage_string37_Generate(v23692)->copyIfNeeded();
}

CL_EXPORT tuple * option_usage_string37_Generate(char *v46356) { 
      { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Compile from C++ source")),
        _string_(((char*)"-skipcl")),
        _string_(((char*)"Compile only C++ sources but not claire sources")));
      return (Result);}
    }
  




  

extern "C" CL_EXPORT void dynLoadGenerate() 
{ Generate.initModule("Generate",Compile.it,list::alloc(Kernel._module,2,_oid_(Optimize.it),_oid_(mClaire.it)),
    "./compile",list::alloc(Kernel._string,6,_string_(((char*)"gsystem")),
      _string_(((char*)"gexp")),
      _string_(((char*)"gstat")),
      _string_(((char*)"cgen")),
      _string_(((char*)"copt")),
      _string_(((char*)"gusage"))));
    Generate.metaLoad();
    Generate.it->comment = "Generate";
    }
  /***** CLAIRE Compilation of file Generate.cl 
         [version 3.5.0 / safety 5] *****/



CL_EXPORT GenerateClass Generate;

// definition of the meta-model for Generate
  void GenerateClass::metaLoad() { 
    
    ClEnv->module_I = it;
// definition of the properties 
    
    Generate.equal_exp = property::make("equal_exp",Generate.it);
    Generate.object_test = property::make("object_test",Generate.it);
    Generate.bitvector_exp = property::make("bitvector_exp",Generate.it);
    Generate.inherit_exp = property::make("inherit_exp",Generate.it);
    Generate.args_list = property::make("args_list",Generate.it);
    Generate.check_var = property::make("check_var",Generate.it);
    Generate.build_Variable = property::make("build_Variable",Generate.it);
    Generate.unfold_args = property::make("unfold_args",Generate.it);
    Generate.c_type_sort = property::make("c_type_sort",Generate.it);
    Generate.unfold_arg = property::make("unfold_arg",Generate.it);
    Generate.unfold_use = property::make("unfold_use",Generate.it);
    Generate.self_statement = property::make("self_statement",Generate.it);
    Generate.stat_construct = property::make("stat_construct",Generate.it);
    Generate.init_var = property::make("init_var",Generate.it);
    Generate.stat_while = property::make("stat_while",Generate.it);
    Generate.stat_gassign = property::make("stat_gassign",Generate.it);
    Generate.stat_for = property::make("stat_for",Generate.it);
    Generate.stat_iteration = property::make("stat_iteration",Generate.it);
    Generate.stat_super = property::make("stat_super",Generate.it);
    Generate.stat_handle = property::make("stat_handle",Generate.it);
    Generate.any_interface = property::make("any_interface",Generate.it);
    Generate.pointer_cast = property::make("pointer_cast",Generate.it);
    Generate.bad_names = property::make("bad_names",Generate.it);
    Generate.good_names = property::make("good_names",Generate.it);
    Generate.generate_float_function = property::make("generate_float_function",Generate.it);
    Generate.generate_regular_function = property::make("generate_regular_function",Generate.it);
    Generate.bitvectorSum = property::make("bitvectorSum",Generate.it);
    Generate.signature_I = property::make("signature!",Generate.it);
    Generate.bitvector_I = property::make("bitvector!",Generate.it);
    Generate.get_restrictions = property::make("get_restrictions",Generate.it);
    Generate.public_static = property::make("public_static",Generate.it);
    Generate.c_sorted_arg = property::make("c_sorted_arg",Generate.it);
    Generate.c_sorted_args = property::make("c_sorted_args",Generate.it);
    Generate.open_comparators = property::make("open_comparators",Generate.it);
    Generate.open_operators = property::make("open_operators",Generate.it);
    Generate.extension = property::make("extension",Generate.it);
    Generate.interfaces = property::make("interfaces",Generate.it);
    Generate.interface_I = property::make("interface!",Generate.it);
    Generate.indent_c = property::make("indent_c",Generate.it);
    Generate.breakline = property::make("breakline",Generate.it);
    Generate.new_block = property::make("new_block",Generate.it);
    Generate.close_block = property::make("close_block",Generate.it);
    Generate.c_test = property::make("c_test",claire.it);
    Generate.c_func = property::make("c_func",Compile.it);
    Generate.expression = property::make("expression",Generate.it);
    Generate.statement = property::make("statement",Generate.it);
    Generate.compile = property::make("compile",claire.it);
    Generate.parents = property::make("parents",Generate.it);
    Generate.outmodule = property::make("outmodule",2,Generate.it);
    Generate.generate_files = property::make("generate_files",Generate.it);
    Generate.generate_classes = property::make("generate_classes",Generate.it);
    Generate.generate_c2f = property::make("generate_c2f",Generate.it);
    Generate.generate_f2f = property::make("generate_f2f",Generate.it);
    Generate.generate_interface = property::make("generate_interface",Generate.it);
    Generate.start_module_interface = property::make("start_module_interface",Generate.it);
    Generate.generate_file = property::make("generate_file",Generate.it);
    Generate.start_file = property::make("start_file",Generate.it);
    Generate.generate_meta_load = property::make("generate_meta_load",Generate.it);
    Generate.generate_start_file = property::make("generate_start_file",Generate.it);
    Generate.generate_functions = property::make("generate_functions",Generate.it);
    Generate.generate_objects = property::make("generate_objects",Generate.it);
    Generate.generate_end_file = property::make("generate_end_file",Generate.it);
    Generate.typed_args_list = property::make("typed_args_list",Generate.it);
    Generate.namespace_I = property::make("namespace!",Generate.it);
    Generate.c_member = property::make("c_member",Generate.it);
    Generate.addFast = property::make("addFast",Generate.it);
    Generate.print_external_call = property::make("print_external_call",Generate.it);
    Generate.getC = property::make("getC",Generate.it);
    Generate.declare = property::make("declare",Generate.it);
    Generate.print_c_function = property::make("print_c_function",Generate.it);
    Generate.create_function_entry = property::make("create_function_entry",Generate.it);
    Generate.check_sort = property::make("check_sort",Generate.it);
    Generate.protect_result = property::make("protect_result",Generate.it);
    Generate.set_outfile = property::make("set_outfile",4,Generate.it);
    Generate.generate_profile = property::make("generate_profile",Generate.it);
    Generate.inner_statement = property::make("inner_statement",Generate.it);
    Generate.update_function_entry = property::make("update_function_entry",Generate.it);
    Generate.get_dependents = property::make("get_dependents",Generate.it);
    Generate.produce = property::make("produce",Generate.it);
    Generate.at = property::make("at",Generate.it);
    Generate.bag_expression = property::make("bag_expression",Generate.it);
    Generate.inline_exp = property::make("inline_exp",4,Generate.it);
    Generate.gc_protection_exp = property::make("gc_protection_exp",Generate.it);
    Generate.exp_to_protect = property::make("exp_to_protect",Generate.it);
    Generate.gc_protect = property::make("gc_protect",Generate.it);
    Generate.gassign = property::make("gassign",Generate.it);
    Generate.to_cl = property::make("to_cl",Generate.it);
    Generate.to_c = property::make("to_c",Generate.it);
    Generate.call_slot = property::make("call_slot",Generate.it);
    Generate.call_table = property::make("call_table",Generate.it);
    Generate.call_array = property::make("call_array",Generate.it);
    Generate.update = property::make("update",Generate.it);
    Generate.sign_equal = property::make("sign_equal",Generate.it);
    Generate.sign_or = property::make("sign_or",Generate.it);
    Generate.macro = property::make("macro",Generate.it);
    Generate.generate_function_start = property::make("generate_function_start",Generate.it);
    Generate.print_body = property::make("print_body",Generate.it);
    Generate.c_safe = property::make("c_safe",Generate.it);
    Generate.outer_statement = property::make("outer_statement",Generate.it);
    Generate.methods_interface = property::make("methods_interface",Generate.it);
    Generate.methods_bodies = property::make("methods_bodies",Generate.it);
    Generate.gc_usage = property::make("gc_usage",Generate.it);
    Generate.gc_usage_star = property::make("gc_usage*",Generate.it);
    Generate.gc_or = property::make("gc_or",Generate.it);
    Generate.stat_exp = property::make("stat_exp",Generate.it);
    Generate.define_variable = property::make("define_variable",Generate.it);
    Generate.char_exp_ask = property::make("char_exp?",Generate.it);
    Generate.char_exp = property::make("char_exp",Generate.it);
    Generate.bool_exp_ask = property::make("bool_exp?",Generate.it);
    Generate.bool_exp_I = property::make("bool_exp!",Generate.it);
    Generate.bexpression = property::make("bexpression",Generate.it);
    Generate.end_module_interface = property::make("end_module_interface",Generate.it);
    Generate.stat_let = property::make("stat_let",Generate.it);
    Generate.exp_Assign = property::make("exp_Assign",Generate.it);
    Generate.generate_tuple_function = property::make("generate_tuple_function",Generate.it);
    Generate.generate_s_file = property::make("generate_s_file",Generate.it);
    Generate.create_load_modules = property::make("create_load_modules",Generate.it);
    Generate.global_var_def_ask = property::make("global_var_def?",Generate.it);
    Generate.global_var_def_I = property::make("global_var_def!",Generate.it);
    Generate.getRange = property::make("getRange",Generate.it);
    Generate.globalVar = property::make("globalVar",Generate.it);
    Generate.c_string = property::make("c_string",Generate.it);
    Generate.class_princ = property::make("class_princ",Generate.it);
    Generate.any_bool_exp = property::make("any_bool_exp",Generate.it);
    Generate.generate_wcl_file = property::make("generate_wcl_file",Generate.it);
    Generate.headers_I = property::make("headers!",Generate.it);
    Generate.new_module = property::make("new_module",Generate.it);
    Generate.external_I = property::make("external!",Generate.it);
    Generate.string2module = property::make("string2module",Generate.it);
    Generate.home_path = property::make("home_path",Generate.it);
    Generate.function_compile = property::make("function_compile",Generate.it);
    Generate.libpath = property::make("libpath",Generate.it);
    Generate.libpath_I = property::make("libpath!",Generate.it);
    Generate.lib_I = property::make("lib!",Generate.it);
    Generate.files_I = property::make("files!",Generate.it);
    Generate.job_option = property::make("job_option",Generate.it);
    Generate.cmakefile = property::make("cmakefile",Generate.it);
    Generate.create_makefile_nt = property::make("create_makefile_nt",Generate.it);
    Generate.create_makefile_unix = property::make("create_makefile_unix",Generate.it);
    Generate.ensure_module_directories_exist = property::make("ensure_module_directories_exist",Generate.it);
    Generate.rcopy = property::make("rcopy",Generate.it);
    Generate.export_module = property::make("export_module",Generate.it);
    Generate.relayed_params = property::make("relayed_params",Generate.it);
    Generate.compile_module_libs = property::make("compile_module_libs",Generate.it);
    Generate.compile_all_module_libs = property::make("compile_all_module_libs",Generate.it);
    Generate.module_list = property::make("module_list",Generate.it);
    Generate.module_info = property::make("module_info",Generate.it);
    Generate.list_fcall = property::make("list_fcall",Generate.it);
    Generate.create_dynload_module = property::make("create_dynload_module",Generate.it);
    Generate.importlib_I = property::make("importlib!",Generate.it);
    
    // instructions from module sources 
    
    { global_variable * v60472 = (Generate._star_ask_interval_star = (global_variable *) Core._global_variable->instantiate("*?_interval*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Kernel.set_I,Core._Interval)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._star_dash_dash_integer_star = (global_variable *) Core._global_variable->instantiate("*--_integer*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Kernel._dot_dot,Kernel._integer)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._star_plus_integer_star = (global_variable *) Core._global_variable->instantiate("*+_integer*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Core._plus,Kernel._integer)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starnth_integer_star = (global_variable *) Core._global_variable->instantiate("*nth_integer*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Kernel.nth,Kernel._integer)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starnth_list_star = (global_variable *) Core._global_variable->instantiate("*nth_list*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Kernel.nth,Kernel._list)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starnth_1_bag_star = (global_variable *) Core._global_variable->instantiate("*nth_1_bag*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Kernel.nth_get,Kernel._bag)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starnth_string_star = (global_variable *) Core._global_variable->instantiate("*nth_string*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Kernel.nth,Kernel._string)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starnth_1_string_star = (global_variable *) Core._global_variable->instantiate("*nth_1_string*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Kernel.nth_get,Kernel._string)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starnth_equal_list_star = (global_variable *) Core._global_variable->instantiate("*nth=_list*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Kernel.nth_equal,Kernel._list)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starnot_star = (global_variable *) Core._global_variable->instantiate("*not*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Core.NOT,Kernel._any)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starknown_star = (global_variable *) Core._global_variable->instantiate("*known*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Core.known_ask,Kernel._any)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starunknown_star = (global_variable *) Core._global_variable->instantiate("*unknown*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Core.unknown_ask,Kernel._any)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starnot_equal_star = (global_variable *) Core._global_variable->instantiate("*not_equal*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Core._I_equal,Kernel._any)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starcontain_star = (global_variable *) Core._global_variable->instantiate("*contain*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Kernel.contain_ask,Kernel._list)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starmin_integer_star = (global_variable *) Core._global_variable->instantiate("*min_integer*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Core.min,Kernel._integer)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starmax_integer_star = (global_variable *) Core._global_variable->instantiate("*max_integer*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Core.max,Kernel._integer)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starlength_array_star = (global_variable *) Core._global_variable->instantiate("*length_array*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Kernel.length,Kernel._array)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starlength_bag_star = (global_variable *) Core._global_variable->instantiate("*length_bag*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Kernel.length,Kernel._bag)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starlength_string_star = (global_variable *) Core._global_variable->instantiate("*length_string*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Kernel.length,Kernel._string)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._star_plus_char_star_star = (global_variable *) Core._global_variable->instantiate("*+_char**",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Core._plus,Core._char_star)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starnth_char_star_star = (global_variable *) Core._global_variable->instantiate("*nth_char**",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Kernel.nth,Core._char_star)));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._starclose_exception_star = (global_variable *) Core._global_variable->instantiate("*close_exception*",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(_at_property1(Kernel.close,Kernel._exception)));
      close_global_variable(v60472);
      }
    
    GC_BIND;
{ (Generate._producer = ClaireClass::make("producer",Kernel._thing,Generate.it));
      CL_ADD_SLOT(Generate._producer,Generate_producer,Generate.open_comparators,open_comparators,nth_class1(Kernel._list,Kernel._operation),CNULL);
      CL_ADD_SLOT(Generate._producer,Generate_producer,Generate.open_operators,open_operators,nth_class1(Kernel._list,Kernel._operation),CNULL);
      CL_ADD_SLOT(Generate._producer,Generate_producer,Kernel.body,body,Kernel._any,((OID)0));
      CL_ADD_SLOT(Generate._producer,Generate_producer,Generate.extension,extension,Kernel._string,CNULL);
      CL_ADD_SLOT(Generate._producer,Generate_producer,Kernel.comment,comment,Kernel._string,CNULL);
      CL_ADD_SLOT(Generate._producer,Generate_producer,Generate.interfaces,interfaces,Kernel._list,CNULL);
      CL_ADD_SLOT(Generate._producer,Generate_producer,Kernel.stat,stat,Kernel._integer,((OID)0));
      }
    
    GC_UNBIND;
{ global_variable * v60472 = (Generate.PRODUCER = (global_variable *) Core._global_variable->instantiate("PRODUCER",claire.it));
      _void_(v60472->range = Generate._producer);
      _void_(v60472->value = CNULL);
      close_global_variable(v60472);
      }
    
    GC_BIND;
Language.ident->addMethod(list::domain(1,Kernel._symbol),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(ident_symbol,"ident_symbol"));
    
    Language.ident->addMethod(list::domain(1,Kernel._thing),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(ident_thing,"ident_thing"));
    
    Language.ident->addMethod(list::domain(1,Kernel._class),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(ident_class,"ident_class"));
    
    Generate.interface_I->addMethod(list::domain(1,Kernel._class),Kernel._void,
    	NEW_ALLOC,_function_(interface_I_class,"interface!_class"));
    
    Generate.class_princ->addMethod(list::domain(1,Kernel._class),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(class_princ_class,"class_princ_class"));
    
    Generate.indent_c->addMethod(list::domain(1,Kernel._void),Kernel._any,
    	RETURN_ARG,_function_(indent_c_void,"indent_c_void"));
    
    Generate.breakline->addMethod(list::domain(1,Kernel._void),Kernel._any,
    	RETURN_ARG,_function_(breakline_void,"breakline_void"));
    
    Generate.new_block->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	SLOT_UPDATE,_function_(new_block_void,"new_block_void"));
    
    Generate.close_block->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(close_block_void,"close_block_void"));
    
    _void_(Generate._producer->open = 3);
    
    Generate.c_test->addMethod(list::domain(1,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_test_any,"c_test_any"));
    
    Generate.c_test->addMethod(list::domain(1,Kernel._method),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_test_method,"c_test_method"));
    
    Generate.compile->addMethod(list::domain(1,Kernel._module),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(compile_module,"compile_module"));
    
    Generate.generate_files->addMethod(list::domain(1,Kernel._module),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_files_module,"generate_files_module"));
    
    Generate.generate_f2f->addMethod(list::domain(1,Kernel._module),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(generate_f2f_module,"generate_f2f_module"));
    
    Generate.generate_file->addMethod(list::domain(2,Kernel._string,Kernel._module),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(generate_file_string1,"generate_file_string1"));
    
    { (Generate.classFile = (table *) Kernel._table->instantiate("classFile",Generate.it));
      _void_(Generate.classFile->range = Kernel._port);
      _void_(Generate.classFile->params = _oid_(Kernel._any));
      _void_(Generate.classFile->domain = Kernel._class);
      _void_(Generate.classFile->graph = make_list_integer(29,CNULL));
      _void_(Generate.classFile->DEFAULT = CNULL);
      }
    
    Generate.generate_classes->addMethod(list::domain(1,Kernel._module),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(generate_classes_module,"generate_classes_module"));
    
    Generate.generate_c2f->addMethod(list::domain(1,Kernel._module),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(generate_c2f_module,"generate_c2f_module"));
    
    Generate.generate_interface->addMethod(list::domain(2,Kernel._module,Kernel._bag),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_interface_module,"generate_interface_module"));
    
    Generate.generate_objects->addMethod(list::domain(1,Kernel._module),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_objects_module,"generate_objects_module"));
    
    Generate.generate_meta_load->addMethod(list::domain(1,Kernel._module),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_meta_load_module,"generate_meta_load_module"));
    
    Generate.global_var_def_ask->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	NEW_ALLOC,_function_(global_var_def_ask_any,"global_var_def?_any"));
    
    Generate.getRange->addMethod(list::domain(1,Core._global_variable),Kernel._class,
    	NEW_ALLOC+RETURN_ARG,_function_(getRange_global_variable,"getRange_global_variable"));
    
    Generate.generate_functions->addMethod(list::domain(1,Kernel._module),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_functions_module,"generate_functions_module"));
    
    Generate.parents->addMethod(list::domain(2,Kernel._module,Kernel._list),Kernel._list,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(parents_module,"parents_module"));
    
    Generate.parents->addMethod(list::domain(1,Kernel._list),Kernel._list,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(parents_list,"parents_list"));
    
    Kernel.get->addMethod(list::domain(1,Kernel._module),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE,_function_(get_module2,"get_module2"));
    
    Generate.generate_file->addMethod(list::domain(2,Kernel._string,Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(generate_file_string2,"generate_file_string2"));
    
    Generate.generate_wcl_file->addMethod(list::domain(3,Kernel._string,Kernel._string,Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(generate_wcl_file_string,"generate_wcl_file_string"));
    
    Optimize.make_c_function->addMethod(list::domain(3,Core._lambda,Kernel._string,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(make_c_function_lambda_Generate,"make_c_function_lambda_Generate"));
    
    Generate.print_c_function->addMethod(list::domain(3,Core._lambda,Kernel._string,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(print_c_function_lambda2,"print_c_function_lambda2"));
    
    Generate.print_body->addMethod(list::domain(5,Language._If,
      Kernel._string,
      Kernel._class,
      Language._If,
      Kernel._boolean),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(print_body_If,"print_body_If"));
    
    Generate.print_body->addMethod(list::domain(5,Kernel._any,
      Kernel._string,
      Kernel._class,
      Kernel._any,
      Kernel._boolean),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(print_body_any,"print_body_any"));
    
    Generate.print_body->addMethod(list::domain(5,Language._Do,
      Kernel._string,
      Kernel._class,
      Kernel._any,
      Kernel._boolean),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(print_body_Do,"print_body_Do"));
    
    Generate.outer_statement->addMethod(list::domain(4,Kernel._any,
      Kernel._string,
      Kernel._class,
      Kernel._boolean),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(outer_statement_any,"outer_statement_any"));
    
    Generate.c_safe->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_safe_any,"c_safe_any"));
    
    GC_UNBIND;
{ global_variable * v60472 = (Generate.WrongMethod = (global_variable *) Core._global_variable->instantiate("WrongMethod",claire.it));
      _void_(v60472->range = Kernel._any);
      _void_(v60472->value = ((OID)1));
      close_global_variable(v60472);
      }
    
    GC_BIND;
Generate.check_sort->addMethod(list::domain(1,Kernel._method),Kernel._class,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(check_sort_method,"check_sort_method"));
    
    Generate.typed_args_list->addMethod(list::domain(1,Kernel._list),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(typed_args_list_list,"typed_args_list_list"));
    
    Generate.get_dependents->addMethod(list::domain(1,Kernel._method),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(get_dependents_method,"get_dependents_method"));
    
    Kernel.c_princ->addMethod(list::domain(1,Kernel._function),Kernel._void,
    	0,_function_(c_princ_function,"c_princ_function"));
    
    Generate.set_outfile->addMethod(list::domain(1,Core._lambda),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(set_outfile_lambda,"set_outfile_lambda"));
    
    { _void_(Generate.set_outfile->open = 4);
      _void_(Generate.inline_exp->open = 4);
      }
    
    Generate.c_func->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_func_any,"c_func_any"));
    
    Generate.expression->addMethod(list::domain(2,Kernel._thing,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_thing,"expression_thing"));
    
    Generate.expression->addMethod(list::domain(2,Kernel._integer,Kernel._any),Kernel._void,
    	0,_function_(expression_integer,"expression_integer"));
    
    Generate.expression->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_any,"expression_any"));
    
    Generate.expression->addMethod(list::domain(2,Kernel._string,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_string,"expression_string"));
    
    Generate.expression->addFloatMethod(list::domain(2,Kernel._float,Kernel._any),Kernel._void,
    	0,_function_(expression_float,"expression_float"),
    _function_(expression_float_,"expression_float_"));
    
    Generate.expression->addMethod(list::domain(2,Kernel._boolean,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_boolean,"expression_boolean"));
    
    Generate.expression->addMethod(list::domain(2,Kernel._environment,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_environment,"expression_environment"));
    
    Generate.expression->addMethod(list::domain(2,Language._Variable,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(expression_Variable,"expression_Variable"));
    
    Generate.expression->addMethod(list::domain(2,Core._global_variable,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_global_variable,"expression_global_variable"));
    
    Generate.expression->addMethod(list::domain(2,Language._Set,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_Set,"expression_Set"));
    
    Generate.expression->addMethod(list::domain(2,Kernel._set,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_set2,"expression_set2"));
    
    Generate.expression->addMethod(list::domain(2,Language._Tuple,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_Tuple,"expression_Tuple"));
    
    Generate.expression->addMethod(list::domain(2,Kernel._tuple,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_tuple,"expression_tuple"));
    
    Generate.expression->addMethod(list::domain(2,Language._List,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_List,"expression_List"));
    
    Generate.expression->addMethod(list::domain(2,Kernel._list,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_list,"expression_list"));
    
    Generate.expression->addMethod(list::domain(2,Language._Call,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(expression_Call2,"expression_Call2"));
    
    Generate.expression->addMethod(list::domain(2,Language._Call_method1,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(expression_Call_method12,"expression_Call_method12"));
    
    Generate.expression->addMethod(list::domain(2,Language._Call_method2,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(expression_Call_method22,"expression_Call_method22"));
    
    Generate.expression->addMethod(list::domain(2,Language._Call_method,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(expression_Call_method2,"expression_Call_method2"));
    
    Generate.bexpression->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(bexpression_any,"bexpression_any"));
    
    Generate.expression->addMethod(list::domain(2,Language._If,Kernel._any),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(expression_If,"expression_If"));
    
    Generate.expression->addMethod(list::domain(2,Language._Assign,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(expression_Assign,"expression_Assign"));
    
    Generate.expression->addMethod(list::domain(2,Optimize._to_protect,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(expression_to_protect,"expression_to_protect"));
    
    Generate.gc_protect->addMethod(list::domain(1,Kernel._class),Kernel._string,
    	SLOT_UPDATE,_function_(gc_protect_class,"gc_protect_class"));
    
    Generate.expression->addMethod(list::domain(2,Language._Gassign,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_Gassign,"expression_Gassign"));
    
    Generate.expression->addMethod(list::domain(2,Language._And,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_And,"expression_And"));
    
    Generate.expression->addMethod(list::domain(2,Language._Or,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_Or,"expression_Or"));
    
    Generate.expression->addMethod(list::domain(2,Optimize._to_CL,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(expression_to_CL,"expression_to_CL"));
    
    Generate.expression->addMethod(list::domain(2,Optimize._to_C,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(expression_to_C,"expression_to_C"));
    
    Generate.expression->addMethod(list::domain(2,Optimize._C_cast,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(expression_C_cast,"expression_C_cast"));
    
    Generate.expression->addMethod(list::domain(2,Language._Call_slot,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_Call_slot,"expression_Call_slot"));
    
    Generate.expression->addMethod(list::domain(2,Language._Call_table,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_Call_table,"expression_Call_table"));
    
    Generate.expression->addMethod(list::domain(2,Language._Call_array,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_Call_array,"expression_Call_array"));
    
    Generate.expression->addMethod(list::domain(2,Language._Update,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(expression_Update,"expression_Update"));
    
    Generate.sign_equal->addMethod(list::domain(1,Kernel._boolean),Kernel._void,
    	0,_function_(sign_equal_boolean,"sign_equal_boolean"));
    
    Generate.sign_or->addMethod(list::domain(1,Kernel._boolean),Kernel._void,
    	0,_function_(sign_or_boolean,"sign_or_boolean"));
    
    Optimize.bool_exp->addMethod(list::domain(3,Kernel._any,Kernel._boolean,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(bool_exp_any_Generate,"bool_exp_any_Generate"));
    
    Generate.any_bool_exp->addMethod(list::domain(4,Kernel._any,
      Kernel._boolean,
      Kernel._any,
      Kernel._boolean),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(any_bool_exp_any,"any_bool_exp_any"));
    
    Optimize.bool_exp->addMethod(list::domain(3,Optimize._to_CL,Kernel._boolean,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(bool_exp_to_CL_Generate,"bool_exp_to_CL_Generate"));
    
    Optimize.bool_exp->addMethod(list::domain(3,Language._If,Kernel._boolean,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(bool_exp_If_Generate,"bool_exp_If_Generate"));
    
    Optimize.bool_exp->addMethod(list::domain(3,Language._And,Kernel._boolean,Kernel._any),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(bool_exp_And_Generate,"bool_exp_And_Generate"));
    
    Optimize.bool_exp->addMethod(list::domain(3,Language._Or,Kernel._boolean,Kernel._any),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(bool_exp_Or_Generate,"bool_exp_Or_Generate"));
    
    Optimize.bool_exp->addMethod(list::domain(3,Language._Call_method1,Kernel._boolean,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(bool_exp_Call_method1_Generate,"bool_exp_Call_method1_Generate"));
    
    Optimize.bool_exp->addMethod(list::domain(3,Language._Call_method2,Kernel._boolean,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(bool_exp_Call_method2_Generate,"bool_exp_Call_method2_Generate"));
    
    Generate.bool_exp_ask->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	NEW_ALLOC,_function_(bool_exp_ask_any,"bool_exp?_any"));
    
    Generate.args_list->addMethod(list::domain(3,Kernel._bag,Kernel._any,Kernel._boolean),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(args_list_bag,"args_list_bag"));
    
    Generate.check_var->addMethod(list::domain(3,Kernel._string,Kernel._any,Kernel._any),Kernel._string,
    	NEW_ALLOC+RETURN_ARG,_function_(check_var_string,"check_var_string"));
    
    Generate.build_Variable->addMethod(list::domain(2,Kernel._string,Kernel._any),Language._Variable,
    	NEW_ALLOC,_function_(build_Variable_string,"build_Variable_string"));
    
    Generate.unfold_args->addMethod(list::domain(1,Kernel._list),Kernel._list,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(unfold_args_list,"unfold_args_list"));
    
    Generate.c_type_sort->addMethod(list::domain(1,Kernel._any),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_type_sort_any,"c_type_sort_any"));
    
    Generate.unfold_arg->addMethod(list::domain(3,Kernel._list,Kernel._list,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(unfold_arg_list,"unfold_arg_list"));
    
    Generate.unfold_use->addMethod(list::domain(4,Kernel._list,
      Kernel._any,
      Kernel._any,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(unfold_use_list,"unfold_use_list"));
    
    Generate.statement->addMethod(list::domain(3,Kernel._any,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(statement_any,"statement_any"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Construct,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(self_statement_Construct,"self_statement_Construct"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._If,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_If,"self_statement_If"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Do,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_Do,"self_statement_Do"));
    
    Generate.inner_statement->addMethod(list::domain(3,Kernel._any,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(inner_statement_any,"inner_statement_any"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Let,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(self_statement_Let,"self_statement_Let"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._And,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_And,"self_statement_And"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Or,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_Or,"self_statement_Or"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._While,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(self_statement_While,"self_statement_While"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Assign,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_Assign,"self_statement_Assign"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Gassign,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(self_statement_Gassign,"self_statement_Gassign"));
    
    Generate.self_statement->addMethod(list::domain(3,Optimize._to_protect,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_to_protect,"self_statement_to_protect"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._For,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(self_statement_For,"self_statement_For"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Iteration,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(self_statement_Iteration,"self_statement_Iteration"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Return,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_Return,"self_statement_Return"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Call,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_Call,"self_statement_Call"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Call_method,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_Call_method,"self_statement_Call_method"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Call_method1,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_Call_method1,"self_statement_Call_method1"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Call_method2,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_Call_method2,"self_statement_Call_method2"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Super,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(self_statement_Super,"self_statement_Super"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Cast,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_Cast,"self_statement_Cast"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Handle,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(self_statement_Handle,"self_statement_Handle"));
    
    Generate.self_statement->addMethod(list::domain(3,Optimize._to_CL,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_to_CL,"self_statement_to_CL"));
    
    Generate.self_statement->addMethod(list::domain(3,Optimize._to_C,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_to_C,"self_statement_to_C"));
    
    Generate.self_statement->addMethod(list::domain(3,Optimize._C_cast,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_C_cast,"self_statement_C_cast"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Call_slot,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_Call_slot,"self_statement_Call_slot"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Call_table,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_Call_table,"self_statement_Call_table"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Call_array,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_Call_array,"self_statement_Call_array"));
    
    Generate.self_statement->addMethod(list::domain(3,Language._Update,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_statement_Update,"self_statement_Update"));
    
    { (Generate._c_producer = ClaireClass::make("c_producer",Generate._producer,Generate.it));
      CL_ADD_SLOT(Generate._c_producer,Generate_c_producer,Generate.bad_names,bad_names,nth_class1(Kernel._list,Kernel._symbol),CNULL);
      CL_ADD_SLOT(Generate._c_producer,Generate_c_producer,Generate.good_names,good_names,nth_class1(Kernel._list,Kernel._symbol),CNULL);
      }
    
    { (Generate.C_plus_plusPRODUCER = (Generate_c_producer *) Generate._c_producer->instantiate("C++PRODUCER",Generate.it));
      _void_(Generate.C_plus_plusPRODUCER->open_comparators = list::alloc(4,_oid_(Kernel._inf),
        _oid_(Kernel._sup),
        _oid_(Kernel._sup_equal),
        _oid_(Kernel._inf_equal)));
      _void_(Generate.C_plus_plusPRODUCER->open_operators = list::alloc(5,_oid_(Core._plus),
        _oid_(Kernel._dash),
        _oid_(Kernel._star),
        _oid_(Kernel._7),
        _oid_(Core._sup_sup)));
      _void_(Generate.C_plus_plusPRODUCER->extension = ((char*)".cpp"));
      _void_(Generate.C_plus_plusPRODUCER->comment = ((char*)"C++"));
      { Generate_c_producer * v23714 = Generate.C_plus_plusPRODUCER; 
        list * v23715;
        { GC_ANY(v23715= list::empty(Kernel.emptySet));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"do"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"if"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"and"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"or"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"not"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"printf"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"void"))));
          ((list *) v23715)->addFast((OID)_oid_(Optimize._Pattern->name));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"exception"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"return"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"new"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"class"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"private"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"operator"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"default"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"Handle"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"import"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"freeable_object"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"catch"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"stdout"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"stdin"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"stderr"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"break"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"char"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"interface"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"EOF"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"relation"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"System"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"object"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"port"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"socket"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"delete"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"boolean"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"function"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"type"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"system_thing"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"environment"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"abstract"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"final"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"system_object"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"NEW_ALLOC"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"BAG_UPDATE"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SLOT_UPDATE"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"RETURN_ARG"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SAFE_RESULT"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SAFE_GC"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"collection"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIG_DFL"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIG_IGN"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGHUP"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGINT"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGQUIT"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGILL"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGTRAP"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGABRT"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGIOT"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGEMT"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGFPE"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGKILL"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGBUS"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGSEGV"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGSYS"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGPIPE"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGALRM"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGTERM"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGURG"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGSTOP"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGTSTP"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGCONT"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGCHLD"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGTTIN"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGTTOU"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGIO"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGXCPU"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGXFSZ"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGVTALRM"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGPROF"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGWINCH"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGINFO"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGUSR1"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"SIGUSR2"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"ITIMER_REAL"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"ITIMER_VIRTUAL"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"ITIMER_PROF"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"F_SETOWN"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"F_SETFL"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"F_GETFL"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"FASYNC"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"WRUNNING"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"WEXITED"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"WSIGNALED"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"WSTOPPED"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"register"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"error"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"pipe"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"sizeof"))));
          ((list *) v23715)->addFast((OID)_oid_(symbol_I_string2(((char*)"do"))));}
        _void_(v23714->bad_names = v23715);}
      { Generate_c_producer * v23716 = Generate.C_plus_plusPRODUCER; 
        list * v23717;
        { GC_ANY(v23717= list::empty(Kernel.emptySet));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"DO"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"IF"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireAnd"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireOr"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"NOT"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"PRINTF"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireVoid"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClairePattern"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireException"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"RETURN"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"NEW"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireClass"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"PRIVATE"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireOperator"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"DEFAULT"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireHandle"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireImport"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"FreeableObject"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CATCH"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"cl_stdout"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"cl_stdin"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"cl_stderr"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"BREAK"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireChar"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireInterface"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"_eof"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireRelation"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"Core"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireObject"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"PortObject"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"cl_socket"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"_delete"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireBoolean"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireFunction"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireType"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"SystemThing"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireEnvironment"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ABSTRACT"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"FINAL"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"SystemObject"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"_NEW_ALLOC"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"_BAG_UPDATE"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"_SLOT_UPDATE"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"_RETURN_ARG"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"_SAFE_RESULT"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"_SAFE_GC"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireCollection"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIG_DFL"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIG_IGN"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGHUP"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGINT"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGQUIT"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGILL"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGTRAP"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGABRT"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGIOT"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGEMT"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGFPE"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGKILL"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGBUS"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGSEGV"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGSYS"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGPIPE"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGALRM"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGTERM"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGURG"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGSTOP"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGTSTP"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGCONT"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGCHLD"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGTTIN"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGTTOU"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGIO"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGXCPU"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGXFSZ"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGVTALRM"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGPROF"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGWINCH"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGINFO"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGUSR1"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_SIGUSR2"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_ITIMER_REAL"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_ITIMER_VIRTUAL"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_ITIMER_PROF"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_F_SETOWN"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_F_SETFL"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_F_GETFL"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_FASYNC"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_WRUNNING"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_WEXITED"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_WSIGNALED"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"CL_WSTOPPED"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"REGISTER"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"ClaireError"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"cl_pipe"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"cl_sizeof"))));
          ((list *) v23717)->addFast((OID)_oid_(symbol_I_string2(((char*)"cldo"))));}
        _void_(v23716->good_names = v23717);}
      _void_(Generate.C_plus_plusPRODUCER->interfaces = list::alloc(14,_oid_(Kernel._string),
        _string_(((char*)"char *")),
        _oid_(Core._char_star),
        _string_(((char*)"char*")),
        _oid_(Kernel._char),
        _string_(((char*)"ClaireChar *")),
        _oid_(Core._FILE_star),
        _string_(((char*)"FILE*")),
        _oid_(Kernel._float),
        _string_(((char*)"double ")),
        _oid_(Kernel._array),
        _string_(((char*)"OID *")),
        _oid_(Kernel._function),
        _string_(((char*)"OID (*)()"))));
      ;}
    
    (Generate.PRODUCER->value= _oid_(Generate.C_plus_plusPRODUCER));
    
    Generate.c_string->addMethod(list::domain(2,Generate._c_producer,Language._Variable),Kernel._string,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_string_c_producer1,"c_string_c_producer1"));
    
    Generate.c_string->addMethod(list::domain(2,Generate._c_producer,Kernel._symbol),Kernel._string,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_string_c_producer2,"c_string_c_producer2"));
    
    Kernel.string_I->addMethod(list::domain(2,Generate._c_producer,Language._Variable),Kernel._string,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(string_I_c_producer1,"string!_c_producer1"));
    
    Kernel.string_I->addMethod(list::domain(2,Generate._c_producer,Kernel._symbol),Kernel._string,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(string_I_c_producer2,"string!_c_producer2"));
    
    Language.ident->addMethod(list::domain(2,Generate._c_producer,Language._Variable),Kernel._void,
    	NEW_ALLOC,_function_(ident_c_producer3,"ident_c_producer3"));
    
    Language.ident->addMethod(list::domain(2,Generate._c_producer,Kernel._symbol),Kernel._void,
    	0,_function_(ident_c_producer,"ident_c_producer"));
    
    Generate.class_princ->addMethod(list::domain(2,Generate._c_producer,Kernel._class),Kernel._void,
    	RETURN_ARG,_function_(class_princ_c_producer,"class_princ_c_producer"));
    
    Generate.produce->addMethod(list::domain(2,Generate._c_producer,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(produce_c_producer2,"produce_c_producer2"));
    
    Generate.globalVar->addMethod(list::domain(2,Generate._c_producer,Core._global_variable),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(globalVar_c_producer,"globalVar_c_producer"));
    
    Generate.stat_exp->addMethod(list::domain(3,Generate._c_producer,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(stat_exp_c_producer,"stat_exp_c_producer"));
    
    Generate.namespace_I->addMethod(list::domain(2,Generate._c_producer,Kernel._module),Kernel._void,
    	NEW_ALLOC,_function_(namespace_I_c_producer,"namespace!_c_producer"));
    
    Kernel.module_I->addMethod(list::domain(2,Generate._c_producer,Kernel._module),Kernel._void,
    	NEW_ALLOC,_function_(module_I_c_producer,"module!_c_producer"));
    
    Generate.declare->addMethod(list::domain(2,Generate._c_producer,Kernel._property),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(declare_c_producer,"declare_c_producer"));
    
    Generate.start_module_interface->addMethod(list::domain(2,Generate._c_producer,Kernel._module),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(start_module_interface_c_producer,"start_module_interface_c_producer"));
    
    Generate.end_module_interface->addMethod(list::domain(2,Generate._c_producer,Kernel._module),Kernel._void,
    	0,_function_(end_module_interface_c_producer,"end_module_interface_c_producer"));
    
    Generate.generate_end_file->addMethod(list::domain(2,Generate._c_producer,Kernel._module),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(generate_end_file_c_producer,"generate_end_file_c_producer"));
    
    Generate.generate_classes->addMethod(list::domain(3,Generate._c_producer,Kernel._string,Kernel._module),Kernel._void,
    	NEW_ALLOC,_function_(generate_classes_c_producer,"generate_classes_c_producer"));
    
    Generate.generate_start_file->addMethod(list::domain(2,Generate._c_producer,Kernel._module),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_start_file_c_producer,"generate_start_file_c_producer"));
    
    Generate.generate_meta_load->addMethod(list::domain(2,Generate._c_producer,Kernel._module),Kernel._void,
    	SLOT_UPDATE,_function_(generate_meta_load_c_producer,"generate_meta_load_c_producer"));
    
    Generate.start_file->addMethod(list::domain(2,Kernel._string,Kernel._module),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(start_file_string,"start_file_string"));
    
    Generate.define_variable->addMethod(list::domain(3,Generate._c_producer,Kernel._class,Kernel._string),Kernel._void,
    	NEW_ALLOC,_function_(define_variable_c_producer2,"define_variable_c_producer2"));
    
    Generate.generate_profile->addMethod(list::domain(2,Generate._c_producer,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_profile_c_producer,"generate_profile_c_producer"));
    
    Generate.generate_interface->addMethod(list::domain(2,Generate._c_producer,Kernel._module),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE,_function_(generate_interface_c_producer,"generate_interface_c_producer"));
    
    Generate.global_var_def_I->addMethod(list::domain(3,Generate._c_producer,Kernel._module,Language._Let),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(global_var_def_I_c_producer,"global_var_def!_c_producer"));
    
    Generate.gc_usage->addMethod(list::domain(2,Kernel._any,Kernel._boolean),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(gc_usage_any,"gc_usage_any"));
    
    Generate.gc_or->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._any,
    	RETURN_ARG,_function_(gc_or_any,"gc_or_any"));
    
    Generate.gc_usage_star->addMethod(list::domain(2,Kernel._list,Kernel._boolean),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(gc_usage_star_list,"gc_usage*_list"));
    
    Generate.protect_result->addMethod(list::domain(4,Generate._c_producer,
      Kernel._class,
      Kernel._boolean,
      Kernel._any),Kernel._string,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(protect_result_c_producer,"protect_result_c_producer"));
    
    Generate.generate_function_start->addMethod(list::domain(5,Generate._c_producer,
      Core._lambda,
      Kernel._class,
      Kernel._any,
      Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_function_start_c_producer,"generate_function_start_c_producer"));
    
    Generate.generate_regular_function->addMethod(list::domain(6,Generate._c_producer,
      Core._lambda,
      Kernel._function,
      Kernel._class,
      Kernel._any,
      Kernel._list),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_regular_function_c_producer,"generate_regular_function_c_producer"));
    
    Generate.generate_float_function->addMethod(list::domain(3,Generate._c_producer,Kernel._method,Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_float_function_c_producer,"generate_float_function_c_producer"));
    
    Generate.at->addMethod(list::domain(1,Generate._c_producer),Kernel._void,
    	0,_function_(at_c_producer,"at_c_producer"));
    
    Generate.generate_tuple_function->addMethod(list::domain(3,Generate._c_producer,Kernel._method,Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_tuple_function_c_producer,"generate_tuple_function_c_producer"));
    
    Generate.create_function_entry->addMethod(list::domain(4,Generate._c_producer,
      Core._lambda,
      Kernel._string,
      Kernel._any),Kernel._any,
    	0,_function_(create_function_entry_c_producer,"create_function_entry_c_producer"));
    
    Generate.update_function_entry->addMethod(list::domain(4,Generate._c_producer,
      Kernel._function,
      Kernel._list,
      Kernel._class),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE,_function_(update_function_entry_c_producer,"update_function_entry_c_producer"));
    
    Optimize.c_interface->addMethod(list::domain(1,Kernel._class),Kernel._string,
    	RETURN_ARG,_function_(c_interface_class1_Generate,"c_interface_class1_Generate"));
    
    Optimize.c_interface->addMethod(list::domain(2,Kernel._class,Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(c_interface_class2_Generate,"c_interface_class2_Generate"));
    
    Optimize.c_interface->addMethod(list::domain(1,Kernel._method),Kernel._void,
    	NEW_ALLOC,_function_(c_interface_method_Generate,"c_interface_method_Generate"));
    
    Generate.interface_I->addMethod(list::domain(2,Generate._c_producer,Kernel._class),Kernel._void,
    	NEW_ALLOC,_function_(interface_I_c_producer,"interface!_c_producer"));
    
    Generate.to_cl->addMethod(list::domain(4,Generate._c_producer,
      Kernel._any,
      Kernel._class,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(to_cl_c_producer,"to_cl_c_producer"));
    
    Generate.to_c->addMethod(list::domain(4,Generate._c_producer,
      Kernel._any,
      Kernel._class,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(to_c_c_producer1,"to_c_c_producer1"));
    
    Generate.to_c->addMethod(list::domain(2,Generate._c_producer,Kernel._class),Kernel._void,
    	NEW_ALLOC,_function_(to_c_c_producer2,"to_c_c_producer2"));
    
    Generate.public_static->addMethod(list::domain(1,Generate._c_producer),Kernel._void,
    	0,_function_(public_static_c_producer,"public_static_c_producer"));
    
    Generate.bool_exp_I->addMethod(list::domain(3,Generate._c_producer,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(bool_exp_I_c_producer,"bool_exp!_c_producer"));
    
    Generate.inherit_exp->addMethod(list::domain(4,Generate._c_producer,
      Kernel._any,
      Kernel._any,
      Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(inherit_exp_c_producer,"inherit_exp_c_producer"));
    
    Generate.bitvector_exp->addMethod(list::domain(4,Generate._c_producer,
      Kernel._any,
      Kernel._any,
      Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(bitvector_exp_c_producer,"bitvector_exp_c_producer"));
    
    Generate.equal_exp->addMethod(list::domain(5,Generate._c_producer,
      Kernel._any,
      Kernel._boolean,
      Kernel._any,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(equal_exp_c_producer,"equal_exp_c_producer"));
    
    Generate.char_exp_ask->addMethod(list::domain(2,Generate._c_producer,Kernel._any),Kernel._boolean,
    	0,_function_(char_exp_ask_c_producer2,"char_exp?_c_producer2"));
    
    Generate.char_exp->addMethod(list::domain(3,Generate._c_producer,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(char_exp_c_producer2,"char_exp_c_producer2"));
    
    Generate.c_member->addMethod(list::domain(5,Generate._c_producer,
      Kernel._any,
      Kernel._class,
      Kernel._property,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(c_member_c_producer,"c_member_c_producer"));
    
    Generate.addFast->addMethod(list::domain(1,Generate._c_producer),Kernel._void,
    	0,_function_(addFast_c_producer,"addFast_c_producer"));
    
    Kernel.cast_I->addMethod(list::domain(3,Generate._c_producer,Optimize._C_cast,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(cast_I_c_producer,"cast!_c_producer"));
    
    Generate.gc_protection_exp->addMethod(list::domain(5,Generate._c_producer,
      Language._Variable,
      Kernel._boolean,
      Kernel._any,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE,_function_(gc_protection_exp_c_producer,"gc_protection_exp_c_producer"));
    
    Generate.bag_expression->addMethod(list::domain(5,Generate._c_producer,
      Kernel._class,
      Kernel._bag,
      Kernel._type,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(bag_expression_c_producer,"bag_expression_c_producer"));
    
    Generate.generate_s_file->addMethod(list::domain(3,Kernel._string,Kernel._list,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(generate_s_file_string,"generate_s_file_string"));
    
    Generate.create_load_modules->addMethod(list::domain(4,Kernel._string,
      Kernel._port,
      Kernel._list,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(create_load_modules_string,"create_load_modules_string"));
    
    Generate.create_dynload_module->addMethod(list::domain(1,Kernel._module),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(create_dynload_module_module1,"create_dynload_module_module1"));
    
    Generate.methods_interface->addMethod(list::domain(2,Generate._c_producer,Kernel._class),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(methods_interface_c_producer,"methods_interface_c_producer"));
    
    Generate.methods_bodies->addMethod(list::domain(2,Generate._c_producer,Kernel._class),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(methods_bodies_c_producer,"methods_bodies_c_producer"));
    
    Generate.inline_exp->addMethod(list::domain(3,Generate._c_producer,Language._Call_method1,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(inline_exp_c_producer1,"inline_exp_c_producer1"));
    
    Generate.inline_exp->addMethod(list::domain(3,Generate._c_producer,Language._Call_method2,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(inline_exp_c_producer2,"inline_exp_c_producer2"));
    
    Generate.inline_exp->addMethod(list::domain(3,Generate._c_producer,Language._Call_method,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(inline_exp_c_producer3,"inline_exp_c_producer3"));
    
    Generate.print_external_call->addMethod(list::domain(3,Generate._c_producer,Language._Call_method,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(print_external_call_c_producer,"print_external_call_c_producer"));
    
    Generate.inline_exp->addMethod(list::domain(3,Generate._c_producer,Language._Call,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(inline_exp_c_producer5,"inline_exp_c_producer5"));
    
    { (Generate.fcall_ask = property::make("fcall?",3,Generate.it,Kernel._any,0));
      _void_(Generate.fcall_ask->open = 3);
      ;}
    
    { (Generate.fcall_exp = property::make("fcall_exp",3,Generate.it,Kernel._any,0));
      _void_(Generate.fcall_exp->open = 3);
      ;}
    
    GC_UNBIND;
{ global_variable * v60472 = (Generate.FCLimit = (global_variable *) Core._global_variable->instantiate("FCLimit",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = ((OID)3));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate.FCALLSTINKS = (global_variable *) Core._global_variable->instantiate("FCALLSTINKS",claire.it));
      _void_(v60472->range = Kernel._boolean);
      _void_(v60472->value = Kernel.cfalse);
      close_global_variable(v60472);
      }
    
    GC_BIND;
Generate.fcall_ask->addMethod(list::domain(1,Language._Call),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(fcall_ask_Call2_Generate,"fcall?_Call2_Generate"));
    
    Generate.get_restrictions->addMethod(list::domain(2,Language._Call,Kernel._list),param_I_class(Kernel._list,Kernel._method),
    	NEW_ALLOC,_function_(get_restrictions_Call2,"get_restrictions_Call2"));
    
    Generate.fcall_exp->addMethod(list::domain(2,Language._Call,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(fcall_exp_Call2_Generate,"fcall_exp_Call2_Generate"));
    
    Generate.c_sorted_arg->addMethod(list::domain(4,Kernel._any,
      Kernel._class,
      Kernel._any,
      Kernel._boolean),Kernel._void,
    	NEW_ALLOC,_function_(c_sorted_arg_any,"c_sorted_arg_any"));
    
    Generate.c_sorted_args->addMethod(list::domain(4,Language._Call,
      Kernel._list,
      Kernel._any,
      Kernel._boolean),Kernel._void,
    	NEW_ALLOC,_function_(c_sorted_args_Call,"c_sorted_args_Call"));
    
    Generate.bitvector_I->addMethod(list::domain(2,Generate._c_producer,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(bitvector_I_c_producer,"bitvector!_c_producer"));
    
    GC_UNBIND;
{ global_variable * v60472 = (Generate.bitvectorList = (global_variable *) Core._global_variable->instantiate("bitvectorList",Compile.it));
      _void_(v60472->range = Kernel.emptySet);
      _void_(v60472->value = _oid_(list::alloc(6,_string_(((char*)"NEW_ALLOC")),
        _string_(((char*)"BAG_UPDATE")),
        _string_(((char*)"SLOT_UPDATE")),
        _string_(((char*)"RETURN_ARG")),
        _string_(((char*)"SAFE_RESULT")),
        _string_(((char*)"SAFE_GC")))));
      close_global_variable(v60472);
      }
    
    GC_BIND;
Generate.bitvectorSum->addMethod(list::domain(1,Kernel._integer),Kernel._void,
    	0,_function_(bitvectorSum_integer,"bitvectorSum_integer"));
    
    Generate.signature_I->addMethod(list::domain(2,Generate._c_producer,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(signature_I_c_producer,"signature!_c_producer"));
    
    Generate.getC->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(getC_any,"getC_any"));
    
    Generate.gassign->addMethod(list::domain(3,Generate._c_producer,Language._Gassign,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(gassign_c_producer,"gassign_c_producer"));
    
    Generate.call_slot->addMethod(list::domain(3,Generate._c_producer,Language._Call_slot,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(call_slot_c_producer,"call_slot_c_producer"));
    
    Generate.call_table->addMethod(list::domain(3,Generate._c_producer,Language._Call_table,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(call_table_c_producer,"call_table_c_producer"));
    
    Generate.call_array->addMethod(list::domain(3,Generate._c_producer,Language._Call_array,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(call_array_c_producer,"call_array_c_producer"));
    
    GC_UNBIND;
{ global_variable * v60472 = (Generate._starin_store_star = (global_variable *) Core._global_variable->instantiate("*in_store*",claire.it));
      _void_(v60472->range = Kernel._boolean);
      _void_(v60472->value = Kernel.cfalse);
      close_global_variable(v60472);
      }
    
    GC_BIND;
Generate.update->addMethod(list::domain(3,Generate._c_producer,Language._Update,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(update_c_producer,"update_c_producer"));
    
    Generate.object_test->addMethod(list::domain(4,Generate._c_producer,
      Kernel._any,
      Kernel._boolean,
      Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(object_test_c_producer,"object_test_c_producer"));
    
    Generate.exp_to_protect->addMethod(list::domain(3,Generate._c_producer,Optimize._to_protect,Kernel._any),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(exp_to_protect_c_producer,"exp_to_protect_c_producer"));
    
    Generate.macro->addMethod(list::domain(1,Generate._c_producer),Kernel._void,
    	0,_function_(macro_c_producer,"macro_c_producer"));
    
    Generate.init_var->addMethod(list::domain(2,Generate._c_producer,Kernel._class),Kernel._void,
    	0,_function_(init_var_c_producer,"init_var_c_producer"));
    
    Generate.any_interface->addMethod(list::domain(1,Generate._c_producer),Kernel._void,
    	0,_function_(any_interface_c_producer,"any_interface_c_producer"));
    
    Generate.pointer_cast->addMethod(list::domain(2,Generate._c_producer,Kernel._class),Kernel._void,
    	0,_function_(pointer_cast_c_producer,"pointer_cast_c_producer"));
    
    Generate.exp_Assign->addMethod(list::domain(3,Generate._c_producer,Language._Assign,Kernel._any),Kernel._void,
    	NEW_ALLOC,_function_(exp_Assign_c_producer,"exp_Assign_c_producer"));
    
    Generate.stat_handle->addMethod(list::domain(4,Generate._c_producer,
      Language._Handle,
      Kernel._any,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(stat_handle_c_producer,"stat_handle_c_producer"));
    
    Generate.stat_construct->addMethod(list::domain(4,Generate._c_producer,
      Language._Construct,
      Kernel._any,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(stat_construct_c_producer,"stat_construct_c_producer"));
    
    Generate.stat_while->addMethod(list::domain(4,Generate._c_producer,
      Language._While,
      Kernel._any,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(stat_while_c_producer,"stat_while_c_producer"));
    
    Generate.stat_gassign->addMethod(list::domain(4,Generate._c_producer,
      Language._Gassign,
      Kernel._any,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(stat_gassign_c_producer,"stat_gassign_c_producer"));
    
    Generate.stat_for->addMethod(list::domain(4,Generate._c_producer,
      Language._For,
      Kernel._any,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(stat_for_c_producer,"stat_for_c_producer"));
    
    Generate.stat_iteration->addMethod(list::domain(4,Generate._c_producer,
      Language._Iteration,
      Kernel._any,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(stat_iteration_c_producer,"stat_iteration_c_producer"));
    
    Generate.stat_super->addMethod(list::domain(4,Generate._c_producer,
      Language._Super,
      Kernel._any,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(stat_super_c_producer,"stat_super_c_producer"));
    
    Generate.stat_let->addMethod(list::domain(4,Generate._c_producer,
      Language._Let,
      Kernel._any,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(stat_let_c_producer,"stat_let_c_producer"));
    
    GC_UNBIND;
{ global_variable * v60472 = (Generate.so_options = (global_variable *) Core._global_variable->instantiate("so_options",claire.it));
      _void_(v60472->range = Kernel._string);
      _void_(v60472->value = _string_(((char*)"")));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate.cxx_options = (global_variable *) Core._global_variable->instantiate("cxx_options",claire.it));
      _void_(v60472->range = Kernel._string);
      _void_(v60472->value = _string_(((char*)"")));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate.ld_options = (global_variable *) Core._global_variable->instantiate("ld_options",claire.it));
      _void_(v60472->range = Kernel._string);
      _void_(v60472->value = _string_(((char*)"")));
      close_global_variable(v60472);
      }
    
    GC_BIND;
Generate.external_I->addMethod(list::domain(1,Kernel._module),Kernel._string,
    	RETURN_ARG,_function_(external_I_module1,"external!_module1"));
    
    Generate.string2module->addMethod(list::domain(1,Kernel._string),Kernel._module,
    	0,_function_(string2module_string1,"string2module_string1"));
    
    GC_UNBIND;
{ global_variable * v60472 = (Generate.rCode = (global_variable *) Core._global_variable->instantiate("rCode",Generate.it));
      _void_(v60472->range = Kernel._boolean);
      _void_(v60472->value = Kernel.ctrue);
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._Zcm = (global_variable *) Core._global_variable->instantiate("%cm",Generate.it));
      _void_(v60472->range = Kernel._string);
      _void_(v60472->value = _string_(((char*)"")));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._Zcf = (global_variable *) Core._global_variable->instantiate("%cf",Generate.it));
      _void_(v60472->range = Kernel._string);
      _void_(v60472->value = _string_(((char*)"")));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._Zcxf = (global_variable *) Core._global_variable->instantiate("%cxf",Generate.it));
      _void_(v60472->range = Kernel._string);
      _void_(v60472->value = _string_(((char*)"")));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate.dblevel = (global_variable *) Core._global_variable->instantiate("dblevel",Generate.it));
      _void_(v60472->range = Kernel._integer);
      _void_(v60472->value = ((OID)1));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._Zout = (global_variable *) Core._global_variable->instantiate("%out",Generate.it));
      _void_(v60472->range = Kernel._string);
      _void_(v60472->value = _string_(((char*)"")));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._Zcj = (global_variable *) Core._global_variable->instantiate("%cj",Generate.it));
      _void_(v60472->range = Kernel._string);
      _void_(v60472->value = _string_(((char*)"")));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._Zsudo = (global_variable *) Core._global_variable->instantiate("%sudo",Generate.it));
      _void_(v60472->range = Kernel._boolean);
      _void_(v60472->value = Kernel.cfalse);
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._Zov = (global_variable *) Core._global_variable->instantiate("%ov",Generate.it));
      _void_(v60472->range = Kernel._boolean);
      _void_(v60472->value = Kernel.cfalse);
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._Zcls = (global_variable *) Core._global_variable->instantiate("%cls",Generate.it));
      _void_(v60472->range = Kernel._boolean);
      _void_(v60472->value = Kernel.cfalse);
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._Zcall = (global_variable *) Core._global_variable->instantiate("%call",Generate.it));
      _void_(v60472->range = Kernel._boolean);
      _void_(v60472->value = Kernel.cfalse);
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._Zexport = (global_variable *) Core._global_variable->instantiate("%export",Generate.it));
      _void_(v60472->range = Kernel._any);
      _void_(v60472->value = Kernel.cfalse);
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._Zboth = (global_variable *) Core._global_variable->instantiate("%both",Generate.it));
      _void_(v60472->range = Kernel._boolean);
      _void_(v60472->value = Kernel.cfalse);
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._Zpublish = (global_variable *) Core._global_variable->instantiate("%publish",Generate.it));
      _void_(v60472->range = Kernel._boolean);
      _void_(v60472->value = Kernel.cfalse);
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._Zsm = (global_variable *) Core._global_variable->instantiate("%sm",Generate.it));
      _void_(v60472->range = Kernel._string);
      _void_(v60472->value = _string_(((char*)"")));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._Zem = (global_variable *) Core._global_variable->instantiate("%em",Generate.it));
      _void_(v60472->range = Kernel._string);
      _void_(v60472->value = _string_(((char*)"")));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate.cppopts = (global_variable *) Core._global_variable->instantiate("cppopts",Generate.it));
      _void_(v60472->range = Kernel._string);
      _void_(v60472->value = _string_(((char*)"")));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate.linkopts = (global_variable *) Core._global_variable->instantiate("linkopts",Generate.it));
      _void_(v60472->range = Kernel._string);
      _void_(v60472->value = _string_(((char*)"")));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate.clevel = (global_variable *) Core._global_variable->instantiate("clevel",Generate.it));
      _void_(v60472->range = Kernel._integer);
      _void_(v60472->value = ((OID)1));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate._Zinit_ask = (global_variable *) Core._global_variable->instantiate("%init?",Generate.it));
      _void_(v60472->range = Kernel._boolean);
      _void_(v60472->value = Kernel.ctrue);
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate.vlevel = (global_variable *) Core._global_variable->instantiate("vlevel",Generate.it));
      _void_(v60472->range = Kernel._integer);
      _void_(v60472->value = ((OID)2));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate.slevel = (global_variable *) Core._global_variable->instantiate("slevel",Generate.it));
      _void_(v60472->range = Kernel._integer);
      _void_(v60472->value = ((OID)0));
      close_global_variable(v60472);
      }
    
    { global_variable * v60472 = (Generate.clcc_ask = (global_variable *) Core._global_variable->instantiate("clcc?",Generate.it));
      _void_(v60472->range = Kernel._boolean);
      _void_(v60472->value = Kernel.ctrue);
      close_global_variable(v60472);
      }
    
    GC_BIND;
Generate.home_path->addMethod(list::domain(1,Kernel._void),Kernel._string,
    	NEW_ALLOC,_function_(home_path_void1,"home_path_void1"));
    
    Generate.function_compile->addMethod(list::domain(2,Kernel._string,Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(function_compile_string1,"function_compile_string1"));
    
    Generate.libpath->addMethod(list::domain(1,Kernel._void),Kernel._string,
    	NEW_ALLOC+RETURN_ARG,_function_(libpath_void1,"libpath_void1"));
    
    Generate.libpath_I->addMethod(list::domain(1,Kernel._module),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE,_function_(libpath_I_module1,"libpath!_module1"));
    
    Generate.headers_I->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE,_function_(headers_I_void1,"headers!_void1"));
    
    Generate.lib_I->addMethod(list::domain(2,Kernel._any,Kernel._list),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE,_function_(lib_I_any1,"lib!_any1"));
    
    Generate.importlib_I->addMethod(list::domain(2,Kernel._any,Kernel._list),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE,_function_(importlib_I_any1,"importlib!_any1"));
    
    Generate.files_I->addMethod(list::domain(3,Kernel._any,Kernel._boolean,Kernel._string),Kernel._void,
    	NEW_ALLOC,_function_(files_I_any1,"files!_any1"));
    
    Generate.job_option->addMethod(list::domain(1,Kernel._void),Kernel._string,
    	NEW_ALLOC,_function_(job_option_void1,"job_option_void1"));
    
    Generate.cmakefile->addMethod(list::domain(2,Kernel._any,Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(cmakefile_any1,"cmakefile_any1"));
    
    Generate.create_makefile_nt->addMethod(list::domain(3,Kernel._any,Kernel._string,Kernel._list),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(create_makefile_nt_any1,"create_makefile_nt_any1"));
    
    Generate.create_makefile_unix->addMethod(list::domain(3,Kernel._any,Kernel._string,Kernel._list),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(create_makefile_unix_any1,"create_makefile_unix_any1"));
    
    Generate.ensure_module_directories_exist->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC,_function_(ensure_module_directories_exist_void1,"ensure_module_directories_exist_void1"));
    
    Generate.new_module->addMethod(list::domain(1,GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(new_module_list1,"new_module_list1"));
    
    Generate.rcopy->addMethod(list::domain(2,Kernel._string,Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(rcopy_string1,"rcopy_string1"));
    
    Generate.export_module->addMethod(list::domain(1,Kernel._boolean),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(export_module_boolean1,"export_module_boolean1"));
    
    Generate.relayed_params->addMethod(list::domain(1,Kernel._void),Kernel._string,
    	NEW_ALLOC+RETURN_ARG,_function_(relayed_params_void1,"relayed_params_void1"));
    
    Generate.compile_module_libs->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(compile_module_libs_void1,"compile_module_libs_void1"));
    
    Generate.compile_all_module_libs->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(compile_all_module_libs_void1,"compile_all_module_libs_void1"));
    
    Generate.module_list->addMethod(list::domain(1,GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(module_list_list1,"module_list_list1"));
    
    Generate.module_info->addMethod(list::domain(1,GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(module_info_list1,"module_info_list1"));
    
    Generate.list_fcall->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(list_fcall_void1,"list_fcall_void1"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-env")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string16_Generate,"option_usage_string16_Generate"),
    _function_(option_usage_string16_Generate_,"option_usage_string16_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-env"))),Kernel._list),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE,_function_(option_respond_string15_Generate,"option_respond_string15_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,2,_string_(((char*)"-l")),_string_(((char*)"-m")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string17_Generate,"option_usage_string17_Generate"),
    _function_(option_usage_string17_Generate_,"option_usage_string17_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,2,_string_(((char*)"-l")),_string_(((char*)"-m"))),Kernel._list),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(option_respond_string16_Generate,"option_respond_string16_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-od")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string18_Generate,"option_usage_string18_Generate"),
    _function_(option_usage_string18_Generate_,"option_usage_string18_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-od"))),Kernel._list),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE,_function_(option_respond_string17_Generate,"option_respond_string17_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,2,_string_(((char*)"-os")),_string_(((char*)"-safe")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string19_Generate,"option_usage_string19_Generate"),
    _function_(option_usage_string19_Generate_,"option_usage_string19_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-safe"))),Kernel._list),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(option_respond_string18_Generate,"option_respond_string18_Generate"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-os"))),Kernel._list),Kernel._void,
    	NEW_ALLOC,_function_(option_respond_string19_Generate,"option_respond_string19_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-o")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string20_Generate,"option_usage_string20_Generate"),
    _function_(option_usage_string20_Generate_,"option_usage_string20_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-o"))),Kernel._list),Kernel._void,
    	NEW_ALLOC,_function_(option_respond_string20_Generate,"option_respond_string20_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,2,_string_(((char*)"-O")),_string_(((char*)"-D")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string21_Generate,"option_usage_string21_Generate"),
    _function_(option_usage_string21_Generate_,"option_usage_string21_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-D"))),Kernel._list),Kernel._void,
    	0,_function_(option_respond_string21_Generate,"option_respond_string21_Generate"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-O"))),Kernel._list),Kernel._void,
    	SLOT_UPDATE,_function_(option_respond_string22_Generate,"option_respond_string22_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-p")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string22_Generate,"option_usage_string22_Generate"),
    _function_(option_usage_string22_Generate_,"option_usage_string22_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-p"))),Kernel._list),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(option_respond_string24_Generate,"option_respond_string24_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,3,_string_(((char*)"-make")),
      _string_(((char*)"-link")),
      _string_(((char*)"-cpp")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string23_Generate,"option_usage_string23_Generate"),
    _function_(option_usage_string23_Generate_,"option_usage_string23_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-cpp"))),Kernel._list),Kernel._void,
    	NEW_ALLOC,_function_(option_respond_string25_Generate,"option_respond_string25_Generate"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-make"))),Kernel._list),Kernel._void,
    	NEW_ALLOC,_function_(option_respond_string43_Generate,"option_respond_string43_Generate"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-link"))),Kernel._list),Kernel._void,
    	NEW_ALLOC,_function_(option_respond_string26_Generate,"option_respond_string26_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,3,_string_(((char*)"-cl")),
      _string_(((char*)"-cc")),
      _string_(((char*)"-cm")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string24_Generate,"option_usage_string24_Generate"),
    _function_(option_usage_string24_Generate_,"option_usage_string24_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,3,_string_(((char*)"-cl")),
      _string_(((char*)"-cc")),
      _string_(((char*)"-cm"))),Kernel._list),Kernel._void,
    	NEW_ALLOC,_function_(option_respond_string27_Generate,"option_respond_string27_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,5,_string_(((char*)"-em")),
      _string_(((char*)"-sm")),
      _string_(((char*)"-call")),
      _string_(((char*)"-cls")),
      _string_(((char*)"-both")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string33_Generate,"option_usage_string33_Generate"),
    _function_(option_usage_string33_Generate_,"option_usage_string33_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-both"))),Kernel._list),Kernel._void,
    	0,_function_(option_respond_string28_Generate,"option_respond_string28_Generate"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-cls"))),Kernel._list),Kernel._void,
    	0,_function_(option_respond_string29_Generate,"option_respond_string29_Generate"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-call"))),Kernel._list),Kernel._void,
    	0,_function_(option_respond_string30_Generate,"option_respond_string30_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,4,_string_(((char*)"-export")),
      _string_(((char*)"-publish")),
      _string_(((char*)"-ov")),
      _string_(((char*)"-sudo")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string26_Generate,"option_usage_string26_Generate"),
    _function_(option_usage_string26_Generate_,"option_usage_string26_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-sudo"))),Kernel._list),Kernel._void,
    	0,_function_(option_respond_string31_Generate,"option_respond_string31_Generate"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-ov"))),Kernel._list),Kernel._void,
    	0,_function_(option_respond_string32_Generate,"option_respond_string32_Generate"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-publish"))),Kernel._list),Kernel._void,
    	0,_function_(option_respond_string33_Generate,"option_respond_string33_Generate"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-sm"))),Kernel._list),Kernel._void,
    	NEW_ALLOC,_function_(option_respond_string42_Generate,"option_respond_string42_Generate"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-em"))),Kernel._list),Kernel._void,
    	NEW_ALLOC,_function_(option_respond_string44_Generate,"option_respond_string44_Generate"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-export"))),Kernel._list),Kernel._void,
    	NEW_ALLOC,_function_(option_respond_string34_Generate,"option_respond_string34_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-nm")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string27_Generate,"option_usage_string27_Generate"),
    _function_(option_usage_string27_Generate_,"option_usage_string27_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-nm"))),Kernel._list),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(option_respond_string35_Generate,"option_respond_string35_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,2,_string_(((char*)"-mi")),_string_(((char*)"-ml")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string28_Generate,"option_usage_string28_Generate"),
    _function_(option_usage_string28_Generate_,"option_usage_string28_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-ml"))),GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(option_respond_string36_Generate,"option_respond_string36_Generate"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-mi"))),GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(option_respond_string37_Generate,"option_respond_string37_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-cx")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string29_Generate,"option_usage_string29_Generate"),
    _function_(option_usage_string29_Generate_,"option_usage_string29_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-cx"))),Kernel._list),Kernel._void,
    	NEW_ALLOC,_function_(option_respond_string38_Generate,"option_respond_string38_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-n")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string30_Generate,"option_usage_string30_Generate"),
    _function_(option_usage_string30_Generate_,"option_usage_string30_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-n"))),Kernel._list),Kernel._void,
    	0,_function_(option_respond_string39_Generate,"option_respond_string39_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-fcall")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string31_Generate,"option_usage_string31_Generate"),
    _function_(option_usage_string31_Generate_,"option_usage_string31_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-fcall"))),Kernel._list),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(option_respond_string40_Generate,"option_respond_string40_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,2,_string_(((char*)"wclConsole")),_string_(((char*)"-noConsole")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string32_Generate,"option_usage_string32_Generate"),
    _function_(option_usage_string32_Generate_,"option_usage_string32_Generate_"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,2,_string_(((char*)"-wclConsole")),_string_(((char*)"-noConsole"))),Kernel._list),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(option_respond_string41_Generate,"option_respond_string41_Generate"));
    
    Core.option_parsed->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(option_parsed_void2_Generate,"option_parsed_void2_Generate"));
    
    Core.option_respond->addMethod(list::domain(2,set::alloc(Kernel.emptySet,1,_string_(((char*)"-skipcl"))),GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	0,_function_(option_respond_string57_Generate,"option_respond_string57_Generate"));
    
    Core.option_usage->addFloatMethod(list::domain(1,set::alloc(Kernel.emptySet,1,_string_(((char*)"-skipcl")))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string37_Generate,"option_usage_string37_Generate"),
    _function_(option_usage_string37_Generate_,"option_usage_string37_Generate_"));
    GC_UNBIND;

    }
  
  
