/***** CLAIRE Compilation of file ./meta/control.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:39 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>

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
void  self_print_If_Language(If *self)
{ princ_string("(");
  (Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)1));
  printstat_If(self);
  (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)1));
  princ_string(")");
  POP_SIGNAL;}


// The c++ function for: printstat(self:If) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  printstat_If(If *self)
{ GC_BIND;
  { CL_INT  g0366 = (int )(current_color);
    CL_INT  g0367 = (int )(current_bold);
    CL_INT  g0368 = g0366;
    CL_INT  g0369 = g0367;
    color(g0366,g0367);
    color_princ_string1("`BLUEif `BLACK");
    g0366= (int )(current_color);
    g0367= (int )(current_bold);
    color(g0368,g0369);
    printexp_any(GC_OID(self->test),CFALSE);
    checkfar_void();
    color(g0366,g0367);
    color(g0366,g0367);
    color_princ_string1(" ");
    g0366= (int )(current_color);
    g0367= (int )(current_bold);
    color(g0368,g0369);
    printif_any(GC_OID(self->arg));
    color(g0366,g0367);
    color(g0368,g0369);
    (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)3));
    color(g0366,g0367);
    color(g0368,g0369);
    printelse_If(self);
    color(g0366,g0367);
    color(g0368,g0369);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: printif(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  printif_any(OID self)
{ (Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)3));
  if (Core.pretty->pbreak == CTRUE)
   { CL_INT  b_index = buffer_length_void();
    CL_INT  _Zl = Core.pretty->index;
    (Core.pretty->pbreak = CFALSE);
    { ClaireHandler c_handle = ClaireHandler();
      if ERROR_IN 
      { print_any(self);
        ERROR_FREE;}
      else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Core._much_too_far)) == CTRUE)
      { c_handle.catchIt();}
      else PREVIOUS_HANDLER;}
    (Core.pretty->pbreak = CTRUE);
    if (short_enough_integer(buffer_length_void()) == CTRUE)
     ;else { buffer_set_length_integer(b_index);
        (Core.pretty->index = _Zl);
        lbreak_void();
        print_any(self);
        }
      }
  else print_any(self);
    POP_SIGNAL;}


// The c++ function for: printelse(self:If) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  printelse_If(If *self)
{ GC_BIND;
  { OID  e = GC_OID(self->other);
    if (INHERIT(OWNER(e),Language._If))
     { CL_INT  g0372 = (int )(current_color);
      CL_INT  g0373 = (int )(current_bold);
      CL_INT  g0374 = g0372;
      CL_INT  g0375 = g0373;
      color(g0372,g0373);
      color_princ_string1(" ");
      g0372= (int )(current_color);
      g0373= (int )(current_bold);
      color(g0374,g0375);
      lbreak_void();
      color(g0372,g0373);
      color(g0372,g0373);
      color_princ_string1("`BLUEelse if `BLACK");
      g0372= (int )(current_color);
      g0373= (int )(current_bold);
      color(g0374,g0375);
      printexp_any(GC_OID(OBJECT(If,e)->test),CFALSE);
      color(g0372,g0373);
      color(g0372,g0373);
      color_princ_string1(" ");
      g0372= (int )(current_color);
      g0373= (int )(current_bold);
      color(g0374,g0375);
      printif_any(GC_OID(OBJECT(If,e)->arg));
      color(g0372,g0373);
      color(g0374,g0375);
      (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)3));
      color(g0372,g0373);
      color(g0374,g0375);
      printelse_If(OBJECT(If,e));
      color(g0372,g0373);
      color(g0374,g0375);
      }
    else if ((equal(e,Core.nil->value) != CTRUE) && 
        (e != Kernel.cfalse))
     { CL_INT  _Zl = Core.pretty->index;
      { CL_INT  g0376 = (int )(current_color);
        CL_INT  g0377 = (int )(current_bold);
        CL_INT  g0378 = g0376;
        CL_INT  g0379 = g0377;
        color(g0376,g0377);
        color_princ_string1(" ");
        g0376= (int )(current_color);
        g0377= (int )(current_bold);
        color(g0378,g0379);
        lbreak_void();
        color(g0376,g0377);
        color(g0376,g0377);
        color_princ_string1("`BLUEelse `BLACK");
        g0376= (int )(current_color);
        g0377= (int )(current_bold);
        color(g0378,g0379);
        set_level_integer(1);
        color(g0376,g0377);
        color(g0378,g0379);
        print_any(e);
        color(g0376,g0377);
        color(g0378,g0379);
        }
      (Core.pretty->index = _Zl);
      }
    }
  GC_UNBIND; POP_SIGNAL;}


// notice that the eval(test) is not a boolean thus the compiler will add
// something
// TODO: check that is is not too slow (may use a constant for _oid_(true))
// The c++ function for: self_eval(self:If) [SAFE_GC]
OID  self_eval_If(If *self)
{ { OID Result = 0;
    { CL_INT  n = ClEnv->trace_I;
      CL_INT  d = ClEnv->debug_I;
      OID  x = eval_any(self->test);
      if (((CL_INT)n > 0) && 
          ((CL_INT)n <= (CL_INT)ClEnv->step_I))
       { (ClEnv->trace_I = 0);
        (ClEnv->debug_I = -1);
        { CL_INT  g0380 = (int )(current_color);
          CL_INT  g0381 = (int )(current_bold);
          CL_INT  g0382 = g0380;
          CL_INT  g0383 = g0381;
          color(g0380,g0381);
          color_princ_string1("  `BLUEif ");
          g0380= (int )(current_color);
          g0381= (int )(current_bold);
          color(g0382,g0383);
          print_any(x);
          color(g0380,g0381);
          color(g0380,g0381);
          color_princ_string1("\n");
          color(g0382,g0383);
          }
        (ClEnv->debug_I = d);
        (ClEnv->trace_I = n);
        }
      { OID  res;
        if (x == Kernel.ctrue)
         res = eval_any(self->arg);
        else if (x == Kernel.cfalse)
         res = eval_any(self->other);
        else if (boolean_I_any(x) == CTRUE)
         res = eval_any(self->arg);
        else res = eval_any(self->other);
          if (((CL_INT)n > 0) && 
            ((CL_INT)n <= (CL_INT)ClEnv->step_I))
         { (ClEnv->trace_I = 0);
          (ClEnv->debug_I = -1);
          { CL_INT  g0384 = (int )(current_color);
            CL_INT  g0385 = (int )(current_bold);
            CL_INT  g0386 = g0384;
            CL_INT  g0387 = g0385;
            color(g0384,g0385);
            color_princ_string1("  `BLUEif -> ");
            g0384= (int )(current_color);
            g0385= (int )(current_bold);
            color(g0386,g0387);
            print_any(res);
            color(g0384,g0385);
            color(g0384,g0385);
            color_princ_string1("\n");
            color(g0386,g0387);
            }
          (ClEnv->debug_I = d);
          (ClEnv->trace_I = n);
          }
        Result = res;
        }
      }
    POP_SIGNAL; return (Result);}
  }


//--------------------- block structure------------------------------
// The c++ function for: self_print(self:Do) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  self_print_Do_Language(Do *self)
{ GC_BIND;
  { CL_INT  _Zl = Core.pretty->index;
    princ_string("(");
    set_level_integer(1);
    printdo_list(GC_OBJECT(list,self->args),CTRUE);
    (Core.pretty->index = _Zl);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: printdo(l:list,clo:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  printdo_list(list *l,ClaireBoolean *clo)
{ { CL_INT  len = l->length;
    CL_INT  n = len;
    CL_INT  i = 1;
    CL_INT  g0388 = len;
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while (((CL_INT)i <= (CL_INT)g0388))
      { { OID  x = (*(l))[i];
          ClaireClass * c = OWNER(x);
          if (c == Language._Princ_wcl)
           princ_string(" ");
          if (INHERIT(OWNER(x),Language._If))
           printstat_If(OBJECT(If,x));
          else print_any(x);
            n= ((CL_INT)n-(CL_INT)1);
          if (c == Language._Princ_wcl)
           { if ((i == len) || 
                (OWNER((*(l))[((CL_INT)i+(CL_INT)1)]) != Language._Call_wcl))
             princ_string(" ");
            }
          if (n == 0)
           { if (clo == CTRUE)
             princ_string(")");
            }
          else if ((c != Language._Princ_wcl) && 
              (c != Language._Call_wcl))
           { princ_string(", ");
            lbreak_void();
            }
          }
        ++i;
        POP_SIGNAL;}
      }
    }
  POP_SIGNAL;}


// The c++ function for: printblock(x:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  printblock_any(OID x)
{ GC_BIND;
  if (INHERIT(OWNER(x),Language._Do))
   printdo_list(GC_OBJECT(list,OBJECT(Do,x)->args),CFALSE);
  else if (INHERIT(OWNER(x),Language._If))
   printstat_If(OBJECT(If,x));
  else print_any(x);
    GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Do) [SAFE_GC]
OID  self_eval_Do(Do *self)
{ { OID Result = 0;
    { OID  res = _oid_(Kernel.emptySet);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(_Zx);
        for (START(self->args); NEXT(_Zx);)
        res= OPT_EVAL(_Zx);
        }
      Result = res;
      }
    POP_SIGNAL; return (Result);}
  }


// ----------------- lexical variable definition -----------------------
// The c++ function for: self_print(self:Let) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  self_print_Let_Language(Let *self)
{ GC_BIND;
  { CL_INT  _Zl = Core.pretty->index;
    set_level_integer(1);
    { CL_INT  g0389 = (int )(current_color);
      CL_INT  g0390 = (int )(current_bold);
      CL_INT  g0391 = g0389;
      CL_INT  g0392 = g0390;
      color(g0389,g0390);
      color_princ_string1("`BLUElet `BLACK");
      g0389= (int )(current_color);
      g0390= (int )(current_bold);
      color(g0391,g0392);
      ppvariable_Variable(GC_OBJECT(Variable,self->var));
      color(g0389,g0390);
      color(g0389,g0390);
      color_princ_string1(" := ");
      g0389= (int )(current_color);
      g0390= (int )(current_bold);
      color(g0391,g0392);
      printexp_any(GC_OID(self->value),CFALSE);
      color(g0389,g0390);
      color(g0391,g0392);
      printbody_Let(self);
      color(g0389,g0390);
      color(g0391,g0392);
      }
    (Core.pretty->index = _Zl);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: printbody(self:Let) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  printbody_Let(Let *self)
{ GC_BIND;
  { OID  a = GC_OID(self->arg);
    if (INHERIT(OWNER(a),Language._Let))
     { princ_string(",");
      lbreak_integer(4);
      ppvariable_Variable(GC_OBJECT(Variable,OBJECT(Instruction_with_var,a)->var));
      princ_string(" := ");
      printexp_any(GC_OID(OBJECT(Let,a)->value),CFALSE);
      (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)4));
      printbody_Let(OBJECT(Let,a));
      }
    else { CL_INT  g0394 = (int )(current_color);
        CL_INT  g0395 = (int )(current_bold);
        CL_INT  g0396 = g0394;
        CL_INT  g0397 = g0395;
        color(g0394,g0395);
        color_princ_string1(" `BLUEin `BLACK");
        g0394= (int )(current_color);
        g0395= (int )(current_bold);
        color(g0396,g0397);
        lbreak_integer(2);
        color(g0394,g0395);
        color(g0396,g0397);
        print_any(a);
        color(g0394,g0395);
        color(g0396,g0397);
        }
      }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Let) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_eval_Let(Let *self)
{ GC_BIND;
  { OID Result = 0;
    { OID  val = GC_OID(eval_any(GC_OID(self->value)));
      CL_INT  n = ClEnv->trace_I;
      CL_INT  d = ClEnv->debug_I;
      write_value_Variable(self->var,val);
      { OID  res = GC_OID(eval_any(GC_OID(self->arg)));
        if (((CL_INT)n > 0) && 
            ((CL_INT)n <= (CL_INT)ClEnv->step_I))
         { (ClEnv->trace_I = 0);
          (ClEnv->debug_I = -1);
          { CL_INT  g0398 = (int )(current_color);
            CL_INT  g0399 = (int )(current_bold);
            CL_INT  g0400 = g0398;
            CL_INT  g0401 = g0399;
            color(g0398,g0399);
            color_princ_string1("  `BLUE");
            g0398= (int )(current_color);
            g0399= (int )(current_bold);
            color(g0400,g0401);
            print_any(GC_OID(_oid_(self->var)));
            color(g0398,g0399);
            color(g0398,g0399);
            color_princ_string1(" := ");
            g0398= (int )(current_color);
            g0399= (int )(current_bold);
            color(g0400,g0401);
            print_any(res);
            color(g0398,g0399);
            color(g0398,g0399);
            color_princ_string1("\n");
            color(g0400,g0401);
            }
          (ClEnv->debug_I = d);
          (ClEnv->trace_I = n);
          }
        Result = res;
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// a when is a special Let that filters out the unknown value !
//
// The c++ function for: self_print(self:When) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  self_print_When_Language(When *self)
{ GC_BIND;
  { CL_INT  _Zl = Core.pretty->index;
    set_level_integer(1);
    { CL_INT  g0402 = (int )(current_color);
      CL_INT  g0403 = (int )(current_bold);
      CL_INT  g0404 = g0402;
      CL_INT  g0405 = g0403;
      color(g0402,g0403);
      color_princ_string1("`BLUEwhen `BLACK");
      g0402= (int )(current_color);
      g0403= (int )(current_bold);
      color(g0404,g0405);
      ppvariable_Variable(GC_OBJECT(Variable,self->var));
      color(g0402,g0403);
      color(g0402,g0403);
      color_princ_string1(" := ");
      g0402= (int )(current_color);
      g0403= (int )(current_bold);
      color(g0404,g0405);
      printexp_any(GC_OID(self->value),CFALSE);
      color(g0402,g0403);
      color(g0402,g0403);
      color_princ_string1(" `BLUEin `BLACK");
      g0402= (int )(current_color);
      g0403= (int )(current_bold);
      color(g0404,g0405);
      lbreak_integer(2);
      color(g0402,g0403);
      color(g0404,g0405);
      print_any(GC_OID(self->arg));
      color(g0402,g0403);
      color(g0404,g0405);
      }
    if (((self->other == CNULL) ? CTRUE : CFALSE) != CTRUE)
     { CL_INT  g0406 = (int )(current_color);
      CL_INT  g0407 = (int )(current_bold);
      CL_INT  g0408 = g0406;
      CL_INT  g0409 = g0407;
      color(g0406,g0407);
      color_princ_string1(" ");
      g0406= (int )(current_color);
      g0407= (int )(current_bold);
      color(g0408,g0409);
      lbreak_void();
      color(g0406,g0407);
      color(g0406,g0407);
      color_princ_string1("`BLUEelse `BLACK");
      g0406= (int )(current_color);
      g0407= (int )(current_bold);
      color(g0408,g0409);
      set_level_integer(1);
      color(g0406,g0407);
      color(g0408,g0409);
      print_any(GC_OID(self->other));
      color(g0406,g0407);
      color(g0408,g0409);
      }
    (Core.pretty->index = _Zl);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:When) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_eval_When(When *self)
{ GC_BIND;
  { OID Result = 0;
    { OID  val = GC_OID(eval_any(GC_OID(self->value)));
      CL_INT  n = ClEnv->trace_I;
      CL_INT  d = ClEnv->debug_I;
      if (((CL_INT)n > 0) && 
          ((CL_INT)n <= (CL_INT)ClEnv->step_I))
       { (ClEnv->trace_I = 0);
        (ClEnv->debug_I = -1);
        { CL_INT  g0410 = (int )(current_color);
          CL_INT  g0411 = (int )(current_bold);
          CL_INT  g0412 = g0410;
          CL_INT  g0413 = g0411;
          color(g0410,g0411);
          color_princ_string1("  `BLUEwhen ");
          g0410= (int )(current_color);
          g0411= (int )(current_bold);
          color(g0412,g0413);
          print_any(GC_OID(_oid_(self->var)));
          color(g0410,g0411);
          color(g0410,g0411);
          color_princ_string1(" := ");
          g0410= (int )(current_color);
          g0411= (int )(current_bold);
          color(g0412,g0413);
          print_any(val);
          color(g0410,g0411);
          color(g0410,g0411);
          color_princ_string1("\n");
          color(g0412,g0413);
          }
        (ClEnv->debug_I = d);
        (ClEnv->trace_I = n);
        }
      { OID  res;
        { if (val != CNULL)
           { write_value_Variable(self->var,val);
            res = eval_any(GC_OID(self->arg));
            }
          else res = eval_any(GC_OID(self->other));
            GC_OID(res);}
        if (((CL_INT)n > 0) && 
            ((CL_INT)n <= (CL_INT)ClEnv->step_I))
         { (ClEnv->trace_I = 0);
          (ClEnv->debug_I = -1);
          { CL_INT  g0414 = (int )(current_color);
            CL_INT  g0415 = (int )(current_bold);
            CL_INT  g0416 = g0414;
            CL_INT  g0417 = g0415;
            color(g0414,g0415);
            color_princ_string1("  `BLUEwhen -> ");
            g0414= (int )(current_color);
            g0415= (int )(current_bold);
            color(g0416,g0417);
            print_any(res);
            color(g0414,g0415);
            color(g0414,g0415);
            color_princ_string1("\n");
            color(g0416,g0417);
            }
          (ClEnv->debug_I = d);
          (ClEnv->trace_I = n);
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
void  self_print_Let_plus_Language(Let_plus *self)
{ GC_BIND;
  { CL_INT  _Zl = Core.pretty->index;
    list * l = GC_OBJECT(list,OBJECT(Do,self->arg)->args);
    set_level_integer(1);
    { CL_INT  g0418 = (int )(current_color);
      CL_INT  g0419 = (int )(current_bold);
      CL_INT  g0420 = g0418;
      CL_INT  g0421 = g0419;
      color(g0418,g0419);
      color_princ_string1("`BLUElet `BLACK");
      g0418= (int )(current_color);
      g0419= (int )(current_bold);
      color(g0420,g0421);
      printexp_any(GC_OID(self->value),CFALSE);
      color(g0418,g0419);
      color(g0418,g0419);
      color_princ_string1(" := ");
      g0418= (int )(current_color);
      g0419= (int )(current_bold);
      color(g0420,g0421);
      printexp_any(GC_OID((*(OBJECT(bag,(*Core.args)((*(l))[1]))))[3]),CFALSE);
      color(g0418,g0419);
      color(g0418,g0419);
      color_princ_string1(" `BLUEin `BLACK");
      g0418= (int )(current_color);
      g0419= (int )(current_bold);
      color(g0420,g0421);
      lbreak_integer(2);
      color(g0418,g0419);
      color(g0420,g0421);
      print_any(GC_OID(OBJECT(Let,(*(l))[2])->value));
      color(g0418,g0419);
      color(g0420,g0421);
      }
    (Core.pretty->index = _Zl);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_print(self:Let*) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  self_print_Let_star_Language(Let_star *self)
{ GC_RESERVE(4);  // v3.0.55 optim !
  { CL_INT  _Zl = Core.pretty->index;
    OID  l = GC_OID(self->arg);
    set_level_integer(1);
    if (INHERIT(OWNER(l),Language._Let))
     { CL_INT  g0422 = (int )(current_color);
      CL_INT  g0423 = (int )(current_bold);
      CL_INT  g0424 = g0422;
      CL_INT  g0425 = g0423;
      color(g0422,g0423);
      color_princ_string1("`BLUElet `BLACK(");
      g0422= (int )(current_color);
      g0423= (int )(current_bold);
      color(g0424,g0425);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((CTRUE == CTRUE))
        { GC_LOOP;
          (*Language.ppvariable)(GC_OID((*Language.var)(l)));
          { OID  lnext = GC_OID((*Kernel.arg)(l));
            if ((INHERIT(OWNER(lnext),Language._Let)) && ((INHERIT(OWNER(OBJECT(Let,lnext)->value),Language._Call)) && 
                (equal(GC_OID((*(OBJECT(bag,(*Core.args)(GC_OID(OBJECT(Let,lnext)->value)))))[1]),GC_OID(_oid_(self->var))) == CTRUE)))
             { princ_string(",");
              GC__OID(l = lnext, 3);
              }
            else { ;ClEnv->cHandle = loop_handle; break;}
              }
          GC_UNLOOP;POP_SIGNAL;}
        }
      color(g0422,g0423);
      color(g0422,g0423);
      color_princ_string1(") := ");
      g0422= (int )(current_color);
      g0423= (int )(current_bold);
      color(g0424,g0425);
      printexp_any(GC_OID(self->value),CFALSE);
      color(g0422,g0423);
      color(g0424,g0425);
      printbody_Let(OBJECT(Let,l));
      color(g0422,g0423);
      color(g0424,g0425);
      }
    else { princ_string("(");
        { ClaireBoolean * _Zf = CTRUE;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(_Za);
            bag *_Za_support;
            _Za_support = GC_OBJECT(list,OBJECT(bag,(*Core.args)(l)));
            for (START(_Za_support); NEXT(_Za);)
            { GC_LOOP;
              { if (_Zf == CTRUE)
                 _Zf= CFALSE;
                else princ_string(",");
                  (*Language.ppvariable)(GC_OID((*Language.var)(_Za)));
                }
              GC_UNLOOP; POP_SIGNAL;}
            }
          }
        princ_string(") := ");
        printexp_any(GC_OID(self->value),CFALSE);
        }
      (Core.pretty->index = _Zl);
    }
  GC_UNBIND; POP_SIGNAL;}


// *********************************************************************
// *     Part 2: set control structures                                *
// *********************************************************************
// for is the simplest evaluation loop
//
// The c++ function for: self_print(self:For) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  self_print_For_Language(For *self)
{ GC_BIND;
  { CL_INT  g0428 = (int )(current_color);
    CL_INT  g0429 = (int )(current_bold);
    CL_INT  g0430 = g0428;
    CL_INT  g0431 = g0429;
    color(g0428,g0429);
    color_princ_string1("`BLUEfor `BLACK");
    g0428= (int )(current_color);
    g0429= (int )(current_bold);
    color(g0430,g0431);
    ppvariable_Variable(GC_OBJECT(Variable,self->var));
    color(g0428,g0429);
    color(g0428,g0429);
    color_princ_string1(" `BLUEin `BLACK");
    g0428= (int )(current_color);
    g0429= (int )(current_bold);
    color(g0430,g0431);
    { CL_INT  _Zl = Core.pretty->index;
      set_level_void();
      printexp_any(GC_OID(self->set_arg),CFALSE);
      (Core.pretty->index = _Zl);
      }
    color(g0428,g0429);
    color(g0428,g0429);
    color_princ_string1(" ");
    g0428= (int )(current_color);
    g0429= (int )(current_bold);
    color(g0430,g0431);
    (Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)2));
    lbreak_void();
    print_any(GC_OID(self->arg));
    (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
    color(g0428,g0429);
    color(g0430,g0431);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:For) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_eval_For(For *self)
{ GC_BIND;
  { OID Result = 0;
    { OID  x = GC_OID(eval_any(GC_OID(self->set_arg)));
      CL_INT  n = ClEnv->trace_I;
      CL_INT  d = ClEnv->debug_I;
      if (((CL_INT)n > 0) && 
          ((CL_INT)n <= (CL_INT)ClEnv->step_I))
       { (ClEnv->trace_I = 0);
        (ClEnv->debug_I = -1);
        { CL_INT  g0432 = (int )(current_color);
          CL_INT  g0433 = (int )(current_bold);
          CL_INT  g0434 = g0432;
          CL_INT  g0435 = g0433;
          color(g0432,g0433);
          color_princ_string1("  `BLUEfor ");
          g0432= (int )(current_color);
          g0433= (int )(current_bold);
          color(g0434,g0435);
          print_any(GC_OID(_oid_(self->var)));
          color(g0432,g0433);
          color(g0432,g0433);
          color_princ_string1(" in ");
          g0432= (int )(current_color);
          g0433= (int )(current_bold);
          color(g0434,g0435);
          print_any(x);
          color(g0432,g0433);
          color(g0432,g0433);
          color_princ_string1("\n");
          color(g0434,g0435);
          }
        (ClEnv->debug_I = d);
        (ClEnv->trace_I = n);
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
              CL_INT  g0436 = 1;
              CL_INT  g0437 = n;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                res= _oid_(CFALSE);
                while (((CL_INT)g0436 <= (CL_INT)g0437))
                { GC_LOOP;
                  { OID  z = nth_get_array(array_v(x),g0436);
                    write_value_Variable(self->var,z);
                    eval_any(GC_OID(self->arg));
                    }
                  ++g0436;
                  GC_UNLOOP;POP_SIGNAL;}
                }
              }
            else if (INHERIT(OWNER(x),Core._Interval))
             { CL_INT  y = OBJECT(Interval,x)->arg1;
              CL_INT  g0438 = OBJECT(Interval,x)->arg2;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                res= _oid_(CFALSE);
                while (((CL_INT)y <= (CL_INT)g0438))
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
            else { OID  V_CL0443;close_exception(((general_error *) (*Core._general_error)(_string_("[136] ~S is not a collection !"),
                  _oid_(list::alloc(1,x)))));
                
                res=_void_(V_CL0443);}
              ERROR_FREE;}
          else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Core._return_error)) == CTRUE)
          { c_handle.catchIt();res = (*Kernel.arg)(GC_OID(_oid_(ClEnv->exception_I)));
            }
          else PREVIOUS_HANDLER;}
        if (((CL_INT)n > 0) && 
            ((CL_INT)n <= (CL_INT)ClEnv->step_I))
         { (ClEnv->trace_I = 0);
          (ClEnv->debug_I = -1);
          { CL_INT  g0439 = (int )(current_color);
            CL_INT  g0440 = (int )(current_bold);
            CL_INT  g0441 = g0439;
            CL_INT  g0442 = g0440;
            color(g0439,g0440);
            color_princ_string1("  `BLUEfor -> ");
            g0439= (int )(current_color);
            g0440= (int )(current_bold);
            color(g0441,g0442);
            print_any(res);
            color(g0439,g0440);
            color(g0439,g0440);
            color_princ_string1("\n");
            color(g0441,g0442);
            }
          (ClEnv->debug_I = d);
          (ClEnv->trace_I = n);
          }
        Result = res;
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> v3.3.33 ffor
// The c++ function for: self_print(self:iClaire/Ffor) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  self_print_Ffor1_Language(iClaire_Ffor *self)
{ GC_BIND;
  { CL_INT  _Zl = Core.pretty->index;
    CL_INT  g0446 = (int )(current_color);
    CL_INT  g0447 = (int )(current_bold);
    CL_INT  g0448 = g0446;
    CL_INT  g0449 = g0447;
    color(g0446,g0447);
    color_princ_string1("`BLUEffor `BLACK");
    g0446= (int )(current_color);
    g0447= (int )(current_bold);
    color(g0448,g0449);
    ppvariable_Variable(GC_OBJECT(Variable,self->var));
    color(g0446,g0447);
    color(g0446,g0447);
    color_princ_string1(" `BLUEin `BLACK");
    g0446= (int )(current_color);
    g0447= (int )(current_bold);
    color(g0448,g0449);
    set_level_void();
    printexp_any(GC_OID(self->set_arg),CFALSE);
    color(g0446,g0447);
    color(g0446,g0447);
    color_princ_string1(" `BLUEby `BLACK");
    g0446= (int )(current_color);
    g0447= (int )(current_bold);
    color(g0448,g0449);
    printexp_any(GC_OID(self->forkedby),CFALSE);
    (Core.pretty->index = _Zl);
    color(g0446,g0447);
    color(g0446,g0447);
    color_princ_string1(" ");
    g0446= (int )(current_color);
    g0447= (int )(current_bold);
    color(g0448,g0449);
    (Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)2));
    lbreak_void();
    print_any(GC_OID(self->arg));
    (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
    color(g0446,g0447);
    color(g0448,g0449);
    }
  GC_UNBIND; POP_SIGNAL;}


//<sb> parallel programing
// The c++ function for: self_eval(self:iClaire/Ffor) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  self_eval_Ffor1(iClaire_Ffor *self)
{ GC_RESERVE(18);  // v3.0.55 optim !
  { OID Result = 0;
    if (unix_ask_void1() != CTRUE)
     { list * res = list::empty(Kernel._any);
      list * l;
      { { list * i_bag = list::empty(Kernel.emptySet);
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
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
            { OID  g0455UU;
              { { ClaireHandler c_handle = ClaireHandler();
                  if ERROR_IN 
                  { { ClaireHandler c_handle = ClaireHandler();
                      if ERROR_IN 
                      { g0455UU = eval_any(GC_OID(self->arg));
                        ERROR_FREE;}
                      else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                      { c_handle.catchIt();{ Core_ffor_error * _CL_obj = ((Core_ffor_error *) GC_OBJECT(Core_ffor_error,new_object_class(Core._ffor_error)));
                          (_CL_obj->childpid = getpid_void());
                          { Core_ffor_error * g0456 = _CL_obj; 
                            char * g0457;
                            { print_in_string_void();
                              print_any(GC_OID(_oid_(ClEnv->exception_I)));
                              g0457 = end_of_string_void();
                              }
                            (g0456->childstr = g0457);}
                          { OID  V_CL0458;close_exception(_CL_obj);
                            
                            g0455UU=_void_(V_CL0458);}
                          }
                        }
                      else PREVIOUS_HANDLER;}
                    ERROR_FREE;}
                  else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                  { c_handle.catchIt();g0455UU = _oid_(ClEnv->exception_I);
                    }
                  else PREVIOUS_HANDLER;}
                GC_OID(g0455UU);}
              res = res->addFast((OID)g0455UU);
              }
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      Result = _oid_(cast_I_list1(res,Kernel.emptySet));
      }
    else { list * l;
        { { list * i_bag = list::empty(Kernel.emptySet);
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
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
         close_exception(((general_error *) (*Core._general_error)(_string_("[200] ~S : by range error ~S does not belong to integer"),
          _oid_(list::alloc(2,_oid_(self),N)))));
        if ((CL_INT)N <= 0)
         close_exception(((general_error *) (*Core._general_error)(_string_("[201] ~S : negative by (~S) argument in dangerous"),
          _oid_(list::alloc(2,_oid_(self),N)))));
        { list * V_CL0459;{ list * i_bag = list::empty(Kernel._list);
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(i);
              bag *i_support;
              i_support = GC_OBJECT(bag,enumerate_any(GC_OID(_oid_(_dot_dot_integer(1,N)))));
              for (START(i_support); NEXT(i);)
              { GC_LOOP;
                i_bag->addFast((OID)GC_OID(_oid_(list::alloc(Kernel._any,4,((OID)-1),
                  ((OID)0),
                  GC_OID(_oid_(blob_I_void1())),
                  ((OID)0)))));
                GC_UNLOOP; POP_SIGNAL;}
              }
            V_CL0459 = GC_OBJECT(list,i_bag);
            }
          
          childs=_oid_(V_CL0459);}
        if (((CL_INT)n > 0) && 
            ((CL_INT)n <= (CL_INT)ClEnv->step_I))
         { (ClEnv->trace_I = 0);
          (ClEnv->debug_I = -1);
          { CL_INT  g0451 = (int )(current_color);
            CL_INT  g0452 = (int )(current_bold);
            CL_INT  g0453 = g0451;
            CL_INT  g0454 = g0452;
            color(g0451,g0452);
            color_princ_string1("  `BLUEffor ");
            g0451= (int )(current_color);
            g0452= (int )(current_bold);
            color(g0453,g0454);
            print_any(GC_OID(_oid_(self->var)));
            color(g0451,g0452);
            color(g0451,g0452);
            color_princ_string1(" in ");
            g0451= (int )(current_color);
            g0452= (int )(current_bold);
            color(g0453,g0454);
            print_any(_oid_(l));
            color(g0451,g0452);
            color(g0451,g0452);
            color_princ_string1(" by ");
            g0451= (int )(current_color);
            g0452= (int )(current_bold);
            color(g0453,g0454);
            print_any(GC_OID(self->forkedby));
            color(g0451,g0452);
            color(g0451,g0452);
            color_princ_string1("\n");
            color(g0453,g0454);
            }
          (ClEnv->debug_I = d);
          (ClEnv->trace_I = n);
          }
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)res->length < (CL_INT)len))
          { GC_LOOP;
            if ((CL_INT)remain > 0)
             { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(i);
              bag *i_support;
              i_support = GC_OBJECT(bag,enumerate_any(GC_OID(_oid_(_dot_dot_integer(1,N)))));
              for (START(i_support); NEXT(i);)
              { GC_LOOP;
                { if (remain == 0)
                   { ;ClEnv->cHandle = loop_handle; break;}
                  if ((*Kernel.nth)(GC_OID((*Kernel.nth)(childs,
                      ((OID)i))),
                    ((OID)1)) == ((OID)-1))
                   { OID  current = (*(l))[lindex];
                    write_value_Variable(self->var,current);
                    { ClaireHandler c_handle = ClaireHandler();
                      if ERROR_IN 
                      { { tuple * g0450 = socketpair_void1();
                          cl_socket * s1 = GC_OBJECT(cl_socket,OBJECT(cl_socket,(*(g0450))[1]));
                          cl_socket * s2 = GC_OBJECT(cl_socket,OBJECT(cl_socket,(*(g0450))[2]));
                          if (forker_ask_void1() == CTRUE)
                           { OID  c = GC_OID((*Kernel.nth)(childs,
                              ((OID)i)));
                            fclose_device1(s1);
                            remain= ((CL_INT)remain-(CL_INT)1);
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
                          else { fclose_device1(s2);
                              { OID  g0460UU;
                                { { ClaireHandler c_handle = ClaireHandler();
                                    if ERROR_IN 
                                    { { ClaireHandler c_handle = ClaireHandler();
                                        if ERROR_IN 
                                        { g0460UU = eval_any(GC_OID(self->arg));
                                          ERROR_FREE;}
                                        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                                        { c_handle.catchIt();{ Core_ffor_error * _CL_obj = ((Core_ffor_error *) GC_OBJECT(Core_ffor_error,new_object_class(Core._ffor_error)));
                                            (_CL_obj->childpid = getpid_void());
                                            { Core_ffor_error * g0461 = _CL_obj; 
                                              char * g0462;
                                              { print_in_string_void();
                                                print_any(GC_OID(_oid_(ClEnv->exception_I)));
                                                g0462 = end_of_string_void();
                                                }
                                              (g0461->childstr = g0462);}
                                            { OID  V_CL0463;close_exception(_CL_obj);
                                              
                                              g0460UU=_void_(V_CL0463);}
                                            }
                                          }
                                        else PREVIOUS_HANDLER;}
                                      ERROR_FREE;}
                                    else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                                    { c_handle.catchIt();g0460UU = _oid_(ClEnv->exception_I);
                                      }
                                    else PREVIOUS_HANDLER;}
                                  GC_OID(g0460UU);}
                                serialize_port3(s1,g0460UU);
                                }
                              fclose_device1(s1);
                              CL_exit(0);
                              }
                            }
                        ERROR_FREE;}
                      else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                      { c_handle.catchIt();}
                      else PREVIOUS_HANDLER;}
                    }
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(i);
              bag *i_support;
              i_support = GC_OBJECT(bag,enumerate_any(GC_OID(_oid_(_dot_dot_integer(1,N)))));
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
                   { read_I_port1(OBJECT(PortObject,s));
                    if ((select_ask_integer1(10) == CTRUE) && 
                        (readable_ask_port1(OBJECT(PortObject,s)) == CTRUE))
                     { fwrite_string2(GC_STRING(fread_port4(OBJECT(PortObject,s),1024)),OBJECT(PortObject,buf));
                      if ((OBJECT(ClaireBoolean,(*Core.eof_port_ask)(s))) == CTRUE)
                       { tuple * st = GC_OBJECT(tuple,waitpid_integer2(pid)->copyIfNeeded());
                        if (((*(st))[1] == _oid_(Core.CL_WEXITED)) && 
                            ((*(st))[3] == ((OID)0)))
                         { OID  g0464UU;
                          { { ClaireHandler c_handle = ClaireHandler();
                              if ERROR_IN 
                              { g0464UU = unserialize_port1(OBJECT(PortObject,buf));
                                ERROR_FREE;}
                              else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                              { c_handle.catchIt();g0464UU = _oid_(ClEnv->exception_I);
                                }
                              else PREVIOUS_HANDLER;}
                            GC_OID(g0464UU);}
                          res = res->addFast((OID)g0464UU);
                          }
                        else res= res->addFast((OID)_oid_(st));
                          (*Core.fclose)(s);
                        set_length_blob1(OBJECT(blob,buf),0);
                        (*Kernel.nth_equal)(c,
                          ((OID)1),
                          ((OID)-1));
                        { ;ClEnv->cHandle = loop_handle; break;}
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
            (*Core.fclose)(GC_OID((*Kernel.nth)(i,
              ((OID)3))));
            GC_UNLOOP; POP_SIGNAL;}
          }
        Result = _oid_(cast_I_list1(res,Kernel.emptySet));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// [collect VAR in SET_EXPR, ...] is the same as a "for", but returns the list of values
//
// The c++ function for: self_print(self:Collect) [NEW_ALLOC+SLOT_UPDATE]
void  self_print_Collect_Language(Collect *self)
{ GC_BIND;
  { CL_INT  g0466 = (int )(current_color);
    CL_INT  g0467 = (int )(current_bold);
    CL_INT  g0468 = g0466;
    CL_INT  g0469 = g0467;
    color(g0466,g0467);
    color_princ_string1("list{ ");
    g0466= (int )(current_color);
    g0467= (int )(current_bold);
    color(g0468,g0469);
    (Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)2));
    printexp_any(GC_OID(self->arg),CFALSE);
    color(g0466,g0467);
    color(g0466,g0467);
    color_princ_string1(" | ");
    g0466= (int )(current_color);
    g0467= (int )(current_bold);
    color(g0468,g0469);
    lbreak_void();
    color(g0466,g0467);
    color(g0468,g0469);
    ppvariable_Variable(GC_OBJECT(Variable,self->var));
    color(g0466,g0467);
    color(g0466,g0467);
    color_princ_string1(" `BLUEin `BLACK");
    g0466= (int )(current_color);
    g0467= (int )(current_bold);
    color(g0468,g0469);
    { CL_INT  _Zl = Core.pretty->index;
      set_level_void();
      printexp_any(GC_OID(self->set_arg),CFALSE);
      (Core.pretty->index = ((CL_INT)_Zl-(CL_INT)2));
      }
    color(g0466,g0467);
    color(g0466,g0467);
    color_princ_string1("}");
    color(g0468,g0469);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Collect) [NEW_ALLOC]
OID  self_eval_Collect(Collect *self)
{ GC_BIND;
  { OID Result = 0;
    { OID  x = GC_OID(OPT_EVAL(self->set_arg));
      list * res = list::empty();
      if (INHERIT(OWNER(x),Kernel._class))
       { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(y);
        for (START(OBJECT(ClaireClass,x)->descendents); NEXT(y);)
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(z);
          for (START(OBJECT(ClaireClass,y)->instances); NEXT(z);)
          { write_value_Variable(self->var,z);
            res= GC_OBJECT(list,res->addFast((OID)GC_OID(OPT_EVAL(self->arg))));
            }
          }
        }
      else { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(y);
          bag *y_support;
          y_support = GC_OBJECT(bag,enumerate_any(x));
          for (START(y_support); NEXT(y);)
          { write_value_Variable(self->var,y);
            res= res->addFast((OID)GC_OID(OPT_EVAL(self->arg)));
            }
          }
        if (((self->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       { { OID  x;
          { { OID  x_some = CNULL;
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(x);
                for (START(res); NEXT(x);)
                if (belong_to(x,_oid_(self->of)) != CTRUE)
                 { x_some= x;
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
        cast_I_list1(res,self->of);
        }
      Result = _oid_(res);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// this is a set image version, that produces a set
//
// The c++ function for: self_print(self:Image) [NEW_ALLOC+SLOT_UPDATE]
void  self_print_Image_Language(Image *self)
{ GC_BIND;
  { CL_INT  g0471 = (int )(current_color);
    CL_INT  g0472 = (int )(current_bold);
    CL_INT  g0473 = g0471;
    CL_INT  g0474 = g0472;
    color(g0471,g0472);
    color_princ_string1("{ ");
    g0471= (int )(current_color);
    g0472= (int )(current_bold);
    color(g0473,g0474);
    (Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)2));
    printexp_any(GC_OID(self->arg),CFALSE);
    color(g0471,g0472);
    color(g0471,g0472);
    color_princ_string1(" | ");
    g0471= (int )(current_color);
    g0472= (int )(current_bold);
    color(g0473,g0474);
    lbreak_void();
    color(g0471,g0472);
    color(g0473,g0474);
    ppvariable_Variable(GC_OBJECT(Variable,self->var));
    color(g0471,g0472);
    color(g0471,g0472);
    color_princ_string1(" `BLUEin `BLACK");
    g0471= (int )(current_color);
    g0472= (int )(current_bold);
    color(g0473,g0474);
    { CL_INT  _Zl = Core.pretty->index;
      set_level_void();
      printexp_any(GC_OID(self->set_arg),CFALSE);
      (Core.pretty->index = ((CL_INT)_Zl-(CL_INT)2));
      }
    color(g0471,g0472);
    color(g0471,g0472);
    color_princ_string1("}");
    color(g0473,g0474);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Image) [NEW_ALLOC]
OID  self_eval_Image(Image *self)
{ GC_BIND;
  { OID Result = 0;
    { OID  x = GC_OID(OPT_EVAL(self->set_arg));
      set * res = set::empty();
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(y);
        bag *y_support;
        y_support = GC_OBJECT(bag,enumerate_any(x));
        for (START(y_support); NEXT(y);)
        { write_value_Variable(self->var,y);
          res= GC_OBJECT(set,res->addFast((OID)GC_OID(OPT_EVAL(self->arg))));
          }
        }
      if (((self->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       { { OID  x;
          { { OID  x_some = CNULL;
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(x);
                for (START(res); NEXT(x);)
                if (belong_to(x,_oid_(self->of)) != CTRUE)
                 { x_some= x;
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
void  self_print_Select_Language(Select *self)
{ GC_BIND;
  { CL_INT  g0476 = (int )(current_color);
    CL_INT  g0477 = (int )(current_bold);
    CL_INT  g0478 = g0476;
    CL_INT  g0479 = g0477;
    color(g0476,g0477);
    color_princ_string1("{ ");
    g0476= (int )(current_color);
    g0477= (int )(current_bold);
    color(g0478,g0479);
    ppvariable_Variable(GC_OBJECT(Variable,self->var));
    color(g0476,g0477);
    color(g0476,g0477);
    color_princ_string1(" `BLUEin `BLACK");
    g0476= (int )(current_color);
    g0477= (int )(current_bold);
    color(g0478,g0479);
    { CL_INT  _Zl = Core.pretty->index;
      set_level_void();
      printexp_any(GC_OID(self->set_arg),CFALSE);
      (Core.pretty->index = _Zl);
      }
    color(g0476,g0477);
    color(g0476,g0477);
    color_princ_string1(" | ");
    g0476= (int )(current_color);
    g0477= (int )(current_bold);
    color(g0478,g0479);
    lbreak_integer(2);
    print_any(GC_OID(self->arg));
    (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
    color(g0476,g0477);
    color(g0476,g0477);
    color_princ_string1("}");
    color(g0478,g0479);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Select) [NEW_ALLOC]
OID  self_eval_Select(Select *self)
{ GC_BIND;
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
        ITERATE(y);
        for (START(OBJECT(ClaireClass,x)->descendents); NEXT(y);)
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(z);
          for (START(OBJECT(ClaireClass,y)->instances); NEXT(z);)
          { write_value_Variable(self->var,z);
            if (OPT_EVAL(self->arg) != Kernel.cfalse)
             res= GC_OBJECT(set,res->addFast((OID)z));
            }
          }
        }
      else { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(y);
          bag *y_support;
          y_support = GC_OBJECT(bag,enumerate_any(x));
          for (START(y_support); NEXT(y);)
          { write_value_Variable(self->var,y);
            if (OPT_EVAL(self->arg) != Kernel.cfalse)
             res= res->addFast((OID)y);
            }
          }
        if (((self->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       { { OID  x;
          { { OID  x_some = CNULL;
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(x);
                for (START(res); NEXT(x);)
                if (belong_to(x,_oid_(self->of)) != CTRUE)
                 { x_some= x;
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
void  self_print_Lselect_Language(Lselect *self)
{ GC_BIND;
  { CL_INT  g0481 = (int )(current_color);
    CL_INT  g0482 = (int )(current_bold);
    CL_INT  g0483 = g0481;
    CL_INT  g0484 = g0482;
    color(g0481,g0482);
    color_princ_string1("list{ ");
    g0481= (int )(current_color);
    g0482= (int )(current_bold);
    color(g0483,g0484);
    ppvariable_Variable(GC_OBJECT(Variable,self->var));
    color(g0481,g0482);
    color(g0481,g0482);
    color_princ_string1(" `BLUEin `BLACK");
    g0481= (int )(current_color);
    g0482= (int )(current_bold);
    color(g0483,g0484);
    { CL_INT  _Zl = Core.pretty->index;
      set_level_void();
      printexp_any(GC_OID(self->set_arg),CFALSE);
      (Core.pretty->index = _Zl);
      }
    color(g0481,g0482);
    color(g0481,g0482);
    color_princ_string1(" | ");
    g0481= (int )(current_color);
    g0482= (int )(current_bold);
    color(g0483,g0484);
    lbreak_integer(2);
    print_any(GC_OID(self->arg));
    (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
    color(g0481,g0482);
    color(g0481,g0482);
    color_princ_string1("}");
    color(g0483,g0484);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Lselect) [NEW_ALLOC]
OID  self_eval_Lselect(Lselect *self)
{ GC_BIND;
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
        ITERATE(y);
        for (START(OBJECT(ClaireClass,x)->descendents); NEXT(y);)
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(z);
          for (START(OBJECT(ClaireClass,y)->instances); NEXT(z);)
          { write_value_Variable(self->var,z);
            if (OPT_EVAL(self->arg) != Kernel.cfalse)
             res= GC_OBJECT(list,res->addFast((OID)z));
            }
          }
        }
      else { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(y);
          bag *y_support;
          y_support = GC_OBJECT(bag,enumerate_any(x));
          for (START(y_support); NEXT(y);)
          { write_value_Variable(self->var,y);
            if (OPT_EVAL(self->arg) != Kernel.cfalse)
             res= res->addFast((OID)y);
            }
          }
        if (((self->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       { { OID  x;
          { { OID  x_some = CNULL;
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(x);
                for (START(res); NEXT(x);)
                if (belong_to(x,_oid_(self->of)) != CTRUE)
                 { x_some= x;
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
        cast_I_list1(res,self->of);
        }
      Result = _oid_(res);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// Exists is an iteration that checks a condition
// other = true => forall,  other = false => exists, other = unknown => some
// The c++ function for: self_print(self:Exists) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  self_print_Exists_Language(Exists *self)
{ GC_BIND;
  if (self->other == Kernel.ctrue)
   color_princ_string1("`BLUEforall`BLACK");
  else if (self->other == Kernel.cfalse)
   color_princ_string1("`BLUEexists`BLACK");
  else color_princ_string1("`BLUEsome`BLACK");
    if (self->set_arg == _oid_(Kernel._any))
   { princ_string("(");
    ppvariable_Variable(GC_OBJECT(Variable,self->var));
    princ_string(",");
    print_any(GC_OID(self->arg));
    princ_string(")");
    }
  else { CL_INT  g0486 = (int )(current_color);
      CL_INT  g0487 = (int )(current_bold);
      CL_INT  g0488 = g0486;
      CL_INT  g0489 = g0487;
      color(g0486,g0487);
      color_princ_string1("(");
      g0486= (int )(current_color);
      g0487= (int )(current_bold);
      color(g0488,g0489);
      ppvariable_Variable(GC_OBJECT(Variable,self->var));
      color(g0486,g0487);
      color(g0486,g0487);
      color_princ_string1(" `BLUEin `BLACK");
      g0486= (int )(current_color);
      g0487= (int )(current_bold);
      color(g0488,g0489);
      { CL_INT  _Zl = Core.pretty->index;
        set_level_void();
        printexp_any(GC_OID(self->set_arg),CFALSE);
        (Core.pretty->index = _Zl);
        }
      color(g0486,g0487);
      color(g0486,g0487);
      color_princ_string1(" | ");
      g0486= (int )(current_color);
      g0487= (int )(current_bold);
      color(g0488,g0489);
      lbreak_integer(2);
      print_any(GC_OID(self->arg));
      (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
      color(g0486,g0487);
      color(g0486,g0487);
      color_princ_string1(")");
      color(g0488,g0489);
      }
    GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Exists) [NEW_ALLOC]
OID  self_eval_Exists(Exists *self)
{ GC_BIND;
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
                      ClEnv->cHandle = loop_handle; break;}
                  }
                else if (b == Kernel.ctrue)
                 { res= Kernel.cfalse;
                  ClEnv->cHandle = loop_handle; break;}
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
                    ClEnv->cHandle = loop_handle; break;}
                }
              else if (b == Kernel.ctrue)
               { res= Kernel.cfalse;
                ClEnv->cHandle = loop_handle; break;}
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
void  self_print_Case_Language(Case *self)
{ GC_BIND;
  { CL_INT  g0492 = (int )(current_color);
    CL_INT  g0493 = (int )(current_bold);
    CL_INT  g0494 = g0492;
    CL_INT  g0495 = g0493;
    color(g0492,g0493);
    color_princ_string1("`BLUEcase `BLACK");
    g0492= (int )(current_color);
    g0493= (int )(current_bold);
    color(g0494,g0495);
    print_any(GC_OID(self->var));
    color(g0492,g0493);
    color(g0492,g0493);
    color_princ_string1(" ");
    g0492= (int )(current_color);
    g0493= (int )(current_bold);
    color(g0494,g0495);
    lbreak_integer(1);
    color(g0492,g0493);
    color(g0492,g0493);
    color_princ_string1("(");
    color(g0494,g0495);
    }
  { CL_INT  n = 1;
    CL_INT  m = self->args->length;
    (Core.pretty->index = ((CL_INT)Core.pretty->index+(CL_INT)1));
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while (((CL_INT)n <= (CL_INT)m))
      { GC_LOOP;
        { CL_INT  _Zl = Core.pretty->index;
          printexp_any(GC_OID((*(self->args))[n]),CFALSE);
          princ_string(" ");
          if ((CL_INT)buffer_length_void() > (CL_INT)((CL_INT)Core.pretty->width-(CL_INT)50))
           lbreak_integer(2);
          else set_level_void();
            print_any(GC_OID((*(self->args))[((CL_INT)n+(CL_INT)1)]));
          (Core.pretty->index = _Zl);
          if (((CL_INT)n+(CL_INT)1) != m)
           { princ_string(", ");
            lbreak_void();
            }
          else ;n= ((CL_INT)n+(CL_INT)2);
          }
        GC_UNLOOP;POP_SIGNAL;}
      }
    princ_string(")");
    (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Case) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_eval_Case(Case *self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { OID Result = 0;
    { OID  truc = GC_OID(eval_any(GC_OID(self->var)));
      ClaireBoolean * flip = CTRUE;
      OID  previous = Kernel.cfalse;
      CL_INT  n = ClEnv->trace_I;
      CL_INT  d = ClEnv->debug_I;
      if (((CL_INT)n > 0) && 
          ((CL_INT)n <= (CL_INT)ClEnv->step_I))
       { (ClEnv->trace_I = 0);
        (ClEnv->debug_I = -1);
        { CL_INT  g0496 = (int )(current_color);
          CL_INT  g0497 = (int )(current_bold);
          CL_INT  g0498 = g0496;
          CL_INT  g0499 = g0497;
          color(g0496,g0497);
          color_princ_string1("  `BLUEcase ");
          g0496= (int )(current_color);
          g0497= (int )(current_bold);
          color(g0498,g0499);
          print_any(truc);
          color(g0496,g0497);
          color(g0496,g0497);
          color_princ_string1("\n");
          color(g0498,g0499);
          }
        (ClEnv->debug_I = d);
        (ClEnv->trace_I = n);
        }
      { OID  res;
        { ClaireBoolean * g0504I;
          { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(x);
              V_C= Kernel.cfalse;
              bag *x_support;
              x_support = GC_OBJECT(list,self->args);
              for (START(x_support); NEXT(x);)
              { GC_LOOP;
                if (flip == CTRUE)
                 { flip= CFALSE;
                  GC__OID(previous = OPT_EVAL(x), 1);
                  }
                else if (belong_to(truc,previous) == CTRUE)
                 { GC__OID(previous = OPT_EVAL(x), 1);
                  { V_C = Kernel.ctrue;
                    ClEnv->cHandle = loop_handle;break;}
                  }
                else flip= CTRUE;
                  GC_UNLOOP; POP_SIGNAL;}
              }
            
            g0504I=OBJECT(ClaireBoolean,V_C);}
          
          if (g0504I == CTRUE) res = previous;
            else res = Kernel.cfalse;
          }
        if (((CL_INT)n > 0) && 
            ((CL_INT)n <= (CL_INT)ClEnv->step_I))
         { (ClEnv->trace_I = 0);
          (ClEnv->debug_I = -1);
          { CL_INT  g0500 = (int )(current_color);
            CL_INT  g0501 = (int )(current_bold);
            CL_INT  g0502 = g0500;
            CL_INT  g0503 = g0501;
            color(g0500,g0501);
            color_princ_string1("  `BLUEcase -> ");
            g0500= (int )(current_color);
            g0501= (int )(current_bold);
            color(g0502,g0503);
            print_any(res);
            color(g0500,g0501);
            color(g0500,g0501);
            color_princ_string1("\n");
            color(g0502,g0503);
            }
          (ClEnv->debug_I = d);
          (ClEnv->trace_I = n);
          }
        Result = res;
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// ------------------ WHILE  and UNTIL  -----------------------------
// the "other" while is until, where the first test is skipped
// The c++ function for: self_print(self:While) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  self_print_While_Language(While *self)
{ GC_BIND;
  { CL_INT  g0506 = (int )(current_color);
    CL_INT  g0507 = (int )(current_bold);
    CL_INT  g0508 = g0506;
    CL_INT  g0509 = g0507;
    color(g0506,g0507);
    color_princ_string1("`BLUE");
    g0506= (int )(current_color);
    g0507= (int )(current_bold);
    color(g0508,g0509);
    princ_string(((self->other == CTRUE) ?
      "until" :
      "while" ));
    color(g0506,g0507);
    color(g0506,g0507);
    color_princ_string1(" `BLACK");
    g0506= (int )(current_color);
    g0507= (int )(current_bold);
    color(g0508,g0509);
    printexp_any(GC_OID(self->test),CFALSE);
    color(g0506,g0507);
    color(g0506,g0507);
    color_princ_string1(" ");
    g0506= (int )(current_color);
    g0507= (int )(current_bold);
    color(g0508,g0509);
    lbreak_integer(2);
    color(g0506,g0507);
    color(g0508,g0509);
    print_any(GC_OID(self->arg));
    color(g0506,g0507);
    color(g0508,g0509);
    }
  (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:While) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_eval_While(While *self)
{ GC_BIND;
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
              b= CFALSE;
              eval_any(GC_OID(self->arg));
              v_while = ((b == CTRUE) ? CTRUE : ((not_any(eval_any(GC_OID(self->test))) == a) ? CTRUE : CFALSE));
              GC_UNLOOP;POP_SIGNAL;}
            }
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Core._return_error)) == CTRUE)
        { c_handle.catchIt();res = (*Kernel.arg)(GC_OID(_oid_(ClEnv->exception_I)));
          }
        else PREVIOUS_HANDLER;}
      if (((CL_INT)n > 0) && 
          ((CL_INT)n <= (CL_INT)ClEnv->step_I))
       { (ClEnv->trace_I = 0);
        (ClEnv->debug_I = -1);
        if (self->other == CTRUE)
         { CL_INT  g0510 = (int )(current_color);
          CL_INT  g0511 = (int )(current_bold);
          CL_INT  g0512 = g0510;
          CL_INT  g0513 = g0511;
          color(g0510,g0511);
          color_princ_string1("  `BLUEuntil -> ");
          g0510= (int )(current_color);
          g0511= (int )(current_bold);
          color(g0512,g0513);
          print_any(res);
          color(g0510,g0511);
          color(g0510,g0511);
          color_princ_string1("\n");
          color(g0512,g0513);
          }
        else { CL_INT  g0514 = (int )(current_color);
            CL_INT  g0515 = (int )(current_bold);
            CL_INT  g0516 = g0514;
            CL_INT  g0517 = g0515;
            color(g0514,g0515);
            color_princ_string1("  `BLUEwhile -> ");
            g0514= (int )(current_color);
            g0515= (int )(current_bold);
            color(g0516,g0517);
            print_any(res);
            color(g0514,g0515);
            color(g0514,g0515);
            color_princ_string1("\n");
            color(g0516,g0517);
            }
          (ClEnv->debug_I = d);
        (ClEnv->trace_I = n);
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
void  self_print_Handle_Language(ClaireHandle *self)
{ GC_BIND;
  { CL_INT  g0519 = (int )(current_color);
    CL_INT  g0520 = (int )(current_bold);
    CL_INT  g0521 = g0519;
    CL_INT  g0522 = g0520;
    color(g0519,g0520);
    color_princ_string1("`BLUEtry `BLACK");
    g0519= (int )(current_color);
    g0520= (int )(current_bold);
    color(g0521,g0522);
    print_any(GC_OID(self->arg));
    color(g0519,g0520);
    color(g0519,g0520);
    color_princ_string1(" ");
    g0519= (int )(current_color);
    g0520= (int )(current_bold);
    color(g0521,g0522);
    lbreak_integer(0);
    color(g0519,g0520);
    color(g0519,g0520);
    color_princ_string1("`BLUEcatch `BLACK");
    g0519= (int )(current_color);
    g0520= (int )(current_bold);
    color(g0521,g0522);
    print_any(GC_OID(self->test));
    color(g0519,g0520);
    color(g0519,g0520);
    color_princ_string1(" ");
    g0519= (int )(current_color);
    g0520= (int )(current_bold);
    color(g0521,g0522);
    print_any(GC_OID(self->other));
    color(g0519,g0520);
    color(g0521,g0522);
    }
  (Core.pretty->index = ((CL_INT)Core.pretty->index-(CL_INT)2));
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Handle) [NEW_ALLOC+RETURN_ARG]
OID  self_eval_Handle(ClaireHandle *self)
{ GC_BIND;
  { OID Result = 0;
    { OID  x = GC_OID(OPT_EVAL(self->test));
      { ClaireHandler c_handle = ClaireHandler();
        if ERROR_IN 
        { Result = OPT_EVAL(self->arg);
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),x) == CTRUE)
        { c_handle.catchIt();if (INHERIT(ClEnv->exception_I->isa,Core._return_error))
           { OID  V_CL0523;close_exception(ClEnv->exception_I);
            
            Result=_void_(V_CL0523);}
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
//<sb> v3.3.35
// The c++ function for: self_print(self:Construct) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  self_print_Construct_Language(Construct *self)
{ GC_BIND;
  { CL_INT  _Zl = Core.pretty->index;
    if (INHERIT(self->isa,Language._List))
     princ_string("list");
    else if (INHERIT(self->isa,Language._Set))
     princ_string("set");
    else if (INHERIT(self->isa,Language._Tuple))
     princ_string("tuple");
    else if (INHERIT(self->isa,Language._Printf))
     color_princ_string1("`BLUEprintf`BLACK");
    else if (INHERIT(self->isa,Language._Scanf))
     color_princ_string1("`BLUEscanf`BLACK");
    else if (INHERIT(self->isa,Language._Error))
     princ_string("error");
    else if (INHERIT(self->isa,Language._Trace))
     color_princ_string1("`BLUEtrace`BLACK");
    else if (INHERIT(self->isa,Language._Assert))
     color_princ_string1("`BLUEassert`BLACK");
    else if (INHERIT(self->isa,Language._Branch))
     color_princ_string1("`BLUEbranch`BLACK");
    else princ_string(string_I_symbol(self->isa->name));
      if ((INHERIT(self->isa,Language._List)) || 
        (INHERIT(self->isa,Language._Set)))
     { OID  _Zt = GC_OID(get_property(Kernel.of,self));
      if (_Zt != CNULL)
       { if (equal(_Zt,_oid_(Kernel.emptySet)) != CTRUE)
         { princ_string("<");
          print_any(_Zt);
          princ_string(">");
          }
        }
      else ;}
    princ_string("(");
    set_level_void();
    printbox_bag2(GC_OBJECT(list,self->args));
    princ_string(")");
    (Core.pretty->index = _Zl);
    }
  GC_UNBIND; POP_SIGNAL;}


// constructors: how to create a list, a set, a tuple or an array
// note that the constructor is typed
// The c++ function for: self_eval(self:List) [NEW_ALLOC+RETURN_ARG]
OID  self_eval_List(List *self)
{ GC_BIND;
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
                 { x_some= x;
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
OID  self_eval_Set(Set *self)
{ GC_BIND;
  { OID Result = 0;
    { set * s;
      { { list * g0524UU;
          { { CL_INT loop_handle = ClEnv->cHandle;
              bag *v_list; OID v_val;
              OID x; CL_INT CLcount;
              v_list = self->args;
               g0524UU = v_list->clone();
              for (CLcount= 1; CLcount <= v_list->length; CLcount++)
              { x = (*(v_list))[CLcount];
                v_val = OPT_EVAL(x);
                
                (*((list *) g0524UU))[CLcount] = v_val;}
              }
            GC_OBJECT(list,g0524UU);}
          s = set_I_bag(g0524UU);
          }
        GC_OBJECT(set,s);}
      if (((self->of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       { { OID  x;
          { { OID  x_some = CNULL;
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(x);
                for (START(s); NEXT(x);)
                if (belong_to(x,_oid_(self->of)) != CTRUE)
                 { x_some= x;
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
OID  self_eval_Tuple(Tuple *self)
{ GC_BIND;
  { OID Result = 0;
    { tuple * V_CL0525;{ list * g0526UU;
        { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID x; CL_INT CLcount;
            v_list = self->args;
             g0526UU = v_list->clone();
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { x = (*(v_list))[CLcount];
              v_val = OPT_EVAL(x);
              
              (*((list *) g0526UU))[CLcount] = v_val;}
            }
          GC_OBJECT(list,g0526UU);}
        V_CL0525 = tuple_I_list(g0526UU);
        }
      
      Result=_oid_(V_CL0525);}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// v3.2.16 - introduce a nicer way to create an array
// The c++ function for: self_eval(self:Array) [NEW_ALLOC]
OID  self_eval_Array2(Array *self)
{ GC_BIND;
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
                 { x_some= x;
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
OID  self_eval_Macro2(Macro *self)
{ GC_BIND;
  { OID Result = 0;
    Result = eval_any(GC_OID((*Language.macroexpand)(_oid_(self))));
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// error produces an exception of type general_error
// The c++ function for: self_eval(self:Error) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  self_eval_Error(Error *self)
{ GC_BIND;
  if ((boolean_I_any(_oid_(self->args)) != CTRUE) || 
      (equal(_oid_(Kernel._string),_oid_(OWNER((*(self->args))[1]))) != CTRUE))
   close_exception(((general_error *) (*Core._general_error)(_string_("Syntax error: ~S"),
    _oid_(list::alloc(1,_oid_(self))))));
  { general_error * x = GC_OBJECT(general_error,((general_error *) new_object_class(Core._general_error)));
    (x->cause = car_list(self->args));
    { general_error * g0527 = x; 
      OID  g0528;
      { list * V_CL0529;{ CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID x; CL_INT CLcount;
          v_list = GC_OBJECT(list,cdr_list(GC_OBJECT(list,self->args)));
           V_CL0529 = v_list->clone();
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { x = (*(v_list))[CLcount];
            v_val = OPT_EVAL(x);
            
            (*((list *) V_CL0529))[CLcount] = v_val;}
          }
        
        g0528=_oid_(V_CL0529);}
      (g0527->arg = g0528);}
    close_exception(x);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_eval(self:Scanf) [NEW_ALLOC]
OID  self_eval_Scanf1(Scanf *self)
{ POP_SIGNAL; return ((*Language.scanfexpand)(_oid_(self)));}


// this is the basic tool for printing in CLAIRE. A complex statement
// is macroexpanded into basic printing instructions
//
// The c++ function for: self_eval(self:Printf) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_eval_Printf(Printf *self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { OID Result = 0;
    { list * larg = GC_OBJECT(list,self->args);
      ClaireBoolean * onport_ask = inherit_ask_class(owner_any(OPT_EVAL((*(larg))[1])),Kernel._port);
      OID  s;
      if (onport_ask == CTRUE)
       s = (*(larg))[2];
      else s = (*(larg))[1];
        if (equal(_oid_(Kernel._string),_oid_(OWNER(s))) != CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("[102] the first argument in ~S must be a string or a port"),
        _oid_(list::alloc(1,_oid_(self))))));
      else { CL_INT  n = find_string2(string_v(s),"~");
          CL_INT  idx = 1;
          PortObject * p = use_as_output_port(((onport_ask == CTRUE) ?
            OBJECT(PortObject,OPT_EVAL((*(larg))[1])) :
            ClEnv->cout ));
          CL_INT  nl = ((onport_ask == CTRUE) ?
            3 :
            2 );
          CL_INT  len = (*Kernel.length)(s);
          CL_INT  col = (int )(current_color);
          CL_INT  bold = (int )(current_bold);
          CL_INT  ccol = col;
          CL_INT  cbold = bold;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((0 < (CL_INT)n) && 
                ((CL_INT)n < (CL_INT)len)))
            { GC_LOOP;
              { OID  m = GC_OID((*Kernel.nth)(s,
                  ((OID)((CL_INT)n+(CL_INT)1))));
                if ((CL_INT)n > 1)
                 { color(ccol,cbold);
                  color_princ_string2(string_v(s),idx,((CL_INT)n-(CL_INT)1));
                  {ccol = current_color; cbold = current_bold;};
                  }
                if (_oid_(_char_(((unsigned char)65 /* 'A' */))) == m)
                 { color(col,bold);
                  (*Kernel.princ)(GC_OID(OPT_EVAL((*(larg))[nl])));
                  color(ccol,cbold);
                  }
                else if (_oid_(_char_(((unsigned char)83 /* 'S' */))) == m)
                 { color(col,bold);
                  print_any(GC_OID(OPT_EVAL((*(larg))[nl])));
                  color(ccol,cbold);
                  }
                else if (_oid_(_char_(((unsigned char)73 /* 'I' */))) == m)
                 { color(col,bold);
                  OPT_EVAL((*(larg))[nl]);
                  color(ccol,cbold);
                  }
                if (m != _oid_(_char_(((unsigned char)37 /* '%' */))))
                 ++nl;
                idx= ((CL_INT)n+(CL_INT)2);
                n= find_string(string_v(s),"~",idx);
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
// The c++ function for: self_eval(self:Trace) [NEW_ALLOC+SLOT_UPDATE]
OID  self_eval_Trace(Trace *self)
{ GC_BIND;
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
      if ((CL_INT)a->length > 1)
       a2 = (*(a))[2];
      else a2 = Kernel.cfalse;
        if ((Kernel._string == OWNER(a2)) && 
          ((INHERIT(OWNER(i),Kernel._integer)) && (CTRUE == CTRUE)))
       mtformat_module1(ClEnv->module_I,string_v(a2),i,skip_list(l,2));
      Result = _oid_(Kernel.emptySet);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// assert is refined in trace.la
//
// The c++ function for: self_eval(self:Assert) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  self_eval_Assert(Assert *self)
{ GC_BIND;
  { OID Result = 0;
    { list * a = GC_OBJECT(list,self->args);
      if (((CL_INT)a->length > 0) && 
          ((get_property(Kernel.ctrace,ClEnv) != CNULL) && 
            (boolean_I_any(OPT_EVAL((*(a))[1])) != CTRUE)))
       { PortObject * p = use_as_output_port(ClEnv->ctrace);
        print_any(GC_OID(_string_(self->external)));
        princ_string(",line=");
        princ_integer(self->index);
        princ_string(": (ASSERT) ");
        print_any((*(a))[1]);
        princ_string("\n");
        use_as_output_port(p);
        if (0 <= (CL_INT)ClEnv->debug_I)
         close_exception(((general_error *) (*Core._general_error)(_string_("Assertion Violation"),
          _oid_(Kernel.nil))));
        Result = _oid_(Kernel.emptySet);
        }
      else Result = Kernel.cfalse;
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: self_eval(self:Branch) [NEW_ALLOC]
OID  self_eval_Branch(Branch *self)
{ GC_BIND;
  if (self->args->length != 1)
   close_exception(((general_error *) (*Core._general_error)(_string_("[104] Syntax error with ~S (one arg. expected)"),
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

