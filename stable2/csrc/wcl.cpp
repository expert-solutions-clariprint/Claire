/***** CLAIRE Compilation of file ./meta/wcl.cl 
         [version 3.3.36 / safety 5] Thu Nov 17 17:12:44 2005 *****/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Serialize.h>
#include <Language.h>
#include <Reader.h>

//*********************************************************************
//* CLAIRE                                            Sylvain Benilan *
//* wcl.cl                                                            *
//* Copyright (C) 2000 - 2003 xl. All Rights Reserved                 *
//*********************************************************************
// ********************************************************************
// *   Part 1: echo & self_html (<?= and <?==)                        *
// ********************************************************************
// The c++ function for: print_oid(x:any) [0]
void  print_oid_any1(OID x)
{ princ_string(CL_Oid(x));
  POP_SIGNAL;}


// The c++ function for: echo(self:any) [NEW_ALLOC+RETURN_ARG]
void  echo_any1_Reader(OID self)
{ (*Kernel.self_print)(self);
  POP_SIGNAL;}


// The c++ function for: echo(self:string) [0]
void  echo_string1_Reader(char *self)
{ princ_string(self);
  POP_SIGNAL;}


// The c++ function for: echo(self:integer) [0]
void  echo_integer1_Reader(int self)
{ princ_integer(self);
  POP_SIGNAL;}


// The c++ function for: echo(g0878:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  echo_float1_Reader_(OID g0878)
{ echo_float1_Reader(float_v(g0878));}


// The c++ function for: echo(self:float) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  echo_float1_Reader(double self)
{ GC_BIND;
  print_any(GC_OID(_float_(self)));
  GC_UNBIND; POP_SIGNAL;}


// The c++ function for: echo(self:char) [0]
void  echo_char1_Reader(ClaireChar *self)
{ princ_char(self);
  POP_SIGNAL;}


// The c++ function for: echo(p:property,self:object) [NEW_ALLOC+RETURN_ARG]
void  echo_property1_Reader(property *p,ClaireObject *self)
{ GC_BIND;
  if (known_ask_property(p,self) == CTRUE)
   (*Language.echo)(GC_OID(get_property(p,self)));
  else ;GC_UNBIND; POP_SIGNAL;}


// The c++ function for: self_html(src:string) [0]
void  self_html_string1_Reader(char *src)
{ { CL_INT  len = LENGTH_STRING(src);
    {
		char *max = src + len;
		char buf[256];
		char *travel = buf;
		while(src < max) {
			int c = (unsigned char)(*src);
			if(c == 10) 
				{*travel++ = '<';
				*travel++ = 'b';
				*travel++ = 'r';
				*travel++ = '>';
				*travel++ = '\n';}
			if(c == 9) 
				{*travel++ = '\240';
				*travel++ = '\240';
				*travel++ = '\240';
				*travel++ = '\240';}
			else if(c >= 32 && c <= 64) {
				switch(c) {
					case ' ':
						{*travel++ = '\240';
						break;}
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
						*travel++ = '#';
						*travel++ = '3';
						*travel++ = '9';
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
			}
			else if(c >= 128 && c <= 255) {
				travel += sprintf(travel, "&#%d;", c);
			}
			else *travel++ = c;
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
char * nl2br_string1(char *self)
{ GC_BIND;
  { char *Result ;
    Result = replace_string(GC_STRING(replace_string(self,"\n","<br>")),"\r","");
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: write_port(self:self_html_converter,buf:char*,len:integer) [SAFE_RESULT]
int  write_port_self_html_converter1_Reader(Reader_self_html_converter *self,char*buf,int len)
{ {char out[256]; char *travel = out;
		int i = 0;
		for(;i < len;i++) {
			switch (buf[i]) {
				case '\n':
					{*travel++ = '<';
					*travel++ = 'b';
					*travel++ = 'r';
					*travel++ = '>';
					*travel++ = '\n';}
				case ' ':
					{*travel++ = '\240';
					break;}
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
					*travel++ = '#';
					*travel++ = '3';
					*travel++ = '9';
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
				case '\t':
					{*travel++ = '\240';
					*travel++ = '\240';
					*travel++ = '\240';
					*travel++ = '\240';
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
			if (travel - out > 250) {
				Core.write_port->fcall((CL_INT)self->src, (CL_INT)out, (CL_INT)(travel - out));
				travel = out;
			}
		}
		if (travel - out > 0)
			Core.write_port->fcall((CL_INT)self->src, (CL_INT)out, (CL_INT)(travel - out));};
  POP_SIGNAL; return (len);}


// The c++ function for: self_html(self:any) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  self_html_any1_Reader(OID self)
{ (OBJECT(Reader_self_html_converter,Reader.SELF_HTML_CONVERTER->value)->src = use_as_output_port(OBJECT(PortObject,Reader.SELF_HTML_CONVERTER->value)));
  print_any(self);
  use_as_output_port(OBJECT(Reader_self_html_converter,Reader.SELF_HTML_CONVERTER->value)->src);
  POP_SIGNAL;}


// The c++ function for: self_html(p:property,self:object) [NEW_ALLOC]
void  self_html_property1_Reader(property *p,ClaireObject *self)
{ GC_BIND;
  if ((boolean_I_any(_oid_(_at_property1(p,OWNER(_oid_(self))))) == CTRUE) && 
      (known_ask_property(p,self) == CTRUE))
   (*Language.self_html)(GC_OID(get_property(p,self)));
  else ;GC_UNBIND; POP_SIGNAL;}


// *********************************************************************
// *   Part 2: Reader callback                                         *
// *********************************************************************
// The c++ function for: wcl_start?(r:meta_reader,p:integer) [NEW_ALLOC]
ClaireBoolean * wcl_start_ask_meta_reader1(meta_reader *r,int p)
{ GC_BIND;
  { ClaireBoolean *Result ;
    if (p == 63)
     { ClaireChar * c = getc_port1(r->fromp);
      if (((unsigned char) c->ascii) == ((unsigned char)62 /* '>' */))
       Result = CTRUE;
      else { unget_port2(r->fromp,c);
          Result = CFALSE;
          }
        }
    else Result = CFALSE;
      GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: nextswcl(r:meta_reader) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  nextswcl_meta_reader1(meta_reader *r)
{ GC_BIND;
  { OID Result = 0;
    { OID  wcl = GC_OID(nexts_meta_reader(r,Reader.none));
      if ((equal(wcl,r->paren) == CTRUE) || 
          ((equal(wcl,r->curly) == CTRUE) || 
            ((equal(wcl,Reader.OR->value) == CTRUE) || 
              ((equal(wcl,r->bracket) == CTRUE) || 
                (equal(wcl,r->comma) == CTRUE)))))
       Result = _oid_(Reader.none);
      else if (wcl == _oid_(Reader._cl_if))
       Result = readif_meta_reader(r,41);
      else if (wcl == _oid_(Reader._cl_Zif))
       { If * _Zi = GC_OBJECT(If,OBJECT(If,readif_meta_reader(r,41)));
        if (boolean_I_any(eval_any(GC_OID(_Zi->test))) == CTRUE)
         Result = _Zi->arg;
        else Result = _Zi->other;
          }
      else if (wcl == _oid_(Reader._cl_else))
       Serror_integer1(173,"Expression starting with else",Kernel.nil);
      else if (keyword_ask_any(wcl) == CTRUE)
       Result = nextstruct_meta_reader(r,OBJECT(keyword,wcl),Reader.none);
      else Result = wcl;
        }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: Call_wcl!(self:property,l:list,loc:tuple) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
Call_wcl * Call_wcl_I_property1(property *self,list *l,tuple *loc)
{ GC_BIND;
  { Call_wcl *Result ;
    { Call_wcl * c;
      { { Call_wcl * _CL_obj = ((Call_wcl *) GC_OBJECT(Call_wcl,new_object_class(Language._Call_wcl)));
          (_CL_obj->selector = self);
          (_CL_obj->args = l);
          add_I_property(Kernel.instances,Language._Call_wcl,11,_oid_(_CL_obj));
          c = _CL_obj;
          }
        GC_OBJECT(Call_wcl,c);}
      tuple * g0879 = loc;
      OID  f = (*(g0879))[1];
      OID  ln = (*(g0879))[2];
      OID  o = (*(g0879))[3];
      char * s = ((self == Language.self_html) ?
        "==" :
        ((self == Language.echo) ?
          "=" :
          self->name->name ) );
      GC_OBJECT(list,c->location)->addFast((OID)f);
      GC_OBJECT(list,c->location)->addFast((OID)ln);
      GC_OBJECT(list,c->location)->addFast((OID)((OID)((CL_INT)(o)-(CL_INT)LENGTH_STRING(s))));
      GC_OBJECT(list,c->location)->addFast((OID)((OID)LENGTH_STRING(s)));
      Result = c;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: build_call_wcl(r:meta_reader,prop:property) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  build_call_wcl_meta_reader2(meta_reader *r,property *prop)
{ GC_BIND;
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
          if (wcl_start_ask_meta_reader1(r,skipc_meta_reader(r)) == CTRUE)
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
OID  build_top_call_wcl_meta_reader1(meta_reader *r,property *prop)
{ GC_BIND;
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
OID  read_top_wcl_meta_reader1(meta_reader *r)
{ GC_BIND;
  { OID Result = 0;
    { PortObject * p = GC_OBJECT(PortObject,r->fromp);
      char * d = GC_STRING(freadline_port1(p,"<?"));
      Princ_wcl * c;
      { { Princ_wcl * _CL_obj = ((Princ_wcl *) GC_OBJECT(Princ_wcl,new_object_class(Language._Princ_wcl)));
          (_CL_obj->selector = Kernel.princ);
          (_CL_obj->args = list::alloc(1,_string_(d)));
          add_I_property(Kernel.instances,Language._Princ_wcl,11,_oid_(_CL_obj));
          c = _CL_obj;
          }
        GC_OBJECT(Princ_wcl,c);}
      (p->firstc = 32);
      { tuple * g0880 = freadline_port4(p,OBJECT(bag,Reader.WCL_STOP->value));
        OID  inl = GC_OID((*(g0880))[1]);
        OID  sep = GC_OID((*(g0880))[2]);
        if (equal(sep,_string_("?")) == CTRUE)
         { ClaireChar * ch = getc_port1(p);
          if (((unsigned char) ch->ascii) == ((unsigned char)62 /* '>' */))
           { OID  swcl = GC_OID(read_top_wcl_meta_reader1(r));
            if (swcl == Core._eof->value)
             Result = _oid_(c);
            else Result = Do_I_any(_oid_(c),swcl);
              }
          else { unget_port2(p,_char_(((unsigned char)63 /* '?' */)));
              unget_port2(p,ch);
              Result = _oid_(c);
              }
            }
        else { if ((CL_INT)LENGTH_STRING(string_v(sep)) > 0)
             (*Core.unget)(_oid_(p),
              sep);
            if (LENGTH_STRING(string_v(inl)) == 0)
             Result = _oid_(c);
            else { OID  prop;
                if (equal(inl,_string_("=")) == CTRUE)
                 prop = _oid_(Language.echo);
                else if (equal(inl,_string_("==")) == CTRUE)
                 prop = _oid_(Language.self_html);
                else if (equal(inl,_string_("oid")) == CTRUE)
                 prop = _oid_(Reader.print_oid);
                else prop = value_string(string_v(inl));
                  if (prop != CNULL)
                 Result = Do_I_any(_oid_(c),GC_OID(build_top_call_wcl_meta_reader1(r,OBJECT(property,prop))));
                else { OID  V_CL0881;close_exception(((general_error *) (*Core._general_error)(_string_("The property ~A is not known in ...<?~A"),
                      _oid_(list::alloc(2,inl,inl)))));
                    
                    Result=_void_(V_CL0881);}
                  }
              }
          }
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


// The c++ function for: read_wcl(r:meta_reader) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE+RETURN_ARG]
OID  read_wcl_meta_reader1(meta_reader *r)
{ GC_BIND;
  { OID Result = 0;
    { PortObject * p = GC_OBJECT(PortObject,r->fromp);
      char * d = GC_STRING(freadline_port1(p,"<?"));
      Princ_wcl * c;
      { { Princ_wcl * _CL_obj = ((Princ_wcl *) GC_OBJECT(Princ_wcl,new_object_class(Language._Princ_wcl)));
          (_CL_obj->selector = Kernel.princ);
          (_CL_obj->args = list::alloc(1,_string_(d)));
          add_I_property(Kernel.instances,Language._Princ_wcl,11,_oid_(_CL_obj));
          c = _CL_obj;
          }
        GC_OBJECT(Princ_wcl,c);}
      char * pend = "";
      (p->firstc = 32);
      { tuple * g0882 = freadline_port4(p,OBJECT(bag,Reader.WCL_STOP->value));
        OID  inl = GC_OID((*(g0882))[1]);
        OID  sep = GC_OID((*(g0882))[2]);
        if (equal(sep,_string_("?")) == CTRUE)
         { ClaireChar * ch = getc_port1(p);
          if (((unsigned char) ch->ascii) == ((unsigned char)62 /* '>' */))
           Result = Do_I_any(_oid_(c),GC_OID(read_wcl_meta_reader1(r)));
          else { unget_port2(p,_char_(((unsigned char)63 /* '?' */)));
              unget_port2(p,ch);
              Result = _oid_(c);
              }
            }
        else { if ((CL_INT)LENGTH_STRING(string_v(sep)) > 0)
             (*Core.unget)(_oid_(p),
              sep);
            if (LENGTH_STRING(string_v(inl)) == 0)
             { if ((equal(sep,_string_("|")) == CTRUE) || 
                  ((equal(sep,_string_("}")) == CTRUE) || 
                    ((equal(sep,_string_("]")) == CTRUE) || 
                      ((equal(sep,_string_(")")) == CTRUE) || 
                        (equal(sep,_string_(",")) == CTRUE)))))
               Result = _oid_(c);
              else { OID  g0883UU;
                  { { OID  wcl = GC_OID(nextswcl_meta_reader1(r));
                      if (wcl_start_ask_meta_reader1(r,skipc_meta_reader(r)) == CTRUE)
                       g0883UU = Do_I_any(wcl,GC_OID(read_wcl_meta_reader1(r)));
                      else g0883UU = wcl;
                        }
                    GC_OID(g0883UU);}
                  Result = Do_I_any(_oid_(c),g0883UU);
                  }
                }
            else { OID  prop;
                if (equal(inl,_string_("=")) == CTRUE)
                 prop = _oid_(Language.echo);
                else if (equal(inl,_string_("==")) == CTRUE)
                 prop = _oid_(Language.self_html);
                else if (equal(inl,_string_("oid")) == CTRUE)
                 prop = _oid_(Reader.print_oid);
                else prop = value_string(string_v(inl));
                  if (prop != CNULL)
                 Result = Do_I_any(_oid_(c),GC_OID(build_call_wcl_meta_reader2(r,OBJECT(property,prop))));
                else { OID  V_CL0884;close_exception(((general_error *) (*Core._general_error)(_string_("The property ~A is not known in ...<?~A"),
                      _oid_(list::alloc(2,inl,inl)))));
                    
                    Result=_void_(V_CL0884);}
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
PortObject * fopen_source_string1(char *self)
{ GC_BIND;
  if ((match_wildcard_ask_string(self,"*.cl") != CTRUE) && 
      (match_wildcard_ask_string(self,"*.wcl") != CTRUE))
   self= GC_STRING(append_string(self,".cl"));
  { PortObject *Result ;
    { PortObject * f = GC_OBJECT(buffer,fopen_string1(self,"r"));
      if (match_wildcard_ask_string(self,"*.wcl") == CTRUE)
       { char * l = GC_STRING(freadline_port(f));
        if (match_wildcard_ask_string(l,"#!*") == CTRUE)
         { unget_port1(f,"\n?>");
          unget_port1(f,l);
          }
        else { unget_port1(f,"\n");
            unget_port1(f,l);
            unget_port1(f,"?>");
            }
          }
      f= GC_OBJECT(line_counter,close_target_I_filter1(line_counter_I_port1(f)));
      Result = f;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> reads a WCL file and return a list of claire definition
// self should look like "filepath@PATH_INFO@path_info"
// The c++ function for: load_wcl!(self:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
list * load_wcl_I_string1(char *self)
{ GC_RESERVE(1);  // HOHO v3.0.55 optim !
  reader_push_void1();
  (Reader.reader->index = 1);
  (Reader.reader->maxstack = 1);
  { list *Result ;
    { list * t = GC_OBJECT(list,explode_string(self,"@PATH_INFO@"));
      char * fname = GC_STRING(string_v(last_list(explode_string(string_v((*(t))[1]),GC_STRING(string_v(Core._starfs_star->value))))));
      char * pinfo = GC_STRING((((CL_INT)t->length > 1) ?
        _7_string(string_v((*(t))[2]),fname) :
        fname ));
      PortObject * f = GC_OBJECT(PortObject,fopen_source_string1(string_v((*(t))[1])));
      CL_INT  start = ClEnv->base;
      CL_INT  top = ClEnv->index;
      OID  _staritem_star = CNULL;
      list * defs = list::empty(Language._Defclaire);
      Do * bo;
      { { Do * _CL_obj = ((Do *) GC_OBJECT(Do,new_object_class(Language._Do)));
          (_CL_obj->args = list::empty(Kernel._any));
          add_I_property(Kernel.instances,Language._Do,11,_oid_(_CL_obj));
          bo = _CL_obj;
          }
        GC_OBJECT(Do,bo);}
      list * lbody = GC_OBJECT(list,bo->args);
      (ClEnv->base= ((OID)top));
      (Reader.reader->fromp = f);
      (Reader.reader->toplevel = CFALSE);
      _staritem_star= GC_OID(readblock_port(f));
      { CL_INT loop_handle = ClEnv->cHandle;
        OID gc_local;
        while ((equal(_staritem_star,Core._eof->value) != CTRUE))
        { GC_LOOP;
          (ClEnv->base= ((OID)top));
          (ClEnv->index= ((OID)((CL_INT)top+(CL_INT)((CL_INT)Reader.reader->maxstack+(CL_INT)1))));
          if (Kernel._string == OWNER(_staritem_star))
           ;else if (INHERIT(OWNER(_staritem_star),Language._Defclaire))
           defs->addFast((OID)_staritem_star);
          else lbody->addFast((OID)_staritem_star);
            (Reader.reader->index = 1);
          (Reader.reader->maxstack = 1);
          (ClEnv->index= ((OID)top));
          (ClEnv->base= ((OID)top));
          GC__OID(_staritem_star = readblock_port(f), 9);
          GC_UNLOOP;POP_SIGNAL;}
        }
      { OID  g0885UU;
        { Defmethod * _CL_obj = ((Defmethod *) GC_OBJECT(Defmethod,new_object_class(Language._Defmethod)));
          { Defmethod * g0886 = _CL_obj; 
            Call * g0887;
            { Call * _CL_obj = ((Call *) GC_OBJECT(Call,new_object_class(Language._Call)));
              (_CL_obj->selector = Reader.load_wcl);
              { Call * g0888 = _CL_obj; 
                list * g0889;
                { OID v_bag;
                  GC_ANY(g0889= list::empty(Kernel.emptySet));
                  { { Vardef * _CL_obj = ((Vardef *) GC_OBJECT(Vardef,new_object_class(Language._Vardef)));
                      (_CL_obj->pname = gensym_void());
                      (_CL_obj->range = set::alloc(1,_string_(pinfo)));
                      add_I_property(Kernel.instances,Language._Vardef,11,_oid_(_CL_obj));
                      v_bag = _oid_(_CL_obj);
                      }
                    GC_OID(v_bag);}
                  ((list *) g0889)->addFast((OID)v_bag);}
                (g0888->args = g0889);}
              add_I_property(Kernel.instances,Language._Call,11,_oid_(_CL_obj));
              g0887 = _CL_obj;
              }
            (g0886->arg = g0887);}
          (_CL_obj->set_arg = _oid_(Kernel._void));
          (_CL_obj->body = _oid_(bo));
          (_CL_obj->inline_ask = Kernel.cfalse);
          add_I_property(Kernel.instances,Language._Defmethod,11,_oid_(_CL_obj));
          g0885UU = _oid_(_CL_obj);
          }
        defs->addFast((OID)g0885UU);
        }
      reader_pop_void1();
      (ClEnv->base= ((OID)start));
      (ClEnv->index= ((OID)top));
      (*Core.fclose)(_oid_(f));
      Result = defs;
      }
    GC_UNBIND; POP_SIGNAL; return (Result);}
  }


//<sb> add a list of WCL file defined by wcl_path wildcard
// to the module's made_of. Any further request with the
// given pathinfo/file will call the compiled method
// The c++ function for: add_wcl(self:module,wcl_path:string,wild:string,pathinfo:string) [NEW_ALLOC+BAG_UPDATE+SLOT_UPDATE]
void  add_wcl_module1(module *self,char *wcl_path,char *wild,char *pathinfo)
{ GC_BIND;
  setenv_string("WCL_RAISE_ERRORS=1");
  cast_I_list1(self->made_of,Kernel._string);
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(x);
    bag *x_support;
    x_support = GC_OBJECT(list,entries_string1(wcl_path,wild));
    for (START(x_support); NEXT(x);)
    { GC_LOOP;
      if (((CL_INT)LENGTH_STRING(string_v(x)) > 0) && 
          (string_v(x)[1 - 1] != ((unsigned char)46 /* '.' */)))
       { if (isfile_ask_string(_7_string(wcl_path,string_v(x))) == CTRUE)
         GC_OBJECT(list,self->made_of)->addFast((OID)GC_OID(_string_(append_string(GC_STRING(append_string(GC_STRING(_7_string(wcl_path,string_v(x))),"@PATH_INFO@")),pathinfo))));
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
void  add_wcl_module2(module *self,char *wcl_path,ClaireType *wild,char *pathinfo)
{ GC_BIND;
  { CL_INT loop_handle = ClEnv->cHandle;
    OID gc_local;
    ITERATE(w);
    bag *w_support;
    w_support = GC_OBJECT(bag,enumerate_any(_oid_(wild)));
    for (START(w_support); NEXT(w);)
    add_wcl_module1(self,wcl_path,string_v(w),pathinfo);
    }
  GC_UNBIND; POP_SIGNAL;}



