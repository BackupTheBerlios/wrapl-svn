#include <Gtk/Gtk/IMContextSimple.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gtk/IMContextSimple.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$IMContext$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkIMContextSimple * result = gtk_im_context_simple_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_im_context_simple_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddTable", TYP, T, TYP, Std$Object$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkIMContextSimple * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	guint16* data = 0;
	int max_seq_len = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int n_seqs = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_im_context_simple_add_table(self, data, max_seq_len, n_seqs);
	return SUCCESS;
};

