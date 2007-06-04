#include <Gtk/Gtk/RcStyle.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gtk/RcStyle.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkRcStyle * result = gtk_rc_style_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_rc_style_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GtkRcStyle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkRcStyle * result = gtk_rc_style_copy(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GtkRcStyle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_rc_style_ref(self);
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GtkRcStyle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_rc_style_unref(self);
	return SUCCESS;
};

