#include <Gtk/Gtk/RadioToolButton.h>

TYPE(T, Gtk$Gtk$ToggleToolButton$T, Gtk$Gtk$ToolButton$T, Gtk$Gtk$ToolItem$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_radiotoolbutton_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
