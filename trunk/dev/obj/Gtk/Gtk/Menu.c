#include <Gtk/Gtk/Menu.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 9
#include <Gtk/Gtk/MenuDetachFunc.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/MenuPositionFunc.h>
#include <Gtk/Gtk/AccelGroup.h>
#include <Gtk/Gdk/Screen.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/Menu.h>
/***********************************/
TYPE(T, Gtk$Gtk$MenuShell$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkMenu * result = gtk_menu_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetForAttachWidget, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* result = gtk_menu_get_for_attach_widget(widget);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_menu_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Attach", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int left_attach = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int right_attach = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int top_attach = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int bottom_attach = ((Std$Integer_smallt *)Args[5].Val)->Value;
	gtk_menu_attach(self, child, left_attach, right_attach, top_attach, bottom_attach);
	return SUCCESS;
};

METHOD("AttachToWidget", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Function$T) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * attach_widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkMenuDetachFunc detacher = Gtk$Gtk$MenuDetachFunc$new(Args[2].Val);
	gtk_menu_attach_to_widget(self, attach_widget, detacher);
	return SUCCESS;
};

METHOD("Detach", TYP, T) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_menu_detach(self);
	return SUCCESS;
};

METHOD("GetAccelGroup", TYP, T) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAccelGroup * result = gtk_menu_get_accel_group(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetActive", TYP, T) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_menu_get_active(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetAttachWidget", TYP, T) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_menu_get_attach_widget(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetTearoffState", TYP, T) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_menu_get_tearoff_state(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetTitle", TYP, T) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_menu_get_title(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("Popdown", TYP, T) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_menu_popdown(self);
	return SUCCESS;
};

METHOD("Popup", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * parent_menu_shell = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkWidget * parent_menu_item = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	GtkMenuPositionFunc func = Gtk$Gtk$MenuPositionFunc$new(Args[3].Val);
	void *data = ((Std$Address_t *)Args[4].Val)->Value;
	int button = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int activate_time = ((Std$Integer_smallt *)Args[6].Val)->Value;
	gtk_menu_popup(self, parent_menu_shell, parent_menu_item, func, data, button, activate_time);
	return SUCCESS;
};

METHOD("ReorderChild", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_menu_reorder_child(self, child, position);
	return SUCCESS;
};

METHOD("Reposition", TYP, T) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_menu_reposition(self);
	return SUCCESS;
};

METHOD("SetAccelGroup", TYP, T, TYP, Gtk$Gtk$AccelGroup$T) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAccelGroup * accel_group = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_menu_set_accel_group(self, accel_group);
	return SUCCESS;
};

METHOD("SetAccelPath", TYP, T, TYP, Std$String$T) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *accel_path = Std$String$flatten(Args[1].Val);
	gtk_menu_set_accel_path(self, accel_path);
	return SUCCESS;
};

METHOD("SetActive", TYP, T, TYP, Std$Integer$SmallT) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int index_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_menu_set_active(self, index_);
	return SUCCESS;
};

METHOD("SetMonitor", TYP, T, TYP, Std$Integer$SmallT) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int monitor_num = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_menu_set_monitor(self, monitor_num);
	return SUCCESS;
};

METHOD("SetScreen", TYP, T, TYP, Gtk$Gdk$Screen$T) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_menu_set_screen(self, screen);
	return SUCCESS;
};

METHOD("SetTearoffState", TYP, T, TYP, Std$Symbol$T) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int torn_off = Args[1].Val == $true;
	gtk_menu_set_tearoff_state(self, torn_off);
	return SUCCESS;
};

METHOD("SetTitle", TYP, T, TYP, Std$String$T) {
	GtkMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *title = Std$String$flatten(Args[1].Val);
	gtk_menu_set_title(self, title);
	return SUCCESS;
};

