#include <Gtk/Gtk/IMContext.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/IMContext.h>
#include <Gtk/Gdk/EventKey.h>
#include <Gtk/Gdk/Rectangle.h>
#include <Gtk/Gdk/Window.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_im_context_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("DeleteSurrounding", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkIMContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int offset = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int n_chars = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gtk_im_context_delete_surrounding(self, offset, n_chars);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("FilterKeypress", TYP, T, TYP, Gtk$Gdk$EventKey$T) {
	GtkIMContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkEventKey * event= &((Gtk$Gdk$EventKey_t *)Args[1].Val)->Value;
	int result = gtk_im_context_filter_keypress(self, event);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("FocusIn", TYP, T) {
	GtkIMContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_im_context_focus_in(self);
	return SUCCESS;
};

METHOD("FocusOut", TYP, T) {
	GtkIMContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_im_context_focus_out(self);
	return SUCCESS;
};

METHOD("GetPreeditString", TYP, T, TYP, Std$List$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkIMContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * str;
	PangoAttrList** attrs = 0;
	gint* cursor_pos = 0;
	gtk_im_context_get_preedit_string(self, str, attrs, cursor_pos);
	return SUCCESS;
};

METHOD("GetSurrounding", TYP, T, TYP, Std$List$T, TYP, Std$Object$T) {
	GtkIMContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * text;
	gint* cursor_index = 0;
	int result = gtk_im_context_get_surrounding(self, text, cursor_index);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Reset", TYP, T) {
	GtkIMContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_im_context_reset(self);
	return SUCCESS;
};

METHOD("SetClientWindow", TYP, T, TYP, Gtk$Gdk$Window$T) {
	GtkIMContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_im_context_set_client_window(self, window);
	return SUCCESS;
};

METHOD("SetCursorLocation", TYP, T, TYP, Gtk$Gdk$Rectangle$T) {
	GtkIMContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRectangle * area= &((Gtk$Gdk$Rectangle_t *)Args[1].Val)->Value;
	gtk_im_context_set_cursor_location(self, area);
	return SUCCESS;
};

METHOD("SetSurrounding", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkIMContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	int len = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int cursor_index = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_im_context_set_surrounding(self, text, len, cursor_index);
	return SUCCESS;
};

METHOD("SetUsePreedit", TYP, T, TYP, Std$Symbol$T) {
	GtkIMContext * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int use_preedit = Args[1].Val == $true;
	gtk_im_context_set_use_preedit(self, use_preedit);
	return SUCCESS;
};

