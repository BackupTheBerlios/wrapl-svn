#include <Gtk/Gtk/Window.h>

TYPE(T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

Lang$Integer_smallt TOPLEVEL[] = {{Lang$Integer$SmallT, GTK_WINDOW_TOPLEVEL}};
Lang$Integer_smallt POPUP[] = {{Lang$Integer$SmallT, GTK_WINDOW_POPUP}};

GLOBAL_FUNCTION(New, 1) {
	GtkWidget *Handle = gtk_window_new(((Lang$Integer_smallt *)Args[0].Val)->Value);
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
