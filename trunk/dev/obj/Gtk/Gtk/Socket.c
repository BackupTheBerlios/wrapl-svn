#include <Gtk/Gtk/Socket.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Socket.h>
/***********************************/
TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkSocket * result = gtk_socket_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_socket_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddId", TYP, T, TYP, Std$Object$T) {
	GtkSocket * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkNativeWindow window_id = 0;
	gtk_socket_add_id(self, window_id);
	return SUCCESS;
};

METHOD("GetId", TYP, T) {
	GtkSocket * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkNativeWindow result = gtk_socket_get_id(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Steal", TYP, T, TYP, Std$Object$T) {
	GtkSocket * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkNativeWindow wid = 0;
	gtk_socket_steal(self, wid);
	return SUCCESS;
};

