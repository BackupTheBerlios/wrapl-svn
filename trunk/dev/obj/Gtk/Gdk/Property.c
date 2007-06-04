#include <Gtk/Gdk/Property.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/Gdk/Atom.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/PropMode.h>
#include <Gtk/Gdk/Window.h>
#include <Std/Boolean.h>
/***********************************/
GLOBAL_FUNCTION(Change, 7) {
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom property = 0;
	GdkAtom type = 0;
	int format = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkPropMode mode = ((Std$Integer_smallt *)Args[4].Val)->Value;
	char *data = Std$String$flatten(Args[5].Val);
	int nelements = ((Std$Integer_smallt *)Args[6].Val)->Value;
	gdk_property_change(window, property, type, format, mode, data, nelements);
	return SUCCESS;
};

GLOBAL_FUNCTION(Delete, 2) {
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom property = 0;
	gdk_property_delete(window, property);
	return SUCCESS;
};

GLOBAL_FUNCTION(Get, 10) {
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom property = 0;
	GdkAtom type = 0;
	int offset = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int length = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int pdelete = ((Std$Integer_smallt *)Args[5].Val)->Value;
	GdkAtom * actual_property_type= ((Gtk$Gdk$Atom_t *)Args[6].Val)->Value;
	gint* actual_format = 0;
	gint* actual_length = 0;
	guchar** data = 0;
	int result = gdk_property_get(window, property, type, offset, length, pdelete, actual_property_type, actual_format, actual_length, data);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

