#include <Gtk/Gdk/Rgb.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/Gdk/Visual.h>
#include <Std/Boolean.h>
#include <Gtk/Gdk/GC.h>
#include <Gtk/Gdk/Colormap.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Color.h>
/***********************************/
GLOBAL_FUNCTION(ColormapDitherable, 1) {
	GdkColormap * cmap = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_rgb_colormap_ditherable(cmap);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(Ditherable, 0) {
	int result = gdk_rgb_ditherable();
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(FindColor, 2) {
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	gdk_rgb_find_color(colormap, color);
	return SUCCESS;
};

GLOBAL_FUNCTION(GcSetBackground, 2) {
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int rgb = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_rgb_gc_set_background(gc, rgb);
	return SUCCESS;
};

GLOBAL_FUNCTION(GcSetForeground, 2) {
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int rgb = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_rgb_gc_set_foreground(gc, rgb);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetColormap, 0) {
	GdkColormap * result = gdk_rgb_get_colormap();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetVisual, 0) {
	GdkVisual * result = gdk_rgb_get_visual();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Init, 0) {
	gdk_rgb_init();
	return SUCCESS;
};

GLOBAL_FUNCTION(SetInstall, 1) {
	int install = Args[0].Val == $true;
	gdk_rgb_set_install(install);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetMinColors, 1) {
	int min_colors = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gdk_rgb_set_min_colors(min_colors);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetVerbose, 1) {
	int verbose = Args[0].Val == $true;
	gdk_rgb_set_verbose(verbose);
	return SUCCESS;
};

GLOBAL_FUNCTION(XpixelFromRgb, 1) {
	int rgb = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int result = gdk_rgb_xpixel_from_rgb(rgb);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

