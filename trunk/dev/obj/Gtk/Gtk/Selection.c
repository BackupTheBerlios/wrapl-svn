#include <Gtk/Gtk/Selection.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/TargetEntry.h>
#include <Gtk/Gdk/EventSelection.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/Widget.h>
/***********************************/
GLOBAL_FUNCTION(AddTarget, 4) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom selection = 0;
	GdkAtom target = 0;
	int info = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_selection_add_target(widget, selection, target, info);
	return SUCCESS;
};

GLOBAL_FUNCTION(AddTargets, 4) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom selection = 0;
	GtkTargetEntry * targets= &((Gtk$Gtk$TargetEntry_t *)Args[2].Val)->Value;
	int ntargets = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_selection_add_targets(widget, selection, targets, ntargets);
	return SUCCESS;
};

GLOBAL_FUNCTION(Clear, 2) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkEventSelection * event= &((Gtk$Gdk$EventSelection_t *)Args[1].Val)->Value;
	int result = gtk_selection_clear(widget, event);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ClearTargets, 2) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom selection = 0;
	gtk_selection_clear_targets(widget, selection);
	return SUCCESS;
};

GLOBAL_FUNCTION(Convert, 4) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom selection = 0;
	GdkAtom target = 0;
	int time_ = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int result = gtk_selection_convert(widget, selection, target, time_);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(OwnerSet, 3) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom selection = 0;
	int time_ = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gtk_selection_owner_set(widget, selection, time_);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(OwnerSetForDisplay, 4) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkAtom selection = 0;
	int time_ = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int result = gtk_selection_owner_set_for_display(display, widget, selection, time_);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(RemoveAll, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_selection_remove_all(widget);
	return SUCCESS;
};

