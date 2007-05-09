#ifndef UTIL_OBJECTTABLE_H
#define UTIL_OBJECTTABLE_H

#include <Lang/Type.h>

#define RIVA_MODULE Util$ObjectTable
#include <Riva-Header.h>

typedef struct Util$ObjectTable_t {
	Lang$Type_t *Type;
	unsigned long Size, Space;
	void *Entries;
} Util$ObjectTable_t;

extern Lang$Type_t Util$ObjectTable$T[];

#define UTIL_OBJECTTABLE_INIT {Util$ObjectTable$T, 0, 0, 0}

RIVA_CFUN(void, init, Util$ObjectTable_t *Table);
RIVA_CFUN(void, put, Util$ObjectTable_t *Table, Lang$Object_t *Key, void *Value);
RIVA_CFUN(void *, get, const Util$ObjectTable_t *Table, Lang$Object_t *Key);

#undef RIVA_MODULE

#endif
