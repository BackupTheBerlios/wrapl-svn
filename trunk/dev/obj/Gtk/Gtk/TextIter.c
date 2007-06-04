#include <Gtk/Gtk/TextIter.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 11
#include <Gtk/Gtk/TextTag.h>
#include <Gtk/Pango/Language.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TextAttributes.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/TextIter.h>
#include <Gtk/Gtk/TextBuffer.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Gtk/Gtk/TextCharPredicate.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/TextChildAnchor.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_text_iter_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("BackwardChar", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_backward_char(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardChars", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_iter_backward_chars(self, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardCursorPosition", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_backward_cursor_position(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardCursorPositions", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_iter_backward_cursor_positions(self, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardFindChar", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextCharPredicate pred = Gtk$Gtk$TextCharPredicate$new(Args[1].Val);
	void *user_data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkTextIter * limit= &((Gtk$Gtk$TextIter_t *)Args[3].Val)->Value;
	int result = gtk_text_iter_backward_find_char(self, pred, user_data, limit);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardLine", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_backward_line(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardLines", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_iter_backward_lines(self, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardSearch", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	char *str = Std$String$flatten(Args[1].Val);
	int flags = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkTextIter * match_start= &((Gtk$Gtk$TextIter_t *)Args[3].Val)->Value;
	GtkTextIter * match_end= &((Gtk$Gtk$TextIter_t *)Args[4].Val)->Value;
	GtkTextIter * limit= &((Gtk$Gtk$TextIter_t *)Args[5].Val)->Value;
	int result = gtk_text_iter_backward_search(self, str, flags, match_start, match_end, limit);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardSentenceStart", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_backward_sentence_start(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardSentenceStarts", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_iter_backward_sentence_starts(self, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardToTagToggle", TYP, T, TYP, Gtk$Gtk$TextTag$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextTag * tag = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_text_iter_backward_to_tag_toggle(self, tag);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardVisibleCursorPosition", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_backward_visible_cursor_position(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardVisibleCursorPositions", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_iter_backward_visible_cursor_positions(self, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardVisibleLine", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_backward_visible_line(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardVisibleLines", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_iter_backward_visible_lines(self, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardVisibleWordStart", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_backward_visible_word_start(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardVisibleWordStarts", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_iter_backward_visible_word_starts(self, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardWordStart", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_backward_word_start(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardWordStarts", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_iter_backward_word_starts(self, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BeginsTag", TYP, T, TYP, Gtk$Gtk$TextTag$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextTag * tag = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_text_iter_begins_tag(self, tag);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("CanInsert", TYP, T, TYP, Std$Symbol$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int default_editability = Args[1].Val == $true;
	int result = gtk_text_iter_can_insert(self, default_editability);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Compare", TYP, T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextIter * rhs= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	int result = gtk_text_iter_compare(self, rhs);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextIter * result = gtk_text_iter_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Editable", TYP, T, TYP, Std$Symbol$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int default_setting = Args[1].Val == $true;
	int result = gtk_text_iter_editable(self, default_setting);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("EndsLine", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_ends_line(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("EndsSentence", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_ends_sentence(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("EndsTag", TYP, T, TYP, Gtk$Gtk$TextTag$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextTag * tag = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_text_iter_ends_tag(self, tag);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("EndsWord", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_ends_word(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Equal", TYP, T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextIter * rhs= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	int result = gtk_text_iter_equal(self, rhs);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardChar", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_forward_char(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardChars", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_iter_forward_chars(self, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardCursorPosition", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_forward_cursor_position(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardCursorPositions", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_iter_forward_cursor_positions(self, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardFindChar", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextCharPredicate pred = Gtk$Gtk$TextCharPredicate$new(Args[1].Val);
	void *user_data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkTextIter * limit= &((Gtk$Gtk$TextIter_t *)Args[3].Val)->Value;
	int result = gtk_text_iter_forward_find_char(self, pred, user_data, limit);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardLine", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_forward_line(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardLines", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_iter_forward_lines(self, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardSearch", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	char *str = Std$String$flatten(Args[1].Val);
	int flags = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkTextIter * match_start= &((Gtk$Gtk$TextIter_t *)Args[3].Val)->Value;
	GtkTextIter * match_end= &((Gtk$Gtk$TextIter_t *)Args[4].Val)->Value;
	GtkTextIter * limit= &((Gtk$Gtk$TextIter_t *)Args[5].Val)->Value;
	int result = gtk_text_iter_forward_search(self, str, flags, match_start, match_end, limit);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardSentenceEnd", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_forward_sentence_end(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardSentenceEnds", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_iter_forward_sentence_ends(self, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardToEnd", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	gtk_text_iter_forward_to_end(self);
	return SUCCESS;
};

METHOD("ForwardToLineEnd", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_forward_to_line_end(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardToTagToggle", TYP, T, TYP, Gtk$Gtk$TextTag$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextTag * tag = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_text_iter_forward_to_tag_toggle(self, tag);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardVisibleCursorPosition", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_forward_visible_cursor_position(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardVisibleCursorPositions", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_iter_forward_visible_cursor_positions(self, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardVisibleLine", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_forward_visible_line(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardVisibleLines", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_iter_forward_visible_lines(self, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardVisibleWordEnd", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_forward_visible_word_end(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardVisibleWordEnds", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_iter_forward_visible_word_ends(self, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardWordEnd", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_forward_word_end(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardWordEnds", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_iter_forward_word_ends(self, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	gtk_text_iter_free(self);
	return SUCCESS;
};

METHOD("GetAttributes", TYP, T, TYP, Gtk$Gtk$TextAttributes$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextAttributes * values= ((Gtk$Gtk$TextAttributes_t *)Args[1].Val)->Value;
	int result = gtk_text_iter_get_attributes(self, values);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetBuffer", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextBuffer * result = gtk_text_iter_get_buffer(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetBytesInLine", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_get_bytes_in_line(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetChar", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	gunichar result = gtk_text_iter_get_char(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetCharsInLine", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_get_chars_in_line(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetChildAnchor", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextChildAnchor * result = gtk_text_iter_get_child_anchor(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetLanguage", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	PangoLanguage * result = gtk_text_iter_get_language(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetLine", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_get_line(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetLineIndex", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_get_line_index(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetLineOffset", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_get_line_offset(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetMarks", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GSList* result = gtk_text_iter_get_marks(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetOffset", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_get_offset(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetPixbuf", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GdkPixbuf * result = gtk_text_iter_get_pixbuf(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetSlice", TYP, T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	char * result = gtk_text_iter_get_slice(self, end);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetTags", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GSList* result = gtk_text_iter_get_tags(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetText", TYP, T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	char * result = gtk_text_iter_get_text(self, end);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetToggledTags", TYP, T, TYP, Std$Symbol$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int toggled_on = Args[1].Val == $true;
	GSList* result = gtk_text_iter_get_toggled_tags(self, toggled_on);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetVisibleLineIndex", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_get_visible_line_index(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetVisibleLineOffset", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_get_visible_line_offset(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetVisibleSlice", TYP, T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	char * result = gtk_text_iter_get_visible_slice(self, end);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetVisibleText", TYP, T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	char * result = gtk_text_iter_get_visible_text(self, end);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("HasTag", TYP, T, TYP, Gtk$Gtk$TextTag$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextTag * tag = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_text_iter_has_tag(self, tag);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("InRange", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextIter * start= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GtkTextIter * end= &((Gtk$Gtk$TextIter_t *)Args[2].Val)->Value;
	int result = gtk_text_iter_in_range(self, start, end);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("InsideSentence", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_inside_sentence(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("InsideWord", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_inside_word(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsCursorPosition", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_is_cursor_position(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsEnd", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_is_end(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsStart", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_is_start(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Order", TYP, T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextIter * second= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	gtk_text_iter_order(self, second);
	return SUCCESS;
};

METHOD("SetLine", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int line_number = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_text_iter_set_line(self, line_number);
	return SUCCESS;
};

METHOD("SetLineIndex", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int byte_on_line = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_text_iter_set_line_index(self, byte_on_line);
	return SUCCESS;
};

METHOD("SetLineOffset", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int char_on_line = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_text_iter_set_line_offset(self, char_on_line);
	return SUCCESS;
};

METHOD("SetOffset", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int char_offset = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_text_iter_set_offset(self, char_offset);
	return SUCCESS;
};

METHOD("SetVisibleLineIndex", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int byte_on_line = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_text_iter_set_visible_line_index(self, byte_on_line);
	return SUCCESS;
};

METHOD("SetVisibleLineOffset", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int char_on_line = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_text_iter_set_visible_line_offset(self, char_on_line);
	return SUCCESS;
};

METHOD("StartsLine", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_starts_line(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("StartsSentence", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_starts_sentence(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("StartsWord", TYP, T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	int result = gtk_text_iter_starts_word(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("TogglesTag", TYP, T, TYP, Gtk$Gtk$TextTag$T) {
	GtkTextIter * self= &((Gtk$Gtk$TextIter_t *)Args[0].Val)->Value;
	GtkTextTag * tag = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_text_iter_toggles_tag(self, tag);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

