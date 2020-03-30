/***** CLAIRE Compilation of file ./meta/read.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:41 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>

//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| reader.cl                                                   |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+
// ---------------------------------------------------------------------
// Contents:
//   Part 1: the reader object
//   Part 2: lexical analysis
//   Part 3: reading structures	
//   Part 4: Variable Handling
// ---------------------------------------------------------------------
// **********************************************************************
// *   Part 1: The reader object                                        *
// **********************************************************************
// global definitions
// *arrow*:boolean :: false
// here we define the basic keywords
//<sb> v3.3.33 ffor
// The c++ function for: keyword?(x:any) [0]
ClaireBoolean * keyword_ask_any(OID x)
{ POP_SIGNAL; return (inherit_ask_class(OWNER(x),Reader._reserved_keyword));}


//<sb> v3.3.33 ffor
//<sb> v3.3.35
// the meta_class of the reader --------------------------------------
// The key values are placed in indexed so that they can be changed (eof ...).
// The slot *internal* is used to give addresses to lexical variables.
// The function next reads a character and places it in the slot first.
//
//<sb> wcl
// The c++ function for: get_lines(r:meta_reader) [RETURN_ARG]
int  get_lines_meta_reader(meta_reader *r)
{ { CL_INT Result = 0;
    Result = ((INHERIT(r->fromp->isa,Core._line_counter)) ?
      ((CL_INT)1+(CL_INT)CLREAD(line_counter,r->fromp,read_lines)) :
      0 );
    POP_SIGNAL; return (Result);}
  }


// closing brace as a CLAIRE entity
// The c++ function for: next(r:meta_reader) [SLOT_UPDATE]
int  next_meta_reader(meta_reader *r)
{ { CL_INT Result = 0;
    { CL_INT  c = (int )(((CL_INT) r->fromp->getNext()));
      (r->nb_line = get_lines_meta_reader(r));
      Result = c;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: firstc(r:meta_reader) [0]
int  firstc_meta_reader(meta_reader *r)
{ POP_SIGNAL; return ((int )(r->fromp->firstc));}


// The c++ function for: stop?(n:integer) [0]
OID  stop_ask_integer(CL_INT n)
{ POP_SIGNAL; return (_oid_(((n == 44) ? CTRUE : ((n == 41) ? CTRUE : ((n == 93) ? CTRUE : ((n == 125) ? CTRUE : CFALSE))))));}


// sugar in file
// this is used to keep comments when translating CLAIRE to another language
//matchWcl? :: property(open = 3) //<sb> wcl
//readWcl :: property(open = 3) //<sb> wcl
// read the next unit (definition, block or expression)
//
// The c++ function for: nextunit(r:meta_reader) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  nextunit_meta_reader(meta_reader *r)
{ GC_BIND;
  { OID Result = 0;
    { OID  n = skipc_meta_reader(r);
      if (n == ((OID)r->eof))
       { next_meta_reader(r);
        Result = Core._eof->value;
        }
      else if (wcl_start_ask_meta_reader1(r,n) == CTRUE)
       Result = read_top_wcl_meta_reader1(r);
      else if (n == ((OID)91))
       { OID  z = GC_OID(nexte_meta_reader(cnext_meta_reader(r)));
        Result = nextdefinition_meta_reader(r,z,GC_OID(nexte_meta_reader(r)),CTRUE);
        }
      else if (n == ((OID)40))
       { if (r->toplevel == CTRUE)
         Result = nexts_meta_reader(r,Reader.none);
        else Result = readblock_meta_reader(r,GC_OID(nexte_meta_reader(cnext_meta_reader(r))),41);
          }
      else if (n == ((OID)96))
       { Quote * _CL_obj = ((Quote *) GC_OBJECT(Quote,new_object_class(Language._Quote)));
        (_CL_obj->arg = nextunit_meta_reader(cnext_meta_reader(r)));
        add_I_property(Kernel.instances,Language._Quote,11,_oid_(_CL_obj));
        Result = _oid_(_CL_obj);
        }
      else if (n == ((OID)59))
       { { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((firstc_meta_reader(r) != r->eof) && 
              (firstc_meta_reader(r) != 10)))
          { next_meta_reader(r);
            POP_SIGNAL;}
          }
        if (firstc_meta_reader(r) == r->eof)
         Result = Core._eof->value;
        else { next_meta_reader(r);
            Result = nextunit_meta_reader(r);
            }
          }
      else { OID  x;
          { if (r->toplevel == CTRUE)
             x = nexts_meta_reader(r,Reader.none);
            else x = nextexp_meta_reader(r,CTRUE);
              GC_OID(x);}
          if ((r->toplevel == CTRUE) && 
              ((INHERIT(OWNER(x),Language._Assign)) && (INHERIT(OWNER(OBJECT(Assign,x)->var),Language._Vardef))))
           { Defobj * _CL_obj = ((Defobj *) GC_OBJECT(Defobj,new_object_class(Language._Defobj)));
            (_CL_obj->ident = OBJECT(Variable,(*Language.var)(x))->pname);
            (_CL_obj->arg = Core._global_variable);
            { Definition * g0612 = _CL_obj; 
              list * g0613;
              { OID v_bag;
                GC_ANY(g0613= list::empty(Kernel.emptySet));
                { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (_CL_obj->selector = Kernel._equal);
                    (_CL_obj->args = list::alloc(2,_oid_(Kernel.range),GC_OID(_oid_(extract_type_any(GC_OID((*Kernel.range)(GC_OID((*Language.var)(x)))))))));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                    v_bag = _oid_(_CL_obj);
                    }
                  GC_OID(v_bag);}
                ((list *) g0613)->addFast((OID)v_bag);
                { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    (_CL_obj->selector = Kernel._equal);
                    (_CL_obj->args = list::alloc(2,_oid_(Kernel.value),GC_OID((*Kernel.arg)(x))));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                    v_bag = _oid_(_CL_obj);
                    }
                  GC_OID(v_bag);}
                ((list *) g0613)->addFast((OID)v_bag);}
              (g0612->args = g0613);}
            add_I_property(Kernel.instances,Language._Defobj,11,_oid_(_CL_obj));
            Result = _oid_(_CL_obj);
            }
          else if (Kernel._string == OWNER(x))
           Result = x;
          else { ClaireBoolean * g0614I;
            if (INHERIT(OWNER(x),Language._Call))
             { ClaireBoolean *v_and;
              { v_and = contain_ask_set(r->s_properties,_oid_(OBJECT(Call,x)->selector));
                if (v_and == CFALSE) g0614I =CFALSE; 
                else { { OID  g0615UU;
                    { CL_INT loop_handle = ClEnv->cHandle;
                      OID gc_local;
                      ITERATE(y);
                      g0615UU= Kernel.cfalse;
                      bag *y_support;
                      y_support = GC_OBJECT(list,OBJECT(Call,x)->args);
                      for (START(y_support); NEXT(y);)
                      if (not_any(_oid_(inherit_ask_class(OWNER(y),Language._Vardef))) != CTRUE)
                       { g0615UU = Kernel.ctrue;
                        ClEnv->cHandle = loop_handle;break;}
                      }
                    v_and = not_any(g0615UU);
                    }
                  if (v_and == CFALSE) g0614I =CFALSE; 
                  else g0614I = CTRUE;}
                }
              }
            else g0614I = CFALSE;
              
            if (g0614I == CTRUE) { Call * z = OBJECT(Call,x);
                OID  a = GC_OID((*(z->args))[1]);
                if ((z->selector == Kernel.begin) && 
                    (INHERIT(OWNER(a),Kernel._unbound_symbol)))
                 ((*(GC_OBJECT(list,z->args)))[1]=_string_(string_I_symbol(extract_symbol_any(a))));
                if ((z->selector == Kernel.end) && 
                    (INHERIT(OWNER(a),Kernel._module)))
                 ((*(GC_OBJECT(list,z->args)))[1]=_oid_(claire.it));
                Result = x;
                }
              else if (((r->toplevel == CTRUE) ? CTRUE : ((INHERIT(OWNER(x),Language._Assert)) ? CTRUE : CFALSE)) != CTRUE)
             Result = nextdefinition_meta_reader(r,x,GC_OID(nexte_meta_reader(r)),CFALSE);
            else Result = x;
              }
          }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// read the next statement & stops at the keyword e or at a delimiter
// the keyword has been read but not the delimiter, so we know which case
// by testing stop?(first(r))
// Note: it actually reads a fragment
//
// The c++ function for: nexts(r:meta_reader,e:keyword) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  nexts_meta_reader(meta_reader *r,keyword *e)
{ GC_BIND;
  { OID Result = 0;
    { OID  n = skipc_meta_reader(r);
      if (n == ((OID)r->eof))
       { next_meta_reader(r);
        Result = Core._eof->value;
        }
      else if (n == ((OID)91))
       { OID  z = GC_OID(nexte_meta_reader(cnext_meta_reader(r)));
        Result = nextdefinition_meta_reader(r,z,GC_OID(nexte_meta_reader(r)),CTRUE);
        }
      else if (e == Reader.None)
       Result = nexte_meta_reader(r);
      else { OID  x = GC_OID(nexte_meta_reader(r));
          if (keyword_ask_any(x) == CTRUE)
           Result = nextstruct_meta_reader(r,OBJECT(keyword,x),e);
          else if ((e == Reader.none) && 
              ((INHERIT(OWNER(x),Language._Call)) && (contain_ask_set(r->s_properties,_oid_(OBJECT(Call,x)->selector)) == CTRUE)))
           Result = x;
          else if ((r->toplevel == CTRUE) && 
              (firstc_meta_reader(r) == 10))
           { if ((OBJECT(ClaireBoolean,Reader.ALTERNATE_COMMAND_ask->value)) == CTRUE)
             { char * start;
              if (INHERIT(OWNER(x),Kernel._unbound_symbol))
               start = OBJECT(unbound_symbol,x)->name->name;
              else start = ((INHERIT(OWNER(x),Kernel._thing)) ?
                OBJECT(thing,x)->name->name :
                ((INHERIT(OWNER(x),Kernel._class)) ?
                  OBJECT(ClaireClass,x)->name->name :
                  ((INHERIT(OWNER(x),Kernel._symbol)) ?
                    OBJECT(symbol,x)->name :
                    ((INHERIT(OWNER(x),Language._Variable)) ?
                      OBJECT(Variable,x)->pname->name :
                      "" ) ) ) );
              OID  y;
              { if ((CL_INT)LENGTH_STRING(start) > 0)
                 y = (*Reader.read_alternate_command)(_oid_(r),
                  _string_(start));
                else y = Kernel.cfalse;
                  GC_OID(y);}
              if (boolean_I_any(y) == CTRUE)
               Result = y;
              else Result = loopexp_meta_reader(r,x,e,CFALSE);
                }
            else Result = loopexp_meta_reader(r,x,e,CFALSE);
              }
          else if (wcl_start_ask_meta_reader1(r,skipc_meta_reader(r)) == CTRUE)
           { unget_port2(GC_OBJECT(PortObject,r->fromp),_char_(((unsigned char)62 /* '>' */)));
            Result = x;
            }
          else if ((r->toplevel == CTRUE) && 
              ((OBJECT(ClaireBoolean,Reader.ALTERNATE_COMMAND_ask->value)) == CTRUE))
           { char * start;
            if (INHERIT(OWNER(x),Kernel._unbound_symbol))
             start = OBJECT(unbound_symbol,x)->name->name;
            else start = ((INHERIT(OWNER(x),Kernel._thing)) ?
              OBJECT(thing,x)->name->name :
              ((INHERIT(OWNER(x),Kernel._class)) ?
                OBJECT(ClaireClass,x)->name->name :
                ((INHERIT(OWNER(x),Kernel._symbol)) ?
                  OBJECT(symbol,x)->name :
                  ((INHERIT(OWNER(x),Language._Variable)) ?
                    OBJECT(Variable,x)->pname->name :
                    "" ) ) ) );
            OID  y;
            { if ((CL_INT)LENGTH_STRING(start) > 0)
               y = (*Reader.read_alternate_command)(_oid_(r),
                _string_(start));
              else y = Kernel.cfalse;
                GC_OID(y);}
            if (boolean_I_any(y) == CTRUE)
             Result = y;
            else Result = loopexp_meta_reader(r,x,e,CFALSE);
              }
          else Result = loopexp_meta_reader(r,x,e,CFALSE);
            }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: leaf_wcl_intruction?(self:any) [0]
ClaireBoolean * leaf_wcl_intruction_ask_any1(OID self)
{ { ClaireBoolean *Result ;
    if (INHERIT(OWNER(self),Language._Instruction))
     { if (INHERIT(OBJECT(ClaireObject,self)->isa,Language._Construct))
       Result = leaf_wcl_intruction_ask_any1(last_list(OBJECT(Construct,self)->args));
      else if (INHERIT(OBJECT(ClaireObject,self)->isa,Language._Definition))
       Result = CFALSE;
      else if (INHERIT(OBJECT(ClaireObject,self)->isa,Language._Call_wcl))
       Result = CFALSE;
      else if (INHERIT(OBJECT(ClaireObject,self)->isa,Language._Princ_wcl))
       Result = CTRUE;
      else if (INHERIT(OBJECT(ClaireObject,self)->isa,Language._Call_method))
       Result = leaf_wcl_intruction_ask_any1(last_list(OBJECT(Call_method,self)->args));
      else if (INHERIT(OBJECT(ClaireObject,self)->isa,Language._Call_slot))
       Result = leaf_wcl_intruction_ask_any1(OBJECT(Call_slot,self)->arg);
      else if (INHERIT(OBJECT(ClaireObject,self)->isa,Language._Call_table))
       Result = leaf_wcl_intruction_ask_any1(OBJECT(Call_table,self)->arg);
      else if (INHERIT(OBJECT(ClaireObject,self)->isa,Language._Call_array))
       Result = leaf_wcl_intruction_ask_any1(OBJECT(Call_array,self)->arg);
      else if (INHERIT(OBJECT(ClaireObject,self)->isa,Language._Update))
       Result = leaf_wcl_intruction_ask_any1(OBJECT(Update,self)->value);
      else if (INHERIT(OBJECT(ClaireObject,self)->isa,Language._Call))
       Result = leaf_wcl_intruction_ask_any1(_oid_(OBJECT(Call,self)->args));
      else if (INHERIT(OBJECT(ClaireObject,self)->isa,Language._If))
       { Result = ((boolean_I_any(OBJECT(If,self)->other) == CTRUE) ?
          leaf_wcl_intruction_ask_any1(OBJECT(If,self)->other) :
          leaf_wcl_intruction_ask_any1(OBJECT(If,self)->arg) );
        }
      else if (INHERIT(OBJECT(ClaireObject,self)->isa,Language._Do))
       { Result = ((OBJECT(Do,self)->args->length != 0) ?
          ((leaf_wcl_intruction_ask_any1(last_list(OBJECT(Do,self)->args)) == CTRUE) ? CTRUE : ((((CL_INT)OBJECT(Do,self)->args->length > 1) && 
              ((last_list(OBJECT(Do,self)->args) == _oid_(Reader.none)) && 
                ((INHERIT(owner_any((*(OBJECT(Do,self)->args))[((CL_INT)OBJECT(Do,self)->args->length-(CL_INT)1)]),Language._Princ_wcl)) || 
                    (INHERIT(owner_any((*(OBJECT(Do,self)->args))[((CL_INT)OBJECT(Do,self)->args->length-(CL_INT)1)]),Language._Call_wcl))))) ? CTRUE : CFALSE)) :
          CFALSE );
        }
      else if (INHERIT(OBJECT(ClaireObject,self)->isa,Language._Iteration))
       Result = leaf_wcl_intruction_ask_any1(OBJECT(Iteration,self)->arg);
      else if (INHERIT(OBJECT(ClaireObject,self)->isa,Language._Ffor))
       Result = leaf_wcl_intruction_ask_any1(OBJECT(iClaire_Ffor,self)->arg);
      else Result = ((INHERIT(OBJECT(ClaireObject,self)->isa,Language._Let)) ?
        leaf_wcl_intruction_ask_any1(OBJECT(Let,self)->arg) :
        ((INHERIT(OBJECT(ClaireObject,self)->isa,Language._Case)) ?
          leaf_wcl_intruction_ask_any1(_oid_(OBJECT(Case,self)->args)) :
          ((INHERIT(OBJECT(ClaireObject,self)->isa,Language._While)) ?
            leaf_wcl_intruction_ask_any1(OBJECT(While,self)->arg) :
            ((INHERIT(OBJECT(ClaireObject,self)->isa,Language._Handle)) ?
              leaf_wcl_intruction_ask_any1(OBJECT(ClaireHandle,self)->other) :
              CFALSE ) ) ) );
      }
    else Result = CFALSE;
      POP_SIGNAL; return (Result);}
  }


// The c++ function for: head_wcl_intruction?(self:any) [0]
ClaireBoolean * head_wcl_intruction_ask_any1(OID self)
{ { ClaireBoolean *Result ;
    Result = ((INHERIT(OWNER(self),Language._Instruction)) ?
      ((INHERIT(OBJECT(ClaireObject,self)->isa,Language._Princ_wcl)) ?
        CTRUE :
        ((INHERIT(OBJECT(ClaireObject,self)->isa,Language._Do)) ?
          ((OBJECT(Do,self)->args->length != 0) ?
            head_wcl_intruction_ask_any1((*(OBJECT(Do,self)->args))[1]) :
            CFALSE ) :
          CFALSE ) ) :
      CFALSE );
    POP_SIGNAL; return (Result);}
  }


// loops until the right expression is built (ends with e ',', '}' or ')')
//
// The c++ function for: loopexp(r:meta_reader,x:any,e:keyword,loop:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  loopexp_meta_reader(meta_reader *r,OID x,keyword *e,ClaireBoolean *loop)
{ if ((r->toplevel == CTRUE) && 
      ((e == Reader.none) && 
        (findeol_meta_reader(r) == CTRUE))) 
  { { OID Result = 0;
      Result = x;
      return (Result);}
     }
  else{ GC_BIND;
    { OID Result = 0;
      if (x == _oid_(Reader._ask))
       { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
        (_CL_obj->selector = Reader.inspect_toplevel);
        (_CL_obj->args = list::alloc(1,GC_OID(nexte_meta_reader(r))));
        add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
        Result = _oid_(_CL_obj);
        }
      else if (skipc_meta_reader(r) == ((OID)58))
       { OID  y = GC_OID(nexte_meta_reader(cnext_meta_reader(r)));
        if (y == _oid_(Kernel._equal))
         Result = loopexp_meta_reader(r,GC_OID(combine_any(x,_oid_(Reader.L__equal),GC_OID(nexte_meta_reader(r)))),e,CTRUE);
        else if (y == _oid_(Reader.L_))
         Result = nextinst_meta_reader(r,x);
        else if (operation_ask_any(y) == CTRUE)
         Result = extended_operator_property1(OBJECT(property,y),x,GC_OID(loopexp_meta_reader(r,GC_OID(nexte_meta_reader(r)),e,CFALSE)));
        else if (INHERIT(OWNER(x),Language._Call))
         { OID  w = GC_OID(nexte_meta_reader(r));
          if (w == _oid_(Reader._equal_sup))
           (r->last_arrow = CTRUE);
          else if (((equal(w,Reader.arrow->value) == CTRUE) ? CTRUE : ((w == _oid_(Reader.L__equal)) ? CTRUE : CFALSE)) != CTRUE)
           Serror_integer1(149,"Wrong keyword (~S) after ~S",list::alloc(2,w,y));
          Result = nextmethod_meta_reader(r,
            x,
            y,
            equal(w,_oid_(Reader.L__equal)),
            CFALSE,
            equal(w,_oid_(Reader._equal_sup)));
          }
        else Serror_integer1(150,"Illegal use of :~S after ~S",list::alloc(2,y,x));
          }
      else if (wcl_start_ask_meta_reader1(r,firstc_meta_reader(r)) == CTRUE)
       { unget_port2(GC_OBJECT(PortObject,r->fromp),_char_(((unsigned char)62 /* '>' */)));
        Result = x;
        }
      else { OID  y = GC_OID(nexte_meta_reader(r));
          if ((y == _oid_(e)) || 
              ((y == _oid_(Reader._equal_sup)) && 
                  (_oid_(e) == Reader.arrow->value)))
           { if (y != _oid_(e))
             (r->last_arrow = CTRUE);
            if (boolean_I_any(stop_ask_integer(firstc_meta_reader(r))) == CTRUE)
             Serror_integer1(151,"~S not allowed after ~S\n",list::alloc(2,_oid_(char_I_integer(firstc_meta_reader(r))),_oid_(e)));
            else Result = x;
              }
          else if ((equal(y,Reader.triangle->value) == CTRUE) || 
              ((equal(y,Reader.arrow->value) == CTRUE) || 
                ((y == _oid_(Reader.L_)) || 
                  ((y == _oid_(Reader.L_L_)) || 
                    (y == _oid_(Reader._equal_sup))))))
           Result = nextdefinition_meta_reader(r,x,y,CFALSE);
          else if ((INHERIT(OWNER(y),Reader._delimiter)) && 
              (boolean_I_any(stop_ask_integer(firstc_meta_reader(r))) == CTRUE))
           Result = x;
          else if (operation_ask_any(y) == CTRUE)
           { if (loop == CTRUE)
             Result = loopexp_meta_reader(r,GC_OID(combine_any(x,y,GC_OID(nexte_meta_reader(r)))),e,CTRUE);
            else Result = loopexp_meta_reader(r,GC_OID(combine_I_any(x,y,GC_OID(nexte_meta_reader(r)))),e,CTRUE);
              }
          else { if (should_trace_ask_module1(Reader.it,3) == CTRUE)
               mtformat_module1(Reader.it,"test leaf x=~S, y=~S \n",3,list::alloc(2,x,y));
              else ;if (y == _oid_(Reader._ask))
               Result = x;
              else if (leaf_wcl_intruction_ask_any1(x) == CTRUE)
               Result = Do_I_any(x,y);
              else if (head_wcl_intruction_ask_any1(y) == CTRUE)
               Result = Do_I_any(x,y);
              else Serror_integer1(152,"Separation missing between ~S \nand ~S [~S?]",list::alloc(3,x,
                  y,
                  _oid_(e)));
                }
            }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  }


// this is the special form for x :op y - new in v3.3.32
// The c++ function for: extended_operator(p:property,x:any,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  extended_operator_property1(property *p,OID x,OID y)
{ GC_BIND;
  { OID Result = 0;
    if (INHERIT(OWNER(x),Language._Call))
     { OID  r;
      { if (OBJECT(Call,x)->selector == Kernel.nth)
         r = (*(OBJECT(Call,x)->args))[2];
        else r = (*(OBJECT(Call,x)->args))[1];
          GC_OID(r);}
      Variable * v;
      { { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
          (_CL_obj->pname = gensym_void());
          add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
          v = _CL_obj;
          }
        GC_OBJECT(Variable,v);}
      list * _Zb = GC_OBJECT(list,bind_I_meta_reader(Reader.reader,v));
      Call * x2;
      if (OBJECT(Call,x)->selector == Kernel.nth)
       { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
        (_CL_obj->selector = Kernel.nth);
        (_CL_obj->args = list::alloc(2,GC_OID((*(OBJECT(Call,x)->args))[1]),_oid_(v)));
        add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
        x2 = _CL_obj;
        }
      else { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          (_CL_obj->selector = OBJECT(Call,x)->selector);
          (_CL_obj->args = list::alloc(1,_oid_(v)));
          add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
          x2 = _CL_obj;
          }
        OID  res;
      { if (INHERIT(OWNER(r),Language._Call))
         { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
          (_CL_obj->var = v);
          (_CL_obj->value = r);
          (_CL_obj->arg = combine_any(_oid_(x2),_oid_(Reader.L__equal),GC_OID(combine_any(_oid_(x2),_oid_(p),y))));
          add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
          res = _oid_(_CL_obj);
          }
        else res = combine_any(x,_oid_(Reader.L__equal),GC_OID(combine_any(x,_oid_(p),y)));
          GC_OID(res);}
      unbind_I_meta_reader(Reader.reader,_Zb);
      Result = res;
      }
    else Result = combine_any(x,_oid_(Reader.L__equal),GC_OID(combine_any(x,_oid_(p),y)));
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// reading the next compact expression - comments are ignored but they can
// be attached to the last read expression
//
// The c++ function for: nexte(r:meta_reader) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  nexte_meta_reader(meta_reader *r)
{ GC_BIND;
  { OID Result = 0;
    { OID  x = GC_OID(nextexp_meta_reader(r,CFALSE));
      if (INHERIT(OWNER(x),Language._Instruction))
       (r->last_form = x);
      Result = x;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// v3.3
//<sb> fill the cache of symbol location
// The c++ function for: mClaire/read_ident(r:meta_reader) [NEW_ALLOC]
OID  read_ident_meta_reader1(meta_reader *r)
{ GC_BIND;
  { OID Result = 0;
    { OID  x = GC_OID(read_ident_port(r->fromp));
      if ((firstc_meta_reader(r) != 58) && 
          (INHERIT(get_device_port1(r->fromp)->isa,Core._disk_file)))
       { if ((((INHERIT(OWNER(x),Kernel._symbol)) || 
                (INHERIT(OWNER(x),Kernel._unbound_symbol))) || 
              (INHERIT(OWNER(x),Kernel._property))) || 
            (INHERIT(OWNER(x),Kernel._class)))
         { tuple * g0616 = get_location_port1(r->fromp);
          char * f = GC_STRING(string_v((*(g0616))[1]));
          CL_INT  l = (*(g0616))[2];
          CL_INT  o = (*(g0616))[3];
          char * s = extract_symbol_any(x)->name;
          list * loc = list::alloc(Kernel._any,1,_string_(s));
          loc->addFast((OID)_string_(f));
          loc->addFast((OID)((OID)l));
          loc->addFast((OID)((OID)((CL_INT)((CL_INT)o-(CL_INT)2)-(CL_INT)LENGTH_STRING(s))));
          loc->addFast((OID)((OID)LENGTH_STRING(s)));
          GC_OBJECT(list,OBJECT(list,Reader.IDENTS->value))->addFast((OID)_oid_(loc));
          }
        }
      Result = x;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// reading the next compact expression/ same
//
// The c++ function for: nextexp(r:meta_reader,str:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  nextexp_meta_reader(meta_reader *r,ClaireBoolean *str)
{ GC_RESERVE(10);  // v3.0.55 optim !
  { OID Result = 0;
    { CL_INT  n = skipc_meta_reader(r);
      if (n == 41)
       Result = r->paren;
      else if (n == 125)
       Result = r->curly;
      else if (n == 93)
       Result = r->bracket;
      else if (n == 124)
       { next_meta_reader(r);
        Result = Reader.OR->value;
        }
      else if (n == 44)
       Result = r->comma;
      else if (n == r->eof)
       Serror_integer1(153,"Eof inside an expression",Kernel.nil);
      else if (n == 59)
       { { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((firstc_meta_reader(r) != r->eof) && 
              (firstc_meta_reader(r) != 10)))
          { next_meta_reader(r);
            POP_SIGNAL;}
          }
        if (firstc_meta_reader(r) == r->eof)
         Result = Core._eof->value;
        else { next_meta_reader(r);
            Result = nexte_meta_reader(r);
            }
          }
      else if (n == 35)
       Result = read_escape_meta_reader(r);
      else if (n == 96)
       { Quote * _CL_obj = ((Quote *) GC_OBJECT(Quote,new_object_class(Language._Quote)));
        (_CL_obj->arg = nexte_meta_reader(cnext_meta_reader(r)));
        add_I_property(Kernel.instances,Language._Quote,11,_oid_(_CL_obj));
        Result = _oid_(_CL_obj);
        }
      else if (wcl_start_ask_meta_reader1(r,n) == CTRUE)
       Result = read_wcl_meta_reader1(r);
      else { OID  y = CNULL;
          OID  x;
          { if (n == 34)
             x = _string_(read_string_port(GC_OBJECT(PortObject,cnext_meta_reader(r)->fromp)));
            else if (n == 40)
             x = readblock_meta_reader(r,GC_OID(nexte_meta_reader(cnext_meta_reader(r))),41);
            else if ((48 <= (CL_INT)n) && 
                ((CL_INT)n <= 57))
             x = read_number_port(GC_OBJECT(PortObject,r->fromp));
            else if (n == 123)
             x = readset_meta_reader(r,GC_OID(nexte_meta_reader(cnext_meta_reader(r))));
            else { y= GC_OID(read_ident_meta_reader1(r));
                if (Kernel._string == OWNER(y))
                 x = y;
                else x = nexti_meta_reader(r,y);
                  }
              GC_OID(x);}
          if ((r->toplevel == CTRUE) && 
              ((OBJECT(ClaireBoolean,Reader.ALTERNATE_COMMAND_ask->value)) == CTRUE))
           { char * start;
            if (INHERIT(OWNER(x),Kernel._unbound_symbol))
             start = OBJECT(unbound_symbol,x)->name->name;
            else start = ((INHERIT(OWNER(x),Kernel._thing)) ?
              OBJECT(thing,x)->name->name :
              ((INHERIT(OWNER(x),Kernel._class)) ?
                OBJECT(ClaireClass,x)->name->name :
                ((INHERIT(OWNER(x),Kernel._symbol)) ?
                  OBJECT(symbol,x)->name :
                  ((INHERIT(OWNER(x),Language._Variable)) ?
                    OBJECT(Variable,x)->pname->name :
                    "" ) ) ) );
            OID  z;
            { if ((CL_INT)LENGTH_STRING(start) > 0)
               z = (*Reader.read_alternate_command)(_oid_(r),
                _string_(start));
              else z = Kernel.cfalse;
                GC_OID(z);}
            if (boolean_I_any(z) == CTRUE)
             x= z;
            }
          if (Kernel._string == OWNER(y))
           { if (extended_comment_ask_meta_reader(r,string_v(y)) == CTRUE)
             Result = extended_comment_I_meta_reader(r,string_v(y));
            else if (str == CTRUE)
             Result = y;
            else if (wcl_start_ask_meta_reader1(r,skipc_meta_reader(r)) == CTRUE)
             { unget_port1(GC_OBJECT(PortObject,r->fromp),">");
              Result = _oid_(Reader._ask);
              }
            else Result = nexte_meta_reader(r);
              }
          else { { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                while (((firstc_meta_reader(r) == 91) || 
                    ((firstc_meta_reader(r) == 46) || 
                      (firstc_meta_reader(r) == 60))))
                { GC_LOOP;
                  if (firstc_meta_reader(r) == 60)
                   { OID  y = GC_OID(nexte_meta_reader(cnext_meta_reader(r)));
                    if ((INHERIT(OWNER(x),Kernel._class)) && 
                        (firstc_meta_reader(r) == 62))
                     { cnext_meta_reader(r);
                      { { ClaireObject * V_CL0617;{ list * g0618UU;
                            { OID v_bag;
                              GC_ANY(g0618UU= list::empty(Kernel.emptySet));
                              { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                  (_CL_obj->selector = Kernel._equal);
                                  (_CL_obj->args = list::alloc(2,_oid_(Kernel.of),y));
                                  add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                                  v_bag = _oid_(_CL_obj);
                                  }
                                GC_OID(v_bag);}
                              ((list *) g0618UU)->addFast((OID)v_bag);}
                            V_CL0617 = extract_class_call_class(OBJECT(ClaireClass,x),g0618UU);
                            }
                          
                          x=_oid_(V_CL0617);}
                         GC__OID(x, 6);}
                      GC__OID(x = nexti_meta_reader(r,x), 6);
                      }
                    else Serror_integer1(154,"~S<~S not allowed",list::alloc(2,x,y));
                      }
                  else if (firstc_meta_reader(r) == 91)
                   { OID  l = GC_OID(nextseq_meta_reader(cnext_meta_reader(r),93));
                    { if ((INHERIT(OWNER(x),Kernel._class)) && 
                          ((x != _oid_(Kernel._type)) && 
                            (boolean_I_any(l) == CTRUE)))
                       x = _oid_(extract_class_call_class(OBJECT(ClaireClass,x),OBJECT(list,l)));
                      else x = _oid_(Call_I_property(Kernel.nth,GC_OBJECT(list,cons_any(x,OBJECT(list,l)))));
                         GC__OID(x, 6);}
                    }
                  else { OID  y = GC_OID(read_ident_meta_reader1(cnext_meta_reader(r)));
                      property * p = make_a_property_any(y);
                      { { Call_plus * _CL_obj = ((Call_plus *) GC_OBJECT(Call_plus,new_object_class(Language._Call_plus)));
                          (_CL_obj->selector = p);
                          (_CL_obj->args = list::alloc(1,x));
                          add_I_property(Kernel.instances,Language._Call_plus,11,_oid_(_CL_obj));
                          x = _oid_(_CL_obj);
                          }
                         GC__OID(x, 6);}
                      if (p->reified == CTRUE)
                       { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          (_CL_obj->selector = Core.read);
                          (_CL_obj->args = list::alloc(1,x));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                          x = _oid_(_CL_obj);
                          }
                         GC__OID(x, 6);}
                      }
                    GC_UNLOOP;POP_SIGNAL;}
                }
              Result = x;
              }
            }
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// reads a compact expression that starts with an ident
//
// The c++ function for: nexti(r:meta_reader,val:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  nexti_meta_reader(meta_reader *r,OID val)
{ GC_BIND;
  { OID Result = 0;
    if (firstc_meta_reader(r) == 40)
     { if ((val == _oid_(Reader.forall)) || 
          ((val == _oid_(Reader.exists)) || 
            (val == _oid_(Reader.some))))
       { Variable * v = GC_OBJECT(Variable,extract_variable_any(GC_OID(nexte_meta_reader(cnext_meta_reader(r)))));
        OID  _Za2 = GC_OID(nexte_meta_reader(r));
        OID  _Za3 = _oid_(Kernel._any);
        if (_Za2 == _oid_(Reader.in))
         { _Za3= GC_OID(nexte_meta_reader(r));
          if (equal(GC_OID(nexte_meta_reader(r)),GC_OID(Reader.OR->value)) != CTRUE)
           Serror_integer1(155,"Missing | in exists / forall",Kernel.nil);
          }
        else if (equal(_Za2,r->comma) == CTRUE)
         cnext_meta_reader(r);
        else Serror_integer1(156,"Wrong use of exists(~S ~S ...",list::alloc(2,_oid_(v),_Za2));
          { Exists * _CL_obj = ((Exists *) GC_OBJECT(Exists,new_object_class(Language._Exists)));
          (_CL_obj->var = v);
          (_CL_obj->set_arg = _Za3);
          { Iteration * g0619 = _CL_obj; 
            OID  g0620;
            { list * _Zbind = GC_OBJECT(list,bind_I_meta_reader(r,v));
              OID  x = GC_OID(nexts_I_meta_reader2(r,41));
              unbind_I_meta_reader(r,_Zbind);
              g0620 = x;
              }
            (g0619->arg = g0620);}
          { Exists * g0621 = _CL_obj; 
            OID  g0622;
            if (val == _oid_(Reader.forall))
             g0622 = Kernel.ctrue;
            else if (val == _oid_(Reader.exists))
             g0622 = Kernel.cfalse;
            else g0622 = CNULL;
              (g0621->other = g0622);}
          add_I_property(Kernel.instances,Language._Exists,11,_oid_(_CL_obj));
          Result = _oid_(_CL_obj);
          }
        }
      else if (val == _oid_(Reader.rule))
       { cnext_meta_reader(r);
        Result = val;
        }
      else Result = readcall_meta_reader(r,val,CNULL);
        }
    else if ((val == _oid_(Kernel._list)) && 
        (firstc_meta_reader(r) == 123))
     { OID  s = GC_OID(readset_meta_reader(r,GC_OID(nexte_meta_reader(cnext_meta_reader(r)))));
      if (INHERIT(OWNER(s),Language._Image))
       { (OBJECT(ClaireObject,s)->isa = Language._Collect);
        Result = s;
        }
      else if (INHERIT(OWNER(s),Language._Select))
       { (OBJECT(ClaireObject,s)->isa = Language._Lselect);
        Result = s;
        }
      else Serror_integer1(157,"~S cannot follow list{",list::alloc(1,s));
        }
    else if (((INHERIT(OWNER(val),Language._Call)) && ((OBJECT(Call,val)->selector == Kernel.nth) && 
          ((*(OBJECT(Call,val)->args))[1] == _oid_(Kernel._list)))) && 
        (firstc_meta_reader(r) == 123))
     { OID  s = GC_OID(readset_meta_reader(r,GC_OID(nexte_meta_reader(cnext_meta_reader(r)))));
      ClaireType * x = GC_OBJECT(ClaireType,extract_of_type_Call(OBJECT(Call,val)));
      if (INHERIT(OWNER(s),Language._Image))
       { (OBJECT(ClaireObject,s)->isa = Language._Collect);
        (OBJECT(Image,s)->of = x);
        Result = s;
        }
      else if (INHERIT(OWNER(s),Language._Select))
       { (OBJECT(ClaireObject,s)->isa = Language._Lselect);
        (OBJECT(Select,s)->of = x);
        Result = s;
        }
      else Serror_integer1(157,"~S cannot follow list{",list::alloc(1,s));
        }
    else if (((INHERIT(OWNER(val),Language._Call)) && ((OBJECT(Call,val)->selector == Kernel.nth) && 
          ((*(OBJECT(Call,val)->args))[1] == _oid_(Kernel._set)))) && 
        (firstc_meta_reader(r) == 123))
     { OID  s = GC_OID(readset_meta_reader(r,GC_OID(nexte_meta_reader(cnext_meta_reader(r)))));
      ClaireType * x = GC_OBJECT(ClaireType,extract_of_type_Call(OBJECT(Call,val)));
      if (INHERIT(OWNER(s),Language._Image))
       { (OBJECT(Image,s)->of = x);
        Result = s;
        }
      else if (INHERIT(OWNER(s),Language._Select))
       { (OBJECT(Select,s)->of = x);
        Result = s;
        }
      else Serror_integer1(157,"~S cannot follow list{",list::alloc(1,s));
        }
    else if (firstc_meta_reader(r) == 58)
     Result = nextvariable_meta_reader(r,val);
    else if (firstc_meta_reader(r) == 64)
     { OID  _Za1 = GC_OID(read_ident_meta_reader1(cnext_meta_reader(r)));
      if (inherit_ask_class(OWNER(_Za1),Kernel._class) != CTRUE)
       Serror_integer1(158,"Wrong type in call ~S@~S",list::alloc(2,val,_Za1));
      if (firstc_meta_reader(r) == 40)
       Result = readcall_meta_reader(r,val,_Za1);
      else Serror_integer1(159,"Missing ( after ~S@~S",list::alloc(2,val,_Za1));
        }
    else Result = val;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// we have read the escape character #
//
// The c++ function for: read_escape(r:meta_reader) [NEW_ALLOC+SLOT_UPDATE]
OID  read_escape_meta_reader(meta_reader *r)
{ { OID Result = 0;
    if (firstc_meta_reader(cnext_meta_reader(r)) == 47)
     { CL_INT  val = firstc_meta_reader(cnext_meta_reader(r));
      next_meta_reader(r);
      Result = ((OID)val);
      }
    else if (firstc_meta_reader(r) == 39)
     Result = _oid_(make_function_string(string_I_symbol(extract_symbol_any(read_ident_meta_reader1(cnext_meta_reader(r))))));
    else if ((firstc_meta_reader(r) == 105) && 
        (firstc_meta_reader(cnext_meta_reader(r)) == 102))
     { next_meta_reader(r);
      Result = _oid_(Reader._cl_Zif);
      }
    else if ((get_lines_meta_reader(r) == 1) && 
        (firstc_meta_reader(r) == 33))
     { { CL_INT loop_handle = ClEnv->cHandle;
        while (((firstc_meta_reader(cnext_meta_reader(r)) != 10) && 
            (firstc_meta_reader(r) != r->eof)))
        { ;POP_SIGNAL;}
        }
      Result = _string_("");
      }
    else Serror_integer1(160,"Wrong use of special char #",Kernel.nil);
      POP_SIGNAL; return (Result);}
  }


// The c++ function for: nextvariable(r:meta_reader,val:any) [NEW_ALLOC+SLOT_UPDATE]
OID  nextvariable_meta_reader(meta_reader *r,OID val)
{ GC_BIND;
  { OID Result = 0;
    if (val == _oid_(Kernel._inf))
     { skipc_meta_reader(r);
      Result = Reader.triangle->value;
      }
    else { Vardef * _CL_obj = ((Vardef *) GC_OBJECT(Vardef,new_object_class(Language._Vardef)));
        (_CL_obj->pname = extract_symbol_any(val));
        update_property(Kernel.range,
          _CL_obj,
          3,
          Kernel._object,
          GC_OID(nexte_meta_reader(cnext_meta_reader(r))));
        add_I_property(Kernel.instances,Language._Vardef,11,_oid_(_CL_obj));
        Result = _oid_(_CL_obj);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// reads an expression, then the exact keyword e
//
// The c++ function for: nexts!(r:meta_reader,e:keyword) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  nexts_I_meta_reader1(meta_reader *r,keyword *e)
{ GC_BIND;
  { OID Result = 0;
    { OID  x = GC_OID(nexts_meta_reader(r,e));
      if (boolean_I_any(stop_ask_integer(firstc_meta_reader(r))) != CTRUE)
       Result = x;
      else Serror_integer1(161,"Missing keyword ~S after ~S",list::alloc(2,_oid_(e),x));
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// reads an expression, then the exact keyword e
//
// The c++ function for: nexte!(r:meta_reader,e:keyword) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  nexte_I_meta_reader(meta_reader *r,keyword *e)
{ GC_BIND;
  { OID Result = 0;
    { OID  x = GC_OID(nexte_meta_reader(r));
      if (nexte_meta_reader(r) == _oid_(e))
       Result = x;
      else Serror_integer1(161,"Missing keyword ~S after ~S",list::alloc(2,_oid_(e),x));
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// ... exact separator
// The c++ function for: nexts!(r:meta_reader,e:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  nexts_I_meta_reader2(meta_reader *r,int e)
{ GC_BIND;
  { OID Result = 0;
    { OID  x = GC_OID(nexts_meta_reader(r,Reader.none));
      if (firstc_meta_reader(r) == e)
       { cnext_meta_reader(r);
        Result = x;
        }
      else Serror_integer1(162,"Missing separator ~S after ~S",list::alloc(2,_oid_(char_I_integer(e)),x));
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// ... keyword e or separator n. DOES NOT SKIP the last character
//
// The c++ function for: nexts!(r:meta_reader,e:keyword,n:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  nexts_I_meta_reader3(meta_reader *r,keyword *e,int n)
{ GC_BIND;
  { OID Result = 0;
    { OID  x = GC_OID(nexts_meta_reader(r,e));
      if ((firstc_meta_reader(r) == n) || 
          (boolean_I_any(stop_ask_integer(firstc_meta_reader(r))) != CTRUE))
       Result = x;
      else Serror_integer1(163,"Wrong separator ~S after ~S",list::alloc(2,_oid_(char_I_integer(firstc_meta_reader(r))),x));
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// checks if s is an extended comment
//
// The c++ function for: extended_comment?(r:meta_reader,s:string) [0]
ClaireBoolean * extended_comment_ask_meta_reader(meta_reader *r,char *s)
{ { ClaireBoolean *Result ;
    { CL_INT  n = get_string(s,_char_(((unsigned char)93 /* ']' */)));
      if ((_oid_(_char_(s[1 - 1])) == Core.EOS->value) || 
          ((s[1 - 1] != ((unsigned char)91 /* '[' */)) || 
            (n == 0)))
       Result = CFALSE;
      else { OID  g0624UU;
          { CL_INT  i = 2;
            CL_INT  g0623 = n;
            { CL_INT loop_handle = ClEnv->cHandle;
              g0624UU= _oid_(CFALSE);
              while (((CL_INT)i <= (CL_INT)g0623))
              { if (_I_equal_any(_oid_(_char_(s[n - 1])),_oid_(_char_(((unsigned char)91 /* '[' */)))) != CTRUE)
                 { g0624UU = Kernel.ctrue;
                  ClEnv->cHandle = loop_handle;break;}
                ++i;
                POP_SIGNAL;}
              }
            }
          Result = not_any(g0624UU);
          }
        }
    POP_SIGNAL; return (Result);}
  }


// produce the equivalent extended comment
//
// The c++ function for: extended_comment!(r:meta_reader,s:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  extended_comment_I_meta_reader(meta_reader *r,char *s)
{ GC_BIND;
  { OID Result = 0;
    { CL_INT  i = get_string(s,_char_(((unsigned char)93 /* ']' */)));
      CL_INT  k = included_string(s,"//",CTRUE);
      CL_INT  m = LENGTH_STRING(s);
      CL_INT  cx = firstc_meta_reader(r);
      print_in_string_void();
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((useless_c_integer(integer_I_char(_char_(s[m - 1]))) == CTRUE))
        { m= ((CL_INT)m-(CL_INT)1);
          POP_SIGNAL;}
        }
      if (s[m - 1] == ((unsigned char)44 /* ',' */))
       { cx= 44;
        m= ((CL_INT)m-(CL_INT)1);
        }
      if (k == 0)
       k= ((CL_INT)m+(CL_INT)1);
      if ((i == 3) && 
          (s[((CL_INT)i-(CL_INT)1) - 1] == ((unsigned char)63 /* '?' */)))
       { princ_string("assert(");
        { CL_INT  j = ((CL_INT)i+(CL_INT)2);
          CL_INT  g0625 = m;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)j <= (CL_INT)g0625))
            { princ_char(_char_(s[j - 1]));
              ++j;
              POP_SIGNAL;}
            }
          }
        princ_string(")");
        }
      else { princ_string("trace(");
          { CL_INT  j = 2;
            CL_INT  g0626 = ((CL_INT)i-(CL_INT)1);
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while (((CL_INT)j <= (CL_INT)g0626))
              { princ_char(_char_(s[j - 1]));
                ++j;
                POP_SIGNAL;}
              }
            }
          princ_string(",\"");
          { CL_INT  j = ((CL_INT)i+(CL_INT)2);
            CL_INT  g0627 = ((CL_INT)k-(CL_INT)1);
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while (((CL_INT)j <= (CL_INT)g0627))
              { princ_char(_char_(s[j - 1]));
                ++j;
                POP_SIGNAL;}
              }
            }
          princ_string("\\n\"");
          if ((CL_INT)((CL_INT)k+(CL_INT)3) <= (CL_INT)m)
           { princ_string(",");
            { CL_INT  j = ((CL_INT)k+(CL_INT)3);
              CL_INT  g0628 = m;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                while (((CL_INT)j <= (CL_INT)g0628))
                { princ_char(_char_(s[j - 1]));
                  ++j;
                  POP_SIGNAL;}
                }
              }
            }
          princ_string("))");
          }
        { ClaireBoolean * isWcl_ask = r->wcl_ask;
        OID  s2;
        { { (r->wcl_ask = CFALSE);
            s2 = read_string(GC_STRING(end_of_string_void()));
            }
          GC_OID(s2);}
        (r->wcl_ask = isWcl_ask);
        flush_port2(Reader.reader->fromp,cx);
        Result = s2;
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }



