#ifndef IO_WINDOWS_H
#define IO_WINDOWS_H

#include <IO/Stream.h>
#include <windows.h>

#define RIVA_MODULE IO$Windows
#include <Riva-Header.h>

typedef struct IO$Windows_t IO$Windows_t;

struct IO$Windows_t {
	Lang$Type_t *Type;
	HANDLE Handle;
};

extern Lang$Type_t IO$Windows$T[];
extern Lang$Type_t IO$Windows$ReaderT[];
extern Lang$Type_t IO$Windows$WriterT[];
extern Lang$Type_t IO$Windows$SeekerT[];
extern Lang$Type_t IO$Windows$TextReaderT[];
extern Lang$Type_t IO$Windows$TextWriterT[];

#undef RIVA_MODULE

#endif

