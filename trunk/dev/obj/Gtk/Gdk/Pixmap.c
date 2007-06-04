#include <Gtk/Gdk/Pixmap.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 8
#include <Gtk/Gdk/Colormap.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Drawable.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Screen.h>
#include <Gtk/Gdk/Pixmap.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 4) {
	GdkDrawable * drawable = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int depth = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkPixmap * result = gdk_pixmap_new(drawable, width, height, depth);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(ColormapCreateFromXpm, 5) {
	GdkDrawable * drawable = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkBitmap** mask = 0;
	GdkColor * transparent_color= &((Gtk$Gdk$Color_t *)Args[3].Val)->Value;
	char *filename = Std$String$flatten(Args[4].Val);
	GdkPixmap * result = gdk_pixmap_colormap_create_from_xpm(drawable, colormap, mask, transparent_color, filename);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ColormapCreateFromXpmD, 5) {
	GdkDrawable * drawable = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkBitmap** mask = 0;
	GdkColor * transparent_color= &((Gtk$Gdk$Color_t *)Args[3].Val)->Value;
	const char * const * data;
	GdkPixmap * result = gdk_pixmap_colormap_create_from_xpm_d(drawable, colormap, mask, transparent_color, data);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(CreateFromData, 7) {
	GdkDrawable * drawable = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *data = Std$String$flatten(Args[1].Val);
	int width = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int depth = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GdkColor * fg= &((Gtk$Gdk$Color_t *)Args[5].Val)->Value;
	GdkColor * bg= &((Gtk$Gdk$Color_t *)Args[6].Val)->Value;
	GdkPixmap * result = gdk_pixmap_create_from_data(drawable, data, width, height, depth, fg, bg);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(CreateFromXpm, 4) {
	GdkDrawable * drawable = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkBitmap** mask = 0;
	GdkColor * transparent_color= &((Gtk$Gdk$Color_t *)Args[2].Val)->Value;
	char *filename = Std$String$flatten(Args[3].Val);
	GdkPixmap * result = gdk_pixmap_create_from_xpm(drawable, mask, transparent_color, filename);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(CreateFromXpmD, 4) {
	GdkDrawable * drawable = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkBitmap** mask = 0;
	GdkColor * transparent_color= &((Gtk$Gdk$Color_t *)Args[2].Val)->Value;
	const char * const * data;
	GdkPixmap * result = gdk_pixmap_create_from_xpm_d(drawable, mask, transparent_color, data);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ForeignNew, 1) {
	GdkNativeWindow anid = 0;
	GdkPixmap * result = gdk_pixmap_foreign_new(anid);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ForeignNewForDisplay, 2) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkNativeWindow anid = 0;
	GdkPixmap * result = gdk_pixmap_foreign_new_for_display(display, anid);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ForeignNewForScreen, 5) {
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkNativeWindow anid = 0;
	int width = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int depth = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GdkPixmap * result = gdk_pixmap_foreign_new_for_screen(screen, anid, width, height, depth);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_pixmap_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Lookup, 1) {
	GdkNativeWindow anid = 0;
	GdkPixmap * result = gdk_pixmap_lookup(anid);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(LookupForDisplay, 2) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkNativeWindow anid = 0;
	GdkPixmap * result = gdk_pixmap_lookup_for_display(display, anid);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

