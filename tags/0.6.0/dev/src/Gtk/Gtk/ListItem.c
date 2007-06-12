#include <Gtk/Gtk/ListItem.h>

TYPE(T, Gtk$Gtk$Item$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_listitem_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};