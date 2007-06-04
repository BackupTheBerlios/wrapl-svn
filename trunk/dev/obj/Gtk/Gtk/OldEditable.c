#include <Gtk/Gtk/OldEditable.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/OldEditable.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_old_editable_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Changed", TYP, T) {
	GtkOldEditable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_old_editable_changed(self);
	return SUCCESS;
};

METHOD("ClaimSelection", TYP, T, TYP, Std$Symbol$T, TYP, Std$Integer$SmallT) {
	GtkOldEditable * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int claim = Args[1].Val == $true;
	int time_ = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_old_editable_claim_selection(self, claim, time_);
	return SUCCESS;
};

