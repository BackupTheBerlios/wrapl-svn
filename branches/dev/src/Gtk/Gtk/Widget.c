#include <Gtk/Gtk/Widget.h>

SYMBOL($TRUE, "TRUE");
SYMBOL($FALSE, "FALSE");

TYPE(T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
//	GtkWidget *Handle = gtk_widget_new();
//	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};

METHOD("show", TYP, T) {
	Gtk$GObject$Object_t *Widget = Args[0].Val;
	gtk_widget_show(Widget->Handle);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("show_all", TYP, T) {
	Gtk$GObject$Object_t *Widget = Args[0].Val;
	gtk_widget_show_all(Widget->Handle);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("hide", TYP, T) {
	Gtk$GObject$Object_t *Widget = Args[0].Val;
	gtk_widget_hide(Widget->Handle);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("hide_all", TYP, T) {
	Gtk$GObject$Object_t *Widget = Args[0].Val;
	gtk_widget_hide_all(Widget->Handle);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("activate", TYP, T) {
	Gtk$GObject$Object_t *Widget = Args[0].Val;
	Result->Arg = Args[0];
	return gtk_widget_activate(Widget->Handle) ? SUCCESS : FAILURE;
};

METHOD("is_focus", TYP, T) {
	Gtk$GObject$Object_t *Widget = Args[0].Val;
	Result->Val = gtk_widget_is_focus(Widget->Handle) ? $TRUE : $FALSE;
	return SUCCESS;
};


METHOD("grab_focus", TYP, T) {
	Gtk$GObject$Object_t *Widget = Args[0].Val;
	gtk_widget_grab_focus(Widget->Handle);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("grab_default", TYP, T) {
	Gtk$GObject$Object_t *Widget = Args[0].Val;
	gtk_widget_grab_default(Widget->Handle);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("set_sensitive", TYP, T, TYP, Lang$Symbol$T) {
	Gtk$GObject$Object_t *Widget = Args[0].Val;
	gtk_widget_set_sensitive(Widget->Handle, Args[1].Val == $TRUE);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("size_request", TYP, T, TYP, Lang$List$T) {
	GtkWidget *Widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	Lang$List_t *Alignment = Args[1].Val;
	if (Alignment->Length != 2) {
		Result->Val = Lang$String$new("Padding requires list of length 2");
		return MESSAGE;
	};
	int Width = ((Lang$Integer_smallt *)Alignment->Head->Value)->Value;
	int Height = ((Lang$Integer_smallt *)Alignment->Tail->Value)->Value;
	gtk_widget_set_size_request(Widget, Width, Height);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("size_request", TYP, T, TYP, Lang$Integer$SmallT, TYP, Lang$Integer$SmallT) {
	GtkWidget *Widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int Width = ((Lang$Integer_smallt *)Args[1].Val)->Value;
	int Height = ((Lang$Integer_smallt *)Args[2].Val)->Value;
	gtk_widget_set_size_request(Widget, Width, Height);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("size_request", TYP, T) {
	GtkWidget *Widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int Width, Height;
	gtk_widget_get_size_request(Widget, &Width, &Height);
	Result->Val = Lang$List$new(2, Lang$Integer$new_small(Width), Lang$Integer$new_small(Height));
	return SUCCESS;
};
