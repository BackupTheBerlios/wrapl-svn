#include <Gtk/Gtk/Init.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Std/Boolean.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/Function.h>
/***********************************/
GLOBAL_FUNCTION(Add, 2) {
	GtkFunction function = Gtk$Gtk$Function$new(Args[0].Val);
	void *data = ((Std$Address_t *)Args[1].Val)->Value;
	gtk_init_add(function, data);
	return SUCCESS;
};

GLOBAL_FUNCTION(Check, 2) {
	int* argc = 0;
	char*** argv = 0;
	int result = gtk_init_check(argc, argv);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(WithArgs, 6) {
	int* argc = 0;
	char*** argv = 0;
	char *parameter_string = Std$String$flatten(Args[2].Val);
	GOptionEntry* entries = 0;
	char *translation_domain = Std$String$flatten(Args[4].Val);
	GError** error = 0;
	int result = gtk_init_with_args(argc, argv, parameter_string, entries, translation_domain, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

