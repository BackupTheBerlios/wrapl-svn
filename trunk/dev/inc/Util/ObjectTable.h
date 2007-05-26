#ifndef UTIL_OBJECTTABLE_H
#define UTIL_OBJECTTABLE_H

#include <Std/Type.h>

#define RIVA_MODULE Util$ObjectTable
#include <Riva-Header.h>

typedef struct Util$ObjectTable_t {
	Std$Type_t *Type;
	unsigned long Size, Space;
	void *Entries;
} Util$ObjectTable_t;

extern Std$Type_t Util$ObjectTable$T[];

#define UTIL_OBJECTTABLE_INIT {Util$ObjectTable$T, 0, 0, 0}

RIVA_CFUN(void, init, Util$ObjectTable_t *Table);
RIVA_CFUN(void, put, Util$ObjectTable_t *Table, Std$Object_t *Key, void *Value);
RIVA_CFUN(void *, get, const Util$ObjectTable_t *Table, Std$Object_t *Key);

#undef RIVA_MODULE

#endif
