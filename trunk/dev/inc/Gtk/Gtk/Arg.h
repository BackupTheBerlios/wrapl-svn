#ifndef Gtk_Arg_H
#define Gtk_Arg_H

#define RIVA_MODULE Gtk$Gtk$Arg
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$Arg_t {
	Std$Type_t *Type;
	GtkArg Value;
} Gtk$Gtk$Arg_t;

extern Std$Type_t Gtk$Gtk$Arg$T[];

#undef RIVA_MODULE

#endif
