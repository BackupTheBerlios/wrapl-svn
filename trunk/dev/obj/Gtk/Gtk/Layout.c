#include <Gtk/Gtk/Layout.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Adjustment.h>
#include <Gtk/Gtk/Widget.h>
#include <Gtk/Gtk/Layout.h>
/***********************************/
TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 2) {
	GtkAdjustment * hadjustment = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * vadjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkLayout * result = gtk_layout_new(hadjustment, vadjustment);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_layout_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Freeze", TYP, T) {
	GtkLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_layout_freeze(self);
	return SUCCESS;
};

METHOD("GetHadjustment", TYP, T) {
	GtkLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * result = gtk_layout_get_hadjustment(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetSize", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	guint* width = 0;
	guint* height = 0;
	gtk_layout_get_size(self, width, height);
	return SUCCESS;
};

METHOD("GetVadjustment", TYP, T) {
	GtkLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * result = gtk_layout_get_vadjustment(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Move", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child_widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_layout_move(self, child_widget, x, y);
	return SUCCESS;
};

METHOD("Put", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child_widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_layout_put(self, child_widget, x, y);
	return SUCCESS;
};

METHOD("SetHadjustment", TYP, T, TYP, Gtk$Gtk$Adjustment$T) {
	GtkLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_layout_set_hadjustment(self, adjustment);
	return SUCCESS;
};

METHOD("SetSize", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_layout_set_size(self, width, height);
	return SUCCESS;
};

METHOD("SetVadjustment", TYP, T, TYP, Gtk$Gtk$Adjustment$T) {
	GtkLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_layout_set_vadjustment(self, adjustment);
	return SUCCESS;
};

METHOD("Thaw", TYP, T) {
	GtkLayout * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_layout_thaw(self);
	return SUCCESS;
};

