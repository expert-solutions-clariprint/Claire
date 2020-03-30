/***** CLAIRE Compilation of file ./meta/pretty.cl 
         [version 3.5.0 / safety 5] *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllexport)
#endif
#include <Language.h>

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllimport)
#endif

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllexport)
#endif

//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| pretty.cl                                                   |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+
// ---------------------------------------------------------------------
// Contents:
//   Part 1: unbound_symbol and variables
//   Part 2: lambdas
//   Part 3: close methods for lattice_set instantiation
//   Part 4: Pretty printing
// ---------------------------------------------------------------------
//<sb> this is for the debugger, let the reader make something
// DEBUG? controls weither the code should be equiped for debug
//<sb> map locations of instructions
// The c++ function for: close(self:Instruction) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT Instruction * close_Instruction1(Instruction *self) { 
    if ((OBJECT(ClaireBoolean,Language.CAN_INIT_LOCATION_ask->value)) == CTRUE)
     (*Language.init_location)(_oid_(self));
    POP_SIGNAL; return (self);}
  


// The c++ function for: option_respond(opt:{"-debug"},l:list[string]) [0]
CL_EXPORT void  option_respond_string50_Language(char *opt,list *l) { 
    (Language.DEBUG_ask->value= Kernel.ctrue);
    POP_SIGNAL;}
  


// The c++ function for: option_usage(g0332:{"-debug"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string34_Language_(char *g0332) { 
    return option_usage_string34_Language(g0332)->copyIfNeeded();
}


// The c++ function for: option_usage(self:{"-debug"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string34_Language(char *self) { 
      { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Debugger")),
        _string_(((char*)"-debug")),
        _string_(((char*)"Make the loaded code instrumented for debug")));
      return (Result);}
    }
  


// The c++ function for: no_eval(self:Instruction) [SAFE_RESULT]
CL_EXPORT OID  no_eval_Instruction(Instruction *self) { 
    { OID Result = 0;
      { OID  V_CL0333;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[144] evaluate(~S) is not defined")),
          _oid_(list::alloc(1,_oid_(OWNER(_oid_(self))))))));
        
        Result=_void_(V_CL0333);}
      POP_SIGNAL; return (Result);}
    }
  


// import
// *********************************************************************
// *   Part 1: unbound_symbol and variables                            *
// *********************************************************************
// An unbound_symbol is created by the reader when a symbol is not bound
//
//unbound_symbol <: Basic_instruction(identifier:symbol)
// The c++ function for: self_print(self:unbound_symbol) [0]
CL_EXPORT void  self_print_unbound_symbol_Language(unbound_symbol *self) { 
    princ_symbol(self->name);
    POP_SIGNAL;}
  


// The c++ function for: self_eval(self:unbound_symbol) [NEW_ALLOC]
CL_EXPORT OID  self_eval_unbound_symbol(unbound_symbol *self) { 
    { OID Result = 0;
      if (INHERIT(owner_any(get_symbol(self->name)),Kernel._thing))
       Result = eval_any(get_symbol(self->name));
      else { OID  V_CL0334;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[145] the symbol ~A is unbound")),
            _oid_(list::alloc(1,_oid_(self->name))))));
          
          Result=_void_(V_CL0334);}
        POP_SIGNAL; return (Result);}
    }
  


//       else Serror(145, "The symbol ~A is unbound", list(self.name))) //<sb> made this error a syntax error
// A lexical variable is defined by a "Let" or inside a method's definition
//
// Lexical variables --------------------------------------------------
//
//<sb> tell that the variable is used for debug
// The c++ function for: self_print(self:Variable) [0]
CL_EXPORT void  self_print_Variable_Language(Variable *self) { 
    { symbol * s = self->pname;
      if (s == (NULL))
       princ_string(((char*)"<unamed variable?>"));
      else princ_symbol(s);
        }
    POP_SIGNAL;}
  


// The c++ function for: ppvariable(self:Variable) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  ppvariable_Variable(Variable *self) { 
    
    GC_BIND;
    if (((self->range == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     { princ_symbol(self->pname);
      princ_string(((char*)":"));
      printexp_any(GC_OID(_oid_(self->range)),CFALSE);
      }
    else princ_symbol(self->pname);
      GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: ppvariable(self:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  ppvariable_list(list *self) { 
    { ClaireBoolean * f = CTRUE;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(v);
        for (START(self); NEXT(v);)
        { if (f == CTRUE)
           f= (CFALSE);
          else princ_string(((char*)","));
            if (INHERIT(OWNER(v),Language._Variable))
           ppvariable_Variable(OBJECT(Variable,v));
          else print_any(v);
            }
        }
      }
    POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Variable) [0]
CL_EXPORT OID  self_eval_Variable(Variable *self) { 
    POP_SIGNAL; return (ClEnv->stack[((OID)((CL_INT)ClEnv->base+(CL_INT)self->index))]);}
  


// The c++ function for: write_value(self:Variable,val:any) [0]
CL_EXPORT OID  write_value_Variable(Variable *self,OID val) { 
    { OID Result = 0;
      if ((self->range == (NULL)) || 
          (belong_to(val,_oid_(self->range)) == CTRUE))
       Result = (ClEnv->stack[((OID)((CL_INT)ClEnv->base+(CL_INT)self->index))]=val);
      else { OID  V_CL0335;close_exception(((range_error *) (*Core._range_error)(_oid_(self),
            val,
            _oid_(self->range))));
          
          Result=_void_(V_CL0335);}
        POP_SIGNAL; return (Result);}
    }
  


// this is the definition of a typed variable
//
// The c++ function for: self_eval(self:Vardef) [0]
CL_EXPORT OID  self_eval_Vardef(Vardef *self) { 
    { OID Result = 0;
      { OID  i = ((OID)self->index);
        if (i != CNULL)
         Result = ClEnv->stack[((OID)((CL_INT)ClEnv->base+(CL_INT)(((CL_INT)i))))];
        else { OID  V_CL0336;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[146] The variable ~S is not defined")),
              _oid_(list::alloc(1,_oid_(self))))));
            
            Result=_void_(V_CL0336);}
          }
      POP_SIGNAL; return (Result);}
    }
  


//   [self_print(self:Vardef) : any -> ppvariable(self) ]
// global_variables are defined in exception ? ---------------------------
// a global variable is a named object with a special evaluation
//
// The c++ function for: self_eval(self:global_variable) [RETURN_ARG]
CL_EXPORT OID  self_eval_global_variable(global_variable *self) { 
    POP_SIGNAL; return (self->value);}
  


// The c++ function for: write_value(self:global_variable,val:any) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  write_value_global_variable(global_variable *self,OID val) { 
    { OID Result = 0;
      if (belong_to(val,_oid_(self->range)) == CTRUE)
       { put_store_property2(Kernel.value,self,val,self->store_ask);
        Result = val;
        }
      else { OID  V_CL0337;close_exception(((range_error *) (*Core._range_error)(_oid_(self),
            val,
            _oid_(self->range))));
          
          Result=_void_(V_CL0337);}
        POP_SIGNAL; return (Result);}
    }
  


// v0.01
// same as C //<sb> moved in Core
//EOF :: global_variable(range = char, value = char!(externC("((CL_INT) EOF)",integer))) // v3.2.52
//EOS :: global_variable(range = char, value = char!(0))
// v3.4
// @doc integer
// This global variable is the greatest supported integer in CLAIRE.
// This is a 30 bit value (integers in CLAIRE are coded on 30 bits).
// This value can be used in code that require a big integer value as
// in the following sample :
// \code
// my_min(l:list[integer]) : integer ->
// 	let minima := MAX_INTEGER
// 	in (for i in l
// 			(if (i < minima) minima := i),
// 		minima)
// \/code
// *********************************************************************
// *   Part 2: CLAIRE Lambdas                                           *
// *********************************************************************
// CLAIRE lambdas are the basic functional objects, defined by a filter
// and a piece of code. Lambda is defined in the "method" file.
// applying a lambda to a list of arguments
//
// @doc calls
// apply(self,%l) applies the lambda expression self to the argument list %l.
// The c++ function for: apply(self:lambda,%l:list) [NEW_ALLOC]
CL_EXPORT OID  apply_lambda(lambda *self,list *_Zl) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT  start = ClEnv->index;
        CL_INT  retour = ClEnv->base;
        (ClEnv->base= ((OID)start));
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(_Zx);
          for (START(_Zl); NEXT(_Zx);)
          PUSH(_Zx);
          }
        stack_add(self->dimension);
        { OID  val = GC_OID(OPT_EVAL(self->body));
          (ClEnv->base= ((OID)retour));
          (ClEnv->index= ((OID)start));
          Result = val;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: call(self:lambda,l:listargs) [NEW_ALLOC]
CL_EXPORT OID  call_lambda2(lambda *self,listargs *l) { 
    POP_SIGNAL; return (apply_lambda(self,l));}
  


// printing a lambda
//
// The c++ function for: self_print(self:lambda) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_print_lambda_Language(lambda *self) { 
    
    GC_BIND;
    princ_string(((char*)"lambda[("));
    ppvariable_list(GC_OBJECT(list,self->vars));
    princ_string(((char*)"),"));
    lbreak_integer(1);
    print_any(GC_OID(self->body));
    _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)1));
    { OID Result = 0;
      princ_string(((char*)"]"));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// lambda! and flexical_build communicate via a global_variable, which
// however is only used in this file (and also by cfile :-) ):
//
// creating a lambda from an instruction and a list of variables
// The c++ function for: iClaire/lambda!(lvar:list,self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT lambda * lambda_I_list(list *lvar,OID self) { 
    
    GC_BIND;
    (Language._starvariable_index_star->value= ((OID)0));
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v);
      for (START(lvar); NEXT(v);)
      { _void_(OBJECT(Variable,v)->index = ((CL_INT)Language._starvariable_index_star->value));
        _void_(OBJECT(ClaireObject,v)->isa = Language._Variable);
        (Language._starvariable_index_star->value= ((OID)((CL_INT)(((CL_INT)Language._starvariable_index_star->value))+(CL_INT)1)));
        }
      }
    { lambda *Result ;
      { OID  corps = GC_OID(lexical_build_any(self,lvar,((CL_INT)Language._starvariable_index_star->value)));
        lambda * resultat = GC_OBJECT(lambda,((lambda *) new_object_class(Core._lambda)));
        _void_(resultat->vars = lvar);
        _void_(resultat->body = corps);
        _void_(resultat->dimension = ((CL_INT)Language._starvariable_index_star->value));
        if ((OBJECT(ClaireBoolean,Language.DEBUG_ask->value)) == CTRUE)
         (*Language.equip)(_oid_(resultat));
        Result = resultat;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// Give to each lexical variable its right position in the stack.
// We look for a named object or an unbound symbol to replace by a lexical
// variable.
// The number of variables is kept in the global_variable *variable_index*.
// On entry, n need not be equal to size(lvar) (see [case ...instruction]).
//
//CALL_ON_LEXICAL_BUILT?:boolean := false
//on_lexical_built:method := (princ @ string)
// The c++ function for: iClaire/lexical_build(self:any,lvar:list,n:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  lexical_build_any(OID self,list *lvar,int n) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  x = GC_OID(lexical_build_imp_any1(self,lvar,n));
        if ((OBJECT(ClaireBoolean,Language.DEBUG_ask->value)) == CTRUE)
         x= (GC_OID((*Language.equip)(x)));
        Result = x;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: lexical_build_imp(self:any,lvar:list,n:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  lexical_build_imp_any1(OID self,list *lvar,int n) { 
    
    GC_BIND;
    { OID Result = 0;
      if ((INHERIT(OWNER(self),Kernel._thing)) || 
          (INHERIT(OWNER(self),Kernel._unbound_symbol)))
       Result = lexical_change_any(self,lvar);
      else { if (INHERIT(OWNER(self),Language._Variable))
           { if (OBJECT(Variable,self)->index == (((CL_INT)CNULL)))
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[145] the symbol ~A is unbound")),
              _oid_(list::alloc(1,_oid_(OBJECT(Variable,self)->pname))))));
            ;}
          else if (INHERIT(OWNER(self),Language._Call))
           { OID  s = lexical_change_any(_oid_(OBJECT(Call,self)->selector),lvar);
            lexical_build_imp_any1(GC_OID(_oid_(OBJECT(Call,self)->args)),lvar,n);
            if (_oid_(OBJECT(Call,self)->selector) != s)
             { _void_(OBJECT(Call,self)->selector = Core.call);
              _void_(OBJECT(Call,self)->args = cons_any(s,GC_OBJECT(list,OBJECT(Call,self)->args)));
              }
            }
          else if (INHERIT(OWNER(self),Language._Instruction))
           { ClaireClass * _Ztype = OBJECT(ClaireObject,self)->isa;
            if (contain_ask_set(Language._Instruction_with_var->descendents,_oid_(_Ztype)) == CTRUE)
             { put_property2(Kernel.index,GC_OBJECT(ClaireObject,OBJECT(ClaireObject,(*Language.var)(self))),((OID)n));
              ++n;
              if ((CL_INT)n > (CL_INT)((CL_INT)Language._starvariable_index_star->value))
               (Language._starvariable_index_star->value= ((OID)n));
              }
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(s);
              for (START(_Ztype->slots); NEXT(s);)
              { OID  x = get_slot(OBJECT(slot,s),OBJECT(ClaireObject,self));
                if (((INHERIT(OWNER(x),Kernel._thing)) || 
                      (INHERIT(OWNER(x),Kernel._unbound_symbol))) && 
                    (OBJECT(restriction,s)->range == Kernel._any))
                 put_slot(OBJECT(slot,s),OBJECT(ClaireObject,self),lexical_change_any(x,lvar));
                else lexical_build_imp_any1(x,lvar,n);
                  }
              }
            }
          else if (INHERIT(OWNER(self),Kernel._bag))
           { CL_INT  _Zn = OBJECT(bag,self)->length;
            { CL_INT loop_handle = ClEnv->cHandle;
              while (((CL_INT)_Zn > (CL_INT)0))
              { { OID  x = (*(OBJECT(bag,self)))[_Zn];
                  if ((INHERIT(OWNER(x),Kernel._thing)) || 
                      (INHERIT(OWNER(x),Kernel._unbound_symbol)))
                   ((*(OBJECT(list,self)))[_Zn]=lexical_change_any(x,lvar));
                  else lexical_build_imp_any1(x,lvar,n);
                    }
                _Zn= (CL_INT)(((CL_INT)_Zn-(CL_INT)1));
                POP_SIGNAL;}
              }
            }
          else ;Result = self;
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/lexical_change(self:any,lvar:list) [0]
CL_EXPORT OID  lexical_change_any(OID self,list *lvar) { 
    { OID Result = 0;
      { OID  rep = self;
        symbol * _Zname = ((INHERIT(OWNER(self),Language._Variable)) ?
          OBJECT(Variable,self)->pname :
          extract_symbol_any(self) );
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(x);
          for (START(lvar); NEXT(x);)
          if (OBJECT(Variable,x)->pname == _Zname)
           rep= (x);
          }
        Result = rep;
        }
      POP_SIGNAL; return (Result);}
    }
  


// *******************************************************************
// *       Part 3: functions for lattice_set instantiation           *
// *******************************************************************
// close is the basic method called by an instantiation.
// Once the indexed list is built, we never call it again.
//
// The c++ function for: close(self:class) [SAFE_RESULT]
CL_EXPORT ClaireClass * close_class(ClaireClass *self) { 
    POP_SIGNAL; return (self);}
  


// Extract the symbol associated with self.
// This is useful e.g. when using read() (read@port, read@string).
//
// The c++ function for: iClaire/extract_symbol(self:any) [RETURN_ARG]
CL_EXPORT symbol * extract_symbol_any(OID self) { 
    { symbol *Result ;
      { ClaireObject *V_CC ;
        if (INHERIT(OWNER(self),Kernel._unbound_symbol))
         V_CC = OBJECT(unbound_symbol,self)->name;
        else if (INHERIT(OWNER(self),Kernel._thing))
         V_CC = OBJECT(thing,self)->name;
        else if (INHERIT(OWNER(self),Kernel._class))
         V_CC = OBJECT(ClaireClass,self)->name;
        else if (INHERIT(OWNER(self),Kernel._symbol))
         V_CC = OBJECT(symbol,self);
        else if (INHERIT(OWNER(self),Language._Variable))
         V_CC = OBJECT(Variable,self)->pname;
        else if (Kernel._boolean == OWNER(self))
         { V_CC = (((OBJECT(ClaireBoolean,self)) == CTRUE) ?
            symbol_I_string2(((char*)"true")) :
            symbol_I_string2(((char*)"nil")) );
          }
        else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[147] a name cannot be made from ~S")),
            _oid_(list::alloc(1,self)))));
          Result= (symbol *) V_CC;}
      POP_SIGNAL; return (Result);}
    }
  


// we must be sure that the selector (in a has statement or in a message)
// is a property.
//
// The c++ function for: iClaire/make_a_property(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT property * make_a_property_any(OID self) { 
    
    GC_BIND;
    { property *Result ;
      { ClaireObject *V_CC ;
        if (INHERIT(OWNER(self),Core._global_variable))
         V_CC = make_a_property_any(GC_OID(OBJECT(global_variable,self)->value));
        else if (INHERIT(OWNER(self),Kernel._property))
         V_CC = OBJECT(property,self);
        else if (INHERIT(OWNER(self),Kernel._symbol))
         { OID  x = get_symbol(OBJECT(symbol,self));
          if (INHERIT(OWNER(x),Kernel._property))
           V_CC = make_a_property_any(x);
          else if (INHERIT(OWNER(x),Core._global_variable))
           V_CC = make_a_property_any(GC_OID(OBJECT(global_variable,x)->value));
          else { property * p = ((property *) new_thing_class(Kernel._property,OBJECT(symbol,self)));
              _void_(p->comment = string_I_symbol(OBJECT(symbol,self)));
              _void_(p->domain = Kernel._any);
              _void_(p->range = Kernel._any);
              V_CC = p;
              }
            }
        else if (INHERIT(OWNER(self),Kernel._unbound_symbol))
         V_CC = make_a_property_any(_oid_(OBJECT(unbound_symbol,self)->name));
        else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[148] Wrong selector: ~S, cannot make a property\n")),
            _oid_(list::alloc(1,self)))));
          Result= (property *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// *********************************************************************
// *  Part 4: Pretty printing                                          *
// *********************************************************************
// fuck
// The c++ function for: lbreak(_CL_obj:void) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  lbreak_void() { 
    { OID Result = 0;
      if (Core.pretty->pprint == CTRUE)
       { if (Core.pretty->pbreak == CTRUE)
         { princ_string(((char*)"\n"));
          put_buffer_void();
          Result = indent_integer(Core.pretty->index);
          }
        else if ((CL_INT)buffer_length_void() > (CL_INT)Core.pretty->width)
         { OID  V_CL0339;close_exception((ClaireException *) new_object_class(Core._much_too_far));
          
          Result=_void_(V_CL0339);}
        else Result = Kernel.cfalse;
          }
      else Result = Kernel.cfalse;
        POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: put_buffer(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  put_buffer_void() { 
    
    GC_BIND;
    { OID Result = 0;
      { char * buffer = GC_STRING(end_of_string_void());
        princ_string(buffer);
        print_in_string_void();
        Result = _oid_(Kernel.emptySet);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: checkfar(_CL_obj:void) [NEW_ALLOC]
CL_EXPORT OID  checkfar_void() { 
    { OID Result = 0;
      if ((Core.pretty->pprint == CTRUE) && 
          ((Core.pretty->pbreak != CTRUE) && 
            ((CL_INT)buffer_length_void() > (CL_INT)Core.pretty->width)))
       { OID  V_CL0340;close_exception((ClaireException *) new_object_class(Core._much_too_far));
        
        Result=_void_(V_CL0340);}
      else Result = Kernel.cfalse;
        POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: lbreak(n:integer) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  lbreak_integer(CL_INT n) { 
    _void_(Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)n));
    POP_SIGNAL; return (lbreak_void());}
  


// indentation
//
// The c++ function for: indent(limit:integer) [RETURN_ARG]
CL_EXPORT OID  indent_integer(CL_INT limit) { 
    { OID Result = 0;
      { CL_INT  x = buffer_length_void();
        { CL_INT loop_handle = ClEnv->cHandle;
          Result= _oid_(CFALSE);
          while (((CL_INT)x < (CL_INT)limit))
          { princ_string(((char*)" "));
            ++x;
            POP_SIGNAL;}
          }
        }
      POP_SIGNAL; return (Result);}
    }
  


// sets the current_level
// The c++ function for: set_level(_CL_obj:void) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  set_level_void() { 
    _void_(Core.pretty->index = ((CL_INT)buffer_length_void()-(CL_INT)1));
    POP_SIGNAL;}
  


// The c++ function for: set_level(n:integer) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  set_level_integer(CL_INT n) { 
    set_level_void();
    _void_(Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)n));
    POP_SIGNAL;}
  


// prints a bag as a box
//
// The c++ function for: printbox(self:bag,start:integer,finish:integer,s:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  printbox_bag1(bag *self,int start,int finish,char *s) { 
    { OID Result = 0;
      { CL_INT  i = 1;
        ClaireBoolean * startline = CTRUE;
        CL_INT  n = self->length;
        CL_INT  _Zl = Core.pretty->index;
        _void_(Core.pretty->index = start);
        if ((Core.pretty->pprint != CTRUE) || 
            ((short_enough_integer(((CL_INT)start+(CL_INT)10)) != CTRUE) && 
                (Core.pretty->pbreak == CTRUE)))
         printl_bag(self,s);
        else if (Core.pretty->pbreak != CTRUE)
         printl_bag(self,s);
        else { CL_INT loop_handle = ClEnv->cHandle;
            while (((CL_INT)i <= (CL_INT)n))
            { { CL_INT loop_handle = ClEnv->cHandle;
                while (((CL_INT)buffer_length_void() < (CL_INT)start))
                { princ_string(((char*)" "));
                  POP_SIGNAL;}
                }
              { CL_INT  idx = buffer_length_void();
                { ClaireHandler c_handle = ClaireHandler();
                  if ERROR_IN 
                  { { _void_(Core.pretty->pbreak = CFALSE);
                      printexp_any((*(self))[i],CTRUE);
                      _void_(Core.pretty->pbreak = CTRUE);
                      }
                    ERROR_FREE;}
                  else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Core._much_too_far)) == CTRUE)
                  { c_handle.catchIt();{ _void_(Core.pretty->pbreak = CTRUE);
                      _void_(Core.pretty->index = start);
                      }
                    }
                  else PREVIOUS_HANDLER;}
                if (i != n)
                 princ_string(s);
                if ((CL_INT)buffer_length_void() < (CL_INT)finish)
                 { ++i;
                  startline= (CFALSE);
                  }
                else { buffer_set_length_integer(idx);
                    if (startline != CTRUE)
                     { lbreak_void();
                      startline= (CTRUE);
                      }
                    else { set_level_void();
                        _void_(Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)1));
                        printexp_any((*(self))[i],CTRUE);
                        _void_(Core.pretty->index = _Zl);
                        if (i != n)
                         { princ_string(s);
                          lbreak_void();
                          }
                        ++i;
                        }
                      }
                  }
              POP_SIGNAL;}
            }
          _void_(Core.pretty->index = _Zl);
        Result = CNULL;
        }
      POP_SIGNAL; return (Result);}
    }
  


// default value of arguments
//
// The c++ function for: printbox(self:bag) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  printbox_bag2(bag *self) { 
    POP_SIGNAL; return (printbox_bag1(self,buffer_length_void(),Core.pretty->width,((char*)", ")));}
  


// The c++ function for: printbox(self:bag,s:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  printbox_bag3(bag *self,char *s) { 
    POP_SIGNAL; return (printbox_bag1(self,buffer_length_void(),Core.pretty->width,s));}
  


// The c++ function for: printl(self:bag,s:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  printl_bag(bag *self,char *s) { 
    
    GC_BIND;
    { ClaireBoolean * f = CTRUE;
      ClaireBoolean * b = Core.pretty->pprint;
      _void_(Core.pretty->pprint = CFALSE);
      { ClaireHandler c_handle = ClaireHandler();
        if ERROR_IN 
        { { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(x);
            for (START(self); NEXT(x);)
            { if (f == CTRUE)
               f= (CFALSE);
              else princ_string(s);
                printexp_any(x,CTRUE);
              if ((b == CTRUE) && 
                  ((Core.pretty->pbreak != CTRUE) && 
                    ((CL_INT)buffer_length_void() > (CL_INT)Core.pretty->width)))
               { _void_(Core.pretty->pprint = b);
                close_exception((ClaireException *) new_object_class(Core._much_too_far));
                }
              }
            }
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._system_error)) == CTRUE)
        { c_handle.catchIt();{ ClaireException * x = GC_OBJECT(ClaireException,ClEnv->exception_I);
            if ((b == CTRUE) && 
                (CLREAD(system_error,x,index) == 16))
             { _void_(Core.pretty->pprint = b);
              close_exception((ClaireException *) new_object_class(Core._much_too_far));
              }
            else close_exception(x);
              }
          }
        else PREVIOUS_HANDLER;}
      _void_(Core.pretty->pprint = b);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// print bounded prints a bounded expression using ( and )
// The c++ function for: printexp(self:any,comp:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  printexp_any(OID self,ClaireBoolean *comp) { 
    if (((INHERIT(OWNER(self),Language._Call)) && (((INHERIT(OBJECT(Call,self)->selector->isa,Kernel._operation)) ? ((comp != CTRUE) ? ((OBJECT(Call,self)->args->length == 2) ? CTRUE: CFALSE): CFALSE): CFALSE) != CTRUE)) || 
        ((INHERIT(OWNER(self),Language._Collect)) || 
          ((INHERIT(OWNER(self),Language._Select)) || 
            ((INHERIT(OWNER(self),Language._Definition)) || 
              ((INHERIT(OWNER(self),Language._Construct)) || 
                ((INHERIT(OWNER(self),Language._Do)) || 
                  ((self == CNULL) || 
                    ((INHERIT(OWNER(self),Language._And)) || 
                      ((INHERIT(OWNER(self),Kernel._cl_import)) || 
                        ((INHERIT(OWNER(self),Language._Or)) || 
                          ((INHERIT(OWNER(self),Language._If)) || 
                            ((INHERIT(OWNER(self),Kernel._restriction)) || 
                              ((INHERIT(OWNER(self),Kernel._unbound_symbol)) || 
                                ((INHERIT(OWNER(self),Language._Variable)) || 
                                  (inherit_ask_class(OWNER(self),Language._Instruction) != CTRUE)))))))))))))))
     print_any(self);
    else { CL_INT  _Zl = Core.pretty->index;
        princ_string(((char*)"("));
        set_level_integer(1);
        print_any(self);
        princ_string(((char*)")"));
        _void_(Core.pretty->index = _Zl);
        }
      POP_SIGNAL;}
  


// The c++ function for: pretty_print(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  pretty_print_any(OID self) { 
    print_in_string_void();
    _void_(Core.pretty->pprint = CTRUE);
    _void_(Core.pretty->pbreak = CTRUE);
    _void_(Core.pretty->index = 0);
    print_any(self);
    _void_(Core.pretty->pprint = CFALSE);
    princ_string(end_of_string_void());
    POP_SIGNAL;}
  


// The c++ function for: self_print(self:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_list_Language(list *self) { 
    if (equal(_oid_(of_bag(self)),_oid_(Kernel.emptySet)) != CTRUE)
     { princ_string(((char*)"list<"));
      print_any(_oid_(of_bag(self)));
      princ_string(((char*)">"));
      }
    { princ_string(((char*)"("));
      printbox_bag2(self);
      princ_string(((char*)")"));
      }
    POP_SIGNAL;}
  


// The c++ function for: self_print(self:set) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_set_Language(set *self) { 
    if (equal(_oid_(of_bag(self)),_oid_(Kernel.emptySet)) == CTRUE)
     { princ_string(((char*)"{"));
      printbox_bag2(self);
      princ_string(((char*)"}"));
      }
    else { princ_string(((char*)"set<"));
        print_any(_oid_(of_bag(self)));
        princ_string(((char*)">"));
        princ_string(((char*)"("));
        printbox_bag2(self);
        princ_string(((char*)")"));
        }
      POP_SIGNAL;}
  


// to remove !
// The c++ function for: self_print(self:tuple) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_tuple_Language(tuple *self) { 
    princ_string(((char*)"tuple("));
    printbox_bag2(self);
    princ_string(((char*)")"));
    POP_SIGNAL;}
  


// bend of file

/***** CLAIRE Compilation of file ./meta/call.cl 
         [version 3.5.0 / safety 5] *****/


//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| call.cl                                                     |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+
// -----------------------------------------------------------------
// This file holds the definition of functional calls in CLAIRE
// -----------------------------------------------------------------
// *********************************************************************
// * Contents                                                          *
// *      Part 1: the basic object messages                            *
// *      Part 2: Basic structures                                     *
// *      Part 3: Specialized structures                               *
// *      Part 4: Functions on instructions                            *
// *********************************************************************
// *********************************************************************
// *      Part 1: the basic object messages                            *
// *********************************************************************
// contains the last message that was evaluated
// messages in CLAIRE are called calls --------------------------------
//
//<sb> tells how to print ?>....<?
// The c++ function for: self_print(self:Princ_wcl) [NEW_ALLOC]
CL_EXPORT void  self_print_Princ_wcl1_Language(Princ_wcl *self) { 
    
    GC_BIND;
    princ_string(((char*)"?>"));
    (*Kernel.princ)((*(self->args))[1]);
    princ_string(((char*)"<?"));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_print(self:Call_wcl) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_Call_wcl1_Language(Call_wcl *self) { 
    
    GC_BIND;
    if (self->selector == Language.echo)
     princ_string(((char*)"= "));
    else if (self->selector == Language.self_html)
     princ_string(((char*)"== "));
    else { princ_string(self->selector->name->name);
        princ_string(((char*)" "));
        }
      print_any(GC_OID((*(self->args))[1]));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_print(self:Call) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_print_Call_Language(Call *self) { 
    
    GC_BIND;
    { CL_INT  _Zl = Core.pretty->index;
      property * _Zs = self->selector;
      list * _Za = GC_OBJECT(list,self->args);
      if ((INHERIT(_Zs->isa,Kernel._operation)) && 
          (_Za->length == 2))
       { _void_(Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)2));
        printe_any((*(_Za))[1],_Zs);
        princ_string(((char*)" "));
        print_any(_oid_(_Zs));
        princ_string(((char*)" "));
        lbreak_void();
        printe_any((*(_Za))[2],_Zs);
        }
      else if (_Zs == Kernel.nth)
       { if (_Za->length == 3)
         { printexp_any((*(_Za))[1],CFALSE);
          princ_string(((char*)"["));
          print_any((*(_Za))[2]);
          princ_string(((char*)","));
          print_any((*(_Za))[3]);
          princ_string(((char*)"]"));
          }
        else if (_Za->length == 1)
         { printexp_any((*(_Za))[1],CFALSE);
          princ_string(((char*)"[]"));
          }
        else { printexp_any((*(_Za))[1],CFALSE);
            princ_string(((char*)"["));
            if (_Za->length == 2)
             print_any((*(_Za))[2]);
            princ_string(((char*)"]"));
            }
          }
      else if ((_Zs == Kernel.nth_equal) && 
          ((CL_INT)3 <= (CL_INT)_Za->length))
       { OID  a = (*(_Za))[3];
        OID  o;
        if (INHERIT(OWNER(a),Language._Call))
         o = _oid_(OBJECT(Call,a)->selector);
        else o = Kernel.cfalse;
          if (_Za->length == 4)
         { printexp_any((*(_Za))[1],CFALSE);
          princ_string(((char*)"["));
          print_any((*(_Za))[2]);
          princ_string(((char*)","));
          print_any(a);
          princ_string(((char*)"] := "));
          lbreak_integer(2);
          print_any((*(_Za))[4]);
          }
        else { ClaireBoolean * g0345I;
          { OID  g0346UU;
            if (INHERIT(OWNER(a),Language._Call))
             g0346UU = (*(OBJECT(Call,a)->args))[1];
            else g0346UU = Kernel.cfalse;
              g0345I = sugar_ask_any((*(_Za))[1],(*(_Za))[2],o,g0346UU);
            }
          
          if (g0345I == CTRUE) { print_any((*(_Za))[1]);
              princ_string(((char*)"["));
              print_any((*(_Za))[2]);
              princ_string(((char*)"] :"));
              print_any(o);
              princ_string(((char*)" "));
              lbreak_integer(2);
              print_any(GC_OID((*(OBJECT(bag,(*Core.args)(a))))[2]));
              }
            else { print_any((*(_Za))[1]);
            princ_string(((char*)"["));
            print_any((*(_Za))[2]);
            princ_string(((char*)"] := "));
            lbreak_integer(2);
            print_any(a);
            }
          }
        }
      else if ((_Zs == Language.assign) && 
          (INHERIT(OWNER((*(_Za))[1]),Kernel._property)))
       { OID  a = (*(_Za))[3];
        OID  o;
        if (INHERIT(OWNER(a),Language._Call))
         o = _oid_(OBJECT(Call,a)->selector);
        else o = Kernel.cfalse;
          { ClaireBoolean * g0347I;
          { OID  g0348UU;
            if (INHERIT(OWNER(a),Language._Call))
             g0348UU = (*(OBJECT(Call,a)->args))[1];
            else g0348UU = Kernel.cfalse;
              g0347I = sugar_ask_any((*(_Za))[1],(*(_Za))[2],o,g0348UU);
            }
          
          if (g0347I == CTRUE) { print_any((*(_Za))[1]);
              princ_string(((char*)"("));
              print_any((*(_Za))[2]);
              princ_string(((char*)") :"));
              print_any(o);
              princ_string(((char*)" "));
              lbreak_integer(2);
              print_any(GC_OID((*(OBJECT(bag,(*Core.args)(a))))[2]));
              }
            else { print_any((*(_Za))[1]);
            princ_string(((char*)"("));
            print_any((*(_Za))[2]);
            princ_string(((char*)") := "));
            lbreak_integer(2);
            print_any((*(_Za))[3]);
            }
          }
        }
      else if ((_Zs == Kernel.add) && 
          (INHERIT(OWNER((*(_Za))[1]),Kernel._property)))
       { print_any((*(_Za))[1]);
        princ_string(((char*)"("));
        print_any((*(_Za))[2]);
        princ_string(((char*)") :add "));
        lbreak_integer(2);
        print_any((*(_Za))[3]);
        }
      else if ((_Zs == Kernel._delete) && 
          (INHERIT(OWNER((*(_Za))[1]),Kernel._property)))
       { print_any((*(_Za))[1]);
        princ_string(((char*)"("));
        print_any((*(_Za))[2]);
        princ_string(((char*)") :delete "));
        lbreak_integer(2);
        print_any((*(_Za))[3]);
        }
      else if (((*(_Za))[1] == _oid_(ClEnv)) && 
          (_Za->length == 1))
       { print_any(_oid_(_Zs));
        princ_string(((char*)"()"));
        }
      else { print_any(_oid_(_Zs));
          princ_string(((char*)"("));
          set_level_void();
          printbox_bag2(_Za);
          princ_string(((char*)")"));
          }
        _void_(Core.pretty->index = _Zl);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_print(self:Call+) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_print_Call_plus_Language(Call_plus *self) { 
    
    GC_BIND;
    printexp_any(GC_OID((*(self->args))[1]),CTRUE);
    princ_string(((char*)"."));
    { OID Result = 0;
      print_any(_oid_(self->selector));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: self_eval(self:Call) [SAFE_GC]
CL_EXPORT OID  self_eval_Call(Call *self) { 
    if (ClEnv->debug_I != ((CL_INT)-1))
     PUSH(_oid_(self));
    { OID Result = 0;
      { CL_INT  start = ClEnv->index;
        property * p = self->selector;
        if ((CL_INT)0 <= (CL_INT)ClEnv->debug_I)
         (Language.LastCall->value= _oid_(self));
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(x);
          bag *x_support;
          x_support = self->args;
          for (START(x_support); NEXT(x);)
          PUSH(OPT_EVAL(x));
          }
        { OID  rx = eval_message_property(p,find_which_property1(p,start,OWNER(ClEnv->stack[((OID)start)])),start,CTRUE);
          if ((CL_INT)0 <= (CL_INT)ClEnv->debug_I)
           (Language.LastCall->value= _oid_(self));
          if (ClEnv->debug_I != ((CL_INT)-1))
           (ClEnv->index= ((OID)((CL_INT)start-(CL_INT)1)));
          Result = rx;
          }
        }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: self_eval(self:Call+) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_eval_Call_plus(Call_plus *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT  back_index = ClEnv->index;
        CL_INT  back_debug = ClEnv->debug_I;
        if (ClEnv->debug_I != ((CL_INT)-1))
         { CL_INT  d_I = ClEnv->debug_I;
          CL_INT  st = ((CL_INT)1+(CL_INT)ClEnv->index);
          PUSH(_oid_(self));
          PUSH(_oid_(self->selector));
          PUSH((*(self->args))[1]);
          _void_(ClEnv->debug_I = ClEnv->index);
          PUSH(((OID)d_I));
          PUSH(_oid_(Core.read));
          PUSH(((OID)2));
          PUSH(((OID)st));
          }
        { property * p = self->selector;
          OID  x = GC_OID(eval_any(GC_OID((*(self->args))[1])));
          ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(p,OWNER(x)));
          if (equal(_oid_(OWNER(_oid_(s))),_oid_(Kernel._slot)) != CTRUE)
           { OID  V_CL0353;close_exception(((selector_error *) (*Core._selector_error)(_oid_(p),
              _oid_(list::alloc(1,x)))));
            
            Result=_void_(V_CL0353);}
          else { (*Core.preread)(_oid_(p),
                x);
              { OID  z = slot_get_object(OBJECT(ClaireObject,x),CLREAD(slot,s,index),CLREAD(slot,s,srange));
                if ((z != CNULL) || 
                    (belong_to(z,(*Kernel.range)(_oid_(s))) == CTRUE))
                 { CL_INT  n = ClEnv->trace_I;
                  CL_INT  d = ClEnv->debug_I;
                  if (((CL_INT)n > (CL_INT)0) && 
                      (n == ClEnv->step_I))
                   { _void_(ClEnv->trace_I = 0);
                    _void_(ClEnv->debug_I = -1);
                    { CL_INT  g0349 = (CL_INT )(current_color);
                      CL_INT  g0350 = (CL_INT )(current_bold);
                      CL_INT  g0351 = g0349;
                      CL_INT  g0352 = g0350;
                      color(g0349,g0350);
                      color_princ_string1(((char*)"  `GREENread: "));
                      g0349= (CL_INT)((CL_INT )(current_color));
                      g0350= (CL_INT)((CL_INT )(current_bold));
                      color(g0351,g0352);
                      print_any(_oid_(p));
                      color(g0349,g0350);
                      color(g0349,g0350);
                      color_princ_string1(((char*)"("));
                      g0349= (CL_INT)((CL_INT )(current_color));
                      g0350= (CL_INT)((CL_INT )(current_bold));
                      color(g0351,g0352);
                      print_any(x);
                      color(g0349,g0350);
                      color(g0349,g0350);
                      color_princ_string1(((char*)") = "));
                      g0349= (CL_INT)((CL_INT )(current_color));
                      g0350= (CL_INT)((CL_INT )(current_bold));
                      color(g0351,g0352);
                      print_any(z);
                      color(g0349,g0350);
                      color(g0349,g0350);
                      color_princ_string1(((char*)"\n"));
                      color(g0351,g0352);
                      }
                    _void_(ClEnv->debug_I = d);
                    _void_(ClEnv->trace_I = n);
                    }
                  (ClEnv->index= ((OID)back_index));
                  _void_(ClEnv->debug_I = back_debug);
                  Result = z;
                  }
                else { OID  V_CL0354;close_exception(((read_slot_error *) (*Core._read_slot_error)(x,
                      _oid_(p))));
                    
                    Result=_void_(V_CL0354);}
                  }
              }
            }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// recursive printing of bicall
//
// The c++ function for: printe(self:any,s:property) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  printe_any(OID self,property *s) { 
    if ((INHERIT(OWNER(self),Language._Call)) && ((INHERIT(OBJECT(Call,self)->selector->isa,Kernel._operation)) && 
        (OBJECT(Call,self)->args->length == 2)))
     { if (CTRUE == CTRUE)
       { princ_string(((char*)"("));
        print_any(self);
        princ_string(((char*)")"));
        }
      else printexp_any(self,CTRUE);
        }
    else printexp_any(self,CTRUE);
      POP_SIGNAL;}
  


// tells if the sugar :op can be used
//
// The c++ function for: sugar?(x:any,x2:any,o:any,a:any) [0]
CL_EXPORT ClaireBoolean * sugar_ask_any(OID x,OID x2,OID o,OID a) { 
    { ClaireBoolean *Result ;
      Result = ((INHERIT(OWNER(o),Kernel._operation)) ?
        ((INHERIT(OWNER(x),Kernel._property)) ?
          ((INHERIT(OWNER(a),Language._Call)) ?
            ((x == _oid_(OBJECT(Call,a)->selector)) ? ((equal((*(OBJECT(Call,a)->args))[1],x2) == CTRUE) ? CTRUE: CFALSE): CFALSE) :
            CFALSE ) :
          CFALSE ) :
        (((INHERIT(OWNER(o),Language._Variable)) || 
            (INHERIT(OWNER(o),Core._global_variable))) ?
          equal(x,a) :
          ((INHERIT(OWNER(a),Language._Call)) ?
            ((OBJECT(Call,a)->selector == Kernel.nth) ? ((equal((*(OBJECT(Call,a)->args))[1],x) == CTRUE) ? ((equal((*(OBJECT(Call,a)->args))[2],x2) == CTRUE) ? CTRUE: CFALSE): CFALSE): CFALSE) :
            CFALSE ) ) );
      POP_SIGNAL; return (Result);}
    }
  


// *********************************************************************
// *      Part 2: Basic structures                                     *
// *********************************************************************
// ------------------ assignment ---------------------------------------
// <-(var V, arg E) where V is a variable (and therefore NOT a global_variable)
//
// the var slot is filled with a real variable later.
// The c++ function for: self_print(self:Assign) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_print_Assign_Language(Assign *self) { 
    
    GC_BIND;
    { OID  a = GC_OID(self->arg);
      OID  o;
      if (INHERIT(OWNER(a),Language._Call))
       o = _oid_(OBJECT(Call,a)->selector);
      else o = Kernel.cfalse;
        { ClaireBoolean * g0360I;
        { OID  g0361UU;
          if (INHERIT(OWNER(a),Language._Call))
           g0361UU = (*(OBJECT(Call,a)->args))[1];
          else g0361UU = Kernel.cfalse;
            g0360I = sugar_ask_any(self->var,_oid_(Kernel.emptySet),o,g0361UU);
          }
        
        if (g0360I == CTRUE) { print_any(GC_OID(self->var));
            princ_string(((char*)" :"));
            print_any(o);
            princ_string(((char*)" "));
            lbreak_integer(2);
            printexp_any(GC_OID((*(OBJECT(bag,(*Core.args)(a))))[2]),CTRUE);
            }
          else { CL_INT  g0356 = (CL_INT )(current_color);
          CL_INT  g0357 = (CL_INT )(current_bold);
          CL_INT  g0358 = g0356;
          CL_INT  g0359 = g0357;
          color(g0358,g0359);
          print_any(GC_OID(self->var));
          color(g0356,g0357);
          color(g0356,g0357);
          color_princ_string1(((char*)" `BLUE:= `BLACK"));
          g0356= (CL_INT)((CL_INT )(current_color));
          g0357= (CL_INT)((CL_INT )(current_bold));
          color(g0358,g0359);
          lbreak_integer(2);
          color(g0356,g0357);
          color(g0358,g0359);
          printexp_any(a,CTRUE);
          color(g0356,g0357);
          color(g0358,g0359);
          }
        }
      _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Assign) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  self_eval_Assign(Assign *self) { 
    
    GC_BIND;
    { OID Result = 0;
      if (INHERIT(OWNER(self->var),Language._Variable))
       Result = write_value_Variable(GC_OBJECT(Variable,OBJECT(Variable,self->var)),GC_OID(OPT_EVAL(self->arg)));
      else { OID  V_CL0362;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[101] ~S is not a variable")),
            _oid_(list::alloc(1,self->var)))));
          
          Result=_void_(V_CL0362);}
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// global variables
//
// The c++ function for: self_print(self:Gassign) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_print_Gassign_Language(Gassign *self) { 
    
    GC_BIND;
    { OID  a = GC_OID(self->arg);
      OID  o;
      if (INHERIT(OWNER(a),Language._Call))
       o = _oid_(OBJECT(Call,a)->selector);
      else o = Kernel.cfalse;
        { ClaireBoolean * g0368I;
        { OID  g0369UU;
          if (INHERIT(OWNER(a),Language._Call))
           g0369UU = (*(OBJECT(Call,a)->args))[1];
          else g0369UU = Kernel.cfalse;
            g0368I = sugar_ask_any(_oid_(self->var),_oid_(Kernel.emptySet),o,g0369UU);
          }
        
        if (g0368I == CTRUE) { print_any(_oid_(self->var));
            princ_string(((char*)" :"));
            print_any(o);
            princ_string(((char*)" "));
            lbreak_integer(2);
            print_any(GC_OID((*(OBJECT(bag,(*Core.args)(a))))[2]));
            }
          else { CL_INT  g0364 = (CL_INT )(current_color);
          CL_INT  g0365 = (CL_INT )(current_bold);
          CL_INT  g0366 = g0364;
          CL_INT  g0367 = g0365;
          color(g0366,g0367);
          print_any(_oid_(self->var));
          color(g0364,g0365);
          color(g0364,g0365);
          color_princ_string1(((char*)" `BLUE:= `BLACK"));
          g0364= (CL_INT)((CL_INT )(current_color));
          g0365= (CL_INT)((CL_INT )(current_bold));
          color(g0366,g0367);
          lbreak_integer(2);
          color(g0364,g0365);
          color(g0366,g0367);
          print_any(a);
          color(g0364,g0365);
          color(g0366,g0367);
          }
        }
      _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Gassign) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  self_eval_Gassign(Gassign *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { global_variable * v = self->var;
        Result = write_value_global_variable(v,GC_OID(eval_any(GC_OID(self->arg))));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//--------------- BOOLEAN OPERATIONS ---------------------------------
// "and" is strictly boolean and is based on short-circuit evaluation.
//
// The c++ function for: self_print(self:And) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_And_Language(And *self) { 
    
    GC_BIND;
    princ_string(((char*)"("));
    printbox_bag3(GC_OBJECT(list,self->args),((char*)" & "));
    princ_string(((char*)")"));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:And) [NEW_ALLOC]
CL_EXPORT OID  self_eval_And(And *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireBoolean * V_CL0370;{ OID  g0371UU;
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(x);
            g0371UU= Kernel.cfalse;
            for (START(self->args); NEXT(x);)
            if (boolean_I_any(OPT_EVAL(x)) != CTRUE)
             { g0371UU = Kernel.ctrue;
              ClEnv->cHandle = loop_handle;break;}
            }
          V_CL0370 = not_any(g0371UU);
          }
        
        Result=_oid_(V_CL0370);}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// or expression
//
// The c++ function for: self_print(self:Or) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_Or_Language(Or *self) { 
    
    GC_BIND;
    princ_string(((char*)"("));
    printbox_bag3(GC_OBJECT(list,self->args),((char*)" | "));
    princ_string(((char*)")"));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Or) [NEW_ALLOC]
CL_EXPORT OID  self_eval_Or(Or *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireBoolean * g0372I;
        { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(x);
            V_C= Kernel.cfalse;
            for (START(self->args); NEXT(x);)
            if (boolean_I_any(OPT_EVAL(x)) == CTRUE)
             { V_C = Kernel.ctrue;
              ClEnv->cHandle = loop_handle;break;}
            }
          
          g0372I=OBJECT(ClaireBoolean,V_C);}
        
        if (g0372I == CTRUE) Result = Kernel.ctrue;
          else Result = Kernel.cfalse;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// ----------------- an anti-evaluator ---------------------------------
//
// The c++ function for: self_print(self:Quote) [NEW_ALLOC]
CL_EXPORT void  self_print_Quote_Language(Quote *self) { 
    
    GC_BIND;
    princ_string(((char*)"quote("));
    print_any(GC_OID(self->arg));
    princ_string(((char*)")"));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Quote) [RETURN_ARG]
CL_EXPORT OID  self_eval_Quote(Quote *self) { 
    POP_SIGNAL; return (self->arg);}
  


// *********************************************************************
// *      Part 3: Specialized structures                               *
// *********************************************************************
// optimized_instruction is the set of optimized messages.
// These are the forms produced by the optimizer. They correspond to basic
// kinds of evaluation.
//
// This is how a call to a compiled method can be compiled.
// We use the C external function
//
// The c++ function for: self_print(self:Call_method) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_Call_method_Language(Call_method *self) { 
    
    GC_BIND;
    print_any(_oid_(self->arg));
    princ_string(((char*)"("));
    princ_bag(GC_OBJECT(list,self->args));
    princ_string(((char*)")"));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Call_method) [NEW_ALLOC]
CL_EXPORT OID  self_eval_Call_method(Call_method *self) { 
    
    GC_BIND;
    if (ClEnv->debug_I != ((CL_INT)-1))
     PUSH(_oid_(self));
    { OID Result = 0;
      { CL_INT  start = ClEnv->index;
        method * Cprop = self->arg;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(x);
          for (START(self->args); NEXT(x);)
          { GC_LOOP;
            PUSH(GC_OID(OPT_EVAL(x)));
            GC_UNLOOP; POP_SIGNAL;}
          }
        { OID  r = GC_OID(execute_method(Cprop,start,CTRUE));
          if (ClEnv->debug_I != ((CL_INT)-1))
           (ClEnv->index= ((OID)((CL_INT)start-(CL_INT)1)));
          Result = r;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// same thing with one only argument: we do not use the stack
//
// The c++ function for: self_eval(self:Call_method1) [NEW_ALLOC]
CL_EXPORT OID  self_eval_Call_method1(Call_method1 *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { method * f = self->arg;
        list * l = self->args;
        Result = funcall_method1(f,GC_OID(OPT_EVAL((*(l))[1])));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// same thing with two arguments
//
// The c++ function for: self_eval(self:Call_method2) [NEW_ALLOC]
CL_EXPORT OID  self_eval_Call_method2(Call_method2 *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { method * f = self->arg;
        list * l = self->args;
        Result = funcall_method2(f,GC_OID(OPT_EVAL((*(l))[1])),GC_OID(OPT_EVAL((*(l))[2])));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// an instruction to read a slot
//
// The c++ function for: self_print(self:Call_slot) [NEW_ALLOC]
CL_EXPORT void  self_print_Call_slot_Language(Call_slot *self) { 
    
    GC_BIND;
    print_any(_oid_(self->selector));
    princ_string(((char*)"("));
    print_any(GC_OID(self->arg));
    princ_string(((char*)")"));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Call_slot) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  self_eval_Call_slot(Call_slot *self) { 
    
    GC_BIND;
    { OID Result = 0;
      Result = get_slot(self->selector,OBJECT(ClaireObject,OPT_EVAL(self->arg)));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// an instruction to read an array
// selector is an exp with type array, arg is an exp with type integer, and test
// contains the inferred member_type of the array
//
// The c++ function for: self_print(self:Call_array) [NEW_ALLOC]
CL_EXPORT void  self_print_Call_array_Language(Call_array *self) { 
    
    GC_BIND;
    print_any(GC_OID(self->selector));
    princ_string(((char*)"["));
    print_any(GC_OID(self->arg));
    princ_string(((char*)"]"));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Call_array) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  self_eval_Call_array(Call_array *self) { 
    
    GC_BIND;
    { OID Result = 0;
      Result = nth_array(array_v(OPT_EVAL(self->selector)),((CL_INT)OPT_EVAL(self->arg)));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// an instruction to read a table
//
// The c++ function for: self_print(self:Call_table) [NEW_ALLOC]
CL_EXPORT void  self_print_Call_table_Language(Call_table *self) { 
    
    GC_BIND;
    print_any(GC_OID(_oid_(self->selector)));
    princ_string(((char*)"["));
    print_any(GC_OID(self->arg));
    princ_string(((char*)"]"));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Call_table) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  self_eval_Call_table(Call_table *self) { 
    
    GC_BIND;
    { OID Result = 0;
      if (self->test == CTRUE)
       Result = nth_table1(self->selector,GC_OID(OPT_EVAL(self->arg)));
      else Result = get_table(self->selector,GC_OID(OPT_EVAL(self->arg)));
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// an instruction to write a slot
// the structure is complex: see ocall.cl
//
// The c++ function for: self_print(self:Update) [NEW_ALLOC]
CL_EXPORT void  self_print_Update_Language(Update *self) { 
    
    GC_BIND;
    print_any(GC_OID(self->selector));
    princ_string(((char*)"("));
    print_any(GC_OID((*Kernel.arg)(self->var)));
    princ_string(((char*)") := "));
    print_any(GC_OID(self->value));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Update) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_eval_Update(Update *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  s = GC_OID(self->selector);
        if (INHERIT(OWNER(s),Kernel._property))
         put_property2(OBJECT(property,s),GC_OBJECT(ClaireObject,OBJECT(ClaireObject,eval_any(GC_OID((*Kernel.arg)(self->var))))),GC_OID(eval_any(GC_OID(self->value))));
        else if (INHERIT(OWNER(s),Kernel._table))
         nth_equal_table1(OBJECT(table,s),GC_OID(eval_any(GC_OID((*Kernel.arg)(self->var)))),GC_OID(eval_any(GC_OID(self->value))));
        Result = CNULL;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// ------------------ SUPER: a jump in the set lattice ---------------
// A "super" allows one to execute a message as if the type of the receiver
// was a given abstract_class.
// However we require that the receiver be in the specified abstract_class.
// The form of the super is: SELECTOR@ABSTRACT_CLASS(RECEIVER , ...)
//
// The c++ function for: self_print(self:Super) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_print_Super_Language(Super *self) { 
    
    GC_BIND;
    { CL_INT  _Zl = Core.pretty->index;
      property * _Zs = self->selector;
      list * _Za = GC_OBJECT(list,self->args);
      print_any(_oid_(self->selector));
      princ_string(((char*)"@"));
      print_any(GC_OID(_oid_(self->cast_to)));
      princ_string(((char*)"("));
      set_level_void();
      printbox_bag2(_Za);
      princ_string(((char*)")"));
      _void_(Core.pretty->index = _Zl);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Super) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_eval_Super(Super *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT  start = ClEnv->index;
        ClaireType * t = GC_OBJECT(ClaireType,self->cast_to);
        ClaireClass * c = class_I_type(t);
        property * p = self->selector;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(x);
          bag *x_support;
          x_support = GC_OBJECT(list,self->args);
          for (START(x_support); NEXT(x);)
          { GC_LOOP;
            PUSH(GC_OID(OPT_EVAL(x)));
            GC_UNLOOP; POP_SIGNAL;}
          }
        Result = eval_message_property(p,find_which_class1(c,p->definition,start,(ClEnv->index)),start,CTRUE);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//--------------- comments ------------------------------------------
// the cast is the new form of simple super
//
// The c++ function for: self_print(x:Cast) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_Cast_Language(Cast *x) { 
    
    GC_BIND;
    { CL_INT  g0373 = (CL_INT )(current_color);
      CL_INT  g0374 = (CL_INT )(current_bold);
      CL_INT  g0375 = g0373;
      CL_INT  g0376 = g0374;
      color(g0375,g0376);
      printexp_any(GC_OID(x->arg),CFALSE);
      color(g0373,g0374);
      color(g0373,g0374);
      color_princ_string1(((char*)" `BLUEas `BLACK"));
      g0373= (CL_INT)((CL_INT )(current_color));
      g0374= (CL_INT)((CL_INT )(current_bold));
      color(g0375,g0376);
      printexp_any(GC_OID(_oid_(x->set_arg)),CFALSE);
      color(g0373,g0374);
      color(g0375,g0376);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Cast) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  self_eval_Cast(Cast *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  x = GC_OID(OPT_EVAL(self->arg));
        ClaireType * y = self->set_arg;
        if ((INHERIT(y->isa,Core._Param)) && (((CLREAD(Param,y,arg) == Kernel._list) || 
              (CLREAD(Param,y,arg) == Kernel._set)) && 
            (Kernel._set == OWNER((*(CLREAD(Param,y,args)))[1]))))
         Result = _oid_(check_in_bag(OBJECT(bag,x),Kernel._bag,GC_OBJECT(ClaireType,OBJECT(ClaireType,(*(OBJECT(set,(*(CLREAD(Param,y,args)))[1])))[1]))));
        else Result = check_in_any(x,y);
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// v3.3.16
// ----------------- return from a loop --------------------------------
//
// return_error is an exception that is handled by the "for" family
// of structures
//
// The c++ function for: self_print(self:Return) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_Return_Language(Return *self) { 
    
    GC_BIND;
    { CL_INT  g0379 = (CL_INT )(current_color);
      CL_INT  g0380 = (CL_INT )(current_bold);
      CL_INT  g0381 = g0379;
      CL_INT  g0382 = g0380;
      color(g0379,g0380);
      color_princ_string1(((char*)"`BLUEbreak`BLACK("));
      g0379= (CL_INT)((CL_INT )(current_color));
      g0380= (CL_INT)((CL_INT )(current_bold));
      color(g0381,g0382);
      _void_(Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)2));
      color(g0379,g0380);
      color(g0381,g0382);
      print_any(GC_OID(self->arg));
      color(g0379,g0380);
      color(g0381,g0382);
      _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
      color(g0379,g0380);
      color(g0379,g0380);
      color_princ_string1(((char*)")"));
      color(g0381,g0382);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Return) [NEW_ALLOC]
CL_EXPORT OID  self_eval_Return(Return *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  V_CL0383;close_exception(((return_error *) (*Core._return_error)(GC_OID(OPT_EVAL(self->arg)))));
        
        Result=_void_(V_CL0383);}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// ****************************************************************
// *       Part 4: Miscellaneous on instructions                  *
// ****************************************************************
// substitute any variable with same name as x with the value val
// The c++ function for: substitution(self:any,x:Variable,val:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  substitution_any(OID self,Variable *x,OID val) { 
    
    GC_BIND;
    { OID Result = 0;
      if (INHERIT(OWNER(self),Language._Variable))
       { if (OBJECT(Variable,self)->pname == x->pname)
         Result = val;
        else Result = self;
          }
      else if (INHERIT(OWNER(self),Kernel._thing))
       { if (OBJECT(thing,self)->name == x->pname)
         Result = val;
        else Result = self;
          }
      else if (INHERIT(OWNER(self),Kernel._bag))
       { { CL_INT  i = 1;
          CL_INT  g0384 = OBJECT(bag,self)->length;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)i <= (CL_INT)g0384))
            { GC_LOOP;
              if ((INHERIT(OWNER((*(OBJECT(bag,self)))[i]),Language._Variable)) || 
                  ((INHERIT(OWNER((*(OBJECT(bag,self)))[i]),Kernel._unbound_symbol)) || 
                    (INHERIT(OWNER((*(OBJECT(bag,self)))[i]),Kernel._thing))))
               ((*(OBJECT(list,self)))[i]=GC_OID(substitution_any((*(OBJECT(bag,self)))[i],x,val)));
              else substitution_any((*(OBJECT(bag,self)))[i],x,val);
                ++i;
              GC_UNLOOP;POP_SIGNAL;}
            }
          }
        Result = self;
        }
      else if (INHERIT(OWNER(self),Kernel._unbound_symbol))
       { if (OBJECT(unbound_symbol,self)->name == x->pname)
         Result = val;
        else Result = self;
          }
      else if (INHERIT(OWNER(self),Language._Instruction))
       { { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(s);
          bag *s_support;
          s_support = OWNER(self)->slots;
          for (START(s_support); NEXT(s);)
          { OID  y = get_slot(OBJECT(slot,s),OBJECT(ClaireObject,self));
            if ((INHERIT(OWNER(y),Language._Variable)) || 
                ((INHERIT(OWNER(y),Kernel._unbound_symbol)) || 
                  (INHERIT(OWNER(y),Kernel._thing))))
             put_slot(OBJECT(slot,s),OBJECT(ClaireObject,self),substitution_any(y,x,val));
            else substitution_any(y,x,val);
              }
          }
        Result = self;
        }
      else Result = self;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// count the number of occurrences of x
// The c++ function for: occurrence(self:any,x:Variable) [NEW_ALLOC]
CL_EXPORT CL_INT  occurrence_any(OID self,Variable *x) { 
    { CL_INT Result = 0;
      if (INHERIT(OWNER(self),Language._Variable))
       { Result = ((OBJECT(Variable,self)->pname == x->pname) ?
          1 :
          0 );
        }
      else if (INHERIT(OWNER(self),Kernel._bag))
       { CL_INT  n = 0;
        { CL_INT  i = 1;
          CL_INT  g0385 = OBJECT(bag,self)->length;
          { CL_INT loop_handle = ClEnv->cHandle;
            while (((CL_INT)i <= (CL_INT)g0385))
            { n= (CL_INT)(((CL_INT)n+(CL_INT)occurrence_any((*(OBJECT(bag,self)))[i],x)));
              ++i;
              POP_SIGNAL;}
            }
          }
        Result = n;
        }
      else if (INHERIT(OWNER(self),Kernel._unbound_symbol))
       { Result = ((OBJECT(unbound_symbol,self)->name == x->pname) ?
          1 :
          0 );
        }
      else if (INHERIT(OWNER(self),Language._Instruction))
       { CL_INT  n = 0;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(s);
          bag *s_support;
          s_support = OWNER(self)->slots;
          for (START(s_support); NEXT(s);)
          n= (CL_INT)(((CL_INT)n+(CL_INT)occurrence_any(get_slot(OBJECT(slot,s),OBJECT(ClaireObject,self)),x)));
          }
        Result = n;
        }
      else Result = 0;
        POP_SIGNAL; return (Result);}
    }
  


// makes a (deep) copy of the instruction self
//
// The c++ function for: instruction_copy(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  instruction_copy_any(OID self) { 
    
    GC_BIND;
    { OID Result = 0;
      if (INHERIT(OWNER(self),Kernel._bag))
       { bag * l = copy_bag(OBJECT(bag,self));
        { CL_INT  i = 1;
          CL_INT  g0386 = OBJECT(bag,self)->length;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)i <= (CL_INT)g0386))
            { GC_LOOP;
              ((*(((list *) l)))[i]=GC_OID(instruction_copy_any((*(OBJECT(bag,self)))[i])));
              ++i;
              GC_UNLOOP;POP_SIGNAL;}
            }
          }
        Result = _oid_(l);
        }
      else if (INHERIT(OWNER(self),Language._Variable))
       Result = self;
      else if (INHERIT(OWNER(self),Language._Instruction))
       { Instruction * o = GC_OBJECT(Instruction,((Instruction *) copy_object(OBJECT(ClaireObject,self))));
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(s);
          bag *s_support;
          s_support = OWNER(self)->slots;
          for (START(s_support); NEXT(s);)
          put_slot(OBJECT(slot,s),o,instruction_copy_any(get_slot(OBJECT(slot,s),OBJECT(ClaireObject,self))));
          }
        Result = _oid_(o);
        }
      else Result = self;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  



/***** CLAIRE Compilation of file ./meta/control.cl 
         [version 3.5.0 / safety 5] *****/


//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| control.cl                                                  |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+
// *********************************************************************
// *     Part 1: If, Do, Let                                           *
// *     Part 2: set control structures                                *
// *     Part 3: other control structures                              *
// *     Part 4: the constructs                                        *
// *********************************************************************
// *********************************************************************
// *     Part 1: If, Do, Let                                           *
// *********************************************************************
//--------------- the IF --------------------------------------------
// The c++ function for: self_print(self:If) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_If_Language(If *self) { 
    princ_string(((char*)"("));
    _void_(Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)1));
    printstat_If(self);
    _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)1));
    princ_string(((char*)")"));
    POP_SIGNAL;}
  


// The c++ function for: printstat(self:If) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  printstat_If(If *self) { 
    
    GC_BIND;
    { CL_INT  g0390 = (CL_INT )(current_color);
      CL_INT  g0391 = (CL_INT )(current_bold);
      CL_INT  g0392 = g0390;
      CL_INT  g0393 = g0391;
      color(g0390,g0391);
      color_princ_string1(((char*)"`BLUEif `BLACK"));
      g0390= (CL_INT)((CL_INT )(current_color));
      g0391= (CL_INT)((CL_INT )(current_bold));
      color(g0392,g0393);
      printexp_any(GC_OID(self->test),CFALSE);
      checkfar_void();
      color(g0390,g0391);
      color(g0390,g0391);
      color_princ_string1(((char*)" "));
      g0390= (CL_INT)((CL_INT )(current_color));
      g0391= (CL_INT)((CL_INT )(current_bold));
      color(g0392,g0393);
      printif_any(GC_OID(self->arg));
      color(g0390,g0391);
      color(g0392,g0393);
      _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)3));
      color(g0390,g0391);
      color(g0392,g0393);
      printelse_If(self);
      color(g0390,g0391);
      color(g0392,g0393);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: printif(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  printif_any(OID self) { 
    _void_(Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)3));
    if (Core.pretty->pbreak == CTRUE)
     { CL_INT  b_index = buffer_length_void();
      CL_INT  _Zl = Core.pretty->index;
      _void_(Core.pretty->pbreak = CFALSE);
      { ClaireHandler c_handle = ClaireHandler();
        if ERROR_IN 
        { print_any(self);
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Core._much_too_far)) == CTRUE)
        { c_handle.catchIt();;}
        else PREVIOUS_HANDLER;}
      _void_(Core.pretty->pbreak = CTRUE);
      if (short_enough_integer(buffer_length_void()) == CTRUE)
       ;else { buffer_set_length_integer(b_index);
          _void_(Core.pretty->index = _Zl);
          lbreak_void();
          print_any(self);
          }
        }
    else print_any(self);
      POP_SIGNAL;}
  


// The c++ function for: printelse(self:If) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  printelse_If(If *self) { 
    
    GC_BIND;
    { OID  e = GC_OID(self->other);
      if (INHERIT(OWNER(e),Language._If))
       { CL_INT  g0396 = (CL_INT )(current_color);
        CL_INT  g0397 = (CL_INT )(current_bold);
        CL_INT  g0398 = g0396;
        CL_INT  g0399 = g0397;
        color(g0396,g0397);
        color_princ_string1(((char*)" "));
        g0396= (CL_INT)((CL_INT )(current_color));
        g0397= (CL_INT)((CL_INT )(current_bold));
        color(g0398,g0399);
        lbreak_void();
        color(g0396,g0397);
        color(g0396,g0397);
        color_princ_string1(((char*)"`BLUEelse if `BLACK"));
        g0396= (CL_INT)((CL_INT )(current_color));
        g0397= (CL_INT)((CL_INT )(current_bold));
        color(g0398,g0399);
        printexp_any(GC_OID(OBJECT(If,e)->test),CFALSE);
        color(g0396,g0397);
        color(g0396,g0397);
        color_princ_string1(((char*)" "));
        g0396= (CL_INT)((CL_INT )(current_color));
        g0397= (CL_INT)((CL_INT )(current_bold));
        color(g0398,g0399);
        printif_any(GC_OID(OBJECT(If,e)->arg));
        color(g0396,g0397);
        color(g0398,g0399);
        _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)3));
        color(g0396,g0397);
        color(g0398,g0399);
        printelse_If(OBJECT(If,e));
        color(g0396,g0397);
        color(g0398,g0399);
        }
      else if ((equal(e,Core.nil->value) != CTRUE) && 
          (e != Kernel.cfalse))
       { CL_INT  _Zl = Core.pretty->index;
        { CL_INT  g0400 = (CL_INT )(current_color);
          CL_INT  g0401 = (CL_INT )(current_bold);
          CL_INT  g0402 = g0400;
          CL_INT  g0403 = g0401;
          color(g0400,g0401);
          color_princ_string1(((char*)" "));
          g0400= (CL_INT)((CL_INT )(current_color));
          g0401= (CL_INT)((CL_INT )(current_bold));
          color(g0402,g0403);
          lbreak_void();
          color(g0400,g0401);
          color(g0400,g0401);
          color_princ_string1(((char*)"`BLUEelse `BLACK"));
          g0400= (CL_INT)((CL_INT )(current_color));
          g0401= (CL_INT)((CL_INT )(current_bold));
          color(g0402,g0403);
          set_level_integer(1);
          color(g0400,g0401);
          color(g0402,g0403);
          print_any(e);
          color(g0400,g0401);
          color(g0402,g0403);
          }
        _void_(Core.pretty->index = _Zl);
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// notice that the eval(test) is not a boolean thus the compiler will add
// something
// TODO: check that is is not too slow (may use a constant for _oid_(true))
// The c++ function for: self_eval(self:If) [SAFE_GC]
CL_EXPORT OID  self_eval_If(If *self) { 
    { OID Result = 0;
      { CL_INT  n = ClEnv->trace_I;
        CL_INT  d = ClEnv->debug_I;
        OID  x = eval_any(self->test);
        if (((CL_INT)n > (CL_INT)0) && 
            ((CL_INT)n <= (CL_INT)ClEnv->step_I))
         { _void_(ClEnv->trace_I = 0);
          _void_(ClEnv->debug_I = -1);
          { CL_INT  g0404 = (CL_INT )(current_color);
            CL_INT  g0405 = (CL_INT )(current_bold);
            CL_INT  g0406 = g0404;
            CL_INT  g0407 = g0405;
            color(g0404,g0405);
            color_princ_string1(((char*)"  `BLUEif "));
            g0404= (CL_INT)((CL_INT )(current_color));
            g0405= (CL_INT)((CL_INT )(current_bold));
            color(g0406,g0407);
            print_any(x);
            color(g0404,g0405);
            color(g0404,g0405);
            color_princ_string1(((char*)"\n"));
            color(g0406,g0407);
            }
          _void_(ClEnv->debug_I = d);
          _void_(ClEnv->trace_I = n);
          }
        { OID  res;
          if (x == Kernel.ctrue)
           res = eval_any(self->arg);
          else if (x == Kernel.cfalse)
           res = eval_any(self->other);
          else if (boolean_I_any(x) == CTRUE)
           res = eval_any(self->arg);
          else res = eval_any(self->other);
            if (((CL_INT)n > (CL_INT)0) && 
              ((CL_INT)n <= (CL_INT)ClEnv->step_I))
           { _void_(ClEnv->trace_I = 0);
            _void_(ClEnv->debug_I = -1);
            { CL_INT  g0408 = (CL_INT )(current_color);
              CL_INT  g0409 = (CL_INT )(current_bold);
              CL_INT  g0410 = g0408;
              CL_INT  g0411 = g0409;
              color(g0408,g0409);
              color_princ_string1(((char*)"  `BLUEif -> "));
              g0408= (CL_INT)((CL_INT )(current_color));
              g0409= (CL_INT)((CL_INT )(current_bold));
              color(g0410,g0411);
              print_any(res);
              color(g0408,g0409);
              color(g0408,g0409);
              color_princ_string1(((char*)"\n"));
              color(g0410,g0411);
              }
            _void_(ClEnv->debug_I = d);
            _void_(ClEnv->trace_I = n);
            }
          Result = res;
          }
        }
      POP_SIGNAL; return (Result);}
    }
  


//--------------------- block structure------------------------------
// The c++ function for: self_print(self:Do) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_print_Do_Language(Do *self) { 
    
    GC_BIND;
    { CL_INT  _Zl = Core.pretty->index;
      princ_string(((char*)"("));
      set_level_integer(1);
      printdo_list(GC_OBJECT(list,self->args),CTRUE);
      _void_(Core.pretty->index = _Zl);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: printdo(l:list,clo:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  printdo_list(list *l,ClaireBoolean *clo) { 
    { CL_INT  len = l->length;
      CL_INT  n = len;
      CL_INT  i = 1;
      CL_INT  g0412 = len;
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((CL_INT)i <= (CL_INT)g0412))
        { { OID  x = (*(l))[i];
            ClaireClass * c = OWNER(x);
            if (c == Language._Princ_wcl)
             princ_string(((char*)" "));
            if (INHERIT(OWNER(x),Language._If))
             printstat_If(OBJECT(If,x));
            else print_any(x);
              n= (CL_INT)(((CL_INT)n-(CL_INT)1));
            if (c == Language._Princ_wcl)
             { if ((i == len) || 
                  (OWNER((*(l))[((CL_INT)i+(CL_INT)1)]) != Language._Call_wcl))
               princ_string(((char*)" "));
              }
            if (n == 0)
             { if (clo == CTRUE)
               princ_string(((char*)")"));
              }
            else if ((c != Language._Princ_wcl) && 
                (c != Language._Call_wcl))
             { princ_string(((char*)", "));
              lbreak_void();
              }
            }
          ++i;
          POP_SIGNAL;}
        }
      }
    POP_SIGNAL;}
  


// The c++ function for: printblock(x:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  printblock_any(OID x) { 
    
    GC_BIND;
    if (INHERIT(OWNER(x),Language._Do))
     printdo_list(GC_OBJECT(list,OBJECT(Do,x)->args),CFALSE);
    else if (INHERIT(OWNER(x),Language._If))
     printstat_If(OBJECT(If,x));
    else print_any(x);
      GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Do) [SAFE_GC]
CL_EXPORT OID  self_eval_Do(Do *self) { 
    { OID Result = 0;
      { OID  res = _oid_(Kernel.emptySet);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(_Zx);
          for (START(self->args); NEXT(_Zx);)
          res= (OPT_EVAL(_Zx));
          }
        Result = res;
        }
      POP_SIGNAL; return (Result);}
    }
  


// ----------------- lexical variable definition -----------------------
// The c++ function for: self_print(self:Let) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_print_Let_Language(Let *self) { 
    
    GC_BIND;
    { CL_INT  _Zl = Core.pretty->index;
      set_level_integer(1);
      { CL_INT  g0413 = (CL_INT )(current_color);
        CL_INT  g0414 = (CL_INT )(current_bold);
        CL_INT  g0415 = g0413;
        CL_INT  g0416 = g0414;
        color(g0413,g0414);
        color_princ_string1(((char*)"`BLUElet `BLACK"));
        g0413= (CL_INT)((CL_INT )(current_color));
        g0414= (CL_INT)((CL_INT )(current_bold));
        color(g0415,g0416);
        ppvariable_Variable(GC_OBJECT(Variable,self->var));
        color(g0413,g0414);
        color(g0413,g0414);
        color_princ_string1(((char*)" := "));
        g0413= (CL_INT)((CL_INT )(current_color));
        g0414= (CL_INT)((CL_INT )(current_bold));
        color(g0415,g0416);
        printexp_any(GC_OID(self->value),CFALSE);
        color(g0413,g0414);
        color(g0415,g0416);
        printbody_Let(self);
        color(g0413,g0414);
        color(g0415,g0416);
        }
      _void_(Core.pretty->index = _Zl);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: printbody(self:Let) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  printbody_Let(Let *self) { 
    
    GC_BIND;
    { OID  a = GC_OID(self->arg);
      if (INHERIT(OWNER(a),Language._Let))
       { princ_string(((char*)","));
        lbreak_integer(4);
        ppvariable_Variable(GC_OBJECT(Variable,OBJECT(Instruction_with_var,a)->var));
        princ_string(((char*)" := "));
        printexp_any(GC_OID(OBJECT(Let,a)->value),CFALSE);
        _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)4));
        printbody_Let(OBJECT(Let,a));
        }
      else { CL_INT  g0418 = (CL_INT )(current_color);
          CL_INT  g0419 = (CL_INT )(current_bold);
          CL_INT  g0420 = g0418;
          CL_INT  g0421 = g0419;
          color(g0418,g0419);
          color_princ_string1(((char*)" `BLUEin `BLACK"));
          g0418= (CL_INT)((CL_INT )(current_color));
          g0419= (CL_INT)((CL_INT )(current_bold));
          color(g0420,g0421);
          lbreak_integer(2);
          color(g0418,g0419);
          color(g0420,g0421);
          print_any(a);
          color(g0418,g0419);
          color(g0420,g0421);
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Let) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_eval_Let(Let *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  val = GC_OID(eval_any(GC_OID(self->value)));
        CL_INT  n = ClEnv->trace_I;
        CL_INT  d = ClEnv->debug_I;
        write_value_Variable(self->var,val);
        { OID  res = GC_OID(eval_any(GC_OID(self->arg)));
          if (((CL_INT)n > (CL_INT)0) && 
              ((CL_INT)n <= (CL_INT)ClEnv->step_I))
           { _void_(ClEnv->trace_I = 0);
            _void_(ClEnv->debug_I = -1);
            { CL_INT  g0422 = (CL_INT )(current_color);
              CL_INT  g0423 = (CL_INT )(current_bold);
              CL_INT  g0424 = g0422;
              CL_INT  g0425 = g0423;
              color(g0422,g0423);
              color_princ_string1(((char*)"  `BLUE"));
              g0422= (CL_INT)((CL_INT )(current_color));
              g0423= (CL_INT)((CL_INT )(current_bold));
              color(g0424,g0425);
              print_any(GC_OID(_oid_(self->var)));
              color(g0422,g0423);
              color(g0422,g0423);
              color_princ_string1(((char*)" := "));
              g0422= (CL_INT)((CL_INT )(current_color));
              g0423= (CL_INT)((CL_INT )(current_bold));
              color(g0424,g0425);
              print_any(res);
              color(g0422,g0423);
              color(g0422,g0423);
              color_princ_string1(((char*)"\n"));
              color(g0424,g0425);
              }
            _void_(ClEnv->debug_I = d);
            _void_(ClEnv->trace_I = n);
            }
          Result = res;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// a when is a special Let that filters out the unknown value !
//
// The c++ function for: self_print(self:When) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_print_When_Language(When *self) { 
    
    GC_BIND;
    { CL_INT  _Zl = Core.pretty->index;
      set_level_integer(1);
      { CL_INT  g0426 = (CL_INT )(current_color);
        CL_INT  g0427 = (CL_INT )(current_bold);
        CL_INT  g0428 = g0426;
        CL_INT  g0429 = g0427;
        color(g0426,g0427);
        color_princ_string1(((char*)"`BLUEwhen `BLACK"));
        g0426= (CL_INT)((CL_INT )(current_color));
        g0427= (CL_INT)((CL_INT )(current_bold));
        color(g0428,g0429);
        ppvariable_Variable(GC_OBJECT(Variable,self->var));
        color(g0426,g0427);
        color(g0426,g0427);
        color_princ_string1(((char*)" := "));
        g0426= (CL_INT)((CL_INT )(current_color));
        g0427= (CL_INT)((CL_INT )(current_bold));
        color(g0428,g0429);
        printexp_any(GC_OID(self->value),CFALSE);
        color(g0426,g0427);
        color(g0426,g0427);
        color_princ_string1(((char*)" `BLUEin `BLACK"));
        g0426= (CL_INT)((CL_INT )(current_color));
        g0427= (CL_INT)((CL_INT )(current_bold));
        color(g0428,g0429);
        lbreak_integer(2);
        color(g0426,g0427);
        color(g0428,g0429);
        print_any(GC_OID(self->arg));
        color(g0426,g0427);
        color(g0428,g0429);
        }
      if (((self->other == CNULL) ? CTRUE : CFALSE) != CTRUE)
       { CL_INT  g0430 = (CL_INT )(current_color);
        CL_INT  g0431 = (CL_INT )(current_bold);
        CL_INT  g0432 = g0430;
        CL_INT  g0433 = g0431;
        color(g0430,g0431);
        color_princ_string1(((char*)" "));
        g0430= (CL_INT)((CL_INT )(current_color));
        g0431= (CL_INT)((CL_INT )(current_bold));
        color(g0432,g0433);
        lbreak_void();
        color(g0430,g0431);
        color(g0430,g0431);
        color_princ_string1(((char*)"`BLUEelse `BLACK"));
        g0430= (CL_INT)((CL_INT )(current_color));
        g0431= (CL_INT)((CL_INT )(current_bold));
        color(g0432,g0433);
        set_level_integer(1);
        color(g0430,g0431);
        color(g0432,g0433);
        print_any(GC_OID(self->other));
        color(g0430,g0431);
        color(g0432,g0433);
        }
      _void_(Core.pretty->index = _Zl);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:When) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_eval_When(When *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  val = GC_OID(eval_any(GC_OID(self->value)));
        CL_INT  n = ClEnv->trace_I;
        CL_INT  d = ClEnv->debug_I;
        if (((CL_INT)n > (CL_INT)0) && 
            ((CL_INT)n <= (CL_INT)ClEnv->step_I))
         { _void_(ClEnv->trace_I = 0);
          _void_(ClEnv->debug_I = -1);
          { CL_INT  g0434 = (CL_INT )(current_color);
            CL_INT  g0435 = (CL_INT )(current_bold);
            CL_INT  g0436 = g0434;
            CL_INT  g0437 = g0435;
            color(g0434,g0435);
            color_princ_string1(((char*)"  `BLUEwhen "));
            g0434= (CL_INT)((CL_INT )(current_color));
            g0435= (CL_INT)((CL_INT )(current_bold));
            color(g0436,g0437);
            print_any(GC_OID(_oid_(self->var)));
            color(g0434,g0435);
            color(g0434,g0435);
            color_princ_string1(((char*)" := "));
            g0434= (CL_INT)((CL_INT )(current_color));
            g0435= (CL_INT)((CL_INT )(current_bold));
            color(g0436,g0437);
            print_any(val);
            color(g0434,g0435);
            color(g0434,g0435);
            color_princ_string1(((char*)"\n"));
            color(g0436,g0437);
            }
          _void_(ClEnv->debug_I = d);
          _void_(ClEnv->trace_I = n);
          }
        { OID  res;
          { if (val != CNULL)
             { write_value_Variable(self->var,val);
              res = eval_any(GC_OID(self->arg));
              }
            else res = eval_any(GC_OID(self->other));
              GC_OID(res);}
          if (((CL_INT)n > (CL_INT)0) && 
              ((CL_INT)n <= (CL_INT)ClEnv->step_I))
           { _void_(ClEnv->trace_I = 0);
            _void_(ClEnv->debug_I = -1);
            { CL_INT  g0438 = (CL_INT )(current_color);
              CL_INT  g0439 = (CL_INT )(current_bold);
              CL_INT  g0440 = g0438;
              CL_INT  g0441 = g0439;
              color(g0438,g0439);
              color_princ_string1(((char*)"  `BLUEwhen -> "));
              g0438= (CL_INT)((CL_INT )(current_color));
              g0439= (CL_INT)((CL_INT )(current_bold));
              color(g0440,g0441);
              print_any(res);
              color(g0438,g0439);
              color(g0438,g0439);
              color_princ_string1(((char*)"\n"));
              color(g0440,g0441);
              }
            _void_(ClEnv->debug_I = d);
            _void_(ClEnv->trace_I = n);
            }
          Result = res;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// two special forms of Let:
// Let+(v,r(x),(r(x) := y),Let(v2,e,(r(x) := v,v2)))    <=>  let r(x) = y in e
// Let*(v,f(),Let(v1,v[1],...(Let(vn,v[n],e))   <=> let (v1,v2,...vn) := f() in e
//
//note: the Let* is also used for multi-assignments
// Let*(v,f(),(v1 := v[1], v2 := v[2], ...))   <=>  (v1,v2,...vn) := f()
//
// The c++ function for: self_print(self:Let+) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_print_Let_plus_Language(Let_plus *self) { 
    
    GC_BIND;
    { CL_INT  _Zl = Core.pretty->index;
      list * l = GC_OBJECT(list,OBJECT(Do,self->arg)->args);
      set_level_integer(1);
      { CL_INT  g0442 = (CL_INT )(current_color);
        CL_INT  g0443 = (CL_INT )(current_bold);
        CL_INT  g0444 = g0442;
        CL_INT  g0445 = g0443;
        color(g0442,g0443);
        color_princ_string1(((char*)"`BLUElet `BLACK"));
        g0442= (CL_INT)((CL_INT )(current_color));
        g0443= (CL_INT)((CL_INT )(current_bold));
        color(g0444,g0445);
        printexp_any(GC_OID(self->value),CFALSE);
        color(g0442,g0443);
        color(g0442,g0443);
        color_princ_string1(((char*)" := "));
        g0442= (CL_INT)((CL_INT )(current_color));
        g0443= (CL_INT)((CL_INT )(current_bold));
        color(g0444,g0445);
        printexp_any(GC_OID((*(OBJECT(bag,(*Core.args)((*(l))[1]))))[3]),CFALSE);
        color(g0442,g0443);
        color(g0442,g0443);
        color_princ_string1(((char*)" `BLUEin `BLACK"));
        g0442= (CL_INT)((CL_INT )(current_color));
        g0443= (CL_INT)((CL_INT )(current_bold));
        color(g0444,g0445);
        lbreak_integer(2);
        color(g0442,g0443);
        color(g0444,g0445);
        print_any(GC_OID(OBJECT(Let,(*(l))[2])->value));
        color(g0442,g0443);
        color(g0444,g0445);
        }
      _void_(Core.pretty->index = _Zl);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_print(self:Let*) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_print_Let_star_Language(Let_star *self) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { CL_INT  _Zl = Core.pretty->index;
      OID  l = GC_OID(self->arg);
      set_level_integer(1);
      if (INHERIT(OWNER(l),Language._Let))
       { CL_INT  g0446 = (CL_INT )(current_color);
        CL_INT  g0447 = (CL_INT )(current_bold);
        CL_INT  g0448 = g0446;
        CL_INT  g0449 = g0447;
        color(g0446,g0447);
        color_princ_string1(((char*)"`BLUElet `BLACK("));
        g0446= (CL_INT)((CL_INT )(current_color));
        g0447= (CL_INT)((CL_INT )(current_bold));
        color(g0448,g0449);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while ((CTRUE == CTRUE))
          { GC_LOOP;
            (*Language.ppvariable)(GC_OID((*Language.var)(l)));
            { OID  lnext = GC_OID((*Kernel.arg)(l));
              if ((INHERIT(OWNER(lnext),Language._Let)) && ((INHERIT(OWNER(OBJECT(Let,lnext)->value),Language._Call)) && 
                  (equal(GC_OID((*(OBJECT(bag,(*Core.args)(GC_OID(OBJECT(Let,lnext)->value)))))[1]),GC_OID(_oid_(self->var))) == CTRUE)))
               { princ_string(((char*)","));
                GC__OID(l = lnext, 1);
                }
              else { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                }
            GC_UNLOOP;POP_SIGNAL;}
          }
        color(g0446,g0447);
        color(g0446,g0447);
        color_princ_string1(((char*)") := "));
        g0446= (CL_INT)((CL_INT )(current_color));
        g0447= (CL_INT)((CL_INT )(current_bold));
        color(g0448,g0449);
        printexp_any(GC_OID(self->value),CFALSE);
        color(g0446,g0447);
        color(g0448,g0449);
        printbody_Let(OBJECT(Let,l));
        color(g0446,g0447);
        color(g0448,g0449);
        }
      else { princ_string(((char*)"("));
          { ClaireBoolean * _Zf = CTRUE;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(_Za);
              bag *_Za_support;
              _Za_support = GC_OBJECT(list,OBJECT(bag,(*Core.args)(l)));
              for (START(_Za_support); NEXT(_Za);)
              { GC_LOOP;
                { if (_Zf == CTRUE)
                   _Zf= (CFALSE);
                  else princ_string(((char*)","));
                    (*Language.ppvariable)(GC_OID((*Language.var)(_Za)));
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            }
          princ_string(((char*)") := "));
          printexp_any(GC_OID(self->value),CFALSE);
          }
        _void_(Core.pretty->index = _Zl);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// *********************************************************************
// *     Part 2: set control structures                                *
// *********************************************************************
// for is the simplest evaluation loop
//
// The c++ function for: self_print(self:For) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_For_Language(For *self) { 
    
    GC_BIND;
    { CL_INT  g0452 = (CL_INT )(current_color);
      CL_INT  g0453 = (CL_INT )(current_bold);
      CL_INT  g0454 = g0452;
      CL_INT  g0455 = g0453;
      color(g0452,g0453);
      color_princ_string1(((char*)"`BLUEfor `BLACK"));
      g0452= (CL_INT)((CL_INT )(current_color));
      g0453= (CL_INT)((CL_INT )(current_bold));
      color(g0454,g0455);
      ppvariable_Variable(GC_OBJECT(Variable,self->var));
      color(g0452,g0453);
      color(g0452,g0453);
      color_princ_string1(((char*)" `BLUEin `BLACK"));
      g0452= (CL_INT)((CL_INT )(current_color));
      g0453= (CL_INT)((CL_INT )(current_bold));
      color(g0454,g0455);
      { CL_INT  _Zl = Core.pretty->index;
        set_level_void();
        printexp_any(GC_OID(self->set_arg),CFALSE);
        _void_(Core.pretty->index = _Zl);
        }
      color(g0452,g0453);
      color(g0452,g0453);
      color_princ_string1(((char*)" "));
      g0452= (CL_INT)((CL_INT )(current_color));
      g0453= (CL_INT)((CL_INT )(current_bold));
      color(g0454,g0455);
      _void_(Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)2));
      lbreak_void();
      print_any(GC_OID(self->arg));
      _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
      color(g0452,g0453);
      color(g0454,g0455);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:For) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_eval_For(For *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  x = GC_OID(eval_any(GC_OID(self->set_arg)));
        CL_INT  n = ClEnv->trace_I;
        CL_INT  d = ClEnv->debug_I;
        if (((CL_INT)n > (CL_INT)0) && 
            ((CL_INT)n <= (CL_INT)ClEnv->step_I))
         { _void_(ClEnv->trace_I = 0);
          _void_(ClEnv->debug_I = -1);
          { CL_INT  g0456 = (CL_INT )(current_color);
            CL_INT  g0457 = (CL_INT )(current_bold);
            CL_INT  g0458 = g0456;
            CL_INT  g0459 = g0457;
            color(g0456,g0457);
            color_princ_string1(((char*)"  `BLUEfor "));
            g0456= (CL_INT)((CL_INT )(current_color));
            g0457= (CL_INT)((CL_INT )(current_bold));
            color(g0458,g0459);
            print_any(GC_OID(_oid_(self->var)));
            color(g0456,g0457);
            color(g0456,g0457);
            color_princ_string1(((char*)" in "));
            g0456= (CL_INT)((CL_INT )(current_color));
            g0457= (CL_INT)((CL_INT )(current_bold));
            color(g0458,g0459);
            print_any(x);
            color(g0456,g0457);
            color(g0456,g0457);
            color_princ_string1(((char*)"\n"));
            color(g0458,g0459);
            }
          _void_(ClEnv->debug_I = d);
          _void_(ClEnv->trace_I = n);
          }
        { OID  res;
          { ClaireHandler c_handle = ClaireHandler();
            if ERROR_IN 
            { if (INHERIT(OWNER(x),Kernel._class))
               { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(y);
                res= Kernel.cfalse;
                for (START(OBJECT(ClaireClass,x)->descendents); NEXT(y);)
                { GC_LOOP;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    OID gc_local;
                    ITERATE(z);
                    for (START(OBJECT(ClaireClass,y)->instances); NEXT(z);)
                    { GC_LOOP;
                      { write_value_Variable(self->var,z);
                        eval_any(GC_OID(self->arg));
                        }
                      GC_UNLOOP; POP_SIGNAL;}
                    }
                  GC_UNLOOP; POP_SIGNAL;}
                }
              else if (Kernel._array == OWNER(x))
               { CL_INT  n = array_v(x)[0];
                CL_INT  g0460 = 1;
                CL_INT  g0461 = n;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  res= _oid_(CFALSE);
                  while (((CL_INT)g0460 <= (CL_INT)g0461))
                  { GC_LOOP;
                    { OID  z = nth_get_array(array_v(x),g0460);
                      write_value_Variable(self->var,z);
                      eval_any(GC_OID(self->arg));
                      }
                    ++g0460;
                    GC_UNLOOP;POP_SIGNAL;}
                  }
                }
              else if (INHERIT(OWNER(x),Core._Interval))
               { CL_INT  y = OBJECT(Interval,x)->arg1;
                CL_INT  g0462 = OBJECT(Interval,x)->arg2;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  res= _oid_(CFALSE);
                  while (((CL_INT)y <= (CL_INT)g0462))
                  { GC_LOOP;
                    write_value_Variable(self->var,((OID)y));
                    eval_any(GC_OID(self->arg));
                    ++y;
                    GC_UNLOOP;POP_SIGNAL;}
                  }
                }
              else if (INHERIT(OWNER(x),Kernel._collection))
               { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(y);
                res= Kernel.cfalse;
                bag *y_support;
                y_support = GC_OBJECT(bag,enumerate_any(x));
                for (START(y_support); NEXT(y);)
                { GC_LOOP;
                  { write_value_Variable(self->var,y);
                    eval_any(GC_OID(self->arg));
                    }
                  GC_UNLOOP; POP_SIGNAL;}
                }
              else { OID  V_CL0467;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[136] ~S is not a collection !")),
                    _oid_(list::alloc(1,x)))));
                  
                  res=_void_(V_CL0467);}
                ERROR_FREE;}
            else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Core._return_error)) == CTRUE)
            { c_handle.catchIt();res = (*Kernel.arg)(GC_OID(_oid_(ClEnv->exception_I)));
              }
            else PREVIOUS_HANDLER;}
          if (((CL_INT)n > (CL_INT)0) && 
              ((CL_INT)n <= (CL_INT)ClEnv->step_I))
           { _void_(ClEnv->trace_I = 0);
            _void_(ClEnv->debug_I = -1);
            { CL_INT  g0463 = (CL_INT )(current_color);
              CL_INT  g0464 = (CL_INT )(current_bold);
              CL_INT  g0465 = g0463;
              CL_INT  g0466 = g0464;
              color(g0463,g0464);
              color_princ_string1(((char*)"  `BLUEfor -> "));
              g0463= (CL_INT)((CL_INT )(current_color));
              g0464= (CL_INT)((CL_INT )(current_bold));
              color(g0465,g0466);
              print_any(res);
              color(g0463,g0464);
              color(g0463,g0464);
              color_princ_string1(((char*)"\n"));
              color(g0465,g0466);
              }
            _void_(ClEnv->debug_I = d);
            _void_(ClEnv->trace_I = n);
            }
          Result = res;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> v3.3.33 ffor
// The c++ function for: self_print(self:iClaire/Ffor) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_Ffor1_Language(iClaire_Ffor *self) { 
    
    GC_BIND;
    { CL_INT  _Zl = Core.pretty->index;
      CL_INT  g0470 = (CL_INT )(current_color);
      CL_INT  g0471 = (CL_INT )(current_bold);
      CL_INT  g0472 = g0470;
      CL_INT  g0473 = g0471;
      color(g0470,g0471);
      color_princ_string1(((char*)"`BLUEffor `BLACK"));
      g0470= (CL_INT)((CL_INT )(current_color));
      g0471= (CL_INT)((CL_INT )(current_bold));
      color(g0472,g0473);
      ppvariable_Variable(GC_OBJECT(Variable,self->var));
      color(g0470,g0471);
      color(g0470,g0471);
      color_princ_string1(((char*)" `BLUEin `BLACK"));
      g0470= (CL_INT)((CL_INT )(current_color));
      g0471= (CL_INT)((CL_INT )(current_bold));
      color(g0472,g0473);
      set_level_void();
      printexp_any(GC_OID(self->set_arg),CFALSE);
      color(g0470,g0471);
      color(g0470,g0471);
      color_princ_string1(((char*)" `BLUEby `BLACK"));
      g0470= (CL_INT)((CL_INT )(current_color));
      g0471= (CL_INT)((CL_INT )(current_bold));
      color(g0472,g0473);
      printexp_any(GC_OID(self->forkedby),CFALSE);
      _void_(Core.pretty->index = _Zl);
      color(g0470,g0471);
      color(g0470,g0471);
      color_princ_string1(((char*)" "));
      g0470= (CL_INT)((CL_INT )(current_color));
      g0471= (CL_INT)((CL_INT )(current_bold));
      color(g0472,g0473);
      _void_(Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)2));
      lbreak_void();
      print_any(GC_OID(self->arg));
      _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
      color(g0470,g0471);
      color(g0472,g0473);
      }
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> parallel programing
// The c++ function for: self_eval(self:iClaire/Ffor) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  self_eval_Ffor1(iClaire_Ffor *self) { 
    
    GC_BIND;
    { OID Result = 0;
      if (unix_ask_void1() != CTRUE)
       { list * res = list::empty(Kernel._any);
        list * l;
        { { list * i_bag = list::empty(Kernel.emptySet);
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(i);
              bag *i_support;
              i_support = GC_OBJECT(bag,enumerate_any(GC_OID(eval_any(GC_OID(self->set_arg)))));
              for (START(i_support); NEXT(i);)
              i_bag->addFast((OID)i);
              }
            l = GC_OBJECT(list,i_bag);
            }
          GC_OBJECT(list,l);}
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(i);
          for (START(l); NEXT(i);)
          { GC_LOOP;
            { write_value_Variable(self->var,i);
              { OID  g0479UU;
                { { ClaireHandler c_handle = ClaireHandler();
                    if ERROR_IN 
                    { { ClaireHandler c_handle = ClaireHandler();
                        if ERROR_IN 
                        { g0479UU = eval_any(GC_OID(self->arg));
                          ERROR_FREE;}
                        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                        { c_handle.catchIt();{ Core_ffor_error * _CL_obj = ((Core_ffor_error *) GC_OBJECT(Core_ffor_error,new_object_class(Core._ffor_error)));
                            _void_(_CL_obj->childpid = getpid_void());
                            { Core_ffor_error * g0480 = _CL_obj; 
                              char * g0481;
                              { print_in_string_void();
                                print_any(GC_OID(_oid_(ClEnv->exception_I)));
                                g0481 = end_of_string_void();
                                }
                              _void_(g0480->childstr = g0481);}
                            { OID  V_CL0482;close_exception(_CL_obj);
                              
                              g0479UU=_void_(V_CL0482);}
                            }
                          }
                        else PREVIOUS_HANDLER;}
                      ERROR_FREE;}
                    else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                    { c_handle.catchIt();g0479UU = _oid_(ClEnv->exception_I);
                      }
                    else PREVIOUS_HANDLER;}
                  GC_OID(g0479UU);}
                res = res->addFast((OID)g0479UU);
                }
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        Result = _oid_(cast_I_list1(res,Kernel.emptySet));
        }
      else { list * l;
          { { list * i_bag = list::empty(Kernel.emptySet);
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(i);
                bag *i_support;
                i_support = GC_OBJECT(bag,enumerate_any(GC_OID(eval_any(GC_OID(self->set_arg)))));
                for (START(i_support); NEXT(i);)
                i_bag->addFast((OID)i);
                }
              l = GC_OBJECT(list,i_bag);
              }
            GC_OBJECT(list,l);}
          OID  N = GC_OID(eval_any(GC_OID(self->forkedby)));
          OID  childs = CNULL;
          list * res = GC_OBJECT(list,list::empty(Kernel._any));
          CL_INT  remain = l->length;
          CL_INT  len = remain;
          CL_INT  lindex = 1;
          CL_INT  n = ClEnv->trace_I;
          CL_INT  d = ClEnv->debug_I;
          if (inherit_ask_class(OWNER(N),Kernel._integer) != CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[200] ~S : by range error ~S does not belong to integer")),
            _oid_(list::alloc(2,_oid_(self),N)))));
          if ((CL_INT)((CL_INT)N) <= (CL_INT)0)
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[201] ~S : negative by (~S) argument in dangerous")),
            _oid_(list::alloc(2,_oid_(self),N)))));
          { list * V_CL0483;{ list * i_bag = list::empty(Kernel._list);
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(i);
                bag *i_support;
                i_support = GC_OBJECT(bag,enumerate_any(GC_OID(_oid_(_dot_dot_integer(1,((CL_INT)N))))));
                for (START(i_support); NEXT(i);)
                { GC_LOOP;
                  i_bag->addFast((OID)GC_OID(_oid_(list::alloc(Kernel._any,4,((OID)-1),
                    ((OID)0),
                    GC_OID(_oid_(blob_I_void1())),
                    ((OID)0)))));
                  GC_UNLOOP; POP_SIGNAL;}
                }
              V_CL0483 = GC_OBJECT(list,i_bag);
              }
            
            childs=_oid_(V_CL0483);}
          if (((CL_INT)n > (CL_INT)0) && 
              ((CL_INT)n <= (CL_INT)ClEnv->step_I))
           { _void_(ClEnv->trace_I = 0);
            _void_(ClEnv->debug_I = -1);
            { CL_INT  g0475 = (CL_INT )(current_color);
              CL_INT  g0476 = (CL_INT )(current_bold);
              CL_INT  g0477 = g0475;
              CL_INT  g0478 = g0476;
              color(g0475,g0476);
              color_princ_string1(((char*)"  `BLUEffor "));
              g0475= (CL_INT)((CL_INT )(current_color));
              g0476= (CL_INT)((CL_INT )(current_bold));
              color(g0477,g0478);
              print_any(GC_OID(_oid_(self->var)));
              color(g0475,g0476);
              color(g0475,g0476);
              color_princ_string1(((char*)" in "));
              g0475= (CL_INT)((CL_INT )(current_color));
              g0476= (CL_INT)((CL_INT )(current_bold));
              color(g0477,g0478);
              print_any(_oid_(l));
              color(g0475,g0476);
              color(g0475,g0476);
              color_princ_string1(((char*)" by "));
              g0475= (CL_INT)((CL_INT )(current_color));
              g0476= (CL_INT)((CL_INT )(current_bold));
              color(g0477,g0478);
              print_any(GC_OID(self->forkedby));
              color(g0475,g0476);
              color(g0475,g0476);
              color_princ_string1(((char*)"\n"));
              color(g0477,g0478);
              }
            _void_(ClEnv->debug_I = d);
            _void_(ClEnv->trace_I = n);
            }
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)res->length < (CL_INT)len))
            { GC_LOOP;
              if ((CL_INT)remain > (CL_INT)0)
               { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(i);
                bag *i_support;
                i_support = GC_OBJECT(bag,enumerate_any(GC_OID(_oid_(_dot_dot_integer(1,((CL_INT)N))))));
                for (START(i_support); NEXT(i);)
                { GC_LOOP;
                  { if (remain == 0)
                     { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                    if ((*Kernel.nth)(GC_OID((*Kernel.nth)(childs,
                        ((OID)i))),
                      ((OID)1)) == ((OID)-1))
                     { OID  current = (*(l))[lindex];
                      write_value_Variable(self->var,current);
                      { ClaireHandler c_handle = ClaireHandler();
                        if ERROR_IN 
                        { { tuple * g0474 = socketpair_void1();
                            cl_socket * s1 = GC_OBJECT(cl_socket,OBJECT(cl_socket,(*(g0474))[1]));
                            cl_socket * s2 = GC_OBJECT(cl_socket,OBJECT(cl_socket,(*(g0474))[2]));
                            if (forker_ask_void1() == CTRUE)
                             { OID  c = GC_OID((*Kernel.nth)(childs,
                                ((OID)i)));
                              fclose_port1(s1);
                              remain= (CL_INT)(((CL_INT)remain-(CL_INT)1));
                              ++lindex;
                              (*Kernel.nth_equal)(c,
                                ((OID)1),
                                ((OID)forked_void()));
                              (*Kernel.nth_equal)(c,
                                ((OID)2),
                                _oid_(s2));
                              (*Kernel.nth_equal)(c,
                                ((OID)4),
                                current);
                              }
                            else { fclose_port1(s2);
                                { OID  g0484UU;
                                  { { ClaireHandler c_handle = ClaireHandler();
                                      if ERROR_IN 
                                      { { ClaireHandler c_handle = ClaireHandler();
                                          if ERROR_IN 
                                          { g0484UU = eval_any(GC_OID(self->arg));
                                            ERROR_FREE;}
                                          else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                                          { c_handle.catchIt();{ Core_ffor_error * _CL_obj = ((Core_ffor_error *) GC_OBJECT(Core_ffor_error,new_object_class(Core._ffor_error)));
                                              _void_(_CL_obj->childpid = getpid_void());
                                              { Core_ffor_error * g0485 = _CL_obj; 
                                                char * g0486;
                                                { print_in_string_void();
                                                  print_any(GC_OID(_oid_(ClEnv->exception_I)));
                                                  g0486 = end_of_string_void();
                                                  }
                                                _void_(g0485->childstr = g0486);}
                                              { OID  V_CL0487;close_exception(_CL_obj);
                                                
                                                g0484UU=_void_(V_CL0487);}
                                              }
                                            }
                                          else PREVIOUS_HANDLER;}
                                        ERROR_FREE;}
                                      else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                                      { c_handle.catchIt();{ fclose_port1(s1);
                                          CL_exit(1);
                                          g0484UU = ((OID)0);
                                          }
                                        }
                                      else PREVIOUS_HANDLER;}
                                    GC_OID(g0484UU);}
                                  serialize_port3(s1,g0484UU);
                                  }
                                fclose_port1(s1);
                                CL_exit(0);
                                }
                              }
                          ERROR_FREE;}
                        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                        { c_handle.catchIt();;}
                        else PREVIOUS_HANDLER;}
                      }
                    }
                  GC_UNLOOP; POP_SIGNAL;}
                }
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(i);
                bag *i_support;
                i_support = GC_OBJECT(bag,enumerate_any(GC_OID(_oid_(_dot_dot_integer(1,((CL_INT)N))))));
                for (START(i_support); NEXT(i);)
                { GC_LOOP;
                  { OID  c = GC_OID((*Kernel.nth)(childs,
                      ((OID)i)));
                    OID  s = GC_OID((*Kernel.nth)(c,
                      ((OID)2)));
                    OID  pid = GC_OID((*Kernel.nth)(c,
                      ((OID)1)));
                    OID  buf = GC_OID((*Kernel.nth)(c,
                      ((OID)3)));
                    if (pid != ((OID)-1))
                     { (*Core.read_I)(s);
                      if ((select_ask_integer1(10) == CTRUE) && 
                          ((OBJECT(ClaireBoolean,(*Core.readable_ask)(s))) == CTRUE))
                       { fwrite_string2(GC_STRING(fread_port4(OBJECT(PortObject,s),1024)),OBJECT(PortObject,buf));
                        if ((OBJECT(ClaireBoolean,(*Core.eof_port_ask)(s))) == CTRUE)
                         { tuple * st = GC_OBJECT(tuple,waitpid_integer2(((CL_INT)pid))->copyIfNeeded());
                          if (((*(st))[1] == _oid_(Core.CL_WEXITED)) && 
                              ((*(st))[3] == ((OID)0)))
                           { OID  g0488UU;
                            { { ClaireHandler c_handle = ClaireHandler();
                                if ERROR_IN 
                                { g0488UU = unserialize_port1(OBJECT(PortObject,buf));
                                  ERROR_FREE;}
                                else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                                { c_handle.catchIt();g0488UU = _oid_(ClEnv->exception_I);
                                  }
                                else PREVIOUS_HANDLER;}
                              GC_OID(g0488UU);}
                            res = res->addFast((OID)g0488UU);
                            }
                          else res= (res->addFast((OID)_oid_(st)));
                            fclose_port1(OBJECT(PortObject,s));
                          set_length_blob1(OBJECT(blob,buf),0);
                          (*Kernel.nth_equal)(c,
                            ((OID)1),
                            ((OID)-1));
                          { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                          }
                        }
                      }
                    }
                  GC_UNLOOP; POP_SIGNAL;}
                }
              GC_UNLOOP;POP_SIGNAL;}
            }
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(i);
            bag *i_support;
            i_support = GC_OBJECT(bag,enumerate_any(childs));
            for (START(i_support); NEXT(i);)
            { GC_LOOP;
              fclose_port1(GC_OBJECT(PortObject,OBJECT(PortObject,(*Kernel.nth)(i,
                ((OID)3)))));
              GC_UNLOOP; POP_SIGNAL;}
            }
          Result = _oid_(cast_I_list1(res,Kernel.emptySet));
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// [collect VAR in SET_EXPR, ...] is the same as a "for", but returns the list of values
//
// The c++ function for: self_print(self:Collect) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_Collect_Language(Collect *self) { 
    
    GC_BIND;
    { CL_INT  g0490 = (CL_INT )(current_color);
      CL_INT  g0491 = (CL_INT )(current_bold);
      CL_INT  g0492 = g0490;
      CL_INT  g0493 = g0491;
      color(g0490,g0491);
      color_princ_string1(((char*)"list{ "));
      g0490= (CL_INT)((CL_INT )(current_color));
      g0491= (CL_INT)((CL_INT )(current_bold));
      color(g0492,g0493);
      _void_(Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)2));
      printexp_any(GC_OID(self->arg),CFALSE);
      color(g0490,g0491);
      color(g0490,g0491);
      color_princ_string1(((char*)" | "));
      g0490= (CL_INT)((CL_INT )(current_color));
      g0491= (CL_INT)((CL_INT )(current_bold));
      color(g0492,g0493);
      lbreak_void();
      color(g0490,g0491);
      color(g0492,g0493);
      ppvariable_Variable(GC_OBJECT(Variable,self->var));
      color(g0490,g0491);
      color(g0490,g0491);
      color_princ_string1(((char*)" `BLUEin `BLACK"));
      g0490= (CL_INT)((CL_INT )(current_color));
      g0491= (CL_INT)((CL_INT )(current_bold));
      color(g0492,g0493);
      { CL_INT  _Zl = Core.pretty->index;
        set_level_void();
        printexp_any(GC_OID(self->set_arg),CFALSE);
        _void_(Core.pretty->index = ((CL_INT)_Zl-(CL_INT)2));
        }
      color(g0490,g0491);
      color(g0490,g0491);
      color_princ_string1(((char*)"}"));
      color(g0492,g0493);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Collect) [NEW_ALLOC]
CL_EXPORT OID  self_eval_Collect(Collect *self) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { OID Result = 0;
      { OID  x = GC_OID(OPT_EVAL(self->set_arg));
        list * res = list::empty();
        if (INHERIT(OWNER(x),Kernel._class))
         { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(y);
          for (START(OBJECT(ClaireClass,x)->descendents); NEXT(y);)
          { GC_LOOP;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(z);
              for (START(OBJECT(ClaireClass,y)->instances); NEXT(z);)
              { GC_LOOP;
                { write_value_Variable(self->var,z);
                  GC__ANY(res = res->addFast((OID)GC_OID(OPT_EVAL(self->arg))), 1);
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        else { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(y);
            bag *y_support;
            y_support = GC_OBJECT(bag,enumerate_any(x));
            for (START(y_support); NEXT(y);)
            { GC_LOOP;
              { write_value_Variable(self->var,y);
                res= (res->addFast((OID)GC_OID(OPT_EVAL(self->arg))));
                }
              GC_UNLOOP; POP_SIGNAL;}
            }
          if (((self->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         { { OID  x;
            { { OID  x_some = CNULL;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(x);
                  for (START(res); NEXT(x);)
                  { GC_LOOP;
                    if (belong_to(x,_oid_(self->of)) != CTRUE)
                     { x_some= (x);
                      GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                x = x_some;
                }
              GC_OID(x);}
            if (x != CNULL)
             close_exception(((range_error *) (*Core._range_error)(_oid_(self),
              x,
              GC_OID(_oid_(self->of)))));
            else ;}
          cast_I_list1(res,self->of);
          }
        Result = _oid_(res);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// this is a set image version, that produces a set
//
// The c++ function for: self_print(self:Image) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_Image_Language(Image *self) { 
    
    GC_BIND;
    { CL_INT  g0495 = (CL_INT )(current_color);
      CL_INT  g0496 = (CL_INT )(current_bold);
      CL_INT  g0497 = g0495;
      CL_INT  g0498 = g0496;
      color(g0495,g0496);
      color_princ_string1(((char*)"{ "));
      g0495= (CL_INT)((CL_INT )(current_color));
      g0496= (CL_INT)((CL_INT )(current_bold));
      color(g0497,g0498);
      _void_(Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)2));
      printexp_any(GC_OID(self->arg),CFALSE);
      color(g0495,g0496);
      color(g0495,g0496);
      color_princ_string1(((char*)" | "));
      g0495= (CL_INT)((CL_INT )(current_color));
      g0496= (CL_INT)((CL_INT )(current_bold));
      color(g0497,g0498);
      lbreak_void();
      color(g0495,g0496);
      color(g0497,g0498);
      ppvariable_Variable(GC_OBJECT(Variable,self->var));
      color(g0495,g0496);
      color(g0495,g0496);
      color_princ_string1(((char*)" `BLUEin `BLACK"));
      g0495= (CL_INT)((CL_INT )(current_color));
      g0496= (CL_INT)((CL_INT )(current_bold));
      color(g0497,g0498);
      { CL_INT  _Zl = Core.pretty->index;
        set_level_void();
        printexp_any(GC_OID(self->set_arg),CFALSE);
        _void_(Core.pretty->index = ((CL_INT)_Zl-(CL_INT)2));
        }
      color(g0495,g0496);
      color(g0495,g0496);
      color_princ_string1(((char*)"}"));
      color(g0497,g0498);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Image) [NEW_ALLOC]
CL_EXPORT OID  self_eval_Image(Image *self) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { OID Result = 0;
      { OID  x = GC_OID(OPT_EVAL(self->set_arg));
        set * res = set::empty();
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(y);
          bag *y_support;
          y_support = GC_OBJECT(bag,enumerate_any(x));
          for (START(y_support); NEXT(y);)
          { GC_LOOP;
            { write_value_Variable(self->var,y);
              GC__ANY(res = res->addFast((OID)GC_OID(OPT_EVAL(self->arg))), 1);
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        if (((self->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         { { OID  x;
            { { OID  x_some = CNULL;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(x);
                  for (START(res); NEXT(x);)
                  { GC_LOOP;
                    if (belong_to(x,_oid_(self->of)) != CTRUE)
                     { x_some= (x);
                      GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                x = x_some;
                }
              GC_OID(x);}
            if (x != CNULL)
             close_exception(((range_error *) (*Core._range_error)(_oid_(self),
              x,
              GC_OID(_oid_(self->of)))));
            else ;}
          cast_I_set1(res,self->of);
          }
        Result = _oid_(res);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// [select VAR in SET_EXPR, ...] is the same as a "for" but returns the subset of
//  members that produce a true value
//
// The c++ function for: self_print(self:Select) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_Select_Language(Select *self) { 
    
    GC_BIND;
    { CL_INT  g0500 = (CL_INT )(current_color);
      CL_INT  g0501 = (CL_INT )(current_bold);
      CL_INT  g0502 = g0500;
      CL_INT  g0503 = g0501;
      color(g0500,g0501);
      color_princ_string1(((char*)"{ "));
      g0500= (CL_INT)((CL_INT )(current_color));
      g0501= (CL_INT)((CL_INT )(current_bold));
      color(g0502,g0503);
      ppvariable_Variable(GC_OBJECT(Variable,self->var));
      color(g0500,g0501);
      color(g0500,g0501);
      color_princ_string1(((char*)" `BLUEin `BLACK"));
      g0500= (CL_INT)((CL_INT )(current_color));
      g0501= (CL_INT)((CL_INT )(current_bold));
      color(g0502,g0503);
      { CL_INT  _Zl = Core.pretty->index;
        set_level_void();
        printexp_any(GC_OID(self->set_arg),CFALSE);
        _void_(Core.pretty->index = _Zl);
        }
      color(g0500,g0501);
      color(g0500,g0501);
      color_princ_string1(((char*)" | "));
      g0500= (CL_INT)((CL_INT )(current_color));
      g0501= (CL_INT)((CL_INT )(current_bold));
      color(g0502,g0503);
      lbreak_integer(2);
      print_any(GC_OID(self->arg));
      _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
      color(g0500,g0501);
      color(g0500,g0501);
      color_princ_string1(((char*)"}"));
      color(g0502,g0503);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Select) [NEW_ALLOC]
CL_EXPORT OID  self_eval_Select(Select *self) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { OID Result = 0;
      { OID  x = GC_OID(OPT_EVAL(self->set_arg));
        set * res;
        { bag *V_CC ;
          if (Kernel._set == OWNER(x))
           V_CC = empty_bag(OBJECT(bag,x));
          else V_CC = set::empty();
            res= (set *) V_CC;}
        if (INHERIT(OWNER(x),Kernel._class))
         { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(y);
          for (START(OBJECT(ClaireClass,x)->descendents); NEXT(y);)
          { GC_LOOP;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(z);
              for (START(OBJECT(ClaireClass,y)->instances); NEXT(z);)
              { GC_LOOP;
                { write_value_Variable(self->var,z);
                  if (OPT_EVAL(self->arg) != Kernel.cfalse)
                   GC__ANY(res = res->addFast((OID)z), 1);
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        else { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(y);
            bag *y_support;
            y_support = GC_OBJECT(bag,enumerate_any(x));
            for (START(y_support); NEXT(y);)
            { GC_LOOP;
              { write_value_Variable(self->var,y);
                if (OPT_EVAL(self->arg) != Kernel.cfalse)
                 res= (res->addFast((OID)y));
                }
              GC_UNLOOP; POP_SIGNAL;}
            }
          if (((self->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         { { OID  x;
            { { OID  x_some = CNULL;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(x);
                  for (START(res); NEXT(x);)
                  { GC_LOOP;
                    if (belong_to(x,_oid_(self->of)) != CTRUE)
                     { x_some= (x);
                      GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                x = x_some;
                }
              GC_OID(x);}
            if (x != CNULL)
             close_exception(((range_error *) (*Core._range_error)(_oid_(self),
              x,
              GC_OID(_oid_(self->of)))));
            else ;}
          cast_I_set1(res,self->of);
          }
        Result = _oid_(res);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// [select VAR in SET_EXPR, ...] is the same as a "for" but returns the subset of
//  members that produce a true value
//
// The c++ function for: self_print(self:Lselect) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_Lselect_Language(Lselect *self) { 
    
    GC_BIND;
    { CL_INT  g0505 = (CL_INT )(current_color);
      CL_INT  g0506 = (CL_INT )(current_bold);
      CL_INT  g0507 = g0505;
      CL_INT  g0508 = g0506;
      color(g0505,g0506);
      color_princ_string1(((char*)"list{ "));
      g0505= (CL_INT)((CL_INT )(current_color));
      g0506= (CL_INT)((CL_INT )(current_bold));
      color(g0507,g0508);
      ppvariable_Variable(GC_OBJECT(Variable,self->var));
      color(g0505,g0506);
      color(g0505,g0506);
      color_princ_string1(((char*)" `BLUEin `BLACK"));
      g0505= (CL_INT)((CL_INT )(current_color));
      g0506= (CL_INT)((CL_INT )(current_bold));
      color(g0507,g0508);
      { CL_INT  _Zl = Core.pretty->index;
        set_level_void();
        printexp_any(GC_OID(self->set_arg),CFALSE);
        _void_(Core.pretty->index = _Zl);
        }
      color(g0505,g0506);
      color(g0505,g0506);
      color_princ_string1(((char*)" | "));
      g0505= (CL_INT)((CL_INT )(current_color));
      g0506= (CL_INT)((CL_INT )(current_bold));
      color(g0507,g0508);
      lbreak_integer(2);
      print_any(GC_OID(self->arg));
      _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
      color(g0505,g0506);
      color(g0505,g0506);
      color_princ_string1(((char*)"}"));
      color(g0507,g0508);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Lselect) [NEW_ALLOC]
CL_EXPORT OID  self_eval_Lselect(Lselect *self) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { OID Result = 0;
      { OID  x = GC_OID(OPT_EVAL(self->set_arg));
        list * res;
        { bag *V_CC ;
          if (INHERIT(OWNER(x),Kernel._list))
           V_CC = empty_bag(OBJECT(bag,x));
          else V_CC = list::empty();
            res= (list *) V_CC;}
        if (INHERIT(OWNER(x),Kernel._class))
         { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(y);
          for (START(OBJECT(ClaireClass,x)->descendents); NEXT(y);)
          { GC_LOOP;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(z);
              for (START(OBJECT(ClaireClass,y)->instances); NEXT(z);)
              { GC_LOOP;
                { write_value_Variable(self->var,z);
                  if (OPT_EVAL(self->arg) != Kernel.cfalse)
                   GC__ANY(res = res->addFast((OID)z), 1);
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        else { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(y);
            bag *y_support;
            y_support = GC_OBJECT(bag,enumerate_any(x));
            for (START(y_support); NEXT(y);)
            { GC_LOOP;
              { write_value_Variable(self->var,y);
                if (OPT_EVAL(self->arg) != Kernel.cfalse)
                 res= (res->addFast((OID)y));
                }
              GC_UNLOOP; POP_SIGNAL;}
            }
          if (((self->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         { { OID  x;
            { { OID  x_some = CNULL;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(x);
                  for (START(res); NEXT(x);)
                  { GC_LOOP;
                    if (belong_to(x,_oid_(self->of)) != CTRUE)
                     { x_some= (x);
                      GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                x = x_some;
                }
              GC_OID(x);}
            if (x != CNULL)
             close_exception(((range_error *) (*Core._range_error)(_oid_(self),
              x,
              GC_OID(_oid_(self->of)))));
            else ;}
          cast_I_list1(res,self->of);
          }
        Result = _oid_(res);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// Exists is an iteration that checks a condition
// other = true => forall,  other = false => exists, other = unknown => some
// The c++ function for: self_print(self:Exists) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_Exists_Language(Exists *self) { 
    
    GC_BIND;
    if (self->other == Kernel.ctrue)
     color_princ_string1(((char*)"`BLUEforall`BLACK"));
    else if (self->other == Kernel.cfalse)
     color_princ_string1(((char*)"`BLUEexists`BLACK"));
    else color_princ_string1(((char*)"`BLUEsome`BLACK"));
      if (self->set_arg == _oid_(Kernel._any))
     { princ_string(((char*)"("));
      ppvariable_Variable(GC_OBJECT(Variable,self->var));
      princ_string(((char*)","));
      print_any(GC_OID(self->arg));
      princ_string(((char*)")"));
      }
    else { CL_INT  g0510 = (CL_INT )(current_color);
        CL_INT  g0511 = (CL_INT )(current_bold);
        CL_INT  g0512 = g0510;
        CL_INT  g0513 = g0511;
        color(g0510,g0511);
        color_princ_string1(((char*)"("));
        g0510= (CL_INT)((CL_INT )(current_color));
        g0511= (CL_INT)((CL_INT )(current_bold));
        color(g0512,g0513);
        ppvariable_Variable(GC_OBJECT(Variable,self->var));
        color(g0510,g0511);
        color(g0510,g0511);
        color_princ_string1(((char*)" `BLUEin `BLACK"));
        g0510= (CL_INT)((CL_INT )(current_color));
        g0511= (CL_INT)((CL_INT )(current_bold));
        color(g0512,g0513);
        { CL_INT  _Zl = Core.pretty->index;
          set_level_void();
          printexp_any(GC_OID(self->set_arg),CFALSE);
          _void_(Core.pretty->index = _Zl);
          }
        color(g0510,g0511);
        color(g0510,g0511);
        color_princ_string1(((char*)" | "));
        g0510= (CL_INT)((CL_INT )(current_color));
        g0511= (CL_INT)((CL_INT )(current_bold));
        color(g0512,g0513);
        lbreak_integer(2);
        print_any(GC_OID(self->arg));
        _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
        color(g0510,g0511);
        color(g0510,g0511);
        color_princ_string1(((char*)")"));
        color(g0512,g0513);
        }
      GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Exists) [NEW_ALLOC]
CL_EXPORT OID  self_eval_Exists(Exists *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  x = GC_OID(OPT_EVAL(self->set_arg));
        OID  b = self->other;
        OID  res = b;
        if (INHERIT(OWNER(x),Kernel._class))
         { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(y);
          for (START(OBJECT(ClaireClass,x)->descendents); NEXT(y);)
          { GC_LOOP;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(z);
              for (START(OBJECT(ClaireClass,y)->instances); NEXT(z);)
              { GC_LOOP;
                { write_value_Variable(self->var,z);
                  if (OPT_EVAL(self->arg) != Kernel.cfalse)
                   { if (b != Kernel.ctrue)
                     { if (boolean_I_any(b) == CTRUE)
                       res = z;
                      else res = Kernel.ctrue;
                        GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                    }
                  else if (b == Kernel.ctrue)
                   { res= (Kernel.cfalse);
                    GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        else { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(y);
            bag *y_support;
            y_support = GC_OBJECT(bag,enumerate_any(x));
            for (START(y_support); NEXT(y);)
            { GC_LOOP;
              { write_value_Variable(self->var,y);
                if (OPT_EVAL(self->arg) != Kernel.cfalse)
                 { if (b != Kernel.ctrue)
                   { if (boolean_I_any(b) == CTRUE)
                     res = y;
                    else res = Kernel.ctrue;
                      GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                  }
                else if (b == Kernel.ctrue)
                 { res= (Kernel.cfalse);
                  GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                }
              GC_UNLOOP; POP_SIGNAL;}
            }
          Result = res;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// *********************************************************************
// *     Part 3: other control structures                              *
// *********************************************************************
// ----------------- case  --------------------------------------
// The c++ function for: self_print(self:Case) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_print_Case_Language(Case *self) { 
    
    GC_BIND;
    { CL_INT  g0516 = (CL_INT )(current_color);
      CL_INT  g0517 = (CL_INT )(current_bold);
      CL_INT  g0518 = g0516;
      CL_INT  g0519 = g0517;
      color(g0516,g0517);
      color_princ_string1(((char*)"`BLUEcase `BLACK"));
      g0516= (CL_INT)((CL_INT )(current_color));
      g0517= (CL_INT)((CL_INT )(current_bold));
      color(g0518,g0519);
      print_any(GC_OID(self->var));
      color(g0516,g0517);
      color(g0516,g0517);
      color_princ_string1(((char*)" "));
      g0516= (CL_INT)((CL_INT )(current_color));
      g0517= (CL_INT)((CL_INT )(current_bold));
      color(g0518,g0519);
      lbreak_integer(1);
      color(g0516,g0517);
      color(g0516,g0517);
      color_princ_string1(((char*)"("));
      color(g0518,g0519);
      }
    { CL_INT  n = 1;
      CL_INT  m = self->args->length;
      _void_(Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)1));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)n <= (CL_INT)m))
        { GC_LOOP;
          { CL_INT  _Zl = Core.pretty->index;
            printexp_any(GC_OID((*(self->args))[n]),CFALSE);
            princ_string(((char*)" "));
            if ((CL_INT)buffer_length_void() > (CL_INT)((CL_INT)Core.pretty->width-(CL_INT)50))
             lbreak_integer(2);
            else set_level_void();
              print_any(GC_OID((*(self->args))[((CL_INT)n+(CL_INT)1)]));
            _void_(Core.pretty->index = _Zl);
            if (((CL_INT)n+(CL_INT)1) != m)
             { princ_string(((char*)", "));
              lbreak_void();
              }
            else ;n= (CL_INT)(((CL_INT)n+(CL_INT)2));
            }
          GC_UNLOOP;POP_SIGNAL;}
        }
      princ_string(((char*)")"));
      _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Case) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_eval_Case(Case *self) { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    { OID Result = 0;
      { OID  truc = GC_OID(eval_any(GC_OID(self->var)));
        ClaireBoolean * flip = CTRUE;
        OID  previous = Kernel.cfalse;
        CL_INT  n = ClEnv->trace_I;
        CL_INT  d = ClEnv->debug_I;
        if (((CL_INT)n > (CL_INT)0) && 
            ((CL_INT)n <= (CL_INT)ClEnv->step_I))
         { _void_(ClEnv->trace_I = 0);
          _void_(ClEnv->debug_I = -1);
          { CL_INT  g0520 = (CL_INT )(current_color);
            CL_INT  g0521 = (CL_INT )(current_bold);
            CL_INT  g0522 = g0520;
            CL_INT  g0523 = g0521;
            color(g0520,g0521);
            color_princ_string1(((char*)"  `BLUEcase "));
            g0520= (CL_INT)((CL_INT )(current_color));
            g0521= (CL_INT)((CL_INT )(current_bold));
            color(g0522,g0523);
            print_any(truc);
            color(g0520,g0521);
            color(g0520,g0521);
            color_princ_string1(((char*)"\n"));
            color(g0522,g0523);
            }
          _void_(ClEnv->debug_I = d);
          _void_(ClEnv->trace_I = n);
          }
        { OID  res;
          { ClaireBoolean * g0528I;
            { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(x);
                V_C= Kernel.cfalse;
                bag *x_support;
                x_support = GC_OBJECT(list,self->args);
                for (START(x_support); NEXT(x);)
                { GC_LOOP;
                  if (flip == CTRUE)
                   { flip= (CFALSE);
                    GC__OID(previous = OPT_EVAL(x), 1);
                    }
                  else if (belong_to(truc,previous) == CTRUE)
                   { GC__OID(previous = OPT_EVAL(x), 2);
                    { GC_UNLOOP;V_C = Kernel.ctrue;
                      ClEnv->cHandle = loop_handle;break;}
                    }
                  else flip= (CTRUE);
                    GC_UNLOOP; POP_SIGNAL;}
                }
              
              g0528I=OBJECT(ClaireBoolean,V_C);}
            
            if (g0528I == CTRUE) res = previous;
              else res = Kernel.cfalse;
            }
          if (((CL_INT)n > (CL_INT)0) && 
              ((CL_INT)n <= (CL_INT)ClEnv->step_I))
           { _void_(ClEnv->trace_I = 0);
            _void_(ClEnv->debug_I = -1);
            { CL_INT  g0524 = (CL_INT )(current_color);
              CL_INT  g0525 = (CL_INT )(current_bold);
              CL_INT  g0526 = g0524;
              CL_INT  g0527 = g0525;
              color(g0524,g0525);
              color_princ_string1(((char*)"  `BLUEcase -> "));
              g0524= (CL_INT)((CL_INT )(current_color));
              g0525= (CL_INT)((CL_INT )(current_bold));
              color(g0526,g0527);
              print_any(res);
              color(g0524,g0525);
              color(g0524,g0525);
              color_princ_string1(((char*)"\n"));
              color(g0526,g0527);
              }
            _void_(ClEnv->debug_I = d);
            _void_(ClEnv->trace_I = n);
            }
          Result = res;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// ------------------ WHILE  and UNTIL  -----------------------------
// the "other" while is until, where the first test is skipped
// The c++ function for: self_print(self:While) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_print_While_Language(While *self) { 
    
    GC_BIND;
    { CL_INT  g0530 = (CL_INT )(current_color);
      CL_INT  g0531 = (CL_INT )(current_bold);
      CL_INT  g0532 = g0530;
      CL_INT  g0533 = g0531;
      color(g0530,g0531);
      color_princ_string1(((char*)"`BLUE"));
      g0530= (CL_INT)((CL_INT )(current_color));
      g0531= (CL_INT)((CL_INT )(current_bold));
      color(g0532,g0533);
      princ_string(((self->other == CTRUE) ?
        ((char*)"until") :
        ((char*)"while") ));
      color(g0530,g0531);
      color(g0530,g0531);
      color_princ_string1(((char*)" `BLACK"));
      g0530= (CL_INT)((CL_INT )(current_color));
      g0531= (CL_INT)((CL_INT )(current_bold));
      color(g0532,g0533);
      printexp_any(GC_OID(self->test),CFALSE);
      color(g0530,g0531);
      color(g0530,g0531);
      color_princ_string1(((char*)" "));
      g0530= (CL_INT)((CL_INT )(current_color));
      g0531= (CL_INT)((CL_INT )(current_bold));
      color(g0532,g0533);
      lbreak_integer(2);
      color(g0530,g0531);
      color(g0532,g0533);
      print_any(GC_OID(self->arg));
      color(g0530,g0531);
      color(g0532,g0533);
      }
    _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:While) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_eval_While(While *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT  n = ClEnv->trace_I;
        CL_INT  d = ClEnv->debug_I;
        ClaireBoolean * a = self->other;
        ClaireBoolean * b = a;
        OID  res;
        { ClaireHandler c_handle = ClaireHandler();
          if ERROR_IN 
          { { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ClaireBoolean *v_while;
              res= _oid_(CFALSE);
              v_while = ((b == CTRUE) ? CTRUE : ((not_any(eval_any(GC_OID(self->test))) == a) ? CTRUE : CFALSE));
              
              while (v_while == CTRUE)
              { GC_LOOP;
                b= (CFALSE);
                eval_any(GC_OID(self->arg));
                v_while = ((b == CTRUE) ? CTRUE : ((not_any(eval_any(GC_OID(self->test))) == a) ? CTRUE : CFALSE));
                GC_UNLOOP;POP_SIGNAL;}
              }
            ERROR_FREE;}
          else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Core._return_error)) == CTRUE)
          { c_handle.catchIt();res = (*Kernel.arg)(GC_OID(_oid_(ClEnv->exception_I)));
            }
          else PREVIOUS_HANDLER;}
        if (((CL_INT)n > (CL_INT)0) && 
            ((CL_INT)n <= (CL_INT)ClEnv->step_I))
         { _void_(ClEnv->trace_I = 0);
          _void_(ClEnv->debug_I = -1);
          if (self->other == CTRUE)
           { CL_INT  g0534 = (CL_INT )(current_color);
            CL_INT  g0535 = (CL_INT )(current_bold);
            CL_INT  g0536 = g0534;
            CL_INT  g0537 = g0535;
            color(g0534,g0535);
            color_princ_string1(((char*)"  `BLUEuntil -> "));
            g0534= (CL_INT)((CL_INT )(current_color));
            g0535= (CL_INT)((CL_INT )(current_bold));
            color(g0536,g0537);
            print_any(res);
            color(g0534,g0535);
            color(g0534,g0535);
            color_princ_string1(((char*)"\n"));
            color(g0536,g0537);
            }
          else { CL_INT  g0538 = (CL_INT )(current_color);
              CL_INT  g0539 = (CL_INT )(current_bold);
              CL_INT  g0540 = g0538;
              CL_INT  g0541 = g0539;
              color(g0538,g0539);
              color_princ_string1(((char*)"  `BLUEwhile -> "));
              g0538= (CL_INT)((CL_INT )(current_color));
              g0539= (CL_INT)((CL_INT )(current_bold));
              color(g0540,g0541);
              print_any(res);
              color(g0538,g0539);
              color(g0538,g0539);
              color_princ_string1(((char*)"\n"));
              color(g0540,g0541);
              }
            _void_(ClEnv->debug_I = d);
          _void_(ClEnv->trace_I = n);
          }
        Result = res;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//-------------- handling errors -----------------------------------
// This is the control structure associated with these errors. Its real
// semantics is defined in the C compiler file
//
// The c++ function for: self_print(self:Handle) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_print_Handle_Language(ClaireHandle *self) { 
    
    GC_BIND;
    { CL_INT  g0543 = (CL_INT )(current_color);
      CL_INT  g0544 = (CL_INT )(current_bold);
      CL_INT  g0545 = g0543;
      CL_INT  g0546 = g0544;
      color(g0543,g0544);
      color_princ_string1(((char*)"`BLUEtry `BLACK"));
      g0543= (CL_INT)((CL_INT )(current_color));
      g0544= (CL_INT)((CL_INT )(current_bold));
      color(g0545,g0546);
      print_any(GC_OID(self->arg));
      color(g0543,g0544);
      color(g0543,g0544);
      color_princ_string1(((char*)" "));
      g0543= (CL_INT)((CL_INT )(current_color));
      g0544= (CL_INT)((CL_INT )(current_bold));
      color(g0545,g0546);
      lbreak_integer(0);
      color(g0543,g0544);
      color(g0543,g0544);
      color_princ_string1(((char*)"`BLUEcatch `BLACK"));
      g0543= (CL_INT)((CL_INT )(current_color));
      g0544= (CL_INT)((CL_INT )(current_bold));
      color(g0545,g0546);
      print_any(GC_OID(self->test));
      color(g0543,g0544);
      color(g0543,g0544);
      color_princ_string1(((char*)" "));
      g0543= (CL_INT)((CL_INT )(current_color));
      g0544= (CL_INT)((CL_INT )(current_bold));
      color(g0545,g0546);
      print_any(GC_OID(self->other));
      color(g0543,g0544);
      color(g0545,g0546);
      }
    _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_eval(self:Handle) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  self_eval_Handle(ClaireHandle *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  x = GC_OID(OPT_EVAL(self->test));
        { ClaireHandler c_handle = ClaireHandler();
          if ERROR_IN 
          { Result = OPT_EVAL(self->arg);
            ERROR_FREE;}
          else if (belong_to(_oid_(ClEnv->exception_I),x) == CTRUE)
          { c_handle.catchIt();if (INHERIT(ClEnv->exception_I->isa,Core._return_error))
             { OID  V_CL0547;close_exception(ClEnv->exception_I);
              
              Result=_void_(V_CL0547);}
            else Result = OPT_EVAL(self->other);
              }
          else PREVIOUS_HANDLER;}
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// <yc> 6/98
// *********************************************************************
// *     Part 4: the constructs                                         *
// *********************************************************************
// v3.2.16   constructor for arrays
// The c++ function for: self_print(self:Construct) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_print_Construct_Language(Construct *self) { 
    
    GC_BIND;
    { CL_INT  _Zl = Core.pretty->index;
      if (INHERIT(self->isa,Language._List))
       princ_string(((char*)"list"));
      else if (INHERIT(self->isa,Language._Set))
       princ_string(((char*)"set"));
      else if (INHERIT(self->isa,Language._Tuple))
       princ_string(((char*)"tuple"));
      else if (INHERIT(self->isa,Language._Printf))
       color_princ_string1(((char*)"`BLUEprintf`BLACK"));
      else if (INHERIT(self->isa,Language._Error))
       princ_string(((char*)"error"));
      else if (INHERIT(self->isa,Language._Trace))
       color_princ_string1(((char*)"`BLUEtrace`BLACK"));
      else if (INHERIT(self->isa,Language._Assert))
       color_princ_string1(((char*)"`BLUEassert`BLACK"));
      else if (INHERIT(self->isa,Language._Branch))
       color_princ_string1(((char*)"`BLUEbranch`BLACK"));
      else princ_string(string_I_symbol(self->isa->name));
        if ((INHERIT(self->isa,Language._List)) || 
          (INHERIT(self->isa,Language._Set)))
       { OID  _Zt = GC_OID(get_property(Kernel.of,self));
        if (_Zt != CNULL)
         { if (equal(_Zt,_oid_(Kernel.emptySet)) != CTRUE)
           { princ_string(((char*)"<"));
            print_any(_Zt);
            princ_string(((char*)">"));
            }
          }
        else ;}
      princ_string(((char*)"("));
      set_level_void();
      printbox_bag2(GC_OBJECT(list,self->args));
      princ_string(((char*)")"));
      _void_(Core.pretty->index = _Zl);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// constructors: how to create a list, a set, a tuple or an array
// note that the constructor is typed
// The c++ function for: self_eval(self:List) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  self_eval_List(List *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { list * l;
        { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID x; CL_INT CLcount;
            v_list = self->args;
             l = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { x = (*(v_list))[CLcount];
              v_val = OPT_EVAL(x);
              
              (*((list *) l))[CLcount] = v_val;}
            }
          GC_OBJECT(list,l);}
        if (((self->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         { { OID  x;
            { { OID  x_some = CNULL;
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(x);
                  for (START(l); NEXT(x);)
                  if (belong_to(x,_oid_(self->of)) != CTRUE)
                   { x_some= (x);
                    ClEnv->cHandle = loop_handle; break;}
                  }
                x = x_some;
                }
              GC_OID(x);}
            if (x != CNULL)
             close_exception(((range_error *) (*Core._range_error)(_oid_(self),
              x,
              GC_OID(_oid_(self->of)))));
            else ;}
          Result = _oid_(cast_I_list1(l,self->of));
          }
        else Result = _oid_(cast_I_list1(l,Kernel.emptySet));
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// v3.2
// The c++ function for: self_eval(self:Set) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  self_eval_Set(Set *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { set * s;
        { { list * g0548UU;
            { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID x; CL_INT CLcount;
                v_list = self->args;
                 g0548UU = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { x = (*(v_list))[CLcount];
                  v_val = OPT_EVAL(x);
                  
                  (*((list *) g0548UU))[CLcount] = v_val;}
                }
              GC_OBJECT(list,g0548UU);}
            s = set_I_bag(g0548UU);
            }
          GC_OBJECT(set,s);}
        if (((self->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         { { OID  x;
            { { OID  x_some = CNULL;
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(x);
                  for (START(s); NEXT(x);)
                  if (belong_to(x,_oid_(self->of)) != CTRUE)
                   { x_some= (x);
                    ClEnv->cHandle = loop_handle; break;}
                  }
                x = x_some;
                }
              GC_OID(x);}
            if (x != CNULL)
             close_exception(((range_error *) (*Core._range_error)(_oid_(self),
              x,
              GC_OID(_oid_(self->of)))));
            else ;}
          Result = _oid_(cast_I_set1(s,self->of));
          }
        else Result = _oid_(cast_I_set1(s,Kernel.emptySet));
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: self_eval(self:Tuple) [NEW_ALLOC]
CL_EXPORT OID  self_eval_Tuple(Tuple *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { tuple * V_CL0549;{ list * g0550UU;
          { { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID x; CL_INT CLcount;
              v_list = self->args;
               g0550UU = v_list->clone();
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { x = (*(v_list))[CLcount];
                v_val = OPT_EVAL(x);
                
                (*((list *) g0550UU))[CLcount] = v_val;}
              }
            GC_OBJECT(list,g0550UU);}
          V_CL0549 = tuple_I_list(g0550UU);
          }
        
        Result=_oid_(V_CL0549);}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// v3.2.16 - introduce a nicer way to create an array
// The c++ function for: self_eval(self:Array) [NEW_ALLOC]
CL_EXPORT OID  self_eval_Array2(Array *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { list * l;
        { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID x; CL_INT CLcount;
            v_list = self->args;
             l = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { x = (*(v_list))[CLcount];
              v_val = OPT_EVAL(x);
              
              (*((list *) l))[CLcount] = v_val;}
            }
          GC_OBJECT(list,l);}
        if (((self->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         { { OID  x;
            { { OID  x_some = CNULL;
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(x);
                  for (START(l); NEXT(x);)
                  if (belong_to(x,_oid_(self->of)) != CTRUE)
                   { x_some= (x);
                    ClEnv->cHandle = loop_handle; break;}
                  }
                x = x_some;
                }
              GC_OID(x);}
            if (x != CNULL)
             close_exception(((range_error *) (*Core._range_error)(_oid_(self),
              x,
              GC_OID(_oid_(self->of)))));
            else ;}
          cast_I_list1(l,self->of);
          }
        else cast_I_list1(l,Kernel._any);
          Result = _array_(array_I_list(l));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// Macros are a nice but undocumented feature of CLAIRE. This is deliberate
//
// The c++ function for: self_eval(self:Macro) [NEW_ALLOC]
CL_EXPORT OID  self_eval_Macro2(Macro *self) { 
    
    GC_BIND;
    { OID Result = 0;
      Result = eval_any(GC_OID((*Language.macroexpand)(_oid_(self))));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// error produces an exception of type general_error
// The c++ function for: self_eval(self:Error) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_eval_Error(Error *self) { 
    
    GC_BIND;
    if (ClEnv->debug_I != ((CL_INT)-1))
     { CL_INT  d_I = ClEnv->debug_I;
      CL_INT  st = ((CL_INT)1+(CL_INT)ClEnv->index);
      PUSH(_oid_(self));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(x);
        bag *x_support;
        x_support = GC_OBJECT(list,self->args);
        for (START(x_support); NEXT(x);)
        PUSH(x);
        }
      _void_(ClEnv->debug_I = ClEnv->index);
      PUSH(((OID)d_I));
      PUSH(_oid_(Kernel._error));
      PUSH(((OID)self->args->length));
      PUSH(((OID)st));
      }
    if ((boolean_I_any(_oid_(self->args)) != CTRUE) || 
        (equal(_oid_(Kernel._string),_oid_(OWNER((*(self->args))[1]))) != CTRUE))
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Syntax error: ~S")),
      _oid_(list::alloc(1,_oid_(self))))));
    { general_error * x = GC_OBJECT(general_error,((general_error *) new_object_class(Core._general_error)));
      _void_(x->cause = car_list(self->args));
      { general_error * g0551 = x; 
        OID  g0552;
        { list * V_CL0553;{ CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID x; CL_INT CLcount;
            v_list = cdr_list(GC_OBJECT(list,self->args));
             V_CL0553 = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { x = (*(v_list))[CLcount];
              v_val = OPT_EVAL(x);
              
              (*((list *) V_CL0553))[CLcount] = v_val;}
            }
          
          g0552=_oid_(V_CL0553);}
        _void_(g0551->arg = g0552);}
      close_exception(x);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// this is the basic tool for printing in CLAIRE. A complex statement
// is macroexpanded into basic printing instructions
//
// The c++ function for: self_eval(self:Printf) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_eval_Printf(Printf *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { list * larg = GC_OBJECT(list,self->args);
        ClaireBoolean * onport_ask = inherit_ask_class(owner_any(OPT_EVAL((*(larg))[1])),Kernel._port);
        OID  s;
        if (onport_ask == CTRUE)
         s = (*(larg))[2];
        else s = (*(larg))[1];
          if (equal(_oid_(Kernel._string),_oid_(OWNER(s))) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[102] the first argument in ~S must be a string or a port")),
          _oid_(list::alloc(1,_oid_(self))))));
        else { CL_INT  n = find_string2(string_v(s),((char*)"~"));
            CL_INT  idx = 1;
            PortObject * p = use_as_output_port(((onport_ask == CTRUE) ?
              OBJECT(PortObject,OPT_EVAL((*(larg))[1])) :
              ClEnv->cout ));
            CL_INT  nl = ((onport_ask == CTRUE) ?
              3 :
              2 );
            CL_INT  len = ((CL_INT)(*Kernel.length)(s));
            CL_INT  col = (CL_INT )(current_color);
            CL_INT  bold = (CL_INT )(current_bold);
            CL_INT  ccol = col;
            CL_INT  cbold = bold;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while ((((CL_INT)0 < (CL_INT)n) && 
                  ((CL_INT)n < (CL_INT)len)))
              { GC_LOOP;
                { OID  m = GC_OID((*Kernel.nth)(s,
                    ((OID)((CL_INT)n+(CL_INT)1))));
                  if ((CL_INT)n > (CL_INT)1)
                   { color(ccol,cbold);
                    color_princ_string2(string_v(s),idx,((CL_INT)n-(CL_INT)1));
                    {ccol = current_color; cbold = current_bold;};
                    }
                  if (_oid_(_char_(((unsigned char)'A'))) == m)
                   { color(col,bold);
                    (*Kernel.princ)(GC_OID(OPT_EVAL((*(larg))[nl])));
                    color(ccol,cbold);
                    }
                  else if (_oid_(_char_(((unsigned char)'S'))) == m)
                   { color(col,bold);
                    print_any(GC_OID(OPT_EVAL((*(larg))[nl])));
                    color(ccol,cbold);
                    }
                  else if (_oid_(_char_(((unsigned char)'I'))) == m)
                   { color(col,bold);
                    OPT_EVAL((*(larg))[nl]);
                    color(ccol,cbold);
                    }
                  if (m != _oid_(_char_(((unsigned char)'%'))))
                   ++nl;
                  idx= (CL_INT)(((CL_INT)n+(CL_INT)2));
                  n= (CL_INT)(find_string(string_v(s),((char*)"~"),idx));
                  }
                GC_UNLOOP;POP_SIGNAL;}
              }
            if ((CL_INT)idx <= (CL_INT)len)
             { color(ccol,cbold);
              color_princ_string2(string_v(s),idx,len);
              }
            color(col,bold);
            use_as_output_port(p);
            }
          Result = CNULL;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// trace is refined in inspect.cl
// If trace_output() is known, use it, else use current output.
//<sb> v3.3.33 forked process also print their pid 
//<sb> modified trace strategy (see mtformat)
// The c++ function for: self_eval(self:Trace) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_eval_Trace(Trace *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { list * a = GC_OBJECT(list,self->args);
        list * l;
        { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID x; CL_INT CLcount;
            v_list = a;
             l = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { x = (*(v_list))[CLcount];
              v_val = OPT_EVAL(x);
              
              (*((list *) l))[CLcount] = v_val;}
            }
          GC_OBJECT(list,l);}
        OID  i = (*(l))[1];
        OID  a2;
        if ((CL_INT)a->length > (CL_INT)1)
         a2 = (*(a))[2];
        else a2 = Kernel.cfalse;
          if ((Kernel._string == OWNER(a2)) && 
            ((INHERIT(OWNER(i),Kernel._integer)) && (CTRUE == CTRUE)))
         mtformat_module1(ClEnv->module_I,string_v(a2),((CL_INT)i),skip_list(l,2));
        Result = _oid_(Kernel.emptySet);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// assert is refined in trace.la
//
// The c++ function for: self_eval(self:Assert) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_eval_Assert(Assert *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { list * a = GC_OBJECT(list,self->args);
        if (((CL_INT)a->length > (CL_INT)0) && 
            ((get_property(Kernel.ctrace,ClEnv) != CNULL) && 
              (boolean_I_any(OPT_EVAL((*(a))[1])) != CTRUE)))
         { PortObject * p = use_as_output_port(ClEnv->ctrace);
          print_any(GC_OID(_string_(self->external)));
          princ_string(((char*)",line="));
          princ_integer(self->index);
          princ_string(((char*)": (ASSERT) "));
          print_any((*(a))[1]);
          princ_string(((char*)"\n"));
          use_as_output_port(p);
          if ((CL_INT)0 <= (CL_INT)ClEnv->debug_I)
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"Assertion Violation")),
            _oid_(Kernel.nil))));
          Result = _oid_(Kernel.emptySet);
          }
        else Result = Kernel.cfalse;
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: self_eval(self:Branch) [NEW_ALLOC]
CL_EXPORT OID  self_eval_Branch(Branch *self) { 
    
    GC_BIND;
    if (self->args->length != 1)
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[104] Syntax error with ~S (one arg. expected)")),
      _oid_(list::alloc(1,_oid_(self))))));
    { OID Result = 0;
      { ClaireHandler c_handle = ClaireHandler();
        if ERROR_IN 
        { { world_push();
            if (OPT_EVAL((*(self->args))[1]) != Kernel.cfalse)
             Result = Kernel.ctrue;
            else { world_pop();
                Result = Kernel.cfalse;
                }
              }
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Core._contradiction)) == CTRUE)
        { c_handle.catchIt();{ world_pop();
            Result = Kernel.cfalse;
            }
          }
        else PREVIOUS_HANDLER;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// end of file

/***** CLAIRE Compilation of file ./meta/define.cl 
         [version 3.5.0 / safety 5] *****/


//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| define.cl                                                   |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+
// ---------------------------------------------------------------------
// Contents:
//   Part 2: the instantiation macros
//   Part 3: the useful stuff
//   Part 4: the other macros
// ---------------------------------------------------------------------
// *********************************************************************
// *     Part 1: Definition                                            *
// *********************************************************************
// this is the basic class instantiation
//
// The c++ function for: self_print(self:Definition) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_print_Definition_Language(Definition *self) { 
    
    GC_BIND;
    print_any(_oid_(self->arg));
    princ_string(((char*)"("));
    printbox_bag2(GC_OBJECT(list,self->args));
    { OID Result = 0;
      princ_string(((char*)")"));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// ------------- named object definition ------------------------------
//
// The c++ function for: self_print(self:Defobj) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_Defobj_Language(Defobj *self) { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    if (self->arg == Core._global_variable)
     { OID  r = _oid_(Kernel._any);
      OID  v = CNULL;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(x);
        bag *x_support;
        x_support = GC_OBJECT(list,self->args);
        for (START(x_support); NEXT(x);)
        { GC_LOOP;
          if ((*(OBJECT(Call,x)->args))[1] == _oid_(Kernel.value))
           GC__OID(v = (*(OBJECT(Call,x)->args))[2], 1);
          else if ((*(OBJECT(Call,x)->args))[1] == _oid_(Kernel.range))
           GC__OID(r = (*(OBJECT(Call,x)->args))[2], 2);
          GC_UNLOOP; POP_SIGNAL;}
        }
      if (boolean_I_any(r) == CTRUE)
       { princ_symbol(self->ident);
        princ_string(((char*)":"));
        print_any(r);
        princ_string(((char*)" := "));
        printexp_any(v,CFALSE);
        }
      else { princ_symbol(self->ident);
          princ_string(((char*)" :: "));
          printexp_any(v,CFALSE);
          }
        }
    else { princ_symbol(self->ident);
        princ_string(((char*)" :: "));
        print_any(_oid_(self->arg));
        princ_string(((char*)"("));
        printbox_bag2(GC_OBJECT(list,self->args));
        princ_string(((char*)")"));
        }
      GC_UNBIND; POP_SIGNAL;}
  


// ------------- class definition ------------------------------------
//
// The c++ function for: self_print(self:Defclass) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_Defclass_Language(Defclass *self) { 
    
    GC_BIND;
    princ_symbol(self->ident);
    if (self->params->length != 0)
     { princ_string(((char*)"["));
      princ_bag(GC_OBJECT(list,self->params));
      princ_string(((char*)"]"));
      }
    princ_string(((char*)" <: "));
    print_any(_oid_(self->arg));
    princ_string(((char*)"("));
    { CL_INT  _Zl = Core.pretty->index;
      list * l = GC_OBJECT(list,self->args);
      CL_INT  n = l->length;
      CL_INT  i = 1;
      CL_INT  g0554 = n;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)i <= (CL_INT)g0554))
        { GC_LOOP;
          if (i == 1)
           set_level_void();
          else lbreak_void();
            if (INHERIT(OWNER((*(l))[i]),Language._Vardef))
           (*Language.ppvariable)((*(l))[i]);
          else { (*Language.ppvariable)(GC_OID((*(OBJECT(bag,(*Core.args)((*(l))[i]))))[1]));
              princ_string(((char*)" = "));
              print_any(GC_OID((*(OBJECT(bag,(*Core.args)((*(l))[i]))))[2]));
              }
            if ((CL_INT)i < (CL_INT)n)
           princ_string(((char*)","));
          ++i;
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    princ_string(((char*)")"));
    GC_UNBIND; POP_SIGNAL;}
  


// -------------- method definition ----------------------------------
//
// The c++ function for: self_print(self:Defmethod) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_print_Defmethod_Language(Defmethod *self) { 
    
    GC_BIND;
    print_any(_oid_(self->arg->selector));
    princ_string(((char*)"("));
    if (((self->arg->args == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     ppvariable_list(GC_OBJECT(list,self->arg->args));
    princ_string(((char*)") : "));
    printexp_any(GC_OID(self->set_arg),CFALSE);
    lbreak_void();
    _void_(Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)4));
    princ_string(((char*)" "));
    princ_string(((boolean_I_any(self->inline_ask) == CTRUE) ?
      ((char*)"=>") :
      ((char*)"->") ));
    princ_string(((char*)" "));
    printexp_any(GC_OID(self->body),CFALSE);
    princ_string(((char*)" "));
    _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)4));
    GC_UNBIND; POP_SIGNAL;}
  


// -------------- array definition -----------------------------------
// The c++ function for: self_print(self:Defarray) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_print_Defarray_Language(Defarray *self) { 
    
    GC_BIND;
    print_any(GC_OID((*(self->arg->args))[1]));
    princ_string(((char*)"["));
    ppvariable_list(GC_OBJECT(list,cdr_list(GC_OBJECT(list,self->arg->args))));
    princ_string(((char*)"] : "));
    print_any(GC_OID(self->set_arg));
    lbreak_void();
    _void_(Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)4));
    princ_string(((char*)" := "));
    printexp_any(GC_OID(self->body),CFALSE);
    princ_string(((char*)" "));
    _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)4));
    GC_UNBIND; POP_SIGNAL;}
  


// -------------- rule definition ------------------------------------
// The c++ function for: self_print(self:Defrule) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  self_print_Defrule_Language(Defrule *self) { 
    
    GC_BIND;
    princ_symbol(self->ident);
    princ_string(((char*)"("));
    ppvariable_list(GC_OBJECT(list,self->args));
    princ_string(((char*)") :: rule("));
    lbreak_integer(4);
    princ_string(((char*)" "));
    print_any(GC_OID(self->arg));
    princ_string(((char*)" "));
    lbreak_integer(4);
    princ_string(((char*)"=> "));
    print_any(GC_OID(self->body));
    princ_string(((char*)")"));
    _void_(Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)4));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_print(self:Defvar) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_Defvar_Language(Defvar *self) { 
    
    GC_BIND;
    ppvariable_Variable(GC_OBJECT(Variable,self->ident));
    princ_string(((char*)" := "));
    printexp_any(GC_OID(self->arg),CFALSE);
    GC_UNBIND; POP_SIGNAL;}
  


// *********************************************************************
// *     Part 2: the general instantiation macro                       *
// *********************************************************************
// creation of a new object
//
// The c++ function for: self_eval(self:Definition) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_eval_Definition(Definition *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT  back_index = ClEnv->index;
        CL_INT  back_debug = ClEnv->debug_I;
        if (ClEnv->debug_I != ((CL_INT)-1))
         { CL_INT  d_I = ClEnv->debug_I;
          CL_INT  st = ((CL_INT)1+(CL_INT)ClEnv->index);
          PUSH(_oid_(self));
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(x);
            bag *x_support;
            x_support = GC_OBJECT(list,self->args);
            for (START(x_support); NEXT(x);)
            PUSH(x);
            }
          _void_(ClEnv->debug_I = ClEnv->index);
          PUSH(((OID)d_I));
          PUSH(_oid_(self->arg));
          PUSH(((OID)self->args->length));
          PUSH(((OID)st));
          }
        { ClaireClass * _Zc = self->arg;
          ClaireObject * _Zo;
          { { if ((CL_INT)_Zc->open <= (CL_INT)0)
               close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[105] cannot instantiate ~S")),
                _oid_(list::alloc(1,_oid_(_Zc))))));
              _Zo = new_object_class(_Zc);
              }
            GC_OBJECT(ClaireObject,_Zo);}
          if (_Zc->open != ClEnv->ephemeral)
           _void_(_Zc->instances = _Zc->instances->addFast((OID)_oid_(_Zo)));
          { OID  res = GC_OID(complete_object(_Zo,GC_OBJECT(list,self->args)));
            (ClEnv->index= ((OID)back_index));
            _void_(ClEnv->debug_I = back_debug);
            Result = res;
            }
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// the instantiation body is a sequence of words from which the initialization
// of the object must be built.
//
// The c++ function for: complete(self:object,%l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  complete_object(ClaireObject *self,list *_Zl) { 
    
    GC_BIND;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(x);
      for (START(_Zl); NEXT(x);)
      { GC_LOOP;
        { property * p = make_a_property_any(GC_OID((*(OBJECT(Call,x)->args))[1]));
          OID  y = GC_OID(eval_any(GC_OID((*(OBJECT(Call,x)->args))[2])));
          ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(p,self->isa));
          if (Kernel._slot == s->isa)
           { if (belong_to(y,_oid_(CLREAD(restriction,s,range))) != CTRUE)
             range_is_wrong_slot(((slot *) s),y);
            else update_property(p,
                self,
                CLREAD(slot,s,index),
                CLREAD(slot,s,srange),
                y);
              }
          else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[106] the object ~S does not understand ~S")),
              _oid_(list::alloc(2,_oid_(self),_oid_(p))))));
            }
        GC_UNLOOP; POP_SIGNAL;}
      }
    { OID Result = 0;
      Result = _oid_(complete_I_object(self));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// creation of a new named object
//
// The c++ function for: self_eval(self:Defobj) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  self_eval_Defobj(Defobj *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireClass * _Zc = self->arg;
        if ((CL_INT)_Zc->open <= (CL_INT)0)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[105] cannot instantiate ~S")),
          _oid_(list::alloc(1,_oid_(_Zc))))));
        if (INHERIT(_Zc,Kernel._thing))
         { thing * _Zo = new_thing_class(_Zc,self->ident);
          if (INHERIT(_Zo->isa,Kernel._property))
           { if ((CL_INT)CLREAD(property,_Zo,restrictions)->length > (CL_INT)0)
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[188] the property ~S is already defined")),
              _oid_(list::alloc(1,_oid_(_Zo))))));
            }
          Result = complete_object(_Zo,GC_OBJECT(list,self->args));
          }
        else { ClaireObject * ob = GC_OBJECT(ClaireObject,new_object_class(_Zc));
            if (_Zc->open != ClEnv->ephemeral)
             _Zc->instances->addFast((OID)_oid_(ob));
            Result = put_symbol(self->ident,complete_object(ob,GC_OBJECT(list,self->args)));
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> auto-reification of slot with range of a given type
// The c++ function for: reified?(self:type) [0]
CL_EXPORT ClaireBoolean * reified_ask_type1_Language(ClaireType *self) { 
    POP_SIGNAL; return (CFALSE);}
  


// creation of a new named object
// The c++ function for: self_eval(self:Defclass) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_eval_Defclass(Defclass *self) { 
    if ((INHERIT(owner_any(get_symbol(self->ident)),Kernel._class)) && 
        ((OBJECT(ClaireClass,get_symbol(self->ident))->open != ((CL_INT)-2)) || 
            (self->arg != OBJECT(ClaireClass,get_symbol(self->ident))->superclass))) 
    { { OID Result = 0;
        { OID  V_CL0560;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[107] class re-definition is not valid: ~S")),
            _oid_(list::alloc(1,_oid_(self))))));
          
          Result=_void_(V_CL0560);}
        return (Result);}
       }
    else{ if ((self->arg->open == 1) || 
          (self->arg->open == ((CL_INT)-1))) 
      { { OID Result = 0;
          { OID  V_CL0561;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[109] the parent class ~S of ~S is closed")),
              _oid_(list::alloc(2,_oid_(self->arg),_oid_(self))))));
            
            Result=_void_(V_CL0561);}
          return (Result);}
         }
      else{ 
        GC_RESERVE(2);  // v3.3.39 optim !
        { OID Result = 0;
          { ClaireClass * _Zo = class_I_symbol(self->ident,self->arg);
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(x);
              bag *x_support;
              x_support = GC_OBJECT(list,self->args);
              for (START(x_support); NEXT(x);)
              { GC_LOOP;
                { OID  v = CNULL;
                  if (INHERIT(OWNER(x),Language._Call))
                   { GC__OID(v = eval_any(GC_OID((*(OBJECT(Call,x)->args))[2])), 1);
                    GC__OID(x = (*(OBJECT(Call,x)->args))[1], 2);
                    }
                  { ClaireType * rt = GC_OBJECT(ClaireType,extract_type_any(GC_OID((*Kernel.range)(x))));
                    property * p = make_a_property_any(_oid_(OBJECT(Variable,x)->pname));
                    slot * ps = OBJECT(slot,last_list(_Zo->slots));
                    CL_INT  ix = ps->index;
                    if ((v != CNULL) && 
                        (belong_to(v,_oid_(rt)) != CTRUE))
                     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[108] default(~S) = ~S does not belong to ~S")),
                      _oid_(list::alloc(3,x,
                        v,
                        _oid_(rt))))));
                    { ClaireBoolean * g0562I;
                      { ClaireBoolean *v_and;
                        { v_and = (((CL_INT)p->open <= (CL_INT)0) ? CTRUE : CFALSE);
                          if (v_and == CFALSE) g0562I =CFALSE; 
                          else { { OID  g0563UU;
                              { CL_INT loop_handle = ClEnv->cHandle;
                                ITERATE(sx);
                                g0563UU= Kernel.cfalse;
                                for (START(self->arg->slots); NEXT(sx);)
                                if (OBJECT(restriction,sx)->selector == p)
                                 { g0563UU = Kernel.ctrue;
                                  ClEnv->cHandle = loop_handle;break;}
                                }
                              v_and = boolean_I_any(g0563UU);
                              }
                            if (v_and == CFALSE) g0562I =CFALSE; 
                            else g0562I = CTRUE;}
                          }
                        }
                      
                      if (g0562I == CTRUE) close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[181] cannot overide a slot for a closed property ~S")),
                          _oid_(list::alloc(1,_oid_(p))))));
                        }
                    if (ps->range == Kernel._float)
                     ++ix;
                    _void_(p->reified = OBJECT(ClaireObject,(*Language.reified_ask)(_oid_(rt))));
                    add_slot_class(_Zo,
                      p,
                      rt,
                      v,
                      ((CL_INT)ix+(CL_INT)1));
                    }
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            close_class(_Zo);
            if (self->forward_ask == CTRUE)
             _void_(_Zo->open = -2);
            else if (_Zo->open == ((CL_INT)-2))
             _void_(_Zo->open = 2);
            if (_inf_equal_type(_Zo,Kernel._cl_import) == CTRUE)
             _void_(_Zo->open = -1);
            _void_(_Zo->params = self->params);
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(p);
              bag *p_support;
              p_support = GC_OBJECT(list,self->params);
              for (START(p_support); NEXT(p);)
              _void_(OBJECT(property,p)->open = 0);
              }
            attach_comment_any(_oid_(_Zo));
            Result = _oid_(_Zo);
            }
          GC_UNBIND; POP_SIGNAL; return (Result);}
        }
      }
    }
  


// method definition
// v0.01
// The c++ function for: self_eval(self:Defmethod) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT]
CL_EXPORT OID  self_eval_Defmethod(Defmethod *self) { 
    
    GC_BIND;
    if (inherit_ask_class(self->arg->isa,Language._Call) != CTRUE)
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[110] wrong signature definition ~S")),
      _oid_(list::alloc(1,GC_OID(_oid_(self->arg)))))));
    { OID Result = 0;
      { property * p = make_a_property_any(_oid_(self->arg->selector));
        list * l = GC_OBJECT(list,self->arg->args);
        list * lv;
        if ((l->length == 1) && 
            ((*(l))[1] == _oid_(ClEnv)))
         { OID v_bag;
          GC_ANY(lv= list::empty(Kernel.emptySet));
          { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(_CL_obj->pname = symbol_I_string2(((char*)"XfakeParameter")));
              _void_(_CL_obj->range = Kernel._void);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              v_bag = _oid_(close_Instruction1(_CL_obj));
              }
            GC_OID(v_bag);}
          ((list *) lv)->addFast((OID)v_bag);}
        else lv = l;
          list * lp = GC_OBJECT(list,extract_signature_list(lv));
        list * lrange = GC_OBJECT(list,extract_range_any(GC_OID(self->set_arg),lv,GC_OBJECT(list,OBJECT(list,Language.LDEF->value))));
        list * lbody = GC_OBJECT(list,extract_status_any(GC_OID(self->body)));
        method * m = add_method_property(p,
          lp,
          OBJECT(ClaireType,(*(lrange))[1]),
          (*(lbody))[1],
          (*(lbody))[2]);
        if (((CL_INT)p->open > (CL_INT)0) && 
            (((CL_INT)p->open <= (CL_INT)1) && 
              (p->dispatcher == 0)))
         { OID  rtest;
          { { OID  r_some = CNULL;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(r);
                for (START(p->restrictions); NEXT(r);)
                { GC_LOOP;
                  if (r != _oid_(m))
                   { if (length_bag(_exp_list(OBJECT(restriction,r)->domain,m->domain)) != 0)
                     { r_some= (r);
                      GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                    }
                  GC_UNLOOP; POP_SIGNAL;}
                }
              rtest = r_some;
              }
            GC_OID(rtest);}
          if (rtest != CNULL)
           { restriction * r = OBJECT(restriction,rtest);
            if (should_trace_ask_module1(Language.it,1) == CTRUE)
             mtformat_module1(Language.it,((char*)"`BLUE--- WARNING ! [186] conflict between ~S and ~S is dangerous since ~S is closed\n"),1,GC_OBJECT(list,list::alloc(3,_oid_(m),
              _oid_(r),
              _oid_(p))));
            else ;}
          else ;}
        (Language.LDEF->value= _oid_(list::empty(Kernel._any)));
        if ((*(lbody))[3] != _oid_(Kernel.body))
         _void_(m->formula = lambda_I_list(lv,(*(lbody))[3]));
        if ((CL_INT)lrange->length > (CL_INT)1)
         _void_(m->typing = (*(lrange))[2]);
        update_property(Kernel.inline_ask,
          m,
          13,
          Kernel._object,
          GC_OID(self->inline_ask));
        { lambda * bd = GC_OBJECT(lambda,m->formula);
          if (bd == (NULL))
           ;else { tuple * tp = tuple::alloc(2,_oid_(m->module_I),_oid_(m->selector));
              put_table(Language.CODE_LOCS,_oid_(tp),nth_table1(Language.CODE_LOCS,_oid_(self->arg)));
              fill_debug_placeholder_any1(GC_OID(bd->body),_oid_(tp));
              }
            }
        attach_comment_any(_oid_(m));
        if ((p == Kernel.close) && 
            (_inf_equal_type(m->range,domain_I_restriction(m)) != CTRUE))
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[184] the close method ~S has a wrong range")),
          _oid_(list::alloc(1,_oid_(m))))));
        Result = _oid_(m);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: fill_debug_placeholder(x:any,m:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  fill_debug_placeholder_any1(OID x,OID m) { 
    
    GC_BIND;
    if ((OBJECT(ClaireBoolean,Language.DEBUG_ask->value)) == CTRUE)
     { if (should_trace_ask_module1(Language.it,4) == CTRUE)
       mtformat_module1(Language.it,((char*)"fill_debug_placeholder(~S, ~S) \n"),4,list::alloc(2,x,m));
      else ;if (INHERIT(OWNER(x),Language._Do))
       { if (((CL_INT)OBJECT(Do,x)->args->length > (CL_INT)0) && 
            ((INHERIT(OWNER((*(OBJECT(Do,x)->args))[1]),Language._Call)) && 
              ((*Kernel.selector)((*(OBJECT(Do,x)->args))[1]) == _oid_(Core.push_frame))))
         { OID  c = GC_OID((*(OBJECT(Do,x)->args))[1]);
          if (equal((*Core.args)(c),_oid_(list::alloc(1,_string_(((char*)"placeholder"))))) == CTRUE)
           { list * l = list::empty(Kernel._any);
            OID  loc = nth_table1(Language.CODE_LOCS,m);
            ClaireBoolean * addloc_ask = CTRUE;
            CL_INT  i = 1;
            CL_INT  len = OBJECT(Do,x)->args->length;
            put_property2(Core.args,OBJECT(ClaireObject,c),_oid_(list::alloc(1,m)));
            l->addFast((OID)c);
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while (((CL_INT)i <= (CL_INT)len))
              { GC_LOOP;
                { OID  y = GC_OID((*(OBJECT(Do,x)->args))[i]);
                  if ((INHERIT(OWNER(y),Language._Call)) && 
                      ((*Kernel.selector)(y) == _oid_(Core.push_arg)))
                   l->addFast((OID)y);
                  else if ((OBJECT(bag,loc)->length != 0) && 
                      (addloc_ask == CTRUE))
                   { { OID  g0564UU;
                      { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          _void_(_CL_obj->selector = Core.update_location);
                          _void_(_CL_obj->args = OBJECT(list,loc));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                          g0564UU = _oid_(close_Instruction1(_CL_obj));
                          }
                        GC_OID(g0564UU);}
                      l->addFast((OID)g0564UU);
                      }
                    addloc_ask= (CFALSE);
                    }
                  else l->addFast((OID)y);
                    ++i;
                  }
                GC_UNLOOP;POP_SIGNAL;}
              }
            _void_(OBJECT(Do,x)->args = l);
            }
          }
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// v3.2.24
// attach a cute comment if needed ... to a defclass or a defmethod
// The c++ function for: attach_comment(x:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  attach_comment_any(OID x) { 
    
    GC_BIND;
    if (((OBJECT(ClaireBoolean,Language.NeedComment->value)) == CTRUE) && 
        (Language.LastComment->value != CNULL))
     write_property(Kernel.comment,OBJECT(ClaireObject,x),GC_OID(Language.LastComment->value));
    GC_UNBIND; POP_SIGNAL;}
  


// returns the list of types AND modifies LDEF
// The c++ function for: iClaire/extract_signature(l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT list * extract_signature_list(list *l) { 
    
    GC_BIND;
    (Language.LDEF->value= _oid_(list::empty(Kernel._any)));
    { list *Result ;
      { CL_INT  n = 0;
        { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID v; CL_INT CLcount;
          v_list = l;
           Result = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { v = (*(v_list))[CLcount];
            if (inherit_ask_class(OBJECT(ClaireObject,v)->isa,Language._Variable) != CTRUE)
             { OID  V_CL0565;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[111] wrong typed argument ~S")),
                _oid_(list::alloc(1,v)))));
              
              v_val=_void_(V_CL0565);}
            else { OID  p = GC_OID(extract_pattern_any(GC_OID(_oid_(OBJECT(Variable,v)->range)),list::alloc(1,((OID)n))));
                ++n;
                if (p == CNULL)
                 close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[111] wrong typed argument ~S (~S)")),
                  _oid_(list::alloc(2,v,GC_OID(_oid_(OBJECT(Variable,v)->range)))))));
                _void_(OBJECT(Variable,v)->range = type_I_any(p));
                v_val = p;
                }
              
            (*((list *) Result))[CLcount] = v_val;}
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// takes an <exp> that must belong to <type> and returns the CLAIRE type
// if LDEF is non-empty, it is used as a list of type variable and patterns
// may be returned. In addition, if the path list is non empty, new type
// variables may be defined. a syntax error will produce the unknown value
//
// The c++ function for: iClaire/extract_pattern(x:any,path:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  extract_pattern_any(OID x,list *path) { 
    
    GC_BIND;
    { OID Result = 0;
      if (INHERIT(OWNER(x),Kernel._class))
       Result = x;
      else if (Kernel._set == OWNER(x))
       { OID  z;
        { if (OBJECT(bag,x)->length == 1)
           z = extract_pattern_any((*(OBJECT(bag,x)))[1],Kernel.nil);
          else z = Kernel.cfalse;
            GC_OID(z);}
        if (INHERIT(OWNER(z),Core._Reference))
         { Reference * w = GC_OBJECT(Reference,((Reference *) copy_object(OBJECT(ClaireObject,z))));
          _void_(w->arg = CTRUE);
          Result = _oid_(w);
          }
        else Result = x;
          }
      else if (INHERIT(OWNER(x),Language._Tuple))
       { list * ltp;
        { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID z; CL_INT CLcount;
            v_list = GC_OBJECT(list,OBJECT(Construct,x)->args);
             ltp = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { z = (*(v_list))[CLcount];
              v_val = extract_pattern_any(z,path);
              
              (*((list *) ltp))[CLcount] = v_val;}
            }
          GC_OBJECT(list,ltp);}
        { ClaireBoolean * g0566I;
          { OID  g0567UU;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(y);
              g0567UU= Kernel.cfalse;
              for (START(ltp); NEXT(y);)
              if (y == CNULL)
               { g0567UU = Kernel.ctrue;
                ClEnv->cHandle = loop_handle;break;}
              }
            g0566I = boolean_I_any(g0567UU);
            }
          
          if (g0566I == CTRUE) Result = CNULL;
            else Result = _oid_(tuple_I_list(ltp));
          }
        }
      else if (INHERIT(OWNER(x),Core._global_variable))
       Result = extract_pattern_any(GC_OID(OBJECT(global_variable,x)->value),path);
      else if (INHERIT(OWNER(x),Language._Call))
       { property * p = OBJECT(Call,x)->selector;
        if (p == Core.U)
         { OID  x1 = GC_OID(extract_pattern_any(GC_OID((*(OBJECT(Call,x)->args))[1]),Kernel.nil));
          OID  x2 = GC_OID(extract_pattern_any(GC_OID((*(OBJECT(Call,x)->args))[2]),Kernel.nil));
          if ((x1 == CNULL) || 
              (x2 == CNULL))
           Result = CNULL;
          else Result = _oid_(U_type(OBJECT(ClaireType,x1),OBJECT(ClaireType,x2)));
            }
        else if (p == Kernel._exp)
         Result = (*Kernel._exp)(GC_OID(extract_pattern_any(GC_OID((*(OBJECT(Call,x)->args))[1]),Kernel.nil)),
          GC_OID(extract_pattern_any(GC_OID((*(OBJECT(Call,x)->args))[2]),Kernel.nil)));
        else if (p == Kernel._dot_dot)
         { OID  v1 = GC_OID(extract_item_any(GC_OID((*(OBJECT(Call,x)->args))[1]),Core.nil->value));
          OID  v2 = GC_OID(extract_item_any(GC_OID((*(OBJECT(Call,x)->args))[2]),Core.nil->value));
          if ((INHERIT(OWNER(v1),Kernel._integer)) && 
              (INHERIT(OWNER(v2),Kernel._integer)))
           Result = _oid_(_dot_dot_integer(((CL_INT)v1),((CL_INT)v2)));
          else Result = CNULL;
            }
        else if (p == Kernel.nth)
         Result = extract_pattern_nth_list(GC_OBJECT(list,OBJECT(Call,x)->args),path);
        else if (p == Kernel._star)
         { OID  z = GC_OID(extract_pattern_any(GC_OID((*(OBJECT(Call,x)->args))[1]),path));
          if (z != CNULL)
           Result = _oid_(U_type(OBJECT(ClaireType,z),set::alloc(Kernel.emptySet,1,CNULL)));
          else Result = CNULL;
            }
        else Result = CNULL;
          }
      else if (INHERIT(OWNER(x),Kernel._type))
       Result = x;
      else if (INHERIT(OWNER(x),Kernel._unbound_symbol))
       { symbol * s = extract_symbol_any(x);
        OID  v;
        { { OID  z_some = CNULL;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(z);
              bag *z_support;
              z_support = GC_OBJECT(bag,enumerate_any(GC_OID(Language.LDEF->value)));
              for (START(z_support); NEXT(z);)
              { GC_LOOP;
                if (OBJECT(Variable,z)->pname == s)
                 { z_some= (z);
                  GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                GC_UNLOOP; POP_SIGNAL;}
              }
            v = z_some;
            }
          GC_OID(v);}
        if (v != CNULL)
         Result = (*Kernel.range)(v);
        else if ((INHERIT(path->isa,Kernel._list)) && ((CL_INT)path->length > (CL_INT)1))
         { Reference * y;
          { { Reference * _CL_obj = ((Reference *) GC_OBJECT(Reference,new_object_class(Core._Reference)));
              _void_(_CL_obj->index = ((CL_INT)(*(path))[1]));
              _void_(_CL_obj->args = cdr_list(path));
              add_I_property(Kernel.instances,Core._Reference,11,_oid_(_CL_obj));
              y = _CL_obj;
              }
            GC_OBJECT(Reference,y);}
          Variable * v;
          { { Instruction *V_CC ;
              { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                _void_(_CL_obj->pname = s);
                _void_(_CL_obj->range = y);
                add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              v= (Variable *) V_CC;}
            GC_OBJECT(Variable,v);}
          (Language.LDEF->value= (*Kernel.add)(GC_OID(Language.LDEF->value),
            _oid_(v)));
          Result = _oid_(Kernel._void);
          }
        else Result = CNULL;
          }
      else Result = CNULL;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// takes an <exp> that must belong to <type> and returns the CLAIRE type
//
// The c++ function for: iClaire/extract_type(x:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireType * extract_type_any(OID x) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { ClaireObject *V_CC ;
        { (Language.LDEF->value= _oid_(list::empty(Kernel._any)));
          { OID  r = GC_OID(extract_pattern_any(x,Kernel.nil));
            if (r == CNULL)
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[112] wrong type expression ~S")),
              _oid_(list::alloc(1,x)))));
            else V_CC = OBJECT(ClaireType,r);
              }
          }
        Result= (ClaireType *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// an item is an integer, a float, a symbol, a string or a type
//
// The c++ function for: extract_item(x:any,y:any) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  extract_item_any(OID x,OID y) { 
    if (((((INHERIT(OWNER(x),Kernel._integer)) || 
              (Kernel._float == OWNER(x))) || 
            (INHERIT(OWNER(x),Kernel._symbol))) || 
          (Kernel._string == OWNER(x))) || 
        (INHERIT(OWNER(x),Kernel._type))) 
    { { OID Result = 0;
        Result = x;
        return (Result);}
       }
    else{ 
      GC_BIND;
      { OID Result = 0;
        if (INHERIT(OWNER(x),Core._global_variable))
         Result = extract_item_any(GC_OID((*Kernel.value)(x)),y);
        else Result = CNULL;
          GC_UNBIND; POP_SIGNAL; return (Result);}
      }
    }
  


// version for X[...] which is the most complex case - note the extensibility
// patch.
// The c++ function for: extract_pattern_nth(l:list,path:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  extract_pattern_nth_list(list *l,list *path) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT  m = l->length;
        OID  x = (*(l))[1];
        if (m == 1)
         { OID  y = GC_OID(extract_pattern_any((*(l))[1],Kernel.nil));
          if (y == CNULL)
           Result = CNULL;
          else { Param * _CL_obj = ((Param *) GC_OBJECT(Param,new_object_class(Core._Param)));
              _void_(_CL_obj->arg = Kernel._array);
              _void_(_CL_obj->params = list::alloc(1,_oid_(Kernel.of)));
              _void_(_CL_obj->args = list::alloc(1,_oid_(set::alloc(1,y))));
              Result = _oid_(_CL_obj);
              }
            }
        else if (m == 2)
         { if (((x == _oid_(Core._subtype)) || 
                ((x == _oid_(Kernel._set)) || 
                  (x == _oid_(Kernel._list)))) || 
              (inherit_ask_class(OWNER(x),Kernel._class) != CTRUE))
           { OID  y = GC_OID(extract_pattern_any((*(l))[2],Kernel.nil));
            { ClaireHandler c_handle = ClaireHandler();
              if ERROR_IN 
              { if (y != CNULL)
                 Result = (*Kernel.nth)((*(l))[1],
                  y);
                else Result = CNULL;
                  ERROR_FREE;}
              else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
              { c_handle.catchIt();Result = CNULL;
                }
              else PREVIOUS_HANDLER;}
            }
          else Result = CNULL;
            }
        else { OID  l1 = (*(l))[2];
            OID  l2 = GC_OID((*Core.args)((*(l))[3]));
            list * l3 = list::empty(Kernel._any);
            { CL_INT  n = 1;
              CL_INT  g0568 = ((CL_INT)(*Kernel.length)(l1));
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                while (((CL_INT)n <= (CL_INT)g0568))
                { GC_LOOP;
                  { OID  y = (*(OBJECT(bag,l2)))[n];
                    { OID  g0569UU;
                      { if (INHERIT(OWNER(y),Language._Set))
                         { OID  v = GC_OID(extract_pattern_any(GC_OID((*(OBJECT(Construct,y)->args))[1]),((list *) copy_bag(path))->addFast((OID)GC_OID((*Kernel.nth)(l1,
                            ((OID)n))))));
                          if (v == _oid_(Kernel._void))
                           g0569UU = _oid_(Kernel._any);
                          else if (INHERIT(OWNER(v),Core._Reference))
                           { Reference * z = GC_OBJECT(Reference,((Reference *) copy_object(OBJECT(ClaireObject,v))));
                            _void_(z->arg = CTRUE);
                            g0569UU = _oid_(z);
                            }
                          else { set * V_CL0570;{ OID v_bag;
                                GC_ANY(V_CL0570= set::empty(Kernel.emptySet));
                                { if (v != CNULL)
                                   v_bag = v;
                                  else v_bag = eval_any(GC_OID((*(OBJECT(Construct,y)->args))[1]));
                                    GC_OID(v_bag);}
                                ((set *) V_CL0570)->addFast((OID)v_bag);}
                              
                              g0569UU=_oid_(V_CL0570);}
                            }
                        else { list * g0571UU;
                            { ClaireObject *V_CC ;
                              if (path->length != 0)
                               V_CC = path->addFast((OID)GC_OID((*Kernel.nth)(l1,
                                ((OID)n))));
                              else V_CC = CFALSE;
                                g0571UU= (list *) V_CC;}
                            g0569UU = extract_pattern_any(y,g0571UU);
                            }
                          GC_OID(g0569UU);}
                      l3 = l3->addFast((OID)g0569UU);
                      }
                    }
                  ++n;
                  GC_UNLOOP;POP_SIGNAL;}
                }
              }
            if (l3->memq(CNULL) == CTRUE)
             Result = CNULL;
            else { Param * _CL_obj = ((Param *) GC_OBJECT(Param,new_object_class(Core._Param)));
                update_property(Kernel.arg,
                  _CL_obj,
                  2,
                  Kernel._object,
                  x);
                update_property(Kernel.params,
                  _CL_obj,
                  3,
                  Kernel._object,
                  l1);
                _void_(_CL_obj->args = l3);
                Result = _oid_(_CL_obj);
                }
              }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// we perform some pre-processing on x[l] at reading time to make evaluation easier
// The c++ function for: iClaire/extract_class_call(self:class,l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireObject * extract_class_call_class(ClaireClass *self,list *l) { 
    
    GC_RESERVE(4);  // v3.3.39 optim !
    { ClaireObject *Result ;
      { ClaireObject *V_CC ;
        { ClaireBoolean * g0573I;
          { ClaireBoolean *v_and;
            { v_and = ((self == Core._subtype) ? CTRUE : ((self == Kernel._set) ? CTRUE : ((self == Kernel._list) ? CTRUE : CFALSE)));
              if (v_and == CFALSE) g0573I =CFALSE; 
              else { v_and = ((l->length == 1) ? CTRUE : CFALSE);
                if (v_and == CFALSE) g0573I =CFALSE; 
                else { { OID  y = (*(l))[1];
                    OID  z = GC_OID(extract_pattern_any(y,Kernel.nil));
                    if (INHERIT(OWNER(y),Core._global_variable))
                     y= (GC_OID((*Kernel.value)((*(l))[1])));
                    v_and = ((INHERIT(OWNER(z),Kernel._type)) ? CTRUE : ((self == Core._subtype) ? CTRUE : (((INHERIT(OWNER(y),Language._Call)) ? ((OBJECT(Call,y)->selector != Kernel._equal) || 
                        (OBJECT(Call,y)->args->length != 2)) : ((INHERIT(OWNER(y),Language._Tuple)) && (CTRUE == CTRUE))) ? CTRUE : CFALSE)));
                    }
                  if (v_and == CFALSE) g0573I =CFALSE; 
                  else g0573I = CTRUE;}
                }
              }
            }
          
          if (g0573I == CTRUE) { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(_CL_obj->selector = Kernel.nth);
              _void_(_CL_obj->args = cons_any(_oid_(self),l));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            else if (self == Core._lambda)
           { if ((l->length == 2) && 
                ((INHERIT(OWNER((*(l))[1]),Language._Do)) || 
                    (INHERIT(OWNER((*(l))[1]),Language._Variable))))
             { list * lv;
              { if (INHERIT(OWNER((*(l))[1]),Language._Do))
                 { list * v_out = list::empty(Kernel.emptySet);
                  { CL_INT loop_handle = ClEnv->cHandle;
                    ITERATE(v);
                    bag *v_support;
                    v_support = GC_OBJECT(list,OBJECT(bag,(*Core.args)((*(l))[1])));
                    for (START(v_support); NEXT(v);)
                    if (INHERIT(OWNER(v),Language._Variable))
                     v_out->addFast((OID)v);
                    }
                  lv = GC_OBJECT(list,v_out);
                  }
                else lv = list::alloc(1,(*(l))[1]);
                  GC_OBJECT(list,lv);}
              extract_signature_list(lv);
              V_CC = lambda_I_list(lv,(*(l))[2]);
              }
            else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[113] Wrong lambda definition lambda[~S]")),
                _oid_(list::alloc(1,_oid_(l))))));
              }
          else { list * l1 = GC_OBJECT(list,list::empty(Kernel._any));
              list * l2 = GC_OBJECT(list,list::empty(Kernel._any));
              CL_INT  m = l->length;
              { CL_INT  n = 1;
                CL_INT  g0572 = m;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  while (((CL_INT)n <= (CL_INT)g0572))
                  { GC_LOOP;
                    { OID  y = (*(l))[n];
                      OID  p = CNULL;
                      OID  v = CNULL;
                      if (INHERIT(OWNER(y),Language._Call))
                       { if (((OBJECT(Call,y)->selector == Kernel._equal) ? ((OBJECT(Call,y)->args->length == 2) ? CTRUE: CFALSE): CFALSE) != CTRUE)
                         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[114] Wrong parametrization ~S")),
                          _oid_(list::alloc(1,y)))));
                        GC__OID(p = _oid_(make_a_property_any(GC_OID((*(OBJECT(Call,y)->args))[1]))), 1);
                        { { Set * _CL_obj = ((Set *) GC_OBJECT(Set,new_object_class(Language._Set)));
                            _void_(_CL_obj->args = list::alloc(1,GC_OID((*(OBJECT(Call,y)->args))[2])));
                            add_I_property(Kernel.instances,Language._Set,11,_oid_(_CL_obj));
                            v = _oid_(close_Instruction1(_CL_obj));
                            }
                           GC__OID(v, 2);}
                        }
                      else if (INHERIT(OWNER(y),Language._Vardef))
                       { p= (_oid_(make_a_property_any(_oid_(OBJECT(Variable,y)->pname))));
                        GC__OID(v = _oid_(OBJECT(Variable,y)->range), 3);
                        }
                      else { GC__OID(p = _oid_(make_a_property_any(y)), 4);
                          v= (_oid_(Kernel.emptySet));
                          }
                        l1= (l1->addFast((OID)p));
                      l2= (l2->addFast((OID)v));
                      }
                    ++n;
                    GC_UNLOOP;POP_SIGNAL;}
                  }
                }
              { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(_CL_obj->selector = Kernel.nth);
                { Call * g0574 = _CL_obj; 
                  list * g0575;
                  { list * g0576UU;
                    { { OID v_bag;
                        GC_ANY(g0576UU= list::empty(Kernel.emptySet));
                        ((list *) g0576UU)->addFast((OID)_oid_(l1));
                        { { List * _CL_obj = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                            _void_(_CL_obj->args = l2);
                            add_I_property(Kernel.instances,Language._List,11,_oid_(_CL_obj));
                            v_bag = _oid_(close_Instruction1(_CL_obj));
                            }
                          GC_OID(v_bag);}
                        ((list *) g0576UU)->addFast((OID)v_bag);}
                      GC_OBJECT(list,g0576UU);}
                    g0575 = cons_any(_oid_(self),g0576UU);
                    }
                  _void_(g0574->args = g0575);}
                add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              }
            }
        Result= (ClaireObject *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// extract the range (type and/or second-order function)
// lvar is the list of arguments that will serve as second-o. args
// ldef is the list of extra type variables that are defined in the sig.
// The c++ function for: iClaire/extract_range(x:any,lvar:list,ldef:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT list * extract_range_any(OID x,list *lvar,list *ldef) { 
    
    GC_RESERVE(3);  // v3.3.39 optim !
    { list *Result ;
      { ClaireBoolean * g0578I;
        { OID  g0579UU;
          if (INHERIT(OWNER(x),Language._Call))
           g0579UU = _oid_(((OBJECT(Call,x)->selector == Kernel.nth) ? (((*(OBJECT(Call,x)->args))[1] == _oid_(Kernel._type)) ? CTRUE: CFALSE): CFALSE));
          else g0579UU = Kernel.cfalse;
            g0578I = not_any(g0579UU);
          }
        
        if (g0578I == CTRUE) Result = list::alloc(2,GC_OID(_oid_(extract_type_any(x))),_oid_(Kernel.emptySet));
          else { { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(v);
            for (START(ldef); NEXT(v);)
            { GC_LOOP;
              { Reference * r = GC_OBJECT(Reference,OBJECT(Reference,(*Kernel.range)(v)));
                list * path = GC_OBJECT(list,r->args);
                CL_INT  n = path->length;
                OID  y = (*(lvar))[((CL_INT)r->index+(CL_INT)1)];
                { CL_INT  i = 1;
                  CL_INT  g0577 = path->length;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    OID gc_local;
                    while (((CL_INT)i <= (CL_INT)g0577))
                    { GC_LOOP;
                      { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          _void_(_CL_obj->selector = Core._at);
                          _void_(_CL_obj->args = list::alloc(2,y,(*(path))[i]));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                          y = _oid_(close_Instruction1(_CL_obj));
                          }
                         GC__OID(y, 1);}
                      ++i;
                      GC_UNLOOP;POP_SIGNAL;}
                    }
                  }
                { { OID  g0580UU;
                    { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        _void_(_CL_obj->selector = Core.member);
                        _void_(_CL_obj->args = list::alloc(1,y));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                        g0580UU = _oid_(close_Instruction1(_CL_obj));
                        }
                      GC_OID(g0580UU);}
                    x = substitution_any(x,OBJECT(Variable,v),g0580UU);
                    }
                   GC__OID(x, 2);}
                }
              GC_UNLOOP; POP_SIGNAL;}
            }
          { list * lv2 = GC_OBJECT(list,list::empty(Kernel._any));
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(v);
              for (START(lvar); NEXT(v);)
              { GC_LOOP;
                { Variable * v2;
                  { { Instruction *V_CC ;
                      { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                        _void_(_CL_obj->pname = OBJECT(Variable,v)->pname);
                        _void_(_CL_obj->range = Kernel._type);
                        add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                        V_CC = close_Instruction1(_CL_obj);
                        }
                      v2= (Variable *) V_CC;}
                    GC_OBJECT(Variable,v2);}
                  lv2= (lv2->addFast((OID)_oid_(v2)));
                  GC__OID(x = substitution_any(x,OBJECT(Variable,v),_oid_(v2)), 3);
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            { lambda * lb = GC_OBJECT(lambda,lambda_I_list(lv2,GC_OID((*(OBJECT(bag,(*Core.args)(x))))[2])));
              OID  ur = CNULL;
              { ClaireHandler c_handle = ClaireHandler();
                if ERROR_IN 
                { { { list * g0581UU;
                      { { CL_INT loop_handle = ClEnv->cHandle;
                          bag *v_list; OID v_val;
                          OID v; CL_INT CLcount;
                          v_list = lvar;
                           g0581UU = v_list->clone();
                          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                          { v = (*(v_list))[CLcount];
                            v_val = (*Kernel.range)(v);
                            
                            (*((list *) g0581UU))[CLcount] = v_val;}
                          }
                        GC_OBJECT(list,g0581UU);}
                      ur = apply_lambda(lb,g0581UU);
                      }
                    GC_OID(ur);}
                  ERROR_FREE;}
                else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                { c_handle.catchIt();{ princ_string(((char*)"The type expression "));
                    print_any(x);
                    princ_string(((char*)" is not a valid because\n"));
                    princ_string(((char*)"lambda = "));
                    print_any(_oid_(lb));
                    princ_string(((char*)", l = "));
                    { OID  g0582UU;
                      { { list * V_CL0583;{ CL_INT loop_handle = ClEnv->cHandle;
                            bag *v_list; OID v_val;
                            OID v; CL_INT CLcount;
                            v_list = lvar;
                             V_CL0583 = v_list->clone();
                            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                            { v = (*(v_list))[CLcount];
                              v_val = (*Kernel.range)(v);
                              
                              (*((list *) V_CL0583))[CLcount] = v_val;}
                            }
                          
                          g0582UU=_oid_(V_CL0583);}
                        GC_OID(g0582UU);}
                      print_any(g0582UU);
                      }
                    princ_string(((char*)"\n"));
                    close_exception(ClEnv->exception_I);
                    }
                  }
                else PREVIOUS_HANDLER;}
              if (inherit_ask_class(OWNER(ur),Kernel._type) != CTRUE)
               close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[115] the (resulting) range ~S is not a type")),
                _oid_(list::alloc(1,ur)))));
              Result = list::alloc(2,ur,_oid_(lb));
              }
            }
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// define the different components of status(m), which is a bit vector
// a new allocation may be done by running the method
// a list is updated whose content is not gcsafe
// an slot is updated whose content is not gcsafe
// the method returns one of its args
// the result (not gcsafe) does not need protection
// the result (not gcsafe) does not need protection
// create a bitvector from a list of flags
// The c++ function for: bit_vector(l:listargs) [0]
CL_EXPORT CL_INT  bit_vector_listargs2(listargs *l) { 
    { CL_INT Result = 0;
      { CL_INT  d = 0;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(x);
          for (START(l); NEXT(x);)
          d= (CL_INT)(((CL_INT)d+(CL_INT)exp2_integer(((CL_INT)x))));
          }
        Result = d;
        }
      POP_SIGNAL; return (Result);}
    }
  


// parse the body and return (status, functional, body)
// the input is  body | (function!(f) | function!(f,s)) < | body> opt
//
// The c++ function for: iClaire/extract_status(x:any) [NEW_ALLOC]
CL_EXPORT list * extract_status_any(OID x) { 
    
    GC_BIND;
    { list *Result ;
      { OID  s = CNULL;
        OID  f;
        if ((INHERIT(OWNER(x),Language._Call)) && (OBJECT(Call,x)->selector == Language.function_I))
         f = x;
        else f = CNULL;
          if (INHERIT(OWNER(x),Language._And))
         { OID  y = (*(OBJECT(And,x)->args))[1];
          if ((INHERIT(OWNER(y),Language._Call)) && (OBJECT(Call,y)->selector == Language.function_I))
           { f= (y);
            x= ((*(OBJECT(And,x)->args))[2]);
            }
          }
        else if (INHERIT(OWNER(x),Language._Call))
         { if (OBJECT(Call,x)->selector == Language.function_I)
           x= (_oid_(Kernel.body));
          }
        else ;if (f != CNULL)
         { x= (_oid_(Kernel.body));
          if ((CL_INT)length_bag(OBJECT(bag,(*Core.args)(f))) > (CL_INT)1)
           { CL_INT  V_CL0584;{ set * g0585UU;
              { set * u_bag = set::empty(Kernel.emptySet);
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(u);
                  bag *u_support;
                  u_support = GC_OBJECT(list,cdr_list(GC_OBJECT(list,OBJECT(list,(*Core.args)(f)))));
                  for (START(u_support); NEXT(u);)
                  { GC_LOOP;
                    { OID  g0586UU;
                      { if (INHERIT(OWNER(u),Kernel._integer))
                         g0586UU = ((OID)u);
                        else if (INHERIT(OWNER(u),Core._global_variable))
                         g0586UU = OBJECT(global_variable,u)->value;
                        else { OID  V_CL0587;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[116] ~S not allowed in function!")),
                              _oid_(list::alloc(1,u)))));
                            
                            g0586UU=_void_(V_CL0587);}
                          GC_OID(g0586UU);}
                      u_bag->addFast((OID)g0586UU);
                      }
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                g0585UU = GC_OBJECT(set,u_bag);
                }
              V_CL0584 = integer_I_set(g0585UU);
              }
            
            s=((OID)V_CL0584);}
          else s= (((OID)0));
            f= (_oid_(make_function_string(string_I_symbol(extract_symbol_any((*(OBJECT(bag,(*Core.args)(f))))[1])))));
          }
        Result = list::alloc(3,s,
          f,
          x);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// cleans a pattern into a type
//
// The c++ function for: iClaire/type!(x:any) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT ClaireType * type_I_any(OID x) { 
    
    GC_BIND;
    { ClaireType *Result ;
      if (INHERIT(OWNER(x),Kernel._list))
       { CL_INT loop_handle = ClEnv->cHandle;
        bag *v_list; OID v_val;
        OID y; CL_INT CLcount;
        v_list = OBJECT(bag,x);
         Result = v_list->clone();
        for (CLcount= 1; CLcount <= v_list->length; CLcount++)
        { y = (*(v_list))[CLcount];
          v_val = _oid_(type_I_any(y));
          
          (*((list *) Result))[CLcount] = v_val;}
        }
      else if (INHERIT(OWNER(x),Core._Param))
       { Param * _CL_obj = ((Param *) GC_OBJECT(Param,new_object_class(Core._Param)));
        _void_(_CL_obj->arg = OBJECT(Param,x)->arg);
        _void_(_CL_obj->params = OBJECT(Param,x)->params);
        { Param * g0588 = _CL_obj; 
          list * g0589;
          { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID y; CL_INT CLcount;
            v_list = GC_OBJECT(list,OBJECT(Param,x)->args);
             g0589 = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { y = (*(v_list))[CLcount];
              v_val = _oid_(type_I_any(y));
              
              (*((list *) g0589))[CLcount] = v_val;}
            }
          _void_(g0588->args = g0589);}
        Result = _CL_obj;
        }
      else if (INHERIT(OWNER(x),Core._Reference))
       Result = Kernel._any;
      else Result = OBJECT(ClaireType,x);
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// creates a table
// to do in later versions: use an array if direct indexed access
// in the meanwhile, arrays of float should be used with care (indexed arrays)
//
// The c++ function for: self_eval(self:Defarray) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_eval_Defarray(Defarray *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { list * a = GC_OBJECT(list,self->arg->args);
        table * ar = ((table *) new_thing_class(Kernel._table,extract_symbol_any((*(a))[1])));
        Variable * v = OBJECT(Variable,(*(a))[2]);
        ClaireType * s = GC_OBJECT(ClaireType,extract_type_any(GC_OID(_oid_(v->range))));
        OID  e;
        { { list * l = GC_OBJECT(list,cdr_list(a));
            OID  b = GC_OID(lexical_build_any(GC_OID(self->body),l,0));
            { ClaireBoolean * g0590I;
              { OID  g0591UU;
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(va);
                  g0591UU= Kernel.cfalse;
                  for (START(l); NEXT(va);)
                  if ((CL_INT)((CL_INT)(*Kernel.occurrence)(b,
                    va)) > (CL_INT)0)
                   { g0591UU = Kernel.ctrue;
                    ClEnv->cHandle = loop_handle;break;}
                  }
                g0590I = boolean_I_any(g0591UU);
                }
              
              if (g0590I == CTRUE) e = _oid_(lambda_I_list(l,b));
                else e = self->body;
              }
            }
          GC_OID(e);}
        OID  d;
        { if (INHERIT(OWNER(e),Core._lambda))
           d = CNULL;
          else d = eval_any(GC_OID(self->body));
            GC_OID(d);}
        update_property(Kernel.range,
          ar,
          5,
          Kernel._object,
          GC_OID(extract_pattern_any(GC_OID(self->set_arg),Kernel.nil)));
        if (ar->range == (NULL))
         close_exception(((range_error *) (*Core._range_error)(_oid_(Kernel._table),
          GC_OID(self->set_arg),
          _oid_(Kernel._type))));
        if ((d != CNULL) && 
            (belong_to(d,_oid_(ar->range)) != CTRUE))
         close_exception(((range_error *) (*Core._range_error)(_oid_(ar),
          d,
          _oid_(ar->range))));
        _void_(v->range = s);
        attach_comment_any(_oid_(ar));
        if (INHERIT(class_I_type(ar->range),Kernel._set))
         _void_(ar->multivalued_ask = CTRUE);
        else if ((INHERIT(class_I_type(ar->range),Kernel._list)) && 
            (inherit_ask_class(ar->range->isa,Language._Tuple) != CTRUE))
         _void_(ar->multivalued_ask = Kernel._list);
        if (a->length == 2)
         { _void_(ar->domain = s);
          if (INHERIT(s->isa,Core._Interval))
           { _void_(ar->params = ((OID)((CL_INT)CLREAD(Interval,s,arg1)-(CL_INT)1)));
            _void_(ar->graph = make_copy_list_integer(size_Interval(((Interval *) s)),d));
            }
          else { _void_(ar->params = _oid_(Kernel._any));
              _void_(ar->graph = make_list_integer(29,CNULL));
              }
            if (INHERIT(OWNER(e),Core._lambda))
           { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(y);
            bag *y_support;
            y_support = GC_OBJECT(bag,enumerate_any(_oid_(ar->domain)));
            for (START(y_support); NEXT(y);)
            { GC_LOOP;
              nth_equal_table1(ar,y,GC_OID(funcall_lambda1(OBJECT(lambda,e),y)));
              GC_UNLOOP; POP_SIGNAL;}
            }
          else _void_(ar->DEFAULT = d);
            }
        else { ClaireType * s2 = GC_OBJECT(ClaireType,extract_type_any(GC_OID(_oid_(OBJECT(Variable,(*(a))[3])->range))));
            _void_(ar->domain = tuple_I_list(GC_OBJECT(list,list::alloc(2,_oid_(s),_oid_(s2)))));
            _void_(OBJECT(Variable,(*(a))[3])->range = s2);
            if ((INHERIT(s->isa,Core._Interval)) && 
                (INHERIT(s2->isa,Core._Interval)))
             { _void_(ar->params = _oid_(list::alloc(2,Core.size->fcall(((CL_INT) s2)),((OID)((CL_INT)((CL_INT)((CL_INT)CLREAD(Interval,s,arg1)*(CL_INT)(((CL_INT)Core.size->fcall(((CL_INT) s2)))))+(CL_INT)CLREAD(Interval,s2,arg1))-(CL_INT)1)))));
              _void_(ar->graph = make_copy_list_integer(((CL_INT)(((CL_INT)Core.size->fcall(((CL_INT) s))))*(CL_INT)(((CL_INT)Core.size->fcall(((CL_INT) s2))))),d));
              }
            else { _void_(ar->params = _oid_(Kernel._any));
                _void_(ar->graph = make_list_integer(29,CNULL));
                }
              if (INHERIT(OWNER(e),Core._lambda))
             { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(y1);
              bag *y1_support;
              y1_support = GC_OBJECT(bag,enumerate_any(_oid_(s)));
              for (START(y1_support); NEXT(y1);)
              { GC_LOOP;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(y2);
                  bag *y2_support;
                  y2_support = GC_OBJECT(bag,enumerate_any(_oid_(s2)));
                  for (START(y2_support); NEXT(y2);)
                  { GC_LOOP;
                    nth_equal_table2(ar,y1,y2,GC_OID((*Kernel.funcall)(e,
                      y1,
                      y2)));
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            else _void_(ar->DEFAULT = d);
              }
          Result = _oid_(ar);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// ------------------ NEW in v3.2 : definition of rules -----------------------
//
// a demon is a lambda with a name and a priority
// The c++ function for: self_print(self:demon) [0]
CL_EXPORT void  self_print_demon(Language_demon *self) { 
    princ_symbol(self->pname);
    POP_SIGNAL;}
  


// The c++ function for: funcall(self:demon,x:any,y:any) [NEW_ALLOC]
CL_EXPORT OID  funcall_demon1(Language_demon *self,OID x,OID y) { 
    
    GC_BIND;
    { OID Result = 0;
      Result = (*Kernel.funcall)(GC_OID(_oid_(self->formula)),
        x,
        y);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: funcall(self:demon,x:any,y:any,z:any) [NEW_ALLOC]
CL_EXPORT OID  funcall_demon2(Language_demon *self,OID x,OID y,OID z) { 
    
    GC_BIND;
    { OID Result = 0;
      Result = (*Kernel.funcall)(GC_OID(_oid_(self->formula)),
        x,
        y,
        z);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// in the interpreted mode we store the list of demons using a table
// list of relevant demons
// the last rule/axiom that was defined on each relation
// this is used to find when the relation may be compiled
// list of involved relations
// compile(ru) => may compile(r)
// evaluate a rule definition: create a new demon and, if needed, the if_write 
// function
// The c++ function for: self_eval(self:Defrule) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  self_eval_Defrule(Defrule *self) { 
    
    GC_BIND;
    { OID Result = 0;
      if ((*(self->args))[1] != _oid_(ClEnv))
       Result = (*Language.eval_rule)(_oid_(self));
      else { OID  _Zcondition = GC_OID(self->arg);
          OID  ru = get_symbol(self->ident);
          _void_(OBJECT(ClaireObject,ru)->isa = Language._rule_object);
          add_I_property(Kernel.instances,Language._rule_object,11,ru);
          { tuple * g0593 = make_filter_any(_Zcondition);
            OID  R = (*(g0593))[1];
            OID  lvar = GC_OID((*(g0593))[2]);
            Language_demon * d = make_demon_relation(OBJECT(ClaireRelation,R),
              OBJECT(symbol,(*Kernel.name)(ru)),
              OBJECT(list,lvar),
              _Zcondition,
              GC_OID(lexical_build_any(GC_OID(self->body),OBJECT(list,lvar),0)));
            if (INHERIT(OWNER(OBJECT(ClaireRelation,R)->if_write),Kernel._function))
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"cannot define a new rule on ~S which is closed")),
              _oid_(list::alloc(1,R)))));
            add_table(Language.demons,R,_oid_(d));
            nth_put_table(Language.last_rule,R,ru);
            if (length_bag(OBJECT(bag,nth_table1(Language.demons,R))) == 1)
             eval_if_write_relation(OBJECT(ClaireRelation,R));
            if ((INHERIT(OBJECT(ClaireObject,R)->isa,Kernel._property)) && (OBJECT(property,R)->restrictions->length == 0))
             eventMethod_property(OBJECT(property,R));
            Result = ru;
            }
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// an eventMethod is a property whose unique (?) restriction is a method
// The c++ function for: eventMethod?(r:relation) [0]
CL_EXPORT ClaireBoolean * eventMethod_ask_relation2(ClaireRelation *r) { 
    { ClaireBoolean *Result ;
      if (INHERIT(r->isa,Kernel._property))
       { OID  g0595UU;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(x);
          g0595UU= Kernel.cfalse;
          for (START(CLREAD(property,r,restrictions)); NEXT(x);)
          if (not_any(_oid_(equal(_oid_(Kernel._slot),_oid_(OBJECT(ClaireObject,x)->isa)))) != CTRUE)
           { g0595UU = Kernel.ctrue;
            ClEnv->cHandle = loop_handle;break;}
          }
        Result = not_any(g0595UU);
        }
      else Result = CFALSE;
        POP_SIGNAL; return (Result);}
    }
  


// check that condition is either a filter or the conjunction of a filter and a 
// condition
// a filter is R(x) := y | R(x) := (y <- z) | R(x) :add y | P(x,y)
// R(x) is x.r or A[x]
// the list of variable is of length 3 if R is mono-valued
// The c++ function for: make_filter(g0596:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT tuple * make_filter_any_(OID g0596) { 
    return make_filter_any(g0596)->copyIfNeeded();
}


// The c++ function for: make_filter(cond:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT tuple * make_filter_any(OID cond) { 
      
    GC_BIND;
    { tuple *Result ;
      { ClaireObject *V_CC ;
        { OID  c;
          { if (INHERIT(OWNER(cond),Language._And))
             c = (*(OBJECT(And,cond)->args))[1];
            else c = cond;
              GC_OID(c);}
          if (should_trace_ask_module1(Language.it,5) == CTRUE)
           mtformat_module1(Language.it,((char*)"make_filter : ~S (~S) \n"),5,list::alloc(2,c,_oid_(OBJECT(ClaireObject,c)->isa)));
          else ;if ((INHERIT(OWNER(c),Language._Call)) && (((OBJECT(Call,c)->selector == Core.write) || 
                (OBJECT(Call,c)->selector == Kernel.nth_equal)) && 
              (INHERIT(OWNER((*(OBJECT(Call,c)->args))[1]),Kernel._relation))))
           { ClaireRelation * R = OBJECT(ClaireRelation,(*(OBJECT(bag,(*Core.args)(c))))[1]);
            Variable * x;
            { { Instruction *V_CC ;
                { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                  _void_(_CL_obj->pname = extract_symbol_any((*(OBJECT(bag,(*Core.args)(c))))[2]));
                  _void_(_CL_obj->range = R->domain);
                  add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                  V_CC = close_Instruction1(_CL_obj);
                  }
                x= (Variable *) V_CC;}
              GC_OBJECT(Variable,x);}
            OID  y1 = GC_OID((*(OBJECT(bag,(*Core.args)(c))))[3]);
            if (multi_ask_any(_oid_(R)) == CTRUE)
             close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[188] wrong event filter ~S for multi-valued relation")),
              _oid_(list::alloc(2,c,_oid_(R))))));
            if ((INHERIT(OWNER(y1),Language._Call)) && (OBJECT(Call,y1)->selector == Language._inf_dash))
             { OID v_bag;
              GC_ANY(V_CC= tuple::empty());
              ((tuple *) V_CC)->addFast((OID)_oid_(R));
              { list * V_CL0597;{ OID v_bag;
                  GC_ANY(V_CL0597= list::empty(Kernel.emptySet));
                  ((list *) V_CL0597)->addFast((OID)_oid_(x));
                  { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                      _void_(_CL_obj->pname = extract_symbol_any((*(OBJECT(bag,(*Core.args)(y1))))[1]));
                      _void_(_CL_obj->range = R->range);
                      add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                      v_bag = _oid_(close_Instruction1(_CL_obj));
                      }
                    GC_OID(v_bag);}
                  ((list *) V_CL0597)->addFast((OID)v_bag);
                  { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                      _void_(_CL_obj->pname = extract_symbol_any((*(OBJECT(bag,(*Core.args)(y1))))[2]));
                      _void_(_CL_obj->range = R->range);
                      add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                      v_bag = _oid_(close_Instruction1(_CL_obj));
                      }
                    GC_OID(v_bag);}
                  ((list *) V_CL0597)->addFast((OID)v_bag);}
                
                v_bag=_oid_(V_CL0597);}
              ((tuple *) V_CC)->addFast((OID)v_bag);}
            else { OID v_bag;
                GC_ANY(V_CC= tuple::empty());
                ((tuple *) V_CC)->addFast((OID)_oid_(R));
                { list * V_CL0598;{ OID v_bag;
                    GC_ANY(V_CL0598= list::empty(Kernel.emptySet));
                    ((list *) V_CL0598)->addFast((OID)_oid_(x));
                    { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                        _void_(_CL_obj->pname = extract_symbol_any(y1));
                        _void_(_CL_obj->range = safeRange_relation(R));
                        add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                        v_bag = _oid_(close_Instruction1(_CL_obj));
                        }
                      GC_OID(v_bag);}
                    ((list *) V_CL0598)->addFast((OID)v_bag);
                    { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                        _void_(_CL_obj->pname = gensym_void());
                        _void_(_CL_obj->range = safeRange_relation(R));
                        add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                        v_bag = _oid_(close_Instruction1(_CL_obj));
                        }
                      GC_OID(v_bag);}
                    ((list *) V_CL0598)->addFast((OID)v_bag);}
                  
                  v_bag=_oid_(V_CL0598);}
                ((tuple *) V_CC)->addFast((OID)v_bag);}
              }
          else if ((INHERIT(OWNER(c),Language._Call)) && ((OBJECT(Call,c)->selector == Kernel.add) && 
              (INHERIT(OWNER((*(OBJECT(Call,c)->args))[1]),Kernel._relation))))
           { ClaireRelation * R = OBJECT(ClaireRelation,(*(OBJECT(bag,(*Core.args)(c))))[1]);
            Variable * x;
            { { Instruction *V_CC ;
                { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                  _void_(_CL_obj->pname = extract_symbol_any((*(OBJECT(bag,(*Core.args)(c))))[2]));
                  _void_(_CL_obj->range = R->domain);
                  add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                  V_CC = close_Instruction1(_CL_obj);
                  }
                x= (Variable *) V_CC;}
              GC_OBJECT(Variable,x);}
            Variable * y;
            { { Instruction *V_CC ;
                { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                  _void_(_CL_obj->pname = extract_symbol_any((*(OBJECT(bag,(*Core.args)(c))))[3]));
                  _void_(_CL_obj->range = R->range);
                  add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                  V_CC = close_Instruction1(_CL_obj);
                  }
                y= (Variable *) V_CC;}
              GC_OBJECT(Variable,y);}
            V_CC = tuple::alloc(2,_oid_(R),_oid_(list::alloc(2,_oid_(x),_oid_(y))));
            }
          else if ((INHERIT(OWNER(c),Language._Call)) && (OBJECT(Call,c)->args->length == 2))
           { property * R = OBJECT(Call,c)->selector;
            Variable * x;
            { { Instruction *V_CC ;
                { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                  _void_(_CL_obj->pname = extract_symbol_any((*(OBJECT(bag,(*Core.args)(c))))[1]));
                  _void_(_CL_obj->range = R->domain);
                  add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                  V_CC = close_Instruction1(_CL_obj);
                  }
                x= (Variable *) V_CC;}
              GC_OBJECT(Variable,x);}
            Variable * y;
            { { Instruction *V_CC ;
                { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                  _void_(_CL_obj->pname = extract_symbol_any((*(OBJECT(bag,(*Core.args)(c))))[2]));
                  _void_(_CL_obj->range = R->range);
                  add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                  V_CC = close_Instruction1(_CL_obj);
                  }
                y= (Variable *) V_CC;}
              GC_OBJECT(Variable,y);}
            V_CC = tuple::alloc(2,_oid_(R),_oid_(list::alloc(2,_oid_(x),_oid_(y))));
            }
          else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[188] wrong event filter: ~S")),
              _oid_(list::alloc(1,c)))));
            }
        Result= (tuple *) V_CC;}
      GC_UNBIND; return (Result);}
    }
  


// create a demon
// notice that a demon has 3 args if R is monovalued 
// The c++ function for: make_demon(R:relation,n:symbol,lvar:list[Variable],cond:any,conc:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT Language_demon * make_demon_relation(ClaireRelation *R,symbol *n,list *lvar,OID cond,OID conc) { 
    
    GC_BIND;
    { Language_demon *Result ;
      { OID  x = (*(lvar))[1];
        OID  y = (*(lvar))[2];
        OID  _Ztest;
        { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            _void_(_CL_obj->selector = ((multi_ask_any(_oid_(R)) == CTRUE) ?
              Kernel._Z :
              Kernel._equal ));
            _void_(_CL_obj->args = list::alloc(2,y,GC_OID(_oid_(readCall_relation(R,x)))));
            add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
            _Ztest = _oid_(close_Instruction1(_CL_obj));
            }
          GC_OID(_Ztest);}
        OID  _Zbody = conc;
        if ((CL_INT)Kernel.if_write->trace_I > (CL_INT)ClEnv->verbose)
         { { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            { Do * g0599 = _CL_obj; 
              list * g0600;
              { OID v_bag;
                GC_ANY(g0600= list::empty(Kernel.emptySet));
                { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(_CL_obj->selector = Core.format);
                    { Call * g0601 = _CL_obj; 
                      list * g0602;
                      { OID v_bag;
                        GC_ANY(g0602= list::empty(Kernel.emptySet));
                        ((list *) g0602)->addFast((OID)_string_(((char*)"--- trigger ~A(~S,~S)\n")));
                        { { List * _CL_obj = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
                            _void_(_CL_obj->args = list::alloc(3,_string_(string_I_symbol(n)),
                              x,
                              y));
                            add_I_property(Kernel.instances,Language._List,11,_oid_(_CL_obj));
                            v_bag = _oid_(close_Instruction1(_CL_obj));
                            }
                          GC_OID(v_bag);}
                        ((list *) g0602)->addFast((OID)v_bag);}
                      _void_(g0601->args = g0602);}
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                    v_bag = _oid_(close_Instruction1(_CL_obj));
                    }
                  GC_OID(v_bag);}
                ((list *) g0600)->addFast((OID)v_bag);
                ((list *) g0600)->addFast((OID)conc);}
              _void_(g0599->args = g0600);}
            add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
            conc = _oid_(close_Instruction1(_CL_obj));
            }
          GC_OID(conc);}
        { { If * _CL_obj = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
            _void_(_CL_obj->arg = conc);
            add_I_property(Kernel.instances,Language._If,11,_oid_(_CL_obj));
            _void_(_CL_obj->other = Kernel.cfalse);
            _Zbody = _oid_(close_Instruction1(_CL_obj));
            }
          GC_OID(_Zbody);}
        if (eventMethod_ask_relation2(R) == CTRUE)
         { if (INHERIT(OWNER(cond),Language._And))
           { if ((CL_INT)OBJECT(And,cond)->args->length > (CL_INT)2)
             { And * _CL_obj = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
              _void_(_CL_obj->args = cdr_list(GC_OBJECT(list,OBJECT(And,cond)->args)));
              add_I_property(Kernel.instances,Language._And,11,_oid_(_CL_obj));
              _Ztest = _oid_(close_Instruction1(_CL_obj));
              }
            else _Ztest = (*(OBJECT(And,cond)->args))[2];
              GC_OID(_Ztest);}
          else _Zbody= (conc);
            }
        else if (INHERIT(OWNER(cond),Language._And))
         { { And * _CL_obj = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
            _void_(_CL_obj->args = append_list(list::alloc(1,_Ztest),GC_OBJECT(list,cdr_list(GC_OBJECT(list,OBJECT(And,cond)->args)))));
            add_I_property(Kernel.instances,Language._And,11,_oid_(_CL_obj));
            _Ztest = _oid_(close_Instruction1(_CL_obj));
            }
          GC_OID(_Ztest);}
        if (INHERIT(OWNER(_Zbody),Language._If))
         _void_(OBJECT(If,_Zbody)->test = _Ztest);
        { Language_demon * _CL_obj = ((Language_demon *) GC_OBJECT(Language_demon,new_object_class(Language._demon)));
          _void_(_CL_obj->pname = n);
          _void_(_CL_obj->formula = lambda_I_list(lvar,_Zbody));
          add_I_property(Kernel.instances,Language._demon,11,_oid_(_CL_obj));
          Result = _CL_obj;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// cute litle guy
// The c++ function for: readCall(R:relation,x:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT Call * readCall_relation(ClaireRelation *R,OID x) { 
    
    GC_BIND;
    { Call *Result ;
      { Instruction *V_CC ;
        if (INHERIT(R->isa,Kernel._table))
         { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          _void_(_CL_obj->selector = Kernel.get);
          _void_(_CL_obj->args = list::alloc(2,_oid_(R),x));
          add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
          V_CC = close_Instruction1(_CL_obj);
          }
        else { Call_plus * _CL_obj = ((Call_plus *) GC_OBJECT(Call_plus,new_object_class(Language._Call_plus)));
            _void_(_CL_obj->selector = ((property *) R));
            _void_(_CL_obj->args = list::alloc(1,x));
            add_I_property(Kernel.instances,Language._Call_plus,11,_oid_(_CL_obj));
            V_CC = close_Instruction1(_CL_obj);
            }
          Result= (Call *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// a small brother
// The c++ function for: putCall(R:relation,x:any,y:any) [NEW_ALLOC]
CL_EXPORT Call * putCall_relation2(ClaireRelation *R,OID x,OID y) { 
    
    GC_BIND;
    { Call *Result ;
      { Instruction *V_CC ;
        if (multi_ask_any(_oid_(R)) == CTRUE)
         { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          _void_(_CL_obj->selector = Core.add_value);
          _void_(_CL_obj->args = list::alloc(3,_oid_(R),
            x,
            y));
          add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
          V_CC = close_Instruction1(_CL_obj);
          }
        else { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
            _void_(_CL_obj->selector = Kernel.put);
            _void_(_CL_obj->args = list::alloc(3,_oid_(R),
              x,
              y));
            add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
            V_CC = close_Instruction1(_CL_obj);
            }
          Result= (Call *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// v3.3 : find the range when we read the current value     
// The c++ function for: safeRange(x:relation) [RETURN_ARG]
CL_EXPORT ClaireType * safeRange_relation(ClaireRelation *x) { 
    { ClaireType *Result ;
      if (INHERIT(x->isa,Kernel._property))
       { { ClaireBoolean * g0603I;
          { OID  g0604UU;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(s);
              g0604UU= Kernel.cfalse;
              for (START(CLREAD(property,x,restrictions)); NEXT(s);)
              { ClaireBoolean * g0605I;
                { OID  g0606UU;
                  { ClaireBoolean * V_CL0607;{ OID  g0608UU;
                      if (Kernel._slot == OBJECT(ClaireObject,s)->isa)
                       g0608UU = _oid_(belong_to(OBJECT(slot,s)->DEFAULT,_oid_(OBJECT(restriction,s)->range)));
                      else g0608UU = Kernel.cfalse;
                        V_CL0607 = boolean_I_any(g0608UU);
                      }
                    
                    g0606UU=_oid_(V_CL0607);}
                  g0605I = ((g0606UU != Kernel.ctrue) ? CTRUE : CFALSE);
                  }
                
                if (g0605I == CTRUE) { g0604UU = Kernel.ctrue;
                    ClEnv->cHandle = loop_handle;break;}
                  }
              }
            g0603I = not_any(g0604UU);
            }
          
          if (g0603I == CTRUE) Result = x->range;
            else Result = Kernel._any;
          }
        }
      else if (INHERIT(x->isa,Kernel._table))
       { if (belong_to(CLREAD(table,x,DEFAULT),_oid_(x->range)) == CTRUE)
         Result = x->range;
        else Result = Kernel._any;
          }
      else Result = Kernel._any;
        POP_SIGNAL; return (Result);}
    }
  


// generate an if_write "daemon", only the first time, which uses
// the list in demons[R]
// the first step is to make the update (with inverse management)
// The c++ function for: eval_if_write(R:relation) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  eval_if_write_relation(ClaireRelation *R) { 
    
    GC_BIND;
    { OID  l = nth_table1(Language.demons,_oid_(R));
      list * lvar = GC_OBJECT(list,OBJECT(Language_demon,(*(OBJECT(bag,l)))[1])->formula->vars);
      Variable * dv;
      { { Instruction *V_CC ;
          { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
            _void_(_CL_obj->pname = gensym_void());
            _void_(_CL_obj->range = Language._demon);
            add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
            V_CC = close_Instruction1(_CL_obj);
            }
          dv= (Variable *) V_CC;}
        GC_OBJECT(Variable,dv);}
      list * l1 = list::alloc(Kernel._any,1,GC_OID(_oid_(putCall_relation2(R,(*(lvar))[1],(*(lvar))[2]))));
      list * l2;
      { OID v_bag;
        GC_ANY(l2= list::empty(Kernel._any));
        { { For * _CL_obj = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
            _void_(_CL_obj->var = dv);
            { Iteration * g0609 = _CL_obj; 
              OID  g0610;
              { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(_CL_obj->selector = Kernel.nth);
                _void_(_CL_obj->args = list::alloc(2,_oid_(Language.demons),_oid_(R)));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                g0610 = _oid_(close_Instruction1(_CL_obj));
                }
              _void_(g0609->set_arg = g0610);}
            { Iteration * g0611 = _CL_obj; 
              OID  g0612;
              { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(_CL_obj->selector = Kernel.funcall);
                _void_(_CL_obj->args = append_list(list::alloc(1,_oid_(dv)),lvar));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                g0612 = _oid_(close_Instruction1(_CL_obj));
                }
              _void_(g0611->arg = g0612);}
            add_I_property(Kernel.instances,Language._For,11,_oid_(_CL_obj));
            v_bag = _oid_(close_Instruction1(_CL_obj));
            }
          GC_OID(v_bag);}
        ((list *) l2)->addFast((OID)v_bag);}
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v);
        for (START(lvar); NEXT(v);)
        { GC_LOOP;
          put_property2(Kernel.range,OBJECT(ClaireObject,v),_oid_(class_I_type(GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Kernel.range)(v))))));
          GC_UNLOOP; POP_SIGNAL;}
        }
      if (((R->inverse == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       { if (multi_ask_any(_oid_(R)) != CTRUE)
         { OID  g0613UU;
          { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(_CL_obj->selector = Core.update_dash);
              _void_(_CL_obj->args = list::alloc(3,_oid_(R->inverse),
                (*(lvar))[3],
                (*(lvar))[1]));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
              g0613UU = _oid_(close_Instruction1(_CL_obj));
              }
            GC_OID(g0613UU);}
          l1 = l1->addFast((OID)g0613UU);
          }
        l1= (l1->addFast((OID)GC_OID(_oid_(putCall_relation2(R->inverse,(*(lvar))[2],(*(lvar))[1])))));
        }
      { ClaireRelation * g0614 = R; 
        OID  g0615;
        { lambda * V_CL0616;{ OID  g0617UU;
            { if (eventMethod_ask_relation2(R) == CTRUE)
               { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                _void_(_CL_obj->args = l2);
                add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
                g0617UU = _oid_(close_Instruction1(_CL_obj));
                }
              else if (multi_ask_any(_oid_(R)) == CTRUE)
               { If * _CL_obj = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                { If * g0618 = _CL_obj; 
                  OID  g0619;
                  { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(_CL_obj->selector = Core.NOT);
                    { Call * g0620 = _CL_obj; 
                      list * g0621;
                      { OID v_bag;
                        GC_ANY(g0621= list::empty(Kernel.emptySet));
                        { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                            _void_(_CL_obj->selector = Kernel._Z);
                            _void_(_CL_obj->args = list::alloc(2,(*(lvar))[2],GC_OID(_oid_(readCall_relation(R,(*(lvar))[1])))));
                            add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                            v_bag = _oid_(close_Instruction1(_CL_obj));
                            }
                          GC_OID(v_bag);}
                        ((list *) g0621)->addFast((OID)v_bag);}
                      _void_(g0620->args = g0621);}
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                    g0619 = _oid_(close_Instruction1(_CL_obj));
                    }
                  _void_(g0618->test = g0619);}
                { If * g0622 = _CL_obj; 
                  OID  g0623;
                  { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                    _void_(_CL_obj->args = append_list(l1,l2));
                    add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
                    g0623 = _oid_(close_Instruction1(_CL_obj));
                    }
                  _void_(g0622->arg = g0623);}
                add_I_property(Kernel.instances,Language._If,11,_oid_(_CL_obj));
                _void_(_CL_obj->other = Kernel.cfalse);
                g0617UU = _oid_(close_Instruction1(_CL_obj));
                }
              else { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                  store_object(_CL_obj,
                    2,
                    Kernel._object,
                    (*(lvar))[3],
                    CFALSE);
                  _void_(_CL_obj->value = _oid_(readCall_relation(R,(*(lvar))[1])));
                  { Let * g0624 = _CL_obj; 
                    OID  g0625;
                    { If * _CL_obj = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
                      { If * g0626 = _CL_obj; 
                        OID  g0627;
                        { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          _void_(_CL_obj->selector = Core._I_equal);
                          _void_(_CL_obj->args = list::alloc(2,(*(lvar))[2],(*(lvar))[3]));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                          g0627 = _oid_(close_Instruction1(_CL_obj));
                          }
                        _void_(g0626->test = g0627);}
                      { If * g0628 = _CL_obj; 
                        OID  g0629;
                        { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                          _void_(_CL_obj->args = append_list(l1,l2));
                          add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
                          g0629 = _oid_(close_Instruction1(_CL_obj));
                          }
                        _void_(g0628->arg = g0629);}
                      add_I_property(Kernel.instances,Language._If,11,_oid_(_CL_obj));
                      _void_(_CL_obj->other = Kernel.cfalse);
                      g0625 = _oid_(close_Instruction1(_CL_obj));
                      }
                    _void_(g0624->arg = g0625);}
                  add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
                  g0617UU = _oid_(close_Instruction1(_CL_obj));
                  }
                GC_OID(g0617UU);}
            V_CL0616 = lambda_I_list(GC_OBJECT(list,list::alloc(2,(*(lvar))[1],(*(lvar))[2])),g0617UU);
            }
          
          g0615=_oid_(V_CL0616);}
        _void_(g0614->if_write = g0615);}
      }
    GC_UNBIND; POP_SIGNAL;}
  


// create a restriction (method) that will trigger an event
// The c++ function for: eventMethod(p:property) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  eventMethod_property(property *p) { 
    { method * m = add_method_property(p,
        list::alloc(2,_oid_(p->domain),_oid_(p->range)),
        Kernel._void,
        ((OID)0),
        CNULL);
      store_object(m,
        8,
        Kernel._object,
        p->if_write,
        CFALSE);
      _void_(m->functional = make_function_string(append_string(string_I_symbol(p->name),((char*)"_write"))));
      }
    POP_SIGNAL;}
  


// new in v3.1: the inter face pragma ******************************
// this array is used to store the declarations
// define a property as an interface
// The c++ function for: interface(p:property) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  interface_property(property *p) { 
    if (boolean_I_any(_oid_(p->restrictions)) != CTRUE)
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[185] cannot define an empty property ~S as an interface")),
      _oid_(list::alloc(1,_oid_(p))))));
    if ((uniform_property(p) != CTRUE) || 
        (OBJECT(restriction,(*(p->restrictions))[1])->domain->memq(_oid_(Kernel._float)) == CTRUE))
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[185] cannot define an non-uniform property ~S as an interface")),
      _oid_(list::alloc(1,_oid_(p))))));
    { ClaireClass * d = domain_I_restriction(OBJECT(restriction,(*(p->restrictions))[1]));
      list * ls = list::empty(Kernel._any);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(g0630);
        bag *g0630_support;
        g0630_support = Kernel._property->descendents;
        for (START(g0630_support); NEXT(g0630);)
        { ClaireBoolean * g0631;
          { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(p2);
              V_C= Kernel.cfalse;
              for (START(OBJECT(ClaireClass,g0630)->instances); NEXT(p2);)
              if (((CL_INT)OBJECT(property,p2)->dispatcher > (CL_INT)0) && 
                  (boolean_I_any((*Core.glb)(_oid_(OBJECT(ClaireRelation,p2)->domain),
                    _oid_(p->domain))) == CTRUE))
               ls= (ls->addFast((OID)((OID)OBJECT(property,p2)->dispatcher)));
              }
            
            g0631=OBJECT(ClaireBoolean,V_C);}
          if (g0631 == CTRUE)
           { ;ClEnv->cHandle = loop_handle; break;}
          }
        }
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(x);
        for (START(p->restrictions); NEXT(x);)
        d= (meet_class(d,domain_I_restriction(OBJECT(restriction,x))));
        }
      _void_(p->domain = d);
      { property * g0633 = p; 
        CL_INT  g0634;
        { OID  i_some = CNULL;
          { CL_INT  i = 1;
            CL_INT  g0632 = ((CL_INT)ls->length+(CL_INT)1);
            { CL_INT loop_handle = ClEnv->cHandle;
              while (((CL_INT)i <= (CL_INT)g0632))
              { if (ls->memq(((OID)i)) != CTRUE)
                 { i_some= (((OID)i));
                  ClEnv->cHandle = loop_handle; break;}
                ++i;
                POP_SIGNAL;}
              }
            }
          g0634 = ((CL_INT)i_some);
          }
        _void_(g0633->dispatcher = g0634);}
      }
    POP_SIGNAL;}
  


// The c++ function for: interface(c:class,l:listargs) [NEW_ALLOC+BAG_UPDATE]
CL_EXPORT void  interface_class(ClaireClass *c,listargs *l) { 
    
    GC_BIND;
    { OID  g0635UU;
      { list * V_CL0636;{ list * x_out = list::empty(Kernel._property);
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(x);
            for (START(l); NEXT(x);)
            if (INHERIT(OWNER(x),Kernel._property))
             x_out->addFast((OID)x);
            }
          V_CL0636 = GC_OBJECT(list,x_out);
          }
        
        g0635UU=_oid_(V_CL0636);}
      put_table(Language.InterfaceList,_oid_(c),g0635UU);
      }
    { property * px = Language.ClaireInterface;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(p);
        bag *p_support;
        p_support = OBJECT(list,nth_table1(Language.InterfaceList,_oid_(c)));
        for (START(p_support); NEXT(p);)
        if ((*Kernel.open)(p) == ((OID)3))
         (*Core.call)(_oid_(px),
          p);
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// only implied for open properties !!!!
// ****************** Construction *********************************
// filling the evaluation form


  

extern "C" CL_EXPORT void dynLoadLanguage() 
{ Language.initModule("Language",iClaire.it,list::alloc(Kernel.emptySet,3,_oid_(Kernel.it),
      _oid_(Core.it),
      _oid_(Serialize.it)),
    "./meta",list::alloc(Kernel.emptySet,4,_string_(((char*)"pretty")),
      _string_(((char*)"call")),
      _string_(((char*)"control")),
      _string_(((char*)"define"))));
    Language.metaLoad();
    Language.it->comment = "Language";
    }
  /***** CLAIRE Compilation of file Language.cl 
         [version 3.5.0 / safety 5] *****/



CL_EXPORT LanguageClass Language;

// definition of the meta-model for Language
  void LanguageClass::metaLoad() { 
    
    ClEnv->module_I = it;
// definition of the properties 
    
    Language.type_I = property::make("type!",iClaire.it);
    Language.forward_ask = property::make("forward?",iClaire.it);
    Language.no_eval = property::make("no_eval",Language.it);
    Language.ppvariable = property::make("ppvariable",Language.it);
    Language.write_value = property::make("write_value",Language.it);
    Language.var = property::make("var",0,claire.it);
    Language.lambda_I = property::make("lambda!",iClaire.it);
    Language.lexical_build = property::make("lexical_build",iClaire.it);
    Language.lexical_change = property::make("lexical_change",iClaire.it);
    Language.extract_symbol = property::make("extract_symbol",iClaire.it);
    Language.make_a_property = property::make("make_a_property",iClaire.it);
    Language.lbreak = property::make("lbreak",Language.it);
    Language.put_buffer = property::make("put_buffer",Language.it);
    Language.checkfar = property::make("checkfar",Language.it);
    Language.indent = property::make("indent",Language.it);
    Language.make_filter = property::make("make_filter",Language.it);
    Language.set_level = property::make("set_level",Language.it);
    Language.printbox = property::make("printbox",Language.it);
    Language.printexp = property::make("printexp",Language.it);
    Language.pretty_print = property::make("pretty_print",claire.it);
    Language.assign = property::make("assign",Language.it);
    Language.printe = property::make("printe",Language.it);
    Language.sugar_ask = property::make("sugar?",Language.it);
    Language.cast_to = property::make("cast_to",iClaire.it);
    Language.set_arg = property::make("set_arg",0,iClaire.it);
    Language.substitution = property::make("substitution",claire.it);
    Language.instruction_copy = property::make("instruction_copy",Language.it);
    Language.other = property::make("other",iClaire.it);
    Language.test = property::make("test",iClaire.it);
    Language.printstat = property::make("printstat",Language.it);
    Language.pname = property::make("pname",Language.it);
    Language.priority = property::make("priority",2,Language.it);
    Language.extract_type = property::make("extract_type",iClaire.it);
    Language.extract_pattern_nth = property::make("extract_pattern_nth",Language.it);
    Language.extract_class_call = property::make("extract_class_call",iClaire.it);
    Language.extract_range = property::make("extract_range",iClaire.it);
    Language.extract_status = property::make("extract_status",iClaire.it);
    Language.make_demon = property::make("make_demon",Language.it);
    Language.eval_if_write = property::make("eval_if_write",Language.it);
    Language.readCall = property::make("readCall",Language.it);
    Language.eventMethod = property::make("eventMethod",Language.it);
    Language.eventMethod_ask = property::make("eventMethod?",Language.it);
    Language.putCall = property::make("putCall",Language.it);
    Language.safeRange = property::make("safeRange",Language.it);
    Language.forkedby = property::make("forkedby",iClaire.it);
    Language.printif = property::make("printif",Language.it);
    Language.printelse = property::make("printelse",Language.it);
    Language.printdo = property::make("printdo",Language.it);
    Language.printblock = property::make("printblock",Language.it);
    Language.printbody = property::make("printbody",Language.it);
    Language.ident = property::make("ident",iClaire.it);
    Language.attach_comment = property::make("attach_comment",Language.it);
    Language.extract_signature = property::make("extract_signature",iClaire.it);
    Language.extract_pattern = property::make("extract_pattern",iClaire.it);
    Language.dindex = property::make("dindex",2,iClaire.it);
    Language.fill_debug_placeholder = property::make("fill_debug_placeholder",Language.it);
    Language.lexical_build_imp = property::make("lexical_build_imp",Language.it);
    
    // instructions from module sources 
    
    GC_BIND;
(Language._Instruction = ClaireClass::make("Instruction",Kernel._system_object,claire.it));
    
    (Language._Basic_instruction = ClaireClass::make("Basic_instruction",Language._Instruction,claire.it));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Language.DEBUG_ask = (global_variable *) Core._global_variable->instantiate("DEBUG?",Language.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.cfalse);
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Language.CAN_INIT_LOCATION_ask = (global_variable *) Core._global_variable->instantiate("CAN_INIT_LOCATION?",Language.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.cfalse);
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
{ (Language.CODE_LOCS = (table *) Kernel._table->instantiate("CODE_LOCS",iClaire.it));
      _void_(Language.CODE_LOCS->multivalued_ask = Kernel._list);
      _void_(Language.CODE_LOCS->range = Kernel._list);
      _void_(Language.CODE_LOCS->params = _oid_(Kernel._any));
      _void_(Language.CODE_LOCS->domain = Kernel._any);
      _void_(Language.CODE_LOCS->graph = make_list_integer(29,CNULL));
      _void_(Language.CODE_LOCS->DEFAULT = Core.nil->value);
      }
    
    { (Language.equip = property::make("equip",3,iClaire.it,Kernel._any,0));
      _void_(Language.equip->open = 3);
      ;}
    
    { (Language.init_location = property::make("init_location",3,Language.it,Kernel._any,0));
      _void_(Language.init_location->open = 3);
      ;}
    
    Kernel.close->addMethod(list::domain(1,Language._Instruction),Language._Instruction,
    	NEW_ALLOC+RETURN_ARG,_function_(close_Instruction1,"close_Instruction1"));
    
    Core.option_respond->addMethod(list::domain(2,GC_OBJECT(set,set::alloc(Kernel.emptySet,1,_string_(((char*)"-debug")))),GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	0,_function_(option_respond_string50_Language,"option_respond_string50_Language"));
    
    Core.option_usage->addFloatMethod(list::domain(1,GC_OBJECT(set,set::alloc(Kernel.emptySet,1,_string_(((char*)"-debug"))))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string34_Language,"option_usage_string34_Language"),
    _function_(option_usage_string34_Language_,"option_usage_string34_Language_"));
    
    Language.no_eval->addMethod(list::domain(1,Language._Instruction),Kernel._any,
    	SAFE_RESULT,_function_(no_eval_Instruction,"no_eval_Instruction"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Language.typing = (global_variable *) Core._global_variable->instantiate("typing",iClaire.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(Kernel.typing));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Language.index = (global_variable *) Core._global_variable->instantiate("index",iClaire.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(Kernel.index));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Kernel.self_print->addMethod(list::domain(1,Kernel._unbound_symbol),Kernel._void,
    	0,_function_(self_print_unbound_symbol_Language,"self_print_unbound_symbol_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Kernel._unbound_symbol),Kernel._any,
    	NEW_ALLOC,_function_(self_eval_unbound_symbol,"self_eval_unbound_symbol"));
    
    { (Language._Variable = ClaireClass::make("Variable",Language._Basic_instruction,claire.it));
      CL_ADD_SLOT(Language._Variable,Variable,Core.pname,pname,Kernel._symbol,CNULL);
      CL_ADD_SLOT(Language._Variable,Variable,Kernel.range,range,Kernel._type,CNULL);
      CL_ADD_SLOT(Language._Variable,Variable,Kernel.index,index,Kernel._integer,CNULL);
      CL_ADD_SLOT(Language._Variable,Variable,Language.dindex,dindex,Kernel._integer,((OID)0));
      _void_(Language._Variable->params = list::alloc(Kernel._any,2,_oid_(Core.pname),_oid_(Kernel.range)));
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Variable),Kernel._void,
    	0,_function_(self_print_Variable_Language,"self_print_Variable_Language"));
    
    Language.ppvariable->addMethod(list::domain(1,Language._Variable),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(ppvariable_Variable,"ppvariable_Variable"));
    
    Language.ppvariable->addMethod(list::domain(1,Kernel._list),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(ppvariable_list,"ppvariable_list"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Variable),Kernel._any,
    	0,_function_(self_eval_Variable,"self_eval_Variable"));
    
    Language.write_value->addMethod(list::domain(2,Language._Variable,Kernel._any),Kernel._any,
    	0,_function_(write_value_Variable,"write_value_Variable"));
    
    (Language._Vardef = ClaireClass::make("Vardef",Language._Variable,claire.it));
    
    Core.self_eval->addMethod(list::domain(1,Language._Vardef),Kernel._any,
    	0,_function_(self_eval_Vardef,"self_eval_Vardef"));
    
    (Language._Complex_instruction = ClaireClass::make("Complex_instruction",Language._Instruction,claire.it));
    
    { (Language._Instruction_with_var = ClaireClass::make("Instruction_with_var",Language._Complex_instruction,claire.it));
      CL_ADD_SLOT(Language._Instruction_with_var,Instruction_with_var,Language.var,var,Language._Variable,CNULL);
      }
    
    (Language._Control_structure = ClaireClass::make("Control_structure",Language._Complex_instruction,claire.it));
    
    Core.self_eval->addMethod(list::domain(1,Core._global_variable),Kernel._any,
    	RETURN_ARG,_function_(self_eval_global_variable,"self_eval_global_variable"));
    
    Language.write_value->addMethod(list::domain(2,Core._global_variable,Kernel._any),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(write_value_global_variable,"write_value_global_variable"));
    
    { _void_(Core._global_variable->evaluate = ((ClaireFunction *) _function_(self_eval_global_variable,"self_eval_global_variable")));
      _void_(Kernel._unbound_symbol->evaluate = ((ClaireFunction *) _function_(self_eval_unbound_symbol,"self_eval_unbound_symbol")));
      }
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Language.MAX_INTEGER = (global_variable *) Core._global_variable->instantiate("MAX_INTEGER",claire.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = CL_MAX_INT); // ((OID)1073741822));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Core.apply->addMethod(list::domain(2,Core._lambda,Kernel._list),Kernel._any,
    	NEW_ALLOC,_function_(apply_lambda,"apply_lambda"));
    
    Core.call->addMethod(list::domain(2,Core._lambda,Kernel._listargs),Kernel._any,
    	NEW_ALLOC,_function_(call_lambda2,"call_lambda2"));
    
    Kernel.self_print->addMethod(list::domain(1,Core._lambda),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_lambda_Language,"self_print_lambda_Language"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Language._starvariable_index_star = (global_variable *) Core._global_variable->instantiate("*variable_index*",claire.it));
      _void_(_CL_obj->range = Kernel._integer);
      _void_(_CL_obj->value = ((OID)0));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Language.lambda_I->addMethod(list::domain(2,Kernel._list,Kernel._any),Core._lambda,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(lambda_I_list,"lambda!_list"));
    
    Language.lexical_build->addMethod(list::domain(3,Kernel._any,Kernel._list,Kernel._integer),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(lexical_build_any,"lexical_build_any"));
    
    Language.lexical_build_imp->addMethod(list::domain(3,Kernel._any,Kernel._list,Kernel._integer),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(lexical_build_imp_any1,"lexical_build_imp_any1"));
    
    Language.lexical_change->addMethod(list::domain(2,Kernel._any,Kernel._list),Kernel._any,
    	0,_function_(lexical_change_any,"lexical_change_any"));
    
    Kernel.close->addMethod(list::domain(1,Kernel._class),Kernel._class,
    	SAFE_RESULT,_function_(close_class,"close_class"));
    
    Language.extract_symbol->addMethod(list::domain(1,Kernel._any),Kernel._symbol,
    	RETURN_ARG,_function_(extract_symbol_any,"extract_symbol_any"));
    
    Language.make_a_property->addMethod(list::domain(1,Kernel._any),Kernel._property,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(make_a_property_any,"make_a_property_any"));
    
    { (Language.printl = property::make("printl",1,claire.it,Kernel._any,0));
      ;}
    
    Language.lbreak->addMethod(list::domain(1,Kernel._void),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(lbreak_void,"lbreak_void"));
    
    Language.put_buffer->addMethod(list::domain(1,Kernel._void),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(put_buffer_void,"put_buffer_void"));
    
    Language.checkfar->addMethod(list::domain(1,Kernel._void),Kernel._any,
    	NEW_ALLOC,_function_(checkfar_void,"checkfar_void"));
    
    Language.lbreak->addMethod(list::domain(1,Kernel._integer),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(lbreak_integer,"lbreak_integer"));
    
    Language.indent->addMethod(list::domain(1,Kernel._integer),Kernel._any,
    	RETURN_ARG,_function_(indent_integer,"indent_integer"));
    
    Language.set_level->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(set_level_void,"set_level_void"));
    
    Language.set_level->addMethod(list::domain(1,Kernel._integer),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(set_level_integer,"set_level_integer"));
    
    Language.printbox->addMethod(list::domain(4,Kernel._bag,
      Kernel._integer,
      Kernel._integer,
      Kernel._string),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(printbox_bag1,"printbox_bag1"));
    
    Language.printbox->addMethod(list::domain(1,Kernel._bag),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(printbox_bag2,"printbox_bag2"));
    
    Language.printbox->addMethod(list::domain(2,Kernel._bag,Kernel._string),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(printbox_bag3,"printbox_bag3"));
    
    Language.printl->addMethod(list::domain(2,Kernel._bag,Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(printl_bag,"printl_bag"));
    
    Language.printexp->addMethod(list::domain(2,Kernel._any,Kernel._boolean),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(printexp_any,"printexp_any"));
    
    Language.pretty_print->addMethod(list::domain(1,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(pretty_print_any,"pretty_print_any"));
    
    Kernel.self_print->addMethod(list::domain(1,Kernel._list),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_list_Language,"self_print_list_Language"));
    
    Kernel.self_print->addMethod(list::domain(1,Kernel._set),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_set_Language,"self_print_set_Language"));
    
    Kernel.self_print->addMethod(list::domain(1,Kernel._tuple),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_tuple_Language,"self_print_tuple_Language"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Language.LastCall = (global_variable *) Core._global_variable->instantiate("LastCall",iClaire.it));
      _void_(_CL_obj->range = Kernel._any);
      _void_(_CL_obj->value = CNULL);
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
{ (Language._Call = ClaireClass::make("Call",Language._Control_structure,claire.it));
      CL_ADD_SLOT(Language._Call,Call,Kernel.selector,selector,Kernel._property,CNULL);
      CL_ADD_SLOT(Language._Call,Call,Core.args,args,Kernel._list,CNULL);
      _void_(Language._Call->params = list::alloc(Kernel._any,2,_oid_(Kernel.selector),_oid_(Core.args)));
      }
    
    { (Language._Call_star = ClaireClass::make("Call*",Language._Call,claire.it));
      _void_(Language._Call_star->params = list::alloc(Kernel._any,2,_oid_(Kernel.selector),_oid_(Core.args)));
      }
    
    { (Language._Call_plus = ClaireClass::make("Call+",Language._Call,claire.it));
      _void_(Language._Call_plus->params = list::alloc(Kernel._any,2,_oid_(Kernel.selector),_oid_(Core.args)));
      }
    
    { (Language._Call_wcl = ClaireClass::make("Call_wcl",Language._Call,claire.it));
      _void_(Language._Call_wcl->params = list::alloc(Kernel._any,2,_oid_(Kernel.selector),_oid_(Core.args)));
      }
    
    { (Language._Princ_wcl = ClaireClass::make("Princ_wcl",Language._Call,claire.it));
      _void_(Language._Princ_wcl->params = list::alloc(Kernel._any,2,_oid_(Kernel.selector),_oid_(Core.args)));
      }
    
    { (Language.echo = property::make("echo",3,claire.it,Kernel._any,0));
      _void_(Language.echo->open = 3);
      ;}
    
    { (Language.self_html = property::make("self_html",3,claire.it,Kernel._any,0));
      _void_(Language.self_html->open = 3);
      ;}
    
    Kernel.self_print->addMethod(list::domain(1,Language._Princ_wcl),Kernel._void,
    	NEW_ALLOC,_function_(self_print_Princ_wcl1_Language,"self_print_Princ_wcl1_Language"));
    
    Kernel.self_print->addMethod(list::domain(1,Language._Call_wcl),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Call_wcl1_Language,"self_print_Call_wcl1_Language"));
    
    Kernel.self_print->addMethod(list::domain(1,Language._Call),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_print_Call_Language,"self_print_Call_Language"));
    
    Kernel.self_print->addMethod(list::domain(1,Language._Call_plus),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Call_plus_Language,"self_print_Call+_Language"));
    
    { (Language.breakpoint = property::make("breakpoint",2,claire.it,Kernel._any,0));
      ;}
    
    Core.self_eval->addMethod(list::domain(1,Language._Call),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE,_function_(self_eval_Call,"self_eval_Call"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Call_plus),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_eval_Call_plus,"self_eval_Call+"));
    
    Language.printe->addMethod(list::domain(2,Kernel._any,Kernel._property),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(printe_any,"printe_any"));
    
    Language.sugar_ask->addMethod(list::domain(4,Kernel._any,
      Kernel._any,
      Kernel._any,
      Kernel._any),Kernel._boolean,
    	0,_function_(sugar_ask_any,"sugar?_any"));
    
    { (Language._Assign = ClaireClass::make("Assign",Language._Basic_instruction,claire.it));
      CL_ADD_SLOT(Language._Assign,Assign,Language.var,var,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Assign,Assign,Kernel.arg,arg,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Assign),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_print_Assign_Language,"self_print_Assign_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Assign),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(self_eval_Assign,"self_eval_Assign"));
    
    { (Language._Gassign = ClaireClass::make("Gassign",Language._Basic_instruction,claire.it));
      CL_ADD_SLOT(Language._Gassign,Gassign,Language.var,var,Core._global_variable,CNULL);
      CL_ADD_SLOT(Language._Gassign,Gassign,Kernel.arg,arg,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Gassign),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_print_Gassign_Language,"self_print_Gassign_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Gassign),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(self_eval_Gassign,"self_eval_Gassign"));
    
    { (Language._And = ClaireClass::make("And",Language._Control_structure,claire.it));
      CL_ADD_SLOT(Language._And,And,Core.args,args,Kernel._list,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._And),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_And_Language,"self_print_And_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._And),Kernel._any,
    	NEW_ALLOC,_function_(self_eval_And,"self_eval_And"));
    
    { (Language._Or = ClaireClass::make("Or",Language._Control_structure,claire.it));
      CL_ADD_SLOT(Language._Or,Or,Core.args,args,Kernel._list,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Or),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Or_Language,"self_print_Or_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Or),Kernel._any,
    	NEW_ALLOC,_function_(self_eval_Or,"self_eval_Or"));
    
    { (Language._Quote = ClaireClass::make("Quote",Language._Basic_instruction,claire.it));
      CL_ADD_SLOT(Language._Quote,Quote,Kernel.arg,arg,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Quote),Kernel._void,
    	NEW_ALLOC,_function_(self_print_Quote_Language,"self_print_Quote_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Quote),Kernel._any,
    	RETURN_ARG,_function_(self_eval_Quote,"self_eval_Quote"));
    
    (Language._Optimized_instruction = ClaireClass::make("Optimized_instruction",Language._Complex_instruction,claire.it));
    
    { (Language._Call_method = ClaireClass::make("Call_method",Language._Optimized_instruction,claire.it));
      CL_ADD_SLOT(Language._Call_method,Call_method,Kernel.arg,arg,Kernel._method,CNULL);
      CL_ADD_SLOT(Language._Call_method,Call_method,Core.args,args,Kernel._list,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Call_method),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Call_method_Language,"self_print_Call_method_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Call_method),Kernel._any,
    	NEW_ALLOC,_function_(self_eval_Call_method,"self_eval_Call_method"));
    
    { (Language._Call_method1 = ClaireClass::make("Call_method1",Language._Call_method,claire.it));
      Core.self_eval->addMethod(list::domain(1,Language._Call_method1),Kernel._any,
      	NEW_ALLOC,_function_(self_eval_Call_method1,"self_eval_Call_method1"));
      }
    
    { (Language._Call_method2 = ClaireClass::make("Call_method2",Language._Call_method,claire.it));
      Core.self_eval->addMethod(list::domain(1,Language._Call_method2),Kernel._any,
      	NEW_ALLOC,_function_(self_eval_Call_method2,"self_eval_Call_method2"));
      }
    
    { (Language._Call_slot = ClaireClass::make("Call_slot",Language._Optimized_instruction,claire.it));
      CL_ADD_SLOT(Language._Call_slot,Call_slot,Kernel.selector,selector,Kernel._slot,CNULL);
      CL_ADD_SLOT(Language._Call_slot,Call_slot,Kernel.arg,arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Call_slot,Call_slot,Language.test,test,Kernel._boolean,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Call_slot),Kernel._void,
    	NEW_ALLOC,_function_(self_print_Call_slot_Language,"self_print_Call_slot_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Call_slot),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(self_eval_Call_slot,"self_eval_Call_slot"));
    
    { (Language._Call_array = ClaireClass::make("Call_array",Language._Optimized_instruction,claire.it));
      CL_ADD_SLOT(Language._Call_array,Call_array,Kernel.selector,selector,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Call_array,Call_array,Kernel.arg,arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Call_array,Call_array,Language.test,test,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Call_array),Kernel._void,
    	NEW_ALLOC,_function_(self_print_Call_array_Language,"self_print_Call_array_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Call_array),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(self_eval_Call_array,"self_eval_Call_array"));
    
    { (Language._Call_table = ClaireClass::make("Call_table",Language._Optimized_instruction,claire.it));
      CL_ADD_SLOT(Language._Call_table,Call_table,Kernel.selector,selector,Kernel._table,CNULL);
      CL_ADD_SLOT(Language._Call_table,Call_table,Kernel.arg,arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Call_table,Call_table,Language.test,test,Kernel._boolean,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Call_table),Kernel._void,
    	NEW_ALLOC,_function_(self_print_Call_table_Language,"self_print_Call_table_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Call_table),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(self_eval_Call_table,"self_eval_Call_table"));
    
    { (Language._Update = ClaireClass::make("Update",Language._Optimized_instruction,claire.it));
      CL_ADD_SLOT(Language._Update,Update,Kernel.selector,selector,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Update,Update,Kernel.arg,arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Update,Update,Kernel.value,value,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Update,Update,Language.var,var,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Update),Kernel._void,
    	NEW_ALLOC,_function_(self_print_Update_Language,"self_print_Update_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Update),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_eval_Update,"self_eval_Update"));
    
    { (Language._Super = ClaireClass::make("Super",Language._Control_structure,claire.it));
      CL_ADD_SLOT(Language._Super,Super,Kernel.selector,selector,Kernel._property,CNULL);
      CL_ADD_SLOT(Language._Super,Super,Language.cast_to,cast_to,Kernel._type,CNULL);
      CL_ADD_SLOT(Language._Super,Super,Core.args,args,Kernel._list,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Super),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_print_Super_Language,"self_print_Super_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Super),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_eval_Super,"self_eval_Super"));
    
    { (Language._Cast = ClaireClass::make("Cast",Language._Basic_instruction,claire.it));
      CL_ADD_SLOT(Language._Cast,Cast,Kernel.arg,arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Cast,Cast,Language.set_arg,set_arg,Kernel._type,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Cast),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Cast_Language,"self_print_Cast_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Cast),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(self_eval_Cast,"self_eval_Cast"));
    
    { (Language._Return = ClaireClass::make("Return",Language._Basic_instruction,claire.it));
      CL_ADD_SLOT(Language._Return,Return,Kernel.arg,arg,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Return),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Return_Language,"self_print_Return_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Return),Kernel._any,
    	NEW_ALLOC,_function_(self_eval_Return,"self_eval_Return"));
    
    Language.substitution->addMethod(list::domain(3,Kernel._any,Language._Variable,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(substitution_any,"substitution_any"));
    
    Kernel.occurrence->addMethod(list::domain(2,Kernel._any,Language._Variable),Kernel._integer,
    	NEW_ALLOC,_function_(occurrence_any,"occurrence_any"));
    
    Language.instruction_copy->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(instruction_copy_any,"instruction_copy_any"));
    
    { (Language._If = ClaireClass::make("If",Language._Control_structure,claire.it));
      CL_ADD_SLOT(Language._If,If,Language.test,test,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._If,If,Kernel.arg,arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._If,If,Language.other,other,Kernel._any,Kernel.cfalse);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._If),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_If_Language,"self_print_If_Language"));
    
    Language.printstat->addMethod(list::domain(1,Language._If),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(printstat_If,"printstat_If"));
    
    Language.printif->addMethod(list::domain(1,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(printif_any,"printif_any"));
    
    Language.printelse->addMethod(list::domain(1,Language._If),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(printelse_If,"printelse_If"));
    
    Core.self_eval->addMethod(list::domain(1,Language._If),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_eval_If,"self_eval_If"));
    
    { (Language._Do = ClaireClass::make("Do",Language._Control_structure,claire.it));
      CL_ADD_SLOT(Language._Do,Do,Core.args,args,Kernel._list,CNULL);
      _void_(Language._Do->params = list::alloc(Kernel._any,1,_oid_(Core.args)));
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Do),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_print_Do_Language,"self_print_Do_Language"));
    
    Language.printdo->addMethod(list::domain(2,Kernel._list,Kernel._boolean),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(printdo_list,"printdo_list"));
    
    Language.printblock->addMethod(list::domain(1,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(printblock_any,"printblock_any"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Do),Kernel._any,
    	NEW_ALLOC,_function_(self_eval_Do,"self_eval_Do"));
    
    { (Language._Let = ClaireClass::make("Let",Language._Instruction_with_var,claire.it));
      CL_ADD_SLOT(Language._Let,Let,Kernel.value,value,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Let,Let,Kernel.arg,arg,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Let),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_print_Let_Language,"self_print_Let_Language"));
    
    Language.printbody->addMethod(list::domain(1,Language._Let),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(printbody_Let,"printbody_Let"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Let),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_eval_Let,"self_eval_Let"));
    
    { (Language._When = ClaireClass::make("When",Language._Let,claire.it));
      CL_ADD_SLOT(Language._When,When,Language.other,other,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._When),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_print_When_Language,"self_print_When_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._When),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_eval_When,"self_eval_When"));
    
    (Language._Let_plus = ClaireClass::make("Let+",Language._Let,claire.it));
    
    (Language._Let_star = ClaireClass::make("Let*",Language._Let,claire.it));
    
    Kernel.self_print->addMethod(list::domain(1,Language._Let_plus),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_print_Let_plus_Language,"self_print_Let+_Language"));
    
    Kernel.self_print->addMethod(list::domain(1,Language._Let_star),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_print_Let_star_Language,"self_print_Let*_Language"));
    
    { (Language._Iteration = ClaireClass::make("Iteration",Language._Instruction_with_var,claire.it));
      CL_ADD_SLOT(Language._Iteration,Iteration,Language.set_arg,set_arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Iteration,Iteration,Kernel.arg,arg,Kernel._any,CNULL);
      }
    
    { (Language.iterate = property::make("iterate",2,claire.it,Kernel._any,0));
      ;}
    
    { (Language.Iterate = property::make("Iterate",2,claire.it,Kernel._any,0));
      ;}
    
    (Language._For = ClaireClass::make("For",Language._Iteration,claire.it));
    
    Kernel.self_print->addMethod(list::domain(1,Language._For),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_For_Language,"self_print_For_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._For),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_eval_For,"self_eval_For"));
    
    { (Language._Ffor = ClaireClass::make("Ffor",Language._Instruction_with_var,iClaire.it));
      CL_ADD_SLOT(Language._Ffor,iClaire_Ffor,Language.set_arg,set_arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Ffor,iClaire_Ffor,Kernel.arg,arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Ffor,iClaire_Ffor,Language.forkedby,forkedby,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Ffor),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Ffor1_Language,"self_print_Ffor1_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Ffor),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_eval_Ffor1,"self_eval_Ffor1"));
    
    { (Language._Collect = ClaireClass::make("Collect",Language._Iteration,claire.it));
      CL_ADD_SLOT(Language._Collect,Collect,Kernel.of,of,Kernel._type,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Collect),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Collect_Language,"self_print_Collect_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Collect),Kernel._any,
    	NEW_ALLOC,_function_(self_eval_Collect,"self_eval_Collect"));
    
    { (Language._Image = ClaireClass::make("Image",Language._Iteration,claire.it));
      CL_ADD_SLOT(Language._Image,Image,Kernel.of,of,Kernel._type,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Image),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Image_Language,"self_print_Image_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Image),Kernel._any,
    	NEW_ALLOC,_function_(self_eval_Image,"self_eval_Image"));
    
    { (Language._Select = ClaireClass::make("Select",Language._Iteration,claire.it));
      CL_ADD_SLOT(Language._Select,Select,Kernel.of,of,Kernel._type,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Select),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Select_Language,"self_print_Select_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Select),Kernel._any,
    	NEW_ALLOC,_function_(self_eval_Select,"self_eval_Select"));
    
    { (Language._Lselect = ClaireClass::make("Lselect",Language._Iteration,claire.it));
      CL_ADD_SLOT(Language._Lselect,Lselect,Kernel.of,of,Kernel._type,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Lselect),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Lselect_Language,"self_print_Lselect_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Lselect),Kernel._any,
    	NEW_ALLOC,_function_(self_eval_Lselect,"self_eval_Lselect"));
    
    { (Language._Exists = ClaireClass::make("Exists",Language._Iteration,claire.it));
      CL_ADD_SLOT(Language._Exists,Exists,Language.other,other,Kernel._any,Kernel.cfalse);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Exists),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Exists_Language,"self_print_Exists_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Exists),Kernel._any,
    	NEW_ALLOC,_function_(self_eval_Exists,"self_eval_Exists"));
    
    { (Language._Case = ClaireClass::make("Case",Language._Control_structure,claire.it));
      CL_ADD_SLOT(Language._Case,Case,Language.var,var,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Case,Case,Core.args,args,Kernel._list,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Case),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_print_Case_Language,"self_print_Case_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Case),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_eval_Case,"self_eval_Case"));
    
    { (Language._While = ClaireClass::make("While",Language._Control_structure,claire.it));
      CL_ADD_SLOT(Language._While,While,Language.test,test,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._While,While,Kernel.arg,arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._While,While,Language.other,other,Kernel._boolean,Kernel.cfalse);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._While),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_print_While_Language,"self_print_While_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._While),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_eval_While,"self_eval_While"));
    
    { (Language._Handle = ClaireClass::make("Handle",Language._Control_structure,claire.it));
      CL_ADD_SLOT(Language._Handle,ClaireHandle,Language.test,test,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Handle,ClaireHandle,Kernel.arg,arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Handle,ClaireHandle,Language.other,other,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Handle),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_print_Handle_Language,"self_print_Handle_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Handle),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(self_eval_Handle,"self_eval_Handle"));
    
    { (Language._Construct = ClaireClass::make("Construct",Language._Complex_instruction,claire.it));
      CL_ADD_SLOT(Language._Construct,Construct,Core.args,args,Kernel._list,CNULL);
      }
    
    { (Language._List = ClaireClass::make("List",Language._Construct,claire.it));
      CL_ADD_SLOT(Language._List,List,Kernel.of,of,Kernel._type,CNULL);
      }
    
    (Language._Tuple = ClaireClass::make("Tuple",Language._Construct,claire.it));
    
    { (Language._Set = ClaireClass::make("Set",Language._Construct,claire.it));
      CL_ADD_SLOT(Language._Set,Set,Kernel.of,of,Kernel._type,CNULL);
      }
    
    { (Language._Array = ClaireClass::make("Array",Language._Construct,claire.it));
      CL_ADD_SLOT(Language._Array,Array,Kernel.of,of,Kernel._type,CNULL);
      }
    
    (Language._Printf = ClaireClass::make("Printf",Language._Construct,claire.it));
    
    (Language._Error = ClaireClass::make("Error",Language._Construct,claire.it));
    
    (Language._Branch = ClaireClass::make("Branch",Language._Construct,claire.it));
    
    Kernel.self_print->addMethod(list::domain(1,Language._Construct),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_print_Construct_Language,"self_print_Construct_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._List),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(self_eval_List,"self_eval_List"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Set),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(self_eval_Set,"self_eval_Set"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Tuple),Kernel._any,
    	NEW_ALLOC,_function_(self_eval_Tuple,"self_eval_Tuple"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Array),Kernel._any,
    	NEW_ALLOC,_function_(self_eval_Array2,"self_eval_Array2"));
    
    (Language._Macro = ClaireClass::make("Macro",Language._Construct,claire.it));
    
    { (Language.macroexpand = property::make("macroexpand",3,claire.it,Kernel._any,0));
      _void_(Language.macroexpand->open = 3);
      ;}
    
    Core.self_eval->addMethod(list::domain(1,Language._Macro),Kernel._any,
    	NEW_ALLOC,_function_(self_eval_Macro2,"self_eval_Macro2"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Error),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(self_eval_Error,"self_eval_Error"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Printf),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_eval_Printf,"self_eval_Printf"));
    
    (Language._Trace = ClaireClass::make("Trace",Language._Construct,claire.it));
    
    Core.self_eval->addMethod(list::domain(1,Language._Trace),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_eval_Trace,"self_eval_Trace"));
    
    { (Language._Assert = ClaireClass::make("Assert",Language._Construct,claire.it));
      CL_ADD_SLOT(Language._Assert,Assert,Kernel.index,index,Kernel._integer,CNULL);
      CL_ADD_SLOT(Language._Assert,Assert,Kernel.external,external,Kernel._string,CNULL);
      }
    
    Core.self_eval->addMethod(list::domain(1,Language._Assert),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_eval_Assert,"self_eval_Assert"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Branch),Kernel._any,
    	NEW_ALLOC,_function_(self_eval_Branch,"self_eval_Branch"));
    
    { (Language.extract_item = property::make("extract_item",1,claire.it,Kernel._any,0));
      ;}
    
    { (Language.function_I = property::make("function!",2,claire.it,Kernel._any,0));
      ;}
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Language.LastComment = (global_variable *) Core._global_variable->instantiate("LastComment",iClaire.it));
      _void_(_CL_obj->range = Kernel._any);
      _void_(_CL_obj->value = CNULL);
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Language.NeedComment = (global_variable *) Core._global_variable->instantiate("NeedComment",claire.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.cfalse);
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
(Language._Defclaire = ClaireClass::make("Defclaire",Language._Complex_instruction,claire.it));
    
    { (Language._Definition = ClaireClass::make("Definition",Language._Defclaire,claire.it));
      CL_ADD_SLOT(Language._Definition,Definition,Kernel.arg,arg,Kernel._class,CNULL);
      CL_ADD_SLOT(Language._Definition,Definition,Core.args,args,Kernel._list,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Definition),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Definition_Language,"self_print_Definition_Language"));
    
    { (Language._Defobj = ClaireClass::make("Defobj",Language._Definition,claire.it));
      CL_ADD_SLOT(Language._Defobj,Defobj,Language.ident,ident,Kernel._symbol,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Defobj),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Defobj_Language,"self_print_Defobj_Language"));
    
    { (Language._Defclass = ClaireClass::make("Defclass",Language._Defobj,claire.it));
      CL_ADD_SLOT(Language._Defclass,Defclass,Kernel.params,params,Kernel._list,CNULL);
      CL_ADD_SLOT(Language._Defclass,Defclass,Language.forward_ask,forward_ask,Kernel._boolean,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Defclass),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Defclass_Language,"self_print_Defclass_Language"));
    
    { (Language._Defmethod = ClaireClass::make("Defmethod",Language._Defclaire,claire.it));
      CL_ADD_SLOT(Language._Defmethod,Defmethod,Kernel.arg,arg,Language._Call,CNULL);
      CL_ADD_SLOT(Language._Defmethod,Defmethod,Language.set_arg,set_arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Defmethod,Defmethod,Kernel.body,body,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Defmethod,Defmethod,Kernel.inline_ask,inline_ask,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Defmethod),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_print_Defmethod_Language,"self_print_Defmethod_Language"));
    
    (Language._Defarray = ClaireClass::make("Defarray",Language._Defmethod,claire.it));
    
    Kernel.self_print->addMethod(list::domain(1,Language._Defarray),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_print_Defarray_Language,"self_print_Defarray_Language"));
    
    { (Language._Defrule = ClaireClass::make("Defrule",Language._Defclaire,claire.it));
      CL_ADD_SLOT(Language._Defrule,Defrule,Language.ident,ident,Kernel._symbol,CNULL);
      CL_ADD_SLOT(Language._Defrule,Defrule,Core.args,args,Kernel._list,CNULL);
      CL_ADD_SLOT(Language._Defrule,Defrule,Kernel.arg,arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Language._Defrule,Defrule,Kernel.body,body,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Defrule),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_print_Defrule_Language,"self_print_Defrule_Language"));
    
    { (Language._Defvar = ClaireClass::make("Defvar",Language._Defclaire,claire.it));
      CL_ADD_SLOT(Language._Defvar,Defvar,Language.ident,ident,Language._Variable,CNULL);
      CL_ADD_SLOT(Language._Defvar,Defvar,Kernel.arg,arg,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._Defvar),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_Defvar_Language,"self_print_Defvar_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Definition),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_eval_Definition,"self_eval_Definition"));
    
    { (Language.complete = property::make("complete",1,claire.it,Kernel._any,0));
      ;}
    
    Language.complete->addMethod(list::domain(2,Kernel._object,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(complete_object,"complete_object"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Defobj),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(self_eval_Defobj,"self_eval_Defobj"));
    
    { (Language.reified_ask = property::make("reified?",3,claire.it,Kernel._any,0));
      _void_(Language.reified_ask->open = 3);
      ;}
    
    Language.reified_ask->addMethod(list::domain(1,Kernel._type),Kernel._boolean,
    	0,_function_(reified_ask_type1_Language,"reified?_type1_Language"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Defclass),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_eval_Defclass,"self_eval_Defclass"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Language.LDEF = (global_variable *) Core._global_variable->instantiate("LDEF",claire.it));
      _void_(_CL_obj->range = Kernel._any);
      _void_(_CL_obj->value = _oid_(list::empty()));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Core.self_eval->addMethod(list::domain(1,Language._Defmethod),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT,_function_(self_eval_Defmethod,"self_eval_Defmethod"));
    
    Language.fill_debug_placeholder->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(fill_debug_placeholder_any1,"fill_debug_placeholder_any1"));
    
    { _void_(Kernel._Z->open = -1);
      _void_(Kernel._sup_equal->open = -1);
      _void_(Kernel._equal->open = -1);
      }
    
    Language.attach_comment->addMethod(list::domain(1,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(attach_comment_any,"attach_comment_any"));
    
    Language.extract_signature->addMethod(list::domain(1,Kernel._list),Kernel._list,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(extract_signature_list,"extract_signature_list"));
    
    Language.extract_pattern->addMethod(list::domain(2,Kernel._any,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(extract_pattern_any,"extract_pattern_any"));
    
    Language.extract_type->addMethod(list::domain(1,Kernel._any),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(extract_type_any,"extract_type_any"));
    
    Language.extract_item->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(extract_item_any,"extract_item_any"));
    
    Language.extract_pattern_nth->addMethod(list::domain(2,Kernel._list,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(extract_pattern_nth_list,"extract_pattern_nth_list"));
    
    Language.extract_class_call->addMethod(list::domain(2,Kernel._class,Kernel._list),Kernel._object,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(extract_class_call_class,"extract_class_call_class"));
    
    Language.extract_range->addMethod(list::domain(3,Kernel._any,Kernel._list,Kernel._list),Kernel._list,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(extract_range_any,"extract_range_any"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Language._NEW_ALLOC = (global_variable *) Core._global_variable->instantiate("NEW_ALLOC",claire.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = ((OID)1));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Language._BAG_UPDATE = (global_variable *) Core._global_variable->instantiate("BAG_UPDATE",claire.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = ((OID)2));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Language._SLOT_UPDATE = (global_variable *) Core._global_variable->instantiate("SLOT_UPDATE",claire.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = ((OID)3));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Language._RETURN_ARG = (global_variable *) Core._global_variable->instantiate("RETURN_ARG",claire.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = ((OID)4));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Language._SAFE_RESULT = (global_variable *) Core._global_variable->instantiate("SAFE_RESULT",claire.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = ((OID)5));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Language._SAFE_GC = (global_variable *) Core._global_variable->instantiate("SAFE_GC",claire.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = ((OID)6));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
{ (Language.bit_vector = property::make("bit_vector",2,claire.it,Kernel._any,0));
      ;}
    
    Language.bit_vector->addMethod(list::domain(1,Kernel._listargs),Kernel._integer,
    	0,_function_(bit_vector_listargs2,"bit_vector_listargs2"));
    
    Language.extract_status->addMethod(list::domain(1,Kernel._any),Kernel._list,
    	NEW_ALLOC,_function_(extract_status_any,"extract_status_any"));
    
    Language.type_I->addMethod(list::domain(1,Kernel._any),Kernel._type,
    	NEW_ALLOC+RETURN_ARG,_function_(type_I_any,"type!_any"));
    
    Core.self_eval->addMethod(list::domain(1,Language._Defarray),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_eval_Defarray,"self_eval_Defarray"));
    
    { (Language._demon = ClaireClass::make("demon",Core._lambda,Language.it));
      CL_ADD_SLOT(Language._demon,Language_demon,Language.pname,pname,Kernel._symbol,_oid_(symbol_I_string2(((char*)"unamed"))));
      CL_ADD_SLOT(Language._demon,Language_demon,Language.priority,priority,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Language._demon,Language_demon,Kernel.formula,formula,Core._lambda,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Language._demon),Kernel._void,
    	0,_function_(self_print_demon,"self_print_demon"));
    
    Kernel.funcall->addMethod(list::domain(3,Language._demon,Kernel._any,Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(funcall_demon1,"funcall_demon1"));
    
    Kernel.funcall->addMethod(list::domain(4,Language._demon,
      Kernel._any,
      Kernel._any,
      Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(funcall_demon2,"funcall_demon2"));
    
    { (Language.demons = (table *) Kernel._table->instantiate("demons",claire.it));
      _void_(Language.demons->multivalued_ask = Kernel._list);
      _void_(Language.demons->range = param_I_class(Kernel._list,Language._demon));
      _void_(Language.demons->params = _oid_(Kernel._any));
      _void_(Language.demons->domain = Kernel._relation);
      _void_(Language.demons->graph = make_list_integer(29,CNULL));
      _void_(Language.demons->DEFAULT = _oid_(list::empty(Language._demon)));
      }
    
    { (Language._inf_dash = (operation *) Kernel._operation->instantiate("<-",claire.it));
      ;}
    
    (Language._rule_object = ClaireClass::make("rule_object",Kernel._property,Language.it));
    
    { (Language.relations = (table *) Kernel._table->instantiate("relations",Language.it));
      _void_(Language.relations->multivalued_ask = CTRUE);
      _void_(Language.relations->range = Kernel._set);
      _void_(Language.relations->params = _oid_(Kernel._any));
      _void_(Language.relations->domain = Language._rule_object);
      _void_(Language.relations->graph = make_list_integer(29,CNULL));
      _void_(Language.relations->DEFAULT = _oid_(Kernel.emptySet));
      }
    
    { (Language.last_rule = (table *) Kernel._table->instantiate("last_rule",Language.it));
      _void_(Language.last_rule->range = Language._rule_object);
      _void_(Language.last_rule->params = _oid_(Kernel._any));
      _void_(Language.last_rule->domain = Kernel._relation);
      _void_(Language.last_rule->graph = make_list_integer(29,CNULL));
      _void_(Language.last_rule->DEFAULT = CNULL);
      }
    
    update_property(Kernel.inverse,
      Language.relations,
      8,
      Kernel._object,
      _oid_(Language.last_rule));
    
    { (Language.eval_rule = property::make("eval_rule",3,claire.it,Kernel._any,0));
      _void_(Language.eval_rule->open = 3);
      ;}
    
    Core.self_eval->addMethod(list::domain(1,Language._Defrule),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_eval_Defrule,"self_eval_Defrule"));
    
    Language.eventMethod_ask->addMethod(list::domain(1,Kernel._relation),Kernel._boolean,
    	0,_function_(eventMethod_ask_relation2,"eventMethod?_relation2"));
    
    Language.make_filter->addFloatMethod(list::domain(1,Kernel._any),tuple::alloc(2,_oid_(Kernel._relation),GC_OID(_oid_(nth_class1(Kernel._list,Language._Variable)))),
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(make_filter_any,"make_filter_any"),
    _function_(make_filter_any_,"make_filter_any_"));
    
    Language.make_demon->addMethod(list::domain(5,Kernel._relation,
      Kernel._symbol,
      GC_OBJECT(ClaireType,nth_class1(Kernel._list,Language._Variable)),
      Kernel._any,
      Kernel._any),Language._demon,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(make_demon_relation,"make_demon_relation"));
    
    Language.readCall->addMethod(list::domain(2,Kernel._relation,Kernel._any),Language._Call,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(readCall_relation,"readCall_relation"));
    
    Language.putCall->addMethod(list::domain(3,Kernel._relation,Kernel._any,Kernel._any),Language._Call,
    	NEW_ALLOC,_function_(putCall_relation2,"putCall_relation2"));
    
    Language.safeRange->addMethod(list::domain(1,Kernel._relation),Kernel._type,
    	RETURN_ARG,_function_(safeRange_relation,"safeRange_relation"));
    
    Language.eval_if_write->addMethod(list::domain(1,Kernel._relation),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(eval_if_write_relation,"eval_if_write_relation"));
    
    Language.eventMethod->addMethod(list::domain(1,Kernel._property),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(eventMethod_property,"eventMethod_property"));
    
    { (Language.InterfaceList = (table *) Kernel._table->instantiate("InterfaceList",Language.it));
      _void_(Language.InterfaceList->multivalued_ask = Kernel._list);
      _void_(Language.InterfaceList->range = Kernel._list);
      _void_(Language.InterfaceList->params = _oid_(Kernel._any));
      _void_(Language.InterfaceList->domain = Kernel._class);
      _void_(Language.InterfaceList->graph = make_list_integer(29,CNULL));
      _void_(Language.InterfaceList->DEFAULT = Core.nil->value);
      }
    
    { (Language.ClaireInterface = property::make("interface",1,claire.it,Kernel._any,0));
      ;}
    
    Language.ClaireInterface->addMethod(list::domain(1,Kernel._property),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(interface_property,"interface_property"));
    
    Language.ClaireInterface->addMethod(list::domain(2,Kernel._class,Kernel._listargs),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE,_function_(interface_class,"interface_class"));
    
    { _void_(Kernel._class->open = 0);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(x);
        bag *x_support;
        x_support = Language._Instruction->descendents;
        for (START(x_support); NEXT(x);)
        { GC_LOOP;
          { OID  m = GC_OID(_oid_(_at_property1(Core.self_eval,OBJECT(ClaireClass,x))));
            _void_(OBJECT(ClaireClass,x)->open = 3);
            if (Kernel._method == OWNER(m))
             _void_(OBJECT(ClaireClass,x)->evaluate = OBJECT(method,m)->functional);
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      }
    
    { restriction * e1 = OBJECT(restriction,(*(Kernel.entries->restrictions))[1]);
      restriction * e2 = OBJECT(restriction,(*(Kernel.entries->restrictions))[2]);
      _void_(e1->range = nth_class1(Kernel._list,Kernel._string));
      _void_(e2->range = nth_class1(Kernel._list,Kernel._string));
      }
    
    { restriction * e1 = OBJECT(restriction,(*(Kernel.explode->restrictions))[1]);
      restriction * e2 = OBJECT(restriction,(*(Kernel.explode->restrictions))[2]);
      _void_(e1->range = nth_class1(Kernel._list,Kernel._string));
      _void_(e2->range = tuple::alloc(9,_oid_(Kernel._integer),
        GC_OID(_oid_(_dot_dot_integer(1,12))),
        GC_OID(_oid_(_dot_dot_integer(1,365))),
        GC_OID(_oid_(_dot_dot_integer(1,31))),
        GC_OID(_oid_(_dot_dot_integer(1,7))),
        GC_OID(_oid_(_dot_dot_integer(0,23))),
        GC_OID(_oid_(_dot_dot_integer(0,59))),
        GC_OID(_oid_(_dot_dot_integer(0,59))),
        _oid_(Kernel._boolean)));
      }
    
    _void_(OBJECT(restriction,(*(Kernel.explode_wildcard->restrictions))[1])->range = nth_class1(Kernel._list,Kernel._string));
    GC_UNBIND;

    }
  
  