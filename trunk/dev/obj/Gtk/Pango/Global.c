#include <Gtk/Pango/Global.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 14
#include <Std/Boolean.h>
#include <Gtk/Pango/LogAttr.h>
#include <Gtk/Pango/Direction.h>
#include <Gtk/Pango/Language.h>
#include <Gtk/Pango/Rectangle.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Script.h>
#include <Gtk/Pango/Matrix.h>
#include <Gtk/Pango/AttrList.h>
#include <Gtk/Pango/Context.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/GravityHint.h>
#include <Gtk/Pango/Gravity.h>
#include <Gtk/Pango/AttrIterator.h>
/***********************************/
GLOBAL_FUNCTION(ExtentsToPixels, 2) {
	PangoRectangle * ink_rect= &((Gtk$Pango$Rectangle_t *)Args[0].Val)->Value;
	PangoRectangle * logical_rect= &((Gtk$Pango$Rectangle_t *)Args[1].Val)->Value;
	pango_extents_to_pixels(ink_rect, logical_rect);
	return SUCCESS;
};

GLOBAL_FUNCTION(FindBaseDir, 2) {
	char *text = Std$String$flatten(Args[0].Val);
	int length = ((Std$Integer_smallt *)Args[1].Val)->Value;
	PangoDirection result = pango_find_base_dir(text, length);
	Gtk$Pango$Direction_t *_result = new(Gtk$Pango$Direction_t);
	_result->Type = Gtk$Pango$Direction$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

GLOBAL_FUNCTION(FindParagraphBoundary, 4) {
	char *text = Std$String$flatten(Args[0].Val);
	int length = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gint* paragraph_delimiter_index = 0;
	gint* next_paragraph_start = 0;
	pango_find_paragraph_boundary(text, length, paragraph_delimiter_index, next_paragraph_start);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetLogAttrs, 6) {
	char *text = Std$String$flatten(Args[0].Val);
	int length = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int level = ((Std$Integer_smallt *)Args[2].Val)->Value;
	PangoLanguage * language= ((Gtk$Pango$Language_t *)Args[3].Val)->Value;
	PangoLogAttr * log_attrs= &((Gtk$Pango$LogAttr_t *)Args[4].Val)->Value;
	int attrs_len = ((Std$Integer_smallt *)Args[5].Val)->Value;
	pango_get_log_attrs(text, length, level, language, log_attrs, attrs_len);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetMirrorChar, 2) {
	gunichar ch = 0;
	gunichar* mirrored_ch = 0;
	int result = pango_get_mirror_char(ch, mirrored_ch);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(GravityGetForMatrix, 1) {
	PangoMatrix * matrix= &((Gtk$Pango$Matrix_t *)Args[0].Val)->Value;
	PangoGravity result = pango_gravity_get_for_matrix(matrix);
	Gtk$Pango$Gravity_t *_result = new(Gtk$Pango$Gravity_t);
	_result->Type = Gtk$Pango$Gravity$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GravityGetForScript, 3) {
	PangoScript script = ((Std$Integer_smallt *)Args[0].Val)->Value;
	PangoGravity base_gravity = ((Std$Integer_smallt *)Args[1].Val)->Value;
	PangoGravityHint hint = ((Std$Integer_smallt *)Args[2].Val)->Value;
	PangoGravity result = pango_gravity_get_for_script(script, base_gravity, hint);
	Gtk$Pango$Gravity_t *_result = new(Gtk$Pango$Gravity_t);
	_result->Type = Gtk$Pango$Gravity$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GravityToRotation, 1) {
	PangoGravity gravity = ((Std$Integer_smallt *)Args[0].Val)->Value;
	double result = pango_gravity_to_rotation(gravity);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(IsZeroWidth, 1) {
	gunichar ch = 0;
	int result = pango_is_zero_width(ch);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ItemizeWithBaseDir, 7) {
	PangoContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoDirection base_dir = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *text = Std$String$flatten(Args[2].Val);
	int start_index = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int length = ((Std$Integer_smallt *)Args[4].Val)->Value;
	PangoAttrList * attrs= ((Gtk$Pango$AttrList_t *)Args[5].Val)->Value;
	PangoAttrIterator * cached_iter= ((Gtk$Pango$AttrIterator_t *)Args[6].Val)->Value;
	GList* result = pango_itemize_with_base_dir(context, base_dir, text, start_index, length, attrs, cached_iter);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(ParseEnum, 5) {
	GType type;
	char *str = Std$String$flatten(Args[1].Val);
	int* value = 0;
	int warn = Args[3].Val == $true;
	const char * const * possible_values;
	int result = pango_parse_enum(type, str, value, warn, possible_values);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ParseMarkup, 7) {
	char *markup_text = Std$String$flatten(Args[0].Val);
	int length = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gunichar accel_marker = 0;
	PangoAttrList** attr_list = 0;
	const char * const * text;
	gunichar* accel_char = 0;
	GError** error = 0;
	int result = pango_parse_markup(markup_text, length, accel_marker, attr_list, text, accel_char, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ParseStretch, 3) {
	char *str = Std$String$flatten(Args[0].Val);
	PangoStretch* stretch = 0;
	int warn = Args[2].Val == $true;
	int result = pango_parse_stretch(str, stretch, warn);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ParseStyle, 3) {
	char *str = Std$String$flatten(Args[0].Val);
	PangoStyle* style = 0;
	int warn = Args[2].Val == $true;
	int result = pango_parse_style(str, style, warn);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ParseVariant, 3) {
	char *str = Std$String$flatten(Args[0].Val);
	PangoVariant* variant = 0;
	int warn = Args[2].Val == $true;
	int result = pango_parse_variant(str, variant, warn);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ParseWeight, 3) {
	char *str = Std$String$flatten(Args[0].Val);
	PangoWeight* weight = 0;
	int warn = Args[2].Val == $true;
	int result = pango_parse_weight(str, weight, warn);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(QuantizeLineGeometry, 2) {
	int* thickness = 0;
	int* position = 0;
	pango_quantize_line_geometry(thickness, position);
	return SUCCESS;
};

GLOBAL_FUNCTION(ReadLine, 2) {
	FILE* stream = 0;
	GString* str = 0;
	int result = pango_read_line(stream, str);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ReorderItems, 1) {
	GList* logical_items = 0;
	GList* result = pango_reorder_items(logical_items);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(ScanInt, 2) {
	const char** pos = 0;
	int* out = 0;
	int result = pango_scan_int(pos, out);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ScanString, 2) {
	const char** pos = 0;
	GString* out = 0;
	int result = pango_scan_string(pos, out);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ScanWord, 2) {
	const char** pos = 0;
	GString* out = 0;
	int result = pango_scan_word(pos, out);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ScriptForUnichar, 1) {
	gunichar ch = 0;
	PangoScript result = pango_script_for_unichar(ch);
	Gtk$Pango$Script_t *_result = new(Gtk$Pango$Script_t);
	_result->Type = Gtk$Pango$Script$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

GLOBAL_FUNCTION(ScriptGetSampleLanguage, 1) {
	PangoScript script = ((Std$Integer_smallt *)Args[0].Val)->Value;
	PangoLanguage * result = pango_script_get_sample_language(script);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(SkipSpace, 1) {
	const char** pos = 0;
	int result = pango_skip_space(pos);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(SplitFileList, 1) {
	char *str = Std$String$flatten(Args[0].Val);
	const char * const * result = pango_split_file_list(str);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(TrimString, 1) {
	char *str = Std$String$flatten(Args[0].Val);
	char * result = pango_trim_string(str);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(UnicharDirection, 1) {
	gunichar ch = 0;
	PangoDirection result = pango_unichar_direction(ch);
	Gtk$Pango$Direction_t *_result = new(Gtk$Pango$Direction_t);
	_result->Type = Gtk$Pango$Direction$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

