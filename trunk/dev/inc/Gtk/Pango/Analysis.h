#ifndef Pango_Analysis_H
#define Pango_Analysis_H

#define RIVA_MODULE Gtk$Pango$Analysis
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$Analysis_t {
	Std$Type_t *Type;
	PangoAnalysis Value;
} Gtk$Pango$Analysis_t;

extern Std$Type_t Gtk$Pango$Analysis$T[];

#undef RIVA_MODULE

#endif
