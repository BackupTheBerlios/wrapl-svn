#include <Gtk/Gdk/Error.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 1
#include <Gtk/GObject/Object.h>
/***********************************/
GLOBAL_FUNCTION(TrapPop, 0) {
	int result = gdk_error_trap_pop();
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(TrapPush, 0) {
	gdk_error_trap_push();
	return SUCCESS;
};

