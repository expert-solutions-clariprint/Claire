// interface definition for module Serialize
#ifndef CLAIREH_Serialize
#define CLAIREH_Serialize

  
class CL_EXPORT serialize_context;
class CL_EXPORT unserialize_context;
class CL_EXPORT Serialize_multiValuedBreak;

class CL_EXPORT serialize_context: public ephemeral_object{ 
    public:
       ClaireBoolean *toplevel_ask;
       ClaireBoolean *toplevel_only_ask;
       CL_INT currentOid;
       list *alreadySerialized;
       list *toSerialize_ask;}
  ;

class CL_EXPORT unserialize_context: public ephemeral_object{ 
    public:
       table *unserialized;}
  ;

class CL_EXPORT Serialize_multiValuedBreak: public thing{ 
    public:}
  ;
extern CL_EXPORT serialize_context * close_serialize_context1(serialize_context *self);
extern CL_EXPORT CL_INT  nth_serialize_context1(serialize_context *self,OID x);
extern CL_EXPORT void  preSerialize_any1(OID self,serialize_context *ctx);
extern CL_EXPORT unserialize_context * close_unserialize_context1(unserialize_context *self);
extern CL_EXPORT void  puti_integer1(CL_INT aint,PortObject *p);
extern CL_EXPORT void  putc_integer1(CL_INT i,PortObject *p);
extern CL_EXPORT CL_INT  newOid_any1(OID self,int tag,PortObject *p,serialize_context *ctx);
extern CL_EXPORT ClaireBoolean * shouldSerialize_ask_any1(OID self,int tag,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_prop_object1(ClaireObject *self,property *prop,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_object2(ClaireObject *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_thing1(thing *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_module1(module *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_symbol1(symbol *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_class1(ClaireClass *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_table1(table *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_system_thing1(SystemThing *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_bag1(bag *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_array1(OID *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_restriction1(restriction *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_collection1(ClaireCollection *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_exception1(ClaireException *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_global_variable1(global_variable *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_boolean1(ClaireBoolean *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_integer1(CL_INT self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_string1(char *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_char1(ClaireChar *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_float1(double self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_float1_(OID g0324,PortObject *g0325,serialize_context *g0326);
extern CL_EXPORT void  ibserialize_any1(OID self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_system_object1(SystemObject *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_blob1(blob *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT void  ibserialize_clob1(clob *self,PortObject *p,serialize_context *ctx);
extern CL_EXPORT CL_INT  bunint_port1(PortObject *p);
extern CL_EXPORT CL_INT  bunid_port1(PortObject *p,unserialize_context *ctx);
extern CL_EXPORT OID  bunoid_port1(PortObject *p,unserialize_context *ctx);
extern CL_EXPORT module * bunmodule_port1(PortObject *p,unserialize_context *ctx);
extern CL_EXPORT char * bunstring_port1(PortObject *p,unserialize_context *ctx);
extern CL_EXPORT symbol * bunsymbol_port1(PortObject *p,unserialize_context *ctx);
extern CL_EXPORT OID  bunbagarray_port1(PortObject *p,unserialize_context *ctx);
extern CL_EXPORT ClaireObject * bunobject_port1(PortObject *p,unserialize_context *ctx);
extern CL_EXPORT ClaireObject * bunthing_port1(PortObject *p,unserialize_context *ctx);
extern CL_EXPORT global_variable * bunvar_port1(PortObject *p,unserialize_context *ctx);
extern CL_EXPORT ClaireClass * bunclass_port1(PortObject *p,unserialize_context *ctx);
extern CL_EXPORT SystemThing * bunsysthing_port1(PortObject *p,unserialize_context *ctx);
extern CL_EXPORT Type * buntype_port1(PortObject *p,unserialize_context *ctx);
extern CL_EXPORT blob * bunblob_port1(PortObject *p,unserialize_context *ctx);
extern CL_EXPORT clob * bunclob_port1(PortObject *p,unserialize_context *ctx);
extern CL_EXPORT OID  ibunserialize_port1(PortObject *p,unserialize_context *ctx);
extern CL_EXPORT void  serialize_port1(PortObject *p,OID self,OID selfTree);
extern CL_EXPORT serialize_context * serialize_port2(PortObject *p,ClaireBoolean *top_ask,OID self);
extern CL_EXPORT serialize_context * serialize_port3(PortObject *p,OID self);
extern CL_EXPORT serialize_context * serialize_port4(PortObject *p,serialize_context *ctx,OID self);
extern CL_EXPORT OID  unserialize_port1(PortObject *p);
extern CL_EXPORT serialize_context * serialize_context_I_void1();
extern CL_EXPORT unserialize_context * unserialize_context_I_void1();
extern CL_EXPORT OID  unserialize_port2(PortObject *p,unserialize_context *ctx);

// namespace class for Serialize 
class CL_EXPORT SerializeClass: public NameSpace {
public:

  ClaireClass * _serialize_context;
  ClaireClass * _unserialize_context;
  global_variable * TEST_SET;
  ClaireClass * _multiValuedBreak;
  Serialize_multiValuedBreak * breakList;
  Serialize_multiValuedBreak * breakTypedList;
  Serialize_multiValuedBreak * breakSet;
  Serialize_multiValuedBreak * breakTypedSet;
  Serialize_multiValuedBreak * breakArray;
  Serialize_multiValuedBreak * breakTypedArray;
  Serialize_multiValuedBreak * breakTuple;
  Serialize_multiValuedBreak * breakObject;
  global_variable * TMP;
  global_variable * VERSION_HEADER;
property * toplevel_ask;// Serialize/"toplevel?"
property * toplevel_only_ask;// claire/"toplevel_only?"
property * currentOid;// Serialize/"currentOid"
property * alreadySerialized;// Serialize/"alreadySerialized"
property * toSerialize_ask;// Serialize/"toSerialize?"
property * preSerialize;// Serialize/"preSerialize"
property * unserialized;// Serialize/"unserialized"
property * puti;// Serialize/"puti"
property * newOid;// Serialize/"newOid"
property * ibserialize;// Serialize/"ibserialize"
property * shouldSerialize_ask;// Serialize/"shouldSerialize?"
property * bunint;// Serialize/"bunint"
property * bunid;// Serialize/"bunid"
property * ibunserialize;// Serialize/"ibunserialize"
property * bunoid;// Serialize/"bunoid"
property * bunmodule;// Serialize/"bunmodule"
property * bunstring;// Serialize/"bunstring"
property * bunsymbol;// Serialize/"bunsymbol"
property * bunbagarray;// Serialize/"bunbagarray"
property * bunobject;// Serialize/"bunobject"
property * bunthing;// Serialize/"bunthing"
property * bunvar;// Serialize/"bunvar"
property * bunclass;// Serialize/"bunclass"
property * bunsysthing;// Serialize/"bunsysthing"
property * buntype;// Serialize/"buntype"
property * serialize;// claire/"serialize"
property * unserialize;// claire/"unserialize"
property * serialize_context_I;// claire/"serialize_context!"
property * unserialize_context_I;// claire/"unserialize_context!"
property * ibserialize_prop;// Serialize/"ibserialize_prop"
property * bunblob;// Serialize/"bunblob"
property * bunclob;// Serialize/"bunclob"

// module definition 
 void metaLoad();};

extern CL_EXPORT SerializeClass Serialize;
extern CL_EXPORT NameSpace iClaire;

#endif

