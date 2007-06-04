#include <Gtk/Gtk/ScrolledWindow.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 8
#include <Gtk/Gtk/CornerType.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/ScrolledWindow.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/ShadowType.h>
#include <Gtk/Gtk/Adjustment.h>
#include <Gtk/Gtk/Widget.h>
#include <Gtk/Gtk/PolicyType.h>
/***********************************/
TYPE(T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 2) {
	GtkAdjustment * hadjustment = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * vadjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkScrolledWindow * result = gtk_scrolled_window_new(hadjustment, vadjustment);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_scrolled_window_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddWithViewport", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkScrolledWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_scrolled_window_add_with_viewport(self, child);
	return SUCCESS;
};

METHOD("GetHadjustment", TYP, T) {
	GtkScrolledWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * result = gtk_scrolled_window_get_hadjustment(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetHscrollbar", TYP, T) {
	GtkScrolledWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_scrolled_window_get_hscrollbar(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPlacement", TYP, T) {
	GtkScrolledWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCornerType result = gtk_scrolled_window_get_placement(self);
	Gtk$Gtk$CornerType_t *_result = new(Gtk$Gtk$CornerType_t);
	_result->Type = Gtk$Gtk$CornerType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetPolicy", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkScrolledWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPolicyType* hscrollbar_policy = 0;
	GtkPolicyType* vscrollbar_policy = 0;
	gtk_scrolled_window_get_policy(self, hscrollbar_policy, vscrollbar_policy);
	return SUCCESS;
};

METHOD("GetShadowType", TYP, T) {
	GtkScrolledWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkShadowType result = gtk_scrolled_window_get_shadow_type(self);
	Gtk$Gtk$ShadowType_t *_result = new(Gtk$Gtk$ShadowType_t);
	_result->Type = Gtk$Gtk$ShadowType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetVadjustment", TYP, T) {
	GtkScrolledWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * result = gtk_scrolled_window_get_vadjustment(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetVscrollbar", TYP, T) {
	GtkScrolledWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_scrolled_window_get_vscrollbar(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("SetHadjustment", TYP, T, TYP, Gtk$Gtk$Adjustment$T) {
	GtkScrolledWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * hadjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_scrolled_window_set_hadjustment(self, hadjustment);
	return SUCCESS;
};

METHOD("SetPlacement", TYP, T, TYP, Gtk$Gtk$CornerType$T) {
	GtkScrolledWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCornerType window_placement = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_scrolled_window_set_placement(self, window_placement);
	return SUCCESS;
};

METHOD("SetPolicy", TYP, T, TYP, Gtk$Gtk$PolicyType$T, TYP, Gtk$Gtk$PolicyType$T) {
	GtkScrolledWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPolicyType hscrollbar_policy = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkPolicyType vscrollbar_policy = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_scrolled_window_set_policy(self, hscrollbar_policy, vscrollbar_policy);
	return SUCCESS;
};

METHOD("SetShadowType", TYP, T, TYP, Gtk$Gtk$ShadowType$T) {
	GtkScrolledWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkShadowType type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_scrolled_window_set_shadow_type(self, type);
	return SUCCESS;
};

METHOD("SetVadjustment", TYP, T, TYP, Gtk$Gtk$Adjustment$T) {
	GtkScrolledWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * vadjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_scrolled_window_set_vadjustment(self, vadjustment);
	return SUCCESS;
};

METHOD("UnsetPlacement", TYP, T) {
	GtkScrolledWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_scrolled_window_unset_placement(self);
	return SUCCESS;
};

