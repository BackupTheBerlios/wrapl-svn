#include <Gtk/Gtk/ProgressBar.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/Pango/EllipsizeMode.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Adjustment.h>
#include <Gtk/Gtk/ProgressBar.h>
#include <Gtk/Gtk/ProgressBarOrientation.h>
#include <Gtk/Gtk/ProgressBarStyle.h>
/***********************************/
TYPE(T, Gtk$Gtk$Progress$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkProgressBar * result = gtk_progress_bar_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithAdjustment, 1) {
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkProgressBar * result = gtk_progress_bar_new_with_adjustment(adjustment);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_progress_bar_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetEllipsize", TYP, T) {
	GtkProgressBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoEllipsizeMode result = gtk_progress_bar_get_ellipsize(self);
	Gtk$Pango$EllipsizeMode_t *_result = new(Gtk$Pango$EllipsizeMode_t);
	_result->Type = Gtk$Pango$EllipsizeMode$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetFraction", TYP, T) {
	GtkProgressBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = gtk_progress_bar_get_fraction(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetOrientation", TYP, T) {
	GtkProgressBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkProgressBarOrientation result = gtk_progress_bar_get_orientation(self);
	Gtk$Gtk$ProgressBarOrientation_t *_result = new(Gtk$Gtk$ProgressBarOrientation_t);
	_result->Type = Gtk$Gtk$ProgressBarOrientation$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetPulseStep", TYP, T) {
	GtkProgressBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = gtk_progress_bar_get_pulse_step(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetText", TYP, T) {
	GtkProgressBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_progress_bar_get_text(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("Pulse", TYP, T) {
	GtkProgressBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_progress_bar_pulse(self);
	return SUCCESS;
};

METHOD("SetActivityBlocks", TYP, T, TYP, Std$Integer$SmallT) {
	GtkProgressBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int blocks = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_progress_bar_set_activity_blocks(self, blocks);
	return SUCCESS;
};

METHOD("SetActivityStep", TYP, T, TYP, Std$Integer$SmallT) {
	GtkProgressBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int step = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_progress_bar_set_activity_step(self, step);
	return SUCCESS;
};

METHOD("SetBarStyle", TYP, T, TYP, Gtk$Gtk$ProgressBarStyle$T) {
	GtkProgressBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkProgressBarStyle style = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_progress_bar_set_bar_style(self, style);
	return SUCCESS;
};

METHOD("SetDiscreteBlocks", TYP, T, TYP, Std$Integer$SmallT) {
	GtkProgressBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int blocks = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_progress_bar_set_discrete_blocks(self, blocks);
	return SUCCESS;
};

METHOD("SetEllipsize", TYP, T, TYP, Gtk$Pango$EllipsizeMode$T) {
	GtkProgressBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoEllipsizeMode mode = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_progress_bar_set_ellipsize(self, mode);
	return SUCCESS;
};

METHOD("SetFraction", TYP, T, TYP, Std$Real$T) {
	GtkProgressBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double fraction = ((Std$Real_t *)Args[1].Val)->Value;
	gtk_progress_bar_set_fraction(self, fraction);
	return SUCCESS;
};

METHOD("SetOrientation", TYP, T, TYP, Gtk$Gtk$ProgressBarOrientation$T) {
	GtkProgressBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkProgressBarOrientation orientation = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_progress_bar_set_orientation(self, orientation);
	return SUCCESS;
};

METHOD("SetPulseStep", TYP, T, TYP, Std$Real$T) {
	GtkProgressBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double fraction = ((Std$Real_t *)Args[1].Val)->Value;
	gtk_progress_bar_set_pulse_step(self, fraction);
	return SUCCESS;
};

METHOD("SetText", TYP, T, TYP, Std$String$T) {
	GtkProgressBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	gtk_progress_bar_set_text(self, text);
	return SUCCESS;
};

METHOD("Update", TYP, T, TYP, Std$Real$T) {
	GtkProgressBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double percentage = ((Std$Real_t *)Args[1].Val)->Value;
	gtk_progress_bar_update(self, percentage);
	return SUCCESS;
};

