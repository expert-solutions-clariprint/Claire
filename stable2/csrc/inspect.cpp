/***** CLAIRE Compilation of file ./meta/inspect.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:42 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>

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
// *      Part 3: Debugger                                             *
// *      Part 4: Stepper                                              *
// *      Part 5: Profiler                                             *
// *********************************************************************
// v3.2.14 cleaner :-)
// v0.01 stop the ... !
// *********************************************************************
// *      Part 1: Inspection                                           *
// *********************************************************************
// this is the method that the user calls
//
//<sb> v3.3.35 : meta toplevel (context)
// The c++ function for: inspect(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  inspect_any(OID self)
{ GC_BIND;
  { OID Result = 0;
    { OID  _Zread = _oid_(Kernel.emptySet);
      module * m0 = ClEnv->module_I;
      CL_INT  ix = 0;
      inspect_system_list2(list::empty(Kernel._any));
      if (INHERIT(OWNER(self),Kernel._bag))
       { CL_INT  i = 1;
        CL_INT  g0698 = OBJECT(bag,self)->length;
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)i <= (CL_INT)g0698))
          { princ_integer(i);
            princ_string(": ");
            print_any((*(OBJECT(bag,self)))[i]);
            princ_string("\n");
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
              princ_string(": ");
              color(34,0);
              print_any(_oid_(OBJECT(restriction,rel)->selector));
              color(30,0);
              princ_string(" = ");
              if (INHERIT(OWNER(val),Kernel._bag))
               { if ((CL_INT)OBJECT(bag,val)->length < 10)
                 pretty_print_any(val);
                else { { OID  g0700UU;
                      { list * V_CL0701;{ list * i_bag = list::empty(Kernel.emptySet);
                          { CL_INT  i = 1;
                            CL_INT  g0699 = 9;
                            { CL_INT loop_handle = ClEnv->cHandle;
                              OID gc_local;
                              while (((CL_INT)i <= (CL_INT)g0699))
                              { i_bag->addFast((OID)(*(OBJECT(bag,val)))[i]);
                                ++i;
                                POP_SIGNAL;}
                              }
                            }
                          V_CL0701 = GC_OBJECT(list,i_bag);
                          }
                        
                        g0700UU=_oid_(V_CL0701);}
                      pretty_print_any(g0700UU);
                      }
                    color_princ_string1(" `RED...`BLACK");
                    }
                  }
              else pretty_print_any(val);
                princ_string("\n");
              }
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      else { pretty_print_any(self);
          princ_string("\n");
          }
        inspect_system_list2(list::alloc(Kernel._any,1,self));
      Result = _oid_(Reader.None);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// this is the inspect top_level
//<sb> v3.3.35 : meta toplevel (context)
// The c++ function for: inspect_loop(%read:any,old:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  inspect_loop_any(OID _Zread,list *old)
{ GC_BIND;
  { OID  self = (*(old))[1];
    if ((INHERIT(OWNER(_Zread),Language._Call)) && (OBJECT(Call,_Zread)->selector == Kernel.put))
     { CL_INT  n = (*(OBJECT(bag,(*Core.args)(_Zread))))[1];
      symbol * s = extract_symbol_any((*(OBJECT(bag,(*Core.args)(_Zread))))[2]);
      if (inherit_ask_class(OWNER(((OID)n)),Kernel._integer) != CTRUE)
       close_exception(((general_error *) (*Core._general_error)(_string_("[128] ~S should be an integer"),
        _oid_(list::alloc(1,((OID)n))))));
      { OID  val = GC_OID(get_from_integer_any(self,n));
        (CLREAD(global_variable,new_class2(Core._global_variable,s),value) = val);
        inspect_any(val);
        old= GC_OBJECT(list,cons_any(val,old));
        }
      }
    else if (_Zread == _oid_(Reader.up))
     { if ((CL_INT)old->length > 1)
       { old= GC_OBJECT(list,cdr_list(old));
        inspect_any((*(old))[1]);
        }
      else { CL_INT  g0702 = (int )(current_color);
          CL_INT  g0703 = (int )(current_bold);
          CL_INT  g0704 = g0702;
          CL_INT  g0705 = g0703;
          color(g0702,g0703);
          color_princ_string1("`RED => top of inspect stack.\n");
          color(g0704,g0705);
          }
        }
    else if (INHERIT(OWNER(_Zread),Kernel._integer))
     { OID  val = GC_OID(get_from_integer_any(self,_Zread));
      if ((INHERIT(OWNER(val),Kernel._bag)) && 
          (boolean_I_any(val) != CTRUE))
       { CL_INT  g0706 = (int )(current_color);
        CL_INT  g0707 = (int )(current_bold);
        CL_INT  g0708 = g0706;
        CL_INT  g0709 = g0707;
        color(g0706,g0707);
        color_princ_string1("`RED => the bag is empty\n");
        color(g0708,g0709);
        }
      else { old= GC_OBJECT(list,cons_any(val,old));
          inspect_any(val);
          }
        }
    else if (_Z_any1(_Zread,Kernel._object) == CTRUE)
     { shrink_list(old,0);
      old= GC_OBJECT(list,old->addFast((OID)_Zread));
      inspect_any(_Zread);
      }
    else { CL_INT  g0710 = (int )(current_color);
        CL_INT  g0711 = (int )(current_bold);
        CL_INT  g0712 = g0710;
        CL_INT  g0713 = g0711;
        color(g0710,g0711);
        color_princ_string1("`RED => given to inspector is wrong.`BLACK \n");
        color(g0712,g0713);
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
OID  get_from_integer_any(OID self,int n)
{ { OID Result = 0;
    if (INHERIT(OWNER(self),Kernel._bag))
     { if (((CL_INT)n > 0) && 
          ((CL_INT)n <= (CL_INT)(*Kernel.length)(self)))
       Result = (*Kernel.nth)(self,
        ((OID)n));
      else { OID  V_CL0714;close_exception(((general_error *) (*Core._general_error)(_string_("~A is not a good index for ~S"),
            _oid_(list::alloc(1,((OID)n))))));
          
          Result=_void_(V_CL0714);}
        }
    else { list * l = OWNER(self)->slots;
        if (((CL_INT)n > 0) && 
            ((CL_INT)n <= (CL_INT)l->length))
         { OID v_rec;
          v_rec = (*(l))[n];
          PUSH(v_rec);
          v_rec = self;
          PUSH(v_rec);
          Result=Kernel.get->super(Kernel._slot,2);}
        else { OID  V_CL0715;close_exception(((general_error *) (*Core._general_error)(_string_("~A is not a good index for ~S"),
              _oid_(list::alloc(1,((OID)n))))));
            
            Result=_void_(V_CL0715);}
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
void  trace_rule_relation(ClaireRelation *R,char *s,OID x,OID y,OID u,OID v)
{ GC_BIND;
  if (5 <= (CL_INT)((CL_INT)Kernel.if_write->trace_I+(CL_INT)ClEnv->verbose))
   { OID  p = GC_OID(get_property(Kernel.ctrace,ClEnv));
    if (p != CNULL)
     p= _oid_(use_as_output_port(OBJECT(PortObject,p)));
    princ_string("--- the rule ");
    princ_string(s);
    princ_string(" is triggered for (");
    print_any(u);
    princ_string(",");
    print_any(v);
    princ_string(") by an update ");
    print_any(_oid_(R));
    princ_string("(");
    print_any(x);
    princ_string(") ");
    princ_string(((multi_ask_any(_oid_(R)) == CTRUE) ?
      ":add" :
      ":=" ));
    princ_string(" ");
    print_any(y);
    princ_string(" \n");
    if (p != CNULL)
     use_as_output_port(OBJECT(PortObject,p));
    }
  GC_UNBIND; POP_SIGNAL;}


// ******************************************************************
// *    Part 3: The debugger interface                              *
// ******************************************************************
//<sb> v3.3.35 moved debug(system) to toplevel
// The c++ function for: breakpoint(_CL_obj:void) [0]
void  breakpoint_void1()
{ if ((CL_INT)ClEnv->debug_I > -1)
   fcall1(OBJECT(method,(*(Core.break_system->restrictions))[1])->functional,Kernel._object,_oid_(ClEnv),Kernel._any);
  POP_SIGNAL;}


// The c++ function for: dump_stack(_CL_obj:void) [NEW_ALLOC]
void  dump_stack_void1()
{ GC_BIND;
  princ_string("===== Dump stack ======\n");
  { CL_INT  i = 0;
    CL_INT  g0716 = ((CL_INT)ClEnv->index-(CL_INT)1);
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while (((CL_INT)i <= (CL_INT)g0716))
      { GC_LOOP;
        print_any(((OID)i));
        princ_string(": ");
        print_any(GC_OID(ClEnv->stack[((OID)i)]));
        princ_string("\n");
        ++i;
        GC_UNLOOP;POP_SIGNAL;}
      }
    }
  princ_string("index: ");
  print_any(((OID)ClEnv->index));
  princ_string("\n");
  princ_string("base: ");
  print_any(((OID)ClEnv->base));
  princ_string("\n");
  princ_string("trace!: ");
  print_any(((OID)ClEnv->trace_I));
  princ_string("\n");
  princ_string("debug!: ");
  print_any(((OID)ClEnv->debug_I));
  princ_string("\n");
  princ_string("======================\n");
  GC_UNBIND; POP_SIGNAL;}


// debug version of the debugger :-)
// The c++ function for: Show(n:integer) [NEW_ALLOC]
OID  Show_integer(int n)
{ GC_BIND;
  { OID Result = 0;
    { CL_INT  i = Reader._starcurd_star->value;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        Result= _oid_(CFALSE);
        while ((((CL_INT)i > 0) && 
            ((CL_INT)n > 0)))
        { GC_LOOP;
          { CL_INT  num_args = ((CL_INT)(ClEnv->stack[((OID)((CL_INT)i+(CL_INT)2))])-(CL_INT)1);
            CL_INT  start = ClEnv->stack[((OID)((CL_INT)i+(CL_INT)3))];
            { CL_INT  g0717 = (int )(current_color);
              CL_INT  g0718 = (int )(current_bold);
              CL_INT  g0719 = g0717;
              CL_INT  g0720 = g0718;
              color(g0717,g0718);
              color_princ_string1("`GREEN[");
              g0717= (int )(current_color);
              g0718= (int )(current_bold);
              color(g0719,g0720);
              princ_integer(start);
              color(g0717,g0718);
              color(g0717,g0718);
              color_princ_string1(" - ");
              g0717= (int )(current_color);
              g0718= (int )(current_bold);
              color(g0719,g0720);
              princ_integer(i);
              color(g0717,g0718);
              color(g0717,g0718);
              color_princ_string1("]: p = ");
              g0717= (int )(current_color);
              g0718= (int )(current_bold);
              color(g0719,g0720);
              print_any(GC_OID(ClEnv->stack[((OID)((CL_INT)i+(CL_INT)1))]));
              color(g0717,g0718);
              color(g0717,g0718);
              color_princ_string1(", narg = ");
              g0717= (int )(current_color);
              g0718= (int )(current_bold);
              color(g0719,g0720);
              print_any(((OID)num_args));
              color(g0717,g0718);
              color(g0717,g0718);
              color_princ_string1(" \n");
              color(g0719,g0720);
              }
            { CL_INT  j = 0;
              CL_INT  g0721 = num_args;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                while (((CL_INT)j <= (CL_INT)g0721))
                { GC_LOOP;
                  { CL_INT  g0722 = (int )(current_color);
                    CL_INT  g0723 = (int )(current_bold);
                    CL_INT  g0724 = g0722;
                    CL_INT  g0725 = g0723;
                    color(g0722,g0723);
                    color_princ_string1("  `GREEN[");
                    g0722= (int )(current_color);
                    g0723= (int )(current_bold);
                    color(g0724,g0725);
                    princ_integer(((CL_INT)j+(CL_INT)i));
                    color(g0722,g0723);
                    color(g0722,g0723);
                    color_princ_string1("]:");
                    g0722= (int )(current_color);
                    g0723= (int )(current_bold);
                    color(g0724,g0725);
                    print_any(GC_OID(ClEnv->stack[((OID)((CL_INT)j+(CL_INT)i))]));
                    color(g0722,g0723);
                    color(g0722,g0723);
                    color_princ_string1(" \n");
                    color(g0724,g0725);
                    }
                  ++j;
                  GC_UNLOOP;POP_SIGNAL;}
                }
              }
            n= ((CL_INT)n-(CL_INT)1);
            i= ClEnv->stack[((OID)i)];
            }
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// go to next block
// top is the top position in this stack (the last entered message)
//
// The c++ function for: block(x:integer,show_var?:boolean) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  block_integer2(int x,ClaireBoolean *show_var_ask)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  if ((CL_INT)ClEnv->debug_I > 0)
   { CL_INT  j = Reader._starcurd_star->value;
    ClaireBoolean * first_ask = CTRUE;
    CL_INT  last_debug = j;
    CL_INT  oldd = ClEnv->debug_I;
    CL_INT  oldt = ClEnv->trace_I;
    CL_INT  stack_level = 0;
    (ClEnv->debug_I = -1);
    (ClEnv->trace_I = 0);
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while ((((CL_INT)j > 0) && 
          (x != 0)))
      { GC_LOOP;
        { OID  nargs = GC_OID(ClEnv->stack[((OID)((CL_INT)j+(CL_INT)2))]);
          CL_INT  start = ClEnv->stack[((OID)((CL_INT)j+(CL_INT)3))];
          property * z = OBJECT(property,ClEnv->stack[((OID)((CL_INT)j+(CL_INT)1))]);
          ClaireObject * m = find_which_list1(z->definition,OWNER(ClEnv->stack[((OID)start)]),start,((CL_INT)start+(CL_INT)(nargs)));
          if (Kernel._method == m->isa)
           { CL_INT  g0726 = (int )(current_color);
            CL_INT  g0727 = (int )(current_bold);
            CL_INT  g0728 = g0726;
            CL_INT  g0729 = g0727;
            color(g0726,g0727);
            color_princ_string1("`GREEN");
            g0726= (int )(current_color);
            g0727= (int )(current_bold);
            color(g0728,g0729);
            princ_integer(((CL_INT)(Reader._starindex_star->value)+(CL_INT)stack_level));
            color(g0726,g0727);
            color(g0726,g0727);
            color_princ_string1("> ");
            g0726= (int )(current_color);
            g0727= (int )(current_bold);
            color(g0728,g0729);
            color(34,0);
            print_any(_oid_(m));
            color(g0726,g0727);
            color(g0726,g0727);
            color_princ_string1("`GREEN(");
            g0726= (int )(current_color);
            g0727= (int )(current_bold);
            color(g0728,g0729);
            first_ask= CTRUE;
            if ((((CLREAD(method,m,formula) == (NULL)) ? CTRUE : CFALSE) != CTRUE) && 
                (INHERIT(CLREAD(method,m,formula)->isa,Core._lambda)))
             { CL_INT  n = 0;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(v);
                bag *v_support;
                v_support = GC_OBJECT(list,closure_build_lambda(GC_OBJECT(lambda,CLREAD(method,m,formula))));
                for (START(v_support); NEXT(v);)
                { GC_LOOP;
                  { if ((((stack_level == 0) || 
                            (show_var_ask != CTRUE)) && 
                          ((CL_INT)n < (CL_INT)CLREAD(restriction,m,domain)->length)) || 
                        ((show_var_ask == CTRUE) && 
                            (((CL_INT)stack_level > 0) && 
                              (ClEnv->stack[((OID)((CL_INT)start+(CL_INT)n))] != _oid_(Core.undefined_debug)))))
                     { CL_INT  g0730 = (int )(current_color);
                      CL_INT  g0731 = (int )(current_bold);
                      CL_INT  g0732 = g0730;
                      CL_INT  g0733 = g0731;
                      color(g0730,g0731);
                      color_princ_string1("`GREEN");
                      g0730= (int )(current_color);
                      g0731= (int )(current_bold);
                      color(g0732,g0733);
                      if (first_ask == CTRUE)
                       first_ask= CFALSE;
                      else princ_string(", ");
                        color(g0730,g0731);
                      color(g0732,g0733);
                      if (show_var_ask == CTRUE)
                       { CL_INT  g0734 = (int )(current_color);
                        CL_INT  g0735 = (int )(current_bold);
                        CL_INT  g0736 = g0734;
                        CL_INT  g0737 = g0735;
                        color(g0734,g0735);
                        color_princ_string1("`GREEN");
                        g0734= (int )(current_color);
                        g0735= (int )(current_bold);
                        color(g0736,g0737);
                        print_any(v);
                        color(g0734,g0735);
                        color(g0734,g0735);
                        color_princ_string1(" =");
                        color(g0736,g0737);
                        }
                      color(g0730,g0731);
                      color(g0730,g0731);
                      color_princ_string1(" ");
                      g0730= (int )(current_color);
                      g0731= (int )(current_bold);
                      color(g0732,g0733);
                      print_any(GC_OID(ClEnv->stack[((OID)((CL_INT)start+(CL_INT)n))]));
                      color(g0730,g0731);
                      color(g0732,g0733);
                      }
                    ++n;
                    }
                  GC_UNLOOP; POP_SIGNAL;}
                }
              { CL_INT  g0738 = (int )(current_color);
                CL_INT  g0739 = (int )(current_bold);
                CL_INT  g0740 = g0738;
                CL_INT  g0741 = g0739;
                color(g0738,g0739);
                color_princ_string1("`GREEN)\n");
                color(g0740,g0741);
                }
              }
            else { CL_INT  n = 0;
                { CL_INT  v = 1;
                  CL_INT  g0742 = CLREAD(restriction,m,domain)->length;
                  { CL_INT loop_handle = ClEnv->cHandle;
                    OID gc_local;
                    while (((CL_INT)v <= (CL_INT)g0742))
                    { GC_LOOP;
                      if (first_ask == CTRUE)
                       first_ask= CFALSE;
                      else princ_string(", ");
                        print_any(GC_OID(ClEnv->stack[((OID)((CL_INT)start+(CL_INT)n))]));
                      ++n;
                      ++v;
                      GC_UNLOOP;POP_SIGNAL;}
                    }
                  }
                if (show_var_ask == CTRUE)
                 { CL_INT  g0743 = (int )(current_color);
                  CL_INT  g0744 = (int )(current_bold);
                  CL_INT  g0745 = g0743;
                  CL_INT  g0746 = g0744;
                  color(g0743,g0744);
                  color_princ_string1("`GREEN) <compiled:");
                  g0743= (int )(current_color);
                  g0744= (int )(current_bold);
                  color(g0745,g0746);
                  print_any(_oid_(CLREAD(restriction,m,module_I)));
                  color(g0743,g0744);
                  color(g0743,g0744);
                  color_princ_string1(">\n");
                  color(g0745,g0746);
                  }
                else { CL_INT  g0747 = (int )(current_color);
                    CL_INT  g0748 = (int )(current_bold);
                    CL_INT  g0749 = g0747;
                    CL_INT  g0750 = g0748;
                    color(g0747,g0748);
                    color_princ_string1("`GREEN)\n");
                    color(g0749,g0750);
                    }
                  }
              color(g0726,g0727);
            color(g0728,g0729);
            }
          else if (m == CFALSE)
           { CL_INT  g0751 = (int )(current_color);
            CL_INT  g0752 = (int )(current_bold);
            CL_INT  g0753 = g0751;
            CL_INT  g0754 = g0752;
            color(g0751,g0752);
            color_princ_string1("`GREEN");
            g0751= (int )(current_color);
            g0752= (int )(current_bold);
            color(g0753,g0754);
            princ_integer(((CL_INT)(Reader._starindex_star->value)+(CL_INT)stack_level));
            color(g0751,g0752);
            color(g0751,g0752);
            color_princ_string1("> ");
            g0751= (int )(current_color);
            g0752= (int )(current_bold);
            color(g0753,g0754);
            print_any(_oid_(z));
            color(g0751,g0752);
            color(g0751,g0752);
            color_princ_string1("\n");
            color(g0753,g0754);
            }
          else { CL_INT  g0755 = (int )(current_color);
              CL_INT  g0756 = (int )(current_bold);
              CL_INT  g0757 = g0755;
              CL_INT  g0758 = g0756;
              color(g0755,g0756);
              color_princ_string1("`GREEN");
              g0755= (int )(current_color);
              g0756= (int )(current_bold);
              color(g0757,g0758);
              princ_integer(((CL_INT)(Reader._starindex_star->value)+(CL_INT)stack_level));
              color(g0755,g0756);
              color(g0755,g0756);
              color_princ_string1("> ");
              g0755= (int )(current_color);
              g0756= (int )(current_bold);
              color(g0757,g0758);
              print_any(_oid_(z));
              color(g0755,g0756);
              color(g0755,g0756);
              color_princ_string1(" -> ");
              g0755= (int )(current_color);
              g0756= (int )(current_bold);
              color(g0757,g0758);
              print_any(_oid_(m));
              color(g0755,g0756);
              color(g0755,g0756);
              color_princ_string1("\n");
              color(g0757,g0758);
              }
            ++stack_level;
          x= ((CL_INT)x-(CL_INT)1);
          j= ClEnv->stack[((OID)j)];
          last_debug= j;
          }
        GC_UNLOOP;POP_SIGNAL;}
      }
    (ClEnv->debug_I = oldd);
    (ClEnv->trace_I = oldt);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: get_current_method(break?:boolean) [RETURN_ARG]
OID  get_current_method_void1(ClaireBoolean *break_ask)
{ { OID Result = 0;
    { CL_INT  j = Reader._starcurd_star->value;
      if ((CL_INT)j <= 0)
       Result = CNULL;
      else { if (break_ask == CTRUE)
           j= ClEnv->stack[((OID)j)];
          if ((break_ask == CTRUE) && 
              ((CL_INT)j <= 0))
           Result = CNULL;
          else { OID  nargs = ClEnv->stack[((OID)((CL_INT)j+(CL_INT)2))];
              CL_INT  start = ClEnv->stack[((OID)((CL_INT)j+(CL_INT)3))];
              property * z = OBJECT(property,ClEnv->stack[((OID)((CL_INT)j+(CL_INT)1))]);
              Result = _oid_(find_which_list1(z->definition,OWNER(ClEnv->stack[((OID)start)]),start,((CL_INT)start+(CL_INT)(nargs))));
              }
            }
        }
    POP_SIGNAL; return (Result);}
  }


// computes the list of variables of a lambda, including everything
//
// The c++ function for: closure_build(self:lambda) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
list * closure_build_lambda(lambda *self)
{ GC_BIND;
  { list *Result ;
    { list * lvar = GC_OBJECT(list,make_list_integer(self->dimension,_oid_(Kernel.emptySet)));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(x);
        bag *x_support;
        x_support = GC_OBJECT(list,self->vars);
        for (START(x_support); NEXT(x);)
        ((*(lvar))[((CL_INT)((*Kernel.index)(x))+(CL_INT)1)]=x);
        }
      closure_build_any(GC_OID(self->body),lvar);
      Result = lvar;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// give to each lexical variable its right position in the stack
// answer with the number of lexical variable
//
// The c++ function for: closure_build(self:any,lvar:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  closure_build_any(OID self,list *lvar)
{ if (INHERIT(OWNER(self),Language._Variable))
   ((*(lvar))[((CL_INT)OBJECT(Variable,self)->index+(CL_INT)1)]=self);
  else if (INHERIT(OWNER(self),Language._Instruction))
   { CL_INT loop_handle = ClEnv->cHandle;
    ITERATE(s);
    for (START(OBJECT(ClaireObject,self)->isa->slots); NEXT(s);)
    closure_build_any(get_slot(OBJECT(slot,s),OBJECT(ClaireObject,self)),lvar);
    }
  else if (INHERIT(OWNER(self),Kernel._bag))
   { CL_INT loop_handle = ClEnv->cHandle;
    ITERATE(x);
    for (START(OBJECT(bag,self)); NEXT(x);)
    closure_build_any(x,lvar);
    }
  else ;POP_SIGNAL;}


// The c++ function for: debug_build(self:lambda) [NEW_ALLOC+SLOT_UPDATE]
list * debug_build_lambda1(lambda *self)
{ GC_BIND;
  { list *Result ;
    { list * lvar = list::empty(Kernel._any);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(x);
        bag *x_support;
        x_support = GC_OBJECT(list,self->vars);
        for (START(x_support); NEXT(x);)
        { lvar->addFast((OID)x);
          (OBJECT(Variable,x)->dindex = (*Kernel.index)(x));
          }
        }
      debug_build_any1(GC_OID(self->body),lvar);
      Result = lvar;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// give to each lexical variable its right position in the stack
// answer with the number of lexical variable
//
// The c++ function for: debug_build(self:any,lvar:list) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  debug_build_any1(OID self,list *lvar)
{ if (INHERIT(OWNER(self),Language._Variable))
   { if (contain_ask_list(lvar,self) != CTRUE)
     { (OBJECT(Variable,self)->dindex = lvar->length);
      lvar->addFast((OID)self);
      }
    }
  else if (INHERIT(OWNER(self),Language._Instruction))
   { CL_INT loop_handle = ClEnv->cHandle;
    ITERATE(s);
    for (START(OBJECT(ClaireObject,self)->isa->slots); NEXT(s);)
    debug_build_any1(get_slot(OBJECT(slot,s),OBJECT(ClaireObject,self)),lvar);
    }
  else if (INHERIT(OWNER(self),Kernel._bag))
   { CL_INT loop_handle = ClEnv->cHandle;
    ITERATE(x);
    for (START(OBJECT(bag,self)); NEXT(x);)
    debug_build_any1(x,lvar);
    }
  else ;POP_SIGNAL;}


// The c++ function for: frame!(debug!:integer) [NEW_ALLOC]
Reader_debug_frame * frame_I_integer1(int debug_I)
{ GC_BIND;
  { Reader_debug_frame *Result ;
    { Reader_debug_frame * fr;
      { { Reader_debug_frame * _CL_obj = ((Reader_debug_frame *) GC_OBJECT(Reader_debug_frame,new_object_class(Reader._debug_frame)));
          (_CL_obj->index = debug_I);
          (_CL_obj->num = 1);
          fr = _CL_obj;
          }
        GC_OBJECT(Reader_debug_frame,fr);}
      init_frame_debug_frame1(fr);
      Result = fr;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: get_location(self:debug_frame) [RETURN_ARG]
list * get_location_debug_frame1(Reader_debug_frame *self)
{ POP_SIGNAL; return (self->locator);}


// The c++ function for: show_source_lines(self:debug_frame,n:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  show_source_lines_debug_frame1(Reader_debug_frame *self,int n)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  if (self->locator->length != 0)
   { if (self->file_lines == (NULL))
     { (self->file_lines = blob_I_void1());
      { ClaireHandler c_handle = ClaireHandler();
        if ERROR_IN 
        { { OID  src = GC_OID((*(self->locator))[1]);
            OID  l = GC_OID((*(self->locator))[2]);
            OID  c = GC_OID((*(self->locator))[3]);
            OID  len = GC_OID((*(self->locator))[4]);
            buffer * f = GC_OBJECT(buffer,fopen_string1(string_v(src),"r"));
            CL_INT  i = 0;
            PortObject * old = use_as_output_port(self->file_lines);
            princ_string("`BLUE[file: `BLACK");
            (*Kernel.princ)(src);
            princ_string("`BLUE]`BLACK\n");
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) f))) != Kernel.ctrue))
              { GC_LOOP;
                ++i;
                if (((OID)i) == l)
                 { princ_string("`BLUE");
                  print_any(((OID)i));
                  princ_string("`BLACK: ");
                  freadwrite_port4(f,GC_OBJECT(PortObject,ClEnv->cout),((CL_INT)(c)-(CL_INT)1));
                  princ_string("`RED");
                  freadwrite_port4(f,GC_OBJECT(PortObject,ClEnv->cout),len);
                  princ_string("`BLACK");
                  princ_string(freadline_port1(f,"\n"));
                  princ_string("\n");
                  }
                else if ((OBJECT(ClaireBoolean,(*Kernel._sup)(((OID)i),
                  GC_OID((*Core._plus)(l,
                    ((OID)n)))))) == CTRUE)
                 { ;ClEnv->cHandle = loop_handle; break;}
                else { char * line = GC_STRING(freadline_port1(f,"\n"));
                    if ((CL_INT)((CL_INT)(l)-(CL_INT)n) <= (CL_INT)i)
                     { princ_string("`BLUE");
                      print_any(((OID)i));
                      princ_string("`BLACK: ");
                      princ_string(line);
                      princ_string("\n");
                      }
                    }
                  GC_UNLOOP;POP_SIGNAL;}
              }
            fclose_filter1(f);
            use_as_output_port(old);
            }
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
        { c_handle.catchIt();{ print_any(GC_OID(_oid_(ClEnv->exception_I)));
            princ_string("\n");
            }
          }
        else PREVIOUS_HANDLER;}
      }
    color_princ_string2((char *)(self->file_lines->data),1,self->file_lines->write_index);
    }
  else { Reader_debug_frame * fr = GC_OBJECT(Reader_debug_frame,next_frame_debug_frame1(self));
      if (fr != self)
       show_source_lines_debug_frame1(fr,n);
      }
    GC_UNBIND; POP_SIGNAL;}


//<sb> initialize a stack frame with debug info that were pushed
// on the stack
// The c++ function for: init_frame(self:debug_frame) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  init_frame_debug_frame1(Reader_debug_frame *self)
{ GC_BIND;
  { CL_INT  j = self->index;
    if ((CL_INT)j > 0)
     { OID  nargs = GC_OID(ClEnv->stack[((OID)((CL_INT)j+(CL_INT)2))]);
      CL_INT  start = ClEnv->stack[((OID)((CL_INT)j+(CL_INT)3))];
      OID  loc = GC_OID(ClEnv->stack[((OID)((CL_INT)start-(CL_INT)1))]);
      OID  z = GC_OID(ClEnv->stack[((OID)((CL_INT)j+(CL_INT)1))]);
      (self->arg_start = start);
      (self->narg = nargs);
      if (INHERIT(OWNER(loc),Core._source_location_star))
       { source_location* l = EXPORT((source_location*),loc);
        if ((((ClaireBoolean *) (ClaireBoolean *)((l ? CTRUE : CFALSE)))) == CTRUE)
         (self->locator = list::alloc(4,_string_((char *)(l->source_file)),
          ((OID)(int )(l->line)),
          ((OID)(int )(l->offset)),
          ((OID)(int )(l->length))));
        }
      else if (INHERIT(OWNER(loc),Language._Call))
       { if (((OBJECT(Call,loc)->location == (NULL)) ? CTRUE : CFALSE) != CTRUE)
         (self->locator = OBJECT(Call,loc)->location);
        }
      if (INHERIT(OWNER(z),Kernel._property))
       { ClaireObject * x = find_which_list1(OBJECT(property,z)->definition,OWNER(ClEnv->stack[((OID)start)]),start,((CL_INT)start+(CL_INT)(nargs)));
        if (Kernel._method == x->isa)
         (self->source = ((method *) x));
        }
      }
    }
  GC_UNBIND; POP_SIGNAL;}


//<sb> go up one frame (identity if self is the top frame)
// The c++ function for: next_frame(self:debug_frame) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
Reader_debug_frame * next_frame_debug_frame1(Reader_debug_frame *self)
{ GC_BIND;
  { Reader_debug_frame *Result ;
    if (((self->next == (NULL)) ? CTRUE : CFALSE) != CTRUE)
     Result = self->next;
    else { OID  n = GC_OID(ClEnv->stack[((OID)self->index)]);
        if (n == ((OID)0))
         Result = self;
        else { Reader_debug_frame * nf;
            { { Reader_debug_frame * _CL_obj = ((Reader_debug_frame *) GC_OBJECT(Reader_debug_frame,new_object_class(Reader._debug_frame)));
                (_CL_obj->index = n);
                nf = _CL_obj;
                }
              GC_OBJECT(Reader_debug_frame,nf);}
            (self->next = nf);
            (nf->prev = self);
            (nf->num = ((CL_INT)self->num+(CL_INT)1));
            init_frame_debug_frame1(nf);
            Result = nf;
            }
          }
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: prev_frame(self:debug_frame) [RETURN_ARG]
Reader_debug_frame * prev_frame_debug_frame1(Reader_debug_frame *self)
{ { Reader_debug_frame *Result ;
    Result = ((((self->prev == (NULL)) ? CTRUE : CFALSE) != CTRUE) ?
      self->prev :
      self );
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: get_frame(self:debug_frame,i:integer) [NEW_ALLOC+RETURN_ARG]
Reader_debug_frame * get_frame_debug_frame1(Reader_debug_frame *self,int i)
{ if (self->num == i) 
  { { Reader_debug_frame *Result ;
      Result = self;
      return (Result);}
     }
  else{ GC_BIND;
    { Reader_debug_frame *Result ;
      if ((CL_INT)i < 1)
       { { CL_INT  g0759 = (int )(current_color);
          CL_INT  g0760 = (int )(current_bold);
          CL_INT  g0761 = g0759;
          CL_INT  g0762 = g0760;
          color(g0759,g0760);
          color_princ_string1("`REDinvalid frame index ");
          g0759= (int )(current_color);
          g0760= (int )(current_bold);
          color(g0761,g0762);
          print_any(((OID)i));
          color(g0759,g0760);
          color(g0759,g0760);
          color_princ_string1("\n");
          color(g0761,g0762);
          }
        Result = self;
        }
      else if ((CL_INT)i < (CL_INT)self->num)
       Result = get_frame_debug_frame1(prev_frame_debug_frame1(self),i);
      else { Reader_debug_frame * n = GC_OBJECT(Reader_debug_frame,next_frame_debug_frame1(self));
          if (n == self)
           { { CL_INT  g0763 = (int )(current_color);
              CL_INT  g0764 = (int )(current_bold);
              CL_INT  g0765 = g0763;
              CL_INT  g0766 = g0764;
              color(g0763,g0764);
              color_princ_string1("`REDtop frame\n");
              color(g0765,g0766);
              }
            Result = self;
            }
          else Result = get_frame_debug_frame1(n,i);
            }
        GC_UNBIND; POP_SIGNAL; return (Result);}
    }
  }


// The c++ function for: get_vars(self:debug_frame) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  get_vars_debug_frame1(Reader_debug_frame *self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  if (boolean_I_any(_oid_(self->vars)) != CTRUE)
   { method * m = self->source;
    if (m == (NULL))
     ;else if (Kernel._method == m->isa)
     { if ((((m->formula == (NULL)) ? CTRUE : CFALSE) != CTRUE) && 
          (INHERIT(m->formula->isa,Core._lambda)))
       { list * cb = GC_OBJECT(list,closure_build_lambda(GC_OBJECT(lambda,m->formula)));
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(v);
          for (START(cb); NEXT(v);)
          { GC_LOOP;
            if (INHERIT(OWNER(v),Language._Variable))
             GC_OBJECT(list,self->vars)->addFast((OID)_oid_(tuple::alloc(2,_string_(OBJECT(Variable,v)->pname->name),GC_OID(ClEnv->stack[((OID)((CL_INT)self->arg_start+(CL_INT)OBJECT(Variable,v)->index))]))));
            GC_UNLOOP; POP_SIGNAL;}
          }
        }
      else if (m->compiled_variables != Kernel.cfalse)
       { OID  names = GC_OID(m->compiled_variables);
        CL_INT  i = 1;
        CL_INT  g0767 = (*Kernel.length)(names);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)i <= (CL_INT)g0767))
          { GC_LOOP;
            { OID  vn = GC_OID((*Kernel.nth)(names,
                ((OID)i)));
              if ((*Kernel.length)(vn) == ((OID)0))
               GC_OBJECT(list,self->vars)->addFast((OID)Core.nil->value);
              else GC_OBJECT(list,self->vars)->addFast((OID)_oid_(tuple::alloc(2,vn,GC_OID(ClEnv->stack[((OID)((CL_INT)((CL_INT)self->arg_start+(CL_INT)i)-(CL_INT)1))]))));
                }
            ++i;
            GC_UNLOOP;POP_SIGNAL;}
          }
        }
      else { CL_INT  i = 1;
          CL_INT  g0768 = self->narg;
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while (((CL_INT)i <= (CL_INT)g0768))
            { GC_LOOP;
              GC_OBJECT(list,self->vars)->addFast((OID)_oid_(tuple::alloc(2,_string_(""),GC_OID(ClEnv->stack[((OID)((CL_INT)((CL_INT)self->arg_start+(CL_INT)i)-(CL_INT)1))]))));
              ++i;
              GC_UNLOOP;POP_SIGNAL;}
            }
          }
        }
    }
  { OID Result = 0;
    Result = _oid_(self->vars);
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: show_frame(self:debug_frame) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  show_frame_debug_frame1(Reader_debug_frame *self)
{ GC_RESERVE(9);  // v3.0.55 optim !
  { CL_INT  g0769 = (int )(current_color);
    CL_INT  g0770 = (int )(current_bold);
    CL_INT  g0771 = g0769;
    CL_INT  g0772 = g0770;
    color(g0769,g0770);
    color_princ_string1("`BLUE");
    g0769= (int )(current_color);
    g0770= (int )(current_bold);
    color(g0771,g0772);
    { method * m = self->source;
      if (m == (NULL))
       ;else { CL_INT  g0773 = (int )(current_color);
          CL_INT  g0774 = (int )(current_bold);
          CL_INT  g0775 = g0773;
          CL_INT  g0776 = g0774;
          color(g0773,g0774);
          color_princ_string1("`BLUE[");
          g0773= (int )(current_color);
          g0774= (int )(current_bold);
          color(g0775,g0776);
          print_any(_oid_(m->module_I));
          color(g0773,g0774);
          color(g0773,g0774);
          color_princ_string1("] ");
          color(g0775,g0776);
          }
        }
    color(g0769,g0770);
    color(g0771,g0772);
    print_any(((OID)self->num));
    color(g0769,g0770);
    color(g0769,g0770);
    color_princ_string1("> ");
    g0769= (int )(current_color);
    g0770= (int )(current_bold);
    color(g0771,g0772);
    { method * m = self->source;
      if (m == (NULL))
       { CL_INT  g0777 = (int )(current_color);
        CL_INT  g0778 = (int )(current_bold);
        CL_INT  g0779 = g0777;
        CL_INT  g0780 = g0778;
        color(g0777,g0778);
        color_princ_string1("`REDunknown");
        color(g0779,g0780);
        }
      else { color_princ_string1("`BLUE");
          print_any(GC_OID(get_property(Kernel.selector,m)));
          princ_string("(");
          { CL_INT  i = 1;
            OID  vs = GC_OID(get_vars_debug_frame1(self));
            CL_INT  len = self->narg;
            ClaireBoolean * f_ask = CTRUE;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              while (((CL_INT)i <= (CL_INT)len))
              { GC_LOOP;
                { OID  v = GC_OID((*Kernel.nth)(vs,
                    ((OID)i)));
                  OID  vn = GC_OID((*Kernel.nth)(v,
                    ((OID)1)));
                  OID  val = GC_OID((*Kernel.nth)(v,
                    ((OID)2)));
                  ++i;
                  { CL_INT  g0781 = (int )(current_color);
                    CL_INT  g0782 = (int )(current_bold);
                    CL_INT  g0783 = g0781;
                    CL_INT  g0784 = g0782;
                    color(g0783,g0784);
                    if (f_ask == CTRUE)
                     f_ask= CFALSE;
                    else { CL_INT  g0785 = (int )(current_color);
                        CL_INT  g0786 = (int )(current_bold);
                        CL_INT  g0787 = g0785;
                        CL_INT  g0788 = g0786;
                        color(g0785,g0786);
                        color_princ_string1("`BLUE, ");
                        color(g0787,g0788);
                        }
                      color(g0781,g0782);
                    color(g0783,g0784);
                    if ((CL_INT)(*Kernel.length)(vn) > 0)
                     { color_princ_string1("`BLUE");
                      (*Kernel.princ)(vn);
                      princ_string(" = ");
                      }
                    color(g0781,g0782);
                    color(g0783,g0784);
                    print_any(val);
                    color(g0781,g0782);
                    color(g0781,g0782);
                    color_princ_string1("`BLACK");
                    color(g0783,g0784);
                    }
                  }
                GC_UNLOOP;POP_SIGNAL;}
              }
            }
          princ_string(")");
          }
        }
    color(g0769,g0770);
    color(g0769,g0770);
    color_princ_string1("\n");
    color(g0771,g0772);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: show_frame_info(self:debug_frame) [0]
void  show_frame_info_debug_frame1(Reader_debug_frame *self)
{ show_frame_debug_frame1(self);
  show_source_lines_debug_frame1(self,1);
  POP_SIGNAL;}


// The c++ function for: show_locale_variable(self:debug_frame) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  show_locale_variable_debug_frame1(Reader_debug_frame *self)
{ GC_RESERVE(7);  // v3.0.55 optim !
  if (self->narg == (CNULL))
   princ_string(" -- frame miss variable info --\n");
  else { CL_INT  i = ((CL_INT)self->narg+(CL_INT)1);
      OID  vs = GC_OID(get_vars_debug_frame1(self));
      CL_INT  len = (*Kernel.length)(vs);
      if ((CL_INT)i > (CL_INT)len)
       princ_string(" -- frame has no variable --\n");
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)i <= (CL_INT)len))
        { GC_LOOP;
          { OID  v = GC_OID((*Kernel.nth)(vs,
              ((OID)i)));
            if (equal(v,Core.nil->value) != CTRUE)
             { OID  vn = GC_OID((*Kernel.nth)(v,
                ((OID)1)));
              OID  val = GC_OID((*Kernel.nth)(v,
                ((OID)2)));
              CL_INT  g0789 = (int )(current_color);
              CL_INT  g0790 = (int )(current_bold);
              CL_INT  g0791 = g0789;
              CL_INT  g0792 = g0790;
              color(g0789,g0790);
              color_princ_string1("  `BLUE");
              g0789= (int )(current_color);
              g0790= (int )(current_bold);
              color(g0791,g0792);
              color_princ_string1("`BLUE");
              (*Kernel.princ)(vn);
              color(g0789,g0790);
              color(g0789,g0790);
              color_princ_string1(" = ");
              g0789= (int )(current_color);
              g0790= (int )(current_bold);
              color(g0791,g0792);
              print_any(val);
              color(g0789,g0790);
              color(g0789,g0790);
              color_princ_string1("\n");
              color(g0791,g0792);
              }
            ++i;
            }
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    GC_UNBIND; POP_SIGNAL;}


// ******************************************************************
// *    Part 4: The Stepper                                         *
// ******************************************************************
// the stepper interface is quite simple and could be improved
//
// memory usage statistics for a class
// The c++ function for: mem(c:class) [NEW_ALLOC]
int  mem_class(ClaireClass *c)
{ { CL_INT Result = 0;
    { CL_INT  n = 0;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(x);
        for (START(c->instances); NEXT(x);)
        { n= ((CL_INT)n+(CL_INT)(slot_get_object(OBJECT(ClaireObject,x),0,Kernel._integer)));
          { CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(sl);
            for (START(c->slots); NEXT(sl);)
            { ClaireType * rs = OBJECT(restriction,sl)->range;
              if (rs == Kernel._float)
               n= ((CL_INT)n+(CL_INT)5);
              else if (rs == Kernel._string)
               { OID  st = get_slot(OBJECT(slot,sl),OBJECT(ClaireObject,x));
                if (st != CNULL)
                 n= ((CL_INT)n+(CL_INT)min_integer1(5,((CL_INT)LENGTH_STRING(string_v(st))/(CL_INT)2)));
                else ;}
              else if (_inf_equal_type(rs,Kernel._bag) == CTRUE)
               { OID  l = get_slot(OBJECT(slot,sl),OBJECT(ClaireObject,x));
                if (l != CNULL)
                 n= ((CL_INT)n+(CL_INT)((*(OBJECT(bag,l)))[0]));
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
// *      Part 5: Profiler                                             *
// *********************************************************************
// we use a counter object for the 5 interesting values  and
// we use the reified slot to store the counter (thus no profiling on reified)
// start time (1st entry)
// get & create if needed a PRcounter
// The c++ function for: PRget(p:property) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
PRcount * PRget_property(property *p)
{ GC_BIND;
  { PRcount *Result ;
    { ClaireObject *V_CC ;
      { ClaireObject * x = GC_OBJECT(ClaireObject,p->reified);
        if (OWNER(_oid_(x)) == Reader._PRcount)
         V_CC = x;
        else if (x == CTRUE)
         close_exception(((general_error *) (*Core._general_error)(_string_("[131] Cannot profile a reified property ~S"),
          _oid_(list::alloc(1,_oid_(p))))));
        else { { PRcount * _CL_obj = ((PRcount *) GC_OBJECT(PRcount,new_object_class(Reader._PRcount)));
              add_I_property(Kernel.instances,Reader._PRcount,11,_oid_(_CL_obj));
              x = _CL_obj;
              }
            (p->reified = x);
            V_CC = x;
            }
          }
      Result= (PRcount *) V_CC;}
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// get & create if needed a PRcounter
// The c++ function for: PRlook(p:property) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  PRlook_property2(property *p)
{ POP_SIGNAL; return (show_any(_oid_(PRget_property(p))));}


// show the profiler statistics on one property
// The c++ function for: PRshow(p:property) [NEW_ALLOC]
void  PRshow_property(property *p)
{ GC_BIND;
  { ClaireObject * x = GC_OBJECT(ClaireObject,p->reified);
    if (INHERIT(x->isa,Reader._PRcount))
     { print_any(_oid_(p));
      princ_string(": ");
      princ_integer(CLREAD(PRcount,x,rnum));
      princ_string(" calls -> ");
      princ_integer(CLREAD(PRcount,x,rtime));
      princ_string(" clock tics\n");
      }
    }
  GC_UNBIND; POP_SIGNAL;}


// elapsed time
// The c++ function for: PRtime(p:property) [RETURN_ARG]
int  PRtime_property(property *p)
{ { CL_INT Result = 0;
    { ClaireObject * x = p->reified;
      Result = ((INHERIT(x->isa,Reader._PRcount)) ?
        CLREAD(PRcount,x,rtime) :
        0 );
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: PRcounter(p:property) [RETURN_ARG]
int  PRcounter_property(property *p)
{ { CL_INT Result = 0;
    { ClaireObject * x = p->reified;
      Result = ((INHERIT(x->isa,Reader._PRcount)) ?
        CLREAD(PRcount,x,rnum) :
        0 );
      }
    POP_SIGNAL; return (Result);}
  }


// show the profiler statistics on the 10 most important properties
// The c++ function for: PRshow(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE]
void  PRshow_void()
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { list * l = list::empty(Kernel._property);
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(g0793);
      bag *g0793_support;
      g0793_support = Kernel._property->descendents;
      for (START(g0793_support); NEXT(g0793);)
      { GC_LOOP;
        { ClaireBoolean * g0794;
          { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(p);
              V_C= Kernel.cfalse;
              for (START(OBJECT(ClaireClass,g0793)->instances); NEXT(p);)
              { GC_LOOP;
                { ClaireBoolean * g0796I;
                  { OID  g0797UU;
                    { CL_INT  i = 1;
                      CL_INT  g0795 = min_integer1(10,l->length);
                      { CL_INT loop_handle = ClEnv->cHandle;
                        OID gc_local;
                        g0797UU= _oid_(CFALSE);
                        while (((CL_INT)i <= (CL_INT)g0795))
                        { { ClaireBoolean * g0798I;
                            if (((CL_INT)PRtime_property(OBJECT(property,p)) > (CL_INT)PRtime_property(OBJECT(property,(*(l))[i]))) || 
                                ((PRtime_property(OBJECT(property,p)) == PRtime_property(OBJECT(property,(*(l))[i]))) && 
                                    ((CL_INT)PRcounter_property(OBJECT(property,p)) > (CL_INT)PRcounter_property(OBJECT(property,(*(l))[i])))))
                             { l= add_at_list(l,i,p);
                              g0798I = CTRUE;
                              }
                            else g0798I = CFALSE;
                              
                            if (g0798I == CTRUE) { g0797UU = Kernel.ctrue;
                                ClEnv->cHandle = loop_handle;break;}
                              }
                          ++i;
                          POP_SIGNAL;}
                        }
                      }
                    g0796I = boolean_I_any(g0797UU);
                    }
                  
                  if (g0796I == CTRUE) ;else if ((CL_INT)l->length < 10)
                   GC__ANY(l = l->addFast((OID)p), 1);
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            
            g0794=OBJECT(ClaireBoolean,V_C);}
          if (g0794 == CTRUE)
           { ;ClEnv->cHandle = loop_handle; break;}
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    shrink_list(l,10);
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(p);
      for (START(l); NEXT(p);)
      if ((CL_INT)PRcounter_property(OBJECT(property,p)) > 0)
       { princ_string("-----------------------------------\n");
        PRshow_property(OBJECT(property,p));
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          ITERATE(p2);
          bag *p2_support;
          p2_support = OBJECT(bag,nth_table1(Reader.PRdependent,p));
          for (START(p2_support); NEXT(p2);)
          if ((CL_INT)PRtime_property(OBJECT(property,p2)) > 0)
           { princ_string("   * ");
            PRshow_property(OBJECT(property,p2));
            }
          }
        }
      }
    }
  GC_UNBIND; POP_SIGNAL;}


// reuse from lexical_build in pretty.cl
// returns the list of properties that are used by a method
// The c++ function for: dependents(self:method) [NEW_ALLOC]
set * dependents_method(method *self)
{ GC_BIND;
  { set *Result ;
    { set * p_out = set::empty(Kernel._property);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(p);
        bag *p_support;
        p_support = GC_OBJECT(bag,enumerate_any(GC_OID((*Reader.dependents)(self->formula->body))));
        for (START(p_support); NEXT(p);)
        { ClaireBoolean * g0799I;
          { OID  g0800UU;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(r);
              g0800UU= Kernel.cfalse;
              for (START(OBJECT(property,p)->restrictions); NEXT(r);)
              if (Kernel._method == OBJECT(ClaireObject,r)->isa)
               { g0800UU = Kernel.ctrue;
                ClEnv->cHandle = loop_handle;break;}
              }
            g0799I = boolean_I_any(g0800UU);
            }
          
          if (g0799I == CTRUE) p_out->addFast((OID)p);
            }
        }
      Result = GC_OBJECT(set,p_out);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// this is really cute ....   v3.2.58: fix typing
// The c++ function for: dependents(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  dependents_any(OID self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
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
          GC__ANY(s = ((set *) U_type(s,GC_OBJECT(ClaireType,OBJECT(ClaireType,(*Reader.dependents)(x))))), 1);
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
void  PRdepends_property(property *p,property *p2)
{ add_table(Reader.PRdependent,_oid_(p),_oid_(p2));
  ;POP_SIGNAL;}


// end of file

