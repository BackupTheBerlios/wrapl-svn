#include <Gtk/Gtk/Accelerator.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 2
#include <Std/Boolean.h>
#include <Gtk/GObject/Object.h>
/***********************************/
GLOBAL_FUNCTION(GetDefaultModMask, 0) {
	int result = gtk_accelerator_get_default_mod_mask();
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetLabel, 2) {
	int accelerator_key = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int accelerator_mods = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char * result = gtk_accelerator_get_label(accelerator_key, accelerator_mods);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Name, 2) {
	int accelerator_key = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int accelerator_mods = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char * result = gtk_accelerator_name(accelerator_key, accelerator_mods);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Parse, 3) {
	char *accelerator = Std$String$flatten(Args[0].Val);
	guint* accelerator_key = 0;
	GdkModifierType* accelerator_mods = 0;
	gtk_accelerator_parse(accelerator, accelerator_key, accelerator_mods);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetDefaultModMask, 1) {
	int default_mod_mask = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gtk_accelerator_set_default_mod_mask(default_mod_mask);
	return SUCCESS;
};

GLOBAL_FUNCTION(Valid, 2) {
	int keyval = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int modifiers = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_accelerator_valid(keyval, modifiers);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

