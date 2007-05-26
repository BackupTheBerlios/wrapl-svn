#ifndef GTK_GOBJECT_CLOSURE_H
#define GTK_GOBJECT_CLOSURE_H

#include <glib-object.h>
#include <Std.h>

#define RIVA_MODULE Gtk$GObject$Closure
#include <Riva-Header.h>

typedef struct Gtk$GObject$Closure_t {
	Lang$Type_t *Type;
	GClosure *Handle;
} Gtk$GObject$Closure_t;

extern Lang$Type_t Gtk$GObject$Closure$T[];

RIVA_CFUN(Gtk$GObject$Closure_t *, new, Lang$Object_t *);

#undef RIVA_MODULE

#endif
