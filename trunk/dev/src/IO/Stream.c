#include <IO/Stream.h>
#include <Util/TypedFunction.h>
#include <Std.h>
#include <Riva/Memory.h>
#include <stdio.h>

#include <stdarg.h>

SYMBOL($read, "read");
SYMBOL($write, "write");
SYMBOL($flush, "flush");
SYMBOL($close, "close");
SYMBOL($eoi, "eoi");
SYMBOL($seek, "seek");
SYMBOL($tell, "tell");
SYMBOL($AS, "@");

ITYPE(T, 1);
ITYPE(ReaderT, 2, T);
ITYPE(WriterT, 2, T);
ITYPE(SeekerT, 2, T);
ITYPE(TextReaderT, 3, ReaderT, T);
ITYPE(TextWriterT, 3, WriterT, T);

TYPE(MessageT);

METHOD("@", TYP, MessageT, VAL, Std$String$T) {
//@msg
	IO$Stream_messaget *Msg = Args[0].Val;
	Result->Val = Std$String$new(Msg->Message);
	return SUCCESS;
};

extern void _flush(IO$Stream_t *);
extern void _close(IO$Stream_t *, int);
extern int _eoi(IO$Stream_t *);
extern int _read(IO$Stream_t *, char *, int);
extern char _readc(IO$Stream_t *);
extern char *_readn(IO$Stream_t *, int);
extern char *_readl(IO$Stream_t *);
extern int _write(IO$Stream_t *, const char *, int);
extern void _writec(IO$Stream_t *, char);
extern void _writes(IO$Stream_t *, const char *);
extern void _writef(IO$Stream_t *, const char *, ...);
extern int _seek(IO$Stream_t *, int, int);
extern int _tell(IO$Stream_t *);

static IO$Stream_messaget ConvertMessage[] = {{MessageT, "Conversion Error"}};

METHOD("write", TYP, TextWriterT, ANY) {
	Std$Function_result Result0;
	switch (Std$Function$call($AS, 2, &Result0, Args[1].Val, Args[1].Ref, Std$String$T, 0)) {
	case SUSPEND:
	case SUCCESS:
		return Std$Function$call($write, 2, Result, Args[0].Val, Args[0].Ref, Result0.Val, Result0.Ref);
	case FAILURE:
		Result->Val = ConvertMessage;
		return MESSAGE;
	case MESSAGE:
		Result->Arg = Result0.Arg;
		return MESSAGE;
	};
};

METHOD("writes", TYP, TextWriterT) {
	for (int I = 1; I < Count; ++I) {
		long Status = Std$Function$call($write, 2, Result, Args[0].Val, Args[0].Ref, Args[I].Val, Args[I].Ref);
		if (Status >= FAILURE) return Status;
	};
	return SUCCESS;
};

METHOD("write", TYP, WriterT, TYP, Std$String$T) {
	Std$String_t *String;
	for (int I = 0; I < String->Count; ++I) {
		long Status = Std$Function$call($write, 2, Result, &String->Blocks[I].Chars, 0, &String->Blocks[I].Length, 0);
		if (Status >= FAILURE) return Status;
	};
	return SUCCESS;
};

static void stream_flush(IO$Stream_t *Stream) {
	Std$Function_result Result;
	Std$Function$call($flush, 1, &Result, Stream, 0);
};

static void stream_close(IO$Stream_t *Stream, int Mode) {
	Std$Function_result Result;
	Std$Function$call($close, 2, &Result, Stream, 0, Std$Integer$new_small(Mode), 0);
};

static int stream_eoi(IO$Stream_t *Stream) {
	Std$Function_result Result;
	if (Std$Function$call($eoi, 1, &Result, Stream, 0) < FAILURE) {
		return 1;
	} else {
		return 0;
	};
};

static int stream_read(IO$Stream_t *Stream, char *Buffer, int Count) {
	Std$Function_result Result;
	if (Std$Function$call($read, 2, &Result, Stream, 0, Std$Address$new(Buffer), 0, Std$Integer$new_small(Count), 0) < FAILURE) {
		return ((Std$Integer_smallt *)Result.Val)->Value;
	} else {
		return 0;
	};
};

static char stream_readc(IO$Stream_t *Stream) {
	Std$Function_result Result;
	if (Std$Function$call($read, 2, &Result, Stream, 0, Std$Integer$new_small(1), 0) < FAILURE) {
		Std$String_t *String = Result.Val;
		return *(char *)(String->Blocks[0].Chars.Value);
	} else {
		return EOF;
	};
};

static char *stream_readn(IO$Stream_t *Stream, int Count) {
	Std$Function_result Result;
	if (Std$Function$call($read, 2, &Result, Stream, 0, Std$Integer$new_small(Count), 0) < FAILURE) {
		return Std$String$flatten(Result.Val);
	} else {
		return 0;
	};
};

static char *stream_readl(IO$Stream_t *Stream) {
	Std$Function_result Result;
	if (Std$Function$call($read, 1, &Result, Stream, 0) < FAILURE) {
		return Std$String$flatten(Result.Val);
	} else {
		return 0;
	};
};

static int stream_write(IO$Stream_t *Stream, const char *Buffer, int Count) {
	Std$Function_result Result;
	Std$Function$call($write, 2, &Result, Stream, 0, Std$Address$new(Buffer), 0, Std$Integer$new_small(Count), 0);
};

static void stream_writec(IO$Stream_t *Stream, char Char) {
	Std$String_t *String = Std$String$new_char(Char);
	Std$Function_result Result;
	Std$Function$call($write, 2, &Result, Stream, 0, String, 0);
};

static void stream_writes(IO$Stream_t *Stream, const char *Text) {
	Std$String_t *String = Std$String$new(Text);
	Std$Function_result Result;
	Std$Function$call($write, 2, &Result, Stream, 0, String, 0);
};

static void stream_writef(IO$Stream_t *Stream, const char *Format, ...) {
	va_list Args;
	va_start(Args, Format);
	char *Buffer;
	int Length = vasprintf(&Buffer, Format, Args);
	Std$String_t *String = Std$String$new_length(Buffer, Length);
	Std$Function_result Result;
	Std$Function$call($write, 2, &Result, Stream, 0, String, 0);
};

Std$Integer_smallt _SEEK_SET[] = {{Std$Integer$SmallT, IO$Stream_SEEK_SET}};
Std$Integer_smallt _SEEK_CUR[] = {{Std$Integer$SmallT, IO$Stream_SEEK_CUR}};
Std$Integer_smallt _SEEK_END[] = {{Std$Integer$SmallT, IO$Stream_SEEK_END}};

static Std$Integer_smallt *_SEEK[] = {_SEEK_SET, _SEEK_CUR, _SEEK_END};

static int stream_seek(IO$Stream_t *Stream, int Position, int Mode) {
	if ((Mode < IO$Stream_SEEK_SET) || (Mode > IO$Stream_SEEK_END)) return -1;
	Std$Function_result Result;
	if (Std$Function$call($seek, 3, &Result, Stream, 0, Std$Integer$new_small(Position), 0, _SEEK[Mode], 0) < FAILURE) {
		return ((Std$Integer_smallt *)Result.Val)->Value;
	} else {
		return -1;
	};
};

static int stream_tell(IO$Stream_t *Stream) {
	Std$Function_result Result;
	if (Std$Function$call($tell, 1, &Result, Stream, 0) < FAILURE) {
		return ((Std$Integer_smallt *)Result.Val)->Value;
	} else {
		return -1;
	};
};

METHOD("copy", TYP, ReaderT, TYP, WriterT, TYP, Std$Integer$SmallT) {
	IO$Stream_t *Rd = Args[0].Val;
	IO$Stream_t *Wr = Args[1].Val;
	int Rem = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char Buffer[1024];
	while (Rem > 1024) {
		int Read = _read(Rd, Buffer, 1024);
		Rem -= Read;
		char *Ptr = Buffer;
		while (Read) {
			int Written = _write(Wr, Ptr, Read);
			Read -= Written;
			Ptr += Written;
		};
	};
	char *Ptr = Buffer;
	int Rem2 = Rem;
	while (Rem) {
		int Read = _read(Rd, Ptr, Rem);
		Rem -= Read;
		Ptr += Read;
	};
	Ptr = Buffer;
	while (Rem2) {
		int Written = _write(Wr, Ptr, Rem2);
		Rem2 -= Written;
		Ptr += Written;
	};
	return SUCCESS;
};

#ifdef LINUX

#include <pthread.h>

typedef struct pair_t {
	IO$Stream_t *Rd, *Wr;
} pair_t;

static void *_link_thread_func(pair_t *Pair) {
	char Buffer[256];
	IO$Stream_t *Rd = Pair->Rd;
	IO$Stream_t *Wr = Pair->Wr;
	int (*read)(IO$Stream_t *, char *, int) = Util$TypedFunction$get(_read, Rd->Type);
	int (*write)(IO$Stream_t *, char *, int) = Util$TypedFunction$get(_write, Wr->Type);
	Pair = 0;
	for (;;) {
		int BytesRead = read(Rd, Buffer, 256);
		if (BytesRead <= 0) {
			_close(Wr, 1);
			return;
		};
		char *Tmp = Buffer;
		while (BytesRead) {
			int BytesWritten = write(Wr, Tmp, BytesRead);
			if (BytesWritten < 0) return;
			Tmp += BytesWritten;
			BytesRead -= BytesWritten;
		};
	};
};

METHOD("link", TYP, T, TYP, T) {
	pthread_t Thread[1];
	pair_t *Pair = new(pair_t);
	Pair->Rd = Args[0].Val;
	Pair->Wr = Args[1].Val;
	pthread_create(Thread, 0, _link_thread_func, Pair);
	return SUCCESS;
};

#endif

void __init(void *Module) {
	Util$TypedFunction$set(_flush, T, stream_flush);
	Util$TypedFunction$set(_close, T, stream_close);
	Util$TypedFunction$set(_eoi, ReaderT, stream_eoi);
	Util$TypedFunction$set(_read, ReaderT, stream_read);
	Util$TypedFunction$set(_readc, ReaderT, stream_readc);
	Util$TypedFunction$set(_readn, ReaderT, stream_readn);
	Util$TypedFunction$set(_readl, ReaderT, stream_readl);
	Util$TypedFunction$set(_write, WriterT, stream_write);
	Util$TypedFunction$set(_writec, WriterT, stream_writec);
	Util$TypedFunction$set(_writes, WriterT, stream_writes);
	Util$TypedFunction$set(_writef, WriterT, stream_writef);
	Util$TypedFunction$set(_seek, SeekerT, stream_seek);
	Util$TypedFunction$set(_tell, SeekerT, stream_tell);
};
