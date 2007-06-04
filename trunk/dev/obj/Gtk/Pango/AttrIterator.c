#include <Gtk/Pango/AttrIterator.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/Pango/FontDescription.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/AttrType.h>
#include <Gtk/Pango/Attribute.h>
#include <Gtk/Pango/AttrIterator.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T);

METHOD("Copy", TYP, T) {
	PangoAttrIterator * self= ((Gtk$Pango$AttrIterator_t *)Args[0].Val)->Value;
	PangoAttrIterator * result = pango_attr_iterator_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Destroy", TYP, T) {
	PangoAttrIterator * self= ((Gtk$Pango$AttrIterator_t *)Args[0].Val)->Value;
	pango_attr_iterator_destroy(self);
	return SUCCESS;
};

METHOD("Get", TYP, T, TYP, Gtk$Pango$AttrType$T) {
	PangoAttrIterator * self= ((Gtk$Pango$AttrIterator_t *)Args[0].Val)->Value;
	PangoAttrType type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	PangoAttribute * result = pango_attr_iterator_get(self, type);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetAttrs", TYP, T) {
	PangoAttrIterator * self= ((Gtk$Pango$AttrIterator_t *)Args[0].Val)->Value;
	GSList* result = pango_attr_iterator_get_attrs(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetFont", TYP, T, TYP, Gtk$Pango$FontDescription$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoAttrIterator * self= ((Gtk$Pango$AttrIterator_t *)Args[0].Val)->Value;
	PangoFontDescription * desc= ((Gtk$Pango$FontDescription_t *)Args[1].Val)->Value;
	PangoLanguage** language = 0;
	GSList** extra_attrs = 0;
	pango_attr_iterator_get_font(self, desc, language, extra_attrs);
	return SUCCESS;
};

METHOD("Next", TYP, T) {
	PangoAttrIterator * self= ((Gtk$Pango$AttrIterator_t *)Args[0].Val)->Value;
	int result = pango_attr_iterator_next(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Range", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoAttrIterator * self= ((Gtk$Pango$AttrIterator_t *)Args[0].Val)->Value;
	gint* start = 0;
	gint* end = 0;
	pango_attr_iterator_range(self, start, end);
	return SUCCESS;
};

