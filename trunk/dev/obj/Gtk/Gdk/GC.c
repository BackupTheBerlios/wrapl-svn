#include <Gtk/Gdk/GC.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 21
#include <Gtk/Gdk/GC.h>
#include <Gtk/Gdk/JoinStyle.h>
#include <Gtk/Gdk/Colormap.h>
#include <Gtk/Gdk/SubwindowMode.h>
#include <Gtk/Gdk/CapStyle.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Drawable.h>
#include <Gtk/Gdk/LineStyle.h>
#include <Gtk/Gdk/GCValues.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/Gdk/Function.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Gtk/Gdk/Screen.h>
#include <Gtk/Gdk/Region.h>
#include <Gtk/Gdk/Bitmap.h>
#include <Gtk/Gdk/Pixmap.h>
#include <Std/Boolean.h>
#include <Gtk/Gdk/GC.h>
#include <Gtk/Gdk/Fill.h>
#include <Gtk/Gdk/Font.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	GdkDrawable * drawable = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * result = gdk_gc_new(drawable);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithValues, 3) {
	GdkDrawable * drawable = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGCValues * values= &((Gtk$Gdk$GCValues_t *)Args[1].Val)->Value;
	int values_mask = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkGC * result = gdk_gc_new_with_values(drawable, values, values_mask);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_gc_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T, TYP, Gtk$Gdk$GC$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * src_gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdk_gc_copy(self, src_gc);
	return SUCCESS;
};

METHOD("GetColormap", TYP, T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * result = gdk_gc_get_colormap(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetScreen", TYP, T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkScreen * result = gdk_gc_get_screen(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetValues", TYP, T, TYP, Gtk$Gdk$GCValues$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGCValues * values= &((Gtk$Gdk$GCValues_t *)Args[1].Val)->Value;
	gdk_gc_get_values(self, values);
	return SUCCESS;
};

METHOD("Offset", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x_offset = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y_offset = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_gc_offset(self, x_offset, y_offset);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * result = gdk_gc_ref(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("SetBackground", TYP, T, TYP, Gtk$Gdk$Color$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	gdk_gc_set_background(self, color);
	return SUCCESS;
};

METHOD("SetClipMask", TYP, T, TYP, Gtk$Gdk$Bitmap$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdk_gc_set_clip_mask(self, mask);
	return SUCCESS;
};

METHOD("SetClipOrigin", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_gc_set_clip_origin(self, x, y);
	return SUCCESS;
};

METHOD("SetClipRectangle", TYP, T, TYP, Gtk$Gdk$Rectangle$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRectangle * rectangle= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	gdk_gc_set_clip_rectangle(self, rectangle);
	return SUCCESS;
};

METHOD("SetClipRegion", TYP, T, TYP, Gtk$Gdk$Region$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRegion * region= ((Gtk$Gdk$Region_t *)Args[1].Val)->Value;
	gdk_gc_set_clip_region(self, region);
	return SUCCESS;
};

METHOD("SetColormap", TYP, T, TYP, Gtk$Gdk$Colormap$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdk_gc_set_colormap(self, colormap);
	return SUCCESS;
};

METHOD("SetDashes", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Integer$SmallT) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int dash_offset = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gint8* dash_list = 0;
	int n = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_gc_set_dashes(self, dash_offset, dash_list, n);
	return SUCCESS;
};

METHOD("SetExposures", TYP, T, TYP, Std$Symbol$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int exposures = Args[1].Val == $true;
	gdk_gc_set_exposures(self, exposures);
	return SUCCESS;
};

METHOD("SetFill", TYP, T, TYP, Gtk$Gdk$Fill$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkFill fill = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_gc_set_fill(self, fill);
	return SUCCESS;
};

METHOD("SetFont", TYP, T, TYP, Gtk$Gdk$Font$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[1].Val)->Value;
	gdk_gc_set_font(self, font);
	return SUCCESS;
};

METHOD("SetForeground", TYP, T, TYP, Gtk$Gdk$Color$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	gdk_gc_set_foreground(self, color);
	return SUCCESS;
};

METHOD("SetFunction", TYP, T, TYP, Gtk$Gdk$Function$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkFunction function = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_gc_set_function(self, function);
	return SUCCESS;
};

METHOD("SetLineAttributes", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$LineStyle$T, TYP, Gtk$Gdk$CapStyle$T, TYP, Gtk$Gdk$JoinStyle$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int line_width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkLineStyle line_style = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkCapStyle cap_style = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkJoinStyle join_style = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gdk_gc_set_line_attributes(self, line_width, line_style, cap_style, join_style);
	return SUCCESS;
};

METHOD("SetRgbBgColor", TYP, T, TYP, Gtk$Gdk$Color$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	gdk_gc_set_rgb_bg_color(self, color);
	return SUCCESS;
};

METHOD("SetRgbFgColor", TYP, T, TYP, Gtk$Gdk$Color$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	gdk_gc_set_rgb_fg_color(self, color);
	return SUCCESS;
};

METHOD("SetStipple", TYP, T, TYP, Gtk$Gdk$Pixmap$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixmap * stipple = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdk_gc_set_stipple(self, stipple);
	return SUCCESS;
};

METHOD("SetSubwindow", TYP, T, TYP, Gtk$Gdk$SubwindowMode$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkSubwindowMode mode = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_gc_set_subwindow(self, mode);
	return SUCCESS;
};

METHOD("SetTile", TYP, T, TYP, Gtk$Gdk$Pixmap$T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixmap * tile = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdk_gc_set_tile(self, tile);
	return SUCCESS;
};

METHOD("SetTsOrigin", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_gc_set_ts_origin(self, x, y);
	return SUCCESS;
};

METHOD("SetValues", TYP, T, TYP, Gtk$Gdk$GCValues$T, TYP, Std$Integer$SmallT) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGCValues * values= &((Gtk$Gdk$GCValues_t *)Args[1].Val)->Value;
	int values_mask = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_gc_set_values(self, values, values_mask);
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GdkGC * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_gc_unref(self);
	return SUCCESS;
};

