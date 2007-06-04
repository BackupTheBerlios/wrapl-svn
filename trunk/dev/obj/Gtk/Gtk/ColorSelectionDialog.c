#include <Gtk/Gtk/ColorSelectionDialog.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 2
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$Dialog$T, Gtk$Gtk$Window$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	char *title = Std$String$flatten(Args[0].Val);
	GtkColorSelectionDialog * result = gtk_color_selection_dialog_new(title);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_color_selection_dialog_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

