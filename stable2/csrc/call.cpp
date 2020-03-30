/***** CLAIRE Compilation of file ./meta/call.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:38 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>

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
//<sb> add a pointer to the location of the call in source (debug)
//<sb> tells how to print ?>....<?
// The c++ function for: self_print(self:Princ_wcl) [NEW_ALLOC]
void  self_print_Princ_wcl1_Language(Princ_wcl *self)
{ GC_BIND;
  princ_string("?>");
  (*Kernel.princ)((*(self->args))[1]);
  princ_string("<?");
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_print(self:Call_wcl) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  self_print_Call_wcl1_Language(Call_wcl *self)
{ GC_BIND;
  if (self->selector == Language.echo)
   princ_string("= ");
  else if (self->selector == Language.self_html)
   princ_string("== ");
  else { princ_string(self->selector->name->name);
      princ_string(" ");
      }
    print_any(GC_OID((*(self->args))[1]));
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_print(self:Call) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  self_print_Call_Language(Call *self)
{ GC_BIND;
  { CL_INT  _Zl = Core.pretty->index;
    property * _Zs = self->selector;
    list * _Za = GC_OBJECT(list,self->args);
    if ((INHERIT(_Zs->isa,Kernel._operation)) && 
        (_Za->length == 2))
     { (Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)2));
      printe_any((*(_Za))[1],_Zs);
      princ_string(" ");
      print_any(_oid_(_Zs));
      princ_string(" ");
      lbreak_void();
      printe_any((*(_Za))[2],_Zs);
      }
    else if (_Zs == Kernel.nth)
     { if (_Za->length == 3)
       { printexp_any((*(_Za))[1],CFALSE);
        princ_string("[");
        print_any((*(_Za))[2]);
        princ_string(",");
        print_any((*(_Za))[3]);
        princ_string("]");
        }
      else if (_Za->length == 1)
       { printexp_any((*(_Za))[1],CFALSE);
        princ_string("[]");
        }
      else { printexp_any((*(_Za))[1],CFALSE);
          princ_string("[");
          if (_Za->length == 2)
           print_any((*(_Za))[2]);
          princ_string("]");
          }
        }
    else if ((_Zs == Kernel.nth_equal) && 
        (3 <= (CL_INT)_Za->length))
     { OID  a = (*(_Za))[3];
      OID  o;
      if (INHERIT(OWNER(a),Language._Call))
       o = _oid_(OBJECT(Call,a)->selector);
      else o = Kernel.cfalse;
        if (_Za->length == 4)
       { printexp_any((*(_Za))[1],CFALSE);
        princ_string("[");
        print_any((*(_Za))[2]);
        princ_string(",");
        print_any(a);
        princ_string("] := ");
        lbreak_integer(2);
        print_any((*(_Za))[4]);
        }
      else { ClaireBoolean * g0321I;
        { OID  g0322UU;
          if (INHERIT(OWNER(a),Language._Call))
           g0322UU = (*(OBJECT(Call,a)->args))[1];
          else g0322UU = Kernel.cfalse;
            g0321I = sugar_ask_any((*(_Za))[1],(*(_Za))[2],o,g0322UU);
          }
        
        if (g0321I == CTRUE) { print_any((*(_Za))[1]);
            princ_string("[");
            print_any((*(_Za))[2]);
            princ_string("] :");
            print_any(o);
            princ_string(" ");
            lbreak_integer(2);
            print_any(GC_OID((*(OBJECT(bag,(*Core.args)(a))))[2]));
            }
          else { print_any((*(_Za))[1]);
          princ_string("[");
          print_any((*(_Za))[2]);
          princ_string("] := ");
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
        { ClaireBoolean * g0323I;
        { OID  g0324UU;
          if (INHERIT(OWNER(a),Language._Call))
           g0324UU = (*(OBJECT(Call,a)->args))[1];
          else g0324UU = Kernel.cfalse;
            g0323I = sugar_ask_any((*(_Za))[1],(*(_Za))[2],o,g0324UU);
          }
        
        if (g0323I == CTRUE) { print_any((*(_Za))[1]);
            princ_string("(");
            print_any((*(_Za))[2]);
            princ_string(") :");
            print_any(o);
            princ_string(" ");
            lbreak_integer(2);
            print_any(GC_OID((*(OBJECT(bag,(*Core.args)(a))))[2]));
            }
          else { print_any((*(_Za))[1]);
          princ_string("(");
          print_any((*(_Za))[2]);
          princ_string(") := ");
          lbreak_integer(2);
          print_any((*(_Za))[3]);
          }
        }
      }
    else if ((_Zs == Kernel.add) && 
        (INHERIT(OWNER((*(_Za))[1]),Kernel._property)))
     { print_any((*(_Za))[1]);
      princ_string("(");
      print_any((*(_Za))[2]);
      princ_string(") :add ");
      lbreak_integer(2);
      print_any((*(_Za))[3]);
      }
    else if ((_Zs == Kernel._delete) && 
        (INHERIT(OWNER((*(_Za))[1]),Kernel._property)))
     { print_any((*(_Za))[1]);
      princ_string("(");
      print_any((*(_Za))[2]);
      princ_string(") :delete ");
      lbreak_integer(2);
      print_any((*(_Za))[3]);
      }
    else if (((*(_Za))[1] == _oid_(ClEnv)) && 
        (_Za->length == 1))
     { print_any(_oid_(_Zs));
      princ_string("()");
      }
    else { print_any(_oid_(_Zs));
        princ_string("(");
        set_level_void();
        printbox_bag2(_Za);
        princ_string(")");
        }
      (Core.pretty->index = _Zl);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_print(self:Call+) [NEW_ALLOC+SLOT_UPDATE]
OID  self_print_Call_plus_Language(Call_plus *self)
{ GC_BIND;
  printexp_any(GC_OID((*(self->args))[1]),CTRUE);
  princ_string(".");
  { OID Result = 0;
    print_any(_oid_(self->selector));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: self_eval(self:Call) [SAFE_GC]
OID  self_eval_Call(Call *self)
{ if (ClEnv->debug_I != ((CL_INT)-1))
   PUSH(_oid_(self));
  { OID Result = 0;
    { CL_INT  start = ClEnv->index;
      property * p = self->selector;
      if (0 <= (CL_INT)ClEnv->debug_I)
       (Language.LastCall->value= _oid_(self));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(x);
        bag *x_support;
        x_support = self->args;
        for (START(x_support); NEXT(x);)
        PUSH(OPT_EVAL(x));
        }
      { OID  rx = eval_message_property(p,find_which_property1(p,start,OWNER(ClEnv->stack[((OID)start)])),start,CTRUE);
        if (0 <= (CL_INT)ClEnv->debug_I)
         (Language.LastCall->value= _oid_(self));
        if (ClEnv->debug_I != ((CL_INT)-1))
         (ClEnv->index= ((OID)((CL_INT)start-(CL_INT)1)));
        Result = rx;
        }
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: self_eval(self:Call+) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_eval_Call_plus(Call_plus *self)
{ GC_BIND;
  { OID Result = 0;
    { property * p = self->selector;
      OID  x = GC_OID(eval_any(GC_OID((*(self->args))[1])));
      ClaireObject * s = GC_OBJECT(ClaireObject,_at_property1(p,OWNER(x)));
      if (equal(_oid_(OWNER(_oid_(s))),_oid_(Kernel._slot)) != CTRUE)
       { OID  V_CL0329;close_exception(((selector_error *) (*Core._selector_error)(_oid_(p),
          _oid_(list::alloc(1,x)))));
        
        Result=_void_(V_CL0329);}
      else { OID  z = slot_get_object(OBJECT(ClaireObject,x),CLREAD(slot,s,index),CLREAD(slot,s,srange));
          if ((z != CNULL) || 
              (belong_to(z,(*Kernel.range)(_oid_(s))) == CTRUE))
           { CL_INT  n = ClEnv->trace_I;
            CL_INT  d = ClEnv->debug_I;
            if (((CL_INT)n > 0) && 
                (n == ClEnv->step_I))
             { (ClEnv->trace_I = 0);
              (ClEnv->debug_I = -1);
              { CL_INT  g0325 = (int )(current_color);
                CL_INT  g0326 = (int )(current_bold);
                CL_INT  g0327 = g0325;
                CL_INT  g0328 = g0326;
                color(g0325,g0326);
                color_princ_string1("  `GREENread: ");
                g0325= (int )(current_color);
                g0326= (int )(current_bold);
                color(g0327,g0328);
                print_any(_oid_(p));
                color(g0325,g0326);
                color(g0325,g0326);
                color_princ_string1("(");
                g0325= (int )(current_color);
                g0326= (int )(current_bold);
                color(g0327,g0328);
                print_any(x);
                color(g0325,g0326);
                color(g0325,g0326);
                color_princ_string1(") = ");
                g0325= (int )(current_color);
                g0326= (int )(current_bold);
                color(g0327,g0328);
                print_any(z);
                color(g0325,g0326);
                color(g0325,g0326);
                color_princ_string1("\n");
                color(g0327,g0328);
                }
              (ClEnv->debug_I = d);
              (ClEnv->trace_I = n);
              }
            Result = z;
            }
          else { OID  V_CL0330;close_exception(((read_slot_error *) (*Core._read_slot_error)(x,
                _oid_(p))));
              
              Result=_void_(V_CL0330);}
            }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// recursive printing of bicall
//
// The c++ function for: printe(self:any,s:property) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  printe_any(OID self,property *s)
{ if ((INHERIT(OWNER(self),Language._Call)) && ((INHERIT(OBJECT(Call,self)->selector->isa,Kernel._operation)) && 
      (OBJECT(Call,self)->args->length == 2)))
   { if (CTRUE == CTRUE)
     { princ_string("(");
      print_any(self);
      princ_string(")");
      }
    else printexp_any(self,CTRUE);
      }
  else printexp_any(self,CTRUE);
    POP_SIGNAL;}


// tells if the sugar :op can be used
//
// The c++ function for: sugar?(x:any,x2:any,o:any,a:any) [0]
ClaireBoolean * sugar_ask_any(OID x,OID x2,OID o,OID a)
{ { ClaireBoolean *Result ;
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
void  self_print_Assign_Language(Assign *self)
{ GC_BIND;
  { OID  a = GC_OID(self->arg);
    OID  o;
    if (INHERIT(OWNER(a),Language._Call))
     o = _oid_(OBJECT(Call,a)->selector);
    else o = Kernel.cfalse;
      { ClaireBoolean * g0336I;
      { OID  g0337UU;
        if (INHERIT(OWNER(a),Language._Call))
         g0337UU = (*(OBJECT(Call,a)->args))[1];
        else g0337UU = Kernel.cfalse;
          g0336I = sugar_ask_any(self->var,_oid_(Kernel.emptySet),o,g0337UU);
        }
      
      if (g0336I == CTRUE) { print_any(GC_OID(self->var));
          princ_string(" :");
          print_any(o);
          princ_string(" ");
          lbreak_integer(2);
          printexp_any(GC_OID((*(OBJECT(bag,(*Core.args)(a))))[2]),CTRUE);
          }
        else { CL_INT  g0332 = (int )(current_color);
        CL_INT  g0333 = (int )(current_bold);
        CL_INT  g0334 = g0332;
        CL_INT  g0335 = g0333;
        color(g0334,g0335);
        print_any(GC_OID(self->var));
        color(g0332,g0333);
        color(g0332,g0333);
        color_princ_string1(" `BLUE:= `BLACK");
        g0332= (int )(current_color);
        g0333= (int )(current_bold);
        color(g0334,g0335);
        lbreak_integer(2);
        color(g0332,g0333);
        color(g0334,g0335);
        printexp_any(a,CTRUE);
        color(g0332,g0333);
        color(g0334,g0335);
        }
      }
    (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Assign) [NEW_ALLOC+RETURN_ARG]
OID  self_eval_Assign(Assign *self)
{ GC_BIND;
  { OID Result = 0;
    if (INHERIT(OWNER(self->var),Language._Variable))
     Result = write_value_Variable(GC_OBJECT(Variable,OBJECT(Variable,self->var)),GC_OID(OPT_EVAL(self->arg)));
    else { OID  V_CL0338;close_exception(((general_error *) (*Core._general_error)(_string_("[101] ~S is not a variable"),
          _oid_(list::alloc(1,self->var)))));
        
        Result=_void_(V_CL0338);}
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// global variables
//
// The c++ function for: self_print(self:Gassign) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  self_print_Gassign_Language(Gassign *self)
{ GC_BIND;
  { OID  a = GC_OID(self->arg);
    OID  o;
    if (INHERIT(OWNER(a),Language._Call))
     o = _oid_(OBJECT(Call,a)->selector);
    else o = Kernel.cfalse;
      { ClaireBoolean * g0344I;
      { OID  g0345UU;
        if (INHERIT(OWNER(a),Language._Call))
         g0345UU = (*(OBJECT(Call,a)->args))[1];
        else g0345UU = Kernel.cfalse;
          g0344I = sugar_ask_any(_oid_(self->var),_oid_(Kernel.emptySet),o,g0345UU);
        }
      
      if (g0344I == CTRUE) { print_any(_oid_(self->var));
          princ_string(" :");
          print_any(o);
          princ_string(" ");
          lbreak_integer(2);
          print_any(GC_OID((*(OBJECT(bag,(*Core.args)(a))))[2]));
          }
        else { CL_INT  g0340 = (int )(current_color);
        CL_INT  g0341 = (int )(current_bold);
        CL_INT  g0342 = g0340;
        CL_INT  g0343 = g0341;
        color(g0342,g0343);
        print_any(_oid_(self->var));
        color(g0340,g0341);
        color(g0340,g0341);
        color_princ_string1(" `BLUE:= `BLACK");
        g0340= (int )(current_color);
        g0341= (int )(current_bold);
        color(g0342,g0343);
        lbreak_integer(2);
        color(g0340,g0341);
        color(g0342,g0343);
        print_any(a);
        color(g0340,g0341);
        color(g0342,g0343);
        }
      }
    (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Gassign) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
OID  self_eval_Gassign(Gassign *self)
{ GC_BIND;
  { OID Result = 0;
    { global_variable * v = self->var;
      Result = write_value_global_variable(v,GC_OID(eval_any(GC_OID(self->arg))));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//--------------- BOOLEAN OPERATIONS ---------------------------------
// "and" is strictly boolean and is based on short-circuit evaluation.
//
// The c++ function for: self_print(self:And) [NEW_ALLOC+SLOT_UPDATE]
void  self_print_And_Language(And *self)
{ GC_BIND;
  princ_string("(");
  printbox_bag3(GC_OBJECT(list,self->args)," & ");
  princ_string(")");
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:And) [NEW_ALLOC]
OID  self_eval_And(And *self)
{ GC_BIND;
  { OID Result = 0;
    { ClaireBoolean * V_CL0346;{ OID  g0347UU;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(x);
          g0347UU= Kernel.cfalse;
          for (START(self->args); NEXT(x);)
          if (boolean_I_any(OPT_EVAL(x)) != CTRUE)
           { g0347UU = Kernel.ctrue;
            ClEnv->cHandle = loop_handle;break;}
          }
        V_CL0346 = not_any(g0347UU);
        }
      
      Result=_oid_(V_CL0346);}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// or expression
//
// The c++ function for: self_print(self:Or) [NEW_ALLOC+SLOT_UPDATE]
void  self_print_Or_Language(Or *self)
{ GC_BIND;
  princ_string("(");
  printbox_bag3(GC_OBJECT(list,self->args)," | ");
  princ_string(")");
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Or) [NEW_ALLOC]
OID  self_eval_Or(Or *self)
{ GC_BIND;
  { OID Result = 0;
    { ClaireBoolean * g0348I;
      { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(x);
          V_C= Kernel.cfalse;
          for (START(self->args); NEXT(x);)
          if (boolean_I_any(OPT_EVAL(x)) == CTRUE)
           { V_C = Kernel.ctrue;
            ClEnv->cHandle = loop_handle;break;}
          }
        
        g0348I=OBJECT(ClaireBoolean,V_C);}
      
      if (g0348I == CTRUE) Result = Kernel.ctrue;
        else Result = Kernel.cfalse;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// ----------------- an anti-evaluator ---------------------------------
//
// The c++ function for: self_print(self:Quote) [NEW_ALLOC]
void  self_print_Quote_Language(Quote *self)
{ GC_BIND;
  princ_string("quote(");
  print_any(GC_OID(self->arg));
  princ_string(")");
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Quote) [RETURN_ARG]
OID  self_eval_Quote(Quote *self)
{ POP_SIGNAL; return (self->arg);}


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
// The c++ function for: self_print(self:Call_method) [NEW_ALLOC+SLOT_UPDATE]
void  self_print_Call_method_Language(Call_method *self)
{ GC_BIND;
  print_any(_oid_(self->arg));
  princ_string("(");
  princ_bag(GC_OBJECT(list,self->args));
  princ_string(")");
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Call_method) [NEW_ALLOC+SLOT_UPDATE]
OID  self_eval_Call_method(Call_method *self)
{ GC_BIND;
  if (ClEnv->debug_I != ((CL_INT)-1))
   PUSH(_oid_(self));
  { OID Result = 0;
    { CL_INT  start = ClEnv->index;
      method * Cprop = self->arg;
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
      { OID  r = GC_OID(execute_method(Cprop,start,CTRUE));
        Result = r;
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// same thing with one only argument: we do not use the stack
//
// The c++ function for: self_eval(self:Call_method1) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_eval_Call_method1(Call_method1 *self)
{ GC_BIND;
  { OID Result = 0;
    { method * f = self->arg;
      list * l = GC_OBJECT(list,self->args);
      Result = funcall_method1(f,GC_OID(OPT_EVAL((*(l))[1])));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// same thing with two arguments
//
// The c++ function for: self_eval(self:Call_method2) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_eval_Call_method2(Call_method2 *self)
{ GC_BIND;
  { OID Result = 0;
    { method * f = self->arg;
      list * l = GC_OBJECT(list,self->args);
      Result = funcall_method2(f,GC_OID(OPT_EVAL((*(l))[1])),GC_OID(OPT_EVAL((*(l))[2])));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// an instruction to read a slot
//
// The c++ function for: self_print(self:Call_slot) [NEW_ALLOC]
void  self_print_Call_slot_Language(Call_slot *self)
{ GC_BIND;
  print_any(_oid_(self->selector));
  princ_string("(");
  print_any(GC_OID(self->arg));
  princ_string(")");
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Call_slot) [NEW_ALLOC+RETURN_ARG]
OID  self_eval_Call_slot(Call_slot *self)
{ GC_BIND;
  { OID Result = 0;
    Result = get_slot(self->selector,OBJECT(ClaireObject,OPT_EVAL(self->arg)));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// an instruction to read an array
// selector is an exp with type array, arg is an exp with type integer, and test
// contains the inferred member_type of the array
//
// The c++ function for: self_print(self:Call_array) [NEW_ALLOC]
void  self_print_Call_array_Language(Call_array *self)
{ GC_BIND;
  print_any(GC_OID(self->selector));
  princ_string("[");
  print_any(GC_OID(self->arg));
  princ_string("]");
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Call_array) [NEW_ALLOC+RETURN_ARG]
OID  self_eval_Call_array(Call_array *self)
{ GC_BIND;
  { OID Result = 0;
    Result = nth_array(array_v(OPT_EVAL(self->selector)),OPT_EVAL(self->arg));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// an instruction to read a table
//
// The c++ function for: self_print(self:Call_table) [NEW_ALLOC]
void  self_print_Call_table_Language(Call_table *self)
{ GC_BIND;
  print_any(GC_OID(_oid_(self->selector)));
  princ_string("[");
  print_any(GC_OID(self->arg));
  princ_string("]");
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Call_table) [NEW_ALLOC+RETURN_ARG]
OID  self_eval_Call_table(Call_table *self)
{ GC_BIND;
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
void  self_print_Update_Language(Update *self)
{ GC_BIND;
  print_any(GC_OID(self->selector));
  princ_string("(");
  print_any(GC_OID((*Kernel.arg)(self->var)));
  princ_string(") := ");
  print_any(GC_OID(self->value));
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Update) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_eval_Update(Update *self)
{ GC_BIND;
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
void  self_print_Super_Language(Super *self)
{ GC_BIND;
  { CL_INT  _Zl = Core.pretty->index;
    property * _Zs = self->selector;
    list * _Za = GC_OBJECT(list,self->args);
    print_any(_oid_(self->selector));
    princ_string("@");
    print_any(GC_OID(_oid_(self->cast_to)));
    princ_string("(");
    set_level_void();
    printbox_bag2(_Za);
    princ_string(")");
    (Core.pretty->index = _Zl);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Super) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_eval_Super(Super *self)
{ GC_BIND;
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
// The c++ function for: self_print(x:Cast) [NEW_ALLOC+SLOT_UPDATE]
void  self_print_Cast_Language(Cast *x)
{ GC_BIND;
  { CL_INT  g0349 = (int )(current_color);
    CL_INT  g0350 = (int )(current_bold);
    CL_INT  g0351 = g0349;
    CL_INT  g0352 = g0350;
    color(g0351,g0352);
    printexp_any(GC_OID(x->arg),CFALSE);
    color(g0349,g0350);
    color(g0349,g0350);
    color_princ_string1(" `BLUEas `BLACK");
    g0349= (int )(current_color);
    g0350= (int )(current_bold);
    color(g0351,g0352);
    printexp_any(GC_OID(_oid_(x->set_arg)),CFALSE);
    color(g0349,g0350);
    color(g0351,g0352);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Cast) [NEW_ALLOC+RETURN_ARG]
OID  self_eval_Cast(Cast *self)
{ GC_BIND;
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
void  self_print_Return_Language(Return *self)
{ GC_BIND;
  { CL_INT  g0355 = (int )(current_color);
    CL_INT  g0356 = (int )(current_bold);
    CL_INT  g0357 = g0355;
    CL_INT  g0358 = g0356;
    color(g0355,g0356);
    color_princ_string1("`BLUEbreak`BLACK(");
    g0355= (int )(current_color);
    g0356= (int )(current_bold);
    color(g0357,g0358);
    (Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)2));
    color(g0355,g0356);
    color(g0357,g0358);
    print_any(GC_OID(self->arg));
    color(g0355,g0356);
    color(g0357,g0358);
    (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
    color(g0355,g0356);
    color(g0355,g0356);
    color_princ_string1(")");
    color(g0357,g0358);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Return) [NEW_ALLOC]
OID  self_eval_Return(Return *self)
{ GC_BIND;
  { OID Result = 0;
    { OID  V_CL0359;close_exception(((return_error *) (*Core._return_error)(GC_OID(OPT_EVAL(self->arg)))));
      
      Result=_void_(V_CL0359);}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// ****************************************************************
// *       Part 4: Miscellaneous on instructions                  *
// ****************************************************************
// substitute any variable with same name as x with the value val
// The c++ function for: substitution(self:any,x:Variable,val:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  substitution_any(OID self,Variable *x,OID val)
{ GC_BIND;
  { OID Result = 0;
    if (INHERIT(OWNER(self),Language._Variable))
     { if (OBJECT(Variable,self)->pname == x->pname)
       Result = val;
      else Result = self;
        }
    else if (INHERIT(OWNER(self),Kernel._bag))
     { { CL_INT  i = 1;
        CL_INT  g0360 = OBJECT(bag,self)->length;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)i <= (CL_INT)g0360))
          { GC_LOOP;
            if ((INHERIT(OWNER((*(OBJECT(bag,self)))[i]),Language._Variable)) || 
                (INHERIT(OWNER((*(OBJECT(bag,self)))[i]),Kernel._unbound_symbol)))
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
        OID gc_local;
        ITERATE(s);
        bag *s_support;
        s_support = OWNER(self)->slots;
        for (START(s_support); NEXT(s);)
        { OID  y = get_slot(OBJECT(slot,s),OBJECT(ClaireObject,self));
          if ((INHERIT(OWNER(y),Language._Variable)) || 
              (INHERIT(OWNER(y),Kernel._unbound_symbol)))
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
int  occurrence_any(OID self,Variable *x)
{ { CL_INT Result = 0;
    if (INHERIT(OWNER(self),Language._Variable))
     { Result = ((OBJECT(Variable,self)->pname == x->pname) ?
        1 :
        0 );
      }
    else if (INHERIT(OWNER(self),Kernel._bag))
     { CL_INT  n = 0;
      { CL_INT  i = 1;
        CL_INT  g0361 = OBJECT(bag,self)->length;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)i <= (CL_INT)g0361))
          { n= ((CL_INT)n+(CL_INT)occurrence_any((*(OBJECT(bag,self)))[i],x));
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
        OID gc_local;
        ITERATE(s);
        bag *s_support;
        s_support = OWNER(self)->slots;
        for (START(s_support); NEXT(s);)
        n= ((CL_INT)n+(CL_INT)occurrence_any(get_slot(OBJECT(slot,s),OBJECT(ClaireObject,self)),x));
        }
      Result = n;
      }
    else Result = 0;
      POP_SIGNAL; return (Result);}
  }


// makes a (deep) copy of the instruction self
//
// The c++ function for: instruction_copy(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  instruction_copy_any(OID self)
{ GC_BIND;
  { OID Result = 0;
    if (INHERIT(OWNER(self),Kernel._bag))
     { bag * l = copy_bag(OBJECT(bag,self));
      { CL_INT  i = 1;
        CL_INT  g0362 = OBJECT(bag,self)->length;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)i <= (CL_INT)g0362))
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
        OID gc_local;
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



