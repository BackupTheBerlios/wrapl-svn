#include <Gtk/Gtk/CellRendererSpin.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 2
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$CellRendererText$T, Gtk$Gtk$CellRenderer$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkCellRendererSpin * result = gtk_cell_renderer_spin_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_cell_renderer_spin_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

