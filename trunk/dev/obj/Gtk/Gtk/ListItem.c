#include <Gtk/Gtk/ListItem.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/ListItem.h>
/***********************************/
TYPE(T, Gtk$Gtk$Item$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkListItem * result = gtk_list_item_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithLabel, 1) {
	char *label = Std$String$flatten(Args[0].Val);
	GtkListItem * result = gtk_list_item_new_with_label(label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_list_item_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Deselect", TYP, T) {
	GtkListItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_list_item_deselect(self);
	return SUCCESS;
};

METHOD("Select", TYP, T) {
	GtkListItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_list_item_select(self);
	return SUCCESS;
};

