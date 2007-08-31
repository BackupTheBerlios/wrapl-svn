#include <Riva.h>
#include <Std.h>

#include <mysql/mysql.h>

TYPE(T);
TYPE(StatementT);
TYPE(ResultT);

typedef struct connection_t {
	Std$Type_t *Type;
	MYSQL Handle;
} connection_t;

typedef struct result_t {
	Std$Type_t *Type;
	MYSQL_RES *Handle;
	int FieldCount;
	MYSQL_FIELD *Fields;
	Std$Object_t *FieldList;
} result_t;

GLOBAL_FUNCTION(Open, 4) {
	connection_t *Connection = new(connection_t);
	Connection->Type = T;
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

METHOD("close", TYP, T) {
	MYSQL *Handle = &((connection_t *)Args[0].Val)->Handle;
	mysql_close(Handle);
	return SUCCESS;
};

METHOD("commit", TYP, T) {
	MYSQL *Handle = &((connection_t *)Args[0].Val)->Handle;
	if (mysql_commit(Handle)) {
		Result->Val = Std$String$new(mysql_error(Handle));
		return MESSAGE;
	};
	return SUCCESS;
};

METHOD("query", TYP, T, TYP, Std$String$T) {
	MYSQL *Handle = &((connection_t *)Args[0].Val)->Handle;
	if (mysql_real_query(Handle, Std$String$flatten(Args[1].Val), ((Std$String_t *)Args[1].Val)->Length.Value)) {
		Result->Val = Std$String$new(mysql_error(Handle));
		return MESSAGE;
	};
	return SUCCESS;
};

METHOD("use_result", TYP, T) {
	MYSQL *Handle = &((connection_t *)Args[0].Val)->Handle;
	MYSQL_RES *ResultHandle = mysql_use_result(Handle);
	if (ResultHandle == 0) {
		Result->Val = Std$String$new(mysql_error(Handle));
		return MESSAGE;
	};
	result_t *Res = new(result_t);
	Res->Type = ResultT;
	Res->Handle = ResultHandle;
	Res->FieldCount = mysql_field_count(Handle);
	Res->Fields = mysql_fetch_fields(ResultHandle);
	Result->Val = Res;
	return SUCCESS;
};

METHOD("store_result", TYP, T) {
	MYSQL *Handle = &((connection_t *)Args[0].Val)->Handle;
	MYSQL_RES *ResultHandle = mysql_store_result(Handle);
	int FieldCount = mysql_field_count(Handle);
	if (ResultHandle == 0) {
		if (FieldCount) {
			Result->Val = Std$String$new(mysql_error(Handle));
			return MESSAGE;
		} else {
			return FAILURE;
		};
	};
	result_t *Res = new(result_t);
	Res->Type = ResultT;
	Res->Handle = ResultHandle;
	Res->FieldCount = FieldCount;
	MYSQL_FIELD *Fields = Res->Fields = mysql_fetch_fields(ResultHandle);
	if (FieldCount) {
		Std$List_t *FieldList = new(Std$List_t);
		FieldList->Type = Std$List$T;
		Std$List_node *Node = new(Std$List_node);
		Node->Value = Std$String$copy_length(Fields[0].name, Fields[0].name_length);
		Std$List_node *Prev = Node;
		FieldList->Head = Node;
		FieldList->Cache = Node;
		FieldList->Index = 1;
		FieldList->Access = 4;
		for (int I = 1; I < FieldCount; ++I) {
			Node = new(Std$List_node);
			Node->Prev = Prev;
			Prev->Next = Node;
			Node->Value = Std$String$copy_length(Fields[I].name, Fields[I].name_length);
			Prev = Node;
		};
		FieldList->Tail = Node;
		FieldList->Length = FieldCount;
		Res->FieldList = FieldList;
	} else {
		Res->FieldList = Std$Object$Nil;
	};
	Result->Val = Res;
	return SUCCESS;
};

METHOD("fields", TYP, ResultT) {
	result_t *Res = Args[0].Val;
	Result->Val = Res->FieldList;
	return SUCCESS;
};

static inline Std$Object_t *convert_field(MYSQL_FIELD *Field, void *Data, unsigned long Length) {
	if (Data == 0) return Std$Object$Nil;
	printf("Field type = %d\n", Field->type);
	switch (Field->type) {
	case MYSQL_TYPE_TINY: return Std$Integer$new_small(*(signed char *)Data);
	case MYSQL_TYPE_SHORT: return Std$Integer$new_small(*(short *)Data);
	case MYSQL_TYPE_LONG: return Std$Integer$new_small(*(long *)Data);
	case MYSQL_TYPE_INT24: return Std$Integer$new_small(*(long *)Data);
	case MYSQL_TYPE_LONGLONG:
	case MYSQL_TYPE_DECIMAL:
	case MYSQL_TYPE_NEWDECIMAL:
	case MYSQL_TYPE_FLOAT: return Std$Real$new(*(float *)Data);
	case MYSQL_TYPE_DOUBLE: return Std$Real$new(*(double *)Data);
	case MYSQL_TYPE_BIT:
	case MYSQL_TYPE_TIMESTAMP:
	case MYSQL_TYPE_DATE:
	case MYSQL_TYPE_TIME:
	case MYSQL_TYPE_DATETIME:
	case MYSQL_TYPE_YEAR:
	case MYSQL_TYPE_STRING: return Std$String$copy_length(Data, Length);
	case MYSQL_TYPE_VAR_STRING: return Std$String$copy_length(Data, Length);
	case MYSQL_TYPE_BLOB:
	case MYSQL_TYPE_SET:
	case MYSQL_TYPE_ENUM:
	case MYSQL_TYPE_GEOMETRY:
	case MYSQL_TYPE_NULL: return Std$Object$Nil;
	};
};

METHOD("row", TYP, ResultT) {
	result_t *Res = Args[0].Val;
	MYSQL_ROW *Row = mysql_fetch_row(Res->Handle);
	if (Row == 0) return FAILURE;
	if (Res->FieldCount == 0) return SUCCESS;
	unsigned long *Lengths = mysql_fetch_lengths(Res->Handle);
	MYSQL_FIELD *Fields = Res->Fields;
	Std$List_t *FieldList = new(Std$List_t);
	FieldList->Type = Std$List$T;
	Std$List_node *Node = new(Std$List_node);
	Node->Value = convert_field(Fields, Row[0], Lengths[0]);
	Std$List_node *Prev = Node;
	FieldList->Head = Node;
	FieldList->Cache = Node;
	FieldList->Index = 1;
	FieldList->Access = 4;
	for (int I = 1; I < Res->FieldCount; ++I) {
		Node = new(Std$List_node);
		Node->Prev = Prev;
		Prev->Next = Node;
		Node->Value = Std$String$copy_length(Row[I], Lengths[I]);
		Prev = Node;
	};
	FieldList->Tail = Node;
	FieldList->Length = Res->FieldCount;
	Result->Val = FieldList;
	return SUCCESS;
};

METHOD("free", TYP, ResultT) {
	result_t *Res = Args[0].Val;
	mysql_free_result(Res->Handle);
	return SUCCESS;
};

void __init(Riva$Module_t *Module) {
	mysql_library_init(0, 0, 0);
};
