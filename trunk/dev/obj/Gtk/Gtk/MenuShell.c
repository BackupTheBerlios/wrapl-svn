#include <Gtk/Gtk/MenuShell.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/MenuShell.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_menu_shell_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("ActivateItem", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Symbol$T) {
	GtkMenuShell * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * menu_item = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int force_deactivate = Args[2].Val == $true;
	gtk_menu_shell_activate_item(self, menu_item, force_deactivate);
	return SUCCESS;
};

METHOD("Append", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkMenuShell * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_menu_shell_append(self, child);
	return SUCCESS;
};

METHOD("Cancel", TYP, T) {
	GtkMenuShell * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_menu_shell_cancel(self);
	return SUCCESS;
};

METHOD("Deactivate", TYP, T) {
	GtkMenuShell * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_menu_shell_deactivate(self);
	return SUCCESS;
};

METHOD("Deselect", TYP, T) {
	GtkMenuShell * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_menu_shell_deselect(self);
	return SUCCESS;
};

METHOD("GetTakeFocus", TYP, T) {
	GtkMenuShell * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_menu_shell_get_take_focus(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Insert", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT) {
	GtkMenuShell * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_menu_shell_insert(self, child, position);
	return SUCCESS;
};

METHOD("Prepend", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkMenuShell * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_menu_shell_prepend(self, child);
	return SUCCESS;
};

METHOD("SelectFirst", TYP, T, TYP, Std$Symbol$T) {
	GtkMenuShell * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int search_sensitive = Args[1].Val == $true;
	gtk_menu_shell_select_first(self, search_sensitive);
	return SUCCESS;
};

METHOD("SelectItem", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkMenuShell * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * menu_item = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_menu_shell_select_item(self, menu_item);
	return SUCCESS;
};

METHOD("SetTakeFocus", TYP, T, TYP, Std$Symbol$T) {
	GtkMenuShell * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int take_focus = Args[1].Val == $true;
	gtk_menu_shell_set_take_focus(self, take_focus);
	return SUCCESS;
};

