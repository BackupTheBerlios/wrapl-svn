#include <Gtk/Gtk/CellView.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 9
#include <Gtk/Gtk/Requisition.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TreePath.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/Gtk/CellView.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/TreeModel.h>
/***********************************/
TYPE(T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkCellView * result = gtk_cell_view_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithMarkup, 1) {
	char *markup = Std$String$flatten(Args[0].Val);
	GtkCellView * result = gtk_cell_view_new_with_markup(markup);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithPixbuf, 1) {
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCellView * result = gtk_cell_view_new_with_pixbuf(pixbuf);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithText, 1) {
	char *text = Std$String$flatten(Args[0].Val);
	GtkCellView * result = gtk_cell_view_new_with_text(text);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_cell_view_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetCellRenderers", TYP, T) {
	GtkCellView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList * result = gtk_cell_view_get_cell_renderers(self);
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

METHOD("GetDisplayedRow", TYP, T) {
	GtkCellView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * result = gtk_cell_view_get_displayed_row(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetSizeOfRow", TYP, T, TYP, Gtk$Gtk$TreePath$T, TYP, Gtk$Gtk$Requisition$T) {
	GtkCellView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	GtkRequisition * requisition= &((Gtk$Gtk$Requisition_t *)Args[2].Val)->Value;
	int result = gtk_cell_view_get_size_of_row(self, path, requisition);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetBackgroundColor", TYP, T, TYP, Gtk$Gdk$Color$T) {
	GtkCellView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	gtk_cell_view_set_background_color(self, color);
	return SUCCESS;
};

METHOD("SetDisplayedRow", TYP, T, TYP, Gtk$Gtk$TreePath$T) {
	GtkCellView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreePath * path= ((Gtk$Gtk$TreePath_t *)Args[1].Val)->Value;
	gtk_cell_view_set_displayed_row(self, path);
	return SUCCESS;
};

METHOD("SetModel", TYP, T, TYP, Gtk$Gtk$TreeModel$T) {
	GtkCellView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModel * model = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_cell_view_set_model(self, model);
	return SUCCESS;
};

