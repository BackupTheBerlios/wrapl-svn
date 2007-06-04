#include <Gtk/Gtk/TextView.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 16
#include <Gtk/Pango/TabArray.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TextAttributes.h>
#include <Gtk/Gtk/WrapMode.h>
#include <Gtk/Gtk/TextWindowType.h>
#include <Gtk/Gtk/Justification.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/TextMark.h>
#include <Gtk/Gtk/TextIter.h>
#include <Gtk/Gtk/TextView.h>
#include <Gtk/Gtk/TextBuffer.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Gtk/Gdk/Window.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/TextChildAnchor.h>
/***********************************/
TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkTextView * result = gtk_text_view_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithBuffer, 1) {
	GtkTextBuffer * buffer = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextView * result = gtk_text_view_new_with_buffer(buffer);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_text_view_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddChildAtAnchor", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gtk$TextChildAnchor$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTextChildAnchor * anchor = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_text_view_add_child_at_anchor(self, child, anchor);
	return SUCCESS;
};

METHOD("AddChildInWindow", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gtk$TextWindowType$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTextWindowType which_window = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int xpos = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int ypos = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_text_view_add_child_in_window(self, child, which_window, xpos, ypos);
	return SUCCESS;
};

METHOD("BackwardDisplayLine", TYP, T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	int result = gtk_text_view_backward_display_line(self, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BackwardDisplayLineStart", TYP, T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	int result = gtk_text_view_backward_display_line_start(self, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("BufferToWindowCoords", TYP, T, TYP, Gtk$Gtk$TextWindowType$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextWindowType win = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int buffer_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int buffer_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gint* window_x = 0;
	gint* window_y = 0;
	gtk_text_view_buffer_to_window_coords(self, win, buffer_x, buffer_y, window_x, window_y);
	return SUCCESS;
};

METHOD("ForwardDisplayLine", TYP, T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	int result = gtk_text_view_forward_display_line(self, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ForwardDisplayLineEnd", TYP, T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	int result = gtk_text_view_forward_display_line_end(self, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetAcceptsTab", TYP, T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_view_get_accepts_tab(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetBorderWindowSize", TYP, T, TYP, Gtk$Gtk$TextWindowType$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextWindowType type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_text_view_get_border_window_size(self, type);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetBuffer", TYP, T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextBuffer * result = gtk_text_view_get_buffer(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetCursorVisible", TYP, T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_view_get_cursor_visible(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetDefaultAttributes", TYP, T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextAttributes * result = gtk_text_view_get_default_attributes(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetEditable", TYP, T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_view_get_editable(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetIndent", TYP, T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_view_get_indent(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetIterAtLocation", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_text_view_get_iter_at_location(self, iter, x, y);
	return SUCCESS;
};

METHOD("GetIterAtPosition", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Object$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	gint* trailing = 0;
	int x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_text_view_get_iter_at_position(self, iter, trailing, x, y);
	return SUCCESS;
};

METHOD("GetIterLocation", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Gtk$Gdk$Rectangle$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	GdkRectangle * location= &((Gtk$Gdk$Rectangle_t *)Args[2].Val)->Value;
	gtk_text_view_get_iter_location(self, iter, location);
	return SUCCESS;
};

METHOD("GetJustification", TYP, T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkJustification result = gtk_text_view_get_justification(self);
	Gtk$Gtk$Justification_t *_result = new(Gtk$Gtk$Justification_t);
	_result->Type = Gtk$Gtk$Justification$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetLeftMargin", TYP, T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_view_get_left_margin(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetLineAtY", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * target_iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gint* line_top = 0;
	gtk_text_view_get_line_at_y(self, target_iter, y, line_top);
	return SUCCESS;
};

METHOD("GetLineYrange", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	gint* y = 0;
	gint* height = 0;
	gtk_text_view_get_line_yrange(self, iter, y, height);
	return SUCCESS;
};

METHOD("GetOverwrite", TYP, T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_view_get_overwrite(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetPixelsAboveLines", TYP, T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_view_get_pixels_above_lines(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetPixelsBelowLines", TYP, T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_view_get_pixels_below_lines(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetPixelsInsideWrap", TYP, T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_view_get_pixels_inside_wrap(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetRightMargin", TYP, T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_view_get_right_margin(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetTabs", TYP, T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoTabArray * result = gtk_text_view_get_tabs(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetVisibleRect", TYP, T, TYP, Gtk$Gdk$Rectangle$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRectangle * visible_rect= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	gtk_text_view_get_visible_rect(self, visible_rect);
	return SUCCESS;
};

METHOD("GetWindow", TYP, T, TYP, Gtk$Gtk$TextWindowType$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextWindowType win = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkWindow * result = gtk_text_view_get_window(self, win);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetWindowType", TYP, T, TYP, Gtk$Gdk$Window$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTextWindowType result = gtk_text_view_get_window_type(self, window);
	Gtk$Gtk$TextWindowType_t *_result = new(Gtk$Gtk$TextWindowType_t);
	_result->Type = Gtk$Gtk$TextWindowType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetWrapMode", TYP, T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWrapMode result = gtk_text_view_get_wrap_mode(self);
	Gtk$Gtk$WrapMode_t *_result = new(Gtk$Gtk$WrapMode_t);
	_result->Type = Gtk$Gtk$WrapMode$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("MoveChild", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int xpos = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int ypos = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_text_view_move_child(self, child, xpos, ypos);
	return SUCCESS;
};

METHOD("MoveMarkOnscreen", TYP, T, TYP, Gtk$Gtk$TextMark$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextMark * mark = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_text_view_move_mark_onscreen(self, mark);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("MoveVisually", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Integer$SmallT) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	int count = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gtk_text_view_move_visually(self, iter, count);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("PlaceCursorOnscreen", TYP, T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_view_place_cursor_onscreen(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ScrollMarkOnscreen", TYP, T, TYP, Gtk$Gtk$TextMark$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextMark * mark = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_text_view_scroll_mark_onscreen(self, mark);
	return SUCCESS;
};

METHOD("ScrollToIter", TYP, T, TYP, Gtk$Gtk$TextIter$T, TYP, Std$Real$T, TYP, Std$Symbol$T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	double within_margin = ((Std$Real_t *)Args[2].Val)->Value;
	int use_align = Args[3].Val == $true;
	double xalign = ((Std$Real_t *)Args[4].Val)->Value;
	double yalign = ((Std$Real_t *)Args[5].Val)->Value;
	int result = gtk_text_view_scroll_to_iter(self, iter, within_margin, use_align, xalign, yalign);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ScrollToMark", TYP, T, TYP, Gtk$Gtk$TextMark$T, TYP, Std$Real$T, TYP, Std$Symbol$T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextMark * mark = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	double within_margin = ((Std$Real_t *)Args[2].Val)->Value;
	int use_align = Args[3].Val == $true;
	double xalign = ((Std$Real_t *)Args[4].Val)->Value;
	double yalign = ((Std$Real_t *)Args[5].Val)->Value;
	gtk_text_view_scroll_to_mark(self, mark, within_margin, use_align, xalign, yalign);
	return SUCCESS;
};

METHOD("SetAcceptsTab", TYP, T, TYP, Std$Symbol$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int accepts_tab = Args[1].Val == $true;
	gtk_text_view_set_accepts_tab(self, accepts_tab);
	return SUCCESS;
};

METHOD("SetBorderWindowSize", TYP, T, TYP, Gtk$Gtk$TextWindowType$T, TYP, Std$Integer$SmallT) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextWindowType type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int size = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_text_view_set_border_window_size(self, type, size);
	return SUCCESS;
};

METHOD("SetBuffer", TYP, T, TYP, Gtk$Gtk$TextBuffer$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextBuffer * buffer = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_text_view_set_buffer(self, buffer);
	return SUCCESS;
};

METHOD("SetCursorVisible", TYP, T, TYP, Std$Symbol$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_text_view_set_cursor_visible(self, setting);
	return SUCCESS;
};

METHOD("SetEditable", TYP, T, TYP, Std$Symbol$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_text_view_set_editable(self, setting);
	return SUCCESS;
};

METHOD("SetIndent", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int indent = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_text_view_set_indent(self, indent);
	return SUCCESS;
};

METHOD("SetJustification", TYP, T, TYP, Gtk$Gtk$Justification$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkJustification justification = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_text_view_set_justification(self, justification);
	return SUCCESS;
};

METHOD("SetLeftMargin", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int left_margin = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_text_view_set_left_margin(self, left_margin);
	return SUCCESS;
};

METHOD("SetOverwrite", TYP, T, TYP, Std$Symbol$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int overwrite = Args[1].Val == $true;
	gtk_text_view_set_overwrite(self, overwrite);
	return SUCCESS;
};

METHOD("SetPixelsAboveLines", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int pixels_above_lines = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_text_view_set_pixels_above_lines(self, pixels_above_lines);
	return SUCCESS;
};

METHOD("SetPixelsBelowLines", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int pixels_below_lines = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_text_view_set_pixels_below_lines(self, pixels_below_lines);
	return SUCCESS;
};

METHOD("SetPixelsInsideWrap", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int pixels_inside_wrap = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_text_view_set_pixels_inside_wrap(self, pixels_inside_wrap);
	return SUCCESS;
};

METHOD("SetRightMargin", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int right_margin = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_text_view_set_right_margin(self, right_margin);
	return SUCCESS;
};

METHOD("SetTabs", TYP, T, TYP, Gtk$Pango$TabArray$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoTabArray * tabs= ((Gtk$Pango$TabArray_t *)Args[1].Val)->Value;
	gtk_text_view_set_tabs(self, tabs);
	return SUCCESS;
};

METHOD("SetWrapMode", TYP, T, TYP, Gtk$Gtk$WrapMode$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWrapMode wrap_mode = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_text_view_set_wrap_mode(self, wrap_mode);
	return SUCCESS;
};

METHOD("StartsDisplayLine", TYP, T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[1].Val)->Value;
	int result = gtk_text_view_starts_display_line(self, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("WindowToBufferCoords", TYP, T, TYP, Gtk$Gtk$TextWindowType$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkTextView * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextWindowType win = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int window_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int window_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gint* buffer_x = 0;
	gint* buffer_y = 0;
	gtk_text_view_window_to_buffer_coords(self, win, window_x, window_y, buffer_x, buffer_y);
	return SUCCESS;
};

