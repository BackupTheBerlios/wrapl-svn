#include <Gtk/Gtk/TreeDragSource.h>
#include <Riva/Memory.h>
#include <Gtk/Gtk/TreePath.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/SelectionData.h>
#include <Gtk/Gtk/TreeDragSource.h>
#include <Std/Boolean.h>
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tree_drag_source_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("DragDataDelete", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeDragSource * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[2].Val)->Value;
	int result = gtk_tree_drag_source_drag_data_delete(self, path);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("DragDataGet", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$SelectionData$T) {
	GtkTreeDragSource * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[2].Val)->Value;
	GtkSelectionData * selection_data= &((Gtk$Gtk$SelectionData_t *)Args[3].Val)->Value;
	int result = gtk_tree_drag_source_drag_data_get(self, path, selection_data);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("RowDraggable", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkTreeDragSource * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[2].Val)->Value;
	int result = gtk_tree_drag_source_row_draggable(self, path);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

