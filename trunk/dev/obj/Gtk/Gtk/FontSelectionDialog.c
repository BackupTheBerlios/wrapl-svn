#include <Gtk/Gtk/FontSelectionDialog.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Std/Boolean.h>
#include <Gtk/Gdk/Font.h>
#include <Gtk/Gtk/FontSelectionDialog.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$Dialog$T, Gtk$Gtk$Window$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	char *title = Std$String$flatten(Args[0].Val);
	GtkFontSelectionDialog * result = gtk_font_selection_dialog_new(title);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_font_selection_dialog_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetFont", TYP, T) {
	GtkFontSelectionDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkFont * result = gtk_font_selection_dialog_get_font(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetFontName", TYP, T) {
	GtkFontSelectionDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char * result = gtk_font_selection_dialog_get_font_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetPreviewText", TYP, T) {
	GtkFontSelectionDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_font_selection_dialog_get_preview_text(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("SetFontName", TYP, T, TYP, Std$String$T) {
	GtkFontSelectionDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *fontname = Std$String$flatten(Args[1].Val);
	int result = gtk_font_selection_dialog_set_font_name(self, fontname);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetPreviewText", TYP, T, TYP, Std$String$T) {
	GtkFontSelectionDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	gtk_font_selection_dialog_set_preview_text(self, text);
	return SUCCESS;
};

