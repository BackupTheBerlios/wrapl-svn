#include <Gtk/Gdk/RgbCmap.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 2
#include <Gtk/Gdk/RgbCmap.h>
#include <Gtk/GObject/Object.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 2) {
	guint32* colors = 0;
	int n_colors = ((Std$Integer_smallt *)Args[1].Val)->Value;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gdk_rgb_cmap_new(colors, n_colors);
	Result->Val= result;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	GdkRgbCmap * self= ((Gtk$Gdk$RgbCmap_t *)Args[0].Val)->Value;
	gdk_rgb_cmap_free(self);
	return SUCCESS;
};

