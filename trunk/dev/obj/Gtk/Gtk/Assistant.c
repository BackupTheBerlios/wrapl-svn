#include <Gtk/Gtk/Assistant.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 8
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Assistant.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/AssistantPageFunc.h>
#include <Gtk/Gtk/AssistantPageType.h>
/***********************************/
TYPE(T, Gtk$Gtk$Window$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkAssistant * result = gtk_assistant_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_assistant_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddActionWidget", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_assistant_add_action_widget(self, child);
	return SUCCESS;
};

METHOD("AppendPage", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * page = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_assistant_append_page(self, page);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetCurrentPage", TYP, T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_assistant_get_current_page(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetNPages", TYP, T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_assistant_get_n_pages(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetNthPage", TYP, T, TYP, Std$Integer$SmallT) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int page_num = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkWidget * result = gtk_assistant_get_nth_page(self, page_num);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPageComplete", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * page = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_assistant_get_page_complete(self, page);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetPageHeaderImage", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * page = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkPixbuf * result = gtk_assistant_get_page_header_image(self, page);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPageSideImage", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * page = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkPixbuf * result = gtk_assistant_get_page_side_image(self, page);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetPageTitle", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * page = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	const char * result = gtk_assistant_get_page_title(self, page);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetPageType", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * page = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkAssistantPageType result = gtk_assistant_get_page_type(self, page);
	Gtk$Gtk$AssistantPageType_t *_result = new(Gtk$Gtk$AssistantPageType_t);
	_result->Type = Gtk$Gtk$AssistantPageType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("InsertPage", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * page = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gtk_assistant_insert_page(self, page, position);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("PrependPage", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * page = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_assistant_prepend_page(self, page);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("RemoveActionWidget", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_assistant_remove_action_widget(self, child);
	return SUCCESS;
};

METHOD("SetCurrentPage", TYP, T, TYP, Std$Integer$SmallT) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int page_num = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_assistant_set_current_page(self, page_num);
	return SUCCESS;
};

METHOD("SetForwardPageFunc", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$Object$T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkAssistantPageFunc page_func = Gtk$Gtk$AssistantPageFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GDestroyNotify destroy = 0;
	gtk_assistant_set_forward_page_func(self, page_func, data, destroy);
	return SUCCESS;
};

METHOD("SetPageComplete", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Symbol$T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * page = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int complete = Args[2].Val == $true;
	gtk_assistant_set_page_complete(self, page, complete);
	return SUCCESS;
};

METHOD("SetPageHeaderImage", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gdk$Pixbuf$T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * page = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_assistant_set_page_header_image(self, page, pixbuf);
	return SUCCESS;
};

METHOD("SetPageSideImage", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gdk$Pixbuf$T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * page = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_assistant_set_page_side_image(self, page, pixbuf);
	return SUCCESS;
};

METHOD("SetPageTitle", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * page = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *title = Std$String$flatten(Args[2].Val);
	gtk_assistant_set_page_title(self, page, title);
	return SUCCESS;
};

METHOD("SetPageType", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gtk$AssistantPageType$T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * page = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkAssistantPageType type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_assistant_set_page_type(self, page, type);
	return SUCCESS;
};

METHOD("UpdateButtonsState", TYP, T) {
	GtkAssistant * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_assistant_update_buttons_state(self);
	return SUCCESS;
};

