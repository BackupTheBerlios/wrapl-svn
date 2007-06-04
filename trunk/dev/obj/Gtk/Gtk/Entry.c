#include <Gtk/Gtk/Entry.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Layout.h>
#include <Gtk/Gtk/Entry.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/EntryCompletion.h>
#include <Gtk/Gtk/Border.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkEntry * result = gtk_entry_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithMaxLength, 1) {
	int max = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GtkEntry * result = gtk_entry_new_with_max_length(max);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_entry_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AppendText", TYP, T, TYP, Std$String$T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	gtk_entry_append_text(self, text);
	return SUCCESS;
};

METHOD("GetActivatesDefault", TYP, T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_entry_get_activates_default(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetAlignment", TYP, T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = gtk_entry_get_alignment(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetCompletion", TYP, T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkEntryCompletion * result = gtk_entry_get_completion(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetHasFrame", TYP, T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_entry_get_has_frame(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetInnerBorder", TYP, T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkBorder * result = gtk_entry_get_inner_border(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetInvisibleChar", TYP, T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gunichar result = gtk_entry_get_invisible_char(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetLayout", TYP, T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoLayout * result = gtk_entry_get_layout(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetLayoutOffsets", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* x = 0;
	gint* y = 0;
	gtk_entry_get_layout_offsets(self, x, y);
	return SUCCESS;
};

METHOD("GetMaxLength", TYP, T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_entry_get_max_length(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetText", TYP, T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_entry_get_text(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetVisibility", TYP, T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_entry_get_visibility(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetWidthChars", TYP, T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_entry_get_width_chars(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("LayoutIndexToTextIndex", TYP, T, TYP, Std$Integer$SmallT) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int layout_index = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_entry_layout_index_to_text_index(self, layout_index);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("PrependText", TYP, T, TYP, Std$String$T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	gtk_entry_prepend_text(self, text);
	return SUCCESS;
};

METHOD("SelectRegion", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int start = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int end = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_entry_select_region(self, start, end);
	return SUCCESS;
};

METHOD("SetActivatesDefault", TYP, T, TYP, Std$Symbol$T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_entry_set_activates_default(self, setting);
	return SUCCESS;
};

METHOD("SetAlignment", TYP, T, TYP, Std$Real$T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double xalign = ((Std$Real_t *)Args[1].Val)->Value;
	gtk_entry_set_alignment(self, xalign);
	return SUCCESS;
};

METHOD("SetCompletion", TYP, T, TYP, Gtk$Gtk$EntryCompletion$T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkEntryCompletion * completion = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_entry_set_completion(self, completion);
	return SUCCESS;
};

METHOD("SetEditable", TYP, T, TYP, Std$Symbol$T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int editable = Args[1].Val == $true;
	gtk_entry_set_editable(self, editable);
	return SUCCESS;
};

METHOD("SetHasFrame", TYP, T, TYP, Std$Symbol$T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_entry_set_has_frame(self, setting);
	return SUCCESS;
};

METHOD("SetInnerBorder", TYP, T, TYP, Gtk$Gtk$Border$T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkBorder * border= &((Gtk$Gtk$Border_t *)Args[1].Val)->Value;
	gtk_entry_set_inner_border(self, border);
	return SUCCESS;
};

METHOD("SetInvisibleChar", TYP, T, TYP, Std$Object$T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gunichar ch = 0;
	gtk_entry_set_invisible_char(self, ch);
	return SUCCESS;
};

METHOD("SetMaxLength", TYP, T, TYP, Std$Integer$SmallT) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int max = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_entry_set_max_length(self, max);
	return SUCCESS;
};

METHOD("SetPosition", TYP, T, TYP, Std$Integer$SmallT) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_entry_set_position(self, position);
	return SUCCESS;
};

METHOD("SetText", TYP, T, TYP, Std$String$T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	gtk_entry_set_text(self, text);
	return SUCCESS;
};

METHOD("SetVisibility", TYP, T, TYP, Std$Symbol$T) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int visible = Args[1].Val == $true;
	gtk_entry_set_visibility(self, visible);
	return SUCCESS;
};

METHOD("SetWidthChars", TYP, T, TYP, Std$Integer$SmallT) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int n_chars = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_entry_set_width_chars(self, n_chars);
	return SUCCESS;
};

METHOD("TextIndexToLayoutIndex", TYP, T, TYP, Std$Integer$SmallT) {
	GtkEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int text_index = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_entry_text_index_to_layout_index(self, text_index);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

