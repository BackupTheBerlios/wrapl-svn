#include <Gtk/Gtk/ToggleAction.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/ToggleAction.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Action$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 4) {
	char *name = Std$String$flatten(Args[0].Val);
	char *label = Std$String$flatten(Args[1].Val);
	char *tooltip = Std$String$flatten(Args[2].Val);
	char *stock_id = Std$String$flatten(Args[3].Val);
	GtkToggleAction * result = gtk_toggle_action_new(name, label, tooltip, stock_id);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_toggle_action_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetActive", TYP, T) {
	GtkToggleAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_toggle_action_get_active(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetDrawAsRadio", TYP, T) {
	GtkToggleAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_toggle_action_get_draw_as_radio(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetActive", TYP, T, TYP, Std$Symbol$T) {
	GtkToggleAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int is_active = Args[1].Val == $true;
	gtk_toggle_action_set_active(self, is_active);
	return SUCCESS;
};

METHOD("SetDrawAsRadio", TYP, T, TYP, Std$Symbol$T) {
	GtkToggleAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int draw_as_radio = Args[1].Val == $true;
	gtk_toggle_action_set_draw_as_radio(self, draw_as_radio);
	return SUCCESS;
};

METHOD("Toggled", TYP, T) {
	GtkToggleAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_toggle_action_toggled(self);
	return SUCCESS;
};

