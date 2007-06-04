#include <Gtk/Gtk/CList.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 17
#include <Gtk/Gtk/SortType.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/Gtk/CListCompareFunc.h>
#include <Gtk/Gtk/Justification.h>
#include <Gtk/Gtk/Style.h>
#include <Gtk/Gtk/CList.h>
#include <Gtk/Gtk/CellType.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/DestroyNotify.h>
#include <Gtk/Gtk/ShadowType.h>
#include <Gtk/Gtk/SelectionMode.h>
#include <Gtk/Gtk/Adjustment.h>
#include <Gtk/Gdk/Bitmap.h>
#include <Gtk/Gdk/Pixmap.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	int columns = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GtkCList * result = gtk_clist_new(columns);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithTitles, 2) {
	int columns = ((Std$Integer_smallt *)Args[0].Val)->Value;
	const char * const * titles;
	GtkCList * result = gtk_clist_new_with_titles(columns, titles);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_clist_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Append", TYP, T, TYP, Std$List$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * text;
	int result = gtk_clist_append(self, text);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Clear", TYP, T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_clist_clear(self);
	return SUCCESS;
};

METHOD("ColumnsAutosize", TYP, T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_clist_columns_autosize(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("FindRowFromData", TYP, T, TYP, Std$Address$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	void *data = ((Std$Address_t *)Args[1].Val)->Value;
	int result = gtk_clist_find_row_from_data(self, data);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Freeze", TYP, T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_clist_freeze(self);
	return SUCCESS;
};

METHOD("GetCellStyle", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkStyle * result = gtk_clist_get_cell_style(self, row, column);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetCellType", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkCellType result = gtk_clist_get_cell_type(self, row, column);
	Gtk$Gtk$CellType_t *_result = new(Gtk$Gtk$CellType_t);
	_result->Type = Gtk$Gtk$CellType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetColumnTitle", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char * result = gtk_clist_get_column_title(self, column);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetColumnWidget", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkWidget * result = gtk_clist_get_column_widget(self, column);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetHadjustment", TYP, T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * result = gtk_clist_get_hadjustment(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPixmap", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkPixmap** pixmap = 0;
	GdkBitmap** mask = 0;
	int result = gtk_clist_get_pixmap(self, row, column, pixmap, mask);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetPixtext", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$List$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	const char * const * text;
	guint8* spacing = 0;
	GdkPixmap** pixmap = 0;
	GdkBitmap** mask = 0;
	int result = gtk_clist_get_pixtext(self, row, column, text, spacing, pixmap, mask);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetRowData", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	void * result = gtk_clist_get_row_data(self, row);
	Result->Val = Std$Address$new(result);
	return SUCCESS;
};

METHOD("GetRowStyle", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkStyle * result = gtk_clist_get_row_style(self, row);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetSelectable", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_clist_get_selectable(self, row);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSelectionInfo", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gint* row = 0;
	gint* column = 0;
	int result = gtk_clist_get_selection_info(self, x, y, row, column);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetText", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$List$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	const char * const * text;
	int result = gtk_clist_get_text(self, row, column, text);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetVadjustment", TYP, T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * result = gtk_clist_get_vadjustment(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Insert", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$List$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	const char * const * text;
	int result = gtk_clist_insert(self, row, text);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Moveto", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	double row_align = ((Std$Real_t *)Args[3].Val)->Value;
	double col_align = ((Std$Real_t *)Args[4].Val)->Value;
	gtk_clist_moveto(self, row, column, row_align, col_align);
	return SUCCESS;
};

METHOD("OptimalColumnWidth", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_clist_optimal_column_width(self, column);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Prepend", TYP, T, TYP, Std$List$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * text;
	int result = gtk_clist_prepend(self, text);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Remove", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_clist_remove(self, row);
	return SUCCESS;
};

METHOD("SelectAll", TYP, T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_clist_select_all(self);
	return SUCCESS;
};

METHOD("SelectRow", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_clist_select_row(self, row, column);
	return SUCCESS;
};

METHOD("SetAutoSort", TYP, T, TYP, Std$Symbol$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int auto_sort = Args[1].Val == $true;
	gtk_clist_set_auto_sort(self, auto_sort);
	return SUCCESS;
};

METHOD("SetBackground", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$Color$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[2].Val)->Value;
	gtk_clist_set_background(self, row, color);
	return SUCCESS;
};

METHOD("SetButtonActions", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int button = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int button_actions = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_clist_set_button_actions(self, button, button_actions);
	return SUCCESS;
};

METHOD("SetCellStyle", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$Style$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	gtk_clist_set_cell_style(self, row, column, style);
	return SUCCESS;
};

METHOD("SetColumnAutoResize", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Symbol$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int auto_resize = Args[2].Val == $true;
	gtk_clist_set_column_auto_resize(self, column, auto_resize);
	return SUCCESS;
};

METHOD("SetColumnJustification", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$Justification$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkJustification justification = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_clist_set_column_justification(self, column, justification);
	return SUCCESS;
};

METHOD("SetColumnMaxWidth", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int max_width = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_clist_set_column_max_width(self, column, max_width);
	return SUCCESS;
};

METHOD("SetColumnMinWidth", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int min_width = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_clist_set_column_min_width(self, column, min_width);
	return SUCCESS;
};

METHOD("SetColumnResizeable", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Symbol$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int resizeable = Args[2].Val == $true;
	gtk_clist_set_column_resizeable(self, column, resizeable);
	return SUCCESS;
};

METHOD("SetColumnTitle", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$String$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *title = Std$String$flatten(Args[2].Val);
	gtk_clist_set_column_title(self, column, title);
	return SUCCESS;
};

METHOD("SetColumnVisibility", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Symbol$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int visible = Args[2].Val == $true;
	gtk_clist_set_column_visibility(self, column, visible);
	return SUCCESS;
};

METHOD("SetColumnWidget", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$Widget$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_clist_set_column_widget(self, column, widget);
	return SUCCESS;
};

METHOD("SetColumnWidth", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_clist_set_column_width(self, column, width);
	return SUCCESS;
};

METHOD("SetCompareFunc", TYP, T, TYP, Std$Function$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCListCompareFunc cmp_func = Gtk$Gtk$CListCompareFunc$new(Args[1].Val);
	gtk_clist_set_compare_func(self, cmp_func);
	return SUCCESS;
};

METHOD("SetForeground", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$Color$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[2].Val)->Value;
	gtk_clist_set_foreground(self, row, color);
	return SUCCESS;
};

METHOD("SetHadjustment", TYP, T, TYP, Gtk$Gtk$Adjustment$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_clist_set_hadjustment(self, adjustment);
	return SUCCESS;
};

METHOD("SetPixmap", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$Pixmap$T, TYP, Gtk$Gdk$Bitmap$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkPixmap * pixmap = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[4].Val)->Handle;
	gtk_clist_set_pixmap(self, row, column, pixmap, mask);
	return SUCCESS;
};

METHOD("SetPixtext", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$Pixmap$T, TYP, Gtk$Gdk$Bitmap$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char *text = Std$String$flatten(Args[3].Val);
	int spacing = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GdkPixmap * pixmap = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[6].Val)->Handle;
	gtk_clist_set_pixtext(self, row, column, text, spacing, pixmap, mask);
	return SUCCESS;
};

METHOD("SetReorderable", TYP, T, TYP, Std$Symbol$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int reorderable = Args[1].Val == $true;
	gtk_clist_set_reorderable(self, reorderable);
	return SUCCESS;
};

METHOD("SetRowData", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Address$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	gtk_clist_set_row_data(self, row, data);
	return SUCCESS;
};

METHOD("SetRowDataFull", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[3].Val);
	gtk_clist_set_row_data_full(self, row, data, destroy);
	return SUCCESS;
};

METHOD("SetRowHeight", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int height = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_clist_set_row_height(self, height);
	return SUCCESS;
};

METHOD("SetRowStyle", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$Style$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_clist_set_row_style(self, row, style);
	return SUCCESS;
};

METHOD("SetSelectable", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Symbol$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int selectable = Args[2].Val == $true;
	gtk_clist_set_selectable(self, row, selectable);
	return SUCCESS;
};

METHOD("SetSelectionMode", TYP, T, TYP, Gtk$Gtk$SelectionMode$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSelectionMode mode = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_clist_set_selection_mode(self, mode);
	return SUCCESS;
};

METHOD("SetShadowType", TYP, T, TYP, Gtk$Gtk$ShadowType$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkShadowType type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_clist_set_shadow_type(self, type);
	return SUCCESS;
};

METHOD("SetShift", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int vertical = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int horizontal = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_clist_set_shift(self, row, column, vertical, horizontal);
	return SUCCESS;
};

METHOD("SetSortColumn", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_clist_set_sort_column(self, column);
	return SUCCESS;
};

METHOD("SetSortType", TYP, T, TYP, Gtk$Gtk$SortType$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSortType sort_type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_clist_set_sort_type(self, sort_type);
	return SUCCESS;
};

METHOD("SetText", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$String$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char *text = Std$String$flatten(Args[3].Val);
	gtk_clist_set_text(self, row, column, text);
	return SUCCESS;
};

METHOD("SetUseDragIcons", TYP, T, TYP, Std$Symbol$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int use_icons = Args[1].Val == $true;
	gtk_clist_set_use_drag_icons(self, use_icons);
	return SUCCESS;
};

METHOD("SetVadjustment", TYP, T, TYP, Gtk$Gtk$Adjustment$T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_clist_set_vadjustment(self, adjustment);
	return SUCCESS;
};

METHOD("Sort", TYP, T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_clist_sort(self);
	return SUCCESS;
};

METHOD("SwapRows", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row1 = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int row2 = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_clist_swap_rows(self, row1, row2);
	return SUCCESS;
};

METHOD("Thaw", TYP, T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_clist_thaw(self);
	return SUCCESS;
};

METHOD("UndoSelection", TYP, T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_clist_undo_selection(self);
	return SUCCESS;
};

METHOD("UnselectAll", TYP, T) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_clist_unselect_all(self);
	return SUCCESS;
};

METHOD("UnselectRow", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkCList * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int column = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_clist_unselect_row(self, row, column);
	return SUCCESS;
};

