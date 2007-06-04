#ifndef Gdk_Font_H
#define Gdk_Font_H

#define RIVA_MODULE Gtk$Gdk$Font
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$Font_t {
	Std$Type_t *Type;
	GdkFont *Value;
} Gtk$Gdk$Font_t;

extern Std$Type_t Gtk$Gdk$Font$T[];

#undef RIVA_MODULE

#endif
