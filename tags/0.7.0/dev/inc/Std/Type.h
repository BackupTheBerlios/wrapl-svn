#ifndef LANG_TYPE_H
#define LANG_TYPE_H

#define RIVA_MODULE Std$Type
#include <Riva-Header.h>

typedef struct Std$Array_t Std$Type_fields;

typedef struct Std$Type_t Std$Type_t;

struct Std$Type_t {
	Std$Type_t *Type;
	Std$Type_t **Types;
	void *Invoke;
	Std$Type_fields *Fields;
	unsigned long *Levels;
};

extern Std$Type_t Std$Type$T[];

#define TYPE(NAME, PARENTS...)\
	extern Std$Type_t *NAME ## _parents[];\
	Std$Type_t NAME[] = {{Std$Type$T, NAME ## _parents}};\
	Std$Type_t *NAME ## _parents[] = {NAME, ## PARENTS, 0}

#define ITYPE(NAME, LEVELS, PARENTS...)\
	extern Std$Type_t *NAME ## _parents[];\
	Std$Type_fields NAME ## _fields[] = {{\
		Std$Array$T, \
		{Std$Integer$SmallT, 0}\
	}};\
	unsigned long NAME ## _levels[] = LEVELS_ ## LEVELS;\
	Std$Type_t NAME[] = {{\
		Std$Type$T, \
		NAME ## _parents, \
		0, \
		NAME ## _fields, \
		NAME ## _levels\
	}};\
	Std$Type_t *NAME ## _parents[] = {NAME, ## PARENTS, 0}

#define LEVELS_1 {1, 0}
#define LEVELS_2 {2, 0, 1}
#define LEVELS_3 {3, 0, 1, 2}
#define LEVELS_4 {4, 0, 1, 2, 3}
#define LEVELS_5 {5, 0, 1, 2, 3, 4}
#define LEVELS_6 {6, 0, 1, 2, 3, 4, 5}
#define LEVELS_7 {7, 0, 1, 2, 3, 4, 5, 6}
#define LEVELS_8 {8, 0, 1, 2, 3, 4, 5, 6, 7}

#undef RIVA_MODULE

#endif
