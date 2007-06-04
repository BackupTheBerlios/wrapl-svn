#include <Gtk/Pango/FontFamily.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/FontFamily.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_font_family_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetName", TYP, T) {
	PangoFontFamily * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = pango_font_family_get_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("IsMonospace", TYP, T) {
	PangoFontFamily * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = pango_font_family_is_monospace(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ListFaces", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoFontFamily * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontFace*** faces = 0;
	int* n_faces = 0;
	pango_font_family_list_faces(self, faces, n_faces);
	return SUCCESS;
};

