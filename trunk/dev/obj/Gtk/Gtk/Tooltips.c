#include <Gtk/Gtk/Tooltips.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Std/Boolean.h>
#include <Gtk/Gtk/Tooltips.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
#include <Gtk/Gtk/Window.h>
/***********************************/
TYPE(T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkTooltips * result = gtk_tooltips_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetInfoFromTipWindow, 3) {
	GtkWindow * tip_window = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTooltips** tooltips = 0;
	GtkWidget** current_widget = 0;
	int result = gtk_tooltips_get_info_from_tip_window(tip_window, tooltips, current_widget);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tooltips_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Disable", TYP, T) {
	GtkTooltips * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tooltips_disable(self);
	return SUCCESS;
};

METHOD("Enable", TYP, T) {
	GtkTooltips * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tooltips_enable(self);
	return SUCCESS;
};

METHOD("ForceWindow", TYP, T) {
	GtkTooltips * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tooltips_force_window(self);
	return SUCCESS;
};

METHOD("SetDelay", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTooltips * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int delay = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_tooltips_set_delay(self, delay);
	return SUCCESS;
};

METHOD("SetTip", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T, TYP, Std$String$T) {
	GtkTooltips * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *tip_text = Std$String$flatten(Args[2].Val);
	char *tip_private = Std$String$flatten(Args[3].Val);
	gtk_tooltips_set_tip(self, widget, tip_text, tip_private);
	return SUCCESS;
};

