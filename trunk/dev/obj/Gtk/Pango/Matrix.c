#include <Gtk/Pango/Matrix.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/Pango/Rectangle.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Matrix.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_matrix_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Concat", TYP, T, TYP, Gtk$Pango$Matrix$T) {
	PangoMatrix * self= &((Gtk$Pango$Matrix_t *)Args[0].Val)->Value;
	PangoMatrix * new_matrix= &((Gtk$Pango$Matrix_t *)Args[1].Val)->Value;
	pango_matrix_concat(self, new_matrix);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	PangoMatrix * self= &((Gtk$Pango$Matrix_t *)Args[0].Val)->Value;
	PangoMatrix * result = pango_matrix_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	PangoMatrix * self= &((Gtk$Pango$Matrix_t *)Args[0].Val)->Value;
	pango_matrix_free(self);
	return SUCCESS;
};

METHOD("GetFontScaleFactor", TYP, T) {
	PangoMatrix * self= &((Gtk$Pango$Matrix_t *)Args[0].Val)->Value;
	double result = pango_matrix_get_font_scale_factor(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("Rotate", TYP, T, TYP, Std$Real$T) {
	PangoMatrix * self= &((Gtk$Pango$Matrix_t *)Args[0].Val)->Value;
	double degrees = ((Std$Real_t *)Args[1].Val)->Value;
	pango_matrix_rotate(self, degrees);
	return SUCCESS;
};

METHOD("Scale", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T) {
	PangoMatrix * self= &((Gtk$Pango$Matrix_t *)Args[0].Val)->Value;
	double scale_x = ((Std$Real_t *)Args[1].Val)->Value;
	double scale_y = ((Std$Real_t *)Args[2].Val)->Value;
	pango_matrix_scale(self, scale_x, scale_y);
	return SUCCESS;
};

METHOD("TransformDistance", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoMatrix * self= &((Gtk$Pango$Matrix_t *)Args[0].Val)->Value;
	double* dx = 0;
	double* dy = 0;
	pango_matrix_transform_distance(self, dx, dy);
	return SUCCESS;
};

METHOD("TransformPixelRectangle", TYP, T, TYP, Gtk$Pango$Rectangle$T) {
	PangoMatrix * self= &((Gtk$Pango$Matrix_t *)Args[0].Val)->Value;
	PangoRectangle * rect= &((Gtk$Pango$Rectangle_t *)Args[1].Val)->Value;
	pango_matrix_transform_pixel_rectangle(self, rect);
	return SUCCESS;
};

METHOD("TransformPoint", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoMatrix * self= &((Gtk$Pango$Matrix_t *)Args[0].Val)->Value;
	double* x = 0;
	double* y = 0;
	pango_matrix_transform_point(self, x, y);
	return SUCCESS;
};

METHOD("TransformRectangle", TYP, T, TYP, Gtk$Pango$Rectangle$T) {
	PangoMatrix * self= &((Gtk$Pango$Matrix_t *)Args[0].Val)->Value;
	PangoRectangle * rect= &((Gtk$Pango$Rectangle_t *)Args[1].Val)->Value;
	pango_matrix_transform_rectangle(self, rect);
	return SUCCESS;
};

METHOD("Translate", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T) {
	PangoMatrix * self= &((Gtk$Pango$Matrix_t *)Args[0].Val)->Value;
	double tx = ((Std$Real_t *)Args[1].Val)->Value;
	double ty = ((Std$Real_t *)Args[2].Val)->Value;
	pango_matrix_translate(self, tx, ty);
	return SUCCESS;
};

