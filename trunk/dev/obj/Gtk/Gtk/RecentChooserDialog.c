#include <Gtk/Gtk/RecentChooserDialog.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Window.h>
#include <Gtk/Gtk/RecentManager.h>
/***********************************/
TYPE(T, Gtk$Gtk$Dialog$T, Gtk$Gtk$Window$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 4) {
	char *title = Std$String$flatten(Args[0].Val);
	GtkWindow * parent = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *first_button_text = Std$String$flatten(Args[2].Val);
	char *___ = 0;
	GtkRecentChooserDialog * result = gtk_recent_chooser_dialog_new(title, parent, first_button_text, ___);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewForManager, 5) {
	char *title = Std$String$flatten(Args[0].Val);
	GtkWindow * parent = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkRecentManager * manager = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	char *first_button_text = Std$String$flatten(Args[3].Val);
	char *___ = 0;
	GtkRecentChooserDialog * result = gtk_recent_chooser_dialog_new_for_manager(title, parent, manager, first_button_text, ___);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_recent_chooser_dialog_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

