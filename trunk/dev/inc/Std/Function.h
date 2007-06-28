#ifndef LANG_FUNCTION_H
#define LANG_FUNCTION_H

#include <Std/Object.h>

#define RIVA_MODULE Std$Function
#include <Riva-Header.h>

typedef struct Std$Function_argument {
	Std$Object_t *Val;
	Std$Object_t **Ref;
} Std$Function_argument;

typedef struct Std$Function_result {
	union {
		struct {
			Std$Object_t *Val;
			Std$Object_t **Ref;
		};
		Std$Function_argument Arg;
	};
	void *State;
} Std$Function_result;

#define SUSPEND -1
#define SUCCESS 0
#define FAILURE 1
#define MESSAGE 2

typedef struct Std$Object_t Std$Function_t;

typedef struct Std$Function_asmt Std$Function_asmt;
typedef struct Std$Function_checkedasmt Std$Function_checkedasmt;
typedef struct Std$Function_ct Std$Function_ct;
typedef struct Std$Function_checkedct Std$Function_checkedct;
typedef struct Std$Function_cstate Std$Function_cstate;
typedef struct Std$Function_cresumedata Std$Function_cresumedata;

struct Std$Function_asmt {
	Std$Type_t *Type;
	void *Invoke;
};

struct Std$Function_checkedasmt {
	Std$Type_t *Type;
	Std$Function_t Target;
};

struct Std$Function_ct {
	Std$Type_t *Type;
	long (*Invoke)(Std$Function_ct *, unsigned long, Std$Function_argument *, Std$Function_result *);
};

struct Std$Function_checkedct {
	Std$Type_t *Type;
	long (*Invoke)(Std$Function_checkedct *, unsigned long, Std$Function_argument *, Std$Function_result *);
	int Count;
	const char *File;
	int Line;
};

struct Std$Function_cresumedata {
	Std$Function_cstate *State;
	Std$Function_argument Result;
};

struct Std$Function_cstate {
	void *Run, *Resume, *Chain;
	long (* Invoke)(Std$Function_cresumedata *Data);
};

extern Std$Type_t Std$Function$T[];
extern Std$Type_t Std$Function$CT[];
extern Std$Type_t Std$Function$CheckedCT[];

RIVA_CFUN(long, resume_c, Std$Function_cresumedata *);
RIVA_CFUN(long, invoke, Std$Object_t *, long, Std$Function_result *, Std$Function_argument *);
RIVA_CFUN(long, call, Std$Object_t *, long, Std$Function_result *, ...);
RIVA_CFUN(long, resume, Std$Function_result *);

#define LOCAL_FUNCTION(NAME)\
	static long invoke_ ## NAME(Std$Function_ct *Fun, unsigned long Count, Std$Function_argument *Args, Std$Function_result *Result);\
	static Std$Function_ct NAME = {Std$Function$CT, invoke_ ## NAME};\
	static long invoke_ ## NAME(Std$Function_ct *Fun, unsigned long Count, Std$Function_argument *Args, Std$Function_result *Result)

#define GLOBAL_FUNCTION(NAME, COUNT)\
	static long invoke_ ## NAME(Std$Function_checkedct *Fun, unsigned long Count, Std$Function_argument *Args, Std$Function_result *Result);\
	Std$Function_checkedct NAME = {Std$Function$CheckedCT, invoke_ ## NAME, COUNT, __FILE__, __LINE__};\
	static long invoke_ ## NAME(Std$Function_checkedct *Fun, unsigned long Count, Std$Function_argument *Args, Std$Function_result *Result)

#undef RIVA_MODULE

#endif
