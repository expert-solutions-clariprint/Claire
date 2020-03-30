/***** CLAIRE Compilation of file meta/serialization.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:37 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>

//*********************************************************************
//* CLAIRE                                            Sylvain Benilan *
//* serialization.cl                                                  *
//* Copyright (C) 2000 - 2003 xl. All Rights Reserved                 *
//*********************************************************************
// This file contains general purpose (un)serialization methods
// for storage or IPC.
// It is intended to to be fast and simple, the serialization format
// is non-human readable (i.e. binary), its API is provided on port.
// Last the serialization method is intented to be endian sensitiveless
// such serialized datas are portable.
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
serialize_context * close_serialize_context1(serialize_context *self)
{ POP_SIGNAL; return (self);}


// The c++ function for: nth(self:serialize_context,x:any) [0]
int  nth_serialize_context1(serialize_context *self,OID x)
{ { CL_INT Result = 0;
    { list * l = self->alreadySerialized;
      CL_INT  i = 1;
      { ClaireBoolean * g0289I;
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
          
          g0289I=OBJECT(ClaireBoolean,V_C);}
        
        if (g0289I == CTRUE) Result = i;
          else Result = 0;
        }
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: preSerialize(self:any,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  preSerialize_any1(OID self,serialize_context *ctx)
{ GC_BIND;
  if (INHERIT(OWNER(self),Kernel._bag))
   { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
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
unserialize_context * close_unserialize_context1(unserialize_context *self)
{ (self->unserialized = make_table_type(Kernel._integer,Kernel._any,CNULL));
  POP_SIGNAL; return (self);}


// The c++ function for: puti(aint:integer,p:port) [0]
void  puti_integer1(int aint,PortObject *p)
{ unsigned CL_INT self = (unsigned CL_INT)aint;
  CL_INT v = 0; for(;v < sizeof(CL_INT);v++) {;
  CL_INT offset = v << 3;
  unsigned char c = (unsigned char)((self & (0xFF << offset)) >> offset);
  p->put((char)c);};
  POP_SIGNAL;}


// The c++ function for: putc(i:integer,p:port) [0]
void  putc_integer1(int i,PortObject *p)
{ unsigned char c = i;p->put((char)c);
  POP_SIGNAL;}


// *********************************************************************
// *   Part 2: serialize                                               *
// *********************************************************************
// The c++ function for: newOid(self:any,tag:integer,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
int  newOid_any1(OID self,int tag,PortObject *p,serialize_context *ctx)
{ GC_BIND;
  (ctx->currentOid = ((CL_INT)ctx->currentOid+(CL_INT)1));
  putc_integer1(tag,p);
  ibserialize_integer1(ctx->currentOid,p,ctx);
  GC_OBJECT(list,ctx->alreadySerialized)->addFast((OID)self);
  { CL_INT Result = 0;
    Result = ctx->currentOid;
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: shouldSerialize?(self:any,tag:integer,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE]
ClaireBoolean * shouldSerialize_ask_any1(OID self,int tag,PortObject *p,serialize_context *ctx)
{ { ClaireBoolean *Result ;
    { CL_INT  z = nth_serialize_context1(ctx,self);
      if ((CL_INT)z > 0)
       { putc_integer1(34,p);
        ibserialize_integer1(z,p,ctx);
        if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
         mtformat_module1(Serialize.it,"~S pop oid ~S --> \n",3,list::alloc(2,self,((OID)z)));
        else ;Result = CFALSE;
        }
      else { newOid_any1(self,tag,p,ctx);
          if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
           mtformat_module1(Serialize.it,"~S push oid ~S <-- \n",3,list::alloc(2,self,((OID)ctx->currentOid)));
          else ;Result = CTRUE;
          }
        }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: ibserialize_prop(self:object,prop:property,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  ibserialize_prop_object1(ClaireObject *self,property *prop,PortObject *p,serialize_context *ctx)
{ GC_BIND;
  if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@slot(~S) <-- \n",3,list::alloc(1,GC_OID(_oid_(_at_property1(prop,OWNER(_oid_(self)))))));
  else ;ibserialize_symbol1(prop->name,p,ctx);
  { OID  val = GC_OID(get_property(prop,self));
    if (val != CNULL)
     { if (boolean_I_any(_oid_(prop->multivalued_ask)) == CTRUE)
       { bag * x;
        { { list * i_out = list::empty(Kernel.emptySet);
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(i);
              bag *i_support;
              i_support = GC_OBJECT(bag,enumerate_any(val));
              for (START(i_support); NEXT(i);)
              { ClaireBoolean * g0294I;
                { ClaireBoolean *v_or;
                  { v_or = not_any(_oid_(ctx->toplevel_only_ask));
                    if (v_or == CTRUE) g0294I =CTRUE; 
                    else { v_or = ctx->toplevel_ask;
                      if (v_or == CTRUE) g0294I =CTRUE; 
                      else { { ClaireClass * z = OWNER(i);
                          v_or = contain_ask_set(OBJECT(set,Serialize.TEST_SET->value),_oid_(z));
                          }
                        if (v_or == CTRUE) g0294I =CTRUE; 
                        else { v_or = contain_ask_list(ctx->toSerialize_ask,i);
                          if (v_or == CTRUE) g0294I =CTRUE; 
                          else g0294I = CFALSE;}
                        }
                      }
                    }
                  }
                
                if (g0294I == CTRUE) i_out->addFast((OID)i);
                  }
              }
            x = GC_OBJECT(list,i_out);
            }
          GC_OBJECT(list,x);}
        if (Kernel._set == OWNER(val))
         x= GC_OBJECT(set,OBJECT(bag,(*Kernel.set_I)(_oid_(x))));
        x= GC_OBJECT(bag,OBJECT(bag,(*Kernel.cast_I)(_oid_(x),
          GC_OID((*Kernel.of)(val)))));
        ibserialize_bag1(x,p,ctx);
        }
      else (*Serialize.ibserialize)(val,
          _oid_(p),
          _oid_(ctx));
        }
    else putc_integer1(10,p);
      }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: ibserialize(self:object,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  ibserialize_object2(ClaireObject *self,PortObject *p,serialize_context *ctx)
{ GC_BIND;
  if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@object(~S) \n",3,list::alloc(1,_oid_(self)));
  else ;{ CL_INT  z = nth_serialize_context1(ctx,_oid_(self));
    if ((CL_INT)z > 0)
     { putc_integer1(34,p);
      if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
       mtformat_module1(Serialize.it,"~S pop oid ~S --> \n",3,list::alloc(2,_oid_(self),((OID)z)));
      else ;ibserialize_integer1(z,p,ctx);
      }
    else if ((ctx->toplevel_only_ask != CTRUE) || 
        ((ctx->toplevel_ask == CTRUE) || 
          (contain_ask_list(ctx->toSerialize_ask,_oid_(self)) == CTRUE)))
     { ClaireBoolean * top_ask = ctx->toplevel_ask;
      ClaireClass * own = OWNER(_oid_(self));
      (ctx->toplevel_ask = CFALSE);
      newOid_any1(_oid_(self),13,p,ctx);
      if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
       mtformat_module1(Serialize.it,"~S push oid ~S <-- \n",3,list::alloc(2,_oid_(self),((OID)ctx->currentOid)));
      else ;ibserialize_class1(own,p,ctx);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(prop);
        bag *prop_support;
        { set * s_bag = set::empty(Kernel.emptySet);
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
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
      (ctx->toplevel_ask = top_ask);
      }
    else putc_integer1(10,p);
      }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: ibserialize(self:thing,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  ibserialize_thing1(thing *self,PortObject *p,serialize_context *ctx)
{ GC_BIND;
  if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@thing(~S) \n",3,list::alloc(1,_oid_(self)));
  else ;{ CL_INT  z = nth_serialize_context1(ctx,_oid_(self));
    if ((CL_INT)z > 0)
     { putc_integer1(34,p);
      if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
       mtformat_module1(Serialize.it,"~S pop oid ~S --> \n",3,list::alloc(2,_oid_(self),((OID)z)));
      else ;ibserialize_integer1(z,p,ctx);
      }
    else if ((ctx->toplevel_only_ask != CTRUE) || 
        ((ctx->toplevel_ask == CTRUE) || 
          (ctx->toSerialize_ask->memq(_oid_(self)) == CTRUE)))
     { ClaireBoolean * top_ask = ctx->toplevel_ask;
      ClaireClass * own = OWNER(_oid_(self));
      (ctx->toplevel_ask = CFALSE);
      newOid_any1(_oid_(self),15,p,ctx);
      if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
       mtformat_module1(Serialize.it,"~S push oid ~S <-- \n",3,list::alloc(2,_oid_(self),((OID)ctx->currentOid)));
      else ;ibserialize_I_symbol1(self->name,p,ctx);
      ibserialize_class1(own,p,ctx);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(prop);
        bag *prop_support;
        { set * s_bag = set::empty(Kernel.emptySet);
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(s);
            for (START(own->slots); NEXT(s);)
            if (s != _oid_(_at_property1(Kernel.isa,Kernel._object)))
             { if (s != _oid_(_at_property1(Kernel.name,Kernel._thing)))
               s_bag->addFast((OID)_oid_(OBJECT(restriction,s)->selector));
              }
            }
          prop_support = GC_OBJECT(set,s_bag);
          }
        for (START(prop_support); NEXT(prop);)
        if ((((INHERIT(owner_any(get_property(OBJECT(property,prop),self)),Kernel._function)) || 
            (INHERIT(owner_any(get_property(OBJECT(property,prop),self)),Kernel._unbound_symbol))) ? CTRUE : ((INHERIT(owner_any(get_property(OBJECT(property,prop),self)),Kernel._environment)) ? CTRUE : CFALSE)) != CTRUE)
         ibserialize_prop_object1(self,OBJECT(property,prop),p,ctx);
        }
      putc_integer1(16,p);
      (ctx->toplevel_ask = top_ask);
      }
    else putc_integer1(10,p);
      }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: ibserialize(self:module,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  ibserialize_module1(module *self,PortObject *p,serialize_context *ctx)
{ if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@module(~S) \n",3,list::alloc(1,_oid_(self)));
  else ;if (shouldSerialize_ask_any1(_oid_(self),8,p,ctx) == CTRUE)
   ibserialize_string1(self->name->name,p,ctx);
  POP_SIGNAL;}


// The c++ function for: ibserialize!(self:symbol,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  ibserialize_I_symbol1(symbol *self,PortObject *p,serialize_context *ctx)
{ if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize!@symbol(~S) \n",3,list::alloc(1,_oid_(self)));
  else ;if (shouldSerialize_ask_any1(_oid_(self),38,p,ctx) == CTRUE)
   { ibserialize_module1(self->module_I,p,ctx);
    ibserialize_string1(self->name,p,ctx);
    }
  POP_SIGNAL;}


// The c++ function for: ibserialize(self:symbol,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  ibserialize_symbol1(symbol *self,PortObject *p,serialize_context *ctx)
{ if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@symbol(~S) \n",3,list::alloc(1,_oid_(self)));
  else ;if (shouldSerialize_ask_any1(_oid_(self),12,p,ctx) == CTRUE)
   { ibserialize_module1(self->module_I,p,ctx);
    ibserialize_string1(self->name,p,ctx);
    }
  POP_SIGNAL;}


// The c++ function for: ibserialize(self:class,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  ibserialize_class1(ClaireClass *self,PortObject *p,serialize_context *ctx)
{ if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@class(~S) \n",3,list::alloc(1,_oid_(self)));
  else ;if (shouldSerialize_ask_any1(_oid_(self),2,p,ctx) == CTRUE)
   ibserialize_symbol1(self->name,p,ctx);
  POP_SIGNAL;}


// The c++ function for: ibserialize(self:table,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  ibserialize_table1(table *self,PortObject *p,serialize_context *ctx)
{ GC_BIND;
  if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@table(~S) \n",3,list::alloc(1,_oid_(self)));
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
  ibserialize_thing1(self,p,ctx);
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: ibserialize(self:system_thing,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  ibserialize_system_thing1(SystemThing *self,PortObject *p,serialize_context *ctx)
{ if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@system_thing(~S) \n",3,list::alloc(1,_oid_(self)));
  else ;if (shouldSerialize_ask_any1(_oid_(self),37,p,ctx) == CTRUE)
   ibserialize_symbol1(self->name,p,ctx);
  POP_SIGNAL;}


// The c++ function for: ibserialize(self:bag,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  ibserialize_bag1(bag *self,PortObject *p,serialize_context *ctx)
{ if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@bag(~S) \n",3,list::alloc(1,_oid_(self)));
  else ;newOid_any1(_oid_(self),18,p,ctx);
  if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"~S push bag oid ~S <-- \n",3,list::alloc(2,_oid_(self),((OID)ctx->currentOid)));
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


// The c++ function for: ibserialize(self:array,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  ibserialize_array1(OID *self,PortObject *p,serialize_context *ctx)
{ if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@array(~S) \n",3,list::alloc(1,_array_(self)));
  else ;if (shouldSerialize_ask_any1(_array_(self),25,p,ctx) == CTRUE)
   { { CL_INT  i = 1;
      CL_INT  g0297 = self[0];
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)i <= (CL_INT)g0297))
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
void  ibserialize_restriction1(restriction *self,PortObject *p,serialize_context *ctx)
{ GC_BIND;
  if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@restriction(~S) \n",3,list::alloc(1,_oid_(self)));
  else ;GC_OBJECT(list,ctx->toSerialize_ask)->addFast((OID)_oid_(self));
  ibserialize_object2(self,p,ctx);
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: ibserialize(self:collection,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  ibserialize_collection1(ClaireCollection *self,PortObject *p,serialize_context *ctx)
{ GC_BIND;
  if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@collection(~S) \n",3,list::alloc(1,_oid_(self)));
  else ;GC_OBJECT(list,ctx->toSerialize_ask)->addFast((OID)_oid_(self));
  ibserialize_object2(self,p,ctx);
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: ibserialize(self:exception,p:port,ctx:serialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  ibserialize_exception1(ClaireException *self,PortObject *p,serialize_context *ctx)
{ GC_BIND;
  if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@exception(~S) \n",3,list::alloc(1,_oid_(self)));
  else ;GC_OBJECT(list,ctx->toSerialize_ask)->addFast((OID)_oid_(self));
  ibserialize_object2(self,p,ctx);
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: ibserialize(self:global_variable,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  ibserialize_global_variable1(global_variable *self,PortObject *p,serialize_context *ctx)
{ GC_BIND;
  if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@global_variable(~S) \n",3,list::alloc(1,_oid_(self)));
  else ;if (shouldSerialize_ask_any1(_oid_(self),24,p,ctx) == CTRUE)
   { ibserialize_I_symbol1(self->name,p,ctx);
    (*Serialize.ibserialize)(_oid_(self->range),
      _oid_(p),
      _oid_(ctx));
    (*Serialize.ibserialize)(GC_OID(self->value),
      _oid_(p),
      _oid_(ctx));
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: ibserialize(self:boolean,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE]
void  ibserialize_boolean1(ClaireBoolean *self,PortObject *p,serialize_context *ctx)
{ if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@boolean(~S) \n",3,list::alloc(1,_oid_(self)));
  else ;if (self == CTRUE)
   putc_integer1(4,p);
  else putc_integer1(5,p);
    POP_SIGNAL;}


// The c++ function for: ibserialize(self:integer,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE]
void  ibserialize_integer1(int self,PortObject *p,serialize_context *ctx)
{ if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@integer(~S) \n",3,list::alloc(1,((OID)self)));
  else ;if (((CL_INT)self < 256) && 
      ((CL_INT)self > -256))
   { if ((CL_INT)self > 0)
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


// The c++ function for: ibserialize(self:string,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE]
void  ibserialize_string1(char *self,PortObject *p,serialize_context *ctx)
{ if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize(~S) \n",3,list::alloc(1,_string_(self)));
  else ;putc_integer1(6,p);
  ibserialize_integer1(LENGTH_STRING(self),p,ctx);
  princ_string(self);
  POP_SIGNAL;}


// The c++ function for: ibserialize(self:char,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE]
void  ibserialize_char1(ClaireChar *self,PortObject *p,serialize_context *ctx)
{ if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize(~S) \n",3,list::alloc(1,_oid_(self)));
  else ;putc_integer1(7,p);
  putc_char1(self,p);
  POP_SIGNAL;}


// The c++ function for: ibserialize(g0301:any,g0302:port,g0303:serialize_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  ibserialize_float1_(OID g0301,PortObject *g0302,serialize_context *g0303)
{ ibserialize_float1(float_v(g0301),g0302,g0303);}


// The c++ function for: ibserialize(self:float,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  ibserialize_float1(double self,PortObject *p,serialize_context *ctx)
{ GC_BIND;
  if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize(~S) \n",3,list::alloc(1,GC_OID(_float_(self))));
  else ;putc_integer1(9,p);
  static char buf[256];
  sprintf(buf,"%.20f",self);
  ibserialize_string1((char *)(buf),p,ctx);
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: ibserialize(self:any,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE]
void  ibserialize_any1(OID self,PortObject *p,serialize_context *ctx)
{ if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@any(~S) \n",3,list::alloc(1,self));
  else ;putc_integer1(10,p);
  POP_SIGNAL;}


//<sb> i.e. put unknown
// The c++ function for: ibserialize(self:system_object,p:port,ctx:serialize_context) [NEW_ALLOC+SLOT_UPDATE+SAFE_RESULT]
void  ibserialize_system_object1(SystemObject *self,PortObject *p,serialize_context *ctx)
{ if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
   mtformat_module1(Serialize.it,"ibserialize@system_object(~S) \n",3,list::alloc(1,_oid_(self)));
  else ;close_exception(((general_error *) (*Core._general_error)(_string_("serialization of system_object (~S) unsupported"),
    _oid_(list::alloc(1,_oid_(self))))));
  POP_SIGNAL;}


//(interface(ibserialize))
// *********************************************************************
// *   Part 3: unserialize                                             *
// *********************************************************************
// The c++ function for: bunint(p:port) [0]
int  bunint_port1(PortObject *p)
{ { CL_INT Result = 0;
    { CL_INT  i = 0;
      CL_INT v = 0; for(;v < sizeof(CL_INT);v++) {;
      unsigned char c = p->get();
      i |= (CL_INT)((CL_INT)c << (v << 3));};
      Result = i;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: bunid(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
int  bunid_port1(PortObject *p,unserialize_context *ctx)
{ GC_BIND;
  { CL_INT Result = 0;
    { CL_INT  oid;
      { OID  x = GC_OID(ibunserialize_port1(p,ctx));
        if (inherit_ask_class(OWNER(x),Kernel._integer) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_("bunid read ~S instead of an integer"),
          _oid_(list::alloc(1,x)))));
        oid = x;
        }
      if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
       mtformat_module1(Serialize.it,"bunid ~S \n",3,list::alloc(1,((OID)oid)));
      else ;{ OID  x = nth_table1(ctx->unserialized,((OID)oid));
        if (x != CNULL)
         close_exception(((general_error *) (*Core._general_error)(_string_("bunid, oid ~S is already known!?"),
          _oid_(list::alloc(1,((OID)oid))))));
        else ;}
      Result = oid;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: bunoid(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  bunoid_port1(PortObject *p,unserialize_context *ctx)
{ GC_BIND;
  { OID Result = 0;
    { CL_INT  oid;
      { OID  x = GC_OID(ibunserialize_port1(p,ctx));
        if (inherit_ask_class(OWNER(x),Kernel._integer) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_("bunoid read ~S instead of an integer"),
          _oid_(list::alloc(1,x)))));
        oid = x;
        }
      if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
       mtformat_module1(Serialize.it,"bunoid ~S \n",3,list::alloc(1,((OID)oid)));
      else ;{ OID  x = nth_table1(ctx->unserialized,((OID)oid));
        if (x != CNULL)
         Result = x;
        else { OID  V_CL0304;close_exception(((general_error *) (*Core._general_error)(_string_("bunoid ~S is an invalid oid!?"),
              _oid_(list::alloc(1,((OID)oid))))));
            
            Result=_void_(V_CL0304);}
          }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: bunmodule(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
module * bunmodule_port1(PortObject *p,unserialize_context *ctx)
{ GC_BIND;
  { module *Result ;
    { CL_INT  oid = bunid_port1(p,ctx);
      char * n;
      { { OID  x = GC_OID(ibunserialize_port1(p,ctx));
          if (equal(_oid_(Kernel._string),_oid_(OWNER(x))) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_("bunmodule read ~S instead of a string"),
            _oid_(list::alloc(1,x)))));
          n = string_v(x);
          }
        GC_STRING(n);}
      OID  mod = value_string(n);
      if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
       mtformat_module1(Serialize.it,"bunmodule ~S \n",3,list::alloc(1,mod));
      else ;if (inherit_ask_class(OWNER(mod),Kernel._module) != CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("bunmodule expected a module instead of ~S"),
        _oid_(list::alloc(1,mod)))));
      nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),mod);
      Result = OBJECT(module,mod);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: bunstring(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
char * bunstring_port1(PortObject *p,unserialize_context *ctx)
{ GC_BIND;
  { char *Result ;
    { PortObject * tmp = GC_OBJECT(PortObject,OBJECT(PortObject,Serialize.TMP->value));
      CL_INT  len;
      { OID  x = GC_OID(ibunserialize_port1(p,ctx));
        if (inherit_ask_class(OWNER(x),Kernel._integer) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_("bunstring expected an integer instead of ~S"),
          _oid_(list::alloc(1,x)))));
        len = x;
        }
      set_length_blob1(((blob *) tmp),0);
      while(len--) {;
      if ((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))))) == CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("bunstring encountered premature eof"),
        _oid_(Kernel.nil))));
      char c = p->get(); tmp->put(c);};
      { char * s = GC_STRING(string_I_blob1(((blob *) tmp)));
        if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
         mtformat_module1(Serialize.it,"bunstring ~S \n",3,list::alloc(1,_string_(s)));
        else ;Result = s;
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: bunsymbol(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT]
symbol * bunsymbol_port1(PortObject *p,unserialize_context *ctx)
{ GC_BIND;
  { symbol *Result ;
    { CL_INT  oid = bunid_port1(p,ctx);
      OID  mod = GC_OID(ibunserialize_port1(p,ctx));
      if (inherit_ask_class(OWNER(mod),Kernel._module) != CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("bunsymbol expected a module instead of ~S"),
        _oid_(list::alloc(1,mod)))));
      { module * m = OBJECT(module,mod);
        symbol * res = claire.it->name;
        char * n;
        { { OID  x = GC_OID(ibunserialize_port1(p,ctx));
            if (equal(_oid_(Kernel._string),_oid_(OWNER(x))) != CTRUE)
             close_exception(((general_error *) (*Core._general_error)(_string_("bunsymbol read ~S instead of a string"),
              _oid_(list::alloc(1,x)))));
            n = string_v(x);
            }
          GC_STRING(n);}
        { OID  sy = get_symbol_module(m,n);
          if (sy != CNULL)
           res= OBJECT(symbol,sy);
          else close_exception(((general_error *) (*Core._general_error)(_string_("bunsymbol error, ~S/~A is an undefined symbol"),
              _oid_(list::alloc(2,mod,_string_(n))))));
            }
        nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),_oid_(res));
        if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
         mtformat_module1(Serialize.it,"bunsymbol ~S \n",3,list::alloc(1,_oid_(res)));
        else ;Result = res;
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: bunsymbol!(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT]
symbol * bunsymbol_I_port1(PortObject *p,unserialize_context *ctx)
{ GC_BIND;
  { symbol *Result ;
    { CL_INT  oid = bunid_port1(p,ctx);
      OID  mod = GC_OID(ibunserialize_port1(p,ctx));
      if (inherit_ask_class(OWNER(mod),Kernel._module) != CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("bunsymbol! expected a module instead of ~S"),
        _oid_(list::alloc(1,mod)))));
      { module * m = OBJECT(module,mod);
        symbol * res = claire.it->name;
        char * n;
        { { OID  x = GC_OID(ibunserialize_port1(p,ctx));
            if (equal(_oid_(Kernel._string),_oid_(OWNER(x))) != CTRUE)
             close_exception(((general_error *) (*Core._general_error)(_string_("bunsymbol! read ~S instead of a string"),
              _oid_(list::alloc(1,x)))));
            n = string_v(x);
            }
          GC_STRING(n);}
        { OID  sy = get_symbol_module(m,n);
          if (sy != CNULL)
           res= OBJECT(symbol,sy);
          else res= symbol_I_string(n,m);
            }
        nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),_oid_(res));
        if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
         mtformat_module1(Serialize.it,"bunsymbol! ~S \n",3,list::alloc(1,_oid_(res)));
        else ;Result = res;
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: bunbagarray(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  bunbagarray_port1(PortObject *p,unserialize_context *ctx)
{ GC_RESERVE(6);  // v3.0.55 optim !
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
             { res = _oid_(cast_I_list1(l,OBJECT(ClaireType,ibunserialize_port1(p,ctx))));
              ClEnv->cHandle = loop_handle;break;}
            else if (x == _oid_(Serialize.breakList))
             { res = _oid_(cast_I_list1(l,Kernel.emptySet));
              ClEnv->cHandle = loop_handle;break;}
            else if (x == _oid_(Serialize.breakTypedSet))
             { res = _oid_(cast_I_set1(GC_OBJECT(set,set_I_bag(l)),GC_OBJECT(ClaireType,OBJECT(ClaireType,ibunserialize_port1(p,ctx)))));
              ClEnv->cHandle = loop_handle;break;}
            else if (x == _oid_(Serialize.breakSet))
             { res = _oid_(cast_I_set1(set_I_bag(l),Kernel.emptySet));
              ClEnv->cHandle = loop_handle;break;}
            else if (x == _oid_(Serialize.breakTypedArray))
             { res = _array_(array_I_list(GC_OBJECT(list,cast_I_list1(l,OBJECT(ClaireType,ibunserialize_port1(p,ctx))))));
              ClEnv->cHandle = loop_handle;break;}
            else if (x == _oid_(Serialize.breakArray))
             { res = _array_(array_I_list(cast_I_list1(l,Kernel.emptySet)));
              ClEnv->cHandle = loop_handle;break;}
            else if (x == _oid_(Serialize.breakTuple))
             { res = _oid_(tuple_I_list(l));
              ClEnv->cHandle = loop_handle;break;}
            else GC__ANY(l = l->addFast((OID)x), 3);
              }
          GC_UNLOOP;POP_SIGNAL;}
        }
      nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),res);
      if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
       mtformat_module1(Serialize.it,"bunbagarray ~S \n",3,GC_OBJECT(list,list::alloc(1,res)));
      else ;Result = res;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: bunobject(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
ClaireObject * bunobject_port1(PortObject *p,unserialize_context *ctx)
{ GC_RESERVE(9);  // v3.0.55 optim !
  { ClaireObject *Result ;
    { OID  s = CNULL;
      OID  val = CNULL;
      CL_INT  oid = bunid_port1(p,ctx);
      OID  c = GC_OID(ibunserialize_port1(p,ctx));
      CL_INT  i = 0;
      ClaireObject * obj;
      { { if (inherit_ask_class(OWNER(c),Kernel._class) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_("bunobject expected a class instead of ~S"),
            _oid_(list::alloc(1,c)))));
          obj = new_object_class(OBJECT(ClaireClass,c));
          }
        GC_OBJECT(ClaireObject,obj);}
      nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),_oid_(obj));
      if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
       mtformat_module1(Serialize.it,"==== bunobject of class ~S \n",3,list::alloc(1,c));
      else ;{ CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))) != Kernel.ctrue))
        { GC_LOOP;
          GC__OID(s = ibunserialize_port1(p,ctx), 3);
          if (s == _oid_(Serialize.breakObject))
           { ;ClEnv->cHandle = loop_handle; break;}
          if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
           mtformat_module1(Serialize.it,"bunslot ~S @ <~S> \n",3,list::alloc(2,s,_oid_(OWNER(_oid_(obj)))));
          else ;if (inherit_ask_class(OWNER(s),Kernel._symbol) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_("bunobject expected a valid symbol instead of ~S (class ~S)"),
            _oid_(list::alloc(2,s,c)))));
          s= get_symbol(OBJECT(symbol,s));
          if (inherit_ask_class(OWNER(s),Kernel._property) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_("bunobject expected a property instead of ~S (class ~S)"),
            _oid_(list::alloc(2,s,c)))));
          GC__OID(val = ibunserialize_port1(p,ctx), 4);
          if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
           mtformat_module1(Serialize.it,"bunslotval ~S @ <~S> <--- ~S \n",3,list::alloc(3,s,
            _oid_(OWNER(_oid_(obj))),
            val));
          else ;{ ClaireObject * sl = GC_OBJECT(ClaireObject,_at_property1(OBJECT(property,s),OBJECT(ClaireClass,c)));
            if ((equal((*Kernel.DEFAULT)(_oid_(sl)),val) != CTRUE) && 
                (belong_to(val,(*Kernel.range)(_oid_(sl))) != CTRUE))
             close_exception(((general_error *) (*Core._general_error)(_string_("bunobject type error, can't put ~S in ~S @ ~S of range ~S"),
              _oid_(list::alloc(4,val,
                s,
                c,
                GC_OID((*Kernel.range)(_oid_(sl))))))));
            }
          if (inherit_ask_class(OWNER(val),Kernel._port) != CTRUE)
           put_property2(OBJECT(property,s),obj,val);
          GC_UNLOOP;POP_SIGNAL;}
        }
      if (s != _oid_(Serialize.breakObject))
       close_exception(((general_error *) (*Core._general_error)(_string_("bunobject encountered premature eof"),
        _oid_(Kernel.nil))));
      if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
       mtformat_module1(Serialize.it,"==== bunobject call complete! on <~S> \n",3,GC_OBJECT(list,list::alloc(1,_oid_(OWNER(_oid_(obj))))));
      else ;if (((*Kernel.open)(c) != ((OID)ClEnv->ephemeral)) && 
          (contain_ask_list(OBJECT(ClaireClass,c)->instances,_oid_(obj)) != CTRUE))
       add_property(Kernel.instances,OBJECT(ClaireObject,c),_oid_(obj));
      Result = complete_I_object(obj);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: bunthing(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
ClaireObject * bunthing_port1(PortObject *p,unserialize_context *ctx)
{ GC_RESERVE(11);  // v3.0.55 optim !
  { ClaireObject *Result ;
    { OID  s = CNULL;
      OID  val = CNULL;
      CL_INT  oid = bunid_port1(p,ctx);
      OID  nm = GC_OID(ibunserialize_port1(p,ctx));
      OID  c = GC_OID(ibunserialize_port1(p,ctx));
      ClaireBoolean * unamed_ask = ((equal(nm,get_symbol_string("unamed")) == CTRUE) ? CTRUE : CFALSE);
      OID  obj;
      { if (inherit_ask_class(OWNER(c),Kernel._class) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_("bunthing expected a class instead of ~S"),
          _oid_(list::alloc(1,c)))));
        if (inherit_ask_class(OWNER(nm),Kernel._symbol) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_("bunthing expected a symbol instead of ~S"),
          _oid_(list::alloc(1,nm)))));
        { OID  x;
          if (unamed_ask == CTRUE)
           x = CNULL;
          else x = get_symbol(OBJECT(symbol,nm));
            if (x != CNULL)
           { if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
             mtformat_module1(Serialize.it,"==== bunthing existing ~S \n",3,list::alloc(1,x));
            else ;nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),x);
            if (equal(_oid_(OWNER(x)),c) != CTRUE)
             close_exception(((general_error *) (*Core._general_error)(_string_("bunthing try to update ~S:~S with an object of class ~S!"),
              _oid_(list::alloc(3,x,
                _oid_(OWNER(x)),
                c)))));
            obj = x;
            }
          else { if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
               mtformat_module1(Serialize.it,"==== bunthing new!@~S with name ~S \n",3,list::alloc(2,c,nm));
              else ;{ ClaireObject * x;
                { if (unamed_ask == CTRUE)
                   x = new_object_class(OBJECT(ClaireClass,c));
                  else x = new_thing_class(OBJECT(ClaireClass,c),OBJECT(symbol,nm));
                    GC_OBJECT(ClaireObject,x);}
                nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),_oid_(x));
                obj = _oid_(x);
                }
              }
            }
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))) != Kernel.ctrue))
        { GC_LOOP;
          GC__OID(s = ibunserialize_port1(p,ctx), 3);
          if (s == _oid_(Serialize.breakObject))
           { ;ClEnv->cHandle = loop_handle; break;}
          if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
           mtformat_module1(Serialize.it,"bunslot ~S @ <~S> \n",3,list::alloc(2,s,_oid_(OWNER(obj))));
          else ;if (inherit_ask_class(OWNER(s),Kernel._symbol) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_("bunthing expected a valid symbol instead of ~S (class ~S)"),
            _oid_(list::alloc(2,s,c)))));
          s= get_symbol(OBJECT(symbol,s));
          if (inherit_ask_class(OWNER(s),Kernel._property) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_("bunthing expected a property instead of ~S (class ~S)"),
            _oid_(list::alloc(2,s,c)))));
          GC__OID(val = ibunserialize_port1(p,ctx), 4);
          { ClaireObject * sl = GC_OBJECT(ClaireObject,_at_property1(OBJECT(property,s),OBJECT(ClaireClass,c)));
            if ((equal((*Kernel.DEFAULT)(_oid_(sl)),val) != CTRUE) && 
                (belong_to(val,(*Kernel.range)(_oid_(sl))) != CTRUE))
             close_exception(((general_error *) (*Core._general_error)(_string_("bunthing type error, can't put ~S in ~S @ ~S of range ~S)"),
              _oid_(list::alloc(4,val,
                s,
                c,
                GC_OID((*Kernel.range)(_oid_(sl))))))));
            }
          if (inherit_ask_class(OWNER(val),Kernel._port) != CTRUE)
           put_property2(OBJECT(property,s),OBJECT(ClaireObject,obj),val);
          GC_UNLOOP;POP_SIGNAL;}
        }
      if (s != _oid_(Serialize.breakObject))
       close_exception(((general_error *) (*Core._general_error)(_string_("bunthing encountered premature eof"),
        _oid_(Kernel.nil))));
      if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
       mtformat_module1(Serialize.it,"==== bunthing call complete! on <~S> \n",3,GC_OBJECT(list,list::alloc(1,_oid_(OWNER(obj)))));
      else ;if (((*Kernel.open)(c) != ((OID)ClEnv->ephemeral)) && 
          ((contain_ask_list(OBJECT(ClaireClass,c)->instances,obj) != CTRUE) && 
            (((unamed_ask == CTRUE) ? ((c == _oid_(Kernel._table)) ? CTRUE: CFALSE): CFALSE) != CTRUE)))
       add_property(Kernel.instances,OBJECT(ClaireObject,c),obj);
      Result = ((c != _oid_(Kernel._table)) ?
        complete_I_object(OBJECT(ClaireObject,obj)) :
        OBJECT(ClaireObject,obj) );
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: bunvar(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
global_variable * bunvar_port1(PortObject *p,unserialize_context *ctx)
{ GC_BIND;
  { global_variable *Result ;
    { ClaireObject *V_CC ;
      { CL_INT  oid = bunid_port1(p,ctx);
        OID  nm = GC_OID(ibunserialize_port1(p,ctx));
        OID  r = CNULL;
        OID  val = CNULL;
        OID  res;
        { if (inherit_ask_class(OWNER(nm),Kernel._symbol) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_("bunvar expected a symbol instead of ~S"),
            _oid_(list::alloc(1,nm)))));
          { OID  x = get_symbol(OBJECT(symbol,nm));
            if (x != CNULL)
             { nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),x);
              if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
               mtformat_module1(Serialize.it,"bunvar existing ~S \n",3,list::alloc(1,x));
              else ;r= GC_OID(ibunserialize_port1(p,ctx));
              if (equal(r,(*Kernel.range)(x)) != CTRUE)
               close_exception(((general_error *) (*Core._general_error)(_string_("bunvar try to update ~S's range (~S) with ~S"),
                _oid_(list::alloc(3,x,
                  GC_OID((*Kernel.range)(x)),
                  r)))));
              res = x;
              }
            else { if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
                 mtformat_module1(Serialize.it,"bunvar ~S \n",3,list::alloc(1,nm));
                else ;r= GC_OID(ibunserialize_port1(p,ctx));
                if (inherit_ask_class(OWNER(r),Kernel._type) != CTRUE)
                 close_exception(((general_error *) (*Core._general_error)(_string_("bunvar range type error, ~S is not a type"),
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
        val= GC_OID(ibunserialize_port1(p,ctx));
        (OBJECT(global_variable,res)->value = val);
        if (contain_ask_list(Core._global_variable->instances,res) != CTRUE)
         add_I_property(Kernel.instances,Core._global_variable,11,res);
        V_CC = complete_I_object(OBJECT(ClaireObject,res));
        }
      Result= (global_variable *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: bunclass(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
ClaireClass * bunclass_port1(PortObject *p,unserialize_context *ctx)
{ GC_BIND;
  { ClaireClass *Result ;
    { CL_INT  oid = bunid_port1(p,ctx);
      OID  symb = GC_OID(ibunserialize_port1(p,ctx));
      OID  res;
      { if (inherit_ask_class(OWNER(symb),Kernel._symbol) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_("~S is not a symbol!"),
          _oid_(list::alloc(1,symb)))));
        res = get_symbol(OBJECT(symbol,symb));
        }
      if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
       mtformat_module1(Serialize.it,"bunclass ~S \n",3,list::alloc(1,res));
      else ;if (inherit_ask_class(OWNER(res),Kernel._class) != CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("~S does not beong to class"),
        _oid_(list::alloc(1,res)))));
      nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),res);
      Result = OBJECT(ClaireClass,res);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: bunsysthing(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
SystemThing * bunsysthing_port1(PortObject *p,unserialize_context *ctx)
{ GC_BIND;
  { SystemThing *Result ;
    { CL_INT  oid = bunid_port1(p,ctx);
      OID  symb = GC_OID(ibunserialize_port1(p,ctx));
      OID  res;
      { if (inherit_ask_class(OWNER(symb),Kernel._symbol) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_("~S is not a symbol!"),
          _oid_(list::alloc(1,symb)))));
        res = get_symbol(OBJECT(symbol,symb));
        }
      if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
       mtformat_module1(Serialize.it,"bunsysthying ~S \n",3,list::alloc(1,res));
      else ;if (inherit_ask_class(OWNER(res),Kernel._system_thing) != CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("~S does not belong to system_thing"),
        _oid_(list::alloc(1,res)))));
      nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),res);
      Result = OBJECT(SystemThing,res);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: buntype(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
Type * buntype_port1(PortObject *p,unserialize_context *ctx)
{ GC_BIND;
  { Type *Result ;
    { CL_INT  oid = bunid_port1(p,ctx);
      OID  res = GC_OID(ibunserialize_port1(p,ctx));
      if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
       mtformat_module1(Serialize.it,"buntype ~S \n",3,list::alloc(1,res));
      else ;if (inherit_ask_class(OWNER(res),Core._Type) != CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("~S is not a Type!"),
        _oid_(list::alloc(1,res)))));
      nth_equal_table1(GC_OBJECT(table,ctx->unserialized),((OID)oid),res);
      Result = OBJECT(Type,res);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: ibunserialize(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  ibunserialize_port1(PortObject *p,unserialize_context *ctx)
{ GC_BIND;
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
           close_exception(((general_error *) (*Core._general_error)(_string_("~S does not belong to string"),
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
         bun = bunbagarray_port1(p,ctx);
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
        else if (tag == 38)
         bun = _oid_(bunsymbol_I_port1(p,ctx));
        else { OID  V_CL0305;close_exception(((general_error *) (*Core._general_error)(_string_("ibunserialize found an invalid tag (~S)"),
              _oid_(list::alloc(1,((OID)tag))))));
            
            bun=_void_(V_CL0305);}
          GC_OID(bun);}
      if (should_trace_ask_module1(Serialize.it,3) == CTRUE)
       mtformat_module1(Serialize.it,"bun ~S \n",3,list::alloc(1,bun));
      else ;Result = bun;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// *********************************************************************
// *   Part 4: api                                                     *
// *********************************************************************
// The c++ function for: serialize(p:port,self:any,selfTree:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  serialize_port1(PortObject *p,OID self,OID selfTree)
{ GC_BIND;
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
    (ctx->toplevel_only_ask = CFALSE);
    (*Serialize.ibserialize)(selfTree,
      _oid_(p),
      _oid_(ctx));
    (ctx->toplevel_only_ask = CTRUE);
    (*Serialize.ibserialize)(self,
      _oid_(p),
      _oid_(ctx));
    putc_integer1(19,p);
    use_as_output_port(old);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: serialize(p:port,top?:boolean,self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
serialize_context * serialize_port2(PortObject *p,ClaireBoolean *top_ask,OID self)
{ GC_BIND;
  { serialize_context *Result ;
    { PortObject * old = use_as_output_port(p);
      serialize_context * ctx;
      { { serialize_context * _CL_obj = ((serialize_context *) GC_OBJECT(serialize_context,new_object_class(Serialize._serialize_context)));
          ctx = close_serialize_context1(_CL_obj);
          }
        GC_OBJECT(serialize_context,ctx);}
      (ctx->toplevel_only_ask = top_ask);
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


// The c++ function for: serialize(p:port,self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
serialize_context * serialize_port3(PortObject *p,OID self)
{ POP_SIGNAL; return (serialize_port2(p,CTRUE,self));}


// The c++ function for: serialize(p:port,ctx:serialize_context,self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
serialize_context * serialize_port4(PortObject *p,serialize_context *ctx,OID self)
{ GC_BIND;
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


// The c++ function for: unserialize(p:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  unserialize_port1(PortObject *p)
{ GC_BIND;
  { OID Result = 0;
    { unserialize_context * ctx;
      { { unserialize_context * _CL_obj = ((unserialize_context *) GC_OBJECT(unserialize_context,new_object_class(Serialize._unserialize_context)));
          ctx = close_unserialize_context1(_CL_obj);
          }
        GC_OBJECT(unserialize_context,ctx);}
      char * ver_header = GC_STRING(fread_port4(p,2));
      if ((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))))) == CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("unserialize has encountered a premature eof"),
        _oid_(Kernel.nil))));
      if (equal(_string_(ver_header),Serialize.VERSION_HEADER->value) != CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("Invalid version of serialized data ~A (~A expected)"),
        _oid_(list::alloc(2,_string_(ver_header),GC_OID(Serialize.VERSION_HEADER->value))))));
      Result = ibunserialize_port1(p,ctx);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: serialize_context!(_CL_obj:void) [NEW_ALLOC]
serialize_context * serialize_context_I_void1()
{ GC_BIND;
  { serialize_context *Result ;
    { serialize_context * _CL_obj = ((serialize_context *) GC_OBJECT(serialize_context,new_object_class(Serialize._serialize_context)));
      Result = close_serialize_context1(_CL_obj);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: unserialize_context!(_CL_obj:void) [NEW_ALLOC]
unserialize_context * unserialize_context_I_void1()
{ GC_BIND;
  { unserialize_context *Result ;
    { unserialize_context * _CL_obj = ((unserialize_context *) GC_OBJECT(unserialize_context,new_object_class(Serialize._unserialize_context)));
      Result = close_unserialize_context1(_CL_obj);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: unserialize(p:port,ctx:unserialize_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  unserialize_port2(PortObject *p,unserialize_context *ctx)
{ GC_BIND;
  { OID Result = 0;
    { unserialize_context * ctx;
      { { unserialize_context * _CL_obj = ((unserialize_context *) GC_OBJECT(unserialize_context,new_object_class(Serialize._unserialize_context)));
          ctx = close_unserialize_context1(_CL_obj);
          }
        GC_OBJECT(unserialize_context,ctx);}
      char * ver_header = GC_STRING(fread_port4(p,2));
      if ((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))))) == CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("unserialize has encountered a premature eof"),
        _oid_(Kernel.nil))));
      if (equal(_string_(ver_header),Serialize.VERSION_HEADER->value) != CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("Invalid version of serialized data ~A (~A expected)"),
        _oid_(list::alloc(2,_string_(ver_header),GC_OID(Serialize.VERSION_HEADER->value))))));
      Result = ibunserialize_port1(p,ctx);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//

