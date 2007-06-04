#include <Gtk/Gdk/Bitmap.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Drawable.h>
#include <Gtk/Gdk/Bitmap.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(CreateFromData, 4) {
	GdkDrawable * drawable = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *data = Std$String$flatten(Args[1].Val);
	int width = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkBitmap * result = gdk_bitmap_create_from_data(drawable, data, width, height);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

