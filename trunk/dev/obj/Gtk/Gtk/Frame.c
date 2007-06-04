#include <Gtk/Gtk/Frame.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/Frame.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/ShadowType.h>
#include <Gtk/Gtk/Widget.h>
/***********************************/
TYPE(T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	char *label = Std$String$flatten(Args[0].Val);
	GtkFrame * result = gtk_frame_new(label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_frame_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetLabel", TYP, T) {
	GtkFrame * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_frame_get_label(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetLabelAlign", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkFrame * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gfloat* xalign = 0;
	gfloat* yalign = 0;
	gtk_frame_get_label_align(self, xalign, yalign);
	return SUCCESS;
};

METHOD("GetLabelWidget", TYP, T) {
	GtkFrame * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_frame_get_label_widget(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetShadowType", TYP, T) {
	GtkFrame * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkShadowType result = gtk_frame_get_shadow_type(self);
	Gtk$Gtk$ShadowType_t *_result = new(Gtk$Gtk$ShadowType_t);
	_result->Type = Gtk$Gtk$ShadowType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("SetLabel", TYP, T, TYP, Std$String$T) {
	GtkFrame * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *label = Std$String$flatten(Args[1].Val);
	gtk_frame_set_label(self, label);
	return SUCCESS;
};

METHOD("SetLabelAlign", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkFrame * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double xalign = ((Std$Real_t *)Args[1].Val)->Value;
	double yalign = ((Std$Real_t *)Args[2].Val)->Value;
	gtk_frame_set_label_align(self, xalign, yalign);
	return SUCCESS;
};

METHOD("SetLabelWidget", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkFrame * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * label_widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_frame_set_label_widget(self, label_widget);
	return SUCCESS;
};

METHOD("SetShadowType", TYP, T, TYP, Gtk$Gtk$ShadowType$T) {
	GtkFrame * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkShadowType type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_frame_set_shadow_type(self, type);
	return SUCCESS;
};

