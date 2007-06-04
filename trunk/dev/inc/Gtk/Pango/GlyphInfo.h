#ifndef Pango_GlyphInfo_H
#define Pango_GlyphInfo_H

#define RIVA_MODULE Gtk$Pango$GlyphInfo
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$GlyphInfo_t {
	Std$Type_t *Type;
	PangoGlyphInfo Value;
} Gtk$Pango$GlyphInfo_t;

extern Std$Type_t Gtk$Pango$GlyphInfo$T[];

#undef RIVA_MODULE

#endif
