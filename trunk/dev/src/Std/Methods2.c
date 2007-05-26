#include <Std.h>
#include <Riva/Memory.h>

typedef struct chars_generator {
	Std$Function_cstate State;
	Std$String_block *Subject;
	long Left;
	char *Next;
} chars_generator;

typedef struct chars_resume_data {
	chars_generator *Generator;
	Std$Function_argument Result;
} chars_resume_data;

static long resume_chars_string(chars_resume_data *Data) {
	chars_generator *Gen = Data->Generator;
	if (--Gen->Left < 0) {
		if ((Gen->Left = (++Gen->Subject)->Length.Value - 1) < 0) return FAILURE;
		Gen->Next = Gen->Subject->Chars.Value;
	};
	Data->Result.Val = Std$String$new_length(Gen->Next++, 1);
	return SUSPEND;
};

METHOD("chars", TYP, Std$String$T) {
	Std$String_t *Arg = Args[0].Val;
	if (Arg->Length.Value == 0) return FAILURE;
	chars_generator *Gen = Riva$Memory$alloc(sizeof(chars_generator));
	Gen->Subject = Arg->Blocks;
	Gen->Left = Gen->Subject->Length.Value - 1;
	Gen->Next = Gen->Subject->Chars.Value;
	Gen->State.Run = Std$Function$resume_c;
	Gen->State.Invoke = resume_chars_string;
	Result->Val = Std$String$new_length(Gen->Next++, 1);
	Result->State = Gen;
	return SUSPEND;
};

typedef struct in_generator {
	Std$Function_cstate State;
	Std$String_block *Subject, *Pattern;
	unsigned long Start, Position, Limit;
} in_generator;

typedef struct in_resume_data {
	in_generator *Generator;
	Std$Function_argument Result;
} in_resume_data;

static long resume_in_string_string(in_resume_data *Data) {
	// Search for occurences of Pattern in Subject starting at Index
	Std$String_block *Subject = Data->Generator->Subject;
	Std$String_block *Pattern = Data->Generator->Pattern;
	unsigned long Position = Data->Generator->Position, Start = Data->Generator->Start;
	unsigned long Limit = Data->Generator->Limit;
	for (;;) {
		++Position;
		if (Position > Limit) return FAILURE;
		Std$String_block *S1 = Subject;
		unsigned long SL = S1->Length.Value - Start;
		if (SL == 0) {
			S1 = ++Subject;
			SL = S1->Length.Value;
			if (SL == 0) return FAILURE;
			Start = 0;
		};
		char *SC = S1->Chars.Value + Start;
		++Start;
		Std$String_block *P1 = Pattern;
		char *PC = P1->Chars.Value;
		unsigned long PL = P1->Length.Value;
		for (;;) {
			if (PL == 0) {
				Data->Generator->Start = Start;
				Data->Generator->Position = Position;
				Data->Generator->Subject = Subject;
				Data->Result.Val = Std$Integer$new_small(Position);
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

METHOD("in", TYP, Std$String$T, TYP, Std$String$T) {
	Std$String_t *Arg0 = Args[0].Val;
	Std$String_t *Arg1 = Args[1].Val;
	Std$String_block *Subject = Arg1->Blocks;
	Std$String_block *Pattern = Arg0->Blocks;
	unsigned long Position = 0, Start = 0;
	for (;;) {
		++Position;
		Std$String_block *S1 = Subject;
		unsigned long SL = S1->Length.Value - Start;
		if (SL == 0) {
			S1 = ++Subject;
			SL = S1->Length.Value;
			if (SL == 0) return FAILURE;
			Start = 0;
		};
		char *SC = S1->Chars.Value + Start;
		++Start;
		Std$String_block *P1 = Pattern;
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
				Generator->State.Run = Std$Function$resume_c;
				Generator->State.Invoke = resume_in_string_string;
				Result->Val = Std$Integer$new_small(Position);
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

METHOD("in", TYP, Std$String$T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	Std$String_t *Arg0 = Args[0].Val;
	Std$String_t *Arg1 = Args[1].Val;
	unsigned long Start = ((Std$Integer_smallt *)Args[2].Val)->Value - 1;
	Std$String_block *Subject = Arg1->Blocks;
	Std$String_block *Pattern = Arg0->Blocks;
	unsigned long Position = Start;
	while (Start >= Subject->Length.Value) {
		Start -= Subject->Length.Value;
		++Subject;
		if (Subject->Length.Value == 0) return FAILURE;
	};
	for (;;) {
		++Position;
		Std$String_block *S1 = Subject;
		unsigned long SL = S1->Length.Value - Start;
		if (SL == 0) {
			S1 = ++Subject;
			SL = S1->Length.Value;
			if (SL == 0) return FAILURE;
			Start = 0;
		};
		char *SC = S1->Chars.Value + Start;
		++Start;
		Std$String_block *P1 = Pattern;
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
				Generator->State.Run = Std$Function$resume_c;
				Generator->State.Invoke = resume_in_string_string;
				Result->Val = Std$Integer$new_small(Position);
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

METHOD("in", TYP, Std$String$T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	Std$String_t *Arg0 = Args[0].Val;
	Std$String_t *Arg1 = Args[1].Val;
	unsigned long Start = ((Std$Integer_smallt *)Args[2].Val)->Value - 1;
	unsigned long Limit = ((Std$Integer_smallt *)Args[3].Val)->Value;
	Std$String_block *Subject = Arg1->Blocks;
	Std$String_block *Pattern = Arg0->Blocks;
	unsigned long Position = Start;
	while (Start >= Subject->Length.Value) {
		Start -= Subject->Length.Value;
		++Subject;
		if (Subject->Length.Value == 0) return FAILURE;
	};
	for (;;) {
		++Position;
		if (Position > Limit) return FAILURE;
		Std$String_block *S1 = Subject;
		unsigned long SL = S1->Length.Value - Start;
		if (SL == 0) {
			S1 = ++Subject;
			SL = S1->Length.Value;
			if (SL == 0) return FAILURE;
			Start = 0;
		};
		char *SC = S1->Chars.Value + Start;
		++Start;
		Std$String_block *P1 = Pattern;
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
				Generator->State.Run = Std$Function$resume_c;
				Generator->State.Invoke = resume_in_string_string;
				Result->Val = Std$Integer$new_small(Position);
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

METHOD("find", TYP, Std$String$T, TYP, Std$String$T) {
	Std$String_t *Arg0 = Args[1].Val;
	Std$String_t *Arg1 = Args[0].Val;
	Std$String_block *Subject = Arg1->Blocks;
	Std$String_block *Pattern = Arg0->Blocks;
	unsigned long Position = 0, Start = 0;
	for (;;) {
		++Position;
		Std$String_block *S1 = Subject;
		unsigned long SL = S1->Length.Value - Start;
		if (SL == 0) {
			S1 = ++Subject;
			SL = S1->Length.Value;
			if (SL == 0) return FAILURE;
			Start = 0;
		};
		char *SC = S1->Chars.Value + Start;
		++Start;
		Std$String_block *P1 = Pattern;
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
				Generator->State.Run = Std$Function$resume_c;
				Generator->State.Invoke = resume_in_string_string;
				Result->Val = Std$Integer$new_small(Position);
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

METHOD("find", TYP, Std$String$T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	Std$String_t *Arg0 = Args[1].Val;
	Std$String_t *Arg1 = Args[0].Val;
	unsigned long Start = ((Std$Integer_smallt *)Args[2].Val)->Value - 1;
	Std$String_block *Subject = Arg1->Blocks;
	Std$String_block *Pattern = Arg0->Blocks;
	unsigned long Position = Start;
	while (Start >= Subject->Length.Value) {
		Start -= Subject->Length.Value;
		++Subject;
		if (Subject->Length.Value == 0) return FAILURE;
	};
	for (;;) {
		++Position;
		Std$String_block *S1 = Subject;
		unsigned long SL = S1->Length.Value - Start;
		if (SL == 0) {
			S1 = ++Subject;
			SL = S1->Length.Value;
			if (SL == 0) return FAILURE;
			Start = 0;
		};
		char *SC = S1->Chars.Value + Start;
		++Start;
		Std$String_block *P1 = Pattern;
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
				Generator->State.Run = Std$Function$resume_c;
				Generator->State.Invoke = resume_in_string_string;
				Result->Val = Std$Integer$new_small(Position);
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

METHOD("find", TYP, Std$String$T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	Std$String_t *Arg0 = Args[1].Val;
	Std$String_t *Arg1 = Args[0].Val;
	unsigned long Start = ((Std$Integer_smallt *)Args[2].Val)->Value - 1;
	unsigned long Limit = ((Std$Integer_smallt *)Args[3].Val)->Value;
	Std$String_block *Subject = Arg1->Blocks;
	Std$String_block *Pattern = Arg0->Blocks;
	unsigned long Position = Start;
	while (Start >= Subject->Length.Value) {
		Start -= Subject->Length.Value;
		++Subject;
		if (Subject->Length.Value == 0) return FAILURE;
	};
	for (;;) {
		++Position;
		if (Position > Limit) return FAILURE;
		Std$String_block *S1 = Subject;
		unsigned long SL = S1->Length.Value - Start;
		if (SL == 0) {
			S1 = ++Subject;
			SL = S1->Length.Value;
			if (SL == 0) return FAILURE;
			Start = 0;
		};
		char *SC = S1->Chars.Value + Start;
		++Start;
		Std$String_block *P1 = Pattern;
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
				Generator->State.Run = Std$Function$resume_c;
				Generator->State.Invoke = resume_in_string_string;
				Result->Val = Std$Integer$new_small(Position);
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
	Std$Function_cstate C;
	double Current, Limit, Increment;
} to_real_state;

typedef struct to_real_resume_data {
	to_real_state *State;
	Std$Function_argument Result;
} to_real_resume_data;

static long resume_to_real_inc(to_real_resume_data *Data) {
	to_real_state *State = Data->State;
	double Current = State->Current + State->Increment;
	if (Current > State->Limit) return FAILURE;
	if (Current == State->Limit) {
		Data->Result.Val = Std$Real$new(Current);
		return SUCCESS;
	};
	State->Current = Current;
	Data->Result.Val = Std$Real$new(Current);
	return SUSPEND;
};

static long resume_to_real_dec(to_real_resume_data *Data) {
	to_real_state *State = Data->State;
	double Current = State->Current + State->Increment;
	if (Current < State->Limit) return FAILURE;
	if (Current == State->Limit) {
		Data->Result.Val = Std$Real$new(Current);
		return SUCCESS;
	};
	State->Current = Current;
	Data->Result.Val = Std$Real$new(Current);
	return SUSPEND;
};

METHOD("to", TYP, Std$Real$T, TYP, Std$Real$T) {
	double From = ((Std$Real_t *)Args[0].Val)->Value;
	double To = ((Std$Real_t *)Args[1].Val)->Value;
	if (From > To) return FAILURE;
	if (From == To) {
		Result->Val = Args[0].Val;
		return SUCCESS;
	};
	to_real_state *State = new(to_real_state);
	State->Current = From;
	State->Limit = To;
	State->Increment = 1.0;
	State->C.Run = Std$Function$resume_c;
	State->C.Invoke = resume_to_real_inc;
	Result->Val = Args[0].Val;
	Result->State = State;
	return SUSPEND;
};

extern void resume_repeat_value(void);

typedef struct repeat_value_state {
	void *Run, *Resume, *Chain;
	Std$Object_t *Value;
} repeat_value_state;

METHOD("to", TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T) {
	double From = ((Std$Real_t *)Args[0].Val)->Value;
	double To = ((Std$Real_t *)Args[1].Val)->Value;
	double Increment = ((Std$Real_t *)Args[2].Val)->Value;
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
		State->C.Run = Std$Function$resume_c;
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
		State->C.Run = Std$Function$resume_c;
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
