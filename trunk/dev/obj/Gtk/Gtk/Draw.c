#include <Gtk/Gtk/Draw.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 17
#include <Gtk/Gtk/ExpanderStyle.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Layout.h>
#include <Gtk/Gdk/Drawable.h>
#include <Gtk/Gtk/Orientation.h>
#include <Gtk/Gdk/Point.h>
#include <Gtk/Gtk/Style.h>
#include <Gtk/Gtk/ShadowType.h>
#include <Gtk/Gdk/WindowEdge.h>
#include <Gtk/Gtk/StateType.h>
#include <Gtk/Gtk/ArrowType.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Gtk/Gdk/Window.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/PositionType.h>
#include <Gtk/Gtk/TextDirection.h>
/***********************************/
GLOBAL_FUNCTION(Arrow, 10) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GtkArrowType arrow_type = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int fill = Args[5].Val == $true;
	int x = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[9].Val)->Value;
	gtk_draw_arrow(style, window, state_type, shadow_type, arrow_type, fill, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(Box, 8) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[7].Val)->Value;
	gtk_draw_box(style, window, state_type, shadow_type, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(BoxGap, 11) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[7].Val)->Value;
	GtkPositionType gap_side = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int gap_x = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int gap_width = ((Std$Integer_smallt *)Args[10].Val)->Value;
	gtk_draw_box_gap(style, window, state_type, shadow_type, x, y, width, height, gap_side, gap_x, gap_width);
	return SUCCESS;
};

GLOBAL_FUNCTION(Check, 8) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[7].Val)->Value;
	gtk_draw_check(style, window, state_type, shadow_type, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(Diamond, 8) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[7].Val)->Value;
	gtk_draw_diamond(style, window, state_type, shadow_type, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(Expander, 6) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GtkExpanderStyle expander_style = ((Std$Integer_smallt *)Args[5].Val)->Value;
	gtk_draw_expander(style, window, state_type, x, y, expander_style);
	return SUCCESS;
};

GLOBAL_FUNCTION(Extension, 9) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[7].Val)->Value;
	GtkPositionType gap_side = ((Std$Integer_smallt *)Args[8].Val)->Value;
	gtk_draw_extension(style, window, state_type, shadow_type, x, y, width, height, gap_side);
	return SUCCESS;
};

GLOBAL_FUNCTION(FlatBox, 8) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[7].Val)->Value;
	gtk_draw_flat_box(style, window, state_type, shadow_type, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(Focus, 6) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[5].Val)->Value;
	gtk_draw_focus(style, window, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(Handle, 9) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[7].Val)->Value;
	GtkOrientation orientation = ((Std$Integer_smallt *)Args[8].Val)->Value;
	gtk_draw_handle(style, window, state_type, shadow_type, x, y, width, height, orientation);
	return SUCCESS;
};

GLOBAL_FUNCTION(Hline, 6) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int x1 = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int x2 = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	gtk_draw_hline(style, window, state_type, x1, x2, y);
	return SUCCESS;
};

GLOBAL_FUNCTION(InsertionCursor, 7) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDrawable * drawable = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[2].Val)->Value;
	GdkRectangle * location= &((Gtk$Gdk$Rectangle_t *)Args[3].Val)->Value;
	int is_primary = Args[4].Val == $true;
	GtkTextDirection direction = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int draw_arrow = Args[6].Val == $true;
	gtk_draw_insertion_cursor(widget, drawable, area, location, is_primary, direction, draw_arrow);
	return SUCCESS;
};

GLOBAL_FUNCTION(Layout, 7) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int use_text = Args[3].Val == $true;
	int x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	PangoLayout * layout = ((Gtk$GObject$Object_t *)Args[6].Val)->Handle;
	gtk_draw_layout(style, window, state_type, use_text, x, y, layout);
	return SUCCESS;
};

GLOBAL_FUNCTION(Option, 8) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[7].Val)->Value;
	gtk_draw_option(style, window, state_type, shadow_type, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(Polygon, 7) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkPoint * points= &((Gtk$Gdk$Point_t *)Args[4].Val)->Value;
	int npoints = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int fill = Args[6].Val == $true;
	gtk_draw_polygon(style, window, state_type, shadow_type, points, npoints, fill);
	return SUCCESS;
};

GLOBAL_FUNCTION(ResizeGrip, 8) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkWindowEdge edge = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[7].Val)->Value;
	gtk_draw_resize_grip(style, window, state_type, edge, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(Shadow, 8) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[7].Val)->Value;
	gtk_draw_shadow(style, window, state_type, shadow_type, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(ShadowGap, 11) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[7].Val)->Value;
	GtkPositionType gap_side = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int gap_x = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int gap_width = ((Std$Integer_smallt *)Args[10].Val)->Value;
	gtk_draw_shadow_gap(style, window, state_type, shadow_type, x, y, width, height, gap_side, gap_x, gap_width);
	return SUCCESS;
};

GLOBAL_FUNCTION(Slider, 9) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[7].Val)->Value;
	GtkOrientation orientation = ((Std$Integer_smallt *)Args[8].Val)->Value;
	gtk_draw_slider(style, window, state_type, shadow_type, x, y, width, height, orientation);
	return SUCCESS;
};

GLOBAL_FUNCTION(String, 6) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	char *string = Std$String$flatten(Args[5].Val);
	gtk_draw_string(style, window, state_type, x, y, string);
	return SUCCESS;
};

GLOBAL_FUNCTION(Tab, 8) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[7].Val)->Value;
	gtk_draw_tab(style, window, state_type, shadow_type, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(Vline, 6) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y1_ = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int y2_ = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[5].Val)->Value;
	gtk_draw_vline(style, window, state_type, y1_, y2_, x);
	return SUCCESS;
};

