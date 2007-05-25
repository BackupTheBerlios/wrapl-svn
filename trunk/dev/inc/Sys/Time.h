#ifndef SYS_TIME_H
#define SYS_TIME_H

#include <Lang/Object.h>

#define RIVA_MODULE Sys$Time
#include <Riva-Header.h>

typedef struct Sys$Time_t Sys$Time_t;

struct Sys$Module_t {
	Lang$Type_t *Type;
};

extern Lang$Type_t Sys$Time$T[];

#undef RIVA_MODULE

#endif
