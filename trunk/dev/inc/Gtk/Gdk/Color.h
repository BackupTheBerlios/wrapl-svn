#ifndef Gdk_Color_H
#define Gdk_Color_H

#define RIVA_MODULE Gtk$Gdk$Color
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$Color_t {
	Std$Type_t *Type;
	GdkColor Value;
} Gtk$Gdk$Color_t;

extern Std$Type_t Gtk$Gdk$Color$T[];

#undef RIVA_MODULE

#endif
