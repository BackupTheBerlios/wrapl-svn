#include <Gtk/Gtk/Window.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 16
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Gravity.h>
#include <Gtk/Gtk/WindowGroup.h>
#include <Gtk/Gdk/Geometry.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/EventKey.h>
#include <Gtk/Gdk/WindowEdge.h>
#include <Gtk/Gtk/WindowType.h>
#include <Gtk/Gtk/AccelGroup.h>
#include <Gtk/Gdk/WindowTypeHint.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Gtk/Gdk/Screen.h>
#include <Gtk/Gtk/Widget.h>
#include <Gtk/Gtk/Window.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/WindowPosition.h>
/***********************************/
TYPE(T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	GtkWindowType type = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GtkWindow * result = gtk_window_new(type);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetDefaultIconList, 0) {
	GList * result = gtk_window_get_default_icon_list();
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

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_window_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ListToplevels, 0) {
	GList * result = gtk_window_list_toplevels();
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

GLOBAL_FUNCTION(SetAutoStartupNotification, 1) {
	int setting = Args[0].Val == $true;
	gtk_window_set_auto_startup_notification(setting);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetDefaultIcon, 1) {
	GdkPixbuf * icon = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_window_set_default_icon(icon);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetDefaultIconFromFile, 2) {
	char *filename = Std$String$flatten(Args[0].Val);
	GError** err = 0;
	int result = gtk_window_set_default_icon_from_file(filename, err);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(SetDefaultIconList, 1) {
	GList* list = 0;
	gtk_window_set_default_icon_list(list);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetDefaultIconName, 1) {
	char *name = Std$String$flatten(Args[0].Val);
	gtk_window_set_default_icon_name(name);
	return SUCCESS;
};

METHOD("ActivateDefault", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_window_activate_default(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ActivateFocus", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_window_activate_focus(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ActivateKey", TYP, T, TYP, Gtk$Gdk$EventKey$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkEventKey * event= &((Gtk$Gdk$EventKey_t *)Args[1].Val)->Value;
	int result = gtk_window_activate_key(self, event);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("AddAccelGroup", TYP, T, TYP, Gtk$Gtk$AccelGroup$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAccelGroup * accel_group = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_window_add_accel_group(self, accel_group);
	return SUCCESS;
};

METHOD("AddEmbeddedXid", TYP, T, TYP, Std$Integer$SmallT) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int xid = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_window_add_embedded_xid(self, xid);
	return SUCCESS;
};

METHOD("AddMnemonic", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$Widget$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int keyval = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkWidget * target = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_window_add_mnemonic(self, keyval, target);
	return SUCCESS;
};

METHOD("BeginMoveDrag", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int button = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int root_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int root_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int timestamp = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_window_begin_move_drag(self, button, root_x, root_y, timestamp);
	return SUCCESS;
};

METHOD("BeginResizeDrag", TYP, T, TYP, Gtk$Gdk$WindowEdge$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindowEdge edge = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int button = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int root_x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int root_y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int timestamp = ((Std$Integer_smallt *)Args[5].Val)->Value;
	gtk_window_begin_resize_drag(self, edge, button, root_x, root_y, timestamp);
	return SUCCESS;
};

METHOD("Deiconify", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_window_deiconify(self);
	return SUCCESS;
};

METHOD("Fullscreen", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_window_fullscreen(self);
	return SUCCESS;
};

METHOD("GetAcceptFocus", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_window_get_accept_focus(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetDecorated", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_window_get_decorated(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetDefaultSize", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* width = 0;
	gint* height = 0;
	gtk_window_get_default_size(self, width, height);
	return SUCCESS;
};

METHOD("GetDeletable", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_window_get_deletable(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetDestroyWithParent", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_window_get_destroy_with_parent(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetFocus", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_window_get_focus(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetFocusOnMap", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_window_get_focus_on_map(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetFrameDimensions", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* left = 0;
	gint* top = 0;
	gint* right = 0;
	gint* bottom = 0;
	gtk_window_get_frame_dimensions(self, left, top, right, bottom);
	return SUCCESS;
};

METHOD("GetGravity", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGravity result = gtk_window_get_gravity(self);
	Gtk$Gdk$Gravity_t *_result = new(Gtk$Gdk$Gravity_t);
	_result->Type = Gtk$Gdk$Gravity$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetGroup", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWindowGroup * result = gtk_window_get_group(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetHasFrame", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_window_get_has_frame(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetIcon", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * result = gtk_window_get_icon(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetIconList", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList * result = gtk_window_get_icon_list(self);
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

METHOD("GetIconName", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_window_get_icon_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetMnemonicModifier", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_window_get_mnemonic_modifier(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetModal", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_window_get_modal(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetPosition", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* root_x = 0;
	gint* root_y = 0;
	gtk_window_get_position(self, root_x, root_y);
	return SUCCESS;
};

METHOD("GetResizable", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_window_get_resizable(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetRole", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_window_get_role(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetScreen", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkScreen * result = gtk_window_get_screen(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetSize", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* width = 0;
	gint* height = 0;
	gtk_window_get_size(self, width, height);
	return SUCCESS;
};

METHOD("GetSkipPagerHint", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_window_get_skip_pager_hint(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSkipTaskbarHint", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_window_get_skip_taskbar_hint(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetTitle", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_window_get_title(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetTransientFor", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWindow * result = gtk_window_get_transient_for(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetTypeHint", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindowTypeHint result = gtk_window_get_type_hint(self);
	Gtk$Gdk$WindowTypeHint_t *_result = new(Gtk$Gdk$WindowTypeHint_t);
	_result->Type = Gtk$Gdk$WindowTypeHint$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetUrgencyHint", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_window_get_urgency_hint(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("HasToplevelFocus", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_window_has_toplevel_focus(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Iconify", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_window_iconify(self);
	return SUCCESS;
};

METHOD("IsActive", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_window_is_active(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Maximize", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_window_maximize(self);
	return SUCCESS;
};

METHOD("MnemonicActivate", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int keyval = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int modifier = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gtk_window_mnemonic_activate(self, keyval, modifier);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Move", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_window_move(self, x, y);
	return SUCCESS;
};

METHOD("ParseGeometry", TYP, T, TYP, Std$String$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *geometry = Std$String$flatten(Args[1].Val);
	int result = gtk_window_parse_geometry(self, geometry);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Present", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_window_present(self);
	return SUCCESS;
};

METHOD("PresentWithTime", TYP, T, TYP, Std$Integer$SmallT) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int timestamp = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_window_present_with_time(self, timestamp);
	return SUCCESS;
};

METHOD("PropagateKeyEvent", TYP, T, TYP, Gtk$Gdk$EventKey$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkEventKey * event= &((Gtk$Gdk$EventKey_t *)Args[1].Val)->Value;
	int result = gtk_window_propagate_key_event(self, event);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("RemoveAccelGroup", TYP, T, TYP, Gtk$Gtk$AccelGroup$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAccelGroup * accel_group = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_window_remove_accel_group(self, accel_group);
	return SUCCESS;
};

METHOD("RemoveEmbeddedXid", TYP, T, TYP, Std$Integer$SmallT) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int xid = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_window_remove_embedded_xid(self, xid);
	return SUCCESS;
};

METHOD("RemoveMnemonic", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$Widget$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int keyval = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkWidget * target = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_window_remove_mnemonic(self, keyval, target);
	return SUCCESS;
};

METHOD("ReshowWithInitialSize", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_window_reshow_with_initial_size(self);
	return SUCCESS;
};

METHOD("Resize", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_window_resize(self, width, height);
	return SUCCESS;
};

METHOD("SetAcceptFocus", TYP, T, TYP, Std$Symbol$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_window_set_accept_focus(self, setting);
	return SUCCESS;
};

METHOD("SetDecorated", TYP, T, TYP, Std$Symbol$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_window_set_decorated(self, setting);
	return SUCCESS;
};

METHOD("SetDefault", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * default_widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_window_set_default(self, default_widget);
	return SUCCESS;
};

METHOD("SetDefaultSize", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_window_set_default_size(self, width, height);
	return SUCCESS;
};

METHOD("SetDeletable", TYP, T, TYP, Std$Symbol$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_window_set_deletable(self, setting);
	return SUCCESS;
};

METHOD("SetDestroyWithParent", TYP, T, TYP, Std$Symbol$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_window_set_destroy_with_parent(self, setting);
	return SUCCESS;
};

METHOD("SetFocus", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * focus = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_window_set_focus(self, focus);
	return SUCCESS;
};

METHOD("SetFocusOnMap", TYP, T, TYP, Std$Symbol$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_window_set_focus_on_map(self, setting);
	return SUCCESS;
};

METHOD("SetFrameDimensions", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int left = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int top = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int right = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int bottom = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_window_set_frame_dimensions(self, left, top, right, bottom);
	return SUCCESS;
};

METHOD("SetGeometryHints", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gdk$Geometry$T, TYP, Std$Integer$SmallT) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * geometry_widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkGeometry * geometry= &((Gtk$Gdk$Geometry_t *)Args[2].Val)->Value;
	int geom_mask = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_window_set_geometry_hints(self, geometry_widget, geometry, geom_mask);
	return SUCCESS;
};

METHOD("SetGravity", TYP, T, TYP, Gtk$Gdk$Gravity$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkGravity gravity = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_window_set_gravity(self, gravity);
	return SUCCESS;
};

METHOD("SetHasFrame", TYP, T, TYP, Std$Symbol$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_window_set_has_frame(self, setting);
	return SUCCESS;
};

METHOD("SetIcon", TYP, T, TYP, Gtk$Gdk$Pixbuf$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * icon = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_window_set_icon(self, icon);
	return SUCCESS;
};

METHOD("SetIconFromFile", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *filename = Std$String$flatten(Args[1].Val);
	GError** err = 0;
	int result = gtk_window_set_icon_from_file(self, filename, err);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetIconList", TYP, T, TYP, Std$Object$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* list = 0;
	gtk_window_set_icon_list(self, list);
	return SUCCESS;
};

METHOD("SetIconName", TYP, T, TYP, Std$String$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	gtk_window_set_icon_name(self, name);
	return SUCCESS;
};

METHOD("SetKeepAbove", TYP, T, TYP, Std$Symbol$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_window_set_keep_above(self, setting);
	return SUCCESS;
};

METHOD("SetKeepBelow", TYP, T, TYP, Std$Symbol$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_window_set_keep_below(self, setting);
	return SUCCESS;
};

METHOD("SetMnemonicModifier", TYP, T, TYP, Std$Integer$SmallT) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int modifier = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_window_set_mnemonic_modifier(self, modifier);
	return SUCCESS;
};

METHOD("SetModal", TYP, T, TYP, Std$Symbol$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int modal = Args[1].Val == $true;
	gtk_window_set_modal(self, modal);
	return SUCCESS;
};

METHOD("SetPolicy", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int allow_shrink = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int allow_grow = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int auto_shrink = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_window_set_policy(self, allow_shrink, allow_grow, auto_shrink);
	return SUCCESS;
};

METHOD("SetPosition", TYP, T, TYP, Gtk$Gtk$WindowPosition$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWindowPosition position = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_window_set_position(self, position);
	return SUCCESS;
};

METHOD("SetResizable", TYP, T, TYP, Std$Symbol$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int resizable = Args[1].Val == $true;
	gtk_window_set_resizable(self, resizable);
	return SUCCESS;
};

METHOD("SetRole", TYP, T, TYP, Std$String$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *role = Std$String$flatten(Args[1].Val);
	gtk_window_set_role(self, role);
	return SUCCESS;
};

METHOD("SetScreen", TYP, T, TYP, Gtk$Gdk$Screen$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_window_set_screen(self, screen);
	return SUCCESS;
};

METHOD("SetSkipPagerHint", TYP, T, TYP, Std$Symbol$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_window_set_skip_pager_hint(self, setting);
	return SUCCESS;
};

METHOD("SetSkipTaskbarHint", TYP, T, TYP, Std$Symbol$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_window_set_skip_taskbar_hint(self, setting);
	return SUCCESS;
};

METHOD("SetTitle", TYP, T, TYP, Std$String$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *title = Std$String$flatten(Args[1].Val);
	gtk_window_set_title(self, title);
	return SUCCESS;
};

METHOD("SetTransientFor", TYP, T, TYP, Gtk$Gtk$Window$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWindow * parent = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_window_set_transient_for(self, parent);
	return SUCCESS;
};

METHOD("SetTypeHint", TYP, T, TYP, Gtk$Gdk$WindowTypeHint$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindowTypeHint hint = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_window_set_type_hint(self, hint);
	return SUCCESS;
};

METHOD("SetUrgencyHint", TYP, T, TYP, Std$Symbol$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_window_set_urgency_hint(self, setting);
	return SUCCESS;
};

METHOD("SetWmclass", TYP, T, TYP, Std$String$T, TYP, Std$String$T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *wmclass_name = Std$String$flatten(Args[1].Val);
	char *wmclass_class = Std$String$flatten(Args[2].Val);
	gtk_window_set_wmclass(self, wmclass_name, wmclass_class);
	return SUCCESS;
};

METHOD("Stick", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_window_stick(self);
	return SUCCESS;
};

METHOD("Unfullscreen", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_window_unfullscreen(self);
	return SUCCESS;
};

METHOD("Unmaximize", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_window_unmaximize(self);
	return SUCCESS;
};

METHOD("Unstick", TYP, T) {
	GtkWindow * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_window_unstick(self);
	return SUCCESS;
};

