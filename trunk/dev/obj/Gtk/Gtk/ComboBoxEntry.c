#include <Gtk/Gtk/ComboBoxEntry.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/Gtk/TreeModel.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/ComboBoxEntry.h>
/***********************************/
TYPE(T, Gtk$Gtk$ComboBox$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkComboBoxEntry * result = gtk_combo_box_entry_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewText, 0) {
	GtkComboBoxEntry * result = gtk_combo_box_entry_new_text();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewWithModel, 2) {
	GtkTreeModel * model = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int text_column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkComboBoxEntry * result = gtk_combo_box_entry_new_with_model(model, text_column);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_combo_box_entry_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetTextColumn", TYP, T) {
	GtkComboBoxEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_combo_box_entry_get_text_column(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("SetTextColumn", TYP, T, TYP, Std$Integer$SmallT) {
	GtkComboBoxEntry * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int text_column = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_combo_box_entry_set_text_column(self, text_column);
	return SUCCESS;
};

