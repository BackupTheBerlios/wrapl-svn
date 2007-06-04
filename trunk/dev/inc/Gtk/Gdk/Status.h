#ifndef Gdk_Status_H
#define Gdk_Status_H

#include <Std.h>
#define RIVA_MODULE Gtk$Gdk$Status
#include <Riva-Header.h>

typedef struct Gtk$Gdk$Status_t {
	Std$Type_t *Type;
	GdkStatus Value;
} Gtk$Gdk$Status_t;

extern Std$Type_t Gtk$Gdk$Status$T[];

#undef RIVA_MODULE

#endif
