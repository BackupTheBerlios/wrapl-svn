#ifndef MISSING_H
#define MISSING_H

#ifdef WINDOWS

#define PATHSTR "\\"
#define PATHCHR '\\'

#include <stdarg.h>

extern "C" int asprintf (char **, const char *, ...);
extern "C" int vasprintf (char **, const char *, va_list);

extern "C" char * stpcpy (char *restrict, const char *restrict);

#define getcwd _getcwd

#else

#define PATHSTR "/"
#define PATHCHR '/'

#endif

#endif
