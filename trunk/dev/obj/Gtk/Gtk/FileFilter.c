#include <Gtk/Gtk/FileFilter.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/FileFilterFunc.h>
#include <Gtk/Gtk/FileFilterInfo.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/FileFilter.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkFileFilter * result = gtk_file_filter_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_file_filter_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddCustom", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Object$T) {
	GtkFileFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int needed = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkFileFilterFunc func = Gtk$Gtk$FileFilterFunc$new(Args[2].Val);
	void *data = ((Std$Address_t *)Args[3].Val)->Value;
	GDestroyNotify notify = 0;
	gtk_file_filter_add_custom(self, needed, func, data, notify);
	return SUCCESS;
};

METHOD("AddMimeType", TYP, T, TYP, Std$String$T) {
	GtkFileFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *mime_type = Std$String$flatten(Args[1].Val);
	gtk_file_filter_add_mime_type(self, mime_type);
	return SUCCESS;
};

METHOD("AddPattern", TYP, T, TYP, Std$String$T) {
	GtkFileFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *pattern = Std$String$flatten(Args[1].Val);
	gtk_file_filter_add_pattern(self, pattern);
	return SUCCESS;
};

METHOD("AddPixbufFormats", TYP, T) {
	GtkFileFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_file_filter_add_pixbuf_formats(self);
	return SUCCESS;
};

METHOD("Filter", TYP, T, TYP, Gtk$Gtk$FileFilterInfo$T) {
	GtkFileFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkFileFilterInfo * filter_info= &((Gtk$Gtk$FileFilterInfo_t *)Args[1].Val)->Value;
	int result = gtk_file_filter_filter(self, filter_info);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetName", TYP, T) {
	GtkFileFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_file_filter_get_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetNeeded", TYP, T) {
	GtkFileFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_file_filter_get_needed(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("SetName", TYP, T, TYP, Std$String$T) {
	GtkFileFilter * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	gtk_file_filter_set_name(self, name);
	return SUCCESS;
};

