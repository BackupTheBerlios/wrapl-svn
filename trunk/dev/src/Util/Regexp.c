#include <Std.h>
#include <Riva.h>

#include <tre/regex.h>

typedef struct regexp_t {
	Std$Type_t *Type;
	regex_t Handle[1];
} regexp_t;

TYPE(T);

GLOBAL_FUNCTION(New, 1) {
	regexp_t *R = new(regexp_t);
	int Flags = REG_EXTENDED;
	if (regcomp(R->Handle, Std$String$flatten(Args[0].Val), Flags)) {
		Result->Val = "Invalid regular expression";
		return MESSAGE;
	} else {
		R->Type = T;
		Result->Val = R;
		return SUCCESS;
	};
};

typedef struct context_t {
	Std$String_block *Head;
	Std$String_block *Block;
	char *Chars;
	int Rem;
	int Pos;
} context_t;

static int get_next_char(tre_char_t *Char, unsigned int *PosAdd, context_t *Context) {
	if (Context->Rem-- == 0) {
		Context->Block++;
		Context->Rem = Context->Block->Length.Value;
		if (Context->Rem == 0) return 1;
		Char = Context->Block->Chars.Value;
	};
	Char[0] = *(Context->Chars++);
	PosAdd[0] = 1;
	Context->Pos++;
	return 0;
};

static void rewind(size_t Pos, context_t *Context) {
	Context->Pos = Pos;
	Std$String_block *Block = Context->Head;
	while (Pos >= Block->Length.Value) {
		Pos -= Block->Length.Value;
		Block++;
	};
	Context->Block = Block;
	Context->Rem = Block->Length.Value - Pos;
	Context->Chars = Block->Chars.Value + Pos;
};

static int compare(size_t Pos1, size_t Pos2, size_t Len, context_t *Context) {
	Std$String_block *Block1 = Context->Head;
	while (Pos1 >= Block1->Length.Value) {
		Pos1 -= Block1->Length.Value;
		Block1++;
	};
	int Rem1 = Block1->Length.Value - Pos1;
	char *Chars1 = Block1->Chars.Value + Pos1;
	Std$String_block *Block2 = Context->Head;
	while (Pos2 >= Block2->Length.Value) {
		Pos2 -= Block2->Length.Value;
		Block2++;
	};
	int Rem2 = Block2->Length.Value - Pos2;
	char *Chars2 = Block2->Chars.Value + Pos2;
	while (Len--) {
		if (Rem1-- == 0) {
			Block1++;
			Rem1 = Block1->Length.Value;
			if (Rem1 == 0) return 1;
			Chars1 = Block1->Chars.Value;
		};
		if (Rem2-- == 0) {
			Block2++;
			Rem2 = Block2->Length.Value;
			if (Rem2 == 0) return 1;
			Chars2 = Block2->Chars.Value;
		};
		if (*(Chars1++) != *(Chars2++)) return 1;
	};
	return 0;
};

extern Std$String_t *index_string_small_small(Std$String_t *String, int A, int B);

METHOD("match", TYP, T, TYP, Std$String$T) {
	regex_t *PReg = ((regexp_t *)Args[0].Val)->Handle;
	Std$String_t *String = Args[1].Val;
	context_t Context[1] = {{
		String->Blocks,
		String->Blocks,
		String->Blocks->Chars.Value,
		String->Blocks->Length.Value,
		0
	}};
	tre_str_source Source[1] = {{
		get_next_char,
		rewind,
		compare,
		Context
	}};
	regmatch_t PMatch[PReg->re_nsub];
	if (reguexec(PReg, Source, PReg->re_nsub, PMatch, 0)) return FAILURE;
	Std$Function_argument *Out = Args + 2;
	int Max = Count - 2;
	if (Max > PReg->re_nsub) Max = PReg->re_nsub;
	for (int I = 0; I < Max; ++I) {
		if (PMatch[I].rm_so != -1) {
			if (Out->Ref) Out->Ref[0] = index_string_small_small(String, PMatch[I].rm_so, PMatch[I].rm_eo);
		};
		Out++;
	};
	Result->Val = Std$Integer$new_small(Context->Pos);
	return SUCCESS;
};
