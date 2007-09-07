#include <Riva.h>
#include <Std.h>

#include <ucontext.h>
#include <stdint.h>
#include "Sqlite3.h"

Std$Integer_smallt OK[] = {{Std$Integer$SmallT, SQLITE_OK}};
Std$Integer_smallt ERROR[] = {{Std$Integer$SmallT, SQLITE_ERROR}};
Std$Integer_smallt INTERNAL[] = {{Std$Integer$SmallT, SQLITE_INTERNAL}};
Std$Integer_smallt PERM[] = {{Std$Integer$SmallT, SQLITE_PERM}};
Std$Integer_smallt ABORT[] = {{Std$Integer$SmallT, SQLITE_ABORT}};
Std$Integer_smallt BUSY[] = {{Std$Integer$SmallT, SQLITE_BUSY}};
Std$Integer_smallt LOCKED[] = {{Std$Integer$SmallT, SQLITE_LOCKED}};
Std$Integer_smallt NOMEM[] = {{Std$Integer$SmallT, SQLITE_NOMEM}};
Std$Integer_smallt READONLY[] = {{Std$Integer$SmallT, SQLITE_READONLY}};
Std$Integer_smallt INTERRUPT[] = {{Std$Integer$SmallT, SQLITE_INTERRUPT}};
Std$Integer_smallt IOERR[] = {{Std$Integer$SmallT, SQLITE_IOERR}};
Std$Integer_smallt CORRUPT[] = {{Std$Integer$SmallT, SQLITE_CORRUPT}};
Std$Integer_smallt NOT_FOUND[] = {{Std$Integer$SmallT, SQLITE_NOTFOUND}};
Std$Integer_smallt FULL[] = {{Std$Integer$SmallT, SQLITE_FULL}};
Std$Integer_smallt CANTOPEN[] = {{Std$Integer$SmallT, SQLITE_CANTOPEN}};
Std$Integer_smallt PROTOCOL[] = {{Std$Integer$SmallT, SQLITE_PROTOCOL}};
Std$Integer_smallt EMPTY[] = {{Std$Integer$SmallT, SQLITE_EMPTY}};
Std$Integer_smallt SCHEME[] = {{Std$Integer$SmallT, SQLITE_SCHEMA}};
Std$Integer_smallt TOOBIG[] = {{Std$Integer$SmallT, SQLITE_TOOBIG}};
Std$Integer_smallt CONSTRAINT[] = {{Std$Integer$SmallT, SQLITE_CONSTRAINT}};
Std$Integer_smallt MISMATCH[] = {{Std$Integer$SmallT, SQLITE_MISMATCH}};
Std$Integer_smallt MISUSE[] = {{Std$Integer$SmallT, SQLITE_MISUSE}};
Std$Integer_smallt NOLFS[] = {{Std$Integer$SmallT, SQLITE_NOLFS}};
Std$Integer_smallt AUTH[] = {{Std$Integer$SmallT, SQLITE_AUTH}};
Std$Integer_smallt FORMAT[] = {{Std$Integer$SmallT, SQLITE_FORMAT}};
Std$Integer_smallt RANGE[] = {{Std$Integer$SmallT, SQLITE_RANGE}};
Std$Integer_smallt NOTADB[] = {{Std$Integer$SmallT, SQLITE_NOTADB}};
Std$Integer_smallt ROW[] = {{Std$Integer$SmallT, SQLITE_ROW}};
Std$Integer_smallt DONE[] = {{Std$Integer$SmallT, SQLITE_DONE}};

TYPE(T);
TYPE(StatementT);

typedef struct database_t {
	Std$Type_t *Type;
	sqlite3 *Handle;
} database_t;

typedef struct statement_t {
	Std$Type_t *Type;
	sqlite3_stmt *Handle;
} statement_t;

METHOD("errmsg", TYP, T) {
	database_t *DB = Args[0].Val;
	Result->Val = Std$String$copy(sqlite3_errmsg(DB->Handle));
	return SUCCESS;
};

METHOD("close", TYP, T) {
	database_t *DB = Args[0].Val;
	return (sqlite3_close(DB->Handle) == SQLITE_BUSY) ? FAILURE : SUCCESS;
};

METHOD("interrupt", TYP, T) {
	database_t *DB = Args[0].Val;
	return SUCCESS;
};

GLOBAL_FUNCTION(Open, 1) {
	sqlite3 *Handle;
	if (sqlite3_open(Std$String$flatten(Args[0].Val), &Handle) == SQLITE_OK) {
		database_t *DB = new(database_t);
		DB->Type = T;
		DB->Handle = Handle;
		Result->Val = DB;
		return SUCCESS;
	} else {
		Result->Val = Std$String$new(sqlite3_errmsg(Handle));
		sqlite3_close(Handle);
		return MESSAGE;
	};
};

METHOD("prepare", TYP, T, TYP, Std$String$T) {
	database_t *DB = Args[0].Val;
	Std$String_t *Str = Args[1].Val;
	sqlite3_stmt *Handle;
	const char *Tail;
	if (sqlite3_prepare_v2(DB->Handle, Std$String$flatten(Str), Str->Length.Value, &Handle, &Tail) == SQLITE_OK) {
		statement_t *S = new(statement_t);
		S->Type = StatementT;
		S->Handle = Handle;
		Result->Val = S;
		return SUCCESS;
	} else {
		Result->Val = Std$String$new("Error: Sqlite statement prepare failed");
		return MESSAGE;
	};
};

METHOD("finalize", TYP, StatementT) {
	statement_t *S = Args[0].Val;
	sqlite3_finalize(S->Handle);
	return SUCCESS;
};

METHOD("reset", TYP, StatementT) {
	statement_t *S = Args[0].Val;
	sqlite3_reset(S->Handle);
	return SUCCESS;
};

METHOD("bind", TYP, StatementT, TYP, Std$Integer$SmallT, TYP, Std$Address$T, TYP, Std$Integer$SmallT) {
	statement_t *S = Args[0].Val;
	sqlite3_bind_blob(S->Handle,
		((Std$Integer_smallt *)Args[1].Val)->Value,
		((Std$Address_t *)Args[2].Val)->Value,
		((Std$Integer_smallt *)Args[3].Val)->Value,
		SQLITE_STATIC
	);
	return SUCCESS;
};

METHOD("bind", TYP, StatementT, TYP, Std$Integer$SmallT, TYP, Std$Real$T) {
	statement_t *S = Args[0].Val;
	sqlite3_bind_double(S->Handle,
		((Std$Integer_smallt *)Args[1].Val)->Value,
		((Std$Real_t *)Args[2].Val)->Value
	);
	return SUCCESS;
};

METHOD("bind", TYP, StatementT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	statement_t *S = Args[0].Val;
	sqlite3_bind_int(S->Handle,
		((Std$Integer_smallt *)Args[1].Val)->Value,
		((Std$Integer_smallt *)Args[2].Val)->Value
	);
	return SUCCESS;
};

METHOD("bind", TYP, StatementT, TYP, Std$Integer$SmallT, VAL, Std$Object$Nil) {
	statement_t *S = Args[0].Val;
	sqlite3_bind_null(S->Handle,
		((Std$Integer_smallt *)Args[1].Val)->Value
	);
	return SUCCESS;
};

METHOD("bind", TYP, StatementT, TYP, Std$Integer$SmallT, TYP, Std$String$T) {
	statement_t *S = Args[0].Val;
	sqlite3_bind_blob(S->Handle,
		((Std$Integer_smallt *)Args[1].Val)->Value,
		Std$String$flatten(Args[2].Val),
		((Std$String_t *)Args[2].Val)->Length.Value,
		SQLITE_STATIC
	);
	return SUCCESS;
};

METHOD("step", TYP, StatementT) {
	statement_t *S = Args[0].Val;
	Result->Val = Std$Integer$new_small(sqlite3_step(S->Handle));
	return SUCCESS;
};

METHOD("column_blob", TYP, StatementT, TYP, Std$Integer$SmallT) {
	statement_t *S = Args[0].Val;
	Result->Val = Std$Address$new(sqlite3_column_blob(S->Handle, ((Std$Integer_smallt *)Args[1].Val)->Value));
	return SUCCESS;
};

METHOD("column_bytes", TYP, StatementT, TYP, Std$Integer$SmallT) {
	statement_t *S = Args[0].Val;
	Result->Val = Std$Integer$new_small(sqlite3_column_bytes(S->Handle, ((Std$Integer_smallt *)Args[1].Val)->Value));
	return SUCCESS;
};

METHOD("column_count", TYP, StatementT) {
	statement_t *S = Args[0].Val;
	Result->Val = Std$Integer$new_small(sqlite3_column_count(S->Handle));
	return SUCCESS;
};

METHOD("column_double", TYP, StatementT, TYP, Std$Integer$SmallT) {
	statement_t *S = Args[0].Val;
	Result->Val = Std$Real$new(sqlite3_column_double(S->Handle, ((Std$Integer_smallt *)Args[1].Val)->Value));
	return SUCCESS;
};

METHOD("column_int", TYP, StatementT, TYP, Std$Integer$SmallT) {
	statement_t *S = Args[0].Val;
	Result->Val = Std$Integer$new_small(sqlite3_column_int(S->Handle, ((Std$Integer_smallt *)Args[1].Val)->Value));
	return SUCCESS;
};

METHOD("column_name", TYP, StatementT, TYP, Std$Integer$SmallT) {
	statement_t *S = Args[0].Val;
	Result->Val = Std$String$new(sqlite3_column_name(S->Handle, ((Std$Integer_smallt *)Args[1].Val)->Value));
	return SUCCESS;
};

METHOD("column_text", TYP, StatementT, TYP, Std$Integer$SmallT) {
	statement_t *S = Args[0].Val;
	const char *Text = sqlite3_column_text(S->Handle, ((Std$Integer_smallt *)Args[1].Val)->Value);
	int Length = sqlite3_column_bytes(S->Handle, ((Std$Integer_smallt *)Args[1].Val)->Value);
	Result->Val = Std$String$copy_length(Text, Length);
	return SUCCESS;
};

METHOD("column_type", TYP, StatementT, TYP, Std$Integer$SmallT) {
	statement_t *S = Args[0].Val;
	Result->Val = Std$Integer$new_small(sqlite3_column_type(S->Handle, ((Std$Integer_smallt *)Args[1].Val)->Value));
	return SUCCESS;
};
