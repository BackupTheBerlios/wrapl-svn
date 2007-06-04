#include <Gtk/Gtk/CTreeNode.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 12
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/Gtk/CTree.h>
#include <Gtk/Gtk/Style.h>
#include <Gtk/Gtk/CellType.h>
#include <Gtk/Gtk/CTreeNode.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/DestroyNotify.h>
#include <Gtk/Gdk/Bitmap.h>
#include <Gtk/Gdk/Pixmap.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/Visibility.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(GetCellStyle, 3) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkStyle * result = gtk_ctree_node_get_cell_style(ctree, node, column);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetCellType, 3) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkCellType result = gtk_ctree_node_get_cell_type(ctree, node, column);
	Gtk$Gtk$CellType_t *_result = new(Gtk$Gtk$CellType_t);
	_result->Type = Gtk$Gtk$CellType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetPixmap, 5) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkPixmap** pixmap = 0;
	GdkBitmap** mask = 0;
	int result = gtk_ctree_node_get_pixmap(ctree, node, column, pixmap, mask);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetPixtext, 7) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	const char * const * text;
	guint8* spacing = 0;
	GdkPixmap** pixmap = 0;
	GdkBitmap** mask = 0;
	int result = gtk_ctree_node_get_pixtext(ctree, node, column, text, spacing, pixmap, mask);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetRowData, 2) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	void * result = gtk_ctree_node_get_row_data(ctree, node);
	Result->Val = Std$Address$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetRowStyle, 2) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	GtkStyle * result = gtk_ctree_node_get_row_style(ctree, node);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetSelectable, 2) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int result = gtk_ctree_node_get_selectable(ctree, node);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetText, 4) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	const char * const * text;
	int result = gtk_ctree_node_get_text(ctree, node, column, text);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_ctree_node_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(IsVisible, 2) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	GtkVisibility result = gtk_ctree_node_is_visible(ctree, node);
	Gtk$Gtk$Visibility_t *_result = new(Gtk$Gtk$Visibility_t);
	_result->Type = Gtk$Gtk$Visibility$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

GLOBAL_FUNCTION(Moveto, 5) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	double row_align = ((Std$Real_t *)Args[3].Val)->Value;
	double col_align = ((Std$Real_t *)Args[4].Val)->Value;
	gtk_ctree_node_moveto(ctree, node, column, row_align, col_align);
	return SUCCESS;
};

GLOBAL_FUNCTION(Nth, 2) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkCTreeNode * result = gtk_ctree_node_nth(ctree, row);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(SetBackground, 3) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[2].Val)->Value;
	gtk_ctree_node_set_background(ctree, node, color);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetCellStyle, 4) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	gtk_ctree_node_set_cell_style(ctree, node, column, style);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetForeground, 3) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[2].Val)->Value;
	gtk_ctree_node_set_foreground(ctree, node, color);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetPixmap, 5) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkPixmap * pixmap = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[4].Val)->Handle;
	gtk_ctree_node_set_pixmap(ctree, node, column, pixmap, mask);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetPixtext, 7) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char *text = Std$String$flatten(Args[3].Val);
	int spacing = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GdkPixmap * pixmap = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[6].Val)->Handle;
	gtk_ctree_node_set_pixtext(ctree, node, column, text, spacing, pixmap, mask);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetRowData, 3) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	gtk_ctree_node_set_row_data(ctree, node, data);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetRowDataFull, 4) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[3].Val);
	gtk_ctree_node_set_row_data_full(ctree, node, data, destroy);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetRowStyle, 3) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_ctree_node_set_row_style(ctree, node, style);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetSelectable, 3) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int selectable = Args[2].Val == $true;
	gtk_ctree_node_set_selectable(ctree, node, selectable);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetShift, 5) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int vertical = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int horizontal = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_ctree_node_set_shift(ctree, node, column, vertical, horizontal);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetText, 4) {
	GtkCTree * ctree = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCTreeNode * node= &((Gtk$Gtk$CTreeNode_t *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char *text = Std$String$flatten(Args[3].Val);
	gtk_ctree_node_set_text(ctree, node, column, text);
	return SUCCESS;
};

