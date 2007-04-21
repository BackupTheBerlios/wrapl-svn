#include <Lang.h>
#include <Riva/Memory.h>

typedef struct chars_generator {
	Lang$Function_cstate State;
	Lang$String_block *Subject;
	long Left;
	char *Next;
} chars_generator;

typedef struct chars_resume_data {
	chars_generator *Generator;
	Lang$Function_argument Result;
} chars_resume_data;

static long resume_chars_string(chars_resume_data *Data) {
	chars_generator *Gen = Data->Generator;
	if (--Gen->Left < 0) {
		if ((Gen->Left = (++Gen->Subject)->Length.Value - 1) < 0) return FAILURE;
		Gen->Next = Gen->Subject->Chars.Value;
	};
	Data->Result.Val = Lang$String$new_length(Gen->Next++, 1);
	return SUSPEND;
};

METHOD("chars", TYP, Lang$String$T) {
	Lang$String_t *Arg = Args[0].Val;
	if (Arg->Length.Value == 0) return FAILURE;
	chars_generator *Gen = Riva$Memory$alloc(sizeof(chars_generator));
	Gen->Subject = Arg->Blocks;
	Gen->Left = Gen->Subject->Length.Value - 1;
	Gen->Next = Gen->Subject->Chars.Value;
	Gen->State.Run = Lang$Function$resume_c;
	Gen->State.Invoke = resume_chars_string;
	Result->Val = Lang$String$new_length(Gen->Next++, 1);
	Result->State = Gen;
	return SUSPEND;
};

typedef struct in_generator {
	Lang$Function_cstate State;
	Lang$String_block *Subject, *Pattern;
	unsigned long Start, Position, Limit;
} in_generator;

typedef struct in_resume_data {
	in_generator *Generator;
	Lang$Function_argument Result;
} in_resume_data;

static long resume_in_string_string(in_resume_data *Data) {
	// Search for occurences of Pattern in Subject starting at Index
	Lang$String_block *Subject = Data->Generator->Subject;
	Lang$String_block *Pattern = Data->Generator->Pattern;
	unsigned long Position = Data->Generator->Position, Start = Data->Generator->Start;
	unsigned long Limit = Data->Generator->Limit;
	for (;;) {
		++Position;
		if (Position > Limit) return FAILURE;
		Lang$String_block *S1 = Subject;
		unsigned long SL = S1->Length.Value - Start;
		if (SL == 0) {
			S1 = ++Subject;
			SL = S1->Length.Value;
			if (SL == 0) return FAILURE;
			Start = 0;
		};
		char *SC = S1->Chars.Value + Start;
		++Start;
		Lang$String_block *P1 = Pattern;
		char *PC = P1->Chars.Value;
		unsigned long PL = P1->Length.Value;
		for (;;) {
			if (PL == 0) {
				Data->Generator->Start = Start;
				Data->Generator->Position = Position;
				Data->Generator->Subject = Subject;
				Data->Result.Val = Lang$Integer$new_small(Position);
				return SUSPEND;
			};
			if (SL == 0) return FAILURE;
			if (*(SC++) != *(PC++)) break;
			if (--SL == 0) {
				S1 += 1;
				SL = S1->Length.Value;
				SC = S1->Chars.Value;
			};
			if (--PL == 0) {
				P1 += 1;
				PL = P1->Length.Value;
				PC = P1->Chars.Value;
			};
		};
	};
	return FAILURE;
};

METHOD("in", TYP, Lang$String$T, TYP, Lang$String$T) {
	Lang$String_t *Arg0 = Args[0].Val;
	Lang$String_t *Arg1 = Args[1].Val;
	Lang$String_block *Subject = Arg1->Blocks;
	Lang$String_block *Pattern = Arg0->Blocks;
	unsigned long Position = 0, Start = 0;
	for (;;) {
		++Position;
		Lang$String_block *S1 = Subject;
		unsigned long SL = S1->Length.Value - Start;
		if (SL == 0) {
			S1 = ++Subject;
			SL = S1->Length.Value;
			if (SL == 0) return FAILURE;
			Start = 0;
		};
		char *SC = S1->Chars.Value + Start;
		++Start;
		Lang$String_block *P1 = Pattern;
		char *PC = P1->Chars.Value;
		unsigned long PL = P1->Length.Value;
		for (;;) {
			if (PL == 0) {
				in_generator *Generator = new(in_generator);
				Generator->Start = Start;
				Generator->Position = Position;
				Generator->Pattern = Pattern;
				Generator->Subject = Subject;
				Generator->Limit = 0xFFFFFFFF;
				Generator->State.Run = Lang$Function$resume_c;
				Generator->State.Invoke = resume_in_string_string;
				Result->Val = Lang$Integer$new_small(Position);
				Result->State = Generator;
				return SUSPEND;
			};
			if (SL == 0) return FAILURE;
			if (*(SC++) != *(PC++)) break;
			if (--SL == 0) {
				S1 += 1;
				SL = S1->Length.Value;
				SC = S1->Chars.Value;
			};
			if (--PL == 0) {
				P1 += 1;
				PL = P1->Length.Value;
				PC = P1->Chars.Value;
			};
		};
	};
	return FAILURE;
};

METHOD("in", TYP, Lang$String$T, TYP, Lang$String$T, TYP, Lang$Integer$SmallT) {
	Lang$String_t *Arg0 = Args[0].Val;
	Lang$String_t *Arg1 = Args[1].Val;
	unsigned long Start = ((Lang$Integer_smallt *)Args[2].Val)->Value - 1;
	Lang$String_block *Subject = Arg1->Blocks;
	Lang$String_block *Pattern = Arg0->Blocks;
	unsigned long Position = Start;
	while (Start >= Subject->Length.Value) {
		Start -= Subject->Length.Value;
		++Subject;
		if (Subject->Length.Value == 0) return FAILURE;
	};
	for (;;) {
		++Position;
		Lang$String_block *S1 = Subject;
		unsigned long SL = S1->Length.Value - Start;
		if (SL == 0) {
			S1 = ++Subject;
			SL = S1->Length.Value;
			if (SL == 0) return FAILURE;
			Start = 0;
		};
		char *SC = S1->Chars.Value + Start;
		++Start;
		Lang$String_block *P1 = Pattern;
		char *PC = P1->Chars.Value;
		unsigned long PL = P1->Length.Value;
		for (;;) {
			if (PL == 0) {
				in_generator *Generator = new(in_generator);
				Generator->Start = Start;
				Generator->Position = Position;
				Generator->Pattern = Pattern;
				Generator->Subject = Subject;
				Generator->Limit = 0xFFFFFFFF;
				Generator->State.Run = Lang$Function$resume_c;
				Generator->State.Invoke = resume_in_string_string;
				Result->Val = Lang$Integer$new_small(Position);
				Result->State = Generator;
				return SUSPEND;
			};
			if (SL == 0) return FAILURE;
			if (*(SC++) != *(PC++)) break;
			if (--SL == 0) {
				S1 += 1;
				SL = S1->Length.Value;
				SC = S1->Chars.Value;
			};
			if (--PL == 0) {
				P1 += 1;
				PL = P1->Length.Value;
				PC = P1->Chars.Value;
			};
		};
	};
	return FAILURE;
};

METHOD("in", TYP, Lang$String$T, TYP, Lang$String$T, TYP, Lang$Integer$SmallT, TYP, Lang$Integer$SmallT) {
	Lang$String_t *Arg0 = Args[0].Val;
	Lang$String_t *Arg1 = Args[1].Val;
	unsigned long Start = ((Lang$Integer_smallt *)Args[2].Val)->Value - 1;
	unsigned long Limit = ((Lang$Integer_smallt *)Args[3].Val)->Value;
	Lang$String_block *Subject = Arg1->Blocks;
	Lang$String_block *Pattern = Arg0->Blocks;
	unsigned long Position = Start;
	while (Start >= Subject->Length.Value) {
		Start -= Subject->Length.Value;
		++Subject;
		if (Subject->Length.Value == 0) return FAILURE;
	};
	for (;;) {
		++Position;
		if (Position > Limit) return FAILURE;
		Lang$String_block *S1 = Subject;
		unsigned long SL = S1->Length.Value - Start;
		if (SL == 0) {
			S1 = ++Subject;
			SL = S1->Length.Value;
			if (SL == 0) return FAILURE;
			Start = 0;
		};
		char *SC = S1->Chars.Value + Start;
		++Start;
		Lang$String_block *P1 = Pattern;
		char *PC = P1->Chars.Value;
		unsigned long PL = P1->Length.Value;
		for (;;) {
			if (PL == 0) {
				in_generator *Generator = new(in_generator);
				Generator->Start = Start;
				Generator->Position = Position;
				Generator->Pattern = Pattern;
				Generator->Subject = Subject;
				Generator->Limit = Limit;
				Generator->State.Run = Lang$Function$resume_c;
				Generator->State.Invoke = resume_in_string_string;
				Result->Val = Lang$Integer$new_small(Position);
				Result->State = Generator;
				return SUSPEND;
			};
			if (SL == 0) return FAILURE;
			if (*(SC++) != *(PC++)) break;
			if (--SL == 0) {
				S1 += 1;
				SL = S1->Length.Value;
				SC = S1->Chars.Value;
			};
			if (--PL == 0) {
				P1 += 1;
				PL = P1->Length.Value;
				PC = P1->Chars.Value;
			};
		};
	};
	return FAILURE;
};

METHOD("find", TYP, Lang$String$T, TYP, Lang$String$T) {
	Lang$String_t *Arg0 = Args[1].Val;
	Lang$String_t *Arg1 = Args[0].Val;
	Lang$String_block *Subject = Arg1->Blocks;
	Lang$String_block *Pattern = Arg0->Blocks;
	unsigned long Position = 0, Start = 0;
	for (;;) {
		++Position;
		Lang$String_block *S1 = Subject;
		unsigned long SL = S1->Length.Value - Start;
		if (SL == 0) {
			S1 = ++Subject;
			SL = S1->Length.Value;
			if (SL == 0) return FAILURE;
			Start = 0;
		};
		char *SC = S1->Chars.Value + Start;
		++Start;
		Lang$String_block *P1 = Pattern;
		char *PC = P1->Chars.Value;
		unsigned long PL = P1->Length.Value;
		for (;;) {
			if (PL == 0) {
				in_generator *Generator = new(in_generator);
				Generator->Start = Start;
				Generator->Position = Position;
				Generator->Pattern = Pattern;
				Generator->Subject = Subject;
				Generator->Limit = 0xFFFFFFFF;
				Generator->State.Run = Lang$Function$resume_c;
				Generator->State.Invoke = resume_in_string_string;
				Result->Val = Lang$Integer$new_small(Position);
				Result->State = Generator;
				return SUSPEND;
			};
			if (SL == 0) return FAILURE;
			if (*(SC++) != *(PC++)) break;
			if (--SL == 0) {
				S1 += 1;
				SL = S1->Length.Value;
				SC = S1->Chars.Value;
			};
			if (--PL == 0) {
				P1 += 1;
				PL = P1->Length.Value;
				PC = P1->Chars.Value;
			};
		};
	};
	return FAILURE;
};

METHOD("find", TYP, Lang$String$T, TYP, Lang$String$T, TYP, Lang$Integer$SmallT) {
	Lang$String_t *Arg0 = Args[1].Val;
	Lang$String_t *Arg1 = Args[0].Val;
	unsigned long Start = ((Lang$Integer_smallt *)Args[2].Val)->Value - 1;
	Lang$String_block *Subject = Arg1->Blocks;
	Lang$String_block *Pattern = Arg0->Blocks;
	unsigned long Position = Start;
	while (Start >= Subject->Length.Value) {
		Start -= Subject->Length.Value;
		++Subject;
		if (Subject->Length.Value == 0) return FAILURE;
	};
	for (;;) {
		++Position;
		Lang$String_block *S1 = Subject;
		unsigned long SL = S1->Length.Value - Start;
		if (SL == 0) {
			S1 = ++Subject;
			SL = S1->Length.Value;
			if (SL == 0) return FAILURE;
			Start = 0;
		};
		char *SC = S1->Chars.Value + Start;
		++Start;
		Lang$String_block *P1 = Pattern;
		char *PC = P1->Chars.Value;
		unsigned long PL = P1->Length.Value;
		for (;;) {
			if (PL == 0) {
				in_generator *Generator = new(in_generator);
				Generator->Start = Start;
				Generator->Position = Position;
				Generator->Pattern = Pattern;
				Generator->Subject = Subject;
				Generator->Limit = 0xFFFFFFFF;
				Generator->State.Run = Lang$Function$resume_c;
				Generator->State.Invoke = resume_in_string_string;
				Result->Val = Lang$Integer$new_small(Position);
				Result->State = Generator;
				return SUSPEND;
			};
			if (SL == 0) return FAILURE;
			if (*(SC++) != *(PC++)) break;
			if (--SL == 0) {
				S1 += 1;
				SL = S1->Length.Value;
				SC = S1->Chars.Value;
			};
			if (--PL == 0) {
				P1 += 1;
				PL = P1->Length.Value;
				PC = P1->Chars.Value;
			};
		};
	};
	return FAILURE;
};

METHOD("find", TYP, Lang$String$T, TYP, Lang$String$T, TYP, Lang$Integer$SmallT, TYP, Lang$Integer$SmallT) {
	Lang$String_t *Arg0 = Args[1].Val;
	Lang$String_t *Arg1 = Args[0].Val;
	unsigned long Start = ((Lang$Integer_smallt *)Args[2].Val)->Value - 1;
	unsigned long Limit = ((Lang$Integer_smallt *)Args[3].Val)->Value;
	Lang$String_block *Subject = Arg1->Blocks;
	Lang$String_block *Pattern = Arg0->Blocks;
	unsigned long Position = Start;
	while (Start >= Subject->Length.Value) {
		Start -= Subject->Length.Value;
		++Subject;
		if (Subject->Length.Value == 0) return FAILURE;
	};
	for (;;) {
		++Position;
		if (Position > Limit) return FAILURE;
		Lang$String_block *S1 = Subject;
		unsigned long SL = S1->Length.Value - Start;
		if (SL == 0) {
			S1 = ++Subject;
			SL = S1->Length.Value;
			if (SL == 0) return FAILURE;
			Start = 0;
		};
		char *SC = S1->Chars.Value + Start;
		++Start;
		Lang$String_block *P1 = Pattern;
		char *PC = P1->Chars.Value;
		unsigned long PL = P1->Length.Value;
		for (;;) {
			if (PL == 0) {
				in_generator *Generator = new(in_generator);
				Generator->Start = Start;
				Generator->Position = Position;
				Generator->Pattern = Pattern;
				Generator->Subject = Subject;
				Generator->Limit = Limit;
				Generator->State.Run = Lang$Function$resume_c;
				Generator->State.Invoke = resume_in_string_string;
				Result->Val = Lang$Integer$new_small(Position);
				Result->State = Generator;
				return SUSPEND;
			};
			if (SL == 0) return FAILURE;
			if (*(SC++) != *(PC++)) break;
			if (--SL == 0) {
				S1 += 1;
				SL = S1->Length.Value;
				SC = S1->Chars.Value;
			};
			if (--PL == 0) {
				P1 += 1;
				PL = P1->Length.Value;
				PC = P1->Chars.Value;
			};
		};
	};
	return FAILURE;
};

typedef struct to_real_state {
	Lang$Function_cstate C;
	double Current, Limit, Increment;
} to_real_state;

typedef struct to_real_resume_data {
	to_real_state *State;
	Lang$Function_argument Result;
} to_real_resume_data;

static long resume_to_real_inc(to_real_resume_data *Data) {
	to_real_state *State = Data->State;
	double Current = State->Current + State->Increment;
	if (Current > State->Limit) return FAILURE;
	if (Current == State->Limit) {
		Data->Result.Val = Lang$Real$new(Current);
		return SUCCESS;
	};
	State->Current = Current;
	Data->Result.Val = Lang$Real$new(Current);
	return SUSPEND;
};

static long resume_to_real_dec(to_real_resume_data *Data) {
	to_real_state *State = Data->State;
	double Current = State->Current + State->Increment;
	if (Current < State->Limit) return FAILURE;
	if (Current == State->Limit) {
		Data->Result.Val = Lang$Real$new(Current);
		return SUCCESS;
	};
	State->Current = Current;
	Data->Result.Val = Lang$Real$new(Current);
	return SUSPEND;
};

METHOD("to", TYP, Lang$Real$T, TYP, Lang$Real$T) {
	double From = ((Lang$Real_t *)Args[0].Val)->Value;
	double To = ((Lang$Real_t *)Args[1].Val)->Value;
	if (From > To) return FAILURE;
	if (From == To) {
		Result->Val = Args[0].Val;
		return SUCCESS;
	};
	to_real_state *State = new(to_real_state);
	State->Current = From;
	State->Limit = To;
	State->Increment = 1.0;
	State->C.Run = Lang$Function$resume_c;
	State->C.Invoke = resume_to_real_inc;
	Result->Val = Args[0].Val;
	Result->State = State;
	return SUSPEND;
};

extern void resume_repeat_value(void);

typedef struct repeat_value_state {
	void *Run, *Resume, *Chain;
	Lang$Object_t *Value;
} repeat_value_state;

METHOD("to", TYP, Lang$Real$T, TYP, Lang$Real$T, TYP, Lang$Real$T) {
	double From = ((Lang$Real_t *)Args[0].Val)->Value;
	double To = ((Lang$Real_t *)Args[1].Val)->Value;
	double Increment = ((Lang$Real_t *)Args[2].Val)->Value;
	if (Increment > 0.0) {
		if (From > To) return FAILURE;
		if (From == To) {
			Result->Val = Args[0].Val;
			return SUCCESS;
		};
		to_real_state *State = new(to_real_state);
		State->Current = From;
		State->Limit = To;
		State->Increment = Increment;
		State->C.Run = Lang$Function$resume_c;
		State->C.Invoke = resume_to_real_inc;
		Result->Val = Args[0].Val;
		Result->State = State;
		return SUSPEND;
	} else if (Increment < 0.0) {
		if (From < To) return FAILURE;
		if (From == To) {
			Result->Val = Args[0].Val;
			return SUCCESS;
		};
		to_real_state *State = new(to_real_state);
		State->Current = From;
		State->Limit = To;
		State->Increment = Increment;
		State->C.Run = Lang$Function$resume_c;
		State->C.Invoke = resume_to_real_dec;
		Result->Val = Args[0].Val;
		Result->State = State;
		return SUSPEND;
	} else {
		repeat_value_state *State = new(repeat_value_state);
		Result->Val = State->Value = Args[0].Val;
		State->Run = resume_repeat_value;
		Result->State = State;
		return SUSPEND;
	};
};
