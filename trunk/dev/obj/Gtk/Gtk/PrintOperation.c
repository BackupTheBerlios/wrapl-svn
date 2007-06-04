#include <Gtk/Gtk/PrintOperation.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 12
#include <Gtk/Gtk/PrintSettings.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/PrintOperation.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Window.h>
#include <Gtk/Gtk/PrintOperationAction.h>
#include <Gtk/Gtk/PrintOperationResult.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/PrintStatus.h>
#include <Gtk/Gtk/PageSetup.h>
#include <Gtk/Gtk/Unit.h>
#include <Gtk/Gtk/PrintSettings.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkPrintOperation * result = gtk_print_operation_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_print_operation_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Cancel", TYP, T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_print_operation_cancel(self);
	return SUCCESS;
};

METHOD("GetDefaultPageSetup", TYP, T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPageSetup * result = gtk_print_operation_get_default_page_setup(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetError", TYP, T, TYP, Std$Object$T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GError** error = 0;
	gtk_print_operation_get_error(self, error);
	return SUCCESS;
};

METHOD("GetPrintSettings", TYP, T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPrintSettings * result = gtk_print_operation_get_print_settings(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetStatus", TYP, T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPrintStatus result = gtk_print_operation_get_status(self);
	Gtk$Gtk$PrintStatus_t *_result = new(Gtk$Gtk$PrintStatus_t);
	_result->Type = Gtk$Gtk$PrintStatus$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetStatusString", TYP, T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_print_operation_get_status_string(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("IsFinished", TYP, T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_print_operation_is_finished(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Run", TYP, T, TYP, Gtk$Gtk$PrintOperationAction$T, TYP, Gtk$Gtk$Window$T, TYP, Std$Object$T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPrintOperationAction action = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkWindow * parent = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	GError** error = 0;
	GtkPrintOperationResult result = gtk_print_operation_run(self, action, parent, error);
	Gtk$Gtk$PrintOperationResult_t *_result = new(Gtk$Gtk$PrintOperationResult_t);
	_result->Type = Gtk$Gtk$PrintOperationResult$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("SetAllowAsync", TYP, T, TYP, Std$Symbol$T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int allow_async = Args[1].Val == $true;
	gtk_print_operation_set_allow_async(self, allow_async);
	return SUCCESS;
};

METHOD("SetCurrentPage", TYP, T, TYP, Std$Integer$SmallT) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int current_page = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_print_operation_set_current_page(self, current_page);
	return SUCCESS;
};

METHOD("SetCustomTabLabel", TYP, T, TYP, Std$String$T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *label = Std$String$flatten(Args[1].Val);
	gtk_print_operation_set_custom_tab_label(self, label);
	return SUCCESS;
};

METHOD("SetDefaultPageSetup", TYP, T, TYP, Gtk$Gtk$PageSetup$T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPageSetup * default_page_setup = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_print_operation_set_default_page_setup(self, default_page_setup);
	return SUCCESS;
};

METHOD("SetExportFilename", TYP, T, TYP, Std$String$T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *filename = Std$String$flatten(Args[1].Val);
	gtk_print_operation_set_export_filename(self, filename);
	return SUCCESS;
};

METHOD("SetJobName", TYP, T, TYP, Std$String$T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *job_name = Std$String$flatten(Args[1].Val);
	gtk_print_operation_set_job_name(self, job_name);
	return SUCCESS;
};

METHOD("SetNPages", TYP, T, TYP, Std$Integer$SmallT) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int n_pages = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_print_operation_set_n_pages(self, n_pages);
	return SUCCESS;
};

METHOD("SetPrintSettings", TYP, T, TYP, Gtk$Gtk$PrintSettings$T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPrintSettings * print_settings = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_print_operation_set_print_settings(self, print_settings);
	return SUCCESS;
};

METHOD("SetShowProgress", TYP, T, TYP, Std$Symbol$T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int show_progress = Args[1].Val == $true;
	gtk_print_operation_set_show_progress(self, show_progress);
	return SUCCESS;
};

METHOD("SetTrackPrintStatus", TYP, T, TYP, Std$Symbol$T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int track_status = Args[1].Val == $true;
	gtk_print_operation_set_track_print_status(self, track_status);
	return SUCCESS;
};

METHOD("SetUnit", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_print_operation_set_unit(self, unit);
	return SUCCESS;
};

METHOD("SetUseFullPage", TYP, T, TYP, Std$Symbol$T) {
	GtkPrintOperation * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int full_page = Args[1].Val == $true;
	gtk_print_operation_set_use_full_page(self, full_page);
	return SUCCESS;
};

