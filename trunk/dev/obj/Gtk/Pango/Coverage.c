#include <Gtk/Pango/Coverage.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Pango/CoverageLevel.h>
#include <Gtk/Pango/Coverage.h>
#include <Gtk/GObject/Object.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 0) {
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = pango_coverage_new();
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(FromBytes, 2) {
	char *bytes = Std$String$flatten(Args[0].Val);
	int n_bytes = ((Std$Integer_smallt *)Args[1].Val)->Value;
	PangoCoverage * result = pango_coverage_from_bytes(bytes, n_bytes);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	PangoCoverage * self= ((Gtk$Pango$Coverage_t *)Args[0].Val)->Value;
	PangoCoverage * result = pango_coverage_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Get", TYP, T, TYP, Std$Integer$SmallT) {
	PangoCoverage * self= ((Gtk$Pango$Coverage_t *)Args[0].Val)->Value;
	int index_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	PangoCoverageLevel result = pango_coverage_get(self, index_);
	Gtk$Pango$CoverageLevel_t *_result = new(Gtk$Pango$CoverageLevel_t);
	_result->Type = Gtk$Pango$CoverageLevel$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("Max", TYP, T, TYP, Gtk$Pango$Coverage$T) {
	PangoCoverage * self= ((Gtk$Pango$Coverage_t *)Args[0].Val)->Value;
	PangoCoverage * other= ((Gtk$Pango$Coverage_t *)Args[1].Val)->Value;
	pango_coverage_max(self, other);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	PangoCoverage * self= ((Gtk$Pango$Coverage_t *)Args[0].Val)->Value;
	PangoCoverage * result = pango_coverage_ref(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Set", TYP, T, TYP, Std$Integer$SmallT, TYP, Gtk$Pango$CoverageLevel$T) {
	PangoCoverage * self= ((Gtk$Pango$Coverage_t *)Args[0].Val)->Value;
	int index_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	PangoCoverageLevel level = ((Std$Integer_smallt *)Args[2].Val)->Value;
	pango_coverage_set(self, index_, level);
	return SUCCESS;
};

METHOD("ToBytes", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoCoverage * self= ((Gtk$Pango$Coverage_t *)Args[0].Val)->Value;
	guchar** bytes = 0;
	int* n_bytes = 0;
	pango_coverage_to_bytes(self, bytes, n_bytes);
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	PangoCoverage * self= ((Gtk$Pango$Coverage_t *)Args[0].Val)->Value;
	pango_coverage_unref(self);
	return SUCCESS;
};

