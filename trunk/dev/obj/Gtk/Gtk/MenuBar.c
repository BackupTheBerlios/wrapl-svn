#include <Gtk/Gtk/MenuBar.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/Gtk/PackDirection.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/MenuBar.h>
/***********************************/
TYPE(T, Gtk$Gtk$MenuShell$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkMenuBar * result = gtk_menu_bar_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_menu_bar_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetChildPackDirection", TYP, T) {
	GtkMenuBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPackDirection result = gtk_menu_bar_get_child_pack_direction(self);
	Gtk$Gtk$PackDirection_t *_result = new(Gtk$Gtk$PackDirection_t);
	_result->Type = Gtk$Gtk$PackDirection$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetPackDirection", TYP, T) {
	GtkMenuBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPackDirection result = gtk_menu_bar_get_pack_direction(self);
	Gtk$Gtk$PackDirection_t *_result = new(Gtk$Gtk$PackDirection_t);
	_result->Type = Gtk$Gtk$PackDirection$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("SetChildPackDirection", TYP, T, TYP, Gtk$Gtk$PackDirection$T) {
	GtkMenuBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPackDirection child_pack_dir = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_menu_bar_set_child_pack_direction(self, child_pack_dir);
	return SUCCESS;
};

METHOD("SetPackDirection", TYP, T, TYP, Gtk$Gtk$PackDirection$T) {
	GtkMenuBar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPackDirection pack_dir = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_menu_bar_set_pack_direction(self, pack_dir);
	return SUCCESS;
};

