#include <Gtk/Gtk/Settings.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/SettingsValue.h>
#include <Gtk/Gtk/RcPropertyParser.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Settings.h>
#include <Gtk/Gdk/Screen.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetDefault, 0) {
	GtkSettings * result = gtk_settings_get_default();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetForScreen, 1) {
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSettings * result = gtk_settings_get_for_screen(screen);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_settings_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(InstallProperty, 1) {
	GParamSpec* pspec = 0;
	gtk_settings_install_property(pspec);
	return SUCCESS;
};

GLOBAL_FUNCTION(InstallPropertyParser, 2) {
	GParamSpec* pspec = 0;
	GtkRcPropertyParser parser = Gtk$Gtk$RcPropertyParser$new(Args[1].Val);
	gtk_settings_install_property_parser(pspec, parser);
	return SUCCESS;
};

METHOD("SetDoubleProperty", TYP, T, TYP, Std$String$T, TYP, Std$Real$T, TYP, Std$String$T) {
	GtkSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	double v_double = ((Std$Real_t *)Args[2].Val)->Value;
	char *origin = Std$String$flatten(Args[3].Val);
	gtk_settings_set_double_property(self, name, v_double, origin);
	return SUCCESS;
};

METHOD("SetLongProperty", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$String$T) {
	GtkSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	int v_long = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char *origin = Std$String$flatten(Args[3].Val);
	gtk_settings_set_long_property(self, name, v_long, origin);
	return SUCCESS;
};

METHOD("SetPropertyValue", TYP, T, TYP, Std$String$T, TYP, Gtk$Gtk$SettingsValue$T) {
	GtkSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	GtkSettingsValue * svalue= &((Gtk$Gtk$SettingsValue_t *)Args[2].Val)->Value;
	gtk_settings_set_property_value(self, name, svalue);
	return SUCCESS;
};

METHOD("SetStringProperty", TYP, T, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$String$T) {
	GtkSettings * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	char *v_string = Std$String$flatten(Args[2].Val);
	char *origin = Std$String$flatten(Args[3].Val);
	gtk_settings_set_string_property(self, name, v_string, origin);
	return SUCCESS;
};

