/***** CLAIRE Compilation of file ./meta/signal.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:36 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>

//*********************************************************************
//* CLAIRE                                            Sylvain Benilan *
//* signal.cl                                                         *
//* Copyright (C) 2000 - 2003 xl. All Rights Reserved                 *
//*********************************************************************
// this file contains signal handling methods and some tools to
// manipulate the process signal mask.
// *********************************************************************
// *  Table of contents                                                *
// *   Part 1: signal handler definition                               *
// *   Part 2: signal API                                              *
// *   Part 3: signal mask                                             *
// *   Part 4: itimer                                                  *
// *   Part 5: waitpid                                                 *
// *   Part 6: fcntl                                                   *
// *********************************************************************
// *********************************************************************
// *   Part 1: signal handler definition                               *
// *********************************************************************
// in claire signals are named objects.
// something different from SIG_DFL or SIG_IGN (i.e. external)
//<sb> setup signal handlers
// *********************************************************************
// *   Part 2: signal API                                              *
// *********************************************************************
//<sb> install a signal handler
// returns the old property associated with the signal
// The c++ function for: signal(sig:signal_handler,p:property) [SLOT_UPDATE]
property * signal_signal_handler(signal_handler *sig,property *p)
{ { property *Result ;
    if (unix_ask_void1() == CTRUE)
     { if (sig->signo == ((CL_INT)-1))
       close_exception(((general_error *) (*Core._general_error)(_string_("signal ~S not available on this machine"),
        _oid_(list::alloc(1,_oid_(sig))))));
      if ((p == Core.CL_SIG_DFL) && 
          (sig != Core.CL_SIGINT))
       { if ((int )((signal(sig->signo, SIG_DFL)==SIG_ERR)) == 1)
         { if ((sig == Core.CL_SIGKILL) || 
              (sig == Core.CL_SIGSTOP))
           close_exception(((general_error *) (*Core._general_error)(_string_("an attempt is made to ignore or supply a handler (~S) for ~S"),
            _oid_(list::alloc(2,_oid_(p),_oid_(sig))))));
          else close_exception(((general_error *) (*Core._general_error)(_string_("signal ~S is not a valid signal number"),
              _oid_(list::alloc(1,_oid_(sig))))));
            }
        }
      else if (p == Core.CL_SIG_IGN)
       { if ((int )((signal(sig->signo, SIG_IGN)==SIG_ERR)) == 1)
         { if ((sig == Core.CL_SIGKILL) || 
              (sig == Core.CL_SIGSTOP))
           close_exception(((general_error *) (*Core._general_error)(_string_("an attempt is made to ignore or supply a handler (~S) for ~S"),
            _oid_(list::alloc(2,_oid_(p),_oid_(sig))))));
          else close_exception(((general_error *) (*Core._general_error)(_string_("signal ~S is not a valid signal number"),
              _oid_(list::alloc(1,_oid_(sig))))));
            }
        }
      else if ((int )((signal(sig->signo, kernel_sighandler_integer)==SIG_ERR)) == 1)
       { if ((sig == Core.CL_SIGKILL) || 
            (sig == Core.CL_SIGSTOP))
         close_exception(((general_error *) (*Core._general_error)(_string_("an attempt is made to ignore or supply a handler (~S) for ~S"),
          _oid_(list::alloc(2,_oid_(p),_oid_(sig))))));
        else close_exception(((general_error *) (*Core._general_error)(_string_("signal ~S is not a valid signal number"),
            _oid_(list::alloc(1,_oid_(sig))))));
          }
      { property * old = sig->handler;
        (sig->handler = p);
        Result = old;
        }
      }
    else Result = p;
      POP_SIGNAL; return (Result);}
  }


//<sb> this is the meta signal handler
// we dispach it according to the current mapping sig/handler in claire.
// note that we catch any exception that can occur during the handler
// a false value is returned in such situation, this tell kernel handler
// to re-close the execption after having restore a correct sigprocmask
// IN CLAIRE A SIGNAL HANDLER REMAINS INSTALLED AFTER ITS DELIVERY
// The c++ function for: meta_sighandler(sigv:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
ClaireBoolean * meta_sighandler_integer(int sigv)
{ GC_BIND;
  { ClaireBoolean *Result ;
    { ClaireObject *V_CC ;
      if (unix_ask_void1() == CTRUE)
       { ClaireHandler c_handle = ClaireHandler();
        if ERROR_IN 
        { { OID  sig = nth_table1(Core.SIG_MAP,((OID)sigv));
            property * p = OBJECT(signal_handler,sig)->handler;
            if (sigv == ((CL_INT)-1))
             { system_error * _CL_obj = ((system_error *) GC_OBJECT(system_error,new_object_class(Kernel._system_error)));
              (_CL_obj->index = 57);
              add_I_property(Kernel.instances,Kernel._system_error,11,_oid_(_CL_obj));
              close_exception(_CL_obj);
              }
            else if ((p != Core.CL_SIG_DFL) && 
                ((p != Core.CL_SIG_IGN) && 
                  (p != Core.SIG_EXT)))
             { OID  htest;
              { { OID  m_some = CNULL;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    ITERATE(m);
                    for (START(p->restrictions); NEXT(m);)
                    { ClaireBoolean * g0134I;
                      { list * dom = OBJECT(restriction,m)->domain;
                        g0134I = (((dom->length == 1) && 
                            ((*(dom))[1] == _oid_(Kernel._void))) ? CTRUE : ((belong_to(sig,(*(dom))[1]) == CTRUE) ? CTRUE : CFALSE));
                        }
                      
                      if (g0134I == CTRUE) { m_some= m;
                          ClEnv->cHandle = loop_handle; break;}
                        }
                    }
                  htest = m_some;
                  }
                GC_OID(htest);}
              if (htest != CNULL)
               { restriction * h = OBJECT(restriction,htest);
                if ((*(h->domain))[1] == _oid_(Kernel._integer))
                 apply_property(p,list::alloc(1,sig));
                else apply_property(p,list::alloc(1,_oid_(Kernel._void)));
                  }
              else close_exception(((general_error *) (*Core._general_error)(_string_("No available restriction of ~S to deliver signal ~S"),
                  _oid_(list::alloc(2,_oid_(p),sig)))));
                }
            else if ((sig == _oid_(Core.CL_SIGINT)) && 
                (p != Core.CL_SIG_IGN))
             { system_error * _CL_obj = ((system_error *) GC_OBJECT(system_error,new_object_class(Kernel._system_error)));
              (_CL_obj->index = 34);
              add_I_property(Kernel.instances,Kernel._system_error,11,_oid_(_CL_obj));
              close_exception(_CL_obj);
              }
            V_CC = CTRUE;
            }
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
        { c_handle.catchIt();V_CC = CFALSE;
          }
        else PREVIOUS_HANDLER;}
      else V_CC = CFALSE;
        Result= (ClaireBoolean *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: raise(sig:signal_handler) [0]
void  raise_signal_handler(signal_handler *sig)
{ if ((int )((raise(sig->signo) == -1)) == 1)
   Cerrorno(87,_integer_(sig->signo),0);
  POP_SIGNAL;}


// The c++ function for: kill(p:integer,sig:signal_handler) [0]
void  kill_integer(int p,signal_handler *sig)
{ 
#if defined(CLPC) || !defined(HAVE_KILL)
		Cerror(75,_string_("kill"),0);
	#else
		if(kill(p,sig->signo) == -1)
			Cerrorno(86,_integer_(p),_integer_(sig->signo));
	#endif
	;
  POP_SIGNAL;}


// *********************************************************************
// *   Part 3: signal mask                                             *
// *********************************************************************
// The c++ function for: sigprocmask(_CL_obj:void) [NEW_ALLOC]
set * sigprocmask_void()
{ { set *Result ;
    { set * l = set::empty(Core._signal_handler);
      
#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)
;
      Cerror(75,_string_("sigprocmask"),0);
      
#else
;
      sigset_t ss;
      sigemptyset(&ss);
      sigprocmask(SIG_SETMASK,0,&ss);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(g0135);
        bag *g0135_support;
        g0135_support = Core._signal_handler->descendents;
        for (START(g0135_support); NEXT(g0135);)
        { ClaireBoolean * g0136;
          { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(sig);
              V_C= Kernel.cfalse;
              for (START(OBJECT(ClaireClass,g0135)->instances); NEXT(sig);)
              if (OBJECT(signal_handler,sig)->signo != ((CL_INT)-1))
               { signal_handler * sh = OBJECT(signal_handler,sig);
                if ((int )(sigismember(&ss,sh->signo)) != 0)
                 l= l->addFast((OID)sig);
                }
              }
            
            g0136=OBJECT(ClaireBoolean,V_C);}
          if (g0136 == CTRUE)
           { ;ClEnv->cHandle = loop_handle; break;}
          }
        }
      
#endif
;
      Result = l;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: sigsetmask(self:subtype[signal_handler]) [NEW_ALLOC]
set * sigsetmask_type(ClaireType *self)
{ GC_BIND;
  { set *Result ;
    { set * l = set::empty(Core._signal_handler);
      
#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)
;
      Cerror(75,_string_("sigprocmask"),0);
      
#else
;
      sigset_t ss,so;
      sigemptyset(&ss);sigemptyset(&so);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(sig);
        bag *sig_support;
        sig_support = GC_OBJECT(bag,enumerate_any(_oid_(self)));
        for (START(sig_support); NEXT(sig);)
        { signal_handler * sh = OBJECT(signal_handler,sig);
          sigaddset(&ss,sh->signo);
          }
        }
      sigprocmask(SIG_SETMASK,&ss,&so);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(g0137);
        bag *g0137_support;
        g0137_support = Core._signal_handler->descendents;
        for (START(g0137_support); NEXT(g0137);)
        { ClaireBoolean * g0138;
          { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(sig);
              V_C= Kernel.cfalse;
              for (START(OBJECT(ClaireClass,g0137)->instances); NEXT(sig);)
              if (OBJECT(signal_handler,sig)->signo != ((CL_INT)-1))
               { signal_handler * sh = OBJECT(signal_handler,sig);
                if ((int )(sigismember(&so,sh->signo)) != 0)
                 l= l->addFast((OID)sig);
                }
              }
            
            g0138=OBJECT(ClaireBoolean,V_C);}
          if (g0138 == CTRUE)
           { ;ClEnv->cHandle = loop_handle; break;}
          }
        }
      
#endif
;
      Result = l;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: sigpending(_CL_obj:void) [NEW_ALLOC]
set * sigpending_void()
{ { set *Result ;
    { set * l = set::empty(Core._signal_handler);
      
#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)
;
      Cerror(75,_string_("sigpending"),0);
      
#else
;
      sigset_t ss;
      if(sigpending(&ss) == -1) Cerrorno(74,_string_("sigpending @ void"),0);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(g0139);
        bag *g0139_support;
        g0139_support = Core._signal_handler->descendents;
        for (START(g0139_support); NEXT(g0139);)
        { ClaireBoolean * g0140;
          { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(sig);
              V_C= Kernel.cfalse;
              for (START(OBJECT(ClaireClass,g0139)->instances); NEXT(sig);)
              if (OBJECT(signal_handler,sig)->signo != ((CL_INT)-1))
               { signal_handler * sh = OBJECT(signal_handler,sig);
                if ((int )(sigismember(&ss,sh->signo)) != 0)
                 l= l->addFast((OID)sig);
                }
              }
            
            g0140=OBJECT(ClaireBoolean,V_C);}
          if (g0140 == CTRUE)
           { ;ClEnv->cHandle = loop_handle; break;}
          }
        }
      
#endif
;
      Result = l;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: sigblock(self:subtype[signal_handler]) [NEW_ALLOC]
set * sigblock_type(ClaireType *self)
{ GC_BIND;
  { set *Result ;
    { set * l = set::empty(Core._signal_handler);
      
#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)
;
      Cerror(75,_string_("sigprocmask"),0);
      
#else
;
      sigset_t ss,so;
      sigemptyset(&ss);sigemptyset(&so);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(sig);
        bag *sig_support;
        sig_support = GC_OBJECT(bag,enumerate_any(_oid_(self)));
        for (START(sig_support); NEXT(sig);)
        { signal_handler * sh = OBJECT(signal_handler,sig);
          sigaddset(&ss,sh->signo);
          }
        }
      sigprocmask(SIG_BLOCK,&ss,&so);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(g0141);
        bag *g0141_support;
        g0141_support = Core._signal_handler->descendents;
        for (START(g0141_support); NEXT(g0141);)
        { ClaireBoolean * g0142;
          { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(sig);
              V_C= Kernel.cfalse;
              for (START(OBJECT(ClaireClass,g0141)->instances); NEXT(sig);)
              if (OBJECT(signal_handler,sig)->signo != ((CL_INT)-1))
               { signal_handler * sh = OBJECT(signal_handler,sig);
                if ((int )(sigismember(&so,sh->signo)) != 0)
                 l= l->addFast((OID)sig);
                }
              }
            
            g0142=OBJECT(ClaireBoolean,V_C);}
          if (g0142 == CTRUE)
           { ;ClEnv->cHandle = loop_handle; break;}
          }
        }
      
#endif
;
      Result = l;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: sigunblock(self:subtype[signal_handler]) [NEW_ALLOC]
set * sigunblock_type(ClaireType *self)
{ GC_BIND;
  { set *Result ;
    { set * l = set::empty(Core._signal_handler);
      
#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)
;
      Cerror(75,_string_("sigprocmask"),0);
      
#else
;
      sigset_t ss,so;
      sigemptyset(&ss);sigemptyset(&so);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(sig);
        bag *sig_support;
        sig_support = GC_OBJECT(bag,enumerate_any(_oid_(self)));
        for (START(sig_support); NEXT(sig);)
        { signal_handler * sh = OBJECT(signal_handler,sig);
          sigaddset(&ss,sh->signo);
          }
        }
      sigprocmask(SIG_UNBLOCK,&ss,&so);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(g0143);
        bag *g0143_support;
        g0143_support = Core._signal_handler->descendents;
        for (START(g0143_support); NEXT(g0143);)
        { ClaireBoolean * g0144;
          { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(sig);
              V_C= Kernel.cfalse;
              for (START(OBJECT(ClaireClass,g0143)->instances); NEXT(sig);)
              if (OBJECT(signal_handler,sig)->signo != ((CL_INT)-1))
               { signal_handler * sh = OBJECT(signal_handler,sig);
                if ((int )(sigismember(&so,sh->signo)) != 0)
                 l= l->addFast((OID)sig);
                }
              }
            
            g0144=OBJECT(ClaireBoolean,V_C);}
          if (g0144 == CTRUE)
           { ;ClEnv->cHandle = loop_handle; break;}
          }
        }
      
#endif
;
      Result = l;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: sigsuspend(self:subtype[signal_handler]) [NEW_ALLOC]
void  sigsuspend_type(ClaireType *self)
{ GC_BIND;
  
#if defined(CLPC) || !defined(HAVE_SIGPROCMASK)
;
  Cerror(75,_string_("sigsuspend"),0);
  
#else
;
  sigset_t ss;
  sigemptyset(&ss);
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(sig);
    bag *sig_support;
    sig_support = GC_OBJECT(bag,enumerate_any(_oid_(self)));
    for (START(sig_support); NEXT(sig);)
    { signal_handler * sh = OBJECT(signal_handler,sig);
      sigaddset(&ss,sh->signo);
      }
    }
  sigsuspend(&ss);
  
#endif
;
  GC_UNBIND; POP_SIGNAL;}


//<sb> install the SIGINT (system_error 34) handler
// *********************************************************************
// *   Part 4: itimer                                                  *
// *********************************************************************
// The c++ function for: setitimer(g0145:itimer,g0146:integer,g0147:integer) [NEW_ALLOC]
tuple * setitimer_itimer_(Core_itimer *g0145,int g0146,int g0147)
{ return setitimer_itimer(g0145,g0146,g0147)->copyIfNeeded();}


// The c++ function for: setitimer(it:itimer,interval:integer,value:integer) [NEW_ALLOC]
tuple * setitimer_itimer(Core_itimer *it,int interval,int value)
{ { tuple *Result ;
    { CL_INT  ointerval = 0;
      CL_INT  ovalue = 0;
      
#if defined(CLPC) || !defined(HAVE_SETITIMER)
;
      Cerror(75,_string_("setitimer"),0);
      
#else
;
      struct itimerval sit,osit;
      sit.it_interval.tv_sec = interval / 1000;
      sit.it_interval.tv_usec = interval % 1000;
      sit.it_value.tv_sec = value / 1000;
      sit.it_value.tv_usec = value % 1000;
      if(setitimer(it->timerno, &sit, &osit) == -1) {;
      Cerrorno(88, it->timerno, 0); };
      ointerval= (int )(osit.it_interval.tv_sec * 1000 + osit.it_interval.tv_usec);
      ovalue= (int )(osit.it_value.tv_sec * 1000 + osit.it_value.tv_usec);
      
#endif
;
      Result = tuple::allocStack(2,((OID)ointerval),((OID)ovalue));
      }
    return (Result);}
  }


// The c++ function for: getitimer(g0148:itimer) [NEW_ALLOC]
tuple * getitimer_itimer_(Core_itimer *g0148)
{ return getitimer_itimer(g0148)->copyIfNeeded();}


// The c++ function for: getitimer(it:itimer) [NEW_ALLOC]
tuple * getitimer_itimer(Core_itimer *it)
{ { tuple *Result ;
    { CL_INT  interval = 0;
      CL_INT  value = 0;
      
#if defined(CLPC) || !defined(HAVE_GETITIMER)
;
      Cerror(75,_string_("getitimer"),0);
      
#else
;
      struct itimerval sit;
      if(getitimer(it->timerno, &sit) == -1) {;
      Cerrorno(89, it->timerno, 0); };
      interval= (int )(sit.it_interval.tv_sec * 1000 + sit.it_interval.tv_usec);
      value= (int )(sit.it_value.tv_sec * 1000 + sit.it_value.tv_usec);
      
#endif
;
      Result = tuple::allocStack(2,((OID)interval),((OID)value));
      }
    return (Result);}
  }


// *********************************************************************
// *   Part 5: waitpid                                                 *
// *********************************************************************
// The c++ function for: (CL_INT *)g0152:integer,g0153:boolean) [NEW_ALLOC]
tuple * waitpid_integer1_(int g0152,ClaireBoolean *g0153)
{ return waitpid_integer1(g0152,g0153)->copyIfNeeded();}


// The c++ function for: (CL_INT *)p:integer,block?:boolean) [NEW_ALLOC]
tuple * waitpid_integer1(int p,ClaireBoolean *block_ask)
{ GC_BIND;
  { tuple *Result ;
    { tuple * g0149 = waitpid_status_integer(p,block_ask);
      CL_INT  status = (*(g0149))[1];
      CL_INT  pid = (*(g0149))[2];
      CL_INT  no = (*(g0149))[3];
      process_status * pstatus = ((status == 0) ?
        Core.CL_WRUNNING :
        ((status == 3) ?
          Core.CL_WSIGNALED :
          ((status == 2) ?
            Core.CL_WSTOPPED :
            Core.CL_WEXITED ) ) );
      if (pstatus == Core.CL_WEXITED)
       { OID v_bag;
        GC_ANY(Result= tuple::empty());
        ((tuple *) Result)->addFast((OID)_oid_(pstatus));
        ((tuple *) Result)->addFast((OID)((OID)pid));
        if (no == ((CL_INT)-1))
         v_bag = CNULL;
        else v_bag = ((OID)no);
          ((tuple *) Result)->addFast((OID)v_bag);}
      else { OID  sigtest;
          { { OID  sig_some = CNULL;
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(g0150);
                bag *g0150_support;
                g0150_support = Core._signal_handler->descendents;
                for (START(g0150_support); NEXT(g0150);)
                { ClaireBoolean * g0151;
                  { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                      ITERATE(sig);
                      V_C= Kernel.cfalse;
                      for (START(OBJECT(ClaireClass,g0150)->instances); NEXT(sig);)
                      if (OBJECT(signal_handler,sig)->signo == no)
                       { V_C = sig_some= sig;
                        ClEnv->cHandle = loop_handle;break;}
                      }
                    
                    g0151=OBJECT(ClaireBoolean,V_C);}
                  if (g0151 == CTRUE)
                   { ;ClEnv->cHandle = loop_handle; break;}
                  }
                }
              sigtest = sig_some;
              }
            GC_OID(sigtest);}
          if (sigtest != CNULL)
           { signal_handler * sig = OBJECT(signal_handler,sigtest);
            Result = tuple::alloc(3,_oid_(pstatus),
              ((OID)pid),
              _oid_(sig));
            }
          else { OID v_bag;
              GC_ANY(Result= tuple::empty());
              ((tuple *) Result)->addFast((OID)_oid_(pstatus));
              ((tuple *) Result)->addFast((OID)((OID)pid));
              if (no == ((CL_INT)-1))
               v_bag = CNULL;
              else v_bag = ((OID)no);
                ((tuple *) Result)->addFast((OID)v_bag);}
            }
        }
    GC_UNBIND; return (Result);}
  }


// The c++ function for: (CL_INT *)g0154:integer) [NEW_ALLOC]
tuple * waitpid_integer2_(int g0154)
{ return waitpid_integer2(g0154)->copyIfNeeded();}


// The c++ function for: (CL_INT *)p:integer) [NEW_ALLOC]
tuple * waitpid_integer2(int p)
{ { tuple *Result ;
    Result = waitpid_integer1(p,CTRUE)->copyIfNeeded();
    return (Result);}
  }


// *********************************************************************
// *   Part 6: fcntl                                                   *
// *********************************************************************
//

