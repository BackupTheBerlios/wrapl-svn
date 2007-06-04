#include <Gtk/Gtk/Print.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/Gtk/PageSetup.h>
#include <Gtk/Gtk/PageSetupDoneFunc.h>
#include <Gtk/Gtk/PrintSettings.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/Window.h>
/***********************************/
GLOBAL_FUNCTION(ErrorQuark, 0) {
	GQuark result = gtk_print_error_quark();
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(RunPageSetupDialog, 3) {
	GtkWindow * parent = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPageSetup * page_setup = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkPrintSettings * settings = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	GtkPageSetup * result = gtk_print_run_page_setup_dialog(parent, page_setup, settings);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(RunPageSetupDialogAsync, 5) {
	GtkWindow * parent = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPageSetup * page_setup = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkPrintSettings * settings = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	GtkPageSetupDoneFunc done_cb = Gtk$Gtk$PageSetupDoneFunc$new(Args[3].Val);
	void *data = ((Std$Address_t *)Args[4].Val)->Value;
	gtk_print_run_page_setup_dialog_async(parent, page_setup, settings, done_cb, data);
	return SUCCESS;
};

