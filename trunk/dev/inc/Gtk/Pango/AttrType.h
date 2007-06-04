#ifndef Pango_AttrType_H
#define Pango_AttrType_H

#include <Std.h>
#define RIVA_MODULE Gtk$Pango$AttrType
#include <Riva-Header.h>

typedef struct Gtk$Pango$AttrType_t {
	Std$Type_t *Type;
	PangoAttrType Value;
} Gtk$Pango$AttrType_t;

extern Std$Type_t Gtk$Pango$AttrType$T[];

#undef RIVA_MODULE

#endif
