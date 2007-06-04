#ifndef Gdk_Atom_H
#define Gdk_Atom_H

#define RIVA_MODULE Gtk$Gdk$Atom
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$Atom_t {
	Std$Type_t *Type;
	GdkAtom *Value;
} Gtk$Gdk$Atom_t;

extern Std$Type_t Gtk$Gdk$Atom$T[];

#undef RIVA_MODULE

#endif
