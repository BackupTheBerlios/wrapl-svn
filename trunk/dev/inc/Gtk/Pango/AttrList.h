#ifndef Pango_AttrList_H
#define Pango_AttrList_H

#define RIVA_MODULE Gtk$Pango$AttrList
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$AttrList_t {
	Std$Type_t *Type;
	PangoAttrList *Value;
} Gtk$Pango$AttrList_t;

extern Std$Type_t Gtk$Pango$AttrList$T[];

#undef RIVA_MODULE

#endif
