#ifndef Pango_AttrFloat_H
#define Pango_AttrFloat_H

#define RIVA_MODULE Gtk$Pango$AttrFloat
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$AttrFloat_t {
	Std$Type_t *Type;
	PangoAttrFloat Value;
} Gtk$Pango$AttrFloat_t;

extern Std$Type_t Gtk$Pango$AttrFloat$T[];

#undef RIVA_MODULE

#endif
