#include <Gtk/Gtk/RecentManager.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/RecentData.h>
#include <Gtk/Gtk/RecentInfo.h>
#include <Gtk/Gdk/Screen.h>
#include <Gtk/Gtk/RecentManager.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkRecentManager * result = gtk_recent_manager_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(ErrorQuark, 0) {
	GQuark result = gtk_recent_manager_error_quark();
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetDefault, 0) {
	GtkRecentManager * result = gtk_recent_manager_get_default();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetForScreen, 1) {
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkRecentManager * result = gtk_recent_manager_get_for_screen(screen);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_recent_manager_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddFull", TYP, T, TYP, Std$String$T, TYP, Gtk$Gtk$RecentData$T) {
	GtkRecentManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *uri = Std$String$flatten(Args[1].Val);
	GtkRecentData * recent_data= &((Gtk$Gtk$RecentData_t *)Args[2].Val)->Value;
	int result = gtk_recent_manager_add_full(self, uri, recent_data);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("AddItem", TYP, T, TYP, Std$String$T) {
	GtkRecentManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *uri = Std$String$flatten(Args[1].Val);
	int result = gtk_recent_manager_add_item(self, uri);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetItems", TYP, T) {
	GtkRecentManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* result = gtk_recent_manager_get_items(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetLimit", TYP, T) {
	GtkRecentManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_recent_manager_get_limit(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("HasItem", TYP, T, TYP, Std$String$T) {
	GtkRecentManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *uri = Std$String$flatten(Args[1].Val);
	int result = gtk_recent_manager_has_item(self, uri);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("LookupItem", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkRecentManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *uri = Std$String$flatten(Args[1].Val);
	GError** error = 0;
	GtkRecentInfo * result = gtk_recent_manager_lookup_item(self, uri, error);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("MoveItem", TYP, T, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkRecentManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *uri = Std$String$flatten(Args[1].Val);
	char *new_uri = Std$String$flatten(Args[2].Val);
	GError** error = 0;
	int result = gtk_recent_manager_move_item(self, uri, new_uri, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("PurgeItems", TYP, T, TYP, Std$Object$T) {
	GtkRecentManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GError** error = 0;
	int result = gtk_recent_manager_purge_items(self, error);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("RemoveItem", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkRecentManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *uri = Std$String$flatten(Args[1].Val);
	GError** error = 0;
	int result = gtk_recent_manager_remove_item(self, uri, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetLimit", TYP, T, TYP, Std$Integer$SmallT) {
	GtkRecentManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int limit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_recent_manager_set_limit(self, limit);
	return SUCCESS;
};

METHOD("SetScreen", TYP, T, TYP, Gtk$Gdk$Screen$T) {
	GtkRecentManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_recent_manager_set_screen(self, screen);
	return SUCCESS;
};

