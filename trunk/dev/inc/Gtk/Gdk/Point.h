#ifndef Gdk_Point_H
#define Gdk_Point_H

#define RIVA_MODULE Gtk$Gdk$Point
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$Point_t {
	Std$Type_t *Type;
	GdkPoint Value;
} Gtk$Gdk$Point_t;

extern Std$Type_t Gtk$Gdk$Point$T[];

#undef RIVA_MODULE

#endif
