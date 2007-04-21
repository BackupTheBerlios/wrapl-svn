#ifndef LANG_TYPE_H
#define LANG_TYPE_H

#define RIVA_MODULE Lang$Type
#include <Riva-Header.h>

typedef struct Lang$Array_t Lang$Type_fields;

typedef struct Lang$Type_t Lang$Type_t;

struct Lang$Type_t {
	Lang$Type_t *Type;
	Lang$Type_t **Types;
	void *Invoke;
	Lang$Type_fields *Fields;
	unsigned long *Levels;
};

extern Lang$Type_t Lang$Type$T[];

#define TYPE(NAME, PARENTS...)\
	extern Lang$Type_t *NAME ## _parents[];\
	Lang$Type_t NAME[] = {{Lang$Type$T, NAME ## _parents}};\
	Lang$Type_t *NAME ## _parents[] = {NAME, ## PARENTS, 0}

#define ITYPE(NAME, LEVELS, PARENTS...)\
	extern Lang$Type_t *NAME ## _parents[];\
	Lang$Type_fields NAME ## _fields[] = {{\
		Lang$Array$T, \
		{Lang$Integer$SmallT, 0}\
	}};\
	unsigned long NAME ## _levels[] = LEVELS_ ## LEVELS;\
	Lang$Type_t NAME[] = {{\
		Lang$Type$T, \
		NAME ## _parents, \
		0, \
		NAME ## _fields, \
		NAME ## _levels\
	}};\
	Lang$Type_t *NAME ## _parents[] = {NAME, ## PARENTS, 0}

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
