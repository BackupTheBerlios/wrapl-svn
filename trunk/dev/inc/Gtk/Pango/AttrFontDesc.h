#ifndef Pango_AttrFontDesc_H
#define Pango_AttrFontDesc_H

#define RIVA_MODULE Gtk$Pango$AttrFontDesc
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$AttrFontDesc_t {
	Std$Type_t *Type;
	PangoAttrFontDesc *Value;
} Gtk$Pango$AttrFontDesc_t;

extern Std$Type_t Gtk$Pango$AttrFontDesc$T[];

#undef RIVA_MODULE

#endif
