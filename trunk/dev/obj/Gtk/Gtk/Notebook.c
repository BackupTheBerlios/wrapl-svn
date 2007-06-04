#include <Gtk/Gtk/Notebook.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 8
#include <Gtk/Gtk/PositionType.h>
#include <Gtk/Gtk/Notebook.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/PackType.h>
#include <Gtk/Gtk/NotebookWindowCreationFunc.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/Widget.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkNotebook * result = gtk_notebook_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_notebook_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetWindowCreationHook, 3) {
	GtkNotebookWindowCreationFunc func = Gtk$Gtk$NotebookWindowCreationFunc$new(Args[0].Val);
	void *data = ((Std$Address_t *)Args[1].Val)->Value;
	GDestroyNotify destroy = 0;
	gtk_notebook_set_window_creation_hook(func, data, destroy);
	return SUCCESS;
};

METHOD("AppendPage", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gtk$Widget$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkWidget * tab_label = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int result = gtk_notebook_append_page(self, child, tab_label);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("AppendPageMenu", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gtk$Widget$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkWidget * tab_label = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	GtkWidget * menu_label = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	int result = gtk_notebook_append_page_menu(self, child, tab_label, menu_label);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetCurrentPage", TYP, T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_notebook_get_current_page(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetGroupId", TYP, T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_notebook_get_group_id(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetMenuLabel", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkWidget * result = gtk_notebook_get_menu_label(self, child);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetMenuLabelText", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	const char * result = gtk_notebook_get_menu_label_text(self, child);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetNPages", TYP, T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_notebook_get_n_pages(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetNthPage", TYP, T, TYP, Std$Integer$SmallT) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int page_num = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkWidget * result = gtk_notebook_get_nth_page(self, page_num);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetScrollable", TYP, T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_notebook_get_scrollable(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetShowBorder", TYP, T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_notebook_get_show_border(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetShowTabs", TYP, T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_notebook_get_show_tabs(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetTabDetachable", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_notebook_get_tab_detachable(self, child);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetTabLabel", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkWidget * result = gtk_notebook_get_tab_label(self, child);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetTabLabelText", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	const char * result = gtk_notebook_get_tab_label_text(self, child);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetTabPos", TYP, T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPositionType result = gtk_notebook_get_tab_pos(self);
	Gtk$Gtk$PositionType_t *_result = new(Gtk$Gtk$PositionType_t);
	_result->Type = Gtk$Gtk$PositionType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetTabReorderable", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int result = gtk_notebook_get_tab_reorderable(self, child);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("InsertPage", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkWidget * tab_label = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int result = gtk_notebook_insert_page(self, child, tab_label, position);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("InsertPageMenu", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkWidget * tab_label = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	GtkWidget * menu_label = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int result = gtk_notebook_insert_page_menu(self, child, tab_label, menu_label, position);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("NextPage", TYP, T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_notebook_next_page(self);
	return SUCCESS;
};

METHOD("PopupDisable", TYP, T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_notebook_popup_disable(self);
	return SUCCESS;
};

METHOD("PopupEnable", TYP, T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_notebook_popup_enable(self);
	return SUCCESS;
};

METHOD("PrependPage", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gtk$Widget$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkWidget * tab_label = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int result = gtk_notebook_prepend_page(self, child, tab_label);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("PrependPageMenu", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gtk$Widget$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkWidget * tab_label = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	GtkWidget * menu_label = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	int result = gtk_notebook_prepend_page_menu(self, child, tab_label, menu_label);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("PrevPage", TYP, T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_notebook_prev_page(self);
	return SUCCESS;
};

METHOD("QueryTabLabelPacking", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gboolean* expand = 0;
	gboolean* fill = 0;
	GtkPackType* pack_type = 0;
	gtk_notebook_query_tab_label_packing(self, child, expand, fill, pack_type);
	return SUCCESS;
};

METHOD("RemovePage", TYP, T, TYP, Std$Integer$SmallT) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int page_num = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_notebook_remove_page(self, page_num);
	return SUCCESS;
};

METHOD("ReorderChild", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Integer$SmallT) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int position = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_notebook_reorder_child(self, child, position);
	return SUCCESS;
};

METHOD("SetCurrentPage", TYP, T, TYP, Std$Integer$SmallT) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int page_num = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_notebook_set_current_page(self, page_num);
	return SUCCESS;
};

METHOD("SetGroupId", TYP, T, TYP, Std$Integer$SmallT) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int group_id = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_notebook_set_group_id(self, group_id);
	return SUCCESS;
};

METHOD("SetHomogeneousTabs", TYP, T, TYP, Std$Symbol$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int homogeneous = Args[1].Val == $true;
	gtk_notebook_set_homogeneous_tabs(self, homogeneous);
	return SUCCESS;
};

METHOD("SetMenuLabel", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gtk$Widget$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkWidget * menu_label = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_notebook_set_menu_label(self, child, menu_label);
	return SUCCESS;
};

METHOD("SetMenuLabelText", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *menu_text = Std$String$flatten(Args[2].Val);
	gtk_notebook_set_menu_label_text(self, child, menu_text);
	return SUCCESS;
};

METHOD("SetScrollable", TYP, T, TYP, Std$Symbol$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int scrollable = Args[1].Val == $true;
	gtk_notebook_set_scrollable(self, scrollable);
	return SUCCESS;
};

METHOD("SetShowBorder", TYP, T, TYP, Std$Symbol$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int show_border = Args[1].Val == $true;
	gtk_notebook_set_show_border(self, show_border);
	return SUCCESS;
};

METHOD("SetShowTabs", TYP, T, TYP, Std$Symbol$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int show_tabs = Args[1].Val == $true;
	gtk_notebook_set_show_tabs(self, show_tabs);
	return SUCCESS;
};

METHOD("SetTabBorder", TYP, T, TYP, Std$Integer$SmallT) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int border_width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_notebook_set_tab_border(self, border_width);
	return SUCCESS;
};

METHOD("SetTabDetachable", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Symbol$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int detachable = Args[2].Val == $true;
	gtk_notebook_set_tab_detachable(self, child, detachable);
	return SUCCESS;
};

METHOD("SetTabHborder", TYP, T, TYP, Std$Integer$SmallT) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int tab_hborder = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_notebook_set_tab_hborder(self, tab_hborder);
	return SUCCESS;
};

METHOD("SetTabLabel", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Gtk$Gtk$Widget$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkWidget * tab_label = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	gtk_notebook_set_tab_label(self, child, tab_label);
	return SUCCESS;
};

METHOD("SetTabLabelPacking", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Symbol$T, TYP, Std$Symbol$T, TYP, Gtk$Gtk$PackType$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int expand = Args[2].Val == $true;
	int fill = Args[3].Val == $true;
	GtkPackType pack_type = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_notebook_set_tab_label_packing(self, child, expand, fill, pack_type);
	return SUCCESS;
};

METHOD("SetTabLabelText", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$String$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	char *tab_text = Std$String$flatten(Args[2].Val);
	gtk_notebook_set_tab_label_text(self, child, tab_text);
	return SUCCESS;
};

METHOD("SetTabPos", TYP, T, TYP, Gtk$Gtk$PositionType$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkPositionType pos = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_notebook_set_tab_pos(self, pos);
	return SUCCESS;
};

METHOD("SetTabReorderable", TYP, T, TYP, Gtk$Gtk$Widget$T, TYP, Std$Symbol$T) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * child = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int reorderable = Args[2].Val == $true;
	gtk_notebook_set_tab_reorderable(self, child, reorderable);
	return SUCCESS;
};

METHOD("SetTabVborder", TYP, T, TYP, Std$Integer$SmallT) {
	GtkNotebook * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int tab_vborder = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_notebook_set_tab_vborder(self, tab_vborder);
	return SUCCESS;
};

