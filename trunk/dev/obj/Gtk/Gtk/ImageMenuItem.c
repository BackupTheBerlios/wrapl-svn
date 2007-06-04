#include <Gtk/Gtk/ImageMenuItem.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/Gtk/ImageMenuItem.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/AccelGroup.h>
#include <Gtk/Gtk/Widget.h>
/***********************************/
TYPE(T, Gtk$Gtk$MenuItem$T, Gtk$Gtk$Item$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkImageMenuItem * result = gtk_image_menu_item_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromStock, 2) {
	char *stock_id = Std$String$flatten(Args[0].Val);
	GtkAccelGroup * accel_group = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkImageMenuItem * result = gtk_image_menu_item_new_from_stock(stock_id, accel_group);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithLabel, 1) {
	char *label = Std$String$flatten(Args[0].Val);
	GtkImageMenuItem * result = gtk_image_menu_item_new_with_label(label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithMnemonic, 1) {
	char *label = Std$String$flatten(Args[0].Val);
	GtkImageMenuItem * result = gtk_image_menu_item_new_with_mnemonic(label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_image_menu_item_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetImage", TYP, T) {
	GtkImageMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_image_menu_item_get_image(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("SetImage", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkImageMenuItem * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * image = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_image_menu_item_set_image(self, image);
	return SUCCESS;
};

