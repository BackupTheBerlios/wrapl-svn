#include <IO/Stream.h>
#include <Util/TypedFunction.h>
#include <Riva/Memory.h>
#include <Std.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

typedef struct node_t node_t;

typedef struct buffer_t {
	Std$Type_t *Type;
	node_t *Head, *Tail;
} buffer_t;

struct node_t {
	node_t *Next;
	uint32_t Length;
	const char *Chars;
};

TYPE(T, IO$Stream$ReaderT, IO$Stream$WriterT, IO$Stream$T);

GLOBAL_FUNCTION(New, 0) {
	buffer_t *Stream = new(buffer_t);
	Stream->Type = T;
	Result->Val = Stream;
	return SUCCESS;
};

static int buffer_eoi(buffer_t *Stream) {
	return (Stream->Head == 0);
};

static int buffer_close(buffer_t *Stream, int Mode) {
};

static Std$Integer_smallt Zero[] = {{Std$Integer$SmallT, 0}};

METHOD("read", TYP, T, TYP, Std$Address$T, TYP, Std$Integer$SmallT) {
	buffer_t *Stream = Args[0].Val;
	node_t *Node = Stream->Head;
	if (Node == 0) {
		Result->Val = Zero;
		return SUCCESS;
	};
	uint32_t Total = 0;
	const char *Src = Node->Chars;
	const char *Dst = ((Std$Address_t *)Args[1].Val)->Value;
	uint32_t Rem0 = Node->Length;
	uint32_t Rem1 = ((Std$Integer_smallt *)Args[2].Val)->Value;
	while (Rem0 <= Rem1) {
		Dst = mempcpy(Dst, Src, Rem0);
		Rem1 -= Rem0;
		Total += Rem0;
		if (Node = Node->Next) {
			Rem0 = Node->Length;
			Src = Node->Chars;
		} else {
			Stream->Head = Stream->Tail = 0;
			Result->Val = Std$Integer$new_small(Total);
			return SUCCESS;
		};
	};
	memcpy(Dst, Src, Rem1);
	Total += Rem1;
	Node->Chars += Rem1;
	Stream->Head = Node;
	Result->Val = Std$Integer$new_small(Total);
	return SUCCESS;
};

static int buffer_read(buffer_t *Stream, char *Buffer, int Count) {
	node_t *Node = Stream->Head;
	if (Node == 0) return 0;
	uint32_t Total = 0;
	const char *Src = Node->Chars;
	const char *Dst = Buffer;
	uint32_t Rem0 = Node->Length;
	uint32_t Rem1 = Count;
	while (Rem0 <= Rem1) {
		Dst = mempcpy(Dst, Src, Rem0);
		Rem1 -= Rem0;
		Total += Rem0;
		if (Node = Node->Next) {
			Rem0 = Node->Length;
			Src = Node->Chars;
		} else {
			Stream->Head = Stream->Tail = 0;
			return Total;
		};
	};
	memcpy(Dst, Src, Rem1);
	Total += Rem1;
	Node->Chars += Rem1;
	Stream->Head = Node;
	return Total;
};

static char buffer_readc(buffer_t *Stream) {
	node_t *Node = Stream->Head;
	if (Node == 0) return EOF;
	char Char = Node->Chars[0];
	if (Node->Length == 1) {
		if (Stream->Head = Node->Next) {
		} else {
			Stream->Tail = 0;
		};
	} else {
		Node->Chars++;
		Node->Length--;
	};
	return Char;
};

METHOD("rest", TYP, T) {
	buffer_t *Stream = Args[0].Val;
	int NoOfBlocks = 0;
	for (node_t *Node = Stream->Head; Node; Node = Node->Next) ++NoOfBlocks;
	Std$String_t *String = Riva$Memory$alloc(sizeof(Std$String_t) + (NoOfBlocks + 1) * sizeof(Std$String_block));
	String->Type = Std$String$T;
	String->Length.Type = Std$Integer$SmallT;
	String->Count = NoOfBlocks;
	Std$String_block *Block = String->Blocks;
	for (node_t *Node = Stream->Head; Node; Node = Node->Next) {
		Block->Length.Type = Std$Integer$SmallT;
		String->Length.Value += (Block->Length.Value = Node->Length);
		Block->Chars.Type = Std$Address$T;
		Block->Chars.Value = Node->Chars;
		Block++;
	};
	Stream->Head = Stream->Tail = 0;
	Result->Val = String;
	return SUCCESS;
};

static Std$String_t *_readn_string_next(buffer_t *Stream, node_t *Node, unsigned long Index, unsigned long Rem) {
	if (Node == 0) {
		Std$String_t *String = Riva$Memory$alloc(sizeof(Std$String_t) + (Index + 1) * sizeof(Std$String_block));
		String->Type = Std$String$T;
		String->Length.Type = Std$Integer$SmallT;
		String->Count = Index;
		Stream->Head = Stream->Tail = 0;
		return String;
	} else if (Rem <= Node->Length) {
		Std$String_t *String = Riva$Memory$alloc(sizeof(Std$String_t) + (Index + 2) * sizeof(Std$String_block));
		String->Type = Std$String$T;
		String->Length.Type = Std$Integer$SmallT;
		String->Length.Value = Rem;
		String->Count = Index + 1;
		String->Blocks[Index].Length.Type = Std$Integer$SmallT;
		String->Blocks[Index].Length.Value = Rem;
		String->Blocks[Index].Chars.Type = Std$Address$T;
		String->Blocks[Index].Chars.Value = Node->Chars;
		if (Node->Length -= Rem) {
			Node->Chars += Rem;
			Stream->Head = Node;
		} else {
			if (Stream->Head = Node->Next) {
			} else {
				Stream->Tail = 0;
			};
		};
		return String;
	} else {
		Std$String_t *String = _readn_string_next(Stream, Node->Next, Index + 1, Rem - Node->Length);
		String->Length.Value += Node->Length;
		String->Blocks[Index].Length.Type = Std$Integer$SmallT;
		String->Blocks[Index].Length.Value = Node->Length;
		String->Blocks[Index].Chars.Type = Std$Address$T;
		String->Blocks[Index].Chars.Value = Node->Chars;
		return String;
	};
};

METHOD("read", TYP, T, TYP, Std$Integer$SmallT) {
	buffer_t *Stream = Args[0].Val;
	if (Stream->Head) {
		Result->Val = _readn_string_next(Stream, Stream->Head, 0, ((Std$Integer_smallt *)Args[1].Val)->Value);
		return SUCCESS;
	} else {
		return FAILURE;		
	};
};

static char *_readn_line_next(buffer_t *Stream, node_t *Node, unsigned long Index, unsigned long Rem) {
	if (Node == 0) {
		char *String = Riva$Memory$alloc_atomic(Index + 2);
		String[Index + 1] = 0;
		return String;
	} else if (Rem <= Node->Length) {
		char *String = Riva$Memory$alloc_atomic(Index + Rem + 1);
		String[Index + Rem] = 0;
		memcpy(String + Index, Node->Chars, Rem);
		if (Node->Length -= Rem) {
			Node->Chars += Rem;
			Stream->Head = Node;
		} else {
			if (Stream->Head = Node->Next) {
			} else {
				Stream->Tail = 0;
			};
		};
		return String;
	} else {
		char *String = _readn_line_next(Stream, Node->Next, Index + Node->Length, Rem - Node->Length);
		memcpy(String + Index, Node->Chars, Node->Length);
		return String;
	};
};

static char *buffer_readn(buffer_t *Stream, int Count) {
	if (Stream->Head) {
		return _readn_line_next(Stream, Stream->Head, 0, Count);
	} else {
		return 0;
	};
};

static Std$String_t *_read_string_next(buffer_t *Stream, node_t *Node, unsigned long Index) {
	if (Node == 0) {
		Std$String_t *String = Riva$Memory$alloc(sizeof(Std$String_t) + (Index + 1) * sizeof(Std$String_block));
		String->Type = Std$String$T;
		String->Length.Type = Std$Integer$SmallT;
		String->Count = Index;
		Stream->Head = Stream->Tail = 0;
		return String;
	} else {
		char *Find = memchr(Node->Chars, '\n', Node->Length);
		if (Find) {
			Std$String_t *String = Riva$Memory$alloc(sizeof(Std$String_t) + (Index + 2) * sizeof(Std$String_block));
			String->Type = Std$String$T;
			String->Length.Type = Std$Integer$SmallT;
			String->Length.Value = Find - Node->Chars;
			String->Count = Index + 1;
			String->Blocks[Index].Length.Type = Std$Integer$SmallT;
			String->Blocks[Index].Length.Value = Find - Node->Chars;
			String->Blocks[Index].Chars.Type = Std$Address$T;
			String->Blocks[Index].Chars.Value = Node->Chars;
			if (Node->Length -= (Find + 1 - Node->Chars)) {
				Node->Chars = Find + 1;
				Stream->Head = Node;
			} else {
				if (Stream->Head = Node->Next) {
				} else {
					Stream->Tail = 0;
				};
			};
			return String;
		} else {
			Std$String_t *String = _read_string_next(Stream, Node->Next, Index + 1);
			String->Length.Value += Node->Length;
			String->Blocks[Index].Length.Type = Std$Integer$SmallT;
			String->Blocks[Index].Length.Value = Node->Length;
			String->Blocks[Index].Chars.Type = Std$Address$T;
			String->Blocks[Index].Chars.Value = Node->Chars;
			return String;
		};
	};
};

METHOD("read", TYP, T) {
	buffer_t *Stream = Args[0].Val;
	if (Stream->Head) {
		Result->Val = _read_string_next(Stream, Stream->Head, 0);
		return SUCCESS;
	} else {
		return FAILURE;		
	};
};

static char *_read_line_next(buffer_t *Stream, node_t *Node, unsigned long Index) {
	if (Node == 0) {
		char *String = Riva$Memory$alloc_atomic(Index + 2);
		String[Index + 1] = 0;
		return String;
	} else {
		char *Find = memchr(Node->Chars, '\n', Node->Length);
		if (Find) {
			int Length = Find - Node->Chars;
			char *String = Riva$Memory$alloc_atomic(Index + Length + 1);
			String[Index + Length] = 0;
			memcpy(String + Index, Node->Chars, Length);
			if (Node->Length -= (Length + 1)) {
				Node->Chars = Find + 1;
				Stream->Head = Node;
			} else {
				if (Stream->Head = Node->Next) {
				} else {
					Stream->Tail = 0;
				};
			};
			return String;
		} else {
			char *String = _read_line_next(Stream, Node->Next, Index + Node->Length);
			memcpy(String + Index, Node->Chars, Node->Length);
			return String;
		};
	};
};

static char *buffer_readl(buffer_t *Stream) {
	if (Stream->Head) {
		return _read_line_next(Stream, Stream->Head, 0);
	} else {
		return 0;
	};
};

METHOD("write", TYP, T, TYP, Std$Address$T, TYP, Std$Integer$SmallT) {
	buffer_t *Stream = Args[0].Val;
	long Length = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char *Chars = Riva$Memory$alloc_atomic(Length);
	memcpy(Chars, ((Std$Address_t *)Args[1].Val)->Value, Length);
	node_t *Node = new(node_t);
	Node->Length = Length;
	Node->Chars = Chars;
	if (Stream->Tail) {
		Stream->Tail->Next = Node;
		Stream->Tail = Node;
	} else {
		Stream->Head = Node;
		Stream->Tail = Node;
	};
	Result->Val = Args[2].Val;
	return SUCCESS;
};

static int buffer_write(buffer_t *Stream, const char *Buffer, int Count) {
	char *Chars = Riva$Memory$alloc_atomic(Count);
	memcpy(Chars, Buffer, Count);
	node_t *Node = new(node_t);
	Node->Length = Count;
	Node->Chars = Chars;
	if (Stream->Tail) {
		Stream->Tail->Next = Node;
		Stream->Tail = Node;
	} else {
		Stream->Head = Node;
		Stream->Tail = Node;
	};
	return Count;};

static void buffer_writec(buffer_t *Stream, char Char) {
	char *Chars = Riva$Memory$alloc_atomic(1);
	Chars[0] = Char;
	node_t *Node = new(node_t);
	Node->Length = 1;
	Node->Chars = Chars;
	if (Stream->Tail) {
		Stream->Tail->Next = Node;
		Stream->Tail = Node;
	} else {
		Stream->Head = Node;
		Stream->Tail = Node;
	};
	return 1;
};

METHOD("write", TYP, T, TYP, Std$String$T) {
	buffer_t *Stream = Args[0].Val;
	int NoOfBlocks = ((Std$String_t *)Args[1].Val)->Count;
	Std$String_block *Block = ((Std$String_t *)Args[1].Val)->Blocks;
	if (Block->Length.Value) {
		node_t *Node = new(node_t);
		Node->Chars = Block->Chars.Value;
		Node->Length = Block->Length.Value;
		if (Stream->Tail) {
			Stream->Tail->Next = Node;
		} else {
			Stream->Head = Node;
		};
		while ((++Block)->Length.Value) {
			node_t *Next = new(node_t);
			Node->Next = Next;
			Node = Next;
			Node->Chars = Block->Chars.Value;
			Node->Length = Block->Length.Value;
		};
		Stream->Tail = Node;
	};
	Result->Arg = Args[0];
	return SUCCESS;
};

static void buffer_writes(buffer_t *Stream, const char *Text) {
	int Length = strlen(Text);
	char *Chars = Riva$Memory$alloc_atomic(Length);
	memcpy(Chars, Text, Length);
	node_t *Node = new(node_t);
	Node->Length = Length;
	Node->Chars = Chars;
	if (Stream->Tail) {
		Stream->Tail->Next = Node;
		Stream->Tail = Node;
	} else {
		Stream->Head = Node;
		Stream->Tail = Node;
	};
	return Length;
};

static void buffer_writef(buffer_t *Stream, const char *Format, ...) {
	va_list Args;
	va_start(Args, Format);
	char *Chars;
	int Length = vasprintf(&Chars, Format, Args);
	node_t *Node = new(node_t);
	Node->Length = Length;
	Node->Chars = Chars;
	if (Stream->Tail) {
		Stream->Tail->Next = Node;
		Stream->Tail = Node;
	} else {
		Stream->Head = Node;
		Stream->Tail = Node;
	};
	return Length;
};

void __init(void) {
	Util$TypedFunction$set(IO$Stream$eoi, T, buffer_eoi);
	Util$TypedFunction$set(IO$Stream$close, T, buffer_close);
	Util$TypedFunction$set(IO$Stream$read, T, buffer_read);
	Util$TypedFunction$set(IO$Stream$readc, T, buffer_readc);
	Util$TypedFunction$set(IO$Stream$readn, T, buffer_readn);
	Util$TypedFunction$set(IO$Stream$readl, T, buffer_readl);
	Util$TypedFunction$set(IO$Stream$write, T, buffer_write);
	Util$TypedFunction$set(IO$Stream$writec, T, buffer_writec);
	Util$TypedFunction$set(IO$Stream$writes, T, buffer_writes);
	Util$TypedFunction$set(IO$Stream$writef, T, buffer_writef);
};
