#include <Gtk/Gtk/HRuler.h>

TYPE(T, Gtk$Gtk$Ruler$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_hruler_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
