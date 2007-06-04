#ifndef Pango_Attribute_H
#define Pango_Attribute_H

#define RIVA_MODULE Gtk$Pango$Attribute
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$Attribute_t {
	Std$Type_t *Type;
	PangoAttribute *Value;
} Gtk$Pango$Attribute_t;

extern Std$Type_t Gtk$Pango$Attribute$T[];

#undef RIVA_MODULE

#endif
