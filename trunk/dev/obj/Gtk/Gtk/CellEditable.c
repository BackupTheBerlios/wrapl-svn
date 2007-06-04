#include <Gtk/Gtk/CellEditable.h>
#include <Riva/Memory.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/CellEditable.h>
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_cell_editable_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("EditingDone", TYP, T) {
	GtkCellEditable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_cell_editable_editing_done(self);
	return SUCCESS;
};

METHOD("RemoveWidget", TYP, T) {
	GtkCellEditable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_cell_editable_remove_widget(self);
	return SUCCESS;
};

METHOD("StartEditing", TYP, T, TYP, Std$Object$T) {
	GtkCellEditable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkEvent* event = 0;
	gtk_cell_editable_start_editing(self, event);
	return SUCCESS;
};

