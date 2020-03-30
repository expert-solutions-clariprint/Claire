/***** CLAIRE Compilation of file ./meta/complete.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:43 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>

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
void  completion_reset_void()
{ (Reader.COMPLETE_START_POSITION->value= ((OID)-1));
  shrink_string(string_v(Reader.LAST_LINE->value),0);
  (Reader.MATCH_INDEX->value= ((OID)0));
  (Reader.LAST_POSITION->value= ((OID)-1));
  (Reader.LAST_MODULE->value= _oid_(claire.it));
  shrink_list(OBJECT(bag,Reader.MATCHES->value),0);
  POP_SIGNAL;}


// The c++ function for: explode_separators(s:string) [NEW_ALLOC+RETURN_ARG]
void  explode_separators_string(char *s)
{ GC_BIND;
  shrink_list(OBJECT(bag,Reader.LAST_EXPLODED->value),0);
  { CL_INT  p1 = 1;
    CL_INT  len = LENGTH_STRING(s);
    list * l = GC_OBJECT(list,OBJECT(list,Reader.LAST_EXPLODED->value));
    { CL_INT  p2 = 1;
      CL_INT  g0802 = len;
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while (((CL_INT)p2 <= (CL_INT)g0802))
        { GC_LOOP;
          if ((s[p2 - 1] == ((unsigned char)32 /* ' ' */)) || 
              ((s[p2 - 1] == ((unsigned char)34 /* '"' */)) || 
                ((s[p2 - 1] == ((unsigned char)39 /* ''' */)) || 
                  ((s[p2 - 1] == ((unsigned char)40 /* '(' */)) || 
                    ((s[p2 - 1] == ((unsigned char)41 /* ')' */)) || 
                      ((s[p2 - 1] == ((unsigned char)44 /* ',' */)) || 
                        ((s[p2 - 1] == ((unsigned char)46 /* '.' */)) || 
                          ((s[p2 - 1] == ((unsigned char)47 /* '/' */)) || 
                            ((s[p2 - 1] == ((unsigned char)58 /* ':' */)) || 
                              ((s[p2 - 1] == ((unsigned char)59 /* ';' */)) || 
                                ((s[p2 - 1] == ((unsigned char)60 /* '<' */)) || 
                                  ((s[p2 - 1] == ((unsigned char)62 /* '>' */)) || 
                                    ((s[p2 - 1] == ((unsigned char)64 /* '@' */)) || 
                                      ((s[p2 - 1] == ((unsigned char)91 /* '[' */)) || 
                                        ((s[p2 - 1] == ((unsigned char)93 /* ']' */)) || 
                                          ((s[p2 - 1] == ((unsigned char)123 /* '{' */)) || 
                                            ((s[p2 - 1] == ((unsigned char)124 /* '|' */)) || 
                                              (s[p2 - 1] == ((unsigned char)125 /* '}' */)))))))))))))))))))
           { if (((CL_INT)p2 > (CL_INT)p1) && 
                ((CL_INT)p1 <= (CL_INT)len))
             l= l->addFast((OID)GC_OID(_string_(substring_string(s,p1,((CL_INT)p2-(CL_INT)1)))));
            l= l->addFast((OID)_oid_(_char_(s[p2 - 1])));
            p1= ((CL_INT)p2+(CL_INT)1);
            }
          ++p2;
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    if ((CL_INT)p1 <= (CL_INT)len)
     l= l->addFast((OID)GC_OID(_string_(substring_string(s,p1,len))));
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: same_tree?(a:module) [NEW_ALLOC]
ClaireBoolean * same_tree_ask_module(module *a)
{ { ClaireBoolean *Result ;
    Result = ((_oid_(a) == Reader.LAST_MODULE->value) ?
      CTRUE :
      ((a == claire.it) ?
        CFALSE :
        same_tree_ask_module(a->part_of) ) );
    POP_SIGNAL; return (Result);}
  }


// The c++ function for: complete_named_object(o:string,l:list[string]) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  complete_named_object_string(char *o,list *l)
{ GC_BIND;
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
           l= l->addFast((OID)_string_(OBJECT(symbol,(*Kernel.name)(s))->name));
          else if (same_tree_ask_module(OBJECT(symbol,(*Kernel.name)(s))->module_I) == CTRUE)
           l= l->addFast((OID)GC_OID(_string_(append_string(GC_STRING(append_string(OBJECT(symbol,(*Kernel.name)(s))->module_I->name->name,"/")),OBJECT(symbol,(*Kernel.name)(s))->name))));
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: complete_slot(o:string,l:list[string]) [NEW_ALLOC+RETURN_ARG]
void  complete_slot_string(char *o,list *l)
{ GC_BIND;
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
           l= l->addFast((OID)_string_(OBJECT(restriction,s)->selector->name->name));
          else if (same_tree_ask_module(OBJECT(restriction,s)->selector->name->module_I) == CTRUE)
           l= l->addFast((OID)GC_OID(_string_(append_string(GC_STRING(append_string(OBJECT(restriction,s)->selector->name->module_I->name->name,"/")),OBJECT(restriction,s)->selector->name->name))));
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: complete_class(o:string,l:list[string]) [NEW_ALLOC+RETURN_ARG]
void  complete_class_string(char *o,list *l)
{ GC_BIND;
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
           l= l->addFast((OID)_string_(OBJECT(ClaireClass,s)->name->name));
          else if (same_tree_ask_module(OBJECT(ClaireClass,s)->name->module_I) == CTRUE)
           l= l->addFast((OID)GC_OID(_string_(append_string(GC_STRING(append_string(OBJECT(ClaireClass,s)->name->module_I->name->name,"/")),OBJECT(ClaireClass,s)->name->name))));
          }
        GC_UNLOOP; POP_SIGNAL;}
      }
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: nodup(l:list[string]) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  nodup_list(list *l)
{ GC_BIND;
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
void  fill_claire_matches_string(char *buf,int end)
{ GC_BIND;
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
      if ((3 <= (CL_INT)len) && 
        (((*(l))[((CL_INT)len-(CL_INT)1)] == _oid_(_char_(((unsigned char)47 /* '/' */)))) && 
          ((Kernel._string == OWNER((*(l))[((CL_INT)len-(CL_INT)2)])) && 
            (Kernel._string == OWNER((*(l))[len])))))
     { OID  x = value_string(string_v((*(l))[((CL_INT)len-(CL_INT)2)]));
      if (x != CNULL)
       { if (INHERIT(OWNER(x),Kernel._module))
         { (Reader.LAST_MODULE->value= x);
          delete_at_list(l,((CL_INT)len-(CL_INT)2));
          delete_at_list(l,((CL_INT)len-(CL_INT)2));
          len= l->length;
          }
        }
      else ;}
    else if ((4 <= (CL_INT)len) && 
        (((*(l))[len] == _oid_(_char_(((unsigned char)40 /* '(' */)))) && 
          ((Kernel._string == OWNER((*(l))[((CL_INT)len-(CL_INT)1)])) && 
            (((*(l))[((CL_INT)len-(CL_INT)2)] == _oid_(_char_(((unsigned char)47 /* '/' */)))) && 
              (Kernel._string == OWNER((*(l))[((CL_INT)len-(CL_INT)3)]))))))
     { OID  x = value_string(string_v((*(l))[((CL_INT)len-(CL_INT)3)]));
      if (x != CNULL)
       { if (INHERIT(OWNER(x),Kernel._module))
         (Reader.LAST_MODULE->value= x);
        }
      else ;}
    if (((CL_INT)len > 0) && 
        (Kernel._string == OWNER((*(l))[len])))
     { if ((((CL_INT)len > 2) && 
            (((*(l))[((CL_INT)len-(CL_INT)2)] == _oid_(_char_(((unsigned char)60 /* '<' */)))) && 
              ((*(l))[((CL_INT)len-(CL_INT)1)] == _oid_(_char_(((unsigned char)40 /* '(' */)))))) || 
          ((((CL_INT)len > 1) && 
              (((*(l))[((CL_INT)len-(CL_INT)1)] == _oid_(_char_(((unsigned char)60 /* '<' */)))) || 
                  ((*(l))[((CL_INT)len-(CL_INT)1)] == _oid_(_char_(((unsigned char)91 /* '[' */)))))) || 
            ((((CL_INT)len > 2) && 
                ((Kernel._string == OWNER((*(l))[((CL_INT)len-(CL_INT)2)])) && 
                  ((*(l))[((CL_INT)len-(CL_INT)1)] == _oid_(_char_(((unsigned char)58 /* ':' */)))))) || 
              ((((CL_INT)len > 2) && 
                  (((*(l))[((CL_INT)len-(CL_INT)1)] == _oid_(_char_(((unsigned char)32 /* ' ' */)))) && 
                    (equal((*(l))[((CL_INT)len-(CL_INT)2)],_string_("U")) == CTRUE))) || 
                (((CL_INT)len > 3) && 
                    (((*(l))[((CL_INT)len-(CL_INT)1)] == _oid_(_char_(((unsigned char)32 /* ' ' */)))) && 
                      (((*(l))[((CL_INT)len-(CL_INT)2)] == _oid_(_char_(((unsigned char)58 /* ':' */)))) && 
                        ((*(l))[((CL_INT)len-(CL_INT)3)] == _oid_(_char_(((unsigned char)32 /* ' ' */)))))))))))
       complete_class_string(string_v((*(l))[len]),res);
      else if (((CL_INT)len > 1) && 
          ((*(l))[((CL_INT)len-(CL_INT)1)] == _oid_(_char_(((unsigned char)46 /* '.' */)))))
       complete_slot_string(string_v((*(l))[len]),res);
      else complete_named_object_string(string_v((*(l))[len]),res);
        }
    nodup_list(res);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: match_prefix(_CL_obj:void) [NEW_ALLOC]
char * match_prefix_void()
{ GC_BIND;
  { char *Result ;
    { list * ll;
      { { CL_INT loop_handle = ClEnv->cHandle;
          bag *v_list; OID v_val;
          OID i; CL_INT CLcount;
          v_list = GC_OBJECT(list,OBJECT(bag,Reader.MATCHES->value));
           ll = v_list->clone(Kernel._string);
          for (CLcount= 1; CLcount <= v_list->length; CLcount++)
          { i = (*(v_list))[CLcount];
            v_val = last_list(explode_string(string_v(i),"/"));
            
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
            lres= li;
            }
          { CL_INT  j = 1;
            CL_INT  g0803 = lres;
            { CL_INT loop_handle = ClEnv->cHandle;
              while (((CL_INT)j <= (CL_INT)g0803))
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
char * method_description_method(method *m)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { char *Result ;
    { char * res = m->selector->name->name;
      ClaireBoolean * first_ask = CTRUE;
      res= GC_STRING(append_string(res,"("));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        ITERATE(a);
        for (START(m->domain); NEXT(a);)
        { GC_LOOP;
          { if (first_ask == CTRUE)
             first_ask= CFALSE;
            else GC__STRING(res = append_string(res,", "), 1);
              { { char * g0804UU;
                { { print_in_string_void();
                    print_any(a);
                    g0804UU = end_of_string_void();
                    }
                  GC_STRING(g0804UU);}
                res = append_string(res,g0804UU);
                }
               GC__STRING(res, 1);}
            }
          GC_UNLOOP; POP_SIGNAL;}
        }
      res= GC_STRING(append_string(res,") `BLUE-> `BLACK"));
      { { char * g0805UU;
          { { print_in_string_void();
              print_any(_oid_(m->range));
              g0805UU = end_of_string_void();
              }
            GC_STRING(g0805UU);}
          res = append_string(res,g0805UU);
          }
        GC_STRING(res);}
      Result = res;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: class_description(self:class) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
char * class_description_class(ClaireClass *self)
{ GC_BIND;
  print_in_string_void();
  print_any(_oid_(self));
  princ_string(" <: ");
  print_any(_oid_(self->superclass));
  princ_string("\n");
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(s);
    for (START(self->slots); NEXT(s);)
    { GC_LOOP;
      if (s != _oid_(_at_property1(Kernel.isa,Kernel._object)))
       { if (s != _oid_(_at_property1(Kernel.name,Kernel._thing)))
         { print_any(_oid_(OBJECT(restriction,s)->selector));
          princ_string(":");
          print_any(_oid_(OBJECT(restriction,s)->range));
          princ_string(" = ");
          print_any(GC_OID(OBJECT(slot,s)->DEFAULT));
          princ_string("\n");
          }
        }
      GC_UNLOOP; POP_SIGNAL;}
    }
  { char *Result ;
    Result = end_of_string_void();
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: claire_complete(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  claire_complete_void()
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { PortObject * oldtrace = GC_OBJECT(PortObject,ClEnv->ctrace);
    (ClEnv->ctrace = null_I_void1());
    { CL_INT  pos = self_print();
      char * line = GC_STRING(interpreter_get_text());
      if ((OBJECT(bag,Reader.MATCHES->value)->length != 0) && 
          ((((OID)pos) == Reader.LAST_POSITION->value) && 
            ((equal(_string_(line),Reader.LAST_LINE->value) == CTRUE) && 
              (Reader.COMPLETE_START_POSITION->value != ((OID)-1)))))
       { interpreter_delete_text(Reader.COMPLETE_START_POSITION->value,pos);
        (Reader.MATCH_INDEX->value= ((OID)((CL_INT)(Reader.MATCH_INDEX->value)+(CL_INT)1)));
        if (Reader.MATCH_INDEX->value == ((OID)OBJECT(bag,Reader.MATCHES->value)->length))
         ding_void();
        if ((CL_INT)Reader.MATCH_INDEX->value > (CL_INT)OBJECT(bag,Reader.MATCHES->value)->length)
         (Reader.MATCH_INDEX->value= ((OID)1));
        interpreter_insert_text(string_v((*(OBJECT(bag,Reader.MATCHES->value)))[Reader.MATCH_INDEX->value]));
        (Reader.LAST_POSITION->value= ((OID)self_print()));
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
                if ((CL_INT)LENGTH_STRING(mp) > (CL_INT)((CL_INT)pos-(CL_INT)(Reader.COMPLETE_START_POSITION->value)))
                 { shrink_list(OBJECT(bag,Reader.MATCHES->value),0);
                  (Reader.MATCHES->value= _oid_(GC_OBJECT(list,OBJECT(list,Reader.MATCHES->value))->addFast((OID)_string_(mp))));
                  claire_complete_void();
                  (Reader.COMPLETE_START_POSITION->value= ((OID)-1));
                  }
                else { ding_void();
                    interpreter_display_list(OBJECT(list,Reader.MATCHES->value));
                    (Reader.MATCHES->value= _oid_(GC_OBJECT(list,OBJECT(list,Reader.MATCHES->value))->addFast((OID)GC_OID(_string_(substring_string(line,Reader.COMPLETE_START_POSITION->value,((CL_INT)pos-(CL_INT)1)))))));
                    }
                  }
              }
          else { list * l = GC_OBJECT(list,OBJECT(list,Reader.LAST_EXPLODED->value));
              CL_INT  len = l->length;
              if (((CL_INT)len > 1) && 
                  (((*(l))[len] == _oid_(_char_(((unsigned char)46 /* '.' */)))) && 
                    (Kernel._string == OWNER((*(l))[((CL_INT)len-(CL_INT)1)]))))
               { OID  p = value_module(OBJECT(module,Reader.LAST_MODULE->value),string_v((*(l))[((CL_INT)len-(CL_INT)1)]));
                if (p != CNULL)
                 { if (INHERIT(OWNER(p),Kernel._class))
                   interpreter_display_list(list::alloc(Kernel._string,1,GC_OID(_string_(class_description_class(OBJECT(ClaireClass,p))))));
                  else interpreter_display_list(list::alloc(Kernel._string,1,GC_OID(_string_(class_description_class(OWNER(p))))));
                    ding_void();
                  }
                else ;}
              else if (((CL_INT)len > 1) && 
                  (((*(l))[len] == _oid_(_char_(((unsigned char)40 /* '(' */)))) && 
                    (Kernel._string == OWNER((*(l))[((CL_INT)len-(CL_INT)1)]))))
               { OID  p = value_module(OBJECT(module,Reader.LAST_MODULE->value),string_v((*(l))[((CL_INT)len-(CL_INT)1)]));
                if (p != CNULL)
                 { if (INHERIT(OWNER(p),Kernel._property))
                   { list * lm = OBJECT(property,p)->restrictions;
                    if (lm->length != 0)
                     { princ_string("\n");
                      { CL_INT loop_handle = ClEnv->cHandle;
                        OID gc_local;
                        ITERATE(g0806);
                        for (START(lm); NEXT(g0806);)
                        { GC_LOOP;
                          { char * i = GC_STRING(method_description_method(OBJECT(method,g0806)));
                            princ_string("  ");
                            color_princ_string1(i);
                            princ_string("\n");
                            }
                          GC_UNLOOP; POP_SIGNAL;}
                        }
                      ding_void();
                      }
                    }
                  }
                else interpreter_insert_text("\t");
                  }
              else interpreter_insert_text("\t");
                }
            }
        }
    (ClEnv->ctrace = oldtrace);
    }
  GC_UNBIND; POP_SIGNAL;}


// *********************************************************************
// * 2. shell completion                                               *
// *********************************************************************
// The c++ function for: bin_init(_CL_obj:void) [NEW_ALLOC+RETURN_ARG]
void  bin_init_void()
{ GC_BIND;
  if (Reader.BINS_INIT_ask->value != Kernel.ctrue)
   { (Reader.BINS_INIT_ask->value= Kernel.ctrue);
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(p);
      bag *p_support;
      p_support = GC_OBJECT(list,explode_string(getenv_string("PATH"),GC_STRING(string_v(Core._starps_star->value))));
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
void  fill_binaries_string(char *buf)
{ GC_BIND;
  { CL_INT  p = rfind_string2(buf,string_v(Core._starfs_star->value));
    CL_INT  p0 = ((CL_INT)rfind_string2(buf," ")+(CL_INT)1);
    (Reader.COMPLETE_START_POSITION->value= ((OID)-1));
    if (((CL_INT)p0 > 1) && 
        ((CL_INT)p0 > (CL_INT)p))
     (Reader.COMPLETE_START_POSITION->value= ((OID)p0));
    else if ((p == 0) && 
        (p0 == 1))
     (Reader.COMPLETE_START_POSITION->value= ((OID)1));
    if ((CL_INT)Reader.COMPLETE_START_POSITION->value > 0)
     buf= GC_STRING(substring_string(buf,Reader.COMPLETE_START_POSITION->value,LENGTH_STRING(buf)));
    bin_init_void();
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      ITERATE(f);
      bag *f_support;
      f_support = GC_OBJECT(list,OBJECT(bag,Reader.BINS->value));
      for (START(f_support); NEXT(f);)
      { GC_LOOP;
        if (find_string2(string_v(f),buf) == 1)
         (Reader.MATCHES->value= _oid_(GC_OBJECT(list,OBJECT(list,Reader.MATCHES->value))->addFast((OID)GC_OID(_string_(append_string(GC_STRING(replace_string(string_v(f)," ","\\ "))," "))))));
        GC_UNLOOP; POP_SIGNAL;}
      }
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: fill_files(buf:string) [NEW_ALLOC+RETURN_ARG]
void  fill_files_string(char *buf)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  { CL_INT  p = rfind_string2(buf,string_v(Core._starfs_star->value));
    CL_INT  p0 = ((CL_INT)rfind_string2(buf," ")+(CL_INT)1);
    char * tmp = GC_STRING(((((CL_INT)p0 > 1) && 
        ((CL_INT)p < (CL_INT)p0)) ?
      substring_string(buf,p0,LENGTH_STRING(buf)) :
      ((((CL_INT)p0 > 1) && 
          ((CL_INT)p0 <= (CL_INT)p)) ?
        substring_string(buf,p0,p) :
        "" ) ));
    char * df = GC_STRING(((((CL_INT)p > 0) && 
        (((CL_INT)p0 <= (CL_INT)p) && 
          ((CL_INT)((CL_INT)p+(CL_INT)1) <= (CL_INT)LENGTH_STRING(buf)))) ?
      substring_string(buf,((CL_INT)p+(CL_INT)1),LENGTH_STRING(buf)) :
      "" ));
    if ((CL_INT)p > 0)
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
                 GC__STRING(match = append_string(match,"/"), 1);
                (Reader.MATCHES->value= _oid_(GC_OBJECT(list,OBJECT(list,Reader.MATCHES->value))->addFast((OID)_string_(match))));
                }
              GC_UNLOOP; POP_SIGNAL;}
            }
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
        { c_handle.catchIt();}
        else PREVIOUS_HANDLER;}
      }
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: shell_complete(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
void  shell_complete_void()
{ GC_BIND;
  { PortObject * oldtrace = GC_OBJECT(PortObject,ClEnv->ctrace);
    (ClEnv->ctrace = null_I_void1());
    { CL_INT  pos = self_print();
      char * line = GC_STRING(interpreter_get_text());
      if ((OBJECT(bag,Reader.MATCHES->value)->length != 0) && 
          ((((OID)pos) == Reader.LAST_POSITION->value) && 
            ((equal(_string_(line),Reader.LAST_LINE->value) == CTRUE) && 
              (Reader.COMPLETE_START_POSITION->value != ((OID)-1)))))
       { interpreter_delete_text(Reader.COMPLETE_START_POSITION->value,pos);
        (Reader.MATCH_INDEX->value= ((OID)((CL_INT)(Reader.MATCH_INDEX->value)+(CL_INT)1)));
        if (Reader.MATCH_INDEX->value == ((OID)OBJECT(bag,Reader.MATCHES->value)->length))
         ding_void();
        if ((CL_INT)Reader.MATCH_INDEX->value > (CL_INT)OBJECT(bag,Reader.MATCHES->value)->length)
         (Reader.MATCH_INDEX->value= ((OID)1));
        interpreter_insert_text(string_v((*(OBJECT(bag,Reader.MATCHES->value)))[Reader.MATCH_INDEX->value]));
        (Reader.LAST_POSITION->value= ((OID)self_print()));
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
                if ((CL_INT)LENGTH_STRING(mp) > (CL_INT)((CL_INT)pos-(CL_INT)(Reader.COMPLETE_START_POSITION->value)))
                 { shrink_list(OBJECT(bag,Reader.MATCHES->value),0);
                  (Reader.MATCHES->value= _oid_(GC_OBJECT(list,OBJECT(list,Reader.MATCHES->value))->addFast((OID)_string_(mp))));
                  shell_complete_void();
                  (Reader.COMPLETE_START_POSITION->value= ((OID)-1));
                  }
                else { ding_void();
                    interpreter_display_list(OBJECT(list,Reader.MATCHES->value));
                    (Reader.MATCHES->value= _oid_(GC_OBJECT(list,OBJECT(list,Reader.MATCHES->value))->addFast((OID)GC_OID(_string_(substring_string(line,Reader.COMPLETE_START_POSITION->value,((CL_INT)pos-(CL_INT)1)))))));
                    }
                  }
              }
          }
        }
    (ClEnv->ctrace = oldtrace);
    }
  GC_UNBIND; POP_SIGNAL;}



