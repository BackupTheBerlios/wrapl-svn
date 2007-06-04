#include <Gtk/Pango/AttrShape.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Pango/Rectangle.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/AttrDataCopyFunc.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 2) {
	PangoRectangle * ink_rect= &((Gtk$Pango$Rectangle_t *)Args[0].Val)->Value;
	PangoRectangle * logical_rect= &((Gtk$Pango$Rectangle_t *)Args[1].Val)->Value;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = pango_attr_shape_new(ink_rect, logical_rect);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithData, 5) {
	PangoRectangle * ink_rect= &((Gtk$Pango$Rectangle_t *)Args[0].Val)->Value;
	PangoRectangle * logical_rect= &((Gtk$Pango$Rectangle_t *)Args[1].Val)->Value;
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	PangoAttrDataCopyFunc copy_func = Gtk$Pango$AttrDataCopyFunc$new(Args[3].Val);
	GDestroyNotify destroy_func = 0;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = pango_attr_shape_new_with_data(ink_rect, logical_rect, data, copy_func, destroy_func);
	Result->Val= result;
	return SUCCESS;
};

