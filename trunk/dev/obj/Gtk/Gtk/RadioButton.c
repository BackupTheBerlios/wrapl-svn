#include <Gtk/Gtk/RadioButton.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/RadioButton.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$CheckButton$T, Gtk$Gtk$ToggleButton$T, Gtk$Gtk$Button$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	GSList* group = 0;
	GtkRadioButton * result = gtk_radio_button_new(group);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromWidget, 1) {
	GtkRadioButton * group = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkRadioButton * result = gtk_radio_button_new_from_widget(group);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithLabel, 2) {
	GSList* group = 0;
	char *label = Std$String$flatten(Args[1].Val);
	GtkRadioButton * result = gtk_radio_button_new_with_label(group, label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithLabelFromWidget, 2) {
	GtkRadioButton * group = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *label = Std$String$flatten(Args[1].Val);
	GtkRadioButton * result = gtk_radio_button_new_with_label_from_widget(group, label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithMnemonic, 2) {
	GSList* group = 0;
	char *label = Std$String$flatten(Args[1].Val);
	GtkRadioButton * result = gtk_radio_button_new_with_mnemonic(group, label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithMnemonicFromWidget, 2) {
	GtkRadioButton * group = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *label = Std$String$flatten(Args[1].Val);
	GtkRadioButton * result = gtk_radio_button_new_with_mnemonic_from_widget(group, label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_radio_button_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetGroup", TYP, T) {
	GtkRadioButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* result = gtk_radio_button_get_group(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("SetGroup", TYP, T, TYP, Std$Object$T) {
	GtkRadioButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* group = 0;
	gtk_radio_button_set_group(self, group);
	return SUCCESS;
};

