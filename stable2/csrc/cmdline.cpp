/***** CLAIRE Compilation of file ./meta/cmdline.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:37 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>

// *********************************************************************
// * CLAIRE                                            Sylvain Benilan *
// * cmdline.cl                                                        *
// * Copyright (C) 2005 xl. All Rights Reserved                        *
// *********************************************************************
//<sb> command line parsing and option dispatch
// any module may define the following restrictions :
// *********************************************************************
// * Part 1: main options usage                                        *
// * Part 2: option help parsing                                       *
// * Part 3: option dispatch                                           *
// *********************************************************************
// *********************************************************************
// * Part 1: main options usage                                        *
// *********************************************************************
// The c++ function for: option_usage(g0198:{"-h", "-help"}) [NEW_ALLOC]
tuple * option_usage_string1_Core_(char *g0198)
{ return option_usage_string1_Core(g0198)->copyIfNeeded();}


// The c++ function for: option_usage(opt:{"-h", "-help"}) [NEW_ALLOC]
tuple * option_usage_string1_Core(char *opt)
{ GC_BIND;
  { tuple *Result ;
    Result = tuple::allocStack(3,_string_("Command line help"),
      _string_("{-h | -help} +[<m:module> | <option:string> | <index:integer>]"),
      GC_OID(_string_(append_string("Display an option index. When <module>, <option> or <index> are given ","the full help is displayed for the requested entities."))));
    GC_UNBIND; return (Result);}
  }


// The c++ function for: option_usage(g0199:{"-about"}) [NEW_ALLOC]
tuple * option_usage_string2_Core_(char *g0199)
{ return option_usage_string2_Core(g0199)->copyIfNeeded();}


// The c++ function for: option_usage(opt:{"-about"}) [NEW_ALLOC]
tuple * option_usage_string2_Core(char *opt)
{ { tuple *Result ;
    Result = tuple::allocStack(3,_string_("About box"),
      _string_("-about"),
      _string_("Display an about message."));
    return (Result);}
  }


// The c++ function for: option_usage(g0200:{"-auto", "-s"}) [NEW_ALLOC]
tuple * option_usage_string3_Core_(char *g0200)
{ return option_usage_string3_Core(g0200)->copyIfNeeded();}


// The c++ function for: option_usage(opt:{"-auto", "-s"}) [NEW_ALLOC]
tuple * option_usage_string3_Core(char *opt)
{ GC_BIND;
  { tuple *Result ;
    Result = tuple::allocStack(3,_string_("Memory initialization"),
      _string_("[-auto] -s <main:(0 .. 9)> <world:(0 .. 9)>"),
      GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string(GC_STRING(append_string("Sets parameters used to initialize CLAIRE memory. The main/world ","memory is increased in a chunk of a two exponent of <main>/<world> argument. ")),"The main memory is used for normal object allocation and the world ")),"memory is used to store defeasible updates.\n")),"When <-auto> is specified the memory is silently allocated to its maximum ")),"but still constrained in a chunk as specified by the <-s> option. ")),"The option <-auto> takes effect arround memory congestion (near an overflow) ")),"where it let the concerned memory to be silently increased such a program ")),"that require more memory (than specified by the <-s> option) can acheive it task. ")),"A program runned in <-auto> will take advantage of modern OS that ")),"actualy manage true virtual pages. The <-auto> flag only controls ")),"the memory congestion issue but never perform any decongestion."))));
    GC_UNBIND; return (Result);}
  }


// The c++ function for: option_usage(g0201:{"-v"}) [NEW_ALLOC]
tuple * option_usage_string4_Core_(char *g0201)
{ return option_usage_string4_Core(g0201)->copyIfNeeded();}


// The c++ function for: option_usage(opt:{"-v"}) [NEW_ALLOC]
tuple * option_usage_string4_Core(char *opt)
{ GC_BIND;
  { tuple *Result ;
    Result = tuple::allocStack(3,_string_("Verbose"),
      _string_("-v [<m:module>] <level:integer>"),
      GC_OID(_string_(append_string(GC_STRING(append_string("Sets the system verbosity level. Any trace instruction with a level ","lower or equal to <verbose> are issued and others prevented. ")),"When <m> is specified the verbosity of the given module is set instead."))));
    GC_UNBIND; return (Result);}
  }


// The c++ function for: option_usage(g0202:{"-q"}) [NEW_ALLOC]
tuple * option_usage_string5_Core_(char *g0202)
{ return option_usage_string5_Core(g0202)->copyIfNeeded();}


// The c++ function for: option_usage(opt:{"-q"}) [NEW_ALLOC]
tuple * option_usage_string5_Core(char *opt)
{ GC_BIND;
  { tuple *Result ;
    Result = tuple::allocStack(3,_string_("Exit now"),
      _string_("-q [<exitcode:integer>]"),
      GC_OID(_string_(append_string(GC_STRING(append_string("Exit now, do not process the end of the command line, do not start an interpreter. ","When <exitcode> is specified, it is used as the program exit code which is 0 otherwise.\n")),"The <-q> option is always reached even if an exeception has occured before."))));
    GC_UNBIND; return (Result);}
  }


// The c++ function for: option_usage(g0203:{"-qonerror", "-errassegv"}) [NEW_ALLOC]
tuple * option_usage_string6_Core_(char *g0203)
{ return option_usage_string6_Core(g0203)->copyIfNeeded();}


// The c++ function for: option_usage(opt:{"-qonerror", "-errassegv"}) [NEW_ALLOC]
tuple * option_usage_string6_Core(char *opt)
{ GC_BIND;
  { tuple *Result ;
    Result = tuple::allocStack(3,_string_("Early termination"),
      _string_("-qonerror | -errassegv"),
      GC_OID(_string_(append_string(GC_STRING(append_string("These options produce an early termination when an uncatched exception occurs. ","With <-qonerror> the program will exit with code 1 and with <-errassegv> it ")),"will raise a segmentation violation signal."))));
    GC_UNBIND; return (Result);}
  }


// The c++ function for: option_usage(g0204:{"-nologo"}) [NEW_ALLOC]
tuple * option_usage_string7_Core_(char *g0204)
{ return option_usage_string7_Core(g0204)->copyIfNeeded();}


// The c++ function for: option_usage(opt:{"-nologo"}) [NEW_ALLOC]
tuple * option_usage_string7_Core(char *opt)
{ { tuple *Result ;
    Result = tuple::allocStack(3,_string_("Avoid banner"),
      _string_("-nologo"),
      _string_("Avoid the banner message to be displayed at startup."));
    return (Result);}
  }


// The c++ function for: option_usage(g0205:{"-noel"}) [NEW_ALLOC]
tuple * option_usage_string8_Core_(char *g0205)
{ return option_usage_string8_Core(g0205)->copyIfNeeded();}


// The c++ function for: option_usage(opt:{"-noel"}) [NEW_ALLOC]
tuple * option_usage_string8_Core(char *opt)
{ { tuple *Result ;
    Result = tuple::allocStack(3,_string_("Avoid editline"),
      _string_("-noel"),
      _string_("Do not use editline for the interpreter."));
    return (Result);}
  }


// The c++ function for: option_usage(g0206:{"-color", "-nocolor"}) [NEW_ALLOC]
tuple * option_usage_string9_Core_(char *g0206)
{ return option_usage_string9_Core(g0206)->copyIfNeeded();}


// The c++ function for: option_usage(opt:{"-color", "-nocolor"}) [NEW_ALLOC]
tuple * option_usage_string9_Core(char *opt)
{ { tuple *Result ;
    Result = tuple::allocStack(3,_string_("Terminal color"),
      _string_("-color | -nocolor"),
      _string_("Enable (or not) the support for terminal colors. Disabled by default."));
    return (Result);}
  }


// The c++ function for: option_usage(g0207:{"-trace"}) [NEW_ALLOC]
tuple * option_usage_string10_Core_(char *g0207)
{ return option_usage_string10_Core(g0207)->copyIfNeeded();}


// The c++ function for: option_usage(opt:{"-trace"}) [NEW_ALLOC]
tuple * option_usage_string10_Core(char *opt)
{ GC_BIND;
  { tuple *Result ;
    Result = tuple::allocStack(3,_string_("Trace file"),
      _string_("-trace [a | append] <file:path>"),
      GC_OID(_string_(append_string("Redirect traces to <file>. The file is overwriten unless 'a' or 'append' ","is specified. Traces depends on the verbosity level (see option <-v>)."))));
    GC_UNBIND; return (Result);}
  }


// The c++ function for: option_usage(g0208:{"-sample"}) [NEW_ALLOC]
tuple * option_usage_string11_Core_(char *g0208)
{ return option_usage_string11_Core(g0208)->copyIfNeeded();}


// The c++ function for: option_usage(opt:{"-sample"}) [NEW_ALLOC]
tuple * option_usage_string11_Core(char *opt)
{ GC_BIND;
  { tuple *Result ;
    Result = tuple::allocStack(3,_string_("Sampling Cmemory"),
      _string_("-sample <period:integer>"),
      GC_OID(_string_(append_string(GC_STRING(append_string("Perform photoes of Cmemory at intervals of <period> millseconds. ","A file clmeormy.samples is issued and may be used with gnuplot to ")),"produce a graph."))));
    GC_UNBIND; return (Result);}
  }


// The c++ function for: option_usage(g0209:{"-chdir"}) [NEW_ALLOC]
tuple * option_usage_string12_Core_(char *g0209)
{ return option_usage_string12_Core(g0209)->copyIfNeeded();}


// The c++ function for: option_usage(opt:{"-chdir"}) [NEW_ALLOC]
tuple * option_usage_string12_Core(char *opt)
{ { tuple *Result ;
    Result = tuple::allocStack(3,_string_("Change directory"),
      _string_("-chdir <dir:relative path>"),
      _string_("Change the current working directory to <dir>"));
    return (Result);}
  }


// *********************************************************************
// * Part 2: option help parsing                                       *
// *********************************************************************
// The c++ function for: print_var(self:string) [0]
void  print_var_string1(char *self)
{ color(32,0);
  princ_string("<");
  princ_string(self);
  princ_string(">");
  color(30,0);
  POP_SIGNAL;}


// The c++ function for: print_option(self:string) [NEW_ALLOC]
void  print_option_string1(char *self)
{ GC_RESERVE(5);  // v3.0.55 optim !
  { blob * p = GC_OBJECT(blob,blob_I_string1(self));
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))) != Kernel.ctrue))
      { GC_LOOP;
        { tuple * g0210 = freadline_port4(p,set::alloc(Kernel.emptySet,1,_string_("<")));
          char * o = GC_STRING(string_v((*(g0210))[1]));
          OID  sep = GC_OID((*(g0210))[2]);
          color(34,0);
          princ_string(o);
          if (equal(sep,_string_("<")) == CTRUE)
           print_var_string1(freadline_port1(p,">"));
          }
        GC_UNLOOP;POP_SIGNAL;}
      }
    }
  color(30,0);
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: print_module(self:module) [NEW_ALLOC]
void  print_module_module1(module *self)
{ princ_string("====== ");
  print_any(_oid_(self));
  princ_string(" options ======\n");
  POP_SIGNAL;}


// The c++ function for: parse_var(p:port,opts:list[string],vars:list[string],rngs:list[string]) [NEW_ALLOC]
char * parse_var_port1(PortObject *p,list *opts,list *vars,list *rngs)
{ GC_BIND;
  { char *Result ;
    { tuple * g0211 = freadline_port4(p,OBJECT(bag,Core.VAR_END->value));
      OID  var = GC_OID((*(g0211))[1]);
      OID  sep = GC_OID((*(g0211))[2]);
      vars= GC_OBJECT(list,vars->addFast((OID)var));
      if (equal(sep,_string_(":")) == CTRUE)
       { char * rng = GC_STRING(freadline_port1(p,">"));
        rngs= GC_OBJECT(list,rngs->addFast((OID)_string_(rng)));
        }
      else rngs= GC_OBJECT(list,rngs->addFast((OID)_string_("unknown")));
        Result = string_v(var);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: parse_option(p:port,opts:list[string],vars:list[string],rngs:list[string]) [NEW_ALLOC+RETURN_ARG]
void  parse_option_port1(PortObject *p,list *opts,list *vars,list *rngs)
{ GC_RESERVE(8);  // v3.0.55 optim !
  { char * opt = "-";
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))) != Kernel.ctrue))
      { GC_LOOP;
        { tuple * g0212 = freadline_port4(p,OBJECT(bag,Core.OPT_END->value));
          char * o = GC_STRING(string_v((*(g0212))[1]));
          OID  sep = GC_OID((*(g0212))[2]);
          GC__STRING(opt = append_string(opt,o), 5);
          if (equal(sep,_string_("<")) == CTRUE)
           GC__STRING(opt = append_string(opt,GC_STRING(append_string(GC_STRING(append_string("<",GC_STRING(parse_var_port1(p,opts,vars,rngs)))),">"))), 5);
          else { GC__ANY(opts = opts->addFast((OID)_string_(opt)), 2);
              print_option_string1(opt);
              (*Kernel.princ)(sep);
              { ;ClEnv->cHandle = loop_handle; break;}
              }
            }
        GC_UNLOOP;POP_SIGNAL;}
      }
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: print_back_option_usage(self:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
list * print_back_option_usage_string1(char *self)
{ GC_BIND;
  { list *Result ;
    { blob * p = GC_OBJECT(blob,blob_I_string1(self));
      Result = print_back_option_usage_port1(p);
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: print_back_option_usage(p:port) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
list * print_back_option_usage_port1(PortObject *p)
{ GC_RESERVE(7);  // v3.0.55 optim !
  { list *Result ;
    { list * vars = list::empty(Kernel._string);
      list * rngs = list::empty(Kernel._string);
      list * opts = list::empty(Kernel._string);
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))) != Kernel.ctrue))
        { GC_LOOP;
          { tuple * g0213 = freadline_port4(p,OBJECT(bag,Core.CMD_SEPS->value));
            char * dummy = GC_STRING(string_v((*(g0213))[1]));
            OID  sep = GC_OID((*(g0213))[2]);
            princ_string(dummy);
            if ((equal(sep,_string_("[")) == CTRUE) || 
                ((equal(sep,_string_("]")) == CTRUE) || 
                  ((equal(sep,_string_("|")) == CTRUE) || 
                    ((equal(sep,_string_("{")) == CTRUE) || 
                      (equal(sep,_string_("}")) == CTRUE)))))
             princ_string(string_v(sep));
            else if (equal(sep,_string_("-")) == CTRUE)
             parse_option_port1(p,opts,vars,rngs);
            else if (equal(sep,_string_("<")) == CTRUE)
             print_var_string1(parse_var_port1(p,opts,vars,rngs));
            else if (equal(sep,_string_(" ")) == CTRUE)
             princ_string(" ");
            }
          GC_UNLOOP;POP_SIGNAL;}
        }
      Result = list::alloc(3,_oid_(opts),
        _oid_(vars),
        _oid_(rngs));
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: print_back_option_help(self:string,l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  print_back_option_help_string1(char *self,list *l)
{ GC_BIND;
  { blob * p = GC_OBJECT(blob,blob_I_string1(self));
    print_back_option_help_port1(p,l);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: print_back_option_help(p:port,l:list) [NEW_ALLOC]
void  print_back_option_help_port1(PortObject *p,list *l)
{ GC_RESERVE(6);  // v3.0.55 optim !
  princ_string("    ");
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    while ((_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))) != Kernel.ctrue))
    { GC_LOOP;
      { tuple * g0214 = freadline_port4(p,set::alloc(Kernel.emptySet,2,_string_("<"),_string_("\n")));
        char * data = GC_STRING(string_v((*(g0214))[1]));
        OID  sep = GC_OID((*(g0214))[2]);
        color_princ_string1(data);
        if (equal(sep,_string_("\n")) == CTRUE)
         princ_string("\n    ");
        else if (_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) p))) != Kernel.ctrue)
         { char * varopt = GC_STRING(freadline_port1(p,">"));
          if (belong_to(_string_(varopt),(*(l))[1]) == CTRUE)
           print_option_string1(varopt);
          else print_var_string1(varopt);
            }
        }
      GC_UNLOOP;POP_SIGNAL;}
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: find_option_usage(self:integer) [0]
OID  find_option_usage_integer1(int self)
{ { OID Result = 0;
    { list * l = Core.option_usage->restrictions;
      CL_INT  idx = 0;
      OID  good = CNULL;
      { CL_INT loop_handle = ClEnv->cHandle;
        ITERATE(g0215);
        bag *g0215_support;
        g0215_support = Kernel._module->descendents;
        for (START(g0215_support); NEXT(g0215);)
        { ClaireBoolean * g0216;
          { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(m);
              V_C= Kernel.cfalse;
              for (START(OBJECT(ClaireClass,g0215)->instances); NEXT(m);)
              { if (good != CNULL)
                 { V_C = Kernel.ctrue;
                  ClEnv->cHandle = loop_handle;break;}
                { CL_INT loop_handle = ClEnv->cHandle;
                  ITERATE(r);
                  for (START(l); NEXT(r);)
                  if (_oid_(OBJECT(restriction,r)->module_I) == m)
                   { ++idx;
                    if (idx == self)
                     { good= r;
                      { ;ClEnv->cHandle = loop_handle; break;}
                      }
                    }
                  }
                }
              }
            
            g0216=OBJECT(ClaireBoolean,V_C);}
          if (g0216 == CTRUE)
           { ;ClEnv->cHandle = loop_handle; break;}
          }
        }
      Result = good;
      }
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: find_option_usage(self:string) [NEW_ALLOC]
OID  find_option_usage_string1(char *self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { OID Result = 0;
    { OID  r_some = CNULL;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(r);
        for (START(Core.option_usage->restrictions); NEXT(r);)
        { GC_LOOP;
          { ClaireBoolean * g0217I;
            { OID  g0218UU;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(w);
                g0218UU= Kernel.cfalse;
                bag *w_support;
                w_support = GC_OBJECT(bag,enumerate_any((*(OBJECT(restriction,r)->domain))[1]));
                for (START(w_support); NEXT(w);)
                if (match_wildcard_ask_string(self,string_v(w)) == CTRUE)
                 { g0218UU = Kernel.ctrue;
                  ClEnv->cHandle = loop_handle;break;}
                }
              g0217I = boolean_I_any(g0218UU);
              }
            
            if (g0217I == CTRUE) { r_some= r;
                ClEnv->cHandle = loop_handle; break;}
              }
          GC_UNLOOP; POP_SIGNAL;}
        }
      Result = r_some;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: print_option_usage(r:method,m:module) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  print_option_usage_method1(method *r,module *m)
{ GC_BIND;
  { OID  g0219 = GC_OID(apply_method(r,list::alloc(1,(*(OBJECT(bag,(*(r->domain))[1])))[1])));
    OID  title = GC_OID((*Kernel.nth)(g0219,
      ((OID)1)));
    OID  syntax = GC_OID((*Kernel.nth)(g0219,
      ((OID)2)));
    OID  help = GC_OID((*Kernel.nth)(g0219,
      ((OID)3)));
    princ_string("  ");
    { OID  l = GC_OID((*Core.print_back_option_usage)(syntax));
      princ_string("\n");
      if ((CL_INT)(*Kernel.length)((*(OBJECT(bag,l)))[2]) > 0)
       { CL_INT  i = 1;
        CL_INT  g0220 = (*Kernel.length)((*(OBJECT(bag,l)))[2]);
        { CL_INT loop_handle = ClEnv->cHandle;
          OID gc_local;
          while (((CL_INT)i <= (CL_INT)g0220))
          { GC_LOOP;
            { ClaireBoolean * g0222I;
              { OID  g0223UU;
                { ClaireBoolean * V_CL0224;{ OID  g0225UU;
                    { CL_INT  j = 1;
                      CL_INT  g0221 = ((CL_INT)i-(CL_INT)1);
                      { CL_INT loop_handle = ClEnv->cHandle;
                        OID gc_local;
                        g0225UU= _oid_(CFALSE);
                        while (((CL_INT)j <= (CL_INT)g0221))
                        { GC_LOOP;
                          if (equal(GC_OID((*Kernel.nth)((*(OBJECT(bag,l)))[2],
                            ((OID)i))),GC_OID((*Kernel.nth)((*(OBJECT(bag,l)))[2],
                            ((OID)j)))) == CTRUE)
                           { g0225UU = Kernel.ctrue;
                            ClEnv->cHandle = loop_handle;break;}
                          ++j;
                          GC_UNLOOP;POP_SIGNAL;}
                        }
                      }
                    V_CL0224 = boolean_I_any(g0225UU);
                    }
                  
                  g0223UU=_oid_(V_CL0224);}
                g0222I = not_any(g0223UU);
                }
              
              if (g0222I == CTRUE) { princ_string("    ");
                  print_var_string1(string_v((*Kernel.nth)((*(OBJECT(bag,l)))[2],
                    ((OID)i))));
                  princ_string(" % ");
                  (*Kernel.princ)(GC_OID((*Kernel.nth)((*(OBJECT(bag,l)))[3],
                    ((OID)i))));
                  princ_string("\n");
                  }
                }
            ++i;
            GC_UNLOOP;POP_SIGNAL;}
          }
        }
      princ_string("\n");
      (*Core.print_back_option_help)(help,
        l);
      princ_string("\n\n");
      }
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: print_option_usage(r:method) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  print_option_usage_method2(method *r)
{ print_option_usage_method1(r,r->module_I);
  POP_SIGNAL;}


// The c++ function for: print_option_usage(opt:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  print_option_usage_string1(char *opt)
{ GC_BIND;
  { OID  rtest = GC_OID(find_option_usage_string1(opt));
    if (rtest != CNULL)
     { method * r = OBJECT(method,rtest);
      print_option_usage_method2(r);
      }
    else { CL_INT  g0226 = (int )(current_color);
        CL_INT  g0227 = (int )(current_bold);
        CL_INT  g0228 = g0226;
        CL_INT  g0229 = g0227;
        color(g0226,g0227);
        color_princ_string1("`REDInvalid option ");
        g0226= (int )(current_color);
        g0227= (int )(current_bold);
        color(g0228,g0229);
        print_any(_string_(opt));
        color(g0226,g0227);
        color(g0226,g0227);
        color_princ_string1("\n");
        color(g0228,g0229);
        }
      }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: print_option_usage(m:module) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  print_option_usage_module1(module *m)
{ { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(r);
    for (START(Core.option_usage->restrictions); NEXT(r);)
    if (OBJECT(restriction,r)->module_I == m)
     print_option_usage_method1(OBJECT(method,r),m);
    }
  POP_SIGNAL;}


// The c++ function for: print_option_usage(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  print_option_usage_void1()
{ { CL_INT loop_handle = ClEnv->cHandle;
    ITERATE(g0230);
    bag *g0230_support;
    g0230_support = Kernel._module->descendents;
    for (START(g0230_support); NEXT(g0230);)
    { ClaireBoolean * g0231;
      { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(m);
          V_C= Kernel.cfalse;
          for (START(OBJECT(ClaireClass,g0230)->instances); NEXT(m);)
          { ClaireBoolean * first_ask = CTRUE;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(r);
              for (START(Core.option_usage->restrictions); NEXT(r);)
              if (_oid_(OBJECT(restriction,r)->module_I) == m)
               { if (first_ask == CTRUE)
                 { first_ask= CFALSE;
                  print_module_module1(OBJECT(module,m));
                  }
                print_option_usage_method1(OBJECT(method,r),OBJECT(module,m));
                }
              }
            }
          }
        
        g0231=OBJECT(ClaireBoolean,V_C);}
      if (g0231 == CTRUE)
       { ;ClEnv->cHandle = loop_handle; break;}
      }
    }
  POP_SIGNAL;}


// The c++ function for: print_option_index(r:method,i:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  print_option_index_method1(method *r,int i)
{ GC_BIND;
  { OID  g0232 = GC_OID(apply_method(r,list::alloc(1,(*(OBJECT(bag,(*(r->domain))[1])))[1])));
    OID  title = GC_OID((*Kernel.nth)(g0232,
      ((OID)1)));
    OID  syntax = GC_OID((*Kernel.nth)(g0232,
      ((OID)2)));
    OID  help = GC_OID((*Kernel.nth)(g0232,
      ((OID)3)));
    color(32,0);
    print_any(((OID)i));
    color(30,0);
    princ_string(" - ");
    (*Kernel.princ)(title);
    princ_string(" : ");
    (*Core.print_back_option_usage)(syntax);
    princ_string("\n");
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: print_option_index(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  print_option_index_void1()
{ princ_string("====== Option syntax ======\n");
  { CL_INT  g0233 = (int )(current_color);
    CL_INT  g0234 = (int )(current_bold);
    CL_INT  g0235 = g0233;
    CL_INT  g0236 = g0234;
    color(g0233,g0234);
    color_princ_string1("  ``BLACK[`BLACKx``BLACK]\t`BLACK-> x is optional\n");
    color(g0235,g0236);
    }
  { CL_INT  g0237 = (int )(current_color);
    CL_INT  g0238 = (int )(current_bold);
    CL_INT  g0239 = g0237;
    CL_INT  g0240 = g0238;
    color(g0237,g0238);
    color_princ_string1("  ``BLACK{`BLACKx``BLACK}\t`BLACK-> x (identity)\n");
    color(g0239,g0240);
    }
  { CL_INT  g0241 = (int )(current_color);
    CL_INT  g0242 = (int )(current_bold);
    CL_INT  g0243 = g0241;
    CL_INT  g0244 = g0242;
    color(g0241,g0242);
    color_princ_string1("  x ``BLACK| `BLACKy\t-> x or y\n");
    color(g0243,g0244);
    }
  { CL_INT  g0245 = (int )(current_color);
    CL_INT  g0246 = (int )(current_bold);
    CL_INT  g0247 = g0245;
    CL_INT  g0248 = g0246;
    color(g0245,g0246);
    color_princ_string1("  ``BLACK+`BLACKx\t-> x can be repeated\n");
    color(g0247,g0248);
    }
  { list * l = Core.option_usage->restrictions;
    CL_INT  idx = 0;
    { CL_INT loop_handle = ClEnv->cHandle;
      ITERATE(g0249);
      bag *g0249_support;
      g0249_support = Kernel._module->descendents;
      for (START(g0249_support); NEXT(g0249);)
      { ClaireBoolean * g0250;
        { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
            ITERATE(m);
            V_C= Kernel.cfalse;
            for (START(OBJECT(ClaireClass,g0249)->instances); NEXT(m);)
            { ClaireBoolean * first_ask = CTRUE;
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(r);
                for (START(l); NEXT(r);)
                if (_oid_(OBJECT(restriction,r)->module_I) == m)
                 { ++idx;
                  if (first_ask == CTRUE)
                   { print_module_module1(OBJECT(module,m));
                    first_ask= CFALSE;
                    }
                  print_option_index_method1(OBJECT(method,r),idx);
                  }
                }
              }
            }
          
          g0250=OBJECT(ClaireBoolean,V_C);}
        if (g0250 == CTRUE)
         { ;ClEnv->cHandle = loop_handle; break;}
        }
      }
    }
  POP_SIGNAL;}


// The c++ function for: apply_option_parsed(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  apply_option_parsed_void1()
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(m);
    bag *m_support;
    m_support = GC_OBJECT(set,OBJECT(bag,Core.RESPONDER_MODULE->value));
    for (START(m_support); NEXT(m);)
    { GC_LOOP;
      { OID  rtest;
        { { OID  o_some = CNULL;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(o);
              for (START(Core.option_parsed->restrictions); NEXT(o);)
              { GC_LOOP;
                if (_oid_(OBJECT(restriction,o)->module_I) == m)
                 { o_some= o;
                  ClEnv->cHandle = loop_handle; break;}
                GC_UNLOOP; POP_SIGNAL;}
              }
            rtest = o_some;
            }
          GC_OID(rtest);}
        if (rtest != CNULL)
         { restriction * r = OBJECT(restriction,rtest);
          apply_method(((method *) r),list::alloc(1,_oid_(Kernel._void)));
          }
        else ;}
      GC_UNLOOP; POP_SIGNAL;}
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: option_respond(opt:{"-h", "-help"},l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  option_respond_string1_Core(char *opt,list *l)
{ GC_RESERVE(13);  // v3.0.55 optim !
  color_integer(1);
  if (boolean_I_any(_oid_(l)) != CTRUE)
   print_option_index_void1();
  else { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while ((l->length != 0))
      { GC_LOOP;
        { OID  opt = (*(l))[1];
          char * lopt = GC_STRING(lower_string(string_v(opt)));
          OID  mod;
          { { OID  m_some = CNULL;
              { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(g0251);
                bag *g0251_support;
                g0251_support = Kernel._module->descendents;
                for (START(g0251_support); NEXT(g0251);)
                { GC_LOOP;
                  { ClaireBoolean * g0252;
                    { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                        OID gc_local;
                        ITERATE(m);
                        V_C= Kernel.cfalse;
                        for (START(OBJECT(ClaireClass,g0251)->instances); NEXT(m);)
                        { GC_LOOP;
                          if (equal_string(lower_string(OBJECT(thing,m)->name->name),lopt) == CTRUE)
                           { V_C = m_some= m;
                            ClEnv->cHandle = loop_handle;break;}
                          GC_UNLOOP; POP_SIGNAL;}
                        }
                      
                      g0252=OBJECT(ClaireBoolean,V_C);}
                    if (g0252 == CTRUE)
                     { ;ClEnv->cHandle = loop_handle; break;}
                    }
                  GC_UNLOOP; POP_SIGNAL;}
                }
              mod = m_some;
              }
            GC_OID(mod);}
          if (INHERIT(OWNER(mod),Kernel._module))
           { princ_string("====== [");
            print_any(mod);
            princ_string("] ======\n\n");
            if (OBJECT(module,mod)->made_of->length != 0)
             print_option_usage_module1(OBJECT(module,mod));
            else { CL_INT loop_handle = ClEnv->cHandle;
                OID gc_local;
                ITERATE(m);
                bag *m_support;
                m_support = GC_OBJECT(list,OBJECT(module,mod)->parts);
                for (START(m_support); NEXT(m);)
                (*Core.print_option_usage)(m);
                }
              }
          else { OID  rtest = GC_OID((*Core.find_option_usage)(opt));
              if (rtest != CNULL)
               { method * r = OBJECT(method,rtest);
                print_option_usage_method2(r);
                }
              else { OID  rtest = find_option_usage_integer1((*Kernel.integer_I)(opt));
                  if (rtest != CNULL)
                   { method * r = OBJECT(method,rtest);
                    print_option_usage_method2(r);
                    }
                  else { CL_INT  g0253 = (int )(current_color);
                      CL_INT  g0254 = (int )(current_bold);
                      CL_INT  g0255 = g0253;
                      CL_INT  g0256 = g0254;
                      color(g0253,g0254);
                      color_princ_string1("`RED");
                      g0253= (int )(current_color);
                      g0254= (int )(current_bold);
                      color(g0255,g0256);
                      (*Kernel.princ)(opt);
                      color(g0253,g0254);
                      color(g0253,g0254);
                      color_princ_string1(" is unbound (try ");
                      g0253= (int )(current_color);
                      g0254= (int )(current_bold);
                      color(g0255,g0256);
                      (*Kernel.princ)((*(ClEnv->params))[1]);
                      color(g0253,g0254);
                      color(g0253,g0254);
                      color_princ_string1(" -h)\n");
                      color(g0255,g0256);
                      }
                    }
                }
            skip_list(l,1);
          }
        GC_UNLOOP;POP_SIGNAL;}
      }
    CL_exit(0);
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: option_respond(opt:{"-s"},l:list) [0]
void  option_respond_string2_Core(char *opt,list *l)
{ skip_list(l,2);
  POP_SIGNAL;}


// The c++ function for: option_respond(opt:{"-color", "-nocolor", "-nologo", "-auto", "-noel", "-alt"},l:list) [0]
void  option_respond_string3_Core(char *opt,list *l)
{ ;POP_SIGNAL;}


// The c++ function for: option_respond(opt:{"-qonerror"},l:list) [0]
void  option_respond_string4_Core(char *opt,list *l)
{ (Core._Zqonerror->value= Kernel.ctrue);
  POP_SIGNAL;}


// The c++ function for: option_respond(opt:{"-errassegv"},l:list) [0]
void  option_respond_string5_Core(char *opt,list *l)
{ (Core._Zerrassegv->value= Kernel.ctrue);
  POP_SIGNAL;}


// The c++ function for: option_respond(opt:{"-about"},l:list) [0]
void  option_respond_string6_Core(char *opt,list *l)
{ about_void();
  CL_exit(0);
  POP_SIGNAL;}


// The c++ function for: number?(s:string) [NEW_ALLOC]
ClaireBoolean * number_ask_string1(char *s)
{ { ClaireBoolean *Result ;
    Result = ((digit_ask_string(s) == CTRUE) ?
      CTRUE :
      (((CL_INT)LENGTH_STRING(s) < 2) ?
        CFALSE :
        ((s[1 - 1] != ((unsigned char)45 /* '-' */)) ?
          CFALSE :
          digit_ask_string(substring_string(s,2,LENGTH_STRING(s))) ) ) );
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: option_respond(opt:{"-q"},l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  option_respond_string7_Core(char *opt,list *l)
{ { OID  l1;
    if (l->length != 0)
     l1 = (*(l))[1];
    else l1 = _string_("");
      apply_option_parsed_void1();
    CL_exit((*Kernel.integer_I)(l1));
    }
  POP_SIGNAL;}


// The c++ function for: option_respond(opt:{"-v"},l:list) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  option_respond_string8_Core(char *opt,list *l)
{ if (boolean_I_any(_oid_(l)) != CTRUE)
   close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
  { OID  opt = (*(l))[1];
    OID  mod = value_string(string_v(opt));
    CL_INT  v = (*Kernel.integer_I)(opt);
    if (INHERIT(OWNER(mod),Kernel._module))
     { skip_list(l,1);
      if ((boolean_I_any(_oid_(l)) != CTRUE) || 
          (number_ask_string1(string_v((*(l))[1])) != CTRUE))
       close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
      (OBJECT(module,mod)->verbose = (*Kernel.integer_I)((*(l))[1]));
      skip_list(l,1);
      }
    else { if (number_ask_string1(string_v((*(l))[1])) != CTRUE)
         close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
        skip_list(l,1);
        (ClEnv->verbose = (*Kernel.integer_I)(opt));
        }
      }
  POP_SIGNAL;}


// The c++ function for: option_respond(opt:{"-trace"},l:list) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  option_respond_string9_Core(char *opt,list *l)
{ { char * m = "w";
    if (boolean_I_any(_oid_(l)) != CTRUE)
     close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
    if ((equal((*(l))[1],_string_("a")) == CTRUE) || 
        (equal((*(l))[1],_string_("append")) == CTRUE))
     { m= "a";
      skip_list(l,1);
      if (boolean_I_any(_oid_(l)) != CTRUE)
       close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
      }
    (ClEnv->ctrace = fopen_string1(string_v((*(l))[1]),m));
    }
  POP_SIGNAL;}


// The c++ function for: option_respond(opt:{"-sample"},l:list) [NEW_ALLOC]
void  option_respond_string41_Core(char *opt,list *l)
{ if (boolean_I_any(_oid_(l)) != CTRUE)
   close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
  skip_list(l,1);
  POP_SIGNAL;}


// The c++ function for: option_respond(opt:{"-chdir"},l:list[string]) [NEW_ALLOC]
void  option_respond_string40_Core(char *opt,list *l)
{ if (boolean_I_any(_oid_(l)) != CTRUE)
   close_exception((ClaireException *) new_object_class(Core._invalid_option_argument));
  { OID  dir = (*(l))[1];
    skip_list(l,1);
    setcwd_string(string_v(dir));
    }
  POP_SIGNAL;}


// *********************************************************************
// * Part 3: option dispatch                                           *
// *********************************************************************
// The c++ function for: print_cmline_exception(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  print_cmline_exception_void1()
{ GC_BIND;
  if (INHERIT(owner_any(value_string("Reader")),Kernel._module))
   { OID  p = value_module(OBJECT(module,value_string("Reader")),"print_exception");
    fcall1(OBJECT(method,(*(OBJECT(property,p)->restrictions))[1])->functional,Kernel._any,_oid_(ClEnv),Kernel._void);
    }
  else { avoid_signal_handling++;
      { PortObject * p = use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value));
        ClaireException * _Zerr = GC_OBJECT(ClaireException,ClEnv->exception_I);
        method * _Zprop = ((method *) _at_property1(Kernel.self_print,OWNER(_oid_(_Zerr))));
        { ClaireHandler c_handle = ClaireHandler();
          if ERROR_IN 
          { { color(31,0);
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
        use_as_output_port(p);
        avoid_signal_handling--;
        }
      }
    GC_UNBIND; POP_SIGNAL;}


//<sb> v3.3.35 this is our new entry point
// The c++ function for: parse_command_line(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  parse_command_line_void1()
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { list * argv = ((list *) copy_bag(ClEnv->params));
    ClaireBoolean * cmd_line_err_ask = CFALSE;
    { ClaireHandler c_handle = ClaireHandler();
      if ERROR_IN 
      { { skip_list(argv,1);
          { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while ((argv->length != 0))
            { GC_LOOP;
              { OID  opt = (*(argv))[1];
                skip_list(argv,1);
                { ClaireHandler c_handle = ClaireHandler();
                  if ERROR_IN 
                  { { OID  rtest;
                      { { OID  r_some = CNULL;
                          { CL_INT loop_handle = ClEnv->cHandle;
                            OID gc_local;
                            ITERATE(r);
                            for (START(Core.option_respond->restrictions); NEXT(r);)
                            { GC_LOOP;
                              { ClaireBoolean * g0277I;
                                { OID  g0278UU;
                                  { CL_INT loop_handle = ClEnv->cHandle;
                                    OID gc_local;
                                    ITERATE(w);
                                    g0278UU= Kernel.cfalse;
                                    bag *w_support;
                                    w_support = GC_OBJECT(bag,enumerate_any((*(OBJECT(restriction,r)->domain))[1]));
                                    for (START(w_support); NEXT(w);)
                                    if (match_wildcard_ask_string(string_v(opt),string_v(w)) == CTRUE)
                                     { g0278UU = Kernel.ctrue;
                                      ClEnv->cHandle = loop_handle;break;}
                                    }
                                  g0277I = boolean_I_any(g0278UU);
                                  }
                                
                                if (g0277I == CTRUE) { r_some= r;
                                    ClEnv->cHandle = loop_handle; break;}
                                  }
                              GC_UNLOOP; POP_SIGNAL;}
                            }
                          rtest = r_some;
                          }
                        GC_OID(rtest);}
                      if (rtest != CNULL)
                       { restriction * r = OBJECT(restriction,rtest);
                        apply_method(((method *) r),GC_OBJECT(list,list::alloc(2,opt,_oid_(argv))));
                        (Core.RESPONDER_MODULE->value= _oid_(GC_OBJECT(set,OBJECT(set,Core.RESPONDER_MODULE->value))->addFast((OID)_oid_(r->module_I))));
                        }
                      else { color_integer(1);
                          { CL_INT  g0257 = (int )(current_color);
                            CL_INT  g0258 = (int )(current_bold);
                            CL_INT  g0259 = g0257;
                            CL_INT  g0260 = g0258;
                            color(g0257,g0258);
                            color_princ_string1("`REDInvalid option ");
                            g0257= (int )(current_color);
                            g0258= (int )(current_bold);
                            color(g0259,g0260);
                            (*Kernel.princ)(opt);
                            color(g0257,g0258);
                            color(g0257,g0258);
                            color_princ_string1(" (try ");
                            g0257= (int )(current_color);
                            g0258= (int )(current_bold);
                            color(g0259,g0260);
                            (*Kernel.princ)((*(ClEnv->params))[1]);
                            color(g0257,g0258);
                            color(g0257,g0258);
                            color_princ_string1(" -h)\n");
                            color(g0259,g0260);
                            }
                          CL_exit(1);
                          }
                        }
                    ERROR_FREE;}
                  else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Core._invalid_option_argument)) == CTRUE)
                  { c_handle.catchIt();{ color_integer(1);
                      (*Core.print_option_usage)(opt);
                      if (argv->length != 0)
                       { CL_INT  g0261 = (int )(current_color);
                        CL_INT  g0262 = (int )(current_bold);
                        CL_INT  g0263 = g0261;
                        CL_INT  g0264 = g0262;
                        color(g0261,g0262);
                        color_princ_string1("`REDInvalid argument ");
                        g0261= (int )(current_color);
                        g0262= (int )(current_bold);
                        color(g0263,g0264);
                        (*Kernel.princ)((*(argv))[1]);
                        color(g0261,g0262);
                        color(g0261,g0262);
                        color_princ_string1(" for option ");
                        g0261= (int )(current_color);
                        g0262= (int )(current_bold);
                        color(g0263,g0264);
                        (*Kernel.princ)(opt);
                        color(g0261,g0262);
                        color(g0261,g0262);
                        color_princ_string1("\n");
                        color(g0263,g0264);
                        }
                      else { CL_INT  g0265 = (int )(current_color);
                          CL_INT  g0266 = (int )(current_bold);
                          CL_INT  g0267 = g0265;
                          CL_INT  g0268 = g0266;
                          color(g0265,g0266);
                          color_princ_string1("`REDMissing argument for option ");
                          g0265= (int )(current_color);
                          g0266= (int )(current_bold);
                          color(g0267,g0268);
                          (*Kernel.princ)(opt);
                          color(g0265,g0266);
                          color(g0265,g0266);
                          color_princ_string1("\n");
                          color(g0267,g0268);
                          }
                        CL_exit(1);
                      }
                    }
                  else PREVIOUS_HANDLER;}
                }
              GC_UNLOOP;POP_SIGNAL;}
            }
          apply_option_parsed_void1();
          }
        ERROR_FREE;}
      else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
      { c_handle.catchIt();{ cmd_line_err_ask= CTRUE;
          if ((OBJECT(ClaireBoolean,Core._Zqonerror->value)) == CTRUE)
           { color_integer(1);
            { CL_INT  g0269 = (int )(current_color);
              CL_INT  g0270 = (int )(current_bold);
              CL_INT  g0271 = g0269;
              CL_INT  g0272 = g0270;
              color(g0269,g0270);
              color_princ_string1("`RED-qonerror handled by exception:\n");
              g0269= (int )(current_color);
              g0270= (int )(current_bold);
              color(g0271,g0272);
              print_cmline_exception_void1();
              color(g0269,g0270);
              color(g0271,g0272);
              }
            CL_exit(1);
            }
          else if (contain_ask_list(ClEnv->params,_string_("-q")) == CTRUE)
           { { CL_INT  g0273 = (int )(current_color);
              CL_INT  g0274 = (int )(current_bold);
              CL_INT  g0275 = g0273;
              CL_INT  g0276 = g0274;
              color(g0273,g0274);
              color_princ_string1("`RED-q handled by exception:\n");
              g0273= (int )(current_color);
              g0274= (int )(current_bold);
              color(g0275,g0276);
              print_cmline_exception_void1();
              color(g0273,g0274);
              color(g0275,g0276);
              }
            CL_exit(1);
            }
          print_cmline_exception_void1();
          }
        }
      else PREVIOUS_HANDLER;}
    if (Core.toplevel->restrictions->length != 0)
     (*Core.toplevel)(_oid_(ClEnv));
    if (cmd_line_err_ask == CTRUE)
     CL_exit(1);
    else CL_exit(0);
      }
  GC_UNBIND; POP_SIGNAL;}



