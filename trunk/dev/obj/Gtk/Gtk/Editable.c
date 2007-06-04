#include <Gtk/Gtk/Editable.h>
#include <Riva/Memory.h>
#include <Gtk/Gtk/Editable.h>
#include <Gtk/GObject/Type.h>
#include <Std/Boolean.h>
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_editable_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("CopyClipboard", TYP, T) {
	GtkEditable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_editable_copy_clipboard(self);
	return SUCCESS;
};

METHOD("CutClipboard", TYP, T) {
	GtkEditable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_editable_cut_clipboard(self);
	return SUCCESS;
};

METHOD("DeleteSelection", TYP, T) {
	GtkEditable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_editable_delete_selection(self);
	return SUCCESS;
};

METHOD("DeleteText", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkEditable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int start_pos = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int end_pos = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_editable_delete_text(self, start_pos, end_pos);
	return SUCCESS;
};

METHOD("GetChars", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkEditable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int start_pos = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int end_pos = ((Std$Integer_smallt *)Args[3].Val)->Value;
	char * result = gtk_editable_get_chars(self, start_pos, end_pos);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetEditable", TYP, T) {
	GtkEditable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_editable_get_editable(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetPosition", TYP, T) {
	GtkEditable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_editable_get_position(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetSelectionBounds", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkEditable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gint* start = 0;
	gint* end = 0;
	int result = gtk_editable_get_selection_bounds(self, start, end);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("InsertText", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkEditable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *new_text = Std$String$flatten(Args[2].Val);
	int new_text_length = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gint* position = 0;
	gtk_editable_insert_text(self, new_text, new_text_length, position);
	return SUCCESS;
};

METHOD("PasteClipboard", TYP, T) {
	GtkEditable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_editable_paste_clipboard(self);
	return SUCCESS;
};

METHOD("SelectRegion", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkEditable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int start = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int end = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_editable_select_region(self, start, end);
	return SUCCESS;
};

METHOD("SetEditable", TYP, T, TYP, Std$Symbol$T) {
	GtkEditable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int is_editable = Args[2].Val == $true;
	gtk_editable_set_editable(self, is_editable);
	return SUCCESS;
};

METHOD("SetPosition", TYP, T, TYP, Std$Integer$SmallT) {
	GtkEditable * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_editable_set_position(self, position);
	return SUCCESS;
};

