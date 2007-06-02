#ifndef GTK_GOBJECT_TYPE_H
#define GTK_GOBJECT_TYPE_H

#include <glib-object.h>
#include <Std.h>

#define RIVA_MODULE Gtk$GObject$Type
#include <Riva-Header.h>

extern Std$Type_t Gtk$GObject$Type$T[];

RIVA_CFUN(Std$Type_t *, to_riva, GType);

#undef RIVA_MODULE

#endif
