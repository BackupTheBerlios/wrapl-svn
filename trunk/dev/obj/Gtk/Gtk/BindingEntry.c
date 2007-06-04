#include <Gtk/Gtk/BindingEntry.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 2
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/BindingSet.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(AddSignal, 6) {
	GtkBindingSet * binding_set= ((Gtk$Gtk$BindingSet_t *)Args[0].Val)->Value;
	int keyval = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int modifiers = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char *signal_name = Std$String$flatten(Args[3].Val);
	int n_args = ((Std$Integer_smallt *)Args[4].Val)->Value;
	char *___ = 0;
	gtk_binding_entry_add_signal(binding_set, keyval, modifiers, signal_name, n_args, ___);
	return SUCCESS;
};

GLOBAL_FUNCTION(AddSignall, 5) {
	GtkBindingSet * binding_set= ((Gtk$Gtk$BindingSet_t *)Args[0].Val)->Value;
	int keyval = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int modifiers = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char *signal_name = Std$String$flatten(Args[3].Val);
	GSList* binding_args = 0;
	gtk_binding_entry_add_signall(binding_set, keyval, modifiers, signal_name, binding_args);
	return SUCCESS;
};

GLOBAL_FUNCTION(Clear, 3) {
	GtkBindingSet * binding_set= ((Gtk$Gtk$BindingSet_t *)Args[0].Val)->Value;
	int keyval = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int modifiers = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_binding_entry_clear(binding_set, keyval, modifiers);
	return SUCCESS;
};

GLOBAL_FUNCTION(Remove, 3) {
	GtkBindingSet * binding_set= ((Gtk$Gtk$BindingSet_t *)Args[0].Val)->Value;
	int keyval = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int modifiers = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_binding_entry_remove(binding_set, keyval, modifiers);
	return SUCCESS;
};

