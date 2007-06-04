#ifndef Gdk_GCValues_H
#define Gdk_GCValues_H

#define RIVA_MODULE Gtk$Gdk$GCValues
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$GCValues_t {
	Std$Type_t *Type;
	GdkGCValues Value;
} Gtk$Gdk$GCValues_t;

extern Std$Type_t Gtk$Gdk$GCValues$T[];

#undef RIVA_MODULE

#endif
