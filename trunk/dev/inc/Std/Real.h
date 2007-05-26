#ifndef LANG_REAL_H
#define LANG_REAL_H

#include <Std/Object.h>

#define RIVA_MODULE Std$Real
#include <Riva-Header.h>

typedef struct Std$Real_t Std$Real_t;

struct Std$Real_t {
	Std$Type_t *Type;
	double Value;
};

extern Std$Type_t Std$Real$T[];

RIVA_CFUN(Std$Real_t *, new, double);
RIVA_CFUN(Std$Real_t *, new_string, const char *);

#undef RIVA_MODULE

#endif
