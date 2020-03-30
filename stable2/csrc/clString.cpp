/***********************************************************************/
/**   microCLAIRE                                       Yves Caseau    */
/**   clString.cpp                                                     */
/**  Copyright (C) 1998-2003 Yves Caseau. All Rights Reserved.         */
/**  cf claire.h                                                       */
/***********************************************************************/

#include <claire.h>
#include <Kernel.h>
#include <marie.h>
#include <Core.h>


// this file contains the C++ code for the imported objects, mostly strings
// (and the associated symbols, although they are not imported) but also
// integers and floats. Note the double implementation for floats

/*********************************************************************/
/** Contents                                                         */
/**    0. Color support (xl)                                         */
/**    1. Strings                                                    */
/**    2. Modules                                                    */
/**    3. Symbol                                                     */
/**    4. integer                                                    */
/**    5. floats                                                     */
/*********************************************************************/

/**********************************************************************/
/**    0: Color support                                               */
/**********************************************************************/

#define PUTS(p, s, n) Core.write_port->fcall((CL_INT)p, (CL_INT)s, n)

// 0 -> disable stratup baner & "bye..." string
CL_INT LOGO = 1;
// 1 -> colors supported
// 2 -> html colors
CL_INT COLOR = 0;

CL_INT current_color = 30;
CL_INT current_bold = 0;

//<sb> if s match m we return true
// and we offset s with the length of m
// note: the given string may be modified!
CL_INT match(char** s, char* m) {
        char* d = *s; char* p = m;
        while(*d && *m) {
        		if(*d != *m) return 0;
                d++;m++;
                if(*m) continue; break; }
        if(*m) return 0;
        *s += m - p; return 1; }

#define IS(sc) match(&format,sc)
void Ctracef(char* format, ...) {
	PortObject* p = ClEnv->cout;
	ClEnv->cout = get_device_port1(ClEnv->ctrace);
    va_list argList; va_start(argList, format);
        char buf[10]; strcpy(buf,"%xxxxxxxx");
        char *formater = (char*)buf; char* fmt;
        while(*format) {
           if(!IS("%")) {
           		char tmp[] = "c";
           		*tmp = *format++;
           		princ_string(tmp); }
           else if(IS("%")) princ_string("%");
           else { fmt = formater + 1; // resolve formater
                  do {*fmt++ = *format;}
                  while(!(IS("d")||IS("f")||IS("i")||IS("u")||IS("x")||IS("X")||
                          IS("s")||IS("c")||IS("g")||IS("e")||IS("E")||IS("o")));
                  *fmt = '\0'; char buffer[2024];
                  sprintf(buffer, formater, va_arg(argList, void*));
                  princ_string(buffer); } }
        ClEnv->cout = p;
}


#define mytput(b,n) { if (terminal_ask_port1(p) == CTRUE) PUTS(p,(char*)b, n); }


//<sb> change current terminal color
void color(CL_INT c, CL_INT bold) {
	PortObject *p = ClEnv->cout;
	if(bold) bold = 1;
	if(current_color == c && current_bold == bold)
		return;
	if(COLOR == 1) {
		#ifndef CLPC
		char buf[16];
		CL_INT n;
		mytput("\033[m", 3);
		if(c != current_color && c != 30) {
			current_color = c;
			n = sprintf(buf,"\033[%dm", c);
			mytput(buf,n);
		}
		if(bold) {
			current_bold = bold;
			n = sprintf(buf,"\033[1m");
			mytput(buf,n);
		}
		#else
		static HANDLE pcConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		static CL_INT black = -1;
		static CL_INT bkground = -1;
		if(black == -1) {
			WORD dw; DWORD nr;COORD xy;xy.X = xy.Y = 0;
			ReadConsoleOutputAttribute(pcConsole,&dw,1,xy,&nr);
			black = (dw&FOREGROUND_RED)|(dw&FOREGROUND_GREEN)|(dw&FOREGROUND_BLUE)|(dw&FOREGROUND_INTENSITY); 
			bkground = (dw&BACKGROUND_RED)|(dw&BACKGROUND_GREEN)|(dw&BACKGROUND_BLUE)|(dw&BACKGROUND_INTENSITY); }
		switch(c) { case 30: c = black; break; // map unices/pc colors
			case 31: c = FOREGROUND_RED|FOREGROUND_INTENSITY; break;
			case 32: c = FOREGROUND_GREEN; break;
			case 33: c = FOREGROUND_GREEN|FOREGROUND_RED; break;
			case 34: c = FOREGROUND_BLUE|FOREGROUND_INTENSITY; break;
			case 35: c = FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY; break;
			case 36: c = FOREGROUND_GREEN|FOREGROUND_BLUE; break;
			case 37: c = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY; break; }
		SetConsoleTextAttribute(pcConsole, c|bkground);
		#endif
	} else if(COLOR == 2) {
		PortObject *pout = ClEnv->cout;
		if(current_bold && bold == 0) PUTS(pout,"</b>",4);
		if (current_color != c && c == 30)
			PUTS(pout,"</font>",7);
		switch(c) {
			case 31:
				PUTS(pout,"<font color=red>",16);
				break;
			case 32:
				PUTS(pout,"<font color=green>",18);
				break;
			case 34:
				PUTS(pout,"<font color=blue>",17);
				break;
			}
		if(bold && current_bold == 0) PUTS(pout,"<b>",3);
		
	}
	current_color = c;
	current_bold = bold;
}

CL_INT color_integer(CL_INT c) {
	avoid_signal_handling++;
	CL_INT old = COLOR;
	if(old == 2) color(30,0);
	COLOR = c;
	avoid_signal_handling--;
	return old;
}

CL_INT color_void() {return COLOR;}

/*********************************************************************/
/**    1: String functions                                           */
/*********************************************************************/

// --- there are all API functions since string are imported char* -----

CL_INT length_string(char* s) {return LENGTH_STRING(s);}

// make a local copy of a string
char *copy_string(char *s)
{	CL_INT len = LENGTH_STRING(s);
	if(len <= 0) return ClAlloc->makeString(0);
	char *a = ClAlloc->makeString(len);
	memcpy(a,s,len);
	return a; }

char *copy_string1(char *s, CL_INT len)
{  	if(len <= 0) return ClAlloc->makeString(0);
	char *a = ClAlloc->makeString(len);
	memcpy(a,s,len);
	return a; }


// equality on strings
ClaireBoolean *equal_string(register char *s1, register char *s2)
{ CL_INT l1 = LENGTH_STRING(s1);
  CL_INT l2 = LENGTH_STRING(s2);
  if (l1 != l2) return CFALSE;
  return memcmp(s1,s2,l1) == 0 ? CTRUE : CFALSE; }


void color_princ_string2(char *s, CL_INT i, CL_INT j)
{ if (i < 1) i = 1; if (j < 1) j = 1;
  CL_INT len = LENGTH_STRING(s);
  PortObject *pout = ClEnv->cout;
  if(len == 0 || pout == 0) return;
  if (j > len) j = len; if (i > len) i = len;
  char *end = s + j;
  char *anchor = 0;
  s = s + i - 1;
  CL_INT bold = 0;
   while(s < end) {
   if(*s == '`') {
   	if(anchor && s - anchor) {
   		if(COLOR == 2) {
    		while(anchor < s) {
    			if(*anchor == '\n') PUTS(pout,"<br>\n",5);
      			else if(*anchor == '>') PUTS(pout,"&gt;",4);
      			else if(*anchor == '<') PUTS(pout,"&lt;",4);
      			else if(*anchor == '&') PUTS(pout,"&amp;",5);
      			else if(*anchor == ' ') PUTS(pout,"&nbsp;",6);
      			else if(*anchor == '"') PUTS(pout,"&quot;",6);
      			else PUTS(pout,anchor,1);
      			anchor++;
    		}
    	} else PUTS(pout,anchor, s - anchor);
   		anchor = 0;
   	}
    bold = 0;
    CL_INT f = 0;
    char* tag = s;
    if (++s == end) {pout->put('`');break;}
    if(*s == '`') {bold = 1; if (++s == end) {pout->put('`');pout->put('`');break;}}
    {if(*s == 'R' && ++s != end && // RED
     *s == 'E' && ++s != end &&
      *s == 'D') {f = 1;if(COLOR > 0) color(31, bold);}
    else if(*s == 'B' && ++s != end) { // BLACK
     if(*s == 'L' && ++s != end) {
      if(*s == 'A') {
       if(++s < end && *s == 'C' && ++s != end &&
        *s == 'K') {f = 1;if(COLOR > 0) color(30, bold);} }
      else if(*s == 'U' && ++s != end && // BLUE
       *s == 'E') {f = 1;if(COLOR > 0) color(34, bold);} }}
    else if(*s == 'C' && ++s != end && // CYAN
     *s == 'Y' && ++s != end &&
      *s == 'A' && ++s != end &&
       *s == 'N') {f = 1;if(COLOR > 0) color(36, bold);}
    else if(*s == 'W' && ++s != end && // WHITE
     *s == 'H' && ++s != end &&
      *s == 'I' && ++s != end &&
       *s == 'T' && ++s != end &&
        *s == 'E') {f = 1;if(COLOR > 0) color(37, bold);}
    else if(*s == 'G' && ++s != end && // GREEN
     *s == 'R' && ++s != end &&
      *s == 'E' && ++s != end &&
       *s == 'E' && ++s != end &&
        *s == 'N') {f = 1;if(COLOR > 0) color(32, bold);}
    else if(*s == 'Y' && ++s != end && // YELLOW
     *s == 'E' && ++s != end &&
      *s == 'L' && ++s != end &&
       *s == 'L' && ++s != end &&
        *s == 'O' && ++s != end &&
         *s == 'W') {f = 1;if(COLOR > 0) color(33, bold);}
    else if(*s == 'M' && ++s != end && // MAGENTA
     *s == 'A' && ++s != end &&
      *s == 'G' && ++s != end &&
       *s == 'E' && ++s != end &&
        *s == 'N' && ++s != end &&
         *s == 'T' && ++s != end &&
          *s == 'A') {f = 1;if(COLOR > 0) color(35, bold);}}
    if(f == 0) {
    	if(COLOR == 2) {
    		while(tag <= s) {
    			if(*tag == '\n') PUTS(pout,"<br>\n",5);
      			else if(*tag == '>') PUTS(pout,"&gt;",4);
      			else if(*tag == '<') PUTS(pout,"&lt;",4);
      			else if(*tag == '&') PUTS(pout,"&amp;",5);
      			else if(*tag == ' ') PUTS(pout,"&nbsp;",6);
      			else if(*tag == '"') PUTS(pout,"&quot;",6);
      			else PUTS(pout,tag,1);
      			tag++;
    		}
    	} else PUTS(pout,tag, s - tag + 1);
    	s++;
    } else {s++; while(s < end && (*s == ' ' || *s == '\t')) s++; }
  } else {
  	if(anchor == 0) anchor = s;
  	s++;
  }}
  if(anchor && s - anchor) {
	if(COLOR == 2) {
		while(anchor < s) {
			if(*anchor == '\n') PUTS(pout,"<br>\n",5);
			else if(*anchor == '>') PUTS(pout,"&gt;",4);
			else if(*anchor == '<') PUTS(pout,"&lt;",4);
			else if(*anchor == '&') PUTS(pout,"&amp;",5);
      		else if(*anchor == ' ') PUTS(pout,"&nbsp;",6);
      		else if(*anchor == '"') PUTS(pout,"&quot;",6);
			else pout->put(*anchor);
			anchor++;
		}
	} else PUTS(pout,anchor, s - anchor);
	anchor = 0; }}

void color_princ_string1(char *s) {
	color_princ_string2(s,1,LENGTH_STRING(s));}

void princ_string1(char *s, CL_INT i, CL_INT j) {
  if(COLOR == 2) {color_princ_string2(s,i,j); return;}
  CL_INT len = LENGTH_STRING(s);
  if(len == 0) return;
  if (j > len) j = len;
  if (i > len) i = len;
  Core.write_port->fcall((CL_INT)ClEnv->cout, (CL_INT)(s+i-1), j-i+1);
}

void princ_string(char *s) {
  if(COLOR == 2) {color_princ_string1(s); return;}
 Core.write_port->fcall((CL_INT)ClEnv->cout, (CL_INT)s, LENGTH_STRING(s));
}

//<sb> add the ability to output in hexa
char* hex_I_integer(CL_INT i) {
	char buf[10] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
	CL_INT j = 0;
	sprintf(buf, "%8X", i);
	while(j < 8 && buf[j] == ' ') {buf[j] = '0';j++;}
	return copy_string(buf);
}

//<sb> add the ability to output in binary
char* bin_I_integer(CL_INT i) {
	char buf[32];
	CL_INT j;
	for(j = 32-2;j >= 0; j--)
       buf[32 - 2 - j] = (i>>j) & 01 ?'1':'0';
	buf[31] = 0;
	return copy_string(buf);
}

#define PRINT_FMT(p,s, n) {if(COLOR > 0) color(C ? 34 : 32,0); PUTS(p,s,n); if(COLOR > 0) color(30,0);}

void internal_print_string(char* ss, CL_INT len) { 
	CL_INT i;
	CL_INT C = 0;
	PortObject *pout = ClEnv->cout;
	for (i=0; i < len; i++) {
		C = 1 - C;
		unsigned char c = ss[i];
	  	//if(c < 0) c = c + 256;
		if (c == '"') PRINT_FMT(pout,"\\\"",2)
		else if (c == '\\') PRINT_FMT(pout,"\\\\",2)
		else if (c == '\n') PRINT_FMT(pout,"\\n",2)
		else if (c == '\t') PRINT_FMT(pout,"\\t",2)
		else if (c == '\r') PRINT_FMT(pout,"\\r",2)
		else if (COLOR == 2 && c == '<') PUTS(pout,"&lt;",4);
		else if (COLOR == 2 && c == '>') PUTS(pout,"&gt;",4);
		else if (COLOR == 2 && c == '&') PUTS(pout,"&amp;",5);
		else if (c == '\0') {
			if(COLOR > 0) color(C ? 34 : 32,0);
			PUTS(pout,"\\0",2);
			if(i < len - 1 && (ss[i+1] >= '0' && ss[i+1] <= '7'))
				PUTS(pout,"\\",1);
			if(COLOR > 0) color(30,0);
		} else if(c <= (unsigned char)31 || c >= (unsigned char)127) {
			if(COLOR > 0) color(C ? 34 : 32,0);
			char buf[4]; sprintf(buf,"%03o",(CL_INT)c);
			PUTS(pout,"\\",1);
			PUTS(pout,buf,3);
			if(COLOR > 0) color(30,0);
		} else PUTS(pout,&c,1);}}

// print a string with the "" (what you see is what you read)
//<sb> prints in a readable form for ascii in (0 .. 31) U (127 .. 159)
// ex: the string of length 1 where integer!(s[1]) = 1 is printed "\001"
void self_print_string(char *ss) {
	PortObject *pout = ClEnv->cout;
	CL_INT len = LENGTH_STRING(ss); //<sb> buffer
	if(COLOR == 1) {
		color(34,0);
		PUTS(pout,"\"", 1);
		color(30,0);
	} else if(COLOR == 2) {
		PUTS(pout,"<font color=blue>\"</font><font color=black>",43);
	} else PUTS(pout,"\"", 1);
 	internal_print_string(ss,len);
	if(COLOR == 1) {
		color(34,0);
		PUTS(pout,"\"", 1);
		color(30,0);
	} else if(COLOR == 2) {
		PUTS(pout,"</font><font color=blue>\"</font>",32);
	} else PUTS(pout,"\"", 1);
}

// concatenate two strings
char *append_string(char *ss1, char *ss2)
{ CL_INT i;
  CL_INT l1 = LENGTH_STRING(ss1);
  CL_INT l2 = LENGTH_STRING(ss2);
  char* a = ClAlloc->makeString(l1 + l2);
  if(l1) memcpy(a,ss1,l1);
  if(l2) memcpy(a+l1,ss2,l2);
  return a;}

// finds the integer value
CL_INT integer_I_string(char *s)
{ return strtol(s,NULL,10);}

// create a substring from a string
//<sb> add support for negative index that
// are accounted from the end of the string
char *substring_string(char *ss, CL_INT n, CL_INT m)
{ CL_INT l = LENGTH_STRING(ss);
  if(n < -l) n = -l;
  if(n < 0) n = l + 1 + n;
  if(m < 0) m = l + 1 + m;
  if(m > l) m = l;
  if (n < 1 || n > l || m < 1) return "";
  CL_INT len = 1 + m - n;
  char* a = ClAlloc->makeString(len);
  if(len) memcpy(a, ss + n - 1, len);
  return a; }


// look for th eposition of the CHAR c in s
CL_INT get_string(char *ss, ClaireChar *c)
{ OID i;
  CL_INT len = LENGTH_STRING(ss);
  char c2 = (char) c->ascii;
  for (i=0; i < len; i++) if (ss[i] == c2) return(i+1);
  return 0;}

// compare two strings
ClaireBoolean *_less_string(char *s1, char *s2)
{CL_INT i;
 CL_INT l1 = LENGTH_STRING(s1); //<sb> buffer
 CL_INT l2 = LENGTH_STRING(s2); 
 for (i = 0; i < l1; i++)
    {if (i >= l2) return CFALSE;
    else if (s1[i] < s2[i]) return(CTRUE);
     else if (s1[i] > s2[i]) return (CFALSE);}           // include s2[i] = '0' !!!
 return CTRUE;}                                          // v3.1.12 ????

// test is a string is included into another
CL_INT included_string(char *s1, char *s2,ClaireBoolean *p)
{CL_INT c,i,j;
  	CL_INT l1 = LENGTH_STRING(s1);
  	CL_INT l2 = LENGTH_STRING(s2);
  	for (i = 0; i < l1; i++)
    for (j = 0;; j++)
      { c = s1[i+j] - s2[j];
        if ((c == 0) || ((p == CTRUE) &&
             (((c == 32) && ((s2[j] >= 'A') && (s2[j] <= 'Z'))) ||
              ((c == -32) && ((s2[j] >= 'a') && (s2[j] <= 'z'))))))
           {if (j+1 >= l2) return i+1;}
        else break;}
  return 0;}

// get the CHAR at the i-th place in s
ClaireChar *nth_string(char *ss, CL_INT n)
{ CL_INT len = LENGTH_STRING(ss);
  if(n < 1 || n > len) Cerror(11,n,_string_(ss));
  return char_I_integer((unsigned char) ss[n-1]); }     // v3.2.44  //<sb> buffer

// set the char at the i_th place in s
void nth_set_string (char *ss, CL_INT n, ClaireChar *c)
{ CL_INT len = LENGTH_STRING(ss);     // v3.2.44  //<sb> buffer
  if(n < 1 || n > len) Cerror(11,n,_string_(ss));
  ss[n-1] = (char) c->ascii; }


// shrinks a string by placing the '\0' marker
char *shrink_string(char *ss, CL_INT n) {
	if (n < 0) n = 0; //<sb> prevent negative length...
	if (n <= LENGTH_STRING(ss))
		{ if(CLMEM(ss)) Cmemory[BUFFER_LEN_IDX(ss)] = n; //<sb> buffer
		ss[n] = '\0';
		}
 	else Cerror(11,n,_string_(ss));
 return ss; }

// the old internal function
// watch out: TODO use claire ?
OID value_string(char *name)
{return value_module(ClEnv->module_I,name);}

// the new internal function
OID value_module(module *m, char *name)
{symbol *s = m->lookup(name);
   if (s == NULL) return CNULL;
   else return s->value;}

// new: access to the symbol the new internal function
OID get_symbol_module(module *m, char *name)
{symbol *s = m->lookup(name);
   if (s == NULL) return CNULL;
   else return _oid_(s);}

// new: return the current date
char *date_I_integer(CL_INT i)
{struct tm *newtime;
 time_t aclock;
 time(&aclock);
 newtime = localtime(&aclock);
 if(newtime == 0) Cerror(70,0,0);
 return copy_string(asctime(newtime)); }

// for upward compatibility
char* getenv_string(char *s)
{char *s2 = getenv(s);
 if (s2 == NULL) s2 = "";
 return s2;}
 
/*********************************************************************/
/**    2: Modules                                                    */
/*********************************************************************/

// ------------- member functions for modules ---------------------------------------

// constructor: create a module from the name and the father in the hierarchy
module *module::make(char *s, module *sup)
{module *m = (module *) ClAlloc->makeAny(13); //<sb>
  m->isa = Kernel._module;
  m->name = symbol::make(s,claire.it,claire.it);
  m->name->value = _oid_(m);
  m->part_of = sup;
  m->status = 0;
  m->version = NULL; //<sb>
  m->external = NULL; //<sb>
  m->evaluate = NULL; //<sb>
  m->source = NULL; //<sb>
  m->comment = s; //<sb>
  m->parts = list::empty(Kernel._module);
  m->verbose = Kernel.ctrue;
  return m;}

// hash function.
CL_UNSIGNED module::hash(register char *s)
{CL_UNSIGNED val;
  CL_INT len = LENGTH_STRING(s); CL_INT i = 0;
  for (val= (CL_INT) this; i < len; (i++,s++))
      val = *s + 31 * val;
  return val & ClAlloc->hashMask;}

// lookup: check if a string in a given module is represented by a symbol (returns NULL
// if no symbol is found - does NOT create a new symbol
// this method embodies the strategy for looking in upper modules (namespace inheritance)
symbol *module::lookup(char *nm)
{CL_INT i = hash(nm);
   while ((ClRes->sTable[i] != NULL) &&
          ((this != ClRes->sTable[i]->module_I) ||
           (equal_string(nm,ClRes->sTable[i]->name) == CFALSE))) i++;
   if (i == ClAlloc->maxHash) Cerror(12,0,0);
   symbol *cur = ClRes->sTable[i];
   if (cur != NULL || this == claire.it) return cur;   // v3.2.38 - Thanks to FXJ !
   else return part_of->lookup(nm); }


// Get a symbol (even if none is there => create it) in the module with the given name,
// this is a combination of lookup + symbol::make(...)
// notice that we do not inherit junk (undefined) but rather create a new symbol
symbol *module::getSymbol(char *nm, module *def)
{symbol *cur = lookup(nm);
  if ((cur != NULL) &&
      ((cur->value != CNULL) || (cur->module_I == this) || (cur == Kernel.unknownName)))
     return cur;
  else return symbol::make(GC_STRING(copy_string(nm)),this,def); }   // v3.2.50

// create the module associated to a namespace (used by the compiler)
// assumes the existence of the claire module
void NameSpace::initModule(char *nom, module *father)
{it = module::make(nom,father);}

// similar but also fills the key slots for the module (compiler method)
// new status (0:default, 1:start, 2 compiled, 3:c+loaded, 4:c+l+trace, 5:c+delayed)
void NameSpace::initModule(char *nom, module *father, list* usage, char *dir, list *files)
{it = module::make(nom,father);
 it->uses = usage;                 // other modules that are used
 it->source = dir;               // directory where the sources can be found
 it->made_of = files;
 it->comment = nom;
 it->status = 3;
  Kernel._module->instances->addFast(_oid_(it));
 father->parts->addFast(_oid_(it));   // manage the inverse
}

// --- API functions for modules ---------------------------------------------------

/* open a module x with module identifier index */
void begin_module (module *x)
{ ((list *) ClEnv->moduleStack)->addFast(_oid_(ClEnv->module_I));
  ClEnv->module_I = x;}

/* close an application */
void end_module (module *x)
{CL_INT n = ((bag *) ClEnv->moduleStack)->length;
  if (n == 0) ClEnv->module_I = claire.it;
  else {ClEnv->module_I = OBJECT(module,(*((bag *) ClEnv->moduleStack))[n]);
        delete_at_list(((list *) ClEnv->moduleStack),n);}}



/*********************************************************************/
/**    3. Symbols                                                    */
/*********************************************************************/

// to remove
void symbolDebug(symbol *s)
{CL_INT i = s->module_I->hash(s->name);
 symbol *test = ClRes->sTable[i];
 if (test != s) {
 	printf("_____________________________________________\n");
 	printf("  symbol debug s = %x\n",s);
 	printf("  string is [%s] (%d)\n  module:%s\n",s->name, LENGTH_STRING(s->name), s->module_I->comment);
 	printf("  position is %d\n",i);
 	printf("ClRes->sTable[%d] -> %s/%s\n", i, test->module_I->name->name, test->name);
 	printf("!!!!!! problem with the table !!!!!!\n");
 	printf("_____________________________________________\n");	}}
 


// -------------- member functions --------------------------------------------

// create a claire symbol from an internal C string and a status, represented by
// def, which is NULL for private symbols and the definition (owner) for other symbols
symbol *symbol::make(char *name, module *ns, module *def)
{CL_INT i = ns->hash(name);
   while ((ClRes->sTable[i] != NULL) &&
          ((ns != ClRes->sTable[i]->module_I) ||
           (equal_string(name,ClRes->sTable[i]->name) == CFALSE))) i++;
   if (i >= ClAlloc->maxHash)
   		Cerror(12,0,0);
   if (ClRes->sTable[i] == NULL)
      {symbol *s = (symbol *) ClAlloc->makeAny(5);
       s->isa = Kernel._symbol;
       s->name = name;
       s->module_I = ns;
       s->definition = def;                  // def = NULL means private
       s->value = CNULL;
       ClRes->sTable[i] = s;}
   return ClRes->sTable[i];}

// read the value bound to a given symbol s. We create an unbound
//   symbol object if necessary
OID symbol::getValue()
{ if (value == CNULL && this != Kernel.unknownName)
     {unbound_symbol *o = (unbound_symbol *) Kernel._unbound_symbol->instantiate();
      o->name = this;
      return _oid_(o);}
  else return value;}


// --------------- API functions ---------------------------------------------

// create a symbol in the current module
symbol *symbol_I_string(char *s,module *m)
{return symbol::make(s,m,ClEnv->module_I);}

// writes the value of a symbol
OID put_symbol(symbol *s, OID x)
{s->value = x;
 return x;}

OID get_symbol(symbol *s) {return s->value;} //<sb> was {return ((s->value == CNULL) ? CNULL : s->value);}

// concatenate two symbols, or a symbol and a string or a symbol and an integer
// the result is a symbol in the module of the first symbol
symbol *append_symbol(symbol *s1, OID s2)
{ OID i;
  char *ss1 = s1->name;
  CL_INT len = LENGTH_STRING(ss1);
  ClEnv->bufferStart();
  for (i = 0; i < len; i++) ClEnv->pushChar(ss1[i]);
  if INTEGERP(s2) ClEnv->pushInteger(s2);
  else {if (OWNER(s2) == Kernel._symbol) ss1 = OBJECT(symbol,s2)->name;
        else if (OWNER(s2) == Kernel._string) ss1 = string_v(s2);
        else ss1 = "";
        CL_INT len = LENGTH_STRING(ss1);
        for (i = 0; i < len; i++) ClEnv->pushChar(ss1[i]);}
  return symbol::make(GC_STRING(ClEnv->bufferCopy()),s1->module_I,s1->definition); }

// print a symbol with its application name
void princ_symbol(symbol *s)
{ if ((s->module_I != claire.it) && (s->module_I != ClEnv->module_I))
     {princ_symbol(s->module_I->name); ClEnv->cout->put('/');}
  princ_string(s->name); }

// find the module where the object is defined
module *defined_symbol (symbol *s)
{ if (s->definition != NULL) return s->definition; else return s->module_I;}

module *module_I_symbol (symbol *s) {return s->module_I;}

char *string_I_symbol(symbol *s)
{return s->name;}

// create a new name
symbol *gensym_string (char *s)
{ ClEnv->bufferStart();
  CL_INT len = LENGTH_STRING(s);
  while(len--) ClEnv->pushChar(*s++);
  //for (; *s != '\0'; s++) ClEnv->pushChar(*s);
  ClEnv->pushChar('0' + ((char) ((ClEnv->gensym % 10000) / 1000)));
  ClEnv->pushChar('0' + ((char) ((ClEnv->gensym % 1000) / 100)));
  ClEnv->pushChar('0' + ((char) ((ClEnv->gensym % 100) / 10)));
  ClEnv->pushChar('0' + ((char) (ClEnv->gensym % 10)));
  ClEnv->gensym++;
  return claire.it->getSymbol(ClEnv->buffer,claire.it);}

// useful to represent a symbol with an integer
CL_INT integer_I_symbol (symbol *s)
{ CL_INT i = s->module_I->hash(s->name);
   while ((ClRes->sTable[i] != NULL) &&
          ((s->module_I != ClRes->sTable[i]->module_I) ||
           (equal_string(s->name,ClRes->sTable[i]->name) == CFALSE))) i++;
   return i;}


/*********************************************************************/
/**    4. integer & float API functions                              */
/*********************************************************************/

// useful upper and lower bound to check overflow
#ifdef __LP64__
double CLMAXFLOAT = 2.30583e+18;
double CLMINFLOAT = -2.30583e+18;
#else
double CLMAXFLOAT = 1073741823.0;              // v3.3.12
double CLMINFLOAT = -1073741822.0;
#endif

/*
void princ_integer(CL_INT i) {ClEnv->cout->put(i);}


// arithmetic functions
int ch_sign(CL_INT n)
{ return (-n) ;}

int _7_integer(CL_INT n, CL_INT m)
{ if (m == 0) Cerror(20,n,0); return (n / m);}

int mod_integer(CL_INT n, CL_INT m)
{ if (m == 0) Cerror(20,n,0); return (n % m);}

// v3.3.16: use float exponentiation and check overflow
int _exp_integer(CL_INT n, CL_INT m)
{double a = (double) n, b = (double) m,  c = pow(a,b);
  if (c < CLMINFLOAT || c > CLMAXFLOAT) Cerror(40,n,m);
  return (CL_INT) c; }

// return a power of 2
int exp2_integer(CL_INT n)
{if ((n >= 0) && (n <= 31)) return (1 << n);
 else Cerror(19,0,0); return 1;}
*/

// translate a integer into a char - v3.2.44 : supports encoding both on (-255 -- 256) or (0 -- 511)
ClaireChar *char_I_integer(CL_INT n)
{if ((n < -1) || (n > 255)) Cerror(21,n,0);
 return ClRes->ascii[(unsigned char)n];}

// create a new string
char *string_I_integer (CL_INT n)
{ ClEnv->bufferStart();
  ClEnv->pushInteger(n);
  return ClEnv->bufferCopy();}

// allocate a list with n member equal to m */
char *make_string_integer(CL_INT n, ClaireChar *c)
{ if (n < 0) Cerror(22,n,0);
  char *s = ClAlloc->makeString(n);
  if(n) memset(s,c->ascii,n);
  return s; }

//<sb> allocate a string without an initializer
char *make_string_integer1(CL_INT n)
{ if (n < 0) Cerror(22,n,0);
  char *s = ClAlloc->makeString(n);
  return s; }

// create a string from a list (v3.0.44) - should have been there from day one !
// TODO: trap the error nicely
char *make_string_list(list *l)
{if (l->of != Kernel._char) Cerror(22,0,0);
 CL_INT i,n = l->length;
 char *s = ClAlloc->makeString(n);
 for (i = 0; i < n; i++) s[i] = (char) OBJECT(ClaireChar,(*(l))[i + 1])->ascii;
 return s; }

CL_INT times_integer(CL_INT n, CL_INT m)
{double a = (double) n, b = (double) m,  c = a * b;
  if (c < CLMINFLOAT || c > CLMAXFLOAT) Cerror(40,n,m);
  return n * m; }

// use C random generator
// v3.3.18: support long integer (> 16 bits) - v3.3.20 : use ALi's ideas to simplify

// v3.3.24 makes sure that rand() returns a > 0 number on all platforms
// v3.3.26 is even stronger, following Sylvain's suggestion
#define C_RAND() (rand() & 0x00007FFF)
#define C_RANDMAX (RAND_MAX & 0x0007FFF)

void random_I_void() {
	srand(time(NULL));
}

CL_INT random_integer(CL_INT n)
{if (n <= 1) return 0;
 else if (n <= 1000) return (C_RAND() % n);
 else if (n <= 30000) return ((C_RAND() * 16384 + (C_RAND() % 16383)) % n);
 else {double ratio = (double) n / (double) (C_RANDMAX + 1);
       double draw = (double) C_RAND() + ((double) C_RAND() / (double) C_RANDMAX);
       //printf("%g * %g = %g\n",draw,ratio, draw * ratio);
       return (CL_INT)floor(draw * ratio);}}

// print
void princ_int(CL_INT n) {ClEnv->cout->put(n);}

/*********************************************************************/
/**    5. floats                                                     */
/*********************************************************************/

// all API functions are doubled:
// op_float(...) returns a double  [float parameters are doubles]
// op_float_(...) returns an OID   [float parameters are OID]

/*
// makes an integer into a float
OID to_float_ (CL_INT n) {return _float_((double) n);}
double to_float (CL_INT n) {return  ((double) n);}

// create a  claire integer from a claire float
int integer_I_float_(OID n) {return integer_I_float(float_v(n));}
int integer_I_float(double n)
{ if (n < CLMINFLOAT || n > CLMAXFLOAT) Cerror(39,_float_(n),0);
  return _integer_((CL_INT) floor(n));}                         // v3.3

// the classical order comparisons for two float
ClaireBoolean *_inf_float(double n,double m)
{ if (n < m) return CTRUE;  else return CFALSE;}

ClaireBoolean *_inf_equal_float(double n,double m)
{ if (n <= m) return CTRUE;  else return CFALSE;}

ClaireBoolean *_sup_float(double n,double m)
{ if (n > m) return CTRUE;  else return CFALSE;}

ClaireBoolean *_sup_equal_float(double n,double m)
{ if (n >= m) return CTRUE;  else return CFALSE;}

ClaireBoolean *_inf_float_(OID n, OID m)
{ if (float_v(n) < float_v(m)) return CTRUE;  else return CFALSE;}

ClaireBoolean *_inf_equal_float_(OID n, OID m)
{ if (float_v(n) <= float_v(m)) return CTRUE;  else return CFALSE;}

ClaireBoolean *_sup_float_(OID n, OID m)
{ if (float_v(n) > float_v(m)) return CTRUE;  else return CFALSE;}

ClaireBoolean *_sup_equal_float_(OID n, OID m)
{ if (float_v(n) >= float_v(m)) return CTRUE;  else return CFALSE;}
*/

// printing
void princ_float(double x) {ClEnv->cout->prettyp(x);}            // v3.2.54
void princ_float_(OID x) {ClEnv->cout->prettyp(float_v(x));}     // v3.2.54

void print_float(double x) {ClEnv->cout->put(x);}            // v3.2.54
void print_float_(OID x) {ClEnv->cout->put(float_v(x));}     // v3.2.54


