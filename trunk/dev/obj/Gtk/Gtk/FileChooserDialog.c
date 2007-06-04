#include <Gtk/Gtk/FileChooserDialog.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Window.h>
#include <Gtk/Gtk/FileChooserAction.h>
/***********************************/
TYPE(T, Gtk$Gtk$Dialog$T, Gtk$Gtk$Window$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 5) {
	char *title = Std$String$flatten(Args[0].Val);
	GtkWindow * parent = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkFileChooserAction action = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char *first_button_text = Std$String$flatten(Args[3].Val);
	char *___ = 0;
	GtkFileChooserDialog * result = gtk_file_chooser_dialog_new(title, parent, action, first_button_text, ___);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithBackend, 6) {
	char *title = Std$String$flatten(Args[0].Val);
	GtkWindow * parent = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkFileChooserAction action = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char *backend = Std$String$flatten(Args[3].Val);
	char *first_button_text = Std$String$flatten(Args[4].Val);
	char *___ = 0;
	GtkFileChooserDialog * result = gtk_file_chooser_dialog_new_with_backend(title, parent, action, backend, first_button_text, ___);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_file_chooser_dialog_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

