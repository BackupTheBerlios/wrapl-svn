#include <Gtk/Gdk/Pointer.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Std/Boolean.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/GrabStatus.h>
#include <Gtk/Gdk/Cursor.h>
#include <Gtk/Gdk/Window.h>
/***********************************/
GLOBAL_FUNCTION(Grab, 6) {
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int owner_events = Args[1].Val == $true;
	int event_mask = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkWindow * confine_to = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	GdkCursor * cursor= ((Gtk$Gdk$Cursor_t *)Args[4].Val)->Value;
	int time_ = ((Std$Integer_smallt *)Args[5].Val)->Value;
	GdkGrabStatus result = gdk_pointer_grab(window, owner_events, event_mask, confine_to, cursor, time_);
	Gtk$Gdk$GrabStatus_t *_result = new(Gtk$Gdk$GrabStatus_t);
	_result->Type = Gtk$Gdk$GrabStatus$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GrabInfoLibgtkOnly, 3) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow** grab_window = 0;
	gboolean* owner_events = 0;
	int result = gdk_pointer_grab_info_libgtk_only(display, grab_window, owner_events);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(IsGrabbed, 0) {
	int result = gdk_pointer_is_grabbed();
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(Ungrab, 1) {
	int time_ = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gdk_pointer_ungrab(time_);
	return SUCCESS;
};

