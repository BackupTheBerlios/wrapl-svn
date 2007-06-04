#include <Gtk/Gtk/SeparatorToolItem.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/SeparatorToolItem.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$ToolItem$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkSeparatorToolItem * result = gtk_separator_tool_item_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_separator_tool_item_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetDraw", TYP, T) {
	GtkSeparatorToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_separator_tool_item_get_draw(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetDraw", TYP, T, TYP, Std$Symbol$T) {
	GtkSeparatorToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int draw = Args[1].Val == $true;
	gtk_separator_tool_item_set_draw(self, draw);
	return SUCCESS;
};

