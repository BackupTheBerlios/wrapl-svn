#include <Gtk/Gtk/CheckMenuItem.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Std/Boolean.h>
#include <Gtk/Gtk/CheckMenuItem.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$MenuItem$T, Gtk$Gtk$Item$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkCheckMenuItem * result = gtk_check_menu_item_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithLabel, 1) {
	char *label = Std$String$flatten(Args[0].Val);
	GtkCheckMenuItem * result = gtk_check_menu_item_new_with_label(label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithMnemonic, 1) {
	char *label = Std$String$flatten(Args[0].Val);
	GtkCheckMenuItem * result = gtk_check_menu_item_new_with_mnemonic(label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_check_menu_item_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetActive", TYP, T) {
	GtkCheckMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_check_menu_item_get_active(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetDrawAsRadio", TYP, T) {
	GtkCheckMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_check_menu_item_get_draw_as_radio(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetInconsistent", TYP, T) {
	GtkCheckMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_check_menu_item_get_inconsistent(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetActive", TYP, T, TYP, Std$Symbol$T) {
	GtkCheckMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int is_active = Args[1].Val == $true;
	gtk_check_menu_item_set_active(self, is_active);
	return SUCCESS;
};

METHOD("SetDrawAsRadio", TYP, T, TYP, Std$Symbol$T) {
	GtkCheckMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int draw_as_radio = Args[1].Val == $true;
	gtk_check_menu_item_set_draw_as_radio(self, draw_as_radio);
	return SUCCESS;
};

METHOD("SetInconsistent", TYP, T, TYP, Std$Symbol$T) {
	GtkCheckMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_check_menu_item_set_inconsistent(self, setting);
	return SUCCESS;
};

METHOD("SetShowToggle", TYP, T, TYP, Std$Symbol$T) {
	GtkCheckMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int always = Args[1].Val == $true;
	gtk_check_menu_item_set_show_toggle(self, always);
	return SUCCESS;
};

METHOD("Toggled", TYP, T) {
	GtkCheckMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_check_menu_item_toggled(self);
	return SUCCESS;
};

