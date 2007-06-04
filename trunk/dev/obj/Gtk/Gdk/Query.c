#include <Gtk/Gdk/Query.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 1
#include <Gtk/GObject/Object.h>
/***********************************/
GLOBAL_FUNCTION(Depths, 2) {
	gint** depths = 0;
	gint* count = 0;
	gdk_query_depths(depths, count);
	return SUCCESS;
};

GLOBAL_FUNCTION(VisualTypes, 2) {
	GdkVisualType** visual_types = 0;
	gint* count = 0;
	gdk_query_visual_types(visual_types, count);
	return SUCCESS;
};

