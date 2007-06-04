#include <Gtk/Gtk/StatusIcon.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 8
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/StatusIcon.h>
#include <Gtk/Gtk/ImageType.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/Menu.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkStatusIcon * result = gtk_status_icon_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromFile, 1) {
	char *filename = Std$String$flatten(Args[0].Val);
	GtkStatusIcon * result = gtk_status_icon_new_from_file(filename);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromIconName, 1) {
	char *icon_name = Std$String$flatten(Args[0].Val);
	GtkStatusIcon * result = gtk_status_icon_new_from_icon_name(icon_name);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromPixbuf, 1) {
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkStatusIcon * result = gtk_status_icon_new_from_pixbuf(pixbuf);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromStock, 1) {
	char *stock_id = Std$String$flatten(Args[0].Val);
	GtkStatusIcon * result = gtk_status_icon_new_from_stock(stock_id);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_status_icon_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(PositionMenu, 5) {
	GtkMenu * menu = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* x = 0;
	gint* y = 0;
	gboolean* push_in = 0;
	void *user_data = ((Std$Address_t *)Args[4].Val)->Value;
	gtk_status_icon_position_menu(menu, x, y, push_in, user_data);
	return SUCCESS;
};

METHOD("GetBlinking", TYP, T) {
	GtkStatusIcon * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_status_icon_get_blinking(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetGeometry", TYP, T, TYP, Std$Object$T, TYP, Gtk$Gdk$Rectangle$T, TYP, Std$Object$T) {
	GtkStatusIcon * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkScreen** screen = 0;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[2].Val)->Value;
	GtkOrientation* orientation = 0;
	int result = gtk_status_icon_get_geometry(self, screen, area, orientation);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetIconName", TYP, T) {
	GtkStatusIcon * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_status_icon_get_icon_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetPixbuf", TYP, T) {
	GtkStatusIcon * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * result = gtk_status_icon_get_pixbuf(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetSize", TYP, T) {
	GtkStatusIcon * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_status_icon_get_size(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetStock", TYP, T) {
	GtkStatusIcon * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_status_icon_get_stock(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetStorageType", TYP, T) {
	GtkStatusIcon * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkImageType result = gtk_status_icon_get_storage_type(self);
	Gtk$Gtk$ImageType_t *_result = new(Gtk$Gtk$ImageType_t);
	_result->Type = Gtk$Gtk$ImageType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetVisible", TYP, T) {
	GtkStatusIcon * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_status_icon_get_visible(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsEmbedded", TYP, T) {
	GtkStatusIcon * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_status_icon_is_embedded(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetBlinking", TYP, T, TYP, Std$Symbol$T) {
	GtkStatusIcon * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int blinking = Args[1].Val == $true;
	gtk_status_icon_set_blinking(self, blinking);
	return SUCCESS;
};

METHOD("SetFromFile", TYP, T, TYP, Std$String$T) {
	GtkStatusIcon * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *filename = Std$String$flatten(Args[1].Val);
	gtk_status_icon_set_from_file(self, filename);
	return SUCCESS;
};

METHOD("SetFromIconName", TYP, T, TYP, Std$String$T) {
	GtkStatusIcon * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *icon_name = Std$String$flatten(Args[1].Val);
	gtk_status_icon_set_from_icon_name(self, icon_name);
	return SUCCESS;
};

METHOD("SetFromPixbuf", TYP, T, TYP, Gtk$Gdk$Pixbuf$T) {
	GtkStatusIcon * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_status_icon_set_from_pixbuf(self, pixbuf);
	return SUCCESS;
};

METHOD("SetFromStock", TYP, T, TYP, Std$String$T) {
	GtkStatusIcon * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *stock_id = Std$String$flatten(Args[1].Val);
	gtk_status_icon_set_from_stock(self, stock_id);
	return SUCCESS;
};

METHOD("SetTooltip", TYP, T, TYP, Std$String$T) {
	GtkStatusIcon * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *tooltip_text = Std$String$flatten(Args[1].Val);
	gtk_status_icon_set_tooltip(self, tooltip_text);
	return SUCCESS;
};

METHOD("SetVisible", TYP, T, TYP, Std$Symbol$T) {
	GtkStatusIcon * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int visible = Args[1].Val == $true;
	gtk_status_icon_set_visible(self, visible);
	return SUCCESS;
};

