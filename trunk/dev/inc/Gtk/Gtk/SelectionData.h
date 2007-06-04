#ifndef Gtk_SelectionData_H
#define Gtk_SelectionData_H

#define RIVA_MODULE Gtk$Gtk$SelectionData
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$SelectionData_t {
	Std$Type_t *Type;
	GtkSelectionData Value;
} Gtk$Gtk$SelectionData_t;

extern Std$Type_t Gtk$Gtk$SelectionData$T[];

#undef RIVA_MODULE

#endif
