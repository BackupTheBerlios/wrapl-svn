#include <Gtk/Gtk/TreeModelSort.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Std/Boolean.h>
#include <Gtk/Gtk/TreeModel.h>
#include <Gtk/Gtk/TreeModelSort.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TreePath.h>
#include <Gtk/Gtk/TreeIter.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(NewWithModel, 1) {
	GtkTreeModel * child_model = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModelSort * result = gtk_tree_model_sort_new_with_model(child_model);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tree_model_sort_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("ClearCache", TYP, T) {
	GtkTreeModelSort * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tree_model_sort_clear_cache(self);
	return SUCCESS;
};

METHOD("ConvertChildIterToIter", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModelSort * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * sort_iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * child_iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	gtk_tree_model_sort_convert_child_iter_to_iter(self, sort_iter, child_iter);
	return SUCCESS;
};

METHOD("ConvertChildPathToPath", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeModelSort * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * child_path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkTreePath * result = gtk_tree_model_sort_convert_child_path_to_path(self, child_path);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("ConvertIterToChildIter", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModelSort * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * child_iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * sorted_iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	gtk_tree_model_sort_convert_iter_to_child_iter(self, child_iter, sorted_iter);
	return SUCCESS;
};

METHOD("ConvertPathToChildPath", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeModelSort * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * sorted_path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkTreePath * result = gtk_tree_model_sort_convert_path_to_child_path(self, sorted_path);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetModel", TYP, T) {
	GtkTreeModelSort * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModel * result = gtk_tree_model_sort_get_model(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("IterIsValid", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModelSort * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	int result = gtk_tree_model_sort_iter_is_valid(self, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ResetDefaultSortFunc", TYP, T) {
	GtkTreeModelSort * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tree_model_sort_reset_default_sort_func(self);
	return SUCCESS;
};

