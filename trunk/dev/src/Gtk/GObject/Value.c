#include <Gtk/GObject/Value.h>
#include <Gtk/GObject/Object.h>
#include <Riva.h>

SYMBOL($true, "true");
SYMBOL($false, "false");

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
		if (G_VALUE_HOLDS(Value, G_TYPE_OBJECT)) {
			return Gtk$GObject$Object$to_riva(g_value_get_object(Value));
		} else {
			return Std$Address$new(g_value_peek_pointer(Value));
		};
	};
	};
};

void _to_gtk(Std$Object_t *Source, GValue *Dest) {
	if (Source == Std$Object$Nil) {
		if (!G_IS_VALUE(Dest)) g_value_init(Dest, G_TYPE_NONE);
	} else if (Source->Type == Std$Integer$SmallT) {
		if (!G_IS_VALUE(Dest)) g_value_init(Dest, G_TYPE_LONG);
		g_value_set_long(Dest, ((Std$Integer_smallt *)Source)->Value);
	} else if (Source->Type == Std$String$T) {
		if (!G_IS_VALUE(Dest)) g_value_init(Dest, G_TYPE_STRING);
		g_value_set_string(Dest, Std$String$flatten(Source));
	} else if (Source->Type == Std$Real$T) {
		if (!G_IS_VALUE(Dest)) g_value_init(Dest, G_TYPE_DOUBLE);
		g_value_set_double(Dest, ((Std$Real_t *)Source)->Value);
	} else if (Source->Type == Std$Address$T) {
		if (!G_IS_VALUE(Dest)) g_value_init(Dest, G_TYPE_POINTER);
		g_value_set_pointer(Dest, ((Std$Address_t *)Source)->Value);
	} else if (Source == $true) {
		if (!G_IS_VALUE(Dest)) g_value_init(Dest, G_TYPE_BOOLEAN);
		g_value_set_boolean(Dest, TRUE);
	} else if (Source == $false) {
		if (!G_IS_VALUE(Dest)) g_value_init(Dest, G_TYPE_BOOLEAN);
		g_value_set_boolean(Dest, FALSE);
	};
};
