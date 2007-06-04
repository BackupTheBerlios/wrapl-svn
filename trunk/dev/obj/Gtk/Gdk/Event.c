#include <Gtk/Gdk/Event.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 9
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Screen.h>
#include <Gtk/Gdk/Window.h>
#include <Std/Boolean.h>
#include <Gtk/Gdk/EventFunc.h>
#include <Gtk/Gdk/EventType.h>
#include <Gtk/Gdk/AxisUse.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/GObject/Object.h>
/***********************************/
GLOBAL_FUNCTION(Copy, 1) {
	GdkEvent* event = 0;
	GdkEvent* result = gdk_event_copy(event);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(Free, 1) {
	GdkEvent* event = 0;
	gdk_event_free(event);
	return SUCCESS;
};

GLOBAL_FUNCTION(Get, 0) {
	GdkEvent* result = gdk_event_get();
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetAxis, 3) {
	GdkEvent* event = 0;
	GdkAxisUse axis_use = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdouble* value = 0;
	int result = gdk_event_get_axis(event, axis_use, value);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetCoords, 3) {
	GdkEvent* event = 0;
	gdouble* x_win = 0;
	gdouble* y_win = 0;
	int result = gdk_event_get_coords(event, x_win, y_win);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetGraphicsExpose, 1) {
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkEvent* result = gdk_event_get_graphics_expose(window);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetRootCoords, 3) {
	GdkEvent* event = 0;
	gdouble* x_root = 0;
	gdouble* y_root = 0;
	int result = gdk_event_get_root_coords(event, x_root, y_root);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetScreen, 1) {
	GdkEvent* event = 0;
	GdkScreen * result = gdk_event_get_screen(event);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetState, 2) {
	GdkEvent* event = 0;
	GdkModifierType* state = 0;
	int result = gdk_event_get_state(event, state);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetTime, 1) {
	GdkEvent* event = 0;
	int result = gdk_event_get_time(event);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_event_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(HandlerSet, 3) {
	GdkEventFunc func = Gtk$Gdk$EventFunc$new(Args[0].Val);
	void *data = ((Std$Address_t *)Args[1].Val)->Value;
	GDestroyNotify notify = 0;
	gdk_event_handler_set(func, data, notify);
	return SUCCESS;
};

GLOBAL_FUNCTION(New, 1) {
	GdkEventType type = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GdkEvent* result = gdk_event_new(type);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(Peek, 0) {
	GdkEvent* result = gdk_event_peek();
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(Put, 1) {
	GdkEvent* event = 0;
	gdk_event_put(event);
	return SUCCESS;
};

GLOBAL_FUNCTION(SendClientMessage, 2) {
	GdkEvent* event = 0;
	GdkNativeWindow winid = 0;
	int result = gdk_event_send_client_message(event, winid);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(SendClientMessageForDisplay, 3) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkEvent* event = 0;
	GdkNativeWindow winid = 0;
	int result = gdk_event_send_client_message_for_display(display, event, winid);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(SendClientmessageToall, 1) {
	GdkEvent* event = 0;
	gdk_event_send_clientmessage_toall(event);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetScreen, 2) {
	GdkEvent* event = 0;
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdk_event_set_screen(event, screen);
	return SUCCESS;
};

