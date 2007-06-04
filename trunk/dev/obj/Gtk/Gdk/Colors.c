#include <Gtk/Gdk/Colors.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Std/Boolean.h>
#include <Gtk/Gdk/Colormap.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Color.h>
/***********************************/
GLOBAL_FUNCTION(Alloc, 6) {
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int contiguous = Args[1].Val == $true;
	gulong* planes = 0;
	int nplanes = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gulong* pixels = 0;
	int npixels = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int result = gdk_colors_alloc(colormap, contiguous, planes, nplanes, pixels, npixels);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Free, 4) {
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gulong* pixels = 0;
	int npixels = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int planes = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_colors_free(colormap, pixels, npixels, planes);
	return SUCCESS;
};

GLOBAL_FUNCTION(Store, 3) {
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * colors= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	int ncolors = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_colors_store(colormap, colors, ncolors);
	return SUCCESS;
};

