#ifndef Pango_AttrClass_H
#define Pango_AttrClass_H

#define RIVA_MODULE Gtk$Pango$AttrClass
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$AttrClass_t {
	Std$Type_t *Type;
	PangoAttrClass Value;
} Gtk$Pango$AttrClass_t;

extern Std$Type_t Gtk$Pango$AttrClass$T[];

#undef RIVA_MODULE

#endif
