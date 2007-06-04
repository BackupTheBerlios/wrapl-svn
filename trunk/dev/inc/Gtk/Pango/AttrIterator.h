#ifndef Pango_AttrIterator_H
#define Pango_AttrIterator_H

#define RIVA_MODULE Gtk$Pango$AttrIterator
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$AttrIterator_t {
	Std$Type_t *Type;
	PangoAttrIterator *Value;
} Gtk$Pango$AttrIterator_t;

extern Std$Type_t Gtk$Pango$AttrIterator$T[];

#undef RIVA_MODULE

#endif
