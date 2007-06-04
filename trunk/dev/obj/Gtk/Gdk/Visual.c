#include <Gtk/Gdk/Visual.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/VisualType.h>
#include <Gtk/Gdk/Visual.h>
#include <Gtk/Gdk/Screen.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetBest, 0) {
	GdkVisual * result = gdk_visual_get_best();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetBestDepth, 0) {
	int result = gdk_visual_get_best_depth();
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetBestType, 0) {
	GdkVisualType result = gdk_visual_get_best_type();
	Gtk$Gdk$VisualType_t *_result = new(Gtk$Gdk$VisualType_t);
	_result->Type = Gtk$Gdk$VisualType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetBestWithBoth, 2) {
	int depth = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GdkVisualType visual_type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkVisual * result = gdk_visual_get_best_with_both(depth, visual_type);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetBestWithDepth, 1) {
	int depth = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GdkVisual * result = gdk_visual_get_best_with_depth(depth);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetBestWithType, 1) {
	GdkVisualType visual_type = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GdkVisual * result = gdk_visual_get_best_with_type(visual_type);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetSystem, 0) {
	GdkVisual * result = gdk_visual_get_system();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_visual_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetScreen", TYP, T) {
	GdkVisual * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkScreen * result = gdk_visual_get_screen(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

