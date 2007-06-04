#ifndef Gtk_RcProperty_H
#define Gtk_RcProperty_H

#define RIVA_MODULE Gtk$Gtk$RcProperty
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$RcProperty_t {
	Std$Type_t *Type;
	GtkRcProperty Value;
} Gtk$Gtk$RcProperty_t;

extern Std$Type_t Gtk$Gtk$RcProperty$T[];

#undef RIVA_MODULE

#endif
