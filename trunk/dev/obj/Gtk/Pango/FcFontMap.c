#include <Gtk/Pango/FcFontMap.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/Pango/FcDecoderFindFunc.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/FcFontMap.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Pango$FontMap$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_fc_font_map_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddDecoderFindFunc", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Object$T) {
	PangoFcFontMap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFcDecoderFindFunc findfunc = Gtk$Pango$FcDecoderFindFunc$new(Args[1].Val);
	void *user_data = ((Std$Address_t *)Args[2].Val)->Value;
	GDestroyNotify dnotify = 0;
	pango_fc_font_map_add_decoder_find_func(self, findfunc, user_data, dnotify);
	return SUCCESS;
};

