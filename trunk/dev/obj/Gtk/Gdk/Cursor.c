#include <Gtk/Gdk/Cursor.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 8
#include <Gtk/Gdk/Display.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Color.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/CursorType.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Gtk/Gdk/Pixmap.h>
#include <Gtk/Gdk/Cursor.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 1) {
	GdkCursorType cursor_type = ((Std$Integer_smallt *)Args[0].Val)->Value;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gdk_cursor_new(cursor_type);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(NewForDisplay, 2) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkCursorType cursor_type = ((Std$Integer_smallt *)Args[1].Val)->Value;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gdk_cursor_new_for_display(display, cursor_type);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromName, 2) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gdk_cursor_new_from_name(display, name);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromPixbuf, 4) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gdk_cursor_new_from_pixbuf(display, pixbuf, x, y);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromPixmap, 6) {
	GdkPixmap * source = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixmap * mask = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkColor * fg= &((Gtk$Gdk$Color_t *)Args[2].Val)->Value;
	GdkColor * bg= &((Gtk$Gdk$Color_t *)Args[3].Val)->Value;
	int x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gdk_cursor_new_from_pixmap(source, mask, fg, bg, x, y);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_cursor_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetDisplay", TYP, T) {
	GdkCursor * self= ((Gtk$Gdk$Cursor_t *)Args[0].Val)->Value;
	GdkDisplay * result = gdk_cursor_get_display(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetImage", TYP, T) {
	GdkCursor * self= ((Gtk$Gdk$Cursor_t *)Args[0].Val)->Value;
	GdkPixbuf * result = gdk_cursor_get_image(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GdkCursor * self= ((Gtk$Gdk$Cursor_t *)Args[0].Val)->Value;
	GdkCursor * result = gdk_cursor_ref(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GdkCursor * self= ((Gtk$Gdk$Cursor_t *)Args[0].Val)->Value;
	gdk_cursor_unref(self);
	return SUCCESS;
};

