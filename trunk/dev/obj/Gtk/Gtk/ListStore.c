#include <Gtk/Gtk/ListStore.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TreeIter.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/ListStore.h>
#include <Gtk/GObject/Value.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 2) {
	int n_columns = ((Std$Integer_smallt *)Args[0].Val)->Value;
	char *___ = 0;
	GtkListStore * result = gtk_list_store_new(n_columns, ___);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(Newv, 2) {
	int n_columns = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GType* types = 0;
	GtkListStore * result = gtk_list_store_newv(n_columns, types);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_list_store_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Append", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	gtk_list_store_append(self, iter);
	return SUCCESS;
};

METHOD("Clear", TYP, T) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_list_store_clear(self);
	return SUCCESS;
};

METHOD("Insert", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Integer$SmallT) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	int position = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_list_store_insert(self, iter, position);
	return SUCCESS;
};

METHOD("InsertAfter", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * sibling= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	gtk_list_store_insert_after(self, iter, sibling);
	return SUCCESS;
};

METHOD("InsertBefore", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * sibling= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	gtk_list_store_insert_before(self, iter, sibling);
	return SUCCESS;
};

METHOD("InsertWithValues", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	int position = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char *___ = 0;
	gtk_list_store_insert_with_values(self, iter, position, ___);
	return SUCCESS;
};

METHOD("InsertWithValuesv", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Integer$SmallT) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	int position = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gint* columns = 0;
	GValue values[1];
	Gtk$GObject$Value$to_gtk(Args[4].Val, values);
	int n_values = ((Std$Integer_smallt *)Args[5].Val)->Value;
	gtk_list_store_insert_with_valuesv(self, iter, position, columns, values, n_values);
	return SUCCESS;
};

METHOD("IterIsValid", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	int result = gtk_list_store_iter_is_valid(self, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("MoveAfter", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * position= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	gtk_list_store_move_after(self, iter, position);
	return SUCCESS;
};

METHOD("MoveBefore", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * position= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	gtk_list_store_move_before(self, iter, position);
	return SUCCESS;
};

METHOD("Prepend", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	gtk_list_store_prepend(self, iter);
	return SUCCESS;
};

METHOD("Remove", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	int result = gtk_list_store_remove(self, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Reorder", TYP, T, TYP, Std$Object$T) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* new_order = 0;
	gtk_list_store_reorder(self, new_order);
	return SUCCESS;
};

METHOD("Set", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Object$T) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	char *___ = 0;
	gtk_list_store_set(self, iter, ___);
	return SUCCESS;
};

METHOD("SetColumnTypes", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int n_columns = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GType* types = 0;
	gtk_list_store_set_column_types(self, n_columns, types);
	return SUCCESS;
};

METHOD("SetValist", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Object$T) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	va_list var_args = 0;
	gtk_list_store_set_valist(self, iter, var_args);
	return SUCCESS;
};

METHOD("SetValue", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GValue value[1];
	Gtk$GObject$Value$to_gtk(Args[3].Val, value);
	gtk_list_store_set_value(self, iter, column, value);
	return SUCCESS;
};

METHOD("Swap", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkListStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * a= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * b= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	gtk_list_store_swap(self, a, b);
	return SUCCESS;
};

