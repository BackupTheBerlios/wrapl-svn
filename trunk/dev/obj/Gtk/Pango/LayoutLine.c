#include <Gtk/Pango/LayoutLine.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Std/Boolean.h>
#include <Gtk/Pango/Rectangle.h>
#include <Gtk/Pango/LayoutLine.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = pango_layout_line_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetExtents", TYP, T, TYP, Gtk$Pango$Rectangle$T, TYP, Gtk$Pango$Rectangle$T) {
	PangoLayoutLine * self= ((Gtk$Pango$LayoutLine_t *)Args[0].Val)->Value;
	PangoRectangle * ink_rect= &((Gtk$Pango$Rectangle_t *)Args[1].Val)->Value;
	PangoRectangle * logical_rect= &((Gtk$Pango$Rectangle_t *)Args[2].Val)->Value;
	pango_layout_line_get_extents(self, ink_rect, logical_rect);
	return SUCCESS;
};

METHOD("GetPixelExtents", TYP, T, TYP, Gtk$Pango$Rectangle$T, TYP, Gtk$Pango$Rectangle$T) {
	PangoLayoutLine * self= ((Gtk$Pango$LayoutLine_t *)Args[0].Val)->Value;
	PangoRectangle * ink_rect= &((Gtk$Pango$Rectangle_t *)Args[1].Val)->Value;
	PangoRectangle * logical_rect= &((Gtk$Pango$Rectangle_t *)Args[2].Val)->Value;
	pango_layout_line_get_pixel_extents(self, ink_rect, logical_rect);
	return SUCCESS;
};

METHOD("GetXRanges", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoLayoutLine * self= ((Gtk$Pango$LayoutLine_t *)Args[0].Val)->Value;
	int start_index = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int end_index = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int** ranges = 0;
	int* n_ranges = 0;
	pango_layout_line_get_x_ranges(self, start_index, end_index, ranges, n_ranges);
	return SUCCESS;
};

METHOD("IndexToX", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Symbol$T, TYP, Std$Object$T) {
	PangoLayoutLine * self= ((Gtk$Pango$LayoutLine_t *)Args[0].Val)->Value;
	int index_ = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int trailing = Args[2].Val == $true;
	int* x_pos = 0;
	pango_layout_line_index_to_x(self, index_, trailing, x_pos);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	PangoLayoutLine * self= ((Gtk$Pango$LayoutLine_t *)Args[0].Val)->Value;
	PangoLayoutLine * result = pango_layout_line_ref(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	PangoLayoutLine * self= ((Gtk$Pango$LayoutLine_t *)Args[0].Val)->Value;
	pango_layout_line_unref(self);
	return SUCCESS;
};

METHOD("XToIndex", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	PangoLayoutLine * self= ((Gtk$Pango$LayoutLine_t *)Args[0].Val)->Value;
	int x_pos = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int* index_ = 0;
	int* trailing = 0;
	int result = pango_layout_line_x_to_index(self, x_pos, index_, trailing);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

