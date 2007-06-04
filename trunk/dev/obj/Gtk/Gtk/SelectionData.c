#include <Gtk/Gtk/SelectionData.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/SelectionData.h>
#include <Gtk/Gtk/TextBuffer.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_selection_data_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GtkSelectionData * self= &((Gtk$Gtk$SelectionData_t *)Args[0].Val)->Value;
	GtkSelectionData * result = gtk_selection_data_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	GtkSelectionData * self= &((Gtk$Gtk$SelectionData_t *)Args[0].Val)->Value;
	gtk_selection_data_free(self);
	return SUCCESS;
};

METHOD("GetPixbuf", TYP, T) {
	GtkSelectionData * self= &((Gtk$Gtk$SelectionData_t *)Args[0].Val)->Value;
	GdkPixbuf * result = gtk_selection_data_get_pixbuf(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetTargets", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkSelectionData * self= &((Gtk$Gtk$SelectionData_t *)Args[0].Val)->Value;
	GdkAtom** targets = 0;
	gint* n_atoms = 0;
	int result = gtk_selection_data_get_targets(self, targets, n_atoms);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetText", TYP, T) {
	GtkSelectionData * self= &((Gtk$Gtk$SelectionData_t *)Args[0].Val)->Value;
	char * result = gtk_selection_data_get_text(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetUris", TYP, T) {
	GtkSelectionData * self= &((Gtk$Gtk$SelectionData_t *)Args[0].Val)->Value;
	const char * const * result = gtk_selection_data_get_uris(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Set", TYP, T, TYP, Std$Object$T, TYP, Std$Integer$SmallT, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GtkSelectionData * self= &((Gtk$Gtk$SelectionData_t *)Args[0].Val)->Value;
	GdkAtom type = 0;
	int format = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char *data = Std$String$flatten(Args[3].Val);
	int length = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_selection_data_set(self, type, format, data, length);
	return SUCCESS;
};

METHOD("SetPixbuf", TYP, T, TYP, Gtk$Gdk$Pixbuf$T) {
	GtkSelectionData * self= &((Gtk$Gtk$SelectionData_t *)Args[0].Val)->Value;
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_selection_data_set_pixbuf(self, pixbuf);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetText", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GtkSelectionData * self= &((Gtk$Gtk$SelectionData_t *)Args[0].Val)->Value;
	char *str = Std$String$flatten(Args[1].Val);
	int len = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gtk_selection_data_set_text(self, str, len);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetUris", TYP, T, TYP, Std$List$T) {
	GtkSelectionData * self= &((Gtk$Gtk$SelectionData_t *)Args[0].Val)->Value;
	const char * const * uris;
	int result = gtk_selection_data_set_uris(self, uris);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("TargetsIncludeImage", TYP, T, TYP, Std$Symbol$T) {
	GtkSelectionData * self= &((Gtk$Gtk$SelectionData_t *)Args[0].Val)->Value;
	int writable = Args[1].Val == $true;
	int result = gtk_selection_data_targets_include_image(self, writable);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("TargetsIncludeRichText", TYP, T, TYP, Gtk$Gtk$TextBuffer$T) {
	GtkSelectionData * self= &((Gtk$Gtk$SelectionData_t *)Args[0].Val)->Value;
	GtkTextBuffer * buffer = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_selection_data_targets_include_rich_text(self, buffer);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("TargetsIncludeText", TYP, T) {
	GtkSelectionData * self= &((Gtk$Gtk$SelectionData_t *)Args[0].Val)->Value;
	int result = gtk_selection_data_targets_include_text(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("TargetsIncludeUri", TYP, T) {
	GtkSelectionData * self= &((Gtk$Gtk$SelectionData_t *)Args[0].Val)->Value;
	int result = gtk_selection_data_targets_include_uri(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

