#include <Gtk/Gdk/Region.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 9
#include <Gtk/Gdk/SpanFunc.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/OverlapType.h>
#include <Gtk/Gdk/Point.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Gtk/Gdk/Region.h>
#include <Gtk/Gdk/FillRule.h>
#include <Std/Boolean.h>
#include <Gtk/Gdk/Span.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 0) {
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gdk_region_new();
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(Polygon, 3) {
	GdkPoint * points= &((Gtk$Gdk$Point_t *)Args[0].Val)->Value;
	int npoints = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkFillRule fill_rule = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkRegion * result = gdk_region_polygon(points, npoints, fill_rule);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(Rectangle, 1) {
	GdkRectangle * rectangle= &((Gtk$Gdk$Rectangle_t *)Args[0].Val)->Value;
	GdkRegion * result = gdk_region_rectangle(rectangle);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GdkRegion * self= ((Gtk$Gdk$Region_t *)Args[0].Val)->Value;
	GdkRegion * result = gdk_region_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Destroy", TYP, T) {
	GdkRegion * self= ((Gtk$Gdk$Region_t *)Args[0].Val)->Value;
	gdk_region_destroy(self);
	return SUCCESS;
};

METHOD("Empty", TYP, T) {
	GdkRegion * self= ((Gtk$Gdk$Region_t *)Args[0].Val)->Value;
	int result = gdk_region_empty(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Equal", TYP, T, TYP, Gtk$Gdk$Region$T) {
	GdkRegion * self= ((Gtk$Gdk$Region_t *)Args[0].Val)->Value;
	GdkRegion * region2= ((Gtk$Gdk$Region_t *)Args[1].Val)->Value;
	int result = gdk_region_equal(self, region2);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetClipbox", TYP, T, TYP, Gtk$Gdk$Rectangle$T) {
	GdkRegion * self= ((Gtk$Gdk$Region_t *)Args[0].Val)->Value;
	GdkRectangle * rectangle= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	gdk_region_get_clipbox(self, rectangle);
	return SUCCESS;
};

METHOD("GetRectangles", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkRegion * self= ((Gtk$Gdk$Region_t *)Args[0].Val)->Value;
	GdkRectangle** rectangles = 0;
	gint* n_rectangles = 0;
	gdk_region_get_rectangles(self, rectangles, n_rectangles);
	return SUCCESS;
};

METHOD("Intersect", TYP, T, TYP, Gtk$Gdk$Region$T) {
	GdkRegion * self= ((Gtk$Gdk$Region_t *)Args[0].Val)->Value;
	GdkRegion * source2= ((Gtk$Gdk$Region_t *)Args[1].Val)->Value;
	gdk_region_intersect(self, source2);
	return SUCCESS;
};

METHOD("Offset", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkRegion * self= ((Gtk$Gdk$Region_t *)Args[0].Val)->Value;
	int dx = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int dy = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_region_offset(self, dx, dy);
	return SUCCESS;
};

METHOD("PointIn", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkRegion * self= ((Gtk$Gdk$Region_t *)Args[0].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gdk_region_point_in(self, x, y);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("RectIn", TYP, T, TYP, Gtk$Gdk$Rectangle$T) {
	GdkRegion * self= ((Gtk$Gdk$Region_t *)Args[0].Val)->Value;
	GdkRectangle * rectangle= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	GdkOverlapType result = gdk_region_rect_in(self, rectangle);
	Gtk$Gdk$OverlapType_t *_result = new(Gtk$Gdk$OverlapType_t);
	_result->Type = Gtk$Gdk$OverlapType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("Shrink", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkRegion * self= ((Gtk$Gdk$Region_t *)Args[0].Val)->Value;
	int dx = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int dy = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_region_shrink(self, dx, dy);
	return SUCCESS;
};

METHOD("SpansIntersectForeach", TYP, T, TYP, Gtk$Gdk$Span$T, TYP, Std$Integer$SmallT, TYP, Std$Symbol$T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GdkRegion * self= ((Gtk$Gdk$Region_t *)Args[0].Val)->Value;
	GdkSpan * spans= &((Gtk$Gdk$Span_t *)Args[1].Val)->Value;
	int n_spans = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int sorted = Args[3].Val == $true;
	GdkSpanFunc function = Gtk$Gdk$SpanFunc$new(Args[4].Val);
	void *data = ((Std$Address_t *)Args[5].Val)->Value;
	gdk_region_spans_intersect_foreach(self, spans, n_spans, sorted, function, data);
	return SUCCESS;
};

METHOD("Subtract", TYP, T, TYP, Gtk$Gdk$Region$T) {
	GdkRegion * self= ((Gtk$Gdk$Region_t *)Args[0].Val)->Value;
	GdkRegion * source2= ((Gtk$Gdk$Region_t *)Args[1].Val)->Value;
	gdk_region_subtract(self, source2);
	return SUCCESS;
};

METHOD("Union", TYP, T, TYP, Gtk$Gdk$Region$T) {
	GdkRegion * self= ((Gtk$Gdk$Region_t *)Args[0].Val)->Value;
	GdkRegion * source2= ((Gtk$Gdk$Region_t *)Args[1].Val)->Value;
	gdk_region_union(self, source2);
	return SUCCESS;
};

METHOD("UnionWithRect", TYP, T, TYP, Gtk$Gdk$Rectangle$T) {
	GdkRegion * self= ((Gtk$Gdk$Region_t *)Args[0].Val)->Value;
	GdkRectangle * rect= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	gdk_region_union_with_rect(self, rect);
	return SUCCESS;
};

METHOD("Xor", TYP, T, TYP, Gtk$Gdk$Region$T) {
	GdkRegion * self= ((Gtk$Gdk$Region_t *)Args[0].Val)->Value;
	GdkRegion * source2= ((Gtk$Gdk$Region_t *)Args[1].Val)->Value;
	gdk_region_xor(self, source2);
	return SUCCESS;
};

