#ifndef Pango_Matrix_H
#define Pango_Matrix_H

#define RIVA_MODULE Gtk$Pango$Matrix
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$Matrix_t {
	Std$Type_t *Type;
	PangoMatrix Value;
} Gtk$Pango$Matrix_t;

extern Std$Type_t Gtk$Pango$Matrix$T[];

#undef RIVA_MODULE

#endif
