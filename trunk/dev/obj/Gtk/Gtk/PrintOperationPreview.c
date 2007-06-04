#include <Gtk/Gtk/PrintOperationPreview.h>
#include <Riva/Memory.h>
#include <Gtk/Gtk/PrintOperationPreview.h>
#include <Gtk/GObject/Type.h>
#include <Std/Boolean.h>
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_print_operation_preview_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("EndPreview", TYP, T) {
	GtkPrintOperationPreview * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_print_operation_preview_end_preview(self);
	return SUCCESS;
};

METHOD("IsSelected", TYP, T, TYP, Std$Integer$SmallT) {
	GtkPrintOperationPreview * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int page_nr = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gtk_print_operation_preview_is_selected(self, page_nr);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("RenderPage", TYP, T, TYP, Std$Integer$SmallT) {
	GtkPrintOperationPreview * self = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int page_nr = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_print_operation_preview_render_page(self, page_nr);
	return SUCCESS;
};

