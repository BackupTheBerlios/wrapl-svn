#include <Gtk/Gdk/Image.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/Gdk/Colormap.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Drawable.h>
#include <Gtk/Gdk/Image.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/ImageType.h>
#include <Gtk/Gdk/Visual.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 4) {
	GdkImageType type = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GdkVisual * visual = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int width = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkImage * result = gdk_image_new(type, visual, width, height);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(Get, 5) {
	GdkDrawable * drawable = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GdkImage * result = gdk_image_get(drawable, x, y, width, height);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_image_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetColormap", TYP, T) {
	GdkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * result = gdk_image_get_colormap(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPixel", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gdk_image_get_pixel(self, x, y);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("PutPixel", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int pixel = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_image_put_pixel(self, x, y, pixel);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GdkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkImage * result = gdk_image_ref(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("SetColormap", TYP, T, TYP, Gtk$Gdk$Colormap$T) {
	GdkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdk_image_set_colormap(self, colormap);
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GdkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_image_unref(self);
	return SUCCESS;
};

