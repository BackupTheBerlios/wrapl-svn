#include <Gtk/Gtk/TextMark.h>

TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_textmark_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
