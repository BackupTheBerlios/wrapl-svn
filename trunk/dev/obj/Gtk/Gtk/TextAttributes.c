#include <Gtk/Gtk/TextAttributes.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TextAttributes.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 0) {
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gtk_text_attributes_new();
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_text_attributes_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GtkTextAttributes * self= ((Gtk$Gtk$TextAttributes_t *)Args[0].Val)->Value;
	GtkTextAttributes * result = gtk_text_attributes_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("CopyValues", TYP, T, TYP, Gtk$Gtk$TextAttributes$T) {
	GtkTextAttributes * self= ((Gtk$Gtk$TextAttributes_t *)Args[0].Val)->Value;
	GtkTextAttributes * dest= ((Gtk$Gtk$TextAttributes_t *)Args[1].Val)->Value;
	gtk_text_attributes_copy_values(self, dest);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GtkTextAttributes * self= ((Gtk$Gtk$TextAttributes_t *)Args[0].Val)->Value;
	GtkTextAttributes * result = gtk_text_attributes_ref(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GtkTextAttributes * self= ((Gtk$Gtk$TextAttributes_t *)Args[0].Val)->Value;
	gtk_text_attributes_unref(self);
	return SUCCESS;
};

