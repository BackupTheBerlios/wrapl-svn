#ifndef LANG_ARRAY_H
#define LANG_ARRAY_H

#include <Std/Object.h>

#define RIVA_MODULE Std$Array
#include <Riva-Header.h>

typedef struct Std$Array_t Std$Array_t;

struct Std$Array_t {
	Std$Type_t *Type;
	Std$Integer_smallt Length;
	Std$Object_t **Values;
};

extern Std$Type_t Std$Array$T[];

RIVA_CFUN(Std$Array_t *, new, int);

#undef RIVA_MODULE

#endif
