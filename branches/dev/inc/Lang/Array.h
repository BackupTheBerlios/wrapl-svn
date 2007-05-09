#ifndef LANG_ARRAY_H
#define LANG_ARRAY_H

#include <Lang/Object.h>

#define RIVA_MODULE Lang$Array
#include <Riva-Header.h>

typedef struct Lang$Array_t Lang$Array_t;

struct Lang$Array_t {
	Lang$Type_t *Type;
	Lang$Integer_smallt Length;
	Lang$Object_t **Values;
};

extern Lang$Type_t Lang$Array$T[];

RIVA_CFUN(Lang$Array_t *, new, int);

#undef RIVA_MODULE

#endif
