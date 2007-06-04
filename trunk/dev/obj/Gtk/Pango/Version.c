#include <Gtk/Pango/Version.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 1
#include <Gtk/GObject/Object.h>
/***********************************/
GLOBAL_FUNCTION(Check, 3) {
	int required_major = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int required_minor = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int required_micro = ((Std$Integer_smallt *)Args[2].Val)->Value;
	const char * result = pango_version_check(required_major, required_minor, required_micro);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(String, 0) {
	const char * result = pango_version_string();
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

