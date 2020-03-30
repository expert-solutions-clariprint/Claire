


#ifndef _LOADER_H_
#define _LOADER_H_

#include "claire.h"
#include "kernel.h"
#include <Core.h>
#include <Language.h>
#include <Reader.h>

#define OUTMAXBUF     1024   // outpout port buffer size
#define OUTMAXBUFEX   1124   // outpout port buffer size

// forward
class Claire;
class ClaireStrPortIn;
class CPClaireOut;



// reading from a string   -> to check for correctnedd
// we could use an istrstream if the documentation was readily available
class ClaireStrPortIn: public ClairePort // implementation in "clconsole.cpp"
{
public:

    char *buffer;
    CL_INT index;
	
	ClaireStrPortIn() : index(0), buffer(NULL) {};
    virtual void debugSee();
    virtual char get();
    virtual void unget(CL_INT c);
};


// output to a string : we implement our own for better control but it could change ...
class ClaireStrPortOut: public ClairePort // implementation in "clconsole.cpp"
{
public:

	Claire *mParent;                              // parent CConsole
    char buffer[OUTMAXBUFEX];                        // out buffer larger than flush limit
    CL_INT index;                                     // current index in buffer
	
	ClaireStrPortOut() : index(0) {};
    virtual void debugSee();
    virtual void put(char c) ;
    virtual void put(CL_INT n);
    virtual void put(double x);
	void Flush();
};



class Claire 
{

	friend class ClaireStrPortOut;
	friend void TopLevelFailure(Claire *cl);
private:
	
	FileObject *pIn;
	FileObject *pOut;
	ClaireStrPortIn *mIn;                          // port object for inputs
	ClaireStrPortOut *mOut;                        // port object for ouputs	
	bool mError;                                   // last command has error?

public:

	Claire();                         
    virtual ~Claire() {};
	
	bool Read(char* cmdline);                      // validate request 
	bool IsValid(const char* cmdline);

private:

	void RedirectToMe();                           // Redirect ports to me
	void TopLevel();							   // include the claire toplevel as a member function
	void SetCommand(char *cmdline);                // initialize input buffer

protected:

	virtual void Flush(const char *result)         // a virtual output callback for customized flush 
		{printf(result);};     
	virtual void End() {};                         // a virtual output callback for customized end of command
	virtual void Failure() {};                     // a virtual notification for toplevel failure (Reset has been called first)

};

#endif