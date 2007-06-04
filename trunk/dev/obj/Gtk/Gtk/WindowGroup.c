#include <Gtk/Gtk/WindowGroup.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/WindowGroup.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Window.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWindowGroup * result = gtk_window_group_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_window_group_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddWindow", TYP, T, TYP, Gtk$Gtk$Window$T) {
	GtkWindowGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_window_group_add_window(self, window);
	return SUCCESS;
};

METHOD("RemoveWindow", TYP, T, TYP, Gtk$Gtk$Window$T) {
	GtkWindowGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_window_group_remove_window(self, window);
	return SUCCESS;
};

