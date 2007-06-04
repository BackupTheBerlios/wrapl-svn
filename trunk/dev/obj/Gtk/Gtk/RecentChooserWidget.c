#include <Gtk/Gtk/RecentChooserWidget.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/RecentManager.h>
/***********************************/
TYPE(T, Gtk$Gtk$VBox$T, Gtk$Gtk$Box$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkRecentChooserWidget * result = gtk_recent_chooser_widget_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewForManager, 1) {
	GtkRecentManager * manager = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkRecentChooserWidget * result = gtk_recent_chooser_widget_new_for_manager(manager);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_recent_chooser_widget_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

