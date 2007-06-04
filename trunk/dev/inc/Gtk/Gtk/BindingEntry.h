#ifndef Gtk_BindingEntry_H
#define Gtk_BindingEntry_H

#define RIVA_MODULE Gtk$Gtk$BindingEntry
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$BindingEntry_t {
	Std$Type_t *Type;
	GtkBindingEntry Value;
} Gtk$Gtk$BindingEntry_t;

extern Std$Type_t Gtk$Gtk$BindingEntry$T[];

#undef RIVA_MODULE

#endif
