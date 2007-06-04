#include <Gtk/Gtk/ToolButton.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/Gtk/ToolButton.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$ToolItem$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 2) {
	GtkWidget * icon_widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *label = Std$String$flatten(Args[1].Val);
	GtkToolButton * result = gtk_tool_button_new(icon_widget, label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromStock, 1) {
	char *stock_id = Std$String$flatten(Args[0].Val);
	GtkToolButton * result = gtk_tool_button_new_from_stock(stock_id);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tool_button_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetIconName", TYP, T) {
	GtkToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_tool_button_get_icon_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetIconWidget", TYP, T) {
	GtkToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_tool_button_get_icon_widget(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetLabel", TYP, T) {
	GtkToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_tool_button_get_label(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetLabelWidget", TYP, T) {
	GtkToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_tool_button_get_label_widget(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetStockId", TYP, T) {
	GtkToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_tool_button_get_stock_id(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetUseUnderline", TYP, T) {
	GtkToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tool_button_get_use_underline(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetIconName", TYP, T, TYP, Std$String$T) {
	GtkToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *icon_name = Std$String$flatten(Args[1].Val);
	gtk_tool_button_set_icon_name(self, icon_name);
	return SUCCESS;
};

METHOD("SetIconWidget", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * icon_widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_tool_button_set_icon_widget(self, icon_widget);
	return SUCCESS;
};

METHOD("SetLabel", TYP, T, TYP, Std$String$T) {
	GtkToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *label = Std$String$flatten(Args[1].Val);
	gtk_tool_button_set_label(self, label);
	return SUCCESS;
};

METHOD("SetLabelWidget", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * label_widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_tool_button_set_label_widget(self, label_widget);
	return SUCCESS;
};

METHOD("SetStockId", TYP, T, TYP, Std$String$T) {
	GtkToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *stock_id = Std$String$flatten(Args[1].Val);
	gtk_tool_button_set_stock_id(self, stock_id);
	return SUCCESS;
};

METHOD("SetUseUnderline", TYP, T, TYP, Std$Symbol$T) {
	GtkToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int use_underline = Args[1].Val == $true;
	gtk_tool_button_set_use_underline(self, use_underline);
	return SUCCESS;
};

