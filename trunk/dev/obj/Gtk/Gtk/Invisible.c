#include <Gtk/Gtk/Invisible.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Screen.h>
#include <Gtk/Gtk/Invisible.h>
/***********************************/
TYPE(T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkInvisible * result = gtk_invisible_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewForScreen, 1) {
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkInvisible * result = gtk_invisible_new_for_screen(screen);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_invisible_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetScreen", TYP, T) {
	GtkInvisible * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkScreen * result = gtk_invisible_get_screen(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("SetScreen", TYP, T, TYP, Gtk$Gdk$Screen$T) {
	GtkInvisible * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_invisible_set_screen(self, screen);
	return SUCCESS;
};

