#include <Gtk/Gtk/TreePath.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TreePath.h>
#include <Gtk/GObject/Type.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 0) {
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gtk_tree_path_new();
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFirst, 0) {
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gtk_tree_path_new_first();
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromIndices, 2) {
	int first_index = ((Std$Integer_smallt *)Args[0].Val)->Value;
	char *___ = 0;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gtk_tree_path_new_from_indices(first_index, ___);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromString, 1) {
	char *path = Std$String$flatten(Args[0].Val);
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gtk_tree_path_new_from_string(path);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tree_path_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AppendIndex", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTreePath * self= ((Gtk$Gtk$TreePath_t *)Args[0].Val)->Value;
	int index_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_tree_path_append_index(self, index_);
	return SUCCESS;
};

METHOD("Compare", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreePath * self= ((Gtk$Gtk$TreePath_t *)Args[0].Val)->Value;
	GtkTreePath * b= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	int result = gtk_tree_path_compare(self, b);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GtkTreePath * self= ((Gtk$Gtk$TreePath_t *)Args[0].Val)->Value;
	GtkTreePath * result = gtk_tree_path_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Down", TYP, T) {
	GtkTreePath * self= ((Gtk$Gtk$TreePath_t *)Args[0].Val)->Value;
	gtk_tree_path_down(self);
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	GtkTreePath * self= ((Gtk$Gtk$TreePath_t *)Args[0].Val)->Value;
	gtk_tree_path_free(self);
	return SUCCESS;
};

METHOD("GetDepth", TYP, T) {
	GtkTreePath * self= ((Gtk$Gtk$TreePath_t *)Args[0].Val)->Value;
	int result = gtk_tree_path_get_depth(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetIndices", TYP, T) {
	GtkTreePath * self= ((Gtk$Gtk$TreePath_t *)Args[0].Val)->Value;
	gint* result = gtk_tree_path_get_indices(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("IsAncestor", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreePath * self= ((Gtk$Gtk$TreePath_t *)Args[0].Val)->Value;
	GtkTreePath * descendant= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	int result = gtk_tree_path_is_ancestor(self, descendant);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsDescendant", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreePath * self= ((Gtk$Gtk$TreePath_t *)Args[0].Val)->Value;
	GtkTreePath * ancestor= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	int result = gtk_tree_path_is_descendant(self, ancestor);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Next", TYP, T) {
	GtkTreePath * self= ((Gtk$Gtk$TreePath_t *)Args[0].Val)->Value;
	gtk_tree_path_next(self);
	return SUCCESS;
};

METHOD("PrependIndex", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTreePath * self= ((Gtk$Gtk$TreePath_t *)Args[0].Val)->Value;
	int index_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_tree_path_prepend_index(self, index_);
	return SUCCESS;
};

METHOD("Prev", TYP, T) {
	GtkTreePath * self= ((Gtk$Gtk$TreePath_t *)Args[0].Val)->Value;
	int result = gtk_tree_path_prev(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ToString", TYP, T) {
	GtkTreePath * self= ((Gtk$Gtk$TreePath_t *)Args[0].Val)->Value;
	char * result = gtk_tree_path_to_string(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("Up", TYP, T) {
	GtkTreePath * self= ((Gtk$Gtk$TreePath_t *)Args[0].Val)->Value;
	int result = gtk_tree_path_up(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

