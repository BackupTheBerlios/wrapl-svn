#include <Gtk/Pango/GlyphString.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/Pango/Font.h>
#include <Gtk/Pango/Rectangle.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/GlyphString.h>
#include <Std/Boolean.h>
#include <Gtk/Pango/Analysis.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 0) {
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = pango_glyph_string_new();
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_glyph_string_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	PangoGlyphString * self= ((Gtk$Pango$GlyphString_t *)Args[0].Val)->Value;
	PangoGlyphString * result = pango_glyph_string_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Extents", TYP, T, TYP, Gtk$Pango$Font$T, TYP, Gtk$Pango$Rectangle$T, TYP, Gtk$Pango$Rectangle$T) {
	PangoGlyphString * self= ((Gtk$Pango$GlyphString_t *)Args[0].Val)->Value;
	PangoFont * font = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	PangoRectangle * ink_rect= &((Gtk$Pango$Rectangle_t *)Args[2].Val)->Value;
	PangoRectangle * logical_rect= &((Gtk$Pango$Rectangle_t *)Args[3].Val)->Value;
	pango_glyph_string_extents(self, font, ink_rect, logical_rect);
	return SUCCESS;
};

METHOD("ExtentsRange", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Pango$Font$T, TYP, Gtk$Pango$Rectangle$T, TYP, Gtk$Pango$Rectangle$T) {
	PangoGlyphString * self= ((Gtk$Pango$GlyphString_t *)Args[0].Val)->Value;
	int start = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int end = ((Std$Integer_smallt *)Args[2].Val)->Value;
	PangoFont * font = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	PangoRectangle * ink_rect= &((Gtk$Pango$Rectangle_t *)Args[4].Val)->Value;
	PangoRectangle * logical_rect= &((Gtk$Pango$Rectangle_t *)Args[5].Val)->Value;
	pango_glyph_string_extents_range(self, start, end, font, ink_rect, logical_rect);
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	PangoGlyphString * self= ((Gtk$Pango$GlyphString_t *)Args[0].Val)->Value;
	pango_glyph_string_free(self);
	return SUCCESS;
};

METHOD("GetLogicalWidths", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	PangoGlyphString * self= ((Gtk$Pango$GlyphString_t *)Args[0].Val)->Value;
	char *text = Std$String$flatten(Args[1].Val);
	int length = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int embedding_level = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int* logical_widths = 0;
	pango_glyph_string_get_logical_widths(self, text, length, embedding_level, logical_widths);
	return SUCCESS;
};

METHOD("GetWidth", TYP, T) {
	PangoGlyphString * self= ((Gtk$Pango$GlyphString_t *)Args[0].Val)->Value;
	int result = pango_glyph_string_get_width(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("IndexToX", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Gtk$Pango$Analysis$T, TYP, Std$Integer$SmallT, TYP, Std$Symbol$T, TYP, Std$Object$T) {
	PangoGlyphString * self= ((Gtk$Pango$GlyphString_t *)Args[0].Val)->Value;
	char *text = Std$String$flatten(Args[1].Val);
	int length = ((Std$Integer_smallt *)Args[2].Val)->Value;
	PangoAnalysis * analysis= &((Gtk$Pango$Analysis_t *)Args[3].Val)->Value;
	int index_ = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int trailing = Args[5].Val == $true;
	int* x_pos = 0;
	pango_glyph_string_index_to_x(self, text, length, analysis, index_, trailing, x_pos);
	return SUCCESS;
};

METHOD("SetSize", TYP, T, TYP, Std$Integer$SmallT) {
	PangoGlyphString * self= ((Gtk$Pango$GlyphString_t *)Args[0].Val)->Value;
	int new_len = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_glyph_string_set_size(self, new_len);
	return SUCCESS;
};

METHOD("XToIndex", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Gtk$Pango$Analysis$T, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoGlyphString * self= ((Gtk$Pango$GlyphString_t *)Args[0].Val)->Value;
	char *text = Std$String$flatten(Args[1].Val);
	int length = ((Std$Integer_smallt *)Args[2].Val)->Value;
	PangoAnalysis * analysis= &((Gtk$Pango$Analysis_t *)Args[3].Val)->Value;
	int x_pos = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int* index_ = 0;
	int* trailing = 0;
	pango_glyph_string_x_to_index(self, text, length, analysis, x_pos, index_, trailing);
	return SUCCESS;
};

