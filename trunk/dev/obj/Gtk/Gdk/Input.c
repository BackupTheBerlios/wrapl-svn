#include <Gtk/Gdk/Input.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/Gdk/InputFunction.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/DestroyNotify.h>
#include <Gtk/Gdk/ExtensionMode.h>
#include <Gtk/Gdk/Window.h>
/***********************************/
GLOBAL_FUNCTION(Add, 4) {
	int source = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int condition = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkInputFunction function = Gtk$Gdk$InputFunction$new(Args[2].Val);
	void *data = ((Std$Address_t *)Args[3].Val)->Value;
	int result = gdk_input_add(source, condition, function, data);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(AddFull, 5) {
	int source = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int condition = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkInputFunction function = Gtk$Gdk$InputFunction$new(Args[2].Val);
	void *data = ((Std$Address_t *)Args[3].Val)->Value;
	GdkDestroyNotify destroy = Gtk$Gdk$DestroyNotify$new(Args[4].Val);
	int result = gdk_input_add_full(source, condition, function, data, destroy);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Remove, 1) {
	int tag = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gdk_input_remove(tag);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetExtensionEvents, 3) {
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int mask = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkExtensionMode mode = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_input_set_extension_events(window, mask, mode);
	return SUCCESS;
};

