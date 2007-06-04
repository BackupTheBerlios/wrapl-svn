#include <Gtk/Gtk/TreeIter.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TreeIter.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tree_iter_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GtkTreeIter * self= &((Gtk$Gtk$TreeIter_t *)Args[0].Val)->Value;
	GtkTreeIter * result = gtk_tree_iter_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	GtkTreeIter * self= &((Gtk$Gtk$TreeIter_t *)Args[0].Val)->Value;
	gtk_tree_iter_free(self);
	return SUCCESS;
};

