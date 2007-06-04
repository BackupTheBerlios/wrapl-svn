#include <Gtk/Pango/Renderer.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 10
#include <Gtk/Pango/Color.h>
#include <Gtk/Pango/Font.h>
#include <Gtk/Pango/LayoutLine.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Layout.h>
#include <Gtk/Pango/Matrix.h>
#include <Gtk/Pango/Renderer.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/RenderPart.h>
#include <Gtk/Pango/GlyphString.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_renderer_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Activate", TYP, T) {
	PangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	pango_renderer_activate(self);
	return SUCCESS;
};

METHOD("Deactivate", TYP, T) {
	PangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	pango_renderer_deactivate(self);
	return SUCCESS;
};

METHOD("DrawErrorUnderline", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	PangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[4].Val)->Value;
	pango_renderer_draw_error_underline(self, x, y, width, height);
	return SUCCESS;
};

METHOD("DrawGlyph", TYP, T, TYP, Gtk$Pango$Font$T, TYP, Std$Object$T, TYP, Std$Real$T, TYP, Std$Real$T) {
	PangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFont * font = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	PangoGlyph glyph = 0;
	double x = ((Std$Real_t *)Args[3].Val)->Value;
	double y = ((Std$Real_t *)Args[4].Val)->Value;
	pango_renderer_draw_glyph(self, font, glyph, x, y);
	return SUCCESS;
};

METHOD("DrawGlyphs", TYP, T, TYP, Gtk$Pango$Font$T, TYP, Gtk$Pango$GlyphString$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	PangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFont * font = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	PangoGlyphString * glyphs= ((Gtk$Pango$GlyphString_t *)Args[2].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	pango_renderer_draw_glyphs(self, font, glyphs, x, y);
	return SUCCESS;
};

METHOD("DrawLayout", TYP, T, TYP, Gtk$Pango$Layout$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	PangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoLayout * layout = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	pango_renderer_draw_layout(self, layout, x, y);
	return SUCCESS;
};

METHOD("DrawLayoutLine", TYP, T, TYP, Gtk$Pango$LayoutLine$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	PangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoLayoutLine * line= ((Gtk$Pango$LayoutLine_t *)Args[1].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	pango_renderer_draw_layout_line(self, line, x, y);
	return SUCCESS;
};

METHOD("DrawRectangle", TYP, T, TYP, Gtk$Pango$RenderPart$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	PangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoRenderPart part = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[5].Val)->Value;
	pango_renderer_draw_rectangle(self, part, x, y, width, height);
	return SUCCESS;
};

METHOD("DrawTrapezoid", TYP, T, TYP, Gtk$Pango$RenderPart$T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T) {
	PangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoRenderPart part = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double y1_ = ((Std$Real_t *)Args[2].Val)->Value;
	double x11 = ((Std$Real_t *)Args[3].Val)->Value;
	double x21 = ((Std$Real_t *)Args[4].Val)->Value;
	double y2 = ((Std$Real_t *)Args[5].Val)->Value;
	double x12 = ((Std$Real_t *)Args[6].Val)->Value;
	double x22 = ((Std$Real_t *)Args[7].Val)->Value;
	pango_renderer_draw_trapezoid(self, part, y1_, x11, x21, y2, x12, x22);
	return SUCCESS;
};

METHOD("GetColor", TYP, T, TYP, Gtk$Pango$RenderPart$T) {
	PangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoRenderPart part = ((Std$Integer_smallt *)Args[1].Val)->Value;
	PangoColor * result = pango_renderer_get_color(self, part);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetMatrix", TYP, T) {
	PangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoMatrix * result = pango_renderer_get_matrix(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("PartChanged", TYP, T, TYP, Gtk$Pango$RenderPart$T) {
	PangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoRenderPart part = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_renderer_part_changed(self, part);
	return SUCCESS;
};

METHOD("SetColor", TYP, T, TYP, Gtk$Pango$RenderPart$T, TYP, Gtk$Pango$Color$T) {
	PangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoRenderPart part = ((Std$Integer_smallt *)Args[1].Val)->Value;
	PangoColor * color= &((Gtk$Pango$Color_t *)Args[2].Val)->Value;
	pango_renderer_set_color(self, part, color);
	return SUCCESS;
};

METHOD("SetMatrix", TYP, T, TYP, Gtk$Pango$Matrix$T) {
	PangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoMatrix * matrix= &((Gtk$Pango$Matrix_t *)Args[1].Val)->Value;
	pango_renderer_set_matrix(self, matrix);
	return SUCCESS;
};

