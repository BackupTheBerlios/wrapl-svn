#ifndef Gdk_EventMotion_H
#define Gdk_EventMotion_H

#define RIVA_MODULE Gtk$Gdk$EventMotion
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$EventMotion_t {
	Std$Type_t *Type;
	GdkEventMotion Value;
} Gtk$Gdk$EventMotion_t;

extern Std$Type_t Gtk$Gdk$EventMotion$T[];

#undef RIVA_MODULE

#endif
