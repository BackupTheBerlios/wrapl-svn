#ifndef Pango_Language_H
#define Pango_Language_H

#define RIVA_MODULE Gtk$Pango$Language
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$Language_t {
	Std$Type_t *Type;
	PangoLanguage *Value;
} Gtk$Pango$Language_t;

extern Std$Type_t Gtk$Pango$Language$T[];

#undef RIVA_MODULE

#endif
