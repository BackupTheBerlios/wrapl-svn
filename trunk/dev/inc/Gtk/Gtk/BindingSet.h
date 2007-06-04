#ifndef Gtk_BindingSet_H
#define Gtk_BindingSet_H

#define RIVA_MODULE Gtk$Gtk$BindingSet
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$BindingSet_t {
	Std$Type_t *Type;
	GtkBindingSet *Value;
} Gtk$Gtk$BindingSet_t;

extern Std$Type_t Gtk$Gtk$BindingSet$T[];

#undef RIVA_MODULE

#endif
