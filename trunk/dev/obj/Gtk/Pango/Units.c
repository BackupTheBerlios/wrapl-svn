#include <Gtk/Pango/Units.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 1
#include <Gtk/GObject/Object.h>
/***********************************/
GLOBAL_FUNCTION(FromDouble, 1) {
	double d = ((Std$Real_t *)Args[0].Val)->Value;
	int result = pango_units_from_double(d);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ToDouble, 1) {
	int i = ((Std$Integer_smallt *)Args[0].Val)->Value;
	double result = pango_units_to_double(i);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

