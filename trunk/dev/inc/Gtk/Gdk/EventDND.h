#ifndef Gdk_EventDND_H
#define Gdk_EventDND_H

#define RIVA_MODULE Gtk$Gdk$EventDND
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$EventDND_t {
	Std$Type_t *Type;
	GdkEventDND Value;
} Gtk$Gdk$EventDND_t;

extern Std$Type_t Gtk$Gdk$EventDND$T[];

#undef RIVA_MODULE

#endif
