#include <Gtk/Pango/LayoutIter.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Std/Boolean.h>
#include <Gtk/Pango/Rectangle.h>
#include <Gtk/Pango/LayoutLine.h>
#include <Gtk/Pango/LayoutIter.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Pango/LayoutRun.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_layout_iter_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AtLastLine", TYP, T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	int result = pango_layout_iter_at_last_line(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	pango_layout_iter_free(self);
	return SUCCESS;
};

METHOD("GetBaseline", TYP, T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	int result = pango_layout_iter_get_baseline(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetCharExtents", TYP, T, TYP, Gtk$Pango$Rectangle$T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	PangoRectangle * logical_rect= &((Gtk$Pango$Rectangle_t *)Args[1].Val)->Value;
	pango_layout_iter_get_char_extents(self, logical_rect);
	return SUCCESS;
};

METHOD("GetClusterExtents", TYP, T, TYP, Gtk$Pango$Rectangle$T, TYP, Gtk$Pango$Rectangle$T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	PangoRectangle * ink_rect= &((Gtk$Pango$Rectangle_t *)Args[1].Val)->Value;
	PangoRectangle * logical_rect= &((Gtk$Pango$Rectangle_t *)Args[2].Val)->Value;
	pango_layout_iter_get_cluster_extents(self, ink_rect, logical_rect);
	return SUCCESS;
};

METHOD("GetIndex", TYP, T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	int result = pango_layout_iter_get_index(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetLayoutExtents", TYP, T, TYP, Gtk$Pango$Rectangle$T, TYP, Gtk$Pango$Rectangle$T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	PangoRectangle * ink_rect= &((Gtk$Pango$Rectangle_t *)Args[1].Val)->Value;
	PangoRectangle * logical_rect= &((Gtk$Pango$Rectangle_t *)Args[2].Val)->Value;
	pango_layout_iter_get_layout_extents(self, ink_rect, logical_rect);
	return SUCCESS;
};

METHOD("GetLine", TYP, T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	PangoLayoutLine * result = pango_layout_iter_get_line(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetLineExtents", TYP, T, TYP, Gtk$Pango$Rectangle$T, TYP, Gtk$Pango$Rectangle$T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	PangoRectangle * ink_rect= &((Gtk$Pango$Rectangle_t *)Args[1].Val)->Value;
	PangoRectangle * logical_rect= &((Gtk$Pango$Rectangle_t *)Args[2].Val)->Value;
	pango_layout_iter_get_line_extents(self, ink_rect, logical_rect);
	return SUCCESS;
};

METHOD("GetLineReadonly", TYP, T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	PangoLayoutLine * result = pango_layout_iter_get_line_readonly(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetLineYrange", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	int* y0_ = 0;
	int* y1_ = 0;
	pango_layout_iter_get_line_yrange(self, y0_, y1_);
	return SUCCESS;
};

METHOD("GetRun", TYP, T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	PangoLayoutRun * result = pango_layout_iter_get_run(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetRunExtents", TYP, T, TYP, Gtk$Pango$Rectangle$T, TYP, Gtk$Pango$Rectangle$T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	PangoRectangle * ink_rect= &((Gtk$Pango$Rectangle_t *)Args[1].Val)->Value;
	PangoRectangle * logical_rect= &((Gtk$Pango$Rectangle_t *)Args[2].Val)->Value;
	pango_layout_iter_get_run_extents(self, ink_rect, logical_rect);
	return SUCCESS;
};

METHOD("GetRunReadonly", TYP, T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	PangoLayoutRun * result = pango_layout_iter_get_run_readonly(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("NextChar", TYP, T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	int result = pango_layout_iter_next_char(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("NextCluster", TYP, T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	int result = pango_layout_iter_next_cluster(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("NextLine", TYP, T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	int result = pango_layout_iter_next_line(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("NextRun", TYP, T) {
	PangoLayoutIter * self= ((Gtk$Pango$LayoutIter_t *)Args[0].Val)->Value;
	int result = pango_layout_iter_next_run(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

