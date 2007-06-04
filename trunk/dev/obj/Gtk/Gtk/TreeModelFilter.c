#include <Gtk/Gtk/TreeModelFilter.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 11
#include <Gtk/Gtk/TreeModel.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TreeModelFilter.h>
#include <Gtk/Gtk/TreeModelFilterVisibleFunc.h>
#include <Gtk/Gtk/TreePath.h>
#include <Gtk/Gtk/TreeIter.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/DestroyNotify.h>
#include <Gtk/Gtk/TreeModelFilterModifyFunc.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/TreeModel.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 2) {
	GtkTreeModel * child_model = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * root= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkTreeModelFilter * result = gtk_tree_model_filter_new(child_model, root);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tree_model_filter_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("ClearCache", TYP, T) {
	GtkTreeModelFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tree_model_filter_clear_cache(self);
	return SUCCESS;
};

METHOD("ConvertChildIterToIter", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModelFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * filter_iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * child_iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	int result = gtk_tree_model_filter_convert_child_iter_to_iter(self, filter_iter, child_iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ConvertChildPathToPath", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeModelFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * child_path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkTreePath * result = gtk_tree_model_filter_convert_child_path_to_path(self, child_path);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("ConvertIterToChildIter", TYP, T, TYP, Gtk$Gtk$TreeIter$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeModelFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * child_iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	GtkTreeIter * filter_iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	gtk_tree_model_filter_convert_iter_to_child_iter(self, child_iter, filter_iter);
	return SUCCESS;
};

METHOD("ConvertPathToChildPath", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeModelFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * filter_path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkTreePath * result = gtk_tree_model_filter_convert_path_to_child_path(self, filter_path);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetModel", TYP, T) {
	GtkTreeModelFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModel * result = gtk_tree_model_filter_get_model(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Refilter", TYP, T) {
	GtkTreeModelFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tree_model_filter_refilter(self);
	return SUCCESS;
};

METHOD("SetModifyFunc", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkTreeModelFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int n_columns = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GType* types = 0;
	GtkTreeModelFilterModifyFunc func = Gtk$Gtk$TreeModelFilterModifyFunc$new(Args[3].Val);
	void *data = ((Std$Address_t *)Args[4].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[5].Val);
	gtk_tree_model_filter_set_modify_func(self, n_columns, types, func, data, destroy);
	return SUCCESS;
};

METHOD("SetVisibleColumn", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTreeModelFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_tree_model_filter_set_visible_column(self, column);
	return SUCCESS;
};

METHOD("SetVisibleFunc", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkTreeModelFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModelFilterVisibleFunc func = Gtk$Gtk$TreeModelFilterVisibleFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[3].Val);
	gtk_tree_model_filter_set_visible_func(self, func, data, destroy);
	return SUCCESS;
};

