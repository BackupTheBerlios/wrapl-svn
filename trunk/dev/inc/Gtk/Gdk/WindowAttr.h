#ifndef Gdk_WindowAttr_H
#define Gdk_WindowAttr_H

#define RIVA_MODULE Gtk$Gdk$WindowAttr
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$WindowAttr_t {
	Std$Type_t *Type;
	GdkWindowAttr Value;
} Gtk$Gdk$WindowAttr_t;

extern Std$Type_t Gtk$Gdk$WindowAttr$T[];

#undef RIVA_MODULE

#endif
