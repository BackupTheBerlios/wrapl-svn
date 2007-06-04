#include <Gtk/Gtk/Bindings.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Std/Boolean.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/EventKey.h>
#include <Gtk/Gtk/Object.h>
/***********************************/
GLOBAL_FUNCTION(Activate, 3) {
	GtkObject * object = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int keyval = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int modifiers = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gtk_bindings_activate(object, keyval, modifiers);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ActivateEvent, 2) {
	GtkObject * object = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkEventKey * event= &((Gtk$Gdk$EventKey_t *)Args[1].Val)->Value;
	int result = gtk_bindings_activate_event(object, event);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

