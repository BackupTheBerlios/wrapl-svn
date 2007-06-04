#include <Gtk/Gtk/Range.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/Gtk/SensitivityType.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/UpdateType.h>
#include <Gtk/Gtk/Range.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Adjustment.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_range_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetAdjustment", TYP, T) {
	GtkRange * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * result = gtk_range_get_adjustment(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetInverted", TYP, T) {
	GtkRange * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_range_get_inverted(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetLowerStepperSensitivity", TYP, T) {
	GtkRange * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSensitivityType result = gtk_range_get_lower_stepper_sensitivity(self);
	Gtk$Gtk$SensitivityType_t *_result = new(Gtk$Gtk$SensitivityType_t);
	_result->Type = Gtk$Gtk$SensitivityType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetUpdatePolicy", TYP, T) {
	GtkRange * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkUpdateType result = gtk_range_get_update_policy(self);
	Gtk$Gtk$UpdateType_t *_result = new(Gtk$Gtk$UpdateType_t);
	_result->Type = Gtk$Gtk$UpdateType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetUpperStepperSensitivity", TYP, T) {
	GtkRange * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSensitivityType result = gtk_range_get_upper_stepper_sensitivity(self);
	Gtk$Gtk$SensitivityType_t *_result = new(Gtk$Gtk$SensitivityType_t);
	_result->Type = Gtk$Gtk$SensitivityType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetValue", TYP, T) {
	GtkRange * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = gtk_range_get_value(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("SetAdjustment", TYP, T, TYP, Gtk$Gtk$Adjustment$T) {
	GtkRange * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_range_set_adjustment(self, adjustment);
	return SUCCESS;
};

METHOD("SetIncrements", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkRange * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double step = ((Std$Real_t *)Args[1].Val)->Value;
	double page = ((Std$Real_t *)Args[2].Val)->Value;
	gtk_range_set_increments(self, step, page);
	return SUCCESS;
};

METHOD("SetInverted", TYP, T, TYP, Std$Symbol$T) {
	GtkRange * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_range_set_inverted(self, setting);
	return SUCCESS;
};

METHOD("SetLowerStepperSensitivity", TYP, T, TYP, Gtk$Gtk$SensitivityType$T) {
	GtkRange * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSensitivityType sensitivity = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_range_set_lower_stepper_sensitivity(self, sensitivity);
	return SUCCESS;
};

METHOD("SetRange", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkRange * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double min = ((Std$Real_t *)Args[1].Val)->Value;
	double max = ((Std$Real_t *)Args[2].Val)->Value;
	gtk_range_set_range(self, min, max);
	return SUCCESS;
};

METHOD("SetUpdatePolicy", TYP, T, TYP, Gtk$Gtk$UpdateType$T) {
	GtkRange * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkUpdateType policy = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_range_set_update_policy(self, policy);
	return SUCCESS;
};

METHOD("SetUpperStepperSensitivity", TYP, T, TYP, Gtk$Gtk$SensitivityType$T) {
	GtkRange * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSensitivityType sensitivity = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_range_set_upper_stepper_sensitivity(self, sensitivity);
	return SUCCESS;
};

METHOD("SetValue", TYP, T, TYP, Std$Real$T) {
	GtkRange * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double value = ((Std$Real_t *)Args[1].Val)->Value;
	gtk_range_set_value(self, value);
	return SUCCESS;
};

