#include <Gtk/Gdk/Text.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Gtk/Gdk/Font.h>
#include <Gtk/Gdk/Display.h>
#include <Gtk/GObject/Object.h>
/***********************************/
GLOBAL_FUNCTION(Extents, 8) {
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	char *text = Std$String$flatten(Args[1].Val);
	int text_length = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gint* lbearing = 0;
	gint* rbearing = 0;
	gint* width = 0;
	gint* ascent = 0;
	gint* descent = 0;
	gdk_text_extents(font, text, text_length, lbearing, rbearing, width, ascent, descent);
	return SUCCESS;
};

GLOBAL_FUNCTION(ExtentsWc, 8) {
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	const GdkWChar* text = 0;
	int text_length = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gint* lbearing = 0;
	gint* rbearing = 0;
	gint* width = 0;
	gint* ascent = 0;
	gint* descent = 0;
	gdk_text_extents_wc(font, text, text_length, lbearing, rbearing, width, ascent, descent);
	return SUCCESS;
};

GLOBAL_FUNCTION(Height, 3) {
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	char *text = Std$String$flatten(Args[1].Val);
	int text_length = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gdk_text_height(font, text, text_length);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Measure, 3) {
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	char *text = Std$String$flatten(Args[1].Val);
	int text_length = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gdk_text_measure(font, text, text_length);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(PropertyToTextList, 5) {
	GdkAtom encoding = 0;
	int format = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *text = Std$String$flatten(Args[2].Val);
	int length = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gchar*** list = 0;
	int result = gdk_text_property_to_text_list(encoding, format, text, length, list);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(PropertyToTextListForDisplay, 6) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom encoding = 0;
	int format = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char *text = Std$String$flatten(Args[3].Val);
	int length = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gchar*** list = 0;
	int result = gdk_text_property_to_text_list_for_display(display, encoding, format, text, length, list);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(PropertyToUtf8List, 5) {
	GdkAtom encoding = 0;
	int format = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *text = Std$String$flatten(Args[2].Val);
	int length = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gchar*** list = 0;
	int result = gdk_text_property_to_utf8_list(encoding, format, text, length, list);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(PropertyToUtf8ListForDisplay, 6) {
	GdkDisplay * display = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkAtom encoding = 0;
	int format = ((Std$Integer_smallt *)Args[2].Val)->Value;
	char *text = Std$String$flatten(Args[3].Val);
	int length = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gchar*** list = 0;
	int result = gdk_text_property_to_utf8_list_for_display(display, encoding, format, text, length, list);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Width, 3) {
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	char *text = Std$String$flatten(Args[1].Val);
	int text_length = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gdk_text_width(font, text, text_length);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(WidthWc, 3) {
	GdkFont * font= ((Gtk$Gdk$Font_t *)Args[0].Val)->Value;
	const GdkWChar* text = 0;
	int text_length = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int result = gdk_text_width_wc(font, text, text_length);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

