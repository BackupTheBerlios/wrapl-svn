#include <Gtk/Gtk/UIManager.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 8
#include <Std/Boolean.h>
#include <Gtk/Gtk/UIManager.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/ActionGroup.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/AccelGroup.h>
#include <Gtk/Gtk/Action.h>
#include <Gtk/Gtk/Widget.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkUIManager * result = gtk_ui_manager_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewMergeId, 1) {
	GtkUIManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkUIManager * result = gtk_ui_manager_new_merge_id(self);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_ui_manager_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddUi", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$Symbol$T) {
	GtkUIManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int merge_id = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *path = Std$String$flatten(Args[2].Val);
	char *name = Std$String$flatten(Args[3].Val);
	char *action = Std$String$flatten(Args[4].Val);
	int type = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int top = Args[6].Val == $true;
	gtk_ui_manager_add_ui(self, merge_id, path, name, action, type, top);
	return SUCCESS;
};

METHOD("AddUiFromFile", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkUIManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *filename = Std$String$flatten(Args[1].Val);
	GError** error = 0;
	int result = gtk_ui_manager_add_ui_from_file(self, filename, error);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("AddUiFromString", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkUIManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *buffer = Std$String$flatten(Args[1].Val);
	int length = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GError** error = 0;
	int result = gtk_ui_manager_add_ui_from_string(self, buffer, length, error);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("EnsureUpdate", TYP, T) {
	GtkUIManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_ui_manager_ensure_update(self);
	return SUCCESS;
};

METHOD("GetAccelGroup", TYP, T) {
	GtkUIManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAccelGroup * result = gtk_ui_manager_get_accel_group(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetAction", TYP, T, TYP, Std$String$T) {
	GtkUIManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *path = Std$String$flatten(Args[1].Val);
	GtkAction * result = gtk_ui_manager_get_action(self, path);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetActionGroups", TYP, T) {
	GtkUIManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* result = gtk_ui_manager_get_action_groups(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetAddTearoffs", TYP, T) {
	GtkUIManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_ui_manager_get_add_tearoffs(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetToplevels", TYP, T, TYP, Std$Integer$SmallT) {
	GtkUIManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int types = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GSList* result = gtk_ui_manager_get_toplevels(self, types);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetUi", TYP, T) {
	GtkUIManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char * result = gtk_ui_manager_get_ui(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetWidget", TYP, T, TYP, Std$String$T) {
	GtkUIManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *path = Std$String$flatten(Args[1].Val);
	GtkWidget * result = gtk_ui_manager_get_widget(self, path);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("InsertActionGroup", TYP, T, TYP, Gtk$Gtk$ActionGroup$T, TYP, Std$Integer$SmallT) {
	GtkUIManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkActionGroup * action_group = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int pos = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_ui_manager_insert_action_group(self, action_group, pos);
	return SUCCESS;
};

METHOD("RemoveActionGroup", TYP, T, TYP, Gtk$Gtk$ActionGroup$T) {
	GtkUIManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkActionGroup * action_group = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_ui_manager_remove_action_group(self, action_group);
	return SUCCESS;
};

METHOD("RemoveUi", TYP, T, TYP, Std$Integer$SmallT) {
	GtkUIManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int merge_id = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_ui_manager_remove_ui(self, merge_id);
	return SUCCESS;
};

METHOD("SetAddTearoffs", TYP, T, TYP, Std$Symbol$T) {
	GtkUIManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int add_tearoffs = Args[1].Val == $true;
	gtk_ui_manager_set_add_tearoffs(self, add_tearoffs);
	return SUCCESS;
};

