#include <Riva.h>
#include <Std.h>

#include <ucontext.h>
#include <stdint.h>
#include "Sqlite3.h"

TYPE(T);

typedef struct database_t {
	Std$Type_t *Type;
	sqlite3 *Handle;
} database_t;

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

int sqlite3_exec(
  sqlite3*,                                  /* An open database */
  const char *sql,                           /* SQL to be evaluted */
  int (*callback)(void*,int,char**,char**),  /* Callback function */
  void *,                                    /* 1st argument to callback */
  char **errmsg                              /* Error msg written here */
);

typedef struct exec_generator {
	Std$Function_cstate State;
	ucontext_t Context0[1];
	ucontext_t Context1[1];
	int Status;
	Std$Function_result *Result;
	uint8_t Stack[4000];
} exec_generator;

typedef struct exec_resume_data {
	exec_generator *Generator;
	Std$Function_argument Result;
} exec_resume_data;

static exec_callback(exec_generator *Gen, int Count, char **Values, char **Names) {
	Gen->Status = SUSPEND;
	Gen->Result->State = Gen;
	Std$Object_t *Table = Std$Table$new(0, 0);
	for (int I = 0; I < Count; ++I) Std$Table$insert(Table, Std$String$new(Names[I]), Std$String$new(Values[I]));
	Gen->Result->Val = Table;
	swapcontext(Gen->Context0, Gen->Context1);
};

static long resume_exec(exec_resume_data *Data) {
	exec_generator *Gen = Data->Generator;
	Gen->Result = &Data->Result;
	swapcontext(Gen->Context1, Gen->Context0);
	return Gen->Status;
};

static void exec_start(sqlite3 *Handle, exec_generator *Gen, const char *Statement) {
	sqlite3_exec(Handle, Statement, exec_callback, Gen, 0);
	Gen->Status = FAILURE;
	setcontext(Gen->Context1);
};

METHOD("exec", TYP, T, TYP, Std$String$T) {
	exec_generator *Gen = new(exec_generator);
	getcontext(Gen->Context0);
	Gen->Context0->uc_stack.ss_sp = Gen->Stack;
	Gen->Context0->uc_stack.ss_size = 4000;	
	makecontext(Gen->Context0, exec_start, 3, ((database_t *)Args[0].Val)->Handle, Gen, Std$String$flatten(Args[1].Val));
	Gen->Result = Result;
	Gen->State.Run = Std$Function$resume_c;
	Gen->State.Invoke = resume_exec;
	swapcontext(Gen->Context1, Gen->Context0);
	return Gen->Status;
};
