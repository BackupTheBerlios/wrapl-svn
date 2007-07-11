#include <Std.h>
#include <Riva/Memory.h>
#include <string.h>
#include <stdarg.h>

extern Std$String_t Nil[];

char *_flatten(Std$String_t *String) {
	if (String == Nil) return 0;
	if (String->Count > 1) {
		char *Flat = Riva$Memory$alloc_atomic(String->Length.Value + 1);
		char *P = Flat;
		for (int I = 0; I < String->Count; ++I) {
			memcpy(P, String->Blocks[I].Chars.Value, String->Blocks[I].Length.Value);
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
			memcpy(Flat, Chars, Length);
			Flat[Length] = 0;
			return Flat;
		};
	};
};

void _flatten_to(Std$String_t *String, char *Result) {
	char *P = Result;
	for (int I = 0; I < String->Count; ++I) {
		__builtin_memcpy(P, String->Blocks[I].Chars.Value, String->Blocks[I].Length.Value);
		P += String->Blocks[I].Length.Value;
	};
	*P = 0;
};
extern Std$Type_t T[];

Std$String_t *_new_format(const char *Format, ...) {
	Std$String_t *String = Riva$Memory$alloc(sizeof(Std$String_t) + sizeof(Std$String_block));
	String->Type = T;
	String->Count = 1;
	String->Blocks[0].Length.Type = String->Length.Type = Std$Integer$SmallT;
	String->Blocks[0].Chars.Type = Std$Address$T;
	va_list Args;
	va_start(Args, Format);
	String->Length.Value = String->Blocks[0].Length.Value = vasprintf(&String->Blocks[0].Chars.Value, Format, Args);
	va_end(Args);
	return String;
};
