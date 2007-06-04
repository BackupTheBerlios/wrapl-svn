#include <Gtk/Gtk/IconSet.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 10
#include <Gtk/Gtk/TextDirection.h>
#include <Gtk/Gtk/IconSource.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/IconSize.h>
#include <Gtk/Gtk/IconSet.h>
#include <Gtk/Gtk/Style.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/StateType.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Gtk/Gtk/Widget.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 0) {
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gtk_icon_set_new();
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromPixbuf, 1) {
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gtk_icon_set_new_from_pixbuf(pixbuf);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_icon_set_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddSource", TYP, T, TYP, Gtk$Gtk$IconSource$T) {
	GtkIconSet * self= ((Gtk$Gtk$IconSet_t *)Args[0].Val)->Value;
	GtkIconSource * source= ((Gtk$Gtk$IconSource_t *)Args[1].Val)->Value;
	gtk_icon_set_add_source(self, source);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GtkIconSet * self= ((Gtk$Gtk$IconSet_t *)Args[0].Val)->Value;
	GtkIconSet * result = gtk_icon_set_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetSizes", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkIconSet * self= ((Gtk$Gtk$IconSet_t *)Args[0].Val)->Value;
	GtkIconSize** sizes = 0;
	gint* n_sizes = 0;
	gtk_icon_set_get_sizes(self, sizes, n_sizes);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GtkIconSet * self= ((Gtk$Gtk$IconSet_t *)Args[0].Val)->Value;
	GtkIconSet * result = gtk_icon_set_ref(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("RenderIcon", TYP, T, TYP, Gtk$Gtk$Style$T, TYP, Gtk$Gtk$TextDirection$T, TYP, Gtk$Gtk$StateType$T, TYP, Gtk$Gtk$IconSize$T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T) {
	GtkIconSet * self= ((Gtk$Gtk$IconSet_t *)Args[0].Val)->Value;
	GtkStyle * style = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTextDirection direction = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkStateType state = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GtkIconSize size = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	char *detail = Std$String$flatten(Args[6].Val);
	GdkPixbuf * result = gtk_icon_set_render_icon(self, style, direction, state, size, widget, detail);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GtkIconSet * self= ((Gtk$Gtk$IconSet_t *)Args[0].Val)->Value;
	gtk_icon_set_unref(self);
	return SUCCESS;
};

