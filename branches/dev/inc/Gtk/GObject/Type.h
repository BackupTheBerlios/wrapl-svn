#ifndef GTK_GOBJECT_TYPE_H
#define GTK_GOBJECT_TYPE_H

#include <glib-object.h>
#include <Lang.h>

#define RIVA_MODULE Gtk$GObject$Type
#include <Riva-Header.h>

extern Lang$Type_t Gtk$GObject$Type$T[];

RIVA_CFUN(Lang$Type_t *, gtk_to_riva, GType);

#undef RIVA_MODULE

#endif
