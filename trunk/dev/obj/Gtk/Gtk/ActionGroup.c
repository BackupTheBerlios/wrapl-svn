#include <Gtk/Gtk/ActionGroup.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 10
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/ToggleActionEntry.h>
#include <Gtk/Gtk/ActionGroup.h>
#include <Gtk/Gtk/ActionEntry.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/DestroyNotify.h>
#include <Gtk/Gtk/RadioActionEntry.h>
#include <Gtk/Gtk/Action.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/TranslateFunc.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	char *name = Std$String$flatten(Args[0].Val);
	GtkActionGroup * result = gtk_action_group_new(name);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_action_group_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddAction", TYP, T, TYP, Gtk$Gtk$Action$T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAction * action = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_action_group_add_action(self, action);
	return SUCCESS;
};

METHOD("AddActionWithAccel", TYP, T, TYP, Gtk$Gtk$Action$T, TYP, Std$String$T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAction * action = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *accelerator = Std$String$flatten(Args[2].Val);
	gtk_action_group_add_action_with_accel(self, action, accelerator);
	return SUCCESS;
};

METHOD("AddActions", TYP, T, TYP, Gtk$Gtk$ActionEntry$T, TYP, Std$Integer$SmallT, TYP, Std$Address$T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkActionEntry * entries= &((Gtk$Gtk$ActionEntry_t *)Args[1].Val)->Value;
	int n_entries = ((Std$Integer_smallt *)Args[2].Val)->Value;
	void *user_data = ((Std$Address_t *)Args[3].Val)->Value;
	gtk_action_group_add_actions(self, entries, n_entries, user_data);
	return SUCCESS;
};

METHOD("AddActionsFull", TYP, T, TYP, Gtk$Gtk$ActionEntry$T, TYP, Std$Integer$SmallT, TYP, Std$Address$T, TYP, Std$Object$T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkActionEntry * entries= &((Gtk$Gtk$ActionEntry_t *)Args[1].Val)->Value;
	int n_entries = ((Std$Integer_smallt *)Args[2].Val)->Value;
	void *user_data = ((Std$Address_t *)Args[3].Val)->Value;
	GDestroyNotify destroy = 0;
	gtk_action_group_add_actions_full(self, entries, n_entries, user_data, destroy);
	return SUCCESS;
};

METHOD("AddRadioActions", TYP, T, TYP, Gtk$Gtk$RadioActionEntry$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Address$T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkRadioActionEntry * entries= &((Gtk$Gtk$RadioActionEntry_t *)Args[1].Val)->Value;
	int n_entries = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int value = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GCallback on_change = 0;
	void *user_data = ((Std$Address_t *)Args[5].Val)->Value;
	gtk_action_group_add_radio_actions(self, entries, n_entries, value, on_change, user_data);
	return SUCCESS;
};

METHOD("AddRadioActionsFull", TYP, T, TYP, Gtk$Gtk$RadioActionEntry$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Address$T, TYP, Std$Object$T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkRadioActionEntry * entries= &((Gtk$Gtk$RadioActionEntry_t *)Args[1].Val)->Value;
	int n_entries = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int value = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GCallback on_change = 0;
	void *user_data = ((Std$Address_t *)Args[5].Val)->Value;
	GDestroyNotify destroy = 0;
	gtk_action_group_add_radio_actions_full(self, entries, n_entries, value, on_change, user_data, destroy);
	return SUCCESS;
};

METHOD("AddToggleActions", TYP, T, TYP, Gtk$Gtk$ToggleActionEntry$T, TYP, Std$Integer$SmallT, TYP, Std$Address$T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkToggleActionEntry * entries= &((Gtk$Gtk$ToggleActionEntry_t *)Args[1].Val)->Value;
	int n_entries = ((Std$Integer_smallt *)Args[2].Val)->Value;
	void *user_data = ((Std$Address_t *)Args[3].Val)->Value;
	gtk_action_group_add_toggle_actions(self, entries, n_entries, user_data);
	return SUCCESS;
};

METHOD("AddToggleActionsFull", TYP, T, TYP, Gtk$Gtk$ToggleActionEntry$T, TYP, Std$Integer$SmallT, TYP, Std$Address$T, TYP, Std$Object$T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkToggleActionEntry * entries= &((Gtk$Gtk$ToggleActionEntry_t *)Args[1].Val)->Value;
	int n_entries = ((Std$Integer_smallt *)Args[2].Val)->Value;
	void *user_data = ((Std$Address_t *)Args[3].Val)->Value;
	GDestroyNotify destroy = 0;
	gtk_action_group_add_toggle_actions_full(self, entries, n_entries, user_data, destroy);
	return SUCCESS;
};

METHOD("GetAction", TYP, T, TYP, Std$String$T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *action_name = Std$String$flatten(Args[1].Val);
	GtkAction * result = gtk_action_group_get_action(self, action_name);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetName", TYP, T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_action_group_get_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetSensitive", TYP, T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_action_group_get_sensitive(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetVisible", TYP, T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_action_group_get_visible(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ListActions", TYP, T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList * result = gtk_action_group_list_actions(self);
	if (result) {
		int _length = 1;
		GList *node = result;
		node->data = Gtk$GObject$Object$to_riva(node->data);
		while (node->next) {
			node = node->next;
			node->data = Gtk$GObject$Object$to_riva(node->data);
			_length++;
		};
		Std$List_t *list = new(Std$List_t);
		list->Type = Std$List$T;
		list->Cache = list->Head = result;
		list->Tail = node;
		list->Length = _length;
		list->Index = 1;
		list->Access = 4;
		Result->Val = list;
	} else {
		Result->Val = Std$List$new(0);
	};
	return SUCCESS;
};

METHOD("RemoveAction", TYP, T, TYP, Gtk$Gtk$Action$T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAction * action = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_action_group_remove_action(self, action);
	return SUCCESS;
};

METHOD("SetSensitive", TYP, T, TYP, Std$Symbol$T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int sensitive = Args[1].Val == $true;
	gtk_action_group_set_sensitive(self, sensitive);
	return SUCCESS;
};

METHOD("SetTranslateFunc", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTranslateFunc func = Gtk$Gtk$TranslateFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkDestroyNotify notify = Gtk$Gtk$DestroyNotify$new(Args[3].Val);
	gtk_action_group_set_translate_func(self, func, data, notify);
	return SUCCESS;
};

METHOD("SetTranslationDomain", TYP, T, TYP, Std$String$T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *domain = Std$String$flatten(Args[1].Val);
	gtk_action_group_set_translation_domain(self, domain);
	return SUCCESS;
};

METHOD("SetVisible", TYP, T, TYP, Std$Symbol$T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int visible = Args[1].Val == $true;
	gtk_action_group_set_visible(self, visible);
	return SUCCESS;
};

METHOD("TranslateString", TYP, T, TYP, Std$String$T) {
	GtkActionGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *string = Std$String$flatten(Args[1].Val);
	const char * result = gtk_action_group_translate_string(self, string);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

