#ifndef IO_STREAM_H
#define IO_STREAM_H

#include <Lang/Object.h>
#include <Lang/Integer.h>
#include <Util/TypeTable.h>

#define RIVA_MODULE IO$Stream
#include <Riva-Header.h>

typedef Lang$Object_t IO$Stream_t;

typedef struct IO$Stream_messaget {
	Lang$Type_t *Type;
	const char *Message;
} IO$Stream_messaget;

extern Lang$Type_t IO$Stream$T[];
extern Lang$Type_t IO$Stream$ReaderT[];
extern Lang$Type_t IO$Stream$WriterT[];
extern Lang$Type_t IO$Stream$TextReaderT[];
extern Lang$Type_t IO$Stream$TextWriterT[];
extern Lang$Type_t IO$Stream$SeekerT[];

extern Lang$Type_t IO$Stream$MessageT[];

typedef struct IO$Stream_t_methods {
	void (*flush)(IO$Stream_t *);
	void (*close)(IO$Stream_t *);
} IO$Stream_t_methods;

typedef struct IO$Stream_reader_methods {
	int (*eoi)(IO$Stream_t *);
	int (*read)(IO$Stream_t *, char *, int);
	char (*readc)(IO$Stream_t *);
	char *(*readn)(IO$Stream_t *, int);
	char *(*readl)(IO$Stream_t *);
} IO$Stream_reader_methods;

typedef struct IO$Stream_writer_methods {
	int (*write)(IO$Stream_t *, const char *, int);
	void (*writec)(IO$Stream_t *, char);
	void (*writes)(IO$Stream_t *, const char *);
	void (*writef)(IO$Stream_t *, const char *, ...);
} IO$Stream_writer_methods;

#define IO$Stream_SEEK_SET 0
#define IO$Stream_SEEK_CUR 1
#define IO$Stream_SEEK_END 2

typedef struct IO$Stream_seeker_methods {
	int (*seek)(IO$Stream_t *, int, int);
	int (*tell)(IO$Stream_t *);
} IO$Stream_seeker_methods;

extern Lang$Integer_smallt IO$Stream$SEEK_SET[];
extern Lang$Integer_smallt IO$Stream$SEEK_CUR[];
extern Lang$Integer_smallt IO$Stream$SEEK_END[];

extern Util$TypeTable_t IO$Stream$T_Methods[];
extern Util$TypeTable_t IO$Stream$ReaderT_Methods[];
extern Util$TypeTable_t IO$Stream$WriterT_Methods[];
extern Util$TypeTable_t IO$Stream$SeekerT_Methods[];

#undef RIVA_MODULE

#endif
