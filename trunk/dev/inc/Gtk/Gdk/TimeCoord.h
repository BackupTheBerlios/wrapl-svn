#ifndef Gdk_TimeCoord_H
#define Gdk_TimeCoord_H

#define RIVA_MODULE Gtk$Gdk$TimeCoord
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$TimeCoord_t {
	Std$Type_t *Type;
	GdkTimeCoord Value;
} Gtk$Gdk$TimeCoord_t;

extern Std$Type_t Gtk$Gdk$TimeCoord$T[];

#undef RIVA_MODULE

#endif
