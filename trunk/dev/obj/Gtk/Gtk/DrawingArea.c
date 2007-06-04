#include <Gtk/Gtk/DrawingArea.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gtk/DrawingArea.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkDrawingArea * result = gtk_drawing_area_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_drawing_area_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Size", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkDrawingArea * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_drawing_area_size(self, width, height);
	return SUCCESS;
};

