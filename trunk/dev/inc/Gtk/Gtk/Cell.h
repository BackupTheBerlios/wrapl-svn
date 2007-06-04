#ifndef Gtk_Cell_H
#define Gtk_Cell_H

#define RIVA_MODULE Gtk$Gtk$Cell
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$Cell_t {
	Std$Type_t *Type;
	GtkCell Value;
} Gtk$Gtk$Cell_t;

extern Std$Type_t Gtk$Gtk$Cell$T[];

#undef RIVA_MODULE

#endif
