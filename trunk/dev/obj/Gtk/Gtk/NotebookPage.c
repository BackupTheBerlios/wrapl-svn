#include <Gtk/Gtk/NotebookPage.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gtk/Notebook.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/Widget.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(Num, 2) {
	GtkNotebook * notebook = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_notebook_page_num(notebook, child);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

