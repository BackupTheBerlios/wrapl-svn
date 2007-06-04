#include <Gtk/Gtk/FileChooserButton.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
#include <Gtk/Gtk/FileChooserAction.h>
#include <Gtk/Gtk/FileChooserButton.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$HBox$T, Gtk$Gtk$Box$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 2) {
	char *title = Std$String$flatten(Args[0].Val);
	GtkFileChooserAction action = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkFileChooserButton * result = gtk_file_chooser_button_new(title, action);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithBackend, 3) {
	char *title = Std$String$flatten(Args[0].Val);
	GtkFileChooserAction action = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *backend = Std$String$flatten(Args[2].Val);
	GtkFileChooserButton * result = gtk_file_chooser_button_new_with_backend(title, action, backend);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithDialog, 1) {
	GtkWidget * dialog = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkFileChooserButton * result = gtk_file_chooser_button_new_with_dialog(dialog);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_file_chooser_button_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetFocusOnClick", TYP, T) {
	GtkFileChooserButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_file_chooser_button_get_focus_on_click(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetTitle", TYP, T) {
	GtkFileChooserButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_file_chooser_button_get_title(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetWidthChars", TYP, T) {
	GtkFileChooserButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_file_chooser_button_get_width_chars(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("SetFocusOnClick", TYP, T, TYP, Std$Symbol$T) {
	GtkFileChooserButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int focus_on_click = Args[1].Val == $true;
	gtk_file_chooser_button_set_focus_on_click(self, focus_on_click);
	return SUCCESS;
};

METHOD("SetTitle", TYP, T, TYP, Std$String$T) {
	GtkFileChooserButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *title = Std$String$flatten(Args[1].Val);
	gtk_file_chooser_button_set_title(self, title);
	return SUCCESS;
};

METHOD("SetWidthChars", TYP, T, TYP, Std$Integer$SmallT) {
	GtkFileChooserButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int n_chars = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_file_chooser_button_set_width_chars(self, n_chars);
	return SUCCESS;
};

