#ifndef Pango_LogAttr_H
#define Pango_LogAttr_H

#define RIVA_MODULE Gtk$Pango$LogAttr
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$LogAttr_t {
	Std$Type_t *Type;
	PangoLogAttr Value;
} Gtk$Pango$LogAttr_t;

extern Std$Type_t Gtk$Pango$LogAttr$T[];

#undef RIVA_MODULE

#endif
