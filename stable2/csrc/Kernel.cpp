/***********************************************************************/
/**   microCLAIRE                                       Yves Caseau    */
/**   Kernel.cpp pp                                                    */
/**  Copyright (C) 1998-2003 Yves Caseau. All Rights Reserved.         */
/**  cf claire.h                                                       */
/***********************************************************************/

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllexport)
#endif
#include <claire.h>
#include <Kernel.h>
#include <marie.h>
#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllimport)
#endif
#include <Core.h>
#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllexport)
#endif

// create the namespace
CL_EXPORT KernelClass Kernel;
CL_EXPORT NameSpace claire;
CL_EXPORT NameSpace mClaire;
CL_EXPORT ClaireBoolean *CTRUE = (ClaireBoolean *) 1;    // v3.2.04
CL_EXPORT ClaireBoolean *CFALSE = (ClaireBoolean *) 0;
CL_EXPORT OID CNULL;

CL_EXPORT ClaireResource *ClRes;
CL_EXPORT ClaireEnvironment *ClEnv;

CL_EXPORT ClaireClass* Kernel_integer;

CL_EXPORT CL_INT no_exit_call = 0;

static fpLoadModule fLoadModules = NULL;
void CL_EXPORT set_load_module(fpLoadModule func) {
  fLoadModules = func;
}

static fpClaireStarted fClaireStarted = NULL;
void CL_EXPORT set_claire_started(fpClaireStarted func) {
  fClaireStarted = func;
}

static fpCallMain fCallMain = NULL;
void CL_EXPORT set_call_main(fpCallMain func) {
  fCallMain = func;
}

static fpServiceFunc fServiceFunc = NULL;
void CL_EXPORT set_service_func(fpServiceFunc func) {
  fServiceFunc = func;
}

CL_EXPORT fp_interpreter_insert_text interpreter_insert_text;
CL_EXPORT fp_interpreter_delete_text interpreter_delete_text;
CL_EXPORT fp_interpreter_reset_state interpreter_reset_state;
CL_EXPORT fp_interpreter_get_text interpreter_get_text;
CL_EXPORT fp_interpreter_get_cursor_position interpreter_get_cursor_position;
CL_EXPORT fp_interpreter_display_list interpreter_display_list;

CL_EXPORT void default_main() {
}

// --------------------------------------------------------------
// this file contains the meta-description of the Kernel module
// ---------------------------------------------------------------

/*********************************************************************/
/** Contents                                                         */
/**    1. Bootstrap                                                  */
/**    2. metaLoad                                                   */
/*********************************************************************/


/*********************************************************************/
/**    1. Bootstrap                                                  */
/*********************************************************************/


// this is the bootstraping kernel ====================================================
// handcrafted ...


void KernelClass::bootstrap()
{_freeable_object = 0;
 CTRUE = (ClaireBoolean *) ClAlloc->makeAny(4);
 CFALSE = (ClaireBoolean *) ClAlloc->makeAny(4);
 CNULL = _oid_(ClAlloc->makeAny(4));
 ctrue = _oid_(CTRUE);
 cfalse = _oid_(CFALSE);
 NoDefault = (thing *) ClAlloc->makeAny(4);
 emptySet = set::empty();
 emptySet->of = emptySet;
 nil = list::empty();
 nil->of = emptySet;

 _integer = NULL;
 Kernel_integer = NULL;
 _float = NULL;

 // step 1 : define the object shells
 _class =  (ClaireClass *) ClAlloc->makeStatic(sizeof(ClaireClass) / sizeof(void*));  // creates the 3 most basic class templates
 _set =  (ClaireClass *) ClAlloc->makeStatic(sizeof(ClaireClass) / sizeof(void*));
 _list =  (ClaireClass *) ClAlloc->makeStatic(sizeof(ClaireClass) / sizeof(void*));
 _class = ClaireClass::make(_class);              // now we can call make
 _class->comment = "class";
 _class->isa = _class;
 
 _symbol = ClaireClass::make(ClAlloc->makeStatic(sizeof(ClaireClass) / sizeof(void*)));
 _module = ClaireClass::make(ClAlloc->makeStatic(sizeof(ClaireClass) / sizeof(void*)));
 _module->comment = "module";
 _list = ClaireClass::make(_list);
 _set = ClaireClass::make(_set);
 emptySet->isa = _set;
 claire.it = (module *) _module->instantiate(13); //<sb> + version in XL claire
 mClaire.it = (module *) _module->instantiate(13); //<sb> + version in XL claire
 it = (module *) _module->instantiate(13 + 4); //<sb> + version in XL claire
 ClEnv->module_I = it;
 claire.it->part_of = NULL;
 claire.it->parts = list::alloc(1,_oid_(mClaire.it));
 claire.it->version = NULL; //<sb>
 claire.it->external = NULL; //<sb>
 claire.it->evaluate = NULL; //<sb>
 claire.it->source = NULL; //<sb>
 claire.it->status = 3;
 claire.it->comment = "claire";
 claire.it->made_of = list::empty();
 claire.it->uses = list::empty();
 claire.it->verbose = ctrue;
 mClaire.it->part_of = claire.it;
 mClaire.it->parts = list::alloc(1,_oid_(it));
 mClaire.it->status = 3;
 mClaire.it->comment = "mClaire";
 mClaire.it->made_of = list::empty();
 mClaire.it->uses = list::empty();
 mClaire.it->version = NULL; //<sb>
 mClaire.it->external = NULL; //<sb>
 mClaire.it->evaluate = NULL; //<sb>
 mClaire.it->source = NULL; //<sb>
 mClaire.it->verbose = ctrue;
 it->uses = list::empty();
 it->parts = list::empty();
 it->part_of = mClaire.it;
 it->status = 3;
 it->made_of = list::empty();
 it->comment = "Kernel";
 it->version = NULL; //<sb>
 it->external = NULL; //<sb>
 it->evaluate = NULL; //<sb>
 it->source = NULL; //<sb>
 it->verbose = ctrue;
 _class->instances = list::domain(5,_class,_symbol,_module,_set,_list);
 // step 2: define the symbols
 _class->name = symbol::make("class",claire.it,it);
 _list->name = symbol::make("list",claire.it,it);
 _set->name = symbol::make("set",claire.it,it);
 _symbol->name = symbol::make("symbol",claire.it,it);
 _module->name = symbol::make("module",claire.it,it);
 claire.it->name = symbol::make("claire",claire.it,claire.it);
 Kernel.it->name = symbol::make("Kernel",claire.it,claire.it);
 mClaire.it->name = symbol::make("mClaire",claire.it,claire.it);
 NoDefault->name = symbol::make("NoDefault",it,it);
 symbol::make("true",claire.it,claire.it)->value = _oid_(CTRUE);
 symbol::make("false",claire.it,claire.it)->value = _oid_(CFALSE);
 unknownName = symbol::make("unknown",claire.it,claire.it);
 unknownName->value = CNULL;
 PRIVATE = symbol::make("private",claire.it,claire.it);
 PRIVATE->value = _oid_(PRIVATE);
 _class->name->value = _oid_(_class);
 _list->name->value = _oid_(_list);
 _set->name->value = _oid_(_set);
 _symbol->name->value = _oid_(_symbol);
 _module->name->value = _oid_(_module);
 claire.it->name->value = _oid_(claire.it);
 Kernel.it->name->value = _oid_(Kernel.it);
 mClaire.it->name->value = _oid_(mClaire.it);
 NoDefault->name->value = _oid_(NoDefault);
 Kernel.nil->isa = _list;
 Kernel.emptySet->isa = _set;
 // step 3: we can now create a few class templates
 _property = ClaireClass::make("property");
 _restriction = ClaireClass::make("restriction");
 _slot = ClaireClass::make("slot");
 _any = ClaireClass::make("any");
 _type = ClaireClass::make("type");
 _float = ClaireClass::make("float");          // used in methods
// _void = ClaireClass::make("void");
 OBJECT(ClaireAny,CNULL)->isa = _any;
 _void = ClaireClass::make("void");
 _boolean = ClaireClass::make("boolean");
    CTRUE->isa = _boolean;
    CFALSE->isa = _boolean;

 // step 4: now we can build prototypes
 // isa/name/comment/slot/sclass/sub/ances/desc/eval/open/inst/proto/par/code/dict
 _class->prototype = list::alloc(18, 0, 0, 0, _oid_(list::empty(_slot)), 0ll,
                                 _oid_(set::empty(_class)),
                                 _oid_(list::empty(_class)),_oid_(set::empty(_class)),
                                 0ll,2ll,_oid_(list::empty()),_oid_(list::empty()),
                                 _oid_(list::empty()),0ll,_oid_(list::empty()),
                                 _oid_(CTRUE),CNULL,_oid_(list::empty()));
 _class->ancestors = list::alloc(1,_oid_(_class));

  // JUST CHANGED in v3.0.54 ! was :
  // _class->ancestors = list::alloc(3,_oid_(_class),1,_oid_(_class));
  // isa/name/comment/dom/ran/ifwrite/store/inv/open/multi/trace/restric/defini/dict/
  
 _property->prototype =  list::alloc(16, 0, 0, 0, _oid_(_any), _oid_(_any), CNULL, _oid_(CFALSE),
                                 0ll, 2ll, _oid_(CFALSE), 0ll, _oid_(list::empty(_restriction)),
                                _oid_(list::empty(_restriction)),_oid_(list::empty()),
                                _oid_(CFALSE), 0ll);
 // isa/module/comment/dom/range/select/srange/default/index

 // step5: this is the first set of properties
 isa = property::make("isa",ClEnv->close,claire.it);
 name = property::make("name",ClEnv->close,claire.it);
 sname = property::make("sname",ClEnv->close,claire.it);
 comment = property::make("comment",claire.it);
 slots = property::make("slots",ClEnv->close,claire.it);
 superclass = property::make("superclass",ClEnv->close,claire.it);
 subclass = property::make("subclass",ClEnv->close,claire.it);
 ancestors = property::make("ancestors",ClEnv->close,claire.it);
 descendents = property::make("descendents",ClEnv->close,claire.it);
// open = property::make("open",ClEnv->close,claire.it);
 instances = property::make("instances",ClEnv->close,claire.it);
 prototype = property::make("prototype",ClEnv->close,mClaire.it);
 params = property::make("params",ClEnv->close,claire.it);
 code = property::make("code",ClEnv->close,claire.it);
 ident_ask = property::make("ident?",claire.it);
 dictionary = property::make("dictionary",ClEnv->close,mClaire.it);
 dispatcher = property::make("dispatcher",ClEnv->close,mClaire.it);
 reified = property::make("reified",claire.it);
 graph = property::make("graph",ClEnv->close,mClaire.it);
 domain = property::make("domain",ClEnv->close,claire.it);
 range = property::make("range",ClEnv->close,claire.it);
 selector = property::make("selector",ClEnv->close,claire.it);
 srange = property::make("srange",ClEnv->close,mClaire.it);
 trace_I = property::make("trace!",it);
 restrictions = property::make("restrictions",ClEnv->close,claire.it);
 definition = property::make("definition",ClEnv->close,mClaire.it);
 inverse = property::make("inverse",claire.it);
 index = property::make("index",ClEnv->close,mClaire.it);
 cerr = property::make("cerr",ClEnv->close,mClaire.it); //<sb> -> map C library error code in system_error
 base = property::make("base",ClEnv->close,mClaire.it);
 debug_I = property::make("debug!",mClaire.it);
 module_I = property::make("module!",claire.it);
 evaluate = property::make("evaluate",mClaire.it);
 formula = property::make("formula",claire.it);
 typing = property::make("typing",it);
 body = property::make("body",claire.it);
 if_write = property::make("if_write",claire.it);
 store_ask = property::make("store?",claire.it);
 multivalued_ask = property::make("multivalued?",claire.it);
 arg = property::make("arg",claire.it);
 value = property::make("value",claire.it);
 functional = property::make("functional",claire.it);
 precedence = property::make("precedence",claire.it);
 status = property::make("status",mClaire.it);
 parts = property::make("parts",claire.it);
 part_of = property::make("part_of",claire.it);
 made_of = property::make("made_of",claire.it);
 source = property::make("source",claire.it);
 uses = property::make("uses",claire.it);
 inline_ask = property::make("inline?",claire.it);
 verbose = property::make("verbose",claire.it);
 exception_I = property::make("exception!",claire.it);
 trace_I = property::make("trace!",claire.it);
 step_I = property::make("step!",claire.it);
 spy_I = property::make("spy!",claire.it); 
 close = property::make("close",claire.it);
 ABSTRACT = property::make("abstract",claire.it);
 FINAL = property::make("final",claire.it);
 DEFAULT = property::make("default",claire.it);
 open = property::make("open",claire.it);
 ephemeral = property::make("ephemeral",claire.it);
 cout = property::make("cout",claire.it);
 ctrace = property::make("ctrace",claire.it);
 last_debug = property::make("last_debug",it);
 last_index = property::make("last_index",it);
 last_trace = property::make("last_trace",it);
 count_call = property::make("count_call",mClaire.it);
 count_level = property::make("count_level",mClaire.it);
 count_trigger = property::make("count_trigger",mClaire.it);
 version = property::make("version",claire.it);
 external = property::make("external",claire.it);
 freeme_ask =  property::make("freeme?",mClaire.it); //<sb>
 imported =   property::make("imported",mClaire.it); //<sb>
 
// step6: this is the first set of classes [we do the root, void, by hand]
//_void = ClaireClass::make("void");   already done
    _void->superclass = NULL;
    _void->ancestors = list::empty(_class)->addFast(_oid_(_void));
    _void->descendents = set::empty(_class)->addFast(_oid_(_void));
    _void->prototype = list::empty();
    //_void->code = 0;

_any = ClaireClass::make("any",_void,claire.it);
_integer = ClaireClass::make("integer",_any,claire.it);
Kernel_integer = _integer;
_object = ClaireClass::make("object",_any,claire.it);
   CL_ADDSLOT(_object,ClaireObject,isa,_class,CNULL);
// primitive
_primitive = ClaireClass::make("primitive",_any,claire.it);
_cl_import = ClaireClass::make("import",_primitive,claire.it);
_float = ClaireClass::make("float",_primitive,claire.it);
_string = ClaireClass::make("string",_primitive,claire.it);
_array = ClaireClass::make("array",_primitive,claire.it);



// _function = ClaireClass::make("function",_primitive,claire.it);
//_imported_port = ClaireClass::make("imported_port",_cl_import,mClaire.it); //<sb> made port freeable

// objects
_system_object = ClaireClass::make("system_object",_object,claire.it);
_symbol = ClaireClass::make("symbol",_system_object,claire.it);
   CL_ADDSLOT(_symbol,symbol,name,_string,CNULL);       // char* part      m1/toto -> "toto"
   CL_ADDSLOT(_symbol,symbol,module_I,_module,CNULL);   // the name space  m1/toto -> m1
   CL_ADDSLOT(_symbol,symbol,definition,_module,CNULL); // where the symbol is defined (NULL => PRIVATE)
   CL_ADDSLOT(_symbol,symbol,value,_any,CNULL);         // the "content" of the symbol

_function = ClaireClass::make("function",_system_object,claire.it);

_freeable_object = ClaireClass::make("freeable_object",_object,claire.it);
   CL_ADDSLOT(_freeable_object,FreeableObject,freeme_ask,_boolean,cfalse);

_freeable_object->open = 4; //<sb> special: seen as ephemeral but also added to instances

//<sb> port hierarchy :

_port = ClaireClass::make("port",_freeable_object,claire.it); //<sb> made port freeable
//   CL_ADD_SLOT(_port,PortObject,closed_ask,closed_ask,_boolean,cfalse);
   
// collections .....
_collection = ClaireClass::make("collection",_object,claire.it);
_type = ClaireClass::make("type",_collection,claire.it);
_bag = ClaireClass::make("bag",_type,claire.it);
_list = ClaireClass::make("list",_bag,claire.it);
_listargs = ClaireClass::make("listargs",_list,claire.it);
_set = ClaireClass::make("set",_bag,claire.it);
_tuple = ClaireClass::make("tuple",_bag,claire.it);
   _list->ident_ask = CFALSE;
   _set->ident_ask = CFALSE;
   _tuple->ident_ask = CFALSE;
_class = ClaireClass::make("class",_type,claire.it);
    CL_ADDSLOT(_class,ClaireClass,name,_symbol,CNULL);
    CL_ADDSLOT(_class,ClaireClass,comment,_string,CNULL);
    CL_ADDSLOT(_class,ClaireClass,slots,_list,_oid_(list::empty(_slot)));
    CL_ADDSLOT(_class,ClaireClass,superclass,_class,CNULL);
    CL_ADDSLOT(_class,ClaireClass,subclass,_set,_oid_(set::empty(_class)));
    CL_ADDSLOT(_class,ClaireClass,ancestors,_list,_oid_(list::empty(_class)));
    CL_ADDSLOT(_class,ClaireClass,descendents,_set,_oid_(set::empty(_class)));
    CL_ADDSLOT(_class,ClaireClass,evaluate,_function,CNULL);
    CL_ADDSLOT(_class,ClaireClass,open,_integer,2);
    CL_ADDSLOT(_class,ClaireClass,instances,_list,_oid_(list::empty()));
    CL_ADDSLOT(_class,ClaireClass,prototype,_list,_oid_(list::empty()));
    CL_ADDSLOT(_class,ClaireClass,params,_list,_oid_(list::empty()));
    CL_ADDSLOT(_class,ClaireClass,dictionary,_list,_oid_(list::empty()));
    CL_ADDSLOT(_class,ClaireClass,ident_ask,_boolean,_oid_(CTRUE));
    CL_ADDSLOT(_class,ClaireClass,if_write,_any,CNULL);
    CL_ADDSLOT(_class,ClaireClass,dispatcher,_object,_oid_(list::empty()));
//    CL_ADDSLOT(_class,ClaireClass,code,_integer,0);
params->multivalued_ask = CFALSE;
dictionary->multivalued_ask = CFALSE;

UNAMED = symbol::make("unamed",claire.it,claire.it);
//see("class prototype",_oid_(_class->prototype),1);
_thing = ClaireClass::make("thing",_object,claire.it);
    CL_ADDSLOT(_thing,thing,name,_symbol,_oid_(UNAMED)); // CNULL);
    NoDefault->isa = _thing;

_system_thing = ClaireClass::make("system_thing",_thing,claire.it);
_boolean      = ClaireClass::make("boolean",_system_object,claire.it);
        _boolean->instances = list::alloc(2,_oid_(CTRUE),_oid_(CFALSE));

_restriction = ClaireClass::make("restriction",_system_object,claire.it);
    CL_ADDSLOT(_restriction,restriction,module_I,_module,CNULL);
    CL_ADDSLOT(_restriction,restriction,comment,_string,CNULL);
    CL_ADDSLOT(_restriction,restriction,domain,_list,_oid_(list::empty(_type)));
    CL_ADDSLOT(_restriction,restriction,range,_type,_oid_(_any));
    CL_ADDSLOT(_restriction,restriction,selector,_property,CNULL);
 //   _restriction,X,srange,_class,CNULL);
domain->multivalued_ask = CFALSE;
_slot = ClaireClass::make("slot",_restriction,claire.it);
    CL_ADDSLOT(_slot,slot,srange,_class,CNULL);
    CL_ADDSLOT(_slot,slot,DEFAULT,_any,CNULL);
    CL_ADDSLOT(_slot,slot,index,_integer,0);
_method = ClaireClass::make("method",_restriction,claire.it);
     CL_ADDSLOT(_method,method,srange,_list,_oid_(list::empty(_type)));
     CL_ADDSLOT(_method,method,formula,_object,CNULL);
     CL_ADDSLOT(_method,method,functional,_function,CNULL);
     CL_ADDSLOT(_method,method,evaluate,_function,CNULL);
     CL_ADDSLOT(_method,method,typing,_any,CNULL);
     CL_ADDSLOT(_method,method,status,_integer,0);
     CL_ADDSLOT(_method,method,inline_ask,_boolean,_oid_(CFALSE));
_char =  ClaireClass::make("char",_system_object,claire.it);
ClaireChar::init();
_relation = ClaireClass::make("relation",_system_thing,claire.it);
    CL_ADDSLOT(_relation,ClaireRelation,comment,_string,CNULL);
    CL_ADDSLOT(_relation,ClaireRelation,domain,_type,_oid_(_any));
    CL_ADDSLOT(_relation,ClaireRelation,range,_type,_oid_(_any));
    CL_ADDSLOT(_relation,ClaireRelation,if_write,_any,CNULL);
    CL_ADDSLOT(_relation,ClaireRelation,store_ask,_boolean,_oid_(CFALSE));
    CL_ADDSLOT(_relation,ClaireRelation,inverse,_relation,CNULL);
    CL_ADDSLOT(_relation,ClaireRelation,open,_integer,2);
    CL_ADDSLOT(_relation,ClaireRelation,multivalued_ask,_object,_oid_(CFALSE)); // an interesting situation ...
_property = ClaireClass::make("property",_relation,claire.it);
    CL_ADDSLOT(_property,property,trace_I,_integer,0);
    CL_ADDSLOT(_property,property,restrictions,_list,_oid_(list::empty(_restriction)));
    CL_ADDSLOT(_property,property,definition,_list,_oid_(list::empty(_restriction)));
 //   CL_ADDSLOT(_property,property,dictionary,_object,_oid_(list::empty()));
    CL_ADDSLOT(_property,property,dictionary,_boolean,_oid_(CFALSE));         // v3.2.58 cleanup
    CL_ADDSLOT(_property,property,reified,_object,_oid_(CFALSE));
    CL_ADDSLOT(_property,property,dispatcher,_integer,0);
_operation = ClaireClass::make("operation",_property,claire.it);
    CL_ADDSLOT(_operation,operation,precedence,_integer,0);
_table = ClaireClass::make("table",_relation,claire.it);
    CL_ADDSLOT(_table,table,graph,_bag,CNULL);
    CL_ADDSLOT(_table,table,params,_any,CNULL);
    CL_ADDSLOT(_table,table,DEFAULT,_any,CNULL);
_module = ClaireClass::make("module",_system_thing,claire.it);
    CL_ADDSLOT(_module,module,comment,_string,CNULL);
    CL_ADDSLOT(_module,module,parts,_list,_oid_(list::empty(_module)));
    CL_ADDSLOT(_module,module,part_of,_module,_oid_(claire.it));   // v2.9
    CL_ADDSLOT(_module,module,uses,_list,_oid_(list::empty(_module)));

    CL_ADDSLOT(_module,module,source,_string,_string_(""));

    CL_ADDSLOT(_module,module,made_of,_list,_oid_(list::empty(_string)));
    CL_ADDSLOT(_module,module,status,_integer,0);
    CL_ADDSLOT(_module,module,evaluate,_function,CNULL);
    CL_ADDSLOT(_module,module,external,_string,CNULL);
    CL_ADDSLOT(_module,module,version,_string,CNULL);
    CL_ADDSLOT(_module,module,verbose,_any,_oid_(CTRUE)); //<sb> v3.3.33
_exception = ClaireClass::make("exception",_system_object,claire.it);
_error = ClaireClass::make("error",_exception,claire.it);
_system_error = ClaireClass::make("system_error",_error,claire.it);     // v3.0.54
    CL_ADDSLOT(_system_error,system_error,index,_integer,0);
    CL_ADDSLOT(_system_error,system_error,value,_any,0);
    CL_ADDSLOT(_system_error,system_error,arg,_any,0);
  CL_ADDSLOT(_system_error,system_error,cerr,_integer,0);

_environment = ClaireClass::make("environment",_system_object,claire.it);
        CL_ADDSLOT(_environment,ClaireEnvironment,verbose,_integer,0);
        CL_ADDSLOT(_environment,ClaireEnvironment,exception_I,_exception,0);
        CL_ADDSLOT(_environment,ClaireEnvironment,module_I,_module,0);
        CL_ADDSLOT(_environment,ClaireEnvironment,name,_string,CNULL);
        CL_ADDSLOT(_environment,ClaireEnvironment,version,_float,_float_(0.0));
        CL_ADDSLOT(_environment,ClaireEnvironment,ctrace,_port,0);
        CL_ADDSLOT(_environment,ClaireEnvironment,cout,_port,0);
        CL_ADDSLOT(_environment,ClaireEnvironment,index,_integer,0);
        CL_ADDSLOT(_environment,ClaireEnvironment,base,_integer,0);
        CL_ADDSLOT(_environment,ClaireEnvironment,debug_I,_integer,(OID)-1);
        CL_ADDSLOT(_environment,ClaireEnvironment,trace_I,_integer,0);
        CL_ADDSLOT(_environment,ClaireEnvironment,step_I,_integer,0);
        CL_ADDSLOT(_environment,ClaireEnvironment,last_debug,_integer, 0);        // last value of the debug index
        CL_ADDSLOT(_environment,ClaireEnvironment,last_index,_integer,0);         // last value of the top of eval stack
        CL_ADDSLOT(_environment,ClaireEnvironment,last_trace,_integer,0);         // last value of the top of eval stack
        CL_ADDSLOT(_environment,ClaireEnvironment,spy_I,_object,0);         // store the spy method if any
        CL_ADDSLOT(_environment,ClaireEnvironment,count_call,_integer, (OID)-1);      // count the numbers of call
        CL_ADDSLOT(_environment,ClaireEnvironment,count_level,_integer, 0);      // level at which something happens ...
        CL_ADDSLOT(_environment,ClaireEnvironment,count_trigger,_any,CNULL);     // what should happen
        CL_ADDSLOT(_environment,ClaireEnvironment,params,_list,_oid_(list::empty()));    // list of arguments v2.4.07
        CL_ADDSLOT(_environment,ClaireEnvironment,close,_integer,0);              // integer constants for open(x)
        CL_ADDSLOT(_environment,ClaireEnvironment,ABSTRACT,_integer,0);           // ....
        CL_ADDSLOT(_environment,ClaireEnvironment,FINAL,_integer,0);
        CL_ADDSLOT(_environment,ClaireEnvironment,DEFAULT,_integer,0);
        CL_ADDSLOT(_environment,ClaireEnvironment,open,_integer,0);
        CL_ADDSLOT(_environment,ClaireEnvironment,ephemeral,_integer,0);
    
ClEnv->moduleStack = list::empty();
ClEnv->isa = _environment;
symbol::make("system",claire.it,claire.it)->value = _oid_(ClEnv);

Kernel.GcError = system_error::make(0,0,0);

_unbound_symbol = ClaireClass::make("unbound_symbol",_system_object,claire.it);
    CL_ADDSLOT(_unbound_symbol,unbound_symbol,name,_symbol,CNULL);
_keyword = ClaireClass::make("keyword",_system_thing,claire.it);

_module->instances = list::alloc(3,_oid_(claire.it),_oid_(it),_oid_(mClaire.it));


{ITERATE(c);
 for (START(_primitive->descendents); NEXT(c);)
    OBJECT(ClaireClass,c)->open = ClEnv->close;}
_cl_import->open = ClEnv->ABSTRACT,
_object->open = ClEnv->ABSTRACT,
_class->open = ClEnv->FINAL;
_slot->open = ClEnv->FINAL;
_boolean->open = ClEnv->FINAL;  // ClEnv->ABSTRACT;
_bag->open = ClEnv->FINAL; // v3.2.24 was ClEnv->ABSTRACT !
_list->open = ClEnv->FINAL; // ClEnv->ABSTRACT;
_set->open = ClEnv->FINAL; // ClEnv->ABSTRACT;
_any->open = ClEnv->FINAL; // ClEnv->ABSTRACT;
_exception->open = 4;
_error->open = 4;
_table->open=4; //<sb>


 }


// ===================== end of bootstrap =========================================

void KernelClass::metaLoad()
{bootstrap();
// properties of module Kernel
copy = property::make("copy",claire.it);
_equal = operation::make("=",claire.it,60);
insensitive_equal = operation::make("insensitive=", claire.it, 60);
slot_get = property::make("slot_get",claire.it);
_Z = operation::make("%",claire.it,50);
hash = property::make("hash",claire.it);
add_slot = property::make("add_slot",claire.it);
sort_I = property::make("sort!",claire.it);
add_method = property::make("add_method",claire.it);
_delete = operation::make("delete",claire.it,20);
add = operation::make("add",claire.it,10);
add_I = operation::make("add!",claire.it,10);
cons = operation::make("cons",claire.it,10);
make_list = property::make("make_list",claire.it);
make_table = property::make("make_table",claire.it); //<sb>
add_star = operation::make("add*",claire.it,10);
_7_plus = operation::make("/+",claire.it,10);
nth_plus = property::make("nth+",claire.it);
nth_dash = property::make("nth-",claire.it);
cdr = property::make("cdr",claire.it);
shrink = property::make("shrink",claire.it);
_exp = operation::make("^",claire.it,5);
set_I = property::make("set!",1,claire.it,1);  // v3.0.52 !!!
list_I = property::make("list!",claire.it);
_dot_dot = operation::make("..",claire.it,30);
_dash_dash_ask = operation::make("--?",claire.it,30);
length = property::make("length",claire.it);
of = property::make("of",claire.it);
nth_get = property::make("nth_get",claire.it);
nth_put = property::make("nth_put",claire.it);
array_I = property::make("array!",claire.it);
princ = property::make("princ",claire.it);
color_princ = property::make("color_princ",claire.it); //<sb> v3.3.33
self_print = property::make("self_print",claire.it);
self_print->open = 3;                         // v3.2.00
integer_I = property::make("integer!",claire.it);
substring = property::make("substring",claire.it);
get = property::make("get",claire.it);
nth = property::make("nth",claire.it);
nth_equal = property::make("nth=",claire.it);
begin = property::make("begin",claire.it);
end = property::make("end",claire.it);
defined = property::make("defined",claire.it);
gensym = property::make("gensym",claire.it);
_dash = operation::make("-",claire.it,20);
mod = operation::make("mod",claire.it,10);
_7 = operation::make("/",claire.it,10);
_exp2 = property::make("^2",claire.it);
char_I = property::make("char!",claire.it);
string_I = property::make("string!",claire.it);
make_string = property::make("make_string",claire.it);
random = property::make("random",claire.it);
random_I = property::make("random!",claire.it);
_star = operation::make("*",claire.it,10);
float_I = property::make("float!",claire.it);
_inf = operation::make("<",4,claire.it,60);                       // v3.2.04
_inf_equal = operation::make("<=",claire.it,60);                  // status 4 means that a new definition
_sup = operation::make(">",4,claire.it,60);                       // that creates a conflict is allowed
_sup_equal = operation::make(">=",4,claire.it,60);                //
use_as_output = property::make("use_as_output",claire.it);
//fclose = property::make("fclose",claire.it);
//putc = property::make("putc",claire.it);
//ungetc = property::make("ungetc",claire.it); //<sb> wcl
set_index = property::make("set_index",claire.it); //<sb> wcl
index_jump = property::make("index_jump", mClaire.it); //<sb> wcl
get_index = property::make("get_index",claire.it); //<sb> wcl
//eof_ask = property::make("eof?",claire.it); //<sb>
//setvbuf = property::make("setvbuf",claire.it); //<sb>
put = property::make("put",claire.it);
//getc = property::make("getc",claire.it);
//flush = property::make("flush",claire.it);
//fopen = property::make("fopen",claire.it);
//clearerr = property::make("clearerr",claire.it); //<sb>
//null_I = property::make("null!",claire.it); //<sb>
//port_I = property::make("port!",claire.it);
//set_length = property::make("set_length",claire.it); //<sb> was defined in mClaire
read_string = property::make("read_string",mClaire.it);
read_ident = property::make("read_ident",mClaire.it);
read_number = property::make("read_number",mClaire.it);
read_thing = property::make("read_thing",mClaire.it);
c_princ = property::make("c_princ",claire.it);
mem = property::make("mem",claire.it);
stat = property::make("stat",claire.it);
stack_apply = property::make("stack_apply",claire.it);
fastcall = property::make("fastcall",claire.it);            // KEEP HERE !
funcall = property::make("funcall",claire.it);
store = property::make("store",claire.it);
choice = property::make("choice",claire.it);         // world+
backtrack = property::make("backtrack",claire.it);   // world-
commit = property::make("commit",claire.it);         // world-!
commit0 = property::make("commit0",claire.it);       // world-0
world_ask = property::make("world?",claire.it);
world_id = property::make("world_id",claire.it);
contain_ask = property::make("contain?",claire.it);
print = property::make("print",claire.it);
member_ask = property::make("member?",claire.it);
cast_I = property::make("cast!",claire.it);
_inf_inf = operation::make("<<",claire.it,10);
symbol_I = property::make("symbol!",claire.it);
boolean_I = property::make("boolean!",claire.it);
restore_state = property::make("restore_state",mClaire.it);
date_I = property::make("date!",claire.it);
empty = property::make("empty",claire.it);
free_I = property::make("free!",ClEnv->open,claire.it);           // v3.2.40
prefree_I = property::make("prefree!",ClEnv->open,claire.it);           // v3.2.40

find_ask = property::make("find?",claire.it);

bin_I = property::make("bin!",claire.it); //<sb>
hex_I = property::make("hex!",claire.it); //<sb>

fread = property::make("fread",claire.it); //<sb>
fwrite = property::make("fwrite",claire.it); //<sb>
freadline = property::make("freadline",claire.it); //<sb>
freadwrite = property::make("freadwrite",claire.it); //<sb>
//reverse_I = property::make("reverse!", claire.it); //<sb>

prealloc_set =   property::make("prealloc_set",claire.it); //<sb>
prealloc_list =   property::make("prealloc_list",claire.it); //<sb>

//<sb>
// === color ==================================================================
color = property::make("color",claire.it);

//<sb>
// === stringtool ==================================================================
alpha_ask = property::make("alpha?",claire.it);
lower_ask = property::make("lower?",claire.it);
upper_ask = property::make("upper?",claire.it);
upper = property::make("upper",claire.it);
lower = property::make("lower",claire.it);
space_ask = property::make("space?",claire.it);
digit_ask = property::make("digit?",claire.it);
replace = property::make("replace",claire.it);
occurrence = property::make("occurrence",claire.it);
find = property::make("find",claire.it);
rfind = property::make("rfind",claire.it);
ltrim = property::make("ltrim",claire.it);
rtrim = property::make("rtrim",claire.it);
trim = property::make("trim",claire.it);
left = property::make("left",claire.it);
right = property::make("right",claire.it);
reverse = property::make("reverse",claire.it);
explode = property::make("explode",claire.it);
explode_wildcard = property::make("explode_wildcard",claire.it);

//<sb>
// === env ==================================================================
ding = property::make("ding",claire.it);
cerror = property::make("cerror",claire.it);
setenv = property::make("setenv",claire.it);
environ = property::make("environ",claire.it);
setcwd = property::make("setcwd",claire.it);
pwd = property::make("pwd",claire.it);
maxenv = property::make("maxenv",claire.it);
isenv_ask =property::make("isenv?",claire.it);

//<sb>
// === encoding ==================================================================
url_encode = property::make("url_encode",claire.it);
url_decode = property::make("url_decode",claire.it);
mime_decode = property::make("mime_decode",claire.it);
mime_encode = property::make("mime_encode",claire.it);
encode64 = property::make("encode64",claire.it);
decode64 = property::make("decode64",claire.it);
unescape = property::make("unescape",claire.it);
escape = property::make("escape",claire.it);

//<sb>
// === time ==================================================================
timer_I = property::make("timer!",claire.it);
elapsed = property::make("elapsed",claire.it);
sleep = property::make("sleep",claire.it);
setlocale = property::make("setlocale",claire.it);
getlocale = property::make("getlocale",claire.it);
make_date = property::make("make_date",claire.it);
make_time = property::make("make_time",claire.it);
strftime = property::make("strftime",claire.it);
diff_time = property::make("diff_time",claire.it);
date_add = property::make("date_add",claire.it);
now = property::make("now",claire.it);
uptime = property::make("uptime",claire.it);
uid = property::make("uid",claire.it);
tzset = property::make("tzset",claire.it);

//<sb>
// === dir/files ==================================================================
match_wildcard_ask = property::make("match_wildcard?",claire.it);
entries = property::make("entries",claire.it);
entry = property::make("entry",claire.it);
isdir_ask = property::make("isdir?",claire.it);
isfile_ask = property::make("isfile?",claire.it);
unlink = property::make("unlink",claire.it);
mkdir = property::make("mkdir",claire.it);
rmdir = property::make("rmdir",claire.it);
chmod = property::make("chmod",claire.it);
link = property::make("link",claire.it);
symlink = property::make("symlink",claire.it);
fcopy = property::make("fcopy",claire.it);
fmove = property::make("fmove",claire.it);
fsize = property::make("fsize",claire.it);
fchanged = property::make("fchanged",claire.it);
fmodified = property::make("fmodified",claire.it);
faccessed = property::make("faccessed",claire.it);
fmode = property::make("fmode",claire.it);
realpath = property::make("realpath",claire.it);
flock = property::make("flock",claire.it);
funlock = property::make("funlock",claire.it);
islocked_ask = property::make("islocked?",claire.it);


//<sb>
// === process ================================================================
getuid = property::make("getuid",claire.it);
getpid = property::make("getpid",claire.it);
getppid = property::make("getppid",claire.it);
cfork = property::make("cfork",claire.it);
forked = property::make("forked",claire.it);
kill = property::make("kill",claire.it);
run_ask = property::make("run?",claire.it);
wait = property::make("wait",claire.it);
waitpid_status = property::make("waitpid_status",Kernel.it);
process_I = property::make("process!",claire.it);
//popen = property::make("popen",claire.it);

//<sb>
// === uname ================================================================
sys_name = property::make("sys_name",claire.it);
sys_node_name = property::make("sys_node_name",claire.it);
sys_release = property::make("sys_release",claire.it);
sys_version = property::make("sys_version",claire.it);
sys_machine = property::make("sys_machine",claire.it);
sys_arch = property::make("sys_arch",claire.it);
sys_compiler = property::make("sys_compiler",claire.it);
sys_compiler_version = property::make("sys_compiler_version",claire.it);

//<sb>
// === socket ================================================================
/*server_I = property::make("server!",claire.it);
client_I = property::make("client!",claire.it);
accept = property::make("accept",claire.it);
send_file = property::make("send_file",claire.it);
set_send_size = property::make("set_send_size",claire.it);
select_ask = property::make("select?",claire.it);
nodelay_I = property::make("nodelay!",claire.it);
readable_ask = property::make("readable?",claire.it);
writable_ask = property::make("writable?",claire.it);
read_I = property::make("read!",claire.it);
write_I = property::make("write!",claire.it);
readwrite_I = property::make("readwrite!",claire.it);
hostaddr = property::make("hostaddr",claire.it);
hostname = property::make("hostname",claire.it);
socketpair = property::make("socketpair",claire.it);
peek = property::make("peek",claire.it);
peekc = property::make("peekc",claire.it);
block_I = property::make("block!",claire.it);
nonblock_I = property::make("nonblock!",claire.it);
shutdown = property::make("shutdown",claire.it);
lingering_close = property::make("lingering_close",claire.it);
*/

//<sb> moved to kernel for performance
find_which = property::make("find_which",1,claire.it,Kernel._any,0);

// methods
// method definition of module Kernel -------------------------------------
// we follow the same order as in the claire.h API list
// TODO: check all status

copy->addMethod( list::domain(1,_object),_object,
                 NEW_ALLOC, _function_(copy_object,"copy_object"));
_equal->addMethod(   list::domain(2,_any,_any),_boolean,
                    0,_function_(equal,"equal"));
slot_get->addMethod( list::domain(3,_object,_integer,_class),_any,
                    0,_function_(slot_get_object,"slot_get_object"));
_Z->addMethod( list::domain(2,_any,_any),_boolean,
                    0,_function_(belong_to,"belong_to"));
boolean_I->addMethod( list::domain(1,_any),_boolean,
                    0,_function_(boolean_I_any,"boolean_I_any"));
hash->addMethod( list::domain(2,_list,_any),_integer,
                0,_function_(hash_list,"hash_list"));
_Z->range = _boolean;

// === class & properties ===================================================
add_slot->addMethod(list::domain(5,_class,_property,_type,_any,_integer),_slot,
                    0,_function_(add_slot_class,"add_slot_class"));
sort_I->addMethod(  list::domain(1,_class),_class,
                    0,_function_(sort_I_class,"sort_I_class"));
add_method->addMethod(  list::domain(5,_property,_list,_type,_any,_any),_method,
                        0,_function_(add_method_property,"add_method_property")),
index->addMethod(   list::domain(2,_table,_any),_integer,
                    0,_function_(index_table,"index_table"));
index->addMethod(   list::domain(3,_table,_any,_any),_integer,
                    0,_function_(index_table2,"index_table2"));


// === bags =================================================================
copy->addMethod(    list::domain(1,_bag),_bag,
                    0,_function_(copy_bag,"copy_bag"));
empty->addMethod(    list::domain(1,_bag),_bag,
                    0,_function_(empty_bag,"empty_bag"));
_delete->addMethod(  list::domain(2,_bag,_any),_bag,
                    0,_function_(delete_bag,"delete_bag"));
of->addMethod(  list::domain(1,_bag),_type,
                0,_function_(of_bag,"of_bag"));
//cast_I->addMethod(  list::domain(2,_bag,_type),_bag,
  //                  RETURN_ARG,_function_(cast_I_bag,"cast_I_bag"));
cast_I->addMethod(  list::domain(2,_list,_type),_list,
                    RETURN_ARG,_function_(cast_I_list1,"cast_I_list1"));
cast_I->addMethod(  list::domain(2,_set,_type),_set,
                    RETURN_ARG,_function_(cast_I_set1,"cast_I_set1"));

// === list =================================================================
add->addMethod( list::domain(2,_list,_any),_list,
                NEW_ALLOC+SAFE_RESULT,_function_(add_list,"add_list"));
add_I->addMethod( list::domain(2,_list,_any),_list,
                NEW_ALLOC+SAFE_RESULT,_function_(add_I_list,"add_I_list"));
cons->addMethod(    list::domain(2,_any,_list),_list,
                    NEW_ALLOC+SAFE_RESULT,_function_(cons_any,"cons_any"));
make_list->addMethod(   list::domain(2,_integer,_any),_list,
                        NEW_ALLOC+SAFE_RESULT ,_function_(make_list_integer,"make_list_integer"));
make_list->addMethod(   list::domain(2,_type,_integer),_list,
                        NEW_ALLOC+SAFE_RESULT ,_function_(make_list_type1,"make_list_type1"));
make_table->addMethod(   list::domain(3,_type,_type,_any),_table,
                        NEW_ALLOC+SAFE_RESULT ,_function_(make_table_type,"make_table_type"));
add_star->addMethod(list::domain(2,_list,_list),_list,
                    NEW_ALLOC+SAFE_RESULT,_function_(add_star_list,"add_star_list"));
_7_plus->addMethod(  list::domain(2,_list,_list),_list,
                    NEW_ALLOC+SAFE_RESULT,_function_(append_list,"append_list"));
nth_plus->addMethod(  list::domain(3,_list,_integer,_any),_list,
                    NEW_ALLOC+BAG_UPDATE+SAFE_RESULT,_function_(add_at_list,"add_at_list"));
nth_dash->addMethod(   list::domain(2,_list,_integer),_list,
                        RETURN_ARG,_function_(delete_at_list,"delete_at_list"));
_inf_inf->addMethod(list::domain(2,_list,_integer),_list,
                0,_function_(skip_list,"skip_list"));
cdr->addMethod( list::domain(1,_list),_list,
                NEW_ALLOC+SAFE_RESULT,_function_(cdr_list,"cdr_list"));  // safe_result  ->
shrink->addMethod(  list::domain(2,_bag,_integer),_bag,          // v3.2.20
                    0,_function_(shrink_list,"shrink_list"));
contain_ask->addMethod( list::domain(2,_list,_any),_boolean,
                        0,_function_(contain_ask_list,"contain_ask_list"));
get->addMethod( list::domain(2,_list,_any),_integer,
                0,_function_(index_list,"index_list"));
// new
make_string->addMethod( list::domain(1,_list),_string,
                        NEW_ALLOC,_function_(make_string_list,"make_string_list"));

prealloc_set->addMethod( list::domain(2,_type,_integer),_set,
                        NEW_ALLOC+SAFE_RESULT,_function_(prealloc_set_type1,"prealloc_set_type1"));
prealloc_list->addMethod( list::domain(2,_type,_integer),_list,
                        NEW_ALLOC+SAFE_RESULT,_function_(prealloc_list_type1,"prealloc_list_type1"));


// === sets =================================================================
add->addMethod( list::domain(2,_set,_any),_set,
                NEW_ALLOC+SAFE_RESULT,_function_(add_set,"add_set"));
add_I->addMethod( list::domain(2,_set,_any),_set,
                  NEW_ALLOC+SAFE_RESULT,_function_(add_I_set,"add_I_set"));
_exp->addMethod(    list::domain(2,_set,_set),_set,
                    NEW_ALLOC+SAFE_RESULT,_function_(_exp_set,"_exp_set"));
contain_ask->addMethod( list::domain(2,_set,_any),_boolean,
                        0,_function_(contain_ask_set,"contain_ask_set"));
_7_plus->addMethod(  list::domain(2,_set,_set),_set,
                    NEW_ALLOC+SAFE_RESULT,_function_(append_set,"append_set"));
//set_I->addMethod(   list::domain(1,_bag),_set,
//                    NEW_ALLOC+SAFE_RESULT,_function_(set_I_bag,"set_I_bag"));
//list_I->addMethod(  list::domain(1,_set),_list,
//                    NEW_ALLOC+SAFE_RESULT,_function_(list_I_set,"list_I_set"));
_dash_dash_ask->addMethod(list::domain(2,_integer,_integer),_collection,
                    NEW_ALLOC+SAFE_RESULT,_function_(sequence_integer,"sequence_integer"));

                    
// === tuple =============================================================
list_I->addMethod(  list::domain(1,_tuple),_list,
                    NEW_ALLOC+SAFE_RESULT,_function_(list_I_tuple,"list_I_tuple"));

// === array ==================================================================
copy->addMethod(list::domain(1,_array),_array,
                NEW_ALLOC,_function_(copy_array,"copy_array"));
length->addMethod(  list::domain(1,_array),_integer,
                    0,_function_(length_array,"length_array"));
of->addMethod(  list::domain(1,_array),_type,
                0,_function_(of_array,"of_array"));
nth_get->addMethod( list::domain(2,_array,_integer),_any,     // v3.0.54 thanxs FXJ !
                    0,_function_(nth_get_array,"nth_get_array"));
nth_put->addMethod( list::domain(3,_array,_integer,_any),_void,
                    0,_function_(nth_put_array,"nth_put_array"));

// === strings =============================================================
copy->addMethod(    list::domain(1,_string),_string,
                    NEW_ALLOC,_function_(copy_string,"copy_string"));
copy->addMethod(    list::domain(2,_string,_integer),_string,
                    NEW_ALLOC,_function_(copy_string1,"copy_string1"));
//_equal->addMethod(  list::domain(2,_string,_string),_boolean,
//                    0,_function_(equal_string,"equal_string"));
insensitive_equal->addMethod(list::domain(2,_string,_string),_boolean,
                    0,_function_(insensitive_equal_string1,"insensitive_equal_string1"));
princ->addMethod(   list::domain(1,_string),_void,
                    0,_function_(princ_string,"princ_string"));
princ->addMethod(   list::domain(3,_string,_integer,_integer),_void,
                    0,_function_(princ_string1,"princ_string1"));
color_princ->addMethod(   list::domain(1,_string),_void, //<sb> v3.3.33
                    0,_function_(color_princ_string1,"color_princ_string1"));
color_princ->addMethod(   list::domain(3,_string,_integer,_integer),_void,
                    0,_function_(color_princ_string2,"color_princ_string2"));
self_print->addMethod(  list::domain(1,_string),_void,
                        0,_function_(self_print_string,"self_print_string"));
_7_plus->addMethod(  list::domain(2,_string,_string),_string,
                    NEW_ALLOC,_function_(append_string,"append_string"));
integer_I->addMethod(   list::domain(1,_string),_integer,
                        0,_function_(integer_I_string,"integer_I_string"));
substring->addMethod(   list::domain(3,_string,_integer,_integer),_string,
                        NEW_ALLOC,_function_(substring_string,"substring_string"));
get->addMethod( list::domain(2,_string,_char),_integer,
                0,_function_(get_string,"get_string"));
_inf_equal->addMethod(   list::domain(2,_string,_string),_boolean,
                    0,_function_(_less_string,"_less_string"));
substring->addMethod(list::domain(3,_string,_string,_boolean),_integer,
                    0,_function_(included_string,"included_string"));
nth->addMethod( list::domain(2,_string,_integer),_char,
                0,_function_(nth_string,"nth_string"));
nth_equal->addMethod( list::domain(3,_string,_integer,_char), _void,
                    0,_function_(nth_set_string,"nth_set_string"));
shrink->addMethod(  list::domain(2,_string,_integer),_string,
                    0,_function_(shrink_string,"shrink_string"));
value->addMethod(   list::domain(1,_string),_any,
                    0,_function_(value_string,"value_string"));
value->addMethod(   list::domain(2,_module,_string),_any,
                    0,_function_(value_module,"value_module"));
date_I->addMethod(  list::domain(1,_integer),_string,
                    NEW_ALLOC,_function_(date_I_integer,"date_I_integer"));

// === ports ==================================================================

use_as_output->addMethod(   list::domain(1,_port),_port,
                            SAFE_RESULT,_function_(use_as_output_port,"use_as_output_port"));

read_string->addMethod( list::domain( 1,_port), _string,
                        NEW_ALLOC,_function_(read_string_port, "read_string_port"));
read_ident->addMethod(  list::domain( 1,_port), _any,
                        NEW_ALLOC,_function_( read_ident_port,"read_ident_port"));
read_number->addMethod( list::domain( 1,_port),_any,
                        NEW_ALLOC,_function_(read_number_port,"read_number_port"));
read_thing->addMethod(  list::domain(4,_port,_module,_char,_module),_any,
                        NEW_ALLOC,_function_(read_thing_port,"read_thing_port"));
free_I->addMethod(list::domain(1,_any),_void,                            // v3.2.40 -> enable free <sb> bind it to import!
                  0,_function_(free_I_any,"free_I_any"));
prefree_I->addMethod(list::domain(1,_any),_void,                            // v3.2.40 -> enable free <sb> bind it to import!
                  0,_function_(prefree_I_any,"prefree_I_any"));


freadline->addMethod(list::domain(1,_port),_string, //<sb>
                        NEW_ALLOC,_function_(freadline_port,"freadline_port"));
freadline->addMethod(list::domain(2,_port,_string),_string, //<sb>
                        NEW_ALLOC,_function_(freadline_port1,"freadline_port1"));
freadline->addMethod(list::domain(3,_port,_string,_boolean),_string, //<sb>
                        NEW_ALLOC,_function_(freadline_port2,"freadline_port2"));
freadline->addMethod(list::domain(4,_port,_string,_boolean,_char),_string, //<sb>
                        NEW_ALLOC,_function_(freadline_port3,"freadline_port3"));
freadline->addMethod(list::domain(2,_port,_bag),_tuple, //<sb>
                        NEW_ALLOC,_function_(freadline_port4,"freadline_port4"));
freadline->addMethod(list::domain(3,_port,_bag,_boolean),_tuple, //<sb>
                        NEW_ALLOC,_function_(freadline_port5,"freadline_port5"));
freadline->addMethod(list::domain(4,_port,_bag,_boolean,_char),_tuple, //<sb>
                        NEW_ALLOC,_function_(freadline_port6,"freadline_port6"));


// ==== modules & symbols =====================================================
begin->addMethod(   list::domain(1,_module),_void,
                    0,_function_(begin_module,"begin_module"));
end->addMethod( list::domain(1,_module),_void,
                0,_function_(end_module,"end_module"));
_7_plus->addMethod(  list::domain(2,_symbol,_any),_symbol,
                    NEW_ALLOC,_function_(append_symbol,"append_symbol"));
princ->addMethod(   list::domain(1,_symbol),_void,
                    0,_function_(princ_symbol,"princ_symbol"));
defined->addMethod( list::domain(1,_symbol),_module,
                    0,_function_(defined_symbol,"defined_symbol"));
gensym->addMethod(  list::domain(1,_string),_symbol,
                    0,_function_(gensym_string ,"gensym_string"));
string_I->addMethod(list::domain( 1,_symbol),_string,
                    0,_function_(string_I_symbol, "string_I_symbol"));
get->addMethod( list::domain(1,_symbol),_any,
                0,_function_(get_symbol,"get_symbol"));
put->addMethod( list::domain(2,_symbol,_any),_any,
                0,_function_(put_symbol,"put_symbol"));
symbol_I->addMethod(list::domain(2,_string,_module),_symbol,
        0,_function_(symbol_I_string,"symbol!_string"));
integer_I->addMethod(   list::domain(1,_symbol),_integer,
                        0,_function_(integer_I_symbol,"integer_I_symbol"));
                    
// === integer & floats =======================================================
_dash->addMethod(  list::domain(1,_integer),_integer,
                    0,_function_(ch_sign,"ch_sign"));
mod->addMethod( list::domain(2,_integer,_integer),_integer,
                0,_function_(mod_integer,"mod_integer"));
_7->addMethod(  list::domain(2,_integer,_integer),_integer,
                0,_function_(_7_integer,"_7_integer"));
_exp->addMethod(    list::domain(2,_integer,_integer),_integer,
                    0,_function_(_exp_integer,"_exp_integer"));
_exp2->addMethod(    list::domain(1,_integer),_integer,
                    0,_function_(exp2_integer,"exp2_integer"));
char_I->addMethod(  list::domain(1,_integer),_char,
                    0,_function_(char_I_integer,"char_I_integer"));
string_I->addMethod(list::domain(1,_integer),_string,
                    NEW_ALLOC,_function_(string_I_integer ,"string_I_integer "));
make_string->addMethod( list::domain(2,_integer,_char),_string,
                        NEW_ALLOC,_function_(make_string_integer,"make_string_integer"));
make_string->addMethod( list::domain(1,_integer),_string,
                        NEW_ALLOC,_function_(make_string_integer1,"make_string_integer1"));
random->addMethod(  list::domain(1,_integer),_integer,
                    0,_function_(random_integer,"random_integer"));
random_I->addMethod(  list::domain(1,_integer),_void,                       // v3.2.36
                    0,_function_(srand,"srand"));
random_I->addMethod(  list::domain(1,_void),_void,                       // v3.2.36
                    0,_function_(random_I_void,"random_I_void"));
_star->addMethod(  list::domain(2,_integer,_integer),_integer,
                    0,_function_(times_integer,"times_integer"));
princ->addMethod(   list::domain(1,_integer),_void,
                    0,_function_(princ_integer,"princ_integer"));

float_I->addFloatMethod( list::domain(1,_integer), _float,
                    0,_function_(to_float ,"to_float "),
                    _function_(to_float_ ,"to_float_"));
integer_I->addFloatMethod(   list::domain(1,_float),_integer,
                        0,_function_(integer_I_float,"integer_I_float")
                         ,_function_(integer_I_float_,"integer_I_float_"));   // v3.0.4
_inf->addFloatMethod(    list::domain(2,_float,_float),_boolean,
                    0,_function_(_inf_float,"_inf_float"),
                    _function_(_inf_float_,"_inf_float_"));
_inf_equal->addFloatMethod(list::domain(2,_float,_float),_boolean,
                 0,_function_(_inf_equal_float,"_inf_equal_float"),
                 _function_(_inf_equal_float_,"_inf_equal_float_"));
_sup->addFloatMethod(list::domain(2,_float,_float),_boolean,
                 0,_function_(_sup_float,"_sup_float"),
                 _function_(_sup_float_,"*_sup_float_"));
_sup_equal->addFloatMethod(  list::domain(2,_float,_float),_boolean,
                    0,_function_(_sup_equal_float,"_sup_equal_float"),
                    _function_(_sup_equal_float_,"_sup_equal_float_"));
princ->addFloatMethod(   list::domain(1,_float),_void,
                         0,_function_(princ_float,"princ_float"),
                         _function_(princ_float_,"princ_float_"));

bin_I->addMethod(list::domain(1,_integer),_string,
                    NEW_ALLOC,_function_(bin_I_integer,"bin_I_integer"));
hex_I->addMethod(list::domain(1,_integer),_string,
                    NEW_ALLOC,_function_(hex_I_integer,"hex_I_integer"));

// === char & system ==========================================================

princ->addMethod(  list::domain(1,_char),_void,
                   0,_function_(princ_char,"princ_char"));
c_princ->addMethod( list::domain(1,_char),_void,
                    0,_function_(c_princ_c,"c_princ_c"));
c_princ->addMethod(list::domain(1,_string),_void,
                    0,_function_(c_princ_string,"c_princ_string"));
c_princ->addMethod( list::domain(1,_symbol),_void,
                    0,_function_(c_princ_symbol,"c_princ_symbol"));
mem->addMethod( list::domain(1,_any),_any,
                NEW_ALLOC,_function_(claire_mem,"claire_mem"));
stat->addMethod(    list::domain(1,_void),_void,
                    0,_function_(claire_stat,"claire_stat"));
integer_I->addMethod(   list::domain(1,_char),_integer,
                        0,_function_(integer_I_char,"integer_I_char"));

// === system functions =======================================================
close->addMethod(   list::domain(1,_exception), Kernel.emptySet,
                    0,_function_(close_exception,"close_exception"));
stack_apply->addMethod(list::domain(1,_integer),_void,
                       0,_function_(stack_add,"stack_add"));
funcall->addMethod( list::domain(4,_function,_class,_any,_class),_any,
                    0,_function_(fcall1,"fcall1"));
funcall->addMethod( list::domain(6,_function,_class,_any,_class,_any,_class),_any,
                    0,_function_(fcall2,"fcall2"));
funcall->addMethod( list::domain(8,_function,_class,_any,_class,_any,_class,_any,_class),
                    _any, 0,_function_(fcall3,"fcall3"));
stack_apply->addMethod( list::domain(4,_function,_list,_integer,_integer),_any,
                        0,_function_(stack_apply_function,"stack_apply_function"));
string_I->addMethod(list::domain(1,_function),_string,
                    0,_function_(string_I_function,"string_I_function"));
store->addMethod(   list::domain(4,_list,_integer,_any,_boolean),_any,
                    BAG_UPDATE ,_function_(store_list,"store_list"));
store->addMethod(   list::domain(4,_array,_integer,_any,_boolean),_any,
                    0,_function_(store_array,"store_array"));
store->addMethod(   list::domain(5,_object,_integer,_class,_any,_boolean),_any,
                    SLOT_UPDATE,_function_(store_object,"store_object"));
store->addMethod(   list::domain(2,_list,_any),_list,
                        NEW_ALLOC + BAG_UPDATE,_function_(store_add,"store_add"));
choice->addMethod(  list::domain(1,_void),_void,
                        0,_function_(world_push,"world_push"));
backtrack->addMethod( list::domain(1,_void),_void,
                        0,_function_(world_pop,"world_pop"));
commit->addMethod(   list::domain(1,_void),_void,
                            0,_function_(world_remove,"world_remove"));
commit0->addMethod(    list::domain(1,_void),_void,
                        0,_function_(world_slaughter,"world_slaughter"));
world_ask->addMethod(   list::domain(1,_void),_integer,
                        0,_function_(world_number,"world_number"));
world_id->addMethod(   list::domain(1,_void),_integer,
                        0,_function_(world_get_id,"world_get_id"));
restore_state->addMethod(   list::domain(1,_void),_void,
                        0,_function_(restore_state_void,"restore_state_void"));

//<sb>
// === color ==================================================================
color->addMethod(list::domain(1,_integer), _integer,
    0,_function_(color_integer,"color_integer"));
color->addMethod(list::domain(1,_void), _integer,
    0,_function_(color_void,"color_void"));
//<sb>
// === stringtool =================================================================
alpha_ask->addMethod(list::domain(1,_string),_boolean,
    0,_function_(alpha_ask_string,"alpha_ask_string"));
alpha_ask->addMethod(list::domain(1,_char),_boolean,
    0,_function_(alpha_ask_char,"alpha_ask_char"));
space_ask->addMethod(list::domain(1,_char),_boolean,
    0,_function_(space_ask_char,"space_ask_char"));
digit_ask->addMethod(list::domain(1,_char),_boolean,
    0,_function_(digit_ask_char,"digit_ask_char"));
space_ask->addMethod(list::domain(1,_string),_boolean,
    0,_function_(space_ask_string,"space_ask_string"));
digit_ask->addMethod(list::domain(1,_string),_boolean,
    0,_function_(digit_ask_string,"digit_ask_string"));
lower_ask->addMethod(list::domain(1,_char),_boolean,
    0,_function_(lower_ask_char,"lower_ask_char"));
lower_ask->addMethod(list::domain(1,_string),_boolean,
    0,_function_(lower_ask_string,"lower_ask_string"));
upper_ask->addMethod(list::domain(1,_char),_boolean,
    0,_function_(upper_ask_char,"upper_ask_char"));
upper_ask->addMethod(list::domain(1,_string),_boolean,
    0,_function_(upper_ask_string,"upper_ask_string"));
upper->addMethod(list::domain(1,_string),_string,
    NEW_ALLOC,_function_(upper_string,"upper_string"));
lower->addMethod(list::domain(1,_string),_string,
    NEW_ALLOC,_function_(lower_string,"lower_string"));
ltrim->addMethod(list::domain(1,_string),_string,
    NEW_ALLOC,_function_(ltrim_string,"ltrim_string"));
rtrim->addMethod(list::domain(1,_string),_string,
    NEW_ALLOC,_function_(rtrim_string,"rtrim_string"));
trim->addMethod(list::domain(1,_string),_string,
    NEW_ALLOC,_function_(trim_string,"trim_string"));
replace->addMethod(list::domain(3,_string,_string,_string),_string,
    NEW_ALLOC,_function_(replace_string,"replace_string"));
occurrence->addMethod(list::domain(2,_string,_string),_integer,
    0,_function_(occurrence_string,"occurrence_string"));
find->addMethod(list::domain(3,_string,_string,_integer),_integer,
    0,_function_(find_string,"find_string"));
find->addMethod(list::domain(2,_string,_string),_integer,
    0,_function_(find_string2,"find_string2"));
left->addMethod(list::domain(2,_string,_integer),_string,
    NEW_ALLOC,_function_(left_string,"left_string"));
right->addMethod(list::domain(2,_string,_integer),_string,
    NEW_ALLOC,_function_(right_string,"right_string"));
rfind->addMethod(list::domain(3,_string,_string,_integer),_integer,
    0,_function_(rfind_string,"rfind_string"));
rfind->addMethod(list::domain(2,_string,_string),_integer,
    0,_function_(rfind_string2,"rfind_string2"));
reverse->addMethod(list::domain(1,_string),_string,
    NEW_ALLOC,_function_(reverse_string,"reverse_string"));
explode->addMethod(list::domain(2,_string,_string),_list,
    NEW_ALLOC,_function_(explode_string,"explode_string"));
explode_wildcard->addMethod(list::domain(2,_string,_string),_list,
    NEW_ALLOC,_function_(explode_wildcard_string,"explode_wildcard_string"));


//<sb>
// === encoding =================================================================
url_encode->addMethod(list::domain(1,_string),_string,
    NEW_ALLOC,_function_(url_encode_string,"url_encode_string"));
url_decode->addMethod(list::domain(1,_string),_string,
    NEW_ALLOC,_function_(url_decode_string,"url_decode_string"));
mime_decode->addMethod(list::domain(1,_string),_string,
    NEW_ALLOC,_function_(mime_decode_string,"mime_decode_string"));
mime_encode->addMethod(list::domain(1,_string),_string,
    NEW_ALLOC,_function_(mime_encode_string,"mime_encode_string"));
encode64->addMethod(list::domain(3,_port,_port,_integer),_void,
    0,_function_(encode64_port,"encode64_port"));
decode64->addMethod(list::domain(2,_port,_port),_void,
    0,_function_(decode64_port,"decode64_port"));
unescape->addMethod(list::domain(1,_string),_string,
    NEW_ALLOC,_function_(unescape_string,"unescape_string"));
escape->addMethod(list::domain(1,_string),_string,
    NEW_ALLOC,_function_(escape_string,"escape_string"));

//<sb>
// === env =================================================================
ding->addMethod(list::domain(1,_void),_void,
    0,_function_(ding_void,"ding_void"));
cerror->addMethod(list::domain(1,_integer),_string,
    NEW_ALLOC,_function_(cerror_integer,"cerror_integer"));
setenv->addMethod(list::domain(1,_string),_void,
    0,_function_(setenv_string,"setenv_string"));
setcwd->addMethod(list::domain(1,_string),_void,
    0,_function_(setcwd_string,"setcwd_string"));
environ->addMethod(list::domain(1,_integer),_string,
    NEW_ALLOC,_function_(environ_integer,"environ_integer"));
pwd->addMethod(list::domain(1,_void),_string,
    NEW_ALLOC,_function_(pwd_void,"pwd_void"));
maxenv->addMethod(list::domain(1,_void),_integer,
    0,_function_(maxenv_void,"maxenv_void"));
isenv_ask->addMethod(list::domain(1,_string),_boolean,
    0,_function_(isenv_ask_string,"isenv_ask_string"));
    
//<sb>
// === process =================================================================
getuid->addMethod(list::domain(1,_void),_integer,
    0,_function_(getuid_void,"getuid_void"));
getpid->addMethod(list::domain(1,_void),_integer,
    0,_function_(getpid_void,"getpid_void"));
getppid->addMethod(list::domain(1,_void),_integer,
    0,_function_(getppid_void,"getppid_void"));
run_ask->addMethod(list::domain(1,_integer),_boolean,
    0,_function_(run_ask_integer,"run_ask_integer"));
kill->addMethod(list::domain(1,_integer),_void,
    0,_function_(kill_integer1,"kill_integer1"));
wait->addMethod(list::domain(2,_integer,_integer),_boolean,
    0,_function_(wait_integer1,"wait_integer1"));
wait->addMethod(list::domain(1,_integer),_void,
    0,_function_(wait_integer2,"wait_integer2"));
process_I->addMethod(list::domain(2,_string,_bag),_integer,
    0,_function_(process_I_string,"process_I_string"));
cfork->addMethod(list::domain(1,_void),_integer,
  0,_function_(cfork_void1,"cfork_void1"));
forked->addMethod(list::domain(1,_void),_integer,
  0,_function_(forked_void,"forked_void"));
//popen->addMethod(list::domain(2,_string,_string),_file,
//  NEW_ALLOC+SAFE_RESULT,_function_(popen_string,"popen_string"));
waitpid_status->addFloatMethod(list::domain(2,_integer,_boolean),_tuple,
    NEW_ALLOC,_function_(waitpid_status_integer,"waitpid_status_integer"),_function_(waitpid_status_integer_,"waitpid_status_integer_"));

//<sb>
// === uname =================================================================
sys_name->addMethod(list::domain(1,_void), _string,
            0,_function_(sys_name_void,"sys_name_void"));
sys_node_name->addMethod(list::domain(1,_void), _string,
            0,_function_(sys_node_name_void,"sys_node_name_void"));
sys_release->addMethod(list::domain(1,_void), _string,
            0,_function_(sys_release_void,"sys_release_void"));
sys_version->addMethod(list::domain(1,_void), _string,
            0,_function_(sys_version_void,"sys_version_void"));
sys_machine->addMethod(list::domain(1,_void), _string,
            0,_function_(sys_machine_void,"sys_machine_void"));
sys_arch->addMethod(list::domain(1,_void), _string,
            0,_function_(sys_arch_void,"sys_arch_void"));
sys_compiler->addMethod(list::domain(1,_void), _string,
            0,_function_(sys_compiler_void,"sys_compiler_void"));
sys_compiler_version->addMethod(list::domain(1,_void), _string,
            0,_function_(sys_compiler_version_void,"sys_compiler_version_void"));

//<sb>
// === time ==================================================================
timer_I->addFloatMethod(list::domain(1,_void), _float,
            NEW_ALLOC,_function_(timer_I_void,"timer_I_void"),_function_(timer_I_void_,"timer_I_void_"));
elapsed->addFloatMethod(list::domain(1,_float), _integer,
            0,_function_(elapsed_float,"elapsed_float"),_function_(elapsed_float_,"elapsed_float_"));
sleep->addMethod(list::domain(1,_integer), _void,
            0,_function_(sleep_integer,"sleep_integer"));
setlocale->addMethod(list::domain(2,_integer,_string), _string,
            NEW_ALLOC,_function_(setlocale_integer,"setlocale_integer"));
getlocale->addMethod(list::domain(1,_integer), _string,
            NEW_ALLOC,_function_(getlocale_integer,"getlocale_integer"));
make_date->addFloatMethod(list::domain(6,_integer,_integer,_integer,_integer,_integer,_integer),_float,
                  NEW_ALLOC,_function_(make_date_integer,"make_date_integer"),_function_(make_date_integer_,"make_date_integer_"));
make_date->addFloatMethod(list::domain(1,_string), _float,
            NEW_ALLOC,_function_(make_date_string,"make_date_string"),_function_(make_date_string_,"make_date_string_"));
make_time->addFloatMethod(list::domain(1,_string), _float,
            NEW_ALLOC,_function_(make_time_string,"make_time_string"),_function_(make_time_string_,"make_time_string_"));
make_time->addFloatMethod(list::domain(3,_integer,_integer,_integer), _float,
            NEW_ALLOC,_function_(make_time_integer,"make_time_integer"),_function_(make_time_integer_,"make_time_integer_"));
strftime->addFloatMethod(list::domain(2,_string,_float), _string,
            NEW_ALLOC,_function_(strftime_string,"strftime_string"),_function_(strftime_string_,"strftime_string_"));
diff_time->addFloatMethod(list::domain(2,_float, _float),_float,
                  NEW_ALLOC,_function_(diff_time_float,"diff_time_float"),_function_(diff_time_float_,"diff_time_float_"));
now->addFloatMethod(list::domain(1,_void),_float,
                  NEW_ALLOC,_function_(now_void,"now_void"),_function_(now_void_,"now_void_"));
uptime->addFloatMethod(list::domain(1,_float),_void,
                  0,_function_(uptime_float,"uptime_float"),_function_(uptime_float_,"uptime_float_"));
date_add->addFloatMethod(list::domain(3,_float,_char,_integer), _float,
            NEW_ALLOC,_function_(date_add_float,"date_add_float"),_function_(date_add_float_,"date_add_float_"));
uid->addMethod(list::domain(1,_void),_string,
            NEW_ALLOC,_function_(uid_void,"uid_void"));
explode->addFloatMethod(list::domain(1,_float),_tuple,
                        NEW_ALLOC,_function_(explode_float,"explode_float"),_function_(explode_float_,"explode_float_"));

tzset->addMethod(list::domain(1,_string),_string,
            0,_function_(tzset_string,"tzset_string"));
//<sb>
// === dir/file ==================================================================
match_wildcard_ask->addMethod(list::domain(2,_string,_string),_boolean,
        0,_function_(match_wildcard_ask_string,"match_wildcard_ask_string"));
entries->addMethod(list::domain(2,_string,_string),_list,
            NEW_ALLOC,_function_(entries_string1,"entries_string1"));
entries->addMethod(list::domain(1,_string),_list,
            NEW_ALLOC,_function_(entries_string2,"entries_string2"));
entry->addMethod(list::domain(2,_string,_string),_string,
            NEW_ALLOC,_function_(entry_string1,"entry_string1"));
isdir_ask->addMethod(list::domain(1,_string),_boolean,
            0,_function_(isdir_ask_string,"isdir_ask_string"));
isfile_ask->addMethod(list::domain(1,_string),_boolean,
            0,_function_(isfile_ask_string,"isfile_ask_string"));
unlink->addMethod(list::domain(1,_string),_void,
            0,_function_(unlink_string,"unlink_string"));
mkdir->addMethod(list::domain(2,_string,_integer),_void,
            0,_function_(mkdir_string1,"mkdir_string1"));
mkdir->addMethod(list::domain(1,_string),_void,
            0,_function_(mkdir_string2,"mkdir_string2"));
rmdir->addMethod(list::domain(1,_string),_void,
            0,_function_(rmdir_string,"rmdir_string"));
chmod->addMethod(list::domain(2,_string,_integer),_void,
            0,_function_(chmod_string,"chmod_string"));
link->addMethod(list::domain(2,_string,_string),_void,
            0,_function_(link_string,"link_string"));
symlink->addMethod(list::domain(2,_string,_string),_void,
            0,_function_(symlink_string,"symlink_string"));
fcopy->addMethod(list::domain(2,_string,_string),_void,
            0,_function_(fcopy_string,"fcopy_string"));
fmove->addMethod(list::domain(2,_string,_string),_void,
            0,_function_(fmove_string,"fmove_string"));
fsize->addFloatMethod(list::domain(1,_string),_float,
      NEW_ALLOC,_function_(fsize_string,"fsize_string"),_function_(fsize_string_,"fsize_string_"));
fchanged->addFloatMethod(list::domain(1,_string),_float,
      NEW_ALLOC,_function_(fchanged_string,"fchanged_string"),_function_(fchanged_string_,"fchanged_string_"));
fmodified->addFloatMethod(list::domain(1,_string),_float,
      NEW_ALLOC,_function_(fmodified_string,"fmodified_string"),_function_(fmodified_string_,"fmodified_string_"));
faccessed->addFloatMethod(list::domain(1,_string),_float,
      NEW_ALLOC,_function_(faccessed_string,"faccessed_string"),_function_(faccessed_string_,"faccessed_string_"));
fmode->addMethod(list::domain(1,_string),_integer,
      0,_function_(fmode_string,"fmode_string"));
realpath->addMethod(list::domain(1,_string),_string,
    NEW_ALLOC,_function_(realpath_string,"realpath_string"));


//<sb> moved to kernel for performance
find_which->addMethod(list::domain(3,Kernel._property,Kernel._integer,Kernel._class),Kernel._object,
    RETURN_ARG,_function_(find_which_property1,"find_which_property1"));

//<sb> stdout/stdin have been moved to Core
// such we don't need Reader to use them

//put_symbol(symbol_I_string("STDIN",claire.it), _oid_(ClAlloc->stdIn));                     
//put_symbol(symbol_I_string("STDOUT",claire.it), _oid_(ClAlloc->stdOut));
//add support for stderr
//put_symbol(symbol_I_string("STDERR",claire.it), _oid_(ClAlloc->stdErr));

Kernel._set->ident_ask = CFALSE;                   
Kernel._list->ident_ask = CFALSE;                   
Kernel._tuple->ident_ask = CFALSE;                   
Kernel._string->ident_ask = CFALSE;                   
Kernel._float->ident_ask = CFALSE;                   
//Kernel._port->ident_ask = CFALSE;                   //<sb> rm #port

}

//<sb> function that can be called from within GDB :
 
void gdb_oid(CL_UNSIGNED oid) {
  if (INTEGERP(oid)) {
#ifdef __LP64__
      fprintf(stdout, "%lu is an integer\n", oid);
#else
    fprintf(stdout, "%d is an integer\n", oid);
#endif
  } else {
    ClaireAny *x = (ClaireAny*)(oid << ADDRTRANS);
#ifdef __LP64__
    fprintf(stdout, "adr 0x%lX\n", (unsigned CL_INT)x);
    fprintf(stdout, "isa 0x%lX\n", (unsigned CL_INT)x->isa);
#else
    fprintf(stdout, "adr 0x%X\n", (unsigned CL_INT)x);
    fprintf(stdout, "isa 0x%X\n", (unsigned CL_INT)x->isa);
#endif
    if (x->isa == NULL)
      fprintf(stdout, "This is a buggy object !!!!\n");
    else if (x->isa == Kernel._string)
      fprintf(stdout, "isa string : \"%s\"\n", string_v(oid));
    else
      fprintf(stdout, "isa %s\n", x->isa->name->name);
  }
}

void gdb_idx(bag *b, CL_INT i) {
  gdb_oid(b->content[i]);
}

void gdb_oid_idx(CL_UNSIGNED oid, CL_INT i) {
  if (INTEGERP(oid)) {
#ifdef __LP64__
      fprintf(stdout, "%lu is an integer (not a bag)!!!!\n", oid);
#else
      fprintf(stdout, "%d is an integer (not a bag)!!!!\n", oid);
#endif
  } else {
    bag *x = (bag*)(oid << ADDRTRANS);
    gdb_oid(x->content[i]);
  }
}


void gdb_obj(ClaireAny *x) {
#ifdef __LP64__
    fprintf(stdout, "oid %llu\n", _oid_(x));
  fprintf(stdout, "isa 0x%lX\n", (unsigned CL_INT)x->isa);
#else
  fprintf(stdout, "oid %u\n", _oid_(x));
  fprintf(stdout, "isa 0x%X\n", (unsigned CL_INT)x->isa);
#endif
  fprintf(stdout, "isa %s\n", x->isa->name->name);

}
/***********************************************************************/
/**   microCLAIRE                                       Yves Caseau    */
/**   clAlloc.cpp                                                      */
/**  Copyright (C) 1998-2003 Yves Caseau. All Rights Reserved.         */
/**  cf claire.h                                                       */
/***********************************************************************/


// this is the allocator file. We use do not use C++ new and delete, so that
// we can allocate everything with a same reference address (&Cmemory[0])
// which is necessary for OIDs. This is slower than system allocation for
// chunks but actually faster for small items

/*********************************************************************/
/** Table of contents                                                */
/**    1. Interface methods                                          */
/**    2. Allocation methods                                         */
/**    3. De-allocation methods                                      */
/**    4. Garbage Collection                                         */
/**    5. Interface functions                                        */
/**    6. Sampling memory                                            */
/**    7. Debugging GC                                               */
/*********************************************************************/

CL_INT BadGuy = 0;      // a remettre a 0 !;
CL_INT maxIndex = 0;
CL_EXPORT CL_INT *CL_dummy;       // not used really
CL_INT numSample = 0;

// debug version that can be instrumented
CL_INT GC_DEBUG(CL_INT n)
  { return n;}


// we use a special object to represent the allocator
// we could use a class with static methods but this is more homogeneous
CL_EXPORT ClaireAllocation *ClAlloc;

CL_EXPORT OID *Cmemory;                  // memory zone
OID *CmemoryAlloc;                  // memory zone
CL_EXPORT OID *CmemoryMax;

CL_EXPORT OID CmemoryAdr;                  // memory zone

// macros for this file -------------------------------------------------
#define CAR 1
#define FOLLOW 2
#define PREVIOUS 3

#ifdef __LP64__
#define ADDRTRANS 3
#define POINTOADR(x) ((CL_UNSIGNED)x >> 3)
#define ADRTOPOIN(x) ((CL_UNSIGNED*)((CL_UNSIGNED)x << 3))
#define SIZE(n) (*((CL_INT*)((CL_UNSIGNED)n << 3) - 1))             // returns the size of the object
#define CL_MAX_INT 0xFFFFFFFFFFFFFFFFLL >> 2
#else
#define ADDRTRANS 2
#define POINTOADR(x) ((CL_UNSIGNED)x >> 2)
#define ADRTOPOIN(x) ((CL_UNSIGNED*)((CL_UNSIGNED)x << 2))
#define SIZE(n) (*((CL_INT*)((CL_UNSIGNED)n << 2) - 1))             // returns the size of the object
#define CL_MAX_INT 0xFFFFFFFF >> 2
#endif


//#define CLDEBUG


static CL_INT from_kill_I = 0;


#ifdef CLDEBUG              // little trick to check that values are OK

CL_INT clbug() {
  raise(SIGSEGV); //<sb> produce a segment violation if a bug is encountered
  return 0;       //  will (if configured to) produce a core file for gdb
}



// for debug, to remove

void checkNextFree()

{ if (ClAlloc->nextFree != NOTHING && ClAlloc->nextFree > ClAlloc->maxSize0) {

    Ctracef("== bug because of cell %d\n",ClAlloc->nextFree);

  clbug();

  }}

CL_INT ISCHUNK(CL_INT n)
{if (n == NOTHING || (n > CmemoryAdr && n < CmemoryAdr + ClAlloc->maxList)) return n;
 else return clbug();}
#else
#define ISCHUNK(n) n
#endif

CL_INT MAXLIST_OFFSET = 2;

/*********************************************************************/
/**    1. Interface methods                                         */
/*********************************************************************/

#define CHECKED_ALLOC(p, t, s) \
  p = (t*)malloc((s) * sizeof(t)); \
   if (p == 0) CL_error_alloc();
   

// init
// contains all the calls to malloc for CLAIRE
void ClaireAllocation::init() {
  CL_INT i;
  CHECKED_ALLOC(ClRes, ClaireResource, 1)
  CHECKED_ALLOC(ClRes->sTable, symbol*, maxHash + 1)
  CHECKED_ALLOC(ClRes->ascii, ClaireChar*, 512)
  CHECKED_ALLOC(ClRes->haiStack, OID*, maxHist) // address part of the stack
  CHECKED_ALLOC(ClRes->hviStack, OID, maxHist) // value part of the stack
  CHECKED_ALLOC(ClRes->haoStack, OID*, maxHist) // address part of the stack
  CHECKED_ALLOC(ClRes->hvoStack, ClaireObject*, maxHist) // value part of the stack
  CHECKED_ALLOC(ClRes->hafStack, double*, maxHist) // address part of the stack
  CHECKED_ALLOC(ClRes->hvfStack, double, maxHist) // value part of the stack
  CHECKED_ALLOC(gcStack, ClaireAny*, maxGC) // GC stack  (v 3.2.38)
  CHECKED_ALLOC(CmemoryAlloc, OID, maxSize0+2) // GC stack  (v 3.2.38)
  Cmemory = CmemoryAlloc;
  Cmemory++;
  //<sb> mem upper bound for CLMEM check
  CmemoryMax = Cmemory + maxSize0;
  CmemoryAdr = ((CL_UNSIGNED)Cmemory >> ADDRTRANS);
  //<sb> flag that tell if claire exits -> can we free stdio (cf clPort) ?
  freeingAll = 0;
  nextFree = NOTHING;
  if (maxList0 % 2 != 0) MAXLIST_OFFSET = 1;
  else MAXLIST_OFFSET = 2;
  firstFree = maxList0 + MAXLIST_OFFSET;    // needs to be even for alignment ! used in sweep
  alertFree = maxList0 + 5 * maxSize / 6;
  maxMem = maxList0 + maxSize;
  mem_auto = (maxMem != maxSize0);
  if(mem_auto) alertFree = maxList0 + 7 * maxSize / 10;
  else alertFree = maxList0 + 5 * maxSize / 6;
  statusGC = 0;              // we like GC, don't we ?
  memset(ClRes->sTable, 0, 4 * (maxHash + 1)); //for (i=0; i <= maxHash; i++) ClRes->sTable[i] = NULL;
  hashMask = ((1ul << (log2up(maxHash) - 1)) - 1);
  // initialization of the Chunk allocation mechanisms: entryList and chained lists (FOLLOW,PREVIOUS)
  //<sb> no known free chunck of size i (< logList) at startup
  for(i = 0; i < logList; i++) entryList[i] = NOTHING;
  entryList[logList] = CmemoryAdr; //<sb> root element of the free chunck chain
  Cmemory[0] = (1ul << logList); //<sb> initialize the first free chunck
  Cmemory[CAR] = NOTHING;
  Cmemory[PREVIOUS] = NOTHING;
  Cmemory[FOLLOW] = NOTHING;
  usedCells = 0;
  base = 0;                     // gc stack base
  index = 1;
  probe = NULL;                // v3.0.4
  ClEnv = (ClaireEnvironment*)makeStatic(sizeof(ClaireEnvironment) / sizeof(CL_INT) + 2  );
  memset(ClEnv, 0, sizeof(ClaireEnvironment));
  CHECKED_ALLOC(ClEnv->handlers, jmp_buf, maxEnv) // handler stack
  CHECKED_ALLOC(ClEnv->stack, CL_INT, maxStack) // eval stack
  currentNew = NULL;                                                // v3.0.60
  numGC = 0;                                                        // v3.2.50
  consumed_exec = 0;
  consumed_gc = 0;
  object_hits = 0;
  chunk_hits = 0;
  msec(origin_exec);
}

//<sb> here we allocate claire memory
// if you use claire as a shared library
// you'll need to call it by hand
// i & j corresponds to option '-s i j'
CL_INT allocateClaire(CL_INT i, CL_INT j, CL_INT memauto) {
  ClAlloc = new ClaireAllocation;
  if(ClAlloc == 0) CL_error_alloc();
  ClAlloc->logList = 18 + i;
#ifdef __LP64__
  if(LOGO) fprintf(stdout,"Loglist = %ld\n", ClAlloc->logList);
#else
  if(LOGO) fprintf(stdout,"Loglist = %d\n", ClAlloc->logList);
#endif  
  ClAlloc->maxList = (1ul << (18 + i));
  ClAlloc->maxSize = (1ul << (18 + i));
  if(memauto) {
    ClAlloc->maxList0 = (1ul << (18 + 10));
    ClAlloc->maxSize0 = (2ul << (18 + 10));
    ClAlloc->maxStack = 8000 * (1ul << 10);
  } else {
    ClAlloc->maxList0 = (1ul << (18 + i));
    ClAlloc->maxSize0 = (2ul << (18 + i));
    ClAlloc->maxStack = 8000 * (1ul << j);
  }
  ClAlloc->maxGC = 20000 * (1ul << j);
  
  ClAlloc->maxHist = 10000 * (1ul << j);
  ClAlloc->maxEnv = 400 * (1ul << j);
  ClAlloc->maxHash = ((1ul << (11 + i)) + 200);       // <yc> 7/98 Changed for claire3 !
  ClAlloc->hashMask = ((1ul << (11 + i)) - 1);
  ClaireResource::run();
  
  claire_runs = 1;
  
  return ClRes && ClAlloc &&
    Cmemory &&
    ClRes->sTable && ClRes->ascii && ClRes->haiStack &&
    ClRes->hviStack && ClRes->haoStack && ClRes->hvoStack &&
    ClRes->hafStack && ClRes->hvfStack && ClEnv->stack &&
    ClEnv->handlers && ClAlloc->gcStack;
}


//<sb> here we free the memory allocated by claire
CL_EXPORT CL_INT freeClaire() {
  claire_runs = 0;
  free(ClEnv->stack);
  free(ClEnv->handlers);
  free(CmemoryAlloc);
  free(ClAlloc->gcStack);
  free(ClRes->hvfStack);
  free(ClRes->hafStack);
  free(ClRes->hvoStack);
  free(ClRes->haoStack);
  free(ClRes->hviStack);
  free(ClRes->haiStack);
  free(ClRes->ascii);
  free(ClRes->sTable);
  free(ClRes);
  delete ClAlloc;
  return 1; }

// bbn check memory params before allocation stuff
CL_EXPORT CL_INT startClaire(CL_INT i, CL_INT j, CL_INT memauto) {
  if (claire_runs == 1) return 0;
  ClAlloc = 0; ClRes = 0;
  return i < 0 || i >= 20 || j < 0 || j >= 20 ? 0 :
        allocateClaire(i,j,memauto);
}

// -qonerror option "Quit on error?"
// claire will exit on the first exception
// with an error code of 0
CL_EXPORT CL_INT QONERROR = 0;
CL_EXPORT CL_INT NOEL = 0;
CL_EXPORT CL_INT SAMPLE_PERIOD = 0;
CL_EXPORT CL_INT MEM_AUTO = 0;

// flag that force gc on each alloction -> gc stress test
// activated by -gcstress
CL_EXPORT CL_INT gcstress = 0;
                  

CL_EXPORT CL_INT startClaire(CL_INT argc, char *argv[]) {
  if (claire_runs == 1) return 0;
  CL_INT l; CL_INT q = 0; CL_INT code = 0; CL_INT main_err = 0;
  CL_INT i = 3, j = 3;
  CL_INT memauto = 0;
  CL_INT add_x_option = 0;
  CL_INT dogcstress = 0;
  if(getenv("SERVER_SOFTWARE")) // we should be a CGI -> no readline, no logo
    { NOEL = 1; LOGO = 0; TOPLEVEL = 0; }
  for (l = 1;l < argc; l++) { // hanlde some options
    if (l == 1 && isfile_ask_string(argv[l]) == CTRUE) {
      add_x_option = 1;
      LOGO = 0;
      TOPLEVEL = 0;
      NOEL = 1;
    } else if(strcmp(argv[l], "-h")==0) {
      LOGO = 0;
      TOPLEVEL = 0;
      NOEL = 1;
    } else if(strcmp(argv[l], "-gcstress")==0) {
      dogcstress = 1;
    } else if(strcmp(argv[l], "-sample")==0) {
      if(++l == argc) break;
      SAMPLE_PERIOD = atoi(argv[l]);
    } else if(strcmp(argv[l],"-x") == 0 || strcmp(argv[l],"-xe") == 0 ||
#ifdef __LP64__		
        sscanf(argv[l],"-x%ld-%ld",&i,&j) == 2 || sscanf(argv[l],"-xe%ld-%ld",&i,&j) == 2)
#else
	    sscanf(argv[l],"-x%d-%d",&i,&j) == 2  || sscanf(argv[l],"-xe%d-%d",&i,&j) == 2)
#endif
	{
      if(++l == argc) break;
      LOGO = 0;
      TOPLEVEL = 0;
      NOEL = 1;
#ifdef __LP64__		
    } else if(strcmp(argv[l],"-xwcl") == 0 || sscanf(argv[l],"-xwcl%ld-%ld",&i,&j) == 2) {
#else
    } else if(strcmp(argv[l],"-xwcl") == 0 || sscanf(argv[l],"-xwcl%d-%d",&i,&j) == 2) {
#endif
      if(++l == argc) break;
      LOGO = 0;
      TOPLEVEL = 0;
      NOEL = 1;
    } else if(strcmp(argv[l],"-qonerror") == 0) QONERROR = 1;
    else if(strcmp(argv[l],"-logo") == 0) LOGO = 1;
    else if(strcmp(argv[l],"-auto") == 0) memauto = 1;
    else if(strcmp(argv[l],"-noel") == 0) NOEL = 1;
    else if(strcmp(argv[l],"-nocolor") == 0) COLOR = 0;
    else if(strcmp(argv[l],"-color") == 0) COLOR = 1;
  }
  CL_INT increase = 0;
  if(argc > 3)
    //<sb> handle '-s i j'
    for(l = 1;l < argc - 2;l++) { 
      if(strcmp("-s", argv[l]) == 0) { 
        i = atoi(argv[l+1]);
        j = atoi(argv[l+2]); increase++; break;
      }
    }
  // force NOLOG for non character device (pipe, file...)
  struct stat sb;
  if(fstat(1, &sb) != -1 && ((sb.st_mode) & S_IFMT) != S_IFCHR) {
    LOGO = 0;
    TOPLEVEL = 0;
    NOEL = 1;
  }
  if(LOGO)
#ifdef __LP64__
    fprintf(stdout,"%s memory size by 2^%ld and 2^%ld, ", increase ? "increase" : "default", i, j);
#else
    fprintf(stdout,"%s memory size by 2^%d and 2^%d, ", increase ? "increase" : "default", i, j);
#endif
  if(startClaire(i, j, memauto) == 0) { // try to allocate claire memory
    CL_error_alloc();
  }

  GC_BIND;
  ClEnv->params = list::empty();
  for (i=0; i < argc; i++) {
    if (i == 1 && add_x_option)
      ClEnv->params->addFast(_string_("-x"));
    ClEnv->params->addFast(_string_(argv[i]));
  }
  GC_UNBIND;
  ClaireHandler c_handle = ClaireHandler();
  if ERROR_IN {
    if(SAMPLE_PERIOD)
      ClAlloc->open_sample_file(SAMPLE_PERIOD);
    gcstress = dogcstress;
    fCallMain();
    if (fClaireStarted)
      fClaireStarted(); //<sb> only once the comman line has been parsed
    if (fServiceFunc && fServiceFunc()) {
      //<sb> windows service mode
    } else {
      parse_command_line_void1();
      CL_exit(0);
    }
  } else {
    c_handle.catchIt();
	{
		if ERROR_IN {
			ClEnv->cout = OBJECT(PortObject,Core.Clib_stderr->value);
			print_any(_oid_(ClEnv->exception_I));
			CL_exit(1);
		} else {
			c_handle.catchIt();
		}

	}
  }
  return 1;
}

CL_EXPORT void CL_exit(CL_INT i) {
  if (no_exit_call) return;
  claire_runs = 0;
  if(SAMPLE_PERIOD) ClAlloc->close_sample_file();
  CL_INT main_err = 0;
  CL_INT code = 0;
  ClaireHandler c_handle = ClaireHandler();
  if ERROR_IN {
    ClAlloc->freeAllFreeable();
  } else {
    c_handle.catchIt();
    ClEnv->cout = OBJECT(PortObject,Core.Clib_stderr->value);
    print_any(_oid_(ClEnv->exception_I));
    princ_string("\n");
  }
  freeClaire();
  if (lastforked || isforked) _exit(i);
  else exit(i);
}

// call to system
CL_EXPORT CL_INT CL_system(char *s) { return system(s); }
  
//<sb> a dynamic allocation failed
void CL_error_alloc() {
  claire_runs = 0;
  fprintf(stderr,"There is not enough memory for CLAIRE, try claire -s 0 0\n");
  exit(1);
}


CL_INT ClaireAllocation::increaseChunk() {
   if(maxList == maxList0 || logList >= MAX_LOGLIST) return 0;
  logList++;
  if (TOPLEVEL)
    Ctracef("Chunk congestion, increase chunk memory (2^%d)\n", logList - 18);
  entryList[logList] = NOTHING;
  entryList[logList-1] = CmemoryAdr + maxList;
  Cmemory[maxList] = (1ul << (logList-1));
  Cmemory[maxList + CAR] = NOTHING;
  Cmemory[maxList + FOLLOW] = NOTHING;
  maxList *= 2;
  consumed_gc = 0;
  consumed_exec = 0;
  chunk_hits = 0;
  return 1;}


CL_INT ClaireAllocation::increaseShort() {
  if(maxMem == maxSize0) return 0;
  maxSize *= 2;
  CL_INT myi = log2up(maxSize) - 19;
  maxMem = maxList0 + maxSize;
  alertFree = maxList0 + 7 * maxSize / 10;
  if (TOPLEVEL)
    Ctracef("Short congestion, increase short memory (2^%d)\n", myi);
  consumed_gc = 0;
  consumed_exec = 0;
  object_hits = 0;
  return 1;}


//<sb> congection device now time based
CL_INT ClaireAllocation::chunkCongestion() {
  if (chunk_hits > 3) chunk_hits = 4;
  return chunk_hits > 3 &&
        3. * (double)consumed_gc > (double)consumed_exec;
}

CL_INT ClaireAllocation::shortCongestion() {
  if (object_hits > 3) object_hits = 4;
  return object_hits > 3 &&
        3. * (double)consumed_gc > (double)consumed_exec;
}

CL_INT ClaireAllocation::gcStackCongestion() {
  CL_INT good = 0;
  if(mem_auto) {
    void *adr = realloc(gcStack, 2 * maxGC * sizeof(ClaireAny*));
    if(adr) {
      gcStack = (ClaireAny**)adr;
      maxGC *= 2;
      good = 1;
      CL_INT igc = 0;
      for(; maxGC > 20000 * (1ul << igc);igc++) ;
      if (TOPLEVEL)
        Ctracef("GC stack congestion, increase memory (2^%d).\n", igc);
     }}
  return good;}

/*********************************************************************/
/**    2. Allocation methods                                         */
/*********************************************************************/

// note: new* methods return an integer value relative to &Cmemory[O]
//       make* methods return a true pointer

CL_INT ClaireAllocation::checkChunkIncrease(CL_INT idx, CL_INT n) {
  if(increaseChunk())
    return newChunk(n);
  Kernel.GcError->index = idx;
    Kernel.GcError->value = n;
    Kernel.GcError->arg = 0;
    close_exception((ClaireException *)Kernel.GcError);
    return 0;
}

CL_INT ClaireAllocation::gcChunk(CL_INT n, CL_INT size, CL_INT *value, CL_INT *i) {
  chunk_hits++;
  gc("Chunk");                // we have not found a free (larger) chunk
  if (size >= logList) checkChunkIncrease(2,n);
  if (entryList[size] != NOTHING)
    {*value = entryList[size];
     entryList[size] = ISCHUNK(ADRTOPOIN(*value)[FOLLOW]);        
    return 1;}
  for (*i = size + 1; entryList[*i] == NOTHING; (*i)++)
    if (*i == logList) {
      *value = checkChunkIncrease(2,n);
      return 1;
    }
  return 0;
}

CL_INT inside_gc = 0;
CL_INT sampling = 0;

// allocate the space for a chunk of n items
// entryList[size] is either a free chunk or NOTHING (free chunks are chained)
// in that case, we need to cut a larger chunk into two pieces (recursively)
// if needed we call the garbage collector to free more chunks
// A free chunk i is organized as follow
//     Cmemory[x + CAR]   = NOTHING  (to know that the chunk is free)
//     Cmemory[x + FOLLOW]  = address of next free chunk of same size
//     Cmemory[x + PREVIOUS] = address of the previous chunk in the chain
CL_INT ClaireAllocation::newChunk(CL_INT n)
{
//	printf("newChunk\n");
//	printf("**** %ld\n", n);
  if (gcstress == 1) gc("StressChunk");
#ifdef CLDEBUG
 if(inside_gc) Ctracef("Warning: newChunck inside gc\n"); 
#endif
 CL_INT value;
 CL_INT size,next,i,j;
 // n *= 2;
  size = log2up(n) ;                          /* note that 2^size is always > n */
// printf("ClaireAllocation::newChunk(%ld) size:%ld\n",n,size);
  if (size > logList) return checkChunkIncrease(1,n);
  if (entryList[size] == NOTHING) //<sb> not a free chunck! we have to find a chunck of a possible bigger size
     { 
		 for (i = size; entryList[i] == NOTHING; i++) //<sb> find a free chunck of sufficent size	 
         if (i > logList) break; //<sb> exceed memory allocation (-s i j -> logList = 18+i)
       for (j = i + 1; j <= logList; j++) //<sb> search a chunck larger than i that isn't free 
           if (entryList[j] != NOTHING) break;
       if ((i > logList) || (i < logList - 1 && j > logList))  // new anti-fragmentation device
           if (gcChunk(n, size, &value, &i))
	   {
		   printf("???????????????\n");
			 return value;}
       value = entryList[i];
	   CL_UNSIGNED _idx = (&(ADRTOPOIN(value)[FOLLOW])) - Cmemory;
	   
	  /* 	   printf("i = %lu    value = %lu  addr %lx  FOLLOW : %lu  	addre follow:  %lu %lu\n",i,value,&(ADRTOPOIN(value)[FOLLOW]),ADRTOPOIN(value)[FOLLOW],
	   		(&(ADRTOPOIN(value)[FOLLOW])) - Cmemory,
			_idx
	    ); */
	   
       entryList[i] = ISCHUNK(ADRTOPOIN(value)[FOLLOW]);  // update next free chunk
	//	  printf("cuts\n");
       for (j = i; (j != size); j--)            // cuts into two until right size
           {CL_INT x = (1ul << (j-1));			// 2^(j- 1) :> taille du block
           next = (CL_UNSIGNED)value + x;		// next = base actuelle + taille du block
//		   print("x = %ul \n", );
		   
           CL_UNSIGNED *nx = ADRTOPOIN(next);
           *nx = x;
           nx[FOLLOW] = NOTHING;
		   // printf("** x =%lu  next:%ld  adr:j:%d %ld  ---- %d => %lx %lx \n ",x,
			//		next,j,((CL_INT)(nx) >> 2) - CmemoryAdr , ((CL_INT)(&nx[FOLLOW]) >> 2) - CmemoryAdr, nx[FOLLOW], &(nx[FOLLOW]));
           nx[CAR] = NOTHING;
           entryList[j - 1] = ISCHUNK(next);}
       *ADRTOPOIN(value) = (1ul << size);}
   else
     {
		 value = entryList[size];
//         entryList[size] = ISCHUNK(Cmemory[value + FOLLOW]);
//			printf("Use free chunk %ld (%ld) add next  entry list : %lp  FOLLOW:%ld\n",
//					(value - CmemoryAdr),ADRTOPOIN(value),ADRTOPOIN(value)[FOLLOW],FOLLOW);
		 
           entryList[size] = ISCHUNK(ADRTOPOIN(value)[FOLLOW]);
	   }
   			usedCells += *ADRTOPOIN(value);                 // book-keeping
//			printf("****** %d\n", Cmemory[50]);
   
//   printf("newChunk() ==> %ld (%#lx)  %ul  \n",(value - CmemoryAdr),value,Cmemory[26]);
   return value;}

// allocation of a short object: this is much simpler and uses a chain of small blocks
// of size OPTIMIZE
CL_INT ClaireAllocation::newShort(CL_INT n)
{
//	printf("newShort(%ld)\n",n);
//	printf("ClaireAllocation::newShort(%ld)\n",n);
  if (gcstress == 1) gc("StressShort");
 #ifdef CLDEBUG
  if(inside_gc) Ctracef("Warning: newShort inside gc\n");  
 #endif
  CL_INT value;
  if (nextFree != NOTHING)                     // chain is not empty
     {
//		 printf(" nextFree :%ld \n",nextFree);
		value = nextFree;
      
      nextFree = Cmemory[nextFree+1];
      #ifdef CLDEBUG
      checkNextFree(); // little trick to check that values are OK
      #endif
	  Cmemory[value] = n;
      }
  else {if (firstFree > alertFree) // chain is empty
         {object_hits++;
          gc("Object");
          if (nextFree != NOTHING) return newShort(n);
          else return newLong(OPTIMIZE); //<sb> was newLong(n);
        } else {value = firstFree;
              Cmemory[value] = n;
              firstFree += OPTIMIZE;}}
//  printf("newShort @ %ld [ %ld] => (%#ld)\n",(long)Cmemory,value,(long)(CmemoryAdr + value));
  return CmemoryAdr + value;}


// allocation of a long object is pure stacking
CL_INT ClaireAllocation::newLong(CL_INT n)
{ 
#ifdef CLDEBUG
 if(inside_gc) Ctracef("Warning: newLong inside gc\n");  
#endif
  if (n % 2 == 0) n++;

  CL_INT newFirstFree = firstFree + (n + 1);
//  printf("newLong(%ld) firstFree=%ld newFirstFree=%ld\n",n,firstFree, newFirstFree);
  if (newFirstFree > maxMem) { //<sb> check memory space before modifying memory
    if(increaseShort()) return newLong(n);
    Kernel.GcError->index = 3;
    Kernel.GcError->value = n;
    Kernel.GcError->arg = 0;
   close_exception((ClaireException *)Kernel.GcError);
  }
  CL_INT value;
  value = firstFree;
  Cmemory[firstFree] = n;
  firstFree = newFirstFree;
//  printf("%lx ")
  return CmemoryAdr + value;
}

// allocation of a long object is pure stacking
ClaireAny *ClaireAllocation::makeStatic(CL_INT n)
{return (ClaireAny *)((newLong(((n < OPTIMIZE) ? OPTIMIZE : n)) + 1) << ADDRTRANS);}


// we allocate the string so that it looks like an imported but is is really special
// string is an import on a char* that is itself allocated by CLAIRE (with a primitive
// isa marking)
//<sb> now take the string length as arg (not the cell size)
char *ClaireAllocation::makeString(CL_INT n)
{CL_INT m;
  CL_INT cells = n / sizeof(CL_INT) + sizeof(CL_INT); //<sb> convert length to cells (+ 1 (4 bytes) for null char)
  if(cells < OPTIMIZE) cells = OPTIMIZE;
  m = newChunk(cells);
  CL_UNSIGNED *a = ADRTOPOIN(m);
  a[1] = (CL_UNSIGNED) Kernel._string;     // allows for a simpler string pushing
  a[2] = (CL_UNSIGNED) n; //<sb> buffer length - negative means string and >= 0 means buffer
  char* res = (char*)(a + 3);
  res[n] = 0; //<sb> set the null char
  return res;}

// similar trick: allocation for an array
// we allocate both the container and the contents thus
OID *ClaireAllocation::makeArray(CL_INT n, ClaireType *t)
{CL_INT m = newChunk(((t == Kernel._float) ? (2 * n) : n) + sizeof(CL_INT)); // v3.2.34 : 4 vs. 3 is necessary for some strange reason
  CL_UNSIGNED *a = ADRTOPOIN(m);
  a[1] = (CL_UNSIGNED) Kernel._array;
  a[2] = (CL_UNSIGNED) t;
  a[3] = (CL_UNSIGNED)n;
  return (OID *)(a + 3);}


// creates an imported object
// notice the automatic protection, which is why the compiler does not protect constants from gc,
// since further optimization are meant to remove the use of import
OID ClaireAllocation::import(ClaireClass *c, OID *x)
{ if (c == Kernel._string) GC_STRING((char *) x);               // v3.2.01 -> protect the content
 OID adr = 1 + newShort(3);
 ClaireImport *obj = (ClaireImport *)(adr << ADDRTRANS);
   if (ClAlloc->statusGC != 2)  GC_PUSH(obj);                   // v3.1.06 -> protect the container, v3.2.30 check stack
   obj->isa = c;
   obj->value = (CL_INT) x;
   return OBJ_CODE + adr;}

// a function is a system object (sort = object) allocated with a special
// method 
ClaireFunction *ClaireAllocation::makeFunction(fptr f,char* s)
{  GC_STRING((char *) s);
  ClaireFunction *obj = (ClaireFunction *)((newShort(sizeof(ClaireFunction) / sizeof(CL_INT)) + 1) << ADDRTRANS);
   if (ClAlloc->statusGC != 2)  GC_PUSH(obj);                   // v3.1.06 -> protect the container, v3.2.30 check stack
    obj->isa = Kernel._function;
    obj->value = (CL_INT) f;
    obj->name = s;
    return obj;}

// creates a function without a body
OID error_undefined_function(void)
{Cerror(31,0,0); return 1;}


CL_EXPORT ClaireFunction *make_function_string(char *s)
{return ClAlloc->makeFunction((fptr) error_undefined_function,s);}

/***********************************************************************/
/**    3. Memory De-allocation   ---------------------------------     */
/***********************************************************************/


//  de-allocation of a chunk of dynamic memory,
//  the returned value is important, it is the address of the next chunk for the
//  sweep loop
CL_INT ClaireAllocation::freeChunk(CL_INT n) {
  CL_UNSIGNED *nl = ADRTOPOIN(n);//Cmemory[n];             /* real length of the allocated space */
  CL_INT l = *nl;//Cmemory[n];             /* real length of the allocated space */
  
  #ifdef CLDEBUG
    CL_INT size,j;
    size = log2up(l) - 1;
    if (l != (1ul << size))
     Ctracef("free ADR %d causes a bug (size = %d not a chunk)\n",n,l);
    ASSERT(l == (1ul << size));
  #endif
  usedCells -= l;
  if (gcstress) {
    CL_INT j;
     for(j=3; j < l; j++)
       *((CL_UNSIGNED*)((n+j) << ADDRTRANS)) = (from_kill_I ? 0xDEADBEEF : 0xFACEBADD);
  }
  return freeLoop(n);}

// we first check if it can be merged with its twin
//  if yes we do it, otherwise we just free the space
// a twin is the adjacent chunk of the same size, which can be on the left or the
// right
CL_INT ClaireAllocation::freeLoop(CL_INT n)
{CL_UNSIGNED *l = ADRTOPOIN(n);
 CL_INT size = log2up(*l) - 1;
 CL_UNSIGNED z = (CL_UNSIGNED)n - CmemoryAdr;
  if (((z >> size) & 1) == 0) // determines if the twin is on the right
     {CL_UNSIGNED *nl = l + *l;
     if ((*nl == *l) && (nl[CAR] == NOTHING))
          return mergeRight(n, POINTOADR(nl), size);
      else return freeSimple(n,size);}
  else                       // twin is on the left
     {CL_UNSIGNED *nl = l - *l;
     if ((*nl == *l) && (nl[CAR] == NOTHING))
          return mergeLeft(POINTOADR(nl), n, size);
      else return freeSimple(n,size);}}

// giving back a list to the data zone
CL_INT ClaireAllocation::freeSimple(CL_INT n, CL_INT size)
{ 
	// printf("ClaireAllocation::freeSimple\n");
	CL_INT esize = entryList[size];
  if (esize != NOTHING)
    ADRTOPOIN(esize)[PREVIOUS] = n;
  CL_UNSIGNED *m = ADRTOPOIN(n);
  m[CAR] = NOTHING;
  m[FOLLOW] = esize;
  m[PREVIOUS] = NOTHING;
  entryList[size] = n;
  return n;}

CL_INT ClaireAllocation::mergeRight(CL_INT a, CL_INT b, CL_INT size) {
  CL_UNSIGNED *bb = ADRTOPOIN(b);
  if (entryList[size] == b)    // b is the first free of this size
      entryList[size] = bb[FOLLOW];
  else
     { CL_UNSIGNED previous = bb[PREVIOUS];
       CL_UNSIGNED follow = bb[FOLLOW];
//	   printf("ClaireAllocation::mergeRight follow [%ld] = %ld\n",(previous - CmemoryAdr + FOLLOW), follow);
       ADRTOPOIN(previous)[FOLLOW] = follow;
       if (follow != NOTHING)
         ADRTOPOIN(follow)[PREVIOUS] = previous;}
  *ADRTOPOIN(a) *= 2;
  return freeLoop(a);}

// symetrical: b is the new one
CL_INT ClaireAllocation::mergeLeft(CL_INT a, CL_INT b, CL_INT size) {
  CL_UNSIGNED *aa = ADRTOPOIN(a);
  if (entryList[size] == a) // a is the first free cell 
     entryList[size] = (CL_INT)aa[FOLLOW];
  else
     { CL_UNSIGNED previous = aa[PREVIOUS];
       CL_UNSIGNED follow = aa[FOLLOW];
//	   printf("ClaireAllocation::mergeLeft follow [%ld] = %ld\n",(previous - CmemoryAdr + FOLLOW), follow);
       ADRTOPOIN(previous)[FOLLOW] = follow;
       if (follow != NOTHING)
           ADRTOPOIN(follow)[PREVIOUS] = previous;}
  *aa *= 2;
  return freeLoop(a);}


//  desallocation if any need, (instruction object) of the memory zone
void ClaireAllocation::freeObject(CL_INT n) {
 n = (CL_UNSIGNED)n - CmemoryAdr;
 if (gcstress) {
   CL_INT i = 2;
  for(;i < OPTIMIZE; i++) Cmemory[n+i] = (from_kill_I ? 0xDEADBEEF : 0xFACEBADD);
 }
 if (Cmemory[n] < OPTIMIZE) {
    Cmemory[n+1] = nextFree;
      Cmemory[n] = 0;
    #ifdef CLDEBUG
      if (n == BadGuy)
         Ctracef("====== free bad guy -> %d\n", nextFree);
    #endif
      nextFree = n;
      #ifdef CLDEBUG              // useful
      checkNextFree();
      #endif
      }}


// free a string
void ClaireAllocation::freeString(char *s)
{ if CLMEM(s)
   {CL_UNSIGNED x = POINTOADR(s) - 3; //<sb> -2 for buffer string
    freeChunk(x);}}


/*********************************************************************/
/**    3. Garbage Collection                                         */
/*********************************************************************/

// mark a cell ! [v3.1.04 use a macro => easier to read + debug]
//<sb> made it inline -> save some double call to ADR 
static inline void MARKCELL(CL_INT n) {CL_INT* x = (CL_INT*)((CL_UNSIGNED)n << ADDRTRANS); x--; *x = -*x;}


// call the garbage collector
// this is a classical mark&sweep designed that has shown to be robust & fast
void ClaireAllocation::gc(char *cause) {
  CL_INT tgc;
  if (LOGO) Ctracef("GC %d start\n", numGC);
  msec(tgc);
  consumed_exec += (tgc - origin_exec);
   if(sampling) sample_once();
  inside_gc++;
  if (statusGC == 2) Cerror(27,0,0);                                     // v3.1.12  -> no GC allowed !
  delayedThings = 1; //<sb> use a flag instead of PUSH for things -> reduce recursivity / preserve stack
  if(inside_gc == 1) markFreeableContainer(); //<sb> have to be the first marked entity!
  markStack();
  markHash();
  if(inside_gc == 1) updateFreeme();
  //<sb> mark the current new object(new object or bag type)
  // note : always the last marked cell since it can be a
  // class and it would be dangerous to have a class container
  // marked at first
    if (currentNew != NULL) {
      OID n = _oid_(currentNew);
      if (SIZE(n) > 0) { // unless it as alreay been mark
	object_used += SIZE(n);
    MARKCELL(n);}
  }
    if (currentType != NULL) {
      OID n = _oid_(currentType);
    if (SIZE(n) > 0) { // unless it as alreay been mark
    object_used += SIZE(n);
    MARKCELL(n);}
  }
  sweepChunk();
  sweepObject();
  if(inside_gc == 1) sweepFreeable();
  CL_INT tegc;
  msec(tegc);
  consumed_gc += (tegc - tgc);
  if(inside_gc == 1) {
      if(shortCongestion()) increaseShort();
    if(chunkCongestion()) increaseChunk();
  }
  msec(origin_exec);
  if (LOGO) Ctracef("GC %d end\n", numGC);
  inside_gc--;
  if(sampling) sample_once();
  numGC++;
}

#define MARK(n) { CL_INT nn = n; if (CTAG(nn) == OBJ_CODE && SIZE(nn) > 0) mark(nn); }

//<sb> NOTE: freeable instances is filled at startup with standard io ports
// which have a particular protection until claire ends.
// This protection is acheive by starting the iteration of the instance
// list at the fourth element.

//<sb> mark the freeable container but not the contained freeable objects
void ClaireAllocation::markFreeableContainer() {
 list *l = Kernel._freeable_object->instances;
 MARKCELL(_oid_(l)); // mark the list
 (*l)[0] = -((*l)[0]); // and its content
}

//<sb> here we check whether a freeable object has been marked or not
// and we update its freeme? slot accordingly
// as we don't want to free an unmarked freeable object until we have called
// free! we perfrom a mark on it
void ClaireAllocation::updateFreeme() {
 list* l = Kernel._freeable_object->instances;
 CL_INT i, len = l->length;
 for (i = 1;i <= len;i++)
    {OID n = (*l)[i];
    FreeableObject *x = OBJECT(FreeableObject,n);
    if (x == probe) {
#ifdef __LP64__
        printf("updateFreeme of probe %ld [%s]\n", SIZE(n), x->isa->name->name);
#else
      printf("updateFreeme of probe %d [%s]\n", SIZE(n), x->isa->name->name);
#endif
    }
    x->freeme_ask = (SIZE(n) > 0 ? CTRUE : CFALSE);}
 //<sb> now that we have updated the freeme? slot
 // we ensure that object that are to be freed are marked 
 for (i = 1;i <= len;i++)
    {OID n = (*l)[i];
    if(SIZE(n) > 0) MARK(n);}}

//<sb> we have kept all freeable objects and now check their freeme? slot
// such to free! objects that need to. The allocated cell will be freed on the next gc...
void ClaireAllocation::sweepFreeable() {
 list* l = Kernel._freeable_object->instances;
 CL_INT i;
 CL_INT len = l->length;
  OID *ct = l->content;
 property &prop_prefree = *Kernel.prefree_I;
 for (i = 1;i <= len;i++)
    {OID n = ct[i];
    FreeableObject *x = OBJECT(FreeableObject,n);
    if (x->freeme_ask == CTRUE) {
      if (x == probe) {
        printf("prefree the freeable probe [%s]\n", x->isa->name->name);
      }
      prop_prefree(n);
    }}

  property &prop_free = *Kernel.free_I;
  i = 1;
  CL_INT inspos = 0;
  for (;i <= len;i++) {
    OID n = ct[i];
    FreeableObject *x = OBJECT(FreeableObject,n);
    if (x->freeme_ask == CTRUE) {
      if (x == probe) {
        printf("free the freeable probe [%s]\n", x->isa->name->name);
      }
      prop_free(n);
    } else {
      ct[++inspos] = ct[i];
    }
  }
  l->length = inspos;
}


//<sb> when claire exits we free any freeable entity
void ClaireAllocation::freeAllFreeable() {
 freeingAll = 1;
 list* l = Kernel._freeable_object->instances;
 CL_INT i;
 for (i = 1;i <= l->length;i++)
    {OID n = (*l)[i];
    (*Kernel.prefree_I)(n);}
 while(l->length > 0)
    {OID n = (*l)[l->length];
    l->length--;
    (*Kernel.free_I)(n);}}

// marks all the object contained in the hash table.
void ClaireAllocation::markHash() {
 CL_INT i;
 MARK(_oid_(ClEnv->moduleStack))
 MARK(_oid_(Kernel.GcError))
 for (i = 0; i < 256; i++) MARK(_oid_(ClRes->ascii[i]))
 delayedThings = 0; //<sb> we can now mark classes
 for (i = 0; i < maxHash; i++)
     {symbol *x = ClRes->sTable[i];
      if (x != NULL)
         {OID n = _oid_(x);
          if(SIZE(n) > 0) {
              symbol_used += SIZE(n);
        MARKCELL(n);
        char* s = x->name;
        if CLMEM(s) { // a CLAIRE string
          CL_INT *ss = (CL_INT*)s - 3;
        if (*ss > 0) {
          string_used += *ss;
          *ss = -*ss;
        }
        } }
      MARK(x->value) }}}

  
// mark the items in the various stacks
void ClaireAllocation::markStack() {
 CL_INT i;
// printf("MARK stack index is = %d\n", ClEnv->index);
 for (i=0; i < ClEnv->index; i++)
   {CL_UNSIGNED oid = ClEnv->stack[i];
  if CLMEM((oid << ADDRTRANS)) MARK(oid)}
 for (i=1; i < index; i++)
    {ClaireAny *x = gcStack[i];
    if CLMEM(x) MARK(_oid_(x))} //<sb> use CLMEM to check that the address is OK
 for (i=1; i <= ClRes->oIndex; i++)
    { ClaireObject *x = ClRes->hvoStack[i];
      if (x) MARK(_oid_(x)) }      // v3.3.28: MARKCELL + markObject !
 for (i=1; i <= ClRes->iIndex; i++) MARK(ClRes->hviStack[i])}      // CL_INT or ANY !




// marks anything seen (an OID)
// note: MARKCELL mark the cell
//<sb> v3.3.33 made mark & markAny a single function
// we use a flag delayedThings instead of PUSHing
//<sb> made mark the unique marking function, avoid func call overhead
// + if possible, perform tail recursion with a goto
void ClaireAllocation::mark(OID n) {
  goto themark;
markany:
  if (CTAG(n) != OBJ_CODE || SIZE(n) <= 0) return;
themark:
  ClaireAny *x = OBJECT(ClaireAny, n);
  if (x == probe) {
#ifdef __LP64__
    printf("marking probe (0x%llx)\n", (CL_UNSIGNED CL_INT)probe);
#else
    printf("marking probe (0x%x)\n", (CL_UNSIGNED CL_INT)probe);
#endif
  }
  ClaireClass *c = x->isa;
  if (!(delayedThings && c == Kernel._class)) {
    CL_UNSIGNED len;
    OID* aa;
    CL_INT cellsize = SIZE(n);
    MARKCELL(n);
    if (c == Kernel._string) {
      string_used += cellsize;
      char* s = (char*)((ClaireImport*)x)->value;
      if CLMEM(s) { // a CLAIRE string
        CL_INT *ss = (CL_INT*)s - 3;
        if (*ss > 0) {
          string_used += *ss;
          *ss = -*ss;
        }
      }
    } else if INHERIT(c,Kernel._bag) {
      bag_used += cellsize;
      bag *b = (bag*)x;
      aa = b->content;
      if (aa) {
        CL_INT bs = aa[0];
        if (bs > 0) {
          bag_used += bs;
          len = b->length;
          aa[0] = -bs; // should use a MARKCELL
          for (; len > 0; len--) {
            #ifdef CLDEBUG
              if (ClEnv->verbose > 10) Ctracef("bag[%d] -> %d\n", len, aa[len]);
            #endif
            MARK(aa[len])
          }
        }
      }
      if (b->of) { // v3.1.04 !!!
        n = _oid_(b->of);
        goto markany;
      }
    } else if (c == Kernel._array) {
      aa = (OID*)x + 2;
      CL_INT *cell = (CL_INT*)x - 1;
      ClaireType *t = ARRAYTYPE(aa);
      if (*cell > 0) {
        array_used += *cell;
        *cell = -(*cell);
        if (t != Kernel._float) {
          len = aa[0];
          for (; len > 0; len--) MARK(aa[len])
        }
      }
      if (t) { // v3.1.04 !!!
        n = _oid_(t);
        goto markany;
      }
    } else {
      object_used += cellsize;
      if (c == Kernel._function) {
        char* s = ((ClaireFunction*)x)->name;
        if CLMEM(s) { // a CLAIRE string
          CL_INT *ss = (CL_INT*)s - 3;
          if (*ss > 0) {
            string_used += *ss;
            *ss = -*ss;
          }
        }
      }
      list *l = c->slots;
      CL_INT llen = l->length;
      if (llen > 1) {
        OID *CLcurrent,*CLlast;
        slot *sl;
        CL_INT z;
        OID* cont = l->content;
        CLcurrent = cont + 1; //<sb> skip isa that is known to be a class
        CLlast = cont + llen;
        for (;CLcurrent <= CLlast;CLcurrent++) { //<sb> skip the isa marker and stop before the last slot
          sl = OBJECT(slot,*CLcurrent);
          z = *SLOTADR(x, sl->index);
          if (z != 0) {
            c = (ClaireClass*)sl->srange;
            // we need to go through mark to perform the MARKCELL routine ! (v3.1.04)
            if (c == Kernel._object) MARK(_oid_(z))
            else if (c == Kernel._any) MARK(z)
            else if (c == Kernel._string) {
              char* s = (char*)z;
              if CLMEM(s) { // a CLAIRE string
                CL_INT *ss = (CL_INT*)s - 3;
                string_used += *ss;
                if (*ss > 0) *ss = -*ss;
              }
            } else if (c == Kernel._array) {
              aa = (OID*)z;              // index in Cmemory
              CL_INT *cell = (CL_INT*)(aa - 3);
              ClaireType *t = ARRAYTYPE(aa);
              if (*cell > 0) {                   // avoid mark => perform test !
                array_used += *cell;
                *cell = -(*cell);
                if (t != Kernel._float) {
                  len = aa[0];
                  for (; len > 0; len--) MARK(aa[len]);
                }
              }
              if (t) MARK(_oid_(t))     // v3.1.04 !!!
            }
          }
        }
      }
    }
  }
}


//  go through the array of items
void ClaireAllocation::sweepChunk()
{ OID i = 0; CL_INT p;
 while (i < maxList-1)
  {p = ((CL_INT*)Cmemory)[i];
   ASSERT(p != 0);
   if (p < 0) {
       ((CL_INT*)Cmemory)[i]= -p;          // chunk was marked -> keep it
     rchunk_used -= p; }
   else if (Cmemory[i + 1] != NOTHING) { // chunk was not marked and is being used
        i = freeChunk(CmemoryAdr + i) - CmemoryAdr;}
   chunk_used += Cmemory[i];
   i = i + Cmemory[i];}}

void ClaireAllocation::sweepObject()
{ CL_INT i = maxList0 + MAXLIST_OFFSET;  // first free position (defined in claire.cp) //<sb> was maxList + 2 thx <fxj> -> solaris
 CL_INT p;
 while (i < firstFree) {
    p = (CL_INT)Cmemory[i];
    if (p < 0)                                  // marked short
       {p = -p;
         rshort_used += p;
        Cmemory[i] = p;
        p++;
    } else if (p != 0) {
         if (Cmemory[i + 1] != (OID) Kernel._function) 
           freeObject((CL_UNSIGNED)i + CmemoryAdr);
         p++; }
    if (p < OPTIMIZE) p = OPTIMIZE;
    short_used += p;
    i = i + p;}
}


// this is a small useful method for debugging
// new in v3.0.54
void checkOID(OID n)
{if (INTEGERP(n)) return;
 CL_INT u = ADR(n);
 CL_UNSIGNED *mem_u = (CL_UNSIGNED*)(n << ADDRTRANS) - 1;
 if (ClAlloc->numGC > 0)
   { if (mem_u[0] == 0)
       {Ctracef("OID %d has size 0!\n", n);
        Cerror(-1,(OID)"corrupted memory", 0);}
     if (mem_u[1] == NOTHING)
       {Ctracef("OID %d has been freed\n", n);
        Cerror(-1,(OID)"corrupted memory", 0);}
     ClaireClass * c = OWNER(n);
     if (c->isa != Kernel._class)
       {Ctracef("OID %d has a corrupted owner 0x%x !\n", (CL_INT)n, (CL_UNSIGNED CL_INT)c->isa);
    Cerror(-1,(OID)"corrupted memory", 0);} }}


/*********************************************************************/
/**    4. Interface functions & Compiler functions                   */
/*********************************************************************/

void ClaireAllocation::kill(OID n)
{if  (CTAG(n) == OBJ_CODE)
  {
  from_kill_I = 1;
   ClaireAny *x = OBJECT(ClaireAny,n);
   CL_INT i = ADR(n);
   ClaireClass *c = x->isa;
   if (c == Kernel._list || c == Kernel._set || c == Kernel._tuple)
        {CL_INT u =  POINTOADR(((bag*)x)->content); //<sb> fix was: POINTOADR(x) - 3;
          if (SIZE(u) < OPTIMIZE) freeObject(u);
          else freeChunk(u);
          freeObject(i);}
   else if (c == Kernel._string)
        {freeString((char *) ((ClaireImport *) x)->value);
         //freeObject(i);
         }
   else if INHERIT(c,Kernel._freeable_object) {         //<sb>
       list* l = Kernel._freeable_object->instances;
       delete_bag(l,n);
       (*Kernel.free_I)(n); }
   else if INHERIT(c,Kernel._cl_import)          // v3.2.40
        {//(*Kernel.free_I)(n);                 // this allows to free the memory for the import
         freeObject(i);}                      // free the OID = import container
   else if (c == Kernel._array)
         freeChunk(i);
   else if (c == Kernel._symbol)
         {symbol *s = ((symbol *) x);
          ClRes->sTable[s->module_I->hash(s->name)] = NULL;
          freeObject(i);}
   else { ASSERT((INHERIT(c,Kernel._object) || INHERIT(c,Kernel._type)));
          if (SIZE(n) < OPTIMIZE) freeObject(i);
          else if (i < maxList) freeChunk(i);}
  from_kill_I = 0;
    }
  }

// the basic function to kill an object: deallocate
CL_EXPORT OID kill_I_any(OID n) {ClAlloc->kill(n);return 0;}

// call the gc
CL_EXPORT void claire_gc() {ClAlloc->gc("Call");}

// same for arrays
CL_EXPORT OID gc_error()  {
  Kernel.GcError->index = 27;
    Kernel.GcError->value = ClAlloc->maxGC;
    Kernel.GcError->arg = ClAlloc->maxGC;
   close_exception((ClaireException *)Kernel.GcError);
    return 1;
  }


// statistics about memory management
// notice that if the verbosity is more than 4 we get a dump
void ClaireAllocation::memStat()
{list *l = memList(CFALSE);
  Ctracef("Loglist = %d\n", ClAlloc->logList);
  Ctracef("Chunk allocation: %d used cells out of %d\n", (*l)[1], maxList);
  Ctracef("Short item allocation: %d used cells out of %d\n", (*l)[2], maxSize);
  Ctracef("Symbol allocation: %d used cells out of %d\n", (*l)[3], maxHash);
  Ctracef("World stack: %d used cells out of %d\n", (*l)[4], maxHist);
  CL_INT i, useList[logList];                         // start the chunk zone analysis
   CL_INT useString = 0, useObject = 0, useOther = 0, maxFree = 0, totalList = 0;
   for (i = 1; i < logList; i++)
      {useList[i] = 0;
       if (entryList[i] != NOTHING) maxFree = i;}
   for (i = 1; i < maxList; i += Cmemory[i])
      {CL_INT p = (CL_INT)Cmemory[i], x = (CL_INT)Cmemory[i + 1];
       if (x != NOTHING)                       // the chunk is used
          {if (x == (CL_INT) Kernel._primitive)              // used for a string
              {useString += p;
               if (ClEnv->verbose > 4) Ctracef("string(%s)\n", &Cmemory[i + 3]);}
           else if (x == (CL_INT) Kernel._array)          // used for an array
              {useOther += p;
               if (ClEnv->verbose > 4) Ctracef("array(%d)\n", p);}
           else if (CLMEM(x) && ((ClaireAny *) x)->isa == Kernel._class)
              {useObject += p;
               if (ClEnv->verbose > 4)
                  Ctracef("object(%s)\n", ((ClaireClass *) x)->name);}
           else {CL_INT size = log2up(p);                     // a bag (what else ?)
                 useList[size] += p;
                 totalList += p;
                 if (ClEnv->verbose > 4)
                  Ctracef("bag(%d)\n", p);}}}
   Ctracef("Bag: %d, Max free bag size: %d\n", totalList, 1ul << maxFree);
   Ctracef("List usage: ");
   for (i = 4; i < logList; i++) Ctracef("%d=%d ", i, useList[i]);
   Ctracef("\nString: %d, Object: %d, Array: %d\n",useString,useObject,useOther); }

// private methods
// we add a parameter (x = true -> returns the max capacity)
list *ClaireAllocation::memList(ClaireBoolean *x)
{CL_INT i = nextFree, nb = 0, usedSymb = 0, usedWorld = ClRes->iIndex, prev; // prev -> remove
 if (x == CTRUE)
     return list::alloc(4,maxList,
                          maxSize,
                          maxHash,
                          maxHist);
 while (i != NOTHING) {
   nb++; i = (CL_INT)Cmemory[i+1];
   prev = i;}
 for (i = 1; i < maxHash; i++) if (ClRes->sTable[i] != NULL) usedSymb++;
 if (ClRes->oIndex > usedWorld) usedWorld = ClRes->oIndex;
 if (ClRes->fIndex > usedWorld) usedWorld = ClRes->fIndex;
 return list::alloc(4,usedCells,
                      firstFree - maxList0 - nb * OPTIMIZE,
                      usedSymb,
                      usedWorld);
}

// C API
CL_EXPORT void claire_stat() {ClAlloc->memStat();}

// query CLAIRE memory management
CL_EXPORT OID claire_mem(OID n)
{if (OWNER(n) == Kernel._boolean)
    return _oid_(ClAlloc->memList(OBJECT(ClaireBoolean,n)));
 else {if (OWNER(n) == Kernel._integer)
           {if (n == 1) Ctracef("Badguy: %d, %d\n",Cmemory[BadGuy],Cmemory[BadGuy + 1]);
           }
        else {Ctracef("--- Probe is of %s OID=%d address=0x%x\n",
                      OBJECT(ClaireAny,n)->isa->name->name,
                      (CL_INT)n,
                      (unsigned CL_INT)OBJECT(ClaireAny,n));
               ClAlloc->probe = OBJECT(ClaireAny,n);}
       return n;}}


/*********************************************************************/
/**    6. Sampling memory                                            */
/*********************************************************************/

void ClaireAllocation::samplerSweepChunk()
{ OID i = 0; CL_INT p;
 while (i < maxList-1)
  {p = ((CL_INT*)Cmemory)[i];
   if (p < 0) {
       p = -p;
       chunk_used += p;
     rchunk_used += p; }
   else if (Cmemory[i + 1] != NOTHING)
       chunk_used += p;
   i = i + p;}}


void ClaireAllocation::samplerSweepObject()
{ CL_INT i = maxList0 + MAXLIST_OFFSET;
 CL_INT p;
 while (i < firstFree) {
    p = (CL_INT)Cmemory[i];
    if (p < 0)
       {p = -p;
         rshort_used += p;
        p++;
        if (p < OPTIMIZE) p = OPTIMIZE;
      short_used += p;
    } else if (p != 0) {
        p++;
        if (p < OPTIMIZE) p = OPTIMIZE;
      short_used += p; }
    if (p < OPTIMIZE) p = OPTIMIZE;
    i = i + p;}
}


//<sb> In order to debug some hard memory bugs it will sometimes
// be interresting to get a memory usage graph.
// This is done when the -sample option is given  wich
// creates a clmemory.sample file that contain 5 columns of values :
//   time : the time offset at which the sample is performed
//   Chunk : chunk space that isn't free (what is used)
//   Short : short  "          "           "
//   Real_chunk : real chunk space that is in use (what is pointed/accessible)
//   Real_short :   "  short        "            "
// Note: after a gc, what is pointed is equal to what is in use.

FILE* samples = 0;
CL_INT sample_period;
void sample_handler(int sig) {ClAlloc->sample_once();}
CL_INT clock_t0 = 0;

//<sb> here we start the sampling. An alarm is created
// such we get samples asynchronously with the given period.
void ClaireAllocation::open_sample_file(CL_INT period) {
  samples = fopen("clmemory.samples","w");
  clock_t0 = clock();
  if(samples) {
    sampling = 1;
    Ctracef("Start sampling with period %dms\n", period);
    fprintf(samples,"time (ms)\tchunks\tshorts\treal chunks\treal shorts\tobjects\tstrings\tbags\tarrays\tsymbols\n");
    fflush(samples);
  #ifdef HAVE_SETITIMER
    signal(SIGVTALRM, sample_handler);
    struct itimerval sit;
    sample_period = period;
    sit.it_interval.tv_sec = 0;
    sit.it_interval.tv_usec = 0;
    sit.it_value.tv_sec = sample_period / 1000;
    sit.it_value.tv_usec = 1000 * (sample_period % 1000);
    setitimer(ITIMER_VIRTUAL, &sit, 0);
  #endif
  } else Ctracef("Cannot open sample file\n"); }



void ClaireAllocation::close_sample_file() {
#ifdef HAVE_FORK
  int st;
  waitpid(-1,&st,WUNTRACED);
#endif
  if(samples) fclose(samples); }

void exit_on_sigint(int i) {
  fclose(samples);
  _exit(0); }

//<sb> Here we append a sample line in the file.
// the startegy is to fork the process and to inspect
// the memory in the child with a mark & count algo.
void ClaireAllocation::sample_once() {
  CL_INT clock_now = clock();
  double t = ((double)clock_now - (double)clock_t0) / (double)CLOCKS_PER_SEC;
#ifdef HAVE_FORK
  #ifdef HAVE_SETITIMER
    signal(SIGVTALRM, SIG_DFL);
    struct itimerval sit;
    setitimer(ITIMER_VIRTUAL, 0, 0);
  #endif
  if(samples) {
    #ifdef SIGINT
    signal(SIGINT, SIG_DFL);
    #endif
    ++numSample;
    int st;
    waitpid(-1,&st,WUNTRACED);
    if(inside_gc == 0 && fork() == 0) {
      signal(SIGINT, exit_on_sigint);
      chunk_used = 0;
      short_used = 0;
      rchunk_used = 0;
      rshort_used = 0;
      string_used = 0;
      object_used = 0;
      bag_used = 0;
      array_used = 0;
      symbol_used = 0;
          delayedThings = 1;
           CL_INT t1 = clock();
           markStack();
      markHash();
      samplerSweepChunk();
      samplerSweepObject();
           fprintf(samples,"%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",
            t,
            4.0 * (double)chunk_used / 1000000.0,
            4.0 * (double)short_used / 1000000.0,
            4.0 * (double)rchunk_used / 1000000.0,
            4.0 * (double)rshort_used / 1000000.0,
            4.0 * (double)object_used / 1000000.0,
            4.0 * (double)string_used / 1000000.0,
            4.0 * (double)bag_used / 1000000.0,
            4.0 * (double)array_used / 1000000.0,
            4.0 * (double)symbol_used / 1000000.0
            );
      fclose(samples);
      raise(SIGKILL);  
    }
  #ifdef HAVE_SETITIMER
    signal(SIGVTALRM, sample_handler);
    sit.it_interval.tv_sec = 0;
    sit.it_interval.tv_usec = 0;
    sit.it_value.tv_sec = sample_period / 1000;
    sit.it_value.tv_usec = 1000 * (sample_period % 1000);
    setitimer(ITIMER_VIRTUAL, &sit, 0);
  #endif
  }
#endif
  CL_INT clock_end = clock();
  clock_t0 += clock_end - clock_now;
}



/***********************************************************************/
/**   microCLAIRE                                       Yves Caseau    */
/**   clBag.cpp                                                        */
/**  Copyright (C) 1998-2003 Yves Caseau. All Rights Reserved.         */
/**  cf claire.h                                                       */
/***********************************************************************/


//<sb> content copy tools
#define upcpy(to,from,s) {if((s)>0) memcpy(to,from,sizeof(OID) * (s));}
#define upmove(to,from,s) {if((s)>0) memmove(to,from,sizeof(OID) * (s));}
#define downmove(to,from,s) {if((s)>0) memmove(to,from,sizeof(OID) * (s));}



// This file contains the definition of the bag, list, set and array classes.

// ***************************************************************************
// * Table of content:                                                       *
// * PART 1: Bags                                                            *
// * PART 2: Lists                                                           *
// * PART 3: Sets                                                            *
// * PART 4: Tuples                                                          *
// * PART 5: Arrays                                                          *
// ***************************************************************************


// ***************************************************************************
// * PART 1: Bags                                                            *
// ***************************************************************************

// member methods ------------------------------------------------------------

// read the i-th element of a list (debug version non-inline !)
#ifdef CLDEBUG
OID &bag::operator[](CL_INT i)  {
   if (ClEnv->verbose > 12) printf("BAG:~%lx [%ld] -> %lx (%ld)\n",this,i,content[i],getADR(content) + i);
   return ((i <= length) ? content[i] : (Cerror(41,_oid_(this),i), content[1]));
}
#endif

#define hash_order(x) ClRes->hashOid(0xFFFFFFFF,x)


// internal static functions that operate on Cmemory
// sort using the hash code order
// should be made available in CLAIRE !
void bag::quickSort(OID *a, CL_INT n, CL_INT m)
{CL_INT x,y;
 if (m > n)                                     // sort memory zone from l + n to m
     {x = a[n]; y = hash_order(x);          // use x as pivot
      if (m == (n + 1)) {if (hash_order(a[m]) < y)                // two pieces
                            {a[n] = a[m]; a[m] = x;}} // swap
      else {CL_INT q = n, p = (m + n) >> 1;        // new in v3.0.20
            x = a[p]; y = hash_order(x);
            if (p != n) a[p] = a[n];            // move pivot to first place
            for (p = n + 1; p <= m; p++)        // sort around pivot
              {if (hash_order(a[p]) < y)
                  {a[q++] = a[p];
                  if (p > q) a[p] = a[q]; }}
            a[q] = x;
            quickSort(a,n,q-1);
            quickSort(a,q+1,m);}}}


// remove duplicates and return cardinal (assumed that a[] was sorted)
// note that equal(x,y) => hash(x) = hash(y)
// at any point a[1 .. j] is cleaned and we have examined a[1 .. i]
// u is the index of the last strict increase in hash_order
CL_INT bag::quickClean(OID *a, CL_INT m)
{ CL_INT i = 1, j = 1, x = a[1], u = 1, y = hash_order(x);
  while (i + 1 <= m)
     {OID x2 = a[i + 1], y2 = hash_order(x2), keep = 1, k;       // do we keep x2 ?
      // printf("hash de %d -> %d [%d,%d]\n",x2,y2,x,y);
      if (y2 != y) u = j ;                                       // y2 != y => y2 > y => yes
      else if IDENTIFIED(x2)
         {for (k = u; k <= j; k++) if (a[k] == x2) {keep = 0; break;}}
      else 
         {for (k = u; k <= j; k++) if (equal(a[k],x2) == CTRUE) {keep = 0; break;}}
      // printf("look at %d in position %d -> keep = %d [%d]\n",x2,i + 1,keep,j);
      if (keep == 1) {if (j < i) a[j + 1] = x2; j++; x = x2; y = y2;}
      i++; }
  return j; }
  
  
// v3.2 new: create a list of same size with no type or a given type
list *bag::clone() 
 {return clone(Kernel.emptySet);}
 
list *bag::clone(ClaireType *t)
{  if (length == 0) return list::empty(t);        // v3.2.38 -> moved up thanks to FXJ
   list *obj = list::make();
   CL_INT i;
   OID *x = ClAlloc->makeContent(length);
   for (i = 1; i <= length; i++) x[i] = CNULL;    // for GC protection
   obj->content = x;
   obj->length = length;
   obj->of = t;
  //if (ClAlloc->statusGC != 2) GC_PUSH(obj);                       // v3.2.20 : clone is protected toolate  ...
  return obj;}

// API functions ------------------------------------------------------------
// copy a bag - in v0.01, we cannot copy nil or {} we return a generic empty
CL_EXPORT bag *copy_bag(bag *l)
{CL_INT i;
 if (Kernel.nil == l) return list::empty();
 else if (l == Kernel.emptySet) return set::empty();
 else {
 bag *obj = (bag *) ClAlloc->makeAny(5);
 obj->isa = l->isa;
 obj->content = NULL;
 obj->of = l->of;                           // v3.1.08
 obj->length = 0;
 obj->prealloc = l->prealloc;
 CL_INT m = l->length;
 if (obj->prealloc > m) m = obj->prealloc; //<sb> for store
 if (ClAlloc->statusGC != 2)  GC_PUSH(obj);  // v3.2.30
 OID *x = ClAlloc->makeContent(m);
  //for (i = 1; i <= l->length ; i++) x[i] = (*l)[i];
  upcpy(x+1,l->content+1,m); //<sb> v3.3.33
 obj->length = l->length;
  obj->content = x;
  return obj;}}

// new in v3.1.16: create an empty copy  
CL_EXPORT bag *empty_bag(bag *l)
{CL_INT i;
 bag *obj = (bag *) ClAlloc->makeAny(5);
 obj->isa = l->isa;
 obj->content = NULL;
 obj->of = l->of;                           // v3.1.08
 obj->length = 0;
 obj->prealloc = 0;
 if (ClAlloc->statusGC != 2) GC_PUSH(obj);     // v3.2.30
 obj->content = ClAlloc->makeContent(l->length);
 obj->content[1] = 0;                       // v3.1.18 erase the NOTHING !
 return obj;}
  
// removes the first occurrence of val in l; works for bags !
// we could still do better with a set if desired ...
CL_EXPORT bag *delete_bag(bag *l, OID val)
{CL_INT i,j, m = l->length;
 OID *x = l->content;
 if ( m == 0 ) return(l);                   // v3.2.22
 if IDENTIFIED(val)
  for (i= 1;;)  {OID j = x[i++];
                  if (j == val) break;
                  if (i > m) return(l);}
  else for (i= 1;;) {OID j = x[i++];
                      if (equal(j,val) == CTRUE) break;
                      if (i > m) return(l);}
  //for (j= i - 1; j < m; j++) x[j] = x[j + 1];
  upmove(x+i-1,x+i,m - i + 1); //<sb> v3.3.33
  l->length = m - 1;
  return l;}

// returns a true type
CL_EXPORT ClaireType * of_bag(bag *l)
{if (l->of == NULL) return Kernel._void; else return l->of;}

// used by the reader to change this information
//bag * cast_I_bag(bag *l, ClaireType *x)  { l->of = x; return l;}
CL_EXPORT list * cast_I_list1(list *l, ClaireType *x)  { l->of = x; return l;}
CL_EXPORT set * cast_I_set1(set *l, ClaireType *x)  { l->of = x; return l;}

// ***************************************************************************
// * PART 2: Lists                                                           *
// ***************************************************************************

// constructors --------------------------------------------------------

// create a list skeleton  - every method uses this one and
// it performs the GC_PUSH
list *list::make()
{list *obj = (list *) ClAlloc->makeAny(sizeof(list) / sizeof(OID));
  obj->length = 0;
  obj->isa = Kernel._list;
  obj->of = NULL;
  obj->prealloc = 0;
  obj->content = NULL;                       // v3.2 make is the only one to use NULL ...
  if (ClAlloc->statusGC != 2)  GC_PUSH(obj);    // v3.2.30
  return obj;}                               // ... and it MUST be replaced by something

// create an empty list
list *list::empty()
{list *obj = list::make();
 OID *x = ClAlloc->makeContent(1);
   obj->length = 0;
   obj->content = x;
   obj->prealloc = 0;
   obj->of = Kernel.emptySet;                 // v3.2 emptySet => do not touch
   return obj;}

// create a typed empty list
list *list::empty(ClaireType *t)
{ ClAlloc->currentType = t;
 list *obj = list::make();
 OID *x = ClAlloc->makeContent(1);
   obj->length = 0;
   obj->content = x;
   obj->prealloc = 0;
   obj->of = t;
   ClAlloc->currentType = NULL;
   return obj;}

// create a list with one element
list *list::make(OID val)
{list *obj = list::make();
 OID *x = ClAlloc->makeContent(1);
   x[1] = val;
   obj->length = 1;
   obj->prealloc = 0;
   obj->content = x;
   return obj;}

// create a list with two members
list *list::make(OID val1, OID val2)
{list *obj = list::make();
 OID *x = ClAlloc->makeContent(2);
   x[1] = val1; x[2] = val2;
   obj->length = 2;
   obj->prealloc = 0;
   obj->content = x;
   return obj;}

/* create a list with two members on the eval stack
list *list::makeStack(OID val1, OID val2)
{OID *adr = &(ClEnv->stack[ClEnv->index]);
 list *obj = (list *) adr;
   obj->isa = Kernel._list;
   obj->of = NULL;
   obj->length = 2;
   obj->content = &adr[4];
   (*obj)[0] = 4; (*obj)[1] = val1; (*obj)[2] = val2;
   ClEnv->index += 7;
   if (ClEnv->index >= ClAlloc->maxStack) Cerror(27,ClAlloc->index,0);
   return obj; }     */

// creates a list
list *list::alloc(CL_INT n,...)
{va_list ap;
 CL_INT i;
 list *obj = list::make();
 obj->of = Kernel.emptySet;                 // v3.2
 OID *x = ClAlloc->makeContent(n);
   va_start(ap,n);
   for (i = 1; i <= n; i++) {
	   OID y = va_arg(ap, OID);
	   x[i] = y;
	//   printf("x[%ld] = %ld => %ld\n", i, y, x[i]);
   }
   obj->length = n;
   obj->content = x;
   va_end(ap);
   return obj;}

// creates a typed list
list *list::alloc(ClaireType *t, CL_INT n,...)
{va_list ap;
 CL_INT i;
  ClAlloc->currentType = t;
 list *obj = list::make();
 OID *x = ClAlloc->makeContent(n);
   va_start(ap,n);
   for (i = 1; i <= n; i++)   x[i] = va_arg(ap, OID);

   obj->length = n;
   obj->content = x;
   obj->of = t;
    ClAlloc->currentType = NULL;
   va_end(ap);
   return obj;}

// this is pure sugar but nice
list *list::domain(CL_INT n, ...)
{va_list ap;
 CL_INT i;
 list *obj = list::make();
 OID *x = ClAlloc->makeContent(n);
   va_start(ap,n);
   for (i = 1; i <= n; i++)
     {CL_INT z = va_arg(ap, CL_INT);
      x[i] = _oid_(((ClaireAny *) z));}
   obj->length = n;
   obj->content = x;
   obj->of = Kernel._type;
   va_end(ap);
   return obj;}


// member methods ------------------------------------------------------

// add a new element to a list (without checking the type)
//<sb> made addFast inline, this version is called when
// the content have to be re-allocated
list *list::addFastAlloc(OID x)
{ OID *y = ClAlloc->makeContent(length + 1);
  upcpy(y+1, content+1, length); //<sb> v3.3.33
  ClAlloc->freeContent(content); //<sb> v3.3.33 force desallocation of the old content
  content = y;
  content[++length] = x;        // add the element
  return this;}


// equality on lists
ClaireBoolean *list::equalList(list *l2)
{CL_INT i, m = length;
  if ( l2->length != m ) return(CFALSE);
  else {for ( i = 1; i <= m ; i++) {
        CL_INT a = (*this)[i];
        CL_INT b = (*l2)[i];
            if (equal(a, b) == CFALSE) return(CFALSE);
        }
        return(CTRUE);}}

// fast membership (we know that val is identified)
ClaireBoolean *list::memq(OID val)
{ITERATE(j);
    for ( START(this); NEXT(j); ) if (j == val) return(CTRUE);
    return(CFALSE);}

// API functions ----------------------------------------------------------------


// generic contains function
CL_EXPORT ClaireBoolean *contain_ask_list(list *l,OID val)
{if IDENTIFIED(val) return l->memq(val);
 else {ITERATE(j);
       for ( START(l); NEXT(j) ; )
           if (equal(j,val) == CTRUE) return(CTRUE);
        return(CFALSE);}}

// API version of add, does the type checking
CL_EXPORT list *add_list(list *l, OID val)
{if (l->of == NULL || l->of->contains(val) == CFALSE ) // v3.3.24
     Cerror(17,val,_oid_(l));         // v3.2
 return l->addFast(val);}

CL_EXPORT list *add_I_list(list *l, OID val)
{ return l->addFast(val);}

/* create a list with car = val and cdr = l ; l must be a list 999 */
CL_EXPORT list *cons_any(OID val, list *l)
{  list *obj = list::make();
   CL_INT i;
   OID *x = ClAlloc->makeContent(l->length + 1);
     x[1] = val;
     //for (i = 1; i <= l->length; i++) x[i + 1] = (*l)[i];
     upcpy(x+2,l->content+1,l->length); //<sb> v3.3.33
     obj->length = l->length + 1;
     obj->content = x;
     if (l->of == NULL || l->of->contains(val) == CFALSE ) // v3.3.24
       obj->of = Kernel._any;
     else obj->of = l->of;                 // v3.2.36
     return obj;}

// allocate a list with n members equal to m
CL_EXPORT list *make_list_integer(CL_INT n, OID m)
{  if ( n < 0 ) n = 0;
   list *obj = list::make();
   CL_INT i;
   if (n > 0)
      {OID *x = ClAlloc->makeContent(n);
       for (i = 1; i <= n; i++) x[i] = m;
       obj->content = x;}
   else obj->content =  ClAlloc->makeContent(1);   // v3.1.16
   obj->length = n;
   obj->of = Kernel._any;
   return obj;}

//<sb> allocate an empty list that is preallocated for n memebers
CL_EXPORT list *make_list_type1(ClaireType *t, CL_INT n)
{  if ( n < 0 ) n = 0;
   list *obj = list::make();
   CL_INT i;
   if (n > 0)
      {OID *x = ClAlloc->makeContent(n);
       obj->content = x;}
   else obj->content =  ClAlloc->makeContent(1);   // v3.1.16
   obj->length = 0;
   obj->of = t;
   return obj;}

//<sb> allocate an empty list that is prealloc-able
// use this for storeable lists
CL_EXPORT list *prealloc_list_type1(ClaireType *t, CL_INT n)
{  if ( n < 0 ) n = 32; 
   list *obj = list::make();
   OID *x = ClAlloc->makeContent(1);
   obj->content = x;
   obj->length = 0;
   obj->prealloc = n;
   obj->of = t;
   return obj;}


// returns the position of val in the list l (use fast iteration)
CL_EXPORT CL_INT index_list (list *l, OID val)
{CL_INT i = 1;
 ITERATE(j);
  for (START(l); NEXT(j); i++)  if (equal(j,val) == CTRUE) return(i);
  return(0);}

// add a second list into a first (destructive - equivalent of LISP nconc)
CL_EXPORT list *add_star_list(list *l1, list *l2)
{CL_INT i = l1->length + 1,k;
 ITERATE(j);
 if (l1->of != NULL)
    for (START(l2) ;NEXT(j) ;)
       if (l1->of->contains(j) == CFALSE) Cerror(17,j,_oid_(l1));  // v3.2
 if (i + l2->length > l1->content[0])
    {OID *x = ClAlloc->makeContent(l1->length + l2->length);
       //for ( i =1 ; i <= l1->length ; i++) x[i] = (*l1)[i];
       upcpy(x+1,l1->content + 1, l1->length); //<sb> v3.3.33
       ClAlloc->freeContent(l1->content); //<sb> v3.3.33 force desallocation of the old content
       l1->content = x;}
 l1->length += l2->length;
 for (START(l2); NEXT(k);) (*l1)[i++] = k;
 return l1;}

void (*callback_refine_append_of)(bag*,bag*,bag*) = NULL;

// append: non destructive
CL_EXPORT list *append_list(list *l1, list *l2)
{ITERATE(k);
 if (l1->length == 0) return (list*)copy_bag(l2);   //<sb> v3.3.33 return a fresh copy
 else if (l2->length == 0) return (list*)copy_bag(l1); //<sb> v3.3.33 return a fresh copy
 else {list *obj = list::make();
       CL_INT n =l1->length + l2->length,j = 1;
       OID *x = ClAlloc->makeContent(n);
         //for (START(l1); NEXT(k);)  x[j++] = k;
         //for (START(l2); NEXT(k);) x[j++] = k;
         upcpy(x+1, l1->content+1,l1->length); //<sb> v3.3.33
         upcpy(x+l1->length+1,l2->content+1,l2->length); //<sb> v3.3.33
         if (l1->of == l2->of) obj->of = l1->of;
         else if(callback_refine_append_of)
           callback_refine_append_of(obj,l1,l2);
         else obj->of = NULL;
         obj->length = n;
         obj->content = x;
         return obj;}}


// insert after a member, works only for a list
CL_EXPORT list *add_at_list(list *l, CL_INT n, OID val)
{CL_INT i,j,m = l->length;
 if (l->of == NULL || l->of->contains(val) == CFALSE ) // v3.3.24
   Cerror(17,val,_oid_(l)); // v3.2
 if (n <= 0 || n > m + 1) Cerror(5,n,_oid_(l));                                 // v3.2.24 !
 if (m + 1 == (*l)[0])
    {OID *x = ClAlloc->makeContent(m + 1);
     //for (i = 1; i <= m; i++) x[i] = (*l)[i];
     upcpy(x+1,l->content+1,m); //<sb> v3.3.33
     ClAlloc->freeContent(l->content); //<sb> v3.3.33 force desallocation of the old content
     l->content = x;}
 l->length = m + 1;
 //for ( j = m; j >= n ; j-- ) (*l)[j + 1] = (*l)[j];
 downmove(l->content + n + 1, l->content + n, m + 1 - n); //<sb> v3.3.33 
 (*l)[n] = val;
 return l;}

// removes the nth member of a list
// TODO write rmlast using delete_at
CL_EXPORT list *delete_at_list (list *l, CL_INT n)
{CL_INT j, m = l->length;
  if ((n < 1) || (n > m)) Cerror(5,n,_oid_(l));    // v3.2.44 : same error as 2.5
  //for (j= n; j < m; j++) (*l)[j] = (*l)[j+1];
  //<sb> protect the deleted element
  GC_OID((*l)[n]);
  upmove(l->content+n, l->content + n + 1, m - n); //<sb> v3.3.33 
  l->length = (m - 1);
  return l;}

 // remove the n first elements of a list
CL_EXPORT list *skip_list(list *l, CL_INT n)
{CL_INT i, m = l->length;OID *ct = l->content; 
    if (n < 0) Cerror(7,_oid_(l),n);
    //<sb> protect the skiped elements
    for (i = 1; i <= n; i++) GC_OID(ct[i]);
    if (m <= n) l->length = 0;
    else {
      //for (i = n + 1; i <= m; i++) (*l)[i-n] = (*l)[i];
        upmove(l->content + 1, ct + 1 + n, m - n); //<sb> v3.3.33 
        l->length = m - n;}
   return l; }

// old LISP cdr ....
CL_EXPORT list *cdr_list(list *l)
{CL_INT i,m = l->length;
  if (m == 0) {Cerror(8,0,0); return NULL;}
  else { list *obj = list::make();
         OID *x = ClAlloc->makeContent(m - 1);
          //for (i = 2; i <= m; i++) x[i - 1] = (*l)[i];
          upcpy(x+1,l->content + 2, m - 1); //<sb> v3.3.33
          obj->length = m - 1;
          obj->content = x;
          obj->of = l->of;
          return obj;}}

// shrinks a list (keep the same allocation)
// v3.2.20 : also works for a bag !
// <sb> need to protect shrank elements
CL_EXPORT bag *shrink_list (bag *l, CL_INT n)
{if (n < 0) Cerror(7,_oid_(l),n);
  if (n < l->length) {
    CL_INT i;
    OID *ct = l->content;
    for (i = 1; i <= l->length; i++) GC_OID(ct[i]);
    l->length = n;
  }
 return l;}


// ***************************************************************************
// * PART 3: Sets                                                            *
// ***************************************************************************


// constructors --------------------------------------------------------

// create an empty list (used for non-constant sets)
set *set::empty()
{set *obj = set::make();
 OID *x = ClAlloc->makeContent(1);
   obj->length = 0;
   obj->content = x;
   obj->of = Kernel.emptySet;                 // v3.2.08 emptySet => do not touch
   return obj;}

// create a typed empty list
set *set::empty(ClaireType *t)
{ ClAlloc->currentType = t;
 set *obj = set::make();
 OID *x = ClAlloc->makeContent(1);
   obj->length = 0;
   obj->content = x;
   obj->of = t;
    ClAlloc->currentType = NULL;
   return obj;}

// create a list skeleton
set *set::make()
{set *obj = (set *) ClAlloc->makeAny(5);
  if (ClAlloc->statusGC != 2)  GC_PUSH(obj);    // v3.2.30
  obj->isa = Kernel._set;
  obj->of = NULL;
  obj->prealloc = 0;
  obj->content = NULL;
  obj->length = 0;
  return obj;}

// creates a set
set *set::alloc(CL_INT n,...)
{va_list ap;
 CL_INT i;
 set *obj = set::empty();
 obj->of = Kernel.emptySet;                 // v3.2
   va_start(ap,n);
   for (i = 1; i <= n; i++) obj->addFast(va_arg(ap, OID));
   va_end(ap);
   return obj;}

// creates a typed set
set *set::alloc(ClaireType *t, CL_INT n,...)
{va_list ap;
 CL_INT i;
 set *obj = set::empty(t);
   va_start(ap,n);
   for (i = 1; i <= n; i++) obj->addFast(va_arg(ap, OID));
   va_end(ap);
   return obj;}


//<sb> allocate an empty list that is prealloc-able
// use this for storeable lists
CL_EXPORT set *prealloc_set_type1(ClaireType *t, CL_INT n)
{  if ( n < 0 ) n = 32; 
   set *obj = set::make();
   OID *x = ClAlloc->makeContent(1);
   obj->content = x;
   obj->length = 0;
   obj->prealloc = n;
   obj->of = t;
   return obj;}



// member methods ------------------------------------------------------

// this methods insert val into the set
set *set::addFast(OID val)
{ if (IDENTIFIED(val) || (contain_ask_set(this,val) == CFALSE))    // otherwise nothing to do !
  {OID *x = content;                // array= chunk
   CL_INT m = length, i = 1, j = m,NEW;
   while ((i + 1) < j)              // dichotomic research for the insertion point [i,j]
     {NEW = ((i + j) >> 1);         // NEW is neither l or j
      if (x[NEW] == val) return this;
       else if (x[NEW] < val) i = NEW;
       else j = NEW;}
  if (m == 0) i = 0;
  else if (x[i] == val || x[j] == val) return this;
  else if (x[i] > val) i = i - 1;
  else if (x[j] < val) i = j;
  length = m + 1;
  if (x[0] == m + 1)                // current chunk is full
     { if (ClEnv->verbose > 10) 
#ifdef __LP64__
		 printf("addFast: complex insertion of OID %lx at %ld [new length %ld]\n",val,j,m + 1);
#else
		 printf("addFast: complex insertion of OID %x at %d [new length %d]\n",val,j,m + 1);
#endif
       OID *y = ClAlloc->makeContent(m + 1);
       //for (j = 1; j <= i; j++) y[j] = x[j];
       //y[j] = val;
       //for (j++; j <= m + 1; j++) y[j] = x[j - 1];
       upcpy(y+1,x+1,i); //<sb> v3.3.33 
       y[i+1] = val;
       upcpy(y+2+i, x+i+1, m - i); //<sb> v3.3.33
       ClAlloc->freeContent(content); //<sb> v3.3.33 force desallocation of the old content
       content = y;
      return this;}
  else                             // simply insert val between i and i+1
    { //for (j = m ; j >= i; j--) x[j+1] = x[j];
      downmove(x+i+1, x+i, m - i + 1); //<sb> v3.3.33 
      x[i+1] = val;
      return this;}}
 else return this;}


// redefinition of generic equal for sets
// *ClaireBoolean set::isEqual(OID x2)
//  {if (OWNER(x2) == Kernel._set) return equalSet(OBJECT(set,x2));
//   else return(CFALSE);}

// equality on lists
ClaireBoolean *set::equalSet(set *l2)
{CL_INT i,direct = 0;                            // direct = 0 <=> fast mode since all members are identified (=> same position)
  if (length != l2->length) return CFALSE;
  for (i=1; i <= length ; i++)
        {OID x = (*this)[i]; 
          if (!IDENTIFIED(x)) direct = 1;
          if (direct != 0) {if (contain_ask_set(l2,x) == CFALSE) return(CFALSE);}
          else if (equal(x,(*l2)[i]) == CFALSE) return(CFALSE);}
  return(CTRUE);}


// API functions ----------------------------------------------------------------

// generic contains function
CL_EXPORT ClaireBoolean *contain_ask_set(set *s,OID val)
 {OID *x = s->content;                // array= chunk
  CL_INT j, m = s->length;
  if (m == 0) return CFALSE;
  if IDENTIFIED(val)
    {CL_INT i = 1, j = m, k;
     while ((i + 1) < j)            // dichotomic search
      {k = ((i + j) >> 1);           // k is neither l or j
       if (x[k] == val) return CTRUE;
       else if (x[k] < val) i = k;
       else j = k;}
     if (x[i] == val || x[j] == val) return CTRUE;
     else  return CFALSE;}
  else  { for (j = 1; j <= m; j++) if (equal(x[j],val) == CTRUE) return CTRUE;
          return CFALSE;}}
          
/* insert a value at the end of a list */
CL_EXPORT set *add_set(set *l, OID val)
{if (l->of == NULL || l->of->contains(val) == CFALSE ) // v3.3.24
  Cerror(17,val,_oid_(l)); // v3.2
  return l->addFast(val);}

CL_EXPORT set *add_I_set(set *l, OID val)
{ return l->addFast(val);}

// intersection of two sets
CL_EXPORT set *_exp_set(set *l1, set *l2)
{set *s = set::empty();
 CL_INT m1 = l1->length, m2 = l2->length, newl = m1,i1,i2,j = 1;
 if (newl > m2) newl = m2;                    // min of 2 length (if needed)
 for ((i1 = 1,i2 = 1); ((i1 <= m1) && (i2 <= m2));)
      {OID x1 = (*l1)[i1], x2 = (*l2)[i2];
       if IDENTIFIED(x1)
         {if (x1 == x2) {if (j == 1) s->content = ClAlloc->makeContent(newl);
                         s->content[j++] = x1; i1++; i2++;}
          else if (x1 < x2) i1++;
          else i2++;}
       else if (contain_ask_set(l2,x1) == CTRUE)
         {if (j == 1) s->content = ClAlloc->makeContent(newl);
          s->content[j++] = x1; i1++;}
       else i1++;}
  if (i2 == m2)
     for ( ;(i1 <= m1); i1++)
        {OID x1 = (*l1)[i1];
          if (!IDENTIFIED(x1) && contain_ask_set(l2,x1) == CTRUE)
             s->content[j++] = x1;}
  s->length = j - 1;
  return s;}

// union of two sets: merge of sorted lists (sort_of) */
CL_EXPORT set *append_set (set *l1, set *l2)
{CL_INT m1 = l1->length, m2 = l2->length;
  if (m1 == 0) return (set *) copy_bag(l2);
  if (m2 == 0) return (set *) copy_bag(l1);
  set *s = set::make();
  OID *x = ClAlloc->makeContent(m1 + m2);
  CL_INT i1,i2,k,j = 1;
  for ((i1 =1, i2 = 1); (i1 <= m1 && i2 <= m2);)       // merge of l1 and l2
    {OID x1 = (*l1)[i1], x2 = (*l2)[i2];
      {if (x1 == x2) {i1++; i2++; x[j++] = x1;}
       else if (x1 < x2)
          {i1++;
           if (!IDENTIFIED(x1))
              {for (k = i2; (k <= m2 && (equal(x1,(*l2)[k]) == CFALSE));k++) ;
               if (k > m2) x[j++] = x1;}              // was not found => add
           else x[j++] = x1;}
       else {i2++;
             if (!IDENTIFIED(x2))
              {for (k = i1; (k <= m1 && (equal(x2,(*l1)[k]) == CFALSE));k++) ;
               if (k > m1) x[j++] = x2; }             // v3.2.44 fixed !
              else x[j++] = x2;}}}
  if (i1 > m1) {
    //for (;(i2 <= m2); i2++)  x[j++] = (*l2)[i2];     // adds what remain in l2..
    i1 = m2 - i2 + 1;
    upcpy(x+j, l2->content + i2, i1); //<sb> v3.3.33
    j += i1;
  } else {
    //for (;(i1 <= m1); i1++)  x[j++] = (*l1)[i1];     // .. or l1
    i2 = m1 - i1 + 1;
    upcpy(x+j,l1->content + i1, i2);  //<sb> v3.3.33
    j += i2;
  }
  s->content = x;
  //s->of = ((l1->of == l2->of) ? l1->of : NULL);
  if (l1->of == l2->of) s->of = l1->of;
  else if(callback_refine_append_of)
     callback_refine_append_of(s,l1,l2);
  else s->of = NULL;
         
  s->length = (j - 1);
  return s;}

/* remove duplicates: very useful ; works on bags*/
CL_EXPORT set *set_I_bag (bag *l)
{ if (l->length == 0)
    {if (l->of == NULL) return set::empty(); else return set::empty(l->of);}
  else if (l->isa == Kernel._set) return (set *) l;
  else {set *obj = (set *) copy_bag(l);
        obj->isa = Kernel._set;
        bag::quickSort(obj->content,1,obj->length);     // <yc> sort by hash code
        obj->length = bag::quickClean(obj->content,obj->length);
        return obj;}}

/* create a list from an enumeration */
CL_EXPORT list *list_I_set (set *l)
{list *obj = (list *) copy_bag(l);
   obj->isa = Kernel._list;
   return obj;}

// returns a nice sequence of consecutive numbers */
CL_EXPORT set *sequence_integer(CL_INT n, CL_INT m)
{ if (m < n) return set::empty();
  else {if (n == m) return set::alloc(Kernel._integer,1,n);
        else {CL_INT i;
              set *x = set::make();
              x->content = ClAlloc->makeContent(m-n+3);
              x->isa = Kernel._set;
              x->of = Kernel._integer;                    // v3.2.01
              x->length = (m -n + 1);
              for (i = n; i <= m; i++) x->content[1 + i - n] = i;
              return x;}}}


// ***************************************************************************
// * PART 4: Tuples                                                          *
// ***************************************************************************

// in Claire 3.0, tuples are bags (without the ability to modify) without
// parameter types (they are values)
// tuples are also types: tuple(1,2) % tuple(integer,integer)

// create a tuple skeleton
tuple *tuple::make()
{tuple *obj = (tuple *) ClAlloc->makeAny(5);
  if (ClAlloc->statusGC != 2)  GC_PUSH(obj);                   // v3.2.30
  obj->isa = Kernel._tuple;
  obj->of = NULL;
  obj->prealloc = 0;
  obj->content = NULL;
  obj->length = 0;
  return obj;}

// create an empty tuple
tuple *tuple::empty()
{tuple *obj = tuple::make();
 OID *x = ClAlloc->makeContent(1);
   obj->length = 0;
   obj->content = x;
   return obj;}
   
// creates a tuple
tuple *tuple::alloc(CL_INT n,...)
{va_list ap;
 CL_INT i;
 tuple *obj = tuple::make();
 OID *x = ClAlloc->makeContent(n);
   va_start(ap,n);
   for (i = 1; i <= n; i++) x[i] = va_arg(ap, OID);
   va_end(ap);
   obj->content = x;
   obj->length = n;
   return obj;}

// creates a (really !) temporary list on the stack
// v3.2.26 - stack allocation is only for tuples
// v3.2.58 - since -> copyIfNeeded is used all the time in the interpreted mode we do not
// need to protect the zone from another eval-push :-)
/*tuple *tuple::allocStack(CL_INT n,...)
{va_list ap;
 CL_INT i;
 if (ClEnv->index + n + 5 >= ClAlloc->maxStack)
   Cerror(27,ClEnv->index,0);
 OID *adr = (OID *)&(ClEnv->stack[ClEnv->index]);
 tuple *obj = (tuple *) adr;
   va_start(ap,n);
   obj->isa = Kernel._tuple;
   obj->of = NULL;
   obj->length = n;
   obj->content = &adr[4];
   (*obj)[0] = ClaireAllocation::log2up(n);        // v3.2.38
   // ClEnv->index += (n + 3);                        v3.2.58
   for (i = 1; i <= n ; i++) (*obj)[i] = va_arg(ap,OID);
   va_end(ap);
   return obj; }*/

tuple *tuple::allocStack(CL_INT n,...)
{va_list ap;
 CL_INT i;
   // <sb> 08/11/2008 - GC fix : protect arguments !
   // indeed the compiler assume a stack alloc
   va_start(ap,n);
   for (i = 1; i <= n; i++) GC_OID(va_arg(ap, OID));
   va_end(ap);
 tuple *obj = tuple::make();
 OID *x = ClAlloc->makeContent(n);
   va_start(ap,n);
   for (i = 1; i <= n; i++) x[i] = va_arg(ap, OID);
   va_end(ap);
   obj->content = x;
   obj->length = n;
   return obj;}

// create a tuple from a list
CL_EXPORT tuple * tuple_I_list(list *l)
{tuple *x = (tuple *) copy_bag(l);
  x->isa = Kernel._tuple;
  x->of = NULL;
  return x;}
  
// create a list from a tuple
CL_EXPORT list * list_I_tuple(tuple *l)
{list *x = (list *) copy_bag(l);
  x->isa = Kernel._list;
  x->of = NULL;
  return x;}

// add is reused from list.
tuple *tuple::addFast(OID x)
{return (tuple *) ((list *) this)->addFast(x);}

// copy a tuple from the stack if needed
tuple *tuple::copyIfNeeded()
{ if CLMEM(this) return(this);
  else return (tuple *) copy_bag(this);
}


// ***************************************************************************
// * PART 5: Arrays                                                          *
// ***************************************************************************

// arrays cannot be bags because they are imported - a cute trick that allows the
// generation of really nice (and fast) code
// as opposed to other imported, the wrapper and the wrapped are part of the same
//

// API functions -----------------------------------------------------------------
// copy an array onto another
// note that a[-2] = EOL if step = 1 and a[-2] = size if step = 2
CL_EXPORT OID *copy_array(OID *a)
{CL_INT i,m = ARRAYLENGTH(a);
 ClaireType *t = ARRAYTYPE(a);
 OID *b = ClAlloc->makeArray(m,t);
 CL_INT n = ((t == Kernel._float) ? (2 * m) + 1 : m);     // v3.2.44
   for (i = 1; i <= n ; i++) b[i] = a[i];
   return b;}

// returns the length of the array (to be removed later)
// the length is always at *a[0]
CL_EXPORT CL_INT length_array(OID *a) {return (CL_INT) a[0];}

// returns the type the array
CL_EXPORT ClaireType  *of_array(OID *a) {return  ARRAYTYPE(a);}

// creates a new array
CL_EXPORT OID *make_array_integer(CL_INT n, ClaireType *t, OID v)
  { if (t->contains(v) == CFALSE) Cerror(42,_oid_(t),v);
    CL_INT i;
    OID *a = ClAlloc->makeArray(n,t);
    if (t != Kernel._float)
       {for (i = 1; i <= n ; i++) a[i] = v;}
    else {double val = OBJECT(ClaireFloat,v)->value;
          for (i = 1; i <= n; i++) ((double *) a)[i] = val;}
    return a;}

// return the nth element of the array
CL_EXPORT OID nth_get_array(OID *a, CL_INT n)
{ // return  (ARRAYFLOAT(a) ? _float_( ((double *) a)[n]) : a[n]); }
  if ARRAYFLOAT(a)
      return _float_( ((double *) a)[n]);
  else return a[n];}

// sets the nth element of the array
CL_EXPORT void nth_put_array(OID *a, CL_INT n, OID y)
   {if ARRAYFLOAT(a) ((double *) a)[n] = OBJECT(ClaireFloat,y)->value;
    else a[n] = y;}

// creates a list copy of the array
CL_EXPORT list *list_I_array(OID *a)
{ CL_INT i,n = ARRAYLENGTH(a);
  list *obj = list::make();
  OID *x = ClAlloc->makeContent(n);
   obj->of = ARRAYTYPE(a);                 // v3.2.8
   obj->length = n;
   obj->content = x;
   if (ClAlloc->statusGC != 2) GC_PUSH(obj);                       // v3.2.54 : protected because of _float_
   if (ARRAYTYPE(a) != Kernel._float)
     { //for (i = 1; i <= n ; i++) x[i] = a[i];
     upcpy(x+1,a+1,n); } //<sb> v3.3.33
   else {
     for (i = 1; i <= n; i++) x[i] = _float_( ((double *) a)[i]);
   }
   return obj;}

// creates an array from a list and a type
CL_EXPORT OID *array_I_list(list *l)
{ CL_INT i,n = l->length;
  OID *a = ClAlloc->makeArray(n,((l->of == NULL) ? Kernel._any : l->of));
  ARRAYLENGTH(a) = n;
  for (i = 1; i <= n ; i++)
   {OID v = (*l)[i];
    if ARRAYFLOAT(a)  ((double *) a)[i] = OBJECT(ClaireFloat,v)->value;
    else a[i] = v;}
  return a;}

CL_EXPORT ClaireBoolean *contain_ask_array(OID *a,OID val)
{ CL_INT i,n = ARRAYLENGTH(a);
  if (ARRAYTYPE(a) != Kernel._float)
     {for (i = 1; i <= n ; i++) if (equal(val, a[i]) == CTRUE) return CTRUE;}
  else for (i = 1; i <= n; i++)         // MOST DISGRACEFUL, TRULY ABJECT
     if (equal(val,_float_( ((double *) a)[i])) == CTRUE) return CTRUE;
  return(CFALSE);}

/***********************************************************************/
/**   microCLAIRE                                       Yves Caseau    */
/**   clEnv.cpp                                                        */
/**  Copyright (C) 1998-2003 Yves Caseau. All Rights Reserved.         */
/**  cf claire.h                                                       */
/***********************************************************************/

// This file contains the definition of the environment classes

/**********************************************************************/
/** Contents                                                          */
/**    1. exception handling functions                                */
/**    2. ClRes functions                                             */
/**    3. Evaluator + ClEnv functions                                 */
/**    4. Function Evaluation (stack_apply)                           */
/**    5. World functions                                             */
/**    6: Encoding & Miscellaneous (will move)                        */
/**    7: signal handling base (xl)                                   */
/**    8: C error mapping (xl)                                        */
/**********************************************************************/

double CKernelRelease = 0.1;
void (*redirect_out_on_exception)() = NULL;

/***********************************************************************/
/**                 1: exception handling functions                    */
/***********************************************************************/

// create an exception - API function
CL_EXPORT OID close_exception(ClaireException *x)
{ ClEnv->exception_I = x;
  avoid_signal_caching = 0;
  if (Core._Zerrassegv->value == Kernel.ctrue) {//<sb> true when option -errasegv specified
    CL_INT *p = NULL;
    *p = 1;
  }
  longjmp(ClEnv->handlers[ClEnv->cHandle],3);
  return 0;}
  
// returns the index of the lexical base in the stack (constructor)
ClaireHandler::ClaireHandler()
{ if (ClEnv->cHandle+1 >= ClAlloc->maxEnv) Cerror(33,0,0);
  sIndex = ClEnv->index;
  sBase = ClEnv->base;
  debug = ClEnv->debug_I;
  trace = ClEnv->trace_I;
  gIndex = ClAlloc->index;
  gBase = ClAlloc->base;
  ecout = ClEnv->cout;
  if (ClAlloc->statusGC != 2) GC_PUSH(ecout); //<sb> push the last output
  ClEnv->cHandle++; }

// restore a good state
void ClaireHandler::catchIt()
{ ClEnv->last_debug = ClEnv->debug_I;          // "last" values for debugger
  ClEnv->last_index = ClEnv->index;         // same
  ClEnv->last_trace = ClEnv->trace_I;
  ClEnv->index = sIndex;
  ClEnv->base = sBase;
  ClEnv->debug_I = debug;
  ClEnv->trace_I = trace;
  ClAlloc->index = gIndex;
  ClAlloc->base = gBase; 
  ClEnv->cHandle--;
  ClEnv->cout = ecout;           //<sb> restore output on error
  ClAlloc->currentNew = NULL; } //<sb> ensure no tmp alloc if an alloc error occur!



// system error handling - C++ API ---------------------------------
CL_EXPORT CL_INT Cerror(CL_INT n, OID a, OID b)
{ if (n == -2) {ClEnv->cout = OBJECT(PortObject,Core.Clib_stderr->value);             // v3.3
                princ_string("Assertion violation in file "); princ_string((char *) a);
                princ_string(" [line "); princ_integer(b); princ_string("]\n");
                ClEnv->abort();}
  else if (n == -1) { ClEnv->cout = OBJECT(PortObject,Core.Clib_stderr->value);             // v3.3
                      princ_string("System Error: "); princ_string((char *) a);
                      princ_string("\n");
                      ClEnv->abort();}
  else close_exception((ClaireException *) system_error::make(n,a,b));
  return 0;}

//<sb>
CL_EXPORT CL_INT Cerrorno(CL_INT n, OID a, OID b) {
  #ifdef CLPC
  close_exception((ClaireException *) system_error::make(n,GetLastError(),a,b));
  #else
  close_exception((ClaireException *) system_error::make(n,errno,a,b));
  #endif
  return 0;
}

//<sb>
CL_EXPORT CL_INT Cerror(CL_INT n, ClaireClass* c, OID a, OID b) {
  close_exception((ClaireException *) system_error::make(n,c,a,b));
  return 0;
}

//<sb>
CL_EXPORT CL_INT Cerrorno(CL_INT n, ClaireClass* c, OID a, OID b) {
  #ifdef CLPC
  close_exception((ClaireException *) system_error::make(n,GetLastError(),c,a,b));
  #else
  close_exception((ClaireException *) system_error::make(n,errno,c,a,b));
  #endif
  return 0;
}


// create a system_error
system_error *system_error::make(CL_INT n, OID x, OID y)
{system_error *o = (system_error *) ClAlloc->makeAny(5);
  o->isa = Kernel._system_error;
  o->index = n;
  o->cerr = 0;
  o->value = x;
  o->arg = y;
  return o;}

system_error *system_error::make(CL_INT n, CL_INT cerrcode, OID x, OID y)
{system_error *o = (system_error *) ClAlloc->makeAny(5);
  o->isa = Kernel._system_error;
  o->cerr = cerrcode;
  o->index = n;
  o->value = x;
  o->arg = y;
  return o;}

system_error *system_error::make(CL_INT n, ClaireClass* c, OID x, OID y)
{system_error *o = (system_error *) ClAlloc->makeAny(5);
  o->isa = c;
  o->cerr = 0;
  o->index = n;
  o->value = x;
  o->arg = y;
  return o;}

system_error *system_error::make(CL_INT n, CL_INT cerrcode, ClaireClass* c, OID x, OID y)
{system_error *o = (system_error *) ClAlloc->makeAny(5);
  o->isa = c;
  o->cerr = cerrcode;
  o->index = n;
  o->value = x;
  o->arg = y;
  return o;}


/***********************************************************************/
/**                 2: System creation functions                       */
/***********************************************************************/


// we now assume that a project/module file p.cpp is generated that contains the
// following functions:
// loadModules() which (a) build all the modules (fill the associated namespaces)
//                     (b) run the generated metaLoad() methods


// how to run the CLAIRE system
void ClaireResource::run()
{  ClAlloc->init();                  // memory  allocation
   ClRes->init();                    // initialization of the Resource object
   ClEnv->init();                    // initialization of the Environment object
   GC_BIND;
   Kernel.metaLoad();                   // load the first module
   {ClaireHandler c = ClaireHandler();
      if ERROR_IN { //GC_BIND;
                   fLoadModules();      // load all the other modules
                   //GC_UNBIND; //<sb> we should keep a pointer on optimized global vars
                   //printf("index= %d, base=%d\n", ClAlloc->index, ClAlloc->base);
                   ERROR_FREE;}
       else {c.catchIt();
           ClEnv->cout = OBJECT(PortObject, Core.cl_stdout->value);
      if (getenv("SERVER_SOFTWARE")) {
        printf("Content-Type: text/html\r\n\r\n");
        fflush(stdout);
        printf("<b><font color=red>[WCL fatal error - abort :</font></b><br>");
        printf("An error has occured in the compiled code:<br>");
        fflush(stdout);
        COLOR = 2;
        (*Kernel.print)(_oid_(ClEnv->exception_I));
        COLOR = 0;
        printf("<b><font color=red>]</font></b>");
        fflush(stdout);
             } else {
               princ_string("\nAn error has occured in the compiled code ...\n");
               (*Kernel.print)(_oid_(ClEnv->exception_I));
            }
            CL_exit(1);
          }
   GC_UNBIND; //<sb> we should keep a pointer on optimized global vars //<sb> no more optimized vars
   }}


// initialization of ClRes
void ClaireResource::init()
{ cWorld = 0;
  cWorldId = 0;
  iIndex = 0;                   // base (previous top) for integer world stack
  iBase = 0;                    // base (previous top) for integer world stack
  oIndex = 0;                   // index (current top)
  oBase = 0;                    // base (previous top) for integer world stack
  fIndex = 0;                   // index (current top)
  fBase = 0;                    // index (current top)
}


// generic hashing function: this is the heart of powerfull alists !
// The mask is supposed to be 0x001...1 and the result is between 0 and mask
CL_INT ClaireResource::hashOid(CL_INT mask, OID x)
{if IDENTIFIED(x)                    // v3.1.10 -> there was a strange bug with CTAG
    return (x & mask);
 else {ClairePrimitive *z = OBJECT(ClairePrimitive,x);
        if ((z->isa == Kernel._list) || (z->isa == Kernel._set) || (z->isa == Kernel._tuple)) // v3.2.16
          {ITERATE(j);
           CL_INT r = 0;
             for (START(((bag *) z)); NEXT(j);)  r = r + hashOid(mask,j);
             return r & mask;}
         else if (z->isa == Kernel._string)
              return claire.it->hash(string_v(x));
         else if (z->isa == Kernel._cl_import)              // v3.3.22
             return (((ClaireImport *) z)->value & mask);
         else if (z->isa == Kernel._float)
            return (((CL_INT) ((ClaireFloat *) z)->value) & mask);
         else return (x & mask);}
 }

/***********************************************************************/
/**        3: ClaireEnvironement functions                             */
/***********************************************************************/

#ifdef HAVE_SIGPROCMASK
sigset_t allsigs;
#endif


void ClaireEnvironment::init()

{ module_I = claire.it;
  cHandle = 0;                  // first handler pointer
  gensym = 0;
  tIndex = 0;                   // first time counter
  base = 0;                     // gc stack base
  trace_I = 0;
  debug_I = -1;                 // -1 means no debug
  index = 1;
  step_I = 0;
  count_trigger = 0;                    // v3.1.16 !!
  name = "Kernel";
  exception_I = NULL;
  spy_I = NULL;
  close = -1;                           // c: do not touch,   p:read only
  verbose = 0;
  ABSTRACT = 0;                         // c: no more instances
  FINAL = 1;                            // c: no more subclasses
  DEFAULT = 2;                          //
  open = 3;                             // p: open property (extensible)
                                        // c: use dynamic compiling
  ephemeral = 4;                       // c:ephemeral objects
  
  bLength = 0;
  allocLength = 256;
  buffer = (char*)malloc(256);

#ifdef HAVE_SIGPROCMASK
    sigfillset(&allsigs);
    //<sb> don't block signals that create a core dump
    #ifdef SIGSEGV
    sigdelset(&allsigs, SIGSEGV);
    #endif
    #ifdef SIGVTALRM
    sigdelset(&allsigs, SIGVTALRM);
    #endif
    #ifdef SIGBUS
    sigdelset(&allsigs, SIGBUS);
    #endif
    #ifdef SIGILL
    sigdelset(&allsigs, SIGILL);
    #endif
    #ifdef SIGQUIT
    sigdelset(&allsigs, SIGQUIT);
    #endif
    #ifdef SIGTRAP
    sigdelset(&allsigs, SIGTRAP);
    #endif
    #ifdef SIGABRT
    sigdelset(&allsigs, SIGABRT);
    #endif
    #ifdef SIGEMT
    sigdelset(&allsigs, SIGEMT);
    #endif
    #ifdef SIGFPE
    sigdelset(&allsigs, SIGFPE);
    #endif
    #ifdef SIGSYS
    sigdelset(&allsigs, SIGSYS);
    #endif
    #ifdef SIGSTOP
    sigdelset(&allsigs, SIGSTOP);
    #endif
#endif
  }


// creates a fatal exception
void ClaireEnvironment::abort()
{ close_exception(system_error::make(-1,_string_("corrupted memory"),0));}

// restore a good working state. m is the reader or 0
// used to be called clean_state -> 
CL_EXPORT void restore_state_void()
{ ClAlloc->index = 3;
  ClAlloc->base = 1;
  ClAlloc->index = 1; //<sb> v3.3.35 see ClRes->init()
  ClAlloc->base = 0;
  ClEnv->cout = OBJECT(PortObject,Core.Clib_stdout->value);             // v3.3
}


void ClaireEnvironment::bufferStart() {
  if (allocLength > 4096) {
    char *buf = (char*)realloc(buffer, 256);
    if (buf) {
      allocLength = 256;
      buffer = buf;
    }
  }
  bLength = 0;
  *buffer = 0;}

CL_INT ClaireEnvironment::pushAttempt(CL_INT n) {
  if (bLength + n >= allocLength) {
    CL_INT newlen = allocLength;
    while (bLength + n >= newlen)
      newlen += 256;
    char *buf = (char*)realloc(buffer, newlen);
    if (buf == NULL)
      Cerror(16,0,0);
    allocLength = newlen;
    buffer = buf;
    return 1;
  }
  return 0;
}

// prints a char in the string buffer
//<sb> moved from Kernel.h -> inline cyqwin
void ClaireEnvironment::pushChar(char c) {              
  pushAttempt(1);
  buffer[bLength++] = c;
  buffer[bLength] = 0;
}

// buffer functions ------------------------------------------------------------
// makes a string from the buffer
char *ClaireEnvironment::bufferCopy()
{char *buf = ClAlloc->makeString(bLength);        // v3.2.01 !
 if(bLength) memcpy(buf, buffer, bLength);
 buf[bLength] = 0;
 return buf;}

// prints an integer in the string buffer
void ClaireEnvironment::pushInteger(CL_INT n) {
  char sprintfbuf[32];
#ifdef __LP64__
  sprintf(sprintfbuf, "%ld", n);
#else
  sprintf(sprintfbuf, "%d", n);
#endif
  CL_INT len = strlen(sprintfbuf);
  
  pushAttempt(len);
    memcpy(buffer + bLength, sprintfbuf, len + 1); //<sb> including trailing \0
    bLength += len;
}


/***********************************************************************/
/**        4: Function handling                                        */
/***********************************************************************/


// ----------- API functions -------------------------------------------

// retunrs the C value that we put in the stack (a function to avoid overNesting)
static inline CL_INT Cpointer(OID x, ClaireClass *c) {return CPOINTER(x,c);}


// moves the stack pointer up by x units */
CL_EXPORT void stack_add(CL_INT x)
{CL_INT z = ClEnv->base + x;
 if (z + 100 >= ClAlloc->maxStack) // take a range so that the error handler can execute
   error_execution_stack_full();
 OID fill = _oid_(Core.undefined_debug);
 while(ClEnv->index <= z)
  ClEnv->stack[ClEnv->index++] = fill;
 ClEnv->index = z;}

// apply a function on an argument, two arguments or more
CL_EXPORT OID fcall1(ClaireFunction *f,ClaireClass *s1,OID a1,ClaireClass *s)
{CL_INT x;
   x = ((fptr1) f->value)((CL_INT) CPOINTER(a1,s1));
   return CLAIREOID(x,s);}

CL_EXPORT OID fcall2(ClaireFunction *f,ClaireClass *s1, OID a1,ClaireClass *s2, OID a2,ClaireClass *s)
{CL_INT x;
   x = ((fptr2) f->value)((CL_INT)CPOINTER(a1,s1), (CL_INT) CPOINTER(a2,s2));
   return CLAIREOID(x,s);}

CL_EXPORT OID fcall3(ClaireFunction *f,ClaireClass *s1, OID a1,ClaireClass *s2,
           OID a2, ClaireClass *s3, OID a3, ClaireClass *s)
{CL_INT x;
   x = ((fptr3) f->value)((CL_INT)CPOINTER(a1,s1), (CL_INT) CPOINTER(a2,s2),
                          (CL_INT) CPOINTER(a3,s3));
   return CLAIREOID(x,s);}


#define FAPPLY(F,f,l) (((F) f->value)l)
#define AR(m) args[m]

OID stack_apply_function_more(ClaireFunction *f, CL_INT n, CL_INT m, CL_INT i, OID *ct, CL_INT *st);

//<sb> throw an execution stack overflow error
CL_EXPORT void error_execution_stack_full() {
   if (ClEnv->exception_I == NULL ||
       !(ClEnv->exception_I->isa == Kernel._system_error &&
         ((system_error*)ClEnv->exception_I)->index == 24))
     Cerror(24,ClEnv->index,0);
}

// apply a function to a list of arguments placed into the stack (m to n)
//<sb> unrolled for message with 3 or less arguments
CL_EXPORT OID stack_apply_function(ClaireFunction *f, list *l, CL_INT n, CL_INT m)
{CL_INT x;
 if (ClEnv->index + 100 >= ClAlloc->maxStack)
   error_execution_stack_full();
 m = m - n;
 char N = m;
 
 CL_INT i = m;
 CL_INT *st = ClEnv->stack + n;
 OID *ct = l->content + 1;
 ClaireClass *s = OBJECT(ClaireClass,*ct);
 CL_INT arg1 = CPOINTER(*st, s);
 switch (N) {
   case 1:
    {x = FAPPLY(fptr1,f,(arg1));
    break;}
   case 2:
    {ClaireClass *s1 = OBJECT(ClaireClass,ct[1]);
    x = FAPPLY(fptr2,f,(arg1, CPOINTER(st[1], s1)));
    break;}
   case 3:
    {ClaireClass *s1 = OBJECT(ClaireClass,ct[1]);
    ClaireClass* s2 = OBJECT(ClaireClass,ct[2]);
    x = FAPPLY(fptr3,f,(arg1, CPOINTER(st[1], s1), CPOINTER(st[2], s2)));
    break;}
   default:
     x = stack_apply_function_more(f,n,m,i,ct,st);
  }   
 ClEnv->index = n;
 s = OBJECT(ClaireClass,ct[m]);
 return CLAIREOID(x, s);
}


OID stack_apply_function_more(ClaireFunction *f, CL_INT n, CL_INT m, CL_INT i, OID *ct, CL_INT *st) {
 static CL_INT args[20];
  OID x;
   while(i) {
     ClaireClass *s = OBJECT(ClaireClass,ct[--i]);
    args[i] = CPOINTER(st[i], s);
   }
       if (m == 4) x = FAPPLY(fptr4,f,(AR(0),AR(1),AR(2),AR(3)));
   else if (m == 5)  x = FAPPLY(fptr5,f,(AR(0),AR(1),AR(2),AR(3),AR(4)));
   else if (m == 6)  x = FAPPLY(fptr6,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5)));
   else if (m == 7)  x = FAPPLY(fptr7,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6)));
   else if (m == 8)  x = FAPPLY(fptr8,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7)));
   else if (m == 9)  x = FAPPLY(fptr9,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8)));
   else if (m == 10)  x = FAPPLY(fptr10,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9)));
   else if (m == 11)  x = FAPPLY(fptr11,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10)));
   else if (m == 12)  x = FAPPLY(fptr12,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11)));
   else if (m == 13)  x = FAPPLY(fptr13,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11),AR(12)));
   else if (m == 14)  x = FAPPLY(fptr14,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11),AR(12),AR(13)));
   else if (m == 15)  x = FAPPLY(fptr15,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11),AR(12),AR(13),AR(14)));
   else if (m == 16)  x = FAPPLY(fptr16,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11),AR(12),AR(13),AR(14),AR(15)));
   else if (m == 17)  x = FAPPLY(fptr17,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11),AR(12),AR(13),AR(14),AR(15),AR(16)));
   else if (m == 18)  x = FAPPLY(fptr18,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11),AR(12),AR(13),AR(14),AR(15),AR(16),AR(17)));
   else if (m == 19)  x = FAPPLY(fptr19,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11),AR(12),AR(13),AR(14),AR(15),AR(16),AR(17),AR(18)));
   else if (m == 20)  x = FAPPLY(fptr20,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11),AR(12),AR(13),AR(14),AR(15),AR(16),AR(17),AR(18),AR(19)));
   else Cerror(32,_oid_(f),m);
 return x;
}


// the name of a function
CL_EXPORT char *string_I_function(ClaireFunction *f)
{ return f->name;}


/*********************************************************************/
/**    5. World functions                                            */
/*********************************************************************/

// defeasible update on a list
CL_EXPORT OID store_list(list *l, CL_INT n, OID y, ClaireBoolean *b)
{CL_INT *z = (CL_INT*)&(l->content[n]);
   if (b == CTRUE && ClRes->cWorld != 0) STOREOID(z,*z)
   return (*z = y);}

// defeasible update on a list
CL_EXPORT OID store_array(OID* a, CL_INT n, OID y, ClaireBoolean *b)
{if ARRAYFLOAT(a)
    {double *z = &(((double *) a)[n]);
     if (b == CTRUE && ClRes->cWorld != 0) STOREFLOAT(z,*z)
     return (OID)(*z = float_v(y));}
 else {CL_INT *z = (CL_INT*)&a[n];
       if (b == CTRUE && ClRes->cWorld != 0) STOREOID(z,*z)
       return (OID)(*z = y);}
}

// get the value, even if it is unknown
// we do not need to copy floats anymore since the stack has its own storage
CL_EXPORT OID store_object(ClaireObject *x, CL_INT n, ClaireClass *s, OID y, ClaireBoolean *b)
{
if (s == Kernel._float)
    {double *z = (double *) SLOTADR(x,n);
     if (b == CTRUE && ClRes->cWorld != 0)  STOREFLOAT(z,*z)
     *z = float_v(y);
     return y;}
else if (s == Kernel._any || s == Kernel._integer)
      {CL_INT *z = SLOTADR(x,n);
       if (b == CTRUE && ClRes->cWorld != 0)  STOREOID(z,*z)
       return (*z = y);}
 else {CL_INT *z = SLOTADR(x,n);
       if (b == CTRUE && ClRes->cWorld != 0)
          STOREOBJ(z,(ClaireObject *) *z)
       *z = ((y == CNULL) ? 0 : CPOINTER(y,s));
       return y;}}

// performs an addition to a list and store the relevant changes
// v3.3.06: this only works if enough memory has beed added beforehand
CL_EXPORT list *store_add(list *l,OID y)
{if (l->length + 1 == (*l)[0])
  Cerror(43, _oid_(l), l->length);
 if (ClRes->cWorld) STOREOID(&(l->length),l->length)
        return l->addFast(y); //
}

CL_EXPORT CL_INT worldCongestion() {
  CL_INT good = 1;
  if (ClRes->iIndex >= ClAlloc->maxHist ||
    ClRes->oIndex >= ClAlloc->maxHist ||
    ClRes->fIndex >= ClAlloc->maxHist) {
  good = 0;
  if(ClAlloc->mem_auto) {
    void *adr = realloc(ClRes->haiStack, 2 * ClAlloc->maxHist * sizeof(CL_INT*));
    if(adr) {
      ClRes->haiStack = (OID**)adr;
      adr = realloc(ClRes->hviStack, 2 * ClAlloc->maxHist * sizeof(CL_INT));
      if(adr) {
        ClRes->hviStack = (OID*)adr;
        adr = realloc(ClRes->hvoStack, 2 * ClAlloc->maxHist * sizeof(ClaireObject*));
        if(adr) {
          ClRes->hvoStack = (ClaireObject**)adr;
          adr = realloc(ClRes->hafStack, 2 * ClAlloc->maxHist * sizeof(CL_INT*));
          if(adr) {
            ClRes->hafStack = (double**)adr;
            adr = realloc(ClRes->hvfStack, 4 * ClAlloc->maxHist * sizeof(double));
            if(adr) {
              ClRes->hvfStack = (double*)adr;
              adr = realloc(ClRes->haoStack, 2 * ClAlloc->maxHist * sizeof(CL_INT*));
              if(adr) {
                ClRes->haoStack = (OID**)adr;
                good = 1;
                PortObject *p = ClEnv->cout;
                ClEnv->cout = ClEnv->ctrace;
                princ_string("World stack congestion, increase memory.\n");
                ClEnv->cout = p;
                ClAlloc->maxHist *= 2;}}}}}}}} return good; }

// add one new world
CL_EXPORT void world_push ()
{if (worldCongestion() == 0) Cerror(37,0,0);
 ClRes->cWorld++;
 ClRes->cWorldId++;                  // v3.2.04
 ClRes->haiStack[++ClRes->iIndex] = (OID *) ClRes->iBase;
 ClRes->iBase = ClRes->iIndex;
 ClRes->haoStack[++ClRes->oIndex] = (OID *) ClRes->oBase;
 ClRes->hvoStack[ClRes->oIndex] = NULL;
 ClRes->oBase = ClRes->oIndex;
 ClRes->hafStack[++ClRes->fIndex] = (double *) ClRes->fBase;
 ClRes->fBase = ClRes->fIndex;}

// remove a world and perform all modifications stored in the stack
CL_EXPORT void world_pop ()
{ClRes->cWorldId++;                       // v3.2.04
 if (ClRes->cWorld-- == 0) ClRes->cWorld++;
 else {CL_INT x = ClRes->iIndex + 1, y = ClRes->iBase;
       while (--x != y) {*(ClRes->haiStack[x]) = ClRes->hviStack[x];}
       ClRes->iIndex = y - 1;
       ClRes->iBase = (CL_INT) ClRes->haiStack[y];
       x = ClRes->oIndex + 1; y = ClRes->oBase;
       while (--x != y) {if (ClRes->haoStack[x] != NULL) *(ClRes->haoStack[x]) = (CL_INT) ClRes->hvoStack[x];}
       ClRes->oIndex = y - 1;
       ClRes->oBase = (CL_INT) ClRes->haoStack[y];
       x = ClRes->fIndex + 1; y = ClRes->fBase;
       while (--x != y) {*( (double *) ClRes->hafStack[x]) = ClRes->hvfStack[x];}
       ClRes->fIndex = y - 1;
       ClRes->fBase = (CL_INT) ClRes->hafStack[y];}}


// commit: all updates are accepted but the traing info is conserved unless in world 1
CL_EXPORT void world_remove (void)
{if (ClRes->cWorld <= 1) world_slaughter();
 else { ClRes->cWorld--;
        if (ClRes->cWorld == -1) ClRes->cWorld++;
        CL_INT y = ClRes->iBase;
        ClRes->iBase = (CL_INT) ClRes->haiStack[y];       // v3.2.04: base(n - 1) is restored ...
        ClRes->haiStack[y] = &(ClRes->hviStack[y]);    // .. and the cell for base(n) is neutralized
        y = ClRes->oBase;
        ClRes->oBase = (CL_INT) ClRes->haoStack[y];
        if (ClRes->haoStack[y] != NULL) 
          ClRes->haoStack[y] = (OID *) &(ClRes->hvoStack[y]);
        y = ClRes->fBase;
        ClRes->fBase = (CL_INT) ClRes->hafStack[y];
        ClRes->hafStack[y] = (double *) &(ClRes->hvfStack[y]);}}
       

// this is the tough version that is irreversible
CL_EXPORT void world_slaughter (void)
{if (ClRes->cWorld-- == 0)
    {ClRes->cWorld++; ClRes->iBase = 0; ClRes->iIndex = 0;  // yc: crude ... may be wrong
     ClRes->oBase = 0; ClRes->oIndex = 0;
     ClRes->fBase = 0; ClRes->fIndex = 0;}
 else  {CL_INT y = ClRes->iBase;
        ClRes->iIndex = y - 1;
        ClRes->iBase = (CL_INT) ClRes->haiStack[y];
        y = ClRes->oBase;
        ClRes->oIndex = y - 1;
        ClRes->oBase = (CL_INT) ClRes->haoStack[y];
        y = ClRes->fBase;
        ClRes->fIndex = y - 1;
        ClRes->fBase = (CL_INT) ClRes->hafStack[y];}}

// give the current world
CL_EXPORT CL_INT world_number (void)  {return ClRes->cWorld;}

// give the current world
CL_EXPORT CL_INT world_get_id (void)  {return ClRes->cWorldId;}

/**********************************************************************/
/**    7: signal handling base (xl)                                   */
/**********************************************************************/

CL_EXPORT CL_INT claire_runs = 0;

#define SIG_STACK_SIZE 32
CL_INT pending_signals[SIG_STACK_SIZE];
CL_EXPORT CL_INT n_pending_signal = 0;
CL_EXPORT CL_INT avoid_signal_handling = 0;
CL_EXPORT CL_INT avoid_signal_caching = 0;
//<sb> in claire we have a generic kernel sig handler
// at the meta level we have a table that maps signals to
// properties (see meta/signal.cl)...
extern CL_IMPORT ClaireBoolean* meta_sighandler_integer(CL_INT sig);

#ifdef CLPC
BOOL WINAPI win_ctrl_handler(DWORD ev) {
  switch( ev ) {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
      kernel_sighandler_integer(SIGINT);
      return TRUE;
  }
  return FALSE;
}

class WinInstallHandler {
public:
  static WinInstallHandler single;
  WinInstallHandler() {
    SetConsoleCtrlHandler(win_ctrl_handler, TRUE);
  }
 ~WinInstallHandler() {}
};

WinInstallHandler WinInstallHandler::single = WinInstallHandler();

#endif


CL_EXPORT CL_INT kernel_pop_signal() {
  if(claire_runs && avoid_signal_handling == 0) {
    avoid_signal_handling = 1;
    #ifdef HAVE_SIGPROCMASK
    sigset_t prev_sigset;
    sigprocmask(SIG_SETMASK,&allsigs,&prev_sigset);
    #endif
    CL_INT isig = 0;
    CL_INT thrown = 0;
    while(isig < n_pending_signal) {
      CL_INT sig = pending_signals[isig++];
      if (sig == SIGINT)
        while(isig + 1 < n_pending_signal && sig == pending_signals[isig+1])
          isig++;
      if(meta_sighandler_integer(sig) == CFALSE) {
        if(ClEnv->cHandle != 0) {
          thrown = 1;
          break;
        }
      }
    }
    if (isig < n_pending_signal) {
      CL_INT i = 0;
      while(isig < n_pending_signal)
        pending_signals[i++] = pending_signals[isig++];
      n_pending_signal = i;
    }
    else n_pending_signal = 0;
    #ifdef HAVE_SIGPROCMASK
    sigprocmask(SIG_SETMASK,&prev_sigset,0);
    #endif
    //<sb> the handler has raised something, since it has
    // been catched raise it again in the main program
    avoid_signal_handling = 0;
    if (thrown) close_exception(ClEnv->exception_I);
  }
  return 0;
}

CL_EXPORT void kernel_sighandler_integer(int sig) {
  #ifdef HAVE_SIGPROCMASK
  sigset_t nset, oset;
  sigemptyset(&nset);
  sigaddset(&nset, sig);
  sigprocmask(SIG_BLOCK, &nset, &oset);
  #endif
  if(avoid_signal_handling == 0 &&
        n_pending_signal < SIG_STACK_SIZE) {
    pending_signals[n_pending_signal] =
      (n_pending_signal + 1 == SIG_STACK_SIZE) ?
        -1 : //<sb> sig stack overflow
        sig;
    n_pending_signal++;
  }
  #ifndef CLPC
  signal(sig, kernel_sighandler_integer); //<sb> reinstall the signal
  #endif
  #ifdef HAVE_SIGPROCMASK
  sigprocmask(SIG_SETMASK, &oset, NULL);
  #endif
  if (avoid_signal_caching)
    kernel_pop_signal();
}

/**********************************************************************/
/**    8: C error mapping (xl)                                        */
/**********************************************************************/

//<sb> From glib/msdn
CL_EXPORT char* cerror_integer(CL_INT errnum)
{

#ifdef HAVE_STRERROR
  return strerror(errnum);
#elif SYS_ERRLIST
  extern CL_INT sys_nerr;
  extern char *sys_errlist[];

  if ((errnum > 0) && (errnum <= sys_nerr))
    return sys_errlist[errnum];
#else
  switch (errnum)
    {
#ifdef E2BIG
    case E2BIG: return "E2BIG: argument list too long";
#endif
#ifdef EACCES
    case EACCES: return "EACCES: permission denied";
#endif
#ifdef EADDRINUSE
    case EADDRINUSE: return "EADDRINUSE: address already in use";
#endif
#ifdef EADDRNOTAVAIL
    case EADDRNOTAVAIL: return "EADDRNOTAVAIL: can't assign requested address";
#endif
#ifdef EADV
    case EADV: return "EADV: advertise error";
#endif
#ifdef EAFNOSUPPORT
    case EAFNOSUPPORT: return "EAFNOSUPPORT: address family not supported by protocol family";
#endif
#ifdef EAGAIN
    case EAGAIN: return "EAGAIN: try again";
#endif
#ifdef EALIGN
    case EALIGN: return "EALIGN";
#endif
#ifdef EALREADY
    case EALREADY: return "EALREADY: operation already in progress";
#endif
#ifdef EBADE
    case EBADE: return "EBADE: bad exchange descriptor";
#endif
#ifdef EBADF
    case EBADF: return "EBADF: bad file number";
#endif
#ifdef EBADFD
    case EBADFD: return "EBADFD: file descriptor in bad state";
#endif
#ifdef EBADMSG
    case EBADMSG: return "EBADMSG: not a data message";
#endif
#ifdef EBADR
    case EBADR: return "EBADR: bad request descriptor";
#endif
#ifdef EBADRPC
    case EBADRPC: return "EBADRPC: RPC structure is bad";
#endif
#ifdef EBADRQC
    case EBADRQC: return "EBADRQC: bad request code";
#endif
#ifdef EBADSLT
    case EBADSLT: return "EBADSLT: invalid slot";
#endif
#ifdef EBFONT
    case EBFONT: return "EBFONT: bad font file format";
#endif
#ifdef EBUSY
    case EBUSY: return "EBUSY: mount device busy";
#endif
#ifdef ECHILD
    case ECHILD: return "ECHILD: no children";
#endif
#ifdef ECHRNG
    case ECHRNG: return "ECHRNG: channel number out of range";
#endif
#ifdef ECOMM
    case ECOMM: return "ECOMM: communication error on send";
#endif
#ifdef ECONNABORTED
    case ECONNABORTED: return "ECONNABORTED: software caused connection abort";
#endif
#ifdef ECONNREFUSED
    case ECONNREFUSED: return "ECONNREFUSED: connection refused";
#endif
#ifdef ECONNRESET
    case ECONNRESET: return "ECONNRESET: connection reset by peer";
#endif
#if defined(EDEADLK) && (!defined(EWOULDBLOCK) || (EDEADLK != EWOULDBLOCK))
    case EDEADLK: return "EDEADLK: resource deadlock avoided";
#endif
//<sb> on linux if we don't make this test it generates a compile error
#if defined(EDEADLOCK) && EDEADLOCK != EDEADLK
    case EDEADLOCK: return "EDEADLOCK: resource deadlock avoided";
#endif
#ifdef EDESTADDRREQ
    case EDESTADDRREQ: return "EDESTADDRREQ: destination address required";
#endif
#ifdef EDIRTY
    case EDIRTY: return "EDIRTY: mounting a dirty fs w/o force";
#endif
#ifdef EDOM
    case EDOM: return "EDOM: math argument out of range";
#endif
#ifdef EDOTDOT
    case EDOTDOT: return "EDOTDOT: cross mount point";
#endif
#ifdef EDQUOT
    case EDQUOT: return "EDQUOT: disk quota exceeded";
#endif
#ifdef EDUPPKG
    case EDUPPKG: return "EDUPPKG: duplicate package name";
#endif
#ifdef EEXIST
    case EEXIST: return "EEXIST: file already exists";
#endif
#ifdef ENOTEMPTY
#if ENOTEMPTY != EEXIST
    case ENOTEMPTY: return "ENOTEMPTY: directory not empty";
#endif
#endif
#ifdef EFAULT
    case EFAULT: return "EFAULT: bad address in system call argument";
#endif
#ifdef EFBIG
    case EFBIG: return "EFBIG: file too large";
#endif
#ifdef EHOSTDOWN
    case EHOSTDOWN: return "EHOSTDOWN: host is down";
#endif
#ifdef EHOSTUNREACH
    case EHOSTUNREACH: return "EHOSTUNREACH: host is unreachable";
#endif
#ifdef EIDRM
    case EIDRM: return "EIDRM: identifier removed";
#endif
#ifdef EINIT
    case EINIT: return "EINIT: initialization error";
#endif
#ifdef EINPROGRESS
    case EINPROGRESS: return "EINPROGRESS: operation now in progress";
#endif
#ifdef EINTR
    case EINTR: return "EINTR: interrupted system call";
#endif
#ifdef EINVAL
    case EINVAL: return "EINVAL: invalid argument";
#endif
#ifdef EIO
    case EIO: return "EIO: I/O error";
#endif
#ifdef EISCONN
    case EISCONN: return "EISCONN: socket is already connected";
#endif
#ifdef EISDIR
    case EISDIR: return "EISDIR: is a directory";
#endif
#ifdef EISNAME
    case EISNAM: return "EISNAM: is a name file";
#endif
#ifdef ELBIN
    case ELBIN: return "ELBIN";
#endif
#ifdef EL2HLT
    case EL2HLT: return "EL2HLT: level 2 halted";
#endif
#ifdef EL2NSYNC
    case EL2NSYNC: return "EL2NSYNC: level 2 not synchronized";
#endif
#ifdef EL3HLT
    case EL3HLT: return "EL3HLT: level 3 halted";
#endif
#ifdef EL3RST
    case EL3RST: return "EL3RST: level 3 reset";
#endif
#ifdef ELIBACC
    case ELIBACC: return "ELIBACC: can not access a needed shared library";
#endif
#ifdef ELIBBAD
    case ELIBBAD: return "ELIBBAD: accessing a corrupted shared library";
#endif
#ifdef ELIBEXEC
    case ELIBEXEC: return "ELIBEXEC: can not exec a shared library directly";
#endif
#ifdef ELIBMAX
    case ELIBMAX: return "ELIBMAX: attempting to link in more shared libraries than system limit";
#endif
#ifdef ELIBSCN
    case ELIBSCN: return "ELIBSCN: .lib section in a.out corrupted";
#endif
#ifdef ELNRNG
    case ELNRNG: return "ELNRNG: link number out of range";
#endif
#ifdef ELOOP
    case ELOOP: return "ELOOP: too many levels of symbolic links";
#endif
#ifdef EMFILE
    case EMFILE: return "EMFILE: too many open files";
#endif
#ifdef EMLINK
    case EMLINK: return "EMLINK: too many links";
#endif
#ifdef EMSGSIZE
    case EMSGSIZE: return "EMSGSIZE: message too long";
#endif
#ifdef EMULTIHOP
    case EMULTIHOP: return "EMULTIHOP: multihop attempted";
#endif
#ifdef ENAMETOOLONG
    case ENAMETOOLONG: return "ENAMETOOLONG: file name too long";
#endif
#ifdef ENAVAIL
    case ENAVAIL: return "ENAVAIL: not available";
#endif
#ifdef ENET
    case ENET: return "ENET";
#endif
#ifdef ENETDOWN
    case ENETDOWN: return "ENETDOWN: network is down";
#endif
#ifdef ENETRESET
    case ENETRESET: return "ENETRESET: network dropped connection on reset";
#endif
#ifdef ENETUNREACH
    case ENETUNREACH: return "ENETUNREACH: network is unreachable";
#endif
#ifdef ENFILE
    case ENFILE: return "ENFILE: file table overflow";
#endif
#ifdef ENOANO
    case ENOANO: return "ENOANO: anode table overflow";
#endif
#if defined(ENOBUFS) && (!defined(ENOSR) || (ENOBUFS != ENOSR))
    case ENOBUFS: return "ENOBUFS: no buffer space available";
#endif
#ifdef ENOCSI
    case ENOCSI: return "ENOCSI: no CSI structure available";
#endif
#ifdef ENODATA
    case ENODATA: return "ENODATA: no data available";
#endif
#ifdef ENODEV
    case ENODEV: return "ENODEV: no such device";
#endif
#ifdef ENOENT
    case ENOENT: return "ENOENT: no such file or directory";
#endif
#ifdef ENOEXEC
    case ENOEXEC: return "ENOEXEC: exec format error";
#endif
#ifdef ENOLCK
    case ENOLCK: return "ENOLCK: no locks available";
#endif
#ifdef ENOLINK
    case ENOLINK: return "ENOLINK: link has be severed";
#endif
#ifdef ENOMEM
    case ENOMEM: return "ENOMEM: not enough memory";
#endif
#ifdef ENOMSG
    case ENOMSG: return "ENOMSG: no message of desired type";
#endif
#ifdef ENONET
    case ENONET: return "ENONET: machine is not on the network";
#endif
#ifdef ENOPKG
    case ENOPKG: return "ENOPKG: package not installed";
#endif
#ifdef ENOPROTOOPT
    case ENOPROTOOPT: return "ENOPROTOOPT: bad proocol option";
#endif
#ifdef ENOSPC
    case ENOSPC: return "ENOSPC: no space left on device";
#endif
#ifdef ENOSR
    case ENOSR: return "ENOSR: out of stream resources";
#endif
#ifdef ENOSTR
    case ENOSTR: return "ENOSTR: not a stream device";
#endif
#ifdef ENOSYM
    case ENOSYM: return "ENOSYM: unresolved symbol name";
#endif
#ifdef ENOSYS
    case ENOSYS: return "ENOSYS: function not implemented";
#endif
#ifdef ENOTBLK
    case ENOTBLK: return "ENOTBLK: block device required";
#endif
#ifdef ENOTCONN
    case ENOTCONN: return "ENOTCONN: socket is not connected";
#endif
#ifdef ENOTDIR
    case ENOTDIR: return "ENOTDIR: not a directory";
#endif
#ifdef ENOTNAM
    case ENOTNAM: return "ENOTNAM: not a name file";
#endif
#ifdef ENOTSOCK
    case ENOTSOCK: return "ENOTSOCK: socket operation on non-socket";
#endif
#ifdef ENOTTY
    case ENOTTY: return "ENOTTY: inappropriate device for ioctl";
#endif
#ifdef ENOTUNIQ
    case ENOTUNIQ: return "ENOTUNIQ: name not unique on network";
#endif
#ifdef ENXIO
    case ENXIO: return "ENXIO: no such device or address";
#endif
#ifdef EOPNOTSUPP
    case EOPNOTSUPP: return "EOPNOTSUPP: operation not supported on socket";
#endif
#ifdef EPERM
    case EPERM: return "EPERM: not owner";
#endif
#ifdef EPFNOSUPPORT
    case EPFNOSUPPORT: return "EPFNOSUPPORT: protocol family not supported";
#endif
#ifdef EPIPE
    case EPIPE: return "EPIPE: broken pipe";
#endif
#ifdef EPROCLIM
    case EPROCLIM: return "EPROCLIM: too many processes";
#endif
#ifdef EPROCUNAVAIL
    case EPROCUNAVAIL: return "EPROCUNAVAIL: bad procedure for program";
#endif
#ifdef EPROGMISMATCH
    case EPROGMISMATCH: return "EPROGMISMATCH: program version wrong";
#endif
#ifdef EPROGUNAVAIL
    case EPROGUNAVAIL: return "EPROGUNAVAIL: RPC program not available";
#endif
#ifdef EPROTO
    case EPROTO: return "EPROTO: protocol error";
#endif
#ifdef EPROTONOSUPPORT
    case EPROTONOSUPPORT: return "EPROTONOSUPPORT: protocol not suppored";
#endif
#ifdef EPROTOTYPE
    case EPROTOTYPE: return "EPROTOTYPE: protocol wrong type for socket";
#endif
#ifdef ERANGE
    case ERANGE: return "ERANGE: math result unrepresentable";
#endif
#if defined(EREFUSED) && (!defined(ECONNREFUSED) || (EREFUSED != ECONNREFUSED))
    case EREFUSED: return "EREFUSED";
#endif
#ifdef EREMCHG
    case EREMCHG: return "EREMCHG: remote address changed";
#endif
#ifdef EREMDEV
    case EREMDEV: return "EREMDEV: remote device";
#endif
#ifdef EREMOTE
    case EREMOTE: return "EREMOTE: pathname hit remote file system";
#endif
#ifdef EREMOTEIO
    case EREMOTEIO: return "EREMOTEIO: remote i/o error";
#endif
#ifdef EREMOTERELEASE
    case EREMOTERELEASE: return "EREMOTERELEASE";
#endif
#ifdef EROFS
    case EROFS: return "EROFS: read-only file system";
#endif
#ifdef ERPCMISMATCH
    case ERPCMISMATCH: return "ERPCMISMATCH: RPC version is wrong";
#endif
#ifdef ERREMOTE
    case ERREMOTE: return "ERREMOTE: object is remote";
#endif
#ifdef ESHUTDOWN
    case ESHUTDOWN: return "ESHUTDOWN: can't send afer socket shutdown";
#endif
#ifdef ESOCKTNOSUPPORT
    case ESOCKTNOSUPPORT: return "ESOCKTNOSUPPORT: socket type not supported";
#endif
#ifdef ESPIPE
    case ESPIPE: return "ESPIPE: invalid seek";
#endif
#ifdef ESRCH
    case ESRCH: return "ESRCH: no such process";
#endif
#ifdef ESRMNT
    case ESRMNT: return "ESRMNT: srmount error";
#endif
#ifdef ESTALE
    case ESTALE: return "ESTALE: stale remote file handle";
#endif
#ifdef ESUCCESS
    case ESUCCESS: return "ESUCCESS: Error 0";
#endif
#ifdef ETIME
    case ETIME: return "ETIME: timer expired";
#endif
#ifdef ETIMEDOUT
    case ETIMEDOUT: return "ETIMEDOUT: connection timed out";
#endif
#ifdef ETOOMANYREFS
    case ETOOMANYREFS: return "ETOOMANYREFS: too many references: can't splice";
#endif
#ifdef ETXTBSY
    case ETXTBSY: return "ETXTBSY: text file or pseudo-device busy";
#endif
#ifdef EUCLEAN
    case EUCLEAN: return "EUCLEAN: structure needs cleaning";
#endif
#ifdef EUNATCH
    case EUNATCH: return "EUNATCH: protocol driver not attached";
#endif
#ifdef EUSERS
    case EUSERS: return "EUSERS: too many users";
#endif
#ifdef EVERSION
    case EVERSION: return "EVERSION: version mismatch";
#endif
#if defined(EWOULDBLOCK) && (!defined(EAGAIN) || (EWOULDBLOCK != EAGAIN))
    case EWOULDBLOCK: return "EWOULDBLOCK: operation would block";
#endif
#ifdef EXDEV
    case EXDEV: return "EXDEV: cross-domain link";
#endif
#ifdef EXFULL
    case EXFULL: return "EXFULL: message tables full";
#endif
    }
#endif

  static char msg[1024];
  
#ifdef CLPC
  static char oem[1024];
  if(FormatMessage( 
    FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    errnum,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
    (LPTSTR) msg,
    1024,
    NULL) != 0) {
    char *end = msg + strlen(msg) - 1;
    while(end > msg && (*end == '\n' || *end == '\r')) *end-- = 0;
    CharToOemBuff(msg,oem,1024);
    return (char*)oem; }
#endif
#ifdef __LP64__
  sprintf(msg,"unknown error (%ld)", errnum);
#else
  sprintf(msg,"unknown error (%d)", errnum);
#endif
  return msg;
}

/***********************************************************************/
/**   microCLAIRE                                       Yves Caseau    */
/**   clPort.cpp                                                       */
/**  Copyright (C) 1998-2003 Yves Caseau. All Rights Reserved.         */
/**  cf claire.h                                                       */
/***********************************************************************/


// this file contains the I/O objects and methods

/*********************************************************************/
/** Contents                                                         */
/**    1: Claire Ports                                               */
/**    3. Reader functions                                           */
/**    3. Character                                                  */
/**    4. System interface (miscellaneous)                           */
/*********************************************************************/


// ***************************************************************************
// * PART 1: Claire Ports                                                    *
// ***************************************************************************

//<sb> In xlclaire ports are implemented at the meta-level (port.cl)
// the C++ PortObject class however have an API layer
// accessible by the kernel for low-level port operations

#ifdef CLPC
//<sb> on PC we use a sigleton instance that when constructed
// initializes the win sock subsystem
class InitSocket {
public:
  static InitSocket single;
  CL_INT initFailed;
  InitSocket() {
    WSADATA wsaData;
     initFailed = (WSAStartup(0x0101, &wsaData) != 0);
 }
 ~InitSocket() {if(!initFailed) WSACleanup();}
};

InitSocket InitSocket::single = InitSocket();
#endif


CL_EXPORT void prefree_I_any(OID o)  {
  if(ClEnv->verbose > 4) {
     PortObject* p = use_as_output_port(ClEnv->ctrace);
     princ_string("prefree! @ ");
     princ_string(OWNER(o)->name->name);
     princ_string(" not implemented\n");
     use_as_output_port(p);
   }
}

CL_EXPORT void free_I_any(OID o)  {
  if(ClEnv->verbose > 4) {
     PortObject* p = use_as_output_port(ClEnv->ctrace);
     princ_string("free! @ ");
     princ_string(OWNER(o)->name->name);
     princ_string(" not implemented\n");
     use_as_output_port(p);
   }
}


CL_EXPORT PortObject *use_as_output_port(PortObject *p)
{ if (p != ClEnv->cout)
     {PortObject *x = ClEnv->cout;
      ClEnv->cout = p;
      if (ClAlloc->statusGC != 2) GC_PUSH(x);
      return x;}
  else return p;}


char PortObject::get() {
  return getc_port1(this)->ascii;
}

CL_INT PortObject::gets(void* data, CL_INT len) {
  return Core.read_port->fcall((CL_INT)this, (CL_INT)data, len);
}

CL_INT PortObject::eof_ask() {
  return (ClaireBoolean*)Core.eof_port_ask->fcall((CL_INT)this) == CTRUE;
}

void PortObject::put(char c) {
  Core.write_port->fcall((CL_INT)this, (CL_INT)&c, 1);
}

CL_INT PortObject::puts(void* data, CL_INT len) {
  return Core.write_port->fcall((CL_INT)this, (CL_INT)data, len);
}

CL_INT PortObject::puts(const char *data) {
  return Core.write_port->fcall((CL_INT)this, (CL_INT)data, strlen(data));
}

CL_INT PortObject::puts(const char *data, CL_INT sz) {
  return Core.write_port->fcall((CL_INT)this, (CL_INT)data, sz);
}

void PortObject::put(CL_INT n) {
  char sprintfbuf[32];
#ifdef __LP64__
  CL_INT len = sprintf(sprintfbuf,"%ld",n);
#else
  CL_INT len = sprintf(sprintfbuf,"%d",n);
#endif
  Core.write_port->fcall((CL_INT)this, (CL_INT)sprintfbuf, len);
}

static CL_INT fixdot(char* sprintfbuf) {
  CL_INT i = 0, len = strlen(sprintfbuf);
   for(;i < len;i++) {
     if(sprintfbuf[i] == '.') return 1;
     if(sprintfbuf[i] == 'e') return 0;
   }
   strcat(sprintfbuf,".0");
   return 0;
}

void PortObject::put(double x) {
  char sprintfbuf[256];
  sprintf(sprintfbuf,"%f",x);
  if(fixdot(sprintfbuf)) {
    while (sprintfbuf[strlen(sprintfbuf) - 1] == '0')
      sprintfbuf[strlen(sprintfbuf) - 1] = 0;
    if(sprintfbuf[strlen(sprintfbuf) - 1] == '.')
      sprintfbuf[strlen(sprintfbuf)] = '0';
  }
  if(strcmp(sprintfbuf,"-0.0") == 0)
    Core.write_port->fcall((CL_INT)this, (CL_INT)"0.0", 3);
  else
    Core.write_port->fcall((CL_INT)this, (CL_INT)sprintfbuf, strlen(sprintfbuf));
}

// v3.2.54   pretty-print
void PortObject::prettyp(double x) {
  char sprintfbuf[256];
  double y = (CL_INT)floor(x);
  if (x > CLMINFLOAT && x < CLMAXFLOAT && y == x)
    sprintf(sprintfbuf,"%#.1f",x);
  else if (y == 0.0 || ( (x - y) / y > 1e-5 && DECIMAL(x)))
    sprintf(sprintfbuf,"%g",x);               // easy print is OK
  else sprintf(sprintfbuf,"%0.10g",x);          // v3.2.54
  fixdot(sprintfbuf);
  if(strcmp(sprintfbuf,"-0.0") == 0)
    Core.write_port->fcall((CL_INT)this, (CL_INT)"0.0", 3);
  else
    Core.write_port->fcall((CL_INT)this, (CL_INT)sprintfbuf, strlen(sprintfbuf));
};



//<sb> freadline family, useful to parse ports until a condition occurs (e.g. line end)
// one can specify an escape char and a sensitive condition

CL_EXPORT char *freadline_port(PortObject* po) {
  tuple *res = freadline_port6(po, list::alloc(2, _string_("\n"), _string_("\r\n")), CTRUE, 0);
  return string_v(res->content[1]);
}
CL_EXPORT char *freadline_port1(PortObject* po, char* sep) {
  tuple *res = freadline_port6(po, list::alloc(1, _string_(sep)), CTRUE, 0);
  return string_v(res->content[1]);
}
CL_EXPORT char *freadline_port2(PortObject* po, char* sep, ClaireBoolean *sensitive) {
  tuple *res = freadline_port6(po, list::alloc(1, _string_(sep)), sensitive, 0);
  return string_v(res->content[1]);
}
CL_EXPORT char *freadline_port3(PortObject* po, char* sep, ClaireBoolean *sensitive, ClaireChar *escape) {
  tuple *res = freadline_port6(po, list::alloc(1, _string_(sep)), sensitive, escape);
  return string_v(res->content[1]);
}
CL_EXPORT tuple *freadline_port4(PortObject* po, bag *seps) {
  return freadline_port6(po, seps, CTRUE, 0);
}
CL_EXPORT tuple *freadline_port5(PortObject* po, bag *seps, ClaireBoolean *sensitive) {
  return freadline_port6(po, seps, sensitive, 0);
}


struct separator_context {
  CL_INT length;
  CL_INT ischar;
  OID oid;
  char *sep;
};

static CL_INT unsensitive_match(char *travel, CL_INT seplen, char *sep);
static void grow_freadline_buffer(char **travel, char **databuf, CL_INT *buflen, CL_INT n, separator_context *separators);

//<sb> this is the heart of freadline function family
// p is read char by char until a seprator matches
CL_EXPORT tuple *freadline_port6(PortObject* p, bag *seps, ClaireBoolean *sensitive, ClaireChar *escape) {
  if (Core.eof_port_ask->fcall((CL_INT)p) == (CL_INT)CTRUE) {
    return tuple::alloc(2, _string_(""), _string_(""));
  } else {
    char c = 0, esc = escape ? escape->ascii : 0;
    CL_INT n = 0, matched = 0, i, j;
    CL_INT nseparator = 0;
    OID oid;
    //<sb> we use a local malloc'ed buffer prior to import
    // the resulting string in CLAIRE
    char *databuf = (char*)malloc(256);
    if(databuf == 0) Cerror(61,_string_("freadline @ bag"),0);
    CL_INT buflen = 256;
    separator_context *separators  = new separator_context[seps->length];
    separator_context *separator;
    if(separators == 0) {
      free(databuf);
      Cerror(61,_string_("freadline @ bag"),0);
    }
    //<sb> fill seprators with their length and values
    for(i=1;i <= seps->length;i++) {
      separator = &separators[nseparator];
      oid = seps->content[i];
      separator->oid = oid;
      ClaireClass *own = OWNER(oid);
      if (Kernel._string == own) {
        char *s = string_v(oid);
        CL_INT len = LENGTH_STRING(s);
        if(len > 0) {
          if(escape) {
            CL_INT elen = 0;
            CL_INT k;
            for(k = 0;k < len;k++) {
              if(k < len - 1 && s[k] == esc) k++;
              elen++;
            }
            separator->length = elen;
          } else separator->length = len;
          separator->sep = s;
          separator->ischar = 0;
          nseparator++;
        }
      } else if (Kernel._char == own)  {
        separator->sep = (char*)(OBJECT(ClaireChar, oid)->ascii);
        separator->length = 1; //<sb> 0 length means a char
        separator->ischar = 1;
        nseparator++;
      }
    }
    //<sb> order seprators by length -> ensure that the longest sep is checked 
    // first, for instances if 'b' and 'ab' are specified and both match this ensure
    // that 'ab' is the returned match
    for(i = 0;i < nseparator - 1;i++)
       for(j = i+1;j < nseparator;j++) {
       separator_context *separatori = &separators[i];
       separator_context *separatorj = &separators[j];
       if(separatorj->length > separatori->length) {
        separator_context dummy;
        memcpy(&dummy, &separators[i], sizeof(separator_context));
        memcpy(&separators[i], &separators[j], sizeof(separator_context));
        memcpy(&separators[j], &dummy, sizeof(separator_context));
       }
       }
    //<sb> read the port until a separator matches
    char testchar[1];
    CL_INT N = 0;
    CL_INT seplen;
    CL_INT escapedlast = 0;
    char *sep;
    char *travel = databuf;
    CL_INT isbuffer = p->isa == Core._buffer;
    CL_INT isblob = p->isa == Core._blob;
    //<sb> cache the function pointer of the read method associated with the given port
    fptr3 read_port_cache =
      ((fptr3) OBJECT(ClaireFunction, 
        ((list *)(p->isa->dispatcher))->content[Core.read_port->dispatcher])->value);
    //<sb> when a buffer or a blob is given as argument we optimize the code by avoid
    // calls to read_port and instead perform direct access on buffer's data
    // this avoid many func calls
    buffer *bo = (buffer*)p;
    blob *b = NULL;
    if (isbuffer) {
      b = bo->pending_r;
      if (b == NULL) {
        fill_read_buffer_buffer1(bo);
        b = bo->pending_r;
      }
    } else if (isblob)
      b = (blob*)p;
    //<sb> check char by char whether a given separator matches 
    while(1) {
      if (isbuffer) {
        if (b->read_index < b->write_index) {
          c = b->data[b->read_index++];
        } else {
          fill_read_buffer_buffer1(bo);
          if (b->read_index == b->write_index)
            break;
          else c = b->data[b->read_index++];
        }
      } else if (isblob) {
        if (b->read_index < b->write_index) {
          c = b->data[b->read_index++];
        } else break;
      } else if (read_port_cache((CL_INT)p, (CL_INT)&c, 1) == 0) {
        break;
      }
      if (escapedlast) {
        n++;
        if (n == buflen)
          grow_freadline_buffer(&travel, &databuf, &buflen, n, separators);
        *travel++ = c;
        escapedlast = 0;
        N = 0;
        continue;
      }
      N++;
      if(escape == 0 || c != esc) {
        n++;
        if (n == buflen)
          grow_freadline_buffer(&travel, &databuf, &buflen, n, separators);
        *travel++ = c;
        for(i = 0;i < nseparator;i++) {
          separator = &separators[i];
          seplen = separator->length;
          if(separator->ischar) {
            testchar[0] = (char)((CL_INT)separator->sep);
            sep = (char*)testchar;
          } else sep = separator->sep;
          if(N >= seplen) {
            if(sensitive == CTRUE) {
              if (memcmp(travel - seplen, sep, seplen) == 0)
                {matched = 1;
                break; }
            } else {
              //<sb> check case
              if (unsensitive_match(travel, seplen, sep))
                {matched = 1;
                break; }
            }
          }
        }
      } else {
        escapedlast = 1;
      }
      if (matched) break;
    }
    oid = separator->oid;
    delete [] separators;
    char * sres = GC_STRING(copy_string1(databuf, matched ? (travel - databuf - seplen) : n));
    free(databuf);
    return tuple::alloc(2, _string_(sres), matched ? oid : _string_(""));
  }
}

void grow_freadline_buffer(char **travel, char **databuf, CL_INT *buflen, CL_INT n, separator_context *separators)
{
  *buflen += 256;
  char *tmp = (char*)realloc(*databuf, *buflen);
  if(tmp == NULL) {
    free(*databuf);
    delete [] separators;
    Cerror(61,_string_("freadline @ bag"),0);
  }
  *databuf = tmp;
  *travel = *databuf + n - 1;
}

CL_INT unsensitive_match(char *travel, CL_INT seplen, char *sep) {
  CL_INT m = 0;
  char* p1 = travel - seplen;
  char* p2 = sep;
  for(;m < seplen;m++) {
    if (*p1 != *p2) {
      if (*p2 >= 'A' && *p2 <= 'Z')
        {if(*p2 + 'a' - 'A' != *p1) break;}
      else if (*p2 >= 'a' && *p2 <= 'z')
        {if(*p2 + 'A' - 'a' != *p1) break;}
      else break;
    }
    p1++; p2++;
  }
  return m == seplen;
}



CL_EXPORT fd_set readset;
CL_EXPORT fd_set writeset;
CL_EXPORT CL_INT fdMaxfd = -1;

/*********************************************************************/
/**    2. Reader general functions                                   */
/*********************************************************************/


// check that a char is not a special char 
CL_EXPORT ClaireBoolean *alpha_char (ClaireChar *cx)
{unsigned char c = cx->ascii;
 if       (  (c == 255)  || (c == '\n') ||
             (c == '}') || (c == ')')  || (c == ']') ||
             (c == '{') || (c == '(')  || (c == '[') ||
             (c == '\t') || (c == ';')  || (c == '|') ||
             (c == ',') || (c == '/')  || (c == ':') ||
             (c == '@') || (c == '.')  || (c == '\r') ||
             (c == '<') || (c == '>')  || (c == ' ') )
           //  (c == '+') || (c == '-')  || (c == '*') )
 return CTRUE;
 else return CFALSE;}


CL_INT reading_a_string = 0;
CL_INT read_escaped = 0;

//<sb> how to read    0{o|O}XXX...    X in (0 .. 7)
CL_EXPORT OID read_octal_port(PortObject* p) {
  double res = (double)(p->firstc - '0'); //<sb> the first digit is already read for octal numbers!
  CL_INT t = 0;
  p->getNext();
  while(p->firstc >= '0' && p->firstc <= '7') {
    res = 8.0 * res + (double)(p->firstc - '0');
    t++;
    if(t == 3 && reading_a_string) break;
    p->getNext();
    if((reading_a_string && p->firstc == '\\') ||
      (p->firstc <= '0' && p->firstc >= '7'))
      {p->getNext();break;}
  }
  if (res >= CLMINFLOAT && res <= CLMAXFLOAT) return ((CL_INT) res);     // rean an int
    else return _float_(res);}

//<sb> how to read   0{x|X|h|H}XXX...   X in (0 .. 9) U (A .. F) U (a .. f)
CL_EXPORT OID read_hexa_port(PortObject* p) {
  double res = 0.0;
  CL_INT t = 0;
  p->getNext();
  while((p->firstc >= '0' && p->firstc <= '9') ||
      (p->firstc >= 'A' && p->firstc <= 'F') ||
      (p->firstc >= 'a' && p->firstc <= 'f')) {
    if(p->firstc >= '0' && p->firstc <= '9')
      res = 16.0 * res + (double)(p->firstc - '0');
    else if(p->firstc >= 'A' && p->firstc <= 'F')
      res = 16.0 * res + (double)(10 + p->firstc - 'A');
    else res = 16.0 * res + (double)(10 + p->firstc - 'a');
    p->getNext();
    t++;
    if(t == 2 && reading_a_string) break;
  }
  if (res >= CLMINFLOAT && res <= CLMAXFLOAT) return ((CL_INT) res);     // rean an int
    else return _float_(res);}

//<sb> how to read   0{d|D}XXX...   X in (0 .. 9)
CL_EXPORT OID read_dec_port(PortObject* p) {
  double res = 0.0;
  CL_INT t = 0;
  p->getNext();
  while((p->firstc >= '0' && p->firstc <= '9')) {
    res = 10.0 * res + (double)(p->firstc - '0');
    p->getNext();
    t++;
    if(t == 3 && reading_a_string) break;
  }
  if (res >= CLMINFLOAT && res <= CLMAXFLOAT) return ((CL_INT) res);     // rean an int
    else return _float_(res); }

//<sb> how to read   0{b|B}XXX...   X in {0,1}
CL_EXPORT OID read_bin_port(PortObject* p) {
  double res = 0.0;
  CL_INT t = 0;
  p->getNext();
  while(p->firstc >= '0' && p->firstc <= '1') {
    res = 2.0 * res + (double)(p->firstc - '0');
    p->getNext();
    t++;
    if(t == 8 && reading_a_string) break;
  }
  if (res >= CLMINFLOAT && res <= CLMAXFLOAT) return ((CL_INT) res);     // rean an int
    else return _float_(res);}

// reading a string in a port - assumes that " was read and that the string will end with "
CL_EXPORT char *read_string_port(PortObject* p) {
 char cur = p->firstc;
 ClEnv->bufferStart();
 while (cur != '"')
    {if (cur == ((char)255)) break;
     if (cur == '\\') {
       p->getNext();
        cur = p->firstc;
        if (cur == 't') cur = '\t';
        else if (cur == 'r') cur = '\r';
        else if (cur == 'n') cur = '\n';
        //else if (cur == '0') cur = '\0';
    else if (cur == '\\') cur = '\\';
    else if (cur == '"') cur = '"';
        //<sb> add support for escaped number in various basis 
    else if ((cur >= '0' && cur <= '7') ||
        cur == 'x' || cur == 'X' ||
        cur == 'h' || cur == 'H' || 
        cur == 'd' || cur == 'D' || 
        cur == 'b' || cur == 'B')
          { read_escaped = 1;
        reading_a_string = 1;
            OID num = read_number_port(p);
            read_escaped = 0;
        reading_a_string = 0;
            //p->getNext();
            if(INTEGERP(num) == 0) Cerror(35,_integer_(num),p->firstc);
            ClEnv->pushChar((char)num);
            cur = p->firstc;
            continue; }}
   ClEnv->pushChar(cur);
     cur = p->getNext();}
 p->getNext();
 char *s = ClEnv->bufferCopy();
 return s;}


// reading an ident, which is either a symbol, a number or a special case
CL_EXPORT OID read_ident_port(PortObject* p) {
 CL_INT cur = p->firstc;
 p->getNext();
 if ((cur == '-') && (('0' <= p->firstc) && ('9' >= p->firstc)))
    {OID value = read_number_port(p);
      if (INTEGERP(value)) return (- value);
      else return _float_( -(float_v(value))); }
 else if (cur == '\\' && 
     ((p->firstc >= '0' && p->firstc <= '7') ||
     p->firstc == 'x' || p->firstc == 'X' ||
     p->firstc == 'h' || p->firstc == 'H' ||
     p->firstc == 'd' || p->firstc == 'D' ||
     p->firstc == 'b' || p->firstc == 'B'))
    {read_escaped = 1;
     OID value = read_number_port(p);
     read_escaped = 0;
      if (INTEGERP(value)) return value;
      else return _float_(float_v(value)); }
 else if (cur == '\'') //<sb> reading a char
   { cur = p->firstc;
   p->getNext();
     //<sb> add support for escaped chars
     if (cur == '\\') {
       if ('\'' == p->firstc) {
         p->getNext();
         if (p->firstc != '\'') Cerror(35,cur,p->firstc);
         p->getNext();
            return _oid_(char_I_integer('\''));
       } else {
       cur = p->firstc;
       if (cur == 't') {cur = '\t';p->getNext();}
       else if (cur == '\\') {cur = '\\';p->getNext();}
       else if (cur == 'r') {cur = '\r';p->getNext();}
       else if (cur == '"') {cur = '"';p->getNext();}
       else if (cur == 'n') {cur = '\n';p->getNext();} 
       //<sb> add support for escaped number in various basis 
      else if (cur >= '0' && cur <= '7') {
        CL_INT oct = (CL_INT)(cur - '0');
        p->getNext();
        cur = p->firstc;
        if (cur >= '0' && cur <= '7') {
          oct = 8 * oct + (CL_INT)(cur - '0');
          p->getNext();
          cur = p->firstc;
        }
        if (cur >= '0' && cur <= '7') {
          oct = 8 * oct + (CL_INT)(cur - '0');
          p->getNext();
          cur = p->firstc;
        }
        if (cur != '\'') Cerror(35,cur,p->firstc);
        p->getNext();
        return _oid_(char_I_integer((unsigned char)oct));
      } else if(cur == 'x' || cur == 'X' || cur == 'h' || cur == 'H' ||
        cur == 'd' || cur == 'D' || cur == 'b' || cur == 'B')
        { read_escaped = 1;
        reading_a_string = 1;
        OID num = read_number_port(p);
        if ((ClEnv->verbose = -1))
        reading_a_string = 0;
        read_escaped = 0;
        if(INTEGERP(num) == 0)
          Cerror(35,_integer_(num),p->firstc);
        cur = (CL_INT)num;
        p->getNext();
        return _oid_(char_I_integer((unsigned char)cur));}
      else {Cerror(35,cur,p->firstc);}}
    }
   if ('\'' != p->firstc) {Cerror(35,cur,p->firstc); return 1;}
     else {p->getNext();
           return _oid_(char_I_integer((unsigned char)cur));}}
 else return  read_thing_port(p,ClEnv->module_I,char_I_integer((unsigned char)cur),ClEnv->module_I); }

// read a number, either a float or an integer
// changed in v3.0.70 to read long floats
//<sb> v3.3.15 read octal/hexa/binary as well (0x... 0o... 0b...)
CL_EXPORT OID read_number_port(PortObject* p) {
 double res = (double) (p->firstc - '0');
 if(read_escaped) { //<sb> add support for number in various basis 
   if(p->firstc >= '0' && p->firstc <= '7') return read_octal_port(p);
   else if(p->firstc == 'x' || p->firstc == 'X') return read_hexa_port(p);
   else if(p->firstc == 'd' || p->firstc == 'D') return read_dec_port(p);
   else if(p->firstc == 'h' || p->firstc == 'H') return read_hexa_port(p);
   else if(p->firstc == 'b' || p->firstc == 'B') return read_bin_port(p); }
 p->getNext();
 while(p->firstc >= '0' && p->firstc <= '9')
     {res = (res * 10.0) + (double) (p->firstc - '0');
      p->getNext();}
 if ((p->firstc != '.') && (p->firstc != 'e') && (p->firstc != 'E'))
    {if (res >= CLMINFLOAT && res <= CLMAXFLOAT)
      {CL_INT d = (CL_INT)res;
      return (OID)d;}     // rean an int
     else return _float_(res);}                                         // overflow -> float (v3.0.70)
 else {double possible = res;                  // read a float (saw a e or a .)
         if (p->firstc == '.')                 // read the decimal part
           {res = 10.0;
            p->getNext();
            while ((p->firstc >= '0') && (p->firstc <= '9'))
               {possible = possible + (((double) (p->firstc - '0')) / res);
                res = res * 10.0;
                p->getNext();}}
         if (p->firstc == 'e' || p->firstc == 'E')                 // read the exponent part
            {char signe = '+';
             res = 0.0;
             p->getNext();
             if (p->firstc == '-') {signe = '-'; p->getNext();}
             if (p->firstc == '+') p->getNext();
             while ((p->firstc >= '0') && (p->firstc <= '9'))
                {res = (res * 10.0) + (double) (p->firstc - '0');
                 p->getNext();}
             if (signe == '-') possible = possible / pow(10.0,  res);
             else  possible = possible * pow(10.0,  res);}
          return _float_(possible);}}

// reading a true identifier (symbol or object)
//   app is the module in which the stream is read, cur is the current
//   character and n is the reader object
// def = NULL means that we read a private name
CL_EXPORT OID read_thing_port(PortObject* p, module *app, ClaireChar *cx, module *def) {
 char cur = (char) cx->ascii;
 if (cur == '"')
    return _oid_(symbol::make(GC_STRING(read_string_port(p)),app,def));      // strings
 if ((cur == '/') && (p->firstc == '*'))                                           // C-style comments
    {while (((cur != '*') || (p->firstc != '/')) && cur != ((char)255))
    {cur = p->firstc; p->getNext();}
     p->getNext();
     return _string_("");}
 ClEnv->bufferStart();
 if ((cur == '/') && (p->firstc == '/'))                                           // C++ comment
    {p->getNext();
     while (((cur = p->firstc) != '\n') && (cur != ((char)255)))
         {ClEnv->pushChar(cur); p->getNext();}
  return _string_(ClEnv->bufferCopy());}
 ClEnv->pushChar(cur);
 if ((cur == ':') && (p->firstc == ':')) {ClEnv->pushChar(cur);p->getNext();}       // :: trap
 else if ((cur == '.') && (p->firstc == '.')) {ClEnv->pushChar(cur);p->getNext();}       // .. trap
 else if ((cur == '<') && (p->firstc == '<')) {ClEnv->pushChar(cur);p->getNext();}       // .. trap
 else if ((cur == '-' || cur == '=' || cur == '>') && (p->firstc == '>'))  //<sb> add check for eof
       {ClEnv->pushChar('>');p->getNext();}       // -> trap for *>
 cur = p->firstc;
 while (alpha_char(char_I_integer(((unsigned char)cur))) == CFALSE)
       {ClEnv->pushChar((char) cur); cur = p->getNext();}
 if (cur == '/')                                                                   // read a qualified ident
    {OID s = (app->getSymbol(ClEnv->buffer,claire.it))->getValue();
     ClaireChar *cx = char_I_integer((unsigned char)p->getNext());
       p->getNext();
       if (s == _oid_(Kernel.PRIVATE)) return read_thing_port(p,app,cx,NULL);
       else {if (OWNER(s) == Core._global_variable) { //<sb> support module alias
        s = OBJECT(global_variable, s)->value;
        if (OWNER(s) != Kernel._module)
          Cerror(29,s,0);
      } else if (OWNER(s) !=  Kernel._module)
                Cerror(29,s,0);
             return read_thing_port(p,OBJECT(module,s),cx,def);}}
 else {symbol *s = app->getSymbol(ClEnv->buffer,def);                               // create the symbol
         if ((app == ClEnv->module_I) || (s->definition != NULL))
           return s->getValue();
         else {Cerror(30,_oid_(s),0); return 1;}}}

/**********************************************************************/
/**    3. Characters                                                  */
/**********************************************************************/

// initialization: create all chars (this is called once ClaireChar is properly defined)
void ClaireChar::init()
{CL_INT i;
  for (i = 0; i < 256; i++) //<sb> was 512 due to signed char (now unsigned)
    {ClaireChar *c = (ClaireChar *) ClAlloc->makeAny(2);
       c->isa = Kernel._char;
       c->ascii = (unsigned char)i;
       ClRes->ascii[i] = c;
       }}

// princ a char / CL_INT / float
//<sb> prints in a readable form for ascii in (0 .. 31) U (127 .. 159)
// ex: ascii code 1 is printed '\001'
CL_EXPORT void princ_char(ClaireChar *cx) {
  ClEnv->cout->put((char)cx->ascii);
}


CL_EXPORT void print_char(ClaireChar *cx) {
  char tmp = (char)cx->ascii;
  PortObject *pout = ClEnv->cout;
  pout->put('\'');
  if(tmp == '"') pout->put('"');
  else if(tmp == '\'') {pout->put('\\');pout->put('\'');}
  else internal_print_string(&tmp,1);
  pout->put('\'');
}


// print the name of an object as a C identifier
//<sb> made c_princ_char relying on c_princ_string
// and add a temp buffer such to decrease the amount of
// write calls
CL_EXPORT void c_princ_string(char *ss)
{ char buf[1024];
  char *travel = buf;
  for (; *ss != '\0'; ss++) {
    char *tmp;
  CL_INT n = 1;
    switch (*ss) {
       case '.':  tmp = "_dot"; n = 4; break;
       case '/':  tmp = "_7"; n = 2; break;
       case '\\': tmp = "_backslash"; n = 10; break;
       case '&':  tmp = "_and"; n = 4; break;
       case '-':  tmp = "_dash"; n = 5; break;
       case '+':  tmp = "_plus"; n = 5; break;
       case '%':  tmp = "_Z"; n = 2; break;
       case '*':  tmp = "_star"; n = 5; break;
       case '?':  tmp = "_ask"; n = 4; break;
       case '!':  tmp = "_I"; n = 2; break;
       case '<':  tmp = "_inf"; n = 4; break;
       case '>':  tmp = "_sup"; n = 4; break;
       case '=':  tmp = "_equal"; n = 6; break;
       case ',':  tmp = "_comma"; n = 6; break;
       case '^':  tmp = "_exp"; n = 4; break;
       case '@':  tmp = "_at"; n = 3; break;
       case '~':  tmp = "_tilda"; n = 6; break;
       case ']':  tmp = "_brack"; n = 6; break;
       case ':':  tmp = "L_"; n = 2; break;
       case '\'': tmp = "_prime"; n = 6; break;
       case '$': tmp = "_dollar"; n = 7; break;       // v3.2.14
       default: tmp = ss;break;
     }
   memcpy(travel, tmp, n);
   travel += n;
   if (travel - buf > 1000) {
     Core.write_port->fcall((CL_INT)ClEnv->cout, (CL_INT)buf, travel - buf);
     travel = buf;
   }
  }
  if(travel > buf)
    Core.write_port->fcall((CL_INT)ClEnv->cout, (CL_INT)buf, travel - buf);
}
    
// special consversion (language dependent)
//<sb> now rely on c_princ_string
CL_EXPORT void c_princ_c(ClaireChar *cx)
{ char c[2] = {0,0};
  c[0] = (char)cx->ascii;
  c_princ_string(c);
}


// print a symbol (the name of an object) as a C identifier */
CL_EXPORT void c_princ_symbol(symbol *s)
{  if (s->module_I != claire.it)
      {c_princ_symbol(s->module_I->name);
       ClEnv->cout->put('_');}
   c_princ_string(s->name);}

CL_EXPORT CL_INT integer_I_char(ClaireChar *c)
{return c->ascii;}

/*********************************************************************/
/**    4. System interface (miscellaneous)                           */
/*********************************************************************/

// set the time counter
CL_EXPORT void time_set_void()
{ if (++ClEnv->tIndex > 9) Cerror(26,ClEnv->tIndex,0);
  msec(ClEnv->tStack[ClEnv->tIndex]);}

// shows the elaped time
CL_EXPORT CL_INT time_get_void()
{CL_INT now;
   msec(now);
   if (ClEnv->tIndex <= 0) Cerror(26,ClEnv->tIndex,0);
   return (now - ClEnv->tStack[ClEnv->tIndex--]);}

CL_EXPORT CL_INT time_read_void()
{CL_INT now;
   msec(now);
   if (ClEnv->tIndex <= 0) Cerror(26,ClEnv->tIndex,0);
   return (now - ClEnv->tStack[ClEnv->tIndex]);}

CL_EXPORT void time_show_void()
{OID now;
   msec(now);
   if (ClEnv->tIndex <= 0) Cerror(26,ClEnv->tIndex,0);
   princ_string("Counter["); princ_integer(ClEnv->tIndex);
   princ_string("] Elapsed time: "); princ_integer(now - ClEnv->tStack[ClEnv->tIndex--]);
   princ_string("ms. \n");}

// pass a command string to the host system
CL_EXPORT CL_INT claire_shell(char *s)
{ return CL_system(s); }


// profiler methods (ClaireProfile -> KernelProfile)
CL_EXPORT PRcount *PRstart(PRcount *p)
{CL_INT x = 0;
  if (p->rdepth == 0) {p->rstart = clock();}  // v3.2.58 : more precision ....
  p->rdepth++; p->rnum++;
  return p;}

// fixed bugs in v3.0.53 thanks to FXJ
CL_EXPORT void PRend(PRcount *p)
{CL_INT x = 0;
  p->rdepth--;
  if (p->rdepth == 0) {p->rtime += (clock() - p->rstart);}}

CL_EXPORT void PRloop(PRcount *p)
{p->rloop++;}


/***********************************************************************/
/**   microCLAIRE                                       Yves Caseau    */
/**   clReflect.cpp                                                    */
/**  Copyright (C) 1998-2003 Yves Caseau. All Rights Reserved.         */
/**  cf claire.h                                                       */
/***********************************************************************/


// ----------------------------------------------------------------------------
// this file contains the methods for reflective objects (and classes)
// it uses a set of external functions that are defined in System (claire code)
// ----------------------------------------------------------------------------

/*********************************************************************/
/** Contents                                                         */
/**    1. Objects                                                    */
/**    2. Class                                                      */
/**    3. Properties                                                 */
/**    4. Tables                                                     */
/*********************************************************************/


/*********************************************************************/
/**    1. Objects                                                    */
/*********************************************************************/

// v3.2.24: was awfully slow -> introduce a direct link to member? method
ClaireBoolean *ClaireCollection::contains(OID oself)
{ if (isa == Kernel._class)
     return (INHERIT(OWNER(oself),((ClaireClass *) this)) ? CTRUE : CFALSE);
  else if (isa == Kernel._list) return contain_ask_list((list *) this, oself);
  else if (isa == Kernel._set) return contain_ask_set((set *) this, oself);
  else {method  *m = OBJECT(method, (*Kernel.member_ask->definition)[1]);
        return ( (ClaireBoolean*)
                 ( ((fptr2) (m->functional->value))(oself, (CL_INT) this)));  }}

// ---------------------- API functions ----------------------------------------

// copy an object (or an item) */
CL_EXPORT ClaireObject *copy_object(ClaireObject *x)
{CL_INT i,m = *SLOTADR(x,0);
 ClaireObject *y = (ClaireObject *) ClAlloc->makeAny(m);
 GC_PUSH(y);
 if (Kernel._freeable_object && INHERIT(x->isa, Kernel._freeable_object))
  Kernel._freeable_object->instances->addFast(_oid_(y));
 else if (x->isa->open != 4)
  x->isa->instances->addFast(_oid_(y));
 for (i = 1; i<= m; i++) *SLOTADR(y,i) = *SLOTADR(x,i);
 return y;}

// logical equality
CL_EXPORT ClaireBoolean *equal(OID n, OID m)
{  if (n == m) return CTRUE;
   else if (IDENTIFIED(n) || IDENTIFIED(m)) return CFALSE;
   else {ClaireAny *x = OBJECT(ClaireAny,n);
         ClaireAny *y = OBJECT(ClaireAny,m);
         ClaireClass *sx = x->isa;
         if (sx != y->isa) return CFALSE;
         else if (sx == Kernel._list || sx == Kernel._tuple)
            return((list *) x)->equalList((list *) y);
         else if (sx == Kernel._set) return((set *) x)->equalSet((set *) y);
         else if (sx == Kernel._string) return equal_string(string_v(n),string_v(m));
         else if (sx == Kernel._float)
             {if (((ClaireFloat *) x)->value == ((ClaireFloat *) y)->value) return CTRUE;
              else return CFALSE;}
         else {if (((ClaireImport *) x)->value == ((ClaireImport *) y)->value) return CTRUE;
               else return CFALSE;}}}

// reading a value in a slot
// new in v2.5: floats
CL_EXPORT OID slot_get_object(ClaireObject *x, CL_INT y, ClaireClass *s)
{if (s == Kernel._float)
    {return _float_(*( (double *) SLOTADR(x,y) )); }
 else {CL_INT z = *SLOTADR(x,y);
        return ((z == 0) ? (((s == Kernel._integer) || (s == Kernel._any)) ? 0 : CNULL) :
                 ((z == CNULL) ? CNULL : CLAIREOID(z,s)));}}

// membership for any collection
CL_EXPORT ClaireBoolean *belong_to(OID oself, OID ens)
{ ClaireClass *c = OWNER(ens);
   if (c == Kernel._integer)
       return ((oself >= 1 && oself <= 29 && BCONTAIN(ens,oself)) ? CTRUE : CFALSE);
   else if (c == Kernel._array) return contain_ask_array(array_v(ens),oself);
   else return OBJECT(ClaireCollection,ens)->contains(oself);}

// hashing for a generic list of length 2^n - 2
CL_EXPORT CL_INT hash_list(list *l, OID x)
{CL_INT i = ClRes->hashOid(l->content[0] - 1,x);
   if (i < l->length) return (i + 1);
   else return (1 + (i % l->length));}

//convert anything into a Boolean
CL_EXPORT ClaireBoolean *boolean_I_ClaireAny(ClaireAny *x)
 {if (x->isa == Kernel._boolean) return (ClaireBoolean *) x;
  else if (x->isa == Kernel._set || x->isa == Kernel._list)
      return ( (((list *) x)->length != 0) ? CTRUE : CFALSE);
  else if (x == CFALSE) return CFALSE;     // to remove later on
  else return CTRUE;}

CL_EXPORT ClaireBoolean *boolean_I_any(OID n)
 { if ((INT_MASK & n) != OBJ_CODE) return CTRUE;
   else return boolean_I_ClaireAny(OBJECT(ClaireAny,n)); }


// ---- three debugging functions which are quite useful ------------------------------------
CL_EXPORT CL_INT CL_Address(OID x) {return ADR(x);}

CL_EXPORT char *CL_Oid(OID x)
{char *s = make_string_integer(15,ClRes->ascii[32]);
#ifdef __LP64__
  CL_INT n = sprintf(s,"%llu",x);
#else
  CL_INT n = sprintf(s,"%u",x);
#endif
  *((CL_INT*)s - 1) = n;
  return s;}

CL_EXPORT OID CL_Oid_inv(char *s)
{OID x;
#ifdef __LP64__
	sscanf(s,"%lu",&x);
#else
	sscanf(s,"%u",&x);
#endif

	return x;}

/*********************************************************************/
/**    2. Class                                                      */
/*********************************************************************/




// new in v3.1.16: float alignment parity is an option
// for 99% of C++ compilers, float slots need to be aligned (even)
// so the C++ compiler wastes memory if needed
//<sb> some architecture may need structure alignment and/or field alignment
class align_struct : ClaireObject {double d;};
class align_field : ClaireObject {CL_INT pad1; CL_INT pad2; double d;};

#define ALIGN_STRUCT (sizeof(class align_struct) != sizeof(double) + sizeof(CL_INT))
#define ALIGN_FIELD (sizeof(class align_field) != sizeof(double) + 3 * sizeof(CL_INT))

// this first constructor works with no environment and is used to create the
// first classes
ClaireClass *ClaireClass::make(ClaireAny *x)
{ClaireClass *c = (ClaireClass *) x;
#ifdef __LP64__
   if (ClEnv->verbose > 11) printf("=== class::make allocates a class @ %lx \n",(CL_INT) c);
#else
   if (ClEnv->verbose > 11) printf("=== class::make allocates a class @ %x \n",(CL_INT) c);
#endif
   c->ancestors = list::empty();
   c->slots = list::empty();
   c->instances = list::empty();
   c->subclass = set::empty();
   c->isa = Kernel._class;
   c->evaluate = (ClaireFunction *) NULL;        // will be setup later
   c->open = 2;
   c->params = list::empty();
   c->dictionary = list::empty();
   c->dispatcher = list::empty();
   c->ident_ask = CTRUE;
   c->if_write = CNULL;
   c->comment = "";
   return c;
   }

// same with a name
ClaireClass *ClaireClass::make(char *n)
{ClaireClass *c = make( ClAlloc->makeStatic(sizeof(ClaireClass) / sizeof(CL_INT) )) ;
 symbol *s = symbol::make(n,claire.it,ClEnv->module_I);
 s->value = _oid_(c);
 c->name = s;
 c->comment = n;
 c->if_write = CNULL;
 Kernel._class->instances->addFast(_oid_(c));
 return c;}


// this is the regular constructor
// open(p) = 0 <=> read only, 1 <=> compiled (cannot be overwritten)
//           2 <=> default (unknown), 3 <=> open (extensible)
//           -1 : system property that may be overwritten  (v3.2.24)
// V3.2 PATCH : final(p) => open(p) = 0 because we allow overwriting open=1 properties !
// open(c) = -2 <=> system_set, -1 <=> no changes !
//           0  <=> no more instance, 1 <=> no new subclasses
//           2 <=> default, 3 <=>open
//           4 <=> ephemeral
ClaireClass *ClaireClass::make(char *name, ClaireClass *c2, module *def)
{ClaireClass *c = (ClaireClass *) Kernel._class->instantiate(name,def);
   c->comment = name;
   c->superclass = c2;
   c->slots = (list *) copy_bag(c2->slots);
   if (c2->open == ClEnv->ephemeral) c->open = ClEnv->ephemeral;
   c->prototype = (list *) copy_bag(c2->prototype),
   c->evaluate = c2->evaluate;
   c->if_write = CNULL;
   c->genealogy();
//   if (c->code == 0) c->encode();
   c->dictionary = (list *) copy_bag(c2->dictionary);
   c->dispatcher = (list *) copy_bag(c2->dispatcher);
   return c;}

// instantiation methods from simple to more complex
ClaireObject *ClaireClass::instantiate(CL_INT n)
{ClaireObject *o = (ClaireObject *) ClAlloc->makeAny(n);
 o->isa = this;
 return o;}

// here we use the prototype list as the pattern
// note: the prototype only contains things that can be copied directly !!!
// in 2.9 we extend this to floats (need to skip the index count: +2)
//     copied_defaults = object (for object) + float (for float) + integer (for anything)
//                       + NULL for objects
// IMPORTANT: do not put a float or an object in the prototype if the range is ANY !!!
//            because an object in prototype means a slot of srange object
//            CNULL means please put 0 (object representation)
//            Nodefault means please put CNULL (OID representation)
// v3.2.52: there is no alighnment problem here IF (1) instantiate respects the parity of the
// object allocation (2) addSlot respects the parity of the position of the float default value
// in the prototype


ClaireObject *ClaireClass::instantiate()
{CL_INT i, n = prototype->length;
 ClaireObject *o = instantiate(n);
 ClAlloc->currentNew = o;                           // protect the object but NOT the content !
 CL_INT u = _oid_(o), rep = ADR(u) + 1;
 // <debug for alignment> printf("alloc object size %d -> rep = %d @ %d\n",n,rep, &o);
 for (i= 2; i<=n ; i++)
    {//int look = rep - ADR(_oid_(o));
   OID v = (*prototype)[i];                          // value in the prototype
     ClaireClass *c = OWNER(v);                        // owner(v)
     if (c == Kernel._float)                        	   // implies a range float !
         { // <debug for alignment> printf("rep = %d, i = %d, & = %x v = %g\n",rep,i,&Cmemory[rep],float_v(v));
           *((double *)(rep << ADDRTRANS)) = float_v(v);
#ifdef __LP64__
         rep ++; }
#else
         rep += 2; i += 1;  }                      // v3.0.68 ! i changes => v changes
#endif 
     else if ((c == Kernel._set) || (c == Kernel._list))
             {// printf("--- put a copy of %x into C[%d]\n",v,rep + 1);
             *((CL_INT*)(rep++ << ADDRTRANS)) = (CL_INT) copy_bag(OBJECT(bag,v)); }       // copy may cause GC!
     else if (CTAG(v) == OBJ_CODE && v != CNULL)
         {if (v == _oid_(Kernel.NoDefault)) *((CL_INT*)(rep++ << ADDRTRANS)) = CNULL;  // NEW in V3.0.41
          else  *((CL_INT*)(rep++ << ADDRTRANS)) = (CL_INT) OBJECT(ClaireAny,v);}
     else *((CL_INT*)(rep++ << ADDRTRANS)) = v; }
#ifdef CLDEBUG
 if (ClEnv->verbose > 11) printf("<<< instantiate returns %x at adress %ld [-> %ld]\n",o,getADR(o),rep - 1);
 checkOID(u); // debug !
#endif
 ClAlloc->currentNew = NULL;
 GC_PUSH(o);
 if (Kernel._freeable_object && INHERIT(this, Kernel._freeable_object))
  Kernel._freeable_object->instances->addFast(u);
 return o;}


// instantiation (for named object) m is the module for the symbol, the definition module
// is taken as the current module
thing *ClaireClass::instantiate(char *n, module *m)
{symbol *s = symbol::make(n,m,ClEnv->module_I);
   if (s->value != CNULL && CTAG(s->value) == OBJ_CODE)
      {thing *o = OBJECT(thing,s->value);
        if (o->isa != this)
            { // ClEnv->verbose = 11;
              // see("--- try to make a ",_oid_(this));
              // printf("--- with name %s\n", n);
              // see("--- and found a ",_oid_(o->isa));
              Cerror(18,_oid_(s),_oid_(o->isa));}
        // printf("reuse address %d for object named %s \n",getADR(o),n);
        return o;}
    else {thing *o = (thing *) instantiate();
           o->name = s;
           s->value = _oid_(o);
           if (open != 4) instances->addFast(_oid_(o));
#ifdef __LP64__
           if (ClEnv->verbose > 10) printf("create a new |%s| @ adr %ld\n",n,getADR(o));
#else
           if (ClEnv->verbose > 10) printf("create a new |%s| @ adr %d\n",n,getADR(o));
#endif
           return o;}}

// creates the genealogy for a class
void ClaireClass::genealogy()
{OID self = _oid_(this);
 ClaireClass *c = superclass;
 ITERATE(y);
   descendents = set::alloc(Kernel._class,1,self);
   for (START(c->ancestors); NEXT(y);)
      { OBJECT(ClaireClass,y)->descendents->addFast(self);}
   c->subclass->addFast(self);
   ancestors = (list *) copy_bag(c->ancestors);
   ancestors->addFast(self); }

  
// how to create a new slot
// v3.2: this method is modified so that it may receive ix = the position of 
// the slot (obtained through a macro) in the C++ object [warning: ix may
// also be provided directly by the interpreter, thus the safety check on parity]
slot *ClaireClass::addSlot(property *p,ClaireType *t,OID def,CL_INT ix)
{ GC_PUSH(t);
 slot *s = (slot *) instantiate(9);
 memset(s, 0, sizeof(slot));
 OID soid = _oid_(s);
 s->isa = Kernel._slot;
 ClAlloc->currentNew = s; //<sb> fix: keep track of the current allocated slot !
 ClaireClass *c1 = class_I_type(t);
 ClaireClass *s1 = sort_I_class(c1);     // sort: range for the slot
 CL_INT i = slots->length;                  // v3.2: number of existing slots
    s->domain = list::alloc(Kernel._type,1,_oid_(this));
    s->selector = p;
    if (c1 == Kernel._list || c1 == Kernel._set)
       {if (p->restrictions->length == 0)
		{
          if (c1 == Kernel._set) p->multivalued_ask = CTRUE;
          else p->multivalued_ask = Kernel._list;
	  }
        if (def == CNULL)
		{
          if (c1 == Kernel._set) def = _oid_(set::empty(of_extract_type(t)));
          else def = _oid_(list::empty(of_extract_type(t))); }
	  }
    else if (c1 == Kernel._float && def == CNULL) def = _float_(0.0); //NOTE: test on c !!
    s->DEFAULT = def;
    if ((s1 != Kernel._integer) &&
              (s1 != Kernel._any) &&
              (def == CNULL)) def = 0;      // NULL
    
    if ((p->multivalued_ask == CTRUE && c1 != Kernel._set) ||
        (p->multivalued_ask == Kernel._list && c1 != Kernel._list)) {
       ClAlloc->currentNew = NULL;              //<sb> release the mark ...
       Cerror(28,_oid_(p),GC_OID(soid));        // v3.1.08 //<sb> ... and protect it for the error instanciation
    }
    //<sb> insert the slot in class/selector
    Kernel._slot->instances->addFast(soid);
    p->restrictions->addFast(soid);
    ClAlloc->currentNew = NULL; //<sb> release our mark
#ifdef __LP64__
    if (c1 == Kernel._float && ix % 2 == 0) {     // some architecture requires even float indexes
      if (ALIGN_FIELD ||
            (ALIGN_STRUCT &&
               //<sb> test that the new slot is the first slot of its domain
               // note : i is always positive due to isa @ object !
               OBJECT(ClaireClass,(*(OBJECT(slot,(*slots)[i])->domain))[1]) != this))
         ix++;
    }
#endif
    // change the default representation that will be stored in the prototype
    //  copied_default = object (for object) + float (for float) + integer (for all) + NULL for objects
    if (s1 == Kernel._object || OWNER(def) == Kernel._integer || c1 == Kernel._float) ; // nothing (store def)
    else if (s1 == Kernel._any || s1 == Kernel._integer) 
       {if (def != CNULL) def = _oid_(Kernel.NoDefault);}    // this is the case that wa cannot handle
    else def = 0;
    // new in v3.2 : allow overiding of existing slots
    while (i > 1 && OBJECT(slot,(*slots)[i])->selector != p)  i--;
    if (i <= 1) 
        {slots->addFast(soid);     // a new slot
         // compute the index for slot s (needed for the interpreter :-( )
#ifndef __LP64__
         if (ix > 1) 
            {slot * sprev = OBJECT(slot,slots->content[slots->length - 1]);
             CL_INT i = sprev->index + ((sprev->srange == Kernel._float) ? 2 : 1);
             if (i != ix)                 // alignment constraint: ix was add +1 !
                prototype->addFast(0);}   // maintain length(proto) = size(object)
#endif			 
          s->index = ix;}                 // ix is given by the interpreter or the C++ compiler !
    else {s->index = OBJECT(slot,(*slots)[i])->index;
          (*slots)[i] = soid;
          (*prototype)[s->index] = def;}
    //  copied_default = object (for object) + float (for float) + integer (for all) + NULL for objects
    if (i <= 1)                                // new slot ! 
     {prototype->addFast(def);
#ifndef __LP64__
      if (c1 == Kernel._float) prototype->addFast(0);
#endif
  }  // maintain length consistency
    s->comment = NULL;      //<sb> fixed in v3.3.35
    s->srange = ((c1 == Kernel._float) ? c1 : s1);      // sort = float allowed only for slots
    s->module_I = ClEnv->module_I;
    s->range = t;
    insert_definition_property(p,s);           // defined in system (unless CLKTEST is defined)
    return s;}                 
    

// --------------------- API method -------------------------------------------

// create a slot
CL_EXPORT void add_slot_class(ClaireClass *c, property *p, ClaireType *t, OID def, CL_INT ix) 
  {c->addSlot(p,t,def,ix);}


// create an instance
CL_EXPORT ClaireObject *new_object_class(ClaireClass *c) {return c->instantiate();}
CL_EXPORT thing *new_thing_class(ClaireClass *c, symbol *s)
   {return c->instantiate(s->name,s->module_I);}

// create a class
CL_EXPORT ClaireClass *class_I_symbol(symbol *s, ClaireClass *c2)
{return ClaireClass::make(s->name,c2,s->module_I);}

// class to sort mapping
// note that the sort float does not exist as such (mapped to any for the methods's sake)
// float-specific tests must use the range.
CL_EXPORT ClaireClass *sort_I_class(ClaireClass *c)
{ if (c == Kernel._array || c == Kernel._any || /*c == Kernel._port ||*/  //<sb> port are now of sort object!
     c == Kernel._integer || c == Kernel._string || c == Kernel._void)  return c;
  else if (c == Kernel._float || c == Kernel._primitive) return Kernel._any;
  else if (c == Kernel._class) return Kernel._object;
  else if (c->superclass == Kernel._cl_import) return c;   // v3.3.22
  else return Kernel._object;}


/*********************************************************************/
/**    3. Property                                                   */
/*********************************************************************/

// create a property
property *property::make(char *name, module *m)
{property *ob = (property *) Kernel._property->instantiate(name,m);
  ob->comment = name;               // for debug
  ob->range = Kernel._any;
  ob->open = 1;
#ifdef __LP64__
  if (ClEnv->verbose > 10) printf("--- create property %s @ %ld\n",ob->comment,getADR(ob));
#else
  if (ClEnv->verbose > 10) printf("--- create property %s @ %d\n",ob->comment,getADR(ob));
#endif
  return ob;}

// same with a status
property *property::make(char *name, CL_INT op, module *m)
{property *ob = make(name,m);
  ob->open = op;
  return ob;}

// temporaty
property *property::make(char *name, CL_INT op, module *m, CL_INT i)
{property *ob = make(name,m);
  ob->open = op;
  ob->dispatcher = i;
  return ob;}

// new (v3.1) same with a dispatcher index !
property *property::make(char *name, CL_INT op, module *m,ClaireClass *c, CL_INT i)
{property *ob = make(name,m);
  ob->open = op;
  ob->dispatcher = i;
  ob->domain = c;
  return ob;}

// constructor for operations
operation *operation::make(char *name, module *m, CL_INT p)
{operation *ob = (operation *) Kernel._operation->instantiate(name,m);
  ob->comment = name;               // for debug
  ob->range = Kernel._any;
  ob->open = 1;
  ob->precedence = p;
  return ob;}
  
// constructor for operations that supports an  open status 
operation *operation::make(char *name, CL_INT op, module *m, CL_INT p)
{operation *ob = (operation *) Kernel._operation->instantiate(name,m);
  ob->comment = name;               // for debug
  ob->range = Kernel._any;
  ob->open = op;
  ob->precedence = p;
  return ob;}
  
// dynamic binding for a message (call) - We got rid of variable argument and use C++
// polymorphism

OID property::operator() (OID arg1)
{PUSH(arg1);
return stack_apply(1);}
   
OID property::operator() (OID arg1, OID arg2)
{PUSH(arg1); PUSH(arg2);
return stack_apply(2);}

OID property::operator() (OID arg1, OID arg2, OID arg3)
{PUSH(arg1); PUSH(arg2); PUSH(arg3);
return stack_apply(3);}

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4);
return stack_apply(4);}

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);
return stack_apply(5);}

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);
 return stack_apply(6); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);
 return stack_apply(7); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);
 return stack_apply(8); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8); PUSH(arg9);
 return stack_apply(9); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8); PUSH(arg9); PUSH(arg10);
 return stack_apply(10); }

// v3.2.54
OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10, OID arg11)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8); PUSH(arg9); PUSH(arg10); PUSH(arg11);
 return stack_apply(11);}
   
OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,OID arg11, OID arg12)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);PUSH(arg9); PUSH(arg10); PUSH(arg11); PUSH(arg12);
    return stack_apply(12); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,
                          OID arg11, OID arg12, OID arg13)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6); PUSH(arg7);PUSH(arg8);PUSH(arg9); PUSH(arg10);PUSH(arg11); PUSH(arg12); PUSH(arg13);
 return stack_apply(13); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,
                          OID arg11, OID arg12, OID arg13, OID arg14)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);
 PUSH(arg9); PUSH(arg10); PUSH(arg11); PUSH(arg12); PUSH(arg13); PUSH(arg14);
 return stack_apply(14); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,
                          OID arg11, OID arg12, OID arg13, OID arg14, OID arg15)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);
 PUSH(arg9); PUSH(arg10); PUSH(arg11); PUSH(arg12); PUSH(arg13); PUSH(arg14); PUSH(arg15);
 return stack_apply(15); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,
                          OID arg11, OID arg12, OID arg13, OID arg14, OID arg15, OID arg16)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);
 PUSH(arg9); PUSH(arg10);PUSH(arg11); PUSH(arg12); PUSH(arg13); PUSH(arg14); PUSH(arg15);PUSH(arg16);
 return stack_apply(16); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,
                          OID arg11, OID arg12, OID arg13, OID arg14, OID arg15,
                          OID arg16, OID arg17)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);
 PUSH(arg9); PUSH(arg10);PUSH(arg11); PUSH(arg12); PUSH(arg13); PUSH(arg14); PUSH(arg15);PUSH(arg16);
 PUSH(arg17);
 return stack_apply(17); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,
                          OID arg11, OID arg12, OID arg13, OID arg14, OID arg15,
                          OID arg16, OID arg17, OID arg18)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);
 PUSH(arg9); PUSH(arg10);PUSH(arg11); PUSH(arg12); PUSH(arg13); PUSH(arg14); PUSH(arg15);PUSH(arg16);
 PUSH(arg17);PUSH(arg8);
 return stack_apply(18); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,
                          OID arg11, OID arg12, OID arg13, OID arg14, OID arg15,
                          OID arg16, OID arg17, OID arg18, OID arg19)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);
 PUSH(arg9); PUSH(arg10);PUSH(arg11); PUSH(arg12); PUSH(arg13); PUSH(arg14); PUSH(arg15);PUSH(arg16);
 PUSH(arg17);PUSH(arg18); PUSH(arg19);
 return stack_apply(19); }

OID property::operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5,
                          OID arg6, OID arg7, OID arg8, OID arg9, OID arg10,
                          OID arg11, OID arg12, OID arg13, OID arg14, OID arg15,
                          OID arg16, OID arg17, OID arg18, OID arg19, OID arg20)
{PUSH(arg1); PUSH(arg2); PUSH(arg3); PUSH(arg4); PUSH(arg5);PUSH(arg6);PUSH(arg7);PUSH(arg8);
 PUSH(arg9); PUSH(arg10);PUSH(arg11); PUSH(arg12); PUSH(arg13); PUSH(arg14); PUSH(arg15);PUSH(arg16);
 PUSH(arg17);PUSH(arg18); PUSH(arg19); PUSH(arg20);
 return stack_apply(20); }

// this is used by the compiler
OID property::super(ClaireClass *c,CL_INT size)
{CL_INT j = ClEnv->index, i = j - size;
 return eval_message_property(this, find_which_class1(c,definition,i,j),i,CFALSE);}


OID property::stack_apply(CL_INT size)
{CL_INT i = ClEnv->index - size;
 return eval_message_property(this,
              find_which_property1(this,i,OWNER(ClEnv->stack[i])), i, CFALSE);}


// how to create a new method
method *property::addMethod(list *dom, ClaireType *ran, CL_INT sta, ClaireFunction *f)
{method *m = (method *) Kernel._method->instantiate();
   Kernel._method->instances->addFast(_oid_(m));
   m->selector = this;
   restrictions->addFast(_oid_(m));
   m->domain = dom;
   m->range = ran;
   m->module_I = ClEnv->module_I;
   m->functional = f;
   m->evaluate = f;
   m->status = sta;
   // computes the list of sorts
   {list* l = list::empty(Kernel._class);
    ITERATE(z);
    for (START(dom); NEXT(z);)
         l->addFast(_oid_(sort_I_class(class_I_type(OBJECT(ClaireType,z)))));
    l->addFast(_oid_(sort_I_class(class_I_type(ran))));
    m->srange = l;}
   insert_definition_property(this,m);
   return m;}


// special case for a float method
method *property::addFloatMethod(list *dom, ClaireType *ran, CL_INT sta, ClaireFunction *f,
                                 ClaireFunction *f2)
{method *m = addMethod(dom,ran,sta,f);
  m->evaluate = f2;
  return m;}


// add an inlining definition
method *method::inlineDef(char *def)
{return inlineok_ask_method(this,def); }

// --------------------- API method -------------------------------------------

CL_EXPORT method *add_method_property(property *p, list *dom, ClaireType *r,
                   CL_INT status, OID f)
 { return p->addMethod(dom,r,status,
                       ((f == CNULL) ? NULL : OBJECT(ClaireFunction,f)));}

 
/*********************************************************************/
/**    4. Tables                                                     */
/*********************************************************************/

// expand the alist (hash table) and then creates the item
// the size is 2^n - 4 (even)
CL_INT table::expand(OID x)
{list *old = (list *) graph;
 CL_INT i, j = old->content[0];             // j = chunk size
 list *NEW = make_list_integer(2 * (*old)[0] - 4,CNULL);
   for (i=1; i < j - 4; i = i+2)
       if ((*old)[i] != CNULL) insertHash(NEW,(*old)[i],(*old)[i + 1]);
   graph = NEW;
   if (ClRes->cWorld != 0 && store_ask == CTRUE)      // new from 2.5
     STOREOBJ(((OID *) &graph),(ClaireObject *) old);
   return index_table(this,x);}

// insert a new bucket in a alist without problem. This only works for
// buckets !
CL_INT table::insertHash (list *l, OID x, OID val)
{CL_INT i,chsize = l->content[0],end = chsize - 4,
     mask = (chsize >> 1) - 1, entry = (ClRes->hashOid(mask,x) << 1) + 1;
     for (i = entry; i < end; i = i + 2)
        if ((*l)[i] == CNULL) {(*l)[i] = x; (*l)[i+1] = val; return 1;}
     for (i = 1; i < entry; i = i + 2)
        if ((*l)[i] == CNULL) {(*l)[i] = x; (*l)[i + 1] = val; return 1;}
     return 1;}

// -------------------- API functions -----------------------------------

// add an item in an association list (of size 2^n - 3, full of unknown)
// uses a hash insertion in a list (use the cardinal to find is a new list
// must be allocated). Returns the position in the list
CL_EXPORT CL_INT index_table(table *a, OID x)
{list *l = (list *) a->graph;
 CL_INT i, chsize = (*l)[0], end = chsize - 4,
     mask = (chsize >> 1) - 1, entry = (ClRes->hashOid(mask,x) << 1) + 1;
   for (i = entry; i < end; i = i + 2)
        if (equal((*l)[i],x) == CTRUE) return i + 1;
        else if ((*l)[i] == CNULL)
          {ClaireClass *c = OWNER(a->DEFAULT);
           if ((i - entry) > (chsize >> 2)) return a->expand(x);
           (*l)[i] = x;
           if ((c == Kernel._set) || (c == Kernel._list))
                (*l)[i+1] = _oid_(copy_bag(OBJECT(bag,a->DEFAULT)));
           else (*l)[i+1] = a->DEFAULT;
           return (i + 1);}
   if ((i - entry) > (chsize >> 2)) return a->expand(x);
   if (entry > end) entry = end;    // <yc> 9/98 do not cross the bound
   for (i = 1; i < entry; i = i + 2)
       if (equal((*l)[i],x) == CTRUE) return i + 1;
       else if ((*l)[i] == CNULL)
          {ClaireClass *c = OWNER(a->DEFAULT);
           (*l)[i] = x;
           if ((c == Kernel._set) || (c == Kernel._list))   // v3.0.29 : copy
                (*l)[i+1] = _oid_(copy_bag(OBJECT(bag,a->DEFAULT)));
           else (*l)[i+1] = a->DEFAULT;
           return (i + 1);}
   return a->expand(x);}


// a nice version that takes two args and does not allocate the tuple.
// WARNING: this does not return the index but the value !!!!
//          it is thus simpler, because it is only used for reading
// v3.2.16: was completely false !!!!
CL_EXPORT CL_INT index_table2(table *a, OID x, OID y)
{list *l = (list *) a->graph;
 CL_INT i,chsize = (*l)[0], end = chsize - 4,
     mask = (chsize >> 1) - 1,
     hash2 = (ClRes->hashOid(mask,x) + ClRes->hashOid(mask,y)) & mask,
     entry = (hash2 << 1) + 1;
   for (i = entry; i < end; i = i + 2)
      {if ((*l)[i] == CNULL) return a->DEFAULT;
       else if (equal((*(OBJECT(list,(*l)[i])))[1],x) == CTRUE &&
                equal((*OBJECT(list,(*l)[i]))[2],y) == CTRUE) return (*l)[i + 1];}
   if (entry > end) entry = end;    // <yc> 9/98 do not cross the bound
   for (i = 1; i < entry; i = i + 2)
     {if ((*l)[i] == CNULL) return a->DEFAULT;
      else if (equal((*OBJECT(list,(*l)[i]))[1],x) == CTRUE &&
               equal((*OBJECT(list,(*l)[i]))[2],y) == CTRUE) return (*l)[i + 1];}
   return a->DEFAULT;}



//<sb> put make_table at the kernel level -> we need a special protection
// new in v3.2.50 a constructor for building a table dynamically
CL_EXPORT table * make_table_type(ClaireType *dom, ClaireType *rng, OID def)
{ table * t = (table *)new_object_class(Kernel._table);
  t->range = rng;
  t->domain = dom;
  t->DEFAULT = def;
  t->params = _oid_(Kernel._any);
  t->graph = 0;
  if (ClAlloc->statusGC != 2)  GC_PUSH(t);
  t->graph = make_list_integer(29, CNULL);
  return t;}


//<sb> moved find_wich_property into Kernel, here any program spends
// many time. It as been carefully optimized :
//    - handles the case when there is no dictionary, an inline 
// version (in Kernel.h) handles the dictionary case (early exit optim)
//     - it manages a cache containing the sort of arguments pushed on the stack,
// and perform the restriction match check against the cache

/*
struct fw_cache_item {
  restriction *r;
  property *def;
  CL_INT narg;
  ClaireClass *owners[4];
  CL_INT conflict;
};

static fw_cache_item fw_cache[1024];

#define FW_HASH_BEGIN CL_INT hash = 0;
#define FW_HASH_MORE(n) {hash += n; hash += (hash << 10);hash ^= (hash >> 6);}
#define FW_HASH_END {hash += (hash << 3); hash ^= (hash >> 11); hash += (hash << 15); hash &= 1023;}
#define FW_HASH_INSERT(restr) {fw_cache_item &it = fw_cache[hash]; \
      if (it.r == NULL) {it.r = restr; it.def = p; it.narg = x; memcpy(&it.owners, sts+1, 4*sizeof(CL_INT));}}

void reset_find_which_cache() {
  memset(fw_cache, 0, sizeof(fw_cache));
}

static ClaireClass* sts[21];

ClaireObject * find_which_property_no_dictionary_more(property *p, CL_INT n, CL_INT *st, CL_INT x, unsigned hash);
ClaireObject * find_which_property_no_dictionary(property *p,int n)
{   CL_INT  x = ClEnv->index - n;
  CL_INT *st = ClEnv->stack;
  CL_INT j = 1;
  CL_INT y = n;
  //<sb> fill a cache of arguments sorts
  FW_HASH_BEGIN
  FW_HASH_MORE((CL_UNSIGNED)p);
  FW_HASH_MORE((CL_UNSIGNED)x);
  for(;j <= x; j++) {
    CL_INT d = st[y++];
    ClaireClass *c = OWNER(d);
    sts[j] = c;
    FW_HASH_MORE((CL_UNSIGNED)c);
  }
  FW_HASH_END
  fw_cache_item &it = fw_cache[hash];
  if (it.r && it.def == p && x == it.narg && memcmp(&it.owners, sts+1, x*sizeof(CL_INT)) == 0) {
    return it.r;
  }
  return find_which_property_no_dictionary_more(p, n, st, x, hash);
}

ClaireObject * find_which_property_no_dictionary_more(property *p, CL_INT n, CL_INT *st, CL_INT x, unsigned hash) {

  static OID lla = 0;
  static ClaireClass *lcl;
  static ClaireClass *lany;
  static ClaireClass *lint;
  if(lla == 0) {
    lla = _oid_(Kernel._listargs);
    lcl = Kernel._class;
    lany = Kernel._any;
    lint = Kernel._integer;
    memset(fw_cache, 0, sizeof(fw_cache));
  }
  list *ldef = p->definition;
  OID *ar = ldef->content;
  CL_INT len = ldef->length;
  CL_INT j;
  //<sb> lookup for a mathing restriction
  for(j = 1;j <= len; j++) {
    restriction *r = OBJECT(restriction,ar[j]);
    list *l = r->domain;
    CL_INT z = l->length;
    OID *ct = l->content;
    if ((z == x) && ct[x] != lla) {
      CL_INT i = 1;
      CL_INT y = n;
      while (i <= x) {
        OID  u = ct[i];
        ClaireClass* ens = OBJECT(ClaireClass,u);
        if (ens->isa == lcl) {
          ClaireClass *c = sts[i];
          if ((INT_MASK & u) != OBJ_CODE) {
            if (c == lany || c == lint)
              break;
          } else if (!INHERIT(c, ens)) {
            break;
          }
        } else if (vmatch_ask_any(u,st[y],n) != CTRUE)
          break;
        ++y;
        ++i;
      }
      if (i > x) {FW_HASH_INSERT(r) return r;}
    } else if ((z-1) <= x && ct[z] == lla) {
       CL_INT  i = 1;
       while ((i <= z))
        { { CL_INT  y = ((n-1)+i);
          if (ct[i] == lla)
           { st[y] = _oid_(get_args_integer(y));
            ClEnv->index = y + 1;
            return r;
            }
          else if (vmatch_ask_any(ct[i],st[y],n) != CTRUE)
           {
            break;
           }
          }
          ++i;
      }
    }      
  }
return CFALSE;
}*/


CL_EXPORT ClaireObject * find_which_property1(property *p,CL_INT n,ClaireClass *c)
{   static OID lla = 0;
  static ClaireClass *lcl;
  static ClaireClass *lany;
  static ClaireClass *lint;
  static ClaireClass* sts[21];
  if (p->dictionary == CTRUE) return hashget_class(c, p);
  else {
    if(lla == 0) {
      lla = _oid_(Kernel._listargs);
      lcl = Kernel._class;
      lany = Kernel._any;
      lint = Kernel._integer;
    }
    list *ldef = p->definition;
    OID *ar = ldef->content;
    CL_INT len = ldef->length;
    CL_INT  x = ClEnv->index - n;
    CL_INT *st = ClEnv->stack;
    CL_INT j = 1;
    CL_INT  y = n;
    //<sb> fill a cache of arguments sorts
    for(;j <= x; j++) {
      CL_INT d = st[y++];
      sts[j] = OWNER(d);
    }
    //<sb> lookup for a mathing restriction
    for(j = 1;j <= len; j++) {
      restriction *r = OBJECT(restriction,ar[j]);
      list *l = r->domain;
      CL_INT z = l->length;
      OID *ct = l->content;
      if ((z == x) && ct[x] != lla) {
        CL_INT i = 1;
        CL_INT y = n;
        while (i <= x) {
          OID  u = ct[i];
          ClaireClass* ens = OBJECT(ClaireClass,u);
          if (ens->isa == lcl) {
            ClaireClass *c = sts[i];
              if ((INT_MASK & u) != OBJ_CODE) {
                if (c == lint || c == lany)
                  break;
              } else if (!INHERIT(c, ens)) {
                break;
              }
          } else if (vmatch_ask_any(u,st[y],n) != CTRUE)
            break;
          ++y;
          ++i;
        }
        if (i > x) return r;
      } else if ((z-1) <= x && ct[z] == lla) {
         CL_INT  i = 1;
         while ((i <= z))
          { { CL_INT  y = ((n-1)+i);
            if (ct[i] == lla)
             { st[y] = _oid_(get_args_integer(y));
              ClEnv->index = y + 1;
              return r;
              }
            else if (vmatch_ask_any(ct[i],st[y],n) != CTRUE)
             {
              break;
             }
            }
            ++i;
        }
      }      
    }
  }
  return CFALSE;
}
/***********************************************************************/
/**   microCLAIRE                                       Yves Caseau    */
/**   clString.cpp                                                     */
/**  Copyright (C) 1998-2003 Yves Caseau. All Rights Reserved.         */
/**  cf claire.h                                                       */
/***********************************************************************/


// this file contains the C++ code for the imported objects, mostly strings
// (and the associated symbols, although they are not imported) but also
// integers and floats. Note the double implementation for floats

/*********************************************************************/
/** Contents                                                         */
/**    0. Color support (xl)                                         */
/**    1. Strings                                                    */
/**    2. Modules                                                    */
/**    3. Symbol                                                     */
/**    4. integer                                                    */
/**    5. floats                                                     */
/*********************************************************************/

/**********************************************************************/
/**    0: Color support                                               */
/**********************************************************************/

#define PUTS(p, s, n) Core.write_port->fcall((CL_INT)p, (CL_INT)s, n)

// 0 -> disable stratup baner & "bye..." string
CL_EXPORT CL_INT LOGO = 0;
CL_EXPORT CL_INT TOPLEVEL = 1;
// 1 -> colors supported
// 2 -> html colors
CL_EXPORT CL_INT COLOR = 0;

CL_EXPORT CL_INT current_color = 30;
CL_EXPORT CL_INT current_bold = 0;

//<sb> if s match m we return true
// and we offset s with the length of m
// note: the given string may be modified!
CL_INT match(char** s, char* m) {
        char* d = *s; char* p = m;
        while(*d && *m) {
            if(*d != *m) return 0;
                d++;m++;
                if(*m) continue; break; }
        if(*m) return 0;
        *s += m - p; return 1; }

#define IS(sc) match(&format,sc)
CL_EXPORT void Ctracef(char* format, ...) {
  PortObject* p = ClEnv->cout;
  ClEnv->cout = get_device_port1(ClEnv->ctrace);
    va_list argList; va_start(argList, format);
        char buf[10]; strcpy(buf,"%xxxxxxxx");
        char *formater = (char*)buf; char* fmt;
        while(*format) {
           if(!IS("%")) {
               char tmp[] = "c";
               *tmp = *format++;
               princ_string(tmp); }
           else if(IS("%")) princ_string("%");
           else { fmt = formater + 1; // resolve formater
                  do {*fmt++ = *format;}
                  while(!(IS("d")||IS("f")||IS("i")||IS("u")||IS("x")||IS("X")||
                          IS("s")||IS("c")||IS("g")||IS("e")||IS("E")||IS("o")));
                  *fmt = '\0'; char buffer[2024];
                  sprintf(buffer, formater, va_arg(argList, void*));
                  princ_string(buffer); } }
        ClEnv->cout = p;
}


#define mytput(b,n) { if (terminal_ask_port1(p) == CTRUE) PUTS(p,(char*)b, n); }


//<sb> change current terminal color
CL_EXPORT void color(CL_INT c, CL_INT bold) {
  #ifndef __MVS__
  //<sb> no color on MVS
  PortObject *p = ClEnv->cout;
  CL_INT cupdate = c;
  if(bold) bold = 1;
  if (c == 30) c = 0;
  if(COLOR == 1) {
    #ifndef CLPC
    char buf[16];
    CL_INT n;
    mytput("\033[0m", 4);
    if(c != current_color) {
      current_color = c;
#ifdef __LP64__
      n = sprintf(buf,"\033[%ldm", c);
#else
      n = sprintf(buf,"\033[%dm", c);
#endif
      mytput(buf,n);
    }
    if(bold) {
      current_bold = bold;
      n = sprintf(buf,"\033[1m");
      mytput(buf,n);
    }
    #else
    static HANDLE pcConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    static CL_INT black = -1;
    static CL_INT bkground = -1;
    if(black == -1) {
      WORD dw; DWORD nr;COORD xy;xy.X = xy.Y = 0;
      ReadConsoleOutputAttribute(pcConsole,&dw,1,xy,&nr);
      black = (dw&FOREGROUND_RED)|(dw&FOREGROUND_GREEN)|(dw&FOREGROUND_BLUE)|(dw&FOREGROUND_INTENSITY); 
      bkground = (dw&BACKGROUND_RED)|(dw&BACKGROUND_GREEN)|(dw&BACKGROUND_BLUE)|(dw&BACKGROUND_INTENSITY); }
    switch(c) { case 0: c = black; break; // map unices/pc colors
      case 31: c = FOREGROUND_RED|FOREGROUND_INTENSITY; break;
      case 32: c = FOREGROUND_GREEN; break;
      case 33: c = FOREGROUND_GREEN|FOREGROUND_RED; break;
      case 34: c = FOREGROUND_BLUE|FOREGROUND_INTENSITY; break;
      case 35: c = FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY; break;
      case 36: c = FOREGROUND_GREEN|FOREGROUND_BLUE; break;
      case 37: c = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY; break; }
    flush_port_port1_Core(ClEnv->cout);
    SetConsoleTextAttribute(pcConsole, c|bkground);
    #endif
  } else if(COLOR == 2) {
    PortObject *pout = ClEnv->cout;
    if(current_bold && bold == 0) PUTS(pout,"</b>",4);
    if (current_color != c && c == 0)
      PUTS(pout,"</font>",7);
    switch(c) {
      case 31:
        PUTS(pout,"<font color=red>",16);
        break;
      case 32:
        PUTS(pout,"<font color=green>",18);
        break;
      case 34:
        PUTS(pout,"<font color=blue>",17);
        break;
      }
    if(bold && current_bold == 0) PUTS(pout,"<b>",3);
    
  }
  current_color = cupdate;
  current_bold = bold;
  #endif
}

CL_EXPORT CL_INT color_integer(CL_INT c) {
  avoid_signal_handling++;
  CL_INT old = COLOR;
  if(old == 2) color(30,0);
  COLOR = c;
  avoid_signal_handling--;
  return old;
}

CL_EXPORT CL_INT color_void() {return COLOR;}

/*********************************************************************/
/**    1: String functions                                           */
/*********************************************************************/

// --- there are all API functions since string are imported char* -----

CL_EXPORT CL_INT length_string(char* s) {return LENGTH_STRING(s);}

// make a local copy of a string
CL_EXPORT char *copy_string(char *s)
{  CL_INT len = LENGTH_STRING(s);
  if(len <= 0) return ClAlloc->makeString(0);
  char *a = ClAlloc->makeString(len);
  memcpy(a,s,len);
  return a; }

CL_EXPORT char *copy_string1(char *s, CL_INT len)
{    if(len <= 0) return ClAlloc->makeString(0);
  char *a = ClAlloc->makeString(len);
  memcpy(a,s,len);
  return a; }


// equality on strings
CL_EXPORT ClaireBoolean *equal_string(register char *s1, register char *s2)
{ if (s1 == s2) return CTRUE;
  CL_INT l1 = LENGTH_STRING(s1);
  CL_INT l2 = LENGTH_STRING(s2);
  if (l1 != l2) return CFALSE;
  return memcmp(s1,s2,l1) == 0 ? CTRUE : CFALSE; }

// equality on strings in an insensitive
CL_EXPORT ClaireBoolean *insensitive_equal_string1(register char *s1, register char *s2)
{ CL_INT l1 = LENGTH_STRING(s1);
  CL_INT l2 = LENGTH_STRING(s2);
  if (l1 != l2) return CFALSE;
  CL_INT i = 0;
  for(;i < l1;i++) {
  unsigned char c1 = s1[i];
  unsigned char c2 = s2[i];
  if (tolower(c1) != tolower(c2))
    return CFALSE;
  }
  return CTRUE; }

//<sb> horific but does the job!
CL_EXPORT void color_princ_string2(char *s, CL_INT i, CL_INT j)
{ if (i < 1) i = 1; if (j < 1) j = 1;
  PortObject *pout = ClEnv->cout;
  if(pout == 0) return;
  char *end = s + j;
  char *anchor = 0;
  s = s + i - 1;
  CL_INT bold = 0;
   while(s < end) {
   if(*s == '`') {
     if(anchor && s - anchor) {
       if(COLOR == 2) {
        while(anchor < s) {
          if(*anchor == '\n') PUTS(pout,"<br>\n",5);
            else if(*anchor == '>') PUTS(pout,"&gt;",4);
            else if(*anchor == '<') PUTS(pout,"&lt;",4);
            else if(*anchor == '&') PUTS(pout,"&amp;",5);
            else if(*anchor == ' ') PUTS(pout,"&nbsp;",6);
            else if(*anchor == '"') PUTS(pout,"&quot;",6);
            else PUTS(pout,anchor,1);
            anchor++;
        }
      } else PUTS(pout,anchor, s - anchor);
       anchor = 0;
     }
    bold = 0;
    CL_INT f = 0;
    char* tag = s;
    if (++s == end) {pout->put('`');break;}
    if(*s == '`') {bold = 1; if (++s == end) {pout->put('`');pout->put('`');break;}}
    {if(*s == 'R' && ++s != end && // RED
     *s == 'E' && ++s != end &&
      *s == 'D') {f = 1;if(COLOR > 0) color(31, bold);}
    else if(*s == 'B' && ++s != end) { // BLACK
     if(*s == 'L' && ++s != end) {
      if(*s == 'A') {
       if(++s < end && *s == 'C' && ++s != end &&
        *s == 'K') {f = 1;if(COLOR > 0) color(30, bold);} }
      else if(*s == 'U' && ++s != end && // BLUE
       *s == 'E') {f = 1;if(COLOR > 0) color(34, bold);} }}
    else if(*s == 'C' && ++s != end && // CYAN
     *s == 'Y' && ++s != end &&
      *s == 'A' && ++s != end &&
       *s == 'N') {f = 1;if(COLOR > 0) color(36, bold);}
    else if(*s == 'W' && ++s != end && // WHITE
     *s == 'H' && ++s != end &&
      *s == 'I' && ++s != end &&
       *s == 'T' && ++s != end &&
        *s == 'E') {f = 1;if(COLOR > 0) color(37, bold);}
    else if(*s == 'G' && ++s != end && // GREEN
     *s == 'R' && ++s != end &&
      *s == 'E' && ++s != end &&
       *s == 'E' && ++s != end &&
        *s == 'N') {f = 1;if(COLOR > 0) color(32, bold);}
    else if(*s == 'Y' && ++s != end && // YELLOW
     *s == 'E' && ++s != end &&
      *s == 'L' && ++s != end &&
       *s == 'L' && ++s != end &&
        *s == 'O' && ++s != end &&
         *s == 'W') {f = 1;if(COLOR > 0) color(33, bold);}
    else if(*s == 'M' && ++s != end && // MAGENTA
     *s == 'A' && ++s != end &&
      *s == 'G' && ++s != end &&
       *s == 'E' && ++s != end &&
        *s == 'N' && ++s != end &&
         *s == 'T' && ++s != end &&
          *s == 'A') {f = 1;if(COLOR > 0) color(35, bold);}}
    if(f == 0) {
      if(COLOR == 2) {
        while(tag <= s) {
          if(*tag == '\n') PUTS(pout,"<br>\n",5);
            else if(*tag == '>') PUTS(pout,"&gt;",4);
            else if(*tag == '<') PUTS(pout,"&lt;",4);
            else if(*tag == '&') PUTS(pout,"&amp;",5);
            else if(*tag == ' ') PUTS(pout,"&nbsp;",6);
            else if(*tag == '"') PUTS(pout,"&quot;",6);
            else PUTS(pout,tag,1);
            tag++;
        }
      } else PUTS(pout,tag, s - tag + 1);
      s++;
    } else {s++; while(s < end && (*s == ' ' || *s == '\t')) s++; }
  } else {
    if(anchor == 0) anchor = s;
    s++;
  }}
  if(anchor && s - anchor) {
  if(COLOR == 2) {
    while(anchor < s) {
      if(*anchor == '\n') PUTS(pout,"<br>\n",5);
      else if(*anchor == '>') PUTS(pout,"&gt;",4);
      else if(*anchor == '<') PUTS(pout,"&lt;",4);
      else if(*anchor == '&') PUTS(pout,"&amp;",5);
          else if(*anchor == ' ') PUTS(pout,"&nbsp;",6);
          else if(*anchor == '"') PUTS(pout,"&quot;",6);
      else pout->put(*anchor);
      anchor++;
    }
  } else PUTS(pout,anchor, s - anchor);
  anchor = 0; }}

CL_EXPORT void color_princ_string1(char *s) {
  color_princ_string2(s,1,LENGTH_STRING(s));}

CL_EXPORT void princ_string1(char *s, CL_INT i, CL_INT j) {
  if(COLOR == 2) {color_princ_string2(s,i,j); return;}
  CL_INT len = LENGTH_STRING(s);
  if(len == 0) return;
  if (j > len) j = len;
  if (i > len) i = len;
  Core.write_port->fcall((CL_INT)ClEnv->cout, (CL_INT)(s+i-1), j-i+1);
}

CL_EXPORT void princ_string(char *s) {
  if(COLOR == 2) {color_princ_string1(s); return;}
 Core.write_port->fcall((CL_INT)ClEnv->cout, (CL_INT)s, LENGTH_STRING(s));
}

//<sb> add the ability to output in hexa
CL_EXPORT char* hex_I_integer(CL_INT i) {
  char buf[10] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
  CL_INT j = 0;
#ifdef __LP64__
  sprintf(buf, "%8lX", i);
#else
  sprintf(buf, "%8X", i);
#endif
  while(j < 8 && buf[j] == ' ') {buf[j] = '0';j++;}
  return copy_string(buf);
}

//<sb> add the ability to output in binary
CL_EXPORT char* bin_I_integer(CL_INT i) {
  char buf[32];
  CL_INT j;
  for(j = 32-2;j >= 0; j--)
       buf[32 - 2 - j] = (i>>j) & 01 ?'1':'0';
  buf[31] = 0;
  return copy_string(buf);
}

#define PRINT_FMT(p,s, n) {if(COLOR > 0) color(C ? 34 : 32,0); PUTS(p,s,n); if(COLOR > 0) color(30,0);}

CL_EXPORT void internal_print_string(char* ss, CL_INT len) { 
  CL_INT i;
  CL_INT C = 0;
  PortObject *pout = ClEnv->cout;
  for (i=0; i < len; i++) {
    C = 1 - C;
    unsigned char c = ss[i];
      //if(c < 0) c = c + 256;
    if (c == '"') PRINT_FMT(pout,"\\\"",2)
    else if (c == '\\') PRINT_FMT(pout,"\\\\",2)
    else if (c == '\n') PRINT_FMT(pout,"\\n",2)
    else if (c == '\t') PRINT_FMT(pout,"\\t",2)
    else if (c == '\r') PRINT_FMT(pout,"\\r",2)
    else if (COLOR == 2 && c == '<') PUTS(pout,"&lt;",4);
    else if (COLOR == 2 && c == '>') PUTS(pout,"&gt;",4);
    else if (COLOR == 2 && c == '&') PUTS(pout,"&amp;",5);
    else if (c == '\0') {
      if(COLOR > 0) color(C ? 34 : 32,0);
      PUTS(pout,"\\0",2);
      if(i < len - 1 && (ss[i+1] >= '0' && ss[i+1] <= '7'))
        PUTS(pout,"00",2);
      if(COLOR > 0) color(30,0);
    } else if(c <= (unsigned char)3) {
      if(COLOR > 0) color(C ? 34 : 32,0);
#ifdef __LP64__
      char buf[4]; sprintf(buf,"%03lo",(CL_INT)c);
#else
      char buf[4]; sprintf(buf,"%03o",(CL_INT)c);
#endif
      PUTS(pout,"\\",1);
      PUTS(pout,buf,3);
      if(COLOR > 0) color(30,0);
    } else PUTS(pout,&c,1);}}

// print a string with the "" (what you see is what you read)
//<sb> prints in a readable form for ascii in (0 .. 31) U (127 .. 159)
// ex: the string of length 1 where integer!(s[1]) = 1 is printed "\001"
CL_EXPORT void self_print_string(char *ss) {
  PortObject *pout = ClEnv->cout;
  CL_INT len = LENGTH_STRING(ss); //<sb> buffer
  if(COLOR == 1) {
    color(34,0);
    PUTS(pout,"\"", 1);
    color(30,0);
  } else if(COLOR == 2) {
    PUTS(pout,"<font color=blue>\"</font><font color=black>",43);
  } else PUTS(pout,"\"", 1);
   internal_print_string(ss,len);
  if(COLOR == 1) {
    color(34,0);
    PUTS(pout,"\"", 1);
    color(30,0);
  } else if(COLOR == 2) {
    PUTS(pout,"</font><font color=blue>\"</font>",32);
  } else PUTS(pout,"\"", 1);
}

// concatenate two strings
CL_EXPORT char *append_string(char *ss1, char *ss2)
{ CL_INT i;
  CL_INT l1 = LENGTH_STRING(ss1);
  CL_INT l2 = LENGTH_STRING(ss2);
  char* a = ClAlloc->makeString(l1 + l2);
  if(l1) memcpy(a,ss1,l1);
  if(l2) memcpy(a+l1,ss2,l2);
  return a;}

// finds the integer value
CL_EXPORT CL_INT integer_I_string(char *s)
{ return strtol(s,NULL,10);}

// create a substring from a string
//<sb> add support for negative index that
// are accounted from the end of the string
CL_EXPORT char *substring_string(char *ss, CL_INT n, CL_INT m)
{ CL_INT l = LENGTH_STRING(ss);
  if(n < -l) n = -l;
  if(n < 0) n = l + 1 + n;
  if(m < 0) m = l + 1 + m;
  if(m > l) m = l;
  if (n < 1 || n > l || m < 1) return "";
  CL_INT len = 1 + m - n;
  char* a = ClAlloc->makeString(len);
  if(len) memcpy(a, ss + n - 1, len);
  return a; }


// look for th eposition of the CHAR c in s
CL_EXPORT CL_INT get_string(char *ss, ClaireChar *c)
{ OID i;
  CL_INT len = LENGTH_STRING(ss);
  char c2 = (char) c->ascii;
  for (i=0; i < len; i++) if (ss[i] == c2) return(i+1);
  return 0;}

// compare two strings
CL_EXPORT ClaireBoolean *_less_string(char *s1, char *s2)
{CL_INT i;
 CL_INT l1 = LENGTH_STRING(s1); //<sb> buffer
 CL_INT l2 = LENGTH_STRING(s2); 
 for (i = 0; i < l1; i++)
    {if (i >= l2) return CFALSE;
    else if (s1[i] < s2[i]) return(CTRUE);
     else if (s1[i] > s2[i]) return (CFALSE);}           // include s2[i] = '0' !!!
 return CTRUE;}                                          // v3.1.12 ????

// test is a string is included into another
CL_EXPORT CL_INT included_string(char *s1, char *s2,ClaireBoolean *p)
{CL_INT c,i,j;
    CL_INT l1 = LENGTH_STRING(s1);
    CL_INT l2 = LENGTH_STRING(s2);
    for (i = 0; i < l1; i++)
    for (j = 0;; j++)
      { c = s1[i+j] - s2[j];
        if ((c == 0) || ((p == CTRUE) &&
             (((c == 32) && ((s2[j] >= 'A') && (s2[j] <= 'Z'))) ||
              ((c == -32) && ((s2[j] >= 'a') && (s2[j] <= 'z'))))))
           {if (j+1 >= l2) return i+1;}
        else break;}
  return 0;}

// get the CHAR at the i-th place in s
CL_EXPORT ClaireChar *nth_string(char *ss, CL_INT n)
{ CL_INT len = LENGTH_STRING(ss);
  if(n < 1 || n > len) Cerror(11,n,_string_(ss));
  return char_I_integer((unsigned char) ss[n-1]); }     // v3.2.44  //<sb> buffer

// set the char at the i_th place in s
CL_EXPORT void nth_set_string (char *ss, CL_INT n, ClaireChar *c)
{ CL_INT len = LENGTH_STRING(ss);     // v3.2.44  //<sb> buffer
  if(n < 1 || n > len) Cerror(11,n,_string_(ss));
  ss[n-1] = (char) c->ascii; }


// shrinks a string by placing the '\0' marker
CL_EXPORT char *shrink_string(char *ss, CL_INT n) {
  if (n < 0) n = 0; //<sb> prevent negative length...
  if (n <= LENGTH_STRING(ss))
    { if(CLMEM(ss)) Cmemory[BUFFER_LEN_IDX(ss)] = n; //<sb> buffer
    ss[n] = '\0';
    }
   else Cerror(11,n,_string_(ss));
 return ss; }

// the old internal function
// watch out: TODO use claire ?
CL_EXPORT OID value_string(char *name)
{return value_module(ClEnv->module_I,name);}

// the new internal function
CL_EXPORT OID value_module(module *m, char *name)
{symbol *s = m->lookup(name);
   if (s == NULL) return CNULL;
   else return s->value;}

// new: access to the symbol the new internal function
CL_EXPORT OID get_symbol_module(module *m, char *name)
{symbol *s = m->lookup(name);
   if (s == NULL) return CNULL;
   else return _oid_(s);}

// new: return the current date
CL_EXPORT char *date_I_integer(CL_INT i)
{struct tm *newtime;
 time_t aclock;
 time(&aclock);
 newtime = localtime(&aclock);
 if(newtime == 0) Cerror(70,0,0);
 return copy_string(asctime(newtime)); }

// for upward compatibility
CL_EXPORT char* getenv_string(char *s)
{char *s2 = getenv(s);
 if (s2 == NULL) s2 = "";
 return copy_string(s2);}
 
/*********************************************************************/
/**    2: Modules                                                    */
/*********************************************************************/

// ------------- member functions for modules ---------------------------------------

// constructor: create a module from the name and the father in the hierarchy
module *module::make(char *s, module *sup)
{module *m = (module *) ClAlloc->makeAny(sizeof(module) / sizeof(CL_INT)); //<sb>
  GC_PUSH(m);
  m->isa = Kernel._module;
  m->name = NULL;
  m->part_of = sup;
  m->status = 0;
  m->version = NULL; //<sb>
  m->external = NULL; //<sb>
  m->evaluate = NULL; //<sb>
  m->source = NULL; //<sb>
  m->comment = s; //<sb>
  m->made_of = Kernel.nil;
  m->uses = Kernel.nil;
  m->parts = Kernel.nil;
  m->verbose = Kernel.ctrue;
  m->name = symbol::make(s,claire.it,claire.it);
  m->name->value = _oid_(m);
  m->parts = list::empty(Kernel._module);
  return m;}

// hash function.
CL_UNSIGNED module::hash(register char *s)
{CL_UNSIGNED val;
  CL_INT len = LENGTH_STRING(s); CL_INT i = 0;
  for (val= (CL_INT) this; i < len; (i++,s++))
      val = *s + 31 * val;
  return val & ClAlloc->hashMask;}

// lookup: check if a string in a given module is represented by a symbol (returns NULL
// if no symbol is found - does NOT create a new symbol
// this method embodies the strategy for looking in upper modules (namespace inheritance)
symbol *module::lookup(char *nm)
{CL_INT i = hash(nm);
   while ((ClRes->sTable[i] != NULL) &&
          ((this != ClRes->sTable[i]->module_I) ||
           (equal_string(nm,ClRes->sTable[i]->name) == CFALSE))) i++;
   if (i == ClAlloc->maxHash) Cerror(12,0,0);
   symbol *cur = ClRes->sTable[i];
   if (cur != NULL || this == claire.it) return cur;   // v3.2.38 - Thanks to FXJ !
   else return part_of->lookup(nm); }


// Get a symbol (even if none is there => create it) in the module with the given name,
// this is a combination of lookup + symbol::make(...)
// notice that we do not inherit junk (undefined) but rather create a new symbol
symbol *module::getSymbol(char *nm, module *def)
{symbol *cur = lookup(nm);
  if ((cur != NULL) &&
      ((cur->value != CNULL) || (cur->module_I == this) || (cur == Kernel.unknownName)))
     return cur;
  else return symbol::make(GC_STRING(copy_string(nm)),this,def); }   // v3.2.50

// create the module associated to a namespace (used by the compiler)
// assumes the existence of the claire module
void NameSpace::initModule(char *nom, module *father)
{it = module::make(nom,father);}

// similar but also fills the key slots for the module (compiler method)
// new status (0:default, 1:start, 2 compiled, 3:c+loaded, 4:c+l+trace, 5:c+delayed)
void NameSpace::initModule(char *nom, module *father, list* usage, char *dir, list *files)
{CL_INT i = 1;
  for(;i <= usage->length;i++) {
    if (OBJECT(ClaireAny,usage->content[i]) == NULL)
      Cerror(4, _string_(nom), 0);
  }
 it = module::make(nom,father);
 it->uses = usage;                 // other modules that are used
 it->source = dir;               // directory where the sources can be found
 it->made_of = files;
 it->comment = nom;
 it->status = 3;
  Kernel._module->instances->addFast(_oid_(it));
 father->parts->addFast(_oid_(it));   // manage the inverse
}

// --- API functions for modules ---------------------------------------------------

/* open a module x with module identifier index */
CL_EXPORT void begin_module (module *x)
{ ((list *) ClEnv->moduleStack)->addFast(_oid_(ClEnv->module_I));
  ClEnv->module_I = x;}

/* close an application */
CL_EXPORT void end_module (module *x)
{CL_INT n = ((bag *) ClEnv->moduleStack)->length;
  if (n == 0) ClEnv->module_I = claire.it;
  else {ClEnv->module_I = OBJECT(module,(*((bag *) ClEnv->moduleStack))[n]);
        delete_at_list(((list *) ClEnv->moduleStack),n);}}



/*********************************************************************/
/**    3. Symbols                                                    */
/*********************************************************************/

// to remove
CL_EXPORT void symbolDebug(symbol *s)
{CL_INT i = s->module_I->hash(s->name);
 symbol *test = ClRes->sTable[i];
 if (test != s) {
   printf("_____________________________________________\n");
#ifdef __LP64__
   printf("  symbol debug s = %lx\n",(CL_INT)s);
   printf("  string is [%s] (%ld)\n  module:%s\n",s->name, LENGTH_STRING(s->name), s->module_I->comment);
   printf("  position is %ld\n",i);
   printf("ClRes->sTable[%ld] -> %s/%s\n", i, test->module_I->name->name, test->name);
#else
   printf("  symbol debug s = %x\n",(CL_INT)s);
   printf("  string is [%s] (%d)\n  module:%s\n",s->name, LENGTH_STRING(s->name), s->module_I->comment);
   printf("  position is %d\n",i);
   printf("ClRes->sTable[%d] -> %s/%s\n", i, test->module_I->name->name, test->name);
#endif
   printf("!!!!!! problem with the table !!!!!!\n");
   printf("_____________________________________________\n");  }}
 


// -------------- member functions --------------------------------------------

// create a claire symbol from an internal C string and a status, represented by
// def, which is NULL for private symbols and the definition (owner) for other symbols
symbol *symbol::make(char *name, module *ns, module *def)
{CL_INT i = ns->hash(name);
   while ((ClRes->sTable[i] != NULL) &&
          ((ns != ClRes->sTable[i]->module_I) ||
           (equal_string(name,ClRes->sTable[i]->name) == CFALSE))) i++;
   if (i >= ClAlloc->maxHash)
       Cerror(12,0,0);
   if (ClRes->sTable[i] == NULL)
      {symbol *s = (symbol *) ClAlloc->makeAny(5);
       s->isa = Kernel._symbol;
       s->name = name;
       s->module_I = ns;
       s->definition = def;                  // def = NULL means private
       s->value = CNULL;
       ClRes->sTable[i] = s;}
   return ClRes->sTable[i];}

// read the value bound to a given symbol s. We create an unbound
//   symbol object if necessary
OID symbol::getValue()
{ if (value == CNULL && this != Kernel.unknownName)
     {unbound_symbol *o = (unbound_symbol *) Kernel._unbound_symbol->instantiate();
      o->name = this;
      return _oid_(o);}
  else return value;}


// --------------- API functions ---------------------------------------------

// create a symbol in the current module
CL_EXPORT symbol *symbol_I_string(char *s,module *m)
{return symbol::make(s,m,ClEnv->module_I);}

// writes the value of a symbol
CL_EXPORT OID put_symbol(symbol *s, OID x)
{s->value = x;
 return x;}

CL_EXPORT OID get_symbol(symbol *s) {return s->value;} //<sb> was {return ((s->value == CNULL) ? CNULL : s->value);}

// concatenate two symbols, or a symbol and a string or a symbol and an integer
// the result is a symbol in the module of the first symbol
CL_EXPORT symbol *append_symbol(symbol *s1, OID s2)
{ OID i;
  char *ss1 = s1->name;
  CL_INT len = LENGTH_STRING(ss1);
  ClEnv->bufferStart();
  for (i = 0; i < len; i++) ClEnv->pushChar(ss1[i]);
  if INTEGERP(s2) ClEnv->pushInteger(s2);
  else {if (OWNER(s2) == Kernel._symbol) ss1 = OBJECT(symbol,s2)->name;
        else if (OWNER(s2) == Kernel._string) ss1 = string_v(s2);
        else ss1 = "";
        CL_INT len = LENGTH_STRING(ss1);
        for (i = 0; i < len; i++) ClEnv->pushChar(ss1[i]);}
  return symbol::make(GC_STRING(ClEnv->bufferCopy()),s1->module_I,s1->definition); }

// print a symbol with its application name
CL_EXPORT void princ_symbol(symbol *s)
{ if ((s->module_I != claire.it) && (s->module_I != ClEnv->module_I))
     {princ_symbol(s->module_I->name); ClEnv->cout->put('/');}
  princ_string(s->name); }

// find the module where the object is defined
CL_EXPORT module *defined_symbol (symbol *s)
{ if (s->definition != NULL) return s->definition; else return s->module_I;}

CL_EXPORT module *module_I_symbol (symbol *s) {return s->module_I;}

CL_EXPORT char *string_I_symbol(symbol *s)
{return s->name;}

// create a new name
CL_EXPORT symbol *gensym_string (char *s)
{ ClEnv->bufferStart();
  CL_INT len = LENGTH_STRING(s);
  while(len--) ClEnv->pushChar(*s++);
  //for (; *s != '\0'; s++) ClEnv->pushChar(*s);
  ClEnv->pushChar('0' + ((char) ((ClEnv->gensym % 10000) / 1000)));
  ClEnv->pushChar('0' + ((char) ((ClEnv->gensym % 1000) / 100)));
  ClEnv->pushChar('0' + ((char) ((ClEnv->gensym % 100) / 10)));
  ClEnv->pushChar('0' + ((char) (ClEnv->gensym % 10)));
  ClEnv->gensym++;
  return claire.it->getSymbol(ClEnv->buffer,claire.it);}

// useful to represent a symbol with an integer
CL_EXPORT CL_INT integer_I_symbol (symbol *s)
{ CL_INT i = s->module_I->hash(s->name);
   while ((ClRes->sTable[i] != NULL) &&
          ((s->module_I != ClRes->sTable[i]->module_I) ||
           (equal_string(s->name,ClRes->sTable[i]->name) == CFALSE))) i++;
   return i;}


/*********************************************************************/
/**    4. integer & float API functions                              */
/*********************************************************************/


/*
void princ_integer(int i) {ClEnv->cout->put(i);}


// arithmetic functions
int ch_sign(int n)
{ return (-n) ;}

int _7_integer(int n, CL_INT m)
{ if (m == 0) Cerror(20,n,0); return (n / m);}

int mod_integer(int n, CL_INT m)
{ if (m == 0) Cerror(20,n,0); return (n % m);}

// v3.3.16: use float exponentiation and check overflow
int _exp_integer(int n, CL_INT m)
{double a = (double) n, b = (double) m,  c = pow(a,b);
  if (c < CLMINFLOAT || c > CLMAXFLOAT) Cerror(40,n,m);
  return (CL_INT) c; }

// return a power of 2
int exp2_integer(int n)
{if ((n >= 0) && (n <= 31)) return (1ul << n);
 else Cerror(19,0,0); return 1;}
*/

// translate a integer into a char - v3.2.44 : supports encoding both on (-255 -- 256) or (0 -- 511)
CL_EXPORT ClaireChar *char_I_integer(CL_INT n)
{if ((n < -1) || (n > 255)) Cerror(21,n,0);
 return ClRes->ascii[(unsigned char)n];}

// create a new string
CL_EXPORT char *string_I_integer (CL_INT n)
{ ClEnv->bufferStart();
  ClEnv->pushInteger(n);
  return ClEnv->bufferCopy();}

// allocate a list with n member equal to m */
CL_EXPORT char *make_string_integer(CL_INT n, ClaireChar *c)
{ if (n < 0) Cerror(22,n,0);
  char *s = ClAlloc->makeString(n);
  if(n) memset(s,c->ascii,n);
  return s; }

//<sb> allocate a string without an initializer
CL_EXPORT char *make_string_integer1(CL_INT n)
{ if (n < 0) Cerror(22,n,0);
  char *s = ClAlloc->makeString(n);
  return s; }

// create a string from a list (v3.0.44) - should have been there from day one !
// TODO: trap the error nicely
CL_EXPORT char *make_string_list(list *l)
{if (l->of != Kernel._char) Cerror(22,0,0);
 CL_INT i,n = l->length;
 char *s = ClAlloc->makeString(n);
 for (i = 0; i < n; i++) s[i] = (char) OBJECT(ClaireChar,(*(l))[i + 1])->ascii;
 return s; }

CL_EXPORT CL_INT times_integer(CL_INT n, CL_INT m)
{double a = (double) n, b = (double) m,  c = a * b;
  if (c < CLMINFLOAT || c > CLMAXFLOAT) Cerror(40,n,m);
  return n * m; }

// use C random generator
// v3.3.18: support long integer (> 16 bits) - v3.3.20 : use ALi's ideas to simplify

// v3.3.24 makes sure that rand() returns a > 0 number on all platforms
// v3.3.26 is even stronger, following Sylvain's suggestion
#define C_RAND() (rand() & 0x00007FFF)
#define C_RANDMAX (RAND_MAX & 0x0007FFF)

CL_EXPORT void random_I_void() {
  srand(time(NULL));
}

CL_EXPORT CL_INT random_integer(CL_INT n)
{if (n <= 1) return 0;
 else if (n <= 1000) return (C_RAND() % n);
 else if (n <= 30000) return ((C_RAND() * 16384 + (C_RAND() % 16383)) % n);
 else {double ratio = (double) n / (double) (C_RANDMAX + 1);
       double draw = (double) C_RAND() + ((double) C_RAND() / (double) C_RANDMAX);
       //printf("%g * %g = %g\n",draw,ratio, draw * ratio);
       return (CL_INT)floor(draw * ratio);}}

// print
CL_EXPORT void princ_int(CL_INT n) {ClEnv->cout->put(n);}

/*********************************************************************/
/**    5. floats                                                     */
/*********************************************************************/

// all API functions are doubled:
// op_float(...) returns a double  [float parameters are doubles]
// op_float_(...) returns an OID   [float parameters are OID]

/*
// makes an integer into a float
OID to_float_ (int n) {return _float_((double) n);}
double to_float (int n) {return  ((double) n);}

// create a  claire integer from a claire float
int integer_I_float_(OID n) {return integer_I_float(float_v(n));}
int integer_I_float(double n)
{ if (n < CLMINFLOAT || n > CLMAXFLOAT) Cerror(39,_float_(n),0);
  return _integer_((CL_INT) floor(n));}                         // v3.3

// the classical order comparisons for two float
ClaireBoolean *_inf_float(double n,double m)
{ if (n < m) return CTRUE;  else return CFALSE;}

ClaireBoolean *_inf_equal_float(double n,double m)
{ if (n <= m) return CTRUE;  else return CFALSE;}

ClaireBoolean *_sup_float(double n,double m)
{ if (n > m) return CTRUE;  else return CFALSE;}

ClaireBoolean *_sup_equal_float(double n,double m)
{ if (n >= m) return CTRUE;  else return CFALSE;}

ClaireBoolean *_inf_float_(OID n, OID m)
{ if (float_v(n) < float_v(m)) return CTRUE;  else return CFALSE;}

ClaireBoolean *_inf_equal_float_(OID n, OID m)
{ if (float_v(n) <= float_v(m)) return CTRUE;  else return CFALSE;}

ClaireBoolean *_sup_float_(OID n, OID m)
{ if (float_v(n) > float_v(m)) return CTRUE;  else return CFALSE;}

ClaireBoolean *_sup_equal_float_(OID n, OID m)
{ if (float_v(n) >= float_v(m)) return CTRUE;  else return CFALSE;}
*/

// printing
CL_EXPORT void princ_float(double x) {ClEnv->cout->prettyp(x);}            // v3.2.54
CL_EXPORT void princ_float_(OID x) {ClEnv->cout->prettyp(float_v(x));}     // v3.2.54

CL_EXPORT void print_float(double x) {ClEnv->cout->put(x);}            // v3.2.54
CL_EXPORT void print_float_(OID x) {ClEnv->cout->put(float_v(x));}     // v3.2.54


/***********************************************************************/
/**   microCLAIRE XL                                   Sylvain Benilan */
/**   clSystem.cpp                                                     */
/**  Copyright (C) 1998-2004 eXpert soLutions. All Rights Reserved.    */
/***********************************************************************/

// useful upper and lower bound to check overflow
double CL_EXPORT CLMAXFLOAT = 1073741823.0;              // v3.3.12
double CL_EXPORT CLMINFLOAT = -1073741822.0;

// this file contains the C++ code for system dependent API
// under unix we benefit of configuration (HAVE_XXX definitions)
// under Win32 we may have a specific code...

/*********************************************************************/
/** Contents                                                         */
/**    1. env/cwd/pid                                                */
/**    2. time/date                                                  */
/**    3. files system                                               */
/**    4. process                                                    */
/**    5. uname                                                      */
/**    6. string - case/digit test                                   */
/**    7. string - find/replace                                      */
/**    8. string - explode                                           */
/**    9. string - encoding/decoding (xl)                            */
/**    10. string - base64 encoding/decoding (xl)                    */
/*********************************************************************/



/*********************************************************************/
/**    1. env/cwd/pid                                                */
/*********************************************************************/

//<sb> funny terminal ding!
CL_EXPORT void ding_void() {putc('\x07',stdout);}

//<sb> setenv wrapper syntax : "var=val"
CL_EXPORT void setenv_string(char *v) {
#ifdef CLPC
  if(_putenv(v))
#else
#ifdef HAVE_SETENV
  char  var[256];
  char *pvar = var;
  while(*v && *v != '=') {
    *pvar = *v;
    pvar++;
    if (pvar - var == 256)
      Cerrorno(64,_string_(v),0);
    v++;
  }
  *pvar = '\0';
  v++;
  if(setenv(var,v,1))
#else
  CL_INT len = LENGTH_STRING(v);
  char *cp = (char*)malloc(len+1);
  if (cp == NULL)
    Cerrorno(64,_string_(v),0);
  memcpy(cp, v, len+1);
  if(putenv(cp))
#endif
#endif
  Cerrorno(64,_string_(v),0);
}

//<sb> sets the current working directory
CL_EXPORT void setcwd_string(char *s) {
#ifdef CLPC
  if (SetCurrentDirectory(s)==0)
#else
  if (chdir(s))
#endif
    Cerrorno(65,_string_(s),0);
}

//<sb> returns the current working directory
CL_EXPORT char *pwd_void() {
#ifdef CLPC
  char tmp[MAX_PATH + 1];
  if(GetCurrentDirectory(MAX_PATH + 1,tmp)==0)
#else
  char tmp[MAXPATHLEN + 1];
  if(getcwd(tmp, MAXPATHLEN + 1) == NULL)
#endif  
    Cerrorno(66,0,0);
  return copy_string(tmp);
}

#ifndef CLPC
  extern char **environ;
#endif

//<sb> get the amount of environment variable
CL_EXPORT CL_INT maxenv_void() {
  CL_INT p = -1;
  while(1)
  #ifdef CLPC
    if(_environ[++p] == NULL)
  #else
    if(environ[++p] == NULL)
  #endif
    break;
  return p; // 1 based index
}

//<sb> get the ith environment variable
CL_EXPORT char *environ_integer(CL_INT i) {
  char *entry;CL_INT p = 0;
  i--; // 1 based index
  if(i < 0) Cerror(67,_integer_((i+1)),0);
  for(;p <= i;p ++)
  #ifdef CLPC
    if(_environ[p] == NULL)
      Cerror(67,_integer_((i+1)),0);
    return copy_string(_environ[i]);
  #else
    if(environ[p] == NULL)
      Cerror(67,_integer_((i+1)),0);
    return copy_string(environ[i]);
  #endif
}

CL_EXPORT ClaireBoolean *isenv_ask_string(char* v) {
  return getenv(v)?CTRUE:CFALSE;
}

/*********************************************************************/
/**    2. time/date                                                  */
/*********************************************************************/

//<sb> sleep until ms has elapsed
CL_EXPORT void sleep_integer(CL_INT ms) {
#ifdef CLPC
  Sleep(ms);
#else
  timeval tv;
    tv.tv_sec = ms / 1000;
    tv.tv_usec = 1000 * (ms % 1000);
    select(1, NULL, NULL, NULL, &tv);
#endif
}

class TzSet {
public:
  char claire_tz[64];
  static TzSet single;
  TzSet() {claire_tz[0] = 0;
      /*setenv_string("TZ=");
      tzset();*/ }
};

TzSet TzSet::single = TzSet();

CL_EXPORT char *tzset_string(char* tz) {
  char tmp[256];
  strcpy(tmp,"TZ=");
  strcat(tmp,tz);
  setenv_string(tmp);
  tzset();
  return "";
}

CL_EXPORT void claire_tzset(CL_INT local) {
  /*char tmp[64];
  tmp[0] = 0;
  strcat(tmp,"TZ=");
  if (local)
    strcat(tmp, TzSet::single.claire_tz);
  setenv_string(tmp);
  tzset();*/
}

CL_EXPORT double timer_I_void() {
#ifdef CLPC
  struct _timeb tstruct;
  _ftime(&tstruct);
  return 0.001 * (double)tstruct.millitm + (double)tstruct.time;
#elif HAVE_GETTIMEOFDAY
  struct timeval tstruct;
  struct timezone tzone;
  gettimeofday(&tstruct,&tzone);
  return (double)0.000001 * (double)tstruct.tv_usec + (double)tstruct.tv_sec;
#elif HAVE_FTIME
  struct timeb tstruct;
  ftime(&tstruct);
  return 0.001 * (double)tstruct.millitm + (double)tstruct.time;
#else
  time_t t;
  time(&t); //<sb> assume no error will occur
  return (double)t;
#endif
}

CL_EXPORT OID timer_I_void_() {
  return _float_(timer_I_void());
}

#if !_LIBC
# define __environ  environ
extern char **environ;
#endif

void myunsetenv(const char *name)
{
  size_t len;
  char **ep;

  if (name == NULL || *name == '\0' || strchr (name, '=') != NULL) {
      return;
  }

  len = strlen (name);

  ep = __environ;
  while (*ep != NULL)
    if (!strncmp (*ep, name, len) && (*ep)[len] == '=') {
      /* Found it.  Remove this pointer by moving later ones back.  */
      char **dp = ep;
      do dp[0] = dp[1];
      while (*dp++);
      /* Continue the loop in case NAME appears again.  */
    } else {
      ++ep;
  }
  return;
}

//<sb> from linux manpage: the portable implementation of timegm
time_t my_timegm(struct tm *tm) {
  time_t ret;
  char *tz;
  tz = getenv("TZ");
  //setenv_string("TZ=");
  #ifdef CLPC
  setenv_string("TZ=");
  #else
  myunsetenv("TZ");
  #endif  
  tzset();
  ret = mktime(tm);
  if (tz) {
    char tmp[1024];
    tmp[0] = 0;
    strcat(tmp,"TZ=");
    strcat(tmp,tz);
    setenv_string(tmp);
  }
  tzset();
  return ret;
}

//<sb> mktime produced an error, we check that the given date
// isn't during a winter/summer time transition
CL_EXPORT void mktime_error(struct tm* atm) {
  atm->tm_isdst = -1;
  CL_INT dst_error;
  atm->tm_hour++;
  claire_tzset(1);
  dst_error = mktime(atm) != -1;
  if(dst_error) {
    atm->tm_hour--;
    atm->tm_hour--;
    //dst_error = mktime(atm) != -1;
    dst_error = mktime(atm) != -1;  
  }
  claire_tzset(0);
  if(dst_error) Cerror(90,0,0);
  else Cerror(70,0,0);
}


CL_EXPORT CL_INT elapsed_float(double t) {
  return _integer_((CL_INT)(1000.0 * (timer_I_void() - t)));
}

CL_EXPORT CL_INT elapsed_float_(OID t) {
  return elapsed_float(float_v(t));
}

CL_EXPORT char* setlocale_integer(CL_INT cat, char *loc) {
  CL_INT category;
  if(cat < 0 || cat > 5) Cerror(68,_integer_(cat),0);
  switch(cat) {
    case 0: category = LC_ALL; break;
    case 1: category = LC_COLLATE; break;
    case 2: category = LC_CTYPE; break;
    case 3: category = LC_MONETARY; break;
    case 4: category = LC_TIME; break;
    case 5: category = LC_NUMERIC; break;
  }
  char *res = setlocale(category ,loc);
  if(res == NULL)
    Cerror(69,_integer_(cat),_string_(loc));
  return copy_string(setlocale(category ,loc));
}

CL_EXPORT char* getlocale_integer(CL_INT cat) {
  CL_INT category;
  if(cat < 0 || cat > 5) Cerror(68,_integer_(cat),0);
  switch(cat) {
    case 0: category = LC_ALL; break;
    case 1: category = LC_COLLATE; break;
    case 2: category = LC_CTYPE; break;
    case 3: category = LC_MONETARY; break;
    case 4: category = LC_TIME; break;
    case 5: category = LC_NUMERIC; break;
  }
  char *res = setlocale(category ,NULL);
  if(res == NULL) Cerror(69,_integer_(cat),_string_(""));
  return copy_string(setlocale(category ,NULL));
}

//<sb> returns the date built with day month year hour minute second
CL_EXPORT double make_date_integer(CL_INT D, CL_INT M, CL_INT Y, CL_INT h, CL_INT m, CL_INT s) {
  struct tm atm;
  atm.tm_sec = s;
  atm.tm_min = m;
  atm.tm_hour = h;
  atm.tm_mday = D;
  atm.tm_mon = M - 1;     // tm_mon is 0 based
  atm.tm_year = Y - 1900; // tm_year is 1900 based
  atm.tm_isdst = -1; //1 - _daylight; //(dst==CTRUE?1:0);
/*
  char *tm_zone;  // abbreviation of timezone name
  long tm_gmtoff; // offset from UTC in seconds 
*/

  time_t t;
  claire_tzset(1);
  t = mktime(&atm);
  claire_tzset(0);
  if(t == -1) mktime_error(&atm);
  return (double)t;
}

CL_EXPORT OID make_date_integer_(CL_INT D, CL_INT M, CL_INT Y, CL_INT h, CL_INT m, CL_INT s) {
  return _float_(make_date_integer(D,M,Y,h,m,s));
}

//<sb> date parser
// "XXXX"     -> "XX/XX/y 0:0:00"
// "XXXXXX"   -> "XX/XX/XX 0:0:00"
// "XX/XX"    -> "XX/XX/y 0:0:00"
// "XX/XX/XX" -> "XX/XX/XX 0:0:00"
// "XX/XX/XX" -> "XX/XX/XXXX 0:0:00"
// where y is the current year
CL_EXPORT double make_date_string(char *self) {
  GC_BIND;
  double Result;
  CL_INT  y = 0;
  CL_INT  m = 0;
  CL_INT  d = 0;
  CL_INT H = 0;
  CL_INT M = 0;
  CL_INT S = 0;
  char sep = ' ';
  char offsetsign = ' ';
  CL_INT offset_val_h = 0;
  CL_INT offset_val_m = 0;
  char tz_name[16];
  char* old_tz = NULL;
  tz_name[0] = '\0';
  char month_name[4];

#ifdef __LP64__
//xp Sat, 10 Dec 2005 16:31:11 GMT ; RFC 1123, standard Internet Time, always in GMT 
  if (sscanf(self, "%*3[A-z], %ld %3[A-z] %ld %ld:%ld:%ld GMT", &d, month_name, &y, &H, &M, &S) == 6) { memcpy(tz_name,"UTC",4); /* XML Schema ISO 8601 extention : named timezone */ }
//xp Sunday, 06-Nov-94 08:49:37 GMT ; RFC 850, obsoleted by RFC 1036
else if (sscanf(self, "%*10[A-z], %ld-%3s-%ld %ld:%ld:%ld GMT", &d, month_name,&y, &H, &M, &S) == 6) { memcpy(tz_name,"UTC",4); /* XML Schema ISO 8601 extention : named timezone */ }
//xp Sun Nov 6 08:49:37 1994       ; ANSI C's asctime() format
else if (sscanf(self, "%*3[A-z] %3[A-z] %ld %ld:%ld:%ld %ld", month_name, &d, &H, &M, &S, &y) == 6) { memcpy(tz_name,"UTC",4); /* XML Schema ISO 8601 extention : named timezone */ }
/* ISO , xp add T seperator support and timezone */
else if (sscanf(self, "%ld-%ld-%ld%1[T ]%ld:%ld:%ld%1[-+]%2ld:%2ld", &y, &m, &d,&sep, &H, &M, &S, &offsetsign, &offset_val_h, &offset_val_m) == 10) { month_name[0] = '\0'; /* XML Schema ISO 8601 extention : named timezone */ }
  else if (sscanf(self, "%ld-%ld-%ld%1[T ]%ld:%ld:%ld%1[-+]%2ld%2ld", &y, &m, &d,&sep, &H, &M, &S, &offsetsign, &offset_val_h, &offset_val_m) == 10) { /* XML Schema ISO 8601 extention : named timezone */ }
else if (sscanf(self, "%ld-%ld-%ld%1[T ]%ld:%ld:%ld %1[-+]%2ld:%2ld", &y, &m, &d,&sep, &H, &M, &S, &offsetsign, &offset_val_h, &offset_val_m) == 10) { month_name[0] = '\0'; /* XML Schema ISO 8601 extention : named timezone */ }
  else if (sscanf(self, "%ld-%ld-%ld%1[T ]%ld:%ld:%ld %1[-+]%2ld%2ld", &y, &m, &d,&sep, &H, &M, &S, &offsetsign, &offset_val_h, &offset_val_m) == 10) { /* XML Schema ISO 8601 extention : named timezone */ }
  else if (sscanf(self, "%ld-%ld-%ld%1[T ]%ld:%ld:%ld%15s", &y, &m, &d,&sep, &H, &M, &S, tz_name ) == 8) { offset_val_h = 0; offset_val_m=0; offsetsign = ' '; /* XML Schema ISO 8601 extention : for named timezone */ }
  else if (sscanf(self, "%ld-%ld-%ld%1[T ]%ld:%ld:%ld", &y, &m, &d, &sep, &H, &M, &S) == 7) {tz_name[0] = '\0'; offset_val_h = 0; offset_val_m=0; offsetsign = ' '; }
  else if (sscanf(self, "%ld-%ld-%ld%1[T ]%ld:%ld", &y, &m, &d, &sep, &H, &M) == 6) {S = 0;}
/* human */
  else if (sscanf(self, "%ld/%ld/%ld%1[T ]%ld:%ld:%ld", &d, &m, &y, &sep, &H, &M, &S) == 7) {}
  else if (sscanf(self, "%ld/%ld/%ld%1[T ]%ld:%ld", &d, &m, &y, &sep, &H, &M) == 6) {S = 0;}
  else if (sscanf(self, "%ld/%ld/%ld", &d, &m, &y) == 3) {H = 0;M = 0;S = 0;}
  else if (sscanf(self, "%ld/%ld", &d, &m) == 3) {H = 0;M = 0;S = 0;}
  else if (sscanf(self, "%ld-%ld-%ld", &y, &m, &d) == 3) {H = 0;M = 0;S = 0;}
  else if (sscanf(self, "%ld:%ld:%ld", &H, &M, &S) == 3) {d = 1;m = 1;y = 1970;}
  else if (sscanf(self, "%ld:%ld", &H, &M) == 2) {d = 1;m = 1;y = 1970;S = 0;}

#else      
  //xp Sat, 10 Dec 2005 16:31:11 GMT ; RFC 1123, standard Internet Time, always in GMT 
    if (sscanf(self, "%*3[A-z], %d %3[A-z] %d %d:%d:%d GMT", &d, month_name, &y, &H, &M, &S) == 6) { memcpy(tz_name,"UTC",4); /* XML Schema ISO 8601 extention : named timezone */ }
  //xp Sunday, 06-Nov-94 08:49:37 GMT ; RFC 850, obsoleted by RFC 1036
  else if (sscanf(self, "%*10[A-z], %d-%3s-%d %d:%d:%d GMT", &d, month_name,&y, &H, &M, &S) == 6) { memcpy(tz_name,"UTC",4); /* XML Schema ISO 8601 extention : named timezone */ }
  //xp Sun Nov 6 08:49:37 1994       ; ANSI C's asctime() format
  else if (sscanf(self, "%*3[A-z] %3[A-z] %d %d:%d:%d %d", month_name, &d, &H, &M, &S, &y) == 6) { memcpy(tz_name,"UTC",4); /* XML Schema ISO 8601 extention : named timezone */ }
  /* ISO , xp add T seperator support and timezone */
  else if (sscanf(self, "%d-%d-%d%1[T ]%d:%d:%d%1[-+]%2d:%2d", &y, &m, &d,&sep, &H, &M, &S, &offsetsign, &offset_val_h, &offset_val_m) == 10) { month_name[0] = '\0'; /* XML Schema ISO 8601 extention : named timezone */ }
    else if (sscanf(self, "%d-%d-%d%1[T ]%d:%d:%d%1[-+]%2d%2d", &y, &m, &d,&sep, &H, &M, &S, &offsetsign, &offset_val_h, &offset_val_m) == 10) { /* XML Schema ISO 8601 extention : named timezone */ }
  else if (sscanf(self, "%d-%d-%d%1[T ]%d:%d:%d %1[-+]%2d:%2d", &y, &m, &d,&sep, &H, &M, &S, &offsetsign, &offset_val_h, &offset_val_m) == 10) { month_name[0] = '\0'; /* XML Schema ISO 8601 extention : named timezone */ }
    else if (sscanf(self, "%d-%d-%d%1[T ]%d:%d:%d %1[-+]%2d%2d", &y, &m, &d,&sep, &H, &M, &S, &offsetsign, &offset_val_h, &offset_val_m) == 10) { /* XML Schema ISO 8601 extention : named timezone */ }
    else if (sscanf(self, "%d-%d-%d%1[T ]%d:%d:%d%15s", &y, &m, &d,&sep, &H, &M, &S, tz_name ) == 8) { offset_val_h = 0; offset_val_m=0; offsetsign = ' '; /* XML Schema ISO 8601 extention : for named timezone */ }
    else if (sscanf(self, "%d-%d-%d%1[T ]%d:%d:%d", &y, &m, &d, &sep, &H, &M, &S) == 7) {tz_name[0] = '\0'; offset_val_h = 0; offset_val_m=0; offsetsign = ' '; }
    else if (sscanf(self, "%d-%d-%d%1[T ]%d:%d", &y, &m, &d, &sep, &H, &M) == 6) {S = 0;}
  /* human */
    else if (sscanf(self, "%d/%d/%d%1[T ]%d:%d:%d", &d, &m, &y, &sep, &H, &M, &S) == 7) {}
    else if (sscanf(self, "%d/%d/%d%1[T ]%d:%d", &d, &m, &y, &sep, &H, &M) == 6) {S = 0;}
    else if (sscanf(self, "%d/%d/%d", &d, &m, &y) == 3) {H = 0;M = 0;S = 0;}
    else if (sscanf(self, "%d/%d", &d, &m) == 3) {H = 0;M = 0;S = 0;}
    else if (sscanf(self, "%d-%d-%d", &y, &m, &d) == 3) {H = 0;M = 0;S = 0;}
    else if (sscanf(self, "%d:%d:%d", &H, &M, &S) == 3) {d = 1;m = 1;y = 1970;}
    else if (sscanf(self, "%d:%d", &H, &M) == 2) {d = 1;m = 1;y = 1970;S = 0;}
#endif
    else {
    struct tm *atm;
    time_t t = (time_t)now_void();  
    claire_tzset(1);
    atm = localtime(&t);
    claire_tzset(0);
    if(atm == 0) Cerror(70,0,0);
    CL_INT len = strlen(self);
    y = atm->tm_year + 1900;
    H = 0;M = 0;S = 0;
    if (4 <= len)
    { d= integer_I_string(substring_string(self,1,2));
    m = integer_I_string(substring_string(self,3,4));
    } 
    if (6 <= len)
    y = integer_I_string(substring_string(self,5,strlen(self))); 
  }
  
  if (y < 70) y= (y+2000);
  else if (y < 100) y= (y+1900);

  //xp: month name check
  if (m == 0 && strlen(month_name) > 0)
  {
    if (strcmp(month_name,"Jan") == 0) { m = 1; }
    else if (strcmp(month_name,"Feb") == 0) { m = 2; }
    else if (strcmp(month_name,"Mar") == 0) { m = 3; }
    else if (strcmp(month_name,"Apr") == 0) { m = 4; }
    else if (strcmp(month_name,"May") == 0) { m = 5; }
    else if (strcmp(month_name,"Jun") == 0) { m = 6; }
    else if (strcmp(month_name,"Jul") == 0) { m = 7; }
    else if (strcmp(month_name,"Aug") == 0) { m = 8; }
    else if (strcmp(month_name,"Sep") == 0) { m = 9; }
    else if (strcmp(month_name,"Oct") == 0) { m = 10; }
    else if (strcmp(month_name,"Nov") == 0) { m = 11; }
    else m = 12;
  }

  //xp: timezone support
  if (offsetsign == '-')
  {
    // negative offset
    old_tz = tzset_string("UTC");
    H += offset_val_h;
    M += offset_val_m;
  } else if (offsetsign == '+')
  {
    // positive offset
    old_tz = tzset_string("UTC");
    H -= offset_val_h;
    M -= offset_val_m;
  } else if (strlen(tz_name)  > 0)
  {
    // custom time zone
    old_tz = tzset_string(tz_name);
  }
  
  Result = make_date_integer(d,m,y,H,M,S);

  //xp back to previously defined timezone if needed
  if (old_tz != NULL) tzset_string(old_tz);

    GC_UNBIND;
    return (Result);
}

CL_EXPORT OID make_date_string_(char *self) {
  return _float_(make_date_string(self));
}

//<sb> time parser
// "XX"    -> "0:XX:00"
// "XXX"   -> "X:XX:00"
// "XX:X"  -> "XX:0X:00"
// "XX:XX" -> "XX:XX:00"
CL_EXPORT double make_time_string(char *self) {
  GC_BIND;
  struct tm atm; // set to January 1, 1970
  atm.tm_isdst = 0;
  atm.tm_year = 70;
  atm.tm_mon = 0;
  atm.tm_mday = 1;
  atm.tm_min = 0;
    atm.tm_sec = 0;
    if (occurrence_string(self,":") == 0)
       atm.tm_hour = integer_I_string(self);
  else if (occurrence_string(self,":") == 1)
       { list * l = GC_OBJECT(list,explode_string(self,":"));
        atm.tm_hour = (*Kernel.integer_I)((*(l))[1]);
        atm.tm_min = (*Kernel.integer_I)((*(l))[2]);
        }
  else if (occurrence_string(self,":") == 2)
       { list * l = GC_OBJECT(list,explode_string(self,":"));
        atm.tm_hour = (*Kernel.integer_I)((*(l))[1]);
        atm.tm_min = (*Kernel.integer_I)((*(l))[2]);
        atm.tm_sec = (*Kernel.integer_I)((*(l))[3]);
       }
    time_t t;
    t = mktime(&atm);
  if(t == -1) mktime_error(&atm);
    GC_UNBIND;
    return (double)t; 
}

CL_EXPORT OID make_time_string_(char *self) {
  return _float_(make_time_string(self));
}

CL_EXPORT double make_time_integer(CL_INT h, CL_INT m, CL_INT s) {
  struct tm atm; // set to January 1, 1970
  atm.tm_isdst = 0;
  atm.tm_year = 70;
  atm.tm_mon = 0;
  atm.tm_mday = 1;
  atm.tm_hour = h;
  atm.tm_min = m;
    atm.tm_sec = s;
    time_t t;
    t = mktime(&atm);
  if(t == -1) mktime_error(&atm);
    return (double)t; 
} 

CL_EXPORT OID make_time_integer_(CL_INT h, CL_INT m, CL_INT s) {
  return _float_(make_time_integer(h,m,s));
}

//<sb> how to add some units on a date/time component
CL_EXPORT double date_add_float(double self, ClaireChar *what, CL_INT inc) {
  struct tm *atm;
  time_t t = (time_t)self;
  claire_tzset(1);
    atm = localtime(&t);
  claire_tzset(0);
    if(atm == 0) Cerror(70,0,0);
    atm->tm_isdst = -1;
  switch(what->ascii) {
      case 'H':
      case 'h':
        atm->tm_hour += inc; break;
      case 'M':
        atm->tm_min += inc; break;
      case 'S':
      case 's':
        atm->tm_sec += inc; break;
      case 'd':
      case 'D':
        atm->tm_mday += inc; break;
      case 'm':
        atm->tm_mon += inc; break;
      case 'Y':
      case 'y':
        atm->tm_year += inc;
    }
    t = mktime(atm);
  if(t == -1) mktime_error(atm);
  return (double)t;
}
CL_EXPORT OID date_add_float_(OID self, ClaireChar *what, CL_INT inc) {
  return _float_(date_add_float(float_v(self),what,inc));
}

//<sb> wrapper for the C strftime - see man
CL_EXPORT char *strftime_string(char* format, double t) {
  ClEnv->bufferStart();
  CL_INT maxlen = 1024 + LENGTH_STRING(format);
  ClEnv->pushAttempt(maxlen);
  struct tm *atm;
  time_t long_time = (time_t)t;  
    //atm = localtime(&long_time);
  claire_tzset(1);
    atm = localtime(&long_time);
  claire_tzset(0);
    if(atm == 0) Cerror(70,0,0);
  claire_tzset(1);
    CL_INT n = strftime(ClEnv->buffer, maxlen, format, atm);
  claire_tzset(0);
    if (n == 0) Cerror(16,0,0);
    else ClEnv->bLength = n;
    return ClEnv->bufferCopy();
}

CL_EXPORT char *strftime_string_(char* format, OID t) {
  return strftime_string(format,float_v(t));
}

//<sb> return the time difference in second
CL_EXPORT double diff_time_float(double t1, double t2) {
  return difftime((time_t)t1,(time_t)t2);
}
CL_EXPORT OID diff_time_float_(OID t1, OID t2) {
  return _float_(diff_time_float(float_v(t1),float_v(t2)));
}

CL_EXPORT tuple* explode_float(double self) {
  struct tm *atm;
  time_t t = (time_t)self;
  claire_tzset(1);
    atm = localtime(&t);
  claire_tzset(0);
  if(atm == 0) Cerror(70,0,0);
  tuple *result;
  result = tuple::alloc(9, atm->tm_year + 1900, atm->tm_mon + 1,
                                atm->tm_yday + 1, atm->tm_mday, atm->tm_wday + 1,
                                atm->tm_hour, atm->tm_min, atm->tm_sec,
                                atm->tm_isdst?Kernel.ctrue:Kernel.cfalse);
  return result;
}

CL_EXPORT tuple* explode_float_(OID t) {
  return explode_float(float_v(t))->copyIfNeeded();
}



//<sb> the current date/time
CL_EXPORT double now_void() {
  time_t t;
  time(&t); //<sb> assume no error will occur
  return (double)t;
}

CL_EXPORT OID now_void_() {
  return _float_(now_void());
}

//<sb> prints the elapsed time since t
CL_EXPORT void uptime_float(double t) {
  char buf[100];
  CL_INT printask = 0;
  double msec = 1000.0 * (timer_I_void() - t);
  CL_INT neg = msec < 0.0;
  if(neg) msec = -msec;
  if (msec < 0) msec = -msec;    
  CL_INT days = (CL_INT)(msec / 86400000.0);
  if(days) {
    sprintf(buf,"%s%dd",(neg?"-":""),days);
    princ_string(buf);
    printask = 1;
  }
  msec = msec - (double)(86400000 * days);
  CL_INT hours = (CL_INT)(msec / 3600000.0);
  if(hours || printask) {
    sprintf(buf,"%s%s%dh",printask?" ":"", (neg?"-":""),hours);
    princ_string(buf);
    printask = 1;
  }
  msec = msec - (double)(3600000 * hours);
  CL_INT mins = (CL_INT)(msec / 60000.0);
  if(mins || printask) {
    sprintf(buf,"%s%s%dm",printask?" ":"", (neg?"-":""),mins);
    princ_string(buf);
    printask = 1;
  }
  msec = msec - (double)(60000 * mins);
  CL_INT sec = (CL_INT)(msec / 1000.0);
  if(sec || printask) {
    sprintf(buf,"%s%s%ds",printask?" ":"", (neg?"-":""),sec);
    princ_string(buf);
    printask = 1;
  }
  msec = msec - (double)(1000 * sec);
  sprintf(buf,"%s%s%dms",printask?" ":"",(neg?"-":""),(CL_INT)msec);
  princ_string(buf);
  }

CL_EXPORT void uptime_float_(OID t) {
  uptime_float(float_v(t));
}

//<sb> return a unique string (26 bytes length)
// based on process birth [date][random number][pid]
CL_EXPORT char* uid_void() {
  static double T0 = 0.0;
  if (T0 == 0.0) T0 = now_void();
  T0 += 1.0;
  char tmp[30];
  char *tmp2;
  char UID[30] = "";
  tmp2 = (char*)tmp;
  sprintf(tmp, "%08.0f", T0);
  while(strlen(tmp2) > 8) tmp2++;
  strcat(UID,tmp2);
  tmp2 = (char*)tmp;
  sprintf(tmp, "%08.0f", now_void());
  while(strlen(tmp2) > 8) tmp2++;
  strcat(UID,tmp2);
  tmp2 = (char*)tmp;
  sprintf(tmp, "%05.0f", (double)getpid_void());
  while(strlen(tmp2) > 5) tmp2++;
  strcat(UID,tmp2);
  tmp2 = (char*)tmp;
  sprintf(tmp, "%05.0f", (double)rand());
  while(strlen(tmp2) > 5) tmp2++;
  strcat(UID,tmp2);
  return copy_string(UID);
}

/*********************************************************************/
/**    3. files system                                               */
/*********************************************************************/

//<sb> simple wilcard parser
// understand following special chars :
//    *  : any sequence of char
//    ?  : any char
//    #<char>  : '<char>'      how to escape a char
static CL_INT match_wildcard_ask_string_impl(char* src, CL_INT lensrc, char* w, CL_INT lenw) {
  if(lensrc == 0 && lenw == 0) return 1;
  if(lenw == 0) return 0;
  if(*w == '#') {
    if(*src != w[1])
      return 0;
    return match_wildcard_ask_string_impl(src + 1, lensrc - 1, w + 2, lenw - 2);
  }
  if(*w == '*') {
    if(lenw == 1) return 1;
    if(lensrc == 0) return 0;
    if (w[1] == '#')
      return (match_wildcard_ask_string_impl(src, lensrc, w + 1, lenw - 1) ||
          match_wildcard_ask_string_impl(src + 1, lensrc - 1, w, lenw));
    if(w[1] == *src)
      return (match_wildcard_ask_string_impl(src + 1, lensrc - 1, w + 2, lenw - 2) ||
          match_wildcard_ask_string_impl(src + 1, lensrc - 1, w, lenw));
    return match_wildcard_ask_string_impl(src + 1, lensrc - 1, w, lenw);
  }
  else if(lensrc == 0) return 0;
  else if(*w == '?') return match_wildcard_ask_string_impl(src + 1, lensrc - 1, w + 1, lenw - 1);
  if(*src != *w) return 0;
  else return match_wildcard_ask_string_impl(src + 1, lensrc - 1, w + 1, lenw - 1);
}

CL_EXPORT ClaireBoolean *match_wildcard_ask_string(char* src, char* w) {
  return match_wildcard_ask_string_impl(src, LENGTH_STRING(src), w, LENGTH_STRING(w)) ?
        CTRUE : CFALSE;
}



char *exw[32];
CL_INT iexw;

static CL_INT explode_wildcard_string_impl(char* src, CL_INT lensrc, char* w, CL_INT lenw, CL_INT sp);
static CL_INT explode_wildcard_string_impl0(char* src, CL_INT lensrc, char* w, CL_INT lenw, CL_INT sp) {
  if (iexw >= 30)
    Cerror(74, _string_("Too many wilcard chars for explode_wildcard"), 0);
  CL_INT old = iexw;
  CL_INT special = (*w == '?' | *w == '*');
  if (sp && !special) //<sb> leave a special char
    exw[iexw++] = src;
  if (!sp && special) //<sb> enter a special char
    exw[iexw++] = src;  
  if(!explode_wildcard_string_impl(src, lensrc, w, lenw, special)) {
    iexw = old;
    return 0;
  }
  return 1;
}

static CL_INT explode_wildcard_string_impl(char* src, CL_INT lensrc, char* w, CL_INT lenw, CL_INT sp) {
  if(lensrc == 0 && lenw == 0) return 1;
  if(lenw == 0) return 0;
  if(*w == '#') {
    if(*src != w[1])
      return 0;
    return explode_wildcard_string_impl0(src + 1, lensrc - 1, w + 2, lenw - 2, 0);
  }
  if(*w == '*') {
    if(lenw == 1) return 1;
    if(lensrc == 0) return 0;
    if (w[1] == '#')
      return (explode_wildcard_string_impl0(src, lensrc, w + 1, lenw - 1, 1) ||
          explode_wildcard_string_impl0(src + 1, lensrc - 1, w, lenw, 1));
    if(w[1] == *src)
      return (explode_wildcard_string_impl0(src, lensrc, w + 1, lenw - 1, 1) ||
          explode_wildcard_string_impl0(src + 1, lensrc - 1, w, lenw, 1));
    return explode_wildcard_string_impl(src + 1, lensrc - 1, w, lenw, sp);
  }
  else if(lensrc == 0) return 0;
  else if(*w == '?') return explode_wildcard_string_impl0(src + 1, lensrc - 1, w + 1, lenw - 1, 1);
  if(*src != *w) return 0;
  else return explode_wildcard_string_impl0(src + 1, lensrc - 1, w + 1, lenw - 1, 0);
}


CL_EXPORT list *explode_wildcard_string(char* src, char* w) {
  iexw = 0;
  if (explode_wildcard_string_impl0(src, LENGTH_STRING(src), w, LENGTH_STRING(w), 0)
      && iexw % 2) //<sb> the end of string is missing (e.g wildcard terminated by *)
    exw[iexw++] = src + LENGTH_STRING(src);
  if (iexw > 0) {
    CL_INT i = 0;
    list *res = make_list_type1(Kernel._string, iexw / 2);
    for(;i < iexw;i++) {
      char *match = exw[i];
      CL_INT len = exw[++i] - match;
      res->content[++res->length] = _string_(GC_STRING(copy_string1(match, len)));
    }
    return res;
  }
  return Kernel.nil; //<sb> no match
}
  



//<sb>
// returns the list of the given directory entries
// that match the wilcard filter
// but . and ..
CL_EXPORT list *entries_string1(char *self,char *wild) {
  GC_RESERVE(1); 
  list * l = list::empty(Kernel._string);
  OID gc_local;
#ifdef CLPC
  WIN32_FIND_DATA wfd;
  HANDLE hFind = FindFirstFile(GC_STRING(append_string(self,"/*")), &wfd);
  if (hFind != INVALID_HANDLE_VALUE) {
    do { GC_LOOP;
      if(strcmp(wfd.cFileName,".") && strcmp(wfd.cFileName,"..") &&
        (wild == 0 || match_wildcard_ask_string(wfd.cFileName,wild) == CTRUE)) {
        GC__ANY(l = l->addFast(GC_OID(_string_(copy_string(wfd.cFileName)))), 1); 
      } GC_UNLOOP;
    } while (FindNextFile(hFind, &wfd));
    FindClose(hFind);
  }
#else
  DIR* fd = opendir(self);
  struct dirent* dp;
  if(fd) {
    while((dp = readdir(fd))) {
       GC_LOOP;
      if(strcmp(dp->d_name,".") && strcmp(dp->d_name,"..") &&
        (wild == 0 || match_wildcard_ask_string(dp->d_name,wild) == CTRUE)) {
        GC__ANY(l = l->addFast(GC_OID(_string_(copy_string(dp->d_name)))), 1); 
      }
      GC_UNLOOP;
    }
    closedir(fd);
  }
#endif
  else if(wild) Cerrorno(72,_string_(self),_string_(wild));
  else Cerrorno(73,_string_(self),0);
  GC_UNBIND;
  return l;
}

//<sb>
// returns a matching entry in the given directory
CL_EXPORT char *entry_string1(char *self,char *wild) {
  char *res = NULL;
#ifdef CLPC
  WIN32_FIND_DATA wfd;
  HANDLE hFind = FindFirstFile(GC_STRING(append_string(self,"/*")), &wfd);
  if (hFind != INVALID_HANDLE_VALUE) {
    do {
      if((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 && strcmp(wfd.cFileName,".") && strcmp(wfd.cFileName,"..") &&
        (wild == 0 || match_wildcard_ask_string(wfd.cFileName,wild) == CTRUE)) {
        res = copy_string(wfd.cFileName); 
        break;
      }
    } while (FindNextFile(hFind, &wfd));
    FindClose(hFind);
  }
#else
  DIR* fd = opendir(self);
  struct dirent* dp;
  char path[8192];
  CL_INT isdir = 1;
  struct stat sb;
  if(fd) {
    while((dp = readdir(fd))) {
      strcpy(path, self);
      strcat(path,"/");
      strcat(path,dp->d_name);
      isdir = 1;
      if(stat(path, &sb) != -1) {
        isdir = ((sb.st_mode) & S_IFMT) == S_IFDIR;
      }
      if(!isdir && strcmp(dp->d_name,".") && strcmp(dp->d_name,"..") &&
        (wild == 0 || match_wildcard_ask_string(dp->d_name,wild) == CTRUE)) {
        res = copy_string(dp->d_name);
        break;
      }
    }
    closedir(fd);
  }
#endif
  else if(wild) Cerrorno(72,_string_(self),_string_(wild));
  else Cerrorno(73,_string_(self),0);
  if (res == NULL) res = copy_string("");
  return res;
}


//<sb> returns the list of all entries of the given directory
// but . and ..
CL_EXPORT list *entries_string2(char *self) {
  return entries_string1(self,0); }

//<sb> check if the given entry is a file
// in case of error we return false
CL_EXPORT ClaireBoolean *isfile_ask_string(char *self) {
  CL_INT isdir = 1;
  struct stat sb;
  if(stat(self, &sb) != -1) {
    isdir = ((sb.st_mode) & S_IFMT) == S_IFDIR;
  }
  return isdir?CFALSE:CTRUE;
}

//<sb> check if the given entry is a directory
// in case of error we return false
CL_EXPORT ClaireBoolean *isdir_ask_string(char *self) {
  CL_INT isdir = 0; 
#ifdef CLPC
  char buf[MAX_PATH];
  strcpy(buf, self);
  CL_INT len = length_string(self);
  CL_INT minlen = 0;
  if (len >= 3 && self[1] == ':') minlen = 3;
  while (len > minlen && (buf[len-1] == '/' || buf[len-1] == '\\')) len--;
  buf[len] = '\0';
  self = buf;
#endif
  struct stat sb;
  if(stat(self, &sb) != -1) {
    isdir = ((sb.st_mode) & S_IFMT) == S_IFDIR;
  }
  return isdir?CTRUE:CFALSE;
}

//<sb> copy a file byte per byte
// sets mode of the copy to the source mode
CL_EXPORT void fcopy_string(char *self, char *trg) {
  CL_INT mode = 0;
  char buf[1024];
  struct stat sb;
  if(stat(self, &sb) == -1) Cerrorno(91,_string_(self),_string_("fcopy"));
  mode = sb.st_mode;
  CL_INT f = open(self, O_RDONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);  
  if(f == -1) Cerrorno(36,_string_(self),0);
  CL_INT t = open(trg, O_WRONLY|O_APPEND|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
  if(t == -1) {
    ::close(f);
    Cerrorno(36,_string_(trg),0);
  }
	#ifdef CLPC
		_setmode(f, _O_BINARY);
		_setmode(t, _O_BINARY);
	#endif
  while(1) {
    CL_INT n = read(f, buf, 1024);
    if(n == -1) {
      ::close(f);
      ::close(t);
      Cerrorno(84,_string_(self),_string_(trg));
    }
    if(n == 0) break;
    n = ::write(t, buf, n);
    if(n == -1) {
      ::close(f);
      ::close(t);
      Cerrorno(84,_string_(self),_string_(trg));
    }
  }
  ::close(f);
  ::close(t);
  if(chmod(trg, (mode_t)mode) == -1) { //<sb> copy source mode
    Cerrorno(81,_string_(trg),_integer_(mode));
  }
}

//<sb> unlink the given file
CL_EXPORT void unlink_string(char *self) {
  if(unlink(self))
    Cerrorno(78, _string_(self),0);
}

//<sb> create a hard link on a file
CL_EXPORT void link_string(char *name1, char *name2) {
  #ifdef CLPC
  if(0)
  #else
  if(link(name1,name2) == -1)
  #endif
    Cerrorno(82, _string_(name1),_string_(name2));
}

//<sb> create a symbolic link on a file
CL_EXPORT void symlink_string(char *name1, char *name2) {
  #ifdef CLPC
  if(0) //<sb> not supported
  #else
  if(symlink(name1,name2) == -1)
  #endif
    Cerrorno(83, _string_(name1),_string_(name2));
}

//<sb> moves a file
CL_EXPORT void fmove_string(char *name1, char *name2) {
  #ifdef CLPC
  if(!MoveFile(name1,name2))
    Cerrorno(99, _string_(name1),_string_(name2));
  #else
  if (isfile_ask_string(name2) == CTRUE)
    Cerrorno(99, _string_(name1),_string_(name2));
  if(rename(name1, name2) != 0)
    Cerrorno(99, _string_(name1),_string_(name2));
  #endif
}

//<sb> create a new directory with a given mode
CL_EXPORT void mkdir_string1(char *self, CL_INT mode) {
  #ifdef CLPC
  if(_mkdir(self))
  #else
  if(mkdir(self,(mode_t)mode))
  #endif
    Cerrorno(79, _string_(self),_integer_(mode));
}

//<sb> create a new directory with mode 0o777
CL_EXPORT void mkdir_string2(char *self) {
  #ifdef CLPC
  mkdir_string1(self,0);
  #else
  mkdir_string1(self,511);
  #endif
}

//<sb> remove a directory expected to be empty
CL_EXPORT void rmdir_string(char *self) {
  if(rmdir(self))
    Cerrorno(80, _string_(self),0);
}

//<sb> change file mode
// not really PC proof
CL_EXPORT void chmod_string(char *self, CL_INT mode) {
  if(chmod(self, (mode_t)mode) == -1)
    Cerrorno(81,_string_(self),_integer_(mode));
}

//<sb> request file size (use float because of integer size limitation...)
CL_EXPORT double fsize_string(char* self) {
  double len = 0.0;
  struct stat sb;
  if(stat(self, &sb) != -1) len = (double)sb.st_size;
  else Cerrorno(91,_string_(self),_string_("fsize"));
  return len;
}

CL_EXPORT OID fsize_string_(char* self) {
  return _float_(fsize_string(self));
}


//<sb> get the time of last change of the given file
CL_EXPORT double fchanged_string(char *self) {
  double t;
  struct stat sb;
  if(stat(self, &sb) != -1)
    t = (double)sb.st_ctime;
  else Cerrorno(91,_string_(self), _string_("fcreated"));
  return t;}

CL_EXPORT OID fchanged_string_(char *self) {
  return _float_(fchanged_string(self));
}

//<sb> get modfication/change time of the given file
CL_EXPORT double fmodified_string(char *self) {
  double t;
  struct stat sb;
  if(stat(self, &sb) != -1)
    t = (double)sb.st_mtime;
  else Cerrorno(91,_string_(self), _string_("fmodified"));
  return t;}

CL_EXPORT OID fmodified_string_(char *self) {
  return _float_(fmodified_string(self));
}

//<sb> get last accessed time of the given file
CL_EXPORT double faccessed_string(char *self) {
  double t;
  struct stat sb;
  if(stat(self, &sb) != -1)
    t = (double)sb.st_atime;
  else Cerrorno(91,_string_(self), _string_("faccessed"));
  return t;
}

CL_EXPORT OID faccessed_string_(char *self) {
  return _float_(faccessed_string(self));
}

//<sb> get a file mode
CL_EXPORT CL_INT fmode_string(char *self) {
  CL_INT mode;
  struct stat sb;
  if(stat(self, &sb) != -1) {
    mode = (CL_INT)sb.st_mode;
  }
  else Cerrorno(91,_string_(self), _string_("fmode"));
  return mode;
}

#ifdef CLPC
// on PC we need to initialize "_" env var
// with the path to the file used to create the current process
class InitUnderscore {
public:
  static InitUnderscore single;
  InitUnderscore() {
    char buf[1024];
    strcpy(buf,"_=");
    GetModuleFileName(NULL,buf+2,1022);
    _putenv(buf);
  }
};
InitUnderscore InitUnderscore::single = InitUnderscore();
#endif

CL_EXPORT char* realpath_string(char* self) {
  #ifdef CLPC
  char  res[4096];
  char *truc;
  if (GetFullPathName(self, sizeof(res), res, &truc) ==  0)
    Cerrorno(91,_string_(self), _string_("realpath"));
    return copy_string(res);
  #else
  char buf[MAXPATHLEN];
  char *res = realpath(self,buf);
  if(res == 0) Cerrorno(91,_string_(self), _string_("realpath"));
  return copy_string(res);
  #endif
}

/*********************************************************************/
/**    4. process                                                    */
/*********************************************************************/

CL_EXPORT CL_INT isforked = 0;
CL_EXPORT CL_INT lastforked = 0;

//<sb> get my pid
CL_EXPORT CL_INT getpid_void() {
#ifdef CLPC
  return (CL_INT)GetCurrentProcessId();
#else
  return (CL_INT)getpid();
#endif
}

//<sb> get my uid
CL_EXPORT CL_INT getuid_void() {
#ifdef CLPC
  return (CL_INT)0;
#else
  return (CL_INT)getuid();
#endif
}

//<sb> get parent process id
CL_EXPORT CL_INT getppid_void() {
#if defined(CLPC) || !defined(HAVE_GETPPID)
	return 0; // not _getpid or whatever
	          // parent process id has no meaning under windows
#else
  return (CL_INT)getppid();
#endif
}

#if !defined(CLPC)
static inline CL_INT process_run(CL_INT p) {
  CL_INT res = 0;
  #ifdef HAVE_GETPRIORITY
  errno = 0;
  getpriority(PRIO_PROCESS,p);
  if(errno) res = -1;
  #else
    #ifdef HAVE_GETSID
    res = (CL_INT)getsid(p);
    #else
    Cerror(75,_string_("getsid"),0);
    #endif
  #endif
  return res;
}

static inline void ensure_no_zombie(CL_INT process) {
  int status;
  waitpid((int)process,  &status, WNOHANG|WUNTRACED);
}
#endif

//<sb> kill (brutal if needed) the given process
CL_EXPORT void kill_integer1(CL_INT process) {
#ifdef CLPC
  HANDLE h = OpenProcess(PROCESS_TERMINATE, 0, process);
  if(h) {
    TerminateProcess(h, 0);
    CloseHandle(h);
  } else Cerrorno(76,_integer_(process),0);
#else
  CL_INT tried = 5;
    // give it a chance to gracefully exit
    if(kill(process, SIGTERM)==-1) Cerrorno(86,process,_string_("SIGTERM"));
    while(process_run(process) >= 0 && tried--) {
      ensure_no_zombie(process);
    sleep_integer(100);
  }
    // well, try to really kill it without advertising
    if (process_run(process) >= 0) {
        if(kill(process, SIGKILL) == -1)
          Cerrorno(86,process,_string_("SIGKILL"));
    ensure_no_zombie(process);
      while(process_run(process) >= 0) {
      ensure_no_zombie(process);
            sleep_integer(100);
    }
    }
#endif  
}

//<sb> test if the given process is running
CL_EXPORT ClaireBoolean* run_ask_integer(CL_INT pr) {
  if(getpid_void() == pr) return CTRUE; //<sb> am I running ?
#ifdef CLPC
  HANDLE h = OpenProcess(SYNCHRONIZE, 0, pr);
  if(h) {
    ClaireBoolean *res = CTRUE;
    if (WaitForSingleObject(h, 0) == WAIT_OBJECT_0)
      res = CFALSE;
    CloseHandle(h);
    return res;
  }
  else return CFALSE;
#else
    return process_run(pr) >= 0 ? CTRUE : CFALSE;
#endif  
}

//<sb> wait for termination of the given process
// returns true as soon as the given process terminates
// and false if timeout (ms) reached
CL_EXPORT ClaireBoolean* wait_integer1(CL_INT pr, CL_INT ms) {
#ifdef CLPC
  HANDLE h = OpenProcess(SYNCHRONIZE, 0, pr);
  if(h) {
    CL_INT res = WaitForSingleObject(h, ms) == WAIT_OBJECT_0;
    CloseHandle(h);
    return res ? CTRUE : CFALSE;
  }
  else return CFALSE;
#else
  timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 10000;
    while(process_run(pr) >= 0)
      { select(1, NULL, NULL, NULL, &tv);
        if((ms -= 10) <= 0) return CFALSE; }
  return CTRUE;
#endif
  
}

//<sb> wait for termination of the given process
CL_EXPORT void wait_integer2(CL_INT pr) {
#ifdef CLPC
  HANDLE h = OpenProcess(SYNCHRONIZE, 0, pr);
  if(h) {
    WaitForSingleObject(h, INFINITE);
    CloseHandle(h);
  }
  else Cerrorno(76,_integer_(pr),0);
#else
  timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 10000;
  while(process_run(pr) >= 0)
    select(1, NULL, NULL, NULL, &tv);
#endif
}

#ifndef CLPC
#ifndef WEXITSTATUS
# define WEXITSTATUS(stat_val) ((CL_UNSIGNED)(stat_val) >> 8)
#endif
#ifndef WIFEXITED
# define WIFEXITED(stat_val) (((stat_val) & 255) == 0)
#endif
#endif

#ifdef CLPC
#define MAX_PROCESS 256
HANDLE subProcessHandles[MAX_PROCESS];
DWORD    subProcessCount = 0;
void pop_process(HANDLE h) {
  DWORD i = 0;
  for (;i < subProcessCount;i++) {
    if (subProcessHandles[i] == h) {
      subProcessCount--;
      CloseHandle(h);
      break;
    }
  }
  for(;i < subProcessCount;i++) {
    subProcessHandles[i] = subProcessHandles[i+1];
  }
}
#endif

CL_EXPORT tuple *waitpid_status_integer(CL_INT process, ClaireBoolean* block) {
  tuple *result;
#if defined(CLPC)
  /* <sb> emulates a UNIX waitpid call for PC */
  DWORD res = 0;
  if (subProcessCount == 0) {
    Cerror(102, 0, 0);
  } else if (process == -1) {
    /* <sb> wait for all subprocess */
    res = WaitForMultipleObjects(subProcessCount, subProcessHandles, FALSE,
          block == CTRUE ? INFINITE : 0);

    if (res == WAIT_FAILED) {
      Cerrorno(74,_string_("waitpid failed"),0);
    } else if (res == WAIT_TIMEOUT) {
      result = tuple::allocStack(3,0,0,-1);
    } else {
      HANDLE h = subProcessHandles[res - WAIT_OBJECT_0];
      CL_INT wpid = (CL_INT)GetProcessId(h);
      DWORD exitstatus;
      GetExitCodeProcess(h, &exitstatus);
      pop_process(h);
      result = tuple::allocStack(3,1,wpid,(CL_INT)exitstatus);
    }
  } else {
    /* <sb> wait for a single subprocess */
    CL_INT i = 0;
    CL_INT found = 0;
    for(;i < subProcessCount;i++) {
      if ((CL_INT)GetProcessId(subProcessHandles[i]) == process) {
        found = 1;
        break;
      }
    }
    if (found == 0) Cerror(100, process, 0);
    HANDLE h = subProcessHandles[i];
    res = WaitForSingleObject(h, block == CTRUE ? INFINITE : 0);

    if (res == WAIT_FAILED) {
      Cerrorno(74,_string_("waitpid failed"),0);
    } else if (res == WAIT_TIMEOUT) {
      result = tuple::allocStack(3,0,0,-1);
    } else {
      DWORD exitstatus;
      GetExitCodeProcess(h, &exitstatus);
      pop_process(h);
      result = tuple::allocStack(3,1,process,(CL_INT)exitstatus);
    }
  }
  
#else
  int status;
	CL_INT exitstatus;
    pid_t wpid;
    // waitpid() returns 0 if the child process is still running, or the 
    // process id if it stopped.  It can also return -1 in case of error.
    if (block == CTRUE)
      wpid = waitpid((pid_t)process, &status, WUNTRACED);
    else wpid = waitpid((pid_t)process, &status, WNOHANG|WUNTRACED);
  if(wpid == -1) Cerrorno(74,_string_("waitpid failed"),0);
  else if(wpid == 0) result = tuple::allocStack(3,0,0,-1);
  else {
    if (WIFEXITED(status)) { // program called exit
      exitstatus = WEXITSTATUS(status);
      result = tuple::allocStack(3,1,wpid,exitstatus);
    } else if(WIFSIGNALED(status)) { // process was signaled
      exitstatus = WTERMSIG(status);
      result = tuple::allocStack(3,2,wpid,exitstatus);
    } else if(WIFSTOPPED(status)) { // process was stopped
      exitstatus = WSTOPSIG(status);
      result = tuple::allocStack(3,3,wpid,exitstatus);
    }
    else result = tuple::allocStack(3,4,wpid,-1);
  }
#endif
  return result;
}

CL_EXPORT tuple *waitpid_status_integer_(CL_INT process, ClaireBoolean* block) {
  return waitpid_status_integer(process, block)->copyIfNeeded();
}

//<sb> fork interface
// on PC we throw an exception...
CL_EXPORT CL_INT cfork_void1() {
#if defined(CLPC) || !defined(HAVE_FORK)
  Cerror(75,_string_("fork"),0);
  return 0;
#else
  lastforked = fork();
  if(lastforked == -1) {
    lastforked = 0;
    Cerrorno(77,0,0);
  }
  if(lastforked == 0) {
    LOGO = 0; //<sb> v3.3.33 child shouldn't print exit string "bye..."
    TOPLEVEL = 0;
    isforked = 1; //<sb> v3.3.33 checked by trace method, do we print pid ?
  }
  return lastforked;
#endif
}


//<sb> get the last forked pid
CL_EXPORT CL_INT forked_void() {
#if defined(CLPC) || !defined(HAVE_FORK)
  Cerror(75,_string_("fork"),0);
  return 0;
#else
  if(lastforked == 0) Cerror(85,0,0);
  return lastforked;
#endif
}



//<sb> we use CreateProcess on a PC
// and fork/execve on unix
#ifdef CLPC

CL_EXPORT CL_INT process_I_string(char* self, bag* args) {
  if (subProcessCount + 1 == MAX_PROCESS)
    Cerror(101, _string_(self), _oid_(args));
  PROCESS_INFORMATION pi;
  STARTUPINFO si;
  CL_INT created;
  CL_INT flag = CREATE_NEW_PROCESS_GROUP;
  ZeroMemory(&si,sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);
  GC_RESERVE(1);  // v3.0.55 optim !
    char *Result ;
    char * s = self;
    OID gc_local;
  ITERATE(i);
  for (START(args); NEXT(i);)
  { GC_LOOP;
       OID  ztest;
       if (Kernel._string == OWNER(i)) ztest = i;
    else if (INHERIT(OWNER(i),Kernel._integer)) ztest = (*Kernel.string_I)(i);
    else if (Kernel._float == OWNER(i)) ztest = (*Kernel.string_I)(i);
    else if (Kernel._boolean == OWNER(i)) {
      if ((OBJECT(ClaireBoolean,i)) == CTRUE)
        ztest = _string_("true");
      else ztest = _string_("false");
    } 
    else ztest = CNULL;
    GC_OID(ztest); 
    if (ztest != CNULL)
    { char * z = string_v(ztest);
              GC__STRING(s = append_string(s,GC_STRING(append_string(GC_STRING(append_string(" \"",z)),"\""))), 1);
    } 
    GC_UNLOOP;} 
  Result = s;
  static HWND console = GetConsoleWindow();
  created = CreateProcess(
        NULL,  // pointer to name of executable module
        Result,  // pointer to command line string
        NULL,  // process security attributes
        NULL,  // thread security attributes
        FALSE, // handle inheritance flag
        (console ? 0 : (CREATE_NO_WINDOW|DETACHED_PROCESS)),//flag,  // creation flags
        NULL,  // pointer to new environment block
        NULL,  // pointer to current directory name
        &si,  // pointer to STARTUPINFO
        &pi);  // pointer to PROCESS_INFORMATION
  if(!created) Cerrorno(77,0,0);
  /*CloseHandle(pi.hProcess);*/
  CloseHandle(pi.hThread);
  GC_UNBIND;
  subProcessHandles[subProcessCount] = pi.hProcess;
  subProcessCount++;
  return pi.dwProcessId;
}

#else

//<sb> here is a private tool to build a C string array
// from a claire bag
// integer/float/boolean are stringed!
static char **make_arg_string(char* self, bag *args) {
  static char** argv = 0;
  CL_INT n = 1;
  if(argv) delete [] argv;
  argv = new char*[args->length + 2];
  if (argv == 0) return 0;
  argv[0] = self;
  GC_BIND;
  OID gc_local;
  ITERATE(i);
  for(START(args); NEXT(i);) {
    OID o = 0;
        if(Kernel._string == OWNER(i)) o = i;
    else if(INHERIT(OWNER(i),Kernel._integer) || Kernel._float == OWNER(i))
      o = (*Kernel.string_I)(i);
    else if(Kernel._boolean == OWNER(i)) {
          if(OBJECT(ClaireBoolean,i) == CTRUE) o = _string_("true");
          else o = _string_("false");
        }
        if(o) {
          GC_OID(o);
          argv[n++] = string_v(o);
        }
    }
    argv[n] = 0;
  GC_UNBIND;
  return argv;
}

CL_EXPORT CL_INT process_I_string(char* self, bag* args) {
  char** argv = make_arg_string(self, args);
  if(argv == 0) Cerror(61,_string_("process! @ (string, bag)"),0);
  CL_INT ret = cfork_void1();
  switch(ret) {
    case 0:
      execve(self, argv, environ);
      Cerrorno(77,0,0);
      break;
  }
  return ret;
}
#endif



/*********************************************************************/
/**    5. uname                                                      */
/*********************************************************************/

#ifdef CLPC

// On a PC, tell if the MMX instruction set is availbale or not.
CL_INT pc_have_mmx_support = 0;

struct  utsname {
  char  sysname[256]; // Name of OS
  char  nodename[256]; // Name of this network node
  char  release[256]; // Release level
  char  version[256]; // Version level
  char  machine[256]; // Hardware type
};
// the pc doesn't understand uname so we guess it could
// exists as :
extern CL_INT uname(struct utsname *name);
CL_INT uname(struct utsname *ub) {
  char *ptr;
  DWORD version;
  SYSTEM_INFO sysinfo;
  char hostname[4096];
  version = GetVersion();
  GetSystemInfo(&sysinfo);
  switch (sysinfo.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_INTEL: strcpy(ub->machine, "ix86");break;
    case PROCESSOR_ARCHITECTURE_MIPS : strcpy(ub->machine, "mips");break;
    case PROCESSOR_ARCHITECTURE_ALPHA: strcpy(ub->machine, "alpha");break;
    case PROCESSOR_ARCHITECTURE_PPC:strcpy(ub->machine, "ppc");break;
    default:strcpy(ub->machine, "unknown");break; }
  if (version<0x80000000) strcpy(ub->version, "NT");
  else if (LOBYTE(LOWORD(version))<4) strcpy(ub->version, "Win32s");
  else strcpy(ub->version, "Win95");
  sprintf(ub->release, "%u.%u", (DWORD)(LOBYTE(LOWORD(version))), (DWORD)(HIBYTE(LOWORD(version))));
  strcpy(ub->sysname, "Windows");
  if(gethostname(hostname, sizeof(hostname)) == 0)
    { if((ptr = strchr(hostname, '.'))) *ptr = '\0'; }
  else strcpy(hostname, "unknown");
  strcpy(ub->nodename, hostname); //, sizeof(ub->nodename));
  //ub->nodename[_SYS_NMLN - 1] = '\0';
  pc_have_mmx_support = IsProcessorFeaturePresent(PF_MMX_INSTRUCTIONS_AVAILABLE);
  return 0;
}

#endif

class InitUname {
public:
  static InitUname single;
  struct utsname un;
  InitUname() {uname(&un);}
};

InitUname InitUname::single = InitUname();

//<sb> the uname struct is exploded in a set of api :
CL_EXPORT char* sys_name_void() {return InitUname::single.un.sysname;}
CL_EXPORT char* sys_node_name_void() {return InitUname::single.un.nodename;}
CL_EXPORT char* sys_release_void() {return InitUname::single.un.release;}
CL_EXPORT char* sys_version_void() {return InitUname::single.un.version;}
CL_EXPORT char* sys_machine_void() {return InitUname::single.un.machine;}
CL_EXPORT char* sys_arch_void() {
  #ifdef CLPC
  return "ix86";
  #else
  return CLARCH;
  #endif
}

CL_EXPORT char* sys_compiler_void() {
  #ifdef CLPC
  return "cl";
  #else
  return CLSYSCOMPILER;
  #endif
}
CL_EXPORT char* sys_compiler_version_void() {
  #ifdef CLPC
  return "";
  #else
  return CLSYSCOMPILERVERSION;
  #endif
}


/*********************************************************************/
/**    6. string - case/digit test                                   */
/*********************************************************************/

CL_EXPORT ClaireBoolean* alpha_ask_string(char* s) {
  CL_INT i = 0;
  CL_INT len = LENGTH_STRING(s);
    for(;i < len;i++) {
      unsigned char c = (unsigned char)s[i];
       if(isalpha(c) == 0) return CFALSE;
    }
    return CTRUE; 
}   


CL_EXPORT ClaireBoolean* alpha_ask_char(ClaireChar* c) {
  unsigned char ch = (unsigned char)c->ascii;
  if(isalpha(ch) == 0) return CFALSE;
  return CTRUE;
}

CL_EXPORT ClaireBoolean* lower_ask_char(ClaireChar* c) {
  unsigned char ch = (unsigned char)c->ascii;
  if(islower(ch) == 0) return CFALSE;
  return CTRUE;
}


CL_EXPORT ClaireBoolean* lower_ask_string(char* s) {
  CL_INT i = 0;
  CL_INT len = LENGTH_STRING(s);
  for(;i < len;i++) {
    unsigned char ch = (unsigned char)s[i];
    if(islower(ch) == 0) return CFALSE;
  }
  return CTRUE;
}


CL_EXPORT ClaireBoolean* upper_ask_char(ClaireChar* c) {
  unsigned char ch = (unsigned char)c->ascii;
  if(isupper(ch) == 0) return CFALSE;
  return CTRUE;
}


CL_EXPORT ClaireBoolean* upper_ask_string(char* s) {
  CL_INT i = 0;
  CL_INT len = LENGTH_STRING(s);
  for(;i < len;i++) {
    unsigned char ch = (unsigned char)s[i];
    if(isupper(ch) == 0) return CFALSE;
  }
  return CTRUE;
}


CL_EXPORT char* upper_string(char* s){
  unsigned char* res = (unsigned char*)copy_string(s);
  CL_INT len = LENGTH_STRING(s);
  CL_INT i = 0;
  for(;i < len;i++) {
    unsigned char ch = (unsigned char)s[i];
    res[i] = toupper(ch);
  }
  return (char*)res;
}


CL_EXPORT char* lower_string(char* s) {
  unsigned char* res = (unsigned char*)copy_string(s);
  CL_INT len = LENGTH_STRING(s);
  CL_INT i = 0;
  for(;i < len;i++) {
    unsigned char ch = (unsigned char)s[i];
    res[i] = tolower(ch);
  }
  return (char*)res;
}

CL_EXPORT ClaireBoolean* space_ask_char(ClaireChar* c) {
  CL_INT ch = (CL_INT)c->ascii;
  return (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') ? CTRUE : CFALSE;
}


CL_EXPORT ClaireBoolean* digit_ask_char(ClaireChar* c) {
  unsigned char ch = (unsigned char)c->ascii;
  if(isdigit(ch) == 0) return CFALSE;
  return CTRUE;
}

CL_EXPORT ClaireBoolean* space_ask_string(char* s) {
  CL_INT i = 0;
  CL_INT len = LENGTH_STRING(s);
  for(;i < len;i++) {
    if(!(s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n'))
    return CFALSE;
  }
  return CTRUE;
}


CL_EXPORT ClaireBoolean* digit_ask_string(char* s) {
  CL_INT i = 0;
  CL_INT len = LENGTH_STRING(s);
  for(;i < len;i++) {
    unsigned char ch = (unsigned char)s[i];
    if(isdigit(ch) == 0) return CFALSE;
  }
  return CTRUE;
}


/*********************************************************************/
/**    7. string - find/replace                                      */
/*********************************************************************/


CL_EXPORT char* replace_string(char* src, char* to, char *by)
{
  CL_INT lto = LENGTH_STRING(to);
  if(lto == 0) return "";
  CL_INT lsrc = LENGTH_STRING(src);
  if(lto > lsrc) return copy_string(src);
  ClEnv->bufferStart();
  CL_INT lby = LENGTH_STRING(by);
  CL_INT i = 0; CL_INT l = 0;
  for(;i < lsrc - lto + 1;i++)
  {
    CL_INT same = 1; CL_INT j = 0;
    for(;j < lto;j++)
      if(to[j] != src[i + j])
        {same = 0; break;}
    if(same)
      {for(j=0;j < lby;j++) ClEnv->pushChar(by[j]);
      i += lto - 1;
      l += lby;}
    else {l++;ClEnv->pushChar(src[i]);} }
  for(;i < lsrc;i++) {l++;ClEnv->pushChar(src[i]);}
  char *tmp = ClEnv->bufferCopy();
  return tmp;
}


CL_EXPORT CL_INT occurrence_string(char* in, char* to)
{
  CL_INT lin = LENGTH_STRING(in);
  CL_INT lto = LENGTH_STRING(to);
  if(lto == 0 || lin == 0) return 0;
  CL_INT res = 0;
  CL_INT i = 0;
  for(;i < lin - lto + 1;i++)
  {
    CL_INT same = 1; CL_INT j = 0;
    for(;j < lto;j++)
      if(to[j] != in[i + j])
        {same = 0; break;}
    if(same)
    {    
      i += lto - 1;
      res++;
    }
  }
  return res;
} 


CL_EXPORT CL_INT find_string(char* src, char* to, CL_INT from)
{
  if(from <= 0) return 0;
  CL_INT lsrc = LENGTH_STRING(src);
  CL_INT lto = LENGTH_STRING(to);
  CL_INT i = from - 1;
  for(;i < lsrc - lto + 1;i++)
  {
    CL_INT j = 0; CL_INT same = 1;
    for(;j < lto;j++)
      if(to[j] != src[i + j])
        {same = 0; break;}
    if(same) return i + 1;
  }
  return 0;
}


CL_EXPORT CL_INT rfind_string(char* src, char* to, CL_INT from)
{
  if(from > LENGTH_STRING(src)) return 0;
  CL_INT lto = LENGTH_STRING(to);
  CL_INT i = from - 1;
  for(;i >= 0;i--)
  {
    CL_INT j = 0; CL_INT same = 1;
    for(;j < lto;j++)
      if(to[j] != src[i + j])
        {same = 0; break;}
    if(same)
      return i + 1;
  }
  return 0;
}


CL_EXPORT char * ltrim_string(char *s) {
  CL_INT  p = 1;
  CL_INT ls = LENGTH_STRING(s);
  while(p <= ls) {
      char ch = s[p - 1];
      if (!(ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n'))
         break;
      p++; } 
  if (CLMEM(s) && p == 1)
    return s;
  return substring_string(s,p,ls); }


CL_EXPORT char * rtrim_string(char *s) {
  CL_INT  p = LENGTH_STRING(s);
  CL_INT ls = p;
   while(p >= 1) {
      char ch = s[p - 1];
      if (!(ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n'))
          break;
      p--; }
  if (CLMEM(s) && p == ls)
    return s;
   return substring_string(s,1,p); }


CL_EXPORT char * trim_string(char *s) {
  CL_INT  p1 = 1;
  CL_INT  p2 = LENGTH_STRING(s);
  CL_INT ls = p2;
  while (p1 <= ls) {
      char ch = s[p1 - 1];
      if(!(ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n'))
         break;
      p1++; } 
  while(p2 >= 1) {
      char ch = s[p2 - 1];
      if(!(ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n'))
        break;
       p2--; }
  if (CLMEM(s) && p1 == 1 && p2 == ls)
    return s;
  return substring_string(s,p1,p2); } 
  
  
CL_EXPORT CL_INT  find_string2(char *src,char *to)
{ return find_string(src,to,1);} 

CL_EXPORT char * right_string(char *src,CL_INT n)
{ CL_INT len = LENGTH_STRING(src);
  if (len <= n) return src;
  return substring_string(src,((len-n)+1),len);} 


CL_EXPORT char * left_string(char *src,CL_INT n)
{ CL_INT len = LENGTH_STRING(src);
  if (len <= n) return src;
   return substring_string(src,1,n);} 

CL_EXPORT CL_INT  rfind_string2(char *src,char *to)
{ return rfind_string(src,to,LENGTH_STRING(src));} 


CL_EXPORT char *reverse_string(char *src) {
  CL_INT len = LENGTH_STRING(src);
  char *res =  ClAlloc->makeString(len);
  char *a = res + len - 1;
  for(;len > 0;len--)
    *a-- = *src++;
  return res;
}


/*********************************************************************/
/**    8. string - explode                                           */
/*********************************************************************/

#define EXPLODE_ADD(l, s, j) { \
  char *a = GC_STRING(ClAlloc->makeString(j)); \
  if(j) memcpy(a,s,j); \
  GC__ANY(l = l->addFast(GC_OID(_string_(a))), 1); }

CL_EXPORT list *explode_char_string(char *self, char sep) {
  GC_RESERVE(1);
    list * l = list::empty(Kernel._string);
    char *end = self + LENGTH_STRING(self);
  char *s1 = self;
  char *s2 = self;
  OID gc_local;
  while(s2 < end) 
  { GC_LOOP;
    s1 = s2;
    while(s1 < end && *s1 != sep) s1++;
    s1--;
    EXPLODE_ADD(l, s2, s1 - s2 + 1)
    s2 = s1+2;
    GC_UNLOOP;}
  if(s2 < end)
    EXPLODE_ADD(l, s2, end - s2 + 1)
  if (l->length == 0)
    EXPLODE_ADD(l, "", 0)
  GC_UNBIND; return l;
}

CL_EXPORT list * explode_string(char *self,char *sep) {
  CL_INT seplen = LENGTH_STRING(sep);
  if(seplen == 1) return explode_char_string(self, *sep);
  GC_RESERVE(1);
  list *l = list::empty(Kernel._string);
  CL_INT len = LENGTH_STRING(self);
  char *s1 = self;
  char *s2 = self + len;
  char *mark = s1;
  OID gc_local;
  while(s1 < s2)
   { GC_LOOP;     
     while(s1 < s2 && memcmp(s1,sep,seplen)) s1++;
     if(s1 >= s2) break;
     EXPLODE_ADD(l, mark, s1 - mark)
     s1 += seplen;
     mark = s1;
    GC_UNLOOP;}
   if(s2 - mark)
    EXPLODE_ADD(l, mark, s2 - mark)
  GC_UNBIND; return l; }



/*********************************************************************/
/**    9. string - encoding/decoding (xl)                            */
/*********************************************************************/


static CL_INT htoi(char *s)
{
  CL_INT value;
  CL_INT c;

  c = s[0];
  if (isupper(c))
    c = tolower(c);
  value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;

  c = s[1];
  if (isupper(c))
    c = tolower(c);
  value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;

  return value;
}

static unsigned char hexchars[] = "0123456789ABCDEF";

CL_EXPORT char* url_encode_string(char* s)
{
  register CL_INT x, y;
  unsigned char *str;
  CL_INT len = LENGTH_STRING(s);
  ClEnv->bufferStart();
  CL_INT l = 0;
  for(x = 0, y = 0; len--; x++, y++) {
    char c = s[x];
    if (c == ' ') {
      {l++;ClEnv->pushChar('+');}
    } else if ((c < '0' && c != '-' && c != '.') ||
           (c < 'A' && c > '9') ||
           (c > 'Z' && c < 'a' && c != '_') ||
           (c > 'z')) {
      l++;ClEnv->pushChar('%');y++;
      l++;ClEnv->pushChar(hexchars[(unsigned char) s[x] >> 4]);y++;
      l++;ClEnv->pushChar(hexchars[(unsigned char) s[x] & 15]);
    } else {l++;ClEnv->pushChar(s[x]);}
  }
  char *res = ClEnv->bufferCopy();
  return res;
}

CL_EXPORT char* url_decode_string(char* data)
{
  char *str = data;
  ClEnv->bufferStart();
  CL_INT len = LENGTH_STRING(data);
  CL_INT l = 0;
  while (len--) {
    if (*data == '+') {l++;ClEnv->pushChar(' ');} //*dest = ' ';
    else if (*data == '%' && len >= 2 && isxdigit((CL_INT) *(data + 1)) && isxdigit((CL_INT) *(data + 2))) {
      ClEnv->pushChar((char)htoi(data + 1));
      l++;
      data += 2;
      len -= 2;
    } else
      {l++;ClEnv->pushChar(*data);}
    data++;
  }
  char *res = ClEnv->bufferCopy();
  return res;
}


CL_EXPORT char *mime_encode_string(char *subject) {
    char *output = 0;
    unsigned char *p, *pDest ;
    CL_INT i, n, len ;

    len = LENGTH_STRING(subject);
    output = new char[len * 3 + 1];
    if(output == 0) Cerror(61, _string_("mime_encode @ string"),0);
    if (output == 0)
        return 0;

    p = (unsigned char*)subject;
    pDest = (unsigned char*)output ;

    for (i = 0; i < len; i++)
    {
        /* XP_IS_ALPHA(*p) || XP_IS_DIGIT(*p)) */
        if (((*p >= 'a') && (*p <= 'z')) ||
             ((*p >= 'A') && (*p <= 'Z')) ||
             ((*p >= '0') && (*p <= '9')))
           *pDest = *p;
        /*if ((*p >= '!' && *p <= '<') ||
            (*p >= '>' && *p <= '~') ||
            *p == '\t' || *p == ' ') 
            *pDest = *p;*/
        else
        {
            *pDest++ = '=';
            n = (*p & 0xF0) >> 4; /* high byte */
            if (n < 10)
                *pDest = '0' + n;
            else
                *pDest = 'A' + n - 10;
            pDest ++ ;

            n = *p & 0x0F;          /* low byte */
            if (n < 10)
                *pDest = '0' + n;
            else
                *pDest = 'A' + n - 10;
        }

        p ++;
        pDest ++;
    }

    *pDest = '\0';
    char* res = copy_string1(output, (char*)pDest - output);
    delete output;
    return res;
}

CL_EXPORT char *mime_decode_string(char *in)
{
    CL_INT i = 0, length = LENGTH_STRING(in);
    char token[3];
    char *out, *dest = 0;

    out = dest = new char[length+1];
    if(dest == 0) Cerror(61, _string_("mime_decode @ string"),0);
    if(dest == 0) return 0;
    memset(out, 0, length+1);
    while (length > 0 || i != 0)
    {
        while (i < 3 && length > 0)
        {
            token [i++] = *in;
            in++;
            length--;
        }

        if (i < 3)
        {
          /* Didn't get enough for a complete token.
             If it might be a token, unread it.
             Otherwise, just dump it.
             */
            strncpy (out, token, i);
            break;
        }
        i = 0;

    if (token [0] == '=')
        {
            unsigned char c = 0;
            if (token[1] >= '0' && token[1] <= '9')
                c = token[1] - '0';
            else if (token[1] >= 'A' && token[1] <= 'F')
                c = token[1] - ('A' - 10);
            else if (token[1] >= 'a' && token[1] <= 'f')
                c = token[1] - ('a' - 10);
            else if (token[1] == '\r' || token[1] == '\n')
            {
                /* =\n means ignore the newline. */
                if (token[1] == '\r' && token[2] == '\n')
                    ;       /* swallow all three chars */
                else
                {
                    in--;   /* put the third char back */
                    length++;
                }
                continue;
            }
            else
            {
                /* = followed by something other than hex or newline -
                 pass it through unaltered, I guess.  (But, if
                 this bogus token happened to occur over a buffer
                 boundary, we can't do this, since we don't have
                 space for it.  Oh well.  Forget it.)  */
                if (in > out) *out++ = token[0];
                if (in > out) *out++ = token[1];
                if (in > out) *out++ = token[2];
                continue;
            }

            /* Second hex digit */
            c = (c << 4);
            if (token[2] >= '0' && token[2] <= '9')
                c += token[2] - '0';
            else if (token[2] >= 'A' && token[2] <= 'F')
                c += token[2] - ('A' - 10);
            else if (token[2] >= 'a' && token[2] <= 'f')
                c += token[2] - ('a' - 10);
            else
            {
                /* We got =xy where "x" was hex and "y" was not, so
                 treat that as a literal "=", x, and y.  (But, if
                 this bogus token happened to occur over a buffer
                 boundary, we can't do this, since we don't have
                 space for it.  Oh well.  Forget it.) */
                if (in > out) *out++ = token[0];
                if (in > out) *out++ = token[1];
                if (in > out) *out++ = token[2];
                continue;
            }

            *out++ = (char) c;
        }
        else
        {
            *out++ = token [0];

            token[0] = token[1];
            token[1] = token[2];
            i = 2;
        }
    }
    /* take care of special underscore case */
    char *bob = dest;
    for (; bob < out; bob++)
        if (*bob == '_')    *bob = ' ';
    
    char* res = copy_string1(dest, out - dest + i);
    delete dest;
    return res;
}


CL_EXPORT char* escape_string(char* src) {
  char *res = (char*)malloc(LENGTH_STRING(src)*6 + 1);
  if(res == 0) Cerror(61, _string_("escape @ string"),0);
  char *travel = res;
  while(*src) {
    CL_INT c = integer_I_char(_char_(*src));
    if(c < 0) c = 256 + c;
    if(c > 256) c -= 256;
    
    /*if(c == 9) {strcpy(travel,"&#09;"); travel += 5;}
    else if(c == 10) {strcpy(travel,"&#10;"); travel += 5;}
    else if(c == 13) {strcpy(travel,"&#13;"); travel += 5;}
    else if(c >= 32 && c <= 64)*/ {
      switch(c) {
        /*case ' ': strcpy(travel,"&nbsp;"); travel += 6; break;
        case '"': strcpy(travel,"&quot;"); travel += 6; break;
        case '\'': strcpy(travel,"&#39;"); travel += 5; break;*/
        case '<': strcpy(travel,"&lt;"); travel += 4; break;
        case '>': strcpy(travel,"&gt;"); travel += 4; break;
        case '&': strcpy(travel,"&amp;"); travel += 5; break;
        default: *travel++ = c;
      }
    }
    /*else if(c >= 128 && c <= 255) {
      char buf[8];
      sprintf(buf, "&#%d;", c);
      strcpy(travel, buf); travel += strlen(buf);
    }
    else *travel++ = c;*/
    src++;
  }
  *travel = 0;
  travel = copy_string1(res, travel - res);
  free(res);
  return travel;
}


void unescapeEOS(char* src) {
  Cerror(62,_string_(src),0); }
void unescapeNUM(char* src) {
  Cerror(63,_string_(src),0); }



CL_EXPORT char* unescape_string(char* src) {
  #define ELSE_CONV_NAME_NUM(name,len,num) else if(strncmp(src,name,len) == 0) {*travel++ = char_I_integer(num)->ascii; src += len;}
  char *anch = src;
  CL_INT len = LENGTH_STRING(src);
  char *res = (char*)malloc(len+1);
  if(res == 0) Cerror(61, _string_("unescape @ string"),0);
  char *travel = res;
  while(*src) {
    if(*src != '&') *travel++ = *src++;
    else {
      src++;
      if(*src == 0) {*travel++ = '&'; break;}
      if(*src == '#') {
        src++;
        if(*src == 0) unescapeEOS(anch);
        if(*src == 'x' || *src == 'X') {
          src++;
          if(*src == 0) unescapeEOS(anch);
          CL_INT c;
          if(sscanf(src,"%x;",&c) != 1) unescapeNUM(anch);
          while(*src != ';') src++;
          src++;
          *travel++ = char_I_integer(c)->ascii;  
        } else {
          CL_INT c;
          if(sscanf(src,"%d;",&c) != 1) unescapeNUM(anch);
          while(*src != ';') src++;
          src++;
          *travel++ = char_I_integer(c)->ascii;
        }
      }
      else if(strncmp(src,"lt;",3) == 0) {*travel++ = '<'; src += 3;}
      else if(strncmp(src,"gt;",3) == 0) {*travel++ = '>'; src += 3;}
      else if(strncmp(src,"amp;",4) == 0) {*travel++ = '&'; src += 4;}
      else if(strncmp(src,"quot;",5) == 0) {*travel++ = '"'; src += 5;}
      else if(strncmp(src,"apos;",5) == 0) {*travel++ = '\''; src += 5;}
      ELSE_CONV_NAME_NUM("yen;",4,165)
      ELSE_CONV_NAME_NUM("uml;",4,168)
      ELSE_CONV_NAME_NUM("not;",4,172)
      ELSE_CONV_NAME_NUM("shy;",4,173)
      ELSE_CONV_NAME_NUM("reg;",4,174)
      ELSE_CONV_NAME_NUM("deg;",4,176)
      ELSE_CONV_NAME_NUM("nbsp;",5,160)
      ELSE_CONV_NAME_NUM("sect;",5,167)
      ELSE_CONV_NAME_NUM("copy;",5,169)
      ELSE_CONV_NAME_NUM("ordf;",5,170)
      ELSE_CONV_NAME_NUM("macr;",5,175)
      ELSE_CONV_NAME_NUM("sup2;",5,178)
      ELSE_CONV_NAME_NUM("sup3;",5,179)
      ELSE_CONV_NAME_NUM("para;",5,182)
      ELSE_CONV_NAME_NUM("sup1;",5,185)
      ELSE_CONV_NAME_NUM("ordm;",5,186)
      ELSE_CONV_NAME_NUM("euro;",5,128)
      ELSE_CONV_NAME_NUM("laquo;",6,171)
      ELSE_CONV_NAME_NUM("iexcl;",6,161)
      ELSE_CONV_NAME_NUM("pound;",6,163)
      ELSE_CONV_NAME_NUM("acute;",6,180)
      ELSE_CONV_NAME_NUM("micro;",6,181)
      ELSE_CONV_NAME_NUM("cedil;",6,184)
      ELSE_CONV_NAME_NUM("raquo;",6,187)
      ELSE_CONV_NAME_NUM("curren;",7,164)
      ELSE_CONV_NAME_NUM("brvbar;",7,166)
      ELSE_CONV_NAME_NUM("plusmn;",7,177)
      ELSE_CONV_NAME_NUM("middot;",7,183)
      ELSE_CONV_NAME_NUM("frac14;",7,188)
      ELSE_CONV_NAME_NUM("frac12;",7,189)
      ELSE_CONV_NAME_NUM("frac34;",7,190)
      ELSE_CONV_NAME_NUM("iquest;",7,191)
      ELSE_CONV_NAME_NUM("Agrave;",7,192)
      ELSE_CONV_NAME_NUM("Aacute;",7,193)
      ELSE_CONV_NAME_NUM("Acirc;",6,194)
      ELSE_CONV_NAME_NUM("Atilde;",7,195)
      ELSE_CONV_NAME_NUM("Auml;",5,196)
      ELSE_CONV_NAME_NUM("Aring;",6,197)
      ELSE_CONV_NAME_NUM("AElig;",6,198)
      ELSE_CONV_NAME_NUM("Ccedil;",7,199)
      ELSE_CONV_NAME_NUM("Egrave;",7,200)
      ELSE_CONV_NAME_NUM("Eacute;",7,201)
      ELSE_CONV_NAME_NUM("Ecirc;",6,202)
      ELSE_CONV_NAME_NUM("Euml;",5,203)
      ELSE_CONV_NAME_NUM("Igrave;",7,204)
      ELSE_CONV_NAME_NUM("Iacute;",7,205)
      ELSE_CONV_NAME_NUM("Icirc;",6,206)
      ELSE_CONV_NAME_NUM("Iuml;",5,207)
      ELSE_CONV_NAME_NUM("ETH;",4,208)
      ELSE_CONV_NAME_NUM("Ntilde;",7,209)
      ELSE_CONV_NAME_NUM("Ograve;",7,210)
      ELSE_CONV_NAME_NUM("Oacute;",7,211)
      ELSE_CONV_NAME_NUM("Ocirc;",6,212)
      ELSE_CONV_NAME_NUM("Otilde;",7,213)
      ELSE_CONV_NAME_NUM("Ouml;",5,214)
      ELSE_CONV_NAME_NUM("times;",6,215)
      ELSE_CONV_NAME_NUM("Oslash;",7,216)
      ELSE_CONV_NAME_NUM("Ugrave;",7,217)
      ELSE_CONV_NAME_NUM("Uacute;",7,218)
      ELSE_CONV_NAME_NUM("Ucirc;",6,219)
      ELSE_CONV_NAME_NUM("Uuml;",5,220)
      ELSE_CONV_NAME_NUM("Yacute;",7,221)
      ELSE_CONV_NAME_NUM("THORN;",6,222)
      ELSE_CONV_NAME_NUM("szlig;",5,223)
      ELSE_CONV_NAME_NUM("agrave;",7,224)
      ELSE_CONV_NAME_NUM("aacute;",7,225)
      ELSE_CONV_NAME_NUM("acirc;",6,226)
      ELSE_CONV_NAME_NUM("atilde;",7,227)
      ELSE_CONV_NAME_NUM("auml;",5,228)
      ELSE_CONV_NAME_NUM("aring;",6,229)
      ELSE_CONV_NAME_NUM("aelig;",6,230)
      ELSE_CONV_NAME_NUM("ccedil;",7,231)
      ELSE_CONV_NAME_NUM("egrave;",7,232)
      ELSE_CONV_NAME_NUM("eacute;",7,233)
      ELSE_CONV_NAME_NUM("ecirc;",6,234)
      ELSE_CONV_NAME_NUM("euml;",5,235)
      ELSE_CONV_NAME_NUM("igrave;",7,236)
      ELSE_CONV_NAME_NUM("iacute;",7,237)
      ELSE_CONV_NAME_NUM("icirc;",6,238)
      ELSE_CONV_NAME_NUM("iuml;",5,239)
      ELSE_CONV_NAME_NUM("eth;",4,240)
      ELSE_CONV_NAME_NUM("ntilde;",7,241)
      ELSE_CONV_NAME_NUM("ograve;",7,242)
      ELSE_CONV_NAME_NUM("oacute;",7,243)
      ELSE_CONV_NAME_NUM("ocirc;",6,244)
      ELSE_CONV_NAME_NUM("otilde;",7,245)
      ELSE_CONV_NAME_NUM("ouml;",5,246)
      ELSE_CONV_NAME_NUM("divide;",7,247)
      ELSE_CONV_NAME_NUM("oslash;",7,248)
      ELSE_CONV_NAME_NUM("ugrave;",7,249)
      ELSE_CONV_NAME_NUM("uacute;",7,250)
      ELSE_CONV_NAME_NUM("ucirc;",6,251)
      ELSE_CONV_NAME_NUM("uuml;",5,252)
      ELSE_CONV_NAME_NUM("yacute;",7,253)
      ELSE_CONV_NAME_NUM("thorn;",6,254)
      ELSE_CONV_NAME_NUM("yuml;",5,255)
      else {*travel++ = '&'; *travel++ = *src++; }
      //else unescapeEOS(anch);
    }
  }
  *travel = 0;
  travel = copy_string1(res, travel-res);
  free(res);
  return travel;
}



/*********************************************************************/
/**    10. string - base64 encoding/decoding (xl)                    */
/*********************************************************************/

static const char cb64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char cd64[]="|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";

void encodeblock( unsigned char in[3], unsigned char out[4], CL_INT len )
{
    out[0] = cb64[ in[0] >> 2 ];
    out[1] = cb64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? cb64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? cb64[ in[2] & 0x3f ] : '=');
}

CL_EXPORT void encode64_port(PortObject *infile, PortObject *outfile, CL_INT linesize) {
    unsigned char in[3], out[4];
    CL_INT i, len, blocksout = 0;
  CL_INT eof = 0;
  if (linesize <= 4) linesize = 80;
    while( !eof ) {
    in[0] = 0; in[1] = 0; in[2] = 0;
        len = Core.read_port->fcall((CL_INT)infile, (CL_INT)in, 3);
        eof = len == 0; 
        if( len ) {
            encodeblock( in, out, len );
            Core.write_port->fcall((CL_INT)outfile, (CL_INT)out, 4);
            blocksout++;
        }
        if(!eof && blocksout >= (linesize/4)) {
      Core.write_port->fcall((CL_INT)outfile, (CL_INT)"\r\n", 2);
            blocksout = 0;
        }
    }
}

void decodeblock( unsigned char in[4], unsigned char out[3] )
{   
    out[ 0 ] = (unsigned char ) (in[0] << 2 | in[1] >> 4);
    out[ 1 ] = (unsigned char ) (in[1] << 4 | in[2] >> 2);
    out[ 2 ] = (unsigned char ) (((in[2] << 6) & 0xc0) | in[3]);
}

CL_EXPORT void decode64_port(PortObject *infile, PortObject *outfile) {
    unsigned char in[4], out[3], v;
    CL_INT i, len;
  CL_INT eof = 0;
  
    while( !eof ) {
        for( len = 0, i = 0; i < 4 && !eof; i++ ) {
            v = 0;
            while( !eof && v == 0 ) {
        eof = Core.read_port->fcall((CL_INT)infile, (CL_INT)&v, 1) == 0;
                v = (unsigned char) ((v < 43 || v > 122) ? 0 : cd64[ v - 43 ]);
                if( v ) {
                    v = (unsigned char) ((v == '$') ? 0 : v - 61);
                }
            }
            if(!eof) {
                len++;
        if( v ) {  
                    in[ i ] = (unsigned char) (v - 1);
                }
      }
      else in[i] = 0;
        }
        if( len ) {
            decodeblock( in, out );
      Core.write_port->fcall((CL_INT)outfile, (CL_INT)out, len - 1);
        }
    }
}

