#include <Gtk/Gtk/Bin.h>

TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

METHOD("child", TYP, T) {
	Gtk$GObject$Object_t *Object = Args[0].Val;
	Result->Val = Gtk$GObject$Object$gtk_to_riva(gtk_bin_get_child(Object->Handle));
	return SUCCESS;
};
