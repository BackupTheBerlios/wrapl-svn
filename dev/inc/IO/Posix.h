#ifndef IO_POSIX_H
#define IO_POSIX_H

#include <IO/Stream.h>

#define RIVA_MODULE IO$Posix
#include <Riva-Header.h>

typedef struct IO$Posix_t IO$Posix_t;

struct IO$Posix_t {
	Lang$Type_t *Type;
	int Handle;
};

extern Lang$Type_t IO$Posix$T[];
extern Lang$Type_t IO$Posix$ReaderT[];
extern Lang$Type_t IO$Posix$WriterT[];
extern Lang$Type_t IO$Posix$SeekerT[];
extern Lang$Type_t IO$Posix$TextReaderT[];
extern Lang$Type_t IO$Posix$TextWriterT[];

#undef RIVA_MODULE

#endif

