#include <Gtk/Gtk/PrintContext.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Layout.h>
#include <Gtk/Pango/Context.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/FontMap.h>
#include <Gtk/Gtk/PrintContext.h>
#include <Gtk/Gtk/PageSetup.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_print_context_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("CreatePangoContext", TYP, T) {
	GtkPrintContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoContext * result = gtk_print_context_create_pango_context(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("CreatePangoLayout", TYP, T) {
	GtkPrintContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoLayout * result = gtk_print_context_create_pango_layout(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetCairoContext", TYP, T) {
	GtkPrintContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	cairo_t* result = gtk_print_context_get_cairo_context(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetDpiX", TYP, T) {
	GtkPrintContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = gtk_print_context_get_dpi_x(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetDpiY", TYP, T) {
	GtkPrintContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = gtk_print_context_get_dpi_y(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetHeight", TYP, T) {
	GtkPrintContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = gtk_print_context_get_height(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetPageSetup", TYP, T) {
	GtkPrintContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPageSetup * result = gtk_print_context_get_page_setup(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPangoFontmap", TYP, T) {
	GtkPrintContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontMap * result = gtk_print_context_get_pango_fontmap(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetWidth", TYP, T) {
	GtkPrintContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = gtk_print_context_get_width(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("SetCairoContext", TYP, T, TYP, Std$Object$T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkPrintContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	cairo_t* cr = 0;
	double dpi_x = ((Std$Real_t *)Args[2].Val)->Value;
	double dpi_y = ((Std$Real_t *)Args[3].Val)->Value;
	gtk_print_context_set_cairo_context(self, cr, dpi_x, dpi_y);
	return SUCCESS;
};

