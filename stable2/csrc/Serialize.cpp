/***** CLAIRE Compilation of file meta/serialization.cl 
         [version 3.5.0 / safety 5] *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllexport)
#endif
#include <Serialize.h>

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllimport)
#endif

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllexport)
#endif

//*********************************************************************
//* CLAIRE                                            Sylvain Benilan *
//* serialization.cl                                                  *
//* Copyright (C) 2000 - 2003 xl. All Rights Reserved                 *
//*********************************************************************
// This file contains general purpose (un)serialization methods
// for storage or IPC.
// It is intended to to be fast and simple, the serialization format
// is non-human readable (i.e. binary), its API is provided on port.
// Last the serialization method is intended to be endian sensitiveness
// such serialized data is portable.
// *********************************************************************
// *  Table of contents                                                *
// *   Part 1: global                                                  *
// *   Part 2: serialize                                               *
// *   Part 3: unserialize                                             *
// *   Part 4: api                                                     *
// *********************************************************************
// *********************************************************************
// *   Part 1: global                                                  *
// *********************************************************************
// The c++ function for: close(self:serialize_context) [RETURN_ARG]
CL_EXPORT serialize_context * close_serialize_context1(serialize_context *self) { 
    POP_SIGNAL; return (self);}
  


// The c++ function for: nth(self:serialize_context,x:any) [0]
CL_EXPORT CL_INT  nth_serialize_context1(serialize_context *self,OID x) { 
    { CL_INT Result = 0;
      { list * l = self->alreadySerialized;
        CL_INT  i = 1;
        { ClaireBoolean * g0312I;
          { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(y);
              V_C= Kernel.cfalse;
              for (START(l); NEXT(y);)
              { if (equal(y,x) == CTRUE)
                 { V_C = Kernel.ctrue;
                  ClEnv->cHandle = loop_handle;break;}
                ++i;
                }
              }
            
            g0312I=OBJECT(ClaireBoolean,V_C);}
          
          if (g0312I == CTRUE) Result = i;
            else Result = 0;
          }
        }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: preSerialize(self:any,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  preSerialize_any1(OID self,serialize_context *ctx) { 
    
    GC_BIND;
    if (INHERIT(OWNER(self),Kernel._bag))
     { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(i);
      bag *i_support;
      i_support = GC_OBJECT(bag,enumerate_any(self));
      for (START(i_support); NEXT(i);)
      preSerialize_any1(i,ctx);
      }
    else if (INHERIT(OWNER(self),Core._global_variable))
     GC_OBJECT(list,ctx->toSerialize_ask)->addFast((OID)GC_OID(get_property(Kernel.value,OBJECT(ClaireObject,self))));
    else if ((self != CNULL) && 
        (_Z_any1(self,Kernel._object) == CTRUE))
     GC_OBJECT(list,ctx->toSerialize_ask)->addFast((OID)self);
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: close(self:unserialize_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT unserialize_context * close_unserialize_context1(unserialize_context *self) { 
    _void_(self->unserialized = make_table_type(Kernel._integer,Kernel._any,CNULL));
    POP_SIGNAL; return (self);}
  


// The c++ function for: puti(aint:integer,p:port) [0]
CL_EXPORT void  puti_integer1(CL_INT aint,PortObject *p) { 
    unsigned CL_INT self = (unsigned CL_INT)aint;
    CL_INT v = 0; for(;v < sizeof(CL_INT);v++) {;
    CL_INT offset = v << 3;
    unsigned char c = (unsigned char)((self & (0xFF << offset)) >> offset);
    p->put((char)c);};
    POP_SIGNAL;}
  


// The c++ function for: putc(i:integer,p:port) [0]
CL_EXPORT void  putc_integer1(CL_INT i,PortObject *p) { 
    unsigned char c = i;p->put((char)c);
    POP_SIGNAL;}
  


// *********************************************************************
// *   Part 2: serialize                                               *
// *********************************************************************
// The c++ function for: newOid(self:any,tag:integer,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT CL_INT  newOid_any1(OID self,int tag,PortObject *p,serialize_context *ctx) { 
    
    GC_BIND;
    _void_(ctx->currentOid = ((CL_INT)ctx->currentOid+(CL_INT)1));
    putc_integer1(tag,p);
    ibserialize_integer1(ctx->currentOid,p,ctx);
    GC_OBJECT(list,ctx->alreadySerialized)->addFast((OID)self);
    { CL_INT Result = 0;
      Result = ctx->currentOid;
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: shouldSerialize?(self:any,tag:integer,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireBoolean * shouldSerialize_ask_any1(OID self,int tag,PortObject *p,serialize_context *ctx) { 
    { ClaireBoolean *Result ;
      { CL_INT  z = nth_serialize_context1(ctx,self);
        if ((CL_INT)z > (CL_INT)0)
         { putc_integer1(34,p);
          ibserialize_integer1(z,p,ctx);
          if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
           mtformat_module1(Serialize.it,((char*)"~S pop oid ~S --> \n"),5,list::alloc(2,self,((OID)z)));
          else ;Result = CFALSE;
          }
        else { newOid_any1(self,tag,p,ctx);
            if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
             mtformat_module1(Serialize.it,((char*)"~S push oid ~S <-- \n"),5,list::alloc(2,self,((OID)ctx->currentOid)));
            else ;Result = CTRUE;
            }
          }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: ibserialize_prop(self:object,prop:property,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_prop_object1(ClaireObject *self,property *prop,PortObject *p,serialize_context *ctx) { 
    
    GC_BIND;
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@slot(~S) <-- \n"),5,list::alloc(1,GC_OID(_oid_(_at_property1(prop,OWNER(_oid_(self)))))));
    else ;ibserialize_symbol1(prop->name,p,ctx);
    { OID  val = GC_OID(get_property(prop,self));
      if (val != CNULL)
       { if (boolean_I_any(_oid_(prop->multivalued_ask)) == CTRUE)
         { bag * x;
          { { list * i_out = list::empty(Kernel.emptySet);
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(i);
                bag *i_support;
                i_support = GC_OBJECT(bag,enumerate_any(val));
                for (START(i_support); NEXT(i);)
                { ClaireBoolean * g0317I;
                  { ClaireBoolean *v_or;
                    { v_or = not_any(_oid_(ctx->toplevel_only_ask));
                      if (v_or == CTRUE) g0317I =CTRUE; 
                      else { v_or = ctx->toplevel_ask;
                        if (v_or == CTRUE) g0317I =CTRUE; 
                        else { { ClaireClass * z = OWNER(i);
                            v_or = contain_ask_set(OBJECT(set,Serialize.TEST_SET->value),_oid_(z));
                            }
                          if (v_or == CTRUE) g0317I =CTRUE; 
                          else { v_or = contain_ask_list(ctx->toSerialize_ask,i);
                            if (v_or == CTRUE) g0317I =CTRUE; 
                            else g0317I = CFALSE;}
                          }
                        }
                      }
                    }
                  
                  if (g0317I == CTRUE) i_out->addFast((OID)i);
                    }
                }
              x = GC_OBJECT(list,i_out);
              }
            GC_OBJECT(list,x);}
          if (Kernel._set == OWNER(val))
           x= (GC_OBJECT(set,OBJECT(bag,(*Kernel.set_I)(_oid_(x)))));
          x= (GC_OBJECT(bag,OBJECT(bag,(*Kernel.cast_I)(_oid_(x),
            GC_OID((*Kernel.of)(val))))));
          ibserialize_bag1(x,p,ctx);
          }
        else (*Serialize.ibserialize)(val,
            _oid_(p),
            _oid_(ctx));
          }
      else putc_integer1(10,p);
        }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:object,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_object2(ClaireObject *self,PortObject *p,serialize_context *ctx) { 
    
    GC_BIND;
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@object(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;{ CL_INT  z = nth_serialize_context1(ctx,_oid_(self));
      if ((CL_INT)z > (CL_INT)0)
       { putc_integer1(34,p);
        if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
         mtformat_module1(Serialize.it,((char*)"~S pop oid ~S --> \n"),5,list::alloc(2,_oid_(self),((OID)z)));
        else ;ibserialize_integer1(z,p,ctx);
        }
      else if ((ctx->toplevel_only_ask != CTRUE) || 
          ((ctx->toplevel_ask == CTRUE) || 
            (contain_ask_list(ctx->toSerialize_ask,_oid_(self)) == CTRUE)))
       { ClaireBoolean * top_ask = ctx->toplevel_ask;
        ClaireClass * own = OWNER(_oid_(self));
        _void_(ctx->toplevel_ask = CFALSE);
        newOid_any1(_oid_(self),13,p,ctx);
        if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
         mtformat_module1(Serialize.it,((char*)"~S push oid ~S <-- \n"),5,list::alloc(2,_oid_(self),((OID)ctx->currentOid)));
        else ;ibserialize_class1(own,p,ctx);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(prop);
          bag *prop_support;
          { set * s_bag = set::empty(Kernel.emptySet);
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(s);
              for (START(own->slots); NEXT(s);)
              if (s != _oid_(_at_property1(Kernel.isa,Kernel._object)))
               s_bag->addFast((OID)_oid_(OBJECT(restriction,s)->selector));
              }
            prop_support = GC_OBJECT(set,s_bag);
            }
          for (START(prop_support); NEXT(prop);)
          if ((((INHERIT(owner_any(get_property(OBJECT(property,prop),self)),Kernel._function)) || 
              (INHERIT(owner_any(get_property(OBJECT(property,prop),self)),Kernel._unbound_symbol))) ? CTRUE : ((INHERIT(owner_any(get_property(OBJECT(property,prop),self)),Kernel._environment)) ? CTRUE : CFALSE)) != CTRUE)
           ibserialize_prop_object1(self,OBJECT(property,prop),p,ctx);
          }
        putc_integer1(14,p);
        _void_(ctx->toplevel_ask = top_ask);
        }
      else putc_integer1(10,p);
        }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:thing,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_thing1(thing *self,PortObject *p,serialize_context *ctx) { 
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@thing(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;if (shouldSerialize_ask_any1(_oid_(self),15,p,ctx) == CTRUE)
     ibserialize_symbol1(self->name,p,ctx);
    POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:module,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_module1(module *self,PortObject *p,serialize_context *ctx) { 
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@module(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;if (shouldSerialize_ask_any1(_oid_(self),8,p,ctx) == CTRUE)
     ibserialize_string1(self->name->name,p,ctx);
    POP_SIGNAL;}
  


//
// The c++ function for: ibserialize(self:symbol,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_symbol1(symbol *self,PortObject *p,serialize_context *ctx) { 
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@symbol(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;if (shouldSerialize_ask_any1(_oid_(self),12,p,ctx) == CTRUE)
     { ibserialize_module1(self->module_I,p,ctx);
      ibserialize_string1(self->name,p,ctx);
      }
    POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:class,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_class1(ClaireClass *self,PortObject *p,serialize_context *ctx) { 
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@class(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;if (shouldSerialize_ask_any1(_oid_(self),2,p,ctx) == CTRUE)
     ibserialize_symbol1(self->name,p,ctx);
    POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:table,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_table1(table *self,PortObject *p,serialize_context *ctx) { 
    
    GC_BIND;
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@table(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;GC_OBJECT(list,ctx->toSerialize_ask)->addFast((OID)_oid_(self));
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(x);
      bag *x_support;
      x_support = GC_OBJECT(bag,self->graph);
      for (START(x_support); NEXT(x);)
      { GC_LOOP;
        if (x != CNULL)
         GC_OBJECT(list,ctx->toSerialize_ask)->addFast((OID)x);
        GC_UNLOOP; POP_SIGNAL;}
      }
    ibserialize_object2(self,p,ctx);
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:system_thing,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_system_thing1(SystemThing *self,PortObject *p,serialize_context *ctx) { 
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@system_thing(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;if (shouldSerialize_ask_any1(_oid_(self),37,p,ctx) == CTRUE)
     ibserialize_symbol1(self->name,p,ctx);
    POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:bag,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_bag1(bag *self,PortObject *p,serialize_context *ctx) { 
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@bag(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;newOid_any1(_oid_(self),18,p,ctx);
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"~S push bag oid ~S <-- \n"),5,list::alloc(2,_oid_(self),((OID)ctx->currentOid)));
    else ;{ CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(i);
      for (START(self); NEXT(i);)
      if (i != CNULL)
       (*Serialize.ibserialize)(i,
        _oid_(p),
        _oid_(ctx));
      else putc_integer1(10,p);
        }
    if (INHERIT(self->isa,Kernel._list))
     { if (equal(_oid_(of_bag(self)),_oid_(Kernel.emptySet)) == CTRUE)
       putc_integer1(19,p);
      else { putc_integer1(22,p);
          (*Serialize.ibserialize)(_oid_(of_bag(self)),
            _oid_(p),
            _oid_(ctx));
          }
        }
    else if (Kernel._set == self->isa)
     { if (equal(_oid_(of_bag(self)),_oid_(Kernel.emptySet)) == CTRUE)
       putc_integer1(20,p);
      else { putc_integer1(23,p);
          (*Serialize.ibserialize)(_oid_(of_bag(self)),
            _oid_(p),
            _oid_(ctx));
          }
        }
    else if (INHERIT(self->isa,Kernel._tuple))
     putc_integer1(21,p);
    POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:array,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_array1(OID *self,PortObject *p,serialize_context *ctx) { 
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@array(~S) \n"),5,list::alloc(1,_array_(self)));
    else ;if (shouldSerialize_ask_any1(_array_(self),25,p,ctx) == CTRUE)
     { { CL_INT  i = 1;
        CL_INT  g0320 = self[0];
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)i <= (CL_INT)g0320))
          { { OID  x = nth_array(self,i);
              if (x != CNULL)
               (*Serialize.ibserialize)(x,
                _oid_(p),
                _oid_(ctx));
              else putc_integer1(10,p);
                }
            ++i;
            POP_SIGNAL;}
          }
        }
      if (equal(_oid_(of_array(self)),_oid_(Kernel.emptySet)) == CTRUE)
       putc_integer1(26,p);
      else { putc_integer1(27,p);
          (*Serialize.ibserialize)(_oid_(of_array(self)),
            _oid_(p),
            _oid_(ctx));
          }
        }
    POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:restriction,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_restriction1(restriction *self,PortObject *p,serialize_context *ctx) { 
    
    GC_BIND;
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@restriction(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;GC_OBJECT(list,ctx->toSerialize_ask)->addFast((OID)_oid_(self));
    ibserialize_object2(self,p,ctx);
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:collection,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_collection1(ClaireCollection *self,PortObject *p,serialize_context *ctx) { 
    
    GC_BIND;
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@collection(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;GC_OBJECT(list,ctx->toSerialize_ask)->addFast((OID)_oid_(self));
    ibserialize_object2(self,p,ctx);
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:exception,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_exception1(ClaireException *self,PortObject *p,serialize_context *ctx) { 
    
    GC_BIND;
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@exception(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;GC_OBJECT(list,ctx->toSerialize_ask)->addFast((OID)_oid_(self));
    ibserialize_object2(self,p,ctx);
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:global_variable,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_global_variable1(global_variable *self,PortObject *p,serialize_context *ctx) { 
    
    GC_BIND;
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@global_variable(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;if (shouldSerialize_ask_any1(_oid_(self),24,p,ctx) == CTRUE)
     { ibserialize_symbol1(self->name,p,ctx);
      (*Serialize.ibserialize)(_oid_(self->range),
        _oid_(p),
        _oid_(ctx));
      (*Serialize.ibserialize)(GC_OID(self->value),
        _oid_(p),
        _oid_(ctx));
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:boolean,p:port,ctx:serialize_context) [NEW_ALLOC]
CL_EXPORT void  ibserialize_boolean1(ClaireBoolean *self,PortObject *p,serialize_context *ctx) { 
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@boolean(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;if (self == CTRUE)
     putc_integer1(4,p);
    else putc_integer1(5,p);
      POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:integer,p:port,ctx:serialize_context) [NEW_ALLOC]
CL_EXPORT void  ibserialize_integer1(CL_INT self,PortObject *p,serialize_context *ctx) { 
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@integer(~S) \n"),5,list::alloc(1,((OID)self)));
    else ;if (((CL_INT)self < (CL_INT)256) && 
        ((CL_INT)self > (CL_INT)-256))
     { if ((CL_INT)self > (CL_INT)0)
       { putc_integer1(28,p);
        unsigned char c = self;p->put((char)c);
        }
      else { putc_integer1(29,p);
          char c = -self;p->put((char)c);
          }
        }
    else { putc_integer1(30,p);
        puti_integer1(self,p);
        }
      POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:string,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  ibserialize_string1(char *self,PortObject *p,serialize_context *ctx) { 
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize(~S) \n"),5,list::alloc(1,_string_(self)));
    else ;putc_integer1(6,p);
    ibserialize_integer1(LENGTH_STRING(self),p,ctx);
    princ_string(self);
    POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:char,p:port,ctx:serialize_context) [NEW_ALLOC]
CL_EXPORT void  ibserialize_char1(ClaireChar *self,PortObject *p,serialize_context *ctx) { 
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;putc_integer1(7,p);
    putc_char1(self,p);
    POP_SIGNAL;}
  


// The c++ function for: ibserialize(g0324:any,g0325:port,g0326:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_float1_(OID g0324,PortObject *g0325,serialize_context *g0326) { 
    ibserialize_float1(float_v(g0324),g0325,g0326);
}


// The c++ function for: ibserialize(self:float,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_float1(double self,PortObject *p,serialize_context *ctx) { 
      
    GC_BIND;
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize(~S) \n"),5,list::alloc(1,GC_OID(_float_(self))));
    else ;putc_integer1(9,p);
    static char buf[256];
    sprintf(buf,"%.20f",self);
    ibserialize_string1((char *)(buf),p,ctx);
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:any,p:port,ctx:serialize_context) [NEW_ALLOC]
CL_EXPORT void  ibserialize_any1(OID self,PortObject *p,serialize_context *ctx) { 
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@any(~S) \n"),5,list::alloc(1,self));
    else ;putc_integer1(10,p);
    POP_SIGNAL;}
  


//<sb> i.e. put unknown
// The c++ function for: ibserialize(self:system_object,p:port,ctx:serialize_context) [NEW_ALLOC+SAFE_RESULT]
CL_EXPORT void  ibserialize_system_object1(SystemObject *self,PortObject *p,serialize_context *ctx) { 
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@system_object(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"serialization of system_object (~S) unsupported")),
      _oid_(list::alloc(1,_oid_(self))))));
    POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:blob,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_blob1(blob *self,PortObject *p,serialize_context *ctx) { 
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@blob(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;if (shouldSerialize_ask_any1(_oid_(self),39,p,ctx) == CTRUE)
     { CL_INT  idx = get_index_blob1(self);
      set_index_blob1(self,0);
      ibserialize_integer1(length_blob1(self),p,ctx);
      freadwrite_port3(self,p);
      set_index_blob1(self,idx);
      }
    POP_SIGNAL;}
  


// The c++ function for: ibserialize(self:clob,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  ibserialize_clob1(clob *self,PortObject *p,serialize_context *ctx) { 
    if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
     mtformat_module1(Serialize.it,((char*)"ibserialize@clob(~S) \n"),5,list::alloc(1,_oid_(self)));
    else ;if (shouldSerialize_ask_any1(_oid_(self),40,p,ctx) == CTRUE)
     { CL_INT  idx = get_index_blob1(self);
      set_index_blob1(self,0);
      ibserialize_integer1(length_blob1(self),p,ctx);
      freadwrite_port3(self,p);
      set_index_blob1(self,idx);
      }
    POP_SIGNAL;}
  


//(interface(ibserialize))
// *********************************************************************
// *   Part 3: unserialize                                             *
// *********************************************************************
// The c++ function for: bunint(p:port) [0]
CL_EXPORT CL_INT  bunint_port1(PortObject *p) { 
    { CL_INT Result = 0;
      { CL_INT  i = 0;
        CL_INT v = 0; for(;v < sizeof(CL_INT);v++) {;
        unsigned char c = p->get();
        i |= (CL_INT)((CL_INT)c << (v << 3));};
        Result = i;
        }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: bunid(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT CL_INT  bunid_port1(PortObject *p,unserialize_context *ctx) { 
    
    GC_BIND;
    { CL_INT Result = 0;
      { CL_INT  oid;
        { OID  x = GC_OID(ibunserialize_port1(p,ctx));
          if (inherit_ask_class(OWNER(x),Kernel._integer) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunid read ~S instead of an integer")),
            _oid_(list::alloc(1,x)))));
          oid = ((CL_INT)x);
          }
        if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
         mtformat_module1(Serialize.it,((char*)"bunid ~S \n"),5,list::alloc(1,((OID)oid)));
        else ;{ OID  x = nth_table1(ctx->unserialized,((OID)oid));
          if (x != CNULL)
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunid, oid ~S is already known!?")),
            _oid_(list::alloc(1,((OID)oid))))));
          else ;}
        Result = oid;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: bunoid(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  bunoid_port1(PortObject *p,unserialize_context *ctx) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT  oid;
        { OID  x = GC_OID(ibunserialize_port1(p,ctx));
          if (inherit_ask_class(OWNER(x),Kernel._integer) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunoid read ~S instead of an integer")),
            _oid_(list::alloc(1,x)))));
          oid = ((CL_INT)x);
          }
        if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
         mtformat_module1(Serialize.it,((char*)"bunoid ~S \n"),5,list::alloc(1,((OID)oid)));
        else ;{ OID  x = nth_table1(ctx->unserialized,((OID)oid));
          if (x != CNULL)
           Result = x;
          else { OID  V_CL0327;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunoid ~S is an invalid oid!?")),
                _oid_(list::alloc(1,((OID)oid))))));
              
              Result=_void_(V_CL0327);}
            }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: bunmodule(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT module * bunmodule_port1(PortObject *p,unserialize_context *ctx) { 
    
    GC_BIND;
    { module *Result ;
      { CL_INT  oid = bunid_port1(p,ctx);
        char * n;
        { { OID  x = GC_OID(ibunserialize_port1(p,ctx));
            if (equal(_oid_(Kernel._string),_oid_(OWNER(x))) != CTRUE)
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunmodule read ~S instead of a string")),
              _oid_(list::alloc(1,x)))));
            n = string_v(x);
            }
          GC_STRING(n);}
        OID  mod = value_string(n);
        if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
         mtformat_module1(Serialize.it,((char*)"bunmodule ~S \n"),5,list::alloc(1,mod));
        else ;if (inherit_ask_class(OWNER(mod),Kernel._module) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunmodule expected a module instead of ~S")),
          _oid_(list::alloc(1,mod)))));
        nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),mod);
        Result = OBJECT(module,mod);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: bunstring(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT char * bunstring_port1(PortObject *p,unserialize_context *ctx) { 
    
    GC_BIND;
    { char *Result ;
      { PortObject * tmp = GC_OBJECT(PortObject,OBJECT(PortObject,Serialize.TMP->value));
        CL_INT  len;
        { OID  x = GC_OID(ibunserialize_port1(p,ctx));
          if (inherit_ask_class(OWNER(x),Kernel._integer) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunstring expected an integer instead of ~S")),
            _oid_(list::alloc(1,x)))));
          len = ((CL_INT)x);
          }
        set_length_blob1(((blob *) tmp),0);
        while(len--) {;
        if ((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))))) == CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunstring encountered premature eof")),
          _oid_(Kernel.nil))));
        char c = p->get(); tmp->put(c);};
        { char * s = GC_STRING(string_I_blob1(((blob *) tmp)));
          if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
           mtformat_module1(Serialize.it,((char*)"bunstring ~S \n"),5,list::alloc(1,_string_(s)));
          else ;Result = s;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: bunsymbol(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT]
CL_EXPORT symbol * bunsymbol_port1(PortObject *p,unserialize_context *ctx) { 
    
    GC_BIND;
    { symbol *Result ;
      { CL_INT  oid = bunid_port1(p,ctx);
        OID  mod = GC_OID(ibunserialize_port1(p,ctx));
        if (inherit_ask_class(OWNER(mod),Kernel._module) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunsymbol expected a module instead of ~S")),
          _oid_(list::alloc(1,mod)))));
        { module * m = OBJECT(module,mod);
          symbol * res = claire.it->name;
          char * n;
          { { OID  x = GC_OID(ibunserialize_port1(p,ctx));
              if (equal(_oid_(Kernel._string),_oid_(OWNER(x))) != CTRUE)
               close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunsymbol read ~S instead of a string")),
                _oid_(list::alloc(1,x)))));
              n = string_v(x);
              }
            GC_STRING(n);}
          { OID  sy = get_symbol_module(m,n);
            if (sy != CNULL)
             res= (OBJECT(symbol,sy));
            else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunsymbol error, ~S/~A is an undefined symbol")),
                _oid_(list::alloc(2,mod,_string_(n))))));
              }
          nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),_oid_(res));
          if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
           mtformat_module1(Serialize.it,((char*)"bunsymbol ~S \n"),5,list::alloc(1,_oid_(res)));
          else ;Result = res;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//
// The c++ function for: bunbagarray(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  bunbagarray_port1(PortObject *p,unserialize_context *ctx) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { OID Result = 0;
      { list * l = list::empty(Kernel._any);
        CL_INT  oid = bunid_port1(p,ctx);
        OID  res;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          res= _oid_(CFALSE);
          while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))) != Kernel.ctrue))
          { GC_LOOP;
            { OID  x = GC_OID(ibunserialize_port1(p,ctx));
              if (x == _oid_(Serialize.breakTypedList))
               { GC_UNLOOP;res = _oid_(cast_I_list1(l,OBJECT(ClaireType,ibunserialize_port1(p,ctx))));
                ClEnv->cHandle = loop_handle;break;}
              else if (x == _oid_(Serialize.breakList))
               { GC_UNLOOP;res = _oid_(cast_I_list1(l,Kernel.emptySet));
                ClEnv->cHandle = loop_handle;break;}
              else if (x == _oid_(Serialize.breakTypedSet))
               { GC_UNLOOP;res = _oid_(cast_I_set1(GC_OBJECT(set,set_I_bag(l)),GC_OBJECT(ClaireType,OBJECT(ClaireType,ibunserialize_port1(p,ctx)))));
                ClEnv->cHandle = loop_handle;break;}
              else if (x == _oid_(Serialize.breakSet))
               { GC_UNLOOP;res = _oid_(cast_I_set1(set_I_bag(l),Kernel.emptySet));
                ClEnv->cHandle = loop_handle;break;}
              else if (x == _oid_(Serialize.breakTypedArray))
               { GC_UNLOOP;res = _array_(array_I_list(GC_OBJECT(list,cast_I_list1(l,OBJECT(ClaireType,ibunserialize_port1(p,ctx))))));
                ClEnv->cHandle = loop_handle;break;}
              else if (x == _oid_(Serialize.breakArray))
               { GC_UNLOOP;res = _array_(array_I_list(cast_I_list1(l,Kernel.emptySet)));
                ClEnv->cHandle = loop_handle;break;}
              else if (x == _oid_(Serialize.breakTuple))
               { GC_UNLOOP;res = _oid_(tuple_I_list(l));
                ClEnv->cHandle = loop_handle;break;}
              else GC__ANY(l = l->addFast((OID)x), 1);
                }
            GC_UNLOOP;POP_SIGNAL;}
          }
        nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),res);
        if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
         mtformat_module1(Serialize.it,((char*)"bunbagarray ~S \n"),5,GC_OBJECT(list,list::alloc(1,res)));
        else ;Result = res;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: bunobject(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT ClaireObject * bunobject_port1(PortObject *p,unserialize_context *ctx) { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    { ClaireObject *Result ;
      { OID  s = CNULL;
        OID  val = CNULL;
        CL_INT  oid = bunid_port1(p,ctx);
        OID  c = GC_OID(ibunserialize_port1(p,ctx));
        CL_INT  i = 0;
        ClaireObject * obj;
        { { if (inherit_ask_class(OWNER(c),Kernel._class) != CTRUE)
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunobject expected a class instead of ~S")),
              _oid_(list::alloc(1,c)))));
            obj = new_object_class(OBJECT(ClaireClass,c));
            }
          GC_OBJECT(ClaireObject,obj);}
        nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),_oid_(obj));
        if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
         mtformat_module1(Serialize.it,((char*)"==== bunobject of class ~S \n"),5,list::alloc(1,c));
        else ;{ CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))) != Kernel.ctrue))
          { GC_LOOP;
            GC__OID(s = ibunserialize_port1(p,ctx), 1);
            if (s == _oid_(Serialize.breakObject))
             { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
            if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
             mtformat_module1(Serialize.it,((char*)"bunslot ~S @ <~S> \n"),5,list::alloc(2,s,_oid_(OWNER(_oid_(obj)))));
            else ;if (inherit_ask_class(OWNER(s),Kernel._symbol) != CTRUE)
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunobject expected a valid symbol instead of ~S (class ~S)")),
              _oid_(list::alloc(2,s,c)))));
            s= (get_symbol(OBJECT(symbol,s)));
            if (inherit_ask_class(OWNER(s),Kernel._property) != CTRUE)
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunobject expected a property instead of ~S (class ~S)")),
              _oid_(list::alloc(2,s,c)))));
            GC__OID(val = ibunserialize_port1(p,ctx), 2);
            if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
             mtformat_module1(Serialize.it,((char*)"bunslotval ~S @ <~S> <--- ~S \n"),5,list::alloc(3,s,
              _oid_(OWNER(_oid_(obj))),
              val));
            else ;{ ClaireObject * sl = GC_OBJECT(ClaireObject,_at_property1(OBJECT(property,s),OBJECT(ClaireClass,c)));
              if ((equal((*Kernel.DEFAULT)(_oid_(sl)),val) != CTRUE) && 
                  (belong_to(val,(*Kernel.range)(_oid_(sl))) != CTRUE))
               close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunobject type error, can't put ~S in ~S @ ~S of range ~S")),
                _oid_(list::alloc(4,val,
                  s,
                  c,
                  GC_OID((*Kernel.range)(_oid_(sl))))))));
              }
            if ((inherit_ask_class(OWNER(val),Kernel._port) != CTRUE) || 
                (INHERIT(OWNER(val),Core._blob)))
             put_property2(OBJECT(property,s),obj,val);
            GC_UNLOOP;POP_SIGNAL;}
          }
        if (s != _oid_(Serialize.breakObject))
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunobject encountered premature eof")),
          _oid_(Kernel.nil))));
        if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
         mtformat_module1(Serialize.it,((char*)"==== bunobject call complete! on <~S> \n"),5,GC_OBJECT(list,list::alloc(1,_oid_(OWNER(_oid_(obj))))));
        else ;if (((*Kernel.open)(c) != ((OID)ClEnv->ephemeral)) && 
            (contain_ask_list(OBJECT(ClaireClass,c)->instances,_oid_(obj)) != CTRUE))
         add_property(Kernel.instances,OBJECT(ClaireObject,c),_oid_(obj));
        Result = complete_I_object(obj);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: bunthing(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireObject * bunthing_port1(PortObject *p,unserialize_context *ctx) { 
    
    GC_BIND;
    { ClaireObject *Result ;
      { CL_INT  oid = bunid_port1(p,ctx);
        OID  nm = GC_OID(ibunserialize_port1(p,ctx));
        if (inherit_ask_class(OWNER(nm),Kernel._symbol) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunthing expected a symbol instead of ~S")),
          _oid_(list::alloc(1,nm)))));
        { OID  x = get_symbol(OBJECT(symbol,nm));
          if (inherit_ask_class(OWNER(x),Kernel._thing) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunthing expected a thing ~S instead of ~S")),
            _oid_(list::alloc(2,nm,x)))));
          nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),x);
          Result = OBJECT(ClaireObject,x);
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//
// The c++ function for: bunvar(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT global_variable * bunvar_port1(PortObject *p,unserialize_context *ctx) { 
    
    GC_BIND;
    { global_variable *Result ;
      { ClaireObject *V_CC ;
        { CL_INT  oid = bunid_port1(p,ctx);
          OID  nm = GC_OID(ibunserialize_port1(p,ctx));
          OID  r = CNULL;
          OID  val = CNULL;
          OID  res;
          { if (inherit_ask_class(OWNER(nm),Kernel._symbol) != CTRUE)
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunvar expected a symbol instead of ~S")),
              _oid_(list::alloc(1,nm)))));
            { OID  x = get_symbol(OBJECT(symbol,nm));
              if (x != CNULL)
               { nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),x);
                if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
                 mtformat_module1(Serialize.it,((char*)"bunvar existing ~S \n"),5,list::alloc(1,x));
                else ;r= (GC_OID(ibunserialize_port1(p,ctx)));
                if (equal(r,(*Kernel.range)(x)) != CTRUE)
                 close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunvar try to update ~S's range (~S) with ~S")),
                  _oid_(list::alloc(3,x,
                    GC_OID((*Kernel.range)(x)),
                    r)))));
                res = x;
                }
              else { if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
                   mtformat_module1(Serialize.it,((char*)"bunvar ~S \n"),5,list::alloc(1,nm));
                  else ;r= (GC_OID(ibunserialize_port1(p,ctx)));
                  if (inherit_ask_class(OWNER(r),Kernel._type) != CTRUE)
                   close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"bunvar range type error, ~S is not a type")),
                    _oid_(list::alloc(1,r)))));
                  { global_variable * x = ((global_variable *) new_thing_class(Core._global_variable,OBJECT(symbol,nm)));
                    store_object(x,
                      4,
                      Kernel._object,
                      r,
                      CFALSE);
                    nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),_oid_(x));
                    res = _oid_(x);
                    }
                  }
                }
            }
          val= (GC_OID(ibunserialize_port1(p,ctx)));
          _void_(OBJECT(global_variable,res)->value = val);
          if (contain_ask_list(Core._global_variable->instances,res) != CTRUE)
           add_I_property(Kernel.instances,Core._global_variable,11,res);
          V_CC = complete_I_object(OBJECT(ClaireObject,res));
          }
        Result= (global_variable *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: bunclass(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireClass * bunclass_port1(PortObject *p,unserialize_context *ctx) { 
    
    GC_BIND;
    { ClaireClass *Result ;
      { CL_INT  oid = bunid_port1(p,ctx);
        OID  symb = GC_OID(ibunserialize_port1(p,ctx));
        OID  res;
        { if (inherit_ask_class(OWNER(symb),Kernel._symbol) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~S is not a symbol!")),
            _oid_(list::alloc(1,symb)))));
          res = get_symbol(OBJECT(symbol,symb));
          }
        if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
         mtformat_module1(Serialize.it,((char*)"bunclass ~S \n"),5,list::alloc(1,res));
        else ;if (inherit_ask_class(OWNER(res),Kernel._class) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~S does not beong to class")),
          _oid_(list::alloc(1,res)))));
        nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),res);
        Result = OBJECT(ClaireClass,res);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: bunsysthing(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT SystemThing * bunsysthing_port1(PortObject *p,unserialize_context *ctx) { 
    
    GC_BIND;
    { SystemThing *Result ;
      { CL_INT  oid = bunid_port1(p,ctx);
        OID  symb = GC_OID(ibunserialize_port1(p,ctx));
        OID  res;
        { if (inherit_ask_class(OWNER(symb),Kernel._symbol) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~S is not a symbol!")),
            _oid_(list::alloc(1,symb)))));
          res = get_symbol(OBJECT(symbol,symb));
          }
        if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
         mtformat_module1(Serialize.it,((char*)"bunsysthying ~S \n"),5,list::alloc(1,res));
        else ;if (inherit_ask_class(OWNER(res),Kernel._system_thing) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~S does not belong to system_thing")),
          _oid_(list::alloc(1,res)))));
        nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),res);
        Result = OBJECT(SystemThing,res);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: buntype(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT Type * buntype_port1(PortObject *p,unserialize_context *ctx) { 
    
    GC_BIND;
    { Type *Result ;
      { CL_INT  oid = bunid_port1(p,ctx);
        OID  res = GC_OID(ibunserialize_port1(p,ctx));
        if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
         mtformat_module1(Serialize.it,((char*)"buntype ~S \n"),5,list::alloc(1,res));
        else ;if (inherit_ask_class(OWNER(res),Core._Type) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~S is not a Type!")),
          _oid_(list::alloc(1,res)))));
        nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),res);
        Result = OBJECT(Type,res);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: bunblob(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT blob * bunblob_port1(PortObject *p,unserialize_context *ctx) { 
    
    GC_BIND;
    { blob *Result ;
      { CL_INT  oid = bunid_port1(p,ctx);
        OID  sz = GC_OID(ibunserialize_port1(p,ctx));
        if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
         mtformat_module1(Serialize.it,((char*)"bunblob ~S \n"),5,list::alloc(1,sz));
        else ;if (inherit_ask_class(OWNER(sz),Kernel._integer) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~S is not a blob size, integer expected!")),
          _oid_(list::alloc(1,sz)))));
        { blob * b = GC_OBJECT(blob,blob_I_void1());
          freadwrite_port4(p,b,((CL_INT)sz));
          nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),_oid_(b));
          Result = b;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: bunclob(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT clob * bunclob_port1(PortObject *p,unserialize_context *ctx) { 
    
    GC_BIND;
    { clob *Result ;
      { CL_INT  oid = bunid_port1(p,ctx);
        OID  sz = GC_OID(ibunserialize_port1(p,ctx));
        if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
         mtformat_module1(Serialize.it,((char*)"bunclob ~S \n"),5,list::alloc(1,sz));
        else ;if (inherit_ask_class(OWNER(sz),Kernel._integer) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~S is not a blob size, integer expected!")),
          _oid_(list::alloc(1,sz)))));
        { clob * b = GC_OBJECT(clob,clob_I_void1());
          freadwrite_port4(p,b,((CL_INT)sz));
          nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),_oid_(b));
          Result = b;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: ibunserialize(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  ibunserialize_port1(PortObject *p,unserialize_context *ctx) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT  tag = (int )(p->get());
        OID  bun;
        { if (tag == 2)
           bun = _oid_(bunclass_port1(p,ctx));
          else if (tag == 4)
           bun = Kernel.ctrue;
          else if (tag == 5)
           bun = Kernel.cfalse;
          else if (tag == 6)
           bun = _string_(bunstring_port1(p,ctx));
          else if (tag == 7)
           bun = _oid_((ClaireChar *)(char_I_integer(p->get())));
          else if (tag == 8)
           bun = _oid_(bunmodule_port1(p,ctx));
          else if (tag == 9)
           { OID  x = GC_OID(ibunserialize_port1(p,ctx));
            if (equal(_oid_(Kernel._string),_oid_(OWNER(x))) != CTRUE)
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~S does not belong to string")),
              _oid_(list::alloc(1,x)))));
            bun = (*Kernel.float_I)(x);
            }
          else if (tag == 10)
           bun = CNULL;
          else if (tag == 11)
           bun = _oid_(buntype_port1(p,ctx));
          else if (tag == 12)
           bun = _oid_(bunsymbol_port1(p,ctx));
          else if (tag == 13)
           bun = _oid_(bunobject_port1(p,ctx));
          else if (tag == 14)
           bun = _oid_(Serialize.breakObject);
          else if (tag == 15)
           bun = _oid_(bunthing_port1(p,ctx));
          else if (tag == 16)
           bun = _oid_(Serialize.breakObject);
          else if ((tag == 18) || 
              (tag == 25))
           bun = (OID )bunbagarray_port1(p,ctx);
          else if (tag == 19)
           bun = _oid_(Serialize.breakList);
          else if (tag == 20)
           bun = _oid_(Serialize.breakSet);
          else if (tag == 21)
           bun = _oid_(Serialize.breakTuple);
          else if (tag == 22)
           bun = _oid_(Serialize.breakTypedList);
          else if (tag == 23)
           bun = _oid_(Serialize.breakTypedSet);
          else if (tag == 24)
           bun = _oid_(bunvar_port1(p,ctx));
          else if (tag == 26)
           bun = _oid_(Serialize.breakArray);
          else if (tag == 27)
           bun = _oid_(Serialize.breakTypedArray);
          else if (tag == 28)
           { CL_INT  i = 0;
            unsigned char c = p->get();i = (CL_INT)c;
            bun = ((OID)i);
            }
          else if (tag == 29)
           { CL_INT  i = 0;
            unsigned char c = p->get();i = (CL_INT)c;
            bun = ((OID)(-i));
            }
          else if (tag == 30)
           bun = ((OID)bunint_port1(p));
          else if (tag == 34)
           bun = bunoid_port1(p,ctx);
          else if (tag == 37)
           bun = _oid_(bunsysthing_port1(p,ctx));
          else if (tag == 39)
           bun = _oid_(bunblob_port1(p,ctx));
          else if (tag == 40)
           bun = _oid_(bunclob_port1(p,ctx));
          else { OID  V_CL0328;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"ibunserialize found an invalid tag (~S)")),
                _oid_(list::alloc(1,((OID)tag))))));
              
              bun=_void_(V_CL0328);}
            GC_OID(bun);}
        if (should_trace_ask_module1(Serialize.it,5) == CTRUE)
         mtformat_module1(Serialize.it,((char*)"bun ~S \n"),5,list::alloc(1,bun));
        else ;Result = bun;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// *********************************************************************
// *   Part 4: api                                                     *
// *********************************************************************
// @cat @xl Serialization
// @section I/O, Modules and system interface
// XL CLAIRE distribution comes with the module Serialize that provide
// generic mechanism (using CLAIRE reflection) for writing/reading CLAIRE
// data structures to/from a communication port.
// The ability to convert a data structure to a binary stream can be used for
// Inter Process Communication (IPC) to exchange objects over a network or to
// store on the hard disk a set of object that belong to a user session.
// For instance :
// \code
// b :: blob!()
// (serialize(b, 12), serialize(b, list(12)))
// (assert(unserialize(b) = 12)
// (assert(unserialize(b) = list(12))
// \/code
// The example above illustrates the simple case when the serialized data represent
// a primitive object (an integer and a list with an integer),
// sometimes we need to serialize a tree of objects having relations one to each other in
// a single step and we would like the serialize process to be recursive :
// \code
// A <: ephemeral_object()
// B <: ephemeral_object(a:A)
// 
// b :: blob!()
// (serialize(b, false, B(a = A())))
// (assert(known?(a, unserialize(b))))
// \/code
// We use a serialize restriction that take a top? flag that tell whether the
// serialization should be simple (when top? is true) or recursive (when top?
// is false). By default serialize in non-recursive :
// \code
// serialize(b, x) <=> serialize(b, false, x)
// \/code
// When used recursively, serialize will traverse the object relation such to
// serialize related objects. As such it would serialize the whole database but
// it doesn't because named objects (class, property...) are not serialized.
// When a named object is serialized we only save its symbol. It comes the
// important rule that the process that unserialize a data stream should have
// in its database all named objects referenced by the data stream (e.g. classes
// have to be defined in both serializer and unserializer process). The recursion
// rules are as follow :
// \ul
// \li primitive are simple case and always serialized
// \li tables are always serialized and a recursion is always performed for objects
// that are referenced by the table.
// \li bags and arrays are always serialized and the recursion is always done for bag's elements.
// \li for named objects only the name is serialized
// \li for any other objects the recursion is made for each slots. So does related
// objects when top? is false.
// \/ul
// Notice that an inverse relation that should exists between a unserialized object
// and the object database is built during unserialization. Also notice that
// when an object is unserialized the close constructor is called so that if you
// serialize an exception, the unserialize process will throw the error (which can
// be used as an event). Here is a sample method that applies a property with a list
// of argument (like apply) but does it in a child process. The result is transmitted
// between the child and the parent through a pipe using serialization facility :
// \code
// [fork_apply(p:property, l:list) : any ->
// 	let s := socketpair() // create a pipe
// 	in (if forker?()
// 			// parent process :
// 			(fclose(s[2]),
// 			let x := (try unserialize(s[1]) // read the result on the pipe
// 						catch any exception!()), // and catch the error if any
// 				st := (CL_INT *)forked()) // wait for child termination
// 			in (if (st[1] != WEXITED & st[3] != 0)
// 					error("fork_apply(~S, ~S) failed with ~S", p, l, st),
// 				fclose(s[1]),
// 				case x (exception close(x)),
// 				x))
// 		else
// 			// child process :
// 			(fclose(s[1]), 
// 			try serialize(s[2], apply(p, l)) // actually apply
// 			catch any serialize(s[2], exception!()),
// 			exit(0),
// 			0))]
// \/code
// When using serialize over a network one can use the same serialize_context object for
// the life time of the connection. The context object associates named objects with IDs
// and the reuse of the same context for multiple serialize operation will be more
// efficient than creating a new context for each serialized data, for instance :
// \code
// let c := client!("host.domain.com", 10000),
// 	ctx := serialize_context!()
// in (while (...)
// 		(serialize(c, ctx, ...),
// 		...))
// \/code
// @cat
// The c++ function for: serialize(p:port,self:any,selfTree:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  serialize_port1(PortObject *p,OID self,OID selfTree) { 
    
    GC_BIND;
    { PortObject * old = use_as_output_port(p);
      serialize_context * ctx;
      { { serialize_context * _CL_obj = ((serialize_context *) GC_OBJECT(serialize_context,new_object_class(Serialize._serialize_context)));
          ctx = close_serialize_context1(_CL_obj);
          }
        GC_OBJECT(serialize_context,ctx);}
      preSerialize_any1(self,ctx);
      preSerialize_any1(selfTree,ctx);
      fwrite_string2(GC_STRING(string_v(Serialize.VERSION_HEADER->value)),p);
      putc_integer1(18,p);
      putc_integer1(28,p);
      putc_integer1(0,p);
      _void_(ctx->toplevel_only_ask = CFALSE);
      (*Serialize.ibserialize)(selfTree,
        _oid_(p),
        _oid_(ctx));
      _void_(ctx->toplevel_only_ask = CTRUE);
      (*Serialize.ibserialize)(self,
        _oid_(p),
        _oid_(ctx));
      putc_integer1(19,p);
      use_as_output_port(old);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// @doc @xl Serialization
// When top? is true serialize(p,top?,self) writes on p a binary representation of
// self. When top? is false serialize(p,top?,self) writes on p the object tree
// starting at self (that is the object self and related objects). The data written
// on p can then be handle with unserialize to build back the object tree.
// The c++ function for: serialize(p:port,top?:boolean,self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT serialize_context * serialize_port2(PortObject *p,ClaireBoolean *top_ask,OID self) { 
    
    GC_BIND;
    { serialize_context *Result ;
      { PortObject * old = use_as_output_port(p);
        serialize_context * ctx;
        { { serialize_context * _CL_obj = ((serialize_context *) GC_OBJECT(serialize_context,new_object_class(Serialize._serialize_context)));
            ctx = close_serialize_context1(_CL_obj);
            }
          GC_OBJECT(serialize_context,ctx);}
        _void_(ctx->toplevel_only_ask = top_ask);
        preSerialize_any1(self,ctx);
        fwrite_string2(GC_STRING(string_v(Serialize.VERSION_HEADER->value)),p);
        (*Serialize.ibserialize)(self,
          _oid_(p),
          _oid_(ctx));
        use_as_output_port(old);
        Result = ctx;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// @doc @xl Serialization
// serialize(p, self) is equivalent to serialize(p, true, self)
// The c++ function for: serialize(p:port,self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT serialize_context * serialize_port3(PortObject *p,OID self) { 
    POP_SIGNAL; return (serialize_port2(p,CTRUE,self));}
  


// The c++ function for: serialize(p:port,ctx:serialize_context,self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT serialize_context * serialize_port4(PortObject *p,serialize_context *ctx,OID self) { 
    
    GC_BIND;
    { serialize_context *Result ;
      { PortObject * old = use_as_output_port(p);
        preSerialize_any1(self,ctx);
        fwrite_string2(GC_STRING(string_v(Serialize.VERSION_HEADER->value)),p);
        (*Serialize.ibserialize)(self,
          _oid_(p),
          _oid_(ctx));
        use_as_output_port(old);
        Result = ctx;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// @doc @xl Serialization
// unserialize(p) creates an object tree from a serialized data stream
// (as done with serialize). The calling process should have a correct reading
// environment, that is the same class definition that was used by the process
// that serialized the data.
// The c++ function for: unserialize(p:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  unserialize_port1(PortObject *p) { 
    
    GC_BIND;
    { OID Result = 0;
      { unserialize_context * ctx;
        { { unserialize_context * _CL_obj = ((unserialize_context *) GC_OBJECT(unserialize_context,new_object_class(Serialize._unserialize_context)));
            ctx = close_unserialize_context1(_CL_obj);
            }
          GC_OBJECT(unserialize_context,ctx);}
        char * ver_header = GC_STRING(fread_port4(p,2));
        if ((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))))) == CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"unserialize has encountered a premature eof")),
          _oid_(Kernel.nil))));
        if (equal(_string_(ver_header),Serialize.VERSION_HEADER->value) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Invalid version of serialized data ~A (~A expected)")),
          _oid_(list::alloc(2,_string_(ver_header),GC_OID(Serialize.VERSION_HEADER->value))))));
        Result = ibunserialize_port1(p,ctx);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: serialize_context!(_CL_obj:void) [NEW_ALLOC]
CL_EXPORT serialize_context * serialize_context_I_void1() { 
    
    GC_BIND;
    { serialize_context *Result ;
      { serialize_context * _CL_obj = ((serialize_context *) GC_OBJECT(serialize_context,new_object_class(Serialize._serialize_context)));
        Result = close_serialize_context1(_CL_obj);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: unserialize_context!(_CL_obj:void) [NEW_ALLOC]
CL_EXPORT unserialize_context * unserialize_context_I_void1() { 
    
    GC_BIND;
    { unserialize_context *Result ;
      { unserialize_context * _CL_obj = ((unserialize_context *) GC_OBJECT(unserialize_context,new_object_class(Serialize._unserialize_context)));
        Result = close_unserialize_context1(_CL_obj);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: unserialize(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  unserialize_port2(PortObject *p,unserialize_context *ctx) { 
    
    GC_BIND;
    { OID Result = 0;
      { char * ver_header = GC_STRING(fread_port4(p,2));
        if ((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))))) == CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"unserialize has encountered a premature eof")),
          _oid_(Kernel.nil))));
        if (equal(_string_(ver_header),Serialize.VERSION_HEADER->value) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Invalid version of serialized data ~A (~A expected)")),
          _oid_(list::alloc(2,_string_(ver_header),GC_OID(Serialize.VERSION_HEADER->value))))));
        Result = ibunserialize_port1(p,ctx);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//


  

extern "C" CL_EXPORT void dynLoadSerialize() 
{ Serialize.initModule("Serialize",iClaire.it,list::alloc(Kernel._module,2,_oid_(Core.it),_oid_(mClaire.it)),
    "meta",list::alloc(Kernel._string,1,_string_(((char*)"serialization"))));
    Serialize.metaLoad();
    Serialize.it->version = "v1.0.0";
    Serialize.it->comment = "Serialize";
    }
  /***** CLAIRE Compilation of file Serialize.cl 
         [version 3.5.0 / safety 5] *****/



CL_EXPORT SerializeClass Serialize;

CL_EXPORT NameSpace iClaire;
// definition of the meta-model for Serialize
  void SerializeClass::metaLoad() { 
    
    ClEnv->module_I = it;
// definition of the properties 
    
    Serialize.toplevel_ask = property::make("toplevel?",Serialize.it);
    Serialize.toplevel_only_ask = property::make("toplevel_only?",claire.it);
    Serialize.currentOid = property::make("currentOid",Serialize.it);
    Serialize.alreadySerialized = property::make("alreadySerialized",Serialize.it);
    Serialize.toSerialize_ask = property::make("toSerialize?",Serialize.it);
    Serialize.preSerialize = property::make("preSerialize",Serialize.it);
    Serialize.unserialized = property::make("unserialized",Serialize.it);
    Serialize.puti = property::make("puti",Serialize.it);
    Serialize.newOid = property::make("newOid",Serialize.it);
    Serialize.ibserialize = property::make("ibserialize",Serialize.it);
    Serialize.shouldSerialize_ask = property::make("shouldSerialize?",Serialize.it);
    Serialize.bunint = property::make("bunint",Serialize.it);
    Serialize.bunid = property::make("bunid",Serialize.it);
    Serialize.ibunserialize = property::make("ibunserialize",Serialize.it);
    Serialize.bunoid = property::make("bunoid",Serialize.it);
    Serialize.bunmodule = property::make("bunmodule",Serialize.it);
    Serialize.bunstring = property::make("bunstring",Serialize.it);
    Serialize.bunsymbol = property::make("bunsymbol",Serialize.it);
    Serialize.bunbagarray = property::make("bunbagarray",Serialize.it);
    Serialize.bunobject = property::make("bunobject",Serialize.it);
    Serialize.bunthing = property::make("bunthing",Serialize.it);
    Serialize.bunvar = property::make("bunvar",Serialize.it);
    Serialize.bunclass = property::make("bunclass",Serialize.it);
    Serialize.bunsysthing = property::make("bunsysthing",Serialize.it);
    Serialize.buntype = property::make("buntype",Serialize.it);
    Serialize.serialize = property::make("serialize",claire.it);
    Serialize.unserialize = property::make("unserialize",claire.it);
    Serialize.serialize_context_I = property::make("serialize_context!",claire.it);
    Serialize.unserialize_context_I = property::make("unserialize_context!",claire.it);
    Serialize.ibserialize_prop = property::make("ibserialize_prop",Serialize.it);
    Serialize.bunblob = property::make("bunblob",Serialize.it);
    Serialize.bunclob = property::make("bunclob",Serialize.it);
    
    // instructions from module sources 
    
    GC_BIND;
{ (Serialize._serialize_context = ClaireClass::make("serialize_context",Core._ephemeral_object,claire.it));
      CL_ADD_SLOT(Serialize._serialize_context,serialize_context,Serialize.toplevel_ask,toplevel_ask,Kernel._boolean,Kernel.ctrue);
      CL_ADD_SLOT(Serialize._serialize_context,serialize_context,Serialize.toplevel_only_ask,toplevel_only_ask,Kernel._boolean,Kernel.ctrue);
      CL_ADD_SLOT(Serialize._serialize_context,serialize_context,Serialize.currentOid,currentOid,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Serialize._serialize_context,serialize_context,Serialize.alreadySerialized,alreadySerialized,nth_class1(Kernel._list,Kernel._any),CNULL);
      CL_ADD_SLOT(Serialize._serialize_context,serialize_context,Serialize.toSerialize_ask,toSerialize_ask,nth_class1(Kernel._list,Kernel._any),CNULL);
      }
    
    Kernel.close->addMethod(list::domain(1,Serialize._serialize_context),Serialize._serialize_context,
    	RETURN_ARG,_function_(close_serialize_context1,"close_serialize_context1"));
    
    Kernel.nth->addMethod(list::domain(2,Serialize._serialize_context,Kernel._any),Kernel._integer,
    	0,_function_(nth_serialize_context1,"nth_serialize_context1"));
    
    Serialize.preSerialize->addMethod(list::domain(2,Kernel._any,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(preSerialize_any1,"preSerialize_any1"));
    
    { (Serialize._unserialize_context = ClaireClass::make("unserialize_context",Core._ephemeral_object,claire.it));
      CL_ADD_SLOT(Serialize._unserialize_context,unserialize_context,Serialize.unserialized,unserialized,nth_class2(Kernel._table,GC_OBJECT(list,list::alloc(Kernel._any,1,_oid_(Kernel.range))),GC_OBJECT(list,list::alloc(1,GC_OID(_oid_(set::alloc(1,_oid_(Kernel._any))))))),CNULL);
      }
    
    Kernel.close->addMethod(list::domain(1,Serialize._unserialize_context),Serialize._unserialize_context,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(close_unserialize_context1,"close_unserialize_context1"));
    
    Serialize.puti->addMethod(list::domain(2,Kernel._integer,Kernel._port),Kernel._void,
    	0,_function_(puti_integer1,"puti_integer1"));
    
    Core.putc->addMethod(list::domain(2,Kernel._integer,Kernel._port),Kernel._void,
    	0,_function_(putc_integer1,"putc_integer1"));
    
    Serialize.newOid->addMethod(list::domain(4,Kernel._any,
      Kernel._integer,
      Kernel._port,
      Serialize._serialize_context),Kernel._integer,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(newOid_any1,"newOid_any1"));
    
    Serialize.shouldSerialize_ask->addMethod(list::domain(4,Kernel._any,
      Kernel._integer,
      Kernel._port,
      Serialize._serialize_context),Kernel._boolean,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(shouldSerialize_ask_any1,"shouldSerialize?_any1"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Serialize.TEST_SET = (global_variable *) Core._global_variable->instantiate("TEST_SET",Serialize.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      { global_variable * g0329 = _CL_obj; 
        OID  g0330;
        { set * V_CL0331;{ GC_ANY(V_CL0331= set::empty(Kernel.emptySet));
            ((set *) V_CL0331)->addFast((OID)_oid_(Kernel._integer));
            ((set *) V_CL0331)->addFast((OID)_oid_(Kernel._string));
            ((set *) V_CL0331)->addFast((OID)_oid_(Kernel._array));
            ((set *) V_CL0331)->addFast((OID)_oid_(Kernel._collection));
            ((set *) V_CL0331)->addFast((OID)_oid_(Kernel._bag));
            ((set *) V_CL0331)->addFast((OID)_oid_(Kernel._char));
            ((set *) V_CL0331)->addFast((OID)_oid_(Kernel._table));
            ((set *) V_CL0331)->addFast((OID)_oid_(Kernel._exception));
            ((set *) V_CL0331)->addFast((OID)_oid_(Kernel._class));
            ((set *) V_CL0331)->addFast((OID)_oid_(Kernel._symbol));
            ((set *) V_CL0331)->addFast((OID)_oid_(Kernel._module));
            ((set *) V_CL0331)->addFast((OID)_oid_(Kernel._restriction));
            ((set *) V_CL0331)->addFast((OID)_oid_(Kernel._type));
            ((set *) V_CL0331)->addFast((OID)_oid_(Kernel._float));
            ((set *) V_CL0331)->addFast((OID)_oid_(Kernel._boolean));}
          
          g0330=_oid_(V_CL0331);}
        _void_(g0329->value = g0330);}
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Serialize.ibserialize_prop->addMethod(list::domain(4,Kernel._object,
      Kernel._property,
      Kernel._port,
      Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_prop_object1,"ibserialize_prop_object1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._object,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_object2,"ibserialize_object2"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._thing,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_thing1,"ibserialize_thing1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._module,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_module1,"ibserialize_module1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._symbol,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_symbol1,"ibserialize_symbol1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._class,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_class1,"ibserialize_class1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._table,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_table1,"ibserialize_table1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._system_thing,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_system_thing1,"ibserialize_system_thing1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._bag,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_bag1,"ibserialize_bag1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._array,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_array1,"ibserialize_array1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._restriction,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_restriction1,"ibserialize_restriction1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._collection,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_collection1,"ibserialize_collection1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._exception,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_exception1,"ibserialize_exception1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Core._global_variable,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_global_variable1,"ibserialize_global_variable1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._boolean,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC,_function_(ibserialize_boolean1,"ibserialize_boolean1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._integer,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC,_function_(ibserialize_integer1,"ibserialize_integer1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._string,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(ibserialize_string1,"ibserialize_string1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._char,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC,_function_(ibserialize_char1,"ibserialize_char1"));
    
    Serialize.ibserialize->addFloatMethod(list::domain(3,Kernel._float,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_float1,"ibserialize_float1"),
    _function_(ibserialize_float1_,"ibserialize_float1_"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._any,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC,_function_(ibserialize_any1,"ibserialize_any1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Kernel._system_object,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+SAFE_RESULT,_function_(ibserialize_system_object1,"ibserialize_system_object1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Core._blob,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_blob1,"ibserialize_blob1"));
    
    Serialize.ibserialize->addMethod(list::domain(3,Core._clob,Kernel._port,Serialize._serialize_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(ibserialize_clob1,"ibserialize_clob1"));
    
    (Serialize._multiValuedBreak = ClaireClass::make("multiValuedBreak",Kernel._thing,Serialize.it));
    
    { (Serialize.breakList = (Serialize_multiValuedBreak *) Serialize._multiValuedBreak->instantiate("breakList",Serialize.it));
      ;}
    
    { (Serialize.breakTypedList = (Serialize_multiValuedBreak *) Serialize._multiValuedBreak->instantiate("breakTypedList",Serialize.it));
      ;}
    
    { (Serialize.breakSet = (Serialize_multiValuedBreak *) Serialize._multiValuedBreak->instantiate("breakSet",Serialize.it));
      ;}
    
    { (Serialize.breakTypedSet = (Serialize_multiValuedBreak *) Serialize._multiValuedBreak->instantiate("breakTypedSet",Serialize.it));
      ;}
    
    { (Serialize.breakArray = (Serialize_multiValuedBreak *) Serialize._multiValuedBreak->instantiate("breakArray",Serialize.it));
      ;}
    
    { (Serialize.breakTypedArray = (Serialize_multiValuedBreak *) Serialize._multiValuedBreak->instantiate("breakTypedArray",Serialize.it));
      ;}
    
    { (Serialize.breakTuple = (Serialize_multiValuedBreak *) Serialize._multiValuedBreak->instantiate("breakTuple",Serialize.it));
      ;}
    
    { (Serialize.breakObject = (Serialize_multiValuedBreak *) Serialize._multiValuedBreak->instantiate("breakObject",Serialize.it));
      ;}
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Serialize.TMP = (global_variable *) Core._global_variable->instantiate("TMP",Serialize.it));
      _void_(_CL_obj->range = Kernel._port);
      _void_(_CL_obj->value = _oid_(blob_I_void1()));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Serialize.bunint->addMethod(list::domain(1,Kernel._port),Kernel._integer,
    	0,_function_(bunint_port1,"bunint_port1"));
    
    Serialize.bunid->addMethod(list::domain(2,Kernel._port,Serialize._unserialize_context),Kernel._integer,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(bunid_port1,"bunid_port1"));
    
    Serialize.bunoid->addMethod(list::domain(2,Kernel._port,Serialize._unserialize_context),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(bunoid_port1,"bunoid_port1"));
    
    Serialize.bunmodule->addMethod(list::domain(2,Kernel._port,Serialize._unserialize_context),Kernel._module,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(bunmodule_port1,"bunmodule_port1"));
    
    Serialize.bunstring->addMethod(list::domain(2,Kernel._port,Serialize._unserialize_context),Kernel._string,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(bunstring_port1,"bunstring_port1"));
    
    Serialize.bunsymbol->addMethod(list::domain(2,Kernel._port,Serialize._unserialize_context),Kernel._symbol,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT,_function_(bunsymbol_port1,"bunsymbol_port1"));
    
    Serialize.bunbagarray->addMethod(list::domain(2,Kernel._port,Serialize._unserialize_context),U_type(Kernel._bag,Kernel._array),
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(bunbagarray_port1,"bunbagarray_port1"));
    
    Serialize.bunobject->addMethod(list::domain(2,Kernel._port,Serialize._unserialize_context),Kernel._object,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(bunobject_port1,"bunobject_port1"));
    
    Serialize.bunthing->addMethod(list::domain(2,Kernel._port,Serialize._unserialize_context),Kernel._object,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(bunthing_port1,"bunthing_port1"));
    
    Serialize.bunvar->addMethod(list::domain(2,Kernel._port,Serialize._unserialize_context),Core._global_variable,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(bunvar_port1,"bunvar_port1"));
    
    Serialize.bunclass->addMethod(list::domain(2,Kernel._port,Serialize._unserialize_context),Kernel._class,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(bunclass_port1,"bunclass_port1"));
    
    Serialize.bunsysthing->addMethod(list::domain(2,Kernel._port,Serialize._unserialize_context),Kernel._system_thing,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(bunsysthing_port1,"bunsysthing_port1"));
    
    Serialize.buntype->addMethod(list::domain(2,Kernel._port,Serialize._unserialize_context),Core._Type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(buntype_port1,"buntype_port1"));
    
    Serialize.bunblob->addMethod(list::domain(2,Kernel._port,Serialize._unserialize_context),Core._blob,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(bunblob_port1,"bunblob_port1"));
    
    Serialize.bunclob->addMethod(list::domain(2,Kernel._port,Serialize._unserialize_context),Core._clob,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(bunclob_port1,"bunclob_port1"));
    
    Serialize.ibunserialize->addMethod(list::domain(2,Kernel._port,Serialize._unserialize_context),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(ibunserialize_port1,"ibunserialize_port1"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Serialize.VERSION_HEADER = (global_variable *) Core._global_variable->instantiate("VERSION_HEADER",Serialize.it));
      _void_(_CL_obj->range = Kernel._string);
      _void_(_CL_obj->value = _string_(((char*)"V2")));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Serialize.serialize->addMethod(list::domain(3,Kernel._port,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(serialize_port1,"serialize_port1"));
    
    Serialize.serialize->addMethod(list::domain(3,Kernel._port,Kernel._boolean,Kernel._any),Serialize._serialize_context,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(serialize_port2,"serialize_port2"));
    
    Serialize.serialize->addMethod(list::domain(2,Kernel._port,Kernel._any),Serialize._serialize_context,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(serialize_port3,"serialize_port3"));
    
    Serialize.serialize->addMethod(list::domain(3,Kernel._port,Serialize._serialize_context,Kernel._any),Serialize._serialize_context,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(serialize_port4,"serialize_port4"));
    
    Serialize.unserialize->addMethod(list::domain(1,Kernel._port),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(unserialize_port1,"unserialize_port1"));
    
    Serialize.serialize_context_I->addMethod(list::domain(1,Kernel._void),Serialize._serialize_context,
    	NEW_ALLOC,_function_(serialize_context_I_void1,"serialize_context!_void1"));
    
    Serialize.unserialize_context_I->addMethod(list::domain(1,Kernel._void),Serialize._unserialize_context,
    	NEW_ALLOC,_function_(unserialize_context_I_void1,"unserialize_context!_void1"));
    
    Serialize.unserialize->addMethod(list::domain(2,Kernel._port,Serialize._unserialize_context),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(unserialize_port2,"unserialize_port2"));
    GC_UNBIND;

    }
  
  