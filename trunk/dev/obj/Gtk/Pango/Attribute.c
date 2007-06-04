#include <Gtk/Pango/Attribute.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Std/Boolean.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Attribute.h>
/***********************************/
TYPE(T);

METHOD("Copy", TYP, T) {
	PangoAttribute * self= ((Gtk$Pango$Attribute_t *)Args[0].Val)->Value;
	PangoAttribute * result = pango_attribute_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Destroy", TYP, T) {
	PangoAttribute * self= ((Gtk$Pango$Attribute_t *)Args[0].Val)->Value;
	pango_attribute_destroy(self);
	return SUCCESS;
};

METHOD("Equal", TYP, T, TYP, Gtk$Pango$Attribute$T) {
	PangoAttribute * self= ((Gtk$Pango$Attribute_t *)Args[0].Val)->Value;
	PangoAttribute * attr2= ((Gtk$Pango$Attribute_t *)Args[1].Val)->Value;
	int result = pango_attribute_equal(self, attr2);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

