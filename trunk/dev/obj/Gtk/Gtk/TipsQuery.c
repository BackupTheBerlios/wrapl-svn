#include <Gtk/Gtk/TipsQuery.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/TipsQuery.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
/***********************************/
TYPE(T, Gtk$Gtk$Label$T, Gtk$Gtk$Misc$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkTipsQuery * result = gtk_tips_query_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_tips_query_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("SetCaller", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkTipsQuery * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * caller = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_tips_query_set_caller(self, caller);
	return SUCCESS;
};

METHOD("SetLabels", TYP, T, TYP, Std$String$T, TYP, Std$String$T) {
	GtkTipsQuery * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *label_inactive = Std$String$flatten(Args[1].Val);
	char *label_no_tip = Std$String$flatten(Args[2].Val);
	gtk_tips_query_set_labels(self, label_inactive, label_no_tip);
	return SUCCESS;
};

METHOD("StartQuery", TYP, T) {
	GtkTipsQuery * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tips_query_start_query(self);
	return SUCCESS;
};

METHOD("StopQuery", TYP, T) {
	GtkTipsQuery * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_tips_query_stop_query(self);
	return SUCCESS;
};

