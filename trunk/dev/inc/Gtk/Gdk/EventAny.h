#ifndef Gdk_EventAny_H
#define Gdk_EventAny_H

#define RIVA_MODULE Gtk$Gdk$EventAny
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$EventAny_t {
	Std$Type_t *Type;
	GdkEventAny Value;
} Gtk$Gdk$EventAny_t;

extern Std$Type_t Gtk$Gdk$EventAny$T[];

#undef RIVA_MODULE

#endif
