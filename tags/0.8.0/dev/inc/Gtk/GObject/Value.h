#ifndef GTK_GOBJECT_VALUE_H
#define GTK_GOBJECT_VALUE_H

#include <glib-object.h>
#include <Std.h>

#define RIVA_MODULE Gtk$GObject$Value
#include <Riva-Header.h>

typedef struct Gtk$GObject$Value_t {
	Std$Type_t *Type;
	GValue *Value;
} Gtk$GObject$Value_t;

extern Std$Type_t Gtk$GObject$Value$T[];

RIVA_CFUN(Std$Object_t *, to_riva, const GValue *);
RIVA_CFUN(void, to_gtk, Std$Object_t *, GValue *);

#undef RIVA_MODULE

#endif
