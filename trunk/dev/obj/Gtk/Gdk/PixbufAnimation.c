#include <Gtk/Gdk/PixbufAnimation.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Std/Boolean.h>
#include <Gtk/Gdk/PixbufAnimationIter.h>
#include <Gtk/Gdk/PixbufAnimation.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Pixbuf.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(NewFromFile, 2) {
	char *filename = Std$String$flatten(Args[0].Val);
	GError** error = 0;
	GdkPixbufAnimation * result = gdk_pixbuf_animation_new_from_file(filename, error);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_pixbuf_animation_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetHeight", TYP, T) {
	GdkPixbufAnimation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_pixbuf_animation_get_height(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetIter", TYP, T, TYP, Std$Object$T) {
	GdkPixbufAnimation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const GTimeVal* start_time = 0;
	GdkPixbufAnimationIter * result = gdk_pixbuf_animation_get_iter(self, start_time);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetStaticImage", TYP, T) {
	GdkPixbufAnimation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * result = gdk_pixbuf_animation_get_static_image(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetWidth", TYP, T) {
	GdkPixbufAnimation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_pixbuf_animation_get_width(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("IsStaticImage", TYP, T) {
	GdkPixbufAnimation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_pixbuf_animation_is_static_image(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GdkPixbufAnimation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbufAnimation * result = gdk_pixbuf_animation_ref(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GdkPixbufAnimation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_pixbuf_animation_unref(self);
	return SUCCESS;
};

