#include <Gtk/Gtk/EventBox.h>

SYMBOL($TRUE, "TRUE");
SYMBOL($FALSE, "FALSE");

TYPE(T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_event_box_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};

METHOD("above", TYP, T) {
	GtkEventBox *EventBox = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	Result->Val = gtk_event_box_get_above_child(EventBox) ? $TRUE : $FALSE;
	return SUCCESS;
};


METHOD("above", TYP, T, TYP, Lang$Symbol$T) {
	GtkEventBox *EventBox = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_event_box_set_above_child(EventBox, Args[1].Val == $TRUE);
	Result->Arg = Args[0];
	return SUCCESS;
};
