#ifndef Pango_AttrColor_H
#define Pango_AttrColor_H

#define RIVA_MODULE Gtk$Pango$AttrColor
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$AttrColor_t {
	Std$Type_t *Type;
	PangoAttrColor Value;
} Gtk$Pango$AttrColor_t;

extern Std$Type_t Gtk$Pango$AttrColor$T[];

#undef RIVA_MODULE

#endif
