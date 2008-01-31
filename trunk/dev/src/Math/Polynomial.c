#include <Std.h>
#include <Riva/Memory.h>
#include <stdint.h>

typedef struct polynomial_t {
	Std$Type_t *Type;
	Std$Integer_smallt Degree;
	Std$Object_t *Coefficients[];
} polynomial_t;

TYPE(T);

GLOBAL_FUNCTION(New, 0) {
	polynomial_t *P = Riva$Memory$alloc(sizeof(polynomial_t) + Count * sizeof(Std$Object_t *));
	P->Type = T;
	P->Degree.Type = Std$Integer$SmallT;
	P->Degree.Value = Count - 1;
	for (int I = 0; I < Count; ++I) P->Coefficients[I] = Args[I].Val;
	Result->Val = P;
	return SUCCESS;
};


METHOD("degree", TYP, T) {
	polynomial_t *P = Args[0].Val;
	Result->Val = &(P->Degree);
	return SUCCESS;
};

SYMBOL($AT, "@");

static Std$Object_t *SpacePlusSpace, *ZeroStr, *XStr, *XPowStr;

METHOD("@", TYP, T, VAL, Std$String$T) {
	polynomial_t *P = Args[0].Val;
	int Degree = P->Degree.Value;
	switch (Degree) {
	case -1: {
		Result->Val = Std$String$new("0");
		return SUCCESS;
	};
	case 0: {
		Std$Function_result Buffer;
		Std$Function$call($AT, 2, &Buffer, P->Coefficients[0], 0, Std$String$T, 0);
		Result->Val = Buffer.Val;
		return SUCCESS;
	};
	case 1: {
		Std$Function_result Buffer;
		Std$Function$call($AT, 2, &Buffer, P->Coefficients[0], 0, Std$String$T, 0);
		Std$String_t *S = Buffer.Val;
		Std$Function$call($AT, 2, &Buffer, P->Coefficients[1], 0, Std$String$T, 0);
		Result->Val = Std$String$add(Std$String$add(Buffer.Val, XStr), Std$String$add(SpacePlusSpace, S));
		return SUCCESS;
	};
	default: {
		Std$Function_result Buffer;
		Std$Function$call($AT, 2, &Buffer, P->Coefficients[0], 0, Std$String$T, 0);
		Std$String_t *S = Buffer.Val;
		Std$Function$call($AT, 2, &Buffer, P->Coefficients[1], 0, Std$String$T, 0);
		S = Std$String$add(Std$String$add(Buffer.Val, XStr), Std$String$add(SpacePlusSpace, S));
		for (int I = 2; I <= Degree; ++I) {
			Std$Function$call($AT, 2, &Buffer, P->Coefficients[I], 0, Std$String$T, 0);
			char *Power;
			asprintf(&Power, "%d", I);
			S = Std$String$add(SpacePlusSpace, S);
			S = Std$String$add(Std$String$new(Power), S);
			S = Std$String$add(XPowStr, S);
			S = Std$String$add(Buffer.Val, S);
		};
		Result->Val = S;
		return SUCCESS;
	};
	};
};

SYMBOL($is0, "is0");
SYMBOL($ADD, "+");

METHOD("+", TYP, T, TYP, T) {
	polynomial_t *A = Args[0].Val;
	polynomial_t *B = Args[1].Val;
	if (A->Degree.Value < B->Degree.Value) {
		polynomial_t *C = Riva$Memory$alloc(sizeof(polynomial_t) + (B->Degree.Value + 1) * sizeof(Std$Object_t *));
		C->Type = T;
		C->Degree.Type = Std$Integer$SmallT;
		C->Degree.Value = B->Degree.Value;
		for (int I = A->Degree.Value; I >= 0; --I) {
			Std$Function_result Buffer;
			Std$Function$call($ADD, 2, &Buffer, A->Coefficients[I], 0, B->Coefficients[I], 0);
			C->Coefficients[I] = Buffer.Val;
		};
		for (int I = A->Degree.Value; ++I <= B->Degree.Value;) {
			C->Coefficients[I] = B->Coefficients[I];
		};
		C->Degree.Value = B->Degree.Value;
		Result->Val = C;
		return SUCCESS;
	} else if (A->Degree.Value > B->Degree.Value) {
		polynomial_t *C = Riva$Memory$alloc(sizeof(polynomial_t) + (A->Degree.Value + 1) * sizeof(Std$Object_t *));
		C->Type = T;
		C->Degree.Type = Std$Integer$SmallT;
		C->Degree.Value = A->Degree.Value;
		for (int I = B->Degree.Value; I >= 0; --I) {
			Std$Function_result Buffer;
			Std$Function$call($ADD, 2, &Buffer, A->Coefficients[I], 0, B->Coefficients[I], 0);
			C->Coefficients[I] = Buffer.Val;
		};
		for (int I = B->Degree.Value; ++I <= A->Degree.Value;) {
			C->Coefficients[I] = A->Coefficients[I];
		};
		C->Degree.Value = A->Degree.Value;
		Result->Val = C;
		return SUCCESS;
	} else {
		int Degree = A->Degree.Value;
		polynomial_t *C = Riva$Memory$alloc(sizeof(polynomial_t) + (Degree + 1) * sizeof(Std$Object_t *));
		C->Type = T;
		C->Degree.Type = Std$Integer$SmallT;
		for (int I = Degree; I >= 0; --I) {
			Std$Function_result Buffer;
			Std$Function$call($ADD, 2, &Buffer, A->Coefficients[I], 0, B->Coefficients[I], 0);
			C->Coefficients[I] = Buffer.Val;
		};
		while (Degree >= 0) {
			Std$Function_result Buffer;
			if (Std$Function$call($is0, 1, &Buffer, C->Coefficients[Degree], 0) >= FAILURE) break;
			--Degree;
		};
		C->Degree.Value = Degree;
		Result->Val = C;
		return SUCCESS;
	};
};

SYMBOL($SUB, "-");

METHOD("-", TYP, T, TYP, T) {
	polynomial_t *A = Args[0].Val;
	polynomial_t *B = Args[1].Val;
	if (A->Degree.Value < B->Degree.Value) {
		polynomial_t *C = Riva$Memory$alloc(sizeof(polynomial_t) + (B->Degree.Value + 1) * sizeof(Std$Object_t *));
		C->Type = T;
		C->Degree.Type = Std$Integer$SmallT;
		C->Degree.Value = B->Degree.Value;
		for (int I = A->Degree.Value; I >= 0; --I) {
			Std$Function_result Buffer;
			Std$Function$call($SUB, 2, &Buffer, A->Coefficients[I], 0, B->Coefficients[I], 0);
			C->Coefficients[I] = Buffer.Val;
		};
		for (int I = A->Degree.Value; ++I <= B->Degree.Value;) {
			Std$Function_result Buffer;
			Std$Function$call($SUB, 1, &Buffer, B->Coefficients[I], 0);
			C->Coefficients[I] = Buffer.Val;
		};
		C->Degree.Value = B->Degree.Value;
		Result->Val = C;
		return SUCCESS;
	} else if (A->Degree.Value > B->Degree.Value) {
		polynomial_t *C = Riva$Memory$alloc(sizeof(polynomial_t) + (A->Degree.Value + 1) * sizeof(Std$Object_t *));
		C->Type = T;
		C->Degree.Type = Std$Integer$SmallT;
		C->Degree.Value = A->Degree.Value;
		for (int I = B->Degree.Value; I >= 0; --I) {
			Std$Function_result Buffer;
			Std$Function$call($SUB, 2, &Buffer, A->Coefficients[I], 0, B->Coefficients[I], 0);
			C->Coefficients[I] = Buffer.Val;
		};
		for (int I = B->Degree.Value; ++I <= A->Degree.Value;) {
			C->Coefficients[I] = A->Coefficients[I];
		};
		C->Degree.Value = A->Degree.Value;
		Result->Val = C;
		return SUCCESS;
	} else {
		int Degree = A->Degree.Value;
		polynomial_t *C = Riva$Memory$alloc(sizeof(polynomial_t) + (Degree + 1) * sizeof(Std$Object_t *));
		C->Type = T;
		C->Degree.Type = Std$Integer$SmallT;
		for (int I = Degree; I >= 0; --I) {
			Std$Function_result Buffer;
			Std$Function$call($SUB, 2, &Buffer, A->Coefficients[I], 0, B->Coefficients[I], 0);
			C->Coefficients[I] = Buffer.Val;
		};
		while (Degree >= 0) {
			Std$Function_result Buffer;
			if (Std$Function$call($is0, 1, &Buffer, C->Coefficients[Degree], 0) >= FAILURE) break;
			--Degree;
		};
		C->Degree.Value = Degree;
		Result->Val = C;
		return SUCCESS;
	};
};

SYMBOL($MUL, "*");

METHOD("*", TYP, T, TYP, T) {
	polynomial_t *A = Args[0].Val;
	polynomial_t *B = Args[1].Val;
	if ((A->Degree.Value == -1) || (B->Degree.Value == -1)) {
		polynomial_t *C = Riva$Memory$alloc(sizeof(polynomial_t));
		C->Type = T;
		C->Degree.Type = Std$Integer$SmallT;
		C->Degree.Value = -1;
		Result->Val = C;
		return SUCCESS;
	};
	int Degree = A->Degree.Value + B->Degree.Value;
	polynomial_t *C = Riva$Memory$alloc(sizeof(polynomial_t) + (Degree + 1) * sizeof(Std$Object_t *));
	C->Type = T;
	C->Degree.Type = Std$Integer$SmallT;
	C->Degree.Value = Degree;
	Std$Object_t **AP = A->Coefficients;
	Std$Object_t *BC = B->Coefficients[0];
	Std$Object_t **CP = C->Coefficients;
	for (int I = A->Degree.Value; I >= 0; --I) {
		Std$Function_result Buffer;
		Std$Function$call($MUL, 2, &Buffer, *(AP++), 0, BC, 0);
		*(CP++) = Buffer.Val;
	};
	for (int I = 1; I <= B->Degree.Value; ++I) {
		AP = A->Coefficients;
		BC = B->Coefficients[I];
		CP = C->Coefficients + I;
		for (int J = A->Degree.Value; J > 0; --J) {
			Std$Function_result Buffer;
			Std$Function$call($MUL, 2, &Buffer, *(AP++), 0, BC, 0);
			Std$Function$call($ADD, 2, &Buffer, *CP, 0, Buffer.Val, 0);
			*(CP++) = Buffer.Val;
		};
		Std$Function_result Buffer;
		Std$Function$call($MUL, 2, &Buffer, *(AP++), 0, B->Coefficients[B->Degree.Value], 0);
		*CP = Buffer.Val;
	};
	Result->Val = C;
	return SUCCESS;
};

SYMBOL($DIV, "div");

METHOD("div", TYP, T, TYP, T) {
};

extern Std$Function_t Polynomial2$INIT[];

void __init (void *Module) {
	SpacePlusSpace = Std$String$new(" + ");
	ZeroStr = Std$String$new("0");
	XStr = Std$String$new("x");
	XPowStr = Std$String$new("x^");
	Std$Function_result Result;
	Std$Function$call(Polynomial2$INIT, 0, &Result);
};
