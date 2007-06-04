#include <Gtk/Gtk/IconInfo.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/IconInfo.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_icon_info_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GtkIconInfo * self= ((Gtk$Gtk$IconInfo_t *)Args[0].Val)->Value;
	GtkIconInfo * result = gtk_icon_info_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	GtkIconInfo * self= ((Gtk$Gtk$IconInfo_t *)Args[0].Val)->Value;
	gtk_icon_info_free(self);
	return SUCCESS;
};

METHOD("GetAttachPoints", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkIconInfo * self= ((Gtk$Gtk$IconInfo_t *)Args[0].Val)->Value;
	GdkPoint** points = 0;
	gint* n_points = 0;
	int result = gtk_icon_info_get_attach_points(self, points, n_points);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetBaseSize", TYP, T) {
	GtkIconInfo * self= ((Gtk$Gtk$IconInfo_t *)Args[0].Val)->Value;
	int result = gtk_icon_info_get_base_size(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetBuiltinPixbuf", TYP, T) {
	GtkIconInfo * self= ((Gtk$Gtk$IconInfo_t *)Args[0].Val)->Value;
	GdkPixbuf * result = gtk_icon_info_get_builtin_pixbuf(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetDisplayName", TYP, T) {
	GtkIconInfo * self= ((Gtk$Gtk$IconInfo_t *)Args[0].Val)->Value;
	const char * result = gtk_icon_info_get_display_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetEmbeddedRect", TYP, T, TYP, Gtk$Gdk$Rectangle$T) {
	GtkIconInfo * self= ((Gtk$Gtk$IconInfo_t *)Args[0].Val)->Value;
	GdkRectangle * rectangle= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	int result = gtk_icon_info_get_embedded_rect(self, rectangle);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetFilename", TYP, T) {
	GtkIconInfo * self= ((Gtk$Gtk$IconInfo_t *)Args[0].Val)->Value;
	const char * result = gtk_icon_info_get_filename(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("LoadIcon", TYP, T, TYP, Std$Object$T) {
	GtkIconInfo * self= ((Gtk$Gtk$IconInfo_t *)Args[0].Val)->Value;
	GError** error = 0;
	GdkPixbuf * result = gtk_icon_info_load_icon(self, error);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("SetRawCoordinates", TYP, T, TYP, Std$Symbol$T) {
	GtkIconInfo * self= ((Gtk$Gtk$IconInfo_t *)Args[0].Val)->Value;
	int raw_coordinates = Args[1].Val == $true;
	gtk_icon_info_set_raw_coordinates(self, raw_coordinates);
	return SUCCESS;
};

