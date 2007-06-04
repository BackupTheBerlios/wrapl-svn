#include <Gtk/Gtk/EntryCompletion.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/EntryCompletion.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/TreeModel.h>
#include <Gtk/Gtk/EntryCompletionMatchFunc.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkEntryCompletion * result = gtk_entry_completion_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_entry_completion_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Complete", TYP, T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_entry_completion_complete(self);
	return SUCCESS;
};

METHOD("DeleteAction", TYP, T, TYP, Std$Integer$SmallT) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int index_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_entry_completion_delete_action(self, index_);
	return SUCCESS;
};

METHOD("GetEntry", TYP, T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_entry_completion_get_entry(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetInlineCompletion", TYP, T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_entry_completion_get_inline_completion(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetMinimumKeyLength", TYP, T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_entry_completion_get_minimum_key_length(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetModel", TYP, T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModel * result = gtk_entry_completion_get_model(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPopupCompletion", TYP, T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_entry_completion_get_popup_completion(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetPopupSetWidth", TYP, T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_entry_completion_get_popup_set_width(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetPopupSingleMatch", TYP, T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_entry_completion_get_popup_single_match(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetTextColumn", TYP, T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_entry_completion_get_text_column(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("InsertActionMarkup", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$String$T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int index_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *markup = Std$String$flatten(Args[2].Val);
	gtk_entry_completion_insert_action_markup(self, index_, markup);
	return SUCCESS;
};

METHOD("InsertActionText", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$String$T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int index_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *text = Std$String$flatten(Args[2].Val);
	gtk_entry_completion_insert_action_text(self, index_, text);
	return SUCCESS;
};

METHOD("InsertPrefix", TYP, T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_entry_completion_insert_prefix(self);
	return SUCCESS;
};

METHOD("SetInlineCompletion", TYP, T, TYP, Std$Symbol$T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int inline_completion = Args[1].Val == $true;
	gtk_entry_completion_set_inline_completion(self, inline_completion);
	return SUCCESS;
};

METHOD("SetMatchFunc", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Object$T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkEntryCompletionMatchFunc func = Gtk$Gtk$EntryCompletionMatchFunc$new(Args[1].Val);
	void *func_data = ((Std$Address_t *)Args[2].Val)->Value;
	GDestroyNotify func_notify = 0;
	gtk_entry_completion_set_match_func(self, func, func_data, func_notify);
	return SUCCESS;
};

METHOD("SetMinimumKeyLength", TYP, T, TYP, Std$Integer$SmallT) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int length = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_entry_completion_set_minimum_key_length(self, length);
	return SUCCESS;
};

METHOD("SetModel", TYP, T, TYP, Gtk$Gtk$TreeModel$T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTreeModel * model = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_entry_completion_set_model(self, model);
	return SUCCESS;
};

METHOD("SetPopupCompletion", TYP, T, TYP, Std$Symbol$T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int popup_completion = Args[1].Val == $true;
	gtk_entry_completion_set_popup_completion(self, popup_completion);
	return SUCCESS;
};

METHOD("SetPopupSetWidth", TYP, T, TYP, Std$Symbol$T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int popup_set_width = Args[1].Val == $true;
	gtk_entry_completion_set_popup_set_width(self, popup_set_width);
	return SUCCESS;
};

METHOD("SetPopupSingleMatch", TYP, T, TYP, Std$Symbol$T) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int popup_single_match = Args[1].Val == $true;
	gtk_entry_completion_set_popup_single_match(self, popup_single_match);
	return SUCCESS;
};

METHOD("SetTextColumn", TYP, T, TYP, Std$Integer$SmallT) {
	GtkEntryCompletion * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_entry_completion_set_text_column(self, column);
	return SUCCESS;
};

