#include <Gtk/Gdk/Screen.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 10
#include <Gtk/Gdk/Colormap.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Gtk/Gdk/Visual.h>
#include <Gtk/Gdk/Screen.h>
#include <Gtk/Gdk/Window.h>
#include <Gtk/GObject/Value.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetDefault, 0) {
	GdkScreen * result = gdk_screen_get_default();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_screen_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Height, 0) {
	int result = gdk_screen_height();
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(HeightMm, 0) {
	int result = gdk_screen_height_mm();
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Width, 0) {
	int result = gdk_screen_width();
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(WidthMm, 0) {
	int result = gdk_screen_width_mm();
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("BroadcastClientMessage", TYP, T, TYP, Std$Object$T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkEvent* event = 0;
	gdk_screen_broadcast_client_message(self, event);
	return SUCCESS;
};

METHOD("GetActiveWindow", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * result = gdk_screen_get_active_window(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetDefaultColormap", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * result = gdk_screen_get_default_colormap(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetDisplay", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDisplay * result = gdk_screen_get_display(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetFontOptions", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const cairo_font_options_t* result = gdk_screen_get_font_options(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetHeight", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_screen_get_height(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetHeightMm", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_screen_get_height_mm(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetMonitorAtPoint", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gdk_screen_get_monitor_at_point(self, x, y);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetMonitorAtWindow", TYP, T, TYP, Gtk$Gdk$Window$T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gdk_screen_get_monitor_at_window(self, window);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetMonitorGeometry", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$Rectangle$T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int monitor_num = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkRectangle * dest= &((Gtk$Gdk$Rectangle_t *)Args[2].Val)->Value;
	gdk_screen_get_monitor_geometry(self, monitor_num, dest);
	return SUCCESS;
};

METHOD("GetNMonitors", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_screen_get_n_monitors(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetNumber", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_screen_get_number(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetResolution", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double result = gdk_screen_get_resolution(self);
	Result->Val = Std$Real$new(result);
	return SUCCESS;
};

METHOD("GetRgbColormap", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * result = gdk_screen_get_rgb_colormap(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetRgbVisual", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkVisual * result = gdk_screen_get_rgb_visual(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetRgbaColormap", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * result = gdk_screen_get_rgba_colormap(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetRgbaVisual", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkVisual * result = gdk_screen_get_rgba_visual(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetRootWindow", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * result = gdk_screen_get_root_window(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetSetting", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	GValue value[1];
	Gtk$GObject$Value$to_gtk(Args[2].Val, value);
	int result = gdk_screen_get_setting(self, name, value);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSystemColormap", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * result = gdk_screen_get_system_colormap(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetSystemVisual", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkVisual * result = gdk_screen_get_system_visual(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetToplevelWindows", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList * result = gdk_screen_get_toplevel_windows(self);
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

METHOD("GetWidth", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_screen_get_width(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetWidthMm", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_screen_get_width_mm(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetWindowStack", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList * result = gdk_screen_get_window_stack(self);
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

METHOD("IsComposited", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_screen_is_composited(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ListVisuals", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList * result = gdk_screen_list_visuals(self);
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

METHOD("MakeDisplayName", TYP, T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char * result = gdk_screen_make_display_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("SetDefaultColormap", TYP, T, TYP, Gtk$Gdk$Colormap$T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gdk_screen_set_default_colormap(self, colormap);
	return SUCCESS;
};

METHOD("SetFontOptions", TYP, T, TYP, Std$Object$T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const cairo_font_options_t* options = 0;
	gdk_screen_set_font_options(self, options);
	return SUCCESS;
};

METHOD("SetResolution", TYP, T, TYP, Std$Real$T) {
	GdkScreen * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	double dpi = ((Std$Real_t *)Args[1].Val)->Value;
	gdk_screen_set_resolution(self, dpi);
	return SUCCESS;
};

