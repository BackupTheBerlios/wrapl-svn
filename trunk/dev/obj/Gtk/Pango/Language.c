#include <Gtk/Pango/Language.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Std/Boolean.h>
#include <Gtk/Pango/Language.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Script.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(FromString, 1) {
	char *language = Std$String$flatten(Args[0].Val);
	PangoLanguage * result = pango_language_from_string(language);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetDefault, 0) {
	PangoLanguage * result = pango_language_get_default();
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_language_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetSampleString", TYP, T) {
	PangoLanguage * self= ((Gtk$Pango$Language_t *)Args[0].Val)->Value;
	const char * result = pango_language_get_sample_string(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("IncludesScript", TYP, T, TYP, Gtk$Pango$Script$T) {
	PangoLanguage * self= ((Gtk$Pango$Language_t *)Args[0].Val)->Value;
	PangoScript script = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = pango_language_includes_script(self, script);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Matches", TYP, T, TYP, Std$String$T) {
	PangoLanguage * self= ((Gtk$Pango$Language_t *)Args[0].Val)->Value;
	char *range_list = Std$String$flatten(Args[1].Val);
	int result = pango_language_matches(self, range_list);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

