#include <Gtk/Gtk/CellRenderer.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 8
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/CellEditable.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Gtk/Gtk/CellRenderer.h>
#include <Gtk/Gdk/Window.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_cell_renderer_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Activate", TYP, T, TYP, Std$Object$T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T, TYP, Gtk$Gdk$Rectangle$T, TYP, Gtk$Gdk$Rectangle$T, TYP, Std$Integer$SmallT) {
	GtkCellRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkEvent* event = 0;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	char *path = Std$String$flatten(Args[3].Val);
	GdkRectangle * background_area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GdkRectangle * cell_area= &((Gtk$Gdk$Rectangle_t *)Args[5].Val)->Value;
	int flags = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int result = gtk_cell_renderer_activate(self, event, widget, path, background_area, cell_area, flags);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("EditingCanceled", TYP, T) {
	GtkCellRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_cell_renderer_editing_canceled(self);
	return SUCCESS;
};

METHOD("GetFixedSize", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkCellRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gint* width = 0;
	gint* height = 0;
	gtk_cell_renderer_get_fixed_size(self, width, height);
	return SUCCESS;
};

METHOD("GetSize", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gdk$Rectangle$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkCellRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkRectangle * cell_area= &((Gtk$Gdk$Rectangle_t *)Args[2].Val)->Value;
	gint* x_offset = 0;
	gint* y_offset = 0;
	gint* width = 0;
	gint* height = 0;
	gtk_cell_renderer_get_size(self, widget, cell_area, x_offset, y_offset, width, height);
	return SUCCESS;
};

METHOD("Render", TYP, T, TYP, Gtk$Gdk$Window$T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gdk$Rectangle$T, TYP, Gtk$Gdk$Rectangle$T, TYP, Gtk$Gdk$Rectangle$T, TYP, Std$Integer$SmallT) {
	GtkCellRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	GdkRectangle * background_area= &((Gtk$Gdk$Rectangle_t *)Args[3].Val)->Value;
	GdkRectangle * cell_area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GdkRectangle * expose_area= &((Gtk$Gdk$Rectangle_t *)Args[5].Val)->Value;
	int flags = ((Std$Integer_smallt *)Args[6].Val)->Value;
	gtk_cell_renderer_render(self, window, widget, background_area, cell_area, expose_area, flags);
	return SUCCESS;
};

METHOD("SetFixedSize", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkCellRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_cell_renderer_set_fixed_size(self, width, height);
	return SUCCESS;
};

METHOD("StartEditing", TYP, T, TYP, Std$Object$T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T, TYP, Gtk$Gdk$Rectangle$T, TYP, Gtk$Gdk$Rectangle$T, TYP, Std$Integer$SmallT) {
	GtkCellRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkEvent* event = 0;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	char *path = Std$String$flatten(Args[3].Val);
	GdkRectangle * background_area= &((Gtk$Gdk$Rectangle_t *)Args[4].Val)->Value;
	GdkRectangle * cell_area= &((Gtk$Gdk$Rectangle_t *)Args[5].Val)->Value;
	int flags = ((Std$Integer_smallt *)Args[6].Val)->Value;
	GtkCellEditable * result = gtk_cell_renderer_start_editing(self, event, widget, path, background_area, cell_area, flags);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("StopEditing", TYP, T, TYP, Std$Symbol$T) {
	GtkCellRenderer * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int canceled = Args[1].Val == $true;
	gtk_cell_renderer_stop_editing(self, canceled);
	return SUCCESS;
};

