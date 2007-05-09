#include <Gtk/Gtk/VBox.h>

TYPE(T, Gtk$Gtk$Box$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

SYMBOL($TRUE, "TRUE");

GLOBAL_FUNCTION(New, 2) {
	GtkWidget *Handle = gtk_vbox_new(Args[0].Val == $TRUE, ((Lang$Integer_smallt *)Args[1].Val)->Value);
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
