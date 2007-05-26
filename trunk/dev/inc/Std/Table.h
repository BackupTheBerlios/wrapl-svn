#ifndef LANG_TABLE_H
#define LANG_TABLE_H

#include <Lang/Object.h>

#define RIVA_MODULE Lang$Table
#include <Riva-Header.h>

extern Lang$Type_t Lang$Table$T[];
RIVA_CFUN(Lang$Object_t *, new, long, ...);
extern Lang$Object_t Lang$Table$New[];
extern Lang$Object_t Lang$Table$Make[];

#undef RIVA_MODULE

#endif
