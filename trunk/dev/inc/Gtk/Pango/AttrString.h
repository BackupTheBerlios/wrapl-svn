#ifndef Pango_AttrString_H
#define Pango_AttrString_H

#define RIVA_MODULE Gtk$Pango$AttrString
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$AttrString_t {
	Std$Type_t *Type;
	PangoAttrString Value;
} Gtk$Pango$AttrString_t;

extern Std$Type_t Gtk$Pango$AttrString$T[];

#undef RIVA_MODULE

#endif
