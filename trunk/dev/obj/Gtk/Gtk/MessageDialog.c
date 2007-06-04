#include <Gtk/Gtk/MessageDialog.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/Gtk/MessageDialog.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/ButtonsType.h>
#include <Gtk/Gtk/MessageType.h>
#include <Gtk/Gtk/Widget.h>
#include <Gtk/Gtk/Window.h>
/***********************************/
TYPE(T, Gtk$Gtk$Dialog$T, Gtk$Gtk$Window$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 6) {
	GtkWindow * parent = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int flags = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkMessageType type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkButtonsType buttons = ((Std$Integer_smallt *)Args[3].Val)->Value;
	char *message_format = Std$String$flatten(Args[4].Val);
	char *___ = 0;
	GtkMessageDialog * result = gtk_message_dialog_new(parent, flags, type, buttons, message_format, ___);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithMarkup, 6) {
	GtkWindow * parent = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int flags = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkMessageType type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkButtonsType buttons = ((Std$Integer_smallt *)Args[3].Val)->Value;
	char *message_format = Std$String$flatten(Args[4].Val);
	char *___ = 0;
	GtkMessageDialog * result = gtk_message_dialog_new_with_markup(parent, flags, type, buttons, message_format, ___);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_message_dialog_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("FormatSecondaryMarkup", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkMessageDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *message_format = Std$String$flatten(Args[1].Val);
	char *___ = 0;
	gtk_message_dialog_format_secondary_markup(self, message_format, ___);
	return SUCCESS;
};

METHOD("FormatSecondaryText", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkMessageDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *message_format = Std$String$flatten(Args[1].Val);
	char *___ = 0;
	gtk_message_dialog_format_secondary_text(self, message_format, ___);
	return SUCCESS;
};

METHOD("SetImage", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkMessageDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * image = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_message_dialog_set_image(self, image);
	return SUCCESS;
};

METHOD("SetMarkup", TYP, T, TYP, Std$String$T) {
	GtkMessageDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *str = Std$String$flatten(Args[1].Val);
	gtk_message_dialog_set_markup(self, str);
	return SUCCESS;
};

