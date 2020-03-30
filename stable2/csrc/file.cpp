/***** CLAIRE Compilation of file ./meta/file.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:42 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>

//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| file.cl                                                     |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+
// ---------------------------------------------------------------------
// Contents:
//   Part 1: Utilities
//   Part 2: Loading
//   Part 3: Reading
//   Part 4: Top-level
//   Part 5: The show & kill compiled_methods
// ---------------------------------------------------------------------
// **********************************************************************
// *   Part 1: Utilities                                                *
// **********************************************************************
// useful gadgets
//
// The c++ function for: self_eval(self:delimiter) [NEW_ALLOC+SLOT_UPDATE]
OID  self_eval_delimiter(delimiter *self)
{ next_meta_reader(Reader.reader);
  POP_SIGNAL; return (_void_(Serror_integer1(117,"Loose delimiter ~S in program",list::alloc(1,_oid_(self)))));}


//<sb>
//<sb> add the register symbol
// a small useful function
// PORTABILITY WARNING: the following assumes newline is ^J (ASCII 10 dec)
// PORTABILITY WARNING: what about ^M (ASCII 13 dec)
//
// a small usefull function
// The c++ function for: useless_c(r:integer) [0]
ClaireBoolean * useless_c_integer(CL_INT r)
{ POP_SIGNAL; return (((r == Reader.reader->space) ? CTRUE : ((r == 10) ? CTRUE : ((r == 13) ? CTRUE : ((r == 32) ? CTRUE : ((r == Reader.reader->tab) ? CTRUE : CFALSE))))));}


// take care of PC format (10 + 13)
// The c++ function for: skipc(self:meta_reader) [SLOT_UPDATE]
OID  skipc_meta_reader(meta_reader *self)
{ { CL_INT loop_handle = ClEnv->cHandle;
    while ((useless_c_integer(firstc_meta_reader(self)) == CTRUE))
    { { ClaireBoolean * b = ((firstc_meta_reader(self) == 10) ? CTRUE : CFALSE);
        next_meta_reader(self);
        if ((b == CTRUE) && 
            (firstc_meta_reader(self) == 13))
         next_meta_reader(self);
        }
      POP_SIGNAL;}
    }
  POP_SIGNAL; return (((OID)firstc_meta_reader(self)));}


// look for a meaningful termination char such as ) or ]
// The c++ function for: skipc!(r:meta_reader) [NEW_ALLOC+SLOT_UPDATE]
OID  skipc_I_meta_reader(meta_reader *r)
{ GC_BIND;
  { OID Result = 0;
    { OID  c = skipc_meta_reader(r);
      if (c == ((OID)59))
       { { CL_INT loop_handle = ClEnv->cHandle;
          while (((firstc_meta_reader(r) != r->eof) && 
              (firstc_meta_reader(r) != 10)))
          { next_meta_reader(r);
            POP_SIGNAL;}
          }
        if (firstc_meta_reader(r) == r->eof)
         Result = Core._eof->value;
        else Result = skipc_I_meta_reader(r);
          }
      else if (c == ((OID)47))
       { OID  x = GC_OID(read_ident_meta_reader1(r));
        if (Kernel._string == OWNER(x))
         Result = skipc_I_meta_reader(r);
        else Result = ((OID)47);
          }
      else Result = c;
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: cnext(self:meta_reader) [SLOT_UPDATE+SAFE_RESULT]
meta_reader * cnext_meta_reader(meta_reader *self)
{ next_meta_reader(self);
  POP_SIGNAL; return (self);}


// The c++ function for: findeol(self:meta_reader) [SLOT_UPDATE]
ClaireBoolean * findeol_meta_reader(meta_reader *self)
{ { ClaireBoolean *Result ;
    { ClaireBoolean *v_or;
      { { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
            V_C= _oid_(CFALSE);
            while ((useless_c_integer(firstc_meta_reader(self)) == CTRUE))
            { if (firstc_meta_reader(self) == 10)
               { V_C = Kernel.ctrue;
                ClEnv->cHandle = loop_handle;break;}
              next_meta_reader(self);
              POP_SIGNAL;}
            }
          
          v_or=OBJECT(ClaireBoolean,V_C);}
        if (v_or == CTRUE) Result =CTRUE; 
        else { v_or = ((firstc_meta_reader(self) == self->eof) ? CTRUE : CFALSE);
          if (v_or == CTRUE) Result =CTRUE; 
          else Result = CFALSE;}
        }
      }
    POP_SIGNAL; return (Result);}
  }


// safety checking
//
// The c++ function for: checkno(r:meta_reader,n:integer,y:any) [NEW_ALLOC]
OID  checkno_meta_reader(meta_reader *r,int n,OID y)
{ { OID Result = 0;
    if (firstc_meta_reader(r) != n)
     Result = _oid_(r);
    else Serror_integer1(118,"Read wrong char ~S after ~S",list::alloc(2,_oid_(char_I_integer(n)),y));
      POP_SIGNAL; return (Result);}
  }


// reads a keyword inside a control structure
//
// The c++ function for: verify(t:any,x:any,y:any) [NEW_ALLOC+RETURN_ARG]
OID  verify_any(OID t,OID x,OID y)
{ { OID Result = 0;
    if (belong_to(x,t) == CTRUE)
     Result = x;
    else Serror_integer1(119,"Read ~S instead of a ~S in a ~S",list::alloc(3,x,
        t,
        y));
      POP_SIGNAL; return (Result);}
  }


// The c++ function for: self_print(self:syntax_error) [NEW_ALLOC+SLOT_UPDATE]
void  self_print_syntax_error1_Reader(Reader_syntax_error *self)
{ GC_BIND;
  princ_string("**** Syntax error [");
  print_any(((OID)self->code));
  princ_string("]\n");
  format_string(GC_STRING(self->cause),GC_OBJECT(list,self->args));
  GC_UNBIND; POP_SIGNAL;}


// prints a syntax error
//
// The c++ function for: Serror(c:integer,s:string,la:list) [NEW_ALLOC]
void  Serror_integer1(int c,char *s,list *la)
{ GC_BIND;
  { Reader_syntax_error * _CL_obj = ((Reader_syntax_error *) GC_OBJECT(Reader_syntax_error,new_object_class(Reader._syntax_error)));
    (_CL_obj->cause = s);
    (_CL_obj->args = la);
    (_CL_obj->code = c);
    close_exception(_CL_obj);
    }
  GC_UNBIND; POP_SIGNAL;}


//general_error(cause = "Syntax error [" /+ string!(c) /+ "] " /+ s, args = la))
// the reader-------------------------------------------------------------
//
// The c++ function for: reader_push(_CL_obj:void) [NEW_ALLOC+RETURN_ARG]
void  reader_push_void1()
{ GC_BIND;
  GC_OBJECT(list,OBJECT(list,Reader.READER_STACK->value))->addFast((OID)GC_OID(_oid_(copy_object(Reader.reader))));
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: reader_pop(_CL_obj:void) [0]
void  reader_pop_void1()
{ { meta_reader * y = OBJECT(meta_reader,last_list(OBJECT(list,Reader.READER_STACK->value)));
    meta_reader * r = Reader.reader;
    shrink_list(OBJECT(bag,Reader.READER_STACK->value),((CL_INT)OBJECT(bag,Reader.READER_STACK->value)->length-(CL_INT)1));
    memcpy(r, y, sizeof(meta_reader));
    }
  POP_SIGNAL;}


// The c++ function for: reader_reset(_CL_obj:void) [0]
void  reader_reset_void1()
{ { CL_INT loop_handle = ClEnv->cHandle;
    while ((OBJECT(bag,Reader.READER_STACK->value)->length != 0))
    { reader_pop_void1();
      POP_SIGNAL;}
    }
  POP_SIGNAL;}


// variable handling -------------------------------------------------
// reads a variable
//
// The c++ function for: extract_variable(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
Variable * extract_variable_any(OID self)
{ GC_BIND;
  { Variable *Result ;
    if ((INHERIT(OWNER(self),Language._Variable)) && (equal(get_symbol(OBJECT(Variable,self)->pname),self) != CTRUE))
     { (OBJECT(Variable,self)->range = extract_type_any(GC_OID((*Kernel.range)(self))));
      Result = OBJECT(Variable,self);
      }
    else { Variable * v;
        { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
            (_CL_obj->pname = extract_symbol_any(self));
            add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
            v = _CL_obj;
            }
          GC_OBJECT(Variable,v);}
        (Reader.reader->last_form = _oid_(v));
        Result = v;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// create a variable and add it to the lexical environment
// The c++ function for: bind!(self:meta_reader,%v:Variable) [NEW_ALLOC+SLOT_UPDATE]
list * bind_I_meta_reader(meta_reader *self,Variable *_Zv)
{ (_Zv->index = self->index);
  { list *Result ;
    { OID  value = get_symbol(_Zv->pname);
      (self->index = ((CL_INT)self->index+(CL_INT)1));
      if ((CL_INT)self->index > (CL_INT)self->maxstack)
       (self->maxstack = self->index);
      put_symbol(_Zv->pname,_oid_(_Zv));
      Result = list::alloc(2,_oid_(_Zv),value);
      }
    POP_SIGNAL; return (Result);}
  }


// remove a variable from the lexical environment
//
// The c++ function for: unbind!(self:meta_reader,%first:list) [SLOT_UPDATE+RETURN_ARG]
OID  unbind_I_meta_reader(meta_reader *self,list *_Zfirst)
{ { OID Result = 0;
    { OID  var = (*(_Zfirst))[1];
      (self->index = ((CL_INT)self->index-(CL_INT)1));
      Result = put_symbol(OBJECT(Variable,var)->pname,(*(_Zfirst))[2]);
      }
    POP_SIGNAL; return (Result);}
  }


//
// basic methods defined in creader.c -----------------------------------
// TODO move!
// flush(self:port) : any -> function!(flush_port)
// this function is called by the main and restores the reader in a good shape. Also
// closes the input port to free the associated file ! <yc>
// The c++ function for: mClaire/restore_state(self:meta_reader) [NEW_ALLOC+SLOT_UPDATE]
void  restore_state_meta_reader(meta_reader *self)
{ GC_BIND;
  if (_oid_(self->fromp) != Core.cl_stdin->value)
   (*Core.fclose)(GC_OID(_oid_(self->fromp)));
  (self->fromp = OBJECT(PortObject,Core.cl_stdin->value));
  (self->index = 1);
  flush_port2(OBJECT(PortObject,Core.cl_stdin->value),32);
  restore_state_void();
  GC_UNBIND; POP_SIGNAL;}


// *********************************************************************
// *   Part 2: Loading                                                 *
// *********************************************************************
//<sb> add index referencing for objects
//<sb> v3.3.35, register file/line
// sload is the interactive version.
//
// The c++ function for: load_file(self:string,b:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  load_file_string(char *self,ClaireBoolean *b)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  reader_push_void1();
  (Reader.reader->index = 0);
  (Reader.reader->maxstack = 0);
  (Reader.reader->external = self);
  if (should_trace_ask_module1(Reader.it,3) == CTRUE)
   mtformat_module1(Reader.it,"---- [load CLAIRE file: ~A]\n",3,list::alloc(1,_string_(self)));
  else ;{ PortObject * f = GC_OBJECT(PortObject,fopen_source_string1(self));
    CL_INT  start = ClEnv->base;
    CL_INT  top = ClEnv->index;
    CL_INT  last_line = 1;
    OID  _staritem_star = CNULL;
    (ClEnv->base= ((OID)top));
    (Reader.reader->fromp = f);
    (Reader.reader->toplevel = CFALSE);
    _staritem_star= GC_OID(readblock_port(f));
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while ((equal(_staritem_star,Core._eof->value) != CTRUE))
      { GC_LOOP;
        if (b == CTRUE)
         { princ_integer(Reader.reader->nb_line);
          princ_string(":");
          print_any(_staritem_star);
          princ_string("\n");
          }
        (ClEnv->index= ((OID)((CL_INT)top+(CL_INT)((CL_INT)Reader.reader->maxstack+(CL_INT)1))));
        if (should_trace_ask_module1(Reader.it,3) == CTRUE)
         mtformat_module1(Reader.it,"load_file -> ~S \n",3,list::alloc(1,_staritem_star));
        else ;if (Kernel._string == OWNER(_staritem_star))
         { if ((OBJECT(ClaireBoolean,Language.NeedComment->value)) == CTRUE)
           { if (Language.LastComment->value != CNULL)
             (Language.LastComment->value= (*Kernel._7_plus)(GC_OID(Language.LastComment->value),
              GC_OID(_string_(append_string("\n",string_v(_staritem_star))))));
            else if ((CL_INT)LENGTH_STRING(string_v(_staritem_star)) > 0)
             (Language.LastComment->value= _staritem_star);
            last_line= (*(get_location_port1(f)->copyIfNeeded()))[2];
            }
          }
        else { GC__OID(_staritem_star = OPT_EVAL(_staritem_star), 1);
            if (Kernel._method == OWNER(_staritem_star))
             put_table(Reader.DB_INDEX,_staritem_star,_oid_(tuple::alloc(2,GC_OID(_string_(Reader.reader->external)),((OID)last_line))));
            last_line= ((CL_INT)1+(CL_INT)((*(get_location_port1(f)->copyIfNeeded()))[2]));
            (Language.LastComment->value= CNULL);
            }
          if (b == CTRUE)
         { princ_string("=> ");
          print_any(_staritem_star);
          princ_string(" \n\n");
          }
        GC__OID(_staritem_star = readblock_port(f), 1);
        GC_UNLOOP;POP_SIGNAL;}
      }
    reader_pop_void1();
    (ClEnv->base= ((OID)start));
    (ClEnv->index= ((OID)top));
    (*Core.fclose)(_oid_(f));
    }
  { OID Result = 0;
    Result = Kernel.ctrue;
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// the simple load
//
// The c++ function for: load(self:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  load_string(char *self)
{ POP_SIGNAL; return (load_file_string(self,CFALSE));}


// The c++ function for: sload(self:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  sload_string(char *self)
{ POP_SIGNAL; return (load_file_string(self,CTRUE));}


// loading a module into the system.
// The correct package is open and each file is loaded.
// The c++ function for: load_file(self:module,b:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  load_file_module(module *self,ClaireBoolean *b)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  if (self->status == 2)
   { fcall1(self->evaluate,Kernel._any,_oid_(Kernel._any),Kernel._any);
    (self->status = 3);
    }
  else if ((self->status == 0) && 
      (((self->source == (NULL)) ? CTRUE : CFALSE) != CTRUE))
   { if (should_trace_ask_module1(Reader.it,3) == CTRUE)
     mtformat_module1(Reader.it,"---- Loading the module ~S.\n",3,list::alloc(1,_oid_(self)));
    else ;begin_module(self);
    { char * s = GC_STRING(append_string(GC_STRING(self->source),GC_STRING(string_v(Core._starfs_star->value))));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(x);
        bag *x_support;
        x_support = GC_OBJECT(list,self->made_of);
        for (START(x_support); NEXT(x);)
        { GC_LOOP;
          if ((match_wildcard_ask_string(string_v(x),"*.cl") == CTRUE) || 
              (match_wildcard_ask_string(string_v(x),"*.*") != CTRUE))
           load_file_string(GC_STRING(append_string(GC_STRING(append_string(s,GC_STRING(replace_string(string_v(x),".cl","")))),".cl")),b);
          GC_UNLOOP; POP_SIGNAL;}
        }
      }
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(x);
      bag *x_support;
      x_support = GC_OBJECT(list,self->made_of);
      for (START(x_support); NEXT(x);)
      { GC_LOOP;
        if (match_wildcard_ask_string(string_v(x),"*@PATH_INFO@*") == CTRUE)
         { if (should_trace_ask_module1(Reader.it,3) == CTRUE)
           mtformat_module1(Reader.it,"---- [load WCL file: ~A]\n",3,GC_OBJECT(list,list::alloc(1,GC_OID((*(explode_string(string_v(x),"@PATH_INFO@")))[1]))));
          else ;reader_push_void1();
          (Reader.reader->toplevel = CFALSE);
          { list * defs = GC_OBJECT(list,load_wcl_I_string1(string_v(x)));
            CL_INT  start = ClEnv->base;
            CL_INT  top = ClEnv->index;
            (ClEnv->base= ((OID)top));
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(y);
              for (START(defs); NEXT(y);)
              { (ClEnv->index= ((OID)((CL_INT)top+(CL_INT)((CL_INT)Reader.reader->maxstack+(CL_INT)1))));
                OPT_EVAL(y);
                }
              }
            reader_pop_void1();
            (ClEnv->base= ((OID)start));
            (ClEnv->index= ((OID)top));
            }
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    (self->status = 1);
    }
  end_module(self);
  GC_UNBIND; POP_SIGNAL;}


//<sb> prevent load @ module to load module's code
// The c++ function for: set_load_module(b:boolean) [SAFE_RESULT]
void  set_load_module_boolean(ClaireBoolean *b)
{ (Reader.PROCESS_LOAD_MODULE_ask->value= _oid_(b));
  POP_SIGNAL;}


// the simple load
//
// The c++ function for: load(self:module) [NEW_ALLOC+BAG_UPDATE]
OID  load_module(module *self)
{ GC_BIND;
  { OID Result = 0;
    if ((OBJECT(ClaireBoolean,Reader.PROCESS_LOAD_MODULE_ask->value)) == CTRUE)
     { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(x);
      Result= Kernel.cfalse;
      bag *x_support;
      x_support = GC_OBJECT(list,add_modules_list(list::alloc(1,_oid_(self))));
      for (START(x_support); NEXT(x);)
      (*Reader.load_file)(x,
        Kernel.cfalse);
      }
    else Result = Kernel.cfalse;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: sload(self:module) [NEW_ALLOC+BAG_UPDATE]
OID  sload_module(module *self)
{ GC_BIND;
  { OID Result = 0;
    if ((OBJECT(ClaireBoolean,Reader.PROCESS_LOAD_MODULE_ask->value)) == CTRUE)
     { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(x);
      Result= Kernel.cfalse;
      bag *x_support;
      x_support = GC_OBJECT(list,add_modules_list(list::alloc(1,_oid_(self))));
      for (START(x_support); NEXT(x);)
      (*Reader.load_file)(x,
        Kernel.ctrue);
      }
    else Result = Kernel.cfalse;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// This is a very important method which adds the right order the
// modules that must be loaded to load oself. the list l represents the
// list of modules that we know will be in the result. result represent
// the current list of ordered modules
//
// The c++ function for: add_modules(self:module,l:set,result:list) [NEW_ALLOC+BAG_UPDATE+RETURN_ARG]
list * add_modules_module(module *self,set *l,list *result)
{ if (result->memq(_oid_(self)) == CTRUE) 
  { { list *Result ;
      Result = result;
      return (Result);}
     }
  else{ if (contain_ask_set(l,_oid_(self)) != CTRUE) 
    { { list *Result ;
        Result = result;
        return (Result);}
       }
    else{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
      if ((((self->part_of == (NULL)) ? CTRUE : CFALSE) != CTRUE) && 
          (self->part_of != claire.it))
       result= GC_OBJECT(list,add_modules_module(self->part_of,l,result));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(x);
        for (START(self->uses); NEXT(x);)
        { GC_LOOP;
          if (INHERIT(OWNER(x),Kernel._module))
           GC__ANY(result = add_modules_module(OBJECT(module,x),l,result), 1);
          GC_UNLOOP; POP_SIGNAL;}
        }
      if (result->memq(_oid_(self)) != CTRUE)
       result= result->addFast((OID)_oid_(self));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(x);
        for (START(self->parts); NEXT(x);)
        { GC_LOOP;
          GC__ANY(result = add_modules_module(OBJECT(module,x),l,result), 1);
          GC_UNLOOP; POP_SIGNAL;}
        }
      { list *Result ;
        Result = result;
        GC_UNBIND; POP_SIGNAL; return (Result);}
      }
    }
  }


//<sb> we adopt a different strategy for add_module :
// first we fill a list of needed modules 
// The c++ function for: add_parts(self:module,result:set) [NEW_ALLOC]
void  add_parts_module(module *self,set *result)
{ GC_BIND;
  result= GC_OBJECT(set,result->addFast((OID)_oid_(self)));
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(m);
    for (START(self->parts); NEXT(m);)
    add_parts_module(OBJECT(module,m),result);
    }
  GC_UNBIND; POP_SIGNAL;}


//<sb> add part_of until claire
// The c++ function for: add_subparts(self:module,result:set) [NEW_ALLOC]
void  add_subparts_module(module *self,set *result)
{ GC_BIND;
  if (((self->part_of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
   { module * m = self->part_of;
    result= GC_OBJECT(set,result->addFast((OID)_oid_(self)));
    if (m != claire.it)
     add_subparts_module(m,result);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: add_uses(self:module,result:set) [NEW_ALLOC]
void  add_uses_module(module *self,set *result)
{ GC_BIND;
  if (contain_ask_set(result,_oid_(self)) != CTRUE)
   result= GC_OBJECT(set,result->addFast((OID)_oid_(self)));
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(m);
    for (START(self->uses); NEXT(m);)
    if (contain_ask_set(result,m) != CTRUE)
     { add_uses_module(OBJECT(module,m),result);
      if (boolean_I_any(_oid_(OBJECT(module,m)->made_of)) != CTRUE)
       add_parts_module(OBJECT(module,m),result);
      }
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: add_modules(self:module,result:set) [NEW_ALLOC+RETURN_ARG]
void  add_modules_module2(module *self,set *result)
{ GC_BIND;
  add_uses_module(self,result);
  add_parts_module(self,result);
  add_subparts_module(self,result);
  result= GC_OBJECT(set,result->addFast((OID)_oid_(self)));
  GC_UNBIND; POP_SIGNAL;}


// this methods takes a list of modules that must be loaded and returns
// a list of modules that are necessary for the definition
//
// The c++ function for: add_modules(self:list) [NEW_ALLOC+BAG_UPDATE]
list * add_modules_list(list *self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { list *Result ;
    { set * base = set::empty(Kernel._module);
      list * l = list::empty(Kernel._module);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(m);
        for (START(self); NEXT(m);)
        add_modules_module2(OBJECT(module,m),base);
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(x);
        for (START(base); NEXT(x);)
        { GC_LOOP;
          GC__ANY(l = add_modules_module(OBJECT(module,x),base,l), 1);
          GC_UNLOOP; POP_SIGNAL;}
        }
      Result = l;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// load a file of expressions (quite useful)
// The c++ function for: eload(self:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  eload_string(char *self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  reader_push_void1();
  (Reader.reader->index = 0);
  (Reader.reader->maxstack = 0);
  (Reader.reader->nb_line = 1);
  (Reader.reader->external = self);
  if (should_trace_ask_module1(Reader.it,3) == CTRUE)
   mtformat_module1(Reader.it,"---- [eload CLAIRE file: ~A]\n",3,list::alloc(1,_string_(self)));
  else ;{ PortObject * p1 = GC_OBJECT(PortObject,fopen_source_string1(self));
    CL_INT  start = ClEnv->base;
    CL_INT  top = ClEnv->index;
    OID  _staritem_star = CNULL;
    (ClEnv->base= ((OID)top));
    (Reader.reader->toplevel = CFALSE);
    (Reader.reader->fromp = p1);
    _staritem_star= GC_OID(read_port(p1));
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while ((equal(_staritem_star,Core._eof->value) != CTRUE))
      { GC_LOOP;
        (ClEnv->index= ((OID)((CL_INT)top+(CL_INT)((CL_INT)Reader.reader->maxstack+(CL_INT)1))));
        GC__OID(_staritem_star = OPT_EVAL(_staritem_star), 1);
        GC__OID(_staritem_star = read_port(p1), 1);
        GC_UNLOOP;POP_SIGNAL;}
      }
    reader_pop_void1();
    (ClEnv->base= ((OID)start));
    (ClEnv->index= ((OID)top));
    (*Core.fclose)(_oid_(p1));
    }
  { OID Result = 0;
    Result = Kernel.ctrue;
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// *********************************************************************
// *   Part 3: Read & Top-level                                        *
// *********************************************************************
// The standard read function.
// This method reads from a CLAIRE port (self).
// We first check if self is the current reading port.
// the last character read (and not used) is in last(reader)
// The c++ function for: readblock(p:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  readblock_port(PortObject *p)
{ GC_BIND;
  (Reader.IDENTS->value= _oid_(list::empty(Kernel._list)));
  { OID Result = 0;
    if (Reader.reader->fromp == p)
     Result = nextunit_meta_reader(Reader.reader);
    else { PortObject * p2 = GC_OBJECT(PortObject,Reader.reader->fromp);
        (Reader.reader->fromp = p);
        { OID  val = GC_OID(nextunit_meta_reader(Reader.reader));
          (Reader.reader->fromp = p2);
          if ((equal(val,Reader.reader->paren) == CTRUE) || 
              ((equal(val,Reader.reader->curly) == CTRUE) || 
                ((equal(val,Reader.reader->comma) == CTRUE) || 
                  (equal(val,Reader.reader->bracket) == CTRUE))))
           Serror_integer1(117,"Loose ~S in file",list::alloc(1,val));
          Result = val;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// read reads a closed expression
// The c++ function for: read(p:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  read_port(PortObject *p)
{ GC_BIND;
  { OID Result = 0;
    { PortObject * p2 = GC_OBJECT(PortObject,Reader.reader->fromp);
      if (p != p2)
       (Reader.reader->fromp = p);
      { OID  val;
        { if (skipc_meta_reader(Reader.reader) == ((OID)Reader.reader->eof))
           val = Core._eof->value;
          else val = nexte_meta_reader(Reader.reader);
            GC_OID(val);}
        if (p != p2)
         (Reader.reader->fromp = p2);
        if ((equal(val,Reader.reader->paren) == CTRUE) || 
            ((equal(val,Reader.reader->curly) == CTRUE) || 
              ((equal(val,Reader.reader->comma) == CTRUE) || 
                (equal(val,Reader.reader->bracket) == CTRUE))))
         Serror_integer1(117,"Loose ~S in file",list::alloc(1,val));
        Result = val;
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// read into a string
// The c++ function for: read(self:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  read_string(char *self)
{ GC_BIND;
  { OID Result = 0;
    { OID  x = CNULL;
      reader_push_void1();
      (Reader.reader->toplevel = CTRUE);
      { blob * p = GC_OBJECT(blob,blob_I_string1(self));
        (Reader.reader->fromp = p);
        { ClaireHandler c_handle = ClaireHandler();
          if ERROR_IN 
          { x= GC_OID(nextunit_meta_reader(Reader.reader));
            ERROR_FREE;}
          else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
          { c_handle.catchIt();{ reader_pop_void1();
              close_exception(ClEnv->exception_I);
              }
            }
          else PREVIOUS_HANDLER;}
        fclose_device1(p);
        }
      reader_pop_void1();
      Result = x;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//call_debug :: property()
// calls the debugger
//
// a method for calling the printer without issuing a message (that would
// modify the stack and make debugging impossible).
// here we assume that self_print is always defined and is always a compiled
// function
// The c++ function for: print_exception(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  print_exception_void()
{ GC_BIND;
  avoid_signal_handling++;
  { OID Result = 0;
    { PortObject * p = use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value));
      ClaireException * _Zerr = GC_OBJECT(ClaireException,ClEnv->exception_I);
      method * _Zprop = ((method *) _at_property1(Kernel.self_print,OWNER(_oid_(_Zerr))));
      { ClaireHandler c_handle = ClaireHandler();
        if ERROR_IN 
        { { if (Reader.reader->toplevel != CTRUE)
             { CL_INT  g0688 = (int )(current_color);
              CL_INT  g0689 = (int )(current_bold);
              CL_INT  g0690 = g0688;
              CL_INT  g0691 = g0689;
              color(g0688,g0689);
              color_princ_string1("`RED---- file: ");
              g0688= (int )(current_color);
              g0689= (int )(current_bold);
              color(g0690,g0691);
              print_source_location_port1(GC_OBJECT(PortObject,Reader.reader->fromp));
              color(g0688,g0689);
              color(g0688,g0689);
              color_princ_string1("\n");
              color(g0690,g0691);
              }
            color(31,0);
            if (((_Zprop->functional == (NULL)) ? CTRUE : CFALSE) != CTRUE)
             fcall1(_Zprop->functional,Kernel._object,_oid_(_Zerr),Kernel._any);
            else funcall_method1(_Zprop,_oid_(_Zerr));
              princ_string("\n");
            }
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
        { c_handle.catchIt();{ color(31,0);
            princ_string("\n****** ERROR[121]: unprintable error <");
            print_any(_oid_(OWNER(_oid_(_Zerr))));
            princ_string(">.\n");
            }
          }
        else PREVIOUS_HANDLER;}
      color(30,0);
      p= use_as_output_port(p);
      avoid_signal_handling--;
      Result = _oid_(p);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// *********************************************************************
// *     Part 4: the show & kill methods                               *
// *********************************************************************
//----------------- printing an object -------------------------
// %show is an open restriction which allow to show the value of a
// binary relation
//
// this method is the basic method called for show(..)
//
// The c++ function for: show(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  show_any(OID self)
{ if (_Z_any1(self,Kernel._object) == CTRUE)
   { CL_INT loop_handle = ClEnv->cHandle;
    ITERATE(rel);
    bag *rel_support;
    rel_support = OWNER(self)->slots;
    for (START(rel_support); NEXT(rel);)
    { print_any(_oid_(OBJECT(restriction,rel)->selector));
      princ_string(": ");
      print_any(get_slot(OBJECT(slot,rel),OBJECT(ClaireObject,self)));
      princ_string("\n");
      }
    }
  else { print_any(self);
      princ_string(" is a ");
      print_any(_oid_(OWNER(self)));
      princ_string("\n");
      }
    POP_SIGNAL; return (Kernel.ctrue);}


//
// our two very special inline methods
// The c++ function for: min(x:any,y:any) [NEW_ALLOC+RETURN_ARG]
OID  min_any(OID x,OID y)
{ { OID Result = 0;
    if ((OBJECT(ClaireBoolean,(*Kernel._inf_equal)(x,
      y))) == CTRUE)
     Result = x;
    else Result = y;
      POP_SIGNAL; return (Result);}
  }


// The c++ function for: max(x:any,y:any) [NEW_ALLOC+RETURN_ARG]
OID  max_any(OID x,OID y)
{ { OID Result = 0;
    if ((OBJECT(ClaireBoolean,(*Kernel._inf_equal)(x,
      y))) == CTRUE)
     Result = y;
    else Result = x;
      POP_SIGNAL; return (Result);}
  }


// check if the value is known?
// The c++ function for: known?(a:table,x:any) [0]
ClaireBoolean * known_ask_table(table *a,OID x)
{ POP_SIGNAL; return (_I_equal_any(get_table(a,x),CNULL));}


// The c++ function for: unknown?(a:table,x:any) [0]
ClaireBoolean * unknown_ask_table(table *a,OID x)
{ POP_SIGNAL; return (equal(get_table(a,x),CNULL));}


//
// v3.00.46 a new macro
// The c++ function for: >=(self:any,x:any) [NEW_ALLOC]
ClaireBoolean * _sup_equal_any(OID self,OID x)
{ POP_SIGNAL; return (OBJECT(ClaireBoolean,(*Kernel._inf_equal)(x,
    self)));}


// this is a useful macro for hashing
// The c++ function for: mClaire/hashgrow(l:list,hi:property) [NEW_ALLOC]
list * hashgrow_list(list *l,property *hi)
{ GC_BIND;
  { list *Result ;
    { list * l1 = l;
      list * l2 = GC_OBJECT(list,make_list_integer(((CL_INT)((*(l1))[0])*(CL_INT)2),CNULL));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(x);
        for (START(l1); NEXT(x);)
        if (x != CNULL)
         (*Core.call)(_oid_(hi),
          _oid_(l2),
          x);
        }
      Result = l2;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> we store external dependencies (module, path)
//<sb> query the module m = "module/version" that will be used
// by another module later ...
// place some use_module commands in your init.cl file
// use_module searches for a init.cl that match module/version in
// both publish folder and CLAIRE_LIBS
// The c++ function for: use_module(m:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  use_module_string(char *m)
{ GC_RESERVE(19);  // v3.0.55 optim !
  if (LENGTH_STRING(m) == 0)
   close_exception(((general_error *) (*Core._general_error)(_string_("use_module called with an empty string !"),
    _oid_(Kernel.nil))));
  if (isenv_ask_string("CLAIRE_LIBS") != CTRUE)
   { if (should_trace_ask_module1(Reader.it,3) == CTRUE)
     mtformat_module1(Reader.it,"---- warning: environment variable CLAIRE_LIBS undefined\n",3,list::empty());
    else ;}
  { char * f = GC_STRING(realpath_string(getenv_string("_")));
    char * hom = GC_STRING(((isenv_ask_string("CLAIRE_PUBLISH_HOME") == CTRUE) ?
      getenv_string("CLAIRE_PUBLISH_HOME") :
      realpath_string(GC_STRING(_7_string(GC_STRING(_7_string(GC_STRING(_7_string(GC_STRING(substring_string(f,1,((CL_INT)rfind_string2(f,string_v(Core._starfs_star->value))-(CL_INT)1))),"..")),"..")),".."))) ));
    list * p;
    { { list * pu = GC_OBJECT(list,explode_string(m,"/"));
        if ((CL_INT)pu->length > 1)
         p = pu;
        else { list * pc = GC_OBJECT(list,explode_string(m,"\\"));
            p = pc;
            }
          }
      GC_OBJECT(list,p);}
    OID  up;
    { if ((CL_INT)p->length > 1)
       up = _string_(_7_string(string_v((*(p))[1]),string_v((*(p))[2])));
      else up = (*(p))[1];
        GC_OID(up);}
    list * libs = GC_OBJECT(list,GC_OBJECT(list,explode_string(getenv_string("CLAIRE_LIBS"),GC_STRING(string_v(Core._starps_star->value))))->addFast((OID)GC_OID(_string_(_7_string(hom,"lib")))));
    char * oldp = GC_STRING(pwd_void());
    if (value_string(string_v((*(p))[1])) == CNULL)
     { OID  mptest;
      { { OID  mp_some = CNULL;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(mp);
            for (START(libs); NEXT(mp);)
            { GC_LOOP;
              if (isfile_ask_string(_7_string(GC_STRING(_7_string(string_v(mp),string_v(up))),"init.cl")) == CTRUE)
               { mp_some= mp;
                ClEnv->cHandle = loop_handle; break;}
              GC_UNLOOP; POP_SIGNAL;}
            }
          mptest = mp_some;
          }
        GC_OID(mptest);}
      if (mptest != CNULL)
       { char * mp = string_v(mptest);
        if (should_trace_ask_module1(Reader.it,3) == CTRUE)
         mtformat_module1(Reader.it,"==== Use module ~A at ~A [v~A] ==== \n",3,GC_OBJECT(list,list::alloc(3,_string_(m),
          _string_(mp),
          GC_OID(release_void()))));
        else ;setcwd_string(_7_string(mp,string_v(up)));
        { ClaireHandler c_handle = ClaireHandler();
          if ERROR_IN 
          { { read_string("begin(claire)");
              load_string("init");
              { OID  m = value_string(string_v((*(p))[1]));
                if (inherit_ask_class(OWNER(m),Kernel._module) != CTRUE)
                 close_exception(((general_error *) (*Core._general_error)(_string_("The init file ~A doesn't define the module ~A!"),
                  _oid_(list::alloc(2,GC_OID(_string_(_7_string(GC_STRING(_7_string(mp,string_v(up))),"init.cl"))),(*(p))[1])))));
                (*Reader.load)(m);
                (Reader.used_modules->value= _oid_(GC_OBJECT(list,OBJECT(list,Reader.used_modules->value))->addFast((OID)_oid_(tuple::alloc(2,m,GC_OID(_string_(_7_string(mp,string_v(up)))))))));
                }
              }
            ERROR_FREE;}
          else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
          { c_handle.catchIt();{ setcwd_string(oldp);
              close_exception(ClEnv->exception_I);
              }
            }
          else PREVIOUS_HANDLER;}
        setcwd_string(oldp);
        }
      else { ClaireBoolean * g0693I;
        { OID  g0694UU;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(mp);
            g0694UU= Kernel.cfalse;
            for (START(libs); NEXT(mp);)
            if (isdir_ask_string(_7_string(string_v(mp),string_v((*(p))[1]))) == CTRUE)
             { g0694UU = Kernel.ctrue;
              ClEnv->cHandle = loop_handle;break;}
            }
          g0693I = boolean_I_any(g0694UU);
          }
        
        if (g0693I == CTRUE) { if (p->length == 1)
             { if (should_trace_ask_module1(Reader.it,3) == CTRUE)
               mtformat_module1(Reader.it,"---- warning: undefined version of module ~A, expect one of: \n",3,list::alloc(1,_string_(m)));
              else ;}
            else if (should_trace_ask_module1(Reader.it,3) == CTRUE)
             mtformat_module1(Reader.it,"---- warning: unresolved module ~A, missing version ~A in: \n",3,list::alloc(2,(*(p))[1],(*(p))[2]));
            else ;{ ClaireBoolean * first_ask = CTRUE;
              char * ump = "";
              ClaireBoolean * haveinit_ask = CFALSE;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(g0692);
                for (START(libs); NEXT(g0692);)
                { GC_LOOP;
                  { char * mp = GC_STRING(_7_string(string_v(g0692),string_v((*(p))[1])));
                    if (isdir_ask_string(mp) == CTRUE)
                     { if (isfile_ask_string(_7_string(mp,"init.cl")) == CTRUE)
                       haveinit_ask= CTRUE;
                      else { list * es;
                          { { bag * e_in = entries_string2(mp);
                              list * e_out = ((list *) empty_bag(e_in));
                              { CL_INT loop_handle = ClEnv->cHandle;
                                OID gc_local;
                                ITERATE(e);
                                for (START(e_in); NEXT(e);)
                                { GC_LOOP;
                                  if ((isdir_ask_string(_7_string(mp,string_v(e))) == CTRUE) && 
                                      (isfile_ask_string(_7_string(GC_STRING(_7_string(mp,string_v(e))),"init.cl")) == CTRUE))
                                   e_out->addFast((OID)e);
                                  GC_UNLOOP; POP_SIGNAL;}
                                }
                              es = GC_OBJECT(list,e_out);
                              }
                            GC_OBJECT(list,es);}
                          if (es->length != 0)
                           { if (should_trace_ask_module1(Reader.it,3) == CTRUE)
                             mtformat_module1(Reader.it,"     [~A] ~A \n",3,GC_OBJECT(list,list::alloc(2,_string_(mp),_oid_(es))));
                            else ;if (first_ask == CTRUE)
                             { first_ask= CFALSE;
                              GC__STRING(ump = string_v((*(sort_method(GC_OBJECT(method,((method *) _at_property1(Kernel._sup,Kernel._string))),es)))[1]), 11);
                              }
                            }
                          }
                        }
                    }
                  GC_UNLOOP; POP_SIGNAL;}
                }
              if ((haveinit_ask == CTRUE) || 
                  ((CL_INT)LENGTH_STRING(ump) > 0))
               { if (should_trace_ask_module1(Reader.it,3) == CTRUE)
                 mtformat_module1(Reader.it,"     ===> try with ~A \n",3,GC_OBJECT(list,list::alloc(1,GC_OID(_string_(_7_string(string_v((*(p))[1]),ump))))));
                else ;if (LENGTH_STRING(ump) == 0)
                 use_module_string(string_v((*(p))[1]));
                else use_module_string(GC_STRING(_7_string(string_v((*(p))[1]),ump)));
                  }
              }
            }
          else { if (should_trace_ask_module1(Reader.it,0) == CTRUE)
           mtformat_module1(Reader.it,"---- warning: the module ~A cannot be found in any of: \n",0,GC_OBJECT(list,list::alloc(1,_string_(m))));
          else ;{ CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(mp);
            for (START(libs); NEXT(mp);)
            { GC_LOOP;
              if (should_trace_ask_module1(Reader.it,0) == CTRUE)
               mtformat_module1(Reader.it,"     ~A \n",0,GC_OBJECT(list,list::alloc(1,mp)));
              else ;GC_UNLOOP; POP_SIGNAL;}
            }
          }
        }
      }
    if (value_string("Compile") != CNULL)
     { read_string("erase(inline?, compiler)");
      read_string("erase(safety, compiler)");
      read_string("erase(overflow?, compiler)");
      read_string("erase(naming, compiler)");
      read_string("(compiler.source := \"csrc\")");
      read_string("(Compile/FCALLSTINKS := false)");
      }
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: option_usage(g0695:{"-f", "-ef"}) [NEW_ALLOC]
tuple * option_usage_string13_Reader_(char *g0695)
{ return option_usage_string13_Reader(g0695)->copyIfNeeded();}


// The c++ function for: option_usage(opt:{"-ef", "-f"}) [NEW_ALLOC]
tuple * option_usage_string13_Reader(char *opt)
{ GC_BIND;
  { tuple *Result ;
    Result = tuple::allocStack(3,_string_("Load file"),
      _string_("{-f | -ef} <file:path> ..."),
      GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(append_string("Load the CLAIRE file(s) <file>. The given path may contain an extension ","assuming .cl by default. When the <-f> option is used, the file is ")),"assumed to contain CLAIRE definitions (variables, class, methods) wheheas "))," <-ef> attemps to read a file made of CLAIRE expression."))));
    GC_UNBIND; return (Result);}
  }


// The c++ function for: option_respond(opt:{"-ef", "-f"},l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  option_respond_string10_Reader(char *opt,list *l)
{ if (boolean_I_any(_oid_(l)) != CTRUE)
   close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
  if ((isfile_ask_string(string_v((*(l))[1])) != CTRUE) && 
      (isfile_ask_string(string_v((*Kernel._7_plus)((*(l))[1],
        _string_(".cl")))) != CTRUE))
   close_exception(((general_error *) (*Core._general_error)(_string_("~A cannot be opened"),
    _oid_(list::alloc(1,(*(l))[1])))));
  { CL_INT loop_handle = ClEnv->cHandle;
    while (((l->length != 0) && 
        ((isfile_ask_string(string_v((*(l))[1])) == CTRUE) || 
            (isfile_ask_string(string_v((*Kernel._7_plus)((*(l))[1],
              _string_(".cl")))) == CTRUE))))
    { { OID  path = (*(l))[1];
        skip_list(l,1);
        if (equal_string(opt,"-f") == CTRUE)
         (*Reader.load)(path);
        else if (equal_string(opt,"-ef") == CTRUE)
         eload_string(string_v(path));
        }
      POP_SIGNAL;}
    }
  POP_SIGNAL;}


// The c++ function for: option_usage(g0696:{"-princ", "-print", "-eval"}) [NEW_ALLOC]
tuple * option_usage_string14_Reader_(char *g0696)
{ return option_usage_string14_Reader(g0696)->copyIfNeeded();}


// The c++ function for: option_usage(opt:{"-eval", "-print", "-princ"}) [NEW_ALLOC]
tuple * option_usage_string14_Reader(char *opt)
{ GC_BIND;
  { tuple *Result ;
    Result = tuple::allocStack(3,_string_("Eval expression"),
      _string_("{-princ | -print | -eval} <exp:any>"),
      GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(append_string("Eval the CLAIRE expresion <exp>. If <-princ> or <-print> is used instead ","of <-eval>, the result of the evaluation is princed/printed on the ")),"standard output. Oftenly, the hosting shell support quotes allowing ")),"<exp> to contain space and/or special chars."))));
    GC_UNBIND; return (Result);}
  }


// The c++ function for: option_respond(opt:{"-print", "-princ", "-eval"},l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  option_respond_string11_Reader(char *opt,list *l)
{ GC_BIND;
  if (boolean_I_any(_oid_(l)) != CTRUE)
   close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
  { OID  fragment = (*(l))[1];
    skip_list(l,1);
    { OID  x = GC_OID(eval_any(GC_OID((*Core.read)(fragment))));
      if (equal_string(opt,"-princ") == CTRUE)
       (*Kernel.princ)(x);
      else if (equal_string(opt,"-print") == CTRUE)
       print_any(x);
      }
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: option_usage(g0697:{"-x", "-xe", "-x?-?", "-xe?-?"}) [NEW_ALLOC]
tuple * option_usage_string15_Reader_(char *g0697)
{ return option_usage_string15_Reader(g0697)->copyIfNeeded();}


// The c++ function for: option_usage(opt:{"-xe?-?", "-x?-?", "-xe", "-x"}) [NEW_ALLOC]
tuple * option_usage_string15_Reader(char *opt)
{ GC_BIND;
  { tuple *Result ;
    Result = tuple::allocStack(3,_string_("Load script"),
      _string_("{-x | -xe | -x<S:(0 .. 9)>-<W:(0 .. 9)> | -xe<S:(0 .. 9)>-<W:(0 .. 9)>} <file:path> [<args>]"),
      GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string("Load the CLAIRE file <file> with implicit options -nologo and -q. ","If the option starts with -xe the file is assumed to contain CLAIRE expressions. ")),"When <S> and <W> are specified they are used to inititalize CLAIRE memory (see -s option). ")),"Unix users may use this option for for a shell script header (e.g #!/usr/local/bin/claire -x). ")),"If the shell command contains any arguments (<args>) one should handle them in the srcipt through ")),"the system variable 'system.params'.\n"))));
    GC_UNBIND; return (Result);}
  }


// The c++ function for: option_respond(opt:{"-xe?-?", "-x?-?", "-xe", "-x"},l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  option_respond_string12_Reader(char *opt,list *l)
{ if (boolean_I_any(_oid_(l)) != CTRUE)
   close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
  { OID  path = (*(l))[1];
    skip_list(l,1);
    { ClaireHandler c_handle = ClaireHandler();
      if ERROR_IN 
      { { if (equal_string(left_string(opt,3),"-xe") == CTRUE)
           eload_string(string_v(path));
          else (*Reader.load)(path);
            shrink_list(l,0);
          }
        ERROR_FREE;}
      else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
      { c_handle.catchIt();{ print_exception_void();
          CL_exit(1);
          }
        }
      else PREVIOUS_HANDLER;}
    CL_exit(0);
    }
  POP_SIGNAL;}


//(inlineok?(eof? @ port, "lambda[(p:port),eof_port?(p)]"))

