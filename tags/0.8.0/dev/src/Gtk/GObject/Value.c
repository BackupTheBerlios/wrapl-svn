#include <Gtk/GObject/Value.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Riva.h>

SYMBOL($true, "true");
SYMBOL($false, "false");

TYPE(T);

Std$Object_t *_to_riva(const GValue *Value) {
	switch (G_VALUE_TYPE(Value)) {
	case G_TYPE_NONE: return Std$Object$Nil;
	case G_TYPE_CHAR: return Std$Integer$new_small(g_value_get_char(Value));
	case G_TYPE_UCHAR: return Std$Integer$new_small(g_value_get_uchar(Value));
	case G_TYPE_BOOLEAN: return g_value_get_boolean(Value) ? $true : $false;
	case G_TYPE_INT: return Std$Integer$new_small(g_value_get_int(Value));
	case G_TYPE_UINT: return Std$Integer$new_small(g_value_get_uint(Value));
	case G_TYPE_LONG: return Std$Integer$new_small(g_value_get_long(Value));
	case G_TYPE_ULONG: return Std$Integer$new_small(g_value_get_ulong(Value));
	case G_TYPE_ENUM: return Std$Integer$new_small(g_value_get_enum(Value));
	case G_TYPE_FLAGS: return Std$Integer$new_small(g_value_get_flags(Value));
	case G_TYPE_FLOAT: return Std$Real$new(g_value_get_float(Value));
	case G_TYPE_DOUBLE: return Std$Real$new(g_value_get_double(Value));
	case G_TYPE_STRING: return Std$String$new(g_value_get_string(Value));
	case G_TYPE_POINTER: return Std$Address$new(g_value_get_pointer(Value));
	default: {
		Std$Type_t *Type;
		if (G_VALUE_HOLDS(Value, G_TYPE_OBJECT)) {
			return Gtk$GObject$Object$to_riva(g_value_get_object(Value));
		} else if (g_value_fits_pointer(Value) && (Type = Gtk$GObject$Type$to_riva(G_VALUE_TYPE(Value)))) {
			Gtk$GObject$Object_t *Object = new(Gtk$GObject$Object_t);
			Object->Type = Type;
			Object->Handle = g_value_peek_pointer(Value);
			return Object;
		} else {
			printf("Warning: Unknown parameter type: %s\n", G_VALUE_TYPE_NAME(Value));
			return Std$Address$new(g_value_peek_pointer(Value));
		};
	};
	};
};

void _to_gtk(Std$Object_t *Source, GValue *Dest) {
	if (G_IS_VALUE(Dest)) g_value_unset(Dest);
	if (Source == Std$Object$Nil) {
		g_value_init(Dest, G_TYPE_NONE);
	} else if (Source->Type == Std$Integer$SmallT) {
		g_value_init(Dest, G_TYPE_LONG);
		g_value_set_long(Dest, ((Std$Integer_smallt *)Source)->Value);
	} else if (Source->Type == Std$String$T) {
		g_value_init(Dest, G_TYPE_STRING);
		g_value_set_string(Dest, Std$String$flatten(Source));
	} else if (Source->Type == Std$Real$T) {
		g_value_init(Dest, G_TYPE_DOUBLE);
		g_value_set_double(Dest, ((Std$Real_t *)Source)->Value);
	} else if (Source->Type == Std$Address$T) {
		g_value_init(Dest, G_TYPE_POINTER);
		g_value_set_pointer(Dest, ((Std$Address_t *)Source)->Value);
	} else if (Source == $true) {
		g_value_init(Dest, G_TYPE_BOOLEAN);
		g_value_set_boolean(Dest, TRUE);
	} else if (Source == $false) {
		g_value_init(Dest, G_TYPE_BOOLEAN);
		g_value_set_boolean(Dest, FALSE);
	};
};

GLOBAL_FUNCTION(New, 0) {
	Gtk$GObject$Value_t *Value = new(Gtk$GObject$Value_t);
	Value->Type = T;
	Value->Value = new(GValue);
	if (Count > 0) _to_gtk(Args[0].Val, Value->Value);
	Result->Val = Value;
	return SUCCESS;
};

METHOD("Get", TYP, T) {
	Gtk$GObject$Value_t *Value = Args[0].Val;
	Result->Val = _to_riva(Value->Value);
	return SUCCESS;
};

/*
METHOD("Set", TYP, T, ANY) {
	Gtk$GObject$Value_t *Value = Args[0].Val;
	_to_gtk(Args[1].Val, Value->Value);
	return SUCCESS;
};
*/

METHOD("Set", TYP, T, VAL, Std$Object$Nil) {
	Gtk$GObject$Value_t *Value = Args[0].Val;
	g_value_init(Value->Value, G_TYPE_NONE);
	return SUCCESS;
};

METHOD("Set", TYP, T, TYP, Std$Integer$SmallT) {
	Gtk$GObject$Value_t *Value = Args[0].Val;
	g_value_init(Value->Value, G_TYPE_LONG);
	g_value_set_long(Value->Value, ((Std$Integer_smallt *)Args[1].Val)->Value);
	return SUCCESS;
};

METHOD("Set", TYP, T, TYP, Std$String$T) {
	Gtk$GObject$Value_t *Value = Args[0].Val;
	g_value_init(Value->Value, G_TYPE_STRING);
	g_value_set_string(Value->Value, Std$String$flatten(Args[1].Val));
	return SUCCESS;
};

METHOD("Set", TYP, T, TYP, Std$Real$T) {
	Gtk$GObject$Value_t *Value = Args[0].Val;
	g_value_init(Value->Value, G_TYPE_DOUBLE);
	g_value_set_double(Value->Value, ((Std$Real_t *)Args[1].Val)->Value);
	return SUCCESS;
};

METHOD("Set", TYP, T, TYP, Std$Address$T) {
	Gtk$GObject$Value_t *Value = Args[0].Val;
	g_value_init(Value->Value, G_TYPE_POINTER);
	g_value_set_pointer(Value->Value, ((Std$Address_t *)Args[1].Val)->Value);
	return SUCCESS;
};

METHOD("Set", TYP, T, VAL, $true) {
	Gtk$GObject$Value_t *Value = Args[0].Val;
	g_value_init(Value->Value, G_TYPE_BOOLEAN);
	g_value_set_boolean(Value->Value, TRUE);
	return SUCCESS;
};

METHOD("Set", TYP, T, VAL, $false) {
	Gtk$GObject$Value_t *Value = Args[0].Val;
	g_value_init(Value->Value, G_TYPE_BOOLEAN);
	g_value_set_boolean(Value->Value, FALSE);
	return SUCCESS;
};

METHOD("Unset", TYP, T) {
	Gtk$GObject$Value_t *Value = Args[0].Val;
	g_value_unset(Value->Value);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	Gtk$GObject$Value_t *Value = Args[0].Val;
	Gtk$GObject$Value_t *Copy = new(Gtk$GObject$Value_t);
	Copy->Type = T;
	Copy->Value = new(GValue);
	g_value_copy(Value->Value, Copy->Value);
	Result->Val = Copy;
	return SUCCESS;
};
