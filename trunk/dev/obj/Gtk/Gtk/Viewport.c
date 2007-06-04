#include <Gtk/Gtk/Viewport.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/ShadowType.h>
#include <Gtk/Gtk/Adjustment.h>
#include <Gtk/Gtk/Viewport.h>
/***********************************/
TYPE(T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 2) {
	GtkAdjustment * hadjustment = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * vadjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkViewport * result = gtk_viewport_new(hadjustment, vadjustment);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_viewport_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetHadjustment", TYP, T) {
	GtkViewport * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * result = gtk_viewport_get_hadjustment(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetShadowType", TYP, T) {
	GtkViewport * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkShadowType result = gtk_viewport_get_shadow_type(self);
	Gtk$Gtk$ShadowType_t *_result = new(Gtk$Gtk$ShadowType_t);
	_result->Type = Gtk$Gtk$ShadowType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetVadjustment", TYP, T) {
	GtkViewport * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * result = gtk_viewport_get_vadjustment(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("SetHadjustment", TYP, T, TYP, Gtk$Gtk$Adjustment$T) {
	GtkViewport * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_viewport_set_hadjustment(self, adjustment);
	return SUCCESS;
};

METHOD("SetShadowType", TYP, T, TYP, Gtk$Gtk$ShadowType$T) {
	GtkViewport * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkShadowType type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_viewport_set_shadow_type(self, type);
	return SUCCESS;
};

METHOD("SetVadjustment", TYP, T, TYP, Gtk$Gtk$Adjustment$T) {
	GtkViewport * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_viewport_set_vadjustment(self, adjustment);
	return SUCCESS;
};

