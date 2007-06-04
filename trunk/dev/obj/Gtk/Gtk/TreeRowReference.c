#include <Gtk/Gtk/TreeRowReference.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Std/Boolean.h>
#include <Gtk/Gtk/TreeModel.h>
#include <Gtk/Gtk/TreeRowReference.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TreePath.h>
#include <Gtk/Gtk/TreeIter.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 2) {
	GtkTreeModel * model = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gtk_tree_row_reference_new(model, path);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(NewProxy, 3) {
	GObject* proxy = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModel * model = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[2].Val)->Value;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gtk_tree_row_reference_new_proxy(proxy, model, path);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(Deleted, 2) {
	GObject* proxy = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	gtk_tree_row_reference_deleted(proxy, path);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tree_row_reference_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Inserted, 2) {
	GObject* proxy = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	gtk_tree_row_reference_inserted(proxy, path);
	return SUCCESS;
};

GLOBAL_FUNCTION(Reordered, 4) {
	GObject* proxy = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	gint* new_order = 0;
	gtk_tree_row_reference_reordered(proxy, path, iter, new_order);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GtkTreeRowReference * self= ((Gtk$Gtk$TreeRowReference_t *)Args[0].Val)->Value;
	GtkTreeRowReference * result = gtk_tree_row_reference_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	GtkTreeRowReference * self= ((Gtk$Gtk$TreeRowReference_t *)Args[0].Val)->Value;
	gtk_tree_row_reference_free(self);
	return SUCCESS;
};

METHOD("GetModel", TYP, T) {
	GtkTreeRowReference * self= ((Gtk$Gtk$TreeRowReference_t *)Args[0].Val)->Value;
	GtkTreeModel * result = gtk_tree_row_reference_get_model(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPath", TYP, T) {
	GtkTreeRowReference * self= ((Gtk$Gtk$TreeRowReference_t *)Args[0].Val)->Value;
	GtkTreePath * result = gtk_tree_row_reference_get_path(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Valid", TYP, T) {
	GtkTreeRowReference * self= ((Gtk$Gtk$TreeRowReference_t *)Args[0].Val)->Value;
	int result = gtk_tree_row_reference_valid(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

