#ifndef Gtk_TargetEntry_H
#define Gtk_TargetEntry_H

#define RIVA_MODULE Gtk$Gtk$TargetEntry
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$TargetEntry_t {
	Std$Type_t *Type;
	GtkTargetEntry Value;
} Gtk$Gtk$TargetEntry_t;

extern Std$Type_t Gtk$Gtk$TargetEntry$T[];

#undef RIVA_MODULE

#endif
