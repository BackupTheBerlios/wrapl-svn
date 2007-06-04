#include <Gtk/Gtk/TargetList.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Std/Boolean.h>
#include <Gtk/Gtk/TargetEntry.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/TextBuffer.h>
#include <Gtk/Gtk/TargetList.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 2) {
	GtkTargetEntry * targets= &((Gtk$Gtk$TargetEntry_t *)Args[0].Val)->Value;
	int ntargets = ((Std$Integer_smallt *)Args[1].Val)->Value;
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gtk_target_list_new(targets, ntargets);
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_target_list_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Add", TYP, T, TYP, Std$Object$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkTargetList * self= ((Gtk$Gtk$TargetList_t *)Args[0].Val)->Value;
	GdkAtom target = 0;
	int flags = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int info = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_target_list_add(self, target, flags, info);
	return SUCCESS;
};

METHOD("AddImageTargets", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Symbol$T) {
	GtkTargetList * self= ((Gtk$Gtk$TargetList_t *)Args[0].Val)->Value;
	int info = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int writable = Args[2].Val == $true;
	gtk_target_list_add_image_targets(self, info, writable);
	return SUCCESS;
};

METHOD("AddRichTextTargets", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Symbol$T, TYP, Gtk$Gtk$TextBuffer$T) {
	GtkTargetList * self= ((Gtk$Gtk$TargetList_t *)Args[0].Val)->Value;
	int info = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int deserializable = Args[2].Val == $true;
	GtkTextBuffer * buffer = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	gtk_target_list_add_rich_text_targets(self, info, deserializable, buffer);
	return SUCCESS;
};

METHOD("AddTable", TYP, T, TYP, Gtk$Gtk$TargetEntry$T, TYP, Std$Integer$SmallT) {
	GtkTargetList * self= ((Gtk$Gtk$TargetList_t *)Args[0].Val)->Value;
	GtkTargetEntry * targets= &((Gtk$Gtk$TargetEntry_t *)Args[1].Val)->Value;
	int ntargets = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_target_list_add_table(self, targets, ntargets);
	return SUCCESS;
};

METHOD("AddTextTargets", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTargetList * self= ((Gtk$Gtk$TargetList_t *)Args[0].Val)->Value;
	int info = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_target_list_add_text_targets(self, info);
	return SUCCESS;
};

METHOD("AddUriTargets", TYP, T, TYP, Std$Integer$SmallT) {
	GtkTargetList * self= ((Gtk$Gtk$TargetList_t *)Args[0].Val)->Value;
	int info = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_target_list_add_uri_targets(self, info);
	return SUCCESS;
};

METHOD("Find", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkTargetList * self= ((Gtk$Gtk$TargetList_t *)Args[0].Val)->Value;
	GdkAtom target = 0;
	guint* info = 0;
	int result = gtk_target_list_find(self, target, info);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GtkTargetList * self= ((Gtk$Gtk$TargetList_t *)Args[0].Val)->Value;
	GtkTargetList * result = gtk_target_list_ref(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Remove", TYP, T, TYP, Std$Object$T) {
	GtkTargetList * self= ((Gtk$Gtk$TargetList_t *)Args[0].Val)->Value;
	GdkAtom target = 0;
	gtk_target_list_remove(self, target);
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GtkTargetList * self= ((Gtk$Gtk$TargetList_t *)Args[0].Val)->Value;
	gtk_target_list_unref(self);
	return SUCCESS;
};

