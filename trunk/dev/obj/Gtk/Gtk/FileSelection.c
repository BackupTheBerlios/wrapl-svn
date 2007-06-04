#include <Gtk/Gtk/FileSelection.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/FileSelection.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Dialog$T, Gtk$Gtk$Window$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	char *title = Std$String$flatten(Args[0].Val);
	GtkFileSelection * result = gtk_file_selection_new(title);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_file_selection_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Complete", TYP, T, TYP, Std$String$T) {
	GtkFileSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *pattern = Std$String$flatten(Args[1].Val);
	gtk_file_selection_complete(self, pattern);
	return SUCCESS;
};

METHOD("GetFilename", TYP, T) {
	GtkFileSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_file_selection_get_filename(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetSelectMultiple", TYP, T) {
	GtkFileSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_file_selection_get_select_multiple(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSelections", TYP, T) {
	GtkFileSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * result = gtk_file_selection_get_selections(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("HideFileopButtons", TYP, T) {
	GtkFileSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_file_selection_hide_fileop_buttons(self);
	return SUCCESS;
};

METHOD("SetFilename", TYP, T, TYP, Std$String$T) {
	GtkFileSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *filename = Std$String$flatten(Args[1].Val);
	gtk_file_selection_set_filename(self, filename);
	return SUCCESS;
};

METHOD("SetSelectMultiple", TYP, T, TYP, Std$Symbol$T) {
	GtkFileSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int select_multiple = Args[1].Val == $true;
	gtk_file_selection_set_select_multiple(self, select_multiple);
	return SUCCESS;
};

METHOD("ShowFileopButtons", TYP, T) {
	GtkFileSelection * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_file_selection_show_fileop_buttons(self);
	return SUCCESS;
};

