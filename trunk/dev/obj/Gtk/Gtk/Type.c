#include <Gtk/Gtk/Type.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gtk/TypeInfo.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
GLOBAL_FUNCTION(Class, 1) {
	GType type;
	void * result = gtk_type_class(type);
	Result->Val = Std$Address$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(EnumFindValue, 2) {
	GType enum_type;
	char *value_name = Std$String$flatten(Args[1].Val);
	GtkEnumValue* result = gtk_type_enum_find_value(enum_type, value_name);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(EnumGetValues, 1) {
	GType enum_type;
	GtkEnumValue* result = gtk_type_enum_get_values(enum_type);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(FlagsFindValue, 2) {
	GType flags_type;
	char *value_name = Std$String$flatten(Args[1].Val);
	GtkFlagValue* result = gtk_type_flags_find_value(flags_type, value_name);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(FlagsGetValues, 1) {
	GType flags_type;
	GtkFlagValue* result = gtk_type_flags_get_values(flags_type);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(Init, 1) {
	GTypeDebugFlags debug_flags = 0;
	gtk_type_init(debug_flags);
	return SUCCESS;
};

GLOBAL_FUNCTION(New, 1) {
	GType type;
	void * result = gtk_type_new(type);
	Result->Val = Std$Address$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Unique, 2) {
	GType parent_type;
	GtkTypeInfo * gtkinfo= &((Gtk$Gtk$TypeInfo_t *)Args[1].Val)->Value;
	GType result = gtk_type_unique(parent_type, gtkinfo);
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

