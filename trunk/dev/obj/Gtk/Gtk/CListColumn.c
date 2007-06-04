#include <Gtk/Gtk/CListColumn.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 2
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/CList.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(TitleActive, 2) {
	GtkCList * clist = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_clist_column_title_active(clist, column);
	return SUCCESS;
};

GLOBAL_FUNCTION(TitlePassive, 2) {
	GtkCList * clist = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_clist_column_title_passive(clist, column);
	return SUCCESS;
};

GLOBAL_FUNCTION(TitlesActive, 1) {
	GtkCList * clist = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_clist_column_titles_active(clist);
	return SUCCESS;
};

GLOBAL_FUNCTION(TitlesHide, 1) {
	GtkCList * clist = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_clist_column_titles_hide(clist);
	return SUCCESS;
};

GLOBAL_FUNCTION(TitlesPassive, 1) {
	GtkCList * clist = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_clist_column_titles_passive(clist);
	return SUCCESS;
};

GLOBAL_FUNCTION(TitlesShow, 1) {
	GtkCList * clist = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_clist_column_titles_show(clist);
	return SUCCESS;
};

