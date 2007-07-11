#ifndef SYMBOL_H
#define SYMBOL_H

#include "module.h"

extern module_t *Symbol;
extern void (*add_methods)(void *);

extern void symbol_init(void);
extern void symbol_make(const char *);

#endif
