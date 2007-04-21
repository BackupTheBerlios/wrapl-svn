#ifndef LANG_OBJECT_H
#define LANG_OBJECT_H

#include <Lang/Type.h>

#define RIVA_MODULE Lang$Object
#include <Riva-Header.h>

typedef struct Lang$Object_t Lang$Object_t;

struct Lang$Object_t {
	Lang$Type_t *Type;
};

extern Lang$Type_t Lang$Object$T[];
extern Lang$Object_t Lang$Object$Nil[];

#undef RIVA_MODULE

#endif
