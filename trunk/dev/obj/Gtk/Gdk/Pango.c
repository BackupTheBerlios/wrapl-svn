#include <Gtk/Gdk/Pango.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/Gdk/Colormap.h>
#include <Gtk/Pango/LayoutLine.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Layout.h>
#include <Gtk/Pango/Context.h>
#include <Gtk/Gdk/Screen.h>
#include <Gtk/Gdk/Region.h>
/***********************************/
GLOBAL_FUNCTION(ContextGet, 0) {
	PangoContext * result = gdk_pango_context_get();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ContextGetForScreen, 1) {
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoContext * result = gdk_pango_context_get_for_screen(screen);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ContextSetColormap, 2) {
	PangoContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdk_pango_context_set_colormap(context, colormap);
	return SUCCESS;
};

GLOBAL_FUNCTION(LayoutGetClipRegion, 5) {
	PangoLayout * layout = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x_origin = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y_origin = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gint* index_ranges = 0;
	int n_ranges = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GdkRegion * result = gdk_pango_layout_get_clip_region(layout, x_origin, y_origin, index_ranges, n_ranges);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(LayoutLineGetClipRegion, 5) {
	PangoLayoutLine * line= ((Gtk$Pango$LayoutLine_t *)Args[0].Val)->Value;
	int x_origin = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y_origin = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gint* index_ranges = 0;
	int n_ranges = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GdkRegion * result = gdk_pango_layout_line_get_clip_region(line, x_origin, y_origin, index_ranges, n_ranges);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

