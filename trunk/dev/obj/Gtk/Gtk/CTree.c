#include <Gtk/Gtk/CTree.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 13
#include <Gtk/Gtk/CTreeCompareDragFunc.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/CTreeExpanderStyle.h>
#include <Gtk/Gtk/CTreeRow.h>
#include <Gtk/Gtk/CTree.h>
#include <Gtk/Gtk/CTreeFunc.h>
#include <Gtk/Gtk/CTreeNode.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Bitmap.h>
#include <Gtk/Gdk/Pixmap.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/CTreeGNodeFunc.h>
#include <Gtk/Gtk/CTreeLineStyle.h>
/***********************************/
TYPE(T, Gtk$Gtk$CList$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 2) {
	int columns = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int tree_column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkCTree * result = gtk_ctree_new(columns, tree_column);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithTitles, 3) {
	int columns = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int tree_column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	const char * const * titles;
	GtkCTree * result = gtk_ctree_new_with_titles(columns, tree_column, titles);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_ctree_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Collapse", TYP, T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	gtk_ctree_collapse(self, node);
	return SUCCESS;
};

METHOD("CollapseRecursive", TYP, T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	gtk_ctree_collapse_recursive(self, node);
	return SUCCESS;
};

METHOD("CollapseToDepth", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Std$Integer$SmallT) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int depth = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_ctree_collapse_to_depth(self, node, depth);
	return SUCCESS;
};

METHOD("Expand", TYP, T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	gtk_ctree_expand(self, node);
	return SUCCESS;
};

METHOD("ExpandRecursive", TYP, T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	gtk_ctree_expand_recursive(self, node);
	return SUCCESS;
};

METHOD("ExpandToDepth", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Std$Integer$SmallT) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int depth = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_ctree_expand_to_depth(self, node, depth);
	return SUCCESS;
};

METHOD("ExportToGnode", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GNode* parent = 0;
	GNode* sibling = 0;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[3].Val)->Value;
	GtkCTreeGNodeFunc func = Gtk$Gtk$CTreeGNodeFunc$new(Args[4].Val);
	void *data = ((Std$Address_t *)Args[5].Val)->Value;
	GNode* result = gtk_ctree_export_to_gnode(self, parent, sibling, node, func, data);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Find", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	GtkCTreeNode * child= &((Gtk$Gtk$CTreeNode_t *)Args[2].Val)->Value;
	int result = gtk_ctree_find(self, node, child);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("FindAllByRowData", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Std$Address$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GList* result = gtk_ctree_find_all_by_row_data(self, node, data);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("FindAllByRowDataCustom", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Std$Address$T, TYP, Std$Object$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GCompareFunc func = 0;
	GList* result = gtk_ctree_find_all_by_row_data_custom(self, node, data, func);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("FindByRowData", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Std$Address$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkCTreeNode * result = gtk_ctree_find_by_row_data(self, node, data);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("FindByRowDataCustom", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Std$Address$T, TYP, Std$Object$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GCompareFunc func = 0;
	GtkCTreeNode * result = gtk_ctree_find_by_row_data_custom(self, node, data, func);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("FindNodePtr", TYP, T, TYP, Gtk$Gtk$CTreeRow$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeRow * ctree_row= &((Gtk$Gtk$CTreeRow_t *)Args[1].Val)->Value;
	GtkCTreeNode * result = gtk_ctree_find_node_ptr(self, ctree_row);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetNodeInfo", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Std$List$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	const char * const * text;
	guint8* spacing = 0;
	GdkPixmap** pixmap_closed = 0;
	GdkBitmap** mask_closed = 0;
	GdkPixmap** pixmap_opened = 0;
	GdkBitmap** mask_opened = 0;
	gboolean* is_leaf = 0;
	gboolean* expanded = 0;
	int result = gtk_ctree_get_node_info(self, node, text, spacing, pixmap_closed, mask_closed, pixmap_opened, mask_opened, is_leaf, expanded);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("InsertGnode", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Std$Object$T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * parent= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	GtkCTreeNode * sibling= &((Gtk$Gtk$CTreeNode_t *)Args[2].Val)->Value;
	GNode* gnode = 0;
	GtkCTreeGNodeFunc func = Gtk$Gtk$CTreeGNodeFunc$new(Args[4].Val);
	void *data = ((Std$Address_t *)Args[5].Val)->Value;
	GtkCTreeNode * result = gtk_ctree_insert_gnode(self, parent, sibling, gnode, func, data);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("InsertNode", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Std$List$T, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$Pixmap$T, TYP, Gtk$Gdk$Bitmap$T, TYP, Gtk$Gdk$Pixmap$T, TYP, Gtk$Gdk$Bitmap$T, TYP, Std$Symbol$T, TYP, Std$Symbol$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * parent= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	GtkCTreeNode * sibling= &((Gtk$Gtk$CTreeNode_t *)Args[2].Val)->Value;
	const char * const * text;
	int spacing = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GdkPixmap * pixmap_closed = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	GdkBitmap * mask_closed = ((Gtk$GObject$Object_t *)Args[6].Val)->Handle;
	GdkPixmap * pixmap_opened = ((Gtk$GObject$Object_t *)Args[7].Val)->Handle;
	GdkBitmap * mask_opened = ((Gtk$GObject$Object_t *)Args[8].Val)->Handle;
	int is_leaf = Args[9].Val == $true;
	int expanded = Args[10].Val == $true;
	GtkCTreeNode * result = gtk_ctree_insert_node(self, parent, sibling, text, spacing, pixmap_closed, mask_closed, pixmap_opened, mask_opened, is_leaf, expanded);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("IsAncestor", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	GtkCTreeNode * child= &((Gtk$Gtk$CTreeNode_t *)Args[2].Val)->Value;
	int result = gtk_ctree_is_ancestor(self, node, child);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsHotSpot", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gtk_ctree_is_hot_spot(self, x, y);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsViewable", TYP, T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int result = gtk_ctree_is_viewable(self, node);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Last", TYP, T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	GtkCTreeNode * result = gtk_ctree_last(self, node);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Move", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	GtkCTreeNode * new_parent= &((Gtk$Gtk$CTreeNode_t *)Args[2].Val)->Value;
	GtkCTreeNode * new_sibling= &((Gtk$Gtk$CTreeNode_t *)Args[3].Val)->Value;
	gtk_ctree_move(self, node, new_parent, new_sibling);
	return SUCCESS;
};

METHOD("PostRecursive", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	GtkCTreeFunc func = Gtk$Gtk$CTreeFunc$new(Args[2].Val);
	void *data = ((Std$Address_t *)Args[3].Val)->Value;
	gtk_ctree_post_recursive(self, node, func, data);
	return SUCCESS;
};

METHOD("PostRecursiveToDepth", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Std$Integer$SmallT, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int depth = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkCTreeFunc func = Gtk$Gtk$CTreeFunc$new(Args[3].Val);
	void *data = ((Std$Address_t *)Args[4].Val)->Value;
	gtk_ctree_post_recursive_to_depth(self, node, depth, func, data);
	return SUCCESS;
};

METHOD("PreRecursive", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	GtkCTreeFunc func = Gtk$Gtk$CTreeFunc$new(Args[2].Val);
	void *data = ((Std$Address_t *)Args[3].Val)->Value;
	gtk_ctree_pre_recursive(self, node, func, data);
	return SUCCESS;
};

METHOD("PreRecursiveToDepth", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Std$Integer$SmallT, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int depth = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkCTreeFunc func = Gtk$Gtk$CTreeFunc$new(Args[3].Val);
	void *data = ((Std$Address_t *)Args[4].Val)->Value;
	gtk_ctree_pre_recursive_to_depth(self, node, depth, func, data);
	return SUCCESS;
};

METHOD("RealSelectRecursive", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Std$Integer$SmallT) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int state = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_ctree_real_select_recursive(self, node, state);
	return SUCCESS;
};

METHOD("RemoveNode", TYP, T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	gtk_ctree_remove_node(self, node);
	return SUCCESS;
};

METHOD("Select", TYP, T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	gtk_ctree_select(self, node);
	return SUCCESS;
};

METHOD("SelectRecursive", TYP, T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	gtk_ctree_select_recursive(self, node);
	return SUCCESS;
};

METHOD("SetDragCompareFunc", TYP, T, TYP, Std$Function$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeCompareDragFunc cmp_func = Gtk$Gtk$CTreeCompareDragFunc$new(Args[1].Val);
	gtk_ctree_set_drag_compare_func(self, cmp_func);
	return SUCCESS;
};

METHOD("SetExpanderStyle", TYP, T, TYP, Gtk$Gtk$CTreeExpanderStyle$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeExpanderStyle expander_style = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_ctree_set_expander_style(self, expander_style);
	return SUCCESS;
};

METHOD("SetIndent", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int indent = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_ctree_set_indent(self, indent);
	return SUCCESS;
};

METHOD("SetLineStyle", TYP, T, TYP, Gtk$Gtk$CTreeLineStyle$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeLineStyle line_style = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_ctree_set_line_style(self, line_style);
	return SUCCESS;
};

METHOD("SetNodeInfo", TYP, T, TYP, Gtk$Gtk$CTreeNode$T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$Pixmap$T, TYP, Gtk$Gdk$Bitmap$T, TYP, Gtk$Gdk$Pixmap$T, TYP, Gtk$Gdk$Bitmap$T, TYP, Std$Symbol$T, TYP, Std$Symbol$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	char *text = Std$String$flatten(Args[2].Val);
	int spacing = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkPixmap * pixmap_closed = ((Gtk$GObject$Object_t *)Args[4].Val)->Handle;
	GdkBitmap * mask_closed = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	GdkPixmap * pixmap_opened = ((Gtk$GObject$Object_t *)Args[6].Val)->Handle;
	GdkBitmap * mask_opened = ((Gtk$GObject$Object_t *)Args[7].Val)->Handle;
	int is_leaf = Args[8].Val == $true;
	int expanded = Args[9].Val == $true;
	gtk_ctree_set_node_info(self, node, text, spacing, pixmap_closed, mask_closed, pixmap_opened, mask_opened, is_leaf, expanded);
	return SUCCESS;
};

METHOD("SetShowStub", TYP, T, TYP, Std$Symbol$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int show_stub = Args[1].Val == $true;
	gtk_ctree_set_show_stub(self, show_stub);
	return SUCCESS;
};

METHOD("SetSpacing", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int spacing = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_ctree_set_spacing(self, spacing);
	return SUCCESS;
};

METHOD("SortNode", TYP, T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	gtk_ctree_sort_node(self, node);
	return SUCCESS;
};

METHOD("SortRecursive", TYP, T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	gtk_ctree_sort_recursive(self, node);
	return SUCCESS;
};

METHOD("ToggleExpansion", TYP, T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	gtk_ctree_toggle_expansion(self, node);
	return SUCCESS;
};

METHOD("ToggleExpansionRecursive", TYP, T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	gtk_ctree_toggle_expansion_recursive(self, node);
	return SUCCESS;
};

METHOD("Unselect", TYP, T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	gtk_ctree_unselect(self, node);
	return SUCCESS;
};

METHOD("UnselectRecursive", TYP, T, TYP, Gtk$Gtk$CTreeNode$T) {
	GtkCTree * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	gtk_ctree_unselect_recursive(self, node);
	return SUCCESS;
};

