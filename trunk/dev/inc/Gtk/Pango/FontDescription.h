#ifndef Pango_FontDescription_H
#define Pango_FontDescription_H

#define RIVA_MODULE Gtk$Pango$FontDescription
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$FontDescription_t {
	Std$Type_t *Type;
	PangoFontDescription *Value;
} Gtk$Pango$FontDescription_t;

extern Std$Type_t Gtk$Pango$FontDescription$T[];

#undef RIVA_MODULE

#endif
