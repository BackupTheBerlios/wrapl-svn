#include <Gtk/Gtk/Action.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 8
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/IconSize.h>
#include <Gtk/GObject/Closure.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/AccelGroup.h>
#include <Gtk/Gtk/Action.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 4) {
	char *name = Std$String$flatten(Args[0].Val);
	char *label = Std$String$flatten(Args[1].Val);
	char *tooltip = Std$String$flatten(Args[2].Val);
	char *stock_id = Std$String$flatten(Args[3].Val);
	GtkAction * result = gtk_action_new(name, label, tooltip, stock_id);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_action_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Activate", TYP, T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_action_activate(self);
	return SUCCESS;
};

METHOD("BlockActivateFrom", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * proxy = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_action_block_activate_from(self, proxy);
	return SUCCESS;
};

METHOD("ConnectAccelerator", TYP, T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_action_connect_accelerator(self);
	return SUCCESS;
};

METHOD("ConnectProxy", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * proxy = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_action_connect_proxy(self, proxy);
	return SUCCESS;
};

METHOD("CreateIcon", TYP, T, TYP, Gtk$Gtk$IconSize$T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkIconSize icon_size = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkWidget * result = gtk_action_create_icon(self, icon_size);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("CreateMenuItem", TYP, T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_action_create_menu_item(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("CreateToolItem", TYP, T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_action_create_tool_item(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("DisconnectAccelerator", TYP, T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_action_disconnect_accelerator(self);
	return SUCCESS;
};

METHOD("DisconnectProxy", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * proxy = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_action_disconnect_proxy(self, proxy);
	return SUCCESS;
};

METHOD("GetAccelClosure", TYP, T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GClosure * result = gtk_action_get_accel_closure(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetAccelPath", TYP, T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_action_get_accel_path(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetName", TYP, T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_action_get_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetProxies", TYP, T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* result = gtk_action_get_proxies(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetSensitive", TYP, T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_action_get_sensitive(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetVisible", TYP, T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_action_get_visible(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsSensitive", TYP, T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_action_is_sensitive(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsVisible", TYP, T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_action_is_visible(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetAccelGroup", TYP, T, TYP, Gtk$Gtk$AccelGroup$T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAccelGroup * accel_group = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_action_set_accel_group(self, accel_group);
	return SUCCESS;
};

METHOD("SetAccelPath", TYP, T, TYP, Std$String$T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *accel_path = Std$String$flatten(Args[1].Val);
	gtk_action_set_accel_path(self, accel_path);
	return SUCCESS;
};

METHOD("SetSensitive", TYP, T, TYP, Std$Symbol$T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int sensitive = Args[1].Val == $true;
	gtk_action_set_sensitive(self, sensitive);
	return SUCCESS;
};

METHOD("SetVisible", TYP, T, TYP, Std$Symbol$T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int visible = Args[1].Val == $true;
	gtk_action_set_visible(self, visible);
	return SUCCESS;
};

METHOD("UnblockActivateFrom", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkAction * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * proxy = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_action_unblock_activate_from(self, proxy);
	return SUCCESS;
};

