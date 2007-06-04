#include <Gtk/Gtk/HButtonBox.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gtk/ButtonBoxStyle.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$ButtonBox$T, Gtk$Gtk$Box$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkHButtonBox * result = gtk_hbutton_box_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetLayoutDefault, 0) {
	GtkButtonBoxStyle result = gtk_hbutton_box_get_layout_default();
	Gtk$Gtk$ButtonBoxStyle_t *_result = new(Gtk$Gtk$ButtonBoxStyle_t);
	_result->Type = Gtk$Gtk$ButtonBoxStyle$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetSpacingDefault, 0) {
	int result = gtk_hbutton_box_get_spacing_default();
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_hbutton_box_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetLayoutDefault, 1) {
	GtkButtonBoxStyle layout = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gtk_hbutton_box_set_layout_default(layout);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetSpacingDefault, 1) {
	int spacing = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gtk_hbutton_box_set_spacing_default(spacing);
	return SUCCESS;
};

