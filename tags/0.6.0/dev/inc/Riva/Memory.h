#ifndef RIVA_MEMORY_H
#define RIVA_MEMORY_H

#define RIVA_MODULE Riva$Memory
#include <Riva-Header.h>

RIVA_CFUN(void, collect, void);

RIVA_CFUN(void *, alloc, unsigned int);
RIVA_CFUN(void *, alloc_stubborn, unsigned int);
RIVA_CFUN(void *, alloc_uncollectable, unsigned int);
RIVA_CFUN(void *, alloc_atomic, unsigned int);
RIVA_CFUN(void *, alloc_small, unsigned int);
RIVA_CFUN(void *, realloc, void *, unsigned int);
RIVA_CFUN(void, free, void *);
RIVA_CFUN(unsigned int, size, void *);

#ifndef __cplusplus
#ifndef new
#define new(T) ((T *)Riva$Memory$alloc(sizeof(T)))
#endif
#else
inline void *operator new(unsigned int Size) {return Riva$Memory$alloc(Size);};
inline void operator delete(void *P) {};

inline void *operator new[](unsigned int Size) {return Riva$Memory$alloc(Size);};
inline void operator delete[](void *P) {};
#endif

RIVA_CFUN(void *, base, void *);

RIVA_CFUN(void *, is_visible, void *);

typedef void (*Riva$Memory_finalizer)(void *, void *);

RIVA_CFUN(void, register_finalizer, void *, Riva$Memory_finalizer, void *, Riva$Memory_finalizer *, void **);
RIVA_CFUN(void, register_finalizer_ignore_self, void *, Riva$Memory_finalizer, void *, Riva$Memory_finalizer *, void **);

#undef RIVA_MODULE

#endif
