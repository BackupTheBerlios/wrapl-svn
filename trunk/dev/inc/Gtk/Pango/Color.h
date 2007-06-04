#ifndef Pango_Color_H
#define Pango_Color_H

#define RIVA_MODULE Gtk$Pango$Color
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$Color_t {
	Std$Type_t *Type;
	PangoColor Value;
} Gtk$Pango$Color_t;

extern Std$Type_t Gtk$Pango$Color$T[];

#undef RIVA_MODULE

#endif
