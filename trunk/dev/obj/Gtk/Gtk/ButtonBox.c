#include <Gtk/Gtk/ButtonBox.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
#include <Gtk/Gtk/ButtonBox.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/ButtonBoxStyle.h>
/***********************************/
TYPE(T, Gtk$Gtk$Box$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_button_box_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetChildIpadding", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkButtonBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* ipad_x = 0;
	gint* ipad_y = 0;
	gtk_button_box_get_child_ipadding(self, ipad_x, ipad_y);
	return SUCCESS;
};

METHOD("GetChildSecondary", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkButtonBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_button_box_get_child_secondary(self, child);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetChildSize", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkButtonBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* min_width = 0;
	gint* min_height = 0;
	gtk_button_box_get_child_size(self, min_width, min_height);
	return SUCCESS;
};

METHOD("GetLayout", TYP, T) {
	GtkButtonBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkButtonBoxStyle result = gtk_button_box_get_layout(self);
	Gtk$Gtk$ButtonBoxStyle_t *_result = new(Gtk$Gtk$ButtonBoxStyle_t);
	_result->Type = Gtk$Gtk$ButtonBoxStyle$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("SetChildIpadding", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkButtonBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int ipad_x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int ipad_y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_button_box_set_child_ipadding(self, ipad_x, ipad_y);
	return SUCCESS;
};

METHOD("SetChildSecondary", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Symbol$T) {
	GtkButtonBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int is_secondary = Args[2].Val == $true;
	gtk_button_box_set_child_secondary(self, child, is_secondary);
	return SUCCESS;
};

METHOD("SetChildSize", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkButtonBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int min_width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int min_height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_button_box_set_child_size(self, min_width, min_height);
	return SUCCESS;
};

METHOD("SetLayout", TYP, T, TYP, Gtk$Gtk$ButtonBoxStyle$T) {
	GtkButtonBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkButtonBoxStyle layout_style = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_button_box_set_layout(self, layout_style);
	return SUCCESS;
};

