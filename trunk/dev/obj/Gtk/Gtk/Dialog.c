#include <Gtk/Gtk/Dialog.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Dialog.h>
#include <Gtk/Gtk/Widget.h>
#include <Gtk/Gtk/Window.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Window$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkDialog * result = gtk_dialog_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithButtons, 5) {
	char *title = Std$String$flatten(Args[0].Val);
	GtkWindow * parent = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int flags = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char *first_button_text = Std$String$flatten(Args[3].Val);
	char *___ = 0;
	GtkDialog * result = gtk_dialog_new_with_buttons(title, parent, flags, first_button_text, ___);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_dialog_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddActionWidget", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT) {
	GtkDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int response_id = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_dialog_add_action_widget(self, child, response_id);
	return SUCCESS;
};

METHOD("AddButton", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GtkDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *button_text = Std$String$flatten(Args[1].Val);
	int response_id = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkWidget * result = gtk_dialog_add_button(self, button_text, response_id);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("AddButtons", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *first_button_text = Std$String$flatten(Args[1].Val);
	char *___ = 0;
	gtk_dialog_add_buttons(self, first_button_text, ___);
	return SUCCESS;
};

METHOD("GetHasSeparator", TYP, T) {
	GtkDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_dialog_get_has_separator(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetResponseForWidget", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_dialog_get_response_for_widget(self, widget);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Response", TYP, T, TYP, Std$Integer$SmallT) {
	GtkDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int response_id = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_dialog_response(self, response_id);
	return SUCCESS;
};

METHOD("Run", TYP, T) {
	GtkDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_dialog_run(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("SetAlternativeButtonOrder", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int first_response_id = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *___ = 0;
	gtk_dialog_set_alternative_button_order(self, first_response_id, ___);
	return SUCCESS;
};

METHOD("SetAlternativeButtonOrderFromArray", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int n_params = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gint* new_order = 0;
	gtk_dialog_set_alternative_button_order_from_array(self, n_params, new_order);
	return SUCCESS;
};

METHOD("SetDefaultResponse", TYP, T, TYP, Std$Integer$SmallT) {
	GtkDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int response_id = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_dialog_set_default_response(self, response_id);
	return SUCCESS;
};

METHOD("SetHasSeparator", TYP, T, TYP, Std$Symbol$T) {
	GtkDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_dialog_set_has_separator(self, setting);
	return SUCCESS;
};

METHOD("SetResponseSensitive", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Symbol$T) {
	GtkDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int response_id = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int setting = Args[2].Val == $true;
	gtk_dialog_set_response_sensitive(self, response_id, setting);
	return SUCCESS;
};

