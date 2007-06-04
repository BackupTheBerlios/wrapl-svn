#include <Gtk/Gtk/Tree.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Std/Boolean.h>
#include <Gtk/Gtk/TreeModel.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TreePath.h>
#include <Gtk/Gtk/SelectionData.h>
/***********************************/
GLOBAL_FUNCTION(GetRowDragData, 3) {
	GtkSelectionData * selection_data= &((Gtk$Gtk$SelectionData_t *)Args[0].Val)->Value;
	GtkTreeModel** tree_model = 0;
	GtkTreePath** path = 0;
	int result = gtk_tree_get_row_drag_data(selection_data, tree_model, path);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(SetRowDragData, 3) {
	GtkSelectionData * selection_data= &((Gtk$Gtk$SelectionData_t *)Args[0].Val)->Value;
	GtkTreeModel * tree_model = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[2].Val)->Value;
	int result = gtk_tree_set_row_drag_data(selection_data, tree_model, path);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

