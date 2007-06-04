#include <Gtk/Gtk/MenuToolButton.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/Gtk/Tooltips.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
#include <Gtk/Gtk/MenuToolButton.h>
/***********************************/
TYPE(T, Gtk$Gtk$ToolButton$T, Gtk$Gtk$ToolItem$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 2) {
	GtkWidget * icon_widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *label = Std$String$flatten(Args[1].Val);
	GtkMenuToolButton * result = gtk_menu_tool_button_new(icon_widget, label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromStock, 1) {
	char *stock_id = Std$String$flatten(Args[0].Val);
	GtkMenuToolButton * result = gtk_menu_tool_button_new_from_stock(stock_id);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_menu_tool_button_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetMenu", TYP, T) {
	GtkMenuToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_menu_tool_button_get_menu(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("SetArrowTooltip", TYP, T, TYP, Gtk$Gtk$Tooltips$T, TYP, Std$String$T, TYP, Std$String$T) {
	GtkMenuToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTooltips * tooltips = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *tip_text = Std$String$flatten(Args[2].Val);
	char *tip_private = Std$String$flatten(Args[3].Val);
	gtk_menu_tool_button_set_arrow_tooltip(self, tooltips, tip_text, tip_private);
	return SUCCESS;
};

METHOD("SetMenu", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkMenuToolButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * menu = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_menu_tool_button_set_menu(self, menu);
	return SUCCESS;
};

