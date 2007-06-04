#include <Gtk/Gtk/HandleBox.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/Gtk/PositionType.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/HandleBox.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/ShadowType.h>
/***********************************/
TYPE(T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkHandleBox * result = gtk_handle_box_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_handle_box_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetHandlePosition", TYP, T) {
	GtkHandleBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPositionType result = gtk_handle_box_get_handle_position(self);
	Gtk$Gtk$PositionType_t *_result = new(Gtk$Gtk$PositionType_t);
	_result->Type = Gtk$Gtk$PositionType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetShadowType", TYP, T) {
	GtkHandleBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkShadowType result = gtk_handle_box_get_shadow_type(self);
	Gtk$Gtk$ShadowType_t *_result = new(Gtk$Gtk$ShadowType_t);
	_result->Type = Gtk$Gtk$ShadowType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetSnapEdge", TYP, T) {
	GtkHandleBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPositionType result = gtk_handle_box_get_snap_edge(self);
	Gtk$Gtk$PositionType_t *_result = new(Gtk$Gtk$PositionType_t);
	_result->Type = Gtk$Gtk$PositionType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("SetHandlePosition", TYP, T, TYP, Gtk$Gtk$PositionType$T) {
	GtkHandleBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPositionType position = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_handle_box_set_handle_position(self, position);
	return SUCCESS;
};

METHOD("SetShadowType", TYP, T, TYP, Gtk$Gtk$ShadowType$T) {
	GtkHandleBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkShadowType type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_handle_box_set_shadow_type(self, type);
	return SUCCESS;
};

METHOD("SetSnapEdge", TYP, T, TYP, Gtk$Gtk$PositionType$T) {
	GtkHandleBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPositionType edge = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_handle_box_set_snap_edge(self, edge);
	return SUCCESS;
};

