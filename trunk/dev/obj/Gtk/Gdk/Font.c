#include <Gtk/Gdk/Font.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Std/Boolean.h>
#include <Gtk/Gdk/Font.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/Pango/FontDescription.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(FromDescription, 1) {
	PangoFontDescription * font_desc= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	GdkFont * result = gdk_font_from_description(font_desc);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(FromDescriptionForDisplay, 2) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontDescription * font_desc= ((Gtk$Pango$FontDescription_t *)Args[1].Val)->Value;
	GdkFont * result = gdk_font_from_description_for_display(display, font_desc);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_font_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Load, 1) {
	char *font_name = Std$String$flatten(Args[0].Val);
	GdkFont * result = gdk_font_load(font_name);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(LoadForDisplay, 2) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *font_name = Std$String$flatten(Args[1].Val);
	GdkFont * result = gdk_font_load_for_display(display, font_name);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Equal", TYP, T, TYP, Gtk$Gdk$Font$T) {
	GdkFont * self= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	GdkFont * fontb= ((Gtk$Gdk$Font_t *)Args[1].Val)->Value;
	int result = gdk_font_equal(self, fontb);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetDisplay", TYP, T) {
	GdkFont * self= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	GdkDisplay * result = gdk_font_get_display(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Id", TYP, T) {
	GdkFont * self= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	int result = gdk_font_id(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GdkFont * self= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	GdkFont * result = gdk_font_ref(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GdkFont * self= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	gdk_font_unref(self);
	return SUCCESS;
};

