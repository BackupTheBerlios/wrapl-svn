#include <Gtk/Gtk/MenuItem.h>
#include <Gtk/Gtk/Menu.h>

TYPE(T, Gtk$Gtk$Item$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = (Count > 0) ? gtk_menu_item_new_with_label(Lang$String$flatten(Args[0].Val)) : gtk_menu_item_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};

METHOD("submenu", TYP, T, TYP, Gtk$Gtk$Menu$T) {
	GtkMenuItem *MenuItem = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget *SubMenu = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_menu_item_set_submenu(MenuItem, SubMenu);
	Result->Arg = Args[1];
	return SUCCESS;
};

METHOD("submenu", TYP, T) {
	GtkMenuItem *MenuItem = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget *SubMenu = gtk_menu_item_get_submenu(MenuItem);
	Result->Val = Gtk$GObject$Object$gtk_to_riva(SubMenu);
	return SUCCESS;
};
