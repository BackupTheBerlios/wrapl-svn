#ifndef LANG_INTEGER_H
#define LANG_INTEGER_H

#include <Std/Object.h>

#define RIVA_MODULE Std$Integer
#include <Riva-Header.h>

typedef struct Std$Integer_smallt Std$Integer_smallt;
typedef struct Std$Integer_bigt Std$Integer_bigt;

struct Std$Integer_smallt {
	Std$Type_t *Type;
	long Value;
};

struct Std$Integer_bigt {
	Std$Type_t *Type;
	//mpz_t Value;
};

extern Std$Type_t Std$Integer$SmallT[];
extern Std$Type_t Std$Integer$BigT[];

RIVA_CFUN(Std$Integer_smallt *, new_small, long);
//RIVA_CFUN(Std$Object_t *, new_big, mpz_t);
RIVA_CFUN(Std$Object_t *, new_string, const char *);

#undef RIVA_MODULE

#endif
