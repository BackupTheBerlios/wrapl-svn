#include <Gtk/Gtk/SpinButton.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/Gtk/SpinButton.h>
#include <Gtk/Gtk/SpinButtonUpdatePolicy.h>
#include <Gtk/Gtk/SpinType.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Adjustment.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Entry$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 3) {
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double climb_rate = ((Std$Real_t *)Args[1].Val)->Value;
	int digits = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkSpinButton * result = gtk_spin_button_new(adjustment, climb_rate, digits);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithRange, 3) {
	double min = ((Std$Real_t *)Args[0].Val)->Value;
	double max = ((Std$Real_t *)Args[1].Val)->Value;
	double step = ((Std$Real_t *)Args[2].Val)->Value;
	GtkSpinButton * result = gtk_spin_button_new_with_range(min, max, step);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_spin_button_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Configure", TYP, T, TYP, Gtk$Gtk$Adjustment$T, TYP, Std$Real$T, TYP, Std$Integer$SmallT) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	double climb_rate = ((Std$Real_t *)Args[2].Val)->Value;
	int digits = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_spin_button_configure(self, adjustment, climb_rate, digits);
	return SUCCESS;
};

METHOD("GetAdjustment", TYP, T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * result = gtk_spin_button_get_adjustment(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetDigits", TYP, T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_spin_button_get_digits(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetIncrements", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdouble* step = 0;
	gdouble* page = 0;
	gtk_spin_button_get_increments(self, step, page);
	return SUCCESS;
};

METHOD("GetNumeric", TYP, T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_spin_button_get_numeric(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetRange", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdouble* min = 0;
	gdouble* max = 0;
	gtk_spin_button_get_range(self, min, max);
	return SUCCESS;
};

METHOD("GetSnapToTicks", TYP, T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_spin_button_get_snap_to_ticks(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetUpdatePolicy", TYP, T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSpinButtonUpdatePolicy result = gtk_spin_button_get_update_policy(self);
	Gtk$Gtk$SpinButtonUpdatePolicy_t *_result = new(Gtk$Gtk$SpinButtonUpdatePolicy_t);
	_result->Type = Gtk$Gtk$SpinButtonUpdatePolicy$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetValue", TYP, T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = gtk_spin_button_get_value(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetValueAsInt", TYP, T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_spin_button_get_value_as_int(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetWrap", TYP, T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_spin_button_get_wrap(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetAdjustment", TYP, T, TYP, Gtk$Gtk$Adjustment$T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_spin_button_set_adjustment(self, adjustment);
	return SUCCESS;
};

METHOD("SetDigits", TYP, T, TYP, Std$Integer$SmallT) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int digits = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_spin_button_set_digits(self, digits);
	return SUCCESS;
};

METHOD("SetIncrements", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double step = ((Std$Real_t *)Args[1].Val)->Value;
	double page = ((Std$Real_t *)Args[2].Val)->Value;
	gtk_spin_button_set_increments(self, step, page);
	return SUCCESS;
};

METHOD("SetNumeric", TYP, T, TYP, Std$Symbol$T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int numeric = Args[1].Val == $true;
	gtk_spin_button_set_numeric(self, numeric);
	return SUCCESS;
};

METHOD("SetRange", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double min = ((Std$Real_t *)Args[1].Val)->Value;
	double max = ((Std$Real_t *)Args[2].Val)->Value;
	gtk_spin_button_set_range(self, min, max);
	return SUCCESS;
};

METHOD("SetSnapToTicks", TYP, T, TYP, Std$Symbol$T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int snap_to_ticks = Args[1].Val == $true;
	gtk_spin_button_set_snap_to_ticks(self, snap_to_ticks);
	return SUCCESS;
};

METHOD("SetUpdatePolicy", TYP, T, TYP, Gtk$Gtk$SpinButtonUpdatePolicy$T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSpinButtonUpdatePolicy policy = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_spin_button_set_update_policy(self, policy);
	return SUCCESS;
};

METHOD("SetValue", TYP, T, TYP, Std$Real$T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double value = ((Std$Real_t *)Args[1].Val)->Value;
	gtk_spin_button_set_value(self, value);
	return SUCCESS;
};

METHOD("SetWrap", TYP, T, TYP, Std$Symbol$T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int wrap = Args[1].Val == $true;
	gtk_spin_button_set_wrap(self, wrap);
	return SUCCESS;
};

METHOD("Spin", TYP, T, TYP, Gtk$Gtk$SpinType$T, TYP, Std$Real$T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSpinType direction = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double increment = ((Std$Real_t *)Args[2].Val)->Value;
	gtk_spin_button_spin(self, direction, increment);
	return SUCCESS;
};

METHOD("Update", TYP, T) {
	GtkSpinButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_spin_button_update(self);
	return SUCCESS;
};

