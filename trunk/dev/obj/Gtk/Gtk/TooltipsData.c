#include <Gtk/Gtk/TooltipsData.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gtk/TooltipsData.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/Widget.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(Get, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTooltipsData * result = gtk_tooltips_data_get(widget);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

