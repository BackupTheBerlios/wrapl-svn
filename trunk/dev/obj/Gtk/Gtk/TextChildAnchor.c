#include <Gtk/Gtk/TextChildAnchor.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Std/Boolean.h>
#include <Gtk/Gtk/TextChildAnchor.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkTextChildAnchor * result = gtk_text_child_anchor_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_text_child_anchor_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetDeleted", TYP, T) {
	GtkTextChildAnchor * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_text_child_anchor_get_deleted(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetWidgets", TYP, T) {
	GtkTextChildAnchor * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GList * result = gtk_text_child_anchor_get_widgets(self);
	if (result) {
		int _length = 1;
		GList *node = result;
		node->data = Gtk$GObject$Object$to_riva(node->data);
		while (node->next) {
			node = node->next;
			node->data = Gtk$GObject$Object$to_riva(node->data);
			_length++;
		};
		Std$List_t *list = new(Std$List_t);
		list->Type = Std$List$T;
		list->Cache = list->Head = result;
		list->Tail = node;
		list->Length = _length;
		list->Index = 1;
		list->Access = 4;
		Result->Val = list;
	} else {
		Result->Val = Std$List$new(0);
	};
	return SUCCESS;
};

