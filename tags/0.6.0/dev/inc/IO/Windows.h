#ifndef IO_WINDOWS_H
#define IO_WINDOWS_H

#include <IO/Stream.h>
#include <windows.h>

#define RIVA_MODULE IO$Windows
#include <Riva-Header.h>

typedef struct IO$Windows_t IO$Windows_t;

struct IO$Windows_t {
	Std$Type_t *Type;
	HANDLE Handle;
};

extern Std$Type_t IO$Windows$T[];
extern Std$Type_t IO$Windows$ReaderT[];
extern Std$Type_t IO$Windows$WriterT[];
extern Std$Type_t IO$Windows$SeekerT[];
extern Std$Type_t IO$Windows$TextReaderT[];
extern Std$Type_t IO$Windows$TextWriterT[];

#undef RIVA_MODULE

#endif

