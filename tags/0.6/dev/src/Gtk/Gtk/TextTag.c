#include <Gtk/Gtk/TextTag.h>

TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_texttag_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
