#include <Gtk/Gtk/IMMulticontext.h>

TYPE(T, Gtk$Gtk$IMContext$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_immulticontext_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
