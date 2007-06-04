#include <Gtk/Gtk/Grab.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 2
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/Widget.h>
/***********************************/
GLOBAL_FUNCTION(Add, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_grab_add(widget);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetCurrent, 0) {
	GtkWidget * result = gtk_grab_get_current();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Remove, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_grab_remove(widget);
	return SUCCESS;
};

