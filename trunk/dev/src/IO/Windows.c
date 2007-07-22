#include <IO/Windows.h>
#include <Std.h>
#include <Riva.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

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

METHOD("flush", TYP, T) {
	IO$Windows_t *Stream = Args[0].Val;
	if (FlushFileBuffers(Stream->Handle) == 0) {
		Result->Val = FlushMessage;
		return MESSAGE;
	};
	Result->Arg = Args[0];
	return SUCCESS;
};

static void windows_flush(IO$Windows_t *Stream) {
	FlushFileBuffers(Stream->Handle);
};

METHOD("close", TYP, T) {
	IO$Windows_t *Stream = Args[0].Val;
	if (CloseHandle(Stream->Handle) == 0) {
		Result->Val = CloseMessage;
		return MESSAGE;
	};
	Result->Val = Std$Object$Nil;
	return SUCCESS;
};

METHOD("Closed", TYP, T) {
	IO$Windows_t *Stream = Args[0].Val;
	// TO BE FIXED
	return FAILURE;
};

static void windows_close(IO$Windows_t *Stream) {
	CloseHandle(Stream->Handle);
};

static int windows_eoi(IO$Windows_t *Stream) {
    char Buffer;
    unsigned long BytesRead;
	return (ReadFile(Stream->Handle, &Buffer, 0, &BytesRead, 0) == 0);
};

METHOD("rest", TYP, ReaderT) {
	IO$Windows_t *Stream = Args[0].Val;
	unsigned long Length = GetFileSize(Stream->Handle, 0) - SetFilePointer(Stream->Handle, 0, 0, FILE_CURRENT);
	char *Buffer = Riva$Memory$alloc_atomic(Length);
	char *Ptr = Buffer;
	unsigned long Rem = Length;
	while (Rem) {
		unsigned long BytesRead;
		ReadFile(Stream->Handle, Ptr, Rem, &BytesRead, 0);
		Rem -= BytesRead;
		Ptr += BytesRead;
	};
	Result->Val = Std$String$new_length(Buffer, Length);
	return SUCCESS;
};

METHOD("read", TYP, ReaderT, TYP, Std$Address$T, TYP, Std$Integer$SmallT) {
	IO$Windows_t *Stream = Args[0].Val;
	char *Buffer = ((Std$Address_t *)Args[1].Val)->Value;
	long Size = ((Std$Integer_smallt *)Args[2].Val)->Value;
	size_t BytesRead;
	if (ReadFile(Stream->Handle, Buffer, Size, &BytesRead, 0) == 0) {
		Result->Val = ReadMessage;
		return MESSAGE;
	};
	Result->Val = Std$Integer$new_small(BytesRead);
	return SUCCESS;
};

static int windows_read(IO$Windows_t *Stream, char *Buffer, int Count) {
    size_t BytesRead;
	ReadFile(Stream->Handle, Buffer, Count, &BytesRead, 0);
	return BytesRead;
};

static char windows_readc(IO$Windows_t *Stream) {
	char Char;
	int BytesRead;
	if (ReadFile(Stream->Handle, &Char, 1, &BytesRead, 0) == 0) return 0;
	if (BytesRead == 0) return EOF;
	return Char;
};

METHOD("read", TYP, ReaderT, TYP, Std$Integer$SmallT) {
	IO$Windows_t *Stream = Args[0].Val;
	unsigned long Length = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *Buffer = Riva$Memory$alloc_atomic(Length);
	size_t BytesRead;
	if (ReadFile(Stream->Handle, Buffer, Length, &BytesRead, 0) == 0) {
		Result->Val = ReadMessage;
		return MESSAGE;
	};
	if (BytesRead == 0) return FAILURE;
	Result->Val = Std$String$new_length(Buffer, BytesRead);
	return SUCCESS;
};

static char *windows_readn(IO$Windows_t *Stream, int Count) {
	char *Buffer = Riva$Memory$alloc_atomic(Count + 1);
	size_t BytesRead;
	return (ReadFile(Stream->Handle, Buffer, Count, &BytesRead, 0) == 0) ? 0 : Buffer;
};

static char *_read_line_next(int Handle, unsigned long Index) {
	char Char;
	int BytesRead;
	if (ReadFile(Handle, &Char, 1, &BytesRead, 0) == 0) return 0;
	if (BytesRead == 0) {
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
	IO$Windows_t *Stream = Args[0].Val;
	char *Line = _read_line_next(Stream->Handle, 0);
	if (Line == 0) {
		return FAILURE;
	} else {
		Result->Val = Std$String$new(Line);
		return SUCCESS;
	};
};

static char *windows_readl(IO$Windows_t *Stream) {
	return _read_line_next(Stream->Handle, 0);
};

METHOD("write", TYP, WriterT, TYP, Std$Address$T, TYP, Std$Integer$SmallT) {
	IO$Windows_t *Stream = Args[0].Val;
	char *Buffer = ((Std$Address_t *)Args[1].Val)->Value;
	long Size = ((Std$Integer_smallt *)Args[2].Val)->Value;
	size_t BytesWritten;
	if (WriteFile(Stream->Handle, Buffer, Size, &BytesWritten, 0) == 0) {
		Result->Val = WriteMessage;
		return MESSAGE;
	};
	Result->Val = Std$Integer$new_small(BytesWritten);
	return SUCCESS;
};

static int windows_write(IO$Windows_t *Stream, const char *Buffer, int Count) {
    size_t BytesWritten;
	WriteFile(Stream->Handle, Buffer, Count, &BytesWritten, 0);
	return BytesWritten;
};

static void windows_writec(IO$Windows_t *Stream, char Char) {
    size_t BytesWritten;
	WriteFile(Stream->Handle, &Char, 1, &BytesWritten, 0);
};

METHOD("write", TYP, WriterT, TYP, Std$String$T) {
	IO$Windows_t *Stream = Args[0].Val;
	Std$String_t *String = Args[1].Val;
	for (long I = 0; I < String->Count; ++I) {
	    size_t BytesWritten;
		if (WriteFile(Stream->Handle, String->Blocks[I].Chars.Value, String->Blocks[I].Length.Value, &BytesWritten, 0) == 0) {
			Result->Val = WriteMessage;
			return MESSAGE;
		};
	};
	Result->Arg = Args[0];
	return SUCCESS;
};

static void windows_writes(IO$Windows_t *Stream, const char *Text) {
    size_t BytesWritten;
	WriteFile(Stream->Handle, Text, strlen(Text), &BytesWritten, 0);
};

METHOD("write", TYP, TextWriterT, ANY) {
	IO$Windows_t *Stream = Args[0].Val;
	Std$Function_result Result0;
	switch (Std$Function$call($AS, 2, &Result0, Args[1].Val, Args[1].Ref, Std$String$T, 0)) {
	case SUSPEND:
	case SUCCESS: {
		Std$String_t *String = Result0.Val;
		for (long I = 0; I < String->Count; ++I) {
		    size_t BytesWritten;
			if (WriteFile(Stream->Handle, String->Blocks[I].Chars.Value, String->Blocks[I].Length.Value, &BytesWritten, 0) == 0) {
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

static void windows_writef(IO$Windows_t *Stream, const char *Format, ...) {
	va_list Args;
	va_start(Args, Format);
	char *Buffer;
	int Length = vasprintf(&Buffer, Format, Args);
	size_t BytesWritten;
	WriteFile(Stream->Handle, Buffer, Length, &BytesWritten, 0);
};

METHOD("seek", TYP, SeekerT, TYP, Std$Integer$SmallT) {
	IO$Windows_t *Stream = Args[0].Val;
	long Position = ((Std$Integer_smallt *)Args[1].Val)->Value;
	Position = SetFilePointer(Stream->Handle, Position, 0, FILE_BEGIN);
	if (Position < 0) {
		Result->Val = SeekMessage;
		return MESSAGE;
	};
	Result->Val = Std$Integer$new_small(Position);
	return SUCCESS;
};

static int windows_seek(IO$Windows_t *Stream, int Position) {
	return SetFilePointer(Stream->Handle, Position, 0, FILE_BEGIN);
};

METHOD("tell", TYP, T) {
	IO$Windows_t *Stream = Args[0].Val;
	Result->Val = Std$Integer$new_small(SetFilePointer(Stream->Handle, 0, 0, FILE_CURRENT));
	return SUCCESS;
};

static int windows_tell(IO$Windows_t *Stream) {
	return SetFilePointer(Stream->Handle, 0, 0, FILE_CURRENT);
};

static IO$Stream_t_methods _T_Methods = {
	windows_flush,
	windows_close
};

static IO$Stream_reader_methods _ReaderT_Methods = {
	windows_eoi,
	windows_read,
	windows_readc,
	windows_readn,
	windows_readl
};

static IO$Stream_writer_methods _WriterT_Methods = {
	windows_write,
	windows_writec,
	windows_writes,
	windows_writef
};

static IO$Stream_seeker_methods _SeekerT_Methods = {
	windows_seek,
	windows_tell
};

void __init(void *Module) {
	Util$TypeTable$put(IO$Stream$T_Methods, T, &_T_Methods);
	Util$TypeTable$put(IO$Stream$ReaderT_Methods, ReaderT, &_ReaderT_Methods);
	Util$TypeTable$put(IO$Stream$WriterT_Methods, WriterT, &_WriterT_Methods);
	Util$TypeTable$put(IO$Stream$SeekerT_Methods, SeekerT, &_SeekerT_Methods);
};
