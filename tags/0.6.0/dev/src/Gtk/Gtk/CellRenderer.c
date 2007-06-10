#include <Gtk/Gtk/CellRenderer.h>

TYPE(T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_cellrenderer_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
