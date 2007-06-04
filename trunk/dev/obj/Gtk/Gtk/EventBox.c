#include <Gtk/Gtk/EventBox.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/EventBox.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkEventBox * result = gtk_event_box_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_event_box_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetAboveChild", TYP, T) {
	GtkEventBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_event_box_get_above_child(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetVisibleWindow", TYP, T) {
	GtkEventBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_event_box_get_visible_window(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetAboveChild", TYP, T, TYP, Std$Symbol$T) {
	GtkEventBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int above_child = Args[1].Val == $true;
	gtk_event_box_set_above_child(self, above_child);
	return SUCCESS;
};

METHOD("SetVisibleWindow", TYP, T, TYP, Std$Symbol$T) {
	GtkEventBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int visible_window = Args[1].Val == $true;
	gtk_event_box_set_visible_window(self, visible_window);
	return SUCCESS;
};

