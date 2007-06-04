#include <Gtk/Gtk/Button.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/Gtk/PositionType.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Button.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/ReliefStyle.h>
/***********************************/
TYPE(T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkButton * result = gtk_button_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromStock, 1) {
	char *stock_id = Std$String$flatten(Args[0].Val);
	GtkButton * result = gtk_button_new_from_stock(stock_id);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithLabel, 1) {
	char *label = Std$String$flatten(Args[0].Val);
	GtkButton * result = gtk_button_new_with_label(label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithMnemonic, 1) {
	char *label = Std$String$flatten(Args[0].Val);
	GtkButton * result = gtk_button_new_with_mnemonic(label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_button_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Clicked", TYP, T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_button_clicked(self);
	return SUCCESS;
};

METHOD("Enter", TYP, T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_button_enter(self);
	return SUCCESS;
};

METHOD("GetAlignment", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gfloat* xalign = 0;
	gfloat* yalign = 0;
	gtk_button_get_alignment(self, xalign, yalign);
	return SUCCESS;
};

METHOD("GetFocusOnClick", TYP, T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_button_get_focus_on_click(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetImage", TYP, T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_button_get_image(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetImagePosition", TYP, T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPositionType result = gtk_button_get_image_position(self);
	Gtk$Gtk$PositionType_t *_result = new(Gtk$Gtk$PositionType_t);
	_result->Type = Gtk$Gtk$PositionType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetLabel", TYP, T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_button_get_label(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetRelief", TYP, T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkReliefStyle result = gtk_button_get_relief(self);
	Gtk$Gtk$ReliefStyle_t *_result = new(Gtk$Gtk$ReliefStyle_t);
	_result->Type = Gtk$Gtk$ReliefStyle$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetUseStock", TYP, T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_button_get_use_stock(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetUseUnderline", TYP, T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_button_get_use_underline(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Leave", TYP, T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_button_leave(self);
	return SUCCESS;
};

METHOD("Pressed", TYP, T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_button_pressed(self);
	return SUCCESS;
};

METHOD("Released", TYP, T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_button_released(self);
	return SUCCESS;
};

METHOD("SetAlignment", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double xalign = ((Std$Real_t *)Args[1].Val)->Value;
	double yalign = ((Std$Real_t *)Args[2].Val)->Value;
	gtk_button_set_alignment(self, xalign, yalign);
	return SUCCESS;
};

METHOD("SetFocusOnClick", TYP, T, TYP, Std$Symbol$T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int focus_on_click = Args[1].Val == $true;
	gtk_button_set_focus_on_click(self, focus_on_click);
	return SUCCESS;
};

METHOD("SetImage", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * image = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_button_set_image(self, image);
	return SUCCESS;
};

METHOD("SetImagePosition", TYP, T, TYP, Gtk$Gtk$PositionType$T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPositionType position = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_button_set_image_position(self, position);
	return SUCCESS;
};

METHOD("SetLabel", TYP, T, TYP, Std$String$T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *label = Std$String$flatten(Args[1].Val);
	gtk_button_set_label(self, label);
	return SUCCESS;
};

METHOD("SetRelief", TYP, T, TYP, Gtk$Gtk$ReliefStyle$T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkReliefStyle newstyle = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_button_set_relief(self, newstyle);
	return SUCCESS;
};

METHOD("SetUseStock", TYP, T, TYP, Std$Symbol$T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int use_stock = Args[1].Val == $true;
	gtk_button_set_use_stock(self, use_stock);
	return SUCCESS;
};

METHOD("SetUseUnderline", TYP, T, TYP, Std$Symbol$T) {
	GtkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int use_underline = Args[1].Val == $true;
	gtk_button_set_use_underline(self, use_underline);
	return SUCCESS;
};

