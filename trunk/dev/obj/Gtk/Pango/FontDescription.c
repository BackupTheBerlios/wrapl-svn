#include <Gtk/Pango/FontDescription.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 9
#include <Std/Boolean.h>
#include <Gtk/Pango/Style.h>
#include <Gtk/Pango/FontDescription.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Weight.h>
#include <Gtk/Pango/Stretch.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/Variant.h>
#include <Gtk/Pango/Gravity.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 0) {
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = pango_font_description_new();
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(FromString, 1) {
	char *str = Std$String$flatten(Args[0].Val);
	PangoFontDescription * result = pango_font_description_from_string(str);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_font_description_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("BetterMatch", TYP, T, TYP, Gtk$Pango$FontDescription$T, TYP, Gtk$Pango$FontDescription$T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	PangoFontDescription * old_match= ((Gtk$Pango$FontDescription_t *)Args[1].Val)->Value;
	PangoFontDescription * new_match= ((Gtk$Pango$FontDescription_t *)Args[2].Val)->Value;
	int result = pango_font_description_better_match(self, old_match, new_match);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	PangoFontDescription * result = pango_font_description_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("CopyStatic", TYP, T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	PangoFontDescription * result = pango_font_description_copy_static(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Equal", TYP, T, TYP, Gtk$Pango$FontDescription$T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	PangoFontDescription * desc2= ((Gtk$Pango$FontDescription_t *)Args[1].Val)->Value;
	int result = pango_font_description_equal(self, desc2);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	pango_font_description_free(self);
	return SUCCESS;
};

METHOD("GetFamily", TYP, T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	const char * result = pango_font_description_get_family(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetGravity", TYP, T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	PangoGravity result = pango_font_description_get_gravity(self);
	Gtk$Pango$Gravity_t *_result = new(Gtk$Pango$Gravity_t);
	_result->Type = Gtk$Pango$Gravity$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetSetFields", TYP, T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	int result = pango_font_description_get_set_fields(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetSize", TYP, T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	int result = pango_font_description_get_size(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetSizeIsAbsolute", TYP, T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	int result = pango_font_description_get_size_is_absolute(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetStretch", TYP, T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	PangoStretch result = pango_font_description_get_stretch(self);
	Gtk$Pango$Stretch_t *_result = new(Gtk$Pango$Stretch_t);
	_result->Type = Gtk$Pango$Stretch$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetStyle", TYP, T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	PangoStyle result = pango_font_description_get_style(self);
	Gtk$Pango$Style_t *_result = new(Gtk$Pango$Style_t);
	_result->Type = Gtk$Pango$Style$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetVariant", TYP, T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	PangoVariant result = pango_font_description_get_variant(self);
	Gtk$Pango$Variant_t *_result = new(Gtk$Pango$Variant_t);
	_result->Type = Gtk$Pango$Variant$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetWeight", TYP, T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	PangoWeight result = pango_font_description_get_weight(self);
	Gtk$Pango$Weight_t *_result = new(Gtk$Pango$Weight_t);
	_result->Type = Gtk$Pango$Weight$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("Hash", TYP, T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	int result = pango_font_description_hash(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Merge", TYP, T, TYP, Gtk$Pango$FontDescription$T, TYP, Std$Symbol$T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	PangoFontDescription * desc_to_merge= ((Gtk$Pango$FontDescription_t *)Args[1].Val)->Value;
	int replace_existing = Args[2].Val == $true;
	pango_font_description_merge(self, desc_to_merge, replace_existing);
	return SUCCESS;
};

METHOD("MergeStatic", TYP, T, TYP, Gtk$Pango$FontDescription$T, TYP, Std$Symbol$T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	PangoFontDescription * desc_to_merge= ((Gtk$Pango$FontDescription_t *)Args[1].Val)->Value;
	int replace_existing = Args[2].Val == $true;
	pango_font_description_merge_static(self, desc_to_merge, replace_existing);
	return SUCCESS;
};

METHOD("SetAbsoluteSize", TYP, T, TYP, Std$Real$T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	double size = ((Std$Real_t *)Args[1].Val)->Value;
	pango_font_description_set_absolute_size(self, size);
	return SUCCESS;
};

METHOD("SetFamily", TYP, T, TYP, Std$String$T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	char *family = Std$String$flatten(Args[1].Val);
	pango_font_description_set_family(self, family);
	return SUCCESS;
};

METHOD("SetFamilyStatic", TYP, T, TYP, Std$String$T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	char *family = Std$String$flatten(Args[1].Val);
	pango_font_description_set_family_static(self, family);
	return SUCCESS;
};

METHOD("SetGravity", TYP, T, TYP, Gtk$Pango$Gravity$T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	PangoGravity gravity = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_font_description_set_gravity(self, gravity);
	return SUCCESS;
};

METHOD("SetSize", TYP, T, TYP, Std$Integer$SmallT) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	int size = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_font_description_set_size(self, size);
	return SUCCESS;
};

METHOD("SetStretch", TYP, T, TYP, Gtk$Pango$Stretch$T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	PangoStretch stretch = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_font_description_set_stretch(self, stretch);
	return SUCCESS;
};

METHOD("SetStyle", TYP, T, TYP, Gtk$Pango$Style$T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	PangoStyle style = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_font_description_set_style(self, style);
	return SUCCESS;
};

METHOD("SetVariant", TYP, T, TYP, Gtk$Pango$Variant$T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	PangoVariant variant = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_font_description_set_variant(self, variant);
	return SUCCESS;
};

METHOD("SetWeight", TYP, T, TYP, Gtk$Pango$Weight$T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	PangoWeight weight = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_font_description_set_weight(self, weight);
	return SUCCESS;
};

METHOD("ToFilename", TYP, T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	char * result = pango_font_description_to_filename(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("ToString", TYP, T) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	char * result = pango_font_description_to_string(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("UnsetFields", TYP, T, TYP, Std$Integer$SmallT) {
	PangoFontDescription * self= ((Gtk$Pango$FontDescription_t *)Args[0].Val)->Value;
	int to_unset = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_font_description_unset_fields(self, to_unset);
	return SUCCESS;
};

