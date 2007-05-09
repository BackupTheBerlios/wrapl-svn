#include <Gtk/Gtk/MenuShell.h>
#include <Gtk/Gtk/MenuItem.h>

TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

METHOD("put", TYP, T, TYP, Gtk$Gtk$MenuItem$T) {
	GtkMenuShell *MenuShell = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget *Child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_menu_shell_append(MenuShell, Child);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("push", TYP, T, TYP, Gtk$Gtk$MenuItem$T) {
	GtkMenuShell *MenuShell = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget *Child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_menu_shell_prepend(MenuShell, Child);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("insert", TYP, T, TYP, Gtk$Gtk$MenuItem$T, TYP, Lang$Integer$SmallT) {
	GtkMenuShell *MenuShell = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget *Child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_menu_shell_insert(MenuShell, Child, ((Lang$Integer_smallt *)Args[2].Val)->Value);
	Result->Arg = Args[0];
	return SUCCESS;
};
