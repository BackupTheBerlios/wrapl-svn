#ifndef LANG_LIST_H
#define LANG_LIST_H

#include <Lang/Object.h>

#define RIVA_MODULE Lang$List
#include <Riva-Header.h>

typedef struct Lang$List_node {
	struct Lang$List_node *Next, *Prev;
	Lang$Object_t *Value;
} Lang$List_node;

typedef struct Lang$List_t {
	Lang$Type_t *Type;
	Lang$List_node *Head, *Tail, *Cache, **Array;
	unsigned long Length;
	unsigned long Index, Lower, Upper, Access;
} Lang$List_t;

extern Lang$Type_t Lang$List$T[];
extern Lang$Object_t Lang$List$New[];
extern Lang$Object_t Lang$List$Make[];

RIVA_CFUN(Lang$Object_t *, new, long, ...);
RIVA_CFUN(Lang$Object_t *, newv, long, Lang$Object_t **);

#undef RIVA_MODULE

#endif
