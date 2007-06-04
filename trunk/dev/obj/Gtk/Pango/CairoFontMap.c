#include <Gtk/Pango/CairoFontMap.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/Pango/CairoFontMap.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Context.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/FontMap.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	PangoCairoFontMap * result = pango_cairo_font_map_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetDefault, 0) {
	PangoFontMap * result = pango_cairo_font_map_get_default();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_cairo_font_map_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("CreateContext", TYP, T) {
	PangoCairoFontMap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoContext * result = pango_cairo_font_map_create_context(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetResolution", TYP, T) {
	PangoCairoFontMap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = pango_cairo_font_map_get_resolution(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("SetResolution", TYP, T, TYP, Std$Real$T) {
	PangoCairoFontMap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double dpi = ((Std$Real_t *)Args[1].Val)->Value;
	pango_cairo_font_map_set_resolution(self, dpi);
	return SUCCESS;
};

