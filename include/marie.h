/***********************************************************************/
/**   microCLAIRE                                       Yves Caseau    */
/**   marie .h                                                         */
/**  Copyright (C) 1998-99 Yves Caseau. All Rights Reserved.           */
/**  Redistribution and use in source and binary forms are permitted   */
/**  provided that source distribution retains this entire copyright   */
/**  notice and comments.                                              */
/**  THIS SOFTWARE IS PROVIDED AS IS AND WITHOUT ANY WARRANTY,         */
/**  INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF          */
/**  MERCHANTABILTY AND FITNESS FOR A PARTICULAR PURPOSE               */
/***********************************************************************/

// this file contains the private header for the Kernel module
//<sb> we use this header to all configurable thing of the kernel


/***********************************************************************/
/** Contents                                                           */
/**    1. Constants                                                    */
/**    2. Macros                                                       */
/***********************************************************************/

/***********************************************************************/
/**    1. Constants                                                    */
/***********************************************************************/

/* in some machines (compilers) RAND is not be defined (appears to be true
   for both cc and g++ on sun. Note the actual constant may be machine
   dependent */
#ifndef RAND_MAX
#define RAND_MAX 0x7FFFFFFF
#endif

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 100
#endif

#ifndef EOF
#define EOF (char)(-1)
#endif

extern double CKernelRelease;

/************************************************************************/
/**    2. Macros & external functions                                   */
/************************************************************************/


#define msec(t)  {t = (CL_INT)(((double) clock()) * 1000.0 / ((double)CLOCKS_PER_SEC));}


#define ADR(A) (A & ADR_MASK)         /* the address                   */


// these are the two macros to convert between the CLAIRE & C++ representation

#define CLAIREOID(x,s) ((s == Kernel._object) ? _oid_(x) : \
                       ((s == Kernel._any) ? x : \
                       ((s == Kernel._integer) ? _integer_((CL_INT) x) : \
                       ((s == Kernel._array) ? _array_(x) : \
                       ((s == Kernel._void) ? CNULL : ClAlloc->import(s,(OID *) x))))))

#define CPOINTER(x,s) ((s == Kernel._object) ? ((CL_INT)(x << ADDRTRANS)) : \
                      ((s == Kernel._any || s == Kernel._integer) ? x : \
                      ((s == Kernel._array) ? ((CL_INT) array_v(x)) : \
                      ((s == Kernel._void) ? NULL : OBJECT(ClaireImport,x)->value))))


// read the n-th slot of the object x
#define SLOTADR(x,n) ((CL_INT *) x + (n - 1))
// no longer used #define SORT(r) ((class ClaireClass *) Lmemory[ADR(r) + 7])

#define ARRAYTYPE(a)  ((ClaireType *) a[-1])
#define ARRAYLENGTH(a)  a[0]
#define ARRAYFLOAT(a) (a[-1] == (CL_INT) Kernel._float)


// we now have three macros STOREOID, STOREOBJ and STOREFLOAT
// STOREOID(x,y)  does the book-keeping so that the value y (an OID) for x (a container) in remembered
// for a defeasible update
#define STOREOID(x,y) {if (++ClRes->iIndex >= ClAlloc->maxHist && worldCongestion() == 0) Cerror(37,1,0); \
						ClRes->haiStack[ClRes->iIndex] = (OID*)x; ClRes->hviStack[ClRes->iIndex] = (OID)y;}

// same when y is an object (X*) and x a containter
#define STOREOBJ(x,y) {if (++ClRes->oIndex >= ClAlloc->maxHist && worldCongestion() == 0) Cerror(37,2,0); \
						ClRes->haoStack[ClRes->oIndex] = (OID*)x; ClRes->hvoStack[ClRes->oIndex] = (ClaireObject*)y; }
                       

#define STOREFLOAT(x,y) {if (++ClRes->fIndex >= ClAlloc->maxHist && worldCongestion() == 0) Cerror(37,3,0); \
						ClRes->hafStack[ClRes->fIndex] = (double *) x;\
                         ClRes->hvfStack[ClRes->fIndex] = y;}



extern void see(OID x);
extern void see(OID x, CL_INT i);
extern void see(char *c,OID x,int i);
extern void see(char *c,OID x);

// for debug
//#define getADR(A) ((CL_INT)A >> 2)  // gets the ADR from the object

// stupid list but necessary for true C++ portability ------------------
// note that we got rid of half of this junk by being optimistic .....
typedef CL_INT (*fptr1) (CL_INT);
typedef CL_INT (*fptr2) (CL_INT,CL_INT);
typedef CL_INT (*fptr3) (CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr4) (CL_INT,CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr5) (CL_INT,CL_INT,CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr6) (CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr7) (CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr8) (CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr9) (CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr10) (CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr11) (CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr12) (CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr13) (CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr14) (CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr15) (CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr16) (CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr17) (CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr18) (CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr19) (CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT);
typedef CL_INT (*fptr20) (CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT,CL_INT);


// used to compile properly the system profiling methods defined in ClPort
// note that this definition is produced in Reader.h
class PRcount: public ClaireObject{ 
  public:
     CL_INT rtime;
     CL_INT rdepth;
     CL_INT rnum;
     CL_INT rloop;
     CL_INT rstart;};


