#include <Gtk/Gdk/Drag.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/DragProtocol.h>
#include <Gtk/Gdk/Screen.h>
#include <Gtk/Gdk/Window.h>
#include <Gtk/Gdk/DragContext.h>
#include <Std/Boolean.h>
#include <Gtk/Gdk/Display.h>
/***********************************/
GLOBAL_FUNCTION(Abort, 2) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int time_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_drag_abort(context, time_);
	return SUCCESS;
};

GLOBAL_FUNCTION(Begin, 2) {
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* targets = 0;
	GdkDragContext * result = gdk_drag_begin(window, targets);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Drop, 2) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int time_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_drag_drop(context, time_);
	return SUCCESS;
};

GLOBAL_FUNCTION(DropSucceeded, 1) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_drag_drop_succeeded(context);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(FindWindow, 6) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * drag_window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x_root = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y_root = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkWindow** dest_window = 0;
	GdkDragProtocol* protocol = 0;
	gdk_drag_find_window(context, drag_window, x_root, y_root, dest_window, protocol);
	return SUCCESS;
};

GLOBAL_FUNCTION(FindWindowForScreen, 7) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * drag_window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int x_root = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int y_root = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GdkWindow** dest_window = 0;
	GdkDragProtocol* protocol = 0;
	gdk_drag_find_window_for_screen(context, drag_window, screen, x_root, y_root, dest_window, protocol);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetProtocol, 2) {
	int xid = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GdkDragProtocol* protocol = 0;
	int result = gdk_drag_get_protocol(xid, protocol);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetProtocolForDisplay, 3) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int xid = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkDragProtocol* protocol = 0;
	int result = gdk_drag_get_protocol_for_display(display, xid, protocol);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetSelection, 1) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom result = gdk_drag_get_selection(context);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(Motion, 8) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * dest_window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkDragProtocol protocol = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int x_root = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int y_root = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int suggested_action = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int possible_actions = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int time_ = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int result = gdk_drag_motion(context, dest_window, protocol, x_root, y_root, suggested_action, possible_actions, time_);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(Status, 3) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int action = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int time_ = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_drag_status(context, action, time_);
	return SUCCESS;
};

