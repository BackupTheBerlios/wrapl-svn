#ifndef Gdk_PointerHooks_H
#define Gdk_PointerHooks_H

#define RIVA_MODULE Gtk$Gdk$PointerHooks
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$PointerHooks_t {
	Std$Type_t *Type;
	GdkPointerHooks Value;
} Gtk$Gdk$PointerHooks_t;

extern Std$Type_t Gtk$Gdk$PointerHooks$T[];

#undef RIVA_MODULE

#endif
