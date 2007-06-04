#ifndef Pango_Style_H
#define Pango_Style_H

#include <Std.h>
#define RIVA_MODULE Gtk$Pango$Style
#include <Riva-Header.h>

typedef struct Gtk$Pango$Style_t {
	Std$Type_t *Type;
	PangoStyle Value;
} Gtk$Pango$Style_t;

extern Std$Type_t Gtk$Pango$Style$T[];

#undef RIVA_MODULE

#endif
