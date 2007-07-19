#include <IO/Posix.h>
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
	};
	Result->Val = Std$Object$Nil;
	return SUCCESS;
};

METHOD("Closed", TYP, T) {
	IO$Posix_t *Stream = Args[0].Val;
	// TO BE FIXED
	return FAILURE;
};

static void posix_close(IO$Posix_t *Stream) {
	close(Stream->Handle);
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

static IO$Stream_t_methods _T_Methods = {
	posix_flush,
	posix_close
};

static IO$Stream_reader_methods _ReaderT_Methods = {
	posix_eoi,
	posix_read,
	posix_readc,
	posix_readn,
	posix_readl
};

static IO$Stream_writer_methods _WriterT_Methods = {
	posix_write,
	posix_writec,
	posix_writes,
	posix_writef
};

static IO$Stream_seeker_methods _SeekerT_Methods = {
	posix_seek,
	posix_tell
};

void __init(void *Module) {
	Util$TypeTable$put(IO$Stream$T_Methods, T, &_T_Methods);
	Util$TypeTable$put(IO$Stream$ReaderT_Methods, ReaderT, &_ReaderT_Methods);
	Util$TypeTable$put(IO$Stream$WriterT_Methods, WriterT, &_WriterT_Methods);
	Util$TypeTable$put(IO$Stream$SeekerT_Methods, SeekerT, &_SeekerT_Methods);
};
