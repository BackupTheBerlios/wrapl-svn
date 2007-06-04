#ifndef Gdk_EventKey_H
#define Gdk_EventKey_H

#define RIVA_MODULE Gtk$Gdk$EventKey
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$EventKey_t {
	Std$Type_t *Type;
	GdkEventKey Value;
} Gtk$Gdk$EventKey_t;

extern Std$Type_t Gtk$Gdk$EventKey$T[];

#undef RIVA_MODULE

#endif
