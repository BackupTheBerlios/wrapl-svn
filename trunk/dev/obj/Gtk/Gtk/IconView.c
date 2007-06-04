#include <Gtk/Gtk/IconView.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 14
#include <Gtk/Gtk/TreeModel.h>
#include <Gtk/Gtk/IconViewDropPosition.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TreePath.h>
#include <Gtk/Gtk/IconView.h>
#include <Gtk/Gtk/Orientation.h>
#include <Gtk/Gtk/IconViewForeachFunc.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/SelectionMode.h>
#include <Gtk/Gtk/CellRenderer.h>
#include <Gtk/Gdk/Pixmap.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/TreeModel.h>
#include <Gtk/Gtk/TargetEntry.h>
/***********************************/
TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkIconView * result = gtk_icon_view_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithModel, 1) {
	GtkTreeModel * model = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkIconView * result = gtk_icon_view_new_with_model(model);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_icon_view_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("CreateDragIcon", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GdkPixmap * result = gtk_icon_view_create_drag_icon(self, path);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("EnableModelDragDest", TYP, T, TYP, Gtk$Gtk$TargetEntry$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTargetEntry * targets= &((Gtk$Gtk$TargetEntry_t *)Args[1].Val)->Value;
	int n_targets = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int actions = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_icon_view_enable_model_drag_dest(self, targets, n_targets, actions);
	return SUCCESS;
};

METHOD("EnableModelDragSource", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$TargetEntry$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int start_button_mask = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkTargetEntry * targets= &((Gtk$Gtk$TargetEntry_t *)Args[2].Val)->Value;
	int n_targets = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int actions = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_icon_view_enable_model_drag_source(self, start_button_mask, targets, n_targets, actions);
	return SUCCESS;
};

METHOD("GetColumnSpacing", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_icon_view_get_column_spacing(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetColumns", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_icon_view_get_columns(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetCursor", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath** path = 0;
	GtkCellRenderer** cell = 0;
	int result = gtk_icon_view_get_cursor(self, path, cell);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetDestItemAtPos", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int drag_x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int drag_y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkTreePath** path = 0;
	GtkIconViewDropPosition* pos = 0;
	int result = gtk_icon_view_get_dest_item_at_pos(self, drag_x, drag_y, path, pos);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetDragDestItem", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath** path = 0;
	GtkIconViewDropPosition* pos = 0;
	gtk_icon_view_get_drag_dest_item(self, path, pos);
	return SUCCESS;
};

METHOD("GetItemAtPos", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkTreePath** path = 0;
	GtkCellRenderer** cell = 0;
	int result = gtk_icon_view_get_item_at_pos(self, x, y, path, cell);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetItemWidth", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_icon_view_get_item_width(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetMargin", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_icon_view_get_margin(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetMarkupColumn", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_icon_view_get_markup_column(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetModel", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModel * result = gtk_icon_view_get_model(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetOrientation", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkOrientation result = gtk_icon_view_get_orientation(self);
	Gtk$Gtk$Orientation_t *_result = new(Gtk$Gtk$Orientation_t);
	_result->Type = Gtk$Gtk$Orientation$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetPathAtPos", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkTreePath * result = gtk_icon_view_get_path_at_pos(self, x, y);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetPixbufColumn", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_icon_view_get_pixbuf_column(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetReorderable", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_icon_view_get_reorderable(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetRowSpacing", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_icon_view_get_row_spacing(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetSelectedItems", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* result = gtk_icon_view_get_selected_items(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetSelectionMode", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSelectionMode result = gtk_icon_view_get_selection_mode(self);
	Gtk$Gtk$SelectionMode_t *_result = new(Gtk$Gtk$SelectionMode_t);
	_result->Type = Gtk$Gtk$SelectionMode$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetSpacing", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_icon_view_get_spacing(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetTextColumn", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_icon_view_get_text_column(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetVisibleRange", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath** start_path = 0;
	GtkTreePath** end_path = 0;
	int result = gtk_icon_view_get_visible_range(self, start_path, end_path);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ItemActivated", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	gtk_icon_view_item_activated(self, path);
	return SUCCESS;
};

METHOD("PathIsSelected", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	int result = gtk_icon_view_path_is_selected(self, path);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ScrollToPath", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Std$Symbol$T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	int use_align = Args[2].Val == $true;
	double row_align = ((Std$Real_t *)Args[3].Val)->Value;
	double col_align = ((Std$Real_t *)Args[4].Val)->Value;
	gtk_icon_view_scroll_to_path(self, path, use_align, row_align, col_align);
	return SUCCESS;
};

METHOD("SelectAll", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_icon_view_select_all(self);
	return SUCCESS;
};

METHOD("SelectPath", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	gtk_icon_view_select_path(self, path);
	return SUCCESS;
};

METHOD("SelectedForeach", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkIconViewForeachFunc func = Gtk$Gtk$IconViewForeachFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	gtk_icon_view_selected_foreach(self, func, data);
	return SUCCESS;
};

METHOD("SetColumnSpacing", TYP, T, TYP, Std$Integer$SmallT) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column_spacing = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_icon_view_set_column_spacing(self, column_spacing);
	return SUCCESS;
};

METHOD("SetColumns", TYP, T, TYP, Std$Integer$SmallT) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int columns = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_icon_view_set_columns(self, columns);
	return SUCCESS;
};

METHOD("SetCursor", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$CellRenderer$T, TYP, Std$Symbol$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkCellRenderer * cell = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int start_editing = Args[3].Val == $true;
	gtk_icon_view_set_cursor(self, path, cell, start_editing);
	return SUCCESS;
};

METHOD("SetDragDestItem", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$IconViewDropPosition$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkIconViewDropPosition pos = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_icon_view_set_drag_dest_item(self, path, pos);
	return SUCCESS;
};

METHOD("SetItemWidth", TYP, T, TYP, Std$Integer$SmallT) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int item_width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_icon_view_set_item_width(self, item_width);
	return SUCCESS;
};

METHOD("SetMargin", TYP, T, TYP, Std$Integer$SmallT) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int margin = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_icon_view_set_margin(self, margin);
	return SUCCESS;
};

METHOD("SetMarkupColumn", TYP, T, TYP, Std$Integer$SmallT) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_icon_view_set_markup_column(self, column);
	return SUCCESS;
};

METHOD("SetModel", TYP, T, TYP, Gtk$Gtk$TreeModel$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModel * model = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_icon_view_set_model(self, model);
	return SUCCESS;
};

METHOD("SetOrientation", TYP, T, TYP, Gtk$Gtk$Orientation$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkOrientation orientation = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_icon_view_set_orientation(self, orientation);
	return SUCCESS;
};

METHOD("SetPixbufColumn", TYP, T, TYP, Std$Integer$SmallT) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_icon_view_set_pixbuf_column(self, column);
	return SUCCESS;
};

METHOD("SetReorderable", TYP, T, TYP, Std$Symbol$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int reorderable = Args[1].Val == $true;
	gtk_icon_view_set_reorderable(self, reorderable);
	return SUCCESS;
};

METHOD("SetRowSpacing", TYP, T, TYP, Std$Integer$SmallT) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row_spacing = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_icon_view_set_row_spacing(self, row_spacing);
	return SUCCESS;
};

METHOD("SetSelectionMode", TYP, T, TYP, Gtk$Gtk$SelectionMode$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSelectionMode mode = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_icon_view_set_selection_mode(self, mode);
	return SUCCESS;
};

METHOD("SetSpacing", TYP, T, TYP, Std$Integer$SmallT) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int spacing = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_icon_view_set_spacing(self, spacing);
	return SUCCESS;
};

METHOD("SetTextColumn", TYP, T, TYP, Std$Integer$SmallT) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_icon_view_set_text_column(self, column);
	return SUCCESS;
};

METHOD("UnselectAll", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_icon_view_unselect_all(self);
	return SUCCESS;
};

METHOD("UnselectPath", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	gtk_icon_view_unselect_path(self, path);
	return SUCCESS;
};

METHOD("UnsetModelDragDest", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_icon_view_unset_model_drag_dest(self);
	return SUCCESS;
};

METHOD("UnsetModelDragSource", TYP, T) {
	GtkIconView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_icon_view_unset_model_drag_source(self);
	return SUCCESS;
};

