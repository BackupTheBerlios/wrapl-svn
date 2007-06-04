#include <Gtk/Gtk/RadioAction.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/RadioAction.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$ToggleAction$T, Gtk$Gtk$Action$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 5) {
	char *name = Std$String$flatten(Args[0].Val);
	char *label = Std$String$flatten(Args[1].Val);
	char *tooltip = Std$String$flatten(Args[2].Val);
	char *stock_id = Std$String$flatten(Args[3].Val);
	int value = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GtkRadioAction * result = gtk_radio_action_new(name, label, tooltip, stock_id, value);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_radio_action_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetCurrentValue", TYP, T) {
	GtkRadioAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_radio_action_get_current_value(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetGroup", TYP, T) {
	GtkRadioAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* result = gtk_radio_action_get_group(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("SetCurrentValue", TYP, T, TYP, Std$Integer$SmallT) {
	GtkRadioAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int current_value = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_radio_action_set_current_value(self, current_value);
	return SUCCESS;
};

METHOD("SetGroup", TYP, T, TYP, Std$Object$T) {
	GtkRadioAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* group = 0;
	gtk_radio_action_set_group(self, group);
	return SUCCESS;
};

