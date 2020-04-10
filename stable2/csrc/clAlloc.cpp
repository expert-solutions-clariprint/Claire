/***********************************************************************/
/**   microCLAIRE                                       Yves Caseau    */
/**   clAlloc.cpp                                                      */
/**  Copyright (C) 1998-2003 Yves Caseau. All Rights Reserved.         */
/**  cf claire.h                                                       */
/***********************************************************************/

#include <claire.h>
#include <Kernel.h>
#include <marie.h>
#include <Core.h>


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
CL_INT *CL_dummy;       // not used really
CL_INT numSample = 0;

// debug version that can be instrumented
CL_INT GC_DEBUG(CL_INT n)
  { return n;}

// we use a special object to represent the allocator
// we could use a class with static methods but this is more homogeneous
ClaireAllocation *ClAlloc;

OID *Cmemory;                  // memory zone
OID *CmemoryMax;

OID CmemoryAdr;                  // memory zone

// macros for this file -------------------------------------------------
#define CAR 1
#define FOLLOW 2
#define PREVIOUS 3
// x is a pointer, returns the ADR (faster than ADR(_oid_(x))

#ifdef _LP64_
#define POINTOADR(x) ((CL_INSIGNED)x >> 3)
#define ADRTOPOIN(x) ((CL_INSIGNED*)((CL_INSIGNED)x << 3))
#define SIZE(n) (*((CL_INT*)((CL_INSIGNED)n << 3) - 1))             // returns the size of the object
#else
#define ADDRTRANS 3

#define POINTOADR(x) ((CL_UNSIGNED)x >> ADDRTRANS)
#define ADRTOPOIN(x) ((CL_UNSIGNED*)((CL_UNSIGNED)x << ADDRTRANS))
#define SIZE(n) (*((CL_INT*))((CL_UNSIGNED)n << ADDRTRANS) - 1)             // returns the size of the object
#else
#define ADDRTRANS 2

#define POINTOADR(x) ((CL_UNSIGNED)x >> ADDRTRANS)
#define ADRTOPOIN(x) ((CL_UNSIGNED*)((CL_UNSIGNED)x << ADDRTRANS))
#define SIZE(n) (*((CL_INT*))((CL_UNSIGNED)n << ADDRTRANS) - 1))             // returns the size of the object
#endif


//#define CLDEBUG


#ifdef CLDEBUG              // little trick to check that values are OK


static CL_INT from_kill_I = 0;


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
{if (n == NOTHING || (n > 0 && n - CmemoryAdr < ClAlloc->maxList)) return n;
 else return clbug();}
#else
#define ISCHUNK(n) n
#endif

#define MAXLIST_OFFSET 2

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
	CHECKED_ALLOC(ClRes->ascii, ClaireChar*, 256)
	CHECKED_ALLOC(ClRes->haiStack, CL_INT*, maxHist) // address part of the stack
	CHECKED_ALLOC(ClRes->hviStack, int, maxHist) // value part of the stack
	CHECKED_ALLOC(ClRes->haoStack, CL_INT*, maxHist) // address part of the stack
	CHECKED_ALLOC(ClRes->hvoStack, ClaireObject*, maxHist) // value part of the stack
	CHECKED_ALLOC(ClRes->hafStack, OID*, maxHist) // address part of the stack
	CHECKED_ALLOC(ClRes->hvfStack, double, maxHist) // value part of the stack
	CHECKED_ALLOC(gcStack, ClaireAny*, maxGC) // GC stack  (v 3.2.38)
	CHECKED_ALLOC(Cmemory, OID, maxSize0+1) // GC stack  (v 3.2.38)
	//<sb> mem upper bound for CLMEM check
	CmemoryMax = Cmemory + maxSize0;
	CmemoryAdr = ((CL_UNSIGNED)Cmemory >> ADDRTRANS);
	//<sb> flag that tell if claire exits -> can we free stdio (cf clPort) ?
	freeingAll = 0;
	nextFree = NOTHING;
	firstFree = maxList0 + MAXLIST_OFFSET;    // needs to be even for alignment ! used in sweep
	alertFree = maxList0 + 5 * maxSize / 6;
	maxMem = maxList0 + maxSize;
	mem_auto = (maxMem != maxSize0);
	if(mem_auto) alertFree = maxList0 + 7 * maxSize / 10;
	else alertFree = maxList0 + 5 * maxSize / 6;
	statusGC = 0;              // we like GC, don't we ?
	for (i=0; i <= maxHash; i++) ClRes->sTable[i] = NULL;
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
	ClEnv = (ClaireEnvironment*)makeStatic(sizeof(ClaireEnvironment) / sizeof(CL_INT) + 2);
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
	if(LOGO) fprintf(stdout,"Loglist = %d\n", ClAlloc->logList);
	ClAlloc->maxList = (1ul << (18 + i));
	ClAlloc->maxSize = (1ul << (18 + i));
	if(memauto) {
		ClAlloc->maxList0 = (1ul << (18 + 9));
		ClAlloc->maxSize0 = (2ul << (18 + 9));
		ClAlloc->maxStack = 8000 * (1ul << 9);
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
CL_INT freeClaire() {
	claire_runs = 0;
	free(ClEnv->stack);
	free(ClEnv->handlers);
	free(Cmemory);
	free(ClAlloc->gcStack);
	free(ClRes->hvfStack);
	free(ClRes->hafStack);
	free(ClRes->hvoStack);
	free(ClRes->haoStack);
	free(ClRes->hviStack);
	free(ClRes->haiStack);
	free(ClRes->ascii);
	free(ClRes->sTable);
	delete ClRes;
	delete ClAlloc;
	return 1; }

// bbn check memory params before allocation stuff
CL_INT startClaire(CL_INT i, CL_INT j, CL_INT memauto) {
	if (claire_runs == 1) return 0;
	ClAlloc = 0; ClRes = 0;
	return i < 0 || i >= 20 || j < 0 || j >= 20 ? 0 :
				allocateClaire(i,j,memauto);
}

// -qonerror option "Quit on error?"
// claire will exit on the first exception
// with an error code of 0
CL_INT QONERROR = 0;
CL_INT NOEL = 0;
CL_INT SAMPLE_PERIOD = 0;
CL_INT MEM_AUTO = 0;

extern void parse_command_line_void1();
extern void call_main();
extern void claire_started();


CL_INT startClaire(CL_INT argc, char *argv[]) {
	if (claire_runs == 1) return 0;
	CL_INT l; CL_INT q = 0; CL_INT code = 0; CL_INT main_err = 0;
	CL_INT i = 3, j = 3;
	CL_INT memauto = 0;
	CL_INT add_x_option = 0;
	if(getenv("SERVER_SOFTWARE")) // we should be a CGI -> no readline, no logo
		{ NOEL = 1; LOGO = 0; }
	for (l = 1;l < argc; l++) { // hanlde some options
		if (l == 1 && isfile_ask_string(argv[l])) {
			add_x_option = 1;
			LOGO = 0;
			NOEL = 1;
		} else if(strcmp(argv[l], "-h")==0) {
			LOGO = 0;
			NOEL = 1;
		} else if(strcmp(argv[l], "-sample")==0) {
			if(++l == argc) break;
			SAMPLE_PERIOD = atoi(argv[l]);
		} else if(strcmp(argv[l],"-x") == 0 || strcmp(argv[l],"-xe") == 0 ||
				sscanf(argv[l],"-x%d-%d",&i,&j) == 2 || sscanf(argv[l],"-xe%d-%d",&i,&j) == 2) {
			if(++l == argc) break;
			LOGO = 0;
			NOEL = 1;
		} else if(strcmp(argv[l],"-xwcl") == 0 || sscanf(argv[l],"-xwcl%d-%d",&i,&j) == 2) {
			if(++l == argc) break;
			LOGO = 0;
			NOEL = 1;
		} else if(strcmp(argv[l],"-qonerror") == 0) QONERROR = 1;
		else if(strcmp(argv[l],"-nologo") == 0) LOGO = 0;
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
	if(LOGO)
		fprintf(stdout,"%s memory size by 2^%d and 2^%d, ", increase ? "increase" : "default", i, j);
	if(startClaire(i, j, memauto) == 0) { // try to allocate claire memory
		fprintf(stdout,"error: failed to allocate CLAIRE memory, try claire -s 0 0\n");
		fprintf(stdout,"bye...\n");
		exit(1); // exit with error code if failed to allocate memory 
	}

	GC_BIND;
	ClEnv->params = list::empty();
	for (i=0; i<argc; i++) {
		if (i == 1 && add_x_option)
			ClEnv->params->addFast(_string_("-x"));
		ClEnv->params->addFast(_string_(argv[i]));
	}
	GC_UNBIND;
	
	ClaireHandler c_handle = ClaireHandler();
	if ERROR_IN {
		claire_started();
		if(SAMPLE_PERIOD)
			ClAlloc->open_sample_file(SAMPLE_PERIOD);
		call_main();
		parse_command_line_void1();
		CL_exit(0);
	} else {
		c_handle.catchIt();
		ClEnv->cout = OBJECT(PortObject,Core.Clib_stderr->value);
		print_any(_oid_(ClEnv->exception_I));
		CL_exit(1);
	}
	return 1;
}

void CL_exit(CL_INT i) {
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
CL_INT CL_system(char *s) { return system(s); }
	
//<sb> a dynamic allocation failed
void CL_error_alloc() {
	claire_runs = 0;
	fprintf(stdout,"There is not enough memory for CLAIRE, try claire -s 0 0\n");
	fprintf(stdout,"bye...\n");
	exit(1);
}


CL_INT ClaireAllocation::increaseChunk() {
 	if(maxList == maxList0 || logList >= 27) return 0;
	logList++;
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
	if(mem_auto && maxGC < 20000 * (1ul << 9)) {
		void *adr = realloc(gcStack, 2 * maxGC * sizeof(ClaireAny*));
		if(adr) {
			gcStack = (ClaireAny**)adr;
			maxGC *= 2;
			good = 1;
			CL_INT igc = 0;
			for(; maxGC > 20000 * (1ul << igc);igc++) ;
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
	for (*i = size + 1; (entryList[*i] == NOTHING); (*i)++)
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
	printf("newChunk()\n");
#ifdef CLDEBUG
 if(inside_gc) Ctracef("Warning: newChunck inside gc\n");  
#endif
 CL_INT value;
 CL_UNSIGNED size,netxt,i,j;
  size = log2up(n);                         /* note that 2^size is always > n */
  if (size > logList) return checkChunkIncrease(1,n);
  if (entryList[size] == NOTHING) //<sb> not a free chunck! we have to find a chunck of a possible bigger size
     { for (i = size; (entryList[i] == NOTHING); i++) //<sb> find a free chunck of sufficent size
     		if (i > logList) break; //<sb> exceed memory allocation (-s i j -> logList = 18+i)
       for (j = i + 1; j <= logList; j++) //<sb> search a chunck larger than i that isn't free 
       		if (entryList[j] != NOTHING) break;
       if ((i > logList) || (i < logList - 1 && j > logList))  // new anti-fragmentation device
       		if (gcChunk(n, size, &value, &i))
       			return value;
       value = entryList[i];                    // we have a chunk of size i
       entryList[i] = ISCHUNK(ADRTOPOIN(value)[FOLLOW]);  // update next free chunk
       for (j = i; (j != size); j--)            // cuts into two until right size
           {CL_INT x = (1ul << (j-1));
           next = (CL_UNSIGNED)value + x;
           CL_UNSIGNED *nx = ADRTOPOIN(next);
           *nx = x;
           nx[FOLLOW] = NOTHING;
           nx[CAR] = NOTHING;
           entryList[j - 1] = ISCHUNK(next);}
       *ADRTOPOIN(value) = (1ul << size);}
   else
     { value = entryList[size];
        entryList[size] = ISCHUNK(ADRTOPOIN(value)[FOLLOW]);}
   usedCells += *ADRTOPOIN(value);                 // book-keeping
   return value;}

// allocation of a short object: this is much simpler and uses a chain of small blocks
// of size OPTIMIZE
CL_INT ClaireAllocation::newShort(CL_INT n)
{
//	printf("newShort()\n");
 #ifdef CLDEBUG
  if(inside_gc) Ctracef("Warning: newShort inside gc\n");  
 #endif
  CL_INT value;
  if (nextFree != NOTHING)                     // chain is not empty
     {value = nextFree;
      Cmemory[value] = n;
      nextFree = Cmemory[nextFree+1];
      #ifdef CLDEBUG
      checkNextFree(); // little trick to check that values are OK
      #endif
      }
  else {if (firstFree > alertFree) // chain is empty
         {object_hits++;
          gc("Object");
          if (nextFree != NOTHING) return newShort(n);
          else return newLong(OPTIMIZE); //<sb> was newLong(n);
      	} else {value = firstFree;
              Cmemory[value] = n;
              firstFree += OPTIMIZE;}}
  return (CmemoryAdr + value);}


// allocation of a long object is pure stacking
CL_INT ClaireAllocation::newLong(CL_INT n)
{ 
	printf("newLong()\n");
#ifdef CLDEBUG
 if(inside_gc) Ctracef("Warning: newLong inside gc\n");  
#endif
  CL_INT newFirstFree = firstFree + (n + 1);
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
  return CmemoryAdr + value; }

// allocation of a long object is pure stacking
ClaireAny *ClaireAllocation::makeStatic(CL_INT n)
	{return (ClaireAny *)((newLong(((n < OPTIMIZE) ? OPTIMIZE : n)) + 1) <<  ADDRTRANS);}


// we allocate the string so that it looks like an imported but is is really special
// string is an import on a char* that is itself allocated by CLAIRE (with a primitive
// isa marking)
//<sb> now take the string length as arg (not the cell size)
char *ClaireAllocation::makeString(CL_INT n)
{CL_INT m;
  CL_INT cells = n  << ADDRTRANS + 4; //<sb> convert length to cells (+ 1 (4 bytes) for null char)
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
{
#ifdef __LP64__
  CL_INT m = newChunk(n + 4); // 4 to store bag info (cell length /class/type,length)
#else
  CL_INT m = newChunk(((t == Kernel._float) ? (2 * n) : n) + 4); // v3.2.34 : 4 vs. 3 is necessary for some strange reason
#endif
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
	ClaireFunction *obj = (ClaireFunction *)((newShort(4) + 1) << ADDRTRANS);
   if (ClAlloc->statusGC != 2)  GC_PUSH(obj);                   // v3.1.06 -> protect the container, v3.2.30 check stack
    obj->isa = Kernel._function;
    obj->value = (CL_INT) f;
    obj->name = s;
    return obj;}

// creates a function without a body
OID error_undefined_function(void)
{Cerror(31,0,0); return 1;}


ClaireFunction *make_function_string(char *s)
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
  #ifdef CLDEBUG
   	for(j=2; j < l; j++) *((CL_UNSIGNED*)((n+j) << ADDRTRANS)) = (from_kill_I ? 0xDDDD : 0xFFFF);
  #endif
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
{ CL_INT esize = entryList[size];
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
       ADRTOPOIN(previous)[FOLLOW] = follow;
       if (follow != NOTHING)
           ADRTOPOIN(follow)[PREVIOUS] = previous;}
  *aa *= 2;
  return freeLoop(a);}


//  desallocation if any need, (instruction object) of the memory zone
void ClaireAllocation::freeObject(CL_INT n) {
 n = (CL_UNSIGNED)n - CmemoryAdr;
#ifdef CLDEBUG
 CL_INT i = 2;
 for(;i < OPTIMIZE; i++) Cmemory[n+i] = (from_kill_I ? 0xDDDD : 0xFFFF);
#endif
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
static inline void MARKCELL(CL_INT n) {CL_INT* x = (CL_INT*))((CL_UNSIGNED)n << ADDRTRANS); x--; *x = -*x;}

// call the garbage collector
// this is a classical mark&sweep designed that has shown to be robust & fast
void ClaireAllocation::gc(char *cause) {
	CL_INT tgc;
	msec(tgc);
	consumed_exec += (tgc - origin_exec);
 	if(sampling) sample_once();
	inside_gc++;
	#ifdef CLDEBUG
	 if ((CL_INT)probe < -2 && (CL_INT)probe == -numGC)
	 	Ctracef("GC %d reached !\n", numGC);
	 if ((CL_INT)probe > 0) {Ctracef("--- the probe is %d -> adr = %d ----\n",probe,getADR(probe));
	                     Ctracef("*[O] = %d, 1:%d, 2:%d\n",probe[1],probe[2],probe[3]);}
	#endif
	if (statusGC == 2) Cerror(27,0,0);                                     // v3.1.12  -> no GC allowed !
	if ((CL_INT)probe <= -2 || (ClEnv->verbose > 0 || (numGC % 10) == 0))
		Ctracef("%s [%d] Garbage collection ... ", cause, numGC);
	numGC++;
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
	sweepChunk();
	sweepObject();
	if ((CL_INT)probe <= -2 || (ClEnv->verbose > 0 || ((numGC-1) % 10) == 0))
	 	Ctracef("done.\n");
	if(inside_gc == 1) sweepFreeable();
	CL_INT tegc;
	msec(tegc);
	consumed_gc += (tegc - tgc);
	if(inside_gc == 1) {
	    if(shortCongestion()) increaseShort();
		if(chunkCongestion()) increaseChunk();
	}
	msec(origin_exec);
	inside_gc--;
	if(sampling) sample_once();
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

//<sb> here we check weither a freeable object has been marked or not
// and we update its freeme? slot accordingly
// as we don't want to free an unmarked freeable object until we have called
// free! we perfrom a mark on it
void ClaireAllocation::updateFreeme() {
 list* l = Kernel._freeable_object->instances;
 CL_INT i, len = l->length;
 for (i = 1;i <= len;i++)
    {OID n = (*l)[i];
    OBJECT(FreeableObject,n)->freeme_ask = (SIZE(n) > 0 ? CTRUE : CFALSE);}
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
 property &prop_prefree = *Kernel.prefree_I;
 for (i = 1;i <= len;i++)
    {OID n = (*l)[i];
    if (OBJECT(FreeableObject,n)->freeme_ask == CTRUE) {
    	prop_prefree(n);
    }}

	property &prop_free = *Kernel.free_I;
	i = 1;
	CL_INT inspos = 0;
	OID *ct = l->content;
	for (;i <= len;i++) {
    	OID n = (*l)[i];
		if (OBJECT(FreeableObject,n)->freeme_ask == CTRUE) {
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
			  	CL_INT *ss = (CL_INT*))s - 3;
				if (*ss > 0) {
					string_used += *ss;
					*ss = -*ss;
				}
				} }
		  MARK(x->value) }}}

// mark the items in the various stacks
void ClaireAllocation::markStack() {
 CL_INT i;
 for (i=0; i < ClEnv->index; i++)
 	{MARK(ClEnv->stack[i])}
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
				CL_INT *ss = (CL_INT*))s - 3;
				if (*ss > 0) {
					string_used += *ss;
					*ss = -*ss;
				}
			}
		} else if INHERIT(c,Kernel._bag) {
			bag_used += cellsize;
			bag *b = (bag*)x;
			aa = b->content;
			#ifdef CLDEBUG
				if (b == probe) Ctracef("Bag probe found and marked --\n");
			#endif
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
			CL_INT *cell = (CL_INT*))x - 1;
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
					CL_INT *ss = (CL_INT*))s - 3;
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
				CLcurrent = cont + 2; //<sb> skip isa that is known to be a class
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
								CL_INT *ss = (CL_INT*))s - 3;
								string_used += *ss;
								if (*ss > 0) *ss = -*ss;
							}
						} else if (c == Kernel._array) {
							aa = (OID*)z;              // index in Cmemory
							CL_INT *cell = (CL_INT*))(aa - 3);
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
  {p = ((CL_INT*))Cmemory)[i];
   ASSERT(p != 0);
   if (p < 0) {
   		((CL_INT*))Cmemory)[i]= -p;          // chunk was marked -> keep it
	 	rchunk_used -= p; }
   else if (Cmemory[i + 1] != NOTHING) { // chunk was not marked and is being used
       #ifdef CLDEBUG
       if ((CL_INT)probe > 0 && i == getADR(probe)) Ctracef("Free the probe chunk !\n");
       #endif
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
    	 #ifdef CLDEBUG
    	  if ((CL_INT)probe > 0 && i == getADR(probe)) Ctracef("Free the probe short object !\n");
         #endif 
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
{CL_INT u = ADR(n);
 if (ClAlloc->numGC > 0)
   { if (Cmemory[u] == 0)
       {Ctracef("OID %d [ADR = %d] has size 0!",n,u);
        Cerror(-1,0,0);}
     if (Cmemory[u + 1] == NOTHING)
       {Ctracef("OID %d [ADR = %d] has been freed",n,u);
        Cerror(-1,0,0);}
     ClaireClass * c = OWNER(n);
     if (c->isa != Kernel._class)
       {Ctracef("OID %d [ADR = %d] has a corrupted owner !",n,u);
        Cerror(-1,0,0);} }}


/*********************************************************************/
/**    4. Interface functions & Compiler functions                   */
/*********************************************************************/

void ClaireAllocation::kill(OID n)
{if  (CTAG(n) == OBJ_CODE)
  {
   #ifdef CLDEBUG
	from_kill_I = 1;
   #endif
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

	#ifdef CLDEBUG

	 from_kill_I = 0;

    #endif

    }}

// the basic function to kill an object: deallocate
OID kill_I_any(OID n) {ClAlloc->kill(n);return 0;}

// call the gc
void claire_gc() {ClAlloc->gc("Call");}

// same for arrays
OID gc_error()  {
	Ctracef("********* GC error *********\n");
	Kernel.GcError->index = 27;
  	Kernel.GcError->value = 0;
  	Kernel.GcError->arg = 0;
 	close_exception((ClaireException *)Kernel.GcError);
    return 1;
  }

// reserves n slots in the garbage stack
void GC_RESERVE(CL_INT n)
{ if ((ClAlloc->index + n) < ClAlloc->maxGC || ClAlloc->gcStackCongestion())
    {CL_INT i = ClAlloc->index, j = i + n + 1;
      ClAlloc->gcStack[i] = (ClaireAny *) (ClAlloc->base);
      ClAlloc->base = i++;
      for (; i <= j; i++) ClAlloc->gcStack[i] = NULL;
      ClAlloc->index = j;}
  else gc_error();}

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
void claire_stat() {ClAlloc->memStat();}

// query CLAIRE memory management
OID claire_mem(OID n)
{if (n == -1) {ClAlloc->probe = (ClaireAny*)n; return n; } //<sb> mem(-n) force all GC trace
 else if (n < 0) {ClAlloc->probe = (ClaireAny*)n; return n; } //<sb> mem(-n) force all GC trace
 else if (OWNER(n) == Kernel._boolean)
    return _oid_(ClAlloc->memList(OBJECT(ClaireBoolean,n)));
 else {if (OWNER(n) == Kernel._integer)
           {if (n == 1) Ctracef("Badguy: %d, %d\n",Cmemory[BadGuy],Cmemory[BadGuy + 1]);
           }
        else {Ctracef("--- the probe is %d -> adr = %d ----\n",OBJECT(ClaireAny,n),ADR(n));
               ClAlloc->probe = OBJECT(ClaireAny,n);}
       return n;}}


/*********************************************************************/
/**    6. Sampling memory                                            */
/*********************************************************************/

void ClaireAllocation::samplerSweepChunk()
{ OID i = 0; CL_INT p;
 while (i < maxList-1)
  {p = ((CL_INT*))Cmemory)[i];
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
void sample_handler(CL_INT sig) {ClAlloc->sample_once();}
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
	CL_INT st;
	(CL_INT *)-1,&st,WUNTRACED);
#endif
	if(samples) fclose(samples); }

void exit_on_sigint(CL_INT i) {
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
		CL_INT st;
		(CL_INT *)-1,&st,WUNTRACED);
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


