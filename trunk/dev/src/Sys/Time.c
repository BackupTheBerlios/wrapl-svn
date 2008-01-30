#include <Std.h>
#include <Sys/Time.h>
#include <Riva/Memory.h>

#include <stdlib.h>
#include <string.h>

TYPE(T);

GLOBAL_FUNCTION(Now, 0) {
	Sys$Time_t *Time = new(Sys$Time_t);
	Time->Type = T;
	Time->Value = time(0);
	Result->Val = Time;
	return SUCCESS;
};

Sys$Time_t *_new(time_t Value) {
	Sys$Time_t *Time = new(Sys$Time_t);
	Time->Type = T;
	Time->Value = Value;
	return Time;
};

METHOD(">", TYP, T, TYP, T) {
	Sys$Time_t *A = Args[0].Val;
	Sys$Time_t *B = Args[1].Val;
	if (A->Value > B->Value) {
		Result->Arg = Args[1];
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

METHOD("<", TYP, T, TYP, T) {
	Sys$Time_t *A = Args[0].Val;
	Sys$Time_t *B = Args[1].Val;
	if (A->Value < B->Value) {
		Result->Arg = Args[1];
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

METHOD(">=", TYP, T, TYP, T) {
	Sys$Time_t *A = Args[0].Val;
	Sys$Time_t *B = Args[1].Val;
	if (A->Value >= B->Value) {
		Result->Arg = Args[1];
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

METHOD("<=", TYP, T, TYP, T) {
	Sys$Time_t *A = Args[0].Val;
	Sys$Time_t *B = Args[1].Val;
	if (A->Value <= B->Value) {
		Result->Arg = Args[1];
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

METHOD("=", TYP, T, TYP, T) {
	Sys$Time_t *A = Args[0].Val;
	Sys$Time_t *B = Args[1].Val;
	if (A->Value == B->Value) {
		Result->Arg = Args[1];
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

METHOD("~=", TYP, T, TYP, T) {
	Sys$Time_t *A = Args[0].Val;
	Sys$Time_t *B = Args[1].Val;
	if (A->Value != B->Value) {
		Result->Arg = Args[1];
		return SUCCESS;
	} else {
		return FAILURE;
	};
};
