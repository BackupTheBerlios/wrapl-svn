#include <Gtk/Gtk/List.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Std/Boolean.h>
#include <Gtk/Gtk/List.h>
#include <Gtk/Gtk/ScrollType.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/SelectionMode.h>
#include <Gtk/Gtk/Widget.h>
/***********************************/
TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkList * result = gtk_list_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_list_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AppendItems", TYP, T, TYP, Std$Object$T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* items = 0;
	gtk_list_append_items(self, items);
	return SUCCESS;
};

METHOD("ChildPosition", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_list_child_position(self, child);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("ClearItems", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int start = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int end = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_list_clear_items(self, start, end);
	return SUCCESS;
};

METHOD("EndDragSelection", TYP, T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_list_end_drag_selection(self);
	return SUCCESS;
};

METHOD("EndSelection", TYP, T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_list_end_selection(self);
	return SUCCESS;
};

METHOD("ExtendSelection", TYP, T, TYP, Gtk$Gtk$ScrollType$T, TYP, Std$Real$T, TYP, Std$Symbol$T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkScrollType scroll_type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double position = ((Std$Real_t *)Args[2].Val)->Value;
	int auto_start_selection = Args[3].Val == $true;
	gtk_list_extend_selection(self, scroll_type, position, auto_start_selection);
	return SUCCESS;
};

METHOD("InsertItems", TYP, T, TYP, Std$Object$T, TYP, Std$Integer$SmallT) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* items = 0;
	int position = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_list_insert_items(self, items, position);
	return SUCCESS;
};

METHOD("PrependItems", TYP, T, TYP, Std$Object$T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* items = 0;
	gtk_list_prepend_items(self, items);
	return SUCCESS;
};

METHOD("RemoveItems", TYP, T, TYP, Std$Object$T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* items = 0;
	gtk_list_remove_items(self, items);
	return SUCCESS;
};

METHOD("RemoveItemsNoUnref", TYP, T, TYP, Std$Object$T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* items = 0;
	gtk_list_remove_items_no_unref(self, items);
	return SUCCESS;
};

METHOD("ScrollHorizontal", TYP, T, TYP, Gtk$Gtk$ScrollType$T, TYP, Std$Real$T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkScrollType scroll_type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double position = ((Std$Real_t *)Args[2].Val)->Value;
	gtk_list_scroll_horizontal(self, scroll_type, position);
	return SUCCESS;
};

METHOD("ScrollVertical", TYP, T, TYP, Gtk$Gtk$ScrollType$T, TYP, Std$Real$T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkScrollType scroll_type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	double position = ((Std$Real_t *)Args[2].Val)->Value;
	gtk_list_scroll_vertical(self, scroll_type, position);
	return SUCCESS;
};

METHOD("SelectAll", TYP, T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_list_select_all(self);
	return SUCCESS;
};

METHOD("SelectChild", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_list_select_child(self, child);
	return SUCCESS;
};

METHOD("SelectItem", TYP, T, TYP, Std$Integer$SmallT) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int item = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_list_select_item(self, item);
	return SUCCESS;
};

METHOD("SetSelectionMode", TYP, T, TYP, Gtk$Gtk$SelectionMode$T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSelectionMode mode = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_list_set_selection_mode(self, mode);
	return SUCCESS;
};

METHOD("StartSelection", TYP, T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_list_start_selection(self);
	return SUCCESS;
};

METHOD("ToggleAddMode", TYP, T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_list_toggle_add_mode(self);
	return SUCCESS;
};

METHOD("ToggleFocusRow", TYP, T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_list_toggle_focus_row(self);
	return SUCCESS;
};

METHOD("ToggleRow", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * item = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_list_toggle_row(self, item);
	return SUCCESS;
};

METHOD("UndoSelection", TYP, T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_list_undo_selection(self);
	return SUCCESS;
};

METHOD("UnselectAll", TYP, T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_list_unselect_all(self);
	return SUCCESS;
};

METHOD("UnselectChild", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_list_unselect_child(self, child);
	return SUCCESS;
};

METHOD("UnselectItem", TYP, T, TYP, Std$Integer$SmallT) {
	GtkList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int item = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_list_unselect_item(self, item);
	return SUCCESS;
};

