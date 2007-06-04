#include <Gtk/Gtk/Item.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gtk/Item.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(FactoriesPathDelete, 2) {
	char *ifactory_path = Std$String$flatten(Args[0].Val);
	char *path = Std$String$flatten(Args[1].Val);
	gtk_item_factories_path_delete(ifactory_path, path);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_item_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Deselect", TYP, T) {
	GtkItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_item_deselect(self);
	return SUCCESS;
};

METHOD("Select", TYP, T) {
	GtkItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_item_select(self);
	return SUCCESS;
};

METHOD("Toggle", TYP, T) {
	GtkItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_item_toggle(self);
	return SUCCESS;
};

