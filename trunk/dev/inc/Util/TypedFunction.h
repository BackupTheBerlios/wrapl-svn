#ifndef UTIL_TYPED_FUNCTION_H
#define UTIL_TYPED_FUNCTION_H

#include <stdint.h>

#define RIVA_MODULE Util$TypedFunction
#include <Riva-Header.h>

RIVA_CFUN(void *, get, void *, Std$Type_t *);
RIVA_CFUN(void, set, void *, Std$Type_t *, void *);

#undef RIVA_MODULE

#endif
