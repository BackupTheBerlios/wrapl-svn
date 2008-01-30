#ifndef LANG_OBJECT_H
#define LANG_OBJECT_H

#include <Std/Type.h>

#define RIVA_MODULE Std$Object
#include <Riva-Header.h>

typedef struct Std$Object_t Std$Object_t;

struct Std$Object_t {
	Std$Type_t *Type;
};

extern Std$Type_t Std$Object$T[];
extern Std$Object_t Std$Object$Nil[];

#undef RIVA_MODULE

#define CONSTANT(NAME)\
static Std$Object_t *init_ ## NAME(void);\
Std$Object_t NAME[] __attribute__ ((section (".constants"))) = {{(Std$Object_t *)&init_ ## NAME}};\
static Std$Object_t *init_ ## NAME(void)

#endif
