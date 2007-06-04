#include <Gtk/Gtk/TextMark.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/TextMark.h>
#include <Gtk/Gtk/TextBuffer.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_text_mark_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetBuffer", TYP, T) {
	GtkTextMark * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextBuffer * result = gtk_text_mark_get_buffer(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetDeleted", TYP, T) {
	GtkTextMark * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_mark_get_deleted(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetLeftGravity", TYP, T) {
	GtkTextMark * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_mark_get_left_gravity(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetName", TYP, T) {
	GtkTextMark * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_text_mark_get_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetVisible", TYP, T) {
	GtkTextMark * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_mark_get_visible(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetVisible", TYP, T, TYP, Std$Symbol$T) {
	GtkTextMark * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int setting = Args[1].Val == $true;
	gtk_text_mark_set_visible(self, setting);
	return SUCCESS;
};

