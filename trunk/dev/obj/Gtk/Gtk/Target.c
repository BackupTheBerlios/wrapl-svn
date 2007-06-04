#include <Gtk/Gtk/Target.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gtk/TargetEntry.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TargetList.h>
/***********************************/
GLOBAL_FUNCTION(TableFree, 2) {
	GtkTargetEntry * targets= &((Gtk$Gtk$TargetEntry_t *)Args[0].Val)->Value;
	int n_targets = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_target_table_free(targets, n_targets);
	return SUCCESS;
};

GLOBAL_FUNCTION(TableNewFromList, 2) {
	GtkTargetList * list= ((Gtk$Gtk$TargetList_t *)Args[0].Val)->Value;
	gint* n_targets = 0;
	GtkTargetEntry * result = gtk_target_table_new_from_list(list, n_targets);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

