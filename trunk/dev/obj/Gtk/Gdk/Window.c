#include <Gtk/Gdk/Window.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 16
#include <Gtk/Gdk/Display.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/Gdk/Geometry.h>
#include <Gtk/Gdk/FilterFunc.h>
#include <Gtk/Gdk/WindowEdge.h>
#include <Gtk/Gdk/WindowType.h>
#include <Gtk/Gdk/WindowAttr.h>
#include <Gtk/Gdk/WindowTypeHint.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Gtk/Gdk/Region.h>
#include <Gtk/Gdk/Bitmap.h>
#include <Gtk/Gdk/Pixmap.h>
#include <Gtk/Gdk/Cursor.h>
#include <Gtk/Gdk/Window.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 3) {
	GdkWindow * parent = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindowAttr * attributes= &((Gtk$Gdk$WindowAttr_t *)Args[1].Val)->Value;
	int attributes_mask = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkWindow * result = gdk_window_new(parent, attributes, attributes_mask);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(AtPointer, 2) {
	gint* win_x = 0;
	gint* win_y = 0;
	GdkWindow * result = gdk_window_at_pointer(win_x, win_y);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ConstrainSize, 6) {
	GdkGeometry * geometry= &((Gtk$Gdk$Geometry_t *)Args[0].Val)->Value;
	int flags = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gint* new_width = 0;
	gint* new_height = 0;
	gdk_window_constrain_size(geometry, flags, width, height, new_width, new_height);
	return SUCCESS;
};

GLOBAL_FUNCTION(ForeignNew, 1) {
	GdkNativeWindow anid = 0;
	GdkWindow * result = gdk_window_foreign_new(anid);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ForeignNewForDisplay, 2) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkNativeWindow anid = 0;
	GdkWindow * result = gdk_window_foreign_new_for_display(display, anid);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetToplevels, 0) {
	GList * result = gdk_window_get_toplevels();
	if (result) {
		int _length = 1;
		GList *node = result;
		node->data = Gtk$GObject$Object$to_riva(node->data);
		while (node->next) {
			node = node->next;
			node->data = Gtk$GObject$Object$to_riva(node->data);
			_length++;
		};
		Std$List_t *list = new(Std$List_t);
		list->Type = Std$List$T;
		list->Cache = list->Head = result;
		list->Tail = node;
		list->Length = _length;
		list->Index = 1;
		list->Access = 4;
		Result->Val = list;
	} else {
		Result->Val = Std$List$new(0);
	};
	return SUCCESS;
};

GLOBAL_FUNCTION(Lookup, 1) {
	GdkNativeWindow anid = 0;
	GdkWindow * result = gdk_window_lookup(anid);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(LookupForDisplay, 2) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkNativeWindow anid = 0;
	GdkWindow * result = gdk_window_lookup_for_display(display, anid);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ProcessAllUpdates, 0) {
	gdk_window_process_all_updates();
	return SUCCESS;
};

GLOBAL_FUNCTION(SetDebugUpdates, 1) {
	int setting = Args[0].Val == $true;
	gdk_window_set_debug_updates(setting);
	return SUCCESS;
};

METHOD("AddFilter", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkFilterFunc function = Gtk$Gdk$FilterFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	gdk_window_add_filter(self, function, data);
	return SUCCESS;
};

METHOD("BeginMoveDrag", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int button = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int root_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int root_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int timestamp = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gdk_window_begin_move_drag(self, button, root_x, root_y, timestamp);
	return SUCCESS;
};

METHOD("BeginPaintRect", TYP, T, TYP, Gtk$Gdk$Rectangle$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRectangle * rectangle= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	gdk_window_begin_paint_rect(self, rectangle);
	return SUCCESS;
};

METHOD("BeginPaintRegion", TYP, T, TYP, Gtk$Gdk$Region$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRegion * region= ((Gtk$Gdk$Region_t *)Args[1].Val)->Value;
	gdk_window_begin_paint_region(self, region);
	return SUCCESS;
};

METHOD("BeginResizeDrag", TYP, T, TYP, Gtk$Gdk$WindowEdge$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindowEdge edge = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int button = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int root_x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int root_y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int timestamp = ((Std$Integer_smallt *)Args[5].Val)->Value;
	gdk_window_begin_resize_drag(self, edge, button, root_x, root_y, timestamp);
	return SUCCESS;
};

METHOD("Clear", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_clear(self);
	return SUCCESS;
};

METHOD("ClearArea", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gdk_window_clear_area(self, x, y, width, height);
	return SUCCESS;
};

METHOD("ClearAreaE", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gdk_window_clear_area_e(self, x, y, width, height);
	return SUCCESS;
};

METHOD("ConfigureFinished", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_configure_finished(self);
	return SUCCESS;
};

METHOD("Deiconify", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_deiconify(self);
	return SUCCESS;
};

METHOD("Destroy", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_destroy(self);
	return SUCCESS;
};

METHOD("EnableSynchronizedConfigure", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_enable_synchronized_configure(self);
	return SUCCESS;
};

METHOD("EndPaint", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_end_paint(self);
	return SUCCESS;
};

METHOD("Focus", TYP, T, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int timestamp = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_window_focus(self, timestamp);
	return SUCCESS;
};

METHOD("FreezeUpdates", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_freeze_updates(self);
	return SUCCESS;
};

METHOD("Fullscreen", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_fullscreen(self);
	return SUCCESS;
};

METHOD("GetChildren", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList * result = gdk_window_get_children(self);
	if (result) {
		int _length = 1;
		GList *node = result;
		node->data = Gtk$GObject$Object$to_riva(node->data);
		while (node->next) {
			node = node->next;
			node->data = Gtk$GObject$Object$to_riva(node->data);
			_length++;
		};
		Std$List_t *list = new(Std$List_t);
		list->Type = Std$List$T;
		list->Cache = list->Head = result;
		list->Tail = node;
		list->Length = _length;
		list->Index = 1;
		list->Access = 4;
		Result->Val = list;
	} else {
		Result->Val = Std$List$new(0);
	};
	return SUCCESS;
};

METHOD("GetDecorations", TYP, T, TYP, Std$Object$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWMDecoration* decorations = 0;
	int result = gdk_window_get_decorations(self, decorations);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetDeskrelativeOrigin", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* x = 0;
	gint* y = 0;
	int result = gdk_window_get_deskrelative_origin(self, x, y);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetEvents", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_window_get_events(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetFrameExtents", TYP, T, TYP, Gtk$Gdk$Rectangle$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRectangle * rect= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	gdk_window_get_frame_extents(self, rect);
	return SUCCESS;
};

METHOD("GetGeometry", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* x = 0;
	gint* y = 0;
	gint* width = 0;
	gint* height = 0;
	gint* depth = 0;
	gdk_window_get_geometry(self, x, y, width, height, depth);
	return SUCCESS;
};

METHOD("GetGroup", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * result = gdk_window_get_group(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetInternalPaintInfo", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDrawable** real_drawable = 0;
	gint* x_offset = 0;
	gint* y_offset = 0;
	gdk_window_get_internal_paint_info(self, real_drawable, x_offset, y_offset);
	return SUCCESS;
};

METHOD("GetOrigin", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* x = 0;
	gint* y = 0;
	int result = gdk_window_get_origin(self, x, y);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetParent", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * result = gdk_window_get_parent(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPointer", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* x = 0;
	gint* y = 0;
	GdkModifierType* mask = 0;
	GdkWindow * result = gdk_window_get_pointer(self, x, y, mask);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPosition", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* x = 0;
	gint* y = 0;
	gdk_window_get_position(self, x, y);
	return SUCCESS;
};

METHOD("GetRootOrigin", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* x = 0;
	gint* y = 0;
	gdk_window_get_root_origin(self, x, y);
	return SUCCESS;
};

METHOD("GetState", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_window_get_state(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetToplevel", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * result = gdk_window_get_toplevel(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetTypeHint", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindowTypeHint result = gdk_window_get_type_hint(self);
	Gtk$Gdk$WindowTypeHint_t *_result = new(Gtk$Gdk$WindowTypeHint_t);
	_result->Type = Gtk$Gdk$WindowTypeHint$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetUpdateArea", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRegion * result = gdk_window_get_update_area(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetUserData", TYP, T, TYP, Std$Object$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gpointer* data = 0;
	gdk_window_get_user_data(self, data);
	return SUCCESS;
};

METHOD("GetWindowType", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindowType result = gdk_window_get_window_type(self);
	Gtk$Gdk$WindowType_t *_result = new(Gtk$Gdk$WindowType_t);
	_result->Type = Gtk$Gdk$WindowType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("Hide", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_hide(self);
	return SUCCESS;
};

METHOD("Iconify", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_iconify(self);
	return SUCCESS;
};

METHOD("InputShapeCombineMask", TYP, T, TYP, Gtk$Gdk$Bitmap$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_window_input_shape_combine_mask(self, mask, x, y);
	return SUCCESS;
};

METHOD("InputShapeCombineRegion", TYP, T, TYP, Gtk$Gdk$Region$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRegion * shape_region= ((Gtk$Gdk$Region_t *)Args[1].Val)->Value;
	int offset_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int offset_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_window_input_shape_combine_region(self, shape_region, offset_x, offset_y);
	return SUCCESS;
};

METHOD("InvalidateRect", TYP, T, TYP, Gtk$Gdk$Rectangle$T, TYP, Std$Symbol$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRectangle * rect= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	int invalidate_children = Args[2].Val == $true;
	gdk_window_invalidate_rect(self, rect, invalidate_children);
	return SUCCESS;
};

METHOD("InvalidateRegion", TYP, T, TYP, Gtk$Gdk$Region$T, TYP, Std$Symbol$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRegion * region= ((Gtk$Gdk$Region_t *)Args[1].Val)->Value;
	int invalidate_children = Args[2].Val == $true;
	gdk_window_invalidate_region(self, region, invalidate_children);
	return SUCCESS;
};

METHOD("IsViewable", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_window_is_viewable(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsVisible", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_window_is_visible(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Lower", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_lower(self);
	return SUCCESS;
};

METHOD("Maximize", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_maximize(self);
	return SUCCESS;
};

METHOD("MergeChildInputShapes", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_merge_child_input_shapes(self);
	return SUCCESS;
};

METHOD("MergeChildShapes", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_merge_child_shapes(self);
	return SUCCESS;
};

METHOD("Move", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_window_move(self, x, y);
	return SUCCESS;
};

METHOD("MoveRegion", TYP, T, TYP, Gtk$Gdk$Region$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRegion * region= ((Gtk$Gdk$Region_t *)Args[1].Val)->Value;
	int dx = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int dy = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_window_move_region(self, region, dx, dy);
	return SUCCESS;
};

METHOD("MoveResize", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gdk_window_move_resize(self, x, y, width, height);
	return SUCCESS;
};

METHOD("PeekChildren", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* result = gdk_window_peek_children(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("ProcessUpdates", TYP, T, TYP, Std$Symbol$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int update_children = Args[1].Val == $true;
	gdk_window_process_updates(self, update_children);
	return SUCCESS;
};

METHOD("Raise", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_raise(self);
	return SUCCESS;
};

METHOD("RegisterDnd", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_register_dnd(self);
	return SUCCESS;
};

METHOD("RemoveFilter", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkFilterFunc function = Gtk$Gdk$FilterFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	gdk_window_remove_filter(self, function, data);
	return SUCCESS;
};

METHOD("Reparent", TYP, T, TYP, Gtk$Gdk$Window$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * new_parent = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_window_reparent(self, new_parent, x, y);
	return SUCCESS;
};

METHOD("Resize", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_window_resize(self, width, height);
	return SUCCESS;
};

METHOD("Scroll", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int dx = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int dy = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_window_scroll(self, dx, dy);
	return SUCCESS;
};

METHOD("SetAcceptFocus", TYP, T, TYP, Std$Symbol$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int accept_focus = Args[1].Val == $true;
	gdk_window_set_accept_focus(self, accept_focus);
	return SUCCESS;
};

METHOD("SetBackPixmap", TYP, T, TYP, Gtk$Gdk$Pixmap$T, TYP, Std$Symbol$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixmap * pixmap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int parent_relative = Args[2].Val == $true;
	gdk_window_set_back_pixmap(self, pixmap, parent_relative);
	return SUCCESS;
};

METHOD("SetBackground", TYP, T, TYP, Gtk$Gdk$Color$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	gdk_window_set_background(self, color);
	return SUCCESS;
};

METHOD("SetChildInputShapes", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_set_child_input_shapes(self);
	return SUCCESS;
};

METHOD("SetChildShapes", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_set_child_shapes(self);
	return SUCCESS;
};

METHOD("SetCursor", TYP, T, TYP, Gtk$Gdk$Cursor$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkCursor * cursor= ((Gtk$Gdk$Cursor_t *)Args[1].Val)->Value;
	gdk_window_set_cursor(self, cursor);
	return SUCCESS;
};

METHOD("SetDecorations", TYP, T, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int decorations = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_window_set_decorations(self, decorations);
	return SUCCESS;
};

METHOD("SetEvents", TYP, T, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int event_mask = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_window_set_events(self, event_mask);
	return SUCCESS;
};

METHOD("SetFocusOnMap", TYP, T, TYP, Std$Symbol$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int focus_on_map = Args[1].Val == $true;
	gdk_window_set_focus_on_map(self, focus_on_map);
	return SUCCESS;
};

METHOD("SetFunctions", TYP, T, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int functions = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_window_set_functions(self, functions);
	return SUCCESS;
};

METHOD("SetGeometryHints", TYP, T, TYP, Gtk$Gdk$Geometry$T, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGeometry * geometry= &((Gtk$Gdk$Geometry_t *)Args[1].Val)->Value;
	int geom_mask = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_window_set_geometry_hints(self, geometry, geom_mask);
	return SUCCESS;
};

METHOD("SetGroup", TYP, T, TYP, Gtk$Gdk$Window$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * leader = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdk_window_set_group(self, leader);
	return SUCCESS;
};

METHOD("SetHints", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int min_width = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int min_height = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int max_width = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int max_height = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int flags = ((Std$Integer_smallt *)Args[7].Val)->Value;
	gdk_window_set_hints(self, x, y, min_width, min_height, max_width, max_height, flags);
	return SUCCESS;
};

METHOD("SetIcon", TYP, T, TYP, Gtk$Gdk$Window$T, TYP, Gtk$Gdk$Pixmap$T, TYP, Gtk$Gdk$Bitmap$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * icon_window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkPixmap * pixmap = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	gdk_window_set_icon(self, icon_window, pixmap, mask);
	return SUCCESS;
};

METHOD("SetIconList", TYP, T, TYP, Std$Object$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* pixbufs = 0;
	gdk_window_set_icon_list(self, pixbufs);
	return SUCCESS;
};

METHOD("SetIconName", TYP, T, TYP, Std$String$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	gdk_window_set_icon_name(self, name);
	return SUCCESS;
};

METHOD("SetKeepAbove", TYP, T, TYP, Std$Symbol$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gdk_window_set_keep_above(self, setting);
	return SUCCESS;
};

METHOD("SetKeepBelow", TYP, T, TYP, Std$Symbol$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gdk_window_set_keep_below(self, setting);
	return SUCCESS;
};

METHOD("SetModalHint", TYP, T, TYP, Std$Symbol$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int modal = Args[1].Val == $true;
	gdk_window_set_modal_hint(self, modal);
	return SUCCESS;
};

METHOD("SetOverrideRedirect", TYP, T, TYP, Std$Symbol$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int override_redirect = Args[1].Val == $true;
	gdk_window_set_override_redirect(self, override_redirect);
	return SUCCESS;
};

METHOD("SetRole", TYP, T, TYP, Std$String$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *role = Std$String$flatten(Args[1].Val);
	gdk_window_set_role(self, role);
	return SUCCESS;
};

METHOD("SetSkipPagerHint", TYP, T, TYP, Std$Symbol$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int skips_pager = Args[1].Val == $true;
	gdk_window_set_skip_pager_hint(self, skips_pager);
	return SUCCESS;
};

METHOD("SetSkipTaskbarHint", TYP, T, TYP, Std$Symbol$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int skips_taskbar = Args[1].Val == $true;
	gdk_window_set_skip_taskbar_hint(self, skips_taskbar);
	return SUCCESS;
};

METHOD("SetStaticGravities", TYP, T, TYP, Std$Symbol$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int use_static = Args[1].Val == $true;
	int result = gdk_window_set_static_gravities(self, use_static);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetTitle", TYP, T, TYP, Std$String$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *title = Std$String$flatten(Args[1].Val);
	gdk_window_set_title(self, title);
	return SUCCESS;
};

METHOD("SetTransientFor", TYP, T, TYP, Gtk$Gdk$Window$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * parent = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdk_window_set_transient_for(self, parent);
	return SUCCESS;
};

METHOD("SetTypeHint", TYP, T, TYP, Gtk$Gdk$WindowTypeHint$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindowTypeHint hint = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_window_set_type_hint(self, hint);
	return SUCCESS;
};

METHOD("SetUrgencyHint", TYP, T, TYP, Std$Symbol$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int urgent = Args[1].Val == $true;
	gdk_window_set_urgency_hint(self, urgent);
	return SUCCESS;
};

METHOD("SetUserData", TYP, T, TYP, Std$Address$T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	void *user_data = ((Std$Address_t *)Args[1].Val)->Value;
	gdk_window_set_user_data(self, user_data);
	return SUCCESS;
};

METHOD("ShapeCombineMask", TYP, T, TYP, Gtk$Gdk$Bitmap$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_window_shape_combine_mask(self, mask, x, y);
	return SUCCESS;
};

METHOD("ShapeCombineRegion", TYP, T, TYP, Gtk$Gdk$Region$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRegion * shape_region= ((Gtk$Gdk$Region_t *)Args[1].Val)->Value;
	int offset_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int offset_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_window_shape_combine_region(self, shape_region, offset_x, offset_y);
	return SUCCESS;
};

METHOD("Show", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_show(self);
	return SUCCESS;
};

METHOD("ShowUnraised", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_show_unraised(self);
	return SUCCESS;
};

METHOD("Stick", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_stick(self);
	return SUCCESS;
};

METHOD("ThawUpdates", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_thaw_updates(self);
	return SUCCESS;
};

METHOD("Unfullscreen", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_unfullscreen(self);
	return SUCCESS;
};

METHOD("Unmaximize", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_unmaximize(self);
	return SUCCESS;
};

METHOD("Unstick", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_unstick(self);
	return SUCCESS;
};

METHOD("Withdraw", TYP, T) {
	GdkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_window_withdraw(self);
	return SUCCESS;
};

