#include <Gtk/Gtk/Arrow.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/Arrow.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/ShadowType.h>
#include <Gtk/Gtk/ArrowType.h>
/***********************************/
TYPE(T, Gtk$Gtk$Misc$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 2) {
	GtkArrowType arrow_type = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkArrow * result = gtk_arrow_new(arrow_type, shadow_type);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_arrow_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Set", TYP, T, TYP, Gtk$Gtk$ArrowType$T, TYP, Gtk$Gtk$ShadowType$T) {
	GtkArrow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkArrowType arrow_type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_arrow_set(self, arrow_type, shadow_type);
	return SUCCESS;
};

