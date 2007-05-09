#include <Gtk/Gtk/ToggleAction.h>

TYPE(T, Gtk$Gtk$Action$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_toggleaction_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
