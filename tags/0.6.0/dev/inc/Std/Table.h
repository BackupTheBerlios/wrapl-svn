#ifndef LANG_TABLE_H
#define LANG_TABLE_H

#include <Std/Object.h>

#define RIVA_MODULE Std$Table
#include <Riva-Header.h>

extern Std$Type_t Std$Table$T[];
RIVA_CFUN(Std$Object_t *, new, long, ...);
extern Std$Object_t Std$Table$New[];
extern Std$Object_t Std$Table$Make[];

#undef RIVA_MODULE

#endif
