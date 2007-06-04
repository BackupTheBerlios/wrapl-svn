#include <Gtk/Gtk/FileChooserWidget.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/FileChooserAction.h>
/***********************************/
TYPE(T, Gtk$Gtk$VBox$T, Gtk$Gtk$Box$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	GtkFileChooserAction action = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GtkFileChooserWidget * result = gtk_file_chooser_widget_new(action);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithBackend, 2) {
	GtkFileChooserAction action = ((Std$Integer_smallt *)Args[0].Val)->Value;
	char *backend = Std$String$flatten(Args[1].Val);
	GtkFileChooserWidget * result = gtk_file_chooser_widget_new_with_backend(action, backend);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_file_chooser_widget_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

