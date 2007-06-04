#include <Gtk/Gtk/Idle.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/CallbackMarshal.h>
#include <Gtk/Gtk/Function.h>
#include <Gtk/Gtk/DestroyNotify.h>
/***********************************/
GLOBAL_FUNCTION(Add, 2) {
	GtkFunction function = Gtk$Gtk$Function$new(Args[0].Val);
	void *data = ((Std$Address_t *)Args[1].Val)->Value;
	int result = gtk_idle_add(function, data);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(AddFull, 5) {
	int priority = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GtkFunction function = Gtk$Gtk$Function$new(Args[1].Val);
	GtkCallbackMarshal marshal = Gtk$Gtk$CallbackMarshal$new(Args[2].Val);
	void *data = ((Std$Address_t *)Args[3].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[4].Val);
	int result = gtk_idle_add_full(priority, function, marshal, data, destroy);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(AddPriority, 3) {
	int priority = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GtkFunction function = Gtk$Gtk$Function$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	int result = gtk_idle_add_priority(priority, function, data);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Remove, 1) {
	int idle_handler_id = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gtk_idle_remove(idle_handler_id);
	return SUCCESS;
};

GLOBAL_FUNCTION(RemoveByData, 1) {
	void *data = ((Std$Address_t *)Args[0].Val)->Value;
	gtk_idle_remove_by_data(data);
	return SUCCESS;
};

