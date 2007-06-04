#include <Gtk/Gtk/VBox.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Std/Boolean.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$Box$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 2) {
	int homogeneous = Args[0].Val == $true;
	int spacing = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkVBox * result = gtk_vbox_new(homogeneous, spacing);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_vbox_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

