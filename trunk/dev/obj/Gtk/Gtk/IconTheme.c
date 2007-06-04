#include <Gtk/Gtk/IconTheme.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/IconTheme.h>
#include <Gtk/Gtk/IconInfo.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Gtk/Gdk/Screen.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkIconTheme * result = gtk_icon_theme_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(AddBuiltinIcon, 3) {
	char *icon_name = Std$String$flatten(Args[0].Val);
	int size = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_icon_theme_add_builtin_icon(icon_name, size, pixbuf);
	return SUCCESS;
};

GLOBAL_FUNCTION(ErrorQuark, 0) {
	GQuark result = gtk_icon_theme_error_quark();
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetDefault, 0) {
	GtkIconTheme * result = gtk_icon_theme_get_default();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetForScreen, 1) {
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkIconTheme * result = gtk_icon_theme_get_for_screen(screen);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_icon_theme_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AppendSearchPath", TYP, T, TYP, Std$String$T) {
	GtkIconTheme * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *path = Std$String$flatten(Args[1].Val);
	gtk_icon_theme_append_search_path(self, path);
	return SUCCESS;
};

METHOD("GetExampleIconName", TYP, T) {
	GtkIconTheme * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char * result = gtk_icon_theme_get_example_icon_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetIconSizes", TYP, T, TYP, Std$String$T) {
	GtkIconTheme * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *icon_name = Std$String$flatten(Args[1].Val);
	gint* result = gtk_icon_theme_get_icon_sizes(self, icon_name);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetSearchPath", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkIconTheme * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gchar*** path = 0;
	gint* n_elements = 0;
	gtk_icon_theme_get_search_path(self, path, n_elements);
	return SUCCESS;
};

METHOD("HasIcon", TYP, T, TYP, Std$String$T) {
	GtkIconTheme * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *icon_name = Std$String$flatten(Args[1].Val);
	int result = gtk_icon_theme_has_icon(self, icon_name);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ListIcons", TYP, T, TYP, Std$String$T) {
	GtkIconTheme * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *context = Std$String$flatten(Args[1].Val);
	GList* result = gtk_icon_theme_list_icons(self, context);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("LoadIcon", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkIconTheme * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *icon_name = Std$String$flatten(Args[1].Val);
	int size = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int flags = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GError** error = 0;
	GdkPixbuf * result = gtk_icon_theme_load_icon(self, icon_name, size, flags, error);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("LookupIcon", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkIconTheme * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *icon_name = Std$String$flatten(Args[1].Val);
	int size = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int flags = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GtkIconInfo * result = gtk_icon_theme_lookup_icon(self, icon_name, size, flags);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("PrependSearchPath", TYP, T, TYP, Std$String$T) {
	GtkIconTheme * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *path = Std$String$flatten(Args[1].Val);
	gtk_icon_theme_prepend_search_path(self, path);
	return SUCCESS;
};

METHOD("RescanIfNeeded", TYP, T) {
	GtkIconTheme * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_icon_theme_rescan_if_needed(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetCustomTheme", TYP, T, TYP, Std$String$T) {
	GtkIconTheme * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *theme_name = Std$String$flatten(Args[1].Val);
	gtk_icon_theme_set_custom_theme(self, theme_name);
	return SUCCESS;
};

METHOD("SetScreen", TYP, T, TYP, Gtk$Gdk$Screen$T) {
	GtkIconTheme * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_icon_theme_set_screen(self, screen);
	return SUCCESS;
};

METHOD("SetSearchPath", TYP, T, TYP, Std$List$T, TYP, Std$Integer$SmallT) {
	GtkIconTheme * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * path;
	int n_elements = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_icon_theme_set_search_path(self, path, n_elements);
	return SUCCESS;
};

