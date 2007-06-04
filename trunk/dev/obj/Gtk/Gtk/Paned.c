#include <Gtk/Gtk/Paned.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/Paned.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_paned_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Add1", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkPaned * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_paned_add1(self, child);
	return SUCCESS;
};

METHOD("Add2", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkPaned * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_paned_add2(self, child);
	return SUCCESS;
};

METHOD("ComputePosition", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkPaned * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int allocation = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int child1_req = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int child2_req = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_paned_compute_position(self, allocation, child1_req, child2_req);
	return SUCCESS;
};

METHOD("GetChild1", TYP, T) {
	GtkPaned * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_paned_get_child1(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetChild2", TYP, T) {
	GtkPaned * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_paned_get_child2(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPosition", TYP, T) {
	GtkPaned * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_paned_get_position(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Pack1", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Symbol$T, TYP, Std$Symbol$T) {
	GtkPaned * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int resize = Args[2].Val == $true;
	int shrink = Args[3].Val == $true;
	gtk_paned_pack1(self, child, resize, shrink);
	return SUCCESS;
};

METHOD("Pack2", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Symbol$T, TYP, Std$Symbol$T) {
	GtkPaned * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int resize = Args[2].Val == $true;
	int shrink = Args[3].Val == $true;
	gtk_paned_pack2(self, child, resize, shrink);
	return SUCCESS;
};

METHOD("SetPosition", TYP, T, TYP, Std$Integer$SmallT) {
	GtkPaned * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_paned_set_position(self, position);
	return SUCCESS;
};

