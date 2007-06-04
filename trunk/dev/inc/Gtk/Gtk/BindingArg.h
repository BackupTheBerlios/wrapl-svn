#ifndef Gtk_BindingArg_H
#define Gtk_BindingArg_H

#define RIVA_MODULE Gtk$Gtk$BindingArg
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$BindingArg_t {
	Std$Type_t *Type;
	GtkBindingArg Value;
} Gtk$Gtk$BindingArg_t;

extern Std$Type_t Gtk$Gtk$BindingArg$T[];

#undef RIVA_MODULE

#endif
