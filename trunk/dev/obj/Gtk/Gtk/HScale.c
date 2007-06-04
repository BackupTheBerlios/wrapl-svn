#include <Gtk/Gtk/HScale.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Adjustment.h>
/***********************************/
TYPE(T, Gtk$Gtk$Scale$T, Gtk$Gtk$Range$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkHScale * result = gtk_hscale_new(adjustment);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithRange, 3) {
	double min = ((Std$Real_t *)Args[0].Val)->Value;
	double max = ((Std$Real_t *)Args[1].Val)->Value;
	double step = ((Std$Real_t *)Args[2].Val)->Value;
	GtkHScale * result = gtk_hscale_new_with_range(min, max, step);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_hscale_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

