#include <Gtk/Gtk/Pixmap.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Bitmap.h>
#include <Gtk/Gdk/Pixmap.h>
#include <Gtk/Gtk/Pixmap.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Misc$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 2) {
	GdkPixmap * pixmap = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkPixmap * result = gtk_pixmap_new(pixmap, mask);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_pixmap_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Get", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkPixmap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixmap** val = 0;
	GdkBitmap** mask = 0;
	gtk_pixmap_get(self, val, mask);
	return SUCCESS;
};

METHOD("Set", TYP, T, TYP, Gtk$Gdk$Pixmap$T, TYP, Gtk$Gdk$Bitmap$T) {
	GtkPixmap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixmap * val = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_pixmap_set(self, val, mask);
	return SUCCESS;
};

METHOD("SetBuildInsensitive", TYP, T, TYP, Std$Symbol$T) {
	GtkPixmap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int build = Args[1].Val == $true;
	gtk_pixmap_set_build_insensitive(self, build);
	return SUCCESS;
};

