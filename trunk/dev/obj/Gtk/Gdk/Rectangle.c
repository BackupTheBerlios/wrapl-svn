#include <Gtk/Gdk/Rectangle.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_rectangle_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Intersect", TYP, T, TYP, Gtk$Gdk$Rectangle$T, TYP, Gtk$Gdk$Rectangle$T) {
	GdkRectangle * self= &((Gtk$Gdk$Rectangle_t *)Args[0].Val)->Value;
	GdkRectangle * src2= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	GdkRectangle * dest= &((Gtk$Gdk$Rectangle_t *)Args[2].Val)->Value;
	int result = gdk_rectangle_intersect(self, src2, dest);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Union", TYP, T, TYP, Gtk$Gdk$Rectangle$T, TYP, Gtk$Gdk$Rectangle$T) {
	GdkRectangle * self= &((Gtk$Gdk$Rectangle_t *)Args[0].Val)->Value;
	GdkRectangle * src2= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	GdkRectangle * dest= &((Gtk$Gdk$Rectangle_t *)Args[2].Val)->Value;
	gdk_rectangle_union(self, src2, dest);
	return SUCCESS;
};

