#ifndef Gtk_TreeIter_H
#define Gtk_TreeIter_H

#define RIVA_MODULE Gtk$Gtk$TreeIter
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$TreeIter_t {
	Std$Type_t *Type;
	GtkTreeIter Value;
} Gtk$Gtk$TreeIter_t;

extern Std$Type_t Gtk$Gtk$TreeIter$T[];

#undef RIVA_MODULE

#endif
