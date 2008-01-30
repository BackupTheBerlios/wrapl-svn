#ifndef SYS_TIME_H
#define SYS_TIME_H

#include <Std/Object.h>

#define RIVA_MODULE Sys$Time
#include <Riva-Header.h>

#include <time.h>

typedef struct Sys$Time_t Sys$Time_t;

struct Sys$Time_t {
	Std$Type_t *Type;
	time_t Value;
};

extern Std$Type_t Sys$Time$T[];

RIVA_CFUN(Sys$Time_t *, new, time_t);

#undef RIVA_MODULE

#endif
