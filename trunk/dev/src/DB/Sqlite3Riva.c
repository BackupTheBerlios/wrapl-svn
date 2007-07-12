#include <Riva.h>
#include <Std.h>

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

void __init(void) {
};
