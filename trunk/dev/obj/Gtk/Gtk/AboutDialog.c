#include <Gtk/Gtk/AboutDialog.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 6
#include <Std/Boolean.h>
#include <Gtk/Gtk/AboutDialog.h>
#include <Gtk/Gtk/AboutDialogActivateLinkFunc.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Pixbuf.h>
/***********************************/
TYPE(T, Gtk$Gtk$Dialog$T, Gtk$Gtk$Window$T, Gtk$Gtk$Bin$T, Gtk$Gtk$Container$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 0) {
	GtkAboutDialog * result = gtk_about_dialog_new();
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_about_dialog_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetEmailHook, 3) {
	GtkAboutDialogActivateLinkFunc func = Gtk$Gtk$AboutDialogActivateLinkFunc$new(Args[0].Val);
	void *data = ((Std$Address_t *)Args[1].Val)->Value;
	GDestroyNotify destroy = 0;
	GtkAboutDialogActivateLinkFunc result = gtk_about_dialog_set_email_hook(func, data, destroy);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(SetUrlHook, 3) {
	GtkAboutDialogActivateLinkFunc func = Gtk$Gtk$AboutDialogActivateLinkFunc$new(Args[0].Val);
	void *data = ((Std$Address_t *)Args[1].Val)->Value;
	GDestroyNotify destroy = 0;
	GtkAboutDialogActivateLinkFunc result = gtk_about_dialog_set_url_hook(func, data, destroy);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetArtists", TYP, T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * result = gtk_about_dialog_get_artists(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetAuthors", TYP, T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * result = gtk_about_dialog_get_authors(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetComments", TYP, T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_about_dialog_get_comments(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetCopyright", TYP, T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_about_dialog_get_copyright(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetDocumenters", TYP, T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * result = gtk_about_dialog_get_documenters(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("GetLicense", TYP, T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_about_dialog_get_license(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetLogo", TYP, T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * result = gtk_about_dialog_get_logo(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetLogoIconName", TYP, T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_about_dialog_get_logo_icon_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetName", TYP, T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_about_dialog_get_name(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetTranslatorCredits", TYP, T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_about_dialog_get_translator_credits(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetVersion", TYP, T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_about_dialog_get_version(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetWebsite", TYP, T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_about_dialog_get_website(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetWebsiteLabel", TYP, T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * result = gtk_about_dialog_get_website_label(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetWrapLicense", TYP, T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_about_dialog_get_wrap_license(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SetArtists", TYP, T, TYP, Std$List$T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * artists;
	gtk_about_dialog_set_artists(self, artists);
	return SUCCESS;
};

METHOD("SetAuthors", TYP, T, TYP, Std$List$T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * authors;
	gtk_about_dialog_set_authors(self, authors);
	return SUCCESS;
};

METHOD("SetComments", TYP, T, TYP, Std$String$T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *comments = Std$String$flatten(Args[1].Val);
	gtk_about_dialog_set_comments(self, comments);
	return SUCCESS;
};

METHOD("SetCopyright", TYP, T, TYP, Std$String$T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *copyright = Std$String$flatten(Args[1].Val);
	gtk_about_dialog_set_copyright(self, copyright);
	return SUCCESS;
};

METHOD("SetDocumenters", TYP, T, TYP, Std$List$T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * documenters;
	gtk_about_dialog_set_documenters(self, documenters);
	return SUCCESS;
};

METHOD("SetLicense", TYP, T, TYP, Std$String$T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *license = Std$String$flatten(Args[1].Val);
	gtk_about_dialog_set_license(self, license);
	return SUCCESS;
};

METHOD("SetLogo", TYP, T, TYP, Gtk$Gdk$Pixbuf$T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * logo = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_about_dialog_set_logo(self, logo);
	return SUCCESS;
};

METHOD("SetLogoIconName", TYP, T, TYP, Std$String$T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *icon_name = Std$String$flatten(Args[1].Val);
	gtk_about_dialog_set_logo_icon_name(self, icon_name);
	return SUCCESS;
};

METHOD("SetName", TYP, T, TYP, Std$String$T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	gtk_about_dialog_set_name(self, name);
	return SUCCESS;
};

METHOD("SetTranslatorCredits", TYP, T, TYP, Std$String$T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *translator_credits = Std$String$flatten(Args[1].Val);
	gtk_about_dialog_set_translator_credits(self, translator_credits);
	return SUCCESS;
};

METHOD("SetVersion", TYP, T, TYP, Std$String$T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *version = Std$String$flatten(Args[1].Val);
	gtk_about_dialog_set_version(self, version);
	return SUCCESS;
};

METHOD("SetWebsite", TYP, T, TYP, Std$String$T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *website = Std$String$flatten(Args[1].Val);
	gtk_about_dialog_set_website(self, website);
	return SUCCESS;
};

METHOD("SetWebsiteLabel", TYP, T, TYP, Std$String$T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *website_label = Std$String$flatten(Args[1].Val);
	gtk_about_dialog_set_website_label(self, website_label);
	return SUCCESS;
};

METHOD("SetWrapLicense", TYP, T, TYP, Std$Symbol$T) {
	GtkAboutDialog * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int wrap_license = Args[1].Val == $true;
	gtk_about_dialog_set_wrap_license(self, wrap_license);
	return SUCCESS;
};

