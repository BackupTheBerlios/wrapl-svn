#include <Gtk/Pango/Font.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 10
#include <Gtk/Pango/FontMetrics.h>
#include <Gtk/Pango/EngineShape.h>
#include <Gtk/Pango/Coverage.h>
#include <Gtk/Pango/FontDescription.h>
#include <Gtk/Pango/Font.h>
#include <Gtk/Pango/Language.h>
#include <Gtk/Pango/Rectangle.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/FontMap.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(DescriptionsFree, 2) {
	PangoFontDescription** descs = 0;
	int n_descs = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_font_descriptions_free(descs, n_descs);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_font_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Describe", TYP, T) {
	PangoFont * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontDescription * result = pango_font_describe(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("DescribeWithAbsoluteSize", TYP, T) {
	PangoFont * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontDescription * result = pango_font_describe_with_absolute_size(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("FindShaper", TYP, T, TYP, Gtk$Pango$Language$T, TYP, Std$Integer$SmallT) {
	PangoFont * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoLanguage * language= ((Gtk$Pango$Language_t *)Args[1].Val)->Value;
	int ch = ((Std$Integer_smallt *)Args[2].Val)->Value;
	PangoEngineShape * result = pango_font_find_shaper(self, language, ch);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetCoverage", TYP, T, TYP, Gtk$Pango$Language$T) {
	PangoFont * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoLanguage * language= ((Gtk$Pango$Language_t *)Args[1].Val)->Value;
	PangoCoverage * result = pango_font_get_coverage(self, language);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetFontMap", TYP, T) {
	PangoFont * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontMap * result = pango_font_get_font_map(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetGlyphExtents", TYP, T, TYP, Std$Object$T, TYP, Gtk$Pango$Rectangle$T, TYP, Gtk$Pango$Rectangle$T) {
	PangoFont * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoGlyph glyph = 0;
	PangoRectangle * ink_rect= &((Gtk$Pango$Rectangle_t *)Args[2].Val)->Value;
	PangoRectangle * logical_rect= &((Gtk$Pango$Rectangle_t *)Args[3].Val)->Value;
	pango_font_get_glyph_extents(self, glyph, ink_rect, logical_rect);
	return SUCCESS;
};

METHOD("GetMetrics", TYP, T, TYP, Gtk$Pango$Language$T) {
	PangoFont * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoLanguage * language= ((Gtk$Pango$Language_t *)Args[1].Val)->Value;
	PangoFontMetrics * result = pango_font_get_metrics(self, language);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

