#include <Gtk/Gtk/CellRendererText.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gtk/CellRendererText.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$CellRenderer$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkCellRendererText * result = gtk_cell_renderer_text_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_cell_renderer_text_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("SetFixedHeightFromFont", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCellRendererText * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int number_of_rows = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_cell_renderer_text_set_fixed_height_from_font(self, number_of_rows);
	return SUCCESS;
};

