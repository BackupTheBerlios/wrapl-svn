#include <Gtk/Gdk/Threads.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 1
#include <Gtk/GObject/Object.h>
/***********************************/
GLOBAL_FUNCTION(Enter, 0) {
	gdk_threads_enter();
	return SUCCESS;
};

GLOBAL_FUNCTION(Init, 0) {
	gdk_threads_init();
	return SUCCESS;
};

GLOBAL_FUNCTION(Leave, 0) {
	gdk_threads_leave();
	return SUCCESS;
};

GLOBAL_FUNCTION(SetLockFunctions, 2) {
	GCallback enter_fn = 0;
	GCallback leave_fn = 0;
	gdk_threads_set_lock_functions(enter_fn, leave_fn);
	return SUCCESS;
};

