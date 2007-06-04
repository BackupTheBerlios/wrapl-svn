#ifndef Gdk_EventProperty_H
#define Gdk_EventProperty_H

#define RIVA_MODULE Gtk$Gdk$EventProperty
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$EventProperty_t {
	Std$Type_t *Type;
	GdkEventProperty Value;
} Gtk$Gdk$EventProperty_t;

extern Std$Type_t Gtk$Gdk$EventProperty$T[];

#undef RIVA_MODULE

#endif
