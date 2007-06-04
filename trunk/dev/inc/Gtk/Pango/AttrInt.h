#ifndef Pango_AttrInt_H
#define Pango_AttrInt_H

#define RIVA_MODULE Gtk$Pango$AttrInt
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$AttrInt_t {
	Std$Type_t *Type;
	PangoAttrInt Value;
} Gtk$Pango$AttrInt_t;

extern Std$Type_t Gtk$Pango$AttrInt$T[];

#undef RIVA_MODULE

#endif
