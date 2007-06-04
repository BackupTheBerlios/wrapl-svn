#include <Gtk/Gtk/Rc.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 8
#include <Gtk/Gtk/RcStyle.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/Gtk/Style.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Settings.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
/***********************************/
GLOBAL_FUNCTION(AddClassStyle, 2) {
	GtkRcStyle * rc_style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *pattern = Std$String$flatten(Args[1].Val);
	gtk_rc_add_class_style(rc_style, pattern);
	return SUCCESS;
};

GLOBAL_FUNCTION(AddDefaultFile, 1) {
	char *filename = Std$String$flatten(Args[0].Val);
	gtk_rc_add_default_file(filename);
	return SUCCESS;
};

GLOBAL_FUNCTION(AddWidgetClassStyle, 2) {
	GtkRcStyle * rc_style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *pattern = Std$String$flatten(Args[1].Val);
	gtk_rc_add_widget_class_style(rc_style, pattern);
	return SUCCESS;
};

GLOBAL_FUNCTION(AddWidgetNameStyle, 2) {
	GtkRcStyle * rc_style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *pattern = Std$String$flatten(Args[1].Val);
	gtk_rc_add_widget_name_style(rc_style, pattern);
	return SUCCESS;
};

GLOBAL_FUNCTION(FindModuleInPath, 1) {
	char *module_file = Std$String$flatten(Args[0].Val);
	char * result = gtk_rc_find_module_in_path(module_file);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(FindPixmapInPath, 3) {
	GtkSettings * settings = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GScanner* scanner = 0;
	char *pixmap_file = Std$String$flatten(Args[2].Val);
	char * result = gtk_rc_find_pixmap_in_path(settings, scanner, pixmap_file);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetDefaultFiles, 0) {
	const char * const * result = gtk_rc_get_default_files();
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetImModuleFile, 0) {
	char * result = gtk_rc_get_im_module_file();
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetImModulePath, 0) {
	char * result = gtk_rc_get_im_module_path();
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetModuleDir, 0) {
	char * result = gtk_rc_get_module_dir();
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetStyle, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkStyle * result = gtk_rc_get_style(widget);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetStyleByPaths, 4) {
	GtkSettings * settings = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *widget_path = Std$String$flatten(Args[1].Val);
	char *class_path = Std$String$flatten(Args[2].Val);
	GType type;
	GtkStyle * result = gtk_rc_get_style_by_paths(settings, widget_path, class_path, type);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetThemeDir, 0) {
	char * result = gtk_rc_get_theme_dir();
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Parse, 1) {
	char *filename = Std$String$flatten(Args[0].Val);
	gtk_rc_parse(filename);
	return SUCCESS;
};

GLOBAL_FUNCTION(ParseColor, 2) {
	GScanner* scanner = 0;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	int result = gtk_rc_parse_color(scanner, color);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ParsePriority, 2) {
	GScanner* scanner = 0;
	GtkPathPriorityType* priority = 0;
	int result = gtk_rc_parse_priority(scanner, priority);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ParseState, 2) {
	GScanner* scanner = 0;
	GtkStateType* state = 0;
	int result = gtk_rc_parse_state(scanner, state);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ParseString, 1) {
	char *rc_string = Std$String$flatten(Args[0].Val);
	gtk_rc_parse_string(rc_string);
	return SUCCESS;
};

GLOBAL_FUNCTION(ReparseAll, 0) {
	int result = gtk_rc_reparse_all();
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ReparseAllForSettings, 2) {
	GtkSettings * settings = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int force_load = Args[1].Val == $true;
	int result = gtk_rc_reparse_all_for_settings(settings, force_load);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ResetStyles, 1) {
	GtkSettings * settings = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_rc_reset_styles(settings);
	return SUCCESS;
};

GLOBAL_FUNCTION(ScannerNew, 0) {
	GScanner* result = gtk_rc_scanner_new();
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(SetDefaultFiles, 1) {
	const char * const * filenames;
	gtk_rc_set_default_files(filenames);
	return SUCCESS;
};

