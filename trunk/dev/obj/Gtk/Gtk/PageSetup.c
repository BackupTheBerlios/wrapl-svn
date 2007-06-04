#include <Gtk/Gtk/PageSetup.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/Gtk/PageSetup.h>
#include <Gtk/Gtk/Unit.h>
#include <Gtk/Gtk/PageOrientation.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/PaperSize.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkPageSetup * result = gtk_page_setup_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_page_setup_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPageSetup * result = gtk_page_setup_copy(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetBottomMargin", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double result = gtk_page_setup_get_bottom_margin(self, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetLeftMargin", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double result = gtk_page_setup_get_left_margin(self, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetOrientation", TYP, T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPageOrientation result = gtk_page_setup_get_orientation(self);
	Gtk$Gtk$PageOrientation_t *_result = new(Gtk$Gtk$PageOrientation_t);
	_result->Type = Gtk$Gtk$PageOrientation$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetPageHeight", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double result = gtk_page_setup_get_page_height(self, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetPageWidth", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double result = gtk_page_setup_get_page_width(self, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetPaperHeight", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double result = gtk_page_setup_get_paper_height(self, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetPaperSize", TYP, T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPaperSize * result = gtk_page_setup_get_paper_size(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetPaperWidth", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double result = gtk_page_setup_get_paper_width(self, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetRightMargin", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double result = gtk_page_setup_get_right_margin(self, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetTopMargin", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double result = gtk_page_setup_get_top_margin(self, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("SetBottomMargin", TYP, T, TYP, Std$Real$T, TYP, Gtk$Gtk$Unit$T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double margin = ((Std$Real_t *)Args[1].Val)->Value;
	GtkUnit unit = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_page_setup_set_bottom_margin(self, margin, unit);
	return SUCCESS;
};

METHOD("SetLeftMargin", TYP, T, TYP, Std$Real$T, TYP, Gtk$Gtk$Unit$T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double margin = ((Std$Real_t *)Args[1].Val)->Value;
	GtkUnit unit = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_page_setup_set_left_margin(self, margin, unit);
	return SUCCESS;
};

METHOD("SetOrientation", TYP, T, TYP, Gtk$Gtk$PageOrientation$T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPageOrientation orientation = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_page_setup_set_orientation(self, orientation);
	return SUCCESS;
};

METHOD("SetPaperSize", TYP, T, TYP, Gtk$Gtk$PaperSize$T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPaperSize * size= ((Gtk$Gtk$PaperSize_t *)Args[1].Val)->Value;
	gtk_page_setup_set_paper_size(self, size);
	return SUCCESS;
};

METHOD("SetPaperSizeAndDefaultMargins", TYP, T, TYP, Gtk$Gtk$PaperSize$T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPaperSize * size= ((Gtk$Gtk$PaperSize_t *)Args[1].Val)->Value;
	gtk_page_setup_set_paper_size_and_default_margins(self, size);
	return SUCCESS;
};

METHOD("SetRightMargin", TYP, T, TYP, Std$Real$T, TYP, Gtk$Gtk$Unit$T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double margin = ((Std$Real_t *)Args[1].Val)->Value;
	GtkUnit unit = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_page_setup_set_right_margin(self, margin, unit);
	return SUCCESS;
};

METHOD("SetTopMargin", TYP, T, TYP, Std$Real$T, TYP, Gtk$Gtk$Unit$T) {
	GtkPageSetup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double margin = ((Std$Real_t *)Args[1].Val)->Value;
	GtkUnit unit = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_page_setup_set_top_margin(self, margin, unit);
	return SUCCESS;
};

