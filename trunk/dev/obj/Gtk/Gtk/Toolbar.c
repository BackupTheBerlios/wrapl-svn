#include <Gtk/Gtk/Toolbar.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 12
#include <Std/Boolean.h>
#include <Gtk/Gtk/ReliefStyle.h>
#include <Gtk/Gtk/Toolbar.h>
#include <Gtk/Gtk/SignalFunc.h>
#include <Gtk/Gtk/ToolbarChildType.h>
#include <Gtk/Gtk/ToolItem.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/IconSize.h>
#include <Gtk/Gtk/Orientation.h>
#include <Gtk/Gtk/ToolbarStyle.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
/***********************************/
TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkToolbar * result = gtk_toolbar_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_toolbar_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AppendElement", TYP, T, TYP, Gtk$Gtk$ToolbarChildType$T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$String$T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkToolbarChildType type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	char *text = Std$String$flatten(Args[3].Val);
	char *tooltip_text = Std$String$flatten(Args[4].Val);
	char *tooltip_private_text = Std$String$flatten(Args[5].Val);
	GtkWidget * icon = ((Gtk$GObject$Object_t *)Args[6].Val)->Handle;
	GtkSignalFunc callback = Gtk$Gtk$SignalFunc$new(Args[7].Val);
	void *user_data = ((Std$Address_t *)Args[8].Val)->Value;
	GtkWidget * result = gtk_toolbar_append_element(self, type, widget, text, tooltip_text, tooltip_private_text, icon, callback, user_data);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("AppendItem", TYP, T, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$String$T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	char *tooltip_text = Std$String$flatten(Args[2].Val);
	char *tooltip_private_text = Std$String$flatten(Args[3].Val);
	GtkWidget * icon = ((Gtk$GObject$Object_t *)Args[4].Val)->Handle;
	GtkSignalFunc callback = Gtk$Gtk$SignalFunc$new(Args[5].Val);
	void *user_data = ((Std$Address_t *)Args[6].Val)->Value;
	GtkWidget * result = gtk_toolbar_append_item(self, text, tooltip_text, tooltip_private_text, icon, callback, user_data);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("AppendSpace", TYP, T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_toolbar_append_space(self);
	return SUCCESS;
};

METHOD("AppendWidget", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T, TYP, Std$String$T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *tooltip_text = Std$String$flatten(Args[2].Val);
	char *tooltip_private_text = Std$String$flatten(Args[3].Val);
	gtk_toolbar_append_widget(self, widget, tooltip_text, tooltip_private_text);
	return SUCCESS;
};

METHOD("GetDropIndex", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gtk_toolbar_get_drop_index(self, x, y);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetIconSize", TYP, T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkIconSize result = gtk_toolbar_get_icon_size(self);
	Gtk$Gtk$IconSize_t *_result = new(Gtk$Gtk$IconSize_t);
	_result->Type = Gtk$Gtk$IconSize$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetItemIndex", TYP, T, TYP, Gtk$Gtk$ToolItem$T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkToolItem * item = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_toolbar_get_item_index(self, item);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetNItems", TYP, T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_toolbar_get_n_items(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetNthItem", TYP, T, TYP, Std$Integer$SmallT) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int n = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkToolItem * result = gtk_toolbar_get_nth_item(self, n);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetOrientation", TYP, T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkOrientation result = gtk_toolbar_get_orientation(self);
	Gtk$Gtk$Orientation_t *_result = new(Gtk$Gtk$Orientation_t);
	_result->Type = Gtk$Gtk$Orientation$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetReliefStyle", TYP, T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkReliefStyle result = gtk_toolbar_get_relief_style(self);
	Gtk$Gtk$ReliefStyle_t *_result = new(Gtk$Gtk$ReliefStyle_t);
	_result->Type = Gtk$Gtk$ReliefStyle$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetShowArrow", TYP, T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_toolbar_get_show_arrow(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetStyle", TYP, T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkToolbarStyle result = gtk_toolbar_get_style(self);
	Gtk$Gtk$ToolbarStyle_t *_result = new(Gtk$Gtk$ToolbarStyle_t);
	_result->Type = Gtk$Gtk$ToolbarStyle$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetTooltips", TYP, T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_toolbar_get_tooltips(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Insert", TYP, T, TYP, Gtk$Gtk$ToolItem$T, TYP, Std$Integer$SmallT) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkToolItem * item = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int pos = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_toolbar_insert(self, item, pos);
	return SUCCESS;
};

METHOD("InsertElement", TYP, T, TYP, Gtk$Gtk$ToolbarChildType$T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$String$T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Integer$SmallT) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkToolbarChildType type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	char *text = Std$String$flatten(Args[3].Val);
	char *tooltip_text = Std$String$flatten(Args[4].Val);
	char *tooltip_private_text = Std$String$flatten(Args[5].Val);
	GtkWidget * icon = ((Gtk$GObject$Object_t *)Args[6].Val)->Handle;
	GtkSignalFunc callback = Gtk$Gtk$SignalFunc$new(Args[7].Val);
	void *user_data = ((Std$Address_t *)Args[8].Val)->Value;
	int position = ((Std$Integer_smallt *)Args[9].Val)->Value;
	GtkWidget * result = gtk_toolbar_insert_element(self, type, widget, text, tooltip_text, tooltip_private_text, icon, callback, user_data, position);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("InsertItem", TYP, T, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$String$T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Integer$SmallT) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	char *tooltip_text = Std$String$flatten(Args[2].Val);
	char *tooltip_private_text = Std$String$flatten(Args[3].Val);
	GtkWidget * icon = ((Gtk$GObject$Object_t *)Args[4].Val)->Handle;
	GtkSignalFunc callback = Gtk$Gtk$SignalFunc$new(Args[5].Val);
	void *user_data = ((Std$Address_t *)Args[6].Val)->Value;
	int position = ((Std$Integer_smallt *)Args[7].Val)->Value;
	GtkWidget * result = gtk_toolbar_insert_item(self, text, tooltip_text, tooltip_private_text, icon, callback, user_data, position);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("InsertSpace", TYP, T, TYP, Std$Integer$SmallT) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_toolbar_insert_space(self, position);
	return SUCCESS;
};

METHOD("InsertStock", TYP, T, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Integer$SmallT) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *stock_id = Std$String$flatten(Args[1].Val);
	char *tooltip_text = Std$String$flatten(Args[2].Val);
	char *tooltip_private_text = Std$String$flatten(Args[3].Val);
	GtkSignalFunc callback = Gtk$Gtk$SignalFunc$new(Args[4].Val);
	void *user_data = ((Std$Address_t *)Args[5].Val)->Value;
	int position = ((Std$Integer_smallt *)Args[6].Val)->Value;
	GtkWidget * result = gtk_toolbar_insert_stock(self, stock_id, tooltip_text, tooltip_private_text, callback, user_data, position);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("InsertWidget", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *tooltip_text = Std$String$flatten(Args[2].Val);
	char *tooltip_private_text = Std$String$flatten(Args[3].Val);
	int position = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_toolbar_insert_widget(self, widget, tooltip_text, tooltip_private_text, position);
	return SUCCESS;
};

METHOD("PrependElement", TYP, T, TYP, Gtk$Gtk$ToolbarChildType$T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$String$T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkToolbarChildType type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	char *text = Std$String$flatten(Args[3].Val);
	char *tooltip_text = Std$String$flatten(Args[4].Val);
	char *tooltip_private_text = Std$String$flatten(Args[5].Val);
	GtkWidget * icon = ((Gtk$GObject$Object_t *)Args[6].Val)->Handle;
	GtkSignalFunc callback = Gtk$Gtk$SignalFunc$new(Args[7].Val);
	void *user_data = ((Std$Address_t *)Args[8].Val)->Value;
	GtkWidget * result = gtk_toolbar_prepend_element(self, type, widget, text, tooltip_text, tooltip_private_text, icon, callback, user_data);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("PrependItem", TYP, T, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$String$T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	char *tooltip_text = Std$String$flatten(Args[2].Val);
	char *tooltip_private_text = Std$String$flatten(Args[3].Val);
	GtkWidget * icon = ((Gtk$GObject$Object_t *)Args[4].Val)->Handle;
	GtkSignalFunc callback = Gtk$Gtk$SignalFunc$new(Args[5].Val);
	void *user_data = ((Std$Address_t *)Args[6].Val)->Value;
	GtkWidget * result = gtk_toolbar_prepend_item(self, text, tooltip_text, tooltip_private_text, icon, callback, user_data);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("PrependSpace", TYP, T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_toolbar_prepend_space(self);
	return SUCCESS;
};

METHOD("PrependWidget", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T, TYP, Std$String$T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *tooltip_text = Std$String$flatten(Args[2].Val);
	char *tooltip_private_text = Std$String$flatten(Args[3].Val);
	gtk_toolbar_prepend_widget(self, widget, tooltip_text, tooltip_private_text);
	return SUCCESS;
};

METHOD("RemoveSpace", TYP, T, TYP, Std$Integer$SmallT) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_toolbar_remove_space(self, position);
	return SUCCESS;
};

METHOD("SetDropHighlightItem", TYP, T, TYP, Gtk$Gtk$ToolItem$T, TYP, Std$Integer$SmallT) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkToolItem * tool_item = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int index_ = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_toolbar_set_drop_highlight_item(self, tool_item, index_);
	return SUCCESS;
};

METHOD("SetIconSize", TYP, T, TYP, Gtk$Gtk$IconSize$T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkIconSize icon_size = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_toolbar_set_icon_size(self, icon_size);
	return SUCCESS;
};

METHOD("SetOrientation", TYP, T, TYP, Gtk$Gtk$Orientation$T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkOrientation orientation = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_toolbar_set_orientation(self, orientation);
	return SUCCESS;
};

METHOD("SetShowArrow", TYP, T, TYP, Std$Symbol$T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int show_arrow = Args[1].Val == $true;
	gtk_toolbar_set_show_arrow(self, show_arrow);
	return SUCCESS;
};

METHOD("SetStyle", TYP, T, TYP, Gtk$Gtk$ToolbarStyle$T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkToolbarStyle style = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_toolbar_set_style(self, style);
	return SUCCESS;
};

METHOD("SetTooltips", TYP, T, TYP, Std$Symbol$T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int enable = Args[1].Val == $true;
	gtk_toolbar_set_tooltips(self, enable);
	return SUCCESS;
};

METHOD("UnsetIconSize", TYP, T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_toolbar_unset_icon_size(self);
	return SUCCESS;
};

METHOD("UnsetStyle", TYP, T) {
	GtkToolbar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_toolbar_unset_style(self);
	return SUCCESS;
};

