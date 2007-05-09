#include <Gtk/Gtk/Button.h>

TYPE(T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkWidget *Handle = gtk_button_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithLabel, 1) {
	GtkWidget *Handle = gtk_button_new_with_label(Lang$String$flatten(Args[0].Val));
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithMnemonic, 1) {
	GtkWidget *Handle = gtk_button_new_with_mnemonic(Lang$String$flatten(Args[0].Val));
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromStock, 1) {
	GtkWidget *Handle = gtk_button_new_from_stock(Lang$String$flatten(Args[0].Val));
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};

METHOD("label", TYP, T) {
	GtkButton *Button = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	Result->Val = Lang$String$new(gtk_button_get_label(Button));
	return SUCCESS;
};

METHOD("label", TYP, T, TYP, Lang$String$T) {
	GtkButton *Button = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_button_set_label(Button, Lang$String$flatten(Args[1].Val));
	Result->Arg = Args[1];
	return SUCCESS;
};

METHOD("alignment", TYP, T, TYP, Lang$List$T) {
	GtkButton *Button = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	Lang$List_t *Alignment = Args[1].Val;
	if (Alignment->Length != 2) {
		Result->Val = Lang$String$new("Alignment requires list of length 2");
		return MESSAGE;
	};
	double XAlign = ((Lang$Real_t *)Alignment->Head->Value)->Value;
	double YAlign = ((Lang$Real_t *)Alignment->Tail->Value)->Value;
	gtk_button_set_alignment(Button, XAlign, YAlign);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("alignment", TYP, T, TYP, Lang$Real$T, TYP, Lang$Real$T) {
	GtkButton *Button = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double XAlign = ((Lang$Real_t *)Args[1].Val)->Value;
	double YAlign = ((Lang$Real_t *)Args[2].Val)->Value;
	gtk_button_set_alignment(Button, XAlign, YAlign);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("alignment", TYP, T) {
	GtkButton *Button = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double XAlign, YAlign;
	gtk_button_get_alignment(Button, &XAlign, &YAlign);
	Result->Val = Lang$List$new(2, Lang$Real$new(XAlign), Lang$Real$new(YAlign));
	return SUCCESS;
};

METHOD("image", TYP, T) {
	GtkButton *Button = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	Result->Val = Gtk$GObject$Object$gtk_to_riva(gtk_button_get_image(Button));
	return SUCCESS;
};

METHOD("image", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkButton *Button = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget *Image = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_button_set_image(Button, Image);
	Result->Arg = Args[0];
	return SUCCESS;
};
