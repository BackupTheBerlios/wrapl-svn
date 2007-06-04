#include <Gtk/Pango/Cairo.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/Pango/Font.h>
#include <Gtk/Pango/LayoutLine.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Layout.h>
#include <Gtk/Pango/Context.h>
#include <Gtk/Pango/GlyphString.h>
/***********************************/
GLOBAL_FUNCTION(ContextGetFontOptions, 1) {
	PangoContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const cairo_font_options_t* result = pango_cairo_context_get_font_options(context);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(ContextGetResolution, 1) {
	PangoContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = pango_cairo_context_get_resolution(context);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ContextSetFontOptions, 2) {
	PangoContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const cairo_font_options_t* options = 0;
	pango_cairo_context_set_font_options(context, options);
	return SUCCESS;
};

GLOBAL_FUNCTION(ContextSetResolution, 2) {
	PangoContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double dpi = ((Std$Real_t *)Args[1].Val)->Value;
	pango_cairo_context_set_resolution(context, dpi);
	return SUCCESS;
};

GLOBAL_FUNCTION(CreateLayout, 1) {
	cairo_t* cr = 0;
	PangoLayout * result = pango_cairo_create_layout(cr);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ErrorUnderlinePath, 5) {
	cairo_t* cr = 0;
	double x = ((Std$Real_t *)Args[1].Val)->Value;
	double y = ((Std$Real_t *)Args[2].Val)->Value;
	double width = ((Std$Real_t *)Args[3].Val)->Value;
	double height = ((Std$Real_t *)Args[4].Val)->Value;
	pango_cairo_error_underline_path(cr, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(GlyphStringPath, 3) {
	cairo_t* cr = 0;
	PangoFont * font = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	PangoGlyphString * glyphs= ((Gtk$Pango$GlyphString_t *)Args[2].Val)->Value;
	pango_cairo_glyph_string_path(cr, font, glyphs);
	return SUCCESS;
};

GLOBAL_FUNCTION(LayoutLinePath, 2) {
	cairo_t* cr = 0;
	PangoLayoutLine * line= ((Gtk$Pango$LayoutLine_t *)Args[1].Val)->Value;
	pango_cairo_layout_line_path(cr, line);
	return SUCCESS;
};

GLOBAL_FUNCTION(LayoutPath, 2) {
	cairo_t* cr = 0;
	PangoLayout * layout = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	pango_cairo_layout_path(cr, layout);
	return SUCCESS;
};

GLOBAL_FUNCTION(ShowErrorUnderline, 5) {
	cairo_t* cr = 0;
	double x = ((Std$Real_t *)Args[1].Val)->Value;
	double y = ((Std$Real_t *)Args[2].Val)->Value;
	double width = ((Std$Real_t *)Args[3].Val)->Value;
	double height = ((Std$Real_t *)Args[4].Val)->Value;
	pango_cairo_show_error_underline(cr, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(ShowGlyphString, 3) {
	cairo_t* cr = 0;
	PangoFont * font = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	PangoGlyphString * glyphs= ((Gtk$Pango$GlyphString_t *)Args[2].Val)->Value;
	pango_cairo_show_glyph_string(cr, font, glyphs);
	return SUCCESS;
};

GLOBAL_FUNCTION(ShowLayout, 2) {
	cairo_t* cr = 0;
	PangoLayout * layout = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	pango_cairo_show_layout(cr, layout);
	return SUCCESS;
};

GLOBAL_FUNCTION(ShowLayoutLine, 2) {
	cairo_t* cr = 0;
	PangoLayoutLine * line= ((Gtk$Pango$LayoutLine_t *)Args[1].Val)->Value;
	pango_cairo_show_layout_line(cr, line);
	return SUCCESS;
};

GLOBAL_FUNCTION(UpdateContext, 2) {
	cairo_t* cr = 0;
	PangoContext * context = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	pango_cairo_update_context(cr, context);
	return SUCCESS;
};

GLOBAL_FUNCTION(UpdateLayout, 2) {
	cairo_t* cr = 0;
	PangoLayout * layout = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	pango_cairo_update_layout(cr, layout);
	return SUCCESS;
};

