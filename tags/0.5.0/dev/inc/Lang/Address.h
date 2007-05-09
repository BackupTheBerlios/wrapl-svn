#ifndef LANG_ADDRESS_H
#define LANG_ADDRESS_H

#include <Lang/Object.h>

#define RIVA_MODULE Lang$Address
#include <Riva-Header.h>

typedef struct Lang$Address_t Lang$Address_t;

struct Lang$Address_t {
	Lang$Type_t *Type;
	void *Value;
};

extern Lang$Type_t Lang$Address$T[];

RIVA_CFUN(Lang$Address_t *, new, void *);

#undef RIVA_MODULE

#endif
