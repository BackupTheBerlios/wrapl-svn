#include <Gtk/Gtk/HSeparator.h>

TYPE(T, Gtk$Gtk$Separator$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_hseparator_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
