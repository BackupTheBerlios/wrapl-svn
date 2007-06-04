#ifndef Pango_AttrLanguage_H
#define Pango_AttrLanguage_H

#define RIVA_MODULE Gtk$Pango$AttrLanguage
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$AttrLanguage_t {
	Std$Type_t *Type;
	PangoAttrLanguage *Value;
} Gtk$Pango$AttrLanguage_t;

extern Std$Type_t Gtk$Pango$AttrLanguage$T[];

#undef RIVA_MODULE

#endif
