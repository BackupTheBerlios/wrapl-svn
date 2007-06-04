#include <Gtk/Gdk/Colormap.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Std/Boolean.h>
#include <Gtk/Gdk/Colormap.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Visual.h>
#include <Gtk/Gdk/Screen.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 2) {
	GdkVisual * visual = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int allocate = Args[1].Val == $true;
	GdkColormap * result = gdk_colormap_new(visual, allocate);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetSystem, 0) {
	GdkColormap * result = gdk_colormap_get_system();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetSystemSize, 0) {
	int result = gdk_colormap_get_system_size();
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_colormap_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AllocColor", TYP, T, TYP, Gtk$Gdk$Color$T, TYP, Std$Symbol$T, TYP, Std$Symbol$T) {
	GdkColormap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	int writeable = Args[2].Val == $true;
	int best_match = Args[3].Val == $true;
	int result = gdk_colormap_alloc_color(self, color, writeable, best_match);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("AllocColors", TYP, T, TYP, Gtk$Gdk$Color$T, TYP, Std$Integer$SmallT, TYP, Std$Symbol$T, TYP, Std$Symbol$T, TYP, Std$Object$T) {
	GdkColormap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * colors= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	int ncolors = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int writeable = Args[3].Val == $true;
	int best_match = Args[4].Val == $true;
	gboolean* success = 0;
	int result = gdk_colormap_alloc_colors(self, colors, ncolors, writeable, best_match, success);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Change", TYP, T, TYP, Std$Integer$SmallT) {
	GdkColormap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int ncolors = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_colormap_change(self, ncolors);
	return SUCCESS;
};

METHOD("FreeColors", TYP, T, TYP, Gtk$Gdk$Color$T, TYP, Std$Integer$SmallT) {
	GdkColormap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * colors= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	int ncolors = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_colormap_free_colors(self, colors, ncolors);
	return SUCCESS;
};

METHOD("GetScreen", TYP, T) {
	GdkColormap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkScreen * result = gdk_colormap_get_screen(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetVisual", TYP, T) {
	GdkColormap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkVisual * result = gdk_colormap_get_visual(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("QueryColor", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$Color$T) {
	GdkColormap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int pixel = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkColor * result= &((Gtk$Gdk$Color_t *)Args[2].Val)->Value;
	gdk_colormap_query_color(self, pixel, result);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GdkColormap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * result = gdk_colormap_ref(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GdkColormap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_colormap_unref(self);
	return SUCCESS;
};

