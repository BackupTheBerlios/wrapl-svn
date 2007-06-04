#include <Gtk/Pango/FcFont.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Std/Boolean.h>
#include <Gtk/Pango/FontDescription.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/FcFont.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Pango$Font$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(DescriptionFromPattern, 2) {
	FcPattern* pattern = 0;
	int include_size = Args[1].Val == $true;
	PangoFontDescription * result = pango_fc_font_description_from_pattern(pattern, include_size);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_fc_font_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("LockFace", TYP, T) {
	PangoFcFont * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	FT_Face result = pango_fc_font_lock_face(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("UnlockFace", TYP, T) {
	PangoFcFont * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	pango_fc_font_unlock_face(self);
	return SUCCESS;
};

