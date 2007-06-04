#include <Gtk/Gtk/MenuItem.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/MenuItem.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Item$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkMenuItem * result = gtk_menu_item_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithLabel, 1) {
	char *label = Std$String$flatten(Args[0].Val);
	GtkMenuItem * result = gtk_menu_item_new_with_label(label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithMnemonic, 1) {
	char *label = Std$String$flatten(Args[0].Val);
	GtkMenuItem * result = gtk_menu_item_new_with_mnemonic(label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_menu_item_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Activate", TYP, T) {
	GtkMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_menu_item_activate(self);
	return SUCCESS;
};

METHOD("Deselect", TYP, T) {
	GtkMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_menu_item_deselect(self);
	return SUCCESS;
};

METHOD("GetRightJustified", TYP, T) {
	GtkMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_menu_item_get_right_justified(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSubmenu", TYP, T) {
	GtkMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_menu_item_get_submenu(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("RemoveSubmenu", TYP, T) {
	GtkMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_menu_item_remove_submenu(self);
	return SUCCESS;
};

METHOD("Select", TYP, T) {
	GtkMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_menu_item_select(self);
	return SUCCESS;
};

METHOD("SetAccelPath", TYP, T, TYP, Std$String$T) {
	GtkMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *accel_path = Std$String$flatten(Args[1].Val);
	gtk_menu_item_set_accel_path(self, accel_path);
	return SUCCESS;
};

METHOD("SetRightJustified", TYP, T, TYP, Std$Symbol$T) {
	GtkMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int right_justified = Args[1].Val == $true;
	gtk_menu_item_set_right_justified(self, right_justified);
	return SUCCESS;
};

METHOD("SetSubmenu", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * submenu = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_menu_item_set_submenu(self, submenu);
	return SUCCESS;
};

METHOD("ToggleSizeAllocate", TYP, T, TYP, Std$Integer$SmallT) {
	GtkMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int allocation = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_menu_item_toggle_size_allocate(self, allocation);
	return SUCCESS;
};

METHOD("ToggleSizeRequest", TYP, T, TYP, Std$Object$T) {
	GtkMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* requisition = 0;
	gtk_menu_item_toggle_size_request(self, requisition);
	return SUCCESS;
};

