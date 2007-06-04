#include <Gtk/Gtk/Table.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Std/Boolean.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/Table.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
/***********************************/
TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 3) {
	int rows = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int columns = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int homogeneous = Args[2].Val == $true;
	GtkTable * result = gtk_table_new(rows, columns, homogeneous);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_table_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Attach", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int left_attach = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int right_attach = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int top_attach = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int bottom_attach = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int xoptions = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int yoptions = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int xpadding = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int ypadding = ((Std$Integer_smallt *)Args[9].Val)->Value;
	gtk_table_attach(self, child, left_attach, right_attach, top_attach, bottom_attach, xoptions, yoptions, xpadding, ypadding);
	return SUCCESS;
};

METHOD("AttachDefaults", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int left_attach = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int right_attach = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int top_attach = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int bottom_attach = ((Std$Integer_smallt *)Args[5].Val)->Value;
	gtk_table_attach_defaults(self, widget, left_attach, right_attach, top_attach, bottom_attach);
	return SUCCESS;
};

METHOD("GetColSpacing", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_table_get_col_spacing(self, column);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetDefaultColSpacing", TYP, T) {
	GtkTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_table_get_default_col_spacing(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetDefaultRowSpacing", TYP, T) {
	GtkTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_table_get_default_row_spacing(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetHomogeneous", TYP, T) {
	GtkTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_table_get_homogeneous(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetRowSpacing", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_table_get_row_spacing(self, row);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Resize", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int rows = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int columns = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_table_resize(self, rows, columns);
	return SUCCESS;
};

METHOD("SetColSpacing", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int spacing = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_table_set_col_spacing(self, column, spacing);
	return SUCCESS;
};

METHOD("SetColSpacings", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int spacing = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_table_set_col_spacings(self, spacing);
	return SUCCESS;
};

METHOD("SetHomogeneous", TYP, T, TYP, Std$Symbol$T) {
	GtkTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int homogeneous = Args[1].Val == $true;
	gtk_table_set_homogeneous(self, homogeneous);
	return SUCCESS;
};

METHOD("SetRowSpacing", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int spacing = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_table_set_row_spacing(self, row, spacing);
	return SUCCESS;
};

METHOD("SetRowSpacings", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int spacing = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_table_set_row_spacings(self, spacing);
	return SUCCESS;
};

