#include <Gtk/Gtk/Accessible.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Accessible.h>
/***********************************/
TYPE(T, Gtk$Atk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_accessible_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("ConnectWidgetDestroyed", TYP, T) {
	GtkAccessible * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_accessible_connect_widget_destroyed(self);
	return SUCCESS;
};

