#ifndef RIVA_MODULE_H
#define RIVA_MODULE_H

#define RIVA_MODULE Riva$Module
#include <Riva-Header.h>

typedef struct Riva$Module_t Riva$Module_t;

typedef int (*Riva$Module_loader)(Riva$Module_t *, const char *);
typedef int (*Riva$Module_importer)(void *, const char *, int *, void **);

RIVA_CFUN(void, add_loader, const char *, Riva$Module_loader);
RIVA_CFUN(void, add_directory, const char *);
RIVA_CFUN(Riva$Module_t *, setup, Riva$Module_t *, void *, Riva$Module_importer);
RIVA_CFUN(Riva$Module_t *, alias, const char *, void *, Riva$Module_importer);
RIVA_CFUN(Riva$Module_t *, load, const char *, const char *);
RIVA_CFUN(Riva$Module_t *, load_file, const char *);
RIVA_CFUN(Riva$Module_t *, run, const char *, const char *);

RIVA_CFUN(int,  import, Riva$Module_t *, const char *, int *, void **);
RIVA_CFUN(void, export, Riva$Module_t *, const char *, int, void *);

RIVA_CFUN(void, set_path, Riva$Module_t *, const char *);
RIVA_CFUN(const char *, get_path, Riva$Module_t *);

RIVA_CFUN(int, lookup, void *, char **, char **);

#undef RIVA_MODULE

#endif
