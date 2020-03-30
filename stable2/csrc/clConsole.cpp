/***********************************************************************/
/**  microCLAIRE                                       Yves Caseau     */
/**  clConsole.cpp.in                                                  */
/**  Copyright (C) 1994-99 Yves Caseau. All Rights Reserved.           */
/**  cf claire.h                                                       */
/***********************************************************************/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>
#include <Language.h>
#include <Reader.h>

#ifdef CLPC
	#include <conio.h>
	#include <direct.h>
	#include <wincon.h>
	#define vsnprintf _vsnprintf
#endif

#ifndef HAVE_HISTEDIT_H
#undef CLEL
#endif

#ifdef CLEL
#ifdef HAVE_HISTEDIT_H
extern "C" { 
#include <histedit.h>
}
#endif
#else
#ifdef HAVE_HISTEDIT_H
#undef HAVE_HISTEDIT_H
#endif
#endif

void finterpreter_insert_text(char* t);

/*********************************************************************/
/** Table of contents                                                */
/**                                                                  */
/**    introduction (xl)                                             */
/**                                                                  */
/**    0. encoded output (xl)                                        */
/**    1. color support (xl)                                         */
/**    2. editline support (xl)                                      */
/**    3. memory - allocate/free claire (xl)                         */
/**    4. C++ main                                                   */
/**    5. system functions API                                       */
/**    6. toplevel                                                   */
/**    7. inspection & debug                                         */
/**    8. consprint                                                  */
/**                                                                  */
/*********************************************************************/


/*********************************************************************/
/**    introduction (xl)                                             */
/*********************************************************************/


//<sb> This file contains console interface specifics for claire.
// It contains the entry point for the program (main)
// from witch we allocate claire memory according to memory
// params specified on the command line by '-s i j'



/*********************************************************************/
/**    2. editline support                                           */
/*********************************************************************/


#ifdef HAVE_HISTEDIT_H


//<sb> realine port class inherits from the claire port class (Kernel.h)
// manage stdin & command history
// you should have readline installed as a shared library (or a framework cf OS X)
// on your system
// this class defines static functions for readline 
// callbacks (readline & completion)
class CELPort : public device {
private:	
	char *clhistory; // file name for claire command history
	char *clshellhistory; // file name for shell command history
	char shprompt[MAXPATHLEN]; // shell prompt (updated according to the current working directory)
	char *input; // we store the string returned by ::readline
	int shell; // are we currently in shell mode? claire: 0, shell: 1
	int historyStorageError;	// remember history storage pb to avoid multiple warning messages
	History* h;
public:
	
	char *line; // trimed version of input 
	static CELPort *singleton; // one and only one instances
	EditLine* el;
	int multiline;
	int eol;
	
	static char* get_prompt(EditLine* el) {
		if (CELPort::singleton->multiline) return "";
		return CELPort::singleton->shell ? CELPort::singleton->shprompt : get_prompt_void2();
	}
	
	static unsigned char complete(EditLine* el, CL_INT ch) {
		avoid_signal_caching = 0;
		LineInfo *l = (LineInfo*)el_line(el);
		if(l->buffer == l->lastchar) {
			if(!CELPort::singleton->multiline) {
				CELPort::singleton->shell = !CELPort::singleton->shell;
				GC_BIND;
				completion_reset_void();
				GC_UNBIND;
				el_reset(CELPort::singleton->el);
				CELPort::singleton->togglehistory();
			} else finterpreter_insert_text("\t");
		} else {
			GC_BIND;
			//<sb> see complete.cl in Reader
			if(CELPort::singleton->shell == 0) claire_complete_void();
			else shell_complete_void();
			GC_UNBIND;
		}
		avoid_signal_caching = 1;
		return CC_REDISPLAY;
	}
	
	void init() {
		CELPort::singleton = this;
		input = 0; shell = 0; // start in claire mode 
		multiline = 0; eol = 0;
		historyStorageError = 0;
		allochistoryname(".clhistory", &clhistory);
		allochistoryname(".clshellhistory", &clshellhistory);
		el = el_init("claire",stdin,stdout,stderr);
		el_set(el, EL_EDITOR, "emacs");
		el_set(el, EL_SIGNAL, 1);
		el_set(el, EL_ADDFN, "complete","complete", CELPort::complete);
		el_set(el, EL_BIND, "^I", "complete", NULL);
		el_set(el, EL_PROMPT, get_prompt);
		HistEvent ev;
		h = history_init();
		history(h, &ev, H_SETSIZE, 200);
		history(h, &ev, H_SETUNIQUE, 1);
		el_set(el, EL_HIST, history, h);
		history(h, &ev, H_LOAD, clhistory); 
	}
	
	~CELPort() {
		delete [] clhistory;
		delete [] clshellhistory; 
	    el_end(el);
		history_end(h);
	}
	
	void allochistoryname(char *filename, char** history) {
		char *home = getenv("CLAIRE_HISTORY");
		if(!home) home = getenv("HOME");
		if(!home) home = ".";
		*history = new char[strlen(home) + strlen(filename) + 2];
		strcpy(*history, home); strcat(*history, "/");
		strcat(*history, filename); }
	
	void togglehistory() { // shell & claire have its own history
		HistEvent ev;
		history(h, &ev, H_CLEAR);
		history(h, &ev, H_LOAD, shell ? clshellhistory : clhistory); 
	}
		
	void readline(char* prompt = 0);

	void flush() {
		multiline = 0;
		eol = 0;
		firstc = ' ';
		line = NULL;}

	char get() {
		if (line == NULL) readline();
		char c = *line;
		line++;
		if(eol == 1 || c == '\0') { // we are at the end of the string
		 	eol++;
		 	multiline = 1;
		 	return '\n'; }
		if(eol) { // such we can handle a new query
		 	eol = 0;
		 	readline();
		 	return get(); } // for witch we request the next char
		 return c; }	// return current line char
    
	void unget(int c)
     {line--;}; //<sb> wcl
	
    void debugSee() { printf("I am an editline input port!\n"); }; };

//<sb> static constant prompt for multiligne claire commands
// we keep blue
CELPort *CELPort::singleton = 0;
	
char *pwd_void1() {
#ifdef CLPC
	static char tmp[MAX_PATH + 1];
	if(GetCurrentDirectory(MAX_PATH,tmp)==0)
#else
	static char tmp[MAXPATHLEN + 1];
	if(getcwd(tmp, MAXPATHLEN) == NULL)
#endif	
		tmp[0] = 0;
	return tmp;
}

int lastevent = 0;
HistEvent lev;

//<sb> realine callback
// here we set the prompt according to the current
// mode (either claire or shell), we save the command
// history each time we get a new command
// note that shell & claire have their own history
void CELPort::readline(char* prompt /* = 0 */) {
	int len;
	do { do { // loop until non empty line
			// set shell prompt according to the working directory
			char* tmp = pwd_void1();
			char* z = tmp + strlen(tmp);
			while(z > tmp && *z != '/' && *z != '\\') z--;
			sprintf(shprompt, "[%s]> ", (strlen(z) > 1 ? z + 1 : tmp));
			while (avoid_signal_handling == 0 && n_pending_signal > 0)
				kernel_pop_signal();
			GC_BIND;
			avoid_signal_caching = 1;
			line = input = (char*)el_gets(el,&len);
			if (line == NULL)
				{line = "";
				return;}
			avoid_signal_caching = 0;
			while(*line == '\t' || *line == ' ') line++;
			GC_UNBIND;
		} while(*line == '\0' || *line == '\n');

		history(h, &lev, multiline ? H_APPEND : H_ENTER, line);
		history(h, &lev, H_SAVE, shell ? clshellhistory : clhistory); 
		
		if(shell) { color(30,0);
			if(strcmp(line, "q\n") == 0) CL_exit(0); // handle 'q' in shell mode
			else if(strcmp(line, "cd\n")==0 || strncmp(line, "cd ",3)==0 || strncmp(line, "cd\t",3)==0) {
				char *path = line + 2; // handle 'cd' command and change manualy the working directory
				while(*path == '\t' || *path == ' ') path++;
				if(!((*path=='\0' && chdir("/")==0) || chdir(path)==0))
					fprintf(stdout,"error: invalid directory '%s'\n", path);}
			else system(line); } // let shell execute the command
		else firstc = ' '; // restore the blank first char	
	} while (shell);
}

#endif

void finterpreter_insert_text(char* t) {
#ifdef HAVE_HISTEDIT_H
	el_insertstr(CELPort::singleton->el, t);
#endif
}


void finterpreter_delete_text(int s,int e) {
#ifdef HAVE_HISTEDIT_H
	el_deletestr(CELPort::singleton->el, e - s);
#endif
}

void finterpreter_reset_state() {
#ifdef HAVE_HISTEDIT_H
	el_reset(CELPort::singleton->el);
#endif
}

int finterpreter_get_cursor_position() {
#ifdef HAVE_HISTEDIT_H
	LineInfo *l = (LineInfo*)el_line(CELPort::singleton->el);
	return 1 + l->cursor - l->buffer;
#else
	return 0;
#endif
}


char *finterpreter_get_text() {
#ifdef HAVE_HISTEDIT_H
	LineInfo *l = (LineInfo*)el_line(CELPort::singleton->el);
	return copy_string1((char*)l->buffer, 1 + l->lastchar - l->buffer);
#else
	return 0;
#endif
}

void finterpreter_display_list(list* matches) {
#ifdef HAVE_HISTEDIT_H
	OID gc_local;
	printf("\n");
	ITERATE(i);
	for (START(matches); NEXT(i);) {
		printf("%s\n",string_v(i));
	}
#endif
}


/*********************************************************************/
/**    4. C++ main                                                   */
/*********************************************************************/


#ifdef HAVE_HISTEDIT_H

void flush_elport(CELPort *p) {
	CELPort::singleton->flush();
}

ClaireBoolean *eof_elport(CELPort *p) {
	return CFALSE;
}


int read_elport(CELPort *p, char *data, CL_INT len) {
	int i = 0;
	for(;i < len; i++)
		((char*)data)[i] = p->get();
	return len;
}
#endif

extern CL_IMPORT CL_INT NOEL;

void claire_started() {
#ifdef HAVE_HISTEDIT_H
	if (NOEL == 0) {
		ClaireClass* _elport = ClaireClass::make("elport", Core._device, claire.it);
		Core.read_port->addMethod(list::domain(3,_elport,Core._char_star,Kernel._integer), Kernel._integer,
			SAFE_RESULT,_function_(read_elport,"read_elport"));
		Core.eof_port_ask->addMethod(list::domain(1,_elport), Kernel._boolean,
			SAFE_RESULT,_function_(eof_elport,"eof_elport"));
		Core.flush_port->addMethod(list::domain(1,_elport), Kernel._void,
			SAFE_RESULT,_function_(flush_elport,"flush_elport"));
		CELPort *p = (CELPort*)ClAlloc->makeStatic(sizeof(CELPort) / sizeof(CL_INT) + 2);
    GC_PUSH(p);
		p->init();
		p->isa = _elport;
		p->freeme_ask = CFALSE;
		p->closed_ask = CFALSE;
		p->firstc = ' ';
		p->filters = list::empty(Core._filter);
		Kernel._freeable_object->instances->addFast(_oid_(p));
		PortObject *input = buffer_I_port1(p, 1);
		Core.cl_stdin->value = _oid_(input);
		Reader.reader->fromp = input;
	}
#endif
}

// this is our main function
int main(int argc, char *argv[]) {
  set_claire_started(claire_started);
  interpreter_insert_text = finterpreter_insert_text;
  interpreter_delete_text = finterpreter_delete_text;
  interpreter_reset_state = finterpreter_reset_state;
  interpreter_get_text = finterpreter_get_text;
  interpreter_get_cursor_position = finterpreter_get_cursor_position;
  interpreter_display_list = finterpreter_display_list;
	if (startClaire(argc, argv) == 0)
		return 1;
	return 0; }

