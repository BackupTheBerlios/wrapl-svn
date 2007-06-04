#include <Gtk/Gtk/LinkButton.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/Gtk/LinkButton.h>
#include <Gtk/Gtk/LinkButtonUriFunc.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$Button$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	char *uri = Std$String$flatten(Args[0].Val);
	GtkLinkButton * result = gtk_link_button_new(uri);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithLabel, 2) {
	char *uri = Std$String$flatten(Args[0].Val);
	char *label = Std$String$flatten(Args[1].Val);
	GtkLinkButton * result = gtk_link_button_new_with_label(uri, label);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_link_button_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetUriHook, 3) {
	GtkLinkButtonUriFunc func = Gtk$Gtk$LinkButtonUriFunc$new(Args[0].Val);
	void *data = ((Std$Address_t *)Args[1].Val)->Value;
	GDestroyNotify destroy = 0;
	GtkLinkButtonUriFunc result = gtk_link_button_set_uri_hook(func, data, destroy);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetUri", TYP, T) {
	GtkLinkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_link_button_get_uri(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("SetUri", TYP, T, TYP, Std$String$T) {
	GtkLinkButton * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *uri = Std$String$flatten(Args[1].Val);
	gtk_link_button_set_uri(self, uri);
	return SUCCESS;
};

