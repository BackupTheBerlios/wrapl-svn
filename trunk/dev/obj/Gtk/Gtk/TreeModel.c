#include <Gtk/Gtk/TreeModel.h>
#include <Riva/Memory.h>
#include <Gtk/Gtk/TreePath.h>
#include <Gtk/Gtk/TreeIter.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/GObject/Value.h>
#include <Gtk/Gtk/TreeModelForeachFunc.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/TreeModel.h>
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tree_model_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Foreach", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeModelForeachFunc func = Gtk$Gtk$TreeModelForeachFunc$new(Args[2].Val);
	void *user_data = ((Std$Address_t *)Args[3].Val)->Value;
	gtk_tree_model_foreach(self, func, user_data);
	return SUCCESS;
};

METHOD("Get", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Object$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	char *___ = 0;
	gtk_tree_model_get(self, iter, ___);
	return SUCCESS;
};

METHOD("GetColumnType", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int index_ = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GType result = gtk_tree_model_get_column_type(self, index_);
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetFlags", TYP, T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_tree_model_get_flags(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetIter", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[3].Val)->Value;
	int result = gtk_tree_model_get_iter(self, iter, path);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetIterFirst", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	int result = gtk_tree_model_get_iter_first(self, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetIterFromString", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$String$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	char *path_string = Std$String$flatten(Args[3].Val);
	int result = gtk_tree_model_get_iter_from_string(self, iter, path_string);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetNColumns", TYP, T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_tree_model_get_n_columns(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetPath", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	GtkTreePath * result = gtk_tree_model_get_path(self, iter);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetStringFromIter", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	char * result = gtk_tree_model_get_string_from_iter(self, iter);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetValist", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Object$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	va_list var_args = 0;
	gtk_tree_model_get_valist(self, iter, var_args);
	return SUCCESS;
};

METHOD("GetValue", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GValue value[1];
	Gtk$GObject$Value$to_gtk(Args[4].Val, value);
	gtk_tree_model_get_value(self, iter, column, value);
	return SUCCESS;
};

METHOD("IterChildren", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	GtkTreeIter * parent= &((Gtk$Gtk$TreeIter_t *)Args[3].Val)->Value;
	int result = gtk_tree_model_iter_children(self, iter, parent);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IterHasChild", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	int result = gtk_tree_model_iter_has_child(self, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IterNChildren", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	int result = gtk_tree_model_iter_n_children(self, iter);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("IterNext", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	int result = gtk_tree_model_iter_next(self, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IterNthChild", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Integer$SmallT) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	GtkTreeIter * parent= &((Gtk$Gtk$TreeIter_t *)Args[3].Val)->Value;
	int n = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int result = gtk_tree_model_iter_nth_child(self, iter, parent, n);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IterParent", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	GtkTreeIter * child= &((Gtk$Gtk$TreeIter_t *)Args[3].Val)->Value;
	int result = gtk_tree_model_iter_parent(self, iter, child);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("RefNode", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	gtk_tree_model_ref_node(self, iter);
	return SUCCESS;
};

METHOD("RowChanged", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[2].Val)->Value;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[3].Val)->Value;
	gtk_tree_model_row_changed(self, path, iter);
	return SUCCESS;
};

METHOD("RowDeleted", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[2].Val)->Value;
	gtk_tree_model_row_deleted(self, path);
	return SUCCESS;
};

METHOD("RowHasChildToggled", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[2].Val)->Value;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[3].Val)->Value;
	gtk_tree_model_row_has_child_toggled(self, path, iter);
	return SUCCESS;
};

METHOD("RowInserted", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[2].Val)->Value;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[3].Val)->Value;
	gtk_tree_model_row_inserted(self, path, iter);
	return SUCCESS;
};

METHOD("RowsReordered", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Object$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[2].Val)->Value;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[3].Val)->Value;
	gint* new_order = 0;
	gtk_tree_model_rows_reordered(self, path, iter, new_order);
	return SUCCESS;
};

METHOD("UnrefNode", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModel * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	gtk_tree_model_unref_node(self, iter);
	return SUCCESS;
};

