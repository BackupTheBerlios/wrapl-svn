#include <Gtk/Gdk/PixbufAnimationIter.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Std/Boolean.h>
#include <Gtk/Gdk/PixbufAnimationIter.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Pixbuf.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_pixbuf_animation_iter_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Advance", TYP, T, TYP, Std$Object$T) {
	GdkPixbufAnimationIter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const GTimeVal* current_time = 0;
	int result = gdk_pixbuf_animation_iter_advance(self, current_time);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetDelayTime", TYP, T) {
	GdkPixbufAnimationIter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_pixbuf_animation_iter_get_delay_time(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetPixbuf", TYP, T) {
	GdkPixbufAnimationIter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * result = gdk_pixbuf_animation_iter_get_pixbuf(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("OnCurrentlyLoadingFrame", TYP, T) {
	GdkPixbufAnimationIter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_pixbuf_animation_iter_on_currently_loading_frame(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

