#ifndef IO_POSIX_H
#define IO_POSIX_H

#include <IO/Stream.h>
#include <unistd.h>
#include <fcntl.h>

#define RIVA_MODULE IO$Posix
#include <Riva-Header.h>

typedef struct IO$Posix_t IO$Posix_t;

struct IO$Posix_t {
	Std$Type_t *Type;
	int Handle;
};

extern Std$Type_t IO$Posix$T[];
extern Std$Type_t IO$Posix$ReaderT[];
extern Std$Type_t IO$Posix$WriterT[];
extern Std$Type_t IO$Posix$SeekerT[];
extern Std$Type_t IO$Posix$TextReaderT[];
extern Std$Type_t IO$Posix$TextWriterT[];

#undef RIVA_MODULE

#endif

