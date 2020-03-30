/***********************************************************************/
/**   microCLAIRE                                       Yves Caseau    */
/**   Kernel.h                                                         */
/**  Copyright (C) 1998-99 Yves Caseau. All Rights Reserved.           */
/**  Redistribution and use in source and binary forms are permitted   */
/**  provided that source distribution retains this entire copyright   */
/**  notice and comments.                                              */
/***********************************************************************/

#ifndef CLAIREH_Kernel
#define CLAIREH_Kernel

// --------------------------------------------------------------------------
// this file is the public header file for the Kernel module.
// it is similar to the files produced by the CLAIRE compiler for each module
// it contains the class CL_EXPORT definitions and the API function signatures
// --------------------------------------------------------------------------


// ***************************************************************************
// *  1. CLAIRE class CL_EXPORT hierarchy                                              *
// *  2. C++ functions that define methods                                   *
// *  3. additional C++ API (xl)                                             *
// *  4. The Kernel object                                                   *
// ***************************************************************************


class CL_EXPORT slot;        // forward
class CL_EXPORT thing;
class CL_EXPORT lambda;

// ***************************************************************************
// *  1. CLAIRE class CL_EXPORT hierarchy                                              *
// ***************************************************************************

// Any is the union of object, primitive and integer - In Java it is a class CL_EXPORT but
// not in C++. Notice that the isa slot exists for Objects (as seen by CLAIRE)
// but also for primitive (not seen by CLAIRE but convenient)
// thus we use a common root ClaireAny that is not reified ...
class CL_EXPORT ClaireAny  {
  public:
  ClaireClass *isa; };

// ---------------------------- primitive -----------------------------------------------
// primitive objects are objects that are not instantiated the claire way ...
class CL_EXPORT ClairePrimitive : public ClaireAny {};

// imports are for extensibility
class CL_EXPORT ClaireImport : public ClairePrimitive
{ public:
  CL_INT value;};                           // the 32 bits address of the thing that we import

// same thing for floats but in CLAIRE 2.9 we use a 64bits double
class CL_EXPORT ClaireFloat: public ClairePrimitive
{public:
 double value;
 };

// Functions are object-pointer to C functions
class CL_EXPORT ClaireFunction: public ClairePrimitive
 {public:
  CL_INT value;
  char* name;};

// arrays are imported that are allocated in a special way so that their tail is a memory
// we only pass the exported OID/double*, from which we can get the Imported back.
// we use the two array_v and _array_ macros
// the
class CL_EXPORT ClaireArray: public ClaireImport { };

// new: use the bounds to print the float properly !
extern CL_EXPORT double CLMAXFLOAT;
extern CL_EXPORT double CLMINFLOAT;


// ----------------------------- objects -----------------------------------------------

// a root for all claire-instantiated objects
class CL_EXPORT ClaireObject: public ClaireAny {};

class CL_EXPORT SystemObject: public ClaireObject{};


// ----------------------------- freeable objects --------------------------------------

//<sb> objects that have a destructor callback from the GC
class CL_EXPORT FreeableObject: public ClaireObject{
public:
	ClaireBoolean* freeme_ask;
};

//<sb> this is an important change : port are now organized
// into a hierarchy

class CL_EXPORT PortObject : public FreeableObject {
public:
	int firstc;
	ClaireBoolean *closed_ask;

	CL_INT puts(void*, CL_INT);
	CL_INT puts(const char*);
	CL_INT puts(const char*, CL_INT);
	void put(char c);
	void put(CL_INT n);
	void put(double x);
	void prettyp(double x);
	
	char get();
	CL_INT gets(void*,CL_INT);
	CL_INT eof_ask();

	CL_INT getNext() {
		firstc = (CL_INT)((unsigned char)get());
		return firstc;
	} 
};

// ----------------------------- collections -------------------------------------------

// in claire v2.9 we regroup collections together
// however the set of "abstract set" (iteration + membership) is larger:
//  collection + set + array
// thus use the OID sort
class CL_EXPORT ClaireCollection: public ClaireObject {
    public:
    ClaireBoolean *contains(OID x);              // private method
    };

// this is the CLAIRE Type System reflective definition ----------------------------------
class CL_EXPORT ClaireType: public ClaireCollection {};

class CL_EXPORT property;

// definitions from <marie.h> that are needed for inline methods
//<sb> moved from end of file -> inline operator []
#ifdef __LP64__
//#define getADR(A) (((CCAST(A) - CCAST(&Cmemory[0])) >> 3) - 1)  // gets the ADR from the object -
#define getADR(A) ((CL_INT)A >> ADDRTRANS)  // gets the ADR from the object
#else
#define getADR(A) ((CL_INT)A >> 2)  // gets the ADR from the object

#endif

extern CL_EXPORT void (*callback_refine_append_of)(bag*,bag*,bag*);

// bag is a common root for lists, sets and arrays (special !)
// note that a bag is now a type, even though we only use sets in CLAIRE
class CL_EXPORT bag: public ClaireType
{
  public:
  CL_INT length;
  ClaireType *of;
  OID* content;
  CL_INT prealloc;

  //to add when inline
  //<sb> implicit inline -> cygwin
#ifdef CLDEBUG
  OID &operator[](CL_INT i);
#else
  OID &operator[](CL_INT i)  { return this->content[i]; }
#endif

  static void quickSort(OID *a, CL_INT i, CL_INT m);
  static CL_INT quickClean(OID *a, CL_INT m);
  list *clone();                      // v3.2: needed for Collect
  list *clone(ClaireType *t);         // v3.2

 };

// lists are typed, ordered collections stored in the content[] array (OIDs)
class CL_EXPORT list: public bag
{public:
 static list *empty();
 static list *empty(ClaireType *t);
 static inline list *make();                          // simple intermediate constructor
 static list *make(OID x);                     // constructor for list(x)
 static list *make(OID x, OID y);              // list(x,y)
// static list *makeStack(OID x, OID y);         // list(x,y) allocated on the stack
 static list *alloc(CL_INT n,...);                // create a list with variable num of args
 static list *alloc(ClaireType *t, CL_INT n,...);
 static list *domain(CL_INT n, ...);              // sugar for list of types

 //<sb> made it inline, if a realloc is needed a call to
 // addFastAlloc is performed.
 list *addFastAlloc(OID x);         // add x at the end of l
 list *addFast(OID x) {         // add x at the end of l
 	if (length + 1 >= *(CL_INT*)content)
 		return addFastAlloc(x);
 	content[++length] = x;
 	return this; }

 ClaireBoolean *equalList(list *l2);
 ClaireBoolean *memq(OID val);
// virtual ClaireBoolean *isEqual(OID x2);
 };


 
// a set is implemented as a sorted list (system order, no duplicates)
class CL_EXPORT set: public bag
 {public:
   static inline set *make();          // contructors
   static set *empty();
   static set *empty(ClaireType *t);

   static set *alloc(CL_INT n,...);              // creates a set with variable number of args
   static set *alloc(ClaireType *t, CL_INT n,...);

   set *addFast(OID val);
// virtual ClaireBoolean *isEqual(OID x2);
   ClaireBoolean *equalSet(set *l2);
    };

// tuples are value (constant bags)
class CL_EXPORT tuple: public bag
{public:
   static inline tuple *make();          // contructors
   static tuple *alloc(CL_INT n,...);              // creates a set with variable number of args
   static tuple *empty();
   static tuple *allocStack(CL_INT n,...);           // for dynamic tuples
   tuple *addFast(OID x);         // add x at the end of l
   tuple *copyIfNeeded();
 
};

class CL_EXPORT listargs: public list {};

// in v2.9 the class CL_EXPORT is put in the type hierarchy.
// classes are described in ClReflect for the C++ part and in CLAIRE for the rest (management
// of restrictions)
class CL_EXPORT ClaireClass: public ClaireType
{public:
  symbol *name;
  char *comment;                // a comment that describes the class
  list *slots;                  // a list of slots
  ClaireClass *superclass;      // father in hierarchy
  set *subclass;
  list *ancestors;
  set *descendents;
  ClaireFunction *evaluate;
  CL_INT open;                     // tells the degree of evolvability (cf.clReflect )
  list *instances;
  list *prototype;
  list *params;
  list *dictionary;             // dictionary (defined in CLAIRE !)
  ClaireBoolean *ident_ask;     // true <=> ( = <=> identical)
  OID if_write;                 // new in 3.0 : rules on instantiation !
  list *dispatcher;             // new in 3.1 : fast dispatch => list of functions

  static ClaireClass *make(ClaireAny *x);  // make a class CL_EXPORT (simple version without alloc) for bootstrap
  static ClaireClass *make(char *n);    // same with a name
  static ClaireClass *make(char *name, ClaireClass *c2, module *def);   // regular constructor
  ClaireObject *instantiate(CL_INT n);      // very crude instantiation (only the zone)
  ClaireObject *instantiate();           // use the prototype list as the pattern
  thing *instantiate(char *n, module *def);  // same for named objects
  void genealogy();                                 // creates the genealogy
  slot *addSlot(property *p,ClaireType *t,OID def,CL_INT ix); // add a slot

  
  ClaireObject *operator() (OID arg1)
	{ClaireObject *o = instantiate(prototype->length);
	 OID *rep = (OID*)o;
	 rep[1] = arg1;
	 return o;}

  ClaireObject *operator() (OID arg1, OID arg2)
	{ClaireObject *o = instantiate(prototype->length);
	 OID *rep = (OID*)o;
	 rep[1] = arg1;
	 rep[2] = arg2;
	 return o;}

  ClaireObject *operator() (OID arg1, OID arg2, OID arg3)
	{ClaireObject *o = instantiate(prototype->length);
	 OID *rep = (OID*)o;
	 rep[1] = arg1;
	 rep[2] = arg2;
	 rep[3] = arg3;
	 return o;}
};



extern CL_EXPORT ClaireClass* Kernel_integer;
extern CL_EXPORT CL_INT no_exit_call;

// all the other types are defined in the System module


// unbound symbols are now in Kernel/unbound
class CL_EXPORT unbound_symbol : public SystemObject{
    public:
 symbol *name;};

// Symbols are regular objects but they are stored in the CLRes hash table
class CL_EXPORT symbol: public SystemObject
{public:
 char* name;                  // char* part      m1/toto -> "toto"
 module *module_I;             // the name space  m1/toto -> m1
 module *definition;            // where the symbol is defined (NULL => PRIVATE)
 OID value;                     // the "content" of the symbol

 static symbol *make(char *s, module *m1, module *m2);           // create a symbol
 OID getValue();                // read a value or create an UnboundSymbol
 };




// we create out 256 chars as objects - stored in the ClRes __ table
class CL_EXPORT ClaireChar: public SystemObject
{public:
CL_UNSIGNED ascii;           //<sb> change: the ascii value is an unsigned
static void init();
};

// exceptions
class CL_EXPORT ClaireException: public SystemObject {};

class CL_EXPORT ClaireError: public ClaireException {};

class CL_EXPORT system_error: public ClaireError {
public:
    CL_INT index;
    OID value;
    OID arg;
    OID cerr;
    static system_error *make(CL_INT a, OID i, OID j);
    static system_error *make(CL_INT a, CL_INT cerrcode, OID i, OID j); //<sb> with the c err code
    static system_error *make(CL_INT a, ClaireClass* c, OID i, OID j); //<sb>
    static system_error *make(CL_INT a, CL_INT cerrcode, ClaireClass* c, OID i, OID j); //<sb>
 };

 
// restrictions (slots & methods) are system objects
class CL_EXPORT restriction: public SystemObject {
 public:
  module *module_I;             // module in which the restriction is defined
  char *comment;                // a comment
  list *domain;
  ClaireType *range;
  property *selector;           // the property
                                // v3.2.38: removed some junk ... :-) FXJ
};

// a slot = instance variable
class CL_EXPORT slot: public restriction {
 public:
  ClaireClass *srange;               // sort for the slot's range: list(method) or type(slot)
  OID DEFAULT;                  // default value
  CL_INT index;                    // position in the class CL_EXPORT structure
};

// a method
class CL_EXPORT method: public restriction
{ public:
  list *srange;                 // sort for the slot's range: list(method) or type(slot)
  lambda *formula;              // a lambda
  ClaireFunction *functional;   // a function that is used by the compiler
  ClaireFunction *evaluate;     // a function that is used by the interpreter
  OID typing;                   // a second order type
  OID status;                   // a bitvector of abstract properties
  ClaireBoolean *inline_ask;               // require macr-expansion by the compiler
  method *inlineDef(char *s);           // add an inline definition to a method
};

// a thing is a named object
class CL_EXPORT thing: public ClaireObject
{public:
 symbol *name;
};

class CL_EXPORT SystemThing: public thing {};
class CL_EXPORT keyword: public SystemThing {};

// the two booleans are objects
class CL_EXPORT ClaireBoolean: public SystemObject {};

// relation is the abstraction of properties and table (defined in System)
class CL_EXPORT ClaireRelation: public SystemThing {
public:
  char *comment;
  ClaireType *domain;
  ClaireType *range;
  OID if_write;                         // a list, a Function or CNULL
  ClaireBoolean *store_ask;             // defeasible updates
  ClaireRelation *inverse;              // inverse or NULL
  CL_INT open;                             // the degree of evolvability
  ClaireObject *multivalued_ask;        // list, true or false
};



// stacks: the ClaireEnv object could be duplicated in a multi-proces environt
class CL_EXPORT ClaireEnvironment: public SystemObject
{public:
  // --- this part is visible from CLAIRE through a meta-description ---------------
  CL_INT verbose;                          // verbosity level
  ClaireException* exception_I;         // the last error
  module* module_I;                     // current module we are in
  char *name;                          // external name
  double version;                      // note the real float !
  PortObject *ctrace;                   // current trace port
  PortObject *cout;                     // current out port
  CL_INT index;                            // eval stack index (top of stack)
  CL_INT base;
  CL_INT debug_I;                          // debug
  CL_INT trace_I;                          // for tracing
  CL_INT step_I;
  CL_INT last_debug;                       // last value of the debug index
  CL_INT last_index;                       // last value of the top of eval stack
  CL_INT last_trace;                       // last value of the top of eval stack
  ClaireObject * spy_I;                 // store the spy method if any
  CL_INT count_call;                       // count the numbers of call
  CL_INT count_level;                      // level at which something happens ...
  OID count_trigger;                    // what should happen
  list *params;                         // list of arguments v2.4.07
  CL_INT close;                            // c: do not touch,   p:read only (-1)
  CL_INT ABSTRACT;                         // c: no more instances           (0)
  CL_INT FINAL;                            // c: no more subclasses          (1)
  CL_INT DEFAULT;                          //                                (2)
  CL_INT open;                             // p: open property (extensible)  (3)
  CL_INT ephemeral;                        // c:ephemeral objects            (4)

  // --- this part is only accessible through the Kernel -------------------------
  CL_INT tIndex;                           // time counter index /* time counters                      */
  CL_INT tStack[10];                       // stack of time counters
  	//<sb> and the part that is not saved by the execution context (see toplevel.cl)
  CL_INT allocLength;                      // its chunk length
  CL_INT bLength;                          // its length
  char *buffer;                  // a local buffer for string creation //<sb> now dynamic
  list* moduleStack;                    // stack for begin/end (NEW)
  CL_INT cHandle;                          // the current level of handler
  jmp_buf *handlers;                    // stack of handlers
  CL_INT *stack;                           // evaluation stack
  CL_INT gensym;                           // a seed for symbol generation


  // methods
  void init();
  void abort();


//<sb> moved from the enf of file -> inline cygwin
// definition of the inline methods that need to be shared (MACROS) and that use
// the definitions of Kernel
 void bufferStart();  // makes a string from the buffer
 CL_INT pushAttempt(CL_INT n); //<sb> realloc if necessary to hold n more bytes
 //<sb> moved from Kernel.h -> inline cyqwin
 void pushChar(char c);               // prints a char in the string buffer
  char *bufferCopy();                   // makes a string from the buffer
  void pushInteger(CL_INT n);              // prints an integer in the string buffer

};

extern CL_EXPORT ClaireEnvironment *ClEnv;

//<sb> moved to Kernel for performance
// methods that are defined in the CLAIRE code (a dumb equivalent exists in the test file)
extern CL_EXPORT void push_debug_property(property *p,CL_INT n, CL_INT m);
extern CL_EXPORT void pop_debug_property(property *p,CL_INT n,OID v);
extern CL_EXPORT ClaireObject* find_which_property1(property *p,CL_INT i, ClaireClass *c);
extern CL_EXPORT OID stack_apply_function(ClaireFunction *f, list *l, CL_INT n, CL_INT m);


//<sb> moved from the end of this file -> inline fcall

// TODO : ffcall with range double ! ...........
// v3.2.28 inline small functions that are really needed ---------------------------------

typedef CL_INT (*fptr1) (CL_INT);
typedef CL_INT (*fptr2) (CL_INT,CL_INT);
typedef CL_INT (*fptr3) (CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr4) (CL_INT,CL_INT,CL_INT,CL_INT);

typedef void (*fpLoadModule) ();
typedef void (*fpClaireStarted) ();
typedef void (*fpCallMain) ();
typedef CL_INT (*fpServiceFunc) ();


extern void CL_EXPORT set_load_module(fpLoadModule func);
extern void CL_EXPORT set_claire_started(fpClaireStarted func);
extern void CL_EXPORT set_call_main(fpCallMain func);
extern void CL_EXPORT set_service_func(fpServiceFunc func);

extern CL_EXPORT void default_main();

// a property is a collection of restrictions that share the same selector
class CL_EXPORT property: public ClaireRelation {
public:
  CL_INT trace_I;                               // trace status
  list *restrictions;
  list *definition;
  ClaireObject *dictionary;                  // FALSE or list
  ClaireObject *reified;                     // boolean or a PRcount
  CL_INT dispatcher;                            // new in v3.1 : index for the fast dispatch

  OID stack_apply(CL_INT i);                             // apply to args in stack

  static property *make(char *name, module *m);               // create a property
  static property *make(char *name, CL_INT op, module *m);       // create a property
  static property *make(char *name, CL_INT op, module *m, CL_INT i);// create a property
  static property *make(char *name, CL_INT op, module *m, ClaireClass *c, CL_INT i);// create a property

  OID operator() (OID arg1);
  OID operator() (OID arg1, OID arg2);
  OID operator() (OID arg1, OID arg2, OID arg3);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6, OID arg7);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6, OID arg7, OID arg8);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6, OID arg7, OID arg8, OID arg9);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6, OID arg7, OID arg8, OID arg9, OID arg10);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6, OID arg7, OID arg8, OID arg9, OID arg10, OID arg11);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6, OID arg7, OID arg8, OID arg9, OID arg10, OID arg11, OID arg12);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6, OID arg7, OID arg8, OID arg9, OID arg10, OID arg11, OID arg12, OID arg13);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6, OID arg7, OID arg8, OID arg9, OID arg10, OID arg11, OID arg12, OID arg13, OID arg14);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6, OID arg7, OID arg8, OID arg9, OID arg10, OID arg11, OID arg12, OID arg13, OID arg14, OID arg15);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6, OID arg7, OID arg8, OID arg9, OID arg10, OID arg11, OID arg12, OID arg13, OID arg14, OID arg15, OID arg16);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6, OID arg7, OID arg8, OID arg9, OID arg10, OID arg11, OID arg12, OID arg13, OID arg14, OID arg15, OID arg16, OID arg17);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6, OID arg7, OID arg8, OID arg9, OID arg10, OID arg11, OID arg12, OID arg13, OID arg14, OID arg15, OID arg16, OID arg17, OID arg18);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6, OID arg7, OID arg8, OID arg9, OID arg10, OID arg11, OID arg12, OID arg13, OID arg14, OID arg15, OID arg16, OID arg17, OID arg18, OID arg19);
  OID operator() (OID arg1, OID arg2, OID arg3, OID arg4, OID arg5, OID arg6, OID arg7, OID arg8, OID arg9, OID arg10, OID arg11, OID arg12, OID arg13, OID arg14, OID arg15, OID arg16, OID arg17, OID arg18, OID arg19, OID arg20);

  // v3.2.24 inline fcall
  //<sb> move inline defs inside class CL_EXPORT def -> cygwin relocable objects
 CL_INT fcall(CL_INT a1)
    {ClaireClass *c = ((ClaireObject *) a1)->isa;
     return ((fptr1) OBJECT(ClaireFunction,
              ((list *) (c->dispatcher))->content[dispatcher])->value)(a1);}

 CL_INT fcall(CL_INT a1,CL_INT a2)
    {ClaireClass *c = ((ClaireObject *) a1)->isa;
     return ((fptr2) OBJECT(ClaireFunction,
             ((list *) (c->dispatcher))->content[dispatcher])->value)(a1,a2);}

 CL_INT fcall(CL_INT a1, CL_INT a2, CL_INT a3)
    {ClaireClass *c = ((ClaireObject *) a1)->isa;
     return ((fptr3) OBJECT(ClaireFunction,
             ((list *) (c->dispatcher))->content[dispatcher])->value)(a1,a2,a3);}

 CL_INT fcall(CL_INT a1, CL_INT a2, CL_INT a3, CL_INT a4)
    {ClaireClass *c = ((ClaireObject *) a1)->isa;
     return ((fptr4) OBJECT(ClaireFunction,
             ((list *) (c->dispatcher))->content[dispatcher])->value)(a1,a2,a3,a4);}

  OID super(ClaireClass *c,CL_INT size);                 // used by compiler
  method *addMethod(list *dom, ClaireType *ran, CL_INT sta, ClaireFunction *f);  // add method
  method *addFloatMethod(list *dom, ClaireType *ran, CL_INT sta, ClaireFunction *f,
                         ClaireFunction *f2);  // add method for floats

  } ;

// an operation is a property with a special syntax 
class CL_EXPORT operation: public property {
public:
  CL_INT precedence;
  static operation *make(char *name, CL_INT op, module *m, CL_INT p);        // create an operation
  static operation *make(char *name, module *m, CL_INT p);        // create an operation
  } ;


// tables
class CL_EXPORT table: public ClaireRelation {
public:
  bag *graph;                  // the graph is a list or an array
  OID params;                  // integer, or pair of integer
  OID DEFAULT;                 // default value

  CL_INT expand(OID x);
  CL_INT insertHash(list *l, OID x, OID val);
};


// modules are regular objects in 2.9 (no more integer IDs)
// they are defined in System and inherit from NameSpace (an internal class)
class CL_EXPORT module: public SystemThing {
public:
    char *comment;
    list *parts;                // list of sub-modules
    module *part_of;             // sub-module of
    list *uses;                 // other modules that are used
    char *source;               // directory where the sources can be found
    list *made_of;
    CL_INT status;                 // new (0:default, 1:loaded, 2 compiled, 3:c+loaded, 4:c+l+traced)
    ClaireFunction *evaluate;   // function
    char *external;             // external of the module: .lib library
    char *version;          //<sb> in XL claire a module has a version
    OID verbose;		//<sb> in XL claire the module has a verbse policy
    
    static module *make(char *s, module *sup);          // constructor
    CL_UNSIGNED hash(char *s);                             // classical has function
    symbol *lookup(char *nm);                         // symbol lookup
    symbol *getSymbol(char *nm, module *def);

 };


// ***************************************************************************
// *  2. C++ functions that define methods                                   *
// ***************************************************************************

// === objects ==============================================================
extern CL_EXPORT ClaireObject *copy_object(ClaireObject *x);
extern CL_EXPORT ClaireBoolean *equal(OID n, OID m);
extern CL_EXPORT OID slot_get_object(ClaireObject *x, CL_INT y, ClaireClass *s);
extern CL_EXPORT ClaireBoolean *belong_to(OID oself, OID ens);
extern CL_EXPORT CL_INT hash_list(list *l, OID x);
extern CL_EXPORT CL_INT Cerror(CL_INT n, OID a, OID b);
extern CL_EXPORT CL_INT Cerror(CL_INT n, ClaireClass* c, OID a, OID b); //<sb>
extern CL_EXPORT ClaireBoolean *boolean_I_ClaireAny(ClaireAny *x);
extern CL_EXPORT ClaireBoolean *boolean_I_any(OID n);

// === class CL_EXPORT & properties ===================================================
extern CL_EXPORT void add_slot_class(ClaireClass *c, property *p, ClaireType *t, OID def,CL_INT i);
// extern CL_EXPORT void add_slot_classNew(ClaireClass *c, property *p, ClaireType *t, OID def, CL_INT i);
extern CL_EXPORT ClaireClass *sort_I_class(ClaireClass *c);
extern CL_EXPORT method *add_method_property(property *p, list *dom, ClaireType *r,
                                   CL_INT status, OID f);
extern CL_EXPORT ClaireObject *new_object_class(ClaireClass *c);
extern CL_EXPORT thing *new_thing_class(ClaireClass *c, symbol *s);

extern CL_EXPORT CL_INT index_table(table *a, OID x);
extern CL_EXPORT CL_INT index_table2(table *a, OID x, OID y);
extern CL_EXPORT table *make_table_type(ClaireType *_Zdomain, ClaireType *_Zrange, OID _Zdefault);
extern CL_EXPORT ClaireClass *class_I_symbol(symbol *s, ClaireClass *c2);

// === bags =================================================================
extern CL_EXPORT bag *copy_bag(bag *l);
extern CL_EXPORT bag *empty_bag(bag *l);
extern CL_EXPORT bag *delete_bag(bag *l, OID x);
extern CL_EXPORT ClaireType * of_bag(bag *l);
//extern CL_EXPORT bag *cast_I_bag(bag *l, ClaireType *x);
extern CL_EXPORT set *cast_I_set1(set *l, ClaireType *x);
extern CL_EXPORT list *cast_I_list1(list *l, ClaireType *x);
extern CL_EXPORT list *prealloc_list_type1(ClaireType *x, CL_INT n);
extern CL_EXPORT set *prealloc_set_type1(ClaireType *x, CL_INT n);
extern CL_EXPORT list *make_list_type1(ClaireType *t, CL_INT n);


// === list =================================================================
extern CL_EXPORT list *add_list(list *l, OID val);
extern CL_EXPORT list *add_I_list(list *l, OID val);
extern CL_EXPORT list *cons_any(OID val, list *l);
extern CL_EXPORT list *make_list_integer(CL_INT n, OID m);
extern CL_EXPORT CL_INT index_list (list *l, OID val);
extern CL_EXPORT list *add_star_list(list *l1, list *l2);
extern CL_EXPORT list *append_list(list *l1, list *l2);
extern CL_EXPORT list *add_at_list(list *l, CL_INT n, OID val);
extern CL_EXPORT list *delete_at_list (list *l, CL_INT n);
extern CL_EXPORT list *skip_list(list *l, CL_INT n);
extern CL_EXPORT list *cdr_list(list *l);
extern CL_EXPORT bag *shrink_list (bag *l, CL_INT n);
extern CL_EXPORT ClaireBoolean *contain_ask_list(list *l,OID x);
extern CL_EXPORT tuple *tuple_I_list(list *l);
extern CL_EXPORT list *list_I_tuple(tuple *l);
extern CL_EXPORT char *make_string_list(list *l);

// === sets =================================================================
extern CL_EXPORT set *add_set(set *l, OID val);
extern CL_EXPORT set *add_I_set(set *l, OID val);
extern CL_EXPORT set *_exp_set(set *l1, set *l2);
extern CL_EXPORT set *append_set (set *l1, set *l2);
extern CL_EXPORT set *set_I_bag (bag *l);
extern CL_EXPORT list *list_I_set (set *l);
extern CL_EXPORT set *sequence_integer(CL_INT n, CL_INT m);
extern CL_EXPORT ClaireBoolean *contain_ask_set(set *l,OID x);

// === array ==================================================================
extern CL_EXPORT OID *copy_array(OID *a);
extern CL_EXPORT CL_INT length_array(OID *a);
extern CL_EXPORT ClaireType  *of_array(OID *a);
extern CL_EXPORT OID *make_array_integer(CL_INT n, ClaireType *t, OID v);
extern CL_EXPORT OID nth_get_array(OID *a, CL_INT n);
extern CL_EXPORT void nth_put_array(OID *a, CL_INT n, OID y);
extern CL_EXPORT list *list_I_array(OID *a);
extern CL_EXPORT OID *array_I_list(list *l);
extern CL_EXPORT ClaireBoolean *contain_ask_array(OID *a, OID val);

// === strings =============================================================
extern CL_EXPORT char *copy_string(char *s);
extern CL_EXPORT char *copy_string1(char *s, CL_INT l); //<sb>
extern CL_EXPORT ClaireBoolean *equal_string(register char *s1, register char *s2);
extern CL_EXPORT void princ_string(char *ss);
extern CL_EXPORT void princ_string1(char *ss,CL_INT i, CL_INT j);
extern CL_EXPORT void color_princ_string1(char *ss); //<sb> v3.3.33
extern CL_EXPORT void color_princ_string2(char *ss,CL_INT i, CL_INT j);
extern CL_EXPORT void self_print_string(char *ss);
extern CL_EXPORT char *append_string(char *ss1, char *ss2);
extern CL_EXPORT CL_INT integer_I_string(char *s);
extern CL_EXPORT char *substring_string(char *ss, CL_INT n, CL_INT m);
extern CL_EXPORT CL_INT get_string(char *ss, ClaireChar *c);
extern CL_EXPORT ClaireBoolean *_less_string(char *s1, char *s2);
extern CL_EXPORT CL_INT included_string(char *s1, char *s2,ClaireBoolean *p);
extern CL_EXPORT ClaireChar *nth_string (char *ss, CL_INT n);
extern CL_EXPORT void nth_set_string (char *ss, CL_INT n, ClaireChar *c);
extern CL_EXPORT char *shrink_string(char *ss, CL_INT n);
extern CL_EXPORT OID value_string(char *name);
extern CL_EXPORT OID value_module(module *m, char *name);
extern CL_EXPORT OID get_symbol_module(module *m, char *name);
extern CL_EXPORT symbol *symbol_I_string(char *s,module *m);
extern CL_EXPORT ClaireFunction *make_function_string(char *s);
extern CL_EXPORT char *date_I_integer(CL_INT i);
extern CL_EXPORT CL_INT length_string(char *s); //<sb> buffer
extern CL_EXPORT char *bin_I_integer(CL_INT i); //<sb> little bin output
extern CL_EXPORT char *hex_I_integer(CL_INT i); //<sb> little hex output
extern CL_EXPORT void internal_print_string(char* ss, CL_INT len);
extern CL_EXPORT ClaireBoolean *insensitive_equal_string1(char*s1,char*s2);
// ==== modules & symbols =====================================================
extern CL_EXPORT void begin_module (module *x);
extern CL_EXPORT void end_module (module *x);
extern CL_EXPORT symbol *append_symbol(symbol *s1, OID s2);
extern CL_EXPORT void princ_symbol(symbol *s);
extern CL_EXPORT module *defined_symbol (symbol *s);
extern CL_EXPORT module *module_I_symbol (symbol *s);
extern CL_EXPORT symbol *gensym_string (char *s);
extern CL_EXPORT OID get_symbol (symbol *s);
extern CL_EXPORT OID put_symbol(symbol *s, OID x);
extern CL_EXPORT char* string_I_symbol(symbol *s);
extern CL_EXPORT CL_INT integer_I_symbol(symbol *s);


// === integer & floats =======================================================
// extern CL_EXPORT CL_INT _integer_(CL_INT n);
// extern CL_EXPORT OID _float_(double v);

/*extern CL_EXPORT void princ_integer(CL_INT n);
extern CL_EXPORT CL_INT ch_sign(CL_INT n);
extern CL_EXPORT CL_INT mod_integer(CL_INT n, CL_INT m);
extern CL_EXPORT CL_INT _7_integer(CL_INT n, CL_INT m);
extern CL_EXPORT CL_INT _exp_integer(CL_INT n, CL_INT m);
extern CL_EXPORT CL_INT exp2_integer(CL_INT n);*/
extern CL_EXPORT ClaireChar *char_I_integer(CL_INT n);
extern CL_EXPORT char *string_I_integer (CL_INT n);
extern CL_EXPORT char *make_string_integer(CL_INT n, ClaireChar *c);
extern CL_EXPORT char *make_string_integer1(CL_INT n);
extern CL_EXPORT CL_INT random_integer(CL_INT n);
extern CL_EXPORT void random_I_void();
extern CL_EXPORT CL_INT times_integer(CL_INT m, CL_INT n);

/*extern CL_EXPORT double to_float (CL_INT n);
extern CL_EXPORT OID to_float_(CL_INT n);
extern CL_EXPORT CL_INT integer_I_float(double n);
extern CL_EXPORT ClaireBoolean *_inf_float(double n, double m);
extern CL_EXPORT ClaireBoolean *_inf_equal_float(double n, double m);
extern CL_EXPORT ClaireBoolean *_sup_float(double n, double m);
extern CL_EXPORT ClaireBoolean *_sup_equal_float(double n, double m);
extern CL_EXPORT CL_INT integer_I_float_(OID n);
extern CL_EXPORT ClaireBoolean *_inf_float_(OID n, OID m);
extern CL_EXPORT ClaireBoolean *_inf_equal_float_(OID n, OID m);
extern CL_EXPORT ClaireBoolean *_sup_float_(OID n, OID m);
extern CL_EXPORT ClaireBoolean *_sup_equal_float_(OID n, OID m);*/
extern CL_EXPORT void princ_float(double x);
extern CL_EXPORT void princ_float_(OID x);
extern CL_EXPORT void print_float(double x);
extern CL_EXPORT void print_float_(OID x);

// === ports ==================================================================

extern CL_EXPORT PortObject *use_as_output_port(PortObject *p);
//extern CL_EXPORT void fclose_port(PortObject *p);
//extern CL_EXPORT void putc_char(ClaireChar *c,PortObject *p);
//extern CL_EXPORT ClaireChar * getc_port(PortObject *p);
//extern CL_EXPORT void flush_port(PortObject *p);
//extern CL_EXPORT FileObject *fopen_string(char *s, char *m);
//extern CL_EXPORT void clearerr_port(FileObject *p);
//extern CL_EXPORT BufferObject *port_I_void();
//extern CL_EXPORT BufferObject *port_I_string(char *s);
//extern CL_EXPORT char *string_I_port(BufferObject *p);
//extern CL_EXPORT OID length_port(BufferObject *p);
//extern CL_EXPORT void set_length_port(BufferObject *p, CL_INT m);
extern CL_EXPORT char *read_string_port(PortObject *p);
extern CL_EXPORT OID read_ident_port(PortObject *p);
extern CL_EXPORT OID read_number_port(PortObject *p);
extern CL_EXPORT OID read_thing_port(PortObject *p, module *app, ClaireChar *cur, module *def);
extern CL_EXPORT void pushback_port(PortObject *p,CL_INT n);
extern CL_EXPORT void free_I_any(OID o); //<sb>
extern CL_EXPORT void prefree_I_any(OID o); //<sb>
//extern CL_EXPORT void free_I_port(PortObject *p); //<sb>
extern CL_EXPORT char *freadline_port(PortObject* po);
extern CL_EXPORT char *freadline_port1(PortObject* po, char* sep);
extern CL_EXPORT char *freadline_port2(PortObject* po, char* sep, ClaireBoolean *sensitive);
extern CL_EXPORT char *freadline_port3(PortObject* po, char* sep, ClaireBoolean *sensitive, ClaireChar *escape);
extern CL_EXPORT tuple *freadline_port4(PortObject* po, bag *seps);
extern CL_EXPORT tuple *freadline_port5(PortObject* po, bag *seps, ClaireBoolean *sensitive);
extern CL_EXPORT tuple *freadline_port6(PortObject* po, bag *seps, ClaireBoolean *sensitive, ClaireChar *escape);
//extern CL_EXPORT CL_INT freadwrite_port1(PortObject* , PortObject*); //<sb>
//extern CL_EXPORT CL_INT freadwrite_port(PortObject* , PortObject* , int); //<sb>
//extern CL_EXPORT void set_index_port(BufferObject *po, CL_INT i); //<sb>
//extern CL_EXPORT CL_INT get_index_port(BufferObject *po); //<sb>


//extern CL_EXPORT ClaireBoolean *reverse_I_port(BufferObject *p, ClaireBoolean *rev); //<sb>
//extern CL_EXPORT void ungetc_port(PortObject *p, CL_INT c); //<sb>
//extern CL_EXPORT ClaireBoolean *eof_ask_port(PortObject *p); //<sb> 
//extern CL_EXPORT PortObject *null_I_void(); //<sb>
//extern CL_EXPORT ClaireChar* nth_port(BufferObject *p, CL_INT m); //<sb>
//extern CL_EXPORT void nth_set_port(BufferObject *p, CL_INT m, ClaireChar *c); //<sb>
//extern CL_EXPORT char *substring_port(BufferObject* p, CL_INT s, CL_INT e); //<sb>
//extern CL_EXPORT ClaireBoolean *find_ask_port(BufferObject*, char* s, CL_INT m); //<sb>
//extern CL_EXPORT char* fread_port(PortObject*, int); //<sb>
//extern CL_EXPORT char *fread_port1(PortObject *p);
//extern CL_EXPORT CL_INT fread_port2(PortObject*, char*); //<sb>
//extern CL_EXPORT void fwrite_string(char*, PortObject*); //<sb>
//extern CL_EXPORT void setvbuf_port(FileObject*, int); //<sb>
//extern CL_EXPORT void flock_file1(FileObject *f); //<sb>
//extern CL_EXPORT void funlock_file1(FileObject *f); //<sb>
//extern CL_EXPORT ClaireBoolean *islocked_ask_file1(FileObject *f); //<sb>

// === char & system ==========================================================
extern CL_EXPORT void print_char(ClaireChar *cx);
extern CL_EXPORT void princ_char(ClaireChar *c);
extern CL_EXPORT void c_princ_c(ClaireChar *c);
extern CL_EXPORT void c_princ_string(char *ss);
extern CL_EXPORT void c_princ_symbol(symbol *s);
extern CL_EXPORT OID claire_mem(OID n);
extern CL_EXPORT void claire_stat();
extern CL_EXPORT ClaireBoolean *alpha_char (ClaireChar *cx);
extern CL_EXPORT CL_INT integer_I_char(ClaireChar *c);


// === system functions =======================================================
extern CL_EXPORT OID close_exception(ClaireException *x);
extern CL_EXPORT OID safe_exception(ClaireException *x);
extern CL_EXPORT void stack_add(CL_INT x);
extern CL_EXPORT OID fcall1(ClaireFunction *f,ClaireClass *s1,OID a1,ClaireClass *s);
extern CL_EXPORT OID fcall2(ClaireFunction *f,ClaireClass *s1,OID a1,ClaireClass *s2, OID a2,
                  ClaireClass *s);
extern CL_EXPORT OID fcall3(ClaireFunction *f,ClaireClass *s1,OID a1,ClaireClass *s2, OID a2,
                  ClaireClass *s3, OID a3, ClaireClass *s);
extern CL_EXPORT void fastcall_any(OID x, OID y, OID z);
extern CL_EXPORT char *string_I_function(ClaireFunction *f);
extern CL_EXPORT OID store_list(list *l, CL_INT n, OID y, ClaireBoolean *b);
extern CL_EXPORT OID store_array(OID* a, CL_INT n, OID y, ClaireBoolean *b);
extern CL_EXPORT OID store_object(ClaireObject *x, CL_INT n, ClaireClass *s, OID y, ClaireBoolean *b);
extern CL_EXPORT list *store_add(list *l,OID y);
extern CL_EXPORT void world_push();
extern CL_EXPORT void world_pop();
extern CL_EXPORT void world_remove();
extern CL_EXPORT void world_slaughter();
extern CL_EXPORT CL_INT world_number();
extern CL_EXPORT CL_INT world_get_id();
extern CL_EXPORT void claire_gc();
extern CL_EXPORT void restore_state_void();
extern CL_EXPORT ClaireObject *GC_OBJ_F(ClaireObject *x);
//extern CL_EXPORT OID GC_OID(OID x);
//extern CL_EXPORT void GC__OID(OID x, CL_INT m);
//extern CL_EXPORT char *GC_STRING(char *s);
//extern CL_EXPORT void GC__STRING(char *s,CL_INT n);
//extern CL_EXPORT OID *GC_ARRAY(OID *a);
extern CL_EXPORT CL_INT GC_DEBUG(CL_INT n);
extern CL_EXPORT OID kill_I_any(OID n);
extern CL_EXPORT CL_INT claire_shell(char *s);
extern CL_EXPORT void time_set_void();
extern CL_EXPORT CL_INT time_get_void();
extern CL_EXPORT CL_INT time_read_void();
extern CL_EXPORT void time_show_void();


// for debug
extern CL_EXPORT CL_INT CL_Address(OID x);
extern CL_EXPORT char *CL_Oid(OID x) ;
extern CL_EXPORT OID CL_Oid_inv(char *s) ;
extern CL_EXPORT void CL_exit(CL_INT i);
extern CL_EXPORT CL_INT CL_system(char *s);
//extern CL_EXPORT void *CL_alloc(CL_INT n); //<sb> rm
extern CL_EXPORT void CL_error_alloc();
extern CL_EXPORT void checkOID(OID n);


typedef void (*fp_interpreter_insert_text)(char*);
extern CL_EXPORT fp_interpreter_insert_text interpreter_insert_text;
typedef void (*fp_interpreter_delete_text)(int,int);
extern CL_EXPORT fp_interpreter_delete_text interpreter_delete_text;
typedef void (*fp_interpreter_reset_state)();
extern CL_EXPORT fp_interpreter_reset_state interpreter_reset_state;
typedef char* (*fp_interpreter_get_text)();
extern CL_EXPORT fp_interpreter_get_text interpreter_get_text;
typedef int (*fp_interpreter_get_cursor_position)();
extern CL_EXPORT fp_interpreter_get_cursor_position interpreter_get_cursor_position;
typedef void (*fp_interpreter_display_list)(list*);
extern CL_EXPORT fp_interpreter_display_list interpreter_display_list;

// DEBUG: to remove (needed for the testI.exe version)
extern CL_EXPORT void see(OID x);
extern CL_EXPORT void see(OID x, CL_INT i);
extern CL_EXPORT void see(char *c,OID x,CL_INT i);
extern CL_EXPORT void see(char *c,OID x);



// ***************************************************************************
// *  3. additional C++ API (xl)                                             *
// ***************************************************************************

//<sb>
// === color =======================================================================
extern CL_EXPORT CL_INT color_integer(CL_INT c);
extern CL_EXPORT CL_INT color_void();
//<sb>
// === stringtool ==================================================================
extern CL_EXPORT ClaireBoolean* alpha_ask_string(char* s);
extern CL_EXPORT ClaireBoolean* alpha_ask_char(ClaireChar* c);
extern CL_EXPORT ClaireBoolean* lower_ask_char(ClaireChar* c);
extern CL_EXPORT ClaireBoolean* lower_ask_string(char* s);
extern CL_EXPORT ClaireBoolean* upper_ask_char(ClaireChar* c);
extern CL_EXPORT ClaireBoolean* upper_ask_string(char* s);
extern CL_EXPORT char* upper_string(char* s);
extern CL_EXPORT char* lower_string(char* s);
extern CL_EXPORT ClaireBoolean* space_ask_char(ClaireChar* c);
extern CL_EXPORT ClaireBoolean* digit_ask_char(ClaireChar* c);
extern CL_EXPORT ClaireBoolean* space_ask_string(char* s);
extern CL_EXPORT ClaireBoolean* digit_ask_string(char* s);
extern CL_EXPORT char* replace_string(char* src, char* to, char *by);
extern CL_EXPORT CL_INT occurrence_string(char* to, char* in);
extern CL_EXPORT CL_INT find_string(char* src, char* to, CL_INT from);
extern CL_EXPORT CL_INT rfind_string(char* src, char* to, CL_INT from);
extern CL_EXPORT char * ltrim_string(char *s);
extern CL_EXPORT char * rtrim_string(char *s);
extern CL_EXPORT char * trim_string(char *s);
extern CL_EXPORT CL_INT  find_string2(char *src,char *to);
extern CL_EXPORT char * left_string(char *src,CL_INT n);
extern CL_EXPORT char * right_string(char *src,CL_INT n);
extern CL_EXPORT CL_INT  rfind_string2(char *src,char *to);
extern CL_EXPORT char *reverse_string(char *src);
extern CL_EXPORT list * explode_string(char *self,char *sep);
extern CL_EXPORT list *explode_wildcard_string(char* src, char* w);

//<sb>
// === encoding ==================================================================
extern CL_EXPORT char *url_encode_string(char* s);
extern CL_EXPORT char *url_decode_string(char* s);
extern CL_EXPORT char *mime_decode_string(char *in);
extern CL_EXPORT char *mime_encode_string(char *in);
extern CL_EXPORT void encode64_port(PortObject *in,PortObject *out, CL_INT len);
extern CL_EXPORT void decode64_port(PortObject *in,PortObject *out);
extern CL_EXPORT char *unescape_string(char* src);
extern CL_EXPORT char *escape_string(char* src);

//<sb>
//======= env =============================================================
extern CL_EXPORT void ding_void();
extern CL_EXPORT char* cerror_integer(CL_INT err);
extern CL_EXPORT char* getenv_string(char *s); //<sb> was in standard kernel (moved for clarity)
extern CL_EXPORT void setenv_string(char *s);
extern CL_EXPORT void setcwd_string(char *s);
extern CL_EXPORT char *pwd_void();
extern CL_EXPORT char *environ_integer(CL_INT i);
extern CL_EXPORT CL_INT maxenv_void();
extern CL_EXPORT ClaireBoolean *isenv_ask_string(char* v);

//<sb>
//======= process =============================================================
extern CL_EXPORT CL_INT getuid_void();
extern CL_EXPORT CL_INT getpid_void();
extern CL_EXPORT CL_INT getppid_void();
extern CL_EXPORT CL_INT cfork_void1();
extern CL_EXPORT CL_INT forked_void();
extern CL_EXPORT void kill_integer1(CL_INT pid);
extern CL_EXPORT ClaireBoolean* run_ask_integer(CL_INT pr);
extern CL_EXPORT ClaireBoolean* wait_integer1(CL_INT pr, CL_INT ms);
extern CL_EXPORT void wait_integer2(CL_INT pr);
extern CL_EXPORT CL_INT process_I_string(char* self, bag* args);
//extern CL_EXPORT FileObject* popen_string(char *p, char *m);
extern CL_EXPORT tuple *waitpid_status_integer(CL_INT process, ClaireBoolean* block);
extern CL_EXPORT tuple *waitpid_status_integer_(CL_INT process, ClaireBoolean* block);

//<sb>
// === uname =================================================================
extern CL_EXPORT char* sys_name_void();
extern CL_EXPORT char* sys_node_name_void();
extern CL_EXPORT char* sys_release_void();
extern CL_EXPORT char* sys_version_void();
extern CL_EXPORT char* sys_machine_void();
extern CL_EXPORT char* sys_arch_void();
extern CL_EXPORT char* sys_compiler_void();
extern CL_EXPORT char* sys_compiler_version_void();

//<sb>
// ==== date/time =====================================================
extern CL_EXPORT double timer_I_void();
extern CL_EXPORT OID timer_I_void_();
extern CL_EXPORT CL_INT elapsed_float(double t);
extern CL_EXPORT CL_INT elapsed_float_(OID t);
extern CL_EXPORT char* setlocale_integer(CL_INT cat, char *loc);
extern CL_EXPORT char* getlocale_integer(CL_INT cat);
extern CL_EXPORT double make_date_integer(CL_INT D, CL_INT M, CL_INT Y, CL_INT h, CL_INT m, CL_INT s);
extern CL_EXPORT OID make_date_integer_(CL_INT D, CL_INT M, CL_INT Y, CL_INT h, CL_INT m, CL_INT s);
extern CL_EXPORT double make_date_string(char* s);
extern CL_EXPORT OID make_date_string_(char* s);
extern CL_EXPORT double make_time_string(char* s);
extern CL_EXPORT OID make_time_string_(char* s);
extern CL_EXPORT double make_time_integer(CL_INT h, CL_INT m, CL_INT s);
extern CL_EXPORT OID make_time_integer_(CL_INT h, CL_INT m, CL_INT s);
extern CL_EXPORT double date_add_float(double self,ClaireChar *what,CL_INT val);
extern CL_EXPORT OID date_add_float_(OID self,ClaireChar *what,CL_INT val);
extern CL_EXPORT char *strftime_string(char* format, double t);
extern CL_EXPORT char *strftime_string_(char* format, OID t);
extern CL_EXPORT double diff_time_float(double t1, double t2);
extern CL_EXPORT OID diff_time_float_(OID t1, OID t2);
extern CL_EXPORT double now_void();
extern CL_EXPORT OID now_void_();
extern CL_EXPORT void sleep_integer(CL_INT ms);
extern CL_EXPORT void uptime_float(double t);
extern CL_EXPORT void uptime_float_(OID t);
extern CL_EXPORT char* uid_void();
extern CL_EXPORT char *tzset_string(char *tz);

//<sb>
// === dir/files ==========================================================
extern CL_EXPORT ClaireBoolean *match_wildcard_ask_string(char *src,char *w);
extern CL_EXPORT list *entries_string1(char *self,char *wild);
extern CL_EXPORT list *entries_string2(char *self);
extern CL_EXPORT char *entry_string1(char *self,char *wild);
extern CL_EXPORT ClaireBoolean *isdir_ask_string(char *self);
extern CL_EXPORT ClaireBoolean *isfile_ask_string(char *self);
extern CL_EXPORT void unlink_string(char *self);
extern CL_EXPORT void mkdir_string1(char *self, CL_INT mode);
extern CL_EXPORT void mkdir_string2(char *self);
extern CL_EXPORT void rmdir_string(char *self);
extern CL_EXPORT void chmod_string(char *self, CL_INT mode);
extern CL_EXPORT void link_string(char *name1, char *name2);
extern CL_EXPORT void symlink_string(char *name1, char *name2);
extern CL_EXPORT void fcopy_string(char *self, char *trg);
extern CL_EXPORT void fmove_string(char *self, char *trg);
extern CL_EXPORT double fsize_string(char* self);
extern CL_EXPORT OID fsize_string_(char* self);
extern CL_EXPORT double fchanged_string(char *self);
extern CL_EXPORT OID fchanged_string_(char *self);
extern CL_EXPORT double fmodified_string(char *self);
extern CL_EXPORT OID fmodified_string_(char *self);
extern CL_EXPORT double faccessed_string(char *self);
extern CL_EXPORT OID faccessed_string_(char *self);
extern CL_EXPORT CL_INT fmode_string(char *self);
extern CL_EXPORT tuple* explode_float(double self);
extern CL_EXPORT tuple* explode_float_(OID t);
extern CL_EXPORT char* realpath_string(char* self);


// ***************************************************************************
// *  4. The Kernel object                                                   *
// ***************************************************************************

// a first subclass CL_EXPORT for Kernel
class CL_EXPORT KernelClass: public NameSpace
{public: 

// class CL_EXPORT hierachy (alphabetical order)
ClaireClass *_any;
ClaireClass *_array;
ClaireClass *_bag;
ClaireClass *_boolean;
ClaireClass *_char;
ClaireClass *_class;
ClaireClass *_collection;
ClaireClass *_environment;
ClaireClass *_error;
ClaireClass *_exception;
ClaireClass *_float;
ClaireClass *_function;
ClaireClass *_cl_import;
ClaireClass *_integer;
ClaireClass *_keyword;
ClaireClass *_list;
ClaireClass *_listargs;
ClaireClass *_method;
ClaireClass *_module;
ClaireClass *_primitive;
ClaireClass *_object;
ClaireClass *_operation;
ClaireClass *_port;
ClaireClass *_property;
ClaireClass *_relation;
ClaireClass *_restriction;
ClaireClass *_set;
ClaireClass *_slot;
ClaireClass *_string;
ClaireClass *_symbol;
ClaireClass *_system_error;
ClaireClass *_socket_error; //<sb> 
ClaireClass *_connection_error; //<sb>
ClaireClass *_connection_closed; //<sb>
ClaireClass *_connection_aborted; //<sb>
ClaireClass *_socket_would_block; //<sb>
ClaireClass *_system_object;
ClaireClass *_system_thing;
ClaireClass *_table;
ClaireClass *_thing;
ClaireClass *_tuple;
ClaireClass *_type;
ClaireClass *_unbound_symbol;
ClaireClass *_void;

ClaireClass *_freeable_object; //<sb> freeable and ports

/*ClaireClass *_imported_port; //<sb> we still use the old ClairePort but inside a freeable container
ClaireClass *_file_descriptor;
ClaireClass *_file;
ClaireClass *_buffer;
ClaireClass *_socket;
ClaireClass *_client_socket;
ClaireClass *_server_socket;*/

// properties
operation *_dot_dot;
operation *_dash_dash_ask;    // new in v3.0.54
operation *_equal;
operation *insensitive_equal;
operation *_exp;
property *_exp2;
operation *_inf;
operation *_inf_equal;
operation *_inf_inf;
operation *_dash;
operation *_sup;
operation *_sup_equal;
operation *_star;
operation *_7;
operation *_7_plus;
operation *_Z;
property *DEFAULT;
property *ABSTRACT;
property *FINAL;
operation *add;
operation *add_I;
property *add_method;
property *add_slot;
property *add_star;
property *ancestors;
property *array_I;
property *arg;
property *backtrack;             // backtrack()
property *base;
property *begin;
property *body;
property *boolean_I;
property *c_princ;
property *cast_I;
property *cdr;
property *cerr; //<sb>
property *char_I;
property *choice;                    // branch()
property *close;
//property *clearerr; //<sb>
property *code;
property *cons;
property *contain_ask;
property *copy;
property *cout;
property *ctrace;                      
property *comment;
property *commit;            // commit()
property *commit0;                      // commit0()
property *count_call;                              // count the numbers of call
property *count_level;                 // level at which something happens ...
property *count_trigger;               // what should happen
property *date_I;
property *debug_I;
property *definition;
operation *_delete;
property *defined;
property *descendents;
property *dictionary;
property *dispatcher;                  // new in v3.1: fast dispatch
property *domain;
property *empty;                       // new in v3.1
property *end;
property *ephemeral;
property *evaluate;
property *exception_I;
property *external;
property *fastcall;
//property *fclose;
property *find_ask;
property *float_I;
//property *flush;
//property *fopen;
property *formula;
property *freadline;
property *freadwrite;
property *prefree_I; //<sb>
property *free_I; //<sb>
property *freeme_ask; //<sb>
property *funcall;
property *functional;
property *gensym;
property *get;
//property *getc;
property *get_index; //<sb>
//property *ungetc; //<sb> 
//property *eof_ask; //<sb> test eof on a port
property *set_index;
property *index_jump;
//property *setvbuf; //<sb>
property *alpha_ask; //<sb>
property *graph;
property *hash;
property *ident_ask;
property *if_write;
property *imported; //<sb>
property *included;
property *index;
property *inline_ask;
property *integer_I;
property *instances;
property *inverse;
property *isa;
property *last_debug;
property *last_index;         // last value of the top of eval stack
property *last_trace;
property *length;
property *list_I;
property *made_of;
property *make_list;
property *make_string;
property *make_table; //<sb> put make_table at kernel level
property *mem;
property *member_ask;
property *mod;
property *module_I;           //  was module
property *multivalued_ask;
property *name;
property *nth;
property *nth_get;
property *nth_put;
property *nth_equal;
property *nth_dash;
property *nth_plus;
//property *null_I; //<sb>
property *of;
property *open;
property *params;
property *parts;
property *part_of;
//property *port_I;
property *precedence;
property *princ;
property *color_princ; //<sb>
property *print;
property *prototype;
property *put;
//property *putc;
property *random;
property *random_I;
property *range;
property *read_ident;
property *read_number;
property *read_string;
property *read_thing;
property *reified;
property *restrictions;
property *restore_state;
property *reverse; //<sb>
//property *reverse_I; //<sb>
property *selector;
property *self_print;
property *set_I;
//property *set_length;
property *shrink;
property *symbol_I;
property *slots;
property *slot_get;
property *sname;
property *sort_I;
property *source;
property *spy_I;                       // store the spy method if any
property *srange;
property *stat;
property *status;
property *stack_apply;
property *step_I;
property *store;
property *store_ask;
property *string_I;
property *superclass;
property *subclass;
property *substring;
property *trace_I;
property *typing;
property *use_as_output;
property *uses;
property *value;
property *verbose;
property *version;
property *world_ask;
property *world_id;

property *bin_I; //<sb>
property *hex_I; //<sb>

property *fread;
property *fwrite;

property *prealloc_set;
property *prealloc_list;
//<sb> color
property *color;

//<sb> - stringtool properties
property *lower_ask;
property *upper_ask;
property *upper;
property *lower;
property *space_ask;
property *digit_ask;
property *replace;
property *occurrence;
property *find;
property *rfind;
property *ltrim;
property *rtrim;
property *trim;
property *left;
property *right;
property *explode;
property *explode_wildcard;

//<sb> - env properties
property *ding;
property *cerror;
property *setenv;
property *environ;
property *setcwd;
property *pwd;
property *maxenv;
property *isenv_ask;

//<sb> - encoding properties
property *url_encode;
property *url_decode;
property *mime_decode;
property *mime_encode;
property *encode64;
property *decode64;
property *unescape;
property *escape;

//<sb> - process properties
property *getuid;
property *getpid;
property *getppid;
property *cfork;
property *forked;
property *kill;
property *run_ask;
property *wait;
property *process_I;
//property *popen;
property *waitpid_status;

//<sb> - dir/file properties
property *match_wildcard_ask;
property *entries;
property *entry;
property *isdir_ask;
property *isfile_ask;
property *unlink;
property *mkdir;
property *rmdir;
property *chmod;
property *link;
property *symlink;
property *fcopy;
property *fmove;
property *fsize;
property *fchanged;
property *fmodified;
property *faccessed;
property *fmode;
property *realpath;
property *flock;
property *funlock;
property *islocked_ask;

//<sb> - time date properties
property *timer_I;
property *elapsed;
property *sleep;
property *setlocale;
property *getlocale;
property *make_time;
property *make_date;
property *strftime;
property *diff_time;
property *date_add;
property *now;
property *uptime;
property *uid;
property *tzset;

//<sb> - uname properties
property *sys_name;
property *sys_node_name;
property *sys_release;
property *sys_version;
property *sys_machine;
property *sys_arch;
property *sys_compiler;
property *sys_compiler_version;

property *find_which;
// tables
// global variables
symbol *PRIVATE;
thing *NoDefault;
set *emptySet;                          // one unique representation for emptyset
list *nil;
symbol *unknownName;
OID ctrue;
OID cfalse;

system_error *GcError; //<sb> static error instance that can be raised by the gc
symbol *UNAMED;

void bootstrap();
void metaLoad();                     // creates all the metaObjects
};

extern CL_EXPORT KernelClass Kernel;
extern CL_EXPORT NameSpace mClaire;



// profiler methods (ClaireProfile -> KernelProfile)
// note: although PRcount is not defined here, it is Kernel.h
extern  CL_EXPORT class PRcount *PRstart(PRcount *p);          // the class keyword is key here !
extern CL_EXPORT void PRend(PRcount *p);
extern CL_EXPORT void PRloop(PRcount *p);
extern CL_EXPORT void default_main();                         // v3.2.50


// create a float  (specialized version of import)
// note that the automatic protection is a necessary burden that frees the compiler from
// generating protection that will be un-necessary if the optimization produces native
// code, which is expected in most cases
static inline OID _float_(double v)
{ClaireFloat *obj = (ClaireFloat *) ClAlloc->makeAny(4);
   if (ClAlloc->statusGC != 2) GC_PUSH(obj);                // v3.2.28   (cf import in ClAlloc), v3.2.30
   obj->isa = Kernel._float;
   obj->value = v;
   return _oid_(obj);}

// makes a oid from an integer
static inline CL_INT _integer_(CL_INT n)
{  if INTEGERP(n) return n; else Cerror(19,0,0); return 1;}





static inline void princ_integer(CL_INT i) {ClEnv->cout->put(i);}

// arithmetic functions
static inline CL_INT ch_sign(CL_INT n)
{ return (-n) ;}

static inline CL_INT _7_integer(CL_INT n, CL_INT m)
{ if (m == 0) Cerror(20,n,0); return (n / m);}

static inline CL_INT mod_integer(CL_INT n, CL_INT m)
{ if (m == 0) Cerror(20,n,0); return (n % m);}

// v3.3.16: use float exponentiation and check overflow
static inline CL_INT _exp_integer(CL_INT n, CL_INT m)
{double a = (double) n, b = (double) m,  c = pow(a,b);
  if (c < CLMINFLOAT || c > CLMAXFLOAT) Cerror(40,n,m);
  return (CL_INT) c; }

// return a power of 2
static inline CL_INT exp2_integer(CL_INT n)
{if ((n >= 0) && (n <= 31)) return (1ul << n);
 else Cerror(19,0,0); return 1;}





// makes an integer into a float */
static inline OID to_float_ (CL_INT n) {return _float_((double) n);}
static inline double to_float (CL_INT n) {return  ((double) n);}

// create a  claire integer from a claire float */
static inline CL_INT integer_I_float(double n)
{ if (n < CLMINFLOAT || n > CLMAXFLOAT) Cerror(39,_float_(n),0);
  return _integer_((CL_INT) floor(n));}                         // v3.3
static inline CL_INT integer_I_float_(OID n) {return integer_I_float(float_v(n));}

// the classical order comparisons for two float
static inline ClaireBoolean *_inf_float(double n,double m)
{ if (n < m) return CTRUE;  else return CFALSE;}

static inline ClaireBoolean *_inf_equal_float(double n,double m)
{ if (n <= m) return CTRUE;  else return CFALSE;}

static inline ClaireBoolean *_sup_float(double n,double m)
{ if (n > m) return CTRUE;  else return CFALSE;}

static inline ClaireBoolean *_sup_equal_float(double n,double m)
{ if (n >= m) return CTRUE;  else return CFALSE;}

static inline ClaireBoolean *_inf_float_(OID n, OID m)
{ if (float_v(n) < float_v(m)) return CTRUE;  else return CFALSE;}

static inline ClaireBoolean *_inf_equal_float_(OID n, OID m)
{ if (float_v(n) <= float_v(m)) return CTRUE;  else return CFALSE;}

static inline ClaireBoolean *_sup_float_(OID n, OID m)
{ if (float_v(n) > float_v(m)) return CTRUE;  else return CFALSE;}

static inline ClaireBoolean *_sup_equal_float_(OID n, OID m)
{ if (float_v(n) >= float_v(m)) return CTRUE;  else return CFALSE;}


extern CL_EXPORT fd_set readset;
extern CL_EXPORT fd_set writeset;
extern CL_EXPORT CL_INT fdMaxfd;


//<sb> in XL version the support for buffer (seen as claire string)
// is highly improved with true bound checking
// a claire string may represent either by a C string (null terminated / strlen)
// or a pascal string (where the length of the string is maintained outside allowing
// presence of null char). The generic method length_string(char*) handle both cases.

#define BUFFER_LEN(s) *((CL_INT*)s - 1)

// tells if a string is a buffer
#define BUFFER_ASK(s) CLMEM(s)

#define BUFFER_LEN_IDX(s) ((((CL_UNSIGNED)s - ((CL_UNSIGNED) &Cmemory[0])) >> ADDRTRANS) - 1)

#define BUFFER_SET_LENGTH(s,l) *((CL_UNSIGNED*)s - 1) = l;

#define LENGTH_STRING(s) (CL_INT)((BUFFER_ASK(s)) ? (BUFFER_LEN(s)) : (strlen(s)))


#endif
