#include <Gtk/Gtk/CellRendererToggle.h>

TYPE(T, Gtk$Gtk$CellRenderer$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_cellrenderertoggle_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
