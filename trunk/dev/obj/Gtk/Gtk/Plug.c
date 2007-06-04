#include <Gtk/Gtk/Plug.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/Gtk/Plug.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$Window$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	GdkNativeWindow socket_id = 0;
	GtkPlug * result = gtk_plug_new(socket_id);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewForDisplay, 2) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkNativeWindow socket_id = 0;
	GtkPlug * result = gtk_plug_new_for_display(display, socket_id);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_plug_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Construct", TYP, T, TYP, Std$Object$T) {
	GtkPlug * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkNativeWindow socket_id = 0;
	gtk_plug_construct(self, socket_id);
	return SUCCESS;
};

METHOD("ConstructForDisplay", TYP, T, TYP, Gtk$Gdk$Display$T, TYP, Std$Object$T) {
	GtkPlug * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkNativeWindow socket_id = 0;
	gtk_plug_construct_for_display(self, display, socket_id);
	return SUCCESS;
};

METHOD("GetId", TYP, T) {
	GtkPlug * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkNativeWindow result = gtk_plug_get_id(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

