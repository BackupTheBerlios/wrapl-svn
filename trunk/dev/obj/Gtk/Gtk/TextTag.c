#include <Gtk/Gtk/TextTag.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Std/Boolean.h>
#include <Gtk/Gtk/TextTag.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/TextIter.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	char *name = Std$String$flatten(Args[0].Val);
	GtkTextTag * result = gtk_text_tag_new(name);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_text_tag_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Event", TYP, T, TYP, Gtk$GObject$Object$T, TYP, Std$Object$T, TYP, Gtk$Gtk$TextIter$T) {
	GtkTextTag * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GObject* event_object = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkEvent* event = 0;
	GtkTextIter * iter= &((Gtk$Gtk$TextIter_t *)Args[3].Val)->Value;
	int result = gtk_text_tag_event(self, event_object, event, iter);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetPriority", TYP, T) {
	GtkTextTag * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_tag_get_priority(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("SetPriority", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTextTag * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int priority = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_text_tag_set_priority(self, priority);
	return SUCCESS;
};

