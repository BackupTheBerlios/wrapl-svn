#include <Gtk/Gdk/PixbufSimpleAnim.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/Gdk/PixbufSimpleAnim.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Pixbuf.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 3) {
	int width = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double rate = ((Std$Real_t *)Args[2].Val)->Value;
	GdkPixbufSimpleAnim * result = gdk_pixbuf_simple_anim_new(width, height, rate);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_pixbuf_simple_anim_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(IterGetType, 0) {
	GType result = gdk_pixbuf_simple_anim_iter_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddFrame", TYP, T, TYP, Gtk$Gdk$Pixbuf$T) {
	GdkPixbufSimpleAnim * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdk_pixbuf_simple_anim_add_frame(self, pixbuf);
	return SUCCESS;
};

