#include <Gtk/Gtk/CellRendererToggle.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/CellRendererToggle.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$CellRenderer$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkCellRendererToggle * result = gtk_cell_renderer_toggle_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_cell_renderer_toggle_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetActive", TYP, T) {
	GtkCellRendererToggle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_cell_renderer_toggle_get_active(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetRadio", TYP, T) {
	GtkCellRendererToggle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_cell_renderer_toggle_get_radio(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetActive", TYP, T, TYP, Std$Symbol$T) {
	GtkCellRendererToggle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_cell_renderer_toggle_set_active(self, setting);
	return SUCCESS;
};

METHOD("SetRadio", TYP, T, TYP, Std$Symbol$T) {
	GtkCellRendererToggle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int radio = Args[1].Val == $true;
	gtk_cell_renderer_toggle_set_radio(self, radio);
	return SUCCESS;
};

