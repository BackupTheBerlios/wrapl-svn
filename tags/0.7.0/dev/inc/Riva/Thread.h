#ifndef RIVA_THREAD_H
#define RIVA_THREAD_H

#define RIVA_MODULE Riva$Thread
#include <Riva-Header.h>

typedef struct Riva$Thread_t Riva$Thread_t;
typedef struct Riva$Thread_key Riva$Thread_key;
typedef struct Riva$Thread_mutex Riva$Thread_mutex;
typedef struct Riva$Thread_cond Riva$Thread_cond;

RIVA_CFUN(Riva$Thread_t *, new, void *(*)(void *), void *);
RIVA_CFUN(Riva$Thread_t *, self);

RIVA_CFUN(Riva$Thread_key *, key_new, void (*)(void *));
RIVA_CFUN(void, key_del, Riva$Thread_key *);
RIVA_CFUN(void *, key_get, Riva$Thread_key *);
RIVA_CFUN(void, key_set, Riva$Thread_key *, void *);

RIVA_CFUN(Riva$Thread_mutex *, mutex_new, void);
RIVA_CFUN(void, mutex_del, Riva$Thread_mutex *);
RIVA_CFUN(int, mutex_lock, Riva$Thread_mutex *);
RIVA_CFUN(int, mutex_trylock, Riva$Thread_mutex *);
RIVA_CFUN(int, mutex_unlock, Riva$Thread_mutex *);

#undef RIVA_MODULE

#endif
