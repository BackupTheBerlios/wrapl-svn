#ifndef Pango_Variant_H
#define Pango_Variant_H

#include <Std.h>
#define RIVA_MODULE Gtk$Pango$Variant
#include <Riva-Header.h>

typedef struct Gtk$Pango$Variant_t {
	Std$Type_t *Type;
	PangoVariant Value;
} Gtk$Pango$Variant_t;

extern Std$Type_t Gtk$Pango$Variant$T[];

#undef RIVA_MODULE

#endif
