#include <Gtk/Gtk/Ruler.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/MetricType.h>
#include <Gtk/Gtk/Ruler.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_ruler_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("DrawPos", TYP, T) {
	GtkRuler * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_ruler_draw_pos(self);
	return SUCCESS;
};

METHOD("DrawTicks", TYP, T) {
	GtkRuler * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_ruler_draw_ticks(self);
	return SUCCESS;
};

METHOD("GetMetric", TYP, T) {
	GtkRuler * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkMetricType result = gtk_ruler_get_metric(self);
	Gtk$Gtk$MetricType_t *_result = new(Gtk$Gtk$MetricType_t);
	_result->Type = Gtk$Gtk$MetricType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetRange", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkRuler * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdouble* lower = 0;
	gdouble* upper = 0;
	gdouble* position = 0;
	gdouble* max_size = 0;
	gtk_ruler_get_range(self, lower, upper, position, max_size);
	return SUCCESS;
};

METHOD("SetMetric", TYP, T, TYP, Gtk$Gtk$MetricType$T) {
	GtkRuler * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkMetricType metric = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_ruler_set_metric(self, metric);
	return SUCCESS;
};

METHOD("SetRange", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkRuler * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double lower = ((Std$Real_t *)Args[1].Val)->Value;
	double upper = ((Std$Real_t *)Args[2].Val)->Value;
	double position = ((Std$Real_t *)Args[3].Val)->Value;
	double max_size = ((Std$Real_t *)Args[4].Val)->Value;
	gtk_ruler_set_range(self, lower, upper, position, max_size);
	return SUCCESS;
};

