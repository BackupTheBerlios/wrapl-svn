#include <Gtk/Gtk/RadioToolButton.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gtk/RadioToolButton.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$ToggleToolButton$T, Gtk$Gtk$ToolButton$T, Gtk$Gtk$ToolItem$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	GSList* group = 0;
	GtkRadioToolButton * result = gtk_radio_tool_button_new(group);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromStock, 2) {
	GSList* group = 0;
	char *stock_id = Std$String$flatten(Args[1].Val);
	GtkRadioToolButton * result = gtk_radio_tool_button_new_from_stock(group, stock_id);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromWidget, 1) {
	GtkRadioToolButton * group = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkRadioToolButton * result = gtk_radio_tool_button_new_from_widget(group);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithStockFromWidget, 2) {
	GtkRadioToolButton * group = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *stock_id = Std$String$flatten(Args[1].Val);
	GtkRadioToolButton * result = gtk_radio_tool_button_new_with_stock_from_widget(group, stock_id);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_radio_tool_button_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetGroup", TYP, T) {
	GtkRadioToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* result = gtk_radio_tool_button_get_group(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("SetGroup", TYP, T, TYP, Std$Object$T) {
	GtkRadioToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* group = 0;
	gtk_radio_tool_button_set_group(self, group);
	return SUCCESS;
};

