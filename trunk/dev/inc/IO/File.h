#ifndef IO_FILE_H
#define IO_FILE_H

#include <IO/Native.h>

#define RIVA_MODULE IO$File
#include <Riva-Header.h>

RIVA_CFUN(NATIVE(_t) *, open, const char *, int);

#define IO$File$OPENREAD		1
#define IO$File$OPENWRITE		2
#define IO$File$OPENTEXT		4
#define IO$File$OPENAPPEND		8

#undef RIVA_MODULE

#endif
