
// highly inspired by clconsole.cpp :)

#include "loader.h"
#include <Core.h>
#include <Language.h>
#include <Reader.h>
#include <conio.h>


/*********************************************************************/
/**    1. same as clconsole.cpp                                      */
/*********************************************************************/

int MODE = 0;               
list *STACK;              
#define TOP 0           
#define DEBUG 1
#define INSPECT 2

int store_i,store_b,store_d;
void loadInit();

// these are three functions that the console must provide to the claire
// system


/* starts an inspector */
int InspectLoop(list *l) {
	STACK = l; if(MODE == DEBUG) (ClEnv->trace_I = 1);
	MODE = INSPECT; return 1;} 

void loadInit() {
	ClaireHandler c = ClaireHandler();
	if ERROR_IN { load_string("d:\\claire\\v2.9\\src\\make\\init.cl"); ERROR_FREE; }
	else { c.catchIt(); printf(" >>>>>>>>>>>>>> please fix the init file ...\n"); } }   

/* start a debug loop */
void DebugLoop() {
	store_d= ClEnv->debug_I; store_b= ClEnv->base;
	store_i= ClEnv->index; Reader.reader->toplevel = CTRUE;
	MODE = DEBUG; princ_string("--------------- Debug -------------------\n"); }

// reads a character on the keyboard
int StepLoop() { CL_INT c = (CL_INT) getc(stdin); if(c != 10) getc(stdin); return c; }       

// reads a string on the keyboad
char *CommandLoopVoid(char* s) { 
	int i = 0; char c; static char buff[100];
	fflush(stdin); fflush(stdout);
	c = (char) getc(stdin);
	while (((c != '\n') && (c != '\r')) || (i == 0)) {
		buff[i++] = c; c =  getc(stdin); }
	buff[i] = '\0'; return buff; }

// default main
void default_main() {}  

// for debug
#define getADR(A) (((CL_INT) A - (CL_INT) &Cmemory[0]) >> 2)  // gets the ADR from the object
#define ADR(A) (A & ADR_MASK)         /* the address                   */

// printf an object with nested level of detail dp
void see(OID n,int dp)
{ if (n == CNULL)        printf("CNULL");
  else if (n == NOTHING) printf("NOTHING");
  else if INTEGERP(n) princ_integer(n);
  else if (OWNER(n) == Kernel._float) princ_float(float_v(n));
  else if (CTAG(n) == OBJ_CODE)
      {ClaireAny *x = OBJECT(ClaireAny,n);
       CL_INT u = getADR(x);
         if (x->isa == Kernel._list || x->isa == Kernel._set)
           {ITERATE(y);
            CL_INT i = 1;
            printf("%s[%d:%d](",((x->isa == Kernel._list) ? "list" : "set"),
                             ((bag *) x)->length, (((bag *) x)->content)[0]);
            if (((bag *) x)->length < 20 && dp > 0)
               {for (START(((bag *) x)); NEXT(y); )
                {see(y, dp - 1);printf(", ");}}
            else printf("...");
            printf(")");}
         else if (x->isa == Kernel._string) printf("'%s",((ClaireImport *) x)->value);
         else if (x == CTRUE) printf("CTRUE");
         else if (x == CFALSE) printf("CFALSE");
         else if (x->isa == Kernel._class)
              princ_string(((ClaireClass *) x)->comment);
         else if ((x->isa == Kernel._property) || (x->isa == Kernel._operation))
                  princ_string(((property *) x)->name->name);
         else if (x->isa == Kernel._char) printf("'%c'",((ClaireChar *) x)->ascii);
         else if (x->isa == Kernel._slot) {printf("slot<");
                                                 see(_oid_(((slot *) x)->selector));
                                                 printf(">");}
         else if (x->isa == Kernel._method) {printf("method<");
                                                 see(_oid_(((slot *) x)->selector));
                                                 printf("@");
                                                 see(_oid_(((method *) x)->domain),1);
                                                 printf(">");}
         else printf("<%s:%d>",x->isa->comment,ADR(n));}
 }

void see(OID x) {see(x,0);}

void see(char *s, OID x, CL_INT i)
{if (ClEnv->verbose >= 10)
   {printf("%s: ",s);
    see(x,i);
    printf("\n");}}

void seeIt(char *s, OID x)
{printf("%s: ",s);
 see(x,1);
 printf("\n");}
    
void see(char *s, OID x) {see(s,x,1);}

/*********************************************************************/
/**    3. memory (xl)                                                */
/*********************************************************************/

void init_stdio() {
	if(LOGO) printf("Init stdio\n");
	ClAlloc->stdOut->pimported = ClairePort::make(stdout);
	if(ClAlloc->stdOut->pimported == 0) CL_error_alloc();
	ClAlloc->stdErr->pimported = ClairePort::make(stderr);
	if(ClAlloc->stdErr->pimported == 0) CL_error_alloc();
	ClAlloc->stdIn->pimported = ClairePort::make(stdin);
	if(ClAlloc->stdIn->pimported == 0) CL_error_alloc(); }



//bbn here we allocate claire memory
// if you use claire as a shared library
// you'll need to call it by hand
// i & j corresponds to option '-s i j'
int allocateClaire(int i, CL_INT j) {
	ClAlloc = new ClaireAllocation;
	if(ClAlloc == 0) CL_error_alloc();
	ClAlloc->logList = 18 + i;
	if(LOGO) printf("Loglist = %d\n", ClAlloc->logList);
	ClAlloc->maxList = (1ul << (18 + i));
	ClAlloc->maxSize = (2ul << (18 + i));
	ClAlloc->maxList0 = (1ul << (18 + i));
	ClAlloc->maxSize0 = (2ul << (18 + i));
	ClAlloc->maxGC = 20000 * (1ul << j);
	ClAlloc->maxStack = 8000 * (1ul << j);                   // <yc> 9/98 changed because of GC
	ClAlloc->maxHist = 10000 * (1ul << j);
	ClAlloc->maxEnv = 400 * (1ul << j);
	ClAlloc->maxHash = ((1ul << (11 + i)) + 200);       // <yc> 7/98 Changed for claire3 !
	ClAlloc->hashMask = ((1ul << (11 + i)) - 1);
	

	ClaireResource::run();
	Reader.reader->fromp = ClAlloc->stdIn;  // special ?
	Reader.reader->nb_line = 0;
	Reader.reader->external = "toplevel";
	
	return ClRes && ClAlloc && Cmemory &&
		ClRes->sTable && ClRes->ascii && ClRes->haiStack &&
		ClRes->hviStack && ClRes->haoStack && ClRes->hvoStack &&
		ClRes->hafStack && ClRes->hvfStack && ClEnv->stack &&
		ClEnv->handlers && ClAlloc->gcStack;
}

#define MAINTRY ClaireHandler c_handle = ClaireHandler(); GC_BIND; if ERROR_IN {
#define MAINCATCH ERROR_FREE; } \
			else { main_err = 1;\
				c_handle.catchIt(); \
				ClEnv->cout = ClAlloc->stdOut; \
				print_any(_oid_(ClEnv->exception_I)); } GC_UNBIND;
				
//bbn here we free the memory allocated by claire
int freeClaire() {
	delete [] ClEnv->stack;
	delete [] ClEnv->handlers;
	#ifdef CLDEBUG
	Cmemory.free();
	#else
	free(Cmemory);
	#endif
	delete [] ClAlloc->gcStack;
	delete [] ClRes->hvfStack;
	delete [] ClRes->hafStack;
	delete [] ClRes->hvoStack;
	delete [] ClRes->haoStack;
	delete [] ClRes->hviStack;
	delete [] ClRes->haiStack;
	delete [] ClRes->ascii;
	delete [] ClRes->sTable;
	delete ClRes;
	delete ClAlloc;
	return 1; }

// bbn check memory params before allocation stuff
int startClaire(int i, CL_INT j) {
	ClAlloc = 0; ClRes = 0; Cmemory = 0;
	return i < 0 || i > 20 || j < 0 || j > 20 ? 0 : allocateClaire(i,j) != 0;
}
	
	
/*********************************************************************/
/**    5. System functions API                                       */
/*********************************************************************/

// these are three functions that the console must provide to the claire
// system

// exit
void CL_exit(int i) {
	int main_err = 0;
	MAINTRY 
	ClAlloc->freeAllFreeable();
	MAINCATCH
	fflush(stdout);
	exit(main_err ? main_err : i);}

// and _exit
void CL__exit(int i) {
	int main_err = 0;
	MAINTRY 
	ClAlloc->freeAllFreeable();
	MAINCATCH
	fflush(stdout);
	_exit(main_err ? main_err : i);}

// call to system
int CL_system(char *s) { return system(s); }
	
//bbn a dynamic allocation failed
void CL_error_alloc() {
	printf("There is not enough memory for CLAIRE, try claire -s 0 0\n");
	printf("bye...\n");
	//freeClaire(); //bbn TODO: free the memory of alocated object IF any
	exit(2); }

/*********************************************************************/
/**    3. Specials                                                   */
/*********************************************************************/

void ClaireStrPortIn::debugSee() 
{ 
	printf("I AM A ClaireStrPortIn !!\n");
}

char ClaireStrPortIn::get() 
{
	char c = buffer[index++];      
	if (c == '\0') return EOF; else return c;
}

void ClaireStrPortIn::unget(int c) 
{
	index--;
}

void ClaireStrPortOut::debugSee() 
{ 
	printf("I AM A ClaireStrPortOut !!\n");
}

void ClaireStrPortOut::put(char c) 
{
     buffer[index++] = c;
     if (index > OUTMAXBUF) Flush();
}

void ClaireStrPortOut::put(int n)
{ 
	sprintf(&buffer[index],"%d",n);
    for ( ;buffer[index] != '\0'; index++);
    if (index > OUTMAXBUF) Flush(); 
}

void ClaireStrPortOut::put(double x)
{ 
	if (floor(x) == x)  sprintf(&buffer[index],"%.1f",x);
    else sprintf(&buffer[index],"%g",x);
    for (;buffer[index] != '\0'; index++) ;
    if (index > OUTMAXBUF) Flush();
}

void ClaireStrPortOut::Flush()
{
	buffer[index] = '\0';
	mParent->Flush(buffer);
	index = 0;
}



OID  print_exception_voidLoader()
{ OID Result = 0;
  { use_as_output_port(ClAlloc->stdOut);
	  //ClairePort * p = use_as_output_port(EXPORT((ClairePort *),Reader.STDOUT->value));
    ClaireException * _Zerr = ClEnv->exception_I;
    method * _Zprop = ((method *) _at_property1(Kernel.self_print,OWNER(_oid_(_Zerr))));
    { ClaireHandler c_handle = ClaireHandler();
      if ERROR_IN 
      { if (_Zprop->functional != NULL)
         fcall1(_Zprop->functional,Kernel._object,_oid_(_Zerr),Kernel._any);
        else funcall_method1(_Zprop,_oid_(_Zerr));
          ClEnv->cHandle--;} 
      else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
      { c_handle.catchIt();princ_string("****** ERROR[121]: unprintable error has occurred.\n");
        } 
      else PREVIOUS_HANDLER;} 
  //  Result = ClAlloc->import(Kernel._port,(CL_INT *) use_as_output_port(p));
    } 
  return (Result);} 


OID  debug_if_possible_voidLoader()
{ OID Result = 0;
  if (0 <= ClEnv->debug_I)
   Result = fcall1(OBJECT(method,(*(Reader.call_debug->restrictions))[1])->functional,Kernel._any,_oid_(ClEnv),Kernel._any);
  else Result = print_exception_voidLoader();
    return (Result);} 


void Claire::TopLevel()
{
	mError = false;
	meta_reader* r = Reader.reader;
	OID res = 0, stop = _oid_(Reader.q);	
    {        
       ClaireHandler c = ClaireHandler();
       if ERROR_IN { GC_BIND;
                     r->toplevel = CTRUE;
                     if (ClEnv->count_call > 0) ClEnv->count_call = 1;
                     res = nextunit_meta_reader(r);
                         if (MODE == TOP) ClEnv->index = 20;
                         if ((MODE == INSPECT) && (res != stop))
                             inspect_loop_any(res,STACK);
                         else {res = eval_any(GC_OID(res));
                               if (res != stop)
                               {ClEnv->cout = pOut;print_any(res); }}
                       GC_UNBIND;
                       ERROR_FREE;}
        else {c.catchIt();				
		      mError = true;
			  if (ClEnv->exception_I->isa == Kernel._system_error &&
                  ((system_error *) ClEnv->exception_I)->index == -1)
                 {MODE = TOP; res = stop;}
              else {
              if (equal_string(r->external,"toplevel") == CFALSE)
                 {princ_string("---- file: "), princ_string(r->external);
                  princ_string(", line: "), princ_integer(r->nb_line);
                  ClEnv->cout->put('\n');}
			  debug_if_possible_voidLoader();
              // ClEnv->cout->put('\n');
                 }}
       if ((MODE != TOP) && (res == stop)) 
          {if (MODE == DEBUG) {ClEnv->index = store_i;
                               ClEnv->base = store_b;
                               ClEnv->trace_I = 1;
                               ClEnv->debug_I = store_d; }
           res = CNULL; MODE = TOP;}
     }			
}
        

void TopLevelFailure(Claire *cl)
{
	cl->mOut->index = 0;
	cl->Failure();
}

// initialisation
Claire::Claire()
{
	pIn = (FileObject*)make_port(Kernel._port,0);
	pOut = (FileObject*)make_port(Kernel._port,0);
	pIn->source = "loader in";
	pOut->source = "loader out";
	mIn = new ClaireStrPortIn;
    mOut = new ClaireStrPortOut;
	pIn->pimported = mIn;
	pOut->pimported = mOut;
	mOut->mParent = this;	
	mOut->index = 0;
}


// redirection stuff
void Claire::RedirectToMe()
{
    Reader.reader->fromp = pIn;
	ClEnv->cout = pOut;
	ClAlloc->stdOut = pOut;
	ClAlloc->stdErr = pOut;
}

// read service
bool Claire::Read(char* cmdline)
{
	RedirectToMe();
	SetCommand(cmdline);
	__try
	{
		TopLevel();
	}
	__except(1)
	{
		TopLevelFailure(this);						
		return false;
	}		
	mOut->Flush();
	End();
	return !mError;
}

bool Claire::IsValid(const char* cmdline)
{
	mError = false;
	int res;
	RedirectToMe();
	SetCommand((char*)cmdline);
	ClaireHandler c = ClaireHandler();
	int tmp1 = ClEnv->index;
	int tmp2 = ClEnv->count_call;	
	ClaireBoolean* tmp3 = Reader.reader->toplevel;
    if ERROR_IN 
	{ 
		GC_BIND;
		Reader.reader->toplevel = CTRUE;
		if (ClEnv->count_call > 0) ClEnv->count_call = 1;						
		res = nextunit_meta_reader(Reader.reader);
		print_any(res);
		GC_UNBIND;
		ERROR_FREE;
	}
    else 
	{
		c.catchIt();
		mError = true;
		print_exception_voidLoader();
	}	
	Reader.reader->toplevel = tmp3;
	ClEnv->count_call = tmp2;
	ClEnv->index = tmp1;
	return !mError;
}

// initialize input buffer 
void Claire::SetCommand(char *cmdline)                 
{
	mIn->index = 0;
	mIn->buffer = cmdline;
	mIn->firstc = ' ';
	mOut->index = 0;
}




