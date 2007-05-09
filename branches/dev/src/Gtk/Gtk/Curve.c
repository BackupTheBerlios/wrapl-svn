#include <Gtk/Gtk/Curve.h>

TYPE(T, Gtk$Gtk$DrawingArea$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_curve_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
