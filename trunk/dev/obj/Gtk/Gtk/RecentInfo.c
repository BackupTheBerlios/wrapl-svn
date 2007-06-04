#include <Gtk/Gtk/RecentInfo.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 5
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/RecentInfo.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Std/Boolean.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_recent_info_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("Exists", TYP, T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	int result = gtk_recent_info_exists(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetAdded", TYP, T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	time_t result = gtk_recent_info_get_added(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetAge", TYP, T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	int result = gtk_recent_info_get_age(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetApplicationInfo", TYP, T, TYP, Std$String$T, TYP, Std$List$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	char *app_name = Std$String$flatten(Args[1].Val);
	const char * const * app_exec;
	guint* count = 0;
	time_t* time_ = 0;
	int result = gtk_recent_info_get_application_info(self, app_name, app_exec, count, time_);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetApplications", TYP, T, TYP, Std$Object$T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	gsize* length = 0;
	const char * const * result = gtk_recent_info_get_applications(self, length);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetDescription", TYP, T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	const char * result = gtk_recent_info_get_description(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetDisplayName", TYP, T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	const char * result = gtk_recent_info_get_display_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetGroups", TYP, T, TYP, Std$Object$T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	gsize* length = 0;
	const char * const * result = gtk_recent_info_get_groups(self, length);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetIcon", TYP, T, TYP, Std$Integer$SmallT) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	int size = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkPixbuf * result = gtk_recent_info_get_icon(self, size);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetMimeType", TYP, T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	const char * result = gtk_recent_info_get_mime_type(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetModified", TYP, T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	time_t result = gtk_recent_info_get_modified(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetPrivateHint", TYP, T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	int result = gtk_recent_info_get_private_hint(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetShortName", TYP, T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	char * result = gtk_recent_info_get_short_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetUri", TYP, T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	const char * result = gtk_recent_info_get_uri(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetUriDisplay", TYP, T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	char * result = gtk_recent_info_get_uri_display(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetVisited", TYP, T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	time_t result = gtk_recent_info_get_visited(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("HasApplication", TYP, T, TYP, Std$String$T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	char *app_name = Std$String$flatten(Args[1].Val);
	int result = gtk_recent_info_has_application(self, app_name);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("HasGroup", TYP, T, TYP, Std$String$T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	char *group_name = Std$String$flatten(Args[1].Val);
	int result = gtk_recent_info_has_group(self, group_name);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("IsLocal", TYP, T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	int result = gtk_recent_info_is_local(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("LastApplication", TYP, T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	char * result = gtk_recent_info_last_application(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("Match", TYP, T, TYP, Gtk$Gtk$RecentInfo$T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	GtkRecentInfo * info_b= ((Gtk$Gtk$RecentInfo_t *)Args[1].Val)->Value;
	int result = gtk_recent_info_match(self, info_b);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	GtkRecentInfo * result = gtk_recent_info_ref(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GtkRecentInfo * self= ((Gtk$Gtk$RecentInfo_t *)Args[0].Val)->Value;
	gtk_recent_info_unref(self);
	return SUCCESS;
};

