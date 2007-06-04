#include <Gtk/Gdk/Selection.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Std/Boolean.h>
#include <Gtk/Gdk/Atom.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Window.h>
/***********************************/
GLOBAL_FUNCTION(Convert, 4) {
	GdkWindow * requestor = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom selection = 0;
	GdkAtom target = 0;
	int time_ = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_selection_convert(requestor, selection, target, time_);
	return SUCCESS;
};

GLOBAL_FUNCTION(OwnerGet, 1) {
	GdkAtom selection = 0;
	GdkWindow * result = gdk_selection_owner_get(selection);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(OwnerGetForDisplay, 2) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom selection = 0;
	GdkWindow * result = gdk_selection_owner_get_for_display(display, selection);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(OwnerSet, 4) {
	GdkWindow * owner = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom selection = 0;
	int time_ = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int send_event = Args[3].Val == $true;
	int result = gdk_selection_owner_set(owner, selection, time_, send_event);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(OwnerSetForDisplay, 5) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * owner = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkAtom selection = 0;
	int time_ = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int send_event = Args[4].Val == $true;
	int result = gdk_selection_owner_set_for_display(display, owner, selection, time_, send_event);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(PropertyGet, 4) {
	GdkWindow * requestor = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	guchar** data = 0;
	GdkAtom * prop_type= ((Gtk$Gdk$Atom_t *)Args[2].Val)->Value;
	gint* prop_format = 0;
	int result = gdk_selection_property_get(requestor, data, prop_type, prop_format);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(SendNotify, 5) {
	int requestor = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GdkAtom selection = 0;
	GdkAtom target = 0;
	GdkAtom property = 0;
	int time_ = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gdk_selection_send_notify(requestor, selection, target, property, time_);
	return SUCCESS;
};

GLOBAL_FUNCTION(SendNotifyForDisplay, 6) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int requestor = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkAtom selection = 0;
	GdkAtom target = 0;
	GdkAtom property = 0;
	int time_ = ((Std$Integer_smallt *)Args[5].Val)->Value;
	gdk_selection_send_notify_for_display(display, requestor, selection, target, property, time_);
	return SUCCESS;
};

