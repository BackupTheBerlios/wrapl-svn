#include <Gtk/Gtk/IconSource.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 8
#include <Std/Boolean.h>
#include <Gtk/Gtk/TextDirection.h>
#include <Gtk/Gtk/IconSource.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/IconSize.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/StateType.h>
#include <Gtk/Gdk/Pixbuf.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(New, 0) {
	Gtk$GObject$Object_t *result = new(Gtk$GObject$Object_t);
	result->Type = T;
	result->Handle = gtk_icon_source_new();
	Result->Val= result;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_icon_source_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	GtkIconSource * result = gtk_icon_source_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	gtk_icon_source_free(self);
	return SUCCESS;
};

METHOD("GetDirection", TYP, T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	GtkTextDirection result = gtk_icon_source_get_direction(self);
	Gtk$Gtk$TextDirection_t *_result = new(Gtk$Gtk$TextDirection_t);
	_result->Type = Gtk$Gtk$TextDirection$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetDirectionWildcarded", TYP, T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	int result = gtk_icon_source_get_direction_wildcarded(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetFilename", TYP, T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	const char * result = gtk_icon_source_get_filename(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetIconName", TYP, T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	const char * result = gtk_icon_source_get_icon_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetPixbuf", TYP, T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	GdkPixbuf * result = gtk_icon_source_get_pixbuf(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetSize", TYP, T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	GtkIconSize result = gtk_icon_source_get_size(self);
	Gtk$Gtk$IconSize_t *_result = new(Gtk$Gtk$IconSize_t);
	_result->Type = Gtk$Gtk$IconSize$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetSizeWildcarded", TYP, T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	int result = gtk_icon_source_get_size_wildcarded(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetState", TYP, T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	GtkStateType result = gtk_icon_source_get_state(self);
	Gtk$Gtk$StateType_t *_result = new(Gtk$Gtk$StateType_t);
	_result->Type = Gtk$Gtk$StateType$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetStateWildcarded", TYP, T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	int result = gtk_icon_source_get_state_wildcarded(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetDirection", TYP, T, TYP, Gtk$Gtk$TextDirection$T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	GtkTextDirection direction = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_icon_source_set_direction(self, direction);
	return SUCCESS;
};

METHOD("SetDirectionWildcarded", TYP, T, TYP, Std$Symbol$T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	int setting = Args[1].Val == $true;
	gtk_icon_source_set_direction_wildcarded(self, setting);
	return SUCCESS;
};

METHOD("SetFilename", TYP, T, TYP, Std$String$T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	char *filename = Std$String$flatten(Args[1].Val);
	gtk_icon_source_set_filename(self, filename);
	return SUCCESS;
};

METHOD("SetIconName", TYP, T, TYP, Std$String$T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	char *icon_name = Std$String$flatten(Args[1].Val);
	gtk_icon_source_set_icon_name(self, icon_name);
	return SUCCESS;
};

METHOD("SetPixbuf", TYP, T, TYP, Gtk$Gdk$Pixbuf$T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_icon_source_set_pixbuf(self, pixbuf);
	return SUCCESS;
};

METHOD("SetSize", TYP, T, TYP, Gtk$Gtk$IconSize$T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	GtkIconSize size = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_icon_source_set_size(self, size);
	return SUCCESS;
};

METHOD("SetSizeWildcarded", TYP, T, TYP, Std$Symbol$T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	int setting = Args[1].Val == $true;
	gtk_icon_source_set_size_wildcarded(self, setting);
	return SUCCESS;
};

METHOD("SetState", TYP, T, TYP, Gtk$Gtk$StateType$T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	GtkStateType state = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_icon_source_set_state(self, state);
	return SUCCESS;
};

METHOD("SetStateWildcarded", TYP, T, TYP, Std$Symbol$T) {
	GtkIconSource * self= ((Gtk$Gtk$IconSource_t *)Args[0].Val)->Value;
	int setting = Args[1].Val == $true;
	gtk_icon_source_set_state_wildcarded(self, setting);
	return SUCCESS;
};

