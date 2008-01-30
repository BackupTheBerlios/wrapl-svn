#include <Std.h>
#include <Riva/Memory.h>
#include <setjmp.h>

typedef struct decoder_t {
	Std$String_block *Block;
	char *Next;
	int Rem;
	jmp_buf OnError[1];
} decoder_t;

static void advance(decoder_t *Decoder) {
	if (--Decoder->Rem == 0) {
		Decoder->Block++;
		Decoder->Next = Decoder->Block->Chars.Value;
		Decoder->Rem = Decoder->Block->Length.Value;
	} else {
		Decoder->Next++;
	};
};

static int Hex[] = {
	['0'] = 0, ['1'] = 1, ['2'] = 2, ['3'] = 3, ['4'] = 4,
	['5'] = 5, ['6'] = 6, ['7'] = 7, ['8'] = 8, ['9'] = 9,
	['A'] = 10, ['B'] = 11, ['C'] = 12, ['D'] = 13, ['E'] = 14, ['F'] = 15,
	['a'] = 10, ['b'] = 11, ['c'] = 12, ['d'] = 13, ['e'] = 14, ['f'] = 15
};

static Std$String_t *next(decoder_t *Decoder, int Index) {
	if (Decoder->Next) {
		char Char = Decoder->Next[0];
		switch (Char) {
		case '%': {
			advance(Decoder);
			Char = Hex[Decoder->Next[0]];
			advance(Decoder);
			Char <<= 4;
			Char += Hex[Decoder->Next[0]];
			advance(Decoder);
			Std$String_t *Key = next(Decoder, Index + 1);
			char *Chars = Key->Blocks->Chars.Value;
			Chars[Index] = Char;
			return Key;
		};
		case '+': {
			advance(Decoder);
			Std$String_t *Key = next(Decoder, Index + 1);
			char *Chars = Key->Blocks->Chars.Value;
			Chars[Index] = ' ';
			return Key;
		};
		case '&': case '=': {
			char *Chars = Riva$Memory$alloc_atomic(Index + 1);
			Chars[Index] = 0;
			Std$String_t *Key = Std$String$new_length(Chars, Index);
			return Key;
		};
		default: {
			advance(Decoder);
			Std$String_t *Key = next(Decoder, Index + 1);
			char *Chars = Key->Blocks->Chars.Value;
			Chars[Index] = Char;
			return Key;
		};
		};
	} else {
		char *Chars = Riva$Memory$alloc_atomic(Index + 1);
		Chars[Index] = 0;
		Std$String_t *Key = Std$String$new_length(Chars, Index);
		return Key;
	};
};

GLOBAL_FUNCTION(Decode, 1) {
	decoder_t Decoder[1] = {
		((Std$String_t *)Args[0].Val)->Blocks,
		((Std$String_t *)Args[0].Val)->Blocks->Chars.Value,
		((Std$String_t *)Args[0].Val)->Blocks->Length.Value
	};
	Std$Object_t *Table = Std$Table$new(0, 0);
	if (Decoder->Rem) for (;;) {
		Std$String_t *Key = next(Decoder, 0);
		Std$Object_t *Value = Std$Object$Nil;
		if (Decoder->Next && (Decoder->Next[0] == '=')) {
			advance(Decoder);
			Value = next(Decoder, 0);
		};
		Std$Table$insert(Table, Key, Value);
		if (Decoder->Next == 0) break;
		if (Decoder->Next[0] != '&') {
			Result->Val = Std$String$new("Decode Error");
			return MESSAGE;
		};
		advance(Decoder);
	};
	Result->Val = Table;
	return SUCCESS;
};

GLOBAL_FUNCTION(Encode, 2) {
};
