#include <Gtk/Gtk/ToggleToolButton.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/ToggleToolButton.h>
#include <Gtk/GObject/Type.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$ToolButton$T, Gtk$Gtk$ToolItem$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkToggleToolButton * result = gtk_toggle_tool_button_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromStock, 1) {
	char *stock_id = Std$String$flatten(Args[0].Val);
	GtkToggleToolButton * result = gtk_toggle_tool_button_new_from_stock(stock_id);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_toggle_tool_button_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetActive", TYP, T) {
	GtkToggleToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_toggle_tool_button_get_active(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetActive", TYP, T, TYP, Std$Symbol$T) {
	GtkToggleToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int is_active = Args[1].Val == $true;
	gtk_toggle_tool_button_set_active(self, is_active);
	return SUCCESS;
};

