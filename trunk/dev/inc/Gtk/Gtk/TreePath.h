#ifndef Gtk_TreePath_H
#define Gtk_TreePath_H

#define RIVA_MODULE Gtk$Gtk$TreePath
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$TreePath_t {
	Std$Type_t *Type;
	GtkTreePath *Value;
} Gtk$Gtk$TreePath_t;

extern Std$Type_t Gtk$Gtk$TreePath$T[];

#undef RIVA_MODULE

#endif
