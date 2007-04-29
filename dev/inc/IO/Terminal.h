#ifndef IO_TERMINAL_H
#define IO_TERMINAL_H

#ifdef WINDOWS
    #include <IO/Windows.h>
    #define NATIVE(x) IO$Windows ## x
#else
    #include <IO/Posix.h>
    #define NATIVE(x) IO$Posix ## x
#endif

#define RIVA_MODULE IO$Terminal
#include <Riva-Header.h>

extern NATIVE(_t) IO$Terminal$In[];
extern NATIVE(_t) IO$Terminal$Out[];

#undef RIVA_MODULE

#endif
