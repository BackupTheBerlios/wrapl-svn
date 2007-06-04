#include <Gtk/Gtk/TreeSelection.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 11
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TreePath.h>
#include <Gtk/Gtk/TreeIter.h>
#include <Gtk/Gtk/TreeView.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/DestroyNotify.h>
#include <Gtk/Gtk/TreeSelectionForeachFunc.h>
#include <Gtk/Gtk/SelectionMode.h>
#include <Gtk/Gtk/TreeSelection.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/TreeSelectionFunc.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tree_selection_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("CountSelectedRows", TYP, T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_selection_count_selected_rows(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetMode", TYP, T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSelectionMode result = gtk_tree_selection_get_mode(self);
	Gtk$Gtk$SelectionMode_t *_result = new(Gtk$Gtk$SelectionMode_t);
	_result->Type = Gtk$Gtk$SelectionMode$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetSelected", TYP, T, TYP, Std$Object$T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModel** model = 0;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	int result = gtk_tree_selection_get_selected(self, model, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSelectedRows", TYP, T, TYP, Std$Object$T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModel** model = 0;
	GList* result = gtk_tree_selection_get_selected_rows(self, model);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetTreeView", TYP, T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeView * result = gtk_tree_selection_get_tree_view(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetUserData", TYP, T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	void * result = gtk_tree_selection_get_user_data(self);
	Result->Val = Std$Address$new(result);
	return SUCCESS;
};

METHOD("IterIsSelected", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	int result = gtk_tree_selection_iter_is_selected(self, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("PathIsSelected", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	int result = gtk_tree_selection_path_is_selected(self, path);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SelectAll", TYP, T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tree_selection_select_all(self);
	return SUCCESS;
};

METHOD("SelectIter", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	gtk_tree_selection_select_iter(self, iter);
	return SUCCESS;
};

METHOD("SelectPath", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	gtk_tree_selection_select_path(self, path);
	return SUCCESS;
};

METHOD("SelectRange", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * start_path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkTreePath * end_path= ((Gtk$Gtk$TreePath_t *)Args[2].Val)->Value;
	gtk_tree_selection_select_range(self, start_path, end_path);
	return SUCCESS;
};

METHOD("SelectedForeach", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeSelectionForeachFunc func = Gtk$Gtk$TreeSelectionForeachFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	gtk_tree_selection_selected_foreach(self, func, data);
	return SUCCESS;
};

METHOD("SetMode", TYP, T, TYP, Gtk$Gtk$SelectionMode$T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSelectionMode type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_tree_selection_set_mode(self, type);
	return SUCCESS;
};

METHOD("SetSelectFunction", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeSelectionFunc func = Gtk$Gtk$TreeSelectionFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[3].Val);
	gtk_tree_selection_set_select_function(self, func, data, destroy);
	return SUCCESS;
};

METHOD("UnselectAll", TYP, T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tree_selection_unselect_all(self);
	return SUCCESS;
};

METHOD("UnselectIter", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	gtk_tree_selection_unselect_iter(self, iter);
	return SUCCESS;
};

METHOD("UnselectPath", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	gtk_tree_selection_unselect_path(self, path);
	return SUCCESS;
};

METHOD("UnselectRange", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * start_path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkTreePath * end_path= ((Gtk$Gtk$TreePath_t *)Args[2].Val)->Value;
	gtk_tree_selection_unselect_range(self, start_path, end_path);
	return SUCCESS;
};

