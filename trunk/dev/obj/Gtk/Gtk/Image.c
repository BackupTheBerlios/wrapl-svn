#include <Gtk/Gtk/Image.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 12
#include <Gtk/Gdk/PixbufAnimation.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/IconSize.h>
#include <Gtk/Gdk/Image.h>
#include <Gtk/Gtk/IconSet.h>
#include <Gtk/Gtk/Image.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/ImageType.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Gtk/Gdk/Bitmap.h>
#include <Gtk/Gdk/Pixmap.h>
#include <Gtk/Gdk/PixbufAnimation.h>
/***********************************/
TYPE(T, Gtk$Gtk$Misc$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkImage * result = gtk_image_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromAnimation, 1) {
	GdkPixbufAnimation * animation = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkImage * result = gtk_image_new_from_animation(animation);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromFile, 1) {
	char *filename = Std$String$flatten(Args[0].Val);
	GtkImage * result = gtk_image_new_from_file(filename);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromIconName, 2) {
	char *icon_name = Std$String$flatten(Args[0].Val);
	GtkIconSize size = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkImage * result = gtk_image_new_from_icon_name(icon_name, size);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromIconSet, 2) {
	GtkIconSet * icon_set= ((Gtk$Gtk$IconSet_t *)Args[0].Val)->Value;
	GtkIconSize size = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkImage * result = gtk_image_new_from_icon_set(icon_set, size);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromImage, 2) {
	GdkImage * image = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkImage * result = gtk_image_new_from_image(image, mask);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromPixbuf, 1) {
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkImage * result = gtk_image_new_from_pixbuf(pixbuf);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromPixmap, 2) {
	GdkPixmap * pixmap = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkImage * result = gtk_image_new_from_pixmap(pixmap, mask);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromStock, 2) {
	char *stock_id = Std$String$flatten(Args[0].Val);
	GtkIconSize size = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkImage * result = gtk_image_new_from_stock(stock_id, size);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_image_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Clear", TYP, T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_image_clear(self);
	return SUCCESS;
};

METHOD("Get", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkImage** val = 0;
	GdkBitmap** mask = 0;
	gtk_image_get(self, val, mask);
	return SUCCESS;
};

METHOD("GetAnimation", TYP, T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbufAnimation * result = gtk_image_get_animation(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetIconName", TYP, T, TYP, Std$List$T, TYP, Std$Object$T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * icon_name;
	GtkIconSize* size = 0;
	gtk_image_get_icon_name(self, icon_name, size);
	return SUCCESS;
};

METHOD("GetIconSet", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkIconSet** icon_set = 0;
	GtkIconSize* size = 0;
	gtk_image_get_icon_set(self, icon_set, size);
	return SUCCESS;
};

METHOD("GetImage", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkImage** gdk_image = 0;
	GdkBitmap** mask = 0;
	gtk_image_get_image(self, gdk_image, mask);
	return SUCCESS;
};

METHOD("GetPixbuf", TYP, T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * result = gtk_image_get_pixbuf(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPixelSize", TYP, T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_image_get_pixel_size(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetPixmap", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixmap** pixmap = 0;
	GdkBitmap** mask = 0;
	gtk_image_get_pixmap(self, pixmap, mask);
	return SUCCESS;
};

METHOD("GetStock", TYP, T, TYP, Std$List$T, TYP, Std$Object$T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * stock_id;
	GtkIconSize* size = 0;
	gtk_image_get_stock(self, stock_id, size);
	return SUCCESS;
};

METHOD("GetStorageType", TYP, T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkImageType result = gtk_image_get_storage_type(self);
	Gtk$Gtk$ImageType_t *_result = new(Gtk$Gtk$ImageType_t);
	_result->Type = Gtk$Gtk$ImageType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("Set", TYP, T, TYP, Gtk$Gdk$Image$T, TYP, Gtk$Gdk$Bitmap$T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkImage * val = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_image_set(self, val, mask);
	return SUCCESS;
};

METHOD("SetFromAnimation", TYP, T, TYP, Gtk$Gdk$PixbufAnimation$T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbufAnimation * animation = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_image_set_from_animation(self, animation);
	return SUCCESS;
};

METHOD("SetFromFile", TYP, T, TYP, Std$String$T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *filename = Std$String$flatten(Args[1].Val);
	gtk_image_set_from_file(self, filename);
	return SUCCESS;
};

METHOD("SetFromIconName", TYP, T, TYP, Std$String$T, TYP, Gtk$Gtk$IconSize$T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *icon_name = Std$String$flatten(Args[1].Val);
	GtkIconSize size = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_image_set_from_icon_name(self, icon_name, size);
	return SUCCESS;
};

METHOD("SetFromIconSet", TYP, T, TYP, Gtk$Gtk$IconSet$T, TYP, Gtk$Gtk$IconSize$T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkIconSet * icon_set= ((Gtk$Gtk$IconSet_t *)Args[1].Val)->Value;
	GtkIconSize size = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_image_set_from_icon_set(self, icon_set, size);
	return SUCCESS;
};

METHOD("SetFromImage", TYP, T, TYP, Gtk$Gdk$Image$T, TYP, Gtk$Gdk$Bitmap$T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkImage * gdk_image = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_image_set_from_image(self, gdk_image, mask);
	return SUCCESS;
};

METHOD("SetFromPixbuf", TYP, T, TYP, Gtk$Gdk$Pixbuf$T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_image_set_from_pixbuf(self, pixbuf);
	return SUCCESS;
};

METHOD("SetFromPixmap", TYP, T, TYP, Gtk$Gdk$Pixmap$T, TYP, Gtk$Gdk$Bitmap$T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixmap * pixmap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_image_set_from_pixmap(self, pixmap, mask);
	return SUCCESS;
};

METHOD("SetFromStock", TYP, T, TYP, Std$String$T, TYP, Gtk$Gtk$IconSize$T) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *stock_id = Std$String$flatten(Args[1].Val);
	GtkIconSize size = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_image_set_from_stock(self, stock_id, size);
	return SUCCESS;
};

METHOD("SetPixelSize", TYP, T, TYP, Std$Integer$SmallT) {
	GtkImage * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int pixel_size = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_image_set_pixel_size(self, pixel_size);
	return SUCCESS;
};

