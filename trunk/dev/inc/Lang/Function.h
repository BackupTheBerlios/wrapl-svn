#ifndef LANG_FUNCTION_H
#define LANG_FUNCTION_H

#include <Lang/Object.h>

#define RIVA_MODULE Lang$Function
#include <Riva-Header.h>

typedef struct Lang$Function_argument {
	Lang$Object_t *Val;
	Lang$Object_t **Ref;
} Lang$Function_argument;

typedef struct Lang$Function_result {
	union {
		struct {
			Lang$Object_t *Val;
			Lang$Object_t **Ref;
		};
		Lang$Function_argument Arg;
	};
	void *State;
} Lang$Function_result;

#define SUSPEND -1
#define SUCCESS 0
#define FAILURE 1
#define MESSAGE 2

typedef struct Lang$Function_asmt Lang$Function_asmt;
typedef struct Lang$Function_ct Lang$Function_ct;
typedef struct Lang$Function_checkedct Lang$Function_checkedct;
typedef struct Lang$Function_cstate Lang$Function_cstate;
typedef struct Lang$Function_cresumedata Lang$Function_cresumedata;

struct Lang$Function_asmt {
	Lang$Type_t *Type;
	void *Invoke;
};

struct Lang$Function_ct {
	Lang$Type_t *Type;
	long (*Invoke)(Lang$Function_ct *, unsigned long, Lang$Function_argument *, Lang$Function_result *);
};

struct Lang$Function_checkedct {
	Lang$Type_t *Type;
	long (*Invoke)(Lang$Function_checkedct *, unsigned long, Lang$Function_argument *, Lang$Function_result *);
	int Count;
	const char *File;
	int Line;
};

struct Lang$Function_cresumedata {
	Lang$Function_cstate *State;
	Lang$Function_argument Result;
};

struct Lang$Function_cstate {
	void *Run, *Resume, *Chain[2];
	long (* Invoke)(Lang$Function_cresumedata *Data);
};

extern Lang$Type_t Lang$Function$T[];
extern Lang$Type_t Lang$Function$CT[];
extern Lang$Type_t Lang$Function$CheckedCT[];

RIVA_CFUN(long, resume_c, Lang$Function_cresumedata *);
RIVA_CFUN(long, invoke, Lang$Object_t *, long, Lang$Function_result *, Lang$Function_argument *);
RIVA_CFUN(long, call, Lang$Object_t *, long, Lang$Function_result *, ...);
RIVA_CFUN(long, resume, Lang$Function_result *);

#define LOCAL_FUNCTION(NAME)\
	static long invoke_ ## NAME(Lang$Function_ct *Fun, unsigned long Count, Lang$Function_argument *Args, Lang$Function_result *Result);\
	static Lang$Function_ct NAME = {Lang$Function$CT, invoke_ ## NAME};\
	static long invoke_ ## NAME(Lang$Function_ct *Fun, unsigned long Count, Lang$Function_argument *Args, Lang$Function_result *Result)

#define GLOBAL_FUNCTION(NAME, COUNT)\
	static long invoke_ ## NAME(Lang$Function_checkedct *Fun, unsigned long Count, Lang$Function_argument *Args, Lang$Function_result *Result);\
	Lang$Function_checkedct NAME = {Lang$Function$CheckedCT, invoke_ ## NAME, COUNT, __FILE__, __LINE__};\
	static long invoke_ ## NAME(Lang$Function_checkedct *Fun, unsigned long Count, Lang$Function_argument *Args, Lang$Function_result *Result)

#undef RIVA_MODULE

#endif
