#include <Gtk/Gtk/Progress.h>

TYPE(T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_progress_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
