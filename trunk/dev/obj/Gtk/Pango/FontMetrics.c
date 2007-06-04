#include <Gtk/Pango/FontMetrics.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Pango/FontMetrics.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_font_metrics_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetApproximateCharWidth", TYP, T) {
	PangoFontMetrics * self= ((Gtk$Pango$FontMetrics_t *)Args[0].Val)->Value;
	int result = pango_font_metrics_get_approximate_char_width(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetApproximateDigitWidth", TYP, T) {
	PangoFontMetrics * self= ((Gtk$Pango$FontMetrics_t *)Args[0].Val)->Value;
	int result = pango_font_metrics_get_approximate_digit_width(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetAscent", TYP, T) {
	PangoFontMetrics * self= ((Gtk$Pango$FontMetrics_t *)Args[0].Val)->Value;
	int result = pango_font_metrics_get_ascent(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetDescent", TYP, T) {
	PangoFontMetrics * self= ((Gtk$Pango$FontMetrics_t *)Args[0].Val)->Value;
	int result = pango_font_metrics_get_descent(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetStrikethroughPosition", TYP, T) {
	PangoFontMetrics * self= ((Gtk$Pango$FontMetrics_t *)Args[0].Val)->Value;
	int result = pango_font_metrics_get_strikethrough_position(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetStrikethroughThickness", TYP, T) {
	PangoFontMetrics * self= ((Gtk$Pango$FontMetrics_t *)Args[0].Val)->Value;
	int result = pango_font_metrics_get_strikethrough_thickness(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetUnderlinePosition", TYP, T) {
	PangoFontMetrics * self= ((Gtk$Pango$FontMetrics_t *)Args[0].Val)->Value;
	int result = pango_font_metrics_get_underline_position(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetUnderlineThickness", TYP, T) {
	PangoFontMetrics * self= ((Gtk$Pango$FontMetrics_t *)Args[0].Val)->Value;
	int result = pango_font_metrics_get_underline_thickness(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	PangoFontMetrics * self= ((Gtk$Pango$FontMetrics_t *)Args[0].Val)->Value;
	PangoFontMetrics * result = pango_font_metrics_ref(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	PangoFontMetrics * self= ((Gtk$Pango$FontMetrics_t *)Args[0].Val)->Value;
	pango_font_metrics_unref(self);
	return SUCCESS;
};

