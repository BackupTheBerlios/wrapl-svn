#include <Gtk/Gtk/Combo.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/Gtk/Item.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/Combo.h>
#include <Gtk/GObject/Type.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$HBox$T, Gtk$Gtk$Box$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkCombo * result = gtk_combo_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_combo_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("DisableActivate", TYP, T) {
	GtkCombo * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_combo_disable_activate(self);
	return SUCCESS;
};

METHOD("SetCaseSensitive", TYP, T, TYP, Std$Symbol$T) {
	GtkCombo * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int val = Args[1].Val == $true;
	gtk_combo_set_case_sensitive(self, val);
	return SUCCESS;
};

METHOD("SetItemString", TYP, T, TYP, Gtk$Gtk$Item$T, TYP, Std$String$T) {
	GtkCombo * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkItem * item = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *item_value = Std$String$flatten(Args[2].Val);
	gtk_combo_set_item_string(self, item, item_value);
	return SUCCESS;
};

METHOD("SetPopdownStrings", TYP, T, TYP, Std$Object$T) {
	GtkCombo * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* strings = 0;
	gtk_combo_set_popdown_strings(self, strings);
	return SUCCESS;
};

METHOD("SetUseArrows", TYP, T, TYP, Std$Symbol$T) {
	GtkCombo * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int val = Args[1].Val == $true;
	gtk_combo_set_use_arrows(self, val);
	return SUCCESS;
};

METHOD("SetUseArrowsAlways", TYP, T, TYP, Std$Symbol$T) {
	GtkCombo * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int val = Args[1].Val == $true;
	gtk_combo_set_use_arrows_always(self, val);
	return SUCCESS;
};

METHOD("SetValueInList", TYP, T, TYP, Std$Symbol$T, TYP, Std$Symbol$T) {
	GtkCombo * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int val = Args[1].Val == $true;
	int ok_if_empty = Args[2].Val == $true;
	gtk_combo_set_value_in_list(self, val, ok_if_empty);
	return SUCCESS;
};

