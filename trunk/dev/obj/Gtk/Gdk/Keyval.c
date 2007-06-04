#include <Gtk/Gdk/Keyval.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 2
#include <Std/Boolean.h>
#include <Gtk/GObject/Object.h>
/***********************************/
GLOBAL_FUNCTION(ConvertCase, 3) {
	int symbol = ((Std$Integer_smallt *)Args[0].Val)->Value;
	guint* lower = 0;
	guint* upper = 0;
	gdk_keyval_convert_case(symbol, lower, upper);
	return SUCCESS;
};

GLOBAL_FUNCTION(FromName, 1) {
	char *keyval_name = Std$String$flatten(Args[0].Val);
	int result = gdk_keyval_from_name(keyval_name);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(IsLower, 1) {
	int keyval = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int result = gdk_keyval_is_lower(keyval);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(IsUpper, 1) {
	int keyval = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int result = gdk_keyval_is_upper(keyval);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(Name, 1) {
	int keyval = ((Std$Integer_smallt *)Args[0].Val)->Value;
	char * result = gdk_keyval_name(keyval);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ToLower, 1) {
	int keyval = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int result = gdk_keyval_to_lower(keyval);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ToUnicode, 1) {
	int keyval = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int result = gdk_keyval_to_unicode(keyval);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ToUpper, 1) {
	int keyval = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int result = gdk_keyval_to_upper(keyval);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

