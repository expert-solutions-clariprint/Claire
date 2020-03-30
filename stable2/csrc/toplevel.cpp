/***** CLAIRE Compilation of file ./meta/toplevel.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:43 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>

// *********************************************************************
// * CLAIRE                                            Sylvain Benilan *
// * toplevel.cl                                                       *
// * Copyright (C) 2005 xl. All Rights Reserved                        *
// *********************************************************************
//<sb> this file contains the console interface code including
// command loops for the interpreter, the inspector and the debugger
// and the managment of execution contexts.
// Most of the code used to be in clConcole.cpp (<ycs>) and as been
// upgraded in claire in the xl version.
// ******************************************************************
// *    Part 3: standart console input                              *
// ******************************************************************
//<sb> stdin_line_reader is a basic terminal interface for the
// Reader, it aim to work on various subsytems.
// The clConsole.cpp file may define a custom line reader port
// based on editline BSD library that add history and completion
// features.
// The c++ function for: close_port(self:stdin_line_reader) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  close_port_stdin_line_reader1_Reader(Reader_stdin_line_reader *self)
{ GC_BIND;
  fclose_device1(GC_OBJECT(blob,self->line));
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: eof_port?(self:stdin_line_reader) [0]
ClaireBoolean * eof_port_ask_stdin_line_reader1_Reader(Reader_stdin_line_reader *self)
{ POP_SIGNAL; return (CFALSE);}


//<sb> note: do not use set_length@blob to reset the line
// since it could be invoked while the line has been freed
// (e.g. at exit)
// The c++ function for: flush_port(self:stdin_line_reader) [NEW_ALLOC+SLOT_UPDATE+RETURN_ARG]
void  flush_port_stdin_line_reader1_Reader(Reader_stdin_line_reader *self)
{ (self->line->read_index = 0);
  (self->line->write_index = 0);
  POP_SIGNAL;}


// The c++ function for: unget_port(self:stdin_line_reader,buf:char*,len:integer) [NEW_ALLOC]
void  unget_port_stdin_line_reader1_Reader(Reader_stdin_line_reader *self,char*buf,int len)
{ GC_BIND;
  _void_(Core.unget_port->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->line)))),((CL_INT) buf),((CL_INT) len)));
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: read_port(self:stdin_line_reader,buf:char*,len:integer) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
int  read_port_stdin_line_reader1_Reader(Reader_stdin_line_reader *self,char*buf,int len)
{ GC_BIND;
  if ((OBJECT(ClaireBoolean,_oid_((ClaireObject *) Core.eof_port_ask->fcall(((CL_INT) OBJECT(ClaireObject,GC_OID(_oid_(self->line)))))))) == CTRUE)
   { set_length_blob1(self->line,0);
    fwrite_string2(GC_STRING(freadline_port(OBJECT(PortObject,Core.Clib_stdin->value))),GC_OBJECT(blob,self->line));
    fwrite_string2("\n\n",GC_OBJECT(blob,self->line));
    }
  nth_equal_char_star1(buf,1,getc_port1(GC_OBJECT(blob,self->line)));
  { CL_INT Result = 0;
    Result = ((len == 1) ?
      1 :
      ((CL_INT)1+(CL_INT)(Core.read_port->fcall(((CL_INT) self),((CL_INT) (buf + 1)),((CL_INT) ((CL_INT)len-(CL_INT)1))))) );
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> change stdin representation
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
Reader_execution_context * save_context_boolean1(ClaireBoolean *debug_ask)
{ GC_BIND;
  { Reader_execution_context *Result ;
    { Reader_execution_context * exe;
      { { Reader_execution_context * _CL_obj = ((Reader_execution_context *) GC_OBJECT(Reader_execution_context,new_object_class(Reader._execution_context)));
          (_CL_obj->debug_context_ask = debug_ask);
          exe = _CL_obj;
          }
        GC_OBJECT(Reader_execution_context,exe);}
      (exe->saved_system = ((ClaireEnvironment *) (ClaireEnvironment *)(ClAlloc->makeAny(debug_ask == CTRUE ? 38 : 27))));
      memcpy(exe->saved_system, ClEnv, debug_ask == CTRUE ? 4*38 : 4*27);
      (exe->saved_reader = ((meta_reader *) copy_object(Reader.reader)));
      if (debug_ask == CTRUE)
       (exe->module_stack = ((list *) copy_bag(((bag *) (list *)(ClEnv->moduleStack)))));
      (exe->store__starindex_star = Reader._starindex_star->value);
      (exe->store__starcurd_star = Reader._starcurd_star->value);
      (exe->store__starmaxd_star = Reader._starmaxd_star->value);
      (ClEnv->base= GC_OID(((OID)ClEnv->index)));
      Result = exe;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: restore_context(self:execution_context) [0]
void  restore_context_execution_context1(Reader_execution_context *self)
{ memcpy(ClEnv, self->saved_system, self->debug_context_ask == CTRUE ? 4*38 : 4*27);
  if (self->debug_context_ask == CTRUE)
   ClEnv->moduleStack = self->module_stack;
  (Reader._starindex_star->value= ((OID)self->store__starindex_star));
  (Reader._starcurd_star->value= ((OID)self->store__starcurd_star));
  (Reader._starmaxd_star->value= ((OID)self->store__starmaxd_star));
  { meta_reader * r = Reader.reader;
    memcpy(r, self->saved_reader, sizeof(meta_reader));
    }
  POP_SIGNAL;}


// ******************************************************************
// *    Part 3: tool                                                *
// ******************************************************************
// The c++ function for: get_prompt(_CL_obj:void) [0]
char * get_prompt_void2()
{ POP_SIGNAL; return (string_v(Reader.PROMPT->value));}


// ******************************************************************
// *    Part 3: inspector loop                                      *
// ******************************************************************
// The c++ function for: inspect_system(self:list[any]) [RETURN_ARG]
void  inspect_system_list2(list *self)
{ (Reader.INSPECT_STACK->value= _oid_(self));
  POP_SIGNAL;}


// The c++ function for: inspect_toplevel(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  inspect_toplevel_any1(OID self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
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
          { { OID  x = GC_OID(read_command_string1("inspect> "));
              (Reader.IN_INSPECT_LOOP_ask->value= Kernel.cfalse);
              if (x == _oid_(Reader.q))
               { ;ClEnv->cHandle = loop_handle; break;}
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
OID  read_command_string1(char *prompt)
{ GC_BIND;
  (Reader.PROMPT->value= _string_(prompt));
  use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value));
  flush_port1(GC_OBJECT(PortObject,OBJECT(PortObject,Core.cl_stdout->value)));
  (Reader.reader->fromp = OBJECT(PortObject,Core.cl_stdin->value));
  if (INHERIT(get_device_port1(OBJECT(PortObject,Core.cl_stdin->value))->isa,Reader._stdin_line_reader))
   { princ_string(prompt);
    flush_port1(GC_OBJECT(PortObject,OBJECT(PortObject,Core.cl_stdout->value)));
    }
  reset_buffer_port1(Reader.reader->fromp);
  (Reader.reader->toplevel = CTRUE);
  flush_port1(GC_OBJECT(device,get_device_port1(Reader.reader->fromp)));
  (Reader.reader->index = 0);
  (Reader.reader->maxstack = 0);
  (Reader.reader->fromp->firstc = 32);
  signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_DFL);
  (Reader.ALTERNATE_COMMAND_ask->value= Kernel.ctrue);
  { OID Result = 0;
    { CL_INT  c = color_void();
      if (c != 0)
       c= color_integer(1);
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
void  eval_command_any2(OID x,int nb_eval,ClaireBoolean *check_break_ask)
{ GC_BIND;
  { CL_INT  g0807 = (int )(current_color);
    CL_INT  g0808 = (int )(current_bold);
    CL_INT  g0809 = g0807;
    CL_INT  g0810 = g0808;
    color(g0807,g0808);
    color_princ_string1("`BLUEeval[");
    g0807= (int )(current_color);
    g0808= (int )(current_bold);
    color(g0809,g0810);
    print_any(((OID)nb_eval));
    color(g0807,g0808);
    color(g0807,g0808);
    color_princ_string1("]> `BLACK");
    color(g0809,g0810);
    }
  flush_port1(GC_OBJECT(PortObject,ClEnv->cout));
  signal_signal_handler(Core.CL_SIGINT,(((OBJECT(ClaireBoolean,Reader.DEBUG_ask->value)) == CTRUE) ?
    Reader.breakpoint_I :
    Core.CL_SIG_DFL ));
  (ClEnv->index= ((OID)((CL_INT)ClEnv->index+(CL_INT)((CL_INT)Reader.reader->maxstack+(CL_INT)1))));
  (Reader.ALTERNATE_COMMAND_ask->value= Kernel.cfalse);
  print_any(GC_OID(OPT_EVAL(x)));
  signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_IGN);
  princ_string("\n");
  flush_port1(GC_OBJECT(PortObject,ClEnv->cout));
  GC_UNBIND; POP_SIGNAL;}


//<sb> here is a special version that raise
// an exception that is catched by the
// toplevel handler, it is used in the special
// case of an unrecoverable error (abort debug
// or memory exception)
// The c++ function for: close_toplevel_exception(self:exception) [0]
void  close_toplevel_exception_exception1(ClaireException *self)
{ { CL_INT  n = Reader.TOP_CHANDLE->value;
    ClEnv->exception_I = self;
			  avoid_signal_caching = 0;
			  longjmp(ClEnv->handlers[n],3);;
    }
  POP_SIGNAL;}


// The c++ function for: Core/toplevel(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  toplevel_void2_Reader()
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_IGN);
  if (INHERIT(OBJECT(ClaireObject,Core.cl_stdin->value)->isa,Core._buffer))
   (Reader.reader->fromp = OBJECT(PortObject,Core.cl_stdin->value));
  else (Reader.reader->fromp = buffer_I_port1(GC_OBJECT(PortObject,OBJECT(PortObject,Core.cl_stdin->value)),1));
    (Reader.NB_EVAL->value= ((OID)0));
  (Reader.TOP_CHANDLE->value= ((OID)(int )((ClEnv->cHandle+1))));
  { Reader_execution_context * exe_ctx = GC_OBJECT(Reader_execution_context,save_context_boolean1(CFALSE));
    { CL_INT loop_handle = ClEnv->cHandle;
      OID gc_local;
      while ((CTRUE == CTRUE))
      { GC_LOOP;
        restore_context_execution_context1(exe_ctx);
        { ClaireHandler c_handle = ClaireHandler();
          if ERROR_IN 
          { { OID  x;
              { { char * g0815UU;
                  { { print_in_string_void();
                      princ_string("[");
                      print_any(((OID)getpid_void()));
                      princ_string("]");
                      print_any(_oid_(ClEnv->module_I));
                      princ_string("> ");
                      g0815UU = end_of_string_void();
                      }
                    GC_STRING(g0815UU);}
                  x = read_command_string1(g0815UU);
                  }
                GC_OID(x);}
              if (x == _oid_(Reader.q))
               { ;ClEnv->cHandle = loop_handle; break;}
              (Reader.NB_EVAL->value= ((OID)((CL_INT)(Reader.NB_EVAL->value)+(CL_INT)1)));
              if ((OBJECT(ClaireBoolean,Reader.DEBUG_ask->value)) == CTRUE)
               { (Core.BREAK_SYSTEM_ask->value= Kernel.ctrue);
                (ClEnv->debug_I = 0);
                (ClEnv->trace_I = 1);
                }
              else { (Core.BREAK_SYSTEM_ask->value= Kernel.cfalse);
                  (ClEnv->debug_I = -1);
                  (ClEnv->trace_I = 0);
                  }
                eval_command_any2(x,Reader.NB_EVAL->value,CTRUE);
              (exe_ctx->saved_system->module_I = ClEnv->module_I);
              }
            ERROR_FREE;}
          else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
          { c_handle.catchIt();{ signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_IGN);
              if (INHERIT(ClEnv->exception_I->isa,Reader._abort_debug))
               { print_any(GC_OID(_oid_(ClEnv->exception_I)));
                princ_string("\n");
                }
              else if ((owner_any(_oid_(ClEnv->exception_I)) == Kernel._system_error) && 
                  ((CL_INT)CLREAD(system_error,ClEnv->exception_I,index) <= 3))
               print_exception_void();
              else if ((OBJECT(ClaireBoolean,Reader.DEBUG_ask->value)) == CTRUE)
               { { ClaireHandler c_handle = ClaireHandler();
                  if ERROR_IN 
                  { debug_loop_void1();
                    ERROR_FREE;}
                  else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                  { c_handle.catchIt();{ CL_INT  g0811 = (int )(current_color);
                      CL_INT  g0812 = (int )(current_bold);
                      CL_INT  g0813 = g0811;
                      CL_INT  g0814 = g0812;
                      color(g0811,g0812);
                      color_princ_string1("`REDThere is a bug in the debug loop :\n");
                      g0811= (int )(current_color);
                      g0812= (int )(current_bold);
                      color(g0813,g0814);
                      print_exception_void();
                      color(g0811,g0812);
                      color(g0813,g0814);
                      }
                    }
                  else PREVIOUS_HANDLER;}
                (ClEnv->exception_I = ((ClaireException *) new_object_class(Reader._abort_debug)));
                print_any(GC_OID(_oid_(ClEnv->exception_I)));
                princ_string("\n");
                }
              else print_exception_void();
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
// The c++ function for: read_alternate_command(r:meta_reader,s:string) [NEW_ALLOC+RETURN_ARG]
OID  read_alternate_command_meta_reader1_Reader(meta_reader *r,char *s)
{ GC_BIND;
  { OID Result = 0;
    if (((OBJECT(ClaireBoolean,Reader.IN_DEBUG_LOOP_ask->value)) == CTRUE) || 
        (((OBJECT(ClaireBoolean,Reader.IN_BREAK_SYSTEM_ask->value)) == CTRUE) || 
          ((OBJECT(ClaireBoolean,Reader.IN_INSPECT_LOOP_ask->value)) == CTRUE)))
     { OID  x = GC_OID(Reader._starframe_star->value);
      if (INHERIT(OWNER(x),Reader._debug_frame))
       { OID  vs = GC_OID(get_vars_debug_frame1(OBJECT(Reader_debug_frame,x)));
        OID  v;
        { { OID  v_some = CNULL;
            { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(v);
              bag *v_support;
              v_support = GC_OBJECT(bag,enumerate_any(vs));
              for (START(v_support); NEXT(v);)
              { GC_LOOP;
                if ((equal(v,Core.nil->value) != CTRUE) && 
                    (equal((*Kernel.nth)(v,
                      ((OID)1)),_string_(s)) == CTRUE))
                 { v_some= v;
                  ClEnv->cHandle = loop_handle; break;}
                GC_UNLOOP; POP_SIGNAL;}
              }
            v = v_some;
            }
          GC_OID(v);}
        if (v != CNULL)
         Result = (*Kernel.nth)(v,
          ((OID)2));
        else Result = Kernel.cfalse;
          }
      else Result = Kernel.cfalse;
        }
    else Result = Kernel.cfalse;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: read_alternate_command(r:meta_reader,br:{"fr"}) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  read_alternate_command_meta_reader3_Reader(meta_reader *r,char *br)
{ GC_BIND;
  { OID Result = 0;
    if (((OBJECT(ClaireBoolean,Reader.IN_DEBUG_LOOP_ask->value)) == CTRUE) || 
        ((OBJECT(ClaireBoolean,Reader.IN_BREAK_SYSTEM_ask->value)) == CTRUE))
     { if (firstc_meta_reader(r) == 10)
       Result = _oid_(new_object_class(Reader._debug_frame_info));
      else { OID  e = GC_OID(nexte_meta_reader(r));
          if (INHERIT(OWNER(e),Kernel._integer))
           Result = _oid_(((Reader_debug_select_frame *) (*Reader._debug_select_frame)(((OID)e))));
          else Result = Kernel.cfalse;
            }
        }
    else Result = Kernel.cfalse;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: read_alternate_command(r:meta_reader,br:{"where", "wh", "w"}) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  read_alternate_command_meta_reader4_Reader(meta_reader *r,char *br)
{ GC_BIND;
  { OID Result = 0;
    if (((OBJECT(ClaireBoolean,Reader.IN_DEBUG_LOOP_ask->value)) == CTRUE) || 
        ((OBJECT(ClaireBoolean,Reader.IN_BREAK_SYSTEM_ask->value)) == CTRUE))
     { OID  e;
      { if (firstc_meta_reader(r) == 10)
         e = Core._eof->value;
        else e = nexte_meta_reader(r);
          GC_OID(e);}
      if (INHERIT(OWNER(e),Kernel._integer))
       Result = _oid_(((Reader_debug_where *) (*Reader._debug_where)(((OID)e))));
      else if (e == _oid_(_char_(((unsigned char)255 /* '\377' */))))
       { Reader_debug_where * _CL_obj = ((Reader_debug_where *) GC_OBJECT(Reader_debug_where,new_object_class(Reader._debug_where)));
        Result = _oid_(_CL_obj);
        }
      else Result = Kernel.cfalse;
        }
    else Result = Kernel.cfalse;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: read_alternate_command(r:meta_reader,br:{"help", "h"}) [NEW_ALLOC]
OID  read_alternate_command_meta_reader5_Reader(meta_reader *r,char *br)
{ { OID Result = 0;
    if (((OBJECT(ClaireBoolean,Reader.IN_DEBUG_LOOP_ask->value)) == CTRUE) || 
        ((OBJECT(ClaireBoolean,Reader.IN_BREAK_SYSTEM_ask->value)) == CTRUE))
     { if (firstc_meta_reader(r) == 10)
       Result = _oid_(new_object_class(Reader._debug_command_help));
      else Result = Kernel.cfalse;
        }
    else Result = Kernel.cfalse;
      POP_SIGNAL; return (Result);}
  }


// The c++ function for: read_alternate_command(r:meta_reader,br:{"dump"}) [NEW_ALLOC]
OID  read_alternate_command_meta_reader7_Reader(meta_reader *r,char *br)
{ { OID Result = 0;
    if (((OBJECT(ClaireBoolean,Reader.IN_DEBUG_LOOP_ask->value)) == CTRUE) || 
        ((OBJECT(ClaireBoolean,Reader.IN_BREAK_SYSTEM_ask->value)) == CTRUE))
     { if (firstc_meta_reader(r) == 10)
       Result = _oid_(new_object_class(Reader._debug_dump_stack));
      else Result = Kernel.cfalse;
        }
    else Result = Kernel.cfalse;
      POP_SIGNAL; return (Result);}
  }


// The c++ function for: read_alternate_command(r:meta_reader,br:{"dn", "do", "d", "up", "u"}) [NEW_ALLOC]
OID  read_alternate_command_meta_reader6_Reader(meta_reader *r,char *br)
{ GC_BIND;
  { OID Result = 0;
    if (((OBJECT(ClaireBoolean,Reader.IN_DEBUG_LOOP_ask->value)) == CTRUE) || 
        ((OBJECT(ClaireBoolean,Reader.IN_BREAK_SYSTEM_ask->value)) == CTRUE))
     { if (firstc_meta_reader(r) == 10)
       { Reader_debug_up_anddown * _CL_obj = ((Reader_debug_up_anddown *) GC_OBJECT(Reader_debug_up_anddown,new_object_class(Reader._debug_up_anddown)));
        (_CL_obj->up_ask = ((equal_string(br,"up") == CTRUE) ? CTRUE : ((equal_string(br,"u") == CTRUE) ? CTRUE : CFALSE)));
        Result = _oid_(_CL_obj);
        }
      else Result = Kernel.cfalse;
        }
    else Result = Kernel.cfalse;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: read_alternate_command(r:meta_reader,br:{"c", "o", "n", "s"}) [NEW_ALLOC]
OID  read_alternate_command_meta_reader8_Reader(meta_reader *r,char *br)
{ GC_BIND;
  { OID Result = 0;
    if ((OBJECT(ClaireBoolean,Reader.IN_BREAK_SYSTEM_ask->value)) == CTRUE)
     { if (firstc_meta_reader(r) == 10)
       { if (equal_string(br,"s") == CTRUE)
         Result = _oid_(((Reader_debug_continue *) (*Reader._debug_continue)(((OID)1))));
        else if (equal_string(br,"n") == CTRUE)
         Result = _oid_(((Reader_debug_continue *) (*Reader._debug_continue)(((OID)0))));
        else if (equal_string(br,"o") == CTRUE)
         Result = _oid_(((Reader_debug_continue *) (*Reader._debug_continue)(((OID)-1))));
        else if (equal_string(br,"c") == CTRUE)
         { Reader_debug_continue * _CL_obj = ((Reader_debug_continue *) GC_OBJECT(Reader_debug_continue,new_object_class(Reader._debug_continue)));
          Result = _oid_(_CL_obj);
          }
        else Result = Kernel.cfalse;
          }
      else Result = Kernel.cfalse;
        }
    else Result = Kernel.cfalse;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: read_alternate_command(r:meta_reader,br:{"locales", "var", "loc"}) [NEW_ALLOC]
OID  read_alternate_command_meta_reader9_Reader(meta_reader *r,char *br)
{ { OID Result = 0;
    if (((OBJECT(ClaireBoolean,Reader.IN_DEBUG_LOOP_ask->value)) == CTRUE) || 
        ((OBJECT(ClaireBoolean,Reader.IN_BREAK_SYSTEM_ask->value)) == CTRUE))
     { if (firstc_meta_reader(r) == 10)
       Result = _oid_(new_object_class(Reader._debug_locale_variable));
      else Result = Kernel.cfalse;
        }
    else Result = Kernel.cfalse;
      POP_SIGNAL; return (Result);}
  }


// ******************************************************************
// *    Part 3: debug loop                                          *
// ******************************************************************
//<sb> toggle debugger on/off
// The c++ function for: debug(_CL_obj:void) [0]
void  debug_void2()
{ if ((OBJECT(ClaireBoolean,Reader.DEBUG_ask->value)) == CTRUE)
   { (Reader.DEBUG_ask->value= Kernel.cfalse);
    { CL_INT  g0816 = (int )(current_color);
      CL_INT  g0817 = (int )(current_bold);
      CL_INT  g0818 = g0816;
      CL_INT  g0819 = g0817;
      color(g0816,g0817);
      color_princ_string1("\n`GREENdebugger removed\n");
      color(g0818,g0819);
      }
    }
  else { (Reader.DEBUG_ask->value= Kernel.ctrue);
      { CL_INT  g0820 = (int )(current_color);
        CL_INT  g0821 = (int )(current_bold);
        CL_INT  g0822 = g0820;
        CL_INT  g0823 = g0821;
        color(g0820,g0821);
        color_princ_string1("\n`GREENdebugger installed\n");
        color(g0822,g0823);
        }
      }
    POP_SIGNAL;}


//<sb> a special exception is used to abort a debug session
// The c++ function for: self_print(self:abort_debug) [0]
void  self_print_abort_debug1_Reader(Reader_abort_debug *self)
{ princ_string("== debug session aborted == ");
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
void  self_print_debug_fatal_error1_Reader(Reader_debug_fatal_error *self)
{ GC_BIND;
  princ_string("== fatal error during debug session ==\n");
  print_any(GC_OID(_oid_(self->src)));
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: debug_help(_CL_obj:void) [0]
void  debug_help_void2()
{ princ_string("==  debugger command help ==\nq     : abort debug session\nwhere : print the call stack\nblock : print the current frame and local variables\ndn    : print and select previous frame is the stack\nup    : print and select next frame is the stack\n<epx> : evaluate expression exp\n");
  POP_SIGNAL;}


//<sb> debug_loop is called when a program issue an unhandled
// exception, it allows stack inspection (call stack, variables)
// The c++ function for: debug_loop(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  debug_loop_void1()
{ GC_RESERVE(11);  // v3.0.55 optim !
  { PortObject * oldout = use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value));
    Reader_execution_context * old_ctx = GC_OBJECT(Reader_execution_context,save_context_boolean1(CTRUE));
    CL_INT  top = ClEnv->last_debug;
    CL_INT  li = ClEnv->last_index;
    (old_ctx->saved_system->exception_I = NULL);
    (ClEnv->base= ((OID)li));
    (ClEnv->index= ((OID)((CL_INT)li+(CL_INT)1)));
    (ClEnv->debug_I = -1);
    { Reader_debug_frame * f1 = GC_OBJECT(Reader_debug_frame,frame_I_integer1(top));
      Reader_debug_frame * fr = f1;
      { CL_INT  g0824 = (int )(current_color);
        CL_INT  g0825 = (int )(current_bold);
        CL_INT  g0826 = g0824;
        CL_INT  g0827 = g0825;
        color(g0824,g0825);
        color_princ_string1("`RED=== unhandled exception in ");
        g0824= (int )(current_color);
        g0825= (int )(current_bold);
        color(g0826,g0827);
        print_any(GC_OID(get_property(Kernel.source,fr)));
        color(g0824,g0825);
        color(g0824,g0825);
        color_princ_string1(" ===\n");
        color(g0826,g0827);
        }
      if (oldout != ClEnv->cout)
       { CL_INT  g0828 = (int )(current_color);
        CL_INT  g0829 = (int )(current_bold);
        CL_INT  g0830 = g0828;
        CL_INT  g0831 = g0829;
        color(g0828,g0829);
        color_princ_string1("`REDNote: output was ");
        g0828= (int )(current_color);
        g0829= (int )(current_bold);
        color(g0830,g0831);
        print_any(_oid_(oldout));
        color(g0828,g0829);
        color(g0828,g0829);
        color_princ_string1("\n");
        color(g0830,g0831);
        }
      show_frame_info_debug_frame1(fr);
      (Reader._starframe_star->value= _oid_(fr));
      (Reader.NB_DEBUG_EVAL->value= ((OID)0));
      print_exception_void();
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((CTRUE == CTRUE))
        { GC_LOOP;
          (Reader.IN_DEBUG_LOOP_ask->value= Kernel.ctrue);
          { ClaireHandler c_handle = ClaireHandler();
            if ERROR_IN 
            { { OID  x;
                { { char * g0832UU;
                    { { print_in_string_void();
                        princ_string("[fr");
                        print_any(((OID)fr->num));
                        princ_string("]debug> ");
                        g0832UU = end_of_string_void();
                        }
                      GC_STRING(g0832UU);}
                    x = read_command_string1(g0832UU);
                    }
                  GC_OID(x);}
                (Reader.IN_DEBUG_LOOP_ask->value= Kernel.cfalse);
                if (x == _oid_(Reader.q))
                 { ;ClEnv->cHandle = loop_handle; break;}
                else if (INHERIT(OWNER(x),Reader._debug_command_help))
                 debug_help_void2();
                else if (INHERIT(OWNER(x),Reader._debug_frame_info))
                 show_frame_info_debug_frame1(fr);
                else if (INHERIT(OWNER(x),Reader._debug_where))
                 { CL_INT  n = OBJECT(Reader_debug_where,x)->arg;
                  Reader_debug_frame * f = f1;
                  Reader_debug_frame * nf = GC_OBJECT(Reader_debug_frame,next_frame_debug_frame1(f));
                  { CL_INT loop_handle = ClEnv->cHandle;
                    OID gc_local;
                    while (((f != nf) && 
                        ((CL_INT)n > 0)))
                    { GC_LOOP;
                      n= ((CL_INT)n-(CL_INT)1);
                      show_frame_debug_frame1(f);
                      GC__ANY(f = nf, 10);
                      GC__ANY(nf = next_frame_debug_frame1(f), 11);
                      GC_UNLOOP;POP_SIGNAL;}
                    }
                  show_frame_debug_frame1(f);
                  }
                else if (INHERIT(OWNER(x),Reader._debug_locale_variable))
                 show_locale_variable_debug_frame1(fr);
                else if (INHERIT(OWNER(x),Reader._debug_dump_stack))
                 dump_stack_void1();
                else if (INHERIT(OWNER(x),Reader._debug_select_frame))
                 { GC__ANY(fr = get_frame_debug_frame1(fr,OBJECT(Reader_debug_select_frame,x)->arg), 7);
                  (Reader._starframe_star->value= _oid_(fr));
                  show_frame_info_debug_frame1(fr);
                  }
                else if (INHERIT(OWNER(x),Reader._debug_up_anddown))
                 { if (OBJECT(Reader_debug_up_anddown,x)->up_ask == CTRUE)
                   GC__ANY(fr = get_frame_debug_frame1(fr,((CL_INT)fr->num+(CL_INT)1)), 7);
                  else GC__ANY(fr = get_frame_debug_frame1(fr,((CL_INT)fr->num-(CL_INT)1)), 7);
                    (Reader._starframe_star->value= _oid_(fr));
                  show_frame_info_debug_frame1(fr);
                  }
                else { (Reader.NB_DEBUG_EVAL->value= ((OID)((CL_INT)(Reader.NB_DEBUG_EVAL->value)+(CL_INT)1)));
                    (ClEnv->debug_I = -1);
                    (ClEnv->trace_I = 0);
                    eval_command_any2(x,Reader.NB_DEBUG_EVAL->value,CFALSE);
                    }
                  }
              ERROR_FREE;}
            else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
            { c_handle.catchIt();{ (Reader.IN_DEBUG_LOOP_ask->value= Kernel.cfalse);
                if ((owner_any(_oid_(ClEnv->exception_I)) == Kernel._system_error) && 
                    ((CL_INT)CLREAD(system_error,ClEnv->exception_I,index) <= 3))
                 { (OBJECT(Reader_debug_fatal_error,Reader._stardebug_fatal_error_star->value)->src = ClEnv->exception_I);
                  close_toplevel_exception_exception1(OBJECT(ClaireException,Reader._stardebug_fatal_error_star->value));
                  }
                signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_IGN);
                print_exception_void();
                }
              }
            else PREVIOUS_HANDLER;}
          GC_UNLOOP;POP_SIGNAL;}
        }
      }
    (Reader.IN_DEBUG_LOOP_ask->value= Kernel.cfalse);
    restore_context_execution_context1(old_ctx);
    }
  GC_UNBIND; POP_SIGNAL;}


// ******************************************************************
// *    Part 3: breakpoint                                          *
// ******************************************************************
//<sb> breakpoint communicate with Core with a boolean flag
// The c++ function for: breakpoint!(_CL_obj:void) [0]
void  breakpoint_I_void2()
{ if ((CL_INT)ClEnv->trace_I > 1)
   (Core.SHOULD_BREAK_ask->value= Kernel.ctrue);
  POP_SIGNAL;}


// ******************************************************************
// *    Part 4: breakpoint loop                                     *
// ******************************************************************
// The c++ function for: breakpoint_help(_CL_obj:void) [0]
void  breakpoint_help_void1()
{ princ_string("==  breakpoint command help ==\nq     : abort debug session\nc     : continue\nwhere : print the call stack\nblock : print the current frame and local variables\ndn    : print and select previous frame is the stack\nup    : print and select next frame is the stack\nn     : continue and break at next call\ni     : continue and break at next call with the same caller\no     : continue and break in the next call of the caller\n<exp> : evaluate expression exp\n");
  POP_SIGNAL;}


//<sb> break_system is called when a breakpoint is 
// reached (or ^C) if the debugger is active
// The c++ function for: Core/break_system(_CL_obj:void) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  break_system_void2()
{ GC_RESERVE(11);  // v3.0.55 optim !
  if ((CL_INT)ClEnv->trace_I > 1)
   { signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_IGN);
    { Reader_debug_frame * f1 = GC_OBJECT(Reader_debug_frame,frame_I_integer1(ClEnv->debug_I));
      Reader_debug_frame * fr = f1;
      Reader_execution_context * old_ctx = GC_OBJECT(Reader_execution_context,save_context_boolean1(CTRUE));
      PortObject * oldout = use_as_output_port(OBJECT(PortObject,Core.cl_stdout->value));
      { CL_INT  g0833 = (int )(current_color);
        CL_INT  g0834 = (int )(current_bold);
        CL_INT  g0835 = g0833;
        CL_INT  g0836 = g0834;
        color(g0833,g0834);
        color_princ_string1("`RED=== break in ");
        g0833= (int )(current_color);
        g0834= (int )(current_bold);
        color(g0835,g0836);
        print_any(GC_OID(get_property(Kernel.source,fr)));
        color(g0833,g0834);
        color(g0833,g0834);
        color_princ_string1(" ===\n");
        color(g0835,g0836);
        }
      if (oldout != ClEnv->cout)
       { CL_INT  g0837 = (int )(current_color);
        CL_INT  g0838 = (int )(current_bold);
        CL_INT  g0839 = g0837;
        CL_INT  g0840 = g0838;
        color(g0837,g0838);
        color_princ_string1("`GREENNote: output was ");
        g0837= (int )(current_color);
        g0838= (int )(current_bold);
        color(g0839,g0840);
        print_any(_oid_(oldout));
        color(g0837,g0838);
        color(g0837,g0838);
        color_princ_string1("\n");
        color(g0839,g0840);
        }
      (Reader.NB_BREAKPOINT_EVAL->value= ((OID)0));
      if (INHERIT(OWNER(Reader.BREAK_EVENT->value),Reader._break_program))
       { print_any(GC_OID(Reader.BREAK_EVENT->value));
        princ_string("\n");
        }
      (ClEnv->debug_I = -1);
      (ClEnv->trace_I = 0);
      (Reader._starframe_star->value= _oid_(fr));
      show_frame_info_debug_frame1(fr);
      { ClaireHandler c_handle = ClaireHandler();
        if ERROR_IN 
        { { CL_INT loop_handle = ClEnv->cHandle;
            OID gc_local;
            while ((CTRUE == CTRUE))
            { GC_LOOP;
              (Reader.IN_BREAK_SYSTEM_ask->value= Kernel.ctrue);
              { ClaireHandler c_handle = ClaireHandler();
                if ERROR_IN 
                { { OID  x;
                    { { char * g0845UU;
                        { { print_in_string_void();
                            princ_string("[fr");
                            print_any(((OID)fr->num));
                            princ_string("]break> ");
                            g0845UU = end_of_string_void();
                            }
                          GC_STRING(g0845UU);}
                        x = read_command_string1(g0845UU);
                        }
                      GC_OID(x);}
                    (Reader.IN_BREAK_SYSTEM_ask->value= Kernel.cfalse);
                    if (x == _oid_(Reader.q))
                     close_exception((ClaireException *) new_object_class(Reader._abort_debug));
                    else if (INHERIT(OWNER(x),Reader._debug_command_help))
                     breakpoint_help_void1();
                    else if (INHERIT(OWNER(x),Reader._debug_frame_info))
                     show_frame_info_debug_frame1(fr);
                    else if (INHERIT(OWNER(x),Reader._debug_where))
                     { CL_INT  n = OBJECT(Reader_debug_where,x)->arg;
                      Reader_debug_frame * f = f1;
                      Reader_debug_frame * nf = GC_OBJECT(Reader_debug_frame,next_frame_debug_frame1(f));
                      { CL_INT loop_handle = ClEnv->cHandle;
                        OID gc_local;
                        while (((f != nf) && 
                            ((CL_INT)n > 0)))
                        { GC_LOOP;
                          n= ((CL_INT)n-(CL_INT)1);
                          show_frame_debug_frame1(f);
                          GC__ANY(f = nf, 9);
                          GC__ANY(nf = next_frame_debug_frame1(f), 10);
                          GC_UNLOOP;POP_SIGNAL;}
                        }
                      show_frame_debug_frame1(f);
                      }
                    else if (INHERIT(OWNER(x),Reader._debug_locale_variable))
                     show_locale_variable_debug_frame1(fr);
                    else if (INHERIT(OWNER(x),Reader._debug_dump_stack))
                     dump_stack_void1();
                    else if (INHERIT(OWNER(x),Reader._debug_select_frame))
                     { GC__ANY(fr = get_frame_debug_frame1(fr,OBJECT(Reader_debug_select_frame,x)->arg), 4);
                      (Reader._starframe_star->value= _oid_(fr));
                      show_frame_info_debug_frame1(fr);
                      }
                    else if (INHERIT(OWNER(x),Reader._debug_up_anddown))
                     { if (OBJECT(Reader_debug_up_anddown,x)->up_ask == CTRUE)
                       GC__ANY(fr = get_frame_debug_frame1(fr,((CL_INT)fr->num+(CL_INT)1)), 4);
                      else GC__ANY(fr = get_frame_debug_frame1(fr,((CL_INT)fr->num-(CL_INT)1)), 4);
                        (Reader._starframe_star->value= _oid_(fr));
                      show_frame_info_debug_frame1(fr);
                      }
                    else if (INHERIT(OWNER(x),Reader._debug_continue))
                     { if (OBJECT(Reader_debug_continue,x)->arg == (CNULL))
                       { (old_ctx->saved_system->step_I = 0);
                        princ_string("Continue...\n");
                        }
                      else if (OBJECT(Reader_debug_continue,x)->arg == 1)
                       (old_ctx->saved_system->step_I = ((CL_INT)old_ctx->saved_system->trace_I+(CL_INT)1));
                      else if (OBJECT(Reader_debug_continue,x)->arg == 0)
                       (old_ctx->saved_system->step_I = old_ctx->saved_system->trace_I);
                      else if (OBJECT(Reader_debug_continue,x)->arg == ((CL_INT)-1))
                       (old_ctx->saved_system->step_I = ((CL_INT)old_ctx->saved_system->trace_I-(CL_INT)1));
                      { ;ClEnv->cHandle = loop_handle; break;}
                      }
                    else { (Reader.NB_BREAKPOINT_EVAL->value= ((OID)((CL_INT)(Reader.NB_BREAKPOINT_EVAL->value)+(CL_INT)1)));
                        eval_command_any2(x,Reader.NB_BREAKPOINT_EVAL->value,CTRUE);
                        }
                      }
                  ERROR_FREE;}
                else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
                { c_handle.catchIt();{ if ((owner_any(_oid_(ClEnv->exception_I)) == Kernel._system_error) && 
                        ((CL_INT)CLREAD(system_error,ClEnv->exception_I,index) <= 3))
                     close_exception(ClEnv->exception_I);
                    signal_signal_handler(Core.CL_SIGINT,Core.CL_SIG_IGN);
                    if (INHERIT(ClEnv->exception_I->isa,Reader._abort_debug))
                     close_exception(ClEnv->exception_I);
                    print_exception_void();
                    }
                  }
                else PREVIOUS_HANDLER;}
              GC_UNLOOP;POP_SIGNAL;}
            }
          ERROR_FREE;}
        else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
        { c_handle.catchIt();{ if ((owner_any(_oid_(ClEnv->exception_I)) == Kernel._system_error) && 
                ((CL_INT)CLREAD(system_error,ClEnv->exception_I,index) <= 3))
             { (OBJECT(Reader_debug_fatal_error,Reader._stardebug_fatal_error_star->value)->src = ClEnv->exception_I);
              close_toplevel_exception_exception1(OBJECT(ClaireException,Reader._stardebug_fatal_error_star->value));
              }
            if (INHERIT(ClEnv->exception_I->isa,Reader._abort_debug))
             close_toplevel_exception_exception1(ClEnv->exception_I);
            else { CL_INT  g0841 = (int )(current_color);
                CL_INT  g0842 = (int )(current_bold);
                CL_INT  g0843 = g0841;
                CL_INT  g0844 = g0842;
                color(g0841,g0842);
                color_princ_string1("`REDThere is a bug in the breakpoint loop:\n");
                g0841= (int )(current_color);
                g0842= (int )(current_bold);
                color(g0843,g0844);
                print_any(GC_OID(_oid_(ClEnv->exception_I)));
                color(g0841,g0842);
                color(g0841,g0842);
                color_princ_string1("\n");
                color(g0843,g0844);
                }
              }
          }
        else PREVIOUS_HANDLER;}
      (Reader.IN_BREAK_SYSTEM_ask->value= Kernel.cfalse);
      (Reader.BREAK_EVENT->value= Kernel.cfalse);
      restore_context_execution_context1(old_ctx);
      signal_signal_handler(Core.CL_SIGINT,Reader.breakpoint_I);
      }
    }
  GC_UNBIND; POP_SIGNAL;}


//<sb> restore breakpoint on SIGINT
// ******************************************************************
// *    Part 4: breakpoints                                         *
// ******************************************************************
// The c++ function for: close(self:break_program) [SLOT_UPDATE+SAFE_RESULT]
Reader_break_program * close_break_program1(Reader_break_program *self)
{ (Reader.BREAK_ID->value= ((OID)((CL_INT)(Reader.BREAK_ID->value)+(CL_INT)1)));
  (self->id = Reader.BREAK_ID->value);
  POP_SIGNAL; return (self);}


// The c++ function for: self_print(self:break_method) [NEW_ALLOC]
void  self_print_break_method1_Reader(Reader_break_method *self)
{ GC_BIND;
  { CL_INT  g0846 = (int )(current_color);
    CL_INT  g0847 = (int )(current_bold);
    CL_INT  g0848 = g0846;
    CL_INT  g0849 = g0847;
    color(g0846,g0847);
    color_princ_string1("`GREEN<");
    g0846= (int )(current_color);
    g0847= (int )(current_bold);
    color(g0848,g0849);
    if (self->check_ask != CTRUE)
     { CL_INT  g0850 = (int )(current_color);
      CL_INT  g0851 = (int )(current_bold);
      CL_INT  g0852 = g0850;
      CL_INT  g0853 = g0851;
      color(g0850,g0851);
      color_princ_string1("`GREEN[inactive] ");
      color(g0852,g0853);
      }
    color(g0846,g0847);
    color(g0848,g0849);
    print_any(((OID)self->id));
    color(g0846,g0847);
    color(g0846,g0847);
    color_princ_string1(": break at method ");
    g0846= (int )(current_color);
    g0847= (int )(current_bold);
    color(g0848,g0849);
    print_any(_oid_(self->event));
    color(g0846,g0847);
    color(g0848,g0849);
    if (self->arg != Kernel.ctrue)
     { CL_INT  g0854 = (int )(current_color);
      CL_INT  g0855 = (int )(current_bold);
      CL_INT  g0856 = g0854;
      CL_INT  g0857 = g0855;
      color(g0854,g0855);
      color_princ_string1(" `GREENonly if ");
      g0854= (int )(current_color);
      g0855= (int )(current_bold);
      color(g0856,g0857);
      print_any(GC_OID(self->arg));
      color(g0854,g0855);
      color(g0856,g0857);
      }
    color(g0846,g0847);
    color(g0846,g0847);
    color_princ_string1(">");
    color(g0848,g0849);
    }
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_print(self:break_property) [NEW_ALLOC]
void  self_print_break_property1_Reader(Reader_break_property *self)
{ GC_BIND;
  { CL_INT  g0858 = (int )(current_color);
    CL_INT  g0859 = (int )(current_bold);
    CL_INT  g0860 = g0858;
    CL_INT  g0861 = g0859;
    color(g0858,g0859);
    color_princ_string1("`GREEN<");
    g0858= (int )(current_color);
    g0859= (int )(current_bold);
    color(g0860,g0861);
    if (self->check_ask != CTRUE)
     { CL_INT  g0862 = (int )(current_color);
      CL_INT  g0863 = (int )(current_bold);
      CL_INT  g0864 = g0862;
      CL_INT  g0865 = g0863;
      color(g0862,g0863);
      color_princ_string1("`GREEN[inactive] ");
      color(g0864,g0865);
      }
    color(g0858,g0859);
    color(g0860,g0861);
    print_any(((OID)self->id));
    color(g0858,g0859);
    color(g0858,g0859);
    color_princ_string1(": break at property ");
    g0858= (int )(current_color);
    g0859= (int )(current_bold);
    color(g0860,g0861);
    print_any(_oid_(self->event));
    color(g0858,g0859);
    color(g0860,g0861);
    if (self->arg != Kernel.ctrue)
     { CL_INT  g0866 = (int )(current_color);
      CL_INT  g0867 = (int )(current_bold);
      CL_INT  g0868 = g0866;
      CL_INT  g0869 = g0867;
      color(g0866,g0867);
      color_princ_string1(" `GREENonly if ");
      g0866= (int )(current_color);
      g0867= (int )(current_bold);
      color(g0868,g0869);
      print_any(GC_OID(self->arg));
      color(g0866,g0867);
      color(g0868,g0869);
      }
    color(g0858,g0859);
    color(g0858,g0859);
    color_princ_string1(">");
    color(g0860,g0861);
    }
  GC_UNBIND; POP_SIGNAL;}


//<sb> this is a Core callback that check whether
// we should stop the program. returns true if an
// existing active breakpoint is sastified
// The c++ function for: Core/should_break?(_CL_obj:void) [NEW_ALLOC+SLOT_UPDATE]
ClaireBoolean * should_break_ask_void1()
{ GC_BIND;
  (Reader._starcurd_star->value= ((OID)ClEnv->debug_I));
  { ClaireBoolean *Result ;
    { CL_INT  oldd = ClEnv->debug_I;
      CL_INT  oldt = ClEnv->trace_I;
      OID  m;
      { (ClEnv->debug_I = -1);
        (ClEnv->trace_I = 0);
        m = get_current_method_void1(CFALSE);
        }
      if (OWNER(m) == Kernel._method)
       { OID  p = GC_OID((*Kernel.selector)(m));
        OID  res;
        { ClaireHandler c_handle = ClaireHandler();
          if ERROR_IN 
          { { CL_INT loop_handle = ClEnv->cHandle;
              OID gc_local;
              ITERATE(g0870);
              res= Kernel.cfalse;
              bag *g0870_support;
              g0870_support = Reader._break_program->descendents;
              for (START(g0870_support); NEXT(g0870);)
              { GC_LOOP;
                { ClaireBoolean * g0871;
                  { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                      OID gc_local;
                      ITERATE(x);
                      V_C= Kernel.cfalse;
                      for (START(OBJECT(ClaireClass,g0870)->instances); NEXT(x);)
                      { GC_LOOP;
                        if (OBJECT(Reader_break_program,x)->check_ask == CTRUE)
                         { if ((INHERIT(OBJECT(ClaireObject,x)->isa,Reader._break_method)) ? ((m == _oid_(OBJECT(Reader_break_method,x)->event)) && 
                              (boolean_I_any(eval_any(GC_OID(OBJECT(Reader_break_program,x)->arg))) == CTRUE)) : ((INHERIT(OBJECT(ClaireObject,x)->isa,Reader._break_property)) && ((p == _oid_(OBJECT(Reader_break_property,x)->event)) && 
                              (boolean_I_any(eval_any(GC_OID(OBJECT(Reader_break_program,x)->arg))) == CTRUE))))
                           { (Reader.BREAK_EVENT->value= x);
                            { V_C = Kernel.ctrue;
                              ClEnv->cHandle = loop_handle;break;}
                            }
                          }
                        GC_UNLOOP; POP_SIGNAL;}
                      }
                    
                    g0871=OBJECT(ClaireBoolean,V_C);}
                  if (g0871 == CTRUE)
                   { res = _oid_(g0871);
                    ClEnv->cHandle = loop_handle;break;}
                  }
                GC_UNLOOP; POP_SIGNAL;}
              }
            ERROR_FREE;}
          else if (belong_to(_oid_(ClEnv->exception_I),_oid_(Kernel._any)) == CTRUE)
          { c_handle.catchIt();{ if (should_trace_ask_module1(Reader.it,0) == CTRUE)
               mtformat_module1(Reader.it,"breakpoint check failure\n~S \n",0,GC_OBJECT(list,list::alloc(1,GC_OID(_oid_(ClEnv->exception_I)))));
              else ;res = Kernel.cfalse;
              }
            }
          else PREVIOUS_HANDLER;}
        (ClEnv->debug_I = oldd);
        (ClEnv->trace_I = oldt);
        Result = OBJECT(ClaireBoolean,res);
        }
      else Result = CFALSE;
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: toggle_break(self:break_program) [SLOT_UPDATE+SAFE_RESULT]
Reader_break_program * toggle_break_break_program1(Reader_break_program *self)
{ (self->check_ask = not_any(_oid_(self->check_ask)));
  POP_SIGNAL; return (self);}


// The c++ function for: toggle_break_break_program1_type
ClaireType * toggle_break_break_program1_type(ClaireType *self)
{ POP_SIGNAL; return (self);}


//<sb> reads a breakpoint declaration on the command line
// if the breakpoint already exists its activation flag
// is toggled
// The c++ function for: read_alternate_command(r:meta_reader,br:{"br"}) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
OID  read_alternate_command_meta_reader2_Reader(meta_reader *r,char *br)
{ GC_BIND;
  { OID Result = 0;
    { OID  e;
      { if (firstc_meta_reader(r) == 10)
         e = Core._eof->value;
        else e = nexte_meta_reader(r);
          GC_OID(e);}
      OID  a;
      { if (firstc_meta_reader(r) == 10)
         a = Kernel.ctrue;
        else a = nexte_meta_reader(r);
          GC_OID(a);}
      OID  res = Kernel.cfalse;
      if (e == _oid_(_char_(((unsigned char)255 /* '\377' */))))
       { if (INHERIT(OWNER(Reader.BREAK_EVENT->value),Reader._break_program))
         res= _oid_(toggle_break_break_program1(OBJECT(Reader_break_program,Reader.BREAK_EVENT->value)));
        }
      else if (INHERIT(OWNER(e),Kernel._integer))
       { OID  xtest;
        { { OID  x_some = CNULL;
            { CL_INT loop_handle = ClEnv->cHandle;
              ITERATE(g0872);
              bag *g0872_support;
              g0872_support = Reader._break_property->descendents;
              for (START(g0872_support); NEXT(g0872);)
              { ClaireBoolean * g0873;
                { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                    ITERATE(x);
                    V_C= Kernel.cfalse;
                    for (START(OBJECT(ClaireClass,g0872)->instances); NEXT(x);)
                    if (OBJECT(Reader_break_program,x)->id == e)
                     { V_C = x_some= x;
                      ClEnv->cHandle = loop_handle;break;}
                    }
                  
                  g0873=OBJECT(ClaireBoolean,V_C);}
                if (g0873 == CTRUE)
                 { ;ClEnv->cHandle = loop_handle; break;}
                }
              }
            xtest = x_some;
            }
          GC_OID(xtest);}
        if (xtest != CNULL)
         { Reader_break_property * x = OBJECT(Reader_break_property,xtest);
          (x->arg = a);
          res = _oid_(toggle_break_break_program1(x));
          }
        else res = Kernel.cfalse;
          }
      else if (INHERIT(OWNER(e),Kernel._property))
       { { OID  xtest;
          { { OID  x_some = CNULL;
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(g0874);
                bag *g0874_support;
                g0874_support = Reader._break_property->descendents;
                for (START(g0874_support); NEXT(g0874);)
                { ClaireBoolean * g0875;
                  { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                      ITERATE(x);
                      V_C= Kernel.cfalse;
                      for (START(OBJECT(ClaireClass,g0874)->instances); NEXT(x);)
                      if (_oid_(OBJECT(Reader_break_property,x)->event) == e)
                       { V_C = x_some= x;
                        ClEnv->cHandle = loop_handle;break;}
                      }
                    
                    g0875=OBJECT(ClaireBoolean,V_C);}
                  if (g0875 == CTRUE)
                   { ;ClEnv->cHandle = loop_handle; break;}
                  }
                }
              xtest = x_some;
              }
            GC_OID(xtest);}
          if (xtest != CNULL)
           { Reader_break_property * x = OBJECT(Reader_break_property,xtest);
            (x->arg = a);
            res = _oid_(toggle_break_break_program1(x));
            }
          else { Reader_break_property * _CL_obj = ((Reader_break_property *) GC_OBJECT(Reader_break_property,new_object_class(Reader._break_property)));
              (_CL_obj->event = OBJECT(property,e));
              (_CL_obj->arg = a);
              add_I_property(Kernel.instances,Reader._break_property,11,_oid_(_CL_obj));
              res = _oid_(close_break_program1(_CL_obj));
              }
            }
        { CL_INT loop_handle = ClEnv->cHandle;
          ITERATE(r);
          for (START(OBJECT(property,e)->restrictions); NEXT(r);)
          (OBJECT(restriction,r)->module_I->status = 4);
          }
        ;}
      else if (Kernel._method == OWNER(e))
       { { OID  xtest;
          { { OID  x_some = CNULL;
              { CL_INT loop_handle = ClEnv->cHandle;
                ITERATE(g0876);
                bag *g0876_support;
                g0876_support = Reader._break_method->descendents;
                for (START(g0876_support); NEXT(g0876);)
                { ClaireBoolean * g0877;
                  { OID V_C;{ CL_INT loop_handle = ClEnv->cHandle;
                      ITERATE(x);
                      V_C= Kernel.cfalse;
                      for (START(OBJECT(ClaireClass,g0876)->instances); NEXT(x);)
                      if (_oid_(OBJECT(Reader_break_method,x)->event) == e)
                       { V_C = x_some= x;
                        ClEnv->cHandle = loop_handle;break;}
                      }
                    
                    g0877=OBJECT(ClaireBoolean,V_C);}
                  if (g0877 == CTRUE)
                   { ;ClEnv->cHandle = loop_handle; break;}
                  }
                }
              xtest = x_some;
              }
            GC_OID(xtest);}
          if (xtest != CNULL)
           { Reader_break_method * x = OBJECT(Reader_break_method,xtest);
            (x->arg = a);
            res = _oid_(toggle_break_break_program1(x));
            }
          else { Reader_break_method * _CL_obj = ((Reader_break_method *) GC_OBJECT(Reader_break_method,new_object_class(Reader._break_method)));
              (_CL_obj->event = OBJECT(method,e));
              (_CL_obj->arg = a);
              add_I_property(Kernel.instances,Reader._break_method,11,_oid_(_CL_obj));
              res = _oid_(close_break_program1(_CL_obj));
              }
            }
        (OBJECT(restriction,e)->module_I->status = 4);
        ;}
      if ((boolean_I_any(res) == CTRUE) && 
          (Reader.DEBUG_ask->value != Kernel.ctrue))
       debug_void2();
      Result = res;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }



