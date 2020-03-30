/***********************************************************************/
/**   microCLAIRE                                       Yves Caseau    */
/**   claire.h                                                         */
/**  Copyright (C) 1998-99 Yves Caseau. All Rights Reserved.           */
/**  Redistribution and use in source and binary forms are permitted   */
/**  provided that source distribution retains this entire copyright   */
/**  notice and comments.                                              */
/**  THIS SOFTWARE IS PROVIDED AS IS AND WITHOUT ANY WARRANTY,         */
/**  INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF          */
/**  MERCHANTABILTY AND FITNESS FOR A PARTICULAR PURPOSE               */
/***********************************************************************/

// --------------------------------------------------------------------------
// this file is the general public header file for the CLAIRE system
// it contains the important macros, constants and system objects
// --------------------------------------------------------------------------

// ***************************************************************************
// * Table of Contents:                                                      *
// * PART 1: Constants and OID structure                                     *
// * PART 2: CLAIRE system classes (resources)                               *
// * PART 3: CLAIRE class hierarchy                                          *
// * PART 4: CLAIRE Namespaces hierarchy                                     *
// * PART 5: API functions                                                   *
// ***************************************************************************


#ifndef __CLAIRE__
#define __CLAIRE__

#if defined(CLPC) && !defined(CLPCNODLL)
  #define CL_IMPORT __declspec(dllimport)
  #ifndef CL_EXPORT
    #define CL_EXPORT __declspec(dllimport)
  #endif
#else
  #define CL_EXPORT
  #define CL_IMPORT
#endif

#ifdef __LP64__
	#define CL_INT long
	#define CL_UNSIGNED unsigned long
	#define CL_MAX_INT 0xFFFFFFFFFFFFFFFF >> 2
#else
	#define CL_INT int
	#define CL_UNSIGNED unsigned
	#define CL_MAX_INT 0xFFFFFFFF >> 2
#endif



#ifdef CLPC
#	include "winsock2.h"
#	include "winbase.h"
#	include "windows.h"
#	include "winuser.h"
#	include <signal.h>
#	include <stdarg.h>
#	include <stdio.h>
#	include <string.h>
#	include <math.h>
#	include <setjmp.h>
#	include <stdlib.h>
#	include <fcntl.h>
#	include <io.h>
#	include <time.h>
#	include <sys/timeb.h>
#	include <sys/stat.h>
#	include <locale.h>
#	include <ctype.h>
#	include <limits.h>
#	include <malloc.h>
#	include <direct.h>
#	include <conio.h>
#	include <io.h>
#	include <errno.h>
#	include <sys/locking.h>

#	define vsnprintf _vsnprintf
#	define SIGQUIT SIGINT

#	define unlink _unlink
#	define snprintf _snprintf
#	define rmdir _rmdir
#	define chmod _chmod
#	define mode_t int
#	define timegm mktime
#	define open _open
#	define read _read
#	define read _read
#	define popen _popen
#	define pclose _pclose
#	define pipe(fds) _pipe(fds,1024,_O_BINARY)


#	define S_IRUSR _S_IREAD
#	define S_IWUSR _S_IWRITE
#	define S_IRGRP 0
#	define S_IROTH 0

#define PCCONST const

#else

#define PCCONST

#include "config.h"


#if HAVE_STDIO_H
#include <stdio.h>
#endif


#if STDC_HEADERS
#  include <stdlib.h>
#  include <stddef.h>
#else
#  if HAVE_STDLIB_H
#   include <stdlib.h>
#  endif
#endif


#if HAVE_STRING_H
#  if !STDC_HEADERS && HAVE_MEMORY_H
#   include <memory.h>
#  endif
#include <string.h>
#endif

#ifdef HAVE_MALLOC_H
#include <malloc.h>
#endif

#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#else
# ifdef HAVE_SYS_UNISTD_H
#  include <sys/unistd.h>
# endif
#endif

#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#else
#ifdef HAVE_SYS_FCNTL_H
#include <sys/fcntl.h>
#endif
#endif

#if HAVE_PTHREAD_H
#include <pthread.h>
#endif


#if defined(STDC_HEADERS) || defined(__STDC__)
# include <stdarg.h>
#else
# include <varargs.h>
#endif

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#else
#ifdef HAVE_TYPES_H
#include <types.h>
#endif
#endif

#ifdef HAVE_CTYPE_H
# include <ctype.h>
#endif


#if TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif

#ifdef __MVS__
# define MAXHOSTNAMELEN 64
# define TCP_NODELAY 0x01
# define MAXPATHLEN 1024
#else
# include <sys/param.h>
#endif

#include <signal.h>
#include <setjmp.h>
#include <math.h>

#include <locale.h>


#if HAVE_INTTYPES_H
# include <inttypes.h>
#else
# if HAVE_STDINT_H
#  include <stdint.h>
# endif
#endif

#ifdef HAVE_ERRNO_H
#include <errno.h>
#else
#ifdef HAVE_SYS_ERRNO_H
#include <sys/errno.h>
#else
#ifdef HAVE_NET_ERRNO_H
#include <net/errno.h>
#endif
#endif
#endif

#include <sys/utsname.h>


#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#else
#ifdef HAVE_SOCKET_H
#include <socket.h>
#endif
#endif
#ifdef HAVE_SOCKET_EXT_H
#include <socket.ext.h>
#endif

#ifdef HAVE_SYS_UN_H
#include <sys/un.h>
#endif

#ifdef HAVE_NETDB_H
#include <netdb.h>
#endif

#ifdef HAVE_BSDTYPES_H
#include <bsdtypes.h>
#endif

#ifdef HAVE_STDEFS_H
#include <stdefs.h>
#endif

#ifdef HAVE_BSDTIME_H
#include <bsdtime.h>
#endif

#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#else
#ifdef HAVE_SELECT_H
#include <select.h>
#endif
#endif

#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#else
#ifdef HAVE_IN_H
#include <in.h>
#endif
#endif

#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#else
#ifdef HAVE_INET_H
#include <inet.h>
#endif
#endif

#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#else
#ifdef HAVE_STAT_H
#include <stat.h>
#endif
#endif

#ifdef HAVE_PWD_H
#include <pwd.h>
#endif

#ifdef HAVE_DIRENT_H
#include <dirent.h>
#define NAMLEN(dirent) strlen((dirent)->d_name)
#else
#define dirent direct
#define NAMLEN(dirent) (dirent)->d_namlen
#ifdef HAVE_SYS_NDIR_H
#include <sys/ndir.h>
#endif

#ifdef HAVE_SYS_DIR_H
#include <sys/dir.h>
#endif

#ifdef HAVE_DIR_H
#include <dir.h>
#endif
#ifdef HAVE_NDIR_H
#include <ndir.h>
#endif
#endif

#ifdef HAVE_SYS_RESOURCE_H
#include <sys/resource.h>
#endif

#ifdef HAVE_WAIT_H
#include <wait.h>
#else
#ifdef HAVE_SYS_WAIT_H
#include <sys/wait.h>
#endif
#endif

#if HAVE_LIMITS_H
#include <limits.h>
#endif

#if HAVE_ISO_LIMITS_ISO_H
#include <iso/limits_iso.h>
#endif


#if defined(_AIX)
  #define  DLOAD_FLAGS        RTLD_NOW | RTLD_GLOBAL | RTLD_MEMBER
#elif defined(__hpux)           
  #define  DLOAD_FLAGS        BIND_DEFERRED |BIND_VERBOSE| DYNAMIC_PATH
#else
  #define  DLOAD_FLAGS        RTLD_NOW | RTLD_GLOBAL
#endif

#if defined(__hpux)
  #include <dl.h>
#else
  #ifdef HAVE_DLFCN_H
    #include <dlfcn.h>
  #endif
#endif


#endif



// ***************************************************************************
// * PART 1: Constants and OID structure                                     *
// ***************************************************************************

//<sb> in xlclaire OID are unsigned (vs CL_INT in <ycs>) which make the OID arithmetic
// simpler since they are NULL referenced (vs Cmemory[0] in <ycs>)
#ifdef __LP64__
#define OID unsigned long
#else 
#define OID unsigned long
#endif

// special for macOS (CL_INT) x is not allowed by the compiler - v3.4.02
#define ccast(x)  ((long)(size_t) x)        // to remove
#define CCAST(x)  ((long)(size_t) x)        // return the pointer as a long
#define CSTRING(x)  ((char *) x)

// we represent OIDs using 30bits of value and 2 bits of tags
// There are only two types of OID:
//  integer (TAG 0,1,2,3 & C,D,E,F), object (identifiable) and Primitive
//  object, which is used both for primitive and instantiated entities
//   Primitive are: imported (include array, string, port, float) [they are their own sort]
//             bags: lists and  sets
//             functions (external)

#ifdef __LP64__
#define ADDRTRANS 3

#define OBJ_CODE		0x4000000000000000LL    /* objects                           */
#define ADR_MASK		0x3FFFFFFFFFFFFFFFLL  /* the bit mask to get the address        */ /*<sb> fix adr mask was 0x0FFFFFFF */
#define TAG_MASK		0xC000000000000000LL  /* the bit mask to get the tag            */ /*<sb> fix adr mask was 0xF0000000 */
#define INT_MASK		0xC000000000000000LL  /* the first 2 bits */
// we need one value that is NOT a valid OID not the adress of a class
#define NOTHING			0x8000000000000001LL     /* end of list                       */
#define MAX_LOGLIST 50
#else
#define ADDRTRANS 2

#define OBJ_CODE		0x40000000    /* objects                           */
#define ADR_MASK		0x3FFFFFFF  /* the bit mask to get the address        */ /*<sb> fix adr mask was 0x0FFFFFFF */
#define TAG_MASK		0xC0000000  /* the bit mask to get the tag            */ /*<sb> fix adr mask was 0xF0000000 */
#define INT_MASK		0xC0000000  /* the first 2 bits */
// we need one value that is NOT a valid OID not the adress of a class
#define NOTHING			0x80000001      /* end of list                       */
#define MAX_LOGLIST 28
#endif
/** OID macros ---------------------------------------------------------*/

#define CTAG(x) (((CL_UNSIGNED)(x)) & TAG_MASK)
#define INTEGERP(x) ((INT_MASK & ((CL_UNSIGNED)(x))) ^ OBJ_CODE)            // assumes no niet !


#define OBJECT(A,B) ((class A *)((CL_UNSIGNED)(B) << ADDRTRANS))
// #define OBJECT(A,B) ((class A *) &Cmemory[(B & ADR_MASK) + 1])

#define EXPORT(A,B) (A ((ClaireImport *)((CL_UNSIGNED)(B) << ADDRTRANS))->value)
#define IDENTIFIED(x) (((((CL_UNSIGNED)x) & TAG_MASK) ^ OBJ_CODE) || \
                       (OBJECT(ClaireAny,x)->isa->ident_ask == CTRUE))

#ifdef __LP64__
#define _oid_(A) (OBJ_CODE | ((CL_UNSIGNED)(A) >> ADDRTRANS))
#define _array_(A) (OBJ_CODE | ((((CL_UNSIGNED)((OID*)(A) - 2))) >> ADDRTRANS))
#define _char_(c) (ClRes->ascii[((unsigned char)(c))])
#else
#define _oid_(A) (OBJ_CODE | ((CL_UNSIGNED)(A) >> ADDRTRANS))
#define _array_(A) (OBJ_CODE | ((((CL_UNSIGNED)((OID*)(A) - 2))) >> ADDRTRANS))
#define _char_(c) (ClRes->ascii[((unsigned char)(c))])
#endif

#define _void_(x) (x,1)
#define _function_(f,s) ClAlloc->makeFunction((fptr) (f), (s))
#define _string_(x) ClAlloc->import(Kernel._string,(OID *) (x))

#define float_v(n) (OBJECT(ClaireFloat,n)->value)
#define char_v(n) (OBJECT(ClaireChar,n)->ascii)
#define string_v(B) ((char *) OBJECT(ClaireImport,B)->value)
#define array_v(A) (((OID *)((CL_UNSIGNED)(A) << ADDRTRANS)) + 2)


// these constant are used for the method status
// note that they are bitvectors whereas in CLAIRE they are indices
#define NEW_ALLOC (1LL << 1)        // a new allocation may be done by running the method
#define BAG_UPDATE (1LL << 2)       // a list is updated whose content is not gcsafe
#define SLOT_UPDATE (1LL << 3)      // a slot is updated whose content is not gcsafe
#define RETURN_ARG (1LL << 4)       // returns one of the input arg
#define SAFE_RESULT (1LL << 5)      // the result (not gcsafe) does not need protection
                                  // mostly because it was protected internally
#define SAFE_GC (1LL << 6)          // the arguments do not need to be protected although
                                  // an allocation may occur in the method, mostly because the
                                  // arguments are pushed on the stack !

// local useful macro (v3.2.26) is a float close to nice decimal number
// v3.2.50 try to make it stricter
#define DECIMAL(x) ((x * 1e5 - (CL_INT)floor(x * 1e5) < 1e-6) ||  ((CL_INT)ceil(x * 1e5) - x * 1e5 < 1e-6))

/* declare function pointers for functions with arbitrary args */
#ifdef CLPC
typedef CL_INT (*fptr) (CL_INT);
#else
typedef CL_INT (*fptr) (...);
#endif


extern CL_EXPORT CL_INT TOPLEVEL;
extern CL_EXPORT CL_INT LOGO; //<sb> logo/nologo -> clConsole
extern CL_EXPORT CL_INT COLOR; //<sb> color support -> clConsole
extern CL_EXPORT CL_INT current_color;
extern CL_EXPORT CL_INT current_bold;
extern CL_EXPORT void color(CL_INT c, CL_INT bold);

//<sb> tell that claire as been allocated and loaded
extern CL_EXPORT CL_INT claire_runs;

//<sb> a general signal handler at the Kernel level
extern CL_EXPORT void kernel_sighandler_integer(int sig);
extern CL_EXPORT OID gc_error();
extern CL_EXPORT void error_execution_stack_full();

// forward definitions
class CL_EXPORT ClaireClass;
class CL_EXPORT ClaireChar;
class CL_EXPORT ClairePrimitive;
class CL_EXPORT ClaireException;
class CL_EXPORT ClaireFloat;
class CL_EXPORT ClaireFunction;
class CL_EXPORT ClaireImport;
class CL_EXPORT ClairePort;
class CL_EXPORT PortObject;
class CL_EXPORT FileObject;
class CL_EXPORT ClaireBoolean;
class CL_EXPORT ClaireObject;
class CL_EXPORT ClaireType;
class CL_EXPORT module;
class CL_EXPORT ClaireAny;
class CL_EXPORT bag;
class CL_EXPORT list;
class CL_EXPORT symbol;

extern CL_EXPORT CL_INT Cerror(CL_INT n, OID a, OID b);
extern CL_EXPORT CL_INT Cerrorno(CL_INT n, OID a, OID b); //<sb> gives back the C err code
extern CL_EXPORT CL_INT Cerror(CL_INT n, ClaireClass* c, OID a, OID b); //<sb>
extern CL_EXPORT CL_INT Cerrorno(CL_INT n, ClaireClass* c, OID a, OID b); //<sb> gives back the C err code

// ***************************************************************************
// * PART 2: CLAIRE system resources                                         *
// ***************************************************************************

// resource object: manages the symbol table and the worlds
// the object ClRes is the unique instance and can be passed to CLAIRE runtime
//
class CL_EXPORT ClaireResource
{public:
   ClaireChar* *ascii;
   CL_INT   iBase;                         // start of current world in stack
   CL_INT   iIndex;                        // top of stack
   OID*  *haiStack;                     // address part of the stack
   OID   *hviStack;                     // value part of the stack
   OID   oBase;                         // start of current world in stack
   CL_INT   oIndex;                        // top of stack
   OID*  *haoStack;                     // address part of the stack
   ClaireObject*  *hvoStack;            // value part of the stack
   CL_INT   fBase;                         // start of current world in stack
   CL_INT   fIndex;                        // top of stack
   double* *hafStack;                    // address part of the stack
   double *hvfStack;                    // value part of the stack
   CL_INT   cWorld;                        // current world number
   CL_INT   cWorldId;                      // v3.2.04: a unique ID for each world
   symbol* *sTable;                     // symbol hash table

 static void run();
 void init();

 CL_INT hashOid(CL_INT mask, OID x);

 };
   

// each handler is represented by a structure that contains the "environment" that
// must be restored
class CL_EXPORT ClaireHandler {
  CL_INT sIndex;          // keep the stack index
  CL_INT sBase;           // keep the stack base
  CL_INT debug;           // keep the debug info ????
  CL_INT trace;           // keep the trace info
  CL_INT gIndex;          // keep the gc stack index
  CL_INT gBase;           // keep the gc stack base
  PortObject *ecout;	//<sb> keep the current output

  public:
  ClaireHandler();     // constructor (use C++ alloc)
  void catchIt();      //
  };


#define OPTIMIZE 6          /*size of the basic object (has to be even) */

// C++ allocator
class CL_EXPORT ClaireAllocation
{// private stuff
public:
 CL_INT entryList[MAX_LOGLIST + 1];                     // keep track of free chunks by size
 CL_INT newChunk(CL_INT n);         // chunk allocation
 CL_INT gcChunk(CL_INT n, CL_INT size, CL_INT *value, CL_INT *i);
 CL_INT newShort(CL_INT n);            // short object allocation
 CL_INT newLong(CL_INT n);
 CL_INT freeChunk(CL_INT n);           // free an unused chunk
 CL_INT freeLoop(CL_INT n);
 CL_INT freeSimple(CL_INT n,CL_INT size);
 CL_INT mergeRight(CL_INT a, CL_INT b, CL_INT size);
 CL_INT mergeLeft(CL_INT a, CL_INT b, CL_INT size);
 void freeObject(CL_INT n);
 void freeString(char *s);

 void markHash();                // mark the content of the hash table
 void markStack();               // mark the items in the various stacks
 void mark(OID n);               // marks anything seen
 void markObject(ClaireObject *x);
 void markPrimitive(ClairePrimitive *x);
 void markBag(bag *s);
 void markString(char *s);
 void markArray(OID* a);
 void markFreeableContainer();
 void sweepChunk();
 void samplerSweepChunk();
 void sweepObject();
 void samplerSweepObject();
 void sweepFreeable();
 void updateFreeme();

 CL_INT chunk_used;
 CL_INT short_used;
 CL_INT rchunk_used;
 CL_INT rshort_used;


 CL_INT string_used;
 CL_INT object_used;
 CL_INT bag_used;
 CL_INT array_used;
 CL_INT symbol_used;

 CL_INT chunkCongestion();
 CL_INT shortCongestion();
 CL_INT increaseChunk();
 CL_INT increaseShort();
 
 CL_INT checkChunkIncrease(CL_INT idx, CL_INT n);

// void chunckDecongestion();
 
public:

 CL_INT gcStackCongestion();

 void freeAllFreeable();                //<sb> called at exit to free all freeable objects

 //<sb> memory sampler
 void open_sample_file(CL_INT);
 void close_sample_file();
 void sample_once();

 CL_INT statusGC;                          // 0:normal, 1:dump, 2:noGC
 CL_INT numGC;                             // num of calls to garbage collector
 ClaireAny *probe;                      // for debuging purposes
 CL_INT maxStack, maxHist, maxEnv,         // parameters for memory allocation
     maxGC, maxHash,maxList0,maxList,maxSize0,maxSize,maxMem;
 CL_INT hashMask;                          // hashing mask for symbol table
 CL_INT logList;                           // log size of chunk zone
 CL_INT usedCells;                         // book-keeping
 CL_INT firstFree;                         // current start of long free zone
 CL_INT alertFree;                         // current start of long free zone
 CL_INT nextFree;                          // start of the small object chain
 ClaireAny* *gcStack;                   // stack for protecting variable's content
 CL_INT index,base;                        // stack management variables
 CL_INT freeingAll;
 ClaireObject *currentNew;              // pointer to what is currently allocated
 ClaireObject *currentType;              //<sb> pointer to what is currently allocated for bags
										// note: we need a different value than currentNew since
										// addSlot/ClaireClass::make can build typed bag...
 CL_INT delayedThings;						//<sb> GC flag that reduce the GC recursivity

 CL_INT mem_auto;
 
 CL_INT tracked_oid;
 CL_INT track_count;

 CL_INT consumed_exec;					//<sb> time congestion interface
 CL_INT origin_exec;
 CL_INT consumed_gc;
 CL_INT chunk_hits;
 CL_INT object_hits;

 //<sb> made log2up inline
 // memory management
 static CL_INT log2up(CL_INT n)              // log - test in v3.2.38 use static methods properly ....
 	{CL_INT value;
  	for (value = 1; (n != 1);) {n = n >> 1; ++value;}
  	return(value);}

 ClaireAny *makeStatic(CL_INT n);          // static object allocation
 char *makeString (CL_INT n);              // string (char*) allocation
 OID *makeArray (CL_INT n, ClaireType *t); // array allocation

 OID *makeContent (CL_INT n)              // bag's content allocation (NOT THE BAG itself)
 	{CL_UNSIGNED x =
		(n < OPTIMIZE-1 ? newShort(OPTIMIZE - 1) : newChunk(n));
	return (OID*)((CL_UNSIGNED)x << ADDRTRANS);}

 void freeContent(OID* x)				//<sb> free the content of a reallocated list
	{CL_INT u = ((CL_UNSIGNED)x >> ADDRTRANS);
	if (*x < OPTIMIZE) freeObject(u);
	else freeChunk(u); }

 ClaireAny *makeAny(CL_INT n)             // simple allocation for an object
 	{CL_INT m = ((n < OPTIMIZE) ? newShort(n) : newChunk(n));
 	return (ClaireAny *)(((CL_UNSIGNED)m + 1) << ADDRTRANS);}

 OID import(ClaireClass *c,OID *n);     // imports into a claire OID
 ClaireFloat *makeFloat();                       // allocates the memory for a ClaireFloat
 ClaireFunction *makeFunction(fptr f, char *s);  // creates a ClaireFunction

 void gc(char *s);                  // call the garbage collector
 void init();                       // allocate the memory zones
 void kill(OID n);                  // deallocates an ClaireAny
 void memStat();
 list *memList(ClaireBoolean *x);
 

  void gc_bind() {
	if (index < maxGC || gcStackCongestion()) {
		gcStack[index] = (ClaireAny *)(base);
		base = index;
		index++;
	} else gc_error();
  }

  void gc_unbind() {
	index = base;
	base = (CL_INT)gcStack[index];
  }

	// reserves n slots in the garbage stack
  void gc_reserve(CL_INT n) {
	if (index + n + 1 < maxGC || gcStackCongestion()) {
		CL_INT i = index, j = i + n + 1;
		gcStack[i] = (ClaireAny *)base;
		base = i++;
		for (; i <= j; i++) gcStack[i] = NULL;
		index = j;
	} else gc_error();
  }

};


extern CL_EXPORT CL_INT freeClaire();
extern CL_EXPORT CL_INT startClaire(CL_INT i, CL_INT j, CL_INT memauto);
extern CL_EXPORT CL_INT startClaire(CL_INT argc, char *argv[]);

// ***************************************************************************
// * PART 3: CLAIRE Namespaces hierarchy                                     *
// ***************************************************************************

// A namespace is a root class for the namespaces that we will generate for each module:
// if m is a CLAIRE module, we create
//   mClass, a subclass of NameSpace
//   m is a C++ instance of mClass, with a slot it that points to the
//   module object
class CL_EXPORT NameSpace
{public:
   module *it;                  // the module associated to the namespace
   void initModule(char *name, module *father);       // simple version for kernel
   void initModule(char *name, module *father,list* usage, char *dir, list *files);       // more complex version
};

// the root of all modules is represented directly with a global variable (claire)
// the "claire namespace" only owns a few constants (CTRUE,...),
// represented with C++ variables
extern CL_EXPORT NameSpace claire;
extern CL_EXPORT NameSpace mClaire;
extern CL_EXPORT ClaireBoolean *CTRUE;
extern CL_EXPORT ClaireBoolean *CFALSE;
extern CL_EXPORT OID CNULL;
extern CL_EXPORT ClaireResource *ClRes;
extern CL_EXPORT ClaireAllocation *ClAlloc;     // Alloc object

extern CL_EXPORT OID *Cmemory;                  // memory zone
extern CL_EXPORT OID *CmemoryMax;


extern CL_EXPORT CL_INT isforked;
extern CL_EXPORT CL_INT lastforked;


extern CL_EXPORT CL_INT n_pending_signal;
extern CL_EXPORT CL_INT avoid_signal_handling;
extern CL_EXPORT CL_INT avoid_signal_caching;

// ***************************************************************************
// * PART 4: API functions & macros                                          *
// ***************************************************************************

//   1. C++ functions --------------------------------------------------------
extern CL_EXPORT void Ctracef(char* format, ...);
extern CL_EXPORT CL_INT kernel_pop_signal();

// 2:  MACROS  ------------------------------------------------------------------
// these are the public macros that are described in the microCLAIRE guide

#define CLREAD(A,B,C) ((class A *) B)->C
#define OWNER(x) (((INT_MASK & x) != OBJ_CODE) ? Kernel_integer : OBJECT(ClaireAny,x)->isa)
#define OPT_EVAL(x) (((INT_MASK & x) == OBJ_CODE) ? \
      ((fptr1) OBJECT(ClaireAny,x)->isa->evaluate->value)((CL_INT) OBJECT(ClaireAny,x)) : x)

// OTRUEP(x) works on an OID and TRUEP(x) on a ClaireAny
#define TRUEP(x) (boolean_I_ClaireAny(x) == CTRUE)
#define OTRUEP(x) (boolean_I_any(x) == CTRUE)
#define FALSEP(x) (boolean_I_ClaireAny(x) == CFALSE)

#ifdef CLDEBUG
extern CL_INT clbug(); // /*Cerror(-2,(CL_INT) __FILE__,__LINE__)*/
#define ASSERT(x) ((x) ? (CL_INT) NULL : \
						(Ctracef("Assertion violation in file %s [line %d]\n",__FILE__,__LINE__), \
						clbug()))
#else
#define ASSERT(x) NULL
#endif


/** 2.b simplifies the generated code -----------------------------------*/

#define INHERIT(self,ens) (ens->ancestors->length <= self->ancestors->length && \
                           self->ancestors->content[ens->ancestors->length] == _oid_(ens))


#define PUSH(A)  (ClEnv->stack[ClEnv->index] = (A), ClEnv->index++)


#define BCONTAIN(s,x) (((s >> x) & 1) == 1)


#define POP_SIGNAL {if (n_pending_signal) kernel_pop_signal();}

/* macros for the GC protection */
#define GC_RESERVE(n) ClAlloc->gc_reserve(n)
#define GC_BIND ClAlloc->gc_bind()
#define GC_UNBIND ClAlloc->gc_unbind()

static inline ClaireAny* GC_ANY(ClaireAny* x) {
	if(ClAlloc->index >= ClAlloc->maxGC && ClAlloc->gcStackCongestion() == 0) gc_error();
	ClAlloc->gcStack[ClAlloc->index++] = x; return x;}

static inline ClaireAny* GC__ANY(ClaireAny* x, CL_INT y) {
	ClAlloc->gcStack[ClAlloc->base + y] = x;
	return x;
}


#define GC_LOOP (gc_local = ClAlloc->index)
#define GC_UNLOOP (ClAlloc->index = gc_local)

// save version of GC_ANY is re-introduced in v3.2.30
static inline ClaireAny* GC_PUSH(ClaireAny* x) {
	if(ClAlloc->index >= ClAlloc->maxGC && ClAlloc->gcStackCongestion() == 0) gc_error();
	ClAlloc->gcStack[ClAlloc->index++] = x; return x;}


/* tells where the string is allocated */
#define CLMEM(s) (((CL_UNSIGNED) s > (CL_UNSIGNED)Cmemory) && ((CL_UNSIGNED) s < (CL_UNSIGNED)CmemoryMax))

// push an OID on the GC stack 
static inline OID GC_OID(OID n)
  {if (CTAG(n) == OBJ_CODE) GC_ANY(OBJECT(ClaireAny,n));
   return n;}

static inline OID GC__OID(OID n, CL_INT m)
   {if (CTAG(n) == OBJ_CODE) GC__ANY(OBJECT(ClaireAny,n),m);
	return n;}

static inline char *GC_STRING(char *s)
	{ return CLMEM(s) ? (GC_ANY((ClaireAny *)((CL_INT*)s - 2)), s) : s; }

static inline char *GC__STRING(char *s, CL_INT n)
	{ if CLMEM(s) GC__ANY((ClaireAny *)((CL_INT*)s - 2), n);
		return s; }

// array
static inline OID *GC_ARRAY(OID *a)
{GC_ANY((ClaireAny*)(a - 2));
 return a;}


#define GC_OBJECT(y,x) ((class y *) GC_ANY(x))



// macros for safe bag iterations (the bag does NOT change)
// {OID *CLcurrent,*CLlast,x;
//      for ( START(S); NEXT(x); )  ....  iterates over the bag S (no updates on S !)
// a safer way is  (to be used by the compiler)
//      for (i = 0;(i <= S.length & x = S.content[i]) ; )
#define ITERATE(x) OID *CLcurrent,*CLlast,x
#define START(S) (CLlast = &((CLcurrent = S->content)[S->length - 1]))
#define NEXT(x) (CLcurrent++ <= CLlast && (x = *CLcurrent, 1))
// #define LIST_OF(l) GC_PUSH(make_list_integer(NTH(l,0),0))

/* macros for exceptions */
#define ERROR_IN  (setjmp(ClEnv->handlers[ClEnv->cHandle]) == 0)
#define PREVIOUS_HANDLER  {longjmp(ClEnv->handlers[--ClEnv->cHandle],3);}
#define ERROR_FREE  {ClEnv->cHandle--;}

extern CL_EXPORT CL_INT worldCongestion();


// objects and primitive
static inline ClaireObject* STOREREF(ClaireObject* y)
{
  if (ClRes->cWorld != 0)
  {
    if (++ClRes->oIndex < ClAlloc->maxHist || worldCongestion())
    {
      ClRes->haoStack[ClRes->oIndex] = NULL;
      ClRes->hvoStack[ClRes->oIndex] = y;
    } else Cerror(37,0,0);
  }
  return y;
}


// three storage macro for defeasible updates (depend on sort of y)
// integer and OIDs
/*
#define STOREI_(x,y) ((x != y) ? ((ClRes->cWorld != 0) ? \
        ((++ClRes->iIndex < ClAlloc->maxHist || worldCongestion()) ? \
         (x = (ClRes->hviStack[ClRes->iIndex] = \
                  *(ClRes->haiStack[ClRes->iIndex] = ((CL_INT *) &(x))), y)) : \
          Cerror(37,0,0)) : \
          (x = y)) : 0 )
*/
static inline CL_INT STOREI(ClaireObject *obj,CL_INT *x,CL_INT y)
{
  STOREREF(obj);
	return ((*x != y) ? ((ClRes->cWorld != 0) ? \
        ((++ClRes->iIndex < ClAlloc->maxHist || worldCongestion()) ? \
         (*x = (ClRes->hviStack[ClRes->iIndex] = \
                  *(ClRes->haiStack[ClRes->iIndex] = ((OID *)(x))), y)) : \
          Cerror(37,0,0)) : \
		(*x = y)) : 0 );
}

static inline CL_INT STOREI(CL_INT *x,CL_INT y)
{
  return ((*x != y) ? ((ClRes->cWorld != 0) ? \
        ((++ClRes->iIndex < ClAlloc->maxHist || worldCongestion()) ? \
         (*x = (ClRes->hviStack[ClRes->iIndex] = \
                  *(ClRes->haiStack[ClRes->iIndex] = ((OID *)(x))), y)) : \
          Cerror(37,0,0)) : \
    (*x = y)) : 0 );
}



/*static inline unsigned CL_INT STOREI(unsigned CL_INT *x,unsigned CL_INT y)
{
	return  unsigned CL_INT STOREI((CL_INT*))x,y);
}*/

static inline unsigned CL_INT STOREI(ClaireObject *o,unsigned CL_INT *x,unsigned CL_INT y)
{
	return (unsigned CL_INT)STOREI(o,(CL_INT*)x,(CL_INT)y);
}

/*
static inline CL_INT STOREI(ClaireObject *x,int y)
{
	return (CL_INT)STOREI((CL_INT*))x,(CL_INT)y);
}

static inline unsigned CL_INT STOREI(ClaireObject *x,unsigned CL_INT y)
{
	return (unsigned int)STOREI((CL_INT*))x,(CL_INT)y);
}
*/
/*

// objects and primitive
#define STOREO(x,y) ((x != y) ? ((ClRes->cWorld != 0) ? \
        ((++ClRes->oIndex < ClAlloc->maxHist || worldCongestion()) ? \
         (x = (ClRes->hvoStack[ClRes->oIndex] = (ClaireObject *) \
                  *(ClRes->haoStack[ClRes->oIndex] = ((CL_INT *) &(x))), y)) : \
          (Cerror(37,0,0),y)) : \
          (x = y)) : y )

*/

static inline ClaireObject * STOREO(ClaireObject*o,ClaireObject **x,ClaireObject *y)
{
  STOREREF(o);
	return ((*x != y) ? ((ClRes->cWorld != 0) ? \
		((++ClRes->oIndex < ClAlloc->maxHist || worldCongestion()) ? \
         (*x = (ClRes->hvoStack[ClRes->oIndex] = (ClaireObject *) \
                  *(ClRes->haoStack[ClRes->oIndex] = ((OID *) (x))), y)) : \
          (Cerror(37,0,0),y)) : \
		(*x = y)) : y );
}



/*        ((++ClRes->oIndex < ClAlloc->maxHist || worldCongestion()) ? \
         (ClRes->hvoStack[ClRes->oIndex] = (ClaireObject *)NULL, y) : \
          (Cerror(37,0,0),y)) */
	

// floats
/*
#define STOREF_(x,y) ((x != y) ? ((ClRes->cWorld != 0) ? \
        ((++ClRes->fIndex < ClAlloc->maxHist || worldCongestion()) ? \
         (x = (ClRes->hvfStack[ClRes->fIndex] = \
                  *( (double *) (ClRes->hafStack[ClRes->fIndex] = ((CL_INT *) &(x)))), y)) : \
          Cerror(37,0,0)) : \
          (x = y)) : y )
*/
static inline double STOREF(ClaireObject* o,double *x,double y)
{
  STOREREF(o);
	if (*x != y && ClRes->cWorld != 0)
	{
		if (++ClRes->fIndex < ClAlloc->maxHist || worldCongestion())
		{
			ClRes->hvfStack[ClRes->fIndex] = *x;
			ClRes->hafStack[ClRes->fIndex] = x;
			*x = y;
		} else Cerror(37,0,0);
	}
	return y;
}

// new in v3.2: give the address of a slot
extern CL_EXPORT CL_INT *CL_dummy;
#define CL_IDX(c,s) (1 + ((((CL_INT) &(((c *) CL_dummy)->s)) - (CL_INT) CL_dummy) / sizeof(OID)))  
#define CL_ADDSLOT(c,CC,p,r,v) c->addSlot(p,r,v,CL_IDX(CC,p))  
#define CL_ADD_SLOT(c,CC,p,PP,r,v) c->addSlot(p,r,(unsigned CL_INT)v,CL_IDX(CC,PP))


extern CL_EXPORT void symbolDebug(symbol *s);
extern CL_EXPORT void seeIt(char *s, OID x);

// macros for reading
#define CHANGE(x,y) ((x != y) ? ((x = y), 1) : 0)
#define KNOWN(p,y) ((y == CNULL) ? (Cerror(38,_oid_(p),0),y) : y)
#define NOTNULL(p,y) ((y == NULL) ? (Cerror(38,_oid_(p),0),y) : y)



#endif
