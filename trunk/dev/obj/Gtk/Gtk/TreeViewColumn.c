#include <Gtk/Gtk/TreeViewColumn.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 13
#include <Gtk/Gtk/SortType.h>
#include <Gtk/Gtk/TreeViewColumnSizing.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TreeIter.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/DestroyNotify.h>
#include <Gtk/Gtk/TreeViewColumn.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Gtk/Gtk/CellRenderer.h>
#include <Gtk/Gtk/Widget.h>
#include <Gtk/Gtk/TreeCellDataFunc.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/TreeModel.h>
/***********************************/
TYPE(T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkTreeViewColumn * result = gtk_tree_view_column_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithAttributes, 3) {
	char *title = Std$String$flatten(Args[0].Val);
	GtkCellRenderer * cell = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *___ = 0;
	GtkTreeViewColumn * result = gtk_tree_view_column_new_with_attributes(title, cell, ___);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tree_view_column_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddAttribute", TYP, T, TYP, Gtk$Gtk$CellRenderer$T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCellRenderer * cell_renderer = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *attribute = Std$String$flatten(Args[2].Val);
	int column = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_tree_view_column_add_attribute(self, cell_renderer, attribute, column);
	return SUCCESS;
};

METHOD("CellGetPosition", TYP, T, TYP, Gtk$Gtk$CellRenderer$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCellRenderer * cell_renderer = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gint* start_pos = 0;
	gint* width = 0;
	int result = gtk_tree_view_column_cell_get_position(self, cell_renderer, start_pos, width);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("CellGetSize", TYP, T, TYP, Gtk$Gdk$Rectangle$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRectangle * cell_area= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	gint* x_offset = 0;
	gint* y_offset = 0;
	gint* width = 0;
	gint* height = 0;
	gtk_tree_view_column_cell_get_size(self, cell_area, x_offset, y_offset, width, height);
	return SUCCESS;
};

METHOD("CellIsVisible", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_column_cell_is_visible(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("CellSetCellData", TYP, T, TYP, Gtk$Gtk$TreeModel$T, TYP, Gtk$Gtk$TreeIter$T, TYP, Std$Symbol$T, TYP, Std$Symbol$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModel * tree_model = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[2].Val)->Value;
	int is_expander = Args[3].Val == $true;
	int is_expanded = Args[4].Val == $true;
	gtk_tree_view_column_cell_set_cell_data(self, tree_model, iter, is_expander, is_expanded);
	return SUCCESS;
};

METHOD("Clear", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tree_view_column_clear(self);
	return SUCCESS;
};

METHOD("ClearAttributes", TYP, T, TYP, Gtk$Gtk$CellRenderer$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCellRenderer * cell_renderer = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_tree_view_column_clear_attributes(self, cell_renderer);
	return SUCCESS;
};

METHOD("Clicked", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tree_view_column_clicked(self);
	return SUCCESS;
};

METHOD("FocusCell", TYP, T, TYP, Gtk$Gtk$CellRenderer$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCellRenderer * cell = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_tree_view_column_focus_cell(self, cell);
	return SUCCESS;
};

METHOD("GetAlignment", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = gtk_tree_view_column_get_alignment(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetCellRenderers", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList * result = gtk_tree_view_column_get_cell_renderers(self);
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

METHOD("GetClickable", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_column_get_clickable(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetExpand", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_column_get_expand(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetFixedWidth", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_column_get_fixed_width(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetMaxWidth", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_column_get_max_width(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetMinWidth", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_column_get_min_width(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetReorderable", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_column_get_reorderable(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetResizable", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_column_get_resizable(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSizing", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewColumnSizing result = gtk_tree_view_column_get_sizing(self);
	Gtk$Gtk$TreeViewColumnSizing_t *_result = new(Gtk$Gtk$TreeViewColumnSizing_t);
	_result->Type = Gtk$Gtk$TreeViewColumnSizing$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetSortColumnId", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_column_get_sort_column_id(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetSortIndicator", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_column_get_sort_indicator(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSortOrder", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSortType result = gtk_tree_view_column_get_sort_order(self);
	Gtk$Gtk$SortType_t *_result = new(Gtk$Gtk$SortType_t);
	_result->Type = Gtk$Gtk$SortType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetSpacing", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_column_get_spacing(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetTitle", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_tree_view_column_get_title(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetVisible", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_column_get_visible(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetWidget", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_tree_view_column_get_widget(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetWidth", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_tree_view_column_get_width(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("PackEnd", TYP, T, TYP, Gtk$Gtk$CellRenderer$T, TYP, Std$Symbol$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCellRenderer * cell = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int expand = Args[2].Val == $true;
	gtk_tree_view_column_pack_end(self, cell, expand);
	return SUCCESS;
};

METHOD("PackStart", TYP, T, TYP, Gtk$Gtk$CellRenderer$T, TYP, Std$Symbol$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCellRenderer * cell = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int expand = Args[2].Val == $true;
	gtk_tree_view_column_pack_start(self, cell, expand);
	return SUCCESS;
};

METHOD("QueueResize", TYP, T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tree_view_column_queue_resize(self);
	return SUCCESS;
};

METHOD("SetAlignment", TYP, T, TYP, Std$Real$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double xalign = ((Std$Real_t *)Args[1].Val)->Value;
	gtk_tree_view_column_set_alignment(self, xalign);
	return SUCCESS;
};

METHOD("SetAttributes", TYP, T, TYP, Gtk$Gtk$CellRenderer$T, TYP, Std$Object$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCellRenderer * cell_renderer = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *___ = 0;
	gtk_tree_view_column_set_attributes(self, cell_renderer, ___);
	return SUCCESS;
};

METHOD("SetCellDataFunc", TYP, T, TYP, Gtk$Gtk$CellRenderer$T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCellRenderer * cell_renderer = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreeCellDataFunc func = Gtk$Gtk$TreeCellDataFunc$new(Args[2].Val);
	void *func_data = ((Std$Address_t *)Args[3].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[4].Val);
	gtk_tree_view_column_set_cell_data_func(self, cell_renderer, func, func_data, destroy);
	return SUCCESS;
};

METHOD("SetClickable", TYP, T, TYP, Std$Symbol$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int clickable = Args[1].Val == $true;
	gtk_tree_view_column_set_clickable(self, clickable);
	return SUCCESS;
};

METHOD("SetExpand", TYP, T, TYP, Std$Symbol$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int expand = Args[1].Val == $true;
	gtk_tree_view_column_set_expand(self, expand);
	return SUCCESS;
};

METHOD("SetFixedWidth", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int fixed_width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_tree_view_column_set_fixed_width(self, fixed_width);
	return SUCCESS;
};

METHOD("SetMaxWidth", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int max_width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_tree_view_column_set_max_width(self, max_width);
	return SUCCESS;
};

METHOD("SetMinWidth", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int min_width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_tree_view_column_set_min_width(self, min_width);
	return SUCCESS;
};

METHOD("SetReorderable", TYP, T, TYP, Std$Symbol$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int reorderable = Args[1].Val == $true;
	gtk_tree_view_column_set_reorderable(self, reorderable);
	return SUCCESS;
};

METHOD("SetResizable", TYP, T, TYP, Std$Symbol$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int resizable = Args[1].Val == $true;
	gtk_tree_view_column_set_resizable(self, resizable);
	return SUCCESS;
};

METHOD("SetSizing", TYP, T, TYP, Gtk$Gtk$TreeViewColumnSizing$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewColumnSizing type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_tree_view_column_set_sizing(self, type);
	return SUCCESS;
};

METHOD("SetSortColumnId", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int sort_column_id = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_tree_view_column_set_sort_column_id(self, sort_column_id);
	return SUCCESS;
};

METHOD("SetSortIndicator", TYP, T, TYP, Std$Symbol$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_tree_view_column_set_sort_indicator(self, setting);
	return SUCCESS;
};

METHOD("SetSortOrder", TYP, T, TYP, Gtk$Gtk$SortType$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSortType order = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_tree_view_column_set_sort_order(self, order);
	return SUCCESS;
};

METHOD("SetSpacing", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int spacing = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_tree_view_column_set_spacing(self, spacing);
	return SUCCESS;
};

METHOD("SetTitle", TYP, T, TYP, Std$String$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *title = Std$String$flatten(Args[1].Val);
	gtk_tree_view_column_set_title(self, title);
	return SUCCESS;
};

METHOD("SetVisible", TYP, T, TYP, Std$Symbol$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int visible = Args[1].Val == $true;
	gtk_tree_view_column_set_visible(self, visible);
	return SUCCESS;
};

METHOD("SetWidget", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkTreeViewColumn * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_tree_view_column_set_widget(self, widget);
	return SUCCESS;
};

