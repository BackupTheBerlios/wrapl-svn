#include <IO/Stream.h>
#include <Lang.h>
#include <Riva/Memory.h>
#include <stdio.h>

#include <stdarg.h>

SYMBOL($read, "read");
SYMBOL($write, "write");
SYMBOL($flush, "flush");
SYMBOL($close, "close");
SYMBOL($EOI, "EOI");
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

METHOD("@", TYP, MessageT, VAL, Lang$String$T) {
	IO$Stream_messaget *Msg = Args[0].Val;
	Result->Val = Lang$String$new(Msg->Message);
	return SUCCESS;
};

static IO$Stream_messaget ConvertMessage[] = {{MessageT, "Conversion Error"}};

METHOD("write", TYP, TextWriterT, ANY) {
	if (Count == 2) {
		Lang$Function_result Result0;
		switch (Lang$Function$call($AS, 2, &Result0, Args[1].Val, Args[1].Ref, Lang$String$T, 0)) {
		case SUSPEND:
		case SUCCESS:
			return Lang$Function$call($write, 2, Result, Args[0].Val, Args[0].Ref, Result0.Val, Result0.Ref);
		case FAILURE:
			Result->Val = ConvertMessage;
			return MESSAGE;
		case MESSAGE:
			Result->Arg = Result0.Arg;
			return MESSAGE;
		};
	} else {
		for (int I = 1; I < Count; ++I) {
			long Status = Lang$Function$call($write, 2, Result, Args[0].Val, Args[0].Ref, Args[I].Val, Args[I].Ref);
			if (Status >= FAILURE) return Status;
		};
		return SUCCESS;
	};
};

static void stream_flush(IO$Stream_t *Stream) {
	Lang$Function_result Result;
	Lang$Function$call($flush, 1, &Result, Stream, 0);
};

static void stream_close(IO$Stream_t *Stream) {
	Lang$Function_result Result;
	Lang$Function$call($close, 1, &Result, Stream, 0);
};

static int stream_eoi(IO$Stream_t *Stream) {
	Lang$Function_result Result;
	if (Lang$Function$call($EOI, 1, &Result, Stream, 0) < FAILURE) {
		return 1;
	} else {
		return 0;
	};
};

static int stream_read(IO$Stream_t *Stream, char *Buffer, int Count) {
	Lang$Function_result Result;
	if (Lang$Function$call($read, 2, &Result, Stream, 0, Lang$Address$new(Buffer), 0, Lang$Integer$new_small(Count), 0) < FAILURE) {
		return ((Lang$Integer_smallt *)Result.Val)->Value;
	} else {
		return 0;
	};
};

static char stream_readc(IO$Stream_t *Stream) {
	Lang$Function_result Result;
	if (Lang$Function$call($read, 2, &Result, Stream, 0, Lang$Integer$new_small(1), 0) < FAILURE) {
		Lang$String_t *String = Result.Val;
		return *(char *)(String->Blocks[0].Chars.Value);
	} else {
		return EOF;
	};
};

static char *stream_readn(IO$Stream_t *Stream, int Count) {
	Lang$Function_result Result;
	if (Lang$Function$call($read, 2, &Result, Stream, 0, Lang$Integer$new_small(Count), 0) < FAILURE) {
		return Lang$String$flatten(Result.Val);
	} else {
		return 0;
	};
};


static char *stream_readl(IO$Stream_t *Stream) {
	Lang$Function_result Result;
	if (Lang$Function$call($read, 2, &Result, Stream, 0) < FAILURE) {
		return Lang$String$flatten(Result.Val);
	} else {
		return 0;
	};
};

static int stream_write(IO$Stream_t *Stream, const char *Buffer, int Count) {
	Lang$Function_result Result;
	Lang$Function$call($write, 2, &Result, Stream, 0, Lang$Address$new(Buffer), 0, Lang$Integer$new_small(Count), 0);
};

static void stream_writec(IO$Stream_t *Stream, char Char) {
	Lang$String_t *String = Lang$String$new_char(Char);
	Lang$Function_result Result;
	Lang$Function$call($write, 2, &Result, Stream, 0, String, 0);
};

static void stream_writes(IO$Stream_t *Stream, const char *Text) {
	Lang$String_t *String = Lang$String$new(Text);
	Lang$Function_result Result;
	Lang$Function$call($write, 2, &Result, Stream, 0, String, 0);
};

static void stream_writef(IO$Stream_t *Stream, const char *Format, ...) {
	va_list Args;
	va_start(Args, Format);
	char *Buffer;
	int Length = vasprintf(&Buffer, Format, Args);
	Lang$String_t *String = Lang$String$new_length(Buffer, Length);
	Lang$Function_result Result;
	Lang$Function$call($write, 2, &Result, Stream, 0, String, 0);
};

Lang$Integer_smallt _SEEK_SET[] = {{Lang$Integer$SmallT, IO$Stream_SEEK_SET}};
Lang$Integer_smallt _SEEK_CUR[] = {{Lang$Integer$SmallT, IO$Stream_SEEK_CUR}};
Lang$Integer_smallt _SEEK_END[] = {{Lang$Integer$SmallT, IO$Stream_SEEK_END}};

static Lang$Integer_smallt *_SEEK[] = {_SEEK_SET, _SEEK_CUR, _SEEK_END};

static int stream_seek(IO$Stream_t *Stream, int Position, int Mode) {
	if ((Mode < IO$Stream_SEEK_SET) || (Mode > IO$Stream_SEEK_END)) return -1;
	Lang$Function_result Result;
	if (Lang$Function$call($seek, 3, &Result, Stream, 0, Lang$Integer$new_small(Position), 0, _SEEK[Mode], 0) < FAILURE) {
		return ((Lang$Integer_smallt *)Result.Val)->Value;
	} else {
		return -1;
	};
};

static int stream_tell(IO$Stream_t *Stream) {
	Lang$Function_result Result;
	if (Lang$Function$call($tell, 1, &Result, Stream, 0) < FAILURE) {
		return ((Lang$Integer_smallt *)Result.Val)->Value;
	} else {
		return -1;
	};
};

static IO$Stream_t_methods _T_Methods = {
	stream_flush,
	stream_close
};

static IO$Stream_reader_methods _ReaderT_Methods = {
	stream_eoi,
	stream_read,
	stream_readc,
	stream_readn,
	stream_readl
};

static IO$Stream_writer_methods _WriterT_Methods = {
	stream_write,
	stream_writec,
	stream_writes,
	stream_writef
};

static IO$Stream_seeker_methods _SeekerT_Methods = {
	stream_seek,
	stream_tell
};

Util$TypeTable_t T_Methods[] = {Util$TypeTable$INIT};
Util$TypeTable_t ReaderT_Methods[] = {Util$TypeTable$INIT};
Util$TypeTable_t WriterT_Methods[] = {Util$TypeTable$INIT};
Util$TypeTable_t SeekerT_Methods[] = {Util$TypeTable$INIT};

void __init(void *Module) {
	Util$TypeTable$put(T_Methods, T, &_T_Methods);
	Util$TypeTable$put(ReaderT_Methods, ReaderT, &_ReaderT_Methods);
	Util$TypeTable$put(WriterT_Methods, WriterT, &_WriterT_Methods);
	Util$TypeTable$put(SeekerT_Methods, SeekerT, &_SeekerT_Methods);
};
