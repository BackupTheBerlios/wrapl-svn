#ifndef Gtk_TextIter_H
#define Gtk_TextIter_H

#define RIVA_MODULE Gtk$Gtk$TextIter
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$TextIter_t {
	Std$Type_t *Type;
	GtkTextIter Value;
} Gtk$Gtk$TextIter_t;

extern Std$Type_t Gtk$Gtk$TextIter$T[];

#undef RIVA_MODULE

#endif
