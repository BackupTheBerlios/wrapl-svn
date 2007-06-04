#ifndef Pango_AttrSize_H
#define Pango_AttrSize_H

#define RIVA_MODULE Gtk$Pango$AttrSize
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$AttrSize_t {
	Std$Type_t *Type;
	PangoAttrSize *Value;
} Gtk$Pango$AttrSize_t;

extern Std$Type_t Gtk$Pango$AttrSize$T[];

#undef RIVA_MODULE

#endif
