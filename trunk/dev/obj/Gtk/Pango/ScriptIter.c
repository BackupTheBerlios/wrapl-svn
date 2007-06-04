#include <Gtk/Pango/ScriptIter.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Std/Boolean.h>
#include <Gtk/Pango/ScriptIter.h>
#include <Gtk/GObject/Object.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 2) {
	char *text = Std$String$flatten(Args[0].Val);
	int length = ((Std$Integer_smallt *)Args[1].Val)->Value;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = pango_script_iter_new(text, length);
	Result->Val= result;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	PangoScriptIter * self= ((Gtk$Pango$ScriptIter_t *)Args[0].Val)->Value;
	pango_script_iter_free(self);
	return SUCCESS;
};

METHOD("GetRange", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoScriptIter * self= ((Gtk$Pango$ScriptIter_t *)Args[0].Val)->Value;
	const char** start = 0;
	const char** end = 0;
	PangoScript* script = 0;
	pango_script_iter_get_range(self, start, end, script);
	return SUCCESS;
};

METHOD("Next", TYP, T) {
	PangoScriptIter * self= ((Gtk$Pango$ScriptIter_t *)Args[0].Val)->Value;
	int result = pango_script_iter_next(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

