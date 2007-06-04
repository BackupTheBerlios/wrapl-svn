#include <Gtk/Gtk/TreeSortable.h>
#include <Riva/Memory.h>
#include <Gtk/Gtk/SortType.h>
#include <Gtk/Gtk/TreeSortable.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/DestroyNotify.h>
#include <Gtk/Gtk/TreeIterCompareFunc.h>
#include <Std/Boolean.h>
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tree_sortable_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetSortColumnId", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkTreeSortable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gint* sort_column_id = 0;
	GtkSortType* order = 0;
	int result = gtk_tree_sortable_get_sort_column_id(self, sort_column_id, order);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("HasDefaultSortFunc", TYP, T) {
	GtkTreeSortable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_tree_sortable_has_default_sort_func(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetDefaultSortFunc", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkTreeSortable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIterCompareFunc sort_func = Gtk$Gtk$TreeIterCompareFunc$new(Args[2].Val);
	void *user_data = ((Std$Address_t *)Args[3].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[4].Val);
	gtk_tree_sortable_set_default_sort_func(self, sort_func, user_data, destroy);
	return SUCCESS;
};

METHOD("SetSortColumnId", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$SortType$T) {
	GtkTreeSortable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int sort_column_id = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkSortType order = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_tree_sortable_set_sort_column_id(self, sort_column_id, order);
	return SUCCESS;
};

METHOD("SetSortFunc", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkTreeSortable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int sort_column_id = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkTreeIterCompareFunc sort_func = Gtk$Gtk$TreeIterCompareFunc$new(Args[3].Val);
	void *user_data = ((Std$Address_t *)Args[4].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[5].Val);
	gtk_tree_sortable_set_sort_func(self, sort_column_id, sort_func, user_data, destroy);
	return SUCCESS;
};

METHOD("SortColumnChanged", TYP, T) {
	GtkTreeSortable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_tree_sortable_sort_column_changed(self);
	return SUCCESS;
};

