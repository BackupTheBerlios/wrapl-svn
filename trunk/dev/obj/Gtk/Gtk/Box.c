#include <Gtk/Gtk/Box.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Std/Boolean.h>
#include <Gtk/Gtk/Box.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/PackType.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
/***********************************/
TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_box_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetHomogeneous", TYP, T) {
	GtkBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_box_get_homogeneous(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetSpacing", TYP, T) {
	GtkBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_box_get_spacing(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("PackEnd", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Symbol$T, TYP, Std$Symbol$T, TYP, Std$Integer$SmallT) {
	GtkBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int expand = Args[2].Val == $true;
	int fill = Args[3].Val == $true;
	int padding = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_box_pack_end(self, child, expand, fill, padding);
	return SUCCESS;
};

METHOD("PackEndDefaults", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_box_pack_end_defaults(self, widget);
	return SUCCESS;
};

METHOD("PackStart", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Symbol$T, TYP, Std$Symbol$T, TYP, Std$Integer$SmallT) {
	GtkBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int expand = Args[2].Val == $true;
	int fill = Args[3].Val == $true;
	int padding = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_box_pack_start(self, child, expand, fill, padding);
	return SUCCESS;
};

METHOD("PackStartDefaults", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_box_pack_start_defaults(self, widget);
	return SUCCESS;
};

METHOD("QueryChildPacking", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gboolean* expand = 0;
	gboolean* fill = 0;
	guint* padding = 0;
	GtkPackType* pack_type = 0;
	gtk_box_query_child_packing(self, child, expand, fill, padding, pack_type);
	return SUCCESS;
};

METHOD("ReorderChild", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT) {
	GtkBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_box_reorder_child(self, child, position);
	return SUCCESS;
};

METHOD("SetChildPacking", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Symbol$T, TYP, Std$Symbol$T, TYP, Std$Integer$SmallT, TYP, Gtk$Gtk$PackType$T) {
	GtkBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int expand = Args[2].Val == $true;
	int fill = Args[3].Val == $true;
	int padding = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GtkPackType pack_type = ((Std$Integer_smallt *)Args[5].Val)->Value;
	gtk_box_set_child_packing(self, child, expand, fill, padding, pack_type);
	return SUCCESS;
};

METHOD("SetHomogeneous", TYP, T, TYP, Std$Symbol$T) {
	GtkBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int homogeneous = Args[1].Val == $true;
	gtk_box_set_homogeneous(self, homogeneous);
	return SUCCESS;
};

METHOD("SetSpacing", TYP, T, TYP, Std$Integer$SmallT) {
	GtkBox * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int spacing = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_box_set_spacing(self, spacing);
	return SUCCESS;
};

