#ifndef GTK_GOBJECT_OBJECT_H
#define GTK_GOBJECT_OBJECT_H

#include <glib-object.h>
#include <Std.h>

#define RIVA_MODULE Gtk$GObject$Object
#include <Riva-Header.h>

typedef struct GtkGOobject$Object_t {
	Std$Type_t *Type;
	GObject *Handle;
} Gtk$GObject$Object_t;

extern Std$Type_t Gtk$GObject$Object$T[];

RIVA_CFUN(Gtk$GObject$Object_t *, new, GObject *, Std$Type_t *);
RIVA_CFUN(Gtk$GObject$Object_t *, to_riva, GObject *);

#undef RIVA_MODULE

#endif
