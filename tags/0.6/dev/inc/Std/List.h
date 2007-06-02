#ifndef LANG_LIST_H
#define LANG_LIST_H

#include <Std/Object.h>

#define RIVA_MODULE Std$List
#include <Riva-Header.h>

typedef struct Std$List_node {
	struct Std$List_node *Next, *Prev;
	Std$Object_t *Value;
} Std$List_node;

typedef struct Std$List_t {
	Std$Type_t *Type;
	Std$List_node *Head, *Tail, *Cache, **Array;
	unsigned long Length;
	unsigned long Index, Lower, Upper, Access;
} Std$List_t;

extern Std$Type_t Std$List$T[];
extern Std$Object_t Std$List$New[];
extern Std$Object_t Std$List$Make[];

RIVA_CFUN(Std$Object_t *, new, long, ...);
RIVA_CFUN(Std$Object_t *, newv, long, Std$Object_t **);

#undef RIVA_MODULE

#endif
