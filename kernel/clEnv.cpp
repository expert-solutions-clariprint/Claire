/***********************************************************************/
/**   microCLAIRE                                       Yves Caseau    */
/**   clEnv.cpp                                                        */
/**  Copyright (C) 1998-2003 Yves Caseau. All Rights Reserved.         */
/**  cf claire.h                                                       */
/***********************************************************************/

#include <claire.h>
#include <Kernel.h>
#include <marie.h>
#include <Core.h>

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
OID close_exception(ClaireException *x)
{ ClEnv->exception_I = x;
  avoid_signal_caching = 0;
  if (Core._Zerrassegv->value == Kernel.ctrue) //<sb> true when option -errasegv specified
  		raise(SIGSEGV);
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

ClaireHandler::~ClaireHandler()
{
  	if(COLOR > 0) color(30,0);
}


// system error handling - C++ API ---------------------------------
CL_INT Cerror(CL_INT n, OID a, OID b)
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
CL_INT Cerrorno(CL_INT n, OID a, OID b) {
	#ifdef CLPC
	close_exception((ClaireException *) system_error::make(n,GetLastError(),a,b));
	#else
	close_exception((ClaireException *) system_error::make(n,errno,a,b));
	#endif
	return 0;
}

//<sb>
CL_INT Cerror(CL_INT n, ClaireClass* c, OID a, OID b) {
	close_exception((ClaireException *) system_error::make(n,c,a,b));
	return 0;
}

//<sb>
CL_INT Cerrorno(CL_INT n, ClaireClass* c, OID a, OID b) {
	#ifdef CLPC
	close_exception((ClaireException *) system_error::make(n,GetLastError(),c,a,b));
	#else
	close_exception((ClaireException *) system_error::make(n,errno,c,a,b));
	#endif
	return 0;
}


// create a system_error
system_error *system_error::make(CL_INT n, OID x, OID y)
{system_error *o = (system_error *) ClAlloc->makeAny(4);
  o->isa = Kernel._system_error;
  o->index = n;
  o->cerr = 0;
  o->value = x;
  o->arg = y;
  return o;}

system_error *system_error::make(CL_INT n, CL_INT cerrcode, OID x, OID y)
{system_error *o = (system_error *) ClAlloc->makeAny(4);
  o->isa = Kernel._system_error;
  o->cerr = cerrcode;
  o->index = n;
  o->value = x;
  o->arg = y;
  return o;}

system_error *system_error::make(CL_INT n, ClaireClass* c, OID x, OID y)
{system_error *o = (system_error *) ClAlloc->makeAny(4);
  o->isa = c;
  o->cerr = 0;
  o->index = n;
  o->value = x;
  o->arg = y;
  return o;}

system_error *system_error::make(CL_INT n, CL_INT cerrcode, ClaireClass* c, OID x, OID y)
{system_error *o = (system_error *) ClAlloc->makeAny(4);
  o->isa = c;
  o->cerr = cerrcode;
  o->index = n;
  o->value = x;
  o->arg = y;
  return o;}


/***********************************************************************/
/**                 2: System creation functions                       */
/***********************************************************************/

extern void loadModules();


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
                   loadModules();      // load all the other modules
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
void restore_state_void()
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
	sprintf(sprintfbuf, "%d", n);
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
void stack_add(CL_INT x)
{CL_INT z = ClEnv->base + x;
 if (z + 100 >= ClAlloc->maxStack) // take a range so that the error handler can execute
   error_execution_stack_full();
 OID fill = _oid_(Core.undefined_debug);
 while(ClEnv->index <= z)
	ClEnv->stack[ClEnv->index++] = fill;
 ClEnv->index = z;}

// apply a function on an argument, two arguments or more
OID fcall1(ClaireFunction *f,ClaireClass *s1,OID a1,ClaireClass *s)
{CL_INT x;
   x = ((fptr1) f->value)((CL_INT) CPOINTER(a1,s1));
   return CLAIREOID(x,s);}

OID fcall2(ClaireFunction *f,ClaireClass *s1, OID a1,ClaireClass *s2, OID a2,ClaireClass *s)
{CL_INT x;
   x = ((fptr2) f->value)((CL_INT)CPOINTER(a1,s1), (CL_INT) CPOINTER(a2,s2));
   return CLAIREOID(x,s);}

OID fcall3(ClaireFunction *f,ClaireClass *s1, OID a1,ClaireClass *s2,
           OID a2, ClaireClass *s3, OID a3, ClaireClass *s)
{CL_INT x;
   x = ((fptr3) f->value)((CL_INT)CPOINTER(a1,s1), (CL_INT) CPOINTER(a2,s2),
                          (CL_INT) CPOINTER(a3,s3));
   return CLAIREOID(x,s);}


#define FAPPLY(F,f,l) (((F) f->value)l)
#define AR(m) args[m]

OID stack_apply_function_more(ClaireFunction *f, CL_INT n, CL_INT m, CL_INT i, OID *ct, CL_INT *st);

//<sb> throw an execution stack overflow error
void error_execution_stack_full() {
   if (ClEnv->exception_I == NULL ||
   		!(ClEnv->exception_I->isa == Kernel._system_error &&
   			((system_error*)ClEnv->exception_I)->index == 24))
	   Cerror(24,ClEnv->index,0);
}

// apply a function to a list of arguments placed into the stack (m to n)
//<sb> unrolled for message with 3 or less arguments
OID stack_apply_function(ClaireFunction *f, list *l, CL_INT n, CL_INT m)
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
	 else if (m == 5)	x = FAPPLY(fptr5,f,(AR(0),AR(1),AR(2),AR(3),AR(4)));
	 else if (m == 6)	x = FAPPLY(fptr6,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5)));
	 else if (m == 7)	x = FAPPLY(fptr7,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6)));
	 else if (m == 8)	x = FAPPLY(fptr8,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7)));
	 else if (m == 9)	x = FAPPLY(fptr9,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8)));
	 else if (m == 10)	x = FAPPLY(fptr10,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9)));
	 else if (m == 11)	x = FAPPLY(fptr11,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10)));
	 else if (m == 12)	x = FAPPLY(fptr12,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11)));
	 else if (m == 13)	x = FAPPLY(fptr13,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11),AR(12)));
	 else if (m == 14)	x = FAPPLY(fptr14,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11),AR(12),AR(13)));
	 else if (m == 15)	x = FAPPLY(fptr15,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11),AR(12),AR(13),AR(14)));
	 else if (m == 16)	x = FAPPLY(fptr16,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11),AR(12),AR(13),AR(14),AR(15)));
	 else if (m == 17)	x = FAPPLY(fptr17,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11),AR(12),AR(13),AR(14),AR(15),AR(16)));
	 else if (m == 18)	x = FAPPLY(fptr18,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11),AR(12),AR(13),AR(14),AR(15),AR(16),AR(17)));
	 else if (m == 19)	x = FAPPLY(fptr19,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11),AR(12),AR(13),AR(14),AR(15),AR(16),AR(17),AR(18)));
	 else if (m == 20)	x = FAPPLY(fptr20,f,(AR(0),AR(1),AR(2),AR(3),AR(4),AR(5),AR(6),AR(7),AR(8),AR(9),AR(10),AR(11),AR(12),AR(13),AR(14),AR(15),AR(16),AR(17),AR(18),AR(19)));
	 else Cerror(32,_oid_(f),m);
 return x;
}


// the name of a function
char *string_I_function(ClaireFunction *f)
{ return f->name;}


/*********************************************************************/
/**    5. World functions                                            */
/*********************************************************************/

// defeasible update on a list
OID store_list(list *l, CL_INT n, OID y, ClaireBoolean *b)
{CL_INT *z = (CL_INT*))&(l->content[n]);
   if (b == CTRUE && ClRes->cWorld != 0) STOREOID(z,*z)
   return (*z = y);}

// defeasible update on a list
OID store_array(OID* a, CL_INT n, OID y, ClaireBoolean *b)
{if ARRAYFLOAT(a)
    {double *z = &(((double *) a)[n]);
     if (b == CTRUE && ClRes->cWorld != 0) STOREFLOAT(z,*z)
     return (OID)(*z = float_v(y));}
 else {CL_INT *z = (CL_INT*))&a[n];
       if (b == CTRUE && ClRes->cWorld != 0) STOREOID(z,*z)
       return (OID)(*z = y);}
}

// get the value, even if it is unknown
// we do not need to copy floats anymore since the stack has its own storage
OID store_object(ClaireObject *x, CL_INT n, ClaireClass *s, OID y, ClaireBoolean *b)
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
list *store_add(list *l,OID y)
{if (l->length + 1 == (*l)[0])
	Cerror(43, _oid_(l), l->length);
 if (ClRes->cWorld) STOREOID(&(l->length),l->length)
        return l->addFast(y); //
}

CL_INT worldCongestion() {
	CL_INT good = 1;
	if (ClRes->iIndex >= ClAlloc->maxHist ||
		ClRes->oIndex >= ClAlloc->maxHist ||
		ClRes->fIndex >= ClAlloc->maxHist) {
	good = 0;
	if(ClAlloc->mem_auto && ClAlloc->maxHist < (10000 * (1ul << 9))) {
		void *adr = realloc(ClRes->haiStack, 2 * ClAlloc->maxHist * sizeof(CL_INT*)));
		if(adr) {
			ClRes->haiStack = (CL_INT*)*)adr;
			adr = realloc(ClRes->hviStack, 2 * ClAlloc->maxHist * sizeof(CL_INT));
			if(adr) {
				ClRes->hviStack = (CL_INT*))adr;
				adr = realloc(ClRes->hvoStack, 2 * ClAlloc->maxHist * sizeof(ClaireObject*));
				if(adr) {
					ClRes->hvoStack = (ClaireObject**)adr;
					adr = realloc(ClRes->hafStack, 2 * ClAlloc->maxHist * sizeof(CL_INT*)));
					if(adr) {
						ClRes->hafStack = (CL_INT*)*)adr;
						adr = realloc(ClRes->hvfStack, 4 * ClAlloc->maxHist * sizeof(double));
						if(adr) {
							ClRes->hvfStack = (double*)adr;
							adr = realloc(ClRes->haoStack, 2 * ClAlloc->maxHist * sizeof(CL_INT*)));
							if(adr) {
								ClRes->haoStack = (CL_INT*)*)adr;
								good = 1;
								PortObject *p = ClEnv->cout;
								ClEnv->cout = ClEnv->ctrace;
								princ_string("World stack congestion, increase memory.\n");
								ClEnv->cout = p;
								ClAlloc->maxHist *= 2;}}}}}}}} return good; }

// add one new world
void world_push ()
{if (worldCongestion() == 0) Cerror(37,0,0);
 ClRes->cWorld++;
 ClRes->cWorldId++;                  // v3.2.04
 ClRes->haiStack[++ClRes->iIndex] = (CL_INT *) ClRes->iBase;
 ClRes->iBase = ClRes->iIndex;
 ClRes->haoStack[++ClRes->oIndex] = (CL_INT *) ClRes->oBase;
 ClRes->hvoStack[ClRes->oIndex] = NULL;
 ClRes->oBase = ClRes->oIndex;
 ClRes->hafStack[++ClRes->fIndex] = (CL_INT *) ClRes->fBase;
 ClRes->fBase = ClRes->fIndex;}

// remove a world and perform all modifications stored in the stack
void world_pop ()
{ClRes->cWorldId++;                       // v3.2.04
 if (ClRes->cWorld-- == 0) ClRes->cWorld++;
 else {CL_INT x = ClRes->iIndex + 1, y = ClRes->iBase;
       while (--x != y) {*(ClRes->haiStack[x]) = ClRes->hviStack[x];}
       ClRes->iIndex = y - 1;
       ClRes->iBase = (CL_INT) ClRes->haiStack[y];
       x = ClRes->oIndex + 1; y = ClRes->oBase;
       while (--x != y) {*(ClRes->haoStack[x]) = (CL_INT) ClRes->hvoStack[x];}
       ClRes->oIndex = y - 1;
       ClRes->oBase = (CL_INT) ClRes->haoStack[y];
       x = ClRes->fIndex + 1; y = ClRes->fBase;
       while (--x != y) {*( (double *) ClRes->hafStack[x]) = ClRes->hvfStack[x];}
       ClRes->fIndex = y - 1;
       ClRes->fBase = (CL_INT) ClRes->hafStack[y];}}


// commit: all updates are accepted but the traing info is conserved unless in world 1
void world_remove (void)
{if (ClRes->cWorld <= 1) world_slaughter();
 else { ClRes->cWorld--;
        if (ClRes->cWorld == -1) ClRes->cWorld++;
        CL_INT y = ClRes->iBase;
        ClRes->iBase = (CL_INT) ClRes->haiStack[y];       // v3.2.04: base(n - 1) is restored ...
        ClRes->haiStack[y] = &(ClRes->hviStack[y]);    // .. and the cell for base(n) is neutralized
        y = ClRes->oBase;
        ClRes->oBase = (CL_INT) ClRes->haoStack[y];
        ClRes->haoStack[y] = (CL_INT *) &(ClRes->hvoStack[y]);
        y = ClRes->fBase;
        ClRes->fBase = (CL_INT) ClRes->hafStack[y];
        ClRes->hafStack[y] = (CL_INT *) &(ClRes->hvfStack[y]);}}
       

// this is the tough version that is irreversible
void world_slaughter (void)
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
CL_INT world_number (void)  {return ClRes->cWorld;}

// give the current world
CL_INT world_get_id (void)  {return ClRes->cWorldId;}

/**********************************************************************/
/**    7: signal handling base (xl)                                   */
/**********************************************************************/

CL_INT claire_runs = 0;

#define SIG_STACK_SIZE 32
CL_INT pending_signals[SIG_STACK_SIZE];
CL_INT n_pending_signal = 0;
CL_INT avoid_signal_handling = 0;
CL_INT avoid_signal_caching = 0;
//<sb> in claire we have a generic kernel sig handler
// at the meta level we have a table that maps signals to
// properties (see meta/signal.cl)...
extern ClaireBoolean* meta_sighandler_integer(CL_INT sig);


CL_INT kernel_pop_signal() {
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


void kernel_sighandler_integer(CL_INT sig) {
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
	signal(sig, kernel_sighandler_integer); //<sb> reinstall the signal
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
char* cerror_integer(CL_INT errnum)
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
#ifdef ENOTEMPTY
    case ENOTEMPTY: return "ENOTEMPTY: directory not empty";
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

  sprintf(msg,"unknown error (%d)", errnum);

  return msg;
}

