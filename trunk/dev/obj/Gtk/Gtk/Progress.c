#include <Gtk/Gtk/Progress.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/Progress.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Adjustment.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_progress_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Configure", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkProgress * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double value = ((Std$Real_t *)Args[1].Val)->Value;
	double hmin = ((Std$Real_t *)Args[2].Val)->Value;
	double max = ((Std$Real_t *)Args[3].Val)->Value;
	gtk_progress_configure(self, value, hmin, max);
	return SUCCESS;
};

METHOD("GetCurrentPercentage", TYP, T) {
	GtkProgress * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = gtk_progress_get_current_percentage(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetCurrentText", TYP, T) {
	GtkProgress * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char * result = gtk_progress_get_current_text(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetPercentageFromValue", TYP, T, TYP, Std$Real$T) {
	GtkProgress * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double value = ((Std$Real_t *)Args[1].Val)->Value;
	double result = gtk_progress_get_percentage_from_value(self, value);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetTextFromValue", TYP, T, TYP, Std$Real$T) {
	GtkProgress * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double value = ((Std$Real_t *)Args[1].Val)->Value;
	char * result = gtk_progress_get_text_from_value(self, value);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetValue", TYP, T) {
	GtkProgress * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = gtk_progress_get_value(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("SetActivityMode", TYP, T, TYP, Std$Symbol$T) {
	GtkProgress * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int activity_mode = Args[1].Val == $true;
	gtk_progress_set_activity_mode(self, activity_mode);
	return SUCCESS;
};

METHOD("SetAdjustment", TYP, T, TYP, Gtk$Gtk$Adjustment$T) {
	GtkProgress * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_progress_set_adjustment(self, adjustment);
	return SUCCESS;
};

METHOD("SetFormatString", TYP, T, TYP, Std$String$T) {
	GtkProgress * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *format = Std$String$flatten(Args[1].Val);
	gtk_progress_set_format_string(self, format);
	return SUCCESS;
};

METHOD("SetPercentage", TYP, T, TYP, Std$Real$T) {
	GtkProgress * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double percentage = ((Std$Real_t *)Args[1].Val)->Value;
	gtk_progress_set_percentage(self, percentage);
	return SUCCESS;
};

METHOD("SetShowText", TYP, T, TYP, Std$Symbol$T) {
	GtkProgress * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int show_text = Args[1].Val == $true;
	gtk_progress_set_show_text(self, show_text);
	return SUCCESS;
};

METHOD("SetTextAlignment", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkProgress * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double x_align = ((Std$Real_t *)Args[1].Val)->Value;
	double y_align = ((Std$Real_t *)Args[2].Val)->Value;
	gtk_progress_set_text_alignment(self, x_align, y_align);
	return SUCCESS;
};

METHOD("SetValue", TYP, T, TYP, Std$Real$T) {
	GtkProgress * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double value = ((Std$Real_t *)Args[1].Val)->Value;
	gtk_progress_set_value(self, value);
	return SUCCESS;
};

