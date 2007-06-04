#include <Gtk/Gdk/DragContext.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/DragContext.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GdkDragContext * result = gdk_drag_context_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_drag_context_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GdkDragContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_drag_context_ref(self);
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GdkDragContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_drag_context_unref(self);
	return SUCCESS;
};

