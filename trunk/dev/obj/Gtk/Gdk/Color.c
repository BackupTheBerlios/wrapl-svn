#include <Gtk/Gdk/Color.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Std/Boolean.h>
#include <Gtk/Gdk/Colormap.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(Alloc, 2) {
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	int result = gdk_color_alloc(colormap, color);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Black, 2) {
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	int result = gdk_color_black(colormap, color);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Change, 2) {
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	int result = gdk_color_change(colormap, color);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_color_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Parse, 2) {
	char *spec = Std$String$flatten(Args[0].Val);
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	int result = gdk_color_parse(spec, color);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(White, 2) {
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	int result = gdk_color_white(colormap, color);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GdkColor * self= &((Gtk$Gdk$Color_t *)Args[0].Val)->Value;
	GdkColor * result = gdk_color_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Equal", TYP, T, TYP, Gtk$Gdk$Color$T) {
	GdkColor * self= &((Gtk$Gdk$Color_t *)Args[0].Val)->Value;
	GdkColor * colorb= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	int result = gdk_color_equal(self, colorb);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	GdkColor * self= &((Gtk$Gdk$Color_t *)Args[0].Val)->Value;
	gdk_color_free(self);
	return SUCCESS;
};

METHOD("Hash", TYP, T) {
	GdkColor * self= &((Gtk$Gdk$Color_t *)Args[0].Val)->Value;
	int result = gdk_color_hash(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

