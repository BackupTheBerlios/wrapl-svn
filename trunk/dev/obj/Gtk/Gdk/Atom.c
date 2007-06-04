#include <Gtk/Gdk/Atom.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Std/Boolean.h>
#include <Gtk/Gdk/Atom.h>
#include <Gtk/GObject/Object.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(Intern, 2) {
	char *atom_name = Std$String$flatten(Args[0].Val);
	int only_if_exists = Args[1].Val == $true;
	GdkAtom result = gdk_atom_intern(atom_name, only_if_exists);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(InternStaticString, 1) {
	char *atom_name = Std$String$flatten(Args[0].Val);
	GdkAtom result = gdk_atom_intern_static_string(atom_name);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Name", TYP, T) {
	GdkAtom * self= ((Gtk$Gdk$Atom_t *)Args[0].Val)->Value;
	char * result = gdk_atom_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

