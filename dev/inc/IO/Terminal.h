#ifndef IO_TERMINAL_H
#define IO_TERMINAL_H

#include <IO/Posix.h>

#define RIVA_MODULE IO$Terminal
#include <Riva-Header.h>

extern IO$Posix_t IO$Terminal$In[];
extern IO$Posix_t IO$Terminal$Out[];

#undef RIVA_MODULE

#endif
