#include <Gtk/Gtk/CellLayout.h>
#include <Riva/Memory.h>
#include <Gtk/Gtk/CellLayout.h>
#include <Gtk/Gtk/CellLayoutDataFunc.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/CellRenderer.h>
#include <Std/Boolean.h>
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_cell_layout_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddAttribute", TYP, T, TYP, Gtk$Gtk$CellRenderer$T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GtkCellLayout * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkCellRenderer * cell = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	char *attribute = Std$String$flatten(Args[3].Val);
	int column = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_cell_layout_add_attribute(self, cell, attribute, column);
	return SUCCESS;
};

METHOD("Clear", TYP, T) {
	GtkCellLayout * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_cell_layout_clear(self);
	return SUCCESS;
};

METHOD("ClearAttributes", TYP, T, TYP, Gtk$Gtk$CellRenderer$T) {
	GtkCellLayout * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkCellRenderer * cell = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_cell_layout_clear_attributes(self, cell);
	return SUCCESS;
};

METHOD("PackEnd", TYP, T, TYP, Gtk$Gtk$CellRenderer$T, TYP, Std$Symbol$T) {
	GtkCellLayout * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkCellRenderer * cell = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int expand = Args[3].Val == $true;
	gtk_cell_layout_pack_end(self, cell, expand);
	return SUCCESS;
};

METHOD("PackStart", TYP, T, TYP, Gtk$Gtk$CellRenderer$T, TYP, Std$Symbol$T) {
	GtkCellLayout * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkCellRenderer * cell = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int expand = Args[3].Val == $true;
	gtk_cell_layout_pack_start(self, cell, expand);
	return SUCCESS;
};

METHOD("Reorder", TYP, T, TYP, Gtk$Gtk$CellRenderer$T, TYP, Std$Integer$SmallT) {
	GtkCellLayout * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkCellRenderer * cell = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_cell_layout_reorder(self, cell, position);
	return SUCCESS;
};

METHOD("SetAttributes", TYP, T, TYP, Gtk$Gtk$CellRenderer$T, TYP, Std$Object$T) {
	GtkCellLayout * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkCellRenderer * cell = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	char *___ = 0;
	gtk_cell_layout_set_attributes(self, cell, ___);
	return SUCCESS;
};

METHOD("SetCellDataFunc", TYP, T, TYP, Gtk$Gtk$CellRenderer$T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Object$T) {
	GtkCellLayout * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkCellRenderer * cell = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	GtkCellLayoutDataFunc func = Gtk$Gtk$CellLayoutDataFunc$new(Args[3].Val);
	void *func_data = ((Std$Address_t *)Args[4].Val)->Value;
	GDestroyNotify destroy = 0;
	gtk_cell_layout_set_cell_data_func(self, cell, func, func_data, destroy);
	return SUCCESS;
};

