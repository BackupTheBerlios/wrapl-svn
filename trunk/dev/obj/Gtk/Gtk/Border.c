#include <Gtk/Gtk/Border.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Border.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_border_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GtkBorder * self= &((Gtk$Gtk$Border_t *)Args[0].Val)->Value;
	GtkBorder * result = gtk_border_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	GtkBorder * self= &((Gtk$Gtk$Border_t *)Args[0].Val)->Value;
	gtk_border_free(self);
	return SUCCESS;
};

