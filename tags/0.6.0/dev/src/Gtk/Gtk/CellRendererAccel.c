#include <Gtk/Gtk/CellRendererAccel.h>

TYPE(T, Gtk$Gtk$CellRendererText$T, Gtk$Gtk$CellRenderer$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_cellrendereraccel_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
