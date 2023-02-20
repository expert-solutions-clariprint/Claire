// --- System configuration file for "claire" ---

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>
#include <Optimize.h>
#include <Generate.h>

  

void loadModules() 
{ //module definitions 
    Core.initModule("Core",mClaire.it,list::alloc(Kernel.emptySet,1,_oid_(Kernel.it)),
    "./meta",list::alloc(Kernel.emptySet,7,_string_(((char*)"method")),
      _string_(((char*)"object")),
      _string_(((char*)"function")),
      _string_(((char*)"types")),
      _string_(((char*)"signal")),
      _string_(((char*)"port")),
      _string_(((char*)"cmdline"))));
    iClaire.initModule("iClaire",claire.it,list::alloc(Kernel.emptySet,1,_oid_(mClaire.it)),
    "",Kernel.nil);
    Serialize.initModule("Serialize",iClaire.it,list::alloc(Kernel._module,2,_oid_(Core.it),_oid_(mClaire.it)),
    "meta",list::alloc(Kernel._string,1,_string_(((char*)"serialization"))));
    Language.initModule("Language",iClaire.it,list::alloc(Kernel.emptySet,3,_oid_(Kernel.it),
      _oid_(Core.it),
      _oid_(Serialize.it)),
    "./meta",list::alloc(Kernel.emptySet,4,_string_(((char*)"pretty")),
      _string_(((char*)"call")),
      _string_(((char*)"control")),
      _string_(((char*)"define"))));
    Reader.initModule("Reader",iClaire.it,list::alloc(Kernel.emptySet,3,_oid_(Kernel.it),
      _oid_(Core.it),
      _oid_(Language.it)),
    "./meta",list::alloc(Kernel._string,8,_string_(((char*)"read")),
      _string_(((char*)"syntax")),
      _string_(((char*)"file")),
      _string_(((char*)"inspect")),
      _string_(((char*)"complete")),
      _string_(((char*)"toplevel")),
      _string_(((char*)"wcl")),
//      _string_(((char*)"scanf")),      
      _string_(((char*)"codedoc"))));
    Compile.initModule("Compile",iClaire.it,list::alloc(Kernel._module,1,_oid_(mClaire.it)),
    "",list::empty(Kernel._string));
    Optimize.initModule("Optimize",Compile.it,list::alloc(Kernel._module,2,_oid_(Reader.it),_oid_(mClaire.it)),
    "./compile",list::alloc(Kernel._string,5,_string_(((char*)"osystem")),
      _string_(((char*)"otool")),
      _string_(((char*)"ocall")),
      _string_(((char*)"ocontrol")),
      _string_(((char*)"odefine"))));
    Generate.initModule("Generate",Compile.it,list::alloc(Kernel._module,2,_oid_(Optimize.it),_oid_(mClaire.it)),
    "./compile",list::alloc(Kernel._string,6,_string_(((char*)"gsystem")),
      _string_(((char*)"gexp")),
      _string_(((char*)"gstat")),
      _string_(((char*)"cgen")),
      _string_(((char*)"copt")),
      _string_(((char*)"gusage"))));
    //module load 
    Core.metaLoad();
    Serialize.metaLoad();
    Language.metaLoad();
    Reader.metaLoad();
    Optimize.metaLoad();
    Generate.metaLoad();
    claire.it->comment = "claire";
    mClaire.it->comment = "mClaire";
    Core.it->comment = "Core";
    iClaire.it->comment = "iClaire";
    Serialize.it->version = "v1.0.0";
    Serialize.it->comment = "Serialize";
    Language.it->comment = "Language";
    Reader.it->comment = "Reader";
    Compile.it->comment = "Compile";
    Optimize.it->comment = "Optimize";
    Generate.it->comment = "Generate";
    ClEnv->module_I = claire.it; 
    }
  
void call_main() {default_main();}


  
  class InitLoadModule {
public:
  static InitLoadModule single;
  InitLoadModule() {
    set_load_module(loadModules);
    set_call_main(call_main);
  }
};

InitLoadModule InitLoadModule::single = InitLoadModule();
