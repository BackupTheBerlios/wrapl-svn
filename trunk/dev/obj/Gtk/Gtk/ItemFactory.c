#include <Gtk/Gtk/ItemFactory.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 9
#include <Gtk/Gtk/ItemFactoryEntry.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/MenuEntry.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/DestroyNotify.h>
#include <Gtk/Gtk/AccelGroup.h>
#include <Gtk/Gtk/Widget.h>
#include <Gtk/Gtk/ItemFactory.h>
#include <Gtk/Gtk/TranslateFunc.h>
/***********************************/
TYPE(T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 3) {
	GType container_type;
	char *path = Std$String$flatten(Args[1].Val);
	GtkAccelGroup * accel_group = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	GtkItemFactory * result = gtk_item_factory_new(container_type, path, accel_group);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(AddForeign, 5) {
	GtkWidget * accel_widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *full_path = Std$String$flatten(Args[1].Val);
	GtkAccelGroup * accel_group = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int keyval = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int modifiers = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_item_factory_add_foreign(accel_widget, full_path, accel_group, keyval, modifiers);
	return SUCCESS;
};

GLOBAL_FUNCTION(CreateMenuEntries, 2) {
	int n_entries = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GtkMenuEntry * entries= &((Gtk$Gtk$MenuEntry_t *)Args[1].Val)->Value;
	gtk_item_factory_create_menu_entries(n_entries, entries);
	return SUCCESS;
};

GLOBAL_FUNCTION(FromPath, 1) {
	char *path = Std$String$flatten(Args[0].Val);
	GtkItemFactory * result = gtk_item_factory_from_path(path);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(FromWidget, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkItemFactory * result = gtk_item_factory_from_widget(widget);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_item_factory_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(PathFromWidget, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_item_factory_path_from_widget(widget);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(PopupDataFromWidget, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	void * result = gtk_item_factory_popup_data_from_widget(widget);
	Result->Val = Std$Address$new(result);
	return SUCCESS;
};

METHOD("Construct", TYP, T, TYP, Gtk$GObject$Type$T, TYP, Std$String$T, TYP, Gtk$Gtk$AccelGroup$T) {
	GtkItemFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GType container_type;
	char *path = Std$String$flatten(Args[2].Val);
	GtkAccelGroup * accel_group = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	gtk_item_factory_construct(self, container_type, path, accel_group);
	return SUCCESS;
};

METHOD("CreateItem", TYP, T, TYP, Gtk$Gtk$ItemFactoryEntry$T, TYP, Std$Address$T, TYP, Std$Integer$SmallT) {
	GtkItemFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkItemFactoryEntry * entry= &((Gtk$Gtk$ItemFactoryEntry_t *)Args[1].Val)->Value;
	void *callback_data = ((Std$Address_t *)Args[2].Val)->Value;
	int callback_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_item_factory_create_item(self, entry, callback_data, callback_type);
	return SUCCESS;
};

METHOD("CreateItems", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$ItemFactoryEntry$T, TYP, Std$Address$T) {
	GtkItemFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int n_entries = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkItemFactoryEntry * entries= &((Gtk$Gtk$ItemFactoryEntry_t *)Args[2].Val)->Value;
	void *callback_data = ((Std$Address_t *)Args[3].Val)->Value;
	gtk_item_factory_create_items(self, n_entries, entries, callback_data);
	return SUCCESS;
};

METHOD("CreateItemsAc", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$ItemFactoryEntry$T, TYP, Std$Address$T, TYP, Std$Integer$SmallT) {
	GtkItemFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int n_entries = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkItemFactoryEntry * entries= &((Gtk$Gtk$ItemFactoryEntry_t *)Args[2].Val)->Value;
	void *callback_data = ((Std$Address_t *)Args[3].Val)->Value;
	int callback_type = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_item_factory_create_items_ac(self, n_entries, entries, callback_data, callback_type);
	return SUCCESS;
};

METHOD("DeleteEntries", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$ItemFactoryEntry$T) {
	GtkItemFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int n_entries = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkItemFactoryEntry * entries= &((Gtk$Gtk$ItemFactoryEntry_t *)Args[2].Val)->Value;
	gtk_item_factory_delete_entries(self, n_entries, entries);
	return SUCCESS;
};

METHOD("DeleteEntry", TYP, T, TYP, Gtk$Gtk$ItemFactoryEntry$T) {
	GtkItemFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkItemFactoryEntry * entry= &((Gtk$Gtk$ItemFactoryEntry_t *)Args[1].Val)->Value;
	gtk_item_factory_delete_entry(self, entry);
	return SUCCESS;
};

METHOD("DeleteItem", TYP, T, TYP, Std$String$T) {
	GtkItemFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *path = Std$String$flatten(Args[1].Val);
	gtk_item_factory_delete_item(self, path);
	return SUCCESS;
};

METHOD("GetItem", TYP, T, TYP, Std$String$T) {
	GtkItemFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *path = Std$String$flatten(Args[1].Val);
	GtkWidget * result = gtk_item_factory_get_item(self, path);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetItemByAction", TYP, T, TYP, Std$Integer$SmallT) {
	GtkItemFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int action = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkWidget * result = gtk_item_factory_get_item_by_action(self, action);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetWidget", TYP, T, TYP, Std$String$T) {
	GtkItemFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *path = Std$String$flatten(Args[1].Val);
	GtkWidget * result = gtk_item_factory_get_widget(self, path);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetWidgetByAction", TYP, T, TYP, Std$Integer$SmallT) {
	GtkItemFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int action = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkWidget * result = gtk_item_factory_get_widget_by_action(self, action);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Popup", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkItemFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int mouse_button = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int time_ = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_item_factory_popup(self, x, y, mouse_button, time_);
	return SUCCESS;
};

METHOD("PopupData", TYP, T) {
	GtkItemFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	void * result = gtk_item_factory_popup_data(self);
	Result->Val = Std$Address$new(result);
	return SUCCESS;
};

METHOD("PopupWithData", TYP, T, TYP, Std$Address$T, TYP, Std$Function$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkItemFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	void *popup_data = ((Std$Address_t *)Args[1].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[2].Val);
	int x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int mouse_button = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int time_ = ((Std$Integer_smallt *)Args[6].Val)->Value;
	gtk_item_factory_popup_with_data(self, popup_data, destroy, x, y, mouse_button, time_);
	return SUCCESS;
};

METHOD("SetTranslateFunc", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkItemFactory * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTranslateFunc func = Gtk$Gtk$TranslateFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkDestroyNotify notify = Gtk$Gtk$DestroyNotify$new(Args[3].Val);
	gtk_item_factory_set_translate_func(self, func, data, notify);
	return SUCCESS;
};

