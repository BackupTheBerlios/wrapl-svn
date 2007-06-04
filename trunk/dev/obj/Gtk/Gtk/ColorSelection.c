#include <Gtk/Gtk/ColorSelection.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 10
#include <Std/Boolean.h>
#include <Gtk/Gtk/ColorSelection.h>
#include <Gtk/Gtk/ColorSelectionChangePaletteFunc.h>
#include <Gtk/Gtk/ColorSelectionChangePaletteFunc.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/UpdateType.h>
#include <Gtk/Gtk/ColorSelectionChangePaletteWithScreenFunc.h>
#include <Gtk/Gtk/ColorSelectionChangePaletteWithScreenFunc.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$VBox$T, Gtk$Gtk$Box$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkColorSelection * result = gtk_color_selection_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_color_selection_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaletteFromString, 3) {
	char *str = Std$String$flatten(Args[0].Val);
	GdkColor** colors = 0;
	gint* n_colors = 0;
	int result = gtk_color_selection_palette_from_string(str, colors, n_colors);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(PaletteToString, 2) {
	GdkColor * colors= &((Gtk$Gdk$Color_t *)Args[0].Val)->Value;
	int n_colors = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char * result = gtk_color_selection_palette_to_string(colors, n_colors);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetChangePaletteHook, 1) {
	GtkColorSelectionChangePaletteFunc func = Gtk$Gtk$ColorSelectionChangePaletteFunc$new(Args[0].Val);
	GtkColorSelectionChangePaletteFunc result = gtk_color_selection_set_change_palette_hook(func);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(SetChangePaletteWithScreenHook, 1) {
	GtkColorSelectionChangePaletteWithScreenFunc func = Gtk$Gtk$ColorSelectionChangePaletteWithScreenFunc$new(Args[0].Val);
	GtkColorSelectionChangePaletteWithScreenFunc result = gtk_color_selection_set_change_palette_with_screen_hook(func);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetColor", TYP, T, TYP, Std$Object$T) {
	GtkColorSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdouble* color = 0;
	gtk_color_selection_get_color(self, color);
	return SUCCESS;
};

METHOD("GetCurrentAlpha", TYP, T) {
	GtkColorSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_color_selection_get_current_alpha(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetCurrentColor", TYP, T, TYP, Gtk$Gdk$Color$T) {
	GtkColorSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	gtk_color_selection_get_current_color(self, color);
	return SUCCESS;
};

METHOD("GetHasOpacityControl", TYP, T) {
	GtkColorSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_color_selection_get_has_opacity_control(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetHasPalette", TYP, T) {
	GtkColorSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_color_selection_get_has_palette(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetPreviousAlpha", TYP, T) {
	GtkColorSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_color_selection_get_previous_alpha(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetPreviousColor", TYP, T, TYP, Gtk$Gdk$Color$T) {
	GtkColorSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	gtk_color_selection_get_previous_color(self, color);
	return SUCCESS;
};

METHOD("IsAdjusting", TYP, T) {
	GtkColorSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_color_selection_is_adjusting(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetColor", TYP, T, TYP, Std$Object$T) {
	GtkColorSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdouble* color = 0;
	gtk_color_selection_set_color(self, color);
	return SUCCESS;
};

METHOD("SetCurrentAlpha", TYP, T, TYP, Std$Integer$SmallT) {
	GtkColorSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int alpha = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_color_selection_set_current_alpha(self, alpha);
	return SUCCESS;
};

METHOD("SetCurrentColor", TYP, T, TYP, Gtk$Gdk$Color$T) {
	GtkColorSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	gtk_color_selection_set_current_color(self, color);
	return SUCCESS;
};

METHOD("SetHasOpacityControl", TYP, T, TYP, Std$Symbol$T) {
	GtkColorSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int has_opacity = Args[1].Val == $true;
	gtk_color_selection_set_has_opacity_control(self, has_opacity);
	return SUCCESS;
};

METHOD("SetHasPalette", TYP, T, TYP, Std$Symbol$T) {
	GtkColorSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int has_palette = Args[1].Val == $true;
	gtk_color_selection_set_has_palette(self, has_palette);
	return SUCCESS;
};

METHOD("SetPreviousAlpha", TYP, T, TYP, Std$Integer$SmallT) {
	GtkColorSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int alpha = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_color_selection_set_previous_alpha(self, alpha);
	return SUCCESS;
};

METHOD("SetPreviousColor", TYP, T, TYP, Gtk$Gdk$Color$T) {
	GtkColorSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	gtk_color_selection_set_previous_color(self, color);
	return SUCCESS;
};

METHOD("SetUpdatePolicy", TYP, T, TYP, Gtk$Gtk$UpdateType$T) {
	GtkColorSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkUpdateType policy = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_color_selection_set_update_policy(self, policy);
	return SUCCESS;
};

