#ifndef Pango_Direction_H
#define Pango_Direction_H

#include <Std.h>
#define RIVA_MODULE Gtk$Pango$Direction
#include <Riva-Header.h>

typedef struct Gtk$Pango$Direction_t {
	Std$Type_t *Type;
	PangoDirection Value;
} Gtk$Pango$Direction_t;

extern Std$Type_t Gtk$Pango$Direction$T[];

#undef RIVA_MODULE

#endif
