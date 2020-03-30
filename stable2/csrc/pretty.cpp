/***** CLAIRE Compilation of file ./meta/pretty.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:38 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>

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
// The c++ function for: no_eval(self:Instruction) [SAFE_RESULT]
OID  no_eval_Instruction(Instruction *self)
{ { OID Result = 0;
    { OID  V_CL0309;close_exception(((general_error *) (*Core._general_error)(_string_("[144] evaluate(~S) is not defined"),
        _oid_(list::alloc(1,_oid_(OWNER(_oid_(self))))))));
      
      Result=_void_(V_CL0309);}
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
void  self_print_unbound_symbol_Language(unbound_symbol *self)
{ princ_symbol(self->name);
  POP_SIGNAL;}


// The c++ function for: self_eval(self:unbound_symbol) [NEW_ALLOC]
OID  self_eval_unbound_symbol(unbound_symbol *self)
{ { OID Result = 0;
    if (INHERIT(owner_any(get_symbol(self->name)),Kernel._thing))
     Result = eval_any(get_symbol(self->name));
    else { OID  V_CL0310;close_exception(((general_error *) (*Core._general_error)(_string_("[145] the symbol ~A is unbound"),
          _oid_(list::alloc(1,_oid_(self->name))))));
        
        Result=_void_(V_CL0310);}
      POP_SIGNAL; return (Result);}
  }


//       else Serror(145, "The symbol ~A is unbound", list(self.name))) //<sb> made this error a syntax error
// A lexical variable is defined by a "Let" or inside a method's definition
//
// Lexical variables --------------------------------------------------
//
//<sb> position in the stack (compiled debug)
// The c++ function for: self_print(self:Variable) [0]
void  self_print_Variable_Language(Variable *self)
{ { symbol * s = self->pname;
    if (s == (NULL))
     princ_string("<unamed variable?>");
    else princ_symbol(s);
      }
  POP_SIGNAL;}


// The c++ function for: ppvariable(self:Variable) [NEW_ALLOC+SLOT_UPDATE]
void  ppvariable_Variable(Variable *self)
{ GC_BIND;
  if (((self->range == (NULL)) ? CTRUE : CFALSE) != CTRUE)
   { princ_symbol(self->pname);
    princ_string(":");
    printexp_any(GC_OID(_oid_(self->range)),CFALSE);
    }
  else princ_symbol(self->pname);
    GC_UNBIND; POP_SIGNAL;}


// The c++ function for: ppvariable(self:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  ppvariable_list(list *self)
{ { ClaireBoolean * f = CTRUE;
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(v);
      for (START(self); NEXT(v);)
      { if (f == CTRUE)
         f= CFALSE;
        else princ_string(",");
          if (INHERIT(OWNER(v),Language._Variable))
         ppvariable_Variable(OBJECT(Variable,v));
        else print_any(v);
          }
      }
    }
  POP_SIGNAL;}


// The c++ function for: self_eval(self:Variable) [0]
OID  self_eval_Variable(Variable *self)
{ POP_SIGNAL; return (ClEnv->stack[((OID)((CL_INT)ClEnv->base+(CL_INT)self->index))]);}


// The c++ function for: write_value(self:Variable,val:any) [0]
OID  write_value_Variable(Variable *self,OID val)
{ { OID Result = 0;
    if ((self->range == (NULL)) || 
        (belong_to(val,_oid_(self->range)) == CTRUE))
     Result = (ClEnv->stack[((OID)((CL_INT)ClEnv->base+(CL_INT)self->index))]=val);
    else { OID  V_CL0311;close_exception(((range_error *) (*Core._range_error)(_oid_(self),
          val,
          _oid_(self->range))));
        
        Result=_void_(V_CL0311);}
      POP_SIGNAL; return (Result);}
  }


// this is the definition of a typed variable
//
// The c++ function for: self_eval(self:Vardef) [0]
OID  self_eval_Vardef(Vardef *self)
{ { OID Result = 0;
    { OID  i = ((OID)self->index);
      if (i != CNULL)
       Result = ClEnv->stack[((OID)((CL_INT)ClEnv->base+(CL_INT)(i)))];
      else { OID  V_CL0312;close_exception(((general_error *) (*Core._general_error)(_string_("[146] The variable ~S is not defined"),
            _oid_(list::alloc(1,_oid_(self))))));
          
          Result=_void_(V_CL0312);}
        }
    POP_SIGNAL; return (Result);}
  }


//   [self_print(self:Vardef) : any -> ppvariable(self) ]
// global_variables are defined in exception ? ---------------------------
// a global variable is a named object with a special evaluation
//
// The c++ function for: self_eval(self:global_variable) [RETURN_ARG]
OID  self_eval_global_variable(global_variable *self)
{ POP_SIGNAL; return (self->value);}


// The c++ function for: write_value(self:global_variable,val:any) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
OID  write_value_global_variable(global_variable *self,OID val)
{ { OID Result = 0;
    if (belong_to(val,_oid_(self->range)) == CTRUE)
     { put_store_property2(Kernel.value,self,val,self->store_ask);
      Result = val;
      }
    else { OID  V_CL0313;close_exception(((range_error *) (*Core._range_error)(_oid_(self),
          val,
          _oid_(self->range))));
        
        Result=_void_(V_CL0313);}
      POP_SIGNAL; return (Result);}
  }


// v0.01
// same as C //<sb> moved in Core
//EOF :: global_variable(range = char, value = char!(externC("((CL_INT) EOF)",integer))) // v3.2.52
//EOS :: global_variable(range = char, value = char!(0))
// v3.4
// *********************************************************************
// *   Part 2: CLAIRE Lambdas                                           *
// *********************************************************************
// CLAIRE lambdas are the basic functional objects, defined by a filter
// and a piece of code. Lambda is defined in the "method" file.
// applying a lambda to a list of arguments
//
// The c++ function for: apply(self:lambda,%l:list) [NEW_ALLOC]
OID  apply_lambda(lambda *self,list *_Zl)
{ GC_BIND;
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
OID  call_lambda2(lambda *self,listargs *l)
{ POP_SIGNAL; return (apply_lambda(self,l));}


// printing a lambda
//
// The c++ function for: self_print(self:lambda) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_print_lambda_Language(lambda *self)
{ GC_BIND;
  princ_string("lambda[(");
  ppvariable_list(GC_OBJECT(list,self->vars));
  princ_string("),");
  lbreak_integer(1);
  print_any(GC_OID(self->body));
  (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)1));
  { OID Result = 0;
    princ_string("]");
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// lambda! and flexical_build communicate via a global_variable, which
// however is only used in this file (and also by cfile :-) ):
//
// creating a lambda from an instruction and a list of variables
// The c++ function for: iClaire/lambda!(lvar:list,self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
lambda * lambda_I_list(list *lvar,OID self)
{ GC_BIND;
  (Language._starvariable_index_star->value= ((OID)0));
  { CL_INT loop_handle = ClEnv->cHandle;
    ITERATE(v);
    for (START(lvar); NEXT(v);)
    { (OBJECT(Variable,v)->index = Language._starvariable_index_star->value);
      (OBJECT(ClaireObject,v)->isa = Language._Variable);
      (Language._starvariable_index_star->value= ((OID)((CL_INT)(Language._starvariable_index_star->value)+(CL_INT)1)));
      }
    }
  { lambda *Result ;
    { OID  corps = GC_OID(lexical_build_any(self,lvar,Language._starvariable_index_star->value));
      lambda * resultat = GC_OBJECT(lambda,((lambda *) new_object_class(Core._lambda)));
      (resultat->vars = lvar);
      (resultat->body = corps);
      (resultat->dimension = Language._starvariable_index_star->value);
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
// The c++ function for: iClaire/lexical_build(self:any,lvar:list,n:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  lexical_build_any(OID self,list *lvar,int n)
{ GC_BIND;
  { OID Result = 0;
    if ((INHERIT(OWNER(self),Kernel._thing)) || 
        (INHERIT(OWNER(self),Kernel._unbound_symbol)))
     Result = lexical_change_any(self,lvar);
    else { if (INHERIT(OWNER(self),Language._Variable))
         { if (OBJECT(Variable,self)->index == (CNULL))
           close_exception(((general_error *) (*Core._general_error)(_string_("[145] the symbol ~A is unbound"),
            _oid_(list::alloc(1,_oid_(OBJECT(Variable,self)->pname))))));
          ;}
        else if (INHERIT(OWNER(self),Language._Call))
         { OID  s = lexical_change_any(_oid_(OBJECT(Call,self)->selector),lvar);
          lexical_build_any(GC_OID(_oid_(OBJECT(Call,self)->args)),lvar,n);
          if (_oid_(OBJECT(Call,self)->selector) != s)
           { (OBJECT(Call,self)->selector = Core.call);
            (OBJECT(Call,self)->args = cons_any(s,GC_OBJECT(list,OBJECT(Call,self)->args)));
            }
          }
        else if (INHERIT(OWNER(self),Language._Instruction))
         { ClaireClass * _Ztype = OBJECT(ClaireObject,self)->isa;
          if (contain_ask_set(Language._Instruction_with_var->descendents,_oid_(_Ztype)) == CTRUE)
           { put_property2(Kernel.index,GC_OBJECT(ClaireObject,OBJECT(ClaireObject,(*Language.var)(self))),((OID)n));
            ++n;
            if ((CL_INT)n > (CL_INT)Language._starvariable_index_star->value)
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
              else lexical_build_any(x,lvar,n);
                }
            }
          }
        else if (INHERIT(OWNER(self),Kernel._bag))
         { CL_INT  _Zn = OBJECT(bag,self)->length;
          { CL_INT loop_handle = ClEnv->cHandle;
            while (((CL_INT)_Zn > 0))
            { { OID  x = (*(OBJECT(bag,self)))[_Zn];
                if ((INHERIT(OWNER(x),Kernel._thing)) || 
                    (INHERIT(OWNER(x),Kernel._unbound_symbol)))
                 ((*(OBJECT(list,self)))[_Zn]=lexical_change_any(x,lvar));
                else lexical_build_any(x,lvar,n);
                  }
              _Zn= ((CL_INT)_Zn-(CL_INT)1);
              POP_SIGNAL;}
            }
          }
        else ;Result = self;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: iClaire/lexical_change(self:any,lvar:list) [0]
OID  lexical_change_any(OID self,list *lvar)
{ { OID Result = 0;
    { OID  rep = self;
      symbol * _Zname = ((INHERIT(OWNER(self),Language._Variable)) ?
        OBJECT(Variable,self)->pname :
        extract_symbol_any(self) );
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(x);
        for (START(lvar); NEXT(x);)
        if (OBJECT(Variable,x)->pname == _Zname)
         rep= x;
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
ClaireClass * close_class(ClaireClass *self)
{ POP_SIGNAL; return (self);}


// Extract the symbol associated with self.
// This is useful e.g. when using read() (read@port, read@string).
//
// The c++ function for: iClaire/extract_symbol(self:any) [RETURN_ARG]
symbol * extract_symbol_any(OID self)
{ { symbol *Result ;
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
          symbol_I_string2("true") :
          symbol_I_string2("nil") );
        }
      else close_exception(((general_error *) (*Core._general_error)(_string_("[147] a name cannot be made from ~S"),
          _oid_(list::alloc(1,self)))));
        Result= (symbol *) V_CC;}
    POP_SIGNAL; return (Result);}
  }


// we must be sure that the selector (in a has statement or in a message)
// is a property.
//
// The c++ function for: iClaire/make_a_property(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
property * make_a_property_any(OID self)
{ GC_BIND;
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
            (p->comment = string_I_symbol(OBJECT(symbol,self)));
            (p->domain = Kernel._any);
            (p->range = Kernel._any);
            V_CC = p;
            }
          }
      else if (INHERIT(OWNER(self),Kernel._unbound_symbol))
       V_CC = make_a_property_any(_oid_(OBJECT(unbound_symbol,self)->name));
      else close_exception(((general_error *) (*Core._general_error)(_string_("[148] Wrong selector: ~S, cannot make a property\n"),
          _oid_(list::alloc(1,self)))));
        Result= (property *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// *********************************************************************
// *  Part 4: Pretty printing                                          *
// *********************************************************************
// fuck
// The c++ function for: lbreak(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  lbreak_void()
{ { OID Result = 0;
    if (Core.pretty->pprint == CTRUE)
     { if (Core.pretty->pbreak == CTRUE)
       { princ_string("\n");
        put_buffer_void();
        Result = indent_integer(Core.pretty->index);
        }
      else if ((CL_INT)buffer_length_void() > (CL_INT)Core.pretty->width)
       { OID  V_CL0315;close_exception((ClaireException *) new_object_class(Core._much_too_far));
        
        Result=_void_(V_CL0315);}
      else Result = Kernel.cfalse;
        }
    else Result = Kernel.cfalse;
      POP_SIGNAL; return (Result);}
  }


// The c++ function for: put_buffer(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  put_buffer_void()
{ GC_BIND;
  { OID Result = 0;
    { char * buffer = GC_STRING(end_of_string_void());
      princ_string(buffer);
      print_in_string_void();
      Result = _oid_(Kernel.emptySet);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: checkfar(_CL_obj:void) [NEW_ALLOC]
OID  checkfar_void()
{ { OID Result = 0;
    if ((Core.pretty->pprint == CTRUE) && 
        ((Core.pretty->pbreak != CTRUE) && 
          ((CL_INT)buffer_length_void() > (CL_INT)Core.pretty->width)))
     { OID  V_CL0316;close_exception((ClaireException *) new_object_class(Core._much_too_far));
      
      Result=_void_(V_CL0316);}
    else Result = Kernel.cfalse;
      POP_SIGNAL; return (Result);}
  }


// The c++ function for: lbreak(n:integer) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
OID  lbreak_integer(int n)
{ (Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)n));
  POP_SIGNAL; return (lbreak_void());}


// indentation
//
// The c++ function for: indent(limit:integer) [RETURN_ARG]
OID  indent_integer(int limit)
{ { OID Result = 0;
    { CL_INT  x = buffer_length_void();
      { CL_INT loop_handle = ClEnv->cHandle;
        Result= _oid_(CFALSE);
        while (((CL_INT)x < (CL_INT)limit))
        { princ_string(" ");
          ++x;
          POP_SIGNAL;}
        }
      }
    POP_SIGNAL; return (Result);}
  }


// sets the current_level
// The c++ function for: set_level(_CL_obj:void) [SLOT_UPDATE+RETURN_ARG]
void  set_level_void()
{ (Core.pretty->index = ((CL_INT)buffer_length_void()-(CL_INT)1));
  POP_SIGNAL;}


// The c++ function for: set_level(n:integer) [SLOT_UPDATE+RETURN_ARG]
void  set_level_integer(int n)
{ set_level_void();
  (Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)n));
  POP_SIGNAL;}


// prints a bag as a box
//
// The c++ function for: printbox(self:bag,start:integer,finish:integer,s:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  printbox_bag1(bag *self,int start,int finish,char *s)
{ { OID Result = 0;
    { CL_INT  i = 1;
      ClaireBoolean * startline = CTRUE;
      CL_INT  n = self->length;
      CL_INT  _Zl = Core.pretty->index;
      (Core.pretty->index = start);
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
              { princ_string(" ");
                POP_SIGNAL;}
              }
            { CL_INT  idx = buffer_length_void();
              { ClaireHandler c_handle = ClaireHandler();
                if ERROR_IN 
                { { (Core.pretty->pbreak = CFALSE);
                    printexp_any((*(self))[i],CTRUE);
                    (Core.pretty->pbreak = CTRUE);
                    }
                  ERROR_FREE;}
                else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Core._much_too_far)) == CTRUE)
                { c_handle.catchIt();{ (Core.pretty->pbreak = CTRUE);
                    (Core.pretty->index = start);
                    }
                  }
                else PREVIOUS_HANDLER;}
              if (i != n)
               princ_string(s);
              if ((CL_INT)buffer_length_void() < (CL_INT)finish)
               { ++i;
                startline= CFALSE;
                }
              else { buffer_set_length_integer(idx);
                  if (startline != CTRUE)
                   { lbreak_void();
                    startline= CTRUE;
                    }
                  else { set_level_void();
                      (Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)1));
                      printexp_any((*(self))[i],CTRUE);
                      (Core.pretty->index = _Zl);
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
        (Core.pretty->index = _Zl);
      Result = CNULL;
      }
    POP_SIGNAL; return (Result);}
  }


// default value of arguments
//
// The c++ function for: printbox(self:bag) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  printbox_bag2(bag *self)
{ POP_SIGNAL; return (printbox_bag1(self,buffer_length_void(),Core.pretty->width,", "));}


// The c++ function for: printbox(self:bag,s:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  printbox_bag3(bag *self,char *s)
{ POP_SIGNAL; return (printbox_bag1(self,buffer_length_void(),Core.pretty->width,s));}


// The c++ function for: printl(self:bag,s:string) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  printl_bag(bag *self,char *s)
{ GC_BIND;
  { ClaireBoolean * f = CTRUE;
    ClaireBoolean * b = Core.pretty->pprint;
    (Core.pretty->pprint = CFALSE);
    { ClaireHandler c_handle = ClaireHandler();
      if ERROR_IN 
      { { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(x);
          for (START(self); NEXT(x);)
          { if (f == CTRUE)
             f= CFALSE;
            else princ_string(s);
              printexp_any(x,CTRUE);
            if ((b == CTRUE) && 
                ((Core.pretty->pbreak != CTRUE) && 
                  ((CL_INT)buffer_length_void() > (CL_INT)Core.pretty->width)))
             { (Core.pretty->pprint = b);
              close_exception((ClaireException *) new_object_class(Core._much_too_far));
              }
            }
          }
        ERROR_FREE;}
      else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._system_error)) == CTRUE)
      { c_handle.catchIt();{ ClaireException * x = GC_OBJECT(ClaireException,ClEnv->exception_I);
          if ((b == CTRUE) && 
              (CLREAD(system_error,x,index) == 16))
           { (Core.pretty->pprint = b);
            close_exception((ClaireException *) new_object_class(Core._much_too_far));
            }
          else close_exception(x);
            }
        }
      else PREVIOUS_HANDLER;}
    (Core.pretty->pprint = b);
    }
  GC_UNBIND; POP_SIGNAL;}


// print bounded prints a bounded expression using ( and )
// The c++ function for: printexp(self:any,comp:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  printexp_any(OID self,ClaireBoolean *comp)
{ if (((INHERIT(OWNER(self),Language._Call)) && (((INHERIT(OBJECT(Call,self)->selector->isa,Kernel._operation)) ? ((comp != CTRUE) ? ((OBJECT(Call,self)->args->length == 2) ? CTRUE: CFALSE): CFALSE): CFALSE) != CTRUE)) || 
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
      princ_string("(");
      set_level_integer(1);
      print_any(self);
      princ_string(")");
      (Core.pretty->index = _Zl);
      }
    POP_SIGNAL;}


// The c++ function for: pretty_print(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  pretty_print_any(OID self)
{ print_in_string_void();
  (Core.pretty->pprint = CTRUE);
  (Core.pretty->pbreak = CTRUE);
  (Core.pretty->index = 0);
  print_any(self);
  (Core.pretty->pprint = CFALSE);
  princ_string(end_of_string_void());
  POP_SIGNAL;}


// The c++ function for: self_print(self:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  self_print_list_Language(list *self)
{ if (equal(_oid_(of_bag(self)),_oid_(Kernel.emptySet)) != CTRUE)
   { princ_string("list<");
    print_any(_oid_(of_bag(self)));
    princ_string(">");
    }
  { princ_string("(");
    printbox_bag2(self);
    princ_string(")");
    }
  POP_SIGNAL;}


// The c++ function for: self_print(self:set) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  self_print_set_Language(set *self)
{ if (equal(_oid_(of_bag(self)),_oid_(Kernel.emptySet)) == CTRUE)
   { princ_string("{");
    printbox_bag2(self);
    princ_string("}");
    }
  else { princ_string("set<");
      print_any(_oid_(of_bag(self)));
      princ_string(">");
      princ_string("(");
      printbox_bag2(self);
      princ_string(")");
      }
    POP_SIGNAL;}


// to remove !
// The c++ function for: self_print(self:tuple) [NEW_ALLOC+SLOT_UPDATE]
void  self_print_tuple_Language(tuple *self)
{ princ_string("tuple(");
  printbox_bag2(self);
  princ_string(")");
  POP_SIGNAL;}


// bend of file

