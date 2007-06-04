#include <Gtk/Gtk/Global.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 20
#include <Std/Boolean.h>
#include <Gtk/Gtk/PositionType.h>
#include <Gtk/Gtk/ExpanderStyle.h>
#include <Gtk/Pango/Language.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/Layout.h>
#include <Gtk/Gtk/Orientation.h>
#include <Gtk/Gdk/Point.h>
#include <Gtk/Gtk/Style.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/ShadowType.h>
#include <Gtk/Gdk/WindowEdge.h>
#include <Gtk/Gtk/StateType.h>
#include <Gtk/Gtk/ArrowType.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Gtk/Gdk/Screen.h>
#include <Gtk/Gdk/Window.h>
#include <Gtk/Gtk/Widget.h>
#include <Gtk/Gtk/Window.h>
#include <Std/Boolean.h>
/***********************************/
GLOBAL_FUNCTION(AlternativeDialogButtonOrder, 1) {
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_alternative_dialog_button_order(screen);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(BindingParseBinding, 1) {
	GScanner* scanner = 0;
	int result = gtk_binding_parse_binding(scanner);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(CheckVersion, 3) {
	int required_major = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int required_minor = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int required_micro = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char * result = gtk_check_version(required_major, required_minor, required_micro);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(DisableSetlocale, 0) {
	gtk_disable_setlocale();
	return SUCCESS;
};

GLOBAL_FUNCTION(EventsPending, 0) {
	int result = gtk_events_pending();
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetCurrentEvent, 0) {
	GdkEvent* result = gtk_get_current_event();
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetCurrentEventState, 1) {
	GdkModifierType* state = 0;
	int result = gtk_get_current_event_state(state);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetCurrentEventTime, 0) {
	int result = gtk_get_current_event_time();
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetDefaultLanguage, 0) {
	PangoLanguage * result = gtk_get_default_language();
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetEventWidget, 1) {
	GdkEvent* event = 0;
	GtkWidget * result = gtk_get_event_widget(event);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetOptionGroup, 1) {
	int open_default_display = Args[0].Val == $true;
	GOptionGroup* result = gtk_get_option_group(open_default_display);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(IdentifierGetType, 0) {
	GType result = gtk_identifier_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintArrow, 13) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	GtkArrowType arrow_type = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int fill = Args[8].Val == $true;
	int x = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[10].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[11].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[12].Val)->Value;
	gtk_paint_arrow(style, window, state_type, shadow_type, area, widget, detail, arrow_type, fill, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintBox, 11) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	int x = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[10].Val)->Value;
	gtk_paint_box(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintBoxGap, 14) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	int x = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[10].Val)->Value;
	GtkPositionType gap_side = ((Std$Integer_smallt *)Args[11].Val)->Value;
	int gap_x = ((Std$Integer_smallt *)Args[12].Val)->Value;
	int gap_width = ((Std$Integer_smallt *)Args[13].Val)->Value;
	gtk_paint_box_gap(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, gap_side, gap_x, gap_width);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintCheck, 11) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	int x = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[10].Val)->Value;
	gtk_paint_check(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintDiamond, 11) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	int x = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[10].Val)->Value;
	gtk_paint_diamond(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintExpander, 9) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[3].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[4].Val)->Handle;
	char *detail = Std$String$flatten(Args[5].Val);
	int x = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[7].Val)->Value;
	GtkExpanderStyle expander_style = ((Std$Integer_smallt *)Args[8].Val)->Value;
	gtk_paint_expander(style, window, state_type, area, widget, detail, x, y, expander_style);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintExtension, 12) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	int x = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[10].Val)->Value;
	GtkPositionType gap_side = ((Std$Integer_smallt *)Args[11].Val)->Value;
	gtk_paint_extension(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, gap_side);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintFlatBox, 11) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	int x = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[10].Val)->Value;
	gtk_paint_flat_box(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintFocus, 10) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[3].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[4].Val)->Handle;
	char *detail = Std$String$flatten(Args[5].Val);
	int x = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[9].Val)->Value;
	gtk_paint_focus(style, window, state_type, area, widget, detail, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintHandle, 12) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	int x = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[10].Val)->Value;
	GtkOrientation orientation = ((Std$Integer_smallt *)Args[11].Val)->Value;
	gtk_paint_handle(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, orientation);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintHline, 9) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[3].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[4].Val)->Handle;
	char *detail = Std$String$flatten(Args[5].Val);
	int x1 = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int x2 = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[8].Val)->Value;
	gtk_paint_hline(style, window, state_type, area, widget, detail, x1, x2, y);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintLayout, 10) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int use_text = Args[3].Val == $true;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	int x = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[8].Val)->Value;
	PangoLayout * layout = ((Gtk$GObject$Object_t *)Args[9].Val)->Handle;
	gtk_paint_layout(style, window, state_type, use_text, area, widget, detail, x, y, layout);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintOption, 11) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	int x = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[10].Val)->Value;
	gtk_paint_option(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintPolygon, 10) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	GdkPoint * points= &((Gtk$Gdk$Point_t *)Args[7].Val)->Value;
	int npoints = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int fill = Args[9].Val == $true;
	gtk_paint_polygon(style, window, state_type, shadow_type, area, widget, detail, points, npoints, fill);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintResizeGrip, 11) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[3].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[4].Val)->Handle;
	char *detail = Std$String$flatten(Args[5].Val);
	GdkWindowEdge edge = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[10].Val)->Value;
	gtk_paint_resize_grip(style, window, state_type, area, widget, detail, edge, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintShadow, 11) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	int x = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[10].Val)->Value;
	gtk_paint_shadow(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintShadowGap, 14) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	int x = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[10].Val)->Value;
	GtkPositionType gap_side = ((Std$Integer_smallt *)Args[11].Val)->Value;
	int gap_x = ((Std$Integer_smallt *)Args[12].Val)->Value;
	int gap_width = ((Std$Integer_smallt *)Args[13].Val)->Value;
	gtk_paint_shadow_gap(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, gap_side, gap_x, gap_width);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintSlider, 12) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	int x = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[10].Val)->Value;
	GtkOrientation orientation = ((Std$Integer_smallt *)Args[11].Val)->Value;
	gtk_paint_slider(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, orientation);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintString, 9) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[3].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[4].Val)->Handle;
	char *detail = Std$String$flatten(Args[5].Val);
	int x = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[7].Val)->Value;
	char *string = Std$String$flatten(Args[8].Val);
	gtk_paint_string(style, window, state_type, area, widget, detail, x, y, string);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintTab, 11) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkShadowType shadow_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	int x = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[10].Val)->Value;
	gtk_paint_tab(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
	return SUCCESS;
};

GLOBAL_FUNCTION(PaintVline, 9) {
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[3].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[4].Val)->Handle;
	char *detail = Std$String$flatten(Args[5].Val);
	int y1_ = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int y2_ = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[8].Val)->Value;
	gtk_paint_vline(style, window, state_type, area, widget, detail, y1_, y2_, x);
	return SUCCESS;
};

GLOBAL_FUNCTION(ParseArgs, 2) {
	int* argc = 0;
	char*** argv = 0;
	int result = gtk_parse_args(argc, argv);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(PrivateFlagsGetType, 0) {
	GType result = gtk_private_flags_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(PropagateEvent, 2) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkEvent* event = 0;
	gtk_propagate_event(widget, event);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetLocale, 0) {
	char * result = gtk_set_locale();
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ShowAboutDialog, 3) {
	GtkWindow * parent = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *first_property_name = Std$String$flatten(Args[1].Val);
	char *___ = 0;
	gtk_show_about_dialog(parent, first_property_name, ___);
	return SUCCESS;
};

