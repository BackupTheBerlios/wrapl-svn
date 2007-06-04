#include <Gtk/Gtk/ComboBox.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 9
#include <Std/Boolean.h>
#include <Gtk/Gtk/TreeModel.h>
#include <Gtk/Gtk/ComboBox.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TreeViewRowSeparatorFunc.h>
#include <Gtk/Gtk/TreeIter.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/DestroyNotify.h>
#include <Gtk/Atk/Object.h>
/***********************************/
TYPE(T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkComboBox * result = gtk_combo_box_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewText, 0) {
	GtkComboBox * result = gtk_combo_box_new_text();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithModel, 1) {
	GtkTreeModel * model = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkComboBox * result = gtk_combo_box_new_with_model(model);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_combo_box_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AppendText", TYP, T, TYP, Std$String$T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	gtk_combo_box_append_text(self, text);
	return SUCCESS;
};

METHOD("GetActive", TYP, T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_combo_box_get_active(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetActiveIter", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	int result = gtk_combo_box_get_active_iter(self, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetActiveText", TYP, T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char * result = gtk_combo_box_get_active_text(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetAddTearoffs", TYP, T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_combo_box_get_add_tearoffs(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetColumnSpanColumn", TYP, T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_combo_box_get_column_span_column(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetFocusOnClick", TYP, T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_combo_box_get_focus_on_click(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetModel", TYP, T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModel * result = gtk_combo_box_get_model(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPopupAccessible", TYP, T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	AtkObject * result = gtk_combo_box_get_popup_accessible(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetRowSeparatorFunc", TYP, T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewRowSeparatorFunc result = gtk_combo_box_get_row_separator_func(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetRowSpanColumn", TYP, T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_combo_box_get_row_span_column(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetTitle", TYP, T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_combo_box_get_title(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetWrapWidth", TYP, T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_combo_box_get_wrap_width(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("InsertText", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$String$T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *text = Std$String$flatten(Args[2].Val);
	gtk_combo_box_insert_text(self, position, text);
	return SUCCESS;
};

METHOD("Popdown", TYP, T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_combo_box_popdown(self);
	return SUCCESS;
};

METHOD("Popup", TYP, T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_combo_box_popup(self);
	return SUCCESS;
};

METHOD("PrependText", TYP, T, TYP, Std$String$T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	gtk_combo_box_prepend_text(self, text);
	return SUCCESS;
};

METHOD("RemoveText", TYP, T, TYP, Std$Integer$SmallT) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_combo_box_remove_text(self, position);
	return SUCCESS;
};

METHOD("SetActive", TYP, T, TYP, Std$Integer$SmallT) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int index_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_combo_box_set_active(self, index_);
	return SUCCESS;
};

METHOD("SetActiveIter", TYP, T, TYP, Gtk$Gtk$TreeIter$T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeIter * iter= &((Gtk$Gtk$TreeIter_t *)Args[1].Val)->Value;
	gtk_combo_box_set_active_iter(self, iter);
	return SUCCESS;
};

METHOD("SetAddTearoffs", TYP, T, TYP, Std$Symbol$T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int add_tearoffs = Args[1].Val == $true;
	gtk_combo_box_set_add_tearoffs(self, add_tearoffs);
	return SUCCESS;
};

METHOD("SetColumnSpanColumn", TYP, T, TYP, Std$Integer$SmallT) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column_span = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_combo_box_set_column_span_column(self, column_span);
	return SUCCESS;
};

METHOD("SetFocusOnClick", TYP, T, TYP, Std$Symbol$T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int focus_on_click = Args[1].Val == $true;
	gtk_combo_box_set_focus_on_click(self, focus_on_click);
	return SUCCESS;
};

METHOD("SetModel", TYP, T, TYP, Gtk$Gtk$TreeModel$T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModel * model = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_combo_box_set_model(self, model);
	return SUCCESS;
};

METHOD("SetRowSeparatorFunc", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeViewRowSeparatorFunc func = Gtk$Gtk$TreeViewRowSeparatorFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[3].Val);
	gtk_combo_box_set_row_separator_func(self, func, data, destroy);
	return SUCCESS;
};

METHOD("SetRowSpanColumn", TYP, T, TYP, Std$Integer$SmallT) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row_span = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_combo_box_set_row_span_column(self, row_span);
	return SUCCESS;
};

METHOD("SetTitle", TYP, T, TYP, Std$String$T) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *title = Std$String$flatten(Args[1].Val);
	gtk_combo_box_set_title(self, title);
	return SUCCESS;
};

METHOD("SetWrapWidth", TYP, T, TYP, Std$Integer$SmallT) {
	GtkComboBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_combo_box_set_wrap_width(self, width);
	return SUCCESS;
};

