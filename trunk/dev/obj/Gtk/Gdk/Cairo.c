#include <Gtk/Gdk/Cairo.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Drawable.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Gtk/Gdk/Region.h>
#include <Gtk/Gdk/Pixmap.h>
/***********************************/
GLOBAL_FUNCTION(Create, 1) {
	GdkDrawable * drawable = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	cairo_t* result = gdk_cairo_create(drawable);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(Rectangle, 2) {
	cairo_t* cr = 0;
	GdkRectangle * rectangle= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	gdk_cairo_rectangle(cr, rectangle);
	return SUCCESS;
};

GLOBAL_FUNCTION(Region, 2) {
	cairo_t* cr = 0;
	GdkRegion * region= ((Gtk$Gdk$Region_t *)Args[1].Val)->Value;
	gdk_cairo_region(cr, region);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetSourceColor, 2) {
	cairo_t* cr = 0;
	GdkColor * color= &((Gtk$Gdk$Color_t *)Args[1].Val)->Value;
	gdk_cairo_set_source_color(cr, color);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetSourcePixbuf, 4) {
	cairo_t* cr = 0;
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	double pixbuf_x = ((Std$Real_t *)Args[2].Val)->Value;
	double pixbuf_y = ((Std$Real_t *)Args[3].Val)->Value;
	gdk_cairo_set_source_pixbuf(cr, pixbuf, pixbuf_x, pixbuf_y);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetSourcePixmap, 4) {
	cairo_t* cr = 0;
	GdkPixmap * pixmap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	double pixmap_x = ((Std$Real_t *)Args[2].Val)->Value;
	double pixmap_y = ((Std$Real_t *)Args[3].Val)->Value;
	gdk_cairo_set_source_pixmap(cr, pixmap, pixmap_x, pixmap_y);
	return SUCCESS;
};

