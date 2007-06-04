#include <Gtk/Gtk/PrintSettings.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 13
#include <Gtk/Gtk/PrintQuality.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/PrintDuplex.h>
#include <Gtk/Gtk/PageRange.h>
#include <Gtk/Gtk/PageSet.h>
#include <Gtk/Gtk/Unit.h>
#include <Gtk/Gtk/PrintSettings.h>
#include <Gtk/Gtk/PrintPages.h>
#include <Gtk/Gtk/PageOrientation.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/PrintSettingsFunc.h>
#include <Gtk/Gtk/PaperSize.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkPrintSettings * result = gtk_print_settings_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_print_settings_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPrintSettings * result = gtk_print_settings_copy(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Foreach", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPrintSettingsFunc func = Gtk$Gtk$PrintSettingsFunc$new(Args[1].Val);
	void *user_data = ((Std$Address_t *)Args[2].Val)->Value;
	gtk_print_settings_foreach(self, func, user_data);
	return SUCCESS;
};

METHOD("Get", TYP, T, TYP, Std$String$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	const char * result = gtk_print_settings_get(self, key);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetBool", TYP, T, TYP, Std$String$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	int result = gtk_print_settings_get_bool(self, key);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetCollate", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_print_settings_get_collate(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetDefaultSource", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_print_settings_get_default_source(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetDither", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_print_settings_get_dither(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetDouble", TYP, T, TYP, Std$String$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	double result = gtk_print_settings_get_double(self, key);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetDoubleWithDefault", TYP, T, TYP, Std$String$T, TYP, Std$Real$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	double def = ((Std$Real_t *)Args[2].Val)->Value;
	double result = gtk_print_settings_get_double_with_default(self, key, def);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetDuplex", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPrintDuplex result = gtk_print_settings_get_duplex(self);
	Gtk$Gtk$PrintDuplex_t *_result = new(Gtk$Gtk$PrintDuplex_t);
	_result->Type = Gtk$Gtk$PrintDuplex$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetFinishings", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_print_settings_get_finishings(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetInt", TYP, T, TYP, Std$String$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	int result = gtk_print_settings_get_int(self, key);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetIntWithDefault", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	int def = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gtk_print_settings_get_int_with_default(self, key, def);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetLength", TYP, T, TYP, Std$String$T, TYP, Gtk$Gtk$Unit$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	GtkUnit unit = ((Std$Integer_smallt *)Args[2].Val)->Value;
	double result = gtk_print_settings_get_length(self, key, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetMediaType", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_print_settings_get_media_type(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetNCopies", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_print_settings_get_n_copies(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetNumberUp", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_print_settings_get_number_up(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetOrientation", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPageOrientation result = gtk_print_settings_get_orientation(self);
	Gtk$Gtk$PageOrientation_t *_result = new(Gtk$Gtk$PageOrientation_t);
	_result->Type = Gtk$Gtk$PageOrientation$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetOutputBin", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_print_settings_get_output_bin(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetPageRanges", TYP, T, TYP, Std$Object$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* num_ranges = 0;
	GtkPageRange * result = gtk_print_settings_get_page_ranges(self, num_ranges);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetPageSet", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPageSet result = gtk_print_settings_get_page_set(self);
	Gtk$Gtk$PageSet_t *_result = new(Gtk$Gtk$PageSet_t);
	_result->Type = Gtk$Gtk$PageSet$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetPaperHeight", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double result = gtk_print_settings_get_paper_height(self, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetPaperSize", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPaperSize * result = gtk_print_settings_get_paper_size(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetPaperWidth", TYP, T, TYP, Gtk$Gtk$Unit$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkUnit unit = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double result = gtk_print_settings_get_paper_width(self, unit);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetPrintPages", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPrintPages result = gtk_print_settings_get_print_pages(self);
	Gtk$Gtk$PrintPages_t *_result = new(Gtk$Gtk$PrintPages_t);
	_result->Type = Gtk$Gtk$PrintPages$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetPrinter", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_print_settings_get_printer(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetQuality", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPrintQuality result = gtk_print_settings_get_quality(self);
	Gtk$Gtk$PrintQuality_t *_result = new(Gtk$Gtk$PrintQuality_t);
	_result->Type = Gtk$Gtk$PrintQuality$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetResolution", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_print_settings_get_resolution(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetReverse", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_print_settings_get_reverse(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetScale", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = gtk_print_settings_get_scale(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetUseColor", TYP, T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_print_settings_get_use_color(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("HasKey", TYP, T, TYP, Std$String$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	int result = gtk_print_settings_has_key(self, key);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Set", TYP, T, TYP, Std$String$T, TYP, Std$String$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	char *value = Std$String$flatten(Args[2].Val);
	gtk_print_settings_set(self, key, value);
	return SUCCESS;
};

METHOD("SetBool", TYP, T, TYP, Std$String$T, TYP, Std$Symbol$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	int value = Args[2].Val == $true;
	gtk_print_settings_set_bool(self, key, value);
	return SUCCESS;
};

METHOD("SetCollate", TYP, T, TYP, Std$Symbol$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int collate = Args[1].Val == $true;
	gtk_print_settings_set_collate(self, collate);
	return SUCCESS;
};

METHOD("SetDefaultSource", TYP, T, TYP, Std$String$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *default_source = Std$String$flatten(Args[1].Val);
	gtk_print_settings_set_default_source(self, default_source);
	return SUCCESS;
};

METHOD("SetDither", TYP, T, TYP, Std$String$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *dither = Std$String$flatten(Args[1].Val);
	gtk_print_settings_set_dither(self, dither);
	return SUCCESS;
};

METHOD("SetDouble", TYP, T, TYP, Std$String$T, TYP, Std$Real$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	double value = ((Std$Real_t *)Args[2].Val)->Value;
	gtk_print_settings_set_double(self, key, value);
	return SUCCESS;
};

METHOD("SetDuplex", TYP, T, TYP, Gtk$Gtk$PrintDuplex$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPrintDuplex duplex = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_print_settings_set_duplex(self, duplex);
	return SUCCESS;
};

METHOD("SetFinishings", TYP, T, TYP, Std$String$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *finishings = Std$String$flatten(Args[1].Val);
	gtk_print_settings_set_finishings(self, finishings);
	return SUCCESS;
};

METHOD("SetInt", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	int value = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_print_settings_set_int(self, key, value);
	return SUCCESS;
};

METHOD("SetLength", TYP, T, TYP, Std$String$T, TYP, Std$Real$T, TYP, Gtk$Gtk$Unit$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	double value = ((Std$Real_t *)Args[2].Val)->Value;
	GtkUnit unit = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_print_settings_set_length(self, key, value, unit);
	return SUCCESS;
};

METHOD("SetMediaType", TYP, T, TYP, Std$String$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *media_type = Std$String$flatten(Args[1].Val);
	gtk_print_settings_set_media_type(self, media_type);
	return SUCCESS;
};

METHOD("SetNCopies", TYP, T, TYP, Std$Integer$SmallT) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int num_copies = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_print_settings_set_n_copies(self, num_copies);
	return SUCCESS;
};

METHOD("SetNumberUp", TYP, T, TYP, Std$Integer$SmallT) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int number_up = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_print_settings_set_number_up(self, number_up);
	return SUCCESS;
};

METHOD("SetOrientation", TYP, T, TYP, Gtk$Gtk$PageOrientation$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPageOrientation orientation = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_print_settings_set_orientation(self, orientation);
	return SUCCESS;
};

METHOD("SetOutputBin", TYP, T, TYP, Std$String$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *output_bin = Std$String$flatten(Args[1].Val);
	gtk_print_settings_set_output_bin(self, output_bin);
	return SUCCESS;
};

METHOD("SetPageRanges", TYP, T, TYP, Gtk$Gtk$PageRange$T, TYP, Std$Integer$SmallT) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPageRange * page_ranges= &((Gtk$Gtk$PageRange_t *)Args[1].Val)->Value;
	int num_ranges = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_print_settings_set_page_ranges(self, page_ranges, num_ranges);
	return SUCCESS;
};

METHOD("SetPageSet", TYP, T, TYP, Gtk$Gtk$PageSet$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPageSet page_set = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_print_settings_set_page_set(self, page_set);
	return SUCCESS;
};

METHOD("SetPaperHeight", TYP, T, TYP, Std$Real$T, TYP, Gtk$Gtk$Unit$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double height = ((Std$Real_t *)Args[1].Val)->Value;
	GtkUnit unit = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_print_settings_set_paper_height(self, height, unit);
	return SUCCESS;
};

METHOD("SetPaperSize", TYP, T, TYP, Gtk$Gtk$PaperSize$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPaperSize * paper_size= ((Gtk$Gtk$PaperSize_t *)Args[1].Val)->Value;
	gtk_print_settings_set_paper_size(self, paper_size);
	return SUCCESS;
};

METHOD("SetPaperWidth", TYP, T, TYP, Std$Real$T, TYP, Gtk$Gtk$Unit$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double width = ((Std$Real_t *)Args[1].Val)->Value;
	GtkUnit unit = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_print_settings_set_paper_width(self, width, unit);
	return SUCCESS;
};

METHOD("SetPrintPages", TYP, T, TYP, Gtk$Gtk$PrintPages$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPrintPages pages = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_print_settings_set_print_pages(self, pages);
	return SUCCESS;
};

METHOD("SetPrinter", TYP, T, TYP, Std$String$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *printer = Std$String$flatten(Args[1].Val);
	gtk_print_settings_set_printer(self, printer);
	return SUCCESS;
};

METHOD("SetQuality", TYP, T, TYP, Gtk$Gtk$PrintQuality$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPrintQuality quality = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_print_settings_set_quality(self, quality);
	return SUCCESS;
};

METHOD("SetResolution", TYP, T, TYP, Std$Integer$SmallT) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int resolution = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_print_settings_set_resolution(self, resolution);
	return SUCCESS;
};

METHOD("SetReverse", TYP, T, TYP, Std$Symbol$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int reverse = Args[1].Val == $true;
	gtk_print_settings_set_reverse(self, reverse);
	return SUCCESS;
};

METHOD("SetScale", TYP, T, TYP, Std$Real$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double scale = ((Std$Real_t *)Args[1].Val)->Value;
	gtk_print_settings_set_scale(self, scale);
	return SUCCESS;
};

METHOD("SetUseColor", TYP, T, TYP, Std$Symbol$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int use_color = Args[1].Val == $true;
	gtk_print_settings_set_use_color(self, use_color);
	return SUCCESS;
};

METHOD("Unset", TYP, T, TYP, Std$String$T) {
	GtkPrintSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	gtk_print_settings_unset(self, key);
	return SUCCESS;
};

