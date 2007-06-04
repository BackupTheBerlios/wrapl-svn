#ifndef Pango_TabArray_H
#define Pango_TabArray_H

#define RIVA_MODULE Gtk$Pango$TabArray
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$TabArray_t {
	Std$Type_t *Type;
	PangoTabArray *Value;
} Gtk$Pango$TabArray_t;

extern Std$Type_t Gtk$Pango$TabArray$T[];

#undef RIVA_MODULE

#endif
