#include <Gtk/Gtk/OptionMenu.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/Gtk/OptionMenu.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
/***********************************/
TYPE(T, Gtk$Gtk$Button$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkOptionMenu * result = gtk_option_menu_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_option_menu_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetHistory", TYP, T) {
	GtkOptionMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_option_menu_get_history(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetMenu", TYP, T) {
	GtkOptionMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_option_menu_get_menu(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("RemoveMenu", TYP, T) {
	GtkOptionMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_option_menu_remove_menu(self);
	return SUCCESS;
};

METHOD("SetHistory", TYP, T, TYP, Std$Integer$SmallT) {
	GtkOptionMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int index_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_option_menu_set_history(self, index_);
	return SUCCESS;
};

METHOD("SetMenu", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkOptionMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * menu = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_option_menu_set_menu(self, menu);
	return SUCCESS;
};

