#include <Gtk/Gtk/Widget.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 33
#include <Gtk/Gtk/RcStyle.h>
#include <Gtk/Gtk/TextDirection.h>
#include <Gtk/Gtk/Clipboard.h>
#include <Gtk/Gdk/Colormap.h>
#include <Gtk/Gtk/Requisition.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/Pango/FontDescription.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Layout.h>
#include <Gtk/Gtk/IconSize.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/Pango/Context.h>
#include <Gtk/Gdk/ExtensionMode.h>
#include <Gtk/Gtk/RcPropertyParser.h>
#include <Gtk/Gtk/Style.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/DirectionType.h>
#include <Gtk/Gtk/Settings.h>
#include <Gtk/Gtk/StateType.h>
#include <Gtk/Gtk/AccelGroup.h>
#include <Gtk/Gtk/Adjustment.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Gtk/Gdk/Visual.h>
#include <Gtk/Gdk/Screen.h>
#include <Gtk/Gdk/Region.h>
#include <Gtk/Gdk/Bitmap.h>
#include <Gtk/Gdk/Window.h>
#include <Gtk/GObject/Value.h>
#include <Gtk/Gtk/Action.h>
#include <Gtk/Atk/Object.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 3) {
	GType type;
	char *first_property_name = Std$String$flatten(Args[1].Val);
	char *___ = 0;
	GtkWidget * result = gtk_widget_new(type, first_property_name, ___);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(ClassFindStyleProperty, 2) {
	GtkWidgetClass* klass = 0;
	char *property_name = Std$String$flatten(Args[1].Val);
	GParamSpec* result = gtk_widget_class_find_style_property(klass, property_name);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(ClassInstallStyleProperty, 2) {
	GtkWidgetClass* klass = 0;
	GParamSpec* pspec = 0;
	gtk_widget_class_install_style_property(klass, pspec);
	return SUCCESS;
};

GLOBAL_FUNCTION(ClassInstallStylePropertyParser, 3) {
	GtkWidgetClass* klass = 0;
	GParamSpec* pspec = 0;
	GtkRcPropertyParser parser = Gtk$Gtk$RcPropertyParser$new(Args[2].Val);
	gtk_widget_class_install_style_property_parser(klass, pspec, parser);
	return SUCCESS;
};

GLOBAL_FUNCTION(ClassListStyleProperties, 2) {
	GtkWidgetClass* klass = 0;
	guint* n_properties = 0;
	GParamSpec** result = gtk_widget_class_list_style_properties(klass, n_properties);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetDefaultColormap, 0) {
	GdkColormap * result = gtk_widget_get_default_colormap();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetDefaultDirection, 0) {
	GtkTextDirection result = gtk_widget_get_default_direction();
	Gtk$Gtk$TextDirection_t *_result = new(Gtk$Gtk$TextDirection_t);
	_result->Type = Gtk$Gtk$TextDirection$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetDefaultStyle, 0) {
	GtkStyle * result = gtk_widget_get_default_style();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetDefaultVisual, 0) {
	GdkVisual * result = gtk_widget_get_default_visual();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_widget_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(PopColormap, 0) {
	gtk_widget_pop_colormap();
	return SUCCESS;
};

GLOBAL_FUNCTION(PopCompositeChild, 0) {
	gtk_widget_pop_composite_child();
	return SUCCESS;
};

GLOBAL_FUNCTION(PushColormap, 1) {
	GdkColormap * cmap = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_push_colormap(cmap);
	return SUCCESS;
};

GLOBAL_FUNCTION(PushCompositeChild, 0) {
	gtk_widget_push_composite_child();
	return SUCCESS;
};

GLOBAL_FUNCTION(SetDefaultColormap, 1) {
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_set_default_colormap(colormap);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetDefaultDirection, 1) {
	GtkTextDirection dir = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gtk_widget_set_default_direction(dir);
	return SUCCESS;
};

METHOD("Activate", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_widget_activate(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("AddAccelerator", TYP, T, TYP, Std$String$T, TYP, Gtk$Gtk$AccelGroup$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *accel_signal = Std$String$flatten(Args[1].Val);
	GtkAccelGroup * accel_group = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int accel_key = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int accel_mods = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int accel_flags = ((Std$Integer_smallt *)Args[5].Val)->Value;
	gtk_widget_add_accelerator(self, accel_signal, accel_group, accel_key, accel_mods, accel_flags);
	return SUCCESS;
};

METHOD("AddEvents", TYP, T, TYP, Std$Integer$SmallT) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int events = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_widget_add_events(self, events);
	return SUCCESS;
};

METHOD("AddMnemonicLabel", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * label = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_widget_add_mnemonic_label(self, label);
	return SUCCESS;
};

METHOD("CanActivateAccel", TYP, T, TYP, Std$Integer$SmallT) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int signal_id = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_widget_can_activate_accel(self, signal_id);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ChildFocus", TYP, T, TYP, Gtk$Gtk$DirectionType$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkDirectionType direction = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_widget_child_focus(self, direction);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ChildNotify", TYP, T, TYP, Std$String$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *child_property = Std$String$flatten(Args[1].Val);
	gtk_widget_child_notify(self, child_property);
	return SUCCESS;
};

METHOD("ClassPath", TYP, T, TYP, Std$Object$T, TYP, Std$List$T, TYP, Std$List$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	guint* path_length = 0;
	const char * const * path;
	const char * const * path_reversed;
	gtk_widget_class_path(self, path_length, path, path_reversed);
	return SUCCESS;
};

METHOD("CreatePangoContext", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoContext * result = gtk_widget_create_pango_context(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("CreatePangoLayout", TYP, T, TYP, Std$String$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	PangoLayout * result = gtk_widget_create_pango_layout(self, text);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Destroy", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_destroy(self);
	return SUCCESS;
};

METHOD("Destroyed", TYP, T, TYP, Std$Object$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget** widget_pointer = 0;
	gtk_widget_destroyed(self, widget_pointer);
	return SUCCESS;
};

METHOD("Draw", TYP, T, TYP, Gtk$Gdk$Rectangle$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	gtk_widget_draw(self, area);
	return SUCCESS;
};

METHOD("EnsureStyle", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_ensure_style(self);
	return SUCCESS;
};

METHOD("Event", TYP, T, TYP, Std$Object$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkEvent* event = 0;
	int result = gtk_widget_event(self, event);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("FreezeChildNotify", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_freeze_child_notify(self);
	return SUCCESS;
};

METHOD("GetAccessible", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	AtkObject * result = gtk_widget_get_accessible(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetAction", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAction * result = gtk_widget_get_action(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetAncestor", TYP, T, TYP, Gtk$GObject$Type$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GType widget_type;
	GtkWidget * result = gtk_widget_get_ancestor(self, widget_type);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetChildRequisition", TYP, T, TYP, Gtk$Gtk$Requisition$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkRequisition * requisition= &((Gtk$Gtk$Requisition_t *)Args[1].Val)->Value;
	gtk_widget_get_child_requisition(self, requisition);
	return SUCCESS;
};

METHOD("GetChildVisible", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_widget_get_child_visible(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetClipboard", TYP, T, TYP, Std$Object$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom selection = 0;
	GtkClipboard * result = gtk_widget_get_clipboard(self, selection);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetColormap", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * result = gtk_widget_get_colormap(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetCompositeName", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char * result = gtk_widget_get_composite_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetDirection", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextDirection result = gtk_widget_get_direction(self);
	Gtk$Gtk$TextDirection_t *_result = new(Gtk$Gtk$TextDirection_t);
	_result->Type = Gtk$Gtk$TextDirection$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetDisplay", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDisplay * result = gtk_widget_get_display(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetEvents", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_widget_get_events(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetExtensionEvents", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkExtensionMode result = gtk_widget_get_extension_events(self);
	Gtk$Gdk$ExtensionMode_t *_result = new(Gtk$Gdk$ExtensionMode_t);
	_result->Type = Gtk$Gdk$ExtensionMode$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetModifierStyle", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkRcStyle * result = gtk_widget_get_modifier_style(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetName", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_widget_get_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetNoShowAll", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_widget_get_no_show_all(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetPangoContext", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoContext * result = gtk_widget_get_pango_context(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetParent", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_widget_get_parent(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetParentWindow", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * result = gtk_widget_get_parent_window(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPointer", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* x = 0;
	gint* y = 0;
	gtk_widget_get_pointer(self, x, y);
	return SUCCESS;
};

METHOD("GetRootWindow", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * result = gtk_widget_get_root_window(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetScreen", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkScreen * result = gtk_widget_get_screen(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetSettings", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSettings * result = gtk_widget_get_settings(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetSizeRequest", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* width = 0;
	gint* height = 0;
	gtk_widget_get_size_request(self, width, height);
	return SUCCESS;
};

METHOD("GetStyle", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkStyle * result = gtk_widget_get_style(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetToplevel", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_widget_get_toplevel(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetVisual", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkVisual * result = gtk_widget_get_visual(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GrabDefault", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_grab_default(self);
	return SUCCESS;
};

METHOD("GrabFocus", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_grab_focus(self);
	return SUCCESS;
};

METHOD("HasScreen", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_widget_has_screen(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Hide", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_hide(self);
	return SUCCESS;
};

METHOD("HideAll", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_hide_all(self);
	return SUCCESS;
};

METHOD("HideOnDelete", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_widget_hide_on_delete(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("InputShapeCombineMask", TYP, T, TYP, Gtk$Gdk$Bitmap$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkBitmap * shape_mask = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int offset_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int offset_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_widget_input_shape_combine_mask(self, shape_mask, offset_x, offset_y);
	return SUCCESS;
};

METHOD("Intersect", TYP, T, TYP, Gtk$Gdk$Rectangle$T, TYP, Gtk$Gdk$Rectangle$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	GdkRectangle * intersection= &((Gtk$Gdk$Rectangle_t *)Args[2].Val)->Value;
	int result = gtk_widget_intersect(self, area, intersection);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsAncestor", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * ancestor = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_widget_is_ancestor(self, ancestor);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsComposited", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_widget_is_composited(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsFocus", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_widget_is_focus(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ListAccelClosures", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* result = gtk_widget_list_accel_closures(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("ListMnemonicLabels", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* result = gtk_widget_list_mnemonic_labels(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Map", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_map(self);
	return SUCCESS;
};

METHOD("MnemonicActivate", TYP, T, TYP, Std$Symbol$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int group_cycling = Args[1].Val == $true;
	int result = gtk_widget_mnemonic_activate(self, group_cycling);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("ModifyBase", TYP, T, TYP, Gtk$Gtk$StateType$T, TYP, Gtk$Gdk$Color$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkStateType state = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[2].Val)->Value;
	gtk_widget_modify_base(self, state, color);
	return SUCCESS;
};

METHOD("ModifyBg", TYP, T, TYP, Gtk$Gtk$StateType$T, TYP, Gtk$Gdk$Color$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkStateType state = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[2].Val)->Value;
	gtk_widget_modify_bg(self, state, color);
	return SUCCESS;
};

METHOD("ModifyFg", TYP, T, TYP, Gtk$Gtk$StateType$T, TYP, Gtk$Gdk$Color$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkStateType state = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[2].Val)->Value;
	gtk_widget_modify_fg(self, state, color);
	return SUCCESS;
};

METHOD("ModifyFont", TYP, T, TYP, Gtk$Pango$FontDescription$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoFontDescription * font_desc= ((Gtk$Pango$FontDescription_t *)Args[1].Val)->Value;
	gtk_widget_modify_font(self, font_desc);
	return SUCCESS;
};

METHOD("ModifyStyle", TYP, T, TYP, Gtk$Gtk$RcStyle$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkRcStyle * style = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_widget_modify_style(self, style);
	return SUCCESS;
};

METHOD("ModifyText", TYP, T, TYP, Gtk$Gtk$StateType$T, TYP, Gtk$Gdk$Color$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkStateType state = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[2].Val)->Value;
	gtk_widget_modify_text(self, state, color);
	return SUCCESS;
};

METHOD("Path", TYP, T, TYP, Std$Object$T, TYP, Std$List$T, TYP, Std$List$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	guint* path_length = 0;
	const char * const * path;
	const char * const * path_reversed;
	gtk_widget_path(self, path_length, path, path_reversed);
	return SUCCESS;
};

METHOD("QueueClear", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_queue_clear(self);
	return SUCCESS;
};

METHOD("QueueClearArea", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_widget_queue_clear_area(self, x, y, width, height);
	return SUCCESS;
};

METHOD("QueueDraw", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_queue_draw(self);
	return SUCCESS;
};

METHOD("QueueDrawArea", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_widget_queue_draw_area(self, x, y, width, height);
	return SUCCESS;
};

METHOD("QueueResize", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_queue_resize(self);
	return SUCCESS;
};

METHOD("QueueResizeNoRedraw", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_queue_resize_no_redraw(self);
	return SUCCESS;
};

METHOD("Realize", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_realize(self);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_widget_ref(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("RegionIntersect", TYP, T, TYP, Gtk$Gdk$Region$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRegion * region= ((Gtk$Gdk$Region_t *)Args[1].Val)->Value;
	GdkRegion * result = gtk_widget_region_intersect(self, region);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("RemoveAccelerator", TYP, T, TYP, Gtk$Gtk$AccelGroup$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAccelGroup * accel_group = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int accel_key = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int accel_mods = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int result = gtk_widget_remove_accelerator(self, accel_group, accel_key, accel_mods);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("RemoveMnemonicLabel", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * label = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_widget_remove_mnemonic_label(self, label);
	return SUCCESS;
};

METHOD("RenderIcon", TYP, T, TYP, Std$String$T, TYP, Gtk$Gtk$IconSize$T, TYP, Std$String$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *stock_id = Std$String$flatten(Args[1].Val);
	GtkIconSize size = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char *detail = Std$String$flatten(Args[3].Val);
	GdkPixbuf * result = gtk_widget_render_icon(self, stock_id, size, detail);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Reparent", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * new_parent = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_widget_reparent(self, new_parent);
	return SUCCESS;
};

METHOD("ResetRcStyles", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_reset_rc_styles(self);
	return SUCCESS;
};

METHOD("ResetShapes", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_reset_shapes(self);
	return SUCCESS;
};

METHOD("SendExpose", TYP, T, TYP, Std$Object$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkEvent* event = 0;
	int result = gtk_widget_send_expose(self, event);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Set", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *first_property_name = Std$String$flatten(Args[1].Val);
	char *___ = 0;
	gtk_widget_set(self, first_property_name, ___);
	return SUCCESS;
};

METHOD("SetAccelPath", TYP, T, TYP, Std$String$T, TYP, Gtk$Gtk$AccelGroup$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *accel_path = Std$String$flatten(Args[1].Val);
	GtkAccelGroup * accel_group = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_widget_set_accel_path(self, accel_path, accel_group);
	return SUCCESS;
};

METHOD("SetAppPaintable", TYP, T, TYP, Std$Symbol$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int app_paintable = Args[1].Val == $true;
	gtk_widget_set_app_paintable(self, app_paintable);
	return SUCCESS;
};

METHOD("SetChildVisible", TYP, T, TYP, Std$Symbol$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int is_visible = Args[1].Val == $true;
	gtk_widget_set_child_visible(self, is_visible);
	return SUCCESS;
};

METHOD("SetColormap", TYP, T, TYP, Gtk$Gdk$Colormap$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_widget_set_colormap(self, colormap);
	return SUCCESS;
};

METHOD("SetCompositeName", TYP, T, TYP, Std$String$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	gtk_widget_set_composite_name(self, name);
	return SUCCESS;
};

METHOD("SetDirection", TYP, T, TYP, Gtk$Gtk$TextDirection$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextDirection dir = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_widget_set_direction(self, dir);
	return SUCCESS;
};

METHOD("SetDoubleBuffered", TYP, T, TYP, Std$Symbol$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int double_buffered = Args[1].Val == $true;
	gtk_widget_set_double_buffered(self, double_buffered);
	return SUCCESS;
};

METHOD("SetEvents", TYP, T, TYP, Std$Integer$SmallT) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int events = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_widget_set_events(self, events);
	return SUCCESS;
};

METHOD("SetExtensionEvents", TYP, T, TYP, Gtk$Gdk$ExtensionMode$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkExtensionMode mode = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_widget_set_extension_events(self, mode);
	return SUCCESS;
};

METHOD("SetName", TYP, T, TYP, Std$String$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	gtk_widget_set_name(self, name);
	return SUCCESS;
};

METHOD("SetNoShowAll", TYP, T, TYP, Std$Symbol$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int no_show_all = Args[1].Val == $true;
	gtk_widget_set_no_show_all(self, no_show_all);
	return SUCCESS;
};

METHOD("SetParent", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * parent = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_widget_set_parent(self, parent);
	return SUCCESS;
};

METHOD("SetParentWindow", TYP, T, TYP, Gtk$Gdk$Window$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * parent_window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_widget_set_parent_window(self, parent_window);
	return SUCCESS;
};

METHOD("SetRedrawOnAllocate", TYP, T, TYP, Std$Symbol$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int redraw_on_allocate = Args[1].Val == $true;
	gtk_widget_set_redraw_on_allocate(self, redraw_on_allocate);
	return SUCCESS;
};

METHOD("SetScrollAdjustments", TYP, T, TYP, Gtk$Gtk$Adjustment$T, TYP, Gtk$Gtk$Adjustment$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * hadjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkAdjustment * vadjustment = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int result = gtk_widget_set_scroll_adjustments(self, hadjustment, vadjustment);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetSensitive", TYP, T, TYP, Std$Symbol$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int sensitive = Args[1].Val == $true;
	gtk_widget_set_sensitive(self, sensitive);
	return SUCCESS;
};

METHOD("SetSizeRequest", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_widget_set_size_request(self, width, height);
	return SUCCESS;
};

METHOD("SetState", TYP, T, TYP, Gtk$Gtk$StateType$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkStateType state = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_widget_set_state(self, state);
	return SUCCESS;
};

METHOD("SetStyle", TYP, T, TYP, Gtk$Gtk$Style$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_widget_set_style(self, style);
	return SUCCESS;
};

METHOD("SetUposition", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_widget_set_uposition(self, x, y);
	return SUCCESS;
};

METHOD("SetUsize", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_widget_set_usize(self, width, height);
	return SUCCESS;
};

METHOD("ShapeCombineMask", TYP, T, TYP, Gtk$Gdk$Bitmap$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkBitmap * shape_mask = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int offset_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int offset_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_widget_shape_combine_mask(self, shape_mask, offset_x, offset_y);
	return SUCCESS;
};

METHOD("Show", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_show(self);
	return SUCCESS;
};

METHOD("ShowAll", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_show_all(self);
	return SUCCESS;
};

METHOD("ShowNow", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_show_now(self);
	return SUCCESS;
};

METHOD("SizeAllocate", TYP, T, TYP, Std$Object$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAllocation* allocation = 0;
	gtk_widget_size_allocate(self, allocation);
	return SUCCESS;
};

METHOD("SizeRequest", TYP, T, TYP, Gtk$Gtk$Requisition$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkRequisition * requisition= &((Gtk$Gtk$Requisition_t *)Args[1].Val)->Value;
	gtk_widget_size_request(self, requisition);
	return SUCCESS;
};

METHOD("StyleGet", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *first_property_name = Std$String$flatten(Args[1].Val);
	char *___ = 0;
	gtk_widget_style_get(self, first_property_name, ___);
	return SUCCESS;
};

METHOD("StyleGetProperty", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *property_name = Std$String$flatten(Args[1].Val);
	GValue value[1];
	Gtk$GObject$Value$to_gtk(Args[2].Val, value);
	gtk_widget_style_get_property(self, property_name, value);
	return SUCCESS;
};

METHOD("StyleGetValist", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *first_property_name = Std$String$flatten(Args[1].Val);
	va_list var_args = 0;
	gtk_widget_style_get_valist(self, first_property_name, var_args);
	return SUCCESS;
};

METHOD("ThawChildNotify", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_thaw_child_notify(self);
	return SUCCESS;
};

METHOD("TranslateCoordinates", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * dest_widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int src_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int src_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gint* dest_x = 0;
	gint* dest_y = 0;
	int result = gtk_widget_translate_coordinates(self, dest_widget, src_x, src_y, dest_x, dest_y);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Unmap", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_unmap(self);
	return SUCCESS;
};

METHOD("Unparent", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_unparent(self);
	return SUCCESS;
};

METHOD("Unrealize", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_unrealize(self);
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GtkWidget * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_widget_unref(self);
	return SUCCESS;
};

