#ifndef Gtk_AccelKey_H
#define Gtk_AccelKey_H

#define RIVA_MODULE Gtk$Gtk$AccelKey
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$AccelKey_t {
	Std$Type_t *Type;
	GtkAccelKey Value;
} Gtk$Gtk$AccelKey_t;

extern Std$Type_t Gtk$Gtk$AccelKey$T[];

#undef RIVA_MODULE

#endif
