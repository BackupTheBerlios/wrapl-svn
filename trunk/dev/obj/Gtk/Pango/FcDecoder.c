#include <Gtk/Pango/FcDecoder.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/FcFont.h>
#include <Gtk/Pango/FcDecoder.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_fc_decoder_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetCharset", TYP, T, TYP, Gtk$Pango$FcFont$T) {
	PangoFcDecoder * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFcFont * fcfont = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	FcCharSet* result = pango_fc_decoder_get_charset(self, fcfont);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetGlyph", TYP, T, TYP, Gtk$Pango$FcFont$T, TYP, Std$Integer$SmallT) {
	PangoFcDecoder * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFcFont * fcfont = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int wc = ((Std$Integer_smallt *)Args[2].Val)->Value;
	PangoGlyph result = pango_fc_decoder_get_glyph(self, fcfont, wc);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

