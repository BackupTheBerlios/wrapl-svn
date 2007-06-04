#include <Gtk/Gtk/CListRow.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gtk/Visibility.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/CList.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(IsVisible, 2) {
	GtkCList * clist = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkVisibility result = gtk_clist_row_is_visible(clist, row);
	Gtk$Gtk$Visibility_t *_result = new(Gtk$Gtk$Visibility_t);
	_result->Type = Gtk$Gtk$Visibility$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

GLOBAL_FUNCTION(Move, 3) {
	GtkCList * clist = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int source_row = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int dest_row = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_clist_row_move(clist, source_row, dest_row);
	return SUCCESS;
};

