#ifndef UTIL_STRINGTABLE_H
#define UTIL_STRINGTABLE_H

#include <Lang/Type.h>

#define RIVA_MODULE Util$StringTable
#include <Riva-Header.h>

typedef struct Util$StringTable_t {
	Lang$Type_t *Type;
	unsigned long Size, Space;
	void *Entries;
} Util$StringTable_t;

extern Lang$Type_t Util$StringTable$T[];

#define Util$StringTable$INIT {Util$StringTable$T, 0, 0, 0}

RIVA_CFUN(void, init, Util$StringTable_t *Table);
RIVA_CFUN(void, put, Util$StringTable_t *Table, const char *Key, void *Value);
RIVA_CFUN(void *, get, const Util$StringTable_t *Table, const char *Key);

#undef RIVA_MODULE

#endif
