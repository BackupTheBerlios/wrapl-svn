#ifndef IO_STREAM_H
#define IO_STREAM_H

#include <Std/Object.h>
#include <Std/Integer.h>
#include <Util/TypeTable.h>

#define RIVA_MODULE IO$Stream
#include <Riva-Header.h>

typedef Std$Object_t IO$Stream_t;

typedef struct IO$Stream_messaget {
	Std$Type_t *Type;
	const char *Message;
} IO$Stream_messaget;

extern Std$Type_t IO$Stream$T[];
extern Std$Type_t IO$Stream$ReaderT[];
extern Std$Type_t IO$Stream$WriterT[];
extern Std$Type_t IO$Stream$TextReaderT[];
extern Std$Type_t IO$Stream$TextWriterT[];
extern Std$Type_t IO$Stream$SeekerT[];

extern Std$Type_t IO$Stream$MessageT[];

RIVA_CFUN(void, flush, IO$Stream_t *);
RIVA_CFUN(void, close, IO$Stream_t *);
RIVA_CFUN(int, eoi, IO$Stream_t *);
RIVA_CFUN(int, read, IO$Stream_t *, char *, int);
RIVA_CFUN(char, readc, IO$Stream_t *);
RIVA_CFUN(char *, readn, IO$Stream_t *, int);
RIVA_CFUN(char *, readl, IO$Stream_t *);
RIVA_CFUN(int, write, IO$Stream_t *, const char *, int);
RIVA_CFUN(void, writec, IO$Stream_t *, char);
RIVA_CFUN(void, writes, IO$Stream_t *, const char *);
RIVA_CFUN(void, writef, IO$Stream_t *, const char *, ...);
RIVA_CFUN(int, seek, IO$Stream_t *, int, int);
RIVA_CFUN(int, tell, IO$Stream_t *);

#define IO$Stream_SEEK_SET 0
#define IO$Stream_SEEK_CUR 1
#define IO$Stream_SEEK_END 2

extern Std$Integer_smallt IO$Stream$SEEK_SET[];
extern Std$Integer_smallt IO$Stream$SEEK_CUR[];
extern Std$Integer_smallt IO$Stream$SEEK_END[];

#undef RIVA_MODULE

#endif
