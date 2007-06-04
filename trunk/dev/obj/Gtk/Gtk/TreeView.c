#include <Gtk/Gtk/TreeView.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 27
#include <Gtk/Gtk/TreeModel.h>
#include <Gtk/Gtk/TreeViewSearchPositionFunc.h>
#include <Gtk/Gtk/TreeViewDropPosition.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TreeViewRowSeparatorFunc.h>
#include <Gtk/Gtk/TreeDestroyCountFunc.h>
#include <Gtk/Gtk/TreePath.h>
#include <Gtk/Gtk/TreeView.h>
#include <Gtk/Gtk/Entry.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/DestroyNotify.h>
#include <Gtk/Gtk/TreeViewColumn.h>
#include <Gtk/Gtk/TreeViewSearchEqualFunc.h>
#include <Gtk/Gtk/Adjustment.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Gtk/Gtk/TreeSelection.h>
#include <Gtk/Gtk/CellRenderer.h>
#include <Gtk/Gdk/Pixmap.h>
#include <Gtk/Gdk/Window.h>
#include <Gtk/Gtk/TreeCellDataFunc.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/TreeModel.h>
#include <Gtk/Gtk/TargetEntry.h>
#include <Gtk/Gtk/TreeViewGridLines.h>
#include <Gtk/Gtk/TreeViewMappingFunc.h>
#include <Gtk/Gtk/TreeViewColumnDropFunc.h>
#include <Gtk/Gtk/TreeViewSearchPositionFunc.h>
/***********************************/
TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkTreeView * result = gtk_tree_view_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithModel, 1) {
	GtkTreeModel * model = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeView * result = gtk_tree_view_new_with_model(model);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tree_view_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ModeGetType, 0) {
	GType result = gtk_tree_view_mode_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AppendColumn", TYP, T, TYP, Gtk$Gtk$TreeViewColumn$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewColumn * column = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_tree_view_append_column(self, column);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("CollapseAll", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tree_view_collapse_all(self);
	return SUCCESS;
};

METHOD("CollapseRow", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	int result = gtk_tree_view_collapse_row(self, path);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ColumnsAutosize", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tree_view_columns_autosize(self);
	return SUCCESS;
};

METHOD("CreateRowDragIcon", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GdkPixmap * result = gtk_tree_view_create_row_drag_icon(self, path);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("EnableModelDragDest", TYP, T, TYP, Gtk$Gtk$TargetEntry$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTargetEntry * targets= &((Gtk$Gtk$TargetEntry_t *)Args[1].Val)->Value;
	int n_targets = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int actions = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_tree_view_enable_model_drag_dest(self, targets, n_targets, actions);
	return SUCCESS;
};

METHOD("EnableModelDragSource", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$TargetEntry$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int start_button_mask = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkTargetEntry * targets= &((Gtk$Gtk$TargetEntry_t *)Args[2].Val)->Value;
	int n_targets = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int actions = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_tree_view_enable_model_drag_source(self, start_button_mask, targets, n_targets, actions);
	return SUCCESS;
};

METHOD("ExpandAll", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tree_view_expand_all(self);
	return SUCCESS;
};

METHOD("ExpandRow", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Std$Symbol$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	int open_all = Args[2].Val == $true;
	int result = gtk_tree_view_expand_row(self, path, open_all);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ExpandToPath", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	gtk_tree_view_expand_to_path(self, path);
	return SUCCESS;
};

METHOD("GetBackgroundArea", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$TreeViewColumn$T, TYP, Gtk$Gdk$Rectangle$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkTreeViewColumn * column = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	GdkRectangle * rect= &((Gtk$Gdk$Rectangle_t *)Args[3].Val)->Value;
	gtk_tree_view_get_background_area(self, path, column, rect);
	return SUCCESS;
};

METHOD("GetBinWindow", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * result = gtk_tree_view_get_bin_window(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetCellArea", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$TreeViewColumn$T, TYP, Gtk$Gdk$Rectangle$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkTreeViewColumn * column = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	GdkRectangle * rect= &((Gtk$Gdk$Rectangle_t *)Args[3].Val)->Value;
	gtk_tree_view_get_cell_area(self, path, column, rect);
	return SUCCESS;
};

METHOD("GetColumn", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int n = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkTreeViewColumn * result = gtk_tree_view_get_column(self, n);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetColumns", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList * result = gtk_tree_view_get_columns(self);
	if (result) {
		int _length = 1;
		GList *node = result;
		node->data = Gtk$GObject$Object$to_riva(node->data);
		while (node->next) {
			node = node->next;
			node->data = Gtk$GObject$Object$to_riva(node->data);
			_length++;
		};
		Std$List_t *list = new(Std$List_t);
		list->Type = Std$List$T;
		list->Cache = list->Head = result;
		list->Tail = node;
		list->Length = _length;
		list->Index = 1;
		list->Access = 4;
		Result->Val = list;
	} else {
		Result->Val = Std$List$new(0);
	};
	return SUCCESS;
};

METHOD("GetCursor", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath** path = 0;
	GtkTreeViewColumn** focus_column = 0;
	gtk_tree_view_get_cursor(self, path, focus_column);
	return SUCCESS;
};

METHOD("GetDestRowAtPos", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int drag_x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int drag_y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkTreePath** path = 0;
	GtkTreeViewDropPosition* pos = 0;
	int result = gtk_tree_view_get_dest_row_at_pos(self, drag_x, drag_y, path, pos);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetDragDestRow", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath** path = 0;
	GtkTreeViewDropPosition* pos = 0;
	gtk_tree_view_get_drag_dest_row(self, path, pos);
	return SUCCESS;
};

METHOD("GetEnableSearch", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_get_enable_search(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetEnableTreeLines", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_get_enable_tree_lines(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetExpanderColumn", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewColumn * result = gtk_tree_view_get_expander_column(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetFixedHeightMode", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_get_fixed_height_mode(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetGridLines", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewGridLines result = gtk_tree_view_get_grid_lines(self);
	Gtk$Gtk$TreeViewGridLines_t *_result = new(Gtk$Gtk$TreeViewGridLines_t);
	_result->Type = Gtk$Gtk$TreeViewGridLines$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetHadjustment", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * result = gtk_tree_view_get_hadjustment(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetHeadersClickable", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_get_headers_clickable(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetHeadersVisible", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_get_headers_visible(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetHoverExpand", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_get_hover_expand(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetHoverSelection", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_get_hover_selection(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetModel", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModel * result = gtk_tree_view_get_model(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPathAtPos", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkTreePath** path = 0;
	GtkTreeViewColumn** column = 0;
	gint* cell_x = 0;
	gint* cell_y = 0;
	int result = gtk_tree_view_get_path_at_pos(self, x, y, path, column, cell_x, cell_y);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetReorderable", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_get_reorderable(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetRowSeparatorFunc", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewRowSeparatorFunc result = gtk_tree_view_get_row_separator_func(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetRubberBanding", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_get_rubber_banding(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetRulesHint", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_get_rules_hint(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSearchColumn", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_get_search_column(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetSearchEntry", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkEntry * result = gtk_tree_view_get_search_entry(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetSearchEqualFunc", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewSearchEqualFunc result = gtk_tree_view_get_search_equal_func(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetSearchPositionFunc", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewSearchPositionFunc result = gtk_tree_view_get_search_position_func(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetSelection", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeSelection * result = gtk_tree_view_get_selection(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetVadjustment", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * result = gtk_tree_view_get_vadjustment(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetVisibleRange", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath** start_path = 0;
	GtkTreePath** end_path = 0;
	int result = gtk_tree_view_get_visible_range(self, start_path, end_path);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetVisibleRect", TYP, T, TYP, Gtk$Gdk$Rectangle$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRectangle * visible_rect= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	gtk_tree_view_get_visible_rect(self, visible_rect);
	return SUCCESS;
};

METHOD("InsertColumn", TYP, T, TYP, Gtk$Gtk$TreeViewColumn$T, TYP, Std$Integer$SmallT) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewColumn * column = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gtk_tree_view_insert_column(self, column, position);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("InsertColumnWithAttributes", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$String$T, TYP, Gtk$Gtk$CellRenderer$T, TYP, Std$Object$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *title = Std$String$flatten(Args[2].Val);
	GtkCellRenderer * cell = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	char *___ = 0;
	int result = gtk_tree_view_insert_column_with_attributes(self, position, title, cell, ___);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("InsertColumnWithDataFunc", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$String$T, TYP, Gtk$Gtk$CellRenderer$T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Object$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *title = Std$String$flatten(Args[2].Val);
	GtkCellRenderer * cell = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	GtkTreeCellDataFunc func = Gtk$Gtk$TreeCellDataFunc$new(Args[4].Val);
	void *data = ((Std$Address_t *)Args[5].Val)->Value;
	GDestroyNotify dnotify = 0;
	int result = gtk_tree_view_insert_column_with_data_func(self, position, title, cell, func, data, dnotify);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("MapExpandedRows", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewMappingFunc func = Gtk$Gtk$TreeViewMappingFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	gtk_tree_view_map_expanded_rows(self, func, data);
	return SUCCESS;
};

METHOD("MoveColumnAfter", TYP, T, TYP, Gtk$Gtk$TreeViewColumn$T, TYP, Gtk$Gtk$TreeViewColumn$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewColumn * column = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeViewColumn * base_column = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_tree_view_move_column_after(self, column, base_column);
	return SUCCESS;
};

METHOD("RemoveColumn", TYP, T, TYP, Gtk$Gtk$TreeViewColumn$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewColumn * column = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_tree_view_remove_column(self, column);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("RowActivated", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$TreeViewColumn$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkTreeViewColumn * column = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_tree_view_row_activated(self, path, column);
	return SUCCESS;
};

METHOD("RowExpanded", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	int result = gtk_tree_view_row_expanded(self, path);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ScrollToCell", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$TreeViewColumn$T, TYP, Std$Symbol$T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkTreeViewColumn * column = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int use_align = Args[3].Val == $true;
	double row_align = ((Std$Real_t *)Args[4].Val)->Value;
	double col_align = ((Std$Real_t *)Args[5].Val)->Value;
	gtk_tree_view_scroll_to_cell(self, path, column, use_align, row_align, col_align);
	return SUCCESS;
};

METHOD("ScrollToPoint", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int tree_x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int tree_y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_tree_view_scroll_to_point(self, tree_x, tree_y);
	return SUCCESS;
};

METHOD("SetColumnDragFunction", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewColumnDropFunc func = Gtk$Gtk$TreeViewColumnDropFunc$new(Args[1].Val);
	void *user_data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[3].Val);
	gtk_tree_view_set_column_drag_function(self, func, user_data, destroy);
	return SUCCESS;
};

METHOD("SetCursor", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$TreeViewColumn$T, TYP, Std$Symbol$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkTreeViewColumn * focus_column = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int start_editing = Args[3].Val == $true;
	gtk_tree_view_set_cursor(self, path, focus_column, start_editing);
	return SUCCESS;
};

METHOD("SetCursorOnCell", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$TreeViewColumn$T, TYP, Gtk$Gtk$CellRenderer$T, TYP, Std$Symbol$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkTreeViewColumn * focus_column = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	GtkCellRenderer * focus_cell = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	int start_editing = Args[4].Val == $true;
	gtk_tree_view_set_cursor_on_cell(self, path, focus_column, focus_cell, start_editing);
	return SUCCESS;
};

METHOD("SetDestroyCountFunc", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeDestroyCountFunc func = Gtk$Gtk$TreeDestroyCountFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[3].Val);
	gtk_tree_view_set_destroy_count_func(self, func, data, destroy);
	return SUCCESS;
};

METHOD("SetDragDestRow", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$TreeViewDropPosition$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkTreeViewDropPosition pos = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_tree_view_set_drag_dest_row(self, path, pos);
	return SUCCESS;
};

METHOD("SetEnableSearch", TYP, T, TYP, Std$Symbol$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int enable_search = Args[1].Val == $true;
	gtk_tree_view_set_enable_search(self, enable_search);
	return SUCCESS;
};

METHOD("SetEnableTreeLines", TYP, T, TYP, Std$Symbol$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int enabled = Args[1].Val == $true;
	gtk_tree_view_set_enable_tree_lines(self, enabled);
	return SUCCESS;
};

METHOD("SetExpanderColumn", TYP, T, TYP, Gtk$Gtk$TreeViewColumn$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewColumn * column = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_tree_view_set_expander_column(self, column);
	return SUCCESS;
};

METHOD("SetFixedHeightMode", TYP, T, TYP, Std$Symbol$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int enable = Args[1].Val == $true;
	gtk_tree_view_set_fixed_height_mode(self, enable);
	return SUCCESS;
};

METHOD("SetGridLines", TYP, T, TYP, Gtk$Gtk$TreeViewGridLines$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewGridLines grid_lines = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_tree_view_set_grid_lines(self, grid_lines);
	return SUCCESS;
};

METHOD("SetHadjustment", TYP, T, TYP, Gtk$Gtk$Adjustment$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_tree_view_set_hadjustment(self, adjustment);
	return SUCCESS;
};

METHOD("SetHeadersClickable", TYP, T, TYP, Std$Symbol$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_tree_view_set_headers_clickable(self, setting);
	return SUCCESS;
};

METHOD("SetHeadersVisible", TYP, T, TYP, Std$Symbol$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int headers_visible = Args[1].Val == $true;
	gtk_tree_view_set_headers_visible(self, headers_visible);
	return SUCCESS;
};

METHOD("SetHoverExpand", TYP, T, TYP, Std$Symbol$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int expand = Args[1].Val == $true;
	gtk_tree_view_set_hover_expand(self, expand);
	return SUCCESS;
};

METHOD("SetHoverSelection", TYP, T, TYP, Std$Symbol$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int hover = Args[1].Val == $true;
	gtk_tree_view_set_hover_selection(self, hover);
	return SUCCESS;
};

METHOD("SetModel", TYP, T, TYP, Gtk$Gtk$TreeModel$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModel * model = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_tree_view_set_model(self, model);
	return SUCCESS;
};

METHOD("SetReorderable", TYP, T, TYP, Std$Symbol$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int reorderable = Args[1].Val == $true;
	gtk_tree_view_set_reorderable(self, reorderable);
	return SUCCESS;
};

METHOD("SetRowSeparatorFunc", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewRowSeparatorFunc func = Gtk$Gtk$TreeViewRowSeparatorFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[3].Val);
	gtk_tree_view_set_row_separator_func(self, func, data, destroy);
	return SUCCESS;
};

METHOD("SetRubberBanding", TYP, T, TYP, Std$Symbol$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int enable = Args[1].Val == $true;
	gtk_tree_view_set_rubber_banding(self, enable);
	return SUCCESS;
};

METHOD("SetRulesHint", TYP, T, TYP, Std$Symbol$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_tree_view_set_rules_hint(self, setting);
	return SUCCESS;
};

METHOD("SetSearchColumn", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_tree_view_set_search_column(self, column);
	return SUCCESS;
};

METHOD("SetSearchEntry", TYP, T, TYP, Gtk$Gtk$Entry$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkEntry * entry = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_tree_view_set_search_entry(self, entry);
	return SUCCESS;
};

METHOD("SetSearchEqualFunc", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewSearchEqualFunc search_equal_func = Gtk$Gtk$TreeViewSearchEqualFunc$new(Args[1].Val);
	void *search_user_data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkDestroyNotify search_destroy = Gtk$Gtk$DestroyNotify$new(Args[3].Val);
	gtk_tree_view_set_search_equal_func(self, search_equal_func, search_user_data, search_destroy);
	return SUCCESS;
};

METHOD("SetSearchPositionFunc", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Object$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewSearchPositionFunc func = Gtk$Gtk$TreeViewSearchPositionFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GDestroyNotify destroy = 0;
	gtk_tree_view_set_search_position_func(self, func, data, destroy);
	return SUCCESS;
};

METHOD("SetVadjustment", TYP, T, TYP, Gtk$Gtk$Adjustment$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_tree_view_set_vadjustment(self, adjustment);
	return SUCCESS;
};

METHOD("TreeToWidgetCoords", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int tx = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int ty = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gint* wx = 0;
	gint* wy = 0;
	gtk_tree_view_tree_to_widget_coords(self, tx, ty, wx, wy);
	return SUCCESS;
};

METHOD("UnsetRowsDragDest", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tree_view_unset_rows_drag_dest(self);
	return SUCCESS;
};

METHOD("UnsetRowsDragSource", TYP, T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tree_view_unset_rows_drag_source(self);
	return SUCCESS;
};

METHOD("WidgetToTreeCoords", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkTreeView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int wx = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int wy = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gint* tx = 0;
	gint* ty = 0;
	gtk_tree_view_widget_to_tree_coords(self, wx, wy, tx, ty);
	return SUCCESS;
};

