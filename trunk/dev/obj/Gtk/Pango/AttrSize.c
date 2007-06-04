#include <Gtk/Pango/AttrSize.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 1
#include <Gtk/GObject/Object.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 1) {
	int size = ((Std$Integer_smallt *)Args[0].Val)->Value;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = pango_attr_size_new(size);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(NewAbsolute, 1) {
	int size = ((Std$Integer_smallt *)Args[0].Val)->Value;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = pango_attr_size_new_absolute(size);
	Result->Val= result;
	return SUCCESS;
};

