#include <Gtk/Gtk/Label.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 10
#include <Gtk/Pango/EllipsizeMode.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Layout.h>
#include <Gtk/Pango/WrapMode.h>
#include <Gtk/Pango/AttrList.h>
#include <Gtk/Gtk/Justification.h>
#include <Gtk/Gtk/Label.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Misc$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	char *str = Std$String$flatten(Args[0].Val);
	GtkLabel * result = gtk_label_new(str);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithMnemonic, 1) {
	char *str = Std$String$flatten(Args[0].Val);
	GtkLabel * result = gtk_label_new_with_mnemonic(str);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_label_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Get", TYP, T, TYP, Std$List$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * str;
	gtk_label_get(self, str);
	return SUCCESS;
};

METHOD("GetAngle", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = gtk_label_get_angle(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetAttributes", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoAttrList * result = gtk_label_get_attributes(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetEllipsize", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoEllipsizeMode result = gtk_label_get_ellipsize(self);
	Gtk$Pango$EllipsizeMode_t *_result = new(Gtk$Pango$EllipsizeMode_t);
	_result->Type = Gtk$Pango$EllipsizeMode$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetJustify", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkJustification result = gtk_label_get_justify(self);
	Gtk$Gtk$Justification_t *_result = new(Gtk$Gtk$Justification_t);
	_result->Type = Gtk$Gtk$Justification$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetLabel", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_label_get_label(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetLayout", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoLayout * result = gtk_label_get_layout(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetLayoutOffsets", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* x = 0;
	gint* y = 0;
	gtk_label_get_layout_offsets(self, x, y);
	return SUCCESS;
};

METHOD("GetLineWrap", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_label_get_line_wrap(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetLineWrapMode", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoWrapMode result = gtk_label_get_line_wrap_mode(self);
	Gtk$Pango$WrapMode_t *_result = new(Gtk$Pango$WrapMode_t);
	_result->Type = Gtk$Pango$WrapMode$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetMaxWidthChars", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_label_get_max_width_chars(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetMnemonicKeyval", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_label_get_mnemonic_keyval(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetMnemonicWidget", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_label_get_mnemonic_widget(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetSelectable", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_label_get_selectable(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSelectionBounds", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* start = 0;
	gint* end = 0;
	int result = gtk_label_get_selection_bounds(self, start, end);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSingleLineMode", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_label_get_single_line_mode(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetText", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_label_get_text(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetUseMarkup", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_label_get_use_markup(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetUseUnderline", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_label_get_use_underline(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetWidthChars", TYP, T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_label_get_width_chars(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("ParseUline", TYP, T, TYP, Std$String$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *string = Std$String$flatten(Args[1].Val);
	int result = gtk_label_parse_uline(self, string);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("SelectRegion", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int start_offset = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int end_offset = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_label_select_region(self, start_offset, end_offset);
	return SUCCESS;
};

METHOD("SetAngle", TYP, T, TYP, Std$Real$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double angle = ((Std$Real_t *)Args[1].Val)->Value;
	gtk_label_set_angle(self, angle);
	return SUCCESS;
};

METHOD("SetAttributes", TYP, T, TYP, Gtk$Pango$AttrList$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoAttrList * attrs= ((Gtk$Pango$AttrList_t *)Args[1].Val)->Value;
	gtk_label_set_attributes(self, attrs);
	return SUCCESS;
};

METHOD("SetEllipsize", TYP, T, TYP, Gtk$Pango$EllipsizeMode$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoEllipsizeMode mode = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_label_set_ellipsize(self, mode);
	return SUCCESS;
};

METHOD("SetJustify", TYP, T, TYP, Gtk$Gtk$Justification$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkJustification jtype = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_label_set_justify(self, jtype);
	return SUCCESS;
};

METHOD("SetLabel", TYP, T, TYP, Std$String$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *str = Std$String$flatten(Args[1].Val);
	gtk_label_set_label(self, str);
	return SUCCESS;
};

METHOD("SetLineWrap", TYP, T, TYP, Std$Symbol$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int wrap = Args[1].Val == $true;
	gtk_label_set_line_wrap(self, wrap);
	return SUCCESS;
};

METHOD("SetLineWrapMode", TYP, T, TYP, Gtk$Pango$WrapMode$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoWrapMode wrap_mode = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_label_set_line_wrap_mode(self, wrap_mode);
	return SUCCESS;
};

METHOD("SetMarkup", TYP, T, TYP, Std$String$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *str = Std$String$flatten(Args[1].Val);
	gtk_label_set_markup(self, str);
	return SUCCESS;
};

METHOD("SetMarkupWithMnemonic", TYP, T, TYP, Std$String$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *str = Std$String$flatten(Args[1].Val);
	gtk_label_set_markup_with_mnemonic(self, str);
	return SUCCESS;
};

METHOD("SetMaxWidthChars", TYP, T, TYP, Std$Integer$SmallT) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int n_chars = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_label_set_max_width_chars(self, n_chars);
	return SUCCESS;
};

METHOD("SetMnemonicWidget", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_label_set_mnemonic_widget(self, widget);
	return SUCCESS;
};

METHOD("SetPattern", TYP, T, TYP, Std$String$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *pattern = Std$String$flatten(Args[1].Val);
	gtk_label_set_pattern(self, pattern);
	return SUCCESS;
};

METHOD("SetSelectable", TYP, T, TYP, Std$Symbol$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_label_set_selectable(self, setting);
	return SUCCESS;
};

METHOD("SetSingleLineMode", TYP, T, TYP, Std$Symbol$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int single_line_mode = Args[1].Val == $true;
	gtk_label_set_single_line_mode(self, single_line_mode);
	return SUCCESS;
};

METHOD("SetText", TYP, T, TYP, Std$String$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *str = Std$String$flatten(Args[1].Val);
	gtk_label_set_text(self, str);
	return SUCCESS;
};

METHOD("SetTextWithMnemonic", TYP, T, TYP, Std$String$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *str = Std$String$flatten(Args[1].Val);
	gtk_label_set_text_with_mnemonic(self, str);
	return SUCCESS;
};

METHOD("SetUseMarkup", TYP, T, TYP, Std$Symbol$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_label_set_use_markup(self, setting);
	return SUCCESS;
};

METHOD("SetUseUnderline", TYP, T, TYP, Std$Symbol$T) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_label_set_use_underline(self, setting);
	return SUCCESS;
};

METHOD("SetWidthChars", TYP, T, TYP, Std$Integer$SmallT) {
	GtkLabel * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int n_chars = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_label_set_width_chars(self, n_chars);
	return SUCCESS;
};

