#include <Std.h>
#include <Riva/Memory.h>
#include <stdint.h>

typedef struct matrix_t {
	Std$Type_t *Type;
	Std$Integer_smallt NoOfRows, NoOfCols;
	Std$Object_t *Entries[];
} matrix_t;

TYPE(T);

GLOBAL_FUNCTION(New, 2) {
	uint32_t NoOfRows = ((Std$Integer_smallt *)Args[0].Val)->Value;
	uint32_t NoOfCols = ((Std$Integer_smallt *)Args[1].Val)->Value;
	if (NoOfRows * NoOfCols != Count - 2) {
		Result->Val = Std$String$new("Incorrect number of arguments to Matrix.New");
		return MESSAGE;
	};
	matrix_t *Matrix = Riva$Memory$alloc(sizeof(matrix_t) + NoOfCols * NoOfRows * sizeof(Std$Object_t **));
	Matrix->Type = T;
	Matrix->NoOfRows.Type = Matrix->NoOfCols.Type = Std$Integer$SmallT;
	Matrix->NoOfRows.Value = NoOfRows;
	Matrix->NoOfCols.Value = NoOfCols;
	Std$Function_argument *Arg = Args + 2;
	Std$Object_t **Ptr = Matrix->Entries;
	for (int I = 0; I < NoOfRows; ++I) {
		for (int J = 0; J < NoOfCols; ++J) {
			*(Ptr++) = (Arg++)->Val;
		};
	};
	Result->Val = Matrix;
	return SUCCESS;
};

METHOD("rows", TYP, T) {
	Result->Val = &((matrix_t *)Args[0].Val)->NoOfRows;
	return SUCCESS;
};

METHOD("cols", TYP, T) {
	Result->Val = &((matrix_t *)Args[0].Val)->NoOfCols;
	return SUCCESS;
};

static Std$Object_t *LeftBracket, *RightBracket, *CommaSpace, *LeftRightBracket, *ValueString;

SYMBOL($AT, "@");
SYMBOL($ADD, "+");
SYMBOL($SUB, "-");
SYMBOL($MUL, "*");
SYMBOL($DIV, "/");

METHOD("@", TYP, T, VAL, Std$String$T) {
	matrix_t *Matrix = Args[0].Val;
	Std$Object_t **Ptr = Matrix->Entries;

	Std$Function_result Buffer;
	Std$String_t *Final = Std$String$add(LeftBracket, LeftBracket);
	if (Std$Function$call($AT, 2, &Buffer, *(Ptr++), 0, Std$String$T, 0) < FAILURE) {
		Final = Std$String$add(Final, Buffer.Val);
	} else {
		Final = Std$String$add(Final, ValueString);
	};
	for (int J = 1; J < Matrix->NoOfCols.Value; ++J) {
		Final = Std$String$add(Final, CommaSpace);
		if (Std$Function$call($AT, 2, &Buffer, *(Ptr++), 0, Std$String$T, 0) < FAILURE) {
			Final = Std$String$add(Final, Buffer.Val);
		} else {
			Final = Std$String$add(Final, ValueString);
		};
	};
	Final = Std$String$add(Final, RightBracket);
	for (int I = 1; I < Matrix->NoOfRows.Value; ++I) {
		Final = Std$String$add(Final, CommaSpace);
		Final = Std$String$add(Final, LeftBracket);
		if (Std$Function$call($AT, 2, &Buffer, *(Ptr++), 0, Std$String$T, 0) < FAILURE) {
			Final = Std$String$add(Final, Buffer.Val);
		} else {
			Final = Std$String$add(Final, ValueString);
		};
		for (int J = 1; J < Matrix->NoOfCols.Value; ++J) {
			Final = Std$String$add(Final, CommaSpace);
			if (Std$Function$call($AT, 2, &Buffer, *(Ptr++), 0, Std$String$T, 0) < FAILURE) {
				Final = Std$String$add(Final, Buffer.Val);
			} else {
				Final = Std$String$add(Final, ValueString);
			};
		};
		Final = Std$String$add(Final, RightBracket);
	};
	Result->Val = Std$String$add(Final, RightBracket);
	return SUCCESS;
};

METHOD("+", TYP, T, TYP, T) {
	matrix_t *A = Args[0].Val;
	matrix_t *B = Args[1].Val;
	uint32_t NoOfRows = A->NoOfRows.Value;
	if (NoOfRows != B->NoOfRows.Value) {
		Result->Val = Std$String$new("Matrices not of equal dimension");
		return MESSAGE;
	};
	uint32_t NoOfCols = A->NoOfCols.Value;
	if (NoOfCols != B->NoOfRows.Value) {
		Result->Val = Std$String$new("Matrices not of equal dimension");
		return MESSAGE;
	};
	matrix_t *C = Riva$Memory$alloc(sizeof(matrix_t) + NoOfCols * NoOfRows * sizeof(Std$Object_t **));
	C->Type = T;
	C->NoOfRows.Type = C->NoOfCols.Type = Std$Integer$SmallT;
	C->NoOfRows.Value = NoOfRows;
	C->NoOfCols.Value = NoOfCols;
	Std$Object_t **AP = A->Entries;
	Std$Object_t **BP = B->Entries;
	Std$Object_t **CP = C->Entries;
	for (int I = NoOfRows * NoOfCols; --I >= 0;) {
		Std$Function_result Buffer;
		switch (Std$Function$call($ADD, 2, &Buffer, *(AP++), 0, *(BP++), 0)) {
		case SUSPEND: case SUCCESS:
			*(CP++) = Buffer.Val;
			break;
		case FAILURE:
			Result->Val = Std$String$new(":\"+\" failed to return a result");
			return MESSAGE;
		case MESSAGE:
			Result->Val = Buffer.Val;
			return MESSAGE;
		};
	};
	Result->Val = C;
	return SUCCESS;
};

METHOD("-", TYP, T, TYP, T) {
	matrix_t *A = Args[0].Val;
	matrix_t *B = Args[1].Val;
	uint32_t NoOfRows = A->NoOfRows.Value;
	if (NoOfRows != B->NoOfRows.Value) {
		Result->Val = Std$String$new("Matrices not of equal dimension");
		return MESSAGE;
	};
	uint32_t NoOfCols = A->NoOfCols.Value;
	if (NoOfCols != B->NoOfRows.Value) {
		Result->Val = Std$String$new("Matrices not of equal dimension");
		return MESSAGE;
	};
	matrix_t *C = Riva$Memory$alloc(sizeof(matrix_t) + NoOfCols * NoOfRows * sizeof(Std$Object_t **));
	C->Type = T;
	C->NoOfRows.Type = C->NoOfCols.Type = Std$Integer$SmallT;
	C->NoOfRows.Value = NoOfRows;
	C->NoOfCols.Value = NoOfCols;
	Std$Object_t **AP = A->Entries;
	Std$Object_t **BP = B->Entries;
	Std$Object_t **CP = C->Entries;
	for (int I = NoOfRows * NoOfCols; --I >= 0;) {
		Std$Function_result Buffer;
		switch (Std$Function$call($SUB, 2, &Buffer, *(AP++), 0, *(BP++), 0)) {
		case SUSPEND: case SUCCESS:
			*(CP++) = Buffer.Val;
			break;
		case FAILURE:
			Result->Val = Std$String$new(":\"-\" failed to return a result");
			return MESSAGE;
		case MESSAGE:
			Result->Val = Buffer.Val;
			return MESSAGE;
		};
	};
	Result->Val = C;
	return SUCCESS;
};

METHOD("*", TYP, T, TYP, T) {
	matrix_t *A = Args[0].Val;
	matrix_t *B = Args[1].Val;
	uint32_t NoOfRows = A->NoOfRows.Value;
	uint32_t NoOfCols = B->NoOfCols.Value;
	uint32_t Temp = A->NoOfCols.Value;
	if (Temp != B->NoOfRows.Value) {
		Result->Val = Std$String$new("Matrices not of compatible dimension");
		return MESSAGE;
	};
	matrix_t *C = Riva$Memory$alloc(sizeof(matrix_t) + NoOfCols * NoOfRows * sizeof(Std$Object_t **));
	C->Type = T;
	C->NoOfRows.Type = C->NoOfCols.Type = Std$Integer$SmallT;
	C->NoOfRows.Value = NoOfRows;
	C->NoOfCols.Value = NoOfCols;
	for (int I = 0; I < NoOfRows; ++I) {
		for (int J = 0; J < NoOfCols; ++J) {
			Std$Function_result Buffer;
			Std$Object_t **AP = A->Entries + I * Temp;
			Std$Object_t **BP = B->Entries + J;
			Std$Function$call($MUL, 2, &Buffer, *(AP), 0, *(BP), 0);
			Std$Object_t *Value = Buffer.Val;
			for (int K = Temp; --K;) {
				Std$Function$call($MUL, 2, &Buffer, *(++AP), 0, *(BP += NoOfCols), 0);
				Std$Function$call($ADD, 2, &Buffer, Value, 0, Buffer.Val, 0);
				Value = Buffer.Val;
			};
			C->Entries[I * NoOfCols + J] = Value;
		};
	};
	Result->Val = C;
	return SUCCESS;
};

static Std$Object_t *determinant2(matrix_t *M, int N, int *Rows, int *Cols) {
	Std$Object_t **Row = M->Entries + Rows[0] * M->NoOfCols.Value;
	++Rows;
	if (--N == 0) return Row[Cols[0]];
	int Cols2[N];
	for (int I = 0; I < N; ++I) Cols2[I] = Cols[I + 1];
	Std$Function_result Buffer;
	Std$Function$call($MUL, 2, &Buffer, Row[Cols[0]], 0, determinant2(M, N, Rows, Cols2), 0);
	Std$Object_t *Det = Buffer.Val;
	for (int I = 0; I < N; ++I) {
		Cols2[I] = Cols[I];
		Std$Function$call($MUL, 2, &Buffer, Row[Cols[I + 1]], 0, determinant2(M, N, Rows, Cols2), 0);
		Std$Function$call(I % 2 ? $ADD : $SUB, 2, &Buffer, Det, 0, Buffer.Val);
		Det = Buffer.Val;
	};
	return Det;
};

inline matrix_t *inverse(matrix_t *M) {
	int N = M->NoOfRows.Value;
	if (N != M->NoOfCols.Value) return 0;
	matrix_t *C = Riva$Memory$alloc(sizeof(matrix_t) + N * N * sizeof(Std$Object_t **));
	C->Type = T;
	C->NoOfRows.Type = C->NoOfCols.Type = Std$Integer$SmallT;
	C->NoOfRows.Value = N;
	C->NoOfCols.Value = N;

	int Rows[N], Cols[N];
	for (int I = 0; I < N; ++I) Rows[I] = Cols[I] = I;
	Std$Object_t *Det = determinant2(M, N, Rows, Cols);
	for (int I = 1; I < N; ++I) Rows[I - 1] = I;

	for (int I = 0; I < N; ++I) {
		for (int J = 1; J < N; ++J) Cols[J - 1] = J;
		for (int J = 0; J < N; ++J) {
			Std$Function_result Buffer;
			if ((I + J) % 2) {
				Std$Function$call($SUB, 1, &Buffer, determinant2(M, N - 1, Rows, Cols), 0);
				Std$Function$call($DIV, 2, &Buffer, Buffer.Val, 0, Det, 0);
			} else {
				Std$Function$call($DIV, 2, &Buffer, determinant2(M, N - 1, Rows, Cols), 0, Det, 0);
			};
			C->Entries[I + J * N] = Buffer.Val;
			Cols[J] = J;
		};
		Rows[I] = I;
	};
	return C;
};

METHOD("/", TYP, T, TYP, T) {
	matrix_t *A = Args[0].Val;
	matrix_t *B = inverse(Args[1].Val);
	uint32_t NoOfRows = A->NoOfRows.Value;
	uint32_t NoOfCols = B->NoOfCols.Value;
	uint32_t Temp = A->NoOfCols.Value;
	if (Temp != B->NoOfRows.Value) {
		Result->Val = Std$String$new("Matrices not of compatible dimension");
		return MESSAGE;
	};
	matrix_t *C = Riva$Memory$alloc(sizeof(matrix_t) + NoOfCols * NoOfRows * sizeof(Std$Object_t **));
	C->Type = T;
	C->NoOfRows.Type = C->NoOfCols.Type = Std$Integer$SmallT;
	C->NoOfRows.Value = NoOfRows;
	C->NoOfCols.Value = NoOfCols;
	for (int I = 0; I < NoOfRows; ++I) {
		for (int J = 0; J < NoOfCols; ++J) {
			Std$Function_result Buffer;
			Std$Object_t **AP = A->Entries + I * Temp;
			Std$Object_t **BP = B->Entries + J;
			Std$Function$call($MUL, 2, &Buffer, *(AP), 0, *(BP), 0);
			Std$Object_t *Value = Buffer.Val;
			for (int K = Temp; --K;) {
				Std$Function$call($MUL, 2, &Buffer, *(++AP), 0, *(BP += NoOfCols), 0);
				Std$Function$call($ADD, 2, &Buffer, Value, 0, Buffer.Val, 0);
				Value = Buffer.Val;
			};
			C->Entries[I * NoOfCols + J] = Value;
		};
	};
	Result->Val = C;
	return SUCCESS;
};

METHOD("det", TYP, T) {
	matrix_t *M = Args[0].Val;
	int N = M->NoOfRows.Value;
	if (N != M->NoOfCols.Value) {
		Result->Val = Std$String$new("Matrix must be square for :det");
		return MESSAGE;
	};
	int Rows[N], Cols[N];
	for (int I = 0; I < N; ++I) Rows[I] = Cols[I] = I;
	Result->Val = determinant2(M, N, Rows, Cols);
	return SUCCESS;
};

METHOD("adj", TYP, T) {
	matrix_t *M = Args[0].Val;
	int N = M->NoOfRows.Value;
	if (N != M->NoOfCols.Value) {
		Result->Val = Std$String$new("Matrix must be square for :adj");
		return MESSAGE;
	};
	matrix_t *C = Riva$Memory$alloc(sizeof(matrix_t) + N * N * sizeof(Std$Object_t **));
	C->Type = T;
	C->NoOfRows.Type = C->NoOfCols.Type = Std$Integer$SmallT;
	C->NoOfRows.Value = N;
	C->NoOfCols.Value = N;

	int Rows[N];
	for (int I = 1; I < N; ++I) Rows[I - 1] = I;

	for (int I = 0; I < N; ++I) {
		int Cols[N];
		for (int J = 1; J < N; ++J) Cols[J - 1] = J;
		for (int J = 0; J < N; ++J) {
			if ((I + J) % 2) {
				Std$Function_result Buffer;
				Std$Function$call($SUB, 1, &Buffer, determinant2(M, N - 1, Rows, Cols), 0);
				C->Entries[I + J * N] = Buffer.Val;
			} else {
				C->Entries[I + J * N] = determinant2(M, N - 1, Rows, Cols);
			};
			Cols[J] = J;
		};
		Rows[I] = I;
	};

	Result->Val = C;
	return SUCCESS;
};

METHOD("inv", TYP, T) {
	matrix_t *M = Args[0].Val;
	int N = M->NoOfRows.Value;
	if (N != M->NoOfCols.Value) {
		Result->Val = Std$String$new("Matrix must be square for :inv");
		return MESSAGE;
	};
	matrix_t *C = Riva$Memory$alloc(sizeof(matrix_t) + N * N * sizeof(Std$Object_t **));
	C->Type = T;
	C->NoOfRows.Type = C->NoOfCols.Type = Std$Integer$SmallT;
	C->NoOfRows.Value = N;
	C->NoOfCols.Value = N;

	int Rows[N], Cols[N];
	for (int I = 0; I < N; ++I) Rows[I] = Cols[I] = I;
	Std$Object_t *Det = determinant2(M, N, Rows, Cols);
	for (int I = 1; I < N; ++I) Rows[I - 1] = I;

	for (int I = 0; I < N; ++I) {
		for (int J = 1; J < N; ++J) Cols[J - 1] = J;
		for (int J = 0; J < N; ++J) {
			Std$Function_result Buffer;
			if ((I + J) % 2) {
				Std$Function$call($SUB, 1, &Buffer, determinant2(M, N - 1, Rows, Cols), 0);
				Std$Function$call($DIV, 2, &Buffer, Buffer.Val, 0, Det, 0);
			} else {
				Std$Function$call($DIV, 2, &Buffer, determinant2(M, N - 1, Rows, Cols), 0, Det, 0);
			};
			C->Entries[I + J * N] = Buffer.Val;
			Cols[J] = J;
		};
		Rows[I] = I;
	};

	Result->Val = C;
	return SUCCESS;
};

METHOD("+", TYP, T, ANY) {
	matrix_t *A = Args[0].Val;
	Std$Object_t *B = Args[1].Val;
	uint32_t NoOfRows = A->NoOfRows.Value;
	uint32_t NoOfCols = A->NoOfCols.Value;
	matrix_t *C = Riva$Memory$alloc(sizeof(matrix_t) + NoOfCols * NoOfRows * sizeof(Std$Object_t **));
	C->Type = T;
	C->NoOfRows.Type = C->NoOfCols.Type = Std$Integer$SmallT;
	C->NoOfRows.Value = NoOfRows;
	C->NoOfCols.Value = NoOfCols;
	memcpy(C->Entries, A->Entries, NoOfRows * NoOfCols * sizeof(Std$Object_t **));
	Std$Object_t **Ptr = C->Entries;
	for (int I = (NoOfRows < NoOfCols ? NoOfRows : NoOfCols); --I >= 0;) {
		Std$Function_result Buffer;
		Std$Function$call($ADD, 2, &Buffer, Ptr[0], 0, B, 0);
		Ptr[0] = Buffer.Val;
		Ptr += NoOfCols + 1;
	};
	Result->Val = C;
	return SUCCESS;
};

METHOD("-", TYP, T, ANY) {
	matrix_t *A = Args[0].Val;
	Std$Object_t *B = Args[1].Val;
	uint32_t NoOfRows = A->NoOfRows.Value;
	uint32_t NoOfCols = A->NoOfCols.Value;
	matrix_t *C = Riva$Memory$alloc(sizeof(matrix_t) + NoOfCols * NoOfRows * sizeof(Std$Object_t **));
	C->Type = T;
	C->NoOfRows.Type = C->NoOfCols.Type = Std$Integer$SmallT;
	C->NoOfRows.Value = NoOfRows;
	C->NoOfCols.Value = NoOfCols;
	memcpy(C->Entries, A->Entries, NoOfRows * NoOfCols * sizeof(Std$Object_t **));
	Std$Object_t **Ptr = C->Entries;
	for (int I = (NoOfRows < NoOfCols ? NoOfRows : NoOfCols); --I >= 0;) {
		Std$Function_result Buffer;
		Std$Function$call($SUB, 2, &Buffer, Ptr[0], 0, B, 0);
		Ptr[0] = Buffer.Val;
		Ptr += NoOfCols + 1;
	};
	Result->Val = C;
	return SUCCESS;
};

METHOD("+", ANY, TYP, T) {
	matrix_t *A = Args[1].Val;
	Std$Object_t *B = Args[0].Val;
	uint32_t NoOfRows = A->NoOfRows.Value;
	uint32_t NoOfCols = A->NoOfCols.Value;
	matrix_t *C = Riva$Memory$alloc(sizeof(matrix_t) + NoOfCols * NoOfRows * sizeof(Std$Object_t **));
	C->Type = T;
	C->NoOfRows.Type = C->NoOfCols.Type = Std$Integer$SmallT;
	C->NoOfRows.Value = NoOfRows;
	C->NoOfCols.Value = NoOfCols;
	memcpy(C->Entries, A->Entries, NoOfRows * NoOfCols * sizeof(Std$Object_t **));
	Std$Object_t **Ptr = C->Entries;
	for (int I = (NoOfRows < NoOfCols ? NoOfRows : NoOfCols); --I >= 0;) {
		Std$Function_result Buffer;
		Std$Function$call($ADD, 2, &Buffer, B, 0, Ptr[0], 0);
		Ptr[0] = Buffer.Val;
		Ptr += NoOfCols + 1;
	};
	Result->Val = C;
	return SUCCESS;
};

METHOD("-", ANY, TYP, T) {
	matrix_t *A = Args[1].Val;
	Std$Object_t *B = Args[0].Val;
	uint32_t NoOfRows = A->NoOfRows.Value;
	uint32_t NoOfCols = A->NoOfCols.Value;
	matrix_t *C = Riva$Memory$alloc(sizeof(matrix_t) + NoOfCols * NoOfRows * sizeof(Std$Object_t **));
	C->Type = T;
	C->NoOfRows.Type = C->NoOfCols.Type = Std$Integer$SmallT;
	C->NoOfRows.Value = NoOfRows;
	C->NoOfCols.Value = NoOfCols;
	memcpy(C->Entries, A->Entries, NoOfRows * NoOfCols * sizeof(Std$Object_t **));
	Std$Object_t **Ptr = C->Entries;
	for (int I = (NoOfRows < NoOfCols ? NoOfRows : NoOfCols); --I >= 0;) {
		Std$Function_result Buffer;
		Std$Function$call($SUB, 2, &Buffer, B, 0, Ptr[0], 0);
		Ptr[0] = Buffer.Val;
		Ptr += NoOfCols + 1;
	};
	Result->Val = C;
	return SUCCESS;
};

METHOD("*", TYP, T, ANY) {
	matrix_t *A = Args[0].Val;
	Std$Object_t *B = Args[1].Val;
	uint32_t NoOfRows = A->NoOfRows.Value;
	uint32_t NoOfCols = A->NoOfCols.Value;
	matrix_t *C = Riva$Memory$alloc(sizeof(matrix_t) + NoOfCols * NoOfRows * sizeof(Std$Object_t **));
	C->Type = T;
	C->NoOfRows.Type = C->NoOfCols.Type = Std$Integer$SmallT;
	C->NoOfRows.Value = NoOfRows;
	C->NoOfCols.Value = NoOfCols;
	Std$Object_t **AP = A->Entries;
	Std$Object_t **CP = C->Entries;
	for (int I = NoOfRows * NoOfCols; --I >= 0;) {
		Std$Function_result Buffer;
		Std$Function$call($MUL, 2, &Buffer, *(AP++), 0, B, 0);
		*(CP++) = Buffer.Val;
	};
	Result->Val = C;
	return SUCCESS;
};

METHOD("*", ANY, TYP, T) {
	matrix_t *A = Args[1].Val;
	Std$Object_t *B = Args[0].Val;
	uint32_t NoOfRows = A->NoOfRows.Value;
	uint32_t NoOfCols = A->NoOfCols.Value;
	matrix_t *C = Riva$Memory$alloc(sizeof(matrix_t) + NoOfCols * NoOfRows * sizeof(Std$Object_t **));
	C->Type = T;
	C->NoOfRows.Type = C->NoOfCols.Type = Std$Integer$SmallT;
	C->NoOfRows.Value = NoOfRows;
	C->NoOfCols.Value = NoOfCols;
	Std$Object_t **AP = A->Entries;
	Std$Object_t **CP = C->Entries;
	for (int I = NoOfRows * NoOfCols; --I >= 0;) {
		Std$Function_result Buffer;
		Std$Function$call($MUL, 2, &Buffer, B, 0, *(AP++), 0);
		*(CP++) = Buffer.Val;
	};
	Result->Val = C;
	return SUCCESS;
};

METHOD("/", TYP, T, ANY) {
	matrix_t *A = Args[0].Val;
	Std$Object_t *B = Args[1].Val;
	uint32_t NoOfRows = A->NoOfRows.Value;
	uint32_t NoOfCols = A->NoOfCols.Value;
	matrix_t *C = Riva$Memory$alloc(sizeof(matrix_t) + NoOfCols * NoOfRows * sizeof(Std$Object_t **));
	C->Type = T;
	C->NoOfRows.Type = C->NoOfCols.Type = Std$Integer$SmallT;
	C->NoOfRows.Value = NoOfRows;
	C->NoOfCols.Value = NoOfCols;
	Std$Object_t **AP = A->Entries;
	Std$Object_t **CP = C->Entries;
	for (int I = NoOfRows * NoOfCols; --I >= 0;) {
		Std$Function_result Buffer;
		Std$Function$call($DIV, 2, &Buffer, *(AP++), 0, B, 0);
		*(CP++) = Buffer.Val;
	};
	Result->Val = C;
	return SUCCESS;
};

METHOD("/", ANY, TYP, T) {
	matrix_t *A = inverse(Args[1].Val);
	Std$Object_t *B = Args[0].Val;
	uint32_t NoOfRows = A->NoOfRows.Value;
	uint32_t NoOfCols = A->NoOfCols.Value;
	matrix_t *C = Riva$Memory$alloc(sizeof(matrix_t) + NoOfCols * NoOfRows * sizeof(Std$Object_t **));
	C->Type = T;
	C->NoOfRows.Type = C->NoOfCols.Type = Std$Integer$SmallT;
	C->NoOfRows.Value = NoOfRows;
	C->NoOfCols.Value = NoOfCols;
	Std$Object_t **AP = A->Entries;
	Std$Object_t **CP = C->Entries;
	for (int I = NoOfRows * NoOfCols; --I >= 0;) {
		Std$Function_result Buffer;
		Std$Function$call($MUL, 2, &Buffer, *(AP++), 0, B, 0);
		*(CP++) = Buffer.Val;
	};
	Result->Val = C;
	return SUCCESS;
};

SYMBOL($is0, "is0");

METHOD("is0", TYP, T) {
	matrix_t *A = Args[0].Val;
	Std$Object_t **AP = A->Entries;
	for (int I = A->NoOfRows.Value * A->NoOfCols.Value; --I >= 0;) {
		Std$Function_result Buffer;
		switch (Std$Function$call($is0, 1, &Buffer, *(AP++), 0)) {
		case FAILURE: return FAILURE;
		case MESSAGE: Result->Val = Buffer.Val; return MESSAGE;
		default: break;
		};
	};
	Result->Val = A;
	return SUCCESS;
};

void __init (void *Module) {
	LeftBracket = Std$String$new("[");
	RightBracket = Std$String$new("]");
	CommaSpace = Std$String$new(", ");
	LeftRightBracket = Std$String$new("[]");
	ValueString = Std$String$new("<value>");
};
