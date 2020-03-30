/***** CLAIRE Compilation of file ./meta/read.cl 
         [version 3.5.0 / safety 5] *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>

#if defined(CLPC) && !defined(CLPCNODLL)
  #undef CL_EXPORT
  #define CL_EXPORT __declspec(dllexport)
#endif
#include <Reader.h>

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
CL_EXPORT ClaireBoolean * keyword_ask_any(OID x) { 
    POP_SIGNAL; return (inherit_ask_class(OWNER(x),Reader._reserved_keyword));}
  


//none :: keyword()
//<sb> v3.3.33 ffor
// the meta_class of the reader --------------------------------------
// The key values are placed in indexed so that they can be changed (eof ...).
// The slot *internal* is used to give addresses to lexical variables.
// The function next reads a character and places it in the slot first.
//
//<sb> wcl
//<sb> cache of symbol and the location of their definitions
//<sb> used by #! scripts to check weither the current line is the first
// The c++ function for: get_lines(r:meta_reader) [RETURN_ARG]
CL_EXPORT CL_INT  get_lines_meta_reader(meta_reader *r) { 
    { CL_INT Result = 0;
      Result = ((INHERIT(r->fromp->isa,Core._line_counter)) ?
        ((CL_INT)1+(CL_INT)CLREAD(line_counter,r->fromp,read_lines)) :
        0 );
      POP_SIGNAL; return (Result);}
    }
  


// closing brace as a CLAIRE entity
// The c++ function for: next(r:meta_reader) [SLOT_UPDATE]
CL_EXPORT CL_INT  next_meta_reader(meta_reader *r) { 
    { CL_INT Result = 0;
      { CL_INT  c = (CL_INT )(((CL_INT) r->fromp->getNext()));
        _void_(r->nb_line = get_lines_meta_reader(r));
        Result = c;
        }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: firstc(r:meta_reader) [0]
CL_EXPORT CL_INT  firstc_meta_reader(meta_reader *r) { 
    POP_SIGNAL; return ((CL_INT )(r->fromp->firstc));}
  


// The c++ function for: stop?(n:integer) [0]
CL_EXPORT OID  stop_ask_integer(CL_INT n) { 
    POP_SIGNAL; return (_oid_(((n == integer_I_char(_char_(((unsigned char)',')))) ? CTRUE : ((n == integer_I_char(_char_(((unsigned char)')')))) ? CTRUE : ((n == integer_I_char(_char_(((unsigned char)']')))) ? CTRUE : ((n == integer_I_char(_char_(((unsigned char)'}')))) ? CTRUE : CFALSE))))));}
  


// sugar in file
// this is used to keep comments when translating CLAIRE to another language
//matchWcl? :: property(open = 3) //<sb> wcl
//readWcl :: property(open = 3) //<sb> wcl
// read the next unit (definition, block or expression)
//
// The c++ function for: nextunit(r:meta_reader) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  nextunit_meta_reader(meta_reader *r) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  n = skipc_meta_reader(r);
        if (n == ((OID)r->eof))
         { next_meta_reader(r);
          Result = Core._eof->value;
          }
        else if (wcl_start_ask_meta_reader1(r,((CL_INT)n)) == CTRUE)
         Result = read_top_wcl_meta_reader1(r);
        else if (n == ((OID)integer_I_char(_char_(((unsigned char)'[')))))
         { OID  z = GC_OID(nexte_meta_reader(cnext_meta_reader(r)));
          Result = nextdefinition_meta_reader(r,z,GC_OID(nexte_meta_reader(r)),CTRUE);
          }
        else if (n == ((OID)integer_I_char(_char_(((unsigned char)'(')))))
         { if (r->toplevel == CTRUE)
           Result = nexts_meta_reader(r,Core.none);
          else Result = readblock_meta_reader(r,GC_OID(nexte_meta_reader(cnext_meta_reader(r))),integer_I_char(_char_(((unsigned char)')'))));
            }
        else if (n == ((OID)integer_I_char(_char_(((unsigned char)'`')))))
         { Quote * _CL_obj = ((Quote *) GC_OBJECT(Quote,new_object_class(Language._Quote)));
          _void_(_CL_obj->arg = nextunit_meta_reader(cnext_meta_reader(r)));
          add_I_property(Kernel.instances,Language._Quote,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if (n == ((OID)integer_I_char(_char_(((unsigned char)';')))))
         { { CL_INT loop_handle = ClEnv->cHandle;
            while (((firstc_meta_reader(r) != r->eof) && 
                (firstc_meta_reader(r) != integer_I_char(_char_(((unsigned char)'\n'))))))
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
               x = nexts_meta_reader(r,Core.none);
              else x = nextexp_meta_reader(r,CTRUE);
                GC_OID(x);}
            if ((r->toplevel == CTRUE) && 
                ((INHERIT(OWNER(x),Language._Assign)) && (INHERIT(OWNER(OBJECT(Assign,x)->var),Language._Vardef))))
             { Defobj * _CL_obj = ((Defobj *) GC_OBJECT(Defobj,new_object_class(Language._Defobj)));
              _void_(_CL_obj->ident = OBJECT(Variable,(*Language.var)(x))->pname);
              _void_(_CL_obj->arg = Core._global_variable);
              { Definition * g0637 = _CL_obj; 
                list * g0638;
                { OID v_bag;
                  GC_ANY(g0638= list::empty(Kernel.emptySet));
                  { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(_CL_obj->selector = Kernel._equal);
                      _void_(_CL_obj->args = list::alloc(2,_oid_(Kernel.range),GC_OID(_oid_(extract_type_any(GC_OID((*Kernel.range)(GC_OID((*Language.var)(x)))))))));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                      v_bag = _oid_(close_Instruction1(_CL_obj));
                      }
                    GC_OID(v_bag);}
                  ((list *) g0638)->addFast((OID)v_bag);
                  { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(_CL_obj->selector = Kernel._equal);
                      _void_(_CL_obj->args = list::alloc(2,_oid_(Kernel.value),GC_OID((*Kernel.arg)(x))));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                      v_bag = _oid_(close_Instruction1(_CL_obj));
                      }
                    GC_OID(v_bag);}
                  ((list *) g0638)->addFast((OID)v_bag);}
                _void_(g0637->args = g0638);}
              add_I_property(Kernel.instances,Language._Defobj,11,_oid_(_CL_obj));
              Result = _oid_(close_Instruction1(_CL_obj));
              }
            else if (Kernel._string == OWNER(x))
             Result = x;
            else { ClaireBoolean * g0639I;
              if (INHERIT(OWNER(x),Language._Call))
               { ClaireBoolean *v_and;
                { v_and = contain_ask_set(r->s_properties,_oid_(OBJECT(Call,x)->selector));
                  if (v_and == CFALSE) g0639I =CFALSE; 
                  else { { OID  g0640UU;
                      { CL_INT loop_handle = ClEnv->cHandle;
                        ITERATE(y);
                        g0640UU= Kernel.cfalse;
                        bag *y_support;
                        y_support = GC_OBJECT(list,OBJECT(Call,x)->args);
                        for (START(y_support); NEXT(y);)
                        if (not_any(_oid_(inherit_ask_class(OWNER(y),Language._Vardef))) != CTRUE)
                         { g0640UU = Kernel.ctrue;
                          ClEnv->cHandle = loop_handle;break;}
                        }
                      v_and = not_any(g0640UU);
                      }
                    if (v_and == CFALSE) g0639I =CFALSE; 
                    else g0639I = CTRUE;}
                  }
                }
              else g0639I = CFALSE;
                
              if (g0639I == CTRUE) { Call * z = OBJECT(Call,x);
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
CL_EXPORT OID  nexts_meta_reader(meta_reader *r,keyword *e) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  n = skipc_meta_reader(r);
        if (n == ((OID)r->eof))
         { next_meta_reader(r);
          Result = Core._eof->value;
          }
        else if (n == ((OID)integer_I_char(_char_(((unsigned char)'[')))))
         { OID  z = GC_OID(nexte_meta_reader(cnext_meta_reader(r)));
          Result = nextdefinition_meta_reader(r,z,GC_OID(nexte_meta_reader(r)),CTRUE);
          }
        else if (e == Reader.None)
         Result = nexte_meta_reader(r);
        else { OID  x = GC_OID(nexte_meta_reader(r));
            if (keyword_ask_any(x) == CTRUE)
             Result = nextstruct_meta_reader(r,OBJECT(keyword,x),e);
            else if ((e == Core.none) && 
                ((INHERIT(OWNER(x),Language._Call)) && (contain_ask_set(r->s_properties,_oid_(OBJECT(Call,x)->selector)) == CTRUE)))
             Result = x;
            else if ((r->toplevel == CTRUE) && 
                (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'\n')))))
             Result = loopexp_meta_reader(r,x,e,CFALSE);
            else if (wcl_start_ask_meta_reader1(r,((CL_INT)skipc_meta_reader(r))) == CTRUE)
             { unget_port2(GC_OBJECT(PortObject,r->fromp),_char_(((unsigned char)'>')));
              Result = x;
              }
            else Result = loopexp_meta_reader(r,x,e,CFALSE);
              }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: leaf_wcl_intruction?(self:any) [0]
CL_EXPORT ClaireBoolean * leaf_wcl_intruction_ask_any1(OID self) { 
    { ClaireBoolean *Result ;
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
            ((leaf_wcl_intruction_ask_any1(last_list(OBJECT(Do,self)->args)) == CTRUE) ? CTRUE : ((((CL_INT)OBJECT(Do,self)->args->length > (CL_INT)1) && 
                ((last_list(OBJECT(Do,self)->args) == _oid_(Core.none)) && 
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
CL_EXPORT ClaireBoolean * head_wcl_intruction_ask_any1(OID self) { 
    { ClaireBoolean *Result ;
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
CL_EXPORT OID  loopexp_meta_reader(meta_reader *r,OID x,keyword *e,ClaireBoolean *loop) { 
    if ((r->toplevel == CTRUE) && 
        ((e == Core.none) && 
          (findeol_meta_reader(r) == CTRUE))) 
    { { OID Result = 0;
        Result = x;
        return (Result);}
       }
    else{ 
      GC_BIND;
      { OID Result = 0;
        if (x == _oid_(Reader._ask))
         { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          _void_(_CL_obj->selector = Reader.inspect_toplevel);
          _void_(_CL_obj->args = list::alloc(1,GC_OID(nexte_meta_reader(r))));
          add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if (skipc_meta_reader(r) == ((OID)integer_I_char(_char_(((unsigned char)':')))))
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
             _void_(r->last_arrow = CTRUE);
            else if (((equal(w,Reader.arrow->value) == CTRUE) ? CTRUE : ((w == _oid_(Reader.L__equal)) ? CTRUE : CFALSE)) != CTRUE)
             Serror_integer1(149,((char*)"Wrong keyword (~S) after ~S"),list::alloc(2,w,y));
            Result = nextmethod_meta_reader(r,
              x,
              y,
              equal(w,_oid_(Reader.L__equal)),
              CFALSE,
              equal(w,_oid_(Reader._equal_sup)));
            }
          else Serror_integer1(150,((char*)"Illegal use of :~S after ~S"),list::alloc(2,y,x));
            }
        else if (wcl_start_ask_meta_reader1(r,firstc_meta_reader(r)) == CTRUE)
         { unget_port2(GC_OBJECT(PortObject,r->fromp),_char_(((unsigned char)'>')));
          Result = x;
          }
        else { OID  y = GC_OID(nexte_meta_reader(r));
            if ((y == _oid_(e)) || 
                ((y == _oid_(Reader._equal_sup)) && 
                    (_oid_(e) == Reader.arrow->value)))
             { if (y != _oid_(e))
               _void_(r->last_arrow = CTRUE);
              if (boolean_I_any(stop_ask_integer(firstc_meta_reader(r))) == CTRUE)
               Serror_integer1(151,((char*)"~S not allowed after ~S\n"),list::alloc(2,_oid_(char_I_integer(firstc_meta_reader(r))),_oid_(e)));
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
                 mtformat_module1(Reader.it,((char*)"test leaf x=~S, y=~S \n"),3,list::alloc(2,x,y));
                else ;if (y == _oid_(Reader._ask))
                 Result = x;
                else if (leaf_wcl_intruction_ask_any1(x) == CTRUE)
                 Result = Do_I_any(x,y);
                else if (head_wcl_intruction_ask_any1(y) == CTRUE)
                 Result = Do_I_any(x,y);
                else Serror_integer1(152,((char*)"Separation missing between ~S \nand ~S [~S?]"),list::alloc(3,x,
                    y,
                    _oid_(e)));
                  }
              }
          GC_UNBIND; POP_SIGNAL; return (Result);}
      }
    }
  


// this is the special form for x :op y - new in v3.3.32
// The c++ function for: extended_operator(p:property,x:any,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  extended_operator_property1(property *p,OID x,OID y) { 
    
    GC_BIND;
    { OID Result = 0;
      if (INHERIT(OWNER(x),Language._Call))
       { OID  r;
        { if (OBJECT(Call,x)->selector == Kernel.nth)
           r = (*(OBJECT(Call,x)->args))[2];
          else r = (*(OBJECT(Call,x)->args))[1];
            GC_OID(r);}
        Variable * v;
        { { Instruction *V_CC ;
            { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(_CL_obj->pname = gensym_void());
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            v= (Variable *) V_CC;}
          GC_OBJECT(Variable,v);}
        list * _Zb = GC_OBJECT(list,bind_I_meta_reader(Reader.reader,v));
        Call * x2;
        { { Instruction *V_CC ;
            if (OBJECT(Call,x)->selector == Kernel.nth)
             { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(_CL_obj->selector = Kernel.nth);
              _void_(_CL_obj->args = list::alloc(2,GC_OID((*(OBJECT(Call,x)->args))[1]),_oid_(v)));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            else { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(_CL_obj->selector = OBJECT(Call,x)->selector);
                _void_(_CL_obj->args = list::alloc(1,_oid_(v)));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              x2= (Call *) V_CC;}
          GC_OBJECT(Call,x2);}
        OID  res;
        { if (INHERIT(OWNER(r),Language._Call))
           { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
            _void_(_CL_obj->var = v);
            _void_(_CL_obj->value = r);
            _void_(_CL_obj->arg = combine_any(_oid_(x2),_oid_(Reader.L__equal),GC_OID(combine_any(_oid_(x2),_oid_(p),y))));
            add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
            res = _oid_(close_Instruction1(_CL_obj));
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
CL_EXPORT OID  nexte_meta_reader(meta_reader *r) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  x = GC_OID(nextexp_meta_reader(r,CFALSE));
        if (INHERIT(OWNER(x),Language._Instruction))
         _void_(r->last_form = x);
        Result = x;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// v3.3
// The c++ function for: add_ident(s:string) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT void  add_ident_string1(char *s) { 
    
    GC_BIND;
    { tuple * g0641 = get_location_port1(Reader.reader->fromp);
      OID  f = GC_OID((*(g0641))[1]);
      CL_INT  l = ((CL_INT)(*(g0641))[2]);
      CL_INT  o = ((CL_INT)(*(g0641))[3]);
      list * loc = list::alloc(Kernel._any,3,_string_(s),
        f,
        ((OID)l));
      if ((equal_string(s,((char*)".")) == CTRUE) || 
          (equal_string(s,((char*)"[")) == CTRUE))
       loc->addFast((OID)((OID)((CL_INT)((CL_INT)o-(CL_INT)1)-(CL_INT)LENGTH_STRING(s))));
      else loc->addFast((OID)((OID)((CL_INT)((CL_INT)o-(CL_INT)2)-(CL_INT)LENGTH_STRING(s))));
        loc->addFast((OID)((OID)LENGTH_STRING(s)));
      GC_OBJECT(list,OBJECT(list,Reader.IDENTS->value))->addFast((OID)_oid_(loc));
      }
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> fill the cache of symbol location
// The c++ function for: mClaire/read_ident(r:meta_reader) [NEW_ALLOC]
CL_EXPORT OID  read_ident_meta_reader1(meta_reader *r) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  x = GC_OID(read_ident_port(r->fromp));
        if (x == _oid_(Reader._cl_while))
         add_ident_string1(((char*)"while"));
        else if (x == _oid_(Reader.CATCH))
         add_ident_string1(((char*)"catch"));
        else if ((((INHERIT(OWNER(x),Kernel._symbol)) || 
                (INHERIT(OWNER(x),Kernel._unbound_symbol))) || 
              (INHERIT(OWNER(x),Kernel._property))) || 
            (INHERIT(OWNER(x),Kernel._class)))
         { add_ident_string1(extract_symbol_any(x)->name);
          if (((OBJECT(ClaireBoolean,Language.CAN_INIT_LOCATION_ask->value)) == CTRUE) && 
              (INHERIT(OBJECT(ClaireObject,x)->isa,Kernel._unbound_symbol)))
           (*Language.init_location)(x);
          }
        Result = x;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// reading the next compact expression/ same
//
// The c++ function for: nextexp(r:meta_reader,str:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  nextexp_meta_reader(meta_reader *r,ClaireBoolean *str) { 
    
    GC_RESERVE(5);  // v3.3.39 optim !
    { OID Result = 0;
      { CL_INT  n = ((CL_INT)skipc_meta_reader(r));
        if (n == integer_I_char(_char_(((unsigned char)')'))))
         Result = r->paren;
        else if (n == integer_I_char(_char_(((unsigned char)'}'))))
         Result = r->curly;
        else if (n == integer_I_char(_char_(((unsigned char)']'))))
         Result = r->bracket;
        else if (n == integer_I_char(_char_(((unsigned char)'|'))))
         { next_meta_reader(r);
          Result = Reader.OR->value;
          }
        else if (n == integer_I_char(_char_(((unsigned char)','))))
         Result = r->comma;
        else if (n == r->eof)
         Serror_integer1(153,((char*)"Eof inside an expression"),Kernel.nil);
        else if (n == integer_I_char(_char_(((unsigned char)';'))))
         { { CL_INT loop_handle = ClEnv->cHandle;
            while (((firstc_meta_reader(r) != r->eof) && 
                (firstc_meta_reader(r) != integer_I_char(_char_(((unsigned char)'\n'))))))
            { next_meta_reader(r);
              POP_SIGNAL;}
            }
          if (firstc_meta_reader(r) == r->eof)
           Result = Core._eof->value;
          else { next_meta_reader(r);
              Result = nexte_meta_reader(r);
              }
            }
        else if (n == integer_I_char(_char_(((unsigned char)'#'))))
         Result = read_escape_meta_reader(r);
        else if (n == integer_I_char(_char_(((unsigned char)'`'))))
         { Quote * _CL_obj = ((Quote *) GC_OBJECT(Quote,new_object_class(Language._Quote)));
          _void_(_CL_obj->arg = nexte_meta_reader(cnext_meta_reader(r)));
          add_I_property(Kernel.instances,Language._Quote,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if (wcl_start_ask_meta_reader1(r,n) == CTRUE)
         Result = read_wcl_meta_reader1(r);
        else { OID  y = CNULL;
            OID  x;
            { if (n == integer_I_char(_char_(((unsigned char)'"'))))
               x = _string_(read_string_port(GC_OBJECT(PortObject,cnext_meta_reader(r)->fromp)));
              else if (n == integer_I_char(_char_(((unsigned char)'('))))
               x = readblock_meta_reader(r,GC_OID(nexte_meta_reader(cnext_meta_reader(r))),integer_I_char(_char_(((unsigned char)')'))));
              else if (((CL_INT)integer_I_char(_char_(((unsigned char)'0'))) <= (CL_INT)n) && 
                  ((CL_INT)n <= (CL_INT)integer_I_char(_char_(((unsigned char)'9')))))
               x = read_number_port(GC_OBJECT(PortObject,r->fromp));
              else if (n == integer_I_char(_char_(((unsigned char)'{'))))
               x = readset_meta_reader(r,GC_OID(nexte_meta_reader(cnext_meta_reader(r))));
              else { y= (GC_OID(read_ident_meta_reader1(r)));
                  if (Kernel._string == OWNER(y))
                   x = y;
                  else x = nexti_meta_reader(r,y);
                    }
                GC_OID(x);}
            if (Kernel._string == OWNER(y))
             { if (extended_comment_ask_meta_reader(r,string_v(y)) == CTRUE)
               Result = extended_comment_I_meta_reader(r,string_v(y));
              else if (str == CTRUE)
               Result = y;
              else if (wcl_start_ask_meta_reader1(r,((CL_INT)skipc_meta_reader(r))) == CTRUE)
               { unget_port1(GC_OBJECT(PortObject,r->fromp),((char*)">"));
                Result = _oid_(Reader._ask);
                }
              else Result = nexte_meta_reader(r);
                }
            else { { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  while (((firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'[')))) || 
                      ((firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'.')))) || 
                        (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'<')))))))
                  { GC_LOOP;
                    if (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'<'))))
                     { OID  y = GC_OID(nexte_meta_reader(cnext_meta_reader(r)));
                      if ((INHERIT(OWNER(x),Kernel._class)) && 
                          (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'>')))))
                       { cnext_meta_reader(r);
                        { { ClaireObject * V_CL0642;{ list * g0643UU;
                              { OID v_bag;
                                GC_ANY(g0643UU= list::empty(Kernel.emptySet));
                                { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                    _void_(_CL_obj->selector = Kernel._equal);
                                    _void_(_CL_obj->args = list::alloc(2,_oid_(Kernel.of),y));
                                    add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                                    v_bag = _oid_(close_Instruction1(_CL_obj));
                                    }
                                  GC_OID(v_bag);}
                                ((list *) g0643UU)->addFast((OID)v_bag);}
                              V_CL0642 = extract_class_call_class(OBJECT(ClaireClass,x),g0643UU);
                              }
                            
                            x=_oid_(V_CL0642);}
                           GC__OID(x, 1);}
                        GC__OID(x = nexti_meta_reader(r,x), 2);
                        }
                      else Serror_integer1(154,((char*)"~S<~S not allowed"),list::alloc(2,x,y));
                        }
                    else if (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'['))))
                     { add_ident_string1(((char*)"["));
                      { OID  l = GC_OID(nextseq_meta_reader(cnext_meta_reader(r),integer_I_char(_char_(((unsigned char)']')))));
                        { if ((INHERIT(OWNER(x),Kernel._class)) && 
                              ((x != _oid_(Kernel._type)) && 
                                (boolean_I_any(l) == CTRUE)))
                           x = _oid_(extract_class_call_class(OBJECT(ClaireClass,x),OBJECT(list,l)));
                          else x = _oid_(Call_I_property(Kernel.nth,GC_OBJECT(list,cons_any(x,OBJECT(list,l)))));
                             GC__OID(x, 3);}
                        }
                      }
                    else { add_ident_string1(((char*)"."));
                        { OID  y = GC_OID(read_ident_port(GC_OBJECT(PortObject,cnext_meta_reader(r)->fromp)));
                          property * p = make_a_property_any(y);
                          { { Call_plus * _CL_obj = ((Call_plus *) GC_OBJECT(Call_plus,new_object_class(Language._Call_plus)));
                              _void_(_CL_obj->selector = p);
                              _void_(_CL_obj->args = list::alloc(1,x));
                              add_I_property(Kernel.instances,Language._Call_plus,11,_oid_(_CL_obj));
                              x = _oid_(close_Instruction1(_CL_obj));
                              }
                             GC__OID(x, 4);}
                          if (p->reified == CTRUE)
                           GC__OID(x = _oid_(Call_I_property(Core.read,list::alloc(1,x))), 5);
                          else ;}
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
CL_EXPORT OID  nexti_meta_reader(meta_reader *r,OID val) { 
    
    GC_BIND;
    { OID Result = 0;
      if (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'('))))
       { if ((val == _oid_(Reader.forall)) || 
            ((val == _oid_(Reader.exists)) || 
              (val == _oid_(Reader.some))))
         { Variable * v = GC_OBJECT(Variable,extract_variable_any(GC_OID(nexte_meta_reader(cnext_meta_reader(r)))));
          OID  _Za2 = GC_OID(nexte_meta_reader(r));
          OID  _Za3 = _oid_(Kernel._any);
          if (_Za2 == _oid_(Reader.in))
           { _Za3= (GC_OID(nexte_meta_reader(r)));
            if (equal(GC_OID(nexte_meta_reader(r)),GC_OID(Reader.OR->value)) != CTRUE)
             Serror_integer1(155,((char*)"Missing | in exists / forall"),Kernel.nil);
            }
          else if (equal(_Za2,r->comma) == CTRUE)
           cnext_meta_reader(r);
          else Serror_integer1(156,((char*)"Wrong use of exists(~S ~S ..."),list::alloc(2,_oid_(v),_Za2));
            { Exists * _CL_obj = ((Exists *) GC_OBJECT(Exists,new_object_class(Language._Exists)));
            _void_(_CL_obj->var = v);
            _void_(_CL_obj->set_arg = _Za3);
            { Iteration * g0644 = _CL_obj; 
              OID  g0645;
              { list * _Zbind = GC_OBJECT(list,bind_I_meta_reader(r,v));
                OID  x = GC_OID(nexts_I_meta_reader2(r,integer_I_char(_char_(((unsigned char)')')))));
                unbind_I_meta_reader(r,_Zbind);
                g0645 = x;
                }
              _void_(g0644->arg = g0645);}
            { Exists * g0646 = _CL_obj; 
              OID  g0647;
              if (val == _oid_(Reader.forall))
               g0647 = Kernel.ctrue;
              else if (val == _oid_(Reader.exists))
               g0647 = Kernel.cfalse;
              else g0647 = CNULL;
                _void_(g0646->other = g0647);}
            add_I_property(Kernel.instances,Language._Exists,11,_oid_(_CL_obj));
            Result = _oid_(close_Instruction1(_CL_obj));
            }
          }
        else if (val == _oid_(Reader.rule))
         { cnext_meta_reader(r);
          Result = val;
          }
        else Result = readcall_meta_reader(r,val,CNULL);
          }
      else if ((val == _oid_(Kernel._list)) && 
          (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'{')))))
       { OID  s = GC_OID(readset_meta_reader(r,GC_OID(nexte_meta_reader(cnext_meta_reader(r)))));
        if (INHERIT(OWNER(s),Language._Image))
         { _void_(OBJECT(ClaireObject,s)->isa = Language._Collect);
          Result = s;
          }
        else if (INHERIT(OWNER(s),Language._Select))
         { _void_(OBJECT(ClaireObject,s)->isa = Language._Lselect);
          Result = s;
          }
        else Serror_integer1(157,((char*)"~S cannot follow list{"),list::alloc(1,s));
          }
      else if (((INHERIT(OWNER(val),Language._Call)) && ((OBJECT(Call,val)->selector == Kernel.nth) && 
            ((*(OBJECT(Call,val)->args))[1] == _oid_(Kernel._list)))) && 
          (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'{')))))
       { OID  s = GC_OID(readset_meta_reader(r,GC_OID(nexte_meta_reader(cnext_meta_reader(r)))));
        ClaireType * x = GC_OBJECT(ClaireType,extract_of_type_Call(OBJECT(Call,val)));
        if (INHERIT(OWNER(s),Language._Image))
         { _void_(OBJECT(ClaireObject,s)->isa = Language._Collect);
          _void_(OBJECT(Image,s)->of = x);
          Result = s;
          }
        else if (INHERIT(OWNER(s),Language._Select))
         { _void_(OBJECT(ClaireObject,s)->isa = Language._Lselect);
          _void_(OBJECT(Select,s)->of = x);
          Result = s;
          }
        else Serror_integer1(157,((char*)"~S cannot follow list{"),list::alloc(1,s));
          }
      else if (((INHERIT(OWNER(val),Language._Call)) && ((OBJECT(Call,val)->selector == Kernel.nth) && 
            ((*(OBJECT(Call,val)->args))[1] == _oid_(Kernel._set)))) && 
          (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'{')))))
       { OID  s = GC_OID(readset_meta_reader(r,GC_OID(nexte_meta_reader(cnext_meta_reader(r)))));
        ClaireType * x = GC_OBJECT(ClaireType,extract_of_type_Call(OBJECT(Call,val)));
        if (INHERIT(OWNER(s),Language._Image))
         { _void_(OBJECT(Image,s)->of = x);
          Result = s;
          }
        else if (INHERIT(OWNER(s),Language._Select))
         { _void_(OBJECT(Select,s)->of = x);
          Result = s;
          }
        else Serror_integer1(157,((char*)"~S cannot follow list{"),list::alloc(1,s));
          }
      else if (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)':'))))
       Result = nextvariable_meta_reader(r,val);
      else if (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'@'))))
       { OID  _Za1 = GC_OID(read_ident_meta_reader1(cnext_meta_reader(r)));
        if (inherit_ask_class(OWNER(_Za1),Kernel._class) != CTRUE)
         Serror_integer1(158,((char*)"Wrong type in call ~S@~S"),list::alloc(2,val,_Za1));
        if (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'('))))
         Result = readcall_meta_reader(r,val,_Za1);
        else Serror_integer1(159,((char*)"Missing ( after ~S@~S"),list::alloc(2,val,_Za1));
          }
      else Result = val;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// we have read the escape character #
//
// The c++ function for: read_escape(r:meta_reader) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT OID  read_escape_meta_reader(meta_reader *r) { 
    
    GC_BIND;
    { OID Result = 0;
      if (firstc_meta_reader(cnext_meta_reader(r)) == integer_I_char(_char_(((unsigned char)'/'))))
       { CL_INT  val = firstc_meta_reader(cnext_meta_reader(r));
        next_meta_reader(r);
        { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          _void_(_CL_obj->selector = Kernel.integer_I);
          _void_(_CL_obj->args = list::alloc(1,_oid_(char_I_integer(val))));
          add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        }
      else if (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'\''))))
       Result = _oid_(make_function_string(string_I_symbol(extract_symbol_any(read_ident_meta_reader1(cnext_meta_reader(r))))));
      else if ((firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'i')))) && 
          (firstc_meta_reader(cnext_meta_reader(r)) == integer_I_char(_char_(((unsigned char)'f')))))
       { next_meta_reader(r);
        Result = _oid_(Reader._cl_Zif);
        }
      else if ((get_lines_meta_reader(r) == 1) && 
          (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'!')))))
       { { CL_INT loop_handle = ClEnv->cHandle;
          while (((firstc_meta_reader(cnext_meta_reader(r)) != integer_I_char(_char_(((unsigned char)'\n')))) && 
              (firstc_meta_reader(r) != r->eof)))
          { ;POP_SIGNAL;}
          }
        Result = _string_(((char*)""));
        }
      else Serror_integer1(160,((char*)"Wrong use of special char #"),Kernel.nil);
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: nextvariable(r:meta_reader,val:any) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT OID  nextvariable_meta_reader(meta_reader *r,OID val) { 
    
    GC_BIND;
    { OID Result = 0;
      if (val == _oid_(Kernel._inf))
       { skipc_meta_reader(r);
        Result = Reader.triangle->value;
        }
      else { Vardef * _CL_obj = ((Vardef *) GC_OBJECT(Vardef,new_object_class(Language._Vardef)));
          _void_(_CL_obj->pname = extract_symbol_any(val));
          update_property(Kernel.range,
            _CL_obj,
            3,
            Kernel._object,
            GC_OID(nexte_meta_reader(cnext_meta_reader(r))));
          add_I_property(Kernel.instances,Language._Vardef,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// reads an expression, then the exact keyword e
//
// The c++ function for: nexts!(r:meta_reader,e:keyword) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  nexts_I_meta_reader1(meta_reader *r,keyword *e) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  x = GC_OID(nexts_meta_reader(r,e));
        if (boolean_I_any(stop_ask_integer(firstc_meta_reader(r))) != CTRUE)
         Result = x;
        else Serror_integer1(161,((char*)"Missing keyword ~S after ~S"),list::alloc(2,_oid_(e),x));
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// reads an expression, then the exact keyword e
//
// The c++ function for: nexte!(r:meta_reader,e:keyword) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  nexte_I_meta_reader(meta_reader *r,keyword *e) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  x = GC_OID(nexte_meta_reader(r));
        if (nexte_meta_reader(r) == _oid_(e))
         Result = x;
        else Serror_integer1(161,((char*)"Missing keyword ~S after ~S"),list::alloc(2,_oid_(e),x));
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// ... exact separator
// The c++ function for: nexts!(r:meta_reader,e:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  nexts_I_meta_reader2(meta_reader *r,int e) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  x = GC_OID(nexts_meta_reader(r,Core.none));
        if (firstc_meta_reader(r) == e)
         { cnext_meta_reader(r);
          Result = x;
          }
        else Serror_integer1(162,((char*)"Missing separator ~S after ~S"),list::alloc(2,_oid_(char_I_integer(e)),x));
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// ... keyword e or separator n. DOES NOT SKIP the last character
//
// The c++ function for: nexts!(r:meta_reader,e:keyword,n:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  nexts_I_meta_reader3(meta_reader *r,keyword *e,int n) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  x = GC_OID(nexts_meta_reader(r,e));
        if ((firstc_meta_reader(r) == n) || 
            (boolean_I_any(stop_ask_integer(firstc_meta_reader(r))) != CTRUE))
         Result = x;
        else Serror_integer1(163,((char*)"Wrong separator ~S after ~S"),list::alloc(2,_oid_(char_I_integer(firstc_meta_reader(r))),x));
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// checks if s is an extended comment
//
// The c++ function for: extended_comment?(r:meta_reader,s:string) [0]
CL_EXPORT ClaireBoolean * extended_comment_ask_meta_reader(meta_reader *r,char *s) { 
    { ClaireBoolean *Result ;
      { CL_INT  n = get_string(s,_char_(((unsigned char)']')));
        if ((_oid_(_char_(s[1 - 1])) == Core.EOS->value) || 
            ((s[1 - 1] != ((unsigned char)'[')) || 
              (n == 0)))
         Result = CFALSE;
        else { OID  g0649UU;
            { CL_INT  i = 2;
              CL_INT  g0648 = n;
              { CL_INT loop_handle = ClEnv->cHandle;
                g0649UU= _oid_(CFALSE);
                while (((CL_INT)i <= (CL_INT)g0648))
                { if (_I_equal_any(_oid_(_char_(s[n - 1])),_oid_(_char_(((unsigned char)'[')))) != CTRUE)
                   { g0649UU = Kernel.ctrue;
                    ClEnv->cHandle = loop_handle;break;}
                  ++i;
                  POP_SIGNAL;}
                }
              }
            Result = not_any(g0649UU);
            }
          }
      POP_SIGNAL; return (Result);}
    }
  


// produce the equivalent extended comment
//
// The c++ function for: extended_comment!(r:meta_reader,s:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  extended_comment_I_meta_reader(meta_reader *r,char *s) { 
    
    GC_BIND;
    { OID Result = 0;
      { CL_INT  i = get_string(s,_char_(((unsigned char)']')));
        CL_INT  k = included_string(s,((char*)"//"),CTRUE);
        CL_INT  m = LENGTH_STRING(s);
        CL_INT  col = color_integer(0);
        CL_INT  cx = firstc_meta_reader(r);
        print_in_string_void();
        { CL_INT loop_handle = ClEnv->cHandle;
          while ((useless_c_integer(integer_I_char(_char_(s[m - 1]))) == CTRUE))
          { m= (CL_INT)(((CL_INT)m-(CL_INT)1));
            POP_SIGNAL;}
          }
        if (s[m - 1] == ((unsigned char)','))
         { cx= (CL_INT)(integer_I_char(_char_(((unsigned char)','))));
          m= (CL_INT)(((CL_INT)m-(CL_INT)1));
          }
        if (k == 0)
         k= (CL_INT)(((CL_INT)m+(CL_INT)1));
        if ((i == 3) && 
            (s[((CL_INT)i-(CL_INT)1) - 1] == ((unsigned char)'?')))
         { princ_string(((char*)"assert("));
          { CL_INT  j = ((CL_INT)i+(CL_INT)2);
            CL_INT  g0650 = m;
            { CL_INT loop_handle = ClEnv->cHandle;
              while (((CL_INT)j <= (CL_INT)g0650))
              { princ_char(_char_(s[j - 1]));
                ++j;
                POP_SIGNAL;}
              }
            }
          princ_string(((char*)")"));
          }
        else { princ_string(((char*)"trace("));
            { CL_INT  j = 2;
              CL_INT  g0651 = ((CL_INT)i-(CL_INT)1);
              { CL_INT loop_handle = ClEnv->cHandle;
                while (((CL_INT)j <= (CL_INT)g0651))
                { princ_char(_char_(s[j - 1]));
                  ++j;
                  POP_SIGNAL;}
                }
              }
            princ_string(((char*)",\""));
            { CL_INT  j = ((CL_INT)i+(CL_INT)2);
              CL_INT  g0652 = ((CL_INT)k-(CL_INT)1);
              { CL_INT loop_handle = ClEnv->cHandle;
                while (((CL_INT)j <= (CL_INT)g0652))
                { princ_char(_char_(s[j - 1]));
                  ++j;
                  POP_SIGNAL;}
                }
              }
            princ_string(((char*)"\\n\""));
            if ((CL_INT)((CL_INT)k+(CL_INT)3) <= (CL_INT)m)
             { princ_string(((char*)","));
              { CL_INT  j = ((CL_INT)k+(CL_INT)3);
                CL_INT  g0653 = m;
                { CL_INT loop_handle = ClEnv->cHandle;
                  while (((CL_INT)j <= (CL_INT)g0653))
                  { princ_char(_char_(s[j - 1]));
                    ++j;
                    POP_SIGNAL;}
                  }
                }
              }
            princ_string(((char*)"))"));
            }
          { ClaireBoolean * isWcl_ask = r->wcl_ask;
          OID  s2;
          { { _void_(r->wcl_ask = CFALSE);
              s2 = read_string(GC_STRING(end_of_string_void()));
              }
            GC_OID(s2);}
          _void_(r->wcl_ask = isWcl_ask);
          flush_port2(Reader.reader->fromp,cx);
          color_integer(col);
          Result = s2;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  



/***** CLAIRE Compilation of file ./meta/syntax.cl 
         [version 3.5.0 / safety 5] *****/


//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| syntax.cl                                                   |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+
// The c++ function for: Call!(p:property,l:list) [NEW_ALLOC]
CL_EXPORT Call * Call_I_property(property *p,list *l) { 
    
    GC_BIND;
    { Call *Result ;
      { Instruction *V_CC ;
        { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
          _void_(_CL_obj->selector = p);
          _void_(_CL_obj->args = l);
          add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
          V_CC = close_Instruction1(_CL_obj);
          }
        Result= (Call *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// who is an operation?
//
// The c++ function for: operation?(y:any) [0]
CL_EXPORT ClaireBoolean * operation_ask_any(OID y) { 
    POP_SIGNAL; return (((y == _oid_(Reader.as)) ? CTRUE : 
    ((y == _oid_(Reader.L__equal)) ? CTRUE : 
    ((INHERIT(OWNER(y),Kernel._operation)) ? CTRUE : 
    ((equal(y,Reader.OR->value) == CTRUE) ? CTRUE : 
    ((y == _oid_(Kernel._Z)) ? CTRUE : 
    ((y == _oid_(Kernel.add)) ? CTRUE : 
    CFALSE)))))));}
  


// produce an expression from an operation
//
// The c++ function for: combine(x:any,y:any,z:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  combine_any(OID x,OID y,OID z) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  p = operation_I_any(x);
        if ((boolean_I_any(p) == CTRUE) && 
            ((CL_INT)precedence_I_any(y) < (CL_INT)precedence_I_any(p)))
         Result = combine_I_any(GC_OID(operand_I_any(x,1)),p,GC_OID(combine_any(GC_OID(operand_I_any(x,2)),y,z)));
        else Result = combine_I_any(x,y,z);
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: combine!(x:any,y:any,z:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  combine_I_any(OID x,OID y,OID z) { 
    
    GC_BIND;
    { OID Result = 0;
      if (y == _oid_(Reader.as))
       { Cast * _CL_obj = ((Cast *) GC_OBJECT(Cast,new_object_class(Language._Cast)));
        _void_(_CL_obj->arg = x);
        _void_(_CL_obj->set_arg = extract_type_any(z));
        add_I_property(Kernel.instances,Language._Cast,11,_oid_(_CL_obj));
        Result = _oid_(close_Instruction1(_CL_obj));
        }
      else if (y == _oid_(Reader.L__equal))
       { if (INHERIT(OWNER(x),Core._global_variable))
         { Gassign * _CL_obj = ((Gassign *) GC_OBJECT(Gassign,new_object_class(Language._Gassign)));
          _void_(_CL_obj->var = OBJECT(global_variable,x));
          _void_(_CL_obj->arg = z);
          add_I_property(Kernel.instances,Language._Gassign,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if (INHERIT(OWNER(x),Language._Call))
         { if ((INHERIT(OWNER(z),Language._Call)) && (((OBJECT(Call,z)->selector == Kernel.add) || 
                (OBJECT(Call,z)->selector == Kernel._delete)) && 
              ((equal((*(OBJECT(Call,z)->args))[1],x) == CTRUE) && 
                ((OBJECT(Call,x)->args->length == 1) ? (multi_ask_any(_oid_(OBJECT(Call,x)->selector)) == CTRUE) : (((OBJECT(Call,x)->selector == Kernel.nth) && 
                    (OBJECT(Call,x)->args->length == 2)) && (multi_ask_any((*(OBJECT(Call,x)->args))[1]) == CTRUE))))))
           { Call * V_CL0655;{ list * g0656UU;
              { OID v_bag;
                GC_ANY(g0656UU= list::empty(Kernel.emptySet));
                { if (OBJECT(Call,x)->args->length == 1)
                   v_bag = _oid_(OBJECT(Call,x)->selector);
                  else v_bag = (*(OBJECT(Call,x)->args))[1];
                    GC_OID(v_bag);}
                ((list *) g0656UU)->addFast((OID)v_bag);
                { if (OBJECT(Call,x)->args->length == 1)
                   v_bag = (*(OBJECT(Call,x)->args))[1];
                  else v_bag = (*(OBJECT(Call,x)->args))[2];
                    GC_OID(v_bag);}
                ((list *) g0656UU)->addFast((OID)v_bag);
                ((list *) g0656UU)->addFast((OID)GC_OID((*(OBJECT(bag,(*Core.args)(z))))[2]));}
              V_CL0655 = Call_I_property(OBJECT(property,(*Kernel.selector)(z)),g0656UU);
              }
            
            Result=_oid_(V_CL0655);}
          else if (OBJECT(Call,x)->selector == Kernel.nth)
           Result = _oid_(Call_I_property(Kernel.nth_equal,GC_OBJECT(list,((list *) copy_bag(OBJECT(Call,x)->args))->addFast((OID)z))));
          else if (OBJECT(Call,x)->args->length == 1)
           { property * p = make_a_property_any(_oid_(OBJECT(Call,x)->selector));
            OID  y = GC_OID((*(OBJECT(Call,x)->args))[1]);
            if ((p == Core.read) && 
                ((INHERIT(OWNER(y),Language._Call_plus)) && (OBJECT(Call,y)->selector->reified == CTRUE)))
             Result = _oid_(Call_I_property(Core.write,list::alloc(2,y,z)));
            else Result = _oid_(Call_I_property(Core.write,list::alloc(3,_oid_(p),
                y,
                z)));
              }
          else Serror_integer1(164,((char*)"~S cannot be assigned with :="),list::alloc(1,x));
            }
        else if (INHERIT(OWNER(x),Language._Do))
         { list * l = GC_OBJECT(list,OBJECT(Do,x)->args);
          CL_INT  m = l->length;
          Variable * v;
          { { Instruction *V_CC ;
              { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                _void_(_CL_obj->pname = gensym_void());
                add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              v= (Variable *) V_CC;}
            GC_OBJECT(Variable,v);}
          list * _Zbind = GC_OBJECT(list,bind_I_meta_reader(Reader.reader,v));
          Let_star * res;
          { { Instruction *V_CC ;
              { Let_star * _CL_obj = ((Let_star *) GC_OBJECT(Let_star,new_object_class(Language._Let_star)));
                _void_(_CL_obj->var = v);
                _void_(_CL_obj->value = z);
                { Let * g0657 = _CL_obj; 
                  OID  g0658;
                  { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                    { Do * g0659 = _CL_obj; 
                      list * g0660;
                      { list * i_bag = list::empty(Kernel._any);
                        { CL_INT  i = 1;
                          CL_INT  g0654 = m;
                          { CL_INT loop_handle = ClEnv->cHandle;
                            OID gc_local;
                            while (((CL_INT)i <= (CL_INT)g0654))
                            { GC_LOOP;
                              { OID  g0661UU;
                                { { Assign * _CL_obj = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
                                    _void_(_CL_obj->var = (*(l))[i]);
                                    _void_(_CL_obj->arg = _oid_(Call_I_property(Kernel.nth,GC_OBJECT(list,list::alloc(2,_oid_(v),((OID)i))))));
                                    add_I_property(Kernel.instances,Language._Assign,11,_oid_(_CL_obj));
                                    g0661UU = _oid_(close_Instruction1(_CL_obj));
                                    }
                                  GC_OID(g0661UU);}
                                i_bag->addFast((OID)g0661UU);
                                }
                              ++i;
                              GC_UNLOOP;POP_SIGNAL;}
                            }
                          }
                        g0660 = GC_OBJECT(list,i_bag);
                        }
                      _void_(g0659->args = g0660);}
                    add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
                    g0658 = _oid_(close_Instruction1(_CL_obj));
                    }
                  _void_(g0657->arg = g0658);}
                add_I_property(Kernel.instances,Language._Let_star,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              res= (Let_star *) V_CC;}
            GC_OBJECT(Let_star,res);}
          unbind_I_meta_reader(Reader.reader,_Zbind);
          Result = _oid_(res);
          }
        else { Assign * _CL_obj = ((Assign *) GC_OBJECT(Assign,new_object_class(Language._Assign)));
            _void_(_CL_obj->var = x);
            _void_(_CL_obj->arg = z);
            add_I_property(Kernel.instances,Language._Assign,11,_oid_(_CL_obj));
            Result = _oid_(close_Instruction1(_CL_obj));
            }
          }
      else if (equal(y,Reader.OR->value) == CTRUE)
       { if (INHERIT(OWNER(x),Language._Or))
         { GC_OBJECT(list,OBJECT(Or,x)->args)->addFast((OID)z);
          Result = x;
          }
        else { Or * _CL_obj = ((Or *) GC_OBJECT(Or,new_object_class(Language._Or)));
            _void_(_CL_obj->args = list::alloc(2,x,z));
            add_I_property(Kernel.instances,Language._Or,11,_oid_(_CL_obj));
            Result = _oid_(close_Instruction1(_CL_obj));
            }
          }
      else if (equal(y,Reader.AND->value) == CTRUE)
       { if (INHERIT(OWNER(x),Language._And))
         { GC_OBJECT(list,OBJECT(And,x)->args)->addFast((OID)z);
          Result = x;
          }
        else { And * _CL_obj = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
            _void_(_CL_obj->args = list::alloc(2,x,z));
            add_I_property(Kernel.instances,Language._And,11,_oid_(_CL_obj));
            Result = _oid_(close_Instruction1(_CL_obj));
            }
          }
      else if (y == _oid_(Kernel._Z))
       Result = _oid_(Call_I_property(Kernel._Z,GC_OBJECT(list,list::alloc(2,x,z))));
      else { Call_star * _CL_obj = ((Call_star *) GC_OBJECT(Call_star,new_object_class(Language._Call_star)));
          update_property(Kernel.selector,
            _CL_obj,
            2,
            Kernel._object,
            y);
          _void_(_CL_obj->args = list::alloc(2,x,z));
          add_I_property(Kernel.instances,Language._Call_star,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// allows to treats Calls, Assigns, Gassign in an homogeneous way
//
// The c++ function for: operation!(x:any) [0]
CL_EXPORT OID  operation_I_any(OID x) { 
    { OID Result = 0;
      if (INHERIT(OWNER(x),Language._Or))
       Result = Reader.OR->value;
      else if (INHERIT(OWNER(x),Language._And))
       Result = Reader.AND->value;
      else if (INHERIT(OWNER(x),Language._Assign))
       Result = _oid_(Reader.L__equal);
      else if (INHERIT(OWNER(x),Language._Gassign))
       Result = _oid_(Reader.L__equal);
      else if (INHERIT(OWNER(x),Language._Call))
       { property * p = OBJECT(Call,x)->selector;
        if ((INHERIT(OBJECT(ClaireObject,x)->isa,Language._Call_star)) && 
            (operation_ask_any(_oid_(p)) == CTRUE))
         Result = _oid_(p);
        else if (p == Kernel.nth_equal)
         Result = _oid_(Reader.L__equal);
        else if (p == Core.write)
         Result = _oid_(Reader.L__equal);
        else Result = Kernel.cfalse;
          }
      else Result = Kernel.cfalse;
        POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: operand!(x:any,n:integer) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  operand_I_any(OID x,int n) { 
    
    GC_BIND;
    { OID Result = 0;
      if (INHERIT(OWNER(x),Language._Or))
       { if (n == 1)
         { Or * _CL_obj = ((Or *) GC_OBJECT(Or,new_object_class(Language._Or)));
          _void_(_CL_obj->args = rmlast_list(((list *) copy_bag(OBJECT(Or,x)->args))));
          add_I_property(Kernel.instances,Language._Or,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else Result = last_list(OBJECT(Or,x)->args);
          }
      else if (INHERIT(OWNER(x),Language._And))
       { if (n == 1)
         { And * _CL_obj = ((And *) GC_OBJECT(And,new_object_class(Language._And)));
          _void_(_CL_obj->args = rmlast_list(((list *) copy_bag(OBJECT(And,x)->args))));
          add_I_property(Kernel.instances,Language._And,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else Result = last_list(OBJECT(And,x)->args);
          }
      else if (INHERIT(OWNER(x),Language._Assign))
       { if (n == 1)
         Result = OBJECT(Assign,x)->var;
        else Result = OBJECT(Assign,x)->arg;
          }
      else if (INHERIT(OWNER(x),Language._Gassign))
       { if (n == 1)
         Result = _oid_(OBJECT(Gassign,x)->var);
        else Result = OBJECT(Gassign,x)->arg;
          }
      else if (INHERIT(OWNER(x),Language._Call))
       { if (OBJECT(Call,x)->selector == Core.write)
         { if (n == 2)
           Result = (*(OBJECT(Call,x)->args))[3];
          else Result = _oid_(Call_I_property(OBJECT(property,(*(OBJECT(Call,x)->args))[1]),list::alloc(1,GC_OID((*(OBJECT(Call,x)->args))[2]))));
            }
        else if (OBJECT(Call,x)->selector == Kernel.nth_equal)
         { if (n == 2)
           Result = last_list(OBJECT(Call,x)->args);
          else Result = _oid_(Call_I_property(Kernel.nth,rmlast_list(((list *) copy_bag(OBJECT(Call,x)->args)))));
            }
        else Result = (*(OBJECT(Call,x)->args))[n];
          }
      else Result = Kernel.cfalse;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// precedence
//
// The c++ function for: precedence!(y:any) [RETURN_ARG]
CL_EXPORT CL_INT  precedence_I_any(OID y) { 
    { CL_INT Result = 0;
      Result = ((y == _oid_(Reader.as)) ?
        0 :
        ((y == _oid_(Reader.L__equal)) ?
          100 :
          ((equal(y,Reader.AND->value) == CTRUE) ?
            1000 :
            ((equal(y,Reader.OR->value) == CTRUE) ?
              1010 :
              OBJECT(operation,y)->precedence ) ) ) );
      POP_SIGNAL; return (Result);}
    }
  


// *********************************************************************
// *      Part 3: Syntactical Analysis                                 *
// *********************************************************************
// The c++ function for: nextstruct(r:meta_reader,%first:keyword,e:keyword) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  nextstruct_meta_reader(meta_reader *r,keyword *_Zfirst,keyword *e) { 
    
    GC_BIND;
    { OID Result = 0;
      if (_Zfirst == Reader._cl_let)
       Result = readlet_meta_reader(r,e);
      else if (_Zfirst == Reader._cl_when)
       Result = readwhen_meta_reader(r,e);
      else if (_Zfirst == Reader._cl_case)
       Result = readcase_meta_reader(r,e);
      else if (_Zfirst == Reader._cl_for)
       { Variable * _Zvar = GC_OBJECT(Variable,extract_variable_any(GC_OID(nexts_I_meta_reader1(r,Reader.in))));
        OID  _Zset = GC_OID(nexte_meta_reader(r));
        list * _Zbind = GC_OBJECT(list,bind_I_meta_reader(r,_Zvar));
        For * x;
        { { Instruction *V_CC ;
            { if (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)','))))
               next_meta_reader(r);
              { For * _CL_obj = ((For *) GC_OBJECT(For,new_object_class(Language._For)));
                _void_(_CL_obj->var = _Zvar);
                _void_(_CL_obj->set_arg = _Zset);
                _void_(_CL_obj->arg = nexts_meta_reader(r,e));
                add_I_property(Kernel.instances,Language._For,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              }
            x= (For *) V_CC;}
          GC_OBJECT(For,x);}
        unbind_I_meta_reader(r,_Zbind);
        Result = _oid_(x);
        }
      else if (_Zfirst == Reader._cl_ffor)
       { Variable * _Zvar = GC_OBJECT(Variable,extract_variable_any(GC_OID(nexts_I_meta_reader1(r,Reader.in))));
        OID  _Zset = GC_OID(nexts_meta_reader(r,Reader.by));
        OID  _Zby;
        { { if (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)','))))
             next_meta_reader(r);
            _Zby = nexte_meta_reader(r);
            }
          GC_OID(_Zby);}
        list * _Zbind = GC_OBJECT(list,bind_I_meta_reader(r,_Zvar));
        iClaire_Ffor * x;
        { { Instruction *V_CC ;
            { iClaire_Ffor * _CL_obj = ((iClaire_Ffor *) GC_OBJECT(iClaire_Ffor,new_object_class(Language._Ffor)));
              _void_(_CL_obj->var = _Zvar);
              _void_(_CL_obj->set_arg = _Zset);
              _void_(_CL_obj->forkedby = _Zby);
              _void_(_CL_obj->arg = nexts_meta_reader(r,e));
              add_I_property(Kernel.instances,Language._Ffor,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            x= (iClaire_Ffor *) V_CC;}
          GC_OBJECT(iClaire_Ffor,x);}
        unbind_I_meta_reader(r,_Zbind);
        Result = _oid_(x);
        }
      else if (_Zfirst == Reader._cl_while)
       { While * _CL_obj = ((While *) GC_OBJECT(While,new_object_class(Language._While)));
        _void_(_CL_obj->test = nexte_meta_reader(r));
        _void_(_CL_obj->arg = nexts_meta_reader(r,e));
        _void_(_CL_obj->other = CFALSE);
        add_I_property(Kernel.instances,Language._While,11,_oid_(_CL_obj));
        Result = _oid_(close_Instruction1(_CL_obj));
        }
      else if (_Zfirst == Reader._cl_until)
       { While * _CL_obj = ((While *) GC_OBJECT(While,new_object_class(Language._While)));
        _void_(_CL_obj->test = nexte_meta_reader(r));
        _void_(_CL_obj->arg = nexts_meta_reader(r,e));
        _void_(_CL_obj->other = CTRUE);
        add_I_property(Kernel.instances,Language._While,11,_oid_(_CL_obj));
        Result = _oid_(close_Instruction1(_CL_obj));
        }
      else if (_Zfirst == Reader._cl_try)
       { OID  _Za = GC_OID(nexts_I_meta_reader1(r,Reader.CATCH));
        OID  _Zt = GC_OID(nexte_meta_reader(r));
        ClaireHandle * _CL_obj = ((ClaireHandle *) GC_OBJECT(ClaireHandle,new_object_class(Language._Handle)));
        _void_(_CL_obj->test = _Zt);
        _void_(_CL_obj->arg = _Za);
        _void_(_CL_obj->other = nexts_meta_reader(r,e));
        add_I_property(Kernel.instances,Language._Handle,11,_oid_(_CL_obj));
        Result = _oid_(close_Instruction1(_CL_obj));
        }
      else Result = _oid_(_Zfirst);
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// reads a let expression
//
// The c++ function for: readlet(r:meta_reader,e:keyword) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  readlet_meta_reader(meta_reader *r,keyword *e) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  _Zdef = GC_OID(nexts_I_meta_reader3(r,Reader.in,integer_I_char(_char_(((unsigned char)',')))));
        if (INHERIT(OWNER(_Zdef),Language._Assign))
         { Variable * v = GC_OBJECT(Variable,extract_variable_any(GC_OID(OBJECT(Assign,_Zdef)->var)));
          list * _Zbind = GC_OBJECT(list,bind_I_meta_reader(r,v));
          Let * x;
          { { Instruction *V_CC ;
              { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                _void_(_CL_obj->var = v);
                _void_(_CL_obj->value = OBJECT(Assign,_Zdef)->arg);
                { Let * g0662 = _CL_obj; 
                  OID  g0663;
                  if (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)','))))
                   g0663 = readlet_meta_reader(cnext_meta_reader(r),e);
                  else g0663 = nexts_meta_reader(r,e);
                    _void_(g0662->arg = g0663);}
                add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              x= (Let *) V_CC;}
            GC_OBJECT(Let,x);}
          unbind_I_meta_reader(r,_Zbind);
          Result = _oid_(x);
          }
        else if (INHERIT(OWNER(_Zdef),Language._Let_star))
         { Variable * v = GC_OBJECT(Variable,OBJECT(Instruction_with_var,_Zdef)->var);
          list * _Zbind = GC_OBJECT(list,bind_I_meta_reader(r,v));
          _void_(OBJECT(Let,_Zdef)->arg = readlet_star_meta_reader(r,GC_OBJECT(list,OBJECT(Do,OBJECT(Let,_Zdef)->arg)->args),1,e));
          unbind_I_meta_reader(r,_Zbind);
          Result = _Zdef;
          }
        else if ((OBJECT(ClaireBoolean,_oid_(((INHERIT(OWNER(_Zdef),Language._Call)) ? (((*Kernel.selector)(_Zdef) == _oid_(Core.write)) ? CTRUE: CFALSE): CFALSE)))) == CTRUE)
         { Variable * v1;
          { { Instruction *V_CC ;
              { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                _void_(_CL_obj->pname = gensym_void());
                _void_(_CL_obj->range = Kernel._any);
                add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              v1= (Variable *) V_CC;}
            GC_OBJECT(Variable,v1);}
          Variable * v2;
          { { Instruction *V_CC ;
              { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                _void_(_CL_obj->pname = gensym_void());
                _void_(_CL_obj->range = Kernel._any);
                add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              v2= (Variable *) V_CC;}
            GC_OBJECT(Variable,v2);}
          list * _Za = GC_OBJECT(list,OBJECT(Call,_Zdef)->args);
          list * _Zb1 = GC_OBJECT(list,bind_I_meta_reader(r,v1));
          list * _Zb2 = GC_OBJECT(list,bind_I_meta_reader(r,v2));
          OID  _Ze = GC_OID(nexts_meta_reader(r,e));
          Let_plus * x;
          { { Instruction *V_CC ;
              { Let_plus * _CL_obj = ((Let_plus *) GC_OBJECT(Let_plus,new_object_class(Language._Let_plus)));
                _void_(_CL_obj->var = v1);
                { Let * g0664 = _CL_obj; 
                  OID  g0665;
                  { Call_plus * _CL_obj = ((Call_plus *) GC_OBJECT(Call_plus,new_object_class(Language._Call_plus)));
                    update_property(Kernel.selector,
                      _CL_obj,
                      2,
                      Kernel._object,
                      (*(_Za))[1]);
                    _void_(_CL_obj->args = list::alloc(1,(*(_Za))[2]));
                    add_I_property(Kernel.instances,Language._Call_plus,11,_oid_(_CL_obj));
                    g0665 = _oid_(close_Instruction1(_CL_obj));
                    }
                  _void_(g0664->value = g0665);}
                { Let * g0666 = _CL_obj; 
                  OID  g0667;
                  { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                    { Do * g0668 = _CL_obj; 
                      list * g0669;
                      { OID v_bag;
                        GC_ANY(g0669= list::empty(Kernel._any));
                        ((list *) g0669)->addFast((OID)_Zdef);
                        { { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                            _void_(_CL_obj->var = v2);
                            _void_(_CL_obj->value = _Ze);
                            { Let * g0670 = _CL_obj; 
                              OID  g0671;
                              { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                                _void_(_CL_obj->args = list::alloc(Kernel._any,2,GC_OID(_oid_(Call_I_property(Core.write,list::alloc(3,(*(_Za))[1],
                                  (*(_Za))[2],
                                  _oid_(v1))))),_oid_(v2)));
                                add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
                                g0671 = _oid_(close_Instruction1(_CL_obj));
                                }
                              _void_(g0670->arg = g0671);}
                            add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
                            v_bag = _oid_(close_Instruction1(_CL_obj));
                            }
                          GC_OID(v_bag);}
                        ((list *) g0669)->addFast((OID)v_bag);}
                      _void_(g0668->args = g0669);}
                    add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
                    g0667 = _oid_(close_Instruction1(_CL_obj));
                    }
                  _void_(g0666->arg = g0667);}
                add_I_property(Kernel.instances,Language._Let_plus,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              x= (Let_plus *) V_CC;}
            GC_OBJECT(Let_plus,x);}
          unbind_I_meta_reader(r,_Zb2);
          unbind_I_meta_reader(r,_Zb1);
          Result = _oid_(x);
          }
        else Serror_integer1(165,((char*)"~S is illegal after a let"),list::alloc(1,_Zdef));
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// recursive construction of the tail of a Let*
//
// The c++ function for: readlet*(r:meta_reader,l:list,n:integer,e:keyword) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  readlet_star_meta_reader(meta_reader *r,list *l,int n,keyword *e) { 
    
    GC_BIND;
    { OID Result = 0;
      if ((CL_INT)n > (CL_INT)l->length)
       { if (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)','))))
         Result = readlet_meta_reader(cnext_meta_reader(r),e);
        else Result = nexts_meta_reader(r,e);
          }
      else { Variable * v = GC_OBJECT(Variable,extract_variable_any(GC_OID((*Language.var)((*(l))[n]))));
          list * _Zbind = GC_OBJECT(list,bind_I_meta_reader(r,v));
          Let * x;
          { { Instruction *V_CC ;
              { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                _void_(_CL_obj->var = v);
                _void_(_CL_obj->value = (*Kernel.arg)((*(l))[n]));
                _void_(_CL_obj->arg = readlet_star_meta_reader(r,l,((CL_INT)n+(CL_INT)1),e));
                add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              x= (Let *) V_CC;}
            GC_OBJECT(Let,x);}
          unbind_I_meta_reader(r,_Zbind);
          Result = _oid_(x);
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// reads a when expression
//
// The c++ function for: readwhen(r:meta_reader,e:keyword) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  readwhen_meta_reader(meta_reader *r,keyword *e) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  _Zdef = GC_OID(nexts_I_meta_reader3(r,Reader.in,integer_I_char(_char_(((unsigned char)',')))));
        if (INHERIT(OWNER(_Zdef),Language._Assign))
         { Variable * v = GC_OBJECT(Variable,extract_variable_any(GC_OID(OBJECT(Assign,_Zdef)->var)));
          list * _Zbind = GC_OBJECT(list,bind_I_meta_reader(r,v));
          OID  _Za = GC_OID(nexts_meta_reader(r,Reader._cl_else));
          When * x;
          { { Instruction *V_CC ;
              { When * _CL_obj = ((When *) GC_OBJECT(When,new_object_class(Language._When)));
                _void_(_CL_obj->var = v);
                _void_(_CL_obj->value = OBJECT(Assign,_Zdef)->arg);
                _void_(_CL_obj->arg = _Za);
                { When * g0672 = _CL_obj; 
                  OID  g0673;
                  if (wcl_start_ask_meta_reader1(r,firstc_meta_reader(r)) == CTRUE)
                   { unget_port2(GC_OBJECT(PortObject,r->fromp),_char_(((unsigned char)'>')));
                    g0673 = CNULL;
                    }
                  else if (boolean_I_any(stop_ask_integer(firstc_meta_reader(r))) == CTRUE)
                   g0673 = CNULL;
                  else g0673 = nexts_meta_reader(r,e);
                    _void_(g0672->other = g0673);}
                add_I_property(Kernel.instances,Language._When,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              x= (When *) V_CC;}
            GC_OBJECT(When,x);}
          unbind_I_meta_reader(r,_Zbind);
          Result = _oid_(x);
          }
        else Serror_integer1(165,((char*)"~S is illegal after a when"),list::alloc(1,_Zdef));
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// read an if
//
// The c++ function for: readif(r:meta_reader,e:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  readif_meta_reader(meta_reader *r,int e) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  _Za1 = GC_OID(nexte_meta_reader(r));
        OID  _Za2 = GC_OID(nexts_meta_reader(r,Reader._cl_else));
        If * _CL_obj = ((If *) GC_OBJECT(If,new_object_class(Language._If)));
        _void_(_CL_obj->test = _Za1);
        _void_(_CL_obj->arg = _Za2);
        { If * g0674 = _CL_obj; 
          OID  g0675;
          if (wcl_start_ask_meta_reader1(r,firstc_meta_reader(r)) == CTRUE)
           { unget_port2(GC_OBJECT(PortObject,r->fromp),_char_(((unsigned char)'>')));
            g0675 = Kernel.cfalse;
            }
          else if ((firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)',')))) || 
              (firstc_meta_reader(r) == e))
           g0675 = Kernel.cfalse;
          else { OID  x = GC_OID(nexte_meta_reader(r));
              if (x == _oid_(Reader._cl_if))
               g0675 = readif_meta_reader(r,e);
              else if (keyword_ask_any(x) == CTRUE)
               g0675 = nextstruct_meta_reader(r,OBJECT(keyword,x),Core.none);
              else g0675 = loopexp_meta_reader(r,x,Core.none,CFALSE);
                }
            _void_(g0674->other = g0675);}
        add_I_property(Kernel.instances,Language._If,11,_oid_(_CL_obj));
        Result = _oid_(close_Instruction1(_CL_obj));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// reads a member_of
//
// The c++ function for: readcase(r:meta_reader,e:keyword) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  readcase_meta_reader(meta_reader *r,keyword *e) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { OID Result = 0;
      { OID  _Zv = GC_OID(nexte_meta_reader(r));
        if (skipc_I_meta_reader(r) != ((OID)integer_I_char(_char_(((unsigned char)'(')))))
         Serror_integer1(166,((char*)"Missing ( after case ~S"),list::alloc(1,_Zv));
        { Case * _Zx;
          { { Instruction *V_CC ;
              { Case * _CL_obj = ((Case *) GC_OBJECT(Case,new_object_class(Language._Case)));
                _void_(_CL_obj->var = _Zv);
                _void_(_CL_obj->args = list::empty());
                add_I_property(Kernel.instances,Language._Case,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              _Zx= (Case *) V_CC;}
            GC_OBJECT(Case,_Zx);}
          OID  _Zt = _oid_(Kernel._any);
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while ((firstc_meta_reader(r) != integer_I_char(_char_(((unsigned char)')')))))
            { GC_LOOP;
              next_meta_reader(r);
              GC__OID(_Zt = _oid_(extract_type_any(GC_OID(nexte_meta_reader(r)))), 1);
              _void_(_Zx->args = GC_OBJECT(list,GC_OBJECT(list,_Zx->args)->addFast((OID)_Zt))->addFast((OID)GC_OID(nexts_meta_reader(r,Core.none))));
              if ((boolean_I_any(stop_ask_integer(firstc_meta_reader(r))) != CTRUE) && 
                  (boolean_I_any(stop_ask_integer(((CL_INT)skipc_meta_reader(r)))) != CTRUE))
               Serror_integer1(167,((char*)"Missing ) or , after ~S"),list::alloc(1,_oid_(_Zx)));
              GC_UNLOOP;POP_SIGNAL;}
            }
          next_meta_reader(r);
          if ((e != Core.none) && 
              ((boolean_I_any(stop_ask_integer(((CL_INT)skipc_meta_reader(r)))) != CTRUE) && 
                (nexte_meta_reader(r) != _oid_(e))))
           Serror_integer1(161,((char*)"Missing ~S after ~S"),GC_OBJECT(list,list::alloc(2,_oid_(e),_oid_(_Zx))));
          Result = _oid_(_Zx);
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// if the expression begins with "{"
//
// The c++ function for: readset(r:meta_reader,%a1:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  readset_meta_reader(meta_reader *r,OID _Za1) { 
    
    GC_BIND;
    { OID Result = 0;
      if (equal(_Za1,r->curly) == CTRUE)
       { next_meta_reader(r);
        Result = _oid_(Kernel.emptySet);
        }
      else { if (keyword_ask_any(_Za1) == CTRUE)
           _Za1= (GC_OID(nextstruct_meta_reader(r,OBJECT(keyword,_Za1),Core.none)));
          { OID  _Za2 = GC_OID(nexte_meta_reader(r));
            if (equal(_Za2,r->comma) == CTRUE)
             { set * V_CL0676;{ set * g0677UU;
                { set * u_bag = set::empty(Kernel.emptySet);
                  { CL_INT loop_handle = ClEnv->cHandle;
                    OID gc_local;
                    ITERATE(u);
                    bag *u_support;
                    u_support = GC_OBJECT(list,cons_any(_Za1,GC_OBJECT(list,OBJECT(list,nextseq_meta_reader(cnext_meta_reader(r),integer_I_char(_char_(((unsigned char)'}'))))))));
                    for (START(u_support); NEXT(u);)
                    { GC_LOOP;
                      u_bag->addFast((OID)GC_OID(dereference_any(u)));
                      GC_UNLOOP; POP_SIGNAL;}
                    }
                  g0677UU = GC_OBJECT(set,u_bag);
                  }
                V_CL0676 = cast_I_set1(g0677UU,Kernel.emptySet);
                }
              
              Result=_oid_(V_CL0676);}
            else if (equal(_Za2,r->curly) == CTRUE)
             { next_meta_reader(r);
              Result = _oid_(cast_I_set1(set::alloc(1,GC_OID(dereference_any(_Za1))),Kernel.emptySet));
              }
            else if (_Za2 == _oid_(Reader.in))
             { Variable * v = GC_OBJECT(Variable,extract_variable_any(_Za1));
              Select * _CL_obj = ((Select *) GC_OBJECT(Select,new_object_class(Language._Select)));
              _void_(_CL_obj->var = v);
              _void_(_CL_obj->set_arg = nexte_meta_reader(r));
              { Iteration * g0678 = _CL_obj; 
                OID  g0679;
                { list * _Zbind = GC_OBJECT(list,bind_I_meta_reader(r,v));
                  OID  x;
                  { if (equal(GC_OID(nexte_meta_reader(r)),GC_OID(Reader.OR->value)) != CTRUE)
                     Serror_integer1(168,((char*)"Missing | in selection"),Kernel.nil);
                    else x = nexts_I_meta_reader2(r,integer_I_char(_char_(((unsigned char)'}'))));
                      GC_OID(x);}
                  unbind_I_meta_reader(r,_Zbind);
                  g0679 = x;
                  }
                _void_(g0678->arg = g0679);}
              add_I_property(Kernel.instances,Language._Select,11,_oid_(_CL_obj));
              Result = _oid_(close_Instruction1(_CL_obj));
              }
            else if (equal(_Za2,Reader.OR->value) == CTRUE)
             { Variable * v = GC_OBJECT(Variable,extract_variable_any(GC_OID(nexts_I_meta_reader1(r,Reader.in))));
              list * _Zbind = GC_OBJECT(list,bind_I_meta_reader(r,v));
              Image * res;
              { { Instruction *V_CC ;
                  { Image * _CL_obj = ((Image *) GC_OBJECT(Image,new_object_class(Language._Image)));
                    _void_(_CL_obj->var = v);
                    _void_(_CL_obj->set_arg = nexts_I_meta_reader2(r,integer_I_char(_char_(((unsigned char)'}')))));
                    _void_(_CL_obj->arg = substitution_any(_Za1,v,_oid_(v)));
                    add_I_property(Kernel.instances,Language._Image,11,_oid_(_CL_obj));
                    V_CC = close_Instruction1(_CL_obj);
                    }
                  res= (Image *) V_CC;}
                GC_OBJECT(Image,res);}
              unbind_I_meta_reader(r,_Zbind);
              Result = _oid_(res);
              }
            else if (operation_ask_any(_Za2) == CTRUE)
             Result = readset_meta_reader(r,GC_OID(loopexp_meta_reader(r,GC_OID(combine_any(_Za1,_Za2,GC_OID(nexte_meta_reader(r)))),Core.none,CFALSE)));
            else Serror_integer1(169,((char*)"Missing separation between ~S and ~S"),GC_OBJECT(list,list::alloc(2,_Za1,_Za2)));
              }
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: dereference(x:any) [NEW_ALLOC]
CL_EXPORT OID  dereference_any(OID x) { 
    { OID Result = 0;
      if (INHERIT(OWNER(x),Kernel._unbound_symbol))
       Serror_integer1(170,((char*)"Cannot use ~S in a set constant"),list::alloc(1,x));
      else if (INHERIT(OWNER(x),Language._Variable))
       Serror_integer1(170,((char*)"Cannot use a variable (~S) in a set constant"),list::alloc(1,x));
      else Result = OPT_EVAL(x);
        POP_SIGNAL; return (Result);}
    }
  


// reads a sequence of exp. Must end with a e = ) | ] | }
//
// The c++ function for: nextseq(r:meta_reader,e:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  nextseq_meta_reader(meta_reader *r,int e) { 
    
    GC_BIND;
    { OID Result = 0;
      if (firstc_meta_reader(r) == e)
       { next_meta_reader(r);
        Result = _oid_(list::empty());
        }
      else { OID  x = GC_OID(nexts_meta_reader(r,Core.none));
          if ((firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)'\n')))) && 
              (r->toplevel == CTRUE))
           skipc_meta_reader(r);
          if (firstc_meta_reader(r) == e)
           { next_meta_reader(r);
            Result = _oid_(list::alloc(1,x));
            }
          else if (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)','))))
           Result = _oid_(cons_any(x,GC_OBJECT(list,OBJECT(list,nextseq_meta_reader(cnext_meta_reader(r),e)))));
          else Serror_integer1(171,((char*)"Read the character ~S inside a sequence"),list::alloc(1,_oid_(char_I_integer(firstc_meta_reader(r)))));
            }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// read the next block: a sequence of exp. Must end with a e = ) | ] | }
//
// The c++ function for: readblock(r:meta_reader,x:any,e:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  readblock_meta_reader(meta_reader *r,OID x,int e) { 
    
    GC_BIND;
    skipc_meta_reader(r);
    { OID Result = 0;
      if (equal(x,r->paren) == CTRUE)
       Result = _oid_(list::empty());
      else if (wcl_start_ask_meta_reader1(r,firstc_meta_reader(r)) == CTRUE)
       Result = Do_I_any(x,GC_OID(readblock_meta_reader(r,GC_OID(read_wcl_meta_reader1(r)),e)));
      else if (firstc_meta_reader(r) == e)
       { cnext_meta_reader(r);
        Result = x;
        }
      else if (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)','))))
       Result = Do_I_any(x,GC_OID(readblock_meta_reader(r,GC_OID(nexte_meta_reader(cnext_meta_reader(r))),e)));
      else if (boolean_I_any(stop_ask_integer(firstc_meta_reader(r))) == CTRUE)
       Serror_integer1(172,((char*)"The sequence ...~S must end with ~A"),list::alloc(2,x,_oid_(char_I_integer(e))));
      else if (x == _oid_(Reader._cl_if))
       Result = readblock_meta_reader(r,GC_OID(readif_meta_reader(r,e)),e);
      else if (x == _oid_(Reader._cl_Zif))
       { If * _Zi = GC_OBJECT(If,OBJECT(If,readif_meta_reader(r,e)));
        { OID  g0680UU;
          { if (boolean_I_any(eval_any(GC_OID(_Zi->test))) == CTRUE)
             g0680UU = _Zi->arg;
            else g0680UU = _Zi->other;
              GC_OID(g0680UU);}
          Result = readblock_meta_reader(r,g0680UU,e);
          }
        }
      else if (x == _oid_(Reader._cl_else))
       Serror_integer1(173,((char*)"Expression starting with else"),Kernel.nil);
      else if (keyword_ask_any(x) == CTRUE)
       Result = readblock_meta_reader(r,GC_OID(nextstruct_meta_reader(r,OBJECT(keyword,x),Core.none)),e);
      else { OID  y = GC_OID(loopexp_meta_reader(r,x,Core.none,CFALSE));
          if (INHERIT(OWNER(y),Language._Call_star))
           _void_(OBJECT(ClaireObject,y)->isa = Language._Call);
          Result = readblock_meta_reader(r,y,e);
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: Do!(x:any,y:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  Do_I_any(OID x,OID y) { 
    
    GC_BIND;
    { OID Result = 0;
      if ((INHERIT(OWNER(x),Language._Do)) && 
          (INHERIT(OWNER(y),Language._Do)))
       { put_property2(Core.args,OBJECT(ClaireObject,x),GC_OID(_oid_(append_list(GC_OBJECT(list,OBJECT(list,(*Core.args)(x))),GC_OBJECT(list,OBJECT(list,(*Core.args)(y)))))));
        Result = x;
        }
      else if (INHERIT(OWNER(y),Language._Do))
       { _void_(OBJECT(Do,y)->args = add_at_list(GC_OBJECT(list,OBJECT(Do,y)->args),1,x));
        Result = y;
        }
      else if (INHERIT(OWNER(x),Language._Do))
       { GC_OBJECT(list,OBJECT(Do,x)->args)->addFast((OID)y);
        Result = x;
        }
      else { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
          _void_(_CL_obj->args = list::alloc(Kernel._any,2,x,y));
          add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// extract the type from a list<X> expression
// The c++ function for: extract_of_type(x:Call) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT ClaireType * extract_of_type_Call(Call *x) { 
    
    GC_BIND;
    { ClaireType *Result ;
      { list * l = GC_OBJECT(list,x->args);
        if ((CL_INT)l->length > (CL_INT)2)
         { OID  y = (*(l))[3];
          if (INHERIT(OWNER(y),Language._List))
           { OID  z = GC_OID((*(OBJECT(Construct,y)->args))[1]);
            if (INHERIT(OWNER(z),Language._Set))
             Result = extract_type_any(GC_OID((*(OBJECT(Construct,z)->args))[1]));
            else Result = Kernel._any;
              }
          else Result = Kernel._any;
            }
        else Result = Kernel._any;
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// if the expression is a call -------------------------------------------
//
// The c++ function for: readcall(r:meta_reader,x:any,t:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  readcall_meta_reader(meta_reader *r,OID x,OID t) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  l = GC_OID(nextseq_meta_reader(cnext_meta_reader(r),integer_I_char(_char_(((unsigned char)')')))));
        if (x == _oid_(Reader.PRINTF))
         { Printf * _CL_obj = ((Printf *) GC_OBJECT(Printf,new_object_class(Language._Printf)));
          store_object(_CL_obj,
            2,
            Kernel._object,
            l,
            CFALSE);
          add_I_property(Kernel.instances,Language._Printf,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if (x == _oid_(Kernel._error))
         { Error * _CL_obj = ((Error *) GC_OBJECT(Error,new_object_class(Language._Error)));
          store_object(_CL_obj,
            2,
            Kernel._object,
            l,
            CFALSE);
          add_I_property(Kernel.instances,Language._Error,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if (x == _oid_(Reader.assert))
         { Assert * _CL_obj = ((Assert *) GC_OBJECT(Assert,new_object_class(Language._Assert)));
          store_object(_CL_obj,
            2,
            Kernel._object,
            l,
            CFALSE);
          _void_(_CL_obj->index = r->nb_line);
          _void_(_CL_obj->external = r->external);
          add_I_property(Kernel.instances,Language._Assert,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if (x == _oid_(Reader.trace))
         { Trace * _CL_obj = ((Trace *) GC_OBJECT(Trace,new_object_class(Language._Trace)));
          store_object(_CL_obj,
            2,
            Kernel._object,
            l,
            CFALSE);
          add_I_property(Kernel.instances,Language._Trace,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if (x == _oid_(Reader._cl_branch))
         { Branch * _CL_obj = ((Branch *) GC_OBJECT(Branch,new_object_class(Language._Branch)));
          store_object(_CL_obj,
            2,
            Kernel._object,
            l,
            CFALSE);
          add_I_property(Kernel.instances,Language._Branch,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if (x == _oid_(Reader.quote))
         { Quote * _CL_obj = ((Quote *) GC_OBJECT(Quote,new_object_class(Language._Quote)));
          { Quote * g0682 = _CL_obj; 
            OID  g0683;
            if (boolean_I_any(l) == CTRUE)
             g0683 = (*Kernel.nth)(l,
              ((OID)1));
            else g0683 = Kernel.cfalse;
              _void_(g0682->arg = g0683);}
          add_I_property(Kernel.instances,Language._Quote,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if (x == _oid_(Kernel._tuple))
         { Tuple * _CL_obj = ((Tuple *) GC_OBJECT(Tuple,new_object_class(Language._Tuple)));
          store_object(_CL_obj,
            2,
            Kernel._object,
            l,
            CFALSE);
          add_I_property(Kernel.instances,Language._Tuple,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if (x == _oid_(Kernel._list))
         { List * _CL_obj = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
          store_object(_CL_obj,
            2,
            Kernel._object,
            l,
            CFALSE);
          add_I_property(Kernel.instances,Language._List,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if ((INHERIT(OWNER(x),Language._Call)) && ((*(OBJECT(Call,x)->args))[1] == _oid_(Kernel._list)))
         { List * _CL_obj = ((List *) GC_OBJECT(List,new_object_class(Language._List)));
          _void_(_CL_obj->of = extract_of_type_Call(OBJECT(Call,x)));
          store_object(_CL_obj,
            2,
            Kernel._object,
            l,
            CFALSE);
          add_I_property(Kernel.instances,Language._List,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if ((INHERIT(OWNER(x),Language._Call)) && ((*(OBJECT(Call,x)->args))[1] == _oid_(Kernel._array)))
         { Array * _CL_obj = ((Array *) GC_OBJECT(Array,new_object_class(Language._Array)));
          _void_(_CL_obj->of = extract_of_type_Call(OBJECT(Call,x)));
          store_object(_CL_obj,
            2,
            Kernel._object,
            l,
            CFALSE);
          add_I_property(Kernel.instances,Language._Array,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if ((INHERIT(OWNER(x),Language._Call)) && ((*(OBJECT(Call,x)->args))[1] == _oid_(Kernel._set)))
         { Set * _CL_obj = ((Set *) GC_OBJECT(Set,new_object_class(Language._Set)));
          _void_(_CL_obj->of = extract_of_type_Call(OBJECT(Call,x)));
          store_object(_CL_obj,
            2,
            Kernel._object,
            l,
            CFALSE);
          add_I_property(Kernel.instances,Language._Set,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if ((INHERIT(OWNER(x),Kernel._class)) && 
            (INHERIT(OBJECT(ClaireClass,x),Language._Macro)))
         { ClaireObject * o = GC_OBJECT(ClaireObject,new_object_class(OBJECT(ClaireClass,x)));
          put_property2(Core.args,o,l);
          (*Language.init_location)(_oid_(o));
          Result = _oid_(o);
          }
        else if (x == _oid_(Kernel._set))
         { Set * _CL_obj = ((Set *) GC_OBJECT(Set,new_object_class(Language._Set)));
          store_object(_CL_obj,
            2,
            Kernel._object,
            l,
            CFALSE);
          add_I_property(Kernel.instances,Language._Set,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if ((x == _oid_(Reader.RETURN)) || 
            (x == _oid_(Reader.BREAK)))
         { Return * _CL_obj = ((Return *) GC_OBJECT(Return,new_object_class(Language._Return)));
          { Return * g0684 = _CL_obj; 
            OID  g0685;
            if (boolean_I_any(l) == CTRUE)
             g0685 = (*Kernel.nth)(l,
              ((OID)1));
            else g0685 = Kernel.ctrue;
              _void_(g0684->arg = g0685);}
          add_I_property(Kernel.instances,Language._Return,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if (INHERIT(OWNER(x),Kernel._class))
         { { ClaireBoolean * g0686I;
            { OID  g0687UU;
              { ClaireBoolean * V_CL0688;{ OID  g0689UU;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    OID gc_local;
                    ITERATE(y);
                    g0689UU= Kernel.cfalse;
                    bag *y_support;
                    y_support = GC_OBJECT(bag,enumerate_any(l));
                    for (START(y_support); NEXT(y);)
                    { GC_LOOP;
                      { ClaireBoolean * g0690I;
                        { OID  g0691UU;
                          if (INHERIT(OWNER(y),Language._Call))
                           { if (OBJECT(Call,y)->selector == Kernel._equal)
                             { ((*(GC_OBJECT(list,OBJECT(Call,y)->args)))[1]=_oid_(make_a_property_any(GC_OID((*(OBJECT(Call,y)->args))[1]))));
                              g0691UU = Kernel.ctrue;
                              }
                            else g0691UU = Kernel.cfalse;
                              }
                          else g0691UU = Kernel.cfalse;
                            g0690I = not_any(g0691UU);
                          }
                        
                        if (g0690I == CTRUE) { GC_UNLOOP;g0689UU = Kernel.ctrue;
                            ClEnv->cHandle = loop_handle;break;}
                          }
                      GC_UNLOOP; POP_SIGNAL;}
                    }
                  V_CL0688 = not_any(g0689UU);
                  }
                
                g0687UU=_oid_(V_CL0688);}
              g0686I = not_any(g0687UU);
              }
            
            if (g0686I == CTRUE) { list * l2 = OBJECT(ClaireClass,x)->params;
                CL_INT  n = ((INHERIT(l2->isa,Kernel._list)) ?
                  l2->length :
                  0 );
                if ((*Kernel.length)(l) == ((OID)n))
                 { list * V_CL0692;{ list * i_bag = list::empty(Kernel.emptySet);
                    { CL_INT  i = 1;
                      CL_INT  g0681 = n;
                      { CL_INT loop_handle = ClEnv->cHandle;
                        OID gc_local;
                        while (((CL_INT)i <= (CL_INT)g0681))
                        { GC_LOOP;
                          { OID  g0693UU;
                            { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                _void_(_CL_obj->selector = Kernel._equal);
                                _void_(_CL_obj->args = list::alloc(2,(*(l2))[i],GC_OID((*Kernel.nth)(l,
                                  ((OID)i)))));
                                add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                                g0693UU = _oid_(close_Instruction1(_CL_obj));
                                }
                              GC_OID(g0693UU);}
                            i_bag->addFast((OID)g0693UU);
                            }
                          ++i;
                          GC_UNLOOP;POP_SIGNAL;}
                        }
                      }
                    V_CL0692 = GC_OBJECT(list,i_bag);
                    }
                  
                  l=_oid_(V_CL0692);}
                else Serror_integer1(174,((char*)"Wrong instantiation list ~S(~S..."),GC_OBJECT(list,list::alloc(2,x,GC_OID(_oid_(list::alloc(1,l))))));
                  }
              }
          { Definition * _CL_obj = ((Definition *) GC_OBJECT(Definition,new_object_class(Language._Definition)));
            update_property(Kernel.arg,
              _CL_obj,
              2,
              Kernel._object,
              x);
            store_object(_CL_obj,
              3,
              Kernel._object,
              l,
              CFALSE);
            add_I_property(Kernel.instances,Language._Definition,11,_oid_(_CL_obj));
            Result = _oid_(close_Instruction1(_CL_obj));
            }
          }
        else { ClaireBoolean * g0694I;
          { ClaireBoolean *v_or;
            { v_or = inherit_ask_class(OWNER(x),Language._Variable);
              if (v_or == CTRUE) g0694I =CTRUE; 
              else { { OID  g0695UU;
                  if (INHERIT(OWNER(x),Core._global_variable))
                   g0695UU = _oid_(OBJECT(global_variable,x)->range);
                  else g0695UU = Kernel.cfalse;
                    v_or = boolean_I_any(g0695UU);
                  }
                if (v_or == CTRUE) g0694I =CTRUE; 
                else g0694I = CFALSE;}
              }
            }
          
          if (g0694I == CTRUE) Result = _oid_(Call_I_property(Core.call,cons_any(x,GC_OBJECT(list,((boolean_I_any(l) == CTRUE) ?
              OBJECT(list,l) :
              list::alloc(1,_oid_(ClEnv)) )))));
            else { property * p = make_a_property_any(x);
            OID  l2;
            { if (boolean_I_any(l) == CTRUE)
               l2 = l;
              else l2 = _oid_(list::alloc(1,_oid_(ClEnv)));
                GC_OID(l2);}
            if (t != CNULL)
             { Super * _CL_obj = ((Super *) GC_OBJECT(Super,new_object_class(Language._Super)));
              _void_(_CL_obj->selector = p);
              update_property(Language.cast_to,
                _CL_obj,
                3,
                Kernel._object,
                t);
              store_object(_CL_obj,
                4,
                Kernel._object,
                l2,
                CFALSE);
              add_I_property(Kernel.instances,Language._Super,11,_oid_(_CL_obj));
              Result = _oid_(close_Instruction1(_CL_obj));
              }
            else Result = _oid_(Call_I_property(p,OBJECT(list,l2)));
              }
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// reads a definition (CLAIRE2 syntax)   - x and y are two expressions that have been read
//
// The c++ function for: nextdefinition(r:meta_reader,x:any,y:any,old?:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  nextdefinition_meta_reader(meta_reader *r,OID x,OID y,ClaireBoolean *old_ask) { 
    
    GC_BIND;
    _void_(r->last_arrow = CFALSE);
    { OID Result = 0;
      if (equal(y,Reader.triangle->value) == CTRUE)
       Result = _oid_(nextDefclass_meta_reader(cnext_meta_reader(r),x,old_ask));
      else if (y == _oid_(Reader.L_))
       { ClaireBoolean * table_ask = ((INHERIT(OWNER(x),Language._Call)) ?
          ((OBJECT(Call,x)->selector == Kernel.nth) ? (((INHERIT(OWNER((*(OBJECT(Call,x)->args))[1]),Kernel._unbound_symbol)) || 
              (INHERIT(OWNER((*(OBJECT(Call,x)->args))[1]),Kernel._table))) ? CTRUE: CFALSE): CFALSE) :
          CFALSE );
        OID  z = GC_OID(nexte_meta_reader(r));
        OID  w = GC_OID(nexte_meta_reader(r));
        if ((table_ask == CTRUE) ? (w == _oid_(Reader.L__equal)) : ((equal(w,Reader.arrow->value) == CTRUE) || 
            (w == _oid_(Reader._equal_sup))))
         ;else Serror_integer1(149,((char*)"Wrong keyword (~S) after ~S"),list::alloc(2,w,z));
          Result = nextmethod_meta_reader(r,
          x,
          z,
          table_ask,
          old_ask,
          equal(w,_oid_(Reader._equal_sup)));
        }
      else if (y == _oid_(Reader.L_L_))
       { if (INHERIT(OWNER(x),Language._Call))
         { OID  ru = GC_OID(nexte_meta_reader(r));
          OID  z = GC_OID(nexts_meta_reader(r,Reader._equal_sup));
          Defrule * _CL_obj = ((Defrule *) GC_OBJECT(Defrule,new_object_class(Language._Defrule)));
          _void_(_CL_obj->ident = OBJECT(Call,x)->selector->name);
          _void_(_CL_obj->args = OBJECT(Call,x)->args);
          _void_(_CL_obj->arg = z);
          { Defrule * g0696 = _CL_obj; 
            OID  g0697;
            if (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)')'))))
             { next_meta_reader(r);
              g0697 = Core.nil->value;
              }
            else g0697 = readblock_meta_reader(r,GC_OID(nexte_meta_reader(r)),integer_I_char(_char_(((unsigned char)')'))));
              _void_(g0696->body = g0697);}
          add_I_property(Kernel.instances,Language._Defrule,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else Result = nextinst_meta_reader(r,x);
          }
      else if ((equal(y,Reader.arrow->value) == CTRUE) || 
          (y == _oid_(Reader._equal_sup)))
       { _void_(r->last_arrow = equal(y,_oid_(Reader._equal_sup)));
        if (should_trace_ask_module1(Reader.it,3) == CTRUE)
         mtformat_module1(Reader.it,((char*)"---- note: ~S - method's range is assumed to be void \n"),3,list::alloc(1,x));
        else ;Result = nextmethod_meta_reader(r,
          x,
          _oid_(Kernel._void),
          CFALSE,
          old_ask,
          equal(y,_oid_(Reader._equal_sup)));
        }
      else if ((y == _oid_(Reader.L__equal)) && 
          (INHERIT(OWNER(x),Language._Vardef)))
       { Defobj * _CL_obj = ((Defobj *) GC_OBJECT(Defobj,new_object_class(Language._Defobj)));
        _void_(_CL_obj->ident = OBJECT(Variable,x)->pname);
        _void_(_CL_obj->arg = Core._global_variable);
        _void_(_CL_obj->args = list::alloc(2,GC_OID(_oid_(Call_I_property(Kernel._equal,list::alloc(2,_oid_(Kernel.range),GC_OID(_oid_(extract_type_any(GC_OID((*Kernel.range)(x))))))))),GC_OID(_oid_(Call_I_property(Kernel._equal,list::alloc(2,_oid_(Kernel.value),GC_OID(nexte_meta_reader(r))))))));
        add_I_property(Kernel.instances,Language._Defobj,11,_oid_(_CL_obj));
        Result = _oid_(close_Instruction1(_CL_obj));
        }
      else { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
          _void_(_CL_obj->args = list::alloc(Kernel._any,2,x,y));
          add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: nextmethod(r:meta_reader,x:any,y:any,table?:boolean,old?:boolean,inl?:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  nextmethod_meta_reader(meta_reader *r,OID x,OID y,ClaireBoolean *table_ask,ClaireBoolean *old_ask,ClaireBoolean *inl_ask) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  n = skipc_meta_reader(r);
        OID  z;
        { if (old_ask == CTRUE)
           z = readblock_meta_reader(r,GC_OID(nexte_meta_reader(r)),integer_I_char(_char_(((unsigned char)']'))));
          else if (n == ((OID)integer_I_char(_char_(((unsigned char)'(')))))
           { if (r->toplevel == CTRUE)
             z = nexts_meta_reader(r,Core.none);
            else z = readblock_meta_reader(r,GC_OID(nexte_meta_reader(cnext_meta_reader(r))),integer_I_char(_char_(((unsigned char)')'))));
              }
          else z = nexte_meta_reader(r);
            GC_OID(z);}
        Defmethod * rs;
        { { Instruction *V_CC ;
            { Defmethod * _CL_obj = ((Defmethod *) GC_OBJECT(Defmethod,new_object_class(Language._Defmethod)));
              update_property(Kernel.arg,
                _CL_obj,
                2,
                Kernel._object,
                x);
              _void_(_CL_obj->set_arg = y);
              { Defmethod * g0698 = _CL_obj; 
                OID  g0699;
                if (z == _oid_(Reader._cl_let))
                 g0699 = readlet_meta_reader(r,Reader.None);
                else g0699 = z;
                  _void_(g0698->body = g0699);}
              _void_(_CL_obj->inline_ask = _oid_(inl_ask));
              add_I_property(Kernel.instances,Language._Defmethod,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            rs= (Defmethod *) V_CC;}
          GC_OBJECT(Defmethod,rs);}
        if (table_ask == CTRUE)
         _void_(rs->isa = Language._Defarray);
        Result = _oid_(rs);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// reads an instantiation
//
// The c++ function for: nextinst(r:meta_reader,x:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  nextinst_meta_reader(meta_reader *r,OID x) { 
    
    GC_BIND;
    { OID Result = 0;
      if (INHERIT(OWNER(x),Language._Variable))
       { Defobj * _CL_obj = ((Defobj *) GC_OBJECT(Defobj,new_object_class(Language._Defobj)));
        _void_(_CL_obj->ident = OBJECT(Variable,x)->pname);
        _void_(_CL_obj->arg = Core._global_variable);
        { Definition * g0700 = _CL_obj; 
          list * g0701;
          { OID v_bag;
            GC_ANY(g0701= list::empty(Kernel.emptySet));
            { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(_CL_obj->selector = Kernel._equal);
                _void_(_CL_obj->args = list::alloc(2,_oid_(Kernel.range),GC_OID(_oid_(extract_type_any(GC_OID(_oid_(OBJECT(Variable,x)->range)))))));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                v_bag = _oid_(close_Instruction1(_CL_obj));
                }
              GC_OID(v_bag);}
            ((list *) g0701)->addFast((OID)v_bag);
            { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(_CL_obj->selector = Kernel._equal);
                _void_(_CL_obj->args = list::alloc(2,_oid_(Kernel.value),GC_OID(nexte_meta_reader(r))));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                v_bag = _oid_(close_Instruction1(_CL_obj));
                }
              GC_OID(v_bag);}
            ((list *) g0701)->addFast((OID)v_bag);}
          _void_(g0700->args = g0701);}
        add_I_property(Kernel.instances,Language._Defobj,11,_oid_(_CL_obj));
        Result = _oid_(close_Instruction1(_CL_obj));
        }
      else if (INHERIT(OWNER(x),Language._Call))
       { OID  ru = GC_OID(nexte_meta_reader(r));
        OID  z = GC_OID(nexts_meta_reader(r,Reader._equal_sup));
        Defrule * _CL_obj = ((Defrule *) GC_OBJECT(Defrule,new_object_class(Language._Defrule)));
        _void_(_CL_obj->ident = OBJECT(Call,x)->selector->name);
        _void_(_CL_obj->args = OBJECT(Call,x)->args);
        _void_(_CL_obj->arg = z);
        { Defrule * g0702 = _CL_obj; 
          OID  g0703;
          if (firstc_meta_reader(r) == integer_I_char(_char_(((unsigned char)')'))))
           { next_meta_reader(r);
            g0703 = Core.nil->value;
            }
          else g0703 = readblock_meta_reader(r,GC_OID(nexte_meta_reader(r)),integer_I_char(_char_(((unsigned char)')'))));
            _void_(g0702->body = g0703);}
        add_I_property(Kernel.instances,Language._Defrule,11,_oid_(_CL_obj));
        Result = _oid_(close_Instruction1(_CL_obj));
        }
      else { OID  y = GC_OID(nexte_meta_reader(r));
          if ((INHERIT(OWNER(x),Core._global_variable)) && (y == CNULL))
           Result = y;
          else if ((INHERIT(OWNER(y),Language._Definition)) && (INHERIT(OBJECT(Definition,y)->arg,Kernel._thing)))
           { Defobj * _CL_obj = ((Defobj *) GC_OBJECT(Defobj,new_object_class(Language._Defobj)));
            _void_(_CL_obj->ident = extract_symbol_any(x));
            update_property(Kernel.arg,
              _CL_obj,
              2,
              Kernel._object,
              GC_OID((*Kernel.arg)(y)));
            store_object(_CL_obj,
              3,
              Kernel._object,
              (*Core.args)(y),
              CFALSE);
            add_I_property(Kernel.instances,Language._Defobj,11,_oid_(_CL_obj));
            Result = _oid_(close_Instruction1(_CL_obj));
            }
          else { Defobj * _CL_obj = ((Defobj *) GC_OBJECT(Defobj,new_object_class(Language._Defobj)));
              _void_(_CL_obj->ident = extract_symbol_any(x));
              _void_(_CL_obj->arg = Core._global_variable);
              { Definition * g0704 = _CL_obj; 
                list * g0705;
                { OID v_bag;
                  GC_ANY(g0705= list::empty(Kernel.emptySet));
                  { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(_CL_obj->selector = Kernel._equal);
                      _void_(_CL_obj->args = list::alloc(2,_oid_(Kernel.range),_oid_(Kernel.emptySet)));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                      v_bag = _oid_(close_Instruction1(_CL_obj));
                      }
                    GC_OID(v_bag);}
                  ((list *) g0705)->addFast((OID)v_bag);
                  { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(_CL_obj->selector = Kernel._equal);
                      _void_(_CL_obj->args = list::alloc(2,_oid_(Kernel.value),y));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                      v_bag = _oid_(close_Instruction1(_CL_obj));
                      }
                    GC_OID(v_bag);}
                  ((list *) g0705)->addFast((OID)v_bag);}
                _void_(g0704->args = g0705);}
              add_I_property(Kernel.instances,Language._Defobj,11,_oid_(_CL_obj));
              Result = _oid_(close_Instruction1(_CL_obj));
              }
            }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// reads a class Definition of the form C(p:t | p:t = v *)
// new in v2.5
// The c++ function for: nextDefclass(r:meta_reader,x:any,old?:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT Defclass * nextDefclass_meta_reader(meta_reader *r,OID x,ClaireBoolean *old_ask) { 
    
    GC_BIND;
    skipc_meta_reader(r);
    { Defclass *Result ;
      { OID  c = GC_OID(verify_any(_oid_(Kernel._class),GC_OID(read_ident_meta_reader1(r)),_oid_(Language._Defclass)));
        Defclass * y;
        { { Instruction *V_CC ;
            if (firstc_meta_reader(r) != integer_I_char(_char_(((unsigned char)'('))))
             { Defclass * _CL_obj = ((Defclass *) GC_OBJECT(Defclass,new_object_class(Language._Defclass)));
              update_property(Kernel.arg,
                _CL_obj,
                2,
                Kernel._object,
                c);
              _void_(_CL_obj->args = Kernel.nil);
              _void_(_CL_obj->forward_ask = CTRUE);
              add_I_property(Kernel.instances,Language._Defclass,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            else { OID  l = GC_OID(nextseq_meta_reader(cnext_meta_reader(r),integer_I_char(_char_(((unsigned char)')')))));
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(y1);
                  bag *y1_support;
                  y1_support = GC_OBJECT(bag,enumerate_any(l));
                  for (START(y1_support); NEXT(y1);)
                  { ClaireBoolean * g0706I;
                    { OID  g0707UU;
                      if (INHERIT(OWNER(y1),Language._Call))
                       g0707UU = _oid_(((OBJECT(Call,y1)->selector == Kernel._equal) ? ((INHERIT(OWNER((*(OBJECT(Call,y1)->args))[1]),Language._Vardef)) ? CTRUE: CFALSE): CFALSE));
                      else if (INHERIT(OWNER(y1),Language._Vardef))
                       g0707UU = Kernel.ctrue;
                      else g0707UU = Kernel.cfalse;
                        g0706I = not_any(g0707UU);
                      }
                    
                    if (g0706I == CTRUE) Serror_integer1(175,((char*)"Wrong form ~S in ~S(~S)"),list::alloc(3,y1,
                        c,
                        l));
                      }
                  }
                { Defclass * _CL_obj = ((Defclass *) GC_OBJECT(Defclass,new_object_class(Language._Defclass)));
                  update_property(Kernel.arg,
                    _CL_obj,
                    2,
                    Kernel._object,
                    c);
                  store_object(_CL_obj,
                    3,
                    Kernel._object,
                    l,
                    CFALSE);
                  _void_(_CL_obj->forward_ask = CFALSE);
                  add_I_property(Kernel.instances,Language._Defclass,11,_oid_(_CL_obj));
                  V_CC = close_Instruction1(_CL_obj);
                  }
                }
              y= (Defclass *) V_CC;}
          GC_OBJECT(Defclass,y);}
        list * lp = Kernel.nil;
        symbol * idt;
        if ((INHERIT(OWNER(x),Language._Call)) && (OBJECT(Call,x)->selector == Kernel.nth))
         { list * l = GC_OBJECT(list,OBJECT(Call,x)->args);
          if (INHERIT(OWNER((*(l))[1]),Kernel._class))
           lp= (OBJECT(list,(*(l))[2]));
          else { { CL_INT loop_handle = ClEnv->cHandle;
                bag *v_list; OID v_val;
                OID y2; CL_INT CLcount;
                v_list = cdr_list(l);
                 lp = v_list->clone();
                for (CLcount= 1; CLcount <= v_list->length; CLcount++)
                { y2 = (*(v_list))[CLcount];
                  v_val = _oid_(make_a_property_any(y2));
                  
                  (*((list *) lp))[CLcount] = v_val;}
                }
              GC_OBJECT(list,lp);}
            idt = extract_symbol_any((*(l))[1]);
          }
        else idt = extract_symbol_any(x);
          if ((old_ask == CTRUE) && 
            (skipc_meta_reader(r) != ((OID)integer_I_char(_char_(((unsigned char)']'))))))
         Serror_integer1(176,((char*)"Missing ] after ~S "),GC_OBJECT(list,list::alloc(1,_oid_(y))));
        else if (old_ask == CTRUE)
         next_meta_reader(r);
        _void_(y->ident = idt);
        _void_(y->params = lp);
        Result = y;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// end of file

/***** CLAIRE Compilation of file ./meta/file.cl 
         [version 3.5.0 / safety 5] *****/


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
CL_EXPORT OID  self_eval_delimiter(delimiter *self) { 
    next_meta_reader(Reader.reader);
    POP_SIGNAL; return (_void_(Serror_integer1(117,((char*)"Loose delimiter ~S in program"),list::alloc(1,_oid_(self)))));}
  


//<sb>
//<sb> add the register symbol
// a small useful function
// PORTABILITY WARNING: the following assumes newline is ^J (ASCII 10 dec)
// PORTABILITY WARNING: what about ^M (ASCII 13 dec)
//
// a small useful function
// The c++ function for: useless_c(r:integer) [0]
CL_EXPORT ClaireBoolean * useless_c_integer(CL_INT r) { 
    POP_SIGNAL; return (((r == (CL_INT )('\n')) ? CTRUE : ((r == (CL_INT )('\r')) ? CTRUE : ((r == (CL_INT )(' ')) ? CTRUE : ((r == Reader.reader->tab) ? CTRUE : CFALSE)))));}
  


// take care of PC format (10 + 13)
// The c++ function for: skipc(self:meta_reader) [SLOT_UPDATE]
CL_EXPORT OID  skipc_meta_reader(meta_reader *self) { 
    { CL_INT loop_handle = ClEnv->cHandle;
      while ((useless_c_integer(firstc_meta_reader(self)) == CTRUE))
      { { ClaireBoolean * b = ((firstc_meta_reader(self) == integer_I_char(_char_(((unsigned char)'\n')))) ? CTRUE : CFALSE);
          next_meta_reader(self);
          if ((b == CTRUE) && 
              (firstc_meta_reader(self) == integer_I_char(_char_(((unsigned char)'\r')))))
           next_meta_reader(self);
          }
        POP_SIGNAL;}
      }
    POP_SIGNAL; return (((OID)firstc_meta_reader(self)));}
  


// look for a meaningful termination char such as ) or ]
// The c++ function for: skipc!(r:meta_reader) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT OID  skipc_I_meta_reader(meta_reader *r) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  c = skipc_meta_reader(r);
        if (c == ((OID)integer_I_char(_char_(((unsigned char)';')))))
         { { CL_INT loop_handle = ClEnv->cHandle;
            while (((firstc_meta_reader(r) != r->eof) && 
                (firstc_meta_reader(r) != integer_I_char(_char_(((unsigned char)'\n'))))))
            { next_meta_reader(r);
              POP_SIGNAL;}
            }
          if (firstc_meta_reader(r) == r->eof)
           Result = Core._eof->value;
          else Result = skipc_I_meta_reader(r);
            }
        else if (c == ((OID)integer_I_char(_char_(((unsigned char)'/')))))
         { OID  x = GC_OID(read_ident_meta_reader1(r));
          if (Kernel._string == OWNER(x))
           Result = skipc_I_meta_reader(r);
          else Result = ((OID)integer_I_char(_char_(((unsigned char)'/'))));
            }
        else Result = c;
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: cnext(self:meta_reader) [SLOT_UPDATE+SAFE_RESULT]
CL_EXPORT meta_reader * cnext_meta_reader(meta_reader *self) { 
    next_meta_reader(self);
    POP_SIGNAL; return (self);}
  


// The c++ function for: findeol(self:meta_reader) [SLOT_UPDATE]
CL_EXPORT ClaireBoolean * findeol_meta_reader(meta_reader *self) { 
    { ClaireBoolean *Result ;
      { ClaireBoolean *v_or;
        { { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
              V_C= _oid_(CFALSE);
              while ((useless_c_integer(firstc_meta_reader(self)) == CTRUE))
              { if (firstc_meta_reader(self) == integer_I_char(_char_(((unsigned char)'\n'))))
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
CL_EXPORT OID  checkno_meta_reader(meta_reader *r,int n,OID y) { 
    { OID Result = 0;
      if (firstc_meta_reader(r) != n)
       Result = _oid_(r);
      else Serror_integer1(118,((char*)"Read wrong char ~S after ~S"),list::alloc(2,_oid_(char_I_integer(n)),y));
        POP_SIGNAL; return (Result);}
    }
  


// reads a keyword inside a control structure
//
// The c++ function for: verify(t:any,x:any,y:any) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  verify_any(OID t,OID x,OID y) { 
    { OID Result = 0;
      if (belong_to(x,t) == CTRUE)
       Result = x;
      else Serror_integer1(119,((char*)"Read ~S instead of a ~S in a ~S"),list::alloc(3,x,
          t,
          y));
        POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: self_print(self:syntax_error) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_syntax_error1_Reader(Reader_syntax_error *self) { 
    
    GC_BIND;
    princ_string(((char*)"Syntax error ["));
    print_any(((OID)self->code));
    princ_string(((char*)"]\n"));
    format_string(GC_STRING(self->cause),GC_OBJECT(list,self->args));
    GC_UNBIND; POP_SIGNAL;}
  


// prints a syntax error
//
// The c++ function for: Serror(c:integer,s:string,la:list) [NEW_ALLOC]
CL_EXPORT void  Serror_integer1(CL_INT c,char *s,list *la) { 
    
    GC_BIND;
    { Reader_syntax_error * _CL_obj = ((Reader_syntax_error *) GC_OBJECT(Reader_syntax_error,new_object_class(Reader._syntax_error)));
      _void_(_CL_obj->cause = s);
      _void_(_CL_obj->args = la);
      _void_(_CL_obj->code = c);
      close_exception(_CL_obj);
      }
    GC_UNBIND; POP_SIGNAL;}
  


//general_error(cause = "Syntax error [" /+ string!(c) /+ "] " /+ s, args = la))
// the reader-------------------------------------------------------------
//
// The c++ function for: reader_push(_CL_obj:void) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT void  reader_push_void1() { 
    
    GC_BIND;
    GC_OBJECT(list,OBJECT(list,Reader.READER_STACK->value))->addFast((OID)GC_OID(_oid_(copy_object(Reader.reader))));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: reader_pop(_CL_obj:void) [0]
CL_EXPORT void  reader_pop_void1() { 
    { meta_reader * y = OBJECT(meta_reader,last_list(OBJECT(list,Reader.READER_STACK->value)));
      meta_reader * r = Reader.reader;
      shrink_list(OBJECT(bag,Reader.READER_STACK->value),((CL_INT)OBJECT(bag,Reader.READER_STACK->value)->length-(CL_INT)1));
      memcpy(r, y, sizeof(meta_reader));
      }
    POP_SIGNAL;}
  


// The c++ function for: reader_reset(_CL_obj:void) [0]
CL_EXPORT void  reader_reset_void1() { 
    { CL_INT loop_handle = ClEnv->cHandle;
      while ((OBJECT(bag,Reader.READER_STACK->value)->length != 0))
      { reader_pop_void1();
        POP_SIGNAL;}
      }
    POP_SIGNAL;}
  


// variable handling -------------------------------------------------
// reads a variable
//
// The c++ function for: extract_variable(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT Variable * extract_variable_any(OID self) { 
    
    GC_BIND;
    { Variable *Result ;
      if ((INHERIT(OWNER(self),Language._Variable)) && (equal(get_symbol(OBJECT(Variable,self)->pname),self) != CTRUE))
       { _void_(OBJECT(Variable,self)->range = extract_type_any(GC_OID((*Kernel.range)(self))));
        Result = OBJECT(Variable,self);
        }
      else { Variable * v;
          { { Instruction *V_CC ;
              { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                _void_(_CL_obj->pname = extract_symbol_any(self));
                add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              v= (Variable *) V_CC;}
            GC_OBJECT(Variable,v);}
          _void_(Reader.reader->last_form = _oid_(v));
          Result = v;
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// create a variable and add it to the lexical environment
// The c++ function for: bind!(self:meta_reader,%v:Variable) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT list * bind_I_meta_reader(meta_reader *self,Variable *_Zv) { 
    _void_(_Zv->index = self->index);
    { list *Result ;
      { OID  value = get_symbol(_Zv->pname);
        _void_(self->index = ((CL_INT)self->index+(CL_INT)1));
        if ((CL_INT)self->index > (CL_INT)self->maxstack)
         _void_(self->maxstack = self->index);
        (Language._starvariable_index_star->value= ((OID)self->maxstack));
        put_symbol(_Zv->pname,_oid_(_Zv));
        Result = list::alloc(2,_oid_(_Zv),value);
        }
      POP_SIGNAL; return (Result);}
    }
  


// remove a variable from the lexical environment
//
// The c++ function for: unbind!(self:meta_reader,%first:list) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  unbind_I_meta_reader(meta_reader *self,list *_Zfirst) { 
    { OID Result = 0;
      { OID  var = (*(_Zfirst))[1];
        _void_(self->index = ((CL_INT)self->index-(CL_INT)1));
        Result = put_symbol(OBJECT(Variable,var)->pname,(*(_Zfirst))[2]);
        }
      POP_SIGNAL; return (Result);}
    }
  


// this function is called by the main and restores the reader in a good shape. Also
// closes the input port to free the associated file ! <yc>
// The c++ function for: mClaire/restore_state(self:meta_reader) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  restore_state_meta_reader(meta_reader *self) { 
    
    GC_BIND;
    if (_oid_(self->fromp) != Core.cl_stdin->value)
     fclose_port1(GC_OBJECT(PortObject,self->fromp));
    _void_(self->fromp = OBJECT(PortObject,Core.cl_stdin->value));
    _void_(self->index = 1);
    flush_port2(OBJECT(PortObject,Core.cl_stdin->value),(CL_INT )(' '));
    restore_state_void();
    GC_UNBIND; POP_SIGNAL;}
  


// *********************************************************************
// *   Part 2: Loading                                                 *
// *********************************************************************
// sload is the interactive version.
//
// The c++ function for: load_file(self:string,b:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  load_file_string(char *self,ClaireBoolean *b) { 
    
    GC_RESERVE(4);  // v3.3.39 optim !
    reader_push_void1();
    _void_(Reader.reader->index = 0);
    _void_(Reader.reader->maxstack = 0);
    _void_(Reader.reader->external = self);
    if (should_trace_ask_module1(Reader.it,3) == CTRUE)
     mtformat_module1(Reader.it,((char*)"---- [load CLAIRE file: ~A]\n"),3,list::alloc(1,_string_(self)));
    else ;{ PortObject * f = GC_OBJECT(PortObject,fopen_source_string1(self));
      CL_INT  start = ClEnv->base;
      CL_INT  top = ClEnv->index;
      OID  _staritem_star = CNULL;
      (ClEnv->base= ((OID)top));
      _void_(Reader.reader->fromp = f);
      _void_(Reader.reader->toplevel = CFALSE);
      if (Reader.PROCESS_EVAL_INSTRUCTIONS_ask->value != Kernel.ctrue)
       { ClaireHandler c_handle = ClaireHandler();
        if ERROR_IN 
        { _staritem_star= (GC_OID(readblock_port(f)));
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
        { c_handle.catchIt();_staritem_star= (CNULL);
          }
        else PREVIOUS_HANDLER;}
      else _staritem_star= (GC_OID(readblock_port(f)));
        { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((equal(_staritem_star,Core._eof->value) != CTRUE))
        { GC_LOOP;
          if (b == CTRUE)
           { princ_integer(Reader.reader->nb_line);
            princ_string(((char*)":"));
            print_any(_staritem_star);
            princ_string(((char*)"\n"));
            }
          index_jump_integer1(((CL_INT)top+(CL_INT)((CL_INT)Reader.reader->maxstack+(CL_INT)1)));
          if (should_trace_ask_module1(Reader.it,4) == CTRUE)
           mtformat_module1(Reader.it,((char*)"load_file -> ~S \n"),4,list::alloc(1,_staritem_star));
          else ;if (Kernel._string == OWNER(_staritem_star))
           { if ((OBJECT(ClaireBoolean,Language.NeedComment->value)) == CTRUE)
             { if (Language.LastComment->value != CNULL)
               (Language.LastComment->value= (*Kernel._7_plus)(GC_OID(Language.LastComment->value),
                GC_OID(_string_(append_string(((char*)"\n"),string_v(_staritem_star))))));
              else if ((CL_INT)LENGTH_STRING(string_v(_staritem_star)) > (CL_INT)0)
               (Language.LastComment->value= _staritem_star);
              }
            }
          else { (Language.LastComment->value= CNULL);
              { ClaireBoolean * g0708I;
                { ClaireBoolean *v_or;
                  { v_or = OBJECT(ClaireBoolean,Reader.PROCESS_EVAL_INSTRUCTIONS_ask->value);
                    if (v_or == CTRUE) g0708I =CTRUE; 
                    else { if (INHERIT(OWNER(_staritem_star),Language._Defobj))
                       v_or = unknown_ask_any(get_symbol(OBJECT(Defobj,_staritem_star)->ident));
                      else if (INHERIT(OWNER(_staritem_star),Language._Call))
                       v_or = ((OBJECT(Call,_staritem_star)->selector == Reader.load) ? CTRUE : ((OBJECT(Call,_staritem_star)->selector == Reader.use_module) ? CTRUE : CFALSE));
                      else if (INHERIT(OWNER(_staritem_star),Language._Defclass))
                       v_or = unknown_ask_any(get_symbol(OBJECT(Defobj,_staritem_star)->ident));
                      else { _void_(f->firstc = integer_I_char(_char_(((unsigned char)' '))));
                          v_or = CFALSE;
                          }
                        if (v_or == CTRUE) g0708I =CTRUE; 
                      else g0708I = CFALSE;}
                    }
                  }
                
                if (g0708I == CTRUE) if (Reader.PROCESS_EVAL_INSTRUCTIONS_ask->value != Kernel.ctrue)
                   { ClaireHandler c_handle = ClaireHandler();
                    if ERROR_IN 
                    { GC__OID(_staritem_star = OPT_EVAL(_staritem_star), 1);
                      ERROR_FREE;}
                    else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                    { c_handle.catchIt();_staritem_star= (CNULL);
                      }
                    else PREVIOUS_HANDLER;}
                  else GC__OID(_staritem_star = OPT_EVAL(_staritem_star), 2);
                    }
              (Language.LastComment->value= CNULL);
              }
            if (b == CTRUE)
           { princ_string(((char*)"=> "));
            print_any(_staritem_star);
            princ_string(((char*)" \n\n"));
            }
          if (Reader.PROCESS_EVAL_INSTRUCTIONS_ask->value != Kernel.ctrue)
           { ClaireHandler c_handle = ClaireHandler();
            if ERROR_IN 
            { GC__OID(_staritem_star = readblock_port(f), 3);
              ERROR_FREE;}
            else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
            { c_handle.catchIt();{ _void_(f->firstc = integer_I_char(_char_(((unsigned char)' '))));
                _staritem_star= (CNULL);
                }
              }
            else PREVIOUS_HANDLER;}
          else GC__OID(_staritem_star = readblock_port(f), 4);
            GC_UNLOOP;POP_SIGNAL;}
        }
      reader_pop_void1();
      (ClEnv->base= ((OID)start));
      (ClEnv->index= ((OID)top));
      fclose_port1(f);
      }
    { OID Result = 0;
      Result = Kernel.ctrue;
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// the simple load
//
// The c++ function for: load(self:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  load_string(char *self) { 
    POP_SIGNAL; return (load_file_string(self,CFALSE));}
  


// The c++ function for: sload(self:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  sload_string(char *self) { 
    POP_SIGNAL; return (load_file_string(self,CTRUE));}
  


// loading a module into the system.
// The correct package is open and each file is loaded.
// The c++ function for: load_file(self:module,b:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  load_file_module(module *self,ClaireBoolean *b) { 
    
    GC_BIND;
    if (self->status == 2)
     { fcall1(self->evaluate,Kernel._any,_oid_(Kernel._any),Kernel._any);
      _void_(self->status = 3);
      }
    else if ((self->status == 0) && 
        (((self->source == (NULL)) ? CTRUE : CFALSE) != CTRUE))
     { if (should_trace_ask_module1(Reader.it,3) == CTRUE)
       mtformat_module1(Reader.it,((char*)"---- Loading the module ~S.\n"),3,list::alloc(1,_oid_(self)));
      else ;begin_module(self);
      { char * s = GC_STRING(append_string(GC_STRING(self->source),GC_STRING(string_v(Core._starfs_star->value))));
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(x);
          bag *x_support;
          x_support = GC_OBJECT(list,self->made_of);
          for (START(x_support); NEXT(x);)
          { GC_LOOP;
            if ((match_wildcard_ask_string(string_v(x),((char*)"*.cl")) == CTRUE) || 
                (match_wildcard_ask_string(string_v(x),((char*)"*.*")) != CTRUE))
             load_file_string(GC_STRING(append_string(GC_STRING(append_string(s,GC_STRING(replace_string(string_v(x),((char*)".cl"),((char*)""))))),((char*)".cl"))),b);
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
          if (match_wildcard_ask_string(string_v(x),((char*)"*@PATH_INFO@*")) == CTRUE)
           { if (should_trace_ask_module1(Reader.it,3) == CTRUE)
             mtformat_module1(Reader.it,((char*)"---- [load WCL file: ~A]\n"),3,GC_OBJECT(list,list::alloc(1,GC_OID((*(explode_string(string_v(x),((char*)"@PATH_INFO@"))))[1]))));
            else ;reader_push_void1();
            _void_(Reader.reader->toplevel = CFALSE);
            { list * defs = GC_OBJECT(list,load_wcl_I_string1(string_v(x)));
              CL_INT  start = ClEnv->base;
              CL_INT  top = ClEnv->index;
              (ClEnv->base= ((OID)top));
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(y);
                for (START(defs); NEXT(y);)
                { index_jump_integer1(((CL_INT)top+(CL_INT)((CL_INT)Reader.reader->maxstack+(CL_INT)1)));
                  if ((OBJECT(ClaireBoolean,Reader.PROCESS_EVAL_INSTRUCTIONS_ask->value)) == CTRUE)
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
      _void_(self->status = 1);
      }
    end_module(self);
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> prevent load @ module to load module's code
// The c++ function for: set_load_module(b:boolean) [SAFE_RESULT]
CL_EXPORT void  set_load_module_boolean(ClaireBoolean *b) { 
    (Reader.PROCESS_LOAD_MODULE_ask->value= _oid_(b));
    POP_SIGNAL;}
  


//<sb> prevent eval(*item*) in load module
// The c++ function for: set_eval_module(b:boolean) [SAFE_RESULT]
CL_EXPORT void  set_eval_module_boolean1(ClaireBoolean *b) { 
    (Reader.PROCESS_EVAL_INSTRUCTIONS_ask->value= _oid_(b));
    POP_SIGNAL;}
  


// the simple load
//
// The c++ function for: load(self:module) [NEW_ALLOC+BAG_UPDATE]
CL_EXPORT OID  load_module(module *self) { 
    
    GC_BIND;
    { OID Result = 0;
      if ((OBJECT(ClaireBoolean,Reader.PROCESS_LOAD_MODULE_ask->value)) == CTRUE)
       { CL_INT loop_handle = ClEnv->cHandle;
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
CL_EXPORT OID  sload_module(module *self) { 
    
    GC_BIND;
    { OID Result = 0;
      if ((OBJECT(ClaireBoolean,Reader.PROCESS_LOAD_MODULE_ask->value)) == CTRUE)
       { CL_INT loop_handle = ClEnv->cHandle;
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
CL_EXPORT list * add_modules_module(module *self,set *l,list *result) { 
    if (result->memq(_oid_(self)) == CTRUE) 
    { { list *Result ;
        Result = result;
        return (Result);}
       }
    else{ if (contain_ask_set(l,_oid_(self)) != CTRUE) 
      { { list *Result ;
          Result = result;
          return (Result);}
         }
      else{ 
        GC_RESERVE(2);  // v3.3.39 optim !
        if ((((self->part_of == (NULL)) ? CTRUE : CFALSE) != CTRUE) && 
            (self->part_of != claire.it))
         result= (GC_OBJECT(list,add_modules_module(self->part_of,l,result)));
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
         result= (result->addFast((OID)_oid_(self)));
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(x);
          for (START(self->parts); NEXT(x);)
          { GC_LOOP;
            GC__ANY(result = add_modules_module(OBJECT(module,x),l,result), 2);
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
CL_EXPORT void  add_parts_module(module *self,set *result) { 
    
    GC_BIND;
    result= (GC_OBJECT(set,result->addFast((OID)_oid_(self))));
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(m);
      for (START(self->parts); NEXT(m);)
      add_parts_module(OBJECT(module,m),result);
      }
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> add part_of until claire
// The c++ function for: add_subparts(self:module,result:set) [NEW_ALLOC]
CL_EXPORT void  add_subparts_module(module *self,set *result) { 
    
    GC_BIND;
    if (((self->part_of == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     { module * m = self->part_of;
      result= (GC_OBJECT(set,result->addFast((OID)_oid_(self))));
      if (m != claire.it)
       add_subparts_module(m,result);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: add_uses(self:module,result:set) [NEW_ALLOC]
CL_EXPORT void  add_uses_module(module *self,set *result) { 
    
    GC_BIND;
    if (contain_ask_set(result,_oid_(self)) != CTRUE)
     result= (GC_OBJECT(set,result->addFast((OID)_oid_(self))));
    { CL_INT loop_handle = ClEnv->cHandle;
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
CL_EXPORT void  add_modules_module2(module *self,set *result) { 
    
    GC_BIND;
    add_uses_module(self,result);
    add_parts_module(self,result);
    add_subparts_module(self,result);
    result= (GC_OBJECT(set,result->addFast((OID)_oid_(self))));
    GC_UNBIND; POP_SIGNAL;}
  


// this methods takes a list of modules that must be loaded and returns
// a list of modules that are necessary for the definition
//
// The c++ function for: add_modules(self:list) [NEW_ALLOC+BAG_UPDATE]
CL_EXPORT list * add_modules_list(list *self) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { list *Result ;
      { set * base = set::empty(Kernel._module);
        list * l = list::empty(Kernel._module);
        { CL_INT loop_handle = ClEnv->cHandle;
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
CL_EXPORT OID  eload_string(char *self) { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    reader_push_void1();
    _void_(Reader.reader->index = 0);
    _void_(Reader.reader->maxstack = 0);
    _void_(Reader.reader->nb_line = 1);
    _void_(Reader.reader->external = self);
    if (should_trace_ask_module1(Reader.it,3) == CTRUE)
     mtformat_module1(Reader.it,((char*)"---- [eload CLAIRE file: ~A]\n"),3,list::alloc(1,_string_(self)));
    else ;{ PortObject * p1 = GC_OBJECT(PortObject,fopen_source_string1(self));
      CL_INT  start = ClEnv->base;
      CL_INT  top = ClEnv->index;
      OID  _staritem_star = CNULL;
      (ClEnv->base= ((OID)top));
      _void_(Reader.reader->toplevel = CFALSE);
      _void_(Reader.reader->fromp = p1);
      _staritem_star= (GC_OID(read_port(p1)));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((equal(_staritem_star,Core._eof->value) != CTRUE))
        { GC_LOOP;
          index_jump_integer1(((CL_INT)top+(CL_INT)((CL_INT)Reader.reader->maxstack+(CL_INT)1)));
          if ((OBJECT(ClaireBoolean,Reader.PROCESS_EVAL_INSTRUCTIONS_ask->value)) == CTRUE)
           GC__OID(_staritem_star = OPT_EVAL(_staritem_star), 1);
          GC__OID(_staritem_star = read_port(p1), 2);
          GC_UNLOOP;POP_SIGNAL;}
        }
      reader_pop_void1();
      (ClEnv->base= ((OID)start));
      (ClEnv->index= ((OID)top));
      fclose_port1(p1);
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
CL_EXPORT OID  readblock_port(PortObject *p) { 
    
    GC_BIND;
    (Reader.IDENTS->value= _oid_(list::empty(Kernel._list)));
    { OID Result = 0;
      if (Reader.reader->fromp == p)
       Result = nextunit_meta_reader(Reader.reader);
      else { PortObject * p2 = GC_OBJECT(PortObject,Reader.reader->fromp);
          _void_(Reader.reader->fromp = p);
          { OID  val = GC_OID(nextunit_meta_reader(Reader.reader));
            _void_(Reader.reader->fromp = p2);
            if ((equal(val,Reader.reader->paren) == CTRUE) || 
                ((equal(val,Reader.reader->curly) == CTRUE) || 
                  ((equal(val,Reader.reader->comma) == CTRUE) || 
                    (equal(val,Reader.reader->bracket) == CTRUE))))
             Serror_integer1(117,((char*)"Loose ~S in file"),list::alloc(1,val));
            Result = val;
            }
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// read reads a closed expression
// The c++ function for: read(p:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  read_port(PortObject *p) { 
    
    GC_BIND;
    { OID Result = 0;
      { PortObject * p2 = GC_OBJECT(PortObject,Reader.reader->fromp);
        if (p != p2)
         _void_(Reader.reader->fromp = p);
        { OID  val;
          { if (skipc_meta_reader(Reader.reader) == ((OID)Reader.reader->eof))
             val = Core._eof->value;
            else val = nexte_meta_reader(Reader.reader);
              GC_OID(val);}
          if (p != p2)
           _void_(Reader.reader->fromp = p2);
          if ((equal(val,Reader.reader->paren) == CTRUE) || 
              ((equal(val,Reader.reader->curly) == CTRUE) || 
                ((equal(val,Reader.reader->comma) == CTRUE) || 
                  (equal(val,Reader.reader->bracket) == CTRUE))))
           Serror_integer1(117,((char*)"Loose ~S in file"),list::alloc(1,val));
          Result = val;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// read into a string
// The c++ function for: read(self:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  read_string(char *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  x = CNULL;
        reader_push_void1();
        _void_(Reader.reader->toplevel = CTRUE);
        { blob * p = GC_OBJECT(blob,blob_I_string1(self));
          _void_(Reader.reader->fromp = p);
          { ClaireHandler c_handle = ClaireHandler();
            if ERROR_IN 
            { x= (GC_OID(nextunit_meta_reader(Reader.reader)));
              ERROR_FREE;}
            else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
            { c_handle.catchIt();{ reader_pop_void1();
                fclose_port1(p);
                close_exception(ClEnv->exception_I);
                }
              }
            else PREVIOUS_HANDLER;}
          fclose_port1(p);
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
CL_EXPORT OID  print_exception_void() { 
    
    GC_BIND;
    { OID Result = 0;
      { PortObject * p = use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value));
        ClaireException * _Zerr = GC_OBJECT(ClaireException,ClEnv->exception_I);
        method * _Zprop = ((method *) _at_property1(Kernel.self_print,OWNER(_oid_(_Zerr))));
        { ClaireHandler c_handle = ClaireHandler();
          if ERROR_IN 
          { { if (Reader.reader->toplevel != CTRUE)
               { tuple * loc = GC_OBJECT(tuple,get_location_port1(GC_OBJECT(PortObject,Reader.reader->fromp))->copyIfNeeded());
                if (isfile_ask_string(string_v((*(loc))[1])) == CTRUE)
                 { if (color_void() == 2)
                   { char * href = GC_STRING(getenv_string(((char*)"WCL_HREF_FORMATER")));
                    buffer * p = GC_OBJECT(buffer,buffer_I_port1(GC_OBJECT(PortObject,ClEnv->cout),4096));
                    PortObject * old = use_as_output_port(p);
                    color_integer(0);
                    if (LENGTH_STRING(href) == 0)
                     href= (((char*)"txmt://open?url=$URLFILE&line=$LINE"));
                    href= (GC_STRING(replace_string(href,((char*)"$FILE"),string_v((*(loc))[1]))));
                    href= (GC_STRING(replace_string(href,((char*)"$URLFILE"),GC_STRING(url_encode_string(GC_STRING(append_string(((char*)"file://"),string_v((*(loc))[1]))))))));
                    href= (GC_STRING(replace_string(href,((char*)"$LINE"),GC_STRING(string_I_integer (((CL_INT)(*(loc))[2]))))));
                    princ_string(((char*)"In&nbsp;<a href='"));
                    (*Language.echo)(_string_(href));
                    princ_string(((char*)"'>"));
                    (*Language.self_html)((*(loc))[1]);
                    princ_string(((char*)":"));
                    (*Language.echo)((*(loc))[2]);
                    princ_string(((char*)"</a><br>"));
                    use_as_output_port(old);
                    fclose_port1(p);
                    color_integer(2);
                    }
                  else { CL_INT  g0709 = (CL_INT )(current_color);
                      CL_INT  g0710 = (CL_INT )(current_bold);
                      CL_INT  g0711 = g0709;
                      CL_INT  g0712 = g0710;
                      color(g0709,g0710);
                      color_princ_string1(((char*)"`REDIn "));
                      g0709= (CL_INT)((CL_INT )(current_color));
                      g0710= (CL_INT)((CL_INT )(current_bold));
                      color(g0711,g0712);
                      princ_string(string_v((*(loc))[1]));
                      color(g0709,g0710);
                      color(g0709,g0710);
                      color_princ_string1(((char*)":"));
                      g0709= (CL_INT)((CL_INT )(current_color));
                      g0710= (CL_INT)((CL_INT )(current_bold));
                      color(g0711,g0712);
                      print_any((*(loc))[2]);
                      color(g0709,g0710);
                      color(g0709,g0710);
                      color_princ_string1(((char*)"\n"));
                      color(g0711,g0712);
                      }
                    }
                }
              color(31,0);
              if (((_Zprop->functional == (NULL)) ? CTRUE : CFALSE) != CTRUE)
               fcall1(_Zprop->functional,Kernel._object,_oid_(_Zerr),Kernel._any);
              else funcall_method1(_Zprop,_oid_(_Zerr));
                princ_string(((char*)"\n"));
              }
            ERROR_FREE;}
          else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
          { c_handle.catchIt();{ color(30,0);
              if ((INHERIT(ClEnv->exception_I->isa,Kernel._system_error)) && ((CLREAD(system_error,ClEnv->exception_I,index) == 1) || 
                  ((CLREAD(system_error,ClEnv->exception_I,index) == 2) || 
                    ((CLREAD(system_error,ClEnv->exception_I,index) == 3) || 
                      ((CLREAD(system_error,ClEnv->exception_I,index) == 24) || 
                        ((CLREAD(system_error,ClEnv->exception_I,index) == 33) || 
                          (CLREAD(system_error,ClEnv->exception_I,index) == 34)))))))
               close_exception(ClEnv->exception_I);
              color(31,0);
              princ_string(((char*)"\n[121] unprintable error <"));
              print_any(_oid_(OWNER(_oid_(_Zerr))));
              princ_string(((char*)">.\n"));
              }
            }
          else PREVIOUS_HANDLER;}
        color(30,0);
        Result = _oid_(use_as_output_port(p));
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
CL_EXPORT OID  show_any(OID self) { 
    if (_Z_any1(self,Kernel._object) == CTRUE)
     { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(rel);
      bag *rel_support;
      rel_support = OWNER(self)->slots;
      for (START(rel_support); NEXT(rel);)
      { print_any(_oid_(OBJECT(restriction,rel)->selector));
        princ_string(((char*)": "));
        print_any(get_slot(OBJECT(slot,rel),OBJECT(ClaireObject,self)));
        princ_string(((char*)"\n"));
        }
      }
    else { print_any(self);
        princ_string(((char*)" is a "));
        print_any(_oid_(OWNER(self)));
        princ_string(((char*)"\n"));
        }
      POP_SIGNAL; return (Kernel.ctrue);}
  


//
// our two very special inline methods
// The c++ function for: min(x:any,y:any) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  min_any(OID x,OID y) { 
    { OID Result = 0;
      if ((OBJECT(ClaireBoolean,(*Kernel._inf_equal)(x,
        y))) == CTRUE)
       Result = x;
      else Result = y;
        POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: max(x:any,y:any) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  max_any(OID x,OID y) { 
    { OID Result = 0;
      if ((OBJECT(ClaireBoolean,(*Kernel._inf_equal)(x,
        y))) == CTRUE)
       Result = y;
      else Result = x;
        POP_SIGNAL; return (Result);}
    }
  


// check if the value is known?
// The c++ function for: known?(a:table,x:any) [0]
CL_EXPORT ClaireBoolean * known_ask_table(table *a,OID x) { 
    POP_SIGNAL; return (_I_equal_any(get_table(a,x),CNULL));}
  


// The c++ function for: unknown?(a:table,x:any) [0]
CL_EXPORT ClaireBoolean * unknown_ask_table(table *a,OID x) { 
    POP_SIGNAL; return (equal(get_table(a,x),CNULL));}
  


//
// v3.00.46 a new macro
// The c++ function for: >=(self:any,x:any) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * _sup_equal_any(OID self,OID x) { 
    POP_SIGNAL; return (OBJECT(ClaireBoolean,(*Kernel._inf_equal)(x,
      self)));}
  


// this is a useful macro for hashing
// The c++ function for: mClaire/hashgrow(l:list,hi:property) [NEW_ALLOC]
CL_EXPORT list * hashgrow_list(list *l,property *hi) { 
    
    GC_BIND;
    { list *Result ;
      { list * l1 = l;
        list * l2 = GC_OBJECT(list,make_list_integer(((CL_INT)(((CL_INT)(*(l1))[0]))*(CL_INT)2),CNULL));
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
CL_EXPORT void  use_module_string(char *m) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    if (LENGTH_STRING(m) == 0)
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"use_module called with an empty string !")),
      _oid_(Kernel.nil))));
    if (isenv_ask_string(((char*)"CLAIRE_LIBS")) != CTRUE)
     { if (should_trace_ask_module1(Reader.it,3) == CTRUE)
       mtformat_module1(Reader.it,((char*)"---- warning: environment variable CLAIRE_LIBS undefined\n"),3,list::empty());
      else ;}
    { char * f = GC_STRING(realpath_string(GC_STRING(getenv_string(((char*)"_")))));
      char * hom = GC_STRING(((isenv_ask_string(((char*)"CLAIRE_PUBLISH_HOME")) == CTRUE) ?
        getenv_string(((char*)"CLAIRE_PUBLISH_HOME")) :
        realpath_string(GC_STRING(_7_string(GC_STRING(_7_string(GC_STRING(_7_string(GC_STRING(substring_string(f,1,((CL_INT)rfind_string2(f,string_v(Core._starfs_star->value))-(CL_INT)1))),((char*)".."))),((char*)".."))),((char*)"..")))) ));
      list * p;
      { { list * pu = GC_OBJECT(list,explode_string(m,((char*)"/")));
          if ((CL_INT)pu->length > (CL_INT)1)
           p = pu;
          else { list * pc = GC_OBJECT(list,explode_string(m,((char*)"\\")));
              p = pc;
              }
            }
        GC_OBJECT(list,p);}
      OID  up;
      { if ((CL_INT)p->length > (CL_INT)1)
         up = _string_(_7_string(string_v((*(p))[1]),string_v((*(p))[2])));
        else up = (*(p))[1];
          GC_OID(up);}
      list * libs = GC_OBJECT(list,GC_OBJECT(list,explode_string(GC_STRING(getenv_string(((char*)"CLAIRE_LIBS"))),GC_STRING(string_v(Core._starps_star->value))))->addFast((OID)GC_OID(_string_(_7_string(hom,((char*)"lib"))))));
      char * oldp = GC_STRING(pwd_void());
      if (value_string(string_v((*(p))[1])) == CNULL)
       { OID  mptest;
        { { OID  mp_some = CNULL;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(mp);
              for (START(libs); NEXT(mp);)
              { GC_LOOP;
                if (isfile_ask_string(_7_string(GC_STRING(_7_string(string_v(mp),string_v(up))),((char*)"init.cl"))) == CTRUE)
                 { mp_some= (mp);
                  GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                GC_UNLOOP; POP_SIGNAL;}
              }
            mptest = mp_some;
            }
          GC_OID(mptest);}
        if (mptest != CNULL)
         { char * mp = string_v(mptest);
          if (should_trace_ask_module1(Reader.it,3) == CTRUE)
           mtformat_module1(Reader.it,((char*)"==== Use module ~A at ~A [v~A] ==== \n"),3,GC_OBJECT(list,list::alloc(3,_string_(m),
            _string_(mp),
            GC_OID(_string_(release_void())))));
          else ;setcwd_string(_7_string(mp,string_v(up)));
          { ClaireHandler c_handle = ClaireHandler();
            if ERROR_IN 
            { { _void_(ClEnv->module_I = claire.it);
                load_string(((char*)"init"));
                { OID  m = value_string(string_v((*(p))[1]));
                  if (inherit_ask_class(OWNER(m),Kernel._module) != CTRUE)
                   close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"The init file ~A doesn't define the module ~A [~S]!")),
                    _oid_(list::alloc(3,GC_OID(_string_(_7_string(GC_STRING(_7_string(mp,string_v(up))),((char*)"init.cl")))),
                      (*(p))[1],
                      m)))));
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
        else { ClaireBoolean * g0714I;
          { OID  g0715UU;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(mp);
              g0715UU= Kernel.cfalse;
              for (START(libs); NEXT(mp);)
              if (isdir_ask_string(_7_string(string_v(mp),string_v((*(p))[1]))) == CTRUE)
               { g0715UU = Kernel.ctrue;
                ClEnv->cHandle = loop_handle;break;}
              }
            g0714I = boolean_I_any(g0715UU);
            }
          
          if (g0714I == CTRUE) { if (p->length == 1)
               { if (should_trace_ask_module1(Reader.it,3) == CTRUE)
                 mtformat_module1(Reader.it,((char*)"---- warning: undefined version of module ~A, expect one of: \n"),3,list::alloc(1,_string_(m)));
                else ;}
              else if (should_trace_ask_module1(Reader.it,3) == CTRUE)
               mtformat_module1(Reader.it,((char*)"---- warning: unresolved module ~A, missing version ~A in: \n"),3,list::alloc(2,(*(p))[1],(*(p))[2]));
              else ;{ ClaireBoolean * first_ask = CTRUE;
                char * ump = ((char*)"");
                ClaireBoolean * haveinit_ask = CFALSE;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(g0713);
                  for (START(libs); NEXT(g0713);)
                  { GC_LOOP;
                    { char * mp = GC_STRING(_7_string(string_v(g0713),string_v((*(p))[1])));
                      if (isdir_ask_string(mp) == CTRUE)
                       { if (isfile_ask_string(_7_string(mp,((char*)"init.cl"))) == CTRUE)
                         haveinit_ask= (CTRUE);
                        else { list * es;
                            { { bag * e_in = entries_string2(mp);
                                list * e_out = ((list *) empty_bag(e_in));
                                { CL_INT loop_handle = ClEnv->cHandle;
                                  OID gc_local;
                                  ITERATE(e);
                                  for (START(e_in); NEXT(e);)
                                  { GC_LOOP;
                                    if ((isdir_ask_string(_7_string(mp,string_v(e))) == CTRUE) && 
                                        (isfile_ask_string(_7_string(GC_STRING(_7_string(mp,string_v(e))),((char*)"init.cl"))) == CTRUE))
                                     e_out->addFast((OID)e);
                                    GC_UNLOOP; POP_SIGNAL;}
                                  }
                                es = GC_OBJECT(list,e_out);
                                }
                              GC_OBJECT(list,es);}
                            if (es->length != 0)
                             { if (should_trace_ask_module1(Reader.it,3) == CTRUE)
                               mtformat_module1(Reader.it,((char*)"     [~A] ~A \n"),3,GC_OBJECT(list,list::alloc(2,_string_(mp),_oid_(es))));
                              else ;if (first_ask == CTRUE)
                               { first_ask= (CFALSE);
                                GC__STRING(ump = string_v((*(sort_method(GC_OBJECT(method,((method *) _at_property1(Kernel._sup,Kernel._string))),es)))[1]), 1);
                                }
                              }
                            }
                          }
                      }
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                if ((haveinit_ask == CTRUE) || 
                    ((CL_INT)LENGTH_STRING(ump) > (CL_INT)0))
                 { if (should_trace_ask_module1(Reader.it,3) == CTRUE)
                   mtformat_module1(Reader.it,((char*)"     ===> try with ~A \n"),3,GC_OBJECT(list,list::alloc(1,GC_OID(_string_(_7_string(string_v((*(p))[1]),ump))))));
                  else ;if (LENGTH_STRING(ump) == 0)
                   use_module_string(string_v((*(p))[1]));
                  else use_module_string(GC_STRING(_7_string(string_v((*(p))[1]),ump)));
                    }
                }
              }
            else { if (should_trace_ask_module1(Reader.it,0) == CTRUE)
             mtformat_module1(Reader.it,((char*)"---- warning: the module ~A cannot be found in any of: \n"),0,GC_OBJECT(list,list::alloc(1,_string_(m))));
            else ;{ CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(mp);
              for (START(libs); NEXT(mp);)
              { GC_LOOP;
                if (should_trace_ask_module1(Reader.it,0) == CTRUE)
                 mtformat_module1(Reader.it,((char*)"     ~A \n"),0,GC_OBJECT(list,list::alloc(1,mp)));
                else ;GC_UNLOOP; POP_SIGNAL;}
              }
            }
          }
        }
      if (value_string(((char*)"Compile")) != CNULL)
       { read_string(((char*)"erase(inline?, compiler)"));
        read_string(((char*)"erase(safety, compiler)"));
        read_string(((char*)"erase(overflow?, compiler)"));
        read_string(((char*)"erase(naming, compiler)"));
        read_string(((char*)"(compiler.source := \"csrc\")"));
        read_string(((char*)"(Compile/FCALLSTINKS := false)"));
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: option_usage(g0716:{"-f", "-ef"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string13_Reader_(char *g0716) { 
    return option_usage_string13_Reader(g0716)->copyIfNeeded();
}


// The c++ function for: option_usage(opt:{"-ef", "-f"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string13_Reader(char *opt) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Load file")),
        _string_(((char*)"{-f | -ef} +[<file:path>]")),
        GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"Load the CLAIRE file(s) <file>. The given path may contain an extension "),((char*)"assuming .cl by default. When the <-f> option is used, the file is "))),((char*)"assumed to contain CLAIRE definitions (variables, class, methods) whereas "))),((char*)" <-ef> attempts to read a file made of CLAIRE expression.")))));
      GC_UNBIND; return (Result);}
    }
  


// The c++ function for: option_respond(opt:{"-ef", "-f"},l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  option_respond_string10_Reader(char *opt,list *l) { 
    if (boolean_I_any(_oid_(l)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    if ((isfile_ask_string(string_v((*(l))[1])) != CTRUE) && 
        (isfile_ask_string(string_v((*Kernel._7_plus)((*(l))[1],
          _string_(((char*)".cl"))))) != CTRUE))
     close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~A cannot be opened")),
      _oid_(list::alloc(1,(*(l))[1])))));
    { CL_INT loop_handle = ClEnv->cHandle;
      while (((l->length != 0) && 
          ((isfile_ask_string(string_v((*(l))[1])) == CTRUE) || 
              (isfile_ask_string(string_v((*Kernel._7_plus)((*(l))[1],
                _string_(((char*)".cl"))))) == CTRUE))))
      { { OID  path = (*(l))[1];
          skip_list(l,1);
          if (equal_string(opt,((char*)"-f")) == CTRUE)
           (*Reader.load)(path);
          else if (equal_string(opt,((char*)"-ef")) == CTRUE)
           eload_string(string_v(path));
          }
        POP_SIGNAL;}
      }
    POP_SIGNAL;}
  


// The c++ function for: option_usage(g0717:{"-princ", "-print", "-eval"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string14_Reader_(char *g0717) { 
    return option_usage_string14_Reader(g0717)->copyIfNeeded();
}


// The c++ function for: option_usage(opt:{"-eval", "-print", "-princ"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string14_Reader(char *opt) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Eval expression")),
        _string_(((char*)"{-princ | -print | -eval} <exp:any>")),
        GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"Eval the CLAIRE expression <exp>. If <-princ> or <-print> is used instead "),((char*)"of <-eval>, the result of the evaluation is princed/printed on the "))),((char*)"standard output. Often, the hosting shell support quotes allowing "))),((char*)"<exp> to contain space and/or special chars.")))));
      GC_UNBIND; return (Result);}
    }
  


// The c++ function for: option_respond(opt:{"-print", "-princ", "-eval"},l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  option_respond_string11_Reader(char *opt,list *l) { 
    
    GC_BIND;
    if (boolean_I_any(_oid_(l)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    { OID  fragment = (*(l))[1];
      skip_list(l,1);
      reader_push_void1();
      { CL_INT  start = ClEnv->base;
        CL_INT  top = ClEnv->index;
        OID  _staritem_star = CNULL;
        (ClEnv->base= ((OID)top));
        _void_(Reader.reader->maxstack = 0);
        _void_(Reader.reader->index = 0);
        update_property(Reader.fromp,
          Reader.reader,
          5,
          Kernel._object,
          GC_OID((*Core.blob_I)(fragment)));
        _staritem_star= (GC_OID(nextunit_meta_reader(Reader.reader)));
        if (equal(_staritem_star,Core._eof->value) != CTRUE)
         { index_jump_integer1(((CL_INT)top+(CL_INT)((CL_INT)Reader.reader->maxstack+(CL_INT)1)));
          _staritem_star= (GC_OID(OPT_EVAL(_staritem_star)));
          }
        reader_pop_void1();
        (ClEnv->base= ((OID)start));
        (ClEnv->index= ((OID)top));
        if (equal_string(opt,((char*)"-princ")) == CTRUE)
         (*Kernel.princ)(_staritem_star);
        else if (equal_string(opt,((char*)"-print")) == CTRUE)
         print_any(_staritem_star);
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: option_usage(g0718:{"-x", "-xe", "-x?-?", "-xe?-?"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string15_Reader_(char *g0718) { 
    return option_usage_string15_Reader(g0718)->copyIfNeeded();
}


// The c++ function for: option_usage(opt:{"-xe?-?", "-x?-?", "-xe", "-x"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string15_Reader(char *opt) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Load script")),
        _string_(((char*)"{-x | -xe | -x<S:(0 .. 9)>-<W:(0 .. 9)> | -xe<S:(0 .. 9)>-<W:(0 .. 9)>} <file:path> [<args>]")),
        GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"Load the CLAIRE file <file> with implicit options -nologo and -q. "),((char*)"If the option starts with -xe the file is assumed to contain CLAIRE expressions. "))),((char*)"When <S> and <W> are specified they are used to initialize CLAIRE memory (see -s option). "))),((char*)"Unix users may use this option for for a shell script header (e.g #!/usr/local/bin/claire -x). "))),((char*)"If the shell command contains any arguments (<args>) one should handle them in the script through "))),((char*)"the system variable 'system.params'.\n")))));
      GC_UNBIND; return (Result);}
    }
  


// The c++ function for: option_respond(opt:{"-xe?-?", "-x?-?", "-xe", "-x"},l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  option_respond_string12_Reader(char *opt,list *l) { 
    if (boolean_I_any(_oid_(l)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    { OID  path = (*(l))[1];
      skip_list(l,1);
      { ClaireHandler c_handle = ClaireHandler();
        if ERROR_IN 
        { { if (equal_string(left_string(opt,3),((char*)"-xe")) == CTRUE)
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
  



/***** CLAIRE Compilation of file ./meta/inspect.cl 
         [version 3.5.0 / safety 5] *****/


//+-------------------------------------------------------------+
//| CLAIRE                                                      |
//| inspect.cl                                                  |
//| Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved  |
//| cf. copyright info in file object.cl: about()               |
//+-------------------------------------------------------------+
// *********************************************************************
// * Contents                                                          *
// *      Part 1: Inspection                                           *
// *      Part 2: Trace                                                *
// *      Part 3: Stepper                                              *
// *      Part 4: Profiler                                             *
// *      Part 5: Code instrumentation (debug) XL                      *
// *********************************************************************
//<sb> in XL claire this file is quite different from <ycs> since
// the debugger has been entirely rewritten. Indeed, in XL claire
// the debugger uses an instrumented code which provide an
// homogeneous behavior in debug mode between interpreted and
// compiled code.
// v0.01 stop the ... !
// *********************************************************************
// *      Part 1: Inspection                                           *
// *********************************************************************
// this is the method that the user calls
//
//<sb> v3.3.35 : meta toplevel (context)
// The c++ function for: inspect(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  inspect_any(OID self) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  _Zread = _oid_(Kernel.emptySet);
        module * m0 = ClEnv->module_I;
        CL_INT  ix = 0;
        inspect_system_list2(list::empty(Kernel._any));
        if (INHERIT(OWNER(self),Kernel._bag))
         { CL_INT  i = 1;
          CL_INT  g0719 = OBJECT(bag,self)->length;
          { CL_INT loop_handle = ClEnv->cHandle;
            while (((CL_INT)i <= (CL_INT)g0719))
            { princ_integer(i);
              princ_string(((char*)": "));
              print_any((*(OBJECT(bag,self)))[i]);
              princ_string(((char*)"\n"));
              ++i;
              POP_SIGNAL;}
            }
          }
        else if (_Z_any1(self,Kernel._object) == CTRUE)
         { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(rel);
          bag *rel_support;
          rel_support = OWNER(self)->slots;
          for (START(rel_support); NEXT(rel);)
          { GC_LOOP;
            { module * m = OBJECT(restriction,rel)->selector->name->module_I;
              ++ix;
              if ((m == m0) || 
                  ((m == claire.it) || 
                    ((OBJECT(ClaireBoolean,Reader._starshowall_star->value)) == CTRUE)))
               { OID  val = get_slot(OBJECT(slot,rel),OBJECT(ClaireObject,self));
                princ_integer(ix);
                princ_string(((char*)": "));
                color(34,0);
                print_any(_oid_(OBJECT(restriction,rel)->selector));
                color(30,0);
                princ_string(((char*)" = "));
                if (INHERIT(OWNER(val),Kernel._bag))
                 { if ((CL_INT)OBJECT(bag,val)->length < (CL_INT)10)
                   pretty_print_any(val);
                  else { { OID  g0721UU;
                        { list * V_CL0722;{ list * i_bag = list::empty(Kernel.emptySet);
                            { CL_INT  i = 1;
                              CL_INT  g0720 = 9;
                              { CL_INT loop_handle = ClEnv->cHandle;
                                while (((CL_INT)i <= (CL_INT)g0720))
                                { i_bag->addFast((OID)(*(OBJECT(bag,val)))[i]);
                                  ++i;
                                  POP_SIGNAL;}
                                }
                              }
                            V_CL0722 = GC_OBJECT(list,i_bag);
                            }
                          
                          g0721UU=_oid_(V_CL0722);}
                        pretty_print_any(g0721UU);
                        }
                      color_princ_string1(((char*)" `RED...`BLACK"));
                      }
                    }
                else pretty_print_any(val);
                  princ_string(((char*)"\n"));
                }
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        else { pretty_print_any(self);
            princ_string(((char*)"\n"));
            }
          inspect_system_list2(list::alloc(Kernel._any,1,self));
        Result = _oid_(Reader.None);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// this is the inspect top_level
//<sb> v3.3.35 : meta toplevel (context)
// The c++ function for: inspect_loop(%read:any,old:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  inspect_loop_any(OID _Zread,list *old) { 
    
    GC_BIND;
    { OID  self = (*(old))[1];
      if ((INHERIT(OWNER(_Zread),Language._Call)) && (OBJECT(Call,_Zread)->selector == Kernel.put))
       { CL_INT  n = ((CL_INT)(*(OBJECT(bag,(*Core.args)(_Zread))))[1]);
        symbol * s = extract_symbol_any((*(OBJECT(bag,(*Core.args)(_Zread))))[2]);
        if (inherit_ask_class(OWNER(((OID)n)),Kernel._integer) != CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[128] ~S should be an integer")),
          _oid_(list::alloc(1,((OID)n))))));
        { OID  val = GC_OID(get_from_integer_any(self,n));
          _void_(CLREAD(global_variable,new_class2(Core._global_variable,s),value) = val);
          inspect_any(val);
          old= (GC_OBJECT(list,cons_any(val,old)));
          }
        }
      else if ((INHERIT(OWNER(_Zread),Kernel._unbound_symbol)) && (equal_string(OBJECT(unbound_symbol,_Zread)->name->name,((char*)"up")) == CTRUE))
       { if ((CL_INT)old->length > (CL_INT)1)
         { old= (GC_OBJECT(list,cdr_list(old)));
          inspect_any((*(old))[1]);
          }
        else { CL_INT  g0723 = (CL_INT )(current_color);
            CL_INT  g0724 = (CL_INT )(current_bold);
            CL_INT  g0725 = g0723;
            CL_INT  g0726 = g0724;
            color(g0723,g0724);
            color_princ_string1(((char*)"`RED => top of inspect stack.\n"));
            color(g0725,g0726);
            }
          }
      else if (INHERIT(OWNER(_Zread),Kernel._integer))
       { OID  val = GC_OID(get_from_integer_any(self,((CL_INT)_Zread)));
        if ((INHERIT(OWNER(val),Kernel._bag)) && 
            (boolean_I_any(val) != CTRUE))
         { CL_INT  g0727 = (CL_INT )(current_color);
          CL_INT  g0728 = (CL_INT )(current_bold);
          CL_INT  g0729 = g0727;
          CL_INT  g0730 = g0728;
          color(g0727,g0728);
          color_princ_string1(((char*)"`RED => the bag is empty\n"));
          color(g0729,g0730);
          }
        else { old= (GC_OBJECT(list,cons_any(val,old)));
            inspect_any(val);
            }
          }
      else if (_Z_any1(_Zread,Kernel._object) == CTRUE)
       { shrink_list(old,0);
        old= (GC_OBJECT(list,old->addFast((OID)_Zread)));
        inspect_any(_Zread);
        }
      else { CL_INT  g0731 = (CL_INT )(current_color);
          CL_INT  g0732 = (CL_INT )(current_bold);
          CL_INT  g0733 = g0731;
          CL_INT  g0734 = g0732;
          color(g0731,g0732);
          color_princ_string1(((char*)"`RED => given to inspector is wrong.`BLACK \n"));
          color(g0733,g0734);
          }
        }
    inspect_system_list2(old);
    { OID Result = 0;
      Result = ((OID)0);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// get the information bound to the index
//
// The c++ function for: get_from_integer(self:any,n:integer) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  get_from_integer_any(OID self,int n) { 
    { OID Result = 0;
      if (INHERIT(OWNER(self),Kernel._bag))
       { if (((CL_INT)n > (CL_INT)0) && 
            ((CL_INT)n <= (CL_INT)((CL_INT)(*Kernel.length)(self))))
         Result = (*Kernel.nth)(self,
          ((OID)n));
        else { OID  V_CL0735;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~A is not a good index for ~S")),
              _oid_(list::alloc(1,((OID)n))))));
            
            Result=_void_(V_CL0735);}
          }
      else { list * l = OWNER(self)->slots;
          if (((CL_INT)n > (CL_INT)0) && 
              ((CL_INT)n <= (CL_INT)l->length))
           { OID v_rec;
            v_rec = (*(l))[n];
            PUSH(v_rec);
            v_rec = self;
            PUSH(v_rec);
            Result=Kernel.get->super(Kernel._slot,2);}
          else { OID  V_CL0736;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~A is not a good index for ~S")),
                _oid_(list::alloc(1,((OID)n))))));
              
              Result=_void_(V_CL0736);}
            }
        POP_SIGNAL; return (Result);}
    }
  


// *********************************************************************
// *      Part 2: Trace methods                                        *
// *********************************************************************
// instrument the code generated from the rules
//
// a filter to restrict the impact of spy
// we put the special value nil (emply list of demons => OK) to mark that spying
// should be waken up on properties from l
//
//
// used to trace the trigger of a rule
//
// The c++ function for: trace_rule(R:relation,s:string,x:any,y:any,u:any,v:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  trace_rule_relation(ClaireRelation *R,char *s,OID x,OID y,OID u,OID v) { 
    
    GC_BIND;
    if ((CL_INT)5 <= (CL_INT)((CL_INT)Kernel.if_write->trace_I+(CL_INT)ClEnv->verbose))
     { OID  p = GC_OID(get_property(Kernel.ctrace,ClEnv));
      if (p != CNULL)
       p= (_oid_(use_as_output_port(OBJECT(PortObject,p))));
      princ_string(((char*)"--- the rule "));
      princ_string(s);
      princ_string(((char*)" is triggered for ("));
      print_any(u);
      princ_string(((char*)","));
      print_any(v);
      princ_string(((char*)") by an update "));
      print_any(_oid_(R));
      princ_string(((char*)"("));
      print_any(x);
      princ_string(((char*)") "));
      princ_string(((multi_ask_any(_oid_(R)) == CTRUE) ?
        ((char*)":add") :
        ((char*)":=") ));
      princ_string(((char*)" "));
      print_any(y);
      princ_string(((char*)" \n"));
      if (p != CNULL)
       use_as_output_port(OBJECT(PortObject,p));
      }
    GC_UNBIND; POP_SIGNAL;}
  


// ******************************************************************
// *    Part 3: The Stepper                                         *
// ******************************************************************
// the stepper interface is quite simple and could be improved
//
// memory usage statistics for a class
// The c++ function for: mem(c:class) [NEW_ALLOC]
CL_EXPORT CL_INT  mem_class(ClaireClass *c) { 
    { CL_INT Result = 0;
      { CL_INT  n = 0;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(x);
          for (START(c->instances); NEXT(x);)
          { n= (CL_INT)(((CL_INT)n+(CL_INT)(((CL_INT)slot_get_object(OBJECT(ClaireObject,x),0,Kernel._integer)))));
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(sl);
              for (START(c->slots); NEXT(sl);)
              { ClaireType * rs = OBJECT(restriction,sl)->range;
                if (rs == Kernel._float)
                 n= (CL_INT)(((CL_INT)n+(CL_INT)5));
                else if (rs == Kernel._string)
                 { OID  st = get_slot(OBJECT(slot,sl),OBJECT(ClaireObject,x));
                  if (st != CNULL)
                   n= (CL_INT)(((CL_INT)n+(CL_INT)min_integer1(5,((CL_INT)LENGTH_STRING(string_v(st))/(CL_INT)2))));
                  else ;}
                else if (_inf_equal_type(rs,Kernel._bag) == CTRUE)
                 { OID  l = get_slot(OBJECT(slot,sl),OBJECT(ClaireObject,x));
                  if (l != CNULL)
                   n= (CL_INT)(((CL_INT)n+(CL_INT)(((CL_INT)(*(OBJECT(bag,l)))[0]))));
                  else ;}
                }
              }
            }
          }
        Result = n;
        }
      POP_SIGNAL; return (Result);}
    }
  


// *********************************************************************
// *      Part 4: Profiler                                             *
// *********************************************************************
// we use a counter object for the 5 interesting values  and
// we use the reified slot to store the counter (thus no profiling on reified)
// start time (1st entry)
// get & create if needed a PRcounter
// The c++ function for: PRget(p:property) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT PRcount * PRget_property(property *p) { 
    
    GC_BIND;
    { PRcount *Result ;
      { ClaireObject *V_CC ;
        { ClaireObject * x = GC_OBJECT(ClaireObject,p->reified);
          if (OWNER(_oid_(x)) == Reader._PRcount)
           V_CC = x;
          else if (x == CTRUE)
           close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"[131] Cannot profile a reified property ~S")),
            _oid_(list::alloc(1,_oid_(p))))));
          else { { PRcount * _CL_obj = ((PRcount *) GC_OBJECT(PRcount,new_object_class(Reader._PRcount)));
                add_I_property(Kernel.instances,Reader._PRcount,11,_oid_(_CL_obj));
                x = _CL_obj;
                }
              _void_(p->reified = x);
              V_CC = x;
              }
            }
        Result= (PRcount *) V_CC;}
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// get & create if needed a PRcounter
// The c++ function for: PRlook(p:property) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  PRlook_property2(property *p) { 
    POP_SIGNAL; return (show_any(_oid_(PRget_property(p))));}
  


// show the profiler statistics on one property
// The c++ function for: PRshow(p:property) [NEW_ALLOC]
CL_EXPORT void  PRshow_property(property *p) { 
    
    GC_BIND;
    { ClaireObject * x = GC_OBJECT(ClaireObject,p->reified);
      if (INHERIT(x->isa,Reader._PRcount))
       { print_any(_oid_(p));
        princ_string(((char*)": "));
        princ_integer(CLREAD(PRcount,x,rnum));
        princ_string(((char*)" calls -> "));
        princ_integer(CLREAD(PRcount,x,rtime));
        princ_string(((char*)" clock tics\n"));
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// elapsed time
// The c++ function for: PRtime(p:property) [RETURN_ARG]
CL_EXPORT CL_INT  PRtime_property(property *p) { 
    { CL_INT Result = 0;
      { ClaireObject * x = p->reified;
        Result = ((INHERIT(x->isa,Reader._PRcount)) ?
          CLREAD(PRcount,x,rtime) :
          0 );
        }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: PRcounter(p:property) [RETURN_ARG]
CL_EXPORT CL_INT  PRcounter_property(property *p) { 
    { CL_INT Result = 0;
      { ClaireObject * x = p->reified;
        Result = ((INHERIT(x->isa,Reader._PRcount)) ?
          CLREAD(PRcount,x,rnum) :
          0 );
        }
      POP_SIGNAL; return (Result);}
    }
  


// show the profiler statistics on the 10 most important properties
// The c++ function for: PRshow(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE]
CL_EXPORT void  PRshow_void() { 
    { list * l = list::empty(Kernel._property);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(g0737);
        bag *g0737_support;
        g0737_support = Kernel._property->descendents;
        for (START(g0737_support); NEXT(g0737);)
        { ClaireBoolean * g0738;
          { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(p);
              V_C= Kernel.cfalse;
              for (START(OBJECT(ClaireClass,g0737)->instances); NEXT(p);)
              { ClaireBoolean * g0740I;
                { OID  g0741UU;
                  { CL_INT  i = 1;
                    CL_INT  g0739 = min_integer1(10,l->length);
                    { CL_INT loop_handle = ClEnv->cHandle;
                      g0741UU= _oid_(CFALSE);
                      while (((CL_INT)i <= (CL_INT)g0739))
                      { { ClaireBoolean * g0742I;
                          if (((CL_INT)PRtime_property(OBJECT(property,p)) > (CL_INT)PRtime_property(OBJECT(property,(*(l))[i]))) || 
                              ((PRtime_property(OBJECT(property,p)) == PRtime_property(OBJECT(property,(*(l))[i]))) && 
                                  ((CL_INT)PRcounter_property(OBJECT(property,p)) > (CL_INT)PRcounter_property(OBJECT(property,(*(l))[i])))))
                           { l= (add_at_list(l,i,p));
                            g0742I = CTRUE;
                            }
                          else g0742I = CFALSE;
                            
                          if (g0742I == CTRUE) { g0741UU = Kernel.ctrue;
                              ClEnv->cHandle = loop_handle;break;}
                            }
                        ++i;
                        POP_SIGNAL;}
                      }
                    }
                  g0740I = boolean_I_any(g0741UU);
                  }
                
                if (g0740I == CTRUE) ;else if ((CL_INT)l->length < (CL_INT)10)
                 l= (l->addFast((OID)p));
                }
              }
            
            g0738=OBJECT(ClaireBoolean,V_C);}
          if (g0738 == CTRUE)
           { ;ClEnv->cHandle = loop_handle; break;}
          }
        }
      shrink_list(l,10);
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(p);
        for (START(l); NEXT(p);)
        if ((CL_INT)PRcounter_property(OBJECT(property,p)) > (CL_INT)0)
         { princ_string(((char*)"-----------------------------------\n"));
          PRshow_property(OBJECT(property,p));
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(p2);
            bag *p2_support;
            p2_support = OBJECT(set,nth_table1(Reader.PRdependent,p));
            for (START(p2_support); NEXT(p2);)
            if ((CL_INT)PRtime_property(OBJECT(property,p2)) > (CL_INT)0)
             { princ_string(((char*)"   * "));
              PRshow_property(OBJECT(property,p2));
              }
            }
          }
        }
      }
    POP_SIGNAL;}
  


// reuse from lexical_build in pretty.cl
// returns the list of properties that are used by a method
// The c++ function for: dependents(self:method) [NEW_ALLOC]
CL_EXPORT set * dependents_method(method *self) { 
    
    GC_BIND;
    { set *Result ;
      { set * p_out = set::empty(Kernel._property);
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(p);
          bag *p_support;
          p_support = GC_OBJECT(bag,enumerate_any(GC_OID((*Reader.dependents)(self->formula->body))));
          for (START(p_support); NEXT(p);)
          { ClaireBoolean * g0743I;
            { OID  g0744UU;
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(r);
                g0744UU= Kernel.cfalse;
                for (START(OBJECT(property,p)->restrictions); NEXT(r);)
                if (Kernel._method == OBJECT(ClaireObject,r)->isa)
                 { g0744UU = Kernel.ctrue;
                  ClEnv->cHandle = loop_handle;break;}
                }
              g0743I = boolean_I_any(g0744UU);
              }
            
            if (g0743I == CTRUE) p_out->addFast((OID)p);
              }
          }
        Result = GC_OBJECT(set,p_out);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// this is really cute ....   v3.2.58: fix typing
// The c++ function for: dependents(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  dependents_any(OID self) { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    { OID Result = 0;
      if (INHERIT(OWNER(self),Language._Call))
       Result = (*Kernel.add)(GC_OID(dependents_any(GC_OID(_oid_(OBJECT(Call,self)->args)))),
        _oid_(OBJECT(Call,self)->selector));
      else if (INHERIT(OWNER(self),Language._Instruction))
       { set * s = set::empty(Kernel._property);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(sl);
          for (START(OBJECT(ClaireObject,self)->isa->slots); NEXT(sl);)
          { GC_LOOP;
            GC__ANY(s = ((set *) U_type(s,GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Reader.dependents)(get_slot(OBJECT(slot,sl),OBJECT(ClaireObject,self))))))), 1);
            GC_UNLOOP; POP_SIGNAL;}
          }
        Result = _oid_(s);
        }
      else if (INHERIT(OWNER(self),Kernel._bag))
       { set * s = GC_OBJECT(set,set::empty(Kernel._property));
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(x);
          for (START(OBJECT(bag,self)); NEXT(x);)
          { GC_LOOP;
            GC__ANY(s = ((set *) U_type(s,GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Reader.dependents)(x))))), 2);
            GC_UNLOOP; POP_SIGNAL;}
          }
        Result = _oid_(s);
        }
      else if (INHERIT(OWNER(self),Kernel._property))
       Result = _oid_(set::alloc(Kernel._property,1,self));
      else Result = _oid_(set::empty(Kernel._property));
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// used to set up the dependence
// The c++ function for: PRdepends(p:property,p2:property) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  PRdepends_property(property *p,property *p2) { 
    add_table(Reader.PRdependent,_oid_(p),_oid_(p2));
    ;POP_SIGNAL;}
  


// ******************************************************************
// *    Part 5: Code instrumentation (debug)                        *
// ******************************************************************
// The c++ function for: dump_stack(_CL_obj:void) [NEW_ALLOC]
CL_EXPORT void  dump_stack_void1() { 
    
    GC_BIND;
    princ_string(((char*)"===== Dump stack ======\n"));
    { CL_INT  i = 0;
      CL_INT  g0746 = ((CL_INT)ClEnv->index-(CL_INT)1);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)i <= (CL_INT)g0746))
        { GC_LOOP;
          print_any(((OID)i));
          princ_string(((char*)": "));
          print_any(GC_OID(ClEnv->stack[((OID)i)]));
          princ_string(((char*)"\n"));
          ++i;
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    princ_string(((char*)"index: "));
    print_any(((OID)ClEnv->index));
    princ_string(((char*)"\n"));
    princ_string(((char*)"base: "));
    print_any(((OID)ClEnv->base));
    princ_string(((char*)"\n"));
    princ_string(((char*)"trace!: "));
    print_any(((OID)ClEnv->trace_I));
    princ_string(((char*)"\n"));
    princ_string(((char*)"debug!: "));
    print_any(((OID)ClEnv->debug_I));
    princ_string(((char*)"\n"));
    princ_string(((char*)"======================\n"));
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> this file contains code for the debugger, how to
// locate instruction in a source file and how to equip the
// code such to control a program execution: generate
// backtrace and handle breakpoints/watchpoints.
// In this implementation (vs Yves's one) the code is equipped
// before being compiled such that we can homogeneously perform
// debug session for both interpreted and compiled code :)
//<sb> called by the close@Instruction constructor (in pretty.cl) 
// Here we try to locate the
// given instruction and map it in CODE_LOCS.
// The c++ function for: Language/init_location(self:any) [NEW_ALLOC+BAG_UPDATE+RETURN_ARG]
CL_EXPORT void  init_location_any1_Reader(OID self) { 
    
    GC_BIND;
    { char * matchident;
      if (INHERIT(OWNER(self),Kernel._unbound_symbol))
       matchident = OBJECT(unbound_symbol,self)->name->name;
      else if (INHERIT(OWNER(self),Language._Definition))
       matchident = OBJECT(Definition,self)->arg->name->name;
      else if (INHERIT(OWNER(self),Language._Call_plus))
       matchident = ((char*)".");
      else if (INHERIT(OWNER(self),Language._Call))
       matchident = OBJECT(Call,self)->selector->name->name;
      else if (INHERIT(OWNER(self),Language._Error))
       matchident = ((char*)"error");
      else if (INHERIT(OWNER(self),Language._Handle))
       matchident = ((char*)"catch");
      else matchident = ((INHERIT(OWNER(self),Language._While)) ?
        ((char*)"while") :
        ((INHERIT(OWNER(self),Language._Macro)) ?
          OBJECT(ClaireObject,self)->isa->name->name :
          ((INHERIT(OWNER(self),Language._Variable)) ?
            OBJECT(Variable,self)->pname->name :
            ((INHERIT(OWNER(self),Language._Assign)) ?
              ((char*)"=") :
              ((char*)"") ) ) ) );
      if ((CL_INT)LENGTH_STRING(matchident) > (CL_INT)0)
       { list * idents = GC_OBJECT(list,OBJECT(list,Reader.IDENTS->value));
        CL_INT  i = idents->length;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)i > (CL_INT)0))
          { GC_LOOP;
            { OID  loc = (*(idents))[i];
              if ((equal((*Kernel.nth)(loc,
                  ((OID)1)),_string_(matchident)) == CTRUE) || 
                  (((INHERIT(OWNER(self),Language._Call)) && (((OBJECT(Call,self)->selector == Kernel.nth_equal) || 
                        (OBJECT(Call,self)->selector == Core.write)) && 
                      (equal((*Kernel.nth)(loc,
                        ((OID)1)),_string_(((char*)"="))) == CTRUE))) || 
                    ((INHERIT(OWNER(self),Language._Call)) && ((OBJECT(Call,self)->selector == Kernel.nth) && 
                        (equal((*Kernel.nth)(loc,
                          ((OID)1)),_string_(((char*)"["))) == CTRUE)))))
               { if ((INHERIT(OWNER(self),Kernel._unbound_symbol)) || 
                    (INHERIT(OWNER(self),Language._Variable)))
                 { OID  l = GC_OID((*Kernel.copy)(loc));
                  skip_list(OBJECT(list,l),1);
                  put_table(Language.CODE_LOCS,self,l);
                  }
                else { (*Kernel._inf_inf)(loc,
                      ((OID)1));
                    put_table(Language.CODE_LOCS,self,loc);
                    shrink_list(idents,((CL_INT)i-(CL_INT)1));
                    }
                  { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                }
              i= (CL_INT)(((CL_INT)i-(CL_INT)1));
              }
            GC_UNLOOP;POP_SIGNAL;}
          }
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> equip method family takes an Instruction and a location that should
// de restore when the instruction terminates : the returned instruction is
// instrumented for debug.
// The c++ function for: update_location!(loc:list) [NEW_ALLOC]
CL_EXPORT OID  update_location_I_list1(list *loc) { 
    
    GC_BIND;
    { OID Result = 0;
      if (loc->length != 0)
       { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
        _void_(_CL_obj->selector = Core.update_location);
        _void_(_CL_obj->args = loc);
        add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
        Result = _oid_(close_Instruction1(_CL_obj));
        }
      else Result = ((OID)1);
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: update_location!(self:any,loc:list) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  update_location_I_any1(OID self,list *loc) { 
    
    GC_BIND;
    { OID Result = 0;
      if (loc->length != 0)
       { Variable * v;
        { { Instruction *V_CC ;
            { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(_CL_obj->pname = gensym_string(((char*)"ULOCDBG")));
              _void_(_CL_obj->dindex = 1);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            v= (Variable *) V_CC;}
          GC_OBJECT(Variable,v);}
        Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
        _void_(_CL_obj->var = v);
        _void_(_CL_obj->value = self);
        { Let * g0747 = _CL_obj; 
          OID  g0748;
          { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            { Do * g0749 = _CL_obj; 
              list * g0750;
              { OID v_bag;
                GC_ANY(g0750= list::empty(Kernel.emptySet));
                { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(_CL_obj->selector = Core.update_location);
                    _void_(_CL_obj->args = loc);
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                    v_bag = _oid_(close_Instruction1(_CL_obj));
                    }
                  GC_OID(v_bag);}
                ((list *) g0750)->addFast((OID)v_bag);
                ((list *) g0750)->addFast((OID)_oid_(v));}
              _void_(g0749->args = g0750);}
            add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
            g0748 = _oid_(close_Instruction1(_CL_obj));
            }
          _void_(g0747->arg = g0748);}
        add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
        Result = _oid_(close_Instruction1(_CL_obj));
        }
      else Result = self;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: pop_frame!(self:any) [NEW_ALLOC]
CL_EXPORT OID  pop_frame_I_any1(OID self) { 
    
    GC_BIND;
    { OID Result = 0;
      { Variable * v;
        { { Instruction *V_CC ;
            { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(_CL_obj->pname = gensym_string(((char*)"POPFDBG")));
              _void_(_CL_obj->dindex = 1);
              _void_(_CL_obj->index = ((CL_INT)Language._starvariable_index_star->value));
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            v= (Variable *) V_CC;}
          GC_OBJECT(Variable,v);}
        (Language._starvariable_index_star->value= ((OID)((CL_INT)(((CL_INT)Language._starvariable_index_star->value))+(CL_INT)1)));
        { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
          _void_(_CL_obj->var = v);
          _void_(_CL_obj->value = self);
          { Let * g0751 = _CL_obj; 
            OID  g0752;
            { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
              { Do * g0753 = _CL_obj; 
                list * g0754;
                { OID v_bag;
                  GC_ANY(g0754= list::empty(Kernel.emptySet));
                  { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(_CL_obj->selector = Core.pop_frame);
                      _void_(_CL_obj->args = list::alloc(1,_oid_(ClEnv)));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                      v_bag = _oid_(close_Instruction1(_CL_obj));
                      }
                    GC_OID(v_bag);}
                  ((list *) g0754)->addFast((OID)v_bag);
                  ((list *) g0754)->addFast((OID)_oid_(v));}
                _void_(g0753->args = g0754);}
              add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
              g0752 = _oid_(close_Instruction1(_CL_obj));
              }
            _void_(g0751->arg = g0752);}
          add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: pop_handle!(self:any,hid:Variable) [NEW_ALLOC]
CL_EXPORT OID  pop_handle_I_any1(OID self,Variable *hid) { 
    
    GC_BIND;
    { OID Result = 0;
      { Variable * v;
        { { Instruction *V_CC ;
            { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(_CL_obj->pname = gensym_string(((char*)"POPHDBG")));
              _void_(_CL_obj->dindex = 1);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            v= (Variable *) V_CC;}
          GC_OBJECT(Variable,v);}
        Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
        _void_(_CL_obj->var = v);
        _void_(_CL_obj->value = self);
        { Let * g0755 = _CL_obj; 
          OID  g0756;
          { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            { Do * g0757 = _CL_obj; 
              list * g0758;
              { OID v_bag;
                GC_ANY(g0758= list::empty(Kernel.emptySet));
                { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(_CL_obj->selector = Core.pop_handle);
                    _void_(_CL_obj->args = list::alloc(1,_oid_(hid)));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                    v_bag = _oid_(close_Instruction1(_CL_obj));
                    }
                  GC_OID(v_bag);}
                ((list *) g0758)->addFast((OID)v_bag);
                ((list *) g0758)->addFast((OID)_oid_(v));}
              _void_(g0757->args = g0758);}
            add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
            g0756 = _oid_(close_Instruction1(_CL_obj));
            }
          _void_(g0755->arg = g0756);}
        add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
        Result = _oid_(close_Instruction1(_CL_obj));
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:any,poploc:list) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  equip_any1_Reader(OID self,list *poploc) { 
    
    GC_BIND;
    { OID Result = 0;
      if (poploc->length != 0)
       { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
        _void_(_CL_obj->args = list::alloc(2,GC_OID(update_location_I_list1(poploc)),self));
        add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
        Result = _oid_(close_Instruction1(_CL_obj));
        }
      else Result = self;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//	update_location!(self, poploc)]
// The c++ function for: iClaire/equip(self:Instruction,poploc:list) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  equip_Instruction1_Reader(Instruction *self,list *poploc) { 
    
    GC_BIND;
    { OID  x = GC_OID(get_property(Kernel.arg,self));
      if (x != CNULL)
       put_property2(Kernel.arg,self,GC_OID((*Language.equip)(x,
        _oid_(poploc))));
      else ;}
    { OID  x = GC_OID(get_property(Kernel.body,self));
      if (x != CNULL)
       put_property2(Kernel.body,self,GC_OID((*Language.equip)(x,
        _oid_(poploc))));
      else ;}
    { OID  x = GC_OID(get_property(Kernel.value,self));
      if (x != CNULL)
       put_property2(Kernel.value,self,GC_OID((*Language.equip)(x,
        _oid_(poploc))));
      else ;}
    { OID  x = GC_OID(get_property(Kernel.of,self));
      if (x != CNULL)
       put_property2(Kernel.of,self,GC_OID((*Language.equip)(x,
        _oid_(poploc))));
      else ;}
    { OID  x = GC_OID(get_property(Language.other,self));
      if (x != CNULL)
       put_property2(Language.other,self,GC_OID((*Language.equip)(x,
        _oid_(poploc))));
      else ;}
    { OID  x = GC_OID(get_property(Language.test,self));
      if (x != CNULL)
       put_property2(Language.test,self,GC_OID((*Language.equip)(x,
        _oid_(poploc))));
      else ;}
    { OID  x = GC_OID(get_property(Core.args,self));
      if (x != CNULL)
       put_property2(Core.args,self,GC_OID(_oid_(equip_list_list1(GC_OBJECT(list,OBJECT(list,(*Core.args)(_oid_(self)))),poploc,1))));
      else ;}
    { OID Result = 0;
      Result = _oid_(self);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: equip_list(self:list,poploc:list,indexstart:integer) [NEW_ALLOC]
CL_EXPORT list * equip_list_list1(list *self,list *poploc,int indexstart) { 
    
    GC_BIND;
    { list *Result ;
      { CL_INT  len = self->length;
        list * res = GC_OBJECT(list,make_list_type1(Kernel._any,len));
        { CL_INT  i = 1;
          CL_INT  g0759 = ((CL_INT)indexstart-(CL_INT)1);
          { CL_INT loop_handle = ClEnv->cHandle;
            while (((CL_INT)i <= (CL_INT)g0759))
            { res->addFast((OID)(*(self))[i]);
              ++i;
              POP_SIGNAL;}
            }
          }
        { CL_INT  i = indexstart;
          CL_INT  g0760 = ((CL_INT)len-(CL_INT)1);
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)i <= (CL_INT)g0760))
            { GC_LOOP;
              res->addFast((OID)GC_OID((*Language.equip)((*(self))[i],
                Core.nil->value)));
              ++i;
              GC_UNLOOP;POP_SIGNAL;}
            }
          }
        if ((CL_INT)len > (CL_INT)((CL_INT)indexstart-(CL_INT)1))
         res->addFast((OID)GC_OID((*Language.equip)((*(self))[len],
          _oid_(poploc))));
        Result = res;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:unbound_symbol,poploc:list) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT OID  equip_unbound_symbol1_Reader(unbound_symbol *self,list *poploc) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  loc = nth_table1(Language.CODE_LOCS,_oid_(self));
        if (OBJECT(bag,loc)->length != 0)
         { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
          _void_(_CL_obj->args = list::alloc(2,GC_OID(update_location_I_list1(OBJECT(list,loc))),_oid_(self)));
          add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else if (poploc->length != 0)
         { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
          _void_(_CL_obj->args = list::alloc(2,GC_OID(update_location_I_list1(poploc)),_oid_(self)));
          add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else Result = _oid_(self);
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:Variable,poploc:list) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT OID  equip_Variable1_Reader(Variable *self,list *poploc) { 
    POP_SIGNAL; return (update_location_I_any1(_oid_(self),poploc));}
  


// The c++ function for: iClaire/equip(self:While,poploc:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  equip_While1_Reader(While *self,list *poploc) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  loc = nth_table1(Language.CODE_LOCS,_oid_(self));
        _void_(self->test = (*Language.equip)(GC_OID(self->test),
          Core.nil->value));
        _void_(self->arg = (*Language.equip)(GC_OID(self->arg),
          Core.nil->value));
        { OID  g0761UU;
          { { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
              _void_(_CL_obj->args = list::alloc(2,GC_OID(update_location_I_list1(OBJECT(list,loc))),_oid_(self)));
              add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
              g0761UU = _oid_(close_Instruction1(_CL_obj));
              }
            GC_OID(g0761UU);}
          Result = update_location_I_any1(g0761UU,poploc);
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:Error,poploc:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  equip_Error1_Reader(Error *self,list *poploc) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  loc = nth_table1(Language.CODE_LOCS,_oid_(self));
        OID  res = _oid_(self);
        if (OBJECT(bag,loc)->length != 0)
         { if ((CL_INT)self->args->length > (CL_INT)1)
           _void_(self->args = equip_list_list1(GC_OBJECT(list,self->args),OBJECT(list,loc),2));
          else { { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                _void_(_CL_obj->args = list::alloc(2,GC_OID(update_location_I_list1(OBJECT(list,loc))),_oid_(self)));
                add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
                res = _oid_(close_Instruction1(_CL_obj));
                }
              GC_OID(res);}
            }
        Result = res;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:Construct,poploc:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  equip_Construct1_Reader(Construct *self,list *poploc) { 
    
    GC_BIND;
    { OID Result = 0;
      if (boolean_I_any(_oid_(self->args)) != CTRUE)
       { if (poploc->length != 0)
         { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
          _void_(_CL_obj->args = list::alloc(2,GC_OID(update_location_I_list1(poploc)),_oid_(self)));
          add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        else Result = _oid_(self);
          }
      else { _void_(self->args = equip_list_list1(GC_OBJECT(list,self->args),poploc,1));
          Result = _oid_(self);
          }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:Call,poploc:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  equip_Call1_Reader(Call *self,list *poploc) { 
    
    GC_BIND;
    { OID Result = 0;
      { ClaireBoolean * g0762I;
        { OID  g0763UU;
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(x);
            g0763UU= Kernel.cfalse;
            bag *x_support;
            x_support = GC_OBJECT(list,self->args);
            for (START(x_support); NEXT(x);)
            { ClaireBoolean * g0764I;
              { OID  g0765UU;
                { ClaireBoolean * V_CL0766;{ OID  g0767UU;
                    if (INHERIT(OWNER(x),Language._Variable))
                     g0767UU = Kernel.ctrue;
                    else if ((OBJECT(ClaireBoolean,_oid_(((INHERIT(OWNER(x),Language._Call)) ? (((*Kernel.selector)(x) == _oid_(Core.externC)) ? CTRUE: CFALSE): CFALSE)))) == CTRUE)
                     g0767UU = Kernel.ctrue;
                    else if (INHERIT(OWNER(x),Language._Instruction))
                     g0767UU = Kernel.cfalse;
                    else g0767UU = Kernel.ctrue;
                      V_CL0766 = boolean_I_any(g0767UU);
                    }
                  
                  g0765UU=_oid_(V_CL0766);}
                g0764I = ((g0765UU != Kernel.ctrue) ? CTRUE : CFALSE);
                }
              
              if (g0764I == CTRUE) { g0763UU = Kernel.ctrue;
                  ClEnv->cHandle = loop_handle;break;}
                }
            }
          g0762I = not_any(g0763UU);
          }
        
        if (g0762I == CTRUE) { OID  g0768UU;
            { { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                _void_(_CL_obj->args = list::alloc(2,GC_OID(update_location_I_list1(OBJECT(list,nth_table1(Language.CODE_LOCS,_oid_(self))))),_oid_(self)));
                add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
                g0768UU = _oid_(close_Instruction1(_CL_obj));
                }
              GC_OID(g0768UU);}
            Result = update_location_I_any1(g0768UU,poploc);
            }
          else { OID  loc = nth_table1(Language.CODE_LOCS,_oid_(self));
          OID  res = _oid_(self);
          if (boolean_I_any(loc) != CTRUE)
           loc= (_oid_(poploc));
          if (OBJECT(bag,loc)->length != 0)
           { if (self->args->length != 0)
             _void_(self->args = equip_list_list1(GC_OBJECT(list,self->args),OBJECT(list,loc),1));
            else res= (GC_OID(update_location_I_any1(_oid_(self),OBJECT(list,loc))));
              }
          if ((poploc->length != 0) && 
              (equal(_oid_(poploc),loc) != CTRUE))
           Result = update_location_I_any1(_oid_(self),poploc);
          else Result = res;
            }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:Do,poploc:list) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  equip_Do1_Reader(Do *self,list *poploc) { 
    
    GC_BIND;
    _void_(self->args = equip_list_list1(GC_OBJECT(list,self->args),poploc,1));
    { OID Result = 0;
      Result = _oid_(self);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:Case,poploc:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  equip_Case1_Reader(Case *self,list *poploc) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  res = _oid_(self);
        if (inherit_ask_class(OWNER(self->var),Language._Variable) != CTRUE)
         { Variable * v;
          { { Instruction *V_CC ;
              { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                _void_(_CL_obj->pname = gensym_string(((char*)"CASEDBG")));
                _void_(_CL_obj->dindex = 1);
                add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              v= (Variable *) V_CC;}
            GC_OBJECT(Variable,v);}
          { { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
              _void_(_CL_obj->var = v);
              _void_(_CL_obj->value = (*Language.equip)(GC_OID(self->var),
                Core.nil->value));
              _void_(_CL_obj->arg = _oid_(self));
              add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
              res = _oid_(close_Instruction1(_CL_obj));
              }
            GC_OID(res);}
          _void_(self->var = _oid_(v));
          }
        { list * l = GC_OBJECT(list,self->args);
          CL_INT  len = l->length;
          list * nl = GC_OBJECT(list,make_list_type1(Kernel._any,len));
          { CL_INT  i = 1;
            CL_INT  g0769 = len;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while (((CL_INT)i <= (CL_INT)g0769))
              { GC_LOOP;
                if (mod_integer(i,2) == 0)
                 nl->addFast((OID)GC_OID((*Language.equip)((*(l))[i],
                  Core.nil->value)));
                else nl->addFast((OID)(*(l))[i]);
                  ++i;
                GC_UNLOOP;POP_SIGNAL;}
              }
            }
          _void_(self->args = nl);
          }
        Result = update_location_I_any1(res,poploc);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:If,poploc:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  equip_If1_Reader(If *self,list *poploc) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  res = _oid_(self);
        _void_(self->arg = (*Language.equip)(GC_OID(self->arg),
          Core.nil->value));
        _void_(self->other = (*Language.equip)(GC_OID(self->other),
          Core.nil->value));
        if ((INHERIT(OWNER(self->test),Language._Variable)) ? (CFALSE == CTRUE) : ((INHERIT(OWNER(self->test),Language._Instruction)) && (CTRUE == CTRUE)))
         { Variable * vtest;
          { { Instruction *V_CC ;
              { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
                _void_(_CL_obj->pname = gensym_string(((char*)"IFDBG")));
                _void_(_CL_obj->dindex = 1);
                add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              vtest= (Variable *) V_CC;}
            GC_OBJECT(Variable,vtest);}
          { { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
              _void_(_CL_obj->var = vtest);
              _void_(_CL_obj->value = (*Language.equip)(GC_OID(self->test),
                Core.nil->value));
              _void_(_CL_obj->arg = _oid_(self));
              add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
              res = _oid_(close_Instruction1(_CL_obj));
              }
            GC_OID(res);}
          _void_(self->test = _oid_(vtest));
          }
        Result = update_location_I_any1(res,poploc);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:Let,poploc:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  equip_Let1_Reader(Let *self,list *poploc) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  loc = nth_table1(Language.CODE_LOCS,_oid_(self->var));
        Variable * v;
        { { Instruction *V_CC ;
            { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(_CL_obj->pname = gensym_string(((char*)"LETDBG")));
              _void_(_CL_obj->dindex = 1);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            v= (Variable *) V_CC;}
          GC_OBJECT(Variable,v);}
        _void_(self->value = (*Language.equip)(GC_OID(self->value),
          Core.nil->value));
        { Let * g0770 = self; 
          OID  g0771;
          { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            { Do * g0772 = _CL_obj; 
              list * g0773;
              { OID v_bag;
                GC_ANY(g0773= list::empty(Kernel.emptySet));
                { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(_CL_obj->selector = Core.push_var);
                    _void_(_CL_obj->args = list::alloc(2,_string_(self->var->pname->name),GC_OID(_oid_(self->var))));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                    v_bag = _oid_(close_Instruction1(_CL_obj));
                    }
                  GC_OID(v_bag);}
                ((list *) g0773)->addFast((OID)v_bag);
                ((list *) g0773)->addFast((OID)GC_OID(update_location_I_list1(OBJECT(list,loc))));
                { { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                    _void_(_CL_obj->var = v);
                    _void_(_CL_obj->value = (*Language.equip)(GC_OID(self->arg),
                      Core.nil->value));
                    { Let * g0774 = _CL_obj; 
                      OID  g0775;
                      { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                        { Do * g0776 = _CL_obj; 
                          list * g0777;
                          { OID v_bag;
                            GC_ANY(g0777= list::empty(Kernel.emptySet));
                            { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                _void_(_CL_obj->selector = Core.pop_var);
                                _void_(_CL_obj->args = list::alloc(1,_oid_(ClEnv)));
                                add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                                v_bag = _oid_(close_Instruction1(_CL_obj));
                                }
                              GC_OID(v_bag);}
                            ((list *) g0777)->addFast((OID)v_bag);
                            ((list *) g0777)->addFast((OID)_oid_(v));}
                          _void_(g0776->args = g0777);}
                        add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
                        g0775 = _oid_(close_Instruction1(_CL_obj));
                        }
                      _void_(g0774->arg = g0775);}
                    add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
                    v_bag = _oid_(close_Instruction1(_CL_obj));
                    }
                  GC_OID(v_bag);}
                ((list *) g0773)->addFast((OID)v_bag);}
              _void_(g0772->args = g0773);}
            add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
            g0771 = _oid_(close_Instruction1(_CL_obj));
            }
          _void_(g0770->arg = g0771);}
        Result = update_location_I_any1(_oid_(self),poploc);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:When,poploc:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  equip_When1_Reader(When *self,list *poploc) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  loc = nth_table1(Language.CODE_LOCS,_oid_(self->var));
        Variable * v;
        { { Instruction *V_CC ;
            { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(_CL_obj->pname = gensym_string(((char*)"LETDBG")));
              _void_(_CL_obj->dindex = 1);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            v= (Variable *) V_CC;}
          GC_OBJECT(Variable,v);}
        _void_(self->value = (*Language.equip)(GC_OID(self->value),
          Core.nil->value));
        { OID  ot = GC_OID(self->other);
          if (ot == CNULL)
           ;else _void_(self->other = (*Language.equip)(ot,
              Core.nil->value));
            }
        { Let * g0778 = self; 
          OID  g0779;
          { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            { Do * g0780 = _CL_obj; 
              list * g0781;
              { OID v_bag;
                GC_ANY(g0781= list::empty(Kernel.emptySet));
                { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(_CL_obj->selector = Core.push_var);
                    _void_(_CL_obj->args = list::alloc(2,_string_(self->var->pname->name),GC_OID(_oid_(self->var))));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                    v_bag = _oid_(close_Instruction1(_CL_obj));
                    }
                  GC_OID(v_bag);}
                ((list *) g0781)->addFast((OID)v_bag);
                ((list *) g0781)->addFast((OID)GC_OID(update_location_I_list1(OBJECT(list,loc))));
                { { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
                    _void_(_CL_obj->var = v);
                    _void_(_CL_obj->value = (*Language.equip)(GC_OID(self->arg),
                      Core.nil->value));
                    { Let * g0782 = _CL_obj; 
                      OID  g0783;
                      { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                        { Do * g0784 = _CL_obj; 
                          list * g0785;
                          { OID v_bag;
                            GC_ANY(g0785= list::empty(Kernel.emptySet));
                            { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                                _void_(_CL_obj->selector = Core.pop_var);
                                _void_(_CL_obj->args = list::alloc(1,_oid_(ClEnv)));
                                add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                                v_bag = _oid_(close_Instruction1(_CL_obj));
                                }
                              GC_OID(v_bag);}
                            ((list *) g0785)->addFast((OID)v_bag);
                            ((list *) g0785)->addFast((OID)_oid_(v));}
                          _void_(g0784->args = g0785);}
                        add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
                        g0783 = _oid_(close_Instruction1(_CL_obj));
                        }
                      _void_(g0782->arg = g0783);}
                    add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
                    v_bag = _oid_(close_Instruction1(_CL_obj));
                    }
                  GC_OID(v_bag);}
                ((list *) g0781)->addFast((OID)v_bag);}
              _void_(g0780->args = g0781);}
            add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
            g0779 = _oid_(close_Instruction1(_CL_obj));
            }
          _void_(g0778->arg = g0779);}
        Result = update_location_I_any1(_oid_(self),poploc);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:Iteration,poploc:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  equip_Iteration1_Reader(Iteration *self,list *poploc) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  loc = nth_table1(Language.CODE_LOCS,_oid_(self->var));
        Variable * vbag;
        { { Instruction *V_CC ;
            { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(_CL_obj->pname = gensym_string(((char*)"BITERDBG")));
              _void_(_CL_obj->dindex = 1);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            vbag= (Variable *) V_CC;}
          GC_OBJECT(Variable,vbag);}
        Variable * ivar;
        { { Instruction *V_CC ;
            { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(_CL_obj->pname = gensym_string(((char*)"IITERDBG")));
              _void_(_CL_obj->dindex = 1);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            ivar= (Variable *) V_CC;}
          GC_OBJECT(Variable,ivar);}
        Let * res;
        { { Instruction *V_CC ;
            { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
              _void_(_CL_obj->var = vbag);
              _void_(_CL_obj->value = (*Language.equip)(GC_OID(self->set_arg),
                Core.nil->value));
              _void_(_CL_obj->arg = _oid_(self));
              add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            res= (Let *) V_CC;}
          GC_OBJECT(Let,res);}
        list * doargs = list::empty(Kernel._any);
        _void_(self->set_arg = _oid_(vbag));
        { OID  g0786UU;
          { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              _void_(_CL_obj->selector = Core.push_var);
              _void_(_CL_obj->args = list::alloc(2,_string_(self->var->pname->name),GC_OID(_oid_(self->var))));
              add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
              g0786UU = _oid_(close_Instruction1(_CL_obj));
              }
            GC_OID(g0786UU);}
          doargs->addFast((OID)g0786UU);
          }
        doargs->addFast((OID)GC_OID(update_location_I_list1(OBJECT(list,loc))));
        { OID  g0787UU;
          { { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
              _void_(_CL_obj->var = ivar);
              _void_(_CL_obj->value = (*Language.equip)(GC_OID(self->arg),
                Core.nil->value));
              { Let * g0788 = _CL_obj; 
                OID  g0789;
                { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                  { Do * g0790 = _CL_obj; 
                    list * g0791;
                    { OID v_bag;
                      GC_ANY(g0791= list::empty(Kernel.emptySet));
                      { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                          _void_(_CL_obj->selector = Core.pop_var);
                          _void_(_CL_obj->args = list::alloc(1,_oid_(ClEnv)));
                          add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                          v_bag = _oid_(close_Instruction1(_CL_obj));
                          }
                        GC_OID(v_bag);}
                      ((list *) g0791)->addFast((OID)v_bag);
                      ((list *) g0791)->addFast((OID)_oid_(ivar));}
                    _void_(g0790->args = g0791);}
                  add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
                  g0789 = _oid_(close_Instruction1(_CL_obj));
                  }
                _void_(g0788->arg = g0789);}
              add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
              g0787UU = _oid_(close_Instruction1(_CL_obj));
              }
            GC_OID(g0787UU);}
          doargs->addFast((OID)g0787UU);
          }
        { Iteration * g0792 = self; 
          OID  g0793;
          { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            _void_(_CL_obj->args = doargs);
            add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
            g0793 = _oid_(close_Instruction1(_CL_obj));
            }
          _void_(g0792->arg = g0793);}
        Result = update_location_I_any1(_oid_(res),poploc);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:For,poploc:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  equip_For1_Reader(For *self,list *poploc) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  loc = nth_table1(Language.CODE_LOCS,_oid_(self->var));
        Variable * vbag;
        { { Instruction *V_CC ;
            { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(_CL_obj->pname = gensym_string(((char*)"BFORDBG")));
              _void_(_CL_obj->dindex = 1);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            vbag= (Variable *) V_CC;}
          GC_OBJECT(Variable,vbag);}
        Variable * vfor;
        { { Instruction *V_CC ;
            { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(_CL_obj->pname = gensym_string(((char*)"RFORDBG")));
              _void_(_CL_obj->dindex = 1);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            vfor= (Variable *) V_CC;}
          GC_OBJECT(Variable,vfor);}
        Let * letbag;
        { { Instruction *V_CC ;
            { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
              _void_(_CL_obj->var = vbag);
              _void_(_CL_obj->value = (*Language.equip)(GC_OID(self->set_arg),
                Core.nil->value));
              add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            letbag= (Let *) V_CC;}
          GC_OBJECT(Let,letbag);}
        Let * letfor;
        { { Instruction *V_CC ;
            { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
              _void_(_CL_obj->var = vfor);
              _void_(_CL_obj->value = _oid_(self));
              add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            letfor= (Let *) V_CC;}
          GC_OBJECT(Let,letfor);}
        list * forargs = list::empty(Kernel._any);
        _void_(self->set_arg = _oid_(vbag));
        { Let * g0794 = letbag; 
          OID  g0795;
          { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            { Do * g0796 = _CL_obj; 
              list * g0797;
              { OID v_bag;
                GC_ANY(g0797= list::empty(Kernel.emptySet));
                { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(_CL_obj->selector = Core.push_var);
                    _void_(_CL_obj->args = list::alloc(2,_string_(self->var->pname->name),CNULL));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                    v_bag = _oid_(close_Instruction1(_CL_obj));
                    }
                  GC_OID(v_bag);}
                ((list *) g0797)->addFast((OID)v_bag);
                ((list *) g0797)->addFast((OID)_oid_(letfor));}
              _void_(g0796->args = g0797);}
            add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
            g0795 = _oid_(close_Instruction1(_CL_obj));
            }
          _void_(g0794->arg = g0795);}
        { Iteration * g0798 = self; 
          OID  g0799;
          { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            { Do * g0800 = _CL_obj; 
              list * g0801;
              { OID v_bag;
                GC_ANY(g0801= list::empty(Kernel.emptySet));
                { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(_CL_obj->selector = Core.update_var);
                    _void_(_CL_obj->args = list::alloc(2,_string_(self->var->pname->name),GC_OID(_oid_(self->var))));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                    v_bag = _oid_(close_Instruction1(_CL_obj));
                    }
                  GC_OID(v_bag);}
                ((list *) g0801)->addFast((OID)v_bag);
                ((list *) g0801)->addFast((OID)GC_OID(update_location_I_list1(OBJECT(list,loc))));
                ((list *) g0801)->addFast((OID)GC_OID((*Language.equip)(GC_OID(self->arg),
                  Core.nil->value)));}
              _void_(g0800->args = g0801);}
            add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
            g0799 = _oid_(close_Instruction1(_CL_obj));
            }
          _void_(g0798->arg = g0799);}
        { Let * g0802 = letfor; 
          OID  g0803;
          { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            { Do * g0804 = _CL_obj; 
              list * g0805;
              { OID v_bag;
                GC_ANY(g0805= list::empty(Kernel.emptySet));
                { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(_CL_obj->selector = Core.pop_var);
                    _void_(_CL_obj->args = list::alloc(1,_oid_(ClEnv)));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                    v_bag = _oid_(close_Instruction1(_CL_obj));
                    }
                  GC_OID(v_bag);}
                ((list *) g0805)->addFast((OID)v_bag);
                ((list *) g0805)->addFast((OID)_oid_(vfor));}
              _void_(g0804->args = g0805);}
            add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
            g0803 = _oid_(close_Instruction1(_CL_obj));
            }
          _void_(g0802->arg = g0803);}
        Result = update_location_I_any1(_oid_(letbag),poploc);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> a handle is a little tricky since we need a unique
// value that identifies the frame of the handle
// The c++ function for: iClaire/equip(self:Handle,poploc:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  equip_Handle1_Reader(ClaireHandle *self,list *poploc) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  loc = nth_table1(Language.CODE_LOCS,_oid_(self));
        Variable * hid;
        { { Instruction *V_CC ;
            { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(_CL_obj->range = Kernel._string);
              _void_(_CL_obj->dindex = 1);
              _void_(_CL_obj->pname = gensym_string(((char*)"HDLDBG")));
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            hid= (Variable *) V_CC;}
          GC_OBJECT(Variable,hid);}
        Let * lt;
        { { Instruction *V_CC ;
            { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
              _void_(_CL_obj->var = hid);
              { Let * g0806 = _CL_obj; 
                OID  g0807;
                { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                  _void_(_CL_obj->selector = Kernel.uid);
                  _void_(_CL_obj->args = list::alloc(1,_oid_(ClEnv)));
                  add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                  g0807 = _oid_(close_Instruction1(_CL_obj));
                  }
                _void_(g0806->value = g0807);}
              add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            lt= (Let *) V_CC;}
          GC_OBJECT(Let,lt);}
        { ClaireHandle * g0808 = self; 
          OID  g0809;
          { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            { Do * g0810 = _CL_obj; 
              list * g0811;
              { OID v_bag;
                GC_ANY(g0811= list::empty(Kernel.emptySet));
                { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(_CL_obj->selector = Core.push_handle);
                    _void_(_CL_obj->args = list::alloc(1,_oid_(hid)));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                    v_bag = _oid_(close_Instruction1(_CL_obj));
                    }
                  GC_OID(v_bag);}
                ((list *) g0811)->addFast((OID)v_bag);
                ((list *) g0811)->addFast((OID)GC_OID((*Language.equip)(GC_OID(self->arg),
                  Core.nil->value)));}
              _void_(g0810->args = g0811);}
            add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
            g0809 = _oid_(close_Instruction1(_CL_obj));
            }
          _void_(g0808->arg = g0809);}
        _void_(self->other = (*Language.equip)(GC_OID(self->other),
          Core.nil->value));
        if (OBJECT(bag,loc)->length != 0)
         { ClaireHandle * g0812 = self; 
          OID  g0813;
          { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            { Do * g0814 = _CL_obj; 
              list * g0815;
              { OID v_bag;
                GC_ANY(g0815= list::empty(Kernel.emptySet));
                { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(_CL_obj->selector = Core.push_handle_frame);
                    _void_(_CL_obj->args = append_list(OBJECT(list,loc),list::alloc(1,_oid_(hid))));
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                    v_bag = _oid_(close_Instruction1(_CL_obj));
                    }
                  GC_OID(v_bag);}
                ((list *) g0815)->addFast((OID)v_bag);
                ((list *) g0815)->addFast((OID)GC_OID(self->other));}
              _void_(g0814->args = g0815);}
            add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
            g0813 = _oid_(close_Instruction1(_CL_obj));
            }
          _void_(g0812->other = g0813);}
        _void_(lt->arg = pop_handle_I_any1(_oid_(self),hid));
        if (poploc->length != 0)
         _void_(lt->arg = update_location_I_any1(GC_OID(lt->arg),poploc));
        Result = _oid_(lt);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:Assign,poploc:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  equip_Assign1_Reader(Assign *self,list *poploc) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  loc = nth_table1(Language.CODE_LOCS,_oid_(self));
        Variable * v;
        { { Instruction *V_CC ;
            { Variable * _CL_obj = ((Variable *) GC_OBJECT(Variable,new_object_class(Language._Variable)));
              _void_(_CL_obj->pname = gensym_string(((char*)"ASGDBG")));
              _void_(_CL_obj->dindex = 1);
              add_I_property(Kernel.instances,Language._Variable,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            v= (Variable *) V_CC;}
          GC_OBJECT(Variable,v);}
        OID  narg = GC_OID((*Language.equip)(GC_OID(self->arg),
          loc));
        _void_(self->arg = _oid_(v));
        { Let * _CL_obj = ((Let *) GC_OBJECT(Let,new_object_class(Language._Let)));
          _void_(_CL_obj->var = v);
          _void_(_CL_obj->value = narg);
          { Let * g0816 = _CL_obj; 
            OID  g0817;
            { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
              { Do * g0818 = _CL_obj; 
                list * g0819;
                { OID v_bag;
                  GC_ANY(g0819= list::empty(Kernel.emptySet));
                  { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                      _void_(_CL_obj->selector = Core.update_var);
                      _void_(_CL_obj->args = list::alloc(2,_string_(OBJECT(Variable,self->var)->pname->name),GC_OID(self->var)));
                      add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                      v_bag = _oid_(close_Instruction1(_CL_obj));
                      }
                    GC_OID(v_bag);}
                  ((list *) g0819)->addFast((OID)v_bag);
                  ((list *) g0819)->addFast((OID)_oid_(self));
                  ((list *) g0819)->addFast((OID)GC_OID(update_location_I_list1(poploc)));
                  ((list *) g0819)->addFast((OID)_oid_(v));}
                _void_(g0818->args = g0819);}
              add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
              g0817 = _oid_(close_Instruction1(_CL_obj));
              }
            _void_(g0816->arg = g0817);}
          add_I_property(Kernel.instances,Language._Let,11,_oid_(_CL_obj));
          Result = _oid_(close_Instruction1(_CL_obj));
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:Defclaire,poploc:list) [RETURN_ARG]
CL_EXPORT OID  equip_Defclaire1_Reader(Defclaire *self,list *poploc) { 
    POP_SIGNAL; return (_oid_(self));}
  


// The c++ function for: iClaire/equip(self:Definition,poploc:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  equip_Definition1_Reader(Definition *self,list *poploc) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  loc = nth_table1(Language.CODE_LOCS,_oid_(self));
        list * vs = GC_OBJECT(list,self->args);
        CL_INT  len = vs->length;
        OID  res = _oid_(self);
        { CL_INT  i = 1;
          CL_INT  g0820 = len;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)i <= (CL_INT)g0820))
            { GC_LOOP;
              { OID  a = (*(vs))[i];
                if (length_bag(OBJECT(bag,(*Core.args)(a))) == 2)
                 { OID  g0821UU;
                  { { list * V_CL0822;{ OID v_bag;
                        GC_ANY(V_CL0822= list::empty(Kernel.emptySet));
                        ((list *) V_CL0822)->addFast((OID)GC_OID((*(OBJECT(bag,(*Core.args)(a))))[1]));
                        { { OID  g0823UU;
                            if ((CL_INT)i < (CL_INT)len)
                             g0823UU = Core.nil->value;
                            else g0823UU = loc;
                              v_bag = (*Language.equip)(GC_OID((*(OBJECT(bag,(*Core.args)(a))))[2]),
                              g0823UU);
                            }
                          GC_OID(v_bag);}
                        ((list *) V_CL0822)->addFast((OID)v_bag);}
                      
                      g0821UU=_oid_(V_CL0822);}
                    GC_OID(g0821UU);}
                  put_property2(Core.args,OBJECT(ClaireObject,a),g0821UU);
                  }
                }
              ++i;
              GC_UNLOOP;POP_SIGNAL;}
            }
          }
        if ((OBJECT(bag,loc)->length != 0) && 
            (len == 0))
         { { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
            _void_(_CL_obj->args = list::alloc(2,GC_OID(update_location_I_list1(OBJECT(list,loc))),res));
            add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
            res = _oid_(close_Instruction1(_CL_obj));
            }
          GC_OID(res);}
        if (poploc->length != 0)
         res= (GC_OID(update_location_I_any1(res,poploc)));
        Result = res;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:Defobj,poploc:list) [RETURN_ARG]
CL_EXPORT OID  equip_Defobj1_Reader(Defobj *self,list *poploc) { 
    POP_SIGNAL; return (_oid_(self));}
  


// The c++ function for: iClaire/equip(self:Defrule,poploc:list) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  equip_Defrule1_Reader(Defrule *self,list *poploc) { 
    
    GC_BIND;
    _void_(self->body = (*Language.equip)(GC_OID(self->body),
      Core.nil->value));
    { OID Result = 0;
      Result = _oid_(self);
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:any) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT OID  equip_any2_Reader(OID self) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  x = GC_OID((*Language.equip)(self,
          Core.nil->value));
        lexical_build_equip_any1(x,((CL_INT)Language._starvariable_index_star->value));
        _void_(Reader.reader->maxstack = ((CL_INT)Language._starvariable_index_star->value));
        Result = x;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: iClaire/equip(self:lambda) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  equip_lambda1_Reader(lambda *self) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  loc;
        if (((self->body == CNULL) ? CTRUE : CFALSE) != CTRUE)
         loc = nth_table1(Language.CODE_LOCS,self->body);
        else loc = Core.nil->value;
          { Do * b;
          { { Instruction *V_CC ;
              { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
                add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
                V_CC = close_Instruction1(_CL_obj);
                }
              b= (Do *) V_CC;}
            GC_OBJECT(Do,b);}
          { OID  g0825UU;
            { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                _void_(_CL_obj->selector = Core.push_frame);
                _void_(_CL_obj->args = list::alloc(1,_string_(((char*)"placeholder"))));
                add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                g0825UU = _oid_(close_Instruction1(_CL_obj));
                }
              GC_OID(g0825UU);}
            GC_OBJECT(list,b->args)->addFast((OID)g0825UU);
            }
          { CL_INT  i = 1;
            CL_INT  g0824 = self->vars->length;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while (((CL_INT)i <= (CL_INT)g0824))
              { GC_LOOP;
                { OID  x = GC_OID((*(self->vars))[i]);
                  if ((*Kernel.range)(x) != _oid_(Kernel._void))
                   { OID  g0826UU;
                    { { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                        _void_(_CL_obj->selector = Core.push_arg);
                        _void_(_CL_obj->args = list::alloc(2,_string_(OBJECT(Variable,x)->pname->name),x));
                        add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                        g0826UU = _oid_(close_Instruction1(_CL_obj));
                        }
                      GC_OID(g0826UU);}
                    GC_OBJECT(list,b->args)->addFast((OID)g0826UU);
                    }
                  }
                ++i;
                GC_UNLOOP;POP_SIGNAL;}
              }
            }
          GC_OBJECT(list,b->args)->addFast((OID)GC_OID(pop_frame_I_any1(GC_OID(self->body))));
          _void_(self->body = _oid_(b));
          }
        _void_(self->dimension = ((CL_INT)Language._starvariable_index_star->value));
        Result = _oid_(self);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: lexical_build_equip(self:any,n:integer) [SLOT_UPDATE]
CL_EXPORT void  lexical_build_equip_any1(OID self,int n) { 
    if (INHERIT(OWNER(self),Kernel._bag))
     { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(x);
      for (START(OBJECT(bag,self)); NEXT(x);)
      lexical_build_equip_any1(x,n);
      }
    else if (INHERIT(OWNER(self),Language._Let))
     { if ((CL_INT)OBJECT(Instruction_with_var,self)->var->dindex > (CL_INT)0)
       { _void_(OBJECT(Instruction_with_var,self)->var->index = n);
        if ((CL_INT)n > (CL_INT)((CL_INT)Language._starvariable_index_star->value))
         (Language._starvariable_index_star->value= ((OID)n));
        lexical_build_equip_any1(OBJECT(Let,self)->value,((CL_INT)n+(CL_INT)1));
        lexical_build_equip_any1(OBJECT(Let,self)->arg,((CL_INT)n+(CL_INT)1));
        }
      else { lexical_build_equip_any1(OBJECT(Let,self)->value,n);
          lexical_build_equip_any1(OBJECT(Let,self)->arg,n);
          }
        }
    else if (INHERIT(OWNER(self),Language._Instruction))
     { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(s);
      bag *s_support;
      s_support = OWNER(self)->slots;
      for (START(s_support); NEXT(s);)
      { OID  y = get_slot(OBJECT(slot,s),OBJECT(ClaireObject,self));
        lexical_build_equip_any1(y,n);
        }
      }
    else ;POP_SIGNAL;}
  



/***** CLAIRE Compilation of file ./meta/complete.cl 
         [version 3.5.0 / safety 5] *****/


//*********************************************************************
//* CLAIRE                                            Sylvain Benilan *
//* complete.cl                                                       *
//* Copyright (C) 2000 - 2003 xl. All Rights Reserved                 *
//*********************************************************************
//<sb> this file contains some completion facility for the command
// line interpreter, it defines generic completion method for both
// claire and shell interpreters.
// The completion style is inspired from zle (zsh command line editor)
// in the way that hitting TAB repeatedly update the command line with
// possible matches.
//<sb> Claire completion is made on any named entity (classes and things)
//<sb> An interpreter should define the following callback that,
// for instances, are convenient for readline library (note that
// in the readline case we doesn't use readline internal completion
// facilities and we access readline buffer directly)
// *********************************************************************
// * Table of content:                                                 *
// * 1. claire completion                                              *
// * 2. shell completion                                               *
// *********************************************************************
// *********************************************************************
// * 1. claire completion                                              *
// *********************************************************************
// The c++ function for: completion_reset(_CL_obj:void) [0]
CL_EXPORT void  completion_reset_void() { 
    (Reader.COMPLETE_START_POSITION->value= ((OID)-1));
    (Reader.LAST_LINE->value= _string_(((char*)"")));
    (Reader.MATCH_INDEX->value= ((OID)0));
    (Reader.LAST_POSITION->value= ((OID)-1));
    (Reader.LAST_MODULE->value= _oid_(claire.it));
    shrink_list(OBJECT(bag,Reader.MATCHES->value),0);
    POP_SIGNAL;}
  


// The c++ function for: explode_separators(s:string) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT void  explode_separators_string(char *s) { 
    
    GC_BIND;
    shrink_list(OBJECT(bag,Reader.LAST_EXPLODED->value),0);
    { CL_INT  p1 = 1;
      CL_INT  len = LENGTH_STRING(s);
      list * l = GC_OBJECT(list,OBJECT(list,Reader.LAST_EXPLODED->value));
      { CL_INT  p2 = 1;
        CL_INT  g0827 = len;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)p2 <= (CL_INT)g0827))
          { GC_LOOP;
            if ((s[p2 - 1] == ((unsigned char)' ')) || 
                ((s[p2 - 1] == ((unsigned char)'"')) || 
                  ((s[p2 - 1] == ((unsigned char)'\'')) || 
                    ((s[p2 - 1] == ((unsigned char)'(')) || 
                      ((s[p2 - 1] == ((unsigned char)')')) || 
                        ((s[p2 - 1] == ((unsigned char)',')) || 
                          ((s[p2 - 1] == ((unsigned char)'.')) || 
                            ((s[p2 - 1] == ((unsigned char)'/')) || 
                              ((s[p2 - 1] == ((unsigned char)':')) || 
                                ((s[p2 - 1] == ((unsigned char)';')) || 
                                  ((s[p2 - 1] == ((unsigned char)'<')) || 
                                    ((s[p2 - 1] == ((unsigned char)'>')) || 
                                      ((s[p2 - 1] == ((unsigned char)'@')) || 
                                        ((s[p2 - 1] == ((unsigned char)'[')) || 
                                          ((s[p2 - 1] == ((unsigned char)']')) || 
                                            ((s[p2 - 1] == ((unsigned char)'{')) || 
                                              ((s[p2 - 1] == ((unsigned char)'|')) || 
                                                (s[p2 - 1] == ((unsigned char)'}')))))))))))))))))))
             { if (((CL_INT)p2 > (CL_INT)p1) && 
                  ((CL_INT)p1 <= (CL_INT)len))
               l= (l->addFast((OID)GC_OID(_string_(substring_string(s,p1,((CL_INT)p2-(CL_INT)1))))));
              l= (l->addFast((OID)_oid_(_char_(s[p2 - 1]))));
              p1= (CL_INT)(((CL_INT)p2+(CL_INT)1));
              }
            ++p2;
            GC_UNLOOP;POP_SIGNAL;}
          }
        }
      if ((CL_INT)p1 <= (CL_INT)len)
       l= (l->addFast((OID)GC_OID(_string_(substring_string(s,p1,len)))));
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: same_tree?(a:module) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * same_tree_ask_module(module *a) { 
    { ClaireBoolean *Result ;
      Result = ((_oid_(a) == Reader.LAST_MODULE->value) ?
        CTRUE :
        ((a == claire.it) ?
          CFALSE :
          same_tree_ask_module(a->part_of) ) );
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: complete_named_object(o:string,l:list[string]) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  complete_named_object_string(char *o,list *l) { 
    
    GC_BIND;
    { CL_INT  p = LENGTH_STRING(o);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(s);
        bag *s_support;
        s_support = GC_OBJECT(bag,enumerate_any(GC_OID(_oid_(U_type(Kernel._thing,Kernel._class)))));
        for (START(s_support); NEXT(s);)
        { GC_LOOP;
          if ((((OBJECT(symbol,(*Kernel.name)(s))->definition == (NULL)) ? CTRUE : CFALSE) != CTRUE) && 
              (equal_string(o,substring_string(OBJECT(symbol,(*Kernel.name)(s))->name,1,p)) == CTRUE))
           { OID  x = value_module(OBJECT(module,Reader.LAST_MODULE->value),OBJECT(symbol,(*Kernel.name)(s))->name);
            if (x != CNULL)
             l= (l->addFast((OID)_string_(OBJECT(symbol,(*Kernel.name)(s))->name)));
            else if (same_tree_ask_module(OBJECT(symbol,(*Kernel.name)(s))->module_I) == CTRUE)
             l= (l->addFast((OID)GC_OID(_string_(append_string(GC_STRING(append_string(OBJECT(symbol,(*Kernel.name)(s))->module_I->name->name,((char*)"/"))),OBJECT(symbol,(*Kernel.name)(s))->name)))));
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: complete_slot(o:string,l:list[string]) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT void  complete_slot_string(char *o,list *l) { 
    
    GC_BIND;
    { CL_INT  p = LENGTH_STRING(o);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(s);
        bag *s_support;
        s_support = Kernel._slot->instances;
        for (START(s_support); NEXT(s);)
        { GC_LOOP;
          if ((((OBJECT(restriction,s)->selector->name->definition == (NULL)) ? CTRUE : CFALSE) != CTRUE) && 
              (equal_string(o,substring_string(OBJECT(restriction,s)->selector->name->name,1,p)) == CTRUE))
           { OID  x = value_module(OBJECT(module,Reader.LAST_MODULE->value),OBJECT(restriction,s)->selector->name->name);
            if (x != CNULL)
             l= (l->addFast((OID)_string_(OBJECT(restriction,s)->selector->name->name)));
            else if (same_tree_ask_module(OBJECT(restriction,s)->selector->name->module_I) == CTRUE)
             l= (l->addFast((OID)GC_OID(_string_(append_string(GC_STRING(append_string(OBJECT(restriction,s)->selector->name->module_I->name->name,((char*)"/"))),OBJECT(restriction,s)->selector->name->name)))));
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: complete_class(o:string,l:list[string]) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT void  complete_class_string(char *o,list *l) { 
    
    GC_BIND;
    { CL_INT  p = LENGTH_STRING(o);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(s);
        bag *s_support;
        s_support = Kernel._class->instances;
        for (START(s_support); NEXT(s);)
        { GC_LOOP;
          if ((((OBJECT(ClaireClass,s)->name->definition == (NULL)) ? CTRUE : CFALSE) != CTRUE) && 
              (equal_string(o,substring_string(OBJECT(ClaireClass,s)->name->name,1,p)) == CTRUE))
           { OID  x = value_module(OBJECT(module,Reader.LAST_MODULE->value),OBJECT(ClaireClass,s)->name->name);
            if (x != CNULL)
             l= (l->addFast((OID)_string_(OBJECT(ClaireClass,s)->name->name)));
            else if (same_tree_ask_module(OBJECT(ClaireClass,s)->name->module_I) == CTRUE)
             l= (l->addFast((OID)GC_OID(_string_(append_string(GC_STRING(append_string(OBJECT(ClaireClass,s)->name->module_I->name->name,((char*)"/"))),OBJECT(ClaireClass,s)->name->name)))));
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: nodup(l:list[string]) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  nodup_list(list *l) { 
    
    GC_BIND;
    shrink_list(OBJECT(bag,Reader.MATCHES->value),0);
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(i);
      for (START(l); NEXT(i);)
      { GC_LOOP;
        if (contain_ask_list(OBJECT(list,Reader.MATCHES->value),i) != CTRUE)
         (Reader.MATCHES->value= _oid_(GC_OBJECT(list,OBJECT(list,Reader.MATCHES->value))->addFast((OID)i)));
        GC_UNLOOP; POP_SIGNAL;}
      }
    (Reader.MATCHES->value= _oid_(sort_method(GC_OBJECT(method,((method *) _at_property1(Kernel._inf,Kernel._string))),GC_OBJECT(list,OBJECT(list,Reader.MATCHES->value)))));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: fill_claire_matches(buf:string,end:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  fill_claire_matches_string(char *buf,int end) { 
    
    GC_BIND;
    { char * tmp = GC_STRING(substring_string(buf,1,end));
      list * l;
      { { explode_separators_string(tmp);
          l = OBJECT(list,Reader.LAST_EXPLODED->value);
          }
        GC_OBJECT(list,l);}
      CL_INT  len = l->length;
      list * res = list::empty(Kernel._string);
      (Reader.LAST_MODULE->value= _oid_(ClEnv->module_I));
      if (Kernel._string == OWNER((*(l))[len]))
       (Reader.COMPLETE_START_POSITION->value= ((OID)((CL_INT)((CL_INT)end-(CL_INT)LENGTH_STRING(string_v((*(l))[len])))+(CL_INT)1)));
      else (Reader.COMPLETE_START_POSITION->value= ((OID)-1));
        if (((CL_INT)3 <= (CL_INT)len) && 
          (((*(l))[((CL_INT)len-(CL_INT)1)] == _oid_(_char_(((unsigned char)'/')))) && 
            ((Kernel._string == OWNER((*(l))[((CL_INT)len-(CL_INT)2)])) && 
              (Kernel._string == OWNER((*(l))[len])))))
       { OID  x = value_string(string_v((*(l))[((CL_INT)len-(CL_INT)2)]));
        if (x != CNULL)
         { if (INHERIT(OWNER(x),Kernel._module))
           { (Reader.LAST_MODULE->value= x);
            delete_at_list(l,((CL_INT)len-(CL_INT)2));
            delete_at_list(l,((CL_INT)len-(CL_INT)2));
            len= (CL_INT)(l->length);
            }
          }
        else ;}
      else if (((CL_INT)4 <= (CL_INT)len) && 
          (((*(l))[len] == _oid_(_char_(((unsigned char)'(')))) && 
            ((Kernel._string == OWNER((*(l))[((CL_INT)len-(CL_INT)1)])) && 
              (((*(l))[((CL_INT)len-(CL_INT)2)] == _oid_(_char_(((unsigned char)'/')))) && 
                (Kernel._string == OWNER((*(l))[((CL_INT)len-(CL_INT)3)]))))))
       { OID  x = value_string(string_v((*(l))[((CL_INT)len-(CL_INT)3)]));
        if (x != CNULL)
         { if (INHERIT(OWNER(x),Kernel._module))
           (Reader.LAST_MODULE->value= x);
          }
        else ;}
      if (((CL_INT)len > (CL_INT)0) && 
          (Kernel._string == OWNER((*(l))[len])))
       { if ((((CL_INT)len > (CL_INT)2) && 
              (((*(l))[((CL_INT)len-(CL_INT)2)] == _oid_(_char_(((unsigned char)'<')))) && 
                ((*(l))[((CL_INT)len-(CL_INT)1)] == _oid_(_char_(((unsigned char)'(')))))) || 
            ((((CL_INT)len > (CL_INT)1) && 
                (((*(l))[((CL_INT)len-(CL_INT)1)] == _oid_(_char_(((unsigned char)'<')))) || 
                    ((*(l))[((CL_INT)len-(CL_INT)1)] == _oid_(_char_(((unsigned char)'[')))))) || 
              ((((CL_INT)len > (CL_INT)2) && 
                  ((Kernel._string == OWNER((*(l))[((CL_INT)len-(CL_INT)2)])) && 
                    ((*(l))[((CL_INT)len-(CL_INT)1)] == _oid_(_char_(((unsigned char)':')))))) || 
                ((((CL_INT)len > (CL_INT)2) && 
                    (((*(l))[((CL_INT)len-(CL_INT)1)] == _oid_(_char_(((unsigned char)' ')))) && 
                      (equal((*(l))[((CL_INT)len-(CL_INT)2)],_string_(((char*)"U"))) == CTRUE))) || 
                  (((CL_INT)len > (CL_INT)3) && 
                      (((*(l))[((CL_INT)len-(CL_INT)1)] == _oid_(_char_(((unsigned char)' ')))) && 
                        (((*(l))[((CL_INT)len-(CL_INT)2)] == _oid_(_char_(((unsigned char)':')))) && 
                          ((*(l))[((CL_INT)len-(CL_INT)3)] == _oid_(_char_(((unsigned char)' ')))))))))))
         complete_class_string(string_v((*(l))[len]),res);
        else if (((CL_INT)len > (CL_INT)1) && 
            ((*(l))[((CL_INT)len-(CL_INT)1)] == _oid_(_char_(((unsigned char)'.')))))
         complete_slot_string(string_v((*(l))[len]),res);
        else complete_named_object_string(string_v((*(l))[len]),res);
          }
      nodup_list(res);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: match_prefix(_CL_obj:void) [NEW_ALLOC]
CL_EXPORT char * match_prefix_void() { 
    
    GC_BIND;
    { char *Result ;
      { list * ll;
        { { CL_INT loop_handle = ClEnv->cHandle;
            bag *v_list; OID v_val;
            OID i; CL_INT CLcount;
            v_list = GC_OBJECT(list,OBJECT(bag,Reader.MATCHES->value));
             ll = v_list->clone(Kernel._string);
            for (CLcount= 1; CLcount <= v_list->length; CLcount++)
            { i = (*(v_list))[CLcount];
              v_val = last_list(explode_string(string_v(i),((char*)"/")));
              
              (*((list *) ll))[CLcount] = v_val;}
            }
          GC_OBJECT(list,ll);}
        char * res = GC_STRING(copy_string(string_v((*(ll))[1])));
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(i);
          for (START(ll); NEXT(i);)
          { CL_INT  lres = LENGTH_STRING(res);
            CL_INT  li = LENGTH_STRING(string_v(i));
            if (lres == 0)
             { ;ClEnv->cHandle = loop_handle; break;}
            if ((CL_INT)li < (CL_INT)lres)
             { shrink_string(res,li);
              lres= (CL_INT)(li);
              }
            { CL_INT  j = 1;
              CL_INT  g0828 = lres;
              { CL_INT loop_handle = ClEnv->cHandle;
                while (((CL_INT)j <= (CL_INT)g0828))
                { if (res[j - 1] != string_v(i)[j - 1])
                   { shrink_string(res,((CL_INT)j-(CL_INT)1));
                    { ;ClEnv->cHandle = loop_handle; break;}
                    }
                  ++j;
                  POP_SIGNAL;}
                }
              }
            }
          }
        Result = res;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: method_description(m:method) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT char * method_description_method(method *m) { 
    
    GC_RESERVE(2);  // v3.3.39 optim !
    { char *Result ;
      { char * res = m->selector->name->name;
        ClaireBoolean * first_ask = CTRUE;
        res= (GC_STRING(append_string(res,((char*)"("))));
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(a);
          for (START(m->domain); NEXT(a);)
          { GC_LOOP;
            { if (first_ask == CTRUE)
               first_ask= (CFALSE);
              else GC__STRING(res = append_string(res,((char*)", ")), 1);
                { { char * g0829UU;
                  { { print_in_string_void();
                      print_any(a);
                      g0829UU = end_of_string_void();
                      }
                    GC_STRING(g0829UU);}
                  res = append_string(res,g0829UU);
                  }
                 GC__STRING(res, 2);}
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        res= (GC_STRING(append_string(res,((char*)") `BLUE-> `BLACK"))));
        { { char * g0830UU;
            { { print_in_string_void();
                print_any(_oid_(m->range));
                g0830UU = end_of_string_void();
                }
              GC_STRING(g0830UU);}
            res = append_string(res,g0830UU);
            }
          GC_STRING(res);}
        Result = res;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: class_description(self:class) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT char * class_description_class(ClaireClass *self) { 
    
    GC_BIND;
    print_in_string_void();
    print_any(_oid_(self));
    princ_string(((char*)" <: "));
    print_any(_oid_(self->superclass));
    princ_string(((char*)"\n"));
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(s);
      for (START(self->slots); NEXT(s);)
      { GC_LOOP;
        if (s != _oid_(_at_property1(Kernel.isa,Kernel._object)))
         { if (s != _oid_(_at_property1(Kernel.name,Kernel._thing)))
           { print_any(_oid_(OBJECT(restriction,s)->selector));
            princ_string(((char*)":"));
            print_any(_oid_(OBJECT(restriction,s)->range));
            princ_string(((char*)" = "));
            print_any(GC_OID(OBJECT(slot,s)->DEFAULT));
            princ_string(((char*)"\n"));
            }
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    { char *Result ;
      Result = end_of_string_void();
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: claire_complete(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  claire_complete_void() { 
    
    GC_BIND;
    { PortObject * oldtrace = GC_OBJECT(PortObject,ClEnv->ctrace);
      _void_(ClEnv->ctrace = null_I_void1());
      { CL_INT  pos = interpreter_get_cursor_position();
        char * line = GC_STRING(interpreter_get_text());
        if ((OBJECT(bag,Reader.MATCHES->value)->length != 0) && 
            ((((OID)pos) == Reader.LAST_POSITION->value) && 
              ((equal(_string_(line),Reader.LAST_LINE->value) == CTRUE) && 
                (Reader.COMPLETE_START_POSITION->value != ((OID)-1)))))
         { interpreter_delete_text(((CL_INT)Reader.COMPLETE_START_POSITION->value),pos);
          (Reader.MATCH_INDEX->value= ((OID)((CL_INT)(((CL_INT)Reader.MATCH_INDEX->value))+(CL_INT)1)));
          if (Reader.MATCH_INDEX->value == ((OID)OBJECT(bag,Reader.MATCHES->value)->length))
           ding_void();
          if ((CL_INT)((CL_INT)Reader.MATCH_INDEX->value) > (CL_INT)OBJECT(bag,Reader.MATCHES->value)->length)
           (Reader.MATCH_INDEX->value= ((OID)1));
          interpreter_insert_text(string_v((*(OBJECT(bag,Reader.MATCHES->value)))[((CL_INT)Reader.MATCH_INDEX->value)]));
          (Reader.LAST_POSITION->value= ((OID)interpreter_get_cursor_position()));
          (Reader.LAST_LINE->value= _string_(interpreter_get_text()));
          }
        else { fill_claire_matches_string(line,((CL_INT)pos-(CL_INT)1));
            if (OBJECT(bag,Reader.MATCHES->value)->length != 0)
             { (Reader.MATCH_INDEX->value= ((OID)0));
              (Reader.LAST_POSITION->value= ((OID)pos));
              (Reader.LAST_LINE->value= _string_(interpreter_get_text()));
              if (OBJECT(bag,Reader.MATCHES->value)->length == 1)
               { claire_complete_void();
                (Reader.COMPLETE_START_POSITION->value= ((OID)-1));
                }
              else { char * mp = GC_STRING(match_prefix_void());
                  if ((CL_INT)LENGTH_STRING(mp) > (CL_INT)((CL_INT)pos-(CL_INT)(((CL_INT)Reader.COMPLETE_START_POSITION->value))))
                   { shrink_list(OBJECT(bag,Reader.MATCHES->value),0);
                    (Reader.MATCHES->value= _oid_(GC_OBJECT(list,OBJECT(list,Reader.MATCHES->value))->addFast((OID)_string_(mp))));
                    claire_complete_void();
                    (Reader.COMPLETE_START_POSITION->value= ((OID)-1));
                    }
                  else { ding_void();
                      interpreter_display_list(OBJECT(list,Reader.MATCHES->value));
                      (Reader.MATCHES->value= _oid_(GC_OBJECT(list,OBJECT(list,Reader.MATCHES->value))->addFast((OID)GC_OID(_string_(substring_string(line,((CL_INT)Reader.COMPLETE_START_POSITION->value),((CL_INT)pos-(CL_INT)1)))))));
                      }
                    }
                }
            else { list * l = GC_OBJECT(list,OBJECT(list,Reader.LAST_EXPLODED->value));
                CL_INT  len = l->length;
                if (((CL_INT)len > (CL_INT)1) && 
                    (((*(l))[len] == _oid_(_char_(((unsigned char)'.')))) && 
                      (Kernel._string == OWNER((*(l))[((CL_INT)len-(CL_INT)1)]))))
                 { OID  p = value_module(OBJECT(module,Reader.LAST_MODULE->value),string_v((*(l))[((CL_INT)len-(CL_INT)1)]));
                  if (p != CNULL)
                   { if (INHERIT(OWNER(p),Kernel._class))
                     interpreter_display_list(list::alloc(Kernel._string,1,GC_OID(_string_(class_description_class(OBJECT(ClaireClass,p))))));
                    else interpreter_display_list(list::alloc(Kernel._string,1,GC_OID(_string_(class_description_class(OWNER(p))))));
                      ding_void();
                    }
                  else ;}
                else if (((CL_INT)len > (CL_INT)1) && 
                    (((*(l))[len] == _oid_(_char_(((unsigned char)'(')))) && 
                      (Kernel._string == OWNER((*(l))[((CL_INT)len-(CL_INT)1)]))))
                 { OID  p = value_module(OBJECT(module,Reader.LAST_MODULE->value),string_v((*(l))[((CL_INT)len-(CL_INT)1)]));
                  if (p != CNULL)
                   { if (INHERIT(OWNER(p),Kernel._property))
                     { list * lm = OBJECT(property,p)->restrictions;
                      if (lm->length != 0)
                       { princ_string(((char*)"\n"));
                        { CL_INT loop_handle = ClEnv->cHandle;
                          OID gc_local;
                          ITERATE(g0831);
                          for (START(lm); NEXT(g0831);)
                          { GC_LOOP;
                            { char * i = GC_STRING(method_description_method(OBJECT(method,g0831)));
                              princ_string(((char*)"  "));
                              color_princ_string1(i);
                              princ_string(((char*)"\n"));
                              }
                            GC_UNLOOP; POP_SIGNAL;}
                          }
                        ding_void();
                        }
                      }
                    }
                  else interpreter_insert_text(((char*)"\t"));
                    }
                else interpreter_insert_text(((char*)"\t"));
                  }
              }
          }
      _void_(ClEnv->ctrace = oldtrace);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// *********************************************************************
// * 2. shell completion                                               *
// *********************************************************************
// The c++ function for: bin_init(_CL_obj:void) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT void  bin_init_void() { 
    
    GC_BIND;
    if (Reader.BINS_INIT_ask->value != Kernel.ctrue)
     { (Reader.BINS_INIT_ask->value= Kernel.ctrue);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(p);
        bag *p_support;
        p_support = GC_OBJECT(list,explode_string(GC_STRING(getenv_string(((char*)"PATH"))),GC_STRING(string_v(Core._starps_star->value))));
        for (START(p_support); NEXT(p);)
        { GC_LOOP;
          if (isdir_ask_string(string_v(p)) == CTRUE)
           { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(f);
            bag *f_support;
            f_support = GC_OBJECT(list,entries_string2(string_v(p)));
            for (START(f_support); NEXT(f);)
            { GC_LOOP;
              if (isdir_ask_string(_7_string(string_v(p),string_v(f))) != CTRUE)
               (Reader.BINS->value= _oid_(GC_OBJECT(list,OBJECT(list,Reader.BINS->value))->addFast((OID)f)));
              GC_UNLOOP; POP_SIGNAL;}
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: fill_binaries(buf:string) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT void  fill_binaries_string(char *buf) { 
    
    GC_BIND;
    { CL_INT  p = rfind_string2(buf,string_v(Core._starfs_star->value));
      CL_INT  p0 = ((CL_INT)rfind_string2(buf,((char*)" "))+(CL_INT)1);
      (Reader.COMPLETE_START_POSITION->value= ((OID)-1));
      if (((CL_INT)p0 > (CL_INT)1) && 
          ((CL_INT)p0 > (CL_INT)p))
       (Reader.COMPLETE_START_POSITION->value= ((OID)p0));
      else if ((p == 0) && 
          (p0 == 1))
       (Reader.COMPLETE_START_POSITION->value= ((OID)1));
      if ((CL_INT)((CL_INT)Reader.COMPLETE_START_POSITION->value) > (CL_INT)0)
       buf= (GC_STRING(substring_string(buf,((CL_INT)Reader.COMPLETE_START_POSITION->value),LENGTH_STRING(buf))));
      bin_init_void();
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(f);
        bag *f_support;
        f_support = GC_OBJECT(list,OBJECT(bag,Reader.BINS->value));
        for (START(f_support); NEXT(f);)
        { GC_LOOP;
          if (find_string2(string_v(f),buf) == 1)
           (Reader.MATCHES->value= _oid_(GC_OBJECT(list,OBJECT(list,Reader.MATCHES->value))->addFast((OID)GC_OID(_string_(append_string(GC_STRING(replace_string(string_v(f),((char*)" "),((char*)"\\ "))),((char*)" ")))))));
          GC_UNLOOP; POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: fill_files(buf:string) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT void  fill_files_string(char *buf) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { CL_INT  p = rfind_string2(buf,string_v(Core._starfs_star->value));
      CL_INT  p0 = ((CL_INT)rfind_string2(buf,((char*)" "))+(CL_INT)1);
      char * tmp = GC_STRING(((((CL_INT)p0 > (CL_INT)1) && 
          ((CL_INT)p < (CL_INT)p0)) ?
        substring_string(buf,p0,LENGTH_STRING(buf)) :
        ((((CL_INT)p0 > (CL_INT)1) && 
            ((CL_INT)p0 <= (CL_INT)p)) ?
          substring_string(buf,p0,p) :
          ((char*)"") ) ));
      char * df = GC_STRING(((((CL_INT)p > (CL_INT)0) && 
          (((CL_INT)p0 <= (CL_INT)p) && 
            ((CL_INT)((CL_INT)p+(CL_INT)1) <= (CL_INT)LENGTH_STRING(buf)))) ?
        substring_string(buf,((CL_INT)p+(CL_INT)1),LENGTH_STRING(buf)) :
        ((char*)"") ));
      if ((CL_INT)p > (CL_INT)0)
       { shrink_list(OBJECT(bag,Reader.MATCHES->value),0);
        (Reader.COMPLETE_START_POSITION->value= ((OID)min_integer1(((CL_INT)p+(CL_INT)1),((CL_INT)1+(CL_INT)LENGTH_STRING(buf)))));
        { ClaireHandler c_handle = ClaireHandler();
          if ERROR_IN 
          { { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(f);
              bag *f_support;
              f_support = GC_OBJECT(list,entries_string2(tmp));
              for (START(f_support); NEXT(f);)
              { GC_LOOP;
                if ((LENGTH_STRING(df) == 0) || 
                    (find_string2(string_v(f),df) == 1))
                 { char * match = string_v(f);
                  if (isdir_ask_string(_7_string(tmp,string_v(f))) == CTRUE)
                   GC__STRING(match = append_string(match,((char*)"/")), 1);
                  (Reader.MATCHES->value= _oid_(GC_OBJECT(list,OBJECT(list,Reader.MATCHES->value))->addFast((OID)_string_(match))));
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            ERROR_FREE;}
          else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
          { c_handle.catchIt();;}
          else PREVIOUS_HANDLER;}
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: shell_complete(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  shell_complete_void() { 
    
    GC_BIND;
    { PortObject * oldtrace = GC_OBJECT(PortObject,ClEnv->ctrace);
      _void_(ClEnv->ctrace = null_I_void1());
      { CL_INT  pos = interpreter_get_cursor_position();
        char * line = GC_STRING(interpreter_get_text());
        if ((OBJECT(bag,Reader.MATCHES->value)->length != 0) && 
            ((((OID)pos) == Reader.LAST_POSITION->value) && 
              ((equal(_string_(line),Reader.LAST_LINE->value) == CTRUE) && 
                (Reader.COMPLETE_START_POSITION->value != ((OID)-1)))))
         { interpreter_delete_text(((CL_INT)Reader.COMPLETE_START_POSITION->value),pos);
          (Reader.MATCH_INDEX->value= ((OID)((CL_INT)(((CL_INT)Reader.MATCH_INDEX->value))+(CL_INT)1)));
          if (Reader.MATCH_INDEX->value == ((OID)OBJECT(bag,Reader.MATCHES->value)->length))
           ding_void();
          if ((CL_INT)((CL_INT)Reader.MATCH_INDEX->value) > (CL_INT)OBJECT(bag,Reader.MATCHES->value)->length)
           (Reader.MATCH_INDEX->value= ((OID)1));
          interpreter_insert_text(string_v((*(OBJECT(bag,Reader.MATCHES->value)))[((CL_INT)Reader.MATCH_INDEX->value)]));
          (Reader.LAST_POSITION->value= ((OID)interpreter_get_cursor_position()));
          (Reader.LAST_LINE->value= _string_(interpreter_get_text()));
          }
        else { shrink_list(OBJECT(bag,Reader.MATCHES->value),0);
            { char * tmp = GC_STRING(substring_string(line,1,((CL_INT)pos-(CL_INT)1)));
              fill_binaries_string(tmp);
              if ((Reader.COMPLETE_START_POSITION->value == ((OID)-1)) || 
                  (OBJECT(bag,Reader.MATCHES->value)->length == 0))
               fill_files_string(tmp);
              }
            nodup_list(((list *) copy_bag(OBJECT(bag,Reader.MATCHES->value))));
            if (OBJECT(bag,Reader.MATCHES->value)->length != 0)
             { (Reader.MATCH_INDEX->value= ((OID)0));
              (Reader.LAST_POSITION->value= ((OID)pos));
              (Reader.LAST_LINE->value= _string_(interpreter_get_text()));
              if (OBJECT(bag,Reader.MATCHES->value)->length == 1)
               { shell_complete_void();
                (Reader.COMPLETE_START_POSITION->value= ((OID)-1));
                }
              else { char * mp = GC_STRING(match_prefix_void());
                  if ((CL_INT)LENGTH_STRING(mp) > (CL_INT)((CL_INT)pos-(CL_INT)(((CL_INT)Reader.COMPLETE_START_POSITION->value))))
                   { shrink_list(OBJECT(bag,Reader.MATCHES->value),0);
                    (Reader.MATCHES->value= _oid_(GC_OBJECT(list,OBJECT(list,Reader.MATCHES->value))->addFast((OID)_string_(mp))));
                    shell_complete_void();
                    (Reader.COMPLETE_START_POSITION->value= ((OID)-1));
                    }
                  else { ding_void();
                      interpreter_display_list(OBJECT(list,Reader.MATCHES->value));
                      (Reader.MATCHES->value= _oid_(GC_OBJECT(list,OBJECT(list,Reader.MATCHES->value))->addFast((OID)GC_OID(_string_(substring_string(line,((CL_INT)Reader.COMPLETE_START_POSITION->value),((CL_INT)pos-(CL_INT)1)))))));
                      }
                    }
                }
            }
          }
      _void_(ClEnv->ctrace = oldtrace);
      }
    GC_UNBIND; POP_SIGNAL;}
  



/***** CLAIRE Compilation of file ./meta/toplevel.cl 
         [version 3.5.0 / safety 5] *****/


// *********************************************************************
// * CLAIRE                                            Sylvain Benilan *
// * toplevel.cl                                                       *
// * Copyright (C) 2005 xl. All Rights Reserved                        *
// *********************************************************************
//<sb> this file contains the console interface code including
// command loops for the interpreter, the inspector and the debugger
// and the management of execution contexts.
// Most of the code used to be in clConcole.cpp (<ycs>) and as been
// upgraded in claire in the xl version.
// ******************************************************************
// *    Part 3: standart console input                              *
// ******************************************************************
//<sb> stdin_line_reader is a basic terminal interface for the
// Reader, it should work on various subsystems.
// The clConsole.cpp file may define a custom line reader port
// based on editline BSD library that add history and completion
// features.
// The c++ function for: close_port(self:stdin_line_reader) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  close_port_stdin_line_reader1_Reader(Reader_stdin_line_reader *self) { 
    
    GC_BIND;
    fclose_port1(GC_OBJECT(blob,self->line));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: eof_port?(self:stdin_line_reader) [0]
CL_EXPORT ClaireBoolean * eof_port_ask_stdin_line_reader1_Reader(Reader_stdin_line_reader *self) { 
    POP_SIGNAL; return (CFALSE);}
  


//<sb> note: do not use set_length@blob to reset the line
// since it could be invoked while the line has been freed
// (e.g. at exit)
// The c++ function for: flush_port(self:stdin_line_reader) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  flush_port_stdin_line_reader1_Reader(Reader_stdin_line_reader *self) { 
    _void_(self->line->read_index = 0);
    _void_(self->line->write_index = 0);
    POP_SIGNAL;}
  


// The c++ function for: unget_port(self:stdin_line_reader,buf:char*,len:integer) [NEW_ALLOC]
CL_EXPORT void  unget_port_stdin_line_reader1_Reader(Reader_stdin_line_reader *self,char*buf,int len) { 
    
    GC_BIND;
    _void_(Core.unget_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->line)))),((CL_INT) buf),((CL_INT) len)));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: read_port(self:stdin_line_reader,buf:char*,len:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT CL_INT  read_port_stdin_line_reader1_Reader(Reader_stdin_line_reader *self,char*buf,int len) { 
    
    GC_BIND;
    if ((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->line)))))))) == CTRUE)
     { set_length_blob1(self->line,0);
      fwrite_string2(GC_STRING(freadline_port(OBJECT(PortObject,Core.Clib_stdin->value))),GC_OBJECT(blob,self->line));
      fwrite_string2(((char*)"\n\n"),GC_OBJECT(blob,self->line));
      }
    nth_equal_char_star1(buf,1,getc_port1(GC_OBJECT(blob,self->line)));
    { CL_INT Result = 0;
      Result = ((len == 1) ?
        1 :
        ((CL_INT)1+(CL_INT)(((CL_INT)Core.read_port->fcall(((CL_INT) self),((CL_INT) (buf + 1)),((CL_INT) ((CL_INT)len-(CL_INT)1)))))) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// ******************************************************************
// *    Part 3: execution context                                   *
// ******************************************************************
//<sb> an execution_context object is an image of the system state
// at the time at which save_context has been called that can be
// restored by a call to restore_context. 
// note: the system backup is allocated in claire memory, this is
// important regarding the GC: it ensures for instance that the
// the backup of cout is marked by the GC...
// The c++ function for: save_context(debug?:boolean) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT Reader_execution_context * save_context_boolean1(ClaireBoolean *debug_ask) { 
    
    GC_BIND;
    { Reader_execution_context *Result ;
      { Reader_execution_context * exe;
        { { Reader_execution_context * _CL_obj = ((Reader_execution_context *) GC_OBJECT(Reader_execution_context,new_object_class(Reader._execution_context)));
            _void_(_CL_obj->debug_context_ask = debug_ask);
            exe = _CL_obj;
            }
          GC_OBJECT(Reader_execution_context,exe);}
        _void_(exe->saved_system = ((ClaireEnvironment *) (ClaireEnvironment *)(ClAlloc->makeAny(debug_ask == CTRUE ? 38 : 27))));
        memcpy(exe->saved_system, ClEnv, debug_ask == CTRUE ? 4*38 : 4*27);
        _void_(exe->saved_reader = ((meta_reader *) copy_object(Reader.reader)));
        if (debug_ask == CTRUE)
         _void_(exe->module_stack = ((list *) copy_bag(((bag *) (list *)(ClEnv->moduleStack)))));
        (ClEnv->base= GC_OID(((OID)ClEnv->index)));
        Result = exe;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: restore_context(self:execution_context) [0]
CL_EXPORT void  restore_context_execution_context1(Reader_execution_context *self) { 
    memcpy(ClEnv, self->saved_system, self->debug_context_ask == CTRUE ? 4*38 : 4*27);
    if (self->debug_context_ask == CTRUE)
     ClEnv->moduleStack = self->module_stack;
    { meta_reader * r = Reader.reader;
      memcpy(r, self->saved_reader, sizeof(meta_reader));
      }
    POP_SIGNAL;}
  


// ******************************************************************
// *    Part 3: tool                                                *
// ******************************************************************
// The c++ function for: get_prompt(_CL_obj:void) [0]
CL_EXPORT char * get_prompt_void2() { 
    POP_SIGNAL; return (string_v(Reader.PROMPT->value));}
  


//<sb> a special exception is used to abort a debug session
// The c++ function for: self_print(self:abort_debug) [0]
CL_EXPORT void  self_print_abort_debug1_Reader(Reader_abort_debug *self) { 
    princ_string(((char*)"== debug session aborted == "));
    POP_SIGNAL;}
  


//<sb> memory failure are not recoverable during debug :
// it would force the system to run in an unsafe environment
// (even the print of an exception could have an undefined issue).
// instead the exception is raised again by debug handlers such it
// can be cached by an outer handler (e.g. toplevel) from which
// stacks (execution & GC) are (hopefully enough) shorter.
// for that service we use a special pre-allocated exception which
// prevent an allocation to occur at the time of the congestion.
// The c++ function for: self_print(self:debug_fatal_error) [NEW_ALLOC]
CL_EXPORT void  self_print_debug_fatal_error1_Reader(Reader_debug_fatal_error *self) { 
    
    GC_BIND;
    princ_string(((char*)"== fatal error during debug session ==\n"));
    print_any(GC_OID(_oid_(self->src)));
    GC_UNBIND; POP_SIGNAL;}
  


// ******************************************************************
// *    Part 3: inspector loop                                      *
// ******************************************************************
// The c++ function for: inspect_system(self:list[any]) [RETURN_ARG]
CL_EXPORT void  inspect_system_list2(list *self) { 
    (Reader.INSPECT_STACK->value= _oid_(self));
    POP_SIGNAL;}
  


// The c++ function for: inspect_toplevel(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  inspect_toplevel_any1(OID self) { 
    
    GC_BIND;
    signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_IGN);
    (Reader.INSPECT_STACK->value= _oid_(list::empty(Kernel._any)));
    { Reader_execution_context * old_ctx = GC_OBJECT(Reader_execution_context,save_context_boolean1(CFALSE));
      inspect_any(self);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((CTRUE == CTRUE))
        { GC_LOOP;
          (Reader.IN_INSPECT_LOOP_ask->value= Kernel.ctrue);
          { ClaireHandler c_handle = ClaireHandler();
            if ERROR_IN 
            { { OID  x = GC_OID(read_command_string1(((char*)"inspect> ")));
                (Reader.IN_INSPECT_LOOP_ask->value= Kernel.cfalse);
                if (x == _oid_(Reader.q))
                 { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                inspect_loop_any(x,GC_OBJECT(list,OBJECT(list,Reader.INSPECT_STACK->value)));
                }
              ERROR_FREE;}
            else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
            { c_handle.catchIt();{ signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_IGN);
                print_exception_void();
                }
              }
            else PREVIOUS_HANDLER;}
          GC_UNLOOP;POP_SIGNAL;}
        }
      (Reader.IN_INSPECT_LOOP_ask->value= Kernel.cfalse);
      restore_context_execution_context1(old_ctx);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// ******************************************************************
// *    Part 3: toplevel loop                                       *
// ******************************************************************
//<sb> read a fragment on stdin
// ^C may be used to abort the command
// The c++ function for: read_command(prompt:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  read_command_string1(char *prompt) { 
    
    GC_BIND;
    (Reader.PROMPT->value= _string_(prompt));
    (Reader.IDENTS->value= _oid_(list::empty(Kernel._any)));
    use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value));
    flush_port1(GC_OBJECT(PortObject,OBJECT(PortObject,Core.cl_stdout->value)));
    _void_(Reader.reader->fromp = OBJECT(PortObject,Core.cl_stdin->value));
    if (unix_ask_void1() != CTRUE)
     _void_(OBJECT(descriptor,Core.Clib_stdin->value)->eof_reached_ask = CFALSE);
    if (INHERIT(get_device_port1(OBJECT(PortObject,Core.cl_stdin->value))->isa,Reader._stdin_line_reader))
     { princ_string(prompt);
      flush_port1(GC_OBJECT(PortObject,OBJECT(PortObject,Core.cl_stdout->value)));
      }
    reset_buffer_port1(Reader.reader->fromp);
    _void_(Reader.reader->toplevel = CTRUE);
    flush_port1(GC_OBJECT(device,get_device_port1(Reader.reader->fromp)));
    _void_(Reader.reader->index = 0);
    _void_(Reader.reader->maxstack = 0);
    _void_(Reader.reader->fromp->firstc = integer_I_char(_char_(((unsigned char)' '))));
    signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_DFL);
    { OID Result = 0;
      { CL_INT  c = color_void();
        if (c != 0)
         c= (CL_INT)(color_integer(1));
        color(30,0);
        flush_port1(GC_OBJECT(PortObject,OBJECT(PortObject,Core.cl_stdout->value)));
        { OID  x = GC_OID(nextunit_meta_reader(Reader.reader));
          signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_IGN);
          color_integer(c);
          Result = x;
          }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> evaluate and print the result of something that
// has been read. ^C may be used to abort the evaluation
// in debug mode ^C breaks the program
// The c++ function for: eval_command(x:any,nb_eval:integer,check_break?:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  eval_command_any2(OID x,int nb_eval,ClaireBoolean *check_break_ask) { 
    
    GC_BIND;
    { CL_INT  g0832 = (CL_INT )(current_color);
      CL_INT  g0833 = (CL_INT )(current_bold);
      CL_INT  g0834 = g0832;
      CL_INT  g0835 = g0833;
      color(g0832,g0833);
      color_princ_string1(((char*)"`BLUEeval["));
      g0832= (CL_INT)((CL_INT )(current_color));
      g0833= (CL_INT)((CL_INT )(current_bold));
      color(g0834,g0835);
      print_any(((OID)nb_eval));
      color(g0832,g0833);
      color(g0832,g0833);
      color_princ_string1(((char*)"]> `BLACK"));
      color(g0834,g0835);
      }
    flush_port1(GC_OBJECT(PortObject,ClEnv->cout));
    if ((OBJECT(ClaireBoolean,Language.DEBUG_ask->value)) == CTRUE)
     signal_signal_handler(Core.CL_SIGINT,Core.on_break_program);
    else signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_DFL);
      index_jump_integer1(((CL_INT)ClEnv->index+(CL_INT)((CL_INT)Reader.reader->maxstack+(CL_INT)1)));
    print_any(GC_OID(OPT_EVAL(x)));
    signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_IGN);
    princ_string(((char*)"\n"));
    flush_port1(GC_OBJECT(PortObject,ClEnv->cout));
    GC_UNBIND; POP_SIGNAL;}
  


//<sb> here is a special version that raise
// an exception that is caught by the
// toplevel handler, it is used in the special
// case of an unrecoverable error (abort debug
// or memory exception)
// The c++ function for: close_toplevel_exception(self:exception) [0]
CL_EXPORT void  close_toplevel_exception_exception1(ClaireException *self) { 
    { CL_INT  n = ((CL_INT)Reader.TOP_CHANDLE->value);
      ClEnv->exception_I = self;
			  avoid_signal_caching = 0;
			  longjmp(ClEnv->handlers[n],3);;
      }
    POP_SIGNAL;}
  


// The c++ function for: self_print(self:command_line_error) [NEW_ALLOC]
CL_EXPORT void  self_print_command_line_error1_Reader(Reader_command_line_error *self) { 
    
    GC_BIND;
    princ_string(((char*)"An error has occurred during the handling of the command line:\n"));
    print_any(GC_OID(self->src));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: Core/toplevel(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  toplevel_void2_Reader() { 
    
    GC_BIND;
    signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_IGN);
    if (Core.cl_stdin->value == Core.Clib_stdin->value)
     { OID  truc;{ buffer * V_CL0856;{ Reader_stdin_line_reader * g0857UU;
          { Reader_stdin_line_reader * _CL_obj = ((Reader_stdin_line_reader *) GC_OBJECT(Reader_stdin_line_reader,new_object_class(Reader._stdin_line_reader)));
            _void_(_CL_obj->line = blob_I_void1());
            g0857UU = _CL_obj;
            }
          V_CL0856 = buffer_I_port1(g0857UU,1);
          }
        
        truc=_oid_(V_CL0856);}
      
      (Core.cl_stdin->value = truc);}
    (Reader.NB_EVAL->value= ((OID)0));
    (Reader.TOP_CHANDLE->value= ((OID)(CL_INT )((ClEnv->cHandle+1))));
    if ((OBJECT(ClaireBoolean,Language.DEBUG_ask->value)) == CTRUE)
     { color_integer(1);
      { CL_INT  g0836 = (CL_INT )(current_color);
        CL_INT  g0837 = (CL_INT )(current_bold);
        CL_INT  g0838 = g0836;
        CL_INT  g0839 = g0837;
        color(g0836,g0837);
        color_princ_string1(((char*)"``RED ========== Debugger installed ==========\n"));
        color(g0838,g0839);
        }
      }
    if (((OBJECT(ClaireBoolean,Language.DEBUG_ask->value)) == CTRUE) && 
        (Core.top_frame->value != Core.current_frame->value))
     { { Reader_command_line_error * clex = GC_OBJECT(Reader_command_line_error,((Reader_command_line_error *) new_object_class(Reader._command_line_error)));
        _void_(clex->src = get_property(Kernel.exception_I,ClEnv));
        _void_(ClEnv->exception_I = clex);
        }
      { ClaireHandler c_handle = ClaireHandler();
        if ERROR_IN 
        { debug_loop_void1();
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
        { c_handle.catchIt();{ CL_INT  g0840 = (CL_INT )(current_color);
            CL_INT  g0841 = (CL_INT )(current_bold);
            CL_INT  g0842 = g0840;
            CL_INT  g0843 = g0841;
            color(g0840,g0841);
            color_princ_string1(((char*)"`REDThere is a bug in the debug loop :\n"));
            g0840= (CL_INT)((CL_INT )(current_color));
            g0841= (CL_INT)((CL_INT )(current_bold));
            color(g0842,g0843);
            print_exception_void();
            color(g0840,g0841);
            color(g0842,g0843);
            }
          }
        else PREVIOUS_HANDLER;}
      _void_(ClEnv->exception_I = ((ClaireException *) new_object_class(Reader._abort_debug)));
      print_any(GC_OID(_oid_(ClEnv->exception_I)));
      princ_string(((char*)"\n"));
      }
    { Reader_execution_context * exe_ctx = GC_OBJECT(Reader_execution_context,save_context_boolean1(CFALSE));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((CTRUE == CTRUE))
        { GC_LOOP;
          restore_context_execution_context1(exe_ctx);
          if ((OBJECT(ClaireBoolean,Language.DEBUG_ask->value)) == CTRUE)
           reset_frame_stack_void1();
          { ClaireHandler c_handle = ClaireHandler();
            if ERROR_IN 
            { { ClaireBoolean * eval_ask = CTRUE;
                OID  x;
                { { char * g0858UU;
                    { { print_in_string_void();
                        princ_string(((char*)"["));
                        print_any(((OID)getpid_void()));
                        princ_string(((char*)"]"));
                        print_any(_oid_(ClEnv->module_I));
                        princ_string(((char*)"> "));
                        g0858UU = end_of_string_void();
                        }
                      GC_STRING(g0858UU);}
                    x = read_command_string1(g0858UU);
                    }
                  GC_OID(x);}
                if (x == _oid_(Reader.q))
                 { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                else if (INHERIT(OWNER(x),Kernel._unbound_symbol))
                 { if ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"step")) == CTRUE) || 
                      ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"ste")) == CTRUE) || 
                        ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"st")) == CTRUE) || 
                          (equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"s")) == CTRUE))))
                   { if (Core.STEP->value == ((OID)-1))
                     { (Core.STEP->value= ((OID)0));
                      { CL_INT  g0844 = (CL_INT )(current_color);
                        CL_INT  g0845 = (CL_INT )(current_bold);
                        CL_INT  g0846 = g0844;
                        CL_INT  g0847 = g0845;
                        color(g0844,g0845);
                        color_princ_string1(((char*)"``RED========== Stepper removed ==========\n"));
                        color(g0846,g0847);
                        }
                      }
                    else { (Core.STEP->value= ((OID)-1));
                        { CL_INT  g0848 = (CL_INT )(current_color);
                          CL_INT  g0849 = (CL_INT )(current_bold);
                          CL_INT  g0850 = g0848;
                          CL_INT  g0851 = g0849;
                          color(g0848,g0849);
                          color_princ_string1(((char*)"``RED========== Stepper installed ==========\n"));
                          color(g0850,g0851);
                          }
                        }
                      eval_ask= (CFALSE);
                    }
                  }
                if (eval_ask == CTRUE)
                 { (Reader.NB_EVAL->value= ((OID)((CL_INT)(((CL_INT)Reader.NB_EVAL->value))+(CL_INT)1)));
                  eval_command_any2(x,((CL_INT)Reader.NB_EVAL->value),CTRUE);
                  }
                _void_(exe_ctx->saved_system->verbose = ClEnv->verbose);
                _void_(exe_ctx->saved_system->module_I = ClEnv->module_I);
                }
              ERROR_FREE;}
            else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
            { c_handle.catchIt();{ signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_IGN);
                if ((owner_any(_oid_(ClEnv->exception_I)) == Kernel._system_error) && 
                    ((CL_INT)CLREAD(system_error,ClEnv->exception_I,index) <= (CL_INT)3))
                 print_exception_void();
                else if (INHERIT(ClEnv->exception_I->isa,Reader._abort_debug))
                 { print_any(GC_OID(_oid_(ClEnv->exception_I)));
                  princ_string(((char*)"\n"));
                  }
                else if (((OBJECT(ClaireBoolean,Language.DEBUG_ask->value)) == CTRUE) && 
                    (Core.top_frame->value != Core.current_frame->value))
                 { { ClaireHandler c_handle = ClaireHandler();
                    if ERROR_IN 
                    { debug_loop_void1();
                      ERROR_FREE;}
                    else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                    { c_handle.catchIt();{ CL_INT  g0852 = (CL_INT )(current_color);
                        CL_INT  g0853 = (CL_INT )(current_bold);
                        CL_INT  g0854 = g0852;
                        CL_INT  g0855 = g0853;
                        color(g0852,g0853);
                        color_princ_string1(((char*)"`REDThere is a bug in the debug loop :\n"));
                        g0852= (CL_INT)((CL_INT )(current_color));
                        g0853= (CL_INT)((CL_INT )(current_bold));
                        color(g0854,g0855);
                        print_exception_void();
                        color(g0852,g0853);
                        color(g0854,g0855);
                        }
                      }
                    else PREVIOUS_HANDLER;}
                  _void_(ClEnv->exception_I = ((ClaireException *) new_object_class(Reader._abort_debug)));
                  print_any(GC_OID(_oid_(ClEnv->exception_I)));
                  princ_string(((char*)"\n"));
                  }
                else { _void_(exe_ctx->saved_system->exception_I = ClEnv->exception_I);
                    print_exception_void();
                    }
                  }
              }
            else PREVIOUS_HANDLER;}
          GC_UNLOOP;POP_SIGNAL;}
        }
      restore_context_execution_context1(exe_ctx);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// ******************************************************************
// *    Part 3: debug command                                       *
// ******************************************************************
//<sb> debug_loop is called when a program issue an unhandled
// exception, it allows stack inspection (call stack, variables)
// The c++ function for: debug_loop(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  debug_loop_void1() { 
    
    GC_RESERVE(4);  // v3.3.39 optim !
    signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_IGN);
    (Core.STEP->value= ((OID)0));
    { PortObject * oldout = use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value));
      Reader_execution_context * old_ctx = GC_OBJECT(Reader_execution_context,save_context_boolean1(CTRUE));
      Core_dbg_frame * frame = GC_OBJECT(Core_dbg_frame,OBJECT(Core_dbg_frame,Core.current_frame->value));
      list * bindings = GC_OBJECT(list,bind_frame_dbg_frame1(frame));
      (Language.DEBUG_ask->value= Kernel.cfalse);
      { CL_INT  g0859 = (CL_INT )(current_color);
        CL_INT  g0860 = (CL_INT )(current_bold);
        CL_INT  g0861 = g0859;
        CL_INT  g0862 = g0860;
        color(g0859,g0860);
        color_princ_string1(((char*)"``RED========= Unhandled exception =========\n"));
        color(g0861,g0862);
        }
      print_exception_void();
      if (oldout != ClEnv->cout)
       { CL_INT  g0863 = (CL_INT )(current_color);
        CL_INT  g0864 = (CL_INT )(current_bold);
        CL_INT  g0865 = g0863;
        CL_INT  g0866 = g0864;
        color(g0863,g0864);
        color_princ_string1(((char*)"`REDNote: output was "));
        g0863= (CL_INT)((CL_INT )(current_color));
        g0864= (CL_INT)((CL_INT )(current_bold));
        color(g0865,g0866);
        print_any(_oid_(oldout));
        color(g0863,g0864);
        color(g0863,g0864);
        color_princ_string1(((char*)"\n"));
        color(g0865,g0866);
        }
      show_frame_info_dbg_frame1(frame);
      (Reader.NB_DEBUG_EVAL->value= ((OID)0));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((CTRUE == CTRUE))
        { GC_LOOP;
          { ClaireHandler c_handle = ClaireHandler();
            if ERROR_IN 
            { { OID  x;
                { { char * g0875UU;
                    { { print_in_string_void();
                        princ_string(((char*)"[debug]"));
                        print_any(((OID)frame->num));
                        princ_string(((char*)">> "));
                        g0875UU = end_of_string_void();
                        }
                      GC_STRING(g0875UU);}
                    x = read_command_string1(g0875UU);
                    }
                  GC_OID(x);}
                if (x == _oid_(Reader.q))
                 { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                else if (INHERIT(OWNER(x),Kernel._unbound_symbol))
                 { if ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"bt")) == CTRUE) || 
                      ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"where")) == CTRUE) || 
                        ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"wher")) == CTRUE) || 
                          ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"whe")) == CTRUE) || 
                            ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"wh")) == CTRUE) || 
                              (equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"w")) == CTRUE))))))
                   where_dbg_frame1(frame);
                  else if ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"frame")) == CTRUE) || 
                      ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"fram")) == CTRUE) || 
                        ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"fra")) == CTRUE) || 
                          ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"fr")) == CTRUE) || 
                            (equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"f")) == CTRUE)))))
                   show_frame_info_dbg_frame1(frame);
                  else if ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"up")) == CTRUE) || 
                      (equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"u")) == CTRUE))
                   { if (frame->num == 1)
                     { CL_INT  g0867 = (CL_INT )(current_color);
                      CL_INT  g0868 = (CL_INT )(current_bold);
                      CL_INT  g0869 = g0867;
                      CL_INT  g0870 = g0868;
                      color(g0867,g0868);
                      color_princ_string1(((char*)"`REDCannot go up the top frame\n"));
                      color(g0869,g0870);
                      }
                    else { unbind_frame_list1(bindings);
                        GC__ANY(frame = frame->prev, 1);
                        GC__ANY(bindings = bind_frame_dbg_frame1(frame), 2);
                        show_frame_info_dbg_frame1(frame);
                        }
                      }
                  else if ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"down")) == CTRUE) || 
                      ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"dow")) == CTRUE) || 
                        ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"do")) == CTRUE) || 
                          (equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"d")) == CTRUE))))
                   { if (frame->next == (NULL))
                     { CL_INT  g0871 = (CL_INT )(current_color);
                      CL_INT  g0872 = (CL_INT )(current_bold);
                      CL_INT  g0873 = g0871;
                      CL_INT  g0874 = g0872;
                      color(g0871,g0872);
                      color_princ_string1(((char*)"`REDCannot go down the innermost frame\n"));
                      color(g0873,g0874);
                      }
                    else { unbind_frame_list1(bindings);
                        GC__ANY(frame = frame->next, 3);
                        GC__ANY(bindings = bind_frame_dbg_frame1(frame), 4);
                        show_frame_info_dbg_frame1(frame);
                        }
                      }
                  else if ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"edit")) == CTRUE) || 
                      ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"edi")) == CTRUE) || 
                        ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"ed")) == CTRUE) || 
                          (equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"e")) == CTRUE))))
                   { print_in_string_void();
                    princ_string(((char*)"claire://source-edit?file="));
                    princ_string(url_encode_string(GC_STRING(frame->source)));
                    princ_string(((char*)"&line="));
                    princ_integer(frame->line);
                    princ_string(((char*)"&editor="));
                    open_link_string1(GC_STRING(end_of_string_void()));
                    }
                  else { (Reader.NB_DEBUG_EVAL->value= ((OID)((CL_INT)(((CL_INT)Reader.NB_DEBUG_EVAL->value))+(CL_INT)1)));
                      eval_command_any2(x,((CL_INT)Reader.NB_DEBUG_EVAL->value),CFALSE);
                      }
                    }
                else { (Reader.NB_DEBUG_EVAL->value= ((OID)((CL_INT)(((CL_INT)Reader.NB_DEBUG_EVAL->value))+(CL_INT)1)));
                    eval_command_any2(x,((CL_INT)Reader.NB_DEBUG_EVAL->value),CFALSE);
                    }
                  }
              ERROR_FREE;}
            else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
            { c_handle.catchIt();{ if ((owner_any(_oid_(ClEnv->exception_I)) == Kernel._system_error) && 
                    ((CL_INT)CLREAD(system_error,ClEnv->exception_I,index) <= (CL_INT)3))
                 { _void_(OBJECT(Reader_debug_fatal_error,Reader._stardebug_fatal_error_star->value)->src = ClEnv->exception_I);
                  close_toplevel_exception_exception1(OBJECT(ClaireException,Reader._stardebug_fatal_error_star->value));
                  }
                signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_IGN);
                print_exception_void();
                }
              }
            else PREVIOUS_HANDLER;}
          GC_UNLOOP;POP_SIGNAL;}
        }
      unbind_frame_list1(bindings);
      (Language.DEBUG_ask->value= Kernel.ctrue);
      restore_context_execution_context1(old_ctx);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: Core/on_break_program(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  on_break_program_void1_Reader() { 
    
    GC_RESERVE(4);  // v3.3.39 optim !
    signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_IGN);
    (Core.STEP->value= ((OID)0));
    { PortObject * oldout = use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value));
      Reader_execution_context * old_ctx = GC_OBJECT(Reader_execution_context,save_context_boolean1(CTRUE));
      Core_dbg_frame * frame = GC_OBJECT(Core_dbg_frame,OBJECT(Core_dbg_frame,Core.current_frame->value));
      list * bindings = GC_OBJECT(list,bind_frame_dbg_frame1(frame));
      (Language.DEBUG_ask->value= Kernel.cfalse);
      { CL_INT  g0876 = (CL_INT )(current_color);
        CL_INT  g0877 = (CL_INT )(current_bold);
        CL_INT  g0878 = g0876;
        CL_INT  g0879 = g0877;
        color(g0876,g0877);
        color_princ_string1(((char*)"``RED=============== Stepper ===============\n"));
        color(g0878,g0879);
        }
      if (oldout != ClEnv->cout)
       { CL_INT  g0880 = (CL_INT )(current_color);
        CL_INT  g0881 = (CL_INT )(current_bold);
        CL_INT  g0882 = g0880;
        CL_INT  g0883 = g0881;
        color(g0880,g0881);
        color_princ_string1(((char*)"`REDNote: output was "));
        g0880= (CL_INT)((CL_INT )(current_color));
        g0881= (CL_INT)((CL_INT )(current_bold));
        color(g0882,g0883);
        print_any(_oid_(oldout));
        color(g0880,g0881);
        color(g0880,g0881);
        color_princ_string1(((char*)"\n"));
        color(g0882,g0883);
        }
      show_frame_info_dbg_frame1(frame);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((CTRUE == CTRUE))
        { GC_LOOP;
          { ClaireHandler c_handle = ClaireHandler();
            if ERROR_IN 
            { { OID  x;
                { { char * g0892UU;
                    { { print_in_string_void();
                        princ_string(((char*)"[step]"));
                        print_any(((OID)frame->num));
                        princ_string(((char*)">> "));
                        g0892UU = end_of_string_void();
                        }
                      GC_STRING(g0892UU);}
                    x = read_command_string1(g0892UU);
                    }
                  GC_OID(x);}
                if (x == _oid_(Reader.q))
                 close_exception((ClaireException *) new_object_class(Reader._abort_debug));
                else if (INHERIT(OWNER(x),Kernel._unbound_symbol))
                 { if ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"bt")) == CTRUE) || 
                      ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"where")) == CTRUE) || 
                        ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"wher")) == CTRUE) || 
                          ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"whe")) == CTRUE) || 
                            ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"wh")) == CTRUE) || 
                              (equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"w")) == CTRUE))))))
                   where_dbg_frame1(frame);
                  else if ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"frame")) == CTRUE) || 
                      ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"fram")) == CTRUE) || 
                        ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"fra")) == CTRUE) || 
                          ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"fr")) == CTRUE) || 
                            (equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"f")) == CTRUE)))))
                   show_frame_info_dbg_frame1(frame);
                  else if ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"up")) == CTRUE) || 
                      (equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"u")) == CTRUE))
                   { if (frame->num == 1)
                     { CL_INT  g0884 = (CL_INT )(current_color);
                      CL_INT  g0885 = (CL_INT )(current_bold);
                      CL_INT  g0886 = g0884;
                      CL_INT  g0887 = g0885;
                      color(g0884,g0885);
                      color_princ_string1(((char*)"`REDCannot go up the top frame\n"));
                      color(g0886,g0887);
                      }
                    else { unbind_frame_list1(bindings);
                        GC__ANY(frame = frame->prev, 1);
                        GC__ANY(bindings = bind_frame_dbg_frame1(frame), 2);
                        show_frame_info_dbg_frame1(frame);
                        }
                      }
                  else if ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"down")) == CTRUE) || 
                      ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"dow")) == CTRUE) || 
                        ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"do")) == CTRUE) || 
                          (equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"d")) == CTRUE))))
                   { if (frame->next == (NULL))
                     { CL_INT  g0888 = (CL_INT )(current_color);
                      CL_INT  g0889 = (CL_INT )(current_bold);
                      CL_INT  g0890 = g0888;
                      CL_INT  g0891 = g0889;
                      color(g0888,g0889);
                      color_princ_string1(((char*)"`REDCannot go down the innermost frame\n"));
                      color(g0890,g0891);
                      }
                    else { unbind_frame_list1(bindings);
                        GC__ANY(frame = frame->next, 3);
                        GC__ANY(bindings = bind_frame_dbg_frame1(frame), 4);
                        show_frame_info_dbg_frame1(frame);
                        }
                      }
                  else if ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"edit")) == CTRUE) || 
                      ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"edi")) == CTRUE) || 
                        ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"ed")) == CTRUE) || 
                          (equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"e")) == CTRUE))))
                   { print_in_string_void();
                    princ_string(((char*)"claire://source-edit?file="));
                    princ_string(url_encode_string(GC_STRING(frame->source)));
                    princ_string(((char*)"&line="));
                    princ_integer(frame->line);
                    princ_string(((char*)"&editor="));
                    open_link_string1(GC_STRING(end_of_string_void()));
                    }
                  else if ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"step")) == CTRUE) || 
                      ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"ste")) == CTRUE) || 
                        ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"st")) == CTRUE) || 
                          (equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"s")) == CTRUE))))
                   { (Core.STEP->value= ((OID)-1));
                    { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                    }
                  else if ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"next")) == CTRUE) || 
                      ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"nex")) == CTRUE) || 
                        ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"ne")) == CTRUE) || 
                          (equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"n")) == CTRUE))))
                   { (Core.STEP->value= ((OID)OBJECT(Core_dbg_frame,Core.current_frame->value)->num));
                    { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                    }
                  else if ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"out")) == CTRUE) || 
                      ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"ou")) == CTRUE) || 
                        (equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"o")) == CTRUE)))
                   { (Core.STEP->value= ((OID)((CL_INT)OBJECT(Core_dbg_frame,Core.current_frame->value)->num-(CL_INT)1)));
                    { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                    }
                  else if ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"continue")) == CTRUE) || 
                      ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"continu")) == CTRUE) || 
                        ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"contin")) == CTRUE) || 
                          ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"conti")) == CTRUE) || 
                            ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"cont")) == CTRUE) || 
                              ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"con")) == CTRUE) || 
                                ((equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"co")) == CTRUE) || 
                                  (equal_string(OBJECT(unbound_symbol,x)->name->name,((char*)"c")) == CTRUE))))))))
                   { (Core.STEP->value= ((OID)0));
                    { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                    }
                  else { (Reader.NB_DEBUG_EVAL->value= ((OID)((CL_INT)(((CL_INT)Reader.NB_DEBUG_EVAL->value))+(CL_INT)1)));
                      eval_command_any2(x,((CL_INT)Reader.NB_DEBUG_EVAL->value),CFALSE);
                      }
                    }
                else { (Reader.NB_DEBUG_EVAL->value= ((OID)((CL_INT)(((CL_INT)Reader.NB_DEBUG_EVAL->value))+(CL_INT)1)));
                    eval_command_any2(x,((CL_INT)Reader.NB_DEBUG_EVAL->value),CFALSE);
                    }
                  }
              ERROR_FREE;}
            else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
            { c_handle.catchIt();{ (Language.DEBUG_ask->value= Kernel.ctrue);
                if (INHERIT(ClEnv->exception_I->isa,Reader._abort_debug))
                 { unbind_frame_list1(bindings);
                  close_exception(ClEnv->exception_I);
                  }
                if ((owner_any(_oid_(ClEnv->exception_I)) == Kernel._system_error) && 
                    ((CL_INT)CLREAD(system_error,ClEnv->exception_I,index) <= (CL_INT)3))
                 { _void_(OBJECT(Reader_debug_fatal_error,Reader._stardebug_fatal_error_star->value)->src = ClEnv->exception_I);
                  close_toplevel_exception_exception1(OBJECT(ClaireException,Reader._stardebug_fatal_error_star->value));
                  }
                signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_IGN);
                print_exception_void();
                }
              }
            else PREVIOUS_HANDLER;}
          GC_UNLOOP;POP_SIGNAL;}
        }
      unbind_frame_list1(bindings);
      (Language.DEBUG_ask->value= Kernel.ctrue);
      restore_context_execution_context1(old_ctx);
      signal_signal_handler(Core.CL_SIGINT,Core.on_break_program);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// ******************************************************************
// *    Part 4: debug frame display                                 *
// ******************************************************************
// The c++ function for: show_frame(self:Core/dbg_frame,frame:Core/dbg_frame) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  show_frame_dbg_frame1(Core_dbg_frame *self,Core_dbg_frame *frame) { 
    
    GC_BIND;
    { CL_INT  g0893 = (CL_INT )(current_color);
      CL_INT  g0894 = (CL_INT )(current_bold);
      CL_INT  g0895 = g0893;
      CL_INT  g0896 = g0894;
      color(g0893,g0894);
      color_princ_string1(((char*)"``BLUE["));
      g0893= (CL_INT)((CL_INT )(current_color));
      g0894= (CL_INT)((CL_INT )(current_bold));
      color(g0895,g0896);
      { OID  g0905UU;
        { OID  s = GC_OID(self->frame_source);
          if (s == CNULL)
           g0905UU = _oid_(ClEnv->module_I);
          else if (Kernel._method == OWNER(s))
           g0905UU = _oid_(OBJECT(restriction,s)->module_I);
          else if (INHERIT(OWNER(s),Kernel._tuple))
           g0905UU = (*(OBJECT(bag,s)))[1];
          else g0905UU = _oid_(ClEnv->module_I);
            }
        print_any(g0905UU);
        }
      color(g0893,g0894);
      color(g0893,g0894);
      color_princ_string1(((char*)"]"));
      g0893= (CL_INT)((CL_INT )(current_color));
      g0894= (CL_INT)((CL_INT )(current_bold));
      color(g0895,g0896);
      color_princ_string1(((char*)"``BLUE"));
      print_any(((OID)self->num));
      color(g0893,g0894);
      color(g0893,g0894);
      color_princ_string1(((char*)">> "));
      g0893= (CL_INT)((CL_INT )(current_color));
      g0894= (CL_INT)((CL_INT )(current_bold));
      color(g0895,g0896);
      color_princ_string1(((char*)"``BLUE"));
      { OID  g0906UU;
        { OID  s = GC_OID(self->frame_source);
          if (s == CNULL)
           g0906UU = _string_(((char*)"???"));
          else if (Kernel._method == OWNER(s))
           g0906UU = _oid_(OBJECT(restriction,s)->selector);
          else if (INHERIT(OWNER(s),Kernel._tuple))
           g0906UU = (*(OBJECT(bag,s)))[2];
          else g0906UU = s;
            }
        print_any(g0906UU);
        }
      color(g0893,g0894);
      color(g0893,g0894);
      color_princ_string1(((char*)"("));
      g0893= (CL_INT)((CL_INT )(current_color));
      g0894= (CL_INT)((CL_INT )(current_bold));
      color(g0895,g0896);
      { CL_INT  i = 1;
        list * l = GC_OBJECT(list,self->vars);
        CL_INT  len = ((CL_INT)2*(CL_INT)self->dimension);
        ClaireBoolean * f_ask = CTRUE;
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)i < (CL_INT)len))
          { { OID  vn = (*(l))[i];
              OID  vval = (*(l))[((CL_INT)i+(CL_INT)1)];
              i= (CL_INT)(((CL_INT)i+(CL_INT)2));
              { CL_INT  g0897 = (CL_INT )(current_color);
                CL_INT  g0898 = (CL_INT )(current_bold);
                CL_INT  g0899 = g0897;
                CL_INT  g0900 = g0898;
                color(g0899,g0900);
                if (f_ask == CTRUE)
                 f_ask= (CFALSE);
                else { CL_INT  g0901 = (CL_INT )(current_color);
                    CL_INT  g0902 = (CL_INT )(current_bold);
                    CL_INT  g0903 = g0901;
                    CL_INT  g0904 = g0902;
                    color(g0901,g0902);
                    color_princ_string1(((char*)"`BLUE, "));
                    color(g0903,g0904);
                    }
                  color(g0897,g0898);
                color(g0899,g0900);
                color_princ_string1(((char*)"`BLUE"));
                (*Kernel.princ)(vn);
                princ_string(((char*)" = "));
                color(g0897,g0898);
                color(g0899,g0900);
                print_any(vval);
                color(g0897,g0898);
                color(g0897,g0898);
                color_princ_string1(((char*)"`BLACK"));
                color(g0899,g0900);
                }
              }
            POP_SIGNAL;}
          }
        }
      color(g0893,g0894);
      color(g0893,g0894);
      color_princ_string1(((char*)")\n"));
      color(g0895,g0896);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: show_source_lines(self:Core/dbg_frame,n:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  show_source_lines_dbg_frame1(Core_dbg_frame *self,int n) { 
    
    GC_BIND;
    { ClaireHandler c_handle = ClaireHandler();
      if ERROR_IN 
      { { char * src = GC_STRING(self->source);
          CL_INT  l = self->line;
          CL_INT  c = self->column;
          CL_INT  len = self->length;
          buffer * f = GC_OBJECT(buffer,fopen_string1(src,((char*)"r")));
          CL_INT  i = 0;
          color_princ_string1(((char*)"`BLUE--- file `BLACK"));
          princ_string(src);
          color_princ_string1(((char*)" `BLUE---`BLACK\n"));
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) f))) != Kernel.ctrue))
            { GC_LOOP;
              ++i;
              if (i == l)
               { color_princ_string1(((char*)"`BLUE"));
                print_any(((OID)i));
                color_princ_string1(((char*)"`BLACK: "));
                freadwrite_port4(f,GC_OBJECT(PortObject,ClEnv->cout),((CL_INT)c-(CL_INT)1));
                { char * tmp = GC_STRING(fread_port4(f,len));
                  CL_INT  lentmp = LENGTH_STRING(tmp);
                  CL_INT  sp = 1;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    while (((CL_INT)sp < (CL_INT)lentmp))
                    { if (tmp[sp - 1] != ((unsigned char)' '))
                       { ;ClEnv->cHandle = loop_handle; break;}
                      princ_string(((char*)" "));
                      ++sp;
                      POP_SIGNAL;}
                    }
                  color_princ_string1(((char*)"``RED"));
                  i= (CL_INT)(((CL_INT)i+(CL_INT)occurrence_string(tmp,((char*)"\n"))));
                  princ_string1(tmp,sp,lentmp);
                  }
                color_princ_string1(((char*)"`BLACK"));
                princ_string(freadline_port1(f,((char*)"\n")));
                princ_string(((char*)"\n"));
                }
              else if ((CL_INT)i > (CL_INT)((CL_INT)l+(CL_INT)n))
               { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
              else { char * line = GC_STRING(freadline_port1(f,((char*)"\n")));
                  if ((CL_INT)((CL_INT)l-(CL_INT)n) <= (CL_INT)i)
                   { color_princ_string1(((char*)"`BLUE"));
                    print_any(((OID)i));
                    color_princ_string1(((char*)"`BLACK: "));
                    princ_string(line);
                    princ_string(((char*)"\n"));
                    }
                  }
                GC_UNLOOP;POP_SIGNAL;}
            }
          fclose_port1(f);
          }
        ERROR_FREE;}
      else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
      { c_handle.catchIt();{ CL_INT  g0907 = (CL_INT )(current_color);
          CL_INT  g0908 = (CL_INT )(current_bold);
          CL_INT  g0909 = g0907;
          CL_INT  g0910 = g0908;
          color(g0907,g0908);
          color_princ_string1(((char*)"`REDNo source file available\n"));
          color(g0909,g0910);
          }
        }
      else PREVIOUS_HANDLER;}
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: show_frame_info(self:Core/dbg_frame) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  show_frame_info_dbg_frame1(Core_dbg_frame *self) { 
    show_frame_info_dbg_frame2(self,self);
    POP_SIGNAL;}
  


// The c++ function for: show_frame_info(self:Core/dbg_frame,frame:Core/dbg_frame) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  show_frame_info_dbg_frame2(Core_dbg_frame *self,Core_dbg_frame *frame) { 
    show_frame_dbg_frame1(self,frame);
    show_source_lines_dbg_frame1(self,2);
    POP_SIGNAL;}
  


// The c++ function for: where(frame:Core/dbg_frame) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  where_dbg_frame1(Core_dbg_frame *frame) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    { Core_dbg_frame * fr = GC_OBJECT(Core_dbg_frame,OBJECT(Core_dbg_frame,Core.current_frame->value));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)fr->num > (CL_INT)0))
        { GC_LOOP;
          show_frame_dbg_frame1(fr,frame);
          GC__ANY(fr = fr->prev, 1);
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// ******************************************************************
// *    Part 5: frame variable binding                              *
// ******************************************************************
//<sb> DebugVariable is a container for local variable that :
//  - is bound to the symbol of the variable (bind_frame)
//  - hold the value of the variable to which it evaluates (self_eval)
// The c++ function for: self_eval(self:DebugVariable) [RETURN_ARG]
CL_EXPORT OID  self_eval_DebugVariable1(Reader_DebugVariable *self) { 
    POP_SIGNAL; return (self->value);}
  


// add frame variables to the lexical environment
// The c++ function for: bind_frame(self:Core/dbg_frame) [NEW_ALLOC]
CL_EXPORT list * bind_frame_dbg_frame1(Core_dbg_frame *self) { 
    
    GC_BIND;
    { list *Result ;
      { list * vs = self->vars;
        CL_INT  len = vs->length;
        CL_INT  i = 1;
        list * bindings = list::empty(Kernel._any);
        { CL_INT loop_handle = ClEnv->cHandle;
          while (((CL_INT)i < (CL_INT)len))
          { { symbol * sym = symbol_I_string(string_v((*(vs))[i]),ClEnv->module_I);
              OID  oval = get_symbol(sym);
              if ((*(vs))[((CL_INT)i+(CL_INT)1)] != _oid_(Core.undefined_debug))
               { bindings->addFast((OID)_oid_(sym));
                bindings->addFast((OID)oval);
                put_symbol(sym,_oid_(((Reader_DebugVariable *) (*Reader._DebugVariable)((*(vs))[((CL_INT)i+(CL_INT)1)]))));
                }
              i= (CL_INT)(((CL_INT)i+(CL_INT)2));
              }
            POP_SIGNAL;}
          }
        Result = bindings;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// remove frame variable from the lexical environment
// The c++ function for: unbind_frame(bindings:list) [RETURN_ARG]
CL_EXPORT void  unbind_frame_list1(list *bindings) { 
    { CL_INT  len = bindings->length;
      CL_INT  i = 1;
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((CL_INT)i < (CL_INT)len))
        { put_symbol(OBJECT(symbol,(*(bindings))[i]),(*(bindings))[((CL_INT)i+(CL_INT)1)]);
          i= (CL_INT)(((CL_INT)i+(CL_INT)2));
          POP_SIGNAL;}
        }
      }
    POP_SIGNAL;}
  



/***** CLAIRE Compilation of file ./meta/wcl.cl 
         [version 3.5.0 / safety 5] *****/


//*********************************************************************
//* CLAIRE                                            Sylvain Benilan *
//* wcl.cl                                                            *
//* Copyright (C) 2000 - 2003 xl. All Rights Reserved                 *
//*********************************************************************
// ********************************************************************
// *   Part 1: echo & self_html (<?= and <?==)                        *
// ********************************************************************
// The c++ function for: print_oid(x:any) [0]
CL_EXPORT void  print_oid_any1(OID x) { 
    princ_string(CL_Oid(x));
    POP_SIGNAL;}
  


// The c++ function for: echo(self:any) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT void  echo_any1_Reader(OID self) { 
    (*Kernel.self_print)(self);
    POP_SIGNAL;}
  


// The c++ function for: echo(self:string) [0]
CL_EXPORT void  echo_string1_Reader(char *self) { 
    princ_string(self);
    POP_SIGNAL;}
  


// The c++ function for: echo(self:integer) [0]
CL_EXPORT void  echo_integer1_Reader(CL_INT self) { 
    princ_integer(self);
    POP_SIGNAL;}
  


// The c++ function for: echo(g0911:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  echo_float1_Reader_(OID g0911) { 
    echo_float1_Reader(float_v(g0911));
}


// The c++ function for: echo(self:float) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  echo_float1_Reader(double self) { 
      
    GC_BIND;
    print_any(GC_OID(_float_(self)));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: echo(self:char) [0]
CL_EXPORT void  echo_char1_Reader(ClaireChar *self) { 
    princ_char(self);
    POP_SIGNAL;}
  


// The c++ function for: echo(p:property,self:object) [NEW_ALLOC+RETURN_ARG]
CL_EXPORT void  echo_property1_Reader(property *p,ClaireObject *self) { 
    
    GC_BIND;
    if (known_ask_property(p,self) == CTRUE)
     (*Language.echo)(GC_OID(get_property(p,self)));
    else ;GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_html(src:string) [0]
CL_EXPORT void  self_html_string1_Reader(char *src) { 
    { CL_INT  len = LENGTH_STRING(src);
      {
		char *max = src + len;
		char buf[256];
		char *travel = buf;
		while(src < max) {
			int c = (unsigned char)(*src);
			switch(c) {
				case '\"':
					{*travel++ = '&';
					*travel++ = 'q';
					*travel++ = 'u';
					*travel++ = 'o';
					*travel++ = 't';
					*travel++ = ';';
					break;}
				case '\'':
					{*travel++ = '&';
					*travel++ = 'a';
					*travel++ = 'p';
					*travel++ = 'o';
					*travel++ = 's';
					*travel++ = ';';
					break;}
				case '<':
					{*travel++ = '&';
					*travel++ = 'l';
					*travel++ = 't';
					*travel++ = ';';
					break;}
				case '>':
					{*travel++ = '&';
					*travel++ = 'g';
					*travel++ = 't';
					*travel++ = ';';
					break;}
				case '&':
					{*travel++ = '&';
					*travel++ = 'a';
					*travel++ = 'm';
					*travel++ = 'p';
					*travel++ = ';';
					break;}
				default: *travel++ = c;
			}
			if (travel - buf > 240) {
				Core.write_port->fcall((CL_INT)ClEnv->cout, (CL_INT)buf, (CL_INT)(travel - buf));
				travel = buf;
			}
			src++;
		}
		if (travel - buf > 0)
			Core.write_port->fcall((CL_INT)ClEnv->cout, (CL_INT)buf, (CL_INT)(travel - buf));};
      }
    POP_SIGNAL;}
  


// The c++ function for: nl2br(self:string) [NEW_ALLOC]
CL_EXPORT char * nl2br_string1(char *self) { 
    
    GC_BIND;
    { char *Result ;
      Result = replace_string(GC_STRING(replace_string(self,((char*)"\n"),((char*)"<br>"))),((char*)"\r"),((char*)""));
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: write_port(self:self_html_converter,buf:char*,len:integer) [SAFE_RESULT]
CL_EXPORT CL_INT  write_port_self_html_converter1_Reader(Reader_self_html_converter *self,char*buf,int len) { 
    {char out[256]; char *travel = out;
		int i = 0;
		for(;i < len;i++) {
			switch (buf[i]) {
				case '\"':
					{*travel++ = '&';
					*travel++ = 'q';
					*travel++ = 'u';
					*travel++ = 'o';
					*travel++ = 't';
					*travel++ = ';';
					break;}
				case '\'':
					{*travel++ = '&';
					*travel++ = 'a';
					*travel++ = 'p';
					*travel++ = 'o';
					*travel++ = 's';
					*travel++ = ';';
					break;}
				case '<':
					{*travel++ = '&';
					*travel++ = 'l';
					*travel++ = 't';
					*travel++ = ';';
					break;}
				case '>':
					{*travel++ = '&';
					*travel++ = 'g';
					*travel++ = 't';
					*travel++ = ';';
					break;}
				case '&':
					{*travel++ = '&';
					*travel++ = 'a';
					*travel++ = 'm';
					*travel++ = 'p';
					*travel++ = ';';
					break;}
				default : *travel++ = buf[i];
			}
			if (travel - out > 200) {
				Core.write_port->fcall((CL_INT)self->src, (CL_INT)out, (CL_INT)(travel - out));
				travel = out;
			}
		}
		if (travel - out > 0)
			Core.write_port->fcall((CL_INT)self->src, (CL_INT)out, (CL_INT)(travel - out));
		};
    POP_SIGNAL; return (len);}
  


// The c++ function for: self_html(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_html_any1_Reader(OID self) { 
    
    GC_BIND;
    { ClaireHandler c_handle = ClaireHandler();
      if ERROR_IN 
      { { Reader_self_html_converter * conv = OBJECT(Reader_self_html_converter,Reader.SELF_HTML_CONVERTER->value);
          PortObject * old = use_as_output_port(conv);
          set_length_blob1(conv->src,0);
          print_any(self);
          use_as_output_port(old);
          freadwrite_port4(GC_OBJECT(blob,conv->src),GC_OBJECT(PortObject,ClEnv->cout),1);
          freadwrite_port3(GC_OBJECT(blob,conv->src),GC_OBJECT(PortObject,ClEnv->cout));
          }
        ERROR_FREE;}
      else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
      { c_handle.catchIt();if (should_trace_ask_module1(Reader.it,-100) == CTRUE)
         mtformat_module1(Reader.it,((char*)"self_html(~S) failed \n"),-100,list::alloc(1,_oid_(OWNER(self))));
        else ;}
      else PREVIOUS_HANDLER;}
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: self_html(p:property,self:object) [NEW_ALLOC]
CL_EXPORT void  self_html_property1_Reader(property *p,ClaireObject *self) { 
    
    GC_BIND;
    if ((boolean_I_any(_oid_(_at_property1(p,OWNER(_oid_(self))))) == CTRUE) && 
        (known_ask_property(p,self) == CTRUE))
     (*Language.self_html)(GC_OID(get_property(p,self)));
    else ;GC_UNBIND; POP_SIGNAL;}
  


// *********************************************************************
// *   Part 2: Reader callback                                         *
// *********************************************************************
// The c++ function for: wcl_start?(r:meta_reader,p:integer) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * wcl_start_ask_meta_reader1(meta_reader *r,int p) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      if (p == 63)
       { ClaireChar * c = getc_port1(r->fromp);
        if (((unsigned char) c->ascii) == ((unsigned char)'>'))
         Result = CTRUE;
        else { unget_port2(r->fromp,c);
            Result = CFALSE;
            }
          }
      else Result = CFALSE;
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: nextswcl(r:meta_reader) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  nextswcl_meta_reader1(meta_reader *r) { 
    
    GC_BIND;
    { OID Result = 0;
      { OID  wcl = GC_OID(nexts_meta_reader(r,Core.none));
        if ((equal(wcl,r->paren) == CTRUE) || 
            ((equal(wcl,r->curly) == CTRUE) || 
              ((equal(wcl,Reader.OR->value) == CTRUE) || 
                ((equal(wcl,r->bracket) == CTRUE) || 
                  (equal(wcl,r->comma) == CTRUE)))))
         Result = _oid_(Core.none);
        else if (wcl == _oid_(Reader._cl_if))
         Result = readif_meta_reader(r,integer_I_char(_char_(((unsigned char)')'))));
        else if (wcl == _oid_(Reader._cl_Zif))
         { If * _Zi = GC_OBJECT(If,OBJECT(If,readif_meta_reader(r,integer_I_char(_char_(((unsigned char)')'))))));
          if (boolean_I_any(eval_any(GC_OID(_Zi->test))) == CTRUE)
           Result = _Zi->arg;
          else Result = _Zi->other;
            }
        else if (wcl == _oid_(Reader._cl_else))
         Serror_integer1(173,((char*)"Expression starting with else"),Kernel.nil);
        else if (keyword_ask_any(wcl) == CTRUE)
         Result = nextstruct_meta_reader(r,OBJECT(keyword,wcl),Core.none);
        else Result = wcl;
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: Call_wcl!(self:property,l:list,loc:tuple) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT Call_wcl * Call_wcl_I_property1(property *self,list *l,tuple *loc) { 
    
    GC_BIND;
    { Call_wcl *Result ;
      { Call_wcl * c;
        { { Instruction *V_CC ;
            { Call_wcl * _CL_obj = ((Call_wcl *) GC_OBJECT(Call_wcl,new_object_class(Language._Call_wcl)));
              _void_(_CL_obj->selector = self);
              _void_(_CL_obj->args = l);
              add_I_property(Kernel.instances,Language._Call_wcl,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            c= (Call_wcl *) V_CC;}
          GC_OBJECT(Call_wcl,c);}
        tuple * g0912 = loc;
        OID  f = (*(g0912))[1];
        OID  ln = (*(g0912))[2];
        OID  o = (*(g0912))[3];
        char * s = ((self == Language.self_html) ?
          ((char*)"==") :
          ((self == Language.echo) ?
            ((char*)"=") :
            self->name->name ) );
        Result = c;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: build_call_wcl(r:meta_reader,prop:property) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  build_call_wcl_meta_reader2(meta_reader *r,property *prop) { 
    
    GC_BIND;
    { OID Result = 0;
      { tuple * loc = GC_OBJECT(tuple,get_location_port1(GC_OBJECT(PortObject,r->fromp))->copyIfNeeded());
        OID  wcl = GC_OID(nextswcl_meta_reader1(r));
        if (wcl == Core._eof->value)
         Result = Core._eof->value;
        else { { if (INHERIT(OWNER(wcl),Language._Call_plus))
               { if (((prop == Language.self_html) || 
                      (prop == Language.echo)) && 
                    (OBJECT(Call,wcl)->args->length == 1))
                 wcl = _oid_(Call_wcl_I_property1(prop,list::alloc(2,_oid_(OBJECT(Call,wcl)->selector),GC_OID((*(OBJECT(Call,wcl)->args))[1])),loc));
                else wcl = _oid_(Call_wcl_I_property1(prop,list::alloc(1,wcl),loc));
                  }
              else wcl = _oid_(Call_wcl_I_property1(prop,list::alloc(1,wcl),loc));
                GC_OID(wcl);}
            if (wcl_start_ask_meta_reader1(r,((CL_INT)skipc_meta_reader(r))) == CTRUE)
             { OID  swcl = GC_OID(read_wcl_meta_reader1(r));
              if (swcl == Core._eof->value)
               Result = wcl;
              else Result = Do_I_any(wcl,swcl);
                }
            else Result = wcl;
              }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: build_top_call_wcl(r:meta_reader,prop:property) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT OID  build_top_call_wcl_meta_reader1(meta_reader *r,property *prop) { 
    
    GC_BIND;
    { OID Result = 0;
      { tuple * loc = GC_OBJECT(tuple,get_location_port1(GC_OBJECT(PortObject,r->fromp))->copyIfNeeded());
        OID  wcl = GC_OID(nexte_meta_reader(r));
        if (wcl == Core._eof->value)
         Result = Core._eof->value;
        else { { if (INHERIT(OWNER(wcl),Language._Call_plus))
               { if (((prop == Language.self_html) || 
                      (prop == Language.echo)) && 
                    (OBJECT(Call,wcl)->args->length == 1))
                 wcl = _oid_(Call_wcl_I_property1(prop,list::alloc(2,_oid_(OBJECT(Call,wcl)->selector),GC_OID((*(OBJECT(Call,wcl)->args))[1])),loc));
                else wcl = _oid_(Call_wcl_I_property1(prop,list::alloc(1,wcl),loc));
                  }
              else wcl = _oid_(Call_wcl_I_property1(prop,list::alloc(1,wcl),loc));
                GC_OID(wcl);}
            Result = wcl;
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> called by nextunit at the toplevel of a source file
// single wcl fragments are read
// The c++ function for: read_top_wcl(r:meta_reader) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  read_top_wcl_meta_reader1(meta_reader *r) { 
    
    GC_BIND;
    { OID Result = 0;
      { PortObject * p = GC_OBJECT(PortObject,r->fromp);
        tuple * loc = GC_OBJECT(tuple,get_location_port1(GC_OBJECT(PortObject,r->fromp))->copyIfNeeded());
        char * d = GC_STRING(freadline_port1(p,((char*)"<?")));
        Princ_wcl * c;
        { { Instruction *V_CC ;
            { Princ_wcl * _CL_obj = ((Princ_wcl *) GC_OBJECT(Princ_wcl,new_object_class(Language._Princ_wcl)));
              _void_(_CL_obj->selector = Kernel.princ);
              _void_(_CL_obj->args = list::alloc(1,_string_(d)));
              add_I_property(Kernel.instances,Language._Princ_wcl,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            c= (Princ_wcl *) V_CC;}
          GC_OBJECT(Princ_wcl,c);}
        _void_(p->firstc = integer_I_char(_char_(((unsigned char)' '))));
        { tuple * g0913 = freadline_port4(p,OBJECT(bag,Reader.WCL_STOP->value));
          OID  inl = GC_OID((*(g0913))[1]);
          OID  sep = GC_OID((*(g0913))[2]);
          if (equal(sep,_string_(((char*)"?"))) == CTRUE)
           { ClaireChar * ch = getc_port1(p);
            if (((unsigned char) ch->ascii) == ((unsigned char)'>'))
             { OID  swcl = GC_OID(read_top_wcl_meta_reader1(r));
              if (swcl == Core._eof->value)
               Result = _oid_(c);
              else Result = Do_I_any(_oid_(c),swcl);
                }
            else { unget_port2(p,_char_(((unsigned char)'?')));
                unget_port2(p,ch);
                Result = _oid_(c);
                }
              }
          else { if ((CL_INT)LENGTH_STRING(string_v(sep)) > (CL_INT)0)
               (*Core.unget)(_oid_(p),
                sep);
              if (LENGTH_STRING(string_v(inl)) == 0)
               Result = _oid_(c);
              else { OID  prop;
                  if (equal(inl,_string_(((char*)"="))) == CTRUE)
                   prop = _oid_(Language.echo);
                  else if (equal(inl,_string_(((char*)"=="))) == CTRUE)
                   prop = _oid_(Language.self_html);
                  else if (equal(inl,_string_(((char*)"oid"))) == CTRUE)
                   prop = _oid_(Reader.print_oid);
                  else prop = value_string(string_v(inl));
                    if (prop != CNULL)
                   Result = Do_I_any(_oid_(c),GC_OID(build_top_call_wcl_meta_reader1(r,OBJECT(property,prop))));
                  else { OID  V_CL0914;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"The property ~A is not known in ...<?~A")),
                        _oid_(list::alloc(2,inl,inl)))));
                      
                      Result=_void_(V_CL0914);}
                    }
                }
            }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: read_wcl(r:meta_reader) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT OID  read_wcl_meta_reader1(meta_reader *r) { 
    
    GC_BIND;
    { OID Result = 0;
      { PortObject * p = GC_OBJECT(PortObject,r->fromp);
        tuple * loc = GC_OBJECT(tuple,get_location_port1(GC_OBJECT(PortObject,r->fromp))->copyIfNeeded());
        char * d = GC_STRING(freadline_port1(p,((char*)"<?")));
        Princ_wcl * c;
        { { Instruction *V_CC ;
            { Princ_wcl * _CL_obj = ((Princ_wcl *) GC_OBJECT(Princ_wcl,new_object_class(Language._Princ_wcl)));
              _void_(_CL_obj->selector = Kernel.princ);
              _void_(_CL_obj->args = list::alloc(1,_string_(d)));
              add_I_property(Kernel.instances,Language._Princ_wcl,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            c= (Princ_wcl *) V_CC;}
          GC_OBJECT(Princ_wcl,c);}
        char * pend = ((char*)"");
        _void_(p->firstc = integer_I_char(_char_(((unsigned char)' '))));
        { tuple * g0915 = freadline_port4(p,OBJECT(bag,Reader.WCL_STOP->value));
          OID  inl = GC_OID((*(g0915))[1]);
          OID  sep = GC_OID((*(g0915))[2]);
          if (equal(sep,_string_(((char*)"?"))) == CTRUE)
           { ClaireChar * ch = getc_port1(p);
            if (((unsigned char) ch->ascii) == ((unsigned char)'>'))
             Result = Do_I_any(_oid_(c),GC_OID(read_wcl_meta_reader1(r)));
            else { unget_port2(p,_char_(((unsigned char)'?')));
                unget_port2(p,ch);
                Result = _oid_(c);
                }
              }
          else { if ((CL_INT)LENGTH_STRING(string_v(sep)) > (CL_INT)0)
               (*Core.unget)(_oid_(p),
                sep);
              if (LENGTH_STRING(string_v(inl)) == 0)
               { if ((equal(sep,_string_(((char*)"|"))) == CTRUE) || 
                    ((equal(sep,_string_(((char*)"}"))) == CTRUE) || 
                      ((equal(sep,_string_(((char*)"]"))) == CTRUE) || 
                        ((equal(sep,_string_(((char*)")"))) == CTRUE) || 
                          (equal(sep,_string_(((char*)","))) == CTRUE)))))
                 Result = _oid_(c);
                else { OID  g0916UU;
                    { { OID  wcl = GC_OID(nextswcl_meta_reader1(r));
                        if (wcl_start_ask_meta_reader1(r,((CL_INT)skipc_meta_reader(r))) == CTRUE)
                         g0916UU = Do_I_any(wcl,GC_OID(read_wcl_meta_reader1(r)));
                        else g0916UU = wcl;
                          }
                      GC_OID(g0916UU);}
                    Result = Do_I_any(_oid_(c),g0916UU);
                    }
                  }
              else { OID  prop;
                  if (equal(inl,_string_(((char*)"="))) == CTRUE)
                   prop = _oid_(Language.echo);
                  else if (equal(inl,_string_(((char*)"=="))) == CTRUE)
                   prop = _oid_(Language.self_html);
                  else if (equal(inl,_string_(((char*)"oid"))) == CTRUE)
                   prop = _oid_(Reader.print_oid);
                  else prop = value_string(string_v(inl));
                    if (prop != CNULL)
                   Result = Do_I_any(_oid_(c),GC_OID(build_call_wcl_meta_reader2(r,OBJECT(property,prop))));
                  else { OID  V_CL0917;close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"The property ~A is not known in ...<?~A")),
                        _oid_(list::alloc(2,inl,inl)))));
                      
                      Result=_void_(V_CL0917);}
                    }
                }
            }
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// *********************************************************************
// *   Part 3: wcl file                                                *
// *********************************************************************
//<sb> activate web claire reader
// The c++ function for: fopen_source(self:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT PortObject * fopen_source_string1(char *self) { 
    
    GC_BIND;
    if ((isfile_ask_string(self) != CTRUE) && 
        ((match_wildcard_ask_string(self,((char*)"*.cl")) != CTRUE) && 
          (match_wildcard_ask_string(self,((char*)"*.wcl")) != CTRUE)))
     self= (GC_STRING(append_string(self,((char*)".cl"))));
    { PortObject *Result ;
      { PortObject * f = GC_OBJECT(buffer,fopen_string1(self,((char*)"r")));
        if (match_wildcard_ask_string(self,((char*)"*.wcl")) == CTRUE)
         { char * l = GC_STRING(freadline_port(f));
          if (match_wildcard_ask_string(l,((char*)"#!*")) == CTRUE)
           { unget_port1(f,((char*)"\n?>"));
            unget_port1(f,l);
            }
          else { unget_port1(f,((char*)"\n"));
              unget_port1(f,l);
              unget_port1(f,((char*)"?>"));
              }
            }
        f= (GC_OBJECT(line_counter,close_target_I_filter1(line_counter_I_port1(f))));
        Result = f;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> reads a WCL file and return a list of claire definition
// self should look like "filepath@PATH_INFO@path_info"
// The c++ function for: load_wcl!(self:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT list * load_wcl_I_string1(char *self) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    reader_push_void1();
    _void_(Reader.reader->index = 1);
    _void_(Reader.reader->maxstack = 1);
    { list *Result ;
      { list * t = GC_OBJECT(list,explode_string(self,((char*)"@PATH_INFO@")));
        char * fname = GC_STRING(string_v(last_list(explode_string(string_v((*(t))[1]),GC_STRING(string_v(Core._starfs_star->value))))));
        char * pinfo = GC_STRING((((CL_INT)t->length > (CL_INT)1) ?
          _7_string(string_v((*(t))[2]),fname) :
          fname ));
        PortObject * f = GC_OBJECT(PortObject,fopen_source_string1(string_v((*(t))[1])));
        tuple * loc = GC_OBJECT(tuple,get_location_port1(f)->copyIfNeeded());
        CL_INT  start = ClEnv->base;
        CL_INT  top = ClEnv->index;
        OID  _staritem_star = CNULL;
        list * defs = list::empty(Language._Defclaire);
        Do * bo;
        { { Instruction *V_CC ;
            { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
              _void_(_CL_obj->args = list::empty(Kernel._any));
              add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
              V_CC = close_Instruction1(_CL_obj);
              }
            bo= (Do *) V_CC;}
          GC_OBJECT(Do,bo);}
        list * lbody = GC_OBJECT(list,bo->args);
        (ClEnv->base= ((OID)top));
        _void_(Reader.reader->fromp = f);
        _void_(Reader.reader->toplevel = CFALSE);
        _staritem_star= (GC_OID(readblock_port(f)));
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while ((equal(_staritem_star,Core._eof->value) != CTRUE))
          { GC_LOOP;
            (ClEnv->base= ((OID)top));
            index_jump_integer1(((CL_INT)top+(CL_INT)((CL_INT)Reader.reader->maxstack+(CL_INT)1)));
            if (Kernel._string == OWNER(_staritem_star))
             ;else if (INHERIT(OWNER(_staritem_star),Language._Defclaire))
             defs->addFast((OID)_staritem_star);
            else lbody->addFast((OID)_staritem_star);
              _void_(Reader.reader->index = 1);
            _void_(Reader.reader->maxstack = 1);
            (ClEnv->index= ((OID)top));
            (ClEnv->base= ((OID)top));
            GC__OID(_staritem_star = readblock_port(f), 1);
            GC_UNLOOP;POP_SIGNAL;}
          }
        { OID  g0918UU;
          { { Defmethod * _CL_obj = ((Defmethod *) GC_OBJECT(Defmethod,new_object_class(Language._Defmethod)));
              { Defmethod * g0919 = _CL_obj; 
                Call * g0920;
                { Instruction *V_CC ;
                  { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
                    _void_(_CL_obj->selector = Reader.load_wcl);
                    { Call * g0921 = _CL_obj; 
                      list * g0922;
                      { OID v_bag;
                        GC_ANY(g0922= list::empty(Kernel.emptySet));
                        { { Vardef * _CL_obj = ((Vardef *) GC_OBJECT(Vardef,new_object_class(Language._Vardef)));
                            _void_(_CL_obj->pname = gensym_void());
                            _void_(_CL_obj->range = set::alloc(1,_string_(pinfo)));
                            add_I_property(Kernel.instances,Language._Vardef,11,_oid_(_CL_obj));
                            v_bag = _oid_(close_Instruction1(_CL_obj));
                            }
                          GC_OID(v_bag);}
                        ((list *) g0922)->addFast((OID)v_bag);}
                      _void_(g0921->args = g0922);}
                    add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
                    V_CC = close_Instruction1(_CL_obj);
                    }
                  g0920= (Call *) V_CC;}
                _void_(g0919->arg = g0920);}
              _void_(_CL_obj->set_arg = _oid_(Kernel._void));
              _void_(_CL_obj->body = _oid_(bo));
              _void_(_CL_obj->inline_ask = Kernel.cfalse);
              add_I_property(Kernel.instances,Language._Defmethod,11,_oid_(_CL_obj));
              g0918UU = _oid_(close_Instruction1(_CL_obj));
              }
            GC_OID(g0918UU);}
          defs->addFast((OID)g0918UU);
          }
        reader_pop_void1();
        (ClEnv->base= ((OID)start));
        (ClEnv->index= ((OID)top));
        fclose_port1(f);
        Result = defs;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


//<sb> add a list of WCL file defined by wcl_path wildcard
// to the module's made_of. Any further request with the
// given pathinfo/file will call the compiled method
// The c++ function for: add_wcl(self:module,wcl_path:string,wild:string,pathinfo:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  add_wcl_module1(module *self,char *wcl_path,char *wild,char *pathinfo) { 
    
    GC_BIND;
    setenv_string(((char*)"WCL_RAISE_ERRORS=1"));
    cast_I_list1(self->made_of,Kernel._string);
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(x);
      bag *x_support;
      x_support = GC_OBJECT(list,entries_string1(wcl_path,wild));
      for (START(x_support); NEXT(x);)
      { GC_LOOP;
        if (((CL_INT)LENGTH_STRING(string_v(x)) > (CL_INT)0) && 
            (string_v(x)[1 - 1] != ((unsigned char)'.')))
         { if (isfile_ask_string(_7_string(wcl_path,string_v(x))) == CTRUE)
           GC_OBJECT(list,self->made_of)->addFast((OID)GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(_7_string(wcl_path,string_v(x))),((char*)"@PATH_INFO@"))),pathinfo))));
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(x);
      bag *x_support;
      x_support = GC_OBJECT(list,entries_string2(wcl_path));
      for (START(x_support); NEXT(x);)
      { GC_LOOP;
        if (isdir_ask_string(_7_string(wcl_path,string_v(x))) == CTRUE)
         add_wcl_module1(self,GC_STRING(_7_string(wcl_path,string_v(x))),wild,GC_STRING(_7_string(pathinfo,string_v(x))));
        GC_UNLOOP; POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: add_wcl(self:module,wcl_path:string,wild:subtype[string],pathinfo:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  add_wcl_module2(module *self,char *wcl_path,ClaireType *wild,char *pathinfo) { 
    
    GC_BIND;
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(w);
      bag *w_support;
      w_support = GC_OBJECT(bag,enumerate_any(_oid_(wild)));
      for (START(w_support); NEXT(w);)
      add_wcl_module1(self,wcl_path,string_v(w),pathinfo);
      }
    GC_UNBIND; POP_SIGNAL;}
  



/***** CLAIRE Compilation of file ./meta/codedoc.cl 
         [version 3.5.0 / safety 5] *****/


// **********************************************************************
// *   Part 1: hash table                                               *
// **********************************************************************
// The c++ function for: hash_table!(n:integer) [NEW_ALLOC]
CL_EXPORT Reader_hash_table * hash_table_I_integer1(CL_INT n) { 
    
    GC_BIND;
    { Reader_hash_table *Result ;
      { Reader_hash_table * _CL_obj = ((Reader_hash_table *) GC_OBJECT(Reader_hash_table,new_object_class(Reader._hash_table)));
        _void_(_CL_obj->hash_max = n);
        _void_(_CL_obj->content = make_list_integer2(n,Kernel._any,((OID)0)));
        Result = _CL_obj;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: reset(self:hash_table) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  reset_hash_table1(Reader_hash_table *self) { 
    _void_(self->hash_max = 0);
    _void_(self->content = Kernel.nil);
    POP_SIGNAL;}
  


// The c++ function for: hash_value_oid(self:hash_table,value:any) [RETURN_ARG]
CL_EXPORT CL_INT  hash_value_oid_hash_table1(Reader_hash_table *self,OID value) { 
    unsigned char *val = (unsigned char*)&value;
    { CL_INT Result = 0;
      { CL_INT  h = 0;
        h += val[0]; h += (h << 10); h ^= (h >> 6);
        h += val[1]; h += (h << 10); h ^= (h >> 6);
        h += val[2]; h += (h << 10); h ^= (h >> 6);
        h += val[3]; h += (h << 10); h ^= (h >> 6);
        h += (h << 3); h ^= (h >> 11); h += (h << 15);
        h &= self->hash_max;
        Result = (((CL_INT)1 <= (CL_INT)h) ?
          h :
          1 );
        }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: hash_value_string(self:hash_table,value:string) [RETURN_ARG]
CL_EXPORT CL_INT  hash_value_string_hash_table1(Reader_hash_table *self,char *value) { 
    { CL_INT Result = 0;
      { CL_INT  len = LENGTH_STRING(value);
        CL_INT  h = 0;
        { CL_INT  i = 0;
          CL_INT  g0924 = ((CL_INT)len-(CL_INT)1);
          { CL_INT loop_handle = ClEnv->cHandle;
            while (((CL_INT)i <= (CL_INT)g0924))
            { unsigned char c = value[i];
              c = c >= 'A' && 'Z' >= c ? c + ('a' - 'A') : c;
              h += c;
              h += (h << 10); h ^= (h >> 6);
              ++i;
              POP_SIGNAL;}
            }
          }
        h += (h << 3); h ^= (h >> 11); h += (h << 15);
        h &= self->hash_max;
        Result = (((CL_INT)1 <= (CL_INT)h) ?
          h :
          1 );
        }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: nth=(self:hash_table,key:any,val:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  nth_equal_hash_table1(Reader_hash_table *self,OID key,OID val) { 
    
    GC_BIND;
    { ClaireBoolean * str_ask = ((Kernel._string == OWNER(key)) ?
        CTRUE :
        CFALSE );
      CL_INT  h = ((str_ask == CTRUE) ?
        hash_value_string_hash_table1(self,string_v(key)) :
        hash_value_oid_hash_table1(self,key) );
      list * g = GC_OBJECT(list,self->content);
      OID  x = (*(g))[h];
      if (x == ((OID)0))
       { if (val != CNULL)
         { OID  g0925UU;
          { Reader_map_node * _CL_obj = ((Reader_map_node *) GC_OBJECT(Reader_map_node,new_object_class(Reader._map_node)));
            _void_(_CL_obj->nkey = key);
            _void_(_CL_obj->nval = val);
            g0925UU = _oid_(_CL_obj);
            }
          ((*(g))[h]=g0925UU);
          }
        }
      else { ClaireBoolean * ok_ask = CFALSE;
          { CL_INT loop_handle = ClEnv->cHandle;
            while ((x != CNULL))
            { { Reader_map_node * n = OBJECT(Reader_map_node,x);
                if (((str_ask == CTRUE) && 
                      ((Kernel._string == OWNER(n->nkey)) && (insensitive_equal_string1(string_v(key),string_v(n->nkey)) == CTRUE))) || 
                    ((str_ask != CTRUE) && 
                        (equal(n->nkey,key) == CTRUE)))
                 { _void_(n->nval = val);
                  ok_ask= (CTRUE);
                  { ;ClEnv->cHandle = loop_handle; break;}
                  }
                x = n->next ? _oid_(n->next) : CNULL;
                }
              POP_SIGNAL;}
            }
          if (ok_ask != CTRUE)
           { OID  g0926UU;
            { Reader_map_node * _CL_obj = ((Reader_map_node *) GC_OBJECT(Reader_map_node,new_object_class(Reader._map_node)));
              _void_(_CL_obj->nkey = key);
              _void_(_CL_obj->nval = val);
              update_property(Reader.next,
                _CL_obj,
                4,
                Kernel._object,
                (*(g))[h]);
              g0926UU = _oid_(_CL_obj);
              }
            ((*(g))[h]=g0926UU);
            }
          }
        }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: nth(self:hash_table,key:any) [0]
CL_EXPORT OID  nth_hash_table1(Reader_hash_table *self,OID key) { 
    { OID Result = 0;
      { ClaireBoolean * str_ask = ((Kernel._string == OWNER(key)) ?
          CTRUE :
          CFALSE );
        CL_INT  h = ((str_ask == CTRUE) ?
          hash_value_string_hash_table1(self,string_v(key)) :
          hash_value_oid_hash_table1(self,key) );
        list * g = self->content;
        OID  x = (*(g))[h];
        OID  res = CNULL;
        if (x != ((OID)0))
         { CL_INT loop_handle = ClEnv->cHandle;
          while ((x != CNULL))
          { { Reader_map_node * n = OBJECT(Reader_map_node,x);
              if (((str_ask == CTRUE) && 
                    ((Kernel._string == OWNER(n->nkey)) && (insensitive_equal_string1(string_v(key),string_v(n->nkey)) == CTRUE))) || 
                  ((str_ask != CTRUE) && 
                      (equal(n->nkey,key) == CTRUE)))
               { res= (n->nval);
                { ;ClEnv->cHandle = loop_handle; break;}
                }
              x = n->next ? _oid_(n->next) : CNULL;
              }
            POP_SIGNAL;}
          }
        Result = res;
        }
      POP_SIGNAL; return (Result);}
    }
  


// **********************************************************************
// *   Part 1: model                                                    *
// **********************************************************************
// The c++ function for: add_ref_to_item(self:doc_item,nm:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  add_ref_to_item_doc_item1(Reader_doc_item *self,char *nm) { 
    
    GC_BIND;
    if (find_string2(nm,((char*)" ")) == 0)
     { Reader_doc_link * _CL_obj = ((Reader_doc_link *) GC_OBJECT(Reader_doc_link,new_object_class(Reader._doc_link)));
      _void_(_CL_obj->name = nm);
      _void_(_CL_obj->oid = CL_Oid(_oid_(self)));
      add_I_property(Kernel.instances,Reader._doc_link,11,_oid_(_CL_obj));
      _void_(_CL_obj->documentation = string_v(CLREAD(slot,_at_property1(Reader.documentation,Reader._doc_link),DEFAULT)));
      ;}
    nth_equal_hash_table1(OBJECT(Reader_hash_table,Reader.NAME_TO_ITEM_TABLE->value),_string_(nm),_oid_(self));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: string2item(ctx:doc_context,s:string) [NEW_ALLOC]
CL_EXPORT OID  string2item_doc_context1(Reader_doc_context *ctx,char *s) { 
    { OID Result = 0;
      { OID  x = nth_hash_table1(OBJECT(Reader_hash_table,Reader.NAME_TO_ITEM_TABLE->value),_string_(s));
        if (x != CNULL)
         Result = x;
        else if (ctx->in_code_ask != CTRUE)
         Result = CNULL;
        else { OID  x = nth_hash_table1(OBJECT(Reader_hash_table,Reader.NAME_TO_ITEM_TABLE->value),_string_(append_string(((char*)"code/"),s)));
            if (x != CNULL)
             Result = x;
            else Result = CNULL;
              }
          }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: save_doc_links(ctx:doc_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  save_doc_links_doc_context1(Reader_doc_context *ctx) { 
    
    GC_BIND;
    { buffer * f = GC_OBJECT(buffer,fopen_string1(GC_STRING(append_string(GC_STRING(_7_string(GC_STRING(ctx->directory),ctx->source->name->name)),((char*)".links"))),((char*)"w")));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(g0927);
        bag *g0927_support;
        g0927_support = Reader._doc_link->descendents;
        for (START(g0927_support); NEXT(g0927);)
        { ClaireBoolean * g0928;
          { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(l);
              V_C= Kernel.cfalse;
              for (START(OBJECT(ClaireClass,g0927)->instances); NEXT(l);)
              if (OBJECT(Reader_doc_link,l)->src == (NULL))
               { PortObject * g0929 = use_as_output_port(f);
                princ_string(OBJECT(Reader_doc_item,l)->name);
                princ_string(((char*)" "));
                princ_string(OBJECT(Reader_doc_link,l)->oid);
                princ_string(((char*)"\n"));
                use_as_output_port(g0929);
                }
              }
            
            g0928=OBJECT(ClaireBoolean,V_C);}
          if (g0928 == CTRUE)
           { ;ClEnv->cHandle = loop_handle; break;}
          }
        }
      fclose_port1(f);
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: load_doc_links(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  load_doc_links_void1() { 
    
    GC_BIND;
    if (isdir_ask_string(getenv_string(((char*)"CLAIRE_DOCLINKS"))) == CTRUE)
     { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(x);
      bag *x_support;
      x_support = GC_OBJECT(list,entries_string1(GC_STRING(getenv_string(((char*)"CLAIRE_DOCLINKS"))),((char*)"*.links")));
      for (START(x_support); NEXT(x);)
      { GC_LOOP;
        { buffer * f = GC_OBJECT(buffer,fopen_string1(GC_STRING(_7_string(GC_STRING(getenv_string(((char*)"CLAIRE_DOCLINKS"))),string_v(x))),((char*)"r")));
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) f))) != Kernel.ctrue))
            { GC_LOOP;
              { char * l = GC_STRING(freadline_port(f));
                if ((CL_INT)LENGTH_STRING(l) > (CL_INT)0)
                 { list * g0930 = GC_OBJECT(list,explode_wildcard_string(l,((char*)"* *")));
                  char * n = string_v((*(g0930))[1]);
                  char * o = string_v((*(g0930))[2]);
                  { OID  g0931UU;
                    { Reader_doc_link * _CL_obj = ((Reader_doc_link *) GC_OBJECT(Reader_doc_link,new_object_class(Reader._doc_link)));
                      _void_(_CL_obj->name = n);
                      _void_(_CL_obj->oid = o);
                      _void_(_CL_obj->src = replace_string(string_v(x),((char*)".links"),((char*)".html")));
                      add_I_property(Kernel.instances,Reader._doc_link,11,_oid_(_CL_obj));
                      _void_(_CL_obj->documentation = string_v(CLREAD(slot,_at_property1(Reader.documentation,Reader._doc_link),DEFAULT)));
                      g0931UU = _oid_(_CL_obj);
                      }
                    nth_equal_hash_table1(OBJECT(Reader_hash_table,Reader.NAME_TO_ITEM_TABLE->value),_string_(n),g0931UU);
                    }
                  }
                }
              GC_UNLOOP;POP_SIGNAL;}
            }
          fclose_port1(f);
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: compare_items(e1:doc_entity,e2:doc_entity) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * compare_items_doc_entity1(Reader_doc_entity *e1,Reader_doc_entity *e2) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      Result = (((INHERIT(e1->isa,Reader._doc_method)) && 
          (INHERIT(e2->isa,Reader._doc_method))) ?
        ((equal_string(e1->name,e2->name) == CTRUE) ?
          _inf_integer(CLREAD(Reader_doc_method,e1,vars)->length,CLREAD(Reader_doc_method,e2,vars)->length) :
          _inf_any(GC_OID(_string_(lower_string(e1->name))),GC_OID(_string_(lower_string(e2->name)))) ) :
        _inf_any(GC_OID(_string_(lower_string(e1->name))),GC_OID(_string_(lower_string(e2->name)))) );
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: ordered_categories(_CL_obj:void) [NEW_ALLOC]
CL_EXPORT list * ordered_categories_void1() { 
    
    GC_BIND;
    { list *Result ;
      { list * l = list::empty(Reader._doc_category);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(g0932);
          bag *g0932_support;
          g0932_support = Reader._doc_section->descendents;
          for (START(g0932_support); NEXT(g0932);)
          { GC_LOOP;
            { ClaireBoolean * g0933;
              { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(sec);
                  V_C= Kernel.cfalse;
                  for (START(OBJECT(ClaireClass,g0932)->instances); NEXT(sec);)
                  { GC_LOOP;
                    if ((Reader._starexpl_doc_star->value != Kernel.ctrue) || 
                        (OBJECT(Reader_doc_section,sec)->exploit_ask == CTRUE))
                     { CL_INT loop_handle = ClEnv->cHandle;
                      ITERATE(cat);
                      for (START(OBJECT(Reader_doc_section,sec)->categories); NEXT(cat);)
                      if ((Reader._starexpl_doc_star->value != Kernel.ctrue) || 
                          ((OBJECT(Reader_doc_category,cat)->exploit_ask == CTRUE) || 
                            (OBJECT(Reader_doc_section,sec)->exploit_ask == CTRUE)))
                       l->addFast((OID)cat);
                      }
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                
                g0933=OBJECT(ClaireBoolean,V_C);}
              if (g0933 == CTRUE)
               { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        if (Reader._starexpl_doc_star->value != Kernel.ctrue)
         { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(g0934);
          bag *g0934_support;
          g0934_support = Reader._doc_category->descendents;
          for (START(g0934_support); NEXT(g0934);)
          { ClaireBoolean * g0935;
            { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(cat);
                V_C= Kernel.cfalse;
                for (START(OBJECT(ClaireClass,g0934)->instances); NEXT(cat);)
                if (OBJECT(Reader_doc_category,cat)->section == (NULL))
                 l->addFast((OID)cat);
                }
              
              g0935=OBJECT(ClaireBoolean,V_C);}
            if (g0935 == CTRUE)
             { ;ClEnv->cHandle = loop_handle; break;}
            }
          }
        Result = l;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: print_module(self:doc_entity) [0]
CL_EXPORT void  print_module_doc_entity1(Reader_doc_entity *self) { 
    ;POP_SIGNAL;}
  


// The c++ function for: make_alias(cat:doc_category,salias:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  make_alias_doc_category1(Reader_doc_category *cat,char *salias) { 
    
    GC_BIND;
    GC_OBJECT(list,cat->aliases)->addFast((OID)_string_(salias));
    add_ref_to_item_doc_item1(cat,salias);
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: make_category(scat:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT Reader_doc_category * make_category_string1(char *scat) { 
    
    GC_BIND;
    { Reader_doc_category *Result ;
      { OID  c = nth_hash_table1(OBJECT(Reader_hash_table,Reader.NAME_TO_ITEM_TABLE->value),_string_(scat));
        if (c != CNULL)
         { if (INHERIT(OWNER(c),Reader._doc_category))
           Result = OBJECT(Reader_doc_category,c);
          else { Reader_doc_category * c;
              { Reader_doc_category * _CL_obj = ((Reader_doc_category *) GC_OBJECT(Reader_doc_category,new_object_class(Reader._doc_category)));
                _void_(_CL_obj->name = scat);
                add_I_property(Kernel.instances,Reader._doc_category,11,_oid_(_CL_obj));
                _void_(_CL_obj->documentation = string_v(CLREAD(slot,_at_property1(Reader.documentation,Reader._doc_category),DEFAULT)));
                c = _CL_obj;
                }
              add_ref_to_item_doc_item1(c,scat);
              Result = c;
              }
            }
        else { Reader_doc_category * c;
            { Reader_doc_category * _CL_obj = ((Reader_doc_category *) GC_OBJECT(Reader_doc_category,new_object_class(Reader._doc_category)));
              _void_(_CL_obj->name = scat);
              add_I_property(Kernel.instances,Reader._doc_category,11,_oid_(_CL_obj));
              _void_(_CL_obj->documentation = string_v(CLREAD(slot,_at_property1(Reader.documentation,Reader._doc_category),DEFAULT)));
              c = _CL_obj;
              }
            add_ref_to_item_doc_item1(c,scat);
            Result = c;
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: make_section(cat:doc_category,ssec:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT]
CL_EXPORT Reader_doc_category * make_section_doc_category1(Reader_doc_category *cat,char *ssec) { 
    { Reader_doc_category *Result ;
      { Reader_doc_section * sec = make_section_string1(ssec);
        update_property(Reader.section,
          cat,
          6,
          Kernel._object,
          _oid_(sec));
        Result = cat;
        }
      POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: make_section(ssec:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT Reader_doc_section * make_section_string1(char *ssec) { 
    
    GC_BIND;
    { Reader_doc_section *Result ;
      { OID  c = nth_hash_table1(OBJECT(Reader_hash_table,Reader.NAME_TO_ITEM_TABLE->value),_string_(ssec));
        if (c != CNULL)
         { if (INHERIT(OWNER(c),Reader._doc_section))
           Result = OBJECT(Reader_doc_section,c);
          else { Reader_doc_section * s;
              { Reader_doc_section * _CL_obj = ((Reader_doc_section *) GC_OBJECT(Reader_doc_section,new_object_class(Reader._doc_section)));
                _void_(_CL_obj->name = ssec);
                add_I_property(Kernel.instances,Reader._doc_section,11,_oid_(_CL_obj));
                _void_(_CL_obj->documentation = string_v(CLREAD(slot,_at_property1(Reader.documentation,Reader._doc_section),DEFAULT)));
                s = _CL_obj;
                }
              nth_equal_hash_table1(OBJECT(Reader_hash_table,Reader.NAME_TO_ITEM_TABLE->value),_string_(ssec),_oid_(s));
              Result = s;
              }
            }
        else { Reader_doc_section * s;
            { Reader_doc_section * _CL_obj = ((Reader_doc_section *) GC_OBJECT(Reader_doc_section,new_object_class(Reader._doc_section)));
              _void_(_CL_obj->name = ssec);
              add_I_property(Kernel.instances,Reader._doc_section,11,_oid_(_CL_obj));
              _void_(_CL_obj->documentation = string_v(CLREAD(slot,_at_property1(Reader.documentation,Reader._doc_section),DEFAULT)));
              s = _CL_obj;
              }
            nth_equal_hash_table1(OBJECT(Reader_hash_table,Reader.NAME_TO_ITEM_TABLE->value),_string_(ssec),_oid_(s));
            Result = s;
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: make_doc_item(x:any,sdoc:string,cat:string,xl:boolean) [0]
CL_EXPORT void  make_doc_item_any1(OID x,char *sdoc,char *cat,ClaireBoolean *xl) { 
    ;POP_SIGNAL;}
  


// The c++ function for: make_doc_item(x:Defmethod,sdoc:string,cat:string,xl:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  make_doc_item_Defmethod1(Defmethod *x,char *sdoc,char *cat,ClaireBoolean *xl) { 
    
    GC_BIND;
    if (Reader._starexpl_doc_star->value != Kernel.ctrue)
     { symbol * idnt = x->arg->selector->name;
      Reader_doc_method * item;
      { Reader_doc_method * _CL_obj = ((Reader_doc_method *) GC_OBJECT(Reader_doc_method,new_object_class(Reader._doc_method)));
        _void_(_CL_obj->source = _oid_(x->arg->selector));
        _void_(_CL_obj->name = idnt->name);
        _void_(_CL_obj->xl_ask = xl);
        _void_(_CL_obj->ident = idnt);
        _void_(_CL_obj->src_location = nth_hash_table1(OBJECT(Reader_hash_table,Reader.ITEM_LOCATION->value),_oid_(x)));
        _void_(_CL_obj->documentation = sdoc);
        add_I_property(Kernel.instances,Reader._doc_method,11,_oid_(_CL_obj));
        item = _CL_obj;
        }
      add_ref_to_item_doc_item1(item,item->name);
      if ((CL_INT)LENGTH_STRING(cat) > (CL_INT)0)
       update_property(Reader.category,
        item,
        8,
        Kernel._object,
        _oid_(make_category_string1(cat)));
      else update_property(Reader.category,
          item,
          8,
          Kernel._object,
          _oid_(make_category_string1(GC_STRING(string_v(Reader.MODULE_NAME->value)))));
        if (LENGTH_STRING(sdoc) == 0)
       { GC_OBJECT(list,item->category->entity_names)->addFast((OID)_string_(item->name));
        GC_OBJECT(list,item->category->aliases)->addFast((OID)_string_(item->name));
        }
      _void_(item->mrange = x->set_arg);
      update_property(Kernel.inline_ask,
        item,
        11,
        Kernel._object,
        GC_OID(x->inline_ask));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(v);
        bag *v_support;
        v_support = GC_OBJECT(list,x->arg->args);
        for (START(v_support); NEXT(v);)
        { GC_LOOP;
          if (v != _oid_(ClEnv))
           { GC_OBJECT(list,item->vars)->addFast((OID)_string_(OBJECT(Variable,v)->pname->name));
            GC_OBJECT(list,item->var_ranges)->addFast((OID)GC_OID((*Kernel.range)(v)));
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      ;}
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: make_doc_item(x:Defarray,sdoc:string,cat:string,xl:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  make_doc_item_Defarray1(Defarray *x,char *sdoc,char *cat,ClaireBoolean *xl) { 
    
    GC_BIND;
    if (Reader._starexpl_doc_star->value != Kernel.ctrue)
     { symbol * idnt = extract_symbol_any((*(x->arg->args))[1]);
      Reader_doc_table * item;
      { Reader_doc_table * _CL_obj = ((Reader_doc_table *) GC_OBJECT(Reader_doc_table,new_object_class(Reader._doc_table)));
        _void_(_CL_obj->source = _oid_(x));
        _void_(_CL_obj->name = idnt->name);
        _void_(_CL_obj->xl_ask = xl);
        _void_(_CL_obj->ident = idnt);
        _void_(_CL_obj->src_location = nth_hash_table1(OBJECT(Reader_hash_table,Reader.ITEM_LOCATION->value),_oid_(x)));
        _void_(_CL_obj->documentation = sdoc);
        add_I_property(Kernel.instances,Reader._doc_table,11,_oid_(_CL_obj));
        item = _CL_obj;
        }
      add_ref_to_item_doc_item1(item,item->name);
      if ((CL_INT)LENGTH_STRING(cat) > (CL_INT)0)
       update_property(Reader.category,
        item,
        8,
        Kernel._object,
        _oid_(make_category_string1(cat)));
      else update_property(Reader.category,
          item,
          8,
          Kernel._object,
          _oid_(make_category_string1(GC_STRING(string_v(Reader.MODULE_NAME->value)))));
        if (LENGTH_STRING(sdoc) == 0)
       { GC_OBJECT(list,item->category->entity_names)->addFast((OID)_string_(item->name));
        GC_OBJECT(list,item->category->aliases)->addFast((OID)_string_(item->name));
        }
      _void_(item->trange = x->set_arg);
      _void_(item->tbody = x->body);
      ;}
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: make_doc_item(x:Defclass,sdoc:string,cat:string,xl:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  make_doc_item_Defclass1(Defclass *x,char *sdoc,char *cat,ClaireBoolean *xl) { 
    
    GC_BIND;
    if (Reader._starexpl_doc_star->value != Kernel.ctrue)
     { symbol * idnt = x->ident;
      Reader_doc_class * item;
      { Reader_doc_class * _CL_obj = ((Reader_doc_class *) GC_OBJECT(Reader_doc_class,new_object_class(Reader._doc_class)));
        _void_(_CL_obj->source = get_symbol(idnt));
        _void_(_CL_obj->name = idnt->name);
        _void_(_CL_obj->xl_ask = xl);
        _void_(_CL_obj->ident = idnt);
        _void_(_CL_obj->src_location = nth_hash_table1(OBJECT(Reader_hash_table,Reader.ITEM_LOCATION->value),_oid_(x)));
        _void_(_CL_obj->documentation = sdoc);
        add_I_property(Kernel.instances,Reader._doc_class,11,_oid_(_CL_obj));
        item = _CL_obj;
        }
      add_ref_to_item_doc_item1(item,item->name);
      if ((CL_INT)LENGTH_STRING(cat) > (CL_INT)0)
       update_property(Reader.category,
        item,
        8,
        Kernel._object,
        _oid_(make_category_string1(cat)));
      else update_property(Reader.category,
          item,
          8,
          Kernel._object,
          _oid_(make_category_string1(GC_STRING(string_v(Reader.MODULE_NAME->value)))));
        if (LENGTH_STRING(sdoc) == 0)
       { GC_OBJECT(list,item->category->entity_names)->addFast((OID)_string_(item->name));
        GC_OBJECT(list,item->category->aliases)->addFast((OID)_string_(item->name));
        }
      _void_(item->superclass = _oid_(x->arg));
      ;}
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: make_doc_item(x:Defobj,sdoc:string,cat:string,xl:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  make_doc_item_Defobj1(Defobj *x,char *sdoc,char *cat,ClaireBoolean *xl) { 
    
    GC_BIND;
    if (Reader._starexpl_doc_star->value != Kernel.ctrue)
     { symbol * idnt = x->ident;
      OID  val = get_symbol(idnt);
      if ((val != CNULL) && 
          ((_inf_equal_type(OWNER(val),Kernel._property) == CTRUE) && 
            (((*Kernel.open)(val) == ((OID)1)) || 
                ((*Kernel.open)(val) == ((OID)3)))))
       { Reader_doc_interface * item;
        { Reader_doc_interface * _CL_obj = ((Reader_doc_interface *) GC_OBJECT(Reader_doc_interface,new_object_class(Reader._doc_interface)));
          _void_(_CL_obj->source = val);
          _void_(_CL_obj->xl_ask = xl);
          _void_(_CL_obj->name = idnt->name);
          _void_(_CL_obj->ident = idnt);
          _void_(_CL_obj->src_location = nth_hash_table1(OBJECT(Reader_hash_table,Reader.ITEM_LOCATION->value),_oid_(x)));
          _void_(_CL_obj->documentation = sdoc);
          add_I_property(Kernel.instances,Reader._doc_interface,11,_oid_(_CL_obj));
          item = _CL_obj;
          }
        add_ref_to_item_doc_item1(item,item->name);
        if ((CL_INT)LENGTH_STRING(cat) > (CL_INT)0)
         update_property(Reader.category,
          item,
          8,
          Kernel._object,
          _oid_(make_category_string1(cat)));
        else update_property(Reader.category,
            item,
            8,
            Kernel._object,
            _oid_(make_category_string1(GC_STRING(string_v(Reader.MODULE_NAME->value)))));
          if (LENGTH_STRING(sdoc) == 0)
         { GC_OBJECT(list,item->category->entity_names)->addFast((OID)_string_(item->name));
          GC_OBJECT(list,item->category->aliases)->addFast((OID)_string_(item->name));
          }
        _void_(item->arg = _oid_(x->arg));
        _void_(item->args = x->args);
        ;}
      else if (x->arg == Core._global_variable)
       { Reader_doc_global * item;
        { Reader_doc_global * _CL_obj = ((Reader_doc_global *) GC_OBJECT(Reader_doc_global,new_object_class(Reader._doc_global)));
          _void_(_CL_obj->source = _oid_(x));
          _void_(_CL_obj->xl_ask = xl);
          _void_(_CL_obj->name = idnt->name);
          _void_(_CL_obj->ident = idnt);
          _void_(_CL_obj->src_location = nth_hash_table1(OBJECT(Reader_hash_table,Reader.ITEM_LOCATION->value),_oid_(x)));
          _void_(_CL_obj->documentation = sdoc);
          add_I_property(Kernel.instances,Reader._doc_global,11,_oid_(_CL_obj));
          item = _CL_obj;
          }
        add_ref_to_item_doc_item1(item,item->name);
        if ((CL_INT)LENGTH_STRING(cat) > (CL_INT)0)
         update_property(Reader.category,
          item,
          8,
          Kernel._object,
          _oid_(make_category_string1(cat)));
        else update_property(Reader.category,
            item,
            8,
            Kernel._object,
            _oid_(make_category_string1(GC_STRING(string_v(Reader.MODULE_NAME->value)))));
          if (LENGTH_STRING(sdoc) == 0)
         { GC_OBJECT(list,item->category->entity_names)->addFast((OID)_string_(item->name));
          GC_OBJECT(list,item->category->aliases)->addFast((OID)_string_(item->name));
          }
        _void_(item->value = (*(OBJECT(bag,(*Core.args)(GC_OID((*(x->args))[2])))))[2]);
        _void_(item->grange = (*(OBJECT(bag,(*Core.args)(GC_OID((*(x->args))[1])))))[2]);
        _void_(item->constant_ask = equal(item->grange,_oid_(Kernel.emptySet)));
        ;}
      }
    GC_UNBIND; POP_SIGNAL;}
  


// **********************************************************************
// *   Part 1: loading files                                            *
// **********************************************************************
// The c++ function for: load_items(self:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT list * load_items_string1(char *self) { 
    
    GC_RESERVE(7);  // v3.3.39 optim !
    reader_push_void1();
    _void_(Reader.reader->index = 0);
    _void_(Reader.reader->maxstack = 0);
    _void_(Reader.reader->external = self);
    { list *Result ;
      { PortObject * f = GC_OBJECT(PortObject,fopen_source_string1(self));
        OID  base_name = GC_OID(last_list(explode_string(self,GC_STRING(string_v(Core._starfs_star->value)))));
        list * res = list::empty(Kernel._any);
        CL_INT  start = ClEnv->base;
        CL_INT  top = ClEnv->index;
        OID  _staritem_star = CNULL;
        ClaireBoolean * br_ask = CFALSE;
        char * insert_href = ((char*)"");
        ClaireBoolean * ineval_ask = CFALSE;
        (ClEnv->base= ((OID)top));
        _void_(Reader.reader->fromp = f);
        _void_(Reader.reader->toplevel = CFALSE);
        _staritem_star= (GC_OID(readblock_port(f)));
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while ((equal(_staritem_star,Core._eof->value) != CTRUE))
          { GC_LOOP;
            _void_(f->firstc = integer_I_char(_char_(((unsigned char)' '))));
            (ClEnv->index= ((OID)((CL_INT)top+(CL_INT)((CL_INT)Reader.reader->maxstack+(CL_INT)1))));
            res->addFast((OID)_staritem_star);
            skipc_meta_reader(Reader.reader);
            { tuple * loc = GC_OBJECT(tuple,get_location_port1(f)->copyIfNeeded());
              GC__OID(_staritem_star = readblock_port(f), 1);
              if (Kernel._string == OWNER(_staritem_star))
               { GC__OID(_staritem_star = _string_(rtrim_string(string_v(_staritem_star))), 2);
                { char * href;
                  { { print_in_string_void();
                      princ_string(((char*)"\\a\\href='claire://source-edit?file="));
                      princ_string(url_encode_string(string_v((*(loc))[1])));
                      princ_string(((char*)"&line="));
                      princ_integer(((CL_INT)(*(loc))[2]));
                      princ_string(((char*)"&editor="));
                      princ_string(url_encode_string(GC_STRING(getenv_string(((char*)"WCL_EDITOR")))));
                      princ_string(((char*)"' ["));
                      princ_string(string_v(base_name));
                      princ_string(((char*)":"));
                      print_any((*(loc))[2]);
                      princ_string(((char*)"]\\/a "));
                      href = end_of_string_void();
                      }
                    GC_STRING(href);}
                  if ((CL_INT)find_string2(string_v(_staritem_star),((char*)"@code")) > (CL_INT)0)
                   { char * cde = GC_STRING(freadline_port1(f,((char*)"// @code\n")));
                    GC__ANY(loc = get_location_port1(f)->copyIfNeeded(), 3);
                    unget_port1(f,cde);
                    res->addFast((OID)_string_(((char*)"\\br \\i \\b - The following code is part of the source - \\/b \\/i")));
                    if ((OBJECT(ClaireBoolean,Reader._stardoc_links_star->value)) == CTRUE)
                     res->addFast((OID)GC_OID(_string_(append_string(((char*)"\\br \\b [dump]\\/b "),href))));
                    res->addFast((OID)_string_(((char*)"\\code")));
                    { list * exl = GC_OBJECT(list,explode_string(cde,((char*)"\n")));
                      { CL_INT loop_handle = ClEnv->cHandle;
                        while (((exl->length != 0) && 
                            (space_ask_string(string_v((*(exl))[1])) == CTRUE)))
                        { skip_list(exl,1);
                          POP_SIGNAL;}
                        }
                      { CL_INT loop_handle = ClEnv->cHandle;
                        while (((exl->length != 0) && 
                            (space_ask_string(string_v((*(exl))[exl->length])) == CTRUE)))
                        { shrink_list(exl,((CL_INT)exl->length-(CL_INT)1));
                          POP_SIGNAL;}
                        }
                      { CL_INT loop_handle = ClEnv->cHandle;
                        ITERATE(x);
                        for (START(exl); NEXT(x);)
                        if (match_wildcard_ask_string(string_v(x),((char*)"//*")) != CTRUE)
                         res->addFast((OID)x);
                        }
                      }
                    res->addFast((OID)_string_(((char*)"\\/code")));
                    if ((OBJECT(ClaireBoolean,Reader._stardoc_links_star->value)) == CTRUE)
                     { OID  g0936UU;
                      { { print_in_string_void();
                          princ_string(((char*)"\\b [/dump]\\/b \\a\\href='claire://source-edit?file="));
                          princ_string(url_encode_string(string_v((*(loc))[1])));
                          princ_string(((char*)"&line="));
                          princ_integer(((CL_INT)(*(loc))[2]));
                          princ_string(((char*)"&editor="));
                          princ_string(url_encode_string(GC_STRING(getenv_string(((char*)"WCL_EDITOR")))));
                          princ_string(((char*)"' ["));
                          princ_string(string_v(base_name));
                          princ_string(((char*)":"));
                          print_any((*(loc))[2]);
                          princ_string(((char*)"]\\/a "));
                          g0936UU = _string_(end_of_string_void());
                          }
                        GC_OID(g0936UU);}
                      res->addFast((OID)g0936UU);
                      }
                    res->addFast((OID)_string_(((char*)"@cat")));
                    _staritem_star= (_string_(((char*)"")));
                    }
                  else if (((CL_INT)find_string2(string_v(_staritem_star),((char*)"@cat")) > (CL_INT)0) && 
                      (equal_string(trim_string(GC_STRING(string_v((*(explode_wildcard_string(string_v(_staritem_star),((char*)"*@cat*"))))[2]))),((char*)"")) != CTRUE))
                   { br_ask= (CFALSE);
                    GC__STRING(insert_href = append_string(((char*)"\\b [cat]\\/b "),href), 4);
                    }
                  else if ((CL_INT)find_string2(string_v(_staritem_star),((char*)"@cat")) > (CL_INT)0)
                   { br_ask= (CFALSE);
                    if ((OBJECT(ClaireBoolean,Reader._stardoc_links_star->value)) == CTRUE)
                     res->addFast((OID)GC_OID(_string_(append_string(((char*)"\\br \\b [/cat]\\/b "),href))));
                    }
                  else if ((CL_INT)find_string2(string_v(_staritem_star),((char*)"@doc")) > (CL_INT)0)
                   { br_ask= (CFALSE);
                    GC__STRING(insert_href = append_string(((char*)"\\b [doc]\\/b "),href), 5);
                    }
                  else if (((CL_INT)LENGTH_STRING(insert_href) > (CL_INT)0) && 
                      ((CL_INT)LENGTH_STRING(string_v(_staritem_star)) > (CL_INT)0))
                   { if ((OBJECT(ClaireBoolean,Reader._stardoc_links_star->value)) == CTRUE)
                     res->addFast((OID)_string_(insert_href));
                    br_ask= (CFALSE);
                    insert_href= (((char*)""));
                    }
                  else if (br_ask == CTRUE)
                   { br_ask= (CFALSE);
                    if ((OBJECT(ClaireBoolean,Reader._stardoc_links_star->value)) == CTRUE)
                     res->addFast((OID)_string_(href));
                    }
                  if (match_wildcard_ask_string(string_v(_staritem_star),((char*)"*\\br")) == CTRUE)
                   br_ask= (CTRUE);
                  else if ((match_wildcard_ask_string(string_v(_staritem_star),((char*)"*\\/code *")) == CTRUE) || 
                      (match_wildcard_ask_string(string_v(_staritem_star),((char*)"*\\/code")) == CTRUE))
                   { br_ask= (CFALSE);
                    GC__OID(_staritem_star = _string_(trim_string(string_v(_staritem_star))), 6);
                    GC__STRING(insert_href = append_string(((char*)"\\br \\b [/code]\\/b "),href), 7);
                    }
                  else if ((match_wildcard_ask_string(string_v(_staritem_star),((char*)"*\\code *")) == CTRUE) || 
                      (match_wildcard_ask_string(string_v(_staritem_star),((char*)"*\\code")) == CTRUE))
                   { br_ask= (CFALSE);
                    if ((OBJECT(ClaireBoolean,Reader._stardoc_links_star->value)) == CTRUE)
                     res->addFast((OID)GC_OID(_string_(append_string(((char*)"\\br \\b [code]\\/b "),href))));
                    }
                  }
                }
              else { insert_href= (((char*)""));
                  ineval_ask= (CFALSE);
                  nth_equal_hash_table1(OBJECT(Reader_hash_table,Reader.ITEM_LOCATION->value),_staritem_star,_oid_(loc));
                  }
                }
            GC_UNLOOP;POP_SIGNAL;}
          }
        reader_pop_void1();
        (ClEnv->base= ((OID)start));
        (ClEnv->index= ((OID)top));
        fclose_port1(f);
        Result = res;
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: self_print(self:bad_eval) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  self_print_bad_eval1_Reader(Reader_bad_eval *self) { 
    
    GC_BIND;
    print_any(GC_OID(_oid_(self->src)));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: load_file_items(self:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  load_file_items_string1(char *self) { 
    
    GC_RESERVE(11);  // v3.3.39 optim !
    { list * items = GC_OBJECT(list,load_items_string1(self));
      CL_INT  len = items->length;
      CL_INT  i = 1;
      char * cursec = ((char*)"");
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)i < (CL_INT)len))
        { GC_LOOP;
          { OID  x = (*(items))[i];
            if (Kernel._string == OWNER(x))
             { if (match_wildcard_ask_string(string_v(x),((char*)"*@@title *")) == CTRUE)
               { list * ex = GC_OBJECT(list,explode_wildcard_string(string_v(x),((char*)"*@@title *")));
                (Reader.DOC_TITLE->value= _string_(trim_string(string_v((*(ex))[2]))));
                (Reader.MODULE_NAME->value= Reader.DOC_TITLE->value);
                }
              else if (match_wildcard_ask_string(string_v(x),((char*)"*@@sec *")) == CTRUE)
               { list * ex = GC_OBJECT(list,explode_wildcard_string(string_v(x),((char*)"*@@sec *")));
                GC__STRING(cursec = trim_string(string_v((*(ex))[2])), 1);
                _void_(make_section_string1(cursec)->exploit_ask = _sup_integer(find_string2(string_v((*(ex))[1]),((char*)"@exploitation")),0));
                }
              else if (match_wildcard_ask_string(string_v(x),((char*)"*@@cat *")) == CTRUE)
               { list * ex = GC_OBJECT(list,explode_wildcard_string(string_v(x),((char*)"*@@cat *")));
                list * al = GC_OBJECT(list,explode_string(string_v((*(ex))[2]),((char*)"@@")));
                Reader_doc_category * ocat = make_category_string1(GC_STRING(trim_string(string_v((*(al))[1]))));
                _void_(ocat->xl_ask = _sup_integer(find_string2(string_v((*(ex))[1]),((char*)"@xl")),0));
                _void_(ocat->exploit_ask = _sup_integer(find_string2(string_v((*(ex))[1]),((char*)"@exploitation")),0));
                if ((CL_INT)al->length > (CL_INT)1)
                 { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(a);
                  bag *a_support;
                  a_support = GC_OBJECT(list,explode_string(string_v((*(al))[2]),((char*)" ")));
                  for (START(a_support); NEXT(a);)
                  { GC_LOOP;
                    if ((CL_INT)LENGTH_STRING(trim_string(string_v(a))) > (CL_INT)0)
                     make_alias_doc_category1(ocat,GC_STRING(trim_string(string_v(a))));
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                make_section_doc_category1(ocat,cursec);
                }
              else if ((CL_INT)find_string2(string_v(x),((char*)"@cat")) > (CL_INT)0)
               { CL_INT  n = find_string2(string_v(x),((char*)"@cat"));
                CL_INT  nxl;
                { CL_INT  n = find_string2(string_v(x),((char*)"@xl"));
                  nxl = (((CL_INT)n > (CL_INT)0) ?
                    ((CL_INT)n+(CL_INT)4) :
                    -1 );
                  }
                CL_INT  nexpl;
                { CL_INT  n = find_string2(string_v(x),((char*)"@exploitation"));
                  nexpl = (((CL_INT)n > (CL_INT)0) ?
                    ((CL_INT)n+(CL_INT)14) :
                    -1 );
                  }
                char * cat = GC_STRING(trim_string(GC_STRING(substring_string(string_v(x),max_integer1(((CL_INT)n+(CL_INT)4),(((CL_INT)nexpl <= (CL_INT)nxl) ?
                  nxl :
                  nexpl )),LENGTH_STRING(string_v(x))))));
                Reader_doc_category * ocat = make_category_string1(cat);
                char * doc = ((char*)"");
                OID  edit = nth_hash_table1(OBJECT(Reader_hash_table,Reader.ITEM_LOCATION->value),x);
                ++i;
                _void_(ocat->src_location = edit);
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  while ((((CL_INT)i < (CL_INT)len) && 
                      ((Kernel._string == OWNER((*(items))[i])) && 
                        (_sup_integer(find_string2(string_v((*(items))[i]),((char*)"@cat")),0) != CTRUE))))
                  { GC_LOOP;
                    { OID  xx = (*(items))[i];
                      CL_INT  si = find_string2(string_v(xx),((char*)"@section"));
                      CL_INT  sa = find_string2(string_v(xx),((char*)"@alias"));
                      CL_INT  sn = find_string2(string_v(xx),((char*)"@name"));
                      if ((CL_INT)find_string2(string_v(xx),((char*)"@eval")) > (CL_INT)0)
                       { char * cde = ((char*)"(");
                        ++i;
                        { CL_INT loop_handle = ClEnv->cHandle;
                          OID gc_local;
                          while ((((CL_INT)i < (CL_INT)len) && 
                              ((Kernel._string == OWNER((*(items))[i])) && 
                                (_sup_integer(find_string2(string_v((*(items))[i]),((char*)"@eval")),0) != CTRUE))))
                          { GC_LOOP;
                            GC__STRING(cde = append_string(cde,GC_STRING(string_v((*Kernel._7_plus)((*(items))[i],
                              _string_(((char*)"\n")))))), 2);
                            ++i;
                            GC_UNLOOP;POP_SIGNAL;}
                          }
                        { blob * b = GC_OBJECT(blob,blob_I_void1());
                          PortObject * old = use_as_output_port(b);
                          { ClaireHandler c_handle = ClaireHandler();
                            if ERROR_IN 
                            { eval_any(GC_OID(read_string(GC_STRING(append_string(cde,((char*)")"))))));
                              ERROR_FREE;}
                            else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                            { c_handle.catchIt();{ Reader_bad_eval * _CL_obj = ((Reader_bad_eval *) GC_OBJECT(Reader_bad_eval,new_object_class(Reader._bad_eval)));
                                _void_(_CL_obj->src = ClEnv->exception_I);
                                close_exception(_CL_obj);
                                }
                              }
                            else PREVIOUS_HANDLER;}
                          use_as_output_port(old);
                          GC__STRING(doc = append_string(doc,GC_STRING(string_I_blob1(b))), 3);
                          fclose_port1(b);
                          }
                        }
                      else if ((CL_INT)si > (CL_INT)0)
                       { char * sec = GC_STRING(trim_string(GC_STRING(string_v((*Kernel.substring)(xx,
                          ((OID)((CL_INT)si+(CL_INT)9)),
                          GC_OID((*Kernel.length)(xx)))))));
                        make_section_doc_category1(ocat,sec);
                        }
                      else if ((CL_INT)sn > (CL_INT)0)
                       { char * nm = GC_STRING(trim_string(GC_STRING(string_v((*Kernel.substring)(xx,
                          ((OID)((CL_INT)sn+(CL_INT)6)),
                          GC_OID((*Kernel.length)(xx)))))));
                        _void_(ocat->aname = nm);
                        }
                      else if ((CL_INT)sa > (CL_INT)0)
                       { CL_INT loop_handle = ClEnv->cHandle;
                        OID gc_local;
                        ITERATE(a);
                        bag *a_support;
                        a_support = GC_OBJECT(list,explode_string(GC_STRING(string_v((*Kernel.substring)(xx,
                          ((OID)((CL_INT)sa+(CL_INT)7)),
                          GC_OID((*Kernel.length)(xx))))),((char*)" ")));
                        for (START(a_support); NEXT(a);)
                        { GC_LOOP;
                          if ((CL_INT)LENGTH_STRING(string_v(a)) > (CL_INT)0)
                           make_alias_doc_category1(ocat,GC_STRING(trim_string(string_v(a))));
                          GC_UNLOOP; POP_SIGNAL;}
                        }
                      else { if ((CL_INT)LENGTH_STRING(doc) > (CL_INT)0)
                           GC__STRING(doc = append_string(doc,((char*)"\n")), 4);
                          GC__STRING(doc = append_string(doc,string_v(xx)), 5);
                          }
                        ++i;
                      }
                    GC_UNLOOP;POP_SIGNAL;}
                  }
                _void_(ocat->xl_ask = _sup_integer(nxl,0));
                _void_(ocat->exploit_ask = _sup_integer(nexpl,0));
                if ((equal_string(ocat->documentation,((char*)"")) != CTRUE) && 
                    ((CL_INT)LENGTH_STRING(doc) > (CL_INT)0))
                 _void_(ocat->documentation = append_string(GC_STRING(ocat->documentation),((char*)" \\br ")));
                _void_(ocat->documentation = append_string(GC_STRING(ocat->documentation),doc));
                }
              else if ((CL_INT)find_string2(string_v(x),((char*)"@copyright")) > (CL_INT)0)
               { CL_INT  n = find_string2(string_v(x),((char*)"@copyright"));
                char * cr = GC_STRING(trim_string(GC_STRING(substring_string(string_v(x),((CL_INT)n+(CL_INT)11),LENGTH_STRING(string_v(x))))));
                Reader_doc_copyright * _CL_obj = ((Reader_doc_copyright *) GC_OBJECT(Reader_doc_copyright,new_object_class(Reader._doc_copyright)));
                _void_(_CL_obj->documentation = cr);
                add_I_property(Kernel.instances,Reader._doc_copyright,11,_oid_(_CL_obj));
                ;}
              else if ((CL_INT)find_string2(string_v(x),((char*)"@depoptions")) > (CL_INT)0)
               (Reader.DEPOPTIONS->value= Kernel.ctrue);
              else if ((CL_INT)find_string2(string_v(x),((char*)"@author")) > (CL_INT)0)
               { CL_INT  n = find_string2(string_v(x),((char*)"@author"));
                char * cr = GC_STRING(trim_string(GC_STRING(substring_string(string_v(x),((CL_INT)n+(CL_INT)8),LENGTH_STRING(string_v(x))))));
                Reader_doc_author * _CL_obj = ((Reader_doc_author *) GC_OBJECT(Reader_doc_author,new_object_class(Reader._doc_author)));
                _void_(_CL_obj->documentation = cr);
                add_I_property(Kernel.instances,Reader._doc_author,11,_oid_(_CL_obj));
                ;}
              else if ((CL_INT)find_string2(string_v(x),((char*)"@preamble")) > (CL_INT)0)
               { char * doc = ((char*)"");
                ++i;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  while ((((CL_INT)i < (CL_INT)len) && 
                      ((Kernel._string == OWNER((*(items))[i])) && 
                        (_sup_integer(find_string2(string_v((*(items))[i]),((char*)"@preamble")),0) != CTRUE))))
                  { GC_LOOP;
                    if ((CL_INT)LENGTH_STRING(doc) > (CL_INT)0)
                     GC__STRING(doc = append_string(doc,((char*)"\n")), 6);
                    GC__STRING(doc = append_string(doc,string_v((*(items))[i])), 7);
                    ++i;
                    GC_UNLOOP;POP_SIGNAL;}
                  }
                if (boolean_I_any(_oid_(Reader._doc_preamble->instances)) != CTRUE)
                 { Reader_doc_preamble * _CL_obj = ((Reader_doc_preamble *) GC_OBJECT(Reader_doc_preamble,new_object_class(Reader._doc_preamble)));
                  add_I_property(Kernel.instances,Reader._doc_preamble,11,_oid_(_CL_obj));
                  _void_(_CL_obj->documentation = string_v(CLREAD(slot,_at_property1(Reader.documentation,Reader._doc_preamble),DEFAULT)));
                  ;}
                { Reader_doc_preamble * g0939 = OBJECT(Reader_doc_preamble,(*(Reader._doc_preamble->instances))[1]);
                  _void_(g0939->documentation = append_string(GC_STRING(g0939->documentation),doc));
                  }
                }
              else if ((CL_INT)find_string2(string_v(x),((char*)"@presentation")) > (CL_INT)0)
               { char * doc = ((char*)"");
                ++i;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  while ((((CL_INT)i < (CL_INT)len) && 
                      ((Kernel._string == OWNER((*(items))[i])) && 
                        (_sup_integer(find_string2(string_v((*(items))[i]),((char*)"@presentation")),0) != CTRUE))))
                  { GC_LOOP;
                    if ((CL_INT)LENGTH_STRING(doc) > (CL_INT)0)
                     GC__STRING(doc = append_string(doc,((char*)"\n")), 8);
                    GC__STRING(doc = append_string(doc,string_v((*(items))[i])), 9);
                    ++i;
                    GC_UNLOOP;POP_SIGNAL;}
                  }
                (Reader.SHORT_PRESENTATION->value= _string_(append_string(GC_STRING(string_v(Reader.SHORT_PRESENTATION->value)),doc)));
                }
              else if ((CL_INT)find_string2(string_v(x),((char*)"@doc")) > (CL_INT)0)
               { CL_INT  n = find_string2(string_v(x),((char*)"@doc"));
                CL_INT  nxl = find_string2(string_v(x),((char*)"@xl"));
                char * cat = GC_STRING(trim_string(GC_STRING(substring_string(string_v(x),(((CL_INT)((CL_INT)nxl+(CL_INT)4) <= (CL_INT)((CL_INT)n+(CL_INT)5)) ?
                  ((CL_INT)n+(CL_INT)5) :
                  ((CL_INT)nxl+(CL_INT)4) ),LENGTH_STRING(string_v(x))))));
                char * doc = ((char*)"");
                ++i;
                { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  while ((((CL_INT)i < (CL_INT)len) && 
                      (Kernel._string == OWNER((*(items))[i]))))
                  { GC_LOOP;
                    if ((CL_INT)LENGTH_STRING(doc) > (CL_INT)0)
                     GC__STRING(doc = append_string(doc,((char*)"\n")), 10);
                    GC__STRING(doc = append_string(doc,string_v((*(items))[i])), 11);
                    ++i;
                    GC_UNLOOP;POP_SIGNAL;}
                  }
                (*Reader.make_doc_item)((*(items))[i],
                  _string_(doc),
                  _string_(cat),
                  _oid_(_sup_integer(nxl,0)));
                }
              }
            else if ((OBJECT(ClaireBoolean,Reader._starcode_doc_star->value)) == CTRUE)
             (*Reader.make_doc_item)(x,
              _string_(((char*)"")),
              _string_(((char*)"Undocumented")),
              Kernel.cfalse);
            ++i;
            }
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// **********************************************************************
// *   Part 1: generator options                                        *
// **********************************************************************
// The c++ function for: option_respond(opt:{"-export-doc-links"},l:list[string]) [0]
CL_EXPORT void  option_respond_string51_Reader(char *opt,list *l) { 
    (Reader._staronly_doc_links_star->value= Kernel.ctrue);
    POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-doclink"},l:list[string]) [0]
CL_EXPORT void  option_respond_string52_Reader(char *opt,list *l) { 
    (Reader._stardoc_links_star->value= Kernel.ctrue);
    POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-onefile"},l:list[string]) [0]
CL_EXPORT void  option_respond_string53_Reader(char *opt,list *l) { 
    (Reader._starone_file_star->value= Kernel.ctrue);
    POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-categories"},l:list[string]) [0]
CL_EXPORT void  option_respond_string54_Reader(char *opt,list *l) { 
    (Reader._starper_cat_file_star->value= Kernel.ctrue);
    POP_SIGNAL;}
  


// The c++ function for: option_respond(opt:{"-exploitationdoc", "-codedoc", "-apidoc"},l:list[string]) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  option_respond_string55_Reader(char *opt,list *l) { 
    
    GC_BIND;
    { OID  smod = GC_OID(last_list(explode_string(GC_STRING(pwd_void()),GC_STRING(string_v(Core._starfs_star->value)))));
      if (isfile_ask_string(((char*)"init.cl")) == CTRUE)
       load_string(((char*)"init"));
      else if (boolean_I_any(_oid_(l)) != CTRUE)
       close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
      else { smod= ((*(l))[1]);
          skip_list(l,1);
          }
        { OID  m = value_string(string_v(smod));
        if (m != CNULL)
         { (Reader._starcode_doc_star->value= _oid_(equal(_string_(opt),_string_(((char*)"-codedoc")))));
          (Reader._starexpl_doc_star->value= _oid_(equal(_string_(opt),_string_(((char*)"-exploitationdoc")))));
          load_doc_links_void1();
          load_module_doc_module1(OBJECT(module,m));
          { ClaireBoolean * g0940I;
            { ClaireBoolean *v_or;
              { v_or = OBJECT(ClaireBoolean,Reader._starcode_doc_star->value);
                if (v_or == CTRUE) g0940I =CTRUE; 
                else { v_or = ((length_bag(Reader._doc_section->instances) != 0) ? CTRUE : CFALSE);
                  if (v_or == CTRUE) g0940I =CTRUE; 
                  else { v_or = ((length_bag(Reader._doc_category->instances) != 0) ? CTRUE : CFALSE);
                    if (v_or == CTRUE) g0940I =CTRUE; 
                    else { { OID  g0941UU;
                        { CL_INT loop_handle = ClEnv->cHandle;
                          ITERATE(c);
                          g0941UU= Kernel.cfalse;
                          bag *c_support;
                          c_support = Reader._doc_entity->descendents;
                          for (START(c_support); NEXT(c);)
                          if (OBJECT(ClaireClass,c)->instances->length != 0)
                           { g0941UU = Kernel.ctrue;
                            ClEnv->cHandle = loop_handle;break;}
                          }
                        v_or = boolean_I_any(g0941UU);
                        }
                      if (v_or == CTRUE) g0940I =CTRUE; 
                      else g0940I = CFALSE;}
                    }
                  }
                }
              }
            
            if (g0940I == CTRUE) if (((Reader._starone_file_star->value != Kernel.ctrue) && 
                    (Reader._starper_cat_file_star->value != Kernel.ctrue)) || 
                  (((OBJECT(ClaireBoolean,Reader._starone_file_star->value)) == CTRUE) && 
                      ((OBJECT(ClaireBoolean,Reader._starper_cat_file_star->value)) == CTRUE)))
               { (Reader._starone_file_star->value= Kernel.ctrue);
                generate_module_doc_module1(OBJECT(module,m));
                (Reader._starone_file_star->value= Kernel.cfalse);
                generate_module_doc_module1(OBJECT(module,m));
                }
              else generate_module_doc_module1(OBJECT(module,m));
                }
          }
        else close_exception(((general_error *) (*Core._general_error)(_string_(((char*)"~A is not a valid module")),
            _oid_(Kernel.nil))));
          }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: option_usage(g0942:{"-doclink", "-onefile", "-categories", "-apidoc", "-codedoc"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string35_Reader_(char *g0942) { 
    return option_usage_string35_Reader(g0942)->copyIfNeeded();
}


// The c++ function for: option_usage(self:{"-codedoc", "-apidoc", "-categories", "-onefile", "-doclink"}) [NEW_ALLOC]
CL_EXPORT tuple * option_usage_string35_Reader(char *self) { 
      
    GC_BIND;
    { tuple *Result ;
      Result = tuple::allocStack(3,_string_(((char*)"Generate documentation")),
        _string_(((char*)"[-doclink] [-onefile | -categories] {-apidoc | -codedoc} <m:module>")),
        GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(((char*)"Generate the documentation of the module <m> from source files. "),((char*)"When -apidoc is used, the documentation will reference definitions "))),((char*)"that have a @doc tag in their comment whereas -codedoc considers all "))),((char*)"definitions.\n"))),((char*)"The generated documentation will contain a single HTML file when -onefile is given "))),((char*)"or a per category file when -categories is specified, otherwise both are generated.\n"))),((char*)"Last, when -doclink is specified then with each definition is associated a link to "))),((char*)"the source file that contain the definition.")))));
      GC_UNBIND; return (Result);}
    }
  


// **********************************************************************
// *   Part 1: loading items from module(s) file(s)                     *
// **********************************************************************
// The c++ function for: load_module_doc(self:module) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  load_module_doc_module1(module *self) { 
    
    GC_BIND;
    { module * m = ClEnv->module_I;
      list * mods = list::empty(Kernel._module);
      _void_(ClEnv->module_I = self);
      (Reader.MODULE_NAME->value= _string_(self->name->name));
      if (self == claire.it)
       { _void_(ClEnv->module_I = Kernel.it);
        _void_(Kernel.it->source = ((char*)"meta"));
        load_file_items_string1(GC_STRING(_7_string(GC_STRING(Kernel.it->source),((char*)"kernel"))));
        _void_(ClEnv->module_I = self);
        mods= (list::alloc(Kernel._module,4,_oid_(Core.it),
          _oid_(Serialize.it),
          _oid_(Language.it),
          _oid_(Reader.it)));
        mods->addFast((OID)value_string(((char*)"Optimize")));
        mods->addFast((OID)value_string(((char*)"Generate")));
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(m);
          for (START(mods); NEXT(m);)
          { GC_LOOP;
            { _void_(ClEnv->module_I = OBJECT(module,m));
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(f);
                bag *f_support;
                f_support = GC_OBJECT(list,OBJECT(module,m)->made_of);
                for (START(f_support); NEXT(f);)
                { GC_LOOP;
                  load_file_items_string1(GC_STRING(_7_string(GC_STRING(OBJECT(module,m)->source),string_v(f))));
                  GC_UNLOOP; POP_SIGNAL;}
                }
              _void_(ClEnv->module_I = self);
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        }
      else { mods= (GC_OBJECT(list,list::alloc(Kernel._module,1,_oid_(self))));
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(f);
            bag *f_support;
            f_support = GC_OBJECT(list,self->made_of);
            for (START(f_support); NEXT(f);)
            { GC_LOOP;
              { ClaireHandler c_handle = ClaireHandler();
                if ERROR_IN 
                { load_file_items_string1(GC_STRING(_7_string(GC_STRING(self->source),string_v(f))));
                  ERROR_FREE;}
                else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                { c_handle.catchIt();if (INHERIT(ClEnv->exception_I->isa,Reader._bad_eval))
                   close_exception(ClEnv->exception_I);
                  }
                else PREVIOUS_HANDLER;}
              GC_UNLOOP; POP_SIGNAL;}
            }
          }
        _void_(ClEnv->module_I = m);
      { list * l;
        if ((OBJECT(ClaireBoolean,Reader.DEPOPTIONS->value)) == CTRUE)
         l = Core.option_usage->restrictions;
        else { list * r_out = list::empty(Kernel._method);
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(r);
              for (START(Core.option_usage->restrictions); NEXT(r);)
              if (OBJECT(restriction,r)->module_I == self)
               r_out->addFast((OID)r);
              }
            l = GC_OBJECT(list,r_out);
            }
          CL_INT  idx = 0;
        ClaireBoolean * first_ask = CTRUE;
        blob * b = GC_OBJECT(blob,blob_I_void1());
        PortObject * old = use_as_output_port(b);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(m);
          for (START(mods); NEXT(m);)
          { GC_LOOP;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(r);
              for (START(l); NEXT(r);)
              { GC_LOOP;
                if ((((equal_string(OBJECT(restriction,r)->module_I->name->name,((char*)"Generate")) == CTRUE) ? CTRUE : ((equal_string(OBJECT(restriction,r)->module_I->name->name,((char*)"Optimize")) == CTRUE) ? CTRUE : ((equal_string(OBJECT(restriction,r)->module_I->name->name,((char*)"Language")) == CTRUE) ? CTRUE : ((equal_string(OBJECT(restriction,r)->module_I->name->name,((char*)"Reader")) == CTRUE) ? CTRUE : CFALSE)))) != CTRUE) && 
                    (((equal((*(OBJECT(bag,(*(OBJECT(restriction,r)->domain))[1])))[1],_string_(((char*)"-sample"))) == CTRUE) ? CTRUE : 
                    ((equal((*(OBJECT(bag,(*(OBJECT(restriction,r)->domain))[1])))[1],_string_(((char*)"-trace"))) == CTRUE) ? CTRUE : 
                    ((equal((*(OBJECT(bag,(*(OBJECT(restriction,r)->domain))[1])))[1],_string_(((char*)"-noel"))) == CTRUE) ? CTRUE : 
                    ((equal((*(OBJECT(bag,(*(OBJECT(restriction,r)->domain))[1])))[1],_string_(((char*)"-errassegv"))) == CTRUE) ? CTRUE : 
                    ((equal((*(OBJECT(bag,(*(OBJECT(restriction,r)->domain))[1])))[1],_string_(((char*)"-qonerror"))) == CTRUE) ? CTRUE : 
                    ((equal((*(OBJECT(bag,(*(OBJECT(restriction,r)->domain))[1])))[1],_string_(((char*)"-v"))) == CTRUE) ? CTRUE : 
                    CFALSE)))))) != CTRUE))
                 { ++idx;
                  set_length_blob1(b,0);
                  { OID  g0943 = GC_OID(apply_method(OBJECT(method,r),GC_OBJECT(list,list::alloc(1,(*(OBJECT(bag,(*(OBJECT(restriction,r)->domain))[1])))[1]))));
                    OID  title = GC_OID((*Kernel.nth)(g0943,
                      ((OID)1)));
                    OID  syntax = GC_OID((*Kernel.nth)(g0943,
                      ((OID)2)));
                    OID  help = GC_OID((*Kernel.nth)(g0943,
                      ((OID)3)));
                    Reader_doc_option * opt;
                    { Reader_doc_option * _CL_obj = ((Reader_doc_option *) GC_OBJECT(Reader_doc_option,new_object_class(Reader._doc_option)));
                      _void_(_CL_obj->name = string_v(title));
                      _void_(_CL_obj->from_module = OBJECT(module,m));
                      add_I_property(Kernel.instances,Reader._doc_option,11,_oid_(_CL_obj));
                      _void_(_CL_obj->documentation = string_v(CLREAD(slot,_at_property1(Reader.documentation,Reader._doc_option),DEFAULT)));
                      opt = _CL_obj;
                      }
                    CL_INT  c = color_integer(2);
                    list * l = GC_OBJECT(list,OBJECT(list,(*Core.print_back_option_usage)(syntax)));
                    color_integer(c);
                    _void_(opt->usage = string_I_blob1(b));
                    update_property(Reader.opts,
                      opt,
                      8,
                      Kernel._object,
                      (*(l))[1]);
                    update_property(Core.vars,
                      opt,
                      9,
                      Kernel._object,
                      (*(l))[2]);
                    update_property(Reader.ranges,
                      opt,
                      10,
                      Kernel._object,
                      (*(l))[3]);
                    _void_(opt->documentation = string_v(help));
                    { CL_INT loop_handle = ClEnv->cHandle;
                      ITERATE(o);
                      bag *o_support;
                      o_support = GC_OBJECT(list,opt->opts);
                      for (START(o_support); NEXT(o);)
                      add_ref_to_item_doc_item1(opt,string_v(o));
                      }
                    }
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        use_as_output_port(old);
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// **********************************************************************
// *   Part 1: doc generation                                           *
// **********************************************************************
// The c++ function for: generate_module_doc(self:module) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  generate_module_doc_module1(module *self) { 
    
    GC_BIND;
    { Reader_doc_context * ctx;
      { { Reader_doc_context * _CL_obj = ((Reader_doc_context *) GC_OBJECT(Reader_doc_context,new_object_class(Reader._doc_context)));
          _void_(_CL_obj->source = self);
          _void_(_CL_obj->directory = string_v(Reader._stardirectory_star->value));
          _void_(_CL_obj->add_source_links_ask = OBJECT(ClaireBoolean,Reader._stardoc_links_star->value));
          _void_(_CL_obj->color = string_v(CLREAD(slot,_at_property1(Kernel.color,Reader._doc_context),DEFAULT)));
          ctx = _CL_obj;
          }
        GC_OBJECT(Reader_doc_context,ctx);}
      if ((OBJECT(ClaireBoolean,Reader._starone_file_star->value)) == CTRUE)
       { _void_(ctx->index = append_string(self->name->name,((char*)".html")));
        _void_(ctx->generation_mode = ((CL_INT)(OID)(0)));
        }
      else _void_(ctx->index = append_string(self->name->name,((char*)".index.html")));
        if (isdir_ask_string(ctx->directory) != CTRUE)
       mkdir_string2(ctx->directory);
      if ((CL_INT)LENGTH_STRING(string_v(Reader.SHORT_PRESENTATION->value)) > (CL_INT)0)
       { buffer * f = GC_OBJECT(buffer,fopen_string1(GC_STRING(append_string(GC_STRING(_7_string(GC_STRING(ctx->directory),ctx->source->name->name)),((char*)".presentation"))),((char*)"w")));
        fwrite_string2(GC_STRING(string_v(Reader.SHORT_PRESENTATION->value)),f);
        fclose_port1(f);
        }
      { buffer * f = GC_OBJECT(buffer,fopen_string1(GC_STRING(_7_string(GC_STRING(ctx->directory),GC_STRING(ctx->index))),((char*)"w")));
        PortObject * old = use_as_output_port(f);
        html_file_header_doc_context1(ctx);
        if (length_bag(Reader._doc_author->instances) != 0)
         { princ_string(((char*)"<ul>\n\t\t\t\t"));
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(g0944);
            bag *g0944_support;
            g0944_support = Reader._doc_author->descendents;
            for (START(g0944_support); NEXT(g0944);)
            { ClaireBoolean * g0945;
              { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(c);
                  V_C= Kernel.cfalse;
                  for (START(OBJECT(ClaireClass,g0944)->instances); NEXT(c);)
                  { princ_string(((char*)"<li><b>Author :</b> "));
                    (*Language.self_html)(_oid_(Reader.documentation),
                      c);
                    princ_string(((char*)"</li>\n\t\t\t\t\t\t"));
                    ;}
                  }
                
                g0945=OBJECT(ClaireBoolean,V_C);}
              if (g0945 == CTRUE)
               { ;ClEnv->cHandle = loop_handle; break;}
              }
            }
          princ_string(((char*)"</ul>\n\t\t\t\t"));
          ;}
        if (length_bag(Reader._doc_copyright->instances) != 0)
         { princ_string(((char*)"<h1><span class=pretitle>&nbsp;</span>&nbsp;Copyright</h1>\n\t\t\t\t"));
          princ_string(((char*)"<ul>\n\t\t\t\t"));
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(g0946);
            bag *g0946_support;
            g0946_support = Reader._doc_copyright->descendents;
            for (START(g0946_support); NEXT(g0946);)
            { ClaireBoolean * g0947;
              { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(c);
                  V_C= Kernel.cfalse;
                  for (START(OBJECT(ClaireClass,g0946)->instances); NEXT(c);)
                  { princ_string(((char*)"<li>"));
                    (*Language.self_html)(_oid_(Reader.documentation),
                      c);
                    princ_string(((char*)"</li>\n\t\t\t\t\t\t"));
                    ;}
                  }
                
                g0947=OBJECT(ClaireBoolean,V_C);}
              if (g0947 == CTRUE)
               { ;ClEnv->cHandle = loop_handle; break;}
              }
            }
          princ_string(((char*)"</ul>\n\t\t\t\t"));
          ;}
        if (length_bag(Reader._doc_preamble->instances) != 0)
         { princ_string(((char*)"<h1><span class=pretitle>&nbsp;</span>&nbsp;Preamble</h1>\n\t\t\t\t"));
          print_doc_doc_context1(ctx,GC_STRING(OBJECT(Reader_doc_item,(*(Reader._doc_preamble->instances))[1])->documentation),Kernel.nil,Kernel.nil);
          }
        generate_index_doc_context1(ctx);
        generate_doc_doc_context1(ctx);
        html_file_footer_void1();
        fclose_port1(f);
        use_as_output_port(old);
        }
      }
    GC_UNBIND; POP_SIGNAL;}
  


// **********************************************************************
// *   Part 1: index generation                                         *
// **********************************************************************
// The c++ function for: generate_index(self:doc_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  generate_index_doc_context1(Reader_doc_context *self) { 
    generate_category_index_doc_context1(self);
    generate_option_index_doc_context1(self);
    if (Reader._starexpl_doc_star->value != Kernel.ctrue)
     { generate_entity_index_doc_context1(self,Reader._doc_global,((char*)"global"),((char*)"Global Variable"));
      generate_entity_index_doc_context1(self,Reader._doc_table,((char*)"table"),((char*)"Table"));
      generate_entity_index_doc_context1(self,Reader._doc_interface,((char*)"interface"),((char*)"Interface"));
      generate_entity_index_doc_context1(self,Reader._doc_class,((char*)"class"),((char*)"Class"));
      generate_entity_index_doc_context1(self,Reader._doc_method,((char*)"method"),((char*)"Method"));
      }
    POP_SIGNAL;}
  


// The c++ function for: generate_index(ctx:doc_context,e:doc_entity) [NEW_ALLOC]
CL_EXPORT void  generate_index_doc_context2(Reader_doc_context *ctx,Reader_doc_entity *e) { 
    generate_index_doc_context3(ctx,e,CFALSE);
    POP_SIGNAL;}
  


// The c++ function for: generate_index(ctx:doc_context,e:doc_entity,catindex?:boolean) [NEW_ALLOC]
CL_EXPORT void  generate_index_doc_context3(Reader_doc_context *ctx,Reader_doc_entity *e,ClaireBoolean *catindex_ask) { 
    
    GC_BIND;
    princ_string(((char*)"<font font-face='Courier' class='item_index'>"));
    if ((ctx->add_source_links_ask == CTRUE) && 
        (((e->src_location == CNULL) ? CTRUE : CFALSE) != CTRUE))
     { princ_string(((char*)"["));
      if ((CL_INT)LENGTH_STRING(e->documentation) > (CL_INT)0)
       edit_link_string1(GC_STRING(string_v((*Kernel.nth)(e->src_location,
        ((OID)1)))),((CL_INT)(*Kernel.nth)(e->src_location,
        ((OID)2))),((char*)"edit"));
      else edit_link_string1(GC_STRING(string_v((*Kernel.nth)(e->src_location,
          ((OID)1)))),((CL_INT)(*Kernel.nth)(e->src_location,
          ((OID)2))),((char*)"<font color='red'>edit</font>"));
        princ_string(((char*)"]"));
      if ((CL_INT)LENGTH_STRING(e->documentation) > (CL_INT)0)
       { princ_string(((char*)"   "));
        ;}
      print_module_doc_entity1(e);
      }
    if ((LENGTH_STRING(e->documentation) == 0) && 
        (catindex_ask == CTRUE))
     { princ_string(((char*)""));
      (*Language.self_html)(_oid_(Kernel.name),
        _oid_(e));
      }
    else item_href_doc_context2(ctx,e);
      (*Reader.item_prototype)(_oid_(e),
      _oid_(ctx));
    if (e->xl_ask == CTRUE)
     princ_string(((char*)" <font color='red'>[XL]</font>"));
    princ_string(((char*)"</font>"));
    ;GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: generate_category_index(self:doc_context) [NEW_ALLOC]
CL_EXPORT void  generate_category_index_doc_context1(Reader_doc_context *self) { 
    
    GC_BIND;
    { ClaireBoolean * g0952I;
      { OID  g0953UU;
        { CL_INT  V_CL0954;{ list * g0955UU;
            { list * c_out = list::empty(Kernel.emptySet);
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(g0948);
                bag *g0948_support;
                g0948_support = Reader._doc_category->descendents;
                for (START(g0948_support); NEXT(g0948);)
                { ClaireBoolean * g0949;
                  { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                      ITERATE(c);
                      V_C= Kernel.cfalse;
                      for (START(OBJECT(ClaireClass,g0948)->instances); NEXT(c);)
                      if ((Reader._starexpl_doc_star->value != Kernel.ctrue) || 
                          ((OBJECT(Reader_doc_category,c)->exploit_ask == CTRUE) || 
                            ((((OBJECT(Reader_doc_category,c)->section == (NULL)) ? CTRUE : CFALSE) != CTRUE) && (OBJECT(Reader_doc_category,c)->section->exploit_ask == CTRUE))))
                       c_out->addFast((OID)c);
                      }
                    
                    g0949=OBJECT(ClaireBoolean,V_C);}
                  if (g0949 == CTRUE)
                   { ;ClEnv->cHandle = loop_handle; break;}
                  }
                }
              g0955UU = GC_OBJECT(list,c_out);
              }
            V_CL0954 = g0955UU->length;
            }
          
          g0953UU=((OID)V_CL0954);}
        g0952I = ((g0953UU != ((OID)0)) ? CTRUE : CFALSE);
        }
      
      if (g0952I == CTRUE) { princ_string(((char*)"<h1><span class=pretitle>&nbsp;</span>&nbsp;<a name='__category_index__'>Category index</a></h1>\n\t\t<ol>"));
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(sec);
            bag *sec_support;
            sec_support = Reader._doc_section->instances;
            for (START(sec_support); NEXT(sec);)
            { GC_LOOP;
              { ClaireBoolean * g0956I;
                { ClaireBoolean *v_or;
                  { v_or = OBJECT(Reader_doc_section,sec)->exploit_ask;
                    if (v_or == CTRUE) g0956I =CTRUE; 
                    else { { OID  g0957UU;
                        { CL_INT loop_handle = ClEnv->cHandle;
                          ITERATE(c);
                          g0957UU= Kernel.cfalse;
                          for (START(OBJECT(Reader_doc_section,sec)->categories); NEXT(c);)
                          if ((Reader._starexpl_doc_star->value != Kernel.ctrue) || 
                              (OBJECT(Reader_doc_category,c)->exploit_ask == CTRUE))
                           { g0957UU = Kernel.ctrue;
                            ClEnv->cHandle = loop_handle;break;}
                          }
                        v_or = boolean_I_any(g0957UU);
                        }
                      if (v_or == CTRUE) g0956I =CTRUE; 
                      else g0956I = CFALSE;}
                    }
                  }
                
                if (g0956I == CTRUE) { princ_string(((char*)"\n\t\t\t<li class='section'><a name='"));
                    print_oid_any1(sec);
                    princ_string(((char*)"'>"));
                    (*Language.self_html)(_oid_(Kernel.name),
                      sec);
                    princ_string(((char*)"</a>\n\t\t\t\t<ol>"));
                    { CL_INT loop_handle = ClEnv->cHandle;
                      ITERATE(cat);
                      for (START(OBJECT(Reader_doc_section,sec)->categories); NEXT(cat);)
                      if ((Reader._starexpl_doc_star->value != Kernel.ctrue) || 
                          ((OBJECT(Reader_doc_section,sec)->exploit_ask == CTRUE) || 
                            (OBJECT(Reader_doc_category,cat)->exploit_ask == CTRUE)))
                       { princ_string(((char*)"<li>\n\t\t\t\t\t\t"));
                        item_href_doc_context2(self,OBJECT(Reader_doc_item,cat));
                        princ_string(((char*)""));
                        if (OBJECT(Reader_doc_item,cat)->xl_ask == CTRUE)
                         princ_string(((char*)" <font color='red'>[XL]</font>"));
                        princ_string(((char*)"</li>\n\t\t\t\t\t"));
                        ;}
                      }
                    princ_string(((char*)"</ol>\n\t\t\t</li>\n\t\t\t"));
                    ;}
                  }
              GC_UNLOOP; POP_SIGNAL;}
            }
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(g0950);
            bag *g0950_support;
            g0950_support = Reader._doc_category->descendents;
            for (START(g0950_support); NEXT(g0950);)
            { ClaireBoolean * g0951;
              { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(cat);
                  V_C= Kernel.cfalse;
                  for (START(OBJECT(ClaireClass,g0950)->instances); NEXT(cat);)
                  if (OBJECT(Reader_doc_category,cat)->section == (NULL))
                   { princ_string(((char*)"<li>"));
                    item_href_doc_context2(self,OBJECT(Reader_doc_item,cat));
                    princ_string(((char*)""));
                    if (OBJECT(Reader_doc_item,cat)->xl_ask == CTRUE)
                     princ_string(((char*)" <font color='red'>[XL]</font>"));
                    princ_string(((char*)"</li>\n\t\t\t"));
                    ;}
                  }
                
                g0951=OBJECT(ClaireBoolean,V_C);}
              if (g0951 == CTRUE)
               { ;ClEnv->cHandle = loop_handle; break;}
              }
            }
          princ_string(((char*)"</ol>\n\t\t"));
          ;}
        }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: generate_option_index(self:doc_context) [NEW_ALLOC]
CL_EXPORT void  generate_option_index_doc_context1(Reader_doc_context *self) { 
    if (length_bag(Reader._doc_option->instances) != 0)
     { princ_string(((char*)"<h1><span class=pretitle>&nbsp;</span>&nbsp;<a name='__option_index__'>Command line option index</a></h1>\n\t\t"));
      princ_string(((char*)"<ol>\n\t\t"));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(opt);
        bag *opt_support;
        opt_support = Reader._doc_option->instances;
        for (START(opt_support); NEXT(opt);)
        { princ_string(((char*)"<li>"));
          item_href_doc_context2(self,OBJECT(Reader_doc_item,opt));
          princ_string(((char*)" : "));
          princ_string(OBJECT(Reader_doc_option,opt)->usage);
          princ_string(((char*)"</li>\n\t\t\t"));
          ;}
        }
      princ_string(((char*)"</ol>\n\t\t"));
      ;}
    POP_SIGNAL;}
  


// The c++ function for: generate_entity_index(self:doc_context,c:class,cn:string,si:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  generate_entity_index_doc_context1(Reader_doc_context *self,ClaireClass *c,char *cn,char *si) { 
    
    GC_BIND;
    if (c->instances->length != 0)
     { princ_string(((char*)"<h1><span class=pretitle>&nbsp;</span>&nbsp;<a name='__"));
      (*Language.echo)(_string_(cn));
      princ_string(((char*)"_index__'>"));
      (*Language.echo)(_string_(si));
      princ_string(((char*)" index</a></h1>\n\t\t<ul>"));
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(e);
        bag *e_support;
        e_support = GC_OBJECT(list,sort_method(GC_OBJECT(method,((method *) _at_property1(Reader.compare_items,Reader._doc_entity))),c->instances));
        for (START(e_support); NEXT(e);)
        { princ_string(((char*)"<li>"));
          generate_index_doc_context3(self,OBJECT(Reader_doc_entity,e),CFALSE);
          princ_string(((char*)"</li>\n\t\t\t"));
          ;}
        }
      princ_string(((char*)"</ul>\n\t\t"));
      ;}
    GC_UNBIND; POP_SIGNAL;}
  


// **********************************************************************
// *   Part 1: doc generation                                           *
// **********************************************************************
// The c++ function for: generate_doc(self:doc_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  generate_doc_doc_context1(Reader_doc_context *self) { 
    
    GC_BIND;
    if ((OBJECT(ClaireBoolean,Reader._staronly_doc_links_star->value)) == CTRUE)
     save_doc_links_doc_context1(self);
    else if (((OID)self->generation_mode) == (OID)(0))
     { save_doc_links_doc_context1(self);
      generate_doc_doc_context2(self,((char*)"categories"),Reader._doc_category);
      generate_doc_doc_context2(self,((char*)"command line options"),Reader._doc_option);
      if (Reader._starexpl_doc_star->value != Kernel.ctrue)
       { generate_doc_doc_context2(self,((char*)"global variables"),Reader._doc_global);
        generate_doc_doc_context2(self,((char*)"tables"),Reader._doc_table);
        generate_doc_doc_context2(self,((char*)"interfaces"),Reader._doc_interface);
        generate_doc_doc_context2(self,((char*)"classes"),Reader._doc_class);
        generate_doc_doc_context2(self,((char*)"methods"),Reader._doc_method);
        }
      }
    else { { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(g0958);
          bag *g0958_support;
          g0958_support = Reader._doc_category->descendents;
          for (START(g0958_support); NEXT(g0958);)
          { GC_LOOP;
            { ClaireBoolean * g0959;
              { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(cat);
                  V_C= Kernel.cfalse;
                  for (START(OBJECT(ClaireClass,g0958)->instances); NEXT(cat);)
                  { GC_LOOP;
                    if ((Reader._starexpl_doc_star->value != Kernel.ctrue) || 
                        (OBJECT(Reader_doc_category,cat)->exploit_ask == CTRUE))
                     { char * fn;
                      { { print_in_string_void();
                          item_file_doc_context1(self,OBJECT(Reader_doc_category,cat));
                          fn = end_of_string_void();
                          }
                        GC_STRING(fn);}
                      buffer * f = GC_OBJECT(buffer,fopen_string1(GC_STRING(_7_string(GC_STRING(self->directory),fn)),((char*)"w")));
                      PortObject * old = use_as_output_port(f);
                      html_file_header_doc_context3(self,OBJECT(Reader_doc_item,cat));
                      generate_doc_doc_category1(OBJECT(Reader_doc_category,cat),self);
                      { CL_INT loop_handle = ClEnv->cHandle;
                        ITERATE(e);
                        bag *e_support;
                        e_support = GC_OBJECT(list,OBJECT(Reader_doc_category,cat)->items);
                        for (START(e_support); NEXT(e);)
                        (*Reader.generate_doc)(e,
                          _oid_(self));
                        }
                      html_file_footer_void1();
                      fclose_port1(f);
                      use_as_output_port(old);
                      }
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                
                g0959=OBJECT(ClaireBoolean,V_C);}
              if (g0959 == CTRUE)
               { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
              }
            GC_UNLOOP; POP_SIGNAL;}
          }
        { buffer * f = GC_OBJECT(buffer,fopen_string1(GC_STRING(append_string(GC_STRING(_7_string(GC_STRING(self->directory),self->source->name->name)),((char*)".option.html"))),((char*)"w")));
          PortObject * old = use_as_output_port(f);
          html_file_header_doc_context2(self,((char*)"options"));
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(g0960);
            bag *g0960_support;
            g0960_support = Reader._doc_option->descendents;
            for (START(g0960_support); NEXT(g0960);)
            { ClaireBoolean * g0961;
              { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(e);
                  V_C= Kernel.cfalse;
                  for (START(OBJECT(ClaireClass,g0960)->instances); NEXT(e);)
                  generate_doc_doc_option1(OBJECT(Reader_doc_option,e),self);
                  }
                
                g0961=OBJECT(ClaireBoolean,V_C);}
              if (g0961 == CTRUE)
               { ;ClEnv->cHandle = loop_handle; break;}
              }
            }
          html_file_footer_void1();
          fclose_port1(f);
          use_as_output_port(old);
          }
        }
      GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: generate_doc(self:doc_context,str:string,c:class) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  generate_doc_doc_context2(Reader_doc_context *self,char *str,ClaireClass *c) { 
    
    GC_BIND;
    { ClaireBoolean * g0964I;
      { OID  g0965UU;
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(x);
          g0965UU= Kernel.cfalse;
          for (START(c->instances); NEXT(x);)
          if (equal_string(OBJECT(Reader_doc_item,x)->documentation,((char*)"")) != CTRUE)
           { g0965UU = Kernel.ctrue;
            ClEnv->cHandle = loop_handle;break;}
          }
        g0964I = boolean_I_any(g0965UU);
        }
      
      if (g0964I == CTRUE) { princ_string(((char*)"<h1 style='page-break-before: always; page-break-after: avoid'><span class=pretitle>&nbsp;</span>&nbsp;"));
          { OID  g0966UU;
            { if ((CL_INT)LENGTH_STRING(string_v(Reader.DOC_TITLE->value)) > (CL_INT)0)
               g0966UU = Reader.DOC_TITLE->value;
              else g0966UU = _oid_(self->source);
                GC_OID(g0966UU);}
            (*Language.self_html)(g0966UU);
            }
          princ_string(((char*)" "));
          (*Language.echo)(_string_(str));
          princ_string(((char*)"</h1>\n\t\t"));
          ;}
        }
    if (c == Reader._doc_category)
     { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(cat);
      bag *cat_support;
      cat_support = GC_OBJECT(list,ordered_categories_void1());
      for (START(cat_support); NEXT(cat);)
      generate_doc_doc_category1(OBJECT(Reader_doc_category,cat),self);
      }
    else if (c == Reader._doc_option)
     { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(g0962);
      bag *g0962_support;
      g0962_support = Reader._doc_option->descendents;
      for (START(g0962_support); NEXT(g0962);)
      { ClaireBoolean * g0963;
        { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(opt);
            V_C= Kernel.cfalse;
            for (START(OBJECT(ClaireClass,g0962)->instances); NEXT(opt);)
            generate_doc_doc_option1(OBJECT(Reader_doc_option,opt),self);
            }
          
          g0963=OBJECT(ClaireBoolean,V_C);}
        if (g0963 == CTRUE)
         { ;ClEnv->cHandle = loop_handle; break;}
        }
      }
    else { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(e);
        bag *e_support;
        e_support = GC_OBJECT(list,sort_method(GC_OBJECT(method,((method *) _at_property1(Reader.compare_items,Reader._doc_entity))),c->instances));
        for (START(e_support); NEXT(e);)
        (*Reader.generate_doc)(e,
          _oid_(self));
        }
      GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: generate_doc(self:doc_category,ctx:doc_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  generate_doc_doc_category1(Reader_doc_category *self,Reader_doc_context *ctx) { 
    
    GC_BIND;
    if (((OID)ctx->generation_mode) == (OID)(0))
     { if (((self->aname == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       { princ_string(((char*)"<a name='"));
        (*Language.self_html)(_oid_(Reader.aname),
          _oid_(self));
        princ_string(((char*)"'>"));
        ;}
      princ_string(((char*)"<a name='"));
      print_oid_any1(_oid_(self));
      princ_string(((char*)"'><hr size=0 style='page-break-before: always' /></a>\n\t\t<a name='"));
      (*Language.echo)(GC_OID(_string_(replace_string(self->name,((char*)" "),((char*)"_")))));
      princ_string(((char*)"'><hr size=0 /></a>"));
      if (((self->aname == (NULL)) ? CTRUE : CFALSE) != CTRUE)
       { princ_string(((char*)"</a>"));
        ;}
      princ_string(((char*)"\n\t\t"));
      ;}
    princ_string(((char*)"<table width='100%' class='item_header'>\n\t\t<tr>\n\t\t\t<td width='33%' align='left' valign='bottom'><i>"));
    if (((self->section == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     { list * l = GC_OBJECT(list,self->section->categories);
      CL_INT  c = index_list(l,_oid_(self));
      if ((CL_INT)c > (CL_INT)1)
       item_href_doc_context2(ctx,OBJECT(Reader_doc_item,(*(l))[((CL_INT)c-(CL_INT)1)]));
      else { list * li = Reader._doc_section->instances;
          CL_INT  cs = index_list(li,_oid_(self->section));
          if ((CL_INT)cs > (CL_INT)1)
           { Reader_doc_section * sec = OBJECT(Reader_doc_section,(*(li))[((CL_INT)cs-(CL_INT)1)]);
            princ_string(((char*)""));
            (*Language.self_html)(_oid_(Kernel.name),
              _oid_(sec));
            if (sec->categories->length != 0)
             { princ_string(((char*)"<br/>"));
              item_href_doc_context2(ctx,OBJECT(Reader_doc_item,last_list(sec->categories)));
              }
            }
          }
        }
    princ_string(((char*)"</i></td>\n\t\t\t<td width='33%' align='center' valign='top'><i>"));
    category_index_href_doc_context1(ctx);
    if (((self->section == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     { princ_string(((char*)"<br/>"));
      section_index_href_doc_context1(ctx,self->section);
      }
    princ_string(((char*)"<br/><b>"));
    (*Language.self_html)(_oid_(Kernel.name),
      _oid_(self));
    princ_string(((char*)"</b>\n\t\t\t\t</i></td>\n\t\t\t<td width='33%' align='right' valign='bottom'><i>"));
    if (((self->section == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     { list * l = GC_OBJECT(list,self->section->categories);
      CL_INT  len = l->length;
      CL_INT  c = index_list(l,_oid_(self));
      if ((CL_INT)c < (CL_INT)len)
       item_href_doc_context2(ctx,OBJECT(Reader_doc_item,(*(l))[((CL_INT)c+(CL_INT)1)]));
      else { list * li = Reader._doc_section->instances;
          CL_INT  cs = index_list(li,_oid_(self->section));
          if ((CL_INT)cs < (CL_INT)li->length)
           { Reader_doc_section * sec = OBJECT(Reader_doc_section,(*(li))[((CL_INT)cs+(CL_INT)1)]);
            princ_string(((char*)""));
            (*Language.self_html)(_oid_(Kernel.name),
              _oid_(sec));
            if (sec->categories->length != 0)
             { princ_string(((char*)"<br/>"));
              item_href_doc_context2(ctx,OBJECT(Reader_doc_item,(*(sec->categories))[1]));
              }
            }
          }
        }
    princ_string(((char*)"</i></td>\n\t\t</tr>\n\t</table>\n\t"));
    if ((((self->section == (NULL)) ? CTRUE : CFALSE) != CTRUE) && 
        (index_list(self->section->categories,_oid_(self)) == 1))
     { princ_string(((char*)"<h1><span class=pretitle>&nbsp;</span>&nbsp;"));
      (*Language.self_html)(_oid_(Kernel.name),
        _oid_(self->section));
      princ_string(((char*)"</h1>\n\t\t"));
      ;}
    princ_string(((char*)"<h2><span class=pretitle>&nbsp;</span>&nbsp;"));
    if (((OID)ctx->generation_mode) != (OID)(0))
     { princ_string(((char*)"<a name='"));
      print_oid_any1(_oid_(self));
      princ_string(((char*)"'>"));
      (*Language.self_html)(_oid_(Kernel.name),
        _oid_(self));
      princ_string(((char*)"</a>\n\t\t\t"));
      ;}
    else { princ_string(((char*)""));
        (*Language.self_html)(_oid_(Kernel.name),
          _oid_(self));
        }
      if (self->xl_ask == CTRUE)
     princ_string(((char*)" <font color='red'>[XL]</font>"));
    princ_string(((char*)"</h2>\n\t"));
    princ_string(((char*)"<ul>"));
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(e);
      bag *e_support;
      e_support = GC_OBJECT(list,sort_method(GC_OBJECT(method,((method *) _at_property1(Reader.compare_items,Reader._doc_entity))),GC_OBJECT(list,self->items)));
      for (START(e_support); NEXT(e);)
      if (INHERIT(OBJECT(ClaireObject,e)->isa,Reader._doc_class))
       { princ_string(((char*)"<li>"));
        generate_index_doc_context3(ctx,OBJECT(Reader_doc_entity,e),CTRUE);
        princ_string(((char*)"</li>"));
        ;}
      }
    princ_string(((char*)"</ul>"));
    princ_string(((char*)"<ul>"));
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(e);
      bag *e_support;
      e_support = GC_OBJECT(list,sort_method(GC_OBJECT(method,((method *) _at_property1(Reader.compare_items,Reader._doc_entity))),GC_OBJECT(list,self->items)));
      for (START(e_support); NEXT(e);)
      if (inherit_ask_class(OBJECT(ClaireObject,e)->isa,Reader._doc_class) != CTRUE)
       { princ_string(((char*)"<li>"));
        generate_index_doc_context3(ctx,OBJECT(Reader_doc_entity,e),CTRUE);
        princ_string(((char*)"</li>"));
        ;}
      }
    princ_string(((char*)"</ul>"));
    print_doc_doc_context1(ctx,GC_STRING(self->documentation),GC_OBJECT(list,self->entity_names),GC_OBJECT(list,self->aliases));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: generate_doc(self:doc_option,ctx:doc_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  generate_doc_doc_option1(Reader_doc_option *self,Reader_doc_context *ctx) { 
    
    GC_BIND;
    princ_string(((char*)"<a name='"));
    print_oid_any1(_oid_(self));
    princ_string(((char*)"'><hr size=0 style='page-break-after: avoid' /></a>\n\t<table width='100%' class='item_header' >\n\t\t<tr>\n\t\t\t<td width='33%' align='left'><i>"));
    option_index_href_doc_context1(ctx);
    princ_string(((char*)"</i></td>\n\t\t\t<td width='33%' align='center'>"));
    (*Language.self_html)(_oid_(Kernel.name),
      _oid_(self));
    princ_string(((char*)"</td>\n\t\t\t<td width='33%' align='right'><i>"));
    { OID  g0970UU;
      { if ((CL_INT)LENGTH_STRING(string_v(Reader.DOC_TITLE->value)) > (CL_INT)0)
         g0970UU = Reader.DOC_TITLE->value;
        else g0970UU = _oid_(self->from_module);
          GC_OID(g0970UU);}
      (*Language.self_html)(g0970UU);
      }
    princ_string(((char*)" command line option</i></td>\n\t\t</tr>\n\t</table>"));
    if (ctx->add_source_links_ask == CTRUE)
     { OID  xtest;
      { { OID  dm_some = CNULL;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            ITERATE(g0967);
            bag *g0967_support;
            g0967_support = Language._Defmethod->descendents;
            for (START(g0967_support); NEXT(g0967);)
            { GC_LOOP;
              { ClaireBoolean * g0968;
                { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                    OID gc_local;
                    ITERATE(dm);
                    V_C= Kernel.cfalse;
                    for (START(OBJECT(ClaireClass,g0967)->instances); NEXT(dm);)
                    { GC_LOOP;
                      { ClaireBoolean * g0971I;
                        { Call * c = GC_OBJECT(Call,OBJECT(Defmethod,dm)->arg);
                          g0971I = ((c->selector == Core.option_usage) ? ((c->args->length != 0) ? ((belong_to(GC_OID((*(self->opts))[1]),GC_OID((*Kernel.range)(GC_OID((*(c->args))[1])))) == CTRUE) ? CTRUE: CFALSE): CFALSE): CFALSE);
                          }
                        
                        if (g0971I == CTRUE) { GC_UNLOOP;V_C = dm_some= (dm);
                            ClEnv->cHandle = loop_handle;break;}
                          }
                      GC_UNLOOP; POP_SIGNAL;}
                    }
                  
                  g0968=OBJECT(ClaireBoolean,V_C);}
                if (g0968 == CTRUE)
                 { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                }
              GC_UNLOOP; POP_SIGNAL;}
            }
          xtest = dm_some;
          }
        GC_OID(xtest);}
      if (xtest != CNULL)
       { Defmethod * x = OBJECT(Defmethod,xtest);
        edit_link_bag1(OBJECT(bag,nth_table1(Language.CODE_LOCS,_oid_(x->arg))));
        }
      else ;}
    princ_string(((char*)"<h3 class='opt_usage'>"));
    princ_string(self->usage);
    princ_string(((char*)"</h3>"));
    if (self->vars->length != 0)
     { princ_string(((char*)"<h4>Where</h4>"));
      princ_string(((char*)"<ul>"));
      { CL_INT  i = 1;
        CL_INT  g0969 = self->vars->length;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)i <= (CL_INT)g0969))
          { GC_LOOP;
            princ_string(((char*)"<li><font color='green'><b>"));
            (*Language.self_html)(GC_OID((*(self->vars))[i]));
            princ_string(((char*)"</b></font> belongs to "));
            (*Language.self_html)(GC_OID((*(self->ranges))[i]));
            princ_string(((char*)"</li>"));
            ;++i;
            GC_UNLOOP;POP_SIGNAL;}
          }
        }
      princ_string(((char*)"</ul>"));
      ;}
    print_doc_doc_context1(ctx,GC_STRING(replace_string(GC_STRING(self->documentation),((char*)"\n"),((char*)"\\br "))),GC_OBJECT(list,self->vars),GC_OBJECT(list,self->opts));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: start_entity_doc(self:doc_entity,ctx:doc_context) [NEW_ALLOC]
CL_EXPORT void  start_entity_doc_doc_entity1(Reader_doc_entity *self,Reader_doc_context *ctx) { 
    (*Reader.item_header)(_oid_(self),
      _oid_(ctx));
    princ_string(((char*)"<h3>"));
    { OID  g0972UU;
      { print_module_doc_entity1(self);
        g0972UU = _string_(self->name);
        }
      (*Language.self_html)(g0972UU);
      }
    (*Reader.item_prototype)(_oid_(self),
      _oid_(ctx));
    princ_string(((char*)"</h3>"));
    ;POP_SIGNAL;}
  


// The c++ function for: generate_doc(self:doc_entity,ctx:doc_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  generate_doc_doc_entity1(Reader_doc_entity *self,Reader_doc_context *ctx) { 
    
    GC_BIND;
    if ((CL_INT)LENGTH_STRING(self->documentation) > (CL_INT)0)
     { start_entity_doc_doc_entity1(self,ctx);
      print_doc_doc_context1(ctx,GC_STRING(self->documentation),Kernel.nil,list::alloc(1,_string_(self->name)));
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: generate_doc(self:doc_method,ctx:doc_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  generate_doc_doc_method1(Reader_doc_method *self,Reader_doc_context *ctx) { 
    
    GC_BIND;
    if ((CL_INT)LENGTH_STRING(self->documentation) > (CL_INT)0)
     { start_entity_doc_doc_entity1(self,ctx);
      print_doc_doc_context1(ctx,GC_STRING(self->documentation),GC_OBJECT(list,self->vars),list::alloc(1,_string_(self->name)));
      }
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: generate_doc(self:doc_class,ctx:doc_context) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  generate_doc_doc_class1(Reader_doc_class *self,Reader_doc_context *ctx) { 
    
    GC_RESERVE(1);  // v3.3.39 optim !
    if ((CL_INT)LENGTH_STRING(self->documentation) > (CL_INT)0)
     { item_header_doc_class1(self,ctx);
      princ_string(((char*)"<table><tr><td class=class_proto>"));
      princ_string(((char*)"<h3>"));
      entity_print_doc_entity1(self,ctx,GC_OID(self->source));
      princ_string(((char*)"</h3>"));
      { OID  c = GC_OID(self->source);
        OID  a = c;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while ((contain_ask_list(OBJECT(list,Reader.DOC_CLASS_ROOTS->value),a) != CTRUE))
          { GC_LOOP;
            { list * aslots;
              { { list * s_out = list::empty(Kernel._slot);
                  { CL_INT loop_handle = ClEnv->cHandle;
                    ITERATE(s);
                    for (START(OBJECT(ClaireClass,c)->slots); NEXT(s);)
                    if (equal((*(OBJECT(restriction,s)->domain))[1],a) == CTRUE)
                     s_out->addFast((OID)s);
                    }
                  aslots = GC_OBJECT(list,s_out);
                  }
                GC_OBJECT(list,aslots);}
              if (equal(a,c) != CTRUE)
               { princ_string(((char*)"<tr><td class='class_proto_super item_index'>"));
                { OID  e = GC_OID(string2item_doc_context1(ctx,OBJECT(symbol,(*Kernel.name)(a))->name));
                  if (e != CNULL)
                   (*Reader.item_href)(_oid_(ctx),
                    e);
                  else entity_print_doc_entity1(self,ctx,a);
                    }
                }
              princ_string(((char*)"<td class_proto_slot>"));
              if (equal(a,c) == CTRUE)
               { princ_string(((char*)"<br/>"));
                ;}
              if (boolean_I_any(_oid_(aslots)) != CTRUE)
               { princ_string(((char*)"<span class=item_index>&nbsp;&nbsp;-</span>"));
                ;}
              else { CL_INT loop_handle = ClEnv->cHandle;
                  OID gc_local;
                  ITERATE(s);
                  for (START(aslots); NEXT(s);)
                  { GC_LOOP;
                    { princ_string(((char*)"<span class=item_index>&nbsp;&nbsp;<b>"));
                      entity_print_doc_entity1(self,ctx,_oid_(OBJECT(restriction,s)->selector));
                      princ_string(((char*)"</b> : "));
                      { ClaireType * rg = OBJECT(restriction,s)->range;
                        if (INHERIT(rg->isa,Core._subtype))
                         { OID  e = GC_OID(string2item_doc_context1(ctx,((INHERIT(CLREAD(subtype,rg,t1)->isa,Kernel._class)) ?
                            CLREAD(ClaireClass,CLREAD(subtype,rg,t1),name)->name :
                            ((char*)"???") )));
                          if (e != CNULL)
                           { princ_string(((char*)""));
                            (*Language.self_html)(_oid_(Kernel.arg),
                              _oid_(rg));
                            princ_string(((char*)"["));
                            (*Reader.item_href)(_oid_(ctx),
                              e);
                            princ_string(((char*)"]"));
                            ;}
                          else entity_print_doc_entity1(self,ctx,_oid_(rg));
                            }
                        else if (INHERIT(rg->isa,Kernel._class))
                         { OID  e = GC_OID(string2item_doc_context1(ctx,CLREAD(ClaireClass,rg,name)->name));
                          if (e != CNULL)
                           (*Reader.item_href)(_oid_(ctx),
                            e);
                          else entity_print_doc_entity1(self,ctx,_oid_(rg));
                            }
                        else entity_print_doc_entity1(self,ctx,_oid_(rg));
                          }
                      princ_string(((char*)"</span><br/>"));
                      ;}
                    GC_UNLOOP; POP_SIGNAL;}
                  }
                GC__OID(a = (*Kernel.superclass)(a), 1);
              }
            GC_UNLOOP;POP_SIGNAL;}
          }
        }
      princ_string(((char*)"</table>"));
      { OID  c = GC_OID(self->source);
        if (INHERIT(OBJECT(ClaireClass,c),Kernel._thing))
         { ClaireBoolean * first_ask = CTRUE;
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(x);
            for (START(OBJECT(ClaireClass,c)->instances); NEXT(x);)
            { if (first_ask == CTRUE)
               { princ_string(((char*)"<h3>Instances</h3>"));
                first_ask= (CFALSE);
                }
              else princ_string(((char*)", "));
                princ_string(((char*)""));
              (*Language.self_html)(x);
              }
            }
          }
        }
      print_doc_doc_context1(ctx,GC_STRING(self->documentation),Kernel.nil,GC_OBJECT(list,list::alloc(1,_string_(self->name))));
      }
    GC_UNBIND; POP_SIGNAL;}
  


// **********************************************************************
// *   Part 1: generation of item headers                               *
// **********************************************************************
// The c++ function for: start_item_header(self:doc_entity,ctx:doc_context,n%:integer) [NEW_ALLOC]
CL_EXPORT void  start_item_header_doc_entity1(Reader_doc_entity *self,Reader_doc_context *ctx,int n_Z) { 
    princ_string(((char*)"<a name='"));
    print_oid_any1(_oid_(self));
    princ_string(((char*)"'><hr size=0 style='page-break-after: avoid' /></a>\n\t<a name='"));
    (*Language.echo)(_oid_(Kernel.name),
      _oid_(self));
    princ_string(((char*)"'><hr size=0 /></a>\n\t<table width='100%' class='item_header'>\n\t\t<tr>\n\t\t\t<td width='"));
    (*Language.echo)(((OID)n_Z));
    princ_string(((char*)"%' align='left'><i>"));
    category_index_href_doc_context1(ctx);
    princ_string(((char*)"</i></td>\n\t\t\t<td width='"));
    (*Language.echo)(((OID)n_Z));
    princ_string(((char*)"%' align='center'><i>"));
    if (((self->category == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     item_href_doc_context2(ctx,self->category);
    princ_string(((char*)"</i></td>"));
    ;POP_SIGNAL;}
  


// The c++ function for: end_item_header(self:doc_entity,ctx:doc_context,n%:integer,kind:string) [NEW_ALLOC]
CL_EXPORT void  end_item_header_doc_entity1(Reader_doc_entity *self,Reader_doc_context *ctx,int n_Z,char *kind) { 
    princ_string(((char*)"<td width='"));
    (*Language.echo)(((OID)n_Z));
    princ_string(((char*)"%' align='right'><i>"));
    if (self->xl_ask == CTRUE)
     princ_string(((char*)"<font color='red'>[XL]</font> "));
    princ_string(((char*)""));
    (*Language.self_html)(_oid_(Kernel.definition),
      _oid_(self->ident));
    princ_string(((char*)" "));
    (*Language.echo)(_string_(kind));
    princ_string(((char*)"</i></td>\n\t</tr></table>"));
    ;POP_SIGNAL;}
  


// The c++ function for: item_header(self:doc_global,ctx:doc_context) [NEW_ALLOC]
CL_EXPORT void  item_header_doc_global1(Reader_doc_global *self,Reader_doc_context *ctx) { 
    start_item_header_doc_entity1(self,ctx,20);
    princ_string(((char*)"<td width='20%' align='center'></td>\n\t<td width='20%' align='center'></td>"));
    end_item_header_doc_entity1(self,ctx,20,((equal(self->grange,_oid_(Kernel.emptySet)) == CTRUE) ?
      ((char*)"constant") :
      ((char*)"global variable") ));
    POP_SIGNAL;}
  


// The c++ function for: item_header(self:doc_table,ctx:doc_context) [NEW_ALLOC]
CL_EXPORT void  item_header_doc_table1(Reader_doc_table *self,Reader_doc_context *ctx) { 
    start_item_header_doc_entity1(self,ctx,20);
    princ_string(((char*)"<td width='20%' align='center'></td>\n\t<td width='20%' align='center'></td>"));
    end_item_header_doc_entity1(self,ctx,20,((char*)"table"));
    POP_SIGNAL;}
  


// The c++ function for: item_header(self:doc_method,ctx:doc_context) [NEW_ALLOC]
CL_EXPORT void  item_header_doc_method1(Reader_doc_method *self,Reader_doc_context *ctx) { 
    
    GC_BIND;
    start_item_header_doc_entity1(self,ctx,20);
    princ_string(((char*)"<td width='20%' align='center'><i>"));
    if (self->inline_ask == CTRUE)
     princ_string(((char*)"inline"));
    else if ((OBJECT(ClaireBoolean,(*Kernel._sup)(GC_OID((*Kernel.dispatcher)(self->source)),
      ((OID)0)))) == CTRUE)
     princ_string(((char*)"fast dispatch"));
    else princ_string(((char*)"normal dispatch"));
      princ_string(((char*)"</i></td>\n\t<td width='20%' align='center'><i>"));
    if (INHERIT(OWNER(self->source),Kernel._operation))
     princ_string(((char*)"operation"));
    princ_string(((char*)"</i></td>"));
    end_item_header_doc_entity1(self,ctx,20,((char*)"method"));
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: item_header(self:doc_class,ctx:doc_context) [NEW_ALLOC]
CL_EXPORT void  item_header_doc_class1(Reader_doc_class *self,Reader_doc_context *ctx) { 
    start_item_header_doc_entity1(self,ctx,20);
    princ_string(((char*)"<td width='20%' align='center'><i>"));
    { OID  c = self->superclass;
      if ((*Kernel.open)(c) == ((OID)0))
       princ_string(((char*)"abstract"));
      else if ((*Kernel.open)(c) == ((OID)1))
       princ_string(((char*)"final"));
      else if ((*Kernel.open)(c) == ((OID)4))
       princ_string(((char*)"ephemeral"));
      else princ_string(((char*)"open"));
        }
    princ_string(((char*)"</i></td>\n\t<td width='20%'></td>"));
    end_item_header_doc_entity1(self,ctx,20,((char*)"class"));
    POP_SIGNAL;}
  


// The c++ function for: item_header(self:doc_interface,ctx:doc_context) [NEW_ALLOC]
CL_EXPORT void  item_header_doc_interface1(Reader_doc_interface *self,Reader_doc_context *ctx) { 
    
    GC_BIND;
    start_item_header_doc_entity1(self,ctx,20);
    princ_string(((char*)"<td width='20%' align='center'><i>"));
    if ((OBJECT(ClaireBoolean,(*Kernel._sup)(GC_OID((*Kernel.dispatcher)(self->source)),
      ((OID)0)))) == CTRUE)
     princ_string(((char*)"fast dispatch"));
    else princ_string(((char*)"normal dispatch"));
      princ_string(((char*)"</i></td>\n\t\t\t<td  width='20%'></td>"));
    end_item_header_doc_entity1(self,ctx,20,((char*)"interface"));
    GC_UNBIND; POP_SIGNAL;}
  


// **********************************************************************
// *   Part 1: HTML tools                                               *
// **********************************************************************
// The c++ function for: file_inline_css_style(_CL_obj:void) [0]
CL_EXPORT void  file_inline_css_style_void1() { 
    princ_string(((char*)"<style>\nbody {\n        font-size: 14px;\n        font-family: arial, Helvetica;\n}\n\nh1 { font-size: 25px; }\nh2 { font-size: 20px; }\n\na[href] {\n\tborder-bottom: 1px dotted grey;\n\ttext-decoration: none\n}\n\n.doc_paragraph\n{\n        font-size: 14px;\n        font-family: arial, helvetica;\n}\n\n.item_header { font-size: 10px; page-break-before: avoid; page-break-inside: avoid; page-break-after: avoid }\n\n.item_index {\n\t\twhite-space: pre;\n        font-size: 11px;\n        font-family: monaco, courier, mono-space;\n}\n\n.table_code {\n\t\tmargin: 10px auto;\n}\n\n.doc_code {\n    white-space: pre;\n\t\tpadding-top: .1em;\n\t\tpadding-bottom: .5em;\n\t\tbackground-color: #EEE;\n\t\tborder: #AAA solid 1px;\n        font-size: 11px;\n        font-family: monaco, courier, mono-space;\n}\n\n.opt_usage {\n\t\tmargin-left: 1em;\n\t\tmargin-right: 1em;\n\t\tpadding: .2em;\n\t\tbackground-color: #EEE;\n\t\tborder: #AAA solid 1px;\n        font-family: monaco, courier, mono-space;\n\t\n}\n\n.class_proto {\n\tvertical-align: top;\n\ttext-align: right;\n}\n\n.class_proto_super {\n\tvertical-align: top;\n\ttext-align: right;\n}\n\n.class_proto_slot {\n\tvertical-align: top;\n\ttext-align: left;\n}\n\n</style>"));
    ;POP_SIGNAL;}
  


// The c++ function for: html_file_header(self:doc_context) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT void  html_file_header_doc_context1(Reader_doc_context *self) { 
    
    GC_BIND;
    princ_string(((char*)"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n<html>\n\t<head>\n\t\t<title>\n\t\t\t"));
    { OID  g0973UU;
      { if ((CL_INT)LENGTH_STRING(string_v(Reader.DOC_TITLE->value)) > (CL_INT)0)
         g0973UU = Reader.DOC_TITLE->value;
        else g0973UU = _oid_(self->source);
          GC_OID(g0973UU);}
      (*Language.self_html)(g0973UU);
      }
    princ_string(((char*)" documentation\n\t\t</title>\n\t\t"));
    file_inline_css_style_void1();
    princ_string(((char*)"\n\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"doc.css\" media=\"all\">\n\t</head>\n\t<body>\n\t<h1><span class=pretitle>&nbsp;</span>&nbsp;"));
    { OID  g0974UU;
      { if ((CL_INT)LENGTH_STRING(string_v(Reader.DOC_TITLE->value)) > (CL_INT)0)
         g0974UU = Reader.DOC_TITLE->value;
        else g0974UU = _oid_(self->source);
          GC_OID(g0974UU);}
      (*Language.self_html)(g0974UU);
      }
    princ_string(((char*)" "));
    if (self->source == claire.it)
     { princ_string(((char*)"v"));
      princ_string(release_void());
      princ_string(((char*)" "));
      }
    else if (((self->source->version == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     { princ_string(self->source->version);
      princ_string(((char*)" "));
      }
    princ_string(((char*)""));
    if ((OBJECT(ClaireBoolean,Reader._starcode_doc_star->value)) == CTRUE)
     princ_string(((char*)"documentation"));
    else if ((OBJECT(ClaireBoolean,Reader._starexpl_doc_star->value)) == CTRUE)
     princ_string(((char*)"exploitation documentation"));
    else princ_string(((char*)"user manual"));
      princ_string(((char*)"</h1>"));
    princ_string(((char*)"<p><i>Last updated : "));
    (*Language.self_html)(GC_OID(_string_(strftime_string(((char*)"%a, %d %b %Y"),now_void()))));
    princ_string(((char*)"</i></p>"));
    ;GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: html_file_header(self:doc_context,kind:string) [NEW_ALLOC]
CL_EXPORT void  html_file_header_doc_context2(Reader_doc_context *self,char *kind) { 
    princ_string(((char*)"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n<html>\n\t<head>\n\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"doc.css\" media=\"all\">\n\t\t<title>\n\t\t\t"));
    (*Language.self_html)(_oid_(Kernel.source),
      _oid_(self));
    princ_string(((char*)" "));
    (*Language.self_html)(_string_(kind));
    princ_string(((char*)"\n\t\t</title>\n\t\t"));
    file_inline_css_style_void1();
    princ_string(((char*)"\n\t</head>\n\t<h1><span class=pretitle>&nbsp;</span>&nbsp;"));
    (*Language.self_html)(_oid_(Kernel.source),
      _oid_(self));
    princ_string(((char*)" "));
    (*Language.self_html)(_string_(kind));
    princ_string(((char*)"\n\t<body>"));
    ;POP_SIGNAL;}
  


// The c++ function for: html_file_header(self:doc_context,x:doc_item) [NEW_ALLOC]
CL_EXPORT void  html_file_header_doc_context3(Reader_doc_context *self,Reader_doc_item *x) { 
    princ_string(((char*)"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n<html>\n\t<head>\n\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"doc.css\" media=\"all\">\n\t\t<title>\n\t\t\t"));
    (*Language.self_html)(_oid_(Kernel.source),
      _oid_(self));
    princ_string(((char*)" : "));
    (*Language.self_html)(_oid_(Kernel.name),
      _oid_(x));
    princ_string(((char*)"\n\t\t</title>\n\t\t"));
    file_inline_css_style_void1();
    princ_string(((char*)"\n\t</head>\n\t<body>"));
    ;POP_SIGNAL;}
  


// The c++ function for: html_file_footer(_CL_obj:void) [0]
CL_EXPORT void  html_file_footer_void1() { 
    princ_string(((char*)"</body>\n\t</html>"));
    ;POP_SIGNAL;}
  


// The c++ function for: category_index_href(self:doc_context) [NEW_ALLOC]
CL_EXPORT void  category_index_href_doc_context1(Reader_doc_context *self) { 
    if (((OID)self->generation_mode) == (OID)(0))
     { princ_string(((char*)"<a href='#__category_index__'>categories</a>"));
      ;}
    else { princ_string(((char*)"<a href='"));
        (*Language.echo)(_oid_(Kernel.index),
          _oid_(self));
        princ_string(((char*)"#__category_index__'>categories</a>"));
        ;}
      POP_SIGNAL;}
  


// The c++ function for: option_index_href(self:doc_context) [NEW_ALLOC]
CL_EXPORT void  option_index_href_doc_context1(Reader_doc_context *self) { 
    if (((OID)self->generation_mode) == (OID)(0))
     { princ_string(((char*)"<a href='#__option_index__'>option index</a>"));
      ;}
    else { princ_string(((char*)"<a href='"));
        (*Language.echo)(_oid_(Kernel.index),
          _oid_(self));
        princ_string(((char*)"#__option_index__'>option index</a>"));
        ;}
      POP_SIGNAL;}
  


// The c++ function for: section_index_href(self:doc_context,sec:doc_section) [NEW_ALLOC]
CL_EXPORT void  section_index_href_doc_context1(Reader_doc_context *self,Reader_doc_section *sec) { 
    if (((OID)self->generation_mode) == (OID)(0))
     { princ_string(((char*)"<a href='#"));
      print_oid_any1(_oid_(sec));
      princ_string(((char*)"'>"));
      (*Language.self_html)(_oid_(Kernel.name),
        _oid_(sec));
      princ_string(((char*)"</a>"));
      ;}
    else { princ_string(((char*)"<a href='"));
        (*Language.echo)(_oid_(Kernel.index),
          _oid_(self));
        princ_string(((char*)"#"));
        print_oid_any1(_oid_(sec));
        princ_string(((char*)"'>"));
        (*Language.self_html)(_oid_(Kernel.name),
          _oid_(sec));
        princ_string(((char*)"</a>"));
        ;}
      POP_SIGNAL;}
  


// The c++ function for: item_href(self:doc_context,x:doc_link) [NEW_ALLOC]
CL_EXPORT void  item_href_doc_context1(Reader_doc_context *self,Reader_doc_link *x) { 
    princ_string(((char*)"<a href='"));
    princ_string(x->src);
    princ_string(((char*)"#"));
    princ_string(x->oid);
    princ_string(((char*)"'><font color='#"));
    (*Language.echo)(_oid_(Kernel.color),
      _oid_(self));
    princ_string(((char*)"'>"));
    (*Language.self_html)(_oid_(Kernel.name),
      _oid_(x));
    princ_string(((char*)"</font></a>"));
    ;POP_SIGNAL;}
  


// The c++ function for: item_href(self:doc_context,x:doc_item) [NEW_ALLOC]
CL_EXPORT void  item_href_doc_context2(Reader_doc_context *self,Reader_doc_item *x) { 
    princ_string(((char*)"<a href='"));
    if ((((OID)self->generation_mode) != (OID)(0)) && 
        (INHERIT(x->isa,Reader._doc_category)))
     { (*Reader.item_file)(_oid_(self),
        _oid_(x));
      princ_string(((char*)"#"));
      print_oid_any1(_oid_(x));
      }
    else { (*Reader.item_file)(_oid_(self),
          _oid_(x));
        princ_string(((char*)"#"));
        if ((INHERIT(x->isa,Reader._doc_entity)) && 
            ((((CLREAD(Reader_doc_entity,x,category) == (NULL)) ? CTRUE : CFALSE) != CTRUE) && 
              (LENGTH_STRING(x->documentation) == 0)))
         { princ_string(((char*)""));
          print_oid_any1(_oid_(CLREAD(Reader_doc_entity,x,category)));
          }
        else { princ_string(((char*)""));
            print_oid_any1(_oid_(x));
            }
          }
      princ_string(((char*)"'>"));
    if ((CL_INT)LENGTH_STRING(self->color) > (CL_INT)0)
     { princ_string(((char*)"<font color='#"));
      (*Language.echo)(_oid_(Kernel.color),
        _oid_(self));
      princ_string(((char*)"'>"));
      ;}
    princ_string(((char*)""));
    (*Language.self_html)(_oid_(Kernel.name),
      _oid_(x));
    if ((CL_INT)LENGTH_STRING(self->color) > (CL_INT)0)
     { princ_string(((char*)"</font>"));
      ;}
    princ_string(((char*)"</a>"));
    ;POP_SIGNAL;}
  


// The c++ function for: item_href(self:doc_context,x:doc_link,w:string) [NEW_ALLOC]
CL_EXPORT void  item_href_doc_context3(Reader_doc_context *self,Reader_doc_link *x,char *w) { 
    princ_string(((char*)"<a href='"));
    princ_string(x->src);
    princ_string(((char*)"#"));
    princ_string(x->oid);
    princ_string(((char*)"'><font color='#"));
    (*Language.echo)(_oid_(Kernel.color),
      _oid_(self));
    princ_string(((char*)"'>"));
    (*Language.self_html)(_string_(w));
    princ_string(((char*)"</font></a>"));
    ;POP_SIGNAL;}
  


// The c++ function for: item_href(self:doc_context,x:doc_item,w:string) [NEW_ALLOC]
CL_EXPORT void  item_href_doc_context4(Reader_doc_context *self,Reader_doc_item *x,char *w) { 
    princ_string(((char*)"<a href='"));
    if ((((OID)self->generation_mode) != (OID)(0)) && 
        (INHERIT(x->isa,Reader._doc_category)))
     { (*Reader.item_file)(_oid_(self),
        _oid_(x));
      princ_string(((char*)"#"));
      print_oid_any1(_oid_(x));
      }
    else { (*Reader.item_file)(_oid_(self),
          _oid_(x));
        princ_string(((char*)"#"));
        if ((INHERIT(x->isa,Reader._doc_entity)) && 
            ((((CLREAD(Reader_doc_entity,x,category) == (NULL)) ? CTRUE : CFALSE) != CTRUE) && 
              (LENGTH_STRING(x->documentation) == 0)))
         { princ_string(((char*)""));
          print_oid_any1(_oid_(CLREAD(Reader_doc_entity,x,category)));
          }
        else { princ_string(((char*)""));
            print_oid_any1(_oid_(x));
            }
          }
      princ_string(((char*)"'><font color='#"));
    (*Language.echo)(_oid_(Kernel.color),
      _oid_(self));
    princ_string(((char*)"'>"));
    (*Language.self_html)(_string_(w));
    princ_string(((char*)"</font></a>"));
    ;POP_SIGNAL;}
  


// The c++ function for: item_href(self:doc_context,x:doc_section,w:string) [NEW_ALLOC]
CL_EXPORT void  item_href_doc_context5(Reader_doc_context *self,Reader_doc_section *x,char *w) { 
    if ((CL_INT)LENGTH_STRING(self->color) > (CL_INT)0)
     { princ_string(((char*)"<font color='#"));
      (*Language.echo)(_oid_(Kernel.color),
        _oid_(self));
      princ_string(((char*)"'>"));
      (*Language.self_html)(_string_(w));
      princ_string(((char*)"</font>"));
      ;}
    else { princ_string(((char*)""));
        (*Language.self_html)(_string_(w));
        princ_string(((char*)""));
        ;}
      POP_SIGNAL;}
  


// The c++ function for: item_file(self:doc_context,x:doc_category) [0]
CL_EXPORT void  item_file_doc_context1(Reader_doc_context *self,Reader_doc_category *x) { 
    if (((OID)self->generation_mode) != (OID)(0))
     { c_princ_string(x->name);
      princ_string(((char*)".html"));
      }
    princ_string(((char*)""));
    ;POP_SIGNAL;}
  


// The c++ function for: item_file(self:doc_context,x:doc_option) [0]
CL_EXPORT void  item_file_doc_context2(Reader_doc_context *self,Reader_doc_option *x) { 
    if (((OID)self->generation_mode) != (OID)(0))
     { princ_string(self->source->name->name);
      princ_string(((char*)".option.html"));
      }
    princ_string(((char*)""));
    ;POP_SIGNAL;}
  


// The c++ function for: item_file(self:doc_context,x:doc_entity) [0]
CL_EXPORT void  item_file_doc_context3(Reader_doc_context *self,Reader_doc_entity *x) { 
    item_file_doc_context1(self,x->category);
    POP_SIGNAL;}
  


// The c++ function for: set_item_module(x:doc_entity) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  set_item_module_doc_entity1(Reader_doc_entity *x) { 
    (Reader.RESTORE_MODULE->value= _oid_(ClEnv->module_I));
    if (((x->ident->definition == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     _void_(ClEnv->module_I = x->ident->definition);
    else _void_(ClEnv->module_I = x->ident->module_I);
      POP_SIGNAL;}
  


// The c++ function for: restore_module(_CL_obj:void) [SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  restore_module_void1() { 
    _void_(ClEnv->module_I = OBJECT(module,Reader.RESTORE_MODULE->value));
    POP_SIGNAL;}
  


// The c++ function for: entity_print(x:doc_entity,ctx:doc_context,e:any) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  entity_print_doc_entity1(Reader_doc_entity *x,Reader_doc_context *ctx,OID e) { 
    set_item_module_doc_entity1(x);
    princ_string(((char*)""));
    (*Language.self_html)(e);
    restore_module_void1();
    POP_SIGNAL;}
  


// The c++ function for: item_prototype(x:doc_global,ctx:doc_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  item_prototype_doc_global1(Reader_doc_global *x,Reader_doc_context *ctx) { 
    set_item_module_doc_entity1(x);
    princ_string(((char*)"<font color='blue'>"));
    if (x->constant_ask == CTRUE)
     princ_string(((char*)" :: "));
    else princ_string(((char*)" : "));
      princ_string(((char*)"</font>"));
    if (x->constant_ask != CTRUE)
     { princ_string(((char*)""));
      (*Language.self_html)(_oid_(Reader.grange),
        _oid_(x));
      princ_string(((char*)"<font color='blue'> := </font>"));
      ;}
    princ_string(((char*)""));
    (*Language.self_html)(_oid_(Kernel.value),
      _oid_(x));
    princ_string(((char*)""));
    ;restore_module_void1();
    POP_SIGNAL;}
  


// The c++ function for: item_prototype(x:doc_table,ctx:doc_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  item_prototype_doc_table1(Reader_doc_table *x,Reader_doc_context *ctx) { 
    
    GC_BIND;
    set_item_module_doc_entity1(x);
    princ_string(((char*)"["));
    { list * l = GC_OBJECT(list,OBJECT(list,(*Core.args)(GC_OID((*Kernel.arg)(GC_OID(x->source))))));
      CL_INT  len = l->length;
      CL_INT  i = 2;
      CL_INT  g0975 = len;
      { CL_INT loop_handle = ClEnv->cHandle;
        while (((CL_INT)i <= (CL_INT)g0975))
        { if ((CL_INT)i > (CL_INT)2)
           princ_string(((char*)", "));
          { OID  v = (*(l))[i];
            princ_string(((char*)""));
            (*Language.self_html)(_oid_(Kernel.name),
              _oid_(OBJECT(Variable,v)->pname));
            princ_string(((char*)"<font color=blue>:</font>"));
            (*Language.self_html)(_oid_(Kernel.range),
              v);
            }
          ++i;
          POP_SIGNAL;}
        }
      }
    princ_string(((char*)"] <font color=blue>:</font> "));
    (*Language.self_html)(_oid_(Reader.trange),
      _oid_(x));
    princ_string(((char*)" <font color=blue>:=</font> "));
    (*Language.self_html)(_oid_(Reader.tbody),
      _oid_(x));
    princ_string(((char*)"\n\t"));
    ;restore_module_void1();
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: item_prototype(x:doc_interface,ctx:doc_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  item_prototype_doc_interface1(Reader_doc_interface *x,Reader_doc_context *ctx) { 
    set_item_module_doc_entity1(x);
    princ_string(((char*)"<font color='blue'> :: </font>"));
    (*Language.self_html)(_oid_(Kernel.arg),
      _oid_(x));
    princ_string(((char*)"("));
    { ClaireBoolean * first_ask = CTRUE;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(y);
        for (START(x->args); NEXT(y);)
        { if (first_ask == CTRUE)
           first_ask= (CFALSE);
          else princ_string(((char*)", "));
            princ_string(((char*)""));
          (*Language.self_html)(y);
          }
        }
      }
    princ_string(((char*)")"));
    restore_module_void1();
    POP_SIGNAL;}
  


// The c++ function for: item_prototype(x:doc_class,ctx:doc_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  item_prototype_doc_class1(Reader_doc_class *x,Reader_doc_context *ctx) { 
    
    GC_BIND;
    set_item_module_doc_entity1(x);
    princ_string(((char*)"<font color='blue'> &lt;: </font>"));
    ;{ OID  e = GC_OID(string2item_doc_context1(ctx,OBJECT(symbol,(*Kernel.name)(x->superclass))->name));
      if (e != CNULL)
       (*Reader.item_href)(_oid_(ctx),
        e);
      else { princ_string(((char*)""));
          (*Language.self_html)(_oid_(Kernel.superclass),
            _oid_(x));
          }
        }
    restore_module_void1();
    GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: item_prototype(x:doc_method,ctx:doc_context) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
CL_EXPORT void  item_prototype_doc_method1(Reader_doc_method *x,Reader_doc_context *ctx) { 
    
    GC_BIND;
    set_item_module_doc_entity1(x);
    princ_string(((char*)"("));
    { ClaireBoolean * first_ask = CTRUE;
      CL_INT  i = 1;
      CL_INT  g0976 = x->vars->length;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)i <= (CL_INT)g0976))
        { GC_LOOP;
          if (first_ask == CTRUE)
           first_ask= (CFALSE);
          else { princ_string(((char*)", "));
              ;}
            princ_string(((char*)"<font color='green'>"));
          (*Language.self_html)((*(x->vars))[i]);
          princ_string(((char*)"</font><font color='blue'>:</font>"));
          (*Language.self_html)((*(x->var_ranges))[i]);
          ++i;
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    princ_string(((char*)")<font color='blue'> "));
    if (x->inline_ask == CTRUE)
     princ_string(((char*)"="));
    else princ_string(((char*)"-"));
      princ_string(((char*)"&gt; </font>"));
    (*Language.self_html)(_oid_(Reader.mrange),
      _oid_(x));
    princ_string(((char*)""));
    ;restore_module_void1();
    GC_UNBIND; POP_SIGNAL;}
  


// **********************************************************************
// *   Part 1: markdown like parser                                     *
// **********************************************************************
// The c++ function for: princ_doc_word(self:doc_context,w:string,vnames:list[string]) [NEW_ALLOC]
CL_EXPORT void  princ_doc_word_doc_context1(Reader_doc_context *self,char *w,list *vnames) { 
    { ClaireBoolean * b_ask = ((self->bold_ask == CTRUE) ? CTRUE : ((contain_ask_list(vnames,_string_(w)) == CTRUE) ? CTRUE : CFALSE));
      if (b_ask == CTRUE)
       princ_string(((char*)"<b>"));
      if ((CL_INT)LENGTH_STRING(self->color) > (CL_INT)0)
       { princ_string(((char*)"<font color='#"));
        princ_string(self->color);
        princ_string(((char*)"'>"));
        }
      else princ_string(((char*)"<font color='black'>"));
        princ_string(((char*)""));
      (*Language.self_html)(_string_(w));
      princ_string(((char*)"</font>"));
      if (b_ask == CTRUE)
       princ_string(((char*)"</b>"));
      }
    POP_SIGNAL;}
  


// The c++ function for: print_doc_word(self:doc_context,w:string,vnames:list[string],exclude:list[string]) [NEW_ALLOC+SLOT_UPDATE]
CL_EXPORT void  print_doc_word_doc_context1(Reader_doc_context *self,char *w,list *vnames,list *exclude) { 
    
    GC_BIND;
    if (contain_ask_list(vnames,_string_(w)) == CTRUE)
     { princ_string(((char*)"<b>"));
      (*Language.self_html)(_string_(w));
      princ_string(((char*)"</b>"));
      ;}
    else if ((LENGTH_STRING(w) == 0) || 
        (space_ask_string(w) == CTRUE))
     princ_string(w);
    else if (self->in_a_ask == CTRUE)
     { princ_string(((char*)""));
      (*Language.self_html)(_string_(w));
      }
    else if ((contain_ask_set(OBJECT(set,Reader.IGNORE_WORDS->value),_string_(w)) == CTRUE) || 
        (contain_ask_list(exclude,_string_(lower_string(w))) == CTRUE))
     { if (LENGTH_STRING(self->color) == 0)
       { princ_string(((char*)""));
        (*Language.self_html)(_string_(w));
        }
      else princ_doc_word_doc_context1(self,w,vnames);
        }
    else { OID  x = GC_OID(string2item_doc_context1(self,w));
        if (x != CNULL)
         (*Reader.item_href)(_oid_(self),
          x,
          _string_(w));
        else { princ_string(((char*)""));
            (*Language.self_html)(_string_(w));
            }
          }
      GC_UNBIND; POP_SIGNAL;}
  


// The c++ function for: isnext?(self:port,s:string) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * isnext_ask_port1(PortObject *self,char *s) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      { char * tmp = GC_STRING(fread_port4(self,LENGTH_STRING(s)));
        if (equal_string(tmp,s) == CTRUE)
         Result = CTRUE;
        else { unget_port1(self,tmp);
            Result = CFALSE;
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: checknext?(self:port,s:string) [NEW_ALLOC]
CL_EXPORT ClaireBoolean * checknext_ask_port1(PortObject *self,char *s) { 
    
    GC_BIND;
    { ClaireBoolean *Result ;
      { char * tmp = GC_STRING(fread_port4(self,LENGTH_STRING(s)));
        unget_port1(self,tmp);
        Result = ((equal_string(tmp,s) == CTRUE) ? CTRUE : CFALSE);
        }
      GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  


// The c++ function for: print_doc(self:doc_context,doc:string,vnames:list[string],exclude:list[string]) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
CL_EXPORT void  print_doc_doc_context1(Reader_doc_context *self,char *doc,list *vnames,list *exclude) { 
    
    GC_BIND;
    princ_string(((char*)"<p align='justify' class='doc_paragraph'>"));
    { blob * b = GC_OBJECT(blob,blob_I_string1(doc));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) b))) != Kernel.ctrue))
        { GC_LOOP;
          { tuple * g0977 = freadline_port4(b,OBJECT(bag,Reader.DOC_STOP->value));
            char * w = GC_STRING(string_v((*(g0977))[1]));
            OID  dum = GC_OID((*(g0977))[2]);
            print_doc_word_doc_context1(self,w,vnames,exclude);
            _void_(self->bold_ask = CFALSE);
            _void_(self->color = ((char*)""));
            if (equal(dum,_string_(((char*)"%%"))) == CTRUE)
             princ_char(getc_port1(b));
            else if (equal(dum,_string_(((char*)"\\"))) == CTRUE)
             { tuple * g0978 = freadline_port4(b,OBJECT(bag,Reader.TAG_STOP->value));
              char * tag = GC_STRING(string_v((*(g0978))[1]));
              OID  sdum = GC_OID((*(g0978))[2]);
              if (equal_string(tag,((char*)"br")) == CTRUE)
               princ_string(((char*)"</p><p align='justify' class='doc_paragraph'>"));
              else if (equal_string(tag,((char*)"xl")) == CTRUE)
               princ_string(((char*)"<font color='red'>[XL]</font> "));
              else if (equal_string(tag,((char*)"bs")) == CTRUE)
               princ_string(((char*)"\\"));
              else if (equal_string(tag,((char*)"def")) == CTRUE)
               { princ_string(((char*)"</p>\n\t\t\t\t\t\t\t\t\t<table align='center' width='80%'>\n\t\t\t\t\t\t\t\t\t<tr><td><p align='justify' class='doc_paragraph'>\n\t\t\t\t\t\t\t\t\t\t<b>Definition : </b><i>"));
                ;}
              else if (equal_string(tag,((char*)"/def")) == CTRUE)
               { princ_string(((char*)"</i></p></td></tr></table>\n\t\t\t\t\t\t\t\t\t<p align='justify' class='doc_paragraph'>"));
                ;}
              else if (equal_string(tag,((char*)"h3")) == CTRUE)
               { princ_string(((char*)"</p>\n\t\t\t\t\t\t\t  <h3><span class=pretitle>&nbsp;</span>&nbsp;"));
                ;}
              else if (equal_string(tag,((char*)"/h3")) == CTRUE)
               { princ_string(((char*)"</h3>\n\t\t\t\t\t\t\t  <p align='justify' class='doc_paragraph'>"));
                ;}
              else if (equal_string(tag,((char*)"center")) == CTRUE)
               { princ_string(((char*)"</p>\n\t\t\t\t\t\t\t  <center>"));
                ;}
              else if (equal_string(tag,((char*)"/center")) == CTRUE)
               { princ_string(((char*)"</center>\n\t\t\t\t\t\t\t  <p align='justify' class='doc_paragraph'>"));
                ;}
              else if (equal_string(tag,((char*)"ul")) == CTRUE)
               { princ_string(((char*)"</p>\n\t\t\t\t\t\t\t  <ul>"));
                ;}
              else if (equal_string(tag,((char*)"/ul")) == CTRUE)
               { princ_string(((char*)"</ul>\n\t\t\t\t\t\t\t  <p align='justify' class='doc_paragraph'>"));
                ;}
              else if (equal_string(tag,((char*)"include")) == CTRUE)
               { ClaireHandler c_handle = ClaireHandler();
                if ERROR_IN 
                { { buffer * f = GC_OBJECT(buffer,fopen_string1(GC_STRING(freadline_port(b)),((char*)"r")));
                    freadwrite_port3(f,GC_OBJECT(PortObject,ClEnv->cout));
                    fclose_port1(f);
                    }
                  ERROR_FREE;}
                else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                { c_handle.catchIt();;}
                else PREVIOUS_HANDLER;}
              else if (equal_string(tag,((char*)"filedump")) == CTRUE)
               { ClaireHandler c_handle = ClaireHandler();
                if ERROR_IN 
                { { buffer * f = GC_OBJECT(buffer,fopen_string1(GC_STRING(freadline_port(b)),((char*)"r")));
                    princ_string(((char*)"</p><table class='table_code' align=center border=0 width='85%'>\n\t\t\t\t\t\t\t\t\t\t  <tr><td class='doc_code'>"));
                    { CL_INT loop_handle = ClEnv->cHandle;
                      OID gc_local;
                      while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) f))) != Kernel.ctrue))
                      { GC_LOOP;
                        { tuple * g0979 = freadline_port4(f,OBJECT(bag,Reader.DOC_STOP->value));
                          char * a = GC_STRING(string_v((*(g0979))[1]));
                          OID  b = GC_OID((*(g0979))[2]);
                          print_doc_word_doc_context1(self,a,vnames,exclude);
                          princ_string(((char*)""));
                          { OID  g0981UU;
                            { if (INHERIT(OWNER(b),Kernel._char))
                               g0981UU = _string_(string_I_char1(OBJECT(ClaireChar,b)));
                              else g0981UU = b;
                                GC_OID(g0981UU);}
                            (*Language.self_html)(g0981UU);
                            }
                          }
                        GC_UNLOOP;POP_SIGNAL;}
                      }
                    princ_string(((char*)"</td></tr></table>\n\t\t\t\t\t\t\t        <p align='justify' class='doc_paragraph'>"));
                    fclose_port1(f);
                    }
                  ERROR_FREE;}
                else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                { c_handle.catchIt();;}
                else PREVIOUS_HANDLER;}
              else if (equal_string(tag,((char*)"code")) == CTRUE)
               { _void_(self->in_code_ask = CTRUE);
                princ_string(((char*)"</p><table class='table_code' align=center border=0 width='85%'>\n\t\t\t\t\t\t\t\t\t\t<tr><td class='doc_code'>"));
                }
              else if (equal_string(tag,((char*)"/code")) == CTRUE)
               { _void_(self->in_code_ask = CFALSE);
                _void_(self->color = ((char*)""));
                _void_(self->bold_ask = CFALSE);
                princ_string(((char*)"</td></tr></table>\n\t\t\t\t\t\t\t  <p align='justify' class='doc_paragraph'>"));
                }
              else { princ_string(((char*)"<"));
                  princ_string(tag);
                  if (equal_string(tag,((char*)"a")) == CTRUE)
                   _void_(self->in_a_ask = CTRUE);
                  else if (equal_string(tag,((char*)"/a")) == CTRUE)
                   _void_(self->in_a_ask = CFALSE);
                  if (sdum == _oid_(_char_(((unsigned char)'\\'))))
                   { CL_INT loop_handle = ClEnv->cHandle;
                    OID gc_local;
                    while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) b))) != Kernel.ctrue))
                    { GC_LOOP;
                      { tuple * g0980 = freadline_port4(b,GC_OBJECT(set,set::alloc(Kernel.emptySet,5,_oid_(_char_(((unsigned char)'\t'))),
                          _oid_(_char_(((unsigned char)'\n'))),
                          _oid_(_char_(((unsigned char)'\r'))),
                          _oid_(_char_(((unsigned char)' '))),
                          _oid_(_char_(((unsigned char)'\\'))))));
                        char * attr = GC_STRING(string_v((*(g0980))[1]));
                        OID  sep = GC_OID((*(g0980))[2]);
                        princ_string(((char*)" "));
                        princ_string(attr);
                        if (sep != _oid_(_char_(((unsigned char)'\\'))))
                         { ;GC_UNLOOP;ClEnv->cHandle = loop_handle; break;}
                        }
                      GC_UNLOOP;POP_SIGNAL;}
                    }
                  princ_string(((char*)">"));
                  }
                }
            else if (dum == _oid_(_char_(((unsigned char)'<'))))
             princ_string(((char*)"&lt;"));
            else if (dum == _oid_(_char_(((unsigned char)'>'))))
             princ_string(((char*)"&gt;"));
            else if ((dum == _oid_(_char_(((unsigned char)' ')))) && 
                (isnext_ask_port1(b,((char*)":")) == CTRUE))
             princ_string(((char*)"&nbsp;:"));
            else (*Kernel.princ)(dum);
              }
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    princ_string(((char*)"</p>"));
    ;GC_UNBIND; POP_SIGNAL;}
  




  

extern "C" CL_EXPORT void dynLoadReader() 
{ Reader.initModule("Reader",iClaire.it,list::alloc(Kernel.emptySet,3,_oid_(Kernel.it),
      _oid_(Core.it),
      _oid_(Language.it)),
    "./meta",list::alloc(Kernel._string,8,_string_(((char*)"read")),
      _string_(((char*)"syntax")),
      _string_(((char*)"file")),
      _string_(((char*)"inspect")),
      _string_(((char*)"complete")),
      _string_(((char*)"toplevel")),
      _string_(((char*)"wcl")),
      _string_(((char*)"codedoc"))));
    Reader.metaLoad();
    Reader.it->comment = "Reader";
    }
  /***** CLAIRE Compilation of file Reader.cl 
         [version 3.5.0 / safety 5] *****/



CL_EXPORT ReaderClass Reader;

// definition of the meta-model for Reader
  void ReaderClass::metaLoad() { 
    
    ClEnv->module_I = it;
// definition of the properties 
    
    Reader.s_index = property::make("s_index",Reader.it);
    Reader.fromp = property::make("fromp",Reader.it);
    Reader.nb_line = property::make("nb_line",Reader.it);
    Reader.firstc = property::make("firstc",Reader.it);
    Reader.last_form = property::make("last_form",Reader.it);
    Reader.maxstack = property::make("maxstack",Reader.it);
    Reader.toplevel = property::make("toplevel",Reader.it);
    Reader.eof = property::make("eof",Reader.it);
    Reader.space = property::make("space",Reader.it);
    Reader.tab = property::make("tab",Reader.it);
    Reader.bracket = property::make("bracket",Reader.it);
    Reader.paren = property::make("paren",Reader.it);
    Reader.comma = property::make("comma",Reader.it);
    Reader.curly = property::make("curly",Reader.it);
    Reader.next = property::make("next",Reader.it);
    Reader.keyword_ask = property::make("keyword?",Reader.it);
    Reader.stop_ask = property::make("stop?",Reader.it);
    Reader.nextunit = property::make("nextunit",Reader.it);
    Reader.nexts = property::make("nexts",Reader.it);
    Reader.loopexp = property::make("loopexp",Reader.it);
    Reader.nexte = property::make("nexte",Reader.it);
    Reader.nextexp = property::make("nextexp",Reader.it);
    Reader.nexti = property::make("nexti",Reader.it);
    Reader.read_escape = property::make("read_escape",Reader.it);
    Reader.nextvariable = property::make("nextvariable",Reader.it);
    Reader.nexts_I = property::make("nexts!",Reader.it);
    Reader.nexte_I = property::make("nexte!",Reader.it);
    Reader.extended_comment_ask = property::make("extended_comment?",Reader.it);
    Reader.extended_comment_I = property::make("extended_comment!",Reader.it);
    Reader.Call_I = property::make("Call!",Reader.it);
    Reader.operation_ask = property::make("operation?",Reader.it);
    Reader.combine = property::make("combine",Reader.it);
    Reader.combine_I = property::make("combine!",Reader.it);
    Reader.operation_I = property::make("operation!",Reader.it);
    Reader.operand_I = property::make("operand!",Reader.it);
    Reader.precedence_I = property::make("precedence!",Reader.it);
    Reader.nextstruct = property::make("nextstruct",Reader.it);
    Reader.readlet = property::make("readlet",Reader.it);
    Reader.readlet_star = property::make("readlet*",Reader.it);
    Reader.readwhen = property::make("readwhen",Reader.it);
    Reader.show = property::make("show",claire.it);
    Reader.readif = property::make("readif",Reader.it);
    Reader.readcase = property::make("readcase",Reader.it);
    Reader.readset = property::make("readset",Reader.it);
    Reader.dereference = property::make("dereference",Reader.it);
    Reader.nextseq = property::make("nextseq",Reader.it);
    Reader.readblock = property::make("readblock",claire.it);
    Reader.Do_I = property::make("Do!",Reader.it);
    Reader.readcall = property::make("readcall",Reader.it);
    Reader.nextdefinition = property::make("nextdefinition",Reader.it);
    Reader.nextmethod = property::make("nextmethod",Reader.it);
    Reader.nextinst = property::make("nextinst",Reader.it);
    Reader.nextDefclass = property::make("nextDefclass",Reader.it);
    Reader.useless_c = property::make("useless_c",Reader.it);
    Reader.skipc = property::make("skipc",Reader.it);
    Reader.skipc_I = property::make("skipc!",Reader.it);
    Reader.cnext = property::make("cnext",Reader.it);
    Reader.findeol = property::make("findeol",Reader.it);
    Reader.checkno = property::make("checkno",Reader.it);
    Reader.verify = property::make("verify",Reader.it);
    Reader.Serror = property::make("Serror",Reader.it);
    Reader.extract_variable = property::make("extract_variable",Reader.it);
    Reader.bind_I = property::make("bind!",Reader.it);
    Reader.unbind_I = property::make("unbind!",Reader.it);
    Reader.load_file = property::make("load_file",Reader.it);
    Reader.load = property::make("load",claire.it);
    Reader.sload = property::make("sload",claire.it);
    Reader.add_modules = property::make("add_modules",Reader.it);
    Reader.eload = property::make("eload",claire.it);
    Reader.print_exception = property::make("print_exception",Reader.it);
    Reader.hashgrow = property::make("hashgrow",mClaire.it);
    Reader.inspect_system = property::make("inspect_system",Reader.it);
    Reader.trace_rule = property::make("trace_rule",Reader.it);
    Reader.rtime = property::make("rtime",Reader.it);
    Reader.rdepth = property::make("rdepth",2,Reader.it);
    Reader.rnum = property::make("rnum",Reader.it);
    Reader.rloop = property::make("rloop",2,Reader.it);
    Reader.rstart = property::make("rstart",2,Reader.it);
    Reader.PRget = property::make("PRget",claire.it);
    Reader.PRlook = property::make("PRlook",claire.it);
    Reader.dependents = property::make("dependents",Reader.it);
    Reader.extract_of_type = property::make("extract_of_type",Reader.it);
    Reader.PRdepends = property::make("PRdepends",claire.it);
    Reader.PRshow = property::make("PRshow",claire.it);
    Reader.PRtime = property::make("PRtime",claire.it);
    Reader.PRcounter = property::make("PRcounter",claire.it);
    Reader.last_arrow = property::make("last_arrow",2,Reader.it);
    Reader.s_properties = property::make("s_properties",Reader.it);
    Reader.wcl_ask = property::make("wcl?",Reader.it);
    Reader.cascade_ask = property::make("cascade?",Reader.it);
    Reader.set_load_module = property::make("set_load_module",Reader.it);
    Reader.get_lines = property::make("get_lines",Reader.it);
    Reader.use_module = property::make("use_module",claire.it);
    Reader.add_parts = property::make("add_parts",Reader.it);
    Reader.add_subparts = property::make("add_subparts",Reader.it);
    Reader.add_uses = property::make("add_uses",Reader.it);
    Reader.insert_text = property::make("insert_text",Reader.it);
    Reader.delete_text = property::make("delete_text",Reader.it);
    Reader.reset_state = property::make("reset_state",2,Reader.it);
    Reader.get_cursor_position = property::make("get_cursor_position",Reader.it);
    Reader.get_text = property::make("get_text",Reader.it);
    Reader.display_list = property::make("display_list",Reader.it);
    Reader.completion_reset = property::make("completion_reset",Reader.it);
    Reader.explode_separators = property::make("explode_separators",Reader.it);
    Reader.same_tree_ask = property::make("same_tree?",Reader.it);
    Reader.complete_named_object = property::make("complete_named_object",Reader.it);
    Reader.complete_slot = property::make("complete_slot",Reader.it);
    Reader.complete_class = property::make("complete_class",Reader.it);
    Reader.nodup = property::make("nodup",Reader.it);
    Reader.fill_claire_matches = property::make("fill_claire_matches",Reader.it);
    Reader.match_prefix = property::make("match_prefix",Reader.it);
    Reader.method_description = property::make("method_description",Reader.it);
    Reader.class_description = property::make("class_description",Reader.it);
    Reader.claire_complete = property::make("claire_complete",Reader.it);
    Reader.bin_init = property::make("bin_init",Reader.it);
    Reader.fill_binaries = property::make("fill_binaries",Reader.it);
    Reader.fill_files = property::make("fill_files",Reader.it);
    Reader.shell_complete = property::make("shell_complete",Reader.it);
    Reader.extended_operator = property::make("extended_operator",Reader.it);
    Reader.inspect_loop = property::make("inspect_loop",claire.it);
    Reader.get_from_integer = property::make("get_from_integer",claire.it);
    Reader.reader_push = property::make("reader_push",Reader.it);
    Reader.reader_pop = property::make("reader_pop",Reader.it);
    Reader.cause = property::make("cause",Reader.it);
    Reader.reader_reset = property::make("reader_reset",Reader.it);
    Reader.dump_stack = property::make("dump_stack",claire.it);
    Reader.module_stack = property::make("module_stack",2,Reader.it);
    Reader.get_prompt = property::make("get_prompt",Reader.it);
    Reader.eval_command = property::make("eval_command",Reader.it);
    Reader.print_oid = property::make("print_oid",Reader.it);
    Reader.nl2br = property::make("nl2br",claire.it);
    Reader.wcl_start_ask = property::make("wcl_start?",Reader.it);
    Reader.read_wcl = property::make("read_wcl",Reader.it);
    Reader.read_top_wcl = property::make("read_top_wcl",Reader.it);
    Reader.fopen_source = property::make("fopen_source",claire.it);
    Reader.load_wcl_I = property::make("load_wcl!",Reader.it);
    Reader.add_wcl = property::make("add_wcl",claire.it);
    Reader.saved_system = property::make("saved_system",Reader.it);
    Reader.saved_reader = property::make("saved_reader",2,Reader.it);
    Reader.save_context = property::make("save_context",Reader.it);
    Reader.restore_context = property::make("restore_context",Reader.it);
    Reader.inspect_toplevel = property::make("inspect_toplevel",Reader.it);
    Reader.read_command = property::make("read_command",Reader.it);
    Reader.debug_loop = property::make("debug_loop",Reader.it);
    Reader.nextswcl = property::make("nextswcl",Reader.it);
    Reader.head_wcl_intruction_ask = property::make("head_wcl_intruction?",Reader.it);
    Reader.Call_wcl_I = property::make("Call_wcl!",Reader.it);
    Reader.build_call_wcl = property::make("build_call_wcl",Reader.it);
    Reader.build_top_call_wcl = property::make("build_top_call_wcl",Reader.it);
    Reader.debug_context_ask = property::make("debug_context?",Reader.it);
    Reader.src = property::make("src",Reader.it);
    Reader.line = property::make("line",Reader.it);
    Reader.leaf_wcl_intruction_ask = property::make("leaf_wcl_intruction?",Reader.it);
    Reader.close_toplevel_exception = property::make("close_toplevel_exception",Reader.it);
    Reader.show_source_lines = property::make("show_source_lines",Reader.it);
    Reader.show_frame = property::make("show_frame",Reader.it);
    Reader.show_frame_info = property::make("show_frame_info",Reader.it);
    Reader.add_ident = property::make("add_ident",Reader.it);
    Reader.set_eval_module = property::make("set_eval_module",Reader.it);
    Reader.hash_max = property::make("hash_max",2,Reader.it);
    Reader.content = property::make("content",Reader.it);
    Reader.hash_table_I = property::make("hash_table!",Reader.it);
    Reader.nkey = property::make("nkey",Reader.it);
    Reader.nval = property::make("nval",Reader.it);
    Reader.reset = property::make("reset",Reader.it);
    Reader.hash_value_oid = property::make("hash_value_oid",Reader.it);
    Reader.hash_value_string = property::make("hash_value_string",Reader.it);
    Reader.print_module = property::make("print_module",Reader.it);
    Reader.category_index_href = property::make("category_index_href",Reader.it);
    Reader.src_location = property::make("src_location",Reader.it);
    Reader.documentation = property::make("documentation",Reader.it);
    Reader.xl_ask = property::make("xl?",Reader.it);
    Reader.oid = property::make("oid",Reader.it);
    Reader.exploit_ask = property::make("exploit?",Reader.it);
    Reader.categories = property::make("categories",Reader.it);
    Reader.section = property::make("section",Reader.it);
    Reader.items = property::make("items",Reader.it);
    Reader.entity_names = property::make("entity_names",Reader.it);
    Reader.aliases = property::make("aliases",Reader.it);
    Reader.aname = property::make("aname",2,Reader.it);
    Reader.usage = property::make("usage",Reader.it);
    Reader.from_module = property::make("from_module",Reader.it);
    Reader.opts = property::make("opts",Reader.it);
    Reader.ranges = property::make("ranges",Reader.it);
    Reader.category = property::make("category",Reader.it);
    Reader.mrange = property::make("mrange",2,Reader.it);
    Reader.var_ranges = property::make("var_ranges",Reader.it);
    Reader.constant_ask = property::make("constant?",Reader.it);
    Reader.grange = property::make("grange",Reader.it);
    Reader.trange = property::make("trange",2,Reader.it);
    Reader.tbody = property::make("tbody",2,Reader.it);
    Reader.add_ref_to_item = property::make("add_ref_to_item",Reader.it);
    Reader.string2item = property::make("string2item",Reader.it);
    Reader.in_code_ask = property::make("in_code?",2,Reader.it);
    Reader.save_doc_links = property::make("save_doc_links",Reader.it);
    Reader.directory = property::make("directory",Reader.it);
    Reader.load_doc_links = property::make("load_doc_links",Reader.it);
    Reader.compare_items = property::make("compare_items",Reader.it);
    Reader.ordered_categories = property::make("ordered_categories",Reader.it);
    Reader.make_alias = property::make("make_alias",Reader.it);
    Reader.make_category = property::make("make_category",Reader.it);
    Reader.make_section = property::make("make_section",Reader.it);
    Reader.make_doc_item = property::make("make_doc_item",Reader.it);
    Reader.load_items = property::make("load_items",Reader.it);
    Reader.load_file_items = property::make("load_file_items",Reader.it);
    Reader.update_location_I = property::make("update_location!",Reader.it);
    Reader.pop_frame_I = property::make("pop_frame!",Reader.it);
    Reader.load_module_doc = property::make("load_module_doc",Reader.it);
    Reader.generate_module_doc = property::make("generate_module_doc",Reader.it);
    Reader.generation_mode = property::make("generation_mode",Reader.it);
    Reader.add_source_links_ask = property::make("add_source_links?",Reader.it);
    Reader.bold_ask = property::make("bold?",Reader.it);
    Reader.in_a_ask = property::make("in_a?",Reader.it);
    Reader.html_file_header = property::make("html_file_header",Reader.it);
    Reader.print_doc = property::make("print_doc",Reader.it);
    Reader.generate_index = property::make("generate_index",Reader.it);
    Reader.generate_doc = property::make("generate_doc",Reader.it);
    Reader.html_file_footer = property::make("html_file_footer",Reader.it);
    Reader.generate_category_index = property::make("generate_category_index",Reader.it);
    Reader.generate_option_index = property::make("generate_option_index",Reader.it);
    Reader.generate_entity_index = property::make("generate_entity_index",Reader.it);
    Reader.item_href = property::make("item_href",Reader.it);
    Reader.item_prototype = property::make("item_prototype",Reader.it);
    Reader.item_file = property::make("item_file",Reader.it);
    Reader.section_index_href = property::make("section_index_href",Reader.it);
    Reader.option_index_href = property::make("option_index_href",Reader.it);
    Reader.start_entity_doc = property::make("start_entity_doc",Reader.it);
    Reader.item_header = property::make("item_header",Reader.it);
    Reader.entity_print = property::make("entity_print",Reader.it);
    Reader.start_item_header = property::make("start_item_header",Reader.it);
    Reader.end_item_header = property::make("end_item_header",Reader.it);
    Reader.file_inline_css_style = property::make("file_inline_css_style",Reader.it);
    Reader.set_item_module = property::make("set_item_module",Reader.it);
    Reader.restore_module = property::make("restore_module",Reader.it);
    Reader.princ_doc_word = property::make("princ_doc_word",Reader.it);
    Reader.print_doc_word = property::make("print_doc_word",Reader.it);
    Reader.isnext_ask = property::make("isnext?",Reader.it);
    Reader.checknext_ask = property::make("checknext?",Reader.it);
    Reader.pop_handle_I = property::make("pop_handle!",Reader.it);
    Reader.equip_list = property::make("equip_list",Reader.it);
    Reader.lexical_build_equip = property::make("lexical_build_equip",Reader.it);
    Reader.where = property::make("where",Reader.it);
    Reader.bind_frame = property::make("bind_frame",Reader.it);
    Reader.unbind_frame = property::make("unbind_frame",Reader.it);
    
    // instructions from module sources 
    
    GC_BIND;
(Reader._delimiter = ClaireClass::make("delimiter",Core._global_variable,claire.it));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.arrow = (global_variable *) Core._global_variable->instantiate("arrow",claire.it));
      _void_(_CL_obj->range = Kernel._any);
      { global_variable * g0982 = _CL_obj; 
        OID  g0983;
        { keyword * _CL_obj = ((keyword *) GC_OBJECT(keyword,new_object_class(Kernel._keyword)));
          _void_(_CL_obj->name = symbol_I_string2(((char*)"->")));
          add_I_property(Kernel.instances,Kernel._keyword,11,_oid_(_CL_obj));
          g0983 = _oid_(_CL_obj);
          }
        _void_(g0982->value = g0983);}
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
put_symbol(OBJECT(symbol,(*Kernel.name)(GC_OID(Reader.arrow->value))),Reader.arrow->value);
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.triangle = (global_variable *) Core._global_variable->instantiate("triangle",claire.it));
      _void_(_CL_obj->range = Kernel._any);
      { global_variable * g0984 = _CL_obj; 
        OID  g0985;
        { keyword * _CL_obj = ((keyword *) GC_OBJECT(keyword,new_object_class(Kernel._keyword)));
          _void_(_CL_obj->name = symbol_I_string2(((char*)"<:")));
          add_I_property(Kernel.instances,Kernel._keyword,11,_oid_(_CL_obj));
          g0985 = _oid_(_CL_obj);
          }
        _void_(g0984->value = g0985);}
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
(Reader._reserved_keyword = ClaireClass::make("reserved_keyword",Kernel._keyword,claire.it));
    
    { (Reader._cl_else = (reserved_keyword *) Reader._reserved_keyword->instantiate("else",claire.it));
      ;}
    
    { (Reader._cl_for = (reserved_keyword *) Reader._reserved_keyword->instantiate("for",claire.it));
      ;}
    
    { (Reader._cl_ffor = (reserved_keyword *) Reader._reserved_keyword->instantiate("ffor",claire.it));
      ;}
    
    { (Reader._cl_case = (reserved_keyword *) Reader._reserved_keyword->instantiate("case",claire.it));
      ;}
    
    { (Reader._cl_while = (reserved_keyword *) Reader._reserved_keyword->instantiate("while",claire.it));
      ;}
    
    { (Reader._cl_until = (reserved_keyword *) Reader._reserved_keyword->instantiate("until",claire.it));
      ;}
    
    { (Reader._cl_let = (reserved_keyword *) Reader._reserved_keyword->instantiate("let",claire.it));
      ;}
    
    { (Reader._cl_when = (reserved_keyword *) Reader._reserved_keyword->instantiate("when",claire.it));
      ;}
    
    { (Reader._cl_try = (reserved_keyword *) Reader._reserved_keyword->instantiate("try",claire.it));
      ;}
    
    { (Reader._cl_if = (reserved_keyword *) Reader._reserved_keyword->instantiate("if",claire.it));
      ;}
    
    { (Reader._cl_Zif = (reserved_keyword *) Reader._reserved_keyword->instantiate("Zif",claire.it));
      ;}
    
    { (Reader._cl_branch = (reserved_keyword *) Reader._reserved_keyword->instantiate("branch",claire.it));
      ;}
    
    Reader.keyword_ask->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	0,_function_(keyword_ask_any,"keyword?_any"));
    
    { (Reader.forall = (keyword *) Kernel._keyword->instantiate("forall",claire.it));
      ;}
    
    { (Reader.None = (keyword *) Kernel._keyword->instantiate("None",claire.it));
      ;}
    
    { (Reader.L__equal = (keyword *) Kernel._keyword->instantiate(":=",claire.it));
      ;}
    
    { (Reader.L_ = (keyword *) Kernel._keyword->instantiate(":",claire.it));
      ;}
    
    { (Reader.CATCH = (keyword *) Kernel._keyword->instantiate("catch",claire.it));
      ;}
    
    { (Reader.in = (keyword *) Kernel._keyword->instantiate("in",claire.it));
      ;}
    
    { (Reader.by = (keyword *) Kernel._keyword->instantiate("by",claire.it));
      ;}
    
    { (Reader.as = (keyword *) Kernel._keyword->instantiate("as",claire.it));
      ;}
    
    { (Reader.L_L_ = (keyword *) Kernel._keyword->instantiate("::",claire.it));
      ;}
    
    { (Reader.PRINTF = (keyword *) Kernel._keyword->instantiate("printf",claire.it));
      ;}
    
    { (Reader.assert = (keyword *) Kernel._keyword->instantiate("assert",claire.it));
      ;}
    
    { (Reader.RETURN = (keyword *) Kernel._keyword->instantiate("return",claire.it));
      ;}
    
    { (Reader.BREAK = (keyword *) Kernel._keyword->instantiate("break",claire.it));
      ;}
    
    { (Reader.trace = (keyword *) Kernel._keyword->instantiate("trace",claire.it));
      ;}
    
    { (Reader.exists = (keyword *) Kernel._keyword->instantiate("exists",claire.it));
      ;}
    
    { (Reader.some = (keyword *) Kernel._keyword->instantiate("some",claire.it));
      ;}
    
    { (Reader._equal_sup = (keyword *) Kernel._keyword->instantiate("=>",claire.it));
      ;}
    
    { (Reader._ask = (keyword *) Kernel._keyword->instantiate("?",claire.it));
      ;}
    
    { (Reader.rule = (keyword *) Kernel._keyword->instantiate("rule",claire.it));
      ;}
    
    { (Reader.quote = (keyword *) Kernel._keyword->instantiate("quote",claire.it));
      ;}
    
    { (Reader.inspect = property::make("inspect",1,claire.it,Kernel._any,0));
      ;}
    
    { (Reader.known_I = property::make("known!",2,claire.it,Kernel._any,0));
      ;}
    
    { (Reader._meta_reader = ClaireClass::make("meta_reader",Kernel._thing,claire.it));
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Kernel.source,source,Kernel._string,CNULL);
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.s_index,s_index,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.fromp,fromp,Kernel._port,Core.cl_stdin->value);
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.nb_line,nb_line,Kernel._integer,CNULL);
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Kernel.external,external,Kernel._string,_string_(((char*)"toplevel")));
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Kernel.index,index,Kernel._integer,CNULL);
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.last_form,last_form,Kernel._any,CNULL);
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.maxstack,maxstack,Kernel._integer,CNULL);
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.toplevel,toplevel,Kernel._boolean,Kernel.ctrue);
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.eof,eof,Kernel._integer,CNULL);
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.space,space,Kernel._integer,CNULL);
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.tab,tab,Kernel._integer,CNULL);
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.bracket,bracket,Kernel._any,CNULL);
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.paren,paren,Kernel._any,CNULL);
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.comma,comma,Kernel._any,CNULL);
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.curly,curly,Kernel._any,CNULL);
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.last_arrow,last_arrow,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.s_properties,s_properties,nth_class1(Kernel._set,Kernel._property),_oid_(set::alloc(Kernel._property,9,_oid_(Kernel.ABSTRACT),
        _oid_(Kernel.FINAL),
        _oid_(Kernel.ephemeral),
        _oid_(Kernel.begin),
        _oid_(Kernel.end),
        _oid_(Kernel.store),
        _oid_(Core.reify),
        _oid_(Language.ClaireInterface),
        _oid_(Reader.known_I))));
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.cascade_ask,cascade_ask,Kernel._boolean,Kernel.ctrue);
      CL_ADD_SLOT(Reader._meta_reader,meta_reader,Reader.wcl_ask,wcl_ask,Kernel._boolean,Kernel.cfalse);
      }
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.IDENTS = (global_variable *) Core._global_variable->instantiate("IDENTS",Reader.it));
      _void_(_CL_obj->range = Kernel._list);
      _void_(_CL_obj->value = _oid_(list::empty(Kernel._list)));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.get_lines->addMethod(list::domain(1,Reader._meta_reader),Kernel._integer,
    	RETURN_ARG,_function_(get_lines_meta_reader,"get_lines_meta_reader"));
    
    Reader.next->addMethod(list::domain(1,Reader._meta_reader),Kernel._integer,
    	SLOT_UPDATE,_function_(next_meta_reader,"next_meta_reader"));
    
    Reader.firstc->addMethod(list::domain(1,Reader._meta_reader),Kernel._integer,
    	0,_function_(firstc_meta_reader,"firstc_meta_reader"));
    
    Reader.stop_ask->addMethod(list::domain(1,Kernel._integer),Kernel._any,
    	0,_function_(stop_ask_integer,"stop?_integer"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.AND = (global_variable *) Core._global_variable->instantiate("AND",claire.it));
      _void_(_CL_obj->range = Kernel._any);
      _void_(_CL_obj->value = _oid_(Core._and));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader.OR = (global_variable *) Core._global_variable->instantiate("OR",claire.it));
      _void_(_CL_obj->range = Kernel._any);
      _void_(_CL_obj->value = _oid_(new_thing_class(Reader._delimiter,symbol_I_string(((char*)"|"),claire.it))));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.nextunit->addMethod(list::domain(1,Reader._meta_reader),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(nextunit_meta_reader,"nextunit_meta_reader"));
    
    Reader.nexts->addMethod(list::domain(2,Reader._meta_reader,Kernel._keyword),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(nexts_meta_reader,"nexts_meta_reader"));
    
    Reader.leaf_wcl_intruction_ask->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	0,_function_(leaf_wcl_intruction_ask_any1,"leaf_wcl_intruction?_any1"));
    
    Reader.head_wcl_intruction_ask->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	0,_function_(head_wcl_intruction_ask_any1,"head_wcl_intruction?_any1"));
    
    Reader.loopexp->addMethod(list::domain(4,Reader._meta_reader,
      Kernel._any,
      Kernel._keyword,
      Kernel._boolean),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(loopexp_meta_reader,"loopexp_meta_reader"));
    
    Reader.extended_operator->addMethod(list::domain(3,Kernel._property,Kernel._any,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(extended_operator_property1,"extended_operator_property1"));
    
    Reader.nexte->addMethod(list::domain(1,Reader._meta_reader),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(nexte_meta_reader,"nexte_meta_reader"));
    
    Reader.add_ident->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(add_ident_string1,"add_ident_string1"));
    
    Kernel.read_ident->addMethod(list::domain(1,Reader._meta_reader),Kernel._any,
    	NEW_ALLOC,_function_(read_ident_meta_reader1,"read_ident_meta_reader1"));
    
    Reader.nextexp->addMethod(list::domain(2,Reader._meta_reader,Kernel._boolean),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(nextexp_meta_reader,"nextexp_meta_reader"));
    
    Reader.nexti->addMethod(list::domain(2,Reader._meta_reader,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(nexti_meta_reader,"nexti_meta_reader"));
    
    Reader.read_escape->addMethod(list::domain(1,Reader._meta_reader),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(read_escape_meta_reader,"read_escape_meta_reader"));
    
    Reader.nextvariable->addMethod(list::domain(2,Reader._meta_reader,Kernel._any),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE,_function_(nextvariable_meta_reader,"nextvariable_meta_reader"));
    
    Reader.nexts_I->addMethod(list::domain(2,Reader._meta_reader,Kernel._keyword),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(nexts_I_meta_reader1,"nexts!_meta_reader1"));
    
    Reader.nexte_I->addMethod(list::domain(2,Reader._meta_reader,Kernel._keyword),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(nexte_I_meta_reader,"nexte!_meta_reader"));
    
    Reader.nexts_I->addMethod(list::domain(2,Reader._meta_reader,Kernel._integer),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(nexts_I_meta_reader2,"nexts!_meta_reader2"));
    
    Reader.nexts_I->addMethod(list::domain(3,Reader._meta_reader,Kernel._keyword,Kernel._integer),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(nexts_I_meta_reader3,"nexts!_meta_reader3"));
    
    Reader.extended_comment_ask->addMethod(list::domain(2,Reader._meta_reader,Kernel._string),Kernel._boolean,
    	0,_function_(extended_comment_ask_meta_reader,"extended_comment?_meta_reader"));
    
    Reader.extended_comment_I->addMethod(list::domain(2,Reader._meta_reader,Kernel._string),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(extended_comment_I_meta_reader,"extended_comment!_meta_reader"));
    
    Reader.Call_I->addMethod(list::domain(2,Kernel._property,Kernel._list),Language._Call,
    	NEW_ALLOC,_function_(Call_I_property,"Call!_property"));
    
    Reader.operation_ask->addMethod(list::domain(1,Kernel._any),Kernel._boolean,
    	0,_function_(operation_ask_any,"operation?_any"));
    
    Reader.combine->addMethod(list::domain(3,Kernel._any,Kernel._any,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(combine_any,"combine_any"));
    
    Reader.combine_I->addMethod(list::domain(3,Kernel._any,Kernel._any,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(combine_I_any,"combine!_any"));
    
    Reader.operation_I->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	0,_function_(operation_I_any,"operation!_any"));
    
    Reader.operand_I->addMethod(list::domain(2,Kernel._any,Kernel._integer),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(operand_I_any,"operand!_any"));
    
    Reader.precedence_I->addMethod(list::domain(1,Kernel._any),Kernel._integer,
    	RETURN_ARG,_function_(precedence_I_any,"precedence!_any"));
    
    Reader.nextstruct->addMethod(list::domain(3,Reader._meta_reader,Kernel._keyword,Kernel._keyword),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(nextstruct_meta_reader,"nextstruct_meta_reader"));
    
    Reader.readlet->addMethod(list::domain(2,Reader._meta_reader,Kernel._keyword),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(readlet_meta_reader,"readlet_meta_reader"));
    
    Reader.readlet_star->addMethod(list::domain(4,Reader._meta_reader,
      Kernel._list,
      Kernel._integer,
      Kernel._keyword),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(readlet_star_meta_reader,"readlet*_meta_reader"));
    
    Reader.readwhen->addMethod(list::domain(2,Reader._meta_reader,Kernel._keyword),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(readwhen_meta_reader,"readwhen_meta_reader"));
    
    Reader.readif->addMethod(list::domain(2,Reader._meta_reader,Kernel._integer),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(readif_meta_reader,"readif_meta_reader"));
    
    Reader.readcase->addMethod(list::domain(2,Reader._meta_reader,Kernel._keyword),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(readcase_meta_reader,"readcase_meta_reader"));
    
    Reader.readset->addMethod(list::domain(2,Reader._meta_reader,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(readset_meta_reader,"readset_meta_reader"));
    
    Reader.dereference->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(dereference_any,"dereference_any"));
    
    Reader.nextseq->addMethod(list::domain(2,Reader._meta_reader,Kernel._integer),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(nextseq_meta_reader,"nextseq_meta_reader"));
    
    Reader.readblock->addMethod(list::domain(3,Reader._meta_reader,Kernel._any,Kernel._integer),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(readblock_meta_reader,"readblock_meta_reader"));
    
    Reader.Do_I->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(Do_I_any,"Do!_any"));
    
    Reader.extract_of_type->addMethod(list::domain(1,Language._Call),Kernel._type,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(extract_of_type_Call,"extract_of_type_Call"));
    
    Reader.readcall->addMethod(list::domain(3,Reader._meta_reader,Kernel._any,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(readcall_meta_reader,"readcall_meta_reader"));
    
    Reader.nextdefinition->addMethod(list::domain(4,Reader._meta_reader,
      Kernel._any,
      Kernel._any,
      Kernel._boolean),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(nextdefinition_meta_reader,"nextdefinition_meta_reader"));
    
    Reader.nextmethod->addMethod(list::domain(6,Reader._meta_reader,
      Kernel._any,
      Kernel._any,
      Kernel._boolean,
      Kernel._boolean,
      Kernel._boolean),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(nextmethod_meta_reader,"nextmethod_meta_reader"));
    
    Reader.nextinst->addMethod(list::domain(2,Reader._meta_reader,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(nextinst_meta_reader,"nextinst_meta_reader"));
    
    Reader.nextDefclass->addMethod(list::domain(3,Reader._meta_reader,Kernel._any,Kernel._boolean),Language._Defclass,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(nextDefclass_meta_reader,"nextDefclass_meta_reader"));
    
    Core.self_eval->addMethod(list::domain(1,Reader._delimiter),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE,_function_(self_eval_delimiter,"self_eval_delimiter"));
    
    _void_(Reader._delimiter->evaluate = CLREAD(method,_at_property1(Core.self_eval,Reader._delimiter),functional));
    
    { (Reader.REGISTER = property::make("register",2,claire.it,Kernel._any,0));
      ;}
    
    Reader.useless_c->addMethod(list::domain(1,Kernel._integer),Kernel._boolean,
    	0,_function_(useless_c_integer,"useless_c_integer"));
    
    Reader.skipc->addMethod(list::domain(1,Reader._meta_reader),Kernel._any,
    	SLOT_UPDATE,_function_(skipc_meta_reader,"skipc_meta_reader"));
    
    Reader.skipc_I->addMethod(list::domain(1,Reader._meta_reader),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE,_function_(skipc_I_meta_reader,"skipc!_meta_reader"));
    
    Reader.cnext->addMethod(list::domain(1,Reader._meta_reader),Reader._meta_reader,
    	SLOT_UPDATE+SAFE_RESULT,_function_(cnext_meta_reader,"cnext_meta_reader"));
    
    Reader.findeol->addMethod(list::domain(1,Reader._meta_reader),Kernel._boolean,
    	SLOT_UPDATE,_function_(findeol_meta_reader,"findeol_meta_reader"));
    
    Reader.checkno->addMethod(list::domain(3,Reader._meta_reader,Kernel._integer,Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(checkno_meta_reader,"checkno_meta_reader"));
    
    Reader.verify->addMethod(list::domain(3,Kernel._any,Kernel._any,Kernel._any),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(verify_any,"verify_any"));
    
    { (Reader._syntax_error = ClaireClass::make("syntax_error",Kernel._exception,Reader.it));
      CL_ADD_SLOT(Reader._syntax_error,Reader_syntax_error,Kernel.code,code,Kernel._integer,CNULL);
      CL_ADD_SLOT(Reader._syntax_error,Reader_syntax_error,Reader.cause,cause,Kernel._string,CNULL);
      CL_ADD_SLOT(Reader._syntax_error,Reader_syntax_error,Core.args,args,Kernel._list,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Reader._syntax_error),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_syntax_error1_Reader,"self_print_syntax_error1_Reader"));
    
    Reader.Serror->addMethod(list::domain(3,Kernel._integer,Kernel._string,Kernel._list),Kernel.emptySet,
    	NEW_ALLOC,_function_(Serror_integer1,"Serror_integer1"));
    
    { (Reader.reader = (meta_reader *) Reader._meta_reader->instantiate("reader",claire.it));
      _void_(Reader.reader->space = 202);
      _void_(Reader.reader->eof = 255);
      _void_(Reader.reader->tab = (CL_INT )('\t'));
      _void_(Reader.reader->index = 1);
      _void_(Reader.reader->bracket = _oid_(new_thing_class(Reader._delimiter,symbol_I_string2(((char*)"]")))));
      _void_(Reader.reader->paren = _oid_(new_thing_class(Reader._delimiter,symbol_I_string2(((char*)")")))));
      _void_(Reader.reader->comma = _oid_(new_thing_class(Reader._delimiter,symbol_I_string2(((char*)",")))));
      _void_(Reader.reader->curly = _oid_(new_thing_class(Reader._delimiter,symbol_I_string2(((char*)"}")))));
      _void_(Reader.reader->external = string_v(CLREAD(slot,_at_property1(Kernel.external,Reader._meta_reader),DEFAULT)));
      ;}
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.READER_STACK = (global_variable *) Core._global_variable->instantiate("READER_STACK",Reader.it));
      _void_(_CL_obj->range = nth_class1(Kernel._list,Reader._meta_reader));
      _void_(_CL_obj->value = _oid_(list::empty(Reader._meta_reader)));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.reader_push->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(reader_push_void1,"reader_push_void1"));
    
    Reader.reader_pop->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	0,_function_(reader_pop_void1,"reader_pop_void1"));
    
    Reader.reader_reset->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	0,_function_(reader_reset_void1,"reader_reset_void1"));
    
    Reader.extract_variable->addMethod(list::domain(1,Kernel._any),Language._Variable,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(extract_variable_any,"extract_variable_any"));
    
    Reader.bind_I->addMethod(list::domain(2,Reader._meta_reader,Language._Variable),Kernel._list,
    	NEW_ALLOC+SLOT_UPDATE,_function_(bind_I_meta_reader,"bind!_meta_reader"));
    
    Reader.unbind_I->addMethod(list::domain(2,Reader._meta_reader,Kernel._list),Kernel._any,
    	SLOT_UPDATE+RETURN_ARG,_function_(unbind_I_meta_reader,"unbind!_meta_reader"));
    
    Kernel.restore_state->addMethod(list::domain(1,Reader._meta_reader),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(restore_state_meta_reader,"restore_state_meta_reader"));
    
    Reader.load_file->addMethod(list::domain(2,Kernel._string,Kernel._boolean),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(load_file_string,"load_file_string"));
    
    Reader.load->addMethod(list::domain(1,Kernel._string),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(load_string,"load_string"));
    
    Reader.sload->addMethod(list::domain(1,Kernel._string),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(sload_string,"sload_string"));
    
    Reader.load_file->addMethod(list::domain(2,Kernel._module,Kernel._boolean),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(load_file_module,"load_file_module"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.PROCESS_LOAD_MODULE_ask = (global_variable *) Core._global_variable->instantiate("PROCESS_LOAD_MODULE?",Reader.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.ctrue);
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.set_load_module->addMethod(list::domain(1,Kernel._boolean),Kernel._void,
    	SAFE_RESULT,_function_(set_load_module_boolean,"set_load_module_boolean"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.PROCESS_EVAL_INSTRUCTIONS_ask = (global_variable *) Core._global_variable->instantiate("PROCESS_EVAL_INSTRUCTIONS?",Reader.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.ctrue);
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.set_eval_module->addMethod(list::domain(1,Kernel._boolean),Kernel._void,
    	SAFE_RESULT,_function_(set_eval_module_boolean1,"set_eval_module_boolean1"));
    
    Reader.load->addMethod(list::domain(1,Kernel._module),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE,_function_(load_module,"load_module"));
    
    Reader.sload->addMethod(list::domain(1,Kernel._module),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE,_function_(sload_module,"sload_module"));
    
    Reader.add_modules->addMethod(list::domain(3,Kernel._module,Kernel._set,Kernel._list),Kernel._list,
    	NEW_ALLOC+BAG_UPDATE+RETURN_ARG,_function_(add_modules_module,"add_modules_module"));
    
    Reader.add_parts->addMethod(list::domain(2,Kernel._module,Kernel._set),Kernel._void,
    	NEW_ALLOC,_function_(add_parts_module,"add_parts_module"));
    
    Reader.add_subparts->addMethod(list::domain(2,Kernel._module,Kernel._set),Kernel._void,
    	NEW_ALLOC,_function_(add_subparts_module,"add_subparts_module"));
    
    Reader.add_uses->addMethod(list::domain(2,Kernel._module,Kernel._set),Kernel._void,
    	NEW_ALLOC,_function_(add_uses_module,"add_uses_module"));
    
    Reader.add_modules->addMethod(list::domain(2,Kernel._module,Kernel._set),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(add_modules_module2,"add_modules_module2"));
    
    Reader.add_modules->addMethod(list::domain(1,Kernel._list),Kernel._list,
    	NEW_ALLOC+BAG_UPDATE,_function_(add_modules_list,"add_modules_list"));
    
    Reader.eload->addMethod(list::domain(1,Kernel._string),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(eload_string,"eload_string"));
    
    Reader.readblock->addMethod(list::domain(1,Kernel._port),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(readblock_port,"readblock_port"));
    
    Core.read->addMethod(list::domain(1,Kernel._port),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(read_port,"read_port"));
    
    Core.read->addMethod(list::domain(1,Kernel._string),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(read_string,"read_string"));
    
    { (Reader.q = (keyword *) Kernel._keyword->instantiate("q",claire.it));
      ;}
    
    Reader.print_exception->addMethod(list::domain(1,Kernel._void),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(print_exception_void,"print_exception_void"));
    
    { (Reader.pretty_show = property::make("pretty_show",3,claire.it,Kernel._any,0));
      _void_(Reader.pretty_show->open = 3);
      ;}
    
    Reader.show->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(show_any,"show_any"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.WCL_STOP = (global_variable *) Core._global_variable->instantiate("WCL_STOP",Reader.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      { global_variable * g0986 = _CL_obj; 
        OID  g0987;
        { set * V_CL0988;{ GC_ANY(V_CL0988= set::empty(Kernel.emptySet));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)"#")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)"'")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)"\"")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)"//")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)";")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)"/*")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)":")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)"?")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)"\t")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)"\n")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)"\r")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)" ")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)",")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)"|")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)"}")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)"{")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)"]")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)"[")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)")")));
            ((set *) V_CL0988)->addFast((OID)_string_(((char*)"(")));}
          
          g0987=_oid_(V_CL0988);}
        _void_(g0986->value = g0987);}
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
GC_OBJECT(method,((method *) _at_property1(Core.min,Kernel._integer)))->inlineDef("lambda[(x:integer,y:integer),(if (x <= y) x else y)]");
    
    GC_OBJECT(method,((method *) _at_property1(Core.min,Kernel._float)))->inlineDef("lambda[(x:float,y:float),(if (x <= y) x else y)]");
    
    GC_OBJECT(method,((method *) _at_property1(Core.max,Kernel._integer)))->inlineDef("lambda[(x:integer,y:integer),(if (y <= x) x else y)]");
    
    GC_OBJECT(method,((method *) _at_property1(Core.max,Kernel._float)))->inlineDef("lambda[(x:float,y:float),(if (y <= x) x else y)]");
    
    Core.min->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(min_any,"min_any"))->inlineDef("lambda[(x:any,y:any),(if (x <= y) x else y)]");
    
    Core.max->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(max_any,"max_any"))->inlineDef("lambda[(x:any,y:any),(if (x <= y) y else x)]");
    
    Core.known_ask->addMethod(list::domain(2,Kernel._table,Kernel._any),Kernel._boolean,
    	0,_function_(known_ask_table,"known?_table"))->inlineDef("lambda[(a:table,x:any),get(a, x) != unknown]");
    
    Core.unknown_ask->addMethod(list::domain(2,Kernel._table,Kernel._any),Kernel._boolean,
    	0,_function_(unknown_ask_table,"unknown?_table"))->inlineDef("lambda[(a:table,x:any),get(a, x) = unknown]");
    
    Kernel._sup_equal->addMethod(list::domain(2,Kernel._any,Kernel._any),Kernel._boolean,
    	NEW_ALLOC,_function_(_sup_equal_any,">=_any"))->inlineDef("lambda[(self:any,x:any),x <= self]");
    
    Reader.hashgrow->addMethod(list::domain(2,Kernel._list,Kernel._property),Kernel._list,
    	NEW_ALLOC,_function_(hashgrow_list,"hashgrow_list"))->inlineDef("lambda[(l:list,hi:property),let l1 := l,l2 := make_list(nth_get(l1, 0) * 2, unknown) in (for x in l1 (if known?(x) hi(l2, x)), l2)]");
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.used_modules = (global_variable *) Core._global_variable->instantiate("used_modules",claire.it));
      _void_(_CL_obj->range = nth_class1(Kernel._list,tuple::alloc(2,_oid_(Kernel._module),_oid_(Kernel._string))));
      _void_(_CL_obj->value = _oid_(list::empty(tuple::alloc(2,_oid_(Kernel._module),_oid_(Kernel._string)))));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.use_module->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(use_module_string,"use_module_string"));
    
    Core.option_usage->addFloatMethod(list::domain(1,GC_OBJECT(set,set::alloc(Kernel.emptySet,2,_string_(((char*)"-ef")),_string_(((char*)"-f"))))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string13_Reader,"option_usage_string13_Reader"),
    _function_(option_usage_string13_Reader_,"option_usage_string13_Reader_"));
    
    Core.option_respond->addMethod(list::domain(2,GC_OBJECT(set,set::alloc(Kernel.emptySet,2,_string_(((char*)"-ef")),_string_(((char*)"-f")))),Kernel._list),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(option_respond_string10_Reader,"option_respond_string10_Reader"));
    
    Core.option_usage->addFloatMethod(list::domain(1,GC_OBJECT(set,set::alloc(Kernel.emptySet,3,_string_(((char*)"-eval")),
      _string_(((char*)"-print")),
      _string_(((char*)"-princ"))))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string14_Reader,"option_usage_string14_Reader"),
    _function_(option_usage_string14_Reader_,"option_usage_string14_Reader_"));
    
    Core.option_respond->addMethod(list::domain(2,GC_OBJECT(set,set::alloc(Kernel.emptySet,3,_string_(((char*)"-print")),
      _string_(((char*)"-princ")),
      _string_(((char*)"-eval")))),Kernel._list),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(option_respond_string11_Reader,"option_respond_string11_Reader"));
    
    Core.option_usage->addFloatMethod(list::domain(1,GC_OBJECT(set,set::alloc(Kernel.emptySet,4,_string_(((char*)"-xe?-?")),
      _string_(((char*)"-x?-?")),
      _string_(((char*)"-xe")),
      _string_(((char*)"-x"))))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string15_Reader,"option_usage_string15_Reader"),
    _function_(option_usage_string15_Reader_,"option_usage_string15_Reader_"));
    
    Core.option_respond->addMethod(list::domain(2,GC_OBJECT(set,set::alloc(Kernel.emptySet,4,_string_(((char*)"-xe?-?")),
      _string_(((char*)"-x?-?")),
      _string_(((char*)"-xe")),
      _string_(((char*)"-x")))),Kernel._list),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(option_respond_string12_Reader,"option_respond_string12_Reader"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.NO_DEBUG_METHOD = (global_variable *) Core._global_variable->instantiate("NO_DEBUG_METHOD",Reader.it));
      _void_(_CL_obj->range = nth_class1(Kernel._list,Kernel._method));
      _void_(_CL_obj->value = _oid_(list::empty(Kernel._method)));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
GC_OBJECT(method,((method *) _at_property1(Core.eof_ask,Kernel._port)))->inlineDef("lambda[(p:port),eof_port?(p)]");
    
    if (isfile_ask_string(_7_dash_string(GC_STRING(getenv_string(((char*)"_"))),((char*)"init.cl"))) == CTRUE)
     { ClaireHandler c_handle = ClaireHandler();
      if ERROR_IN 
      { load_string(GC_STRING(_7_dash_string(GC_STRING(getenv_string(((char*)"_"))),((char*)"init.cl"))));
        ERROR_FREE;}
      else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
      { c_handle.catchIt();;}
      else PREVIOUS_HANDLER;}
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader._starshowall_star = (global_variable *) Core._global_variable->instantiate("*showall*",claire.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.ctrue);
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.inspect->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(inspect_any,"inspect_any"));
    
    Reader.inspect_loop->addMethod(list::domain(2,Kernel._any,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(inspect_loop_any,"inspect_loop_any"));
    
    Reader.get_from_integer->addMethod(list::domain(2,Kernel._any,Kernel._integer),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(get_from_integer_any,"get_from_integer_any"));
    
    Reader.trace_rule->addMethod(list::domain(6,Kernel._relation,
      Kernel._string,
      Kernel._any,
      Kernel._any,
      Kernel._any,
      Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(trace_rule_relation,"trace_rule_relation"));
    
    Kernel.mem->addMethod(list::domain(1,Kernel._class),Kernel._integer,
    	NEW_ALLOC,_function_(mem_class,"mem_class"));
    
    { (Reader._PRcount = ClaireClass::make("PRcount",Kernel._object,claire.it));
      CL_ADD_SLOT(Reader._PRcount,PRcount,Reader.rtime,rtime,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Reader._PRcount,PRcount,Reader.rdepth,rdepth,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Reader._PRcount,PRcount,Reader.rnum,rnum,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Reader._PRcount,PRcount,Reader.rloop,rloop,Kernel._integer,((OID)0));
      CL_ADD_SLOT(Reader._PRcount,PRcount,Reader.rstart,rstart,Kernel._integer,((OID)0));
      }
    
    Reader.PRget->addMethod(list::domain(1,Kernel._property),Reader._PRcount,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(PRget_property,"PRget_property"));
    
    Reader.PRlook->addMethod(list::domain(1,Kernel._property),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(PRlook_property2,"PRlook_property2"));
    
    Reader.PRshow->addMethod(list::domain(1,Kernel._property),Kernel._void,
    	NEW_ALLOC,_function_(PRshow_property,"PRshow_property"));
    
    Reader.PRtime->addMethod(list::domain(1,Kernel._property),Kernel._integer,
    	RETURN_ARG,_function_(PRtime_property,"PRtime_property"));
    
    Reader.PRcounter->addMethod(list::domain(1,Kernel._property),Kernel._integer,
    	RETURN_ARG,_function_(PRcounter_property,"PRcounter_property"));
    
    Reader.PRshow->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE,_function_(PRshow_void,"PRshow_void"));
    
    { (Reader.PRdependent = (table *) Kernel._table->instantiate("PRdependent",Reader.it));
      _void_(Reader.PRdependent->multivalued_ask = CTRUE);
      _void_(Reader.PRdependent->range = nth_class1(Kernel._set,Kernel._property));
      _void_(Reader.PRdependent->params = _oid_(Kernel._any));
      _void_(Reader.PRdependent->domain = Kernel._property);
      _void_(Reader.PRdependent->graph = make_list_integer(29,CNULL));
      _void_(Reader.PRdependent->DEFAULT = _oid_(set::empty(Kernel._property)));
      }
    
    { (Reader.PRdependentOf = (table *) Kernel._table->instantiate("PRdependentOf",Reader.it));
      _void_(Reader.PRdependentOf->multivalued_ask = CTRUE);
      _void_(Reader.PRdependentOf->range = nth_class1(Kernel._set,Kernel._property));
      _void_(Reader.PRdependentOf->params = _oid_(Kernel._any));
      _void_(Reader.PRdependentOf->domain = Kernel._property);
      _void_(Reader.PRdependentOf->graph = make_list_integer(29,CNULL));
      _void_(Reader.PRdependentOf->DEFAULT = _oid_(set::empty(Kernel._property)));
      }
    
    Reader.dependents->addMethod(list::domain(1,Kernel._method),nth_class1(Kernel._set,Kernel._property),
    	NEW_ALLOC,_function_(dependents_method,"dependents_method"));
    
    Reader.dependents->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(dependents_any,"dependents_any"));
    
    update_property(Kernel.inverse,
      Reader.PRdependent,
      8,
      Kernel._object,
      _oid_(Reader.PRdependentOf));
    
    Reader.PRdepends->addMethod(list::domain(2,Kernel._property,Kernel._property),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(PRdepends_property,"PRdepends_property"));
    
    Reader.dump_stack->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC,_function_(dump_stack_void1,"dump_stack_void1"));
    
    Language.init_location->addMethod(list::domain(1,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+RETURN_ARG,_function_(init_location_any1_Reader,"init_location_any1_Reader"));
    
    (Language.CAN_INIT_LOCATION_ask->value= Kernel.ctrue);
    
    Reader.update_location_I->addMethod(list::domain(1,Kernel._list),Kernel._any,
    	NEW_ALLOC,_function_(update_location_I_list1,"update_location!_list1"));
    
    Reader.update_location_I->addMethod(list::domain(2,Kernel._any,Kernel._list),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(update_location_I_any1,"update_location!_any1"));
    
    Reader.pop_frame_I->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	NEW_ALLOC,_function_(pop_frame_I_any1,"pop_frame!_any1"));
    
    Reader.pop_handle_I->addMethod(list::domain(2,Kernel._any,Language._Variable),Kernel._any,
    	NEW_ALLOC,_function_(pop_handle_I_any1,"pop_handle!_any1"));
    
    Language.equip->addMethod(list::domain(2,Kernel._any,Kernel._list),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(equip_any1_Reader,"equip_any1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._Instruction,Kernel._list),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(equip_Instruction1_Reader,"equip_Instruction1_Reader"));
    
    Reader.equip_list->addMethod(list::domain(3,Kernel._list,Kernel._list,Kernel._integer),Kernel._list,
    	NEW_ALLOC,_function_(equip_list_list1,"equip_list_list1"));
    
    Language.equip->addMethod(list::domain(2,Kernel._unbound_symbol,Kernel._list),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE,_function_(equip_unbound_symbol1_Reader,"equip_unbound_symbol1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._Variable,Kernel._list),Kernel._any,
    	NEW_ALLOC+RETURN_ARG,_function_(equip_Variable1_Reader,"equip_Variable1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._While,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(equip_While1_Reader,"equip_While1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._Error,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(equip_Error1_Reader,"equip_Error1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._Construct,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(equip_Construct1_Reader,"equip_Construct1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._Call,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(equip_Call1_Reader,"equip_Call1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._Do,Kernel._list),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(equip_Do1_Reader,"equip_Do1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._Case,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(equip_Case1_Reader,"equip_Case1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._If,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(equip_If1_Reader,"equip_If1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._Let,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(equip_Let1_Reader,"equip_Let1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._When,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(equip_When1_Reader,"equip_When1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._Iteration,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(equip_Iteration1_Reader,"equip_Iteration1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._For,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(equip_For1_Reader,"equip_For1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._Handle,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(equip_Handle1_Reader,"equip_Handle1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._Assign,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(equip_Assign1_Reader,"equip_Assign1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._Defclaire,Kernel._list),Kernel._any,
    	RETURN_ARG,_function_(equip_Defclaire1_Reader,"equip_Defclaire1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._Definition,Kernel._list),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(equip_Definition1_Reader,"equip_Definition1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._Defobj,Kernel._list),Kernel._any,
    	RETURN_ARG,_function_(equip_Defobj1_Reader,"equip_Defobj1_Reader"));
    
    Language.equip->addMethod(list::domain(2,Language._Defrule,Kernel._list),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(equip_Defrule1_Reader,"equip_Defrule1_Reader"));
    
    Language.equip->addMethod(list::domain(1,Kernel._any),Kernel._any,
    	NEW_ALLOC+SLOT_UPDATE,_function_(equip_any2_Reader,"equip_any2_Reader"));
    
    Language.equip->addMethod(list::domain(1,Core._lambda),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(equip_lambda1_Reader,"equip_lambda1_Reader"));
    
    Reader.lexical_build_equip->addMethod(list::domain(2,Kernel._any,Kernel._integer),Kernel._void,
    	SLOT_UPDATE,_function_(lexical_build_equip_any1,"lexical_build_equip_any1"));
    
    Reader.insert_text->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	0,_function_(interpreter_insert_text,"interpreter_insert_text"));
    
    Reader.delete_text->addMethod(list::domain(2,Kernel._integer,Kernel._integer),Kernel._void,
    	0,_function_(interpreter_delete_text,"interpreter_delete_text"));
    
    Reader.reset_state->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	0,_function_(interpreter_reset_state,"interpreter_reset_state"));
    
	    Reader.get_cursor_position->addMethod(list::domain(1,Kernel._void),Kernel._integer,
	    	0,_function_(interpreter_get_cursor_position,"interpreter_get_cursor_position"));
    
    Reader.get_text->addMethod(list::domain(1,Kernel._void),Kernel._string,
    	NEW_ALLOC,_function_(interpreter_get_text,"interpreter_get_text"));
    
    Reader.display_list->addMethod(list::domain(1,Kernel._list),Kernel._void,
    	0,_function_(interpreter_display_list,"interpreter_display_list"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.MATCHES = (global_variable *) Core._global_variable->instantiate("MATCHES",Reader.it));
      _void_(_CL_obj->range = nth_class1(Kernel._list,Kernel._string));
      _void_(_CL_obj->value = _oid_(list::empty(Kernel._string)));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader.LAST_EXPLODED = (global_variable *) Core._global_variable->instantiate("LAST_EXPLODED",Reader.it));
      _void_(_CL_obj->range = nth_class1(Kernel._list,GC_OBJECT(ClaireType,U_type(Kernel._char,Kernel._string))));
      _void_(_CL_obj->value = _oid_(list::empty(U_type(Kernel._char,Kernel._string))));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader.LAST_MODULE = (global_variable *) Core._global_variable->instantiate("LAST_MODULE",Reader.it));
      _void_(_CL_obj->range = Kernel._module);
      _void_(_CL_obj->value = _oid_(claire.it));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader.LAST_LINE = (global_variable *) Core._global_variable->instantiate("LAST_LINE",Reader.it));
      _void_(_CL_obj->range = Kernel._string);
      _void_(_CL_obj->value = _string_(((char*)"")));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader.LAST_POSITION = (global_variable *) Core._global_variable->instantiate("LAST_POSITION",Reader.it));
      _void_(_CL_obj->range = Kernel._integer);
      _void_(_CL_obj->value = ((OID)-1));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader.MATCH_INDEX = (global_variable *) Core._global_variable->instantiate("MATCH_INDEX",Reader.it));
      _void_(_CL_obj->range = Kernel._integer);
      _void_(_CL_obj->value = ((OID)0));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader.COMPLETE_START_POSITION = (global_variable *) Core._global_variable->instantiate("COMPLETE_START_POSITION",Reader.it));
      _void_(_CL_obj->range = Kernel._integer);
      _void_(_CL_obj->value = ((OID)-1));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.completion_reset->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	0,_function_(completion_reset_void,"completion_reset_void"));
    
    Reader.explode_separators->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(explode_separators_string,"explode_separators_string"));
    
    Reader.same_tree_ask->addMethod(list::domain(1,Kernel._module),Kernel._boolean,
    	NEW_ALLOC,_function_(same_tree_ask_module,"same_tree?_module"));
    
    Reader.complete_named_object->addMethod(list::domain(2,Kernel._string,GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(complete_named_object_string,"complete_named_object_string"));
    
    Reader.complete_slot->addMethod(list::domain(2,Kernel._string,GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(complete_slot_string,"complete_slot_string"));
    
    Reader.complete_class->addMethod(list::domain(2,Kernel._string,GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(complete_class_string,"complete_class_string"));
    
    Reader.nodup->addMethod(list::domain(1,GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(nodup_list,"nodup_list"));
    
    Reader.fill_claire_matches->addMethod(list::domain(2,Kernel._string,Kernel._integer),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(fill_claire_matches_string,"fill_claire_matches_string"));
    
    Reader.match_prefix->addMethod(list::domain(1,Kernel._void),Kernel._string,
    	NEW_ALLOC,_function_(match_prefix_void,"match_prefix_void"));
    
    Reader.method_description->addMethod(list::domain(1,Kernel._method),Kernel._string,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(method_description_method,"method_description_method"));
    
    Reader.class_description->addMethod(list::domain(1,Kernel._class),Kernel._string,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(class_description_class,"class_description_class"));
    
    Reader.claire_complete->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(claire_complete_void,"claire_complete_void"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.BINS = (global_variable *) Core._global_variable->instantiate("BINS",Reader.it));
      _void_(_CL_obj->range = nth_class1(Kernel._list,Kernel._string));
      _void_(_CL_obj->value = _oid_(list::empty(Kernel._string)));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader.BINS_INIT_ask = (global_variable *) Core._global_variable->instantiate("BINS_INIT?",Reader.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.cfalse);
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.bin_init->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(bin_init_void,"bin_init_void"));
    
    Reader.fill_binaries->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(fill_binaries_string,"fill_binaries_string"));
    
    Reader.fill_files->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(fill_files_string,"fill_files_string"));
    
    Reader.shell_complete->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(shell_complete_void,"shell_complete_void"));
    
    { (Reader._stdin_line_reader = ClaireClass::make("stdin_line_reader",Core._device,Reader.it));
      CL_ADD_SLOT(Reader._stdin_line_reader,Reader_stdin_line_reader,Reader.line,line,Core._blob,CNULL);
      }
    
    Core.close_port->addMethod(list::domain(1,Reader._stdin_line_reader),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(close_port_stdin_line_reader1_Reader,"close_port_stdin_line_reader1_Reader"));
    
    Core.eof_port_ask->addMethod(list::domain(1,Reader._stdin_line_reader),Kernel._boolean,
    	0,_function_(eof_port_ask_stdin_line_reader1_Reader,"eof_port?_stdin_line_reader1_Reader"));
    
    Core.flush_port->addMethod(list::domain(1,Reader._stdin_line_reader),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(flush_port_stdin_line_reader1_Reader,"flush_port_stdin_line_reader1_Reader"));
    
    Core.unget_port->addMethod(list::domain(3,Reader._stdin_line_reader,Core._char_star,Kernel._integer),Kernel._void,
    	NEW_ALLOC,_function_(unget_port_stdin_line_reader1_Reader,"unget_port_stdin_line_reader1_Reader"));
    
    Core.read_port->addMethod(list::domain(3,Reader._stdin_line_reader,Core._char_star,Kernel._integer),Kernel._integer,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(read_port_stdin_line_reader1_Reader,"read_port_stdin_line_reader1_Reader"));
    
    { (Reader._execution_context = ClaireClass::make("execution_context",Core._ephemeral_object,Reader.it));
      CL_ADD_SLOT(Reader._execution_context,Reader_execution_context,Reader.module_stack,module_stack,Kernel._list,CNULL);
      CL_ADD_SLOT(Reader._execution_context,Reader_execution_context,Reader.saved_system,saved_system,Kernel._environment,CNULL);
      CL_ADD_SLOT(Reader._execution_context,Reader_execution_context,Reader.saved_reader,saved_reader,Reader._meta_reader,CNULL);
      CL_ADD_SLOT(Reader._execution_context,Reader_execution_context,Reader.debug_context_ask,debug_context_ask,Kernel._boolean,CNULL);
      }
    
    Reader.save_context->addMethod(list::domain(1,Kernel._boolean),Reader._execution_context,
    	NEW_ALLOC+SLOT_UPDATE,_function_(save_context_boolean1,"save_context_boolean1"));
    
    Reader.restore_context->addMethod(list::domain(1,Reader._execution_context),Kernel._void,
    	0,_function_(restore_context_execution_context1,"restore_context_execution_context1"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.PROMPT = (global_variable *) Core._global_variable->instantiate("PROMPT",Reader.it));
      _void_(_CL_obj->range = Kernel._string);
      _void_(_CL_obj->value = _string_(((char*)"")));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.get_prompt->addMethod(list::domain(1,Kernel._void),Kernel._string,
    	0,_function_(get_prompt_void2,"get_prompt_void2"));
    
    (Reader._abort_debug = ClaireClass::make("abort_debug",Kernel._exception,Reader.it));
    
    Kernel.self_print->addMethod(list::domain(1,Reader._abort_debug),Kernel._void,
    	0,_function_(self_print_abort_debug1_Reader,"self_print_abort_debug1_Reader"));
    
    { (Reader._debug_fatal_error = ClaireClass::make("debug_fatal_error",Reader._abort_debug,Reader.it));
      CL_ADD_SLOT(Reader._debug_fatal_error,Reader_debug_fatal_error,Reader.src,src,Kernel._exception,CNULL);
      }
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader._stardebug_fatal_error_star = (global_variable *) Core._global_variable->instantiate("*debug_fatal_error*",Reader.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(new_object_class(Reader._debug_fatal_error)));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Kernel.self_print->addMethod(list::domain(1,Reader._debug_fatal_error),Kernel._void,
    	NEW_ALLOC,_function_(self_print_debug_fatal_error1_Reader,"self_print_debug_fatal_error1_Reader"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.INSPECT_STACK = (global_variable *) Core._global_variable->instantiate("INSPECT_STACK",Reader.it));
      _void_(_CL_obj->range = nth_class1(Kernel._list,Kernel._any));
      _void_(_CL_obj->value = _oid_(list::empty(Kernel._any)));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.inspect_system->addMethod(list::domain(1,GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._any))),Kernel._void,
    	RETURN_ARG,_function_(inspect_system_list2,"inspect_system_list2"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.IN_INSPECT_LOOP_ask = (global_variable *) Core._global_variable->instantiate("IN_INSPECT_LOOP?",Reader.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.cfalse);
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.inspect_toplevel->addMethod(list::domain(1,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(inspect_toplevel_any1,"inspect_toplevel_any1"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.NB_EVAL = (global_variable *) Core._global_variable->instantiate("NB_EVAL",Reader.it));
      _void_(_CL_obj->range = Kernel._integer);
      _void_(_CL_obj->value = ((OID)0));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.read_command->addMethod(list::domain(1,Kernel._string),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(read_command_string1,"read_command_string1"));
    
    Reader.eval_command->addMethod(list::domain(3,Kernel._any,Kernel._integer,Kernel._boolean),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(eval_command_any2,"eval_command_any2"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.TOP_CHANDLE = (global_variable *) Core._global_variable->instantiate("TOP_CHANDLE",Reader.it));
      _void_(_CL_obj->range = Kernel._integer);
      _void_(_CL_obj->value = ((OID)0));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.close_toplevel_exception->addMethod(list::domain(1,Kernel._exception),Kernel._void,
    	0,_function_(close_toplevel_exception_exception1,"close_toplevel_exception_exception1"));
    
    { (Reader._command_line_error = ClaireClass::make("command_line_error",Kernel._exception,Reader.it));
      CL_ADD_SLOT(Reader._command_line_error,Reader_command_line_error,Reader.src,src,Kernel._any,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Reader._command_line_error),Kernel._void,
    	NEW_ALLOC,_function_(self_print_command_line_error1_Reader,"self_print_command_line_error1_Reader"));
    
    Core.toplevel->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(toplevel_void2_Reader,"toplevel_void2_Reader"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.NB_DEBUG_EVAL = (global_variable *) Core._global_variable->instantiate("NB_DEBUG_EVAL",Reader.it));
      _void_(_CL_obj->range = Kernel._integer);
      _void_(_CL_obj->value = ((OID)0));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.debug_loop->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(debug_loop_void1,"debug_loop_void1"));
    
    Core.on_break_program->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(on_break_program_void1_Reader,"on_break_program_void1_Reader"));
    
    Reader.show_frame->addMethod(list::domain(2,Core._dbg_frame,Core._dbg_frame),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(show_frame_dbg_frame1,"show_frame_dbg_frame1"));
    
    Reader.show_source_lines->addMethod(list::domain(2,Core._dbg_frame,Kernel._integer),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(show_source_lines_dbg_frame1,"show_source_lines_dbg_frame1"));
    
    Reader.show_frame_info->addMethod(list::domain(1,Core._dbg_frame),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(show_frame_info_dbg_frame1,"show_frame_info_dbg_frame1"));
    
    Reader.show_frame_info->addMethod(list::domain(2,Core._dbg_frame,Core._dbg_frame),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(show_frame_info_dbg_frame2,"show_frame_info_dbg_frame2"));
    
    Reader.where->addMethod(list::domain(1,Core._dbg_frame),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(where_dbg_frame1,"where_dbg_frame1"));
    
    { (Reader._DebugVariable = ClaireClass::make("DebugVariable",Core._ephemeral_object,Reader.it));
      CL_ADD_SLOT(Reader._DebugVariable,Reader_DebugVariable,Kernel.value,value,Kernel._any,CNULL);
      }
    
    Core.self_eval->addMethod(list::domain(1,Reader._DebugVariable),Kernel._any,
    	RETURN_ARG,_function_(self_eval_DebugVariable1,"self_eval_DebugVariable1"));
    
    _void_(Reader._DebugVariable->evaluate = ((ClaireFunction *) _function_(self_eval_DebugVariable1,"self_eval_DebugVariable1")));
    
    Reader.bind_frame->addMethod(list::domain(1,Core._dbg_frame),Kernel._list,
    	NEW_ALLOC,_function_(bind_frame_dbg_frame1,"bind_frame_dbg_frame1"));
    
    Reader.unbind_frame->addMethod(list::domain(1,Kernel._list),Kernel._void,
    	RETURN_ARG,_function_(unbind_frame_list1,"unbind_frame_list1"));
    
    Reader.print_oid->addMethod(list::domain(1,Kernel._any),Kernel._void,
    	0,_function_(print_oid_any1,"print_oid_any1"));
    
    Language.echo->addMethod(list::domain(1,Kernel._any),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(echo_any1_Reader,"echo_any1_Reader"));
    
    Language.echo->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	0,_function_(echo_string1_Reader,"echo_string1_Reader"));
    
    Language.echo->addMethod(list::domain(1,Kernel._integer),Kernel._void,
    	0,_function_(echo_integer1_Reader,"echo_integer1_Reader"));
    
    Language.echo->addFloatMethod(list::domain(1,Kernel._float),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(echo_float1_Reader,"echo_float1_Reader"),
    _function_(echo_float1_Reader_,"echo_float1_Reader_"));
    
    Language.echo->addMethod(list::domain(1,Kernel._char),Kernel._void,
    	0,_function_(echo_char1_Reader,"echo_char1_Reader"));
    
    Language.echo->addMethod(list::domain(2,Kernel._property,Kernel._object),Kernel._void,
    	NEW_ALLOC+RETURN_ARG,_function_(echo_property1_Reader,"echo_property1_Reader"));
    
    Language.self_html->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	0,_function_(self_html_string1_Reader,"self_html_string1_Reader"));
    
    Reader.nl2br->addMethod(list::domain(1,Kernel._string),Kernel._string,
    	NEW_ALLOC,_function_(nl2br_string1,"nl2br_string1"));
    
    { (Reader._self_html_converter = ClaireClass::make("self_html_converter",Core._device,Reader.it));
      CL_ADD_SLOT(Reader._self_html_converter,Reader_self_html_converter,Reader.src,src,Core._blob,CNULL);
      }
    
    Core.write_port->addMethod(list::domain(3,Reader._self_html_converter,Core._char_star,Kernel._integer),Kernel._integer,
    	SAFE_RESULT,_function_(write_port_self_html_converter1_Reader,"write_port_self_html_converter1_Reader"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.SELF_HTML_CONVERTER = (global_variable *) Core._global_variable->instantiate("SELF_HTML_CONVERTER",Reader.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      { global_variable * g0989 = _CL_obj; 
        OID  g0990;
        { Reader_self_html_converter * _CL_obj = ((Reader_self_html_converter *) GC_OBJECT(Reader_self_html_converter,new_object_class(Reader._self_html_converter)));
          _void_(_CL_obj->src = blob_I_void1());
          g0990 = _oid_(_CL_obj);
          }
        _void_(g0989->value = g0990);}
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Language.self_html->addMethod(list::domain(1,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_html_any1_Reader,"self_html_any1_Reader"));
    
    Language.self_html->addMethod(list::domain(2,Kernel._property,Kernel._object),Kernel._void,
    	NEW_ALLOC,_function_(self_html_property1_Reader,"self_html_property1_Reader"));
    
    Reader.wcl_start_ask->addMethod(list::domain(2,Reader._meta_reader,Kernel._integer),Kernel._boolean,
    	NEW_ALLOC,_function_(wcl_start_ask_meta_reader1,"wcl_start?_meta_reader1"));
    
    Reader.nextswcl->addMethod(list::domain(1,Reader._meta_reader),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(nextswcl_meta_reader1,"nextswcl_meta_reader1"));
    
    Reader.Call_wcl_I->addMethod(list::domain(3,Kernel._property,Kernel._list,Kernel._tuple),Language._Call_wcl,
    	NEW_ALLOC+SLOT_UPDATE,_function_(Call_wcl_I_property1,"Call_wcl!_property1"));
    
    Reader.build_call_wcl->addMethod(list::domain(2,Reader._meta_reader,Kernel._property),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(build_call_wcl_meta_reader2,"build_call_wcl_meta_reader2"));
    
    Reader.build_top_call_wcl->addMethod(list::domain(2,Reader._meta_reader,Kernel._property),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(build_top_call_wcl_meta_reader1,"build_top_call_wcl_meta_reader1"));
    
    Reader.read_top_wcl->addMethod(list::domain(1,Reader._meta_reader),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(read_top_wcl_meta_reader1,"read_top_wcl_meta_reader1"));
    
    Reader.read_wcl->addMethod(list::domain(1,Reader._meta_reader),Kernel._any,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(read_wcl_meta_reader1,"read_wcl_meta_reader1"));
    
    _void_(Reader.reader->wcl_ask = CTRUE);
    
    Reader.fopen_source->addMethod(list::domain(1,Kernel._string),Kernel._port,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(fopen_source_string1,"fopen_source_string1"));
    
    { (Reader.load_wcl = property::make("load_wcl",3,claire.it,Kernel._any,0));
      _void_(Reader.load_wcl->open = 3);
      ;}
    
    Reader.load_wcl_I->addMethod(list::domain(1,Kernel._string),nth_class1(Kernel._list,Language._Defclaire),
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(load_wcl_I_string1,"load_wcl!_string1"));
    
    Reader.add_wcl->addMethod(list::domain(4,Kernel._module,
      Kernel._string,
      Kernel._string,
      Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(add_wcl_module1,"add_wcl_module1"));
    
    Reader.add_wcl->addMethod(list::domain(4,Kernel._module,
      Kernel._string,
      GC_OBJECT(ClaireType,nth_class1(Kernel._type,Kernel._string)),
      Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(add_wcl_module2,"add_wcl_module2"));
    
    { (Reader._hash_table = ClaireClass::make("hash_table",Core._ephemeral_object,Reader.it));
      CL_ADD_SLOT(Reader._hash_table,Reader_hash_table,Reader.hash_max,hash_max,Kernel._integer,CNULL);
      CL_ADD_SLOT(Reader._hash_table,Reader_hash_table,Reader.content,content,nth_class1(Kernel._list,Kernel._any),CNULL);
      }
    
    Reader.hash_table_I->addMethod(list::domain(1,Kernel._integer),Reader._hash_table,
    	NEW_ALLOC,_function_(hash_table_I_integer1,"hash_table!_integer1"));
    
    (Reader._map_node = ClaireClass::make("map_node",Core._ephemeral_object,Reader.it));
    
    { (Reader._map_node = ClaireClass::make("map_node",Core._ephemeral_object,Reader.it));
      CL_ADD_SLOT(Reader._map_node,Reader_map_node,Reader.nkey,nkey,Kernel._any,CNULL);
      CL_ADD_SLOT(Reader._map_node,Reader_map_node,Reader.nval,nval,Kernel._any,CNULL);
      CL_ADD_SLOT(Reader._map_node,Reader_map_node,Reader.next,next,Reader._map_node,CNULL);
      }
    
    Reader.reset->addMethod(list::domain(1,Reader._hash_table),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(reset_hash_table1,"reset_hash_table1"));
    
    Reader.hash_value_oid->addMethod(list::domain(2,Reader._hash_table,Kernel._any),Kernel._integer,
    	RETURN_ARG,_function_(hash_value_oid_hash_table1,"hash_value_oid_hash_table1"));
    
    Reader.hash_value_string->addMethod(list::domain(2,Reader._hash_table,Kernel._string),Kernel._integer,
    	RETURN_ARG,_function_(hash_value_string_hash_table1,"hash_value_string_hash_table1"));
    
    Kernel.nth_equal->addMethod(list::domain(3,Reader._hash_table,Kernel._any,Kernel._any),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(nth_equal_hash_table1,"nth=_hash_table1"));
    
    Kernel.nth->addMethod(list::domain(2,Reader._hash_table,Kernel._any),Kernel._any,
    	0,_function_(nth_hash_table1,"nth_hash_table1"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.MODULE_NAME = (global_variable *) Core._global_variable->instantiate("MODULE_NAME",Reader.it));
      _void_(_CL_obj->range = Kernel._string);
      _void_(_CL_obj->value = _string_(((char*)"Other")));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader.NAME_TO_ITEM_TABLE = (global_variable *) Core._global_variable->instantiate("NAME_TO_ITEM_TABLE",Reader.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(hash_table_I_integer1(8191)));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader.ITEM_LOCATION = (global_variable *) Core._global_variable->instantiate("ITEM_LOCATION",Reader.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(hash_table_I_integer1(8191)));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader.SHORT_PRESENTATION = (global_variable *) Core._global_variable->instantiate("SHORT_PRESENTATION",Reader.it));
      _void_(_CL_obj->range = Kernel._string);
      _void_(_CL_obj->value = _string_(((char*)"")));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader.DOC_TITLE = (global_variable *) Core._global_variable->instantiate("DOC_TITLE",Reader.it));
      _void_(_CL_obj->range = Kernel._string);
      _void_(_CL_obj->value = _string_(((char*)"")));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader._starexpl_doc_star = (global_variable *) Core._global_variable->instantiate("*expl_doc*",Reader.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.cfalse);
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader._starcode_doc_star = (global_variable *) Core._global_variable->instantiate("*code_doc*",Reader.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.cfalse);
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader._stardoc_links_star = (global_variable *) Core._global_variable->instantiate("*doc_links*",Reader.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.cfalse);
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader._starone_file_star = (global_variable *) Core._global_variable->instantiate("*one_file*",Reader.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.cfalse);
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader._starper_cat_file_star = (global_variable *) Core._global_variable->instantiate("*per_cat_file*",Reader.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.cfalse);
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader._stardirectory_star = (global_variable *) Core._global_variable->instantiate("*directory*",Reader.it));
      _void_(_CL_obj->range = Kernel._string);
      _void_(_CL_obj->value = _string_(((char*)"doc")));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader._staronly_doc_links_star = (global_variable *) Core._global_variable->instantiate("*only_doc_links*",Reader.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.cfalse);
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader.DEPOPTIONS = (global_variable *) Core._global_variable->instantiate("DEPOPTIONS",Reader.it));
      _void_(_CL_obj->range = Kernel._boolean);
      _void_(_CL_obj->value = Kernel.cfalse);
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
(Reader._doc_context = ClaireClass::make("doc_context",Core._ephemeral_object,Reader.it));
    
    { (Reader._doc_item = ClaireClass::make("doc_item",Kernel._object,Reader.it));
      CL_ADD_SLOT(Reader._doc_item,Reader_doc_item,Reader.src_location,src_location,Kernel._any,CNULL);
      CL_ADD_SLOT(Reader._doc_item,Reader_doc_item,Reader.documentation,documentation,Kernel._string,_string_(((char*)"")));
      CL_ADD_SLOT(Reader._doc_item,Reader_doc_item,Reader.xl_ask,xl_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Reader._doc_item,Reader_doc_item,Kernel.name,name,Kernel._string,CNULL);
      }
    
    { (Reader._doc_link = ClaireClass::make("doc_link",Reader._doc_item,Reader.it));
      CL_ADD_SLOT(Reader._doc_link,Reader_doc_link,Reader.oid,oid,Kernel._string,CNULL);
      CL_ADD_SLOT(Reader._doc_link,Reader_doc_link,Reader.src,src,Kernel._string,CNULL);
      }
    
    (Reader._doc_copyright = ClaireClass::make("doc_copyright",Reader._doc_item,Reader.it));
    
    (Reader._doc_preamble = ClaireClass::make("doc_preamble",Reader._doc_item,Reader.it));
    
    (Reader._doc_author = ClaireClass::make("doc_author",Reader._doc_item,Reader.it));
    
    (Reader._doc_category = ClaireClass::make("doc_category",Reader._doc_item,Reader.it));
    
    (Reader._doc_entity = ClaireClass::make("doc_entity",Reader._doc_item,Reader.it));
    
    { (Reader._doc_section = ClaireClass::make("doc_section",Reader._doc_item,Reader.it));
      CL_ADD_SLOT(Reader._doc_section,Reader_doc_section,Reader.exploit_ask,exploit_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Reader._doc_section,Reader_doc_section,Reader.categories,categories,nth_class1(Kernel._list,Reader._doc_category),CNULL);
      }
    
    { (Reader._doc_category = ClaireClass::make("doc_category",Reader._doc_item,Reader.it));
      CL_ADD_SLOT(Reader._doc_category,Reader_doc_category,Reader.section,section,Reader._doc_section,CNULL);
      CL_ADD_SLOT(Reader._doc_category,Reader_doc_category,Reader.exploit_ask,exploit_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Reader._doc_category,Reader_doc_category,Reader.items,items,nth_class1(Kernel._list,Reader._doc_entity),CNULL);
      CL_ADD_SLOT(Reader._doc_category,Reader_doc_category,Reader.entity_names,entity_names,nth_class1(Kernel._list,Kernel._string),CNULL);
      CL_ADD_SLOT(Reader._doc_category,Reader_doc_category,Reader.aliases,aliases,nth_class1(Kernel._list,Kernel._string),CNULL);
      CL_ADD_SLOT(Reader._doc_category,Reader_doc_category,Reader.aname,aname,Kernel._string,CNULL);
      }
    
    { (Reader._doc_option = ClaireClass::make("doc_option",Reader._doc_item,Reader.it));
      CL_ADD_SLOT(Reader._doc_option,Reader_doc_option,Reader.usage,usage,Kernel._string,CNULL);
      CL_ADD_SLOT(Reader._doc_option,Reader_doc_option,Reader.from_module,from_module,Kernel._module,CNULL);
      CL_ADD_SLOT(Reader._doc_option,Reader_doc_option,Reader.opts,opts,nth_class1(Kernel._list,Kernel._string),CNULL);
      CL_ADD_SLOT(Reader._doc_option,Reader_doc_option,Core.vars,vars,nth_class1(Kernel._list,Kernel._string),CNULL);
      CL_ADD_SLOT(Reader._doc_option,Reader_doc_option,Reader.ranges,ranges,nth_class1(Kernel._list,Kernel._string),CNULL);
      }
    
    { (Reader._doc_entity = ClaireClass::make("doc_entity",Reader._doc_item,Reader.it));
      CL_ADD_SLOT(Reader._doc_entity,Reader_doc_entity,Kernel.source,source,Kernel._any,CNULL);
      CL_ADD_SLOT(Reader._doc_entity,Reader_doc_entity,Language.ident,ident,Kernel._symbol,CNULL);
      CL_ADD_SLOT(Reader._doc_entity,Reader_doc_entity,Reader.category,category,Reader._doc_category,CNULL);
      }
    
    update_property(Kernel.inverse,
      Reader.section,
      8,
      Kernel._object,
      _oid_(Reader.categories));
    
    update_property(Kernel.inverse,
      Reader.category,
      8,
      Kernel._object,
      _oid_(Reader.items));
    
    { (Reader._doc_method = ClaireClass::make("doc_method",Reader._doc_entity,Reader.it));
      CL_ADD_SLOT(Reader._doc_method,Reader_doc_method,Core.vars,vars,nth_class1(Kernel._list,Kernel._string),CNULL);
      CL_ADD_SLOT(Reader._doc_method,Reader_doc_method,Reader.mrange,mrange,Kernel._any,CNULL);
      CL_ADD_SLOT(Reader._doc_method,Reader_doc_method,Kernel.inline_ask,inline_ask,Kernel._boolean,CNULL);
      CL_ADD_SLOT(Reader._doc_method,Reader_doc_method,Reader.var_ranges,var_ranges,nth_class1(Kernel._list,Kernel._any),CNULL);
      }
    
    { (Reader._doc_class = ClaireClass::make("doc_class",Reader._doc_entity,Reader.it));
      CL_ADD_SLOT(Reader._doc_class,Reader_doc_class,Kernel.superclass,superclass,Kernel._any,CNULL);
      }
    
    { (Reader._doc_global = ClaireClass::make("doc_global",Reader._doc_entity,Reader.it));
      CL_ADD_SLOT(Reader._doc_global,Reader_doc_global,Reader.constant_ask,constant_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Reader._doc_global,Reader_doc_global,Reader.grange,grange,Kernel._any,CNULL);
      CL_ADD_SLOT(Reader._doc_global,Reader_doc_global,Kernel.value,value,Kernel._any,CNULL);
      }
    
    { (Reader._doc_interface = ClaireClass::make("doc_interface",Reader._doc_entity,Reader.it));
      CL_ADD_SLOT(Reader._doc_interface,Reader_doc_interface,Kernel.arg,arg,Kernel._any,CNULL);
      CL_ADD_SLOT(Reader._doc_interface,Reader_doc_interface,Core.args,args,Kernel._list,CNULL);
      }
    
    { (Reader._doc_table = ClaireClass::make("doc_table",Reader._doc_entity,Reader.it));
      CL_ADD_SLOT(Reader._doc_table,Reader_doc_table,Reader.trange,trange,Kernel._any,CNULL);
      CL_ADD_SLOT(Reader._doc_table,Reader_doc_table,Reader.tbody,tbody,Kernel._any,CNULL);
      }
    
    Reader.add_ref_to_item->addMethod(list::domain(2,Reader._doc_item,Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(add_ref_to_item_doc_item1,"add_ref_to_item_doc_item1"));
    
    Reader.string2item->addMethod(list::domain(2,Reader._doc_context,Kernel._string),Kernel._any,
    	NEW_ALLOC,_function_(string2item_doc_context1,"string2item_doc_context1"));
    
    Reader.save_doc_links->addMethod(list::domain(1,Reader._doc_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(save_doc_links_doc_context1,"save_doc_links_doc_context1"));
    
    Reader.load_doc_links->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(load_doc_links_void1,"load_doc_links_void1"));
    
    Reader.compare_items->addMethod(list::domain(2,Reader._doc_entity,Reader._doc_entity),Kernel._boolean,
    	NEW_ALLOC,_function_(compare_items_doc_entity1,"compare_items_doc_entity1"));
    
    Reader.ordered_categories->addMethod(list::domain(1,Kernel._void),nth_class1(Kernel._list,Reader._doc_category),
    	NEW_ALLOC,_function_(ordered_categories_void1,"ordered_categories_void1"));
    
    Reader.print_module->addMethod(list::domain(1,Reader._doc_entity),Kernel._void,
    	0,_function_(print_module_doc_entity1,"print_module_doc_entity1"));
    
    Reader.make_alias->addMethod(list::domain(2,Reader._doc_category,Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(make_alias_doc_category1,"make_alias_doc_category1"));
    
    Reader.make_category->addMethod(list::domain(1,Kernel._string),Reader._doc_category,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(make_category_string1,"make_category_string1"));
    
    Reader.make_section->addMethod(list::domain(2,Reader._doc_category,Kernel._string),Reader._doc_category,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+SAFE_RESULT,_function_(make_section_doc_category1,"make_section_doc_category1"));
    
    Reader.make_section->addMethod(list::domain(1,Kernel._string),Reader._doc_section,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(make_section_string1,"make_section_string1"));
    
    Reader.make_doc_item->addMethod(list::domain(4,Kernel._any,
      Kernel._string,
      Kernel._string,
      Kernel._boolean),Kernel._void,
    	0,_function_(make_doc_item_any1,"make_doc_item_any1"));
    
    Reader.make_doc_item->addMethod(list::domain(4,Language._Defmethod,
      Kernel._string,
      Kernel._string,
      Kernel._boolean),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(make_doc_item_Defmethod1,"make_doc_item_Defmethod1"));
    
    Reader.make_doc_item->addMethod(list::domain(4,Language._Defarray,
      Kernel._string,
      Kernel._string,
      Kernel._boolean),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(make_doc_item_Defarray1,"make_doc_item_Defarray1"));
    
    Reader.make_doc_item->addMethod(list::domain(4,Language._Defclass,
      Kernel._string,
      Kernel._string,
      Kernel._boolean),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(make_doc_item_Defclass1,"make_doc_item_Defclass1"));
    
    Reader.make_doc_item->addMethod(list::domain(4,Language._Defobj,
      Kernel._string,
      Kernel._string,
      Kernel._boolean),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(make_doc_item_Defobj1,"make_doc_item_Defobj1"));
    
    Reader.load_items->addMethod(list::domain(1,Kernel._string),nth_class1(Kernel._list,Kernel._any),
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(load_items_string1,"load_items_string1"));
    
    { (Reader._bad_eval = ClaireClass::make("bad_eval",Kernel._exception,Reader.it));
      CL_ADD_SLOT(Reader._bad_eval,Reader_bad_eval,Reader.src,src,Kernel._exception,CNULL);
      }
    
    Kernel.self_print->addMethod(list::domain(1,Reader._bad_eval),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(self_print_bad_eval1_Reader,"self_print_bad_eval1_Reader"));
    
    Reader.load_file_items->addMethod(list::domain(1,Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(load_file_items_string1,"load_file_items_string1"));
    
    Core.option_respond->addMethod(list::domain(2,GC_OBJECT(set,set::alloc(Kernel.emptySet,1,_string_(((char*)"-export-doc-links")))),GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	0,_function_(option_respond_string51_Reader,"option_respond_string51_Reader"));
    
    Core.option_respond->addMethod(list::domain(2,GC_OBJECT(set,set::alloc(Kernel.emptySet,1,_string_(((char*)"-doclink")))),GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	0,_function_(option_respond_string52_Reader,"option_respond_string52_Reader"));
    
    Core.option_respond->addMethod(list::domain(2,GC_OBJECT(set,set::alloc(Kernel.emptySet,1,_string_(((char*)"-onefile")))),GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	0,_function_(option_respond_string53_Reader,"option_respond_string53_Reader"));
    
    Core.option_respond->addMethod(list::domain(2,GC_OBJECT(set,set::alloc(Kernel.emptySet,1,_string_(((char*)"-categories")))),GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	0,_function_(option_respond_string54_Reader,"option_respond_string54_Reader"));
    
    Core.option_respond->addMethod(list::domain(2,GC_OBJECT(set,set::alloc(Kernel.emptySet,3,_string_(((char*)"-exploitationdoc")),
      _string_(((char*)"-codedoc")),
      _string_(((char*)"-apidoc")))),GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(option_respond_string55_Reader,"option_respond_string55_Reader"));
    
    Core.option_usage->addFloatMethod(list::domain(1,GC_OBJECT(set,set::alloc(Kernel.emptySet,5,_string_(((char*)"-codedoc")),
      _string_(((char*)"-apidoc")),
      _string_(((char*)"-categories")),
      _string_(((char*)"-onefile")),
      _string_(((char*)"-doclink"))))),tuple::alloc(3,_oid_(Kernel._string),
      _oid_(Kernel._string),
      _oid_(Kernel._string)),
    	NEW_ALLOC,_function_(option_usage_string35_Reader,"option_usage_string35_Reader"),
    _function_(option_usage_string35_Reader_,"option_usage_string35_Reader_"));
    
    Reader.load_module_doc->addMethod(list::domain(1,Kernel._module),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(load_module_doc_module1,"load_module_doc_module1"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.ONE_FILE = (global_variable *) Core._global_variable->instantiate("ONE_FILE",Reader.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = ((OID)0));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader.PER_CATEGORY_FILE = (global_variable *) Core._global_variable->instantiate("PER_CATEGORY_FILE",Reader.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = ((OID)2));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
{ (Reader._doc_context = ClaireClass::make("doc_context",Core._ephemeral_object,Reader.it));
      CL_ADD_SLOT(Reader._doc_context,Reader_doc_context,Reader.generation_mode,generation_mode,Kernel._integer,(OID)(2));
      CL_ADD_SLOT(Reader._doc_context,Reader_doc_context,Reader.add_source_links_ask,add_source_links_ask,Kernel._boolean,CNULL);
      CL_ADD_SLOT(Reader._doc_context,Reader_doc_context,Kernel.source,source,Kernel._module,CNULL);
      CL_ADD_SLOT(Reader._doc_context,Reader_doc_context,Kernel.index,index,Kernel._string,CNULL);
      CL_ADD_SLOT(Reader._doc_context,Reader_doc_context,Reader.directory,directory,Kernel._string,CNULL);
      CL_ADD_SLOT(Reader._doc_context,Reader_doc_context,Kernel.color,color,Kernel._string,_string_(((char*)"")));
      CL_ADD_SLOT(Reader._doc_context,Reader_doc_context,Reader.bold_ask,bold_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Reader._doc_context,Reader_doc_context,Reader.in_code_ask,in_code_ask,Kernel._boolean,Kernel.cfalse);
      CL_ADD_SLOT(Reader._doc_context,Reader_doc_context,Reader.in_a_ask,in_a_ask,Kernel._boolean,Kernel.cfalse);
      }
    
    Reader.generate_module_doc->addMethod(list::domain(1,Kernel._module),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_module_doc_module1,"generate_module_doc_module1"));
    
    Reader.generate_index->addMethod(list::domain(1,Reader._doc_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_index_doc_context1,"generate_index_doc_context1"));
    
    Reader.generate_index->addMethod(list::domain(2,Reader._doc_context,Reader._doc_entity),Kernel._void,
    	NEW_ALLOC,_function_(generate_index_doc_context2,"generate_index_doc_context2"));
    
    Reader.generate_index->addMethod(list::domain(3,Reader._doc_context,Reader._doc_entity,Kernel._boolean),Kernel._void,
    	NEW_ALLOC,_function_(generate_index_doc_context3,"generate_index_doc_context3"));
    
    Reader.generate_category_index->addMethod(list::domain(1,Reader._doc_context),Kernel._void,
    	NEW_ALLOC,_function_(generate_category_index_doc_context1,"generate_category_index_doc_context1"));
    
    Reader.generate_option_index->addMethod(list::domain(1,Reader._doc_context),Kernel._void,
    	NEW_ALLOC,_function_(generate_option_index_doc_context1,"generate_option_index_doc_context1"));
    
    Reader.generate_entity_index->addMethod(list::domain(4,Reader._doc_context,
      Kernel._class,
      Kernel._string,
      Kernel._string),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_entity_index_doc_context1,"generate_entity_index_doc_context1"));
    
    Reader.generate_doc->addMethod(list::domain(1,Reader._doc_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(generate_doc_doc_context1,"generate_doc_doc_context1"));
    
    Reader.generate_doc->addMethod(list::domain(3,Reader._doc_context,Kernel._string,Kernel._class),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG,_function_(generate_doc_doc_context2,"generate_doc_doc_context2"));
    
    Reader.generate_doc->addMethod(list::domain(2,Reader._doc_category,Reader._doc_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_doc_doc_category1,"generate_doc_doc_category1"));
    
    Reader.generate_doc->addMethod(list::domain(2,Reader._doc_option,Reader._doc_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_doc_doc_option1,"generate_doc_doc_option1"));
    
    Reader.start_entity_doc->addMethod(list::domain(2,Reader._doc_entity,Reader._doc_context),Kernel._void,
    	NEW_ALLOC,_function_(start_entity_doc_doc_entity1,"start_entity_doc_doc_entity1"));
    
    Reader.generate_doc->addMethod(list::domain(2,Reader._doc_entity,Reader._doc_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_doc_doc_entity1,"generate_doc_doc_entity1"));
    
    Reader.generate_doc->addMethod(list::domain(2,Reader._doc_method,Reader._doc_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_doc_doc_method1,"generate_doc_doc_method1"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.DOC_CLASS_ROOTS = (global_variable *) Core._global_variable->instantiate("DOC_CLASS_ROOTS",Reader.it));
      _void_(_CL_obj->range = nth_class1(Kernel._list,Kernel._class));
      _void_(_CL_obj->value = _oid_(list::alloc(Kernel._class,3,_oid_(Kernel._any),
        _oid_(Core._ephemeral_object),
        _oid_(Kernel._thing))));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.generate_doc->addMethod(list::domain(2,Reader._doc_class,Reader._doc_context),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(generate_doc_doc_class1,"generate_doc_doc_class1"));
    
    Reader.start_item_header->addMethod(list::domain(3,Reader._doc_entity,Reader._doc_context,Kernel._integer),Kernel._void,
    	NEW_ALLOC,_function_(start_item_header_doc_entity1,"start_item_header_doc_entity1"));
    
    Reader.end_item_header->addMethod(list::domain(4,Reader._doc_entity,
      Reader._doc_context,
      Kernel._integer,
      Kernel._string),Kernel._void,
    	NEW_ALLOC,_function_(end_item_header_doc_entity1,"end_item_header_doc_entity1"));
    
    Reader.item_header->addMethod(list::domain(2,Reader._doc_global,Reader._doc_context),Kernel._void,
    	NEW_ALLOC,_function_(item_header_doc_global1,"item_header_doc_global1"));
    
    Reader.item_header->addMethod(list::domain(2,Reader._doc_table,Reader._doc_context),Kernel._void,
    	NEW_ALLOC,_function_(item_header_doc_table1,"item_header_doc_table1"));
    
    Reader.item_header->addMethod(list::domain(2,Reader._doc_method,Reader._doc_context),Kernel._void,
    	NEW_ALLOC,_function_(item_header_doc_method1,"item_header_doc_method1"));
    
    Reader.item_header->addMethod(list::domain(2,Reader._doc_class,Reader._doc_context),Kernel._void,
    	NEW_ALLOC,_function_(item_header_doc_class1,"item_header_doc_class1"));
    
    Reader.item_header->addMethod(list::domain(2,Reader._doc_interface,Reader._doc_context),Kernel._void,
    	NEW_ALLOC,_function_(item_header_doc_interface1,"item_header_doc_interface1"));
    
    Reader.file_inline_css_style->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	0,_function_(file_inline_css_style_void1,"file_inline_css_style_void1"));
    
    Reader.html_file_header->addMethod(list::domain(1,Reader._doc_context),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE,_function_(html_file_header_doc_context1,"html_file_header_doc_context1"));
    
    Reader.html_file_header->addMethod(list::domain(2,Reader._doc_context,Kernel._string),Kernel._void,
    	NEW_ALLOC,_function_(html_file_header_doc_context2,"html_file_header_doc_context2"));
    
    Reader.html_file_header->addMethod(list::domain(2,Reader._doc_context,Reader._doc_item),Kernel._void,
    	NEW_ALLOC,_function_(html_file_header_doc_context3,"html_file_header_doc_context3"));
    
    Reader.html_file_footer->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	0,_function_(html_file_footer_void1,"html_file_footer_void1"));
    
    Reader.category_index_href->addMethod(list::domain(1,Reader._doc_context),Kernel._void,
    	NEW_ALLOC,_function_(category_index_href_doc_context1,"category_index_href_doc_context1"));
    
    Reader.option_index_href->addMethod(list::domain(1,Reader._doc_context),Kernel._void,
    	NEW_ALLOC,_function_(option_index_href_doc_context1,"option_index_href_doc_context1"));
    
    Reader.section_index_href->addMethod(list::domain(2,Reader._doc_context,Reader._doc_section),Kernel._void,
    	NEW_ALLOC,_function_(section_index_href_doc_context1,"section_index_href_doc_context1"));
    
    Reader.item_href->addMethod(list::domain(2,Reader._doc_context,Reader._doc_link),Kernel._void,
    	NEW_ALLOC,_function_(item_href_doc_context1,"item_href_doc_context1"));
    
    Reader.item_href->addMethod(list::domain(2,Reader._doc_context,Reader._doc_item),Kernel._void,
    	NEW_ALLOC,_function_(item_href_doc_context2,"item_href_doc_context2"));
    
    Reader.item_href->addMethod(list::domain(3,Reader._doc_context,Reader._doc_link,Kernel._string),Kernel._void,
    	NEW_ALLOC,_function_(item_href_doc_context3,"item_href_doc_context3"));
    
    Reader.item_href->addMethod(list::domain(3,Reader._doc_context,Reader._doc_item,Kernel._string),Kernel._void,
    	NEW_ALLOC,_function_(item_href_doc_context4,"item_href_doc_context4"));
    
    Reader.item_href->addMethod(list::domain(3,Reader._doc_context,Reader._doc_section,Kernel._string),Kernel._void,
    	NEW_ALLOC,_function_(item_href_doc_context5,"item_href_doc_context5"));
    
    Reader.item_file->addMethod(list::domain(2,Reader._doc_context,Reader._doc_category),Kernel._void,
    	0,_function_(item_file_doc_context1,"item_file_doc_context1"));
    
    Reader.item_file->addMethod(list::domain(2,Reader._doc_context,Reader._doc_option),Kernel._void,
    	0,_function_(item_file_doc_context2,"item_file_doc_context2"));
    
    Reader.item_file->addMethod(list::domain(2,Reader._doc_context,Reader._doc_entity),Kernel._void,
    	0,_function_(item_file_doc_context3,"item_file_doc_context3"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.RESTORE_MODULE = (global_variable *) Core._global_variable->instantiate("RESTORE_MODULE",Reader.it));
      _void_(_CL_obj->range = Kernel._module);
      _void_(_CL_obj->value = _oid_(claire.it));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.set_item_module->addMethod(list::domain(1,Reader._doc_entity),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(set_item_module_doc_entity1,"set_item_module_doc_entity1"));
    
    Reader.restore_module->addMethod(list::domain(1,Kernel._void),Kernel._void,
    	SLOT_UPDATE+RETURN_ARG,_function_(restore_module_void1,"restore_module_void1"));
    
    Reader.entity_print->addMethod(list::domain(3,Reader._doc_entity,Reader._doc_context,Kernel._any),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(entity_print_doc_entity1,"entity_print_doc_entity1"));
    
    Reader.item_prototype->addMethod(list::domain(2,Reader._doc_global,Reader._doc_context),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(item_prototype_doc_global1,"item_prototype_doc_global1"));
    
    Reader.item_prototype->addMethod(list::domain(2,Reader._doc_table,Reader._doc_context),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(item_prototype_doc_table1,"item_prototype_doc_table1"));
    
    Reader.item_prototype->addMethod(list::domain(2,Reader._doc_interface,Reader._doc_context),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(item_prototype_doc_interface1,"item_prototype_doc_interface1"));
    
    Reader.item_prototype->addMethod(list::domain(2,Reader._doc_class,Reader._doc_context),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(item_prototype_doc_class1,"item_prototype_doc_class1"));
    
    Reader.item_prototype->addMethod(list::domain(2,Reader._doc_method,Reader._doc_context),Kernel._void,
    	NEW_ALLOC+SLOT_UPDATE+RETURN_ARG,_function_(item_prototype_doc_method1,"item_prototype_doc_method1"));
    
    Reader.princ_doc_word->addMethod(list::domain(3,Reader._doc_context,Kernel._string,GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC,_function_(princ_doc_word_doc_context1,"princ_doc_word_doc_context1"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.IGNORE_WORDS = (global_variable *) Core._global_variable->instantiate("IGNORE_WORDS",Reader.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(set::alloc(Kernel.emptySet,13,_string_(((char*)">=")),
        _string_(((char*)"<=")),
        _string_(((char*)"*")),
        _string_(((char*)"/")),
        _string_(((char*)"-")),
        _string_(((char*)"+")),
        _string_(((char*)">")),
        _string_(((char*)"<")),
        _string_(((char*)"!=")),
        _string_(((char*)"=")),
        _string_(((char*)"the")),
        _string_(((char*)"or")),
        _string_(((char*)"and")))));
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.print_doc_word->addMethod(list::domain(4,Reader._doc_context,
      Kernel._string,
      GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string)),
      GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC,_function_(print_doc_word_doc_context1,"print_doc_word_doc_context1"));
    
    GC_UNBIND;
{ global_variable * _CL_obj = (Reader.TAG_STOP = (global_variable *) Core._global_variable->instantiate("TAG_STOP",Reader.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      _void_(_CL_obj->value = _oid_(set::alloc(Kernel.emptySet,5,_oid_(_char_(((unsigned char)'\t'))),
        _oid_(_char_(((unsigned char)'\n'))),
        _oid_(_char_(((unsigned char)'\r'))),
        _oid_(_char_(((unsigned char)' '))),
        _oid_(_char_(((unsigned char)'\\'))))));
      close_global_variable(_CL_obj);
      }
    
    { global_variable * _CL_obj = (Reader.DOC_STOP = (global_variable *) Core._global_variable->instantiate("DOC_STOP",Reader.it));
      _void_(_CL_obj->range = Kernel.emptySet);
      { global_variable * g0991 = _CL_obj; 
        OID  g0992;
        { set * V_CL0993;{ GC_ANY(V_CL0993= set::empty(Kernel.emptySet));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)'\t'))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)'\n'))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)'\r'))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)' '))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)'#'))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)'('))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)')'))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)'*'))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)'+'))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)','))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)'.'))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)'/'))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)':'))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)';'))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)'='))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)'>'))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)'['))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)']'))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)'{'))));
            ((set *) V_CL0993)->addFast((OID)_oid_(_char_(((unsigned char)'}'))));
            ((set *) V_CL0993)->addFast((OID)_string_(((char*)"?>")));
            ((set *) V_CL0993)->addFast((OID)_string_(((char*)"'")));
            ((set *) V_CL0993)->addFast((OID)_string_(((char*)"\"")));
            ((set *) V_CL0993)->addFast((OID)_string_(((char*)"%%")));
            ((set *) V_CL0993)->addFast((OID)_string_(((char*)"\\")));}
          
          g0992=_oid_(V_CL0993);}
        _void_(g0991->value = g0992);}
      close_global_variable(_CL_obj);
      }
    
    GC_BIND;
Reader.isnext_ask->addMethod(list::domain(2,Kernel._port,Kernel._string),Kernel._boolean,
    	NEW_ALLOC,_function_(isnext_ask_port1,"isnext?_port1"));
    
    Reader.checknext_ask->addMethod(list::domain(2,Kernel._port,Kernel._string),Kernel._boolean,
    	NEW_ALLOC,_function_(checknext_ask_port1,"checknext?_port1"));
    
    Reader.print_doc->addMethod(list::domain(4,Reader._doc_context,
      Kernel._string,
      GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string)),
      GC_OBJECT(ClaireType,nth_class1(Kernel._list,Kernel._string))),Kernel._void,
    	NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE,_function_(print_doc_doc_context1,"print_doc_doc_context1"));
    GC_UNBIND;

    }
  
  