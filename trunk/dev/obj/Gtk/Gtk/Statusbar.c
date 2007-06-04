#include <Gtk/Gtk/Statusbar.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Statusbar.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$HBox$T, Gtk$Gtk$Box$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkStatusbar * result = gtk_statusbar_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_statusbar_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetContextId", TYP, T, TYP, Std$String$T) {
	GtkStatusbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *context_description = Std$String$flatten(Args[1].Val);
	int result = gtk_statusbar_get_context_id(self, context_description);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetHasResizeGrip", TYP, T) {
	GtkStatusbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_statusbar_get_has_resize_grip(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Pop", TYP, T, TYP, Std$Integer$SmallT) {
	GtkStatusbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int context_id = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_statusbar_pop(self, context_id);
	return SUCCESS;
};

METHOD("Push", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$String$T) {
	GtkStatusbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int context_id = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *text = Std$String$flatten(Args[2].Val);
	int result = gtk_statusbar_push(self, context_id, text);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Remove", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkStatusbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int context_id = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int message_id = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_statusbar_remove(self, context_id, message_id);
	return SUCCESS;
};

METHOD("SetHasResizeGrip", TYP, T, TYP, Std$Symbol$T) {
	GtkStatusbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_statusbar_set_has_resize_grip(self, setting);
	return SUCCESS;
};

