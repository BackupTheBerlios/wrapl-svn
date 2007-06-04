#include <Gtk/Gdk/Drawable.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 24
#include <Gtk/Gdk/GC.h>
#include <Gtk/Gdk/Font.h>
#include <Gtk/Gdk/RgbCmap.h>
#include <Gtk/Gdk/Segment.h>
#include <Gtk/Gdk/Colormap.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/Pango/Font.h>
#include <Gtk/Pango/LayoutLine.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Layout.h>
#include <Gtk/Pango/Matrix.h>
#include <Gtk/Gdk/Drawable.h>
#include <Gtk/Gdk/Image.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/Gdk/Point.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/GlyphString.h>
#include <Gtk/Gdk/Trapezoid.h>
#include <Gtk/Gdk/RgbDither.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Gtk/Gdk/Visual.h>
#include <Gtk/Gdk/Screen.h>
#include <Gtk/Gdk/Region.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_drawable_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("DrawArc", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Std$Symbol$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int filled = Args[2].Val == $true;
	int x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int angle1 = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int angle2 = ((Std$Integer_smallt *)Args[8].Val)->Value;
	gdk_draw_arc(self, gc, filled, x, y, width, height, angle1, angle2);
	return SUCCESS;
};

METHOD("DrawDrawable", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Gtk$Gdk$Drawable$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkDrawable * src = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int xsrc = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int ysrc = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int xdest = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int ydest = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[8].Val)->Value;
	gdk_draw_drawable(self, gc, src, xsrc, ysrc, xdest, ydest, width, height);
	return SUCCESS;
};

METHOD("DrawGlyphs", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Gtk$Pango$Font$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Pango$GlyphString$T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	PangoFont * font = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	PangoGlyphString * glyphs= ((Gtk$Pango$GlyphString_t *)Args[5].Val)->Value;
	gdk_draw_glyphs(self, gc, font, x, y, glyphs);
	return SUCCESS;
};

METHOD("DrawGlyphsTransformed", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Gtk$Pango$Matrix$T, TYP, Gtk$Pango$Font$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Pango$GlyphString$T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	PangoMatrix * matrix= &((Gtk$Pango$Matrix_t *)Args[2].Val)->Value;
	PangoFont * font = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	PangoGlyphString * glyphs= ((Gtk$Pango$GlyphString_t *)Args[6].Val)->Value;
	gdk_draw_glyphs_transformed(self, gc, matrix, font, x, y, glyphs);
	return SUCCESS;
};

METHOD("DrawGrayImage", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$RgbDither$T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[5].Val)->Value;
	GdkRgbDither dith = ((Std$Integer_smallt *)Args[6].Val)->Value;
	char *buf = Std$String$flatten(Args[7].Val);
	int rowstride = ((Std$Integer_smallt *)Args[8].Val)->Value;
	gdk_draw_gray_image(self, gc, x, y, width, height, dith, buf, rowstride);
	return SUCCESS;
};

METHOD("DrawImage", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Gtk$Gdk$Image$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkImage * image = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int xsrc = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int ysrc = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int xdest = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int ydest = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[8].Val)->Value;
	gdk_draw_image(self, gc, image, xsrc, ysrc, xdest, ydest, width, height);
	return SUCCESS;
};

METHOD("DrawIndexedImage", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$RgbDither$T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$RgbCmap$T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[5].Val)->Value;
	GdkRgbDither dith = ((Std$Integer_smallt *)Args[6].Val)->Value;
	char *buf = Std$String$flatten(Args[7].Val);
	int rowstride = ((Std$Integer_smallt *)Args[8].Val)->Value;
	GdkRgbCmap * cmap= ((Gtk$Gdk$RgbCmap_t *)Args[9].Val)->Value;
	gdk_draw_indexed_image(self, gc, x, y, width, height, dith, buf, rowstride, cmap);
	return SUCCESS;
};

METHOD("DrawLayout", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Pango$Layout$T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	PangoLayout * layout = ((Gtk$GObject$Object_t *)Args[4].Val)->Handle;
	gdk_draw_layout(self, gc, x, y, layout);
	return SUCCESS;
};

METHOD("DrawLayoutLine", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Pango$LayoutLine$T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	PangoLayoutLine * line= ((Gtk$Pango$LayoutLine_t *)Args[4].Val)->Value;
	gdk_draw_layout_line(self, gc, x, y, line);
	return SUCCESS;
};

METHOD("DrawLayoutLineWithColors", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Pango$LayoutLine$T, TYP, Gtk$Gdk$Color$T, TYP, Gtk$Gdk$Color$T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	PangoLayoutLine * line= ((Gtk$Pango$LayoutLine_t *)Args[4].Val)->Value;
	GdkColor * foreground= &((Gtk$Gdk$Color_t *)Args[5].Val)->Value;
	GdkColor * background= &((Gtk$Gdk$Color_t *)Args[6].Val)->Value;
	gdk_draw_layout_line_with_colors(self, gc, x, y, line, foreground, background);
	return SUCCESS;
};

METHOD("DrawLayoutWithColors", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Pango$Layout$T, TYP, Gtk$Gdk$Color$T, TYP, Gtk$Gdk$Color$T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	PangoLayout * layout = ((Gtk$GObject$Object_t *)Args[4].Val)->Handle;
	GdkColor * foreground= &((Gtk$Gdk$Color_t *)Args[5].Val)->Value;
	GdkColor * background= &((Gtk$Gdk$Color_t *)Args[6].Val)->Value;
	gdk_draw_layout_with_colors(self, gc, x, y, layout, foreground, background);
	return SUCCESS;
};

METHOD("DrawLine", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x1_ = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y1_ = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int x2_ = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y2_ = ((Std$Integer_smallt *)Args[5].Val)->Value;
	gdk_draw_line(self, gc, x1_, y1_, x2_, y2_);
	return SUCCESS;
};

METHOD("DrawLines", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Gtk$Gdk$Point$T, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkPoint * points= &((Gtk$Gdk$Point_t *)Args[2].Val)->Value;
	int npoints = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_draw_lines(self, gc, points, npoints);
	return SUCCESS;
};

METHOD("DrawPixbuf", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Gtk$Gdk$Pixbuf$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$RgbDither$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int src_x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int src_y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int dest_x = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int dest_y = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[8].Val)->Value;
	GdkRgbDither dither = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int x_dither = ((Std$Integer_smallt *)Args[10].Val)->Value;
	int y_dither = ((Std$Integer_smallt *)Args[11].Val)->Value;
	gdk_draw_pixbuf(self, gc, pixbuf, src_x, src_y, dest_x, dest_y, width, height, dither, x_dither, y_dither);
	return SUCCESS;
};

METHOD("DrawPoint", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_draw_point(self, gc, x, y);
	return SUCCESS;
};

METHOD("DrawPoints", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Gtk$Gdk$Point$T, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkPoint * points= &((Gtk$Gdk$Point_t *)Args[2].Val)->Value;
	int npoints = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_draw_points(self, gc, points, npoints);
	return SUCCESS;
};

METHOD("DrawPolygon", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Std$Symbol$T, TYP, Gtk$Gdk$Point$T, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int filled = Args[2].Val == $true;
	GdkPoint * points= &((Gtk$Gdk$Point_t *)Args[3].Val)->Value;
	int npoints = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gdk_draw_polygon(self, gc, filled, points, npoints);
	return SUCCESS;
};

METHOD("DrawRectangle", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Std$Symbol$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int filled = Args[2].Val == $true;
	int x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[6].Val)->Value;
	gdk_draw_rectangle(self, gc, filled, x, y, width, height);
	return SUCCESS;
};

METHOD("DrawRgb32Image", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$RgbDither$T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[5].Val)->Value;
	GdkRgbDither dith = ((Std$Integer_smallt *)Args[6].Val)->Value;
	char *buf = Std$String$flatten(Args[7].Val);
	int rowstride = ((Std$Integer_smallt *)Args[8].Val)->Value;
	gdk_draw_rgb_32_image(self, gc, x, y, width, height, dith, buf, rowstride);
	return SUCCESS;
};

METHOD("DrawRgb32ImageDithalign", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$RgbDither$T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[5].Val)->Value;
	GdkRgbDither dith = ((Std$Integer_smallt *)Args[6].Val)->Value;
	char *buf = Std$String$flatten(Args[7].Val);
	int rowstride = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int xdith = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int ydith = ((Std$Integer_smallt *)Args[10].Val)->Value;
	gdk_draw_rgb_32_image_dithalign(self, gc, x, y, width, height, dith, buf, rowstride, xdith, ydith);
	return SUCCESS;
};

METHOD("DrawRgbImage", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$RgbDither$T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[5].Val)->Value;
	GdkRgbDither dith = ((Std$Integer_smallt *)Args[6].Val)->Value;
	char *rgb_buf = Std$String$flatten(Args[7].Val);
	int rowstride = ((Std$Integer_smallt *)Args[8].Val)->Value;
	gdk_draw_rgb_image(self, gc, x, y, width, height, dith, rgb_buf, rowstride);
	return SUCCESS;
};

METHOD("DrawRgbImageDithalign", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$RgbDither$T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[5].Val)->Value;
	GdkRgbDither dith = ((Std$Integer_smallt *)Args[6].Val)->Value;
	char *rgb_buf = Std$String$flatten(Args[7].Val);
	int rowstride = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int xdith = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int ydith = ((Std$Integer_smallt *)Args[10].Val)->Value;
	gdk_draw_rgb_image_dithalign(self, gc, x, y, width, height, dith, rgb_buf, rowstride, xdith, ydith);
	return SUCCESS;
};

METHOD("DrawSegments", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Gtk$Gdk$Segment$T, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkSegment * segs= &((Gtk$Gdk$Segment_t *)Args[2].Val)->Value;
	int nsegs = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_draw_segments(self, gc, segs, nsegs);
	return SUCCESS;
};

METHOD("DrawString", TYP, T, TYP, Gtk$Gdk$Font$T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$String$T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[1].Val)->Value;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	char *string = Std$String$flatten(Args[5].Val);
	gdk_draw_string(self, font, gc, x, y, string);
	return SUCCESS;
};

METHOD("DrawText", TYP, T, TYP, Gtk$Gdk$Font$T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[1].Val)->Value;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	char *text = Std$String$flatten(Args[5].Val);
	int text_length = ((Std$Integer_smallt *)Args[6].Val)->Value;
	gdk_draw_text(self, font, gc, x, y, text, text_length);
	return SUCCESS;
};

METHOD("DrawTextWc", TYP, T, TYP, Gtk$Gdk$Font$T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[1].Val)->Value;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	const GdkWChar* text = 0;
	int text_length = ((Std$Integer_smallt *)Args[6].Val)->Value;
	gdk_draw_text_wc(self, font, gc, x, y, text, text_length);
	return SUCCESS;
};

METHOD("DrawTrapezoids", TYP, T, TYP, Gtk$Gdk$GC$T, TYP, Gtk$Gdk$Trapezoid$T, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkTrapezoid * trapezoids= &((Gtk$Gdk$Trapezoid_t *)Args[2].Val)->Value;
	int n_trapezoids = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_draw_trapezoids(self, gc, trapezoids, n_trapezoids);
	return SUCCESS;
};

METHOD("CopyToImage", TYP, T, TYP, Gtk$Gdk$Image$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkImage * image = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int src_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int src_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int dest_x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int dest_y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[7].Val)->Value;
	GdkImage * result = gdk_drawable_copy_to_image(self, image, src_x, src_y, dest_x, dest_y, width, height);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetClipRegion", TYP, T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRegion * result = gdk_drawable_get_clip_region(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetColormap", TYP, T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * result = gdk_drawable_get_colormap(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetData", TYP, T, TYP, Std$String$T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	void * result = gdk_drawable_get_data(self, key);
	Result->Val = Std$Address$new(result);
	return SUCCESS;
};

METHOD("GetDepth", TYP, T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_drawable_get_depth(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetDisplay", TYP, T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDisplay * result = gdk_drawable_get_display(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetImage", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GdkImage * result = gdk_drawable_get_image(self, x, y, width, height);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetScreen", TYP, T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkScreen * result = gdk_drawable_get_screen(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetSize", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* width = 0;
	gint* height = 0;
	gdk_drawable_get_size(self, width, height);
	return SUCCESS;
};

METHOD("GetVisibleRegion", TYP, T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRegion * result = gdk_drawable_get_visible_region(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetVisual", TYP, T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkVisual * result = gdk_drawable_get_visual(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDrawable * result = gdk_drawable_ref(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("SetColormap", TYP, T, TYP, Gtk$Gdk$Colormap$T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdk_drawable_set_colormap(self, colormap);
	return SUCCESS;
};

METHOD("SetData", TYP, T, TYP, Std$String$T, TYP, Std$Address$T, TYP, Std$Object$T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GDestroyNotify destroy_func = 0;
	gdk_drawable_set_data(self, key, data, destroy_func);
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GdkDrawable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_drawable_unref(self);
	return SUCCESS;
};

