/***********************************************************************/
/**   microCLAIRE                                       Yves Caseau    */
/**   clPort.cpp                                                       */
/**  Copyright (C) 1998-2003 Yves Caseau. All Rights Reserved.         */
/**  cf claire.h                                                       */
/***********************************************************************/

#include <claire.h>
#include <Kernel.h>
#include <marie.h>
#include <Core.h>


// this file contains the I/O objects and methods

/*********************************************************************/
/** Contents                                                         */
/**    1: Claire Ports                                               */
/**    3. Reader functions                                           */
/**    3. Character                                                  */
/**    4. System interface (miscellaneous)                           */
/*********************************************************************/


// ***************************************************************************
// * PART 1: Claire Ports                                                    *
// ***************************************************************************

//<sb> In xlclaire ports are implemented at the meta-level (port.cl)
// the C++ PortObject class however have an API layer
// accessible by the kernel for low-level port operations

#ifdef CLPC
//<sb> on PC we use a sigleton instance that when constructed
// initializes the win sock subsystem
class InitSocket {
public:
	static InitSocket single;
	CL_INT initFailed;
	InitSocket() {
		WSADATA wsaData;
 		initFailed = (WSAStartup(0x0101, &wsaData) != 0);
 }
 ~InitSocket() {if(!initFailed) WSACleanup();}
};

InitSocket InitSocket::single = InitSocket();
#endif


void prefree_I_any(OID o)  {
	if(ClEnv->verbose > 4) {
		 PortObject* p = use_as_output_port(ClEnv->ctrace);
		 princ_string("prefree! @ ");
		 princ_string(OWNER(o)->name->name);
		 princ_string(" not implemented\n");
		 use_as_output_port(p);
	 }
}

void free_I_any(OID o)  {
	if(ClEnv->verbose > 4) {
		 PortObject* p = use_as_output_port(ClEnv->ctrace);
		 princ_string("free! @ ");
		 princ_string(OWNER(o)->name->name);
		 princ_string(" not implemented\n");
		 use_as_output_port(p);
	 }
}


PortObject *use_as_output_port(PortObject *p)
{ if (p != ClEnv->cout)
     {PortObject *x = ClEnv->cout;
      ClEnv->cout = p;
      if (ClAlloc->statusGC != 2) GC_PUSH(x);
      return x;}
  else return p;}


char PortObject::get() {
	return getc_port1(this)->ascii;
}

CL_INT PortObject::gets(void* data, CL_INT len) {
	return Core.read_port->fcall((CL_INT)this, (CL_INT)data, len);
}

CL_INT PortObject::eof_ask() {
	return (ClaireBoolean*)Core.eof_port_ask->fcall((CL_INT)this) == CTRUE;
}

void PortObject::put(char c) {
	Core.write_port->fcall((CL_INT)this, (CL_INT)&c, 1);
}

CL_INT PortObject::puts(void* data, CL_INT len) {
	return Core.write_port->fcall((CL_INT)this, (CL_INT)data, len);
}

CL_INT PortObject::puts(const char *data) {
	return Core.write_port->fcall((CL_INT)this, (CL_INT)data, strlen(data));
}

CL_INT PortObject::puts(const char *data, CL_INT sz) {
	return Core.write_port->fcall((CL_INT)this, (CL_INT)data, sz);
}

void PortObject::put(CL_INT n) {
	char sprintfbuf[32];
	CL_INT len = snprintf(sprintfbuf,32,"%d",n);
	Core.write_port->fcall((CL_INT)this, (CL_INT)sprintfbuf, len);
}

static CL_INT fixdot(char* sprintfbuf) {
	CL_INT i = 0, len = strlen(sprintfbuf);
 	for(;i < len;i++) {
 		if(sprintfbuf[i] == '.') return 1;
 		if(sprintfbuf[i] == 'e') return 0;
 	}
 	strcat(sprintfbuf,".0");
 	return 0;
}

void PortObject::put(double x) {
	char sprintfbuf[256];
	snprintf(sprintfbuf,256,"%f",x);
	if(fixdot(sprintfbuf)) {
		while (sprintfbuf[strlen(sprintfbuf) - 1] == '0')
			sprintfbuf[strlen(sprintfbuf) - 1] = 0;
		if(sprintfbuf[strlen(sprintfbuf) - 1] == '.')
			sprintfbuf[strlen(sprintfbuf)] = '0';
	}
	if(strcmp(sprintfbuf,"-0.0") == 0)
		Core.write_port->fcall((CL_INT)this, (CL_INT)"0.0", 3);
	else
		Core.write_port->fcall((CL_INT)this, (CL_INT)sprintfbuf, strlen(sprintfbuf));
}

// v3.2.54   pretty-print
void PortObject::prettyp(double x) {
	char sprintfbuf[256];
	double y = (CL_INT)floor(x);
	if (x > CLMINFLOAT && x < CLMAXFLOAT && y == x)
		sprintf(sprintfbuf,"%#.1f",x);
	else if (y == 0.0 || ( (x - y) / y > 1e-5 && DECIMAL(x)))
		sprintf(sprintfbuf,"%g",x);               // easy print is OK
	else sprintf(sprintfbuf,"%0.10g",x);          // v3.2.54
	fixdot(sprintfbuf);
	if(strcmp(sprintfbuf,"-0.0") == 0)
		Core.write_port->fcall((CL_INT)this, (CL_INT)"0.0", 3);
	else
		Core.write_port->fcall((CL_INT)this, (CL_INT)sprintfbuf, strlen(sprintfbuf));
};



//<sb> freadline family, useful to parse ports until a condition occurs (e.g. line end)
// one can specify an escape char and a sensitive condition

char *freadline_port(PortObject* po) {
	tuple *res = freadline_port6(po, list::alloc(2, _string_("\n"), _string_("\r\n")), CTRUE, 0);
	return string_v(res->content[1]);
}
char *freadline_port1(PortObject* po, char* sep) {
	tuple *res = freadline_port6(po, list::alloc(1, _string_(sep)), CTRUE, 0);
	return string_v(res->content[1]);
}
char *freadline_port2(PortObject* po, char* sep, ClaireBoolean *sensitive) {
	tuple *res = freadline_port6(po, list::alloc(1, _string_(sep)), sensitive, 0);
	return string_v(res->content[1]);
}
char *freadline_port3(PortObject* po, char* sep, ClaireBoolean *sensitive, ClaireChar *escape) {
	tuple *res = freadline_port6(po, list::alloc(1, _string_(sep)), sensitive, escape);
	return string_v(res->content[1]);
}
tuple *freadline_port4(PortObject* po, bag *seps) {
	return freadline_port6(po, seps, CTRUE, 0);
}
tuple *freadline_port5(PortObject* po, bag *seps, ClaireBoolean *sensitive) {
	return freadline_port6(po, seps, sensitive, 0);
}


struct separator_context {
	CL_INT length;
	CL_INT ischar;
	OID oid;
	char *sep;
};

static CL_INT unsensitive_match(char *travel, CL_INT seplen, char *sep);
static void grow_freadline_buffer(char **travel, char **databuf, CL_INT *buflen, CL_INT n, separator_context *separators);

//<sb> this is the heart of freadline function family
// p is read char by char until a seprator matches
tuple *freadline_port6(PortObject* p, bag *seps, ClaireBoolean *sensitive, ClaireChar *escape) {
	if (Core.eof_port_ask->fcall((CL_INT)p) == (CL_INT)CTRUE) {
		return tuple::alloc(2, _string_(""), _string_(""));
	} else {
		char c = 0, esc = escape ? escape->ascii : 0;
		CL_INT n = 0, matched = 0, i, j;
		CL_INT nseparator = 0;
		OID oid;
		//<sb> we use a local malloc'ed buffer prior to import
		// the resulting string in CLAIRE
		char *databuf = (char*)malloc(256);
		if(databuf == 0) Cerror(61,_string_("freadline @ bag"),0);
		CL_INT buflen = 256;
		separator_context *separators  = new separator_context[seps->length];
		separator_context *separator;
		if(separators == 0) {
			free(databuf);
			Cerror(61,_string_("freadline @ bag"),0);
		}
		//<sb> fill seprators with their length and values
		for(i=1;i <= seps->length;i++) {
			separator = &separators[nseparator];
			oid = seps->content[i];
			separator->oid = oid;
			ClaireClass *own = OWNER(oid);
			if (Kernel._string == own) {
				char *s = string_v(oid);
				CL_INT len = LENGTH_STRING(s);
				if(len > 0) {
					if(escape) {
						CL_INT elen = 0;
						CL_INT k;
						for(k = 0;k < len;k++) {
							if(k < len - 1 && s[k] == esc) k++;
							elen++;
						}
						separator->length = elen;
					} else separator->length = len;
					separator->sep = s;
					separator->ischar = 0;
					nseparator++;
				}
			} else if (Kernel._char == own)  {
				separator->sep = (char*)(OBJECT(ClaireChar, oid)->ascii);
				separator->length = 1; //<sb> 0 length means a char
				separator->ischar = 1;
				nseparator++;
			}
		}
		//<sb> order seprators by length -> ensure that the longest sep is checked 
		// first, for instances if 'b' and 'ab' are specified and both match this ensure
		// that 'ab' is the returned match
		for(i = 0;i < nseparator - 1;i++)
		   for(j = i+1;j < nseparator;j++) {
			 separator_context *separatori = &separators[i];
			 separator_context *separatorj = &separators[j];
			 if(separatorj->length > separatori->length) {
				separator_context dummy;
				memcpy(&dummy, &separators[i], sizeof(separator_context));
				memcpy(&separators[i], &separators[j], sizeof(separator_context));
				memcpy(&separators[j], &dummy, sizeof(separator_context));
			 }
		   }
		//<sb> read the port until a separator matches
		char testchar[1];
		CL_INT N = 0;
		CL_INT seplen;
		CL_INT escapedlast = 0;
		char *sep;
		char *travel = databuf;
		CL_INT isbuffer = p->isa == Core._buffer;
		CL_INT isblob = p->isa == Core._blob;
		//<sb> cache the function pointer of the read method associated with the given port
		fptr3 read_port_cache =
			((fptr3) OBJECT(ClaireFunction, 
				((list *)(p->isa->dispatcher))->content[Core.read_port->dispatcher])->value);
		//<sb> when a buffer or a blob is given as argument we optimize the code by avoid
		// calls to read_port and instead perform direct access on buffer's data
		// this avoid many func calls
		buffer *bo = (buffer*)p;
		blob *b = NULL;
		if (isbuffer) {
			b = bo->pending_r;
			if (b == NULL) {
				fill_read_buffer_buffer1(bo);
				b = bo->pending_r;
			}
		} else if (isblob)
			b = (blob*)p;
		//<sb> check char by char wheither a given separator matches 
		while(1) {
			if (isbuffer) {
				if (b->read_index < b->write_index) {
					c = b->data[b->read_index++];
				} else {
					fill_read_buffer_buffer1(bo);
					if (b->read_index == b->write_index)
						break;
					else c = b->data[b->read_index++];
				}
			} else if (isblob) {
				if (b->read_index < b->write_index) {
					c = b->data[b->read_index++];
				} else break;
			} else if (read_port_cache((CL_INT)p, (CL_INT)&c, 1) == 0) {
				break;
			}
			if (escapedlast) {
				n++;
				if (n == buflen)
					grow_freadline_buffer(&travel, &databuf, &buflen, n, separators);
				*travel++ = c;
				escapedlast = 0;
				N = 0;
				continue;
			}
			N++;
			if(escape == 0 || c != esc) {
				n++;
				if (n == buflen)
					grow_freadline_buffer(&travel, &databuf, &buflen, n, separators);
				*travel++ = c;
				for(i = 0;i < nseparator;i++) {
					separator = &separators[i];
					seplen = separator->length;
					if(separator->ischar) {
						testchar[0] = (char)((CL_INT)separator->sep);
						sep = (char*)testchar;
					} else sep = separator->sep;
					if(N >= seplen) {
						if(sensitive == CTRUE) {
							if (memcmp(travel - seplen, sep, seplen) == 0)
								{matched = 1;
								break; }
						} else {
							//<sb> check case
							if (unsensitive_match(travel, seplen, sep))
								{matched = 1;
								break; }
						}
					}
				}
			} else {
				escapedlast = 1;
			}
			if (matched) break;
		}
		oid = separator->oid;
		delete [] separators;
		char * sres = copy_string1(databuf, matched ? (travel - databuf - seplen) : n);
		free(databuf);
		return tuple::alloc(2, _string_(sres), matched ? oid : _string_(""));
	}
}

void grow_freadline_buffer(char **travel, char **databuf, CL_INT *buflen, CL_INT n, separator_context *separators)
{
	*buflen += 256;
	char *tmp = (char*)realloc(*databuf, *buflen);
	if(tmp == NULL) {
		free(*databuf);
		delete [] separators;
		Cerror(61,_string_("freadline @ bag"),0);
	}
	*databuf = tmp;
	*travel = *databuf + n - 1;
}

CL_INT unsensitive_match(char *travel, CL_INT seplen, char *sep) {
	CL_INT m = 0;
	char* p1 = travel - seplen;
	char* p2 = sep;
	for(;m < seplen;m++) {
		if (*p1 != *p2) {
			if (*p2 >= 'A' && *p2 <= 'Z')
				{if(*p2 + 'a' - 'A' != *p1) break;}
			else if (*p2 >= 'a' && *p2 <= 'z')
				{if(*p2 + 'A' - 'a' != *p1) break;}
			else break;
		}
		p1++; p2++;
	}
	return m == seplen;
}



fd_set readset;
fd_set writeset;
CL_INT fdMaxfd = -1;

/*********************************************************************/
/**    2. Reader general functions                                   */
/*********************************************************************/


// check that a char is not a special char 
ClaireBoolean *alpha_char (ClaireChar *cx)
{unsigned char c = cx->ascii;
 if       (  (c == 255)  || (c == '\n') ||
             (c == '}') || (c == ')')  || (c == ']') ||
             (c == '{') || (c == '(')  || (c == '[') ||
             (c == 9  ) || (c == ';')  || (c == '|') ||
             (c == ',') || (c == '/')  || (c == ':') ||
             (c == '@') || (c == '.')  || (c == '\r') ||
             (c == '<') || (c == '>')  || (c == ' ') )
           //  (c == '+') || (c == '-')  || (c == '*') )
 return CTRUE;
 else return CFALSE;}


CL_INT reading_a_string = 0;
CL_INT read_escaped = 0;

//<sb> how to read    0{o|O}XXX...    X in (0 .. 7)
OID read_octal_port(PortObject* p) {
	double res = (double)(p->firstc - '0'); //<sb> the first digit is already read for octal numbers!
	CL_INT t = 0;
	p->getNext();
	while(p->firstc >= '0' && p->firstc <= '7') {
		res = 8.0 * res + (double)(p->firstc - '0');
		t++;
		if(t == 3 && reading_a_string) break;
		p->getNext();
		if((reading_a_string && p->firstc == '\\') ||
			(p->firstc <= '0' && p->firstc >= '7'))
			{p->getNext();break;}
	}
	if (res >= CLMINFLOAT && res <= CLMAXFLOAT) return ((CL_INT) res);     // rean an int
    else return _float_(res);}

//<sb> how to read   0{x|X|h|H}XXX...   X in (0 .. 9) U (A .. F) U (a .. f)
OID read_hexa_port(PortObject* p) {
	double res = 0.0;
	CL_INT t = 0;
	p->getNext();
	while((p->firstc >= '0' && p->firstc <= '9') ||
			(p->firstc >= 'A' && p->firstc <= 'F') ||
			(p->firstc >= 'a' && p->firstc <= 'f')) {
		if(p->firstc >= '0' && p->firstc <= '9')
			res = 16.0 * res + (double)(p->firstc - '0');
		else if(p->firstc >= 'A' && p->firstc <= 'F')
			res = 16.0 * res + (double)(10 + p->firstc - 'A');
		else res = 16.0 * res + (double)(10 + p->firstc - 'a');
		p->getNext();
		t++;
		if(t == 2 && reading_a_string) break;
	}
	if (res >= CLMINFLOAT && res <= CLMAXFLOAT) return ((CL_INT) res);     // rean an int
    else return _float_(res);}

//<sb> how to read   0{d|D}XXX...   X in (0 .. 9)
OID read_dec_port(PortObject* p) {
	double res = 0.0;
	CL_INT t = 0;
	p->getNext();
	while((p->firstc >= '0' && p->firstc <= '9')) {
		res = 10.0 * res + (double)(p->firstc - '0');
		p->getNext();
		t++;
		if(t == 3 && reading_a_string) break;
	}
	if (res >= CLMINFLOAT && res <= CLMAXFLOAT) return ((CL_INT) res);     // rean an int
    else return _float_(res); }

//<sb> how to read   0{b|B}XXX...   X in {0,1}
OID read_bin_port(PortObject* p) {
	double res = 0.0;
	CL_INT t = 0;
	p->getNext();
	while(p->firstc >= '0' && p->firstc <= '1') {
		res = 2.0 * res + (double)(p->firstc - '0');
		p->getNext();
		t++;
		if(t == 8 && reading_a_string) break;
	}
	if (res >= CLMINFLOAT && res <= CLMAXFLOAT) return ((CL_INT) res);     // rean an int
    else return _float_(res);}

// reading a string in a port - assumes that " was read and that the string will end with "
char *read_string_port(PortObject* p) {
 char cur = p->firstc;
 ClEnv->bufferStart();
 while (cur != '"')
    {if (cur == ((char)255)) break;
     if (cur == '\\') {
     	p->getNext();
        cur = p->firstc;
        if (cur == 't') cur = '\t';
        else if (cur == 'r') cur = '\r';
        else if (cur == 'n') cur = '\n';
        //else if (cur == '0') cur = '\0';
		else if (cur == '\\') cur = '\\';
		else if (cur == '"') cur = '"';
        //<sb> add support for escaped number in various basis 
		else if ((cur >= '0' && cur <= '7') ||
				cur == 'x' || cur == 'X' ||
				cur == 'h' || cur == 'H' || 
				cur == 'd' || cur == 'D' || 
				cur == 'b' || cur == 'B')
          { read_escaped = 1;
		    reading_a_string = 1;
            OID num = read_number_port(p);
            read_escaped = 0;
		    reading_a_string = 0;
            //p->getNext();
            if(INTEGERP(num) == 0) Cerror(35,_integer_(num),p->firstc);
            ClEnv->pushChar((char)num);
            cur = p->firstc;
            continue; }}
	 ClEnv->pushChar(cur);
     cur = p->getNext();}
 p->getNext();
 char *s = ClEnv->bufferCopy();
 return s;}


// reading an ident, which is either a symbol, a number or a special case
OID read_ident_port(PortObject* p) {
 CL_INT cur = p->firstc;
 p->getNext();
 if ((cur == '-') && (('0' <= p->firstc) && ('9' >= p->firstc)))
    {OID value = read_number_port(p);
      if (INTEGERP(value)) return (- value);
      else return _float_( -(float_v(value))); }
 else if (cur == '\\' && 
 		((p->firstc >= '0' && p->firstc <= '7') ||
 		p->firstc == 'x' || p->firstc == 'X' ||
 		p->firstc == 'h' || p->firstc == 'H' ||
 		p->firstc == 'd' || p->firstc == 'D' ||
 		p->firstc == 'b' || p->firstc == 'B'))
 	 {read_escaped = 1;
 	  OID value = read_number_port(p);
 	  read_escaped = 0;
      if (INTEGERP(value)) return value;
      else return _float_(float_v(value)); }
 else if (cur == '\'') //<sb> reading a char
   { cur = p->firstc;
	 p->getNext();
     //<sb> add support for escaped chars
     if (cur == '\\') {
     	if ('\'' == p->firstc) {
     		p->getNext();
     		if (p->firstc != '\'') Cerror(35,cur,p->firstc);
     		p->getNext();
            return _oid_(char_I_integer('\''));
       } else {
		   cur = p->firstc;
		   if (cur == 't') {cur = '\t';p->getNext();}
		   else if (cur == '\\') {cur = '\\';p->getNext();}
		   else if (cur == 'r') {cur = '\r';p->getNext();}
		   else if (cur == '"') {cur = '"';p->getNext();}
		   else if (cur == 'n') {cur = '\n';p->getNext();} 
		   //<sb> add support for escaped number in various basis 
			else if (cur >= '0' && cur <= '7') {
				CL_INT oct = (CL_INT)(cur - '0');
				p->getNext();
				cur = p->firstc;
				if (cur >= '0' && cur <= '7') {
					oct = 8 * oct + (CL_INT)(cur - '0');
					p->getNext();
					cur = p->firstc;
				}
				if (cur >= '0' && cur <= '7') {
					oct = 8 * oct + (CL_INT)(cur - '0');
					p->getNext();
					cur = p->firstc;
				}
				if (cur != '\'') Cerror(35,cur,p->firstc);
				p->getNext();
				return _oid_(char_I_integer((unsigned char)oct));
			} else if(cur == 'x' || cur == 'X' || cur == 'h' || cur == 'H' ||
				cur == 'd' || cur == 'D' || cur == 'b' || cur == 'B')
			  { read_escaped = 1;
				reading_a_string = 1;
				OID num = read_number_port(p);
				if (ClEnv->verbose = -1)
				reading_a_string = 0;
				read_escaped = 0;
				if(INTEGERP(num) == 0)
					Cerror(35,_integer_(num),p->firstc);
				cur = (CL_INT)num;
				p->getNext();
				return _oid_(char_I_integer((unsigned char)cur));}
			else {Cerror(35,cur,p->firstc);}}
		}
	 if ('\'' != p->firstc) {Cerror(35,cur,p->firstc); return 1;}
     else {p->getNext();
           return _oid_(char_I_integer((unsigned char)cur));}}
 else return  read_thing_port(p,ClEnv->module_I,char_I_integer((unsigned char)cur),ClEnv->module_I); }

// read a number, either a float or an integer
// changed in v3.0.70 to read long floats
//<sb> v3.3.15 read octal/hexa/binary as well (0x... 0o... 0b...)
OID read_number_port(PortObject* p) {
 double res = (double) (p->firstc - '0');
 if(read_escaped) { //<sb> add support for number in various basis 
 	if(p->firstc >= '0' && p->firstc <= '7') return read_octal_port(p);
 	else if(p->firstc == 'x' || p->firstc == 'X') return read_hexa_port(p);
 	else if(p->firstc == 'd' || p->firstc == 'D') return read_dec_port(p);
 	else if(p->firstc == 'h' || p->firstc == 'H') return read_hexa_port(p);
 	else if(p->firstc == 'b' || p->firstc == 'B') return read_bin_port(p); }
 p->getNext();
 while(p->firstc >= '0' && p->firstc <= '9')
     {res = (res * 10.0) + (double) (p->firstc - '0');
      p->getNext();}
 if ((p->firstc != '.') && (p->firstc != 'e') && (p->firstc != 'E'))
    {if (res >= CLMINFLOAT && res <= CLMAXFLOAT)
    	{CL_INT d = (CL_INT)res;
    	return (OID)d;}     // rean an int
     else return _float_(res);}                                         // overflow -> float (v3.0.70)
 else {double possible = res;                  // read a float (saw a e or a .)
         if (p->firstc == '.')                 // read the decimal part
           {res = 10.0;
            p->getNext();
            while ((p->firstc >= '0') && (p->firstc <= '9'))
               {possible = possible + (((double) (p->firstc - '0')) / res);
                res = res * 10.0;
                p->getNext();}}
         if (p->firstc == 'e' || p->firstc == 'E')                 // read the exponent part
            {char signe = '+';
             res = 0.0;
             p->getNext();
             if (p->firstc == '-') {signe = '-'; p->getNext();}
             if (p->firstc == '+') p->getNext();
             while ((p->firstc >= '0') && (p->firstc <= '9'))
                {res = (res * 10.0) + (double) (p->firstc - '0');
                 p->getNext();}
             if (signe == '-') possible = possible / pow(10.0,  res);
             else  possible = possible * pow(10.0,  res);}
          return _float_(possible);}}

// reading a true identifier (symbol or object)
//   app is the module in which the stream is read, cur is the current
//   character and n is the reader object
// def = NULL means that we read a private name
OID read_thing_port(PortObject* p, module *app, ClaireChar *cx, module *def) {
 char cur = (char) cx->ascii;
 if (cur == '"')
    return _oid_(symbol::make(GC_STRING(read_string_port(p)),app,def));      // strings
 if ((cur == '/') && (p->firstc == '*'))                                           // C-style comments
    {while (((cur != '*') || (p->firstc != '/')) && cur != ((char)255))
		{cur = p->firstc; p->getNext();}
     p->getNext();
     return _string_("");}
 ClEnv->bufferStart();
 if ((cur == '/') && (p->firstc == '/'))                                           // C++ comment
    {p->getNext();
     while (((cur = p->firstc) != '\n') && (cur != ((char)255)))
         {ClEnv->pushChar(cur); p->getNext();}
	return _string_(ClEnv->bufferCopy());}
 ClEnv->pushChar(cur);
 if ((cur == ':') && (p->firstc == ':')) {ClEnv->pushChar(cur);p->getNext();}       // :: trap
 else if ((cur == '.') && (p->firstc == '.')) {ClEnv->pushChar(cur);p->getNext();}       // .. trap
 else if ((cur == '<') && (p->firstc == '<')) {ClEnv->pushChar(cur);p->getNext();}       // .. trap
 else if ((cur == '-' || cur == '=' || cur == '>') && (p->firstc == '>'))	//<sb> add check for eof
       {ClEnv->pushChar('>');p->getNext();}       // -> trap for *>
 cur = p->firstc;
 while (alpha_char(char_I_integer(((unsigned char)cur))) == CFALSE)
       {ClEnv->pushChar((char) cur); cur = p->getNext();}
 if (cur == '/')                                                                   // read a qualified ident
    {OID s = (app->getSymbol(ClEnv->buffer,claire.it))->getValue();
     ClaireChar *cx = char_I_integer((unsigned char)p->getNext());
       p->getNext();
       if (s == _oid_(Kernel.PRIVATE)) return read_thing_port(p,app,cx,NULL);
       else {if (OWNER(s) == Core._global_variable) { //<sb> support module alias
				s = OBJECT(global_variable, s)->value;
				if (OWNER(s) != Kernel._module)
					Cerror(29,s,0);
			} else if (OWNER(s) !=  Kernel._module)
                Cerror(29,s,0);
             return read_thing_port(p,OBJECT(module,s),cx,def);}}
 else {symbol *s = app->getSymbol(ClEnv->buffer,def);                               // create the symbol
         if ((app == ClEnv->module_I) || (s->definition != NULL))
           return s->getValue();
         else {Cerror(30,_oid_(s),0); return 1;}}}

/**********************************************************************/
/**    3. Characters                                                  */
/**********************************************************************/

// initialization: create all chars (this is called once ClaireChar is properly defined)
void ClaireChar::init()
{CL_INT i;
  for (i = 0; i < 256; i++) //<sb> was 512 due to signed char (now unsigned)
    {ClaireChar *c = (ClaireChar *) ClAlloc->makeAny(4);
       c->isa = Kernel._char;
       c->ascii = (unsigned char)i;
       ClRes->ascii[i] = c;
       }}

// princ a char / CL_INT / float
//<sb> prints in a readable form for ascii in (0 .. 31) U (127 .. 159)
// ex: ascii code 1 is printed '\001'
void princ_char(ClaireChar *cx) {
	ClEnv->cout->put((char)cx->ascii);
}


void print_char(ClaireChar *cx) {
	char tmp = (char)cx->ascii;
	PortObject *pout = ClEnv->cout;
	pout->put('\'');
	if(tmp == '"') pout->put('"');
	else internal_print_string(&tmp,1);
	pout->put('\'');
}


// print the name of an object as a C identifier
//<sb> made c_princ_char relying on c_princ_string
// and add a temp buffer such to decrease the amount of
// write calls
void c_princ_string(char *ss)
{ char buf[1024];
  char *travel = buf;
  for (; *ss != '\0'; ss++) {
  	char *tmp;
	CL_INT n = 1;
  	switch (*ss) {
       case '.':  tmp = "_dot"; n = 4; break;
       case '/':  tmp = "_7"; n = 2; break;
       case '\\': tmp = "_backslash"; n = 10; break;
       case '&':  tmp = "_and"; n = 4; break;
       case '-':  tmp = "_dash"; n = 5; break;
       case '+':  tmp = "_plus"; n = 5; break;
       case '%':  tmp = "_Z"; n = 2; break;
       case '*':  tmp = "_star"; n = 5; break;
       case '?':  tmp = "_ask"; n = 4; break;
       case '!':  tmp = "_I"; n = 2; break;
       case '<':  tmp = "_inf"; n = 4; break;
       case '>':  tmp = "_sup"; n = 4; break;
       case '=':  tmp = "_equal"; n = 6; break;
       case ',':  tmp = "_comma"; n = 6; break;
       case '^':  tmp = "_exp"; n = 4; break;
       case '@':  tmp = "_at"; n = 3; break;
       case '~':  tmp = "_tilda"; n = 6; break;
       case ']':  tmp = "_brack"; n = 6; break;
       case ':':  tmp = "L_"; n = 2; break;
       case '\'': tmp = "_prime"; n = 6; break;
       case '$': tmp = "_dollar"; n = 7; break;       // v3.2.14
       default: tmp = ss;break;
     }
	 memcpy(travel, tmp, n);
	 travel += n;
	 if (travel - buf > 1000) {
	 	Core.write_port->fcall((CL_INT)ClEnv->cout, (CL_INT)buf, travel - buf);
	 	travel = buf;
	 }
  }
  if(travel > buf)
	  Core.write_port->fcall((CL_INT)ClEnv->cout, (CL_INT)buf, travel - buf);
}
  	
// special consversion (language dependent)
//<sb> now rely on c_princ_string
void c_princ_c(ClaireChar *cx)
{ char c[2] = {0,0};
  c[0] = (char)cx->ascii;
  c_princ_string(c);
}


// print a symbol (the name of an object) as a C identifier */
void c_princ_symbol(symbol *s)
{  if (s->module_I != claire.it)
      {c_princ_symbol(s->module_I->name);
       ClEnv->cout->put('_');}
   c_princ_string(s->name);}

CL_INT integer_I_char(ClaireChar *c)
{return c->ascii;}

/*********************************************************************/
/**    4. System interface (miscellaneous)                           */
/*********************************************************************/

// set the time counter
void time_set_void()
{ if (++ClEnv->tIndex > 9) Cerror(26,ClEnv->tIndex,0);
  msec(ClEnv->tStack[ClEnv->tIndex]);}

// shows the elaped time
CL_INT time_get_void()
{CL_INT now;
   msec(now);
   if (ClEnv->tIndex <= 0) Cerror(26,ClEnv->tIndex,0);
   return (now - ClEnv->tStack[ClEnv->tIndex--]);}

CL_INT time_read_void()
{CL_INT now;
   msec(now);
   if (ClEnv->tIndex <= 0) Cerror(26,ClEnv->tIndex,0);
   return (now - ClEnv->tStack[ClEnv->tIndex]);}

void time_show_void()
{OID now;
   msec(now);
   if (ClEnv->tIndex <= 0) Cerror(26,ClEnv->tIndex,0);
   princ_string("Counter["); princ_integer(ClEnv->tIndex);
   princ_string("] Elapsed time: "); princ_integer(now - ClEnv->tStack[ClEnv->tIndex--]);
   princ_string("ms. \n");}

// pass a command string to the host system
CL_INT claire_shell(char *s)
{ return CL_system(s); }


// profiler methods (ClaireProfile -> KernelProfile)
PRcount *PRstart(PRcount *p)
{CL_INT x = 0;
  if (p->rdepth == 0) {p->rstart = clock();}  // v3.2.58 : more precision ....
  p->rdepth++; p->rnum++;
  return p;}

// fixed bugs in v3.0.53 thanks to FXJ
void PRend(PRcount *p)
{CL_INT x = 0;
  p->rdepth--;
  if (p->rdepth == 0) {p->rtime += (clock() - p->rstart);}}

void PRloop(PRcount *p)
{p->rloop++;}


