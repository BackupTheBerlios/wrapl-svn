#include <Gtk/Gtk/TreeDragDest.h>
#include <Riva/Memory.h>
#include <Gtk/Gtk/TreePath.h>
#include <Gtk/Gtk/TreeDragDest.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/SelectionData.h>
#include <Std/Boolean.h>
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tree_drag_dest_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("DragDataReceived", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$SelectionData$T) {
	GtkTreeDragDest * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreePath * dest= ((Gtk$Gtk$TreePath_t *)Args[2].Val)->Value;
	GtkSelectionData * selection_data= &((Gtk$Gtk$SelectionData_t *)Args[3].Val)->Value;
	int result = gtk_tree_drag_dest_drag_data_received(self, dest, selection_data);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("RowDropPossible", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$SelectionData$T) {
	GtkTreeDragDest * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTreePath * dest_path= ((Gtk$Gtk$TreePath_t *)Args[2].Val)->Value;
	GtkSelectionData * selection_data= &((Gtk$Gtk$SelectionData_t *)Args[3].Val)->Value;
	int result = gtk_tree_drag_dest_row_drop_possible(self, dest_path, selection_data);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

