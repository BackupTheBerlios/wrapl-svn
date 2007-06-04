#include <Gtk/Gtk/FontButton.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/FontButton.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Button$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkFontButton * result = gtk_font_button_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithFont, 1) {
	char *fontname = Std$String$flatten(Args[0].Val);
	GtkFontButton * result = gtk_font_button_new_with_font(fontname);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_font_button_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetFontName", TYP, T) {
	GtkFontButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_font_button_get_font_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetShowSize", TYP, T) {
	GtkFontButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_font_button_get_show_size(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetShowStyle", TYP, T) {
	GtkFontButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_font_button_get_show_style(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetTitle", TYP, T) {
	GtkFontButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_font_button_get_title(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetUseFont", TYP, T) {
	GtkFontButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_font_button_get_use_font(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetUseSize", TYP, T) {
	GtkFontButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_font_button_get_use_size(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetFontName", TYP, T, TYP, Std$String$T) {
	GtkFontButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *fontname = Std$String$flatten(Args[1].Val);
	int result = gtk_font_button_set_font_name(self, fontname);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetShowSize", TYP, T, TYP, Std$Symbol$T) {
	GtkFontButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int show_size = Args[1].Val == $true;
	gtk_font_button_set_show_size(self, show_size);
	return SUCCESS;
};

METHOD("SetShowStyle", TYP, T, TYP, Std$Symbol$T) {
	GtkFontButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int show_style = Args[1].Val == $true;
	gtk_font_button_set_show_style(self, show_style);
	return SUCCESS;
};

METHOD("SetTitle", TYP, T, TYP, Std$String$T) {
	GtkFontButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *title = Std$String$flatten(Args[1].Val);
	gtk_font_button_set_title(self, title);
	return SUCCESS;
};

METHOD("SetUseFont", TYP, T, TYP, Std$Symbol$T) {
	GtkFontButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int use_font = Args[1].Val == $true;
	gtk_font_button_set_use_font(self, use_font);
	return SUCCESS;
};

METHOD("SetUseSize", TYP, T, TYP, Std$Symbol$T) {
	GtkFontButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int use_size = Args[1].Val == $true;
	gtk_font_button_set_use_size(self, use_size);
	return SUCCESS;
};

