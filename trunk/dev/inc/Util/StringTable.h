#ifndef UTIL_STRINGTABLE_H
#define UTIL_STRINGTABLE_H

#include <Std/Type.h>

#define RIVA_MODULE Util$StringTable
#include <Riva-Header.h>

typedef struct Util$StringTable_node {
	const char *Key;
	unsigned long Length, Hash;
	void *Value;
} Util$StringTable_node;

typedef struct Util$StringTable_t {
	Std$Type_t *Type;
	unsigned long Size, Space;
	Util$StringTable_node *Entries;
} Util$StringTable_t;

extern Std$Type_t Util$StringTable$T[];

#define Util$StringTable$INIT {Util$StringTable$T, 0, 0, 0}

RIVA_CFUN(void, init, Util$StringTable_t *Table);
RIVA_CFUN(void, put, Util$StringTable_t *Table, const char *Key, void *Value);
RIVA_CFUN(void *, get, const Util$StringTable_t *Table, const char *Key);

#undef RIVA_MODULE

#endif
