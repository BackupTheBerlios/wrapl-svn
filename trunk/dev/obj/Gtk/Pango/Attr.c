#include <Gtk/Pango/Attr.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 12
#include <Std/Boolean.h>
#include <Gtk/Pango/Style.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Weight.h>
#include <Gtk/Pango/Underline.h>
#include <Gtk/Pango/AttrType.h>
#include <Gtk/Pango/Attribute.h>
#include <Gtk/Pango/Stretch.h>
#include <Gtk/Pango/Variant.h>
#include <Gtk/Pango/GravityHint.h>
#include <Gtk/Pango/Gravity.h>
#include <Std/Boolean.h>
/***********************************/
GLOBAL_FUNCTION(BackgroundNew, 3) {
	int red = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int green = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int blue = ((Std$Integer_smallt *)Args[2].Val)->Value;
	PangoAttribute * result = pango_attr_background_new(red, green, blue);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(FallbackNew, 1) {
	int enable_fallback = Args[0].Val == $true;
	PangoAttribute * result = pango_attr_fallback_new(enable_fallback);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(FamilyNew, 1) {
	char *family = Std$String$flatten(Args[0].Val);
	PangoAttribute * result = pango_attr_family_new(family);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(ForegroundNew, 3) {
	int red = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int green = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int blue = ((Std$Integer_smallt *)Args[2].Val)->Value;
	PangoAttribute * result = pango_attr_foreground_new(red, green, blue);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GravityHintNew, 1) {
	PangoGravityHint hint = ((Std$Integer_smallt *)Args[0].Val)->Value;
	PangoAttribute * result = pango_attr_gravity_hint_new(hint);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GravityNew, 1) {
	PangoGravity gravity = ((Std$Integer_smallt *)Args[0].Val)->Value;
	PangoAttribute * result = pango_attr_gravity_new(gravity);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(LetterSpacingNew, 1) {
	int letter_spacing = ((Std$Integer_smallt *)Args[0].Val)->Value;
	PangoAttribute * result = pango_attr_letter_spacing_new(letter_spacing);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(RiseNew, 1) {
	int rise = ((Std$Integer_smallt *)Args[0].Val)->Value;
	PangoAttribute * result = pango_attr_rise_new(rise);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(ScaleNew, 1) {
	double scale_factor = ((Std$Real_t *)Args[0].Val)->Value;
	PangoAttribute * result = pango_attr_scale_new(scale_factor);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(StretchNew, 1) {
	PangoStretch stretch = ((Std$Integer_smallt *)Args[0].Val)->Value;
	PangoAttribute * result = pango_attr_stretch_new(stretch);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(StrikethroughColorNew, 3) {
	int red = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int green = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int blue = ((Std$Integer_smallt *)Args[2].Val)->Value;
	PangoAttribute * result = pango_attr_strikethrough_color_new(red, green, blue);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(StrikethroughNew, 1) {
	int strikethrough = Args[0].Val == $true;
	PangoAttribute * result = pango_attr_strikethrough_new(strikethrough);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(StyleNew, 1) {
	PangoStyle style = ((Std$Integer_smallt *)Args[0].Val)->Value;
	PangoAttribute * result = pango_attr_style_new(style);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(TypeRegister, 1) {
	char *name = Std$String$flatten(Args[0].Val);
	PangoAttrType result = pango_attr_type_register(name);
	Gtk$Pango$AttrType_t *_result = new(Gtk$Pango$AttrType_t);
	_result->Type = Gtk$Pango$AttrType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

GLOBAL_FUNCTION(UnderlineColorNew, 3) {
	int red = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int green = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int blue = ((Std$Integer_smallt *)Args[2].Val)->Value;
	PangoAttribute * result = pango_attr_underline_color_new(red, green, blue);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(UnderlineNew, 1) {
	PangoUnderline underline = ((Std$Integer_smallt *)Args[0].Val)->Value;
	PangoAttribute * result = pango_attr_underline_new(underline);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(VariantNew, 1) {
	PangoVariant variant = ((Std$Integer_smallt *)Args[0].Val)->Value;
	PangoAttribute * result = pango_attr_variant_new(variant);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(WeightNew, 1) {
	PangoWeight weight = ((Std$Integer_smallt *)Args[0].Val)->Value;
	PangoAttribute * result = pango_attr_weight_new(weight);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

