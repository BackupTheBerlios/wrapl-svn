#ifndef Gdk_Region_H
#define Gdk_Region_H

#define RIVA_MODULE Gtk$Gdk$Region
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$Region_t {
	Std$Type_t *Type;
	GdkRegion *Value;
} Gtk$Gdk$Region_t;

extern Std$Type_t Gtk$Gdk$Region$T[];

#undef RIVA_MODULE

#endif
