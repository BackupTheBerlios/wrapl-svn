#include <Gtk/Gtk/AccelMap.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Gtk/Gtk/AccelMap.h>
#include <Gtk/Gtk/AccelKey.h>
#include <Gtk/GObject/Type.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/AccelMapForeach.h>
#include <Gtk/GObject/Object.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(AddEntry, 3) {
	char *accel_path = Std$String$flatten(Args[0].Val);
	int accel_key = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int accel_mods = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_accel_map_add_entry(accel_path, accel_key, accel_mods);
	return SUCCESS;
};

GLOBAL_FUNCTION(AddFilter, 1) {
	char *filter_pattern = Std$String$flatten(Args[0].Val);
	gtk_accel_map_add_filter(filter_pattern);
	return SUCCESS;
};

GLOBAL_FUNCTION(ChangeEntry, 4) {
	char *accel_path = Std$String$flatten(Args[0].Val);
	int accel_key = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int accel_mods = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int replace = Args[3].Val == $true;
	int result = gtk_accel_map_change_entry(accel_path, accel_key, accel_mods, replace);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(Foreach, 2) {
	void *data = ((Std$Address_t *)Args[0].Val)->Value;
	GtkAccelMapForeach foreach_func = Gtk$Gtk$AccelMapForeach$new(Args[1].Val);
	gtk_accel_map_foreach(data, foreach_func);
	return SUCCESS;
};

GLOBAL_FUNCTION(ForeachUnfiltered, 2) {
	void *data = ((Std$Address_t *)Args[0].Val)->Value;
	GtkAccelMapForeach foreach_func = Gtk$Gtk$AccelMapForeach$new(Args[1].Val);
	gtk_accel_map_foreach_unfiltered(data, foreach_func);
	return SUCCESS;
};

GLOBAL_FUNCTION(Get, 0) {
	GtkAccelMap * result = gtk_accel_map_get();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_accel_map_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Load, 1) {
	char *file_name = Std$String$flatten(Args[0].Val);
	gtk_accel_map_load(file_name);
	return SUCCESS;
};

GLOBAL_FUNCTION(LoadFd, 1) {
	int fd = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gtk_accel_map_load_fd(fd);
	return SUCCESS;
};

GLOBAL_FUNCTION(LoadScanner, 1) {
	GScanner* scanner = 0;
	gtk_accel_map_load_scanner(scanner);
	return SUCCESS;
};

GLOBAL_FUNCTION(LockPath, 1) {
	char *accel_path = Std$String$flatten(Args[0].Val);
	gtk_accel_map_lock_path(accel_path);
	return SUCCESS;
};

GLOBAL_FUNCTION(LookupEntry, 2) {
	char *accel_path = Std$String$flatten(Args[0].Val);
	GtkAccelKey * key= &((Gtk$Gtk$AccelKey_t *)Args[1].Val)->Value;
	int result = gtk_accel_map_lookup_entry(accel_path, key);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(Save, 1) {
	char *file_name = Std$String$flatten(Args[0].Val);
	gtk_accel_map_save(file_name);
	return SUCCESS;
};

GLOBAL_FUNCTION(SaveFd, 1) {
	int fd = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gtk_accel_map_save_fd(fd);
	return SUCCESS;
};

GLOBAL_FUNCTION(UnlockPath, 1) {
	char *accel_path = Std$String$flatten(Args[0].Val);
	gtk_accel_map_unlock_path(accel_path);
	return SUCCESS;
};

