#include <Gtk/Gtk/ToolItem.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 10
#include <Std/Boolean.h>
#include <Gtk/Gtk/ReliefStyle.h>
#include <Gtk/Gtk/ToolItem.h>
#include <Gtk/Gtk/Tooltips.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/IconSize.h>
#include <Gtk/Gtk/Orientation.h>
#include <Gtk/Gtk/ToolbarStyle.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
/***********************************/
TYPE(T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkToolItem * result = gtk_tool_item_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tool_item_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetExpand", TYP, T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tool_item_get_expand(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetHomogeneous", TYP, T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tool_item_get_homogeneous(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetIconSize", TYP, T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkIconSize result = gtk_tool_item_get_icon_size(self);
	Gtk$Gtk$IconSize_t *_result = new(Gtk$Gtk$IconSize_t);
	_result->Type = Gtk$Gtk$IconSize$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetIsImportant", TYP, T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tool_item_get_is_important(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetOrientation", TYP, T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkOrientation result = gtk_tool_item_get_orientation(self);
	Gtk$Gtk$Orientation_t *_result = new(Gtk$Gtk$Orientation_t);
	_result->Type = Gtk$Gtk$Orientation$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetProxyMenuItem", TYP, T, TYP, Std$String$T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *menu_item_id = Std$String$flatten(Args[1].Val);
	GtkWidget * result = gtk_tool_item_get_proxy_menu_item(self, menu_item_id);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetReliefStyle", TYP, T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkReliefStyle result = gtk_tool_item_get_relief_style(self);
	Gtk$Gtk$ReliefStyle_t *_result = new(Gtk$Gtk$ReliefStyle_t);
	_result->Type = Gtk$Gtk$ReliefStyle$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetToolbarStyle", TYP, T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkToolbarStyle result = gtk_tool_item_get_toolbar_style(self);
	Gtk$Gtk$ToolbarStyle_t *_result = new(Gtk$Gtk$ToolbarStyle_t);
	_result->Type = Gtk$Gtk$ToolbarStyle$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetUseDragWindow", TYP, T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tool_item_get_use_drag_window(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetVisibleHorizontal", TYP, T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tool_item_get_visible_horizontal(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetVisibleVertical", TYP, T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tool_item_get_visible_vertical(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("RebuildMenu", TYP, T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tool_item_rebuild_menu(self);
	return SUCCESS;
};

METHOD("RetrieveProxyMenuItem", TYP, T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_tool_item_retrieve_proxy_menu_item(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("SetExpand", TYP, T, TYP, Std$Symbol$T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int expand = Args[1].Val == $true;
	gtk_tool_item_set_expand(self, expand);
	return SUCCESS;
};

METHOD("SetHomogeneous", TYP, T, TYP, Std$Symbol$T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int homogeneous = Args[1].Val == $true;
	gtk_tool_item_set_homogeneous(self, homogeneous);
	return SUCCESS;
};

METHOD("SetIsImportant", TYP, T, TYP, Std$Symbol$T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int is_important = Args[1].Val == $true;
	gtk_tool_item_set_is_important(self, is_important);
	return SUCCESS;
};

METHOD("SetProxyMenuItem", TYP, T, TYP, Std$String$T, TYP, Gtk$Gtk$Widget$T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *menu_item_id = Std$String$flatten(Args[1].Val);
	GtkWidget * menu_item = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_tool_item_set_proxy_menu_item(self, menu_item_id, menu_item);
	return SUCCESS;
};

METHOD("SetTooltip", TYP, T, TYP, Gtk$Gtk$Tooltips$T, TYP, Std$String$T, TYP, Std$String$T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTooltips * tooltips = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *tip_text = Std$String$flatten(Args[2].Val);
	char *tip_private = Std$String$flatten(Args[3].Val);
	gtk_tool_item_set_tooltip(self, tooltips, tip_text, tip_private);
	return SUCCESS;
};

METHOD("SetUseDragWindow", TYP, T, TYP, Std$Symbol$T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int use_drag_window = Args[1].Val == $true;
	gtk_tool_item_set_use_drag_window(self, use_drag_window);
	return SUCCESS;
};

METHOD("SetVisibleHorizontal", TYP, T, TYP, Std$Symbol$T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int visible_horizontal = Args[1].Val == $true;
	gtk_tool_item_set_visible_horizontal(self, visible_horizontal);
	return SUCCESS;
};

METHOD("SetVisibleVertical", TYP, T, TYP, Std$Symbol$T) {
	GtkToolItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int visible_vertical = Args[1].Val == $true;
	gtk_tool_item_set_visible_vertical(self, visible_vertical);
	return SUCCESS;
};

