#include <Gtk/Pango/TabArray.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Std/Boolean.h>
#include <Gtk/Pango/TabAlign.h>
#include <Gtk/Pango/TabArray.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 2) {
	int initial_size = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int positions_in_pixels = Args[1].Val == $true;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = pango_tab_array_new(initial_size, positions_in_pixels);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithPositions, 5) {
	int size = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int positions_in_pixels = Args[1].Val == $true;
	PangoTabAlign first_alignment = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int first_position = ((Std$Integer_smallt *)Args[3].Val)->Value;
	char *___ = 0;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = pango_tab_array_new_with_positions(size, positions_in_pixels, first_alignment, first_position, ___);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_tab_array_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	PangoTabArray * self= ((Gtk$Pango$TabArray_t *)Args[0].Val)->Value;
	PangoTabArray * result = pango_tab_array_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	PangoTabArray * self= ((Gtk$Pango$TabArray_t *)Args[0].Val)->Value;
	pango_tab_array_free(self);
	return SUCCESS;
};

METHOD("GetPositionsInPixels", TYP, T) {
	PangoTabArray * self= ((Gtk$Pango$TabArray_t *)Args[0].Val)->Value;
	int result = pango_tab_array_get_positions_in_pixels(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSize", TYP, T) {
	PangoTabArray * self= ((Gtk$Pango$TabArray_t *)Args[0].Val)->Value;
	int result = pango_tab_array_get_size(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetTab", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoTabArray * self= ((Gtk$Pango$TabArray_t *)Args[0].Val)->Value;
	int tab_index = ((Std$Integer_smallt *)Args[1].Val)->Value;
	PangoTabAlign* alignment = 0;
	gint* location = 0;
	pango_tab_array_get_tab(self, tab_index, alignment, location);
	return SUCCESS;
};

METHOD("GetTabs", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoTabArray * self= ((Gtk$Pango$TabArray_t *)Args[0].Val)->Value;
	PangoTabAlign** alignments = 0;
	gint** locations = 0;
	pango_tab_array_get_tabs(self, alignments, locations);
	return SUCCESS;
};

METHOD("Resize", TYP, T, TYP, Std$Integer$SmallT) {
	PangoTabArray * self= ((Gtk$Pango$TabArray_t *)Args[0].Val)->Value;
	int new_size = ((Std$Integer_smallt *)Args[1].Val)->Value;
	pango_tab_array_resize(self, new_size);
	return SUCCESS;
};

METHOD("SetTab", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Pango$TabAlign$T, TYP, Std$Integer$SmallT) {
	PangoTabArray * self= ((Gtk$Pango$TabArray_t *)Args[0].Val)->Value;
	int tab_index = ((Std$Integer_smallt *)Args[1].Val)->Value;
	PangoTabAlign alignment = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int location = ((Std$Integer_smallt *)Args[3].Val)->Value;
	pango_tab_array_set_tab(self, tab_index, alignment, location);
	return SUCCESS;
};

