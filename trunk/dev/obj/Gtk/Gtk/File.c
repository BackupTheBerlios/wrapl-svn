#include <Gtk/Gtk/File.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 1
#include <Gtk/GObject/Object.h>
/***********************************/
GLOBAL_FUNCTION(PathsCopy, 1) {
	GSList* paths = 0;
	GSList* result = gtk_file_paths_copy(paths);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(PathsFree, 1) {
	GSList* paths = 0;
	gtk_file_paths_free(paths);
	return SUCCESS;
};

GLOBAL_FUNCTION(PathsSort, 1) {
	GSList* paths = 0;
	GSList* result = gtk_file_paths_sort(paths);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

