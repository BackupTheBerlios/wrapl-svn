#include <Gtk/Gtk/ColorButton.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/ColorButton.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Button$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkColorButton * result = gtk_color_button_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithColor, 1) {
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[0].Val)->Value;
	GtkColorButton * result = gtk_color_button_new_with_color(color);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_color_button_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetAlpha", TYP, T) {
	GtkColorButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_color_button_get_alpha(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetColor", TYP, T, TYP, Gtk$Gdk$Color$T) {
	GtkColorButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	gtk_color_button_get_color(self, color);
	return SUCCESS;
};

METHOD("GetTitle", TYP, T) {
	GtkColorButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_color_button_get_title(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetUseAlpha", TYP, T) {
	GtkColorButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_color_button_get_use_alpha(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetAlpha", TYP, T, TYP, Std$Integer$SmallT) {
	GtkColorButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int alpha = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_color_button_set_alpha(self, alpha);
	return SUCCESS;
};

METHOD("SetColor", TYP, T, TYP, Gtk$Gdk$Color$T) {
	GtkColorButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	gtk_color_button_set_color(self, color);
	return SUCCESS;
};

METHOD("SetTitle", TYP, T, TYP, Std$String$T) {
	GtkColorButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *title = Std$String$flatten(Args[1].Val);
	gtk_color_button_set_title(self, title);
	return SUCCESS;
};

METHOD("SetUseAlpha", TYP, T, TYP, Std$Symbol$T) {
	GtkColorButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int use_alpha = Args[1].Val == $true;
	gtk_color_button_set_use_alpha(self, use_alpha);
	return SUCCESS;
};

