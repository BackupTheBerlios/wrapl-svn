#include <Gtk/Gtk/RecentChooser.h>
#include <Riva/Memory.h>
#include <Gtk/Gtk/RecentChooser.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/RecentInfo.h>
#include <Gtk/Gtk/RecentFilter.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/RecentSortFunc.h>
#include <Gtk/Gtk/RecentSortType.h>
#include <Gtk/Gtk/RecentChooser.h>
TYPE(T);

GLOBAL_FUNCTION(ErrorQuark, 0) {
	GQuark result = gtk_recent_chooser_error_quark();
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_recent_chooser_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddFilter", TYP, T, TYP, Gtk$Gtk$RecentFilter$T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkRecentFilter * filter = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_recent_chooser_add_filter(self, filter);
	return SUCCESS;
};

METHOD("GetCurrentItem", TYP, T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkRecentInfo * result = gtk_recent_chooser_get_current_item(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetCurrentUri", TYP, T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char * result = gtk_recent_chooser_get_current_uri(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetFilter", TYP, T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkRecentFilter * result = gtk_recent_chooser_get_filter(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetItems", TYP, T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GList* result = gtk_recent_chooser_get_items(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetLimit", TYP, T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_recent_chooser_get_limit(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetLocalOnly", TYP, T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_recent_chooser_get_local_only(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSelectMultiple", TYP, T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_recent_chooser_get_select_multiple(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetShowIcons", TYP, T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_recent_chooser_get_show_icons(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetShowNotFound", TYP, T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_recent_chooser_get_show_not_found(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetShowNumbers", TYP, T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_recent_chooser_get_show_numbers(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetShowPrivate", TYP, T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_recent_chooser_get_show_private(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetShowTips", TYP, T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_recent_chooser_get_show_tips(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSortType", TYP, T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkRecentSortType result = gtk_recent_chooser_get_sort_type(self);
	Gtk$Gtk$RecentSortType_t *_result = new(Gtk$Gtk$RecentSortType_t);
	_result->Type = Gtk$Gtk$RecentSortType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetUris", TYP, T, TYP, Std$Object$T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gsize* length = 0;
	const char * const * result = gtk_recent_chooser_get_uris(self, length);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("ListFilters", TYP, T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GSList* result = gtk_recent_chooser_list_filters(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("RemoveFilter", TYP, T, TYP, Gtk$Gtk$RecentFilter$T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkRecentFilter * filter = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_recent_chooser_remove_filter(self, filter);
	return SUCCESS;
};

METHOD("SelectAll", TYP, T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_recent_chooser_select_all(self);
	return SUCCESS;
};

METHOD("SelectUri", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *uri = Std$String$flatten(Args[2].Val);
	GError** error = 0;
	int result = gtk_recent_chooser_select_uri(self, uri, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetCurrentUri", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *uri = Std$String$flatten(Args[2].Val);
	GError** error = 0;
	int result = gtk_recent_chooser_set_current_uri(self, uri, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetFilter", TYP, T, TYP, Gtk$Gtk$RecentFilter$T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkRecentFilter * filter = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_recent_chooser_set_filter(self, filter);
	return SUCCESS;
};

METHOD("SetLimit", TYP, T, TYP, Std$Integer$SmallT) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int limit = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_recent_chooser_set_limit(self, limit);
	return SUCCESS;
};

METHOD("SetLocalOnly", TYP, T, TYP, Std$Symbol$T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int local_only = Args[2].Val == $true;
	gtk_recent_chooser_set_local_only(self, local_only);
	return SUCCESS;
};

METHOD("SetSelectMultiple", TYP, T, TYP, Std$Symbol$T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int select_multiple = Args[2].Val == $true;
	gtk_recent_chooser_set_select_multiple(self, select_multiple);
	return SUCCESS;
};

METHOD("SetShowIcons", TYP, T, TYP, Std$Symbol$T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int show_icons = Args[2].Val == $true;
	gtk_recent_chooser_set_show_icons(self, show_icons);
	return SUCCESS;
};

METHOD("SetShowNotFound", TYP, T, TYP, Std$Symbol$T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int show_not_found = Args[2].Val == $true;
	gtk_recent_chooser_set_show_not_found(self, show_not_found);
	return SUCCESS;
};

METHOD("SetShowNumbers", TYP, T, TYP, Std$Symbol$T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int show_numbers = Args[2].Val == $true;
	gtk_recent_chooser_set_show_numbers(self, show_numbers);
	return SUCCESS;
};

METHOD("SetShowPrivate", TYP, T, TYP, Std$Symbol$T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int show_private = Args[2].Val == $true;
	gtk_recent_chooser_set_show_private(self, show_private);
	return SUCCESS;
};

METHOD("SetShowTips", TYP, T, TYP, Std$Symbol$T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int show_tips = Args[2].Val == $true;
	gtk_recent_chooser_set_show_tips(self, show_tips);
	return SUCCESS;
};

METHOD("SetSortFunc", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Object$T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkRecentSortFunc sort_func = Gtk$Gtk$RecentSortFunc$new(Args[2].Val);
	void *sort_data = ((Std$Address_t *)Args[3].Val)->Value;
	GDestroyNotify data_destroy = 0;
	gtk_recent_chooser_set_sort_func(self, sort_func, sort_data, data_destroy);
	return SUCCESS;
};

METHOD("SetSortType", TYP, T, TYP, Gtk$Gtk$RecentSortType$T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkRecentSortType sort_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_recent_chooser_set_sort_type(self, sort_type);
	return SUCCESS;
};

METHOD("UnselectAll", TYP, T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_recent_chooser_unselect_all(self);
	return SUCCESS;
};

METHOD("UnselectUri", TYP, T, TYP, Std$String$T) {
	GtkRecentChooser * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *uri = Std$String$flatten(Args[2].Val);
	gtk_recent_chooser_unselect_uri(self, uri);
	return SUCCESS;
};

