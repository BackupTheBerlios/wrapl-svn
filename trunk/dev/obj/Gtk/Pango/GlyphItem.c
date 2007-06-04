#include <Gtk/Pango/GlyphItem.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/Pango/LogAttr.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Pango/AttrList.h>
#include <Gtk/Pango/GlyphItem.h>
/***********************************/
TYPE(T);

METHOD("ApplyAttrs", TYP, T, TYP, Std$String$T, TYP, Gtk$Pango$AttrList$T) {
	PangoGlyphItem * self= &((Gtk$Pango$GlyphItem_t *)Args[0].Val)->Value;
	char *text = Std$String$flatten(Args[1].Val);
	PangoAttrList * list= ((Gtk$Pango$AttrList_t *)Args[2].Val)->Value;
	GSList* result = pango_glyph_item_apply_attrs(self, text, list);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	PangoGlyphItem * self= &((Gtk$Pango$GlyphItem_t *)Args[0].Val)->Value;
	pango_glyph_item_free(self);
	return SUCCESS;
};

METHOD("LetterSpace", TYP, T, TYP, Std$String$T, TYP, Gtk$Pango$LogAttr$T, TYP, Std$Integer$SmallT) {
	PangoGlyphItem * self= &((Gtk$Pango$GlyphItem_t *)Args[0].Val)->Value;
	char *text = Std$String$flatten(Args[1].Val);
	PangoLogAttr * log_attrs= &((Gtk$Pango$LogAttr_t *)Args[2].Val)->Value;
	int letter_spacing = ((Std$Integer_smallt *)Args[3].Val)->Value;
	pango_glyph_item_letter_space(self, text, log_attrs, letter_spacing);
	return SUCCESS;
};

METHOD("Split", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	PangoGlyphItem * self= &((Gtk$Pango$GlyphItem_t *)Args[0].Val)->Value;
	char *text = Std$String$flatten(Args[1].Val);
	int split_index = ((Std$Integer_smallt *)Args[2].Val)->Value;
	PangoGlyphItem * result = pango_glyph_item_split(self, text, split_index);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

