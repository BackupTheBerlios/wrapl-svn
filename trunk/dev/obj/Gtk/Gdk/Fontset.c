#include <Gtk/Gdk/Fontset.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gdk/Font.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/GObject/Object.h>
/***********************************/
GLOBAL_FUNCTION(Load, 1) {
	char *fontset_name = Std$String$flatten(Args[0].Val);
	GdkFont * result = gdk_fontset_load(fontset_name);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(LoadForDisplay, 2) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *fontset_name = Std$String$flatten(Args[1].Val);
	GdkFont * result = gdk_fontset_load_for_display(display, fontset_name);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

