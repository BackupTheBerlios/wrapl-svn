#include <Gtk/Gtk/AccelLabel.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Closure.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/AccelLabel.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Label$T, Gtk$Gtk$Misc$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	char *string = Std$String$flatten(Args[0].Val);
	GtkAccelLabel * result = gtk_accel_label_new(string);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_accel_label_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetAccelWidget", TYP, T) {
	GtkAccelLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_accel_label_get_accel_widget(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetAccelWidth", TYP, T) {
	GtkAccelLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_accel_label_get_accel_width(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Refetch", TYP, T) {
	GtkAccelLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_accel_label_refetch(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetAccelClosure", TYP, T, TYP, Gtk$GObject$Closure$T) {
	GtkAccelLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GClosure *accel_closure = Gtk$GObject$Closure$new(Args[1].Val);
	gtk_accel_label_set_accel_closure(self, accel_closure);
	return SUCCESS;
};

METHOD("SetAccelWidget", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkAccelLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * accel_widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_accel_label_set_accel_widget(self, accel_widget);
	return SUCCESS;
};

