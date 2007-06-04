#include <Gtk/Gdk/Global.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 9
#include <Gtk/Gdk/PointerHooks.h>
#include <Std/Boolean.h>
#include <Gtk/Gdk/Atom.h>
#include <Gtk/Gdk/Font.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/FilterFunc.h>
#include <Gtk/Gdk/Window.h>
#include <Gtk/GObject/Value.h>
/***********************************/
GLOBAL_FUNCTION(AddClientMessageFilter, 3) {
	GdkAtom message_type = 0;
	GdkFilterFunc func = Gtk$Gdk$FilterFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	gdk_add_client_message_filter(message_type, func, data);
	return SUCCESS;
};

GLOBAL_FUNCTION(AddOptionEntriesLibgtkOnly, 1) {
	GOptionGroup* group = 0;
	gdk_add_option_entries_libgtk_only(group);
	return SUCCESS;
};

GLOBAL_FUNCTION(DevicesList, 0) {
	GList* result = gdk_devices_list();
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(EventsPending, 0) {
	int result = gdk_events_pending();
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(FreeCompoundText, 1) {
	char *ctext = Std$String$flatten(Args[0].Val);
	gdk_free_compound_text(ctext);
	return SUCCESS;
};

GLOBAL_FUNCTION(FreeTextList, 1) {
	const char * const * list;
	gdk_free_text_list(list);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetDefaultRootWindow, 0) {
	GdkWindow * result = gdk_get_default_root_window();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetDisplay, 0) {
	char * result = gdk_get_display();
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetDisplayArgName, 0) {
	const char * result = gdk_get_display_arg_name();
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetProgramClass, 0) {
	const char * result = gdk_get_program_class();
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetShowEvents, 0) {
	int result = gdk_get_show_events();
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetUseXshm, 0) {
	int result = gdk_get_use_xshm();
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(InitCheck, 2) {
	gint* argc = 0;
	gchar*** argv = 0;
	int result = gdk_init_check(argc, argv);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ListVisuals, 0) {
	GList * result = gdk_list_visuals();
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

GLOBAL_FUNCTION(NetWmSupports, 1) {
	GdkAtom property = 0;
	int result = gdk_net_wm_supports(property);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(NotifyStartupComplete, 0) {
	gdk_notify_startup_complete();
	return SUCCESS;
};

GLOBAL_FUNCTION(ParseArgs, 2) {
	gint* argc = 0;
	gchar*** argv = 0;
	gdk_parse_args(argc, argv);
	return SUCCESS;
};

GLOBAL_FUNCTION(PreParseLibgtkOnly, 0) {
	gdk_pre_parse_libgtk_only();
	return SUCCESS;
};

GLOBAL_FUNCTION(SetDoubleClickTime, 1) {
	int msec = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gdk_set_double_click_time(msec);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetLocale, 0) {
	char * result = gdk_set_locale();
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetPointerHooks, 1) {
	GdkPointerHooks * new_hooks= &((Gtk$Gdk$PointerHooks_t *)Args[0].Val)->Value;
	GdkPointerHooks * result = gdk_set_pointer_hooks(new_hooks);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(SetProgramClass, 1) {
	char *program_class = Std$String$flatten(Args[0].Val);
	gdk_set_program_class(program_class);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetShowEvents, 1) {
	int show_events = Args[0].Val == $true;
	gdk_set_show_events(show_events);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetSmClientId, 1) {
	char *sm_client_id = Std$String$flatten(Args[0].Val);
	gdk_set_sm_client_id(sm_client_id);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetUseXshm, 1) {
	int use_xshm = Args[0].Val == $true;
	gdk_set_use_xshm(use_xshm);
	return SUCCESS;
};

GLOBAL_FUNCTION(SettingGet, 2) {
	char *name = Std$String$flatten(Args[0].Val);
	GValue value[1];
	Gtk$GObject$Value$to_gtk(Args[1].Val, value);
	int result = gdk_setting_get(name, value);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(StringExtents, 7) {
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	char *string = Std$String$flatten(Args[1].Val);
	gint* lbearing = 0;
	gint* rbearing = 0;
	gint* width = 0;
	gint* ascent = 0;
	gint* descent = 0;
	gdk_string_extents(font, string, lbearing, rbearing, width, ascent, descent);
	return SUCCESS;
};

GLOBAL_FUNCTION(StringHeight, 2) {
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	char *string = Std$String$flatten(Args[1].Val);
	int result = gdk_string_height(font, string);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(StringMeasure, 2) {
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	char *string = Std$String$flatten(Args[1].Val);
	int result = gdk_string_measure(font, string);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(StringToCompoundText, 5) {
	char *str = Std$String$flatten(Args[0].Val);
	GdkAtom * encoding= ((Gtk$Gdk$Atom_t *)Args[1].Val)->Value;
	gint* format = 0;
	guchar** ctext = 0;
	gint* length = 0;
	int result = gdk_string_to_compound_text(str, encoding, format, ctext, length);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(StringToCompoundTextForDisplay, 6) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *str = Std$String$flatten(Args[1].Val);
	GdkAtom * encoding= ((Gtk$Gdk$Atom_t *)Args[2].Val)->Value;
	gint* format = 0;
	guchar** ctext = 0;
	gint* length = 0;
	int result = gdk_string_to_compound_text_for_display(display, str, encoding, format, ctext, length);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(StringWidth, 2) {
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	char *string = Std$String$flatten(Args[1].Val);
	int result = gdk_string_width(font, string);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(UnicodeToKeyval, 1) {
	int wc = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int result = gdk_unicode_to_keyval(wc);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

