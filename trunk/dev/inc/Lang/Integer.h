#ifndef LANG_INTEGER_H
#define LANG_INTEGER_H

#include <Lang/Object.h>

#define RIVA_MODULE Lang$Integer
#include <Riva-Header.h>

typedef struct Lang$Integer_smallt Lang$Integer_smallt;
typedef struct Lang$Integer_bigt Lang$Integer_bigt;

struct Lang$Integer_smallt {
	Lang$Type_t *Type;
	long Value;
};

struct Lang$Integer_bigt {
	Lang$Type_t *Type;
	//mpz_t Value;
};

extern Lang$Type_t Lang$Integer$SmallT[];
extern Lang$Type_t Lang$Integer$BigT[];

RIVA_CFUN(Lang$Integer_smallt *, new_small, long);
//RIVA_CFUN(Lang$Object_t *, new_big, mpz_t);
RIVA_CFUN(Lang$Object_t *, new_string, const char *);

#undef RIVA_MODULE

#endif
