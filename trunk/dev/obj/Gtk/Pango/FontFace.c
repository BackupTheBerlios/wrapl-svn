#include <Gtk/Pango/FontFace.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/Pango/FontFace.h>
#include <Gtk/Pango/FontDescription.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_font_face_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Describe", TYP, T) {
	PangoFontFace * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontDescription * result = pango_font_face_describe(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetFaceName", TYP, T) {
	PangoFontFace * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = pango_font_face_get_face_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("ListSizes", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoFontFace * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int** sizes = 0;
	int* n_sizes = 0;
	pango_font_face_list_sizes(self, sizes, n_sizes);
	return SUCCESS;
};

