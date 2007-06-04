#include <Gtk/Gtk/SizeGroup.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Std/Boolean.h>
#include <Gtk/Gtk/SizeGroupMode.h>
#include <Gtk/Gtk/SizeGroup.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	GtkSizeGroupMode mode = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GtkSizeGroup * result = gtk_size_group_new(mode);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_size_group_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddWidget", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkSizeGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_size_group_add_widget(self, widget);
	return SUCCESS;
};

METHOD("GetIgnoreHidden", TYP, T) {
	GtkSizeGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_size_group_get_ignore_hidden(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetMode", TYP, T) {
	GtkSizeGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSizeGroupMode result = gtk_size_group_get_mode(self);
	Gtk$Gtk$SizeGroupMode_t *_result = new(Gtk$Gtk$SizeGroupMode_t);
	_result->Type = Gtk$Gtk$SizeGroupMode$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetWidgets", TYP, T) {
	GtkSizeGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* result = gtk_size_group_get_widgets(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("RemoveWidget", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkSizeGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_size_group_remove_widget(self, widget);
	return SUCCESS;
};

METHOD("SetIgnoreHidden", TYP, T, TYP, Std$Symbol$T) {
	GtkSizeGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int ignore_hidden = Args[1].Val == $true;
	gtk_size_group_set_ignore_hidden(self, ignore_hidden);
	return SUCCESS;
};

METHOD("SetMode", TYP, T, TYP, Gtk$Gtk$SizeGroupMode$T) {
	GtkSizeGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSizeGroupMode mode = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_size_group_set_mode(self, mode);
	return SUCCESS;
};

