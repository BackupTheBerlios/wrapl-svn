#ifndef Pango_GlyphString_H
#define Pango_GlyphString_H

#define RIVA_MODULE Gtk$Pango$GlyphString
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$GlyphString_t {
	Std$Type_t *Type;
	PangoGlyphString *Value;
} Gtk$Pango$GlyphString_t;

extern Std$Type_t Gtk$Pango$GlyphString$T[];

#undef RIVA_MODULE

#endif
