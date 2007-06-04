#include <Gtk/Gtk/Fixed.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/Fixed.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkFixed * result = gtk_fixed_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_fixed_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetHasWindow", TYP, T) {
	GtkFixed * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_fixed_get_has_window(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Move", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkFixed * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_fixed_move(self, widget, x, y);
	return SUCCESS;
};

METHOD("Put", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkFixed * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_fixed_put(self, widget, x, y);
	return SUCCESS;
};

METHOD("SetHasWindow", TYP, T, TYP, Std$Symbol$T) {
	GtkFixed * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int has_window = Args[1].Val == $true;
	gtk_fixed_set_has_window(self, has_window);
	return SUCCESS;
};

