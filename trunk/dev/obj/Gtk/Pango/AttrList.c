#include <Gtk/Pango/AttrList.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/Pango/AttrFilterFunc.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/AttrList.h>
#include <Gtk/Pango/Attribute.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/AttrIterator.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 0) {
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = pango_attr_list_new();
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_attr_list_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Change", TYP, T, TYP, Gtk$Pango$Attribute$T) {
	PangoAttrList * self= ((Gtk$Pango$AttrList_t *)Args[0].Val)->Value;
	PangoAttribute * attr= ((Gtk$Pango$Attribute_t *)Args[1].Val)->Value;
	pango_attr_list_change(self, attr);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	PangoAttrList * self= ((Gtk$Pango$AttrList_t *)Args[0].Val)->Value;
	PangoAttrList * result = pango_attr_list_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Filter", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	PangoAttrList * self= ((Gtk$Pango$AttrList_t *)Args[0].Val)->Value;
	PangoAttrFilterFunc func = Gtk$Pango$AttrFilterFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	PangoAttrList * result = pango_attr_list_filter(self, func, data);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetIterator", TYP, T) {
	PangoAttrList * self= ((Gtk$Pango$AttrList_t *)Args[0].Val)->Value;
	PangoAttrIterator * result = pango_attr_list_get_iterator(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Insert", TYP, T, TYP, Gtk$Pango$Attribute$T) {
	PangoAttrList * self= ((Gtk$Pango$AttrList_t *)Args[0].Val)->Value;
	PangoAttribute * attr= ((Gtk$Pango$Attribute_t *)Args[1].Val)->Value;
	pango_attr_list_insert(self, attr);
	return SUCCESS;
};

METHOD("InsertBefore", TYP, T, TYP, Gtk$Pango$Attribute$T) {
	PangoAttrList * self= ((Gtk$Pango$AttrList_t *)Args[0].Val)->Value;
	PangoAttribute * attr= ((Gtk$Pango$Attribute_t *)Args[1].Val)->Value;
	pango_attr_list_insert_before(self, attr);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	PangoAttrList * self= ((Gtk$Pango$AttrList_t *)Args[0].Val)->Value;
	PangoAttrList * result = pango_attr_list_ref(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Splice", TYP, T, TYP, Gtk$Pango$AttrList$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	PangoAttrList * self= ((Gtk$Pango$AttrList_t *)Args[0].Val)->Value;
	PangoAttrList * other= ((Gtk$Pango$AttrList_t *)Args[1].Val)->Value;
	int pos = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int len = ((Std$Integer_smallt *)Args[3].Val)->Value;
	pango_attr_list_splice(self, other, pos, len);
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	PangoAttrList * self= ((Gtk$Pango$AttrList_t *)Args[0].Val)->Value;
	pango_attr_list_unref(self);
	return SUCCESS;
};

