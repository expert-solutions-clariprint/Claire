/***********************************************************************/
/**   microCLAIRE XL                                   Sylvain Benilan */
/**   clSystem.cpp                                                     */
/**  Copyright (C) 1998-2004 eXpert soLutions. All Rights Reserved.    */
/***********************************************************************/

#include <claire.h>
#include <Kernel.h>
#include <marie.h>
#include <Core.h>

extern double CLMINFLOAT;
extern double CLMAXFLOAT;

// this file contains the C++ code for system dependent API
// under unix we benefit of configuration (HAVE_XXX definitions)
// under Win32 we may have a specific code...

/*********************************************************************/
/** Contents                                                         */
/**    1. env/cwd/pid                                                */
/**    2. time/date                                                  */
/**    3. files system                                               */
/**    4. process                                                    */
/**    5. uname                                                      */
/**    6. string - case/digit test                                   */
/**    7. string - find/replace                                      */
/**    8. string - explode                                           */
/**    9. string - encoding/decoding (xl)                            */
/**    10. string - base64 encoding/decoding (xl)                    */
/*********************************************************************/



/*********************************************************************/
/**    1. env/cwd/pid                                                */
/*********************************************************************/

//<sb> funny terminal ding!
void ding_void() {putc('\x07',stdout);}

//<sb> setenv wrapper syntax : "var=val"
void setenv_string(char *s) {
#ifdef CLPC
	if(_putenv(s))
#else
#ifdef HAVE_SETENV
	char* v = s;
	while(*v && *v != '=') v++;
	char c = *v;
	char *u = v;
	if(c) v++;
	*u = '\0';
	CL_INT n = setenv(s,v,1);
	*u = c;
	if(n)
#else
	if(putenv(s))
#endif
#endif
	Cerrorno(64,_string_(s),0);
}

//<sb> sets the current working directory
void setcwd_string(char *s) {
#ifdef CLPC
	if (SetCurrentDirectory(s)==0)
#else
	if (chdir(s))
#endif
		Cerrorno(65,_string_(s),0);
}

//<sb> returns the current working directory
char *pwd_void() {
#ifdef CLPC
	char tmp[MAX_PATH + 1];
	if(GetCurrentDirectory(MAX_PATH + 1,tmp)==0)
#else
	char tmp[MAXPATHLEN + 1];
	if(getcwd(tmp, MAXPATHLEN + 1) == NULL)
#endif	
		Cerrorno(66,0,0);
	return copy_string(tmp);
}

#ifndef CLPC
	extern char **environ;
#endif

//<sb> get the amount of environment variable
CL_INT maxenv_void() {
	CL_INT p = -1;
	while(1)
	#ifdef CLPC
		if(_environ[++p] == NULL)
	#else
		if(environ[++p] == NULL)
	#endif
		break;
	return p; // 1 based index
}

//<sb> get the ith environment variable
char *environ_integer(CL_INT i) {
	char *entry;CL_INT p = 0;
	i--; // 1 based index
	if(i < 0) Cerror(67,_integer_((i+1)),0);
	for(;p <= i;p ++)
	#ifdef CLPC
		if(_environ[p] == NULL)
			Cerror(67,_integer_((i+1)),0);
		return copy_string(_environ[i]);
	#else
		if(environ[p] == NULL)
			Cerror(67,_integer_((i+1)),0);
		return copy_string(environ[i]);
	#endif
}

ClaireBoolean *isenv_ask_string(char* v) {
	return getenv(v)?CTRUE:CFALSE;
}

/*********************************************************************/
/**    2. time/date                                                  */
/*********************************************************************/

//<sb> sleep until ms has elapsed
void sleep_integer(CL_INT ms) {
#ifdef CLPC
	Sleep(ms);
#else
	timeval tv;
    tv.tv_sec = ms / 1000;
    tv.tv_usec = 1000 * (ms % 1000);
    select(1, NULL, NULL, NULL, &tv);
#endif
}

class TzSet {
public:
	char claire_tz[64];
	static TzSet single;
	TzSet() {claire_tz[0] = 0;
			setenv_string("TZ=");
			tzset();}
};

TzSet TzSet::single = TzSet();

char *tzset_string(char* tz) {
	CL_INT len = strlen(tz);
	CL_INT olen = strlen(TzSet::single.claire_tz);
	char *old = ClAlloc->makeString(olen);
	GC_STRING(old);
	memcpy(old, TzSet::single.claire_tz, olen+1);
	if (len < 60)
		memcpy(TzSet::single.claire_tz, tz, len+1);
	return old;
}

void claire_tzset(CL_INT local) {
	char tmp[64];
	tmp[0] = 0;
	strcat(tmp,"TZ=");
	if (local)
		strcat(tmp, TzSet::single.claire_tz);
	setenv_string(tmp);
}

double timer_I_void() {
#ifdef CLPC
	struct _timeb tstruct;
	_ftime(&tstruct);
	return 0.001 * (double)tstruct.millitm + (double)tstruct.time;
#elif HAVE_GETTIMEOFDAY
	struct timeval tstruct;
	struct timezone tzone;
	gettimeofday(&tstruct,&tzone);
	return (double)0.000001 * (double)tstruct.tv_usec + (double)tstruct.tv_sec;
#elif HAVE_FTIME
	struct timeb tstruct;
	ftime(&tstruct);
	return 0.001 * (double)tstruct.millitm + (double)tstruct.time;
#else
	time_t t;
	time(&t); //<sb> assume no error will occur
	return (double)t;
#endif
}

OID timer_I_void_() {
	return _float_(timer_I_void());
}


//<sb> from linux manpage: the portable implementation of timegm
time_t my_timegm(struct tm *tm) {
	time_t ret;
	char *tz;
	tz = getenv("TZ");
	//setenv_string("TZ=");
	#ifdef CLPC
	setenv_string("TZ=");
	#else
	unsetenv("TZ");
	#endif	
	tzset();
	ret = mktime(tm);
	if (tz) {
		char tmp[1024];
		tmp[0] = 0;
		strcat(tmp,"TZ=");
		strcat(tmp,tz);
		setenv_string(tmp);
	}
	tzset();
	return ret;
}

//<sb> mktime produced an error, we check that the given date
// isn't during a winter/summer time transition
void mktime_error(struct tm* atm) {
	atm->tm_isdst = -1;
	CL_INT dst_error;
	atm->tm_hour++;
	claire_tzset(1);
	dst_error = mktime(atm) != -1;
	if(dst_error) {
		atm->tm_hour--;
		atm->tm_hour--;
		//dst_error = mktime(atm) != -1;
		dst_error = mktime(atm) != -1;	
	}
	claire_tzset(0);
	if(dst_error) Cerror(90,0,0);
	else Cerror(70,0,0);
}


CL_INT elapsed_float(double t) {
	return _integer_((CL_INT)(1000.0 * (timer_I_void() - t)));
}

CL_INT elapsed_float_(OID t) {
	return elapsed_float(float_v(t));
}

char* setlocale_integer(CL_INT cat, char *loc) {
	CL_INT category;
	if(cat < 0 || cat > 5) Cerror(68,_integer_(cat),0);
	switch(cat) {
		case 0: category = LC_ALL; break;
		case 1: category = LC_COLLATE; break;
		case 2: category = LC_CTYPE; break;
		case 3: category = LC_MONETARY; break;
		case 4: category = LC_TIME; break;
		case 5: category = LC_NUMERIC; break;
	}
	char *res = setlocale(category ,loc);
	if(res == NULL)
		Cerror(69,_integer_(cat),_string_(loc));
	return copy_string(setlocale(category ,loc));
}

char* getlocale_integer(CL_INT cat) {
	CL_INT category;
	if(cat < 0 || cat > 5) Cerror(68,_integer_(cat),0);
	switch(cat) {
		case 0: category = LC_ALL; break;
		case 1: category = LC_COLLATE; break;
		case 2: category = LC_CTYPE; break;
		case 3: category = LC_MONETARY; break;
		case 4: category = LC_TIME; break;
		case 5: category = LC_NUMERIC; break;
	}
	char *res = setlocale(category ,NULL);
	if(res == NULL) Cerror(69,_integer_(cat),_string_(""));
	return copy_string(setlocale(category ,NULL));
}

//<sb> returns the date built with day month year hour minute second
double make_date_integer(CL_INT D, CL_INT M, CL_INT Y, CL_INT h, CL_INT m, CL_INT s) {
	struct tm atm;
	atm.tm_sec = s;
	atm.tm_min = m;
	atm.tm_hour = h;
	atm.tm_mday = D;
	atm.tm_mon = M - 1;     // tm_mon is 0 based
	atm.tm_year = Y - 1900; // tm_year is 1900 based
	atm.tm_isdst = -1; //1 - _daylight; //(dst==CTRUE?1:0);
/*
	char *tm_zone;  // abbreviation of timezone name
	long tm_gmtoff; // offset from UTC in seconds 
*/

	time_t t;
	claire_tzset(1);
	t = mktime(&atm);
	claire_tzset(0);
	if(t == -1) mktime_error(&atm);
	return (double)t;
}

OID make_date_integer_(CL_INT D, CL_INT M, CL_INT Y, CL_INT h, CL_INT m, CL_INT s) {
	return _float_(make_date_integer(D,M,Y,h,m,s));
}

//<sb> date parser
// "XXXX"     -> "XX/XX/y 0:0:00"
// "XXXXXX"   -> "XX/XX/XX 0:0:00"
// "XX/XX"    -> "XX/XX/y 0:0:00"
// "XX/XX/XX" -> "XX/XX/XX 0:0:00"
// "XX/XX/XX" -> "XX/XX/XXXX 0:0:00"
// where y is the current year
double make_date_string(char *self) {
	GC_BIND;
	double Result;
	CL_INT  y = 0;
	CL_INT  m = 0;
	CL_INT  d = 0;
	CL_INT H = 0;
	CL_INT M = 0;
	CL_INT S = 0;
	char sep = ' ';
	char offsetsign = ' ';
	CL_INT offset_val_h = 0;
	CL_INT offset_val_m = 0;
	char tz_name[16];
	char* old_tz = NULL;
	tz_name[0] = '\0';
	char month_name[4];
			
	//xp Sat, 10 Dec 2005 16:31:11 GMT ; RFC 1123, standard Internet Time, always in GMT 
    if (sscanf(self, "%*3[A-z], %d %3[A-z] %d %d:%d:%d GMT", &d, &month_name, &y, &H, &M, &S) == 6) { memcpy(tz_name,"UTC",4); /* XML Schema ISO 8601 extention : named timezone */ }
	//xp Sunday, 06-Nov-94 08:49:37 GMT ; RFC 850, obsoleted by RFC 1036
	else if (sscanf(self, "%*10[A-z], %d-%3s-%d %d:%d:%d GMT", &d, &month_name,&y, &H, &M, &S) == 6) { memcpy(tz_name,"UTC",4); /* XML Schema ISO 8601 extention : named timezone */ }
	//xp Sun Nov 6 08:49:37 1994       ; ANSI C's asctime() format
	else if (sscanf(self, "%*3[A-z] %3[A-z] %d %d:%d:%d %d", &month_name, &d, &H, &M, &S, &y) == 6) { memcpy(tz_name,"UTC",4); /* XML Schema ISO 8601 extention : named timezone */ }
	/* ISO , xp add T seperator support and timezone */
	else if (sscanf(self, "%d-%d-%d%1[T ]%d:%d:%d%1[-+]%2d:%2d", &y, &m, &d,&sep, &H, &M, &S, &offsetsign, &offset_val_h, &offset_val_m) == 10) { month_name[0] = '\0'; /* XML Schema ISO 8601 extention : named timezone */ }
    else if (sscanf(self, "%d-%d-%d%1[T ]%d:%d:%d%1[-+]%2d%2d", &y, &m, &d,&sep, &H, &M, &S, &offsetsign, &offset_val_h, &offset_val_m) == 10) { /* XML Schema ISO 8601 extention : named timezone */ }
	else if (sscanf(self, "%d-%d-%d%1[T ]%d:%d:%d %1[-+]%2d:%2d", &y, &m, &d,&sep, &H, &M, &S, &offsetsign, &offset_val_h, &offset_val_m) == 10) { month_name[0] = '\0'; /* XML Schema ISO 8601 extention : named timezone */ }
    else if (sscanf(self, "%d-%d-%d%1[T ]%d:%d:%d %1[-+]%2d%2d", &y, &m, &d,&sep, &H, &M, &S, &offsetsign, &offset_val_h, &offset_val_m) == 10) { /* XML Schema ISO 8601 extention : named timezone */ }
    else if (sscanf(self, "%d-%d-%d%1[T ]%d:%d:%d%15s", &y, &m, &d,&sep, &H, &M, &S, tz_name ) == 8) { offset_val_h = 0; offset_val_m=0; offsetsign = ' '; /* XML Schema ISO 8601 extention : for named timezone */ }
    else if (sscanf(self, "%d-%d-%d%1[T ]%d:%d:%d", &y, &m, &d, &sep, &H, &M, &S) == 7) {tz_name[0] = '\0'; offset_val_h = 0; offset_val_m=0; offsetsign = ' '; }
    else if (sscanf(self, "%d-%d-%d%1[T ]%d:%d", &y, &m, &d, &sep, &H, &M) == 6) {S = 0;}
	/* human */
    else if (sscanf(self, "%d/%d/%d%1[T ]%d:%d:%d", &d, &m, &y, &sep, &H, &M, &S) == 7) {}
    else if (sscanf(self, "%d/%d/%d%1[T ]%d:%d", &d, &m, &y, &sep, &H, &M) == 6) {S = 0;}
    else if (sscanf(self, "%d/%d/%d", &d, &m, &y) == 3) {H = 0;M = 0;S = 0;}
    else if (sscanf(self, "%d/%d", &d, &m) == 3) {H = 0;M = 0;S = 0;}
    else if (sscanf(self, "%d-%d-%d", &y, &m, &d) == 3) {H = 0;M = 0;S = 0;}
    else if (sscanf(self, "%d:%d:%d", &H, &M, &S) == 3) {d = 1;m = 1;y = 1970;}
    else if (sscanf(self, "%d:%d", &H, &M) == 2) {d = 1;m = 1;y = 1970;S = 0;}
    else {
		struct tm *atm;
		time_t t = (time_t)now_void();	
		claire_tzset(1);
		atm = localtime(&t);
		claire_tzset(0);
		if(atm == 0) Cerror(70,0,0);
		CL_INT len = strlen(self);
		y = atm->tm_year + 1900;
		H = 0;M = 0;S = 0;
		if (4 <= len)
		{ d= integer_I_string(substring_string(self,1,2));
		m = integer_I_string(substring_string(self,3,4));
		} 
		if (6 <= len)
		y = integer_I_string(substring_string(self,5,strlen(self))); 
	}
	
	if (y < 70) y= (y+2000);
	else if (y < 100) y= (y+1900);

	//xp: month name check
	if (m == 0 & strlen(month_name) > 0)
	{
		if (strcmp(month_name,"Jan") == 0) { m = 1; }
		else if (strcmp(month_name,"Feb") == 0) { m = 2; }
		else if (strcmp(month_name,"Mar") == 0) { m = 3; }
		else if (strcmp(month_name,"Apr") == 0) { m = 4; }
		else if (strcmp(month_name,"May") == 0) { m = 5; }
		else if (strcmp(month_name,"Jun") == 0) { m = 6; }
		else if (strcmp(month_name,"Jul") == 0) { m = 7; }
		else if (strcmp(month_name,"Aug") == 0) { m = 8; }
		else if (strcmp(month_name,"Sep") == 0) { m = 9; }
		else if (strcmp(month_name,"Oct") == 0) { m = 10; }
		else if (strcmp(month_name,"Nov") == 0) { m = 11; }
		else m = 12;
	}

	//xp: timezone support
	if (offsetsign == '-')
	{
		// negative offset
		old_tz = tzset_string("UTC");
		H += offset_val_h;
		M += offset_val_m;
	} else if (offsetsign == '+')
	{
		// positive offset
		old_tz = tzset_string("UTC");
		H -= offset_val_h;
		M -= offset_val_m;
	} else if (strlen(tz_name)  > 0)
	{
		// custom time zone
		old_tz = tzset_string(tz_name);
	}
	
	Result = make_date_integer(d,m,y,H,M,S);

	//xp back to previously defined timezone if needed
	if (old_tz != NULL) tzset_string(old_tz);

    GC_UNBIND;
    return (Result);
}

OID make_date_string_(char *self) {
	return _float_(make_date_string(self));
}

//<sb> time parser
// "XX"    -> "0:XX:00"
// "XXX"   -> "X:XX:00"
// "XX:X"  -> "XX:0X:00"
// "XX:XX" -> "XX:XX:00"
double make_time_string(char *self) {
	GC_BIND;
	struct tm atm; // set to January 1, 1970
	atm.tm_isdst = 0;
	atm.tm_year = 70;
	atm.tm_mon = 0;
	atm.tm_mday = 1;
	atm.tm_min = 0;
    atm.tm_sec = 0;
    if (occurrence_string(self,":") == 0)
       atm.tm_hour = integer_I_string(self);
	else if (occurrence_string(self,":") == 1)
       { list * l = GC_OBJECT(list,explode_string(self,":"));
        atm.tm_hour = (*Kernel.integer_I)((*(l))[1]);
        atm.tm_min = (*Kernel.integer_I)((*(l))[2]);
        }
	else if (occurrence_string(self,":") == 2)
       { list * l = GC_OBJECT(list,explode_string(self,":"));
        atm.tm_hour = (*Kernel.integer_I)((*(l))[1]);
        atm.tm_min = (*Kernel.integer_I)((*(l))[2]);
        atm.tm_sec = (*Kernel.integer_I)((*(l))[3]);
       }
    time_t t;
    t = mktime(&atm);
	if(t == -1) mktime_error(&atm);
    GC_UNBIND;
    return (double)t; 
}

OID make_time_string_(char *self) {
	return _float_(make_time_string(self));
}

double make_time_integer(CL_INT h, CL_INT m, CL_INT s) {
	struct tm atm; // set to January 1, 1970
	atm.tm_isdst = 0;
	atm.tm_year = 70;
	atm.tm_mon = 0;
	atm.tm_mday = 1;
	atm.tm_hour = h;
	atm.tm_min = m;
    atm.tm_sec = s;
    time_t t;
    t = mktime(&atm);
	if(t == -1) mktime_error(&atm);
    return (double)t; 
} 

OID make_time_integer_(CL_INT h, CL_INT m, CL_INT s) {
	return _float_(make_time_integer(h,m,s));
}

//<sb> how to add some units on a date/time component
double date_add_float(double self, ClaireChar *what, CL_INT inc) {
	struct tm *atm;
	time_t t = (time_t)self;
	claire_tzset(1);
    atm = localtime(&t);
	claire_tzset(0);
    if(atm == 0) Cerror(70,0,0);
    atm->tm_isdst = -1;
	switch(what->ascii) {
    	case 'H':
    	case 'h':
    		atm->tm_hour += inc; break;
    	case 'M':
    		atm->tm_min += inc; break;
    	case 'S':
    	case 's':
    		atm->tm_sec += inc; break;
    	case 'd':
    	case 'D':
    		atm->tm_mday += inc; break;
    	case 'm':
    		atm->tm_mon += inc; break;
    	case 'Y':
    	case 'y':
    		atm->tm_year += inc;
    }
    t = mktime(atm);
	if(t == -1) mktime_error(atm);
	return (double)t;
}
OID date_add_float_(OID self, ClaireChar *what, CL_INT inc) {
	return _float_(date_add_float(float_v(self),what,inc));
}

//<sb> wrapper for the C strftime - see man
char *strftime_string(char* format, double t) {
	ClEnv->bufferStart();
	CL_INT maxlen = 1024 + LENGTH_STRING(format);
	ClEnv->pushAttempt(maxlen);
	struct tm *atm;
	time_t long_time = (time_t)t;	
    //atm = localtime(&long_time);
	claire_tzset(1);
    atm = localtime(&long_time);
	claire_tzset(0);
    if(atm == 0) Cerror(70,0,0);
	claire_tzset(1);
    CL_INT n = strftime(ClEnv->buffer, maxlen, format, atm);
	claire_tzset(0);
    if (n == 0) Cerror(16,0,0);
    else ClEnv->bLength = n;
    return ClEnv->bufferCopy();
}

char *strftime_string_(char* format, OID t) {
	return strftime_string(format,float_v(t));
}

//<sb> return the time difference in second
double diff_time_float(double t1, double t2) {
	return difftime((time_t)t1,(time_t)t2);
}
OID diff_time_float_(OID t1, OID t2) {
	return _float_(diff_time_float(float_v(t1),float_v(t2)));
}

tuple* explode_float(double self) {
	struct tm *atm;
	time_t t = (time_t)self;
	claire_tzset(1);
    atm = localtime(&t);
	claire_tzset(0);
	if(atm == 0) Cerror(70,0,0);
	tuple *result;
	result = tuple::alloc(9, atm->tm_year + 1900, atm->tm_mon + 1,
	                              atm->tm_yday + 1, atm->tm_mday, atm->tm_wday + 1,
	                              atm->tm_hour, atm->tm_min, atm->tm_sec,
	                              atm->tm_isdst?Kernel.ctrue:Kernel.cfalse);
	return result;
}

tuple* explode_float_(OID t) {
	return explode_float(float_v(t))->copyIfNeeded();
}



//<sb> the current date/time
double now_void() {
	time_t t;
	time(&t); //<sb> assume no error will occur
	return (double)t;
}

OID now_void_() {
	return _float_(now_void());
}

//<sb> prints the elapsed time since t
void uptime_float(double t) {
	char buf[100];
	CL_INT printask = 0;
	double msec = 1000.0 * (timer_I_void() - t);
	CL_INT neg = msec < 0.0;
	if(neg) msec = -msec;
	if (msec < 0) msec = -msec;		
	long days = (long)(msec / 86400000.0);
	if(days) {
		sprintf(buf,"%s%dd",(neg?"-":""),days);
		princ_string(buf);
		printask = 1;
	}
	msec = msec - (double)(86400000 * days);
	long hours = (long)(msec / 3600000.0);
	if(hours || printask) {
		sprintf(buf,"%s%s%dh",printask?" ":"", (neg?"-":""),hours);
		princ_string(buf);
		printask = 1;
	}
	msec = msec - (double)(3600000 * hours);
	long mins = (long)(msec / 60000.0);
	if(mins || printask) {
		sprintf(buf,"%s%s%dm",printask?" ":"", (neg?"-":""),mins);
		princ_string(buf);
		printask = 1;
	}
	msec = msec - (double)(60000 * mins);
	long sec = (long)(msec / 1000.0);
	if(sec || printask) {
		sprintf(buf,"%s%s%ds",printask?" ":"", (neg?"-":""),sec);
		princ_string(buf);
		printask = 1;
	}
	msec = msec - (double)(1000 * sec);
	sprintf(buf,"%s%s%dms",printask?" ":"",(neg?"-":""),(long)msec);
	princ_string(buf);
  }

void uptime_float_(OID t) {
	uptime_float(float_v(t));
}

//<sb> return a unique string (26 bytes length)
// based on process birth [date][random number][pid]
char* uid_void() {
	static double T0 = 0.0;
	if (T0 == 0.0) T0 = now_void();
	T0 += 1.0;
	char tmp[30];
	char *tmp2;
	char UID[30] = "";
	tmp2 = (char*)tmp;
	sprintf(tmp, "%08.0f", T0);
	while(strlen(tmp2) > 8) tmp2++;
	strcat(UID,tmp2);
	tmp2 = (char*)tmp;
	sprintf(tmp, "%08.0f", now_void());
	while(strlen(tmp2) > 8) tmp2++;
	strcat(UID,tmp2);
	tmp2 = (char*)tmp;
	sprintf(tmp, "%05.0f", (double)getpid_void());
	while(strlen(tmp2) > 5) tmp2++;
	strcat(UID,tmp2);
	tmp2 = (char*)tmp;
	sprintf(tmp, "%05.0f", (double)rand());
	while(strlen(tmp2) > 5) tmp2++;
	strcat(UID,tmp2);
	return copy_string(UID);
}

/*********************************************************************/
/**    3. files system                                               */
/*********************************************************************/

//<sb> simple wilcard parser
// understand following special chars :
//		*	: any sequence of char
//		?	: any char
//		#<char>	: '<char>'      how to escape a char
static CL_INT match_wildcard_ask_string_impl(char* src, CL_INT lensrc, char* w, CL_INT lenw) {
	if(lensrc == 0 && lenw == 0) return 1;
	if(lenw == 0) return 0;
	if(*w == '#') {
		if(*src != w[1])
			return 0;
		return match_wildcard_ask_string_impl(src + 1, lensrc - 1, w + 2, lenw - 2);
	}
	if(*w == '*') {
		if(lenw == 1) return 1;
		if(lensrc == 0) return 0;
		if (w[1] == '#')
			return (match_wildcard_ask_string_impl(src, lensrc, w + 1, lenw - 1) ||
					match_wildcard_ask_string_impl(src + 1, lensrc - 1, w, lenw));
		if(w[1] == *src)
			return (match_wildcard_ask_string_impl(src + 1, lensrc - 1, w + 2, lenw - 2) ||
					match_wildcard_ask_string_impl(src + 1, lensrc - 1, w, lenw));
		return match_wildcard_ask_string_impl(src + 1, lensrc - 1, w, lenw);
	}
	else if(lensrc == 0) return 0;
	else if(*w == '?') return match_wildcard_ask_string_impl(src + 1, lensrc - 1, w + 1, lenw - 1);
	if(*src != *w) return 0;
	else return match_wildcard_ask_string_impl(src + 1, lensrc - 1, w + 1, lenw - 1);
}

ClaireBoolean *match_wildcard_ask_string(char* src, char* w) {
	return match_wildcard_ask_string_impl(src, LENGTH_STRING(src), w, LENGTH_STRING(w)) ?
				CTRUE : CFALSE;
}



char *exw[32];
CL_INT iexw;

static CL_INT explode_wildcard_string_impl(char* src, CL_INT lensrc, char* w, CL_INT lenw, CL_INT sp);
static CL_INT explode_wildcard_string_impl0(char* src, CL_INT lensrc, char* w, CL_INT lenw, CL_INT sp) {
	if (iexw >= 30)
		Cerror(74, _string_("Too many wilcard chars for explode_wildcard"), 0);
	CL_INT old = iexw;
	CL_INT special = (*w == '?' | *w == '*');
	if (sp && !special) //<sb> leave a special char
		exw[iexw++] = src;
	if (!sp && special) //<sb> enter a special char
		exw[iexw++] = src;	
	if(!explode_wildcard_string_impl(src, lensrc, w, lenw, special)) {
		iexw = old;
		return 0;
	}
	return 1;
}

static CL_INT explode_wildcard_string_impl(char* src, CL_INT lensrc, char* w, CL_INT lenw, CL_INT sp) {
	if(lensrc == 0 && lenw == 0) return 1;
	if(lenw == 0) return 0;
	if(*w == '#') {
		if(*src != w[1])
			return 0;
		return explode_wildcard_string_impl0(src + 1, lensrc - 1, w + 2, lenw - 2, 0);
	}
	if(*w == '*') {
		if(lenw == 1) return 1;
		if(lensrc == 0) return 0;
		if (w[1] == '#')
			return (explode_wildcard_string_impl0(src, lensrc, w + 1, lenw - 1, 1) ||
					explode_wildcard_string_impl0(src + 1, lensrc - 1, w, lenw, 1));
		if(w[1] == *src)
			return (explode_wildcard_string_impl0(src, lensrc, w + 1, lenw - 1, 1) ||
					explode_wildcard_string_impl0(src + 1, lensrc - 1, w, lenw, 1));
		return explode_wildcard_string_impl(src + 1, lensrc - 1, w, lenw, sp);
	}
	else if(lensrc == 0) return 0;
	else if(*w == '?') return explode_wildcard_string_impl0(src + 1, lensrc - 1, w + 1, lenw - 1, 1);
	if(*src != *w) return 0;
	else return explode_wildcard_string_impl0(src + 1, lensrc - 1, w + 1, lenw - 1, 0);
}


list *explode_wildcard_string(char* src, char* w) {
	iexw = 0;
	if (explode_wildcard_string_impl0(src, LENGTH_STRING(src), w, LENGTH_STRING(w), 0)
			&& iexw % 2) //<sb> the end of string is missing (e.g wildcard terminated by *)
		exw[iexw++] = src + LENGTH_STRING(src);
	if (iexw > 0) {
		CL_INT i = 0;
		list *res = make_list_type1(Kernel._string, iexw / 2);
		for(;i < iexw;i++) {
			char *match = exw[i];
			CL_INT len = exw[++i] - match;
			res->content[++res->length] = _string_(GC_STRING(copy_string1(match, len)));
		}
		return res;
	}
	return Kernel.nil; //<sb> no match
}
	



//<sb>
// returns the list of the given directory entries
// that match the wilcard filter
// but . and ..
list *entries_string1(char *self,char *wild) {
	GC_RESERVE(1); 
	list * l = list::empty(Kernel._string);
	OID gc_local;
#ifdef CLPC
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(GC_STRING(append_string(self,"/*")), &wfd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do { GC_LOOP;
			if(strcmp(wfd.cFileName,".") && strcmp(wfd.cFileName,"..") &&
				(wild == 0 || match_wildcard_ask_string(wfd.cFileName,wild) == CTRUE)) {
				GC__ANY(l = l->addFast(GC_OID(_string_(copy_string(wfd.cFileName)))), 1); 
			} GC_UNLOOP;
		} while (FindNextFile(hFind, &wfd));
		FindClose(hFind);
	}
#else
	DIR* fd = opendir(self);
	struct dirent* dp;
	if(fd) {
		while((dp = readdir(fd))) {
			 GC_LOOP;
			if(strcmp(dp->d_name,".") && strcmp(dp->d_name,"..") &&
				(wild == 0 || match_wildcard_ask_string(dp->d_name,wild) == CTRUE)) {
				GC__ANY(l = l->addFast(GC_OID(_string_(copy_string(dp->d_name)))), 1); 
			}
			GC_UNLOOP;
		}
		closedir(fd);
	}
#endif
	else if(wild) Cerrorno(72,_string_(self),_string_(wild));
	else Cerrorno(73,_string_(self),0);
	GC_UNBIND;
	return l;
}

//<sb> returns the list of all entries of the given directory
// but . and ..
list *entries_string2(char *self) {
	return entries_string1(self,0); }

//<sb> check if the given entry is a file
// in case of error we return false
ClaireBoolean *isfile_ask_string(char *self) {
	CL_INT isdir = 1;
	struct stat sb;
	if(stat(self, &sb) != -1) {
		isdir = ((sb.st_mode) & S_IFMT) == S_IFDIR;
	}
	return isdir?CFALSE:CTRUE;
}

//<sb> check if the given entry is a directory
// in case of error we return false
ClaireBoolean *isdir_ask_string(char *self) {
	CL_INT isdir = 0; 
	struct stat sb;
	if(stat(self, &sb) != -1) {
		isdir = ((sb.st_mode) & S_IFMT) == S_IFDIR;
	}
	return isdir?CTRUE:CFALSE;
}

//<sb> copy a file byte per byte
// sets mode of the copy to the source mode
void fcopy_string(char *self, char *trg) {
	CL_INT mode = 0;
	char buf[1024];
	struct stat sb;
	if(stat(self, &sb) == -1) Cerrorno(91,_string_(self),_string_("fcopy"));
	mode = sb.st_mode;
	FILE *f = fopen(self,"rb");
	if(f == 0) Cerrorno(36,_string_(self),0);
	FILE *t = fopen(trg,"wb");
	if(t == 0) {
		fclose(f);
		Cerrorno(36,_string_(trg),0);
	}
	while(1) {
		CL_INT n = fread(buf, 1, 1024, f);
		if(ferror(f)) {
			fclose(f); fclose(t);
			Cerrorno(84,_string_(self),_string_(trg));
		}
		if(n>0) {
			fwrite(buf, 1, n, t);
			if(ferror(t)) {
				fclose(f); fclose(t);
				Cerrorno(84,_string_(self),_string_(trg));
			}
		}
		if(feof(f)) break;
	}
	if(chmod(trg, (mode_t)mode) == -1) { //<sb> copy source mode
		fclose(f); fclose(t);
		Cerrorno(81,_string_(trg),_integer_(mode));
	}
	fclose(f);
	fclose(t);
}

//<sb> unlink the given file
void unlink_string(char *self) {
	if(unlink(self))
		Cerrorno(78, _string_(self),0);
}

//<sb> create a new directory with a given mode
void mkdir_string1(char *self, CL_INT mode) {
	#ifdef CLPC
	if(_mkdir(self))
	#else
	if(mkdir(self,(mode_t)mode))
	#endif
		Cerrorno(79, _string_(self),_integer_(mode));
}

//<sb> create a new directory with mode 0o777
void mkdir_string2(char *self) {
	#ifdef CLPC
	mkdir_string1(self,0);
	#else
	mkdir_string1(self,511);
	#endif
}

//<sb> remove a directory expected to be empty
void rmdir_string(char *self) {
	if(rmdir(self))
		Cerrorno(80, _string_(self),0);
}

//<sb> change file mode
// not really PC proof
void chmod_string(char *self, CL_INT mode) {
	if(chmod(self, (mode_t)mode) == -1)
		Cerrorno(81,_string_(self),_integer_(mode));
}

//<sb> create a hard link on a file
void link_string(char *name1, char *name2) {
	#ifdef CLPC
	if(0) //<sb> not supported
	#else
	if(link(name1,name2) == -1)
	#endif
		Cerrorno(82, _string_(name1),_string_(name2));
}

//<sb> create a symbolic link on a file
void symlink_string(char *name1, char *name2) {
	#ifdef CLPC
	if(0) //<sb> not supported
	#else
	if(symlink(name1,name2) == -1)
	#endif
		Cerrorno(83, _string_(name1),_string_(name2));
}

//<sb> request file size (use float because of integer size limitation...)
double fsize_string(char* self) {
	double len = 0.0;
	struct stat sb;
	if(stat(self, &sb) != -1) len = (double)sb.st_size;
	else Cerrorno(91,_string_(self),_string_("fsize"));
	return len;
}

OID fsize_string_(char* self) {
	return _float_(fsize_string(self));
}


//<sb> get the time of last change of the given file
double fchanged_string(char *self) {
	double t;
	struct stat sb;
	if(stat(self, &sb) != -1)
		t = (double)sb.st_ctime;
	else Cerrorno(91,_string_(self), _string_("fcreated"));
	return t;}

OID fchanged_string_(char *self) {
	return _float_(fchanged_string(self));
}

//<sb> get modfication/change time of the given file
double fmodified_string(char *self) {
	double t;
	struct stat sb;
	if(stat(self, &sb) != -1)
		t = (double)sb.st_mtime;
	else Cerrorno(91,_string_(self), _string_("fmodified"));
	return t;}

OID fmodified_string_(char *self) {
	return _float_(fmodified_string(self));
}

//<sb> get last accessed time of the given file
double faccessed_string(char *self) {
	double t;
	struct stat sb;
	if(stat(self, &sb) != -1)
		t = (double)sb.st_atime;
	else Cerrorno(91,_string_(self), _string_("faccessed"));
	return t;
}

OID faccessed_string_(char *self) {
	return _float_(faccessed_string(self));
}

//<sb> get a file mode
CL_INT fmode_string(char *self) {
	CL_INT mode;
	struct stat sb;
	if(stat(self, &sb) != -1) {
		mode = (CL_INT)sb.st_mode;
	}
	else Cerrorno(91,_string_(self), _string_("fmode"));
	return mode;
}

#ifdef CLPC
// on PC we need to initialize "_" env var
// with the path to the file used to create the current process
class InitUnderscore {
public:
	static InitUnderscore single;
	InitUnderscore() {
		char buf[1024];
		strcpy(buf,"_=");
		GetModuleFileName(NULL,buf+2,1022);
		_putenv(buf);
	}
};
InitUnderscore InitUnderscore::single = InitUnderscore();
#endif

char* realpath_string(char* self) {
	#ifdef CLPC
	static char res[1024];
    strcpy(res, self);
    if(res[strlen(res) - 1] == '\\') res[strlen(res) - 1] = 0;
    return copy_string(res);
	#else
	char buf[MAXPATHLEN];
	char *res = realpath(self,buf);
	if(res == 0) Cerrorno(91,_string_(self), _string_("realpath"));
	return copy_string(res);
	#endif
}

/*********************************************************************/
/**    4. process                                                    */
/*********************************************************************/

CL_INT isforked = 0;
CL_INT lastforked = 0;

//<sb> get my pid
CL_INT getpid_void() {
#ifdef CLPC
	return (CL_INT)GetCurrentProcessId();
#else
	return (CL_INT)getpid();
#endif
}

//<sb> get my uid
CL_INT getuid_void() {
#ifdef CLPC
	return (CL_INT)0;
#else
	return (CL_INT)getuid();
#endif
}

//<sb> get my pid
CL_INT getppid_void() {
#if defined(CLPC) || !defined(HAVE_GETPPID)
	return 0;
#else
	return (CL_INT)getppid();
#endif
}

#if !defined(CLPC)
static inline CL_INT process_run(CL_INT p) {
	CL_INT res = 0;
	#ifdef HAVE_GETSID
	res = (CL_INT)getsid(p);
	#else
	#ifdef HAVE_GETPRIORITY
	errno = 0;
	getpriority(PRIO_PROCESS,p);
	if(errno) res = -1;
	#else
	Cerror(75,_string_("getsid"),0);
	#endif
	#endif
	return res;
}

static inline void ensure_no_zombie(CL_INT process) {
	CL_INT status;
	waitpid(process,  &status, WNOHANG|WUNTRACED);
}
#endif

//<sb> kill (brutal if needed) the given process
void kill_integer1(CL_INT process) {
#ifdef CLPC
	HANDLE h = OpenProcess(PROCESS_TERMINATE, 0, process);
	if(h) {
		TerminateProcess(h, 0);
		CloseHandle(h);
	} else Cerrorno(76,_integer_(process),0);
#else
	CL_INT tried = 5;
    // give it a chance to gracefully exit
    if(kill(process, SIGTERM)==-1) Cerrorno(86,process,_string_("SIGTERM"));
    while(process_run(process) >= 0 && tried--) {
    	ensure_no_zombie(process);
		sleep_integer(100);
	}
    // well, try to really kill it without advertising
    if (process_run(process) >= 0) {
        if(kill(process, SIGKILL) == -1)
        	Cerrorno(86,process,_string_("SIGKILL"));
		ensure_no_zombie(process);
    	while(process_run(process) >= 0) {
			ensure_no_zombie(process);
            sleep_integer(100);
		}
    }
#endif	
}

//<sb> test if the given process is running
ClaireBoolean* run_ask_integer(CL_INT pr) {
	if(getpid_void() == pr) return CTRUE; //<sb> am I running ?
#ifdef CLPC
	HANDLE h = OpenProcess(SYNCHRONIZE, 0, pr);
	if(h) {
		CloseHandle(h);
		return CTRUE;
	}
	else return CFALSE;
#else
    return process_run(pr) >= 0 ? CTRUE : CFALSE;
#endif	
}

//<sb> wait for termination of the given process
// returns true as soon as the given process terminates
// and false if timeout (ms) reached
ClaireBoolean* wait_integer1(CL_INT pr, CL_INT ms) {
#ifdef CLPC
	HANDLE h = OpenProcess(SYNCHRONIZE, 0, pr);
	if(h) {
		CL_INT res = WaitForSingleObject(h, ms) == WAIT_OBJECT_0;
		CloseHandle(h);
		return res ? CTRUE : CFALSE;
	}
	else return CFALSE;
#else
	timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 10000;
    while(process_run(pr) >= 0)
    	{ select(1, NULL, NULL, NULL, &tv);
    		if((ms -= 10) <= 0) return CFALSE; }
	return CTRUE;
#endif
	
}

//<sb> wait for termination of the given process
void wait_integer2(CL_INT pr) {
#ifdef CLPC
	HANDLE h = OpenProcess(SYNCHRONIZE, 0, pr);
	if(h) {
		WaitForSingleObject(h, INFINITE);
		CloseHandle(h);
	}
	else Cerrorno(76,_integer_(pr),0);
#else
	timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 10000;
	while(process_run(pr) >= 0)
		select(1, NULL, NULL, NULL, &tv);
#endif
}

#ifndef CLPC
#ifndef WEXITSTATUS
# define WEXITSTATUS(stat_val) ((CL_UNSIGNED)(stat_val) >> 8)
#endif
#ifndef WIFEXITED
# define WIFEXITED(stat_val) (((stat_val) & 255) == 0)
#endif
#endif

tuple *waitpid_status_integer(CL_INT process, ClaireBoolean* block) {
#if defined(CLPC)
	Cerror(75,_string_("waitpid"),0);
	return 0;
#else
	CL_INT status, exitstatus;
    pid_t wpid;
    tuple *result;
    // waitpid() returns 0 if the child process is still running, or the 
    // process id if it stopped.  It can also return -1 in case of error.
    if (block == CTRUE)
    	wpid = waitpid((pid_t)process, &status, WUNTRACED);
    else wpid = waitpid((pid_t)process, &status, WNOHANG|WUNTRACED);
	if(wpid == -1) Cerrorno(74,_string_("waitpid failed"),0);
	else if(wpid == 0) result = tuple::alloc(3,0,0,-1);
	else {
		if (WIFEXITED(status)) { // program called exit
			exitstatus = WEXITSTATUS(status);
			result = tuple::alloc(3,1,wpid,exitstatus);
		} else if(WIFSIGNALED(status)) { // process was signaled
			exitstatus = WTERMSIG(status);
			result = tuple::alloc(3,2,wpid,exitstatus);
		} else if(WIFSTOPPED(status)) { // process was stopped
			exitstatus = WSTOPSIG(status);
			result = tuple::alloc(3,3,wpid,exitstatus);
		}
		else result = tuple::alloc(3,4,wpid,-1);
	}
	return result;
#endif
}

tuple *waitpid_status_integer_(CL_INT process, ClaireBoolean* block) {
	return waitpid_status_integer(process, block)->copyIfNeeded();
}

//<sb> fork interface
// on PC we throw an exception...
CL_INT cfork_void1() {
#if defined(CLPC) || !defined(HAVE_FORK)
	Cerror(75,_string_("fork"),0);
	return 0;
#else
	lastforked = fork();
	if(lastforked == -1) {
		lastforked = 0;
		Cerrorno(77,0,0);
	}
	if(lastforked == 0) {
		LOGO = 0; //<sb> v3.3.33 child shouldn't print exit string "bye..."
		isforked = 1; //<sb> v3.3.33 checked by trace method, do we print pid ?
	}
	return lastforked;
#endif
}


//<sb> get the last forked pid
CL_INT forked_void() {
#if defined(CLPC) || !defined(HAVE_FORK)
	Cerror(75,_string_("fork"),0);
	return 0;
#else
	if(lastforked == 0) Cerror(85,0,0);
	return lastforked;
#endif
}



//<sb> we use CreateProcess on a PC
// and fork/execve on unix
#ifdef CLPC
CL_INT pocess_I_string(char* self, bag* args) {
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	CL_INT created;
	CL_INT flag = CREATE_NEW_PROCESS_GROUP;
	ZeroMemory(&si,sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	GC_RESERVE(1);  // v3.0.55 optim !
    char *Result ;
    char * s = self;
    OID gc_local;
	ITERATE(i);
	for (START(args); NEXT(i);)
	{ GC_LOOP;
       OID  ztest;
       if (Kernel._string == OWNER(i)) ztest = i;
		else if (INHERIT(OWNER(i),Kernel._integer)) ztest = (*Kernel.string_I)(i);
		else if (Kernel._float == OWNER(i)) ztest = (*Kernel.string_I)(i);
		else if (Kernel._boolean == OWNER(i)) {
			if ((OBJECT(ClaireBoolean,i)) == CTRUE)
				ztest = _string_("true");
			else ztest = _string_("false");
		} 
		else ztest = CNULL;
		GC_OID(ztest); 
		if (ztest != CNULL)
		{ char * z = string_v(ztest);
              GC__STRING(s = append_string(s,GC_STRING(append_string(GC_STRING(append_string(" \"",z)),"\""))), 1);
		} 
    GC_UNLOOP;} 
	Result = s;
	created = CreateProcess(
			  NULL,	// pointer to name of executable module
			  Result,	// pointer to command line string
			  NULL,	// process security attributes
			  NULL,	// thread security attributes
			  0,//daemon,	// handle inheritance flag
			  0,//flag,	// creation flags
			  NULL,	// pointer to new environment block
			  NULL,	// pointer to current directory name
			  &si,	// pointer to STARTUPINFO
			  &pi);	// pointer to PROCESS_INFORMATION
	if(!created) Cerrorno(77,0,0);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	GC_UNBIND;
	return pi.dwProcessId;
}

#else

//<sb> here is a private tool to build a C string array
// from a claire bag
// integer/float/boolean are stringed!
static char **make_arg_string(char* self, bag *args) {
	static char** argv = 0;
	CL_INT n = 1;
	if(argv) delete [] argv;
	argv = new char*[args->length + 2];
	if (argv == 0) return 0;
	argv[0] = self;
	GC_BIND;
	OID gc_local;
	ITERATE(i);
	for(START(args); NEXT(i);) {
		OID o = 0;
        if(Kernel._string == OWNER(i)) o = i;
		else if(INHERIT(OWNER(i),Kernel._integer) || Kernel._float == OWNER(i))
			o = (*Kernel.string_I)(i);
		else if(Kernel._boolean == OWNER(i)) {
        	if(OBJECT(ClaireBoolean,i) == CTRUE) o = _string_("true");
        	else o = _string_("false");
        }
        if(o) {
        	GC_OID(o);
        	argv[n++] = string_v(o);
        }
    }
    argv[n] = 0;
	GC_UNBIND;
	return argv;
}

CL_INT pocess_I_string(char* self, bag* args) {
	char** argv = make_arg_string(self, args);
	if(argv == 0) Cerror(61,_string_("process! @ (string, bag)"),0);
	CL_INT ret = cfork_void1();
	switch(ret) {
		case 0:
			execve(self, argv, environ);
			Cerrorno(77,0,0);
			break;
	}
	return ret;
}
#endif



/*********************************************************************/
/**    5. uname                                                      */
/*********************************************************************/

#ifdef CLPC

// On a PC, tell if the MMX instruction set is availbale or not.
CL_INT pc_have_mmx_support = 0;

struct	utsname {
	char	sysname[256]; // Name of OS
	char	nodename[256]; // Name of this network node
	char	release[256]; // Release level
	char	version[256]; // Version level
	char	machine[256]; // Hardware type
};
// the pc doesn't understand uname so we guess it could
// exists as :
extern CL_INT uname(struct utsname *name);
CL_INT uname(struct utsname *ub) {
	char *ptr;
	DWORD version;
	SYSTEM_INFO sysinfo;
	char hostname[4096];
	version = GetVersion();
	GetSystemInfo(&sysinfo);
	switch (sysinfo.wProcessorArchitecture) {
		case PROCESSOR_ARCHITECTURE_INTEL: strcpy(ub->machine, "ix86");break;
		case PROCESSOR_ARCHITECTURE_MIPS : strcpy(ub->machine, "mips");break;
		case PROCESSOR_ARCHITECTURE_ALPHA: strcpy(ub->machine, "alpha");break;
		case PROCESSOR_ARCHITECTURE_PPC:strcpy(ub->machine, "ppc");break;
		default:strcpy(ub->machine, "unknown");break; }
	if (version<0x80000000) strcpy(ub->version, "NT");
	else if (LOBYTE(LOWORD(version))<4) strcpy(ub->version, "Win32s");
	else strcpy(ub->version, "Win95");
	sprintf(ub->release, "%u.%u", (DWORD)(LOBYTE(LOWORD(version))), (DWORD)(HIBYTE(LOWORD(version))));
	strcpy(ub->sysname, "Windows");
	if(gethostname(hostname, sizeof(hostname)) == 0)
		{ if((ptr = strchr(hostname, '.'))) *ptr = '\0'; }
	else strcpy(hostname, "unknown");
	strcpy(ub->nodename, hostname); //, sizeof(ub->nodename));
	//ub->nodename[_SYS_NMLN - 1] = '\0';
	pc_have_mmx_support = IsProcessorFeaturePresent(PF_MMX_INSTRUCTIONS_AVAILABLE);
	return 0;
}

#endif

class InitUname {
public:
	static InitUname single;
	struct utsname un;
	InitUname() {uname(&un);}
};

InitUname InitUname::single = InitUname();

//<sb> the uname struct is exploded in a set of api :
char* sys_name_void() {return InitUname::single.un.sysname;}
char* sys_node_name_void() {return InitUname::single.un.nodename;}
char* sys_release_void() {return InitUname::single.un.release;}
char* sys_version_void() {return InitUname::single.un.version;}
char* sys_machine_void() {return InitUname::single.un.machine;}
char* sys_arch_void() {
	#ifdef CLPC
	return "ix86";
	#else
	return CLARCH;
	#endif
}

char* sys_compiler_void() {
	#ifdef CLPC
	return "cl";
	#else
	return CLSYSCOMPILER;
	#endif
}
char* sys_compiler_version_void() {
	#ifdef CLPC
	return "";
	#else
	return CLSYSCOMPILERVERSION;
	#endif
}


/*********************************************************************/
/**    6. string - case/digit test                                   */
/*********************************************************************/

ClaireBoolean* alpha_ask_string(char* s) {
	CL_INT i = 0;
	CL_INT len = LENGTH_STRING(s);
    for(;i < len;i++) {
       //if(isalpha((CL_INT)s[i])==0) return CFALSE;
       if(s[i] >= 'a' && s[i] <= 'z') continue;
	   if(s[i] >= 'A' && s[i] <= 'Z') continue;
		return CFALSE; 
	}
    return CTRUE; 
}   


ClaireBoolean* alpha_ask_char(ClaireChar* c) {
	if((CL_INT)c->ascii >= 'a' && (CL_INT)c->ascii <= 'z') return CTRUE;
	if((CL_INT)c->ascii >= 'A' && (CL_INT)c->ascii <= 'Z') return CTRUE;
    return CFALSE;
}

ClaireBoolean* lower_ask_char(ClaireChar* c) {
	if((CL_INT)c->ascii >= 'A' && (CL_INT)c->ascii <= 'Z') return CFALSE;
    return CTRUE;
}


ClaireBoolean* lower_ask_string(char* s) {
	CL_INT i = 0;
	CL_INT len = LENGTH_STRING(s);
    for(;i < len;i++)
    	if(s[i] >= 'A' && s[i] <= 'Z') return CFALSE;
    return CTRUE;
}


ClaireBoolean* upper_ask_char(ClaireChar* c) {
    if((CL_INT)c->ascii >= 'a' && (CL_INT)c->ascii <= 'z') return CFALSE;
    return CTRUE;
}


ClaireBoolean* upper_ask_string(char* s) {
	CL_INT i = 0;
	CL_INT len = LENGTH_STRING(s);
    for(;i < len;i++)
       if(s[i] >= 'a' && s[i] <= 'z') return CFALSE;
    return CTRUE;
}


char* upper_string(char* s){
    char* res = copy_string(s);
    CL_INT len = LENGTH_STRING(s);
	CL_INT i = 0;
	for(;i < len;i++)
		if(s[i] >= 'a' && s[i] <= 'z')
			res[i] = s[i] + 'A' - 'a';
    return res;
}


char* lower_string(char* s) {
    char* res = copy_string(s);
    CL_INT len = LENGTH_STRING(s);
	CL_INT i = 0;
	for(;i < len;i++)
		if(s[i] >= 'A' && s[i] <= 'Z')
			res[i] = s[i] + 'a' - 'A';
	return res;
}

ClaireBoolean* space_ask_char(ClaireChar* c) {
  CL_INT ch = (CL_INT)c->ascii;
  return (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') ? CTRUE : CFALSE;
}


ClaireBoolean* digit_ask_char(ClaireChar* c) {
	return ((CL_INT)c->ascii >= '0' && (CL_INT)c->ascii <= '9') ? CTRUE : CFALSE;
}

ClaireBoolean* space_ask_string(char* s) {
	CL_INT i = 0;
	CL_INT len = LENGTH_STRING(s);
	for(;i < len;i++)
		if(!(s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n')) return CFALSE;
    return CTRUE;
}


ClaireBoolean* digit_ask_string(char* s) {
	CL_INT i = 0;
	CL_INT len = LENGTH_STRING(s);
	for(;i < len;i++)
		if(!(s[i] >= '0' && s[i] <= '9')) return CFALSE;
    return CTRUE;
}


/*********************************************************************/
/**    7. string - find/replace                                      */
/*********************************************************************/


char* replace_string(char* src, char* to, char *by)
{
	CL_INT lto = LENGTH_STRING(to);
	if(lto == 0) return "";
	CL_INT lsrc = LENGTH_STRING(src);
	if(lto > lsrc) return copy_string(src);
	ClEnv->bufferStart();
	CL_INT lby = LENGTH_STRING(by);
	CL_INT i = 0; CL_INT l = 0;
	for(;i < lsrc - lto + 1;i++)
	{
		CL_INT same = 1; CL_INT j = 0;
		for(;j < lto;j++)
			if(to[j] != src[i + j])
				{same = 0; break;}
		if(same)
			{for(j=0;j < lby;j++) ClEnv->pushChar(by[j]);
			i += lto - 1;
			l += lby;}
		else {l++;ClEnv->pushChar(src[i]);} }
	for(;i < lsrc;i++) {l++;ClEnv->pushChar(src[i]);}
	char *tmp = ClEnv->bufferCopy();
	return tmp;
}


CL_INT occurrence_string(char* in, char* to)
{
	CL_INT lin = LENGTH_STRING(in);
	CL_INT lto = LENGTH_STRING(to);
	if(lto == 0 || lin == 0) return 0;
	CL_INT res = 0;
	CL_INT i = 0;
	for(;i < lin - lto + 1;i++)
	{
		CL_INT same = 1; CL_INT j = 0;
		for(;j < lto;j++)
			if(to[j] != in[i + j])
				{same = 0; break;}
		if(same)
		{		
			i += lto - 1;
			res++;
		}
	}
	return res;
} 


CL_INT find_string(char* src, char* to, CL_INT from)
{
	if(from <= 0) return 0;
	CL_INT lsrc = LENGTH_STRING(src);
	CL_INT lto = LENGTH_STRING(to);
	CL_INT i = from - 1;
	for(;i < lsrc - lto + 1;i++)
	{
		CL_INT j = 0; CL_INT same = 1;
		for(;j < lto;j++)
			if(to[j] != src[i + j])
				{same = 0; break;}
		if(same) return i + 1;
	}
	return 0;
}


CL_INT rfind_string(char* src, char* to, CL_INT from)
{
	if(from > LENGTH_STRING(src)) return 0;
	CL_INT lto = LENGTH_STRING(to);
	CL_INT i = from - 1;
	for(;i >= 0;i--)
	{
		CL_INT j = 0; CL_INT same = 1;
		for(;j < lto;j++)
			if(to[j] != src[i + j])
				{same = 0; break;}
		if(same)
			return i + 1;
	}
	return 0;
}


char * ltrim_string(char *s) {
  CL_INT  p = 1;
  CL_INT ls = LENGTH_STRING(s);
  while(p <= ls) {
      char ch = s[p - 1];
      if (!(ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n'))
         break;
      p++; } 
  return substring_string(s,p,ls); }


char * rtrim_string(char *s) {
  CL_INT  p = LENGTH_STRING(s);
   while(p >= 1) {
      char ch = s[p - 1];
      if (!(ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n'))
        	break;
      p--; }
   return substring_string(s,1,p); }


char * trim_string(char *s) {
  CL_INT  p1 = 1;
  CL_INT  p2 = LENGTH_STRING(s);
  CL_INT ls = LENGTH_STRING(s);
  while (p1 <= ls) {
      char ch = s[p1 - 1];
      if(!(ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n'))
         break;
      p1++; } 
  while(p2 >= 1) {
  	  char ch = s[p2 - 1];
      if(!(ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n'))
        break;
       p2--; } 
  return substring_string(s,p1,p2); } 
  
  
CL_INT  find_string2(char *src,char *to)
{ return find_string(src,to,1);} 

char * right_string(char *src,CL_INT n)
{ return substring_string(src,((LENGTH_STRING(src)-n)+1),LENGTH_STRING(src));} 


char * left_string(char *src,CL_INT n)
{ return substring_string(src,1,n);} 

CL_INT  rfind_string2(char *src,char *to)
{ return rfind_string(src,to,LENGTH_STRING(src));} 


char *reverse_string(char *src) {
	CL_INT len = LENGTH_STRING(src);
	char *res =  ClAlloc->makeString(len);
	char *a = res + len - 1;
	for(;len > 0;len--)
		*a-- = *src++;
	return res;
}


/*********************************************************************/
/**    8. string - explode                                           */
/*********************************************************************/

#define EXPLODE_ADD(l, s, j) { \
	char *a = GC_STRING(ClAlloc->makeString(j)); \
	if(j) memcpy(a,s,j); \
	GC__ANY(l = l->addFast(GC_OID(_string_(a))), 1); }

list *explode_char_string(char *self, char sep) {
	GC_RESERVE(1);
  	list * l = list::empty(Kernel._string);
  	char *end = self + LENGTH_STRING(self);
	char *s1 = self;
	char *s2 = self;
	OID gc_local;
	while(s2 < end) 
	{ GC_LOOP;
	  s1 = s2;
	  while(s1 < end && *s1 != sep) s1++;
	  s1--;
	  EXPLODE_ADD(l, s2, s1 - s2 + 1)
		s2 = s1+2;
		GC_UNLOOP;}
	if(s2 < end)
		EXPLODE_ADD(l, s2, end - s2 + 1)
	GC_UNBIND; return l;
}

list * explode_string(char *self,char *sep) {
  CL_INT seplen = LENGTH_STRING(sep);
  if(seplen == 1) return explode_char_string(self, *sep);
  GC_RESERVE(1);
  list *l = list::empty(Kernel._string);
  CL_INT len = LENGTH_STRING(self);
  char *s1 = self;
  char *s2 = self + len;
  char *mark = s1;
  OID gc_local;
  while(s1 < s2)
   { GC_LOOP;     
     while(s1 < s2 && memcmp(s1,sep,seplen)) s1++;
     if(s1 >= s2) break;
     EXPLODE_ADD(l, mark, s1 - mark)
     s1 += seplen;
     mark = s1;
    GC_UNLOOP;}
   if(s2 - mark)
  	EXPLODE_ADD(l, mark, s2 - mark)
  GC_UNBIND; return l; }



/*********************************************************************/
/**    9. string - encoding/decoding (xl)                            */
/*********************************************************************/


static CL_INT htoi(char *s)
{
	CL_INT value;
	CL_INT c;

	c = s[0];
	if (isupper(c))
		c = tolower(c);
	value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;

	c = s[1];
	if (isupper(c))
		c = tolower(c);
	value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;

	return value;
}

static unsigned char hexchars[] = "0123456789ABCDEF";

char* url_encode_string(char* s)
{
	register CL_INT x, y;
	unsigned char *str;
	CL_INT len = LENGTH_STRING(s);
	ClEnv->bufferStart();
	CL_INT l = 0;
	for(x = 0, y = 0; len--; x++, y++) {
		char c = s[x];
		if (c == ' ') {
			{l++;ClEnv->pushChar('+');}
		} else if ((c < '0' && c != '-' && c != '.') ||
				   (c < 'A' && c > '9') ||
				   (c > 'Z' && c < 'a' && c != '_') ||
				   (c > 'z')) {
			l++;ClEnv->pushChar('%');y++;
			l++;ClEnv->pushChar(hexchars[(unsigned char) s[x] >> 4]);y++;
			l++;ClEnv->pushChar(hexchars[(unsigned char) s[x] & 15]);
		} else {l++;ClEnv->pushChar(s[x]);}
	}
	char *res = ClEnv->bufferCopy();
	return res;
}

char* url_decode_string(char* data)
{
	char *str = data;
	ClEnv->bufferStart();
	CL_INT len = LENGTH_STRING(data);
	CL_INT l = 0;
	while (len--) {
		if (*data == '+') {l++;ClEnv->pushChar(' ');} //*dest = ' ';
		else if (*data == '%' && len >= 2 && isxdigit((CL_INT) *(data + 1)) && isxdigit((CL_INT) *(data + 2))) {
			ClEnv->pushChar((char)htoi(data + 1));
			l++;
			data += 2;
			len -= 2;
		} else
			{l++;ClEnv->pushChar(*data);}
		data++;
	}
	char *res = ClEnv->bufferCopy();
	return res;
}


char *mime_encode_string(char *subject) {
    char *output = 0;
    unsigned char *p, *pDest ;
    CL_INT i, n, len ;

    len = LENGTH_STRING(subject);
    output = new char[len * 3 + 1];
    if(output == 0) Cerror(61, _string_("mime_encode @ string"),0);
    if (output == 0)
        return 0;

    p = (unsigned char*)subject;
    pDest = (unsigned char*)output ;

    for (i = 0; i < len; i++)
    {
        /* XP_IS_ALPHA(*p) || XP_IS_DIGIT(*p)) */
        if (((*p >= 'a') && (*p <= 'z')) ||
             ((*p >= 'A') && (*p <= 'Z')) ||
             ((*p >= '0') && (*p <= '9')))
           *pDest = *p;
        /*if ((*p >= '!' && *p <= '<') ||
        		(*p >= '>' && *p <= '~') ||
        		*p == '\t' || *p == ' ') 
            *pDest = *p;*/
        else
        {
            *pDest++ = '=';
            n = (*p & 0xF0) >> 4; /* high byte */
            if (n < 10)
                *pDest = '0' + n;
            else
                *pDest = 'A' + n - 10;
            pDest ++ ;

            n = *p & 0x0F;          /* low byte */
            if (n < 10)
                *pDest = '0' + n;
            else
                *pDest = 'A' + n - 10;
        }

        p ++;
        pDest ++;
    }

    *pDest = '\0';
    char* res = copy_string1(output, (char*)pDest - output);
    delete output;
    return res;
}

char *mime_decode_string(char *in)
{
    CL_INT i = 0, length = LENGTH_STRING(in);
    char token[3];
    char *out, *dest = 0;

    out = dest = new char[length+1];
    if(dest == 0) Cerror(61, _string_("mime_decode @ string"),0);
    if(dest == 0) return 0;
    memset(out, 0, length+1);
    while (length > 0 || i != 0)
    {
        while (i < 3 && length > 0)
        {
            token [i++] = *in;
            in++;
            length--;
        }

        if (i < 3)
        {
          /* Didn't get enough for a complete token.
             If it might be a token, unread it.
             Otherwise, just dump it.
             */
            strncpy (out, token, i);
            break;
        }
        i = 0;

		if (token [0] == '=')
        {
            unsigned char c = 0;
            if (token[1] >= '0' && token[1] <= '9')
                c = token[1] - '0';
            else if (token[1] >= 'A' && token[1] <= 'F')
                c = token[1] - ('A' - 10);
            else if (token[1] >= 'a' && token[1] <= 'f')
                c = token[1] - ('a' - 10);
            else if (token[1] == '\r' || token[1] == '\n')
            {
                /* =\n means ignore the newline. */
                if (token[1] == '\r' && token[2] == '\n')
                    ;       /* swallow all three chars */
                else
                {
                    in--;   /* put the third char back */
                    length++;
                }
                continue;
            }
            else
            {
                /* = followed by something other than hex or newline -
                 pass it through unaltered, I guess.  (But, if
                 this bogus token happened to occur over a buffer
                 boundary, we can't do this, since we don't have
                 space for it.  Oh well.  Forget it.)  */
                if (in > out) *out++ = token[0];
                if (in > out) *out++ = token[1];
                if (in > out) *out++ = token[2];
                continue;
            }

            /* Second hex digit */
            c = (c << 4);
            if (token[2] >= '0' && token[2] <= '9')
                c += token[2] - '0';
            else if (token[2] >= 'A' && token[2] <= 'F')
                c += token[2] - ('A' - 10);
            else if (token[2] >= 'a' && token[2] <= 'f')
                c += token[2] - ('a' - 10);
            else
            {
                /* We got =xy where "x" was hex and "y" was not, so
                 treat that as a literal "=", x, and y.  (But, if
                 this bogus token happened to occur over a buffer
                 boundary, we can't do this, since we don't have
                 space for it.  Oh well.  Forget it.) */
                if (in > out) *out++ = token[0];
                if (in > out) *out++ = token[1];
                if (in > out) *out++ = token[2];
                continue;
            }

            *out++ = (char) c;
        }
        else
        {
            *out++ = token [0];

            token[0] = token[1];
            token[1] = token[2];
            i = 2;
        }
    }
    /* take care of special underscore case */
    char *bob = dest;
    for (; bob < out; bob++)
        if (*bob == '_')    *bob = ' ';
    
    char* res = copy_string1(dest, out - dest + i);
    delete dest;
    return res;
}


char* escape_string(char* src) {
	char *res = (char*)malloc(LENGTH_STRING(src)*6 + 1);
	if(res == 0) Cerror(61, _string_("escape @ string"),0);
	char *travel = res;
	while(*src) {
		CL_INT c = integer_I_char(_char_(*src));
		if(c < 0) c = 256 + c;
		if(c > 256) c -= 256;
		
		if(c == 9) {strcpy(travel,"&#09;"); travel += 5;}
		else if(c == 10) {strcpy(travel,"&#10;"); travel += 5;}
		else if(c == 13) {strcpy(travel,"&#13;"); travel += 5;}
		else if(c >= 32 && c <= 64) {
			switch(c) {
				case ' ': strcpy(travel,"&nbsp;"); travel += 6; break;
				case '"': strcpy(travel,"&quot;"); travel += 6; break;
				case '\'': strcpy(travel,"&#39;"); travel += 5; break;
				case '<': strcpy(travel,"&lt;"); travel += 4; break;
				case '>': strcpy(travel,"&gt;"); travel += 4; break;
				case '&': strcpy(travel,"&amp;"); travel += 5; break;
				default: *travel++ = c;
			}
		}
		else if(c >= 128 && c <= 255) {
			char buf[8];
			sprintf(buf, "&#%d;", c);
			strcpy(travel, buf); travel += strlen(buf);
		}
		else *travel++ = c;
		src++;
	}
	*travel = 0;
	travel = copy_string1(res, travel - res);
	free(res);
	return travel;
}


void unescapeEOS(char* src) {
	Cerror(62,_string_(src),0); }
void unescapeNUM(char* src) {
	Cerror(63,_string_(src),0); }



char* unescape_string(char* src) {
	#define ELSE_CONV_NAME_NUM(name,len,num) else if(strncmp(src,name,len) == 0) {*travel++ = char_I_integer(num)->ascii; src += len;}
	char *anch = src;
	CL_INT len = LENGTH_STRING(src);
	char *res = (char*)malloc(len+1);
	if(res == 0) Cerror(61, _string_("unescape @ string"),0);
	char *travel = res;
	while(*src) {
		if(*src != '&') *travel++ = *src++;
		else {
			src++;
			if(*src == 0) {*travel++ = '&'; break;}
			if(*src == '#') {
				src++;
				if(*src == 0) unescapeEOS(anch);
				if(*src == 'x' || *src == 'X') {
					src++;
					if(*src == 0) unescapeEOS(anch);
					CL_INT c;
					if(sscanf(src,"%x;",&c) != 1) unescapeNUM(anch);
					while(*src != ';') src++;
					src++;
					*travel++ = char_I_integer(c)->ascii;	
				} else {
					CL_INT c;
					if(sscanf(src,"%d;",&c) != 1) unescapeNUM(anch);
					while(*src != ';') src++;
					src++;
					*travel++ = char_I_integer(c)->ascii;
				}
			}
			else if(strncmp(src,"lt;",3) == 0) {*travel++ = '<'; src += 3;}
			else if(strncmp(src,"gt;",3) == 0) {*travel++ = '>'; src += 3;}
			else if(strncmp(src,"amp;",4) == 0) {*travel++ = '&'; src += 4;}
			else if(strncmp(src,"quot;",5) == 0) {*travel++ = '"'; src += 5;}
			ELSE_CONV_NAME_NUM("yen;",4,165)
			ELSE_CONV_NAME_NUM("uml;",4,168)
			ELSE_CONV_NAME_NUM("not;",4,172)
			ELSE_CONV_NAME_NUM("shy;",4,173)
			ELSE_CONV_NAME_NUM("reg;",4,174)
			ELSE_CONV_NAME_NUM("deg;",4,176)
			ELSE_CONV_NAME_NUM("nbsp;",5,160)
			ELSE_CONV_NAME_NUM("sect;",5,167)
			ELSE_CONV_NAME_NUM("copy;",5,169)
			ELSE_CONV_NAME_NUM("ordf;",5,170)
			ELSE_CONV_NAME_NUM("macr;",5,175)
			ELSE_CONV_NAME_NUM("sup2;",5,178)
			ELSE_CONV_NAME_NUM("sup3;",5,179)
			ELSE_CONV_NAME_NUM("para;",5,182)
			ELSE_CONV_NAME_NUM("sup1;",5,185)
			ELSE_CONV_NAME_NUM("ordm;",5,186)
			ELSE_CONV_NAME_NUM("euro;",5,128)
			ELSE_CONV_NAME_NUM("laquo;",6,171)
			ELSE_CONV_NAME_NUM("iexcl;",6,161)
			ELSE_CONV_NAME_NUM("pound;",6,163)
			ELSE_CONV_NAME_NUM("acute;",6,180)
			ELSE_CONV_NAME_NUM("micro;",6,181)
			ELSE_CONV_NAME_NUM("cedil;",6,184)
			ELSE_CONV_NAME_NUM("raquo;",6,187)
			ELSE_CONV_NAME_NUM("curren;",7,164)
			ELSE_CONV_NAME_NUM("brvbar;",7,166)
			ELSE_CONV_NAME_NUM("plusmn;",7,177)
			ELSE_CONV_NAME_NUM("middot;",7,183)
			ELSE_CONV_NAME_NUM("frac14;",7,188)
			ELSE_CONV_NAME_NUM("frac12;",7,189)
			ELSE_CONV_NAME_NUM("frac34;",7,190)
			ELSE_CONV_NAME_NUM("iquest;",7,191)
			ELSE_CONV_NAME_NUM("Agrave;",7,192)
			ELSE_CONV_NAME_NUM("Aacute;",7,193)
			ELSE_CONV_NAME_NUM("Acirc;",6,194)
			ELSE_CONV_NAME_NUM("Atilde;",7,195)
			ELSE_CONV_NAME_NUM("Auml;",5,196)
			ELSE_CONV_NAME_NUM("Aring;",6,197)
			ELSE_CONV_NAME_NUM("AElig;",6,198)
			ELSE_CONV_NAME_NUM("Ccedil;",7,199)
			ELSE_CONV_NAME_NUM("Egrave;",7,200)
			ELSE_CONV_NAME_NUM("Eacute;",7,201)
			ELSE_CONV_NAME_NUM("Ecirc;",6,202)
			ELSE_CONV_NAME_NUM("Euml;",5,203)
			ELSE_CONV_NAME_NUM("Igrave;",7,204)
			ELSE_CONV_NAME_NUM("Iacute;",7,205)
			ELSE_CONV_NAME_NUM("Icirc;",6,206)
			ELSE_CONV_NAME_NUM("Iuml;",5,207)
			ELSE_CONV_NAME_NUM("ETH;",4,208)
			ELSE_CONV_NAME_NUM("Ntilde;",7,209)
			ELSE_CONV_NAME_NUM("Ograve;",7,210)
			ELSE_CONV_NAME_NUM("Oacute;",7,211)
			ELSE_CONV_NAME_NUM("Ocirc;",6,212)
			ELSE_CONV_NAME_NUM("Otilde;",7,213)
			ELSE_CONV_NAME_NUM("Ouml;",5,214)
			ELSE_CONV_NAME_NUM("times;",6,215)
			ELSE_CONV_NAME_NUM("Oslash;",7,216)
			ELSE_CONV_NAME_NUM("Ugrave;",7,217)
			ELSE_CONV_NAME_NUM("Uacute;",7,218)
			ELSE_CONV_NAME_NUM("Ucirc;",6,219)
			ELSE_CONV_NAME_NUM("Uuml;",5,220)
			ELSE_CONV_NAME_NUM("Yacute;",7,221)
			ELSE_CONV_NAME_NUM("THORN;",6,222)
			ELSE_CONV_NAME_NUM("szlig;",5,223)
			ELSE_CONV_NAME_NUM("agrave;",7,224)
			ELSE_CONV_NAME_NUM("aacute;",7,225)
			ELSE_CONV_NAME_NUM("acirc;",6,226)
			ELSE_CONV_NAME_NUM("atilde;",7,227)
			ELSE_CONV_NAME_NUM("auml;",5,228)
			ELSE_CONV_NAME_NUM("aring;",6,229)
			ELSE_CONV_NAME_NUM("aelig;",6,230)
			ELSE_CONV_NAME_NUM("ccedil;",7,231)
			ELSE_CONV_NAME_NUM("egrave;",7,232)
			ELSE_CONV_NAME_NUM("eacute;",7,233)
			ELSE_CONV_NAME_NUM("ecirc;",6,234)
			ELSE_CONV_NAME_NUM("euml;",5,235)
			ELSE_CONV_NAME_NUM("igrave;",7,236)
			ELSE_CONV_NAME_NUM("iacute;",7,237)
			ELSE_CONV_NAME_NUM("icirc;",6,238)
			ELSE_CONV_NAME_NUM("iuml;",5,239)
			ELSE_CONV_NAME_NUM("eth;",4,240)
			ELSE_CONV_NAME_NUM("ntilde;",7,241)
			ELSE_CONV_NAME_NUM("ograve;",7,242)
			ELSE_CONV_NAME_NUM("oacute;",7,243)
			ELSE_CONV_NAME_NUM("ocirc;",6,244)
			ELSE_CONV_NAME_NUM("otilde;",7,245)
			ELSE_CONV_NAME_NUM("ouml;",5,246)
			ELSE_CONV_NAME_NUM("divide;",7,247)
			ELSE_CONV_NAME_NUM("oslash;",7,248)
			ELSE_CONV_NAME_NUM("ugrave;",7,249)
			ELSE_CONV_NAME_NUM("uacute;",7,250)
			ELSE_CONV_NAME_NUM("ucirc;",6,251)
			ELSE_CONV_NAME_NUM("uuml;",5,252)
			ELSE_CONV_NAME_NUM("yacute;",7,253)
			ELSE_CONV_NAME_NUM("thorn;",6,254)
			ELSE_CONV_NAME_NUM("yuml;",5,255)
			else {*travel++ = '&'; *travel++ = *src++; }
			//else unescapeEOS(anch);
		}
	}
	*travel = 0;
	travel = copy_string1(res, travel-res);
	free(res);
	return travel;
}



/*********************************************************************/
/**    10. string - base64 encoding/decoding (xl)                    */
/*********************************************************************/

static const char cb64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char cd64[]="|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";

void encodeblock( unsigned char in[3], unsigned char out[4], CL_INT len )
{
    out[0] = cb64[ in[0] >> 2 ];
    out[1] = cb64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? cb64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? cb64[ in[2] & 0x3f ] : '=');
}

void encode64_port(PortObject *infile, PortObject *outfile, CL_INT linesize) {
    unsigned char in[3], out[4];
    CL_INT i, len, blocksout = 0;
	CL_INT eof = 0;
	if (linesize <= 4) linesize = 80;
    while( !eof ) {
		in[0] = 0; in[1] = 0; in[2] = 0;
        len = Core.read_port->fcall((CL_INT)infile, (CL_INT)in, 3);
        eof = len == 0; 
        if( len ) {
            encodeblock( in, out, len );
            Core.write_port->fcall((CL_INT)outfile, (CL_INT)out, 4);
            blocksout++;
        }
        if(!eof && blocksout >= (linesize/4)) {
			Core.write_port->fcall((CL_INT)outfile, (CL_INT)"\r\n", 2);
            blocksout = 0;
        }
    }
}

void decodeblock( unsigned char in[4], unsigned char out[3] )
{   
    out[ 0 ] = (unsigned char ) (in[0] << 2 | in[1] >> 4);
    out[ 1 ] = (unsigned char ) (in[1] << 4 | in[2] >> 2);
    out[ 2 ] = (unsigned char ) (((in[2] << 6) & 0xc0) | in[3]);
}

void decode64_port(PortObject *infile, PortObject *outfile) {
    unsigned char in[4], out[3], v;
    CL_INT i, len;
	CL_INT eof = 0;
	
    while( !eof ) {
        for( len = 0, i = 0; i < 4 && !eof; i++ ) {
            v = 0;
            while( !eof && v == 0 ) {
				eof = Core.read_port->fcall((CL_INT)infile, (CL_INT)&v, 1) == 0;
                v = (unsigned char) ((v < 43 || v > 122) ? 0 : cd64[ v - 43 ]);
                if( v ) {
                    v = (unsigned char) ((v == '$') ? 0 : v - 61);
                }
            }
            if(!eof) {
                len++;
				if( v ) {	
                    in[ i ] = (unsigned char) (v - 1);
                }
			}
			else in[i] = 0;
        }
        if( len ) {
            decodeblock( in, out );
			Core.write_port->fcall((CL_INT)outfile, (CL_INT)out, len - 1);
        }
    }
}

