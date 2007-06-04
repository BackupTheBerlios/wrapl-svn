#ifndef Pango_FontMetrics_H
#define Pango_FontMetrics_H

#define RIVA_MODULE Gtk$Pango$FontMetrics
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$FontMetrics_t {
	Std$Type_t *Type;
	PangoFontMetrics *Value;
} Gtk$Pango$FontMetrics_t;

extern Std$Type_t Gtk$Pango$FontMetrics$T[];

#undef RIVA_MODULE

#endif
