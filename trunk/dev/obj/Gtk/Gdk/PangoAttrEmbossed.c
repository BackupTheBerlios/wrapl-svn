#include <Gtk/Gdk/PangoAttrEmbossed.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 2
#include <Std/Boolean.h>
#include <Gtk/GObject/Object.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 1) {
	int embossed = Args[0].Val == $true;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gdk_pango_attr_embossed_new(embossed);
	Result->Val= result;
	return SUCCESS;
};

