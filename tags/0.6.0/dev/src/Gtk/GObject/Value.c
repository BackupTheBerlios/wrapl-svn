#include <Gtk/GObject/Value.h>
#include <Gtk/GObject/Object.h>
#include <Riva.h>

SYMBOL($TRUE, "TRUE");
SYMBOL($FALSE, "FALSE");

Lang$Object_t *_to_riva(const GValue *Value) {
	switch (G_VALUE_TYPE(Value)) {
	case G_TYPE_NONE: return Lang$Object$Nil;
	case G_TYPE_CHAR: return Lang$Integer$new_small(g_value_get_char(Value));
	case G_TYPE_UCHAR: return Lang$Integer$new_small(g_value_get_uchar(Value));
	case G_TYPE_BOOLEAN: return g_value_get_boolean(Value) ? $TRUE : $FALSE;
	case G_TYPE_INT: return Lang$Integer$new_small(g_value_get_int(Value));
	case G_TYPE_UINT: return Lang$Integer$new_small(g_value_get_uint(Value));
	case G_TYPE_LONG: return Lang$Integer$new_small(g_value_get_long(Value));
	case G_TYPE_ULONG: return Lang$Integer$new_small(g_value_get_ulong(Value));
	case G_TYPE_ENUM: return Lang$Integer$new_small(g_value_get_enum(Value));
	case G_TYPE_FLAGS: return Lang$Integer$new_small(g_value_get_flags(Value));
	case G_TYPE_FLOAT: return Lang$Real$new(g_value_get_float(Value));
	case G_TYPE_DOUBLE: return Lang$Real$new(g_value_get_double(Value));
	case G_TYPE_STRING: return Lang$String$new(g_value_get_string(Value));
	case G_TYPE_POINTER: return Lang$Address$new(g_value_get_pointer(Value));
	default: {
		if (G_VALUE_HOLDS(Value, G_TYPE_OBJECT)) {
			return Gtk$GObject$Object$gtk_to_riva(g_value_get_object(Value));
		} else {
			return Lang$Address$new(g_value_peek_pointer(Value));
		};
	};
	};
};

void _to_gtk(Lang$Object_t *Source, GValue *Dest) {
	if (Source == Lang$Object$Nil) {
		if (!G_IS_VALUE(Dest)) g_value_init(Dest, G_TYPE_NONE);
	} else if (Source->Type == Lang$Integer$SmallT) {
		if (!G_IS_VALUE(Dest)) g_value_init(Dest, G_TYPE_LONG);
		g_value_set_long(Dest, ((Lang$Integer_smallt *)Source)->Value);
	} else if (Source->Type == Lang$String$T) {
		if (!G_IS_VALUE(Dest)) g_value_init(Dest, G_TYPE_STRING);
		g_value_set_string(Dest, Lang$String$flatten(Source));
	} else if (Source->Type == Lang$Real$T) {
		if (!G_IS_VALUE(Dest)) g_value_init(Dest, G_TYPE_DOUBLE);
		g_value_set_double(Dest, ((Lang$Real_t *)Source)->Value);
	} else if (Source->Type == Lang$Address$T) {
		if (!G_IS_VALUE(Dest)) g_value_init(Dest, G_TYPE_POINTER);
		g_value_set_pointer(Dest, ((Lang$Address_t *)Source)->Value);
	} else if (Source == $TRUE) {
		if (!G_IS_VALUE(Dest)) g_value_init(Dest, G_TYPE_BOOLEAN);
		g_value_set_boolean(Dest, TRUE);
	} else if (Source == $FALSE) {
		if (!G_IS_VALUE(Dest)) g_value_init(Dest, G_TYPE_BOOLEAN);
		g_value_set_boolean(Dest, FALSE);
	};
};
