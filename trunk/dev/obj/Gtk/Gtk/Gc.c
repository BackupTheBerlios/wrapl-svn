#include <Gtk/Gtk/Gc.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/Gdk/GC.h>
#include <Gtk/Gdk/Colormap.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/GCValues.h>
/***********************************/
GLOBAL_FUNCTION(Get, 4) {
	int depth = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkGCValues * values= &((Gtk$Gdk$GCValues_t *)Args[2].Val)->Value;
	int values_mask = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkGC * result = gtk_gc_get(depth, colormap, values, values_mask);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Release, 1) {
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_gc_release(gc);
	return SUCCESS;
};

