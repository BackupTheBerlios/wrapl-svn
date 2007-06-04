#include <Gtk/Gdk/PixbufFormat.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Std/Boolean.h>
#include <Gtk/Gdk/PixbufFormat.h>
#include <Gtk/GObject/Object.h>
/***********************************/
TYPE(T);

METHOD("GetDescription", TYP, T) {
	GdkPixbufFormat * self= ((Gtk$Gdk$PixbufFormat_t *)Args[0].Val)->Value;
	char * result = gdk_pixbuf_format_get_description(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetExtensions", TYP, T) {
	GdkPixbufFormat * self= ((Gtk$Gdk$PixbufFormat_t *)Args[0].Val)->Value;
	const char * const * result = gdk_pixbuf_format_get_extensions(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetLicense", TYP, T) {
	GdkPixbufFormat * self= ((Gtk$Gdk$PixbufFormat_t *)Args[0].Val)->Value;
	char * result = gdk_pixbuf_format_get_license(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetMimeTypes", TYP, T) {
	GdkPixbufFormat * self= ((Gtk$Gdk$PixbufFormat_t *)Args[0].Val)->Value;
	const char * const * result = gdk_pixbuf_format_get_mime_types(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetName", TYP, T) {
	GdkPixbufFormat * self= ((Gtk$Gdk$PixbufFormat_t *)Args[0].Val)->Value;
	char * result = gdk_pixbuf_format_get_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("IsDisabled", TYP, T) {
	GdkPixbufFormat * self= ((Gtk$Gdk$PixbufFormat_t *)Args[0].Val)->Value;
	int result = gdk_pixbuf_format_is_disabled(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsScalable", TYP, T) {
	GdkPixbufFormat * self= ((Gtk$Gdk$PixbufFormat_t *)Args[0].Val)->Value;
	int result = gdk_pixbuf_format_is_scalable(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsWritable", TYP, T) {
	GdkPixbufFormat * self= ((Gtk$Gdk$PixbufFormat_t *)Args[0].Val)->Value;
	int result = gdk_pixbuf_format_is_writable(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetDisabled", TYP, T, TYP, Std$Symbol$T) {
	GdkPixbufFormat * self= ((Gtk$Gdk$PixbufFormat_t *)Args[0].Val)->Value;
	int disabled = Args[1].Val == $true;
	gdk_pixbuf_format_set_disabled(self, disabled);
	return SUCCESS;
};

