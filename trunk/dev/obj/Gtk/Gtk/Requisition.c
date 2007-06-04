#include <Gtk/Gtk/Requisition.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gtk/Requisition.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_requisition_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GtkRequisition * self= &((Gtk$Gtk$Requisition_t *)Args[0].Val)->Value;
	GtkRequisition * result = gtk_requisition_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	GtkRequisition * self= &((Gtk$Gtk$Requisition_t *)Args[0].Val)->Value;
	gtk_requisition_free(self);
	return SUCCESS;
};

