#ifndef UTIL_TYPETABLE_H
#define UTIL_TYPETABLE_H

#include <Std/Type.h>

#define RIVA_MODULE Util$TypeTable
#include <Riva-Header.h>

typedef struct Util$TypeTable_t {
	Std$Type_t *Type;
	unsigned long Size, Space;
	void *Entries;
} Util$TypeTable_t;

extern Std$Type_t Util$TypeTable$T[];

#define Util$TypeTable$INIT {Util$TypeTable$T, 0, 0, 0}

RIVA_CFUN(void, init, Util$TypeTable_t *Table);
RIVA_CFUN(void, put, Util$TypeTable_t *Table, Std$Type_t *Key, void *Value);
RIVA_CFUN(void *, get, const Util$TypeTable_t *Table, Std$Type_t *Key);

#undef RIVA_MODULE

#endif
