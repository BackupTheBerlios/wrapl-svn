#ifndef RIVA_CONFIG_H
#define RIVA_CONFIG_H
#define RIVA_MODULE Riva$Config
#include <Riva-Header.h>

RIVA_CFUN(const char *, get, const char *);
RIVA_CFUN(void, set, const char *, const char *);

#undef RIVA_MODULE

#endif
