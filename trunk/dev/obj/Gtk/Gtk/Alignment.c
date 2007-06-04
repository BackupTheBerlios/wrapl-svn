#include <Gtk/Gtk/Alignment.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gtk/Alignment.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 4) {
	double xalign = ((Std$Real_t *)Args[0].Val)->Value;
	double yalign = ((Std$Real_t *)Args[1].Val)->Value;
	double xscale = ((Std$Real_t *)Args[2].Val)->Value;
	double yscale = ((Std$Real_t *)Args[3].Val)->Value;
	GtkAlignment * result = gtk_alignment_new(xalign, yalign, xscale, yscale);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_alignment_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetPadding", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkAlignment * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	guint* padding_top = 0;
	guint* padding_bottom = 0;
	guint* padding_left = 0;
	guint* padding_right = 0;
	gtk_alignment_get_padding(self, padding_top, padding_bottom, padding_left, padding_right);
	return SUCCESS;
};

METHOD("Set", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkAlignment * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double xalign = ((Std$Real_t *)Args[1].Val)->Value;
	double yalign = ((Std$Real_t *)Args[2].Val)->Value;
	double xscale = ((Std$Real_t *)Args[3].Val)->Value;
	double yscale = ((Std$Real_t *)Args[4].Val)->Value;
	gtk_alignment_set(self, xalign, yalign, xscale, yscale);
	return SUCCESS;
};

METHOD("SetPadding", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkAlignment * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int padding_top = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int padding_bottom = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int padding_left = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int padding_right = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_alignment_set_padding(self, padding_top, padding_bottom, padding_left, padding_right);
	return SUCCESS;
};

