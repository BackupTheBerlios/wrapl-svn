#include <Gtk/Gtk/Clipboard.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 17
#include <Gtk/Gdk/Pixbuf.h>
#include <Gtk/Gtk/ClipboardGetFunc.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/ClipboardReceivedFunc.h>
#include <Gtk/Gtk/TargetEntry.h>
#include <Gtk/Gtk/ClipboardTargetsReceivedFunc.h>
#include <Gtk/Gdk/Atom.h>
#include <Gtk/Gtk/Clipboard.h>
#include <Gtk/Gtk/ClipboardClearFunc.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/ClipboardRichTextReceivedFunc.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/ClipboardTextReceivedFunc.h>
#include <Gtk/Gtk/SelectionData.h>
#include <Gtk/Gtk/TextBuffer.h>
#include <Gtk/Gtk/ClipboardImageReceivedFunc.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(Get, 1) {
	GdkAtom selection = 0;
	GtkClipboard * result = gtk_clipboard_get(selection);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetForDisplay, 2) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom selection = 0;
	GtkClipboard * result = gtk_clipboard_get_for_display(display, selection);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_clipboard_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Clear", TYP, T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_clipboard_clear(self);
	return SUCCESS;
};

METHOD("GetDisplay", TYP, T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDisplay * result = gtk_clipboard_get_display(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetOwner", TYP, T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GObject* result = gtk_clipboard_get_owner(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("RequestContents", TYP, T, TYP, Std$Object$T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom target = 0;
	GtkClipboardReceivedFunc callback = Gtk$Gtk$ClipboardReceivedFunc$new(Args[2].Val);
	void *user_data = ((Std$Address_t *)Args[3].Val)->Value;
	gtk_clipboard_request_contents(self, target, callback, user_data);
	return SUCCESS;
};

METHOD("RequestImage", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkClipboardImageReceivedFunc callback = Gtk$Gtk$ClipboardImageReceivedFunc$new(Args[1].Val);
	void *user_data = ((Std$Address_t *)Args[2].Val)->Value;
	gtk_clipboard_request_image(self, callback, user_data);
	return SUCCESS;
};

METHOD("RequestRichText", TYP, T, TYP, Gtk$Gtk$TextBuffer$T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextBuffer * buffer = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkClipboardRichTextReceivedFunc callback = Gtk$Gtk$ClipboardRichTextReceivedFunc$new(Args[2].Val);
	void *user_data = ((Std$Address_t *)Args[3].Val)->Value;
	gtk_clipboard_request_rich_text(self, buffer, callback, user_data);
	return SUCCESS;
};

METHOD("RequestTargets", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkClipboardTargetsReceivedFunc callback = Gtk$Gtk$ClipboardTargetsReceivedFunc$new(Args[1].Val);
	void *user_data = ((Std$Address_t *)Args[2].Val)->Value;
	gtk_clipboard_request_targets(self, callback, user_data);
	return SUCCESS;
};

METHOD("RequestText", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkClipboardTextReceivedFunc callback = Gtk$Gtk$ClipboardTextReceivedFunc$new(Args[1].Val);
	void *user_data = ((Std$Address_t *)Args[2].Val)->Value;
	gtk_clipboard_request_text(self, callback, user_data);
	return SUCCESS;
};

METHOD("SetCanStore", TYP, T, TYP, Gtk$Gtk$TargetEntry$T, TYP, Std$Integer$SmallT) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTargetEntry * targets= &((Gtk$Gtk$TargetEntry_t *)Args[1].Val)->Value;
	int n_targets = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_clipboard_set_can_store(self, targets, n_targets);
	return SUCCESS;
};

METHOD("SetImage", TYP, T, TYP, Gtk$Gdk$Pixbuf$T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_clipboard_set_image(self, pixbuf);
	return SUCCESS;
};

METHOD("SetText", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *text = Std$String$flatten(Args[1].Val);
	int len = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_clipboard_set_text(self, text, len);
	return SUCCESS;
};

METHOD("SetWithData", TYP, T, TYP, Gtk$Gtk$TargetEntry$T, TYP, Std$Integer$SmallT, TYP, Std$Function$T, TYP, Std$Function$T, TYP, Std$Address$T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTargetEntry * targets= &((Gtk$Gtk$TargetEntry_t *)Args[1].Val)->Value;
	int n_targets = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkClipboardGetFunc get_func = Gtk$Gtk$ClipboardGetFunc$new(Args[3].Val);
	GtkClipboardClearFunc clear_func = Gtk$Gtk$ClipboardClearFunc$new(Args[4].Val);
	void *user_data = ((Std$Address_t *)Args[5].Val)->Value;
	int result = gtk_clipboard_set_with_data(self, targets, n_targets, get_func, clear_func, user_data);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetWithOwner", TYP, T, TYP, Gtk$Gtk$TargetEntry$T, TYP, Std$Integer$SmallT, TYP, Std$Function$T, TYP, Std$Function$T, TYP, Gtk$GObject$Object$T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTargetEntry * targets= &((Gtk$Gtk$TargetEntry_t *)Args[1].Val)->Value;
	int n_targets = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GtkClipboardGetFunc get_func = Gtk$Gtk$ClipboardGetFunc$new(Args[3].Val);
	GtkClipboardClearFunc clear_func = Gtk$Gtk$ClipboardClearFunc$new(Args[4].Val);
	GObject* owner = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	int result = gtk_clipboard_set_with_owner(self, targets, n_targets, get_func, clear_func, owner);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Store", TYP, T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_clipboard_store(self);
	return SUCCESS;
};

METHOD("WaitForContents", TYP, T, TYP, Std$Object$T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom target = 0;
	GtkSelectionData * result = gtk_clipboard_wait_for_contents(self, target);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("WaitForImage", TYP, T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * result = gtk_clipboard_wait_for_image(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("WaitForRichText", TYP, T, TYP, Gtk$Gtk$TextBuffer$T, TYP, Gtk$Gdk$Atom$T, TYP, Std$Object$T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextBuffer * buffer = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkAtom * format= ((Gtk$Gdk$Atom_t *)Args[2].Val)->Value;
	gsize* length = 0;
	guint8* result = gtk_clipboard_wait_for_rich_text(self, buffer, format, length);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("WaitForTargets", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom** targets = 0;
	gint* n_targets = 0;
	int result = gtk_clipboard_wait_for_targets(self, targets, n_targets);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("WaitForText", TYP, T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char * result = gtk_clipboard_wait_for_text(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("WaitIsImageAvailable", TYP, T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_clipboard_wait_is_image_available(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("WaitIsRichTextAvailable", TYP, T, TYP, Gtk$Gtk$TextBuffer$T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTextBuffer * buffer = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_clipboard_wait_is_rich_text_available(self, buffer);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("WaitIsTargetAvailable", TYP, T, TYP, Std$Object$T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom target = 0;
	int result = gtk_clipboard_wait_is_target_available(self, target);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("WaitIsTextAvailable", TYP, T) {
	GtkClipboard * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_clipboard_wait_is_text_available(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

