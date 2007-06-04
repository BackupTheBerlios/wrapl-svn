#ifndef Pango_Coverage_H
#define Pango_Coverage_H

#define RIVA_MODULE Gtk$Pango$Coverage
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$Coverage_t {
	Std$Type_t *Type;
	PangoCoverage *Value;
} Gtk$Pango$Coverage_t;

extern Std$Type_t Gtk$Pango$Coverage$T[];

#undef RIVA_MODULE

#endif
