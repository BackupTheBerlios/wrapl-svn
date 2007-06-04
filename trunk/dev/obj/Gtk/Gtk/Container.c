#include <Gtk/Gtk/Container.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 12
#include <Gtk/Gtk/ResizeMode.h>
#include <Gtk/Gtk/Callback.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/CallbackMarshal.h>
#include <Gtk/Gtk/Container.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/DestroyNotify.h>
#include <Gtk/Gtk/Adjustment.h>
#include <Gtk/GObject/Value.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
#include <Gtk/Gdk/EventExpose.h>
/***********************************/
TYPE(T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(ClassFindChildProperty, 2) {
	GObjectClass* cclass = 0;
	char *property_name = Std$String$flatten(Args[1].Val);
	GParamSpec* result = gtk_container_class_find_child_property(cclass, property_name);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(ClassInstallChildProperty, 3) {
	GtkContainerClass* cclass = 0;
	int property_id = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GParamSpec* pspec = 0;
	gtk_container_class_install_child_property(cclass, property_id, pspec);
	return SUCCESS;
};

GLOBAL_FUNCTION(ClassListChildProperties, 2) {
	GObjectClass* cclass = 0;
	guint* n_properties = 0;
	GParamSpec** result = gtk_container_class_list_child_properties(cclass, n_properties);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_container_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Add", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_container_add(self, widget);
	return SUCCESS;
};

METHOD("AddWithProperties", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *first_prop_name = Std$String$flatten(Args[2].Val);
	char *___ = 0;
	gtk_container_add_with_properties(self, widget, first_prop_name, ___);
	return SUCCESS;
};

METHOD("CheckResize", TYP, T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_container_check_resize(self);
	return SUCCESS;
};

METHOD("ChildGet", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *first_prop_name = Std$String$flatten(Args[2].Val);
	char *___ = 0;
	gtk_container_child_get(self, child, first_prop_name, ___);
	return SUCCESS;
};

METHOD("ChildGetProperty", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *property_name = Std$String$flatten(Args[2].Val);
	GValue value[1];
	Gtk$GObject$Value$to_gtk(Args[3].Val, value);
	gtk_container_child_get_property(self, child, property_name, value);
	return SUCCESS;
};

METHOD("ChildGetValist", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *first_property_name = Std$String$flatten(Args[2].Val);
	va_list var_args = 0;
	gtk_container_child_get_valist(self, child, first_property_name, var_args);
	return SUCCESS;
};

METHOD("ChildSet", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *first_prop_name = Std$String$flatten(Args[2].Val);
	char *___ = 0;
	gtk_container_child_set(self, child, first_prop_name, ___);
	return SUCCESS;
};

METHOD("ChildSetProperty", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *property_name = Std$String$flatten(Args[2].Val);
	GValue value[1];
	Gtk$GObject$Value$to_gtk(Args[3].Val, value);
	gtk_container_child_set_property(self, child, property_name, value);
	return SUCCESS;
};

METHOD("ChildSetValist", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *first_property_name = Std$String$flatten(Args[2].Val);
	va_list var_args = 0;
	gtk_container_child_set_valist(self, child, first_property_name, var_args);
	return SUCCESS;
};

METHOD("ChildType", TYP, T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GType result = gtk_container_child_type(self);
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Forall", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCallback callback = Gtk$Gtk$Callback$new(Args[1].Val);
	void *callback_data = ((Std$Address_t *)Args[2].Val)->Value;
	gtk_container_forall(self, callback, callback_data);
	return SUCCESS;
};

METHOD("Foreach", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCallback callback = Gtk$Gtk$Callback$new(Args[1].Val);
	void *callback_data = ((Std$Address_t *)Args[2].Val)->Value;
	gtk_container_foreach(self, callback, callback_data);
	return SUCCESS;
};

METHOD("ForeachFull", TYP, T, TYP, Std$Function$T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkCallback callback = Gtk$Gtk$Callback$new(Args[1].Val);
	GtkCallbackMarshal marshal = Gtk$Gtk$CallbackMarshal$new(Args[2].Val);
	void *callback_data = ((Std$Address_t *)Args[3].Val)->Value;
	GtkDestroyNotify notify = Gtk$Gtk$DestroyNotify$new(Args[4].Val);
	gtk_container_foreach_full(self, callback, marshal, callback_data, notify);
	return SUCCESS;
};

METHOD("GetBorderWidth", TYP, T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_container_get_border_width(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetChildren", TYP, T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList * result = gtk_container_get_children(self);
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

METHOD("GetFocusChain", TYP, T, TYP, Std$Object$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList** focusable_widgets = 0;
	int result = gtk_container_get_focus_chain(self, focusable_widgets);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetFocusHadjustment", TYP, T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * result = gtk_container_get_focus_hadjustment(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetFocusVadjustment", TYP, T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * result = gtk_container_get_focus_vadjustment(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetResizeMode", TYP, T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkResizeMode result = gtk_container_get_resize_mode(self);
	Gtk$Gtk$ResizeMode_t *_result = new(Gtk$Gtk$ResizeMode_t);
	_result->Type = Gtk$Gtk$ResizeMode$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("PropagateExpose", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gdk$EventExpose$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkEventExpose * event= &((Gtk$Gdk$EventExpose_t *)Args[2].Val)->Value;
	gtk_container_propagate_expose(self, child, event);
	return SUCCESS;
};

METHOD("Remove", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_container_remove(self, widget);
	return SUCCESS;
};

METHOD("ResizeChildren", TYP, T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_container_resize_children(self);
	return SUCCESS;
};

METHOD("SetBorderWidth", TYP, T, TYP, Std$Integer$SmallT) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int border_width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_container_set_border_width(self, border_width);
	return SUCCESS;
};

METHOD("SetFocusChain", TYP, T, TYP, Std$Object$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList* focusable_widgets = 0;
	gtk_container_set_focus_chain(self, focusable_widgets);
	return SUCCESS;
};

METHOD("SetFocusChild", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_container_set_focus_child(self, child);
	return SUCCESS;
};

METHOD("SetFocusHadjustment", TYP, T, TYP, Gtk$Gtk$Adjustment$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_container_set_focus_hadjustment(self, adjustment);
	return SUCCESS;
};

METHOD("SetFocusVadjustment", TYP, T, TYP, Gtk$Gtk$Adjustment$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAdjustment * adjustment = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_container_set_focus_vadjustment(self, adjustment);
	return SUCCESS;
};

METHOD("SetReallocateRedraws", TYP, T, TYP, Std$Symbol$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int needs_redraws = Args[1].Val == $true;
	gtk_container_set_reallocate_redraws(self, needs_redraws);
	return SUCCESS;
};

METHOD("SetResizeMode", TYP, T, TYP, Gtk$Gtk$ResizeMode$T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkResizeMode resize_mode = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_container_set_resize_mode(self, resize_mode);
	return SUCCESS;
};

METHOD("UnsetFocusChain", TYP, T) {
	GtkContainer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_container_unset_focus_chain(self);
	return SUCCESS;
};

