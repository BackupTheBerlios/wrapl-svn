#ifndef SYS_MODULE_H
#define SYS_MODULE_H

#include <Lang/Object.h>
#include <Riva/Module.h>

#define RIVA_MODULE Sys$Module
#include <Riva-Header.h>

typedef struct Sys$Module_t Sys$Module_t;

struct Sys$Module_t {
	Lang$Type_t *Type;
	Riva$Module_t *Handle;
};

extern Lang$Type_t Sys$Module$T[];

RIVA_CFUN(Sys$Module_t *, new);
RIVA_CFUN(Sys$Module_t *, load, const char *, const char *);
RIVA_CFUN(int, import, Sys$Module_t *, const char *, int *, void **);
RIVA_CFUN(void, export, Sys$Module_t *, const char *, int, void *);

RIVA_CFUN(void, set_path, Sys$Module_t *, const char *);
RIVA_CFUN(const char *, get_path, Sys$Module_t *);

#undef RIVA_MODULE

#endif
