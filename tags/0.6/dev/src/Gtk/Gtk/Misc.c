#include <Gtk/Gtk/Misc.h>

TYPE(T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

METHOD("alignment", TYP, T, TYP, Lang$List$T) {
	GtkMisc *Misc = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	Lang$List_t *Alignment = Args[1].Val;
	if (Alignment->Length != 2) {
		Result->Val = Lang$String$new("Alignment requires list of length 2");
		return MESSAGE;
	};
	double XAlign = ((Lang$Real_t *)Alignment->Head->Value)->Value;
	double YAlign = ((Lang$Real_t *)Alignment->Tail->Value)->Value;
	gtk_misc_set_alignment(Misc, XAlign, YAlign);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("alignment", TYP, T, TYP, Lang$Real$T, TYP, Lang$Real$T) {
	GtkMisc *Misc = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double XAlign = ((Lang$Real_t *)Args[1].Val)->Value;
	double YAlign = ((Lang$Real_t *)Args[2].Val)->Value;
	gtk_misc_set_alignment(Misc, XAlign, YAlign);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("alignment", TYP, T) {
	GtkMisc *Misc = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double XAlign, YAlign;
	gtk_misc_get_alignment(Misc, &XAlign, &YAlign);
	Result->Val = Lang$List$new(2, Lang$Real$new(XAlign), Lang$Real$new(YAlign));
	return SUCCESS;
};

METHOD("padding", TYP, T, TYP, Lang$List$T) {
	GtkMisc *Misc = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	Lang$List_t *Alignment = Args[1].Val;
	if (Alignment->Length != 2) {
		Result->Val = Lang$String$new("Padding requires list of length 2");
		return MESSAGE;
	};
	int XPad = ((Lang$Integer_smallt *)Alignment->Head->Value)->Value;
	int YPad = ((Lang$Integer_smallt *)Alignment->Tail->Value)->Value;
	gtk_misc_set_padding(Misc, XPad, YPad);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("padding", TYP, T, TYP, Lang$Integer$SmallT, TYP, Lang$Integer$SmallT) {
	GtkMisc *Misc = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int XPad = ((Lang$Integer_smallt *)Args[1].Val)->Value;
	int YPad = ((Lang$Integer_smallt *)Args[2].Val)->Value;
	gtk_misc_set_padding(Misc, XPad, YPad);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("padding", TYP, T) {
	GtkMisc *Misc = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int XPad, YPad;
	gtk_misc_get_padding(Misc, &XPad, &YPad);
	Result->Val = Lang$List$new(2, Lang$Integer$new_small(XPad), Lang$Integer$new_small(XPad));
	return SUCCESS;
};
