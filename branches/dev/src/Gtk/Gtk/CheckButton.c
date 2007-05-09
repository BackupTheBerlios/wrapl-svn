#include <Gtk/Gtk/CheckButton.h>

TYPE(T, Gtk$Gtk$ToggleButton$T, Gtk$Gtk$Button$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_check_button_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithLabel, 1) {
	GtkWidget *Handle = gtk_check_button_new_with_label(Lang$String$flatten(Args[0].Val));
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithMnemonic, 1) {
	GtkWidget *Handle = gtk_check_button_new_with_mnemonic(Lang$String$flatten(Args[0].Val));
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};
