#include <Gtk/Pango/Fontset.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/Pango/FontsetForeachFunc.h>
#include <Gtk/Pango/Font.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/Fontset.h>
#include <Gtk/Pango/FontMetrics.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_fontset_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Foreach", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	PangoFontset * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontsetForeachFunc func = Gtk$Pango$FontsetForeachFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	pango_fontset_foreach(self, func, data);
	return SUCCESS;
};

METHOD("GetFont", TYP, T, TYP, Std$Integer$SmallT) {
	PangoFontset * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int wc = ((Std$Integer_smallt *)Args[1].Val)->Value;
	PangoFont * result = pango_fontset_get_font(self, wc);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetMetrics", TYP, T) {
	PangoFontset * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontMetrics * result = pango_fontset_get_metrics(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

