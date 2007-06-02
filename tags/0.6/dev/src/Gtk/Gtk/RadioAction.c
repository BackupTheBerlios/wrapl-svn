#include <Gtk/Gtk/RadioAction.h>

TYPE(T, Gtk$Gtk$ToggleAction$T, Gtk$Gtk$Action$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_radioaction_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
