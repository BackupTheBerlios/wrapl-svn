#include <Gtk/Gtk/Curve.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/Curve.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/CurveType.h>
/***********************************/
TYPE(T, Gtk$Gtk$DrawingArea$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkCurve * result = gtk_curve_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_curve_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetVector", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkCurve * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int veclen = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gfloat* vector = 0;
	gtk_curve_get_vector(self, veclen, vector);
	return SUCCESS;
};

METHOD("Reset", TYP, T) {
	GtkCurve * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_curve_reset(self);
	return SUCCESS;
};

METHOD("SetCurveType", TYP, T, TYP, Gtk$Gtk$CurveType$T) {
	GtkCurve * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCurveType type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_curve_set_curve_type(self, type);
	return SUCCESS;
};

METHOD("SetGamma", TYP, T, TYP, Std$Real$T) {
	GtkCurve * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double gamma_ = ((Std$Real_t *)Args[1].Val)->Value;
	gtk_curve_set_gamma(self, gamma_);
	return SUCCESS;
};

METHOD("SetRange", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkCurve * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double min_x = ((Std$Real_t *)Args[1].Val)->Value;
	double max_x = ((Std$Real_t *)Args[2].Val)->Value;
	double min_y = ((Std$Real_t *)Args[3].Val)->Value;
	double max_y = ((Std$Real_t *)Args[4].Val)->Value;
	gtk_curve_set_range(self, min_x, max_x, min_y, max_y);
	return SUCCESS;
};

METHOD("SetVector", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkCurve * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int veclen = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gfloat* vector = 0;
	gtk_curve_set_vector(self, veclen, vector);
	return SUCCESS;
};

