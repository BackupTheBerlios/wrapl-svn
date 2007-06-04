#include <Gtk/Gtk/IconFactory.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/IconSet.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/IconFactory.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkIconFactory * result = gtk_icon_factory_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_icon_factory_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(LookupDefault, 1) {
	char *stock_id = Std$String$flatten(Args[0].Val);
	GtkIconSet * result = gtk_icon_factory_lookup_default(stock_id);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Add", TYP, T, TYP, Std$String$T, TYP, Gtk$Gtk$IconSet$T) {
	GtkIconFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *stock_id = Std$String$flatten(Args[1].Val);
	GtkIconSet * icon_set= ((Gtk$Gtk$IconSet_t *)Args[2].Val)->Value;
	gtk_icon_factory_add(self, stock_id, icon_set);
	return SUCCESS;
};

METHOD("AddDefault", TYP, T) {
	GtkIconFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_icon_factory_add_default(self);
	return SUCCESS;
};

METHOD("Lookup", TYP, T, TYP, Std$String$T) {
	GtkIconFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *stock_id = Std$String$flatten(Args[1].Val);
	GtkIconSet * result = gtk_icon_factory_lookup(self, stock_id);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("RemoveDefault", TYP, T) {
	GtkIconFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_icon_factory_remove_default(self);
	return SUCCESS;
};

