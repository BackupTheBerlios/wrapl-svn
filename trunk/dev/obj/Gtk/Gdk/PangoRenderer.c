#include <Gtk/Gdk/PangoRenderer.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 10
#include <Gtk/Gdk/PangoRenderer.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Drawable.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/Pango/Renderer.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/RenderPart.h>
#include <Gtk/Gdk/Screen.h>
#include <Gtk/Gdk/Bitmap.h>
#include <Gtk/Gdk/GC.h>
/***********************************/
TYPE(T, Gtk$Pango$Renderer$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPangoRenderer * result = gdk_pango_renderer_new(screen);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetDefault, 1) {
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoRenderer * result = gdk_pango_renderer_get_default(screen);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_pango_renderer_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("SetDrawable", TYP, T, TYP, Gtk$Gdk$Drawable$T) {
	GdkPangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDrawable * drawable = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdk_pango_renderer_set_drawable(self, drawable);
	return SUCCESS;
};

METHOD("SetGc", TYP, T, TYP, Gtk$Gdk$GC$T) {
	GdkPangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdk_pango_renderer_set_gc(self, gc);
	return SUCCESS;
};

METHOD("SetOverrideColor", TYP, T, TYP, Gtk$Pango$RenderPart$T, TYP, Gtk$Gdk$Color$T) {
	GdkPangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoRenderPart part = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[2].Val)->Value;
	gdk_pango_renderer_set_override_color(self, part, color);
	return SUCCESS;
};

METHOD("SetStipple", TYP, T, TYP, Gtk$Pango$RenderPart$T, TYP, Gtk$Gdk$Bitmap$T) {
	GdkPangoRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoRenderPart part = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkBitmap * stipple = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gdk_pango_renderer_set_stipple(self, part, stipple);
	return SUCCESS;
};

