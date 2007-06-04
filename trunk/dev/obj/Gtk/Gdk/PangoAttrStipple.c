#include <Gtk/Gdk/PangoAttrStipple.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 2
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Bitmap.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 1) {
	GdkBitmap * stipple = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gdk_pango_attr_stipple_new(stipple);
	Result->Val= result;
	return SUCCESS;
};

