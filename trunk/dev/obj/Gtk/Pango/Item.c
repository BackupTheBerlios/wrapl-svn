#include <Gtk/Pango/Item.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Pango/Item.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 0) {
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = pango_item_new();
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_item_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	PangoItem * self= ((Gtk$Pango$Item_t *)Args[0].Val)->Value;
	PangoItem * result = pango_item_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	PangoItem * self= ((Gtk$Pango$Item_t *)Args[0].Val)->Value;
	pango_item_free(self);
	return SUCCESS;
};

METHOD("Split", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	PangoItem * self= ((Gtk$Pango$Item_t *)Args[0].Val)->Value;
	int split_index = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int split_offset = ((Std$Integer_smallt *)Args[2].Val)->Value;
	PangoItem * result = pango_item_split(self, split_index, split_offset);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

