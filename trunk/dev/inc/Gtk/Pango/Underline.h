#ifndef Pango_Underline_H
#define Pango_Underline_H

#include <Std.h>
#define RIVA_MODULE Gtk$Pango$Underline
#include <Riva-Header.h>

typedef struct Gtk$Pango$Underline_t {
	Std$Type_t *Type;
	PangoUnderline Value;
} Gtk$Pango$Underline_t;

extern Std$Type_t Gtk$Pango$Underline$T[];

#undef RIVA_MODULE

#endif
