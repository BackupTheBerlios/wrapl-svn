#include <Gtk/Gtk/Misc.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gtk/Misc.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_misc_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetAlignment", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkMisc * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gfloat* xalign = 0;
	gfloat* yalign = 0;
	gtk_misc_get_alignment(self, xalign, yalign);
	return SUCCESS;
};

METHOD("GetPadding", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkMisc * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* xpad = 0;
	gint* ypad = 0;
	gtk_misc_get_padding(self, xpad, ypad);
	return SUCCESS;
};

METHOD("SetAlignment", TYP, T, TYP, Std$Real$T, TYP, Std$Real$T) {
	GtkMisc * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double xalign = ((Std$Real_t *)Args[1].Val)->Value;
	double yalign = ((Std$Real_t *)Args[2].Val)->Value;
	gtk_misc_set_alignment(self, xalign, yalign);
	return SUCCESS;
};

METHOD("SetPadding", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkMisc * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int xpad = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int ypad = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_misc_set_padding(self, xpad, ypad);
	return SUCCESS;
};

