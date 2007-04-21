#include <Lang.h>
#include <Riva/Memory.h>
#include <string.h>

GLOBAL_FUNCTION(Ord, 1) {
	Lang$String_t *String = Args[0].Val;
	if (String->Length.Value) {
		Result->Val = Lang$Integer$new_small(*(char *)String->Blocks[0].Chars.Value);
		Result->Ref = 0;
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

GLOBAL_FUNCTION(Chr, 1) {
	Lang$Integer_smallt *Int = Args[0].Val;
	Result->Val = _new_char(Int->Value);
	Result->Ref = 0;
	return SUCCESS;
};

char *_flatten(Lang$String_t *String) {
	if (String->Count > 1) {
		char *Flat = Riva$Memory$alloc_atomic(String->Length.Value + 1);
		char *P = Flat;
		for (int I = 0; I < String->Count; ++I) {
			__builtin_memcpy(P, String->Blocks[I].Chars.Value, String->Blocks[I].Length.Value);
			P += String->Blocks[I].Length.Value;
		};
		*P = 0;
		return Flat;
	} else {
		char *Chars = String->Blocks[0].Chars.Value;
		long Length = String->Blocks[0].Length.Value;
		if (Chars[Length] == 0) {
			return Chars;
		} else {
			char *Flat = Riva$Memory$alloc_atomic(Length + 1);
			__builtin_memcpy(Flat, Chars, Length);
			Flat[Length] = 0;
			return Flat;
		};
	};
};

void _flatten_to(Lang$String_t *String, char *Result) {
	char *P = Result;
	for (int I = 0; I < String->Count; ++I) {
		__builtin_memcpy(P, String->Blocks[I].Chars.Value, String->Blocks[I].Length.Value);
		P += String->Blocks[I].Length.Value;
	};
	*P = 0;
};
