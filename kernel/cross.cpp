// --- System configuration file for "claire" , ["Sun Jan 18 12:45:05 2009\n"] ---

#include <claire.h>
#include <Kernel.h>
#include <Core.h>

extern void loadModules();
extern void call_main();

class InitCross {
public:
	static InitCross single;
	InitCross() {
    set_load_module(loadModules);
    set_call_main(call_main);
	}
};

InitCross InitCross::single = InitCross();
