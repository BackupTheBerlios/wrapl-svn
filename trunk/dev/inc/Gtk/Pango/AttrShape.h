#ifndef Pango_AttrShape_H
#define Pango_AttrShape_H

#define RIVA_MODULE Gtk$Pango$AttrShape
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$AttrShape_t {
	Std$Type_t *Type;
	PangoAttrShape *Value;
} Gtk$Pango$AttrShape_t;

extern Std$Type_t Gtk$Pango$AttrShape$T[];

#undef RIVA_MODULE

#endif
