#include <Gtk/Gtk/Adjustment.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Adjustment.h>
/***********************************/
TYPE(T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 6) {
	double value = ((Std$Real_t *)Args[0].Val)->Value;
	double lower = ((Std$Real_t *)Args[1].Val)->Value;
	double upper = ((Std$Real_t *)Args[2].Val)->Value;
	double step_increment = ((Std$Real_t *)Args[3].Val)->Value;
	double page_increment = ((Std$Real_t *)Args[4].Val)->Value;
	double page_size = ((Std$Real_t *)Args[5].Val)->Value;
	GtkAdjustment * result = gtk_adjustment_new(value, lower, upper, step_increment, page_increment, page_size);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_adjustment_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Changed", TYP, T) {
	GtkAdjustment * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_adjustment_changed(self);
	return SUCCESS;
};

METHOD("ClampPage", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkAdjustment * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double lower = ((Std$Real_t *)Args[1].Val)->Value;
	double upper = ((Std$Real_t *)Args[2].Val)->Value;
	gtk_adjustment_clamp_page(self, lower, upper);
	return SUCCESS;
};

METHOD("GetValue", TYP, T) {
	GtkAdjustment * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = gtk_adjustment_get_value(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("SetValue", TYP, T, TYP, Std$Real$T) {
	GtkAdjustment * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double value = ((Std$Real_t *)Args[1].Val)->Value;
	gtk_adjustment_set_value(self, value);
	return SUCCESS;
};

METHOD("ValueChanged", TYP, T) {
	GtkAdjustment * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_adjustment_value_changed(self);
	return SUCCESS;
};

