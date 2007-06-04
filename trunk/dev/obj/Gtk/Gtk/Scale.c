#include <Gtk/Gtk/Scale.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/Gtk/PositionType.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Layout.h>
#include <Gtk/Gtk/Scale.h>
#include <Gtk/GObject/Type.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Range$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_scale_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetDigits", TYP, T) {
	GtkScale * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_scale_get_digits(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetDrawValue", TYP, T) {
	GtkScale * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_scale_get_draw_value(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetLayout", TYP, T) {
	GtkScale * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoLayout * result = gtk_scale_get_layout(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetLayoutOffsets", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkScale * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* x = 0;
	gint* y = 0;
	gtk_scale_get_layout_offsets(self, x, y);
	return SUCCESS;
};

METHOD("GetValuePos", TYP, T) {
	GtkScale * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPositionType result = gtk_scale_get_value_pos(self);
	Gtk$Gtk$PositionType_t *_result = new(Gtk$Gtk$PositionType_t);
	_result->Type = Gtk$Gtk$PositionType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("SetDigits", TYP, T, TYP, Std$Integer$SmallT) {
	GtkScale * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int digits = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_scale_set_digits(self, digits);
	return SUCCESS;
};

METHOD("SetDrawValue", TYP, T, TYP, Std$Symbol$T) {
	GtkScale * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int draw_value = Args[1].Val == $true;
	gtk_scale_set_draw_value(self, draw_value);
	return SUCCESS;
};

METHOD("SetValuePos", TYP, T, TYP, Gtk$Gtk$PositionType$T) {
	GtkScale * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPositionType pos = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_scale_set_value_pos(self, pos);
	return SUCCESS;
};

