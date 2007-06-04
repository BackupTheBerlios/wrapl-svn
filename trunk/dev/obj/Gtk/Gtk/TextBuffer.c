#include <Gtk/Gtk/TextBuffer.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 16
#include <Gtk/Gtk/Clipboard.h>
#include <Gtk/Gtk/TextTag.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TextTagTable.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/TextMark.h>
#include <Gtk/Gtk/TextIter.h>
#include <Gtk/Gtk/TextBuffer.h>
#include <Gtk/Gtk/TextBufferDeserializeFunc.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Gtk/Gtk/TargetList.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/TextChildAnchor.h>
#include <Gtk/Gtk/TextBufferSerializeFunc.h>
#include <Gtk/Gdk/Atom.h>
#include <Gtk/Gtk/Clipboard.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	GtkTextTagTable * table = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextBuffer * result = gtk_text_buffer_new(table);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_text_buffer_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddSelectionClipboard", TYP, T, TYP, Gtk$Gtk$Clipboard$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkClipboard * clipboard = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_text_buffer_add_selection_clipboard(self, clipboard);
	return SUCCESS;
};

METHOD("ApplyTag", TYP, T, TYP, Gtk$Gtk$TextTag$T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextTag * tag = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTextIter * start= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[3].Val)->Value;
	gtk_text_buffer_apply_tag(self, tag, start, end);
	return SUCCESS;
};

METHOD("ApplyTagByName", TYP, T, TYP, Std$String$T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	GtkTextIter * start= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[3].Val)->Value;
	gtk_text_buffer_apply_tag_by_name(self, name, start, end);
	return SUCCESS;
};

METHOD("Backspace", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Symbol$T, TYP, Std$Symbol$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	int interactive = Args[2].Val == $true;
	int default_editable = Args[3].Val == $true;
	int result = gtk_text_buffer_backspace(self, iter, interactive, default_editable);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BeginUserAction", TYP, T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_text_buffer_begin_user_action(self);
	return SUCCESS;
};

METHOD("CopyClipboard", TYP, T, TYP, Gtk$Gtk$Clipboard$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkClipboard * clipboard = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_text_buffer_copy_clipboard(self, clipboard);
	return SUCCESS;
};

METHOD("CreateChildAnchor", TYP, T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GtkTextChildAnchor * result = gtk_text_buffer_create_child_anchor(self, iter);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("CreateMark", TYP, T, TYP, Std$String$T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Symbol$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *mark_name = Std$String$flatten(Args[1].Val);
	GtkTextIter * where= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	int left_gravity = Args[3].Val == $true;
	GtkTextMark * result = gtk_text_buffer_create_mark(self, mark_name, where, left_gravity);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("CreateTag", TYP, T, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *tag_name = Std$String$flatten(Args[1].Val);
	char *first_property_name = Std$String$flatten(Args[2].Val);
	char *___ = 0;
	GtkTextTag * result = gtk_text_buffer_create_tag(self, tag_name, first_property_name, ___);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("CutClipboard", TYP, T, TYP, Gtk$Gtk$Clipboard$T, TYP, Std$Symbol$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkClipboard * clipboard = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int default_editable = Args[2].Val == $true;
	gtk_text_buffer_cut_clipboard(self, clipboard, default_editable);
	return SUCCESS;
};

METHOD("Delete", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * start= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	gtk_text_buffer_delete(self, start, end);
	return SUCCESS;
};

METHOD("DeleteInteractive", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Symbol$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * start_iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GtkTextIter * end_iter= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	int default_editable = Args[3].Val == $true;
	int result = gtk_text_buffer_delete_interactive(self, start_iter, end_iter, default_editable);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("DeleteMark", TYP, T, TYP, Gtk$Gtk$TextMark$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextMark * mark = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_text_buffer_delete_mark(self, mark);
	return SUCCESS;
};

METHOD("DeleteMarkByName", TYP, T, TYP, Std$String$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	gtk_text_buffer_delete_mark_by_name(self, name);
	return SUCCESS;
};

METHOD("DeleteSelection", TYP, T, TYP, Std$Symbol$T, TYP, Std$Symbol$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int interactive = Args[1].Val == $true;
	int default_editable = Args[2].Val == $true;
	int result = gtk_text_buffer_delete_selection(self, interactive, default_editable);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Deserialize", TYP, T, TYP, Gtk$Gtk$TextBuffer$T, TYP, Std$Object$T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Object$T, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextBuffer * content_buffer = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkAtom format = 0;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[3].Val)->Value;
	const guint8* data = 0;
	int length = ((Std$Integer_smallt *)Args[5].Val)->Value;
	GError** error = 0;
	int result = gtk_text_buffer_deserialize(self, content_buffer, format, iter, data, length, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("DeserializeGetCanCreateTags", TYP, T, TYP, Std$Object$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom format = 0;
	int result = gtk_text_buffer_deserialize_get_can_create_tags(self, format);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("DeserializeSetCanCreateTags", TYP, T, TYP, Std$Object$T, TYP, Std$Symbol$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom format = 0;
	int can_create_tags = Args[2].Val == $true;
	gtk_text_buffer_deserialize_set_can_create_tags(self, format, can_create_tags);
	return SUCCESS;
};

METHOD("EndUserAction", TYP, T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_text_buffer_end_user_action(self);
	return SUCCESS;
};

METHOD("GetBounds", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * start= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	gtk_text_buffer_get_bounds(self, start, end);
	return SUCCESS;
};

METHOD("GetCharCount", TYP, T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_buffer_get_char_count(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetCopyTargetList", TYP, T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTargetList * result = gtk_text_buffer_get_copy_target_list(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetDeserializeFormats", TYP, T, TYP, Std$Object$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* n_formats = 0;
	GdkAtom * result = gtk_text_buffer_get_deserialize_formats(self, n_formats);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetEndIter", TYP, T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	gtk_text_buffer_get_end_iter(self, iter);
	return SUCCESS;
};

METHOD("GetHasSelection", TYP, T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_buffer_get_has_selection(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetInsert", TYP, T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextMark * result = gtk_text_buffer_get_insert(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetIterAtChildAnchor", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextChildAnchor$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GtkTextChildAnchor * anchor = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_text_buffer_get_iter_at_child_anchor(self, iter, anchor);
	return SUCCESS;
};

METHOD("GetIterAtLine", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Integer$SmallT) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	int line_number = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_text_buffer_get_iter_at_line(self, iter, line_number);
	return SUCCESS;
};

METHOD("GetIterAtLineIndex", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	int line_number = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int byte_index = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_text_buffer_get_iter_at_line_index(self, iter, line_number, byte_index);
	return SUCCESS;
};

METHOD("GetIterAtLineOffset", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	int line_number = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int char_offset = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_text_buffer_get_iter_at_line_offset(self, iter, line_number, char_offset);
	return SUCCESS;
};

METHOD("GetIterAtMark", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextMark$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GtkTextMark * mark = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_text_buffer_get_iter_at_mark(self, iter, mark);
	return SUCCESS;
};

METHOD("GetIterAtOffset", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Integer$SmallT) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	int char_offset = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_text_buffer_get_iter_at_offset(self, iter, char_offset);
	return SUCCESS;
};

METHOD("GetLineCount", TYP, T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_buffer_get_line_count(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetMark", TYP, T, TYP, Std$String$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	GtkTextMark * result = gtk_text_buffer_get_mark(self, name);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetModified", TYP, T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_buffer_get_modified(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetPasteTargetList", TYP, T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTargetList * result = gtk_text_buffer_get_paste_target_list(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetSelectionBound", TYP, T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextMark * result = gtk_text_buffer_get_selection_bound(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetSelectionBounds", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * start= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	int result = gtk_text_buffer_get_selection_bounds(self, start, end);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSerializeFormats", TYP, T, TYP, Std$Object$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* n_formats = 0;
	GdkAtom * result = gtk_text_buffer_get_serialize_formats(self, n_formats);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetSlice", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Symbol$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * start= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	int include_hidden_chars = Args[3].Val == $true;
	char * result = gtk_text_buffer_get_slice(self, start, end, include_hidden_chars);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetStartIter", TYP, T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	gtk_text_buffer_get_start_iter(self, iter);
	return SUCCESS;
};

METHOD("GetTagTable", TYP, T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextTagTable * result = gtk_text_buffer_get_tag_table(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetText", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Symbol$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * start= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	int include_hidden_chars = Args[3].Val == $true;
	char * result = gtk_text_buffer_get_text(self, start, end, include_hidden_chars);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("Insert", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	char *text = Std$String$flatten(Args[2].Val);
	int len = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_text_buffer_insert(self, iter, text, len);
	return SUCCESS;
};

METHOD("InsertAtCursor", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	int len = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_text_buffer_insert_at_cursor(self, text, len);
	return SUCCESS;
};

METHOD("InsertChildAnchor", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextChildAnchor$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GtkTextChildAnchor * anchor = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_text_buffer_insert_child_anchor(self, iter, anchor);
	return SUCCESS;
};

METHOD("InsertInteractive", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$Symbol$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	char *text = Std$String$flatten(Args[2].Val);
	int len = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int default_editable = Args[4].Val == $true;
	int result = gtk_text_buffer_insert_interactive(self, iter, text, len, default_editable);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("InsertInteractiveAtCursor", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$Symbol$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	int len = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int default_editable = Args[3].Val == $true;
	int result = gtk_text_buffer_insert_interactive_at_cursor(self, text, len, default_editable);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("InsertPixbuf", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gdk$Pixbuf$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_text_buffer_insert_pixbuf(self, iter, pixbuf);
	return SUCCESS;
};

METHOD("InsertRange", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GtkTextIter * start= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[3].Val)->Value;
	gtk_text_buffer_insert_range(self, iter, start, end);
	return SUCCESS;
};

METHOD("InsertRangeInteractive", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Symbol$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GtkTextIter * start= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[3].Val)->Value;
	int default_editable = Args[4].Val == $true;
	int result = gtk_text_buffer_insert_range_interactive(self, iter, start, end, default_editable);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("InsertWithTags", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$TextTag$T, TYP, Std$Object$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	char *text = Std$String$flatten(Args[2].Val);
	int len = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GtkTextTag * first_tag = ((Gtk$GObject$Object_t *)Args[4].Val)->Handle;
	char *___ = 0;
	gtk_text_buffer_insert_with_tags(self, iter, text, len, first_tag, ___);
	return SUCCESS;
};

METHOD("InsertWithTagsByName", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	char *text = Std$String$flatten(Args[2].Val);
	int len = ((Std$Integer_smallt *)Args[3].Val)->Value;
	char *first_tag_name = Std$String$flatten(Args[4].Val);
	char *___ = 0;
	gtk_text_buffer_insert_with_tags_by_name(self, iter, text, len, first_tag_name, ___);
	return SUCCESS;
};

METHOD("MoveMark", TYP, T, TYP, Gtk$Gtk$TextMark$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextMark * mark = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTextIter * where= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	gtk_text_buffer_move_mark(self, mark, where);
	return SUCCESS;
};

METHOD("MoveMarkByName", TYP, T, TYP, Std$String$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	GtkTextIter * where= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	gtk_text_buffer_move_mark_by_name(self, name, where);
	return SUCCESS;
};

METHOD("PasteClipboard", TYP, T, TYP, Gtk$Gtk$Clipboard$T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Symbol$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkClipboard * clipboard = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTextIter * override_location= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	int default_editable = Args[3].Val == $true;
	gtk_text_buffer_paste_clipboard(self, clipboard, override_location, default_editable);
	return SUCCESS;
};

METHOD("PlaceCursor", TYP, T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * where= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	gtk_text_buffer_place_cursor(self, where);
	return SUCCESS;
};

METHOD("RegisterDeserializeFormat", TYP, T, TYP, Std$String$T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Object$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *mime_type = Std$String$flatten(Args[1].Val);
	GtkTextBufferDeserializeFunc function = Gtk$Gtk$TextBufferDeserializeFunc$new(Args[2].Val);
	void *user_data = ((Std$Address_t *)Args[3].Val)->Value;
	GDestroyNotify user_data_destroy = 0;
	GdkAtom result = gtk_text_buffer_register_deserialize_format(self, mime_type, function, user_data, user_data_destroy);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("RegisterDeserializeTagset", TYP, T, TYP, Std$String$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *tagset_name = Std$String$flatten(Args[1].Val);
	GdkAtom result = gtk_text_buffer_register_deserialize_tagset(self, tagset_name);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("RegisterSerializeFormat", TYP, T, TYP, Std$String$T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Object$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *mime_type = Std$String$flatten(Args[1].Val);
	GtkTextBufferSerializeFunc function = Gtk$Gtk$TextBufferSerializeFunc$new(Args[2].Val);
	void *user_data = ((Std$Address_t *)Args[3].Val)->Value;
	GDestroyNotify user_data_destroy = 0;
	GdkAtom result = gtk_text_buffer_register_serialize_format(self, mime_type, function, user_data, user_data_destroy);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("RegisterSerializeTagset", TYP, T, TYP, Std$String$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *tagset_name = Std$String$flatten(Args[1].Val);
	GdkAtom result = gtk_text_buffer_register_serialize_tagset(self, tagset_name);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("RemoveAllTags", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * start= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	gtk_text_buffer_remove_all_tags(self, start, end);
	return SUCCESS;
};

METHOD("RemoveSelectionClipboard", TYP, T, TYP, Gtk$Gtk$Clipboard$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkClipboard * clipboard = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_text_buffer_remove_selection_clipboard(self, clipboard);
	return SUCCESS;
};

METHOD("RemoveTag", TYP, T, TYP, Gtk$Gtk$TextTag$T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextTag * tag = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTextIter * start= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[3].Val)->Value;
	gtk_text_buffer_remove_tag(self, tag, start, end);
	return SUCCESS;
};

METHOD("RemoveTagByName", TYP, T, TYP, Std$String$T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	GtkTextIter * start= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[3].Val)->Value;
	gtk_text_buffer_remove_tag_by_name(self, name, start, end);
	return SUCCESS;
};

METHOD("SelectRange", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * ins= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GtkTextIter * bound= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	gtk_text_buffer_select_range(self, ins, bound);
	return SUCCESS;
};

METHOD("Serialize", TYP, T, TYP, Gtk$Gtk$TextBuffer$T, TYP, Std$Object$T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Object$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextBuffer * content_buffer = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkAtom format = 0;
	GtkTextIter * start= &((Gtk$Gtk$TextIter_t *)Args[3].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[4].Val)->Value;
	gsize* length = 0;
	guint8* result = gtk_text_buffer_serialize(self, content_buffer, format, start, end, length);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("SetModified", TYP, T, TYP, Std$Symbol$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_text_buffer_set_modified(self, setting);
	return SUCCESS;
};

METHOD("SetText", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	int len = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_text_buffer_set_text(self, text, len);
	return SUCCESS;
};

METHOD("UnregisterDeserializeFormat", TYP, T, TYP, Std$Object$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom format = 0;
	gtk_text_buffer_unregister_deserialize_format(self, format);
	return SUCCESS;
};

METHOD("UnregisterSerializeFormat", TYP, T, TYP, Std$Object$T) {
	GtkTextBuffer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom format = 0;
	gtk_text_buffer_unregister_serialize_format(self, format);
	return SUCCESS;
};

