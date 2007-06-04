#include <Gtk/Gtk/RecentChooserMenu.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/RecentChooserMenu.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/RecentManager.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Menu$T, Gtk$Gtk$MenuShell$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkRecentChooserMenu * result = gtk_recent_chooser_menu_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewForManager, 1) {
	GtkRecentManager * manager = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkRecentChooserMenu * result = gtk_recent_chooser_menu_new_for_manager(manager);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_recent_chooser_menu_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetShowNumbers", TYP, T) {
	GtkRecentChooserMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_recent_chooser_menu_get_show_numbers(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetShowNumbers", TYP, T, TYP, Std$Symbol$T) {
	GtkRecentChooserMenu * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int show_numbers = Args[1].Val == $true;
	gtk_recent_chooser_menu_set_show_numbers(self, show_numbers);
	return SUCCESS;
};

