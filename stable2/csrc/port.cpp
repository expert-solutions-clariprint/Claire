/***** CLAIRE Compilation of file ./meta/port.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:36 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>

// *********************************************************************
// * CLAIRE                                            Sylvain Benilan *
// * port.cl                                                           *
// * Copyright (C) 2005 xl. All Rights Reserved                        *
// *********************************************************************
//<sb> This file is a port implementation written in claire that is
// compatible with <ycs> C++ implementation.
// In this implementation ports are organized into an extensible hierarchy
// of objects (instead of a primitive).
// Two sorts are defined :
//	- device : 'physical' port like a descriptor or a blob that may be handled
//				through a chain of filter.
//	- filter : port that may analyse and/or transform and/or collect read
//				and/or written datas like a buffer, a line counter or even a
//				MIME decoder or any kind embeded protocols.
// ***************************************************************************
// * part 1: low level char*                                                 *
// * part 1: model                                                           *
// * part 2: default interface                                               *
// * part 3: API                                                             *
// * part 4: null port                                                       *
// * part 4: blob                                                            *
// * part 5: buffer                                                          *
// * part 6: line_buffer                                                     *
// * part 7: byte_counter                                                    *
// * part 8: line_counter                                                    *
// * part 9: descriptor                                                      *
// * part 10: disk_file                                                      *
// * part 11: pipe                                                           *
// * part 12: socket                                                         *
// ***************************************************************************
// ***************************************************************************
// * part 1: low level char*                                                 *
// ***************************************************************************
// read and write operate on given buffer and a given size. these
// buffers are char* imported from C, this way we have in interface
// similar to read(2) and write(2) :
// The c++ function for: +(self:char*,n:integer) [SAFE_RESULT+SAFE_GC]
char* _plus_char_star1(char*self,int n)
{ POP_SIGNAL; return ((char*)((self + n)));}


//<sb> Warning: no bound check on char*
// The c++ function for: nth(self:char*,n:integer) [SAFE_RESULT+SAFE_GC]
ClaireChar * nth_char_star1(char*self,int n)
{ POP_SIGNAL; return (char_I_integer((int )(((unsigned char)(self[n-1])))));}


// The c++ function for: nth=(self:char*,n:integer,c:char) [SAFE_GC]
void  nth_equal_char_star1(char*self,int n,ClaireChar *c)
{ self[n-1] = (char)c->ascii;
  POP_SIGNAL;}


//<sb> make a new string from a char*
// The c++ function for: string!(self:char*,len:integer) [NEW_ALLOC+SAFE_GC]
char * string_I_char_star1(char*self,int len)
{ { char *Result ;
    { char * s = make_string_integer1(len);
      memcpy(s, self, len);
      Result = s;
      }
    POP_SIGNAL; return (Result);}
  }


//<sb> do not protect arguments in char* tools
// ***************************************************************************
// * part 1: model                                                           *
// ***************************************************************************
//<sb> port inherit from freeable_object, this way we can
// catch an instance deallocation (for instance to close an
// open descriptor).
//
// The c++ function for: get_top_most(self:port) [RETURN_ARG]
PortObject * get_top_most_port1(PortObject *self)
{ { PortObject *Result ;
    Result = ((INHERIT(self->isa,Core._device)) ?
      ((CLREAD(device,self,filters)->length != 0) ?
        OBJECT(PortObject,last_list(CLREAD(device,self,filters))) :
        self ) :
      ((INHERIT(self->isa,Core._filter)) ?
        OBJECT(PortObject,last_list(CLREAD(filter,self,dev)->filters)) :
        self ) );
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: get_device(self:port) [RETURN_ARG]
device * get_device_port1(PortObject *self)
{ { device *Result ;
    { ClaireObject *V_CC ;
      if (INHERIT(self->isa,Core._filter))
       V_CC = CLREAD(filter,self,dev);
      else if (INHERIT(self->isa,Core._device))
       V_CC = self;
      else close_exception(((general_error *) (*Core._general_error)(_string_("~S is not a device"),
          _oid_(list::alloc(1,_oid_(self))))));
        Result= (device *) V_CC;}
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: filter!(self:filter,p:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
filter * filter_I_filter1(filter *self,PortObject *p)
{ GC_BIND;
  if (p->closed_ask == CTRUE)
   close_exception(((general_error *) (*Core._general_error)(_string_("Attempt to add filter ~S to ~S that is already closed"),
    _oid_(Kernel.nil))));
  { filter *Result ;
    { OID  d;
      { if (INHERIT(p->isa,Core._device))
         d = _oid_(p);
        else if (INHERIT(p->isa,Core._filter))
         d = _oid_(CLREAD(filter,p,dev));
        else d = Kernel.cfalse;
          GC_OID(d);}
      list * fs = GC_OBJECT(list,OBJECT(device,d)->filters);
      OID  p;
      if (fs->length != 0)
       p = last_list(fs);
      else p = d;
        update_property(Core.dev,
        self,
        5,
        Kernel._object,
        d);
      (self->target = OBJECT(PortObject,p));
      Result = self;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: filter!_filter1_type
ClaireType * filter_I_filter1_type(ClaireType *self,ClaireType *p)
{ POP_SIGNAL; return (self);}


// The c++ function for: close_target!(self:filter) [SLOT_UPDATE+RETURN_ARG]
filter * close_target_I_filter1(filter *self)
{ (self->close_target_ask = CTRUE);
  POP_SIGNAL; return (self);}


// The c++ function for: close_target!_filter1_type
ClaireType * close_target_I_filter1_type(ClaireType *self)
{ POP_SIGNAL; return (self);}


// The c++ function for: self_print(self:filter) [NEW_ALLOC]
void  self_print_filter1_Core(filter *self)
{ GC_BIND;
  if (self->dev == (NULL))
   { princ_string("<unconneted ");
    print_any(_oid_(OWNER(_oid_(self))));
    princ_string(">");
    }
  else { princ_string("<");
      princ_string(OWNER(_oid_(self->dev))->name->name);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(f);
        bag *f_support;
        f_support = GC_OBJECT(list,self->dev->filters);
        for (START(f_support); NEXT(f);)
        if (f == _oid_(self))
         { princ_string("/*");
          princ_string(OWNER(f)->name->name);
          princ_string("*");
          }
        else { princ_string("/");
            princ_string(OWNER(f)->name->name);
            }
          }
      princ_string(">");
      }
    GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_print(self:device) [0]
void  self_print_device1_Core(device *self)
{ princ_string("<*");
  princ_string(OWNER(_oid_(self))->name->name);
  princ_string("*");
  { CL_INT loop_handle = ClEnv->cHandle;
    ITERATE(f);
    for (START(self->filters); NEXT(f);)
    { princ_string("/");
      princ_string(OWNER(f)->name->name);
      }
    }
  princ_string(">");
  POP_SIGNAL;}


// The c++ function for: princ(self:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  princ_port1(PortObject *self)
{ print_any(_oid_(OWNER(_oid_(self))));
  POP_SIGNAL;}


// ***************************************************************************
// * part 2: default interface                                               *
// ***************************************************************************
// The port interface :
//	- eof_port? : check the end-of-file
//	- read_port : read n bytes
//	- write_port : write n bytes
//	- flush_port : gives a chance for the port to write out any pending
//		datas (buffer)
//	- close_port : gives a chance for the port to clean internal datas
//<sb> read interface
//<sb> write interface
// The c++ function for: write_port(self:port,buf:char*,len:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
int  write_port_port1_Core(PortObject *self,char*buf,int len)
{ GC_BIND;
  { CL_INT Result = 0;
    { ClaireClass * c = OWNER(_oid_(self));
      OID  r = GC_OID(_oid_(_at_property1(Core.write_port,c)));
      if ((boolean_I_any(r) == CTRUE) && 
          ((*(OBJECT(bag,(*Kernel.domain)(r))))[1] == _oid_(c)))
       Result = apply_method(OBJECT(method,r),list::alloc(3,_oid_(self),
        GC_OID(ClAlloc->import(Core._char_star,(OID *) buf)),
        ((OID)len)));
      else if (INHERIT(self->isa,Core._filter))
       Result = Core.write_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(CLREAD(filter,self,target))))),((CL_INT) buf),((CL_INT) len));
      else { close_exception(((general_error *) (*Core._general_error)(_string_("write_port @ ~S not implemented"),
            _oid_(list::alloc(1,_oid_(OWNER(_oid_(self))))))));
          Result = 0;
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: read_port(self:port,buf:char*,len:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
int  read_port_port1_Core(PortObject *self,char*buf,int len)
{ GC_BIND;
  { CL_INT Result = 0;
    { ClaireClass * c = OWNER(_oid_(self));
      OID  r = GC_OID(_oid_(_at_property1(Core.read_port,c)));
      if ((boolean_I_any(r) == CTRUE) && 
          ((*(OBJECT(bag,(*Kernel.domain)(r))))[1] == _oid_(c)))
       Result = apply_method(OBJECT(method,r),list::alloc(3,_oid_(self),
        GC_OID(ClAlloc->import(Core._char_star,(OID *) buf)),
        ((OID)len)));
      else if (INHERIT(self->isa,Core._filter))
       Result = Core.read_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(CLREAD(filter,self,target))))),((CL_INT) buf),((CL_INT) len));
      else { close_exception(((general_error *) (*Core._general_error)(_string_("read_port @ ~S not implemented"),
            _oid_(list::alloc(1,_oid_(OWNER(_oid_(self))))))));
          Result = 0;
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: unget_port(self:port,buf:char*,len:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  unget_port_port1_Core(PortObject *self,char*buf,int len)
{ GC_BIND;
  { ClaireClass * c = OWNER(_oid_(self));
    OID  r = GC_OID(_oid_(_at_property1(Core.unget_port,c)));
    if ((boolean_I_any(r) == CTRUE) && 
        ((*(OBJECT(bag,(*Kernel.domain)(r))))[1] == _oid_(c)))
     apply_method(OBJECT(method,r),list::alloc(3,_oid_(self),
      GC_OID(ClAlloc->import(Core._char_star,(OID *) buf)),
      ((OID)len)));
    else if (INHERIT(self->isa,Core._filter))
     _void_(Core.unget_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(CLREAD(filter,self,target))))),((CL_INT) buf),((CL_INT) len)));
    else { close_exception(((general_error *) (*Core._general_error)(_string_("unget_port @ ~S not implemented"),
          _oid_(list::alloc(1,_oid_(OWNER(_oid_(self))))))));
        ;}
      }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: eof_port?(self:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
ClaireBoolean * eof_port_ask_port1_Core(PortObject *self)
{ GC_BIND;
  { ClaireBoolean *Result ;
    { ClaireObject *V_CC ;
      { ClaireClass * c = OWNER(_oid_(self));
        OID  r = GC_OID(_oid_(_at_property1(Core.eof_port_ask,c)));
        if ((boolean_I_any(r) == CTRUE) && 
            ((*(OBJECT(bag,(*Kernel.domain)(r))))[1] == _oid_(c)))
         V_CC = OBJECT(ClaireBoolean,apply_method(OBJECT(method,r),list::alloc(1,_oid_(self))));
        else if (INHERIT(self->isa,Core._filter))
         V_CC = OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(CLREAD(filter,self,target))))))));
        else { close_exception(((general_error *) (*Core._general_error)(_string_("eof_port? @ ~S not implemented"),
              _oid_(list::alloc(1,_oid_(OWNER(_oid_(self))))))));
            V_CC = 0;
            }
          }
      Result= (ClaireBoolean *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: flush_port(self:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  flush_port_port1_Core(PortObject *self)
{ GC_BIND;
  { ClaireClass * c = OWNER(_oid_(self));
    OID  r = GC_OID(_oid_(_at_property1(Core.flush_port,c)));
    if ((boolean_I_any(r) == CTRUE) && 
        ((*(OBJECT(bag,(*Kernel.domain)(r))))[1] == _oid_(c)))
     apply_method(OBJECT(method,r),list::alloc(1,_oid_(self)));
    else if (INHERIT(self->isa,Core._filter))
     _void_(Core.flush_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(CLREAD(filter,self,target)))))));
    else ;}
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: close_port(self:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  close_port_port1_Core(PortObject *self)
{ GC_BIND;
  { ClaireClass * c = OWNER(_oid_(self));
    OID  r = GC_OID(_oid_(_at_property1(Core.close_port,c)));
    if ((boolean_I_any(r) == CTRUE) && 
        ((*(OBJECT(bag,(*Kernel.domain)(r))))[1] == _oid_(c)))
     apply_method(OBJECT(method,r),list::alloc(1,_oid_(self)));
    else ;}
  GC_UNBIND; POP_SIGNAL;}


//<sb> activate fast disptach on port interface
// Note: interpreted messages won't be handled automaticaly since the
// interface for port uses fast dispatch. In default handlers we try to
// dispatch the message by hand. This is a limited support of dynamic
// dispatch, it will only work with interpreted code if it is based on
// default handlers (i.e. with domain port). The dynamic dispatch is safe
// on interpreted classes derived from device or filter whereas, for
// instance, an attemp to write on a port derived from descriptor will
// fail.
// ***************************************************************************
// * part 3: API                                                             *
// ***************************************************************************
//<sb> check wheither the end-of-file condition has been reached
// The c++ function for: eof?(self:port) [NEW_ALLOC+RETURN_ARG]
ClaireBoolean * eof_ask_port1(PortObject *self)
{ POP_SIGNAL; return (OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) self)))));}


//<sb> read a string of n bytes on self
// the length of the returned string may be
// lower than n if an eof condition is reached
// on self
// The c++ function for: fread(self:port,n:integer) [NEW_ALLOC]
char * fread_port4(PortObject *self,int n)
{ GC_BIND;
  { char *Result ;
    { char * s = GC_STRING(make_string_integer1(n));
      shrink_string(s,Core.read_port->fcall(((CL_INT) self),((CL_INT) (char*)(s)),((CL_INT) n)));
      Result = s;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> read inside an existing string, this overwrites
// the string content and may modify the string length
// if an eof condition is reached on self. the amount
// of queried bytes is the length of the input string
// The c++ function for: fread(self:port,s:string) [NEW_ALLOC]
int  fread_port5(PortObject *self,char *s)
{ GC_BIND;
  { CL_INT Result = 0;
    { CL_INT  n = LENGTH_STRING(s);
      CL_INT  on = Core.read_port->fcall(((CL_INT) self),((CL_INT) (char*)(s)),((CL_INT) n));
      shrink_string(s,on);
      Result = on;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> read all datas on self until eof
// The c++ function for: fread(self:port) [NEW_ALLOC]
char * fread_port6(PortObject *self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { char *Result ;
    { char * res = "";
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) self))) != Kernel.ctrue))
        { GC_LOOP;
          GC__STRING(res = append_string(res,GC_STRING(fread_port4(self,254))), 1);
          GC_UNLOOP;POP_SIGNAL;}
        }
      Result = res;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> read a single char on self
// reading an EOF char does not mean than
// the eof is reached, one should use eof? @ port
// to check the eof condition
// The c++ function for: getc(self:port) [NEW_ALLOC]
ClaireChar * getc_port1(PortObject *self)
{ GC_BIND;
  { ClaireChar *Result ;
    { ClaireObject *V_CC ;
      { char c;
        if (((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) self))))) == CTRUE) || 
            (Core.read_port->fcall(((CL_INT) self),((CL_INT) (char*)(&c)),((CL_INT) 1)) == ((OID)0)))
         V_CC = OBJECT(ClaireChar,Core._eof->value);
        else V_CC = (ClaireChar *)(_char_(c));
          }
      Result= (ClaireChar *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> unget a string (see buffer)
// The c++ function for: unget(self:port,s:string) [NEW_ALLOC]
void  unget_port1(PortObject *self,char *s)
{ GC_BIND;
  _void_(Core.unget_port->fcall(((CL_INT) self),((CL_INT) (char*)(s)),((CL_INT) LENGTH_STRING(s))));
  GC_UNBIND; POP_SIGNAL;}


//<sb> unget a char
// The c++ function for: unget(self:port,c:char) [NEW_ALLOC]
void  unget_port2(PortObject *self,ClaireChar *c)
{ GC_BIND;
  char ch = (char)c->ascii;
  _void_(Core.unget_port->fcall(((CL_INT) self),((CL_INT) (char*)((&ch))),((CL_INT) 1)));
  GC_UNBIND; POP_SIGNAL;}


//<sb> read a single UTF-8 sequence
//
//<sb> flush pending buffers in the chain such
// pending datas are actually written on the device
// The c++ function for: flush(self:port) [NEW_ALLOC+RETURN_ARG]
void  flush_port1(PortObject *self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { PortObject * p = self;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while ((INHERIT(p->isa,Core._filter)))
      { GC_LOOP;
        _void_(Core.flush_port->fcall(((CL_INT) p)));
        GC__ANY(p = CLREAD(filter,p,target), 1);
        GC_UNLOOP;POP_SIGNAL;}
      }
    _void_(Core.flush_port->fcall(((CL_INT) p)));
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: flush(self:port,n:integer) [SLOT_UPDATE+RETURN_ARG]
void  flush_port2(PortObject *self,int n)
{ (self->firstc = n);
  POP_SIGNAL;}


//<sb> writes a raw string on the port p
// The c++ function for: fwrite(self:string,p:port) [NEW_ALLOC]
int  fwrite_string2(char *self,PortObject *p)
{ GC_BIND;
  { CL_INT Result = 0;
    Result = Core.write_port->fcall(((CL_INT) p),((CL_INT) (char*)(self)),((CL_INT) LENGTH_STRING(self)));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> writes a single byte on p
// The c++ function for: putc(self:char,p:port) [NEW_ALLOC]
void  putc_char1(ClaireChar *self,PortObject *p)
{ GC_BIND;
  char c = (char)self->ascii;
  Core.write_port->fcall(((CL_INT) p),((CL_INT) (char*)(&c)),((CL_INT) 1));
  GC_UNBIND; POP_SIGNAL;}


//<sb> read all datas from src until eof and write it on trgt
// without performing any allocation.
// returns the amount of byte transfered
// The c++ function for: freadwrite(src:port,trgt:port) [NEW_ALLOC]
int  freadwrite_port3(PortObject *src,PortObject *trgt)
{ GC_BIND;
  if (src == trgt)
   close_exception(((general_error *) (*Core._general_error)(_string_("Attempt to freadwrite ~S on itself !"),
    _oid_(list::alloc(1,_oid_(src))))));
  char tmp[4096];
  { CL_INT Result = 0;
    { CL_INT  n = 0;
      char* buf = (char*)(tmp);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) src))) != Kernel.ctrue))
        { GC_LOOP;
          { CL_INT  m = Core.read_port->fcall(((CL_INT) src),((CL_INT) buf),((CL_INT) 4096));
            n= ((CL_INT)n+(CL_INT)m);
            Core.write_port->fcall(((CL_INT) trgt),((CL_INT) buf),((CL_INT) m));
            }
          GC_UNLOOP;POP_SIGNAL;}
        }
      Result = n;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> read upto len bytes from src and write them on trgt
// without performing any allocation.
// returns the amount of bytes actualy tranfered (may be
// lower than len if an eof condition is reached on src)
// The c++ function for: freadwrite(src:port,trgt:port,len:integer) [NEW_ALLOC]
int  freadwrite_port4(PortObject *src,PortObject *trgt,int len)
{ GC_BIND;
  if (src == trgt)
   close_exception(((general_error *) (*Core._general_error)(_string_("Attempt to freadwrite ~S on itself !"),
    _oid_(list::alloc(1,_oid_(src))))));
  char tmp[4096];
  { CL_INT Result = 0;
    { CL_INT  n = 0;
      char* buf = (char*)(tmp);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) src))) != Kernel.ctrue) && 
            ((CL_INT)len > 0)))
        { GC_LOOP;
          { CL_INT  toread = (((CL_INT)len <= 4096) ?
              len :
              4096 );
            CL_INT  m = Core.read_port->fcall(((CL_INT) src),((CL_INT) buf),((CL_INT) toread));
            n= ((CL_INT)n+(CL_INT)m);
            len= ((CL_INT)len-(CL_INT)m);
            Core.write_port->fcall(((CL_INT) trgt),((CL_INT) buf),((CL_INT) m));
            }
          GC_UNLOOP;POP_SIGNAL;}
        }
      Result = n;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> skip n bytes from self (dummy read) without performing
// any allocation and return the amount of bytes actualy skiped
// (may be lower than len if an eof condition is reached)
// The c++ function for: fskip(self:port,len:integer) [NEW_ALLOC]
int  fskip_port1(PortObject *self,int len)
{ GC_BIND;
  char tmp[256];
  { CL_INT Result = 0;
    { CL_INT  n = 0;
      char* buf = (char*)(tmp);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) self))) != Kernel.ctrue) && 
            ((CL_INT)len > 0)))
        { GC_LOOP;
          { CL_INT  nread = (((CL_INT)len <= 256) ?
              len :
              256 );
            CL_INT  m = Core.read_port->fcall(((CL_INT) self),((CL_INT) buf),((CL_INT) nread));
            n= ((CL_INT)n+(CL_INT)m);
            len= ((CL_INT)len-(CL_INT)m);
            }
          GC_UNLOOP;POP_SIGNAL;}
        }
      Result = n;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> close the specified device including the associated
// filter chain
// The c++ function for: fclose(self:device) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  fclose_device1(device *self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  if (self->closed_ask != CTRUE)
   { { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while ((self->filters->length != 0))
      { GC_LOOP;
        { filter * f = GC_OBJECT(filter,OBJECT(filter,last_list(self->filters)));
          fclose_filter1(f);
          if ((self->filters->length != 0) && 
              (last_list(self->filters) == _oid_(f)))
           { if (should_trace_ask_module1(Core.it,0) == CTRUE)
             mtformat_module1(Core.it,"failed to close filter ~S \n",0,list::alloc(1,_oid_(f)));
            else ;}
          }
        GC_UNLOOP;POP_SIGNAL;}
      }
    _void_(Core.flush_port->fcall(((CL_INT) self)));
    (self->closed_ask = CTRUE);
    _void_(Core.close_port->fcall(((CL_INT) self)));
    }
  if (_oid_(self) == Core.Clib_stdout->value)
   (ClEnv->cout = null_I_void1());
  if (ClEnv->cout == self)
   (ClEnv->cout = OBJECT(PortObject,Core.Clib_stdout->value));
  if (ClEnv->ctrace == self)
   (ClEnv->ctrace = OBJECT(PortObject,Core.Clib_stdout->value));
  GC_UNBIND; POP_SIGNAL;}


//<sb> close the top filter only
// The c++ function for: fclose(self:filter) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  fclose_filter1(filter *self)
{ GC_BIND;
  { device * d = GC_OBJECT(device,self->dev);
    if (d == (NULL))
     ;else { if (self->closed_ask != CTRUE)
         { if (_oid_(self) == last_list(d->filters))
           { _void_(Core.flush_port->fcall(((CL_INT) self)));
            (self->closed_ask = CTRUE);
            _void_(Core.close_port->fcall(((CL_INT) self)));
            rmlast_list(d->filters);
            (self->dev = NULL);
            if (self->close_target_ask == CTRUE)
             (*Core.fclose)(GC_OID(_oid_(self->target)));
            }
          }
        if (ClEnv->cout == self)
         (ClEnv->cout = OBJECT(PortObject,Core.Clib_stdout->value));
        if (ClEnv->ctrace == self)
         (ClEnv->ctrace = OBJECT(PortObject,Core.Clib_stdout->value));
        }
      }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: get_filter(self:port,c:class) [0]
PortObject * get_filter_port1(PortObject *self,ClaireClass *c)
{ { PortObject *Result ;
    { device * d = get_device_port1(self);
      list * fs = d->filters;
      CL_INT  len = fs->length;
      PortObject * p = self;
      { CL_INT  i = 1;
        CL_INT  g0155 = len;
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)i <= (CL_INT)g0155))
          { if (_Z_any1((*(fs))[i],c) == CTRUE)
             { p= OBJECT(PortObject,(*(fs))[i]);
              { ;ClEnv->cHandle = loop_handle; break;}
              }
            ++i;
            POP_SIGNAL;}
          }
        }
      Result = p;
      }
    POP_SIGNAL; return (Result);}
  }


//<sb> GC callback raised when the object is freed
// The c++ function for: prefree!(self:filter) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  prefree_I_filter1(filter *self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  if (self->closed_ask != CTRUE)
   { device * d = GC_OBJECT(device,self->dev);
    if (d == (NULL))
     ;else { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((d->filters->length != 0))
        { GC_LOOP;
          { filter * f = GC_OBJECT(filter,OBJECT(filter,last_list(d->filters)));
            if (ClEnv->cout == f)
             (ClEnv->cout = OBJECT(PortObject,Core.Clib_stdout->value));
            if (ClEnv->ctrace == f)
             (ClEnv->ctrace = OBJECT(PortObject,Core.Clib_stdout->value));
            _void_(Core.flush_port->fcall(((CL_INT) f)));
            (f->closed_ask = CTRUE);
            _void_(Core.close_port->fcall(((CL_INT) f)));
            rmlast_list(d->filters);
            (f->dev = NULL);
            }
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: free!(self:device) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  free_I_port2_Core(device *self)
{ if (self->closed_ask != CTRUE)
   { if (ClEnv->cout == self)
     (ClEnv->cout = OBJECT(PortObject,Core.Clib_stdout->value));
    if (ClEnv->ctrace == self)
     (ClEnv->ctrace = OBJECT(PortObject,Core.Clib_stdout->value));
    _void_(Core.flush_port->fcall(((CL_INT) self)));
    (self->closed_ask = CTRUE);
    _void_(Core.close_port->fcall(((CL_INT) self)));
    }
  POP_SIGNAL;}


// ***************************************************************************
// * part 4: null port                                                       *
// ***************************************************************************
// The c++ function for: null!(_CL_obj:void) [0]
null_port * null_I_void1()
{ POP_SIGNAL; return (OBJECT(null_port,Core.null->value));}


//<sb> null port does nothing
// The c++ function for: read_port(self:null_port,buf:char*,len:integer) [0]
int  read_port_null_port1_Core(null_port *self,char*buf,int len)
{ POP_SIGNAL; return (0);}


// The c++ function for: eof_port?(self:null_port) [0]
ClaireBoolean * eof_port_ask_null_port1_Core(null_port *self)
{ POP_SIGNAL; return (CTRUE);}


// The c++ function for: write_port(self:null_port,buf:char*,len:integer) [SAFE_RESULT]
int  write_port_null_port1_Core(null_port *self,char*buf,int len)
{ POP_SIGNAL; return (len);}


// The c++ function for: flush_port(self:null_port) [0]
void  flush_port_null_port1_Core(null_port *self)
{ ;POP_SIGNAL;}


//<sb> keep the singleton opened
// The c++ function for: close_port(self:null_port) [SLOT_UPDATE+RETURN_ARG]
void  close_port_null_port1_Core(null_port *self)
{ (self->closed_ask = CFALSE);
  POP_SIGNAL;}


// ***************************************************************************
// * part 4: blob                                                            *
// ***************************************************************************
//<sb> blob is a port interface for strings, datas are stored in a chunk of
// memory allocated outside claire memory. When a new blob is instantiated
// it is important to allocate the container chunk first (the container is
// the claire blob object) and only then the data chunk, as such we always
// have a valid container to hold the mallocated data.
//<sb> index in data of the next byte to write
//<sb> blobs have a pretty self printing that shows the content
// of the blob around the reading index
// The c++ function for: princ(self:blob) [NEW_ALLOC]
void  princ_blob1(blob *self)
{ if (self->write_index == 0)
   { print_any(_oid_(OWNER(_oid_(self))));
    princ_string("(0)");
    }
  else if ((CL_INT)self->write_index < 40)
   { CL_INT  g0156 = (int )(current_color);
    CL_INT  g0157 = (int )(current_bold);
    CL_INT  g0158 = g0156;
    CL_INT  g0159 = g0157;
    color(g0158,g0159);
    print_any(_oid_(OWNER(_oid_(self))));
    color(g0156,g0157);
    color(g0156,g0157);
    color_princ_string1("(");
    g0156= (int )(current_color);
    g0157= (int )(current_bold);
    color(g0158,g0159);
    print_any(((OID)self->write_index));
    color(g0156,g0157);
    color(g0156,g0157);
    color_princ_string1(":`BLACK");
    g0156= (int )(current_color);
    g0157= (int )(current_bold);
    color(g0158,g0159);
    if ((CL_INT)self->read_index > 0)
     internal_print_string(self->data, self->read_index);
    color(g0156,g0157);
    color(g0156,g0157);
    color_princ_string1("``RED|`BLACK");
    g0156= (int )(current_color);
    g0157= (int )(current_bold);
    color(g0158,g0159);
    if ((CL_INT)self->read_index < (CL_INT)self->write_index)
     internal_print_string(self->data + self->read_index, self->write_index - self->read_index);
    color(g0156,g0157);
    color(g0156,g0157);
    color_princ_string1("`BLACK)");
    color(g0158,g0159);
    }
  else if ((CL_INT)self->read_index < 20)
   { CL_INT  g0160 = (int )(current_color);
    CL_INT  g0161 = (int )(current_bold);
    CL_INT  g0162 = g0160;
    CL_INT  g0163 = g0161;
    color(g0162,g0163);
    print_any(_oid_(OWNER(_oid_(self))));
    color(g0160,g0161);
    color(g0160,g0161);
    color_princ_string1("(");
    g0160= (int )(current_color);
    g0161= (int )(current_bold);
    color(g0162,g0163);
    print_any(((OID)self->write_index));
    color(g0160,g0161);
    color(g0160,g0161);
    color_princ_string1(":`BLACK");
    g0160= (int )(current_color);
    g0161= (int )(current_bold);
    color(g0162,g0163);
    if ((CL_INT)self->read_index > 0)
     internal_print_string(self->data, self->read_index);
    color(g0160,g0161);
    color(g0160,g0161);
    color_princ_string1("``RED|`BLACK");
    g0160= (int )(current_color);
    g0161= (int )(current_bold);
    color(g0162,g0163);
    internal_print_string(self->data + self->read_index, 20);
    color(g0160,g0161);
    color(g0160,g0161);
    color_princ_string1("`RED...`BLACK)");
    color(g0162,g0163);
    }
  else if ((CL_INT)self->write_index <= (CL_INT)((CL_INT)self->read_index+(CL_INT)20))
   { CL_INT  g0164 = (int )(current_color);
    CL_INT  g0165 = (int )(current_bold);
    CL_INT  g0166 = g0164;
    CL_INT  g0167 = g0165;
    color(g0166,g0167);
    print_any(_oid_(OWNER(_oid_(self))));
    color(g0164,g0165);
    color(g0164,g0165);
    color_princ_string1("(");
    g0164= (int )(current_color);
    g0165= (int )(current_bold);
    color(g0166,g0167);
    print_any(((OID)self->write_index));
    color(g0164,g0165);
    color(g0164,g0165);
    color_princ_string1(":`RED...`BLACK");
    g0164= (int )(current_color);
    g0165= (int )(current_bold);
    color(g0166,g0167);
    if ((CL_INT)self->read_index > 0)
     internal_print_string(self->data + self->read_index - 20, 20);
    color(g0164,g0165);
    color(g0164,g0165);
    color_princ_string1("``RED|`BLACK");
    g0164= (int )(current_color);
    g0165= (int )(current_bold);
    color(g0166,g0167);
    internal_print_string(self->data + self->read_index, self->write_index - self->read_index);
    color(g0164,g0165);
    color(g0164,g0165);
    color_princ_string1("`BLACK)");
    color(g0166,g0167);
    }
  else { CL_INT  g0168 = (int )(current_color);
      CL_INT  g0169 = (int )(current_bold);
      CL_INT  g0170 = g0168;
      CL_INT  g0171 = g0169;
      color(g0170,g0171);
      print_any(_oid_(OWNER(_oid_(self))));
      color(g0168,g0169);
      color(g0168,g0169);
      color_princ_string1("(");
      g0168= (int )(current_color);
      g0169= (int )(current_bold);
      color(g0170,g0171);
      print_any(((OID)self->write_index));
      color(g0168,g0169);
      color(g0168,g0169);
      color_princ_string1(":`RED...`BLACK");
      g0168= (int )(current_color);
      g0169= (int )(current_bold);
      color(g0170,g0171);
      internal_print_string(self->data + self->read_index - 20, 20);
      color(g0168,g0169);
      color(g0168,g0169);
      color_princ_string1("``RED|`BLACK");
      g0168= (int )(current_color);
      g0169= (int )(current_bold);
      color(g0170,g0171);
      internal_print_string(self->data + self->read_index, 20);
      color(g0168,g0169);
      color(g0168,g0169);
      color_princ_string1("`RED...`BLACK)");
      color(g0170,g0171);
      }
    POP_SIGNAL;}


//<sb> ensure that the internal buffer is large enough to
// hold n bytes at the current write index
// The c++ function for: write_attempt(self:blob,n:integer) [SLOT_UPDATE+RETURN_ARG]
void  write_attempt_blob1(blob *self,int n)
{ if ((CL_INT)remain_for_write_blob1(self) < (CL_INT)n)
   { CL_INT  len_after = ((CL_INT)self->write_index+(CL_INT)n);
    CL_INT  new_length = ((CL_INT)self->alloc_length+(CL_INT)512);
    { CL_INT loop_handle = ClEnv->cHandle;
      while (((CL_INT)new_length < (CL_INT)len_after))
      { new_length= ((CL_INT)new_length+(CL_INT)512);
        POP_SIGNAL;}
      }
    { char* new_data = (char*)(((char*)realloc(self->data, new_length)));
      if ((((ClaireBoolean *) (ClaireBoolean *)((new_data == NULL ? CTRUE : CFALSE)))) == CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("failed to allocate external memory for blob ~S"),
        _oid_(list::alloc(1,_oid_(self))))));
      (self->alloc_length = new_length);
      (self->data = new_data);
      }
    }
  POP_SIGNAL;}


// The c++ function for: unget_port(self:blob,buf:char*,len:integer) [SLOT_UPDATE]
void  unget_port_blob1_Core(blob *self,char*buf,int len)
{ { CL_INT  room = self->read_index;
    if ((CL_INT)len <= (CL_INT)room)
     (self->read_index = ((CL_INT)self->read_index-(CL_INT)len));
    else { CL_INT  grow = ((CL_INT)len-(CL_INT)room);
        CL_INT  remain = remain_to_read_blob1(self);
        write_attempt_blob1(self,grow);
        if ((CL_INT)remain > 0)
         memmove(self->data + self->read_index + grow, self->data + self->read_index, remain);
        (self->write_index = ((CL_INT)self->write_index+(CL_INT)grow));
        (self->read_index = 0);
        }
      memcpy(self->data + self->read_index, buf, len);
    }
  POP_SIGNAL;}


//<sb> allocate an empty blob
// The c++ function for: blob!(_CL_obj:void) [NEW_ALLOC+SLOT_UPDATE]
blob * blob_I_void1()
{ GC_BIND;
  { blob *Result ;
    { blob * b;
      { { blob * _CL_obj = ((blob *) GC_OBJECT(blob,new_object_class(Core._blob)));
          b = _CL_obj;
          }
        GC_OBJECT(blob,b);}
      char* buf = (char*)(((char*)malloc(512)));
      if ((((ClaireBoolean *) (ClaireBoolean *)((buf == NULL ? CTRUE : CFALSE)))) == CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("failed to allocate external memory in blobl! @ void"),
        _oid_(Kernel.nil))));
      (b->data = buf);
      (b->alloc_length = 512);
      Result = b;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> allocate a blob that is a copy of the given blob
// The c++ function for: blob!(p:blob) [NEW_ALLOC+SLOT_UPDATE]
blob * blob_I_blob1(blob *p)
{ GC_BIND;
  { blob *Result ;
    { blob * b;
      { { blob * _CL_obj = ((blob *) GC_OBJECT(blob,new_object_class(Core._blob)));
          b = _CL_obj;
          }
        GC_OBJECT(blob,b);}
      char* buf = (char*)(((char*)malloc(p->alloc_length)));
      if ((((ClaireBoolean *) (ClaireBoolean *)((buf == NULL ? CTRUE : CFALSE)))) == CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("failed to allocate external memory for blob!(~S)"),
        _oid_(list::alloc(1,_oid_(p))))));
      memcpy(buf, p->data, p->write_index);
      (b->data = buf);
      (b->firstc = p->firstc);
      (b->read_index = p->read_index);
      (b->write_index = p->write_index);
      (b->alloc_length = p->alloc_length);
      Result = b;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> allocate a blob that is filled with all datas that can
// be read on p
// The c++ function for: blob!(p:port) [NEW_ALLOC]
blob * blob_I_port1(PortObject *p)
{ GC_BIND;
  { blob *Result ;
    { blob * b = GC_OBJECT(blob,blob_I_void1());
      freadwrite_port3(p,b);
      Result = b;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> allocate a blob with the string self has the initial data
// The c++ function for: blob!(self:string) [NEW_ALLOC+SLOT_UPDATE]
blob * blob_I_string1(char *self)
{ GC_BIND;
  { blob *Result ;
    { blob * b;
      { { blob * _CL_obj = ((blob *) GC_OBJECT(blob,new_object_class(Core._blob)));
          b = _CL_obj;
          }
        GC_OBJECT(blob,b);}
      CL_INT  len = LENGTH_STRING(self);
      write_attempt_blob1(b,len);
      memcpy(b->data, self, len);
      (b->write_index = len);
      Result = b;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> allocate a blob that can receive at least n bytes
// i.e. writing more than n bytes may cause further allocation
// The c++ function for: blob!(n:integer) [NEW_ALLOC+SLOT_UPDATE]
blob * blob_I_integer1(int n)
{ GC_BIND;
  { blob *Result ;
    { blob * b;
      { { blob * _CL_obj = ((blob *) GC_OBJECT(blob,new_object_class(Core._blob)));
          b = _CL_obj;
          }
        GC_OBJECT(blob,b);}
      write_attempt_blob1(b,n);
      Result = b;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> compatibility with <ycs>
//<sb> return the amount of bytes remaining for writing or reading
// The c++ function for: remain_for_write(self:blob) [RETURN_ARG]
int  remain_for_write_blob1(blob *self)
{ POP_SIGNAL; return (((CL_INT)self->alloc_length-(CL_INT)self->write_index));}


// The c++ function for: remain_to_read(self:blob) [RETURN_ARG]
int  remain_to_read_blob1(blob *self)
{ POP_SIGNAL; return (((CL_INT)self->write_index-(CL_INT)self->read_index));}


// The c++ function for: eof_port?(self:blob) [0]
ClaireBoolean * eof_port_ask_blob1_Core(blob *self)
{ POP_SIGNAL; return (((ClaireBoolean *) (ClaireBoolean *)((self->read_index == self->write_index ? CTRUE : CFALSE))));}


// The c++ function for: read_port(self:blob,buf:char*,len:integer) [SLOT_UPDATE]
int  read_port_blob1_Core(blob *self,char*buf,int len)
{ { CL_INT Result = 0;
    { CL_INT  avail = remain_to_read_blob1(self);
      if ((CL_INT)len < (CL_INT)avail)
       avail= len;
      memcpy(buf, self->data + self->read_index, avail);
      (self->read_index = ((CL_INT)self->read_index+(CL_INT)avail));
      Result = avail;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: write_port(self:blob,buf:char*,len:integer) [SLOT_UPDATE+SAFE_RESULT]
int  write_port_blob1_Core(blob *self,char*buf,int len)
{ write_attempt_blob1(self,len);
  memcpy(self->data + self->write_index, buf, len);
  (self->write_index = ((CL_INT)self->write_index+(CL_INT)len));
  POP_SIGNAL; return (len);}


// The c++ function for: close_port(self:blob) [0]
void  close_port_blob1_Core(blob *self)
{ {if (self->data) ::free(self->data);};
  POP_SIGNAL;}


//<sb> string! converts a blob in a string
// The c++ function for: string!(self:blob) [NEW_ALLOC]
char * string_I_blob1(blob *self)
{ GC_BIND;
  { char *Result ;
    { CL_INT  len = self->write_index;
      char * s = GC_STRING(make_string_integer1(len));
      memcpy(s, self->data, len);
      Result = s;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> buffer access on the blob
// The c++ function for: nth(self:blob,n:integer) [0]
ClaireChar * nth_blob1(blob *self,int n)
{ { ClaireChar *Result ;
    { ClaireObject *V_CC ;
      { n= ((1 <= (CL_INT)n) ?
          n :
          1 );
        n= (((CL_INT)n <= (CL_INT)self->alloc_length) ?
          n :
          self->alloc_length );
        if (n == 0)
         V_CC = OBJECT(ClaireChar,Core._eof->value);
        else V_CC = (ClaireChar *)(_char_(self->data[n-1]));
          }
      Result= (ClaireChar *) V_CC;}
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: nth=(self:blob,n:integer,c:char) [0]
void  nth_equal_blob1(blob *self,int n,ClaireChar *c)
{ n= ((1 <= (CL_INT)n) ?
    n :
    1 );
  n= (((CL_INT)n <= (CL_INT)self->alloc_length) ?
    n :
    self->alloc_length );
  if (n == 0)
   close_exception(((general_error *) (*Core._general_error)(_string_("nth=@blob: the blob ~S is empty"),
    _oid_(list::alloc(1,_oid_(self))))));
  self->data[n-1] = c->ascii;
  POP_SIGNAL;}


// The c++ function for: length(self:blob) [RETURN_ARG]
int  length_blob1(blob *self)
{ POP_SIGNAL; return (self->write_index);}


// The c++ function for: set_length(self:blob,n:integer) [SLOT_UPDATE+RETURN_ARG]
void  set_length_blob1(blob *self,int n)
{ if ((CL_INT)n <= 0)
   { char* new_data = (char*)(((char*)realloc(self->data, 512)));
    if ((((ClaireBoolean *) (ClaireBoolean *)((new_data == NULL ? CTRUE : CFALSE)))) == CTRUE)
     close_exception(((general_error *) (*Core._general_error)(_string_("failed to allocate external memory in set_length(~S, ~S)"),
      _oid_(list::alloc(2,_oid_(self),((OID)n))))));
    (self->data = new_data);
    (self->alloc_length = 512);
    (self->read_index = 0);
    (self->write_index = 0);
    }
  else { CL_INT  maxn = self->alloc_length;
      if ((CL_INT)n > (CL_INT)maxn)
       write_attempt_blob1(self,((CL_INT)n-(CL_INT)maxn));
      else { (self->write_index = (((CL_INT)self->write_index <= (CL_INT)n) ?
            self->write_index :
            n ));
          (self->read_index = (((CL_INT)self->read_index <= (CL_INT)n) ?
            self->read_index :
            n ));
          }
        }
    POP_SIGNAL;}


// The c++ function for: substring(self:blob,i:integer,j:integer) [NEW_ALLOC]
char * substring_blob1(blob *self,int i,int j)
{ GC_BIND;
  i= ((1 <= (CL_INT)i) ?
    i :
    1 );
  j= (((CL_INT)i <= (CL_INT)j) ?
    j :
    i );
  i= (((CL_INT)i <= (CL_INT)self->alloc_length) ?
    i :
    self->alloc_length );
  j= (((CL_INT)j <= (CL_INT)self->alloc_length) ?
    j :
    self->alloc_length );
  { char *Result ;
    { CL_INT  len = ((CL_INT)((CL_INT)j-(CL_INT)i)+(CL_INT)1);
      char * s = GC_STRING(make_string_integer1(len));
      memcpy(s, self->data + i - 1, len);
      Result = s;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: get_index(self:blob) [RETURN_ARG]
int  get_index_blob1(blob *self)
{ POP_SIGNAL; return (self->read_index);}


// The c++ function for: set_index(self:blob,n:integer) [SLOT_UPDATE+RETURN_ARG]
void  set_index_blob1(blob *self,int n)
{ { CL_INT  i = (((CL_INT)self->write_index <= (CL_INT)n) ?
      self->write_index :
      n );
    (self->read_index = (((CL_INT)i <= 0) ?
      0 :
      i ));
    }
  POP_SIGNAL;}


// ***************************************************************************
// * part 5: reverser                                                        *
// ***************************************************************************
// The c++ function for: reverser!(self:blob) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
Core_reverser * reverser_I_blob1(blob *self)
{ GC_BIND;
  { Core_reverser *Result ;
    { filter *V_CC ;
      { if (get_top_most_port1(self) != self)
         close_exception(((general_error *) (*Core._general_error)(_string_("Cannot create a reverser on ~S that is already filtered"),
          _oid_(list::alloc(1,_oid_(self))))));
        { Core_reverser * g0178UU;
          { Core_reverser * _CL_obj = ((Core_reverser *) GC_OBJECT(Core_reverser,new_object_class(Core._reverser)));
            (_CL_obj->left_to_read = self->write_index);
            g0178UU = _CL_obj;
            }
          V_CC = filter_I_filter1(g0178UU,self);
          }
        }
      Result= (Core_reverser *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: eof_port?(self:reverser) [0]
ClaireBoolean * eof_port_ask_reverser1_Core(Core_reverser *self)
{ POP_SIGNAL; return (equal(((OID)self->left_to_read),((OID)0)));}


// The c++ function for: read_port(self:reverser,buf:char*,len:integer) [SLOT_UPDATE]
int  read_port_reverser1_Core(Core_reverser *self,char*buf,int len)
{ { CL_INT Result = 0;
    { blob * bl = ((blob *) self->target);
      char* d = bl->data;
      CL_INT  n = 0;
      CL_INT  left_after = ((CL_INT)self->left_to_read-(CL_INT)len);
      if ((CL_INT)self->left_to_read > (CL_INT)bl->write_index)
       close_exception(((general_error *) (*Core._general_error)(_string_("dangerous read_port @ reverser since the blob has changed !"),
        _oid_(Kernel.nil))));
      left_after= ((0 <= (CL_INT)left_after) ?
        left_after :
        0 );
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((CL_INT)self->left_to_read > (CL_INT)left_after))
        { *buf = d[self->left_to_read - 1];
						buf++;
          ++n;
          (self->left_to_read = ((CL_INT)self->left_to_read-(CL_INT)1));
          POP_SIGNAL;}
        }
      Result = n;
      }
    POP_SIGNAL; return (Result);}
  }


// ***************************************************************************
// * part 5: buffer                                                          *
// ***************************************************************************
//<sb> a buffer filter performs a single read/write call on its tagret
// for each data raw of a given size. 
// The c++ function for: buffer!(self:port,bufsize:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
buffer * buffer_I_port1(PortObject *self,int bufsize)
{ GC_BIND;
  { buffer *Result ;
    { filter *V_CC ;
      { buffer * g0180UU;
        { buffer * _CL_obj = ((buffer *) GC_OBJECT(buffer,new_object_class(Core._buffer)));
          (_CL_obj->buffer_length = bufsize);
          g0180UU = _CL_obj;
          }
        V_CC = filter_I_filter1(g0180UU,self);
        }
      Result= (buffer *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: buffer!(self:buffer,p:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
buffer * buffer_I_buffer1(buffer *self,PortObject *p)
{ GC_BIND;
  { buffer *Result ;
    { buffer * f;
      { { filter *V_CC ;
          { buffer * g0181UU;
            { buffer * _CL_obj = ((buffer *) GC_OBJECT(buffer,new_object_class(Core._buffer)));
              (_CL_obj->buffer_length = self->buffer_length);
              (_CL_obj->close_target_ask = self->close_target_ask);
              (_CL_obj->firstc = self->firstc);
              g0181UU = _CL_obj;
              }
            V_CC = filter_I_filter1(g0181UU,p);
            }
          f= (buffer *) V_CC;}
        GC_OBJECT(buffer,f);}
      if (((self->pending_r == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       (f->pending_r = blob_I_blob1(GC_OBJECT(blob,self->pending_r)));
      if (((self->pending_w == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       (f->pending_w = blob_I_blob1(GC_OBJECT(blob,self->pending_w)));
      Result = f;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: princ(self:buffer) [NEW_ALLOC]
void  princ_buffer1(buffer *self)
{ GC_BIND;
  princ_string("buffer[");
  if (((self->pending_r == (NULL)) ? CTRUE : CFALSE) != CTRUE)
   { princ_string("R<");
    princ_blob1(self->pending_r);
    princ_string(">");
    }
  if ((((self->pending_r == (NULL)) ? CTRUE : CFALSE) != CTRUE) && 
      (((self->pending_w == (NULL)) ? CTRUE : CFALSE) != CTRUE))
   princ_string(" ");
  if (((self->pending_w == (NULL)) ? CTRUE : CFALSE) != CTRUE)
   { princ_string("W<");
    princ_blob1(self->pending_w);
    princ_string(">");
    }
  princ_string("]");
  GC_UNBIND; POP_SIGNAL;}


//<sb> read
// The c++ function for: reset_buffer(self:port) [SLOT_UPDATE+RETURN_ARG]
void  reset_buffer_port1(PortObject *self)
{ { PortObject * p = get_filter_port1(self,Core._buffer);
    if (INHERIT(p->isa,Core._buffer))
     { if (((CLREAD(buffer,p,pending_r) == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       { (CLREAD(buffer,p,pending_r)->write_index = 0);
        (CLREAD(buffer,p,pending_r)->read_index = 0);
        }
      }
    else close_exception(((general_error *) (*Core._general_error)(_string_("~S is not connected to a buffer"),
        _oid_(list::alloc(1,_oid_(self))))));
      }
  POP_SIGNAL;}


//<sb> the buffer reads its target by chunks of buffer_length bytes
// Note wcl: in order to have a toplevel compatible with wcl
// we have to connect the input to a buffer (wcl reader uses unget),
// the length of such a buffer is 1 such it always reads on the terminal
// input a single char at a time
// The c++ function for: fill_read_buffer(self:buffer) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  fill_read_buffer_buffer1(buffer *self)
{ GC_BIND;
  if (self->pending_r == (NULL))
   (self->pending_r = blob_I_integer1(self->buffer_length));
  { blob * pend = GC_OBJECT(blob,self->pending_r);
    (pend->read_index = 0);
    (pend->write_index = Core.read_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))),((CL_INT) (char*)(pend->data)),((CL_INT) self->buffer_length)));
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: eof_port?(self:buffer) [NEW_ALLOC]
ClaireBoolean * eof_port_ask_buffer1_Core(buffer *self)
{ GC_BIND;
  { ClaireBoolean *Result ;
    Result = ((((self->pending_r == (NULL)) ? CTRUE : CFALSE) != CTRUE) ? ((remain_to_read_blob1(self->pending_r) == 0) ? (((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))))))) == CTRUE) ? CTRUE: CFALSE): CFALSE): CFALSE);
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: read_port(self:buffer,buf:char*,len:integer) [NEW_ALLOC+SLOT_UPDATE]
int  read_port_buffer1_Core(buffer *self,char*buf,int len)
{ if (self->pending_r == (NULL))
   (self->pending_r = blob_I_integer1(self->buffer_length));
  { CL_INT Result = 0;
    { blob * pend = ((blob *) (blob *)(self->pending_r));
      CL_INT  disp = ((CL_INT)pend->write_index-(CL_INT)pend->read_index);
      CL_INT  n = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((CL_INT)len > 0))
        { { CL_INT  m = (((CL_INT)disp <= (CL_INT)len) ?
              disp :
              len );
            if ((CL_INT)m > 0)
             { memcpy(buf, pend->data + pend->read_index, m);
              len= ((CL_INT)len-(CL_INT)m);
              n= ((CL_INT)n+(CL_INT)m);
              (pend->read_index = ((CL_INT)pend->read_index+(CL_INT)m));
              buf= (buf + m);
              }
            disp= ((CL_INT)pend->write_index-(CL_INT)pend->read_index);
            if (disp == 0)
             { if ((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) (PortObject *)(self->target)))))) == CTRUE)
               { ;ClEnv->cHandle = loop_handle; break;}
              fill_read_buffer_buffer1(self);
              disp= remain_to_read_blob1(pend);
              }
            }
          POP_SIGNAL;}
        }
      Result = n;
      }
    POP_SIGNAL; return (Result);}
  }


//<sb> this is our unget interface for stream. the given data
// is copied back in the buffer and the read index is moved
// such the next data to read is s
// Note: the message is not transmited to the target, a buffer
// always accumlate ungotten datas and there is no more message
// after that.
// The c++ function for: unget_port(self:buffer,buf:char*,len:integer) [NEW_ALLOC+SLOT_UPDATE]
void  unget_port_buffer1_Core(buffer *self,char*buf,int len)
{ GC_BIND;
  if (self->pending_r == (NULL))
   { (self->pending_r = blob_I_integer1(self->buffer_length));
    Core.write_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->pending_r)))),((CL_INT) buf),((CL_INT) len));
    }
  else _void_(Core.unget_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->pending_r)))),((CL_INT) buf),((CL_INT) len)));
    GC_UNBIND; POP_SIGNAL;}


//<sb> write
// The c++ function for: flush_port(self:buffer) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  flush_port_buffer1_Core(buffer *self)
{ GC_BIND;
  if (((self->pending_w == (NULL)) ? CTRUE : CFALSE) != CTRUE)
   { blob * pend = GC_OBJECT(blob,self->pending_w);
    if ((CL_INT)pend->write_index > 0)
     Core.write_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))),((CL_INT) (char*)(pend->data)),((CL_INT) pend->write_index));
    (pend->write_index = 0);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: write_port(self:buffer,buf:char*,len:integer) [NEW_ALLOC+SLOT_UPDATE]
int  write_port_buffer1_Core(buffer *self,char*buf,int len)
{ GC_BIND;
  if (self->pending_w == (NULL))
   (self->pending_w = blob_I_integer1(self->buffer_length));
  { CL_INT Result = 0;
    { blob * pend = ((blob *) (blob *)(self->pending_w));
      CL_INT  blen = self->buffer_length;
      CL_INT  disp = ((CL_INT)blen-(CL_INT)pend->write_index);
      CL_INT  n = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)len > 0))
        { GC_LOOP;
          { CL_INT  m = (((CL_INT)disp <= (CL_INT)len) ?
              disp :
              len );
            if ((CL_INT)m > 0)
             { memcpy(pend->data + pend->write_index, buf, m);
              len= ((CL_INT)len-(CL_INT)m);
              n= ((CL_INT)n+(CL_INT)m);
              (pend->write_index = ((CL_INT)pend->write_index+(CL_INT)m));
              buf= (buf + m);
              }
            disp= ((CL_INT)blen-(CL_INT)pend->write_index);
            if (disp == 0)
             { Core.write_port->fcall(((CL_INT) (PortObject *)(self->target)),((CL_INT) (char*)(pend->data)),((CL_INT) blen));
              (pend->write_index = 0);
              disp= blen;
              }
            }
          GC_UNLOOP;POP_SIGNAL;}
        }
      Result = n;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: close_port(self:buffer) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  close_port_buffer1_Core(buffer *self)
{ GC_BIND;
  if (((self->pending_r == (NULL)) ? CTRUE : CFALSE) != CTRUE)
   fclose_device1(GC_OBJECT(blob,self->pending_r));
  if (((self->pending_w == (NULL)) ? CTRUE : CFALSE) != CTRUE)
   fclose_device1(GC_OBJECT(blob,self->pending_w));
  GC_UNBIND; POP_SIGNAL;}


// ***************************************************************************
// * part 6: line_buffer                                                     *
// ***************************************************************************
//<sb> line_buffer is a write filter that collects written datas
// until a new line character. each line is flushed with a single
// write on the target port. It is mainly used for terminal output
// such to prevent line overlap when multiple process share the same
// terminal output or when a trace file is shared by multiple process.
//<sb> a pending line
// The c++ function for: line_buffer!(self:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
line_buffer * line_buffer_I_port1(PortObject *self)
{ GC_BIND;
  { line_buffer *Result ;
    { line_buffer * lb;
      { { filter *V_CC ;
          { line_buffer * g0184UU;
            { line_buffer * _CL_obj = ((line_buffer *) GC_OBJECT(line_buffer,new_object_class(Core._line_buffer)));
              g0184UU = _CL_obj;
              }
            V_CC = filter_I_filter1(g0184UU,self);
            }
          lb= (line_buffer *) V_CC;}
        GC_OBJECT(line_buffer,lb);}
      (lb->pending = blob_I_void1());
      Result = lb;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: flush_port(self:line_buffer) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  flush_port_line_buffer1_Core(line_buffer *self)
{ GC_BIND;
  { blob * pend = GC_OBJECT(blob,self->pending);
    CL_INT  len = remain_to_read_blob1(pend);
    if ((CL_INT)len > 0)
     { Core.write_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))),((CL_INT) (char*)(pend->data)),((CL_INT) len));
      (pend->read_index = 0);
      (pend->write_index = 0);
      }
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: close_port(self:line_buffer) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  close_port_line_buffer1_Core(line_buffer *self)
{ GC_BIND;
  fclose_device1(GC_OBJECT(blob,self->pending));
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: write_port(self:line_buffer,buf:char*,len:integer) [NEW_ALLOC+SAFE_RESULT]
int  write_port_line_buffer1_Core(line_buffer *self,char*buf,int len)
{ GC_BIND;
  { CL_INT Result = 0;
    { blob * pend = self->pending;
      ClaireBoolean * nl = CFALSE;
      CL_INT  n = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)n < (CL_INT)len))
        { GC_LOOP;
          { CL_INT  n0 = n;
            while (1) {if (buf[n] == '\n') nl = CTRUE;
									if (n + 1 == len) break;
									n++;};
            Core.write_port->fcall(((CL_INT) pend),((CL_INT) (buf + n0)),((CL_INT) ((CL_INT)((CL_INT)n-(CL_INT)n0)+(CL_INT)1)));
            if (nl == CTRUE)
             { _void_(Core.flush_port->fcall(((CL_INT) self)));
              nl= CFALSE;
              }
            ++n;
            }
          GC_UNLOOP;POP_SIGNAL;}
        }
      Result = len;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// ***************************************************************************
// * part 7: byte_counter                                                    *
// ***************************************************************************
//<sb> byte_counter is a pure filter that count the number of bytes
// transfered in both directions
// The c++ function for: byte_counter!(self:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
byte_counter * byte_counter_I_port1(PortObject *self)
{ GC_BIND;
  { byte_counter *Result ;
    { filter *V_CC ;
      { byte_counter * g0185UU;
        { byte_counter * _CL_obj = ((byte_counter *) GC_OBJECT(byte_counter,new_object_class(Core._byte_counter)));
          g0185UU = _CL_obj;
          }
        V_CC = filter_I_filter1(g0185UU,self);
        }
      Result= (byte_counter *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: byte_counter!(self:byte_counter,p:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
byte_counter * byte_counter_I_byte_counter1(byte_counter *self,PortObject *p)
{ GC_BIND;
  { byte_counter *Result ;
    { filter *V_CC ;
      { byte_counter * g0186UU;
        { byte_counter * _CL_obj = ((byte_counter *) GC_OBJECT(byte_counter,new_object_class(Core._byte_counter)));
          (_CL_obj->close_target_ask = self->close_target_ask);
          (_CL_obj->firstc = self->firstc);
          (_CL_obj->written_bytes = self->written_bytes);
          (_CL_obj->read_bytes = self->read_bytes);
          g0186UU = _CL_obj;
          }
        V_CC = filter_I_filter1(g0186UU,p);
        }
      Result= (byte_counter *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: write_port(self:byte_counter,buf:char*,len:integer) [NEW_ALLOC+SLOT_UPDATE]
int  write_port_byte_counter1_Core(byte_counter *self,char*buf,int len)
{ GC_BIND;
  { CL_INT Result = 0;
    { CL_INT  n = Core.write_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))),((CL_INT) buf),((CL_INT) len));
      (self->written_bytes = ((CL_INT)self->written_bytes+(CL_INT)n));
      Result = n;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: read_port(self:byte_counter,buf:char*,len:integer) [NEW_ALLOC+SLOT_UPDATE]
int  read_port_byte_counter1_Core(byte_counter *self,char*buf,int len)
{ GC_BIND;
  { CL_INT Result = 0;
    { CL_INT  n = Core.read_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))),((CL_INT) buf),((CL_INT) len));
      (self->read_bytes = ((CL_INT)self->read_bytes+(CL_INT)n));
      Result = n;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// ***************************************************************************
// * part 8: line_counter                                                    *
// ***************************************************************************
//<sb> line_counter is a pure filter that count the number of lines
// transfered in both directions
// The c++ function for: line_counter!(self:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
line_counter * line_counter_I_port1(PortObject *self)
{ GC_BIND;
  { line_counter *Result ;
    { filter *V_CC ;
      { line_counter * g0189UU;
        { line_counter * _CL_obj = ((line_counter *) GC_OBJECT(line_counter,new_object_class(Core._line_counter)));
          g0189UU = _CL_obj;
          }
        V_CC = filter_I_filter1(g0189UU,self);
        }
      Result= (line_counter *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: line_counter!(self:line_counter,p:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
line_counter * line_counter_I_line_counter1(line_counter *self,PortObject *p)
{ GC_BIND;
  { line_counter *Result ;
    { filter *V_CC ;
      { line_counter * g0190UU;
        { line_counter * _CL_obj = ((line_counter *) GC_OBJECT(line_counter,new_object_class(Core._line_counter)));
          (_CL_obj->close_target_ask = self->close_target_ask);
          (_CL_obj->firstc = self->firstc);
          (_CL_obj->written_lines = self->written_lines);
          (_CL_obj->read_lines = self->read_lines);
          g0190UU = _CL_obj;
          }
        V_CC = filter_I_filter1(g0190UU,p);
        }
      Result= (line_counter *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: write_port(self:line_counter,buf:char*,len:integer) [NEW_ALLOC+SLOT_UPDATE]
int  write_port_line_counter1_Core(line_counter *self,char*buf,int len)
{ GC_BIND;
  { CL_INT Result = 0;
    { CL_INT  n = Core.write_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))),((CL_INT) buf),((CL_INT) len));
      CL_INT  slashn = 0;
      CL_INT  i = 0;
      while (i < n) {if (buf[i++] == '\n') slashn++;};
      (self->written_lines = ((CL_INT)self->written_lines+(CL_INT)slashn));
      Result = n;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: read_port(self:line_counter,buf:char*,len:integer) [NEW_ALLOC+SLOT_UPDATE]
int  read_port_line_counter1_Core(line_counter *self,char*buf,int len)
{ GC_BIND;
  { CL_INT Result = 0;
    { CL_INT  n = Core.read_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))),((CL_INT) buf),((CL_INT) len));
      CL_INT  slashn = 0;
      CL_INT  i = 0;
      while (i < n) {if (buf[i++] == '\n') slashn++;};
      if (slashn == 0)
       (self->line_offset = ((CL_INT)self->line_offset+(CL_INT)len));
      else { CL_INT  o = 0;
          (self->prev_line_offset = self->line_offset);
          while (len) {if (buf[len] == '\n') break; len--; o++;};
          (self->line_offset = o);
          }
        (self->read_lines = ((CL_INT)self->read_lines+(CL_INT)slashn));
      Result = n;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: unget_port(self:line_counter,buf:char*,len:integer) [NEW_ALLOC+SLOT_UPDATE]
void  unget_port_line_counter1_Core(line_counter *self,char*buf,int len)
{ GC_BIND;
  { CL_INT  i = 0;
    CL_INT  slashn = 0;
    while (i < len) {if (buf[i++] == '\n') slashn++;};
    if (slashn == 0)
     (self->line_offset = ((CL_INT)self->line_offset-(CL_INT)len));
    else (self->line_offset = self->prev_line_offset);
      (self->read_lines = ((CL_INT)self->read_lines-(CL_INT)slashn));
    _void_(Core.unget_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->target)))),((CL_INT) buf),((CL_INT) len)));
    }
  GC_UNBIND; POP_SIGNAL;}


// ***************************************************************************
// * part 9: descriptor                                                      *
// ***************************************************************************
//<sb> unix file descriptor wrapping. we do not use C stream capabilities
// (FILE*) but the descriptor itself, which make the API relying on system
// calls read(2) and write(2), stream interface is provided by filters (buffer)
//<sb> wan't write error on closed descriptors
// The c++ function for: princ(self:descriptor) [NEW_ALLOC]
void  princ_descriptor1(descriptor *self)
{ print_any(_oid_(OWNER(_oid_(self))));
  princ_string("/");
  print_any(((OID)self->fd));
  POP_SIGNAL;}


// The c++ function for: close_port(self:descriptor) [0]
void  close_port_descriptor1_Core(descriptor *self)
{ if (_oid_(self) == Core.Clib_stdout->value)
   if (LOGO) ::write(1, "bye...\n", 7);
  if (self->fd != -1) ::close(self->fd);
  POP_SIGNAL;}


// The c++ function for: eof_port?(self:descriptor) [RETURN_ARG]
ClaireBoolean * eof_port_ask_descriptor1_Core(descriptor *self)
{ POP_SIGNAL; return (self->eof_reached_ask);}


// The c++ function for: read_port(self:descriptor,buf:char*,len:integer) [SLOT_UPDATE]
int  read_port_descriptor1_Core(descriptor *self,char*buf,int len)
{ { CL_INT Result = 0;
    { CL_INT  r = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((CL_INT)r < (CL_INT)len))
        { { CL_INT  n = (int )(::read(self->fd, buf + r, len - r));
            if (n == 0)
             { (self->eof_reached_ask = CTRUE);
              { ;ClEnv->cHandle = loop_handle; break;}
              }
            else if ((n == ((CL_INT)-1)) && 
                ((((ClaireBoolean *) (ClaireBoolean *)((errno != EINTR ? CTRUE : CFALSE)))) == CTRUE))
             Cerrorno(97, _string_("read"), _oid_(self));
            else r= ((CL_INT)r+(CL_INT)n);
              }
          POP_SIGNAL;}
        }
      Result = r;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: write_port(self:descriptor,buf:char*,len:integer) [0]
int  write_port_descriptor1_Core(descriptor *self,char*buf,int len)
{ { CL_INT Result = 0;
    { CL_INT  r = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((CL_INT)r < (CL_INT)len))
        { { CL_INT  n = (int )(::write(self->fd, buf + r, len - r));
            if ((n == ((CL_INT)-1)) && 
                ((((ClaireBoolean *) (ClaireBoolean *)((errno != EINTR ? CTRUE : CFALSE)))) == CTRUE))
             Cerrorno(97, _string_("write"), _oid_(self));
            else r= ((CL_INT)r+(CL_INT)n);
              }
          POP_SIGNAL;}
        }
      Result = r;
      }
    POP_SIGNAL; return (Result);}
  }


//<sb> check wheither a descriptor is connected to a terminal device
// The c++ function for: terminal?(p:port) [0]
ClaireBoolean * terminal_ask_port1(PortObject *p)
{ p= get_device_port1(p);
  { ClaireBoolean *Result ;
    if (INHERIT(p->isa,Core._descriptor))
     { descriptor * self = ((descriptor *) p);
      
					struct stat sb;
					if(fstat(self->fd, &sb) != -1)
						return ((sb.st_mode) & S_IFMT) != S_IFCHR ? CFALSE : CTRUE;
				;
      Result = CFALSE;
      }
    else Result = CFALSE;
      POP_SIGNAL; return (Result);}
  }


//<sb> duplicate a descriptor to be used in place of another
// Note : the new descriptor will be set to the lowest available
// descriptor (small int) for the current process.
// The c++ function for: duplicate(anfd:descriptor) [NEW_ALLOC]
descriptor * duplicate_descriptor1(descriptor *anfd)
{ GC_BIND;
  { descriptor *Result ;
    { CL_INT  desc = 0;
      if (anfd->closed_ask == CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("Attemp to duplicate descriptor ~S that is already closed."),
        _oid_(list::alloc(1,_oid_(anfd))))));
      desc = dup(anfd->fd);
      if (desc == ((CL_INT)-1))
       Cerrorno(97, _string_("duplicate"), _oid_(anfd));
      { descriptor * _CL_obj = ((descriptor *) GC_OBJECT(descriptor,new_object_class(Core._descriptor)));
        (_CL_obj->fd = desc);
        Result = close_descriptor1(_CL_obj);
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> here we initialize Clib standard ports by hand assuming that
// the underlying lib defines 0,1,2 respectively standard in,out,err
// program descriptor and already opened.
//<sb> new! avoid a call to close
//<sb> here we catch wheither a standard port is redirected and update
// our knownlegde about Clib standard ports accordingly.
// e.g. closing stdout and dup(2)
// The c++ function for: close(self:descriptor) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
descriptor * close_descriptor1(descriptor *self)
{ if (self->fd == 0)
   write_property(Kernel.value,OBJECT(ClaireObject,value_module(Core.it,"Clib_stdin")),_oid_(self));
  else if (self->fd == 1)
   write_property(Kernel.value,OBJECT(ClaireObject,value_module(Core.it,"Clib_stdout")),_oid_(self));
  else if (self->fd == 2)
   write_property(Kernel.value,OBJECT(ClaireObject,value_module(Core.it,"Clib_stderr")),_oid_(self));
  POP_SIGNAL; return (self);}


//<sb> here we initialize standard ports and system ports.
// note 1: if something is wrong until there during the meta load
// the behavior is undefined, even error printing cannot be acheived safely
// note 2 : for standard out (intended for write) we check wheither
// the actual device is a terminal in which case a line buffer filter is added
// note 3 : stderr is always unbuffered
//<sb> add color support
// release() should produce a version number
// The c++ function for: select?(_CL_obj:void) [0]
ClaireBoolean * select_ask_void1()
{ { ClaireBoolean *Result ;
    { ClaireObject *V_CC ;
      { 
		int rs = fdMaxfd == -1 ? 0 : select(fdMaxfd+1,&readset,&writeset,0,0);
		fdMaxfd = -1;
        V_CC = (ClaireBoolean *)((rs<=0 ? CFALSE : CTRUE));
        }
      Result= (ClaireBoolean *) V_CC;}
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: select?(ms:integer) [0]
ClaireBoolean * select_ask_integer1(int ms)
{ { ClaireBoolean *Result ;
    { ClaireObject *V_CC ;
      { 
		timeval timeout;
		timeout.tv_sec = ms / 1000;
		timeout.tv_usec = 1000 * (ms % 1000);
		int rs = fdMaxfd == -1 ? 0 : select(fdMaxfd+1,&readset,&writeset,0,&timeout);
		fdMaxfd = -1;
        V_CC = (ClaireBoolean *)((rs<=0 ? CFALSE : CTRUE));
        }
      Result= (ClaireBoolean *) V_CC;}
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: get_descriptor(self:port) [0]
descriptor * get_descriptor_port1(PortObject *self)
{ { descriptor *Result ;
    { device *V_CC ;
      { device * p = get_device_port1(self);
        if (inherit_ask_class(p->isa,Core._descriptor) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_("~S is not a descriptor"),
          _oid_(list::alloc(1,_oid_(self))))));
        V_CC = p;
        }
      Result= (descriptor *) V_CC;}
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: readable?(self:port) [0]
ClaireBoolean * readable_ask_port1(PortObject *self)
{ { ClaireBoolean *Result ;
    { ClaireObject *V_CC ;
      { descriptor * p = get_descriptor_port1(self);
        V_CC = (ClaireBoolean *)((FD_ISSET(p->fd, &readset) ? CTRUE : CFALSE));
        }
      Result= (ClaireBoolean *) V_CC;}
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: writable?(self:port) [0]
ClaireBoolean * writable_ask_port1(PortObject *self)
{ { ClaireBoolean *Result ;
    { ClaireObject *V_CC ;
      { descriptor * p = get_descriptor_port1(self);
        V_CC = (ClaireBoolean *)((FD_ISSET(p->fd, &writeset) ? CTRUE : CFALSE));
        }
      Result= (ClaireBoolean *) V_CC;}
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: read!(self:port) [0]
void  read_I_port1(PortObject *self)
{ { descriptor * p = get_descriptor_port1(self);
    
		if(fdMaxfd == -1) {FD_ZERO(&readset); FD_ZERO(&writeset);}
		if(p->fd > fdMaxfd) fdMaxfd = p->fd;
		FD_SET(p->fd, &readset);;
    }
  POP_SIGNAL;}


// The c++ function for: write!(self:port) [0]
void  write_I_port1(PortObject *self)
{ { descriptor * p = get_descriptor_port1(self);
    
		if(fdMaxfd == -1) {FD_ZERO(&readset); FD_ZERO(&writeset);}
		if(p->fd > fdMaxfd) fdMaxfd = p->fd;
		FD_SET(p->fd, &writeset);;
    }
  POP_SIGNAL;}


// The c++ function for: readwrite!(self:port) [0]
void  readwrite_I_port1(PortObject *self)
{ read_I_port1(self);
  write_I_port1(self);
  POP_SIGNAL;}


// ***************************************************************************
// * part 10: disk_file                                                      *
// ***************************************************************************
// The c++ function for: princ(self:disk_file) [NEW_ALLOC]
void  princ_disk_file1(disk_file *self)
{ princ_string("file/");
  print_any(((OID)self->fd));
  princ_string("/");
  { OID  g0196UU;
    if (self->mode == 1)
     g0196UU = _string_("r");
    else if (self->mode == 0)
     g0196UU = _string_("w");
    else if (self->mode == 2)
     g0196UU = _string_("rw");
    else g0196UU = Kernel.cfalse;
      (*Kernel.princ)(g0196UU);
    }
  princ_string("(");
  princ_string(self->file_path);
  princ_string(")");
  POP_SIGNAL;}


// The c++ function for: disk_file!(self:string,mod:{"r", "w", "a", "rw", "wr", "rb", "wb", "ab"}) [NEW_ALLOC+SLOT_UPDATE]
disk_file * disk_file_I_string1(char *self,char *mod)
{ GC_BIND;
  { disk_file *Result ;
    { disk_file * f;
      { { descriptor *V_CC ;
          { disk_file * _CL_obj = ((disk_file *) GC_OBJECT(disk_file,new_object_class(Core._disk_file)));
            (_CL_obj->file_path = self);
            (_CL_obj->mode = (((equal_string(mod,"r") == CTRUE) || 
                (equal_string(mod,"rb") == CTRUE)) ?
              1 :
              (((equal_string(mod,"w") == CTRUE) || 
                  ((equal_string(mod,"wb") == CTRUE) || 
                    ((equal_string(mod,"a") == CTRUE) || 
                      (equal_string(mod,"ab") == CTRUE)))) ?
                0 :
                2 ) ));
            V_CC = close_descriptor1(_CL_obj);
            }
          f= (disk_file *) V_CC;}
        GC_OBJECT(disk_file,f);}
      CL_INT  desc;
      if ((equal_string(mod,"r") == CTRUE) || 
          (equal_string(mod,"rb") == CTRUE))
       desc = (int )(open(self, O_RDONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
      else if ((equal_string(mod,"rw") == CTRUE) || 
          (equal_string(mod,"wr") == CTRUE))
       desc = (int )(open(self, O_RDWR|O_APPEND|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
      else if ((equal_string(mod,"w") == CTRUE) || 
          (equal_string(mod,"wb") == CTRUE))
       desc = (int )(open(self, O_WRONLY|O_APPEND|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
      else desc = (int )(open(self, O_WRONLY|O_APPEND|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
        if (desc == ((CL_INT)-1))
       Cerrorno(36, _string_(self), 0);
      (f->fd = desc);
      Result = f;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> reopen a file for read, the current offset
// of the reopened file is moved at the same place
// if a buffer is present on the filter chain then
// it contents and index are restored
// The c++ function for: reopen(self:port) [NEW_ALLOC+SLOT_UPDATE]
PortObject * reopen_port1(PortObject *self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { PortObject *Result ;
    { disk_file * s = get_disk_file_port1(self);
      CL_INT  pos = (int )((CL_INT)lseek(s->fd, (off_t)0, SEEK_CUR));
      disk_file * n = GC_OBJECT(disk_file,disk_file_I_string1(GC_STRING(s->file_path),"r"));
      PortObject * t = n;
      (n->firstc = s->firstc);
      lseek(n->fd, (off_t)pos, SEEK_SET);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(f);
        bag *f_support;
        f_support = GC_OBJECT(list,s->filters);
        for (START(f_support); NEXT(f);)
        { GC_LOOP;
          if (INHERIT(OBJECT(ClaireObject,f)->isa,Core._buffer))
           GC__ANY(t = buffer_I_buffer1(OBJECT(buffer,f),t), 1);
          else if (INHERIT(OBJECT(ClaireObject,f)->isa,Core._line_counter))
           GC__ANY(t = line_counter_I_line_counter1(OBJECT(line_counter,f),t), 1);
          else if (INHERIT(OBJECT(ClaireObject,f)->isa,Core._byte_counter))
           GC__ANY(t = byte_counter_I_byte_counter1(OBJECT(byte_counter,f),t), 1);
          GC_UNLOOP; POP_SIGNAL;}
        }
      Result = t;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> open a file on disk. the returned port is buffered.
// This is a lib C like fopen API (see man for details).
// note: unlike in C lib there is no support for the 'b'
// mode (binary) i.e. always open in binary mode
// The c++ function for: fopen(self:string,mode:{"r", "w", "a", "rw", "wr", "rb", "wb", "ab"}) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
buffer * fopen_string1(char *self,char *mode)
{ GC_BIND;
  { buffer *Result ;
    { filter *V_CC ;
      { disk_file * f = GC_OBJECT(disk_file,disk_file_I_string1(self,mode));
        V_CC = close_target_I_filter1(buffer_I_port1(f,4096));
        }
      Result= (buffer *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: get_disk_file(self:port) [0]
disk_file * get_disk_file_port1(PortObject *self)
{ { disk_file *Result ;
    { device *V_CC ;
      { device * p = get_device_port1(self);
        if (inherit_ask_class(p->isa,Core._disk_file) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_("~S is not a disk file"),
          _oid_(list::alloc(1,_oid_(self))))));
        V_CC = p;
        }
      Result= (disk_file *) V_CC;}
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: flock(self:port) [SLOT_UPDATE+RETURN_ARG]
void  flock_port1(PortObject *self)
{ { disk_file * f = get_disk_file_port1(self);
    if (f->locked_ask != CTRUE)
     { 
			int rc = -1;
			#ifdef CLPC
				long p = _tell(f->fd);
				_lseek(f->fd, 0, SEEK_SET);
				while(rc < 0) {
					rc = _locking(f->fd, _LK_LOCK, 1);
				}
				_lseek(f->fd, p, SEEK_SET);
				p = _tell(f->fd);
			#else 
				#ifdef HAVE_FCNTL
					struct flock lock_it;
					lock_it.l_whence = SEEK_SET;
					lock_it.l_start = 0;
					lock_it.l_len = 0;
					lock_it.l_type = (f->mode == 1 ? F_RDLCK :
										(f->mode == 2 ? (F_WRLCK|F_RDLCK) :
											F_WRLCK));
					lock_it.l_pid = 0;
					while ( ((rc = fcntl(f->fd, F_SETLKW, &lock_it)) < 0) &&
								(errno == EINTR) ) {
						continue;
					}
				#endif
			#endif
			if (rc < 0)
				Cerrorno(94,_oid_(f),0);;
      (f->locked_ask = CTRUE);
      }
    }
  POP_SIGNAL;}


// The c++ function for: funlock(self:port) [SLOT_UPDATE+RETURN_ARG]
void  funlock_port1(PortObject *self)
{ { disk_file * f = get_disk_file_port1(self);
    if (f->locked_ask == CTRUE)
     { 
			int rc = 0;
			#ifdef CLPC
				long p = _tell(f->fd);
				_lseek(f->fd, 0, SEEK_SET);
				rc = _locking(f->fd, _LK_UNLCK, 1);
				_lseek(f->fd, p, SEEK_SET);
				p = _tell(f->fd);
			#else 
				#ifdef HAVE_FCNTL
					struct flock unlock_it;
					unlock_it.l_whence = SEEK_SET;
					unlock_it.l_start  = 0;
					unlock_it.l_len    = 0;
					unlock_it.l_type   = F_UNLCK;
					unlock_it.l_pid    = 0;
					rc = fcntl(f->fd, F_SETLKW, &unlock_it);
				#endif
			#endif
			if (rc < 0)
				Cerrorno(95,_oid_(self),0);;
      (f->locked_ask = CFALSE);
      }
    }
  POP_SIGNAL;}


// The c++ function for: islocked?(self:port) [0]
ClaireBoolean * islocked_ask_port1(PortObject *self)
{ { ClaireBoolean *Result ;
    { ClaireBoolean * l = CFALSE;
      disk_file * f = get_disk_file_port1(self);
      
			int rc = 0;
			#ifdef CLPC
				long p = _tell(f->fd);
				_lseek(f->fd, 0, SEEK_SET);
				rc = _locking(f->fd, _LK_NBLCK, 1);
				if (rc == 0) {
					_lseek(f->fd, 0, SEEK_SET);
					_locking(f->fd, _LK_UNLCK, 1);
					_lseek(f->fd, p, SEEK_SET);
					p = _tell(f->fd);
					l = CFALSE;
				} else if (rc > 0) {
					lseek(f->fd, p, SEEK_SET);
					p = _tell(f->fd);
					l = CTRUE;
				}
			#else 
				#ifdef HAVE_FCNTL
					struct flock lock_it;
					lock_it.l_whence = SEEK_SET;
					lock_it.l_start = 0;
					lock_it.l_len = 0;
					lock_it.l_type = f->mode == 1 ? F_RDLCK : F_WRLCK;
					lock_it.l_pid = 0;
					rc = fcntl(f->fd, F_GETLK, &lock_it);
					l = (lock_it.l_type != F_UNLCK) ? CTRUE : CFALSE;
				#endif
			#endif
			if (rc < 0)
				Cerrorno(94,_oid_(self),0);;
      Result = l;
      }
    POP_SIGNAL; return (Result);}
  }


// ***************************************************************************
// * part 11: pipe                                                           *
// ***************************************************************************
//<sb> create a pair of unidirectional pipe connected to each other.
// The first one is intended for read and the second one for write.
// note: some system may return bi-directional pipes...
// The c++ function for: pipe!() [NEW_ALLOC+SLOT_UPDATE]
tuple * pipe_I_void1_()
{ return pipe_I_void1()->copyIfNeeded();}


// The c++ function for: pipe!(_CL_obj:void) [NEW_ALLOC+SLOT_UPDATE]
tuple * pipe_I_void1()
{ GC_BIND;
  { tuple *Result ;
    { cl_pipe * p1;
      { { descriptor *V_CC ;
          { cl_pipe * _CL_obj = ((cl_pipe *) GC_OBJECT(cl_pipe,new_object_class(Core._pipe)));
            V_CC = close_descriptor1(_CL_obj);
            }
          p1= (cl_pipe *) V_CC;}
        GC_OBJECT(cl_pipe,p1);}
      cl_pipe * p2;
      { { descriptor *V_CC ;
          { cl_pipe * _CL_obj = ((cl_pipe *) GC_OBJECT(cl_pipe,new_object_class(Core._pipe)));
            V_CC = close_descriptor1(_CL_obj);
            }
          p2= (cl_pipe *) V_CC;}
        GC_OBJECT(cl_pipe,p2);}
      CL_INT fds[2];
      if ((int )(::pipe(fds)) == ((CL_INT)-1))
       Cerrorno(98, 0, 0);
      (p1->fd = *fds);
      (p2->fd = *(fds+1));
      Result = tuple::allocStack(2,_oid_(p1),_oid_(p2));
      }
    GC_UNBIND; return (Result);}
  }


// The c++ function for: princ(self:pipe) [NEW_ALLOC]
void  princ_pipe1(cl_pipe *self)
{ princ_string("pipe/");
  print_any(((OID)self->fd));
  POP_SIGNAL;}


// ***************************************************************************
// * part 12: socket                                                         *
// ***************************************************************************
// The c++ function for: princ(self:socket) [NEW_ALLOC+SLOT_UPDATE]
void  princ_socket1(cl_socket *self)
{ print_any(_oid_(OWNER(_oid_(self))));
  princ_string("/");
  princ_string(((self->address[1 - 1] == ((unsigned char)47 /* '/' */)) ?
    "UNIX" :
    "INET" ));
  princ_string("/");
  print_any(((OID)self->fd));
  princ_string("(");
  princ_string(self->address);
  princ_string(":");
  print_any(((OID)self->tcpport));
  princ_string(")");
  POP_SIGNAL;}


// The c++ function for: close_port(self:socket) [0]
void  close_port_socket1_Core(cl_socket *self)
{ 
	#ifdef CLPC
		closesocket(self->fd);
	#else
		::close(self->fd)
	#endif
	;
  POP_SIGNAL;}


// The c++ function for: unlink(self:listener) [0]
void  unlink_listener1(listener *self)
{ unlink_string(self->address);
  POP_SIGNAL;}


// The c++ function for: gethostname(_CL_obj:void) [NEW_ALLOC]
char * gethostname_void1()
{ char tmp[500];
  { char *Result ;
    Result = (((((ClaireBoolean *) (ClaireBoolean *)((gethostname(tmp, 500) == 0 ? CTRUE : CFALSE)))) == CTRUE) ?
      copy_string((char *)(tmp)) :
      "unknown host name" );
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: client!(addr:string,p:integer) [NEW_ALLOC+SLOT_UPDATE]
cl_socket * client_I_string1(char *addr,int p)
{ GC_BIND;
  { cl_socket *Result ;
    { cl_socket * s;
      { { descriptor *V_CC ;
          { cl_socket * _CL_obj = ((cl_socket *) GC_OBJECT(cl_socket,new_object_class(Core._socket)));
            (_CL_obj->address = addr);
            (_CL_obj->tcpport = p);
            V_CC = close_descriptor1(_CL_obj);
            }
          s= (cl_socket *) V_CC;}
        GC_OBJECT(cl_socket,s);}
      (s->fd = connect_string1(addr,p));
      Result = s;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: client!(addr:string) [NEW_ALLOC+SLOT_UPDATE]
cl_socket * client_I_string2(char *addr)
{ GC_BIND;
  { cl_socket *Result ;
    { cl_socket * s;
      { { descriptor *V_CC ;
          { cl_socket * _CL_obj = ((cl_socket *) GC_OBJECT(cl_socket,new_object_class(Core._socket)));
            (_CL_obj->address = addr);
            (_CL_obj->tcpport = -1);
            V_CC = close_descriptor1(_CL_obj);
            }
          s= (cl_socket *) V_CC;}
        GC_OBJECT(cl_socket,s);}
      (s->fd = connect_string1(addr,-1));
      Result = s;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: connect(addr:string,p:integer) [0]
int  connect_string1(char *addr,int p)
{ 
		int sock;
		int unix_domain = 0;
		#ifdef CLPC
			struct sockaddr_in inAddr;
		#else
			struct sockaddr_in inAddr;
			struct sockaddr_un unAddr;
			unix_domain = (strlen(addr) > 0 && addr[0] == '/');
		#endif
		if((sock = socket(unix_domain ? AF_UNIX : AF_INET, SOCK_STREAM, 0)) < 0)
			Cerrorno(74,_string_("connect @ string"),0);
		if (unix_domain) {
			#ifndef CLPC
			strcpy(unAddr.sun_path, addr);
			#endif
		} else if((addr[0] >= '0' && addr[0] <= '9') || *addr == 0) {
			if(*addr == 0) inAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
			else inAddr.sin_addr.s_addr = inet_addr(addr);
		} else {
			struct hostent *servent;
			if((servent = gethostbyname(addr)) == 0) {
				#ifdef CLPC
					closesocket(sock);
				#else
					::close(sock);
				#endif
				Cerrorno(74,_string_("connect @ string"),0);
			}
			memcpy(&inAddr.sin_addr, servent->h_addr, servent->h_length);
		}
		if (unix_domain) {
			#ifndef CLPC
			unAddr.sun_family = AF_UNIX;
			#endif
		} else {
			inAddr.sin_family = AF_INET;
			inAddr.sin_port = htons(p);
		}
		#ifdef CLPC
		if((connect(sock, (sockaddr*)&inAddr, sizeof(inAddr))) != 0) {
		#else
		if( (unix_domain && connect(sock, (sockaddr*)&unAddr, sizeof(unAddr)) != 0) ||
			(unix_domain == 0 && connect(sock, (sockaddr*)&inAddr, sizeof(inAddr))) != 0) {
		#endif
			#ifdef CLPC
				closesocket(sock);
			#else
				::close(sock);
			#endif
			Cerrorno(74,_string_("connect @ string"),0);
		};
  POP_SIGNAL; return ((int )(sock));}


//<sb> creates a UNIX domain listener socket
// The c++ function for: server!(addr:string) [NEW_ALLOC]
listener * server_I_string2(char *addr)
{ POP_SIGNAL; return (server_I_string1(addr,-1,5));}


//<sb> creates a INET domain listener socket
// The c++ function for: server!(p:integer) [NEW_ALLOC]
listener * server_I_integer1(int p)
{ POP_SIGNAL; return (server_I_string1("",p,5));}


// The c++ function for: server!(addr:string,p:integer,qlen:integer) [NEW_ALLOC+SLOT_UPDATE]
listener * server_I_string1(char *addr,int p,int qlen)
{ GC_BIND;
  { listener *Result ;
    { listener * s;
      { { descriptor *V_CC ;
          { listener * _CL_obj = ((listener *) GC_OBJECT(listener,new_object_class(Core._listener)));
            (_CL_obj->address = string_v(CLREAD(slot,_at_property1(Core.address,Core._listener),DEFAULT)));
            V_CC = close_descriptor1(_CL_obj);
            }
          s= (listener *) V_CC;}
        GC_OBJECT(listener,s);}
      
		int sock;
		int unix_domain = 0;
		#ifdef CLPC
			struct sockaddr_in inAddr;
		#else
			struct sockaddr_in inAddr;
			struct sockaddr_un unAddr;
			unix_domain = (strlen(addr) > 0 && addr[0] == '/');
		#endif
		if((sock = socket(unix_domain ? AF_UNIX : AF_INET, SOCK_STREAM, 0)) == 0) {
			#ifdef CLPC
				closesocket(sock);
			#else
				::close(sock);
			#endif
			Cerrorno(74,_string_("server! @ string"),0);
		}
		int val = 1;
		setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&val, sizeof(val));
		#if !defined(CLPC)
		// ensure a previously used socket won't prevent to call to succed
		setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char*)&val,sizeof(val));
		if(fcntl(sock, F_GETFL, 0) == -1) {
			::close(sock);
			Cerrorno(74,_string_("server! @ string"),0);
		}
		#endif
		if (unix_domain) {
			#ifndef CLPC
			strcpy(unAddr.sun_path, addr);
			#endif
		} else if(strlen(addr)==0) inAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		else inAddr.sin_addr.s_addr = inet_addr(addr);
		if (unix_domain) {
			#ifndef CLPC
			unAddr.sun_family = unix_domain ? AF_UNIX : AF_INET;
			#endif
		} else {
			inAddr.sin_family = unix_domain ? AF_UNIX : AF_INET;
			inAddr.sin_port = htons(p);
		}
		#ifdef CLPC
		if( (bind(sock, (sockaddr*)&inAddr, sizeof(inAddr)) != 0)) {
		#else
		if( (unix_domain && bind(sock, (sockaddr*)&unAddr, sizeof(unAddr)) != 0) ||
			(unix_domain == 0 && bind(sock, (sockaddr*)&inAddr, sizeof(inAddr)) != 0)) {
		#endif
			#ifdef CLPC
				closesocket(sock);
			#else
				::close(sock);
			#endif
			Cerrorno(74,_string_("server! @ string"),0);
		}
		if(listen(sock, qlen) != 0) {
			#ifdef CLPC
				closesocket(sock);
			#else
				::close(sock);
			#endif
			Cerrorno(74,_string_("server! @ string"),0);
		};
      (s->fd = (int )(sock));
      if (addr[1 - 1] == ((unsigned char)47 /* '/' */))
       (s->address = addr);
      else { (s->address = gethostname_void1());
          (s->tcpport = p);
          }
        Result = s;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: shutdown(self:socket,mod:{"r", "w"}) [0]
void  shutdown_socket1(cl_socket *self,char *mod)
{ if (equal_string(mod,"r") == CTRUE)
   { {
		#if defined(CLPC)
			::shutdown(self->fd, SD_RECEIVE);
		#else 
			::shutdown(self->fd, SHUT_RD);
		#endif
		};
    ;}
  else { {
		#if defined(CLPC)
			::shutdown(self->fd, SD_SEND);
		#else 
			::shutdown(self->fd, SHUT_WR);
		#endif
		};
      ;}
    POP_SIGNAL;}


// The c++ function for: linger(self:socket) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  linger_socket1(cl_socket *self)
{ flush_port1(self);
  
		#if defined(CLPC)
			int how = SD_SEND;
		#else 
			int how = SHUT_WR;
		#endif
		if(!::shutdown(self->fd, how)) {
			int t = 0;
			do {
				fd_set fdset;
				struct timeval tv;
				tv.tv_sec = 0;
				tv.tv_usec = 1000;
				FD_ZERO(&fdset);
				FD_SET(self->fd, &fdset);
				if(select(self->fd+1, &fdset, NULL, NULL, &tv) > 0) {
					char dummy[256];
					if (recv(self->fd,dummy,256,0) != 0)
						break; }
				t++;
			} while(t < 3000);
		};
  fclose_device1(self);
  POP_SIGNAL;}


// The c++ function for: accept(self:listener) [NEW_ALLOC+SLOT_UPDATE]
cl_socket * accept_listener1(listener *self)
{ GC_BIND;
  { cl_socket *Result ;
    { cl_socket * c;
      { { descriptor *V_CC ;
          { cl_socket * _CL_obj = ((cl_socket *) GC_OBJECT(cl_socket,new_object_class(Core._socket)));
            (_CL_obj->tcpport = self->tcpport);
            (_CL_obj->address = string_v(CLREAD(slot,_at_property1(Core.address,Core._socket),DEFAULT)));
            V_CC = close_descriptor1(_CL_obj);
            }
          c= (cl_socket *) V_CC;}
        GC_OBJECT(cl_socket,c);}
      
		int s;
		#ifdef CLPC
			struct sockaddr_in inAddr;
			int sin_size = sizeof(struct sockaddr_in);
			s = accept(self->fd, (struct sockaddr*)(&inAddr), &sin_size);
			if(s == INVALID_SOCKET) {
				Cerrorno(74,_string_("accept @ listener"),0);
			}
		#else
			struct sockaddr_in inAddr;
			GETPEERNAME_ARG3 sin_size = (GETPEERNAME_ARG3)sizeof(struct sockaddr_in);
			s = accept(self->fd, (struct sockaddr*)(&inAddr), &sin_size);
			if(s == -1) {
				Cerrorno(74,_string_("accept @ listener"),0);
			}
		#endif
		;
      (c->fd = (int )(s));
      (c->address = copy_string((char *)(inet_ntoa(inAddr.sin_addr))));
      Result = c;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: socketpair() [NEW_ALLOC]
tuple * socketpair_void1_()
{ return socketpair_void1()->copyIfNeeded();}


// The c++ function for: socketpair(_CL_obj:void) [NEW_ALLOC]
tuple * socketpair_void1()
{ GC_BIND;
  { tuple *Result ;
    { cl_socket * s1;
      { { descriptor *V_CC ;
          { cl_socket * _CL_obj = ((cl_socket *) GC_OBJECT(cl_socket,new_object_class(Core._socket)));
            (_CL_obj->address = string_v(CLREAD(slot,_at_property1(Core.address,Core._socket),DEFAULT)));
            V_CC = close_descriptor1(_CL_obj);
            }
          s1= (cl_socket *) V_CC;}
        GC_OBJECT(cl_socket,s1);}
      cl_socket * s2;
      { { descriptor *V_CC ;
          { cl_socket * _CL_obj = ((cl_socket *) GC_OBJECT(cl_socket,new_object_class(Core._socket)));
            (_CL_obj->address = string_v(CLREAD(slot,_at_property1(Core.address,Core._socket),DEFAULT)));
            V_CC = close_descriptor1(_CL_obj);
            }
          s2= (cl_socket *) V_CC;}
        GC_OBJECT(cl_socket,s2);}
      tuple * res = tuple::alloc(2,_oid_(s1),_oid_(s2));
      
		#if defined(CLPC) || !defined(HAVE_SOCKETPAIR)
			Cerror(75,_string_("socketpair"),0);
		#else
			int socks[2];
			if(socketpair((CL_INT)AF_UNIX, (CL_INT)SOCK_STREAM, 0, socks) < 0) {
				Cerrorno(74,_string_("socketpair @ void"),0);
			}
			s1->fd = socks[0];
			s2->fd = socks[1];
		#endif
		;
      Result = res;
      }
    GC_UNBIND; return (Result);}
  }


// The c++ function for: read_port(self:socket,buf:char*,len:integer) [SLOT_UPDATE]
int  read_port_socket1_Core(cl_socket *self,char*buf,int len)
{ { CL_INT Result = 0;
    { CL_INT  r = 0;
      
#ifdef CLPC
;
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((CL_INT)r < (CL_INT)len))
        { { CL_INT  n = (int )(::recv(self->fd, buf + r, len - r,0));
            if (n == 0)
             { (self->eof_reached_ask = CTRUE);
              { ;ClEnv->cHandle = loop_handle; break;}
              }
            else if (n == ((CL_INT)-1))
             Cerrorno(97, _string_("read"), _oid_(self));
            else r= ((CL_INT)r+(CL_INT)n);
              }
          POP_SIGNAL;}
        }
      
#else
;
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((CL_INT)r < (CL_INT)len))
        { { CL_INT  n = (int )(::read(self->fd, buf + r, len - r));
            if (n == 0)
             { (self->eof_reached_ask = CTRUE);
              { ;ClEnv->cHandle = loop_handle; break;}
              }
            else if ((n == ((CL_INT)-1)) && 
                ((((ClaireBoolean *) (ClaireBoolean *)((errno != EINTR ? CTRUE : CFALSE)))) == CTRUE))
             Cerrorno(97, _string_("read"), _oid_(self));
            else r= ((CL_INT)r+(CL_INT)n);
              }
          POP_SIGNAL;}
        }
      
#endif
;
      Result = r;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: write_port(self:socket,buf:char*,len:integer) [0]
int  write_port_socket1_Core(cl_socket *self,char*buf,int len)
{ { CL_INT Result = 0;
    { CL_INT  r = 0;
      
#ifdef CLPC
;
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((CL_INT)r < (CL_INT)len))
        { { CL_INT  n = (int )(::send(self->fd, buf + r, len - r,0));
            if (n == ((CL_INT)-1))
             Cerrorno(97, _string_("write"), _oid_(self));
            else r= ((CL_INT)r+(CL_INT)n);
              }
          POP_SIGNAL;}
        }
      
#else
;
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((CL_INT)r < (CL_INT)len))
        { { CL_INT  n = (int )(::write(self->fd, buf + r, len - r));
            if ((n == ((CL_INT)-1)) && 
                ((((ClaireBoolean *) (ClaireBoolean *)((errno != EINTR ? CTRUE : CFALSE)))) == CTRUE))
             Cerrorno(97, _string_("write"), _oid_(self));
            else r= ((CL_INT)r+(CL_INT)n);
              }
          POP_SIGNAL;}
        }
      
#endif
;
      Result = r;
      }
    POP_SIGNAL; return (Result);}
  }


// ***************************************************************************
// * part 13: source location                                                *
// ***************************************************************************
//<sb> print the location associated with the current state
// of the given port without issuing a dynamic message (debug proof).
// mainly used to print "<file>:<line>"
// The c++ function for: print_source_location(self:port) [NEW_ALLOC]
void  print_source_location_port1(PortObject *self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { CL_INT  line = 0;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while ((INHERIT(self->isa,Core._filter)))
      { GC_LOOP;
        if (OWNER(_oid_(self)) == Core._line_counter)
         line= ((CL_INT)1+(CL_INT)CLREAD(line_counter,self,read_lines));
        GC__ANY(self = CLREAD(filter,self,target), 1);
        GC_UNLOOP;POP_SIGNAL;}
      }
    { device * d = ((device *) self);
      if (INHERIT(d->isa,Core._disk_file))
       princ_string(CLREAD(disk_file,d,file_path));
      else if (INHERIT(d->isa,Core._socket))
       princ_string(append_string(CLREAD(cl_socket,d,address),GC_STRING(string_I_integer (CLREAD(cl_socket,d,tcpport)))));
      else if (INHERIT(d->isa,Core._descriptor))
       princ_string(append_string("descriptor ",GC_STRING(string_I_integer (CLREAD(descriptor,d,fd)))));
      else princ_string(OWNER(_oid_(d))->name->name);
        if ((CL_INT)line > 0)
       { princ_string(":");
        princ_integer(line);
        }
      }
    }
  GC_UNBIND; POP_SIGNAL;}


//<sb> return the current file and position in that file
// in the form of tuple(<filename>, <line>, <offset in the line>)
// The c++ function for: get_location(g0197:port) [NEW_ALLOC]
tuple * get_location_port1_(PortObject *g0197)
{ return get_location_port1(g0197)->copyIfNeeded();}


// The c++ function for: get_location(self:port) [NEW_ALLOC]
tuple * get_location_port1(PortObject *self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { tuple *Result ;
    { CL_INT  line = 0;
      CL_INT  off = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((INHERIT(self->isa,Core._filter)))
        { GC_LOOP;
          if (OWNER(_oid_(self)) == Core._line_counter)
           { line= ((CL_INT)1+(CL_INT)CLREAD(line_counter,self,read_lines));
            off= ((CL_INT)CLREAD(line_counter,self,line_offset)+(CL_INT)1);
            }
          GC__ANY(self = CLREAD(filter,self,target), 1);
          GC_UNLOOP;POP_SIGNAL;}
        }
      { device * d = ((device *) self);
        { OID v_bag;
          GC_ANY(Result= tuple::empty());
          { if (INHERIT(d->isa,Core._disk_file))
             v_bag = _string_(CLREAD(disk_file,d,file_path));
            else if (INHERIT(d->isa,Core._socket))
             v_bag = _string_(append_string(CLREAD(cl_socket,d,address),GC_STRING(string_I_integer (CLREAD(cl_socket,d,tcpport)))));
            else if (INHERIT(d->isa,Core._descriptor))
             v_bag = _string_(append_string("descriptor ",GC_STRING(string_I_integer (CLREAD(descriptor,d,fd)))));
            else v_bag = _string_(OWNER(_oid_(d))->name->name);
              GC_OID(v_bag);}
          ((tuple *) Result)->addFast((OID)v_bag);
          ((tuple *) Result)->addFast((OID)((OID)line));
          ((tuple *) Result)->addFast((OID)((OID)off));}
        }
      }
    GC_UNBIND; return (Result);}
  }


// ***************************************************************************
// * part 5: popen                                                           *
// ***************************************************************************
//<sb> our only C FILE* interface: redirected process
// The c++ function for: eof_port?(self:popen_device) [0]
ClaireBoolean * eof_port_ask_popen_device1_Core(Core_popen_device *self)
{ POP_SIGNAL; return (((ClaireBoolean *) (ClaireBoolean *)((feof(self->child_comm) ? CTRUE : CFALSE))));}


// The c++ function for: close_port(self:popen_device) [0]
void  close_port_popen_device1_Core(Core_popen_device *self)
{ ::fclose(self->child_comm);
  POP_SIGNAL;}


// The c++ function for: read_port(self:popen_device,buf:char*,len:integer) [0]
int  read_port_popen_device1_Core(Core_popen_device *self,char*buf,int len)
{ { CL_INT Result = 0;
    { CL_INT  rc = (int )(::fread(buf,1,len,self->child_comm));
      if ((((ClaireBoolean *) (ClaireBoolean *)((ferror(self->child_comm) ? CTRUE : CFALSE)))) == CTRUE)
       Cerrorno(74,_string_("read_port @ popen_device"),0);
      Result = rc;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: flush_port(self:popen_device) [0]
void  flush_port_popen_device1_Core(Core_popen_device *self)
{ ::fflush(self->child_comm);
  POP_SIGNAL;}


// The c++ function for: write_port(self:popen_device,buf:char*,len:integer) [0]
int  write_port_popen_device1_Core(Core_popen_device *self,char*buf,int len)
{ { CL_INT Result = 0;
    { CL_INT  rc = (int )(::fwrite(buf,1,len,self->child_comm));
      if ((((ClaireBoolean *) (ClaireBoolean *)((ferror(self->child_comm) ? CTRUE : CFALSE)))) == CTRUE)
       Cerrorno(74,_string_("write_port @ popen_device"),0);
      Result = rc;
      }
    POP_SIGNAL; return (Result);}
  }


//<sb> popen may be a two way communication device, this
// is system dependent
// The c++ function for: popen(file:string,mod:{"r", "w", "rw"}) [NEW_ALLOC]
Core_popen_device * popen_string1(char *file,char *mod)
{ GC_BIND;
  { Core_popen_device *Result ;
    { FILE* f = (FILE*)(::popen(file, mod));
      if ((((ClaireBoolean *) (ClaireBoolean *)((f == NULL ? CTRUE : CFALSE)))) == CTRUE)
       Cerrorno(74,_string_("popen @ string"),0);
      { Core_popen_device * _CL_obj = ((Core_popen_device *) GC_OBJECT(Core_popen_device,new_object_class(Core._popen_device)));
        (_CL_obj->child_comm = f);
        Result = _CL_obj;
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> perform a backquote expansion of the command s.
// subexpressions enclosed by '`' are substituted by the
// output generated by the corresponding command
// ex: bexpand("`ls`") returns the result of an ls command
// The c++ function for: bqexpand(s:string) [NEW_ALLOC+SLOT_UPDATE]
char * bqexpand_string1(char *s)
{ GC_RESERVE(5);  // v3.0.55 optim !
  { char *Result ;
    { list * subs = GC_OBJECT(list,explode_string(s,"`"));
      char * res = "";
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((subs->length != 0))
        { GC_LOOP;
          GC__STRING(res = append_string(res,string_v((*(subs))[1])), 3);
          subs= skip_list(subs,1);
          if (subs->length != 0)
           { Core_popen_device * p = GC_OBJECT(Core_popen_device,popen_string1(string_v((*(subs))[1]),"r"));
            char * tmp = "";
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))) != Kernel.ctrue))
              { GC_LOOP;
                GC__STRING(tmp = append_string(tmp,GC_STRING(fread_port4(p,1024))), 5);
                GC_UNLOOP;POP_SIGNAL;}
              }
            GC__STRING(res = append_string(res,GC_STRING(trim_string(tmp))), 3);
            subs= skip_list(subs,1);
            fclose_device1(p);
            }
          GC_UNLOOP;POP_SIGNAL;}
        }
      Result = res;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }



