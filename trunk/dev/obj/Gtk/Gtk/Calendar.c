#include <Gtk/Gtk/Calendar.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Std/Boolean.h>
#include <Gtk/Gtk/Calendar.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
/***********************************/
TYPE(T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkCalendar * result = gtk_calendar_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_calendar_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("ClearMarks", TYP, T) {
	GtkCalendar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_calendar_clear_marks(self);
	return SUCCESS;
};

METHOD("DisplayOptions", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCalendar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int flags = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_calendar_display_options(self, flags);
	return SUCCESS;
};

METHOD("Freeze", TYP, T) {
	GtkCalendar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_calendar_freeze(self);
	return SUCCESS;
};

METHOD("GetDate", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkCalendar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	guint* year = 0;
	guint* month = 0;
	guint* day = 0;
	gtk_calendar_get_date(self, year, month, day);
	return SUCCESS;
};

METHOD("GetDisplayOptions", TYP, T) {
	GtkCalendar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_calendar_get_display_options(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("MarkDay", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCalendar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int day = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_calendar_mark_day(self, day);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SelectDay", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCalendar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int day = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_calendar_select_day(self, day);
	return SUCCESS;
};

METHOD("SelectMonth", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkCalendar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int month = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int year = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gtk_calendar_select_month(self, month, year);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetDisplayOptions", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCalendar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int flags = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_calendar_set_display_options(self, flags);
	return SUCCESS;
};

METHOD("Thaw", TYP, T) {
	GtkCalendar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_calendar_thaw(self);
	return SUCCESS;
};

METHOD("UnmarkDay", TYP, T, TYP, Std$Integer$SmallT) {
	GtkCalendar * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int day = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_calendar_unmark_day(self, day);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

