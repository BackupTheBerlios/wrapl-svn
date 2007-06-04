#include <Gtk/Gtk/Accel.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 2
#include <Std/Boolean.h>
#include <Gtk/GObject/Object.h>
/***********************************/
GLOBAL_FUNCTION(GroupsActivate, 3) {
	GObject* object = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int accel_key = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int accel_mods = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gtk_accel_groups_activate(object, accel_key, accel_mods);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(GroupsFromObject, 1) {
	GObject* object = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* result = gtk_accel_groups_from_object(object);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

