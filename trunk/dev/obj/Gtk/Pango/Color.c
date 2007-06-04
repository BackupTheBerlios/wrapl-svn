#include <Gtk/Pango/Color.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Std/Boolean.h>
#include <Gtk/Pango/Color.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_color_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	PangoColor * self= &((Gtk$Pango$Color_t *)Args[0].Val)->Value;
	PangoColor * result = pango_color_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	PangoColor * self= &((Gtk$Pango$Color_t *)Args[0].Val)->Value;
	pango_color_free(self);
	return SUCCESS;
};

METHOD("Parse", TYP, T, TYP, Std$String$T) {
	PangoColor * self= &((Gtk$Pango$Color_t *)Args[0].Val)->Value;
	char *spec = Std$String$flatten(Args[1].Val);
	int result = pango_color_parse(self, spec);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ToString", TYP, T) {
	PangoColor * self= &((Gtk$Pango$Color_t *)Args[0].Val)->Value;
	char * result = pango_color_to_string(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

