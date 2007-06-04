#ifndef Gtk_TextAttributes_H
#define Gtk_TextAttributes_H

#define RIVA_MODULE Gtk$Gtk$TextAttributes
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$TextAttributes_t {
	Std$Type_t *Type;
	GtkTextAttributes *Value;
} Gtk$Gtk$TextAttributes_t;

extern Std$Type_t Gtk$Gtk$TextAttributes$T[];

#undef RIVA_MODULE

#endif
