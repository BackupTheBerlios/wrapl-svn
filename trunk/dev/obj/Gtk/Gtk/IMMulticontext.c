#include <Gtk/Gtk/IMMulticontext.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/MenuShell.h>
#include <Gtk/Gtk/IMMulticontext.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$IMContext$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkIMMulticontext * result = gtk_im_multicontext_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_im_multicontext_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AppendMenuitems", TYP, T, TYP, Gtk$Gtk$MenuShell$T) {
	GtkIMMulticontext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkMenuShell * menushell = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_im_multicontext_append_menuitems(self, menushell);
	return SUCCESS;
};

