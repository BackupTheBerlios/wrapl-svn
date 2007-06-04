#include <Gtk/Gtk/Input.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/Gdk/InputFunction.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/CallbackMarshal.h>
#include <Gtk/Gtk/DestroyNotify.h>
/***********************************/
GLOBAL_FUNCTION(AddFull, 6) {
	int source = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int condition = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkInputFunction function = Gtk$Gdk$InputFunction$new(Args[2].Val);
	GtkCallbackMarshal marshal = Gtk$Gtk$CallbackMarshal$new(Args[3].Val);
	void *data = ((Std$Address_t *)Args[4].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[5].Val);
	int result = gtk_input_add_full(source, condition, function, marshal, data, destroy);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Remove, 1) {
	int input_handler_id = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gtk_input_remove(input_handler_id);
	return SUCCESS;
};

