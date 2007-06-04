#ifndef Pango_Rectangle_H
#define Pango_Rectangle_H

#define RIVA_MODULE Gtk$Pango$Rectangle
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$Rectangle_t {
	Std$Type_t *Type;
	PangoRectangle Value;
} Gtk$Pango$Rectangle_t;

extern Std$Type_t Gtk$Pango$Rectangle$T[];

#undef RIVA_MODULE

#endif
