#include <Gtk/Gtk/Main.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 2
#include <Std/Boolean.h>
#include <Gtk/GObject/Object.h>
/***********************************/
GLOBAL_FUNCTION(DoEvent, 1) {
	GdkEvent* event = 0;
	gtk_main_do_event(event);
	return SUCCESS;
};

GLOBAL_FUNCTION(Iteration, 0) {
	int result = gtk_main_iteration();
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(IterationDo, 1) {
	int blocking = Args[0].Val == $true;
	int result = gtk_main_iteration_do(blocking);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(Level, 0) {
	int result = gtk_main_level();
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Quit, 0) {
	gtk_main_quit();
	return SUCCESS;
};

GLOBAL_FUNCTION(Run, 0) {
	gtk_main();
	return SUCCESS;
};

