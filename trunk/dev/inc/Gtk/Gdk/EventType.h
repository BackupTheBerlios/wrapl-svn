#ifndef Gdk_EventType_H
#define Gdk_EventType_H

#include <Std.h>
#define RIVA_MODULE Gtk$Gdk$EventType
#include <Riva-Header.h>

typedef struct Gtk$Gdk$EventType_t {
	Std$Type_t *Type;
	GdkEventType Value;
} Gtk$Gdk$EventType_t;

extern Std$Type_t Gtk$Gdk$EventType$T[];

#undef RIVA_MODULE

#endif
