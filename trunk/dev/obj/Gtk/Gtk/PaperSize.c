#include <Gtk/Gtk/PaperSize.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Std/Boolean.h>
#include <Gtk/Gtk/Unit.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/PaperSize.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 1) {
	char *name = Std$String$flatten(Args[0].Val);
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gtk_paper_size_new(name);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(NewCustom, 5) {
	char *name = Std$String$flatten(Args[0].Val);
	char *display_name = Std$String$flatten(Args[1].Val);
	double width = ((Std$Real_t *)Args[2].Val)->Value;
	double height = ((Std$Real_t *)Args[3].Val)->Value;
	GtkUnit unit = ((Std$Integer_smallt *)Args[4].Val)->Value;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gtk_paper_size_new_custom(name, display_name, width, height, unit);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromPpd, 4) {
	char *ppd_name = Std$String$flatten(Args[0].Val);
	char *ppd_display_name = Std$String$flatten(Args[1].Val);
	double width = ((Std$Real_t *)Args[2].Val)->Value;
	double height = ((Std$Real_t *)Args[3].Val)->Value;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gtk_paper_size_new_from_ppd(ppd_name, ppd_display_name, width, height);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetDefault, 0) {
	const char * result = gtk_paper_size_get_default();
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_paper_size_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GtkPaperSize * self= ((Gtk$Gtk$PaperSize_t *)Args[0].Val)->Value;
	GtkPaperSize * result = gtk_paper_size_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	GtkPaperSize * self= ((Gtk$Gtk$PaperSize_t *)Args[0].Val)->Value;
	gtk_paper_size_free(self);
	return SUCCESS;
};

METHOD("GetDefaultBottomMargin", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPaperSize * self= ((Gtk$Gtk$PaperSize_t *)Args[0].Val)->Value;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double result = gtk_paper_size_get_default_bottom_margin(self, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetDefaultLeftMargin", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPaperSize * self= ((Gtk$Gtk$PaperSize_t *)Args[0].Val)->Value;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double result = gtk_paper_size_get_default_left_margin(self, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetDefaultRightMargin", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPaperSize * self= ((Gtk$Gtk$PaperSize_t *)Args[0].Val)->Value;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double result = gtk_paper_size_get_default_right_margin(self, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetDefaultTopMargin", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPaperSize * self= ((Gtk$Gtk$PaperSize_t *)Args[0].Val)->Value;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double result = gtk_paper_size_get_default_top_margin(self, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetDisplayName", TYP, T) {
	GtkPaperSize * self= ((Gtk$Gtk$PaperSize_t *)Args[0].Val)->Value;
	const char * result = gtk_paper_size_get_display_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetHeight", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPaperSize * self= ((Gtk$Gtk$PaperSize_t *)Args[0].Val)->Value;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double result = gtk_paper_size_get_height(self, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetName", TYP, T) {
	GtkPaperSize * self= ((Gtk$Gtk$PaperSize_t *)Args[0].Val)->Value;
	const char * result = gtk_paper_size_get_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetPpdName", TYP, T) {
	GtkPaperSize * self= ((Gtk$Gtk$PaperSize_t *)Args[0].Val)->Value;
	const char * result = gtk_paper_size_get_ppd_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetWidth", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPaperSize * self= ((Gtk$Gtk$PaperSize_t *)Args[0].Val)->Value;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double result = gtk_paper_size_get_width(self, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("IsCustom", TYP, T) {
	GtkPaperSize * self= ((Gtk$Gtk$PaperSize_t *)Args[0].Val)->Value;
	int result = gtk_paper_size_is_custom(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsEqual", TYP, T, TYP, Gtk$Gtk$PaperSize$T) {
	GtkPaperSize * self= ((Gtk$Gtk$PaperSize_t *)Args[0].Val)->Value;
	GtkPaperSize * size2= ((Gtk$Gtk$PaperSize_t *)Args[1].Val)->Value;
	int result = gtk_paper_size_is_equal(self, size2);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetSize", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Gtk$Gtk$Unit$T) {
	GtkPaperSize * self= ((Gtk$Gtk$PaperSize_t *)Args[0].Val)->Value;
	double width = ((Std$Real_t *)Args[1].Val)->Value;
	double height = ((Std$Real_t *)Args[2].Val)->Value;
	GtkUnit unit = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_paper_size_set_size(self, width, height, unit);
	return SUCCESS;
};

