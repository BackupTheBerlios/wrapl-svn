#include <Gtk/Gtk/Accessible.h>

TYPE(T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_accessible_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
