#include <Gtk/Gtk/BindingSet.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/PathType.h>
#include <Gtk/Gtk/PathPriorityType.h>
#include <Gtk/Gtk/BindingSet.h>
#include <Gtk/Gtk/Object.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 1) {
	char *set_name = Std$String$flatten(Args[0].Val);
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gtk_binding_set_new(set_name);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(ByClass, 1) {
	void *object_class = ((Std$Address_t *)Args[0].Val)->Value;
	GtkBindingSet * result = gtk_binding_set_by_class(object_class);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(Find, 1) {
	char *set_name = Std$String$flatten(Args[0].Val);
	GtkBindingSet * result = gtk_binding_set_find(set_name);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Activate", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$Object$T) {
	GtkBindingSet * self= ((Gtk$Gtk$BindingSet_t *)Args[0].Val)->Value;
	int keyval = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int modifiers = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkObject * object = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	int result = gtk_binding_set_activate(self, keyval, modifiers, object);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("AddPath", TYP, T, TYP, Gtk$Gtk$PathType$T, TYP, Std$String$T, TYP, Gtk$Gtk$PathPriorityType$T) {
	GtkBindingSet * self= ((Gtk$Gtk$BindingSet_t *)Args[0].Val)->Value;
	GtkPathType path_type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *path_pattern = Std$String$flatten(Args[2].Val);
	GtkPathPriorityType priority = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_binding_set_add_path(self, path_type, path_pattern, priority);
	return SUCCESS;
};

