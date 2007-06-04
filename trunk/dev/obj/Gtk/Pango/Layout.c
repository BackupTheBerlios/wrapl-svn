#include <Gtk/Pango/Layout.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 14
#include <Gtk/Pango/EllipsizeMode.h>
#include <Gtk/Pango/FontDescription.h>
#include <Gtk/Pango/Rectangle.h>
#include <Gtk/Pango/TabArray.h>
#include <Gtk/Pango/LayoutLine.h>
#include <Gtk/Pango/LayoutIter.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Layout.h>
#include <Gtk/Pango/WrapMode.h>
#include <Gtk/Pango/AttrList.h>
#include <Gtk/Pango/Context.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/Alignment.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	PangoContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoLayout * result = pango_layout_new(context);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_layout_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("ContextChanged", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	pango_layout_context_changed(self);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoLayout * result = pango_layout_copy(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetAlignment", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoAlignment result = pango_layout_get_alignment(self);
	Gtk$Pango$Alignment_t *_result = new(Gtk$Pango$Alignment_t);
	_result->Type = Gtk$Pango$Alignment$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetAttributes", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoAttrList * result = pango_layout_get_attributes(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetAutoDir", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = pango_layout_get_auto_dir(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetContext", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoContext * result = pango_layout_get_context(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetCursorPos", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Pango$Rectangle$T, TYP, Gtk$Pango$Rectangle$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int index_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	PangoRectangle * strong_pos= &((Gtk$Pango$Rectangle_t *)Args[2].Val)->Value;
	PangoRectangle * weak_pos= &((Gtk$Pango$Rectangle_t *)Args[3].Val)->Value;
	pango_layout_get_cursor_pos(self, index_, strong_pos, weak_pos);
	return SUCCESS;
};

METHOD("GetEllipsize", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoEllipsizeMode result = pango_layout_get_ellipsize(self);
	Gtk$Pango$EllipsizeMode_t *_result = new(Gtk$Pango$EllipsizeMode_t);
	_result->Type = Gtk$Pango$EllipsizeMode$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetExtents", TYP, T, TYP, Gtk$Pango$Rectangle$T, TYP, Gtk$Pango$Rectangle$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoRectangle * ink_rect= &((Gtk$Pango$Rectangle_t *)Args[1].Val)->Value;
	PangoRectangle * logical_rect= &((Gtk$Pango$Rectangle_t *)Args[2].Val)->Value;
	pango_layout_get_extents(self, ink_rect, logical_rect);
	return SUCCESS;
};

METHOD("GetFontDescription", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontDescription * result = pango_layout_get_font_description(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetIndent", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = pango_layout_get_indent(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetIter", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoLayoutIter * result = pango_layout_get_iter(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetJustify", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = pango_layout_get_justify(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetLine", TYP, T, TYP, Std$Integer$SmallT) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int line = ((Std$Integer_smallt *)Args[1].Val)->Value;
	PangoLayoutLine * result = pango_layout_get_line(self, line);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetLineCount", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = pango_layout_get_line_count(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetLineReadonly", TYP, T, TYP, Std$Integer$SmallT) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int line = ((Std$Integer_smallt *)Args[1].Val)->Value;
	PangoLayoutLine * result = pango_layout_get_line_readonly(self, line);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetLines", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* result = pango_layout_get_lines(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetLinesReadonly", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* result = pango_layout_get_lines_readonly(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetLogAttrs", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoLogAttr** attrs = 0;
	gint* n_attrs = 0;
	pango_layout_get_log_attrs(self, attrs, n_attrs);
	return SUCCESS;
};

METHOD("GetPixelExtents", TYP, T, TYP, Gtk$Pango$Rectangle$T, TYP, Gtk$Pango$Rectangle$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoRectangle * ink_rect= &((Gtk$Pango$Rectangle_t *)Args[1].Val)->Value;
	PangoRectangle * logical_rect= &((Gtk$Pango$Rectangle_t *)Args[2].Val)->Value;
	pango_layout_get_pixel_extents(self, ink_rect, logical_rect);
	return SUCCESS;
};

METHOD("GetPixelSize", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int* width = 0;
	int* height = 0;
	pango_layout_get_pixel_size(self, width, height);
	return SUCCESS;
};

METHOD("GetSingleParagraphMode", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = pango_layout_get_single_paragraph_mode(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSize", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int* width = 0;
	int* height = 0;
	pango_layout_get_size(self, width, height);
	return SUCCESS;
};

METHOD("GetSpacing", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = pango_layout_get_spacing(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetTabs", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoTabArray * result = pango_layout_get_tabs(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetText", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = pango_layout_get_text(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetUnknownGlyphsCount", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = pango_layout_get_unknown_glyphs_count(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetWidth", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = pango_layout_get_width(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetWrap", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoWrapMode result = pango_layout_get_wrap(self);
	Gtk$Pango$WrapMode_t *_result = new(Gtk$Pango$WrapMode_t);
	_result->Type = Gtk$Pango$WrapMode$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("IndexToLineX", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Symbol$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int index_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int trailing = Args[2].Val == $true;
	int* line = 0;
	int* x_pos = 0;
	pango_layout_index_to_line_x(self, index_, trailing, line, x_pos);
	return SUCCESS;
};

METHOD("IndexToPos", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Pango$Rectangle$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int index_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	PangoRectangle * pos= &((Gtk$Pango$Rectangle_t *)Args[2].Val)->Value;
	pango_layout_index_to_pos(self, index_, pos);
	return SUCCESS;
};

METHOD("IsEllipsized", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = pango_layout_is_ellipsized(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsWrapped", TYP, T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = pango_layout_is_wrapped(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("MoveCursorVisually", TYP, T, TYP, Std$Symbol$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int strong = Args[1].Val == $true;
	int old_index = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int old_trailing = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int direction = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int* new_index = 0;
	int* new_trailing = 0;
	pango_layout_move_cursor_visually(self, strong, old_index, old_trailing, direction, new_index, new_trailing);
	return SUCCESS;
};

METHOD("SetAlignment", TYP, T, TYP, Gtk$Pango$Alignment$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoAlignment alignment = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_layout_set_alignment(self, alignment);
	return SUCCESS;
};

METHOD("SetAttributes", TYP, T, TYP, Gtk$Pango$AttrList$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoAttrList * attrs= ((Gtk$Pango$AttrList_t *)Args[1].Val)->Value;
	pango_layout_set_attributes(self, attrs);
	return SUCCESS;
};

METHOD("SetAutoDir", TYP, T, TYP, Std$Symbol$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int auto_dir = Args[1].Val == $true;
	pango_layout_set_auto_dir(self, auto_dir);
	return SUCCESS;
};

METHOD("SetEllipsize", TYP, T, TYP, Gtk$Pango$EllipsizeMode$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoEllipsizeMode ellipsize = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_layout_set_ellipsize(self, ellipsize);
	return SUCCESS;
};

METHOD("SetFontDescription", TYP, T, TYP, Gtk$Pango$FontDescription$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontDescription * desc= ((Gtk$Pango$FontDescription_t *)Args[1].Val)->Value;
	pango_layout_set_font_description(self, desc);
	return SUCCESS;
};

METHOD("SetIndent", TYP, T, TYP, Std$Integer$SmallT) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int indent = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_layout_set_indent(self, indent);
	return SUCCESS;
};

METHOD("SetJustify", TYP, T, TYP, Std$Symbol$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int justify = Args[1].Val == $true;
	pango_layout_set_justify(self, justify);
	return SUCCESS;
};

METHOD("SetMarkup", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *markup = Std$String$flatten(Args[1].Val);
	int length = ((Std$Integer_smallt *)Args[2].Val)->Value;
	pango_layout_set_markup(self, markup, length);
	return SUCCESS;
};

METHOD("SetMarkupWithAccel", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *markup = Std$String$flatten(Args[1].Val);
	int length = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gunichar accel_marker = 0;
	gunichar* accel_char = 0;
	pango_layout_set_markup_with_accel(self, markup, length, accel_marker, accel_char);
	return SUCCESS;
};

METHOD("SetSingleParagraphMode", TYP, T, TYP, Std$Symbol$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	pango_layout_set_single_paragraph_mode(self, setting);
	return SUCCESS;
};

METHOD("SetSpacing", TYP, T, TYP, Std$Integer$SmallT) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int spacing = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_layout_set_spacing(self, spacing);
	return SUCCESS;
};

METHOD("SetTabs", TYP, T, TYP, Gtk$Pango$TabArray$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoTabArray * tabs= ((Gtk$Pango$TabArray_t *)Args[1].Val)->Value;
	pango_layout_set_tabs(self, tabs);
	return SUCCESS;
};

METHOD("SetText", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	int length = ((Std$Integer_smallt *)Args[2].Val)->Value;
	pango_layout_set_text(self, text, length);
	return SUCCESS;
};

METHOD("SetWidth", TYP, T, TYP, Std$Integer$SmallT) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_layout_set_width(self, width);
	return SUCCESS;
};

METHOD("SetWrap", TYP, T, TYP, Gtk$Pango$WrapMode$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoWrapMode wrap = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_layout_set_wrap(self, wrap);
	return SUCCESS;
};

METHOD("XyToIndex", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int* index_ = 0;
	int* trailing = 0;
	int result = pango_layout_xy_to_index(self, x, y, index_, trailing);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

