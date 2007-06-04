#include <Gtk/Gtk/TextTagTable.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/Gtk/TextTag.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TextTagTable.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/TextTagTableForeach.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkTextTagTable * result = gtk_text_tag_table_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_text_tag_table_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Add", TYP, T, TYP, Gtk$Gtk$TextTag$T) {
	GtkTextTagTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextTag * tag = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_text_tag_table_add(self, tag);
	return SUCCESS;
};

METHOD("Foreach", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkTextTagTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextTagTableForeach func = Gtk$Gtk$TextTagTableForeach$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	gtk_text_tag_table_foreach(self, func, data);
	return SUCCESS;
};

METHOD("GetSize", TYP, T) {
	GtkTextTagTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_tag_table_get_size(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Lookup", TYP, T, TYP, Std$String$T) {
	GtkTextTagTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	GtkTextTag * result = gtk_text_tag_table_lookup(self, name);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Remove", TYP, T, TYP, Gtk$Gtk$TextTag$T) {
	GtkTextTagTable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextTag * tag = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_text_tag_table_remove(self, tag);
	return SUCCESS;
};

