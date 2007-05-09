#include <Gtk/Gtk/Box.h>

TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

SYMBOL($TRUE, "TRUE");
SYMBOL($FALSE, "FALSE");

METHOD("push", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Lang$Symbol$T, TYP, Lang$Symbol$T, TYP, Lang$Integer$SmallT) {
	Gtk$GObject$Object_t *Box = Args[0].Val;
	Gtk$GObject$Object_t *Child = Args[1].Val;
	gboolean Expand = (Args[2].Val == $TRUE);
	gboolean Fill = (Args[3].Val == $TRUE);
	guint Padding = ((Lang$Integer_smallt *)Args[4].Val)->Value;
	gtk_box_pack_start(Box->Handle, Child->Handle, Expand, Fill, Padding);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("push", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	Gtk$GObject$Object_t *Box = Args[0].Val;
	Gtk$GObject$Object_t *Child = Args[1].Val;
	gtk_box_pack_start_defaults(Box->Handle, Child->Handle);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("put", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Lang$Symbol$T, TYP, Lang$Symbol$T, TYP, Lang$Integer$SmallT) {
	Gtk$GObject$Object_t *Box = Args[0].Val;
	Gtk$GObject$Object_t *Child = Args[1].Val;
	gboolean Expand = (Args[2].Val == $TRUE);
	gboolean Fill = (Args[3].Val == $TRUE);
	guint Padding = ((Lang$Integer_smallt *)Args[4].Val)->Value;
	gtk_box_pack_end(Box->Handle, Child->Handle, Expand, Fill, Padding);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("put", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	Gtk$GObject$Object_t *Box = Args[0].Val;
	Gtk$GObject$Object_t *Child = Args[1].Val;
	gtk_box_pack_end_defaults(Box->Handle, Child->Handle);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("homogeneous", TYP, T) {
	Gtk$GObject$Object_t *Box = Args[0].Val;
	Result->Val = gtk_box_get_homogeneous(Box->Handle) ? $TRUE : $FALSE;
	return SUCCESS;
};

METHOD("homogeneous", TYP, T, TYP, Lang$Symbol$T) {
	Gtk$GObject$Object_t *Box = Args[0].Val;
	gtk_box_set_homogeneous(Box->Handle, Args[1].Val == $TRUE);
	Result->Arg = Args[1];
	return SUCCESS;
};

METHOD("spacing", TYP, T) {
	Gtk$GObject$Object_t *Box = Args[0].Val;
	Result->Val = Lang$Integer$new_small(gtk_box_get_spacing(Box->Handle));
	return SUCCESS;
};

METHOD("spacing", TYP, T, TYP, Lang$Integer$SmallT) {
	Gtk$GObject$Object_t *Box = Args[0].Val;
	gtk_box_set_spacing(Box->Handle, ((Lang$Integer_smallt *)Args[1].Val)->Value);
	Result->Arg = Args[1];
	return SUCCESS;
};
