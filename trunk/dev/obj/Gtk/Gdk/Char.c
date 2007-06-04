#include <Gtk/Gdk/Char.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 2
#include <Gtk/Gdk/Font.h>
#include <Gtk/GObject/Object.h>
/***********************************/
GLOBAL_FUNCTION(Height, 2) {
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	char character = ((char *)((Std$String_t *)Args[1].Val)->Blocks[0].Chars.Value)[0];
	int result = gdk_char_height(font, character);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Measure, 2) {
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	char character = ((char *)((Std$String_t *)Args[1].Val)->Blocks[0].Chars.Value)[0];
	int result = gdk_char_measure(font, character);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Width, 2) {
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	char character = ((char *)((Std$String_t *)Args[1].Val)->Blocks[0].Chars.Value)[0];
	int result = gdk_char_width(font, character);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(WidthWc, 2) {
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	GdkWChar character = 0;
	int result = gdk_char_width_wc(font, character);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

