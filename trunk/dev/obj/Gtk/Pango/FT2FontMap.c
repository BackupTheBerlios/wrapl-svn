#include <Gtk/Pango/FT2FontMap.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/FT2FontMap.h>
#include <Gtk/Pango/Context.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/FontMap.h>
#include <Gtk/Pango/FT2SubstituteFunc.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	PangoFT2FontMap * result = pango_ft2_font_map_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(ForDisplay, 0) {
	PangoFontMap * result = pango_ft2_font_map_for_display();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_ft2_font_map_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("CreateContext", TYP, T) {
	PangoFT2FontMap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoContext * result = pango_ft2_font_map_create_context(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("SetDefaultSubstitute", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Object$T) {
	PangoFT2FontMap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFT2SubstituteFunc func = Gtk$Pango$FT2SubstituteFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GDestroyNotify notify = 0;
	pango_ft2_font_map_set_default_substitute(self, func, data, notify);
	return SUCCESS;
};

METHOD("SetResolution", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T) {
	PangoFT2FontMap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double dpi_x = ((Std$Real_t *)Args[1].Val)->Value;
	double dpi_y = ((Std$Real_t *)Args[2].Val)->Value;
	pango_ft2_font_map_set_resolution(self, dpi_x, dpi_y);
	return SUCCESS;
};

METHOD("SubstituteChanged", TYP, T) {
	PangoFT2FontMap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	pango_ft2_font_map_substitute_changed(self);
	return SUCCESS;
};

