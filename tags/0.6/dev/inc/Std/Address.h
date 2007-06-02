#ifndef LANG_ADDRESS_H
#define LANG_ADDRESS_H

#include <Std/Object.h>

#define RIVA_MODULE Std$Address
#include <Riva-Header.h>

typedef struct Std$Address_t Std$Address_t;

struct Std$Address_t {
	Std$Type_t *Type;
	void *Value;
};

extern Std$Type_t Std$Address$T[];

RIVA_CFUN(Std$Address_t *, new, void *);

#undef RIVA_MODULE

#endif
