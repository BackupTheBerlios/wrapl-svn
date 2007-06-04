#include <Gtk/Pango/Context.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 13
#include <Gtk/Pango/FontDescription.h>
#include <Gtk/Pango/Font.h>
#include <Gtk/Pango/Direction.h>
#include <Gtk/Pango/Language.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Matrix.h>
#include <Gtk/Pango/Context.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/FontMap.h>
#include <Gtk/Pango/Fontset.h>
#include <Gtk/Pango/GravityHint.h>
#include <Gtk/Pango/Gravity.h>
#include <Gtk/Pango/FontMetrics.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_context_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetBaseDir", TYP, T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoDirection result = pango_context_get_base_dir(self);
	Gtk$Pango$Direction_t *_result = new(Gtk$Pango$Direction_t);
	_result->Type = Gtk$Pango$Direction$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetBaseGravity", TYP, T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoGravity result = pango_context_get_base_gravity(self);
	Gtk$Pango$Gravity_t *_result = new(Gtk$Pango$Gravity_t);
	_result->Type = Gtk$Pango$Gravity$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetFontDescription", TYP, T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontDescription * result = pango_context_get_font_description(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetFontMap", TYP, T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontMap * result = pango_context_get_font_map(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetGravity", TYP, T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoGravity result = pango_context_get_gravity(self);
	Gtk$Pango$Gravity_t *_result = new(Gtk$Pango$Gravity_t);
	_result->Type = Gtk$Pango$Gravity$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetGravityHint", TYP, T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoGravityHint result = pango_context_get_gravity_hint(self);
	Gtk$Pango$GravityHint_t *_result = new(Gtk$Pango$GravityHint_t);
	_result->Type = Gtk$Pango$GravityHint$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetLanguage", TYP, T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoLanguage * result = pango_context_get_language(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetMatrix", TYP, T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoMatrix * result = pango_context_get_matrix(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetMetrics", TYP, T, TYP, Gtk$Pango$FontDescription$T, TYP, Gtk$Pango$Language$T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontDescription * desc= ((Gtk$Pango$FontDescription_t *)Args[1].Val)->Value;
	PangoLanguage * language= ((Gtk$Pango$Language_t *)Args[2].Val)->Value;
	PangoFontMetrics * result = pango_context_get_metrics(self, desc, language);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("ListFamilies", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontFamily*** families = 0;
	int* n_families = 0;
	pango_context_list_families(self, families, n_families);
	return SUCCESS;
};

METHOD("LoadFont", TYP, T, TYP, Gtk$Pango$FontDescription$T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontDescription * desc= ((Gtk$Pango$FontDescription_t *)Args[1].Val)->Value;
	PangoFont * result = pango_context_load_font(self, desc);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("LoadFontset", TYP, T, TYP, Gtk$Pango$FontDescription$T, TYP, Gtk$Pango$Language$T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontDescription * desc= ((Gtk$Pango$FontDescription_t *)Args[1].Val)->Value;
	PangoLanguage * language= ((Gtk$Pango$Language_t *)Args[2].Val)->Value;
	PangoFontset * result = pango_context_load_fontset(self, desc, language);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("SetBaseDir", TYP, T, TYP, Gtk$Pango$Direction$T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoDirection direction = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_context_set_base_dir(self, direction);
	return SUCCESS;
};

METHOD("SetBaseGravity", TYP, T, TYP, Gtk$Pango$Gravity$T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoGravity gravity = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_context_set_base_gravity(self, gravity);
	return SUCCESS;
};

METHOD("SetFontDescription", TYP, T, TYP, Gtk$Pango$FontDescription$T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontDescription * desc= ((Gtk$Pango$FontDescription_t *)Args[1].Val)->Value;
	pango_context_set_font_description(self, desc);
	return SUCCESS;
};

METHOD("SetGravityHint", TYP, T, TYP, Gtk$Pango$GravityHint$T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoGravityHint hint = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_context_set_gravity_hint(self, hint);
	return SUCCESS;
};

METHOD("SetLanguage", TYP, T, TYP, Gtk$Pango$Language$T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoLanguage * language= ((Gtk$Pango$Language_t *)Args[1].Val)->Value;
	pango_context_set_language(self, language);
	return SUCCESS;
};

METHOD("SetMatrix", TYP, T, TYP, Gtk$Pango$Matrix$T) {
	PangoContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoMatrix * matrix= &((Gtk$Pango$Matrix_t *)Args[1].Val)->Value;
	pango_context_set_matrix(self, matrix);
	return SUCCESS;
};

