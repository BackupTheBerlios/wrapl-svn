#include <Gtk/Gtk/ToggleButton.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/ToggleButton.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Button$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkToggleButton * result = gtk_toggle_button_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithLabel, 1) {
	char *label = Std$String$flatten(Args[0].Val);
	GtkToggleButton * result = gtk_toggle_button_new_with_label(label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithMnemonic, 1) {
	char *label = Std$String$flatten(Args[0].Val);
	GtkToggleButton * result = gtk_toggle_button_new_with_mnemonic(label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_toggle_button_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetActive", TYP, T) {
	GtkToggleButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_toggle_button_get_active(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetInconsistent", TYP, T) {
	GtkToggleButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_toggle_button_get_inconsistent(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetMode", TYP, T) {
	GtkToggleButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_toggle_button_get_mode(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetActive", TYP, T, TYP, Std$Symbol$T) {
	GtkToggleButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int is_active = Args[1].Val == $true;
	gtk_toggle_button_set_active(self, is_active);
	return SUCCESS;
};

METHOD("SetInconsistent", TYP, T, TYP, Std$Symbol$T) {
	GtkToggleButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_toggle_button_set_inconsistent(self, setting);
	return SUCCESS;
};

METHOD("SetMode", TYP, T, TYP, Std$Symbol$T) {
	GtkToggleButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int draw_indicator = Args[1].Val == $true;
	gtk_toggle_button_set_mode(self, draw_indicator);
	return SUCCESS;
};

METHOD("Toggled", TYP, T) {
	GtkToggleButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_toggle_button_toggled(self);
	return SUCCESS;
};

