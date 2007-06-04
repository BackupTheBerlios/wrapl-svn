#include <Gtk/Pango/FontMap.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 8
#include <Gtk/Pango/FontDescription.h>
#include <Gtk/Pango/Font.h>
#include <Gtk/Pango/Language.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Context.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/FontMap.h>
#include <Gtk/Pango/Fontset.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_font_map_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("ListFamilies", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoFontMap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontFamily*** families = 0;
	int* n_families = 0;
	pango_font_map_list_families(self, families, n_families);
	return SUCCESS;
};

METHOD("LoadFont", TYP, T, TYP, Gtk$Pango$Context$T, TYP, Gtk$Pango$FontDescription$T) {
	PangoFontMap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoContext * context = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	PangoFontDescription * desc= ((Gtk$Pango$FontDescription_t *)Args[2].Val)->Value;
	PangoFont * result = pango_font_map_load_font(self, context, desc);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("LoadFontset", TYP, T, TYP, Gtk$Pango$Context$T, TYP, Gtk$Pango$FontDescription$T, TYP, Gtk$Pango$Language$T) {
	PangoFontMap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoContext * context = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	PangoFontDescription * desc= ((Gtk$Pango$FontDescription_t *)Args[2].Val)->Value;
	PangoLanguage * language= ((Gtk$Pango$Language_t *)Args[3].Val)->Value;
	PangoFontset * result = pango_font_map_load_fontset(self, context, desc, language);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

