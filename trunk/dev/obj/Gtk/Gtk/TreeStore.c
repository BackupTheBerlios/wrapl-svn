#include <Gtk/Gtk/TreeStore.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Std/Boolean.h>
#include <Gtk/Gtk/TreeStore.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TreeIter.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/GObject/Value.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 2) {
	int n_columns = ((Std$Integer_smallt *)Args[0].Val)->Value;
	char *___ = 0;
	GtkTreeStore * result = gtk_tree_store_new(n_columns, ___);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(Newv, 2) {
	int n_columns = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GType* types = 0;
	GtkTreeStore * result = gtk_tree_store_newv(n_columns, types);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tree_store_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Append", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * parent= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	gtk_tree_store_append(self, iter, parent);
	return SUCCESS;
};

METHOD("Clear", TYP, T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tree_store_clear(self);
	return SUCCESS;
};

METHOD("Insert", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Integer$SmallT) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * parent= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	int position = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_tree_store_insert(self, iter, parent, position);
	return SUCCESS;
};

METHOD("InsertAfter", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * parent= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	GtkTreeIter * sibling= &((Gtk$Gtk$TreeIter_t *)Args[3].Val)->Value;
	gtk_tree_store_insert_after(self, iter, parent, sibling);
	return SUCCESS;
};

METHOD("InsertBefore", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * parent= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	GtkTreeIter * sibling= &((Gtk$Gtk$TreeIter_t *)Args[3].Val)->Value;
	gtk_tree_store_insert_before(self, iter, parent, sibling);
	return SUCCESS;
};

METHOD("InsertWithValues", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * parent= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	int position = ((Std$Integer_smallt *)Args[3].Val)->Value;
	char *___ = 0;
	gtk_tree_store_insert_with_values(self, iter, parent, position, ___);
	return SUCCESS;
};

METHOD("InsertWithValuesv", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Integer$SmallT) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * parent= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	int position = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gint* columns = 0;
	GValue values[1];
	Gtk$GObject$Value$to_gtk(Args[5].Val, values);
	int n_values = ((Std$Integer_smallt *)Args[6].Val)->Value;
	gtk_tree_store_insert_with_valuesv(self, iter, parent, position, columns, values, n_values);
	return SUCCESS;
};

METHOD("IsAncestor", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * descendant= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	int result = gtk_tree_store_is_ancestor(self, iter, descendant);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IterDepth", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	int result = gtk_tree_store_iter_depth(self, iter);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("IterIsValid", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	int result = gtk_tree_store_iter_is_valid(self, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("MoveAfter", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * position= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	gtk_tree_store_move_after(self, iter, position);
	return SUCCESS;
};

METHOD("MoveBefore", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * position= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	gtk_tree_store_move_before(self, iter, position);
	return SUCCESS;
};

METHOD("Prepend", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * parent= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	gtk_tree_store_prepend(self, iter, parent);
	return SUCCESS;
};

METHOD("Remove", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	int result = gtk_tree_store_remove(self, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Reorder", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Object$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * parent= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	gint* new_order = 0;
	gtk_tree_store_reorder(self, parent, new_order);
	return SUCCESS;
};

METHOD("Set", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Object$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	char *___ = 0;
	gtk_tree_store_set(self, iter, ___);
	return SUCCESS;
};

METHOD("SetColumnTypes", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int n_columns = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GType* types = 0;
	gtk_tree_store_set_column_types(self, n_columns, types);
	return SUCCESS;
};

METHOD("SetValist", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Object$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	va_list var_args = 0;
	gtk_tree_store_set_valist(self, iter, var_args);
	return SUCCESS;
};

METHOD("SetValue", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GValue value[1];
	Gtk$GObject$Value$to_gtk(Args[3].Val, value);
	gtk_tree_store_set_value(self, iter, column, value);
	return SUCCESS;
};

METHOD("Swap", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeStore * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * a= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * b= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	gtk_tree_store_swap(self, a, b);
	return SUCCESS;
};

