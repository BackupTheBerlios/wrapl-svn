#include <Gtk/Gtk/AccelGroup.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 8
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/AccelKey.h>
#include <Gtk/Gtk/AccelGroupFindFunc.h>
#include <Gtk/GObject/Closure.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/AccelGroup.h>
#include <Gtk/Gtk/AccelGroupEntry.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkAccelGroup * result = gtk_accel_group_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(FromAccelClosure, 1) {
	GClosure *closure = Gtk$GObject$Closure$new(Args[0].Val);
	GtkAccelGroup * result = gtk_accel_group_from_accel_closure(closure);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_accel_group_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Activate", TYP, T, TYP, Std$Object$T, TYP, Gtk$GObject$Object$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkAccelGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GQuark accel_quark = 0;
	GObject* acceleratable = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int accel_key = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int accel_mods = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int result = gtk_accel_group_activate(self, accel_quark, acceleratable, accel_key, accel_mods);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Connect", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$GObject$Closure$T) {
	GtkAccelGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int accel_key = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int accel_mods = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int accel_flags = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GClosure *closure = Gtk$GObject$Closure$new(Args[4].Val);
	gtk_accel_group_connect(self, accel_key, accel_mods, accel_flags, closure);
	return SUCCESS;
};

METHOD("ConnectByPath", TYP, T, TYP, Std$String$T, TYP, Gtk$GObject$Closure$T) {
	GtkAccelGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *accel_path = Std$String$flatten(Args[1].Val);
	GClosure *closure = Gtk$GObject$Closure$new(Args[2].Val);
	gtk_accel_group_connect_by_path(self, accel_path, closure);
	return SUCCESS;
};

METHOD("Disconnect", TYP, T, TYP, Gtk$GObject$Closure$T) {
	GtkAccelGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GClosure *closure = Gtk$GObject$Closure$new(Args[1].Val);
	int result = gtk_accel_group_disconnect(self, closure);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("DisconnectKey", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkAccelGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int accel_key = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int accel_mods = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gtk_accel_group_disconnect_key(self, accel_key, accel_mods);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Find", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkAccelGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAccelGroupFindFunc find_func = Gtk$Gtk$AccelGroupFindFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GtkAccelKey * result = gtk_accel_group_find(self, find_func, data);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Lock", TYP, T) {
	GtkAccelGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_accel_group_lock(self);
	return SUCCESS;
};

METHOD("Query", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T) {
	GtkAccelGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int accel_key = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int accel_mods = ((Std$Integer_smallt *)Args[2].Val)->Value;
	guint* n_entries = 0;
	GtkAccelGroupEntry * result = gtk_accel_group_query(self, accel_key, accel_mods, n_entries);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Unlock", TYP, T) {
	GtkAccelGroup * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_accel_group_unlock(self);
	return SUCCESS;
};

