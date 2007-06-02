#include <Gtk/Gtk/HScale.h>

TYPE(T, Gtk$Gtk$Scale$T, Gtk$Gtk$Range$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_hscale_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
