#include <Gtk/Gtk/TextTagTable.h>

TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_texttagtable_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
