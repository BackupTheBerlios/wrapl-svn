#include <Riva.h>
#include <Std.h>

#include <mysql/mysql.h>

TYPE(T);
TYPE(StatementT);

typedef struct connection_t {
	Std$Type_t *Type;
	MYSQL Handle;
} connection_t;

GLOBAL_FUNCTION(Open, 4) {
	connection_t *Connection = new(connection_t);
	mysql_init(&Connection->Handle);
	int Port = 0;
	const char *Socket = 0;
	if (Count > 4) {
		if (Args[4].Val->Type == Std$String$T) {
			Socket = Std$String$flatten(Args[3].Val);
		} else if (Args[4].Val->Type == Std$Integer$SmallT) {
			Port = ((Std$Integer_smallt *)Args[3].Val)->Value;
		};
	};
	if (mysql_real_connect(&Connection->Handle,
		Std$String$flatten(Args[0].Val),
		Std$String$flatten(Args[1].Val),
		Std$String$flatten(Args[2].Val),
		Std$String$flatten(Args[3].Val),
		Port,
		Socket,
		0
	) == 0) {
		Result->Val = Std$String$new(mysql_error(&Connection->Handle));
		return MESSAGE;
	};
	Result->Val = Connection;
	return SUCCESS;
};

void __init(Riva$Module_t *Module) {
	mysql_library_init(0, 0, 0);
};
