#ifndef UTIL_INTEGERTABLE_H
#define UTIL_INTEGERTABLE_H

#include <Std/Object.h>

#define RIVA_MODULE Util$IntegerTable
#include <Riva-Header.h>

typedef struct Util$IntegerTable_t {
	Std$Type_t *Type;
	unsigned long Size, Space;
	void *Entries;
} Util$IntegerTable_t;

extern Std$Type_t Util$IntegerTable$T[];

RIVA_CFUN(void, init, Util$IntegerTable_t *Table);
RIVA_CFUN(void, put, Util$IntegerTable_t *Table, unsigned long Key, void *Value);
RIVA_CFUN(void *, get, const Util$IntegerTable_t *Table, unsigned long Key);

#undef RIVA_MODULE

#endif
