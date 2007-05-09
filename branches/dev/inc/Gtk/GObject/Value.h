#ifndef GTK_GOBJECT_VALUE_H
#define GTK_GOBJECT_VALUE_H

#include <glib-object.h>
#include <Lang.h>

#define RIVA_MODULE Gtk$GObject$Value
#include <Riva-Header.h>

RIVA_CFUN(Lang$Object_t *, to_riva, const GValue *);
RIVA_CFUN(void, to_gtk, Lang$Object_t *, GValue *);

#undef RIVA_MODULE

#endif
