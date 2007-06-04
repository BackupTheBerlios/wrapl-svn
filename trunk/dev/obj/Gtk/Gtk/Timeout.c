#include <Gtk/Gtk/Timeout.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/CallbackMarshal.h>
#include <Gtk/Gtk/Function.h>
#include <Gtk/Gtk/DestroyNotify.h>
/***********************************/
GLOBAL_FUNCTION(Add, 3) {
	int interval = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GtkFunction function = Gtk$Gtk$Function$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	int result = gtk_timeout_add(interval, function, data);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(AddFull, 5) {
	int interval = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GtkFunction function = Gtk$Gtk$Function$new(Args[1].Val);
	GtkCallbackMarshal marshal = Gtk$Gtk$CallbackMarshal$new(Args[2].Val);
	void *data = ((Std$Address_t *)Args[3].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[4].Val);
	int result = gtk_timeout_add_full(interval, function, marshal, data, destroy);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Remove, 1) {
	int timeout_handler_id = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gtk_timeout_remove(timeout_handler_id);
	return SUCCESS;
};

