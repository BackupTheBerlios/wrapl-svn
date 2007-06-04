#include <Gtk/Gtk/HScrollbar.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Adjustment.h>
/***********************************/
TYPE(T, Gtk$Gtk$Scrollbar$T, Gtk$Gtk$Range$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkHScrollbar * result = gtk_hscrollbar_new(adjustment);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_hscrollbar_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

