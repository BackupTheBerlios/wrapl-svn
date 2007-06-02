#include <Gtk/Gtk/Label.h>

TYPE(T, Gtk$Gtk$Misc$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_label_new((Count == 1) ? Lang$String$flatten(Args[0].Val) : 0);
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};

METHOD("Text", TYP, T, TYP, Lang$String$T) {
	GtkLabel *Label = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_label_set_text(Label, Lang$String$flatten(Args[1].Val));
	Result->Arg = Args[1];
	return SUCCESS;
};
