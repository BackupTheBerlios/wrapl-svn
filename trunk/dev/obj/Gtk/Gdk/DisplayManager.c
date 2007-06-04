#include <Gtk/Gdk/DisplayManager.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/Gdk/DisplayManager.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(Get, 0) {
	GdkDisplayManager * result = gdk_display_manager_get();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_display_manager_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetDefaultDisplay", TYP, T) {
	GdkDisplayManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDisplay * result = gdk_display_manager_get_default_display(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("ListDisplays", TYP, T) {
	GdkDisplayManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* result = gdk_display_manager_list_displays(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("SetDefaultDisplay", TYP, T, TYP, Gtk$Gdk$Display$T) {
	GdkDisplayManager * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdk_display_manager_set_default_display(self, display);
	return SUCCESS;
};

