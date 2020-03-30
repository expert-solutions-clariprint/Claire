
#include "loader.h"
#include <string>


#define DLLEXPORT   __declspec(dllexport) __stdcall 



extern CL_INT startClaire(int, int);
extern CL_INT freeClaire();


class Loader; // forward


/**************************************************************/
/* globals                                                    */
/**************************************************************/


char cl_obuffer[100000]; // should be enought?
Loader *loader = NULL;
int bFailure;

FILE* f;

/**************************************************************/
/* Loader object                                            */
/**************************************************************/

class Loader : public Claire
{
public:
	Loader() : Claire() {};
	virtual void Flush(const char *buf);
	virtual void Failure(); 
};

void Loader::Flush(const char *buf)
{
	strncat(cl_obuffer,buf,strlen(buf));
}

void Loader::Failure() 
{
	bFailure = 1;
} 

/**************************************************************/
/* export                                                     */
/**************************************************************/


#define LOG(s) if(f) { fprintf(f,s);fflush(f); }
#define LOGS(s,a) if(f) { fprintf(f,s,a);fflush(f); }
#define LOGSS(s,a,b) if(f) { fprintf(f,s,a,b);fflush(f); }


#ifdef __cplusplus
extern "C" {
#endif

	int DLLEXPORT get_infodll(char* ibuffer,char **obuffer) 
	{		
		bFailure = 0;		
		int res;
		cl_obuffer[0] = '\0';
		LOGS("   *** read ***\n%s\n\n",ibuffer)
		res = loader->Read(ibuffer);
		*obuffer = cl_obuffer;
		if(bFailure) 
		{
			LOG("   !!! failure !!!\n\n\n")
			return -1;
		}
		LOGS("   *** result ***\n%s\n\n\n",*obuffer)
		return res;
	} 

	int DLLEXPORT IsValid(char* ibuffer,char** out) 
	{		
		cl_obuffer[0] = '\0';
		bool res = loader->IsValid(ibuffer);
		*out = cl_obuffer;
		return res;
	}

	int  DLLEXPORT main_dll(int i,int j,const char* file) 
	{
		f = NULL;
		if(file)
			f = fopen(file,"w");
		LOGSS("*** claire start (%d,%d) ***\n\n\n",i,j)
		if(!startClaire(i,j))
		{
			freeClaire();
			return 0;
		}
		loader = new Loader();
		return (loader != 0);
	}


	int  DLLEXPORT C_kill_claire() 
	{		 
		LOG("*** claire killed ***\n\n\n")
		freeClaire();
		if(loader) delete loader;
		loader = 0;		 
		return 0;
	} 
	
	int  DLLEXPORT loader_version() 
	{		 
		return 2;
	}   

#ifdef __cplusplus
}
#endif



void interpreter_insert_text(char* t) {
}


void interpreter_delete_text(int s,int e) {
}
void interpreter_reset_state() {
}
int self_print() {
	return 0;
}
char *interpreter_get_text() {
	return 0;
}
void interpreter_display_list(list* matches) {
}
     