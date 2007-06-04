#include <Gtk/Gtk/Icon.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Std/Boolean.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/IconSize.h>
#include <Gtk/Gtk/Settings.h>
/***********************************/
GLOBAL_FUNCTION(SizeFromName, 1) {
	char *name = Std$String$flatten(Args[0].Val);
	GtkIconSize result = gtk_icon_size_from_name(name);
	Gtk$Gtk$IconSize_t *_result = new(Gtk$Gtk$IconSize_t);
	_result->Type = Gtk$Gtk$IconSize$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

GLOBAL_FUNCTION(SizeGetName, 1) {
	GtkIconSize size = ((Std$Integer_smallt *)Args[0].Val)->Value;
	const char * result = gtk_icon_size_get_name(size);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(SizeLookup, 3) {
	GtkIconSize size = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gint* width = 0;
	gint* height = 0;
	int result = gtk_icon_size_lookup(size, width, height);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(SizeLookupForSettings, 4) {
	GtkSettings * settings = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkIconSize size = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gint* width = 0;
	gint* height = 0;
	int result = gtk_icon_size_lookup_for_settings(settings, size, width, height);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(SizeRegister, 3) {
	char *name = Std$String$flatten(Args[0].Val);
	int width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkIconSize result = gtk_icon_size_register(name, width, height);
	Gtk$Gtk$IconSize_t *_result = new(Gtk$Gtk$IconSize_t);
	_result->Type = Gtk$Gtk$IconSize$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

GLOBAL_FUNCTION(SizeRegisterAlias, 2) {
	char *alias = Std$String$flatten(Args[0].Val);
	GtkIconSize target = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_icon_size_register_alias(alias, target);
	return SUCCESS;
};

