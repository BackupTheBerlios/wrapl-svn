#include <IO/Stream.h>
#include <Riva/Memory.h>
#include <Std.h>
#include <stdint.h>

typedef struct node_t node_t;

typedef struct buffer_t {
	Std$Type_t *Type;
	node_t *Head, *Tail, *Current;
	uint32_t Offset;
} buffer_t;

struct node_t {
	node_t *Next, *Prev;
	uint32_t Length;
	const char *Chars;
};

TYPE(T, IO$Stream$ReaderT, IO$Stream$WriterT, IO$Stream$SeekerT, IO$Stream$T);

GLOBAL_FUNCTION(New, 0) {
	buffer_t *Stream = new(buffer_t);
	Stream->Type = T;
	Result->Val = Stream;
	return SUCCESS;
};

static int buffer_eoi(buffer_t *Stream) {
	return 0;
};

METHOD("read", TYP, T, TYP, Std$Address$T, TYP, Std$Integer$SmallT) {
	buffer_t *Stream = Args[0].Val;
	node_t *Node = Stream->Current;
	uint32_t Total = 0;
	const char *Src = Node->Chars;
	const char *Dst = ((Std$Address_t *)Args[1])->Value;
	uint32_t Rem0 = Chars->Length - Stream->Offset;
	uint32_t Rem1 = ((Std$Integer_smallt *)Args[2])->Value;
	while (Rem0 <= Rem1) {
		Dst = mempcpy(Dst, Src, Rem0);
		Rem1 -= Rem0;
		if (Node = Node->Next) {
			Rem0 = Node->Length;
			Src = Node->Chars;
		} else {
			
		};
	};
	return SUCCESS;
};

static int buffer_read(buffer_t *Stream, char *Buffer, int Count) {
};

static char buffer_readc(buffer_t *Stream) {
	char Char;
	return Char;
};

METHOD("rest", TYP, T) {
	buffer_t *Stream = Args[0].Val;
	return SUCCESS;
};

METHOD("read", TYP, T, TYP, Std$Integer$SmallT) {
	buffer_t *Stream = Args[0].Val;
	return SUCCESS;
};

static char *buffer_readn(buffer_t *Stream, int Count) {
};

static char *_read_line_next(buffer_t *Stream, unsigned long Index) {
/*	char Char;
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
*/
};

METHOD("read", TYP, T) {
	buffer_t *Stream = Args[0].Val;
	char *Line = _read_line_next(Stream, 0);
	if (Line == 0) {
		return FAILURE;
	} else {
		Result->Val = Std$String$new(Line);
		return SUCCESS;
	};
};

static char *buffer_readl(buffer_t *Stream) {
	return _read_line_next(Stream, 0);
};

METHOD("write", TYP, T, TYP, Std$Address$T, TYP, Std$Integer$SmallT) {
	buffer_t *Stream = Args[0].Val;
	return SUCCESS;
};

static int buffer_write(buffer_t *Stream, const char *Buffer, int Count) {};

static void buffer_writec(buffer_t *Stream, char Char) {
};

METHOD("write", TYP, T, TYP, Std$String$T) {
	buffer_t *Stream = Args[0].Val;
	return SUCCESS;
};

static void buffer_writes(buffer_t *Stream, const char *Text) {
};

METHOD("write", TYP, T, ANY) {
	buffer_t *Stream = Args[0].Val;
/*	Std$Function_result Result0;
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
*/
};

static void buffer_writef(buffer_t *Stream, const char *Format, ...) {
/*	va_list Args;
	va_start(Args, Format);
	char *Buffer;
	int Length = vasprintf(&Buffer, Format, Args);
	write(Stream->Handle, Buffer, Length);
*/
};

METHOD("seek", TYP, T, TYP, Std$Integer$SmallT) {
	buffer_t *Stream = Args[0].Val;
	return SUCCESS;
};

static int buffer_seek(buffer_t *Stream, int Position) {
};

METHOD("tell", TYP, T) {
	buffer_t *Stream = Args[0].Val;
	return SUCCESS;
};

static int buffer_tell(buffer_t *Stream) {
};
