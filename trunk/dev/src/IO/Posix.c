#include <IO/Posix.h>
#include <Util/TypedFunction.h>
#include <Std.h>
#include <Riva.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/poll.h>

SYMBOL($AS, "@");

TYPE(T, IO$Stream$T);

TYPE(ReaderT, T, IO$Stream$ReaderT, IO$Stream$T);
TYPE(WriterT, T, IO$Stream$WriterT, IO$Stream$T);
TYPE(SeekerT, T, IO$Stream$SeekerT, IO$Stream$T);

TYPE(TextReaderT, T, ReaderT, IO$Stream$TextReaderT, IO$Stream$ReaderT, IO$Stream$T);
TYPE(TextWriterT, T, WriterT, IO$Stream$TextWriterT, IO$Stream$WriterT, IO$Stream$T);

static IO$Stream_messaget ConvertMessage[] = {{IO$Stream$MessageT, "Conversion Error"}};
static IO$Stream_messaget ReadMessage[] = {{IO$Stream$MessageT, "Read Error"}};
static IO$Stream_messaget WriteMessage[] = {{IO$Stream$MessageT, "Write Error"}};
static IO$Stream_messaget FlushMessage[] = {{IO$Stream$MessageT, "Flush Error"}};
static IO$Stream_messaget SeekMessage[] = {{IO$Stream$MessageT, "Seek Error"}};
static IO$Stream_messaget CloseMessage[] = {{IO$Stream$MessageT, "Close Error"}};
static IO$Stream_messaget PollMessage[] = {{IO$Stream$MessageT, "Poll Error"}};

Std$Integer_smallt __POLLIN[] = {{Std$Integer$SmallT, POLLIN}};
Std$Integer_smallt __POLLOUT[] = {{Std$Integer$SmallT, POLLOUT}};
Std$Integer_smallt __POLLHUP[] = {{Std$Integer$SmallT, POLLHUP}};
Std$Integer_smallt __POLLPRI[] = {{Std$Integer$SmallT, POLLPRI}};

METHOD("flush", TYP, T) {
	IO$Posix_t *Stream = Args[0].Val;
	if (fsync(Stream->Handle) < 0) {
		Result->Val = FlushMessage;
		return MESSAGE;
	};
	Result->Arg = Args[0];
	return SUCCESS;
};

static void posix_flush(IO$Posix_t *Stream) {
	fsync(Stream->Handle);
};

METHOD("close", TYP, T) {
	IO$Posix_t *Stream = Args[0].Val;
	if (close(Stream->Handle)) {
		Result->Val = CloseMessage;
		return MESSAGE;
	} else {
		Riva$Memory$register_finalizer(Stream, 0, 0, 0, 0);
		Result->Val = Std$Object$Nil;
		return SUCCESS;
	};
};

METHOD("closed", TYP, T) {
	IO$Posix_t *Stream = Args[0].Val;
	// TO BE FIXED
	return FAILURE;
};

static void posix_close(IO$Posix_t *Stream) {
	if (close(Stream->Handle) == 0) {
		Riva$Memory$register_finalizer(Stream, 0, 0, 0, 0);
	};
};

static void posix_finalize(IO$Posix_t *Stream, void *Data) {
	close(Stream->Handle);
};

void _posix_register_finalizer(IO$Posix_t *Stream) {
	Riva$Memory$register_finalizer(Stream, posix_finalize, 0, 0, 0);
};

IO$Posix_t *_posix_new(Std$Type_t *Type, int Handle) {
	IO$Posix_t *Stream = new(IO$Posix_t);
	Stream->Type = Type;
	Stream->Handle = Handle;
	Riva$Memory$register_finalizer(Stream, posix_finalize, 0, 0, 0);
	return Stream;
};

static int posix_eoi(IO$Posix_t *Stream) {
	off_t Current = lseek(Stream->Handle, 0, SEEK_CUR);
	if (Current == -1) return 0;
	return 0;
};

METHOD("read", TYP, ReaderT, TYP, Std$Address$T, TYP, Std$Integer$SmallT) {
	IO$Posix_t *Stream = Args[0].Val;
	char *Buffer = ((Std$Address_t *)Args[1].Val)->Value;
	long Size = ((Std$Integer_smallt *)Args[2].Val)->Value;
	size_t BytesRead = read(Stream->Handle, Buffer, Size);
	if (BytesRead < 0) {
		Result->Val = ReadMessage;
		return MESSAGE;
	};
	Result->Val = Std$Integer$new_small(BytesRead);
	return SUCCESS;
};

static int posix_read(IO$Posix_t *Stream, char *Buffer, int Count) {
	return read(Stream->Handle, Buffer, Count);
};

static char posix_readc(IO$Posix_t *Stream) {
	char Char;
	int Status = read(Stream->Handle, &Char, 1);
	if (Status < 0) return 0;
	if (Status == 0) return EOF;
	return Char;
};

METHOD("rest", TYP, ReaderT) {
	IO$Posix_t *Stream = Args[0].Val;
	size_t Pos = lseek(Stream->Handle, 0, SEEK_CUR);
	size_t Length = lseek(Stream->Handle, 0, SEEK_END) - Pos;
	lseek(Stream->Handle, Pos, SEEK_SET);
	char *Buffer = Riva$Memory$alloc_atomic(Length);
	char *Ptr = Buffer;
	size_t Rem = Length;
	while (Rem) {
		size_t BytesRead = read(Stream->Handle, Ptr, Rem);
		Rem -= BytesRead;
		Ptr += BytesRead;
	};
	
	Result->Val = Std$String$new_length(Buffer, Length);
	return SUCCESS;
};

METHOD("read", TYP, ReaderT, TYP, Std$Integer$SmallT) {
	IO$Posix_t *Stream = Args[0].Val;
	unsigned long Length = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *Buffer = Riva$Memory$alloc_atomic(Length);
	size_t BytesRead = read(Stream->Handle, Buffer, Length);
	if (BytesRead == 0) return FAILURE;
	if (BytesRead < 0) {
		Result->Val = ReadMessage;
		return MESSAGE;
	};
	Result->Val = Std$String$new_length(Buffer, BytesRead);
	return SUCCESS;
};

static char *posix_readn(IO$Posix_t *Stream, int Count) {
	char *Buffer = Riva$Memory$alloc_atomic(Count + 1);
	return (read(Stream->Handle, Buffer, Count) < 0) ? 0 : Buffer;
};

static char *_read_line_next(int Handle, unsigned long Index) {
	char Char;
	int Status = read(Handle, &Char, 1);
	if (Status < 0) return 0;
	if (Status == 0) {
		if (Index == 0) return 0;
		char *Line = Riva$Memory$alloc_atomic(Index + 1);
		Line[Index] = 0;
		return Line;
	};
	if (Char == '\n') {
		char *Line = Riva$Memory$alloc_atomic(Index + 1);
		Line[Index] = 0;
		return Line;
	};
	if (Char == '\r') {
		char *Line = _read_line_next(Handle, Index);
		return Line;
	} else {
		char *Line = _read_line_next(Handle, Index + 1);
		if (Line) Line[Index] = Char;
		return Line;
	};
};

METHOD("read", TYP, TextReaderT) {
	IO$Posix_t *Stream = Args[0].Val;
	char *Line = _read_line_next(Stream->Handle, 0);
	if (Line == 0) {
		return FAILURE;
	} else {
		Result->Val = Std$String$new(Line);
		return SUCCESS;
	};
};

static char *posix_readl(IO$Posix_t *Stream) {
	return _read_line_next(Stream->Handle, 0);
};

METHOD("write", TYP, WriterT, TYP, Std$Address$T, TYP, Std$Integer$SmallT) {
	IO$Posix_t *Stream = Args[0].Val;
	char *Buffer = ((Std$Address_t *)Args[1].Val)->Value;
	long Size = ((Std$Integer_smallt *)Args[2].Val)->Value;
	size_t BytesWritten = write(Stream->Handle, Buffer, Size);
	if (BytesWritten < 0) {
		Result->Val = WriteMessage;
		return MESSAGE;
	};
	Result->Val = Std$Integer$new_small(BytesWritten);
	return SUCCESS;
};

static int posix_write(IO$Posix_t *Stream, const char *Buffer, int Count) {
	return write(Stream->Handle, Buffer, Count);
};

static void posix_writec(IO$Posix_t *Stream, char Char) {
	write(Stream->Handle, &Char, 1);
};

METHOD("write", TYP, WriterT, TYP, Std$String$T) {
	IO$Posix_t *Stream = Args[0].Val;
	Std$String_t *String = Args[1].Val;
	for (long I = 0; I < String->Count; ++I) {
		if (write(Stream->Handle, String->Blocks[I].Chars.Value, String->Blocks[I].Length.Value) < 0) {
			Result->Val = WriteMessage;
			return MESSAGE;
		};
	};
	Result->Arg = Args[0];
	return SUCCESS;
};

static void posix_writes(IO$Posix_t *Stream, const char *Text) {
	write(Stream->Handle, Text, strlen(Text));
};

METHOD("write", TYP, TextWriterT, ANY) {
	IO$Posix_t *Stream = Args[0].Val;
	Std$Function_result Result0;
	switch (Std$Function$call($AS, 2, &Result0, Args[1].Val, Args[1].Ref, Std$String$T, 0)) {
	case SUSPEND:
	case SUCCESS: {
		Std$String_t *String = Result0.Val;
		for (long I = 0; I < String->Count; ++I) {
			if (write(Stream->Handle, String->Blocks[I].Chars.Value, String->Blocks[I].Length.Value) < 0) {
				Result->Val = WriteMessage;
				return MESSAGE;
			};
		};
		Result->Arg = Args[0];
		return SUCCESS;
	};
	case FAILURE:
		Result->Val = ConvertMessage;
		return MESSAGE;
	case MESSAGE:
		Result->Arg = Result0.Arg;
		return MESSAGE;
	};
};

static void posix_writef(IO$Posix_t *Stream, const char *Format, ...) {
	va_list Args;
	va_start(Args, Format);
	char *Buffer;
	int Length = vasprintf(&Buffer, Format, Args);
	write(Stream->Handle, Buffer, Length);
};

METHOD("seek", TYP, SeekerT, TYP, Std$Integer$SmallT) {
	IO$Posix_t *Stream = Args[0].Val;
	long Position = ((Std$Integer_smallt *)Args[1].Val)->Value;
	Position = lseek(Stream->Handle, Position, SEEK_SET);
	if (Position < 0) {
		Result->Val = SeekMessage;
		return MESSAGE;
	};
	Result->Val = Std$Integer$new_small(Position);
	return SUCCESS;
};

static int posix_seek(IO$Posix_t *Stream, int Position) {
	return lseek(Stream->Handle, Position, SEEK_SET);
};

METHOD("tell", TYP, T) {
	IO$Posix_t *Stream = Args[0].Val;
	Result->Val = Std$Integer$new_small(lseek(Stream->Handle, 0, SEEK_CUR));
	return SUCCESS;
};

static int posix_tell(IO$Posix_t *Stream) {
	return lseek(Stream->Handle, 0, SEEK_CUR);
};

METHOD("poll", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	IO$Posix_t *Stream = Args[0].Val;
	struct pollfd PollFd[] = {{Stream->Handle, ((Std$Integer_smallt *)Args[1].Val)->Value, 0}};
	int Status = poll(PollFd, 1, ((Std$Integer_smallt *)Args[2].Val)->Value);
	if (Status < 0) {
		Result->Val = PollMessage;
		return MESSAGE;
	};
	if (Status == 0) return FAILURE;
	Result->Val = Std$Integer$new_small(PollFd->revents);
	return SUCCESS;
};

void __init(void *Module) {
	Util$TypedFunction$add(IO$Stream$flush, T, posix_flush);
	Util$TypedFunction$add(IO$Stream$close, T, posix_close);
	Util$TypedFunction$add(IO$Stream$eoi, ReaderT, posix_eoi);
	Util$TypedFunction$add(IO$Stream$read, ReaderT, posix_read);
	Util$TypedFunction$add(IO$Stream$readc, ReaderT, posix_readc);
	Util$TypedFunction$add(IO$Stream$readn, ReaderT, posix_readn);
	Util$TypedFunction$add(IO$Stream$readl, ReaderT, posix_readl);
	Util$TypedFunction$add(IO$Stream$write, WriterT, posix_write);
	Util$TypedFunction$add(IO$Stream$writec, WriterT, posix_writec);
	Util$TypedFunction$add(IO$Stream$writes, WriterT, posix_writes);
	Util$TypedFunction$add(IO$Stream$writef, WriterT, posix_writef);
	Util$TypedFunction$add(IO$Stream$seek, SeekerT, posix_seek);
	Util$TypedFunction$add(IO$Stream$tell, SeekerT, posix_tell);
};
