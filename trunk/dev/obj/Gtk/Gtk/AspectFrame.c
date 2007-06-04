#include <Gtk/Gtk/AspectFrame.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Std/Boolean.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/AspectFrame.h>
/***********************************/
TYPE(T, Gtk$Gtk$Frame$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 5) {
	char *label = Std$String$flatten(Args[0].Val);
	double xalign = ((Std$Real_t *)Args[1].Val)->Value;
	double yalign = ((Std$Real_t *)Args[2].Val)->Value;
	double ratio = ((Std$Real_t *)Args[3].Val)->Value;
	int obey_child = Args[4].Val == $true;
	GtkAspectFrame * result = gtk_aspect_frame_new(label, xalign, yalign, ratio, obey_child);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_aspect_frame_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Set", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Symbol$T) {
	GtkAspectFrame * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double xalign = ((Std$Real_t *)Args[1].Val)->Value;
	double yalign = ((Std$Real_t *)Args[2].Val)->Value;
	double ratio = ((Std$Real_t *)Args[3].Val)->Value;
	int obey_child = Args[4].Val == $true;
	gtk_aspect_frame_set(self, xalign, yalign, ratio, obey_child);
	return SUCCESS;
};

