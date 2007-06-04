#include <Gtk/Gdk/Display.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 10
#include <Gtk/Gdk/DisplayPointerHooks.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/FilterFunc.h>
#include <Gtk/Gdk/Device.h>
#include <Gtk/Gdk/Screen.h>
#include <Gtk/Gdk/Window.h>
#include <Std/Boolean.h>
#include <Gtk/Gdk/Atom.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetDefault, 0) {
	GdkDisplay * result = gdk_display_get_default();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_display_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Open, 1) {
	char *display_name = Std$String$flatten(Args[0].Val);
	GdkDisplay * result = gdk_display_open(display_name);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(OpenDefaultLibgtkOnly, 0) {
	GdkDisplay * result = gdk_display_open_default_libgtk_only();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("AddClientMessageFilter", TYP, T, TYP, Std$Object$T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom message_type = 0;
	GdkFilterFunc func = Gtk$Gdk$FilterFunc$new(Args[2].Val);
	void *data = ((Std$Address_t *)Args[3].Val)->Value;
	gdk_display_add_client_message_filter(self, message_type, func, data);
	return SUCCESS;
};

METHOD("Beep", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_display_beep(self);
	return SUCCESS;
};

METHOD("Close", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_display_close(self);
	return SUCCESS;
};

METHOD("Flush", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_display_flush(self);
	return SUCCESS;
};

METHOD("GetCorePointer", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDevice * result = gdk_display_get_core_pointer(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetDefaultCursorSize", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_display_get_default_cursor_size(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetDefaultGroup", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * result = gdk_display_get_default_group(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetDefaultScreen", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkScreen * result = gdk_display_get_default_screen(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetEvent", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkEvent* result = gdk_display_get_event(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetMaximalCursorSize", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	guint* width = 0;
	guint* height = 0;
	gdk_display_get_maximal_cursor_size(self, width, height);
	return SUCCESS;
};

METHOD("GetNScreens", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_display_get_n_screens(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetName", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gdk_display_get_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetPointer", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkScreen** screen = 0;
	gint* x = 0;
	gint* y = 0;
	GdkModifierType* mask = 0;
	gdk_display_get_pointer(self, screen, x, y, mask);
	return SUCCESS;
};

METHOD("GetScreen", TYP, T, TYP, Std$Integer$SmallT) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int screen_num = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkScreen * result = gdk_display_get_screen(self, screen_num);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetWindowAtPointer", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* win_x = 0;
	gint* win_y = 0;
	GdkWindow * result = gdk_display_get_window_at_pointer(self, win_x, win_y);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("KeyboardUngrab", TYP, T, TYP, Std$Integer$SmallT) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int time_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_display_keyboard_ungrab(self, time_);
	return SUCCESS;
};

METHOD("ListDevices", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* result = gdk_display_list_devices(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("PeekEvent", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkEvent* result = gdk_display_peek_event(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("PointerIsGrabbed", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_display_pointer_is_grabbed(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("PointerUngrab", TYP, T, TYP, Std$Integer$SmallT) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int time_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_display_pointer_ungrab(self, time_);
	return SUCCESS;
};

METHOD("PutEvent", TYP, T, TYP, Std$Object$T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkEvent* event = 0;
	gdk_display_put_event(self, event);
	return SUCCESS;
};

METHOD("RequestSelectionNotification", TYP, T, TYP, Std$Object$T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom selection = 0;
	int result = gdk_display_request_selection_notification(self, selection);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetDoubleClickDistance", TYP, T, TYP, Std$Integer$SmallT) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int distance = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_display_set_double_click_distance(self, distance);
	return SUCCESS;
};

METHOD("SetDoubleClickTime", TYP, T, TYP, Std$Integer$SmallT) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int msec = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_display_set_double_click_time(self, msec);
	return SUCCESS;
};

METHOD("SetPointerHooks", TYP, T, TYP, Gtk$Gdk$DisplayPointerHooks$T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDisplayPointerHooks * new_hooks= &((Gtk$Gdk$DisplayPointerHooks_t *)Args[1].Val)->Value;
	GdkDisplayPointerHooks * result = gdk_display_set_pointer_hooks(self, new_hooks);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("StoreClipboard", TYP, T, TYP, Gtk$Gdk$Window$T, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$Atom$T, TYP, Std$Integer$SmallT) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * clipboard_window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int time_ = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkAtom * targets= ((Gtk$Gdk$Atom_t *)Args[3].Val)->Value;
	int n_targets = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gdk_display_store_clipboard(self, clipboard_window, time_, targets, n_targets);
	return SUCCESS;
};

METHOD("SupportsClipboardPersistence", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_display_supports_clipboard_persistence(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SupportsCursorAlpha", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_display_supports_cursor_alpha(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SupportsCursorColor", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_display_supports_cursor_color(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SupportsInputShapes", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_display_supports_input_shapes(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SupportsSelectionNotification", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_display_supports_selection_notification(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SupportsShapes", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_display_supports_shapes(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Sync", TYP, T) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_display_sync(self);
	return SUCCESS;
};

METHOD("WarpPointer", TYP, T, TYP, Gtk$Gdk$Screen$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkDisplay * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_display_warp_pointer(self, screen, x, y);
	return SUCCESS;
};

