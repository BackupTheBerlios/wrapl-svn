#include <Gtk/Gtk/Key.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 2
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/KeySnoopFunc.h>
/***********************************/
GLOBAL_FUNCTION(SnooperInstall, 2) {
	GtkKeySnoopFunc snooper = Gtk$Gtk$KeySnoopFunc$new(Args[0].Val);
	void *func_data = ((Std$Address_t *)Args[1].Val)->Value;
	int result = gtk_key_snooper_install(snooper, func_data);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(SnooperRemove, 1) {
	int snooper_handler_id = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gtk_key_snooper_remove(snooper_handler_id);
	return SUCCESS;
};

