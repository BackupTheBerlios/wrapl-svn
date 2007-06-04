#include <Gtk/Gtk/Expander.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Expander.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	char *label = Std$String$flatten(Args[0].Val);
	GtkExpander * result = gtk_expander_new(label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithMnemonic, 1) {
	char *label = Std$String$flatten(Args[0].Val);
	GtkExpander * result = gtk_expander_new_with_mnemonic(label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_expander_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetExpanded", TYP, T) {
	GtkExpander * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_expander_get_expanded(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetLabel", TYP, T) {
	GtkExpander * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_expander_get_label(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetLabelWidget", TYP, T) {
	GtkExpander * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_expander_get_label_widget(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetSpacing", TYP, T) {
	GtkExpander * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_expander_get_spacing(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetUseMarkup", TYP, T) {
	GtkExpander * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_expander_get_use_markup(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetUseUnderline", TYP, T) {
	GtkExpander * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_expander_get_use_underline(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetExpanded", TYP, T, TYP, Std$Symbol$T) {
	GtkExpander * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int expanded = Args[1].Val == $true;
	gtk_expander_set_expanded(self, expanded);
	return SUCCESS;
};

METHOD("SetLabel", TYP, T, TYP, Std$String$T) {
	GtkExpander * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *label = Std$String$flatten(Args[1].Val);
	gtk_expander_set_label(self, label);
	return SUCCESS;
};

METHOD("SetLabelWidget", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkExpander * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * label_widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_expander_set_label_widget(self, label_widget);
	return SUCCESS;
};

METHOD("SetSpacing", TYP, T, TYP, Std$Integer$SmallT) {
	GtkExpander * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int spacing = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_expander_set_spacing(self, spacing);
	return SUCCESS;
};

METHOD("SetUseMarkup", TYP, T, TYP, Std$Symbol$T) {
	GtkExpander * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int use_markup = Args[1].Val == $true;
	gtk_expander_set_use_markup(self, use_markup);
	return SUCCESS;
};

METHOD("SetUseUnderline", TYP, T, TYP, Std$Symbol$T) {
	GtkExpander * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int use_underline = Args[1].Val == $true;
	gtk_expander_set_use_underline(self, use_underline);
	return SUCCESS;
};

