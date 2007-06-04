#include <Gtk/Gtk/Style.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 15
#include <Gtk/Gtk/TextDirection.h>
#include <Gtk/Gtk/IconSource.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/IconSize.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/Gtk/IconSet.h>
#include <Gtk/Gtk/Style.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/StateType.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Gtk/Gdk/Window.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
#include <Gtk/Gdk/Font.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkStyle * result = gtk_style_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_style_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("ApplyDefaultBackground", TYP, T, TYP, Gtk$Gdk$Window$T, TYP, Std$Symbol$T, TYP, Gtk$Gtk$StateType$T, TYP, Gtk$Gdk$Rectangle$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkStyle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int set_bg = Args[2].Val == $true;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[8].Val)->Value;
	gtk_style_apply_default_background(self, window, set_bg, state_type, area, x, y, width, height);
	return SUCCESS;
};

METHOD("Attach", TYP, T, TYP, Gtk$Gdk$Window$T) {
	GtkStyle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStyle * result = gtk_style_attach(self, window);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GtkStyle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkStyle * result = gtk_style_copy(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Detach", TYP, T) {
	GtkStyle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_style_detach(self);
	return SUCCESS;
};

METHOD("GetFont", TYP, T) {
	GtkStyle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkFont * result = gtk_style_get_font(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("LookupColor", TYP, T, TYP, Std$String$T, TYP, Gtk$Gdk$Color$T) {
	GtkStyle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *color_name = Std$String$flatten(Args[1].Val);
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[2].Val)->Value;
	int result = gtk_style_lookup_color(self, color_name, color);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("LookupIconSet", TYP, T, TYP, Std$String$T) {
	GtkStyle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *stock_id = Std$String$flatten(Args[1].Val);
	GtkIconSet * result = gtk_style_lookup_icon_set(self, stock_id);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GtkStyle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkStyle * result = gtk_style_ref(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("RenderIcon", TYP, T, TYP, Gtk$Gtk$IconSource$T, TYP, Gtk$Gtk$TextDirection$T, TYP, Gtk$Gtk$StateType$T, TYP, Gtk$Gtk$IconSize$T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T) {
	GtkStyle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkIconSource * source= ((Gtk$Gtk$IconSource_t *)Args[1].Val)->Value;
	GtkTextDirection direction = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkStateType state = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GtkIconSize size = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	GdkPixbuf * result = gtk_style_render_icon(self, source, direction, state, size, widget, detail);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("SetBackground", TYP, T, TYP, Gtk$Gdk$Window$T, TYP, Gtk$Gtk$StateType$T) {
	GtkStyle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkStateType state_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_style_set_background(self, window, state_type);
	return SUCCESS;
};

METHOD("SetFont", TYP, T, TYP, Gtk$Gdk$Font$T) {
	GtkStyle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[1].Val)->Value;
	gtk_style_set_font(self, font);
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GtkStyle * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_style_unref(self);
	return SUCCESS;
};

