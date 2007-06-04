#include <Gtk/Gdk/Device.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 8
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/InputMode.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Device.h>
#include <Gtk/Gdk/Window.h>
#include <Std/Boolean.h>
#include <Gtk/Gdk/InputSource.h>
#include <Gtk/Gdk/AxisUse.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(FreeHistory, 2) {
	GdkTimeCoord** events = 0;
	int n_events = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_device_free_history(events, n_events);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetCorePointer, 0) {
	GdkDevice * result = gdk_device_get_core_pointer();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_device_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetAxis", TYP, T, TYP, Std$Object$T, TYP, Gtk$Gdk$AxisUse$T, TYP, Std$Object$T) {
	GdkDevice * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdouble* axes = 0;
	GdkAxisUse use = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdouble* value = 0;
	int result = gdk_device_get_axis(self, axes, use, value);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetHistory", TYP, T, TYP, Gtk$Gdk$Window$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkDevice * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int start = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int stop = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkTimeCoord*** events = 0;
	gint* n_events = 0;
	int result = gdk_device_get_history(self, window, start, stop, events, n_events);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetState", TYP, T, TYP, Gtk$Gdk$Window$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkDevice * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdouble* axes = 0;
	GdkModifierType* mask = 0;
	gdk_device_get_state(self, window, axes, mask);
	return SUCCESS;
};

METHOD("SetAxisUse", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$AxisUse$T) {
	GdkDevice * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int index_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkAxisUse use = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_device_set_axis_use(self, index_, use);
	return SUCCESS;
};

METHOD("SetKey", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkDevice * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int index_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int keyval = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int modifiers = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_device_set_key(self, index_, keyval, modifiers);
	return SUCCESS;
};

METHOD("SetMode", TYP, T, TYP, Gtk$Gdk$InputMode$T) {
	GdkDevice * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkInputMode mode = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gdk_device_set_mode(self, mode);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetSource", TYP, T, TYP, Gtk$Gdk$InputSource$T) {
	GdkDevice * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkInputSource source = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_device_set_source(self, source);
	return SUCCESS;
};

