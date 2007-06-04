#ifndef Pango_Script_H
#define Pango_Script_H

#include <Std.h>
#define RIVA_MODULE Gtk$Pango$Script
#include <Riva-Header.h>

typedef struct Gtk$Pango$Script_t {
	Std$Type_t *Type;
	PangoScript Value;
} Gtk$Pango$Script_t;

extern Std$Type_t Gtk$Pango$Script$T[];

#undef RIVA_MODULE

#endif
