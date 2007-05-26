#ifndef LANG_REAL_H
#define LANG_REAL_H

#include <Lang/Object.h>

#define RIVA_MODULE Lang$Real
#include <Riva-Header.h>

typedef struct Lang$Real_t Lang$Real_t;

struct Lang$Real_t {
	Lang$Type_t *Type;
	double Value;
};

extern Lang$Type_t Lang$Real$T[];

RIVA_CFUN(Lang$Real_t *, new, double);
RIVA_CFUN(Lang$Real_t *, new_string, const char *);

#undef RIVA_MODULE

#endif
