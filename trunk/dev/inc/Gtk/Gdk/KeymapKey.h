#ifndef Gdk_KeymapKey_H
#define Gdk_KeymapKey_H

#define RIVA_MODULE Gtk$Gdk$KeymapKey
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$KeymapKey_t {
	Std$Type_t *Type;
	GdkKeymapKey Value;
} Gtk$Gdk$KeymapKey_t;

extern Std$Type_t Gtk$Gdk$KeymapKey$T[];

#undef RIVA_MODULE

#endif
