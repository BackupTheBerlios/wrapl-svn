#include <Gtk/Gdk/Keymap.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 7
#include <Std/Boolean.h>
#include <Gtk/Gdk/KeymapKey.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/Pango/Direction.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/Keymap.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(GetDefault, 0) {
	GdkKeymap * result = gdk_keymap_get_default();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetForDisplay, 1) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkKeymap * result = gdk_keymap_get_for_display(display);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_keymap_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("GetDirection", TYP, T) {
	GdkKeymap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	PangoDirection result = gdk_keymap_get_direction(self);
	Gtk$Pango$Direction_t *_result = new(Gtk$Pango$Direction_t);
	_result->Type = Gtk$Pango$Direction$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetEntriesForKeycode", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkKeymap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int hardware_keycode = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkKeymapKey** keys = 0;
	guint** keyvals = 0;
	gint* n_entries = 0;
	int result = gdk_keymap_get_entries_for_keycode(self, hardware_keycode, keys, keyvals, n_entries);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetEntriesForKeyval", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkKeymap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int keyval = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkKeymapKey** keys = 0;
	gint* n_keys = 0;
	int result = gdk_keymap_get_entries_for_keyval(self, keyval, keys, n_keys);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("LookupKey", TYP, T, TYP, Gtk$Gdk$KeymapKey$T) {
	GdkKeymap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkKeymapKey * key= &((Gtk$Gdk$KeymapKey_t *)Args[1].Val)->Value;
	int result = gdk_keymap_lookup_key(self, key);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("TranslateKeyboardState", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkKeymap * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int hardware_keycode = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int state = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int group = ((Std$Integer_smallt *)Args[3].Val)->Value;
	guint* keyval = 0;
	gint* effective_group = 0;
	gint* level = 0;
	GdkModifierType* consumed_modifiers = 0;
	int result = gdk_keymap_translate_keyboard_state(self, hardware_keycode, state, group, keyval, effective_group, level, consumed_modifiers);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

