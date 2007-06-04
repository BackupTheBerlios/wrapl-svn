#include <Gtk/Gtk/FileChooser.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/FileFilter.h>
#include <Gtk/Gtk/Widget.h>
#include <Gtk/Gtk/FileChooser.h>
#include <Gtk/Gtk/FileChooserAction.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(ErrorQuark, 0) {
	GQuark result = gtk_file_chooser_error_quark();
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_file_chooser_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddFilter", TYP, T, TYP, Gtk$Gtk$FileFilter$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkFileFilter * filter = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_file_chooser_add_filter(self, filter);
	return SUCCESS;
};

METHOD("AddShortcutFolder", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *folder = Std$String$flatten(Args[1].Val);
	GError** error = 0;
	int result = gtk_file_chooser_add_shortcut_folder(self, folder, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("AddShortcutFolderUri", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *uri = Std$String$flatten(Args[1].Val);
	GError** error = 0;
	int result = gtk_file_chooser_add_shortcut_folder_uri(self, uri, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetAction", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkFileChooserAction result = gtk_file_chooser_get_action(self);
	Gtk$Gtk$FileChooserAction_t *_result = new(Gtk$Gtk$FileChooserAction_t);
	_result->Type = Gtk$Gtk$FileChooserAction$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetCurrentFolder", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char * result = gtk_file_chooser_get_current_folder(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetCurrentFolderUri", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char * result = gtk_file_chooser_get_current_folder_uri(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetDoOverwriteConfirmation", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_file_chooser_get_do_overwrite_confirmation(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetExtraWidget", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_file_chooser_get_extra_widget(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetFilename", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char * result = gtk_file_chooser_get_filename(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetFilenames", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* result = gtk_file_chooser_get_filenames(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetFilter", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkFileFilter * result = gtk_file_chooser_get_filter(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetLocalOnly", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_file_chooser_get_local_only(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetPreviewFilename", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char * result = gtk_file_chooser_get_preview_filename(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetPreviewUri", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char * result = gtk_file_chooser_get_preview_uri(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetPreviewWidget", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_file_chooser_get_preview_widget(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPreviewWidgetActive", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_file_chooser_get_preview_widget_active(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSelectMultiple", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_file_chooser_get_select_multiple(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetShowHidden", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_file_chooser_get_show_hidden(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetUri", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char * result = gtk_file_chooser_get_uri(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetUris", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* result = gtk_file_chooser_get_uris(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetUsePreviewLabel", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_file_chooser_get_use_preview_label(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ListFilters", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* result = gtk_file_chooser_list_filters(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("ListShortcutFolderUris", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* result = gtk_file_chooser_list_shortcut_folder_uris(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("ListShortcutFolders", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GSList* result = gtk_file_chooser_list_shortcut_folders(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("RemoveFilter", TYP, T, TYP, Gtk$Gtk$FileFilter$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkFileFilter * filter = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_file_chooser_remove_filter(self, filter);
	return SUCCESS;
};

METHOD("RemoveShortcutFolder", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *folder = Std$String$flatten(Args[1].Val);
	GError** error = 0;
	int result = gtk_file_chooser_remove_shortcut_folder(self, folder, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("RemoveShortcutFolderUri", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *uri = Std$String$flatten(Args[1].Val);
	GError** error = 0;
	int result = gtk_file_chooser_remove_shortcut_folder_uri(self, uri, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SelectAll", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_file_chooser_select_all(self);
	return SUCCESS;
};

METHOD("SelectFilename", TYP, T, TYP, Std$String$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *filename = Std$String$flatten(Args[1].Val);
	int result = gtk_file_chooser_select_filename(self, filename);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SelectUri", TYP, T, TYP, Std$String$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *uri = Std$String$flatten(Args[1].Val);
	int result = gtk_file_chooser_select_uri(self, uri);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetAction", TYP, T, TYP, Gtk$Gtk$FileChooserAction$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkFileChooserAction action = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_file_chooser_set_action(self, action);
	return SUCCESS;
};

METHOD("SetCurrentFolder", TYP, T, TYP, Std$String$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *filename = Std$String$flatten(Args[1].Val);
	int result = gtk_file_chooser_set_current_folder(self, filename);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetCurrentFolderUri", TYP, T, TYP, Std$String$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *uri = Std$String$flatten(Args[1].Val);
	int result = gtk_file_chooser_set_current_folder_uri(self, uri);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetCurrentName", TYP, T, TYP, Std$String$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	gtk_file_chooser_set_current_name(self, name);
	return SUCCESS;
};

METHOD("SetDoOverwriteConfirmation", TYP, T, TYP, Std$Symbol$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int do_overwrite_confirmation = Args[1].Val == $true;
	gtk_file_chooser_set_do_overwrite_confirmation(self, do_overwrite_confirmation);
	return SUCCESS;
};

METHOD("SetExtraWidget", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * extra_widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_file_chooser_set_extra_widget(self, extra_widget);
	return SUCCESS;
};

METHOD("SetFilename", TYP, T, TYP, Std$String$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *filename = Std$String$flatten(Args[1].Val);
	int result = gtk_file_chooser_set_filename(self, filename);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetFilter", TYP, T, TYP, Gtk$Gtk$FileFilter$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkFileFilter * filter = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_file_chooser_set_filter(self, filter);
	return SUCCESS;
};

METHOD("SetLocalOnly", TYP, T, TYP, Std$Symbol$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int local_only = Args[1].Val == $true;
	gtk_file_chooser_set_local_only(self, local_only);
	return SUCCESS;
};

METHOD("SetPreviewWidget", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * preview_widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_file_chooser_set_preview_widget(self, preview_widget);
	return SUCCESS;
};

METHOD("SetPreviewWidgetActive", TYP, T, TYP, Std$Symbol$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int active = Args[1].Val == $true;
	gtk_file_chooser_set_preview_widget_active(self, active);
	return SUCCESS;
};

METHOD("SetSelectMultiple", TYP, T, TYP, Std$Symbol$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int select_multiple = Args[1].Val == $true;
	gtk_file_chooser_set_select_multiple(self, select_multiple);
	return SUCCESS;
};

METHOD("SetShowHidden", TYP, T, TYP, Std$Symbol$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int show_hidden = Args[1].Val == $true;
	gtk_file_chooser_set_show_hidden(self, show_hidden);
	return SUCCESS;
};

METHOD("SetUri", TYP, T, TYP, Std$String$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *uri = Std$String$flatten(Args[1].Val);
	int result = gtk_file_chooser_set_uri(self, uri);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetUsePreviewLabel", TYP, T, TYP, Std$Symbol$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int use_label = Args[1].Val == $true;
	gtk_file_chooser_set_use_preview_label(self, use_label);
	return SUCCESS;
};

METHOD("UnselectAll", TYP, T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_file_chooser_unselect_all(self);
	return SUCCESS;
};

METHOD("UnselectFilename", TYP, T, TYP, Std$String$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *filename = Std$String$flatten(Args[1].Val);
	gtk_file_chooser_unselect_filename(self, filename);
	return SUCCESS;
};

METHOD("UnselectUri", TYP, T, TYP, Std$String$T) {
	GtkFileChooser * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *uri = Std$String$flatten(Args[1].Val);
	gtk_file_chooser_unselect_uri(self, uri);
	return SUCCESS;
};

