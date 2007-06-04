#include <Gtk/Gtk/Object.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/DestroyNotify.h>
#include <Gtk/Gtk/Object.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 3) {
	GType type;
	char *first_property_name = Std$String$flatten(Args[1].Val);
	char *___ = 0;
	GtkObject * result = gtk_object_new(type, first_property_name, ___);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(AddArgType, 4) {
	char *arg_name = Std$String$flatten(Args[0].Val);
	GType arg_type;
	int arg_flags = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int arg_id = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_object_add_arg_type(arg_name, arg_type, arg_flags, arg_id);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_object_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Destroy", TYP, T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_object_destroy(self);
	return SUCCESS;
};

METHOD("Get", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *first_property_name = Std$String$flatten(Args[1].Val);
	char *___ = 0;
	gtk_object_get(self, first_property_name, ___);
	return SUCCESS;
};

METHOD("GetData", TYP, T, TYP, Std$String$T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	void * result = gtk_object_get_data(self, key);
	Result->Val = Std$Address$new(result);
	return SUCCESS;
};

METHOD("GetDataById", TYP, T, TYP, Std$Object$T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GQuark data_id = 0;
	void * result = gtk_object_get_data_by_id(self, data_id);
	Result->Val = Std$Address$new(result);
	return SUCCESS;
};

METHOD("GetUserData", TYP, T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	void * result = gtk_object_get_user_data(self);
	Result->Val = Std$Address$new(result);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkObject * result = gtk_object_ref(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("RemoveData", TYP, T, TYP, Std$String$T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	gtk_object_remove_data(self, key);
	return SUCCESS;
};

METHOD("RemoveDataById", TYP, T, TYP, Std$Object$T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GQuark data_id = 0;
	gtk_object_remove_data_by_id(self, data_id);
	return SUCCESS;
};

METHOD("RemoveNoNotify", TYP, T, TYP, Std$String$T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	gtk_object_remove_no_notify(self, key);
	return SUCCESS;
};

METHOD("RemoveNoNotifyById", TYP, T, TYP, Std$Object$T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GQuark key_id = 0;
	gtk_object_remove_no_notify_by_id(self, key_id);
	return SUCCESS;
};

METHOD("Set", TYP, T, TYP, Std$String$T, TYP, Std$Object$T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *first_property_name = Std$String$flatten(Args[1].Val);
	char *___ = 0;
	gtk_object_set(self, first_property_name, ___);
	return SUCCESS;
};

METHOD("SetData", TYP, T, TYP, Std$String$T, TYP, Std$Address$T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	gtk_object_set_data(self, key, data);
	return SUCCESS;
};

METHOD("SetDataById", TYP, T, TYP, Std$Object$T, TYP, Std$Address$T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GQuark data_id = 0;
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	gtk_object_set_data_by_id(self, data_id, data);
	return SUCCESS;
};

METHOD("SetDataByIdFull", TYP, T, TYP, Std$Object$T, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GQuark data_id = 0;
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[3].Val);
	gtk_object_set_data_by_id_full(self, data_id, data, destroy);
	return SUCCESS;
};

METHOD("SetDataFull", TYP, T, TYP, Std$String$T, TYP, Std$Address$T, TYP, Std$Function$T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkDestroyNotify destroy = Gtk$Gtk$DestroyNotify$new(Args[3].Val);
	gtk_object_set_data_full(self, key, data, destroy);
	return SUCCESS;
};

METHOD("SetUserData", TYP, T, TYP, Std$Address$T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	void *data = ((Std$Address_t *)Args[1].Val)->Value;
	gtk_object_set_user_data(self, data);
	return SUCCESS;
};

METHOD("Sink", TYP, T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_object_sink(self);
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_object_unref(self);
	return SUCCESS;
};

METHOD("Weakref", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkDestroyNotify notify = Gtk$Gtk$DestroyNotify$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	gtk_object_weakref(self, notify, data);
	return SUCCESS;
};

METHOD("Weakunref", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkObject * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkDestroyNotify notify = Gtk$Gtk$DestroyNotify$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	gtk_object_weakunref(self, notify, data);
	return SUCCESS;
};

