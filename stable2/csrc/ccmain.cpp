/***** CLAIRE Compilation of file ccmain.cl.cl 
         [version 3.5.0 / safety 5] *****/

#include <claire.h>
#include <Kernel.h>

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllexport)
#endif

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllimport)
#endif
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>
#include <Optimize.h>
#include <Generate.h>
#include <ccmain.h>

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT
#endif

// *******************************************************************
// * CLAIRE                                                          *
// * ccmain.cl                                                       *
// * Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved      *
// * cf. copyright info in file object.cl: about()                   *
// *******************************************************************
// * Sylvain Benilan                                                 *
// * this file has been highly modified for the xl version           *
// *******************************************************************
// The c++ function for: main(l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  main_list(list *l) { 
  _void_(OBJECT(Generate_producer,Generate.PRODUCER->value)->extension = ((char*)".cpp"));
    update_property(Optimize.libraries_dir,
      Optimize.compiler,
      17,
      Kernel._object,
      _oid_(list::alloc(Kernel._any,3,_string_(((char*)"release")),
        _string_(((char*)"debug")),
        _string_(((char*)"release")))));
    update_property(Optimize.libraries,
      Optimize.compiler,
      12,
      Kernel._object,
      _oid_(list::alloc(Kernel._string,1,_string_(((char*)"Kernel")))));
    _void_(Optimize.compiler->headers_dir = ((char*)"include"));
    _void_(Optimize.compiler->source = ((char*)"csrc"));
    update_property(Optimize.options,
      Optimize.compiler,
      19,
      Kernel._object,
      _oid_(list::alloc(Kernel._any,3,_string_(((char*)"")),
        _string_(((char*)"")),
        _string_(((char*)"")))));
    _void_(Optimize.compiler->env = ((char*)"Darwin-i386-g++13.0.0"));
    (Generate.so_options->value= _string_(((char*)" -dynamiclib -undefined dynamic_lookup")));
    (Generate.cxx_options->value= _string_(((char*)" -fPIC -DPIC")));
    (Generate.ld_options->value= _string_(((char*)" -DCL64 -rdynamic")));
    POP_SIGNAL;}
  



