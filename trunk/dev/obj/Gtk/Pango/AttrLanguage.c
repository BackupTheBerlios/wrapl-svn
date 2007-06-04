#include <Gtk/Pango/AttrLanguage.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 2
#include <Gtk/Pango/Language.h>
#include <Gtk/GObject/Object.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 1) {
	PangoLanguage * language= ((Gtk$Pango$Language_t *)Args[0].Val)->Value;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = pango_attr_language_new(language);
	Result->Val= result;
	return SUCCESS;
};

