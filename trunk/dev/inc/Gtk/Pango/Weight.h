#ifndef Pango_Weight_H
#define Pango_Weight_H

#include <Std.h>
#define RIVA_MODULE Gtk$Pango$Weight
#include <Riva-Header.h>

typedef struct Gtk$Pango$Weight_t {
	Std$Type_t *Type;
	PangoWeight Value;
} Gtk$Pango$Weight_t;

extern Std$Type_t Gtk$Pango$Weight$T[];

#undef RIVA_MODULE

#endif
