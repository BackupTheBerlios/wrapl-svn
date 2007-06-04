#include <Gtk/Gtk/Quit.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/CallbackMarshal.h>
#include <Gtk/Gtk/Function.h>
#include <Gtk/Gtk/DestroyNotify.h>
#include <Gtk/Gtk/Object.h>
/***********************************/
GLOBAL_FUNCTION(Add, 3) {
	int main_level = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GtkFunction function = Gtk$Gtk$Function$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	int result = gtk_quit_add(main_level, function, data);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(AddDestroy, 2) {
	int main_level = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GtkObject * object = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_quit_add_destroy(main_level, object);
	return SUCCESS;
};

GLOBAL_FUNCTION(AddFull, 5) {
	int main_level = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GtkFunction function = Gtk$Gtk$Function$new(Args[1].Val);
	GtkCallbackMarshal marshal = Gtk$Gtk$CallbackMarshal$new(Args[2].Val);
	void *data = ((Std$Address_t *)Args[3].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[4].Val);
	int result = gtk_quit_add_full(main_level, function, marshal, data, destroy);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Remove, 1) {
	int quit_handler_id = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gtk_quit_remove(quit_handler_id);
	return SUCCESS;
};

GLOBAL_FUNCTION(RemoveByData, 1) {
	void *data = ((Std$Address_t *)Args[0].Val)->Value;
	gtk_quit_remove_by_data(data);
	return SUCCESS;
};

