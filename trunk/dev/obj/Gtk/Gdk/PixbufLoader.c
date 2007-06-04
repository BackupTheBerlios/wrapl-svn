#include <Gtk/Gdk/PixbufLoader.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/Gdk/Pixbuf.h>
#include <Std/Boolean.h>
#include <Gtk/Gdk/PixbufLoader.h>
#include <Gtk/Gdk/PixbufFormat.h>
#include <Gtk/Gdk/PixbufAnimation.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GdkPixbufLoader * result = gdk_pixbuf_loader_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithMimeType, 2) {
	char *mime_type = Std$String$flatten(Args[0].Val);
	GError** error = 0;
	GdkPixbufLoader * result = gdk_pixbuf_loader_new_with_mime_type(mime_type, error);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithType, 2) {
	char *image_type = Std$String$flatten(Args[0].Val);
	GError** error = 0;
	GdkPixbufLoader * result = gdk_pixbuf_loader_new_with_type(image_type, error);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_pixbuf_loader_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Close", TYP, T, TYP, Std$Object$T) {
	GdkPixbufLoader * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GError** error = 0;
	int result = gdk_pixbuf_loader_close(self, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetAnimation", TYP, T) {
	GdkPixbufLoader * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbufAnimation * result = gdk_pixbuf_loader_get_animation(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetFormat", TYP, T) {
	GdkPixbufLoader * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbufFormat * result = gdk_pixbuf_loader_get_format(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetPixbuf", TYP, T) {
	GdkPixbufLoader * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * result = gdk_pixbuf_loader_get_pixbuf(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("SetSize", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkPixbufLoader * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_pixbuf_loader_set_size(self, width, height);
	return SUCCESS;
};

METHOD("Write", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GdkPixbufLoader * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *buf = Std$String$flatten(Args[1].Val);
	int count = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GError** error = 0;
	int result = gdk_pixbuf_loader_write(self, buf, count, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

